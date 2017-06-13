/*******************************************************************************
* File Name: Calib_4_4.h  
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

#if !defined(CY_PINS_Calib_4_4_H) /* Pins Calib_4_4_H */
#define CY_PINS_Calib_4_4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Calib_4_4_aliases.h"


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
} Calib_4_4_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Calib_4_4_Read(void);
void    Calib_4_4_Write(uint8 value);
uint8   Calib_4_4_ReadDataReg(void);
#if defined(Calib_4_4__PC) || (CY_PSOC4_4200L) 
    void    Calib_4_4_SetDriveMode(uint8 mode);
#endif
void    Calib_4_4_SetInterruptMode(uint16 position, uint16 mode);
uint8   Calib_4_4_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Calib_4_4_Sleep(void); 
void Calib_4_4_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Calib_4_4__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Calib_4_4_DRIVE_MODE_BITS        (3)
    #define Calib_4_4_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Calib_4_4_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Calib_4_4_SetDriveMode() function.
         *  @{
         */
        #define Calib_4_4_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Calib_4_4_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Calib_4_4_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Calib_4_4_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Calib_4_4_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Calib_4_4_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Calib_4_4_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Calib_4_4_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Calib_4_4_MASK               Calib_4_4__MASK
#define Calib_4_4_SHIFT              Calib_4_4__SHIFT
#define Calib_4_4_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Calib_4_4_SetInterruptMode() function.
     *  @{
     */
        #define Calib_4_4_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Calib_4_4_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Calib_4_4_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Calib_4_4_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Calib_4_4__SIO)
    #define Calib_4_4_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Calib_4_4__PC) && (CY_PSOC4_4200L)
    #define Calib_4_4_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Calib_4_4_USBIO_DISABLE              ((uint32)(~Calib_4_4_USBIO_ENABLE))
    #define Calib_4_4_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Calib_4_4_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Calib_4_4_USBIO_ENTER_SLEEP          ((uint32)((1u << Calib_4_4_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Calib_4_4_USBIO_SUSPEND_DEL_SHIFT)))
    #define Calib_4_4_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Calib_4_4_USBIO_SUSPEND_SHIFT)))
    #define Calib_4_4_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Calib_4_4_USBIO_SUSPEND_DEL_SHIFT)))
    #define Calib_4_4_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Calib_4_4__PC)
    /* Port Configuration */
    #define Calib_4_4_PC                 (* (reg32 *) Calib_4_4__PC)
#endif
/* Pin State */
#define Calib_4_4_PS                     (* (reg32 *) Calib_4_4__PS)
/* Data Register */
#define Calib_4_4_DR                     (* (reg32 *) Calib_4_4__DR)
/* Input Buffer Disable Override */
#define Calib_4_4_INP_DIS                (* (reg32 *) Calib_4_4__PC2)

/* Interrupt configuration Registers */
#define Calib_4_4_INTCFG                 (* (reg32 *) Calib_4_4__INTCFG)
#define Calib_4_4_INTSTAT                (* (reg32 *) Calib_4_4__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Calib_4_4_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Calib_4_4__SIO)
    #define Calib_4_4_SIO_REG            (* (reg32 *) Calib_4_4__SIO)
#endif /* (Calib_4_4__SIO_CFG) */

/* USBIO registers */
#if !defined(Calib_4_4__PC) && (CY_PSOC4_4200L)
    #define Calib_4_4_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Calib_4_4_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Calib_4_4_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Calib_4_4_DRIVE_MODE_SHIFT       (0x00u)
#define Calib_4_4_DRIVE_MODE_MASK        (0x07u << Calib_4_4_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Calib_4_4_H */


/* [] END OF FILE */
