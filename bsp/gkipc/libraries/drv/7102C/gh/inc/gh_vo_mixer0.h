/*!
*******************************************************************************
**
** \file      gh_vo_mixer0.h
**
** \brief     VO Mixer A access function.
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
#ifndef _GH_VO_MIXER0_H
#define _GH_VO_MIXER0_H

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

#define GH_VO_MIXER0_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VO_MIXER0_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VO_MIXER0_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
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
#define REG_VO_MIXER0_CONTROL                               FIO_ADDRESS(VO_MIXER0,0x90004200) /* read/write */
#define REG_VO_MIXER0_STATUS                                FIO_ADDRESS(VO_MIXER0,0x90004204) /* read */
#define REG_VO_MIXER0_ACTIVE_SIZE                           FIO_ADDRESS(VO_MIXER0,0x90004208) /* read/write */
#define REG_VO_MIXER0_VIDEO_START                           FIO_ADDRESS(VO_MIXER0,0x9000420C) /* read/write */
#define REG_VO_MIXER0_VIDEO_END                             FIO_ADDRESS(VO_MIXER0,0x90004210) /* read/write */
#define REG_VO_MIXER0_OSD_START                             FIO_ADDRESS(VO_MIXER0,0x9000421C) /* read/write */
#define REG_VO_MIXER0_OSD_END                               FIO_ADDRESS(VO_MIXER0,0x90004220) /* read/write */
#define REG_VO_MIXER0_BACKGROUND                            FIO_ADDRESS(VO_MIXER0,0x90004224) /* read/write */
#define REG_VO_MIXER0_HIGHLIGHT                             FIO_ADDRESS(VO_MIXER0,0x90004228) /* read/write */
#define REG_VO_MIXER0_OSD_CONTROL                           FIO_ADDRESS(VO_MIXER0,0x9000422C) /* read/write */
#define REG_VO_MIXER0_ENABLE_CTRL                           FIO_ADDRESS(VO_MIXER0,0x90004250) /* read/write */
#define REG_VO_MIXER0_INPUT_VIDEO_SYNC                      FIO_ADDRESS(VO_MIXER0,0x90004254) /* read/write */
#define REG_VO_MIXER0_OUTPUT_SYNC                           FIO_ADDRESS(VO_MIXER0,0x9000425C) /* read/write */
#define REG_VO_MIXER0_SMEM_INPUT                            FIO_ADDRESS(VO_MIXER0,0x90004260) /* read/write */
#define REG_VO_MIXER0_SMEM_OUT                              FIO_ADDRESS(VO_MIXER0,0x90004268) /* read/write */
#define REG_VO_MIXER0_FRAME_ENABLE                          FIO_ADDRESS(VO_MIXER0,0x9000426C) /* read/write */
#define REG_VO_MIXER0_CLUT_A                                FIO_ADDRESS(VO_MIXER0,0x90011000) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_MIXER0_CONTROL */
    U32 all;
    struct {
        U32                             : 31;
        U32 reset                       : 1;
    } bitc;
} GH_VO_MIXER0_CONTROL_S;

typedef union { /* VO_MIXER0_STATUS */
    U32 all;
    struct {
        U32                             : 31;
        U32 reset                       : 1;
    } bitc;
} GH_VO_MIXER0_STATUS_S;

typedef union { /* VO_MIXER0_ACTIVE_SIZE */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER0_ACTIVE_SIZE_S;

typedef union { /* VO_MIXER0_VIDEO_START */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER0_VIDEO_START_S;

typedef union { /* VO_MIXER0_VIDEO_END */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER0_VIDEO_END_S;

typedef union { /* VO_MIXER0_OSD_START */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER0_OSD_START_S;

typedef union { /* VO_MIXER0_OSD_END */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER0_OSD_END_S;

typedef union { /* VO_MIXER0_BACKGROUND */
    U32 all;
    struct {
        U32 v                           : 8;
        U32 u                           : 8;
        U32 y                           : 8;
        U32                             : 8;
    } bitc;
} GH_VO_MIXER0_BACKGROUND_S;

typedef union { /* VO_MIXER0_HIGHLIGHT */
    U32 all;
    struct {
        U32 v                           : 8;
        U32 u                           : 8;
        U32 y                           : 8;
        U32 threshold                   : 8;
    } bitc;
} GH_VO_MIXER0_HIGHLIGHT_S;

typedef union { /* VO_MIXER0_OSD_CONTROL */
    U32 all;
    struct {
        U32 global_blend                : 8;
        U32 premultiplied               : 1;
        U32 mode                        : 3;
        U32 enable_transparent_color    : 1;
        U32                             : 3;
        U32 transparent_color           : 16;
    } bitc;
} GH_VO_MIXER0_OSD_CONTROL_S;

typedef union { /* VO_MIXER0_ENABLE_CTRL */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32 mapped_direct               : 2;
        U32 smem                        : 1;
        U32 display                     : 1;
        U32                             : 27;
    } bitc;
} GH_VO_MIXER0_ENABLE_CTRL_S;

typedef union { /* VO_MIXER0_INPUT_VIDEO_SYNC */
    U32 all;
    struct {
        U32 sync_mode                   : 2;
        U32 line                        : 3;
        U32 video                       : 6;
        U32 decrement                   : 1;
        U32                             : 20;
    } bitc;
} GH_VO_MIXER0_INPUT_VIDEO_SYNC_S;

typedef union { /* VO_MIXER0_OUTPUT_SYNC */
    U32 all;
    struct {
        U32 sync_mode                   : 1;
        U32                             : 1;
        U32 number                      : 3;
        U32 counter                     : 6;
        U32 sync                        : 1;
        U32 frame                       : 6;
        U32                             : 14;
    } bitc;
} GH_VO_MIXER0_OUTPUT_SYNC_S;

typedef union { /* VO_MIXER0_SMEM_INPUT */
    U32 all;
    struct {
        U32 luma_number                 : 8;
        U32 chroma_number               : 8;
        U32 osd_number                  : 8;
        U32 priority                    : 2;
        U32 video_length                : 2;
        U32 osd_length                  : 2;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER0_SMEM_INPUT_S;

typedef union { /* VO_MIXER0_SMEM_OUT */
    U32 all;
    struct {
        U32 luma_number                 : 8;
        U32 chroma_number               : 8;
        U32 priority                    : 2;
        U32                             : 14;
    } bitc;
} GH_VO_MIXER0_SMEM_OUT_S;

typedef union { /* VO_MIXER0_FRAME_ENABLE */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_MIXER0_FRAME_ENABLE_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_CONTROL (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_CONTROL'. */
void GH_VO_MIXER0_set_CONTROL(U32 data);
/*! \brief Reads the register 'VO_MIXER0_CONTROL'. */
U32  GH_VO_MIXER0_get_CONTROL(void);
/*! \brief Writes the bit group 'Reset' of register 'VO_MIXER0_CONTROL'. */
void GH_VO_MIXER0_set_CONTROL_Reset(U8 data);
/*! \brief Reads the bit group 'Reset' of register 'VO_MIXER0_CONTROL'. */
U8   GH_VO_MIXER0_get_CONTROL_Reset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_CONTROL = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_CONTROL] <-- 0x%08x\n",
                        REG_VO_MIXER0_CONTROL,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_CONTROL);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_CONTROL] --> 0x%08x\n",
                        REG_VO_MIXER0_CONTROL,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_CONTROL_Reset(U8 data)
{
    GH_VO_MIXER0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_CONTROL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_VO_MIXER0_CONTROL = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_CONTROL_Reset] <-- 0x%08x\n",
                        REG_VO_MIXER0_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_CONTROL_Reset(void)
{
    GH_VO_MIXER0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_CONTROL_Reset] --> 0x%08x\n",
                        REG_VO_MIXER0_CONTROL,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_STATUS (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'VO_MIXER0_STATUS'. */
U32  GH_VO_MIXER0_get_STATUS(void);
/*! \brief Reads the bit group 'Reset' of register 'VO_MIXER0_STATUS'. */
U8   GH_VO_MIXER0_get_STATUS_Reset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_VO_MIXER0_get_STATUS(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_STATUS);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_STATUS] --> 0x%08x\n",
                        REG_VO_MIXER0_STATUS,value);
    #endif
    return value;
}
GH_INLINE U8   GH_VO_MIXER0_get_STATUS_Reset(void)
{
    GH_VO_MIXER0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_STATUS);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_STATUS_Reset] --> 0x%08x\n",
                        REG_VO_MIXER0_STATUS,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_ACTIVE_SIZE (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_ACTIVE_SIZE'. */
void GH_VO_MIXER0_set_ACTIVE_SIZE(U32 data);
/*! \brief Reads the register 'VO_MIXER0_ACTIVE_SIZE'. */
U32  GH_VO_MIXER0_get_ACTIVE_SIZE(void);
/*! \brief Writes the bit group 'Vertical' of register 'VO_MIXER0_ACTIVE_SIZE'. */
void GH_VO_MIXER0_set_ACTIVE_SIZE_Vertical(U16 data);
/*! \brief Reads the bit group 'Vertical' of register 'VO_MIXER0_ACTIVE_SIZE'. */
U16  GH_VO_MIXER0_get_ACTIVE_SIZE_Vertical(void);
/*! \brief Writes the bit group 'Horizontal' of register 'VO_MIXER0_ACTIVE_SIZE'. */
void GH_VO_MIXER0_set_ACTIVE_SIZE_Horizontal(U16 data);
/*! \brief Reads the bit group 'Horizontal' of register 'VO_MIXER0_ACTIVE_SIZE'. */
U16  GH_VO_MIXER0_get_ACTIVE_SIZE_Horizontal(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_ACTIVE_SIZE(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_ACTIVE_SIZE = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_ACTIVE_SIZE] <-- 0x%08x\n",
                        REG_VO_MIXER0_ACTIVE_SIZE,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_ACTIVE_SIZE(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_ACTIVE_SIZE);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_ACTIVE_SIZE] --> 0x%08x\n",
                        REG_VO_MIXER0_ACTIVE_SIZE,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_ACTIVE_SIZE_Vertical(U16 data)
{
    GH_VO_MIXER0_ACTIVE_SIZE_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_ACTIVE_SIZE;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER0_ACTIVE_SIZE = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_ACTIVE_SIZE_Vertical] <-- 0x%08x\n",
                        REG_VO_MIXER0_ACTIVE_SIZE,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_MIXER0_get_ACTIVE_SIZE_Vertical(void)
{
    GH_VO_MIXER0_ACTIVE_SIZE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_ACTIVE_SIZE);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_ACTIVE_SIZE_Vertical] --> 0x%08x\n",
                        REG_VO_MIXER0_ACTIVE_SIZE,value);
    #endif
    return tmp_value.bitc.vertical;
}
GH_INLINE void GH_VO_MIXER0_set_ACTIVE_SIZE_Horizontal(U16 data)
{
    GH_VO_MIXER0_ACTIVE_SIZE_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_ACTIVE_SIZE;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER0_ACTIVE_SIZE = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_ACTIVE_SIZE_Horizontal] <-- 0x%08x\n",
                        REG_VO_MIXER0_ACTIVE_SIZE,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_MIXER0_get_ACTIVE_SIZE_Horizontal(void)
{
    GH_VO_MIXER0_ACTIVE_SIZE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_ACTIVE_SIZE);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_ACTIVE_SIZE_Horizontal] --> 0x%08x\n",
                        REG_VO_MIXER0_ACTIVE_SIZE,value);
    #endif
    return tmp_value.bitc.horizontal;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_VIDEO_START (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_VIDEO_START'. */
void GH_VO_MIXER0_set_VIDEO_START(U32 data);
/*! \brief Reads the register 'VO_MIXER0_VIDEO_START'. */
U32  GH_VO_MIXER0_get_VIDEO_START(void);
/*! \brief Writes the bit group 'Vertical' of register 'VO_MIXER0_VIDEO_START'. */
void GH_VO_MIXER0_set_VIDEO_START_Vertical(U16 data);
/*! \brief Reads the bit group 'Vertical' of register 'VO_MIXER0_VIDEO_START'. */
U16  GH_VO_MIXER0_get_VIDEO_START_Vertical(void);
/*! \brief Writes the bit group 'Horizontal' of register 'VO_MIXER0_VIDEO_START'. */
void GH_VO_MIXER0_set_VIDEO_START_Horizontal(U16 data);
/*! \brief Reads the bit group 'Horizontal' of register 'VO_MIXER0_VIDEO_START'. */
U16  GH_VO_MIXER0_get_VIDEO_START_Horizontal(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_VIDEO_START(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_VIDEO_START = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_VIDEO_START] <-- 0x%08x\n",
                        REG_VO_MIXER0_VIDEO_START,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_VIDEO_START(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_VIDEO_START);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_VIDEO_START] --> 0x%08x\n",
                        REG_VO_MIXER0_VIDEO_START,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_VIDEO_START_Vertical(U16 data)
{
    GH_VO_MIXER0_VIDEO_START_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_VIDEO_START;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER0_VIDEO_START = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_VIDEO_START_Vertical] <-- 0x%08x\n",
                        REG_VO_MIXER0_VIDEO_START,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_MIXER0_get_VIDEO_START_Vertical(void)
{
    GH_VO_MIXER0_VIDEO_START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_VIDEO_START);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_VIDEO_START_Vertical] --> 0x%08x\n",
                        REG_VO_MIXER0_VIDEO_START,value);
    #endif
    return tmp_value.bitc.vertical;
}
GH_INLINE void GH_VO_MIXER0_set_VIDEO_START_Horizontal(U16 data)
{
    GH_VO_MIXER0_VIDEO_START_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_VIDEO_START;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER0_VIDEO_START = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_VIDEO_START_Horizontal] <-- 0x%08x\n",
                        REG_VO_MIXER0_VIDEO_START,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_MIXER0_get_VIDEO_START_Horizontal(void)
{
    GH_VO_MIXER0_VIDEO_START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_VIDEO_START);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_VIDEO_START_Horizontal] --> 0x%08x\n",
                        REG_VO_MIXER0_VIDEO_START,value);
    #endif
    return tmp_value.bitc.horizontal;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_VIDEO_END (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_VIDEO_END'. */
void GH_VO_MIXER0_set_VIDEO_END(U32 data);
/*! \brief Reads the register 'VO_MIXER0_VIDEO_END'. */
U32  GH_VO_MIXER0_get_VIDEO_END(void);
/*! \brief Writes the bit group 'Vertical' of register 'VO_MIXER0_VIDEO_END'. */
void GH_VO_MIXER0_set_VIDEO_END_Vertical(U16 data);
/*! \brief Reads the bit group 'Vertical' of register 'VO_MIXER0_VIDEO_END'. */
U16  GH_VO_MIXER0_get_VIDEO_END_Vertical(void);
/*! \brief Writes the bit group 'Horizontal' of register 'VO_MIXER0_VIDEO_END'. */
void GH_VO_MIXER0_set_VIDEO_END_Horizontal(U16 data);
/*! \brief Reads the bit group 'Horizontal' of register 'VO_MIXER0_VIDEO_END'. */
U16  GH_VO_MIXER0_get_VIDEO_END_Horizontal(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_VIDEO_END(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_VIDEO_END = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_VIDEO_END] <-- 0x%08x\n",
                        REG_VO_MIXER0_VIDEO_END,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_VIDEO_END(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_VIDEO_END);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_VIDEO_END] --> 0x%08x\n",
                        REG_VO_MIXER0_VIDEO_END,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_VIDEO_END_Vertical(U16 data)
{
    GH_VO_MIXER0_VIDEO_END_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_VIDEO_END;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER0_VIDEO_END = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_VIDEO_END_Vertical] <-- 0x%08x\n",
                        REG_VO_MIXER0_VIDEO_END,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_MIXER0_get_VIDEO_END_Vertical(void)
{
    GH_VO_MIXER0_VIDEO_END_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_VIDEO_END);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_VIDEO_END_Vertical] --> 0x%08x\n",
                        REG_VO_MIXER0_VIDEO_END,value);
    #endif
    return tmp_value.bitc.vertical;
}
GH_INLINE void GH_VO_MIXER0_set_VIDEO_END_Horizontal(U16 data)
{
    GH_VO_MIXER0_VIDEO_END_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_VIDEO_END;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER0_VIDEO_END = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_VIDEO_END_Horizontal] <-- 0x%08x\n",
                        REG_VO_MIXER0_VIDEO_END,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_MIXER0_get_VIDEO_END_Horizontal(void)
{
    GH_VO_MIXER0_VIDEO_END_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_VIDEO_END);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_VIDEO_END_Horizontal] --> 0x%08x\n",
                        REG_VO_MIXER0_VIDEO_END,value);
    #endif
    return tmp_value.bitc.horizontal;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_OSD_START (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_OSD_START'. */
void GH_VO_MIXER0_set_OSD_START(U32 data);
/*! \brief Reads the register 'VO_MIXER0_OSD_START'. */
U32  GH_VO_MIXER0_get_OSD_START(void);
/*! \brief Writes the bit group 'Vertical' of register 'VO_MIXER0_OSD_START'. */
void GH_VO_MIXER0_set_OSD_START_Vertical(U16 data);
/*! \brief Reads the bit group 'Vertical' of register 'VO_MIXER0_OSD_START'. */
U16  GH_VO_MIXER0_get_OSD_START_Vertical(void);
/*! \brief Writes the bit group 'Horizontal' of register 'VO_MIXER0_OSD_START'. */
void GH_VO_MIXER0_set_OSD_START_Horizontal(U16 data);
/*! \brief Reads the bit group 'Horizontal' of register 'VO_MIXER0_OSD_START'. */
U16  GH_VO_MIXER0_get_OSD_START_Horizontal(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_OSD_START(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_OSD_START = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OSD_START] <-- 0x%08x\n",
                        REG_VO_MIXER0_OSD_START,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_OSD_START(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OSD_START);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OSD_START] --> 0x%08x\n",
                        REG_VO_MIXER0_OSD_START,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_OSD_START_Vertical(U16 data)
{
    GH_VO_MIXER0_OSD_START_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OSD_START;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER0_OSD_START = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OSD_START_Vertical] <-- 0x%08x\n",
                        REG_VO_MIXER0_OSD_START,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_MIXER0_get_OSD_START_Vertical(void)
{
    GH_VO_MIXER0_OSD_START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OSD_START);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OSD_START_Vertical] --> 0x%08x\n",
                        REG_VO_MIXER0_OSD_START,value);
    #endif
    return tmp_value.bitc.vertical;
}
GH_INLINE void GH_VO_MIXER0_set_OSD_START_Horizontal(U16 data)
{
    GH_VO_MIXER0_OSD_START_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OSD_START;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER0_OSD_START = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OSD_START_Horizontal] <-- 0x%08x\n",
                        REG_VO_MIXER0_OSD_START,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_MIXER0_get_OSD_START_Horizontal(void)
{
    GH_VO_MIXER0_OSD_START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OSD_START);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OSD_START_Horizontal] --> 0x%08x\n",
                        REG_VO_MIXER0_OSD_START,value);
    #endif
    return tmp_value.bitc.horizontal;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_OSD_END (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_OSD_END'. */
void GH_VO_MIXER0_set_OSD_END(U32 data);
/*! \brief Reads the register 'VO_MIXER0_OSD_END'. */
U32  GH_VO_MIXER0_get_OSD_END(void);
/*! \brief Writes the bit group 'Vertical' of register 'VO_MIXER0_OSD_END'. */
void GH_VO_MIXER0_set_OSD_END_Vertical(U16 data);
/*! \brief Reads the bit group 'Vertical' of register 'VO_MIXER0_OSD_END'. */
U16  GH_VO_MIXER0_get_OSD_END_Vertical(void);
/*! \brief Writes the bit group 'Horizontal' of register 'VO_MIXER0_OSD_END'. */
void GH_VO_MIXER0_set_OSD_END_Horizontal(U16 data);
/*! \brief Reads the bit group 'Horizontal' of register 'VO_MIXER0_OSD_END'. */
U16  GH_VO_MIXER0_get_OSD_END_Horizontal(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_OSD_END(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_OSD_END = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OSD_END] <-- 0x%08x\n",
                        REG_VO_MIXER0_OSD_END,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_OSD_END(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OSD_END);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OSD_END] --> 0x%08x\n",
                        REG_VO_MIXER0_OSD_END,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_OSD_END_Vertical(U16 data)
{
    GH_VO_MIXER0_OSD_END_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OSD_END;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER0_OSD_END = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OSD_END_Vertical] <-- 0x%08x\n",
                        REG_VO_MIXER0_OSD_END,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_MIXER0_get_OSD_END_Vertical(void)
{
    GH_VO_MIXER0_OSD_END_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OSD_END);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OSD_END_Vertical] --> 0x%08x\n",
                        REG_VO_MIXER0_OSD_END,value);
    #endif
    return tmp_value.bitc.vertical;
}
GH_INLINE void GH_VO_MIXER0_set_OSD_END_Horizontal(U16 data)
{
    GH_VO_MIXER0_OSD_END_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OSD_END;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER0_OSD_END = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OSD_END_Horizontal] <-- 0x%08x\n",
                        REG_VO_MIXER0_OSD_END,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_MIXER0_get_OSD_END_Horizontal(void)
{
    GH_VO_MIXER0_OSD_END_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OSD_END);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OSD_END_Horizontal] --> 0x%08x\n",
                        REG_VO_MIXER0_OSD_END,value);
    #endif
    return tmp_value.bitc.horizontal;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_BACKGROUND (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_BACKGROUND'. */
void GH_VO_MIXER0_set_BACKGROUND(U32 data);
/*! \brief Reads the register 'VO_MIXER0_BACKGROUND'. */
U32  GH_VO_MIXER0_get_BACKGROUND(void);
/*! \brief Writes the bit group 'V' of register 'VO_MIXER0_BACKGROUND'. */
void GH_VO_MIXER0_set_BACKGROUND_V(U8 data);
/*! \brief Reads the bit group 'V' of register 'VO_MIXER0_BACKGROUND'. */
U8   GH_VO_MIXER0_get_BACKGROUND_V(void);
/*! \brief Writes the bit group 'U' of register 'VO_MIXER0_BACKGROUND'. */
void GH_VO_MIXER0_set_BACKGROUND_U(U8 data);
/*! \brief Reads the bit group 'U' of register 'VO_MIXER0_BACKGROUND'. */
U8   GH_VO_MIXER0_get_BACKGROUND_U(void);
/*! \brief Writes the bit group 'Y' of register 'VO_MIXER0_BACKGROUND'. */
void GH_VO_MIXER0_set_BACKGROUND_Y(U8 data);
/*! \brief Reads the bit group 'Y' of register 'VO_MIXER0_BACKGROUND'. */
U8   GH_VO_MIXER0_get_BACKGROUND_Y(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_BACKGROUND(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_BACKGROUND = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_BACKGROUND] <-- 0x%08x\n",
                        REG_VO_MIXER0_BACKGROUND,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_BACKGROUND(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_BACKGROUND);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_BACKGROUND] --> 0x%08x\n",
                        REG_VO_MIXER0_BACKGROUND,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_BACKGROUND_V(U8 data)
{
    GH_VO_MIXER0_BACKGROUND_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_BACKGROUND;
    d.bitc.v = data;
    *(volatile U32 *)REG_VO_MIXER0_BACKGROUND = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_BACKGROUND_V] <-- 0x%08x\n",
                        REG_VO_MIXER0_BACKGROUND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_BACKGROUND_V(void)
{
    GH_VO_MIXER0_BACKGROUND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_BACKGROUND);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_BACKGROUND_V] --> 0x%08x\n",
                        REG_VO_MIXER0_BACKGROUND,value);
    #endif
    return tmp_value.bitc.v;
}
GH_INLINE void GH_VO_MIXER0_set_BACKGROUND_U(U8 data)
{
    GH_VO_MIXER0_BACKGROUND_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_BACKGROUND;
    d.bitc.u = data;
    *(volatile U32 *)REG_VO_MIXER0_BACKGROUND = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_BACKGROUND_U] <-- 0x%08x\n",
                        REG_VO_MIXER0_BACKGROUND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_BACKGROUND_U(void)
{
    GH_VO_MIXER0_BACKGROUND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_BACKGROUND);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_BACKGROUND_U] --> 0x%08x\n",
                        REG_VO_MIXER0_BACKGROUND,value);
    #endif
    return tmp_value.bitc.u;
}
GH_INLINE void GH_VO_MIXER0_set_BACKGROUND_Y(U8 data)
{
    GH_VO_MIXER0_BACKGROUND_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_BACKGROUND;
    d.bitc.y = data;
    *(volatile U32 *)REG_VO_MIXER0_BACKGROUND = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_BACKGROUND_Y] <-- 0x%08x\n",
                        REG_VO_MIXER0_BACKGROUND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_BACKGROUND_Y(void)
{
    GH_VO_MIXER0_BACKGROUND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_BACKGROUND);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_BACKGROUND_Y] --> 0x%08x\n",
                        REG_VO_MIXER0_BACKGROUND,value);
    #endif
    return tmp_value.bitc.y;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_HIGHLIGHT (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_HIGHLIGHT'. */
void GH_VO_MIXER0_set_HIGHLIGHT(U32 data);
/*! \brief Reads the register 'VO_MIXER0_HIGHLIGHT'. */
U32  GH_VO_MIXER0_get_HIGHLIGHT(void);
/*! \brief Writes the bit group 'V' of register 'VO_MIXER0_HIGHLIGHT'. */
void GH_VO_MIXER0_set_HIGHLIGHT_V(U8 data);
/*! \brief Reads the bit group 'V' of register 'VO_MIXER0_HIGHLIGHT'. */
U8   GH_VO_MIXER0_get_HIGHLIGHT_V(void);
/*! \brief Writes the bit group 'U' of register 'VO_MIXER0_HIGHLIGHT'. */
void GH_VO_MIXER0_set_HIGHLIGHT_U(U8 data);
/*! \brief Reads the bit group 'U' of register 'VO_MIXER0_HIGHLIGHT'. */
U8   GH_VO_MIXER0_get_HIGHLIGHT_U(void);
/*! \brief Writes the bit group 'Y' of register 'VO_MIXER0_HIGHLIGHT'. */
void GH_VO_MIXER0_set_HIGHLIGHT_Y(U8 data);
/*! \brief Reads the bit group 'Y' of register 'VO_MIXER0_HIGHLIGHT'. */
U8   GH_VO_MIXER0_get_HIGHLIGHT_Y(void);
/*! \brief Writes the bit group 'threshold' of register 'VO_MIXER0_HIGHLIGHT'. */
void GH_VO_MIXER0_set_HIGHLIGHT_threshold(U8 data);
/*! \brief Reads the bit group 'threshold' of register 'VO_MIXER0_HIGHLIGHT'. */
U8   GH_VO_MIXER0_get_HIGHLIGHT_threshold(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_HIGHLIGHT(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_HIGHLIGHT] <-- 0x%08x\n",
                        REG_VO_MIXER0_HIGHLIGHT,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_HIGHLIGHT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_HIGHLIGHT] --> 0x%08x\n",
                        REG_VO_MIXER0_HIGHLIGHT,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_HIGHLIGHT_V(U8 data)
{
    GH_VO_MIXER0_HIGHLIGHT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT;
    d.bitc.v = data;
    *(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_HIGHLIGHT_V] <-- 0x%08x\n",
                        REG_VO_MIXER0_HIGHLIGHT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_HIGHLIGHT_V(void)
{
    GH_VO_MIXER0_HIGHLIGHT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_HIGHLIGHT_V] --> 0x%08x\n",
                        REG_VO_MIXER0_HIGHLIGHT,value);
    #endif
    return tmp_value.bitc.v;
}
GH_INLINE void GH_VO_MIXER0_set_HIGHLIGHT_U(U8 data)
{
    GH_VO_MIXER0_HIGHLIGHT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT;
    d.bitc.u = data;
    *(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_HIGHLIGHT_U] <-- 0x%08x\n",
                        REG_VO_MIXER0_HIGHLIGHT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_HIGHLIGHT_U(void)
{
    GH_VO_MIXER0_HIGHLIGHT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_HIGHLIGHT_U] --> 0x%08x\n",
                        REG_VO_MIXER0_HIGHLIGHT,value);
    #endif
    return tmp_value.bitc.u;
}
GH_INLINE void GH_VO_MIXER0_set_HIGHLIGHT_Y(U8 data)
{
    GH_VO_MIXER0_HIGHLIGHT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT;
    d.bitc.y = data;
    *(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_HIGHLIGHT_Y] <-- 0x%08x\n",
                        REG_VO_MIXER0_HIGHLIGHT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_HIGHLIGHT_Y(void)
{
    GH_VO_MIXER0_HIGHLIGHT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_HIGHLIGHT_Y] --> 0x%08x\n",
                        REG_VO_MIXER0_HIGHLIGHT,value);
    #endif
    return tmp_value.bitc.y;
}
GH_INLINE void GH_VO_MIXER0_set_HIGHLIGHT_threshold(U8 data)
{
    GH_VO_MIXER0_HIGHLIGHT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT;
    d.bitc.threshold = data;
    *(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_HIGHLIGHT_threshold] <-- 0x%08x\n",
                        REG_VO_MIXER0_HIGHLIGHT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_HIGHLIGHT_threshold(void)
{
    GH_VO_MIXER0_HIGHLIGHT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_HIGHLIGHT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_HIGHLIGHT_threshold] --> 0x%08x\n",
                        REG_VO_MIXER0_HIGHLIGHT,value);
    #endif
    return tmp_value.bitc.threshold;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_OSD_CONTROL (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_OSD_CONTROL'. */
void GH_VO_MIXER0_set_OSD_CONTROL(U32 data);
/*! \brief Reads the register 'VO_MIXER0_OSD_CONTROL'. */
U32  GH_VO_MIXER0_get_OSD_CONTROL(void);
/*! \brief Writes the bit group 'Global_Blend' of register 'VO_MIXER0_OSD_CONTROL'. */
void GH_VO_MIXER0_set_OSD_CONTROL_Global_Blend(U8 data);
/*! \brief Reads the bit group 'Global_Blend' of register 'VO_MIXER0_OSD_CONTROL'. */
U8   GH_VO_MIXER0_get_OSD_CONTROL_Global_Blend(void);
/*! \brief Writes the bit group 'Premultiplied' of register 'VO_MIXER0_OSD_CONTROL'. */
void GH_VO_MIXER0_set_OSD_CONTROL_Premultiplied(U8 data);
/*! \brief Reads the bit group 'Premultiplied' of register 'VO_MIXER0_OSD_CONTROL'. */
U8   GH_VO_MIXER0_get_OSD_CONTROL_Premultiplied(void);
/*! \brief Writes the bit group 'Mode' of register 'VO_MIXER0_OSD_CONTROL'. */
void GH_VO_MIXER0_set_OSD_CONTROL_Mode(U8 data);
/*! \brief Reads the bit group 'Mode' of register 'VO_MIXER0_OSD_CONTROL'. */
U8   GH_VO_MIXER0_get_OSD_CONTROL_Mode(void);
/*! \brief Writes the bit group 'Enable_Transparent_Color' of register 'VO_MIXER0_OSD_CONTROL'. */
void GH_VO_MIXER0_set_OSD_CONTROL_Enable_Transparent_Color(U8 data);
/*! \brief Reads the bit group 'Enable_Transparent_Color' of register 'VO_MIXER0_OSD_CONTROL'. */
U8   GH_VO_MIXER0_get_OSD_CONTROL_Enable_Transparent_Color(void);
/*! \brief Writes the bit group 'Transparent_Color' of register 'VO_MIXER0_OSD_CONTROL'. */
void GH_VO_MIXER0_set_OSD_CONTROL_Transparent_Color(U16 data);
/*! \brief Reads the bit group 'Transparent_Color' of register 'VO_MIXER0_OSD_CONTROL'. */
U16  GH_VO_MIXER0_get_OSD_CONTROL_Transparent_Color(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_OSD_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OSD_CONTROL] <-- 0x%08x\n",
                        REG_VO_MIXER0_OSD_CONTROL,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_OSD_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OSD_CONTROL] --> 0x%08x\n",
                        REG_VO_MIXER0_OSD_CONTROL,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_OSD_CONTROL_Global_Blend(U8 data)
{
    GH_VO_MIXER0_OSD_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL;
    d.bitc.global_blend = data;
    *(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OSD_CONTROL_Global_Blend] <-- 0x%08x\n",
                        REG_VO_MIXER0_OSD_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_OSD_CONTROL_Global_Blend(void)
{
    GH_VO_MIXER0_OSD_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OSD_CONTROL_Global_Blend] --> 0x%08x\n",
                        REG_VO_MIXER0_OSD_CONTROL,value);
    #endif
    return tmp_value.bitc.global_blend;
}
GH_INLINE void GH_VO_MIXER0_set_OSD_CONTROL_Premultiplied(U8 data)
{
    GH_VO_MIXER0_OSD_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL;
    d.bitc.premultiplied = data;
    *(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OSD_CONTROL_Premultiplied] <-- 0x%08x\n",
                        REG_VO_MIXER0_OSD_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_OSD_CONTROL_Premultiplied(void)
{
    GH_VO_MIXER0_OSD_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OSD_CONTROL_Premultiplied] --> 0x%08x\n",
                        REG_VO_MIXER0_OSD_CONTROL,value);
    #endif
    return tmp_value.bitc.premultiplied;
}
GH_INLINE void GH_VO_MIXER0_set_OSD_CONTROL_Mode(U8 data)
{
    GH_VO_MIXER0_OSD_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL;
    d.bitc.mode = data;
    *(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OSD_CONTROL_Mode] <-- 0x%08x\n",
                        REG_VO_MIXER0_OSD_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_OSD_CONTROL_Mode(void)
{
    GH_VO_MIXER0_OSD_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OSD_CONTROL_Mode] --> 0x%08x\n",
                        REG_VO_MIXER0_OSD_CONTROL,value);
    #endif
    return tmp_value.bitc.mode;
}
GH_INLINE void GH_VO_MIXER0_set_OSD_CONTROL_Enable_Transparent_Color(U8 data)
{
    GH_VO_MIXER0_OSD_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL;
    d.bitc.enable_transparent_color = data;
    *(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OSD_CONTROL_Enable_Transparent_Color] <-- 0x%08x\n",
                        REG_VO_MIXER0_OSD_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_OSD_CONTROL_Enable_Transparent_Color(void)
{
    GH_VO_MIXER0_OSD_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OSD_CONTROL_Enable_Transparent_Color] --> 0x%08x\n",
                        REG_VO_MIXER0_OSD_CONTROL,value);
    #endif
    return tmp_value.bitc.enable_transparent_color;
}
GH_INLINE void GH_VO_MIXER0_set_OSD_CONTROL_Transparent_Color(U16 data)
{
    GH_VO_MIXER0_OSD_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL;
    d.bitc.transparent_color = data;
    *(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OSD_CONTROL_Transparent_Color] <-- 0x%08x\n",
                        REG_VO_MIXER0_OSD_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_MIXER0_get_OSD_CONTROL_Transparent_Color(void)
{
    GH_VO_MIXER0_OSD_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OSD_CONTROL);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OSD_CONTROL_Transparent_Color] --> 0x%08x\n",
                        REG_VO_MIXER0_OSD_CONTROL,value);
    #endif
    return tmp_value.bitc.transparent_color;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_ENABLE_CTRL (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_ENABLE_CTRL'. */
void GH_VO_MIXER0_set_ENABLE_CTRL(U32 data);
/*! \brief Reads the register 'VO_MIXER0_ENABLE_CTRL'. */
U32  GH_VO_MIXER0_get_ENABLE_CTRL(void);
/*! \brief Writes the bit group 'enable' of register 'VO_MIXER0_ENABLE_CTRL'. */
void GH_VO_MIXER0_set_ENABLE_CTRL_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_MIXER0_ENABLE_CTRL'. */
U8   GH_VO_MIXER0_get_ENABLE_CTRL_enable(void);
/*! \brief Writes the bit group 'mapped_direct' of register 'VO_MIXER0_ENABLE_CTRL'. */
void GH_VO_MIXER0_set_ENABLE_CTRL_mapped_direct(U8 data);
/*! \brief Reads the bit group 'mapped_direct' of register 'VO_MIXER0_ENABLE_CTRL'. */
U8   GH_VO_MIXER0_get_ENABLE_CTRL_mapped_direct(void);
/*! \brief Writes the bit group 'smem' of register 'VO_MIXER0_ENABLE_CTRL'. */
void GH_VO_MIXER0_set_ENABLE_CTRL_smem(U8 data);
/*! \brief Reads the bit group 'smem' of register 'VO_MIXER0_ENABLE_CTRL'. */
U8   GH_VO_MIXER0_get_ENABLE_CTRL_smem(void);
/*! \brief Writes the bit group 'display' of register 'VO_MIXER0_ENABLE_CTRL'. */
void GH_VO_MIXER0_set_ENABLE_CTRL_display(U8 data);
/*! \brief Reads the bit group 'display' of register 'VO_MIXER0_ENABLE_CTRL'. */
U8   GH_VO_MIXER0_get_ENABLE_CTRL_display(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_ENABLE_CTRL(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_ENABLE_CTRL] <-- 0x%08x\n",
                        REG_VO_MIXER0_ENABLE_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_ENABLE_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_ENABLE_CTRL] --> 0x%08x\n",
                        REG_VO_MIXER0_ENABLE_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_ENABLE_CTRL_enable(U8 data)
{
    GH_VO_MIXER0_ENABLE_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_ENABLE_CTRL_enable] <-- 0x%08x\n",
                        REG_VO_MIXER0_ENABLE_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_ENABLE_CTRL_enable(void)
{
    GH_VO_MIXER0_ENABLE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_ENABLE_CTRL_enable] --> 0x%08x\n",
                        REG_VO_MIXER0_ENABLE_CTRL,value);
    #endif
    return tmp_value.bitc.enable;
}
GH_INLINE void GH_VO_MIXER0_set_ENABLE_CTRL_mapped_direct(U8 data)
{
    GH_VO_MIXER0_ENABLE_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL;
    d.bitc.mapped_direct = data;
    *(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_ENABLE_CTRL_mapped_direct] <-- 0x%08x\n",
                        REG_VO_MIXER0_ENABLE_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_ENABLE_CTRL_mapped_direct(void)
{
    GH_VO_MIXER0_ENABLE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_ENABLE_CTRL_mapped_direct] --> 0x%08x\n",
                        REG_VO_MIXER0_ENABLE_CTRL,value);
    #endif
    return tmp_value.bitc.mapped_direct;
}
GH_INLINE void GH_VO_MIXER0_set_ENABLE_CTRL_smem(U8 data)
{
    GH_VO_MIXER0_ENABLE_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL;
    d.bitc.smem = data;
    *(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_ENABLE_CTRL_smem] <-- 0x%08x\n",
                        REG_VO_MIXER0_ENABLE_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_ENABLE_CTRL_smem(void)
{
    GH_VO_MIXER0_ENABLE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_ENABLE_CTRL_smem] --> 0x%08x\n",
                        REG_VO_MIXER0_ENABLE_CTRL,value);
    #endif
    return tmp_value.bitc.smem;
}
GH_INLINE void GH_VO_MIXER0_set_ENABLE_CTRL_display(U8 data)
{
    GH_VO_MIXER0_ENABLE_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL;
    d.bitc.display = data;
    *(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_ENABLE_CTRL_display] <-- 0x%08x\n",
                        REG_VO_MIXER0_ENABLE_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_ENABLE_CTRL_display(void)
{
    GH_VO_MIXER0_ENABLE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_ENABLE_CTRL);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_ENABLE_CTRL_display] --> 0x%08x\n",
                        REG_VO_MIXER0_ENABLE_CTRL,value);
    #endif
    return tmp_value.bitc.display;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_INPUT_VIDEO_SYNC (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_INPUT_VIDEO_SYNC'. */
void GH_VO_MIXER0_set_INPUT_VIDEO_SYNC(U32 data);
/*! \brief Reads the register 'VO_MIXER0_INPUT_VIDEO_SYNC'. */
U32  GH_VO_MIXER0_get_INPUT_VIDEO_SYNC(void);
/*! \brief Writes the bit group 'sync_mode' of register 'VO_MIXER0_INPUT_VIDEO_SYNC'. */
void GH_VO_MIXER0_set_INPUT_VIDEO_SYNC_sync_mode(U8 data);
/*! \brief Reads the bit group 'sync_mode' of register 'VO_MIXER0_INPUT_VIDEO_SYNC'. */
U8   GH_VO_MIXER0_get_INPUT_VIDEO_SYNC_sync_mode(void);
/*! \brief Writes the bit group 'line' of register 'VO_MIXER0_INPUT_VIDEO_SYNC'. */
void GH_VO_MIXER0_set_INPUT_VIDEO_SYNC_line(U8 data);
/*! \brief Reads the bit group 'line' of register 'VO_MIXER0_INPUT_VIDEO_SYNC'. */
U8   GH_VO_MIXER0_get_INPUT_VIDEO_SYNC_line(void);
/*! \brief Writes the bit group 'video' of register 'VO_MIXER0_INPUT_VIDEO_SYNC'. */
void GH_VO_MIXER0_set_INPUT_VIDEO_SYNC_video(U8 data);
/*! \brief Reads the bit group 'video' of register 'VO_MIXER0_INPUT_VIDEO_SYNC'. */
U8   GH_VO_MIXER0_get_INPUT_VIDEO_SYNC_video(void);
/*! \brief Writes the bit group 'decrement' of register 'VO_MIXER0_INPUT_VIDEO_SYNC'. */
void GH_VO_MIXER0_set_INPUT_VIDEO_SYNC_decrement(U8 data);
/*! \brief Reads the bit group 'decrement' of register 'VO_MIXER0_INPUT_VIDEO_SYNC'. */
U8   GH_VO_MIXER0_get_INPUT_VIDEO_SYNC_decrement(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_INPUT_VIDEO_SYNC(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_INPUT_VIDEO_SYNC] <-- 0x%08x\n",
                        REG_VO_MIXER0_INPUT_VIDEO_SYNC,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_INPUT_VIDEO_SYNC(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_INPUT_VIDEO_SYNC] --> 0x%08x\n",
                        REG_VO_MIXER0_INPUT_VIDEO_SYNC,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_INPUT_VIDEO_SYNC_sync_mode(U8 data)
{
    GH_VO_MIXER0_INPUT_VIDEO_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC;
    d.bitc.sync_mode = data;
    *(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_INPUT_VIDEO_SYNC_sync_mode] <-- 0x%08x\n",
                        REG_VO_MIXER0_INPUT_VIDEO_SYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_INPUT_VIDEO_SYNC_sync_mode(void)
{
    GH_VO_MIXER0_INPUT_VIDEO_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_INPUT_VIDEO_SYNC_sync_mode] --> 0x%08x\n",
                        REG_VO_MIXER0_INPUT_VIDEO_SYNC,value);
    #endif
    return tmp_value.bitc.sync_mode;
}
GH_INLINE void GH_VO_MIXER0_set_INPUT_VIDEO_SYNC_line(U8 data)
{
    GH_VO_MIXER0_INPUT_VIDEO_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC;
    d.bitc.line = data;
    *(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_INPUT_VIDEO_SYNC_line] <-- 0x%08x\n",
                        REG_VO_MIXER0_INPUT_VIDEO_SYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_INPUT_VIDEO_SYNC_line(void)
{
    GH_VO_MIXER0_INPUT_VIDEO_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_INPUT_VIDEO_SYNC_line] --> 0x%08x\n",
                        REG_VO_MIXER0_INPUT_VIDEO_SYNC,value);
    #endif
    return tmp_value.bitc.line;
}
GH_INLINE void GH_VO_MIXER0_set_INPUT_VIDEO_SYNC_video(U8 data)
{
    GH_VO_MIXER0_INPUT_VIDEO_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC;
    d.bitc.video = data;
    *(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_INPUT_VIDEO_SYNC_video] <-- 0x%08x\n",
                        REG_VO_MIXER0_INPUT_VIDEO_SYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_INPUT_VIDEO_SYNC_video(void)
{
    GH_VO_MIXER0_INPUT_VIDEO_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_INPUT_VIDEO_SYNC_video] --> 0x%08x\n",
                        REG_VO_MIXER0_INPUT_VIDEO_SYNC,value);
    #endif
    return tmp_value.bitc.video;
}
GH_INLINE void GH_VO_MIXER0_set_INPUT_VIDEO_SYNC_decrement(U8 data)
{
    GH_VO_MIXER0_INPUT_VIDEO_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC;
    d.bitc.decrement = data;
    *(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_INPUT_VIDEO_SYNC_decrement] <-- 0x%08x\n",
                        REG_VO_MIXER0_INPUT_VIDEO_SYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_INPUT_VIDEO_SYNC_decrement(void)
{
    GH_VO_MIXER0_INPUT_VIDEO_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_INPUT_VIDEO_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_INPUT_VIDEO_SYNC_decrement] --> 0x%08x\n",
                        REG_VO_MIXER0_INPUT_VIDEO_SYNC,value);
    #endif
    return tmp_value.bitc.decrement;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_OUTPUT_SYNC (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_OUTPUT_SYNC'. */
void GH_VO_MIXER0_set_OUTPUT_SYNC(U32 data);
/*! \brief Reads the register 'VO_MIXER0_OUTPUT_SYNC'. */
U32  GH_VO_MIXER0_get_OUTPUT_SYNC(void);
/*! \brief Writes the bit group 'sync_mode' of register 'VO_MIXER0_OUTPUT_SYNC'. */
void GH_VO_MIXER0_set_OUTPUT_SYNC_sync_mode(U8 data);
/*! \brief Reads the bit group 'sync_mode' of register 'VO_MIXER0_OUTPUT_SYNC'. */
U8   GH_VO_MIXER0_get_OUTPUT_SYNC_sync_mode(void);
/*! \brief Writes the bit group 'number' of register 'VO_MIXER0_OUTPUT_SYNC'. */
void GH_VO_MIXER0_set_OUTPUT_SYNC_number(U8 data);
/*! \brief Reads the bit group 'number' of register 'VO_MIXER0_OUTPUT_SYNC'. */
U8   GH_VO_MIXER0_get_OUTPUT_SYNC_number(void);
/*! \brief Writes the bit group 'counter' of register 'VO_MIXER0_OUTPUT_SYNC'. */
void GH_VO_MIXER0_set_OUTPUT_SYNC_counter(U8 data);
/*! \brief Reads the bit group 'counter' of register 'VO_MIXER0_OUTPUT_SYNC'. */
U8   GH_VO_MIXER0_get_OUTPUT_SYNC_counter(void);
/*! \brief Writes the bit group 'sync' of register 'VO_MIXER0_OUTPUT_SYNC'. */
void GH_VO_MIXER0_set_OUTPUT_SYNC_sync(U8 data);
/*! \brief Reads the bit group 'sync' of register 'VO_MIXER0_OUTPUT_SYNC'. */
U8   GH_VO_MIXER0_get_OUTPUT_SYNC_sync(void);
/*! \brief Writes the bit group 'frame' of register 'VO_MIXER0_OUTPUT_SYNC'. */
void GH_VO_MIXER0_set_OUTPUT_SYNC_frame(U8 data);
/*! \brief Reads the bit group 'frame' of register 'VO_MIXER0_OUTPUT_SYNC'. */
U8   GH_VO_MIXER0_get_OUTPUT_SYNC_frame(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_OUTPUT_SYNC(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OUTPUT_SYNC] <-- 0x%08x\n",
                        REG_VO_MIXER0_OUTPUT_SYNC,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_OUTPUT_SYNC(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OUTPUT_SYNC] --> 0x%08x\n",
                        REG_VO_MIXER0_OUTPUT_SYNC,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_OUTPUT_SYNC_sync_mode(U8 data)
{
    GH_VO_MIXER0_OUTPUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC;
    d.bitc.sync_mode = data;
    *(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OUTPUT_SYNC_sync_mode] <-- 0x%08x\n",
                        REG_VO_MIXER0_OUTPUT_SYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_OUTPUT_SYNC_sync_mode(void)
{
    GH_VO_MIXER0_OUTPUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OUTPUT_SYNC_sync_mode] --> 0x%08x\n",
                        REG_VO_MIXER0_OUTPUT_SYNC,value);
    #endif
    return tmp_value.bitc.sync_mode;
}
GH_INLINE void GH_VO_MIXER0_set_OUTPUT_SYNC_number(U8 data)
{
    GH_VO_MIXER0_OUTPUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC;
    d.bitc.number = data;
    *(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OUTPUT_SYNC_number] <-- 0x%08x\n",
                        REG_VO_MIXER0_OUTPUT_SYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_OUTPUT_SYNC_number(void)
{
    GH_VO_MIXER0_OUTPUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OUTPUT_SYNC_number] --> 0x%08x\n",
                        REG_VO_MIXER0_OUTPUT_SYNC,value);
    #endif
    return tmp_value.bitc.number;
}
GH_INLINE void GH_VO_MIXER0_set_OUTPUT_SYNC_counter(U8 data)
{
    GH_VO_MIXER0_OUTPUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC;
    d.bitc.counter = data;
    *(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OUTPUT_SYNC_counter] <-- 0x%08x\n",
                        REG_VO_MIXER0_OUTPUT_SYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_OUTPUT_SYNC_counter(void)
{
    GH_VO_MIXER0_OUTPUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OUTPUT_SYNC_counter] --> 0x%08x\n",
                        REG_VO_MIXER0_OUTPUT_SYNC,value);
    #endif
    return tmp_value.bitc.counter;
}
GH_INLINE void GH_VO_MIXER0_set_OUTPUT_SYNC_sync(U8 data)
{
    GH_VO_MIXER0_OUTPUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC;
    d.bitc.sync = data;
    *(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OUTPUT_SYNC_sync] <-- 0x%08x\n",
                        REG_VO_MIXER0_OUTPUT_SYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_OUTPUT_SYNC_sync(void)
{
    GH_VO_MIXER0_OUTPUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OUTPUT_SYNC_sync] --> 0x%08x\n",
                        REG_VO_MIXER0_OUTPUT_SYNC,value);
    #endif
    return tmp_value.bitc.sync;
}
GH_INLINE void GH_VO_MIXER0_set_OUTPUT_SYNC_frame(U8 data)
{
    GH_VO_MIXER0_OUTPUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC;
    d.bitc.frame = data;
    *(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_OUTPUT_SYNC_frame] <-- 0x%08x\n",
                        REG_VO_MIXER0_OUTPUT_SYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_OUTPUT_SYNC_frame(void)
{
    GH_VO_MIXER0_OUTPUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_OUTPUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_OUTPUT_SYNC_frame] --> 0x%08x\n",
                        REG_VO_MIXER0_OUTPUT_SYNC,value);
    #endif
    return tmp_value.bitc.frame;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_SMEM_INPUT (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_SMEM_INPUT'. */
void GH_VO_MIXER0_set_SMEM_INPUT(U32 data);
/*! \brief Reads the register 'VO_MIXER0_SMEM_INPUT'. */
U32  GH_VO_MIXER0_get_SMEM_INPUT(void);
/*! \brief Writes the bit group 'luma_number' of register 'VO_MIXER0_SMEM_INPUT'. */
void GH_VO_MIXER0_set_SMEM_INPUT_luma_number(U8 data);
/*! \brief Reads the bit group 'luma_number' of register 'VO_MIXER0_SMEM_INPUT'. */
U8   GH_VO_MIXER0_get_SMEM_INPUT_luma_number(void);
/*! \brief Writes the bit group 'chroma_number' of register 'VO_MIXER0_SMEM_INPUT'. */
void GH_VO_MIXER0_set_SMEM_INPUT_chroma_number(U8 data);
/*! \brief Reads the bit group 'chroma_number' of register 'VO_MIXER0_SMEM_INPUT'. */
U8   GH_VO_MIXER0_get_SMEM_INPUT_chroma_number(void);
/*! \brief Writes the bit group 'osd_number' of register 'VO_MIXER0_SMEM_INPUT'. */
void GH_VO_MIXER0_set_SMEM_INPUT_osd_number(U8 data);
/*! \brief Reads the bit group 'osd_number' of register 'VO_MIXER0_SMEM_INPUT'. */
U8   GH_VO_MIXER0_get_SMEM_INPUT_osd_number(void);
/*! \brief Writes the bit group 'priority' of register 'VO_MIXER0_SMEM_INPUT'. */
void GH_VO_MIXER0_set_SMEM_INPUT_priority(U8 data);
/*! \brief Reads the bit group 'priority' of register 'VO_MIXER0_SMEM_INPUT'. */
U8   GH_VO_MIXER0_get_SMEM_INPUT_priority(void);
/*! \brief Writes the bit group 'video_length' of register 'VO_MIXER0_SMEM_INPUT'. */
void GH_VO_MIXER0_set_SMEM_INPUT_video_length(U8 data);
/*! \brief Reads the bit group 'video_length' of register 'VO_MIXER0_SMEM_INPUT'. */
U8   GH_VO_MIXER0_get_SMEM_INPUT_video_length(void);
/*! \brief Writes the bit group 'osd_length' of register 'VO_MIXER0_SMEM_INPUT'. */
void GH_VO_MIXER0_set_SMEM_INPUT_osd_length(U8 data);
/*! \brief Reads the bit group 'osd_length' of register 'VO_MIXER0_SMEM_INPUT'. */
U8   GH_VO_MIXER0_get_SMEM_INPUT_osd_length(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_SMEM_INPUT(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_SMEM_INPUT] <-- 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_SMEM_INPUT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_SMEM_INPUT] --> 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_SMEM_INPUT_luma_number(U8 data)
{
    GH_VO_MIXER0_SMEM_INPUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT;
    d.bitc.luma_number = data;
    *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_SMEM_INPUT_luma_number] <-- 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_SMEM_INPUT_luma_number(void)
{
    GH_VO_MIXER0_SMEM_INPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_SMEM_INPUT_luma_number] --> 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,value);
    #endif
    return tmp_value.bitc.luma_number;
}
GH_INLINE void GH_VO_MIXER0_set_SMEM_INPUT_chroma_number(U8 data)
{
    GH_VO_MIXER0_SMEM_INPUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT;
    d.bitc.chroma_number = data;
    *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_SMEM_INPUT_chroma_number] <-- 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_SMEM_INPUT_chroma_number(void)
{
    GH_VO_MIXER0_SMEM_INPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_SMEM_INPUT_chroma_number] --> 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,value);
    #endif
    return tmp_value.bitc.chroma_number;
}
GH_INLINE void GH_VO_MIXER0_set_SMEM_INPUT_osd_number(U8 data)
{
    GH_VO_MIXER0_SMEM_INPUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT;
    d.bitc.osd_number = data;
    *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_SMEM_INPUT_osd_number] <-- 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_SMEM_INPUT_osd_number(void)
{
    GH_VO_MIXER0_SMEM_INPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_SMEM_INPUT_osd_number] --> 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,value);
    #endif
    return tmp_value.bitc.osd_number;
}
GH_INLINE void GH_VO_MIXER0_set_SMEM_INPUT_priority(U8 data)
{
    GH_VO_MIXER0_SMEM_INPUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT;
    d.bitc.priority = data;
    *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_SMEM_INPUT_priority] <-- 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_SMEM_INPUT_priority(void)
{
    GH_VO_MIXER0_SMEM_INPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_SMEM_INPUT_priority] --> 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,value);
    #endif
    return tmp_value.bitc.priority;
}
GH_INLINE void GH_VO_MIXER0_set_SMEM_INPUT_video_length(U8 data)
{
    GH_VO_MIXER0_SMEM_INPUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT;
    d.bitc.video_length = data;
    *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_SMEM_INPUT_video_length] <-- 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_SMEM_INPUT_video_length(void)
{
    GH_VO_MIXER0_SMEM_INPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_SMEM_INPUT_video_length] --> 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,value);
    #endif
    return tmp_value.bitc.video_length;
}
GH_INLINE void GH_VO_MIXER0_set_SMEM_INPUT_osd_length(U8 data)
{
    GH_VO_MIXER0_SMEM_INPUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT;
    d.bitc.osd_length = data;
    *(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_SMEM_INPUT_osd_length] <-- 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_SMEM_INPUT_osd_length(void)
{
    GH_VO_MIXER0_SMEM_INPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_SMEM_INPUT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_SMEM_INPUT_osd_length] --> 0x%08x\n",
                        REG_VO_MIXER0_SMEM_INPUT,value);
    #endif
    return tmp_value.bitc.osd_length;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_SMEM_OUT (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_SMEM_OUT'. */
void GH_VO_MIXER0_set_SMEM_OUT(U32 data);
/*! \brief Reads the register 'VO_MIXER0_SMEM_OUT'. */
U32  GH_VO_MIXER0_get_SMEM_OUT(void);
/*! \brief Writes the bit group 'luma_number' of register 'VO_MIXER0_SMEM_OUT'. */
void GH_VO_MIXER0_set_SMEM_OUT_luma_number(U8 data);
/*! \brief Reads the bit group 'luma_number' of register 'VO_MIXER0_SMEM_OUT'. */
U8   GH_VO_MIXER0_get_SMEM_OUT_luma_number(void);
/*! \brief Writes the bit group 'chroma_number' of register 'VO_MIXER0_SMEM_OUT'. */
void GH_VO_MIXER0_set_SMEM_OUT_chroma_number(U8 data);
/*! \brief Reads the bit group 'chroma_number' of register 'VO_MIXER0_SMEM_OUT'. */
U8   GH_VO_MIXER0_get_SMEM_OUT_chroma_number(void);
/*! \brief Writes the bit group 'priority' of register 'VO_MIXER0_SMEM_OUT'. */
void GH_VO_MIXER0_set_SMEM_OUT_priority(U8 data);
/*! \brief Reads the bit group 'priority' of register 'VO_MIXER0_SMEM_OUT'. */
U8   GH_VO_MIXER0_get_SMEM_OUT_priority(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_SMEM_OUT(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_SMEM_OUT = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_SMEM_OUT] <-- 0x%08x\n",
                        REG_VO_MIXER0_SMEM_OUT,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_SMEM_OUT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_SMEM_OUT);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_SMEM_OUT] --> 0x%08x\n",
                        REG_VO_MIXER0_SMEM_OUT,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_SMEM_OUT_luma_number(U8 data)
{
    GH_VO_MIXER0_SMEM_OUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_SMEM_OUT;
    d.bitc.luma_number = data;
    *(volatile U32 *)REG_VO_MIXER0_SMEM_OUT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_SMEM_OUT_luma_number] <-- 0x%08x\n",
                        REG_VO_MIXER0_SMEM_OUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_SMEM_OUT_luma_number(void)
{
    GH_VO_MIXER0_SMEM_OUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_SMEM_OUT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_SMEM_OUT_luma_number] --> 0x%08x\n",
                        REG_VO_MIXER0_SMEM_OUT,value);
    #endif
    return tmp_value.bitc.luma_number;
}
GH_INLINE void GH_VO_MIXER0_set_SMEM_OUT_chroma_number(U8 data)
{
    GH_VO_MIXER0_SMEM_OUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_SMEM_OUT;
    d.bitc.chroma_number = data;
    *(volatile U32 *)REG_VO_MIXER0_SMEM_OUT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_SMEM_OUT_chroma_number] <-- 0x%08x\n",
                        REG_VO_MIXER0_SMEM_OUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_SMEM_OUT_chroma_number(void)
{
    GH_VO_MIXER0_SMEM_OUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_SMEM_OUT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_SMEM_OUT_chroma_number] --> 0x%08x\n",
                        REG_VO_MIXER0_SMEM_OUT,value);
    #endif
    return tmp_value.bitc.chroma_number;
}
GH_INLINE void GH_VO_MIXER0_set_SMEM_OUT_priority(U8 data)
{
    GH_VO_MIXER0_SMEM_OUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_SMEM_OUT;
    d.bitc.priority = data;
    *(volatile U32 *)REG_VO_MIXER0_SMEM_OUT = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_SMEM_OUT_priority] <-- 0x%08x\n",
                        REG_VO_MIXER0_SMEM_OUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_SMEM_OUT_priority(void)
{
    GH_VO_MIXER0_SMEM_OUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_SMEM_OUT);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_SMEM_OUT_priority] --> 0x%08x\n",
                        REG_VO_MIXER0_SMEM_OUT,value);
    #endif
    return tmp_value.bitc.priority;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_FRAME_ENABLE (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_FRAME_ENABLE'. */
void GH_VO_MIXER0_set_FRAME_ENABLE(U32 data);
/*! \brief Reads the register 'VO_MIXER0_FRAME_ENABLE'. */
U32  GH_VO_MIXER0_get_FRAME_ENABLE(void);
/*! \brief Writes the bit group 'enable' of register 'VO_MIXER0_FRAME_ENABLE'. */
void GH_VO_MIXER0_set_FRAME_ENABLE_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_MIXER0_FRAME_ENABLE'. */
U8   GH_VO_MIXER0_get_FRAME_ENABLE_enable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_FRAME_ENABLE(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER0_FRAME_ENABLE = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_FRAME_ENABLE] <-- 0x%08x\n",
                        REG_VO_MIXER0_FRAME_ENABLE,data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_FRAME_ENABLE(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_FRAME_ENABLE);

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_FRAME_ENABLE] --> 0x%08x\n",
                        REG_VO_MIXER0_FRAME_ENABLE,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_MIXER0_set_FRAME_ENABLE_enable(U8 data)
{
    GH_VO_MIXER0_FRAME_ENABLE_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER0_FRAME_ENABLE;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_MIXER0_FRAME_ENABLE = d.all;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_FRAME_ENABLE_enable] <-- 0x%08x\n",
                        REG_VO_MIXER0_FRAME_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_MIXER0_get_FRAME_ENABLE_enable(void)
{
    GH_VO_MIXER0_FRAME_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER0_FRAME_ENABLE);

    tmp_value.all = value;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_FRAME_ENABLE_enable] --> 0x%08x\n",
                        REG_VO_MIXER0_FRAME_ENABLE,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER0_CLUT_A (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_MIXER0_CLUT_A'. */
void GH_VO_MIXER0_set_CLUT_A(U16 index, U32 data);
/*! \brief Reads the register 'VO_MIXER0_CLUT_A'. */
U32  GH_VO_MIXER0_get_CLUT_A(U16 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_MIXER0_set_CLUT_A(U16 index, U32 data)
{
    *(volatile U32 *)(REG_VO_MIXER0_CLUT_A + index * FIO_MOFFSET(VO_MIXER0,0x00000004)) = data;
    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER0_set_CLUT_A] <-- 0x%08x\n",
                        (REG_VO_MIXER0_CLUT_A + index * FIO_MOFFSET(VO_MIXER0,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_VO_MIXER0_get_CLUT_A(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_VO_MIXER0_CLUT_A + index * FIO_MOFFSET(VO_MIXER0,0x00000004)));

    #if GH_VO_MIXER0_ENABLE_DEBUG_PRINT
    GH_VO_MIXER0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER0_get_CLUT_A] --> 0x%08x\n",
                        (REG_VO_MIXER0_CLUT_A + index * FIO_MOFFSET(VO_MIXER0,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_MIXER0_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_MIXER0_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

