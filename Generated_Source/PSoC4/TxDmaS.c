/*******************************************************************************
* File Name: TxDmaS.h
* Version 1.0
*
* Description:
*  This file contains all of the channel DMA API functions.
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TxDmaS.h"

uint8 TxDmaS_initVar = 0u;


/*******************************************************************************
* Function Name: TxDmaS_Start
********************************************************************************
*
* Summary:
*  Calls Init() to configure the DMA channel based on the customizer settings if
*  the channel has not been initialized before.
*  Sets source and destination address, validates descriptor 0 and enables the
*  channel. After calling this function the DMA channel is active and waiting
*  for a trigger.
*
* Parameters:
*  srcAddress: Address of DMA transfer source for descriptor 0.
*  dstAddress: Address of DMA transfer destination for descriptor 0.
*                   
* Return:
*  None.
*
*******************************************************************************/
void TxDmaS_Start(void * srcAddress, void * dstAddress)
{
    if(0u == TxDmaS_initVar)
    {
        TxDmaS_Init();
        TxDmaS_initVar = 1u;
    }
    CyDmaEnable();
    TxDmaS_SetSrcAddress(0, srcAddress);
    TxDmaS_SetDstAddress(0, dstAddress);
    TxDmaS_ValidateDescriptor(0);
    TxDmaS_ChEnable();
}


/*******************************************************************************
* Function Name: TxDmaS_Init
********************************************************************************
*
* Summary:
*  Initializes the DMA channel based on the parameters set in the component
*  customizer. It is not necessary to call TxDmaS_Init() because the
*  TxDmaS_Start() API calls this function, which is the preferred method
*  to begin component operation.
*
* Parameters:
*  None.
*                   
* Return:
*  None.
*
* Side effect:
*  The first descriptor is set to descriptor 0. This function should not be
*  called while the channel is enabled. All settings will be reset to their
*  initial values.
*
*******************************************************************************/
void TxDmaS_Init(void)
{
    CYDMA_CH_CTL_BASE.ctl[TxDmaS_CHANNEL] = TxDmaS_CHANNEL_CFG;
    CYDMA_DESCR_BASE.descriptor[TxDmaS_CHANNEL][0].ctl = TxDmaS_DESCR0_CFG;
    CYDMA_DESCR_BASE.descriptor[TxDmaS_CHANNEL][1].ctl = TxDmaS_DESCR1_CFG;

    /* If the Generate IRQ option is selected for descriptor 0 or 1, set the
    * channel bit field in the DMA interrupt mask register.
    */
    #if (0u != ((TxDmaS_DESCR0_CFG | TxDmaS_DESCR1_CFG) & CYDMA_GENERATE_IRQ))
        CYDMA_INTR_MASK_REG |= TxDmaS_CHANNEL_MASK;
    #endif /* (0u != ((TxDmaS_DESCR0_CFG | TxDmaS_DESCR1_CFG) & CYDMA_GENERATE_IRQ)) */
}


/* [] END OF FILE */
