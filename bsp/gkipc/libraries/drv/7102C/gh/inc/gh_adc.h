/*!
*******************************************************************************
**
** \file      gh_adc.h
**
** \brief     ADC.
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
#ifndef _GH_ADC_H
#define _GH_ADC_H

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

#define GH_ADC_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_ADC_DEBUG_PRINT_FUNCTION printk
#else
#define GH_ADC_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_ADC_ENABLE_DEBUG_PRINT
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
#define REG_ADC_AUX_ATOP_REG0                               FIO_ADDRESS(ADC,0x90020A00) /* read/write */
#define REG_ADC_AUX_ATOP_REG1                               FIO_ADDRESS(ADC,0x90020A04) /* read/write */
#define REG_ADC_AUX_ATOP_REG2                               FIO_ADDRESS(ADC,0x90020A08) /* read/write */
#define REG_ADC_CONTROL                                     FIO_ADDRESS(ADC,0xA0007000) /* read/write */
#define REG_ADC_READDATA                                    FIO_ADDRESS(ADC,0xA0007004) /* read */
#define REG_ADC_ENABLE                                      FIO_ADDRESS(ADC,0xA0007018) /* read/write */
#define REG_ADC_INTCONTROL                                  FIO_ADDRESS(ADC,0xA0007044) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* ADC_AUX_ATOP_REG0 */
    U32 all;
    struct {
        U32 sar_maxsel                  : 4;
        U32 sar_maxnsel                 : 3;
        U32 sar_pd                      : 1;
        U32 sar_oneshot                 : 1;
        U32 sar_freerun                 : 1;
        U32 sar_refnsel                 : 2;
        U32 sar_refsel                  : 3;
        U32 pd_tsi                      : 1;
        U32                             : 16;
    } bitc;
} GH_ADC_AUX_ATOP_REG0_S;

typedef union { /* ADC_AUX_ATOP_REG1 */
    U32 all;
    struct {
        U32 i_sar_key                   : 4;
        U32 sar_key_pge                 : 4;
        U32 sar_key_aie                 : 4;
        U32 oen_sar_key                 : 4;
        U32                             : 16;
    } bitc;
} GH_ADC_AUX_ATOP_REG1_S;

typedef union { /* ADC_AUX_ATOP_REG2 */
    U32 all;
    struct {
        U32 sar_test                    : 4;
        U32 tsi_rctrl12                 : 2;
        U32                             : 2;
        U32 enzyr                       : 1;
        U32 enzyp                       : 1;
        U32 enzxr                       : 1;
        U32 enzxp                       : 1;
        U32 enyn                        : 1;
        U32 enxn                        : 1;
        U32 enzoint                     : 1;
        U32 tsi_is                      : 1;
        U32                             : 16;
    } bitc;
} GH_ADC_AUX_ATOP_REG2_S;

typedef union { /* ADC_Control */
    U32 all;
    struct {
        U32 status                      : 1;
        U32 start                       : 1;
        U32                             : 1;
        U32 channel                     : 3;
        U32                             : 26;
    } bitc;
} GH_ADC_CONTROL_S;

typedef union { /* ADC_IntControl */
    U32 all;
    struct {
        U32 val_lo                      : 10;
        U32                             : 5;
        U32 val_hi                      : 10;
        U32                             : 5;
        U32 en_lo                       : 1;
        U32 en_hi                       : 1;
    } bitc;
} GH_ADC_INTCONTROL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register ADC_AUX_ATOP_REG0 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'ADC_AUX_ATOP_REG0'. */
void GH_ADC_set_AUX_ATOP_REG0(U32 data);
/*! \brief Reads the register 'ADC_AUX_ATOP_REG0'. */
U32  GH_ADC_get_AUX_ATOP_REG0(void);
/*! \brief Writes the bit group 'sar_maxsel' of register 'ADC_AUX_ATOP_REG0'. */
void GH_ADC_set_AUX_ATOP_REG0_sar_maxsel(U8 data);
/*! \brief Reads the bit group 'sar_maxsel' of register 'ADC_AUX_ATOP_REG0'. */
U8   GH_ADC_get_AUX_ATOP_REG0_sar_maxsel(void);
/*! \brief Writes the bit group 'sar_maxnsel' of register 'ADC_AUX_ATOP_REG0'. */
void GH_ADC_set_AUX_ATOP_REG0_sar_maxnsel(U8 data);
/*! \brief Reads the bit group 'sar_maxnsel' of register 'ADC_AUX_ATOP_REG0'. */
U8   GH_ADC_get_AUX_ATOP_REG0_sar_maxnsel(void);
/*! \brief Writes the bit group 'sar_pd' of register 'ADC_AUX_ATOP_REG0'. */
void GH_ADC_set_AUX_ATOP_REG0_sar_pd(U8 data);
/*! \brief Reads the bit group 'sar_pd' of register 'ADC_AUX_ATOP_REG0'. */
U8   GH_ADC_get_AUX_ATOP_REG0_sar_pd(void);
/*! \brief Writes the bit group 'sar_oneshot' of register 'ADC_AUX_ATOP_REG0'. */
void GH_ADC_set_AUX_ATOP_REG0_sar_oneshot(U8 data);
/*! \brief Reads the bit group 'sar_oneshot' of register 'ADC_AUX_ATOP_REG0'. */
U8   GH_ADC_get_AUX_ATOP_REG0_sar_oneshot(void);
/*! \brief Writes the bit group 'sar_freerun' of register 'ADC_AUX_ATOP_REG0'. */
void GH_ADC_set_AUX_ATOP_REG0_sar_freerun(U8 data);
/*! \brief Reads the bit group 'sar_freerun' of register 'ADC_AUX_ATOP_REG0'. */
U8   GH_ADC_get_AUX_ATOP_REG0_sar_freerun(void);
/*! \brief Writes the bit group 'sar_refnsel' of register 'ADC_AUX_ATOP_REG0'. */
void GH_ADC_set_AUX_ATOP_REG0_sar_refnsel(U8 data);
/*! \brief Reads the bit group 'sar_refnsel' of register 'ADC_AUX_ATOP_REG0'. */
U8   GH_ADC_get_AUX_ATOP_REG0_sar_refnsel(void);
/*! \brief Writes the bit group 'sar_refsel' of register 'ADC_AUX_ATOP_REG0'. */
void GH_ADC_set_AUX_ATOP_REG0_sar_refsel(U8 data);
/*! \brief Reads the bit group 'sar_refsel' of register 'ADC_AUX_ATOP_REG0'. */
U8   GH_ADC_get_AUX_ATOP_REG0_sar_refsel(void);
/*! \brief Writes the bit group 'pd_tsi' of register 'ADC_AUX_ATOP_REG0'. */
void GH_ADC_set_AUX_ATOP_REG0_pd_tsi(U8 data);
/*! \brief Reads the bit group 'pd_tsi' of register 'ADC_AUX_ATOP_REG0'. */
U8   GH_ADC_get_AUX_ATOP_REG0_pd_tsi(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_ADC_set_AUX_ATOP_REG0(U32 data)
{
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = data;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,data,data);
    #endif
}
GH_INLINE U32  GH_ADC_get_AUX_ATOP_REG0(void)
{
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return value;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG0_sar_maxsel(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_maxsel = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_maxsel] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG0_sar_maxsel(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_maxsel] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_maxsel;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG0_sar_maxnsel(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_maxnsel = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_maxnsel] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG0_sar_maxnsel(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_maxnsel] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_maxnsel;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG0_sar_pd(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_pd = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_pd] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG0_sar_pd(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_pd] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_pd;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG0_sar_oneshot(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_oneshot = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_oneshot] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG0_sar_oneshot(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_oneshot] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_oneshot;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG0_sar_freerun(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_freerun = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_freerun] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG0_sar_freerun(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_freerun] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_freerun;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG0_sar_refnsel(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_refnsel = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_refnsel] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG0_sar_refnsel(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_refnsel] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_refnsel;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG0_sar_refsel(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_refsel = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_refsel] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG0_sar_refsel(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_refsel] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_refsel;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG0_pd_tsi(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.pd_tsi = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_pd_tsi] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG0_pd_tsi(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_pd_tsi] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.pd_tsi;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ADC_AUX_ATOP_REG1 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'ADC_AUX_ATOP_REG1'. */
void GH_ADC_set_AUX_ATOP_REG1(U32 data);
/*! \brief Reads the register 'ADC_AUX_ATOP_REG1'. */
U32  GH_ADC_get_AUX_ATOP_REG1(void);
/*! \brief Writes the bit group 'i_sar_key' of register 'ADC_AUX_ATOP_REG1'. */
void GH_ADC_set_AUX_ATOP_REG1_i_sar_key(U8 data);
/*! \brief Reads the bit group 'i_sar_key' of register 'ADC_AUX_ATOP_REG1'. */
U8   GH_ADC_get_AUX_ATOP_REG1_i_sar_key(void);
/*! \brief Writes the bit group 'sar_key_pge' of register 'ADC_AUX_ATOP_REG1'. */
void GH_ADC_set_AUX_ATOP_REG1_sar_key_pge(U8 data);
/*! \brief Reads the bit group 'sar_key_pge' of register 'ADC_AUX_ATOP_REG1'. */
U8   GH_ADC_get_AUX_ATOP_REG1_sar_key_pge(void);
/*! \brief Writes the bit group 'sar_key_aie' of register 'ADC_AUX_ATOP_REG1'. */
void GH_ADC_set_AUX_ATOP_REG1_sar_key_aie(U8 data);
/*! \brief Reads the bit group 'sar_key_aie' of register 'ADC_AUX_ATOP_REG1'. */
U8   GH_ADC_get_AUX_ATOP_REG1_sar_key_aie(void);
/*! \brief Writes the bit group 'oen_sar_key' of register 'ADC_AUX_ATOP_REG1'. */
void GH_ADC_set_AUX_ATOP_REG1_oen_sar_key(U8 data);
/*! \brief Reads the bit group 'oen_sar_key' of register 'ADC_AUX_ATOP_REG1'. */
U8   GH_ADC_get_AUX_ATOP_REG1_oen_sar_key(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_ADC_set_AUX_ATOP_REG1(U32 data)
{
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG1 = data;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG1] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,data,data);
    #endif
}
GH_INLINE U32  GH_ADC_get_AUX_ATOP_REG1(void)
{
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG1);

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG1] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,value);
    #endif
    return value;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG1_i_sar_key(U8 data)
{
    GH_ADC_AUX_ATOP_REG1_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG1;
    d.bitc.i_sar_key = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG1 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG1_i_sar_key] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG1_i_sar_key(void)
{
    GH_ADC_AUX_ATOP_REG1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG1);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG1_i_sar_key] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,value);
    #endif
    return tmp_value.bitc.i_sar_key;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG1_sar_key_pge(U8 data)
{
    GH_ADC_AUX_ATOP_REG1_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG1;
    d.bitc.sar_key_pge = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG1 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG1_sar_key_pge] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG1_sar_key_pge(void)
{
    GH_ADC_AUX_ATOP_REG1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG1);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG1_sar_key_pge] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,value);
    #endif
    return tmp_value.bitc.sar_key_pge;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG1_sar_key_aie(U8 data)
{
    GH_ADC_AUX_ATOP_REG1_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG1;
    d.bitc.sar_key_aie = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG1 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG1_sar_key_aie] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG1_sar_key_aie(void)
{
    GH_ADC_AUX_ATOP_REG1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG1);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG1_sar_key_aie] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,value);
    #endif
    return tmp_value.bitc.sar_key_aie;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG1_oen_sar_key(U8 data)
{
    GH_ADC_AUX_ATOP_REG1_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG1;
    d.bitc.oen_sar_key = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG1 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG1_oen_sar_key] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG1_oen_sar_key(void)
{
    GH_ADC_AUX_ATOP_REG1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG1);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG1_oen_sar_key] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,value);
    #endif
    return tmp_value.bitc.oen_sar_key;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ADC_AUX_ATOP_REG2 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'ADC_AUX_ATOP_REG2'. */
void GH_ADC_set_AUX_ATOP_REG2(U32 data);
/*! \brief Reads the register 'ADC_AUX_ATOP_REG2'. */
U32  GH_ADC_get_AUX_ATOP_REG2(void);
/*! \brief Writes the bit group 'sar_test' of register 'ADC_AUX_ATOP_REG2'. */
void GH_ADC_set_AUX_ATOP_REG2_sar_test(U8 data);
/*! \brief Reads the bit group 'sar_test' of register 'ADC_AUX_ATOP_REG2'. */
U8   GH_ADC_get_AUX_ATOP_REG2_sar_test(void);
/*! \brief Writes the bit group 'TSI_RCTRL12' of register 'ADC_AUX_ATOP_REG2'. */
void GH_ADC_set_AUX_ATOP_REG2_TSI_RCTRL12(U8 data);
/*! \brief Reads the bit group 'TSI_RCTRL12' of register 'ADC_AUX_ATOP_REG2'. */
U8   GH_ADC_get_AUX_ATOP_REG2_TSI_RCTRL12(void);
/*! \brief Writes the bit group 'ENZYR' of register 'ADC_AUX_ATOP_REG2'. */
void GH_ADC_set_AUX_ATOP_REG2_ENZYR(U8 data);
/*! \brief Reads the bit group 'ENZYR' of register 'ADC_AUX_ATOP_REG2'. */
U8   GH_ADC_get_AUX_ATOP_REG2_ENZYR(void);
/*! \brief Writes the bit group 'ENZYP' of register 'ADC_AUX_ATOP_REG2'. */
void GH_ADC_set_AUX_ATOP_REG2_ENZYP(U8 data);
/*! \brief Reads the bit group 'ENZYP' of register 'ADC_AUX_ATOP_REG2'. */
U8   GH_ADC_get_AUX_ATOP_REG2_ENZYP(void);
/*! \brief Writes the bit group 'ENZXR' of register 'ADC_AUX_ATOP_REG2'. */
void GH_ADC_set_AUX_ATOP_REG2_ENZXR(U8 data);
/*! \brief Reads the bit group 'ENZXR' of register 'ADC_AUX_ATOP_REG2'. */
U8   GH_ADC_get_AUX_ATOP_REG2_ENZXR(void);
/*! \brief Writes the bit group 'ENZXP' of register 'ADC_AUX_ATOP_REG2'. */
void GH_ADC_set_AUX_ATOP_REG2_ENZXP(U8 data);
/*! \brief Reads the bit group 'ENZXP' of register 'ADC_AUX_ATOP_REG2'. */
U8   GH_ADC_get_AUX_ATOP_REG2_ENZXP(void);
/*! \brief Writes the bit group 'ENYN' of register 'ADC_AUX_ATOP_REG2'. */
void GH_ADC_set_AUX_ATOP_REG2_ENYN(U8 data);
/*! \brief Reads the bit group 'ENYN' of register 'ADC_AUX_ATOP_REG2'. */
U8   GH_ADC_get_AUX_ATOP_REG2_ENYN(void);
/*! \brief Writes the bit group 'ENXN' of register 'ADC_AUX_ATOP_REG2'. */
void GH_ADC_set_AUX_ATOP_REG2_ENXN(U8 data);
/*! \brief Reads the bit group 'ENXN' of register 'ADC_AUX_ATOP_REG2'. */
U8   GH_ADC_get_AUX_ATOP_REG2_ENXN(void);
/*! \brief Writes the bit group 'ENZOINT' of register 'ADC_AUX_ATOP_REG2'. */
void GH_ADC_set_AUX_ATOP_REG2_ENZOINT(U8 data);
/*! \brief Reads the bit group 'ENZOINT' of register 'ADC_AUX_ATOP_REG2'. */
U8   GH_ADC_get_AUX_ATOP_REG2_ENZOINT(void);
/*! \brief Writes the bit group 'TSI_IS' of register 'ADC_AUX_ATOP_REG2'. */
void GH_ADC_set_AUX_ATOP_REG2_TSI_IS(U8 data);
/*! \brief Reads the bit group 'TSI_IS' of register 'ADC_AUX_ATOP_REG2'. */
U8   GH_ADC_get_AUX_ATOP_REG2_TSI_IS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_ADC_set_AUX_ATOP_REG2(U32 data)
{
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = data;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,data,data);
    #endif
}
GH_INLINE U32  GH_ADC_get_AUX_ATOP_REG2(void)
{
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return value;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG2_sar_test(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.sar_test = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_sar_test] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG2_sar_test(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_sar_test] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.sar_test;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG2_TSI_RCTRL12(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.tsi_rctrl12 = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_TSI_RCTRL12] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG2_TSI_RCTRL12(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_TSI_RCTRL12] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.tsi_rctrl12;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG2_ENZYR(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enzyr = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENZYR] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG2_ENZYR(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENZYR] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enzyr;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG2_ENZYP(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enzyp = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENZYP] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG2_ENZYP(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENZYP] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enzyp;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG2_ENZXR(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enzxr = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENZXR] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG2_ENZXR(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENZXR] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enzxr;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG2_ENZXP(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enzxp = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENZXP] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG2_ENZXP(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENZXP] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enzxp;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG2_ENYN(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enyn = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENYN] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG2_ENYN(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENYN] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enyn;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG2_ENXN(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enxn = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENXN] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG2_ENXN(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENXN] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enxn;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG2_ENZOINT(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enzoint = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENZOINT] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG2_ENZOINT(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENZOINT] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enzoint;
}
GH_INLINE void GH_ADC_set_AUX_ATOP_REG2_TSI_IS(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.tsi_is = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_TSI_IS] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_AUX_ATOP_REG2_TSI_IS(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_TSI_IS] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.tsi_is;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ADC_Control (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'ADC_Control'. */
void GH_ADC_set_Control(U32 data);
/*! \brief Reads the register 'ADC_Control'. */
U32  GH_ADC_get_Control(void);
/*! \brief Writes the bit group 'status' of register 'ADC_Control'. */
void GH_ADC_set_Control_status(U8 data);
/*! \brief Reads the bit group 'status' of register 'ADC_Control'. */
U8   GH_ADC_get_Control_status(void);
/*! \brief Writes the bit group 'start' of register 'ADC_Control'. */
void GH_ADC_set_Control_start(U8 data);
/*! \brief Reads the bit group 'start' of register 'ADC_Control'. */
U8   GH_ADC_get_Control_start(void);
/*! \brief Writes the bit group 'channel' of register 'ADC_Control'. */
void GH_ADC_set_Control_channel(U8 data);
/*! \brief Reads the bit group 'channel' of register 'ADC_Control'. */
U8   GH_ADC_get_Control_channel(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_ADC_set_Control(U32 data)
{
    *(volatile U32 *)REG_ADC_CONTROL = data;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_Control] <-- 0x%08x\n",
                        REG_ADC_CONTROL,data,data);
    #endif
}
GH_INLINE U32  GH_ADC_get_Control(void)
{
    U32 value = (*(volatile U32 *)REG_ADC_CONTROL);

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_Control] --> 0x%08x\n",
                        REG_ADC_CONTROL,value);
    #endif
    return value;
}
GH_INLINE void GH_ADC_set_Control_status(U8 data)
{
    GH_ADC_CONTROL_S d;
    d.all = *(volatile U32 *)REG_ADC_CONTROL;
    d.bitc.status = data;
    *(volatile U32 *)REG_ADC_CONTROL = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_Control_status] <-- 0x%08x\n",
                        REG_ADC_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_Control_status(void)
{
    GH_ADC_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_CONTROL);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_Control_status] --> 0x%08x\n",
                        REG_ADC_CONTROL,value);
    #endif
    return tmp_value.bitc.status;
}
GH_INLINE void GH_ADC_set_Control_start(U8 data)
{
    GH_ADC_CONTROL_S d;
    d.all = *(volatile U32 *)REG_ADC_CONTROL;
    d.bitc.start = data;
    *(volatile U32 *)REG_ADC_CONTROL = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_Control_start] <-- 0x%08x\n",
                        REG_ADC_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_Control_start(void)
{
    GH_ADC_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_CONTROL);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_Control_start] --> 0x%08x\n",
                        REG_ADC_CONTROL,value);
    #endif
    return tmp_value.bitc.start;
}
GH_INLINE void GH_ADC_set_Control_channel(U8 data)
{
    GH_ADC_CONTROL_S d;
    d.all = *(volatile U32 *)REG_ADC_CONTROL;
    d.bitc.channel = data;
    *(volatile U32 *)REG_ADC_CONTROL = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_Control_channel] <-- 0x%08x\n",
                        REG_ADC_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_Control_channel(void)
{
    GH_ADC_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_CONTROL);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_Control_channel] --> 0x%08x\n",
                        REG_ADC_CONTROL,value);
    #endif
    return tmp_value.bitc.channel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ADC_ReadData (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'ADC_ReadData'. */
U32  GH_ADC_get_ReadData(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_ADC_get_ReadData(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_ADC_READDATA + index * FIO_MOFFSET(ADC,0x00000004)));

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_ReadData] --> 0x%08x\n",
                        (REG_ADC_READDATA + index * FIO_MOFFSET(ADC,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ADC_Enable (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'ADC_Enable'. */
void GH_ADC_set_Enable(U32 data);
/*! \brief Reads the register 'ADC_Enable'. */
U32  GH_ADC_get_Enable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_ADC_set_Enable(U32 data)
{
    *(volatile U32 *)REG_ADC_ENABLE = data;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_Enable] <-- 0x%08x\n",
                        REG_ADC_ENABLE,data,data);
    #endif
}
GH_INLINE U32  GH_ADC_get_Enable(void)
{
    U32 value = (*(volatile U32 *)REG_ADC_ENABLE);

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_Enable] --> 0x%08x\n",
                        REG_ADC_ENABLE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ADC_IntControl (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'ADC_IntControl'. */
void GH_ADC_set_IntControl(U8 index, U32 data);
/*! \brief Reads the register 'ADC_IntControl'. */
U32  GH_ADC_get_IntControl(U8 index);
/*! \brief Writes the bit group 'val_lo' of register 'ADC_IntControl'. */
void GH_ADC_set_IntControl_val_lo(U8 index, U16 data);
/*! \brief Reads the bit group 'val_lo' of register 'ADC_IntControl'. */
U16  GH_ADC_get_IntControl_val_lo(U8 index);
/*! \brief Writes the bit group 'val_hi' of register 'ADC_IntControl'. */
void GH_ADC_set_IntControl_val_hi(U8 index, U16 data);
/*! \brief Reads the bit group 'val_hi' of register 'ADC_IntControl'. */
U16  GH_ADC_get_IntControl_val_hi(U8 index);
/*! \brief Writes the bit group 'en_lo' of register 'ADC_IntControl'. */
void GH_ADC_set_IntControl_en_lo(U8 index, U8 data);
/*! \brief Reads the bit group 'en_lo' of register 'ADC_IntControl'. */
U8   GH_ADC_get_IntControl_en_lo(U8 index);
/*! \brief Writes the bit group 'en_hi' of register 'ADC_IntControl'. */
void GH_ADC_set_IntControl_en_hi(U8 index, U8 data);
/*! \brief Reads the bit group 'en_hi' of register 'ADC_IntControl'. */
U8   GH_ADC_get_IntControl_en_hi(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_ADC_set_IntControl(U8 index, U32 data)
{
    *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)) = data;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_IntControl] <-- 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_ADC_get_IntControl(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)));

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_IntControl] --> 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),value);
    #endif
    return value;
}
GH_INLINE void GH_ADC_set_IntControl_val_lo(U8 index, U16 data)
{
    GH_ADC_INTCONTROL_S d;
    d.all = *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004));
    d.bitc.val_lo = data;
    *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)) = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_IntControl_val_lo] <-- 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),d.all,d.all);
    #endif
}
GH_INLINE U16  GH_ADC_get_IntControl_val_lo(U8 index)
{
    GH_ADC_INTCONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)));

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_IntControl_val_lo] --> 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),value);
    #endif
    return tmp_value.bitc.val_lo;
}
GH_INLINE void GH_ADC_set_IntControl_val_hi(U8 index, U16 data)
{
    GH_ADC_INTCONTROL_S d;
    d.all = *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004));
    d.bitc.val_hi = data;
    *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)) = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_IntControl_val_hi] <-- 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),d.all,d.all);
    #endif
}
GH_INLINE U16  GH_ADC_get_IntControl_val_hi(U8 index)
{
    GH_ADC_INTCONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)));

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_IntControl_val_hi] --> 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),value);
    #endif
    return tmp_value.bitc.val_hi;
}
GH_INLINE void GH_ADC_set_IntControl_en_lo(U8 index, U8 data)
{
    GH_ADC_INTCONTROL_S d;
    d.all = *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004));
    d.bitc.en_lo = data;
    *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)) = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_IntControl_en_lo] <-- 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_IntControl_en_lo(U8 index)
{
    GH_ADC_INTCONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)));

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_IntControl_en_lo] --> 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),value);
    #endif
    return tmp_value.bitc.en_lo;
}
GH_INLINE void GH_ADC_set_IntControl_en_hi(U8 index, U8 data)
{
    GH_ADC_INTCONTROL_S d;
    d.all = *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004));
    d.bitc.en_hi = data;
    *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)) = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_IntControl_en_hi] <-- 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_ADC_get_IntControl_en_hi(U8 index)
{
    GH_ADC_INTCONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)));

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_IntControl_en_hi] --> 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),value);
    #endif
    return tmp_value.bitc.en_hi;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_ADC_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_ADC_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

