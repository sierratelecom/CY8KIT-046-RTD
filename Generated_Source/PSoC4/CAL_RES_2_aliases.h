/*******************************************************************************
* File Name: CAL_RES_2.h  
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

#if !defined(CY_PINS_CAL_RES_2_ALIASES_H) /* Pins CAL_RES_2_ALIASES_H */
#define CY_PINS_CAL_RES_2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CAL_RES_2_0			(CAL_RES_2__0__PC)
#define CAL_RES_2_0_PS		(CAL_RES_2__0__PS)
#define CAL_RES_2_0_PC		(CAL_RES_2__0__PC)
#define CAL_RES_2_0_DR		(CAL_RES_2__0__DR)
#define CAL_RES_2_0_SHIFT	(CAL_RES_2__0__SHIFT)
#define CAL_RES_2_0_INTR	((uint16)((uint16)0x0003u << (CAL_RES_2__0__SHIFT*2u)))

#define CAL_RES_2_INTR_ALL	 ((uint16)(CAL_RES_2_0_INTR))


#endif /* End Pins CAL_RES_2_ALIASES_H */


/* [] END OF FILE */
