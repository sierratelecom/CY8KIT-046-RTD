/*******************************************************************************
* File Name: Calib_4_4.c  
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
#include "Calib_4_4.h"

static Calib_4_4_BACKUP_STRUCT  Calib_4_4_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Calib_4_4_Sleep
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
*  \snippet Calib_4_4_SUT.c usage_Calib_4_4_Sleep_Wakeup
*******************************************************************************/
void Calib_4_4_Sleep(void)
{
    #if defined(Calib_4_4__PC)
        Calib_4_4_backup.pcState = Calib_4_4_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Calib_4_4_backup.usbState = Calib_4_4_CR1_REG;
            Calib_4_4_USB_POWER_REG |= Calib_4_4_USBIO_ENTER_SLEEP;
            Calib_4_4_CR1_REG &= Calib_4_4_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Calib_4_4__SIO)
        Calib_4_4_backup.sioState = Calib_4_4_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Calib_4_4_SIO_REG &= (uint32)(~Calib_4_4_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Calib_4_4_Wakeup
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
*  Refer to Calib_4_4_Sleep() for an example usage.
*******************************************************************************/
void Calib_4_4_Wakeup(void)
{
    #if defined(Calib_4_4__PC)
        Calib_4_4_PC = Calib_4_4_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Calib_4_4_USB_POWER_REG &= Calib_4_4_USBIO_EXIT_SLEEP_PH1;
            Calib_4_4_CR1_REG = Calib_4_4_backup.usbState;
            Calib_4_4_USB_POWER_REG &= Calib_4_4_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Calib_4_4__SIO)
        Calib_4_4_SIO_REG = Calib_4_4_backup.sioState;
    #endif
}


/* [] END OF FILE */
