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
    return -1;
}

void GH_SDIO_set_TranModeReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeReg(data);
    }
}

U16  GH_SDIO_get_TranModeReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeReg();
    }
    return -1;
}
void GH_SDIO_set_TranModeReg_BlkCountEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeReg_BlkCountEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeReg_BlkCountEn(data);
    }
}
U8   GH_SDIO_get_TranModeReg_BlkCountEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeReg_BlkCountEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeReg_BlkCountEn();
    }
    return -1;
}
void GH_SDIO_set_TranModeReg_AutoCmd12En(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeReg_AutoCmd12En(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeReg_AutoCmd12En(data);
    }
}
U8   GH_SDIO_get_TranModeReg_AutoCmd12En(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeReg_AutoCmd12En();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeReg_AutoCmd12En();
    }
    return -1;
}
void GH_SDIO_set_TranModeReg_DmaEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeReg_DmaEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeReg_DmaEn(data);
    }
}
U8   GH_SDIO_get_TranModeReg_DmaEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeReg_DmaEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeReg_DmaEn();
    }
    return -1;
}
void GH_SDIO_set_TranModeReg_MSBlkSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeReg_MSBlkSelect(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeReg_MSBlkSelect(data);
    }
}
U8   GH_SDIO_get_TranModeReg_MSBlkSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeReg_MSBlkSelect();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeReg_MSBlkSelect();
    }
    return -1;
}
void GH_SDIO_set_TranModeReg_DataTraDirSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeReg_DataTraDirSelect(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeReg_DataTraDirSelect(data);
    }
}
U8   GH_SDIO_get_TranModeReg_DataTraDirSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeReg_DataTraDirSelect();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeReg_DataTraDirSelect();
    }
    return -1;
}

void GH_SDIO_set_NorIntSigEnReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg(data);
    }
}
U16  GH_SDIO_get_NorIntSigEnReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg();
    }
    return -1;
}
void GH_SDIO_set_NorIntSigEnReg_CmdCompleteSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_CmdCompleteSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_CmdCompleteSigEn(data);
    }
}
U8   GH_SDIO_get_NorIntSigEnReg_CmdCompleteSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_CmdCompleteSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_CmdCompleteSigEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntSigEnReg_TraCompleteSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_TraCompleteSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_TraCompleteSigEn(data);
    }
}
U8   GH_SDIO_get_NorIntSigEnReg_TraCompleteSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_TraCompleteSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_TraCompleteSigEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntSigEnReg_BlkGapEveSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_BlkGapEveSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_BlkGapEveSigEn(data);
    }
}
U8   GH_SDIO_get_NorIntSigEnReg_BlkGapEveSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_BlkGapEveSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_BlkGapEveSigEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntSigEnReg_DmaIntSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_DmaIntSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_DmaIntSigEn(data);
    }
}
U8   GH_SDIO_get_NorIntSigEnReg_DmaIntSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_DmaIntSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_DmaIntSigEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntSigEnReg_BufWReadySigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_BufWReadySigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_BufWReadySigEn(data);
    }
}
U8   GH_SDIO_get_NorIntSigEnReg_BufWReadySigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_BufWReadySigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_BufWReadySigEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntSigEnReg_BufRReadySigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_BufRReadySigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_BufRReadySigEn(data);
    }
}
U8   GH_SDIO_get_NorIntSigEnReg_BufRReadySigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_BufRReadySigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_BufRReadySigEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntSigEnReg_CardInsertionSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_CardInsertionSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_CardInsertionSigEn(data);
    }
}
U8   GH_SDIO_get_NorIntSigEnReg_CardInsertionSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_CardInsertionSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_CardInsertionSigEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntSigEnReg_CardRemSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_CardRemSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_CardRemSigEn(data);
    }
}
U8   GH_SDIO_get_NorIntSigEnReg_CardRemSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_CardRemSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_CardRemSigEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntSigEnReg_CardIntSigEN(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_CardIntSigEN(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_CardIntSigEN(data);
    }
}
U8   GH_SDIO_get_NorIntSigEnReg_CardIntSigEN(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_CardIntSigEN();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_CardIntSigEN();
    }
    return -1;
}
void GH_SDIO_set_NorIntSigEnReg_FixedTo0(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_FixedTo0(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_FixedTo0(data);
    }
}
U8   GH_SDIO_get_NorIntSigEnReg_FixedTo0(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_FixedTo0();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_FixedTo0();
    }
    return -1;
}

void GH_SDIO_set_ErrIntSigEnReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnReg(data);
    }
}
U16  GH_SDIO_get_ErrIntSigEnReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnReg();
    }
    return -1;
}
void GH_SDIO_set_ErrIntSigEnReg_CmdTimeoutErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnReg_CmdTimeoutErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnReg_CmdTimeoutErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnReg_CmdTimeoutErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnReg_CmdTimeoutErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnReg_CmdTimeoutErrSigEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntSigEnReg_CmdEndBitErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnReg_CmdEndBitErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnReg_CmdEndBitErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnReg_CmdEndBitErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnReg_CmdEndBitErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnReg_CmdEndBitErrSigEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntSigEnReg_CmdIndexErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnReg_CmdIndexErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnReg_CmdIndexErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnReg_CmdIndexErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnReg_CmdIndexErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnReg_CmdIndexErrSigEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntSigEnReg_DataTimeoutErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnReg_DataTimeoutErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnReg_DataTimeoutErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnReg_DataTimeoutErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnReg_DataTimeoutErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnReg_DataTimeoutErrSigEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntSigEnReg_CmdCrcErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnReg_CmdCrcErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnReg_CmdCrcErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnReg_CmdCrcErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnReg_CmdCrcErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnReg_CmdCrcErrSigEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntSigEnReg_DataCrcErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnReg_DataCrcErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnReg_DataCrcErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnReg_DataCrcErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnReg_DataCrcErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnReg_DataCrcErrSigEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntSigEnReg_DataEndBitErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnReg_DataEndBitErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnReg_DataEndBitErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnReg_DataEndBitErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnReg_DataEndBitErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnReg_DataEndBitErrSigEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntSigEnReg_CurLimitErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnReg_CurLimitErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnReg_CurLimitErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnReg_CurLimitErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnReg_CurLimitErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnReg_CurLimitErrSigEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntSigEnReg_AutoCmd12ErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnReg_AutoCmd12ErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnReg_AutoCmd12ErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnReg_AutoCmd12ErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnReg_AutoCmd12ErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnReg_AutoCmd12ErrSigEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntSigEnReg_VendorSpecificErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEnReg_VendorSpecificErrSigEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEnReg_VendorSpecificErrSigEn(data);
    }
}
U8   GH_SDIO_get_ErrIntSigEnReg_VendorSpecificErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEnReg_VendorSpecificErrSigEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEnReg_VendorSpecificErrSigEn();
    }
    return -1;
}

void GH_SDIO_set_BlkCouReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkCouReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkCouReg(data);
    }
}
U16  GH_SDIO_get_BlkCouReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkCouReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkCouReg();
    }
    return -1;
}
void GH_SDIO_set_BlkCouReg_BlkCountForCurTra(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkCouReg_BlkCountForCurTra(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkCouReg_BlkCountForCurTra(data);
    }
}
U16  GH_SDIO_get_BlkCouReg_BlkCountForCurTra(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkCouReg_BlkCountForCurTra();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkCouReg_BlkCountForCurTra();
    }
    return -1;
}

void GH_SDIO_set_BlkSizeReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeReg(data);
    }
}
U16  GH_SDIO_get_BlkSizeReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeReg();
    }
    return -1;
}
void GH_SDIO_set_BlkSizeReg_TraBlkSize(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeReg_TraBlkSize(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeReg_TraBlkSize(data);
    }
}
U16  GH_SDIO_get_BlkSizeReg_TraBlkSize(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeReg_TraBlkSize();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeReg_TraBlkSize();
    }
    return -1;
}
void GH_SDIO_set_BlkSizeReg_HostSdmaBufSize(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeReg_HostSdmaBufSize(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeReg_HostSdmaBufSize(data);
    }
}
U8   GH_SDIO_get_BlkSizeReg_HostSdmaBufSize(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeReg_HostSdmaBufSize();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeReg_HostSdmaBufSize();
    }
    return -1;
}

void GH_SDIO_set_NorIntStaEnReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg(data);
    }
}
U16  GH_SDIO_get_NorIntStaEnReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaEnReg_CmdCompleteStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_CmdCompleteStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_CmdCompleteStatusEn(data);
    }
}
U8   GH_SDIO_get_NorIntStaEnReg_CmdCompleteStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_CmdCompleteStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_CmdCompleteStatusEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaEnReg_TraCompleteStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_TraCompleteStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_TraCompleteStatusEn(data);
    }
}
U8   GH_SDIO_get_NorIntStaEnReg_TraCompleteStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_TraCompleteStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_TraCompleteStatusEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaEnReg_BlkGapEveStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_BlkGapEveStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_BlkGapEveStatusEn(data);
    }
}
U8   GH_SDIO_get_NorIntStaEnReg_BlkGapEveStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_BlkGapEveStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_BlkGapEveStatusEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaEnReg_DmaIntStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_DmaIntStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_DmaIntStatusEn(data);
    }
}
U8   GH_SDIO_get_NorIntStaEnReg_DmaIntStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_DmaIntStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_DmaIntStatusEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaEnReg_BufWReadyStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_BufWReadyStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_BufWReadyStatusEn(data);
    }
}
U8   GH_SDIO_get_NorIntStaEnReg_BufWReadyStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_BufWReadyStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_BufWReadyStatusEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaEnReg_BufRReadyStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_BufRReadyStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_BufRReadyStatusEn(data);
    }
}
U8   GH_SDIO_get_NorIntStaEnReg_BufRReadyStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_BufRReadyStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_BufRReadyStatusEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaEnReg_CardInsertionStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_CardInsertionStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_CardInsertionStatusEn(data);
    }
}
U8   GH_SDIO_get_NorIntStaEnReg_CardInsertionStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_CardInsertionStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_CardInsertionStatusEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaEnReg_CardRemStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_CardRemStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_CardRemStatusEn(data);
    }
}
U8   GH_SDIO_get_NorIntStaEnReg_CardRemStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_CardRemStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_CardRemStatusEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaEnReg_CardIntStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_CardIntStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_CardIntStatusEn(data);
    }
}
U8   GH_SDIO_get_NorIntStaEnReg_CardIntStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_CardIntStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_CardIntStatusEn();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaEnReg_FixedTo0(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_FixedTo0(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_FixedTo0(data);
    }
}
U8   GH_SDIO_get_NorIntStaEnReg_FixedTo0(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_FixedTo0();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_FixedTo0();
    }
    return -1;
}

void GH_SDIO_set_ErrIntStaEnReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg(data);
    }
}
U16  GH_SDIO_get_ErrIntStaEnReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStaEnReg_CmdEndBitErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_CmdEndBitErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_CmdEndBitErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnReg_CmdEndBitErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_CmdEndBitErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_CmdEndBitErrStatusEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStaEnReg_CmdCrcErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_CmdCrcErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_CmdCrcErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnReg_CmdCrcErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_CmdCrcErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_CmdCrcErrStatusEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStaEnReg_CmdIndexErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_CmdIndexErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_CmdIndexErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnReg_CmdIndexErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_CmdIndexErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_CmdIndexErrStatusEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStaEnReg_DataCrcErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_DataCrcErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_DataCrcErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnReg_DataCrcErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_DataCrcErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_DataCrcErrStatusEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStaEnReg_DataTimeoutErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_DataTimeoutErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_DataTimeoutErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnReg_DataTimeoutErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_DataTimeoutErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_DataTimeoutErrStatusEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStaEnReg_DataEndBitErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_DataEndBitErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_DataEndBitErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnReg_DataEndBitErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_DataEndBitErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_DataEndBitErrStatusEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStaEnReg_CurLimitErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_CurLimitErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_CurLimitErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnReg_CurLimitErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_CurLimitErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_CurLimitErrStatusEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStaEnReg_VendorSpecificErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_VendorSpecificErrStatusEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_VendorSpecificErrStatusEn(data);
    }
}
U8   GH_SDIO_get_ErrIntStaEnReg_VendorSpecificErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_VendorSpecificErrStatusEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_VendorSpecificErrStatusEn();
    }
    return -1;
}

void GH_SDIO_set_NorIntStaReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg(data);
    }
}
U16  GH_SDIO_get_NorIntStaReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaReg_CmdComplete(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_CmdComplete(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_CmdComplete(data);
    }
}
U8   GH_SDIO_get_NorIntStaReg_CmdComplete(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_CmdComplete();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_CmdComplete();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaReg_BlkGapEvent(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_BlkGapEvent(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_BlkGapEvent(data);
    }
}
U8   GH_SDIO_get_NorIntStaReg_BlkGapEvent(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_BlkGapEvent();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_BlkGapEvent();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaReg_DmaInt(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_DmaInt(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_DmaInt(data);
    }
}
U8   GH_SDIO_get_NorIntStaReg_DmaInt(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_DmaInt();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_DmaInt();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaReg_TraComplete(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_TraComplete(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_TraComplete(data);
    }
}
U8   GH_SDIO_get_NorIntStaReg_TraComplete(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_TraComplete();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_TraComplete();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaReg_BufWReady(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_BufWReady(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_BufWReady(data);
    }
}
U8   GH_SDIO_get_NorIntStaReg_BufWReady(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_BufWReady();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_BufWReady();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaReg_CardInsertion(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_CardInsertion(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_CardInsertion(data);
    }
}
U8   GH_SDIO_get_NorIntStaReg_CardInsertion(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_CardInsertion();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_CardInsertion();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaReg_BufRReady(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_BufRReady(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_BufRReady(data);
    }
}
U8   GH_SDIO_get_NorIntStaReg_BufRReady(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_BufRReady();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_BufRReady();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaReg_CardRemoval(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_CardRemoval(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_CardRemoval(data);
    }
}
U8   GH_SDIO_get_NorIntStaReg_CardRemoval(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_CardRemoval();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_CardRemoval();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaReg_CardInt(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_CardInt(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_CardInt(data);
    }
}
U8   GH_SDIO_get_NorIntStaReg_CardInt(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_CardInt();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_CardInt();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaReg_BootAckRcv(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_BootAckRcv(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_BootAckRcv(data);
    }
}
U8   GH_SDIO_get_NorIntStaReg_BootAckRcv(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_BootAckRcv();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_BootAckRcv();
    }
    return -1;
}
void GH_SDIO_set_NorIntStaReg_ErrInt(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_ErrInt(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_ErrInt(data);
    }
}
U8   GH_SDIO_get_NorIntStaReg_ErrInt(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_ErrInt();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_ErrInt();
    }
    return -1;
}

void GH_SDIO_set_ErrIntStatusReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusReg(data);
    }
}
U16  GH_SDIO_get_ErrIntStatusReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusReg();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStatusReg_CmdTimeoutErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusReg_CmdTimeoutErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusReg_CmdTimeoutErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusReg_CmdTimeoutErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusReg_CmdTimeoutErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusReg_CmdTimeoutErr();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStatusReg_CmdCrcErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusReg_CmdCrcErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusReg_CmdCrcErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusReg_CmdCrcErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusReg_CmdCrcErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusReg_CmdCrcErr();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStatusReg_CmdEndBitErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusReg_CmdEndBitErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusReg_CmdEndBitErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusReg_CmdEndBitErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusReg_CmdEndBitErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusReg_CmdEndBitErr();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStatusReg_CmdIndexErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusReg_CmdIndexErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusReg_CmdIndexErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusReg_CmdIndexErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusReg_CmdIndexErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusReg_CmdIndexErr();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStatusReg_DataTimeoutErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusReg_DataTimeoutErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusReg_DataTimeoutErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusReg_DataTimeoutErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusReg_DataTimeoutErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusReg_DataTimeoutErr();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStatusReg_DataCrcErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusReg_DataCrcErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusReg_DataCrcErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusReg_DataCrcErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusReg_DataCrcErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusReg_DataCrcErr();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStatusReg_DataEndBitErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusReg_DataEndBitErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusReg_DataEndBitErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusReg_DataEndBitErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusReg_DataEndBitErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusReg_DataEndBitErr();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStatusReg_CurLimitErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusReg_CurLimitErr(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusReg_CurLimitErr(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusReg_CurLimitErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusReg_CurLimitErr();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusReg_CurLimitErr();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStatusReg_AutoCmd12Err(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusReg_AutoCmd12Err(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusReg_AutoCmd12Err(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusReg_AutoCmd12Err(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusReg_AutoCmd12Err();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusReg_AutoCmd12Err();
    }
    return -1;
}
void GH_SDIO_set_ErrIntStatusReg_VendorSpecificErrStatus(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStatusReg_VendorSpecificErrStatus(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStatusReg_VendorSpecificErrStatus(data);
    }
}
U8   GH_SDIO_get_ErrIntStatusReg_VendorSpecificErrStatus(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStatusReg_VendorSpecificErrStatus();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStatusReg_VendorSpecificErrStatus();
    }
    return -1;
}

void GH_SDIO_set_CommondReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CommondReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CommondReg(data);
    }
}
U16  GH_SDIO_get_CommondReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CommondReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CommondReg();
    }
    return -1;
}
void GH_SDIO_set_CommondReg_RepTypeSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CommondReg_RepTypeSelect(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CommondReg_RepTypeSelect(data);
    }
}
U8   GH_SDIO_get_CommondReg_RepTypeSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CommondReg_RepTypeSelect();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CommondReg_RepTypeSelect();
    }
    return -1;
}
void GH_SDIO_set_CommondReg_CmdCrcCheckEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CommondReg_CmdCrcCheckEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CommondReg_CmdCrcCheckEn(data);
    }
}
U8   GH_SDIO_get_CommondReg_CmdCrcCheckEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CommondReg_CmdCrcCheckEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CommondReg_CmdCrcCheckEn();
    }
    return -1;
}
void GH_SDIO_set_CommondReg_DataPreSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CommondReg_DataPreSelect(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CommondReg_DataPreSelect(data);
    }
}
U8   GH_SDIO_get_CommondReg_DataPreSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CommondReg_DataPreSelect();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CommondReg_DataPreSelect();
    }
    return -1;
}
void GH_SDIO_set_CommondReg_CmdIndexCheckEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CommondReg_CmdIndexCheckEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CommondReg_CmdIndexCheckEn(data);
    }
}
U8   GH_SDIO_get_CommondReg_CmdIndexCheckEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CommondReg_CmdIndexCheckEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CommondReg_CmdIndexCheckEn();
    }
    return -1;
}
void GH_SDIO_set_CommondReg_CmdType(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CommondReg_CmdType(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CommondReg_CmdType(data);
    }
}
U8   GH_SDIO_get_CommondReg_CmdType(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CommondReg_CmdType();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CommondReg_CmdType();
    }
    return -1;
}
void GH_SDIO_set_CommondReg_CmdIndex(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CommondReg_CmdIndex(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CommondReg_CmdIndex(data);
    }
}
U8   GH_SDIO_get_CommondReg_CmdIndex(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CommondReg_CmdIndex();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CommondReg_CmdIndex();
    }
    return -1;
}

void GH_SDIO_set_SoftResetReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_SoftResetReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_SoftResetReg(data);
    }
}
U16  GH_SDIO_get_SoftResetReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SoftResetReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SoftResetReg();
    }
    return -1;
}
void GH_SDIO_set_SoftResetReg_DataTimeoutCounterValue(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_SoftResetReg_DataTimeoutCounterValue(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_SoftResetReg_DataTimeoutCounterValue(data);
    }
}
U8   GH_SDIO_get_SoftResetReg_DataTimeoutCounterValue(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SoftResetReg_DataTimeoutCounterValue();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SoftResetReg_DataTimeoutCounterValue();
    }
    return -1;
}
void GH_SDIO_set_SoftResetReg_SoftwareResetCmdLine(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_SoftResetReg_SoftwareResetCmdLine(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_SoftResetReg_SoftwareResetCmdLine(data);
    }
}
U8   GH_SDIO_get_SoftResetReg_SoftwareResetCmdLine(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SoftResetReg_SoftwareResetCmdLine();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SoftResetReg_SoftwareResetCmdLine();
    }
    return -1;
}
void GH_SDIO_set_SoftResetReg_SoftwareResetAll(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_SoftResetReg_SoftwareResetAll(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_SoftResetReg_SoftwareResetAll(data);
    }
}
U8   GH_SDIO_get_SoftResetReg_SoftwareResetAll(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SoftResetReg_SoftwareResetAll();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SoftResetReg_SoftwareResetAll();
    }
    return -1;
}
void GH_SDIO_set_SoftResetReg_SoftwareResetDatLine(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_SoftResetReg_SoftwareResetDatLine(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_SoftResetReg_SoftwareResetDatLine(data);
    }
}
U8   GH_SDIO_get_SoftResetReg_SoftwareResetDatLine(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SoftResetReg_SoftwareResetDatLine();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SoftResetReg_SoftwareResetDatLine();
    }
    return -1;
}

void GH_SDIO_set_ClkControlReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ClkControlReg(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ClkControlReg(data);
    }
}
U16  GH_SDIO_get_ClkControlReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ClkControlReg();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ClkControlReg();
    }
    return -1;
}
void GH_SDIO_set_ClkControlReg_InternalClkEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ClkControlReg_InternalClkEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ClkControlReg_InternalClkEn(data);
    }
}
U8   GH_SDIO_get_ClkControlReg_InternalClkEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ClkControlReg_InternalClkEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ClkControlReg_InternalClkEn();
    }
    return -1;
}
void GH_SDIO_set_ClkControlReg_InternalClkStable(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ClkControlReg_InternalClkStable(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ClkControlReg_InternalClkStable(data);
    }
}
U8   GH_SDIO_get_ClkControlReg_InternalClkStable(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ClkControlReg_InternalClkStable();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ClkControlReg_InternalClkStable();
    }
    return -1;
}
void GH_SDIO_set_ClkControlReg_SdClkEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ClkControlReg_SdClkEn(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ClkControlReg_SdClkEn(data);
    }
}
U8   GH_SDIO_get_ClkControlReg_SdClkEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ClkControlReg_SdClkEn();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ClkControlReg_SdClkEn();
    }
    return -1;
}
void GH_SDIO_set_ClkControlReg_SdclkFreSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ClkControlReg_SdclkFreSelect(data);
    }
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ClkControlReg_SdclkFreSelect(data);
    }
}
U8   GH_SDIO_get_ClkControlReg_SdclkFreSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ClkControlReg_SdclkFreSelect();
    }
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ClkControlReg_SdclkFreSelect();
    }
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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
    return -1;
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

