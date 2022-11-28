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
 *  File name   :       de_gsu_type.h
 *
 *  Description :       display engine 2.0 gsu struct declaration
 *
 *  History     :       2014/03/20  vito cheng  v0.1  Initial version
 *
 */

#ifndef __DE_GSU_TYPE_H__
#define __DE_GSU_TYPE_H__

/*
 * __gsu_reg_t
 */
union GSU_CTRL_REG {
    unsigned int dwval;
    struct {
        unsigned int en:1;
        unsigned int res0:3;
        unsigned int coef_switch_rdy:1;
        unsigned int res1:25;
        unsigned int reset:1;
        unsigned int res2:1;
    } bits;
};

union GSU_STATUS_REG {
    unsigned int dwval;
    struct {
        unsigned int res0:4;
        unsigned int busy:1;
        unsigned int res1:11;
        unsigned int line_cnt:12;
        unsigned int res2:4;
    } bits;
};

union GSU_FIELD_CTRL_REG {
    unsigned int dwval;
    struct {
        unsigned int vphase_sel_en:1;
        unsigned int res0:31;
    } bits;
};

union GSU_BIST_REG {
    unsigned int dwval;
    struct {
        unsigned int bist_en:1;
        unsigned int res0:15;
        unsigned int bist_sel:5;
        unsigned int res1:11;
    } bits;
};

union GSU_OUTSIZE_REG {
    unsigned int dwval;
    struct {
        unsigned int width:13;
        unsigned int res0:3;
        unsigned int height:13;
        unsigned int res1:3;
    } bits;
};

union GSU_INSIZE_REG {
    unsigned int dwval;
    struct {
        unsigned int width:13;
        unsigned int res0:3;
        unsigned int height:13;
        unsigned int res1:3;
    } bits;
};

union GSU_HSTEP_REG {
    unsigned int dwval;
    struct {
        unsigned int res0:2;
        unsigned int frac:18;
        unsigned int integer:5;
        unsigned int res1:7;
    } bits;
};

union GSU_VSTEP_REG {
    unsigned int dwval;
    struct {
        unsigned int res0:2;
        unsigned int frac:18;
        unsigned int integer:5;
        unsigned int res1:7;
    } bits;
};

union GSU_HPHASE_REG {
    unsigned int dwval;
    struct {
        unsigned int res0:2;
        unsigned int frac:18;
        unsigned int integer:5;
        unsigned int res1:7;
    } bits;
};

union GSU_VPHASE0_REG {
    unsigned int dwval;
    struct {
        unsigned int res0:2;
        unsigned int frac:18;
        unsigned int integer:5;
        unsigned int res1:7;
    } bits;
};

union GSU_VPHASE1_REG {
    unsigned int dwval;
    struct {
        unsigned int res0:2;
        unsigned int frac:18;
        unsigned int integer:4;
        unsigned int res1:8;
    } bits;
};

union GSU_HCOEFF_REG {
    unsigned int dwval;
    struct {
        unsigned int coef0:8;
        unsigned int coef1:8;
        unsigned int coef2:8;
        unsigned int coef3:8;
    } bits;
};

struct __gsu_reg_t {
    union GSU_CTRL_REG ctrl;        /* 0x0000 */
    unsigned int res0;      /* 0x0004 */
    union GSU_STATUS_REG status;        /* 0x0008 */
    union GSU_FIELD_CTRL_REG field; /* 0x000c */
    union GSU_BIST_REG bist;        /* 0x0010 */
    unsigned int res1[11];      /* 0x0014-3c */
    union GSU_OUTSIZE_REG outsize;  /* 0x0040 */
    unsigned int res5[15];      /* 0x0044-0x07c */
    union GSU_INSIZE_REG insize;        /* 0x0080 */
    unsigned int res2;      /* 0x0084 */
    union GSU_HSTEP_REG hstep;      /* 0x0088 */
    union GSU_VSTEP_REG vstep;      /* 0x008C */
    union GSU_HPHASE_REG hphase;        /* 0x0090 */
    unsigned int res3;      /* 0x0094 */
    union GSU_VPHASE0_REG vphase0;  /* 0x0098 */
    union GSU_VPHASE1_REG vphase1;  /* 0x009c */
    unsigned int res4[88];      /* 0x00a0-1fc */
    union GSU_HCOEFF_REG hcoeff[16];    /* 0x0200-0x23c */
};

#endif
