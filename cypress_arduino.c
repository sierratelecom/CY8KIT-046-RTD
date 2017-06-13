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

/** @file cypress_ardunio.c
 *
 *  Created on: Feb 18, 2017
 *      Author: greg.phillips
 */




#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "arduino.h"
#include "cypress_arduino.h"

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

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
arduino_config_t acb = {
      .config =
         {
            .arduino_code = IMATRIX_ARDUINO_CODE,
            .no_controls = NO_ARDUINO_CONTROLS,
            .no_sensors = NO_ARDUINO_SENSORS,
         },
};

/******************************************************
 *               Function Definitions
 ******************************************************/
/**
  * @brief  Initialize the Arduino sub system
  * @param  None
  * @retval : None
  */
void init_arduino(void)
{
    
}
void set_uint32_sensor_data( uint16_t sensor_no, uint32_t value )
{
   if( sensor_no < acb.config.no_sensors ) {
        /*
         * Save the value and set the bit to indicate new value to upload
         */
        acb.data_sensors[ sensor_no ].uint_32bit = value;
        acb.slave.status |= ARDUINO_NEW_VALUE << ( sensor_no * 2);
        
//      printf( "Saving sensor: %u, value: %f\r\n", sensor_no, value );
   }
}
void set_int32_sensor_data( uint16_t sensor_no, int32_t value )
{
   if( sensor_no < acb.config.no_sensors ) {
        /*
         * Save the value and set the bit to indicate new value to upload
         */
        acb.data_sensors[ sensor_no ].int_32bit = value;
        acb.slave.status |= ARDUINO_NEW_VALUE << ( sensor_no * 2);
        
//      printf( "Saving sensor: %u, value: %f\r\n", sensor_no, value );
   }
}

void set_float_sensor_data( uint16_t sensor_no, float value )
{
   if( sensor_no < acb.config.no_sensors ) {
        /*
         * Save the value and set the bit to indicate new value to upload
         */
        acb.data_sensors[ sensor_no ].float_32bit = value;
        acb.slave.status |= ARDUINO_NEW_VALUE << ( sensor_no * 2);
        
//      printf( "Saving sensor: %u, value: %f\r\n", sensor_no, value );
   }
}

/* [] END OF FILE */
