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
#include "mmu.h"
#include "lv_gpu_n9h30_ge2d.h"

#define LOG_TAG             "lvgl.disp"
#define DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL DBG_INFO
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

static uint32_t LV_USE_GPU_N9H30_GE2D = 1;

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
    if (IS_CACHEABLE_VRAM(color_p))
        mmu_clean_dcache((uint32_t)color_p, disp_drv->draw_buf->size * sizeof(lv_color_t));

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
    int32_t area_w = lv_area_get_width(area);
    int32_t area_h = lv_area_get_height(area);

    lv_draw_sw_blend_dsc_t blend_flush = {0};
    lv_draw_ctx_t draw_flush = {0};
    lv_area_t flush_area = {0, 0, info.width - 1, info.height - 1 };

    //rt_kprintf("[nu_flush %d %08x] %dx%d %d %d\n", lv_area_get_size(area), color_p, area_w, area_h, area->x1, area->y1 );

    blend_flush.blend_area = area;
    blend_flush.src_buf    = color_p;
    blend_flush.mask_buf   = NULL;
    blend_flush.opa        = LV_OPA_MAX;
    blend_flush.blend_mode = LV_BLEND_MODE_NORMAL;

    draw_flush.buf         = info.framebuffer;
    draw_flush.clip_area   = &flush_area;
    draw_flush.buf_area    = &flush_area;

    lv_draw_n9h30_ge2d_blend(&draw_flush, (const lv_draw_sw_blend_dsc_t *)&blend_flush);

    if (!u32FirstFlush)
    {
        /* Enable backlight at first flushing. */
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_POWERON, RT_NULL);
        u32FirstFlush = 1;
    }

    lv_disp_flush_ready(disp_drv);
}

void nu_perf_monitor(struct _lv_disp_drv_t *disp_drv, uint32_t time, uint32_t px)
{
    LOG_I("Elapsed: %dms, Pixel: %d, Bytes:%d, %d%\n", time, px, px * sizeof(lv_color_t), px * 100 / disp_drv->draw_buf->size);
}

void lv_port_disp_init(void)
{
    rt_err_t result;
    void *buf1 = RT_NULL;
    void *buf2 = RT_NULL;
    uint32_t u32FBSize;

    lcd_device = rt_device_find(NU_PKG_LVGL_RENDERING_LAYER);
    if (lcd_device == RT_NULL)
    {
        LOG_E("error!");
        return;
    }

    if (!LV_VERSION_CHECK(8, 3, 0))
    {
        LV_USE_GPU_N9H30_GE2D = 0;
    }
    LOG_I("LVGL: %s drawing using 2DGE", LV_USE_GPU_N9H30_GE2D ? "Enabled" : "Disabled");

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
    u32FBSize = info.height * info.width * (info.bits_per_pixel / 8);

#if (LV_USE_ANTI_TEARING==1)
    disp_drv.full_refresh = 1;
#endif
    LOG_I("LVGL: %s anti-tearing", disp_drv.full_refresh ? "Enabled" : "Disabled");

    if (disp_drv.full_refresh)
    {
        buf1 = (void *)((uint32_t)info.framebuffer & ~BIT31); // Use Cacheable VRAM
        buf2 = (void *)((uint32_t)buf1 + u32FBSize);
        buf3_next = (void *)((uint32_t)buf2 + u32FBSize);
        LOG_I("LVGL: Use triple screen-sized buffers(full_refresh) - buf1@%08x, buf2@%08x, buf3_next@%08x", buf1, buf2, buf3_next);

        disp_drv.flush_cb = nu_flush_full_refresh;
    }
    else
    {
        buf1 = (void *)(((uint32_t)info.framebuffer & ~BIT31) + u32FBSize); // Use Cacheable VRAM
        buf2 = (void *)((uint32_t)buf1 + u32FBSize);
        LOG_I("LVGL: Use two screen-sized buffers - buf1@%08x, buf2@%08x", buf1, buf2);
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_PAN_DISPLAY, info.framebuffer);

        disp_drv.flush_cb = nu_flush;
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

    if (LV_USE_GPU_N9H30_GE2D)
    {
        disp_drv.draw_ctx_init = lv_draw_n9h30_ge2d_ctx_init;
        disp_drv.draw_ctx_deinit = lv_draw_n9h30_ge2d_ctx_init;
        disp_drv.draw_ctx_size = sizeof(lv_draw_n9h30_ge2d_ctx_t);
    }

    /*Called after every refresh cycle to tell the rendering and flushing time + the number of flushed pixels*/
    //disp_drv.monitor_cb = nu_perf_monitor;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}
