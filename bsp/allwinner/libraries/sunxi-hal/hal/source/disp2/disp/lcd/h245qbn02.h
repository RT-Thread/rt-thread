/* drivers/video/sunxi/disp2/disp/lcd/he0801a068.h
 *
 * Copyright (c) 2017 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
 * he0801a-068 panel driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
#ifndef _H245QBN02_H
#define _H245QBN02_H

#include "panels.h"

extern struct __lcd_panel h245qbn02_panel;

extern s32 bsp_disp_get_panel_info(u32 screen_id, struct disp_panel_para *info);

extern void tcon_reset(u32 sel);

#endif /*End of file*/
