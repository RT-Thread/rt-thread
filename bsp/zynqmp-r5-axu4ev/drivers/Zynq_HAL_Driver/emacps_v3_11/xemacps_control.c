/******************************************************************************
* Copyright (C) 2009 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file xemacps_control.c
* @addtogroup emacps_v3_11
* @{
 *
 * Functions in this file implement general purpose command and control related
 * functionality. See xemacps.h for a detailed description of the driver.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- ---- -------- -------------------------------------------------------
 * 1.00a wsy  01/10/10 First release
 * 1.02a asa  11/05/12 Added a new API for deleting an entry from the HASH
 *					   register. Added a new API for setting the BURST length
 *					   in DMACR register.
 * 2.1   srt  07/15/14 Add support for Zynq Ultrascale Mp architecture.
 * 3.0   kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
 * 3.0   hk   02/20/15 Added support for jumbo frames.
 * 3.2   hk   02/22/16 Added SGMII support for Zynq Ultrascale+ MPSoC.
 * </pre>
 *****************************************************************************/

/***************************** Include Files *********************************/

#include "xemacps.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/


/************************** Variable Definitions *****************************/


/*****************************************************************************/
/**
 * Set the MAC address for this driver/device.  The address is a 48-bit value.
 * The device must be stopped before calling this function.
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 * @param AddressPtr is a pointer to a 6-byte MAC address.
 * @param Index is a index to which MAC (1-4) address.
 *
 * @return
 * - XST_SUCCESS if the MAC address was set successfully
 * - XST_DEVICE_IS_STARTED if the device has not yet been stopped
 *
 *****************************************************************************/
LONG XEmacPs_SetMacAddress(XEmacPs *InstancePtr, void *AddressPtr, u8 Index)
{
	u32 MacAddr;
	u8 *Aptr = (u8 *)(void *)AddressPtr;
	u8 IndexLoc = Index;
	LONG Status;
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(Aptr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid((IndexLoc <= (u8)XEMACPS_MAX_MAC_ADDR) && (IndexLoc > 0x00U));

	/* Be sure device has been stopped */
	if (InstancePtr->IsStarted == (u32)XIL_COMPONENT_IS_STARTED) {
		Status = (LONG)(XST_DEVICE_IS_STARTED);
	}
	else{
	/* Index ranges 1 to 4, for offset calculation is 0 to 3. */
		IndexLoc--;

	/* Set the MAC bits [31:0] in BOT */
		MacAddr = *(Aptr);
		MacAddr |= ((u32)(*(Aptr+1)) << 8U);
		MacAddr |= ((u32)(*(Aptr+2)) << 16U);
		MacAddr |= ((u32)(*(Aptr+3)) << 24U);
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				((u32)XEMACPS_LADDR1L_OFFSET + ((u32)IndexLoc * (u32)8)), MacAddr);

	/* There are reserved bits in TOP so don't affect them */
	MacAddr = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					((u32)XEMACPS_LADDR1H_OFFSET + ((u32)IndexLoc * (u32)8)));

		MacAddr &= (u32)(~XEMACPS_LADDR_MACH_MASK);

	/* Set MAC bits [47:32] in TOP */
		MacAddr |= (u32)(*(Aptr+4));
		MacAddr |= (u32)(*(Aptr+5)) << 8U;

	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				((u32)XEMACPS_LADDR1H_OFFSET + ((u32)IndexLoc * (u32)8)), MacAddr);

		Status = (LONG)(XST_SUCCESS);
	}
	return Status;
}


/*****************************************************************************/
/**
 * Get the MAC address for this driver/device.
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 * @param AddressPtr is an output parameter, and is a pointer to a buffer into
 *        which the current MAC address will be copied.
 * @param Index is a index to which MAC (1-4) address.
 *
 *****************************************************************************/
void XEmacPs_GetMacAddress(XEmacPs *InstancePtr, void *AddressPtr, u8 Index)
{
	u32 MacAddr;
	u8 *Aptr = (u8 *)(void *)AddressPtr;
	u8 IndexLoc = Index;
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(Aptr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);
	Xil_AssertVoid((IndexLoc <= (u8)XEMACPS_MAX_MAC_ADDR) && (IndexLoc > 0x00U));

	/* Index ranges 1 to 4, for offset calculation is 0 to 3. */
	IndexLoc--;

	MacAddr = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				    ((u32)XEMACPS_LADDR1L_OFFSET + ((u32)IndexLoc * (u32)8)));
	*Aptr = (u8) MacAddr;
	*(Aptr+1) = (u8) (MacAddr >> 8U);
	*(Aptr+2) = (u8) (MacAddr >> 16U);
	*(Aptr+3) = (u8) (MacAddr >> 24U);

	/* Read MAC bits [47:32] in TOP */
	MacAddr = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				    ((u32)XEMACPS_LADDR1H_OFFSET + ((u32)IndexLoc * (u32)8)));
	*(Aptr+4) = (u8) MacAddr;
	*(Aptr+5) = (u8) (MacAddr >> 8U);
}


/*****************************************************************************/
/**
 * Set 48-bit MAC addresses in hash table.
 * The device must be stopped before calling this function.
 *
 * The hash address register is 64 bits long and takes up two locations in
 * the memory map. The least significant bits are stored in hash register
 * bottom and the most significant bits in hash register top.
 *
 * The unicast hash enable and the multicast hash enable bits in the network
 * configuration register enable the reception of hash matched frames. The
 * destination address is reduced to a 6 bit index into the 64 bit hash
 * register using the following hash function. The hash function is an XOR
 * of every sixth bit of the destination address.
 *
 * <pre>
 * hash_index[05] = da[05]^da[11]^da[17]^da[23]^da[29]^da[35]^da[41]^da[47]
 * hash_index[04] = da[04]^da[10]^da[16]^da[22]^da[28]^da[34]^da[40]^da[46]
 * hash_index[03] = da[03]^da[09]^da[15]^da[21]^da[27]^da[33]^da[39]^da[45]
 * hash_index[02] = da[02]^da[08]^da[14]^da[20]^da[26]^da[32]^da[38]^da[44]
 * hash_index[01] = da[01]^da[07]^da[13]^da[19]^da[25]^da[31]^da[37]^da[43]
 * hash_index[00] = da[00]^da[06]^da[12]^da[18]^da[24]^da[30]^da[36]^da[42]
 * </pre>
 *
 * da[0] represents the least significant bit of the first byte received,
 * that is, the multicast/unicast indicator, and da[47] represents the most
 * significant bit of the last byte received.
 *
 * If the hash index points to a bit that is set in the hash register then
 * the frame will be matched according to whether the frame is multicast
 * or unicast.
 *
 * A multicast match will be signaled if the multicast hash enable bit is
 * set, da[0] is logic 1 and the hash index points to a bit set in the hash
 * register.
 *
 * A unicast match will be signaled if the unicast hash enable bit is set,
 * da[0] is logic 0 and the hash index points to a bit set in the hash
 * register.
 *
 * To receive all multicast frames, the hash register should be set with
 * all ones and the multicast hash enable bit should be set in the network
 * configuration register.
 *
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 * @param AddressPtr is a pointer to a 6-byte MAC address.
 *
 * @return
 * - XST_SUCCESS if the HASH MAC address was set successfully
 * - XST_DEVICE_IS_STARTED if the device has not yet been stopped
 * - XST_INVALID_PARAM if the HASH MAC address passed in does not meet
 *   requirement after calculation
 *
 * @note
 * Having Aptr be unsigned type prevents the following operations from sign
 * extending.
 *****************************************************************************/
LONG XEmacPs_SetHash(XEmacPs *InstancePtr, void *AddressPtr)
{
	u32 HashAddr;
	u8 *Aptr = (u8 *)(void *)AddressPtr;
	u8 Temp1, Temp2, Temp3, Temp4, Temp5, Temp6, Temp7, Temp8;
	u32 Result;
	LONG Status;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(AddressPtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	/* Be sure device has been stopped */
	if (InstancePtr->IsStarted == (u32)XIL_COMPONENT_IS_STARTED) {
		Status = (LONG)(XST_DEVICE_IS_STARTED);
	} else {
		Temp1 = (*(Aptr+0)) & 0x3FU;
		Temp2 = ((*(Aptr+0) >> 6U) & 0x03U) | ((*(Aptr+1) & 0x0FU) << 2U);

		Temp3 = ((*(Aptr+1) >> 4U) & 0x0FU) | ((*(Aptr+2) & 0x3U) << 4U);
		Temp4 = ((*(Aptr+2) >> 2U) & 0x3FU);
		Temp5 =   (*(Aptr+3)) & 0x3FU;
		Temp6 = ((*(Aptr+3) >> 6U) & 0x03U) | ((*(Aptr+4) & 0x0FU) << 2U);
		Temp7 = ((*(Aptr+4) >> 4U) & 0x0FU) | ((*(Aptr+5) & 0x03U) << 4U);
		Temp8 = ((*(Aptr+5) >> 2U) & 0x3FU);

		Result = (u32)((u32)Temp1 ^ (u32)Temp2 ^ (u32)Temp3 ^ (u32)Temp4 ^
				(u32)Temp5 ^ (u32)Temp6 ^ (u32)Temp7 ^ (u32)Temp8);

		if (Result >= (u32)XEMACPS_MAX_HASH_BITS) {
			Status = (LONG)(XST_INVALID_PARAM);
		} else {

			if (Result < (u32)32) {
		HashAddr = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				XEMACPS_HASHL_OFFSET);
				HashAddr |= (u32)(0x00000001U << Result);
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			XEMACPS_HASHL_OFFSET, HashAddr);
	} else {
		HashAddr = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				XEMACPS_HASHH_OFFSET);
				HashAddr |= (u32)(0x00000001U << (u32)(Result - (u32)32));
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			XEMACPS_HASHH_OFFSET, HashAddr);
	}
			Status = (LONG)(XST_SUCCESS);
		}
	}
	return Status;
}

/*****************************************************************************/
/**
 * Delete 48-bit MAC addresses in hash table.
 * The device must be stopped before calling this function.
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 * @param AddressPtr is a pointer to a 6-byte MAC address.
 *
 * @return
 * - XST_SUCCESS if the HASH MAC address was deleted successfully
 * - XST_DEVICE_IS_STARTED if the device has not yet been stopped
 * - XST_INVALID_PARAM if the HASH MAC address passed in does not meet
 *   requirement after calculation
 *
 * @note
 * Having Aptr be unsigned type prevents the following operations from sign
 * extending.
 *****************************************************************************/
LONG XEmacPs_DeleteHash(XEmacPs *InstancePtr, void *AddressPtr)
{
	u32 HashAddr;
	u8 *Aptr = (u8 *)(void *)AddressPtr;
	u8 Temp1, Temp2, Temp3, Temp4, Temp5, Temp6, Temp7, Temp8;
	u32 Result;
	LONG Status;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(Aptr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	/* Be sure device has been stopped */
	if (InstancePtr->IsStarted == (u32)XIL_COMPONENT_IS_STARTED) {
		Status = (LONG)(XST_DEVICE_IS_STARTED);
	} else {
		Temp1 = (*(Aptr+0)) & 0x3FU;
		Temp2 = ((*(Aptr+0) >> 6U) & 0x03U) | ((*(Aptr+1) & 0x0FU) << 2U);
		Temp3 = ((*(Aptr+1) >> 4U) & 0x0FU) | ((*(Aptr+2) & 0x03U) << 4U);
		Temp4 = ((*(Aptr+2) >> 2U) & 0x3FU);
		Temp5 =   (*(Aptr+3)) & 0x3FU;
		Temp6 = ((*(Aptr+3) >> 6U) & 0x03U) | ((*(Aptr+4) & 0x0FU) << 2U);
		Temp7 = ((*(Aptr+4) >> 4U) & 0x0FU) | ((*(Aptr+5) & 0x03U) << 4U);
		Temp8 = ((*(Aptr+5) >> 2U) & 0x3FU);

		Result = (u32)((u32)Temp1 ^ (u32)Temp2 ^ (u32)Temp3 ^ (u32)Temp4 ^
					(u32)Temp5 ^ (u32)Temp6 ^ (u32)Temp7 ^ (u32)Temp8);

		if (Result >= (u32)(XEMACPS_MAX_HASH_BITS)) {
			Status =  (LONG)(XST_INVALID_PARAM);
		} else {
			if (Result < (u32)32) {
		HashAddr = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				XEMACPS_HASHL_OFFSET);
				HashAddr &= (u32)(~(0x00000001U << Result));
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				XEMACPS_HASHL_OFFSET, HashAddr);
	} else {
		HashAddr = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				XEMACPS_HASHH_OFFSET);
				HashAddr &= (u32)(~(0x00000001U << (u32)(Result - (u32)32)));
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			XEMACPS_HASHH_OFFSET, HashAddr);
	}
			Status = (LONG)(XST_SUCCESS);
		}
	}
	return Status;
}
/*****************************************************************************/
/**
 * Clear the Hash registers for the mac address pointed by AddressPtr.
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 *
 *****************************************************************************/
void XEmacPs_ClearHash(XEmacPs *InstancePtr)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				    XEMACPS_HASHL_OFFSET, 0x0U);

	/* write bits [63:32] in TOP */
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				    XEMACPS_HASHH_OFFSET, 0x0U);
}


/*****************************************************************************/
/**
 * Get the Hash address for this driver/device.
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 * @param AddressPtr is an output parameter, and is a pointer to a buffer into
 *        which the current HASH MAC address will be copied.
 *
 *****************************************************************************/
void XEmacPs_GetHash(XEmacPs *InstancePtr, void *AddressPtr)
{
	u32 *Aptr = (u32 *)(void *)AddressPtr;

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(AddressPtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	*(Aptr+0) = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				    XEMACPS_HASHL_OFFSET);

	/* Read Hash bits [63:32] in TOP */
	*(Aptr+1) = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				    XEMACPS_HASHH_OFFSET);
}


/*****************************************************************************/
/**
 * Set the Type ID match for this driver/device.  The register is a 32-bit
 * value. The device must be stopped before calling this function.
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 * @param Id_Check is type ID to be configured.
 * @param Index is a index to which Type ID (1-4).
 *
 * @return
 * - XST_SUCCESS if the MAC address was set successfully
 * - XST_DEVICE_IS_STARTED if the device has not yet been stopped
 *
 *****************************************************************************/
LONG XEmacPs_SetTypeIdCheck(XEmacPs *InstancePtr, u32 Id_Check, u8 Index)
{
	u8 IndexLoc = Index;
	LONG Status;
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid((IndexLoc <= (u8)XEMACPS_MAX_TYPE_ID) && (IndexLoc > 0x00U));

	/* Be sure device has been stopped */
	if (InstancePtr->IsStarted == (u32)XIL_COMPONENT_IS_STARTED) {
		Status = (LONG)(XST_DEVICE_IS_STARTED);
	} else {

	/* Index ranges 1 to 4, for offset calculation is 0 to 3. */
		IndexLoc--;

	/* Set the ID bits in MATCHx register */
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   ((u32)XEMACPS_MATCH1_OFFSET + ((u32)IndexLoc * (u32)4)), Id_Check);

		Status = (LONG)(XST_SUCCESS);
	}
	return Status;
}

/*****************************************************************************/
/**
 * Set options for the driver/device. The driver should be stopped with
 * XEmacPs_Stop() before changing options.
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 * @param Options are the options to set. Multiple options can be set by OR'ing
 *        XTE_*_OPTIONS constants together. Options not specified are not
 *        affected.
 *
 * @return
 * - XST_SUCCESS if the options were set successfully
 * - XST_DEVICE_IS_STARTED if the device has not yet been stopped
 *
 * @note
 * See xemacps.h for a description of the available options.
 *
 *****************************************************************************/
LONG XEmacPs_SetOptions(XEmacPs *InstancePtr, u32 Options)
{
	u32 Reg;		/* Generic register contents */
	u32 RegNetCfg;		/* Reflects original contents of NET_CONFIG */
	u32 RegNewNetCfg;	/* Reflects new contents of NET_CONFIG */
	LONG Status;
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	/* Be sure device has been stopped */
	if (InstancePtr->IsStarted == (u32)XIL_COMPONENT_IS_STARTED) {
		Status = (LONG)(XST_DEVICE_IS_STARTED);
	} else {

	/* Many of these options will change the NET_CONFIG registers.
	 * To reduce the amount of IO to the device, group these options here
	 * and change them all at once.
	 */

	/* Grab current register contents */
	RegNetCfg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				      XEMACPS_NWCFG_OFFSET);
	RegNewNetCfg = RegNetCfg;

	/*
	 * It is configured to max 1536.
	 */
		if ((Options & XEMACPS_FRAME1536_OPTION) != 0x00000000U) {
		RegNewNetCfg |= (XEMACPS_NWCFG_1536RXEN_MASK);
	}

	/* Turn on VLAN packet only, only VLAN tagged will be accepted */
		if ((Options & XEMACPS_VLAN_OPTION) != 0x00000000U) {
		RegNewNetCfg |= XEMACPS_NWCFG_NVLANDISC_MASK;
	}

	/* Turn on FCS stripping on receive packets */
		if ((Options & XEMACPS_FCS_STRIP_OPTION) != 0x00000000U) {
		RegNewNetCfg |= XEMACPS_NWCFG_FCSREM_MASK;
	}

	/* Turn on length/type field checking on receive packets */
		if ((Options & XEMACPS_LENTYPE_ERR_OPTION) != 0x00000000U) {
			RegNewNetCfg |= XEMACPS_NWCFG_LENERRDSCRD_MASK;
	}

	/* Turn on flow control */
		if ((Options & XEMACPS_FLOW_CONTROL_OPTION) != 0x00000000U) {
		RegNewNetCfg |= XEMACPS_NWCFG_PAUSEEN_MASK;
	}

	/* Turn on promiscuous frame filtering (all frames are received) */
		if ((Options & XEMACPS_PROMISC_OPTION) != 0x00000000U) {
		RegNewNetCfg |= XEMACPS_NWCFG_COPYALLEN_MASK;
	}

	/* Allow broadcast address reception */
		if ((Options & XEMACPS_BROADCAST_OPTION) != 0x00000000U) {
			RegNewNetCfg &= (u32)(~XEMACPS_NWCFG_BCASTDI_MASK);
	}

	/* Allow multicast address filtering */
		if ((Options & XEMACPS_MULTICAST_OPTION) != 0x00000000U) {
		RegNewNetCfg |= XEMACPS_NWCFG_MCASTHASHEN_MASK;
	}

	/* enable RX checksum offload */
		if ((Options & XEMACPS_RX_CHKSUM_ENABLE_OPTION) != 0x00000000U) {
		RegNewNetCfg |= XEMACPS_NWCFG_RXCHKSUMEN_MASK;
	}

	/* Enable jumbo frames */
	if (((Options & XEMACPS_JUMBO_ENABLE_OPTION) != 0x00000000U) &&
		(InstancePtr->Version > 2)) {
		RegNewNetCfg |= XEMACPS_NWCFG_JUMBO_MASK;
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			XEMACPS_JUMBOMAXLEN_OFFSET, XEMACPS_RX_BUF_SIZE_JUMBO);
		Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				      XEMACPS_DMACR_OFFSET);
		Reg &= ~XEMACPS_DMACR_RXBUF_MASK;
		Reg |= (((((u32)XEMACPS_RX_BUF_SIZE_JUMBO / (u32)XEMACPS_RX_BUF_UNIT) +
			(((((u32)XEMACPS_RX_BUF_SIZE_JUMBO %
			(u32)XEMACPS_RX_BUF_UNIT))!=(u32)0) ? 1U : 0U)) <<
			(u32)(XEMACPS_DMACR_RXBUF_SHIFT)) &
			(u32)(XEMACPS_DMACR_RXBUF_MASK));
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			XEMACPS_DMACR_OFFSET, Reg);
		InstancePtr->MaxMtuSize = XEMACPS_MTU_JUMBO;
		InstancePtr->MaxFrameSize = XEMACPS_MTU_JUMBO +
					XEMACPS_HDR_SIZE + XEMACPS_TRL_SIZE;
		InstancePtr->MaxVlanFrameSize = InstancePtr->MaxFrameSize +
					XEMACPS_HDR_VLAN_SIZE;
		InstancePtr->RxBufMask = XEMACPS_RXBUF_LEN_JUMBO_MASK;
	}

	if (((Options & XEMACPS_SGMII_ENABLE_OPTION) != 0x00000000U) &&
		(InstancePtr->Version > 2)) {
		RegNewNetCfg |= (XEMACPS_NWCFG_SGMIIEN_MASK |
						XEMACPS_NWCFG_PCSSEL_MASK);
	}

	/* Officially change the NET_CONFIG registers if it needs to be
	 * modified.
	 */
	if (RegNetCfg != RegNewNetCfg) {
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_NWCFG_OFFSET, RegNewNetCfg);
	}

	/* Enable TX checksum offload */
		if ((Options & XEMACPS_TX_CHKSUM_ENABLE_OPTION) != 0x00000000U) {
		Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					XEMACPS_DMACR_OFFSET);
		Reg |= XEMACPS_DMACR_TCPCKSUM_MASK;
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
					 XEMACPS_DMACR_OFFSET, Reg);
	}

	/* Enable transmitter */
		if ((Options & XEMACPS_TRANSMITTER_ENABLE_OPTION) != 0x00000000U) {
		Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					XEMACPS_NWCTRL_OFFSET);
		Reg |= XEMACPS_NWCTRL_TXEN_MASK;
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_NWCTRL_OFFSET, Reg);
	}

	/* Enable receiver */
		if ((Options & XEMACPS_RECEIVER_ENABLE_OPTION) != 0x00000000U) {
		Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					XEMACPS_NWCTRL_OFFSET);
		Reg |= XEMACPS_NWCTRL_RXEN_MASK;
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_NWCTRL_OFFSET, Reg);
	}

	/* The remaining options not handled here are managed elsewhere in the
	 * driver. No register modifications are needed at this time. Reflecting
	 * the option in InstancePtr->Options is good enough for now.
	 */

	/* Set options word to its new value */
	InstancePtr->Options |= Options;

		Status = (LONG)(XST_SUCCESS);
	}
	return Status;
}


/*****************************************************************************/
/**
 * Clear options for the driver/device
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 * @param Options are the options to clear. Multiple options can be cleared by
 *        OR'ing XEMACPS_*_OPTIONS constants together. Options not specified
 *        are not affected.
 *
 * @return
 * - XST_SUCCESS if the options were set successfully
 * - XST_DEVICE_IS_STARTED if the device has not yet been stopped
 *
 * @note
 * See xemacps.h for a description of the available options.
 *
 *****************************************************************************/
LONG XEmacPs_ClearOptions(XEmacPs *InstancePtr, u32 Options)
{
	u32 Reg;		/* Generic */
	u32 RegNetCfg;		/* Reflects original contents of NET_CONFIG */
	u32 RegNewNetCfg;	/* Reflects new contents of NET_CONFIG */
	LONG Status;
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	/* Be sure device has been stopped */
	if (InstancePtr->IsStarted == (u32)XIL_COMPONENT_IS_STARTED) {
		Status = (LONG)(XST_DEVICE_IS_STARTED);
	} else {

	/* Many of these options will change the NET_CONFIG registers.
	 * To reduce the amount of IO to the device, group these options here
	 * and change them all at once.
	 */

	/* Grab current register contents */
	RegNetCfg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				      XEMACPS_NWCFG_OFFSET);
	RegNewNetCfg = RegNetCfg;

	/* There is only RX configuration!?
	 * It is configured in two different length, up to 1536 and 10240 bytes
	 */
		if ((Options & XEMACPS_FRAME1536_OPTION) != 0x00000000U) {
			RegNewNetCfg &= (u32)(~XEMACPS_NWCFG_1536RXEN_MASK);
	}

	/* Turn off VLAN packet only */
		if ((Options & XEMACPS_VLAN_OPTION) != 0x00000000U) {
			RegNewNetCfg &= (u32)(~XEMACPS_NWCFG_NVLANDISC_MASK);
	}

	/* Turn off FCS stripping on receive packets */
		if ((Options & XEMACPS_FCS_STRIP_OPTION) != 0x00000000U) {
			RegNewNetCfg &= (u32)(~XEMACPS_NWCFG_FCSREM_MASK);
	}

	/* Turn off length/type field checking on receive packets */
		if ((Options & XEMACPS_LENTYPE_ERR_OPTION) != 0x00000000U) {
			RegNewNetCfg &= (u32)(~XEMACPS_NWCFG_LENERRDSCRD_MASK);
	}

	/* Turn off flow control */
		if ((Options & XEMACPS_FLOW_CONTROL_OPTION) != 0x00000000U) {
			RegNewNetCfg &= (u32)(~XEMACPS_NWCFG_PAUSEEN_MASK);
	}

	/* Turn off promiscuous frame filtering (all frames are received) */
		if ((Options & XEMACPS_PROMISC_OPTION) != 0x00000000U) {
			RegNewNetCfg &= (u32)(~XEMACPS_NWCFG_COPYALLEN_MASK);
	}

	/* Disallow broadcast address filtering => broadcast reception */
		if ((Options & XEMACPS_BROADCAST_OPTION) != 0x00000000U) {
		RegNewNetCfg |= XEMACPS_NWCFG_BCASTDI_MASK;
	}

	/* Disallow multicast address filtering */
		if ((Options & XEMACPS_MULTICAST_OPTION) != 0x00000000U) {
			RegNewNetCfg &= (u32)(~XEMACPS_NWCFG_MCASTHASHEN_MASK);
	}

	/* Disable RX checksum offload */
		if ((Options & XEMACPS_RX_CHKSUM_ENABLE_OPTION) != 0x00000000U) {
			RegNewNetCfg &= (u32)(~XEMACPS_NWCFG_RXCHKSUMEN_MASK);
	}

	/* Disable jumbo frames */
	if (((Options & XEMACPS_JUMBO_ENABLE_OPTION) != 0x00000000U) &&
		(InstancePtr->Version > 2)) {
		RegNewNetCfg &= (u32)(~XEMACPS_NWCFG_JUMBO_MASK);
		Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				      XEMACPS_DMACR_OFFSET);
		Reg &= ~XEMACPS_DMACR_RXBUF_MASK;
		Reg |= (((((u32)XEMACPS_RX_BUF_SIZE / (u32)XEMACPS_RX_BUF_UNIT) +
			(((((u32)XEMACPS_RX_BUF_SIZE %
			(u32)XEMACPS_RX_BUF_UNIT))!=(u32)0) ? 1U : 0U)) <<
			(u32)(XEMACPS_DMACR_RXBUF_SHIFT)) &
			(u32)(XEMACPS_DMACR_RXBUF_MASK));
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			XEMACPS_DMACR_OFFSET, Reg);
		InstancePtr->MaxMtuSize = XEMACPS_MTU;
		InstancePtr->MaxFrameSize = XEMACPS_MTU +
					XEMACPS_HDR_SIZE + XEMACPS_TRL_SIZE;
		InstancePtr->MaxVlanFrameSize = InstancePtr->MaxFrameSize +
					XEMACPS_HDR_VLAN_SIZE;
		InstancePtr->RxBufMask = XEMACPS_RXBUF_LEN_MASK;
	}

	if (((Options & XEMACPS_SGMII_ENABLE_OPTION) != 0x00000000U) &&
		(InstancePtr->Version > 2)) {
		RegNewNetCfg &= (u32)(~(XEMACPS_NWCFG_SGMIIEN_MASK |
						XEMACPS_NWCFG_PCSSEL_MASK));
	}

	/* Officially change the NET_CONFIG registers if it needs to be
	 * modified.
	 */
	if (RegNetCfg != RegNewNetCfg) {
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_NWCFG_OFFSET, RegNewNetCfg);
	}

	/* Disable TX checksum offload */
		if ((Options & XEMACPS_TX_CHKSUM_ENABLE_OPTION) != 0x00000000U) {
		Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					XEMACPS_DMACR_OFFSET);
			Reg &= (u32)(~XEMACPS_DMACR_TCPCKSUM_MASK);
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
					 XEMACPS_DMACR_OFFSET, Reg);
	}

	/* Disable transmitter */
		if ((Options & XEMACPS_TRANSMITTER_ENABLE_OPTION) != 0x00000000U) {
		Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					XEMACPS_NWCTRL_OFFSET);
			Reg &= (u32)(~XEMACPS_NWCTRL_TXEN_MASK);
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_NWCTRL_OFFSET, Reg);
	}

	/* Disable receiver */
		if ((Options & XEMACPS_RECEIVER_ENABLE_OPTION) != 0x00000000U) {
		Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					XEMACPS_NWCTRL_OFFSET);
			Reg &= (u32)(~XEMACPS_NWCTRL_RXEN_MASK);
		XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
				   XEMACPS_NWCTRL_OFFSET, Reg);
	}

	/* The remaining options not handled here are managed elsewhere in the
	 * driver. No register modifications are needed at this time. Reflecting
	 * option in InstancePtr->Options is good enough for now.
	 */

	/* Set options word to its new value */
	InstancePtr->Options &= ~Options;

		Status = (LONG)(XST_SUCCESS);
	}
	return Status;
}


/*****************************************************************************/
/**
 * Get current option settings
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 *
 * @return
 * A bitmask of XTE_*_OPTION constants. Any bit set to 1 is to be interpreted
 * as a set option.
 *
 * @note
 * See xemacps.h for a description of the available options.
 *
 *****************************************************************************/
u32 XEmacPs_GetOptions(XEmacPs *InstancePtr)
{
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	return (InstancePtr->Options);
}


/*****************************************************************************/
/**
 * Send a pause packet
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 *
 * @return
 * - XST_SUCCESS if pause frame transmission was initiated
 * - XST_DEVICE_IS_STOPPED if the device has not been started.
 *
 *****************************************************************************/
LONG XEmacPs_SendPausePacket(XEmacPs *InstancePtr)
{
	u32 Reg;
	LONG Status;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	/* Make sure device is ready for this operation */
	if (InstancePtr->IsStarted != (u32)XIL_COMPONENT_IS_STARTED) {
		Status = (LONG)(XST_DEVICE_IS_STOPPED);
	} else {
	/* Send flow control frame */
	Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				XEMACPS_NWCTRL_OFFSET);
	Reg |= XEMACPS_NWCTRL_PAUSETX_MASK;
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			   XEMACPS_NWCTRL_OFFSET, Reg);
		Status = (LONG)(XST_SUCCESS);
	}
	return Status;
}

/*****************************************************************************/
/**
 * XEmacPs_GetOperatingSpeed gets the current operating link speed. This may
 * be the value set by XEmacPs_SetOperatingSpeed() or a hardware default.
 *
 * @param InstancePtr references the TEMAC channel on which to operate.
 *
 * @return XEmacPs_GetOperatingSpeed returns the link speed in units of
 *         megabits per second.
 *
 * @note
 *
 *****************************************************************************/
u16 XEmacPs_GetOperatingSpeed(XEmacPs *InstancePtr)
{
	u32 Reg;
	u16 Status;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);

	Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
			XEMACPS_NWCFG_OFFSET);

	if ((Reg & XEMACPS_NWCFG_1000_MASK) != 0x00000000U) {
		Status = (u16)(1000);
	} else {
		if ((Reg & XEMACPS_NWCFG_100_MASK) != 0x00000000U) {
			Status = (u16)(100);
		} else {
			Status = (u16)(10);
		}
	}
	return Status;
}


/*****************************************************************************/
/**
 * XEmacPs_SetOperatingSpeed sets the current operating link speed. For any
 * traffic to be passed, this speed must match the current MII/GMII/SGMII/RGMII
 * link speed.
 *
 * @param InstancePtr references the TEMAC channel on which to operate.
 * @param Speed is the speed to set in units of Mbps. Valid values are 10, 100,
 *        or 1000. XEmacPs_SetOperatingSpeed ignores invalid values.
 *
 * @note
 *
 *****************************************************************************/
void XEmacPs_SetOperatingSpeed(XEmacPs *InstancePtr, u16 Speed)
{
        u32 Reg;
        Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);
    Xil_AssertVoid((Speed == (u16)10) || (Speed == (u16)100) || (Speed == (u16)1000));

        Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
			XEMACPS_NWCFG_OFFSET);
	Reg &= (u32)(~(XEMACPS_NWCFG_1000_MASK | XEMACPS_NWCFG_100_MASK));

	switch (Speed) {
		case (u16)10:
                break;

        case (u16)100:
                Reg |= XEMACPS_NWCFG_100_MASK;
                break;

        case (u16)1000:
                Reg |= XEMACPS_NWCFG_1000_MASK;
                break;
    }

        /* Set register and return */
        XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
                XEMACPS_NWCFG_OFFSET, Reg);
}


/*****************************************************************************/
/**
 * Set the MDIO clock divisor.
 *
 * Calculating the divisor:
 *
 * <pre>
 *              f[HOSTCLK]
 *   f[MDC] = -----------------
 *            (1 + Divisor) * 2
 * </pre>
 *
 * where f[HOSTCLK] is the bus clock frequency in MHz, and f[MDC] is the
 * MDIO clock frequency in MHz to the PHY. Typically, f[MDC] should not
 * exceed 2.5 MHz. Some PHYs can tolerate faster speeds which means faster
 * access. Here is the table to show values to generate MDC,
 *
 * <pre>
 * 000 : divide pclk by   8 (pclk up to  20 MHz)
 * 001 : divide pclk by  16 (pclk up to  40 MHz)
 * 010 : divide pclk by  32 (pclk up to  80 MHz)
 * 011 : divide pclk by  48 (pclk up to 120 MHz)
 * 100 : divide pclk by  64 (pclk up to 160 MHz)
 * 101 : divide pclk by  96 (pclk up to 240 MHz)
 * 110 : divide pclk by 128 (pclk up to 320 MHz)
 * 111 : divide pclk by 224 (pclk up to 540 MHz)
 * </pre>
 *
 * @param InstancePtr is a pointer to the instance to be worked on.
 * @param Divisor is the divisor to set. Range is 0b000 to 0b111.
 *
 *****************************************************************************/
void XEmacPs_SetMdioDivisor(XEmacPs *InstancePtr, XEmacPs_MdcDiv Divisor)
{
	u32 Reg;
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == (u32)XIL_COMPONENT_IS_READY);
	Xil_AssertVoid(Divisor <= (XEmacPs_MdcDiv)0x7); /* only last three bits are valid */

	Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				XEMACPS_NWCFG_OFFSET);
	/* clear these three bits, could be done with mask */
	Reg &= (u32)(~XEMACPS_NWCFG_MDCCLKDIV_MASK);

	Reg |= ((u32)Divisor << XEMACPS_NWCFG_MDC_SHIFT_MASK);

	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			   XEMACPS_NWCFG_OFFSET, Reg);
}


/*****************************************************************************/
/**
* Read the current value of the PHY register indicated by the PhyAddress and
* the RegisterNum parameters. The MAC provides the driver with the ability to
* talk to a PHY that adheres to the Media Independent Interface (MII) as
* defined in the IEEE 802.3 standard.
*
* Prior to PHY access with this function, the user should have setup the MDIO
* clock with XEmacPs_SetMdioDivisor().
*
* @param InstancePtr is a pointer to the XEmacPs instance to be worked on.
* @param PhyAddress is the address of the PHY to be read (supports multiple
*        PHYs)
* @param RegisterNum is the register number, 0-31, of the specific PHY register
*        to read
* @param PhyDataPtr is an output parameter, and points to a 16-bit buffer into
*        which the current value of the register will be copied.
*
* @return
*
* - XST_SUCCESS if the PHY was read from successfully
* - XST_EMAC_MII_BUSY if there is another PHY operation in progress
*
* @note
*
* This function is not thread-safe. The user must provide mutually exclusive
* access to this function if there are to be multiple threads that can call it.
*
* There is the possibility that this function will not return if the hardware
* is broken (i.e., it never sets the status bit indicating that the read is
* done). If this is of concern to the user, the user should provide a mechanism
* suitable to their needs for recovery.
*
* For the duration of this function, all host interface reads and writes are
* blocked to the current XEmacPs instance.
*
******************************************************************************/
LONG XEmacPs_PhyRead(XEmacPs *InstancePtr, u32 PhyAddress,
		     u32 RegisterNum, u16 *PhyDataPtr)
{
	u32 Mgtcr;
	volatile u32 Ipisr;
	u32 IpReadTemp;
	LONG Status;

	Xil_AssertNonvoid(InstancePtr != NULL);

	/* Make sure no other PHY operation is currently in progress */
	if ((!(XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				XEMACPS_NWSR_OFFSET) &
	      XEMACPS_NWSR_MDIOIDLE_MASK))==TRUE) {
		Status = (LONG)(XST_EMAC_MII_BUSY);
	} else {

	/* Construct Mgtcr mask for the operation */
	Mgtcr = XEMACPS_PHYMNTNC_OP_MASK | XEMACPS_PHYMNTNC_OP_R_MASK |
			(PhyAddress << XEMACPS_PHYMNTNC_PHAD_SHFT_MSK) |
			(RegisterNum << XEMACPS_PHYMNTNC_PREG_SHFT_MSK);

	/* Write Mgtcr and wait for completion */
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			   XEMACPS_PHYMNTNC_OFFSET, Mgtcr);

	do {
		Ipisr = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					  XEMACPS_NWSR_OFFSET);
			IpReadTemp = Ipisr;
		} while ((IpReadTemp & XEMACPS_NWSR_MDIOIDLE_MASK) == 0x00000000U);

	/* Read data */
		*PhyDataPtr = (u16)XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					XEMACPS_PHYMNTNC_OFFSET);
		Status = (LONG)(XST_SUCCESS);
	}
	return Status;
}


/*****************************************************************************/
/**
* Write data to the specified PHY register. The Ethernet driver does not
* require the device to be stopped before writing to the PHY.  Although it is
* probably a good idea to stop the device, it is the responsibility of the
* application to deem this necessary. The MAC provides the driver with the
* ability to talk to a PHY that adheres to the Media Independent Interface
* (MII) as defined in the IEEE 802.3 standard.
*
* Prior to PHY access with this function, the user should have setup the MDIO
* clock with XEmacPs_SetMdioDivisor().
*
* @param InstancePtr is a pointer to the XEmacPs instance to be worked on.
* @param PhyAddress is the address of the PHY to be written (supports multiple
*        PHYs)
* @param RegisterNum is the register number, 0-31, of the specific PHY register
*        to write
* @param PhyData is the 16-bit value that will be written to the register
*
* @return
*
* - XST_SUCCESS if the PHY was written to successfully. Since there is no error
*   status from the MAC on a write, the user should read the PHY to verify the
*   write was successful.
* - XST_EMAC_MII_BUSY if there is another PHY operation in progress
*
* @note
*
* This function is not thread-safe. The user must provide mutually exclusive
* access to this function if there are to be multiple threads that can call it.
*
* There is the possibility that this function will not return if the hardware
* is broken (i.e., it never sets the status bit indicating that the write is
* done). If this is of concern to the user, the user should provide a mechanism
* suitable to their needs for recovery.
*
* For the duration of this function, all host interface reads and writes are
* blocked to the current XEmacPs instance.
*
******************************************************************************/
LONG XEmacPs_PhyWrite(XEmacPs *InstancePtr, u32 PhyAddress,
		      u32 RegisterNum, u16 PhyData)
{
	u32 Mgtcr;
	volatile u32 Ipisr;
	u32 IpWriteTemp;
	LONG Status;

	Xil_AssertNonvoid(InstancePtr != NULL);

	/* Make sure no other PHY operation is currently in progress */
	if ((!(XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
				XEMACPS_NWSR_OFFSET) &
	      XEMACPS_NWSR_MDIOIDLE_MASK))==TRUE) {
		Status = (LONG)(XST_EMAC_MII_BUSY);
	} else {
	/* Construct Mgtcr mask for the operation */
	Mgtcr = XEMACPS_PHYMNTNC_OP_MASK | XEMACPS_PHYMNTNC_OP_W_MASK |
			(PhyAddress << XEMACPS_PHYMNTNC_PHAD_SHFT_MSK) |
			(RegisterNum << XEMACPS_PHYMNTNC_PREG_SHFT_MSK) | (u32)PhyData;

	/* Write Mgtcr and wait for completion */
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress,
			   XEMACPS_PHYMNTNC_OFFSET, Mgtcr);

	do {
		Ipisr = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
					  XEMACPS_NWSR_OFFSET);
				IpWriteTemp = Ipisr;
		} while ((IpWriteTemp & XEMACPS_NWSR_MDIOIDLE_MASK) == 0x00000000U);

		Status = (LONG)(XST_SUCCESS);
	}
	return Status;
}

/*****************************************************************************/
/**
* API to update the Burst length in the DMACR register.
*
* @param InstancePtr is a pointer to the XEmacPs instance to be worked on.
* @param BLength is the length in bytes for the dma burst.
*
* @return None
*
******************************************************************************/
void XEmacPs_DMABLengthUpdate(XEmacPs *InstancePtr, s32 BLength)
{
	u32 Reg;
	u32 RegUpdateVal = 0;

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid((BLength == XEMACPS_SINGLE_BURST) ||
					(BLength == XEMACPS_4BYTE_BURST) ||
					(BLength == XEMACPS_8BYTE_BURST) ||
					(BLength == XEMACPS_16BYTE_BURST));

	switch (BLength) {
		case XEMACPS_SINGLE_BURST:
			RegUpdateVal = XEMACPS_DMACR_SINGLE_AHB_BURST;
			break;

		case XEMACPS_4BYTE_BURST:
			RegUpdateVal = XEMACPS_DMACR_INCR4_AHB_BURST;
			break;

		case XEMACPS_8BYTE_BURST:
			RegUpdateVal = XEMACPS_DMACR_INCR8_AHB_BURST;
			break;

		case XEMACPS_16BYTE_BURST:
			RegUpdateVal = XEMACPS_DMACR_INCR16_AHB_BURST;
			break;
	}
	Reg = XEmacPs_ReadReg(InstancePtr->Config.BaseAddress,
						XEMACPS_DMACR_OFFSET);

	Reg &= (u32)(~XEMACPS_DMACR_BLENGTH_MASK);
	Reg |= RegUpdateVal;
	XEmacPs_WriteReg(InstancePtr->Config.BaseAddress, XEMACPS_DMACR_OFFSET,
																	Reg);
}
/** @} */
