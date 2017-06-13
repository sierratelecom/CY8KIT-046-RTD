/*******************************************************************************
* File Name: CURRENT_5.c  
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
#include "CURRENT_5.h"

static CURRENT_5_BACKUP_STRUCT  CURRENT_5_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: CURRENT_5_Sleep
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
*  \snippet CURRENT_5_SUT.c usage_CURRENT_5_Sleep_Wakeup
*******************************************************************************/
void CURRENT_5_Sleep(void)
{
    #if defined(CURRENT_5__PC)
        CURRENT_5_backup.pcState = CURRENT_5_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            CURRENT_5_backup.usbState = CURRENT_5_CR1_REG;
            CURRENT_5_USB_POWER_REG |= CURRENT_5_USBIO_ENTER_SLEEP;
            CURRENT_5_CR1_REG &= CURRENT_5_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CURRENT_5__SIO)
        CURRENT_5_backup.sioState = CURRENT_5_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        CURRENT_5_SIO_REG &= (uint32)(~CURRENT_5_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: CURRENT_5_Wakeup
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
*  Refer to CURRENT_5_Sleep() for an example usage.
*******************************************************************************/
void CURRENT_5_Wakeup(void)
{
    #if defined(CURRENT_5__PC)
        CURRENT_5_PC = CURRENT_5_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            CURRENT_5_USB_POWER_REG &= CURRENT_5_USBIO_EXIT_SLEEP_PH1;
            CURRENT_5_CR1_REG = CURRENT_5_backup.usbState;
            CURRENT_5_USB_POWER_REG &= CURRENT_5_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CURRENT_5__SIO)
        CURRENT_5_SIO_REG = CURRENT_5_backup.sioState;
    #endif
}


/* [] END OF FILE */
