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
 *All Winner Tech, All Right Reserved. 2014-2015 Copyright (c)
 *
 *File name   :de_rtmx.h
 *
 *Description :display engine 2.0 realtime
 *              mixer processing base functions implement
 *History     :2014/02/08  iptang  v0.1  Initial version
 *
 */

#ifndef __DE_RTMX_H__
#define __DE_RTMX_H__

#include "de_feat.h"
#include "../include.h"

#define max2(s, t) (((s) >= (t)) ? (s) : (t))
#define min2(s, t) (((s) <= (t)) ? (s) : (t))
#define N2_POWER(a, power)  (((unsigned long long)a)<<power)

enum de_color_space {
    DE_BT601 = 0,
    DE_BT709 = 1,
    DE_YCC = 2,
    DE_ENHANCE = 3,
    /* DE_VXYCC  = 3, */
};

enum de_pixel_format {
    DE_FORMAT_ARGB_8888 = 0x00,
        /*MSB  A-R-G-B  LSB */
    DE_FORMAT_ABGR_8888 = 0x01,
    DE_FORMAT_RGBA_8888 = 0x02,
    DE_FORMAT_BGRA_8888 = 0x03,
    DE_FORMAT_XRGB_8888 = 0x04,
    DE_FORMAT_XBGR_8888 = 0x05,
    DE_FORMAT_RGBX_8888 = 0x06,
    DE_FORMAT_BGRX_8888 = 0x07,
    DE_FORMAT_RGB_888 = 0x08,
    DE_FORMAT_BGR_888 = 0x09,
    DE_FORMAT_RGB_565 = 0x0a,
    DE_FORMAT_BGR_565 = 0x0b,
    DE_FORMAT_ARGB_4444 = 0x0c,
    DE_FORMAT_ABGR_4444 = 0x0d,
    DE_FORMAT_RGBA_4444 = 0x0e,
    DE_FORMAT_BGRA_4444 = 0x0f,
    DE_FORMAT_ARGB_1555 = 0x10,
    DE_FORMAT_ABGR_1555 = 0x11,
    DE_FORMAT_RGBA_5551 = 0x12,
    DE_FORMAT_BGRA_5551 = 0x13,
    DE_FORMAT_A2R10G10B10 = 0x14,
    DE_FORMAT_A2B10G10R10 = 0x15,
    DE_FORMAT_R10G10B10A2 = 0x16,
    DE_FORMAT_B10G10R10A2 = 0x17,
    DE_FORMAT_1bpp_palette_LE = 0x18,
    DE_FORMAT_2bpp_palette_LE = 0x19,
    DE_FORMAT_4bpp_palette_LE = 0x1a,
    DE_FORMAT_8bpp_palette_LE = 0x1b,
    /* SP: semi-planar, P:planar, I:interleaved
     * UVUV: U in the LSBs;     VUVU: V in the LSBs
     */
    DE_FORMAT_YUV444_I_AYUV = 0x40,
    /* MSB  A-Y-U-V  LSB, reserved */
    DE_FORMAT_YUV444_I_VUYA = 0x41,
    /* MSB  V-U-Y-A  LSB */
    DE_FORMAT_YUV422_I_YVYU = 0x42,
    /* MSB  Y-V-Y-U  LSB */
    DE_FORMAT_YUV422_I_YUYV = 0x43,
    /* MSB  Y-U-Y-V  LSB */
    DE_FORMAT_YUV422_I_UYVY = 0x44,
    /* MSB  U-Y-V-Y  LSB */
    DE_FORMAT_YUV422_I_VYUY = 0x45,
    /* MSB  V-Y-U-Y  LSB */
    DE_FORMAT_YUV444_P = 0x46,
    /* MSB  P3-2-1-0 LSB,  YYYY UUUU VVVV, reserved */
    DE_FORMAT_YUV422_P = 0x47,
    /* MSB  P3-2-1-0 LSB   YYYY UU   VV */
    DE_FORMAT_YUV420_P = 0x48,
    /* MSB  P3-2-1-0 LSB   YYYY U    V */
    DE_FORMAT_YUV411_P = 0x49,
    /* MSB  P3-2-1-0 LSB   YYYY U    V */
    DE_FORMAT_YUV422_SP_UVUV = 0x4a,
    /* MSB  V-U-V-U  LSB */
    DE_FORMAT_YUV422_SP_VUVU = 0x4b,
    /* MSB  U-V-U-V  LSB */
    DE_FORMAT_YUV420_SP_UVUV = 0x4c,
    DE_FORMAT_YUV420_SP_VUVU = 0x4d,
    DE_FORMAT_YUV411_SP_UVUV = 0x4e,
    DE_FORMAT_YUV411_SP_VUVU = 0x4f,
};

enum de_3d_in_mode {
    DE_3D_SRC_NORMAL = 0x0,
    /* not 3d mode */
    DE_3D_SRC_MODE_TB = 0x1 << 0,
    /* top bottom */
    DE_3D_SRC_MODE_FP = 0x1 << 1,
    /* frame packing */
    DE_3D_SRC_MODE_SSF = 0x1 << 2,
    /* side by side full */
    DE_3D_SRC_MODE_SSH = 0x1 << 3,
    /* side by side half */
    DE_3D_SRC_MODE_LI = 0x1 << 4,
    /* line interleaved */
};

enum de_3d_out_mode {
    DE_3D_OUT_MODE_CI_1 = 0x5,
    /* column interleaved 1 */
    DE_3D_OUT_MODE_CI_2 = 0x6,
    /* column interleaved 2 */
    DE_3D_OUT_MODE_CI_3 = 0x7,
    /* column interleaved 3 */
    DE_3D_OUT_MODE_CI_4 = 0x8,
    /* column interleaved 4 */
    DE_3D_OUT_MODE_LIRGB = 0x9,
    /* line interleaved rgb */

    DE_3D_OUT_MODE_TB = 0x0,
    /* top bottom */
    DE_3D_OUT_MODE_FP = 0x1,
    /* frame packing */
    DE_3D_OUT_MODE_SSF = 0x2,
    /* side by side full */
    DE_3D_OUT_MODE_SSH = 0x3,
    /* side by side half */
    DE_3D_OUT_MODE_LI = 0x4,
    /* line interleaved */
    DE_3D_OUT_MODE_FA = 0xa,
    /* field alternative */
};

enum de_dirty_flags {
    DE_LAYER_ATTR_DIRTY = 0x00000001,
    DE_LAYER_VI_FC_DIRTY = 0x00000002,
    DE_LAYER_HADDR_DIRTY = 0x00000004,
    DE_LAYER_SIZE_DIRTY = 0x00000008,
    DE_BLEND_ENABLE_DIRTY = 0x00000010,
    DE_BLEND_ATTR_DIRTY = 0x00000020,
    DE_BLEND_CTL_DIRTY = 0x00000040,
    DE_BLEND_OUT_DIRTY = 0x00000080,
    DE_LAYER_ALL_DIRTY = 0x000000ff,

};

enum de_bld_mode {
    /*
     * pixel color = sc * sa * cfs + dc * da * cfd
     * pixel alpha = sa * afs + da * afd
     * sc = source color
     * sa = source alpha
     * dc = destination color
     * da = destination alpha
     * cfs = source color factor for blend function
     * cfd = destination color factor for blend function
     * afs = source alpha factor for blend function
     * afd = destination alpha factor for blend function
     */
    DE_BLD_CLEAR = 0x00,
    /* cfs/afs:    0     cfd/afd:    0    */
    DE_BLD_SRC = 0x01,
    /* cfs/afs:    1     cfd/afd:    0    */
    DE_BLD_DST = 0x02,
    /* cfs/afs:    0     cfd/afd:    1    */
    DE_BLD_SRCOVER = 0x03,
    /* cfs/afs:    1     cfd/afd:    1-sa */
    DE_BLD_DSTOVER = 0x04,
    /* cfs/afs:    1-da  cfd/afd:    1    */
    DE_BLD_SRCIN = 0x05,
    /* cfs/afs:    da    cfd/afd:    0    */
    DE_BLD_DSTIN = 0x06,
    /* cfs/afs:    0     cfd/afd:    sa   */
    DE_BLD_SRCOUT = 0x07,
    /* cfs/afs:    1-da  cfd/afd:    0    */
    DE_BLD_DSTOUT = 0x08,
    /* cfs/afs:    0     cfd/afd:    1-sa */
    DE_BLD_SRCATOP = 0x09,
    /* cfs/afs:    da    cfd/afd:    1-sa */
    DE_BLD_DSTATOP = 0x0a,
    /* cfs/afs:    1-da  cfd/afd:    sa   */
    DE_BLD_XOR = 0x0b,
    /* cfs/afs:    1-da  cfd/afd:    1-sa */
};

enum de_ck_mode {
    DE_CK_SRC = 0x0,
    /* the pixel value match source image,
     * it displays the destination image pixel
     */
    DE_CK_DST = 0x1,
    /* the pixel value match destination image,
     * it displays the source image pixel
     */
};

enum de_coarsescale_sts {
    DE_NO_CS = 0x0,
    /* no coarse scale in both direction */
    DE_CS_HORZ = 0x1,
    /* coarse scale only in horizon */
    DE_CS_VERT = 0x2,
    /* coarse scale only in vertical */
    DE_CS_BOTHDIR = 0x3
    /* coarse scale in both direction */
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

struct de_reg_blocks {
    void *val;
    /* address from memory */
    uintptr_t off;
    /* register offset */
    unsigned int size;
    /* unit:byte */
    unsigned char dirty;
};

struct __lay_para_t {
    bool en;
    bool fcolor_en;
    bool top_bot_en;
    unsigned char fmt;
    unsigned char alpha_mode;
    unsigned char premul_ctl;
    unsigned char alpha;

    unsigned char haddr_t[3];
    unsigned char haddr_b[3];
    unsigned int pitch[3];
    struct de_rect layer;
    unsigned int laddr_t[3];
    unsigned int laddr_b[3];
    struct de_rect lbc_crop;
    unsigned int lbc_laddr;
    unsigned int lbc_haddr;
    unsigned int lbc_en;
    struct disp_lbc_info lbc_info;
};

struct __bld_ch_para_t {
    unsigned char fcolor_en;
    unsigned char pipe_en;
    unsigned char route;
    unsigned char alpha_mode;
    unsigned int fcolor;
    unsigned int inwidth;
    unsigned int inheight;
    unsigned int offsetx;
    unsigned int offsety;
};

struct __bld_para_t {
    unsigned char pixel_fs[4];
    unsigned char pixel_fd[4];
    unsigned char alpha_fs[4];
    unsigned char alpha_fd[4];

    unsigned char ck_en[4];
    unsigned char ck_dir[4];
    unsigned char ck_con[4];
    unsigned int ck_max[4];
    unsigned int ck_min[4];
    unsigned int bkcolor;
    unsigned int outwidth;
    unsigned int outheight;
    unsigned int out_ctl;
    struct __bld_ch_para_t ch_attr[5];
};

/* DATA typedef structURE */
struct scaler_para {
    int hphase;
    /* initial phase of vsu/gsu in horizon */
    int vphase;
    /* initial phase of vsu/gsu in vertical */
    unsigned int hstep;
    /* scale step of vsu/gsu in horizon */
    unsigned int vstep;
    /* scale step of vsu/gsu in vertical */
};

int de_rtmx_init(unsigned int sel, uintptr_t reg_base);
int de_rtmx_exit(unsigned int sel);
int de_rtmx_update_regs(unsigned int sel);
int de_rtmx_set_gld_reg_base(unsigned int sel, void *base);
int de_rtmx_set_bld_reg_base(unsigned int sel, void *base);
int de_rtmx_set_overlay_reg_base(unsigned int sel, unsigned int chno,
                 void *base);
int de_rtmx_set_lay_cfg(unsigned int sel, unsigned int chno, unsigned int layno,
            struct __lay_para_t *cfg);
int de_rtmx_set_lay_haddr(unsigned int sel, unsigned int chno,
              unsigned int layno, unsigned char top_bot_en,
              unsigned char *haddr_t, unsigned char *haddr_b, unsigned int lbc_en);
int de_rtmx_set_lay_laddr(unsigned int sel, unsigned int chno,
          unsigned int layno, unsigned char fmt, struct de_rect crop,
          unsigned int *size, unsigned int *align,
          enum de_3d_in_mode trdinmode, unsigned int *addr,
              unsigned char *haddr, unsigned int lbc_en);
int de_rtmx_get_3d_in(unsigned char fmt, struct de_rect crop,
            struct de_fb *size,
          unsigned int *align, enum de_3d_in_mode trdinmode,
          unsigned int *addr, unsigned int *trd_addr,
          unsigned int *pitch, unsigned int *pitchr,
          unsigned int *lay_laddr);
int de_rtmx_get_3d_in_single_size(enum de_3d_in_mode inmode,
    struct de_rect64 *size);
int de_rtmx_get_3d_out(struct de_rect frame0, unsigned int scn_w,
    unsigned int scn_h, enum de_3d_out_mode trdoutmode,
    struct de_rect *frame1);
int de_rtmx_get_li_addr_offset(unsigned int size, unsigned int align,
            unsigned int x, unsigned int y,
            unsigned int cnt);
int de_rtmx_set_lay_fcolor(unsigned int sel, unsigned int chno,
               unsigned int layno, unsigned char en,
               unsigned char fmt, unsigned int color, unsigned int lbc_en);
int de_rtmx_set_overlay_size(unsigned int sel, unsigned int chno,
                 unsigned int w, unsigned int h, unsigned int lbc_en);
int de_rtmx_set_coarse_fac(unsigned int sel, unsigned char chno,
               unsigned int fmt, unsigned int lcd_fps,
               unsigned int lcd_height, unsigned int de_freq_mhz,
               unsigned int ovl_w, unsigned int ovl_h,
               unsigned int vsu_outw, unsigned int vsu_outh,
               unsigned int *midyw, unsigned int *midyh,
               unsigned int *midcw, unsigned int *midch);
int de_rtmx_set_pf_en(unsigned int sel, unsigned char *pen);
int de_rtmx_set_pipe_cfg(unsigned int sel, unsigned char pno,
             unsigned int color, struct de_rect bldrc);
int de_rtmx_set_route(unsigned int sel, unsigned char pno, unsigned int zoder);
int de_rtmx_set_premul(unsigned int sel, unsigned char pno,
               unsigned int pre_mul);
int de_rtmx_set_background_color(unsigned int sel, unsigned int color);
int de_rtmx_set_blend_size(unsigned int sel, unsigned int w, unsigned int h);
int de_rtmx_set_blend_mode(unsigned int sel, unsigned int bldno,
               unsigned char mode);
int de_rtmx_set_blend_color(unsigned int sel, unsigned int bldno,
                unsigned int color);
int de_rtmx_set_outitl(unsigned int sel, unsigned char interlace_en);
int de_rtmx_set_colorkey(unsigned int sel, unsigned char ck_no,
             unsigned char ck_mode, unsigned char ck_red_match,
             unsigned char ck_green_match,
             unsigned char ck_blue_match, unsigned int ck_max,
             unsigned int ck_min);
int de_rtmx_calc_chnrect(unsigned char *lay_en, int laynum,
    struct de_rect *frame, struct de_rect *crop, int gsu_sel,
     struct scaler_para *step, struct de_rect *layer,
     struct de_rect *bld_rect, unsigned int *ovlw, unsigned int *ovlh);
int de_rtmx_trimcoord(struct de_rect *frame, struct de_rect *crop,
        unsigned int outw, unsigned int outh, int xratio, int yratio);
int de_rtmx_get_premul_ctl(int laynum, unsigned char *premul);
struct de_rect de_rtmx_extend_rect(struct de_rect rc1, struct de_rect rc2);
int de_rtmx_set_dbuff_rdy(unsigned int sel);
int de_rtmx_set_enable(unsigned int sel, unsigned int en);
int de_rtmx_set_display_size(unsigned int sel, unsigned int width,
                 unsigned int height);
int de_rtmx_query_irq(unsigned int sel);
int de_rtmx_enable_irq(unsigned int sel, unsigned int en);

int de_rtmx_mux(unsigned int sel, unsigned int tcon_index);
int de_rtmx_get_mux(unsigned int sel);
int de_rtmx_sync_hw(unsigned int sel);
int de_rtmx_get_lay_enabled(unsigned int sel, unsigned int chno,
                unsigned int layno);
int de_rtmx_get_lay_address(unsigned int sel, unsigned int chno,
                unsigned int layno, unsigned long long *addr);
int de_rtmx_get_lay_size(unsigned int sel, unsigned int chno,
             unsigned int layno, struct disp_rectsz *size);
int de_rtmx_get_lay_win(unsigned int sel, unsigned int chno, unsigned int layno,
            struct disp_rect *win);
int de_rtmx_get_lay_format(unsigned int sel, unsigned int chno,
               unsigned int layno);
int de_rtmx_get_display_size(unsigned int sel, unsigned int *width,
                 unsigned int *height);
int de_rtmx_set_palette(unsigned int sel, unsigned int chno,
            void *data, unsigned int num);
int de_rtmx_set_dither_out(unsigned int sel, unsigned int en, unsigned int fifo_3d,
            unsigned int mode, unsigned int fmt);
#endif
