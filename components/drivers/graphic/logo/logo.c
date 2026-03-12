/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "graphic.logo"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#if __STARTUP_LOGO_WIDTH__ && __STARTUP_LOGO_HEIGHT__ && __STARTUP_LOGO_COLOR_MAX__
static rt_uint8_t builtin_logo[] =
{
    #include "logo.inc"
};

static void *startup_logo = builtin_logo;
#else
static void *startup_logo = RT_NULL;
#endif
static int startup_logo_width = __STARTUP_LOGO_WIDTH__;
static int startup_logo_height = __STARTUP_LOGO_HEIGHT__;
static int startup_logo_color_max = __STARTUP_LOGO_COLOR_MAX__;

rt_err_t rt_graphic_logo_change(void *data, int width, int height, int color_max)
{
    if (!data && !width && !height && !color_max)
    {
        /* Disable logo */
        startup_logo = RT_NULL;
    }
    else if (data && width > 0 && height > 0 && color_max > 0)
    {
        startup_logo = data;
        startup_logo_width = width;
        startup_logo_height = height;
        startup_logo_color_max = color_max;
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_ubase_t to_grayscale(rt_ubase_t red, rt_ubase_t green, rt_ubase_t blue)
{
    return (299 * red + 587 * green + 114 * blue) / 1000;
}

static rt_ubase_t to_color(rt_ubase_t color, rt_ubase_t in_color_max, rt_ubase_t out_color_max)
{
    return color * out_color_max / in_color_max;
}

static rt_ubase_t gray_reordering(rt_ubase_t red, rt_ubase_t red_off,
                                  rt_ubase_t green, rt_ubase_t green_off,
                                  rt_ubase_t blue, rt_ubase_t blue_off,
                                  rt_ubase_t in_color_max, rt_ubase_t out_color_max)
{
    return to_grayscale(to_color(red, in_color_max, out_color_max),
                        to_color(green, in_color_max, out_color_max),
                        to_color(blue, in_color_max, out_color_max));
}

static rt_ubase_t rgb_reordering(rt_ubase_t red, rt_ubase_t red_off,
                                 rt_ubase_t green, rt_ubase_t green_off,
                                 rt_ubase_t blue, rt_ubase_t blue_off,
                                 rt_ubase_t in_color_max, rt_ubase_t out_color_max)
{
    return (to_color(red, in_color_max, out_color_max) << red_off) |
           (to_color(green, in_color_max, out_color_max) << green_off) |
           (to_color(blue, in_color_max, out_color_max) << blue_off);
}

rt_err_t rt_graphic_logo_render(struct rt_graphic_device *gdev)
{
    rt_err_t err;
    int fb_color_max;
    rt_ubase_t xlate, none_alpha;
    rt_ubase_t red_off, green_off, blue_off;
    rt_ubase_t red_mask, green_mask, blue_mask;
    rt_uint8_t *logo, *fb, bytes_per_pixel;
    rt_ubase_t (*color_reordering)(rt_ubase_t, rt_ubase_t,
                                   rt_ubase_t, rt_ubase_t,
                                   rt_ubase_t, rt_ubase_t,
                                   rt_ubase_t, rt_ubase_t);
    struct fb_var_screeninfo var;
    struct rt_device_rect_info rect;
    struct rt_device_graphic_info info;
    struct rt_device *fbdev = &gdev->parent;

    if (!startup_logo)
    {
        return RT_EOK;
    }

    if ((err = rt_device_open(fbdev, 0)))
    {
        return err;
    }

    if ((err = rt_device_control(fbdev, FBIOGET_VSCREENINFO, &var)))
    {
        LOG_E("Get framebuffer %s error = %s", "var", rt_strerror(err));

        goto _close_fbdev;
    }

    if (startup_logo_width > var.xres || startup_logo_height > var.yres)
    {
        LOG_E("PPM logo[%u, %u] Out of screen[%u, %u]",
                startup_logo_width, startup_logo_height, var.xres, var.yres);

        err = -RT_EINVAL;
        goto _close_fbdev;
    }

    if ((err = rt_device_control(fbdev, RTGRAPHIC_CTRL_GET_INFO, &info)))
    {
        LOG_E("Get framebuffer %s error = %s", "info", rt_strerror(err));

        goto _close_fbdev;
    }

    if ((err = rt_device_control(fbdev, RTGRAPHIC_CTRL_POWERON, RT_NULL)))
    {
        LOG_E("Power on graphic device error = %s", rt_strerror(err));

        goto _close_fbdev;
    }

    if (var.grayscale)
    {
        color_reordering = &gray_reordering;
    }
    else
    {
        color_reordering = &rgb_reordering;
    }

    bytes_per_pixel = var.bits_per_pixel / 8;
    xlate = (var.xres - startup_logo_width) * bytes_per_pixel;

    rect.x = (var.xres - startup_logo_width) >> 1;
    rect.y = (var.yres - startup_logo_height) >> 1;
    rect.width = startup_logo_width,
    rect.height = startup_logo_height,

    fb = (void *)info.framebuffer;
    fb += rect.x * bytes_per_pixel + rect.y * info.pitch;

    logo = startup_logo;

    red_off = var.red.offset;
    red_mask = RT_GENMASK(var.red.length - 1, 0);
    green_off = var.green.offset;
    green_mask = RT_GENMASK(var.green.length - 1, 0);
    blue_off = var.blue.offset;
    blue_mask = RT_GENMASK(var.blue.length - 1, 0);

    fb_color_max = rt_max_t(int, rt_max_t(int, red_mask, green_mask), blue_mask);

    if (var.transp.length)
    {
        none_alpha = RT_GENMASK(var.transp.length - 1, 0) << var.transp.offset;
    }
    else
    {
        none_alpha = 0;
    }

    for (int dy = 0; dy < startup_logo_height; ++dy)
    {
        for (int dx = 0; dx < startup_logo_width; ++dx)
        {
            rt_ubase_t color = color_reordering(logo[0], red_off,
                                                logo[1], green_off,
                                                logo[2], blue_off,
                                                fb_color_max, startup_logo_color_max) |
                                                none_alpha;

            rt_memcpy(fb, &color, bytes_per_pixel);

            fb += bytes_per_pixel;
            logo += 3;
        }

        fb += xlate;
    }

    rt_device_control(fbdev, RTGRAPHIC_CTRL_RECT_UPDATE, &rect);
    rt_device_control(fbdev, RTGRAPHIC_CTRL_WAIT_VSYNC, RT_NULL);

    /* Complete */
    startup_logo = RT_NULL;

    /*
     * Should recycle here, logo takes up too much memory
     * if builtin is not RT_GRAPHIC_LOGO_NONE.
     */

_close_fbdev:
    rt_device_close(fbdev);

    return err;
}
