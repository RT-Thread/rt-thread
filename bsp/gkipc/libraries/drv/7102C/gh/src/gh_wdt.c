/******************************************************************************
**
** \file      gh_wdt.c
**
** \brief     Watch Dog Timer.
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
#include "gh_wdt.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_WDT_CLRR_S                           m_wdt_clrr;
U32                                     m_wdt_restartr;

/*----------------------------------------------------------------------------*/
/* register WDT_CtrlR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_WDT_set_CtrlR(U32 data)
{
    *(volatile U32 *)REG_WDT_CTRLR = data;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_CtrlR] <-- 0x%08x\n",
                        REG_WDT_CTRLR,data,data);
    #endif
}
U32  GH_WDT_get_CtrlR(void)
{
    U32 value = (*(volatile U32 *)REG_WDT_CTRLR);

    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_CtrlR] --> 0x%08x\n",
                        REG_WDT_CTRLR,value);
    #endif
    return value;
}
void GH_WDT_set_CtrlR_Enable(U8 data)
{
    GH_WDT_CTRLR_S d;
    d.all = *(volatile U32 *)REG_WDT_CTRLR;
    d.bitc.enable = data;
    *(volatile U32 *)REG_WDT_CTRLR = d.all;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_CtrlR_Enable] <-- 0x%08x\n",
                        REG_WDT_CTRLR,d.all,d.all);
    #endif
}
U8   GH_WDT_get_CtrlR_Enable(void)
{
    GH_WDT_CTRLR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_WDT_CTRLR);

    tmp_value.all = value;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_CtrlR_Enable] --> 0x%08x\n",
                        REG_WDT_CTRLR,value);
    #endif
    return tmp_value.bitc.enable;
}
void GH_WDT_set_CtrlR_IntEnable(U8 data)
{
    GH_WDT_CTRLR_S d;
    d.all = *(volatile U32 *)REG_WDT_CTRLR;
    d.bitc.intenable = data;
    *(volatile U32 *)REG_WDT_CTRLR = d.all;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_CtrlR_IntEnable] <-- 0x%08x\n",
                        REG_WDT_CTRLR,d.all,d.all);
    #endif
}
U8   GH_WDT_get_CtrlR_IntEnable(void)
{
    GH_WDT_CTRLR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_WDT_CTRLR);

    tmp_value.all = value;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_CtrlR_IntEnable] --> 0x%08x\n",
                        REG_WDT_CTRLR,value);
    #endif
    return tmp_value.bitc.intenable;
}
void GH_WDT_set_CtrlR_ResetEnable(U8 data)
{
    GH_WDT_CTRLR_S d;
    d.all = *(volatile U32 *)REG_WDT_CTRLR;
    d.bitc.resetenable = data;
    *(volatile U32 *)REG_WDT_CTRLR = d.all;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_CtrlR_ResetEnable] <-- 0x%08x\n",
                        REG_WDT_CTRLR,d.all,d.all);
    #endif
}
U8   GH_WDT_get_CtrlR_ResetEnable(void)
{
    GH_WDT_CTRLR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_WDT_CTRLR);

    tmp_value.all = value;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_CtrlR_ResetEnable] --> 0x%08x\n",
                        REG_WDT_CTRLR,value);
    #endif
    return tmp_value.bitc.resetenable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register WDT_TimeoutR (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_WDT_get_TimeoutR(void)
{
    U32 value = (*(volatile U32 *)REG_WDT_TIMEOUTR);

    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_TimeoutR] --> 0x%08x\n",
                        REG_WDT_TIMEOUTR,value);
    #endif
    return value;
}
U8   GH_WDT_get_TimeoutR_Timeout(void)
{
    GH_WDT_TIMEOUTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_WDT_TIMEOUTR);

    tmp_value.all = value;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_TimeoutR_Timeout] --> 0x%08x\n",
                        REG_WDT_TIMEOUTR,value);
    #endif
    return tmp_value.bitc.timeout;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register WDT_ClrR (write)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_WDT_set_ClrR(U32 data)
{
    m_wdt_clrr.all = data;
    *(volatile U32 *)REG_WDT_CLRR = data;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_ClrR] <-- 0x%08x\n",
                        REG_WDT_CLRR,data,data);
    #endif
}
U32  GH_WDT_getm_ClrR(void)
{
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "[GH_WDT_getm_ClrR] --> 0x%08x\n",
                        m_wdt_clrr.all);
    #endif
    return m_wdt_clrr.all;
}
void GH_WDT_set_ClrR_Clr(U8 data)
{
    m_wdt_clrr.bitc.clr = data;
    *(volatile U32 *)REG_WDT_CLRR = m_wdt_clrr.all;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_ClrR_Clr] <-- 0x%08x\n",
                        REG_WDT_CLRR,m_wdt_clrr.all,m_wdt_clrr.all);
    #endif
}
U8   GH_WDT_getm_ClrR_Clr(void)
{
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "[GH_WDT_getm_ClrR_Clr] --> 0x%08x\n",
                        m_wdt_clrr.bitc.clr);
    #endif
    return m_wdt_clrr.bitc.clr;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register WDT_CntStsR (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_WDT_get_CntStsR(void)
{
    U32 value = (*(volatile U32 *)REG_WDT_CNTSTSR);

    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_CntStsR] --> 0x%08x\n",
                        REG_WDT_CNTSTSR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register WDT_ReloadR (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_WDT_set_ReloadR(U32 data)
{
    *(volatile U32 *)REG_WDT_RELOADR = data;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_ReloadR] <-- 0x%08x\n",
                        REG_WDT_RELOADR,data,data);
    #endif
}
U32  GH_WDT_get_ReloadR(void)
{
    U32 value = (*(volatile U32 *)REG_WDT_RELOADR);

    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_ReloadR] --> 0x%08x\n",
                        REG_WDT_RELOADR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register WDT_RestartR (write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_WDT_set_RestartR(U32 data)
{
    m_wdt_restartr = data;
    *(volatile U32 *)REG_WDT_RESTARTR = data;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_RestartR] <-- 0x%08x\n",
                        REG_WDT_RESTARTR,data,data);
    #endif
}
U32  GH_WDT_getm_RestartR(void)
{
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "[GH_WDT_getm_RestartR] --> 0x%08x\n",
                        m_wdt_restartr);
    #endif
    return m_wdt_restartr;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register WDT_RstWdR (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_WDT_set_RstWdR(U32 data)
{
    *(volatile U32 *)REG_WDT_RSTWDR = data;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_RstWdR] <-- 0x%08x\n",
                        REG_WDT_RSTWDR,data,data);
    #endif
}
U32  GH_WDT_get_RstWdR(void)
{
    U32 value = (*(volatile U32 *)REG_WDT_RSTWDR);

    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_RstWdR] --> 0x%08x\n",
                        REG_WDT_RSTWDR,value);
    #endif
    return value;
}
void GH_WDT_set_RstWdR_RstWd(U8 data)
{
    GH_WDT_RSTWDR_S d;
    d.all = *(volatile U32 *)REG_WDT_RSTWDR;
    d.bitc.rstwd = data;
    *(volatile U32 *)REG_WDT_RSTWDR = d.all;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_RstWdR_RstWd] <-- 0x%08x\n",
                        REG_WDT_RSTWDR,d.all,d.all);
    #endif
}
U8   GH_WDT_get_RstWdR_RstWd(void)
{
    GH_WDT_RSTWDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_WDT_RSTWDR);

    tmp_value.all = value;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_RstWdR_RstWd] --> 0x%08x\n",
                        REG_WDT_RSTWDR,value);
    #endif
    return tmp_value.bitc.rstwd;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_WDT_init(void)
{
    GH_WDT_set_CtrlR((U32)0x00000000);
    GH_WDT_set_ClrR((U32)0x00000000);
    GH_WDT_set_ReloadR((U32)0x03ef1480);
    GH_WDT_set_RestartR((U32)0x00000000);
    GH_WDT_set_RstWdR((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

