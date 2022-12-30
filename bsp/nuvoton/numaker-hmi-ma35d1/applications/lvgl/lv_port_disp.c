/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-17     Wayne        The first version
 */
#include <lvgl.h>
#include "drv_common.h"

#define LOG_TAG             "lvgl.disp"
#define DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL DBG_ERROR
#define DBG_COLOR
#include <rtdbg.h>

#if !defined(NU_PKG_LVGL_RENDERING_LAYER)
    #define NU_PKG_LVGL_RENDERING_LAYER "lcd"
#endif

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;
static rt_device_t lcd_device = 0;
static struct rt_device_graphic_info info;
static lv_disp_drv_t disp_drv;  /*Descriptor of a display driver*/

static void *buf3_next = RT_NULL;

static uint32_t u32FirstFlush = 0;

static void nu_antitearing(lv_disp_draw_buf_t *draw_buf, lv_color_t *color_p)
{
    if (buf3_next)
    {
        /* vsync-none: Use triple screen-sized buffers. */
        if (draw_buf->buf1 == color_p)
            draw_buf->buf1 = buf3_next;
        else
            draw_buf->buf2 = buf3_next;

        draw_buf->buf_act = buf3_next;
        buf3_next = color_p;
    }
    else
    {
        /* vsync-after: Use ping-pong screen-sized buffers only.*/
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_WAIT_VSYNC, RT_NULL);
    }
}

static void nu_flush_full_refresh(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    rt_hw_cpu_dcache_clean(color_p, disp_drv->draw_buf->size * sizeof(lv_color_t));

    /* Use PANDISPLAY without H/W copying */
    rt_device_control(lcd_device, RTGRAPHIC_CTRL_PAN_DISPLAY, color_p);

    nu_antitearing(disp_drv->draw_buf, color_p);

    if (!u32FirstFlush)
    {
        /* Enable backlight at first flushing. */
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_POWERON, RT_NULL);
        u32FirstFlush = 1;
    }

    lv_disp_flush_ready(disp_drv);
}

static void nu_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    int32_t x, y;
    int32_t w = lv_area_get_width(area);
    int32_t h = lv_area_get_height(area);
    lv_color_t *pDisp;

    pDisp = (lv_color_t *)info.framebuffer + (info.width * area->y1 + area->x1);

    /* Update dirty region. */
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            pDisp[x] = color_p[x];
        }
        pDisp += info.width;
        color_p += w;
    }

    if (!u32FirstFlush)
    {
        /* Point to first screen buffer address. */
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_PAN_DISPLAY, info.framebuffer);

        /* Enable backlight at first flushing. */
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_POWERON, RT_NULL);
        u32FirstFlush = 1;
    }
    lv_disp_flush_ready(disp_drv);
}

void nu_perf_monitor(struct _lv_disp_drv_t *disp_drv, uint32_t time, uint32_t px)
{
    rt_kprintf("Elapsed: %dms, Pixel: %d, Bytes:%d, %d%\n", time, px, px * sizeof(lv_color_t), px * 100 / disp_drv->draw_buf->size);
}

void lv_port_disp_init(void)
{
    rt_err_t result;
    void *buf1 = RT_NULL;
    void *buf2 = RT_NULL;
    uint32_t u32FBSize;

    lcd_device = rt_device_find(NU_PKG_LVGL_RENDERING_LAYER);
    if (lcd_device == 0)
    {
        LOG_E("error!");
        return;
    }

    /* get framebuffer address */
    result = rt_device_control(lcd_device, RTGRAPHIC_CTRL_GET_INFO, &info);
    if (result != RT_EOK)
    {
        LOG_E("error!");
        /* get device information failed */
        return;
    }

    /* Disable backlight at startup. */
    rt_device_control(lcd_device, RTGRAPHIC_CTRL_POWEROFF, RT_NULL);

    RT_ASSERT(info.bits_per_pixel == 8 || info.bits_per_pixel == 16 ||
              info.bits_per_pixel == 24 || info.bits_per_pixel == 32);

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = info.width;
    disp_drv.ver_res = info.height;
    //disp_drv.full_refresh = 1;
    u32FBSize = info.height * info.width * (info.bits_per_pixel / 8);

    if (disp_drv.full_refresh)
    {
        disp_drv.flush_cb = nu_flush_full_refresh;
        buf1 = (void *)((uint32_t)info.framebuffer & (~UNCACHEABLE));
        buf2 = (void *)((uint32_t)buf1 + u32FBSize);
        buf3_next = (void *)((uint32_t)buf2 + u32FBSize);

        LOG_I("LVGL: Triple screen-sized buffers(full_refresh) - buf1@%08x, buf2@%08x, buf3_next@%08x\n", buf1, buf2, buf3_next);
    }
    else
    {
        disp_drv.flush_cb = nu_flush;
        buf1 = (void *)(((uint32_t)info.framebuffer & (~UNCACHEABLE)) + u32FBSize);
        buf2 = (void *)((uint32_t)buf1 + u32FBSize);

        rt_kprintf("LVGL: Two screen-sized buffers - buf1@%08x, buf2@%08x\n", buf1, buf2);
    }

    /*Initialize `disp_buf` with the buffer(s).*/
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, info.width * info.height);

    result = rt_device_open(lcd_device, 0);
    if (result != RT_EOK)
    {
        LOG_E("error!");
        return;
    }

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Called after every refresh cycle to tell the rendering and flushing time + the number of flushed pixels*/
    //disp_drv.monitor_cb = nu_perf_monitor;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}
