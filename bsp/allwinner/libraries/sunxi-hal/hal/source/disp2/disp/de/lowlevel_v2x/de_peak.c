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
 *  File name   :       de_peak.c
 *
 *  Description :       display engine 2.0 peaking basic function definition
 *
 *  History     :       2014/03/27  vito cheng  v0.1  Initial version
 *
 ******************************************************************************/

#ifdef CONFIG_DISP2_SUNXI_SUPPORT_ENAHNCE
#include "de_peak_type.h"
#include "de_rtmx.h"
#include "de_enhance.h"

static volatile struct __peak_reg_t *peak_dev[DE_NUM][CHN_NUM];
static struct de_reg_blocks peak_block[DE_NUM][CHN_NUM];
static struct de_reg_blocks peak_gain_block[DE_NUM][CHN_NUM];

/*******************************************************************************
 * function       : de_peak_set_reg_base(unsigned int sel, unsigned int chno,
 *                  unsigned int base)
 * description    : set peak reg base
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  base        <reg base>
 * return         :
 *                  success
 ******************************************************************************/
int de_peak_set_reg_base(unsigned int sel, unsigned int chno, void *base)
{
    DE_INF("sel=%d, chno=%d, base=0x%p\n", sel, chno, base);
    peak_dev[sel][chno] = (struct __peak_reg_t *) base;

    return 0;
}

int de_peak_update_regs(unsigned int sel, unsigned int chno)
{
    if (peak_block[sel][chno].dirty == 0x1) {
        regwrite((void *)peak_block[sel][chno].off,
               peak_block[sel][chno].val, peak_block[sel][chno].size);
        peak_block[sel][chno].dirty = 0x0;
    }

    if (peak_gain_block[sel][chno].dirty == 0x1) {
        regwrite((void *)peak_gain_block[sel][chno].off,
               peak_gain_block[sel][chno].val,
               peak_gain_block[sel][chno].size);
        peak_gain_block[sel][chno].dirty = 0x0;
    }

    return 0;
}

int de_peak_init(unsigned int sel, unsigned int chno, uintptr_t reg_base)
{
    uintptr_t base;
    void *memory;

    /* FIXME: chno is not considered */
    base = reg_base + (sel + 1) * 0x00100000 + PEAK_OFST;
#if defined(CONFIG_ARCH_SUN50IW10)
    if (sel)
        base = base - 0x00100000;
#endif
    DE_INF("sel %d, peak_base[%d]=0x%p\n", sel, chno, (void *)base);

    memory = disp_sys_malloc(sizeof(struct __peak_reg_t));
    if (memory == NULL) {
        DE_WRN("disp_sys_malloc peak[%d][%d] memory fail! size=0x%x\n", sel, chno,
              (unsigned int)sizeof(struct __peak_reg_t));
        return -1;
    }

    peak_block[sel][chno].off = base;
    peak_block[sel][chno].val = memory;
    peak_block[sel][chno].size = 0x10;
    peak_block[sel][chno].dirty = 0;

    peak_gain_block[sel][chno].off = base + 0x10;
    peak_gain_block[sel][chno].val = memory + 0x10;
    peak_gain_block[sel][chno].size = 0x20;
    peak_gain_block[sel][chno].dirty = 0;

    de_peak_set_reg_base(sel, chno, memory);

    return 0;
}

int de_peak_exit(unsigned int sel, unsigned int chno)
{
    disp_sys_free(peak_block[sel][chno].val);

    return 0;
}

/*******************************************************************************
 * function       : de_peak_enable(unsigned int sel, unsigned int chno,
 *                  unsigned int en)
 * description    : enable/disable peak
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  en          <enable: 0-disable; 1-enable>
 * return         :
 *                  success
 ******************************************************************************/
int de_peak_enable(unsigned int sel, unsigned int chno, unsigned int en)
{
    DE_INF("sel=%d, chno=%d, en=%d\n", sel, chno, en);
    peak_dev[sel][chno]->ctrl.bits.en = en;
    peak_block[sel][chno].dirty = 1;
    return 0;
}

/*******************************************************************************
 * function       : de_peak_set_size(unsigned int sel, unsigned int chno,
 *                   unsigned int width, unsigned int height)
 * description    : set peak size
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  width       <input width>
 *                                      height  <input height>
 * return         :
 *                  success
 ******************************************************************************/
int de_peak_set_size(unsigned int sel, unsigned int chno, unsigned int width,
             unsigned int height)
{
    peak_dev[sel][chno]->size.bits.width = width - 1;
    peak_dev[sel][chno]->size.bits.height = height - 1;
    peak_block[sel][chno].dirty = 1;
    return 0;
}

/*******************************************************************************
 * function       : de_peak_set_window(unsigned int sel, unsigned int chno,
 *                  unsigned int win_enable, struct de_rect window)
 * description    : set peak window
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  win_enable  <enable: 0-window mode disable;
 *                                       1-window mode enable>
 *                                      window  <window rectangle>
 * return         :
 *                  success
 ******************************************************************************/
int de_peak_set_window(unsigned int sel, unsigned int chno,
               unsigned int win_enable, struct de_rect window)
{
    peak_dev[sel][chno]->ctrl.bits.win_en = win_enable;

    if (win_enable) {
        peak_dev[sel][chno]->win0.bits.win_left = window.x;
        peak_dev[sel][chno]->win0.bits.win_top = window.y;
        peak_dev[sel][chno]->win1.bits.win_right =
            window.x + window.w - 1;
        peak_dev[sel][chno]->win1.bits.win_bot =
            window.y + window.h - 1;
    }
    peak_block[sel][chno].dirty = 1;
    return 0;
}

/*******************************************************************************
 * function       : de_peak_set_para(unsigned int sel, unsigned int chno,
 *                  unsigned int gain,unsigned int hp_ratio,
 *                                      unsigned int bp0_ratio)
 * description    : set peak para
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  gain        <peak gain: normal setting 36-42>
 *                                      hp_ratio<high pass filter ratio>
 *                                      bp0_ratio<band pass filter 0 ratio>
 * return         :
 *                  success
 * note           : 14/09/01  add hp_ratio and bp0_ratio
 ******************************************************************************/
int de_peak_set_para(unsigned int sel, unsigned int chno, unsigned int gain,
             unsigned int hp_ratio, unsigned int bp0_ratio)
{
    peak_dev[sel][chno]->gain.bits.gain = gain;
    peak_dev[sel][chno]->filter.bits.filter_sel = 0;
    peak_dev[sel][chno]->filter.bits.hp_ratio = hp_ratio;
    peak_dev[sel][chno]->filter.bits.bp0_ratio = bp0_ratio;

    peak_dev[sel][chno]->filter.bits.bp1_ratio = 0;
    peak_dev[sel][chno]->gainctrl.bits.beta = 0;
    peak_dev[sel][chno]->gainctrl.bits.dif_up = 128;
    peak_dev[sel][chno]->shootctrl.bits.neg_gain = 31;
    peak_dev[sel][chno]->coring.bits.corthr = 4;

    peak_gain_block[sel][chno].dirty = 1;
    return 0;
}

/*******************************************************************************
 * function       : de_peak_info2para(unsigned int sharp, struct de_rect window,
 *                    struct __peak_config_data *para)
 * description    : info->para conversion
 * parameters     :
 *                  sharp               <info from user>
 *                  window              <window info>
 *                  para                <bsp para>
 * return         :
 *                  success
 ******************************************************************************/
int de_peak_info2para(unsigned int sharp, struct de_rect window,
              struct __peak_config_data *para)
{
    int mode;
    int peak_para[PEAK_PARA_NUM][PEAK_MODE_NUM] = {
        {0, 36, 48},      /* gain */
        {0, 0x4, 0xe},  /* hp_ratio */
        {0, 0xc, 0x2},  /* bp0_ratio */
    };

    /* parameters */
    mode = (sharp >> 4) & 0xf;
    para->peak_en = mode ? 1 : 0;

    para->gain = peak_para[0][mode];
    para->hp_ratio = peak_para[1][mode];
    para->bp0_ratio = peak_para[2][mode];

    return 0;
}
#endif
