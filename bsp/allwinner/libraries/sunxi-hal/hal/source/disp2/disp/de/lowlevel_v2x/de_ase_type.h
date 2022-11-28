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
 *  File name   :   de_ase_type.h
 *
 *  Description :   display engine 2.0 ase struct declaration
 *
 *  History     :   2014/04/01  vito cheng  v0.1  Initial version
 *
******************************************************************************/

#ifndef __DE_ASE_TYPE_H__
#define __DE_ASE_TYPE_H__

#include "de_rtmx.h"

#define ASE_PARA_NUM  1
#define ASE_MODE_NUM  4
union ASE_CTRL_REG {
    unsigned int dwval;
    struct {
        unsigned int en:1;
        unsigned int win_en:1;
        unsigned int res0:30;
    } bits;
};

union ASE_SIZE_REG {
    unsigned int dwval;
    struct {
        unsigned int width:12;
        unsigned int res0:4;
        unsigned int height:12;
        unsigned int res1:4;
    } bits;
};

union ASE_WIN0_REG {
    unsigned int dwval;
    struct {
        unsigned int left:12;
        unsigned int res0:4;
        unsigned int top:12;
        unsigned int res1:4;
    } bits;
};

union ASE_WIN1_REG {
    unsigned int dwval;
    struct {
        unsigned int right:12;
        unsigned int res0:4;
        unsigned int bot:12;
        unsigned int res1:4;
    } bits;
};

union ASE_GAIN_REG {
    unsigned int dwval;
    struct {
        unsigned int gain:5;
        unsigned int res0:27;
    } bits;
};

struct __ase_reg_t {
    union ASE_CTRL_REG ctrl;
    union ASE_SIZE_REG size;
    union ASE_WIN0_REG win0;
    union ASE_WIN1_REG win1;
    union ASE_GAIN_REG gain;
};

struct __ase_config_data {
    /* ase */
    unsigned int ase_en;
    unsigned int gain;

    /* window */
    unsigned int win_en;
    struct de_rect win;
};
#endif
