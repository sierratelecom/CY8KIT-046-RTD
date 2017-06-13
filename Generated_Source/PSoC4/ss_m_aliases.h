/*******************************************************************************
* File Name: ss_m.h  
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

#if !defined(CY_PINS_ss_m_ALIASES_H) /* Pins ss_m_ALIASES_H */
#define CY_PINS_ss_m_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ss_m_0			(ss_m__0__PC)
#define ss_m_0_PS		(ss_m__0__PS)
#define ss_m_0_PC		(ss_m__0__PC)
#define ss_m_0_DR		(ss_m__0__DR)
#define ss_m_0_SHIFT	(ss_m__0__SHIFT)
#define ss_m_0_INTR	((uint16)((uint16)0x0003u << (ss_m__0__SHIFT*2u)))

#define ss_m_INTR_ALL	 ((uint16)(ss_m_0_INTR))


#endif /* End Pins ss_m_ALIASES_H */


/* [] END OF FILE */
