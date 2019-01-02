/*!
*******************************************************************************
**
** \file      gh_pwm.h
**
** \brief     Pulse Width Modulator.
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
#ifndef _GH_PWM_H
#define _GH_PWM_H

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

#define GH_PWM_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_PWM_DEBUG_PRINT_FUNCTION printk
#else
#define GH_PWM_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_PWM_ENABLE_DEBUG_PRINT
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
#define REG_PWM_ENABLE                                      FIO_ADDRESS(PWM,0xA000A000) /* read/write */
#define REG_PWM_CONTROL0                                    FIO_ADDRESS(PWM,0xA000A004) /* read/write */
#define REG_PWM_CONTROL1                                    FIO_ADDRESS(PWM,0xA000A008) /* read/write */
#define REG_PWM_MODE                                        FIO_ADDRESS(PWM,0xA000A00C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* PWM_Enable */
    U32 all;
    struct {
        U32 enb                         : 1;
        U32                             : 31;
    } bitc;
} GH_PWM_ENABLE_S;

typedef union { /* PWM_Control0 */
    U32 all;
    struct {
        U32 highcnt                     : 16;
        U32 lowcnt                      : 16;
    } bitc;
} GH_PWM_CONTROL0_S;

typedef union { /* PWM_Control1 */
    U32 all;
    struct {
        U32 highcnt                     : 16;
        U32 lowcnt                      : 16;
    } bitc;
} GH_PWM_CONTROL1_S;

typedef union { /* PWM_Mode */
    U32 all;
    struct {
        U32 divider                     : 10;
        U32 mode                        : 1;
        U32                             : 21;
    } bitc;
} GH_PWM_MODE_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register PWM_Enable (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PWM_Enable'. */
void GH_PWM_set_Enable(U8 index, U32 data);
/*! \brief Reads the register 'PWM_Enable'. */
U32  GH_PWM_get_Enable(U8 index);
/*! \brief Writes the bit group 'enb' of register 'PWM_Enable'. */
void GH_PWM_set_Enable_enb(U8 index, U8 data);
/*! \brief Reads the bit group 'enb' of register 'PWM_Enable'. */
U8   GH_PWM_get_Enable_enb(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PWM_set_Enable(U8 index, U32 data)
{
    *(volatile U32 *)(REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)) = data;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Enable] <-- 0x%08x\n",
                        (REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_PWM_get_Enable(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)));

    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Enable] --> 0x%08x\n",
                        (REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return value;
}
GH_INLINE void GH_PWM_set_Enable_enb(U8 index, U8 data)
{
    GH_PWM_ENABLE_S d;
    d.all = *(volatile U32 *)(REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.enb = data;
    *(volatile U32 *)(REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Enable_enb] <-- 0x%08x\n",
                        (REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PWM_get_Enable_enb(U8 index)
{
    GH_PWM_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Enable_enb] --> 0x%08x\n",
                        (REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.enb;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PWM_Control0 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PWM_Control0'. */
void GH_PWM_set_Control0(U8 index, U32 data);
/*! \brief Reads the register 'PWM_Control0'. */
U32  GH_PWM_get_Control0(U8 index);
/*! \brief Writes the bit group 'HighCnt' of register 'PWM_Control0'. */
void GH_PWM_set_Control0_HighCnt(U8 index, U16 data);
/*! \brief Reads the bit group 'HighCnt' of register 'PWM_Control0'. */
U16  GH_PWM_get_Control0_HighCnt(U8 index);
/*! \brief Writes the bit group 'LowCnt' of register 'PWM_Control0'. */
void GH_PWM_set_Control0_LowCnt(U8 index, U16 data);
/*! \brief Reads the bit group 'LowCnt' of register 'PWM_Control0'. */
U16  GH_PWM_get_Control0_LowCnt(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PWM_set_Control0(U8 index, U32 data)
{
    *(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)) = data;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Control0] <-- 0x%08x\n",
                        (REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_PWM_get_Control0(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)));

    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Control0] --> 0x%08x\n",
                        (REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return value;
}
GH_INLINE void GH_PWM_set_Control0_HighCnt(U8 index, U16 data)
{
    GH_PWM_CONTROL0_S d;
    d.all = *(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.highcnt = data;
    *(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Control0_HighCnt] <-- 0x%08x\n",
                        (REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PWM_get_Control0_HighCnt(U8 index)
{
    GH_PWM_CONTROL0_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Control0_HighCnt] --> 0x%08x\n",
                        (REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.highcnt;
}
GH_INLINE void GH_PWM_set_Control0_LowCnt(U8 index, U16 data)
{
    GH_PWM_CONTROL0_S d;
    d.all = *(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.lowcnt = data;
    *(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Control0_LowCnt] <-- 0x%08x\n",
                        (REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PWM_get_Control0_LowCnt(U8 index)
{
    GH_PWM_CONTROL0_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Control0_LowCnt] --> 0x%08x\n",
                        (REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.lowcnt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PWM_Control1 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PWM_Control1'. */
void GH_PWM_set_Control1(U8 index, U32 data);
/*! \brief Reads the register 'PWM_Control1'. */
U32  GH_PWM_get_Control1(U8 index);
/*! \brief Writes the bit group 'HighCnt' of register 'PWM_Control1'. */
void GH_PWM_set_Control1_HighCnt(U8 index, U16 data);
/*! \brief Reads the bit group 'HighCnt' of register 'PWM_Control1'. */
U16  GH_PWM_get_Control1_HighCnt(U8 index);
/*! \brief Writes the bit group 'LowCnt' of register 'PWM_Control1'. */
void GH_PWM_set_Control1_LowCnt(U8 index, U16 data);
/*! \brief Reads the bit group 'LowCnt' of register 'PWM_Control1'. */
U16  GH_PWM_get_Control1_LowCnt(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PWM_set_Control1(U8 index, U32 data)
{
    *(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)) = data;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Control1] <-- 0x%08x\n",
                        (REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_PWM_get_Control1(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)));

    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Control1] --> 0x%08x\n",
                        (REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return value;
}
GH_INLINE void GH_PWM_set_Control1_HighCnt(U8 index, U16 data)
{
    GH_PWM_CONTROL1_S d;
    d.all = *(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.highcnt = data;
    *(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Control1_HighCnt] <-- 0x%08x\n",
                        (REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PWM_get_Control1_HighCnt(U8 index)
{
    GH_PWM_CONTROL1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Control1_HighCnt] --> 0x%08x\n",
                        (REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.highcnt;
}
GH_INLINE void GH_PWM_set_Control1_LowCnt(U8 index, U16 data)
{
    GH_PWM_CONTROL1_S d;
    d.all = *(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.lowcnt = data;
    *(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Control1_LowCnt] <-- 0x%08x\n",
                        (REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PWM_get_Control1_LowCnt(U8 index)
{
    GH_PWM_CONTROL1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Control1_LowCnt] --> 0x%08x\n",
                        (REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.lowcnt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PWM_Mode (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PWM_Mode'. */
void GH_PWM_set_Mode(U8 index, U32 data);
/*! \brief Reads the register 'PWM_Mode'. */
U32  GH_PWM_get_Mode(U8 index);
/*! \brief Writes the bit group 'divider' of register 'PWM_Mode'. */
void GH_PWM_set_Mode_divider(U8 index, U16 data);
/*! \brief Reads the bit group 'divider' of register 'PWM_Mode'. */
U16  GH_PWM_get_Mode_divider(U8 index);
/*! \brief Writes the bit group 'mode' of register 'PWM_Mode'. */
void GH_PWM_set_Mode_mode(U8 index, U8 data);
/*! \brief Reads the bit group 'mode' of register 'PWM_Mode'. */
U8   GH_PWM_get_Mode_mode(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PWM_set_Mode(U8 index, U32 data)
{
    GH_PWM_MODE_S d;
    d.all = (*(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)));
    d.bitc.mode = data;
    *(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Mode] <-- 0x%08x\n",
                        (REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_PWM_get_Mode(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)));

    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Mode] --> 0x%08x\n",
                        (REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return value;
}
GH_INLINE void GH_PWM_set_Mode_divider(U8 index, U16 data)
{
    GH_PWM_MODE_S d;
    d.all = *(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.divider = data;
    *(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Mode_divider] <-- 0x%08x\n",
                        (REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PWM_get_Mode_divider(U8 index)
{
    GH_PWM_MODE_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Mode_divider] --> 0x%08x\n",
                        (REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.divider;
}
GH_INLINE void GH_PWM_set_Mode_mode(U8 index, U8 data)
{
    GH_PWM_MODE_S d;
    d.all = *(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.mode = data;
    *(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Mode_mode] <-- 0x%08x\n",
                        (REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PWM_get_Mode_mode(U8 index)
{
    GH_PWM_MODE_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Mode_mode] --> 0x%08x\n",
                        (REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_PWM_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_PWM_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

