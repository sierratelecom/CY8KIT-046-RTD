/*******************************************************************************
* File Name: OpAmp_In.h  
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

#if !defined(CY_PINS_OpAmp_In_H) /* Pins OpAmp_In_H */
#define CY_PINS_OpAmp_In_H

#include "cytypes.h"
#include "cyfitter.h"
#include "OpAmp_In_aliases.h"


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
} OpAmp_In_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   OpAmp_In_Read(void);
void    OpAmp_In_Write(uint8 value);
uint8   OpAmp_In_ReadDataReg(void);
#if defined(OpAmp_In__PC) || (CY_PSOC4_4200L) 
    void    OpAmp_In_SetDriveMode(uint8 mode);
#endif
void    OpAmp_In_SetInterruptMode(uint16 position, uint16 mode);
uint8   OpAmp_In_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void OpAmp_In_Sleep(void); 
void OpAmp_In_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(OpAmp_In__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define OpAmp_In_DRIVE_MODE_BITS        (3)
    #define OpAmp_In_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - OpAmp_In_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the OpAmp_In_SetDriveMode() function.
         *  @{
         */
        #define OpAmp_In_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define OpAmp_In_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define OpAmp_In_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define OpAmp_In_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define OpAmp_In_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define OpAmp_In_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define OpAmp_In_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define OpAmp_In_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define OpAmp_In_MASK               OpAmp_In__MASK
#define OpAmp_In_SHIFT              OpAmp_In__SHIFT
#define OpAmp_In_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in OpAmp_In_SetInterruptMode() function.
     *  @{
     */
        #define OpAmp_In_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define OpAmp_In_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define OpAmp_In_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define OpAmp_In_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(OpAmp_In__SIO)
    #define OpAmp_In_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(OpAmp_In__PC) && (CY_PSOC4_4200L)
    #define OpAmp_In_USBIO_ENABLE               ((uint32)0x80000000u)
    #define OpAmp_In_USBIO_DISABLE              ((uint32)(~OpAmp_In_USBIO_ENABLE))
    #define OpAmp_In_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define OpAmp_In_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define OpAmp_In_USBIO_ENTER_SLEEP          ((uint32)((1u << OpAmp_In_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << OpAmp_In_USBIO_SUSPEND_DEL_SHIFT)))
    #define OpAmp_In_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << OpAmp_In_USBIO_SUSPEND_SHIFT)))
    #define OpAmp_In_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << OpAmp_In_USBIO_SUSPEND_DEL_SHIFT)))
    #define OpAmp_In_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(OpAmp_In__PC)
    /* Port Configuration */
    #define OpAmp_In_PC                 (* (reg32 *) OpAmp_In__PC)
#endif
/* Pin State */
#define OpAmp_In_PS                     (* (reg32 *) OpAmp_In__PS)
/* Data Register */
#define OpAmp_In_DR                     (* (reg32 *) OpAmp_In__DR)
/* Input Buffer Disable Override */
#define OpAmp_In_INP_DIS                (* (reg32 *) OpAmp_In__PC2)

/* Interrupt configuration Registers */
#define OpAmp_In_INTCFG                 (* (reg32 *) OpAmp_In__INTCFG)
#define OpAmp_In_INTSTAT                (* (reg32 *) OpAmp_In__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define OpAmp_In_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(OpAmp_In__SIO)
    #define OpAmp_In_SIO_REG            (* (reg32 *) OpAmp_In__SIO)
#endif /* (OpAmp_In__SIO_CFG) */

/* USBIO registers */
#if !defined(OpAmp_In__PC) && (CY_PSOC4_4200L)
    #define OpAmp_In_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define OpAmp_In_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define OpAmp_In_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define OpAmp_In_DRIVE_MODE_SHIFT       (0x00u)
#define OpAmp_In_DRIVE_MODE_MASK        (0x07u << OpAmp_In_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins OpAmp_In_H */


/* [] END OF FILE */
