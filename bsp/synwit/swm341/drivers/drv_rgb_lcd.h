/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
 */

#ifndef __DRV_RGB_LCD_H__
#define __DRV_RGB_LCD_H__

#include "board.h"

struct swm_rgb_lcd_device
{
    struct rt_device parent;
    struct rt_device_graphic_info lcd_info;
};

int swm_rgb_lcd_init(void);

#endif /* __DRV_RGB_LCD_H__ */
