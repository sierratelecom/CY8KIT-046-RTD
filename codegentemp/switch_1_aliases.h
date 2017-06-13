/*******************************************************************************
* File Name: switch_1.h  
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

#if !defined(CY_PINS_switch_1_ALIASES_H) /* Pins switch_1_ALIASES_H */
#define CY_PINS_switch_1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define switch_1_0			(switch_1__0__PC)
#define switch_1_0_PS		(switch_1__0__PS)
#define switch_1_0_PC		(switch_1__0__PC)
#define switch_1_0_DR		(switch_1__0__DR)
#define switch_1_0_SHIFT	(switch_1__0__SHIFT)
#define switch_1_0_INTR	((uint16)((uint16)0x0003u << (switch_1__0__SHIFT*2u)))

#define switch_1_INTR_ALL	 ((uint16)(switch_1_0_INTR))


#endif /* End Pins switch_1_ALIASES_H */


/* [] END OF FILE */
