/*!
*******************************************************************************
**
** \file      gh_wdt.h
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
#ifndef _GH_WDT_H
#define _GH_WDT_H

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
#include "gtypes.h" /* global type definitions */
#include "gh_lib_cfg.h" /* configuration */
#endif

#define GH_WDT_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_WDT_DEBUG_PRINT_FUNCTION printk
#else
#define GH_WDT_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_WDT_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/* check configuration */
#ifndef GH_INLINE_LEVEL
  #error "GH_INLINE_LEVEL is not defined!"
#endif
#if GH_INLINE_LEVEL > 2
  #error "GH_INLINE_LEVEL must be set 0, 1 or 2!"
#endif
#ifndef GH_INLINE
  #error "GH_INLINE is not defined!"
#endif

/* disable inlining for debugging */
#ifdef DEBUG
  #undef GH_INLINE_LEVEL
  #define GH_INLINE_LEVEL 0
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_WDT_CTRLR                                       FIO_ADDRESS(WDT,0xA0006000) /* read/write */
#define REG_WDT_TIMEOUTR                                    FIO_ADDRESS(WDT,0xA0006004) /* read */
#define REG_WDT_CLRR                                        FIO_ADDRESS(WDT,0xA0006008) /* write */
#define REG_WDT_CNTSTSR                                     FIO_ADDRESS(WDT,0xA000600C) /* read */
#define REG_WDT_RELOADR                                     FIO_ADDRESS(WDT,0xA0006010) /* read/write */
#define REG_WDT_RESTARTR                                    FIO_ADDRESS(WDT,0xA0006014) /* write */
#define REG_WDT_RSTWDR                                      FIO_ADDRESS(WDT,0xA0006018) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* WDT_CtrlR */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32 intenable                   : 1;
        U32 resetenable                 : 1;
        U32                             : 29;
    } bitc;
} GH_WDT_CTRLR_S;

typedef union { /* WDT_TimeoutR */
    U32 all;
    struct {
        U32 timeout                     : 1;
        U32                             : 31;
    } bitc;
} GH_WDT_TIMEOUTR_S;

typedef union { /* WDT_ClrR */
    U32 all;
    struct {
        U32 clr                         : 1;
        U32                             : 31;
    } bitc;
} GH_WDT_CLRR_S;

typedef union { /* WDT_RstWdR */
    U32 all;
    struct {
        U32 rstwd                       : 8;
        U32                             : 24;
    } bitc;
} GH_WDT_RSTWDR_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_WDT_CLRR_S                           m_wdt_clrr;
extern U32                                     m_wdt_restartr;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register WDT_CtrlR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'WDT_CtrlR'. */
void GH_WDT_set_CtrlR(U32 data);
/*! \brief Reads the register 'WDT_CtrlR'. */
U32  GH_WDT_get_CtrlR(void);
/*! \brief Writes the bit group 'Enable' of register 'WDT_CtrlR'. */
void GH_WDT_set_CtrlR_Enable(U8 data);
/*! \brief Reads the bit group 'Enable' of register 'WDT_CtrlR'. */
U8   GH_WDT_get_CtrlR_Enable(void);
/*! \brief Writes the bit group 'IntEnable' of register 'WDT_CtrlR'. */
void GH_WDT_set_CtrlR_IntEnable(U8 data);
/*! \brief Reads the bit group 'IntEnable' of register 'WDT_CtrlR'. */
U8   GH_WDT_get_CtrlR_IntEnable(void);
/*! \brief Writes the bit group 'ResetEnable' of register 'WDT_CtrlR'. */
void GH_WDT_set_CtrlR_ResetEnable(U8 data);
/*! \brief Reads the bit group 'ResetEnable' of register 'WDT_CtrlR'. */
U8   GH_WDT_get_CtrlR_ResetEnable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_WDT_set_CtrlR(U32 data)
{
    *(volatile U32 *)REG_WDT_CTRLR = data;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_CtrlR] <-- 0x%08x\n",
                        REG_WDT_CTRLR,data,data);
    #endif
}
GH_INLINE U32  GH_WDT_get_CtrlR(void)
{
    U32 value = (*(volatile U32 *)REG_WDT_CTRLR);

    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_CtrlR] --> 0x%08x\n",
                        REG_WDT_CTRLR,value);
    #endif
    return value;
}
GH_INLINE void GH_WDT_set_CtrlR_Enable(U8 data)
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
GH_INLINE U8   GH_WDT_get_CtrlR_Enable(void)
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
GH_INLINE void GH_WDT_set_CtrlR_IntEnable(U8 data)
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
GH_INLINE U8   GH_WDT_get_CtrlR_IntEnable(void)
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
GH_INLINE void GH_WDT_set_CtrlR_ResetEnable(U8 data)
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
GH_INLINE U8   GH_WDT_get_CtrlR_ResetEnable(void)
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
/*! \brief Reads the register 'WDT_TimeoutR'. */
U32  GH_WDT_get_TimeoutR(void);
/*! \brief Reads the bit group 'Timeout' of register 'WDT_TimeoutR'. */
U8   GH_WDT_get_TimeoutR_Timeout(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_WDT_get_TimeoutR(void)
{
    U32 value = (*(volatile U32 *)REG_WDT_TIMEOUTR);

    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_TimeoutR] --> 0x%08x\n",
                        REG_WDT_TIMEOUTR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_WDT_get_TimeoutR_Timeout(void)
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
/*! \brief Writes the register 'WDT_ClrR'. */
void GH_WDT_set_ClrR(U32 data);
/*! \brief Reads the mirror variable of the register 'WDT_ClrR'. */
U32  GH_WDT_getm_ClrR(void);
/*! \brief Writes the bit group 'Clr' of register 'WDT_ClrR'. */
void GH_WDT_set_ClrR_Clr(U8 data);
/*! \brief Reads the bit group 'Clr' from the mirror variable of register 'WDT_ClrR'. */
U8   GH_WDT_getm_ClrR_Clr(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_WDT_set_ClrR(U32 data)
{
    m_wdt_clrr.all = data;
    *(volatile U32 *)REG_WDT_CLRR = data;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_ClrR] <-- 0x%08x\n",
                        REG_WDT_CLRR,data,data);
    #endif
}
GH_INLINE U32  GH_WDT_getm_ClrR(void)
{
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "[GH_WDT_getm_ClrR] --> 0x%08x\n",
                        m_wdt_clrr.all);
    #endif
    return m_wdt_clrr.all;
}
GH_INLINE void GH_WDT_set_ClrR_Clr(U8 data)
{
    m_wdt_clrr.bitc.clr = data;
    *(volatile U32 *)REG_WDT_CLRR = m_wdt_clrr.all;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_ClrR_Clr] <-- 0x%08x\n",
                        REG_WDT_CLRR,m_wdt_clrr.all,m_wdt_clrr.all);
    #endif
}
GH_INLINE U8   GH_WDT_getm_ClrR_Clr(void)
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
/*! \brief Reads the register 'WDT_CntStsR'. */
U32  GH_WDT_get_CntStsR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_WDT_get_CntStsR(void)
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
/*! \brief Writes the register 'WDT_ReloadR'. */
void GH_WDT_set_ReloadR(U32 data);
/*! \brief Reads the register 'WDT_ReloadR'. */
U32  GH_WDT_get_ReloadR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_WDT_set_ReloadR(U32 data)
{
    *(volatile U32 *)REG_WDT_RELOADR = data;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_ReloadR] <-- 0x%08x\n",
                        REG_WDT_RELOADR,data,data);
    #endif
}
GH_INLINE U32  GH_WDT_get_ReloadR(void)
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
/*! \brief Writes the register 'WDT_RestartR'. */
void GH_WDT_set_RestartR(U32 data);
/*! \brief Reads the mirror variable of the register 'WDT_RestartR'. */
U32  GH_WDT_getm_RestartR(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_WDT_set_RestartR(U32 data)
{
    m_wdt_restartr = data;
    *(volatile U32 *)REG_WDT_RESTARTR = data;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_RestartR] <-- 0x%08x\n",
                        REG_WDT_RESTARTR,data,data);
    #endif
}
GH_INLINE U32  GH_WDT_getm_RestartR(void)
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
/*! \brief Writes the register 'WDT_RstWdR'. */
void GH_WDT_set_RstWdR(U32 data);
/*! \brief Reads the register 'WDT_RstWdR'. */
U32  GH_WDT_get_RstWdR(void);
/*! \brief Writes the bit group 'RstWd' of register 'WDT_RstWdR'. */
void GH_WDT_set_RstWdR_RstWd(U8 data);
/*! \brief Reads the bit group 'RstWd' of register 'WDT_RstWdR'. */
U8   GH_WDT_get_RstWdR_RstWd(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_WDT_set_RstWdR(U32 data)
{
    *(volatile U32 *)REG_WDT_RSTWDR = data;
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_WDT_set_RstWdR] <-- 0x%08x\n",
                        REG_WDT_RSTWDR,data,data);
    #endif
}
GH_INLINE U32  GH_WDT_get_RstWdR(void)
{
    U32 value = (*(volatile U32 *)REG_WDT_RSTWDR);

    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_WDT_get_RstWdR] --> 0x%08x\n",
                        REG_WDT_RSTWDR,value);
    #endif
    return value;
}
GH_INLINE void GH_WDT_set_RstWdR_RstWd(U8 data)
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
GH_INLINE U8   GH_WDT_get_RstWdR_RstWd(void)
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
/*! \brief Initialises the registers and mirror variables. */
void GH_WDT_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_WDT_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

