/*!
*******************************************************************************
**
** \file      gh_debug_memd.h
**
** \brief     MEMD Debug Registers.
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
#ifndef _GH_DEBUG_MEMD_H
#define _GH_DEBUG_MEMD_H

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

#define GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION printk
#else
#define GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
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
#define REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR                  FIO_ADDRESS(DEBUG_MEMD,0xa0150000) /* read/write */
#define REG_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR                FIO_ADDRESS(DEBUG_MEMD,0xa0150004) /* write */
#define REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR                FIO_ADDRESS(DEBUG_MEMD,0xa0150008) /* read/write */
#define REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR                 FIO_ADDRESS(DEBUG_MEMD,0xa015000C) /* read/write */
#define REG_DEBUG_MEMD_MEMD_CR_TS_T0_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa0150010) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_TS_T1_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa0150014) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_TS_T2_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa0150018) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_TS_T3_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa015001C) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_IS_ADDR                      FIO_ADDRESS(DEBUG_MEMD,0xa0150020) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR                     FIO_ADDRESS(DEBUG_MEMD,0xa0150024) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_PC_T0_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa0150028) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_PC_T1_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa015002C) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_PC_T2_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa0150030) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_PC_T3_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa0150034) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR                    FIO_ADDRESS(DEBUG_MEMD,0xa0150038) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_OP_D_ADDR                    FIO_ADDRESS(DEBUG_MEMD,0xa015003C) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_STALL_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa0150040) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_DMAQ0_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa0150044) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_DMAQ1_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa0150048) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_DMAQ2_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa015004C) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_CMDQ0_ADDR                   FIO_ADDRESS(DEBUG_MEMD,0xa0150050) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_ME_ADDR                      FIO_ADDRESS(DEBUG_MEMD,0xa0150060) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_MD_ADDR                      FIO_ADDRESS(DEBUG_MEMD,0xa0150064) /* read */
#define REG_DEBUG_MEMD_MEMD_CR_RF_ADDR                      FIO_ADDRESS(DEBUG_MEMD,0xa0150800) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* DEBUG_MEMD_MEMD_CR_TRESET_ADDR */
    U32 all;
    struct {
        U32 reset                       : 4;
        U32 suspend                     : 4;
        U32                             : 23;
        U32 orc_reset                   : 1;
    } bitc;
} GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S;

typedef union { /* DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR */
    U32 all;
    struct {
        U32 icache                      : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR_S;

typedef union { /* DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR */
    U32 all;
    struct {
        U32 reset                       : 32;
    } bitc;
} GH_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_S;

typedef union { /* DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR */
    U32 all;
    struct {
        U32 mctf                        : 1;
        U32 me                          : 1;
        U32 md                          : 1;
        U32                             : 1;
        U32 mctf_hw                     : 1;
        U32 me_hw                       : 1;
        U32 md_hw                       : 1;
        U32                             : 25;
    } bitc;
} GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S;

typedef union { /* DEBUG_MEMD_MEMD_CR_LRU_ADDR */
    U32 all;
    struct {
        U32 entry0                      : 4;
        U32 entry1                      : 4;
        U32 entry2                      : 4;
        U32 entry3                      : 4;
        U32                             : 16;
    } bitc;
} GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_S;

typedef union { /* DEBUG_MEMD_MEMD_CR_PC_D_ADDR */
    U32 all;
    struct {
        U32 pc_d                        : 20;
        U32                             : 11;
        U32 vld_d                       : 1;
    } bitc;
} GH_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR_S   m_debug_memd_memd_cr_ic_invld_addr;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TRESET_ADDR (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_MEMD_MEMD_CR_TRESET_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR(U32 data);
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_TRESET_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR(void);
/*! \brief Writes the bit group 'reset' of register 'DEBUG_MEMD_MEMD_CR_TRESET_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_reset(U8 data);
/*! \brief Reads the bit group 'reset' of register 'DEBUG_MEMD_MEMD_CR_TRESET_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_reset(void);
/*! \brief Writes the bit group 'suspend' of register 'DEBUG_MEMD_MEMD_CR_TRESET_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_suspend(U8 data);
/*! \brief Reads the bit group 'suspend' of register 'DEBUG_MEMD_MEMD_CR_TRESET_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_suspend(void);
/*! \brief Writes the bit group 'ORC_reset' of register 'DEBUG_MEMD_MEMD_CR_TRESET_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_ORC_reset(U8 data);
/*! \brief Reads the bit group 'ORC_reset' of register 'DEBUG_MEMD_MEMD_CR_TRESET_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_ORC_reset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR = data;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_reset(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_reset] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_reset(void)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_reset] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,value);
    #endif
    return tmp_value.bitc.reset;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_suspend(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR;
    d.bitc.suspend = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_suspend] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_suspend(void)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_suspend] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,value);
    #endif
    return tmp_value.bitc.suspend;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_ORC_reset(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR;
    d.bitc.orc_reset = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_ORC_reset] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_ORC_reset(void)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_ORC_reset] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,value);
    #endif
    return tmp_value.bitc.orc_reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR (write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR(U32 data);
/*! \brief Reads the mirror variable of the register 'DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR'. */
U32  GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR(void);
/*! \brief Writes the bit group 'icache' of register 'DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR_icache(U8 data);
/*! \brief Reads the bit group 'icache' from the mirror variable of register 'DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR'. */
U8   GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR_icache(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR(U32 data)
{
    m_debug_memd_memd_cr_ic_invld_addr.all = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR = data;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR(void)
{
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR] --> 0x%08x\n",
                        m_debug_memd_memd_cr_ic_invld_addr.all);
    #endif
    return m_debug_memd_memd_cr_ic_invld_addr.all;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR_icache(U8 data)
{
    m_debug_memd_memd_cr_ic_invld_addr.bitc.icache = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR = m_debug_memd_memd_cr_ic_invld_addr.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR_icache] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR,m_debug_memd_memd_cr_ic_invld_addr.all,m_debug_memd_memd_cr_ic_invld_addr.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR_icache(void)
{
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR_icache] --> 0x%08x\n",
                        m_debug_memd_memd_cr_ic_invld_addr.bitc.icache);
    #endif
    return m_debug_memd_memd_cr_ic_invld_addr.bitc.icache;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR (read/write)                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR(U32 data);
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_RESET_PC_ADDR(void);
/*! \brief Writes the bit group 'reset' of register 'DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR_reset(U32 data);
/*! \brief Reads the bit group 'reset' of register 'DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_RESET_PC_ADDR_reset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR = data;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_RESET_PC_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_RESET_PC_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR_reset(U32 data)
{
    GH_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR_reset] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_RESET_PC_ADDR_reset(void)
{
    GH_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_RESET_PC_ADDR_reset] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR(U32 data);
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR(void);
/*! \brief Writes the bit group 'MCTF' of register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MCTF(U8 data);
/*! \brief Reads the bit group 'MCTF' of register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MCTF(void);
/*! \brief Writes the bit group 'ME' of register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_ME(U8 data);
/*! \brief Reads the bit group 'ME' of register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_ME(void);
/*! \brief Writes the bit group 'MD' of register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MD(U8 data);
/*! \brief Reads the bit group 'MD' of register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MD(void);
/*! \brief Writes the bit group 'MCTF_HW' of register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MCTF_HW(U8 data);
/*! \brief Reads the bit group 'MCTF_HW' of register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MCTF_HW(void);
/*! \brief Writes the bit group 'ME_HW' of register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_ME_HW(U8 data);
/*! \brief Reads the bit group 'ME_HW' of register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_ME_HW(void);
/*! \brief Writes the bit group 'MD_HW' of register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MD_HW(U8 data);
/*! \brief Reads the bit group 'MD_HW' of register 'DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MD_HW(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = data;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MCTF(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR;
    d.bitc.mctf = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MCTF] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MCTF(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MCTF] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return tmp_value.bitc.mctf;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_ME(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR;
    d.bitc.me = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_ME] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_ME(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_ME] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return tmp_value.bitc.me;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MD(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR;
    d.bitc.md = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MD] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MD(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MD] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return tmp_value.bitc.md;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MCTF_HW(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR;
    d.bitc.mctf_hw = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MCTF_HW] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MCTF_HW(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MCTF_HW] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return tmp_value.bitc.mctf_hw;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_ME_HW(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR;
    d.bitc.me_hw = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_ME_HW] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_ME_HW(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_ME_HW] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return tmp_value.bitc.me_hw;
}
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MD_HW(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR;
    d.bitc.md_hw = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MD_HW] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MD_HW(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MD_HW] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return tmp_value.bitc.md_hw;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TS_T0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_TS_T0_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T0_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TS_T0_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TS_T0_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TS_T0_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TS_T1_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_TS_T1_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T1_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T1_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TS_T1_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TS_T1_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TS_T1_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TS_T2_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_TS_T2_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T2_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T2_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TS_T2_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TS_T2_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TS_T2_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TS_T3_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_TS_T3_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T3_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T3_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TS_T3_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TS_T3_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TS_T3_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_IS_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_IS_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_IS_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_IS_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_IS_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_IS_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_IS_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_LRU_ADDR (read)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_LRU_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR(void);
/*! \brief Reads the bit group 'entry0' of register 'DEBUG_MEMD_MEMD_CR_LRU_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry0(void);
/*! \brief Reads the bit group 'entry1' of register 'DEBUG_MEMD_MEMD_CR_LRU_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry1(void);
/*! \brief Reads the bit group 'entry2' of register 'DEBUG_MEMD_MEMD_CR_LRU_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry2(void);
/*! \brief Reads the bit group 'entry3' of register 'DEBUG_MEMD_MEMD_CR_LRU_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry3(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry0(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry0] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR,value);
    #endif
    return tmp_value.bitc.entry0;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry1(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry1] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR,value);
    #endif
    return tmp_value.bitc.entry1;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry2(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry2] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR,value);
    #endif
    return tmp_value.bitc.entry2;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry3(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry3] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR,value);
    #endif
    return tmp_value.bitc.entry3;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_T0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_PC_T0_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T0_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_T0_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_T0_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_T0_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_T1_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_PC_T1_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T1_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T1_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_T1_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_T1_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_T1_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_T2_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_PC_T2_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T2_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T2_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_T2_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_T2_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_T2_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_T3_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_PC_T3_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T3_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T3_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_T3_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_T3_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_T3_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_D_ADDR (read)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_PC_D_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR(void);
/*! \brief Reads the bit group 'pc_d' of register 'DEBUG_MEMD_MEMD_CR_PC_D_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR_pc_d(void);
/*! \brief Reads the bit group 'vld_d' of register 'DEBUG_MEMD_MEMD_CR_PC_D_ADDR'. */
U8   GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR_vld_d(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR,value);
    #endif
    return value;
}
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR_pc_d(void)
{
    GH_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR_pc_d] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR,value);
    #endif
    return tmp_value.bitc.pc_d;
}
GH_INLINE U8   GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR_vld_d(void)
{
    GH_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR_vld_d] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR,value);
    #endif
    return tmp_value.bitc.vld_d;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_OP_D_ADDR (read)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_OP_D_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_OP_D_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_OP_D_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_OP_D_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_OP_D_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_OP_D_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_STALL_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_STALL_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_STALL_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_STALL_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_STALL_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_STALL_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_STALL_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_DMAQ0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_DMAQ0_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_DMAQ0_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_DMAQ0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_DMAQ0_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_DMAQ0_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_DMAQ0_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_DMAQ1_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_DMAQ1_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_DMAQ1_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_DMAQ1_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_DMAQ1_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_DMAQ1_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_DMAQ1_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_DMAQ2_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_DMAQ2_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_DMAQ2_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_DMAQ2_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_DMAQ2_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_DMAQ2_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_DMAQ2_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_CMDQ0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_CMDQ0_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_CMDQ0_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_CMDQ0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CMDQ0_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CMDQ0_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CMDQ0_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_ME_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_ME_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_ME_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_ME_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_ME_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_ME_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_ME_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_MD_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_MD_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_MD_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_MD_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_MD_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_MD_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_MD_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_RF_ADDR (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_MEMD_MEMD_CR_RF_ADDR'. */
void GH_DEBUG_MEMD_set_MEMD_CR_RF_ADDR(U32 data);
/*! \brief Reads the register 'DEBUG_MEMD_MEMD_CR_RF_ADDR'. */
U32  GH_DEBUG_MEMD_get_MEMD_CR_RF_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_MEMD_set_MEMD_CR_RF_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RF_ADDR = data;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_RF_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_RF_ADDR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_MEMD_get_MEMD_CR_RF_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RF_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_RF_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_RF_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_DEBUG_MEMD_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_DEBUG_MEMD_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

