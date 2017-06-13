/*******************************************************************************
* File Name: Calib_4_5.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Calib_4_5_ALIASES_H) /* Pins Calib_4_5_ALIASES_H */
#define CY_PINS_Calib_4_5_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Calib_4_5_0			(Calib_4_5__0__PC)
#define Calib_4_5_0_PS		(Calib_4_5__0__PS)
#define Calib_4_5_0_PC		(Calib_4_5__0__PC)
#define Calib_4_5_0_DR		(Calib_4_5__0__DR)
#define Calib_4_5_0_SHIFT	(Calib_4_5__0__SHIFT)
#define Calib_4_5_0_INTR	((uint16)((uint16)0x0003u << (Calib_4_5__0__SHIFT*2u)))

#define Calib_4_5_INTR_ALL	 ((uint16)(Calib_4_5_0_INTR))


#endif /* End Pins Calib_4_5_ALIASES_H */


/* [] END OF FILE */
