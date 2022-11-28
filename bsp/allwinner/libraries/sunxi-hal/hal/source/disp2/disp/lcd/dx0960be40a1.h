/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DX0960BE40A1_PANEL_H__
#define  __DX0960BE40A1_PANEL_H__

#include "panels.h"

extern struct __lcd_panel dx0960be40a1_panel;
extern s32 bsp_disp_get_panel_info(u32 screen_id, struct disp_panel_para *info);

#endif
