/*******************************************************************************
* File Name: CAL_RED1.h  
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

#if !defined(CY_PINS_CAL_RED1_ALIASES_H) /* Pins CAL_RED1_ALIASES_H */
#define CY_PINS_CAL_RED1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CAL_RED1_0			(CAL_RED1__0__PC)
#define CAL_RED1_0_PS		(CAL_RED1__0__PS)
#define CAL_RED1_0_PC		(CAL_RED1__0__PC)
#define CAL_RED1_0_DR		(CAL_RED1__0__DR)
#define CAL_RED1_0_SHIFT	(CAL_RED1__0__SHIFT)
#define CAL_RED1_0_INTR	((uint16)((uint16)0x0003u << (CAL_RED1__0__SHIFT*2u)))

#define CAL_RED1_INTR_ALL	 ((uint16)(CAL_RED1_0_INTR))


#endif /* End Pins CAL_RED1_ALIASES_H */


/* [] END OF FILE */
