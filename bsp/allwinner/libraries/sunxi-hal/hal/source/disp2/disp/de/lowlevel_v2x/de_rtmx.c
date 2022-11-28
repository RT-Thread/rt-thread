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
 *File name   :de_rtmx.c
 *
 *Description :display engine 2.0 realtime mixer
 *             processing base functions implement
 *
 *History     :2014/02/08  iptang  v0.1  Initial version
 *
*/

#include "de_rtmx.h"
#include "de_rtmx_type.h"
#include "de_scaler.h"

static struct __rtmx_reg_t de200_rtmx[DE_NUM];

static struct de_reg_blocks glb_ctl_block[DE_NUM];

static struct de_reg_blocks
    vi_attr_block[DE_NUM][VI_CHN_NUM][LAYER_MAX_NUM_PER_CHN];
static struct de_reg_blocks vi_fc_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks vi_haddr_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks vi_size_block[DE_NUM][VI_CHN_NUM];

static struct de_reg_blocks
    ui_attr_block[DE_NUM][CHN_NUM - VI_CHN_NUM][LAYER_MAX_NUM_PER_CHN];
static struct de_reg_blocks ui_haddr_block[DE_NUM][CHN_NUM - VI_CHN_NUM];
static struct de_reg_blocks ui_size_block[DE_NUM][CHN_NUM - VI_CHN_NUM];

static struct de_reg_blocks bld_attr_block[DE_NUM];
static struct de_reg_blocks bld_ctl_block[DE_NUM];
static struct de_reg_blocks bld_ck_block[DE_NUM];
static struct de_reg_blocks bld_out_block[DE_NUM];
#if defined(SUPPORT_LBC)
static struct de_reg_blocks lbc_block[DE_NUM][VI_CHN_NUM];
#endif

#if defined(SUPPORT_PALETTE)
static struct de_reg_blocks vi_palette_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks ui_palette_block[DE_NUM][CHN_NUM - VI_CHN_NUM];
#endif

#if defined(SUPPORT_DITHER_OUTPUT)
static struct de_reg_blocks dither_ctrl_block[DE_NUM];
#endif

/* static uintptr_t de_base = 0; */
static uintptr_t de_base;

int de_rtmx_update_regs(unsigned int sel)
{
    int i, j, ui_chno, vi_chno, layno;

    vi_chno = de_feat_get_num_vi_chns(sel);
    ui_chno = de_feat_get_num_ui_chns(sel);
    layno = LAYER_MAX_NUM_PER_CHN;

    if (glb_ctl_block[sel].dirty == 0x1) {
        regwrite((void *)glb_ctl_block[sel].off, glb_ctl_block[sel].val,
               glb_ctl_block[sel].size);
        glb_ctl_block[sel].dirty = 0;
    }
#if defined(SUPPORT_DITHER_OUTPUT)

    if (dither_ctrl_block[sel].dirty == 0x1) {
        regwrite((void *)dither_ctrl_block[sel].off, dither_ctrl_block[sel].val,
               dither_ctrl_block[sel].size);
        dither_ctrl_block[sel].dirty = 0;
    }
#endif
    for (j = 0; j < vi_chno; j++) {
        for (i = 0; i < layno; i++) {
            if (vi_attr_block[sel][j][i].dirty == 0x1) {
                regwrite((void *)vi_attr_block[sel][j][i].off,
                       vi_attr_block[sel][j][i].val,
                       vi_attr_block[sel][j][i].size);
                vi_attr_block[sel][j][i].dirty = 0;
            }
        }

        if (vi_fc_block[sel][j].dirty == 0x1) {
            regwrite((void *)vi_fc_block[sel][j].off,
                   vi_fc_block[sel][j].val,
                   vi_fc_block[sel][j].size);
            vi_fc_block[sel][j].dirty = 0;
        }

        if (vi_haddr_block[sel][j].dirty == 0x1) {
            regwrite((void *)vi_haddr_block[sel][j].off,
                   vi_haddr_block[sel][j].val,
                   vi_haddr_block[sel][j].size);
            vi_haddr_block[sel][j].dirty = 0;
        }

        if (vi_size_block[sel][j].dirty == 0x1) {
            regwrite((void *)vi_size_block[sel][j].off,
                   vi_size_block[sel][j].val,
                   vi_size_block[sel][j].size);
            vi_size_block[sel][j].dirty = 0;
        }

#if defined(SUPPORT_LBC)
        if (lbc_block[sel][j].dirty == 0x1) {
            regwrite((void *)lbc_block[sel][j].off,
                   lbc_block[sel][j].val,
                   lbc_block[sel][j].size);
            lbc_block[sel][j].dirty = 0;
        }
#endif

#if defined(SUPPORT_PALETTE)
        if (vi_palette_block[sel][j].dirty == 0x1) {
            regwrite((void *)vi_palette_block[sel][j].off,
                   vi_palette_block[sel][j].val,
                   vi_palette_block[sel][j].size);
            vi_palette_block[sel][j].dirty = 0;
            de200_rtmx[sel].vi_ovl[j]->vi_lay_cfg[0].lay_attr.bits.access_sw = 0;
            vi_attr_block[sel][j][0].dirty = 1;
        }
#endif
    }

    for (j = 0; j < ui_chno; j++) {
        for (i = 0; i < layno; i++) {
            if (ui_attr_block[sel][j][i].dirty == 0x1) {
                regwrite((void *)ui_attr_block[sel][j][i].off,
                       ui_attr_block[sel][j][i].val,
                       ui_attr_block[sel][j][i].size);
                ui_attr_block[sel][j][i].dirty = 0;
            }
        }

        if (ui_haddr_block[sel][j].dirty == 0x1) {
            regwrite((void *)ui_haddr_block[sel][j].off,
                   ui_haddr_block[sel][j].val,
                   ui_haddr_block[sel][j].size);
            ui_haddr_block[sel][j].dirty = 0;
        }

        if (ui_size_block[sel][j].dirty == 0x1) {
            regwrite((void *)ui_size_block[sel][j].off,
                   ui_size_block[sel][j].val,
                   ui_size_block[sel][j].size);
            ui_size_block[sel][j].dirty = 0;
        }
#if defined(SUPPORT_PALETTE)
        if (ui_palette_block[sel][j].dirty == 0x1) {
            regwrite((void *)ui_palette_block[sel][j].off,
                   ui_palette_block[sel][j].val,
                   ui_palette_block[sel][j].size);
            ui_palette_block[sel][j].dirty = 0;
                de200_rtmx[sel].ui_ovl[j]->ui_lay_cfg[0].lay_attr.bits.access_sw = 0;
                ui_attr_block[sel][j][0].dirty = 1;
        }
#endif
    }

    if (bld_attr_block[sel].dirty == 0x1) {
        regwrite((void *)bld_attr_block[sel].off, bld_attr_block[sel].val,
               bld_attr_block[sel].size);
        bld_attr_block[sel].dirty = 0;
    }

    if (bld_ctl_block[sel].dirty == 0x1) {
        regwrite((void *)bld_ctl_block[sel].off, bld_ctl_block[sel].val,
               bld_ctl_block[sel].size);
        bld_ctl_block[sel].dirty = 0;
    }

    if (bld_ck_block[sel].dirty == 0x1) {
        regwrite((void *)bld_ck_block[sel].off, bld_ck_block[sel].val,
               bld_ck_block[sel].size);
        bld_ck_block[sel].dirty = 0;
    }

    if (bld_out_block[sel].dirty == 0x1) {
        regwrite((void *)bld_out_block[sel].off, bld_out_block[sel].val,
               bld_out_block[sel].size);
        bld_out_block[sel].dirty = 0;
    }

    return 0;
}

static int de_rtmx_force_dirty(unsigned int sel)
{
    int i, j, ui_chno, vi_chno, layno;

    vi_chno = de_feat_get_num_vi_chns(sel);
    ui_chno = de_feat_get_num_ui_chns(sel);
    layno = LAYER_MAX_NUM_PER_CHN;

    glb_ctl_block[sel].dirty = 1;
    for (j = 0; j < vi_chno; j++) {
        for (i = 0; i < layno; i++)
            vi_attr_block[sel][j][i].dirty = 1;
        vi_fc_block[sel][j].dirty = 1;
        vi_haddr_block[sel][j].dirty = 1;
        vi_size_block[sel][j].dirty = 1;
    }

    for (j = 0; j < ui_chno; j++) {
        for (i = 0; i < layno; i++)
            ui_attr_block[sel][j][i].dirty = 1;
        ui_haddr_block[sel][j].dirty = 1;
        ui_size_block[sel][j].dirty = 1;
    }

    bld_attr_block[sel].dirty = 1;
    bld_ctl_block[sel].dirty = 1;
    bld_ck_block[sel].dirty = 1;
    bld_out_block[sel].dirty = 1;

    return 0;
}

int de_rtmx_init(unsigned int sel, uintptr_t reg_base)
{
    void *memory;
    int i, j, vi_chno, ui_chno, layno;
    uintptr_t glb_base, apb_base, ovl_base;
    int ch_index = 0;

    de_base = reg_base;

    if (sel > de_feat_get_num_screens())
        DE_WRN("sel %d out of range\n", sel);

    vi_chno = de_feat_get_num_vi_chns(sel);
    ui_chno = de_feat_get_num_ui_chns(sel);
    layno = LAYER_MAX_NUM_PER_CHN;

    glb_base = reg_base + 0x00100000;
    apb_base = reg_base + 0x00101000;
    ovl_base = reg_base + 0x00102000;

    if (sel) {
        glb_base = reg_base + 0x00200000;
        apb_base = reg_base + 0x00201000;
        ovl_base = reg_base + 0x00202000;
    }
#if defined(CONFIG_ARCH_SUN50IW10)
    if (sel) {
        glb_base = glb_base - 0x00100000;
        apb_base = apb_base - 0x00100000;
        ovl_base = ovl_base - 0x00100000;

    }
#endif
    memory = disp_sys_malloc(sizeof(struct __glb_reg_t) + sizeof(struct __glb_dither_reg_t));
    if (memory == NULL) {
        DE_WRN("disp_sys_malloc rtmx global memory fail! size=0x%x\n",
              (unsigned int)sizeof(struct __glb_reg_t));
        return -1;
    }

    glb_ctl_block[sel].off = glb_base;
    glb_ctl_block[sel].val = memory;
    glb_ctl_block[sel].size = 0x10;
    glb_ctl_block[sel].dirty = 1;

    de_rtmx_set_gld_reg_base(sel, memory);
#if defined(SUPPORT_DITHER_OUTPUT)
    dither_ctrl_block[sel].off = glb_base + 0x14;
    dither_ctrl_block[sel].val = ((u8 *)memory) + sizeof(struct __glb_reg_t);
    dither_ctrl_block[sel].size = sizeof(struct __glb_dither_reg_t);
    dither_ctrl_block[sel].dirty = 1;
    de200_rtmx[sel].dither_ctl = (struct __glb_dither_reg_t *)(dither_ctrl_block[sel].val);
#endif

    for (j = 0; j < vi_chno; j++) {
        memory =
            disp_sys_malloc(sizeof(struct __vi_ovl_reg_t));
        if (memory == NULL) {
            DE_WRN("disp_sys_malloc video overlay memory fail! size=0x%x\n",
                  (unsigned int)sizeof(struct __vi_ovl_reg_t));
            return -1;
        }
        DE_INF("disp_sys_malloc memory ok(0x%p) for video channel\n",
            (void *)memory);

        for (i = 0; i < layno; i++) {
            vi_attr_block[sel][j][i].off =
                ovl_base + ch_index * 0x00001000 + i * 0x30;
            vi_attr_block[sel][j][i].val = (memory + i * 0x30);
            vi_attr_block[sel][j][i].size = 0x30;
            vi_attr_block[sel][j][i].dirty = 1;
        }

        vi_fc_block[sel][j].off =
            ovl_base + ch_index * 0x00001000 + 0xc0;
        vi_fc_block[sel][j].val = (memory + 0xc0);
        vi_fc_block[sel][j].size = 0x10;
        vi_fc_block[sel][j].dirty = 1;

        vi_haddr_block[sel][j].off =
            ovl_base + ch_index * 0x00001000 + 0xd0;
        vi_haddr_block[sel][j].val = (memory + 0xd0);
        vi_haddr_block[sel][j].size = 0x18;
        vi_haddr_block[sel][j].dirty = 1;

        vi_size_block[sel][j].off =
            ovl_base + ch_index * 0x00001000 + 0xe8;
        vi_size_block[sel][j].val = (memory + 0xe8);
        vi_size_block[sel][j].size = 0x18;
        vi_size_block[sel][j].dirty = 1;
        de_rtmx_set_overlay_reg_base(sel, j, memory);
#if defined(SUPPORT_PALETTE)
        memory = disp_sys_malloc(sizeof(struct __ovl_palette_reg_t));
        if (memory == NULL) {
            __wrn("malloc vi_palette overlay memory fail! size=0x%x\n",
                (unsigned int)sizeof(struct __ovl_palette_reg_t));
            return -1;
        }

        vi_palette_block[sel][j].off = ovl_base + ch_index * 0x00001000 + 0x400;
        vi_palette_block[sel][j].val = memory;
        vi_palette_block[sel][j].size = PALETTE_SIZE*4;
        vi_palette_block[sel][j].dirty = 0;
        de200_rtmx[sel].vi_palette[j] = (struct __ovl_palette_reg_t *) memory;
#endif
        ch_index++;
    }

    for (j = 0; j < ui_chno; j++) {

        memory =
            disp_sys_malloc(sizeof(struct __ui_ovl_reg_t));
        if (memory == NULL) {
            DE_WRN("disp_sys_malloc ui overlay memory fail! size=0x%x\n",
                  (unsigned int)sizeof(struct __ui_ovl_reg_t));
            return -1;
        }

        for (i = 0; i < layno; i++) {
            ui_attr_block[sel][j][i].off =
                ovl_base + ch_index * 0x00001000 + i * 0x20;
            ui_attr_block[sel][j][i].val = (memory + i * 0x20);
            ui_attr_block[sel][j][i].size = 0x20;
            ui_attr_block[sel][j][i].dirty = 1;
        }

        ui_haddr_block[sel][j].off =
            ovl_base + ch_index * 0x00001000 + 0x80;
        ui_haddr_block[sel][j].val = (memory + 0x80);
        ui_haddr_block[sel][j].size = 0x8;
        ui_haddr_block[sel][j].dirty = 1;

        ui_size_block[sel][j].off =
            ovl_base + ch_index * 0x00001000 + 0x88;
        ui_size_block[sel][j].val = (memory + 0x88);
        ui_size_block[sel][j].size = 0x4;
        ui_size_block[sel][j].dirty = 1;

        de_rtmx_set_overlay_reg_base(sel, j + vi_chno, memory);
#if defined(SUPPORT_PALETTE)
        memory = disp_sys_malloc(sizeof(struct __ovl_palette_reg_t));
        if (memory == NULL) {
            __wrn("malloc ui_palette overlay memory fail! size=0x%x\n",
                (unsigned int)sizeof(struct __ovl_palette_reg_t));
            return -1;
        }

        ui_palette_block[sel][j].off = ovl_base + ch_index * 0x00001000 + 0x400;
        ui_palette_block[sel][j].val = memory;
        ui_palette_block[sel][j].size = PALETTE_SIZE*4;
        ui_palette_block[sel][j].dirty = 0;
        de200_rtmx[sel].ui_palette[j] = (struct __ovl_palette_reg_t *) memory;

#endif
        ch_index++;
    }
#if defined(SUPPORT_LBC)

    ch_index = 0;
    for (j = 0; j < vi_chno; j++) {
        memory = disp_sys_malloc(sizeof(struct __lbc_ovl_reg_t));
        if (memory == NULL) {
            __wrn("malloc lbc overlay memory fail! size=0x%x\n",
                  (unsigned int)sizeof(struct __lbc_ovl_reg_t));
            return -1;
        }

        lbc_block[sel][j].off = ovl_base + ch_index * 0x00001000 + 0x100;
        lbc_block[sel][j].val = memory;
        lbc_block[sel][j].size = 0x28;
        lbc_block[sel][j].dirty = 1;

        de200_rtmx[sel].lbc_ovl[j] = (struct __lbc_ovl_reg_t *) memory;
        ch_index++;
    }
#endif
    memory = disp_sys_malloc(sizeof(struct __bld_reg_t));
    if (memory == NULL) {
        DE_WRN("disp_sys_malloc blending memory fail! size=0x%x\n",
              (unsigned int)sizeof(struct __bld_reg_t));
        return -1;
    }

    bld_attr_block[sel].off = apb_base;
    bld_attr_block[sel].val = memory;
    bld_attr_block[sel].size = 0x44;
    bld_attr_block[sel].dirty = 1;

    bld_ctl_block[sel].off = apb_base + 0x80;
    bld_ctl_block[sel].val = (memory + 0x80);
    bld_ctl_block[sel].size = 0x20;
    bld_ctl_block[sel].dirty = 1;

    bld_ck_block[sel].off = apb_base + 0xb0;
    bld_ck_block[sel].val = (memory + 0xb0);
    bld_ck_block[sel].size = 0x4c;
    bld_ck_block[sel].dirty = 1;

    bld_out_block[sel].off = apb_base + 0xfc;
    bld_out_block[sel].val = (memory + 0xfc);
    bld_out_block[sel].size = 0x4;
    bld_out_block[sel].dirty = 1;

    de_rtmx_set_bld_reg_base(sel, memory);

    return 0;
}

int de_rtmx_exit(unsigned int sel)
{
    int j, vi_chno, ui_chno;
    int ch_index = 0;

    if (sel > de_feat_get_num_screens())
        DE_WRN("sel %d out of range\n", sel);

    vi_chno = de_feat_get_num_vi_chns(sel);
    ui_chno = de_feat_get_num_ui_chns(sel);

    disp_sys_free(glb_ctl_block[sel].val);

    for (j = 0; j < vi_chno; j++) {
        disp_sys_free(vi_attr_block[sel][j][0].val);
#if defined(SUPPORT_LBC)
        disp_sys_free(lbc_block[sel][j].val);
#endif
#if defined(SUPPORT_PALETTE)
        disp_sys_free(vi_palette_block[sel][j].val);
#endif
        ch_index++;
    }

    for (j = 0; j < ui_chno; j++) {
        disp_sys_free(ui_attr_block[sel][j][0].val);
#if defined(SUPPORT_PALETTE)
        disp_sys_free(ui_palette_block[sel][j].val);
#endif
        ch_index++;
    }

    disp_sys_free(bld_attr_block[sel].val);

    return 0;
}

/**
 *function    : de_rtmx_set_gld_reg_base(unsigned int sel, unsigned int base)
 *description : set de reg base
 *parameters  :
 *              sel         <rtmx select>
 *              base        <reg base>
 *return      :
 *              success
 */
int de_rtmx_set_gld_reg_base(unsigned int sel, void *base)
{
    DE_INF("sel=0x%x, addr=0x%p\n", sel, base);
    de200_rtmx[sel].glb_ctl = (struct __glb_reg_t *)base;

    return 0;
}

/**
 *function    : de_rtmx_set_bld_reg_base(unsigned int sel, unsigned int base)
 *description : set de reg base
 *parameters  :
 *              sel         <rtmx select>
 *              base        <reg base>
 *return      :
 *              success
 */
int de_rtmx_set_bld_reg_base(unsigned int sel, void *base)
{
    DE_INF("sel=%d, base=0x%p\n", sel, base);
    de200_rtmx[sel].bld_ctl = (struct __bld_reg_t *) base;

    return 0;
}

/**
 *function   : de_rtmx_set_overlay_reg_base(unsigned int sel,
 *                      unsigned int chno, unsigned int base)
 *description: set de reg base
 *parameters :
 *             sel         <rtmx select>
 *             chno        <overlay select>
 *             base        <reg base>
 *return     :
 *             success
 */
int de_rtmx_set_overlay_reg_base(unsigned int sel, unsigned int chno,
                 void *base)
{
    int vi_chno = de_feat_get_num_vi_chns(sel);

    DE_INF("sel=0x%x, overlayer %d, addr=0x%p\n", sel, chno, base);

    if (chno < vi_chno) {
        de200_rtmx[sel].vi_ovl[chno] = (struct __vi_ovl_reg_t *) base;
    } else {
        de200_rtmx[sel].ui_ovl[chno - vi_chno] =
            (struct __ui_ovl_reg_t *) base;
    }

    return 0;
}

int de_rtmx_set_display_size(unsigned int sel, unsigned int width,
                 unsigned int height)
{
    de200_rtmx[sel].glb_ctl->glb_size.bits.width =
        width == 0 ? 0 : width - 1;
    de200_rtmx[sel].glb_ctl->glb_size.bits.height =
        height == 0 ? 0 : height - 1;

    glb_ctl_block[sel].dirty = 1;

    return 0;
}

int de_rtmx_set_dbuff_rdy(unsigned int sel)
{
    de200_rtmx[sel].glb_ctl->glb_dbuff.dwval = 0x1;

    glb_ctl_block[sel].dirty = 1;

    return 0;
}

int de_rtmx_set_enable(unsigned int sel, unsigned int en)
{
    /* de200_rtmx[sel].glb_ctl->glb_ctl.bits.finish_irq_en = en&0x1; */

    /* 0:write back fetch data after dep;
     * 1:write back fetch data before dep
     */
    de200_rtmx[sel].glb_ctl->glb_ctl.bits.rtwb_port = 0x1;
    de200_rtmx[sel].glb_ctl->glb_ctl.bits.rt_en = en & 0x1;

    /* glb_ctl_block[sel].dirty      = 1;  */
    if (en)
        de_rtmx_force_dirty(sel);

    return 0;
}

int de_rtmx_query_irq(unsigned int sel)
{
    unsigned int irq_flag;
    uintptr_t base = glb_ctl_block[sel].off;

    irq_flag = readl((void  *)(base + 0x04));
    if (irq_flag & 0x1) {
        writel(irq_flag, (void  *)(base + 0x04));
        return 1;
    }

    return 0;
}

int de_rtmx_enable_irq(unsigned int sel, unsigned int en)
{
    unsigned int irq_flag;
    uintptr_t base = glb_ctl_block[sel].off;

    irq_flag = readl((void  *)(base + 0x0));
    irq_flag &= (~(0x1 << 4));
    irq_flag |= (en & 0x1) << 4;
    writel(irq_flag, (void  *)(base + 0x0));

    return 0;
}

/**
 *function       : de_rtmx_set_lay_cfg(unsigned int sel,
 *              unsigned int chno, unsigned int layno, struct __lay_para_t *cfg)
 *description    : set de layer config
 *parameters     :
 *                 sel         <rtmx select>
 *                 chno        <overlay channel number>
 *                 layno       <layer number>
 *                 cfg         <layer config data>
 *return         :
 *                 success
 */
int de_rtmx_set_lay_cfg(unsigned int sel, unsigned int chno, unsigned int layno,
            struct __lay_para_t *cfg)
{
    int fmt, ui_sel;
    int vi_chno = de_feat_get_num_vi_chns(sel);
#if defined(SUPPORT_LBC)
    int lbc_en = cfg->lbc_en;
    unsigned int lbc_support;
    unsigned int tmp;
    lbc_support = de_feat_is_support_lbc_by_chn(sel, chno);
    if (lbc_support == 0 && lbc_en == 1) {
        __wrn("rtmx%d chno%d lay%d does not supported LBC\n", sel, chno, layno);
        return 0;
    }
    if (lbc_en == 1) {
        /* disable overlay */
        tmp = de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_attr.dwval;
        tmp &= 0xfffffffe;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_attr.dwval = tmp;
        vi_attr_block[sel][chno][layno].dirty = 1;

        de200_rtmx[sel].lbc_ovl[chno]->lbc_ctl.bits.lbc_en = cfg->lbc_en;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_ctl.bits.lbc_fcen = cfg->fcolor_en;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_ctl.bits.alpmode = cfg->alpha_mode;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_ctl.bits.clk_gate = 1;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_ctl.bits.is_lossy = cfg->lbc_info.is_lossy ? 1 : 0;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_ctl.bits.rc_en = cfg->lbc_info.rc_en ? 1 : 0;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_ctl.bits.alpha = cfg->alpha;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_v_size.bits.lay_width = cfg->layer.w - 1;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_v_size.bits.lay_hight = cfg->layer.h - 1;

        de200_rtmx[sel].lbc_ovl[chno]->lbc_crop_coor.bits.left_crop = cfg->lbc_crop.x;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_crop_coor.bits.top_crop = cfg->lbc_crop.y;

        de200_rtmx[sel].lbc_ovl[chno]->lbc_crop_size.bits.width_crop = cfg->lbc_crop.w - 1;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_crop_size.bits.hight_crop = cfg->lbc_crop.h - 1;

        de200_rtmx[sel].lbc_ovl[chno]->lbc_laddr.bits.laddr = cfg->lbc_laddr;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_haddr.bits.haddr = cfg->lbc_haddr & 0xFF;

        de200_rtmx[sel].lbc_ovl[chno]->lbc_seg.bits.pitch = cfg->lbc_info.pitch & 0xFFFF;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_seg.bits.seg_bit = cfg->lbc_info.seg_bit & 0xFFFF;
/*
        de200_rtmx[sel].lbc_ovl[chno]->lbc_lay_coor.bits.ovl_coorx = cfg->layer.x;
        de200_rtmx[sel].lbc_ovl[chno]->lbc_lay_coor.bits.ovl_coory = cfg->layer.y;
*/

        lbc_block[sel][chno].dirty = 1;
        return 0;
    }

#endif

    if (chno >= vi_chno) {
        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_lay_cfg[layno].lay_attr.
            bits.lay_en = cfg->en;
        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_lay_cfg[layno].lay_attr.
            bits.lay_alpmod = cfg->alpha_mode;
        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_lay_cfg[layno].lay_attr.
            bits.lay_fcolor_en = cfg->fcolor_en;
        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_lay_cfg[layno].lay_attr.
            bits.lay_fmt = cfg->fmt;
        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_lay_cfg[layno].lay_attr.
            bits.lay_alpctl = cfg->premul_ctl;
        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_lay_cfg[layno].lay_attr.
            bits.lay_top_down = cfg->top_bot_en;
        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_lay_cfg[layno].lay_attr.
            bits.lay_alpha = cfg->alpha;

        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_lay_cfg[layno].lay_size.
            bits.lay_width = cfg->layer.w == 0 ? 0 : cfg->layer.w - 1;
        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_lay_cfg[layno].lay_size.
            bits.lay_height = cfg->layer.h == 0 ? 0 : cfg->layer.h - 1;

        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_lay_cfg[layno].lay_coor.
            bits.lay_coorx = cfg->layer.x;
        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_lay_cfg[layno].lay_coor.
            bits.lay_coory = cfg->layer.y;

        ui_attr_block[sel][chno - vi_chno][layno].dirty = 1;
    } else {
        if (cfg->fmt == DE_FORMAT_YUV422_I_VYUY) {
            ui_sel = 0x0;
            fmt = 0x0;
        } else if (cfg->fmt == DE_FORMAT_YUV422_I_YVYU) {
            ui_sel = 0x0;
            fmt = 0x1;
        } else if (cfg->fmt == DE_FORMAT_YUV422_I_UYVY) {
            ui_sel = 0x0;
            fmt = 0x2;
        } else if (cfg->fmt == DE_FORMAT_YUV422_I_YUYV) {
            ui_sel = 0x0;
            fmt = 0x3;
        } else if (cfg->fmt == DE_FORMAT_YUV422_SP_VUVU) {
            ui_sel = 0x0;
            fmt = 0x5;
        } else if (cfg->fmt == DE_FORMAT_YUV422_SP_UVUV) {
            ui_sel = 0x0;
            fmt = 0x4;
        } else if (cfg->fmt == DE_FORMAT_YUV422_P) {
            ui_sel = 0x0;
            fmt = 0x6;
        } else if (cfg->fmt == DE_FORMAT_YUV420_SP_VUVU) {
            ui_sel = 0x0;
            fmt = 0x9;
        } else if (cfg->fmt == DE_FORMAT_YUV420_SP_UVUV) {
            ui_sel = 0x0;
            fmt = 0x8;
        } else if (cfg->fmt == DE_FORMAT_YUV420_P) {
            ui_sel = 0x0;
            fmt = 0xa;
        } else if (cfg->fmt == DE_FORMAT_YUV411_SP_VUVU) {
            ui_sel = 0x0;
            fmt = 0xd;
        } else if (cfg->fmt == DE_FORMAT_YUV411_SP_UVUV) {
            ui_sel = 0x0;
            fmt = 0xc;
        } else if (cfg->fmt == DE_FORMAT_YUV411_P) {
            ui_sel = 0x0;
            fmt = 0xe;
        } else {
            ui_sel = 0x1;
            fmt = cfg->fmt;
        }

        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_attr.bits.
            lay_en = cfg->en;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_attr.bits.
            alpmode = cfg->alpha_mode;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_attr.bits.
            alpctl = cfg->premul_ctl;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_attr.bits.
            alpha = cfg->alpha;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_attr.bits.
            lay_fcolor_en = cfg->fcolor_en;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_attr.bits.
            lay_fmt = fmt;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_attr.bits.
            ui_sel = ui_sel;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_attr.bits.
            lay_top_down = cfg->top_bot_en;

        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_size.bits.
            lay_width = cfg->layer.w == 0 ? 0 : cfg->layer.w - 1;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_size.bits.
            lay_height = cfg->layer.h == 0 ? 0 : cfg->layer.h - 1;

        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_coor.bits.
            lay_coorx = cfg->layer.x;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_coor.bits.
            lay_coory = cfg->layer.y;

        vi_attr_block[sel][chno][layno].dirty = 1;
    }
#if defined(SUPPORT_LBC)
    if (lbc_support && layno == 0) {
        de200_rtmx[sel].lbc_ovl[chno]->lbc_ctl.dwval = 0;
        lbc_block[sel][chno].dirty = 1;
    }
#endif
    return 0;
}

/*
 *function       : de_rtmx_set_lay_haddr(unsigned int sel, unsigned int chno,
 *                     unsigned int layno, unsigned char top_bot_en,
 *                     unsigned char *haddr_t, unsigned char *haddr_b,
               unsigned int lbc_en)
 *description    : set de high address for layers
 *parameters     :
 *                 sel         <rtmx select>
 *                 chno        <overlay channel number>
 *                 haddr_t     <layer high top address data>
 *                 haddr_b     <layer high bottom address data>
 *                 lbc_en      <is enable lbc>
 *return         :
 *                 success
 */
int de_rtmx_set_lay_haddr(unsigned int sel, unsigned int chno,
              unsigned int layno, unsigned char top_bot_en,
              unsigned char *haddr_t, unsigned char *haddr_b,
              unsigned int lbc_en)
{
    unsigned int haddr, mask;
    int vi_chno = de_feat_get_num_vi_chns(sel);

    switch (layno) {
    case 0:
        mask = 0xffffff00;
        break;
    case 1:
        mask = 0xffff00ff;
        break;
    case 2:
        mask = 0xff00ffff;
        break;
    default:
        mask = 0x00ffffff;
        break;
    }

    if (chno >= vi_chno) {

        haddr =
            de200_rtmx[sel].ui_ovl[chno -
            vi_chno]->ui_lay_top_haddr.dwval & mask;
        de200_rtmx[sel].ui_ovl[chno - vi_chno]->ui_lay_top_haddr.dwval =
            haddr + (haddr_t[0] << layno);

        if (top_bot_en) {
            haddr =
                de200_rtmx[sel].ui_ovl[chno - vi_chno]
                ->ui_lay_bot_haddr.dwval & mask;
            de200_rtmx[sel].ui_ovl[chno - vi_chno]
                ->ui_lay_bot_haddr.dwval =
                haddr + (haddr_b[0] << layno);
        }

        ui_haddr_block[sel][chno - vi_chno].dirty = 1;
    } else {
#if defined(SUPPORT_LBC)
            if (lbc_en)
                return 0;
#endif
        haddr =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_top_haddr[0].dwval
            & mask;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_top_haddr[0].dwval =
            haddr + (haddr_t[0] << layno);
        haddr =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_top_haddr[1].dwval
            & mask;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_top_haddr[1].dwval =
            haddr + (haddr_t[1] << layno);
        haddr =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_top_haddr[2].dwval
            & mask;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_top_haddr[2].dwval =
            haddr + (haddr_t[2] << layno);

        if (top_bot_en) {
            haddr =
                de200_rtmx[sel].vi_ovl[chno]->vi_lay_bot_haddr[0].
                dwval & mask;
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_bot_haddr[0].dwval
                = haddr + (haddr_b[0] << layno);
            haddr =
                de200_rtmx[sel].vi_ovl[chno]->vi_lay_bot_haddr[1].
                dwval & mask;
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_bot_haddr[1].dwval
                = haddr + (haddr_b[1] << layno);
            haddr =
                de200_rtmx[sel].vi_ovl[chno]->vi_lay_bot_haddr[2].
                dwval & mask;
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_bot_haddr[2].dwval
                = haddr + (haddr_b[2] << layno);
        }

        vi_haddr_block[sel][chno].dirty = 1;
    }

    return 0;
}

/**
 *function       : de_rtmx_set_lay_laddr(unsigned int sel, unsigned int chno,
 *                 unsigned int layno, unsigned char fmt,struct de_rect crop,
 *                 unsigned int *size, enum de_3d_in_mode trdinmode,
 *                  unsigned int *addr,unsigned char *haddr)
 *description    : set de low address for layer
 *parameters     :
 *                 sel         <rtmx select>
 *                 chno        <overlay channel number>
 *                 layno       <layer number>
 *                 fmt         <layer data data format>
 *return         :
 *                 success
 */
int de_rtmx_set_lay_laddr(unsigned int sel, unsigned int chno,
            unsigned int layno, unsigned char fmt,
            struct de_rect crop, unsigned int *size,
            unsigned int *align, enum de_3d_in_mode trdinmode,
            unsigned int *addr, unsigned char *haddr,
            unsigned int lbc_en)
{
    long long addr_off[3];
    unsigned int pitch[3];
    unsigned int x0, x1, y0, y1, ycnt, ucnt;
    int vi_chno = de_feat_get_num_vi_chns(sel);

    x0 = crop.x;
    y0 = crop.y;
    x1 = y1 = 0;
    ycnt = ucnt = 0;

    if (fmt <= DE_FORMAT_BGRX_8888) {
        ycnt = 4;
    } else if (fmt <= DE_FORMAT_BGR_888) {
        ycnt = 3;
    } else if (fmt <= DE_FORMAT_BGRA_5551) {
        ycnt = 2;
    } else if (fmt >= DE_FORMAT_1bpp_palette_LE
            && fmt <= DE_FORMAT_8bpp_palette_LE) {
        ycnt = 1;
    } else if (fmt <= DE_FORMAT_YUV422_I_VYUY) {
        ycnt = 2;
        ucnt = 0;
    } else if (fmt == DE_FORMAT_YUV422_P) {
        ycnt = 1;
        ucnt = 1;
        x1 = x0 / 2;
        y1 = y0;
    }
    /* YUV422 */
    else if (fmt == DE_FORMAT_YUV420_P) {
        ycnt = 1;
        ucnt = 1;
        x1 = x0 / 2;
        y1 = y0 / 2;
    }
    /* YUV420 */
    else if (fmt == DE_FORMAT_YUV411_P) {
        ycnt = 1;
        ucnt = 1;
        x1 = x0 / 4;
        y1 = y0;
    }
    /* YUV411 */
    else if (fmt <= DE_FORMAT_YUV422_SP_VUVU) {
        ycnt = 1;
        ucnt = 2;
        x1 = x0 / 2;
        y1 = y0;
    } else if (fmt <= DE_FORMAT_YUV420_SP_VUVU) {
        ycnt = 1;
        ucnt = 2;
        x1 = x0 / 2;
        y1 = y0 / 2;
    } else if (fmt <= DE_FORMAT_YUV411_SP_VUVU) {
        ycnt = 1;
        ucnt = 2;
        x1 = x0 / 4;
        y1 = y0;
    } else {
        ycnt = 4;
    }

    pitch[0] = DISPALIGN(size[0] * ycnt, align[0]);
    pitch[1] = DISPALIGN(size[1] * ucnt, align[1]);
    pitch[2] = DISPALIGN(size[2] * ucnt, align[2]);

    if (trdinmode == DE_3D_SRC_MODE_LI)
        addr_off[0] =
            addr[0] + de_rtmx_get_li_addr_offset(size[0], align[0], x0,
                y0, ycnt);
    else
        addr_off[0] = addr[0] + pitch[0] * y0 + x0 * ycnt;
        /* Y/ARGB */

    haddr[0] = (addr_off[0] >> 32) & 0xff;
    if (chno >= vi_chno) {
        de200_rtmx[sel].ui_ovl[chno - vi_chno]
            ->ui_lay_cfg[layno].lay_pitch.dwval = pitch[0];
        de200_rtmx[sel].ui_ovl[chno - vi_chno]->ui_lay_cfg[layno].
            lay_top_laddr.dwval = (addr_off[0] & 0xffffffff);
        de200_rtmx[sel].ui_ovl[chno - vi_chno]->
            ui_lay_cfg[layno].lay_bot_laddr.dwval = 0x0;

        ui_attr_block[sel][chno - vi_chno][layno].dirty = 1;
    } else {
#if defined(SUPPORT_LBC)
    if (lbc_en)
        return 0;
#endif
        if (trdinmode == DE_3D_SRC_MODE_LI) {
            addr_off[1] =
                addr[1] + de_rtmx_get_li_addr_offset(size[1],
                                 align[1], x1,
                                 y1, ucnt);
            addr_off[2] =
                addr[2] + de_rtmx_get_li_addr_offset(size[2],
                                 align[2], x1,
                                 y1, ucnt);
        } else {
            addr_off[1] = addr[1] + pitch[1] * y1 + x1 * ucnt;
            /* UV/U */
            addr_off[2] = addr[2] + pitch[2] * y1 + x1 * ucnt;
            /* V */
        }

        haddr[1] = (addr_off[1] >> 32) & 0xff;
        haddr[2] = (addr_off[2] >> 32) & 0xff;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_pitch[0].
            dwval = pitch[0];
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_pitch[1].
            dwval = pitch[1];
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_pitch[2].
            dwval = pitch[2];

        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].
            lay_top_laddr[0].dwval = (addr_off[0] & 0xffffffff);
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].
            lay_top_laddr[1].dwval = (addr_off[1] & 0xffffffff);
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].
            lay_top_laddr[2].dwval = (addr_off[2] & 0xffffffff);

        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].
            lay_bot_laddr[0].dwval = 0x0;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].
            lay_bot_laddr[1].dwval = 0x0;
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].
            lay_bot_laddr[2].dwval = 0x0;

        vi_attr_block[sel][chno][layno].dirty = 1;
    }

    return 0;
}

int de_rtmx_get_3d_in_single_size(enum de_3d_in_mode inmode,
    struct de_rect64 *size)
{

    switch (inmode) {
    case DE_3D_SRC_MODE_TB:
        /*size->w = size->w;*/
        size->h = size->h >> 1;
        /*size->x = size->x;
        size->y = size->y;*/
        break;
    case DE_3D_SRC_MODE_SSF:
    case DE_3D_SRC_MODE_SSH:
        size->w = size->w >> 1;
        /*size->h = size->h;
        size->x = size->x;
        size->y = size->y;*/
        break;
    case DE_3D_SRC_MODE_LI:
        /*size->w = size->w;*/
        size->h = size->h >> 1;
        /*size->x = size->x;*/
        size->y = size->y >> 1;
        break;
    case DE_3D_SRC_MODE_FP:
        /*size->w = size->w;
        size->h = size->h;
        size->x = size->x;
        size->y = size->y;*/
        break;
    default:
        /* undefine input mode */
        break;
    }

    return 0;
}

int de_rtmx_get_3d_in(unsigned char fmt, struct de_rect crop,
            struct de_fb *size, unsigned int *align,
            enum de_3d_in_mode trdinmode, unsigned int *addr,
            unsigned int *trd_addr, unsigned int *pitch,
            unsigned int *pitchr, unsigned int *lay_laddr)
{
    unsigned int ycnt, ucnt, data_type;
    unsigned int image_w0, image_w1, image_w2, image_h0, image_h1, image_h2;

    ycnt = ucnt = 0;
    if (trdinmode == DE_3D_SRC_NORMAL)
        return -1;

    if (fmt <= DE_FORMAT_BGRX_8888) {
        ycnt = 4;
        data_type = 0x0;
    } else if (fmt <= DE_FORMAT_BGR_888) {
        ycnt = 3;
        data_type = 0x0;
    } else if (fmt <= DE_FORMAT_BGRA_5551) {
        ycnt = 2;
        data_type = 0x0;
    } else if (fmt <= DE_FORMAT_YUV422_I_VYUY) {
        ycnt = 2;
        data_type = 0x0;
        ucnt = 0;
    } else if (fmt == DE_FORMAT_YUV422_P) {
        ycnt = 1;
        data_type = 0x2;
        ucnt = 1;
    }
    /* YUV422 */
    else if (fmt == DE_FORMAT_YUV420_P) {
        ycnt = 1;
        data_type = 0x2;
        ucnt = 1;
    }
    /* YUV420 */
    else if (fmt == DE_FORMAT_YUV411_P) {
        ycnt = 1;
        data_type = 0x2;
        ucnt = 1;
    }
    /* YUV411 */
    else if (fmt <= DE_FORMAT_YUV422_SP_VUVU) {
        ycnt = 1;
        data_type = 0x1;
        ucnt = 2;
    } else if (fmt <= DE_FORMAT_YUV420_SP_VUVU) {
        ycnt = 1;
        data_type = 0x1;
        ucnt = 2;
    } else if (fmt <= DE_FORMAT_YUV411_SP_VUVU) {
        ycnt = 1;
        data_type = 0x1;
        ucnt = 2;
    } else {
        ycnt = 4;
        data_type = 0x0;
    }

    switch (fmt) {
    case DE_FORMAT_YUV420_P:
    case DE_FORMAT_YUV420_SP_VUVU:
    case DE_FORMAT_YUV420_SP_UVUV:
        image_w0 = crop.w;
        image_w2 = image_w1 = crop.w >> 1;
        image_h0 = crop.h;
        image_h2 = image_h1 = crop.h >> 1;
        break;
    case DE_FORMAT_YUV422_P:
    case DE_FORMAT_YUV422_SP_VUVU:
    case DE_FORMAT_YUV422_SP_UVUV:
        image_w0 = crop.w;
        image_w2 = image_w1 = crop.w >> 1;
        image_h0 = crop.h;
        image_h2 = image_h1 = image_h0;
        break;
    case DE_FORMAT_YUV411_P:
    case DE_FORMAT_YUV411_SP_VUVU:
    case DE_FORMAT_YUV411_SP_UVUV:
        image_w0 = crop.w;
        image_w2 = image_w1 = crop.w >> 2;
        image_h0 = crop.h;
        image_h2 = image_h1 = image_h0;
        break;
    default:
        image_w0 = crop.w;
        image_w2 = image_w1 = image_w0;
        image_h0 = crop.h;
        image_h2 = image_h1 = image_h0;
        break;
    }
    /* planar */
    if (data_type == 0x2) {
        if (trdinmode == DE_3D_SRC_MODE_TB) {
            pitchr[0] = pitch[0] = DISPALIGN(size[0].w, align[0]);
            pitchr[1] = pitch[1] = DISPALIGN(size[1].w, align[1]);
            pitchr[2] = pitch[2] = DISPALIGN(size[2].w, align[2]);

            lay_laddr[0] = pitch[0] * image_h0 + addr[0];
            lay_laddr[1] = pitch[1] * image_h1 + addr[1];
            lay_laddr[2] = pitch[2] * image_h2 + addr[2];

        } else if (trdinmode == DE_3D_SRC_MODE_FP) {
            pitchr[0] = pitch[0] = DISPALIGN(size[0].w, align[0]);
            pitchr[1] = pitch[1] = DISPALIGN(size[1].w, align[1]);
            pitchr[2] = pitch[2] = DISPALIGN(size[2].w, align[2]);

            lay_laddr[0] = trd_addr[0];
            lay_laddr[1] = trd_addr[1];
            lay_laddr[2] = trd_addr[2];

        } else if ((trdinmode == DE_3D_SRC_MODE_SSF)
               || (trdinmode == DE_3D_SRC_MODE_SSH)) {
            pitchr[0] = pitch[0] = DISPALIGN(size[0].w, align[0]);
            pitchr[1] = pitch[1] = DISPALIGN(size[1].w, align[1]);
            pitchr[2] = pitch[2] = DISPALIGN(size[2].w, align[2]);

            lay_laddr[0] = image_w0 + addr[0];
            lay_laddr[1] = image_w1 + addr[1];
            lay_laddr[2] = image_w2 + addr[2];
        } else if (trdinmode == DE_3D_SRC_MODE_LI) {
            pitchr[0] = pitch[0] =
                (DISPALIGN(size[0].w, align[0])) << 1;
            pitchr[1] = pitch[1] =
                (DISPALIGN(size[1].w, align[1])) << 1;
            pitchr[2] = pitch[2] =
                (DISPALIGN(size[2].w, align[2])) << 1;

            lay_laddr[0] = DISPALIGN(size[0].w, align[0]) + addr[0];
            lay_laddr[1] = DISPALIGN(size[1].w, align[1]) + addr[1];
            lay_laddr[2] = DISPALIGN(size[2].w, align[2]) + addr[2];
        }
    } else if (data_type == 0x0)
        /* interleaved */
    {
        if (trdinmode == DE_3D_SRC_MODE_FP) {
            pitchr[0] = pitch[0] =
                DISPALIGN(size[0].w * ycnt, align[0]) / ycnt;
            pitchr[1] = pitch[1] = 0;
            pitchr[2] = pitch[2] = 0;

            lay_laddr[0] = trd_addr[0];
            lay_laddr[1] = 0;
            lay_laddr[2] = 0;
        } else if (trdinmode == DE_3D_SRC_MODE_TB) {
            pitchr[0] = pitch[0] =
                DISPALIGN(size[0].w * ycnt, align[0]) / ycnt;
            pitchr[1] = pitch[1] = 0;
            pitchr[2] = pitch[2] = 0;

            lay_laddr[0] = pitch[0] * image_h0 * ycnt + addr[0];
            lay_laddr[1] = 0;
            lay_laddr[2] = 0;
        } else if ((trdinmode == DE_3D_SRC_MODE_SSF)
               || (trdinmode == DE_3D_SRC_MODE_SSH)) {

            pitchr[0] = pitch[0] =
                DISPALIGN(size[0].w * ycnt, align[0]) / ycnt;
            pitchr[1] = pitch[1] = 0;
            pitchr[2] = pitch[2] = 0;

            lay_laddr[0] = image_w0 * ycnt + addr[0];
            lay_laddr[1] = 0;
            lay_laddr[2] = 0;
        } else if (trdinmode == DE_3D_SRC_MODE_LI) {
            pitchr[0] = pitch[0] =
                (DISPALIGN(size[0].w, align[0])) << 1;
            pitchr[1] = pitch[1] = 0;
            pitchr[2] = pitch[2] = 0;

            lay_laddr[0] =
                (DISPALIGN(size[0].w, align[0])) * ycnt + addr[0];
            lay_laddr[1] = 0;
            lay_laddr[2] = 0;
        }
    } else if (data_type == 0x1)
        /* semi-planar */
    {
        if ((trdinmode == DE_3D_SRC_MODE_SSF)
            || (trdinmode == DE_3D_SRC_MODE_SSH)) {
            pitchr[0] = pitch[0] = DISPALIGN(size[0].w, align[0]);
            pitchr[1] = pitch[1] = DISPALIGN(size[1].w, align[1]);
            pitchr[2] = pitch[2] = 0;

            lay_laddr[0] = image_w0 + addr[0];
            lay_laddr[1] = (image_w1 * ucnt) + addr[1];
            lay_laddr[2] = 0;
        } else if (trdinmode == DE_3D_SRC_MODE_TB) {
            pitchr[0] = pitch[0] = DISPALIGN(size[0].w, align[0]);
            pitchr[1] = pitch[1] = DISPALIGN(size[1].w, align[1]);
            pitchr[2] = pitch[2] = 0;

            lay_laddr[0] = pitch[0] * image_h0 + addr[0];
            lay_laddr[1] = pitch[1] * image_h1 * ucnt + addr[1];
            lay_laddr[2] = 0;
        } else if (trdinmode == DE_3D_SRC_MODE_FP) {
            pitchr[0] = pitch[0] = DISPALIGN(size[0].w, align[0]);
            pitchr[1] = pitch[1] = DISPALIGN(size[1].w, align[1]);
            pitchr[2] = pitch[2] = 0;

            lay_laddr[0] = trd_addr[0];
            lay_laddr[1] = trd_addr[1];
            lay_laddr[2] = 0;
        } else if (trdinmode == DE_3D_SRC_MODE_LI) {
            pitchr[0] = pitch[0] =
                (DISPALIGN(size[0].w, align[0])) << 1;
            pitchr[1] = pitch[1] =
                (DISPALIGN(size[1].w, align[1])) << 1;
            pitchr[2] = pitch[2] = 0;

            lay_laddr[0] = addr[0] + DISPALIGN(size[1].w, align[1]);
            lay_laddr[1] =
                addr[1] + (DISPALIGN(size[1].w, align[1])) * ucnt;
            lay_laddr[2] = 0;
        }
    }

    return 0;
}

int de_rtmx_get_li_addr_offset(unsigned int size, unsigned int align,
                   unsigned int x, unsigned int y, unsigned int cnt)
{
    unsigned int offset;

    offset = DISPALIGN(size, align) * (y >> 1) + x * cnt;

    return offset;
}

int de_rtmx_get_3d_out(struct de_rect frame0, unsigned int scn_w,
            unsigned int scn_h, enum de_3d_out_mode trdoutmode,
            struct de_rect *frame1)
{
    switch (trdoutmode) {
    case DE_3D_OUT_MODE_CI_1:
    case DE_3D_OUT_MODE_CI_2:
    case DE_3D_OUT_MODE_CI_3:
    case DE_3D_OUT_MODE_CI_4:
    case DE_3D_OUT_MODE_SSF:
    case DE_3D_OUT_MODE_SSH:
        {
            frame1->x = frame0.x + scn_w;
            frame1->y = frame0.y;
            frame1->w = frame0.w;
            frame1->h = frame0.h;
            break;
        }
    case DE_3D_OUT_MODE_TB:
    case DE_3D_OUT_MODE_FP:
        {
            frame1->x = frame0.x;
            frame1->y = frame0.y + (scn_h >> 1);
            frame1->w = frame0.w;
            frame1->h = frame0.h;
            break;
        }
    case DE_3D_OUT_MODE_LI:
        /* enable remapping */
        {
            frame1->x = frame0.x + scn_w;
            frame1->y = frame0.y;
            frame1->w = frame0.w;
            frame1->h = frame0.h;
            break;
        }
    case DE_3D_OUT_MODE_LIRGB:
        /* enable remapp */
        {
            frame1->x = frame0.x;
            frame1->y = frame0.y + scn_h;
            frame1->w = frame0.w;
            frame1->h = frame0.h;
            break;
        }
    default:
        break;
    }
    DE_INF("frame0=<%d,%d,%d,%d>\n", frame0.x, frame0.y, frame0.w, frame0.h);
    DE_INF("frame1=<%d,%d,%d,%d>\n", frame1->x, frame1->y, frame1->w,
          frame1->h);

    return 0;
}

int de_rtmx_set_lay_fcolor(unsigned int sel, unsigned int chno,
               unsigned int layno, unsigned char en,
               unsigned char fmt, unsigned int color, unsigned int lbc_en)
{
    unsigned int Y, U, V;
    int vi_chno = de_feat_get_num_vi_chns(sel);

    if (chno >= vi_chno) {
        de200_rtmx[sel].ui_ovl[chno - vi_chno]
            ->ui_lay_cfg[layno].lay_fcolor.dwval = en ? color : 0;

        ui_attr_block[sel][chno - vi_chno][layno].dirty = 1;
    } else {
        Y = color & 0xff0000;
        switch (fmt) {
        case DE_FORMAT_YUV422_I_UYVY:
        case DE_FORMAT_YUV422_I_YUYV:
        case DE_FORMAT_YUV422_SP_UVUV:
        case DE_FORMAT_YUV420_SP_UVUV:
        case DE_FORMAT_YUV411_SP_UVUV:
            U = (color & 0xff) << 8;
            V = (color & 0xff00) >> 8;
            break;
        default:
            U = (color & 0xff00);
            V = (color & 0xff);
            break;
        }
#if defined(SUPPORT_LBC)
        if (lbc_en) {
            de200_rtmx[sel].lbc_ovl[chno]->lbc_fcolor.dwval = en ?
                ((0xFF << 24) | Y | U | V) : 0;
            lbc_block[sel][chno].dirty = 1;
            return 0;
        }
#endif
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_fcolor[layno].dwval = en ?
            ((0xFF << 24) | Y | U | V) : 0;

        vi_fc_block[sel][chno].dirty = 1;
    }

    return 0;
}

int de_rtmx_set_overlay_size(unsigned int sel, unsigned int chno,
                 unsigned int w, unsigned int h, unsigned int lbc_en)
{
    int vi_chno = de_feat_get_num_vi_chns(sel);

    if (chno >= vi_chno) {
        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_ovl_size.bits.ovl_width =
            w == 0 ? 0 : w - 1;
        de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_ovl_size.bits.ovl_height =
            h == 0 ? 0 : h - 1;

        ui_size_block[sel][chno - vi_chno].dirty = 1;
    } else {
#if defined(SUPPORT_LBC)
        if (lbc_en) {
            de200_rtmx[sel].lbc_ovl[chno]->lbc_ovl_size.bits.width_ovl =
                w == 0 ? 0 : w - 1;
            de200_rtmx[sel].lbc_ovl[chno]->lbc_ovl_size.bits.height_ovl =
                h == 0 ? 0 : h - 1;
            lbc_block[sel][chno].dirty = 1;
        }
#endif
        de200_rtmx[sel].vi_ovl[chno]->vi_ovl_size[0].bits.ovl_width =
            w == 0 ? 0 : w - 1;
        de200_rtmx[sel].vi_ovl[chno]->vi_ovl_size[0].bits.ovl_height =
            h == 0 ? 0 : h - 1;

        vi_size_block[sel][chno].dirty = 1;
    }

    return 0;
}
int de_rtmx_set_palette(unsigned int sel, unsigned int chno,
            void *data, unsigned int num)
{
#if defined(SUPPORT_PALETTE)
    int vi_chno = de_feat_get_num_vi_chns(sel);
    if (num == 0)
        return 0;
    if (chno >= vi_chno) {
        regwrite(de200_rtmx[sel].ui_palette[chno - vi_chno], data, num * 4);
        ui_palette_block[sel][chno - vi_chno].size = num * 4;
        ui_palette_block[sel][chno - vi_chno].dirty = 1;
        /*only need to set the first layer.*/
        de200_rtmx[sel].ui_ovl[chno - vi_chno]->ui_lay_cfg[0].lay_attr.bits.access_sw = 1;
        ui_attr_block[sel][chno - vi_chno][0].dirty = 1;

    } else {
        regwrite(de200_rtmx[sel].vi_palette[chno], data, num * 4);
        vi_palette_block[sel][chno].size = num*4;
        vi_palette_block[sel][chno].dirty = 1;
        /*only need to set the first layer.*/
        de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[0].lay_attr.bits.access_sw = 1;
        vi_attr_block[sel][chno][0].dirty = 1;

    }
#endif
    return 0;
}

int de_rtmx_set_dither_out(unsigned int sel, unsigned int en, unsigned int fifo_3d,
            unsigned int mode, unsigned int fmt)
{
#if defined(SUPPORT_DITHER_OUTPUT)

    de200_rtmx[sel].dither_ctl->auto_clk.bits.en = en ? 1 : 0;
    de200_rtmx[sel].dither_ctl->dither.bits.en = en ? 1 : 0;
    de200_rtmx[sel].dither_ctl->dither.bits.fmt = fmt;
    de200_rtmx[sel].dither_ctl->dither.bits.mode = mode;
    de200_rtmx[sel].dither_ctl->dither.bits.fifo_3d = fifo_3d;
    dither_ctrl_block[sel].dirty = 1;
#endif
    return 0;

}
static int de_rtmx_get_coarse_fac(unsigned int sel, unsigned int ovl_w,
                  unsigned int ovl_h, unsigned int vsu_outw,
                  unsigned int vsu_outh, unsigned int fmt,
                  unsigned int lcd_fps, unsigned int lcd_height,
                  unsigned int de_freq_mhz, unsigned int *yhm,
                  unsigned int *yhn, unsigned int *yvm,
                  unsigned int *yvn, unsigned int *chm,
                  unsigned int *chn, unsigned int *cvm,
                  unsigned int *cvn, unsigned int *midyw,
                  unsigned int *midyh, unsigned int *midcw,
                  unsigned int *midch)
{
    unsigned int format, wshift, hshift, status;
    unsigned int tmpyhm, tmpyhn, tmpyvm, tmpyvn;
    unsigned int tmp, required_speed_ability;
    unsigned long long update_speed_ability;
    unsigned int linebuf = 2048;

    /* 0-422, 1-420, 2-411, 3-no mean */
    switch (fmt) {
    case DE_FORMAT_YUV422_I_YVYU:
    case DE_FORMAT_YUV422_I_YUYV:
    case DE_FORMAT_YUV422_I_UYVY:
    case DE_FORMAT_YUV422_I_VYUY:
    case DE_FORMAT_YUV422_P:
    case DE_FORMAT_YUV422_SP_UVUV:
    case DE_FORMAT_YUV422_SP_VUVU:
        format = 0;
        break;
    case DE_FORMAT_YUV420_P:
    case DE_FORMAT_YUV420_SP_UVUV:
    case DE_FORMAT_YUV420_SP_VUVU:
        format = 1;
        break;
    case DE_FORMAT_YUV411_P:
    case DE_FORMAT_YUV411_SP_UVUV:
    case DE_FORMAT_YUV411_SP_VUVU:
        format = 2;
        break;
    default:
        format = 3;
        break;
    }

    if (format == 0) {
        wshift = 1;
        hshift = 0;
    } else if (format == 1) {
        wshift = 1;
        hshift = 1;
    } else if (format == 2) {
        wshift = 2;
        hshift = 0;
    } else {
        wshift = 0;
        hshift = 0;
    }

    /* floor Y channel size */
    ovl_w = ovl_w & (~((1 << wshift) - 1));
    ovl_h = ovl_h & (~((1 << hshift) - 1));

    status = 0x0;
    *yhm = 0;
    *yhn = 0;
    *chm = 0;
    *chn = 0;
    *midyw = ovl_w;
    *midcw = ovl_w >> wshift;
    /* add for UI size not scaler */
    if ((format > 2) && (ovl_w == vsu_outw) && (ovl_h == vsu_outh)) {
        *yvm = 0;
        *yvn = 0;
        *cvm = 0;
        *cvn = 0;
        *midyh = ovl_h;
        *midch = ovl_h >> hshift;
        return status;
    }

    linebuf = de_feat_get_scale_linebuf(sel);
    if ((ovl_w > linebuf)
        && (ovl_w > 8 * vsu_outw)) {
        tmpyhn = (linebuf < (8 * vsu_outw)) ?
            linebuf : (8 * vsu_outw);
        status = 0x1;
    /* horizontal Y channel */
    } else if (ovl_w > linebuf) {
        tmpyhn = linebuf;
        status = 0x1;
    } else if (ovl_w > 8 * vsu_outw) {
        tmpyhn = 8 * vsu_outw;
        status = 0x1;
    }

    if (status == 0x1) {
        tmpyhn = tmpyhn & (~((1 << wshift) - 1));
        tmpyhm = ovl_w;
        *yhm = tmpyhm;
        *yhn = tmpyhn;
        *chm = *yhm;
        *chn = *yhn;

        /* actually fetch horizontal pixel Y channel */
        *midyw = tmpyhn;

        /* actually fetch horizontal pixel C channel */
        *midcw = tmpyhn >> wshift;
    }

/*lcd_freq_MHz = lcd_width*lcd_height*lcd_fps/1000000;
 *
 *how many overlay line can be fetched during scanning
 *  one lcd line(consider 80% dram efficiency)
 *update_speed_ability = lcd_width*de_freq_mhz*125/(ovl_w*lcd_freq_MHz);
 */
/* how many overlay line can be fetched
 * during scanning one lcd line(consider 80% dram efficiency)
 */
    tmp = lcd_height * lcd_fps * (ovl_w > vsu_outw ? ovl_w : vsu_outw);
    if (tmp != 0) {
        update_speed_ability =
            ((unsigned long long)de_freq_mhz * 80000000);
        update_speed_ability = update_speed_ability/ tmp;
    } else
        update_speed_ability = 0;

/* how many overlay line need to fetch during scanning one lcd line */
    required_speed_ability = vsu_outh == 0 ? 0 : ovl_h * 100 / vsu_outh;

    DE_INF("%d,%d,%d,%d\n", de_freq_mhz, tmp, vsu_outh, ovl_h);
    DE_INF("%lld,%d\n", update_speed_ability, required_speed_ability);

    /* vertical Y channel */
    if (update_speed_ability < required_speed_ability) {
        /* if ability < required, use coarse scale */
        unsigned long long tmp2 = update_speed_ability * vsu_outh;

        tmp2 = tmp2 / 100;
        tmpyvn = tmp == 0 ? 0 : (unsigned int)tmp2;
        tmpyvn = tmpyvn & (~((1 << hshift) - 1));
        tmpyvm = ovl_h;
        *yvm = tmpyvm;
        *yvn = tmpyvn;
        *cvm = *yvm;
        *cvn = *yvn;

        /* actually fetch vertical pixel Y channel */
        *midyh = tmpyvn;

        /* actually fetch vertical pixel C channel */
        *midch = tmpyvn >> hshift;
        status |= (0x1 << 1);
    } else if (ovl_h > 4 * vsu_outh) {
        /* to save dram bandwidth when scale down factor more than 4. */
        tmpyvn = 4 * vsu_outh;
        tmpyvn = tmpyvn & (~((1 << hshift) - 1));
        tmpyvm = ovl_h;
        *yvm = tmpyvm;
        *yvn = tmpyvn;
        *cvm = *yvm;
        *cvn = *yvn;

        /* actually fetch vertical pixel Y channel */
        *midyh = tmpyvn;

        /* actually fetch vertical pixel C channel */
        *midch = tmpyvn >> hshift;
        status |= (0x1 << 1);
    } else {
        *yvm = 0;
        *yvn = 0;
        *cvm = 0;
        *cvn = 0;
        *midyh = ovl_h;
        *midch = ovl_h >> hshift;
    }

    return status;
}

/**
 *function   : de_rtmx_set_coarse_fac(unsigned int sel, unsigned int fmt,
 *             unsigned int ovl_w, unsigned int ovl_h,unsigned int vsu_outw,
 *             unsigned int vsu_outh, unsigned int *midyw, unsigned int *midyh,
 *             unsigned int *midcw, unsigned int *midch)
 *description: set de reg base
 *parameters :
 *             sel                                 <rtmx select>
 *             fmt                                 <layer data format>
 *             ovl_w,ovl_h                 <overlay output size>
 *             vsu_outw,vsu_outh   <vsu output size>
 *             *midyw,*midyh               <vsu inputput y size>
 *             *midcw,*midch               <vsu inputput cbcr size>
 *return     :
 *             success
 */
int de_rtmx_set_coarse_fac(unsigned int sel, unsigned char chno,
               unsigned int fmt, unsigned int lcd_fps,
               unsigned int lcd_height, unsigned int de_freq_mhz,
               unsigned int ovl_w, unsigned int ovl_h,
               unsigned int vsu_outw, unsigned int vsu_outh,
               unsigned int *midyw, unsigned int *midyh,
               unsigned int *midcw, unsigned int *midch)
{
    unsigned int yhm, yhn, yvm, yvn, chm, chn, cvm, cvn;
    int status;

    status =
        de_rtmx_get_coarse_fac(sel, ovl_w, ovl_h, vsu_outw, vsu_outh, fmt,
                   lcd_fps, lcd_height, de_freq_mhz, &yhm, &yhn,
                   &yvm, &yvn, &chm, &chn, &cvm, &cvn, midyw,
                   midyh, midcw, midch);

    de200_rtmx[sel].vi_ovl[chno]->vi_hori_ds[0].bits.m = yhm;
    de200_rtmx[sel].vi_ovl[chno]->vi_hori_ds[0].bits.n = yhn;

    de200_rtmx[sel].vi_ovl[chno]->vi_hori_ds[1].bits.m = chm;
    de200_rtmx[sel].vi_ovl[chno]->vi_hori_ds[1].bits.n = chn;

    de200_rtmx[sel].vi_ovl[chno]->vi_vert_ds[0].bits.m = yvm;
    de200_rtmx[sel].vi_ovl[chno]->vi_vert_ds[0].bits.n = yvn;

    de200_rtmx[sel].vi_ovl[chno]->vi_vert_ds[1].bits.m = cvm;
    de200_rtmx[sel].vi_ovl[chno]->vi_vert_ds[1].bits.n = cvn;

    vi_size_block[sel][chno].dirty = 1;

    return status;
}

int de_rtmx_set_pf_en(unsigned int sel, unsigned char *pen)
{
    unsigned char fen[4] = { 1, 0, 0, 0 };

    de200_rtmx[sel].bld_ctl->bld_fcolor_ctl.bits.p0_en = pen[0];
    de200_rtmx[sel].bld_ctl->bld_fcolor_ctl.bits.p1_en = pen[1];
    de200_rtmx[sel].bld_ctl->bld_fcolor_ctl.bits.p2_en = pen[2];
    de200_rtmx[sel].bld_ctl->bld_fcolor_ctl.bits.p3_en = pen[3];

    de200_rtmx[sel].bld_ctl->bld_fcolor_ctl.bits.p0_fcolor_en = fen[0];
    de200_rtmx[sel].bld_ctl->bld_fcolor_ctl.bits.p1_fcolor_en = fen[1];
    de200_rtmx[sel].bld_ctl->bld_fcolor_ctl.bits.p2_fcolor_en = fen[2];
    de200_rtmx[sel].bld_ctl->bld_fcolor_ctl.bits.p3_fcolor_en = fen[3];

    bld_attr_block[sel].dirty = 1;

    return 0;
}

int de_rtmx_set_pipe_cfg(unsigned int sel, unsigned char pno,
             unsigned int color, struct de_rect bldrc)
{
    /* fix the pipe fill color to 0xff000000(alpha=1)
     * actually, we just want to fix the fill color of the bottom pipe
     * so only the fill color function of the bottom pipe is enabled
     * cause:
     * co = cs + cb * (1 - as),
     * ao = as + ab * (1 - as),
     * Co(result) = co / ao
     * when ab = 0, the result is   ( Cs );
     *  when 1, the result is ( Cs * as ), this is what we want.
     */
    de200_rtmx[sel].bld_ctl->bld_pipe_attr[pno].fcolor.dwval =
        0xff000000 | color;
    de200_rtmx[sel].bld_ctl->bld_pipe_attr[pno].insize.bits.width =
        bldrc.w == 0 ? 0 : bldrc.w - 1;
    de200_rtmx[sel].bld_ctl->bld_pipe_attr[pno].insize.bits.height =
        bldrc.h == 0 ? 0 : bldrc.h - 1;
    de200_rtmx[sel].bld_ctl->bld_pipe_attr[pno].offset.bits.coorx = bldrc.x;
    de200_rtmx[sel].bld_ctl->bld_pipe_attr[pno].offset.bits.coory = bldrc.y;

    bld_attr_block[sel].dirty = 1;

    return 0;
}

int de_rtmx_set_route(unsigned int sel, unsigned char pno, unsigned int zoder)
{
    unsigned int route;

    route =
        de200_rtmx[sel].bld_ctl->bld_route_ctl.dwval
        & (~(0xf << (pno << 2)));
    DE_INF("sel%d, pno%d, zorder%d, route:0x%x\n", sel, pno, zoder, route);
    de200_rtmx[sel].bld_ctl->bld_route_ctl.dwval =
        route | (zoder << (pno << 2));
    DE_INF("addr=0x%p, reg=0x%x\n", &de200_rtmx[sel].bld_ctl->bld_route_ctl,
          de200_rtmx[sel].bld_ctl->bld_route_ctl.dwval);

    bld_ctl_block[sel].dirty = 1;

    return 0;
}

int de_rtmx_set_premul(unsigned int sel, unsigned char pno,
               unsigned int pre_mul)
{
    unsigned int pre_mode;

    pre_mode =
        de200_rtmx[sel].bld_ctl->bld_premultiply_ctl.dwval
        & (~(0x1 << pno));
    de200_rtmx[sel].bld_ctl->bld_premultiply_ctl.dwval =
        pre_mode | (pre_mul << pno);

    bld_ctl_block[sel].dirty = 1;

    return 0;
}

int de_rtmx_set_background_color(unsigned int sel, unsigned int color)
{

    de200_rtmx[sel].bld_ctl->bld_bkcolor.dwval =
        (0xff << 24) | (color & 0xffffff);

    bld_ctl_block[sel].dirty = 1;

    return 0;
}

int de_rtmx_set_blend_size(unsigned int sel, unsigned int w, unsigned int h)
{
    de200_rtmx[sel].bld_ctl->bld_output_size.bits.width =
        w == 0 ? 0 : w - 1;
    de200_rtmx[sel].bld_ctl->bld_output_size.bits.height =
        h == 0 ? 0 : h - 1;

    bld_ctl_block[sel].dirty = 1;

    return 0;
}

int de_rtmx_set_blend_mode(unsigned int sel, unsigned int bldno,
               unsigned char mode)
{
    unsigned int bld_mode;

    if (mode == DE_BLD_CLEAR)
        bld_mode = 0x00000000;
    else if (mode == DE_BLD_SRC)
        bld_mode = 0x00010001;
    else if (mode == DE_BLD_DST)
        bld_mode = 0x01000100;
    else if (mode == DE_BLD_SRCOVER)
        bld_mode = 0x03010301;
    else if (mode == DE_BLD_DSTOVER)
        bld_mode = 0x01030103;
    else if (mode == DE_BLD_SRCIN)
        bld_mode = 0x00020002;
    else if (mode == DE_BLD_DSTIN)
        bld_mode = 0x02000200;
    else if (mode == DE_BLD_SRCOUT)
        bld_mode = 0x00030003;
    else if (mode == DE_BLD_DSTOUT)
        bld_mode = 0x03000300;
    else if (mode == DE_BLD_SRCATOP)
        bld_mode = 0x03020302;
    else if (mode == DE_BLD_DSTATOP)
        bld_mode = 0x02030203;
    else if (mode == DE_BLD_XOR)
        bld_mode = 0x03030303;
    else
        bld_mode = 0x03010301;

    de200_rtmx[sel].bld_ctl->bld_mode[bldno].dwval = bld_mode;

    bld_ctl_block[sel].dirty = 1;

    return 0;
}

int de_rtmx_set_blend_color(unsigned int sel, unsigned int bldno,
                unsigned int color)
{
    de200_rtmx[sel].bld_ctl->bld_pipe_attr[bldno].fcolor.dwval =
        (0xff << 24) | (color & 0xffffff);
    bld_attr_block[sel].dirty = 1;

    return 0;
}

int de_rtmx_set_outitl(unsigned int sel, unsigned char interlace_en)
{

    de200_rtmx[sel].bld_ctl->bld_out_ctl.bits.interlace_en =
        interlace_en & 0x1;
    de200_rtmx[sel].bld_ctl->bld_out_ctl.bits.premultiply_en = 0x0;

    bld_out_block[sel].dirty = 1;

    return 0;
}

int de_rtmx_set_colorkey(unsigned int sel, unsigned char ck_no,
             unsigned char ck_mode, unsigned char ck_red_match,
             unsigned char ck_green_match,
             unsigned char ck_blue_match, unsigned int ck_max,
             unsigned int ck_min)
{
    unsigned int tmp, ck_match;

    tmp =
        de200_rtmx[sel].bld_ctl->bld_ck_ctl.
        dwval & (~(0x6 << (0x2 << ck_no)));
    de200_rtmx[sel].bld_ctl->bld_ck_ctl.dwval =
        tmp | (ck_mode << (0x2 << (ck_no + 0x1)));

    ck_match = (ck_red_match << 2) | (ck_green_match << 1) | ck_blue_match;
    tmp =
        de200_rtmx[sel].bld_ctl->bld_ck_cfg.
        dwval & (~(0x7 << (ck_no << 8)));
    de200_rtmx[sel].bld_ctl->bld_ck_ctl.dwval =
        tmp | (ck_match << (ck_no << 8));

    de200_rtmx[sel].bld_ctl->bld_ck_max[ck_no].dwval = ck_max & 0xffffff;
    de200_rtmx[sel].bld_ctl->bld_ck_min[ck_no].dwval = ck_min & 0xffffff;

    bld_ck_block[sel].dirty = 1;

    return 0;
}

struct de_rect de_rtmx_extend_rect(struct de_rect rc1, struct de_rect rc2)
{
    struct de_rect rc;
    int xmax, ymax;

    if ((rc1.w == 0) || (rc1.h == 0))
        return rc2;
    rc.x = min2(rc1.x, rc2.x);
    rc.y = min2(rc1.y, rc2.y);

    xmax = max2(rc1.x + rc1.w, rc2.x + rc2.w);
    ymax = max2(rc1.y + rc1.h, rc2.y + rc2.h);

    rc.w = xmax - rc.x;
    rc.h = ymax - rc.y;

    return rc;
}

int de_rtmx_calc_chnrect(unsigned char *lay_en, int laynum,
    struct de_rect *frame, struct de_rect *crop, int gsu_sel,
    struct scaler_para *step, struct de_rect *layer,
    struct de_rect *bld_rect, unsigned int *ovlw, unsigned int *ovlh)
{
    unsigned int i, minx, miny, pipe_en;
    struct de_rect RCOVL = { 0, 0, 0, 0 };
    struct de_rect RCBLD = { 0, 0, 0, 0 };

    minx = 0xffffffff;
    miny = 0xffffffff;

    /* find min cord */
    for (i = 0; i < laynum; i++) {
        if (lay_en[i]) {
            minx = min2(frame[i].x, minx);
            miny = min2(frame[i].y, miny);
        }
    }

    /* recall the layer cord by sub */
    for (i = 0; i < laynum; i++) {
        if (lay_en[i]) {
            layer[i].x =
                de_calc_ovl_coord(frame[i].x - minx, step[i].hstep,
                      gsu_sel);
            layer[i].y =
                de_calc_ovl_coord(frame[i].y - miny, step[i].vstep,
                      gsu_sel);
            layer[i].w = crop[i].w;
            layer[i].h = crop[i].h;
            DE_INF("layernum=%d, i=%d\n", laynum, i);
            DE_INF("crop=<%d,%d,%d,%d>\n", crop[i].x, crop[i].y,
                  crop[i].w, crop[i].h);
            DE_INF("layer=<%d,%d,%d,%d>\n", layer[i].x, layer[i].y,
                  layer[i].w, layer[i].h);
        }
    }

    for (i = 0; i < laynum; i++) {
        if (lay_en[i]) {
            RCOVL = de_rtmx_extend_rect(RCOVL, layer[i]);
            RCBLD = de_rtmx_extend_rect(RCBLD, frame[i]);
            DE_INF("ovl_rect=<%d,%d,%d,%d>\n", RCOVL.x, RCOVL.y,
                  RCOVL.w, RCOVL.h);
            DE_INF("bld_rect=<%d,%d,%d,%d>\n", RCBLD.x, RCBLD.y,
                  RCBLD.w, RCBLD.h);
        }
    }

    *ovlw = RCOVL.w;
    *ovlh = RCOVL.h;

    bld_rect->x = RCBLD.x;
    bld_rect->y = RCBLD.y;
    bld_rect->w = RCBLD.w;
    bld_rect->h = RCBLD.h;

    pipe_en = 1;
    if ((RCBLD.w == 0) || (RCBLD.h == 0))
        pipe_en = 0;

    return pipe_en;
}

/* ycbcr odd/even */
int de_rtmx_trimcoord(struct de_rect *frame, struct de_rect *crop,
        unsigned int outw, unsigned int outh, int xratio, int yratio)
{
    int left, right, up, down;
    int cut_up, cut_down, cut_left, cut_right;
    int hstep, vstep, hphase, vphase;

    if ((frame->w == 0) || (frame->h == 0)) {
        hstep = vstep = 0;
        hphase = vphase = 0;
        xratio = hstep;
        yratio = vstep;

        return 0;
    }

    /* clear compiler waring */
    hstep = xratio;
    vstep = yratio;

    /* calculate scaler step size */
    hstep = (crop->w << 18) / frame->w;
    vstep = (crop->h << 18) / frame->h;

    /* calculate scaling ratio */
    xratio = hstep;
    yratio = vstep;

    /* assume only frame coordinate has negative value */
    left = up = 0;
    cut_left = cut_right = cut_up = cut_down = 0;
    if (((frame->x + (int)frame->w) < 0) || ((frame->x - outw) > 0)) {
        /* out of screen */
        frame->w = frame->x = 0;
    } else if (frame->x < 0) {
        /* cut left */
        left = (((-frame->x) * crop->w) << 18) / frame->w;
        cut_left = (int)(left >> 18);

        frame->w += frame->x;
        frame->x = 0;
    } else if ((frame->x + frame->w) > outw) {
        /* cut right */
        right =
            (((frame->x + frame->w - outw) * crop->h) << 18) / frame->h;
        cut_right = (int)(right >> 18);

        frame->w = outw - frame->x;
    }
    crop->x += cut_left;
    crop->w -= (cut_left + cut_right);
    hphase = (int)(left & 0x3ffff);

    if (((frame->y + (int)frame->h) < 0) || ((frame->y - outh) > 0)) {
        /* out of screen */
        frame->h = frame->y = 0;
    } else if (frame->y < 0) {
        /* cut up */
        up = (((-frame->y) * crop->h) << 18) / frame->h;
        cut_up = (int)(up >> 18);

        frame->h += frame->y;
        frame->y = 0;
    } else if ((frame->y + frame->h) > outh) {
        /* cut down */
        down =
            (((frame->y + frame->h - outh) * crop->h) << 18) / frame->h;
        cut_down = (int)(down >> 18);

        frame->h = outh - frame->y;
    }
    crop->y += cut_up;
    crop->h -= (cut_up + cut_down);
    vphase = (int)(up & 0x3ffff);

    return 0;
}

int de_rtmx_get_premul_ctl(int laynum, unsigned char *premul)
{
    int i, same, pipe_mode;

    same = 0;
    pipe_mode = 1;
    for (i = 0; i < laynum; i++)
        same += premul[i];

    for (i = 0; i < laynum; i++) {
        if (premul[i]) {
            premul[i] = 2;
        } else if (same == 0)
            /* all zero */
        {
            pipe_mode = 0;
            premul[i] = 0;
        } else {
            premul[i] = 1;
        }
    }

    return pipe_mode;
}

int de_rtmx_mux(unsigned int sel, unsigned int tcon_index)
{
    u32 reg_val;

    if (sel == tcon_index) {
        reg_val = readl((void  *)(de_base + 0x10));
        reg_val &= ~0x1;
        writel(reg_val, (void  *)(de_base + 0x10));
    } else {
        reg_val = readl((void  *)(de_base + 0x10));
        reg_val |= 0x1;
        writel(reg_val, (void  *)(de_base + 0x10));
    }

    return 0;
}

int de_rtmx_get_mux(unsigned int sel)
{
    u32 reg_val;

    reg_val = readl((void  *)(de_base + 0x10));
    reg_val &= 0x1;

    return (reg_val == 0) ? (sel) : (1 - sel);
}

int de_rtmx_sync_hw(unsigned int sel)
{
    int i, j, ui_chno, vi_chno, layno;

    vi_chno = de_feat_get_num_vi_chns(sel);
    ui_chno = de_feat_get_num_ui_chns(sel);
    layno = LAYER_MAX_NUM_PER_CHN;

    regwrite(glb_ctl_block[sel].val, (void *)glb_ctl_block[sel].off,
           glb_ctl_block[sel].size);

    for (j = 0; j < vi_chno; j++) {
        for (i = 0; i < layno; i++) {
            regwrite(vi_attr_block[sel][j][i].val,
                   (void *)vi_attr_block[sel][j][i].off,
                   vi_attr_block[sel][j][i].size);
        }

        regwrite(vi_fc_block[sel][j].val,
            (void *)vi_fc_block[sel][j].off,
            vi_fc_block[sel][j].size);

        regwrite(vi_haddr_block[sel][j].val,
            (void *)vi_haddr_block[sel][j].off,
            vi_haddr_block[sel][j].size);

        regwrite(vi_size_block[sel][j].val,
            (void *)vi_size_block[sel][j].off,
            vi_size_block[sel][j].size);
    }

    for (j = 0; j < ui_chno; j++) {
        for (i = 0; i < layno; i++) {
            regwrite(ui_attr_block[sel][j][i].val,
                (void *)ui_attr_block[sel][j][i].off,
                ui_attr_block[sel][j][i].size);
        }

        regwrite(ui_haddr_block[sel][j].val,
            (void *)ui_haddr_block[sel][j].off,
            ui_haddr_block[sel][j].size);

        regwrite(ui_size_block[sel][j].val,
            (void *)ui_size_block[sel][j].off,
            ui_size_block[sel][j].size);
    }

    regwrite(bld_attr_block[sel].val,
        (void *)bld_attr_block[sel].off,
        bld_attr_block[sel].size);

    regwrite(bld_ctl_block[sel].val,
        (void *)bld_ctl_block[sel].off,
        bld_ctl_block[sel].size);

    regwrite(bld_ck_block[sel].val,
        (void *)bld_ck_block[sel].off,
        bld_ck_block[sel].size);

    regwrite(bld_out_block[sel].val,
        (void *)bld_out_block[sel].off,
        bld_out_block[sel].size);

    return 0;
}

int de_rtmx_get_lay_enabled(unsigned int sel, unsigned int chno,
                unsigned int layno)
{
    int vi_chno = de_feat_get_num_vi_chns(sel);
    int ret = 0;

    if (chno >= vi_chno) {
        ret =
            de200_rtmx[sel].ui_ovl[chno - vi_chno]
            ->ui_lay_cfg[layno].lay_attr.bits.lay_en;
    } else {
        ret =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno]
            .lay_attr.bits.lay_en;
    }

    return ret;
}

int de_rtmx_get_lay_address(unsigned int sel, unsigned int chno,
                unsigned int layno, unsigned long long *addr)
{
    int vi_chno = de_feat_get_num_vi_chns(sel);
    int ret = 0;
    unsigned long long tmp;

    if (chno >= vi_chno) {
        addr[0] = de200_rtmx[sel].ui_ovl[chno - vi_chno]->
        ui_lay_cfg[layno].lay_top_laddr.dwval;
        /* low address */
        tmp = de200_rtmx[sel].ui_ovl[chno - vi_chno]
        ->ui_lay_top_haddr.dwval & (0xff << layno);
        /* high address */
        addr[0] |= tmp << 32;
        addr[1] = 0;
        addr[2] = 0;
    } else {
        addr[0] =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].
            lay_top_laddr[0].dwval;
        addr[1] =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].
            lay_top_laddr[1].dwval;
        addr[2] =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].
            lay_top_laddr[2].dwval;

        tmp = de200_rtmx[sel].vi_ovl[chno]->vi_lay_top_haddr[0].dwval
        & (0xff << layno);
        /* high address */
        addr[0] |= tmp << 32;
        tmp =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_top_haddr[1].dwval
            & (0xff << layno);
        addr[1] |= tmp << 32;
        tmp =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_top_haddr[2].dwval
            & (0xff << layno);
        addr[2] |= tmp << 32;
    }

    return ret;
}

int de_rtmx_get_lay_size(unsigned int sel, unsigned int chno,
             unsigned int layno, struct disp_rectsz *size)
{
    int vi_chno = de_feat_get_num_vi_chns(sel);
    int ret = 0;
    int fmt, ycnt = 4, ucnt = 2;

    if (chno >= vi_chno) {
        fmt =
            de200_rtmx[sel].ui_ovl[chno -
                       vi_chno]->ui_lay_cfg[layno].lay_attr.
            bits.lay_fmt;
        if (fmt <= DE_FORMAT_BGRX_8888)
            ycnt = 4;
        else if (fmt <= DE_FORMAT_BGR_888)
            ycnt = 3;
        else if (fmt <= DE_FORMAT_BGRA_5551)
            ycnt = 2;
        else
            ycnt = 4;

        size[0].width = de200_rtmx[sel].ui_ovl[chno - vi_chno]->
        ui_lay_cfg[layno].lay_pitch.dwval / ycnt;
        /* fixme,according to format */
        size[0].height =
            de200_rtmx[sel].ui_ovl[chno - vi_chno]
            ->ui_lay_cfg[layno].lay_size.bits.lay_height;
    } else {
        fmt =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_attr.
            bits.lay_fmt;
        if (fmt <= DE_FORMAT_BGRX_8888) {
            ycnt = 4;
        } else if (fmt <= DE_FORMAT_BGR_888) {
            ycnt = 3;
        } else if (fmt <= DE_FORMAT_BGRA_5551) {
            ycnt = 2;
        } else if (fmt <= DE_FORMAT_YUV422_I_VYUY) {
            ycnt = 2;
        } else if (fmt == DE_FORMAT_YUV422_P) {
            ycnt = 1;
            ucnt = 1;
        }
        /* YUV422 */
        else if (fmt == DE_FORMAT_YUV420_P) {
            ycnt = 1;
            ucnt = 1;
        }
        /* YUV420 */
        else if (fmt == DE_FORMAT_YUV411_P) {
            ycnt = 1;
            ucnt = 1;
        }
        /* YUV411 */
        else if (fmt <= DE_FORMAT_YUV422_SP_VUVU) {
            ycnt = 1;
            ucnt = 2;
        } else if (fmt <= DE_FORMAT_YUV420_SP_VUVU) {
            ycnt = 1;
            ucnt = 2;
        } else if (fmt <= DE_FORMAT_YUV411_SP_VUVU) {
            ycnt = 1;
            ucnt = 2;
        } else {
            ycnt = 4;
        }
        size[0].width =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].
            lay_pitch[0].dwval / ycnt;
        size[1].width =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].
            lay_pitch[1].dwval / ucnt;
        size[2].width =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].
            lay_pitch[2].dwval / ucnt;
        size[0].height =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_size.
            bits.lay_height;
        size[2].height = size[1].height = size[0].height;
    }

    return ret;
}

int de_rtmx_get_lay_win(unsigned int sel, unsigned int chno, unsigned int layno,
            struct disp_rect *win)
{
    int vi_chno = de_feat_get_num_vi_chns(sel);
    int ret = 0;

    if (chno >= vi_chno) {
        win->width =
            de200_rtmx[sel].ui_ovl[chno - vi_chno]->ui_lay_cfg[layno].
            lay_size.bits.lay_width + 1;
        win->height =
            de200_rtmx[sel].ui_ovl[chno - vi_chno]->ui_lay_cfg[layno].
            lay_size.bits.lay_height + 1;
    } else {
        win->width =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_size.
            bits.lay_width + 1;
        win->height =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_size.
            bits.lay_height + 1;
    }

    return ret;
}

int de_rtmx_get_display_size(unsigned int sel, unsigned int *width,
                 unsigned int *height)
{
    *width = de200_rtmx[sel].glb_ctl->glb_size.bits.width + 1;
    *height = de200_rtmx[sel].glb_ctl->glb_size.bits.height + 1;

    return 0;
}

int de_rtmx_get_lay_format(unsigned int sel, unsigned int chno,
               unsigned int layno)
{
    int vi_chno = de_feat_get_num_vi_chns(sel);
    int fmt = 0;

    if (chno >= vi_chno) {
        fmt =
            de200_rtmx[sel].ui_ovl[chno - vi_chno]->ui_lay_cfg[layno].
            lay_attr.bits.lay_fmt;
    } else {
        fmt =
            de200_rtmx[sel].vi_ovl[chno]->vi_lay_cfg[layno].lay_attr.
            bits.lay_fmt;

        if (fmt == 0)
            fmt = DE_FORMAT_YUV422_I_VYUY;
        else if (fmt == 1)
            fmt = DE_FORMAT_YUV422_I_YVYU;
        else if (fmt == 2)
            fmt = DE_FORMAT_YUV422_I_UYVY;
        else if (fmt == 3)
            fmt = DE_FORMAT_YUV422_I_YUYV;
        else if (fmt == 4)
            fmt = DE_FORMAT_YUV422_SP_UVUV;
        else if (fmt == 5)
            fmt = DE_FORMAT_YUV422_SP_VUVU;
        else if (fmt == 6)
            fmt = DE_FORMAT_YUV422_P;
        else if (fmt == 8)
            fmt = DE_FORMAT_YUV420_SP_UVUV;
        else if (fmt == 9)
            fmt = DE_FORMAT_YUV420_SP_VUVU;
        else if (fmt == 0xa)
            fmt = DE_FORMAT_YUV420_P;
        else if (fmt == 0xc)
            fmt = DE_FORMAT_YUV411_SP_UVUV;
        else if (fmt == 0xd)
            fmt = DE_FORMAT_YUV411_SP_VUVU;
        else if (fmt == 0xe)
            fmt = DE_FORMAT_YUV411_P;
    }

    return fmt;
}
