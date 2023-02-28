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
 *  File name   :       de_fcc.c
 *
 *  Description :       display engine 2.0 fcc base functions implement
 *
 *  History     :       2014/03/28  iptang  v0.1  Initial version
 *
 ******************************************************************************/

#ifdef CONFIG_DISP2_SUNXI_SUPPORT_ENAHNCE
#include "de_fcc_type.h"
#include "de_rtmx.h"
#include "de_vep_table.h"
#include "de_enhance.h"

static volatile struct __fcc_reg_t *fcc_dev[DE_NUM][CHN_NUM];
static struct de_reg_blocks fcc_para_block[DE_NUM][CHN_NUM];

/*******************************************************************************
 *  function       : de_fcc_set_reg_base
 *  description    : set fcc reg base
 *  parameters     :
 *                   sel         <rtmx select>
 *                   chno        <overlay select>
 *                   base        <reg base>
 *  return         :
 *                   success
 ******************************************************************************/
int de_fcc_set_reg_base(unsigned int sel, unsigned int chno, void *base)
{
    fcc_dev[sel][chno] = (struct __fcc_reg_t *) base;

    return 0;
}

int de_fcc_init(unsigned int sel, unsigned int chno, uintptr_t reg_base)
{
    uintptr_t fcc_base;
    void *memory;

    fcc_base = reg_base + (sel + 1) * 0x00100000 + FCC_OFST;
#if defined(CONFIG_ARCH_SUN50IW10)
    if (sel)
        fcc_base = fcc_base - 0x00100000;
#endif
    /* FIXME  display path offset should be defined */

    memory = disp_sys_malloc(sizeof(struct __fcc_reg_t));
    if (memory == NULL) {
        DE_WRN("disp_sys_malloc vep fcc[%d][%d] memory fail! size=0x%x\n", sel,
              chno, (unsigned int)sizeof(struct __fcc_reg_t));
        return -1;
    }

    fcc_para_block[sel][chno].off = fcc_base;
    fcc_para_block[sel][chno].val = memory;
    fcc_para_block[sel][chno].size = 0x48;
    fcc_para_block[sel][chno].dirty = 0;

    de_fcc_set_reg_base(sel, chno, memory);

    return 0;
}

int de_fcc_exit(unsigned int sel, unsigned int chno)
{
    disp_sys_free(fcc_para_block[sel][chno].val);

    return 0;
}

int de_fcc_update_regs(unsigned int sel, unsigned int chno)
{
    if (fcc_para_block[sel][chno].dirty == 0x1) {
        regwrite((void *)fcc_para_block[sel][chno].off,
               fcc_para_block[sel][chno].val,
               fcc_para_block[sel][chno].size);
        fcc_para_block[sel][chno].dirty = 0x0;
    }

    return 0;
}

/*******************************************************************************
 * function       : de_fcc_enable(unsigned int sel, unsigned int chno,
 *                   unsigned int en)
 * description    : enable/disable fcc
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  en          <enable: 0-disable; 1-enable>
 * return         :
 *                  success
 ******************************************************************************/
int de_fcc_enable(unsigned int sel, unsigned int chno, unsigned int en)
{
    fcc_dev[sel][chno]->fcc_ctl.bits.en = en;
    fcc_para_block[sel][chno].dirty = 1;

    return 0;
}

/*******************************************************************************
 * function       : de_fcc_set_size(unsigned int sel, unsigned int chno,
 *                  unsigned int width, unsigned int height)
 * description    : set fcc size
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  width       <input width>
 *                                      height  <input height>
 * return         :
 *                  success
 ******************************************************************************/
int de_fcc_set_size(unsigned int sel, unsigned int chno, unsigned int width,
            unsigned int height)
{
    fcc_dev[sel][chno]->fcc_size.bits.width = width == 0 ? 0 : width - 1;
    fcc_dev[sel][chno]->fcc_size.bits.height = height == 0 ? 0 : height - 1;

    fcc_para_block[sel][chno].dirty = 1;

    return 0;
}

/*******************************************************************************
 * function       : de_fcc_set_window(unsigned int sel, unsigned int chno,
 *                    unsigned int win_en, struct de_rect window)
 * description    : set fcc window
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  win_en      <enable: 0-window mode disable;
 *                                       1-window mode enable>
 *                  window  <window rectangle>
 * return         :
 *                  success
 ******************************************************************************/
int de_fcc_set_window(unsigned int sel, unsigned int chno, unsigned int win_en,
              struct de_rect window)
{
    fcc_dev[sel][chno]->fcc_ctl.bits.win_en = win_en & 0x1;

    if (win_en) {
        fcc_dev[sel][chno]->fcc_win0.bits.left = window.x;
        fcc_dev[sel][chno]->fcc_win0.bits.top = window.y;
        fcc_dev[sel][chno]->fcc_win1.bits.right =
            window.x + window.w - 1;
        fcc_dev[sel][chno]->fcc_win1.bits.bot = window.y + window.h - 1;
    }

    fcc_para_block[sel][chno].dirty = 1;

    return 0;
}

/*******************************************************************************
 * function       : de_fcc_set_para(unsigned int sel, unsigned int chno,
 *                   unsigned int mode)
 * description    : set fcc para
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  sgain
 * return         :
 *                  success
 ******************************************************************************/
int de_fcc_set_para(unsigned int sel, unsigned int chno, unsigned int sgain[6])
{
    regwrite((void *)fcc_dev[sel][chno]->fcc_range,
           (void *)&fcc_range_gain[0], sizeof(int) * 6);
    regwrite((void *)fcc_dev[sel][chno]->fcc_gain, (void *)&sgain[0],
           sizeof(int) * 6);

    fcc_para_block[sel][chno].dirty = 1;

    return 0;
}

/*******************************************************************************
 * function       : de_fcc_info2para(unsigned int gain, struct de_rect window,
 *                    struct __fcc_config_data *para)
 * description    : info->para conversion
 * parameters     :
 *                  gain                <gain info from user>
 *                  window              <window info>
 *                  para                <bsp para>
 * return         :
 *                  success
 ******************************************************************************/
int de_fcc_info2para(unsigned int sgain0, unsigned int sgain1,
            unsigned int sgain2, unsigned int sgain3,
            unsigned int sgain4, unsigned int sgain5,
            struct de_rect window, struct __fcc_config_data *para)
{
    int fcc_para[FCC_PARA_NUM][FCC_MODE_NUM] = {
        {0, 5, 10},   /* sgain0 */
        {0, 12, 24},    /* sgain1 */
        {0, 4, 8},    /* sgain2 */
        {0, 0, 0},    /* sgain3 */
        {0, 0, 0},    /* sgain4 */
        {0, 0, 0},    /* sgain5 */
    };

    /* parameters */
    para->fcc_en =
        ((sgain0 | sgain1 | sgain2 | sgain3 | sgain4 | sgain5) == 0) ?
            0 : 1;

    para->sgain[0] = fcc_para[0][sgain0];
    para->sgain[1] = fcc_para[1][sgain1];
    para->sgain[2] = fcc_para[2][sgain2];
    para->sgain[3] = fcc_para[3][sgain3];
    para->sgain[4] = fcc_para[4][sgain4];
    para->sgain[5] = fcc_para[5][sgain5];

    return 0;
}
#endif
