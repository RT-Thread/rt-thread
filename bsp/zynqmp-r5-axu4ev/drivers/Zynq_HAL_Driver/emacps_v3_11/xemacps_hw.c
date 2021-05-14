/******************************************************************************
* Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xemacps_hw.c
* @addtogroup emacps_v3_11
* @{
*
* This file contains the implementation of the ethernet interface reset sequence
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.05a kpc  28/06/13 First release
* 3.00  kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xemacps_hw.h"
#include "xparameters.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

/*****************************************************************************/
/**
* This function perform the reset sequence to the given emacps interface by
* configuring the appropriate control bits in the emacps specific registers.
* the emacps reset sequence involves the following steps
*    Disable all the interuupts
*    Clear the status registers
*    Disable Rx and Tx engines
*    Update the Tx and Rx descriptor queue registers with reset values
*    Update the other relevant control registers with reset value
*
* @param   BaseAddr of the interface
*
* @return N/A
*
* @note
* This function will not modify the slcr registers that are relevant for
* emacps controller
******************************************************************************/
void XEmacPs_ResetHw(u32 BaseAddr)
{
    u32 RegVal;

    /* Disable the interrupts  */
    XEmacPs_WriteReg(BaseAddr,XEMACPS_IDR_OFFSET,0x0U);

    /* Stop transmission,disable loopback and Stop tx and Rx engines */
    RegVal = XEmacPs_ReadReg(BaseAddr,XEMACPS_NWCTRL_OFFSET);
    RegVal &= ~((u32)XEMACPS_NWCTRL_TXEN_MASK|
                (u32)XEMACPS_NWCTRL_RXEN_MASK|
                (u32)XEMACPS_NWCTRL_HALTTX_MASK|
                (u32)XEMACPS_NWCTRL_LOOPEN_MASK);
    /* Clear the statistic registers, flush the packets in DPRAM*/
    RegVal |= (XEMACPS_NWCTRL_STATCLR_MASK|
                XEMACPS_NWCTRL_FLUSH_DPRAM_MASK);
    XEmacPs_WriteReg(BaseAddr,XEMACPS_NWCTRL_OFFSET,RegVal);
    /* Clear the interrupt status */
    XEmacPs_WriteReg(BaseAddr,XEMACPS_ISR_OFFSET,XEMACPS_IXR_ALL_MASK);
    /* Clear the tx status */
    XEmacPs_WriteReg(BaseAddr,XEMACPS_TXSR_OFFSET,(XEMACPS_TXSR_ERROR_MASK|
                                    (u32)XEMACPS_TXSR_TXCOMPL_MASK|
                                    (u32)XEMACPS_TXSR_TXGO_MASK));
    /* Clear the rx status */
    XEmacPs_WriteReg(BaseAddr,XEMACPS_RXSR_OFFSET,
                                XEMACPS_RXSR_FRAMERX_MASK);
    /* Clear the tx base address */
    XEmacPs_WriteReg(BaseAddr,XEMACPS_TXQBASE_OFFSET,0x0U);
    /* Clear the rx base address */
    XEmacPs_WriteReg(BaseAddr,XEMACPS_RXQBASE_OFFSET,0x0U);
    /* Update the network config register with reset value */
    XEmacPs_WriteReg(BaseAddr,XEMACPS_NWCFG_OFFSET,XEMACPS_NWCFG_RESET_MASK);
    /* Update the hash address registers with reset value */
    XEmacPs_WriteReg(BaseAddr,XEMACPS_HASHL_OFFSET,0x0U);
    XEmacPs_WriteReg(BaseAddr,XEMACPS_HASHH_OFFSET,0x0U);
}
/** @} */
