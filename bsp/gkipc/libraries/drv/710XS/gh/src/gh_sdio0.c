/******************************************************************************
**
** \file      gh_sdio0.c
**
** \brief     SDIO0 Host Controller.
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
#include "gh_sdio0.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register SDIO0_SysAddrReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_SysAddrReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_SYSADDRREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SysAddrReg] <-- 0x%08x\n",
                        REG_SDIO0_SYSADDRREG,data,data);
    #endif
}
U32  GH_SDIO0_get_SysAddrReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_SYSADDRREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SysAddrReg] --> 0x%08x\n",
                        REG_SDIO0_SYSADDRREG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_TranModeNorIntSigEnReg (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_TranModeNorIntSigEnReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,data,data);
    #endif
}
U32  GH_SDIO0_get_TranModeNorIntSigEnReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_BlkCountEn(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.blkcounten = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_BlkCountEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_BlkCountEn(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_BlkCountEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.blkcounten;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_AutoCmd12En(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.autocmd12en = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_AutoCmd12En] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_AutoCmd12En(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_AutoCmd12En] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.autocmd12en;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_DmaEn(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.dmaen = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_DmaEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_DmaEn(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_DmaEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.dmaen;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_MSBlkSelect(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.msblkselect = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_MSBlkSelect] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_MSBlkSelect(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_MSBlkSelect] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.msblkselect;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_DataTraDirSelect(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.datatradirselect = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_DataTraDirSelect] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_DataTraDirSelect(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_DataTraDirSelect] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.datatradirselect;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_CmdCompleteSigEn(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.cmdcompletesigen = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_CmdCompleteSigEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_CmdCompleteSigEn(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_CmdCompleteSigEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdcompletesigen;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_TraCompleteSigEn(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.tracompletesigen = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_TraCompleteSigEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_TraCompleteSigEn(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_TraCompleteSigEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.tracompletesigen;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_BlkGapEveSigEn(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.blkgapevesigen = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_BlkGapEveSigEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_BlkGapEveSigEn(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_BlkGapEveSigEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.blkgapevesigen;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_DmaIntSigEn(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.dmaintsigen = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_DmaIntSigEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_DmaIntSigEn(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_DmaIntSigEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.dmaintsigen;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_BufWReadySigEn(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.bufwreadysigen = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_BufWReadySigEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_BufWReadySigEn(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_BufWReadySigEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.bufwreadysigen;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_BufRReadySigEn(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.bufrreadysigen = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_BufRReadySigEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_BufRReadySigEn(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_BufRReadySigEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.bufrreadysigen;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_CardInsertionSigEn(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.cardinsertionsigen = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_CardInsertionSigEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_CardInsertionSigEn(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_CardInsertionSigEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardinsertionsigen;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_CardRemSigEn(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.cardremsigen = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_CardRemSigEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_CardRemSigEn(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_CardRemSigEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardremsigen;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_CardIntSigEN(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.cardintsigen = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_CardIntSigEN] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_CardIntSigEN(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_CardIntSigEN] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardintsigen;
}
void GH_SDIO0_set_TranModeNorIntSigEnReg_FixedTo0(U8 data)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG;
    d.bitc.fixedto0 = data;
    *(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeNorIntSigEnReg_FixedTo0] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeNorIntSigEnReg_FixedTo0(void)
{
    GH_SDIO0_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeNorIntSigEnReg_FixedTo0] --> 0x%08x\n",
                        REG_SDIO0_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.fixedto0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntSigEnBlkCouReg (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_ErrIntSigEnBlkCouReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnBlkCouReg] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,data,data);
    #endif
}
U32  GH_SDIO0_get_ErrIntSigEnBlkCouReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnBlkCouReg] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG;
    d.bitc.cmdtimeouterrsigen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterrsigen;
}
void GH_SDIO0_set_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG;
    d.bitc.cmdendbiterrsigen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterrsigen;
}
void GH_SDIO0_set_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG;
    d.bitc.cmdindexerrsigen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.cmdindexerrsigen;
}
void GH_SDIO0_set_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG;
    d.bitc.datatimeouterrsigen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.datatimeouterrsigen;
}
void GH_SDIO0_set_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG;
    d.bitc.cmdcrcerrsigen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerrsigen;
}
void GH_SDIO0_set_ErrIntSigEnBlkCouReg_DataCrcErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG;
    d.bitc.datacrcerrsigen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnBlkCouReg_DataCrcErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnBlkCouReg_DataCrcErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnBlkCouReg_DataCrcErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.datacrcerrsigen;
}
void GH_SDIO0_set_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG;
    d.bitc.dataendbiterrsigen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.dataendbiterrsigen;
}
void GH_SDIO0_set_ErrIntSigEnBlkCouReg_CurLimitErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG;
    d.bitc.curlimiterrsigen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnBlkCouReg_CurLimitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnBlkCouReg_CurLimitErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnBlkCouReg_CurLimitErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.curlimiterrsigen;
}
void GH_SDIO0_set_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG;
    d.bitc.autocmd12errsigen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.autocmd12errsigen;
}
void GH_SDIO0_set_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG;
    d.bitc.vendorspecificerrsigen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrsigen;
}
void GH_SDIO0_set_ErrIntSigEnBlkCouReg_BlkCountForCurTra(U16 data)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG;
    d.bitc.blkcountforcurtra = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnBlkCouReg_BlkCountForCurTra] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
U16  GH_SDIO0_get_ErrIntSigEnBlkCouReg_BlkCountForCurTra(void)
{
    GH_SDIO0_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnBlkCouReg_BlkCountForCurTra] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.blkcountforcurtra;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_BlkSizeNorIntStaEnReg (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_BlkSizeNorIntStaEnReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,data,data);
    #endif
}
U32  GH_SDIO0_get_BlkSizeNorIntStaEnReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_BlkSizeNorIntStaEnReg_TraBlkSize(U16 data)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG;
    d.bitc.trablksize = data;
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg_TraBlkSize] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
U16  GH_SDIO0_get_BlkSizeNorIntStaEnReg_TraBlkSize(void)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg_TraBlkSize] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.trablksize;
}
void GH_SDIO0_set_BlkSizeNorIntStaEnReg_HostSdmaBufSize(U8 data)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG;
    d.bitc.hostsdmabufsize = data;
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg_HostSdmaBufSize] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_BlkSizeNorIntStaEnReg_HostSdmaBufSize(void)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg_HostSdmaBufSize] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.hostsdmabufsize;
}
void GH_SDIO0_set_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn(U8 data)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG;
    d.bitc.cmdcompletestatusen = data;
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn(void)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdcompletestatusen;
}
void GH_SDIO0_set_BlkSizeNorIntStaEnReg_TraCompleteStatusEn(U8 data)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG;
    d.bitc.tracompletestatusen = data;
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg_TraCompleteStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_BlkSizeNorIntStaEnReg_TraCompleteStatusEn(void)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg_TraCompleteStatusEn] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.tracompletestatusen;
}
void GH_SDIO0_set_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn(U8 data)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG;
    d.bitc.blkgapevestatusen = data;
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn(void)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.blkgapevestatusen;
}
void GH_SDIO0_set_BlkSizeNorIntStaEnReg_DmaIntStatusEn(U8 data)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG;
    d.bitc.dmaintstatusen = data;
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg_DmaIntStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_BlkSizeNorIntStaEnReg_DmaIntStatusEn(void)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg_DmaIntStatusEn] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.dmaintstatusen;
}
void GH_SDIO0_set_BlkSizeNorIntStaEnReg_BufWReadyStatusEn(U8 data)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG;
    d.bitc.bufwreadystatusen = data;
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg_BufWReadyStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_BlkSizeNorIntStaEnReg_BufWReadyStatusEn(void)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg_BufWReadyStatusEn] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.bufwreadystatusen;
}
void GH_SDIO0_set_BlkSizeNorIntStaEnReg_BufRReadyStatusEn(U8 data)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG;
    d.bitc.bufrreadystatusen = data;
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg_BufRReadyStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_BlkSizeNorIntStaEnReg_BufRReadyStatusEn(void)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg_BufRReadyStatusEn] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.bufrreadystatusen;
}
void GH_SDIO0_set_BlkSizeNorIntStaEnReg_CardInsertionStatusEn(U8 data)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG;
    d.bitc.cardinsertionstatusen = data;
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg_CardInsertionStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_BlkSizeNorIntStaEnReg_CardInsertionStatusEn(void)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg_CardInsertionStatusEn] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardinsertionstatusen;
}
void GH_SDIO0_set_BlkSizeNorIntStaEnReg_CardRemStatusEn(U8 data)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG;
    d.bitc.cardremstatusen = data;
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg_CardRemStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_BlkSizeNorIntStaEnReg_CardRemStatusEn(void)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg_CardRemStatusEn] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardremstatusen;
}
void GH_SDIO0_set_BlkSizeNorIntStaEnReg_CardIntStatusEn(U8 data)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG;
    d.bitc.cardintstatusen = data;
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg_CardIntStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_BlkSizeNorIntStaEnReg_CardIntStatusEn(void)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg_CardIntStatusEn] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardintstatusen;
}
void GH_SDIO0_set_BlkSizeNorIntStaEnReg_FixedTo0(U8 data)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG;
    d.bitc.fixedto0 = data;
    *(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeNorIntStaEnReg_FixedTo0] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_BlkSizeNorIntStaEnReg_FixedTo0(void)
{
    GH_SDIO0_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeNorIntStaEnReg_FixedTo0] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.fixedto0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntStaEnNorIntStaReg (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,data,data);
    #endif
}
U32  GH_SDIO0_get_ErrIntStaEnNorIntStaReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.cmdtimeouterrstatusen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.cmdendbiterrstatusen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.cmdcrcerrstatusen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.cmdindexerrstatusen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdindexerrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.datacrcerrstatusen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.datacrcerrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.datatimeouterrstatusen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.datatimeouterrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.dataendbiterrstatusen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.dataendbiterrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.curlimiterrstatusen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.curlimiterrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.autocmd12errstatusen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.autocmd12errstatusen;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.vendorspecificerrstatusen = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdComplete(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.cmdcomplete = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CmdComplete] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdComplete(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CmdComplete] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdcomplete;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_BlkGapEvent(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.blkgapevent = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_BlkGapEvent] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_BlkGapEvent(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_BlkGapEvent] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.blkgapevent;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_DmaInt(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.dmaint = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_DmaInt] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_DmaInt(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_DmaInt] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.dmaint;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_TraComplete(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.tracomplete = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_TraComplete] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_TraComplete(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_TraComplete] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.tracomplete;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_BufWReady(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.bufwready = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_BufWReady] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_BufWReady(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_BufWReady] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bufwready;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CardInsertion(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.cardinsertion = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CardInsertion] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CardInsertion(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CardInsertion] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardinsertion;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_BufRReady(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.bufrready = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_BufRReady] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_BufRReady(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_BufRReady] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bufrready;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CardRemoval(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.cardremoval = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CardRemoval] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CardRemoval(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CardRemoval] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardremoval;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CardInt(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.cardint = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_CardInt] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CardInt(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_CardInt] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardint;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_BootAckRcv(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.bootackrcv = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_BootAckRcv] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_BootAckRcv(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_BootAckRcv] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bootackrcv;
}
void GH_SDIO0_set_ErrIntStaEnNorIntStaReg_ErrInt(U8 data)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG;
    d.bitc.errint = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnNorIntStaReg_ErrInt] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnNorIntStaReg_ErrInt(void)
{
    GH_SDIO0_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnNorIntStaReg_ErrInt] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.errint;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntStatusCommondReg (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_ErrIntStatusCommondReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,data,data);
    #endif
}
U32  GH_SDIO0_get_ErrIntStatusCommondReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_CmdTimeoutErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdtimeouterr = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_CmdTimeoutErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_CmdTimeoutErr(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_CmdTimeoutErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterr;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_CmdCrcErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdcrcerr = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_CmdCrcErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_CmdCrcErr(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_CmdCrcErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerr;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_CmdEndBitErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdendbiterr = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_CmdEndBitErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_CmdEndBitErr(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_CmdEndBitErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterr;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_CmdIndexErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdindexerr = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_CmdIndexErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_CmdIndexErr(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_CmdIndexErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdindexerr;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_DataTimeoutErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.datatimeouterr = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_DataTimeoutErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_DataTimeoutErr(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_DataTimeoutErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.datatimeouterr;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_DataCrcErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.datacrcerr = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_DataCrcErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_DataCrcErr(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_DataCrcErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.datacrcerr;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_DataEndBitErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.dataendbiterr = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_DataEndBitErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_DataEndBitErr(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_DataEndBitErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.dataendbiterr;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_CurLimitErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.curlimiterr = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_CurLimitErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_CurLimitErr(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_CurLimitErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.curlimiterr;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_AutoCmd12Err(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.autocmd12err = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_AutoCmd12Err] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_AutoCmd12Err(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_AutoCmd12Err] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.autocmd12err;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_VendorSpecificErrStatus(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.vendorspecificerrstatus = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_VendorSpecificErrStatus] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_VendorSpecificErrStatus(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_VendorSpecificErrStatus] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrstatus;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_RepTypeSelect(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.reptypeselect = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_RepTypeSelect] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_RepTypeSelect(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_RepTypeSelect] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.reptypeselect;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_CmdCrcCheckEn(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdcrcchecken = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_CmdCrcCheckEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_CmdCrcCheckEn(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_CmdCrcCheckEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdcrcchecken;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_DataPreSelect(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.datapreselect = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_DataPreSelect] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_DataPreSelect(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_DataPreSelect] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.datapreselect;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_CmdIndexCheckEn(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdindexchecken = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_CmdIndexCheckEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_CmdIndexCheckEn(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_CmdIndexCheckEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdindexchecken;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_CmdType(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdtype = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_CmdType] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_CmdType(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_CmdType] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdtype;
}
void GH_SDIO0_set_ErrIntStatusCommondReg_CmdIndex(U8 data)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdindex = data;
    *(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusCommondReg_CmdIndex] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusCommondReg_CmdIndex(void)
{
    GH_SDIO0_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusCommondReg_CmdIndex] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdindex;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_Control01Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_Control01Reg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_CONTROL01REG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,data,data);
    #endif
}
U32  GH_SDIO0_get_Control01Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return value;
}
void GH_SDIO0_set_Control01Reg_DataTimeoutCounterValue(U8 data)
{
    GH_SDIO0_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG;
    d.bitc.datatimeoutcountervalue = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_DataTimeoutCounterValue] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control01Reg_DataTimeoutCounterValue(void)
{
    GH_SDIO0_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_DataTimeoutCounterValue] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.datatimeoutcountervalue;
}
void GH_SDIO0_set_Control01Reg_SoftwareResetCmdLine(U8 data)
{
    GH_SDIO0_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG;
    d.bitc.softwareresetcmdline = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_SoftwareResetCmdLine] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control01Reg_SoftwareResetCmdLine(void)
{
    GH_SDIO0_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_SoftwareResetCmdLine] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.softwareresetcmdline;
}
void GH_SDIO0_set_Control01Reg_SoftwareResetAll(U8 data)
{
    GH_SDIO0_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG;
    d.bitc.softwareresetall = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_SoftwareResetAll] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control01Reg_SoftwareResetAll(void)
{
    GH_SDIO0_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_SoftwareResetAll] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.softwareresetall;
}
void GH_SDIO0_set_Control01Reg_SoftwareResetDatLine(U8 data)
{
    GH_SDIO0_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG;
    d.bitc.softwareresetdatline = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_SoftwareResetDatLine] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control01Reg_SoftwareResetDatLine(void)
{
    GH_SDIO0_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_SoftwareResetDatLine] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.softwareresetdatline;
}
void GH_SDIO0_set_Control01Reg_InternalClkEn(U8 data)
{
    GH_SDIO0_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG;
    d.bitc.internalclken = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_InternalClkEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control01Reg_InternalClkEn(void)
{
    GH_SDIO0_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_InternalClkEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.internalclken;
}
void GH_SDIO0_set_Control01Reg_InternalClkStable(U8 data)
{
    GH_SDIO0_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG;
    d.bitc.internalclkstable = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_InternalClkStable] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control01Reg_InternalClkStable(void)
{
    GH_SDIO0_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_InternalClkStable] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.internalclkstable;
}
void GH_SDIO0_set_Control01Reg_SdClkEn(U8 data)
{
    GH_SDIO0_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG;
    d.bitc.sdclken = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_SdClkEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control01Reg_SdClkEn(void)
{
    GH_SDIO0_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_SdClkEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.sdclken;
}
void GH_SDIO0_set_Control01Reg_SdclkFreSelect(U8 data)
{
    GH_SDIO0_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG;
    d.bitc.sdclkfreselect = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_SdclkFreSelect] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control01Reg_SdclkFreSelect(void)
{
    GH_SDIO0_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_SdclkFreSelect] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.sdclkfreselect;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp0Reg (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SDIO0_get_Resp0Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_RESP0REG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Resp0Reg] --> 0x%08x\n",
                        REG_SDIO0_RESP0REG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp1Reg (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SDIO0_get_Resp1Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_RESP1REG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Resp1Reg] --> 0x%08x\n",
                        REG_SDIO0_RESP1REG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp2Reg (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SDIO0_get_Resp2Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_RESP2REG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Resp2Reg] --> 0x%08x\n",
                        REG_SDIO0_RESP2REG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp3Reg (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SDIO0_get_Resp3Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_RESP3REG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Resp3Reg] --> 0x%08x\n",
                        REG_SDIO0_RESP3REG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_Control00Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_Control00Reg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,data,data);
    #endif
}
U32  GH_SDIO0_get_Control00Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return value;
}
void GH_SDIO0_set_Control00Reg_LedControl(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.ledcontrol = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_LedControl] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_LedControl(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_LedControl] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.ledcontrol;
}
void GH_SDIO0_set_Control00Reg_DataTraWidth(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.datatrawidth = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_DataTraWidth] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_DataTraWidth(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_DataTraWidth] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.datatrawidth;
}
void GH_SDIO0_set_Control00Reg_Sd8BitMode(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.sd8bitmode = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_Sd8BitMode] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_Sd8BitMode(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_Sd8BitMode] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.sd8bitmode;
}
void GH_SDIO0_set_Control00Reg_HostSpeedEn(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.hostspeeden = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_HostSpeedEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_HostSpeedEn(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_HostSpeedEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.hostspeeden;
}
void GH_SDIO0_set_Control00Reg_CardDetectTestLevel(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.carddetecttestlevel = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_CardDetectTestLevel] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_CardDetectTestLevel(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_CardDetectTestLevel] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.carddetecttestlevel;
}
void GH_SDIO0_set_Control00Reg_CardDetectSigDet(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.carddetectsigdet = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_CardDetectSigDet] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_CardDetectSigDet(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_CardDetectSigDet] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.carddetectsigdet;
}
void GH_SDIO0_set_Control00Reg_SdBusPower(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.sdbuspower = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_SdBusPower] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_SdBusPower(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_SdBusPower] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.sdbuspower;
}
void GH_SDIO0_set_Control00Reg_SdBusVoltageSelect(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.sdbusvoltageselect = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_SdBusVoltageSelect] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_SdBusVoltageSelect(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_SdBusVoltageSelect] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.sdbusvoltageselect;
}
void GH_SDIO0_set_Control00Reg_StopAtBlkGapReq(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.stopatblkgapreq = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_StopAtBlkGapReq] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_StopAtBlkGapReq(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_StopAtBlkGapReq] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.stopatblkgapreq;
}
void GH_SDIO0_set_Control00Reg_RWaitControl(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.rwaitcontrol = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_RWaitControl] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_RWaitControl(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_RWaitControl] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.rwaitcontrol;
}
void GH_SDIO0_set_Control00Reg_ContinueReq(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.continuereq = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_ContinueReq] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_ContinueReq(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_ContinueReq] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.continuereq;
}
void GH_SDIO0_set_Control00Reg_IntAtBlkGap(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.intatblkgap = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_IntAtBlkGap] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_IntAtBlkGap(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_IntAtBlkGap] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.intatblkgap;
}
void GH_SDIO0_set_Control00Reg_DriveCcsd(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.driveccsd = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_DriveCcsd] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_DriveCcsd(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_DriveCcsd] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.driveccsd;
}
void GH_SDIO0_set_Control00Reg_SpiMode(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.spimode = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_SpiMode] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_SpiMode(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_SpiMode] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.spimode;
}
void GH_SDIO0_set_Control00Reg_BootEn(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.booten = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_BootEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_BootEn(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_BootEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.booten;
}
void GH_SDIO0_set_Control00Reg_AltBootEn(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.altbooten = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_AltBootEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_AltBootEn(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_AltBootEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.altbooten;
}
void GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardIns(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.wakeupevetenoncardins = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardIns] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardIns(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardIns] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.wakeupevetenoncardins;
}
void GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardInt(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.wakeupevetenoncardint = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardInt] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardInt(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardInt] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.wakeupevetenoncardint;
}
void GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardRem(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.wakeupevetenoncardrem = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardRem] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardRem(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardRem] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.wakeupevetenoncardrem;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_PresentStateReg (read)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SDIO0_get_PresentStateReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return value;
}
U8   GH_SDIO0_get_PresentStateReg_CmdInhibitCmd(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CmdInhibitCmd] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cmdinhibitcmd;
}
U8   GH_SDIO0_get_PresentStateReg_DataLineActive(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_DataLineActive] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.datalineactive;
}
U8   GH_SDIO0_get_PresentStateReg_CmdInhibitData(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CmdInhibitData] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cmdinhibitdata;
}
U8   GH_SDIO0_get_PresentStateReg_RTraActive(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_RTraActive] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.rtraactive;
}
U8   GH_SDIO0_get_PresentStateReg_BufWEn(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_BufWEn] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.bufwen;
}
U8   GH_SDIO0_get_PresentStateReg_WTraActive(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_WTraActive] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.wtraactive;
}
U8   GH_SDIO0_get_PresentStateReg_BufREn(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_BufREn] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.bufren;
}
U8   GH_SDIO0_get_PresentStateReg_CardInserted(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CardInserted] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cardinserted;
}
U8   GH_SDIO0_get_PresentStateReg_CardDetectPinLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CardDetectPinLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.carddetectpinlevel;
}
U8   GH_SDIO0_get_PresentStateReg_CardStateStable(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CardStateStable] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cardstatestable;
}
U8   GH_SDIO0_get_PresentStateReg_WProSwiPinLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_WProSwiPinLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.wproswipinlevel;
}
U8   GH_SDIO0_get_PresentStateReg_Data03LineSigLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_Data03LineSigLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.data03linesiglevel;
}
U8   GH_SDIO0_get_PresentStateReg_CmdLineSigLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CmdLineSigLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cmdlinesiglevel;
}
U8   GH_SDIO0_get_PresentStateReg_Data47LineSigLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_Data47LineSigLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.data47linesiglevel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ArgReg (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_ArgReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_ARGREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ArgReg] <-- 0x%08x\n",
                        REG_SDIO0_ARGREG,data,data);
    #endif
}
U32  GH_SDIO0_get_ArgReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_ARGREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ArgReg] --> 0x%08x\n",
                        REG_SDIO0_ARGREG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_CapReg (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SDIO0_get_CapReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return value;
}
U8   GH_SDIO0_get_CapReg_TimeoutClkFre(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_TimeoutClkFre] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.timeoutclkfre;
}
U8   GH_SDIO0_get_CapReg_TimeoutClkUnit(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_TimeoutClkUnit] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.timeoutclkunit;
}
U8   GH_SDIO0_get_CapReg_BaseClkFreForSdClk(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_BaseClkFreForSdClk] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.baseclkfreforsdclk;
}
U8   GH_SDIO0_get_CapReg_MaxBlkLen(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_MaxBlkLen] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.maxblklen;
}
U8   GH_SDIO0_get_CapReg_ExtendedMediaBusSup(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_ExtendedMediaBusSup] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.extendedmediabussup;
}
U8   GH_SDIO0_get_CapReg_HighSpeedSup(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_HighSpeedSup] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.highspeedsup;
}
U8   GH_SDIO0_get_CapReg_SusResSup(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_SusResSup] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.susressup;
}
U8   GH_SDIO0_get_CapReg_SdmaSup(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_SdmaSup] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.sdmasup;
}
U8   GH_SDIO0_get_CapReg_VoltageSup33v(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_VoltageSup33v] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.voltagesup33v;
}
U8   GH_SDIO0_get_CapReg_VoltageSup30v(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_VoltageSup30v] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.voltagesup30v;
}
U8   GH_SDIO0_get_CapReg_VoltageSup18v(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_VoltageSup18v] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.voltagesup18v;
}
U8   GH_SDIO0_get_CapReg_IntMode(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_IntMode] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.intmode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_AutoCmd12ErrStatusReg (read)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SDIO0_get_AutoCmd12ErrStatusReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return value;
}
U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12timeouterr;
}
U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12crcerr;
}
U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12endbiterr;
}
U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12notexe;
}
U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12indexerr;
}
U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.cmdnotissuedbyautocmd12err;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_BufferDataPortReg (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_BufferDataPortReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_BUFFERDATAPORTREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BufferDataPortReg] <-- 0x%08x\n",
                        REG_SDIO0_BUFFERDATAPORTREG,data,data);
    #endif
}
U32  GH_SDIO0_get_BufferDataPortReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_BUFFERDATAPORTREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BufferDataPortReg] --> 0x%08x\n",
                        REG_SDIO0_BUFFERDATAPORTREG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_MaxCurCapReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_MaxCurCapReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_MAXCURCAPREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_MaxCurCapReg] <-- 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,data,data);
    #endif
}
U32  GH_SDIO0_get_MaxCurCapReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_MAXCURCAPREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_MaxCurCapReg] --> 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_MaxCurCapReg_MaxCurFor33v(U8 data)
{
    GH_SDIO0_MAXCURCAPREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_MAXCURCAPREG;
    d.bitc.maxcurfor33v = data;
    *(volatile U32 *)REG_SDIO0_MAXCURCAPREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_MaxCurCapReg_MaxCurFor33v] <-- 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_MaxCurCapReg_MaxCurFor33v(void)
{
    GH_SDIO0_MAXCURCAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_MAXCURCAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_MaxCurCapReg_MaxCurFor33v] --> 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,value);
    #endif
    return tmp_value.bitc.maxcurfor33v;
}
void GH_SDIO0_set_MaxCurCapReg_MaxCurFor30v(U8 data)
{
    GH_SDIO0_MAXCURCAPREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_MAXCURCAPREG;
    d.bitc.maxcurfor30v = data;
    *(volatile U32 *)REG_SDIO0_MAXCURCAPREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_MaxCurCapReg_MaxCurFor30v] <-- 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_MaxCurCapReg_MaxCurFor30v(void)
{
    GH_SDIO0_MAXCURCAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_MAXCURCAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_MaxCurCapReg_MaxCurFor30v] --> 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,value);
    #endif
    return tmp_value.bitc.maxcurfor30v;
}
void GH_SDIO0_set_MaxCurCapReg_MaxCurFor18v(U8 data)
{
    GH_SDIO0_MAXCURCAPREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_MAXCURCAPREG;
    d.bitc.maxcurfor18v = data;
    *(volatile U32 *)REG_SDIO0_MAXCURCAPREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_MaxCurCapReg_MaxCurFor18v] <-- 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_MaxCurCapReg_MaxCurFor18v(void)
{
    GH_SDIO0_MAXCURCAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_MAXCURCAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_MaxCurCapReg_MaxCurFor18v] --> 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,value);
    #endif
    return tmp_value.bitc.maxcurfor18v;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_SlotIntStatusReg (read)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SDIO0_get_SlotIntStatusReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_SLOTINTSTATUSREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SlotIntStatusReg] --> 0x%08x\n",
                        REG_SDIO0_SLOTINTSTATUSREG,value);
    #endif
    return value;
}
U8   GH_SDIO0_get_SlotIntStatusReg_IntSigForEachSlot(void)
{
    GH_SDIO0_SLOTINTSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_SLOTINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SlotIntStatusReg_IntSigForEachSlot] --> 0x%08x\n",
                        REG_SDIO0_SLOTINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.intsigforeachslot;
}
U8   GH_SDIO0_get_SlotIntStatusReg_SpecifiVerNum(void)
{
    GH_SDIO0_SLOTINTSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_SLOTINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SlotIntStatusReg_SpecifiVerNum] --> 0x%08x\n",
                        REG_SDIO0_SLOTINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.specifivernum;
}
U8   GH_SDIO0_get_SlotIntStatusReg_VendorVerNum(void)
{
    GH_SDIO0_SLOTINTSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_SLOTINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SlotIntStatusReg_VendorVerNum] --> 0x%08x\n",
                        REG_SDIO0_SLOTINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.vendorvernum;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_SDIO0_init(void)
{
    GH_SDIO0_set_SysAddrReg((U32)0x00000000);
    GH_SDIO0_set_TranModeNorIntSigEnReg((U32)0x00000000);
    GH_SDIO0_set_ErrIntSigEnBlkCouReg((U32)0x00000000);
    GH_SDIO0_set_BlkSizeNorIntStaEnReg((U32)0x00000000);
    GH_SDIO0_set_ErrIntStaEnNorIntStaReg((U32)0x00000000);
    GH_SDIO0_set_ErrIntStatusCommondReg((U32)0x00000000);
    GH_SDIO0_set_Control01Reg((U32)0x00000000);
    GH_SDIO0_set_Control00Reg((U32)0x00000000);
    GH_SDIO0_set_ArgReg((U32)0x00000000);
    GH_SDIO0_set_MaxCurCapReg((U32)0x00000001);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

