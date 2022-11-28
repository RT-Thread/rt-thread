/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DISP_EINK_DATA_H__
#define __DISP_EINK_DATA_H__

#include "../include.h"
#ifdef EINK_DRIVER      /* if you have eink driver, pls define this macro */
#include "../disp_eink.h"
#endif


#define     EINK_PANEL_W            800
#define     EINK_PANEL_H            600

#define     EINK_LSL                10
#define     EINK_LBL                4
#define     EINK_LDL                (EINK_PANEL_W/4)        /* 1024/4 = 256, */
#define     EINK_LEL                44
#define     EINK_HYNC               (EINK_LSL+EINK_LBL+EINK_LEL)   /* 58 */

#define     EINK_FSL                5
#define     EINK_FBL                4
#define     EINK_FDL                EINK_PANEL_H                   /* 758 */
#define     EINK_FEL                12
#define     EINK_VYNC               (EINK_FSL+EINK_FBL+EINK_FEL)   /* 20 */

#define     EINK_LCD_W              (EINK_LDL+EINK_HYNC)    /* 256+58=314 */
#define     EINK_LCD_H              (EINK_FDL+EINK_VYNC)    /* 758+20=778 */

#define     EINK_WF_WIDTH           EINK_LCD_W      /* 314 */
#define     EINK_WF_HEIGHT          EINK_LCD_H      /* 778 */

#if 0

#ifndef EINK_DRIVER
struct eink_timing_param {
    unsigned int lbl; /*  */
    unsigned int lel; /*  */
    unsigned int lsl;
    unsigned int fbl; /*  */
    unsigned int fel; /*  */
    unsigned int fsl; /*  */
    unsigned int width;  /* image width */
    unsigned int height;  /* image height */
};
#endif
#endif
/************A13 TCON INTERFACE********
D23->STV
D22->CKV
D21->STH
D20->OEH
D15->MODE
D13->LEH

D12->D7
D11->D6
D10->D5
D7->D4
D6->D3
D5->D2
D4->D1
D3->D0
*************************************/
typedef union {
    __u32 dwval;
    struct {
        __u32 res0              :  3;    /* D0~D2 */
        __u32 d0        :  1;    /* D3 */
        __u32 d1        :  1;    /* D4 */
        __u32 d2        :  1;    /* D5 */
        __u32 d3        :  1;    /* D6 */
        __u32 d4        :  1;    /* D7 */

        __u32 res1              :  2;    /* D8~D9 */
        __u32 d5        :  1;    /* D10 */
        __u32 d6        :  1;    /* D11 */
        __u32 d7        :  1;    /* D12 */
        __u32 leh       :  1;    /* D13 */
        __u32 res2      :  1;    /* D14 */
        __u32 mode      :  1;     /* D15 */

        __u32 res3      :  4;    /* D16~D19 */
        __u32 oeh       :  1;    /* D20 */
        __u32 sth       :  1;    /* D21 */
        __u32 ckv       :  1;    /* D22 */
        __u32 stv       :  1;    /* D23 */

        __u32 res4              :  8;    /* D24~D31 */
    } bits;
} A13_WAVEDATA;

/************8DATA TCON INTERFACE********
D15->D7
D14->D6
D13->D5
D12->D4
D11->D3
D10->D2
D9->D1
D8->D0

D5->STV
D4->CKV
D3->STH
D2->LEH
D1->OEH
D0->MODE
****************************************/
typedef union {
    __u16 dwval;
    struct {
        __u16 mode              :  1;    /* D0 */
        __u16 oeh       :  1;     /* D1 */
        __u16 leh       :  1;    /* D2 */
        __u16 sth       :  1;     /* D3 */
        __u16 ckv       :  1;     /* D4 */
        __u16 stv       :  1;     /* D5 */
        __u16 res0          :  2;    /* D6~D7 */

        __u16 d0        :  1;    /* D8 */
        __u16 d1        :  1;    /* D9 */
        __u16 d2        :  1;    /* D10 */
        __u16 d3        :  1;    /* D11 */
        __u16 d4        :  1;    /* D12 */
        __u16 d5        :  1;    /* D13 */
        __u16 d6        :  1;    /* D14 */
        __u16 d7        :  1;    /* D15 */
    } bits;
} WAVEDATA_8;


/************16DATA TCON INTERFACE********
D23->D15
D22->D14
D21->D13
D20->D12
D19->D11
D18->D10
D17->D9
D16->D8

D15->D7
D14->D6
D13->D5
D12->D4
D11->D3
D10->D2
D9->D1
D8->D0

D5->STV
D4->CKV
D3->STH
D2->LEH
D1->OEH
D0->MODE
****************************************/

typedef union {
    __u32 dwval;
    struct {
        __u32 mode              :  1;    /* D0 */
        __u32 oeh       :  1;     /* D1 */
        __u32 leh       :  1;    /* D2 */
        __u32 sth       :  1;     /* D3 */
        __u32 ckv       :  1;     /* D4 */
        __u32 stv       :  1;     /* D5 */
        __u32 res0          :  2;    /* D6~D7 */

        __u32 d0        :  1;    /* D8 */
        __u32 d1        :  1;    /* D9 */
        __u32 d2        :  1;    /* D10 */
        __u32 d3        :  1;    /* D11 */
        __u32 d4        :  1;    /* D12 */
        __u32 d5        :  1;    /* D13 */
        __u32 d6        :  1;    /* D14 */
        __u32 d7        :  1;    /* D15 */

        __u32 d8        :  1;    /* D16 */
        __u32 d9        :  1;    /* D17 */
        __u32 d10               :  1;    /* D18 */
        __u32 d11               :  1;    /* D19 */
        __u32 d12               :  1;    /* D20 */
        __u32 d13               :  1;    /* D21 */
        __u32 d14               :  1;    /* D22 */
        __u32 d15               :  1;    /* D23 */

        __u32 res1          :  8;   /* D24~D31 */
    } bits;
} WAVEDATA_16;

extern int init_eink_ctrl_data_8(unsigned long wavedata_buf,
        struct eink_timing_param *eink_timing_info, unsigned int i);
extern int init_eink_ctrl_data_16(unsigned long wavedata_buf,
        struct eink_timing_param *eink_timing_info);
#endif
