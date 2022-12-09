/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

/* ************************************************************************* */
/* File name   :    rtmx_eink.h */
/*  */
/* Description :    display engine 2.0 realtime mixer processing */
/*          base functions implement */
/*  */
/* History     :    2015/06/28  iptang  v0.1  Initial version */
/*  */
/* ************************************************************************* */

#ifndef __RTMX_EE_H__
#define __RTMX_EE_H__

#if 0
enum de_color_space {
    DE_BT601  = 0,
    DE_BT709  = 1,
    DE_YCC    = 2,
    DE_ENHANCE = 3,
    /* DE_VXYCC  = 3, */
};

enum de_pixel_format {
    DE_FORMAT_ARGB_8888                    = 0x00,/* MSB  A-R-G-B  LSB */
    DE_FORMAT_ABGR_8888                    = 0x01,
    DE_FORMAT_RGBA_8888                    = 0x02,
    DE_FORMAT_BGRA_8888                    = 0x03,
    DE_FORMAT_XRGB_8888                    = 0x04,
    DE_FORMAT_XBGR_8888                    = 0x05,
    DE_FORMAT_RGBX_8888                    = 0x06,
    DE_FORMAT_BGRX_8888                    = 0x07,
    DE_FORMAT_RGB_888                      = 0x08,
    DE_FORMAT_BGR_888                      = 0x09,
    DE_FORMAT_RGB_565                      = 0x0a,
    DE_FORMAT_BGR_565                      = 0x0b,
    DE_FORMAT_ARGB_4444                    = 0x0c,
    DE_FORMAT_ABGR_4444                    = 0x0d,
    DE_FORMAT_RGBA_4444                    = 0x0e,
    DE_FORMAT_BGRA_4444                    = 0x0f,
    DE_FORMAT_ARGB_1555                    = 0x10,
    DE_FORMAT_ABGR_1555                    = 0x11,
    DE_FORMAT_RGBA_5551                    = 0x12,
    DE_FORMAT_BGRA_5551                    = 0x13,

    /* SP: semi-planar, P:planar, I:interleaved
     * UVUV: U in the LSBs;     VUVU: V in the LSBs
     */
    DE_FORMAT_YUV444_I_AYUV         = 0x40,/* MSB  A-Y-U-V  LSB, reserved */
    DE_FORMAT_YUV444_I_VUYA                = 0x41,/* MSB  V-U-Y-A  LSB */
    DE_FORMAT_YUV422_I_YVYU                = 0x42,/* MSB  Y-V-Y-U  LSB */
    DE_FORMAT_YUV422_I_YUYV                = 0x43,/* MSB  Y-U-Y-V  LSB */
    DE_FORMAT_YUV422_I_UYVY                = 0x44,/* MSB  U-Y-V-Y  LSB */
    DE_FORMAT_YUV422_I_VYUY                = 0x45,/* MSB  V-Y-U-Y  LSB */
    DE_FORMAT_YUV444_P                     = 0x46,
            /* MSB  P3-2-1-0 LSB,  YYYY UUUU VVVV, reserved */
    DE_FORMAT_YUV422_P                     = 0x47,
            /* MSB  P3-2-1-0 LSB   YYYY UU   VV */
    DE_FORMAT_YUV420_P                     = 0x48,
            /* MSB  P3-2-1-0 LSB   YYYY U    V */
    DE_FORMAT_YUV411_P                     = 0x49,
            /* MSB  P3-2-1-0 LSB   YYYY U    V */
    DE_FORMAT_YUV422_SP_UVUV               = 0x4a,/* MSB  V-U-V-U  LSB */
    DE_FORMAT_YUV422_SP_VUVU               = 0x4b,/* MSB  U-V-U-V  LSB */
    DE_FORMAT_YUV420_SP_UVUV               = 0x4c,
    DE_FORMAT_YUV420_SP_VUVU               = 0x4d,
    DE_FORMAT_YUV411_SP_UVUV               = 0x4e,
    DE_FORMAT_YUV411_SP_VUVU               = 0x4f,
};

struct de_fb {
    unsigned int w;
    unsigned int h;
};

struct de_rect {
    int x;
    int y;
    unsigned int w;
    unsigned int h;
};

struct de_rect64 {
    long long x;
    long long y;
    unsigned long long w;
    unsigned long long h;
};
#endif

int rtmx_set_base(unsigned int reg_base);
void rt_mixer_init(int sel, unsigned int addr0, unsigned int addr1,
        unsigned int addr2, unsigned int w, unsigned int h,
        unsigned int outw, unsigned int outh, unsigned int fmt);
void rt_mixer_set_addr(int sel, unsigned int addr0);

#endif
