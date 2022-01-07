/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-08-29     zdzn           first version
 */
#ifndef __DRV_FB_H__
#define __DRV_FB_H__

#define RGB(r, g, b) ((((r))<<16) | (((g))<<8) | ((b)))

#define COLOR_BLACK RGB(0, 0, 0)

#define COLOR_GREEN RGB(0, 255, 0)

#define COLOR_CYAN RGB(0, 255, 255)

#define COLOR_RED RGB(255, 0, 0)

#define COLOR_YELLOW RGB(255, 255, 0)

#define COLOR_WHITE RGB(255, 255, 255)

#define CONSOLE_WHITE COLOR_WHITE
#define CONSOLE_BLACK COLOR_BLACK
#define CONSOLE_GREEN COLOR_GREEN
#define CONSOLE_CYAN COLOR_CYAN
#define CONSOLE_RED COLOR_RED
#define CONSOLE_YELLOW COLOR_YELLOW

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
    rt_uint32_t addr;
    rt_uint32_t size;
} fb_t;

struct rt_hdmi_fb_device
{
    struct rt_device parent;
    fb_t fb;
};

extern fb_t fb_info;
void print_fb_info();

#endif/* __DRV_FB_H__ */
