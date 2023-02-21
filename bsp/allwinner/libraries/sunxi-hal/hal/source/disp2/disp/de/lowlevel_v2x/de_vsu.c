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
 *  File name   :       de_gsu.c
 *
 *  Description :       display engine 2.0 vsu basic function definition
 *
 *  History     :       2014/03/20  vito cheng  v0.1  Initial version
 *
 */
#include "de_vsu_type.h"
#include "de_scaler.h"
#include "de_scaler_table.h"

static volatile struct __vsu_reg_t *vsu_dev[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks vsu_glb_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks vsu_out_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks vsu_yscale_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks vsu_cscale_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks vsu_yhcoeff0_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks vsu_yhcoeff1_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks vsu_yvcoeff_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks vsu_chcoeff0_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks vsu_chcoeff1_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks vsu_cvcoeff_block[DE_NUM][VI_CHN_NUM];

int de_vsu_update_regs(unsigned int sel)
{
    int i, chno;

    chno = de_feat_get_num_vi_chns(sel);

    for (i = 0; i < chno; i++) {
        if (vsu_glb_block[sel][i].dirty == 0x1) {
            regwrite((void *)vsu_glb_block[sel][i].off,
                vsu_glb_block[sel][i].val,
                vsu_glb_block[sel][i].size);
            vsu_glb_block[sel][i].dirty = 0x0;
        }
        if (vsu_out_block[sel][i].dirty == 0x1) {
            regwrite((void *)vsu_out_block[sel][i].off,
                vsu_out_block[sel][i].val,
                vsu_out_block[sel][i].size);
            vsu_out_block[sel][i].dirty = 0x0;
        }
        if (vsu_yscale_block[sel][i].dirty == 0x1) {
            regwrite((void *)vsu_yscale_block[sel][i].off,
                vsu_yscale_block[sel][i].val,
                vsu_yscale_block[sel][i].size);
            vsu_yscale_block[sel][i].dirty = 0x0;
        }
        if (vsu_cscale_block[sel][i].dirty == 0x1) {
            regwrite((void *)vsu_cscale_block[sel][i].off,
                vsu_cscale_block[sel][i].val,
                vsu_cscale_block[sel][i].size);
            vsu_cscale_block[sel][i].dirty = 0x0;
        }
        if (vsu_yhcoeff0_block[sel][i].dirty == 0x1) {
            regwrite((void *)vsu_yhcoeff0_block[sel][i].off,
                vsu_yhcoeff0_block[sel][i].val,
                vsu_yhcoeff0_block[sel][i].size);
            regwrite((void *)vsu_yhcoeff1_block[sel][i].off,
                vsu_yhcoeff1_block[sel][i].val,
                vsu_yhcoeff1_block[sel][i].size);
            regwrite((void *)vsu_yvcoeff_block[sel][i].off,
                vsu_yvcoeff_block[sel][i].val,
                vsu_yvcoeff_block[sel][i].size);
            regwrite((void *)vsu_chcoeff0_block[sel][i].off,
                vsu_chcoeff0_block[sel][i].val,
                vsu_chcoeff0_block[sel][i].size);
            regwrite((void *)vsu_chcoeff1_block[sel][i].off,
                vsu_chcoeff1_block[sel][i].val,
                vsu_chcoeff1_block[sel][i].size);
            regwrite((void *)vsu_cvcoeff_block[sel][i].off,
                vsu_cvcoeff_block[sel][i].val,
                vsu_cvcoeff_block[sel][i].size);
            vsu_yhcoeff0_block[sel][i].dirty = 0x0;
        }
    }

    return 0;
}

int de_vsu_init(unsigned int sel, uintptr_t reg_base)
{
    int j, chno;
    uintptr_t vsu_base;
    void *memory;

    chno = de_feat_get_num_vi_chns(sel);

    for (j = 0; j < chno; j++) {
        vsu_base = reg_base + (sel + 1) * 0x00100000 + VSU_OFST
                + j * 0x20000;
#if defined(CONFIG_ARCH_SUN50IW10)
        if (sel)
            vsu_base = vsu_base - 0x00100000;
#endif
        memory = disp_sys_malloc(sizeof(struct __vsu_reg_t));
        if (memory == NULL) {
            DE_WRN("disp_sys_malloc vscaler[%d][%d] memory fail! size=0x%x\n",
                sel,
                j,
                (unsigned int)sizeof(struct __vsu_reg_t));
            return -1;
        }

        vsu_glb_block[sel][j].off = vsu_base;
        vsu_glb_block[sel][j].val = memory;
        vsu_glb_block[sel][j].size = 0x10;
        vsu_glb_block[sel][j].dirty = 0;

        vsu_out_block[sel][j].off = vsu_base + 0x40;
        vsu_out_block[sel][j].val = memory + 0x40;
        vsu_out_block[sel][j].size = 0x4;
        vsu_out_block[sel][j].dirty = 0;

        vsu_yscale_block[sel][j].off = vsu_base + 0x80;
        vsu_yscale_block[sel][j].val = memory + 0x80;
        vsu_yscale_block[sel][j].size = 0x20;
        vsu_yscale_block[sel][j].dirty = 0;

        vsu_cscale_block[sel][j].off = vsu_base + 0xc0;
        vsu_cscale_block[sel][j].val = memory + 0xc0;
        vsu_cscale_block[sel][j].size = 0x20;
        vsu_cscale_block[sel][j].dirty = 0;

        vsu_yhcoeff0_block[sel][j].off = vsu_base + 0x200;
        vsu_yhcoeff0_block[sel][j].val = memory + 0x200;
        vsu_yhcoeff0_block[sel][j].size = 0x80;

        vsu_yhcoeff1_block[sel][j].off = vsu_base + 0x300;
        vsu_yhcoeff1_block[sel][j].val = memory + 0x300;
        vsu_yhcoeff1_block[sel][j].size = 0x80;

        vsu_yvcoeff_block[sel][j].off = vsu_base + 0x400;
        vsu_yvcoeff_block[sel][j].val = memory + 0x400;
        vsu_yvcoeff_block[sel][j].size = 0x80;

        vsu_chcoeff0_block[sel][j].off = vsu_base + 0x600;
        vsu_chcoeff0_block[sel][j].val = memory + 0x600;
        vsu_chcoeff0_block[sel][j].size = 0x80;

        vsu_chcoeff1_block[sel][j].off = vsu_base + 0x700;
        vsu_chcoeff1_block[sel][j].val = memory + 0x700;
        vsu_chcoeff1_block[sel][j].size = 0x80;

        vsu_cvcoeff_block[sel][j].off = vsu_base + 0x800;
        vsu_cvcoeff_block[sel][j].val = memory + 0x800;
        vsu_cvcoeff_block[sel][j].size = 0x80;

        /* only use one para to represent all coeff block */
        vsu_yhcoeff0_block[sel][j].dirty = 0;

        de_vsu_set_reg_base(sel, j, memory);
    }

    return 0;
}

int de_vsu_exit(unsigned int sel)
{
    int j, chno;

    chno = de_feat_get_num_vi_chns(sel);

    for (j = 0; j < chno; j++)
        disp_sys_free(vsu_glb_block[sel][j].val);

    return 0;
}
/**
 *  function       : de_vsu_set_reg_base(unsigned int sel,
 *                      unsigned int chno,
 *                      void *base)
 *  description    : set vsu reg base
 *  parameters     :
 *          sel         <rtmx select>
 *          chno        <overlay select>
 *          base        <reg base>
 *  return         :
 *          success
 */
int de_vsu_set_reg_base(unsigned int sel, unsigned int chno, void *base)
{
    DE_INF("sel=%d, chno=%d, base=0x%p\n", sel, chno, base);
    vsu_dev[sel][chno] = (struct __vsu_reg_t *) base;

    return 0;
}

/**
 *  function       : de_vsu_enable(unsigned int sel,
 *                  unsigned int chno, unsigned int en)
 *  description    : enable/disable vsu
 *  parameters     :
 *          sel         <rtmx select>
 *          chno        <overlay select>
 *          en          <enable: 0-disable; 1-enable>
 *  return         :
 *          success
 */
int de_vsu_enable(unsigned int sel, unsigned int chno, unsigned int en)
{
    vsu_dev[sel][chno]->ctrl.bits.en = en;
    vsu_glb_block[sel][chno].dirty = 1;

    return 0;
}

/*
 *  function       : de_vsu_calc_fir_coef(unsigned int step)
 *  description    : set fir coefficients
 *  parameters     :
 *          step       <horizontal scale ratio of vsu>
 *  return         :
 *          offset (in word) of coefficient table
 */
static unsigned int de_vsu_calc_fir_coef(unsigned int step)
{
    unsigned int pt_coef;
    unsigned int scale_ratio, int_part, float_part, fir_coef_ofst;

    scale_ratio = step >> (VSU_PHASE_FRAC_BITWIDTH - 3);
    int_part = scale_ratio >> 3;
    float_part = scale_ratio & 0x7;
    fir_coef_ofst = (int_part == 0) ? VSU_ZOOM0_SIZE :
            (int_part == 1) ? VSU_ZOOM0_SIZE + float_part :
            (int_part == 2) ? VSU_ZOOM0_SIZE + VSU_ZOOM1_SIZE
            + (float_part >> 1) :
            (int_part == 3) ? VSU_ZOOM0_SIZE + VSU_ZOOM1_SIZE
            + VSU_ZOOM2_SIZE :
            (int_part == 4) ? VSU_ZOOM0_SIZE + VSU_ZOOM1_SIZE
            + VSU_ZOOM2_SIZE + VSU_ZOOM3_SIZE :
            VSU_ZOOM0_SIZE + VSU_ZOOM1_SIZE + VSU_ZOOM2_SIZE
            + VSU_ZOOM3_SIZE + VSU_ZOOM4_SIZE;

    pt_coef = fir_coef_ofst * VSU_PHASE_NUM;

    return pt_coef;
}

/**
 *  function       : de_vsu_set_para(unsigned int sel, unsigned int chno,
 *                      unsigned int *coef)
 *  description    : set fir coefficients
 *  parameters     :
 *          sel         <rtmx select>
 *          chno        <overlay select>
 *          *coef       <coefficients pointer>
 *  return         :
 *          success
 */
int de_vsu_set_para(unsigned int sel, unsigned int chno, unsigned int enable,
            unsigned char fmt,
            unsigned int in_w, unsigned int in_h,
            unsigned int out_w, unsigned int out_h,
            struct scaler_para *ypara, struct scaler_para *cpara)
{
    unsigned int pt_coef, in_cw, in_ch, format;

    DE_INF("sel%d, ch %d, en=%d, in<%dx%d>,out<%dx%d>\n", sel, chno, enable,
        in_w, in_h, out_w, out_h);
    vsu_dev[sel][chno]->ctrl.bits.en = enable;
    if (enable == 0) {
        vsu_glb_block[sel][chno].dirty = 1;
        return 0;
    }

    switch (fmt) {
    case DE_FORMAT_YUV422_I_YVYU:
    case DE_FORMAT_YUV422_I_YUYV:
    case DE_FORMAT_YUV422_I_UYVY:
    case DE_FORMAT_YUV422_I_VYUY:
    case DE_FORMAT_YUV422_P:
    case DE_FORMAT_YUV422_SP_UVUV:
    case DE_FORMAT_YUV422_SP_VUVU:
        in_cw = (in_w + 1) >> 1;
        in_ch = in_h;
        format = VSU_FORMAT_YUV422;
        break;
    case DE_FORMAT_YUV420_P:
    case DE_FORMAT_YUV420_SP_UVUV:
    case DE_FORMAT_YUV420_SP_VUVU:
        in_cw = (in_w + 1) >> 1;
        in_ch = (in_h + 1) >> 1;
        format = VSU_FORMAT_YUV420;
        break;
    case DE_FORMAT_YUV411_P:
    case DE_FORMAT_YUV411_SP_UVUV:
    case DE_FORMAT_YUV411_SP_VUVU:
        in_cw = (in_w + 3) >> 2;
        in_ch = in_h;
        format = VSU_FORMAT_YUV411;
        break;
    default:
        in_cw = in_w;
        in_ch = in_h;
        format = VSU_FORMAT_RGB;
        break;
    }

    /* basic parameter */
    vsu_dev[sel][chno]->outsize.dwval = ((out_h - 1) << 16) | (out_w - 1);
    vsu_dev[sel][chno]->ysize.dwval = ((in_h - 1) << 16) | (in_w - 1);
    vsu_dev[sel][chno]->csize.dwval = ((in_ch - 1) << 16) | (in_cw - 1);
    vsu_dev[sel][chno]->yhstep.dwval
        = ypara->hstep << VSU_PHASE_FRAC_REG_SHIFT;
    vsu_dev[sel][chno]->yvstep.dwval
        = ypara->vstep << VSU_PHASE_FRAC_REG_SHIFT;
    vsu_dev[sel][chno]->chstep.dwval
        = cpara->hstep << VSU_PHASE_FRAC_REG_SHIFT;
    vsu_dev[sel][chno]->cvstep.dwval
        = cpara->vstep << VSU_PHASE_FRAC_REG_SHIFT;
    vsu_dev[sel][chno]->yhphase.dwval
        = ypara->hphase << VSU_PHASE_FRAC_REG_SHIFT;
    vsu_dev[sel][chno]->yvphase0.dwval
        = ypara->vphase << VSU_PHASE_FRAC_REG_SHIFT;

    /* modify 14-11-8 */
    vsu_dev[sel][chno]->chphase.dwval
        = cpara->hphase << VSU_PHASE_FRAC_REG_SHIFT;
    vsu_dev[sel][chno]->cvphase0.dwval
        = cpara->vphase << VSU_PHASE_FRAC_REG_SHIFT;

    /* fir coefficient */
    /* ch0 */
    pt_coef = de_vsu_calc_fir_coef(ypara->hstep);
    regwrite(((void *)&vsu_dev[sel][chno]->yhcoeff0),
            lan3coefftab32_left + pt_coef,
            sizeof(unsigned int) * VSU_PHASE_NUM);
    regwrite(((void *)&vsu_dev[sel][chno]->yhcoeff1),
            lan3coefftab32_right + pt_coef,
            sizeof(unsigned int) * VSU_PHASE_NUM);

    pt_coef = de_vsu_calc_fir_coef(ypara->vstep);
    regwrite(((void *)&vsu_dev[sel][chno]->yvcoeff),
            lan2coefftab32 + pt_coef,
            sizeof(unsigned int) * VSU_PHASE_NUM);

    /* ch1/2 */
    if (format == VSU_FORMAT_RGB) {
        pt_coef = de_vsu_calc_fir_coef(cpara->hstep);
        regwrite(((void *)&vsu_dev[sel][chno]->chcoeff0),
            lan3coefftab32_left + pt_coef,
            sizeof(unsigned int) * VSU_PHASE_NUM);
        regwrite(((void *)&vsu_dev[sel][chno]->chcoeff1),
            lan3coefftab32_right + pt_coef,
            sizeof(unsigned int) * VSU_PHASE_NUM);

        pt_coef = de_vsu_calc_fir_coef(cpara->vstep);
        regwrite(((void *)&vsu_dev[sel][chno]->cvcoeff),
            lan2coefftab32 + pt_coef,
            sizeof(unsigned int) * VSU_PHASE_NUM);
    } else {
        pt_coef = de_vsu_calc_fir_coef(cpara->hstep);
        regwrite(((void *)&vsu_dev[sel][chno]->chcoeff0),
            bicubic8coefftab32_left + pt_coef,
            sizeof(unsigned int) * VSU_PHASE_NUM);
        regwrite(((void *)&vsu_dev[sel][chno]->chcoeff1),
            bicubic8coefftab32_right + pt_coef,
            sizeof(unsigned int) * VSU_PHASE_NUM);

        pt_coef = de_vsu_calc_fir_coef(cpara->vstep);
        regwrite(((void *)&vsu_dev[sel][chno]->cvcoeff),
            bicubic4coefftab32 + pt_coef,
            sizeof(unsigned int) * VSU_PHASE_NUM);
    }
    vsu_dev[sel][chno]->ctrl.bits.coef_switch_rdy = 1;
    vsu_glb_block[sel][chno].dirty = 1;
    vsu_out_block[sel][chno].dirty = 1;
    vsu_yscale_block[sel][chno].dirty = 1;
    vsu_cscale_block[sel][chno].dirty = 1;
    vsu_yhcoeff0_block[sel][chno].dirty = 1;

    return 0;
}

/**
 *  function       : de_vsu_calc_scaler_para(unsigned char fmt,
 *      struct de_rect64 crop, struct de_rect frame,
 *      struct de_rect *crop_fix, struct scaler_para *ypara,
 *      struct scaler_para *cpara)
 *  description    : calculate scaler parameters
 *  parameters     :
 *      fmt     <format>
 *      crop.w  <framebuffer crop width with 32bit fraction part>
 *      crop.h  <framebuffer crop height with 32bit fraction part>
 *      crop.x  <framebuffer coordinate x with 32bit fraction part>
 *      crop.y  <framebuffer coordinate y with 32bit fraction part>
 *      frame.w <frame width in integer>
 *      frame.h <frame height in integer>
 *      crop_fix->w <framebuffer crop_fix width after fixed>
 *      crop_fix->h <framebuffer crop_fix height after fixed>
 *      crop_fix->x <framebuffer crop_fix coordinate x after fixed>
 *      crop_fix->y <framebuffer crop_fix coordinate y after fixed>
 *      yhstep  <y/r channel horizon scale ratio>
 *      yvstep  <y/r channel vertical scale ratio>
 *      yhphase <y/r channel horizon initial phase>
 *      yvphase <y/r channel vertical initial phase>
 *      chstep  <uv/gb channel horizon scale ratio>
 *      cvstep  <uv/gb channel vertical scale ratio>
 *      chphase <uv/gb channel horizon initial phase>
 *      cvphase <uv/gb channel vertical initial phase>
 *  return         :
 *                   success
 */
int de_vsu_calc_scaler_para(unsigned char fmt, struct de_rect64 crop,
            struct de_rect frame,
            struct de_rect *crop_fix, struct scaler_para *ypara,
            struct scaler_para *cpara)
{
    int format;
    unsigned long long tmp = 0;

    switch (fmt) {
    case DE_FORMAT_YUV422_I_YVYU:
    case DE_FORMAT_YUV422_I_YUYV:
    case DE_FORMAT_YUV422_I_UYVY:
    case DE_FORMAT_YUV422_I_VYUY:
    case DE_FORMAT_YUV422_P:
    case DE_FORMAT_YUV422_SP_UVUV:
    case DE_FORMAT_YUV422_SP_VUVU:
        format = VSU_FORMAT_YUV422;
        break;
    case DE_FORMAT_YUV420_P:
    case DE_FORMAT_YUV420_SP_UVUV:
    case DE_FORMAT_YUV420_SP_VUVU:
        format = VSU_FORMAT_YUV420;
        break;
    case DE_FORMAT_YUV411_P:
    case DE_FORMAT_YUV411_SP_UVUV:
    case DE_FORMAT_YUV411_SP_VUVU:
        format = VSU_FORMAT_YUV411;
        break;
    default:
        format = VSU_FORMAT_RGB;
        break;
    }

    tmp = (N2_POWER(crop.w, VSU_PHASE_FRAC_BITWIDTH));
    if (frame.w)
        tmp = tmp / frame.w;
    else
        tmp = 0;
    ypara->hstep = (unsigned int)(tmp >> VSU_FB_FRAC_BITWIDTH);

    tmp = (N2_POWER(crop.h, VSU_PHASE_FRAC_BITWIDTH));
    if (frame.h)
        tmp = tmp / frame.h;
    else
        tmp = 0;
    ypara->vstep = (unsigned int)(tmp >> VSU_FB_FRAC_BITWIDTH);

    ypara->hphase
        = ((crop.x & 0xffffffff) >> (32 - VSU_PHASE_FRAC_BITWIDTH));
    ypara->vphase
        = ((crop.y & 0xffffffff) >> (32 - VSU_PHASE_FRAC_BITWIDTH));

    crop_fix->w
        = (unsigned int)(
        ((crop.w & 0xffffffff) + (crop.x & 0xffffffff))
        >= N2_POWER(1, VSU_FB_FRAC_BITWIDTH) ?
        ((crop.w >> VSU_FB_FRAC_BITWIDTH) + 1) :
        (crop.w >> VSU_FB_FRAC_BITWIDTH));

    crop_fix->h
        = (unsigned int)(
        ((crop.h & 0xffffffff) + (crop.y & 0xffffffff))
        >= N2_POWER(1, VSU_FB_FRAC_BITWIDTH) ?
        ((crop.h >> VSU_FB_FRAC_BITWIDTH) + 1) :
        (crop.h >> VSU_FB_FRAC_BITWIDTH));

    crop_fix->x = (int)(crop.x >> VSU_FB_FRAC_BITWIDTH);
    crop_fix->y = (int)(crop.y >> VSU_FB_FRAC_BITWIDTH);

    if (format == VSU_FORMAT_RGB) {
        cpara->hstep = ypara->hstep;
        cpara->vstep = ypara->vstep;
        cpara->hphase = ypara->hphase;
        cpara->vphase = ypara->vphase;
    } else if (format == VSU_FORMAT_YUV422) {
        /* horizon crop info fix */
        if ((crop_fix->x & 0x1) == 0x0 && (crop_fix->w & 0x1) == 0x1)
            /* odd crop_w, crop down width, */
            /* last line may disappear */
            crop_fix->w = (crop_fix->w >> 1) << 1;
        else if ((crop_fix->x & 0x1) == 0x1
            && (crop_fix->w & 0x1) == 0x0) {
            /* odd crop_x, crop down x, and phase + 1 */
            crop_fix->x = (crop_fix->x >> 1) << 1;
            ypara->hphase = ypara->hphase
            + (unsigned int)(N2_POWER(1, VSU_PHASE_FRAC_BITWIDTH));
        } else if ((crop_fix->x & 0x1) == 0x1
            && (crop_fix->w & 0x1) == 0x1) {
            /* odd crop_x and crop_w, */
            /* crop_x - 1, and phase + 1, crop_w + 1 */
            crop_fix->x = (crop_fix->x >> 1) << 1;
            ypara->hphase = ypara->hphase
            + (unsigned int)(N2_POWER(1, VSU_PHASE_FRAC_BITWIDTH));
            crop_fix->w = ((crop_fix->w + 1) >> 1) << 1;
        }

        cpara->hstep = ypara->hstep >> 1;
        cpara->vstep = ypara->vstep;
        cpara->hphase = ypara->hphase;
        cpara->vphase = ypara->vphase;
    } else if (format == VSU_FORMAT_YUV420) {
        /* horizon crop info fix */
        if ((crop_fix->x & 0x1) == 0x0 && (crop_fix->w & 0x1) == 0x1)
            /* odd crop_w, crop down width, */
            /* last line may disappear */
            crop_fix->w = (crop_fix->w >> 1) << 1;
        else if ((crop_fix->x & 0x1) == 0x1
            && (crop_fix->w & 0x1) == 0x0) {
            /* odd crop_x, crop down x, and phase + 1 */
            crop_fix->x = (crop_fix->x >> 1) << 1;
            ypara->hphase = ypara->hphase
            + (unsigned int)(N2_POWER(1, VSU_PHASE_FRAC_BITWIDTH));
        } else if ((crop_fix->x & 0x1) == 0x1
            && (crop_fix->w & 0x1) == 0x1) {
            /* odd crop_x and crop_w, crop_x - 1, */
            /* and phase + 1, crop_w + 1 */
            crop_fix->x = (crop_fix->x >> 1) << 1;
            ypara->hphase = ypara->hphase
            + (unsigned int)(N2_POWER(1, VSU_PHASE_FRAC_BITWIDTH));
            crop_fix->w = ((crop_fix->w + 1) >> 1) << 1;
        }
        /* vertical crop info fix */
        if ((crop_fix->y & 0x1) == 0x0 && (crop_fix->h & 0x1) == 0x1)
            /* odd crop_h, crop down height, */
            /* last line may disappear */
            crop_fix->h = (crop_fix->h >> 1) << 1;
        else if ((crop_fix->y & 0x1) == 0x1
            && (crop_fix->h & 0x1) == 0x0) {
            /* odd crop_y, crop down y, and phase + 1 */
            crop_fix->y = (crop_fix->y >> 1) << 1;
            ypara->vphase = ypara->vphase
            + (unsigned int)(N2_POWER(1, VSU_PHASE_FRAC_BITWIDTH));
        } else if ((crop_fix->y & 0x1) == 0x1
            && (crop_fix->h & 0x1) == 0x1) {
            /* odd crop_y and crop_h, crop_y - 1, */
            /* and phase + 1, crop_h + 1 */
            crop_fix->y = (crop_fix->y >> 1) << 1;
            ypara->vphase = ypara->vphase
            + (unsigned int)(N2_POWER(1, VSU_PHASE_FRAC_BITWIDTH));
            crop_fix->h = ((crop_fix->h + 1) >> 1) << 1;
        }

        cpara->hstep = ypara->hstep >> 1;
        cpara->vstep = ypara->vstep >> 1;
        /* H.261, H.263, MPEG-1 sample method */
        /* cpara->hphase = (ypara->hphase>>1) */
        /* - ((N2_POWER(1,VSU_PHASE_FRAC_BITWIDTH))>>2); */
        /* MPEG-2, MPEG-4.2, H264, VC-1 sample method (default choise)*/
        cpara->hphase = ypara->hphase >> 1;
        /* chorma vertical phase should -0.25 when input format is */
        /* yuv420 */
        cpara->vphase = (ypara->vphase >> 1)
            - ((N2_POWER(1, VSU_PHASE_FRAC_BITWIDTH)) >> 2);
    } else if (format == VSU_FORMAT_YUV411) {
        /* horizon crop info */
        if ((crop_fix->x & 0x3) == 0x0 && (crop_fix->w & 0x3) != 0x0)
            /* odd crop_w, crop down width, */
            /* last 1-3 lines may disappear */
            crop_fix->w = (crop_fix->w >> 2) << 2;
        else if ((crop_fix->x & 0x3) != 0x0
            && (crop_fix->w & 0x3) == 0x0) {
            /* odd crop_x, crop down x, and phase + 1 */
            crop_fix->x = (crop_fix->x >> 2) << 2;
            ypara->hphase = ypara->hphase
            + (unsigned int)
            (N2_POWER(crop_fix->x & 0x3, VSU_PHASE_FRAC_BITWIDTH));
        } else if ((crop_fix->x & 0x3) != 0x0
            && (crop_fix->w & 0x3) != 0x0) {
            /* odd crop_x and crop_w, crop_x aligned to 4 pixel */
            crop_fix->x = (crop_fix->x >> 2) << 2;
            ypara->hphase = ypara->hphase
            + (unsigned int)
            (N2_POWER(crop_fix->x & 0x3, VSU_PHASE_FRAC_BITWIDTH));
            crop_fix->w
            = ((crop_fix->w + (crop_fix->x & 0x3)) >> 2) << 2;
        }

        cpara->hstep = ypara->hstep >> 2;
        cpara->vstep = ypara->vstep;
        cpara->hphase = ypara->hphase;
        cpara->vphase = ypara->vphase;
    }
    return 0;
}

/**
 *  function       : de_vsu_sel_ovl_scaler_para(unsigned char *en,
 *          struct scaler_para *layer_luma_scale_para[],
 *          struct scaler_para *layer_chroma_scale_para[],
 *          struct scaler_para *ovl_luma_scale_para,
 *          struct scaler_para *ovl_chroma_scale_para)
 *  description    : calculate video overlay scaler parameters
 *  parameters     :
 *      en          <pointer of layer enable>
 *      layer_luma_scale_para   <pointer array of video layer luma
 *                  channel scaler parameter>
 *      layer_chroma_scale_para <pointer array of video layer chroma
 *                  channel scaler parameter>
 *      ovl_luma_scale_para     <pointer of video overlay luma
 *                  channel scaler parameter>
 *      ovl_chroma_scale_para   <pointer of video overlay chroma
 *                  channel scaler parameter>
 *  return         :
 *          success
 */
int de_vsu_sel_ovl_scaler_para(unsigned char *en,
                struct scaler_para *layer_luma_scale_para,
                struct scaler_para *layer_chroma_scale_para,
                struct scaler_para *ovl_luma_scale_para,
                struct scaler_para *ovl_chroma_scale_para)
{
    int i, j, layer_en_num;
    int used_layer_idx[LAYER_MAX_NUM_PER_CHN];

    /* get valid layer number and record layer index */
    layer_en_num = 0;
    j = 0;
    for (i = 0; i < LAYER_MAX_NUM_PER_CHN; i++) {
        if (*(en + i) == 1) {
            layer_en_num++;
            used_layer_idx[j++] = i;
        }
    }

    if (layer_en_num == 1) {
        /*only one layer enabled in one overlay */
        /* set overlay scale para through this layer */
        ovl_luma_scale_para->hphase =
            layer_luma_scale_para[used_layer_idx[0]].hphase;
        ovl_luma_scale_para->vphase =
            layer_luma_scale_para[used_layer_idx[0]].vphase;
        ovl_luma_scale_para->hstep =
            layer_luma_scale_para[used_layer_idx[0]].hstep;
        ovl_luma_scale_para->vstep =
            layer_luma_scale_para[used_layer_idx[0]].vstep;

        ovl_chroma_scale_para->hphase =
            layer_chroma_scale_para[used_layer_idx[0]].
            hphase;
        ovl_chroma_scale_para->vphase =
            layer_chroma_scale_para[used_layer_idx[0]].vphase;
        ovl_chroma_scale_para->hstep =
            layer_chroma_scale_para[used_layer_idx[0]].hstep;
        ovl_chroma_scale_para->vstep =
            layer_chroma_scale_para[used_layer_idx[0]].vstep;
    } else if (layer_en_num > 1) {
        /* two or more layers enabled in one overlay */
        /* set overlay scale step through first enabled layer */
        ovl_luma_scale_para->hstep =
            layer_luma_scale_para[used_layer_idx[0]].hstep;
        ovl_luma_scale_para->vstep =
            layer_luma_scale_para[used_layer_idx[0]].vstep;
        ovl_chroma_scale_para->hstep =
            layer_chroma_scale_para[used_layer_idx[0]].hstep;
        ovl_chroma_scale_para->vstep =
            layer_chroma_scale_para[used_layer_idx[0]].vstep;

        /* set overlay phase through 1st enabled non-zero-phase layer */
        for (i = 0; i < layer_en_num; i++) {
            if (layer_luma_scale_para[used_layer_idx[i]].hphase
                != 0) {
                ovl_luma_scale_para->hphase =
                layer_luma_scale_para[used_layer_idx[i]].hphase;
                ovl_chroma_scale_para->hphase =
                layer_chroma_scale_para[used_layer_idx[i]].
                    hphase;

                break;
            }
        }

        /* all layer phase equal to zero */
        if (i == layer_en_num) {
            ovl_luma_scale_para->hphase =
                layer_luma_scale_para[used_layer_idx[0]].hphase;
            ovl_chroma_scale_para->hphase =
                layer_chroma_scale_para[used_layer_idx[0]].hphase;
        }
        /* set overlay phase through first non-zero layer */
        for (i = 0; i < layer_en_num; i++) {
            if (layer_luma_scale_para[used_layer_idx[i]].vphase
                != 0) {
                ovl_luma_scale_para->vphase =
                    layer_luma_scale_para[used_layer_idx[i]].
                    vphase;
                ovl_chroma_scale_para->vphase =
                    layer_chroma_scale_para[used_layer_idx[i]].
                    vphase;
                break;
            }
        }

        /* all layer phase equal to zero */
        if (i == layer_en_num) {
            ovl_luma_scale_para->vphase =
            layer_luma_scale_para[used_layer_idx[0]].vphase;
            ovl_chroma_scale_para->vphase =
            layer_chroma_scale_para[used_layer_idx[0]].vphase;
        }

    } else {
        ovl_luma_scale_para->hphase = 0;
        ovl_luma_scale_para->vphase = 0;
        ovl_luma_scale_para->hstep =
            (unsigned int)N2_POWER(1, VSU_PHASE_FRAC_BITWIDTH);
        ovl_luma_scale_para->vstep =
            (unsigned int)N2_POWER(1, VSU_PHASE_FRAC_BITWIDTH);
        ovl_chroma_scale_para->hphase = 0;
        ovl_chroma_scale_para->vphase = 0;
        ovl_chroma_scale_para->hstep =
            (unsigned int)N2_POWER(1, VSU_PHASE_FRAC_BITWIDTH);
        ovl_chroma_scale_para->vstep =
            (unsigned int)N2_POWER(1, VSU_PHASE_FRAC_BITWIDTH);
    }

    return 0;
}

/**
 *  function       : de_vsu_recalc_scale_para(int coarse_status,
 *              unsigned int vsu_outw, unsigned int vsu_outh,
 *              unsigned int vsu_inw, unsigned int vsu_inh,
 *              unsigned int vsu_inw_c, unsigned int vsu_inh_c,
 *              scale_para *fix_y_para, scale_para *fix_c_para)
 *  description    : recalculate scale para through coarse status
 *  parameters     :
 *      coarse_status       <0-no coarse scale in both direction,
 *                  1-coarse scale only in horizon,
 *                  2-coarse scale only in vertical,
 *                  3-coarse scale in both direction>
 *      vsu_outw,vsu_outh   <vsu output size>
 *      vsu_inw,vsu_inh     <vsu input y size>
 *      vsu_inw_c,vsu_inh_c <vsu input cbcr size>
 *      fix_y_para          <vsu y channel fixed scale para>
 *      fix_c_para          <vsu cbcr channel fixed scale para>
 *  return         :
 *                   success
 */
int de_vsu_recalc_scale_para(int coarse_status, unsigned int vsu_outw,
            unsigned int vsu_outh, unsigned int vsu_inw,
            unsigned int vsu_inh, unsigned int vsu_inw_c,
            unsigned int vsu_inh_c, struct scaler_para *fix_y_para,
            struct scaler_para *fix_c_para)
{
    unsigned int tmp = 0;

    if (coarse_status & DE_CS_HORZ) {
        tmp = N2_POWER(vsu_inw, VSU_PHASE_FRAC_BITWIDTH);
        tmp = tmp / vsu_outw;
        fix_y_para->hstep = tmp;

        tmp = N2_POWER(vsu_inw_c, VSU_PHASE_FRAC_BITWIDTH);
        tmp = tmp / vsu_outw;
        fix_c_para->hstep = tmp;
        /* no meaning when coarse scale using */
        fix_y_para->hphase = 0;
        /* no meaning when coarse scale using */
        fix_c_para->hphase = 0;
    }

    if (coarse_status & DE_CS_VERT) {
        tmp = N2_POWER(vsu_inh, VSU_PHASE_FRAC_BITWIDTH);
        tmp = tmp / vsu_outh;
        fix_y_para->vstep = tmp;

        tmp = N2_POWER(vsu_inh_c, VSU_PHASE_FRAC_BITWIDTH);
        tmp = tmp / vsu_outh;
        fix_c_para->vstep = tmp;
        /* no meaning when coarse scale using */
        fix_y_para->vphase = 0;
        /* no meaning when coarse scale using */
        fix_c_para->vphase = 0;
    }

    return 0;
}

/**
 *  function       : de_recalc_ovl_bld_for_scale((unsigned int scaler_en,
 *  unsigned char *lay_en, int laynum, struct scaler_para *step,
 *  struct de_rect *layer, struct de_rect *bld_rect, unsigned int *ovlw,
 *  unsigned int *ovlh, unsigned int gsu_sel,
 *  unsigned int scn_w, unsigned scn_h)
 *  description    : recalculate overlay and blending parameters for scaler
 *              size limitation
 *  return         :
 *          success
 */
int de_recalc_ovl_bld_for_scale(unsigned int scaler_en, unsigned char *lay_en,
        int laynum, struct scaler_para *step, struct de_rect *layer,
        struct de_rect *bld_rect, unsigned int *ovlw,
        unsigned int *ovlh, unsigned int gsu_sel,
        unsigned int scn_w, unsigned scn_h)
{
    unsigned int shift, i;
    unsigned int org_bld_w, org_bld_h;

    if (scaler_en == 0)
        return 0;

    if (*ovlw != 0 && *ovlh != 0 && bld_rect->w != 0 && bld_rect->h != 0
        && step->hstep != 0 && step->vstep != 0) {
        /* horizon */
        if (*ovlw < SC_MIN_WIDTH || bld_rect->w < SC_MIN_WIDTH) {
            shift = (gsu_sel == 0) ? VSU_PHASE_FRAC_BITWIDTH :
                GSU_PHASE_FRAC_BITWIDTH;
            org_bld_w = bld_rect->w;
            if (step->hstep > (1 << shift)) {
                /* scale down */
                bld_rect->w = SC_MIN_WIDTH;
                *ovlw = (step->hstep * SC_MIN_WIDTH) >> shift;
            } else {
                /* scale up */
                *ovlw = SC_MIN_WIDTH;
                bld_rect->w = SC_MIN_WIDTH * (1 << shift)
                        / step->hstep;
            }

            if (bld_rect->w + bld_rect->x > scn_w) {
                bld_rect->x -= (bld_rect->w - org_bld_w);

                for (i = 0; i < laynum; i++) {
                    if (lay_en[i]) {
                        layer[i].x
                            += ((step->hstep
                            * (bld_rect->w
                            - org_bld_w)) >> shift);
                    }
                }
            }
        }
        /* vertical */
        if (*ovlh < SC_MIN_HEIGHT || bld_rect->h < SC_MIN_HEIGHT) {
            shift = (gsu_sel == 0) ? VSU_PHASE_FRAC_BITWIDTH :
                GSU_PHASE_FRAC_BITWIDTH;
            org_bld_h = bld_rect->h;
            if (step->vstep > (1 << shift)) {
                /* scale down */
                bld_rect->h = SC_MIN_HEIGHT;
                *ovlh = (step->vstep * SC_MIN_HEIGHT) >> shift;
            } else {
                /* scale up */
                *ovlh = SC_MIN_HEIGHT;
                bld_rect->h = SC_MIN_HEIGHT * (1 << shift)
                        / step->vstep;
            }

            if (bld_rect->h + bld_rect->y > scn_h) {
                bld_rect->y -= (bld_rect->h - org_bld_h);

                for (i = 0; i < laynum; i++) {
                    if (lay_en[i]) {
                        layer[i].y
                            += ((step->vstep
                            * (bld_rect->h
                            - org_bld_h)) >> shift);
                    }
                }
            }
        }

    }

    return 0;
}
