/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */


#include "de_lcd_type.h"
#include "de_lcd.h"

static volatile struct __de_lcd_dev_t *lcd_dev[DEVICE_NUM];
#if defined(HAVE_DEVICE_COMMON_MODULE)
#if defined(CONFIG_ARCH_SUN50IW10)
static volatile struct __de_lcd_top_dev_t *lcd_top[DEVICE_NUM];
#else
static volatile struct __de_lcd_top_dev_t *lcd_top[1];
#endif
#endif

#if defined(HAVE_DEVICE_COMMON_MODULE)

/**
 * @name       vdpo_src_sel
 * @brief      select the video source of vdpo module
 * @param[IN]  sel: (index of vdpo)
 * @param[IN]  src: (0:tcon_lcd0, 1:tcon_tv0)
 * @param[OUT] none
 * @return     0 if success
 */
s32 vdpo_src_sel(u32 sel, u32 src)
{
#if defined(CONFIG_ARCH_SUN50IW10)
    if (sel == 0)
        lcd_top[0]->vdpo_src_select.bits.vdpo0_src_sel = src;
    else
        lcd_top[1]->vdpo_src_select.bits.vdpo1_src_sel = src;
#else
    if (sel == 0)
        lcd_top[0]->vdpo_src_select.bits.vdpo0_src_sel = src;
    else
        lcd_top[0]->vdpo_src_select.bits.vdpo1_src_sel = src;
#endif
    return 0;
}

/**
 * @name       dsi_src_sel
 * @brief      select the video source of dsi module
 * @param[IN]  sel:dsi module index; src:0 or 1
 * @param[OUT] none
 * @return     return 0 if successful
 */
s32 dsi_src_sel(u32 sel, u32 src)
{
    if (sel >= DEVICE_DSI_NUM || src > 1)
        return -1;
#if defined(CONFIG_ARCH_SUN50IW10)
    if (sel == 0)
        lcd_top[0]->dsi_src_select.bits.dsi0_src_sel = src;
    else
        lcd_top[1]->dsi_src_select.bits.dsi1_src_sel = src;
#else
    if (sel == 0)
        lcd_top[0]->dsi_src_select.bits.dsi0_src_sel = src;
    else
        lcd_top[0]->dsi_src_select.bits.dsi1_src_sel = src;
#endif
    return 0;
}
/* sel: the index of timing controller */
s32 tcon0_out_to_gpio(u32 sel)
{
    if (sel >= DEVICE_NUM)
        return -1;

    if (sel == 0)
        lcd_top[0]->tcon_tv_setup.bits.tv0_out = LCD_TO_GPIO;
    else if (sel == 1)
        lcd_top[0]->tcon_tv_setup.bits.tv1_out = LCD_TO_GPIO;

    return 0;
}

/* sel: the index of timing controller */
s32 tcon1_out_to_gpio(u32 sel)
{
    if (sel >= DEVICE_NUM)
        return -1;

    if (sel == 2)
        lcd_top[0]->tcon_tv_setup.bits.tv0_out = TV_TO_GPIO;
    else if (sel == 3)
        lcd_top[0]->tcon_tv_setup.bits.tv1_out = TV_TO_GPIO;

    return 0;
}

/* @sel: the index of timing controller
 * @en:  enable clock or not
 */
s32 tcon1_tv_clk_enable(u32 sel, u32 en)
{
    int tcon_index = -1;
    if (sel >= DEVICE_NUM)
        return -1;

    if (!de_feat_get_tcon_type(sel))
        return -1;

    tcon_index = de_feat_get_tcon_index(sel);
    if (tcon_index < 0)
        return -1;

    if (tcon_index == 0) {
        lcd_top[0]->tcon_tv_setup.bits.tv0_clk_src = TV_CLK_F_TVE;
        lcd_top[0]->tcon_clk_gate.bits.tv0_clk_gate = en;
    } else if (tcon_index == 1) {
        lcd_top[0]->tcon_tv_setup.bits.tv1_clk_src = TV_CLK_F_TVE;
        lcd_top[0]->tcon_clk_gate.bits.tv1_clk_gate = en;
    }

    return 0;
}

/**
 * tcon1_hdmi_clk_enable - enable tcon clk output to hdmi
 * @sel: The index of tcon selected for hdmi source
 * @en: Enable or not for tcon
 *
 * Returns 0.
 */
s32 tcon1_hdmi_clk_enable(u32 sel, u32 en)
{
    int tcon_index;

    if (sel >= DEVICE_NUM)
        return -1;
    if (!de_feat_get_tcon_type(sel))
        return -1;

    tcon_index = de_feat_get_tcon_index(sel);
    if (tcon_index < 0)
        return -1;

    if (tcon_index == 0)
        lcd_top[0]->tcon_clk_gate.bits.tv0_clk_gate = en;
    else
        lcd_top[0]->tcon_clk_gate.bits.tv1_clk_gate = en;

    if (en) {
        if (tcon_index == 0)
            lcd_top[0]->tcon_clk_gate.bits.hdmi_src = 1;
        else if (tcon_index == 1)
            lcd_top[0]->tcon_clk_gate.bits.hdmi_src = 2;
    } else {
        /* disable tcon output to hdmi */
        if (((tcon_index == 0)
             && (lcd_top[0]->tcon_clk_gate.bits.hdmi_src == 1))
            || ((tcon_index == 1)
            && (lcd_top[0]->tcon_clk_gate.bits.hdmi_src == 2))) {
            lcd_top[0]->tcon_clk_gate.bits.hdmi_src = 0;
        }
    }

    return 0;
}

/**
 * @name       tcon_vdpo_clk_enable
 * @brief      releae vdpo gate in display if top
 * @param[IN]  sel: (index of vdpo)
 * @param[IN]  en: (0:disable, 1:enable)
 * @param[OUT] none
 * @return     0 if success
 */
s32 tcon_vdpo_clk_enable(u32 sel, u32 en)
{
#if defined(CONFIG_ARCH_SUN50IW10)
    if (sel == 0)
        lcd_top[0]->tcon_clk_gate.bits.vdpo0_clk_gate = en;
    else
        lcd_top[1]->tcon_clk_gate.bits.vdpo1_clk_gate = en;
#else
    if (sel == 0)
        lcd_top[0]->tcon_clk_gate.bits.vdpo0_clk_gate = en;
    else
        lcd_top[0]->tcon_clk_gate.bits.vdpo1_clk_gate = en;
#endif
    return 0;
}

/**
 * tcon0_dsi_clk_enable - enable tcon clk output to dsi
 * @sel: The index of tcon selected for dsi source
 * @en: Enable or not for tcon
 *
 * Returns 0.
 */
s32 tcon0_dsi_clk_enable(u32 sel, u32 en)
{
    /* only tcon0 support dsi on sun8iw11 platform */
#if defined(CONFIG_ARCH_SUN8IW17P1)
    lcd_top[0]->tcon_clk_gate.bits.lcd1_dsi_clk_gate = en;
#else
    if (sel == 0)
        lcd_top[0]->tcon_clk_gate.bits.dsi_clk_gate = en;
#endif

    return 0;
}

/**
 * tcon_de_attach - attach tcon and de specified by de_index and tcon_index
 * @de_index: The index of de to be attached
 * @tcon_index: The index of tcon to be attached
 *
 * Returns 0 while successful, otherwise returns -1.
 */
s32 tcon_de_attach(u32 tcon_index, u32 de_index)
{
    int tcon_real_index = 0;

    if ((de_index >= DE_NUM) || (tcon_index >= DEVICE_NUM))
        return -1;
    tcon_real_index = de_feat_get_tcon_index(tcon_index);
    if (tcon_real_index < 0)
        return -1;
    if (de_feat_get_tcon_type(tcon_index)) {
        if (tcon_real_index < 2)
            tcon_real_index += 2;
        else
            tcon_real_index += 4;
    } else {
        if (tcon_real_index > 2)
            tcon_real_index += 2;
    }

#if defined(CONFIG_ARCH_SUN50IW10)
    if (de_index == 0)
        lcd_top[0]->tcon_de_perh.bits.de_port0_perh = tcon_real_index;
    else if (de_index == 1)
        lcd_top[1]->tcon_de_perh.bits.de_port1_perh = tcon_real_index;
#else
    if (de_index == 0)
        lcd_top[0]->tcon_de_perh.bits.de_port0_perh = tcon_real_index;
    else if (de_index == 1)
        lcd_top[0]->tcon_de_perh.bits.de_port1_perh = tcon_real_index;
#endif

    return 0;
}

/**
 * @name       get_tcon_type_by_de_index
 * @brief      get tcon type by de index
 * @param[IN]  de_index:index of de
 * @param[OUT] none
 * @return     0:tcon lcd,1 tcon tv,-1 fail
 */
s32 get_tcon_type_by_de_index(u32 de_index)
{
    s32 tcon_index = 0;

#if defined(CONFIG_ARCH_SUN50IW10)
    if (de_index == 0)
        tcon_index = lcd_top[0]->tcon_de_perh.bits.de_port0_perh;
    else if (de_index == 1)
        tcon_index = lcd_top[1]->tcon_de_perh.bits.de_port1_perh;
    else
        return -1;
#else
    if (de_index == 0)
        tcon_index = lcd_top[0]->tcon_de_perh.bits.de_port0_perh;
    else if (de_index == 1)
        tcon_index = lcd_top[0]->tcon_de_perh.bits.de_port1_perh;
    else
        return -1;
#endif
    return ((tcon_index / 2) % 2 != 0) ? 1 : 0;
}
/**
 * tcon_get_attach_by_de_index - get the index of tcon by de_index
 * @de_index: The index of de to be attached
 *
 * Returns the index of tcon attached with the de specified
 * or -1 while not attach.
 */
s32 tcon_get_attach_by_de_index(u32 de_index)
{
    s32 tcon_index = 0;

#if defined(CONFIG_ARCH_SUN50IW10)
    if (de_index == 0)
        tcon_index = lcd_top[0]->tcon_de_perh.bits.de_port0_perh;
    else if (de_index == 1)
        tcon_index = lcd_top[1]->tcon_de_perh.bits.de_port1_perh;
#else
    if (de_index == 0)
        tcon_index = lcd_top[0]->tcon_de_perh.bits.de_port0_perh;
    else if (de_index == 1)
        tcon_index = lcd_top[0]->tcon_de_perh.bits.de_port1_perh;
#endif
    return tcon_index;
}

s32 tcon_top_set_reg_base(u32 sel, uintptr_t base)
{
    lcd_top[sel] = (struct __de_lcd_top_dev_t *) (uintptr_t) (base);
    return 0;
}

uintptr_t tcon_top_get_reg_base(u32 sel)
{
    return (uintptr_t) lcd_top[sel];
}
#else
s32 tcon0_out_to_gpio(u32 sel)
{
    return 0;
}

s32 tcon1_out_to_gpio(u32 sel)
{
    return 0;
}

s32 tcon1_tv_clk_enable(u32 sel, u32 en)
{
    return 0;
}

s32 tcon1_hdmi_clk_enable(u32 sel, u32 en)
{
    return 0;
}

s32 tcon0_dsi_clk_enable(u32 sel, u32 en)
{
    return 0;
}

s32 tcon_de_attach(u32 tcon_index, u32 de_index)
{
    return 0;
}

s32 tcon_get_attach_by_de_index(u32 de_index)
{
    return 0;
}

s32 tcon_top_set_reg_base(u32 sel, uintptr_t base)
{
    return 0;
}

uintptr_t tcon_top_get_reg_base(u32 sel)
{
    return 0;
}
s32 vdpo_src_sel(u32 sel, u32 src)
{
    return 0;
}
s32 tcon_vdpo_clk_enable(u32 sel, u32 en)
{
    return 0;
}
#endif

s32 lvds_open(u32 sel, struct disp_panel_para *panel)
{
    lcd_dev[sel]->tcon0_lvds_ctl.bits.tcon0_lvds_en = 1;
    if (panel->lcd_lvds_if == LCD_LVDS_IF_DUAL_LINK) {
        lcd_dev[sel]->tcon0_lvds_ana[0].bits.c = 2;
        lcd_dev[sel]->tcon0_lvds_ana[0].bits.v = 3;
        lcd_dev[sel]->tcon0_lvds_ana[0].bits.pd = 2;
        lcd_dev[sel]->tcon0_lvds_ana[1].bits.c = 2;
        lcd_dev[sel]->tcon0_lvds_ana[1].bits.v = 3;
        lcd_dev[sel]->tcon0_lvds_ana[1].bits.pd = 2;

        lcd_dev[sel]->tcon0_lvds_ana[0].bits.en_ldo = 1;
        lcd_dev[sel]->tcon0_lvds_ana[1].bits.en_ldo = 1;
        /* 1200ns */
        disp_delay_us(5);
        lcd_dev[sel]->tcon0_lvds_ana[0].bits.en_mb = 1;
        lcd_dev[sel]->tcon0_lvds_ana[1].bits.en_mb = 1;
        /* 1200ns */
        disp_delay_us(5);
        lcd_dev[sel]->tcon0_lvds_ana[0].bits.en_drvc = 1;
        lcd_dev[sel]->tcon0_lvds_ana[1].bits.en_drvc = 1;
        if (panel->lcd_lvds_colordepth == LCD_LVDS_6bit) {
            lcd_dev[sel]->tcon0_lvds_ana[0].bits.en_drvd = 0x7;
            lcd_dev[sel]->tcon0_lvds_ana[1].bits.en_drvd = 0x7;
        } else {
            lcd_dev[sel]->tcon0_lvds_ana[0].bits.en_drvd = 0xf;
            lcd_dev[sel]->tcon0_lvds_ana[1].bits.en_drvd = 0xf;
        }
    } else {
        lcd_dev[sel]->tcon0_lvds_ana[sel].bits.c = 2;
        lcd_dev[sel]->tcon0_lvds_ana[sel].bits.v = 3;
        lcd_dev[sel]->tcon0_lvds_ana[sel].bits.pd = 2;

        lcd_dev[sel]->tcon0_lvds_ana[sel].bits.en_ldo = 1;
        /* 1200ns */
        disp_delay_us(5);
        lcd_dev[sel]->tcon0_lvds_ana[sel].bits.en_mb = 1;
        /* 1200ns */
        disp_delay_us(5);
        lcd_dev[sel]->tcon0_lvds_ana[sel].bits.en_drvc = 1;
        if (panel->lcd_lvds_colordepth == LCD_LVDS_6bit)
            lcd_dev[sel]->tcon0_lvds_ana[sel].bits.en_drvd = 0x7;
        else
            lcd_dev[sel]->tcon0_lvds_ana[sel].bits.en_drvd = 0xf;
    }

    return 0;
}

s32 lvds_close(u32 sel)
{
    lcd_dev[sel]->tcon0_lvds_ana[0].bits.en_drvd = 0;
    lcd_dev[sel]->tcon0_lvds_ana[1].bits.en_drvd = 0;
    lcd_dev[sel]->tcon0_lvds_ana[0].bits.en_drvc = 0;
    lcd_dev[sel]->tcon0_lvds_ana[1].bits.en_drvc = 0;
    /* 1200ns */
    disp_delay_us(5);
    lcd_dev[sel]->tcon0_lvds_ana[0].bits.en_mb = 0;
    lcd_dev[sel]->tcon0_lvds_ana[1].bits.en_mb = 0;
    /* 1200ns */
    disp_delay_us(5);
    lcd_dev[sel]->tcon0_lvds_ana[0].bits.en_ldo = 0;
    lcd_dev[sel]->tcon0_lvds_ana[1].bits.en_ldo = 0;
    lcd_dev[sel]->tcon0_lvds_ctl.bits.tcon0_lvds_en = 0;

    return 0;
}

u32 tcon_get_cur_field(u32 sel, u32 tcon_index)
{
    if (tcon_index == 0)
        return lcd_dev[sel]->tcon_debug.bits.tcon0_field_polarity;
    else if (tcon_index == 1)
        return lcd_dev[sel]->tcon_debug.bits.tcon1_field_polarity;

    return 0;
}

s32 tcon_get_timing(u32 sel, u32 index, struct disp_video_timings *tt)
{
    u32 x, y, ht, hbp, vt, vbp, hspw, vspw;
    u32 lcd_if = 0, lcd_hv_if = 0;
    u32 b_interlace = 0;

    if (index == 0) {
        lcd_if = lcd_dev[sel]->tcon0_ctl.bits.tcon0_if;
        lcd_hv_if = lcd_dev[sel]->tcon0_hv_ctl.bits.hv_mode;
        x = lcd_dev[sel]->tcon0_basic0.bits.x;
        y = lcd_dev[sel]->tcon0_basic0.bits.y;
        ht = lcd_dev[sel]->tcon0_basic1.bits.ht;
        hbp = lcd_dev[sel]->tcon0_basic1.bits.hbp;
        vt = lcd_dev[sel]->tcon0_basic2.bits.vt;
        vbp = lcd_dev[sel]->tcon0_basic2.bits.vbp;
        hspw = lcd_dev[sel]->tcon0_basic3.bits.hspw;
        vspw = lcd_dev[sel]->tcon0_basic3.bits.vspw;
    } else {
        b_interlace = lcd_dev[sel]->tcon1_ctl.bits.interlace_en;
        x = lcd_dev[sel]->tcon1_basic0.bits.x;
        y = lcd_dev[sel]->tcon1_basic0.bits.y;
        ht = lcd_dev[sel]->tcon1_basic3.bits.ht;
        hbp = lcd_dev[sel]->tcon1_basic3.bits.hbp;
        vt = lcd_dev[sel]->tcon1_basic4.bits.vt;
        vbp = lcd_dev[sel]->tcon1_basic4.bits.vbp;
        hspw = lcd_dev[sel]->tcon1_basic5.bits.hspw;
        vspw = lcd_dev[sel]->tcon1_basic5.bits.vspw;
    }

    tt->x_res = x;
    tt->hor_back_porch = (hbp + 1) - (hspw + 1);
    tt->hor_front_porch = (ht + 1) - (x + 1) - (hbp + 1);
    tt->hor_total_time = ht + 1;
    tt->y_res = y;
    tt->ver_back_porch = (vbp + 1) - (vspw + 1);
    tt->ver_front_porch = (vt / 2) - (y + 1) - (vbp + 1);
    tt->hor_sync_time = (hspw + 1);
    tt->ver_sync_time = (vspw + 1);
    tt->ver_total_time = (vt / 2);

    if ((index == 0) && (lcd_if == LCD_IF_HV)
        && (lcd_hv_if == LCD_HV_IF_CCIR656_2CYC)) {
        tt->ver_total_time = vt;
        tt->hor_total_time = (ht + 1) / 2;
        tt->hor_back_porch = (hbp + 1) / 2;
        tt->hor_sync_time = (hspw + 1) / 2;
        tt->y_res = (y + 1) * 2;
    } else if (b_interlace == 1) {
        tt->y_res = (y + 1) * 2;
        tt->ver_total_time = vt;
    }

    return 0;
}

s32 tcon_set_reg_base(u32 sel, uintptr_t base)
{
    lcd_dev[sel] = (struct __de_lcd_dev_t *) (uintptr_t) (base);
    return 0;
}

uintptr_t tcon_get_reg_base(u32 sel)
{
    return (uintptr_t)lcd_dev[sel];
}

s32 tcon_init(u32 sel)
{
    lcd_dev[sel]->tcon_gctl.bits.io_map_sel = 0;
    lcd_dev[sel]->tcon_gctl.bits.pad_sel = 1;
    lcd_dev[sel]->tcon0_ctl.bits.tcon0_en = 0;
    lcd_dev[sel]->tcon1_ctl.bits.tcon1_en = 0;
    lcd_dev[sel]->tcon_gctl.bits.tcon_en = 0;
    lcd_dev[sel]->tcon_gint0.bits.tcon_irq_en = 0;
    lcd_dev[sel]->tcon_gint0.bits.tcon_irq_flag = 0;
    lcd_dev[sel]->tcon_gctl.bits.tcon_en = 1;

    return 0;
}

s32 tcon_pan_sel(u32 sel, u32 pad)
{
    lcd_dev[sel]->tcon_gctl.bits.pad_sel = pad;

    return 0;
}

s32 tcon_exit(u32 sel)
{
    lcd_dev[sel]->tcon_gctl.bits.tcon_en = 0;
    lcd_dev[sel]->tcon0_dclk.bits.tcon0_dclk_en = 0;

    lcd_dev[sel]->tcon_gctl.bits.pad_sel = 0;
    lcd_dev[sel]->tcon_gctl.bits.io_map_sel = 1;
    return 0;
}

s32 tcon_irq_enable(u32 sel, enum __lcd_irq_id_t id)
{
    lcd_dev[sel]->tcon_gint0.bits.tcon_irq_en |= (1 << id);

    return 0;
}

s32 tcon_irq_disable(u32 sel, enum __lcd_irq_id_t id)
{
    lcd_dev[sel]->tcon_gint0.bits.tcon_irq_en &= ~(1 << id);

    return 0;
}

u32 tcon_irq_query(u32 sel, enum __lcd_irq_id_t id)
{
    u32 en, fl;

    en = lcd_dev[sel]->tcon_gint0.bits.tcon_irq_en;
    fl = lcd_dev[sel]->tcon_gint0.bits.tcon_irq_flag;
    if (en & fl & (((u32) 1) << id)) {
        lcd_dev[sel]->tcon_gint0.bits.tcon_irq_flag &=
            ~(((u32) 1) << id);
        return 1;
    } else
        return 0;
}

u32 tcon_get_start_delay(u32 sel, u32 tcon_index)
{
    if (tcon_index == 0)
        return lcd_dev[sel]->tcon0_ctl.bits.start_delay;
    else if (tcon_index == 1)
        return lcd_dev[sel]->tcon1_ctl.bits.start_delay;

    return 0;
}

u32 tcon0_get_cpu_tri2_start_delay(u32 sel)
{
    return lcd_dev[sel]->tcon0_cpu_tri2.bits.start_delay;
}

u32 tcon_get_cur_line(u32 sel, u32 tcon_index)
{
    if (tcon_index == 0)
        return lcd_dev[sel]->tcon_debug.bits.tcon0_current_line;
    else if (tcon_index == 1)
        return lcd_dev[sel]->tcon_debug.bits.tcon1_current_line;

    return 0;
}

/* 0: normal; -1:under flow; */
s32 tcon_get_status(u32 sel, u32 tcon_index)
{
    if (tcon_index == 0) {
        if (lcd_dev[sel]->tcon_debug.bits.tcon0_fifo_under_flow) {
            lcd_dev[sel]->tcon_debug.bits.tcon0_fifo_under_flow = 0;
            return -1;
        }
    } else if (tcon_index == 1) {
        if (lcd_dev[sel]->tcon_debug.bits.tcon1_fifo_under_flow) {
            lcd_dev[sel]->tcon_debug.bits.tcon1_fifo_under_flow = 0;
            return -1;
        }
    }

    return 0;
}

s32 tcon0_src_select(u32 sel, enum __lcd_src_t src, u32 de_no)
{
    lcd_dev[sel]->tcon0_ctl.bits.src_sel = src;
    if (src == LCD_SRC_DE)
        tcon_de_attach(sel, de_no);

    return 0;
}

s32 tcon0_src_get(u32 sel)
{
    return lcd_dev[sel]->tcon0_ctl.bits.src_sel;
}

s32 tcon0_open(u32 sel, struct disp_panel_para *panel)
{
    tcon0_out_to_gpio(sel);

    /*clear tcon_irq_flag except FSYNC_INT_INV*/
    lcd_dev[sel]->tcon_gint0.bits.tcon_irq_flag &= 0x00000004;
    if ((panel->lcd_if == LCD_IF_HV) || (panel->lcd_if == LCD_IF_LVDS) ||
        (panel->lcd_if == LCD_IF_EXT_DSI) ||
        (panel->lcd_if == LCD_IF_VDPO)) {
        lcd_dev[sel]->tcon0_dclk.bits.tcon0_dclk_en = 0xf;
        lcd_dev[sel]->tcon0_ctl.bits.tcon0_en = 1;
        tcon_irq_enable(sel, LCD_IRQ_TCON0_VBLK);
    } else if (panel->lcd_if == LCD_IF_CPU) {
        lcd_dev[sel]->tcon0_ctl.bits.tcon0_en = 1;
        if ((panel->lcd_cpu_mode == 0)
            && (panel->lcd_if == LCD_IF_CPU))
            tcon_irq_enable(sel, LCD_IRQ_TCON0_VBLK);
        else {
            lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 1;
            tcon_irq_enable(sel, LCD_IRQ_TCON0_CNTR);
        }
    } else if (panel->lcd_if == LCD_IF_DSI) {
        lcd_dev[sel]->tcon0_dclk.bits.tcon0_dclk_en = 0xf;
        lcd_dev[sel]->tcon0_ctl.bits.tcon0_en = 1;
        if (panel->lcd_dsi_if == LCD_DSI_IF_COMMAND_MODE)
            tcon_irq_enable(sel, LCD_IRQ_TCON0_CNTR);
#if defined(SUPPORT_DSI) && !defined(DSI_VERSION_40)
        else if (panel->lcd_dsi_if == LCD_DSI_IF_VIDEO_MODE ||
             panel->lcd_dsi_if == LCD_DSI_IF_BURST_MODE) {
            tcon_irq_enable(sel, LCD_IRQ_TCON0_VBLK);
            lcd_dev[sel]->tcon0_dclk.bits.tcon0_dclk_en = 0xf;
        }
#endif
        else
            lcd_dev[sel]->tcon0_dclk.bits.tcon0_dclk_en = 0xf;
    }

    return 0;
}

s32 tcon0_close(u32 sel)
{
    tcon_irq_disable(sel, LCD_IRQ_TCON0_CNTR);
    tcon_irq_disable(sel, LCD_IRQ_TCON0_VBLK);
    tcon_irq_disable(sel, LCD_IRQ_TCON0_TRIF);
    /* while (lcd_dev[sel]->tcon0_cpu_ctl.bits.trigger_start); */
    lcd_dev[sel]->tcon0_ctl.bits.tcon0_en = 0;
    lcd_dev[sel]->tcon0_dclk.bits.tcon0_dclk_en = 0x0;
#if defined(HAVE_DEVICE_COMMON_MODULE) && defined(SUPPORT_DSI)
    tcon0_dsi_clk_enable(sel, 0);
    if (lcd_dev[sel]->tcon_sync_ctl.bits.dsi_num &&
        sel + 1 < DEVICE_DSI_NUM)
        tcon0_dsi_clk_enable(sel + 1, 0);
#endif

#ifdef CONFIG_EINK_PANEL_USED
    /* eink panel no need to delay, for faster display */
#else
    disp_delay_ms(30);
#endif


    return 1;
}

s32 tcon0_simple_close(u32 sel)
{

    tcon_irq_disable(sel, LCD_IRQ_TCON0_CNTR);
    tcon_irq_disable(sel, LCD_IRQ_TCON0_VBLK);
    tcon_irq_disable(sel, LCD_IRQ_TCON0_TRIF);

    lcd_dev[sel]->tcon0_ctl.bits.tcon0_en = 0;
    lcd_dev[sel]->tcon0_dclk.bits.tcon0_dclk_en = 0x0;

    return 1;
}

s32 tcon0_simple_open(u32 sel)
{
    tcon_irq_enable(sel, LCD_IRQ_TCON0_VBLK);
    lcd_dev[sel]->tcon0_dclk.bits.tcon0_dclk_en = 0xf;
    lcd_dev[sel]->tcon0_ctl.bits.tcon0_en = 1;

    return 1;
}
static s32 tcon0_cfg_mode_auto(u32 sel, struct disp_panel_para *panel)
{
    s32 start_delay;

    lcd_dev[sel]->tcon0_basic0.bits.x = panel->lcd_x - 1;
    lcd_dev[sel]->tcon0_basic0.bits.y = panel->lcd_y - 1;
    lcd_dev[sel]->tcon0_basic1.bits.ht = panel->lcd_ht - 1;
    lcd_dev[sel]->tcon0_basic1.bits.hbp =
        (panel->lcd_hbp == 0) ? 0 : panel->lcd_hbp - 1;
    lcd_dev[sel]->tcon0_basic2.bits.vt = panel->lcd_vt * 2;
    lcd_dev[sel]->tcon0_basic2.bits.vbp =
        (panel->lcd_vbp == 0) ? 0 : panel->lcd_vbp - 1;
    lcd_dev[sel]->tcon0_basic3.bits.hspw =
        (panel->lcd_hspw == 0) ? 0 : panel->lcd_hspw - 1;
    lcd_dev[sel]->tcon0_basic3.bits.vspw =
        (panel->lcd_vspw == 0) ? 0 : panel->lcd_vspw - 1;
    start_delay = panel->lcd_vt - panel->lcd_y - 8;
    if (panel->lcd_hv_if == LCD_HV_IF_CCIR656_2CYC) {
        if (panel->lcd_interlace) {
            lcd_dev[sel]->tcon0_basic0.bits.y =
                panel->lcd_y / 2 - 1;
            lcd_dev[sel]->tcon0_basic2.bits.vt =
                (panel->lcd_hv_syuv_fdly ==
                 LCD_HV_SRGB_FDLY_2LINE) ? 525 : 625;
            start_delay = panel->lcd_vt / 2 - panel->lcd_y / 2 - 10;
        } else {
            lcd_dev[sel]->tcon0_basic0.bits.y = panel->lcd_y - 1;
            lcd_dev[sel]->tcon0_basic2.bits.vt =
                (panel->lcd_hv_syuv_fdly ==
                 LCD_HV_SRGB_FDLY_2LINE) ? 1050 : 1250;
        }

        lcd_dev[sel]->tcon0_basic1.bits.ht =
            (panel->lcd_ht == 0) ? 0 : (panel->lcd_ht * 2 - 1);
        lcd_dev[sel]->tcon0_basic1.bits.hbp =
            (panel->lcd_hbp == 0) ? 0 : (panel->lcd_hbp * 2 - 1);
        lcd_dev[sel]->tcon0_basic3.bits.hspw =
            (panel->lcd_hspw == 0) ? 0 : (panel->lcd_hspw * 2 - 1);
    }
    if (start_delay < 10)
        start_delay = 10;
    else if (start_delay > 31)
        start_delay = 31;

    lcd_dev[sel]->tcon0_ctl.bits.start_delay = start_delay;

    if (panel->lcd_if == LCD_IF_CPU)
        lcd_dev[sel]->tcon0_dclk.bits.tcon0_dclk_en = 0xf;

    return 0;
}

static s32 tcon0_cfg_mode_tri(u32 sel, struct disp_panel_para *panel)
{
    u32 start_delay = 0;
    u32 de_clk_rate = de_get_clk_rate() / 1000000;

    de_clk_rate = (de_clk_rate == 0) ? 250 : de_clk_rate;

    lcd_dev[sel]->tcon0_basic0.bits.x = panel->lcd_x - 1;
    lcd_dev[sel]->tcon0_basic0.bits.y = panel->lcd_y - 1;
    lcd_dev[sel]->tcon0_cpu_tri0.bits.block_size = panel->lcd_x - 1;
    lcd_dev[sel]->tcon0_cpu_tri1.bits.block_num = panel->lcd_y - 1;
    lcd_dev[sel]->tcon0_cpu_tri2.bits.trans_start_mode = 0;
    lcd_dev[sel]->tcon0_cpu_tri2.bits.sync_mode = 0;
    start_delay = (panel->lcd_vt - panel->lcd_y - 8 - 1)
        * panel->lcd_ht * de_clk_rate / panel->lcd_dclk_freq / 8;
    lcd_dev[sel]->tcon0_cpu_tri2.bits.start_delay = start_delay;

    lcd_dev[sel]->tcon0_cpu_ctl.bits.trigger_fifo_en = 1;
    lcd_dev[sel]->tcon0_cpu_ctl.bits.trigger_en = 1;
    /* lcd_dev[sel]->tcon0_cpu_ctl.bits.flush = 1; */
    lcd_dev[sel]->tcon0_ctl.bits.tcon0_en = 1;
    lcd_dev[sel]->tcon_gctl.bits.tcon_en = 1;
    lcd_dev[sel]->tcon_gctl.bits.pad_sel = 1;

    if ((panel->lcd_if == LCD_IF_CPU)
        || (panel->lcd_if == LCD_IF_DSI
        && panel->lcd_dsi_if == LCD_DSI_IF_COMMAND_MODE)) {
        lcd_dev[sel]->tcon0_dclk.bits.tcon0_dclk_en = 0xf;
        lcd_dev[sel]->tcon0_cpu_tri0.bits.block_space =
            panel->lcd_ht - panel->lcd_x - 1;
        lcd_dev[sel]->tcon0_cpu_tri2.bits.trans_start_set =
            panel->lcd_x - 1;
    } else if ((panel->lcd_if == LCD_IF_DSI)
           && (panel->lcd_dsi_if == LCD_DSI_IF_VIDEO_MODE
               || panel->lcd_dsi_if == LCD_DSI_IF_BURST_MODE)) {
#if defined(SUPPORT_DSI)
        lcd_dev[sel]->tcon0_cpu_tri0.bits.block_space =
            panel->lcd_ht * dsi_pixel_bits[panel->lcd_dsi_format] /
            (tcon_div * panel->lcd_dsi_lane) - panel->lcd_x - 40;
        lcd_dev[sel]->tcon0_cpu_tri2.bits.trans_start_set = 10;
#endif
    }
    if (panel->lcd_fresh_mode == 1) {
        u32 lcd_te;

        lcd_te = (panel->lcd_if == LCD_IF_CPU) ?
            panel->lcd_cpu_te : panel->lcd_dsi_te;
        /*
         * It's running at falling mode when lcd_te eq 2
         *  and rising mode when eq 1
         */
        if (lcd_te == 2)
            lcd_dev[sel]->tcon0_cpu_tri3.bits.tri_int_mode = 3;
        else if (lcd_te == 1)
            lcd_dev[sel]->tcon0_cpu_tri3.bits.tri_int_mode = 2;
        else {
            u32 cntr_set = panel->lcd_ht * panel->lcd_vt / 4;
            u32 cntr_n, cntr_m;

            for (cntr_m = 1; cntr_m < 256; cntr_m++) {
                if ((cntr_set / cntr_m) < 65535) {
                    cntr_n = cntr_set / cntr_m;
                    lcd_dev[sel]->tcon0_cpu_tri3.bits.
                        counter_m = cntr_m - 1;
                    lcd_dev[sel]->tcon0_cpu_tri3.bits.
                        counter_n = cntr_n - 1;
                    lcd_dev[sel]->tcon0_cpu_tri3.bits.
                        tri_int_mode = 1;
                    return 0;
                }
            }
            lcd_dev[sel]->tcon0_cpu_tri3.bits.tri_int_mode = 0;
            return -1;
        }
    }

    return 0;
}

s32 tcon0_cfg(u32 sel, struct disp_panel_para *panel)
{
    if ((panel->lcd_if == LCD_IF_HV) || (panel->lcd_if == LCD_IF_EXT_DSI) ||
        (panel->lcd_if == LCD_IF_VDPO)) {
#ifdef CONFIG_EINK_PANEL_USED
        lcd_dev[sel]->tcon0_ctl.bits.tcon0_if = 2;
#else
        lcd_dev[sel]->tcon0_ctl.bits.tcon0_if = 0;
#endif
        lcd_dev[sel]->tcon0_hv_ctl.bits.hv_mode = panel->lcd_hv_if;
        lcd_dev[sel]->tcon0_hv_ctl.bits.srgb_seq =
            panel->lcd_hv_srgb_seq;
        lcd_dev[sel]->tcon0_hv_ctl.bits.syuv_seq =
            panel->lcd_hv_syuv_seq;
        lcd_dev[sel]->tcon0_hv_ctl.bits.syuv_fdly =
            panel->lcd_hv_syuv_fdly;
        panel->lcd_fresh_mode = 0;
        lcd_dev[sel]->tcon0_hv_ctl.bits.ccir_csc_dis = panel->input_csc;
        tcon0_cfg_mode_auto(sel, panel);
        if (panel->lcd_if == LCD_IF_VDPO) {
            vdpo_src_sel(0, 0); /*use tcon_lcd0*/
        }
    } else if (panel->lcd_if == LCD_IF_LVDS) {
        lcd_dev[sel]->tcon0_ctl.bits.tcon0_if = 0;
        lcd_dev[sel]->tcon0_hv_ctl.bits.hv_mode = 0;
        lcd_dev[sel]->tcon0_lvds_ctl.bits.tcon0_lvds_link =
            panel->lcd_lvds_if;
        lcd_dev[sel]->tcon0_lvds_ctl.bits.tcon0_lvds_bitwidth =
            panel->lcd_lvds_colordepth;
        lcd_dev[sel]->tcon0_lvds_ctl.bits.tcon0_lvds_mode =
            panel->lcd_lvds_mode;
        lcd_dev[sel]->tcon0_lvds_ctl.bits.tcon0_lvds_debug_en = 0;
        lcd_dev[sel]->tcon0_lvds_ctl.bits.tcon0_lvds_correct_mode = 0;
        lcd_dev[sel]->tcon0_lvds_ctl.bits.tcon0_lvds_dir = 0;
        lcd_dev[sel]->tcon0_lvds_ctl.bits.tcon0_lvds_clk_sel = 1;
#if defined(LVDS_REVERT)
        lcd_dev[sel]->tcon0_lvds_ctl.bits.tcon0_lvds_data_revert = 0xf;
        lcd_dev[sel]->tcon0_lvds_ctl.bits.tcon0_lvds_clk_revert = 0x1;
#endif
        panel->lcd_fresh_mode = 0;
        tcon0_cfg_mode_auto(sel, panel);
    } else if (panel->lcd_if == LCD_IF_CPU) {
        lcd_dev[sel]->tcon0_ctl.bits.tcon0_if = 1;
        lcd_dev[sel]->tcon0_cpu_ctl.bits.cpu_mode = panel->lcd_cpu_if;
        /* why delete ?
         * lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 1;
         */
        lcd_dev[sel]->tcon_ecfifo_ctl.bits.ecc_fifo_setting = (1 << 3);
        panel->lcd_fresh_mode = 1;
        if (panel->lcd_cpu_mode == 0)
            tcon0_cfg_mode_auto(sel, panel);
        else
            tcon0_cfg_mode_tri(sel, panel);
        lcd_dev[sel]->tcon0_cpu_tri4.bits.en = 0;
    } else if (panel->lcd_if == LCD_IF_DSI) {
        lcd_dev[sel]->tcon_sync_ctl.bits.dsi_num =
            (panel->lcd_tcon_mode == DISP_TCON_DUAL_DSI) ? 1 : 0;
        lcd_dev[sel]->tcon0_3d_fifo.bits.fifo_3d_setting =
            1; /*normal fifo*/

        /*sync setting between master lcd and slave lcd*/
        if (panel->lcd_tcon_mode < DISP_TCON_DUAL_DSI) {
            lcd_dev[sel]->tcon_sync_ctl.bits.master_slave =
                (panel->lcd_tcon_mode == DISP_TCON_SLAVE_MODE) ? 1
                                       : 0;

            if (panel->lcd_tcon_mode <
                DISP_TCON_SLAVE_MODE) { /*master tcon*/
                lcd_dev[sel]->tcon_sync_pos.bits.sync_line_num =
                    panel->lcd_sync_line_num;
                lcd_dev[sel]
                    ->tcon_sync_pos.bits.sync_pixel_num =
                    panel->lcd_sync_pixel_num;
                lcd_dev[sel]
                    ->tcon_sync_ctl.bits.ctrl_sync_mode =
                    (panel->lcd_tcon_mode ==
                     DISP_TCON_MASTER_SYNC_EVERY_FRAME)
                    ? 1
                    : 0;
            } else { /*slave tcon*/
                lcd_dev[sel]->tcon_slave_stop.bits.stop_val =
                    panel->lcd_slave_stop_pos;
            }
        } else {
            /*enable 3D FIFO*/
            lcd_dev[sel]->tcon0_3d_fifo.bits.fifo_3d_setting = 2;
            lcd_dev[sel]
                ->tcon0_3d_fifo.bits.fifo_3d_half_line_size =
                panel->lcd_x / 2 - 1;
            lcd_dev[sel]->tcon0_3d_fifo.bits.fifo_3d_bist_en = 0;
        }
#if defined(SUPPORT_DSI) && !defined(DSI_VERSION_40)
        if (panel->lcd_dsi_if == LCD_DSI_IF_VIDEO_MODE ||
            panel->lcd_dsi_if == LCD_DSI_IF_BURST_MODE) {
            panel->lcd_fresh_mode = 0;
            lcd_dev[sel]->tcon0_ctl.bits.tcon0_if = 0;
            lcd_dev[sel]->tcon0_hv_ctl.bits.hv_mode =
                panel->lcd_hv_if;
            lcd_dev[sel]->tcon0_hv_ctl.bits.srgb_seq =
                panel->lcd_hv_srgb_seq;
            lcd_dev[sel]->tcon0_hv_ctl.bits.syuv_seq =
                panel->lcd_hv_syuv_seq;
            lcd_dev[sel]->tcon0_hv_ctl.bits.syuv_fdly =
                panel->lcd_hv_syuv_fdly;
            panel->lcd_fresh_mode = 0;
            lcd_dev[sel]->tcon0_hv_ctl.bits.res0 = 0;
            lcd_dev[sel]->tcon0_hv_ctl.bits.ccir_csc_dis = 1;
            tcon0_cfg_mode_auto(sel, panel);
#if defined(HAVE_DEVICE_COMMON_MODULE)
            if (panel->lcd_tcon_mode == DISP_TCON_DUAL_DSI) {
                dsi_src_sel(0, 0); /*same source*/
                dsi_src_sel(1, 1);
                tcon0_dsi_clk_enable(0, 1);
                tcon0_dsi_clk_enable(1, 1);
            } else {
                dsi_src_sel(sel, 0); /*different source*/
                tcon0_dsi_clk_enable(sel, 1);
            }
#endif
        } else
#endif
        {
            /*dsi command mode*/
            lcd_dev[sel]->tcon0_ctl.bits.tcon0_if = 1;
#if defined(DSI_VERSION_40)
            lcd_dev[sel]->tcon0_cpu_ctl.bits.cpu_mode = MODE_DSI;
#else
            lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 1;
            lcd_dev[sel]->tcon0_cpu_ctl.bits.flush = 1;
            lcd_dev[sel]->tcon0_cpu_ctl.bits.cpu_mode = MODE0_16BIT;
#endif
            lcd_dev[sel]->tcon_ecfifo_ctl.bits.ecc_fifo_setting =
                (1 << 3);
            panel->lcd_fresh_mode =
                (panel->lcd_dsi_if == LCD_DSI_IF_COMMAND_MODE) ? 1
                                       : 0;
            tcon0_cfg_mode_tri(sel, panel);
#if defined(DSI_VERSION_28)
            lcd_dev[sel]->tcon0_cpu_tri4.bits.data = 0x460;
            lcd_dev[sel]->tcon0_cpu_tri4.bits.a1 = 0;
            lcd_dev[sel]->tcon0_cpu_tri5.bits.data = 0x4e0;
            lcd_dev[sel]->tcon0_cpu_tri5.bits.a1 = 0;
            lcd_dev[sel]->tcon0_cpu_tri4.bits.en = 1;
#endif
#if defined(HAVE_DEVICE_COMMON_MODULE) && defined(SUPPORT_DSI)
            if (panel->lcd_tcon_mode == DISP_TCON_DUAL_DSI) {
                tcon0_dsi_clk_enable(0, 1);
                tcon0_dsi_clk_enable(1, 1);
            } else
                tcon0_dsi_clk_enable(sel, 1);
#endif
        }
    }

    tcon0_frm(sel, panel->lcd_frm);

    /*fsync config*/
    lcd_dev[sel]->fsync_gen_ctrl.bits.fsync_gen_en = panel->lcd_fsync_en;
    tcon_set_fsync_pol(sel, panel->lcd_fsync_pol);

    /*follow vsync's pol*/
    lcd_dev[sel]->fsync_gen_ctrl.bits.sel_vsync_en =
        lcd_dev[sel]->tcon1_io_pol.bits.io0_inv;

    if (panel->lcd_fsync_act_time) {
        tcon_set_fsync_active_time(sel, panel->lcd_fsync_act_time);
    } else {
        lcd_dev[sel]->fsync_gen_dly.bits.sensor_act0_time =
            panel->lcd_ht / 4;
        lcd_dev[sel]->fsync_gen_dly.bits.sensor_act1_time =
            panel->lcd_ht / 4;
    }

    lcd_dev[sel]->fsync_gen_ctrl.bits.sensor_dis_time =
        (panel->lcd_fsync_dis_time) ? panel->lcd_fsync_dis_time : 1;

    lcd_dev[sel]->tcon0_ctl.bits.rb_swap = panel->lcd_rb_swap;
    lcd_dev[sel]->tcon0_io_tri.bits.rgb_endian = panel->lcd_rgb_endian;
    lcd_dev[sel]->tcon_volume_ctl.bits.safe_period_mode = 3;
    lcd_dev[sel]->tcon_volume_ctl.bits.safe_period_fifo_num =
        panel->lcd_dclk_freq * 15;
    lcd_dev[sel]->tcon0_io_pol.bits.sync_inv = panel->lcd_hv_sync_polarity;
    lcd_dev[sel]->fsync_gen_ctrl.bits.hsync_pol_sel =
        !panel->lcd_hv_sync_polarity;
    switch (panel->lcd_hv_clk_phase) {
    case 0:
        lcd_dev[sel]->tcon0_io_pol.bits.clk_inv = 0;
        lcd_dev[sel]->tcon0_io_pol.bits.dclk_sel = 0;
        break;
    case 1:
        lcd_dev[sel]->tcon0_io_pol.bits.clk_inv = 0;
        lcd_dev[sel]->tcon0_io_pol.bits.dclk_sel = 2;
        break;
    case 2:
        lcd_dev[sel]->tcon0_io_pol.bits.clk_inv = 1;
        lcd_dev[sel]->tcon0_io_pol.bits.dclk_sel = 0;
        break;
    case 3:
        lcd_dev[sel]->tcon0_io_pol.bits.clk_inv = 1;
        lcd_dev[sel]->tcon0_io_pol.bits.dclk_sel = 2;
        break;
    default:
        lcd_dev[sel]->tcon0_io_pol.bits.clk_inv = 0;
        lcd_dev[sel]->tcon0_io_pol.bits.dclk_sel = 0;
        break;
    }
    if (panel->lcd_hv_data_polarity)
        lcd_dev[sel]->tcon0_io_pol.bits.data_inv = 0xffffff;

    if (panel->lcd_fresh_mode == 1) {
        u32 lcd_te;

        lcd_te =
            (panel->lcd_if ==
             LCD_IF_CPU) ? panel->lcd_cpu_te : panel->lcd_dsi_te;
        lcd_dev[sel]->tcon0_io_tri.bits.io0_output_tri_en =
            (lcd_te == 0) ? 0 : 1;
    } else {
        lcd_dev[sel]->tcon0_io_tri.bits.io0_output_tri_en = 0;
    }
    lcd_dev[sel]->tcon0_io_tri.bits.io1_output_tri_en = 0;
    lcd_dev[sel]->tcon0_io_tri.bits.io2_output_tri_en = 0;
    lcd_dev[sel]->tcon0_io_tri.bits.io3_output_tri_en = 0;
    lcd_dev[sel]->tcon0_io_tri.bits.data_output_tri_en = 0;

    return 0;
}

s32 tcon0_cfg_ext(u32 sel, struct panel_extend_para *extend_panel)
{
    tcon_gamma(sel, extend_panel->lcd_gamma_en,
           extend_panel->lcd_gamma_tbl);
    tcon_cmap(sel, extend_panel->lcd_cmap_en, extend_panel->lcd_cmap_tbl);

    return 0;
}

s32 tcon0_tri_busy(u32 sel)
{
    return lcd_dev[sel]->tcon0_cpu_ctl.bits.trigger_start;
}

s32 tcon0_cpu_set_auto_mode(u32 sel)
{
    /* trigger mode 0 */
    lcd_dev[sel]->tcon0_cpu_ctl.bits.auto_ = 1;
    /* trigger mode 1 */
    lcd_dev[sel]->tcon0_cpu_ctl.bits.flush = 0;
    return 0;
}

s32 tcon0_tri_start(u32 sel)
{
    /* don't need ?
     * lcd_dev[sel]->tcon0_cpu_ctl.bits.trigger_start = 0;
     */
    lcd_dev[sel]->tcon0_cpu_ctl.bits.trigger_start = 1;
    return 0;
}

s32 tcon0_frm(u32 sel, u32 mode)
{
    if (mode == LCD_FRM_BYPASS) {
        lcd_dev[sel]->tcon0_frm_ctl.bits.tcon0_frm_en = 0;
        return 0;
    }
    lcd_dev[sel]->tcon0_frm_seed_pr.bits.seed_value = 1;
    lcd_dev[sel]->tcon0_frm_seed_pg.bits.seed_value = 3;
    lcd_dev[sel]->tcon0_frm_seed_pb.bits.seed_value = 5;
    lcd_dev[sel]->tcon0_frm_seed_lr.bits.seed_value = 7;
    lcd_dev[sel]->tcon0_frm_seed_lg.bits.seed_value = 11;
    lcd_dev[sel]->tcon0_frm_seed_lb.bits.seed_value = 13;
    lcd_dev[sel]->tcon0_frm_tbl_0.bits.frm_table_value = 0x01010000;
    lcd_dev[sel]->tcon0_frm_tbl_1.bits.frm_table_value = 0x15151111;
    lcd_dev[sel]->tcon0_frm_tbl_2.bits.frm_table_value = 0x57575555;
    lcd_dev[sel]->tcon0_frm_tbl_3.bits.frm_table_value = 0x7f7f7777;
    if (mode == LCD_FRM_RGB666) {
        lcd_dev[sel]->tcon0_frm_ctl.bits.tcon0_frm_mode_r = 0;
        lcd_dev[sel]->tcon0_frm_ctl.bits.tcon0_frm_mode_g = 0;
        lcd_dev[sel]->tcon0_frm_ctl.bits.tcon0_frm_mode_b = 0;
    } else if (mode == LCD_FRM_RGB565) {
        lcd_dev[sel]->tcon0_frm_ctl.bits.tcon0_frm_mode_r = 1;
        lcd_dev[sel]->tcon0_frm_ctl.bits.tcon0_frm_mode_g = 0;
        lcd_dev[sel]->tcon0_frm_ctl.bits.tcon0_frm_mode_b = 1;
    }
    lcd_dev[sel]->tcon0_frm_ctl.bits.tcon0_frm_en = 1;
    return 0;
}

u32 tcon0_cpu_16b_to_24b(u32 value)
{
    return ((value & 0xfc00) << 8)
        | ((value & 0x0300) << 6)
        | ((value & 0x00e0) << 5)
        | ((value & 0x001f) << 3);
}

u32 tcon0_cpu_24b_to_16b(u32 value)
{
    return ((value & 0xfc0000) >> 8)
        | ((value & 0x00c000) >> 6)
        | ((value & 0x001c00) >> 5)
        | ((value & 0x0000f8) >> 3);
}

u32 tcon0_cpu_busy(u32 sel)
{
    if (lcd_dev[sel]->tcon0_cpu_ctl.bits.wr_flag
        || lcd_dev[sel]->tcon0_cpu_ctl.bits.rd_flag)
        return 1;
    else
        return 0;
}

#if defined(CONFIG_ARCH_SUN8IW19P1)
s32 tcon0_cpu_wr_24b_index(u32 sel, u32 index)
{
    u32 count = 0;

    if (lcd_dev[sel]->tcon0_io_pol.bits.data_inv == 0xffffff)
        index = ~index;

    while ((tcon0_cpu_busy(sel)) && (count < 50)) {
        count++;
        disp_delay_us(100);
    }
    lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 0;
    /*
     * 0: write index
     * 1: write param
     */
    lcd_dev[sel]->tcon0_cpu_ctl.bits.ca = 0;
    lcd_dev[sel]->tcon0_cpu_wr.bits.data_wr = index;
    return 0;
}

s32 tcon0_cpu_wr_24b_data(u32 sel, u32 data)
{
    u32 count = 0;

    if (lcd_dev[sel]->tcon0_io_pol.bits.data_inv == 0xffffff)
        data = ~data;

    while ((tcon0_cpu_busy(sel)) && (count < 50)) {
        count++;
        disp_delay_us(100);
    }
    /*
     * 0: write index
     * 1: write param
     */
    lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 0;
    lcd_dev[sel]->tcon0_cpu_ctl.bits.ca = 1;
    lcd_dev[sel]->tcon0_cpu_wr.bits.data_wr = data;
    return 0;
}
#else
s32 tcon0_cpu_wr_24b_index(u32 sel, u32 index)
{
    u32 count = 0;

    if (lcd_dev[sel]->tcon0_io_pol.bits.data_inv == 0xffffff)
        index = ~index;

    while ((tcon0_cpu_busy(sel)) && (count < 50)) {
        count++;
        disp_delay_us(100);
    }
    lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 0;
    /*
     * 0: write index
     * 1: write param
     */
    lcd_dev[sel]->tcon0_cpu_ctl.bits.ca = 0;
    lcd_dev[sel]->tcon0_cpu_wr.bits.data_wr = index;
    lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 1;
    return 0;
}

s32 tcon0_cpu_wr_24b_data(u32 sel, u32 data)
{
    u32 count = 0;

    if (lcd_dev[sel]->tcon0_io_pol.bits.data_inv == 0xffffff)
        data = ~data;

    while ((tcon0_cpu_busy(sel)) && (count < 50)) {
        count++;
        disp_delay_us(100);
    }
    /*
     * 0: write index
     * 1: write param
     */
    lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 0;
    lcd_dev[sel]->tcon0_cpu_ctl.bits.ca = 1;
    lcd_dev[sel]->tcon0_cpu_wr.bits.data_wr = data;
    lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 1;
    return 0;
}
#endif

s32 tcon0_cpu_wr_24b(u32 sel, u32 index, u32 data)
{
    tcon0_cpu_wr_24b_index(sel, index);
    tcon0_cpu_wr_24b_data(sel, data);
    return 0;
}

s32 tcon0_cpu_rd_24b(u32 sel, u32 index, u32 *data)
{
    return -1;
}

s32 tcon0_cpu_rd_24b_data(u32 sel, u32 index, u32 *data, u32 size)
{
    u32 count = 0;
    u32 tmp;
    int i = 0;

    tcon0_cpu_wr_24b_index(sel, tcon0_cpu_16b_to_24b(index));

    count = 0;
    while ((tcon0_cpu_busy(sel)) && (count < 50)) {
        count++;
        disp_delay_us(100);
    }

    lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 0;
    lcd_dev[sel]->tcon0_cpu_ctl.bits.ca = 1;
    tmp = lcd_dev[sel]->tcon0_cpu_rd.bits.data_rd0;
    lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 1;

    for (i = 0; i < size; i++) {
        count = 0;
        while ((tcon0_cpu_busy(sel)) && (count < 50)) {
            count++;
            disp_delay_us(100);
        }

        lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 0;
        lcd_dev[sel]->tcon0_cpu_ctl.bits.ca = 1;
        tmp = lcd_dev[sel]->tcon0_cpu_rd.bits.data_rd0;
        lcd_dev[sel]->tcon0_cpu_ctl.bits.da = 1;

        *data++ = tcon0_cpu_24b_to_16b(tmp);
    }

    return 0;
}

s32 tcon0_cpu_wr_16b(u32 sel, u32 index, u32 data)
{
    tcon0_cpu_wr_24b(sel, tcon0_cpu_16b_to_24b(index),
             tcon0_cpu_16b_to_24b(data));
    return 0;
}

s32 tcon0_cpu_wr_16b_index(u32 sel, u32 index)
{
    tcon0_cpu_wr_24b_index(sel, tcon0_cpu_16b_to_24b(index));
    return 0;
}

s32 tcon0_cpu_wr_16b_data(u32 sel, u32 data)
{
    tcon0_cpu_wr_24b_data(sel, tcon0_cpu_16b_to_24b(data));
    return 0;
}

s32 tcon0_cpu_rd_16b(u32 sel, u32 index, u32 *data)
{
    return -1;
}

/**
 * @name       :tcon0_cpu_wr_16b_multi
 * @brief      :write multiple data
 * @param[IN]  :sel:tcon index
 * @param[IN]  :para:pointer of data
 * @param[IN]  :para_num:number of para
 */
void tcon0_cpu_wr_16b_multi(u32 sel, u8 cmd, u8 *para, u32 para_num)
{
    u8 index = cmd;
    u8 *data_p = para;
    u16 i;

    tcon0_cpu_wr_16b_index(sel, index);
    for (i = 0; i < para_num; i++)
        tcon0_cpu_wr_16b_data(sel, *(data_p++));
}

/**
 * @name       :tcon0_cpu_wr_16b_multi
 * @brief      :write multiple data
 * @param[IN]  :sel:tcon index
 * @param[IN]  :para:pointer of data
 * @param[IN]  :para_num:number of para
 */
void tcon0_cpu_wr_24b_multi(u32 sel, u8 cmd, u8 *para, u32 para_num)
{
    u8 index = cmd;
    u8 *data_p = para;
    u16 i;

    tcon0_cpu_wr_24b_index(sel, index);
    for (i = 0; i < para_num; i++)
        tcon0_cpu_wr_24b_data(sel, *(data_p++));
}

s32 tcon0_set_dclk_div(u32 sel, u8 div)
{
    lcd_dev[sel]->tcon0_dclk.bits.tcon0_dclk_div = div;

    return 0;
}

u32 tcon0_get_dclk_div(u32 sel)
{
    return lcd_dev[sel]->tcon0_dclk.bits.tcon0_dclk_div;
}

s32 tcon1_open(u32 sel)
{
    lcd_dev[sel]->tcon1_ctl.bits.tcon1_en = 1;
    tcon_irq_enable(sel, LCD_IRQ_TCON1_VBLK);

    return 0;
}

s32 tcon1_close(u32 sel)
{
    lcd_dev[sel]->tcon1_ctl.bits.tcon1_en = 0;
    tcon_irq_disable(sel, LCD_IRQ_TCON0_VBLK);
    return 0;
}

s32 tcon_set_sync_pol(u32 sel, u32 ver_pol, u32 hor_pol)
{
#if defined(HAVE_DEVICE_COMMON_MODULE)
    lcd_dev[sel]->tcon0_io_pol.bits.sync_inv = hor_pol | (ver_pol << 1);
#else
    lcd_dev[sel]->tcon1_io_pol.bits.io0_inv = ver_pol;
    lcd_dev[sel]->tcon1_io_pol.bits.io1_inv = hor_pol;
#endif
    return 0;
}

#ifdef TCON_POL_CORRECT
u32 tcon1_cfg_correct(u32 sel, struct disp_video_timings *timing)
{
    if (timing->pixel_clk > 27000000)
        lcd_dev[sel]->tcon0_io_pol.bits.sync_inv
                = (timing->hor_sync_polarity ? 0 : 1)
                | ((timing->ver_sync_polarity ? 0 : 1) << 1);
    else
        lcd_dev[sel]->tcon0_io_pol.bits.sync_inv = 0;

    return 0;
}
#endif

s32 tcon1_cfg(u32 sel, struct disp_video_timings *timing)
{
    u32 start_delay;

    lcd_dev[sel]->tcon1_basic0.bits.x = timing->x_res - 1;
    lcd_dev[sel]->tcon1_basic0.bits.y =
        timing->y_res / (timing->b_interlace + 1) - 1;
    lcd_dev[sel]->tcon1_basic1.bits.ls_xo = timing->x_res - 1;
    lcd_dev[sel]->tcon1_basic1.bits.ls_yo = timing->y_res
        / (timing->b_interlace + 1) + timing->vactive_space - 1;
    lcd_dev[sel]->tcon1_basic2.bits.xo = timing->x_res - 1;
    lcd_dev[sel]->tcon1_basic2.bits.yo = timing->y_res
        / (timing->b_interlace + 1) + timing->vactive_space - 1;
    lcd_dev[sel]->tcon1_basic3.bits.ht = timing->hor_total_time - 1;
    lcd_dev[sel]->tcon1_basic3.bits.hbp =
        timing->hor_sync_time + timing->hor_back_porch - 1;
    lcd_dev[sel]->tcon1_basic4.bits.vt =
        timing->ver_total_time * (2 - timing->b_interlace) *
        ((timing->vactive_space != 0) ? 2 : 1);
    lcd_dev[sel]->tcon1_basic4.bits.vbp =
        timing->ver_sync_time + timing->ver_back_porch - 1;
    lcd_dev[sel]->tcon1_basic5.bits.hspw = timing->hor_sync_time - 1;
    lcd_dev[sel]->tcon1_basic5.bits.vspw = timing->ver_sync_time - 1;

#if defined(HAVE_DEVICE_COMMON_MODULE)
    lcd_dev[sel]->tcon0_io_pol.bits.sync_inv = timing->hor_sync_polarity
                    | (timing->ver_sync_polarity<<1);
#else
    lcd_dev[sel]->tcon1_io_pol.bits.io0_inv = timing->ver_sync_polarity;
    lcd_dev[sel]->tcon1_io_pol.bits.io1_inv = timing->hor_sync_polarity;
#endif
    lcd_dev[sel]->tcon1_ctl.bits.interlace_en = timing->b_interlace;
    lcd_dev[sel]->tcon_fill_start0.bits.fill_begin =
        (timing->ver_total_time + 1) << 12;
    lcd_dev[sel]->tcon_fill_end0.bits.fill_end =
        (timing->ver_total_time + timing->vactive_space) << 12;
    lcd_dev[sel]->tcon_fill_data0.bits.fill_value = 0;
    lcd_dev[sel]->tcon_fill_ctl.bits.tcon1_fill_en =
        (timing->vactive_space != 0) ? 1 : 0;
    start_delay = (timing->ver_total_time - timing->y_res)
        / (timing->b_interlace + 1) - 5;
    start_delay = (start_delay > 31) ? 31 : start_delay;
    lcd_dev[sel]->tcon1_ctl.bits.start_delay = start_delay;

    return 0;
}

s32 tcon1_cfg_ex(u32 sel, struct disp_panel_para *panel)
{
    struct disp_video_timings timing;

    memset(&timing, 0, sizeof(struct disp_video_timings));
    timing.x_res = panel->lcd_x;
    timing.y_res = panel->lcd_y;
    timing.hor_total_time = panel->lcd_ht;
    timing.hor_back_porch = panel->lcd_hbp - panel->lcd_hspw;
    timing.hor_front_porch = panel->lcd_ht - panel->lcd_x - panel->lcd_hbp;
    timing.hor_sync_time = panel->lcd_hspw;
    timing.hor_sync_polarity = 0;
    timing.ver_total_time = panel->lcd_vt;
    timing.ver_back_porch = panel->lcd_vbp - panel->lcd_vspw;
    timing.ver_front_porch = panel->lcd_vt - panel->lcd_y - panel->lcd_vbp;
    timing.ver_sync_time = panel->lcd_vspw;
    timing.ver_sync_polarity = 0;

    tcon1_cfg(sel, &timing);
    return 0;
}

s32 tcon1_hdmi_color_remap(u32 sel, u32 onoff, u32 is_yuv)
{
#if defined(CONFIG_ARCH_SUN8IW12)
    if (is_yuv) {
        lcd_dev[sel]->tcon_ceu_coef_rr.bits.value = 0;
        lcd_dev[sel]->tcon_ceu_coef_rg.bits.value = 0;
        lcd_dev[sel]->tcon_ceu_coef_rb.bits.value = 0x100;
        lcd_dev[sel]->tcon_ceu_coef_rc.bits.value = 0;

        lcd_dev[sel]->tcon_ceu_coef_gr.bits.value = 0;
        lcd_dev[sel]->tcon_ceu_coef_gg.bits.value = 0x100;
        lcd_dev[sel]->tcon_ceu_coef_gb.bits.value = 0;
        lcd_dev[sel]->tcon_ceu_coef_gc.bits.value = 0;

        lcd_dev[sel]->tcon_ceu_coef_br.bits.value = 0x100;
        lcd_dev[sel]->tcon_ceu_coef_bg.bits.value = 0;
        lcd_dev[sel]->tcon_ceu_coef_bb.bits.value = 0;
        lcd_dev[sel]->tcon_ceu_coef_bc.bits.value = 0;

        lcd_dev[sel]->tcon_ceu_coef_rv.bits.max = 255;
        lcd_dev[sel]->tcon_ceu_coef_rv.bits.min = 0;
        lcd_dev[sel]->tcon_ceu_coef_gv.bits.max = 255;
        lcd_dev[sel]->tcon_ceu_coef_gv.bits.min = 0;
        lcd_dev[sel]->tcon_ceu_coef_bv.bits.max = 255;
        lcd_dev[sel]->tcon_ceu_coef_bv.bits.min = 0;
    } else {
        lcd_dev[sel]->tcon_ceu_coef_rr.bits.value = 0x100;
        lcd_dev[sel]->tcon_ceu_coef_rg.bits.value = 0;
        lcd_dev[sel]->tcon_ceu_coef_rb.bits.value = 0;
        lcd_dev[sel]->tcon_ceu_coef_rc.bits.value = 0;

        lcd_dev[sel]->tcon_ceu_coef_gr.bits.value = 0;
        lcd_dev[sel]->tcon_ceu_coef_gg.bits.value = 0;
        lcd_dev[sel]->tcon_ceu_coef_gb.bits.value = 0x100;
        lcd_dev[sel]->tcon_ceu_coef_gc.bits.value = 0;

        lcd_dev[sel]->tcon_ceu_coef_br.bits.value = 0;
        lcd_dev[sel]->tcon_ceu_coef_bg.bits.value = 0x100;
        lcd_dev[sel]->tcon_ceu_coef_bb.bits.value = 0;
        lcd_dev[sel]->tcon_ceu_coef_bc.bits.value = 0;

        lcd_dev[sel]->tcon_ceu_coef_rv.bits.max = 255;
        lcd_dev[sel]->tcon_ceu_coef_rv.bits.min = 0;
        lcd_dev[sel]->tcon_ceu_coef_gv.bits.max = 255;
        lcd_dev[sel]->tcon_ceu_coef_gv.bits.min = 0;
        lcd_dev[sel]->tcon_ceu_coef_bv.bits.max = 255;
        lcd_dev[sel]->tcon_ceu_coef_bv.bits.min = 0;
    }
    lcd_dev[sel]->tcon_ceu_ctl.bits.ceu_en = 1;
#else
    /*
     * plane sequence:
     * v: 16~240
     * y: 16~235
     * u: 16~240
     */
    lcd_dev[sel]->tcon_ceu_coef_rr.bits.value = 0;
    lcd_dev[sel]->tcon_ceu_coef_rg.bits.value = 0;
    lcd_dev[sel]->tcon_ceu_coef_rb.bits.value = 0x100;
    lcd_dev[sel]->tcon_ceu_coef_rc.bits.value = 0;

    lcd_dev[sel]->tcon_ceu_coef_gr.bits.value = 0x100;
    lcd_dev[sel]->tcon_ceu_coef_gg.bits.value = 0;
    lcd_dev[sel]->tcon_ceu_coef_gb.bits.value = 0;
    lcd_dev[sel]->tcon_ceu_coef_gc.bits.value = 0;

    lcd_dev[sel]->tcon_ceu_coef_br.bits.value = 0;
    lcd_dev[sel]->tcon_ceu_coef_bg.bits.value = 0x100;
    lcd_dev[sel]->tcon_ceu_coef_bb.bits.value = 0;
    lcd_dev[sel]->tcon_ceu_coef_bc.bits.value = 0;

    lcd_dev[sel]->tcon_ceu_coef_rv.bits.max = 240;
    lcd_dev[sel]->tcon_ceu_coef_rv.bits.min = 16;
    lcd_dev[sel]->tcon_ceu_coef_gv.bits.max = 235;
    lcd_dev[sel]->tcon_ceu_coef_gv.bits.min = 16;
    lcd_dev[sel]->tcon_ceu_coef_bv.bits.max = 240;
    lcd_dev[sel]->tcon_ceu_coef_bv.bits.min = 16;
    if (onoff)
        lcd_dev[sel]->tcon_ceu_ctl.bits.ceu_en = 1;
    else
        lcd_dev[sel]->tcon_ceu_ctl.bits.ceu_en = 0;

#endif /*endif CONFIG_SUN8 */


    return 0;
}

s32 tcon1_yuv_range(u32 sel, u32 onoff)
{
    /*
     * plane sequence:
     * y: 16~235
     * u: 16~240
     * v: 16~240
     */
    lcd_dev[sel]->tcon_ceu_coef_rr.bits.value = 0x100;
    lcd_dev[sel]->tcon_ceu_coef_rg.bits.value = 0;
    lcd_dev[sel]->tcon_ceu_coef_rb.bits.value = 0;
    lcd_dev[sel]->tcon_ceu_coef_rc.bits.value = 0;

    lcd_dev[sel]->tcon_ceu_coef_gr.bits.value = 0;
    lcd_dev[sel]->tcon_ceu_coef_gg.bits.value = 0x100;
    lcd_dev[sel]->tcon_ceu_coef_gb.bits.value = 0;
    lcd_dev[sel]->tcon_ceu_coef_gc.bits.value = 0;

    lcd_dev[sel]->tcon_ceu_coef_br.bits.value = 0;
    lcd_dev[sel]->tcon_ceu_coef_bg.bits.value = 0;
    lcd_dev[sel]->tcon_ceu_coef_bb.bits.value = 0x100;
    lcd_dev[sel]->tcon_ceu_coef_bc.bits.value = 0;

    lcd_dev[sel]->tcon_ceu_coef_rv.bits.max = 235;
    lcd_dev[sel]->tcon_ceu_coef_rv.bits.min = 16;
    lcd_dev[sel]->tcon_ceu_coef_gv.bits.max = 240;
    lcd_dev[sel]->tcon_ceu_coef_gv.bits.min = 16;
    lcd_dev[sel]->tcon_ceu_coef_bv.bits.max = 240;
    lcd_dev[sel]->tcon_ceu_coef_bv.bits.min = 16;

    if (onoff)
        lcd_dev[sel]->tcon_ceu_ctl.bits.ceu_en = 1;
    else
        lcd_dev[sel]->tcon_ceu_ctl.bits.ceu_en = 0;

    return 0;
}

s32 tcon1_set_timming(u32 sel, struct disp_video_timings *timming)
{
    tcon1_cfg(sel, timming);
#if defined(HAVE_DEVICE_COMMON_MODULE)
    /* these register in tv_tcon1 maping to tcon1's tcon0 position */
    lcd_dev[sel]->tcon0_io_pol.bits.clk_inv = 0;
    lcd_dev[sel]->tcon0_io_tri.bits.io0_output_tri_en = 0;
    lcd_dev[sel]->tcon0_io_tri.bits.io1_output_tri_en = 0;
    lcd_dev[sel]->tcon0_io_tri.bits.io2_output_tri_en = 1;
    lcd_dev[sel]->tcon0_io_tri.bits.io3_output_tri_en = 1;
    lcd_dev[sel]->tcon0_io_tri.bits.data_output_tri_en = 0xffffff;
#else
    lcd_dev[sel]->tcon1_io_pol.bits.io2_inv = 1;
    lcd_dev[sel]->tcon1_io_tri.bits.io0_output_tri_en = 1;
    lcd_dev[sel]->tcon1_io_tri.bits.io1_output_tri_en = 1;
    lcd_dev[sel]->tcon1_io_tri.bits.io2_output_tri_en = 1;
    lcd_dev[sel]->tcon1_io_tri.bits.io3_output_tri_en = 1;
    lcd_dev[sel]->tcon1_io_tri.bits.data_output_tri_en = 0xffffff;
#endif
    /*select the source of hdmi*/
    lcd_dev[0]->tcon_mul_ctl.bits.hdmi_src = sel;
    return 0;
}

s32 tcon1_set_tv_mode(u32 sel, enum disp_output_type mode)
{
    return -1;
}

s32 tcon1_src_select(u32 sel, enum __lcd_src_t src, enum __de_perh_t de_no)
{
    if (src == LCD_SRC_BLUE) {
        lcd_dev[sel]->tcon1_ctl.bits.src_sel = 2;
    } else {
        lcd_dev[sel]->tcon1_ctl.bits.src_sel = src;
        if (src == LCD_SRC_DE)
            tcon_de_attach(sel, de_no);
    }
    return 0;
}

s32 tcon1_src_get(u32 sel)
{
    u32 src = 0;

    src = lcd_dev[sel]->tcon1_ctl.bits.src_sel;
    if (src == 2)
        return LCD_SRC_BLUE;

    src = lcd_dev[sel]->tcon1_ctl.bits.src_sel;
    return src;
}

static u32 tcon_ceu_range_cut(s32 *x_value, s32 x_min, s32 x_max)
{
    if (*x_value > x_max) {
        *x_value = x_max;
        return 1;
    } else if (*x_value < x_min) {
        *x_value = x_min;
        return 1;
    } else
        return 0;
}

static s32 tcon_ceu_reg_corr(s32 val, u32 bit)
{
    if (val >= 0)
        return val;
    else
        return (bit) | (u32) (-val);
}

static s32 tcon_ceu_rect_multi(s32 *dest, s32 *src1, s32 *src2)
{
    u32 x, y, z;
    __s64 val_int64;

    for (x = 0; x < 4; x++)
        for (y = 0; y < 4; y++) {
            val_int64 = 0;
            for (z = 0; z < 4; z++)
                val_int64 +=
                    (__s64) src1[x * 4 + z] * src2[z * 4 + y];
            val_int64 = (val_int64 + 512) >> 10;
            dest[x * 4 + y] = val_int64;
        }
    return 0;
}

static s32 tcon_ceu_rect_calc(s32 *p_rect, s32 b, s32 c, s32 s, s32 h)
{
    u8 const table_sin[91] = {
        0, 2, 4, 7, 9, 11, 13, 16, 18, 20,
        22, 24, 27, 29, 31, 33, 35, 37, 40, 42,
        44, 46, 48, 50, 52, 54, 56, 58, 60, 62,
        64, 66, 68, 70, 72, 73, 75, 77, 79, 81,
        82, 84, 86, 87, 89, 91, 92, 94, 95, 97,
        98, 99, 101, 102, 104, 105, 106, 107, 109, 110,
        111, 112, 113, 114, 115, 116, 117, 118, 119, 119,
        120, 121, 122, 122, 123, 124, 124, 125, 125, 126,
        126, 126, 127, 127, 127, 128, 128, 128, 128, 128,
        128
    };

    s32 const f_csh = 1024;
    s32 const f_sh = 8;
    s32 h1 = 0, h2 = 0, h3 = 0, h4 = 0;

    if (h >= 0 && h < 90) {
        h1 = table_sin[90 - h];
        h2 = table_sin[h];
        h3 = -table_sin[h];
        h4 = table_sin[90 - h];
    } else if (h >= 90 && h < 180) {
        h1 = -table_sin[h - 90];
        h2 = table_sin[180 - h];
        h3 = -table_sin[180 - h];
        h4 = -table_sin[h - 90];
    } else if (h >= 180 && h < 270) {
        h1 = -table_sin[270 - h];
        h2 = -table_sin[h - 180];
        h3 = table_sin[h - 180];
        h4 = -table_sin[270 - h];
    } else if (h >= 270 && h <= 360) {
        h1 = table_sin[h - 270];
        h2 = -table_sin[360 - h];
        h3 = table_sin[360 - h];
        h4 = table_sin[h - 270];
    }

    p_rect[0] = c * f_sh;
    p_rect[1] = 0;
    p_rect[2] = 0;
    p_rect[3] = -16 * c * f_sh + (b + 16) * f_csh;
    p_rect[4] = 0;
    p_rect[5] = (c * s * h1) >> 11;
    p_rect[6] = (c * s * h2) >> 11;
    p_rect[7] = 128 * (1 * f_csh - p_rect[5] - p_rect[6]);
    p_rect[8] = 0;
    p_rect[9] = (c * s * h3) >> 11;
    p_rect[10] = (c * s * h4) >> 11;
    p_rect[11] = 128 * (1 * f_csh - p_rect[9] - p_rect[10]);
    p_rect[12] = 0;
    p_rect[13] = 0;
    p_rect[14] = 0;
    p_rect[15] = 1024;
    return 0;
}

static s32 tcon_ceu_calc(u32 r2y_type, u32 cen_type, u32 y2r_type, s32 b, s32 c,
             s32 s, s32 h, s32 *p_coff)
{
    const s32 rect_1[16] = {
        1024, 0, 0, 0,
        0, 1024, 0, 0,
        0, 0, 1024, 0,
        0, 0, 0, 1024
    };

    const s32 rect_r2y_sd[16] = {
        263, 516, 100, 16384,
        -152, -298, 450, 131072,
        450, -377, -73, 131072,
        0, 0, 0, 1024
    };

    const s32 rect_r2y_hd[16] = {
        187, 629, 63, 16384,
        -103, -346, 450, 131072,
        450, -409, -41, 131072,
        0, 0, 0, 1024
    };

    const s32 rect_y2r_sd[16] = {
        1192, 0, 1634, -228262,
        1192, -400, -833, 138740,
        1192, 2066, 0, -283574,
        0, 0, 0, 1024
    };

    const s32 rect_y2r_hd[16] = {
        1192, 0, 1836, -254083,
        1192, -218, -547, 78840,
        1192, 2166, 0, -296288,
        0, 0, 0, 1024
    };

    s32 rect_tmp0[16];
    s32 rect_tmp1[16];

    s32 *p_rect = NULL;
    s32 *p_r2y = NULL;
    s32 *p_y2r = NULL;
    s32 *p_ceu = NULL;
    u32 i = 0;

    if (r2y_type) {
        if (r2y_type == 1)
            p_r2y = (s32 *) rect_r2y_sd;
        else if (r2y_type == 2)
            p_r2y = (s32 *) rect_r2y_hd;
        p_rect = p_r2y;
    } else
        p_rect = (s32 *) rect_1;

    if (cen_type) {
        tcon_ceu_range_cut(&b, -600, 600);
        tcon_ceu_range_cut(&c, 0, 300);
        tcon_ceu_range_cut(&s, 0, 300);
        tcon_ceu_range_cut(&h, 0, 360);
        p_ceu = rect_tmp1;
        tcon_ceu_rect_calc(p_ceu, b, c, s, h);
        tcon_ceu_rect_multi(rect_tmp0, p_ceu, p_rect);
        p_rect = rect_tmp0;
    }

    if (y2r_type) {
        if (y2r_type == 1)
            p_y2r = (s32 *) rect_y2r_sd;
        else if (y2r_type == 2)
            p_y2r = (s32 *) rect_y2r_hd;
        tcon_ceu_rect_multi(rect_tmp1, p_y2r, p_rect);
        p_rect = rect_tmp1;
    }

    for (i = 0; i < 12; i++)
        *(p_coff + i) = *(p_rect + i);

    return 0;
}

s32 tcon_ceu(u32 sel, u32 mode, s32 b, s32 c, s32 s, s32 h)
{
    s32 ceu_coff[12];
    u32 error;

    if (mode == 1) {
        tcon_ceu_calc(1, 1, 1, b, c, s, h, ceu_coff);
    } else if (mode == 2) {
        tcon_ceu_calc(0, 1, 0, b, c, s, h, ceu_coff);
    } else {
        lcd_dev[sel]->tcon_ceu_ctl.bits.ceu_en = 0;
        return 0;
    }

    ceu_coff[0] = (ceu_coff[0] + 2) >> 2;
    ceu_coff[1] = (ceu_coff[1] + 2) >> 2;
    ceu_coff[2] = (ceu_coff[2] + 2) >> 2;
    ceu_coff[3] = (ceu_coff[3] + 32) >> 6;
    ceu_coff[4] = (ceu_coff[4] + 2) >> 2;
    ceu_coff[5] = (ceu_coff[5] + 2) >> 2;
    ceu_coff[6] = (ceu_coff[6] + 2) >> 2;
    ceu_coff[7] = (ceu_coff[7] + 32) >> 6;
    ceu_coff[8] = (ceu_coff[8] + 2) >> 2;
    ceu_coff[9] = (ceu_coff[9] + 2) >> 2;
    ceu_coff[10] = (ceu_coff[10] + 2) >> 2;
    ceu_coff[11] = (ceu_coff[11] + 32) >> 6;

    error = 0;
    error |= tcon_ceu_range_cut(ceu_coff + 0, -4095, 4095);
    error |= tcon_ceu_range_cut(ceu_coff + 1, -4095, 4095);
    error |= tcon_ceu_range_cut(ceu_coff + 2, -4095, 4095);
    error |= tcon_ceu_range_cut(ceu_coff + 3, -262143, 262143);
    error |= tcon_ceu_range_cut(ceu_coff + 4, -4095, 4095);
    error |= tcon_ceu_range_cut(ceu_coff + 5, -4095, 4095);
    error |= tcon_ceu_range_cut(ceu_coff + 6, -4095, 4095);
    error |= tcon_ceu_range_cut(ceu_coff + 7, -262143, 262143);
    error |= tcon_ceu_range_cut(ceu_coff + 8, -4095, 4095);
    error |= tcon_ceu_range_cut(ceu_coff + 9, -4095, 4095);
    error |= tcon_ceu_range_cut(ceu_coff + 10, -4095, 4095);
    error |= tcon_ceu_range_cut(ceu_coff + 11, -262143, 262143);

    if (error) {
        lcd_dev[sel]->tcon_ceu_ctl.bits.ceu_en = 0;
        return -1;
    }

    if (mode == 1) {
        lcd_dev[sel]->tcon_ceu_coef_rv.bits.max = 255;
        lcd_dev[sel]->tcon_ceu_coef_rv.bits.min = 0;
        lcd_dev[sel]->tcon_ceu_coef_gv.bits.max = 255;
        lcd_dev[sel]->tcon_ceu_coef_gv.bits.min = 0;
        lcd_dev[sel]->tcon_ceu_coef_bv.bits.max = 255;
        lcd_dev[sel]->tcon_ceu_coef_bv.bits.min = 0;
    } else if (mode == 2) {
        lcd_dev[sel]->tcon_ceu_coef_rv.bits.max = 235;
        lcd_dev[sel]->tcon_ceu_coef_rv.bits.min = 16;
        lcd_dev[sel]->tcon_ceu_coef_gv.bits.max = 240;
        lcd_dev[sel]->tcon_ceu_coef_gv.bits.min = 16;
        lcd_dev[sel]->tcon_ceu_coef_bv.bits.max = 240;
        lcd_dev[sel]->tcon_ceu_coef_bv.bits.min = 16;
    }
    lcd_dev[sel]->tcon_ceu_coef_rr.bits.value =
        tcon_ceu_reg_corr(ceu_coff[0], 1 << 12);
    lcd_dev[sel]->tcon_ceu_coef_rg.bits.value =
        tcon_ceu_reg_corr(ceu_coff[1], 1 << 12);
    lcd_dev[sel]->tcon_ceu_coef_rb.bits.value =
        tcon_ceu_reg_corr(ceu_coff[2], 1 << 12);
    lcd_dev[sel]->tcon_ceu_coef_rc.bits.value =
        tcon_ceu_reg_corr(ceu_coff[3], 1 << 18);
    lcd_dev[sel]->tcon_ceu_coef_gr.bits.value =
        tcon_ceu_reg_corr(ceu_coff[0], 1 << 12);
    lcd_dev[sel]->tcon_ceu_coef_gg.bits.value =
        tcon_ceu_reg_corr(ceu_coff[1], 1 << 12);
    lcd_dev[sel]->tcon_ceu_coef_gb.bits.value =
        tcon_ceu_reg_corr(ceu_coff[2], 1 << 12);
    lcd_dev[sel]->tcon_ceu_coef_gc.bits.value =
        tcon_ceu_reg_corr(ceu_coff[3], 1 << 18);
    lcd_dev[sel]->tcon_ceu_coef_br.bits.value =
        tcon_ceu_reg_corr(ceu_coff[0], 1 << 12);
    lcd_dev[sel]->tcon_ceu_coef_bg.bits.value =
        tcon_ceu_reg_corr(ceu_coff[1], 1 << 12);
    lcd_dev[sel]->tcon_ceu_coef_bb.bits.value =
        tcon_ceu_reg_corr(ceu_coff[2], 1 << 12);
    lcd_dev[sel]->tcon_ceu_coef_bc.bits.value =
        tcon_ceu_reg_corr(ceu_coff[3], 1 << 18);
    lcd_dev[sel]->tcon_ceu_ctl.bits.ceu_en = 1;

    return 0;
}

s32 tcon_gamma(u32 sel, u32 en, u32 *gamma_tbl)
{
    u32 i;

    lcd_dev[sel]->tcon_gctl.bits.tcon_gamma_en = 0;
    if (en == 0)
        return 0;

    for (i = 0; i < 256; i++) {
        lcd_dev[sel]->tcon_gamma_tlb[i].bits.pixel = *gamma_tbl;
        gamma_tbl++;
    }

    lcd_dev[sel]->tcon_gctl.bits.tcon_gamma_en = en;
    return 0;
}

s32 tcon_cmap(u32 sel, u32 mode, u32 lcd_cmap_tbl[2][3][4])
{
    if (!(mode == 1)) {
        lcd_dev[sel]->tcon_cmap_ctl.bits.cmap_en = 0;
    } else {
        lcd_dev[sel]->tcon_cmap_odd0.bits.out0 =
            (lcd_cmap_tbl[0][2][0] << 8) | (lcd_cmap_tbl[0][1][0] << 4)
            | (lcd_cmap_tbl[0][0][0]);
        lcd_dev[sel]->tcon_cmap_odd0.bits.out1 =
            (lcd_cmap_tbl[0][2][1] << 8) | (lcd_cmap_tbl[0][1][1] << 4)
            | (lcd_cmap_tbl[0][0][1]);
        lcd_dev[sel]->tcon_cmap_odd1.bits.out2 =
            (lcd_cmap_tbl[0][2][2] << 8) | (lcd_cmap_tbl[0][1][2] << 4)
            | (lcd_cmap_tbl[0][0][2]);
        lcd_dev[sel]->tcon_cmap_odd1.bits.out3 =
            (lcd_cmap_tbl[0][2][3] << 8) | (lcd_cmap_tbl[0][1][3] << 4)
            | (lcd_cmap_tbl[0][0][3]);
        lcd_dev[sel]->tcon_cmap_even0.bits.out0 =
            (lcd_cmap_tbl[1][2][0] << 8) | (lcd_cmap_tbl[1][1][0] << 4)
            | (lcd_cmap_tbl[1][0][0]);
        lcd_dev[sel]->tcon_cmap_even0.bits.out1 =
            (lcd_cmap_tbl[1][2][1] << 8) | (lcd_cmap_tbl[1][1][1] << 4)
            | (lcd_cmap_tbl[1][0][1]);
        lcd_dev[sel]->tcon_cmap_even1.bits.out2 =
            (lcd_cmap_tbl[1][2][2] << 8) | (lcd_cmap_tbl[1][1][2] << 4)
            | (lcd_cmap_tbl[1][0][2]);
        lcd_dev[sel]->tcon_cmap_even1.bits.out3 =
            (lcd_cmap_tbl[1][2][3] << 8) | (lcd_cmap_tbl[1][1][3] << 4)
            | (lcd_cmap_tbl[1][0][3]);
        lcd_dev[sel]->tcon_cmap_ctl.bits.cmap_en = 1;
    }
    return 0;
}

void tcon_show_builtin_patten(u32 sel, u32 patten)
{
    lcd_dev[sel]->tcon0_ctl.bits.src_sel = patten;
}


/**
 * @name       :tcon_set_fsync_pol
 * @brief      :set fsync's polarity
 * @param[IN]  :sel:tcon index
 * @param[IN]  :pol:polarity. 1:positive;0:negative
 *  positive:
 *           +---------+
 *  ---------+         +-----------
 *
 *  negative:
 *  ---------+         +------------
 *       +---------+
 *
 * @return     :always 0
 */
s32 tcon_set_fsync_pol(u32 sel, u32 pol)
{
    if (pol) {
        lcd_dev[sel]->tcon_gint0.bits.tcon_irq_flag |= 0x00000004;
        lcd_dev[sel]->fsync_gen_ctrl.bits.sensor_dis_value = 0;
        lcd_dev[sel]->fsync_gen_ctrl.bits.sensor_act0_value = 1;
        lcd_dev[sel]->fsync_gen_ctrl.bits.sensor_act1_value = 1;
    } else {
        lcd_dev[sel]->tcon_gint0.bits.tcon_irq_flag &= 0xfffffffb;
        lcd_dev[sel]->fsync_gen_ctrl.bits.sensor_dis_value = 1;
        lcd_dev[sel]->fsync_gen_ctrl.bits.sensor_act0_value = 0;
        lcd_dev[sel]->fsync_gen_ctrl.bits.sensor_act1_value = 0;
    }
    return 0;
}

/**
 * @name       :tcon_set_fsync_active_time
 * @brief      :set tcon fsync's active time
 * @param[IN]  :sel:tcon index
 * @param[IN]  :pixel_num:number of pixel time(Tpixel) to set
 *
 * Tpixel = 1/fps*1e9/vt/ht, unit:ns
 *
 * @return     :0 if success
 */
s32 tcon_set_fsync_active_time(u32 sel, u32 pixel_num)
{
    /*4095*2*/
    if (pixel_num > 8190 || pixel_num <= 0)
        return -1;

    if (pixel_num > 4095) {
        lcd_dev[sel]->fsync_gen_dly.bits.sensor_act0_time = 4095;
        lcd_dev[sel]->fsync_gen_dly.bits.sensor_act1_time =
            pixel_num - 4095;
    } else {
        lcd_dev[sel]->fsync_gen_dly.bits.sensor_act0_time =
            pixel_num / 2;
        lcd_dev[sel]->fsync_gen_dly.bits.sensor_act1_time =
            pixel_num - pixel_num / 2;
    }

    return 0;
}

void tcon_reset(u32 sel)
{
    lcd_dev[sel]->tcon0_ctl.bits.src_sel = 1;
    lcd_dev[sel]->tcon_gctl.bits.tcon_en = 0;
    disp_delay_us(20);
    lcd_dev[sel]->tcon0_ctl.bits.src_sel = 0;
    lcd_dev[sel]->tcon_gctl.bits.tcon_en = 1;
}
