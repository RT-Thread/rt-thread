/******************************************************************************
* Copyright (C) 2013 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xsdps_include.h
* @addtogroup sdps_v3_9
* @{
*
* This header file contains the identifiers and basic HW access driver
* functions (or  macros) that can be used to access the device. Other driver
* functions are defined in xsdps.h.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ---    -------- -----------------------------------------------
* 3.9   mn     03/03/20 Restructured the code for more readability and modularity
*       mn     03/16/20 Move XSdPs_Select_Card API to User APIs
*
* </pre>
*
******************************************************************************/

#ifndef SDPS_INCLUDE_H_
#define SDPS_INCLUDE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "xsdps.h"
#if defined (__aarch64__)
#include "xil_smc.h"
#endif

/** @cond INTERNAL */
s32 XSdPs_SdCardInitialize(XSdPs *InstancePtr);
s32 XSdPs_MmcCardInitialize(XSdPs *InstancePtr);
s32 XSdPs_IdentifyCard(XSdPs *InstancePtr);
s32 XSdPs_CmdTransfer(XSdPs *InstancePtr, u32 Cmd, u32 Arg, u32 BlkCnt);
s32 XSdPs_SetupTransfer(XSdPs *InstancePtr);
s32 XSdPs_Read(XSdPs *InstancePtr, u32 Arg, u32 BlkCnt, u8 *Buff);
s32 XSdPs_Write(XSdPs *InstancePtr, u32 Arg, u32 BlkCnt, const u8 *Buff);
void XSdPs_Identify_UhsMode(XSdPs *InstancePtr, u8 *ReadBuff);
s32 XSdPs_Uhs_ModeInit(XSdPs *InstancePtr, u8 Mode);
s32 XSdPs_DllReset(XSdPs *InstancePtr);
s32 XSdPs_Switch_Voltage(XSdPs *InstancePtr);
void XSdPs_SetupADMA2DescTbl64Bit(XSdPs *InstancePtr, u32 BlkCnt);
void XSdPs_SetupADMA2DescTbl(XSdPs *InstancePtr, u32 BlkCnt, const u8 *Buff);
void XSdPs_DllRstCtrl(XSdPs *InstancePtr, u8 EnRst);
void XSdPs_ConfigTapDelay(XSdPs *InstancePtr);
s32 XSdPs_Execute_Tuning(XSdPs *InstancePtr);
void XSdPs_Setup32ADMA2DescTbl(XSdPs *InstancePtr, u32 BlkCnt, const u8 *Buff);
void XSdPs_Setup64ADMA2DescTbl(XSdPs *InstancePtr, u32 BlkCnt, const u8 *Buff);
u32 XSdPs_FrameCmd(XSdPs *InstancePtr, u32 Cmd);
void XSdPs_SetTapDelay(XSdPs *InstancePtr);
s32 XSdPs_CheckResetDone(XSdPs *InstancePtr, u8 Value);
s32 XSdPs_CheckVoltage18(XSdPs *InstancePtr);
s32 XSdPs_SetupCmd(XSdPs *InstancePtr, u32 Arg, u32 BlkCnt);
void XSdPs_SetExecTuning(XSdPs *InstancePtr);
s32 XSdPs_CheckCardDetect(XSdPs *InstancePtr);
s32 XSdPs_CardReset(XSdPs *InstancePtr);
s32 XSdPs_CardIfCond(XSdPs *InstancePtr);
s32 XSdPs_CardOpCond(XSdPs *InstancePtr);
s32 XSdPs_GetCardId(XSdPs *InstancePtr);
s32 XSdPs_GetCsd(XSdPs *InstancePtr);
s32 XSdPs_CardSetVoltage18(XSdPs *InstancePtr);
s32 XSdPs_SdModeInit(XSdPs *InstancePtr);
s32 XSdPs_SdCardEnum(XSdPs *InstancePtr);
s32 XSdPs_MmcCardEnum(XSdPs *InstancePtr);
s32 XSdPs_MmcModeInit(XSdPs *InstancePtr);
s32 XSdPs_EmmcModeInit(XSdPs *InstancePtr);
s32 XSdPs_ResetConfig(XSdPs *InstancePtr);
void XSdPs_HostConfig(XSdPs *InstancePtr);
s32 XSdPs_Reset(XSdPs *InstancePtr, u8 Value);
void XSdPs_DisableBusPower(XSdPs *InstancePtr);
void XSdPs_EnableBusPower(XSdPs *InstancePtr);
s32 XSdPs_CheckBusIdle(XSdPs *InstancePtr, u32 Value);
s32 XSdPs_CheckBusHigh(XSdPs *InstancePtr);
s32 XSdPs_SetupVoltageSwitch(XSdPs *InstancePtr);
s32 XSdPs_AutoTuning(XSdPs *InstancePtr);
s32 XSdPs_SetClock(XSdPs *InstancePtr, u32 SelFreq);
u32 XSdPs_CalcClock(XSdPs *InstancePtr, u32 SelFreq);
s32 XSdPs_EnableClock(XSdPs *InstancePtr, u16 ClockReg);
s32 XSdps_CheckTransferDone(XSdPs *InstancePtr);
s32 XSdPs_Change_SdBusSpeed(XSdPs *InstancePtr);
s32 XSdPs_Change_MmcBusSpeed(XSdPs *InstancePtr);
s32 XSdPs_CalcBusSpeed(XSdPs *InstancePtr, u32 *Arg);
void XSdPs_SetupReadDma(XSdPs *InstancePtr, u16 BlkCnt, u16 BlkSize, u8 *Buff);
void XSdPs_SetupWriteDma(XSdPs *InstancePtr, u16 BlkCnt, u16 BlkSize, const u8 *Buff);
s32 XSdPs_DoDmaTransfer(XSdPs *InstancePtr, u32 Cmd, u32 Arg, u32 BlkCnt);
s32 XSdPs_DoCmdTransfer(XSdPs *InstancePtr, u32 Cmd, u32 Arg, u32 BlkCnt);
s32 XSdPs_SetVoltage18(XSdPs *InstancePtr);
s32 XSdPs_SendCmd(XSdPs *InstancePtr, u32 Cmd);
void XSdPs_IdentifyEmmcMode(XSdPs *InstancePtr, const u8 *ExtCsd);
s32 XSdPs_CheckEmmcTiming(XSdPs *InstancePtr, u8 *ExtCsd);
void XSdPs_ConfigPower(XSdPs *InstancePtr);
void XSdPs_ConfigDma(XSdPs *InstancePtr);
void XSdPs_ConfigInterrupt(XSdPs *InstancePtr);

#if EL1_NONSECURE && defined (__aarch64__)
void XSdps_Smc(XSdPs *InstancePtr, u32 RegOffset, u32 Mask, u32 Val);
#endif
/** @endcond */

#ifdef __cplusplus
}
#endif

#endif
