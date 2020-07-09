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
/* register SDIO0_TranModeReg (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_TranModeReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_TRANMODEREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,data,data);
    #endif
}
U16  GH_SDIO0_get_TranModeReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_TranModeReg_BlkCountEn(U8 data)
{
    GH_SDIO0_TRANMODEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG;
    d.bitc.blkcounten = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_BlkCountEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeReg_BlkCountEn(void)
{
    GH_SDIO0_TRANMODEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_BlkCountEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.blkcounten;
}
void GH_SDIO0_set_TranModeReg_AutoCmd12En(U8 data)
{
    GH_SDIO0_TRANMODEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG;
    d.bitc.autocmd12en = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_AutoCmd12En] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeReg_AutoCmd12En(void)
{
    GH_SDIO0_TRANMODEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_AutoCmd12En] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.autocmd12en;
}
void GH_SDIO0_set_TranModeReg_DmaEn(U8 data)
{
    GH_SDIO0_TRANMODEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG;
    d.bitc.dmaen = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_DmaEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeReg_DmaEn(void)
{
    GH_SDIO0_TRANMODEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_DmaEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.dmaen;
}
void GH_SDIO0_set_TranModeReg_MSBlkSelect(U8 data)
{
    GH_SDIO0_TRANMODEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG;
    d.bitc.msblkselect = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_MSBlkSelect] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeReg_MSBlkSelect(void)
{
    GH_SDIO0_TRANMODEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_MSBlkSelect] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.msblkselect;
}
void GH_SDIO0_set_TranModeReg_DataTraDirSelect(U8 data)
{
    GH_SDIO0_TRANMODEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG;
    d.bitc.datatradirselect = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_DataTraDirSelect] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_TranModeReg_DataTraDirSelect(void)
{
    GH_SDIO0_TRANMODEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_DataTraDirSelect] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.datatradirselect;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_NorIntSigEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_NorIntSigEnReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,data,data);
    #endif
}
U16  GH_SDIO0_get_NorIntSigEnReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_NorIntSigEnReg_CmdCompleteSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.cmdcompletesigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_CmdCompleteSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntSigEnReg_CmdCompleteSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_CmdCompleteSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdcompletesigen;
}
void GH_SDIO0_set_NorIntSigEnReg_TraCompleteSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.tracompletesigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_TraCompleteSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntSigEnReg_TraCompleteSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_TraCompleteSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.tracompletesigen;
}
void GH_SDIO0_set_NorIntSigEnReg_BlkGapEveSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.blkgapevesigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_BlkGapEveSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntSigEnReg_BlkGapEveSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_BlkGapEveSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.blkgapevesigen;
}
void GH_SDIO0_set_NorIntSigEnReg_DmaIntSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.dmaintsigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_DmaIntSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntSigEnReg_DmaIntSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_DmaIntSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.dmaintsigen;
}
void GH_SDIO0_set_NorIntSigEnReg_BufWReadySigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.bufwreadysigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_BufWReadySigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntSigEnReg_BufWReadySigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_BufWReadySigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.bufwreadysigen;
}
void GH_SDIO0_set_NorIntSigEnReg_BufRReadySigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.bufrreadysigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_BufRReadySigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntSigEnReg_BufRReadySigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_BufRReadySigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.bufrreadysigen;
}
void GH_SDIO0_set_NorIntSigEnReg_CardInsertionSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.cardinsertionsigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_CardInsertionSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntSigEnReg_CardInsertionSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_CardInsertionSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardinsertionsigen;
}
void GH_SDIO0_set_NorIntSigEnReg_CardRemSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.cardremsigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_CardRemSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntSigEnReg_CardRemSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_CardRemSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardremsigen;
}
void GH_SDIO0_set_NorIntSigEnReg_CardIntSigEN(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.cardintsigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_CardIntSigEN] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntSigEnReg_CardIntSigEN(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_CardIntSigEN] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardintsigen;
}
void GH_SDIO0_set_NorIntSigEnReg_FixedTo0(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.fixedto0 = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_FixedTo0] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntSigEnReg_FixedTo0(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_FixedTo0] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.fixedto0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntSigEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_ErrIntSigEnReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,data,data);
    #endif
}
U16  GH_SDIO0_get_ErrIntSigEnReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_ErrIntSigEnReg_CmdTimeoutErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.cmdtimeouterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_CmdTimeoutErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnReg_CmdTimeoutErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_CmdTimeoutErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterrsigen;
}
void GH_SDIO0_set_ErrIntSigEnReg_CmdEndBitErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.cmdendbiterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_CmdEndBitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnReg_CmdEndBitErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_CmdEndBitErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterrsigen;
}
void GH_SDIO0_set_ErrIntSigEnReg_CmdIndexErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.cmdindexerrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_CmdIndexErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnReg_CmdIndexErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_CmdIndexErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdindexerrsigen;
}
void GH_SDIO0_set_ErrIntSigEnReg_DataTimeoutErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.datatimeouterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_DataTimeoutErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnReg_DataTimeoutErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_DataTimeoutErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.datatimeouterrsigen;
}
void GH_SDIO0_set_ErrIntSigEnReg_CmdCrcErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.cmdcrcerrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_CmdCrcErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnReg_CmdCrcErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_CmdCrcErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerrsigen;
}
void GH_SDIO0_set_ErrIntSigEnReg_DataCrcErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.datacrcerrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_DataCrcErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnReg_DataCrcErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_DataCrcErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.datacrcerrsigen;
}
void GH_SDIO0_set_ErrIntSigEnReg_DataEndBitErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.dataendbiterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_DataEndBitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnReg_DataEndBitErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_DataEndBitErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.dataendbiterrsigen;
}
void GH_SDIO0_set_ErrIntSigEnReg_CurLimitErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.curlimiterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_CurLimitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnReg_CurLimitErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_CurLimitErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.curlimiterrsigen;
}
void GH_SDIO0_set_ErrIntSigEnReg_AutoCmd12ErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.autocmd12errsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_AutoCmd12ErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnReg_AutoCmd12ErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_AutoCmd12ErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.autocmd12errsigen;
}
void GH_SDIO0_set_ErrIntSigEnReg_VendorSpecificErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.vendorspecificerrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_VendorSpecificErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntSigEnReg_VendorSpecificErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_VendorSpecificErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrsigen;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_BlkCouReg (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_BlkCouReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_BLKCOUREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkCouReg] <-- 0x%08x\n",
                        REG_SDIO0_BLKCOUREG,data,data);
    #endif
}
U16  GH_SDIO0_get_BlkCouReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKCOUREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkCouReg] --> 0x%08x\n",
                        REG_SDIO0_BLKCOUREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_BlkCouReg_BlkCountForCurTra(U16 data)
{
    GH_SDIO0_BLKCOUREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_BLKCOUREG;
    d.bitc.blkcountforcurtra = data;
    *(volatile U16 *)REG_SDIO0_BLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkCouReg_BlkCountForCurTra] <-- 0x%08x\n",
                        REG_SDIO0_BLKCOUREG,d.all,d.all);
    #endif
}
U16  GH_SDIO0_get_BlkCouReg_BlkCountForCurTra(void)
{
    GH_SDIO0_BLKCOUREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkCouReg_BlkCountForCurTra] --> 0x%08x\n",
                        REG_SDIO0_BLKCOUREG,value);
    #endif
    return tmp_value.bitc.blkcountforcurtra;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_BlkSizeReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_BlkSizeReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_BLKSIZEREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeReg] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,data,data);
    #endif
}
U16  GH_SDIO0_get_BlkSizeReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKSIZEREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeReg] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_BlkSizeReg_TraBlkSize(U16 data)
{
    GH_SDIO0_BLKSIZEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_BLKSIZEREG;
    d.bitc.trablksize = data;
    *(volatile U16 *)REG_SDIO0_BLKSIZEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeReg_TraBlkSize] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,d.all,d.all);
    #endif
}
U16  GH_SDIO0_get_BlkSizeReg_TraBlkSize(void)
{
    GH_SDIO0_BLKSIZEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKSIZEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeReg_TraBlkSize] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,value);
    #endif
    return tmp_value.bitc.trablksize;
}
void GH_SDIO0_set_BlkSizeReg_HostSdmaBufSize(U8 data)
{
    GH_SDIO0_BLKSIZEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_BLKSIZEREG;
    d.bitc.hostsdmabufsize = data;
    *(volatile U16 *)REG_SDIO0_BLKSIZEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeReg_HostSdmaBufSize] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_BlkSizeReg_HostSdmaBufSize(void)
{
    GH_SDIO0_BLKSIZEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKSIZEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeReg_HostSdmaBufSize] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,value);
    #endif
    return tmp_value.bitc.hostsdmabufsize;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_NorIntStaEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_NorIntStaEnReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,data,data);
    #endif
}
U16  GH_SDIO0_get_NorIntStaEnReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_NorIntStaEnReg_CmdCompleteStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.cmdcompletestatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_CmdCompleteStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaEnReg_CmdCompleteStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_CmdCompleteStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdcompletestatusen;
}
void GH_SDIO0_set_NorIntStaEnReg_TraCompleteStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.tracompletestatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_TraCompleteStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaEnReg_TraCompleteStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_TraCompleteStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.tracompletestatusen;
}
void GH_SDIO0_set_NorIntStaEnReg_BlkGapEveStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.blkgapevestatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_BlkGapEveStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaEnReg_BlkGapEveStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_BlkGapEveStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.blkgapevestatusen;
}
void GH_SDIO0_set_NorIntStaEnReg_DmaIntStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.dmaintstatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_DmaIntStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaEnReg_DmaIntStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_DmaIntStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.dmaintstatusen;
}
void GH_SDIO0_set_NorIntStaEnReg_BufWReadyStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.bufwreadystatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_BufWReadyStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaEnReg_BufWReadyStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_BufWReadyStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.bufwreadystatusen;
}
void GH_SDIO0_set_NorIntStaEnReg_BufRReadyStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.bufrreadystatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_BufRReadyStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaEnReg_BufRReadyStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_BufRReadyStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.bufrreadystatusen;
}
void GH_SDIO0_set_NorIntStaEnReg_CardInsertionStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.cardinsertionstatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_CardInsertionStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaEnReg_CardInsertionStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_CardInsertionStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardinsertionstatusen;
}
void GH_SDIO0_set_NorIntStaEnReg_CardRemStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.cardremstatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_CardRemStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaEnReg_CardRemStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_CardRemStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardremstatusen;
}
void GH_SDIO0_set_NorIntStaEnReg_CardIntStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.cardintstatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_CardIntStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaEnReg_CardIntStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_CardIntStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardintstatusen;
}
void GH_SDIO0_set_NorIntStaEnReg_FixedTo0(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.fixedto0 = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_FixedTo0] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaEnReg_FixedTo0(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_FixedTo0] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.fixedto0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntStaEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_ErrIntStaEnReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,data,data);
    #endif
}
U16  GH_SDIO0_get_ErrIntStaEnReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.cmdtimeouterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnReg_CmdEndBitErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.cmdendbiterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CmdEndBitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnReg_CmdEndBitErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CmdEndBitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnReg_CmdCrcErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.cmdcrcerrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CmdCrcErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnReg_CmdCrcErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CmdCrcErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnReg_CmdIndexErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.cmdindexerrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CmdIndexErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnReg_CmdIndexErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CmdIndexErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdindexerrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnReg_DataCrcErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.datacrcerrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_DataCrcErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnReg_DataCrcErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_DataCrcErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.datacrcerrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnReg_DataTimeoutErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.datatimeouterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_DataTimeoutErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnReg_DataTimeoutErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_DataTimeoutErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.datatimeouterrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnReg_DataEndBitErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.dataendbiterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_DataEndBitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnReg_DataEndBitErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_DataEndBitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.dataendbiterrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnReg_CurLimitErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.curlimiterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CurLimitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnReg_CurLimitErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CurLimitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.curlimiterrstatusen;
}
void GH_SDIO0_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.autocmd12errstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.autocmd12errstatusen;
}
void GH_SDIO0_set_ErrIntStaEnReg_VendorSpecificErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.vendorspecificerrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_VendorSpecificErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStaEnReg_VendorSpecificErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_VendorSpecificErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrstatusen;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_NorIntStaReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_NorIntStaReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,data,data);
    #endif
}
U16  GH_SDIO0_get_NorIntStaReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_NorIntStaReg_CmdComplete(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.cmdcomplete = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_CmdComplete] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaReg_CmdComplete(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_CmdComplete] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdcomplete;
}
void GH_SDIO0_set_NorIntStaReg_BlkGapEvent(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.blkgapevent = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_BlkGapEvent] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaReg_BlkGapEvent(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_BlkGapEvent] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.blkgapevent;
}
void GH_SDIO0_set_NorIntStaReg_DmaInt(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.dmaint = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_DmaInt] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaReg_DmaInt(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_DmaInt] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.dmaint;
}
void GH_SDIO0_set_NorIntStaReg_TraComplete(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.tracomplete = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_TraComplete] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaReg_TraComplete(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_TraComplete] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.tracomplete;
}
void GH_SDIO0_set_NorIntStaReg_BufWReady(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.bufwready = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_BufWReady] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaReg_BufWReady(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_BufWReady] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bufwready;
}
void GH_SDIO0_set_NorIntStaReg_CardInsertion(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.cardinsertion = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_CardInsertion] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaReg_CardInsertion(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_CardInsertion] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardinsertion;
}
void GH_SDIO0_set_NorIntStaReg_BufRReady(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.bufrready = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_BufRReady] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaReg_BufRReady(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_BufRReady] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bufrready;
}
void GH_SDIO0_set_NorIntStaReg_CardRemoval(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.cardremoval = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_CardRemoval] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaReg_CardRemoval(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_CardRemoval] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardremoval;
}
void GH_SDIO0_set_NorIntStaReg_CardInt(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.cardint = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_CardInt] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaReg_CardInt(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_CardInt] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardint;
}
void GH_SDIO0_set_NorIntStaReg_BootAckRcv(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.bootackrcv = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_BootAckRcv] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaReg_BootAckRcv(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_BootAckRcv] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bootackrcv;
}
void GH_SDIO0_set_NorIntStaReg_ErrInt(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.errint = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_ErrInt] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_NorIntStaReg_ErrInt(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_ErrInt] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.errint;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntStatusReg (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_ErrIntStatusReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,data,data);
    #endif
}
U16  GH_SDIO0_get_ErrIntStatusReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_ErrIntStatusReg_CmdTimeoutErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.cmdtimeouterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_CmdTimeoutErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusReg_CmdTimeoutErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_CmdTimeoutErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterr;
}
void GH_SDIO0_set_ErrIntStatusReg_CmdCrcErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.cmdcrcerr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_CmdCrcErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusReg_CmdCrcErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_CmdCrcErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerr;
}
void GH_SDIO0_set_ErrIntStatusReg_CmdEndBitErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.cmdendbiterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_CmdEndBitErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusReg_CmdEndBitErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_CmdEndBitErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterr;
}
void GH_SDIO0_set_ErrIntStatusReg_CmdIndexErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.cmdindexerr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_CmdIndexErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusReg_CmdIndexErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_CmdIndexErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.cmdindexerr;
}
void GH_SDIO0_set_ErrIntStatusReg_DataTimeoutErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.datatimeouterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_DataTimeoutErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusReg_DataTimeoutErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_DataTimeoutErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.datatimeouterr;
}
void GH_SDIO0_set_ErrIntStatusReg_DataCrcErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.datacrcerr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_DataCrcErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusReg_DataCrcErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_DataCrcErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.datacrcerr;
}
void GH_SDIO0_set_ErrIntStatusReg_DataEndBitErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.dataendbiterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_DataEndBitErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusReg_DataEndBitErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_DataEndBitErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.dataendbiterr;
}
void GH_SDIO0_set_ErrIntStatusReg_CurLimitErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.curlimiterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_CurLimitErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusReg_CurLimitErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_CurLimitErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.curlimiterr;
}
void GH_SDIO0_set_ErrIntStatusReg_AutoCmd12Err(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.autocmd12err = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_AutoCmd12Err] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusReg_AutoCmd12Err(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_AutoCmd12Err] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12err;
}
void GH_SDIO0_set_ErrIntStatusReg_VendorSpecificErrStatus(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.vendorspecificerrstatus = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_VendorSpecificErrStatus] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ErrIntStatusReg_VendorSpecificErrStatus(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_VendorSpecificErrStatus] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrstatus;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_CommondReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_CommondReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_COMMONDREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,data,data);
    #endif
}
U16  GH_SDIO0_get_CommondReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_CommondReg_RepTypeSelect(U8 data)
{
    GH_SDIO0_COMMONDREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_COMMONDREG;
    d.bitc.reptypeselect = data;
    *(volatile U16 *)REG_SDIO0_COMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg_RepTypeSelect] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_CommondReg_RepTypeSelect(void)
{
    GH_SDIO0_COMMONDREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg_RepTypeSelect] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return tmp_value.bitc.reptypeselect;
}
void GH_SDIO0_set_CommondReg_CmdCrcCheckEn(U8 data)
{
    GH_SDIO0_COMMONDREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_COMMONDREG;
    d.bitc.cmdcrcchecken = data;
    *(volatile U16 *)REG_SDIO0_COMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg_CmdCrcCheckEn] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_CommondReg_CmdCrcCheckEn(void)
{
    GH_SDIO0_COMMONDREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg_CmdCrcCheckEn] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdcrcchecken;
}
void GH_SDIO0_set_CommondReg_DataPreSelect(U8 data)
{
    GH_SDIO0_COMMONDREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_COMMONDREG;
    d.bitc.datapreselect = data;
    *(volatile U16 *)REG_SDIO0_COMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg_DataPreSelect] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_CommondReg_DataPreSelect(void)
{
    GH_SDIO0_COMMONDREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg_DataPreSelect] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return tmp_value.bitc.datapreselect;
}
void GH_SDIO0_set_CommondReg_CmdIndexCheckEn(U8 data)
{
    GH_SDIO0_COMMONDREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_COMMONDREG;
    d.bitc.cmdindexchecken = data;
    *(volatile U16 *)REG_SDIO0_COMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg_CmdIndexCheckEn] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_CommondReg_CmdIndexCheckEn(void)
{
    GH_SDIO0_COMMONDREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg_CmdIndexCheckEn] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdindexchecken;
}
void GH_SDIO0_set_CommondReg_CmdType(U8 data)
{
    GH_SDIO0_COMMONDREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_COMMONDREG;
    d.bitc.cmdtype = data;
    *(volatile U16 *)REG_SDIO0_COMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg_CmdType] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_CommondReg_CmdType(void)
{
    GH_SDIO0_COMMONDREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg_CmdType] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdtype;
}
void GH_SDIO0_set_CommondReg_CmdIndex(U8 data)
{
    GH_SDIO0_COMMONDREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_COMMONDREG;
    d.bitc.cmdindex = data;
    *(volatile U16 *)REG_SDIO0_COMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg_CmdIndex] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_CommondReg_CmdIndex(void)
{
    GH_SDIO0_COMMONDREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg_CmdIndex] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdindex;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_SoftResetReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_SoftResetReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_SOFTRESETREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SoftResetReg] <-- 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,data,data);
    #endif
}
U16  GH_SDIO0_get_SoftResetReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_SOFTRESETREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SoftResetReg] --> 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_SoftResetReg_DataTimeoutCounterValue(U8 data)
{
    GH_SDIO0_SOFTRESETREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_SOFTRESETREG;
    d.bitc.datatimeoutcountervalue = data;
    *(volatile U16 *)REG_SDIO0_SOFTRESETREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SoftResetReg_DataTimeoutCounterValue] <-- 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_SoftResetReg_DataTimeoutCounterValue(void)
{
    GH_SDIO0_SOFTRESETREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_SOFTRESETREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SoftResetReg_DataTimeoutCounterValue] --> 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,value);
    #endif
    return tmp_value.bitc.datatimeoutcountervalue;
}
void GH_SDIO0_set_SoftResetReg_SoftwareResetCmdLine(U8 data)
{
    GH_SDIO0_SOFTRESETREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_SOFTRESETREG;
    d.bitc.softwareresetcmdline = data;
    *(volatile U16 *)REG_SDIO0_SOFTRESETREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SoftResetReg_SoftwareResetCmdLine] <-- 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_SoftResetReg_SoftwareResetCmdLine(void)
{
    GH_SDIO0_SOFTRESETREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_SOFTRESETREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SoftResetReg_SoftwareResetCmdLine] --> 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,value);
    #endif
    return tmp_value.bitc.softwareresetcmdline;
}
void GH_SDIO0_set_SoftResetReg_SoftwareResetAll(U8 data)
{
    GH_SDIO0_SOFTRESETREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_SOFTRESETREG;
    d.bitc.softwareresetall = data;
    *(volatile U16 *)REG_SDIO0_SOFTRESETREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SoftResetReg_SoftwareResetAll] <-- 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_SoftResetReg_SoftwareResetAll(void)
{
    GH_SDIO0_SOFTRESETREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_SOFTRESETREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SoftResetReg_SoftwareResetAll] --> 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,value);
    #endif
    return tmp_value.bitc.softwareresetall;
}
void GH_SDIO0_set_SoftResetReg_SoftwareResetDatLine(U8 data)
{
    GH_SDIO0_SOFTRESETREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_SOFTRESETREG;
    d.bitc.softwareresetdatline = data;
    *(volatile U16 *)REG_SDIO0_SOFTRESETREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SoftResetReg_SoftwareResetDatLine] <-- 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_SoftResetReg_SoftwareResetDatLine(void)
{
    GH_SDIO0_SOFTRESETREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_SOFTRESETREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SoftResetReg_SoftwareResetDatLine] --> 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,value);
    #endif
    return tmp_value.bitc.softwareresetdatline;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ClkControlReg (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SDIO0_set_ClkControlReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_CLKCONTROLREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ClkControlReg] <-- 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,data,data);
    #endif
}
U16  GH_SDIO0_get_ClkControlReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_CLKCONTROLREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ClkControlReg] --> 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,value);
    #endif
    return value;
}
void GH_SDIO0_set_ClkControlReg_InternalClkEn(U8 data)
{
    GH_SDIO0_CLKCONTROLREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CLKCONTROLREG;
    d.bitc.internalclken = data;
    *(volatile U16 *)REG_SDIO0_CLKCONTROLREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ClkControlReg_InternalClkEn] <-- 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ClkControlReg_InternalClkEn(void)
{
    GH_SDIO0_CLKCONTROLREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CLKCONTROLREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ClkControlReg_InternalClkEn] --> 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,value);
    #endif
    return tmp_value.bitc.internalclken;
}
void GH_SDIO0_set_ClkControlReg_InternalClkStable(U8 data)
{
    GH_SDIO0_CLKCONTROLREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CLKCONTROLREG;
    d.bitc.internalclkstable = data;
    *(volatile U16 *)REG_SDIO0_CLKCONTROLREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ClkControlReg_InternalClkStable] <-- 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ClkControlReg_InternalClkStable(void)
{
    GH_SDIO0_CLKCONTROLREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CLKCONTROLREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ClkControlReg_InternalClkStable] --> 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,value);
    #endif
    return tmp_value.bitc.internalclkstable;
}
void GH_SDIO0_set_ClkControlReg_SdClkEn(U8 data)
{
    GH_SDIO0_CLKCONTROLREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CLKCONTROLREG;
    d.bitc.sdclken = data;
    *(volatile U16 *)REG_SDIO0_CLKCONTROLREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ClkControlReg_SdClkEn] <-- 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ClkControlReg_SdClkEn(void)
{
    GH_SDIO0_CLKCONTROLREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CLKCONTROLREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ClkControlReg_SdClkEn] --> 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,value);
    #endif
    return tmp_value.bitc.sdclken;
}
void GH_SDIO0_set_ClkControlReg_SdclkFreSelect(U8 data)
{
    GH_SDIO0_CLKCONTROLREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CLKCONTROLREG;
    d.bitc.sdclkfreselect = data;
    *(volatile U16 *)REG_SDIO0_CLKCONTROLREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ClkControlReg_SdclkFreSelect] <-- 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,d.all,d.all);
    #endif
}
U8   GH_SDIO0_get_ClkControlReg_SdclkFreSelect(void)
{
    GH_SDIO0_CLKCONTROLREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CLKCONTROLREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ClkControlReg_SdclkFreSelect] --> 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,value);
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
    GH_SDIO0_set_TranModeReg((U16)0x0000);
    GH_SDIO0_set_NorIntSigEnReg((U16)0x0000);
    GH_SDIO0_set_ErrIntSigEnReg((U16)0x0000);
    GH_SDIO0_set_BlkCouReg((U16)0x0000);
    GH_SDIO0_set_BlkSizeReg((U16)0x0000);
    GH_SDIO0_set_NorIntStaEnReg((U16)0x0000);
    GH_SDIO0_set_ErrIntStaEnReg((U16)0x0000);
    GH_SDIO0_set_NorIntStaReg((U16)0x0000);
    GH_SDIO0_set_ErrIntStatusReg((U16)0x0000);
    GH_SDIO0_set_CommondReg((U16)0x0000);
    GH_SDIO0_set_SoftResetReg((U16)0x0000);
    GH_SDIO0_set_ClkControlReg((U16)0x0000);
    GH_SDIO0_set_Control00Reg((U32)0x00000000);
    GH_SDIO0_set_ArgReg((U32)0x00000000);
    GH_SDIO0_set_MaxCurCapReg((U32)0x00000001);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

