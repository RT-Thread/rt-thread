/******************************************************************************
* Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xemacps.c
* @addtogroup emacps_v3_11
* @{
*
* The XEmacPs driver. Functions in this file are the minimum required functions
* for this driver. See xemacps.h for a detailed description of the driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a wsy  01/10/10 First release
* 2.1  srt  07/15/14 Add support for Zynq Ultrascale Mp GEM specification and
*		      64-bit changes.
* 3.00 kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
* 3.0  hk   02/20/15 Added support for jumbo frames. Increase AHB burst.
*                    Disable extended mode. Perform all 64 bit changes under
*                    check for arch64.
* 3.1  hk   08/10/15 Update upper 32 bit tx and rx queue ptr registers
* 3.5  hk   08/14/17 Update cache coherency information of the interface in
*                    its config structure.
* 3.8  hk   09/17/18 Cleanup stale comments.
* 3.8  mus  11/05/18 Support 64 bit DMA addresses for Microblaze-X platform.
* 3.10 hk   05/16/19 Clear status registers properly in reset
* 3.11 sd   02/14/20 Add clock support
*
* </pre>
******************************************************************************/

/***************************** Include Files *********************************/

#include "xemacps.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

void XEmacPs_StubHandler(void);	/* Default handler routine */

/************************** Variable Definitions *****************************/


/*****************************************************************************/
/**
* Initialize a specific XEmacPs instance/driver. The initialization entails:
* - Initialize fields of the XEmacPs instance structure
* - Reset hardware and apply default options
* - Configure the DMA channels
*
* The PHY is setup independently from the device. Use the MII or whatever other
* interface may be present for setup.
*
* @param InstancePtr is a pointer to the instance to be worked on.
* @param CfgPtr is the device configuration structure containing required
*        hardware build data.
* @param EffectiveAddress is the base address of the device. If address
*        translation is not utilized, this parameter can be passed in using
*        CfgPtr->Config.BaseAddress to specify the physical base address.
*
* @return
* - XST_SUCCESS if initialization was successful
*
******************************************************************************/
LONG XEmacPs_CfgInitialize(XEmacPs *InstancePtr, XEmacPs_Config * CfgPtr,
			   UINTPTR EffectiveAddress)
{
	/* Verify arguments */
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(CfgPtr != NULL);

	/* Set device base address and ID */
	InstancePtr->Config.DeviceId = CfgPtr->DeviceId;
	InstancePtr->Config.BaseAddress = EffectiveAddress;
	InstancePtr->Config.IsCacheCoherent = CfgPtr->IsCacheCoherent;
#if defined  (XCLOCKING)
	InstancePtr->Config.RefClk = CfgPtr->RefClk;
#endif

	/* Set callbacks to an initial stub routine */
	InstancePtr->SendHandler = ((XEmacPs_Handler)((void*)XEmacPs_StubHandler));
	InstancePtr->RecvHandler = ((XEmacPs_Handler)(void*)XEmacPs_StubHandler);
	InstancePtr->ErrorHandler = ((XEmacPs_ErrHandler)(void*)XEmacPs_StubHandler);

	/* Reset the hardware and set default options */
	InstancePtr->IsReady = XIL_COMPONENT_IS_READY;
	XEmacPs_Reset(InstancePtr);

	return (LONG)(XST_SUCCESS);
}


/*****************************************************************************/
/**
* Start the Ethernet controller as follows:
*   - Enable transmitter if XTE_TRANSMIT_ENABLE_OPTION is set
*   - Enable receiver if XTE_RECEIVER_ENABLE_OPTION is set
*   - Start the SG DMA send and receive channels and enable the device
*     interrupt
*
* @param InstancePtr is a pointer to the instance to be worked on.
*
* @return N/A
*
* @note
* Hardware is configured with scatter-gather DMA, the driver expects to start
* the scatter-gather channels and expects that the user has previously set up
* the buffer descriptor lists.
*
* This function makes use of internal resources that are shared between the
* Start, Stop, and Set/ClearOptions functions. So if one task might be setting
* device options while another is trying to start the device, the user is
* required to provide protection of this shared data (typically using a
* semaphore).
*
* This function must not be preempted by an interrupt that may service the
* device.
*
******************************************************************************/
void XEmacPs_Start(XEmacPs *InstancePtr)
{
	u32 Reg;

	/* Assert bad arguments and conditions */
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

#if defined  (XCLOCKING)
	if (InstancePtr->IsStarted != (u32)XIL_COMPONENT_IS_STARTED) {
		Xil_ClockEnable(InstancePtr->Config.RefClk);
	}
#endif

	/* Start DMA */
	/* When starting the DMA channels, both transmit and receive sides
	 * need an initialized BD list.
	 */
	if (InstancePtr->Version == 2) {
		Xil_AssertVoid(InstancePtr->RxBdRing.BaseBdAddr != 0);
		Xil_AssertVoid(InstancePtr->TxBdRing.BaseBdAddr != 0);
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			   XEMACPS_RXQBASE_OFFSET,
			   InstancePtr->RxBdRing.BaseBdAddr);

	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			   XEMACPS_TXQBASE_OFFSET,
			   InstancePtr->TxBdRing.BaseBdAddr);
	}

	/* clear any existed int status */
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress, XEMACPS_ISR_OFFSET,
			   XEMACPS_IXR_ALL_MASK);

	/* Enable transmitter if not already enabled */
	if ((InstancePtr->Options & (u32)XEMACPS_TRANSMITTER_ENABLE_OPTION)!=0x00000000U) {
		Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					XEMACPS_NWCTRL_OFFSET);
		if ((!(Reg & XEMACPS_NWCTRL_TXEN_MASK))==TRUE) {
			XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
					   XEMACPS_NWCTRL_OFFSET,
				   Reg | (u32)XEMACPS_NWCTRL_TXEN_MASK);
		}
	}

	/* Enable receiver if not already enabled */
	if ((InstancePtr->Options & XEMACPS_RECEIVER_ENABLE_OPTION) != 0x00000000U) {
		Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					XEMACPS_NWCTRL_OFFSET);
		if ((!(Reg & XEMACPS_NWCTRL_RXEN_MASK))==TRUE) {
			XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
					   XEMACPS_NWCTRL_OFFSET,
				   Reg | (u32)XEMACPS_NWCTRL_RXEN_MASK);
		}
	}

        /* Enable TX and RX interrupts */
        XEmacPs_IntEnable(InstancePtr, (XEMACPS_IXR_TX_ERR_MASK |
	XEMACPS_IXR_RX_ERR_MASK | (u32)XEMACPS_IXR_FRAMERX_MASK |
	(u32)XEMACPS_IXR_TXCOMPL_MASK));

	/* Enable TX Q1 Interrupts */
	if (InstancePtr->Version > 2)
		XEmacPs_IntQ1Enable(InstancePtr, XEMACPS_INTQ1_IXR_ALL_MASK);

	/* Mark as started */
	InstancePtr->IsStarted = XIL_COMPONENT_IS_STARTED;

	return;
}


/*****************************************************************************/
/**
* Gracefully stop the Ethernet MAC as follows:
*   - Disable all interrupts from this device
*   - Stop DMA channels
*   - Disable the tansmitter and receiver
*
* Device options currently in effect are not changed.
*
* This function will disable all interrupts. Default interrupts settings that
* had been enabled will be restored when XEmacPs_Start() is called.
*
* @param InstancePtr is a pointer to the instance to be worked on.
*
* @note
* This function makes use of internal resources that are shared between the
* Start, Stop, SetOptions, and ClearOptions functions. So if one task might be
* setting device options while another is trying to start the device, the user
* is required to provide protection of this shared data (typically using a
* semaphore).
*
* Stopping the DMA channels causes this function to block until the DMA
* operation is complete.
*
******************************************************************************/
void XEmacPs_Stop(XEmacPs *InstancePtr)
{
	u32 Reg;

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	/* Disable all interrupts */
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress, XEMACPS_IDR_OFFSET,
			   XEMACPS_IXR_ALL_MASK);

	/* Disable the receiver & transmitter */
	Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				XEMACPS_NWCTRL_OFFSET);
	Reg &= (u32)(~XEMACPS_NWCTRL_RXEN_MASK);
	Reg &= (u32)(~XEMACPS_NWCTRL_TXEN_MASK);
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			   XEMACPS_NWCTRL_OFFSET, Reg);

	/* Mark as stopped */
	InstancePtr->IsStarted = 0U;
#if defined  (XCLOCKING)
	Xil_ClockDisable(InstancePtr->Config.RefClk);
#endif
}


/*****************************************************************************/
/**
* Perform a graceful reset of the Ethernet MAC. Resets the DMA channels, the
* transmitter, and the receiver.
*
* Steps to reset
* - Stops transmit and receive channels
* - Stops DMA
* - Configure transmit and receive buffer size to default
* - Clear transmit and receive status register and counters
* - Clear all interrupt sources
* - Clear phy (if there is any previously detected) address
* - Clear MAC addresses (1-4) as well as Type IDs and hash value
*
* All options are placed in their default state. Any frames in the
* descriptor lists will remain in the lists. The side effect of doing
* this is that after a reset and following a restart of the device, frames
* were in the list before the reset may be transmitted or received.
*
* The upper layer software is responsible for re-configuring (if necessary)
* and restarting the MAC after the reset. Note also that driver statistics
* are not cleared on reset. It is up to the upper layer software to clear the
* statistics if needed.
*
* When a reset is required, the driver notifies the upper layer software of
* this need through the ErrorHandler callback and specific status codes.
* The upper layer software is responsible for calling this Reset function
* and then re-configuring the device.
*
* @param InstancePtr is a pointer to the instance to be worked on.
*
******************************************************************************/
void XEmacPs_Reset(XEmacPs *InstancePtr)
{
	u32 Reg;
	u8 i;
	s8 EmacPs_zero_MAC[6] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	/* Stop the device and reset hardware */
	XEmacPs_Stop(InstancePtr);
	InstancePtr->Options = XEMACPS_DEFAULT_OPTIONS;

	InstancePtr->Version = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress, 0xFC);

	InstancePtr->Version = (InstancePtr->Version >> 16) & 0xFFF;

	InstancePtr->MaxMtuSize = XEMACPS_MTU;
	InstancePtr->MaxFrameSize = XEMACPS_MTU + XEMACPS_HDR_SIZE +
					XEMACPS_TRL_SIZE;
	InstancePtr->MaxVlanFrameSize = InstancePtr->MaxFrameSize +
					XEMACPS_HDR_VLAN_SIZE;
	InstancePtr->RxBufMask = XEMACPS_RXBUF_LEN_MASK;

	/* Setup hardware with default values */
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			XEMACPS_NWCTRL_OFFSET,
			(XEMACPS_NWCTRL_STATCLR_MASK |
			XEMACPS_NWCTRL_MDEN_MASK) &
			(u32)(~XEMACPS_NWCTRL_LOOPEN_MASK));

	Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
			XEMACPS_NWCFG_OFFSET);
	Reg &= XEMACPS_NWCFG_MDCCLKDIV_MASK;

	Reg = Reg | (u32)XEMACPS_NWCFG_100_MASK |
			(u32)XEMACPS_NWCFG_FDEN_MASK |
			(u32)XEMACPS_NWCFG_UCASTHASHEN_MASK;

	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
					XEMACPS_NWCFG_OFFSET, Reg);
	if (InstancePtr->Version > 2) {
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress, XEMACPS_NWCFG_OFFSET,
			(XEmacPs_ReadReg(InstancePtr->Config.BaseAddress, XEMACPS_NWCFG_OFFSET) |
				XEMACPS_NWCFG_DWIDTH_64_MASK));
	}

	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			XEMACPS_DMACR_OFFSET,
			(((((u32)XEMACPS_RX_BUF_SIZE / (u32)XEMACPS_RX_BUF_UNIT) +
				(((((u32)XEMACPS_RX_BUF_SIZE %
				(u32)XEMACPS_RX_BUF_UNIT))!=(u32)0) ? 1U : 0U)) <<
				(u32)(XEMACPS_DMACR_RXBUF_SHIFT)) &
				(u32)(XEMACPS_DMACR_RXBUF_MASK)) |
				(u32)XEMACPS_DMACR_RXSIZE_MASK |
				(u32)XEMACPS_DMACR_TXSIZE_MASK);


	if (InstancePtr->Version > 2) {
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress, XEMACPS_DMACR_OFFSET,
			(XEmacPs_ReadReg(InstancePtr->Config.BaseAddress, XEMACPS_DMACR_OFFSET) |
#if defined(__aarch64__) || defined(__arch64__)
			(u32)XEMACPS_DMACR_ADDR_WIDTH_64 |
#endif
			(u32)XEMACPS_DMACR_INCR16_AHB_BURST));
	}

	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			   XEMACPS_TXSR_OFFSET, XEMACPS_SR_ALL_MASK);

	XEmacPs_SetQueuePtr(InstancePtr, 0, 0x00U, (u16)XEMACPS_SEND);
	if (InstancePtr->Version > 2)
		XEmacPs_SetQueuePtr(InstancePtr, 0, 0x01U, (u16)XEMACPS_SEND);
	XEmacPs_SetQueuePtr(InstancePtr, 0, 0x00U, (u16)XEMACPS_RECV);

	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			   XEMACPS_RXSR_OFFSET, XEMACPS_SR_ALL_MASK);

	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress, XEMACPS_IDR_OFFSET,
			   XEMACPS_IXR_ALL_MASK);

	Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				XEMACPS_ISR_OFFSET);
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress, XEMACPS_ISR_OFFSET,
			   Reg);

	XEmacPs_ClearHash(InstancePtr);

	for (i = 1U; i < 5U; i++) {
		(void)XEmacPs_SetMacAddress(InstancePtr, EmacPs_zero_MAC, i);
		(void)XEmacPs_SetTypeIdCheck(InstancePtr, 0x00000000U, i);
	}

	/* clear all counters */
	for (i = 0U; i < (u8)((XEMACPS_LAST_OFFSET - XEMACPS_OCTTXL_OFFSET) / 4U);
	     i++) {
		(void)XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
                                   XEMACPS_OCTTXL_OFFSET + (u32)(((u32)i) * ((u32)4)));
	}

	/* Disable the receiver */
	Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				XEMACPS_NWCTRL_OFFSET);
	Reg &= (u32)(~XEMACPS_NWCTRL_RXEN_MASK);
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			   XEMACPS_NWCTRL_OFFSET, Reg);

	/* Sync default options with hardware but leave receiver and
         * transmitter disabled. They get enabled with XEmacPs_Start() if
	 * XEMACPS_TRANSMITTER_ENABLE_OPTION and
         * XEMACPS_RECEIVER_ENABLE_OPTION are set.
	 */
	(void)XEmacPs_SetOptions(InstancePtr, InstancePtr->Options &
			    ~((u32)XEMACPS_TRANSMITTER_ENABLE_OPTION |
			      (u32)XEMACPS_RECEIVER_ENABLE_OPTION));

	(void)XEmacPs_ClearOptions(InstancePtr, ~InstancePtr->Options);
}


/******************************************************************************/
/**
 * This is a stub for the asynchronous callbacks. The stub is here in case the
 * upper layer forgot to set the handler(s). On initialization, all handlers are
 * set to this callback. It is considered an error for this handler to be
 * invoked.
 *
 ******************************************************************************/
void XEmacPs_StubHandler(void)
{
	Xil_AssertVoidAlways();
}

/*****************************************************************************/
/**
* This function sets the start address of the transmit/receive buffer queue.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
* @param	QPtr is the address of the Queue to be written
* @param	QueueNum is the Buffer Queue Index
* @param	Direction indicates Transmit/Receive
*
* @note
* The buffer queue addresses has to be set before starting the transfer, so
* this function has to be called in prior to XEmacPs_Start()
*
******************************************************************************/
void XEmacPs_SetQueuePtr(XEmacPs *InstancePtr, UINTPTR QPtr, u8 QueueNum,
			 u16 Direction)
{
	/* Assert bad arguments and conditions */
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

        /* If already started, then there is nothing to do */
        if (InstancePtr->IsStarted == (u32)XIL_COMPONENT_IS_STARTED) {
                return;
        }

	if (QueueNum == 0x00U) {
		if (Direction == XEMACPS_SEND) {
			XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				XEMACPS_TXQBASE_OFFSET,
				(QPtr & ULONG64_LO_MASK));
		} else {
			XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				XEMACPS_RXQBASE_OFFSET,
				(QPtr & ULONG64_LO_MASK));
		}
	}
	 else {
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			XEMACPS_TXQ1BASE_OFFSET,
			(QPtr & ULONG64_LO_MASK));
	}
#ifdef __aarch64__
	if (Direction == XEMACPS_SEND) {
		/* Set the MSB of TX Queue start address */
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				XEMACPS_MSBBUF_TXQBASE_OFFSET,
				(u32)((QPtr & ULONG64_HI_MASK) >> 32U));
	} else {
		/* Set the MSB of RX Queue start address */
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				XEMACPS_MSBBUF_RXQBASE_OFFSET,
				(u32)((QPtr & ULONG64_HI_MASK) >> 32U));
	}
#endif
}
/** @} */
