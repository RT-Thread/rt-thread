/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

/*******************************************************************************
 *  All Winner Tech, All Right Reserved. 2014-2015 Copyright (c)
 *
 *  File name   :   de_fce_type.h
 *
 *  Description :   display engine 2.0 fce struct declaration
 *
 *  History     :   2014/04/01  vito cheng  v0.1  Initial version
 *                  2014/04/29      vito cheng  v0.2  Add __fce_config_data
 ******************************************************************************/

#ifndef __DE_FCE_TYPE_H__
#define __DE_FCE_TYPE_H__

#include "de_rtmx.h"

/*
 * 0x0: do hist in even frame;
 * 0x1, do hist in odd frame;
 * 0x2, do hist in all frames
 */
#define HIST_FRAME_MASK  0x00000002

/*
 * 0x0: do CE in even frame;
 * 0x1, do CE in odd frame;
 * 0x2, do CE in all frames
 */
#define CE_FRAME_MASK    0x00000002

#define LCE_PARA_NUM  2
#define LCE_MODE_NUM  2

#define AUTOCE_PARA_NUM  5
#define AUTOCE_MODE_NUM  3

#define CE_PARA_NUM  2
#define CE_MODE_NUM  2

#define FTC_PARA_NUM  2
#define FTC_MODE_NUM  2

#define AVG_NUM 8

/* for hist */
extern unsigned int *g_hist[DE_NUM][CHN_NUM];
extern unsigned int *g_hist_p[DE_NUM][CHN_NUM];
extern unsigned int g_sum[DE_NUM][CHN_NUM];

extern unsigned int g_format[DE_NUM];

union FCE_GCTRL_REG {
    unsigned int dwval;
    struct {
        unsigned int en:1;
        unsigned int res0:15;
        unsigned int hist_en:1;
        unsigned int ce_en:1;
        unsigned int lce_en:1;
        unsigned int res1:1;
        unsigned int ftc_en:1;
        unsigned int res2:10;
        unsigned int win_en:1;
    } bits;
};

union FCE_SIZE_REG {
    unsigned int dwval;
    struct {
        unsigned int width:12;
        unsigned int res0:4;
        unsigned int height:12;
        unsigned int res1:4;
    } bits;
};

union FCE_WIN0_REG {
    unsigned int dwval;
    struct {
        unsigned int win_left:12;
        unsigned int res0:4;
        unsigned int win_top:12;
        unsigned int res1:4;
    } bits;
};

union FCE_WIN1_REG {
    unsigned int dwval;
    struct {
        unsigned int win_right:12;
        unsigned int res0:4;
        unsigned int win_bot:12;
        unsigned int res1:4;
    } bits;
};

union LCE_GAIN_REG {
    unsigned int dwval;
    struct {
        unsigned int lce_gain:6;
        unsigned int res0:2;
        unsigned int lce_blend:8;
        unsigned int res1:16;
    } bits;
};

union HIST_SUM_REG {
    unsigned int dwval;
    struct {
        unsigned int sum:32;
    } bits;
};

union HIST_STATUS_REG {
    unsigned int dwval;
    struct {
        unsigned int hist_valid:1;
        unsigned int res0:31;
    } bits;
};

union CE_STATUS_REG {
    unsigned int dwval;
    struct {
        unsigned int celut_access_switch:1;
        unsigned int res0:31;
    } bits;
};

union FTC_GAIN_REG {
    unsigned int dwval;
    struct {
        unsigned int ftc_gain1:8;
        unsigned int res0:8;
        unsigned int ftc_gain2:8;
        unsigned int res1:8;
    } bits;
};

union FTC_CSCBYPASS_REG {
    unsigned int dwval;
    struct {
        unsigned int csc_bypass:1;
        unsigned int res0:31;
    } bits;
};

union CE_LUT_REG {
    unsigned int dwval;
    struct {
        unsigned int lut0:8;
        unsigned int lut1:8;
        unsigned int lut2:8;
        unsigned int lut3:8;
    } bits;
};

union HIST_CNT_REG {
    unsigned int dwval;
    struct {
        unsigned int hist:22;
        unsigned int res0:10;
    } bits;
};

struct __fce_reg_t {
    union FCE_GCTRL_REG ctrl;               /* 0x0000        */
    union FCE_SIZE_REG size;                /* 0x0004        */
    union FCE_WIN0_REG win0;                /* 0x0008        */
    union FCE_WIN1_REG win1;                /* 0x000c        */
    union LCE_GAIN_REG lcegain;           /* 0x0010        */
    unsigned int res0[3];             /* 0x0014-0x001c */
    union HIST_SUM_REG histsum;           /* 0x0020        */
    union HIST_STATUS_REG histstauts;       /* 0x0024        */
    union CE_STATUS_REG cestatus;           /* 0x0028        */
    unsigned int res1;              /* 0x002c        */
    union FTC_GAIN_REG ftcgain;           /* 0x0030        */
    unsigned int res2[3];             /* 0x0034-0x003c */
    union FTC_CSCBYPASS_REG cscbypass;    /* 0x0040        */
    unsigned int res3[47];          /* 0x0044-0x00fc */
    union CE_LUT_REG celut[64];           /* 0x0100-0x01fc */
    union HIST_CNT_REG hist[256];           /* 0x0200-0x05fc */
};

struct __fce_config_data {
    /* global */
    unsigned int fce_en;

    /* ce */
    unsigned int ce_en;
    unsigned int up_precent_thr;
    unsigned int down_precent_thr;
    unsigned int b_automode;
    unsigned int update_diff_thr;

    /* bws */
    unsigned int present_black;
    unsigned int present_white;
    unsigned int slope_black_lmt;
    unsigned int slope_white_lmt;
    unsigned int black_prec;
    unsigned int white_prec;
    unsigned int lowest_black;
    unsigned int highest_white;

    /* lce */
    unsigned int lce_en;
    unsigned int lce_blend;
    unsigned int lce_gain;

    /* ftc */
    unsigned int ftc_en;
    unsigned int ftc_gain1;
    unsigned int ftc_gain2;

    unsigned int hist_en;

    unsigned int win_en;
    struct de_rect win;
};

struct __hist_status_t {
    /* Frame number of Histogram run */
    unsigned int runtime;
    /* Histogram enabled */
    unsigned int isenable;
    /* Already get histogram of two frames */
    unsigned int twohistready;
};

struct __ce_status_t {
    unsigned int isenable;    /* CE enabled */
    unsigned int b_automode;    /* 0: Constant CE ; 1: Auto CE */
    unsigned int width;
    unsigned int height;
    /* alg */
    unsigned int up_precent_thr;
    unsigned int down_precent_thr;
    unsigned int update_diff_thr;
    unsigned int slope_black_lmt;
    unsigned int slope_white_lmt;

};

struct hist_data {
    unsigned int hist_mean;
    unsigned int old_hist_mean;
    int hist_mean_diff;
    unsigned int avg_mean_saved[AVG_NUM];
    unsigned int avg_mean_idx;
    unsigned int avg_mean;
    unsigned int counter;
    unsigned int diff_coeff;

    unsigned int black_thr0;
    unsigned int black_thr1;
    unsigned int white_thr0;
    unsigned int white_thr1;

    unsigned int black_slp0;
    unsigned int black_slp1;
    unsigned int white_slp0;
    unsigned int white_slp1;

};

#endif
