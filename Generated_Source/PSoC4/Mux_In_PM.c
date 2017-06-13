/*******************************************************************************
* File Name: Mux_In.c  
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
#include "Mux_In.h"

static Mux_In_BACKUP_STRUCT  Mux_In_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Mux_In_Sleep
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
*  \snippet Mux_In_SUT.c usage_Mux_In_Sleep_Wakeup
*******************************************************************************/
void Mux_In_Sleep(void)
{
    #if defined(Mux_In__PC)
        Mux_In_backup.pcState = Mux_In_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Mux_In_backup.usbState = Mux_In_CR1_REG;
            Mux_In_USB_POWER_REG |= Mux_In_USBIO_ENTER_SLEEP;
            Mux_In_CR1_REG &= Mux_In_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Mux_In__SIO)
        Mux_In_backup.sioState = Mux_In_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Mux_In_SIO_REG &= (uint32)(~Mux_In_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Mux_In_Wakeup
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
*  Refer to Mux_In_Sleep() for an example usage.
*******************************************************************************/
void Mux_In_Wakeup(void)
{
    #if defined(Mux_In__PC)
        Mux_In_PC = Mux_In_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Mux_In_USB_POWER_REG &= Mux_In_USBIO_EXIT_SLEEP_PH1;
            Mux_In_CR1_REG = Mux_In_backup.usbState;
            Mux_In_USB_POWER_REG &= Mux_In_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Mux_In__SIO)
        Mux_In_SIO_REG = Mux_In_backup.sioState;
    #endif
}


/* [] END OF FILE */
