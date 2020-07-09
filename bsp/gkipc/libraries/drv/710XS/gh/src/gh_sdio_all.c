/******************************************************************************
**
** \file      gh_sdio_all.c
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
#include "gtypes.h"
#include "gh_sdio_all.h"

void GH_SDIO_set_SysAddrReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_SysAddrReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_SysAddrReg(data);
    }
}
U32  GH_SDIO_get_SysAddrReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SysAddrReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SysAddrReg();
    }
}

void GH_SDIO_set_TranModeNorIntSigEnReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg(data);
    }
}
U32  GH_SDIO_get_TranModeNorIntSigEnReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_DmaEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_DmaEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_DmaEn(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_DmaEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_DmaEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_DmaEn();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_BlkCountEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_BlkCountEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_BlkCountEn(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_BlkCountEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_BlkCountEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_BlkCountEn();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_AutoCmd12En(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_AutoCmd12En(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_AutoCmd12En(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_AutoCmd12En(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_AutoCmd12En();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_AutoCmd12En();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_DataTraDirSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_DataTraDirSelect(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_DataTraDirSelect(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_DataTraDirSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_DataTraDirSelect();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_DataTraDirSelect();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_MSBlkSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_MSBlkSelect(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_MSBlkSelect(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_MSBlkSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_MSBlkSelect();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_MSBlkSelect();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_CmdCompleteSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_CmdCompleteSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_CmdCompleteSigEn(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_CmdCompleteSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_CmdCompleteSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_CmdCompleteSigEn();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_TraCompleteSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_TraCompleteSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_TraCompleteSigEn(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_TraCompleteSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_TraCompleteSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_TraCompleteSigEn();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_BlkGapEveSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_BlkGapEveSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_BlkGapEveSigEn(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_BlkGapEveSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_BlkGapEveSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_BlkGapEveSigEn();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_DmaIntSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_DmaIntSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_DmaIntSigEn(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_DmaIntSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_DmaIntSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_DmaIntSigEn();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_BufWReadySigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_BufWReadySigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_BufWReadySigEn(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_BufWReadySigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_BufWReadySigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_BufWReadySigEn();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_BufRReadySigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_BufRReadySigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_BufRReadySigEn(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_BufRReadySigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_BufRReadySigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_BufRReadySigEn();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_CardInsertionSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_CardInsertionSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_CardInsertionSigEn(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_CardInsertionSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_CardInsertionSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_CardInsertionSigEn();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_CardRemSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_CardRemSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_CardRemSigEn(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_CardRemSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_CardRemSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_CardRemSigEn();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_CardIntSigEN(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_CardIntSigEN(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_CardIntSigEN(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_CardIntSigEN(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_CardIntSigEN();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_CardIntSigEN();
    }
}
void GH_SDIO_set_TranModeNorIntSigEnReg_FixedTo0(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeNorIntSigEnReg_FixedTo0(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeNorIntSigEnReg_FixedTo0(data);
    }
}
U8   GH_SDIO_get_TranModeNorIntSigEnReg_FixedTo0(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeNorIntSigEnReg_FixedTo0();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeNorIntSigEnReg_FixedTo0();
    }
}

void GH_SDIO_set_ErrIntSigEnBlkCouReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnBlkCouReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnBlkCouReg(data);
    }
}
U32  GH_SDIO_get_ErrIntSigEnBlkCouReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnBlkCouReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnBlkCouReg();
    }
}
void GH_SDIO_set_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn();
    }
}
void GH_SDIO_set_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn();
    }
}
void GH_SDIO_set_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn();
    }
}
void GH_SDIO_set_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn();
    }
}
void GH_SDIO_set_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn();
    }
}
void GH_SDIO_set_ErrIntSigEnBlkCouReg_DataCrcErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnBlkCouReg_DataCrcErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnBlkCouReg_DataCrcErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_DataCrcErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnBlkCouReg_DataCrcErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnBlkCouReg_DataCrcErrSigEn();
    }
}
void GH_SDIO_set_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn();
    }
}
void GH_SDIO_set_ErrIntSigEnBlkCouReg_CurLimitErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnBlkCouReg_CurLimitErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnBlkCouReg_CurLimitErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_CurLimitErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnBlkCouReg_CurLimitErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnBlkCouReg_CurLimitErrSigEn();
    }
}
void GH_SDIO_set_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn();
    }
}
void GH_SDIO_set_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn();
    }
}
void GH_SDIO_set_ErrIntSigEnBlkCouReg_BlkCountForCurTra(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnBlkCouReg_BlkCountForCurTra(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnBlkCouReg_BlkCountForCurTra(data);
    }
}
U16  GH_SDIO_get_ErrIntSigEnBlkCouReg_BlkCountForCurTra(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnBlkCouReg_BlkCountForCurTra();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnBlkCouReg_BlkCountForCurTra();
    }
}

void GH_SDIO_set_BlkSizeNorIntStaEnReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg(data);
    }
}
U32  GH_SDIO_get_BlkSizeNorIntStaEnReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg();
    }
}
void GH_SDIO_set_BlkSizeNorIntStaEnReg_TraBlkSize(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg_TraBlkSize(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg_TraBlkSize(data);
    }
}
U16  GH_SDIO_get_BlkSizeNorIntStaEnReg_TraBlkSize(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg_TraBlkSize();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg_TraBlkSize();
    }
}
void GH_SDIO_set_BlkSizeNorIntStaEnReg_HostSdmaBufSize(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg_HostSdmaBufSize(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg_HostSdmaBufSize(data);
    }
}
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_HostSdmaBufSize(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg_HostSdmaBufSize();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg_HostSdmaBufSize();
    }
}
void GH_SDIO_set_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn(data);
    }
}
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn();
    }
}
void GH_SDIO_set_BlkSizeNorIntStaEnReg_TraCompleteStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg_TraCompleteStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg_TraCompleteStatusEn(data);
    }
}
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_TraCompleteStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg_TraCompleteStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg_TraCompleteStatusEn();
    }
}
void GH_SDIO_set_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn(data);
    }
}
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn();
    }
}
void GH_SDIO_set_BlkSizeNorIntStaEnReg_DmaIntStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg_DmaIntStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg_DmaIntStatusEn(data);
    }
}
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_DmaIntStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg_DmaIntStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg_DmaIntStatusEn();
    }
}
void GH_SDIO_set_BlkSizeNorIntStaEnReg_BufWReadyStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg_BufWReadyStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg_BufWReadyStatusEn(data);
    }
}
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_BufWReadyStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg_BufWReadyStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg_BufWReadyStatusEn();
    }
}
void GH_SDIO_set_BlkSizeNorIntStaEnReg_BufRReadyStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg_BufRReadyStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg_BufRReadyStatusEn(data);
    }
}
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_BufRReadyStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg_BufRReadyStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg_BufRReadyStatusEn();
    }
}
void GH_SDIO_set_BlkSizeNorIntStaEnReg_CardInsertionStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg_CardInsertionStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg_CardInsertionStatusEn(data);
    }
}
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_CardInsertionStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg_CardInsertionStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg_CardInsertionStatusEn();
    }
}
void GH_SDIO_set_BlkSizeNorIntStaEnReg_CardRemStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg_CardRemStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg_CardRemStatusEn(data);
    }
}
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_CardRemStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg_CardRemStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg_CardRemStatusEn();
    }
}
void GH_SDIO_set_BlkSizeNorIntStaEnReg_CardIntStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg_CardIntStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg_CardIntStatusEn(data);
    }
}
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_CardIntStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg_CardIntStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg_CardIntStatusEn();
    }
}
void GH_SDIO_set_BlkSizeNorIntStaEnReg_FixedTo0(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeNorIntStaEnReg_FixedTo0(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeNorIntStaEnReg_FixedTo0(data);
    }
}
U8   GH_SDIO_get_BlkSizeNorIntStaEnReg_FixedTo0(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeNorIntStaEnReg_FixedTo0();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeNorIntStaEnReg_FixedTo0();
    }
}

void GH_SDIO_set_ErrIntStaEnNorIntStaReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg(data);
    }
}
U32  GH_SDIO_get_ErrIntStaEnNorIntStaReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CmdComplete(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdComplete(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdComplete(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CmdComplete(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdComplete();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdComplete();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_TraComplete(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_TraComplete(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_TraComplete(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_TraComplete(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_TraComplete();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_TraComplete();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_BlkGapEvent(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_BlkGapEvent(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BlkGapEvent(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_BlkGapEvent(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_BlkGapEvent();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BlkGapEvent();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_DmaInt(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_DmaInt(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DmaInt(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_DmaInt(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_DmaInt();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DmaInt();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_BufWReady(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_BufWReady(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BufWReady(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_BufWReady(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_BufWReady();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BufWReady();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_BufRReady(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_BufRReady(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BufRReady(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_BufRReady(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_BufRReady();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BufRReady();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CardInsertion(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CardInsertion(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CardInsertion(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CardInsertion(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CardInsertion();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CardInsertion();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CardRemoval(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CardRemoval(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CardRemoval(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CardRemoval(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CardRemoval();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CardRemoval();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_CardInt(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CardInt(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CardInt(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_CardInt(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CardInt();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CardInt();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_BootAckRcv(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_BootAckRcv(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BootAckRcv(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_BootAckRcv(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_BootAckRcv();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BootAckRcv();
    }
}
void GH_SDIO_set_ErrIntStaEnNorIntStaReg_ErrInt(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnNorIntStaReg_ErrInt(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnNorIntStaReg_ErrInt(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnNorIntStaReg_ErrInt(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnNorIntStaReg_ErrInt();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnNorIntStaReg_ErrInt();
    }
}

void GH_SDIO_set_ErrIntStatusCommondReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg(data);
    }
}
U32  GH_SDIO_get_ErrIntStatusCommondReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_CmdTimeoutErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_CmdTimeoutErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_CmdTimeoutErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdTimeoutErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_CmdTimeoutErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_CmdTimeoutErr();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_CmdCrcErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_CmdCrcErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_CmdCrcErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdCrcErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_CmdCrcErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_CmdCrcErr();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_CmdEndBitErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_CmdEndBitErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_CmdEndBitErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdEndBitErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_CmdEndBitErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_CmdEndBitErr();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_CmdIndexErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_CmdIndexErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_CmdIndexErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdIndexErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_CmdIndexErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_CmdIndexErr();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_DataTimeoutErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_DataTimeoutErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_DataTimeoutErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_DataTimeoutErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_DataTimeoutErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_DataTimeoutErr();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_DataCrcErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_DataCrcErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_DataCrcErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_DataCrcErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_DataCrcErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_DataCrcErr();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_DataEndBitErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_DataEndBitErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_DataEndBitErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_DataEndBitErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_DataEndBitErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_DataEndBitErr();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_CurLimitErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_CurLimitErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_CurLimitErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_CurLimitErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_CurLimitErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_CurLimitErr();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_AutoCmd12Err(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_AutoCmd12Err(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_AutoCmd12Err(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_AutoCmd12Err(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_AutoCmd12Err();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_AutoCmd12Err();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_VendorSpecificErrStatus(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_VendorSpecificErrStatus(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_VendorSpecificErrStatus(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_VendorSpecificErrStatus(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_VendorSpecificErrStatus();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_VendorSpecificErrStatus();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_RepTypeSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_RepTypeSelect(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_RepTypeSelect(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_RepTypeSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_RepTypeSelect();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_RepTypeSelect();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_CmdCrcCheckEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_CmdCrcCheckEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_CmdCrcCheckEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdCrcCheckEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_CmdCrcCheckEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_CmdCrcCheckEn();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_CmdIndexCheckEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_CmdIndexCheckEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_CmdIndexCheckEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdIndexCheckEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_CmdIndexCheckEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_CmdIndexCheckEn();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_DataPreSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_DataPreSelect(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_DataPreSelect(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_DataPreSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_DataPreSelect();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_DataPreSelect();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_CmdType(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_CmdType(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_CmdType(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdType(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_CmdType();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_CmdType();
    }
}
void GH_SDIO_set_ErrIntStatusCommondReg_CmdIndex(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusCommondReg_CmdIndex(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusCommondReg_CmdIndex(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusCommondReg_CmdIndex(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusCommondReg_CmdIndex();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusCommondReg_CmdIndex();
    }
}

void GH_SDIO_set_Control01Reg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg(data);
    }
}
U32  GH_SDIO_get_Control01Reg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg();
    }
}
void GH_SDIO_set_Control01Reg_DataTimeoutCounterValue(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_DataTimeoutCounterValue(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_DataTimeoutCounterValue(data);
    }
}
U8   GH_SDIO_get_Control01Reg_DataTimeoutCounterValue(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_DataTimeoutCounterValue();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_DataTimeoutCounterValue();
    }
}
void GH_SDIO_set_Control01Reg_SoftwareResetAll(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_SoftwareResetAll(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_SoftwareResetAll(data);
    }
}
U8   GH_SDIO_get_Control01Reg_SoftwareResetAll(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_SoftwareResetAll();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_SoftwareResetAll();
    }
}
void GH_SDIO_set_Control01Reg_SoftwareResetCmdLine(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_SoftwareResetCmdLine(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_SoftwareResetCmdLine(data);
    }
}
U8   GH_SDIO_get_Control01Reg_SoftwareResetCmdLine(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_SoftwareResetCmdLine();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_SoftwareResetCmdLine();
    }
}
void GH_SDIO_set_Control01Reg_SoftwareResetDatLine(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_SoftwareResetDatLine(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_SoftwareResetDatLine(data);
    }
}
U8   GH_SDIO_get_Control01Reg_SoftwareResetDatLine(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_SoftwareResetDatLine();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_SoftwareResetDatLine();
    }
}
void GH_SDIO_set_Control01Reg_InternalClkEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_InternalClkEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_InternalClkEn(data);
    }
}
U8   GH_SDIO_get_Control01Reg_InternalClkEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_InternalClkEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_InternalClkEn();
    }
}
void GH_SDIO_set_Control01Reg_InternalClkStable(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_InternalClkStable(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_InternalClkStable(data);
    }
}
U8   GH_SDIO_get_Control01Reg_InternalClkStable(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_InternalClkStable();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_InternalClkStable();
    }
}
void GH_SDIO_set_Control01Reg_SdClkEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_SdClkEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_SdClkEn(data);
    }
}
U8   GH_SDIO_get_Control01Reg_SdClkEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_SdClkEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_SdClkEn();
    }
}
void GH_SDIO_set_Control01Reg_SdclkFreSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_SdclkFreSelect(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_SdclkFreSelect(data);
    }
}
U8   GH_SDIO_get_Control01Reg_SdclkFreSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_SdclkFreSelect();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_SdclkFreSelect();
    }
}

U32  GH_SDIO_get_Resp0Reg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Resp0Reg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Resp0Reg();
    }
}

U32  GH_SDIO_get_Resp1Reg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Resp1Reg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Resp1Reg();
    }
}

U32  GH_SDIO_get_Resp2Reg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Resp2Reg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Resp2Reg();
    }
}

U32  GH_SDIO_get_Resp3Reg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Resp3Reg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Resp3Reg();
    }
}

void GH_SDIO_set_Control00Reg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg(data);
    }
}
U32  GH_SDIO_get_Control00Reg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg();
    }
}
void GH_SDIO_set_Control00Reg_LedControl(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_LedControl(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_LedControl(data);
    }
}
U8   GH_SDIO_get_Control00Reg_LedControl(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_LedControl();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_LedControl();
    }
}
void GH_SDIO_set_Control00Reg_DataTraWidth(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_DataTraWidth(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_DataTraWidth(data);
    }
}
U8   GH_SDIO_get_Control00Reg_DataTraWidth(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_DataTraWidth();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_DataTraWidth();
    }
}
void GH_SDIO_set_Control00Reg_HostSpeedEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_HostSpeedEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_HostSpeedEn(data);
    }
}
U8   GH_SDIO_get_Control00Reg_HostSpeedEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_HostSpeedEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_HostSpeedEn();
    }
}
void GH_SDIO_set_Control00Reg_Sd8BitMode(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_Sd8BitMode(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_Sd8BitMode(data);
    }
}
U8   GH_SDIO_get_Control00Reg_Sd8BitMode(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_Sd8BitMode();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_Sd8BitMode();
    }
}
void GH_SDIO_set_Control00Reg_CardDetectTestLevel(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_CardDetectTestLevel(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_CardDetectTestLevel(data);
    }
}
U8   GH_SDIO_get_Control00Reg_CardDetectTestLevel(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_CardDetectTestLevel();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_CardDetectTestLevel();
    }
}
void GH_SDIO_set_Control00Reg_CardDetectSigDet(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_CardDetectSigDet(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_CardDetectSigDet(data);
    }
}
U8   GH_SDIO_get_Control00Reg_CardDetectSigDet(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_CardDetectSigDet();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_CardDetectSigDet();
    }
}
void GH_SDIO_set_Control00Reg_SdBusPower(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_SdBusPower(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_SdBusPower(data);
    }
}
U8   GH_SDIO_get_Control00Reg_SdBusPower(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_SdBusPower();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_SdBusPower();
    }
}
void GH_SDIO_set_Control00Reg_SdBusVoltageSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_SdBusVoltageSelect(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_SdBusVoltageSelect(data);
    }
}
U8   GH_SDIO_get_Control00Reg_SdBusVoltageSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_SdBusVoltageSelect();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_SdBusVoltageSelect();
    }
}
void GH_SDIO_set_Control00Reg_StopAtBlkGapReq(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_StopAtBlkGapReq(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_StopAtBlkGapReq(data);
    }
}
U8   GH_SDIO_get_Control00Reg_StopAtBlkGapReq(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_StopAtBlkGapReq();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_StopAtBlkGapReq();
    }
}
void GH_SDIO_set_Control00Reg_ContinueReq(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_ContinueReq(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_ContinueReq(data);
    }
}
U8   GH_SDIO_get_Control00Reg_ContinueReq(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_ContinueReq();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_ContinueReq();
    }
}
void GH_SDIO_set_Control00Reg_RWaitControl(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_RWaitControl(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_RWaitControl(data);
    }
}
U8   GH_SDIO_get_Control00Reg_RWaitControl(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_RWaitControl();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_RWaitControl();
    }
}
void GH_SDIO_set_Control00Reg_IntAtBlkGap(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_IntAtBlkGap(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_IntAtBlkGap(data);
    }
}
U8   GH_SDIO_get_Control00Reg_IntAtBlkGap(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_IntAtBlkGap();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_IntAtBlkGap();
    }
}
void GH_SDIO_set_Control00Reg_DriveCcsd(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_DriveCcsd(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_DriveCcsd(data);
    }
}
U8   GH_SDIO_get_Control00Reg_DriveCcsd(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_DriveCcsd();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_DriveCcsd();
    }
}
void GH_SDIO_set_Control00Reg_SpiMode(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_SpiMode(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_SpiMode(data);
    }
}
U8   GH_SDIO_get_Control00Reg_SpiMode(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_SpiMode();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_SpiMode();
    }
}
void GH_SDIO_set_Control00Reg_BootEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_BootEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_BootEn(data);
    }
}
U8   GH_SDIO_get_Control00Reg_BootEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_BootEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_BootEn();
    }
}
void GH_SDIO_set_Control00Reg_AltBootEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_AltBootEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_AltBootEn(data);
    }
}
U8   GH_SDIO_get_Control00Reg_AltBootEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_AltBootEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_AltBootEn();
    }
}
void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardInt(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardInt(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardInt(data);
    }
}
U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardInt(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardInt();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardInt();
    }
}
void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardIns(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardIns(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardIns(data);
    }
}
U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardIns(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardIns();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardIns();
    }
}
void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardRem(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardRem(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardRem(data);
    }
}
U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardRem(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardRem();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardRem();
    }
}

U32  GH_SDIO_get_PresentStateReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg();
    }
}
U8   GH_SDIO_get_PresentStateReg_CmdInhibitCmd(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_CmdInhibitCmd();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_CmdInhibitCmd();
    }
}
U8   GH_SDIO_get_PresentStateReg_CmdInhibitData(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_CmdInhibitData();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_CmdInhibitData();
    }
}
U8   GH_SDIO_get_PresentStateReg_DataLineActive(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_DataLineActive();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_DataLineActive();
    }
}
U8   GH_SDIO_get_PresentStateReg_WTraActive(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_WTraActive();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_WTraActive();
    }
}
U8   GH_SDIO_get_PresentStateReg_RTraActive(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_RTraActive();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_RTraActive();
    }
}
U8   GH_SDIO_get_PresentStateReg_BufWEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_BufWEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_BufWEn();
    }
}
U8   GH_SDIO_get_PresentStateReg_BufREn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_BufREn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_BufREn();
    }
}
U8   GH_SDIO_get_PresentStateReg_CardInserted(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_CardInserted();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_CardInserted();
    }
}
U8   GH_SDIO_get_PresentStateReg_CardStateStable(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_CardStateStable();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_CardStateStable();
    }
}
U8   GH_SDIO_get_PresentStateReg_CardDetectPinLevel(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_CardDetectPinLevel();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_CardDetectPinLevel();
    }
}
U8   GH_SDIO_get_PresentStateReg_WProSwiPinLevel(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_WProSwiPinLevel();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_WProSwiPinLevel();
    }
}
U8   GH_SDIO_get_PresentStateReg_Data03LineSigLevel(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_Data03LineSigLevel();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_Data03LineSigLevel();
    }
}
U8   GH_SDIO_get_PresentStateReg_CmdLineSigLevel(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_CmdLineSigLevel();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_CmdLineSigLevel();
    }
}
U8   GH_SDIO_get_PresentStateReg_Data47LineSigLevel(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_Data47LineSigLevel();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_Data47LineSigLevel();
    }
}

void GH_SDIO_set_ArgReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ArgReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ArgReg(data);
    }
}
U32  GH_SDIO_get_ArgReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ArgReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ArgReg();
    }
}

U32  GH_SDIO_get_CapReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg();
    }
}
U8   GH_SDIO_get_CapReg_TimeoutClkFre(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_TimeoutClkFre();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_TimeoutClkFre();
    }
}
U8   GH_SDIO_get_CapReg_TimeoutClkUnit(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_TimeoutClkUnit();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_TimeoutClkUnit();
    }
}
U8   GH_SDIO_get_CapReg_BaseClkFreForSdClk(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_BaseClkFreForSdClk();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_BaseClkFreForSdClk();
    }
}
U8   GH_SDIO_get_CapReg_MaxBlkLen(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_MaxBlkLen();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_MaxBlkLen();
    }
}
U8   GH_SDIO_get_CapReg_ExtendedMediaBusSup(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_ExtendedMediaBusSup();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_ExtendedMediaBusSup();
    }
}
U8   GH_SDIO_get_CapReg_HighSpeedSup(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_HighSpeedSup();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_HighSpeedSup();
    }
}
U8   GH_SDIO_get_CapReg_SdmaSup(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_SdmaSup();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_SdmaSup();
    }
}
U8   GH_SDIO_get_CapReg_SusResSup(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_SusResSup();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_SusResSup();
    }
}
U8   GH_SDIO_get_CapReg_VoltageSup33v(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_VoltageSup33v();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_VoltageSup33v();
    }
}
U8   GH_SDIO_get_CapReg_VoltageSup30v(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_VoltageSup30v();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_VoltageSup30v();
    }
}
U8   GH_SDIO_get_CapReg_VoltageSup18v(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_VoltageSup18v();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_VoltageSup18v();
    }
}
U8   GH_SDIO_get_CapReg_IntMode(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_IntMode();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_IntMode();
    }
}

U32  GH_SDIO_get_AutoCmd12ErrStatusReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg();
    }
}
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe();
    }
}
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr();
    }
}
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr();
    }
}
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr();
    }
}
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr();
    }
}
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err();
    }
}

void GH_SDIO_set_BufferDataPortReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BufferDataPortReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BufferDataPortReg(data);
    }
}
U32  GH_SDIO_get_BufferDataPortReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BufferDataPortReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BufferDataPortReg();
    }
}

void GH_SDIO_set_MaxCurCapReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_MaxCurCapReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_MaxCurCapReg(data);
    }
}
U32  GH_SDIO_get_MaxCurCapReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_MaxCurCapReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_MaxCurCapReg();
    }
}
void GH_SDIO_set_MaxCurCapReg_MaxCurFor33v(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_MaxCurCapReg_MaxCurFor33v(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_MaxCurCapReg_MaxCurFor33v(data);
    }
}
U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor33v(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_MaxCurCapReg_MaxCurFor33v();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_MaxCurCapReg_MaxCurFor33v();
    }
}
void GH_SDIO_set_MaxCurCapReg_MaxCurFor30v(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_MaxCurCapReg_MaxCurFor30v(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_MaxCurCapReg_MaxCurFor30v(data);
    }
}
U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor30v(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_MaxCurCapReg_MaxCurFor30v();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_MaxCurCapReg_MaxCurFor30v();
    }
}
void GH_SDIO_set_MaxCurCapReg_MaxCurFor18v(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_MaxCurCapReg_MaxCurFor18v(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_MaxCurCapReg_MaxCurFor18v(data);
    }
}
U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor18v(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_MaxCurCapReg_MaxCurFor18v();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_MaxCurCapReg_MaxCurFor18v();
    }
}

U32  GH_SDIO_get_SlotIntStatusReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SlotIntStatusReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SlotIntStatusReg();
    }
}
U8   GH_SDIO_get_SlotIntStatusReg_IntSigForEachSlot(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SlotIntStatusReg_IntSigForEachSlot();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SlotIntStatusReg_IntSigForEachSlot();
    }
}
U8   GH_SDIO_get_SlotIntStatusReg_SpecifiVerNum(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SlotIntStatusReg_SpecifiVerNum();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SlotIntStatusReg_SpecifiVerNum();
    }
}
U8   GH_SDIO_get_SlotIntStatusReg_VendorVerNum(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SlotIntStatusReg_VendorVerNum();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SlotIntStatusReg_VendorVerNum();
    }
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_SDIO_init(void)
{
    GH_SDIO0_init();
    GH_SDIO1_init();
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

