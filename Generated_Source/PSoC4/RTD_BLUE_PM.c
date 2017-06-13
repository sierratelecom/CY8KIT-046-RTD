/*******************************************************************************
* File Name: RTD_BLUE.c  
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
#include "RTD_BLUE.h"

static RTD_BLUE_BACKUP_STRUCT  RTD_BLUE_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: RTD_BLUE_Sleep
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
*  \snippet RTD_BLUE_SUT.c usage_RTD_BLUE_Sleep_Wakeup
*******************************************************************************/
void RTD_BLUE_Sleep(void)
{
    #if defined(RTD_BLUE__PC)
        RTD_BLUE_backup.pcState = RTD_BLUE_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            RTD_BLUE_backup.usbState = RTD_BLUE_CR1_REG;
            RTD_BLUE_USB_POWER_REG |= RTD_BLUE_USBIO_ENTER_SLEEP;
            RTD_BLUE_CR1_REG &= RTD_BLUE_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(RTD_BLUE__SIO)
        RTD_BLUE_backup.sioState = RTD_BLUE_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        RTD_BLUE_SIO_REG &= (uint32)(~RTD_BLUE_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: RTD_BLUE_Wakeup
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
*  Refer to RTD_BLUE_Sleep() for an example usage.
*******************************************************************************/
void RTD_BLUE_Wakeup(void)
{
    #if defined(RTD_BLUE__PC)
        RTD_BLUE_PC = RTD_BLUE_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            RTD_BLUE_USB_POWER_REG &= RTD_BLUE_USBIO_EXIT_SLEEP_PH1;
            RTD_BLUE_CR1_REG = RTD_BLUE_backup.usbState;
            RTD_BLUE_USB_POWER_REG &= RTD_BLUE_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(RTD_BLUE__SIO)
        RTD_BLUE_SIO_REG = RTD_BLUE_backup.sioState;
    #endif
}


/* [] END OF FILE */
