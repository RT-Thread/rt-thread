/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

/* #include "../include.h" */
#include "rtmx_eink.h"
#include "de_rtmx.h"
#include <linux/kernel.h>

static unsigned int de_base;
/* #define de_writel writel */
/* #define de_readl readl */

#define de_writel(addr, val) (*((volatile unsigned long  *)(addr)) = (unsigned long)(val))
#define de_readl(addr) (*((volatile unsigned long  *)(addr)))


#define RTMX0_BASE 0x00100000
#define CSC0_BASE  0x001aa050
#define RTMX1_BASE 0x00200000
#define CSC1_BASE  0x002a0000

int csc_tab_601_fullrgbtoyuv[12] = {0x107, 0x204, 0x64, 0x4000,
                    0xFFFFFF68, 0xFFFFFED6, 0x1C2, 0x20000,
                    0x1C2, 0xFFFFFE87, 0xFFFFFFB7, 0x20000};
int csc_tab_601_yuvtofullrgb[12] = {0x4A8, 0x0, 0x662, 0xFFFC865A,
                0x4A8, 0xFFFFFE70, 0xFFFFFCBF, 0x00021FF4,
                0x4A8, 0x812, 0x0, 0xFFFBAE4A};

int rtmx_set_base(unsigned int reg_base)
{
    de_base = reg_base;
    pr_info("%s: set de base = 0x%x\n", __func__, reg_base);
    return 0;
}


/* csc_mode:0:yuv2rgb,1:rgb2yuv */
void csc_set(int csc_mode, int sel, int csc_en)
{
    int i;
    unsigned int csc_base;

    csc_base = sel ? (de_base + CSC1_BASE) : (de_base + CSC0_BASE);
    for (i = 0; i < 12; i++) {
        de_writel(csc_base + 0x10 + (i << 2),
            csc_mode ? csc_tab_601_fullrgbtoyuv[i] :
                csc_tab_601_yuvtofullrgb[i]);
    }
    de_writel(csc_base + 0x0, csc_en);
}

#if 0
/* sel:0:rt-mixer0,1:rt-mixer1 */
/* addr0:y/argb addr;addr1:u addr;addr2:u addr; */
/* csc_en:0:disable csc,1:enable csc */
/* fmt: input fmt */
/* DE_FORMAT_ARGB_8888                    = 0x00,//MSB  A-R-G-B  LSB */
/* DE_FORMAT_ABGR_8888                    = 0x01, */
/* DE_FORMAT_RGBA_8888                    = 0x02, */
/* DE_FORMAT_BGRA_8888                    = 0x03, */
/* DE_FORMAT_XRGB_8888                    = 0x04, */
/* DE_FORMAT_XBGR_8888                    = 0x05, */
/* DE_FORMAT_RGBX_8888                    = 0x06, */
/* DE_FORMAT_BGRX_8888                    = 0x07, */
/* DE_FORMAT_RGB_888                      = 0x08, */
/* DE_FORMAT_BGR_888                      = 0x09, */
/* DE_FORMAT_RGB_565                      = 0x0a, */
/* DE_FORMAT_BGR_565                      = 0x0b, */
/* DE_FORMAT_ARGB_4444                    = 0x0c, */
/* DE_FORMAT_ABGR_4444                    = 0x0d, */
/* DE_FORMAT_RGBA_4444                    = 0x0e, */
/* DE_FORMAT_BGRA_4444                    = 0x0f, */
/* DE_FORMAT_ARGB_1555                    = 0x10, */
/* DE_FORMAT_ABGR_1555                    = 0x11, */
/* DE_FORMAT_RGBA_5551                    = 0x12, */
/* DE_FORMAT_BGRA_5551                    = 0x13, */
/*  */
/* SP: semi-planar, P:planar, I:interleaved */
/* UVUV: U in the LSBs;     VUVU: V in the LSBs */
/* DE_FORMAT_YUV444_I_AYUV               = 0x40,//MSB  A-Y-U-V  LSB, reserved */
/* DE_FORMAT_YUV444_I_VUYA               = 0x41,//MSB  V-U-Y-A  LSB */
/* DE_FORMAT_YUV422_I_YVYU               = 0x42,//MSB  Y-V-Y-U  LSB */
/* DE_FORMAT_YUV422_I_YUYV               = 0x43,//MSB  Y-U-Y-V  LSB */
/* DE_FORMAT_YUV422_I_UYVY               = 0x44,//MSB  U-Y-V-Y  LSB */
/* DE_FORMAT_YUV422_I_VYUY               = 0x45,//MSB  V-Y-U-Y  LSB */
/* DE_FORMAT_YUV444_P            = 0x46,//MSB  P3-2-1-0 LSB, */
/*                  YYYY UUUU VVVV, reserved */
/* DE_FORMAT_YUV422_P            = 0x47,//MSB  P3-2-1-0 LSB   YYYY UU   VV */
/* DE_FORMAT_YUV420_P            = 0x48,//MSB  P3-2-1-0 LSB   YYYY U    V */
/* DE_FORMAT_YUV411_P            = 0x49,//MSB  P3-2-1-0 LSB   YYYY U    V */
/* DE_FORMAT_YUV422_SP_UVUV               = 0x4a,//MSB  V-U-V-U  LSB */
/* DE_FORMAT_YUV422_SP_VUVU               = 0x4b,//MSB  U-V-U-V  LSB */
/* DE_FORMAT_YUV420_SP_UVUV               = 0x4c, */
/* DE_FORMAT_YUV420_SP_VUVU               = 0x4d, */
/* DE_FORMAT_YUV411_SP_UVUV               = 0x4e, */
/* DE_FORMAT_YUV411_SP_VUVU               = 0x4f, */
void rt_mixer_set(int sel, unsigned int addr0, unsigned int addr1,
        unsigned int addr2, unsigned int w, unsigned int h,
        unsigned int outw, unsigned int outh, unsigned int fmt)
{
    int ycnt, ccnt, uisel;
    int cinw, cinh, r_fmt;
    unsigned int yhstep, yvstep, chstep, cvstep;
    unsigned int base;

    uisel = 0;
    base = sel ? (de_base + RTMX1_BASE) : (de_base + RTMX0_BASE);

    if (fmt == DE_FORMAT_YUV422_I_VYUY) {
        r_fmt = 0x0;
    } else if (fmt == DE_FORMAT_YUV422_I_YVYU) {
        r_fmt = 0x1;
    } else if (fmt == DE_FORMAT_YUV422_I_YVYU) {
        r_fmt = 0x1;
    } else if (fmt == DE_FORMAT_YUV422_I_UYVY) {
        r_fmt = 0x2;
    } else if (fmt == DE_FORMAT_YUV422_I_UYVY) {
        r_fmt = 0x2;
    } else if (fmt == DE_FORMAT_YUV422_I_YUYV) {
        r_fmt = 0x3;
    } else if (fmt == DE_FORMAT_YUV422_I_YUYV) {
        r_fmt = 0x3;
    } else if (fmt == DE_FORMAT_YUV422_SP_VUVU) {
        r_fmt = 0x5;
    } else if (fmt == DE_FORMAT_YUV422_SP_VUVU) {
        r_fmt = 0x5;
    } else if (fmt == DE_FORMAT_YUV422_SP_UVUV) {
        r_fmt = 0x4;
    } else if (fmt == DE_FORMAT_YUV422_SP_UVUV) {
        r_fmt = 0x4;
    } else if (fmt == DE_FORMAT_YUV422_P) {
        r_fmt = 0x6;
    } else if (fmt == DE_FORMAT_YUV422_P) {
        r_fmt = 0x6;
    } else if (fmt == DE_FORMAT_YUV420_SP_VUVU) {
        r_fmt = 0x9;
    } else if (fmt == DE_FORMAT_YUV420_SP_VUVU) {
        r_fmt = 0x9;
    } else if (fmt == DE_FORMAT_YUV420_SP_UVUV) {
        r_fmt = 0x8;
    } else if (fmt == DE_FORMAT_YUV420_SP_UVUV) {
        r_fmt = 0x8;
    } else if (fmt == DE_FORMAT_YUV420_P) {
        r_fmt = 0xa;
    } else if (fmt == DE_FORMAT_YUV420_P) {
        r_fmt = 0xa;
    } else if (fmt == DE_FORMAT_YUV411_SP_VUVU) {
        r_fmt = 0xd;
    } else if (fmt == DE_FORMAT_YUV411_SP_VUVU) {
        r_fmt = 0xd;
    } else if (fmt == DE_FORMAT_YUV411_SP_UVUV) {
        r_fmt = 0xc;
    } else if (fmt == DE_FORMAT_YUV411_SP_UVUV) {
        r_fmt = 0xc;
    } else if (fmt == DE_FORMAT_YUV411_P) {
        r_fmt = 0xe;
    } else if (fmt == DE_FORMAT_YUV411_P) {
        r_fmt = 0xe;
    } else {
        uisel = 0x1;
        r_fmt = fmt;
    }

    ccnt = 0;
    if (!uisel) {
        if       (r_fmt <= 0x3)   {
            ycnt = 2;
            cinw = w>>1;
            cinh = h;
        } else if    (r_fmt == 0x6)   {
            ycnt = 1;
            ccnt = 1;
            cinw = w >> 1;
            cinh = h;
        } else if    (r_fmt <= 0x9)   {
            ycnt = 1;
            ccnt = 0;
            cinw = w >> 1;
            cinh = h >> 1;
        } else if    (r_fmt == 0xa)   {
            ycnt = 1;
            ccnt = 1;
            cinw = w >> 1;
            cinh = h >> 1;
        } else if    (r_fmt <= 0xd)   {
            ycnt = 1;
            ccnt = 1;
            cinw = w >> 2;
            cinh = h;
        } else if    (r_fmt == 0xe)   {
            ycnt = 1;
            ccnt = 2;
            cinw = w >> 2;
            cinh = h;
        }
        if       ((r_fmt == 0x4) || (r_fmt == 0x5)) {
            cinw = w>>1;
            cinh = h;
        }
        csc_set(0, sel, 1);
    } else {
        if (r_fmt <= 0x7)
            ycnt = 4;
        else if  (r_fmt <= 0x9)
            ycnt = 3;
        else
            ycnt = 2;
        cinw = w;
        cinh = h;
        csc_set(1, sel, 0);
    }

    yhstep = (w<<20)/outw;
    yvstep = (h<<20)/outh;
    chstep = (cinw<<20)/outw;
    cvstep = (cinh<<20)/outh;

    /* [RTMX] */
    de_writel(base + 0x00000, 0x00000000);
    de_writel(base + 0x01000, 0x00000100);
    de_writel(base + 0x01004, 0x00000000);
    de_writel(base + 0x01008, ((outh - 1) << 16) | (outw - 1));
    de_writel(base + 0x0100c, 0x00000000);
    de_writel(base + 0x01010, 0x00000000);
    de_writel(base + 0x01014, 0x00000000);
    de_writel(base + 0x01018, 0x00000000);
    de_writel(base + 0x0101c, 0x00000000);
    de_writel(base + 0x01020, 0x00000000);
    de_writel(base + 0x01024, 0x00000000);
    de_writel(base + 0x01028, 0x00000000);
    de_writel(base + 0x0102c, 0x00000000);
    de_writel(base + 0x01030, 0x00000000);
    de_writel(base + 0x01034, 0x00000000);
    de_writel(base + 0x01038, 0x00000000);
    de_writel(base + 0x0103c, 0x00000000);
    de_writel(base + 0x01040, 0x00000000);
    de_writel(base + 0x01044, 0x00000000);
    de_writel(base + 0x01048, 0x00000000);
    de_writel(base + 0x0104c, 0x00000000);
    de_writel(base + 0x01050, 0x00000000);
    de_writel(base + 0x01054, 0x00000000);
    de_writel(base + 0x01058, 0x00000000);
    de_writel(base + 0x0105c, 0x00000000);
    de_writel(base + 0x01060, 0x00000000);
    de_writel(base + 0x01064, 0x00000000);
    de_writel(base + 0x01068, 0x00000000);
    de_writel(base + 0x0106c, 0x00000000);
    de_writel(base + 0x01070, 0x00000000);
    de_writel(base + 0x01074, 0x00000000);
    de_writel(base + 0x01078, 0x00000000);
    de_writel(base + 0x0107c, 0x00000000);
    de_writel(base + 0x01080, 0x00043210);
    de_writel(base + 0x01084, 0x00000000);
    de_writel(base + 0x01088, 0xffff0000);
    de_writel(base + 0x0108c, ((outh - 1) << 16) | (outw - 1));
    de_writel(base + 0x01090, 0x03010301);
    de_writel(base + 0x01094, 0x03010301);
    de_writel(base + 0x01098, 0x03010301);
    de_writel(base + 0x0109c, 0x03010301);
    de_writel(base + 0x010a0, 0x00000000);
    de_writel(base + 0x010a4, 0x00000000);
    de_writel(base + 0x010a8, 0x00000000);
    de_writel(base + 0x010ac, 0x00000000);
    de_writel(base + 0x010b0, 0x00000000);
    de_writel(base + 0x010b4, 0x00000000);
    de_writel(base + 0x010b8, 0x00000000);
    de_writel(base + 0x010bc, 0x00000000);
    de_writel(base + 0x010c0, 0x00000000);
    de_writel(base + 0x010c4, 0x00000000);
    de_writel(base + 0x010c8, 0x00000000);
    de_writel(base + 0x010cc, 0x00000000);
    de_writel(base + 0x010d0, 0x00000000);
    de_writel(base + 0x010d4, 0x00000000);
    de_writel(base + 0x010d8, 0x00000000);
    de_writel(base + 0x010dc, 0x00000000);
    de_writel(base + 0x010e0, 0x00000000);
    de_writel(base + 0x010e4, 0x00000000);
    de_writel(base + 0x010e8, 0x00000000);
    de_writel(base + 0x010ec, 0x00000000);
    de_writel(base + 0x010f0, 0x00000000);
    de_writel(base + 0x010f4, 0x00000000);
    de_writel(base + 0x010f8, 0x00000000);
    de_writel(base + 0x010fc, 0x00000000);
    de_writel(base + 0x02000, (uisel << 15) | (r_fmt << 8) | 0x1);
    de_writel(base + 0x02004, ((h - 1) << 16) | (w - 1));
    de_writel(base + 0x02008, 0x00000000);
    de_writel(base + 0x0200c, (w * ycnt));
    de_writel(base + 0x02010, (w >> ccnt));
    de_writel(base + 0x02014, (w >> ccnt));
    de_writel(base + 0x02018, addr0);
    de_writel(base + 0x0201c, addr1);
    de_writel(base + 0x02020, addr2);
    de_writel(base + 0x02024, 0x00000000);
    de_writel(base + 0x02028, 0x00000000);
    de_writel(base + 0x0202c, 0x00000000);
    de_writel(base + 0x02030, 0x00000000);
    de_writel(base + 0x02034, 0x00000000);
    de_writel(base + 0x02038, 0x00000000);
    de_writel(base + 0x0203c, 0x00000000);
    de_writel(base + 0x02040, 0x00000000);
    de_writel(base + 0x02044, 0x00000000);
    de_writel(base + 0x02048, 0x00000000);
    de_writel(base + 0x0204c, 0x00000000);
    de_writel(base + 0x02050, 0x00000000);
    de_writel(base + 0x02054, 0x00000000);
    de_writel(base + 0x02058, 0x00000000);
    de_writel(base + 0x0205c, 0x00000000);
    de_writel(base + 0x02060, 0x00000000);
    de_writel(base + 0x02064, 0x00000000);
    de_writel(base + 0x02068, 0x00000000);
    de_writel(base + 0x0206c, 0x00000000);
    de_writel(base + 0x02070, 0x00000000);
    de_writel(base + 0x02074, 0x00000000);
    de_writel(base + 0x02078, 0x00000000);
    de_writel(base + 0x0207c, 0x00000000);
    de_writel(base + 0x02080, 0x00000000);
    de_writel(base + 0x02084, 0x00000000);
    de_writel(base + 0x02088, 0x00000000);
    de_writel(base + 0x0208c, 0x00000000);
    de_writel(base + 0x02090, 0x00000000);
    de_writel(base + 0x02094, 0x00000000);
    de_writel(base + 0x02098, 0x00000000);
    de_writel(base + 0x0209c, 0x00000000);
    de_writel(base + 0x020a0, 0x00000000);
    de_writel(base + 0x020a4, 0x00000000);
    de_writel(base + 0x020a8, 0x00000000);
    de_writel(base + 0x020ac, 0x00000000);
    de_writel(base + 0x020b0, 0x00000000);
    de_writel(base + 0x020b4, 0x00000000);
    de_writel(base + 0x020b8, 0x00000000);
    de_writel(base + 0x020bc, 0x00000000);
    de_writel(base + 0x020c0, 0x00000000);
    de_writel(base + 0x020c4, 0x00000000);
    de_writel(base + 0x020c8, 0x00000000);
    de_writel(base + 0x020cc, 0x00000000);
    de_writel(base + 0x020d0, 0x00000000);
    de_writel(base + 0x020d4, 0x00000000);
    de_writel(base + 0x020d8, 0x00000000);
    de_writel(base + 0x020dc, 0x00000000);
    de_writel(base + 0x020e0, 0x00000000);
    de_writel(base + 0x020e4, 0x00000000);
    de_writel(base + 0x020e8, ((h - 1) << 16) | (w - 1));
    de_writel(base + 0x020ec, 0x00000000);
    de_writel(base + 0x020f0, 0x00000000);
    de_writel(base + 0x020f4, 0x00000000);
    de_writel(base + 0x020f8, 0x00000000);
    de_writel(base + 0x020fc, 0x00000000);
    de_writel(base + 0x03000, 0x00000000);
    de_writel(base + 0x03004, 0x00000000);
    de_writel(base + 0x03008, 0x00000000);
    de_writel(base + 0x0300c, 0x00000000);
    de_writel(base + 0x03010, 0x00000000);
    de_writel(base + 0x03014, 0x00000000);
    de_writel(base + 0x03018, 0x00000000);
    de_writel(base + 0x0301c, 0x00000000);
    de_writel(base + 0x03020, 0x00000000);
    de_writel(base + 0x03024, 0x00000000);
    de_writel(base + 0x03028, 0x00000000);
    de_writel(base + 0x0302c, 0x00000000);
    de_writel(base + 0x03030, 0x00000000);
    de_writel(base + 0x03034, 0x00000000);
    de_writel(base + 0x03038, 0x00000000);
    de_writel(base + 0x0303c, 0x00000000);
    de_writel(base + 0x03040, 0x00000000);
    de_writel(base + 0x03044, 0x00000000);
    de_writel(base + 0x03048, 0x00000000);
    de_writel(base + 0x0304c, 0x00000000);
    de_writel(base + 0x03050, 0x00000000);
    de_writel(base + 0x03054, 0x00000000);
    de_writel(base + 0x03058, 0x00000000);
    de_writel(base + 0x0305c, 0x00000000);
    de_writel(base + 0x03060, 0x00000000);
    de_writel(base + 0x03064, 0x00000000);
    de_writel(base + 0x03068, 0x00000000);
    de_writel(base + 0x0306c, 0x00000000);
    de_writel(base + 0x03070, 0x00000000);
    de_writel(base + 0x03074, 0x00000000);
    de_writel(base + 0x03078, 0x00000000);
    de_writel(base + 0x0307c, 0x00000000);
    de_writel(base + 0x03080, 0x00000000);
    de_writel(base + 0x03084, 0x00000000);
    de_writel(base + 0x03088, 0x00000000);
    if (!sel) {
        de_writel(base + 0x04000, 0x00000000);
        de_writel(base + 0x04004, 0x00000000);
        de_writel(base + 0x04008, 0x00000000);
        de_writel(base + 0x0400c, 0x00000000);
        de_writel(base + 0x04010, 0x00000000);
        de_writel(base + 0x04014, 0x00000000);
        de_writel(base + 0x04018, 0x00000000);
        de_writel(base + 0x0401c, 0x00000000);
        de_writel(base + 0x04020, 0x00000000);
        de_writel(base + 0x04024, 0x00000000);
        de_writel(base + 0x04028, 0x00000000);
        de_writel(base + 0x0402c, 0x00000000);
        de_writel(base + 0x04030, 0x00000000);
        de_writel(base + 0x04034, 0x00000000);
        de_writel(base + 0x04038, 0x00000000);
        de_writel(base + 0x0403c, 0x00000000);
        de_writel(base + 0x04040, 0x00000000);
        de_writel(base + 0x04044, 0x00000000);
        de_writel(base + 0x04048, 0x00000000);
        de_writel(base + 0x0404c, 0x00000000);
        de_writel(base + 0x04050, 0x00000000);
        de_writel(base + 0x04054, 0x00000000);
        de_writel(base + 0x04058, 0x00000000);
        de_writel(base + 0x0405c, 0x00000000);
        de_writel(base + 0x04060, 0x00000000);
        de_writel(base + 0x04064, 0x00000000);
        de_writel(base + 0x04068, 0x00000000);
        de_writel(base + 0x0406c, 0x00000000);
        de_writel(base + 0x04070, 0x00000000);
        de_writel(base + 0x04074, 0x00000000);
        de_writel(base + 0x04078, 0x00000000);
        de_writel(base + 0x0407c, 0x00000000);
        de_writel(base + 0x04080, 0x00000000);
        de_writel(base + 0x04084, 0x00000000);
        de_writel(base + 0x04088, 0x00000000);
        de_writel(base + 0x05000, 0x00000000);
        de_writel(base + 0x05004, 0x00000000);
        de_writel(base + 0x05008, 0x00000000);
        de_writel(base + 0x0500c, 0x00000000);
        de_writel(base + 0x05010, 0x00000000);
        de_writel(base + 0x05014, 0x00000000);
        de_writel(base + 0x05018, 0x00000000);
        de_writel(base + 0x0501c, 0x00000000);
        de_writel(base + 0x05020, 0x00000000);
        de_writel(base + 0x05024, 0x00000000);
        de_writel(base + 0x05028, 0x00000000);
        de_writel(base + 0x0502c, 0x00000000);
        de_writel(base + 0x05030, 0x00000000);
        de_writel(base + 0x05034, 0x00000000);
        de_writel(base + 0x05038, 0x00000000);
        de_writel(base + 0x0503c, 0x00000000);
        de_writel(base + 0x05040, 0x00000000);
        de_writel(base + 0x05044, 0x00000000);
        de_writel(base + 0x05048, 0x00000000);
        de_writel(base + 0x0504c, 0x00000000);
        de_writel(base + 0x05050, 0x00000000);
        de_writel(base + 0x05054, 0x00000000);
        de_writel(base + 0x05058, 0x00000000);
        de_writel(base + 0x0505c, 0x00000000);
        de_writel(base + 0x05060, 0x00000000);
        de_writel(base + 0x05064, 0x00000000);
        de_writel(base + 0x05068, 0x00000000);
        de_writel(base + 0x0506c, 0x00000000);
        de_writel(base + 0x05070, 0x00000000);
        de_writel(base + 0x05074, 0x00000000);
        de_writel(base + 0x05078, 0x00000000);
        de_writel(base + 0x0507c, 0x00000000);
        de_writel(base + 0x05080, 0x00000000);
        de_writel(base + 0x05084, 0x00000000);
        de_writel(base + 0x05088, 0x00000000);
    }
    de_writel(base + 0x00004, 0x00000000);
    de_writel(base + 0x00008, 0x00000001);
    de_writel(base + 0x0000c, ((outh - 1) << 16) | (outw - 1));
    de_writel(base + 0x00000, 0x00000001);

    /* [SCALERVIDEO_0] */
    de_writel(base + 0x2000c, 0x00000000);
    de_writel(base + 0x20040, ((outh - 1) << 16) | (outw - 1));
    de_writel(base + 0x20080, ((h - 1) << 16) | (w - 1));
    de_writel(base + 0x20088, yhstep);
    de_writel(base + 0x2008c, yvstep);
    de_writel(base + 0x20090, 0x00000000);
    de_writel(base + 0x20098, 0x00000000);
    de_writel(base + 0x2009c, 0x00000000);
    de_writel(base + 0x200c0, ((cinh - 1) << 16) | (cinw - 1));/*  */
    de_writel(base + 0x200c8, chstep);
    de_writel(base + 0x200cc, cvstep);
    de_writel(base + 0x200d0, 0x00000000);
    de_writel(base + 0x200d8, 0x00000000);
    de_writel(base + 0x200dc, 0x00000000);
    de_writel(base + 0x20200, 0x40000000);
    de_writel(base + 0x20204, 0x40fe0000);
    de_writel(base + 0x20208, 0x3ffd0100);
    de_writel(base + 0x2020c, 0x3efc0100);
    de_writel(base + 0x20210, 0x3efb0100);
    de_writel(base + 0x20214, 0x3dfa0200);
    de_writel(base + 0x20218, 0x3cf90200);
    de_writel(base + 0x2021c, 0x3bf80200);
    de_writel(base + 0x20220, 0x39f70200);
    de_writel(base + 0x20224, 0x37f70200);
    de_writel(base + 0x20228, 0x35f70200);
    de_writel(base + 0x2022c, 0x33f70200);
    de_writel(base + 0x20230, 0x31f70200);
    de_writel(base + 0x20234, 0x2ef70200);
    de_writel(base + 0x20238, 0x2cf70200);
    de_writel(base + 0x2023c, 0x2af70200);
    de_writel(base + 0x20240, 0x27f70200);
    de_writel(base + 0x20244, 0x24f80100);
    de_writel(base + 0x20248, 0x22f80100);
    de_writel(base + 0x2024c, 0x1ef90100);
    de_writel(base + 0x20250, 0x1cf90100);
    de_writel(base + 0x20254, 0x19fa0100);
    de_writel(base + 0x20258, 0x17fa0100);
    de_writel(base + 0x2025c, 0x14fb0100);
    de_writel(base + 0x20260, 0x11fc0000);
    de_writel(base + 0x20264, 0x0ffc0000);
    de_writel(base + 0x20268, 0x0cfd0000);
    de_writel(base + 0x2026c, 0x0afd0000);
    de_writel(base + 0x20270, 0x08fe0000);
    de_writel(base + 0x20274, 0x05ff0000);
    de_writel(base + 0x20278, 0x03ff0000);
    de_writel(base + 0x2027c, 0x02000000);
    de_writel(base + 0x20300, 0x00000000);
    de_writel(base + 0x20304, 0x00000002);
    de_writel(base + 0x20308, 0x0000ff04);
    de_writel(base + 0x2030c, 0x0000ff06);
    de_writel(base + 0x20310, 0x0000fe08);
    de_writel(base + 0x20314, 0x0000fd0a);
    de_writel(base + 0x20318, 0x0000fd0c);
    de_writel(base + 0x2031c, 0x0000fc0f);
    de_writel(base + 0x20320, 0x0000fc12);
    de_writel(base + 0x20324, 0x0001fb14);
    de_writel(base + 0x20328, 0x0001fa17);
    de_writel(base + 0x2032c, 0x0001fa19);
    de_writel(base + 0x20330, 0x0001f91c);
    de_writel(base + 0x20334, 0x0001f91f);
    de_writel(base + 0x20338, 0x0001f822);
    de_writel(base + 0x2033c, 0x0001f824);
    de_writel(base + 0x20340, 0x0002f727);
    de_writel(base + 0x20344, 0x0002f72a);
    de_writel(base + 0x20348, 0x0002f72c);
    de_writel(base + 0x2034c, 0x0002f72f);
    de_writel(base + 0x20350, 0x0002f731);
    de_writel(base + 0x20354, 0x0002f733);
    de_writel(base + 0x20358, 0x0002f735);
    de_writel(base + 0x2035c, 0x0002f737);
    de_writel(base + 0x20360, 0x0002f73a);
    de_writel(base + 0x20364, 0x0002f83b);
    de_writel(base + 0x20368, 0x0002f93c);
    de_writel(base + 0x2036c, 0x0002fa3d);
    de_writel(base + 0x20370, 0x0001fb3e);
    de_writel(base + 0x20374, 0x0001fc3f);
    de_writel(base + 0x20378, 0x0001fd40);
    de_writel(base + 0x2037c, 0x0000fe40);
    de_writel(base + 0x20400, 0x00004000);
    de_writel(base + 0x20404, 0x000140ff);
    de_writel(base + 0x20408, 0x00033ffe);
    de_writel(base + 0x2040c, 0x00043ffd);
    de_writel(base + 0x20410, 0x00063efc);
    de_writel(base + 0x20414, 0xff083dfc);
    de_writel(base + 0x20418, 0x000a3bfb);
    de_writel(base + 0x2041c, 0xff0d39fb);
    de_writel(base + 0x20420, 0xff0f37fb);
    de_writel(base + 0x20424, 0xff1136fa);
    de_writel(base + 0x20428, 0xfe1433fb);
    de_writel(base + 0x2042c, 0xfe1631fb);
    de_writel(base + 0x20430, 0xfd192ffb);
    de_writel(base + 0x20434, 0xfd1c2cfb);
    de_writel(base + 0x20438, 0xfd1f29fb);
    de_writel(base + 0x2043c, 0xfc2127fc);
    de_writel(base + 0x20440, 0xfc2424fc);
    de_writel(base + 0x20444, 0xfc2721fc);
    de_writel(base + 0x20448, 0xfb291ffd);
    de_writel(base + 0x2044c, 0xfb2c1cfd);
    de_writel(base + 0x20450, 0xfb2f19fd);
    de_writel(base + 0x20454, 0xfb3116fe);
    de_writel(base + 0x20458, 0xfb3314fe);
    de_writel(base + 0x2045c, 0xfa3611ff);
    de_writel(base + 0x20460, 0xfb370fff);
    de_writel(base + 0x20464, 0xfb390dff);
    de_writel(base + 0x20468, 0xfb3b0a00);
    de_writel(base + 0x2046c, 0xfc3d08ff);
    de_writel(base + 0x20470, 0xfc3e0600);
    de_writel(base + 0x20474, 0xfd3f0400);
    de_writel(base + 0x20478, 0xfe3f0300);
    de_writel(base + 0x2047c, 0xff400100);
    de_writel(base + 0x20600, 0x40000000);
    de_writel(base + 0x20604, 0x40fe0000);
    de_writel(base + 0x20608, 0x3ffd0100);
    de_writel(base + 0x2060c, 0x3efc0100);
    de_writel(base + 0x20610, 0x3efb0100);
    de_writel(base + 0x20614, 0x3dfa0200);
    de_writel(base + 0x20618, 0x3cf90200);
    de_writel(base + 0x2061c, 0x3bf80200);
    de_writel(base + 0x20620, 0x39f70200);
    de_writel(base + 0x20624, 0x37f70200);
    de_writel(base + 0x20628, 0x35f70200);
    de_writel(base + 0x2062c, 0x33f70200);
    de_writel(base + 0x20630, 0x31f70200);
    de_writel(base + 0x20634, 0x2ef70200);
    de_writel(base + 0x20638, 0x2cf70200);
    de_writel(base + 0x2063c, 0x2af70200);
    de_writel(base + 0x20640, 0x27f70200);
    de_writel(base + 0x20644, 0x24f80100);
    de_writel(base + 0x20648, 0x22f80100);
    de_writel(base + 0x2064c, 0x1ef90100);
    de_writel(base + 0x20650, 0x1cf90100);
    de_writel(base + 0x20654, 0x19fa0100);
    de_writel(base + 0x20658, 0x17fa0100);
    de_writel(base + 0x2065c, 0x14fb0100);
    de_writel(base + 0x20660, 0x11fc0000);
    de_writel(base + 0x20664, 0x0ffc0000);
    de_writel(base + 0x20668, 0x0cfd0000);
    de_writel(base + 0x2066c, 0x0afd0000);
    de_writel(base + 0x20670, 0x08fe0000);
    de_writel(base + 0x20674, 0x05ff0000);
    de_writel(base + 0x20678, 0x03ff0000);
    de_writel(base + 0x2067c, 0x02000000);
    de_writel(base + 0x20700, 0x00000000);
    de_writel(base + 0x20704, 0x00000002);
    de_writel(base + 0x20708, 0x0000ff04);
    de_writel(base + 0x2070c, 0x0000ff06);
    de_writel(base + 0x20710, 0x0000fe08);
    de_writel(base + 0x20714, 0x0000fd0a);
    de_writel(base + 0x20718, 0x0000fd0c);
    de_writel(base + 0x2071c, 0x0000fc0f);
    de_writel(base + 0x20720, 0x0000fc12);
    de_writel(base + 0x20724, 0x0001fb14);
    de_writel(base + 0x20728, 0x0001fa17);
    de_writel(base + 0x2072c, 0x0001fa19);
    de_writel(base + 0x20730, 0x0001f91c);
    de_writel(base + 0x20734, 0x0001f91f);
    de_writel(base + 0x20738, 0x0001f822);
    de_writel(base + 0x2073c, 0x0001f824);
    de_writel(base + 0x20740, 0x0002f727);
    de_writel(base + 0x20744, 0x0002f72a);
    de_writel(base + 0x20748, 0x0002f72c);
    de_writel(base + 0x2074c, 0x0002f72f);
    de_writel(base + 0x20750, 0x0002f731);
    de_writel(base + 0x20754, 0x0002f733);
    de_writel(base + 0x20758, 0x0002f735);
    de_writel(base + 0x2075c, 0x0002f737);
    de_writel(base + 0x20760, 0x0002f73a);
    de_writel(base + 0x20764, 0x0002f83b);
    de_writel(base + 0x20768, 0x0002f93c);
    de_writel(base + 0x2076c, 0x0002fa3d);
    de_writel(base + 0x20770, 0x0001fb3e);
    de_writel(base + 0x20774, 0x0001fc3f);
    de_writel(base + 0x20778, 0x0001fd40);
    de_writel(base + 0x2077c, 0x0000fe40);
    de_writel(base + 0x20800, 0x00004000);
    de_writel(base + 0x20804, 0x000140ff);
    de_writel(base + 0x20808, 0x00033ffe);
    de_writel(base + 0x2080c, 0x00043ffd);
    de_writel(base + 0x20810, 0x00063efc);
    de_writel(base + 0x20814, 0xff083dfc);
    de_writel(base + 0x20818, 0x000a3bfb);
    de_writel(base + 0x2081c, 0xff0d39fb);
    de_writel(base + 0x20820, 0xff0f37fb);
    de_writel(base + 0x20824, 0xff1136fa);
    de_writel(base + 0x20828, 0xfe1433fb);
    de_writel(base + 0x2082c, 0xfe1631fb);
    de_writel(base + 0x20830, 0xfd192ffb);
    de_writel(base + 0x20834, 0xfd1c2cfb);
    de_writel(base + 0x20838, 0xfd1f29fb);
    de_writel(base + 0x2083c, 0xfc2127fc);
    de_writel(base + 0x20840, 0xfc2424fc);
    de_writel(base + 0x20844, 0xfc2721fc);
    de_writel(base + 0x20848, 0xfb291ffd);
    de_writel(base + 0x2084c, 0xfb2c1cfd);
    de_writel(base + 0x20850, 0xfb2f19fd);
    de_writel(base + 0x20854, 0xfb3116fe);
    de_writel(base + 0x20858, 0xfb3314fe);
    de_writel(base + 0x2085c, 0xfa3611ff);
    de_writel(base + 0x20860, 0xfb370fff);
    de_writel(base + 0x20864, 0xfb390dff);
    de_writel(base + 0x20868, 0xfb3b0a00);
    de_writel(base + 0x2086c, 0xfc3d08ff);
    de_writel(base + 0x20870, 0xfc3e0600);
    de_writel(base + 0x20874, 0xfd3f0400);
    de_writel(base + 0x20878, 0xfe3f0300);
    de_writel(base + 0x2087c, 0xff400100);
    de_writel(base + 0x20000, 0x00000011);
    de_writel(base + 0x00008, 0x00000001);

}
#else
void rt_mixer_init(int sel, unsigned int addr0, unsigned int addr1,
        unsigned int addr2, unsigned int w, unsigned int h,
        unsigned int outw, unsigned int outh, unsigned int fmt)
{
    int ycnt, ccnt, uisel;
    int cinw, cinh, r_fmt;
    unsigned int yhstep, yvstep, chstep, cvstep;
    unsigned int base;

    uisel = 0;
    base = sel ? (de_base + RTMX1_BASE):(de_base + RTMX0_BASE);

    if (fmt == DE_FORMAT_YUV422_I_VYUY)
        r_fmt = 0x0;
    else if (fmt == DE_FORMAT_YUV422_I_YVYU)
        r_fmt = 0x1;
    else if (fmt == DE_FORMAT_YUV422_I_YVYU)
        r_fmt = 0x1;
    else if (fmt == DE_FORMAT_YUV422_I_UYVY)
        r_fmt = 0x2;
    else if (fmt == DE_FORMAT_YUV422_I_UYVY)
        r_fmt = 0x2;
    else if (fmt == DE_FORMAT_YUV422_I_YUYV)
        r_fmt = 0x3;
    else if (fmt == DE_FORMAT_YUV422_I_YUYV)
        r_fmt = 0x3;
    else if (fmt == DE_FORMAT_YUV422_SP_VUVU)
        r_fmt = 0x5;
    else if (fmt == DE_FORMAT_YUV422_SP_VUVU)
        r_fmt = 0x5;
    else if (fmt == DE_FORMAT_YUV422_SP_UVUV)
        r_fmt = 0x4;
    else if (fmt == DE_FORMAT_YUV422_SP_UVUV)
        r_fmt = 0x4;
    else if (fmt == DE_FORMAT_YUV422_P)
        r_fmt = 0x6;
    else if (fmt == DE_FORMAT_YUV422_P)
        r_fmt = 0x6;
    else if (fmt == DE_FORMAT_YUV420_SP_VUVU)
        r_fmt = 0x9;
    else if (fmt == DE_FORMAT_YUV420_SP_VUVU)
        r_fmt = 0x9;
    else if (fmt == DE_FORMAT_YUV420_SP_UVUV)
        r_fmt = 0x8;
    else if (fmt == DE_FORMAT_YUV420_SP_UVUV)
        r_fmt = 0x8;
    else if (fmt == DE_FORMAT_YUV420_P)
        r_fmt = 0xa;
    else if (fmt == DE_FORMAT_YUV420_P)
        r_fmt = 0xa;
    else if (fmt == DE_FORMAT_YUV411_SP_VUVU)
        r_fmt = 0xd;
    else if (fmt == DE_FORMAT_YUV411_SP_VUVU)
        r_fmt = 0xd;
    else if (fmt == DE_FORMAT_YUV411_SP_UVUV)
        r_fmt = 0xc;
    else if (fmt == DE_FORMAT_YUV411_SP_UVUV)
        r_fmt = 0xc;
    else if (fmt == DE_FORMAT_YUV411_P)
        r_fmt = 0xe;
    else if (fmt == DE_FORMAT_YUV411_P)
        r_fmt = 0xe;
    else {
        uisel = 0x1;
        r_fmt = fmt;
    }

    ccnt = 0;
    if (!uisel) {
        if (r_fmt <= 0x3) {
            ycnt = 2;
            cinw = w >> 1;
            cinh = h;
        } else if (r_fmt == 0x6) {
            ycnt = 1;
            ccnt = 1;
            cinw = w >> 1;
            cinh = h;
        } else if (r_fmt <= 0x9) {
            ycnt = 1;
            ccnt = 0;
            cinw = w >> 1;
            cinh = h >> 1;
        } else if (r_fmt == 0xa) {
            ycnt = 1;
            ccnt = 1;
            cinw = w >> 1;
            cinh = h >> 1;
        } else if (r_fmt <= 0xd) {
            ycnt = 1;
            ccnt = 1;
            cinw = w >> 2;
            cinh = h;
        } else if (r_fmt == 0xe) {
            ycnt = 1;
            ccnt = 2;
            cinw = w>>2; cinh = h;
        }
        if ((r_fmt == 0x4) || (r_fmt == 0x5)) {
            cinw = w >> 1;
            cinh = h;
        }
        csc_set(0, sel, 1);
    } else {
        if (r_fmt <= 0x7)
            ycnt = 4;
        else if (r_fmt <= 0x9)
            ycnt = 3;
        else
            ycnt = 2;
        cinw = w;
        cinh = h;
        csc_set(1, sel, 0);
    }

    yhstep = (w << 20) / outw;
    yvstep = (h << 20) / outh;
    chstep = (cinw << 20) / outw;
    cvstep = (cinh << 20) / outh;

    /* [RTMX] */
    de_writel(base + 0x00000, 0x00000000);
    de_writel(base + 0x01000, 0x00000100);
    de_writel(base + 0x01004, 0x00000000);
    de_writel(base + 0x01008, ((outh - 1) << 16)|(outw - 1));
    de_writel(base + 0x0100c, 0x00000000);
    de_writel(base + 0x01010, 0x00000000);
    de_writel(base + 0x01014, 0x00000000);
    de_writel(base + 0x01018, 0x00000000);
    de_writel(base + 0x0101c, 0x00000000);
    de_writel(base + 0x01020, 0x00000000);
    de_writel(base + 0x01024, 0x00000000);
    de_writel(base + 0x01028, 0x00000000);
    de_writel(base + 0x0102c, 0x00000000);
    de_writel(base + 0x01030, 0x00000000);
    de_writel(base + 0x01034, 0x00000000);
    de_writel(base + 0x01038, 0x00000000);
    de_writel(base + 0x0103c, 0x00000000);
    de_writel(base + 0x01040, 0x00000000);
    de_writel(base + 0x01044, 0x00000000);
    de_writel(base + 0x01048, 0x00000000);
    de_writel(base + 0x0104c, 0x00000000);
    de_writel(base + 0x01050, 0x00000000);
    de_writel(base + 0x01054, 0x00000000);
    de_writel(base + 0x01058, 0x00000000);
    de_writel(base + 0x0105c, 0x00000000);
    de_writel(base + 0x01060, 0x00000000);
    de_writel(base + 0x01064, 0x00000000);
    de_writel(base + 0x01068, 0x00000000);
    de_writel(base + 0x0106c, 0x00000000);
    de_writel(base + 0x01070, 0x00000000);
    de_writel(base + 0x01074, 0x00000000);
    de_writel(base + 0x01078, 0x00000000);
    de_writel(base + 0x0107c, 0x00000000);
    de_writel(base + 0x01080, 0x00043210);
    de_writel(base + 0x01084, 0x00000000);
    de_writel(base + 0x01088, 0xffff0000);
    de_writel(base + 0x0108c, ((outh - 1) << 16) | (outw - 1));
    de_writel(base + 0x01090, 0x03010301);
    de_writel(base + 0x01094, 0x03010301);
    de_writel(base + 0x01098, 0x03010301);
    de_writel(base + 0x0109c, 0x03010301);
    de_writel(base + 0x010a0, 0x00000000);
    de_writel(base + 0x010a4, 0x00000000);
    de_writel(base + 0x010a8, 0x00000000);
    de_writel(base + 0x010ac, 0x00000000);
    de_writel(base + 0x010b0, 0x00000000);
    de_writel(base + 0x010b4, 0x00000000);
    de_writel(base + 0x010b8, 0x00000000);
    de_writel(base + 0x010bc, 0x00000000);
    de_writel(base + 0x010c0, 0x00000000);
    de_writel(base + 0x010c4, 0x00000000);
    de_writel(base + 0x010c8, 0x00000000);
    de_writel(base + 0x010cc, 0x00000000);
    de_writel(base + 0x010d0, 0x00000000);
    de_writel(base + 0x010d4, 0x00000000);
    de_writel(base + 0x010d8, 0x00000000);
    de_writel(base + 0x010dc, 0x00000000);
    de_writel(base + 0x010e0, 0x00000000);
    de_writel(base + 0x010e4, 0x00000000);
    de_writel(base + 0x010e8, 0x00000000);
    de_writel(base + 0x010ec, 0x00000000);
    de_writel(base + 0x010f0, 0x00000000);
    de_writel(base + 0x010f4, 0x00000000);
    de_writel(base + 0x010f8, 0x00000000);
    de_writel(base + 0x010fc, 0x00000000);
    de_writel(base + 0x02000, (uisel << 15) | (r_fmt << 8) | 0x1);
    de_writel(base + 0x02004, ((h - 1) << 16) | (w - 1));
    de_writel(base + 0x02008, 0x00000000);
    de_writel(base + 0x0200c, (w * ycnt));
    de_writel(base + 0x02010, (w >> ccnt));
    de_writel(base + 0x02014, (w >> ccnt));
    de_writel(base + 0x02018, addr0);
    de_writel(base + 0x0201c, addr1);
    de_writel(base + 0x02020, addr2);
    de_writel(base + 0x02024, 0x00000000);
    de_writel(base + 0x02028, 0x00000000);
    de_writel(base + 0x0202c, 0x00000000);
    de_writel(base + 0x02030, 0x00000000);
    de_writel(base + 0x02034, 0x00000000);
    de_writel(base + 0x02038, 0x00000000);
    de_writel(base + 0x0203c, 0x00000000);
    de_writel(base + 0x02040, 0x00000000);
    de_writel(base + 0x02044, 0x00000000);
    de_writel(base + 0x02048, 0x00000000);
    de_writel(base + 0x0204c, 0x00000000);
    de_writel(base + 0x02050, 0x00000000);
    de_writel(base + 0x02054, 0x00000000);
    de_writel(base + 0x02058, 0x00000000);
    de_writel(base + 0x0205c, 0x00000000);
    de_writel(base + 0x02060, 0x00000000);
    de_writel(base + 0x02064, 0x00000000);
    de_writel(base + 0x02068, 0x00000000);
    de_writel(base + 0x0206c, 0x00000000);
    de_writel(base + 0x02070, 0x00000000);
    de_writel(base + 0x02074, 0x00000000);
    de_writel(base + 0x02078, 0x00000000);
    de_writel(base + 0x0207c, 0x00000000);
    de_writel(base + 0x02080, 0x00000000);
    de_writel(base + 0x02084, 0x00000000);
    de_writel(base + 0x02088, 0x00000000);
    de_writel(base + 0x0208c, 0x00000000);
    de_writel(base + 0x02090, 0x00000000);
    de_writel(base + 0x02094, 0x00000000);
    de_writel(base + 0x02098, 0x00000000);
    de_writel(base + 0x0209c, 0x00000000);
    de_writel(base + 0x020a0, 0x00000000);
    de_writel(base + 0x020a4, 0x00000000);
    de_writel(base + 0x020a8, 0x00000000);
    de_writel(base + 0x020ac, 0x00000000);
    de_writel(base + 0x020b0, 0x00000000);
    de_writel(base + 0x020b4, 0x00000000);
    de_writel(base + 0x020b8, 0x00000000);
    de_writel(base + 0x020bc, 0x00000000);
    de_writel(base + 0x020c0, 0x00000000);
    de_writel(base + 0x020c4, 0x00000000);
    de_writel(base + 0x020c8, 0x00000000);
    de_writel(base + 0x020cc, 0x00000000);
    de_writel(base + 0x020d0, 0x00000000);
    de_writel(base + 0x020d4, 0x00000000);
    de_writel(base + 0x020d8, 0x00000000);
    de_writel(base + 0x020dc, 0x00000000);
    de_writel(base + 0x020e0, 0x00000000);
    de_writel(base + 0x020e4, 0x00000000);
    de_writel(base + 0x020e8, ((h - 1) << 16) | (w - 1));
    de_writel(base + 0x020ec, 0x00000000);
    de_writel(base + 0x020f0, 0x00000000);
    de_writel(base + 0x020f4, 0x00000000);
    de_writel(base + 0x020f8, 0x00000000);
    de_writel(base + 0x020fc, 0x00000000);
    de_writel(base + 0x03000, 0x00000000);
    de_writel(base + 0x03004, 0x00000000);
    de_writel(base + 0x03008, 0x00000000);
    de_writel(base + 0x0300c, 0x00000000);
    de_writel(base + 0x03010, 0x00000000);
    de_writel(base + 0x03014, 0x00000000);
    de_writel(base + 0x03018, 0x00000000);
    de_writel(base + 0x0301c, 0x00000000);
    de_writel(base + 0x03020, 0x00000000);
    de_writel(base + 0x03024, 0x00000000);
    de_writel(base + 0x03028, 0x00000000);
    de_writel(base + 0x0302c, 0x00000000);
    de_writel(base + 0x03030, 0x00000000);
    de_writel(base + 0x03034, 0x00000000);
    de_writel(base + 0x03038, 0x00000000);
    de_writel(base + 0x0303c, 0x00000000);
    de_writel(base + 0x03040, 0x00000000);
    de_writel(base + 0x03044, 0x00000000);
    de_writel(base + 0x03048, 0x00000000);
    de_writel(base + 0x0304c, 0x00000000);
    de_writel(base + 0x03050, 0x00000000);
    de_writel(base + 0x03054, 0x00000000);
    de_writel(base + 0x03058, 0x00000000);
    de_writel(base + 0x0305c, 0x00000000);
    de_writel(base + 0x03060, 0x00000000);
    de_writel(base + 0x03064, 0x00000000);
    de_writel(base + 0x03068, 0x00000000);
    de_writel(base + 0x0306c, 0x00000000);
    de_writel(base + 0x03070, 0x00000000);
    de_writel(base + 0x03074, 0x00000000);
    de_writel(base + 0x03078, 0x00000000);
    de_writel(base + 0x0307c, 0x00000000);
    de_writel(base + 0x03080, 0x00000000);
    de_writel(base + 0x03084, 0x00000000);
    de_writel(base + 0x03088, 0x00000000);
    if (!sel) {
        de_writel(base + 0x04000, 0x00000000);
        de_writel(base + 0x04004, 0x00000000);
        de_writel(base + 0x04008, 0x00000000);
        de_writel(base + 0x0400c, 0x00000000);
        de_writel(base + 0x04010, 0x00000000);
        de_writel(base + 0x04014, 0x00000000);
        de_writel(base + 0x04018, 0x00000000);
        de_writel(base + 0x0401c, 0x00000000);
        de_writel(base + 0x04020, 0x00000000);
        de_writel(base + 0x04024, 0x00000000);
        de_writel(base + 0x04028, 0x00000000);
        de_writel(base + 0x0402c, 0x00000000);
        de_writel(base + 0x04030, 0x00000000);
        de_writel(base + 0x04034, 0x00000000);
        de_writel(base + 0x04038, 0x00000000);
        de_writel(base + 0x0403c, 0x00000000);
        de_writel(base + 0x04040, 0x00000000);
        de_writel(base + 0x04044, 0x00000000);
        de_writel(base + 0x04048, 0x00000000);
        de_writel(base + 0x0404c, 0x00000000);
        de_writel(base + 0x04050, 0x00000000);
        de_writel(base + 0x04054, 0x00000000);
        de_writel(base + 0x04058, 0x00000000);
        de_writel(base + 0x0405c, 0x00000000);
        de_writel(base + 0x04060, 0x00000000);
        de_writel(base + 0x04064, 0x00000000);
        de_writel(base + 0x04068, 0x00000000);
        de_writel(base + 0x0406c, 0x00000000);
        de_writel(base + 0x04070, 0x00000000);
        de_writel(base + 0x04074, 0x00000000);
        de_writel(base + 0x04078, 0x00000000);
        de_writel(base + 0x0407c, 0x00000000);
        de_writel(base + 0x04080, 0x00000000);
        de_writel(base + 0x04084, 0x00000000);
        de_writel(base + 0x04088, 0x00000000);
        de_writel(base + 0x05000, 0x00000000);
        de_writel(base + 0x05004, 0x00000000);
        de_writel(base + 0x05008, 0x00000000);
        de_writel(base + 0x0500c, 0x00000000);
        de_writel(base + 0x05010, 0x00000000);
        de_writel(base + 0x05014, 0x00000000);
        de_writel(base + 0x05018, 0x00000000);
        de_writel(base + 0x0501c, 0x00000000);
        de_writel(base + 0x05020, 0x00000000);
        de_writel(base + 0x05024, 0x00000000);
        de_writel(base + 0x05028, 0x00000000);
        de_writel(base + 0x0502c, 0x00000000);
        de_writel(base + 0x05030, 0x00000000);
        de_writel(base + 0x05034, 0x00000000);
        de_writel(base + 0x05038, 0x00000000);
        de_writel(base + 0x0503c, 0x00000000);
        de_writel(base + 0x05040, 0x00000000);
        de_writel(base + 0x05044, 0x00000000);
        de_writel(base + 0x05048, 0x00000000);
        de_writel(base + 0x0504c, 0x00000000);
        de_writel(base + 0x05050, 0x00000000);
        de_writel(base + 0x05054, 0x00000000);
        de_writel(base + 0x05058, 0x00000000);
        de_writel(base + 0x0505c, 0x00000000);
        de_writel(base + 0x05060, 0x00000000);
        de_writel(base + 0x05064, 0x00000000);
        de_writel(base + 0x05068, 0x00000000);
        de_writel(base + 0x0506c, 0x00000000);
        de_writel(base + 0x05070, 0x00000000);
        de_writel(base + 0x05074, 0x00000000);
        de_writel(base + 0x05078, 0x00000000);
        de_writel(base + 0x0507c, 0x00000000);
        de_writel(base + 0x05080, 0x00000000);
        de_writel(base + 0x05084, 0x00000000);
        de_writel(base + 0x05088, 0x00000000);
    }
    de_writel(base + 0x00004, 0x00000000);
    de_writel(base + 0x00008, 0x00000001);
    de_writel(base + 0x0000c, ((outh-1)<<16)|(outw-1));
    de_writel(base + 0x00000, 0x00000001);

    /* [SCALERVIDEO_0] */
    if (w != outw || h != outh || fmt > 0x40) {
        de_writel(base + 0x2000c, 0x00000000);
        de_writel(base + 0x20040, ((outh-1)<<16)|(outw-1));
        de_writel(base + 0x20080, ((h-1)<<16)|(w-1));
        de_writel(base + 0x20088, yhstep);
        de_writel(base + 0x2008c, yvstep);
        de_writel(base + 0x20090, 0x00000000);
        de_writel(base + 0x20098, 0x00000000);
        de_writel(base + 0x2009c, 0x00000000);
        de_writel(base + 0x200c0, ((cinh-1)<<16)|(cinw-1));
        de_writel(base + 0x200c8, chstep);
        de_writel(base + 0x200cc, cvstep);
        de_writel(base + 0x200d0, 0x00000000);
        de_writel(base + 0x200d8, 0x00000000);
        de_writel(base + 0x200dc, 0x00000000);
        de_writel(base + 0x20200, 0x40000000);
        de_writel(base + 0x20204, 0x40fe0000);
        de_writel(base + 0x20208, 0x3ffd0100);
        de_writel(base + 0x2020c, 0x3efc0100);
        de_writel(base + 0x20210, 0x3efb0100);
        de_writel(base + 0x20214, 0x3dfa0200);
        de_writel(base + 0x20218, 0x3cf90200);
        de_writel(base + 0x2021c, 0x3bf80200);
        de_writel(base + 0x20220, 0x39f70200);
        de_writel(base + 0x20224, 0x37f70200);
        de_writel(base + 0x20228, 0x35f70200);
        de_writel(base + 0x2022c, 0x33f70200);
        de_writel(base + 0x20230, 0x31f70200);
        de_writel(base + 0x20234, 0x2ef70200);
        de_writel(base + 0x20238, 0x2cf70200);
        de_writel(base + 0x2023c, 0x2af70200);
        de_writel(base + 0x20240, 0x27f70200);
        de_writel(base + 0x20244, 0x24f80100);
        de_writel(base + 0x20248, 0x22f80100);
        de_writel(base + 0x2024c, 0x1ef90100);
        de_writel(base + 0x20250, 0x1cf90100);
        de_writel(base + 0x20254, 0x19fa0100);
        de_writel(base + 0x20258, 0x17fa0100);
        de_writel(base + 0x2025c, 0x14fb0100);
        de_writel(base + 0x20260, 0x11fc0000);
        de_writel(base + 0x20264, 0x0ffc0000);
        de_writel(base + 0x20268, 0x0cfd0000);
        de_writel(base + 0x2026c, 0x0afd0000);
        de_writel(base + 0x20270, 0x08fe0000);
        de_writel(base + 0x20274, 0x05ff0000);
        de_writel(base + 0x20278, 0x03ff0000);
        de_writel(base + 0x2027c, 0x02000000);
        de_writel(base + 0x20300, 0x00000000);
        de_writel(base + 0x20304, 0x00000002);
        de_writel(base + 0x20308, 0x0000ff04);
        de_writel(base + 0x2030c, 0x0000ff06);
        de_writel(base + 0x20310, 0x0000fe08);
        de_writel(base + 0x20314, 0x0000fd0a);
        de_writel(base + 0x20318, 0x0000fd0c);
        de_writel(base + 0x2031c, 0x0000fc0f);
        de_writel(base + 0x20320, 0x0000fc12);
        de_writel(base + 0x20324, 0x0001fb14);
        de_writel(base + 0x20328, 0x0001fa17);
        de_writel(base + 0x2032c, 0x0001fa19);
        de_writel(base + 0x20330, 0x0001f91c);
        de_writel(base + 0x20334, 0x0001f91f);
        de_writel(base + 0x20338, 0x0001f822);
        de_writel(base + 0x2033c, 0x0001f824);
        de_writel(base + 0x20340, 0x0002f727);
        de_writel(base + 0x20344, 0x0002f72a);
        de_writel(base + 0x20348, 0x0002f72c);
        de_writel(base + 0x2034c, 0x0002f72f);
        de_writel(base + 0x20350, 0x0002f731);
        de_writel(base + 0x20354, 0x0002f733);
        de_writel(base + 0x20358, 0x0002f735);
        de_writel(base + 0x2035c, 0x0002f737);
        de_writel(base + 0x20360, 0x0002f73a);
        de_writel(base + 0x20364, 0x0002f83b);
        de_writel(base + 0x20368, 0x0002f93c);
        de_writel(base + 0x2036c, 0x0002fa3d);
        de_writel(base + 0x20370, 0x0001fb3e);
        de_writel(base + 0x20374, 0x0001fc3f);
        de_writel(base + 0x20378, 0x0001fd40);
        de_writel(base + 0x2037c, 0x0000fe40);
        de_writel(base + 0x20400, 0x00004000);
        de_writel(base + 0x20404, 0x000140ff);
        de_writel(base + 0x20408, 0x00033ffe);
        de_writel(base + 0x2040c, 0x00043ffd);
        de_writel(base + 0x20410, 0x00063efc);
        de_writel(base + 0x20414, 0xff083dfc);
        de_writel(base + 0x20418, 0x000a3bfb);
        de_writel(base + 0x2041c, 0xff0d39fb);
        de_writel(base + 0x20420, 0xff0f37fb);
        de_writel(base + 0x20424, 0xff1136fa);
        de_writel(base + 0x20428, 0xfe1433fb);
        de_writel(base + 0x2042c, 0xfe1631fb);
        de_writel(base + 0x20430, 0xfd192ffb);
        de_writel(base + 0x20434, 0xfd1c2cfb);
        de_writel(base + 0x20438, 0xfd1f29fb);
        de_writel(base + 0x2043c, 0xfc2127fc);
        de_writel(base + 0x20440, 0xfc2424fc);
        de_writel(base + 0x20444, 0xfc2721fc);
        de_writel(base + 0x20448, 0xfb291ffd);
        de_writel(base + 0x2044c, 0xfb2c1cfd);
        de_writel(base + 0x20450, 0xfb2f19fd);
        de_writel(base + 0x20454, 0xfb3116fe);
        de_writel(base + 0x20458, 0xfb3314fe);
        de_writel(base + 0x2045c, 0xfa3611ff);
        de_writel(base + 0x20460, 0xfb370fff);
        de_writel(base + 0x20464, 0xfb390dff);
        de_writel(base + 0x20468, 0xfb3b0a00);
        de_writel(base + 0x2046c, 0xfc3d08ff);
        de_writel(base + 0x20470, 0xfc3e0600);
        de_writel(base + 0x20474, 0xfd3f0400);
        de_writel(base + 0x20478, 0xfe3f0300);
        de_writel(base + 0x2047c, 0xff400100);
        de_writel(base + 0x20600, 0x40000000);
        de_writel(base + 0x20604, 0x40fe0000);
        de_writel(base + 0x20608, 0x3ffd0100);
        de_writel(base + 0x2060c, 0x3efc0100);
        de_writel(base + 0x20610, 0x3efb0100);
        de_writel(base + 0x20614, 0x3dfa0200);
        de_writel(base + 0x20618, 0x3cf90200);
        de_writel(base + 0x2061c, 0x3bf80200);
        de_writel(base + 0x20620, 0x39f70200);
        de_writel(base + 0x20624, 0x37f70200);
        de_writel(base + 0x20628, 0x35f70200);
        de_writel(base + 0x2062c, 0x33f70200);
        de_writel(base + 0x20630, 0x31f70200);
        de_writel(base + 0x20634, 0x2ef70200);
        de_writel(base + 0x20638, 0x2cf70200);
        de_writel(base + 0x2063c, 0x2af70200);
        de_writel(base + 0x20640, 0x27f70200);
        de_writel(base + 0x20644, 0x24f80100);
        de_writel(base + 0x20648, 0x22f80100);
        de_writel(base + 0x2064c, 0x1ef90100);
        de_writel(base + 0x20650, 0x1cf90100);
        de_writel(base + 0x20654, 0x19fa0100);
        de_writel(base + 0x20658, 0x17fa0100);
        de_writel(base + 0x2065c, 0x14fb0100);
        de_writel(base + 0x20660, 0x11fc0000);
        de_writel(base + 0x20664, 0x0ffc0000);
        de_writel(base + 0x20668, 0x0cfd0000);
        de_writel(base + 0x2066c, 0x0afd0000);
        de_writel(base + 0x20670, 0x08fe0000);
        de_writel(base + 0x20674, 0x05ff0000);
        de_writel(base + 0x20678, 0x03ff0000);
        de_writel(base + 0x2067c, 0x02000000);
        de_writel(base + 0x20700, 0x00000000);
        de_writel(base + 0x20704, 0x00000002);
        de_writel(base + 0x20708, 0x0000ff04);
        de_writel(base + 0x2070c, 0x0000ff06);
        de_writel(base + 0x20710, 0x0000fe08);
        de_writel(base + 0x20714, 0x0000fd0a);
        de_writel(base + 0x20718, 0x0000fd0c);
        de_writel(base + 0x2071c, 0x0000fc0f);
        de_writel(base + 0x20720, 0x0000fc12);
        de_writel(base + 0x20724, 0x0001fb14);
        de_writel(base + 0x20728, 0x0001fa17);
        de_writel(base + 0x2072c, 0x0001fa19);
        de_writel(base + 0x20730, 0x0001f91c);
        de_writel(base + 0x20734, 0x0001f91f);
        de_writel(base + 0x20738, 0x0001f822);
        de_writel(base + 0x2073c, 0x0001f824);
        de_writel(base + 0x20740, 0x0002f727);
        de_writel(base + 0x20744, 0x0002f72a);
        de_writel(base + 0x20748, 0x0002f72c);
        de_writel(base + 0x2074c, 0x0002f72f);
        de_writel(base + 0x20750, 0x0002f731);
        de_writel(base + 0x20754, 0x0002f733);
        de_writel(base + 0x20758, 0x0002f735);
        de_writel(base + 0x2075c, 0x0002f737);
        de_writel(base + 0x20760, 0x0002f73a);
        de_writel(base + 0x20764, 0x0002f83b);
        de_writel(base + 0x20768, 0x0002f93c);
        de_writel(base + 0x2076c, 0x0002fa3d);
        de_writel(base + 0x20770, 0x0001fb3e);
        de_writel(base + 0x20774, 0x0001fc3f);
        de_writel(base + 0x20778, 0x0001fd40);
        de_writel(base + 0x2077c, 0x0000fe40);
        de_writel(base + 0x20800, 0x00004000);
        de_writel(base + 0x20804, 0x000140ff);
        de_writel(base + 0x20808, 0x00033ffe);
        de_writel(base + 0x2080c, 0x00043ffd);
        de_writel(base + 0x20810, 0x00063efc);
        de_writel(base + 0x20814, 0xff083dfc);
        de_writel(base + 0x20818, 0x000a3bfb);
        de_writel(base + 0x2081c, 0xff0d39fb);
        de_writel(base + 0x20820, 0xff0f37fb);
        de_writel(base + 0x20824, 0xff1136fa);
        de_writel(base + 0x20828, 0xfe1433fb);
        de_writel(base + 0x2082c, 0xfe1631fb);
        de_writel(base + 0x20830, 0xfd192ffb);
        de_writel(base + 0x20834, 0xfd1c2cfb);
        de_writel(base + 0x20838, 0xfd1f29fb);
        de_writel(base + 0x2083c, 0xfc2127fc);
        de_writel(base + 0x20840, 0xfc2424fc);
        de_writel(base + 0x20844, 0xfc2721fc);
        de_writel(base + 0x20848, 0xfb291ffd);
        de_writel(base + 0x2084c, 0xfb2c1cfd);
        de_writel(base + 0x20850, 0xfb2f19fd);
        de_writel(base + 0x20854, 0xfb3116fe);
        de_writel(base + 0x20858, 0xfb3314fe);
        de_writel(base + 0x2085c, 0xfa3611ff);
        de_writel(base + 0x20860, 0xfb370fff);
        de_writel(base + 0x20864, 0xfb390dff);
        de_writel(base + 0x20868, 0xfb3b0a00);
        de_writel(base + 0x2086c, 0xfc3d08ff);
        de_writel(base + 0x20870, 0xfc3e0600);
        de_writel(base + 0x20874, 0xfd3f0400);
        de_writel(base + 0x20878, 0xfe3f0300);
        de_writel(base + 0x2087c, 0xff400100);
        de_writel(base + 0x20000, 0x00000011);
    }

    de_writel(base + 0x00008, 0x00000001);
}

void rt_mixer_set_addr(int sel, unsigned int addr0)
{
    unsigned int base;

    base = sel?(de_base + RTMX1_BASE):(de_base + RTMX0_BASE);
    de_writel(base + 0x02018, addr0);
}
#endif
