/*******************************************************************************
* File Name: CURRENT_2.c  
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
#include "CURRENT_2.h"

static CURRENT_2_BACKUP_STRUCT  CURRENT_2_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: CURRENT_2_Sleep
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
*  \snippet CURRENT_2_SUT.c usage_CURRENT_2_Sleep_Wakeup
*******************************************************************************/
void CURRENT_2_Sleep(void)
{
    #if defined(CURRENT_2__PC)
        CURRENT_2_backup.pcState = CURRENT_2_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            CURRENT_2_backup.usbState = CURRENT_2_CR1_REG;
            CURRENT_2_USB_POWER_REG |= CURRENT_2_USBIO_ENTER_SLEEP;
            CURRENT_2_CR1_REG &= CURRENT_2_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CURRENT_2__SIO)
        CURRENT_2_backup.sioState = CURRENT_2_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        CURRENT_2_SIO_REG &= (uint32)(~CURRENT_2_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: CURRENT_2_Wakeup
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
*  Refer to CURRENT_2_Sleep() for an example usage.
*******************************************************************************/
void CURRENT_2_Wakeup(void)
{
    #if defined(CURRENT_2__PC)
        CURRENT_2_PC = CURRENT_2_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            CURRENT_2_USB_POWER_REG &= CURRENT_2_USBIO_EXIT_SLEEP_PH1;
            CURRENT_2_CR1_REG = CURRENT_2_backup.usbState;
            CURRENT_2_USB_POWER_REG &= CURRENT_2_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CURRENT_2__SIO)
        CURRENT_2_SIO_REG = CURRENT_2_backup.sioState;
    #endif
}


/* [] END OF FILE */
