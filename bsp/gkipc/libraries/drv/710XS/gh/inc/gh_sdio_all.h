/*!
*******************************************************************************
**
** \file      gh_sdio_all.h
**
** \brief     SDIO Host Controller.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GH_SDIO_ALL_H
#define _GH_SDIO_ALL_H

#include "gtypes.h" /* global type definitions */
#include "gh_sdio0.h"
#include "gh_sdio1.h"

#define GH_SDIO0 0
#define GH_SDIO1 1

/*---------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
void GH_SDIO_set_SysAddrReg(U32 sdio, U32 data);
U32  GH_SDIO_get_SysAddrReg(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg(U32 sdio, U32 data);
U32  GH_SDIO_get_TranModeNorIntSigEnReg(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_DmaEn(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_DmaEn(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_BlkCountEn(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_BlkCountEn(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_AutoCmd12En(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_AutoCmd12En(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_DataTraDirSelect(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_DataTraDirSelect(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_MSBlkSelect(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_MSBlkSelect(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_CmdCompleteSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_CmdCompleteSigEn(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_TraCompleteSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_TraCompleteSigEn(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_BlkGapEveSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_BlkGapEveSigEn(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_DmaIntSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_DmaIntSigEn(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_BufWReadySigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_BufWReadySigEn(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_BufRReadySigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_BufRReadySigEn(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_CardInsertionSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_CardInsertionSigEn(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_CardRemSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_CardRemSigEn(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_CardIntSigEN(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_CardIntSigEN(U32 sdio);
void GH_SDIO_set_TranModeNorIntSigEnReg_FixedTo0(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeNorIntSigEnReg_FixedTo0(U32 sdio);

void GH_SDIO_set_ErrIntSigEnBlkCouReg(U32 sdio, U32 data);
U32  GH_SDIO_get_ErrIntSigEnBlkCouReg(U32 sdio);
void GH_SDIO_set_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnBlkCouReg_DataCrcErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_DataCrcErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnBlkCouReg_CurLimitErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_CurLimitErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnBlkCouReg_BlkCountForCurTra(U32 sdio, U16 data);
U16  GH_SDIO_get_ErrIntSigEnBlkCouReg_BlkCountForCurTra(U32 sdio);

void GH_SDIO_set_BlkSizeNorIntStaEnReg(U32 sdio, U32 data);
U32  GH_SDIO_get_BlkSizeNorIntStaEnReg(U32 sdio);
void GH_SDIO_set_BlkSizeNorIntStaEnReg_TraBlkSize(U32 sdio, U16 data);
U16  GH_SDIO_get_BlkSizeNorIntStaEnReg_TraBlkSize(U32 sdio);
void GH_SDIO_set_BlkSizeNorIntStaEnReg_HostSdmaBufSize(U32 sdio, U8 data);
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_HostSdmaBufSize(U32 sdio);
void GH_SDIO_set_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn(U32 sdio);
void GH_SDIO_set_BlkSizeNorIntStaEnReg_TraCompleteStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_TraCompleteStatusEn(U32 sdio);
void GH_SDIO_set_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn(U32 sdio);
void GH_SDIO_set_BlkSizeNorIntStaEnReg_DmaIntStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_DmaIntStatusEn(U32 sdio);
void GH_SDIO_set_BlkSizeNorIntStaEnReg_BufWReadyStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_BufWReadyStatusEn(U32 sdio);
void GH_SDIO_set_BlkSizeNorIntStaEnReg_BufRReadyStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_BufRReadyStatusEn(U32 sdio);
void GH_SDIO_set_BlkSizeNorIntStaEnReg_CardInsertionStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_CardInsertionStatusEn(U32 sdio);
void GH_SDIO_set_BlkSizeNorIntStaEnReg_CardRemStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_CardRemStatusEn(U32 sdio);
void GH_SDIO_set_BlkSizeNorIntStaEnReg_CardIntStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_CardIntStatusEn(U32 sdio);
void GH_SDIO_set_BlkSizeNorIntStaEnReg_FixedTo0(U32 sdio, U8 data);
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_FixedTo0(U32 sdio);

void GH_SDIO_set_ErrIntStaEnNorIntStaReg(U32 sdio, U32 data);
U32  GH_SDIO_get_ErrIntStaEnNorIntStaReg(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CmdComplete(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CmdComplete(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_TraComplete(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_TraComplete(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_BlkGapEvent(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_BlkGapEvent(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_DmaInt(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_DmaInt(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_BufWReady(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_BufWReady(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_BufRReady(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_BufRReady(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CardInsertion(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CardInsertion(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CardRemoval(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CardRemoval(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CardInt(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CardInt(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_BootAckRcv(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_BootAckRcv(U32 sdio);
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_ErrInt(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_ErrInt(U32 sdio);

void GH_SDIO_set_ErrIntStatusCommondReg(U32 sdio, U32 data);
U32  GH_SDIO_get_ErrIntStatusCommondReg(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_CmdTimeoutErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdTimeoutErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_CmdCrcErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdCrcErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_CmdEndBitErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdEndBitErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_CmdIndexErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdIndexErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_DataTimeoutErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_DataTimeoutErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_DataCrcErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_DataCrcErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_DataEndBitErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_DataEndBitErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_CurLimitErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_CurLimitErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_AutoCmd12Err(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_AutoCmd12Err(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_VendorSpecificErrStatus(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_VendorSpecificErrStatus(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_RepTypeSelect(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_RepTypeSelect(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_CmdCrcCheckEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdCrcCheckEn(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_CmdIndexCheckEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdIndexCheckEn(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_DataPreSelect(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_DataPreSelect(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_CmdType(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdType(U32 sdio);
void GH_SDIO_set_ErrIntStatusCommondReg_CmdIndex(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdIndex(U32 sdio);

void GH_SDIO_set_Control01Reg(U32 sdio, U32 data);
U32  GH_SDIO_get_Control01Reg(U32 sdio);
void GH_SDIO_set_Control01Reg_DataTimeoutCounterValue(U32 sdio, U8 data);
U8   GH_SDIO_get_Control01Reg_DataTimeoutCounterValue(U32 sdio);
void GH_SDIO_set_Control01Reg_SoftwareResetAll(U32 sdio, U8 data);
U8   GH_SDIO_get_Control01Reg_SoftwareResetAll(U32 sdio);
void GH_SDIO_set_Control01Reg_SoftwareResetCmdLine(U32 sdio, U8 data);
U8   GH_SDIO_get_Control01Reg_SoftwareResetCmdLine(U32 sdio);
void GH_SDIO_set_Control01Reg_SoftwareResetDatLine(U32 sdio, U8 data);
U8   GH_SDIO_get_Control01Reg_SoftwareResetDatLine(U32 sdio);
void GH_SDIO_set_Control01Reg_InternalClkEn(U32 sdio, U8 data);
U8   GH_SDIO_get_Control01Reg_InternalClkEn(U32 sdio);
void GH_SDIO_set_Control01Reg_InternalClkStable(U32 sdio, U8 data);
U8   GH_SDIO_get_Control01Reg_InternalClkStable(U32 sdio);
void GH_SDIO_set_Control01Reg_SdClkEn(U32 sdio, U8 data);
U8   GH_SDIO_get_Control01Reg_SdClkEn(U32 sdio);
void GH_SDIO_set_Control01Reg_SdclkFreSelect(U32 sdio, U8 data);
U8   GH_SDIO_get_Control01Reg_SdclkFreSelect(U32 sdio);

U32  GH_SDIO_get_Resp0Reg(U32 sdio);

U32  GH_SDIO_get_Resp1Reg(U32 sdio);

U32  GH_SDIO_get_Resp2Reg(U32 sdio);

U32  GH_SDIO_get_Resp3Reg(U32 sdio);

void GH_SDIO_set_Control00Reg(U32 sdio, U32 data);
U32  GH_SDIO_get_Control00Reg(U32 sdio);
void GH_SDIO_set_Control00Reg_LedControl(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_LedControl(U32 sdio);
void GH_SDIO_set_Control00Reg_DataTraWidth(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_DataTraWidth(U32 sdio);
void GH_SDIO_set_Control00Reg_HostSpeedEn(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_HostSpeedEn(U32 sdio);
void GH_SDIO_set_Control00Reg_Sd8BitMode(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_Sd8BitMode(U32 sdio);
void GH_SDIO_set_Control00Reg_CardDetectTestLevel(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_CardDetectTestLevel(U32 sdio);
void GH_SDIO_set_Control00Reg_CardDetectSigDet(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_CardDetectSigDet(U32 sdio);
void GH_SDIO_set_Control00Reg_SdBusPower(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_SdBusPower(U32 sdio);
void GH_SDIO_set_Control00Reg_SdBusVoltageSelect(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_SdBusVoltageSelect(U32 sdio);
void GH_SDIO_set_Control00Reg_StopAtBlkGapReq(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_StopAtBlkGapReq(U32 sdio);
void GH_SDIO_set_Control00Reg_ContinueReq(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_ContinueReq(U32 sdio);
void GH_SDIO_set_Control00Reg_RWaitControl(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_RWaitControl(U32 sdio);
void GH_SDIO_set_Control00Reg_IntAtBlkGap(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_IntAtBlkGap(U32 sdio);
void GH_SDIO_set_Control00Reg_DriveCcsd(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_DriveCcsd(U32 sdio);
void GH_SDIO_set_Control00Reg_SpiMode(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_SpiMode(U32 sdio);
void GH_SDIO_set_Control00Reg_BootEn(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_BootEn(U32 sdio);
void GH_SDIO_set_Control00Reg_AltBootEn(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_AltBootEn(U32 sdio);
void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardInt(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardInt(U32 sdio);
void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardIns(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardIns(U32 sdio);
void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardRem(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardRem(U32 sdio);

U32  GH_SDIO_get_PresentStateReg(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_CmdInhibitCmd(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_CmdInhibitData(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_DataLineActive(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_WTraActive(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_RTraActive(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_BufWEn(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_BufREn(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_CardInserted(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_CardStateStable(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_CardDetectPinLevel(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_WProSwiPinLevel(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_Data03LineSigLevel(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_CmdLineSigLevel(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_Data47LineSigLevel(U32 sdio);

void GH_SDIO_set_ArgReg(U32 sdio, U32 data);
U32  GH_SDIO_get_ArgReg(U32 sdio);

U32  GH_SDIO_get_CapReg(U32 sdio);
U8   GH_SDIO_get_CapReg_TimeoutClkFre(U32 sdio);
U8   GH_SDIO_get_CapReg_TimeoutClkUnit(U32 sdio);
U8   GH_SDIO_get_CapReg_BaseClkFreForSdClk(U32 sdio);
U8   GH_SDIO_get_CapReg_MaxBlkLen(U32 sdio);
U8   GH_SDIO_get_CapReg_ExtendedMediaBusSup(U32 sdio);
U8   GH_SDIO_get_CapReg_HighSpeedSup(U32 sdio);
U8   GH_SDIO_get_CapReg_SdmaSup(U32 sdio);
U8   GH_SDIO_get_CapReg_SusResSup(U32 sdio);
U8   GH_SDIO_get_CapReg_VoltageSup33v(U32 sdio);
U8   GH_SDIO_get_CapReg_VoltageSup30v(U32 sdio);
U8   GH_SDIO_get_CapReg_VoltageSup18v(U32 sdio);
U8   GH_SDIO_get_CapReg_IntMode(U32 sdio);

U32  GH_SDIO_get_AutoCmd12ErrStatusReg(U32 sdio);
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe(U32 sdio);
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr(U32 sdio);
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr(U32 sdio);
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr(U32 sdio);
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr(U32 sdio);
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err(U32 sdio);

void GH_SDIO_set_BufferDataPortReg(U32 sdio, U32 data);
U32  GH_SDIO_get_BufferDataPortReg(U32 sdio);

void GH_SDIO_set_MaxCurCapReg(U32 sdio, U32 data);
U32  GH_SDIO_get_MaxCurCapReg(U32 sdio);
void GH_SDIO_set_MaxCurCapReg_MaxCurFor33v(U32 sdio, U8 data);
U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor33v(U32 sdio);
void GH_SDIO_set_MaxCurCapReg_MaxCurFor30v(U32 sdio, U8 data);
U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor30v(U32 sdio);
void GH_SDIO_set_MaxCurCapReg_MaxCurFor18v(U32 sdio, U8 data);
U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor18v(U32 sdio);

U32  GH_SDIO_get_SlotIntStatusReg(U32 sdio);
U8   GH_SDIO_get_SlotIntStatusReg_IntSigForEachSlot(U32 sdio);
U8   GH_SDIO_get_SlotIntStatusReg_SpecifiVerNum(U32 sdio);
U8   GH_SDIO_get_SlotIntStatusReg_VendorVerNum(U32 sdio);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_SDIO_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_SDIO_ALL_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

