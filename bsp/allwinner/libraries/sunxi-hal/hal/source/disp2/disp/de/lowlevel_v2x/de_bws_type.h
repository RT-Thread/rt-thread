/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

/*****************************************************************************
 *  All Winner Tech, All Right Reserved. 2014-2015 Copyright (c)
 *
 *  File name   :   de_bws_type.h
 *
 *  Description :   display engine 2.0 bws struct declaration
 *
 *  History     :   2014/03/26  vito cheng  v0.1  Initial version
 *
 *****************************************************************************/

#ifndef __DE_BWS_TYPE_H__
#define __DE_BWS_TYPE_H__

#include "de_rtmx.h"

/* for hist */
extern unsigned int *g_hist[DE_NUM][CHN_NUM];
extern unsigned int *g_hist_p[DE_NUM][CHN_NUM];
extern unsigned int g_sum[DE_NUM][CHN_NUM];
extern struct __hist_status_t *g_hist_status[DE_NUM][CHN_NUM];

#define BWS_FRAME_MASK  0x00000002
/*
 * 0x0: do bws in odd frame;
 * 0x1, do bws in even frame;
 * 0x2, do bws in all frames
 */
#define BWS_DEFAULT_SLOPE 0x100

union BWS_CTRL_REG {
    unsigned int dwval;
    struct {
        unsigned int en:1;
        unsigned int res:30;
        unsigned int win_en:1;
    } bits;
};

union BWS_SIZE_REG {
    unsigned int dwval;
    struct {
        unsigned int width:12;
        unsigned int res0:4;
        unsigned int height:12;
        unsigned int res1:4;
    } bits;
};

union BWS_WIN0_REG {
    unsigned int dwval;
    struct {
        unsigned int win_left:12;
        unsigned int res0:4;
        unsigned int win_top:12;
        unsigned int res1:4;
    } bits;
};

union BWS_WIN1_REG {
    unsigned int dwval;
    struct {
        unsigned int win_right:12;
        unsigned int res0:4;
        unsigned int win_bot:12;
        unsigned int res1:4;
    } bits;
};

union BWS_LS_THR0_REG {
    unsigned int dwval;
    struct {
        unsigned int min:8;
        unsigned int res0:8;
        unsigned int black:8;
        unsigned int res1:8;
    } bits;
};

union BWS_LS_THR1_REG {
    unsigned int dwval;
    struct {
        unsigned int white:8;
        unsigned int res0:8;
        unsigned int max:8;
        unsigned int res1:8;
    } bits;
};

union BWS_LS_SLP0_REG {
    unsigned int dwval;
    struct {
        unsigned int slope0:10;
        unsigned int res0:6;
        unsigned int slope1:10;
        unsigned int res1:6;
    } bits;
};

union BWS_LS_SLP1_REG {
    unsigned int dwval;
    struct {
        unsigned int slope2:10;
        unsigned int res0:6;
        unsigned int slope3:10;
        unsigned int res1:6;
    } bits;
};

struct __bws_reg_t {
    union BWS_CTRL_REG ctrl;        /* 0x0000 */
    union BWS_SIZE_REG size;        /* 0x0004 */
    union BWS_WIN0_REG win0;        /* 0x0008 */
    union BWS_WIN1_REG win1;        /* 0x000c */
    unsigned int res0[4];         /* 0x0010-0x001c */
    union BWS_LS_THR0_REG blkthr;   /* 0x0020 */
    union BWS_LS_THR1_REG whtthr;   /* 0x0024 */
    union BWS_LS_SLP0_REG blkslp;   /* 0x0028 */
    union BWS_LS_SLP1_REG whtslp;   /* 0x002c */
};

struct __bws_config_data {
    /* bws */
    unsigned int bws_en;
    unsigned int bld_high_thr;
    unsigned int bld_low_thr;
    unsigned int bld_weight_lmt;
    unsigned int present_black;
    unsigned int present_white;
    unsigned int slope_black_lmt;
    unsigned int slope_white_lmt;
    unsigned int black_prec;
    unsigned int white_prec;
    unsigned int lowest_black;
    unsigned int highest_white;

    /* window */
    unsigned int win_en;
    struct de_rect win;
};

struct __bws_status_t {
    unsigned int isenable;       /* BWS enabled */
    unsigned int runtime;          /* Frame number of BWS run */
    unsigned int preslopeready;  /* Get two slope */
    unsigned int width;
    unsigned int height;
    unsigned int slope_black;
    unsigned int slope_white;
};
#endif
