/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DE_LCD_H_
#define __DE_LCD_H_

#include "../include.h"
#include "de_feat.h"

enum __lcd_irq_id_t {
    LCD_IRQ_TCON0_VBLK = 15,
    LCD_IRQ_TCON1_VBLK = 14,
    LCD_IRQ_TCON0_LINE = 13,
    LCD_IRQ_TCON1_LINE = 12,
    LCD_IRQ_TCON0_TRIF = 11,
    LCD_IRQ_TCON0_CNTR = 10,
    LCD_IRQ_FSYNC_INT = 9,
    LCD_IRQ_DATA_EN_INT = 8,
};

enum __dsi_irq_id_t {
    DSI_IRQ_VIDEO_LINE = 3,
    DSI_IRQ_VIDEO_VBLK = 2,
    DSI_IRQ_INSTR_STEP = 1,
    DSI_IRQ_INSTR_END = 0,
};

enum __edp_irq_id_t {
    EDP_IRQ_VBLK = 0,
    EDP_IRQ_LINE1 = 1,
};

enum __lcd_src_t {
    LCD_SRC_DE = 0,
    LCD_SRC_COLOR_BAR = 1,
    LCD_SRC_GRAYSCALE = 2,
    LCD_SRC_BLACK_BY_WHITE = 3,
    LCD_SRC_BLACK = 4,
    LCD_SRC_WHITE = 5,
    LCD_SRC_GRID = 7,
    LCD_SRC_BLUE = 8
};

enum __tv_set_t {
    TV_TO_GPIO = 1,
    LCD_TO_GPIO = 0,
    TV_CLK_F_CCU = 0,
    TV_CLK_F_TVE = 1
};

enum __de_perh_t {
    LCD0 = 0,
    LCD1 = 1,
    TV0 = 2,
    TV1 = 3
};

s32 tcon0_out_to_gpio(u32 sel);
s32 tcon1_out_to_gpio(u32 sel);
s32 tcon1_tv_clk_enable(u32 sel, u32 en);
s32 tcon1_hdmi_clk_enable(u32 sel, u32 en);
s32 tcon0_dsi_clk_enable(u32 sel, u32 en);
s32 tcon_de_attach(u32 tcon_index, u32 de_index);
s32 tcon_get_attach_by_de_index(u32 de_index);
s32 tcon_top_set_reg_base(u32 sel, uintptr_t base);
uintptr_t tcon_top_get_reg_base(u32 sel);
s32 lvds_open(u32 sel, struct disp_panel_para *panel);
s32 lvds_close(u32 sel);
u32 tcon_get_cur_field(u32 sel, u32 tcon_index);
s32 tcon_irq_enable(u32 sel, enum __lcd_irq_id_t id);
s32 tcon_irq_disable(u32 sel, enum __lcd_irq_id_t id);
s32 tcon_set_reg_base(u32 sel, uintptr_t address);
uintptr_t tcon_get_reg_base(u32 sel);
s32 tcon_init(u32 sel);
s32 tcon_exit(u32 sel);
s32 tcon_get_timing(u32 sel, u32 index, struct disp_video_timings *tt);
u32 tcon_irq_query(u32 sel, enum __lcd_irq_id_t id);
u32 tcon_get_start_delay(u32 sel, u32 tcon_index);
u32 tcon_get_cur_line(u32 sel, u32 tcon_index);
s32 tcon_gamma(u32 sel, u32 en, u32 *gamma_tbl);
s32 tcon_get_status(u32 sel, u32 tcon_index);

s32 tcon0_cfg(u32 sel, struct disp_panel_para *panel);
s32 tcon0_cfg_ext(u32 sel, struct panel_extend_para *extend_panel);
s32 tcon0_src_select(u32 sel, enum __lcd_src_t src, u32 de_no);
s32 tcon0_src_get(u32 sel);
s32 tcon0_open(u32 sel, struct disp_panel_para *panel);
s32 tcon0_close(u32 sel);
s32 tcon0_set_dclk_div(u32 sel, u8 div);
u32 tcon0_get_dclk_div(u32 sel);
s32 tcon0_tri_busy(u32 sel);
s32 tcon0_cpu_set_auto_mode(u32 sel);
s32 tcon0_tri_start(u32 sel);
u32 tcon0_cpu_16b_to_24b(u32 value);
u32 tcon0_cpu_24b_to_16b(u32 value);
u32 tcon0_cpu_busy(u32 sel);
s32 tcon0_cpu_wr_24b(u32 sel, u32 index, u32 data);
s32 tcon0_cpu_wr_24b_index(u32 sel, u32 index);
s32 tcon0_cpu_wr_24b_data(u32 sel, u32 data);
s32 tcon0_cpu_rd_24b(u32 sel, u32 index, u32 *data);
s32 tcon0_cpu_rd_24b_data(u32 sel, u32 index, u32 *data, u32 size);
s32 tcon0_cpu_wr_16b(u32 sel, u32 index, u32 data);
s32 tcon0_cpu_wr_16b_index(u32 sel, u32 index);
s32 tcon0_cpu_wr_16b_data(u32 sel, u32 data);
s32 tcon0_cpu_rd_16b(u32 sel, u32 index, u32 *data);

s32 tcon_pan_sel(u32 sel, u32 pad);
s32 tcon1_open(u32 sel);
s32 tcon1_close(u32 sel);
s32 tcon1_src_select(u32 sel, enum __lcd_src_t src, enum __de_perh_t de_no);
s32 tcon1_src_get(u32 sel);
s32 tcon1_cfg_ex(u32 sel, struct disp_panel_para *panel);
s32 tcon1_set_timming(u32 sel, struct disp_video_timings *timming);
s32 tcon1_cfg(u32 sel, struct disp_video_timings *timing);
#ifdef TCON_POL_CORRECT
u32 tcon1_cfg_correct(u32 sel, struct disp_video_timings *timing);
#endif
s32 tcon1_set_tv_mode(u32 sel, enum disp_output_type mode);
s32 hmdi_src_sel(u32 sel);
s32 tcon1_hdmi_color_remap(u32 sel, u32 onoff, u32 is_yuv);
s32 tcon1_yuv_range(u32 sel, u32 onoff);
u32 tcon0_get_cpu_tri2_start_delay(u32 sel);
s32 tcon_set_sync_pol(u32 sel, u32 ver_pol, u32 hor_pol);
s32 get_tcon_type_by_de_index(u32 de_index);
s32 tcon_vdpo_clk_enable(u32 sel, u32 en);
s32 vdpo_src_sel(u32 sel, u32 src);
void tcon_show_builtin_patten(u32 sel, u32 patten);
void tcon0_cpu_wr_16b_multi(u32 sel, u8 cmd, u8 *para, u32 para_num);
void tcon0_cpu_wr_24b_multi(u32 sel, u8 cmd, u8 *para, u32 para_num);

/**
 * @name       :tcon_fsync_set_pol
 * @brief      :set fsync's polarity
 * @param[IN]  :sel:tcon index
 * @param[IN]  :pol:polarity. 1:positive;0:negetive
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
s32 tcon_set_fsync_pol(u32 sel, u32 pol);

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
s32 tcon_set_fsync_active_time(u32 sel, u32 pixel_num);

void tcon_reset(u32 sel);

#if defined(SUPPORT_DSI)
extern __u32 dsi_pixel_bits[4];
extern __u32 tcon_div;
#endif
extern s32 disp_delay_us(u32 us);
extern s32 disp_delay_ms(u32 ms);
extern int de_get_clk_rate(void);

#endif
