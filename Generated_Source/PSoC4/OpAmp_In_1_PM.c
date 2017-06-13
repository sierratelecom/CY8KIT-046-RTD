/*******************************************************************************
* File Name: OpAmp_In_1.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "OpAmp_In_1.h"

static OpAmp_In_1_BACKUP_STRUCT  OpAmp_In_1_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: OpAmp_In_1_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet OpAmp_In_1_SUT.c usage_OpAmp_In_1_Sleep_Wakeup
*******************************************************************************/
void OpAmp_In_1_Sleep(void)
{
    #if defined(OpAmp_In_1__PC)
        OpAmp_In_1_backup.pcState = OpAmp_In_1_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            OpAmp_In_1_backup.usbState = OpAmp_In_1_CR1_REG;
            OpAmp_In_1_USB_POWER_REG |= OpAmp_In_1_USBIO_ENTER_SLEEP;
            OpAmp_In_1_CR1_REG &= OpAmp_In_1_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(OpAmp_In_1__SIO)
        OpAmp_In_1_backup.sioState = OpAmp_In_1_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        OpAmp_In_1_SIO_REG &= (uint32)(~OpAmp_In_1_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: OpAmp_In_1_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to OpAmp_In_1_Sleep() for an example usage.
*******************************************************************************/
void OpAmp_In_1_Wakeup(void)
{
    #if defined(OpAmp_In_1__PC)
        OpAmp_In_1_PC = OpAmp_In_1_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            OpAmp_In_1_USB_POWER_REG &= OpAmp_In_1_USBIO_EXIT_SLEEP_PH1;
            OpAmp_In_1_CR1_REG = OpAmp_In_1_backup.usbState;
            OpAmp_In_1_USB_POWER_REG &= OpAmp_In_1_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(OpAmp_In_1__SIO)
        OpAmp_In_1_SIO_REG = OpAmp_In_1_backup.sioState;
    #endif
}


/* [] END OF FILE */