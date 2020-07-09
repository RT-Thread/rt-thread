/*!
*******************************************************************************
**
** \file      gh_vo_top.h
**
** \brief     TOP control Registers.
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
#ifndef _GH_VO_TOP_H
#define _GH_VO_TOP_H

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

#define GH_VO_TOP_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VO_TOP_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VO_TOP_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VO_TOP_ENABLE_DEBUG_PRINT
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
#define REG_VO_TOP_RESET_VOUT                               FIO_ADDRESS(VO_TOP,0x90004A00) /* read/write */
#define REG_VO_TOP_ENABLE_CLOCK_A                           FIO_ADDRESS(VO_TOP,0x90004A04) /* read/write */
#define REG_VO_TOP_ENABLE_CLOCK_B                           FIO_ADDRESS(VO_TOP,0x90004A08) /* read/write */
#define REG_VO_TOP_ENABLE_CLOCK_OSDR                        FIO_ADDRESS(VO_TOP,0x90004A0C) /* read/write */
#define REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING              FIO_ADDRESS(VO_TOP,0x90004A10) /* read/write */
#define REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING               FIO_ADDRESS(VO_TOP,0x90004A14) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_TOP_RESET_VOUT */
    U32 all;
    struct {
        U32                             : 31;
        U32 reset                       : 1;
    } bitc;
} GH_VO_TOP_RESET_VOUT_S;

typedef union { /* VO_TOP_ENABLE_CLOCK_A */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_CLOCK_A_S;

typedef union { /* VO_TOP_ENABLE_CLOCK_B */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_CLOCK_B_S;

typedef union { /* VO_TOP_ENABLE_CLOCK_OSDR */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_CLOCK_OSDR_S;

typedef union { /* VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_S;

typedef union { /* VO_TOP_ENABLE_CONFIG_CLOCK_GATING */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VO_TOP_RESET_VOUT (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_TOP_RESET_VOUT'. */
void GH_VO_TOP_set_RESET_VOUT(U32 data);
/*! \brief Reads the register 'VO_TOP_RESET_VOUT'. */
U32  GH_VO_TOP_get_RESET_VOUT(void);
/*! \brief Writes the bit group 'reset' of register 'VO_TOP_RESET_VOUT'. */
void GH_VO_TOP_set_RESET_VOUT_reset(U8 data);
/*! \brief Reads the bit group 'reset' of register 'VO_TOP_RESET_VOUT'. */
U8   GH_VO_TOP_get_RESET_VOUT_reset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_TOP_set_RESET_VOUT(U32 data)
{
    *(volatile U32 *)REG_VO_TOP_RESET_VOUT = data;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_RESET_VOUT] <-- 0x%08x\n",
                        REG_VO_TOP_RESET_VOUT,data,data);
    #endif
}
GH_INLINE U32  GH_VO_TOP_get_RESET_VOUT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_TOP_RESET_VOUT);

    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_RESET_VOUT] --> 0x%08x\n",
                        REG_VO_TOP_RESET_VOUT,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_TOP_set_RESET_VOUT_reset(U8 data)
{
    GH_VO_TOP_RESET_VOUT_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_RESET_VOUT;
    d.bitc.reset = data;
    *(volatile U32 *)REG_VO_TOP_RESET_VOUT = d.all;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_RESET_VOUT_reset] <-- 0x%08x\n",
                        REG_VO_TOP_RESET_VOUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_TOP_get_RESET_VOUT_reset(void)
{
    GH_VO_TOP_RESET_VOUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_RESET_VOUT);

    tmp_value.all = value;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_RESET_VOUT_reset] --> 0x%08x\n",
                        REG_VO_TOP_RESET_VOUT,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CLOCK_A (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_TOP_ENABLE_CLOCK_A'. */
void GH_VO_TOP_set_ENABLE_CLOCK_A(U32 data);
/*! \brief Reads the register 'VO_TOP_ENABLE_CLOCK_A'. */
U32  GH_VO_TOP_get_ENABLE_CLOCK_A(void);
/*! \brief Writes the bit group 'enable' of register 'VO_TOP_ENABLE_CLOCK_A'. */
void GH_VO_TOP_set_ENABLE_CLOCK_A_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_TOP_ENABLE_CLOCK_A'. */
U8   GH_VO_TOP_get_ENABLE_CLOCK_A_enable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_TOP_set_ENABLE_CLOCK_A(U32 data)
{
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A = data;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CLOCK_A] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_A,data,data);
    #endif
}
GH_INLINE U32  GH_VO_TOP_get_ENABLE_CLOCK_A(void)
{
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A);

    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CLOCK_A] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_A,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_TOP_set_ENABLE_CLOCK_A_enable(U8 data)
{
    GH_VO_TOP_ENABLE_CLOCK_A_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A = d.all;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CLOCK_A_enable] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_TOP_get_ENABLE_CLOCK_A_enable(void)
{
    GH_VO_TOP_ENABLE_CLOCK_A_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A);

    tmp_value.all = value;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CLOCK_A_enable] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_A,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CLOCK_B (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_TOP_ENABLE_CLOCK_B'. */
void GH_VO_TOP_set_ENABLE_CLOCK_B(U32 data);
/*! \brief Reads the register 'VO_TOP_ENABLE_CLOCK_B'. */
U32  GH_VO_TOP_get_ENABLE_CLOCK_B(void);
/*! \brief Writes the bit group 'enable' of register 'VO_TOP_ENABLE_CLOCK_B'. */
void GH_VO_TOP_set_ENABLE_CLOCK_B_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_TOP_ENABLE_CLOCK_B'. */
U8   GH_VO_TOP_get_ENABLE_CLOCK_B_enable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_TOP_set_ENABLE_CLOCK_B(U32 data)
{
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B = data;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CLOCK_B] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_B,data,data);
    #endif
}
GH_INLINE U32  GH_VO_TOP_get_ENABLE_CLOCK_B(void)
{
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B);

    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CLOCK_B] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_B,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_TOP_set_ENABLE_CLOCK_B_enable(U8 data)
{
    GH_VO_TOP_ENABLE_CLOCK_B_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B = d.all;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CLOCK_B_enable] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_B,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_TOP_get_ENABLE_CLOCK_B_enable(void)
{
    GH_VO_TOP_ENABLE_CLOCK_B_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B);

    tmp_value.all = value;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CLOCK_B_enable] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_B,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CLOCK_OSDR (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_TOP_ENABLE_CLOCK_OSDR'. */
void GH_VO_TOP_set_ENABLE_CLOCK_OSDR(U32 data);
/*! \brief Reads the register 'VO_TOP_ENABLE_CLOCK_OSDR'. */
U32  GH_VO_TOP_get_ENABLE_CLOCK_OSDR(void);
/*! \brief Writes the bit group 'enable' of register 'VO_TOP_ENABLE_CLOCK_OSDR'. */
void GH_VO_TOP_set_ENABLE_CLOCK_OSDR_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_TOP_ENABLE_CLOCK_OSDR'. */
U8   GH_VO_TOP_get_ENABLE_CLOCK_OSDR_enable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_TOP_set_ENABLE_CLOCK_OSDR(U32 data)
{
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR = data;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CLOCK_OSDR] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_OSDR,data,data);
    #endif
}
GH_INLINE U32  GH_VO_TOP_get_ENABLE_CLOCK_OSDR(void)
{
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR);

    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CLOCK_OSDR] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_OSDR,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_TOP_set_ENABLE_CLOCK_OSDR_enable(U8 data)
{
    GH_VO_TOP_ENABLE_CLOCK_OSDR_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR = d.all;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CLOCK_OSDR_enable] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_OSDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_TOP_get_ENABLE_CLOCK_OSDR_enable(void)
{
    GH_VO_TOP_ENABLE_CLOCK_OSDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR);

    tmp_value.all = value;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CLOCK_OSDR_enable] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_OSDR,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING (read/write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING'. */
void GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING(U32 data);
/*! \brief Reads the register 'VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING'. */
U32  GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING(void);
/*! \brief Writes the bit group 'enable' of register 'VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING'. */
void GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING'. */
U8   GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING_enable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING(U32 data)
{
    *(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING = data;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING,data,data);
    #endif
}
GH_INLINE U32  GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING(void)
{
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING);

    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING_enable(U8 data)
{
    GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING = d.all;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING_enable] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING_enable(void)
{
    GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING);

    tmp_value.all = value;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING_enable] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CONFIG_CLOCK_GATING (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_TOP_ENABLE_CONFIG_CLOCK_GATING'. */
void GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING(U32 data);
/*! \brief Reads the register 'VO_TOP_ENABLE_CONFIG_CLOCK_GATING'. */
U32  GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING(void);
/*! \brief Writes the bit group 'enable' of register 'VO_TOP_ENABLE_CONFIG_CLOCK_GATING'. */
void GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_TOP_ENABLE_CONFIG_CLOCK_GATING'. */
U8   GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING_enable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING(U32 data)
{
    *(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING = data;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING,data,data);
    #endif
}
GH_INLINE U32  GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING(void)
{
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING);

    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING_enable(U8 data)
{
    GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING = d.all;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING_enable] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING_enable(void)
{
    GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING);

    tmp_value.all = value;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING_enable] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_TOP_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_TOP_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

