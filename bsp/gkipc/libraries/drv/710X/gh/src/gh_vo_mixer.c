/******************************************************************************
**
** \file      gh_vo_mixer.c
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
#ifndef SRC_INLINE
#include "gh_vo_mixer.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_MIXER_CONTROL_REAL                           FIO_ADDRESS(VO_MIXER,0x60008500) /* read/write */
#define REG_VO_MIXER_STATUS_REAL                            FIO_ADDRESS(VO_MIXER,0x60008504) /* read */
#define REG_VO_MIXER_ACTIVE_SIZE_REAL                       FIO_ADDRESS(VO_MIXER,0x60008508) /* read/write */
#define REG_VO_MIXER_VIDEO_START_REAL                       FIO_ADDRESS(VO_MIXER,0x6000850C) /* read/write */
#define REG_VO_MIXER_VIDEO_END_REAL                         FIO_ADDRESS(VO_MIXER,0x60008510) /* read/write */
#define REG_VO_MIXER_OSD_START_REAL                         FIO_ADDRESS(VO_MIXER,0x6000851C) /* read/write */
#define REG_VO_MIXER_OSD_END_REAL                           FIO_ADDRESS(VO_MIXER,0x60008520) /* read/write */
#define REG_VO_MIXER_BACKGROUND_REAL                        FIO_ADDRESS(VO_MIXER,0x60008524) /* read/write */
#define REG_VO_MIXER_HIGHLIGHT_REAL                         FIO_ADDRESS(VO_MIXER,0x60008528) /* read/write */
#define REG_VO_MIXER_OSD_CONTROL_REAL                       FIO_ADDRESS(VO_MIXER,0x6000852C) /* read/write */
#define REG_VO_MIXER_ENABLE_CTRL_REAL                       FIO_ADDRESS(VO_MIXER,0x60008550) /* read/write */
#define REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL                  FIO_ADDRESS(VO_MIXER,0x60008554) /* read/write */
#define REG_VO_MIXER_OUTPUT_SYNC_REAL                       FIO_ADDRESS(VO_MIXER,0x6000855C) /* read/write */
#define REG_VO_MIXER_SMEM_INPUT_REAL                        FIO_ADDRESS(VO_MIXER,0x60008560) /* read/write */
#define REG_VO_MIXER_SMEM_OUT_REAL                          FIO_ADDRESS(VO_MIXER,0x60008568) /* read/write */
#define REG_VO_MIXER_FRAME_ENABLE_REAL                      FIO_ADDRESS(VO_MIXER,0x6000856C) /* read/write */
#define REG_VO_MIXER_CLUT_B_REAL                            FIO_ADDRESS(VO_MIXER,0x60009400) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_MIXER_CONTROL */
    U32 all;
    struct {
        U32                             : 31;
        U32 reset                       : 1;
    } bitc;
} GH_VO_MIXER_CONTROL_REAL_S;

typedef union { /* VO_MIXER_STATUS */
    U32 all;
    struct {
        U32                             : 31;
        U32 reset                       : 1;
    } bitc;
} GH_VO_MIXER_STATUS_REAL_S;

typedef union { /* VO_MIXER_ACTIVE_SIZE */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER_ACTIVE_SIZE_REAL_S;

typedef union { /* VO_MIXER_VIDEO_START */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER_VIDEO_START_REAL_S;

typedef union { /* VO_MIXER_VIDEO_END */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER_VIDEO_END_REAL_S;

typedef union { /* VO_MIXER_OSD_START */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER_OSD_START_REAL_S;

typedef union { /* VO_MIXER_OSD_END */
    U32 all;
    struct {
        U32 vertical                    : 14;
        U32                             : 2;
        U32 horizontal                  : 14;
        U32                             : 2;
    } bitc;
} GH_VO_MIXER_OSD_END_REAL_S;

typedef union { /* VO_MIXER_BACKGROUND */
    U32 all;
    struct {
        U32 v                           : 8;
        U32 u                           : 8;
        U32 y                           : 8;
        U32                             : 8;
    } bitc;
} GH_VO_MIXER_BACKGROUND_REAL_S;

typedef union { /* VO_MIXER_HIGHLIGHT */
    U32 all;
    struct {
        U32 v                           : 8;
        U32 u                           : 8;
        U32 y                           : 8;
        U32 threshold                   : 8;
    } bitc;
} GH_VO_MIXER_HIGHLIGHT_REAL_S;

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
} GH_VO_MIXER_OSD_CONTROL_REAL_S;

typedef union { /* VO_MIXER_ENABLE_CTRL */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32 mapped_direct               : 2;
        U32 smem                        : 1;
        U32 display                     : 1;
        U32                             : 27;
    } bitc;
} GH_VO_MIXER_ENABLE_CTRL_REAL_S;

typedef union { /* VO_MIXER_INPUT_VIDEO_SYNC */
    U32 all;
    struct {
        U32 sync_mode                   : 2;
        U32 line                        : 3;
        U32 video                       : 6;
        U32 decrement                   : 1;
        U32                             : 20;
    } bitc;
} GH_VO_MIXER_INPUT_VIDEO_SYNC_REAL_S;

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
} GH_VO_MIXER_OUTPUT_SYNC_REAL_S;

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
} GH_VO_MIXER_SMEM_INPUT_REAL_S;

typedef union { /* VO_MIXER_SMEM_OUT */
    U32 all;
    struct {
        U32 luma_number                 : 8;
        U32 chroma_number               : 8;
        U32 priority                    : 2;
        U32                             : 14;
    } bitc;
} GH_VO_MIXER_SMEM_OUT_REAL_S;

typedef union { /* VO_MIXER_FRAME_ENABLE */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_MIXER_FRAME_ENABLE_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_CONTROL (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_CONTROL(U32 data)
{
    GH_VO_MIXER_CONTROL_REAL_S real;
    GH_VO_MIXER_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.reset = dummy.bitc.reset;
    *(volatile U32 *)REG_VO_MIXER_CONTROL_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_CONTROL(void)
{
    GH_VO_MIXER_CONTROL_REAL_S real;
    GH_VO_MIXER_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_CONTROL_REAL);

    dummy.bitc.reset = real.bitc.reset;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_CONTROL_Reset(U8 data)
{
    GH_VO_MIXER_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_CONTROL_REAL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_VO_MIXER_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_CONTROL_Reset(void)
{
    GH_VO_MIXER_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_STATUS (read)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_VO_MIXER_get_STATUS(void)
{
    GH_VO_MIXER_STATUS_REAL_S real;
    GH_VO_MIXER_STATUS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_STATUS_REAL);

    dummy.bitc.reset = real.bitc.reset;
    return dummy.all;
}
GH_INLINE U8   GH_VO_MIXER_get_STATUS_Reset(void)
{
    GH_VO_MIXER_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_ACTIVE_SIZE (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_ACTIVE_SIZE(U32 data)
{
    GH_VO_MIXER_ACTIVE_SIZE_REAL_S real;
    GH_VO_MIXER_ACTIVE_SIZE_S dummy;
    dummy.all = data ;
    real.bitc.vertical = dummy.bitc.vertical;
    real.bitc.horizontal = dummy.bitc.horizontal;
    *(volatile U32 *)REG_VO_MIXER_ACTIVE_SIZE_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_ACTIVE_SIZE(void)
{
    GH_VO_MIXER_ACTIVE_SIZE_REAL_S real;
    GH_VO_MIXER_ACTIVE_SIZE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_ACTIVE_SIZE_REAL);

    dummy.bitc.vertical = real.bitc.vertical;
    dummy.bitc.horizontal = real.bitc.horizontal;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_ACTIVE_SIZE_Vertical(U16 data)
{
    GH_VO_MIXER_ACTIVE_SIZE_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_ACTIVE_SIZE_REAL;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER_ACTIVE_SIZE_REAL = d.all;
}
GH_INLINE U16  GH_VO_MIXER_get_ACTIVE_SIZE_Vertical(void)
{
    GH_VO_MIXER_ACTIVE_SIZE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_ACTIVE_SIZE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vertical;
}
GH_INLINE void GH_VO_MIXER_set_ACTIVE_SIZE_Horizontal(U16 data)
{
    GH_VO_MIXER_ACTIVE_SIZE_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_ACTIVE_SIZE_REAL;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER_ACTIVE_SIZE_REAL = d.all;
}
GH_INLINE U16  GH_VO_MIXER_get_ACTIVE_SIZE_Horizontal(void)
{
    GH_VO_MIXER_ACTIVE_SIZE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_ACTIVE_SIZE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.horizontal;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_VIDEO_START (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_VIDEO_START(U32 data)
{
    GH_VO_MIXER_VIDEO_START_REAL_S real;
    GH_VO_MIXER_VIDEO_START_S dummy;
    dummy.all = data ;
    real.bitc.vertical = dummy.bitc.vertical;
    real.bitc.horizontal = dummy.bitc.horizontal;
    *(volatile U32 *)REG_VO_MIXER_VIDEO_START_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_VIDEO_START(void)
{
    GH_VO_MIXER_VIDEO_START_REAL_S real;
    GH_VO_MIXER_VIDEO_START_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_VIDEO_START_REAL);

    dummy.bitc.vertical = real.bitc.vertical;
    dummy.bitc.horizontal = real.bitc.horizontal;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_VIDEO_START_Vertical(U16 data)
{
    GH_VO_MIXER_VIDEO_START_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_VIDEO_START_REAL;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER_VIDEO_START_REAL = d.all;
}
GH_INLINE U16  GH_VO_MIXER_get_VIDEO_START_Vertical(void)
{
    GH_VO_MIXER_VIDEO_START_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_VIDEO_START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vertical;
}
GH_INLINE void GH_VO_MIXER_set_VIDEO_START_Horizontal(U16 data)
{
    GH_VO_MIXER_VIDEO_START_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_VIDEO_START_REAL;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER_VIDEO_START_REAL = d.all;
}
GH_INLINE U16  GH_VO_MIXER_get_VIDEO_START_Horizontal(void)
{
    GH_VO_MIXER_VIDEO_START_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_VIDEO_START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.horizontal;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_VIDEO_END (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_VIDEO_END(U32 data)
{
    GH_VO_MIXER_VIDEO_END_REAL_S real;
    GH_VO_MIXER_VIDEO_END_S dummy;
    dummy.all = data ;
    real.bitc.vertical = dummy.bitc.vertical;
    real.bitc.horizontal = dummy.bitc.horizontal;
    *(volatile U32 *)REG_VO_MIXER_VIDEO_END_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_VIDEO_END(void)
{
    GH_VO_MIXER_VIDEO_END_REAL_S real;
    GH_VO_MIXER_VIDEO_END_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_VIDEO_END_REAL);

    dummy.bitc.vertical = real.bitc.vertical;
    dummy.bitc.horizontal = real.bitc.horizontal;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_VIDEO_END_Vertical(U16 data)
{
    GH_VO_MIXER_VIDEO_END_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_VIDEO_END_REAL;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER_VIDEO_END_REAL = d.all;
}
GH_INLINE U16  GH_VO_MIXER_get_VIDEO_END_Vertical(void)
{
    GH_VO_MIXER_VIDEO_END_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_VIDEO_END_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vertical;
}
GH_INLINE void GH_VO_MIXER_set_VIDEO_END_Horizontal(U16 data)
{
    GH_VO_MIXER_VIDEO_END_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_VIDEO_END_REAL;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER_VIDEO_END_REAL = d.all;
}
GH_INLINE U16  GH_VO_MIXER_get_VIDEO_END_Horizontal(void)
{
    GH_VO_MIXER_VIDEO_END_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_VIDEO_END_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.horizontal;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_OSD_START (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_OSD_START(U32 data)
{
    GH_VO_MIXER_OSD_START_REAL_S real;
    GH_VO_MIXER_OSD_START_S dummy;
    dummy.all = data ;
    real.bitc.vertical = dummy.bitc.vertical;
    real.bitc.horizontal = dummy.bitc.horizontal;
    *(volatile U32 *)REG_VO_MIXER_OSD_START_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_OSD_START(void)
{
    GH_VO_MIXER_OSD_START_REAL_S real;
    GH_VO_MIXER_OSD_START_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_OSD_START_REAL);

    dummy.bitc.vertical = real.bitc.vertical;
    dummy.bitc.horizontal = real.bitc.horizontal;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_OSD_START_Vertical(U16 data)
{
    GH_VO_MIXER_OSD_START_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OSD_START_REAL;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER_OSD_START_REAL = d.all;
}
GH_INLINE U16  GH_VO_MIXER_get_OSD_START_Vertical(void)
{
    GH_VO_MIXER_OSD_START_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OSD_START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vertical;
}
GH_INLINE void GH_VO_MIXER_set_OSD_START_Horizontal(U16 data)
{
    GH_VO_MIXER_OSD_START_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OSD_START_REAL;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER_OSD_START_REAL = d.all;
}
GH_INLINE U16  GH_VO_MIXER_get_OSD_START_Horizontal(void)
{
    GH_VO_MIXER_OSD_START_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OSD_START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.horizontal;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_OSD_END (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_OSD_END(U32 data)
{
    GH_VO_MIXER_OSD_END_REAL_S real;
    GH_VO_MIXER_OSD_END_S dummy;
    dummy.all = data ;
    real.bitc.vertical = dummy.bitc.vertical;
    real.bitc.horizontal = dummy.bitc.horizontal;
    *(volatile U32 *)REG_VO_MIXER_OSD_END_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_OSD_END(void)
{
    GH_VO_MIXER_OSD_END_REAL_S real;
    GH_VO_MIXER_OSD_END_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_OSD_END_REAL);

    dummy.bitc.vertical = real.bitc.vertical;
    dummy.bitc.horizontal = real.bitc.horizontal;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_OSD_END_Vertical(U16 data)
{
    GH_VO_MIXER_OSD_END_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OSD_END_REAL;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER_OSD_END_REAL = d.all;
}
GH_INLINE U16  GH_VO_MIXER_get_OSD_END_Vertical(void)
{
    GH_VO_MIXER_OSD_END_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OSD_END_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vertical;
}
GH_INLINE void GH_VO_MIXER_set_OSD_END_Horizontal(U16 data)
{
    GH_VO_MIXER_OSD_END_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OSD_END_REAL;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER_OSD_END_REAL = d.all;
}
GH_INLINE U16  GH_VO_MIXER_get_OSD_END_Horizontal(void)
{
    GH_VO_MIXER_OSD_END_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OSD_END_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.horizontal;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_BACKGROUND (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_BACKGROUND(U32 data)
{
    GH_VO_MIXER_BACKGROUND_REAL_S real;
    GH_VO_MIXER_BACKGROUND_S dummy;
    dummy.all = data ;
    real.bitc.v = dummy.bitc.v;
    real.bitc.u = dummy.bitc.u;
    real.bitc.y = dummy.bitc.y;
    *(volatile U32 *)REG_VO_MIXER_BACKGROUND_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_BACKGROUND(void)
{
    GH_VO_MIXER_BACKGROUND_REAL_S real;
    GH_VO_MIXER_BACKGROUND_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_BACKGROUND_REAL);

    dummy.bitc.v = real.bitc.v;
    dummy.bitc.u = real.bitc.u;
    dummy.bitc.y = real.bitc.y;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_BACKGROUND_V(U8 data)
{
    GH_VO_MIXER_BACKGROUND_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_BACKGROUND_REAL;
    d.bitc.v = data;
    *(volatile U32 *)REG_VO_MIXER_BACKGROUND_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_BACKGROUND_V(void)
{
    GH_VO_MIXER_BACKGROUND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_BACKGROUND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.v;
}
GH_INLINE void GH_VO_MIXER_set_BACKGROUND_U(U8 data)
{
    GH_VO_MIXER_BACKGROUND_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_BACKGROUND_REAL;
    d.bitc.u = data;
    *(volatile U32 *)REG_VO_MIXER_BACKGROUND_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_BACKGROUND_U(void)
{
    GH_VO_MIXER_BACKGROUND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_BACKGROUND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.u;
}
GH_INLINE void GH_VO_MIXER_set_BACKGROUND_Y(U8 data)
{
    GH_VO_MIXER_BACKGROUND_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_BACKGROUND_REAL;
    d.bitc.y = data;
    *(volatile U32 *)REG_VO_MIXER_BACKGROUND_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_BACKGROUND_Y(void)
{
    GH_VO_MIXER_BACKGROUND_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_BACKGROUND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.y;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_HIGHLIGHT (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_HIGHLIGHT(U32 data)
{
    GH_VO_MIXER_HIGHLIGHT_REAL_S real;
    GH_VO_MIXER_HIGHLIGHT_S dummy;
    dummy.all = data ;
    real.bitc.v = dummy.bitc.v;
    real.bitc.u = dummy.bitc.u;
    real.bitc.y = dummy.bitc.y;
    real.bitc.threshold = dummy.bitc.threshold;
    *(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_HIGHLIGHT(void)
{
    GH_VO_MIXER_HIGHLIGHT_REAL_S real;
    GH_VO_MIXER_HIGHLIGHT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL);

    dummy.bitc.v = real.bitc.v;
    dummy.bitc.u = real.bitc.u;
    dummy.bitc.y = real.bitc.y;
    dummy.bitc.threshold = real.bitc.threshold;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_HIGHLIGHT_V(U8 data)
{
    GH_VO_MIXER_HIGHLIGHT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL;
    d.bitc.v = data;
    *(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_HIGHLIGHT_V(void)
{
    GH_VO_MIXER_HIGHLIGHT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.v;
}
GH_INLINE void GH_VO_MIXER_set_HIGHLIGHT_U(U8 data)
{
    GH_VO_MIXER_HIGHLIGHT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL;
    d.bitc.u = data;
    *(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_HIGHLIGHT_U(void)
{
    GH_VO_MIXER_HIGHLIGHT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.u;
}
GH_INLINE void GH_VO_MIXER_set_HIGHLIGHT_Y(U8 data)
{
    GH_VO_MIXER_HIGHLIGHT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL;
    d.bitc.y = data;
    *(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_HIGHLIGHT_Y(void)
{
    GH_VO_MIXER_HIGHLIGHT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.y;
}
GH_INLINE void GH_VO_MIXER_set_HIGHLIGHT_threshold(U8 data)
{
    GH_VO_MIXER_HIGHLIGHT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL;
    d.bitc.threshold = data;
    *(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_HIGHLIGHT_threshold(void)
{
    GH_VO_MIXER_HIGHLIGHT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_HIGHLIGHT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.threshold;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_OSD_CONTROL (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_OSD_CONTROL(U32 data)
{
    GH_VO_MIXER_OSD_CONTROL_REAL_S real;
    GH_VO_MIXER_OSD_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.global_blend = dummy.bitc.global_blend;
    real.bitc.premultiplied = dummy.bitc.premultiplied;
    real.bitc.mode = dummy.bitc.mode;
    real.bitc.enable_transparent_color = dummy.bitc.enable_transparent_color;
    real.bitc.transparent_color = dummy.bitc.transparent_color;
    *(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_OSD_CONTROL(void)
{
    GH_VO_MIXER_OSD_CONTROL_REAL_S real;
    GH_VO_MIXER_OSD_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL);

    dummy.bitc.global_blend = real.bitc.global_blend;
    dummy.bitc.premultiplied = real.bitc.premultiplied;
    dummy.bitc.mode = real.bitc.mode;
    dummy.bitc.enable_transparent_color = real.bitc.enable_transparent_color;
    dummy.bitc.transparent_color = real.bitc.transparent_color;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_OSD_CONTROL_Global_Blend(U8 data)
{
    GH_VO_MIXER_OSD_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL;
    d.bitc.global_blend = data;
    *(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_OSD_CONTROL_Global_Blend(void)
{
    GH_VO_MIXER_OSD_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.global_blend;
}
GH_INLINE void GH_VO_MIXER_set_OSD_CONTROL_Premultiplied(U8 data)
{
    GH_VO_MIXER_OSD_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL;
    d.bitc.premultiplied = data;
    *(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_OSD_CONTROL_Premultiplied(void)
{
    GH_VO_MIXER_OSD_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.premultiplied;
}
GH_INLINE void GH_VO_MIXER_set_OSD_CONTROL_Mode(U8 data)
{
    GH_VO_MIXER_OSD_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL;
    d.bitc.mode = data;
    *(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_OSD_CONTROL_Mode(void)
{
    GH_VO_MIXER_OSD_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mode;
}
GH_INLINE void GH_VO_MIXER_set_OSD_CONTROL_Enable_Transparent_Color(U8 data)
{
    GH_VO_MIXER_OSD_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL;
    d.bitc.enable_transparent_color = data;
    *(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_OSD_CONTROL_Enable_Transparent_Color(void)
{
    GH_VO_MIXER_OSD_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable_transparent_color;
}
GH_INLINE void GH_VO_MIXER_set_OSD_CONTROL_Transparent_Color(U16 data)
{
    GH_VO_MIXER_OSD_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL;
    d.bitc.transparent_color = data;
    *(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL = d.all;
}
GH_INLINE U16  GH_VO_MIXER_get_OSD_CONTROL_Transparent_Color(void)
{
    GH_VO_MIXER_OSD_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OSD_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.transparent_color;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_ENABLE_CTRL (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_ENABLE_CTRL(U32 data)
{
    GH_VO_MIXER_ENABLE_CTRL_REAL_S real;
    GH_VO_MIXER_ENABLE_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    real.bitc.mapped_direct = dummy.bitc.mapped_direct;
    real.bitc.smem = dummy.bitc.smem;
    real.bitc.display = dummy.bitc.display;
    *(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_ENABLE_CTRL(void)
{
    GH_VO_MIXER_ENABLE_CTRL_REAL_S real;
    GH_VO_MIXER_ENABLE_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL);

    dummy.bitc.enable = real.bitc.enable;
    dummy.bitc.mapped_direct = real.bitc.mapped_direct;
    dummy.bitc.smem = real.bitc.smem;
    dummy.bitc.display = real.bitc.display;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_ENABLE_CTRL_enable(U8 data)
{
    GH_VO_MIXER_ENABLE_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_ENABLE_CTRL_enable(void)
{
    GH_VO_MIXER_ENABLE_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}
GH_INLINE void GH_VO_MIXER_set_ENABLE_CTRL_mapped_direct(U8 data)
{
    GH_VO_MIXER_ENABLE_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL;
    d.bitc.mapped_direct = data;
    *(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_ENABLE_CTRL_mapped_direct(void)
{
    GH_VO_MIXER_ENABLE_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mapped_direct;
}
GH_INLINE void GH_VO_MIXER_set_ENABLE_CTRL_smem(U8 data)
{
    GH_VO_MIXER_ENABLE_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL;
    d.bitc.smem = data;
    *(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_ENABLE_CTRL_smem(void)
{
    GH_VO_MIXER_ENABLE_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.smem;
}
GH_INLINE void GH_VO_MIXER_set_ENABLE_CTRL_display(U8 data)
{
    GH_VO_MIXER_ENABLE_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL;
    d.bitc.display = data;
    *(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_ENABLE_CTRL_display(void)
{
    GH_VO_MIXER_ENABLE_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_ENABLE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.display;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_INPUT_VIDEO_SYNC (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_INPUT_VIDEO_SYNC(U32 data)
{
    GH_VO_MIXER_INPUT_VIDEO_SYNC_REAL_S real;
    GH_VO_MIXER_INPUT_VIDEO_SYNC_S dummy;
    dummy.all = data ;
    real.bitc.sync_mode = dummy.bitc.sync_mode;
    real.bitc.line = dummy.bitc.line;
    real.bitc.video = dummy.bitc.video;
    real.bitc.decrement = dummy.bitc.decrement;
    *(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_INPUT_VIDEO_SYNC(void)
{
    GH_VO_MIXER_INPUT_VIDEO_SYNC_REAL_S real;
    GH_VO_MIXER_INPUT_VIDEO_SYNC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL);

    dummy.bitc.sync_mode = real.bitc.sync_mode;
    dummy.bitc.line = real.bitc.line;
    dummy.bitc.video = real.bitc.video;
    dummy.bitc.decrement = real.bitc.decrement;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_INPUT_VIDEO_SYNC_sync_mode(U8 data)
{
    GH_VO_MIXER_INPUT_VIDEO_SYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL;
    d.bitc.sync_mode = data;
    *(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_INPUT_VIDEO_SYNC_sync_mode(void)
{
    GH_VO_MIXER_INPUT_VIDEO_SYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sync_mode;
}
GH_INLINE void GH_VO_MIXER_set_INPUT_VIDEO_SYNC_line(U8 data)
{
    GH_VO_MIXER_INPUT_VIDEO_SYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL;
    d.bitc.line = data;
    *(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_INPUT_VIDEO_SYNC_line(void)
{
    GH_VO_MIXER_INPUT_VIDEO_SYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.line;
}
GH_INLINE void GH_VO_MIXER_set_INPUT_VIDEO_SYNC_video(U8 data)
{
    GH_VO_MIXER_INPUT_VIDEO_SYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL;
    d.bitc.video = data;
    *(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_INPUT_VIDEO_SYNC_video(void)
{
    GH_VO_MIXER_INPUT_VIDEO_SYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.video;
}
GH_INLINE void GH_VO_MIXER_set_INPUT_VIDEO_SYNC_decrement(U8 data)
{
    GH_VO_MIXER_INPUT_VIDEO_SYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL;
    d.bitc.decrement = data;
    *(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_INPUT_VIDEO_SYNC_decrement(void)
{
    GH_VO_MIXER_INPUT_VIDEO_SYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_INPUT_VIDEO_SYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.decrement;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_OUTPUT_SYNC (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_OUTPUT_SYNC(U32 data)
{
    GH_VO_MIXER_OUTPUT_SYNC_REAL_S real;
    GH_VO_MIXER_OUTPUT_SYNC_S dummy;
    dummy.all = data ;
    real.bitc.sync_mode = dummy.bitc.sync_mode;
    real.bitc.number = dummy.bitc.number;
    real.bitc.counter = dummy.bitc.counter;
    real.bitc.sync = dummy.bitc.sync;
    real.bitc.frame = dummy.bitc.frame;
    *(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_OUTPUT_SYNC(void)
{
    GH_VO_MIXER_OUTPUT_SYNC_REAL_S real;
    GH_VO_MIXER_OUTPUT_SYNC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL);

    dummy.bitc.sync_mode = real.bitc.sync_mode;
    dummy.bitc.number = real.bitc.number;
    dummy.bitc.counter = real.bitc.counter;
    dummy.bitc.sync = real.bitc.sync;
    dummy.bitc.frame = real.bitc.frame;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_OUTPUT_SYNC_sync_mode(U8 data)
{
    GH_VO_MIXER_OUTPUT_SYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL;
    d.bitc.sync_mode = data;
    *(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_OUTPUT_SYNC_sync_mode(void)
{
    GH_VO_MIXER_OUTPUT_SYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sync_mode;
}
GH_INLINE void GH_VO_MIXER_set_OUTPUT_SYNC_number(U8 data)
{
    GH_VO_MIXER_OUTPUT_SYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL;
    d.bitc.number = data;
    *(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_OUTPUT_SYNC_number(void)
{
    GH_VO_MIXER_OUTPUT_SYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.number;
}
GH_INLINE void GH_VO_MIXER_set_OUTPUT_SYNC_counter(U8 data)
{
    GH_VO_MIXER_OUTPUT_SYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL;
    d.bitc.counter = data;
    *(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_OUTPUT_SYNC_counter(void)
{
    GH_VO_MIXER_OUTPUT_SYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.counter;
}
GH_INLINE void GH_VO_MIXER_set_OUTPUT_SYNC_sync(U8 data)
{
    GH_VO_MIXER_OUTPUT_SYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL;
    d.bitc.sync = data;
    *(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_OUTPUT_SYNC_sync(void)
{
    GH_VO_MIXER_OUTPUT_SYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sync;
}
GH_INLINE void GH_VO_MIXER_set_OUTPUT_SYNC_frame(U8 data)
{
    GH_VO_MIXER_OUTPUT_SYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL;
    d.bitc.frame = data;
    *(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_OUTPUT_SYNC_frame(void)
{
    GH_VO_MIXER_OUTPUT_SYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_OUTPUT_SYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.frame;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_SMEM_INPUT (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_SMEM_INPUT(U32 data)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S real;
    GH_VO_MIXER_SMEM_INPUT_S dummy;
    dummy.all = data ;
    real.bitc.luma_number = dummy.bitc.luma_number;
    real.bitc.chroma_number = dummy.bitc.chroma_number;
    real.bitc.osd_number = dummy.bitc.osd_number;
    real.bitc.priority = dummy.bitc.priority;
    real.bitc.video_length = dummy.bitc.video_length;
    real.bitc.osd_length = dummy.bitc.osd_length;
    *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_SMEM_INPUT(void)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S real;
    GH_VO_MIXER_SMEM_INPUT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL);

    dummy.bitc.luma_number = real.bitc.luma_number;
    dummy.bitc.chroma_number = real.bitc.chroma_number;
    dummy.bitc.osd_number = real.bitc.osd_number;
    dummy.bitc.priority = real.bitc.priority;
    dummy.bitc.video_length = real.bitc.video_length;
    dummy.bitc.osd_length = real.bitc.osd_length;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_SMEM_INPUT_luma_number(U8 data)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL;
    d.bitc.luma_number = data;
    *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_SMEM_INPUT_luma_number(void)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.luma_number;
}
GH_INLINE void GH_VO_MIXER_set_SMEM_INPUT_chroma_number(U8 data)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL;
    d.bitc.chroma_number = data;
    *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_SMEM_INPUT_chroma_number(void)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.chroma_number;
}
GH_INLINE void GH_VO_MIXER_set_SMEM_INPUT_osd_number(U8 data)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL;
    d.bitc.osd_number = data;
    *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_SMEM_INPUT_osd_number(void)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.osd_number;
}
GH_INLINE void GH_VO_MIXER_set_SMEM_INPUT_priority(U8 data)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL;
    d.bitc.priority = data;
    *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_SMEM_INPUT_priority(void)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.priority;
}
GH_INLINE void GH_VO_MIXER_set_SMEM_INPUT_video_length(U8 data)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL;
    d.bitc.video_length = data;
    *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_SMEM_INPUT_video_length(void)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.video_length;
}
GH_INLINE void GH_VO_MIXER_set_SMEM_INPUT_osd_length(U8 data)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL;
    d.bitc.osd_length = data;
    *(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_SMEM_INPUT_osd_length(void)
{
    GH_VO_MIXER_SMEM_INPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_SMEM_INPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.osd_length;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_SMEM_OUT (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_SMEM_OUT(U32 data)
{
    GH_VO_MIXER_SMEM_OUT_REAL_S real;
    GH_VO_MIXER_SMEM_OUT_S dummy;
    dummy.all = data ;
    real.bitc.luma_number = dummy.bitc.luma_number;
    real.bitc.chroma_number = dummy.bitc.chroma_number;
    real.bitc.priority = dummy.bitc.priority;
    *(volatile U32 *)REG_VO_MIXER_SMEM_OUT_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_SMEM_OUT(void)
{
    GH_VO_MIXER_SMEM_OUT_REAL_S real;
    GH_VO_MIXER_SMEM_OUT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_SMEM_OUT_REAL);

    dummy.bitc.luma_number = real.bitc.luma_number;
    dummy.bitc.chroma_number = real.bitc.chroma_number;
    dummy.bitc.priority = real.bitc.priority;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_SMEM_OUT_luma_number(U8 data)
{
    GH_VO_MIXER_SMEM_OUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_SMEM_OUT_REAL;
    d.bitc.luma_number = data;
    *(volatile U32 *)REG_VO_MIXER_SMEM_OUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_SMEM_OUT_luma_number(void)
{
    GH_VO_MIXER_SMEM_OUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_SMEM_OUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.luma_number;
}
GH_INLINE void GH_VO_MIXER_set_SMEM_OUT_chroma_number(U8 data)
{
    GH_VO_MIXER_SMEM_OUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_SMEM_OUT_REAL;
    d.bitc.chroma_number = data;
    *(volatile U32 *)REG_VO_MIXER_SMEM_OUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_SMEM_OUT_chroma_number(void)
{
    GH_VO_MIXER_SMEM_OUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_SMEM_OUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.chroma_number;
}
GH_INLINE void GH_VO_MIXER_set_SMEM_OUT_priority(U8 data)
{
    GH_VO_MIXER_SMEM_OUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_SMEM_OUT_REAL;
    d.bitc.priority = data;
    *(volatile U32 *)REG_VO_MIXER_SMEM_OUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_SMEM_OUT_priority(void)
{
    GH_VO_MIXER_SMEM_OUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_SMEM_OUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.priority;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_FRAME_ENABLE (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_FRAME_ENABLE(U32 data)
{
    GH_VO_MIXER_FRAME_ENABLE_REAL_S real;
    GH_VO_MIXER_FRAME_ENABLE_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    *(volatile U32 *)REG_VO_MIXER_FRAME_ENABLE_REAL = real.all;
}
GH_INLINE U32  GH_VO_MIXER_get_FRAME_ENABLE(void)
{
    GH_VO_MIXER_FRAME_ENABLE_REAL_S real;
    GH_VO_MIXER_FRAME_ENABLE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_MIXER_FRAME_ENABLE_REAL);

    dummy.bitc.enable = real.bitc.enable;
    return dummy.all;
}
GH_INLINE void GH_VO_MIXER_set_FRAME_ENABLE_enable(U8 data)
{
    GH_VO_MIXER_FRAME_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER_FRAME_ENABLE_REAL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_MIXER_FRAME_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_VO_MIXER_get_FRAME_ENABLE_enable(void)
{
    GH_VO_MIXER_FRAME_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER_FRAME_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}

/*----------------------------------------------------------------------------*/
/* register VO_MIXER_CLUT_B (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_set_CLUT_B(U16 index, U32 data)
{
    *(volatile U32 *)(REG_VO_MIXER_CLUT_B_REAL + index * FIO_MOFFSET(VO_MIXER,0x00000004)) = data;
}
GH_INLINE U32  GH_VO_MIXER_get_CLUT_B(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_VO_MIXER_CLUT_B_REAL + index * FIO_MOFFSET(VO_MIXER,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_MIXER_init(void)
{
    int i;

    GH_VO_MIXER_set_CONTROL((U32)0x00000000);
    GH_VO_MIXER_set_ACTIVE_SIZE((U32)0x00000000);
    GH_VO_MIXER_set_VIDEO_START((U32)0x00000000);
    GH_VO_MIXER_set_VIDEO_END((U32)0x00000000);
    GH_VO_MIXER_set_OSD_START((U32)0x00000000);
    GH_VO_MIXER_set_OSD_END((U32)0x00000000);
    GH_VO_MIXER_set_BACKGROUND((U32)0x00000000);
    GH_VO_MIXER_set_HIGHLIGHT((U32)0xff000000);
    GH_VO_MIXER_set_OSD_CONTROL((U32)0x000000ff);
    GH_VO_MIXER_set_ENABLE_CTRL((U32)0x00000000);
    GH_VO_MIXER_set_INPUT_VIDEO_SYNC((U32)0x00000000);
    GH_VO_MIXER_set_OUTPUT_SYNC((U32)0x00000000);
    GH_VO_MIXER_set_SMEM_INPUT((U32)0x00000000);
    GH_VO_MIXER_set_SMEM_OUT((U32)0x00000000);
    GH_VO_MIXER_set_FRAME_ENABLE((U32)0x00000000);
    GH_VO_MIXER_set_CLUT_B(0, (U32)0x00000000);
    for (i=1; i<256; i++)
    {
        GH_VO_MIXER_set_CLUT_B(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

