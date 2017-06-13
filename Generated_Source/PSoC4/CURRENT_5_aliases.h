/*******************************************************************************
* File Name: CURRENT_5.h  
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

#if !defined(CY_PINS_CURRENT_5_ALIASES_H) /* Pins CURRENT_5_ALIASES_H */
#define CY_PINS_CURRENT_5_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CURRENT_5_0			(CURRENT_5__0__PC)
#define CURRENT_5_0_PS		(CURRENT_5__0__PS)
#define CURRENT_5_0_PC		(CURRENT_5__0__PC)
#define CURRENT_5_0_DR		(CURRENT_5__0__DR)
#define CURRENT_5_0_SHIFT	(CURRENT_5__0__SHIFT)
#define CURRENT_5_0_INTR	((uint16)((uint16)0x0003u << (CURRENT_5__0__SHIFT*2u)))

#define CURRENT_5_INTR_ALL	 ((uint16)(CURRENT_5_0_INTR))


#endif /* End Pins CURRENT_5_ALIASES_H */


/* [] END OF FILE */
