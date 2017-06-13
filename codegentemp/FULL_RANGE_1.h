/*******************************************************************************
* File Name: FULL_RANGE_1.h  
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

#if !defined(CY_PINS_FULL_RANGE_1_H) /* Pins FULL_RANGE_1_H */
#define CY_PINS_FULL_RANGE_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "FULL_RANGE_1_aliases.h"


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
} FULL_RANGE_1_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   FULL_RANGE_1_Read(void);
void    FULL_RANGE_1_Write(uint8 value);
uint8   FULL_RANGE_1_ReadDataReg(void);
#if defined(FULL_RANGE_1__PC) || (CY_PSOC4_4200L) 
    void    FULL_RANGE_1_SetDriveMode(uint8 mode);
#endif
void    FULL_RANGE_1_SetInterruptMode(uint16 position, uint16 mode);
uint8   FULL_RANGE_1_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void FULL_RANGE_1_Sleep(void); 
void FULL_RANGE_1_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(FULL_RANGE_1__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define FULL_RANGE_1_DRIVE_MODE_BITS        (3)
    #define FULL_RANGE_1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - FULL_RANGE_1_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the FULL_RANGE_1_SetDriveMode() function.
         *  @{
         */
        #define FULL_RANGE_1_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define FULL_RANGE_1_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define FULL_RANGE_1_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define FULL_RANGE_1_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define FULL_RANGE_1_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define FULL_RANGE_1_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define FULL_RANGE_1_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define FULL_RANGE_1_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define FULL_RANGE_1_MASK               FULL_RANGE_1__MASK
#define FULL_RANGE_1_SHIFT              FULL_RANGE_1__SHIFT
#define FULL_RANGE_1_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FULL_RANGE_1_SetInterruptMode() function.
     *  @{
     */
        #define FULL_RANGE_1_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define FULL_RANGE_1_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define FULL_RANGE_1_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define FULL_RANGE_1_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(FULL_RANGE_1__SIO)
    #define FULL_RANGE_1_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(FULL_RANGE_1__PC) && (CY_PSOC4_4200L)
    #define FULL_RANGE_1_USBIO_ENABLE               ((uint32)0x80000000u)
    #define FULL_RANGE_1_USBIO_DISABLE              ((uint32)(~FULL_RANGE_1_USBIO_ENABLE))
    #define FULL_RANGE_1_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define FULL_RANGE_1_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define FULL_RANGE_1_USBIO_ENTER_SLEEP          ((uint32)((1u << FULL_RANGE_1_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << FULL_RANGE_1_USBIO_SUSPEND_DEL_SHIFT)))
    #define FULL_RANGE_1_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << FULL_RANGE_1_USBIO_SUSPEND_SHIFT)))
    #define FULL_RANGE_1_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << FULL_RANGE_1_USBIO_SUSPEND_DEL_SHIFT)))
    #define FULL_RANGE_1_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(FULL_RANGE_1__PC)
    /* Port Configuration */
    #define FULL_RANGE_1_PC                 (* (reg32 *) FULL_RANGE_1__PC)
#endif
/* Pin State */
#define FULL_RANGE_1_PS                     (* (reg32 *) FULL_RANGE_1__PS)
/* Data Register */
#define FULL_RANGE_1_DR                     (* (reg32 *) FULL_RANGE_1__DR)
/* Input Buffer Disable Override */
#define FULL_RANGE_1_INP_DIS                (* (reg32 *) FULL_RANGE_1__PC2)

/* Interrupt configuration Registers */
#define FULL_RANGE_1_INTCFG                 (* (reg32 *) FULL_RANGE_1__INTCFG)
#define FULL_RANGE_1_INTSTAT                (* (reg32 *) FULL_RANGE_1__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define FULL_RANGE_1_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(FULL_RANGE_1__SIO)
    #define FULL_RANGE_1_SIO_REG            (* (reg32 *) FULL_RANGE_1__SIO)
#endif /* (FULL_RANGE_1__SIO_CFG) */

/* USBIO registers */
#if !defined(FULL_RANGE_1__PC) && (CY_PSOC4_4200L)
    #define FULL_RANGE_1_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define FULL_RANGE_1_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define FULL_RANGE_1_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define FULL_RANGE_1_DRIVE_MODE_SHIFT       (0x00u)
#define FULL_RANGE_1_DRIVE_MODE_MASK        (0x07u << FULL_RANGE_1_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins FULL_RANGE_1_H */


/* [] END OF FILE */
