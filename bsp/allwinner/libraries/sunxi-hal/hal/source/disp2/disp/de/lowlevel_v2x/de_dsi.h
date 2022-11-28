/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DE_DSI_H_
#define __DE_DSI_H_

#include "../include.h"

extern u32 dsi_bits_per_pixel[4];

enum __dsi_dt_t {
    /*
     * Processor to Peripheral Direction (Processor-Sourced)
     * Packet Data Types
     */
    DSI_DT_VSS = 0x01,
    DSI_DT_VSE = 0x11,
    DSI_DT_HSS = 0x21,
    DSI_DT_HSE = 0x31,
    DSI_DT_EOT = 0x08,
    DSI_DT_CM_OFF = 0x02,
    DSI_DT_CM_ON = 0x12,
    DSI_DT_SHUT_DOWN = 0x22,
    DSI_DT_TURN_ON = 0x32,
    DSI_DT_GEN_WR_P0 = 0x03,
    DSI_DT_GEN_WR_P1 = 0x13,
    DSI_DT_GEN_WR_P2 = 0x23,
    DSI_DT_GEN_RD_P0 = 0x04,
    DSI_DT_GEN_RD_P1 = 0x14,
    DSI_DT_GEN_RD_P2 = 0x24,
    DSI_DT_DCS_WR_P0 = 0x05,
    DSI_DT_DCS_WR_P1 = 0x15,
    DSI_DT_DCS_RD_P0 = 0x06,
    DSI_DT_MAX_RET_SIZE = 0x37,
    DSI_DT_NULL = 0x09,
    DSI_DT_BLK = 0x19,
    DSI_DT_GEN_LONG_WR = 0x29,
    DSI_DT_DCS_LONG_WR = 0x39,
    DSI_DT_PIXEL_RGB565 = 0x0E,
    DSI_DT_PIXEL_RGB666P = 0x1E,
    DSI_DT_PIXEL_RGB666 = 0x2E,
    DSI_DT_PIXEL_RGB888 = 0x3E,

    /* Data Types for Peripheral-sourced Packets */
    DSI_DT_ACK_ERR = 0x02,
    DSI_DT_EOT_PERI = 0x08,
    DSI_DT_GEN_RD_R1 = 0x11,
    DSI_DT_GEN_RD_R2 = 0x12,
    DSI_DT_GEN_LONG_RD_R = 0x1A,
    DSI_DT_DCS_LONG_RD_R = 0x1C,
    DSI_DT_DCS_RD_R1 = 0x21,
    DSI_DT_DCS_RD_R2 = 0x22,
};

enum __dsi_dcs_t {
    DSI_DCS_ENTER_IDLE_MODE = 0x39,
    DSI_DCS_ENTER_INVERT_MODE = 0x21,
    DSI_DCS_ENTER_NORMAL_MODE = 0x13,
    DSI_DCS_ENTER_PARTIAL_MODE = 0x12,
    DSI_DCS_ENTER_SLEEP_MODE = 0x10,
    DSI_DCS_EXIT_IDLE_MODE = 0x38,
    DSI_DCS_EXIT_INVERT_MODE = 0x20,
    DSI_DCS_EXIT_SLEEP_MODE = 0x11,
    DSI_DCS_GET_ADDRESS_MODE = 0x0b,
    DSI_DCS_GET_BLUE_CHANNEL = 0x08,
    DSI_DCS_GET_DIAGNOSTIC_RESULT = 0x0f,
    DSI_DCS_GET_DISPLAY_MODE = 0x0d,
    DSI_DCS_GET_GREEN_CHANNEL = 0x07,
    DSI_DCS_GET_PIXEL_FORMAT = 0x0c,
    DSI_DCS_GET_POWER_MODE = 0x0a,
    DSI_DCS_GET_RED_CHANNEL = 0x06,
    DSI_DCS_GET_SCANLINE = 0x45,
    DSI_DCS_GET_SIGNAL_MODE = 0x0e,
    DSI_DCS_NOP = 0x00,
    DSI_DCS_READ_DDB_CONTINUE = 0xa8,
    DSI_DCS_READ_DDB_START = 0xa1,
    DSI_DCS_READ_MEMORY_CONTINUE = 0x3e,
    DSI_DCS_READ_MEMORY_START = 0x2e,
    DSI_DCS_SET_ADDRESS_MODE = 0x36,
    DSI_DCS_SET_COLUMN_ADDRESS = 0x2a,
    DSI_DCS_SET_DISPLAY_OFF = 0x28,
    DSI_DCS_SET_DISPLAY_ON = 0x29,
    DSI_DCS_SET_GAMMA_CURVE = 0x26,
    DSI_DCS_SET_PAGE_ADDRESS = 0x2b,
    DSI_DCS_SET_PARTIAL_AREA = 0x30,
    DSI_DCS_SET_PIXEL_FORMAT = 0x3a,
    DSI_DCS_SET_SCROLL_AREA = 0x33,
    DSI_DCS_SET_SCROLL_START = 0x37,
    DSI_DCS_SET_TEAR_OFF = 0x34,
    DSI_DCS_SET_TEAR_ON = 0x35,
    DSI_DCS_SET_TEAR_SCANLINE = 0x44,
    DSI_DCS_SOFT_RESET = 0x01,
    DSI_DCS_WRITE_LUT = 0x2d,
    DSI_DCS_WRITE_MEMORY_CONTINUE = 0x3c,
    DSI_DCS_WRITE_MEMORY_START = 0x2c,
};

enum __dsi_start_t {
    DSI_START_LP11 = 0,
    DSI_START_TBA = 1,
    DSI_START_HSTX = 2,
    DSI_START_LPTX = 3,
    DSI_START_LPRX = 4,
    DSI_START_HSC = 5,
    DSI_START_HSD = 6,
};

enum __dsi_inst_id_t {
    DSI_INST_ID_LP11 = 0,
    DSI_INST_ID_TBA = 1,
    DSI_INST_ID_HSC = 2,
    DSI_INST_ID_HSD = 3,
    DSI_INST_ID_LPDT = 4,
    DSI_INST_ID_HSCEXIT = 5,
    DSI_INST_ID_NOP = 6,
    DSI_INST_ID_DLY = 7,
    DSI_INST_ID_END = 15,
};

enum __dsi_inst_mode_t {
    DSI_INST_MODE_STOP = 0,
    DSI_INST_MODE_TBA = 1,
    DSI_INST_MODE_HS = 2,
    DSI_INST_MODE_ESCAPE = 3,
    DSI_INST_MODE_HSCEXIT = 4,
    DSI_INST_MODE_NOP = 5,
};

enum __dsi_inst_escape_t {
    DSI_INST_ESCA_LPDT = 0,
    DSI_INST_ESCA_ULPS = 1,
    DSI_INST_ESCA_UN1 = 2,
    DSI_INST_ESCA_UN2 = 3,
    DSI_INST_ESCA_RESET = 4,
    DSI_INST_ESCA_UN3 = 5,
    DSI_INST_ESCA_UN4 = 6,
    DSI_INST_ESCA_UN5 = 7,
};

enum __dsi_inst_packet_t {
    DSI_INST_PACK_PIXEL = 0,
    DSI_INST_PACK_COMMAND = 1,
};

s32 dsi_delay_ms(u32 ms);
s32 dsi_delay_us(u32 us);
s32 dsi_set_reg_base(u32 sel, uintptr_t base);
u32 dsi_get_reg_base(u32 sel);
u32 dsi_irq_query(u32 sel, enum __dsi_irq_id_t id);
s32 dsi_cfg(u32 sel, struct disp_panel_para *panel);
s32 dsi_exit(u32 sel);
s32 dsi_open(u32 sel, struct disp_panel_para *panel);
s32 dsi_close(u32 sel);
s32 dsi_inst_busy(u32 sel);
s32 dsi_tri_start(u32 sel);
s32 dsi_dcs_wr(u32 sel, u8 cmd, u8 *para_p, u32 para_num);
s32 dsi_dcs_wr_index(u32 sel, u8 index);
s32 dsi_dcs_wr_data(u32 sel, u8 data);
u32 dsi_get_start_delay(u32 sel);
u32 dsi_get_cur_line(u32 sel);
u32 dsi_io_open(u32 sel, struct disp_panel_para *panel);
u32 dsi_io_close(u32 sel);
s32 dsi_clk_enable(u32 sel, u32 en);
u32 dsi_dphy_get_reg_base(u32 sel);
s32 dsi_irq_enable(u32 sel, enum __dsi_irq_id_t id);
s32 dsi_irq_disable(u32 sel, enum __dsi_irq_id_t id);
s32 dsi_dcs_wr_0para(u32 sel, u8 cmd);
s32 dsi_dcs_wr_1para(u32 sel, u8 cmd, u8 para);
s32 dsi_dcs_wr_2para(u32 sel, u8 cmd, u8 para1, u8 para2);
s32 dsi_dcs_wr_3para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3);
s32 dsi_dcs_wr_4para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3, u8 para4);
s32 dsi_dcs_wr_5para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3, u8 para4,
             u8 para5);
s32 dsi_dcs_wr_memory(u32 sel, u32 *p_data, u32 length);
s32 dsi_dcs_rd(u32 sel, u8 cmd, u8 *para_p, u32 *num_p);
s32 dsi_dcs_rd_memory(u32 sel, u32 *p_data, u32 length);
s32 dsi_start(u32 sel, enum __dsi_start_t func);
s32 dsi_command_enable(u32 sel, u32 cmd_en, u32 is_lp);
s32 dsi_set_max_ret_size(u32 sel, u32 size);
s32 dsi_gen_wr(u32 sel, u8 cmd, u8 *para_p, u32 para_num);
s32 dsi_gen_wr_0para(u32 sel, u8 cmd);
s32 dsi_gen_wr_1para(u32 sel, u8 cmd, u8 para);
s32 dsi_gen_wr_2para(u32 sel, u8 cmd, u8 para1, u8 para2);
s32 dsi_gen_wr_3para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3);
s32 dsi_gen_wr_4para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3, u8 para4);
s32 dsi_gen_wr_5para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3, u8 para4,
             u8 para5);

s32 dsi_dphy_cfg_0data(u32 sel, u32 code);
s32 dsi_dphy_cfg_1data(u32 sel, u32 code, u32 data);
s32 dsi_dphy_cfg_2data(u32 sel, u32 code, u32 data0, u32 data1);
s32 dsi_gen_short_rd(__u32 sel, __u8 *para_p, __u8 para_num, __u8 *result);

extern u32 dsi_pixel_bits[4];
extern u32 dsi_lane_den[4];
extern u32 tcon_div;
s32 dsi_hs_clk(u32 sel, u32 on_off);
u8 dsi_ecc_pro(u32 dsi_ph);
u16 dsi_crc_pro_pd_repeat(u8 pd, u32 pd_bytes);
u16 dsi_crc_pro(u8 *pd_p, u32 pd_bytes);
s32 dsi_mode_switch(__u32 sel, __u32 cmd_en, __u32 lp_en);
/**
 * @name       :dsi_read_mode_en
 * @brief      :Enable dsi read mode in the case of reading in display
 * interrupt.
 *  user must enable read mode before read and disable it after read
 * @param[IN]  :sel:dsi module index
 * @param[IN]  :en: enable read mode
 * @return     :none
 */
void dsi_read_mode_en(u32 sel, u32 en);
s32 dsi_turn_on_peripheral_command(__u32 sel);
/* 0: normal; -1:under flow; */
s32 dsi_get_status(u32 sel);
s32 lvds_combphy_open(__u32 sel, struct disp_panel_para *panel);
__s32 lvds_combphy_close(__u32 sel);
#endif
