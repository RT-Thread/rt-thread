/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __FD055HD003S_PANEL_H__
#define  __FD055HD003S_PANEL_H__

#include "panels.h"

extern struct __lcd_panel fd055hd003s_panel;

extern s32 bsp_disp_get_panel_info(u32 screen_id, struct disp_panel_para *info);

#endif
