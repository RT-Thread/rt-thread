/******************************************************************************
**
** \file      gh_eth.c
**
** \brief     Ethernet controller.
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
#include "gh_eth.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register ETH_MCR (read/write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_MCR(U32 data)
{
    *(volatile U32 *)REG_ETH_MCR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR] <-- 0x%08x\n",
                        REG_ETH_MCR,data,data);
    #endif
}
U32  GH_ETH_get_MCR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return value;
}
void GH_ETH_set_MCR_RE(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.re = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_RE] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_RE(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_RE] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.re;
}
void GH_ETH_set_MCR_TE(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.te = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_TE] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_TE(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_TE] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.te;
}
void GH_ETH_set_MCR_DC(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.dc = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_DC] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_DC(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_DC] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.dc;
}
void GH_ETH_set_MCR_BL(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.bl = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_BL] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_BL(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_BL] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.bl;
}
void GH_ETH_set_MCR_ACS(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.acs = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_ACS] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_ACS(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_ACS] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.acs;
}
void GH_ETH_set_MCR_LUD(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.lud = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_LUD] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_LUD(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_LUD] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.lud;
}
void GH_ETH_set_MCR_DR(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.dr = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_DR] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_DR(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_DR] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.dr;
}
void GH_ETH_set_MCR_IPC(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.ipc = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_IPC] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_IPC(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_IPC] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.ipc;
}
void GH_ETH_set_MCR_DM(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.dm = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_DM] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_DM(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_DM] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.dm;
}
void GH_ETH_set_MCR_LM(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.lm = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_LM] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_LM(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_LM] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.lm;
}
void GH_ETH_set_MCR_DRO(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.dro = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_DRO] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_DRO(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_DRO] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.dro;
}
void GH_ETH_set_MCR_FES(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.fes = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_FES] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_FES(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_FES] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.fes;
}
void GH_ETH_set_MCR_PS(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.ps = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_PS] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_PS(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_PS] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.ps;
}
void GH_ETH_set_MCR_DCRS(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.dcrs = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_DCRS] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_DCRS(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_DCRS] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.dcrs;
}
void GH_ETH_set_MCR_IFG(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.ifg = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_IFG] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_IFG(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_IFG] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.ifg;
}
void GH_ETH_set_MCR_JE(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.je = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_JE] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_JE(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_JE] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.je;
}
void GH_ETH_set_MCR_BE(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.be = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_BE] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_BE(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_BE] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.be;
}
void GH_ETH_set_MCR_JD(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.jd = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_JD] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_JD(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_JD] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.jd;
}
void GH_ETH_set_MCR_WD(U8 data)
{
    GH_ETH_MCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR;
    d.bitc.wd = data;
    *(volatile U32 *)REG_ETH_MCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MCR_WD] <-- 0x%08x\n",
                        REG_ETH_MCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MCR_WD(void)
{
    GH_ETH_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MCR_WD] --> 0x%08x\n",
                        REG_ETH_MCR,value);
    #endif
    return tmp_value.bitc.wd;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_GAR (read/write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_GAR(U32 data)
{
    *(volatile U32 *)REG_ETH_GAR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_GAR] <-- 0x%08x\n",
                        REG_ETH_GAR,data,data);
    #endif
}
U32  GH_ETH_get_GAR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_GAR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_GAR] --> 0x%08x\n",
                        REG_ETH_GAR,value);
    #endif
    return value;
}
void GH_ETH_set_GAR_GB(U8 data)
{
    GH_ETH_GAR_S d;
    d.all = *(volatile U32 *)REG_ETH_GAR;
    d.bitc.gb = data;
    *(volatile U32 *)REG_ETH_GAR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_GAR_GB] <-- 0x%08x\n",
                        REG_ETH_GAR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_GAR_GB(void)
{
    GH_ETH_GAR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_GAR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_GAR_GB] --> 0x%08x\n",
                        REG_ETH_GAR,value);
    #endif
    return tmp_value.bitc.gb;
}
void GH_ETH_set_GAR_GW(U8 data)
{
    GH_ETH_GAR_S d;
    d.all = *(volatile U32 *)REG_ETH_GAR;
    d.bitc.gw = data;
    *(volatile U32 *)REG_ETH_GAR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_GAR_GW] <-- 0x%08x\n",
                        REG_ETH_GAR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_GAR_GW(void)
{
    GH_ETH_GAR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_GAR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_GAR_GW] --> 0x%08x\n",
                        REG_ETH_GAR,value);
    #endif
    return tmp_value.bitc.gw;
}
void GH_ETH_set_GAR_CR(U8 data)
{
    GH_ETH_GAR_S d;
    d.all = *(volatile U32 *)REG_ETH_GAR;
    d.bitc.cr = data;
    *(volatile U32 *)REG_ETH_GAR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_GAR_CR] <-- 0x%08x\n",
                        REG_ETH_GAR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_GAR_CR(void)
{
    GH_ETH_GAR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_GAR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_GAR_CR] --> 0x%08x\n",
                        REG_ETH_GAR,value);
    #endif
    return tmp_value.bitc.cr;
}
void GH_ETH_set_GAR_GR(U8 data)
{
    GH_ETH_GAR_S d;
    d.all = *(volatile U32 *)REG_ETH_GAR;
    d.bitc.gr = data;
    *(volatile U32 *)REG_ETH_GAR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_GAR_GR] <-- 0x%08x\n",
                        REG_ETH_GAR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_GAR_GR(void)
{
    GH_ETH_GAR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_GAR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_GAR_GR] --> 0x%08x\n",
                        REG_ETH_GAR,value);
    #endif
    return tmp_value.bitc.gr;
}
void GH_ETH_set_GAR_PA(U8 data)
{
    GH_ETH_GAR_S d;
    d.all = *(volatile U32 *)REG_ETH_GAR;
    d.bitc.pa = data;
    *(volatile U32 *)REG_ETH_GAR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_GAR_PA] <-- 0x%08x\n",
                        REG_ETH_GAR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_GAR_PA(void)
{
    GH_ETH_GAR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_GAR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_GAR_PA] --> 0x%08x\n",
                        REG_ETH_GAR,value);
    #endif
    return tmp_value.bitc.pa;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_GDR (read/write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_GDR(U32 data)
{
    *(volatile U32 *)REG_ETH_GDR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_GDR] <-- 0x%08x\n",
                        REG_ETH_GDR,data,data);
    #endif
}
U32  GH_ETH_get_GDR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_GDR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_GDR] --> 0x%08x\n",
                        REG_ETH_GDR,value);
    #endif
    return value;
}
void GH_ETH_set_GDR_GD(U16 data)
{
    GH_ETH_GDR_S d;
    d.all = *(volatile U32 *)REG_ETH_GDR;
    d.bitc.gd = data;
    *(volatile U32 *)REG_ETH_GDR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_GDR_GD] <-- 0x%08x\n",
                        REG_ETH_GDR,d.all,d.all);
    #endif
}
U16  GH_ETH_get_GDR_GD(void)
{
    GH_ETH_GDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_GDR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_GDR_GD] --> 0x%08x\n",
                        REG_ETH_GDR,value);
    #endif
    return tmp_value.bitc.gd;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_MFFR (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_MFFR(U32 data)
{
    *(volatile U32 *)REG_ETH_MFFR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFFR] <-- 0x%08x\n",
                        REG_ETH_MFFR,data,data);
    #endif
}
U32  GH_ETH_get_MFFR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_MFFR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFFR] --> 0x%08x\n",
                        REG_ETH_MFFR,value);
    #endif
    return value;
}
void GH_ETH_set_MFFR_PR(U8 data)
{
    GH_ETH_MFFR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR;
    d.bitc.pr = data;
    *(volatile U32 *)REG_ETH_MFFR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFFR_PR] <-- 0x%08x\n",
                        REG_ETH_MFFR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFFR_PR(void)
{
    GH_ETH_MFFR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFFR_PR] --> 0x%08x\n",
                        REG_ETH_MFFR,value);
    #endif
    return tmp_value.bitc.pr;
}
void GH_ETH_set_MFFR_HUC(U8 data)
{
    GH_ETH_MFFR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR;
    d.bitc.huc = data;
    *(volatile U32 *)REG_ETH_MFFR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFFR_HUC] <-- 0x%08x\n",
                        REG_ETH_MFFR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFFR_HUC(void)
{
    GH_ETH_MFFR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFFR_HUC] --> 0x%08x\n",
                        REG_ETH_MFFR,value);
    #endif
    return tmp_value.bitc.huc;
}
void GH_ETH_set_MFFR_HMC(U8 data)
{
    GH_ETH_MFFR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR;
    d.bitc.hmc = data;
    *(volatile U32 *)REG_ETH_MFFR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFFR_HMC] <-- 0x%08x\n",
                        REG_ETH_MFFR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFFR_HMC(void)
{
    GH_ETH_MFFR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFFR_HMC] --> 0x%08x\n",
                        REG_ETH_MFFR,value);
    #endif
    return tmp_value.bitc.hmc;
}
void GH_ETH_set_MFFR_IFT(U8 data)
{
    GH_ETH_MFFR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR;
    d.bitc.ift = data;
    *(volatile U32 *)REG_ETH_MFFR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFFR_IFT] <-- 0x%08x\n",
                        REG_ETH_MFFR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFFR_IFT(void)
{
    GH_ETH_MFFR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFFR_IFT] --> 0x%08x\n",
                        REG_ETH_MFFR,value);
    #endif
    return tmp_value.bitc.ift;
}
void GH_ETH_set_MFFR_PM(U8 data)
{
    GH_ETH_MFFR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR;
    d.bitc.pm = data;
    *(volatile U32 *)REG_ETH_MFFR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFFR_PM] <-- 0x%08x\n",
                        REG_ETH_MFFR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFFR_PM(void)
{
    GH_ETH_MFFR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFFR_PM] --> 0x%08x\n",
                        REG_ETH_MFFR,value);
    #endif
    return tmp_value.bitc.pm;
}
void GH_ETH_set_MFFR_DB(U8 data)
{
    GH_ETH_MFFR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR;
    d.bitc.db = data;
    *(volatile U32 *)REG_ETH_MFFR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFFR_DB] <-- 0x%08x\n",
                        REG_ETH_MFFR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFFR_DB(void)
{
    GH_ETH_MFFR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFFR_DB] --> 0x%08x\n",
                        REG_ETH_MFFR,value);
    #endif
    return tmp_value.bitc.db;
}
void GH_ETH_set_MFFR_PCF(U8 data)
{
    GH_ETH_MFFR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR;
    d.bitc.pcf = data;
    *(volatile U32 *)REG_ETH_MFFR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFFR_PCF] <-- 0x%08x\n",
                        REG_ETH_MFFR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFFR_PCF(void)
{
    GH_ETH_MFFR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFFR_PCF] --> 0x%08x\n",
                        REG_ETH_MFFR,value);
    #endif
    return tmp_value.bitc.pcf;
}
void GH_ETH_set_MFFR_SAIF(U8 data)
{
    GH_ETH_MFFR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR;
    d.bitc.saif = data;
    *(volatile U32 *)REG_ETH_MFFR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFFR_SAIF] <-- 0x%08x\n",
                        REG_ETH_MFFR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFFR_SAIF(void)
{
    GH_ETH_MFFR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFFR_SAIF] --> 0x%08x\n",
                        REG_ETH_MFFR,value);
    #endif
    return tmp_value.bitc.saif;
}
void GH_ETH_set_MFFR_SAF(U8 data)
{
    GH_ETH_MFFR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR;
    d.bitc.saf = data;
    *(volatile U32 *)REG_ETH_MFFR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFFR_SAF] <-- 0x%08x\n",
                        REG_ETH_MFFR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFFR_SAF(void)
{
    GH_ETH_MFFR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFFR_SAF] --> 0x%08x\n",
                        REG_ETH_MFFR,value);
    #endif
    return tmp_value.bitc.saf;
}
void GH_ETH_set_MFFR_HPF(U8 data)
{
    GH_ETH_MFFR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR;
    d.bitc.hpf = data;
    *(volatile U32 *)REG_ETH_MFFR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFFR_HPF] <-- 0x%08x\n",
                        REG_ETH_MFFR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFFR_HPF(void)
{
    GH_ETH_MFFR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFFR_HPF] --> 0x%08x\n",
                        REG_ETH_MFFR,value);
    #endif
    return tmp_value.bitc.hpf;
}
void GH_ETH_set_MFFR_RA(U8 data)
{
    GH_ETH_MFFR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR;
    d.bitc.ra = data;
    *(volatile U32 *)REG_ETH_MFFR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFFR_RA] <-- 0x%08x\n",
                        REG_ETH_MFFR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFFR_RA(void)
{
    GH_ETH_MFFR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFFR_RA] --> 0x%08x\n",
                        REG_ETH_MFFR,value);
    #endif
    return tmp_value.bitc.ra;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_MHTRH (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_MHTRH(U32 data)
{
    *(volatile U32 *)REG_ETH_MHTRH = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MHTRH] <-- 0x%08x\n",
                        REG_ETH_MHTRH,data,data);
    #endif
}
U32  GH_ETH_get_MHTRH(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_MHTRH);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MHTRH] --> 0x%08x\n",
                        REG_ETH_MHTRH,value);
    #endif
    return value;
}
void GH_ETH_set_MHTRH_HTH(U32 data)
{
    GH_ETH_MHTRH_S d;
    d.all = *(volatile U32 *)REG_ETH_MHTRH;
    d.bitc.hth = data;
    *(volatile U32 *)REG_ETH_MHTRH = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MHTRH_HTH] <-- 0x%08x\n",
                        REG_ETH_MHTRH,d.all,d.all);
    #endif
}
U32  GH_ETH_get_MHTRH_HTH(void)
{
    GH_ETH_MHTRH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MHTRH);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MHTRH_HTH] --> 0x%08x\n",
                        REG_ETH_MHTRH,value);
    #endif
    return tmp_value.bitc.hth;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_MHTRL (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_MHTRL(U32 data)
{
    *(volatile U32 *)REG_ETH_MHTRL = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MHTRL] <-- 0x%08x\n",
                        REG_ETH_MHTRL,data,data);
    #endif
}
U32  GH_ETH_get_MHTRL(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_MHTRL);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MHTRL] --> 0x%08x\n",
                        REG_ETH_MHTRL,value);
    #endif
    return value;
}
void GH_ETH_set_MHTRL_HTL(U32 data)
{
    GH_ETH_MHTRL_S d;
    d.all = *(volatile U32 *)REG_ETH_MHTRL;
    d.bitc.htl = data;
    *(volatile U32 *)REG_ETH_MHTRL = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MHTRL_HTL] <-- 0x%08x\n",
                        REG_ETH_MHTRL,d.all,d.all);
    #endif
}
U32  GH_ETH_get_MHTRL_HTL(void)
{
    GH_ETH_MHTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MHTRL);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MHTRL_HTL] --> 0x%08x\n",
                        REG_ETH_MHTRL,value);
    #endif
    return tmp_value.bitc.htl;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_FCR (read/write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_FCR(U32 data)
{
    *(volatile U32 *)REG_ETH_FCR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_FCR] <-- 0x%08x\n",
                        REG_ETH_FCR,data,data);
    #endif
}
U32  GH_ETH_get_FCR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_FCR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_FCR] --> 0x%08x\n",
                        REG_ETH_FCR,value);
    #endif
    return value;
}
void GH_ETH_set_FCR_FCB(U8 data)
{
    GH_ETH_FCR_S d;
    d.all = *(volatile U32 *)REG_ETH_FCR;
    d.bitc.fcb = data;
    *(volatile U32 *)REG_ETH_FCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_FCR_FCB] <-- 0x%08x\n",
                        REG_ETH_FCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_FCR_FCB(void)
{
    GH_ETH_FCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_FCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_FCR_FCB] --> 0x%08x\n",
                        REG_ETH_FCR,value);
    #endif
    return tmp_value.bitc.fcb;
}
void GH_ETH_set_FCR_TFE(U8 data)
{
    GH_ETH_FCR_S d;
    d.all = *(volatile U32 *)REG_ETH_FCR;
    d.bitc.tfe = data;
    *(volatile U32 *)REG_ETH_FCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_FCR_TFE] <-- 0x%08x\n",
                        REG_ETH_FCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_FCR_TFE(void)
{
    GH_ETH_FCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_FCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_FCR_TFE] --> 0x%08x\n",
                        REG_ETH_FCR,value);
    #endif
    return tmp_value.bitc.tfe;
}
void GH_ETH_set_FCR_RFE(U8 data)
{
    GH_ETH_FCR_S d;
    d.all = *(volatile U32 *)REG_ETH_FCR;
    d.bitc.rfe = data;
    *(volatile U32 *)REG_ETH_FCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_FCR_RFE] <-- 0x%08x\n",
                        REG_ETH_FCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_FCR_RFE(void)
{
    GH_ETH_FCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_FCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_FCR_RFE] --> 0x%08x\n",
                        REG_ETH_FCR,value);
    #endif
    return tmp_value.bitc.rfe;
}
void GH_ETH_set_FCR_UP(U8 data)
{
    GH_ETH_FCR_S d;
    d.all = *(volatile U32 *)REG_ETH_FCR;
    d.bitc.up = data;
    *(volatile U32 *)REG_ETH_FCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_FCR_UP] <-- 0x%08x\n",
                        REG_ETH_FCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_FCR_UP(void)
{
    GH_ETH_FCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_FCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_FCR_UP] --> 0x%08x\n",
                        REG_ETH_FCR,value);
    #endif
    return tmp_value.bitc.up;
}
void GH_ETH_set_FCR_PLT(U8 data)
{
    GH_ETH_FCR_S d;
    d.all = *(volatile U32 *)REG_ETH_FCR;
    d.bitc.plt = data;
    *(volatile U32 *)REG_ETH_FCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_FCR_PLT] <-- 0x%08x\n",
                        REG_ETH_FCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_FCR_PLT(void)
{
    GH_ETH_FCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_FCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_FCR_PLT] --> 0x%08x\n",
                        REG_ETH_FCR,value);
    #endif
    return tmp_value.bitc.plt;
}
void GH_ETH_set_FCR_PT(U16 data)
{
    GH_ETH_FCR_S d;
    d.all = *(volatile U32 *)REG_ETH_FCR;
    d.bitc.pt = data;
    *(volatile U32 *)REG_ETH_FCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_FCR_PT] <-- 0x%08x\n",
                        REG_ETH_FCR,d.all,d.all);
    #endif
}
U16  GH_ETH_get_FCR_PT(void)
{
    GH_ETH_FCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_FCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_FCR_PT] --> 0x%08x\n",
                        REG_ETH_FCR,value);
    #endif
    return tmp_value.bitc.pt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_VTR (read/write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_VTR(U32 data)
{
    *(volatile U32 *)REG_ETH_VTR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_VTR] <-- 0x%08x\n",
                        REG_ETH_VTR,data,data);
    #endif
}
U32  GH_ETH_get_VTR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_VTR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_VTR] --> 0x%08x\n",
                        REG_ETH_VTR,value);
    #endif
    return value;
}
void GH_ETH_set_VTR_VL(U16 data)
{
    GH_ETH_VTR_S d;
    d.all = *(volatile U32 *)REG_ETH_VTR;
    d.bitc.vl = data;
    *(volatile U32 *)REG_ETH_VTR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_VTR_VL] <-- 0x%08x\n",
                        REG_ETH_VTR,d.all,d.all);
    #endif
}
U16  GH_ETH_get_VTR_VL(void)
{
    GH_ETH_VTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_VTR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_VTR_VL] --> 0x%08x\n",
                        REG_ETH_VTR,value);
    #endif
    return tmp_value.bitc.vl;
}
void GH_ETH_set_VTR_ETV(U8 data)
{
    GH_ETH_VTR_S d;
    d.all = *(volatile U32 *)REG_ETH_VTR;
    d.bitc.etv = data;
    *(volatile U32 *)REG_ETH_VTR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_VTR_ETV] <-- 0x%08x\n",
                        REG_ETH_VTR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_VTR_ETV(void)
{
    GH_ETH_VTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_VTR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_VTR_ETV] --> 0x%08x\n",
                        REG_ETH_VTR,value);
    #endif
    return tmp_value.bitc.etv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_MAR0H (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_MAR0H(U32 data)
{
    *(volatile U32 *)REG_ETH_MAR0H = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR0H] <-- 0x%08x\n",
                        REG_ETH_MAR0H,data,data);
    #endif
}
U32  GH_ETH_get_MAR0H(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_MAR0H);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR0H] --> 0x%08x\n",
                        REG_ETH_MAR0H,value);
    #endif
    return value;
}
void GH_ETH_set_MAR0H_A0(U16 data)
{
    GH_ETH_MAR0H_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR0H;
    d.bitc.a0 = data;
    *(volatile U32 *)REG_ETH_MAR0H = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR0H_A0] <-- 0x%08x\n",
                        REG_ETH_MAR0H,d.all,d.all);
    #endif
}
U16  GH_ETH_get_MAR0H_A0(void)
{
    GH_ETH_MAR0H_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR0H);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR0H_A0] --> 0x%08x\n",
                        REG_ETH_MAR0H,value);
    #endif
    return tmp_value.bitc.a0;
}
void GH_ETH_set_MAR0H_M0(U8 data)
{
    GH_ETH_MAR0H_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR0H;
    d.bitc.m0 = data;
    *(volatile U32 *)REG_ETH_MAR0H = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR0H_M0] <-- 0x%08x\n",
                        REG_ETH_MAR0H,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MAR0H_M0(void)
{
    GH_ETH_MAR0H_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR0H);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR0H_M0] --> 0x%08x\n",
                        REG_ETH_MAR0H,value);
    #endif
    return tmp_value.bitc.m0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_MAR0L (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_MAR0L(U32 data)
{
    *(volatile U32 *)REG_ETH_MAR0L = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR0L] <-- 0x%08x\n",
                        REG_ETH_MAR0L,data,data);
    #endif
}
U32  GH_ETH_get_MAR0L(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_MAR0L);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR0L] --> 0x%08x\n",
                        REG_ETH_MAR0L,value);
    #endif
    return value;
}
void GH_ETH_set_MAR0L_A0(U32 data)
{
    GH_ETH_MAR0L_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR0L;
    d.bitc.a0 = data;
    *(volatile U32 *)REG_ETH_MAR0L = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR0L_A0] <-- 0x%08x\n",
                        REG_ETH_MAR0L,d.all,d.all);
    #endif
}
U32  GH_ETH_get_MAR0L_A0(void)
{
    GH_ETH_MAR0L_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR0L);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR0L_A0] --> 0x%08x\n",
                        REG_ETH_MAR0L,value);
    #endif
    return tmp_value.bitc.a0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_MAR1H (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_MAR1H(U32 data)
{
    *(volatile U32 *)REG_ETH_MAR1H = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR1H] <-- 0x%08x\n",
                        REG_ETH_MAR1H,data,data);
    #endif
}
U32  GH_ETH_get_MAR1H(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_MAR1H);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR1H] --> 0x%08x\n",
                        REG_ETH_MAR1H,value);
    #endif
    return value;
}
void GH_ETH_set_MAR1H_A1(U16 data)
{
    GH_ETH_MAR1H_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR1H;
    d.bitc.a1 = data;
    *(volatile U32 *)REG_ETH_MAR1H = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR1H_A1] <-- 0x%08x\n",
                        REG_ETH_MAR1H,d.all,d.all);
    #endif
}
U16  GH_ETH_get_MAR1H_A1(void)
{
    GH_ETH_MAR1H_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR1H);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR1H_A1] --> 0x%08x\n",
                        REG_ETH_MAR1H,value);
    #endif
    return tmp_value.bitc.a1;
}
void GH_ETH_set_MAR1H_MBC(U8 data)
{
    GH_ETH_MAR1H_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR1H;
    d.bitc.mbc = data;
    *(volatile U32 *)REG_ETH_MAR1H = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR1H_MBC] <-- 0x%08x\n",
                        REG_ETH_MAR1H,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MAR1H_MBC(void)
{
    GH_ETH_MAR1H_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR1H);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR1H_MBC] --> 0x%08x\n",
                        REG_ETH_MAR1H,value);
    #endif
    return tmp_value.bitc.mbc;
}
void GH_ETH_set_MAR1H_SA(U8 data)
{
    GH_ETH_MAR1H_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR1H;
    d.bitc.sa = data;
    *(volatile U32 *)REG_ETH_MAR1H = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR1H_SA] <-- 0x%08x\n",
                        REG_ETH_MAR1H,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MAR1H_SA(void)
{
    GH_ETH_MAR1H_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR1H);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR1H_SA] --> 0x%08x\n",
                        REG_ETH_MAR1H,value);
    #endif
    return tmp_value.bitc.sa;
}
void GH_ETH_set_MAR1H_A1E(U8 data)
{
    GH_ETH_MAR1H_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR1H;
    d.bitc.a1e = data;
    *(volatile U32 *)REG_ETH_MAR1H = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR1H_A1E] <-- 0x%08x\n",
                        REG_ETH_MAR1H,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MAR1H_A1E(void)
{
    GH_ETH_MAR1H_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR1H);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR1H_A1E] --> 0x%08x\n",
                        REG_ETH_MAR1H,value);
    #endif
    return tmp_value.bitc.a1e;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_MAR1L (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_MAR1L(U32 data)
{
    *(volatile U32 *)REG_ETH_MAR1L = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR1L] <-- 0x%08x\n",
                        REG_ETH_MAR1L,data,data);
    #endif
}
U32  GH_ETH_get_MAR1L(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_MAR1L);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR1L] --> 0x%08x\n",
                        REG_ETH_MAR1L,value);
    #endif
    return value;
}
void GH_ETH_set_MAR1L_A1(U32 data)
{
    GH_ETH_MAR1L_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR1L;
    d.bitc.a1 = data;
    *(volatile U32 *)REG_ETH_MAR1L = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR1L_A1] <-- 0x%08x\n",
                        REG_ETH_MAR1L,d.all,d.all);
    #endif
}
U32  GH_ETH_get_MAR1L_A1(void)
{
    GH_ETH_MAR1L_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR1L);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR1L_A1] --> 0x%08x\n",
                        REG_ETH_MAR1L,value);
    #endif
    return tmp_value.bitc.a1;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_MAR2H (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_MAR2H(U32 data)
{
    *(volatile U32 *)REG_ETH_MAR2H = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR2H] <-- 0x%08x\n",
                        REG_ETH_MAR2H,data,data);
    #endif
}
U32  GH_ETH_get_MAR2H(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_MAR2H);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR2H] --> 0x%08x\n",
                        REG_ETH_MAR2H,value);
    #endif
    return value;
}
void GH_ETH_set_MAR2H_A2(U16 data)
{
    GH_ETH_MAR2H_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR2H;
    d.bitc.a2 = data;
    *(volatile U32 *)REG_ETH_MAR2H = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR2H_A2] <-- 0x%08x\n",
                        REG_ETH_MAR2H,d.all,d.all);
    #endif
}
U16  GH_ETH_get_MAR2H_A2(void)
{
    GH_ETH_MAR2H_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR2H);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR2H_A2] --> 0x%08x\n",
                        REG_ETH_MAR2H,value);
    #endif
    return tmp_value.bitc.a2;
}
void GH_ETH_set_MAR2H_MBC(U8 data)
{
    GH_ETH_MAR2H_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR2H;
    d.bitc.mbc = data;
    *(volatile U32 *)REG_ETH_MAR2H = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR2H_MBC] <-- 0x%08x\n",
                        REG_ETH_MAR2H,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MAR2H_MBC(void)
{
    GH_ETH_MAR2H_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR2H);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR2H_MBC] --> 0x%08x\n",
                        REG_ETH_MAR2H,value);
    #endif
    return tmp_value.bitc.mbc;
}
void GH_ETH_set_MAR2H_SA(U8 data)
{
    GH_ETH_MAR2H_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR2H;
    d.bitc.sa = data;
    *(volatile U32 *)REG_ETH_MAR2H = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR2H_SA] <-- 0x%08x\n",
                        REG_ETH_MAR2H,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MAR2H_SA(void)
{
    GH_ETH_MAR2H_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR2H);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR2H_SA] --> 0x%08x\n",
                        REG_ETH_MAR2H,value);
    #endif
    return tmp_value.bitc.sa;
}
void GH_ETH_set_MAR2H_A2E(U8 data)
{
    GH_ETH_MAR2H_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR2H;
    d.bitc.a2e = data;
    *(volatile U32 *)REG_ETH_MAR2H = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR2H_A2E] <-- 0x%08x\n",
                        REG_ETH_MAR2H,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MAR2H_A2E(void)
{
    GH_ETH_MAR2H_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR2H);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR2H_A2E] --> 0x%08x\n",
                        REG_ETH_MAR2H,value);
    #endif
    return tmp_value.bitc.a2e;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_MAR2L (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_MAR2L(U32 data)
{
    *(volatile U32 *)REG_ETH_MAR2L = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR2L] <-- 0x%08x\n",
                        REG_ETH_MAR2L,data,data);
    #endif
}
U32  GH_ETH_get_MAR2L(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_MAR2L);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR2L] --> 0x%08x\n",
                        REG_ETH_MAR2L,value);
    #endif
    return value;
}
void GH_ETH_set_MAR2L_A2(U32 data)
{
    GH_ETH_MAR2L_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR2L;
    d.bitc.a2 = data;
    *(volatile U32 *)REG_ETH_MAR2L = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MAR2L_A2] <-- 0x%08x\n",
                        REG_ETH_MAR2L,d.all,d.all);
    #endif
}
U32  GH_ETH_get_MAR2L_A2(void)
{
    GH_ETH_MAR2L_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR2L);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MAR2L_A2] --> 0x%08x\n",
                        REG_ETH_MAR2L,value);
    #endif
    return tmp_value.bitc.a2;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_VR (read)                                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_ETH_get_VR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_VR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_VR] --> 0x%08x\n",
                        REG_ETH_VR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_EPHY_DEBUG (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_EPHY_DEBUG(U32 data)
{
    *(volatile U32 *)REG_ETH_EPHY_DEBUG = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_EPHY_DEBUG] <-- 0x%08x\n",
                        REG_ETH_EPHY_DEBUG,data,data);
    #endif
}
U32  GH_ETH_get_EPHY_DEBUG(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_EPHY_DEBUG);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_EPHY_DEBUG] --> 0x%08x\n",
                        REG_ETH_EPHY_DEBUG,value);
    #endif
    return value;
}
void GH_ETH_set_EPHY_DEBUG_debug(U32 data)
{
    GH_ETH_EPHY_DEBUG_S d;
    d.all = *(volatile U32 *)REG_ETH_EPHY_DEBUG;
    d.bitc.debug = data;
    *(volatile U32 *)REG_ETH_EPHY_DEBUG = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_EPHY_DEBUG_debug] <-- 0x%08x\n",
                        REG_ETH_EPHY_DEBUG,d.all,d.all);
    #endif
}
U32  GH_ETH_get_EPHY_DEBUG_debug(void)
{
    GH_ETH_EPHY_DEBUG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_EPHY_DEBUG);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_EPHY_DEBUG_debug] --> 0x%08x\n",
                        REG_ETH_EPHY_DEBUG,value);
    #endif
    return tmp_value.bitc.debug;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_TPDR (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_TPDR(U32 data)
{
    *(volatile U32 *)REG_ETH_TPDR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_TPDR] <-- 0x%08x\n",
                        REG_ETH_TPDR,data,data);
    #endif
}
U32  GH_ETH_get_TPDR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_TPDR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_TPDR] --> 0x%08x\n",
                        REG_ETH_TPDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_RPDR (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_RPDR(U32 data)
{
    *(volatile U32 *)REG_ETH_RPDR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_RPDR] <-- 0x%08x\n",
                        REG_ETH_RPDR,data,data);
    #endif
}
U32  GH_ETH_get_RPDR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_RPDR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_RPDR] --> 0x%08x\n",
                        REG_ETH_RPDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_BMR (read/write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_BMR(U32 data)
{
    *(volatile U32 *)REG_ETH_BMR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_BMR] <-- 0x%08x\n",
                        REG_ETH_BMR,data,data);
    #endif
}
U32  GH_ETH_get_BMR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_BMR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_BMR] --> 0x%08x\n",
                        REG_ETH_BMR,value);
    #endif
    return value;
}
void GH_ETH_set_BMR_SWR(U8 data)
{
    GH_ETH_BMR_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR;
    d.bitc.swr = data;
    *(volatile U32 *)REG_ETH_BMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_BMR_SWR] <-- 0x%08x\n",
                        REG_ETH_BMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_BMR_SWR(void)
{
    GH_ETH_BMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_BMR_SWR] --> 0x%08x\n",
                        REG_ETH_BMR,value);
    #endif
    return tmp_value.bitc.swr;
}
void GH_ETH_set_BMR_DA(U8 data)
{
    GH_ETH_BMR_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR;
    d.bitc.da = data;
    *(volatile U32 *)REG_ETH_BMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_BMR_DA] <-- 0x%08x\n",
                        REG_ETH_BMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_BMR_DA(void)
{
    GH_ETH_BMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_BMR_DA] --> 0x%08x\n",
                        REG_ETH_BMR,value);
    #endif
    return tmp_value.bitc.da;
}
void GH_ETH_set_BMR_DSL(U8 data)
{
    GH_ETH_BMR_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR;
    d.bitc.dsl = data;
    *(volatile U32 *)REG_ETH_BMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_BMR_DSL] <-- 0x%08x\n",
                        REG_ETH_BMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_BMR_DSL(void)
{
    GH_ETH_BMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_BMR_DSL] --> 0x%08x\n",
                        REG_ETH_BMR,value);
    #endif
    return tmp_value.bitc.dsl;
}
void GH_ETH_set_BMR_PBL(U8 data)
{
    GH_ETH_BMR_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR;
    d.bitc.pbl = data;
    *(volatile U32 *)REG_ETH_BMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_BMR_PBL] <-- 0x%08x\n",
                        REG_ETH_BMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_BMR_PBL(void)
{
    GH_ETH_BMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_BMR_PBL] --> 0x%08x\n",
                        REG_ETH_BMR,value);
    #endif
    return tmp_value.bitc.pbl;
}
void GH_ETH_set_BMR_PR(U8 data)
{
    GH_ETH_BMR_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR;
    d.bitc.pr = data;
    *(volatile U32 *)REG_ETH_BMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_BMR_PR] <-- 0x%08x\n",
                        REG_ETH_BMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_BMR_PR(void)
{
    GH_ETH_BMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_BMR_PR] --> 0x%08x\n",
                        REG_ETH_BMR,value);
    #endif
    return tmp_value.bitc.pr;
}
void GH_ETH_set_BMR_FB(U8 data)
{
    GH_ETH_BMR_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR;
    d.bitc.fb = data;
    *(volatile U32 *)REG_ETH_BMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_BMR_FB] <-- 0x%08x\n",
                        REG_ETH_BMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_BMR_FB(void)
{
    GH_ETH_BMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_BMR_FB] --> 0x%08x\n",
                        REG_ETH_BMR,value);
    #endif
    return tmp_value.bitc.fb;
}
void GH_ETH_set_BMR_RPBL(U8 data)
{
    GH_ETH_BMR_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR;
    d.bitc.rpbl = data;
    *(volatile U32 *)REG_ETH_BMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_BMR_RPBL] <-- 0x%08x\n",
                        REG_ETH_BMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_BMR_RPBL(void)
{
    GH_ETH_BMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_BMR_RPBL] --> 0x%08x\n",
                        REG_ETH_BMR,value);
    #endif
    return tmp_value.bitc.rpbl;
}
void GH_ETH_set_BMR_USP(U8 data)
{
    GH_ETH_BMR_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR;
    d.bitc.usp = data;
    *(volatile U32 *)REG_ETH_BMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_BMR_USP] <-- 0x%08x\n",
                        REG_ETH_BMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_BMR_USP(void)
{
    GH_ETH_BMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_BMR_USP] --> 0x%08x\n",
                        REG_ETH_BMR,value);
    #endif
    return tmp_value.bitc.usp;
}
void GH_ETH_set_BMR_PBL4X(U8 data)
{
    GH_ETH_BMR_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR;
    d.bitc.pbl4x = data;
    *(volatile U32 *)REG_ETH_BMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_BMR_PBL4X] <-- 0x%08x\n",
                        REG_ETH_BMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_BMR_PBL4X(void)
{
    GH_ETH_BMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_BMR_PBL4X] --> 0x%08x\n",
                        REG_ETH_BMR,value);
    #endif
    return tmp_value.bitc.pbl4x;
}
void GH_ETH_set_BMR_AAL(U8 data)
{
    GH_ETH_BMR_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR;
    d.bitc.aal = data;
    *(volatile U32 *)REG_ETH_BMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_BMR_AAL] <-- 0x%08x\n",
                        REG_ETH_BMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_BMR_AAL(void)
{
    GH_ETH_BMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_BMR_AAL] --> 0x%08x\n",
                        REG_ETH_BMR,value);
    #endif
    return tmp_value.bitc.aal;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_RDLAR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_RDLAR(U32 data)
{
    *(volatile U32 *)REG_ETH_RDLAR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_RDLAR] <-- 0x%08x\n",
                        REG_ETH_RDLAR,data,data);
    #endif
}
U32  GH_ETH_get_RDLAR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_RDLAR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_RDLAR] --> 0x%08x\n",
                        REG_ETH_RDLAR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_TDLAR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_TDLAR(U32 data)
{
    *(volatile U32 *)REG_ETH_TDLAR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_TDLAR] <-- 0x%08x\n",
                        REG_ETH_TDLAR,data,data);
    #endif
}
U32  GH_ETH_get_TDLAR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_TDLAR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_TDLAR] --> 0x%08x\n",
                        REG_ETH_TDLAR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_SR (read/write)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_SR(U32 data)
{
    *(volatile U32 *)REG_ETH_SR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR] <-- 0x%08x\n",
                        REG_ETH_SR,data,data);
    #endif
}
U32  GH_ETH_get_SR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return value;
}
void GH_ETH_set_SR_TI(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.ti = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_TI] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_TI(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_TI] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.ti;
}
void GH_ETH_set_SR_TPS(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.tps = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_TPS] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_TPS(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_TPS] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.tps;
}
void GH_ETH_set_SR_TU(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.tu = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_TU] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_TU(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_TU] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.tu;
}
void GH_ETH_set_SR_TJT(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.tjt = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_TJT] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_TJT(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_TJT] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.tjt;
}
void GH_ETH_set_SR_OVF(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.ovf = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_OVF] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_OVF(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_OVF] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.ovf;
}
void GH_ETH_set_SR_UNF(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.unf = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_UNF] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_UNF(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_UNF] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.unf;
}
void GH_ETH_set_SR_RI(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.ri = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_RI] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_RI(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_RI] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.ri;
}
void GH_ETH_set_SR_RU(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.ru = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_RU] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_RU(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_RU] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.ru;
}
void GH_ETH_set_SR_RPS(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.rps = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_RPS] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_RPS(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_RPS] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.rps;
}
void GH_ETH_set_SR_RWT(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.rwt = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_RWT] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_RWT(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_RWT] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.rwt;
}
void GH_ETH_set_SR_ETI(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.eti = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_ETI] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_ETI(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_ETI] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.eti;
}
void GH_ETH_set_SR_FBE(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.fbe = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_FBE] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_FBE(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_FBE] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.fbe;
}
void GH_ETH_set_SR_ERI(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.eri = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_ERI] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_ERI(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_ERI] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.eri;
}
void GH_ETH_set_SR_AIS(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.ais = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_AIS] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_AIS(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_AIS] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.ais;
}
void GH_ETH_set_SR_NIS(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.nis = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_NIS] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_NIS(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_NIS] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.nis;
}
void GH_ETH_set_SR_RS(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.rs = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_RS] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_RS(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_RS] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.rs;
}
void GH_ETH_set_SR_TS(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.ts = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_TS] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_TS(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_TS] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.ts;
}
void GH_ETH_set_SR_EB(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.eb = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_EB] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_EB(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_EB] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.eb;
}
void GH_ETH_set_SR_GLI(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.gli = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_GLI] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_GLI(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_GLI] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.gli;
}
void GH_ETH_set_SR_GMI(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.gmi = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_GMI] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_GMI(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_GMI] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.gmi;
}
void GH_ETH_set_SR_GPI(U8 data)
{
    GH_ETH_SR_S d;
    d.all = *(volatile U32 *)REG_ETH_SR;
    d.bitc.gpi = data;
    *(volatile U32 *)REG_ETH_SR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_SR_GPI] <-- 0x%08x\n",
                        REG_ETH_SR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_SR_GPI(void)
{
    GH_ETH_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_SR_GPI] --> 0x%08x\n",
                        REG_ETH_SR,value);
    #endif
    return tmp_value.bitc.gpi;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_MFBOCR (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_MFBOCR(U32 data)
{
    *(volatile U32 *)REG_ETH_MFBOCR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFBOCR] <-- 0x%08x\n",
                        REG_ETH_MFBOCR,data,data);
    #endif
}
U32  GH_ETH_get_MFBOCR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_MFBOCR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFBOCR] --> 0x%08x\n",
                        REG_ETH_MFBOCR,value);
    #endif
    return value;
}
void GH_ETH_set_MFBOCR_NMFH(U16 data)
{
    GH_ETH_MFBOCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFBOCR;
    d.bitc.nmfh = data;
    *(volatile U32 *)REG_ETH_MFBOCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFBOCR_NMFH] <-- 0x%08x\n",
                        REG_ETH_MFBOCR,d.all,d.all);
    #endif
}
U16  GH_ETH_get_MFBOCR_NMFH(void)
{
    GH_ETH_MFBOCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFBOCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFBOCR_NMFH] --> 0x%08x\n",
                        REG_ETH_MFBOCR,value);
    #endif
    return tmp_value.bitc.nmfh;
}
void GH_ETH_set_MFBOCR_OVMFC(U8 data)
{
    GH_ETH_MFBOCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFBOCR;
    d.bitc.ovmfc = data;
    *(volatile U32 *)REG_ETH_MFBOCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFBOCR_OVMFC] <-- 0x%08x\n",
                        REG_ETH_MFBOCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFBOCR_OVMFC(void)
{
    GH_ETH_MFBOCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFBOCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFBOCR_OVMFC] --> 0x%08x\n",
                        REG_ETH_MFBOCR,value);
    #endif
    return tmp_value.bitc.ovmfc;
}
void GH_ETH_set_MFBOCR_NMFF(U16 data)
{
    GH_ETH_MFBOCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFBOCR;
    d.bitc.nmff = data;
    *(volatile U32 *)REG_ETH_MFBOCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFBOCR_NMFF] <-- 0x%08x\n",
                        REG_ETH_MFBOCR,d.all,d.all);
    #endif
}
U16  GH_ETH_get_MFBOCR_NMFF(void)
{
    GH_ETH_MFBOCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFBOCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFBOCR_NMFF] --> 0x%08x\n",
                        REG_ETH_MFBOCR,value);
    #endif
    return tmp_value.bitc.nmff;
}
void GH_ETH_set_MFBOCR_ONMFF(U8 data)
{
    GH_ETH_MFBOCR_S d;
    d.all = *(volatile U32 *)REG_ETH_MFBOCR;
    d.bitc.onmff = data;
    *(volatile U32 *)REG_ETH_MFBOCR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_MFBOCR_ONMFF] <-- 0x%08x\n",
                        REG_ETH_MFBOCR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_MFBOCR_ONMFF(void)
{
    GH_ETH_MFBOCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFBOCR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_MFBOCR_ONMFF] --> 0x%08x\n",
                        REG_ETH_MFBOCR,value);
    #endif
    return tmp_value.bitc.onmff;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_IER (read/write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_IER(U32 data)
{
    *(volatile U32 *)REG_ETH_IER = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER] <-- 0x%08x\n",
                        REG_ETH_IER,data,data);
    #endif
}
U32  GH_ETH_get_IER(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return value;
}
void GH_ETH_set_IER_TI(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.ti = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_TI] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_TI(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_TI] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.ti;
}
void GH_ETH_set_IER_TS(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.ts = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_TS] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_TS(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_TS] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.ts;
}
void GH_ETH_set_IER_TU(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.tu = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_TU] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_TU(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_TU] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.tu;
}
void GH_ETH_set_IER_TJ(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.tj = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_TJ] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_TJ(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_TJ] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.tj;
}
void GH_ETH_set_IER_OV(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.ov = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_OV] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_OV(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_OV] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.ov;
}
void GH_ETH_set_IER_UN(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.un = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_UN] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_UN(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_UN] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.un;
}
void GH_ETH_set_IER_RI(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.ri = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_RI] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_RI(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_RI] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.ri;
}
void GH_ETH_set_IER_RU(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.ru = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_RU] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_RU(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_RU] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.ru;
}
void GH_ETH_set_IER_RS(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.rs = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_RS] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_RS(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_RS] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.rs;
}
void GH_ETH_set_IER_RW(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.rw = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_RW] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_RW(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_RW] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.rw;
}
void GH_ETH_set_IER_ETE(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.ete = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_ETE] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_ETE(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_ETE] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.ete;
}
void GH_ETH_set_IER_FBE(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.fbe = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_FBE] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_FBE(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_FBE] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.fbe;
}
void GH_ETH_set_IER_ERE(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.ere = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_ERE] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_ERE(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_ERE] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.ere;
}
void GH_ETH_set_IER_AI(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.ai = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_AI] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_AI(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_AI] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.ai;
}
void GH_ETH_set_IER_NI(U8 data)
{
    GH_ETH_IER_S d;
    d.all = *(volatile U32 *)REG_ETH_IER;
    d.bitc.ni = data;
    *(volatile U32 *)REG_ETH_IER = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_IER_NI] <-- 0x%08x\n",
                        REG_ETH_IER,d.all,d.all);
    #endif
}
U8   GH_ETH_get_IER_NI(void)
{
    GH_ETH_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_IER_NI] --> 0x%08x\n",
                        REG_ETH_IER,value);
    #endif
    return tmp_value.bitc.ni;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_OMR (read/write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_OMR(U32 data)
{
    *(volatile U32 *)REG_ETH_OMR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR] <-- 0x%08x\n",
                        REG_ETH_OMR,data,data);
    #endif
}
U32  GH_ETH_get_OMR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return value;
}
void GH_ETH_set_OMR_SR(U8 data)
{
    GH_ETH_OMR_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR;
    d.bitc.sr = data;
    *(volatile U32 *)REG_ETH_OMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR_SR] <-- 0x%08x\n",
                        REG_ETH_OMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_OMR_SR(void)
{
    GH_ETH_OMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR_SR] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return tmp_value.bitc.sr;
}
void GH_ETH_set_OMR_OSF(U8 data)
{
    GH_ETH_OMR_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR;
    d.bitc.osf = data;
    *(volatile U32 *)REG_ETH_OMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR_OSF] <-- 0x%08x\n",
                        REG_ETH_OMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_OMR_OSF(void)
{
    GH_ETH_OMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR_OSF] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return tmp_value.bitc.osf;
}
void GH_ETH_set_OMR_RTC(U8 data)
{
    GH_ETH_OMR_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR;
    d.bitc.rtc = data;
    *(volatile U32 *)REG_ETH_OMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR_RTC] <-- 0x%08x\n",
                        REG_ETH_OMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_OMR_RTC(void)
{
    GH_ETH_OMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR_RTC] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return tmp_value.bitc.rtc;
}
void GH_ETH_set_OMR_FUF(U8 data)
{
    GH_ETH_OMR_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR;
    d.bitc.fuf = data;
    *(volatile U32 *)REG_ETH_OMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR_FUF] <-- 0x%08x\n",
                        REG_ETH_OMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_OMR_FUF(void)
{
    GH_ETH_OMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR_FUF] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return tmp_value.bitc.fuf;
}
void GH_ETH_set_OMR_FEF(U8 data)
{
    GH_ETH_OMR_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR;
    d.bitc.fef = data;
    *(volatile U32 *)REG_ETH_OMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR_FEF] <-- 0x%08x\n",
                        REG_ETH_OMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_OMR_FEF(void)
{
    GH_ETH_OMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR_FEF] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return tmp_value.bitc.fef;
}
void GH_ETH_set_OMR_EFC(U8 data)
{
    GH_ETH_OMR_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR;
    d.bitc.efc = data;
    *(volatile U32 *)REG_ETH_OMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR_EFC] <-- 0x%08x\n",
                        REG_ETH_OMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_OMR_EFC(void)
{
    GH_ETH_OMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR_EFC] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return tmp_value.bitc.efc;
}
void GH_ETH_set_OMR_RFA(U8 data)
{
    GH_ETH_OMR_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR;
    d.bitc.rfa = data;
    *(volatile U32 *)REG_ETH_OMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR_RFA] <-- 0x%08x\n",
                        REG_ETH_OMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_OMR_RFA(void)
{
    GH_ETH_OMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR_RFA] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return tmp_value.bitc.rfa;
}
void GH_ETH_set_OMR_RFD(U8 data)
{
    GH_ETH_OMR_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR;
    d.bitc.rfd = data;
    *(volatile U32 *)REG_ETH_OMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR_RFD] <-- 0x%08x\n",
                        REG_ETH_OMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_OMR_RFD(void)
{
    GH_ETH_OMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR_RFD] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return tmp_value.bitc.rfd;
}
void GH_ETH_set_OMR_ST(U8 data)
{
    GH_ETH_OMR_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR;
    d.bitc.st = data;
    *(volatile U32 *)REG_ETH_OMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR_ST] <-- 0x%08x\n",
                        REG_ETH_OMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_OMR_ST(void)
{
    GH_ETH_OMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR_ST] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return tmp_value.bitc.st;
}
void GH_ETH_set_OMR_TTC(U8 data)
{
    GH_ETH_OMR_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR;
    d.bitc.ttc = data;
    *(volatile U32 *)REG_ETH_OMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR_TTC] <-- 0x%08x\n",
                        REG_ETH_OMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_OMR_TTC(void)
{
    GH_ETH_OMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR_TTC] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return tmp_value.bitc.ttc;
}
void GH_ETH_set_OMR_FTF(U8 data)
{
    GH_ETH_OMR_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR;
    d.bitc.ftf = data;
    *(volatile U32 *)REG_ETH_OMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR_FTF] <-- 0x%08x\n",
                        REG_ETH_OMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_OMR_FTF(void)
{
    GH_ETH_OMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR_FTF] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return tmp_value.bitc.ftf;
}
void GH_ETH_set_OMR_SF(U8 data)
{
    GH_ETH_OMR_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR;
    d.bitc.sf = data;
    *(volatile U32 *)REG_ETH_OMR = d.all;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_OMR_SF] <-- 0x%08x\n",
                        REG_ETH_OMR,d.all,d.all);
    #endif
}
U8   GH_ETH_get_OMR_SF(void)
{
    GH_ETH_OMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR);

    tmp_value.all = value;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_OMR_SF] --> 0x%08x\n",
                        REG_ETH_OMR,value);
    #endif
    return tmp_value.bitc.sf;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_CHTBAR (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_CHTBAR(U32 data)
{
    *(volatile U32 *)REG_ETH_CHTBAR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_CHTBAR] <-- 0x%08x\n",
                        REG_ETH_CHTBAR,data,data);
    #endif
}
U32  GH_ETH_get_CHTBAR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_CHTBAR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_CHTBAR] --> 0x%08x\n",
                        REG_ETH_CHTBAR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_CHRBAR (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_CHRBAR(U32 data)
{
    *(volatile U32 *)REG_ETH_CHRBAR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_CHRBAR] <-- 0x%08x\n",
                        REG_ETH_CHRBAR,data,data);
    #endif
}
U32  GH_ETH_get_CHRBAR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_CHRBAR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_CHRBAR] --> 0x%08x\n",
                        REG_ETH_CHRBAR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_CHTDR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_CHTDR(U32 data)
{
    *(volatile U32 *)REG_ETH_CHTDR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_CHTDR] <-- 0x%08x\n",
                        REG_ETH_CHTDR,data,data);
    #endif
}
U32  GH_ETH_get_CHTDR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_CHTDR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_CHTDR] --> 0x%08x\n",
                        REG_ETH_CHTDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ETH_CHRDR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ETH_set_CHRDR(U32 data)
{
    *(volatile U32 *)REG_ETH_CHRDR = data;
    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ETH_set_CHRDR] <-- 0x%08x\n",
                        REG_ETH_CHRDR,data,data);
    #endif
}
U32  GH_ETH_get_CHRDR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_CHRDR);

    #if GH_ETH_ENABLE_DEBUG_PRINT
    GH_ETH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ETH_get_CHRDR] --> 0x%08x\n",
                        REG_ETH_CHRDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_ETH_init(void)
{
    GH_ETH_set_MCR((U32)0x00000000);
    GH_ETH_set_GAR((U32)0x00000000);
    GH_ETH_set_GDR((U32)0x00000000);
    GH_ETH_set_MFFR((U32)0x00000000);
    GH_ETH_set_MHTRH((U32)0x00000000);
    GH_ETH_set_MHTRL((U32)0x00000000);
    GH_ETH_set_FCR((U32)0x00000000);
    GH_ETH_set_VTR((U32)0x00000000);
    GH_ETH_set_MAR0H((U32)0x00000000);
    GH_ETH_set_MAR0L((U32)0x00000000);
    GH_ETH_set_MAR1H((U32)0x00000000);
    GH_ETH_set_MAR1L((U32)0x00000000);
    GH_ETH_set_MAR2H((U32)0x00000000);
    GH_ETH_set_MAR2L((U32)0x00000000);
    GH_ETH_set_EPHY_DEBUG((U32)0x00000000);
    GH_ETH_set_BMR((U32)0x00010000);
    GH_ETH_set_SR((U32)0x00000000);
    GH_ETH_set_MFBOCR((U32)0x00000000);
    GH_ETH_set_IER((U32)0x00000000);
    GH_ETH_set_OMR((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

