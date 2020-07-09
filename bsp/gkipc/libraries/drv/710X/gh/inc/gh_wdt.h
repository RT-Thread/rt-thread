/*!
*******************************************************************************
**
** \file      gh_wdt.h
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

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_WDT_CNTSTSR                                     FIO_ADDRESS(WDT,0xa000C000) /* read */
#define REG_WDT_RELOADR                                     FIO_ADDRESS(WDT,0xa000C004) /* read/write */
#define REG_WDT_RESTARTR                                    FIO_ADDRESS(WDT,0xa000C008) /* write */
#define REG_WDT_CTRLR                                       FIO_ADDRESS(WDT,0xa000C00C) /* read/write */
#define REG_WDT_TIMEOUTR                                    FIO_ADDRESS(WDT,0xa000C010) /* read */
#define REG_WDT_CLRR                                        FIO_ADDRESS(WDT,0xa000C014) /* write */
#define REG_WDT_RSTWDR                                      FIO_ADDRESS(WDT,0xa000C018) /* read/write */

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
extern U32                                     m_wdt_restartr;
extern GH_WDT_CLRR_S                           m_wdt_clrr;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register WDT_CntStsR (read)                                                */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'WDT_CntStsR'. */
U32  GH_WDT_get_CntStsR(void);

/*----------------------------------------------------------------------------*/
/* register WDT_ReloadR (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'WDT_ReloadR'. */
void GH_WDT_set_ReloadR(U32 data);
/*! \brief Reads the register 'WDT_ReloadR'. */
U32  GH_WDT_get_ReloadR(void);

/*----------------------------------------------------------------------------*/
/* register WDT_RestartR (write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'WDT_RestartR'. */
void GH_WDT_set_RestartR(U32 data);
/*! \brief Reads the mirror variable of the register 'WDT_RestartR'. */
U32  GH_WDT_getm_RestartR(void);

/*----------------------------------------------------------------------------*/
/* register WDT_CtrlR (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'WDT_CtrlR'. */
void GH_WDT_set_CtrlR(U32 data);
/*! \brief Reads the register 'WDT_CtrlR'. */
U32  GH_WDT_get_CtrlR(void);
/*! \brief Writes the bit group 'Enable' of register 'WDT_CtrlR'. */
void GH_WDT_set_CtrlR_Enable(U8 data);
/*! \brief Reads the bit group 'Enable' of register 'WDT_CtrlR'. */
U8   GH_WDT_get_CtrlR_Enable(void);
/*! \brief Writes the bit group 'ResetEnable' of register 'WDT_CtrlR'. */
void GH_WDT_set_CtrlR_ResetEnable(U8 data);
/*! \brief Reads the bit group 'ResetEnable' of register 'WDT_CtrlR'. */
U8   GH_WDT_get_CtrlR_ResetEnable(void);
/*! \brief Writes the bit group 'IntEnable' of register 'WDT_CtrlR'. */
void GH_WDT_set_CtrlR_IntEnable(U8 data);
/*! \brief Reads the bit group 'IntEnable' of register 'WDT_CtrlR'. */
U8   GH_WDT_get_CtrlR_IntEnable(void);

/*----------------------------------------------------------------------------*/
/* register WDT_TimeoutR (read)                                               */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'WDT_TimeoutR'. */
U32  GH_WDT_get_TimeoutR(void);
/*! \brief Reads the bit group 'Timeout' of register 'WDT_TimeoutR'. */
U8   GH_WDT_get_TimeoutR_Timeout(void);

/*----------------------------------------------------------------------------*/
/* register WDT_ClrR (write)                                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'WDT_ClrR'. */
void GH_WDT_set_ClrR(U32 data);
/*! \brief Reads the mirror variable of the register 'WDT_ClrR'. */
U32  GH_WDT_getm_ClrR(void);
/*! \brief Writes the bit group 'Clr' of register 'WDT_ClrR'. */
void GH_WDT_set_ClrR_Clr(U8 data);
/*! \brief Reads the bit group 'Clr' from the mirror variable of register 'WDT_ClrR'. */
U8   GH_WDT_getm_ClrR_Clr(void);

/*----------------------------------------------------------------------------*/
/* register WDT_RstWdR (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'WDT_RstWdR'. */
void GH_WDT_set_RstWdR(U32 data);
/*! \brief Reads the register 'WDT_RstWdR'. */
U32  GH_WDT_get_RstWdR(void);
/*! \brief Writes the bit group 'RstWd' of register 'WDT_RstWdR'. */
void GH_WDT_set_RstWdR_RstWd(U8 data);
/*! \brief Reads the bit group 'RstWd' of register 'WDT_RstWdR'. */
U8   GH_WDT_get_RstWdR_RstWd(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_WDT_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_wdt.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_WDT_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

