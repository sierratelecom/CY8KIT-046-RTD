/*******************************************************************************
* File Name: Mux_In.h  
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

#if !defined(CY_PINS_Mux_In_H) /* Pins Mux_In_H */
#define CY_PINS_Mux_In_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Mux_In_aliases.h"


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
} Mux_In_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Mux_In_Read(void);
void    Mux_In_Write(uint8 value);
uint8   Mux_In_ReadDataReg(void);
#if defined(Mux_In__PC) || (CY_PSOC4_4200L) 
    void    Mux_In_SetDriveMode(uint8 mode);
#endif
void    Mux_In_SetInterruptMode(uint16 position, uint16 mode);
uint8   Mux_In_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Mux_In_Sleep(void); 
void Mux_In_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Mux_In__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Mux_In_DRIVE_MODE_BITS        (3)
    #define Mux_In_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Mux_In_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Mux_In_SetDriveMode() function.
         *  @{
         */
        #define Mux_In_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Mux_In_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Mux_In_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Mux_In_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Mux_In_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Mux_In_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Mux_In_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Mux_In_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Mux_In_MASK               Mux_In__MASK
#define Mux_In_SHIFT              Mux_In__SHIFT
#define Mux_In_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Mux_In_SetInterruptMode() function.
     *  @{
     */
        #define Mux_In_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Mux_In_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Mux_In_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Mux_In_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Mux_In__SIO)
    #define Mux_In_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Mux_In__PC) && (CY_PSOC4_4200L)
    #define Mux_In_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Mux_In_USBIO_DISABLE              ((uint32)(~Mux_In_USBIO_ENABLE))
    #define Mux_In_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Mux_In_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Mux_In_USBIO_ENTER_SLEEP          ((uint32)((1u << Mux_In_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Mux_In_USBIO_SUSPEND_DEL_SHIFT)))
    #define Mux_In_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Mux_In_USBIO_SUSPEND_SHIFT)))
    #define Mux_In_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Mux_In_USBIO_SUSPEND_DEL_SHIFT)))
    #define Mux_In_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Mux_In__PC)
    /* Port Configuration */
    #define Mux_In_PC                 (* (reg32 *) Mux_In__PC)
#endif
/* Pin State */
#define Mux_In_PS                     (* (reg32 *) Mux_In__PS)
/* Data Register */
#define Mux_In_DR                     (* (reg32 *) Mux_In__DR)
/* Input Buffer Disable Override */
#define Mux_In_INP_DIS                (* (reg32 *) Mux_In__PC2)

/* Interrupt configuration Registers */
#define Mux_In_INTCFG                 (* (reg32 *) Mux_In__INTCFG)
#define Mux_In_INTSTAT                (* (reg32 *) Mux_In__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Mux_In_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Mux_In__SIO)
    #define Mux_In_SIO_REG            (* (reg32 *) Mux_In__SIO)
#endif /* (Mux_In__SIO_CFG) */

/* USBIO registers */
#if !defined(Mux_In__PC) && (CY_PSOC4_4200L)
    #define Mux_In_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Mux_In_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Mux_In_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Mux_In_DRIVE_MODE_SHIFT       (0x00u)
#define Mux_In_DRIVE_MODE_MASK        (0x07u << Mux_In_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Mux_In_H */


/* [] END OF FILE */
