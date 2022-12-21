/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __LT070ME05000_PANEL_H__
#define  __LT070ME05000_PANEL_H__

#include "panels.h"

extern struct __lcd_panel lt070me05000_panel;

extern s32 dsi_dcs_wr_0para(u32 sel, u8 cmd);
extern s32 dsi_dcs_wr_1para(u32 sel, u8 cmd, u8 para);
extern s32 dsi_dcs_wr_2para(u32 sel, u8 cmd, u8 para1, u8 para2);
extern s32 dsi_dcs_wr_3para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3);
extern s32 dsi_dcs_wr_4para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3,
                u8 para4);
extern s32 dsi_dcs_wr_5para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3,
                u8 para4, u8 para5);
extern s32 dsi_gen_wr_0para(u32 sel, u8 cmd);
extern s32 dsi_gen_wr_1para(u32 sel, u8 cmd, u8 para);
extern s32 dsi_gen_wr_2para(u32 sel, u8 cmd, u8 para1, u8 para2);
extern s32 dsi_gen_wr_3para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3);
extern s32 dsi_gen_wr_4para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3,
                u8 para4);
extern s32 dsi_gen_wr_5para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3,
                u8 para4, u8 para5);

extern s32 bsp_disp_get_panel_info(u32 screen_id, struct disp_panel_para *info);
#endif
