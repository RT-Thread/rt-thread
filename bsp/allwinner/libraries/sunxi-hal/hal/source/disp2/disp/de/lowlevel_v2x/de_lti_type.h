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
 *  File name   :   de_lti_type.h
 *
 *  Description :   display engine 2.0 lti struct declaration
 *
 *  History     :   2014/04/01  vito cheng  v0.1  Initial version
 *
 ******************************************************************************/

#ifndef __DE_LTI_TYPE_H__
#define __DE_LTI_TYPE_H__

#include "de_rtmx.h"

#define LTI_PARA_NUM 1
#define LTI_MODE_NUM 2

union LTI_EN {
    unsigned int dwval;
    struct {
        unsigned int en:1;
        unsigned int res0:7;
        unsigned int sel:1;
        unsigned int res1:7;
        unsigned int nonl_en:1;
        unsigned int res2:7;
        unsigned int win_en:1;
        unsigned int res3:7;

    } bits;
};

union LTI_SIZE {
    unsigned int dwval;
    struct {
        unsigned int width:12;
        unsigned int res0:4;
        unsigned int height:12;
        unsigned int res1:4;
    } bits;
};

union LTI_FIR_COFF0 {
    unsigned int dwval;
    struct {
        unsigned int c0:8;
        unsigned int res0:8;
        unsigned int c1:8;
        unsigned int res1:8;
    } bits;
};
union LTI_FIR_COFF1 {
    unsigned int dwval;
    struct {
        unsigned int c2:8;
        unsigned int res0:8;
        unsigned int c3:8;
        unsigned int res1:8;
    } bits;
};
union LTI_FIR_COFF2 {
    unsigned int dwval;
    struct {
        unsigned int c4:8;
        unsigned int res0:24;
    } bits;
};

union LTI_FIR_GAIN {
    unsigned int dwval;
    struct {
        unsigned int lti_fil_gain:4;
        unsigned int res0:28;

    } bits;
};

union LTI_COR_TH {
    unsigned int dwval;
    struct {
        unsigned int lti_cor_th:10;
        unsigned int res0:22;
    } bits;
};

union LTI_DIFF_CTL {
    unsigned int dwval;
    struct {
        unsigned int offset:8;
        unsigned int res0:8;
        unsigned int slope:5;
        unsigned int res1:11;
    } bits;
};

union LTI_EDGE_GAIN {
    unsigned int dwval;
    struct {
        unsigned int edge_gain:5;
        unsigned int res0:27;
    } bits;
};

union LTI_OS_CON {
    unsigned int dwval;
    struct {
        unsigned int core_x:8;
        unsigned int res0:8;
        unsigned int clip:8;
        unsigned int res1:4;
        unsigned int peak_limit:3;
        unsigned int res2:1;
    } bits;
};

union LTI_WIN_EXPANSION {
    unsigned int dwval;
    struct {
        unsigned int win_range:8;
        unsigned int res0:24;
    } bits;
};

union LTI_EDGE_ELVEL_TH {
    unsigned int dwval;
    struct {
        unsigned int elvel_th:8;
        unsigned int res0:24;
    } bits;
};

union LTI_WIN0_REG {
    unsigned int dwval;
    struct {
        unsigned int win_left:12;
        unsigned int res0:4;
        unsigned int win_top:12;
        unsigned int res1:4;
    } bits;
};

union LTI_WIN1_REG {
    unsigned int dwval;
    struct {
        unsigned int win_right:12;
        unsigned int res0:4;
        unsigned int win_bot:12;
        unsigned int res1:4;
    } bits;
};

struct __lti_reg_t {
    union LTI_EN ctrl;                     /* 0x0000 */
    unsigned int res0[2];            /* 0x0004-0x0008 */
    union LTI_SIZE size;                     /* 0x000c */
    union LTI_FIR_COFF0 coef0;           /* 0x0010 */
    union LTI_FIR_COFF1 coef1;           /* 0x0014 */
    union LTI_FIR_COFF2 coef2;           /* 0x0018 */
    union LTI_FIR_GAIN gain;               /* 0x001c */
    union LTI_COR_TH corth;              /* 0x0020 */
    union LTI_DIFF_CTL diff;               /* 0x0024 */
    union LTI_EDGE_GAIN edge_gain;       /* 0x0028 */
    union LTI_OS_CON os_con;               /* 0x002c */
    union LTI_WIN_EXPANSION win_range;   /* 0x0030 */
    union LTI_EDGE_ELVEL_TH elvel_th;      /* 0x0034 */
    union LTI_WIN0_REG win0;               /* 0x0038 */
    union LTI_WIN1_REG win1;               /* 0x003c */
};

struct __lti_config_data {
    /* lti */
    unsigned int lti_en;
    unsigned int gain;

    /* window */
    unsigned int win_en;
    struct de_rect win;

};

#endif
