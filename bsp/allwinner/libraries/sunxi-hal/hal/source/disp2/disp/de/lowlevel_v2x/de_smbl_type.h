/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

/**
 *  All Winner Tech, All Right Reserved. 2014-2015 Copyright (c)
 *
 *  File name   :       de_smbl_type.h
 *
 *  Description :       display engine 2.0 smbl struct declaration
 *
 *  History     :       2014/05/13  vito cheng  v0.1  Initial version
 *
 */
#ifndef __DE_SMBL_TYPE_H__
#define __DE_SMBL_TYPE_H__

#include "de_rtmx.h"

#define SMBL_FRAME_MASK 0x00000002
/* 0x0: do SMBL in even frame;
 * 0x1, do SMBL in odd frame;
 * 0x2, do SMBL in all frames
 */

#define IEP_LH_INTERVAL_NUM 8
#define IEP_LH_PWRSV_NUM 24

union __imgehc_gnectl_reg_t {
    u32 dwval;
    struct {
        u32 en:1;
        u32 incsc_en:1;
        u32 r0:2;
        u32 coef_switch_en:1;
        u32 r1:3;
        u32 mod:2;
        u32 r2:21;
        u32 bist_en:1;
    } bits;
};

union __imgehc_drcsize_reg_t {
    u32 dwval;
    struct {
        u32 disp_w:13;
        u32 r0:3;
        u32 disp_h:13;
        u32 r1:3;
    } bits;
};

union __imgehc_drcctl_reg_t {
    u32 dwval;
    struct {
        u32 db_en:1;
        u32 r0:7;
        u32 win_en:1;
        u32 hsv_en:1;
        u32 r1:22;
    } bits;
};

union __imgehc_drc_set_reg_t {
    u32 dwval;
    struct {
        u32 lgc_abslumshf:1;
        u32 adjust_en:1;
        u32 r0:6;
        u32 lgc_abslumperval:8;
        u32 r1:16;
    } bits;
};

union __imgehc_drc_wp_reg0_t {
    u32 dwval;
    struct {
        u32 win_left:12;
        u32 r0:4;
        u32 win_top:12;
        u32 r1:4;
    } bits;
};

union __imgehc_drc_wp_reg1_t {
    u32 dwval;
    struct {
        u32 win_right:12;
        u32 r0:4;
        u32 win_bottom:12;
        u32 r1:4;
    } bits;
};

union __imgehc_lhctl_reg_t {
    u32 dwval;
    struct {
        u32 lh_rec_clr:1;
        u32 lh_mod:1;
        u32 r0:30;
    } bits;
};

union __imgehc_lhthr_reg0_t {
    u32 dwval;
    struct {
        u32 lh_thres_val1:8;
        u32 lh_thres_val2:8;
        u32 lh_thres_val3:8;
        u32 lh_thres_val4:8;
    } bits;
};

union __imgehc_lhthr_reg1_t {
    u32 dwval;
    struct {
        u32 lh_thres_val5:8;
        u32 lh_thres_val6:8;
        u32 lh_thres_val7:8;
        u32 r0:8;
    } bits;
};

union __imgehc_lhslum_reg_t {
    u32 dwval;
    struct {
        u32 lh_lum_data:32;
    } bits;
};

union __imgehc_lhscnt_reg_t {
    u32 dwval;
    struct {
        u32 lh_cnt_data:32;
    } bits;
};

union __imgehc_cscygcoff_reg_t {
    u32 dwval;
    struct {
        u32 csc_yg_coff:13;
        u32 r0:19;
    } bits;
};

union __imgehc_cscygcon_reg_t {
    u32 dwval;
    struct {
        u32 csc_yg_con:14;
        u32 r0:18;
    } bits;
};

union __imgehc_cscurcoff_reg_t {
    u32 dwval;
    struct {
        u32 csc_ur_coff:13;
        u32 r0:19;
    } bits;
};

union __imgehc_cscurcon_reg_t {
    u32 dwval;
    struct {
        u32 csc_ur_con:14;
        u32 r0:18;
    } bits;
};

union __imgehc_cscvbcoff_reg_t {
    u32 dwval;
    struct {
        u32 csc_vb_coff:13;
        u32 r0:19;
    } bits;
};

union __imgehc_cscvbcon_reg_t {
    u32 dwval;
    struct {
        u32 csc_vb_con:14;
        u32 r0:18;
    } bits;
};

union __imgehc_drcspacoff_reg_t {
    u32 dwval;
    struct {
        u32 spa_coff0:8;
        u32 spa_coff1:8;
        u32 spa_coff2:8;
        u32 r0:8;
    } bits;
};

union __imgehc_drcintcoff_reg_t {
    u32 dwval;
    struct {
        u32 inten_coff0:8;
        u32 inten_coff1:8;
        u32 inten_coff2:8;
        u32 inten_coff3:8;
    } bits;
};

union __imgehc_drclgcoff_reg_t {
    u32 dwval;
    struct {
        u32 lumagain_coff0:16;
        u32 lumagain_coff1:16;
    } bits;
};

struct __smbl_reg_t {
    union __imgehc_gnectl_reg_t gnectl;         /* 0x00 */
    union __imgehc_drcsize_reg_t drcsize;           /* 0x04 */
    u32 r0[2];                  /* 0x08~0x0c */
    union __imgehc_drcctl_reg_t drcctl;         /* 0x10 */
    u32 r1;                     /* 0x14 */
    union __imgehc_drc_set_reg_t drc_set;           /* 0x18 */
    union __imgehc_drc_wp_reg0_t drc_wp0;           /* 0x1c */
    union __imgehc_drc_wp_reg1_t drc_wp1;           /* 0x20 */
    u32 r5[3];                  /* 0x24~0x2c */
    union __imgehc_lhctl_reg_t lhctl;           /* 0x30 */
    union __imgehc_lhthr_reg0_t lhthr0;         /* 0x34 */
    union __imgehc_lhthr_reg1_t lhthr1;         /* 0x38 */
    u32 r2;                     /* 0x3c */
    union __imgehc_lhslum_reg_t lhslum[8];      /* 0x40~0x5c */
    union __imgehc_lhscnt_reg_t lhscnt[8];      /* 0x0060 ~ 0x007c */
    union __imgehc_cscygcoff_reg_t incscycoff[3];       /* 0x80~0x88 */
    union __imgehc_cscygcon_reg_t incscycon;        /* 0x8c */
    union __imgehc_cscurcoff_reg_t incscucoff[3];       /* 0x90~0x98 */
    union __imgehc_cscurcon_reg_t incscucon;        /* 0x9c */
    union __imgehc_cscvbcoff_reg_t incscvcoff[3];       /* 0xa0~0xa8 */
    union __imgehc_cscvbcon_reg_t incscvcon;        /* 0xac */
    u32 r6[4];                  /* 0xb0~0xbc */
    union __imgehc_cscygcoff_reg_t cscrcoff[3];     /* 0xc0~0xc8 */
    union __imgehc_cscygcon_reg_t cscrcon;      /* 0xcc */
    union __imgehc_cscurcoff_reg_t cscgcoff[3];     /* 0xd0~0xd8 */
    union __imgehc_cscurcon_reg_t cscgcon;      /* 0xdc */
    union __imgehc_cscvbcoff_reg_t cscbcoff[3];     /* 0xe0~0xe8 */
    union __imgehc_cscvbcon_reg_t cscbcon;      /* 0xec */
    union __imgehc_drcspacoff_reg_t drcspacoff[3];  /* 0xf0~0xf8 */
    u32 r4;                     /* 0xfc */
    union __imgehc_drcintcoff_reg_t drcintcoff[64]; /* 0x0100 ~ 0x01fc */
    union __imgehc_drclgcoff_reg_t drclgcoff[128];  /* 0x0200 ~ 0x03fc */
};

struct __smbl_status_t {
    unsigned int isenable;
    unsigned int runtime;
    unsigned int backlight;
    unsigned int dimming;
    unsigned char min_adj_index_hist[IEP_LH_PWRSV_NUM];
    unsigned int size; /* size = width*height/100 */
};

#endif
