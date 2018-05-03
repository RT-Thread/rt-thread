/*!
*******************************************************************************
**
** \file      gh_vo_mixer.h
**
** \brief     VO Mixer access function.
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
#ifndef _GH_VO_MIXER_H
#define _GH_VO_MIXER_H

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

#define GH_VO_MIXER_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VO_MIXER_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VO_MIXER_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VO_MIXER_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_MIXER_CONTROL                                FIO_ADDRESS(VO_MIXER,0x90008500) /* read/write */
#define REG_VO_MIXER_STATUS                                 FIO_ADDRESS(VO_MIXER,0x90008504) /* read */
#define REG_VO_MIXER_ACTIVE_SIZE                            FIO_ADDRESS(VO_MIXER,0x90008508) /* read/write */
#define REG_VO_MIXER_VIDEO_START                            FIO_ADDRESS(VO_MIXER,0x9000850C) /* read/write */
#define REG_VO_MIXER_VIDEO_END                              FIO_ADDRESS(VO_MIXER,0x90008510) /* read/write */
#define REG_VO_MIXER_OSD_START                              FIO_ADDRESS(VO_MIXER,0x9000851C) /* read/write */
#define REG_VO_MIXER_OSD_END                                FIO_ADDRESS(VO_MIXER,0x90008520) /* read/write */
#define REG_VO_MIXER_BACKGROUND                             FIO_ADDRESS(VO_MIXER,0x90008524) /* read/write */
#define REG_VO_MIXER_HIGHLIGHT                              FIO_ADDRESS(VO_MIXER,0x90008528) /* read/write */
#define REG_VO_MIXER_OSD_CONTROL                            FIO_ADDRESS(VO_MIXER,0x9000852C) /* read/write */
#define REG_VO_MIXER_ENABLE_CTRL                            FIO_ADDRESS(VO_MIXER,0x90008550) /* read/write */
#define REG_VO_MIXER_INPUT_VIDEO_SYNC                       FIO_ADDRESS(VO_MIXER,0x90008554) /* read/write */
#define REG_VO_MIXER_OUTPUT_SYNC                            FIO_ADDRESS(VO_MIXER,0x9000855C) /* read/write */
#define REG_VO_MIXER_SMEM_INPUT                             FIO_ADDRESS(VO_MIXER,0x90008560) /* read/write */
#define REG_VO_MIXER_SMEM_OUT                               FIO_ADDRESS(VO_MIXER,0x90008568) /* read/write */
#define REG_VO_MIXER_FRAME_ENABLE                           FIO_ADDRESS(VO_MIXER,0x9000856C) /* read/write */
#define REG_VO_MIXER_CLUT_B                                 FIO_ADDRESS(VO_MIXER,0x90009400) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_MIXER_CONTROL */
    U32 all;
    struct {
        U32                             : 31;
        U32 reset                       : 1;
    } bitc;
} GH_VO_MIXER_CONTROL_S;

typedef union { /* VO_MIXER_STATUS */
    U32 all;
    struct {
        U32                             : 31;
        U32 reset                       : 1;
    } bitc;
} GH_VO_MIXER_STATUS_S;

typedef union { /* VO_MIXER_ACTIVE_SIZE */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER_ACTIVE_SIZE_S;

typedef union { /* VO_MIXER_VIDEO_START */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER_VIDEO_START_S;

typedef union { /* VO_MIXER_VIDEO_END */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER_VIDEO_END_S;

typedef union { /* VO_MIXER_OSD_START */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER_OSD_START_S;

typedef union { /* VO_MIXER_OSD_END */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER_OSD_END_S;

typedef union { /* VO_MIXER_BACKGROUND */
    U32 all;
    struct {
        U32 v                           : 8;
        U32 u                           : 8;
        U32 y                           : 8;
        U32                             : 8;
    } bitc;
} GH_VO_MIXER_BACKGROUND_S;

typedef union { /* VO_MIXER_HIGHLIGHT */
    U32 all;
    struct {
        U32 v                           : 8;
        U32 u                           : 8;
        U32 y                           : 8;
        U32 threshold                   : 8;
    } bitc;
} GH_VO_MIXER_HIGHLIGHT_S;

typedef union { /* VO_MIXER_OSD_CONTROL */
    U32 all;
    struct {
        U32 global_blend                : 8;
        U32 premultiplied               : 1;
        U32 mode                        : 3;
        U32 enable_transparent_color    : 1;
        U32                             : 3;
        U32 transparent_color           : 16;
    } bitc;
} GH_VO_MIXER_OSD_CONTROL_S;

typedef union { /* VO_MIXER_ENABLE_CTRL */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32 mapped_direct               : 2;
        U32 smem                        : 1;
        U32 display                     : 1;
        U32                             : 27;
    } bitc;
} GH_VO_MIXER_ENABLE_CTRL_S;

typedef union { /* VO_MIXER_INPUT_VIDEO_SYNC */
    U32 all;
    struct {
        U32 sync_mode                   : 2;
        U32 line                        : 3;
        U32 video                       : 6;
        U32 decrement                   : 1;
        U32                             : 20;
    } bitc;
} GH_VO_MIXER_INPUT_VIDEO_SYNC_S;

typedef union { /* VO_MIXER_OUTPUT_SYNC */
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
} GH_VO_MIXER_OUTPUT_SYNC_S;

typedef union { /* VO_MIXER_SMEM_INPUT */
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
} GH_VO_MIXER_SMEM_INPUT_S;

typedef union { /* VO_MIXER_SMEM_OUT */
    U32 all;
    struct {
        U32 luma_number                 : 8;
        U32 chroma_number               : 8;
        U32 priority                    : 2;
        U32                             : 14;
    } bitc;
} GH_VO_MIXER_SMEM_OUT_S;

typedef union { /* VO_MIXER_FRAME_ENABLE */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_MIXER_FRAME_ENABLE_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_CONTROL (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_CONTROL'. */
void GH_VO_MIXER_set_CONTROL(U32 data);
/*! \brief Reads the register 'VO_MIXER_CONTROL'. */
U32  GH_VO_MIXER_get_CONTROL(void);
/*! \brief Writes the bit group 'Reset' of register 'VO_MIXER_CONTROL'. */
void GH_VO_MIXER_set_CONTROL_Reset(U8 data);
/*! \brief Reads the bit group 'Reset' of register 'VO_MIXER_CONTROL'. */
U8   GH_VO_MIXER_get_CONTROL_Reset(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_STATUS (read)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VO_MIXER_STATUS'. */
U32  GH_VO_MIXER_get_STATUS(void);
/*! \brief Reads the bit group 'Reset' of register 'VO_MIXER_STATUS'. */
U8   GH_VO_MIXER_get_STATUS_Reset(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_ACTIVE_SIZE (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_ACTIVE_SIZE'. */
void GH_VO_MIXER_set_ACTIVE_SIZE(U32 data);
/*! \brief Reads the register 'VO_MIXER_ACTIVE_SIZE'. */
U32  GH_VO_MIXER_get_ACTIVE_SIZE(void);
/*! \brief Writes the bit group 'Vertical' of register 'VO_MIXER_ACTIVE_SIZE'. */
void GH_VO_MIXER_set_ACTIVE_SIZE_Vertical(U16 data);
/*! \brief Reads the bit group 'Vertical' of register 'VO_MIXER_ACTIVE_SIZE'. */
U16  GH_VO_MIXER_get_ACTIVE_SIZE_Vertical(void);
/*! \brief Writes the bit group 'Horizontal' of register 'VO_MIXER_ACTIVE_SIZE'. */
void GH_VO_MIXER_set_ACTIVE_SIZE_Horizontal(U16 data);
/*! \brief Reads the bit group 'Horizontal' of register 'VO_MIXER_ACTIVE_SIZE'. */
U16  GH_VO_MIXER_get_ACTIVE_SIZE_Horizontal(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_VIDEO_START (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_VIDEO_START'. */
void GH_VO_MIXER_set_VIDEO_START(U32 data);
/*! \brief Reads the register 'VO_MIXER_VIDEO_START'. */
U32  GH_VO_MIXER_get_VIDEO_START(void);
/*! \brief Writes the bit group 'Vertical' of register 'VO_MIXER_VIDEO_START'. */
void GH_VO_MIXER_set_VIDEO_START_Vertical(U16 data);
/*! \brief Reads the bit group 'Vertical' of register 'VO_MIXER_VIDEO_START'. */
U16  GH_VO_MIXER_get_VIDEO_START_Vertical(void);
/*! \brief Writes the bit group 'Horizontal' of register 'VO_MIXER_VIDEO_START'. */
void GH_VO_MIXER_set_VIDEO_START_Horizontal(U16 data);
/*! \brief Reads the bit group 'Horizontal' of register 'VO_MIXER_VIDEO_START'. */
U16  GH_VO_MIXER_get_VIDEO_START_Horizontal(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_VIDEO_END (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_VIDEO_END'. */
void GH_VO_MIXER_set_VIDEO_END(U32 data);
/*! \brief Reads the register 'VO_MIXER_VIDEO_END'. */
U32  GH_VO_MIXER_get_VIDEO_END(void);
/*! \brief Writes the bit group 'Vertical' of register 'VO_MIXER_VIDEO_END'. */
void GH_VO_MIXER_set_VIDEO_END_Vertical(U16 data);
/*! \brief Reads the bit group 'Vertical' of register 'VO_MIXER_VIDEO_END'. */
U16  GH_VO_MIXER_get_VIDEO_END_Vertical(void);
/*! \brief Writes the bit group 'Horizontal' of register 'VO_MIXER_VIDEO_END'. */
void GH_VO_MIXER_set_VIDEO_END_Horizontal(U16 data);
/*! \brief Reads the bit group 'Horizontal' of register 'VO_MIXER_VIDEO_END'. */
U16  GH_VO_MIXER_get_VIDEO_END_Horizontal(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_OSD_START (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_OSD_START'. */
void GH_VO_MIXER_set_OSD_START(U32 data);
/*! \brief Reads the register 'VO_MIXER_OSD_START'. */
U32  GH_VO_MIXER_get_OSD_START(void);
/*! \brief Writes the bit group 'Vertical' of register 'VO_MIXER_OSD_START'. */
void GH_VO_MIXER_set_OSD_START_Vertical(U16 data);
/*! \brief Reads the bit group 'Vertical' of register 'VO_MIXER_OSD_START'. */
U16  GH_VO_MIXER_get_OSD_START_Vertical(void);
/*! \brief Writes the bit group 'Horizontal' of register 'VO_MIXER_OSD_START'. */
void GH_VO_MIXER_set_OSD_START_Horizontal(U16 data);
/*! \brief Reads the bit group 'Horizontal' of register 'VO_MIXER_OSD_START'. */
U16  GH_VO_MIXER_get_OSD_START_Horizontal(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_OSD_END (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_OSD_END'. */
void GH_VO_MIXER_set_OSD_END(U32 data);
/*! \brief Reads the register 'VO_MIXER_OSD_END'. */
U32  GH_VO_MIXER_get_OSD_END(void);
/*! \brief Writes the bit group 'Vertical' of register 'VO_MIXER_OSD_END'. */
void GH_VO_MIXER_set_OSD_END_Vertical(U16 data);
/*! \brief Reads the bit group 'Vertical' of register 'VO_MIXER_OSD_END'. */
U16  GH_VO_MIXER_get_OSD_END_Vertical(void);
/*! \brief Writes the bit group 'Horizontal' of register 'VO_MIXER_OSD_END'. */
void GH_VO_MIXER_set_OSD_END_Horizontal(U16 data);
/*! \brief Reads the bit group 'Horizontal' of register 'VO_MIXER_OSD_END'. */
U16  GH_VO_MIXER_get_OSD_END_Horizontal(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_BACKGROUND (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_BACKGROUND'. */
void GH_VO_MIXER_set_BACKGROUND(U32 data);
/*! \brief Reads the register 'VO_MIXER_BACKGROUND'. */
U32  GH_VO_MIXER_get_BACKGROUND(void);
/*! \brief Writes the bit group 'V' of register 'VO_MIXER_BACKGROUND'. */
void GH_VO_MIXER_set_BACKGROUND_V(U8 data);
/*! \brief Reads the bit group 'V' of register 'VO_MIXER_BACKGROUND'. */
U8   GH_VO_MIXER_get_BACKGROUND_V(void);
/*! \brief Writes the bit group 'U' of register 'VO_MIXER_BACKGROUND'. */
void GH_VO_MIXER_set_BACKGROUND_U(U8 data);
/*! \brief Reads the bit group 'U' of register 'VO_MIXER_BACKGROUND'. */
U8   GH_VO_MIXER_get_BACKGROUND_U(void);
/*! \brief Writes the bit group 'Y' of register 'VO_MIXER_BACKGROUND'. */
void GH_VO_MIXER_set_BACKGROUND_Y(U8 data);
/*! \brief Reads the bit group 'Y' of register 'VO_MIXER_BACKGROUND'. */
U8   GH_VO_MIXER_get_BACKGROUND_Y(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_HIGHLIGHT (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_HIGHLIGHT'. */
void GH_VO_MIXER_set_HIGHLIGHT(U32 data);
/*! \brief Reads the register 'VO_MIXER_HIGHLIGHT'. */
U32  GH_VO_MIXER_get_HIGHLIGHT(void);
/*! \brief Writes the bit group 'V' of register 'VO_MIXER_HIGHLIGHT'. */
void GH_VO_MIXER_set_HIGHLIGHT_V(U8 data);
/*! \brief Reads the bit group 'V' of register 'VO_MIXER_HIGHLIGHT'. */
U8   GH_VO_MIXER_get_HIGHLIGHT_V(void);
/*! \brief Writes the bit group 'U' of register 'VO_MIXER_HIGHLIGHT'. */
void GH_VO_MIXER_set_HIGHLIGHT_U(U8 data);
/*! \brief Reads the bit group 'U' of register 'VO_MIXER_HIGHLIGHT'. */
U8   GH_VO_MIXER_get_HIGHLIGHT_U(void);
/*! \brief Writes the bit group 'Y' of register 'VO_MIXER_HIGHLIGHT'. */
void GH_VO_MIXER_set_HIGHLIGHT_Y(U8 data);
/*! \brief Reads the bit group 'Y' of register 'VO_MIXER_HIGHLIGHT'. */
U8   GH_VO_MIXER_get_HIGHLIGHT_Y(void);
/*! \brief Writes the bit group 'threshold' of register 'VO_MIXER_HIGHLIGHT'. */
void GH_VO_MIXER_set_HIGHLIGHT_threshold(U8 data);
/*! \brief Reads the bit group 'threshold' of register 'VO_MIXER_HIGHLIGHT'. */
U8   GH_VO_MIXER_get_HIGHLIGHT_threshold(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_OSD_CONTROL (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_OSD_CONTROL'. */
void GH_VO_MIXER_set_OSD_CONTROL(U32 data);
/*! \brief Reads the register 'VO_MIXER_OSD_CONTROL'. */
U32  GH_VO_MIXER_get_OSD_CONTROL(void);
/*! \brief Writes the bit group 'Global_Blend' of register 'VO_MIXER_OSD_CONTROL'. */
void GH_VO_MIXER_set_OSD_CONTROL_Global_Blend(U8 data);
/*! \brief Reads the bit group 'Global_Blend' of register 'VO_MIXER_OSD_CONTROL'. */
U8   GH_VO_MIXER_get_OSD_CONTROL_Global_Blend(void);
/*! \brief Writes the bit group 'Premultiplied' of register 'VO_MIXER_OSD_CONTROL'. */
void GH_VO_MIXER_set_OSD_CONTROL_Premultiplied(U8 data);
/*! \brief Reads the bit group 'Premultiplied' of register 'VO_MIXER_OSD_CONTROL'. */
U8   GH_VO_MIXER_get_OSD_CONTROL_Premultiplied(void);
/*! \brief Writes the bit group 'Mode' of register 'VO_MIXER_OSD_CONTROL'. */
void GH_VO_MIXER_set_OSD_CONTROL_Mode(U8 data);
/*! \brief Reads the bit group 'Mode' of register 'VO_MIXER_OSD_CONTROL'. */
U8   GH_VO_MIXER_get_OSD_CONTROL_Mode(void);
/*! \brief Writes the bit group 'Enable_Transparent_Color' of register 'VO_MIXER_OSD_CONTROL'. */
void GH_VO_MIXER_set_OSD_CONTROL_Enable_Transparent_Color(U8 data);
/*! \brief Reads the bit group 'Enable_Transparent_Color' of register 'VO_MIXER_OSD_CONTROL'. */
U8   GH_VO_MIXER_get_OSD_CONTROL_Enable_Transparent_Color(void);
/*! \brief Writes the bit group 'Transparent_Color' of register 'VO_MIXER_OSD_CONTROL'. */
void GH_VO_MIXER_set_OSD_CONTROL_Transparent_Color(U16 data);
/*! \brief Reads the bit group 'Transparent_Color' of register 'VO_MIXER_OSD_CONTROL'. */
U16  GH_VO_MIXER_get_OSD_CONTROL_Transparent_Color(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_ENABLE_CTRL (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_ENABLE_CTRL'. */
void GH_VO_MIXER_set_ENABLE_CTRL(U32 data);
/*! \brief Reads the register 'VO_MIXER_ENABLE_CTRL'. */
U32  GH_VO_MIXER_get_ENABLE_CTRL(void);
/*! \brief Writes the bit group 'enable' of register 'VO_MIXER_ENABLE_CTRL'. */
void GH_VO_MIXER_set_ENABLE_CTRL_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_MIXER_ENABLE_CTRL'. */
U8   GH_VO_MIXER_get_ENABLE_CTRL_enable(void);
/*! \brief Writes the bit group 'mapped_direct' of register 'VO_MIXER_ENABLE_CTRL'. */
void GH_VO_MIXER_set_ENABLE_CTRL_mapped_direct(U8 data);
/*! \brief Reads the bit group 'mapped_direct' of register 'VO_MIXER_ENABLE_CTRL'. */
U8   GH_VO_MIXER_get_ENABLE_CTRL_mapped_direct(void);
/*! \brief Writes the bit group 'smem' of register 'VO_MIXER_ENABLE_CTRL'. */
void GH_VO_MIXER_set_ENABLE_CTRL_smem(U8 data);
/*! \brief Reads the bit group 'smem' of register 'VO_MIXER_ENABLE_CTRL'. */
U8   GH_VO_MIXER_get_ENABLE_CTRL_smem(void);
/*! \brief Writes the bit group 'display' of register 'VO_MIXER_ENABLE_CTRL'. */
void GH_VO_MIXER_set_ENABLE_CTRL_display(U8 data);
/*! \brief Reads the bit group 'display' of register 'VO_MIXER_ENABLE_CTRL'. */
U8   GH_VO_MIXER_get_ENABLE_CTRL_display(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_INPUT_VIDEO_SYNC (read/write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_INPUT_VIDEO_SYNC'. */
void GH_VO_MIXER_set_INPUT_VIDEO_SYNC(U32 data);
/*! \brief Reads the register 'VO_MIXER_INPUT_VIDEO_SYNC'. */
U32  GH_VO_MIXER_get_INPUT_VIDEO_SYNC(void);
/*! \brief Writes the bit group 'sync_mode' of register 'VO_MIXER_INPUT_VIDEO_SYNC'. */
void GH_VO_MIXER_set_INPUT_VIDEO_SYNC_sync_mode(U8 data);
/*! \brief Reads the bit group 'sync_mode' of register 'VO_MIXER_INPUT_VIDEO_SYNC'. */
U8   GH_VO_MIXER_get_INPUT_VIDEO_SYNC_sync_mode(void);
/*! \brief Writes the bit group 'line' of register 'VO_MIXER_INPUT_VIDEO_SYNC'. */
void GH_VO_MIXER_set_INPUT_VIDEO_SYNC_line(U8 data);
/*! \brief Reads the bit group 'line' of register 'VO_MIXER_INPUT_VIDEO_SYNC'. */
U8   GH_VO_MIXER_get_INPUT_VIDEO_SYNC_line(void);
/*! \brief Writes the bit group 'video' of register 'VO_MIXER_INPUT_VIDEO_SYNC'. */
void GH_VO_MIXER_set_INPUT_VIDEO_SYNC_video(U8 data);
/*! \brief Reads the bit group 'video' of register 'VO_MIXER_INPUT_VIDEO_SYNC'. */
U8   GH_VO_MIXER_get_INPUT_VIDEO_SYNC_video(void);
/*! \brief Writes the bit group 'decrement' of register 'VO_MIXER_INPUT_VIDEO_SYNC'. */
void GH_VO_MIXER_set_INPUT_VIDEO_SYNC_decrement(U8 data);
/*! \brief Reads the bit group 'decrement' of register 'VO_MIXER_INPUT_VIDEO_SYNC'. */
U8   GH_VO_MIXER_get_INPUT_VIDEO_SYNC_decrement(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_OUTPUT_SYNC (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_OUTPUT_SYNC'. */
void GH_VO_MIXER_set_OUTPUT_SYNC(U32 data);
/*! \brief Reads the register 'VO_MIXER_OUTPUT_SYNC'. */
U32  GH_VO_MIXER_get_OUTPUT_SYNC(void);
/*! \brief Writes the bit group 'sync_mode' of register 'VO_MIXER_OUTPUT_SYNC'. */
void GH_VO_MIXER_set_OUTPUT_SYNC_sync_mode(U8 data);
/*! \brief Reads the bit group 'sync_mode' of register 'VO_MIXER_OUTPUT_SYNC'. */
U8   GH_VO_MIXER_get_OUTPUT_SYNC_sync_mode(void);
/*! \brief Writes the bit group 'number' of register 'VO_MIXER_OUTPUT_SYNC'. */
void GH_VO_MIXER_set_OUTPUT_SYNC_number(U8 data);
/*! \brief Reads the bit group 'number' of register 'VO_MIXER_OUTPUT_SYNC'. */
U8   GH_VO_MIXER_get_OUTPUT_SYNC_number(void);
/*! \brief Writes the bit group 'counter' of register 'VO_MIXER_OUTPUT_SYNC'. */
void GH_VO_MIXER_set_OUTPUT_SYNC_counter(U8 data);
/*! \brief Reads the bit group 'counter' of register 'VO_MIXER_OUTPUT_SYNC'. */
U8   GH_VO_MIXER_get_OUTPUT_SYNC_counter(void);
/*! \brief Writes the bit group 'sync' of register 'VO_MIXER_OUTPUT_SYNC'. */
void GH_VO_MIXER_set_OUTPUT_SYNC_sync(U8 data);
/*! \brief Reads the bit group 'sync' of register 'VO_MIXER_OUTPUT_SYNC'. */
U8   GH_VO_MIXER_get_OUTPUT_SYNC_sync(void);
/*! \brief Writes the bit group 'frame' of register 'VO_MIXER_OUTPUT_SYNC'. */
void GH_VO_MIXER_set_OUTPUT_SYNC_frame(U8 data);
/*! \brief Reads the bit group 'frame' of register 'VO_MIXER_OUTPUT_SYNC'. */
U8   GH_VO_MIXER_get_OUTPUT_SYNC_frame(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_SMEM_INPUT (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_SMEM_INPUT'. */
void GH_VO_MIXER_set_SMEM_INPUT(U32 data);
/*! \brief Reads the register 'VO_MIXER_SMEM_INPUT'. */
U32  GH_VO_MIXER_get_SMEM_INPUT(void);
/*! \brief Writes the bit group 'luma_number' of register 'VO_MIXER_SMEM_INPUT'. */
void GH_VO_MIXER_set_SMEM_INPUT_luma_number(U8 data);
/*! \brief Reads the bit group 'luma_number' of register 'VO_MIXER_SMEM_INPUT'. */
U8   GH_VO_MIXER_get_SMEM_INPUT_luma_number(void);
/*! \brief Writes the bit group 'chroma_number' of register 'VO_MIXER_SMEM_INPUT'. */
void GH_VO_MIXER_set_SMEM_INPUT_chroma_number(U8 data);
/*! \brief Reads the bit group 'chroma_number' of register 'VO_MIXER_SMEM_INPUT'. */
U8   GH_VO_MIXER_get_SMEM_INPUT_chroma_number(void);
/*! \brief Writes the bit group 'osd_number' of register 'VO_MIXER_SMEM_INPUT'. */
void GH_VO_MIXER_set_SMEM_INPUT_osd_number(U8 data);
/*! \brief Reads the bit group 'osd_number' of register 'VO_MIXER_SMEM_INPUT'. */
U8   GH_VO_MIXER_get_SMEM_INPUT_osd_number(void);
/*! \brief Writes the bit group 'priority' of register 'VO_MIXER_SMEM_INPUT'. */
void GH_VO_MIXER_set_SMEM_INPUT_priority(U8 data);
/*! \brief Reads the bit group 'priority' of register 'VO_MIXER_SMEM_INPUT'. */
U8   GH_VO_MIXER_get_SMEM_INPUT_priority(void);
/*! \brief Writes the bit group 'video_length' of register 'VO_MIXER_SMEM_INPUT'. */
void GH_VO_MIXER_set_SMEM_INPUT_video_length(U8 data);
/*! \brief Reads the bit group 'video_length' of register 'VO_MIXER_SMEM_INPUT'. */
U8   GH_VO_MIXER_get_SMEM_INPUT_video_length(void);
/*! \brief Writes the bit group 'osd_length' of register 'VO_MIXER_SMEM_INPUT'. */
void GH_VO_MIXER_set_SMEM_INPUT_osd_length(U8 data);
/*! \brief Reads the bit group 'osd_length' of register 'VO_MIXER_SMEM_INPUT'. */
U8   GH_VO_MIXER_get_SMEM_INPUT_osd_length(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_SMEM_OUT (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_SMEM_OUT'. */
void GH_VO_MIXER_set_SMEM_OUT(U32 data);
/*! \brief Reads the register 'VO_MIXER_SMEM_OUT'. */
U32  GH_VO_MIXER_get_SMEM_OUT(void);
/*! \brief Writes the bit group 'luma_number' of register 'VO_MIXER_SMEM_OUT'. */
void GH_VO_MIXER_set_SMEM_OUT_luma_number(U8 data);
/*! \brief Reads the bit group 'luma_number' of register 'VO_MIXER_SMEM_OUT'. */
U8   GH_VO_MIXER_get_SMEM_OUT_luma_number(void);
/*! \brief Writes the bit group 'chroma_number' of register 'VO_MIXER_SMEM_OUT'. */
void GH_VO_MIXER_set_SMEM_OUT_chroma_number(U8 data);
/*! \brief Reads the bit group 'chroma_number' of register 'VO_MIXER_SMEM_OUT'. */
U8   GH_VO_MIXER_get_SMEM_OUT_chroma_number(void);
/*! \brief Writes the bit group 'priority' of register 'VO_MIXER_SMEM_OUT'. */
void GH_VO_MIXER_set_SMEM_OUT_priority(U8 data);
/*! \brief Reads the bit group 'priority' of register 'VO_MIXER_SMEM_OUT'. */
U8   GH_VO_MIXER_get_SMEM_OUT_priority(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_FRAME_ENABLE (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_FRAME_ENABLE'. */
void GH_VO_MIXER_set_FRAME_ENABLE(U32 data);
/*! \brief Reads the register 'VO_MIXER_FRAME_ENABLE'. */
U32  GH_VO_MIXER_get_FRAME_ENABLE(void);
/*! \brief Writes the bit group 'enable' of register 'VO_MIXER_FRAME_ENABLE'. */
void GH_VO_MIXER_set_FRAME_ENABLE_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_MIXER_FRAME_ENABLE'. */
U8   GH_VO_MIXER_get_FRAME_ENABLE_enable(void);

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_CLUT_B (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_MIXER_CLUT_B'. */
void GH_VO_MIXER_set_CLUT_B(U16 index, U32 data);
/*! \brief Reads the register 'VO_MIXER_CLUT_B'. */
U32  GH_VO_MIXER_get_CLUT_B(U16 index);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_MIXER_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_vo_mixer.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_MIXER_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

