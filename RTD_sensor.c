/*
 * Copyright 2017, Sierra Telecom. All Rights Reserved.
 *
 * This software, associated documentation and materials ("Software"),
 * is owned by Sierra Telecom ("Sierra") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Sierra hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Sierra's
 * integrated circuit products. Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Sierra.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Sierra
 * reserves the right to make changes to the Software without notice. Sierra
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Sierra does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Sierra product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Sierra's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Sierra against all liability.
 */
/** @file RTD_sensor.c
 *
 *  Created on: April 26, 2017
 *      Author: greg.phillips
 */

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow the usage of floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif


#include <project.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "arduino.h"
#include "cypress_arduino.h"
/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/
/* Calibration resistor value for RTD temp sensors - 100ohms as used 
 * on PSoC Temperature sensor EBK */
#define CAL_REF_RESISTOR                (100u)
#define ADC_BIT_VALUE                   0.0005     // 1.024 / 2048 
/* Define the current per bit of the IDAC drive */
#define IDAC_CURRENT_PER_BIT            (2.4)

/* Scaling factors */
#define TEMP_SCALE                      (100u)
#define OP_AMP_RESISTANCE_SCALE         (3u)

/* Defines for ADC MUX channels */
#define MUX_RTD_CHANNEL    (0)
#define MUX_CAL_CHANNEL    (1)
#define MUX_REF_CHANNEL    (2)

/* Define the Mask for channel selection */
#define MASK_RTD_CHANNEL    0x01
#define MASK_CAL_CHANNEL    0x02
#define MASK_REF_CHANNEL    0x04

/* Define ADC_SAR_SEQ Channels */
#define ADC_RTD_CHANNEL     0x00
#define ADC_CAL_CHANNEL     0x01
#define ADC_REF_CHANNEL     0x02

#define IDAC_MEASURE_VAL    0xFF    // 500uA?

/******************************************************
 *                   Enumerations
 ******************************************************/
enum {
    RTD_INIT,
    RTD_SETUP_CALIBRATE_CURRENT,
    RTD_GET_CURRENT_CAL_ZERO_OFFSET,
    RTD_CURRENT_CALIBRATE,
    RTD_SETUP_CALIBRATE,
    RTD_GET_CAL_ZERO_OFFSET,
    RTD_CALIBRATE,
    RTD_GET_RTD_ZERO_OFFSET,
    RTD_SETUP_READ_TEMP,
    RTD_READ_TEMP,
    RTD_CALCUATE_TEMP,
};
/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

/******************************************************
 *               Variable Definitions
 ******************************************************/
/*
 *  Voltage across know 100 Ohm Resistor
 */
uint32_t ref_voltage;
/*
 * Voltage read across calibration resistor at Full current
 */
 uint32 rtdCalVoltage = 0;
/*
 * Calculated RTD resistance
 */
 uint32 rtdRes = 0;
/*
 * Measured RTD voltage
 */
 uint32 rtdVoltage = 0;
/*
 * Calculated temperature using RTD sensor resistance
 */
 int32 rtdTemp = 0;
/*
 * Offset counts
 */
uint32 zeroCurrentOffset = 0;
/*
 * Actual Current as calculated
 */
float current_source = 0;
/*
 * Data ready for channel mask
 */
volatile uint32 dataReady = 0u;
/*
 * Stored result of conversion
 */
volatile int16 result[ADC_SAR_SEQ_TOTAL_CHANNELS_NUM];
/*
 * State variable for continuing calculations
 */
uint32_t RTD_state;
/******************************************************
 *               Function Definitions
 ******************************************************/
/**
  * ADC_SAR_SEQ_ISR_LOC
  * @brief Handle Interrupt Service Routine. Source - ADC SAR Seq.
  * @param  None
  * @retval : None
  */
CY_ISR(ADC_SAR_SEQ_ISR_LOC)
{
    uint32 intr_status;
    uint32 range_status;

    /* Read interrupt status registers */
    intr_status = ADC_SAR_SEQ_SAR_INTR_MASKED_REG;
    /* Check for End of Scan interrupt */
    if((intr_status & ADC_SAR_SEQ_EOS_MASK) != 0u)
    {
        /* Read range detect status */
        range_status = ADC_SAR_SEQ_SAR_RANGE_INTR_MASKED_REG;
        
        /* Verify that the conversion result met the condition Low_Limit <= Result < High_Limit  */
        if( range_status & MASK_RTD_CHANNEL ) {
            /* Read conversion result */
            result[ ADC_RTD_CHANNEL ] = ADC_SAR_SEQ_GetResult16( ADC_RTD_CHANNEL );
            dataReady |= MASK_RTD_CHANNEL;
        }
        if( range_status & MASK_REF_CHANNEL ) {
            /* Read conversion result */
            result[ ADC_REF_CHANNEL ] = ADC_SAR_SEQ_GetResult16( ADC_REF_CHANNEL );
            dataReady |= MASK_REF_CHANNEL;
        }
        /* Clear range detect status */
        ADC_SAR_SEQ_SAR_RANGE_INTR_REG = range_status;
    }    
    /* Clear handled interrupt */
    ADC_SAR_SEQ_SAR_INTR_REG = intr_status;
}

/**
  * @brief Initialize any sensors
  * @param  None
  * @retval : None
  */
void init_RTD(void)
{
    RTD_state = RTD_INIT;
}

float temp = 25.0;

/**
  * @brief process the RTD sensor
  * @param  None
  * @retval : None
  */
void process_RTD(void)
{
    float temp;
   
    switch( RTD_state ) {
        case RTD_INIT :
            /*
             * Setup the Converter for a calbration
             *
             * Start the devices
             * Select the correct MUX channel
             * Select the mask to only convert the calibration ADC channel
             */
	        IDAC_Start();
            Opamp_1_Start();
	        ADC_SAR_SEQ_Start();
            ADC_SAR_SEQ_IRQ_StartEx( ADC_SAR_SEQ_ISR_LOC );
            CyGlobalIntEnable;
            RTD_state = RTD_SETUP_CALIBRATE_CURRENT;
            break;
        case RTD_SETUP_CALIBRATE_CURRENT :
            /*
             * Set up for Zero Offset reading
             */
            IDAC_SetValue(0u);
//            ADC_SAR_SEQ_SetChanMask( MASK_REF_CHANNEL );
            ADC_SAR_SEQ_StartConvert();
            /*
             * Enable interrupt and set interrupt handler to local routine
             */
            RTD_state = RTD_GET_CURRENT_CAL_ZERO_OFFSET;
            break;
        case RTD_GET_CURRENT_CAL_ZERO_OFFSET :
            if( 0 != ( dataReady & MASK_REF_CHANNEL ) ) {
                ADC_SAR_SEQ_StopConvert();
                dataReady &= ~MASK_REF_CHANNEL;
                zeroCurrentOffset =  0x800; // result[ ADC_REF_CHANNEL ];
                /*
                * Setup for Calibration - Configure IDAC to measurement current
                */
                IDAC_SetValue( IDAC_MEASURE_VAL );
                ADC_SAR_SEQ_StartConvert();
                RTD_state = RTD_CURRENT_CALIBRATE;
            }
            break;
        case RTD_CURRENT_CALIBRATE :
            if( 0 != ( dataReady & MASK_REF_CHANNEL ) ) {
                ADC_SAR_SEQ_StopConvert();
                dataReady &= ~MASK_REF_CHANNEL;
                ref_voltage = result[ ADC_REF_CHANNEL ];
                /*
                 * Get CDS difference
                 */
            	ref_voltage = ref_voltage - zeroCurrentOffset;
                /*
                 * Update Sensor Value Current = Voltage / Resistance -> Ref_voltage / 100
                 */
                current_source = ( (float) ( ref_voltage ) * ADC_BIT_VALUE ) / 100.63; // CAL_REF_RESISTOR;
                set_float_sensor_data( ASCB_SENSOR_CURRENT_SOURCE, (float) ref_voltage * ADC_BIT_VALUE );
                RTD_state = RTD_SETUP_CALIBRATE;
            }
            break;
        case RTD_SETUP_CALIBRATE :  // Mesure wire resistance
            /*
             * Set up for Zero Offset reading
             */
            IDAC_SetValue(0u);
//            ADC_SAR_SEQ_SetChanMask( MASK_CAL_CHANNEL );
            ADC_SAR_SEQ_StartConvert();
            RTD_state = RTD_GET_CAL_ZERO_OFFSET;
            break;
        case RTD_GET_CAL_ZERO_OFFSET :
            zeroCurrentOffset = 0;
            /*
             * Setup for Calibration - Configure IDAC to measurement current level
             *
             * Leave this for now so when / if we add real calibration of wires state machine is same
             */
            IDAC_SetValue( IDAC_MEASURE_VAL );
            ADC_SAR_SEQ_StartConvert();
            RTD_state = RTD_CALIBRATE;
            break;
        case RTD_CALIBRATE :
            /*
             * Rough guess for now
             */
            rtdCalVoltage = 1;
            /*
             * Get CDS difference
             */
          	rtdCalVoltage = rtdCalVoltage - zeroCurrentOffset;
            /*
             * Update Sensor Value
             */
            set_float_sensor_data( ASCB_SENSOR_CAL_VOLTAGE, (float) rtdCalVoltage * ADC_BIT_VALUE );
            /*
             * Set up for Zero Offset reading
             */
            IDAC_SetValue(0u);
//                ADC_SAR_SEQ_SetChanMask( MASK_RTD_CHANNEL );
            ADC_SAR_SEQ_StartConvert();
            RTD_state = RTD_GET_RTD_ZERO_OFFSET;
            break;
        case RTD_GET_RTD_ZERO_OFFSET :
            if( 0 != ( dataReady & MASK_RTD_CHANNEL ) ) {
                ADC_SAR_SEQ_StopConvert();
                dataReady &= ~MASK_RTD_CHANNEL;
                zeroCurrentOffset = 0x800;  // result[ ADC_RTD_CHANNEL ];
                /*
                * Setup for Temperature - Configure IDAC to measurement current
                */
                RTD_state = RTD_SETUP_READ_TEMP;
            }
            break;
        case RTD_SETUP_READ_TEMP :
            IDAC_SetValue( IDAC_MEASURE_VAL );
            ADC_SAR_SEQ_StartConvert();
            RTD_state = RTD_READ_TEMP;
            break;
        case RTD_READ_TEMP :
            if( 0 != ( dataReady & MASK_RTD_CHANNEL ) ) {
                dataReady &= ~MASK_RTD_CHANNEL;
                ADC_SAR_SEQ_StopConvert();
                rtdVoltage = result[ ADC_RTD_CHANNEL ];
                rtdVoltage = rtdVoltage - zeroCurrentOffset;
                /*
                 * Update Sensor Value
                 */
                set_float_sensor_data( ASCB_SENSOR_RTD_VOLTAGE, (float) rtdVoltage * ADC_BIT_VALUE );
                RTD_state = RTD_CALCUATE_TEMP;
                /*
                 * Set Zero to power off
                 */
                IDAC_SetValue(0u);
            }
            break;
        case RTD_CALCUATE_TEMP :
           	/* Get CDS difference */
            
            /* Find RTD resistance */
    	    rtdRes = ( uint32_t) ( ( (float) ( rtdVoltage  - rtdCalVoltage ) * ADC_BIT_VALUE ) / current_source ) * 1000.0;

            /* Get temperature */
            rtdTemp = RTD_GetTemperature(rtdRes);

            /* Get temperature in degree C */
            temp = ( (float) ( rtdTemp )/ TEMP_SCALE );

            /*
             * Update Sensor Value
             */
            set_float_sensor_data( ASCB_SENSOR_TEMP, temp );
            RTD_state = RTD_SETUP_CALIBRATE_CURRENT;
            break;
        default :
            RTD_state = RTD_INIT;
            break;
    }

}

/* [] END OF FILE */

