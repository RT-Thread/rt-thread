/******************************************************************************
* Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xemacps_intr.c
* @addtogroup emacps_v3_11
* @{
*
* Functions in this file implement general purpose interrupt processing related
* functionality. See xemacps.h for a detailed description of the driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a wsy  01/10/10 First release
* 1.03a asa  01/24/13 Fix for CR #692702 which updates error handling for
*		      Rx errors. Under heavy Rx traffic, there will be a large
*		      number of errors related to receive buffer not available.
*		      Because of a HW bug (SI #692601), under such heavy errors,
*		      the Rx data path can become unresponsive. To reduce the
*		      probabilities for hitting this HW bug, the SW writes to
*		      bit 18 to flush a packet from Rx DPRAM immediately. The
*		      changes for it are done in the function
*		      XEmacPs_IntrHandler.
* 2.1   srt  07/15/14 Add support for Zynq Ultrascale Mp GEM specification
*		       and 64-bit changes.
* 3.0   kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
* 3.1   hk   07/27/15 Do not call error handler with '0' error code when
*                     there is no error. CR# 869403
* </pre>
******************************************************************************/

/***************************** Include Files *********************************/

#include "xemacps.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/


/************************** Variable Definitions *****************************/


/*****************************************************************************/
/**
 * Install an asynchronous handler function for the given HandlerType:
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 * @param HandlerType indicates what interrupt handler type is.
 *        XEMACPS_HANDLER_DMASEND, XEMACPS_HANDLER_DMARECV and
 *        XEMACPS_HANDLER_ERROR.
 * @param FuncPointer is the pointer to the callback function
 * @param CallBackRef is the upper layer callback reference passed back when
 *        when the callback function is invoked.
 *
 * @return
 *
 * None.
 *
 * @note
 * There is no assert on the CallBackRef since the driver doesn't know what
 * it is.
 *
 *****************************************************************************/
LONG XEmacPs_SetHandler(XEmacPs *InstancePtr, u32 HandlerType,
			void *FuncPointer, void *CallBackRef)
{
	LONG Status;
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(FuncPointer != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	switch (HandlerType) {
	case XEMACPS_HANDLER_DMASEND:
		Status = (LONG)(XST_SUCCESS);
		InstancePtr->SendHandler = ((XEmacPs_Handler)(void *)FuncPointer);
		InstancePtr->SendRef = CallBackRef;
		break;
	case XEMACPS_HANDLER_DMARECV:
		Status = (LONG)(XST_SUCCESS);
		InstancePtr->RecvHandler = ((XEmacPs_Handler)(void *)FuncPointer);
		InstancePtr->RecvRef = CallBackRef;
		break;
	case XEMACPS_HANDLER_ERROR:
		Status = (LONG)(XST_SUCCESS);
		InstancePtr->ErrorHandler = ((XEmacPs_ErrHandler)(void *)FuncPointer);
		InstancePtr->ErrorRef = CallBackRef;
		break;
	default:
		Status = (LONG)(XST_INVALID_PARAM);
		break;
	}
	return Status;
}

/*****************************************************************************/
/**
* Master interrupt handler for EMAC driver. This routine will query the
* status of the device, bump statistics, and invoke user callbacks.
*
* This routine must be connected to an interrupt controller using OS/BSP
* specific methods.
*
* @param XEmacPsPtr is a pointer to the XEMACPS instance that has caused the
*        interrupt.
*
******************************************************************************/
void XEmacPs_IntrHandler(void *XEmacPsPtr)
{
	u32 RegISR;
	u32 RegSR;
	u32 RegCtrl;
	u32 RegQ1ISR = 0U;
	XEmacPs *InstancePtr = (XEmacPs *) XEmacPsPtr;

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	/* This ISR will try to handle as many interrupts as it can in a single
	 * call. However, in most of the places where the user's error handler
         * is called, this ISR exits because it is expected that the user will
         * reset the device in nearly all instances.
	 */
	RegISR = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_ISR_OFFSET);

	/* Read Transmit Q1 ISR */

	if (InstancePtr->Version > 2)
		RegQ1ISR = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_INTQ1_STS_OFFSET);

	/* Clear the interrupt status register */
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress, XEMACPS_ISR_OFFSET,
			   RegISR);

	/* Receive complete interrupt */
	if ((RegISR & XEMACPS_IXR_FRAMERX_MASK) != 0x00000000U) {
		/* Clear RX status register RX complete indication but preserve
		 * error bits if there is any */
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_RXSR_OFFSET,
				   ((u32)XEMACPS_RXSR_FRAMERX_MASK |
				   (u32)XEMACPS_RXSR_BUFFNA_MASK));
		InstancePtr->RecvHandler(InstancePtr->RecvRef);
	}

	/* Transmit Q1 complete interrupt */
	if ((InstancePtr->Version > 2) &&
			((RegQ1ISR & XEMACPS_INTQ1SR_TXCOMPL_MASK) != 0x00000000U)) {
		/* Clear TX status register TX complete indication but preserve
		 * error bits if there is any */
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_INTQ1_STS_OFFSET,
				   XEMACPS_INTQ1SR_TXCOMPL_MASK);
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_TXSR_OFFSET,
				   ((u32)XEMACPS_TXSR_TXCOMPL_MASK |
				   (u32)XEMACPS_TXSR_USEDREAD_MASK));
		InstancePtr->SendHandler(InstancePtr->SendRef);
	}

	/* Transmit complete interrupt */
	if ((RegISR & XEMACPS_IXR_TXCOMPL_MASK) != 0x00000000U) {
		/* Clear TX status register TX complete indication but preserve
		 * error bits if there is any */
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_TXSR_OFFSET,
				   ((u32)XEMACPS_TXSR_TXCOMPL_MASK |
				   (u32)XEMACPS_TXSR_USEDREAD_MASK));
		InstancePtr->SendHandler(InstancePtr->SendRef);
	}

	/* Receive error conditions interrupt */
	if ((RegISR & XEMACPS_IXR_RX_ERR_MASK) != 0x00000000U) {
		/* Clear RX status register */
		RegSR = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					  XEMACPS_RXSR_OFFSET);
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_RXSR_OFFSET, RegSR);

		/* Fix for CR # 692702. Write to bit 18 of net_ctrl
		 * register to flush a packet out of Rx SRAM upon
		 * an error for receive buffer not available. */
		if ((RegISR & XEMACPS_IXR_RXUSED_MASK) != 0x00000000U) {
			RegCtrl =
			XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
						XEMACPS_NWCTRL_OFFSET);
			RegCtrl |= (u32)XEMACPS_NWCTRL_FLUSH_DPRAM_MASK;
			XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
					XEMACPS_NWCTRL_OFFSET, RegCtrl);
		}

		if(RegSR != 0) {
			InstancePtr->ErrorHandler(InstancePtr->ErrorRef,
						XEMACPS_RECV, RegSR);
		}
	}

        /* When XEMACPS_IXR_TXCOMPL_MASK is flagged, XEMACPS_IXR_TXUSED_MASK
         * will be asserted the same time.
         * Have to distinguish this bit to handle the real error condition.
         */
	/* Transmit Q1 error conditions interrupt */
        if ((InstancePtr->Version > 2) &&
			((RegQ1ISR & XEMACPS_INTQ1SR_TXERR_MASK) != 0x00000000U) &&
            ((RegQ1ISR & XEMACPS_INTQ1SR_TXCOMPL_MASK) != 0x00000000U)) {
			/* Clear Interrupt Q1 status register */
			XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_INTQ1_STS_OFFSET, RegQ1ISR);
			InstancePtr->ErrorHandler(InstancePtr->ErrorRef, XEMACPS_SEND,
					  RegQ1ISR);
	   }

	/* Transmit error conditions interrupt */
        if (((RegISR & XEMACPS_IXR_TX_ERR_MASK) != 0x00000000U) &&
            (!(RegISR & XEMACPS_IXR_TXCOMPL_MASK) != 0x00000000U)) {
		/* Clear TX status register */
		RegSR = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					  XEMACPS_TXSR_OFFSET);
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_TXSR_OFFSET, RegSR);
		InstancePtr->ErrorHandler(InstancePtr->ErrorRef, XEMACPS_SEND,
					  RegSR);
	}

}
/** @} */
