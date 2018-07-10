/******************************************************************************
**
** \file      gh_wdt.c
**
** \brief     Watch Dog Timer.
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
#ifndef SRC_INLINE
#include "gh_wdt.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_WDT_CNTSTSR_REAL                                FIO_ADDRESS(WDT,0x7000C000) /* read */
#define REG_WDT_RELOADR_REAL                                FIO_ADDRESS(WDT,0x7000C004) /* read/write */
#define REG_WDT_RESTARTR_REAL                               FIO_ADDRESS(WDT,0x7000C008) /* write */
#define REG_WDT_CTRLR_REAL                                  FIO_ADDRESS(WDT,0x7000C00C) /* read/write */
#define REG_WDT_TIMEOUTR_REAL                               FIO_ADDRESS(WDT,0x7000C010) /* read */
#define REG_WDT_CLRR_REAL                                   FIO_ADDRESS(WDT,0x7000C014) /* write */
#define REG_WDT_RSTWDR_REAL                                 FIO_ADDRESS(WDT,0x7000C018) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* WDT_CtrlR */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32 resetenable                 : 1;
        U32 intenable                   : 1;
        U32                             : 29;
    } bitc;
} GH_WDT_CTRLR_REAL_S;

typedef union { /* WDT_TimeoutR */
    U32 all;
    struct {
        U32 timeout                     : 1;
        U32                             : 31;
    } bitc;
} GH_WDT_TIMEOUTR_REAL_S;

typedef union { /* WDT_ClrR */
    U32 all;
    struct {
        U32 clr                         : 1;
        U32                             : 31;
    } bitc;
} GH_WDT_CLRR_REAL_S;

typedef union { /* WDT_RstWdR */
    U32 all;
    struct {
        U32 rstwd                       : 8;
        U32                             : 24;
    } bitc;
} GH_WDT_RSTWDR_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
U32                                     m_wdt_restartr;
GH_WDT_CLRR_S                           m_wdt_clrr;

/*----------------------------------------------------------------------------*/
/* register WDT_CntStsR (read)                                                */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_WDT_get_CntStsR(void)
{
    U32 value = (*(volatile U32 *)REG_WDT_CNTSTSR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register WDT_ReloadR (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_WDT_set_ReloadR(U32 data)
{
    *(volatile U32 *)REG_WDT_RELOADR_REAL = data;
}
GH_INLINE U32  GH_WDT_get_ReloadR(void)
{
    U32 value = (*(volatile U32 *)REG_WDT_RELOADR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register WDT_RestartR (write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_WDT_set_RestartR(U32 data)
{
    m_wdt_restartr = data;
    *(volatile U32 *)REG_WDT_RESTARTR_REAL = data;
}
GH_INLINE U32  GH_WDT_getm_RestartR(void)
{
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "[GH_WDT_getm_RestartR] --> 0x%08x\n",
                        m_wdt_restartr);
    #endif
    return m_wdt_restartr;
}

/*----------------------------------------------------------------------------*/
/* register WDT_CtrlR (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_WDT_set_CtrlR(U32 data)
{
    GH_WDT_CTRLR_REAL_S real;
    GH_WDT_CTRLR_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    real.bitc.resetenable = dummy.bitc.resetenable;
    real.bitc.intenable = dummy.bitc.intenable;
    *(volatile U32 *)REG_WDT_CTRLR_REAL = real.all;
}
GH_INLINE U32  GH_WDT_get_CtrlR(void)
{
    GH_WDT_CTRLR_REAL_S real;
    GH_WDT_CTRLR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_WDT_CTRLR_REAL);

    dummy.bitc.enable = real.bitc.enable;
    dummy.bitc.resetenable = real.bitc.resetenable;
    dummy.bitc.intenable = real.bitc.intenable;
    return dummy.all;
}
GH_INLINE void GH_WDT_set_CtrlR_Enable(U8 data)
{
    GH_WDT_CTRLR_REAL_S d;
    d.all = *(volatile U32 *)REG_WDT_CTRLR_REAL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_WDT_CTRLR_REAL = d.all;
}
GH_INLINE U8   GH_WDT_get_CtrlR_Enable(void)
{
    GH_WDT_CTRLR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_WDT_CTRLR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}
GH_INLINE void GH_WDT_set_CtrlR_ResetEnable(U8 data)
{
    GH_WDT_CTRLR_REAL_S d;
    d.all = *(volatile U32 *)REG_WDT_CTRLR_REAL;
    d.bitc.resetenable = data;
    *(volatile U32 *)REG_WDT_CTRLR_REAL = d.all;
}
GH_INLINE U8   GH_WDT_get_CtrlR_ResetEnable(void)
{
    GH_WDT_CTRLR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_WDT_CTRLR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.resetenable;
}
GH_INLINE void GH_WDT_set_CtrlR_IntEnable(U8 data)
{
    GH_WDT_CTRLR_REAL_S d;
    d.all = *(volatile U32 *)REG_WDT_CTRLR_REAL;
    d.bitc.intenable = data;
    *(volatile U32 *)REG_WDT_CTRLR_REAL = d.all;
}
GH_INLINE U8   GH_WDT_get_CtrlR_IntEnable(void)
{
    GH_WDT_CTRLR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_WDT_CTRLR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.intenable;
}

/*----------------------------------------------------------------------------*/
/* register WDT_TimeoutR (read)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_WDT_get_TimeoutR(void)
{
    GH_WDT_TIMEOUTR_REAL_S real;
    GH_WDT_TIMEOUTR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_WDT_TIMEOUTR_REAL);

    dummy.bitc.timeout = real.bitc.timeout;
    return dummy.all;
}
GH_INLINE U8   GH_WDT_get_TimeoutR_Timeout(void)
{
    GH_WDT_TIMEOUTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_WDT_TIMEOUTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.timeout;
}

/*----------------------------------------------------------------------------*/
/* register WDT_ClrR (write)                                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_WDT_set_ClrR(U32 data)
{
    m_wdt_clrr.all = data;
    GH_WDT_CLRR_REAL_S real;
    GH_WDT_CLRR_S dummy;
    dummy.all = data ;
    real.bitc.clr = dummy.bitc.clr;
    *(volatile U32 *)REG_WDT_CLRR_REAL = real.all;
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
    GH_WDT_CLRR_REAL_S real;
    real.bitc.clr = m_wdt_clrr.bitc.clr;
    *(volatile U32 *)REG_WDT_CLRR_REAL = real.all;
}
GH_INLINE U8   GH_WDT_getm_ClrR_Clr(void)
{
    #if GH_WDT_ENABLE_DEBUG_PRINT
    GH_WDT_DEBUG_PRINT_FUNCTION( "[GH_WDT_getm_ClrR_Clr] --> 0x%08x\n",
                        m_wdt_clrr.bitc.clr);
    #endif
    return m_wdt_clrr.bitc.clr;
}

/*----------------------------------------------------------------------------*/
/* register WDT_RstWdR (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_WDT_set_RstWdR(U32 data)
{
    GH_WDT_RSTWDR_REAL_S real;
    GH_WDT_RSTWDR_S dummy;
    dummy.all = data ;
    real.bitc.rstwd = dummy.bitc.rstwd;
    *(volatile U32 *)REG_WDT_RSTWDR_REAL = real.all;
}
GH_INLINE U32  GH_WDT_get_RstWdR(void)
{
    GH_WDT_RSTWDR_REAL_S real;
    GH_WDT_RSTWDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_WDT_RSTWDR_REAL);

    dummy.bitc.rstwd = real.bitc.rstwd;
    return dummy.all;
}
GH_INLINE void GH_WDT_set_RstWdR_RstWd(U8 data)
{
    GH_WDT_RSTWDR_REAL_S d;
    d.all = *(volatile U32 *)REG_WDT_RSTWDR_REAL;
    d.bitc.rstwd = data;
    *(volatile U32 *)REG_WDT_RSTWDR_REAL = d.all;
}
GH_INLINE U8   GH_WDT_get_RstWdR_RstWd(void)
{
    GH_WDT_RSTWDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_WDT_RSTWDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rstwd;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_WDT_init(void)
{
    GH_WDT_set_ReloadR((U32)0x03ef1480);
    GH_WDT_set_RestartR((U32)0x00000000);
    GH_WDT_set_CtrlR((U32)0x00000000);
    GH_WDT_set_ClrR((U32)0x00000000);
    GH_WDT_set_RstWdR((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

