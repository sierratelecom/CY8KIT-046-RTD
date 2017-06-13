/*******************************************************************************
* File Name: RTD_RED.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_RTD_RED_H) /* Pins RTD_RED_H */
#define CY_PINS_RTD_RED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RTD_RED_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} RTD_RED_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   RTD_RED_Read(void);
void    RTD_RED_Write(uint8 value);
uint8   RTD_RED_ReadDataReg(void);
#if defined(RTD_RED__PC) || (CY_PSOC4_4200L) 
    void    RTD_RED_SetDriveMode(uint8 mode);
#endif
void    RTD_RED_SetInterruptMode(uint16 position, uint16 mode);
uint8   RTD_RED_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void RTD_RED_Sleep(void); 
void RTD_RED_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(RTD_RED__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define RTD_RED_DRIVE_MODE_BITS        (3)
    #define RTD_RED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RTD_RED_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the RTD_RED_SetDriveMode() function.
         *  @{
         */
        #define RTD_RED_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define RTD_RED_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define RTD_RED_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define RTD_RED_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define RTD_RED_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define RTD_RED_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define RTD_RED_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define RTD_RED_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define RTD_RED_MASK               RTD_RED__MASK
#define RTD_RED_SHIFT              RTD_RED__SHIFT
#define RTD_RED_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RTD_RED_SetInterruptMode() function.
     *  @{
     */
        #define RTD_RED_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define RTD_RED_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define RTD_RED_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define RTD_RED_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(RTD_RED__SIO)
    #define RTD_RED_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(RTD_RED__PC) && (CY_PSOC4_4200L)
    #define RTD_RED_USBIO_ENABLE               ((uint32)0x80000000u)
    #define RTD_RED_USBIO_DISABLE              ((uint32)(~RTD_RED_USBIO_ENABLE))
    #define RTD_RED_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define RTD_RED_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define RTD_RED_USBIO_ENTER_SLEEP          ((uint32)((1u << RTD_RED_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << RTD_RED_USBIO_SUSPEND_DEL_SHIFT)))
    #define RTD_RED_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << RTD_RED_USBIO_SUSPEND_SHIFT)))
    #define RTD_RED_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << RTD_RED_USBIO_SUSPEND_DEL_SHIFT)))
    #define RTD_RED_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(RTD_RED__PC)
    /* Port Configuration */
    #define RTD_RED_PC                 (* (reg32 *) RTD_RED__PC)
#endif
/* Pin State */
#define RTD_RED_PS                     (* (reg32 *) RTD_RED__PS)
/* Data Register */
#define RTD_RED_DR                     (* (reg32 *) RTD_RED__DR)
/* Input Buffer Disable Override */
#define RTD_RED_INP_DIS                (* (reg32 *) RTD_RED__PC2)

/* Interrupt configuration Registers */
#define RTD_RED_INTCFG                 (* (reg32 *) RTD_RED__INTCFG)
#define RTD_RED_INTSTAT                (* (reg32 *) RTD_RED__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define RTD_RED_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(RTD_RED__SIO)
    #define RTD_RED_SIO_REG            (* (reg32 *) RTD_RED__SIO)
#endif /* (RTD_RED__SIO_CFG) */

/* USBIO registers */
#if !defined(RTD_RED__PC) && (CY_PSOC4_4200L)
    #define RTD_RED_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define RTD_RED_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define RTD_RED_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define RTD_RED_DRIVE_MODE_SHIFT       (0x00u)
#define RTD_RED_DRIVE_MODE_MASK        (0x07u << RTD_RED_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins RTD_RED_H */


/* [] END OF FILE */
