/*******************************************************************************
* File Name: FULL_RANGE_2.h  
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

#if !defined(CY_PINS_FULL_RANGE_2_ALIASES_H) /* Pins FULL_RANGE_2_ALIASES_H */
#define CY_PINS_FULL_RANGE_2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define FULL_RANGE_2_0			(FULL_RANGE_2__0__PC)
#define FULL_RANGE_2_0_PS		(FULL_RANGE_2__0__PS)
#define FULL_RANGE_2_0_PC		(FULL_RANGE_2__0__PC)
#define FULL_RANGE_2_0_DR		(FULL_RANGE_2__0__DR)
#define FULL_RANGE_2_0_SHIFT	(FULL_RANGE_2__0__SHIFT)
#define FULL_RANGE_2_0_INTR	((uint16)((uint16)0x0003u << (FULL_RANGE_2__0__SHIFT*2u)))

#define FULL_RANGE_2_INTR_ALL	 ((uint16)(FULL_RANGE_2_0_INTR))


#endif /* End Pins FULL_RANGE_2_ALIASES_H */


/* [] END OF FILE */
