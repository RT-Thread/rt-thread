
/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-11-09     bigmagic       first version
 */
#ifndef __LCD_CONSOLE_H__
#define __LCD_CONSOLE_H__

#include <rtthread.h>

#define RGB(r, g, b) ((((r))<<16) | (((g))<<8) | ((b)))
#define COLOR_BLACK RGB(0, 0, 0)
#define COLOR_GREEN RGB(0, 255, 0)
#define COLOR_CYAN RGB(0, 255, 255)
#define COLOR_RED RGB(255, 0, 0)
#define COLOR_YELLOW RGB(255, 255, 0)
#define COLOR_WHITE RGB(255, 255, 255)

#define CONSOLE_WHITE_32 COLOR_WHITE
#define CONSOLE_BLACK_32 COLOR_BLACK
#define CONSOLE_GREEN_32 COLOR_GREEN
#define CONSOLE_CYAN_32 COLOR_CYAN
#define CONSOLE_RED_32 COLOR_RED


#define RGB16(r, g, b) ((((r))<<11) | (((g))<<5) | ((b)))
#define CONSOLE_YELLOW_16 RGB16(0x1f,0x3f,0)
#define CONSOLE_WHITE_16 RGB16(0x1f,0x3f,0x1f)
#define CONSOLE_BLACK_16 RGB16(0,0,0)
#define CONSOLE_GREEN_16 RGB16(0,0x3f,0)
#define CONSOLE_CYAN_16 RGB16(0,0x3f,0x1f)
#define CONSOLE_RED_16 RGB16(0x1f,0,0)

typedef struct
{
    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint32_t vwidth;
    rt_uint32_t vheight;
    rt_uint32_t pitch;
    rt_uint32_t depth;
    rt_uint32_t fore;
    rt_uint32_t back;
    rt_uint32_t x;
    rt_uint32_t y;
    rt_uint32_t vaddr;
    rt_uint32_t paddr;
    rt_uint32_t size;
} fb_t;

void fb_print(char *s);
int lcd_console_init(void);

#endif//CONSOLE
