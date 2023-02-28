/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

/*******************************************************************************
 *  All Winner Tech, All Right Reserved. 2014-2015 Copyright (c)
 *
 *  File name   :  display engine 2.0 fce basic function definition
 *
 *  History     :  2014/04/01  vito cheng  v0.1  Initial version
 *                 2014/04/25      vito cheng  v0.11 Add block updated function
 ******************************************************************************/

#ifdef CONFIG_DISP2_SUNXI_SUPPORT_ENAHNCE
#include "de_fce_type.h"
#include "de_rtmx.h"
#include "de_enhance.h"
#include "de_vep_table.h"

static volatile struct __fce_reg_t *fce_dev[DE_NUM][CHN_NUM];

static struct de_reg_blocks fce_para_block[DE_NUM][CHN_NUM];
static struct de_reg_blocks fce_celut_block[DE_NUM][CHN_NUM];
static struct de_reg_blocks fce_hist_block[DE_NUM][CHN_NUM];

static uintptr_t fce_hw_base[DE_NUM][CHN_NUM] = { {0} };

struct __hist_status_t *g_hist_status[DE_NUM][CHN_NUM];

/* for ce */
struct __ce_status_t *g_ce_status[DE_NUM][CHN_NUM];
static unsigned char *g_celut[DE_NUM][CHN_NUM];
static struct hist_data *hist_res[DE_NUM][CHN_NUM];

/*******************************************************************************
 * function       : de_fce_set_reg_base(unsigned int sel, unsigned int chno,
 *                  unsigned int base)
 * description    : set fce reg base
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  base        <reg base>
 * return         :
 *                  success
 ******************************************************************************/
int de_fce_set_reg_base(unsigned int sel, unsigned int chno, void *base)
{
    fce_dev[sel][chno] = (struct __fce_reg_t *) base;

    return 0;
}

int de_fce_update_regs(unsigned int sel, unsigned int chno)
{
    uintptr_t base;

    if (fce_para_block[sel][chno].dirty == 0x1) {
        regwrite((void *)fce_para_block[sel][chno].off,
               fce_para_block[sel][chno].val,
               fce_para_block[sel][chno].size);
        fce_para_block[sel][chno].dirty = 0x0;
    }

    if (fce_celut_block[sel][chno].dirty == 0x1) {
        base = fce_hw_base[sel][chno];
        writel(0x1, (void  *)(base + 0x28));
        /* AHB access CE LUT */
        regwrite((void *)fce_celut_block[sel][chno].off,
               fce_celut_block[sel][chno].val,
               fce_celut_block[sel][chno].size);
        writel(0x0, (void  *)(base + 0x28));
        /* Module access CE LUT */
        fce_celut_block[sel][chno].dirty = 0x0;
    }

    return 0;
}

int de_fce_init(unsigned int sel, unsigned int chno, uintptr_t reg_base)
{
    uintptr_t base;
    void *memory;

    base = reg_base + (sel + 1) * 0x00100000 + FCE_OFST;
#if defined(CONFIG_ARCH_SUN50IW10)
    if (sel)
        base = base - 0x00100000;
#endif
    /* FIXME  display path offset should be defined */
    fce_hw_base[sel][chno] = base;

    memory = disp_sys_malloc(sizeof(struct __fce_reg_t));
    if (memory == NULL) {
        DE_WRN("disp_sys_malloc fce[%d][%d] memory fail! size=0x%x\n", sel, chno,
              (unsigned int)sizeof(struct __fce_reg_t));
        return -1;
    }

    fce_para_block[sel][chno].off = base;
    fce_para_block[sel][chno].val = memory;
    fce_para_block[sel][chno].size = 0x34;
    fce_para_block[sel][chno].dirty = 0;

    fce_celut_block[sel][chno].off = base + 0x100;
    fce_celut_block[sel][chno].val = memory + 0x100;
    fce_celut_block[sel][chno].size = 0x100;
    fce_celut_block[sel][chno].dirty = 0;

    fce_hist_block[sel][chno].off = base + 0x200;
    fce_hist_block[sel][chno].val = memory + 0x200;
    fce_hist_block[sel][chno].size = 0x400;
    fce_hist_block[sel][chno].dirty = 0;

    de_fce_set_reg_base(sel, chno, memory);

    /* hist */
    g_hist_status[sel][chno] =
        disp_sys_malloc(sizeof(struct __hist_status_t));
    if (g_hist_status[sel][chno] == NULL) {
        DE_WRN("disp_sys_malloc g_hist_status[%d][%d] memory fail! size=0x%x\n",
              sel, chno, (unsigned int)sizeof(struct __hist_status_t));
        return -1;
    }

    g_hist_status[sel][chno]->runtime = 0;
    g_hist_status[sel][chno]->isenable = 0;
    g_hist_status[sel][chno]->twohistready = 0;

    g_hist[sel][chno] = disp_sys_malloc(1024);
    if (g_hist[sel][chno] == NULL) {
        DE_WRN("disp_sys_malloc hist[%d][%d] memory fail! size=0x%x\n",
        sel, chno, 1024);
        return -1;
    }
    g_hist_p[sel][chno] = disp_sys_malloc(1024);
    if (g_hist_p[sel][chno] == NULL) {
        DE_WRN("disp_sys_malloc g_hist_p[%d][%d] memory fail! size=0x%x\n", sel,
              chno, 1024);
        return -1;
    }
    /* ce */
    g_ce_status[sel][chno] =
        disp_sys_malloc(sizeof(struct __ce_status_t));
    if (g_ce_status[sel][chno] == NULL) {
        DE_WRN("disp_sys_malloc g_ce_status[%d][%d] memory fail! size=0x%x\n",
              sel, chno, (unsigned int)sizeof(struct __ce_status_t));
        return -1;
    }

    g_ce_status[sel][chno]->isenable = 0;

    g_celut[sel][chno] = disp_sys_malloc(256);
    if (g_celut[sel][chno] == NULL) {
        DE_WRN("disp_sys_malloc celut[%d][%d] memory fail! size=0x%x\n",
              sel, chno, 256);
        return -1;
    }

    hist_res[sel][chno] =
        disp_sys_malloc(sizeof(struct hist_data));
    if (hist_res[sel][chno] == NULL) {
        DE_WRN("disp_sys_malloc hist_res[%d][%d] memory fail! size=0x%x\n", sel,
              chno, (unsigned int)sizeof(struct hist_data));
        return -1;
    }

    memset(hist_res[sel][chno], 0, sizeof(struct hist_data));

    return 0;
}

int de_fce_exit(unsigned int sel, unsigned int chno)
{
    disp_sys_free(fce_para_block[sel][chno].val);
    disp_sys_free(g_hist_status[sel][chno]);
    disp_sys_free(g_hist[sel][chno]);
    disp_sys_free(g_hist_p[sel][chno]);
    disp_sys_free(g_ce_status[sel][chno]);
    disp_sys_free(g_celut[sel][chno]);
    disp_sys_free(hist_res[sel][chno]);

    return 0;
}

/*******************************************************************************
 * function       : de_fce_enable(unsigned int sel, unsigned int chno,
 *                    unsigned int en)
 * description    : enable/disable fce
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  en          <enable: 0-disable; 1-enable>
 * return         :
 *                  success
 ******************************************************************************/
int de_fce_enable(unsigned int sel, unsigned int chno, unsigned int en)
{
    fce_dev[sel][chno]->ctrl.bits.en = en;
    /* must enable when BWS_EN == 1 or ASE_EN == 1 */
    fce_para_block[sel][chno].dirty = 1;

    return 0;
}

/*******************************************************************************
 * function       : de_fce_set_size(unsigned int sel, unsigned int chno,
 *                   unsigned int width, unsigned int height)
 * description    : set fce size
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  width       <input width>
 *                                      height  <input height>
 * return         :
 *                  success
 ******************************************************************************/
int de_fce_set_size(unsigned int sel, unsigned int chno, unsigned int width,
            unsigned int height)
{
    fce_dev[sel][chno]->size.bits.width = width - 1;
    fce_dev[sel][chno]->size.bits.height = height - 1;
    fce_para_block[sel][chno].dirty = 1;

    return 0;
}

/*******************************************************************************
 * function       : de_fce_set_window(unsigned int sel, unsigned int chno,
 *                     unsigned int win_enable, struct de_rect window)
 * description    : set fce window
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  win_enable  <enable: 0-window mode disable;
 *                                       1-window mode enable>
 *                  window  <window rectangle>
 * return         :
 *                  success
 ******************************************************************************/
int de_fce_set_window(unsigned int sel, unsigned int chno,
              unsigned int win_enable, struct de_rect window)
{
    fce_dev[sel][chno]->ctrl.bits.win_en = win_enable;

    if (win_enable) {
        fce_dev[sel][chno]->win0.bits.win_left = window.x;
        fce_dev[sel][chno]->win0.bits.win_top = window.y;
        fce_dev[sel][chno]->win1.bits.win_right =
            window.x + window.w - 1;
        fce_dev[sel][chno]->win1.bits.win_bot = window.y + window.h - 1;
    }
    fce_para_block[sel][chno].dirty = 1;

    return 0;
}

/*******************************************************************************
 * function       : de_fce_csc_en(unsigned int sel, unsigned int chno,
 *                  unsigned int csc_enable)
 * description    : set fce window
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  csc_enable  <enable: 0-csc disable; 1-csc enable>
 * return         :
 *                  success
 ******************************************************************************/
int de_fce_csc_en(unsigned int sel, unsigned int chno, unsigned int csc_enable)
{
    fce_dev[sel][chno]->cscbypass.bits.csc_bypass = csc_enable;
    fce_para_block[sel][chno].dirty = 1;

    return 0;
}

/*******************************************************************************
 * function       : de_fce_set_para(unsigned int sel, unsigned int chno,
 *                  unsigned int lce_en, unsigned int ftc_en,
 *                  unsigned int ce_en, unsigned int hist_en)
 * description    : set fce para
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  fce_para <fce parameters>
 * return         :
 *                  success
 ******************************************************************************/
int de_fce_set_para(unsigned int sel, unsigned int chno,
            struct __fce_config_data fce_para)
{
    fce_dev[sel][chno]->ctrl.bits.lce_en = fce_para.lce_en;
    fce_dev[sel][chno]->ctrl.bits.ftc_en = fce_para.ftc_en;
    fce_dev[sel][chno]->ctrl.bits.ce_en = fce_para.ce_en;
    fce_dev[sel][chno]->ctrl.bits.hist_en = fce_para.hist_en;

    fce_dev[sel][chno]->lcegain.bits.lce_gain = fce_para.lce_gain;
    fce_dev[sel][chno]->lcegain.bits.lce_blend = fce_para.lce_blend;
    fce_dev[sel][chno]->ftcgain.bits.ftc_gain1 = fce_para.ftc_gain1;
    fce_dev[sel][chno]->ftcgain.bits.ftc_gain2 = fce_para.ftc_gain2;
    fce_para_block[sel][chno].dirty = 1;

    return 0;
}

/*******************************************************************************
 * function       : de_fce_get_hist(unsigned int sel, unsigned int chno,
 *                  unsigned int hist[256], unsigned int *sum)
 * description    : get histogram result
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  hist[256]   <frame histogram>
 *                  sum             <frame pixel value sum>
 * return         :
 *                  success
 ******************************************************************************/
int de_fce_get_hist(unsigned int sel, unsigned int chno, unsigned int hist[256],
            unsigned int *sum)
{
    uintptr_t base;

    base = fce_hw_base[sel][chno];

    /* Read histogram to hist[256] */
    memcpy((unsigned char *)hist,
           (unsigned char *)fce_hist_block[sel][chno].off,
           sizeof(unsigned int) * 256);

    /* Read */
    *sum = readl((void  *)(base + 0x20));

    return 0;
}

/*******************************************************************************
 * function       : de_fce_set_ce(unsigned int sel, unsigned int chno,
 *                           unsigned int ce_lut[256])
 * description    : set ce lut, directly write to registers
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  ce_lut[256] <ce lut>
 * return         :
 *                  success
 ******************************************************************************/
int de_fce_set_ce(unsigned int sel, unsigned int chno,
          unsigned char ce_lut[256])
{
    memcpy(fce_celut_block[sel][chno].val, (unsigned char *)ce_lut,
           sizeof(unsigned char) * 256);
    fce_celut_block[sel][chno].dirty = 1;

    return 0;
}

/*******************************************************************************
 * function       : de_fce_info2para(unsigned int sharp,
 *                  unsigned int auto_contrast, unsigned int auto_color,
 *                  struct de_rect window, struct __fce_config_data *para)
 * description    : info->para conversion
 * parameters     :
 *                  sharp/auto_contrast/auto_color      <gain info from user>
 *                  window              <window info>
 *                  para                <bsp para>
 * return         :
 *                  success
 ******************************************************************************/
int de_fce_info2para(unsigned int sharp, unsigned int auto_contrast,
             unsigned int auto_color, struct de_rect window,
             struct __fce_config_data *para)
{
    int lce_mode, ce_mode, autoce_mode, ftc_mode;
    int lce_para[LCE_PARA_NUM][LCE_MODE_NUM] = {
        {0, 15},    /* gain */
        {0, 84},    /* blending */
    };
    /* int ce_para[CE_PARA_NUM][CE_MODE_NUM]; //FIXME */
    int auto_ce_para[AUTOCE_PARA_NUM][AUTOCE_MODE_NUM] = {
        {0, 15, 10},      /* stretch_precent_thr  */
        {0, 15, 10},      /* suppress_precent_thr */
        {0, 16, 8},     /* update_diff_thr      */
        {0, 384, 300},  /* slope_black_lmt      */
        {0, 384, 300},  /* slope_white_lmt      */
    };
    int ftc_para[FTC_PARA_NUM][FTC_MODE_NUM] = {
        {0, 10},    /* ftc_gain_1 */
        {0, 5},     /* ftc_gain_2 */
    };

    /* auto_contrast */
    lce_mode = (auto_contrast >> 16) & 0xf;
    ce_mode = auto_contrast & 0xf;
    autoce_mode = (auto_contrast >> 4) & 0xf;
    para->lce_en = lce_mode ? 1 : 0;
    para->ce_en = (auto_contrast & 0xff) ? 1 : 0;
    para->b_automode = autoce_mode ? 1 : 0;
    para->hist_en = autoce_mode ? 1 : 0;

    para->lce_gain = lce_para[0][lce_mode];
    para->lce_blend = lce_para[1][lce_mode];

    para->up_precent_thr = auto_ce_para[0][autoce_mode];
    para->down_precent_thr = auto_ce_para[1][autoce_mode];
    para->update_diff_thr = auto_ce_para[2][autoce_mode];
    para->slope_black_lmt = auto_ce_para[3][autoce_mode];
    para->slope_white_lmt = auto_ce_para[4][autoce_mode];

    /* auto_color */
    ftc_mode = auto_color & 0xf;
    para->ftc_en = ftc_mode ? 1 : 0;

    para->ftc_gain1 = ftc_para[0][ftc_mode];
    para->ftc_gain2 = ftc_para[1][ftc_mode];

    /* fce */
    para->fce_en =
        (para->lce_en | para->ce_en | para->hist_en | para->ftc_en) ? 1 : 0;

    return 0;
}

static int toupdate(int hist_mean, int hist_diff, int diff_coeff,
            int change_thr)
{
    int toupdate = 0;
    int diff_div = 1;

    if (hist_diff < 0)
        diff_div = 2;
    else
        diff_div = 1;

    if (hist_mean > 96)
        change_thr = 3 * change_thr / diff_div;
    if (hist_mean > 64)
        change_thr = 2 * change_thr / diff_div;
    else
        change_thr = change_thr / diff_div;

    hist_diff = abs(hist_diff);

    if (hist_diff > change_thr ||
        (diff_coeff > 100 && hist_diff > change_thr / 8) ||
        (diff_coeff > 64 && hist_diff > change_thr / 4) ||
        (diff_coeff > 32 && hist_diff > change_thr / 2)) {
        toupdate = 1;
    } else
        toupdate = 0;

    return toupdate;
}

/*******************************************************************************
 * function       :auto_ce_model(unsigned int width, unsigned height,
 *                 unsigned int sumcnt, unsigned int hist[256],
 *                 unsigned int up_precent_thr, unsigned int down_precent_thr,
 *                 unsigned char celut[256])
 * description    : Auto-ce Alg
 * parameters     :
 *                  width               <layer width>
 *                  height              <layer height>
 *                  hist[256]   <the latest frame histogram>
 *                  sumcnt       <the latest frame pixel value sum>
 *                  up_precent_thr/down_precent_thr <ce para>
 *                  celut <auto-ce result>
 * return         :
 ******************************************************************************/
static void
auto_ce_model(unsigned int width, unsigned height,
        unsigned int sumcnt, unsigned int hist[256],
        unsigned int up_precent_thr,
        unsigned int down_precent_thr,
        unsigned int change_thr, unsigned int lowest_black,
        unsigned int highest_white, unsigned int ce_thr,
        unsigned char celut[256], struct hist_data *p_hist_data)
{
    static u32 hist_r[256], p[256];
    u32 i;
    u32 mean;
    u32 total_pixel, total_pixel_r, total_size;
    s32 uthr, lthr;
    u32 rate, half;
    int tmp;
    unsigned int black_str_lv;
    unsigned int white_str_lv;

    if (height % 2 == 0) {
        total_size = total_pixel = (width * height) >> 1;
    } else {
        total_size = total_pixel = (width * (height - 1)
            + (width + 1)) >> 1;
    }

    for (i = 0; i < lowest_black; i++)
        total_pixel -= hist[i];

    for (i = highest_white; i < 256; i++)
        total_pixel -= hist[i];

    /* less than 66% pixel in valid range */
    if (total_size > 3 * total_pixel)
        total_size = 0;

    total_pixel_r = 0;

    /* MEAN */
    mean = total_pixel / (highest_white - lowest_black);

    /* picture too small, can't ce */
    if ((mean == 0) || (p_hist_data->hist_mean < ce_thr)
      || total_size == 0) {
        for (i = 0; i < 256; i++)
            celut[i] = i;
    } else {
        int black_thr;

        uthr = mean + mean * up_precent_thr / 100;
        lthr = mean - mean * down_precent_thr / 100;

        black_thr = lthr;
        white_str_lv = lthr * 1 / 3;

        if (p_hist_data->hist_mean > 96)
            black_str_lv = black_thr;
        else if (p_hist_data->hist_mean > 64)
            black_str_lv = black_thr * 2 / 3;
        else if (p_hist_data->hist_mean < 21)
            black_str_lv = black_thr * 1 / 3;
        else
            black_str_lv = black_thr * 1 / 3
                + (p_hist_data->hist_mean * black_thr / (64 * 3));

        /* generate p */
        if (hist[lowest_black] > mean)
            hist_r[lowest_black] = mean;
        else if (hist[lowest_black] > black_str_lv)
            hist_r[lowest_black] = hist[lowest_black];
        else
            hist_r[lowest_black] = black_str_lv;

        total_pixel_r = hist_r[lowest_black];
        p[lowest_black] = hist_r[lowest_black];

        /* black zone */
        for (i = lowest_black + 1; i < p_hist_data->black_thr0; i++) {
            if (hist[i] > mean)
                hist_r[i] = mean;
            else if (hist[i] > black_str_lv)
                hist_r[i] = hist[i];
            else
                hist_r[i] = black_str_lv;

            total_pixel_r = total_pixel_r + hist_r[i];
            p[i] = p[i - 1] + hist_r[i];
        }

        for (i = p_hist_data->black_thr0; i < p_hist_data->black_thr1;
             i++) {
            if (hist[i] > mean)
                hist_r[i] = mean;
            else if (hist[i] > lthr)
                hist_r[i] = hist[i];
            else
                hist_r[i] = lthr;

            total_pixel_r = total_pixel_r + hist_r[i];
            p[i] = p[i - 1] + hist_r[i];
        }

        if (p_hist_data->white_thr0 >= 256) {
            DE_WRN("p_hist_data->white_thr0(%d) >= 256",
                  p_hist_data->white_thr0);
            p_hist_data->white_thr0 = 255;
        }
        for (i = p_hist_data->black_thr1; i < p_hist_data->white_thr0;
             i++) {
            if (hist[i] > uthr)
                hist_r[i] = uthr;
            else if (hist[i] > lthr)
                hist_r[i] = hist[i];
            else
                hist_r[i] = lthr;

            total_pixel_r = total_pixel_r + hist_r[i];
            p[i] = p[i - 1] + hist_r[i];
        }

        /* white zone */
        for (i = p_hist_data->white_thr0; i < p_hist_data->white_thr1;
             i++) {
            if (hist[i] > uthr)
                hist_r[i] = uthr;
            else if (hist[i] > white_str_lv)
                hist_r[i] = hist[i];
            else
                hist_r[i] = lthr;

            total_pixel_r = total_pixel_r + hist_r[i];
            p[i] = p[i - 1] + hist_r[i];
        }
        for (i = p_hist_data->white_thr1; i < highest_white; i++) {
            if (hist[i] > uthr)
                hist_r[i] = uthr;
            else if (hist[i] > white_str_lv)
                hist_r[i] = hist[i];
            else
                hist_r[i] = white_str_lv;

            total_pixel_r = total_pixel_r + hist_r[i];
            p[i] = p[i - 1] + hist_r[i];
        }
        if (total_pixel_r != 0) {
            rate =
                (total_pixel * (highest_white - lowest_black))
                / total_pixel_r;
            half = rate >> 1;
        } else {
            pr_warn("auto_ce_model : total_pixel_r == 0.\n");
            rate = highest_white - lowest_black;
            half = rate >> 1;
        }
        tmp =
            toupdate(p_hist_data->hist_mean,
                 p_hist_data->hist_mean_diff,
                 p_hist_data->diff_coeff, change_thr);

        if (tmp) {
            for (i = lowest_black; i < highest_white; i++) {
                tmp = (p[i] * rate + half) / total_pixel
                    + lowest_black;
                if (tmp >= highest_white)
                    tmp = highest_white - 1;

                celut[i] = (unsigned char)tmp;

            }

            for (i = 0; i < lowest_black; i++)
                celut[i] = i;
            for (i = highest_white; i < 256; i++)
                celut[i] = i;

        }
    }
}

/*******************************************************************************
 * function       : auto_bws_model(unsigned int width, unsigned int height,
 *                  unsigned int hist[256], unsigned int sum,
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
 *                  sum                     <the latest frame pixel value sum>
 *                  pre_slope_black/pre_slope_white
 *                         <the frame before the latest frame auto-bws result>
 *                  ymin/black/white/ymax/shope0/1/2/3 <auto-bws result>
 * return         :
 *
 ******************************************************************************/
/*
 * R_ROPC_EN--frame_bld_en--1
 * R_ROPC_TH_UPPER--bld_high_thr--90
 * R_ROPC_TH_LOWER--bld_low_thr--74
 * R_ROPC_WEIGHT_MIN--bld_weight_lmt--8
 * R_PRESET_TILT_BLACK--present_black--53
 * R_PRESET_TILT_WHITE--present_white--235
 * R_SLOPE_LIMIT_BLACK--slope_black_lmt--512
 * R_SLOPE_LIMIT_WHITE--slope_white_lmt--384
 * R_BLACK_PERCENT--black_prec--5
 * R_WHITE_PERCENT--white_prec--2
 * R_LOWEST_BLACK--lowest_black--3
 * R_HIGHEST_WHITE--highest_white--252
 */
static void auto_bws_model(unsigned int width, unsigned int height,
        unsigned int hist[256], unsigned int hist_pre[256],
        unsigned int sum,
        unsigned int pre_slope_black, unsigned int pre_slope_white,
        unsigned int frame_bld_en, unsigned int bld_high_thr,
        unsigned int bld_low_thr, unsigned int bld_weight_lmt,
        unsigned int present_black, unsigned int present_white,
        unsigned int slope_black_lmt, unsigned int slope_white_lmt,
        unsigned int black_prec, unsigned int white_prec,
        unsigned int lowest_black, unsigned int highest_white,
        struct hist_data *p_hist_data)
{
    int total, k;
    int validcnt, validsum;
    int ratio_b, ratio_w, cdf_b, cdf_w;
    int mean;
    int pd_ymin = lowest_black, pd_ymax = highest_white;
    int pd_black, pd_white;
    int pd_ymin_fix, pd_ymax_fix;
    int pd_s0, pd_s1, pd_s2, pd_s3;
    int tmp;
    int i = 0;

    int coeff, diff_hist = 0;

    total = 0;
    for (k = 0; k < 256; k++) {
        diff_hist += abs(hist[k] - hist_pre[k]);
        total += hist[k];
    }
    if (total == 0) {
        if (diff_hist == 0)
            coeff = 0;
        else
            coeff = 200;
    } else
        coeff = (100 * diff_hist) / total;
    p_hist_data->diff_coeff = coeff;

    /* 2.kick out the lowest black and the highest white in hist and sum */
    validsum = sum;
    for (k = 0; k < lowest_black; k++) {
        if (validsum < hist[k] * k)
            break;

        validsum -= hist[k] * k;
    }
    for (k = 255; k > highest_white - 1; k--) {
        if (validsum < hist[k] * k)
            break;

        validsum -= hist[k] * k;
    }

    validcnt = total;
    for (k = 0; k < lowest_black; k++)
        validcnt -= hist[k];

    if (validcnt == 0)
        mean = lowest_black;
    else {
        for (k = 255; k > highest_white - 1; k--)
            validcnt -= hist[k];

        if (validcnt == 0)
            mean = highest_white;
        else
            mean = validsum / validcnt;
    }

    if (validcnt != 0) {
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

        /* bright */
        if (p_hist_data->hist_mean <= 16) {
            /*slope_black_lmt = slope_black_lmt;*/
        } else {
            int step = slope_black_lmt - 256;

            if (step < 0)
                step = 0;

            slope_black_lmt = slope_black_lmt
                - (p_hist_data->hist_mean) * step / (5 * 16);

            if (slope_black_lmt < 256)
                slope_black_lmt = 256;
        }

        /* 4.limit black and white don't cross mean */
        pd_black = (present_black < mean * 3 / 2) ?
            present_black : mean * 3 / 2;
        pd_white = (present_white > mean) ? present_white : mean;

        /* 5.calculate slope1/2
         * and limit to slope_black_lmt or slope_white_lmt
         */
        pd_s1 = (pd_ymin < pd_black) ?
            ((pd_black << 8) / (pd_black - pd_ymin)) : 256;

        pd_s1 = (pd_s1 > slope_black_lmt) ? slope_black_lmt : pd_s1;

        pd_s2 = (pd_ymax > pd_white) ?
            (((255 - pd_white) << 8) / (pd_ymax - pd_white)) : 256;
        pd_s2 = (pd_s2 > slope_white_lmt) ? slope_white_lmt : pd_s2;

        tmp = pd_black + ((pd_s1 * (pd_ymin - pd_black) + 128) >> 8);
        /* 7.calculate slope0/3 and re-calculate ymin and ymax */
        if ((tmp > 0) && (pd_ymin < pd_black) && (pd_ymin > 0)) {
            pd_s0 = ((tmp << 8) + 128) / pd_ymin;
            pd_ymin_fix = pd_ymin;
        } else if (pd_ymin >= pd_black) {
            pd_s0 = 256;
            pd_ymin_fix = 16;
          /* do noting use s0 */
        } else {
            pd_s0 = 0;
            pd_ymin_fix =
                -((pd_black << 8) - 128) / pd_s1 + pd_black;
        }

        if (pd_s0 == 0)
            pd_s1 = 256 * pd_black / (pd_black - pd_ymin_fix);

        if (pd_s1 == 256)
            pd_s0 = 256;

        tmp = pd_white + ((pd_s2 * (pd_ymax - pd_white)) >> 8);
        if ((tmp < 255) && (pd_ymax > pd_white) && (pd_ymax < 255)) {
            pd_s3 = (((255 - tmp) << 8) + 128) / (255 - pd_ymax);
            pd_ymax_fix = pd_ymax;
        } else if (pd_ymax <= pd_white) {
            pd_s3 = 256;
            pd_ymax_fix = 255;
          /* do noting use s3 */
        } else {
            pd_s3 = 0;
            pd_ymax_fix =
                (((255 - pd_white) << 8) - 128) / pd_s2 + pd_white;
        }

        if (pd_s3 == 256)
            pd_s2 = 256;
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

    if (mean < 0 || pd_ymin_fix < 0 || pd_black < 0 || pd_white > 255
        || pd_white < 0 || pd_ymax_fix < 0 || pd_ymax_fix > 255) {
        mean = 0;
        pd_ymin_fix = 16;
        pd_black = 32;
        pd_white = 224;
        pd_ymax_fix = 240;
        pd_s0 = 0x100;
        pd_s1 = 0x100;
        pd_s2 = 0x100;
        pd_s3 = 0x100;
    }

    p_hist_data->old_hist_mean = p_hist_data->hist_mean;
    p_hist_data->hist_mean = mean;  /* add by zly 2014-8-19 16:12:14 */

    p_hist_data->avg_mean_saved[p_hist_data->avg_mean_idx] = mean;
    p_hist_data->avg_mean_idx++;
    if (p_hist_data->avg_mean_idx == AVG_NUM)
        p_hist_data->avg_mean_idx = 0;

    p_hist_data->avg_mean = 0;
    for (i = 0; i < AVG_NUM; i++)
        p_hist_data->avg_mean += p_hist_data->avg_mean_saved[i];

    p_hist_data->avg_mean = p_hist_data->avg_mean / AVG_NUM;

    p_hist_data->hist_mean_diff =
        (int)p_hist_data->avg_mean - (int)p_hist_data->hist_mean;

    /* cal th */
    p_hist_data->black_thr0 = pd_ymin_fix;
    p_hist_data->black_thr1 = pd_black;
    p_hist_data->white_thr0 = pd_white;
    p_hist_data->white_thr1 = pd_ymax_fix;
    p_hist_data->black_slp0 = pd_s0;
    p_hist_data->black_slp1 = pd_s1;
    p_hist_data->white_slp0 = pd_s2;
    p_hist_data->white_slp1 = pd_s3;
}

int de_hist_apply(unsigned int screen_id, unsigned int chno,
          unsigned int hist_en, unsigned int auto_contrast_dirty)
{
    if (hist_en == 1 && auto_contrast_dirty) {
        /*
         * enable this time
         * reset hist buffer
         */
        memset((unsigned char *)g_hist[screen_id][chno], 0, 1024);

        g_hist_status[screen_id][chno]->runtime = 0;
        g_hist_status[screen_id][chno]->twohistready = 0;
        g_hist_status[screen_id][chno]->isenable = 1;
    } else if (hist_en == 0 && auto_contrast_dirty) {
        /* disable this time */
        g_hist_status[screen_id][chno]->runtime = 0;
        g_hist_status[screen_id][chno]->twohistready = 0;
        g_hist_status[screen_id][chno]->isenable = 0;
    }

    return 0;
}

int de_hist_tasklet(unsigned int screen_id, unsigned int chno,
            unsigned int frame_cnt)
{
    if ((g_hist_status[screen_id][chno]->isenable)
        && ((HIST_FRAME_MASK == (frame_cnt % 2))
        || (HIST_FRAME_MASK == 0x2))) {
        memcpy((unsigned char *)g_hist_p[screen_id][chno],
               (unsigned char *)g_hist[screen_id][chno], 1024);
        de_fce_get_hist(screen_id, chno, g_hist[screen_id][chno],
                &g_sum[screen_id][chno]);

        if (g_hist_status[screen_id][chno]->runtime < 2)
            g_hist_status[screen_id][chno]->runtime++;
        else
            g_hist_status[screen_id][chno]->twohistready = 1;
    }
    return 0;

}

int de_ce_apply(unsigned int screen_id, unsigned int chno, unsigned int ce_en,
        unsigned int b_automode, unsigned int up_precent_thr,
        unsigned int down_precent_thr, unsigned int update_diff_thr,
        unsigned int black_slope_lmt, unsigned int white_slope_lmt,
        unsigned int auto_contrast_dirty)
{
    if (ce_en == 1 && auto_contrast_dirty) {
        /* enable this time */
        g_ce_status[screen_id][chno]->isenable = 1;
        g_ce_status[screen_id][chno]->b_automode = b_automode;

        if (b_automode) {
            g_ce_status[screen_id][chno]->up_precent_thr =
                up_precent_thr;
            g_ce_status[screen_id][chno]->down_precent_thr =
                down_precent_thr;
            g_ce_status[screen_id][chno]->update_diff_thr =
                update_diff_thr;
            g_ce_status[screen_id][chno]->slope_black_lmt =
                black_slope_lmt;
            g_ce_status[screen_id][chno]->slope_white_lmt =
                white_slope_lmt;

            memset(hist_res[screen_id][chno], 0,
                sizeof(struct hist_data));
            /* clear hist data when disable */

            /* set bypass lut first */
            memcpy((void *)g_celut[screen_id][chno],
                   (void *)ce_bypass_lut, 256);
        } else {
            memcpy((void *)g_celut[screen_id][chno],
                   (void *)ce_constant_lut, 256);
        }

        de_fce_set_ce(screen_id, chno, g_celut[screen_id][chno]);

    } else if (ce_en == 0 && auto_contrast_dirty) {
        /* disable this time */
        g_ce_status[screen_id][chno]->isenable = 0;

    }

    return 0;

}

int de_ce_tasklet(unsigned int screen_id, unsigned int chno,
          unsigned int frame_cnt)
{
    unsigned int percent_black, percent_white;
    unsigned int lowest_black, highest_white, autoce_thr;

    percent_black = 5;
    percent_white = 4;
    lowest_black = 4;
    highest_white = 252;
    autoce_thr = 21;

    if (g_ce_status[screen_id][chno]->isenable
        && g_ce_status[screen_id][chno]->b_automode
        && ((CE_FRAME_MASK == (frame_cnt % 2)) || (CE_FRAME_MASK == 0x2))) {
        if (g_hist_status[screen_id][chno]->twohistready) {
            auto_bws_model(g_ce_status[screen_id][chno]->width,
                       g_ce_status[screen_id][chno]->height,
                       g_hist[screen_id][chno],
                       g_hist_p[screen_id][chno],
                       g_sum[screen_id][chno], 256, 256, 1, 90,
                       74, 8, 53, 235,
                       g_ce_status[screen_id][chno]->
                       slope_black_lmt,
                       g_ce_status[screen_id][chno]->
                       slope_white_lmt, percent_black,
                       percent_white, lowest_black,
                       highest_white,
                       hist_res[screen_id][chno]);

            auto_ce_model(g_ce_status[screen_id][chno]->width,
                      g_ce_status[screen_id][chno]->height,
                      g_sum[screen_id][chno],
                      g_hist[screen_id][chno],
                      g_ce_status[screen_id][chno]->
                      up_precent_thr,
                      g_ce_status[screen_id][chno]->
                      down_precent_thr,
                      g_ce_status[screen_id][chno]->
                      update_diff_thr, lowest_black,
                      highest_white, autoce_thr,
                      g_celut[screen_id][chno],
                      hist_res[screen_id][chno]);
        } else {
            memcpy((void *)g_celut[screen_id][chno],
                   (void *)ce_bypass_lut, 256);
        }
        de_fce_set_ce(screen_id, chno, g_celut[screen_id][chno]);
    }

    return 0;
}
#endif
