/* drivers/video/sunxi/disp2/disp/lcd/ls029b3sx02.h
 *
 * Copyright (c) 2017 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
 * ls029b3sx02 panel driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
#ifndef _LS029B3SX02_H
#define _LS029B3SX02_H

#include "panels.h"

extern struct __lcd_panel ls029b3sx02_panel;
extern s32 bsp_disp_get_panel_info(u32 screen_id, struct disp_panel_para *info);

#endif /*End of file*/
