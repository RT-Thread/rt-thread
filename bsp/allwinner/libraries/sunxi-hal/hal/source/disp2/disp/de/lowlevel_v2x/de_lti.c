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
 *  File name   :       de_lti.c
 *
 *  Description :       display engine 2.0 LTI basic function definition
 *
 *  History     :       2014/04/01  vito cheng  v0.1  Initial version
 *
 ******************************************************************************/

#ifdef CONFIG_DISP2_SUNXI_SUPPORT_ENAHNCE
#include "de_lti_type.h"
#include "de_enhance.h"

static volatile struct __lti_reg_t *lti_dev[DE_NUM][CHN_NUM];
static struct de_reg_blocks lti_block[DE_NUM][CHN_NUM];

/*******************************************************************************
 * function       : de_lti_set_reg_base(unsigned int sel, unsigned int chno,
 *                    unsigned int base)
 * description    : set lti reg base
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  base        <reg base>
 * return         :
 *                  success
 ******************************************************************************/
int de_lti_set_reg_base(unsigned int sel, unsigned int chno, void *base)
{
    lti_dev[sel][chno] = (struct __lti_reg_t *) base;

    return 0;
}

int de_lti_update_regs(unsigned int sel, unsigned int chno)
{
    if (lti_block[sel][chno].dirty == 0x1) {
        regwrite((void *)lti_block[sel][chno].off,
               lti_block[sel][chno].val, lti_block[sel][chno].size);
        lti_block[sel][chno].dirty = 0x0;
    }

    return 0;
}

int de_lti_init(unsigned int sel, unsigned int chno, uintptr_t reg_base)
{
    uintptr_t base;
    void *memory;

    /* FIXME  display path offset should be defined */
    base = reg_base + (sel + 1) * 0x00100000 + LTI_OFST;
#if defined(CONFIG_ARCH_SUN50IW10)
    if (sel)
        base = base - 0x00100000;
#endif
    DE_INF("sel %d, lti_base[%d]=0x%p\n", sel, chno, (void *)base);

    memory = disp_sys_malloc(sizeof(struct __lti_reg_t));
    if (memory == NULL) {
        DE_WRN("disp_sys_malloc lti[%d][%d] memory fail! size=0x%x\n", sel, chno,
              (unsigned int)sizeof(struct __lti_reg_t));
        return -1;
    }

    lti_block[sel][chno].off = base;
    lti_block[sel][chno].val = memory;
    lti_block[sel][chno].size = 0x40;
    lti_block[sel][chno].dirty = 0;

    de_lti_set_reg_base(sel, chno, memory);

    return 0;
}

int de_lti_exit(unsigned int sel, unsigned int chno)
{
    disp_sys_free(lti_block[sel][chno].val);

    return 0;
}

/*******************************************************************************
 * function       : de_lti_enable(unsigned int sel, unsigned int chno,
 *                  unsigned int en)
 * description    : enable/disable lti
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  en          <enable: 0-disable; 1-enable>
 * return         :
 *                  success
 ******************************************************************************/
int de_lti_enable(unsigned int sel, unsigned int chno, unsigned int en)
{
    lti_dev[sel][chno]->ctrl.bits.en = en;
    lti_block[sel][chno].dirty = 1;
    return 0;
}

/*******************************************************************************
 * function       : de_lti_set_size(unsigned int sel, unsigned int chno,
 *                    unsigned int width, unsigned int height)
 * description    : set lti size
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  width       <input width>
 *                                      height  <input height>
 * return         :
 *                  success
******************************************************************************/
int de_lti_set_size(unsigned int sel, unsigned int chno, unsigned int width,
            unsigned int height)
{
    lti_dev[sel][chno]->size.bits.width = width - 1;
    lti_dev[sel][chno]->size.bits.height = height - 1;
    lti_block[sel][chno].dirty = 1;
    return 0;
}

/*******************************************************************************
 * function       : de_lti_set_window(unsigned int sel, unsigned int chno,
 *                   unsigned int win_enable, struct de_rect window)
 * description    : set lti window
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  win_enable  <enable: 0-window mode disable;
 *                                       1-window mode enable>
 *                  window  <window rectangle>
 * return         :
 *                  success
 ******************************************************************************/
int de_lti_set_window(unsigned int sel, unsigned int chno,
              unsigned int win_enable, struct de_rect window)
{
    lti_dev[sel][chno]->ctrl.bits.win_en = win_enable;

    if (win_enable) {
        lti_dev[sel][chno]->win0.bits.win_left = window.x;
        lti_dev[sel][chno]->win0.bits.win_top = window.y;
        lti_dev[sel][chno]->win1.bits.win_right =
            window.x + window.w - 1;
        lti_dev[sel][chno]->win1.bits.win_bot = window.y + window.h - 1;
    }
    lti_block[sel][chno].dirty = 1;
    return 0;
}

/*******************************************************************************
 * function       : de_lti_set_para(unsigned int sel, unsigned int chno,
 *                    unsigned int gain)
 * description    : set lti para
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  gain        <lti gain: normal setting 0-3>
 * return         :
 *                  success
 ******************************************************************************/
int de_lti_set_para(unsigned int sel, unsigned int chno, unsigned int gain)
{
    lti_dev[sel][chno]->gain.bits.lti_fil_gain = gain;

    lti_dev[sel][chno]->ctrl.bits.sel = 0;
    lti_dev[sel][chno]->ctrl.bits.nonl_en = 0;

    lti_dev[sel][chno]->coef0.bits.c0 = 127;
    lti_dev[sel][chno]->coef0.bits.c1 = 64;
    lti_dev[sel][chno]->coef1.bits.c2 = 0xe0;
    lti_dev[sel][chno]->coef1.bits.c3 = 0xc0;
    lti_dev[sel][chno]->coef2.bits.c4 = 0xe0;

    lti_dev[sel][chno]->corth.bits.lti_cor_th = 4;
    lti_dev[sel][chno]->diff.bits.offset = 32;
    lti_dev[sel][chno]->diff.bits.slope = 4;
    lti_dev[sel][chno]->edge_gain.bits.edge_gain = 1;
    lti_dev[sel][chno]->os_con.bits.core_x = 0;
    lti_dev[sel][chno]->os_con.bits.clip = 40;
    lti_dev[sel][chno]->os_con.bits.peak_limit = 1;

    lti_dev[sel][chno]->win_range.bits.win_range = 2;
    lti_dev[sel][chno]->elvel_th.bits.elvel_th = 32;

    lti_block[sel][chno].dirty = 1;
    return 0;
}

/*******************************************************************************
 * function       : de_lti_info2para(unsigned int sharp, struct de_rect window,
 *                   struct __lti_config_data *para)
 * description    : info->para conversion
 * parameters     :
 *                  sharp               <gain info from user>
 *                  window              <window info>
 *                  para                <bsp para>
 * return         :
 *                  success
 ******************************************************************************/
int de_lti_info2para(unsigned int sharp, struct de_rect window,
             struct __lti_config_data *para)
{
    int mode;
    int lti_para[LTI_PARA_NUM][LTI_MODE_NUM] = {
        {0, 3},     /* gain */
    };

    /* parameters */
    mode = sharp & 0xf;
    para->lti_en = mode ? 1 : 0;
    para->gain = lti_para[0][mode];

    return 0;
}
#endif
