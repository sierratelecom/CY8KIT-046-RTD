/*******************************************************************************
* File Name: Current_Mux.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_Current_Mux_H)
#define CY_AMUX_Current_Mux_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void Current_Mux_Start(void) ;
#define Current_Mux_Init() Current_Mux_Start()
void Current_Mux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void Current_Mux_Stop(void); */
/* void Current_Mux_Select(uint8 channel); */
/* void Current_Mux_Connect(uint8 channel); */
/* void Current_Mux_Disconnect(uint8 channel); */
/* void Current_Mux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define Current_Mux_CHANNELS  3u
#define Current_Mux_MUXTYPE   1
#define Current_Mux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define Current_Mux_NULL_CHANNEL 0xFFu
#define Current_Mux_MUX_SINGLE   1
#define Current_Mux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if Current_Mux_MUXTYPE == Current_Mux_MUX_SINGLE
# if !Current_Mux_ATMOSTONE
#  define Current_Mux_Connect(channel) Current_Mux_Set(channel)
# endif
# define Current_Mux_Disconnect(channel) Current_Mux_Unset(channel)
#else
# if !Current_Mux_ATMOSTONE
void Current_Mux_Connect(uint8 channel) ;
# endif
void Current_Mux_Disconnect(uint8 channel) ;
#endif

#if Current_Mux_ATMOSTONE
# define Current_Mux_Stop() Current_Mux_DisconnectAll()
# define Current_Mux_Select(channel) Current_Mux_FastSelect(channel)
void Current_Mux_DisconnectAll(void) ;
#else
# define Current_Mux_Stop() Current_Mux_Start()
void Current_Mux_Select(uint8 channel) ;
# define Current_Mux_DisconnectAll() Current_Mux_Start()
#endif

#endif /* CY_AMUX_Current_Mux_H */


/* [] END OF FILE */
