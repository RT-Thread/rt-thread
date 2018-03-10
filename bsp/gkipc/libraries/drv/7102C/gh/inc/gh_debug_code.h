/*!
*******************************************************************************
**
** \file      gh_debug_code.h
**
** \brief     CODE Debug Registers.
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
#ifndef _GH_DEBUG_CODE_H
#define _GH_DEBUG_CODE_H

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

#define GH_DEBUG_CODE_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION printk
#else
#define GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
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
#define REG_DEBUG_CODE_CODE_CR_TRESET_ADDR                  FIO_ADDRESS(DEBUG_CODE,0xa0160000) /* read/write */
#define REG_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR                FIO_ADDRESS(DEBUG_CODE,0xa0160004) /* write */
#define REG_DEBUG_CODE_CODE_CR_RESET_PC_ADDR                FIO_ADDRESS(DEBUG_CODE,0xa0160008) /* read/write */
#define REG_DEBUG_CODE_CODE_CR_TS_ADDR                      FIO_ADDRESS(DEBUG_CODE,0xa0160010) /* read */
#define REG_DEBUG_CODE_CODE_CR_PC_T0_ADDR                   FIO_ADDRESS(DEBUG_CODE,0xa0160020) /* read */
#define REG_DEBUG_CODE_CODE_CR_PC_T1_ADDR                   FIO_ADDRESS(DEBUG_CODE,0xa0160024) /* read */
#define REG_DEBUG_CODE_CODE_CR_PC_T2_ADDR                   FIO_ADDRESS(DEBUG_CODE,0xa0160028) /* read */
#define REG_DEBUG_CODE_CODE_CR_PC_T3_ADDR                   FIO_ADDRESS(DEBUG_CODE,0xa016002C) /* read */
#define REG_DEBUG_CODE_CODE_CR_STALL_ADDR                   FIO_ADDRESS(DEBUG_CODE,0xa0160038) /* read */
#define REG_DEBUG_CODE_CODE_CR_RF_ADDR                      FIO_ADDRESS(DEBUG_CODE,0xa0160200) /* read */
#define REG_DEBUG_CODE_CODE_CR_DC_ADDR                      FIO_ADDRESS(DEBUG_CODE,0xa0164000) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* DEBUG_CODE_CODE_CR_IC_INVLD_ADDR */
    U32 all;
    struct {
        U32 invalid_icache              : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR_S;

typedef union { /* DEBUG_CODE_CODE_CR_TS_ADDR */
    U32 all;
    struct {
        U32 ts_t0_run                   : 1;
        U32 ts_t0_restmr                : 1;
        U32 ts_t0_dmab4                 : 1;
        U32 ts_t0_codeb4                : 1;
        U32 ts_t0_sendb4                : 1;
        U32 ts_t0_recb4                 : 1;
        U32                             : 2;
        U32 ts_t1_run                   : 1;
        U32 ts_t1_restmr                : 1;
        U32 ts_t1_dmab4                 : 1;
        U32 ts_t1_codeb4                : 1;
        U32 ts_t1_sendb4                : 1;
        U32 ts_t1_recb4                 : 1;
        U32                             : 2;
        U32 ts_t2_run                   : 1;
        U32 ts_t2_restmr                : 1;
        U32 ts_t2_dmab4                 : 1;
        U32 ts_t2_codeb4                : 1;
        U32 ts_t2_sendb4                : 1;
        U32 ts_t2_recb4                 : 1;
        U32                             : 2;
        U32 ts_t3_run                   : 1;
        U32 ts_t3_restmr                : 1;
        U32 ts_t3_dmab4                 : 1;
        U32 ts_t3_codeb4                : 1;
        U32 ts_t3_sendb4                : 1;
        U32 ts_t3_recb4                 : 1;
        U32                             : 2;
    } bitc;
} GH_DEBUG_CODE_CODE_CR_TS_ADDR_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR_S   m_debug_code_code_cr_ic_invld_addr;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_TRESET_ADDR (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_CODE_CODE_CR_TRESET_ADDR'. */
void GH_DEBUG_CODE_set_CODE_CR_TRESET_ADDR(U32 data);
/*! \brief Reads the register 'DEBUG_CODE_CODE_CR_TRESET_ADDR'. */
U32  GH_DEBUG_CODE_get_CODE_CR_TRESET_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_CODE_set_CODE_CR_TRESET_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TRESET_ADDR = data;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_CODE_set_CODE_CR_TRESET_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TRESET_ADDR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_TRESET_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TRESET_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TRESET_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TRESET_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_IC_INVLD_ADDR (write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'DEBUG_CODE_CODE_CR_IC_INVLD_ADDR'. */
void GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR(U32 data);
/*! \brief Reads the mirror variable of the register 'DEBUG_CODE_CODE_CR_IC_INVLD_ADDR'. */
U32  GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR(void);
/*! \brief Writes the bit group 'invalid_icache' of register 'DEBUG_CODE_CODE_CR_IC_INVLD_ADDR'. */
void GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR_invalid_icache(U8 data);
/*! \brief Reads the bit group 'invalid_icache' from the mirror variable of register 'DEBUG_CODE_CODE_CR_IC_INVLD_ADDR'. */
U8   GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR_invalid_icache(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR(U32 data)
{
    m_debug_code_code_cr_ic_invld_addr.all = data;
    *(volatile U32 *)REG_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR = data;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR(void)
{
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR] --> 0x%08x\n",
                        m_debug_code_code_cr_ic_invld_addr.all);
    #endif
    return m_debug_code_code_cr_ic_invld_addr.all;
}
GH_INLINE void GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR_invalid_icache(U8 data)
{
    m_debug_code_code_cr_ic_invld_addr.bitc.invalid_icache = data;
    *(volatile U32 *)REG_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR = m_debug_code_code_cr_ic_invld_addr.all;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR_invalid_icache] <-- 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR,m_debug_code_code_cr_ic_invld_addr.all,m_debug_code_code_cr_ic_invld_addr.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR_invalid_icache(void)
{
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR_invalid_icache] --> 0x%08x\n",
                        m_debug_code_code_cr_ic_invld_addr.bitc.invalid_icache);
    #endif
    return m_debug_code_code_cr_ic_invld_addr.bitc.invalid_icache;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_RESET_PC_ADDR (read/write)                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_CODE_CODE_CR_RESET_PC_ADDR'. */
void GH_DEBUG_CODE_set_CODE_CR_RESET_PC_ADDR(U32 data);
/*! \brief Reads the register 'DEBUG_CODE_CODE_CR_RESET_PC_ADDR'. */
U32  GH_DEBUG_CODE_get_CODE_CR_RESET_PC_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_CODE_set_CODE_CR_RESET_PC_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_CODE_CODE_CR_RESET_PC_ADDR = data;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_CODE_set_CODE_CR_RESET_PC_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_RESET_PC_ADDR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_RESET_PC_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_RESET_PC_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_RESET_PC_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_RESET_PC_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_TS_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U32  GH_DEBUG_CODE_get_CODE_CR_TS_ADDR(void);
/*! \brief Reads the bit group 'ts_t0_run' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_run(void);
/*! \brief Reads the bit group 'ts_t0_restmr' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_restmr(void);
/*! \brief Reads the bit group 'ts_t0_dmab4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_dmab4(void);
/*! \brief Reads the bit group 'ts_t0_codeb4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_codeb4(void);
/*! \brief Reads the bit group 'ts_t0_sendb4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_sendb4(void);
/*! \brief Reads the bit group 'ts_t0_recb4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_recb4(void);
/*! \brief Reads the bit group 'ts_t1_run' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_run(void);
/*! \brief Reads the bit group 'ts_t1_restmr' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_restmr(void);
/*! \brief Reads the bit group 'ts_t1_dmab4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_dmab4(void);
/*! \brief Reads the bit group 'ts_t1_codeb4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_codeb4(void);
/*! \brief Reads the bit group 'ts_t1_sendb4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_sendb4(void);
/*! \brief Reads the bit group 'ts_t1_recb4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_recb4(void);
/*! \brief Reads the bit group 'ts_t2_run' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_run(void);
/*! \brief Reads the bit group 'ts_t2_restmr' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_restmr(void);
/*! \brief Reads the bit group 'ts_t2_dmab4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_dmab4(void);
/*! \brief Reads the bit group 'ts_t2_codeb4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_codeb4(void);
/*! \brief Reads the bit group 'ts_t2_sendb4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_sendb4(void);
/*! \brief Reads the bit group 'ts_t2_recb4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_recb4(void);
/*! \brief Reads the bit group 'ts_t3_run' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_run(void);
/*! \brief Reads the bit group 'ts_t3_restmr' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_restmr(void);
/*! \brief Reads the bit group 'ts_t3_dmab4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_dmab4(void);
/*! \brief Reads the bit group 'ts_t3_codeb4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_codeb4(void);
/*! \brief Reads the bit group 'ts_t3_sendb4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_sendb4(void);
/*! \brief Reads the bit group 'ts_t3_recb4' of register 'DEBUG_CODE_CODE_CR_TS_ADDR'. */
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_recb4(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_TS_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_run(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_run] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t0_run;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_restmr(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_restmr] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t0_restmr;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_dmab4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_dmab4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t0_dmab4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_codeb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_codeb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t0_codeb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_sendb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_sendb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t0_sendb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_recb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_recb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t0_recb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_run(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_run] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t1_run;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_restmr(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_restmr] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t1_restmr;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_dmab4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_dmab4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t1_dmab4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_codeb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_codeb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t1_codeb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_sendb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_sendb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t1_sendb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_recb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_recb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t1_recb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_run(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_run] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t2_run;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_restmr(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_restmr] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t2_restmr;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_dmab4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_dmab4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t2_dmab4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_codeb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_codeb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t2_codeb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_sendb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_sendb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t2_sendb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_recb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_recb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t2_recb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_run(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_run] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t3_run;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_restmr(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_restmr] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t3_restmr;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_dmab4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_dmab4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t3_dmab4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_codeb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_codeb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t3_codeb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_sendb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_sendb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t3_sendb4;
}
GH_INLINE U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_recb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_recb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t3_recb4;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_PC_T0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_CODE_CODE_CR_PC_T0_ADDR'. */
U32  GH_DEBUG_CODE_get_CODE_CR_PC_T0_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_PC_T0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_PC_T0_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_PC_T0_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_PC_T0_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_PC_T1_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_CODE_CODE_CR_PC_T1_ADDR'. */
U32  GH_DEBUG_CODE_get_CODE_CR_PC_T1_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_PC_T1_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_PC_T1_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_PC_T1_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_PC_T1_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_PC_T2_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_CODE_CODE_CR_PC_T2_ADDR'. */
U32  GH_DEBUG_CODE_get_CODE_CR_PC_T2_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_PC_T2_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_PC_T2_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_PC_T2_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_PC_T2_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_PC_T3_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_CODE_CODE_CR_PC_T3_ADDR'. */
U32  GH_DEBUG_CODE_get_CODE_CR_PC_T3_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_PC_T3_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_PC_T3_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_PC_T3_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_PC_T3_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_STALL_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_CODE_CODE_CR_STALL_ADDR'. */
U32  GH_DEBUG_CODE_get_CODE_CR_STALL_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_STALL_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_STALL_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_STALL_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_STALL_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_RF_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_CODE_CODE_CR_RF_ADDR'. */
U32  GH_DEBUG_CODE_get_CODE_CR_RF_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_RF_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_RF_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_RF_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_RF_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_DC_ADDR (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_CODE_CODE_CR_DC_ADDR'. */
void GH_DEBUG_CODE_set_CODE_CR_DC_ADDR(U16 index, U32 data);
/*! \brief Reads the register 'DEBUG_CODE_CODE_CR_DC_ADDR'. */
U32  GH_DEBUG_CODE_get_CODE_CR_DC_ADDR(U16 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_CODE_set_CODE_CR_DC_ADDR(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_CODE_CODE_CR_DC_ADDR + index * FIO_MOFFSET(DEBUG_CODE,0x00000004)) = data;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_CODE_set_CODE_CR_DC_ADDR] <-- 0x%08x\n",
                        (REG_DEBUG_CODE_CODE_CR_DC_ADDR + index * FIO_MOFFSET(DEBUG_CODE,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_CODE_get_CODE_CR_DC_ADDR(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_CODE_CODE_CR_DC_ADDR + index * FIO_MOFFSET(DEBUG_CODE,0x00000004)));

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_DC_ADDR] --> 0x%08x\n",
                        (REG_DEBUG_CODE_CODE_CR_DC_ADDR + index * FIO_MOFFSET(DEBUG_CODE,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_DEBUG_CODE_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_DEBUG_CODE_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

