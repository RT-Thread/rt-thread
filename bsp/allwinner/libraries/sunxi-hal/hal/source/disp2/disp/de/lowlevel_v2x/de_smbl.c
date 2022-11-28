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
 *  File name   :       de_smbl.c
 *
 *  Description :       display engine 2.0 smbl basic function definition
 *
 *  History     :       2014/05/13  vito cheng  v0.1  Initial version
 *
 */
#include "de_feat.h"
#include "de_smbl_type.h"
#include "de_smbl.h"
#include "de_rtmx.h"

#if defined(SUPPORT_SMBL)

#include "de_smbl_tab.h"
/* SMBL offset based on RTMX */
#define SMBL_OFST   0xB0000

static volatile struct __smbl_reg_t *smbl_dev[DE_NUM];
static struct de_reg_blocks smbl_enable_block[DE_NUM];
static struct de_reg_blocks smbl_ctrl_block[DE_NUM];
static struct de_reg_blocks smbl_hist_block[DE_NUM];
static struct de_reg_blocks smbl_csc_block[DE_NUM];
static struct de_reg_blocks smbl_filter_block[DE_NUM];
static struct de_reg_blocks smbl_lut_block[DE_NUM];

static struct __smbl_status_t *g_smbl_status[DE_NUM];
static unsigned int smbl_frame_cnt[DE_NUM] = { 0 };
/* POINTER of LGC tab */
static unsigned short *pttab[DE_NUM];

static uintptr_t smbl_hw_base[DE_NUM] = { 0 };
/* when bsp_disp_lcd_get_bright() exceed PWRSAVE_PROC_THRES, STOP PWRSAVE */
static u32 PWRSAVE_PROC_THRES = 85;

/*
 *  typedef enum
 *  {
 *      SMBL_DIRTY_ENABLE    = 0x00000001,
 *      SMBL_DIRTY_WINDOW    = 0x00000002,
 *      SMBL_DIRTY_SIZE      = 0x00000004,
 *      SMBL_DIRTY_BL        = 0x00000008,
 *      SMBL_DIRTY_ALL       = 0x0000000F,
 *  }disp_smbl_dirty_flags;
 *
 *  typedef struct disp_smbl_info {
 *      u32 enable;
 *      u32 window; //effect rectangle
 *      struct de_rectz size;   //display size
 *      u32 bl;     //backlight
 *      disp_smbl_dirty_flags flags;
 *  };
*/

/**
 *  function       : PWRSAVE_CORE(unsigned int sel)
 *
 *  description    : Power Save alg core
 *           Dynamic adjust backlight and lgc gain through screen
 *           content and user backlight setting
 *  parameters     :
 *          sel         <screen index>
 *  return         :
 *          lgcaddr     <LGC table pointer>
 *  history        :
 *          Add HANG-UP DETECT: When use PWRSAVE_CORE in LOW
 *          referential backlight condiction, backlight will
 *          flicker. So STOP use PWRSAVE_CORE.
 */
static unsigned short *PWRSAVE_CORE(u32 sel)
{
    s32 i;
    u32 hist_region_num = 8;
    u32 histcnt[IEP_LH_INTERVAL_NUM];
    u32 hist[IEP_LH_INTERVAL_NUM], p95;
    u32 size = 0;
    u32 min_adj_index;
    unsigned short *lgcaddr;
    u32 drc_filter_tmp = 0;
    u32 backlight, thres_low, thres_high;
    static u32 printf_cnt;

    printf_cnt = 0;
    backlight = g_smbl_status[sel]->backlight;

    if (backlight < PWRSAVE_PROC_THRES) {
        /* if current backlight lt PWRSAVE_PROC_THRES, close smart */
        /* backlight function */
        memset(g_smbl_status[sel]->min_adj_index_hist, 255,
               sizeof(u8) * IEP_LH_PWRSV_NUM);
        lgcaddr = (unsigned short *)((uintptr_t) pttab[sel] +
              ((128 - 1) << 9));

        g_smbl_status[sel]->dimming = 256;
    } else {
        /* if current backlight ge PWRSAVE_PROC_THRES, */
        /* open smart backlight function */
        p95 = 0;

        hist_region_num =
               (hist_region_num > 8) ? 8 : IEP_LH_INTERVAL_NUM;

        /* read histogram result */
        de_smbl_get_hist(sel, histcnt);

        /*for (i=0; i<IEP_LH_INTERVAL_NUM; i++) {
         *      size += histcnt[i];
         *}
         *size = (size==0) ? 1 : size;
         *
         *calculate some var
         *hist[0] = (histcnt[0]*100)/size;
         *for (i = 1; i < hist_region_num; i++) {
         *      hist[i] = (histcnt[i]*100)/size + hist[i-1];
         *}
         */
        size = g_smbl_status[sel]->size;

        /* calculate some var */
        hist[0] = (histcnt[0]) / size;
        for (i = 1; i < hist_region_num; i++)
            hist[i] = (histcnt[i]) / size + hist[i - 1];

#if 0
        for (i = 0; i < hist_region_num; i++)
            if (hist[i] >= 95) {
                p95 = hist_thres_pwrsv[i];
                break;
            }

        /* sometime, hist[hist_region_num - 1] may less than 95 */
        /* due to integer calc */
        if (i == hist_region_num)
            p95 = hist_thres_pwrsv[7];

#else       /* fix bug of some thing bright appear in a dark background */
        for (i = hist_region_num - 1; i >= 0; i--)
            if (hist[i] < 80)
                break;

        /* sometime, hist[hist_region_num - 1] may less than 95 */
        /* due to integer calc */
        if (i == hist_region_num - 1)
            p95 = hist_thres_pwrsv[7];
        else if (i == 0)
            p95 = hist_thres_pwrsv[0];
        else
            p95 = hist_thres_pwrsv[i + 1];
#endif
        min_adj_index = p95;

        /* DE_INF("min_adj_index: %d\n", min_adj_index); */
        for (i = 0; i < IEP_LH_PWRSV_NUM - 1; i++) {
            g_smbl_status[sel]->min_adj_index_hist[i] =
                g_smbl_status[sel]->min_adj_index_hist[i + 1];
        }
        g_smbl_status[sel]->min_adj_index_hist[IEP_LH_PWRSV_NUM - 1] =
            min_adj_index;

        for (i = 0; i < IEP_LH_PWRSV_NUM; i++) {
            /* drc_filter_total += drc_filter[i]; */
            drc_filter_tmp +=
                drc_filter[i] *
                g_smbl_status[sel]->min_adj_index_hist[i];
        }
        /* min_adj_index = drc_filter_tmp/drc_filter_total; */
        min_adj_index = drc_filter_tmp >> 10;

        thres_low = PWRSAVE_PROC_THRES;
        thres_high =
            PWRSAVE_PROC_THRES + ((255 - PWRSAVE_PROC_THRES) / 5);
        if (backlight < thres_high) {
            min_adj_index =
               min_adj_index + (255 - min_adj_index) *
               (thres_high - backlight) / (thres_high - thres_low);
        }
        min_adj_index =
            (min_adj_index >= 255) ?
            255 : ((min_adj_index < hist_thres_pwrsv[0]) ?
            hist_thres_pwrsv[0] : min_adj_index);

        g_smbl_status[sel]->dimming = min_adj_index + 1;

        lgcaddr =
            (unsigned short *)((uintptr_t) pttab[sel] +
                    ((min_adj_index - 128) << 9));

        if (printf_cnt == 600) {
            DE_INF("save backlight power: %d percent\n",
                  (256 - (u32) min_adj_index) * 100 / 256);
            printf_cnt = 0;
        } else {
            printf_cnt++;
        }

    }
    return lgcaddr;
}

int de_smbl_tasklet(unsigned int sel)
{
    unsigned short *lut;

    if (g_smbl_status[sel]->isenable
        && ((SMBL_FRAME_MASK == (smbl_frame_cnt[sel] % 2))
        || (SMBL_FRAME_MASK == 0x2))) {
        if (g_smbl_status[sel]->runtime > 0) {
            /* POWER SAVE ALG */
            lut = (unsigned short *)PWRSAVE_CORE(sel);
        } else {
            lut = (unsigned short *)pwrsv_lgc_tab[128 - 1];
        }

        de_smbl_set_lut(sel, lut);

        if (g_smbl_status[sel]->runtime == 0)
            g_smbl_status[sel]->runtime++;
    }
    smbl_frame_cnt[sel]++;

    return 0;
}

int de_smbl_apply(unsigned int sel, struct disp_smbl_info *info)
{
    DE_INF("sel%d, en=%d, win=<%d,%d,%d,%d>\n", sel, info->enable,
          info->window.x, info->window.y, info->window.width,
          info->window.height);
    g_smbl_status[sel]->backlight = info->backlight;
    if (info->flags & SMBL_DIRTY_ENABLE) {
        g_smbl_status[sel]->isenable = info->enable;
        de_smbl_enable(sel, g_smbl_status[sel]->isenable);

        if (g_smbl_status[sel]->isenable) {
            g_smbl_status[sel]->runtime = 0;
            memset(g_smbl_status[sel]->min_adj_index_hist, 255,
                   sizeof(u8) * IEP_LH_PWRSV_NUM);
            de_smbl_set_para(sel, info->size.width,
                     info->size.height);
        } else {
        }
    }
    g_smbl_status[sel]->backlight = info->backlight;

    if (info->flags & SMBL_DIRTY_WINDOW)
        de_smbl_set_window(sel, 1, info->window);

    return 0;

}

int de_smbl_update_regs(unsigned int sel)
{
    unsigned int reg_val;

    if (smbl_ctrl_block[sel].dirty == 0x1) {
        regwrite((void *)smbl_ctrl_block[sel].off,
               smbl_ctrl_block[sel].val, smbl_ctrl_block[sel].size);
        smbl_ctrl_block[sel].dirty = 0x0;
    }

    if (smbl_enable_block[sel].dirty == 0x1) {
        reg_val = readl((void  *)(smbl_enable_block[sel].off));
        reg_val &= 0x2;
        reg_val |= *((volatile u32 *)smbl_enable_block[sel].val);
        writel(reg_val, (void  *)(smbl_enable_block[sel].off));
        smbl_enable_block[sel].dirty = 0;
    }
    return 0;
}

int de_smbl_set_reg_base(unsigned int sel, void *base)
{
    smbl_dev[sel] = (struct __smbl_reg_t *) base;

    return 0;
}

int de_smbl_init(unsigned int sel, uintptr_t reg_base)
{
    uintptr_t base;
    void *memory;
    unsigned int lcdgamma;
    int value = 1;
    char primary_key[20];
    int ret;

    base = reg_base + (sel + 1) * 0x00100000 + SMBL_OFST;
#if defined(CONFIG_ARCH_SUN50IW10)
    if (sel)
        base = base - 0x00100000;
#endif
    smbl_hw_base[sel] = base;

    DE_INF("sel %d, smbl_base=0x%p\n", sel, (void *)base);

    memory = disp_sys_malloc(sizeof(struct __smbl_reg_t));
    if (memory == NULL) {
        DE_WRN("disp_sys_malloc smbl[%d] memory fail! size=0x%x\n", sel,
              (unsigned int)sizeof(struct __smbl_reg_t));
        return -1;
    }

    smbl_enable_block[sel].off = base;
    smbl_enable_block[sel].val = memory;
    smbl_enable_block[sel].size = 0x4;
    smbl_enable_block[sel].dirty = 0;

    smbl_ctrl_block[sel].off = base + 0x4;
    smbl_ctrl_block[sel].val = memory + 0x4;
    smbl_ctrl_block[sel].size = 0x38;
    smbl_ctrl_block[sel].dirty = 0;

    smbl_hist_block[sel].off = base + 0x60;
    smbl_hist_block[sel].val = memory + 0x60;
    smbl_hist_block[sel].size = 0x20;
    smbl_hist_block[sel].dirty = 0;

    smbl_csc_block[sel].off = base + 0xc0;
    smbl_csc_block[sel].val = memory + 0xc0;
    smbl_csc_block[sel].size = 0x30;
    smbl_csc_block[sel].dirty = 0;

    smbl_filter_block[sel].off = base + 0xf0;
    smbl_filter_block[sel].val = memory + 0xf0;
    smbl_filter_block[sel].size = 0x110;
    smbl_filter_block[sel].dirty = 0;

    smbl_lut_block[sel].off = base + 0x200;
    smbl_lut_block[sel].val = memory + 0x200;
    smbl_lut_block[sel].size = 0x200;
    smbl_lut_block[sel].dirty = 0;

    de_smbl_set_reg_base(sel, memory);

    g_smbl_status[sel] = disp_sys_malloc(sizeof(struct __smbl_status_t));
    if (g_smbl_status[sel] == NULL) {
        DE_WRN("disp_sys_malloc g_smbl_status[%d] memory fail! size=0x%x\n", sel,
              (unsigned int)sizeof(struct __smbl_status_t));
        return -1;
    }

    g_smbl_status[sel]->isenable = 0;
    g_smbl_status[sel]->runtime = 0;
    g_smbl_status[sel]->dimming = 256;

    sprintf(primary_key, "lcd%d", sel);

    ret = disp_sys_script_get_item(primary_key, "lcdgamma4iep", &value, 1);
    if (ret != 1) {
        /* default gamma = 2.2 */
        lcdgamma = 6;
    } else {
        /* DE_INF("lcdgamma4iep for lcd%d = %d.\n", sel, value); */
        if (value > 30 || value < 10) {
            /* DE_WRN("lcdgamma4iep for lcd%d too small or too
             * large. default value 22 will be set. please set it
             * between 10 and 30 to make it valid.\n",sel);
             */
            lcdgamma = 6;
        } else {
            lcdgamma = (value - 10) / 2;
        }
    }

    pttab[sel] = pwrsv_lgc_tab[128 * lcdgamma];

    ret =
        disp_sys_script_get_item(primary_key, "smartbl_low_limit", &value,
                     1);
    if (ret != 1) {
        /* DE_INF("smartbl_low_limit for lcd%d not exist.\n", sel); */
    } else {
        /* DE_INF("smartbl_low_limit for lcd%d = %d.\n", sel, value); */
        if (value > 255 || value < 20)
            DE_INF("smartbl_low_limit of lcd%d must be in<20,255>\n",
                sel);
        else
            PWRSAVE_PROC_THRES = value;
    }
    sprintf(primary_key, "lcd%d", sel);
    ret = disp_sys_script_get_item(primary_key, "lcd_backlight", &value, 1);
    if (ret == 1)
        g_smbl_status[sel]->backlight = value;

    return 0;
}

int de_smbl_exit(unsigned int sel)
{
    disp_sys_free(smbl_enable_block[sel].val);
    disp_sys_free(g_smbl_status[sel]);

    return 0;
}


/**
 *  function       : de_smbl_enable(unsigned int sel, unsigned int en)
 *  description    : enable/disable smbl
 *  parameters     :
 *                   sel         <rtmx select>
 *                   en          <enable: 0-disable; 1-enable>
 *  return         :
 *                   success
 */
int de_smbl_enable(unsigned int sel, unsigned int en)
{
    smbl_dev[sel]->gnectl.bits.en = en;
    smbl_enable_block[sel].dirty = 1;
    return 0;
}

/**
 *  function       : de_smbl_set_window(unsigned int sel,
 *                      unsigned int win_enable,
 *                      struct de_rect window)
 *  description    : set smbl window
 *  parameters     :
 *                   sel         <rtmx select>
 *                   win_enable  <enable: 0-window mode disable;
 *                                        1-window mode enable>
 *                   window      <window rectangle>
 *  return         :
 *                   success
 */
int de_smbl_set_window(unsigned int sel, unsigned int win_enable,
            struct disp_rect window)
{
    smbl_dev[sel]->drcctl.bits.win_en = win_enable;

    if (win_enable) {
        smbl_dev[sel]->drc_wp0.bits.win_left = window.x;
        smbl_dev[sel]->drc_wp0.bits.win_top = window.y;
        smbl_dev[sel]->drc_wp1.bits.win_right =
            window.x + window.width - 1;
        smbl_dev[sel]->drc_wp1.bits.win_bottom =
            window.y + window.height - 1;
    }
    smbl_ctrl_block[sel].dirty = 1;
    return 0;
}

/**
 *  function       : de_smbl_set_para(unsigned int sel)
 *  description    : set smbl para
 *  parameters     :
 *                   sel         <rtmx select>
 *  return         :
 *                   success
 */
int de_smbl_set_para(unsigned int sel, unsigned int width, unsigned int height)
{
    smbl_dev[sel]->gnectl.bits.mod = 2;
    smbl_dev[sel]->drcsize.dwval = (height - 1) << 16 | (width - 1);
    smbl_dev[sel]->drcctl.bits.hsv_en = 1;
    smbl_dev[sel]->drcctl.bits.db_en = 1;
    smbl_dev[sel]->drc_set.dwval = 0;
    smbl_dev[sel]->lhctl.dwval = 0;

    smbl_dev[sel]->lhthr0.dwval =
        (hist_thres_drc[3] << 24) | (hist_thres_drc[2] << 16) |
        (hist_thres_drc[1] << 8) | (hist_thres_drc[0]);
    smbl_dev[sel]->lhthr1.dwval =
        (hist_thres_drc[6] << 16) | (hist_thres_drc[5] << 8) |
        (hist_thres_drc[4]);

    /* out_csc coeff */
    regwrite((void *)smbl_csc_block[sel].off,
           (unsigned char *)csc_bypass_coeff, sizeof(unsigned int) * 12);

    /* filter coeff */
    regwrite((void *)smbl_filter_block[sel].off,
          (unsigned char *)smbl_filter_coeff, sizeof(unsigned char) * 272);

    smbl_enable_block[sel].dirty = 1;
    smbl_ctrl_block[sel].dirty = 1;
    smbl_csc_block[sel].dirty = 0;
    smbl_filter_block[sel].dirty = 0;

    g_smbl_status[sel]->size = width * height / 100;

    return 0;
}

int de_smbl_set_lut(unsigned int sel, unsigned short *lut)
{
    uintptr_t base;
    unsigned int reg_val;

    base = smbl_hw_base[sel];

    /* set lut to smbl lut SRAM */
    regwrite((void *)smbl_lut_block[sel].off, (unsigned char *)lut,
           sizeof(unsigned short) * 256);
    reg_val = readl((void  *)(base));
    reg_val |= 0x00000010;
    writel(reg_val, (void  *)(base));

    return 0;
}

int de_smbl_get_hist(unsigned int sel, unsigned int *cnt)
{
    /* Read histogram */
    memcpy((unsigned char *)cnt, (unsigned char *)smbl_hist_block[sel].off,
           sizeof(unsigned int) * IEP_LH_INTERVAL_NUM);

    return 0;
}

int de_smbl_get_status(unsigned int sel)
{
    return g_smbl_status[sel]->dimming;
}

#else

int de_smbl_set_reg_base(unsigned int sel, void *base)
{
    return 0;
}

int de_smbl_update_regs(unsigned int sel)
{
    return 0;
}

int de_smbl_tasklet(unsigned int sel)
{
    return 0;
}

int de_smbl_apply(unsigned int sel, struct disp_smbl_info *info)
{
    return 0;
}

int de_smbl_sync(unsigned int sel)
{
    return 0;
}

int de_smbl_init(unsigned int sel, uintptr_t reg_base)
{
    return 0;
}

int de_smbl_enable(unsigned int sel, unsigned int en)
{
    return 0;
}

int de_smbl_set_window(unsigned int sel, unsigned int win_enable,
               struct disp_rect window)
{
    return 0;
}

int de_smbl_set_para(unsigned int sel, unsigned int width, unsigned int height)
{
    return 0;
}

int de_smbl_set_lut(unsigned int sel, unsigned short *lut)
{
    return 0;
}

int de_smbl_get_hist(unsigned int sel, unsigned int *cnt)
{
    return 0;
}
int de_smbl_get_status(unsigned int sel)
{
    return 0;
}
#endif
