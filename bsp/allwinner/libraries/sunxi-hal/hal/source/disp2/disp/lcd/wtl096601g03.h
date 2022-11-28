/* drivers/video/sunxi/disp2/disp/lcd/ST7796S.h
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
#ifndef _WTL096601G03_H
#define _WTL096601G03_H

#include "panels.h"

extern struct __lcd_panel wtl096601g03_panel;

extern s32 bsp_disp_get_panel_info(u32 screen_id, struct disp_panel_para *info);

#endif /*End of file*/
