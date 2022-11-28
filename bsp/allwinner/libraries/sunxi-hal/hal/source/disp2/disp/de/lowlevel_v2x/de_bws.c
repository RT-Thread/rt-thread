/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

/******************************************************************************
 *  All Winner Tech, All Right Reserved. 2014-2015 Copyright (c)
 *
 *  File name   : de_bws.c
 *
 *  Description : display engine 2.0 bws basic function definition
 *
 *  History     : 2014/04/01  vito cheng  v0.1  Initial version
 *                2014/04/25      vito cheng  v0.11 Add block updated function
 *****************************************************************************/

#ifdef CONFIG_DISP2_SUNXI_SUPPORT_ENAHNCE
#include "de_bws_type.h"
#include "de_rtmx.h"
#include "de_fce_type.h"
#include "de_enhance.h"

#define BWS_OFST    0xA2000 /* BWS offset based on RTMX */

static volatile struct __bws_reg_t *bws_dev[DE_NUM][CHN_NUM];
static struct de_reg_blocks bws_block[DE_NUM][CHN_NUM];
static struct de_reg_blocks bws_para_block[DE_NUM][CHN_NUM];

static uintptr_t bws_hw_base[DE_NUM][CHN_NUM] = { {0} };

/* for bws */
static struct __bws_status_t *g_bws_status[DE_NUM][CHN_NUM];

/******************************************************************************
 * function       : de_bws_set_reg_base(unsigned int sel, unsigned int chno,
 *                                   unsigned int base)
 * description    : set bws reg base
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  base        <reg base>
 * return         :
 *                  success
 *****************************************************************************/
int de_bws_set_reg_base(unsigned int sel, unsigned int chno, void *base)
{
    bws_dev[sel][chno] = (struct __bws_reg_t *) base;

    return 0;
}

#ifdef __VEP_DO_IT_IN_VBLANK
int de_bws_update_regs(unsigned int sel, unsigned int chno)
{
    if (bws_block[sel][chno].dirty == 0x1) {
        regwrite((void *)bws_block[sel][chno].off,
               bws_block[sel][chno].val, bws_block[sel][chno].size);
        bws_block[sel][chno].dirty = 0x0;
    }

    return 0;
}
#else
int de_bws_update_regs(unsigned int sel, unsigned int chno)
{
    if (bws_block[sel][chno].dirty == 0x1) {
        regwrite((void *)bws_block[sel][chno].off,
               bws_block[sel][chno].val, bws_block[sel][chno].size);
        bws_block[sel][chno].dirty = 0x0;
    }

    if (bws_para_block[sel][chno].dirty == 0x1) {
        regwrite((void *)bws_para_block[sel][chno].off,
               bws_para_block[sel][chno].val,
               bws_para_block[sel][chno].size);
        bws_para_block[sel][chno].dirty = 0x0;
    }
    return 0;
}

#endif

int de_bws_init(unsigned int sel, unsigned int chno, uintptr_t reg_base)
{
    uintptr_t base;
    void *memory;

    base = reg_base + (sel + 1) * 0x00100000 + BWS_OFST;
#if defined(CONFIG_ARCH_SUN50IW10)
    if (sel)
        base = base - 0x00100000;
#endif
    /* FIXME  display path offset should be defined */
    bws_hw_base[sel][chno] = base;

    DE_INF("sel %d, bws_base[%d]=0x%p\n", sel, chno, (void *)base);

    memory = disp_sys_malloc(sizeof(struct __bws_reg_t));
    if (memory == NULL) {
        DE_WRN("disp_sys_malloc bws[%d][%d] memory fail! size=0x%x\n", sel, chno,
              (unsigned int)sizeof(struct __bws_reg_t));
        return -1;
    }

    bws_block[sel][chno].off = base;
    bws_block[sel][chno].val = memory;
    bws_block[sel][chno].size = 0x10;
    bws_block[sel][chno].dirty = 0;

    bws_para_block[sel][chno].off = base + 0x20;
    bws_para_block[sel][chno].val = memory + 0x20;
    bws_para_block[sel][chno].size = 0x10;
    bws_para_block[sel][chno].dirty = 0;

    de_bws_set_reg_base(sel, chno, memory);

    /* bws */
    g_bws_status[sel][chno] = disp_sys_malloc(sizeof(struct __bws_status_t));
    /* FIXME where to FREE? */
    if (g_bws_status[sel][chno] == NULL) {
        DE_WRN("disp_sys_malloc g_bws_status[%d][%d] memory fail! size=0x%x\n",
              sel, chno, (unsigned int)sizeof(struct __bws_status_t));
        return -1;
    }

    g_bws_status[sel][chno]->isenable = 0;
    g_bws_status[sel][chno]->runtime = 0;
    g_bws_status[sel][chno]->preslopeready = 0;

    return 0;
}

/******************************************************************************
 * function       : de_bws_enable(unsigned int sel, unsigned int chno,
 *                                 unsigned int en)
 * description    : enable/disable bws
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  en          <enable: 0-disable; 1-enable>
 * return         :
 *                  success
 *****************************************************************************/
int de_bws_enable(unsigned int sel, unsigned int chno, unsigned int en)
{
    bws_dev[sel][chno]->ctrl.bits.en = en;
    bws_block[sel][chno].dirty = 1;
    return 0;
}

/******************************************************************************
 * function       : de_bws_set_size(unsigned int sel, unsigned int chno,
 *                                   unsigned int width, unsigned int height)
 * description    : set bws size
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  width       <input width>
 *                                      height  <input height>
 * return         :
 *                  success
 *****************************************************************************/
int de_bws_set_size(unsigned int sel, unsigned int chno, unsigned int width,
                unsigned int height)
{
    bws_dev[sel][chno]->size.bits.width = width - 1;
    bws_dev[sel][chno]->size.bits.height = height - 1;
    bws_block[sel][chno].dirty = 1;
    return 0;
}

/******************************************************************************
 * function       : de_bws_set_window(unsigned int sel, unsigned int chno,
 *                 unsigned int win_enable, struct de_rect window)
 * description    : set bws window
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  win_enable  <enable: 0-window mode disable;
 *                  1-window mode enable>
 *                                      window  <window rectangle>
 * return         :
 *                  success
 *****************************************************************************/
int de_bws_set_window(unsigned int sel, unsigned int chno,
                unsigned int win_enable, struct de_rect window)
{
    bws_dev[sel][chno]->ctrl.bits.win_en = win_enable;

    if (win_enable) {
        bws_dev[sel][chno]->win0.bits.win_left = window.x;
        bws_dev[sel][chno]->win0.bits.win_top = window.y;
        bws_dev[sel][chno]->win1.bits.win_right =
            window.x + window.w - 1;
        bws_dev[sel][chno]->win1.bits.win_bot = window.y + window.h - 1;
    }
    bws_block[sel][chno].dirty = 1;
    return 0;
}

/******************************************************************************
 * function       : de_bws_set_para(unsigned int sel, unsigned int chno,
 *                  unsigned int min, unsigned int black,
 *                  unsigned int white, unsigned int max,
 *                  unsigned int slope0, unsigned int slope1,
 *                  unsigned int slope2, unsigned int slope3)
 *
 * description    : set bws para
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  min/max/black/white <bws threshold>
 *                                      slope0/1/2/3 <bws slope>
 * return         :
 *                  success
 *****************************************************************************/
#ifdef __VEP_DO_IT_IN_VBLANK
int de_bws_set_para(unsigned int sel, unsigned int chno,
        unsigned int min, unsigned int black, unsigned int white,
        unsigned int max, unsigned int slope0, unsigned int slope1,
        unsigned int slope2, unsigned int slope3)
{
    uintptr_t base;

    base = bws_hw_base[sel][chno];

    writel((black << 16) | min, (void  *)(base + 0x20));
    writel((max << 16) | white, (void  *)(base + 0x24));
    writel((slope1 << 16) | slope0, (void  *)(base + 0x28));
    writel((slope3 << 16) | slope2, (void  *)(base + 0x2c));

    return 0;
}
#else
int de_bws_set_para(unsigned int sel, unsigned int chno,
        unsigned int min, unsigned int black, unsigned int white,
        unsigned int max, unsigned int slope0, unsigned int slope1,
        unsigned int slope2, unsigned int slope3)
{

    bws_dev[sel][chno]->blkthr.bits.min = min;
    bws_dev[sel][chno]->blkthr.bits.black = black;
    bws_dev[sel][chno]->whtthr.bits.max = max;
    bws_dev[sel][chno]->whtthr.bits.white = white;

    bws_dev[sel][chno]->blkslp.bits.slope0 = slope0;
    bws_dev[sel][chno]->blkslp.bits.slope1 = slope1;
    bws_dev[sel][chno]->whtslp.bits.slope2 = slope2;
    bws_dev[sel][chno]->whtslp.bits.slope3 = slope3;

    bws_para_block[sel][chno].dirty = 1;

    return 0;
}

#endif
/******************************************************************************
 * function       : auto_bws_model(unsigned int width, unsigned int height,
 *                  unsigned int hist[256], unsigned int hist_pre[256],
 *                  unsigned int sum,
 *                  unsigned int pre_slope_black, unsigned int pre_slope_white,
 *                  unsigned int frame_bld_en, unsigned int bld_high_thr,
 *                  unsigned int bld_low_thr, unsigned int bld_weight_lmt,
 *                  unsigned int present_black, unsigned int present_white,
 *                  unsigned int slope_black_lmt, unsigned int slope_white_lmt,
 *                  unsigned int black_prec, unsigned int white_prec,
 *                  unsigned int lowest_black, unsigned int highest_white,
 *                  unsigned int *ymin, unsigned int *black,
 *                  unsigned int *white, unsigned int *ymax,
 *                  unsigned int *slope0, unsigned int *slope1,
 *                  unsigned int *slope2, unsigned int *slope3)
 * description    : Auto-BWS Alg
 * parameters     :
 *                  width               <layer width>
 *                  height              <layer height>
 *                  hist[256]   <the latest frame histogram>
 *                  hist_pre[256] <the frame before the latest frame histogram>
 *                  sum  <the latest frame pixel value sum>
 *                  pre_slope_black/pre_slope_white
 *                  <the frame before the latest frame auto-bws result>
 *                  ymin/black/white/ymax/shope0/1/2/3 <auto-bws result>
 * return         :
 ****************************************************************************/
/*
 *R_ROPC_EN--frame_bld_en--1
 *R_ROPC_TH_UPPER--bld_high_thr--90
 *R_ROPC_TH_LOWER--bld_low_thr--74
 *R_ROPC_WEIGHT_MIN--bld_weight_lmt--8
 *R_PRESET_TILT_BLACK--present_black--53
 *R_PRESET_TILT_WHITE--present_white--235
 *R_SLOPE_LIMIT_BLACK--slope_black_lmt--512
 *R_SLOPE_LIMIT_WHITE--slope_white_lmt--384
 *R_BLACK_PERCENT--black_prec--5
 *R_WHITE_PERCENT--white_prec--2
 *R_LOWEST_BLACK--lowest_black--3
 *R_HIGHEST_WHITE--highest_white--252
 */
static void auto_bws_model(unsigned int width, unsigned int height,
        unsigned int hist[256], unsigned int hist_pre[256],
        unsigned int sum, unsigned int pre_slope_black,
        unsigned int pre_slope_white,
        unsigned int frame_bld_en, unsigned int bld_high_thr,
        unsigned int bld_low_thr,
        unsigned int bld_weight_lmt,
        unsigned int present_black,
        unsigned int present_white,
        unsigned int slope_black_lmt,
        unsigned int slope_white_lmt,
        unsigned int black_prec, unsigned int white_prec,
        unsigned int lowest_black,
        unsigned int highest_white, unsigned int *ymin,
        unsigned int *black, unsigned int *white,
        unsigned int *ymax, unsigned int *slope0,
        unsigned int *slope1, unsigned int *slope2,
        unsigned int *slope3)
{
    int coeff, diff_hist, total, k;
    int validcnt, validsum;
    int ratio_b, ratio_w, cdf_b, cdf_w;
    int weight;
    int mean;
    int pd_ymin = lowest_black, pd_ymax = highest_white;
    int pd_black, pd_white;
    int pd_ymin_fix, pd_ymax_fix;
    int pd_s0, pd_s1, pd_s2, pd_s3;
    int tmp;
    /* 1.calculate frame different and frame blend weight */
    if (frame_bld_en) {
        diff_hist = 0;
        total = 0;
        for (k = 0; k < 256; k++) {
            diff_hist += abs(hist[k] - hist_pre[k]);
            total += hist[k];
        }
        coeff = (100 * diff_hist) / total;

        weight = (coeff >= bld_high_thr) ? 256 :
            (coeff < bld_low_thr) ? bld_weight_lmt :
            ((256 - bld_weight_lmt) / (bld_high_thr -
                           bld_low_thr) * (coeff -
                                   bld_low_thr) +
             bld_weight_lmt);

    } else {
        total = 0;
        for (k = 0; k < 256; k++)
            total += hist[k];
        weight = 256;
    }

    /* 2.kick out the lowest black and the highest white in hist and sum */
    validcnt = total;
    for (k = 0; k < lowest_black; k++)
        validcnt -= hist[k];
    for (k = 255; k > highest_white - 1; k--)
        validcnt -= hist[k];

    validsum = sum;
    for (k = 0; k < lowest_black; k++)
        validsum -= hist[k] * k;
    for (k = 255; k > highest_white - 1; k--)
        validsum -= hist[k] * k;
    if (validcnt != 0) {
        mean = validsum / validcnt;

        /* 3.find Ymin and Ymax */
        ratio_b = validcnt * black_prec / 100;
        cdf_b = 0;
        for (k = lowest_black; k < 255; k++) {
            cdf_b += hist[k];
            if (cdf_b > ratio_b) {
                pd_ymin = k;
                break;
            }
        }

        ratio_w = validcnt * white_prec / 100;
        cdf_w = 0;
        for (k = highest_white; k >= 0; k--) {
            cdf_w += hist[k];
            if (cdf_w > ratio_w) {
                pd_ymax = k;
                break;
            }
        }

        /* 4.limit black and white don't cross mean */
        pd_black = (present_black < mean) ? present_black : mean;
        pd_white = (present_white > mean) ? present_white : mean;

        /* 5.calculate slope1/2
         * and limit to slope_black_lmt or slope_white_lmt
         */
        pd_s1 =
            (pd_ymin < pd_black) ?
            ((pd_black << 8) / (pd_black - pd_ymin)) : 256;

        pd_s1 = (pd_s1 > slope_black_lmt) ? slope_black_lmt : pd_s1;

        pd_s2 =
            (pd_ymax > pd_white) ?
            (((255 - pd_white) << 8) / (pd_ymax - pd_white)) : 256;
        pd_s2 = (pd_s2 > slope_white_lmt) ? slope_white_lmt : pd_s2;

        /* 6.frame blend to slope1/2 */
        pd_s1 =
            (pre_slope_black * (256 - weight) + weight * pd_s1) >> 8;
        pd_s2 =
            (pre_slope_white * (256 - weight) + weight * pd_s2) >> 8;

        tmp = pd_black + ((pd_s1 * (pd_ymin - pd_black) + 128) >> 8);
        /* 7.calculate slope0/3 and re-calculate ymin and ymax */
        if ((tmp > 0) && (pd_ymin < pd_black) && (pd_ymin > 0)) {
            pd_s0 = ((tmp << 8) + 128) / pd_ymin;
            pd_ymin_fix = pd_ymin;
        } else if (pd_ymin >= pd_black) {
            /* do noting use s0 */
            pd_s0 = 256;
            pd_ymin_fix = 0;
        } else {
            pd_s0 = 0;
            pd_ymin_fix =
                -((pd_black << 8) - 128) / pd_s1 + pd_black;
        }

        tmp = pd_white + ((pd_s2 * (pd_ymax - pd_white)) >> 8);
        if ((tmp < 255) && (pd_ymax > pd_white) && (pd_ymax < 255)) {
            pd_s3 = (((255 - tmp) << 8) + 128) / (255 - pd_ymax);
            pd_ymax_fix = pd_ymax;
        } else if (pd_ymax <= pd_white) {
            /* do noting use s3 */
            pd_s3 = 256;
            pd_ymax_fix = 255;
        } else {
            pd_s3 = 0;
            pd_ymax_fix =
                (((255 - pd_white) << 8) - 128) / pd_s2 + pd_white;
        }
    } else {
        /* no enough pixel for auto bws */
        pd_ymin_fix = 16;
        pd_black = 32;
        pd_white = 224;
        pd_ymax_fix = 240;
        pd_s0 = 0x100;
        pd_s1 = 0x100;
        pd_s2 = 0x100;
        pd_s3 = 0x100;
    }

    *ymin = pd_ymin_fix;
    *black = pd_black;
    *white = pd_white;
    *ymax = pd_ymax_fix;
    *slope0 = pd_s0;
    *slope1 = pd_s1;
    *slope2 = pd_s2;
    *slope3 = pd_s3;

}

/******************************************************************************
 * function       : de_bws_info2para(unsigned int auto_contrast,
 *                   struct de_rect window, struct __bws_config_data *para)
 * description    : info->para conversion
 * parameters     :
 *                  auto_contrast <info from user>
 *                  window              <window info>
 *                  para                <bsp para>
 * return         :
 *                  success
 *****************************************************************************/
int de_bws_info2para(unsigned int auto_contrast, struct de_rect window,
        struct __bws_config_data *para)
{
    /* parameters */
    para->bws_en = (auto_contrast == 2 || auto_contrast == 3) ? 1 : 0;

    /* window
     * para->win_en = 1;
     * para->win.x = window.x;
     * para->win.y = window.y;
     * para->win.w = window.w;
     * para->win.h = window.h;
     */
    return 0;
}

int de_bws_apply(unsigned int screen_id, unsigned int chno, unsigned int bws_en,
         unsigned int auto_contrast_dirty)
{
    if (bws_en == 1 && auto_contrast_dirty) {
        /* enable this time */
        g_bws_status[screen_id][chno]->isenable = 1;
        g_bws_status[screen_id][chno]->runtime = 0;
        g_bws_status[screen_id][chno]->preslopeready = 0;
    } else if (bws_en == 0 && auto_contrast_dirty) {
        /* disable this time */
        g_bws_status[screen_id][chno]->isenable = 0;
        g_bws_status[screen_id][chno]->runtime = 0;
        g_bws_status[screen_id][chno]->preslopeready = 0;
    }
    return 0;

}

int de_bws_tasklet(unsigned int screen_id, unsigned int chno,
           unsigned int frame_cnt)
{
    unsigned int pre_slope_black, pre_slope_white;
    unsigned int th0, th1, th2, th3, s0, s1, s2, s3;

    if (g_bws_status[screen_id][chno]->isenable
        && ((BWS_FRAME_MASK == (frame_cnt % 2))
        || (BWS_FRAME_MASK == 0x2))) {
        if (g_hist_status[screen_id][chno]->twohistready) {
            if (g_bws_status[screen_id][chno]->preslopeready) {
                pre_slope_black =
                    g_bws_status[screen_id][chno]->slope_black;
                pre_slope_white =
                    g_bws_status[screen_id][chno]->slope_white;
            } else {
                pre_slope_black = BWS_DEFAULT_SLOPE;
                pre_slope_white = BWS_DEFAULT_SLOPE;
            }

            auto_bws_model(g_bws_status[screen_id][chno]->width,
                       g_bws_status[screen_id][chno]->height,
                       g_hist[screen_id][chno],
                       g_hist_p[screen_id][chno],
                       g_sum[screen_id][chno], pre_slope_black,
                       pre_slope_white, 1, 90, 74, 8, 53, 235,
                       512, 384, 5, 2, 3, 252, &th0, &th1, &th2,
                       &th3, &s0, &s1, &s2, &s3);
            th0 = 32;
            th1 = 64;
            th2 = 224;
            th3 = 240;
            /* 384;  128 */
            s0 = 192;
            /* 128;  384; */
            s1 = 320;
            s2 = 384;
            s3 = 128;
        } else {
            /* hist no ready for auto_bws */
            th0 = 16;
            th1 = 32;
            th2 = 224;
            th3 = 240;
            s0 = BWS_DEFAULT_SLOPE;
            s1 = BWS_DEFAULT_SLOPE;
            s2 = BWS_DEFAULT_SLOPE;
            s3 = BWS_DEFAULT_SLOPE;
        }

        de_bws_set_para(screen_id, chno, th0, th1, th2, th3, s0, s1, s2,
                s3);

        g_bws_status[screen_id][chno]->slope_black = s1;
        g_bws_status[screen_id][chno]->slope_white = s2;

        if (g_bws_status[screen_id][chno]->runtime < 1)
            g_bws_status[screen_id][chno]->runtime++;
        else
            g_bws_status[screen_id][chno]->preslopeready = 1;
    }
    return 0;

}
#endif
