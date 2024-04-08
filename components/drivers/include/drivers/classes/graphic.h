/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-10-11     zmshahaha    move from <rtdef.h>
 */

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <rtdef.h>

/**
 * cursor control command
 */
#define RT_DEVICE_CTRL_CURSOR_SET_POSITION  0x10
#define RT_DEVICE_CTRL_CURSOR_SET_TYPE      0x11

/**
 * graphic device control command
 */
#define RTGRAPHIC_CTRL_RECT_UPDATE      (RT_DEVICE_CTRL_BASE(Graphic) + 0)
#define RTGRAPHIC_CTRL_POWERON          (RT_DEVICE_CTRL_BASE(Graphic) + 1)
#define RTGRAPHIC_CTRL_POWEROFF         (RT_DEVICE_CTRL_BASE(Graphic) + 2)
#define RTGRAPHIC_CTRL_GET_INFO         (RT_DEVICE_CTRL_BASE(Graphic) + 3)
#define RTGRAPHIC_CTRL_SET_MODE         (RT_DEVICE_CTRL_BASE(Graphic) + 4)
#define RTGRAPHIC_CTRL_GET_EXT          (RT_DEVICE_CTRL_BASE(Graphic) + 5)
#define RTGRAPHIC_CTRL_SET_BRIGHTNESS   (RT_DEVICE_CTRL_BASE(Graphic) + 6)
#define RTGRAPHIC_CTRL_GET_BRIGHTNESS   (RT_DEVICE_CTRL_BASE(Graphic) + 7)
#define RTGRAPHIC_CTRL_GET_MODE         (RT_DEVICE_CTRL_BASE(Graphic) + 8)
#define RTGRAPHIC_CTRL_GET_STATUS       (RT_DEVICE_CTRL_BASE(Graphic) + 9)
#define RTGRAPHIC_CTRL_PAN_DISPLAY      (RT_DEVICE_CTRL_BASE(Graphic) + 10)
#define RTGRAPHIC_CTRL_WAIT_VSYNC       (RT_DEVICE_CTRL_BASE(Graphic) + 11)

/* graphic device */
enum
{
    RTGRAPHIC_PIXEL_FORMAT_MONO = 0,
    RTGRAPHIC_PIXEL_FORMAT_GRAY4,
    RTGRAPHIC_PIXEL_FORMAT_GRAY16,
    RTGRAPHIC_PIXEL_FORMAT_RGB332,
    RTGRAPHIC_PIXEL_FORMAT_RGB444,
    RTGRAPHIC_PIXEL_FORMAT_RGB565,
    RTGRAPHIC_PIXEL_FORMAT_RGB565P,
    RTGRAPHIC_PIXEL_FORMAT_BGR565 = RTGRAPHIC_PIXEL_FORMAT_RGB565P,
    RTGRAPHIC_PIXEL_FORMAT_RGB666,
    RTGRAPHIC_PIXEL_FORMAT_RGB888,
    RTGRAPHIC_PIXEL_FORMAT_BGR888,
    RTGRAPHIC_PIXEL_FORMAT_ARGB888,
    RTGRAPHIC_PIXEL_FORMAT_ABGR888,
    RTGRAPHIC_PIXEL_FORMAT_RESERVED,
};

/**
 * build a pixel position according to (x, y) coordinates.
 */
#define RTGRAPHIC_PIXEL_POSITION(x, y)  ((x << 16) | y)

/**
 * graphic device information structure
 */
struct rt_device_graphic_info
{
    rt_uint8_t  pixel_format;                           /**< graphic format */
    rt_uint8_t  bits_per_pixel;                         /**< bits per pixel */
    rt_uint16_t pitch;                                  /**< bytes per line */

    rt_uint16_t width;                                  /**< width of graphic device */
    rt_uint16_t height;                                 /**< height of graphic device */

    rt_uint8_t *framebuffer;                            /**< frame buffer */
    rt_uint32_t smem_len;                               /**< allocated frame buffer size */
};

/**
 * rectangle information structure
 */
struct rt_device_rect_info
{
    rt_uint16_t x;                                      /**< x coordinate */
    rt_uint16_t y;                                      /**< y coordinate */
    rt_uint16_t width;                                  /**< width */
    rt_uint16_t height;                                 /**< height */
};

/**
 * graphic operations
 */
struct rt_device_graphic_ops
{
    void (*set_pixel) (const char *pixel, int x, int y);
    void (*get_pixel) (char *pixel, int x, int y);

    void (*draw_hline)(const char *pixel, int x1, int x2, int y);
    void (*draw_vline)(const char *pixel, int x, int y1, int y2);

    void (*blit_line) (const char *pixel, int x, int y, rt_size_t size);
};
#define rt_graphix_ops(device)          ((struct rt_device_graphic_ops *)(device->user_data))

#endif /* __GRAPHIC_H__ */
