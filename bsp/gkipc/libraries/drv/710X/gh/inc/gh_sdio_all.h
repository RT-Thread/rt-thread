/******************************************************************************
**
** \file      gh_sdio_all.c
**
** \brief     SDIO Host Controller.
**
**            Copyright:   2012 - 2016 (C) GoKe Microelectronics
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
#ifdef GK7101S
#include "gh_sdio1.h"
#endif

#define GH_SDIO0 0
#define GH_SDIO1 1
#define GH_ERR   -1

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register SDIO_SysAddrReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_SysAddrReg(U32 sdio, U32 data);
 U32  GH_SDIO_get_SysAddrReg(U32 sdio);
/*----------------------------------------------------------------------------*/
/* register SDIO_TranModeReg (read/write)                                    */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_TranModeReg(U32 sdio, U16 data);
 U16  GH_SDIO_get_TranModeReg(U32 sdio);
 void GH_SDIO_set_TranModeReg_BlkCountEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_TranModeReg_BlkCountEn(U32 sdio);
 void GH_SDIO_set_TranModeReg_AutoCmd12En(U32 sdio, U8 data);
 U8   GH_SDIO_get_TranModeReg_AutoCmd12En(U32 sdio);
 void GH_SDIO_set_TranModeReg_DmaEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_TranModeReg_DmaEn(U32 sdio);
 void GH_SDIO_set_TranModeReg_MSBlkSelect(U32 sdio, U8 data);
 U8   GH_SDIO_get_TranModeReg_MSBlkSelect(U32 sdio);
 void GH_SDIO_set_TranModeReg_DataTraDirSelect(U32 sdio, U8 data);
 U8   GH_SDIO_get_TranModeReg_DataTraDirSelect(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_NorIntSigEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_NorIntSigEnReg(U32 sdio, U16 data);
 U16  GH_SDIO_get_NorIntSigEnReg(U32 sdio);
 void GH_SDIO_set_NorIntSigEnReg_CmdCompleteSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntSigEnReg_CmdCompleteSigEn(U32 sdio);
 void GH_SDIO_set_NorIntSigEnReg_TraCompleteSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntSigEnReg_TraCompleteSigEn(U32 sdio);
 void GH_SDIO_set_NorIntSigEnReg_BlkGapEveSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntSigEnReg_BlkGapEveSigEn(U32 sdio);
 void GH_SDIO_set_NorIntSigEnReg_DmaIntSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntSigEnReg_DmaIntSigEn(U32 sdio);
 void GH_SDIO_set_NorIntSigEnReg_BufWReadySigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntSigEnReg_BufWReadySigEn(U32 sdio);
 void GH_SDIO_set_NorIntSigEnReg_BufRReadySigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntSigEnReg_BufRReadySigEn(U32 sdio);
 void GH_SDIO_set_NorIntSigEnReg_CardInsertionSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntSigEnReg_CardInsertionSigEn(U32 sdio);
 void GH_SDIO_set_NorIntSigEnReg_CardRemSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntSigEnReg_CardRemSigEn(U32 sdio);
 void GH_SDIO_set_NorIntSigEnReg_CardIntSigEN(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntSigEnReg_CardIntSigEN(U32 sdio);
 void GH_SDIO_set_NorIntSigEnReg_FixedTo0(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntSigEnReg_FixedTo0(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_ErrIntSigEn (read/write)                                    */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_ErrIntSigEnReg(U32 sdio, U16 data);
 U16  GH_SDIO_get_ErrIntSigEnReg(U32 sdio);
 void GH_SDIO_set_ErrIntSigEnReg_CmdTimeoutErrSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntSigEnReg_CmdTimeoutErrSigEn(U32 sdio);
 void GH_SDIO_set_ErrIntSigEnReg_CmdEndBitErrSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntSigEnReg_CmdEndBitErrSigEn(U32 sdio);
 void GH_SDIO_set_ErrIntSigEnReg_CmdIndexErrSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntSigEnReg_CmdIndexErrSigEn(U32 sdio);
 void GH_SDIO_set_ErrIntSigEnReg_DataTimeoutErrSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntSigEnReg_DataTimeoutErrSigEn(U32 sdio);
 void GH_SDIO_set_ErrIntSigEnReg_CmdCrcErrSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntSigEnReg_CmdCrcErrSigEn(U32 sdio);
 void GH_SDIO_set_ErrIntSigEnReg_DataCrcErrSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntSigEnReg_DataCrcErrSigEn(U32 sdio);
 void GH_SDIO_set_ErrIntSigEnReg_DataEndBitErrSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntSigEnReg_DataEndBitErrSigEn(U32 sdio);
 void GH_SDIO_set_ErrIntSigEnReg_CurLimitErrSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntSigEnReg_CurLimitErrSigEn(U32 sdio);
 void GH_SDIO_set_ErrIntSigEnReg_AutoCmd12ErrSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntSigEnReg_AutoCmd12ErrSigEn(U32 sdio);
 void GH_SDIO_set_ErrIntSigEnReg_VendorSpecificErrSigEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntSigEnReg_VendorSpecificErrSigEn(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_BlkCouReg (read/write)                                      */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_BlkCouReg(U32 sdio, U16 data);
 U16  GH_SDIO_get_BlkCouReg(U32 sdio);
 void GH_SDIO_set_BlkCouReg_BlkCountForCurTra(U32 sdio, U16 data);
 U16  GH_SDIO_get_BlkCouReg_BlkCountForCurTra(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_BlkSizeReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_BlkSizeReg(U32 sdio, U16 data);
 U16  GH_SDIO_get_BlkSizeReg(U32 sdio);
 void GH_SDIO_set_BlkSizeReg_TraBlkSize(U32 sdio, U16 data);
 U16  GH_SDIO_get_BlkSizeReg_TraBlkSize(U32 sdio);
 void GH_SDIO_set_BlkSizeReg_HostSdmaBufSize(U32 sdio, U8 data);
 U8   GH_SDIO_get_BlkSizeReg_HostSdmaBufSize(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_NorIntStaEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_NorIntStaEnReg(U32 sdio, U16 data);
 U16  GH_SDIO_get_NorIntStaEnReg(U32 sdio);
 void GH_SDIO_set_NorIntStaEnReg_CmdCompleteStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaEnReg_CmdCompleteStatusEn(U32 sdio);
 void GH_SDIO_set_NorIntStaEnReg_TraCompleteStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaEnReg_TraCompleteStatusEn(U32 sdio);
 void GH_SDIO_set_NorIntStaEnReg_BlkGapEveStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaEnReg_BlkGapEveStatusEn(U32 sdio);
 void GH_SDIO_set_NorIntStaEnReg_DmaIntStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaEnReg_DmaIntStatusEn(U32 sdio);
 void GH_SDIO_set_NorIntStaEnReg_BufWReadyStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaEnReg_BufWReadyStatusEn(U32 sdio);
 void GH_SDIO_set_NorIntStaEnReg_BufRReadyStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaEnReg_BufRReadyStatusEn(U32 sdio);
 void GH_SDIO_set_NorIntStaEnReg_CardInsertionStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaEnReg_CardInsertionStatusEn(U32 sdio);
 void GH_SDIO_set_NorIntStaEnReg_CardRemStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaEnReg_CardRemStatusEn(U32 sdio);
 void GH_SDIO_set_NorIntStaEnReg_CardIntStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaEnReg_CardIntStatusEn(U32 sdio);
 void GH_SDIO_set_NorIntStaEnReg_FixedTo0(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaEnReg_FixedTo0(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_ErrIntStaEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_ErrIntStaEnReg(U32 sdio, U16 data);
 U16  GH_SDIO_get_ErrIntStaEnReg(U32 sdio);
 void GH_SDIO_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn(U32 sdio);
 void GH_SDIO_set_ErrIntStaEnReg_CmdEndBitErrStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaEnReg_CmdEndBitErrStatusEn(U32 sdio);
 void GH_SDIO_set_ErrIntStaEnReg_CmdCrcErrStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaEnReg_CmdCrcErrStatusEn(U32 sdio);
 void GH_SDIO_set_ErrIntStaEnReg_CmdIndexErrStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaEnReg_CmdIndexErrStatusEn(U32 sdio);
 void GH_SDIO_set_ErrIntStaEnReg_DataCrcErrStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaEnReg_DataCrcErrStatusEn(U32 sdio);
 void GH_SDIO_set_ErrIntStaEnReg_DataTimeoutErrStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaEnReg_DataTimeoutErrStatusEn(U32 sdio);
 void GH_SDIO_set_ErrIntStaEnReg_DataEndBitErrStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaEnReg_DataEndBitErrStatusEn(U32 sdio);
 void GH_SDIO_set_ErrIntStaEnReg_CurLimitErrStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaEnReg_CurLimitErrStatusEn(U32 sdio);
 void GH_SDIO_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn(U32 sdio);
 void GH_SDIO_set_ErrIntStaEnReg_VendorSpecificErrStatusEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaEnReg_VendorSpecificErrStatusEn(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_NorIntStaReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_NorIntStaReg(U32 sdio, U16 data);
 U16  GH_SDIO_get_NorIntStaReg(U32 sdio);
 void GH_SDIO_set_NorIntStaReg_CmdComplete(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaReg_CmdComplete(U32 sdio);
 void GH_SDIO_set_NorIntStaReg_BlkGapEvent(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaReg_BlkGapEvent(U32 sdio);
 void GH_SDIO_set_NorIntStaReg_DmaInt(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaReg_DmaInt(U32 sdio);
 void GH_SDIO_set_NorIntStaReg_TraComplete(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaReg_TraComplete(U32 sdio);
 void GH_SDIO_set_NorIntStaReg_BufWReady(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaReg_BufWReady(U32 sdio);
 void GH_SDIO_set_NorIntStaReg_CardInsertion(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaReg_CardInsertion(U32 sdio);
 void GH_SDIO_set_NorIntStaReg_BufRReady(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaReg_BufRReady(U32 sdio);
 void GH_SDIO_set_NorIntStaReg_CardRemoval(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaReg_CardRemoval(U32 sdio);
 void GH_SDIO_set_NorIntStaReg_CardInt(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaReg_CardInt(U32 sdio);
 void GH_SDIO_set_NorIntStaReg_BootAckRcv(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaReg_BootAckRcv(U32 sdio);
 void GH_SDIO_set_NorIntStaReg_ErrInt(U32 sdio, U8 data);
 U8   GH_SDIO_get_NorIntStaReg_ErrInt(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_ErrIntStaReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_ErrIntStaReg(U32 sdio, U16 data);
 U16  GH_SDIO_get_ErrIntStaReg(U32 sdio);
 void GH_SDIO_set_ErrIntStaReg_CmdTimeoutErr(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaReg_CmdTimeoutErr(U32 sdio);
 void GH_SDIO_set_ErrIntStaReg_CmdCrcErr(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaReg_CmdCrcErr(U32 sdio);
 void GH_SDIO_set_ErrIntStaReg_CmdEndBitErr(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaReg_CmdEndBitErr(U32 sdio);
 void GH_SDIO_set_ErrIntStaReg_CmdIndexErr(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaReg_CmdIndexErr(U32 sdio);
 void GH_SDIO_set_ErrIntStaReg_DataTimeoutErr(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaReg_DataTimeoutErr(U32 sdio);
 void GH_SDIO_set_ErrIntStaReg_DataCrcErr(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaReg_DataCrcErr(U32 sdio);
 void GH_SDIO_set_ErrIntStaReg_DataEndBitErr(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaReg_DataEndBitErr(U32 sdio);
 void GH_SDIO_set_ErrIntStaReg_CurLimitErr(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaReg_CurLimitErr(U32 sdio);
 void GH_SDIO_set_ErrIntStaReg_AutoCmd12Err(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaReg_AutoCmd12Err(U32 sdio);
 void GH_SDIO_set_ErrIntStaReg_VendorSpecificErrStatus(U32 sdio, U8 data);
 U8   GH_SDIO_get_ErrIntStaReg_VendorSpecificErrStatus(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_CmdReg (read/write)                                         */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_CmdReg(U32 sdio, U16 data);
 U16  GH_SDIO_get_CmdReg(U32 sdio);
 void GH_SDIO_set_CmdReg_RepTypeSelect(U32 sdio, U8 data);
 U8   GH_SDIO_get_CmdReg_RepTypeSelect(U32 sdio);
 void GH_SDIO_set_CmdReg_CmdCrcCheckEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_CmdReg_CmdCrcCheckEn(U32 sdio);
 void GH_SDIO_set_CmdReg_DataPreSelect(U32 sdio, U8 data);
 U8   GH_SDIO_get_CmdReg_DataPreSelect(U32 sdio);
 void GH_SDIO_set_CmdReg_CmdIndexCheckEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_CmdReg_CmdIndexCheckEn(U32 sdio);
 void GH_SDIO_set_CmdReg_CmdType(U32 sdio, U8 data);
 U8   GH_SDIO_get_CmdReg_CmdType(U32 sdio);
 void GH_SDIO_set_CmdReg_CmdIndex(U32 sdio, U8 data);
 U8   GH_SDIO_get_CmdReg_CmdIndex(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_Control01Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_Control01Reg(U32 sdio, U32 data);
 U32  GH_SDIO_get_Control01Reg(U32 sdio);
 void GH_SDIO_set_Control01Reg_DataTimeoutCounterValue(U32 sdio, U8 data);
 U8   GH_SDIO_get_Control01Reg_DataTimeoutCounterValue(U32 sdio);
 void GH_SDIO_set_Control01Reg_SoftwareResetCmdLine(U32 sdio, U8 data);
 U8   GH_SDIO_get_Control01Reg_SoftwareResetCmdLine(U32 sdio);
 void GH_SDIO_set_Control01Reg_SoftwareResetAll(U32 sdio, U8 data);
 U8   GH_SDIO_get_Control01Reg_SoftwareResetAll(U32 sdio);
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

/*----------------------------------------------------------------------------*/
/* register SDIO_Resp0Reg (read)                                             */
/*----------------------------------------------------------------------------*/
 U32  GH_SDIO_get_Resp0Reg(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_Resp1Reg (read)                                             */
/*----------------------------------------------------------------------------*/
 U32  GH_SDIO_get_Resp1Reg(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_Resp2Reg (read)                                             */
/*----------------------------------------------------------------------------*/
 U32  GH_SDIO_get_Resp2Reg(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_Resp3Reg (read)                                             */
/*----------------------------------------------------------------------------*/
 U32  GH_SDIO_get_Resp3Reg(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_Control00Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_Control00Reg(U32 sdio, U32 data);
 U32  GH_SDIO_get_Control00Reg(U32 sdio);
 void GH_SDIO_set_Control00Reg_LedControl(U32 sdio, U8 data);
 U8   GH_SDIO_get_Control00Reg_LedControl(U32 sdio);
 void GH_SDIO_set_Control00Reg_DataTraWidth(U32 sdio, U8 data);
 U8   GH_SDIO_get_Control00Reg_DataTraWidth(U32 sdio);
 void GH_SDIO_set_Control00Reg_Sd8BitMode(U32 sdio, U8 data);
 U8   GH_SDIO_get_Control00Reg_Sd8BitMode(U32 sdio);
 void GH_SDIO_set_Control00Reg_HostSpeedEn(U32 sdio, U8 data);
 U8   GH_SDIO_get_Control00Reg_HostSpeedEn(U32 sdio);
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
 void GH_SDIO_set_Control00Reg_RWaitControl(U32 sdio, U8 data);
 U8   GH_SDIO_get_Control00Reg_RWaitControl(U32 sdio);
 void GH_SDIO_set_Control00Reg_ContinueReq(U32 sdio, U8 data);
 U8   GH_SDIO_get_Control00Reg_ContinueReq(U32 sdio);
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
 void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardIns(U32 sdio, U8 data);
 U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardIns(U32 sdio);
 void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardInt(U32 sdio, U8 data);
 U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardInt(U32 sdio);
 void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardRem(U32 sdio, U8 data);
 U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardRem(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_PresentStateReg (read)                                      */
/*----------------------------------------------------------------------------*/
 U32  GH_SDIO_get_PresentStateReg(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_CmdInhibitCmd(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_DataLineActive(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_CmdInhibitData(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_RTraActive(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_BufWEn(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_WTraActive(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_BufREn(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_CardInserted(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_CardDetectPinLevel(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_CardStateStable(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_WProSwiPinLevel(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_Data03LineSigLevel(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_CmdLineSigLevel(U32 sdio);
 U8   GH_SDIO_get_PresentStateReg_Data47LineSigLevel(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_ArgReg (read/write)                                         */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_ArgReg(U32 sdio, U32 data);
 U32  GH_SDIO_get_ArgReg(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_CapReg (read)                                               */
/*----------------------------------------------------------------------------*/
 U32  GH_SDIO_get_CapReg(U32 sdio);
 U8   GH_SDIO_get_CapReg_TimeoutClkFre(U32 sdio);
 U8   GH_SDIO_get_CapReg_TimeoutClkUnit(U32 sdio);
 U8   GH_SDIO_get_CapReg_BaseClkFreForSdClk(U32 sdio);
 U8   GH_SDIO_get_CapReg_MaxBlkLen(U32 sdio);
 U8   GH_SDIO_get_CapReg_ExtendedMediaBusSup(U32 sdio);
 U8   GH_SDIO_get_CapReg_HighSpeedSup(U32 sdio);
 U8   GH_SDIO_get_CapReg_SusResSup(U32 sdio);
 U8   GH_SDIO_get_CapReg_SdmaSup(U32 sdio);
 U8   GH_SDIO_get_CapReg_VoltageSup33v(U32 sdio);
 U8   GH_SDIO_get_CapReg_VoltageSup30v(U32 sdio);
 U8   GH_SDIO_get_CapReg_VoltageSup18v(U32 sdio);
 U8   GH_SDIO_get_CapReg_IntMode(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_AutoCmd12ErrStatusReg (read)                                */
/*----------------------------------------------------------------------------*/
 U32  GH_SDIO_get_AutoCmd12ErrStatusReg(U32 sdio);
 U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr(U32 sdio);
 U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr(U32 sdio);
 U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr(U32 sdio);
 U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe(U32 sdio);
 U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr(U32 sdio);
 U8   GH_SDIO_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_BufferDataPortReg (read/write)                              */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_BufferDataPortReg(U32 sdio, U32 data);
 U32  GH_SDIO_get_BufferDataPortReg(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_MaxCurCapReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
 void GH_SDIO_set_MaxCurCapReg(U32 sdio, U32 data);
 U32  GH_SDIO_get_MaxCurCapReg(U32 sdio);
 void GH_SDIO_set_MaxCurCapReg_MaxCurFor33v(U32 sdio, U8 data);
 U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor33v(U32 sdio);
 void GH_SDIO_set_MaxCurCapReg_MaxCurFor30v(U32 sdio, U8 data);
 U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor30v(U32 sdio);
 void GH_SDIO_set_MaxCurCapReg_MaxCurFor18v(U32 sdio, U8 data);
 U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor18v(U32 sdio);

/*----------------------------------------------------------------------------*/
/* register SDIO_SlotIntStatusReg (read)                                     */
/*----------------------------------------------------------------------------*/
 U32  GH_SDIO_get_SlotIntStatusReg(U32 sdio);
 U8   GH_SDIO_get_SlotIntStatusReg_IntSigForEachSlot(U32 sdio);
 U8   GH_SDIO_get_SlotIntStatusReg_SpecifiVerNum(U32 sdio);
 U8   GH_SDIO_get_SlotIntStatusReg_VendorVerNum(U32 sdio);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_SDIO_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_SDIO_ALL_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

