/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-04-12     RT-Thread    the first version
 */

#ifndef __DRV_LCD_H__
#define __DRV_LCD_H__

#include <stdint.h>

#define REVERSE_X       (1<<0)
#define REVERSE_Y       (1<<1)
#define REVERSE_MODE    (1<<2)

int rt_hw_lcd_init(void);

#define FBIOGET_FSCREENINFO     0x4602

struct fb_fix_screeninfo
{
    char id[16];
    unsigned long smem_start;
    uint32_t smem_len;

    uint32_t line_length;
};
rt_uint8_t get_lcd_backlight(void);
void set_lcd_backlight(rt_uint8_t value);
void turn_down_lcd_backlight(void);
void turn_on_lcd_backlight(void);

#endif
