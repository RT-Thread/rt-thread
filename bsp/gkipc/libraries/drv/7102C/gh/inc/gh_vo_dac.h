/*!
*******************************************************************************
**
** \file      gh_vo_dac.h
**
** \brief     VDAC Registers.
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
#ifndef _GH_VO_DAC_H
#define _GH_VO_DAC_H

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

#define GH_VO_DAC_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VO_DAC_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VO_DAC_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VO_DAC_ENABLE_DEBUG_PRINT
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
#define REG_VO_DAC_EN_IDAC_X                                FIO_ADDRESS(VO_DAC,0x90022680) /* read/write */
#define REG_VO_DAC_MODE_SD                                  FIO_ADDRESS(VO_DAC,0x90022681) /* read/write */
#define REG_VO_DAC_IDAC_IHALF_SD                            FIO_ADDRESS(VO_DAC,0x90022682) /* read/write */
#define REG_VO_DAC_GCR_LEVEL                                FIO_ADDRESS(VO_DAC,0x90022684) /* read/write */
#define REG_VO_DAC_IDA_IQUART_SD                            FIO_ADDRESS(VO_DAC,0x90022685) /* read/write */
#define REG_VO_DAC_GCR_IDAC_GAINX                           FIO_ADDRESS(VO_DAC,0x90022686) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_DAC_EN_IDAC_X */
    U8 all;
    struct {
        U8 enable                       : 1;
        U8                              : 7;
    } bitc;
} GH_VO_DAC_EN_IDAC_X_S;

typedef union { /* VO_DAC_MODE_SD */
    U8 all;
    struct {
        U8 mode                         : 1;
        U8                              : 7;
    } bitc;
} GH_VO_DAC_MODE_SD_S;

typedef union { /* VO_DAC_IDAC_IHALF_SD */
    U8 all;
    struct {
        U8 half                         : 1;
        U8                              : 7;
    } bitc;
} GH_VO_DAC_IDAC_IHALF_SD_S;

typedef union { /* VO_DAC_GCR_LEVEL */
    U8 all;
    struct {
        U8 level                        : 2;
        U8                              : 6;
    } bitc;
} GH_VO_DAC_GCR_LEVEL_S;

typedef union { /* VO_DAC_IDA_IQUART_SD */
    U8 all;
    struct {
        U8 quart                        : 1;
        U8                              : 7;
    } bitc;
} GH_VO_DAC_IDA_IQUART_SD_S;

typedef union { /* VO_DAC_GCR_IDAC_GAINX */
    U8 all;
    struct {
        U8 gain                         : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DAC_GCR_IDAC_GAINX_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VO_DAC_EN_IDAC_X (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DAC_EN_IDAC_X'. */
void GH_VO_DAC_set_EN_IDAC_X(U8 data);
/*! \brief Reads the register 'VO_DAC_EN_IDAC_X'. */
U8   GH_VO_DAC_get_EN_IDAC_X(void);
/*! \brief Writes the bit group 'enable' of register 'VO_DAC_EN_IDAC_X'. */
void GH_VO_DAC_set_EN_IDAC_X_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_DAC_EN_IDAC_X'. */
U8   GH_VO_DAC_get_EN_IDAC_X_enable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DAC_set_EN_IDAC_X(U8 data)
{
    *(volatile U8 *)REG_VO_DAC_EN_IDAC_X = data;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_EN_IDAC_X] <-- 0x%08x\n",
                        REG_VO_DAC_EN_IDAC_X,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DAC_get_EN_IDAC_X(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DAC_EN_IDAC_X);

    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_EN_IDAC_X] --> 0x%08x\n",
                        REG_VO_DAC_EN_IDAC_X,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DAC_set_EN_IDAC_X_enable(U8 data)
{
    GH_VO_DAC_EN_IDAC_X_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_EN_IDAC_X;
    d.bitc.enable = data;
    *(volatile U8 *)REG_VO_DAC_EN_IDAC_X = d.all;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_EN_IDAC_X_enable] <-- 0x%08x\n",
                        REG_VO_DAC_EN_IDAC_X,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DAC_get_EN_IDAC_X_enable(void)
{
    GH_VO_DAC_EN_IDAC_X_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_EN_IDAC_X);

    tmp_value.all = value;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_EN_IDAC_X_enable] --> 0x%08x\n",
                        REG_VO_DAC_EN_IDAC_X,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DAC_MODE_SD (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DAC_MODE_SD'. */
void GH_VO_DAC_set_MODE_SD(U8 data);
/*! \brief Reads the register 'VO_DAC_MODE_SD'. */
U8   GH_VO_DAC_get_MODE_SD(void);
/*! \brief Writes the bit group 'mode' of register 'VO_DAC_MODE_SD'. */
void GH_VO_DAC_set_MODE_SD_mode(U8 data);
/*! \brief Reads the bit group 'mode' of register 'VO_DAC_MODE_SD'. */
U8   GH_VO_DAC_get_MODE_SD_mode(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DAC_set_MODE_SD(U8 data)
{
    *(volatile U8 *)REG_VO_DAC_MODE_SD = data;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_MODE_SD] <-- 0x%08x\n",
                        REG_VO_DAC_MODE_SD,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DAC_get_MODE_SD(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DAC_MODE_SD);

    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_MODE_SD] --> 0x%08x\n",
                        REG_VO_DAC_MODE_SD,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DAC_set_MODE_SD_mode(U8 data)
{
    GH_VO_DAC_MODE_SD_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_MODE_SD;
    d.bitc.mode = data;
    *(volatile U8 *)REG_VO_DAC_MODE_SD = d.all;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_MODE_SD_mode] <-- 0x%08x\n",
                        REG_VO_DAC_MODE_SD,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DAC_get_MODE_SD_mode(void)
{
    GH_VO_DAC_MODE_SD_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_MODE_SD);

    tmp_value.all = value;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_MODE_SD_mode] --> 0x%08x\n",
                        REG_VO_DAC_MODE_SD,value);
    #endif
    return tmp_value.bitc.mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DAC_IDAC_IHALF_SD (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DAC_IDAC_IHALF_SD'. */
void GH_VO_DAC_set_IDAC_IHALF_SD(U8 data);
/*! \brief Reads the register 'VO_DAC_IDAC_IHALF_SD'. */
U8   GH_VO_DAC_get_IDAC_IHALF_SD(void);
/*! \brief Writes the bit group 'half' of register 'VO_DAC_IDAC_IHALF_SD'. */
void GH_VO_DAC_set_IDAC_IHALF_SD_half(U8 data);
/*! \brief Reads the bit group 'half' of register 'VO_DAC_IDAC_IHALF_SD'. */
U8   GH_VO_DAC_get_IDAC_IHALF_SD_half(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DAC_set_IDAC_IHALF_SD(U8 data)
{
    *(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD = data;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_IDAC_IHALF_SD] <-- 0x%08x\n",
                        REG_VO_DAC_IDAC_IHALF_SD,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DAC_get_IDAC_IHALF_SD(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD);

    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_IDAC_IHALF_SD] --> 0x%08x\n",
                        REG_VO_DAC_IDAC_IHALF_SD,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DAC_set_IDAC_IHALF_SD_half(U8 data)
{
    GH_VO_DAC_IDAC_IHALF_SD_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD;
    d.bitc.half = data;
    *(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD = d.all;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_IDAC_IHALF_SD_half] <-- 0x%08x\n",
                        REG_VO_DAC_IDAC_IHALF_SD,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DAC_get_IDAC_IHALF_SD_half(void)
{
    GH_VO_DAC_IDAC_IHALF_SD_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_IDAC_IHALF_SD);

    tmp_value.all = value;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_IDAC_IHALF_SD_half] --> 0x%08x\n",
                        REG_VO_DAC_IDAC_IHALF_SD,value);
    #endif
    return tmp_value.bitc.half;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DAC_GCR_LEVEL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DAC_GCR_LEVEL'. */
void GH_VO_DAC_set_GCR_LEVEL(U8 data);
/*! \brief Reads the register 'VO_DAC_GCR_LEVEL'. */
U8   GH_VO_DAC_get_GCR_LEVEL(void);
/*! \brief Writes the bit group 'level' of register 'VO_DAC_GCR_LEVEL'. */
void GH_VO_DAC_set_GCR_LEVEL_level(U8 data);
/*! \brief Reads the bit group 'level' of register 'VO_DAC_GCR_LEVEL'. */
U8   GH_VO_DAC_get_GCR_LEVEL_level(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DAC_set_GCR_LEVEL(U8 data)
{
    *(volatile U8 *)REG_VO_DAC_GCR_LEVEL = data;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_GCR_LEVEL] <-- 0x%08x\n",
                        REG_VO_DAC_GCR_LEVEL,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DAC_get_GCR_LEVEL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DAC_GCR_LEVEL);

    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_GCR_LEVEL] --> 0x%08x\n",
                        REG_VO_DAC_GCR_LEVEL,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DAC_set_GCR_LEVEL_level(U8 data)
{
    GH_VO_DAC_GCR_LEVEL_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_GCR_LEVEL;
    d.bitc.level = data;
    *(volatile U8 *)REG_VO_DAC_GCR_LEVEL = d.all;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_GCR_LEVEL_level] <-- 0x%08x\n",
                        REG_VO_DAC_GCR_LEVEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DAC_get_GCR_LEVEL_level(void)
{
    GH_VO_DAC_GCR_LEVEL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_GCR_LEVEL);

    tmp_value.all = value;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_GCR_LEVEL_level] --> 0x%08x\n",
                        REG_VO_DAC_GCR_LEVEL,value);
    #endif
    return tmp_value.bitc.level;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DAC_IDA_IQUART_SD (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DAC_IDA_IQUART_SD'. */
void GH_VO_DAC_set_IDA_IQUART_SD(U8 data);
/*! \brief Reads the register 'VO_DAC_IDA_IQUART_SD'. */
U8   GH_VO_DAC_get_IDA_IQUART_SD(void);
/*! \brief Writes the bit group 'quart' of register 'VO_DAC_IDA_IQUART_SD'. */
void GH_VO_DAC_set_IDA_IQUART_SD_quart(U8 data);
/*! \brief Reads the bit group 'quart' of register 'VO_DAC_IDA_IQUART_SD'. */
U8   GH_VO_DAC_get_IDA_IQUART_SD_quart(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DAC_set_IDA_IQUART_SD(U8 data)
{
    *(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD = data;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_IDA_IQUART_SD] <-- 0x%08x\n",
                        REG_VO_DAC_IDA_IQUART_SD,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DAC_get_IDA_IQUART_SD(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD);

    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_IDA_IQUART_SD] --> 0x%08x\n",
                        REG_VO_DAC_IDA_IQUART_SD,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DAC_set_IDA_IQUART_SD_quart(U8 data)
{
    GH_VO_DAC_IDA_IQUART_SD_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD;
    d.bitc.quart = data;
    *(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD = d.all;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_IDA_IQUART_SD_quart] <-- 0x%08x\n",
                        REG_VO_DAC_IDA_IQUART_SD,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DAC_get_IDA_IQUART_SD_quart(void)
{
    GH_VO_DAC_IDA_IQUART_SD_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_IDA_IQUART_SD);

    tmp_value.all = value;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_IDA_IQUART_SD_quart] --> 0x%08x\n",
                        REG_VO_DAC_IDA_IQUART_SD,value);
    #endif
    return tmp_value.bitc.quart;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DAC_GCR_IDAC_GAINX (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DAC_GCR_IDAC_GAINX'. */
void GH_VO_DAC_set_GCR_IDAC_GAINX(U8 data);
/*! \brief Reads the register 'VO_DAC_GCR_IDAC_GAINX'. */
U8   GH_VO_DAC_get_GCR_IDAC_GAINX(void);
/*! \brief Writes the bit group 'gain' of register 'VO_DAC_GCR_IDAC_GAINX'. */
void GH_VO_DAC_set_GCR_IDAC_GAINX_gain(U8 data);
/*! \brief Reads the bit group 'gain' of register 'VO_DAC_GCR_IDAC_GAINX'. */
U8   GH_VO_DAC_get_GCR_IDAC_GAINX_gain(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DAC_set_GCR_IDAC_GAINX(U8 data)
{
    *(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX = data;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_GCR_IDAC_GAINX] <-- 0x%08x\n",
                        REG_VO_DAC_GCR_IDAC_GAINX,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DAC_get_GCR_IDAC_GAINX(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX);

    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_GCR_IDAC_GAINX] --> 0x%08x\n",
                        REG_VO_DAC_GCR_IDAC_GAINX,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DAC_set_GCR_IDAC_GAINX_gain(U8 data)
{
    GH_VO_DAC_GCR_IDAC_GAINX_S d;
    d.all = *(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX;
    d.bitc.gain = data;
    *(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX = d.all;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DAC_set_GCR_IDAC_GAINX_gain] <-- 0x%08x\n",
                        REG_VO_DAC_GCR_IDAC_GAINX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DAC_get_GCR_IDAC_GAINX_gain(void)
{
    GH_VO_DAC_GCR_IDAC_GAINX_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DAC_GCR_IDAC_GAINX);

    tmp_value.all = value;
    #if GH_VO_DAC_ENABLE_DEBUG_PRINT
    GH_VO_DAC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DAC_get_GCR_IDAC_GAINX_gain] --> 0x%08x\n",
                        REG_VO_DAC_GCR_IDAC_GAINX,value);
    #endif
    return tmp_value.bitc.gain;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_DAC_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_DAC_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

