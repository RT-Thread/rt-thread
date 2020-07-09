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
#include "gtypes.h"
#include "gh_sdio_all.h"

/*----------------------------------------------------------------------------*/
/* register SDIO_SysAddrReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_SysAddrReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_SysAddrReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_SysAddrReg(data);
    }
#endif
}
GH_INLINE U32  GH_SDIO_get_SysAddrReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SysAddrReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SysAddrReg();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_TranModeReg (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_TranModeReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeReg(data);
    }
#endif
}
GH_INLINE U16  GH_SDIO_get_TranModeReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_TranModeReg_BlkCountEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeReg_BlkCountEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeReg_BlkCountEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_TranModeReg_BlkCountEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeReg_BlkCountEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeReg_BlkCountEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_TranModeReg_AutoCmd12En(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeReg_AutoCmd12En(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeReg_AutoCmd12En(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_TranModeReg_AutoCmd12En(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeReg_AutoCmd12En();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeReg_AutoCmd12En();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_TranModeReg_DmaEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeReg_DmaEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeReg_DmaEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_TranModeReg_DmaEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeReg_DmaEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeReg_DmaEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_TranModeReg_MSBlkSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeReg_MSBlkSelect(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeReg_MSBlkSelect(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_TranModeReg_MSBlkSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeReg_MSBlkSelect();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeReg_MSBlkSelect();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_TranModeReg_DataTraDirSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_TranModeReg_DataTraDirSelect(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_TranModeReg_DataTraDirSelect(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_TranModeReg_DataTraDirSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_TranModeReg_DataTraDirSelect();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_TranModeReg_DataTraDirSelect();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_NorIntSigEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_NorIntSigEnReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg(data);
    }
#endif
}
GH_INLINE U16  GH_SDIO_get_NorIntSigEnReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntSigEnReg_CmdCompleteSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_CmdCompleteSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_CmdCompleteSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntSigEnReg_CmdCompleteSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_CmdCompleteSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_CmdCompleteSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntSigEnReg_TraCompleteSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_TraCompleteSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_TraCompleteSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntSigEnReg_TraCompleteSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_TraCompleteSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_TraCompleteSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntSigEnReg_BlkGapEveSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_BlkGapEveSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_BlkGapEveSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntSigEnReg_BlkGapEveSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_BlkGapEveSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_BlkGapEveSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntSigEnReg_DmaIntSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_DmaIntSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_DmaIntSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntSigEnReg_DmaIntSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_DmaIntSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_DmaIntSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntSigEnReg_BufWReadySigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_BufWReadySigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_BufWReadySigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntSigEnReg_BufWReadySigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_BufWReadySigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_BufWReadySigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntSigEnReg_BufRReadySigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_BufRReadySigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_BufRReadySigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntSigEnReg_BufRReadySigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_BufRReadySigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_BufRReadySigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntSigEnReg_CardInsertionSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_CardInsertionSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_CardInsertionSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntSigEnReg_CardInsertionSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_CardInsertionSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_CardInsertionSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntSigEnReg_CardRemSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_CardRemSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_CardRemSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntSigEnReg_CardRemSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_CardRemSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_CardRemSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntSigEnReg_CardIntSigEN(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_CardIntSigEN(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_CardIntSigEN(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntSigEnReg_CardIntSigEN(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_CardIntSigEN();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_CardIntSigEN();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntSigEnReg_FixedTo0(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntSigEnReg_FixedTo0(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntSigEnReg_FixedTo0(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntSigEnReg_FixedTo0(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntSigEnReg_FixedTo0();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntSigEnReg_FixedTo0();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_ErrIntSigEn (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_ErrIntSigEnReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEn(data);
    }
#endif
}
GH_INLINE U16  GH_SDIO_get_ErrIntSigEnReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntSigEnReg_CmdTimeoutErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEn_CmdTimeoutErrSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEn_CmdTimeoutErrSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntSigEnReg_CmdTimeoutErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEn_CmdTimeoutErrSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEn_CmdTimeoutErrSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntSigEnReg_CmdEndBitErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEn_CmdEndBitErrSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEn_CmdEndBitErrSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntSigEnReg_CmdEndBitErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEn_CmdEndBitErrSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEn_CmdEndBitErrSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntSigEnReg_CmdIndexErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEn_CmdIndexErrSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEn_CmdIndexErrSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntSigEnReg_CmdIndexErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEn_CmdIndexErrSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEn_CmdIndexErrSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntSigEnReg_DataTimeoutErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEn_DataTimeoutErrSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEn_DataTimeoutErrSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntSigEnReg_DataTimeoutErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEn_DataTimeoutErrSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEn_DataTimeoutErrSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntSigEnReg_CmdCrcErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEn_CmdCrcErrSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEn_CmdCrcErrSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntSigEnReg_CmdCrcErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEn_CmdCrcErrSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEn_CmdCrcErrSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntSigEnReg_DataCrcErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEn_DataCrcErrSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEn_DataCrcErrSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntSigEnReg_DataCrcErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEn_DataCrcErrSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEn_DataCrcErrSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntSigEnReg_DataEndBitErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEn_DataEndBitErrSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEn_DataEndBitErrSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntSigEnReg_DataEndBitErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEn_DataEndBitErrSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEn_DataEndBitErrSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntSigEnReg_CurLimitErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEn_CurLimitErrSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEn_CurLimitErrSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntSigEnReg_CurLimitErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEn_CurLimitErrSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEn_CurLimitErrSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntSigEnReg_AutoCmd12ErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEn_AutoCmd12ErrSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEn_AutoCmd12ErrSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntSigEnReg_AutoCmd12ErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEn_AutoCmd12ErrSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEn_AutoCmd12ErrSigEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntSigEnReg_VendorSpecificErrSigEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntSigEn_VendorSpecificErrSigEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntSigEn_VendorSpecificErrSigEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntSigEnReg_VendorSpecificErrSigEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntSigEn_VendorSpecificErrSigEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntSigEn_VendorSpecificErrSigEn();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_BlkCouReg (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_BlkCouReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkCouReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkCouReg(data);
    }
#endif
}
GH_INLINE U16  GH_SDIO_get_BlkCouReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkCouReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkCouReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_BlkCouReg_BlkCountForCurTra(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkCouReg_BlkCountForCurTra(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkCouReg_BlkCountForCurTra(data);
    }
#endif
}
GH_INLINE U16  GH_SDIO_get_BlkCouReg_BlkCountForCurTra(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkCouReg_BlkCountForCurTra();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkCouReg_BlkCountForCurTra();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_BlkSizeReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_BlkSizeReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeReg(data);
    }
#endif
}
GH_INLINE U16  GH_SDIO_get_BlkSizeReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_BlkSizeReg_TraBlkSize(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeReg_TraBlkSize(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeReg_TraBlkSize(data);
    }
#endif
}
GH_INLINE U16  GH_SDIO_get_BlkSizeReg_TraBlkSize(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeReg_TraBlkSize();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeReg_TraBlkSize();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_BlkSizeReg_HostSdmaBufSize(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BlkSizeReg_HostSdmaBufSize(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BlkSizeReg_HostSdmaBufSize(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_BlkSizeReg_HostSdmaBufSize(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BlkSizeReg_HostSdmaBufSize();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BlkSizeReg_HostSdmaBufSize();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_NorIntStaEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_NorIntStaEnReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg(data);
    }
#endif
}
GH_INLINE U16  GH_SDIO_get_NorIntStaEnReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaEnReg_CmdCompleteStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_CmdCompleteStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_CmdCompleteStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaEnReg_CmdCompleteStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_CmdCompleteStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_CmdCompleteStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaEnReg_TraCompleteStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_TraCompleteStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_TraCompleteStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaEnReg_TraCompleteStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_TraCompleteStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_TraCompleteStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaEnReg_BlkGapEveStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_BlkGapEveStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_BlkGapEveStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaEnReg_BlkGapEveStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_BlkGapEveStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_BlkGapEveStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaEnReg_DmaIntStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_DmaIntStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_DmaIntStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaEnReg_DmaIntStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_DmaIntStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_DmaIntStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaEnReg_BufWReadyStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_BufWReadyStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_BufWReadyStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaEnReg_BufWReadyStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_BufWReadyStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_BufWReadyStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaEnReg_BufRReadyStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_BufRReadyStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_BufRReadyStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaEnReg_BufRReadyStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_BufRReadyStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_BufRReadyStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaEnReg_CardInsertionStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_CardInsertionStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_CardInsertionStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaEnReg_CardInsertionStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_CardInsertionStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_CardInsertionStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaEnReg_CardRemStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_CardRemStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_CardRemStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaEnReg_CardRemStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_CardRemStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_CardRemStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaEnReg_CardIntStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_CardIntStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_CardIntStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaEnReg_CardIntStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_CardIntStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_CardIntStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaEnReg_FixedTo0(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaEnReg_FixedTo0(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaEnReg_FixedTo0(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaEnReg_FixedTo0(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaEnReg_FixedTo0();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaEnReg_FixedTo0();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_ErrIntStaEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_ErrIntStaEnReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO0_set_ErrIntStaEnReg(data);
    }
#endif
}
GH_INLINE U16  GH_SDIO_get_ErrIntStaEnReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaEnReg_CmdEndBitErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_CmdEndBitErrStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_CmdEndBitErrStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaEnReg_CmdEndBitErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_CmdEndBitErrStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_CmdEndBitErrStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaEnReg_CmdCrcErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_CmdCrcErrStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_CmdCrcErrStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaEnReg_CmdCrcErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_CmdCrcErrStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_CmdCrcErrStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaEnReg_CmdIndexErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_CmdIndexErrStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_CmdIndexErrStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaEnReg_CmdIndexErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_CmdIndexErrStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_CmdIndexErrStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaEnReg_DataCrcErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_DataCrcErrStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_DataCrcErrStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaEnReg_DataCrcErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_DataCrcErrStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_DataCrcErrStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaEnReg_DataTimeoutErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_DataTimeoutErrStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_DataTimeoutErrStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaEnReg_DataTimeoutErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_DataTimeoutErrStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_DataTimeoutErrStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaEnReg_DataEndBitErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_DataEndBitErrStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_DataEndBitErrStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaEnReg_DataEndBitErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_DataEndBitErrStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_DataEndBitErrStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaEnReg_CurLimitErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_CurLimitErrStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_CurLimitErrStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaEnReg_CurLimitErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_CurLimitErrStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_CurLimitErrStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaEnReg_VendorSpecificErrStatusEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaEnReg_VendorSpecificErrStatusEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaEnReg_VendorSpecificErrStatusEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaEnReg_VendorSpecificErrStatusEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaEnReg_VendorSpecificErrStatusEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaEnReg_VendorSpecificErrStatusEn();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_NorIntStaReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_NorIntStaReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg(data);
    }
#endif
}
GH_INLINE U16  GH_SDIO_get_NorIntStaReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaReg_CmdComplete(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_CmdComplete(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_CmdComplete(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaReg_CmdComplete(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_CmdComplete();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_CmdComplete();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaReg_BlkGapEvent(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_BlkGapEvent(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_BlkGapEvent(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaReg_BlkGapEvent(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_BlkGapEvent();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_BlkGapEvent();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaReg_DmaInt(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_DmaInt(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_DmaInt(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaReg_DmaInt(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_DmaInt();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_DmaInt();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaReg_TraComplete(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_TraComplete(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_TraComplete(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaReg_TraComplete(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_TraComplete();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_TraComplete();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaReg_BufWReady(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_BufWReady(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_BufWReady(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaReg_BufWReady(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_BufWReady();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_BufWReady();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaReg_CardInsertion(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_CardInsertion(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_CardInsertion(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaReg_CardInsertion(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_CardInsertion();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_CardInsertion();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaReg_BufRReady(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_BufRReady(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_BufRReady(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaReg_BufRReady(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_BufRReady();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_BufRReady();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaReg_CardRemoval(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_CardRemoval(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_CardRemoval(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaReg_CardRemoval(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_CardRemoval();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_CardRemoval();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaReg_CardInt(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_CardInt(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_CardInt(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaReg_CardInt(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_CardInt();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_CardInt();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaReg_BootAckRcv(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_BootAckRcv(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_BootAckRcv(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaReg_BootAckRcv(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_BootAckRcv();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_BootAckRcv();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_NorIntStaReg_ErrInt(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_NorIntStaReg_ErrInt(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_NorIntStaReg_ErrInt(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_NorIntStaReg_ErrInt(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_NorIntStaReg_ErrInt();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_NorIntStaReg_ErrInt();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_ErrIntStaReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_ErrIntStaReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaReg(data);
    }
#endif
}
GH_INLINE U16  GH_SDIO_get_ErrIntStaReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaReg_CmdTimeoutErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaReg_CmdTimeoutErr(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaReg_CmdTimeoutErr(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaReg_CmdTimeoutErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaReg_CmdTimeoutErr();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaReg_CmdTimeoutErr();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaReg_CmdCrcErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaReg_CmdCrcErr(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaReg_CmdCrcErr(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaReg_CmdCrcErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaReg_CmdCrcErr();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaReg_CmdCrcErr();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaReg_CmdEndBitErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaReg_CmdEndBitErr(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaReg_CmdEndBitErr(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaReg_CmdEndBitErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaReg_CmdEndBitErr();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaReg_CmdEndBitErr();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaReg_CmdIndexErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaReg_CmdIndexErr(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaReg_CmdIndexErr(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaReg_CmdIndexErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaReg_CmdIndexErr();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaReg_CmdIndexErr();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaReg_DataTimeoutErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaReg_DataTimeoutErr(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaReg_DataTimeoutErr(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaReg_DataTimeoutErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaReg_DataTimeoutErr();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaReg_DataTimeoutErr();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaReg_DataCrcErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaReg_DataCrcErr(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaReg_DataCrcErr(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaReg_DataCrcErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaReg_DataCrcErr();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaReg_DataCrcErr();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaReg_DataEndBitErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaReg_DataEndBitErr(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaReg_DataEndBitErr(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaReg_DataEndBitErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaReg_DataEndBitErr();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaReg_DataEndBitErr();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaReg_CurLimitErr(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaReg_CurLimitErr(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
       GH_SDIO1_set_ErrIntStaReg_CurLimitErr (data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaReg_CurLimitErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaReg_CurLimitErr();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaReg_CurLimitErr();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaReg_AutoCmd12Err(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaReg_AutoCmd12Err(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaReg_AutoCmd12Err(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaReg_AutoCmd12Err(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaReg_AutoCmd12Err();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaReg_AutoCmd12Err();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_ErrIntStaReg_VendorSpecificErrStatus(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ErrIntStaReg_VendorSpecificErrStatus(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ErrIntStaReg_VendorSpecificErrStatus(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_ErrIntStaReg_VendorSpecificErrStatus(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ErrIntStaReg_VendorSpecificErrStatus();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ErrIntStaReg_VendorSpecificErrStatus();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_CmdReg (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_CmdReg(U32 sdio, U16 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CmdReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CmdReg(data);
    }
#endif
}
GH_INLINE U16  GH_SDIO_get_CmdReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CmdReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CmdReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_CmdReg_RepTypeSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CmdReg_RepTypeSelect(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CmdReg_RepTypeSelect(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_CmdReg_RepTypeSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CmdReg_RepTypeSelect();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CmdReg_RepTypeSelect();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_CmdReg_CmdCrcCheckEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CmdReg_CmdCrcCheckEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CmdReg_CmdCrcCheckEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_CmdReg_CmdCrcCheckEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CmdReg_CmdCrcCheckEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CmdReg_CmdCrcCheckEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_CmdReg_DataPreSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CmdReg_DataPreSelect(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CmdReg_DataPreSelect(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_CmdReg_DataPreSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CmdReg_DataPreSelect();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CmdReg_DataPreSelect();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_CmdReg_CmdIndexCheckEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CmdReg_CmdIndexCheckEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CmdReg_CmdIndexCheckEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_CmdReg_CmdIndexCheckEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CmdReg_CmdIndexCheckEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CmdReg_CmdIndexCheckEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_CmdReg_CmdType(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CmdReg_CmdType(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CmdReg_CmdType(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_CmdReg_CmdType(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CmdReg_CmdType();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CmdReg_CmdType();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_CmdReg_CmdIndex(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_CmdReg_CmdIndex(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_CmdReg_CmdIndex(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_CmdReg_CmdIndex(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CmdReg_CmdIndex();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CmdReg_CmdIndex();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_Control01Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_Control01Reg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg(data);
    }
#endif
}
GH_INLINE U32  GH_SDIO_get_Control01Reg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control01Reg_DataTimeoutCounterValue(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_DataTimeoutCounterValue(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_DataTimeoutCounterValue(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control01Reg_DataTimeoutCounterValue(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_DataTimeoutCounterValue();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_DataTimeoutCounterValue();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control01Reg_SoftwareResetCmdLine(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_SoftwareResetCmdLine(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_SoftwareResetCmdLine(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control01Reg_SoftwareResetCmdLine(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_SoftwareResetCmdLine();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_SoftwareResetCmdLine();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control01Reg_SoftwareResetAll(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_SoftwareResetAll(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_SoftwareResetAll(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control01Reg_SoftwareResetAll(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_SoftwareResetAll();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_SoftwareResetAll();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control01Reg_SoftwareResetDatLine(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_SoftwareResetDatLine(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_SoftwareResetDatLine(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control01Reg_SoftwareResetDatLine(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_SoftwareResetDatLine();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_SoftwareResetDatLine();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control01Reg_InternalClkEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_InternalClkEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_InternalClkEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control01Reg_InternalClkEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_InternalClkEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_InternalClkEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control01Reg_InternalClkStable(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_InternalClkStable(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_InternalClkStable(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control01Reg_InternalClkStable(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_InternalClkStable();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_InternalClkStable();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control01Reg_SdClkEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_SdClkEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_SdClkEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control01Reg_SdClkEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_SdClkEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_SdClkEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control01Reg_SdclkFreSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control01Reg_SdclkFreSelect(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control01Reg_SdclkFreSelect(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control01Reg_SdclkFreSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control01Reg_SdclkFreSelect();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control01Reg_SdclkFreSelect();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_Resp0Reg (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO_get_Resp0Reg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Resp0Reg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Resp0Reg();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_Resp1Reg (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO_get_Resp1Reg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Resp1Reg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Resp1Reg();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_Resp2Reg (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO_get_Resp2Reg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Resp2Reg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Resp2Reg();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_Resp3Reg (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO_get_Resp3Reg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Resp3Reg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Resp3Reg();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_Control00Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_Control00Reg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg(data);
    }
#endif
}
GH_INLINE U32  GH_SDIO_get_Control00Reg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_LedControl(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_LedControl(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_LedControl(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_LedControl(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_LedControl();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_LedControl();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_DataTraWidth(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_DataTraWidth(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_DataTraWidth(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_DataTraWidth(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_DataTraWidth();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_DataTraWidth();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_Sd8BitMode(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_Sd8BitMode(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_Sd8BitMode(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_Sd8BitMode(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_Sd8BitMode();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_Sd8BitMode();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_HostSpeedEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_HostSpeedEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_HostSpeedEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_HostSpeedEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_HostSpeedEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_HostSpeedEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_CardDetectTestLevel(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_CardDetectTestLevel(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_CardDetectTestLevel(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_CardDetectTestLevel(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_CardDetectTestLevel();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_CardDetectTestLevel();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_CardDetectSigDet(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_CardDetectSigDet(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_CardDetectSigDet(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_CardDetectSigDet(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_CardDetectSigDet();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_CardDetectSigDet();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_SdBusPower(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_SdBusPower(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_SdBusPower(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_SdBusPower(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_SdBusPower();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_SdBusPower();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_SdBusVoltageSelect(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_SdBusVoltageSelect(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_SdBusVoltageSelect(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_SdBusVoltageSelect(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_SdBusVoltageSelect();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_SdBusVoltageSelect();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_StopAtBlkGapReq(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_StopAtBlkGapReq(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_StopAtBlkGapReq(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_StopAtBlkGapReq(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_StopAtBlkGapReq();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_StopAtBlkGapReq();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_RWaitControl(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_RWaitControl(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_RWaitControl(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_RWaitControl(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_RWaitControl();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_RWaitControl();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_ContinueReq(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_ContinueReq(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_ContinueReq(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_ContinueReq(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_ContinueReq();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_ContinueReq();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_IntAtBlkGap(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_IntAtBlkGap(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_IntAtBlkGap(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_IntAtBlkGap(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_IntAtBlkGap();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_IntAtBlkGap();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_DriveCcsd(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_DriveCcsd(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_DriveCcsd(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_DriveCcsd(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_DriveCcsd();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_DriveCcsd();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_SpiMode(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_SpiMode(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_SpiMode(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_SpiMode(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_SpiMode();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_SpiMode();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_BootEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_BootEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_BootEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_BootEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_BootEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_BootEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_AltBootEn(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_AltBootEn(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_AltBootEn(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_AltBootEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_AltBootEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_AltBootEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardIns(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardIns(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardIns(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardIns(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardIns();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardIns();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardInt(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardInt(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardInt(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardInt(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardInt();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardInt();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardRem(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardRem(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardRem(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardRem(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardRem();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardRem();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_PresentStateReg (read)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO_get_PresentStateReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_CmdInhibitCmd(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_CmdInhibitCmd();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_CmdInhibitCmd();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_DataLineActive(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_DataLineActive();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_DataLineActive();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_CmdInhibitData(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_CmdInhibitData();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_CmdInhibitData();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_RTraActive(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_RTraActive();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_RTraActive();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_BufWEn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_BufWEn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_BufWEn();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_WTraActive(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_WTraActive();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_WTraActive();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_BufREn(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_BufREn();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_BufREn();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_CardInserted(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_CardInserted();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_CardInserted();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_CardDetectPinLevel(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_CardDetectPinLevel();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_CardDetectPinLevel();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_CardStateStable(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_CardStateStable();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_CardStateStable();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_WProSwiPinLevel(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_WProSwiPinLevel();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_WProSwiPinLevel();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_Data03LineSigLevel(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_Data03LineSigLevel();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_Data03LineSigLevel();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_CmdLineSigLevel(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_CmdLineSigLevel();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_CmdLineSigLevel();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_PresentStateReg_Data47LineSigLevel(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_PresentStateReg_Data47LineSigLevel();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_PresentStateReg_Data47LineSigLevel();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_ArgReg (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_ArgReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_ArgReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_ArgReg(data);
    }
#endif
}
GH_INLINE U32  GH_SDIO_get_ArgReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_ArgReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_ArgReg();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_CapReg (read)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO_get_CapReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_CapReg_TimeoutClkFre(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_TimeoutClkFre();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_TimeoutClkFre();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_CapReg_TimeoutClkUnit(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_TimeoutClkUnit();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_TimeoutClkUnit();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_CapReg_BaseClkFreForSdClk(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_BaseClkFreForSdClk();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_BaseClkFreForSdClk();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_CapReg_MaxBlkLen(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_MaxBlkLen();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_MaxBlkLen();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_CapReg_ExtendedMediaBusSup(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_ExtendedMediaBusSup();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_ExtendedMediaBusSup();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_CapReg_HighSpeedSup(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_HighSpeedSup();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_HighSpeedSup();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_CapReg_SusResSup(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_SusResSup();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_SusResSup();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_CapReg_SdmaSup(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_SdmaSup();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_SdmaSup();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_CapReg_VoltageSup33v(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_VoltageSup33v();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_VoltageSup33v();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_CapReg_VoltageSup30v(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_VoltageSup30v();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_VoltageSup30v();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_CapReg_VoltageSup18v(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_VoltageSup18v();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_VoltageSup18v();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_CapReg_IntMode(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_CapReg_IntMode();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_CapReg_IntMode();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_AutoCmd12ErrStatusReg (read)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO_get_AutoCmd12ErrStatusReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_BufferDataPortReg (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_BufferDataPortReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_BufferDataPortReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_BufferDataPortReg(data);
    }
#endif
}
GH_INLINE U32  GH_SDIO_get_BufferDataPortReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_BufferDataPortReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_BufferDataPortReg();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_MaxCurCapReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO_set_MaxCurCapReg(U32 sdio, U32 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_MaxCurCapReg(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_MaxCurCapReg(data);
    }
#endif
}
GH_INLINE U32  GH_SDIO_get_MaxCurCapReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_MaxCurCapReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_MaxCurCapReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_MaxCurCapReg_MaxCurFor33v(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_MaxCurCapReg_MaxCurFor33v(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_MaxCurCapReg_MaxCurFor33v(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor33v(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_MaxCurCapReg_MaxCurFor33v();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_MaxCurCapReg_MaxCurFor33v();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_MaxCurCapReg_MaxCurFor30v(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_MaxCurCapReg_MaxCurFor30v(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_MaxCurCapReg_MaxCurFor30v(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor30v(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_MaxCurCapReg_MaxCurFor30v();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_MaxCurCapReg_MaxCurFor30v();
    }
#endif
    return GH_ERR;
}
GH_INLINE void GH_SDIO_set_MaxCurCapReg_MaxCurFor18v(U32 sdio, U8 data)
{
    if(sdio == GH_SDIO0)
    {
        GH_SDIO0_set_MaxCurCapReg_MaxCurFor18v(data);
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        GH_SDIO1_set_MaxCurCapReg_MaxCurFor18v(data);
    }
#endif
}
GH_INLINE U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor18v(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_MaxCurCapReg_MaxCurFor18v();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_MaxCurCapReg_MaxCurFor18v();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* register SDIO_SlotIntStatusReg (read)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO_get_SlotIntStatusReg(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SlotIntStatusReg();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SlotIntStatusReg();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_SlotIntStatusReg_IntSigForEachSlot(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SlotIntStatusReg_IntSigForEachSlot();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SlotIntStatusReg_IntSigForEachSlot();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_SlotIntStatusReg_SpecifiVerNum(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SlotIntStatusReg_SpecifiVerNum();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SlotIntStatusReg_SpecifiVerNum();
    }
#endif
    return GH_ERR;
}
GH_INLINE U8   GH_SDIO_get_SlotIntStatusReg_VendorVerNum(U32 sdio)
{
    if(sdio == GH_SDIO0)
    {
        return GH_SDIO0_get_SlotIntStatusReg_VendorVerNum();
    }
#ifdef GK7101S
    else if(sdio == GH_SDIO1)
    {
        return GH_SDIO1_get_SlotIntStatusReg_VendorVerNum();
    }
#endif
    return GH_ERR;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_SDIO_init(void)
{
    GH_SDIO0_init();
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

