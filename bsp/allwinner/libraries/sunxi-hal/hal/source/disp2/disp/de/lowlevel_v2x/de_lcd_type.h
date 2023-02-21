/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DE_LCD_TYPE_H__
#define __DE_LCD_TYPE_H__

#include "de_lcd.h"

/*
 * detail information of registers
 */

union tcon_gctl_reg_t {
    u32 dwval;
    struct {
        u32 io_map_sel:1;
        u32 pad_sel:1;
        u32 res0:28;
        u32 tcon_gamma_en:1;
        u32 tcon_en:1;
    } bits;
};

union tcon_gint0_reg_t {
    u32 dwval;
    struct {
        u32 tcon_irq_flag:16;
        u32 tcon_irq_en:16;
    } bits;
};

union tcon_gint1_reg_t {
    u32 dwval;
    struct {
        u32 tcon1_line_int_num:12;
        u32 res0:4;
        u32 tcon0_line_int_num:12;
        u32 res1:4;
    } bits;
};

union tcon0_frm_ctl_reg_t {
    u32 dwval;
    struct {
        u32 tcon0_frm_test:2;
        u32 res0:2;
        u32 tcon0_frm_mode_b:1;
        u32 tcon0_frm_mode_g:1;
        u32 tcon0_frm_mode_r:1;
        u32 res1:24;
        u32 tcon0_frm_en:1;
    } bits;
};

union tcon0_frm_seed_reg_t {
    u32 dwval;
    struct {
        u32 seed_value:13;
        u32 res0:19;
    } bits;
};

union tcon0_frm_tab_reg_t {
    u32 dwval;
    struct {
        u32 frm_table_value;
    } bits;
};

union tcon0_3d_fifo_reg_t {
    u32 dwval;
    struct {
        u32 fifo_3d_setting:2;
        u32 res0:2;
        u32 fifo_3d_half_line_size:11;
        u32 res1:16;
        u32 fifo_3d_bist_en:1;
    } bits;
};

union tcon0_ctl_reg_t {
    u32 dwval;
    struct {
        u32 src_sel:3;
        u32 res0:1;
        u32 start_delay:5;
        u32 res1:11;
        u32 interlace_en:1;
        u32 fifo1_rst:1;
        u32 test_value:1;
        u32 rb_swap:1;
        u32 tcon0_if:2;
        u32 res2:2;
        u32 tcon0_work_mode:1;
        u32 res3:2;
        u32 tcon0_en:1;
    } bits;
};

union tcon0_dclk_reg_t {
    u32 dwval;
    struct {
        u32 tcon0_dclk_div:7;
        u32 res0:21;
        u32 tcon0_dclk_en:4;
    } bits;
};

union tcon0_basic0_reg_t {
    u32 dwval;
    struct {
        u32 y:12;
        u32 res0:4;
        u32 x:12;
        u32 res1:4;
    } bits;
};

union tcon0_basic1_reg_t {
    u32 dwval;
    struct {
        u32 hbp:12;
        u32 res0:4;
        u32 ht:13;
        u32 res1:2;
        u32 reservd:1;
    } bits;
};

union tcon0_basic2_reg_t {
    u32 dwval;
    struct {
        u32 vbp:12;
        u32 res0:4;
        u32 vt:13;
        u32 res1:3;
    } bits;
};

union tcon0_basic3_reg_t {
    u32 dwval;
    struct {
        u32 vspw:10;
        u32 res0:6;
        u32 hspw:10;
        u32 res1:6;
    } bits;
};

union tcon0_hv_if_reg_t {
    u32 dwval;
    struct {
        u32 res0:19;
        u32 ccir_csc_dis:1;
        u32 syuv_fdly:2;
        u32 syuv_seq:2;
        u32 srgb_seq:4;
        u32 hv_mode:4;
    } bits;
};

union tcon0_cpu_if_reg_t {
    u32 dwval;
    struct {
        u32 trigger_en:1;
        u32 trigger_start:1;
        u32 trigger_fifo_en:1;
        u32 trigger_fifo_bist_en:1;
        u32 trigger_sync_mode:2;
        u32 res0:10;
        u32 flush:1;
        u32 auto_:1;
        u32 res1:4;
        u32 rd_flag:1;
        u32 wr_flag:1;
        u32 vsync_cs_sel:1;
        u32 ca:1;
        u32 da:1;
        u32 res2:1;
        u32 cpu_mode:4;
    } bits;
};

union tcon0_cpu_wr_reg_t {
    u32 dwval;
    struct {
        u32 data_wr:24;
        u32 res0:8;
    } bits;
};

union tcon0_cpu_rd0_reg_t {
    u32 dwval;
    struct {
        u32 data_rd0:24;
        u32 res0:8;
    } bits;
};

union tcon0_cpu_rd1_reg_t {
    u32 dwval;
    struct {
        u32 data_rd1:24;
        u32 res0:8;
    } bits;
};

union tcon0_lvds_if_reg_t {
    u32 dwval;
    struct {
        u32 tcon0_lvds_data_revert:4;
        u32 tcon0_lvds_clk_revert:1;
        u32 res0:15;
        u32 tcon0_lvds_clk_sel:1;
        u32 res1:2;
        u32 tcon0_lvds_correct_mode:1;
        u32 tcon0_lvds_debug_mode:1;
        u32 tcon0_lvds_debug_en:1;
        u32 tcon0_lvds_bitwidth:1;
        u32 tcon0_lvds_mode:1;
        u32 tcon0_lvds_dir:1;
        u32 tcon0_lvds_even_odd_dir:1;
        u32 tcon0_lvds_link:1;
        u32 tcon0_lvds_en:1;
    } bits;
};

union tcon0_io_pol_reg_t {
    u32 dwval;
    struct {
        u32 data_inv:24;
        u32 sync_inv:2;
        u32 clk_inv:1;
        u32 de_inv:1;
        u32 dclk_sel:3;
        u32 io_output_sel:1;
    } bits;
};

union tcon0_io_tri_reg_t {
    u32 dwval;
    struct {
        u32 data_output_tri_en:24;
        u32 io0_output_tri_en:1;
        u32 io1_output_tri_en:1;
        u32 io2_output_tri_en:1;
        u32 io3_output_tri_en:1;
        u32 rgb_endian:1;
        u32 res0:3;
    } bits;
};

union tcon1_ctl_reg_t {
    u32 dwval;
    struct {
        u32 src_sel:2;
        u32 res0:2;
        u32 start_delay:5;
        u32 res1:11;
        u32 interlace_en:1;
        u32 res2:10;
        u32 tcon1_en:1;
    } bits;
};

union tcon1_basic0_reg_t {
    u32 dwval;
    struct {
        u32 y:12;
        u32 res0:4;
        u32 x:12;
        u32 res1:4;
    } bits;
};

union tcon1_basic1_reg_t {
    u32 dwval;
    struct {
        u32 ls_yo:12;
        u32 res0:4;
        u32 ls_xo:12;
        u32 res1:4;
    } bits;
};

union tcon1_basic2_reg_t {
    u32 dwval;
    struct {
        u32 yo:12;
        u32 res0:4;
        u32 xo:12;
        u32 res1:4;
    } bits;
};

union tcon1_basic3_reg_t {
    u32 dwval;
    struct {
        u32 hbp:12;
        u32 res0:4;
        u32 ht:13;
        u32 res1:3;
    } bits;
};

union tcon1_basic4_reg_t {
    u32 dwval;
    struct {
        u32 vbp:12;
        u32 res0:4;
        u32 vt:13;
        u32 res1:3;
    } bits;
};

union tcon1_basic5_reg_t {
    u32 dwval;
    struct {
        u32 vspw:10;
        u32 res0:6;
        u32 hspw:10;
        u32 res1:6;
    } bits;
};

union tcon1_ps_sync_reg_t {
    u32 dwval;
    struct {
        u32 sync_y:16;
        u32 sync_x:16;
    } bits;
};

union tcon1_io_pol_reg_t {
    u32 dwval;
    struct {
        u32 data_inv:24;
        u32 io0_inv:1;
        u32 io1_inv:1;
        u32 io2_inv:1;
        u32 io3_inv:1;
        u32 res0:4;
    } bits;
};

union tcon1_io_tri_reg_t {
    u32 dwval;
    struct {
        u32 data_output_tri_en:24;
        u32 io0_output_tri_en:1;
        u32 io1_output_tri_en:1;
        u32 io2_output_tri_en:1;
        u32 io3_output_tri_en:1;
        u32 res0:4;
    } bits;
};

union tcon_ecc_fifo_reg_t {
    u32 dwval;
    struct {
        u32 ecc_fifo_setting:8;
        u32 ecc_fifo_blank_en:1;
        u32 res0:7;
        u32 ecc_fifo_err_bits:8;
        u32 res1:6;
        u32 ecc_fifo_err_flag:1;
        u32 ecc_fifo_bist_en:1;
    } bits;
};

union tcon_debug_reg_t {
    u32 dwval;
    struct {
        u32 tcon1_current_line:12;
        u32 res0:1;
        u32 ecc_fifo_bypass:1;
        u32 res1:2;
        u32 tcon0_current_line:12;
        u32 tcon1_field_polarity:1;
        u32 tcon0_field_polarity:1;
        u32 tcon1_fifo_under_flow:1;
        u32 tcon0_fifo_under_flow:1;
    } bits;
};

union tcon_ceu_ctl_reg_t {
    u32 dwval;
    struct {
        u32 res0:31;
        u32 ceu_en:1;
    } bits;
};

union tcon_ceu_coef_mul_reg_t {
    u32 dwval;
    struct {
        u32 value:13;
        u32 res0:19;
    } bits;
};

union tcon_ceu_coef_add_reg_t {
    u32 dwval;
    struct {
        u32 value:19;
        u32 res0:13;
    } bits;
};

union tcon_ceu_coef_rang_reg_t {
    u32 dwval;
    struct {
        u32 max:8;
        u32 res0:8;
        u32 min:8;
        u32 res1:8;
    } bits;
};

union tcon0_cpu_tri0_reg_t {
    u32 dwval;
    struct {
        u32 block_size:12;
        u32 res0:4;
        u32 block_space:12;
        u32 res1:4;
    } bits;
};

union tcon0_cpu_tri1_reg_t {
    u32 dwval;
    struct {
        u32 block_num:16;
        u32 block_current_num:16;
    } bits;
};

union tcon0_cpu_tri2_reg_t {
    u32 dwval;
    struct {
        u32 trans_start_set:13;
        u32 sync_mode:2;
        u32 trans_start_mode:1;
        u32 start_delay:16;
    } bits;
};

union tcon0_cpu_tri3_reg_t {
    u32 dwval;
    struct {
        u32 counter_m:8;
        u32 counter_n:16;
        u32 res0:4;
        u32 tri_int_mode:2;
        u32 res1:2;
    } bits;
};

union tcon0_cpu_tri4_reg_t {
    u32 dwval;
    struct {
        u32 data:24;
        u32 a1:1;
        u32 res0:3;
        u32 en:1;
        u32 res1:3;
    } bits;
};

union tcon0_cpu_tri5_reg_t {
    u32 dwval;
    struct {
        u32 data:24;
        u32 a1:1;
        u32 res0:7;
    } bits;
};

union tcon_cmap_ctl_reg_t {
    u32 dwval;
    struct {
        u32 out_format:1;
        u32 res0:30;
        u32 cmap_en:1;
    } bits;
};

union tcon_cmap_odd0_reg_t {
    u32 dwval;
    struct {
        u32 out0:16;
        u32 out1:16;
    } bits;
};

union tcon_cmap_odd1_reg_t {
    u32 dwval;
    struct {
        u32 out2:16;
        u32 out3:16;
    } bits;
};

union tcon_cmap_even0_reg_t {
    u32 dwval;
    struct {
        u32 out0:16;
        u32 out1:16;
    } bits;
};

union tcon_cmap_even1_reg_t {
    u32 dwval;
    struct {
        u32 out2:16;
        u32 out3:16;
    } bits;
};

union tcon_safe_period_reg_t {
    u32 dwval;
    struct {
        u32 safe_period_mode:2;
        u32 res0:14;
        u32 safe_period_fifo_num:13;
        u32 res1:3;
    } bits;
};

union tcon_mux_ctl_reg_t {
    u32 dwval;
    struct {
        u32 dsi_src:2;
        u32 res0:6;
        u32 hdmi_src:2;
        u32 res1:22;
    } bits;
};

union tcon_sync_ctl_reg_t {
    u32 dwval;
    struct {
        u32 ctrl_sync_mode:1;
        u32 res0:3;
        u32 master_slave:1;
        u32 res1:3;
        u32 dsi_num:1;
        u32 res2:23;
    } bits;
};

union tcon_sync_pos_reg_t {
    u32 dwval;
    struct {
        u32 sync_line_num:12;
        u32 res0:4;
        u32 sync_pixel_num:12;
        u32 res1:4;
    } bits;
};

union tcon_slave_stop_reg_t {
    u32 dwval;
    struct {
        u32 stop_val:8;
        u32 res0:24;
    } bits;
};

union tcon_fsync_gen_ctrl_reg_t {
    u32 dwval;
    struct {
        u32 fsync_gen_en:1;
        u32 sel_vsync_en:1;
        u32 hsync_pol_sel:1;
        u32 res0:1;
        u32 sensor_dis_value:1;
        u32 sensor_act0_value:1;
        u32 sensor_act1_value:1;
        u32 res1:1;
        u32 sensor_dis_time:11;
        u32 res2:13;
    } bits;
};

union tcon_fsync_gen_dly_reg_t {
    u32 dwval;
    struct {
        u32 sensor_act1_time:12;
        u32 res0:4;
        u32 sensor_act0_time:12;
        u32 res1:4;
    } bits;
};

union tcon0_lvds_ana_reg_t {
    u32 dwval;
    struct {
        u32 pwsmb:1;
        u32 pwslv:1;
        u32 res0:2;
        u32 pd:2;
        u32 res1:2;
        u32 v:2;
        u32 res2:2;
        u32 den:4;
        u32 denc:1;
        u32 c:2;
        u32 res3:1;
        u32 en_drvd:4;
        u32 en_drvc:1;
        u32 res4:3;
        u32 en_24m:1;
        u32 en_lvds:1;
        u32 en_ldo:1;
        u32 en_mb:1;
    } bits;
};

union tcon1_fill_ctl_reg_t {
    u32 dwval;
    struct {
        u32 res0:31;
        u32 tcon1_fill_en:1;
    } bits;
};

union tcon1_fill_begin_reg_t {
    u32 dwval;
    struct {
        u32 fill_begin:24;
        u32 res0:8;
    } bits;
};

union tcon1_fill_end_reg_t {
    u32 dwval;
    struct {
        u32 fill_end:24;
        u32 res0:8;
    } bits;
};

union tcon1_fill_data_reg_t {
    u32 dwval;
    struct {
        u32 fill_value:24;
        u32 res0:8;
    } bits;
};

union tcon_gamma_tlb_reg_t {
    u32 dwval;
    struct {
        u32 pixel:24;
        u32 res0:8;
    } bits;
    struct {
        u32 blue:8;
        u32 green:8;
        u32 red:8;
        u32 res0:8;
    } bytes;
};

union tcon_reservd_reg_t {
    u32 dwval;
    struct {
        u32 res0;
    } bits;
};

#if defined(HAVE_DEVICE_COMMON_MODULE)
/*
 * tcon_tv_setup_reg_t - tcon config for tv output
 * @tv0_clk_src: 0:clk from ccu,1:clk from tve0
 * @tv1_clk_src: 0:clk from ccu,1:clk from tve1
 * @tv0_out: 0:lcd0 to gpiod,1:tv0 to gpiod
 * @tv1_out: 0:lcd1 to gpioh,1:tv1 to gpioh
 */
union tcon_tv_setup_reg_t {
    u32 dwval;
    struct {
        u32 tv0_clk_src:1;
        u32 res3:3;
        u32 tv1_clk_src:1;
        u32 res2:3;
        u32 tv0_out:1;
        u32 res1:3;
        u32 tv1_out:1;
        u32 res4:2;
        u32 rgb0_src_sel:1;
        u32 res0:16;
    } bits;
};

union tcon_de_perh_reg_t {
    u32 dwval;
    struct {
        u32 de_port0_perh:2;
        u32 res1:2;
        u32 de_port1_perh:2;
        u32 res0:26;
    } bits;
};

union tcon_clk_gate_reg_t {
    u32 dwval;
    struct {
        u32 vdpo0_clk_gate:1;
        u32 vdpo1_clk_gate:1;
        u32 res4:14;
        u32 dsi_clk_gate:1;
        u32 lcd1_dsi_clk_gate:1;
        u32 res3:2;
        u32 tv0_clk_gate:1;
        u32 res2:3;
        u32 tv1_clk_gate:1;
        u32 res1:3;
        u32 hdmi_src:2;
        u32 res0:2;
    } bits;
};

union dsi_src_select_reg_t {
    u32 dwval;
    struct {
        u32 dsi0_src_sel:1;
        u32 res0:3;
        u32 dsi1_src_sel:1;
        u32 res1:27;
    } bits;
};

union vdpo_src_select_reg_t {
    u32 dwval;
    struct {
        u32 vdpo0_src_sel:1;
        u32 res0:3;
        u32 vdpo1_src_sel:1;
        u32 res1:27;
    } bits;
};

struct __de_lcd_top_dev_t {
    /* 0x00 - 0x0c */
    union tcon_tv_setup_reg_t tcon_tv_setup;
    union dsi_src_select_reg_t dsi_src_select;
    union vdpo_src_select_reg_t vdpo_src_select;
    union tcon_reservd_reg_t tcon_reg_000c;
    /* 0x10 - 0x1c */
    union tcon_reservd_reg_t tcon_reg_0010;
    union tcon_reservd_reg_t tcon_reg_0014;
    union tcon_reservd_reg_t tcon_reg_0018;
    union tcon_de_perh_reg_t tcon_de_perh;
    /* 0x20 - 0x2c */
    union tcon_clk_gate_reg_t tcon_clk_gate;
};
/* edit by lrx---end */
#endif

enum cpu_mode {
    MODE_18BIT = 0,
    MODE0_16BIT = 2,
    MODE1_16BIT = 4,
    MODE2_16BIT = 6,
    MODE3_16BIT = 8,
    MODE_9BIT = 10,
    MODE_8BIT_256K = 12,
    MODE_8BIT_65K = 14,
    MODE_DSI = 1,
};

struct __de_lcd_dev_t {
    /* 0x00 - 0x0c */
    union tcon_gctl_reg_t tcon_gctl;
    union tcon_gint0_reg_t tcon_gint0;
    union tcon_gint1_reg_t tcon_gint1;
    union tcon_reservd_reg_t tcon_reg01c;
    /* 0x10 - 0x1c */
    union tcon0_frm_ctl_reg_t tcon0_frm_ctl;
    union tcon0_frm_seed_reg_t tcon0_frm_seed_pr;
    union tcon0_frm_seed_reg_t tcon0_frm_seed_pg;
    union tcon0_frm_seed_reg_t tcon0_frm_seed_pb;
    /* 0x20 - 0x2c */
    union tcon0_frm_seed_reg_t tcon0_frm_seed_lr;
    union tcon0_frm_seed_reg_t tcon0_frm_seed_lg;
    union tcon0_frm_seed_reg_t tcon0_frm_seed_lb;
    union tcon0_frm_tab_reg_t tcon0_frm_tbl_0;
    /* 0x30 - 0x3c */
    union tcon0_frm_tab_reg_t tcon0_frm_tbl_1;
    union tcon0_frm_tab_reg_t tcon0_frm_tbl_2;
    union tcon0_frm_tab_reg_t tcon0_frm_tbl_3;
    union tcon0_3d_fifo_reg_t tcon0_3d_fifo;
    /* 0x40 - 0x4c */
    union tcon0_ctl_reg_t tcon0_ctl;
    union tcon0_dclk_reg_t tcon0_dclk;
    union tcon0_basic0_reg_t tcon0_basic0;
    union tcon0_basic1_reg_t tcon0_basic1;
    /* 0x50 - 0x5c */
    union tcon0_basic2_reg_t tcon0_basic2;
    union tcon0_basic3_reg_t tcon0_basic3;
    union tcon0_hv_if_reg_t tcon0_hv_ctl;
    union tcon_reservd_reg_t tcon_reg05c;
    /* 0x60 - 0x6c */
    union tcon0_cpu_if_reg_t tcon0_cpu_ctl;
    union tcon0_cpu_wr_reg_t tcon0_cpu_wr;
    union tcon0_cpu_rd0_reg_t tcon0_cpu_rd;
    union tcon0_cpu_rd1_reg_t tcon0_cpu_fet;
    /* 0x70 - 0x7c */
    union tcon_reservd_reg_t tcon_reg070[4];
    /* 0x80 - 0x8c */
    union tcon_reservd_reg_t tcon_reg080;
    union tcon0_lvds_if_reg_t tcon0_lvds_ctl;
    union tcon0_io_pol_reg_t tcon0_io_pol;
    union tcon0_io_tri_reg_t tcon0_io_tri;
    /* 0x90 - 0x9c */
    union tcon1_ctl_reg_t tcon1_ctl;
    union tcon1_basic0_reg_t tcon1_basic0;
    union tcon1_basic1_reg_t tcon1_basic1;
    union tcon1_basic2_reg_t tcon1_basic2;
    /* 0xa0 - 0xac */
    union tcon1_basic3_reg_t tcon1_basic3;
    union tcon1_basic4_reg_t tcon1_basic4;
    union tcon1_basic5_reg_t tcon1_basic5;
    union tcon_reservd_reg_t tcon_reg0ac;
    /* 0xb0 - 0xec */
    union tcon1_ps_sync_reg_t tcon1_ps_ctl;
    union tcon_reservd_reg_t tcon_reg0b4[15];
    /* 0xf0 - 0xfc */
    union tcon1_io_pol_reg_t tcon1_io_pol;
    union tcon1_io_tri_reg_t tcon1_io_tri;
    union tcon_ecc_fifo_reg_t tcon_ecfifo_ctl;
    union tcon_debug_reg_t tcon_debug;
    /* 0x100 - 0x10c */
    union tcon_ceu_ctl_reg_t tcon_ceu_ctl;
    union tcon_reservd_reg_t tcon_reg104[3];
    /* 0x110 - 0x11c */
    union tcon_ceu_coef_mul_reg_t tcon_ceu_coef_rr;
    union tcon_ceu_coef_mul_reg_t tcon_ceu_coef_rg;
    union tcon_ceu_coef_mul_reg_t tcon_ceu_coef_rb;
    union tcon_ceu_coef_add_reg_t tcon_ceu_coef_rc;
    /* 0x120 - 0x12c */
    union tcon_ceu_coef_mul_reg_t tcon_ceu_coef_gr;
    union tcon_ceu_coef_mul_reg_t tcon_ceu_coef_gg;
    union tcon_ceu_coef_mul_reg_t tcon_ceu_coef_gb;
    union tcon_ceu_coef_add_reg_t tcon_ceu_coef_gc;
    /* 0x130 - 0x13c */
    union tcon_ceu_coef_mul_reg_t tcon_ceu_coef_br;
    union tcon_ceu_coef_mul_reg_t tcon_ceu_coef_bg;
    union tcon_ceu_coef_mul_reg_t tcon_ceu_coef_bb;
    union tcon_ceu_coef_add_reg_t tcon_ceu_coef_bc;
    /* 0x140 - 0x14c */
    union tcon_ceu_coef_rang_reg_t tcon_ceu_coef_rv;
    union tcon_ceu_coef_rang_reg_t tcon_ceu_coef_gv;
    union tcon_ceu_coef_rang_reg_t tcon_ceu_coef_bv;
    union tcon_reservd_reg_t tcon_reg14c;
    /* 0x150 - 0x15c */
    union tcon_reservd_reg_t tcon_reg150[4];
    /* 0x160 - 0x16c */
    union tcon0_cpu_tri0_reg_t tcon0_cpu_tri0;
    union tcon0_cpu_tri1_reg_t tcon0_cpu_tri1;
    union tcon0_cpu_tri2_reg_t tcon0_cpu_tri2;
    union tcon0_cpu_tri3_reg_t tcon0_cpu_tri3;
    /* 0x170 - 0x17c */
    union tcon0_cpu_tri4_reg_t tcon0_cpu_tri4;
    union tcon0_cpu_tri5_reg_t tcon0_cpu_tri5;
    union tcon_reservd_reg_t tcon_reg178[2];
    /* 0x180 - 0x18c */
    union tcon_cmap_ctl_reg_t tcon_cmap_ctl;
    union tcon_reservd_reg_t tcon_reg184[3];
    /* 0x190 - 0x19c */
    union tcon_cmap_odd0_reg_t tcon_cmap_odd0;
    union tcon_cmap_odd1_reg_t tcon_cmap_odd1;
    union tcon_cmap_even0_reg_t tcon_cmap_even0;
    union tcon_cmap_even1_reg_t tcon_cmap_even1;
    /* 0x1a0 - 0x1ec */
    union tcon_reservd_reg_t tcon_reg1a0[20];
    /* 0x1f0 - 0x1fc */
    union tcon_safe_period_reg_t tcon_volume_ctl;
    union tcon_reservd_reg_t tcon_reg1f4[3];
    /* 0x200 - 0x21c */
    union tcon_mux_ctl_reg_t tcon_mul_ctl;
    union tcon_reservd_reg_t tcon_reg204[7];
    /* 0x220 - 0x22c */
    union tcon0_lvds_ana_reg_t tcon0_lvds_ana[2];
    union tcon_reservd_reg_t tcon_reg228[2];
    /* 0x230 - 0x2fc */
    union tcon_sync_ctl_reg_t tcon_sync_ctl;
    union tcon_sync_pos_reg_t tcon_sync_pos;
    union tcon_slave_stop_reg_t tcon_slave_stop;
#if defined(CONFIG_ARCH_SUN20IW1)
    union tcon0_lvds_ana_reg_t tcon0_lvds1_ana[2];
    union tcon0_lvds_if_reg_t tcon0_lvds1_ctl;
    union tcon_reservd_reg_t tcon_reg248[46];
#else
    union tcon_fsync_gen_ctrl_reg_t fsync_gen_ctrl;
    union tcon_fsync_gen_dly_reg_t fsync_gen_dly;
    union tcon_reservd_reg_t tcon_reg244[47];
#endif
    /* 0x300 - 0x30c */
    union tcon1_fill_ctl_reg_t tcon_fill_ctl;
    union tcon1_fill_begin_reg_t tcon_fill_start0;
    union tcon1_fill_end_reg_t tcon_fill_end0;
    union tcon1_fill_data_reg_t tcon_fill_data0;
    /* 0x310 - 0x31c */
    union tcon1_fill_begin_reg_t tcon_fill_start1;
    union tcon1_fill_end_reg_t tcon_fill_end1;
    union tcon1_fill_data_reg_t tcon_fill_data1;
    union tcon1_fill_begin_reg_t tcon_fill_start2;
    /* 0x320 - 0x32c */
    union tcon1_fill_end_reg_t tcon_fill_end2;
    union tcon1_fill_data_reg_t tcon_fill_data2;
    union tcon_reservd_reg_t tcon_reg328[2];
    /* 0x330 - 0x3fc */
    union tcon_reservd_reg_t tcon_reg330[52];
    /* 0x400 - 0x40c */
    union tcon_gamma_tlb_reg_t tcon_gamma_tlb[256];
};

s32 tcon_cmap(u32 sel, u32 mode, u32 lcd_cmap_tbl[2][3][4]);
s32 tcon_gamma(u32 sel, u32 mode, u32 gamma_tbl[256]);
s32 tcon_ceu(u32 sel, u32 mode, s32 b, s32 c, s32 s, s32 h);
s32 tcon0_frm(u32 sel, u32 mode);

#endif
