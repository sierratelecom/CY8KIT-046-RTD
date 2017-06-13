/*******************************************************************************
* File Name: mosi_m.c  
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
#include "mosi_m.h"

static mosi_m_BACKUP_STRUCT  mosi_m_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: mosi_m_Sleep
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
*  \snippet mosi_m_SUT.c usage_mosi_m_Sleep_Wakeup
*******************************************************************************/
void mosi_m_Sleep(void)
{
    #if defined(mosi_m__PC)
        mosi_m_backup.pcState = mosi_m_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            mosi_m_backup.usbState = mosi_m_CR1_REG;
            mosi_m_USB_POWER_REG |= mosi_m_USBIO_ENTER_SLEEP;
            mosi_m_CR1_REG &= mosi_m_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(mosi_m__SIO)
        mosi_m_backup.sioState = mosi_m_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        mosi_m_SIO_REG &= (uint32)(~mosi_m_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: mosi_m_Wakeup
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
*  Refer to mosi_m_Sleep() for an example usage.
*******************************************************************************/
void mosi_m_Wakeup(void)
{
    #if defined(mosi_m__PC)
        mosi_m_PC = mosi_m_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            mosi_m_USB_POWER_REG &= mosi_m_USBIO_EXIT_SLEEP_PH1;
            mosi_m_CR1_REG = mosi_m_backup.usbState;
            mosi_m_USB_POWER_REG &= mosi_m_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(mosi_m__SIO)
        mosi_m_SIO_REG = mosi_m_backup.sioState;
    #endif
}


/* [] END OF FILE */
