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
 *  File name   :       de_vsu_type.h
 *
 *  Description :       display engine 2.0 vsu struct declaration
 *
 *  History     :       2014/03/20  vito cheng  v0.1  Initial version
 *
 */
#ifndef __DE_VSU_TYPE_H__
#define __DE_VSU_TYPE_H__

/*
 * __vsu_reg_t
 */
union VSU_CTRL_REG {
    unsigned int dwval;
    struct {
        unsigned int en:1;
        unsigned int res0:3;
        unsigned int coef_switch_rdy:1;
        unsigned int res1:25;
        unsigned int reset:1;
        unsigned int bist:1;
    } bits;
};

union VSU_STATUS_REG {
    unsigned int dwval;
    struct {
        unsigned int res0:4;
        unsigned int busy:1;
        unsigned int res1:11;
        unsigned int line_cnt:12;
        unsigned int res2:4;
    } bits;
};

union VSU_FIELD_CTRL_REG {
    unsigned int dwval;
    struct {
        unsigned int vphase_sel_en:1;
        unsigned int res0:31;
    } bits;
};

union VSU_OUTSIZE_REG {
    unsigned int dwval;
    struct {
        unsigned int width:13;
        unsigned int res0:3;
        unsigned int height:13;
        unsigned int res1:3;
    } bits;
};

union VSU_INSIZE_REG {
    unsigned int dwval;
    struct {
        unsigned int width:13;
        unsigned int res0:3;
        unsigned int height:13;
        unsigned int res1:3;
    } bits;
};

union VSU_HSTEP_REG {
    unsigned int dwval;
    struct {
        unsigned int res0:1;
        unsigned int frac:19;
        unsigned int integer:4;
        unsigned int res1:8;
    } bits;
};

union VSU_VSTEP_REG {
    unsigned int dwval;
    struct {
        unsigned int res0:1;
        unsigned int frac:19;
        unsigned int integer:4;
        unsigned int res1:8;
    } bits;
};

union VSU_HPHASE_REG {
    unsigned int dwval;
    struct {
        unsigned int res0:1;
        unsigned int frac:19;
        unsigned int integer:4;
        unsigned int res1:8;
    } bits;
};

union VSU_VPHASE0_REG {
    unsigned int dwval;
    struct {
        unsigned int res0:1;
        unsigned int frac:19;
        unsigned int integer:4;
        unsigned int res1:8;
    } bits;
};

union VSU_VPHASE1_REG {
    unsigned int dwval;
    struct {
        unsigned int res0:1;
        unsigned int frac:19;
        unsigned int integer:4;
        unsigned int res1:8;
    } bits;
};

union VSU_COEFF_REG {
    unsigned int dwval;
    struct {
        unsigned int coef0:8;
        unsigned int coef1:8;
        unsigned int coef2:8;
        unsigned int coef3:8;
    } bits;
};

struct __vsu_reg_t {
    union VSU_CTRL_REG ctrl;        /* 0x0000 */
    unsigned int res0;      /* 0x0004 */
    union VSU_STATUS_REG status;        /* 0x0008 */
    union VSU_FIELD_CTRL_REG field; /* 0x000c */
    unsigned int res1[12];      /* 0x0010-3c */
    union VSU_OUTSIZE_REG outsize;  /* 0x0040 */
    unsigned int res13[15];     /* 0x0044-0x07c */
    union VSU_INSIZE_REG ysize;     /* 0x0080 */
    unsigned int res2;      /* 0x0084 */
    union VSU_HSTEP_REG yhstep;     /* 0x0088 */
    union VSU_VSTEP_REG yvstep;     /* 0x008C */
    union VSU_HPHASE_REG yhphase;       /* 0x0090 */
    unsigned int res3;      /* 0x0094 */
    union VSU_VPHASE0_REG yvphase0; /* 0x0098 */
    union VSU_VPHASE1_REG yvphase1; /* 0x009c */
    unsigned int res4[8];       /* 0x00a0-bc */
    union VSU_INSIZE_REG csize;     /* 0x00c0 */
    unsigned int res5;      /* 0x00c4 */
    union VSU_HSTEP_REG chstep;     /* 0x00c8 */
    union VSU_VSTEP_REG cvstep;     /* 0x00cC */
    union VSU_HPHASE_REG chphase;       /* 0x00d0 */
    unsigned int res6;      /* 0x00d4 */
    union VSU_VPHASE0_REG cvphase0; /* 0x00d8 */
    union VSU_VPHASE1_REG cvphase1; /* 0x00dc */
    unsigned int res7[72];      /* 0x00e0-0x1fc */
    union VSU_COEFF_REG yhcoeff0[32];   /* 0x0200-0x27c */
    unsigned int res8[32];      /* 0x0280-0x2fc */
    union VSU_COEFF_REG yhcoeff1[32];   /* 0x0300-0x37c */
    unsigned int res9[32];      /* 0x0380-0x3fc */
    union VSU_COEFF_REG yvcoeff[32];    /* 0x0400-0x47c */
    unsigned int res10[96];     /* 0x0480-0x5fc */
    union VSU_COEFF_REG chcoeff0[32];   /* 0x0600-0x67c */
    unsigned int res11[32];     /* 0x0680-0x6fc */
    union VSU_COEFF_REG chcoeff1[32];   /* 0x0700-0x77c */
    unsigned int res12[32];     /* 0x0780-0x7fc */
    union VSU_COEFF_REG cvcoeff[32];    /* 0x0800-0x87c */
};

#endif
