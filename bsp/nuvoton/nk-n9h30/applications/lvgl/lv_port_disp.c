/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-17     Wayne        The first version
 */
#include <lvgl.h>
#include "nu_2d.h"

#define LOG_TAG             "lvgl.disp"
#define DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL DBG_ERROR
#define DBG_COLOR
#include <rtdbg.h>

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;
static rt_device_t lcd_device = 0;
static struct rt_device_graphic_info info;
static lv_disp_drv_t disp_drv;  /*Descriptor of a display driver*/

static void nu_flush_direct(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    lv_disp_t *psDisp = _lv_refr_get_disp_refreshing();
    void *pvDstReDraw;

    /* Use PANDISPLAY */
    rt_device_control(lcd_device, RTGRAPHIC_CTRL_PAN_DISPLAY, color_p);

    /* Need to do on-/off- screen buffer synchronization. Here, we do a source-copying using GE2D engine. */
    if (disp_drv->draw_buf->buf1 == color_p)
        pvDstReDraw = disp_drv->draw_buf->buf2;
    else
        pvDstReDraw = disp_drv->draw_buf->buf1;

    // Enter GE2D ->
    ge2dInit(sizeof(lv_color_t) * 8, info.width, info.height, pvDstReDraw);
    ge2dBitblt_SetAlphaMode(-1, 0, 0);
    ge2dBitblt_SetDrawMode(-1, 0, 0);
    ge2dSpriteBlt_Screen(0, 0, info.width, info.height, (void *)color_p);
    // -> Leave GE2D

    /* WAIT_VSYNC */
    rt_device_control(lcd_device, RTGRAPHIC_CTRL_WAIT_VSYNC, RT_NULL);

    lv_disp_flush_ready(disp_drv);
}

static void nu_flush_full_refresh(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    /* Use PANDISPLAY+WAIT_VSYNC without H/W copying. */
    rt_device_control(lcd_device, RTGRAPHIC_CTRL_PAN_DISPLAY, color_p);
    rt_device_control(lcd_device, RTGRAPHIC_CTRL_WAIT_VSYNC, RT_NULL);

    lv_disp_flush_ready(disp_drv);
}

static void nu_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    int32_t flush_area_w = lv_area_get_width(area);
    int32_t flush_area_h = lv_area_get_height(area);

    //rt_kprintf("[%s %08x] %dx%d %d %d %d %d\n", __func__, color_p, flush_area_w, flush_area_h, area->x1, area->y1, area->x2, area->y2 );

    /* Update dirty region. */
    // Enter GE2D ->
    ge2dInit(sizeof(lv_color_t) * 8, info.width, info.height, (void *)info.framebuffer);
    ge2dBitblt_SetAlphaMode(-1, 0, 0);
    ge2dBitblt_SetDrawMode(-1, 0, 0);

    ge2dSpriteBlt_Screen(area->x1, area->y1, flush_area_w, flush_area_h, (void *)color_p);
    // -> Leave GE2D

    lv_disp_flush_ready(disp_drv);
}


static void nu_fill_cb(struct _lv_disp_drv_t *disp_drv, lv_color_t *dest_buf, lv_coord_t dest_width,
                       const lv_area_t *fill_area, lv_color_t color)
{
    int32_t fill_area_w = lv_area_get_width(fill_area);
    int32_t fill_area_h = lv_area_get_height(fill_area);

    //rt_kprintf("[%s %08x] %dx%d %d %d %d %d\n", __func__, dest_buf, fill_area_w, fill_area_h, fill_area->x1, fill_area->y1, fill_area->x2, fill_area->y2 );

    if (lv_area_get_size(fill_area) < 3600)
    {
        /*Software filling*/
        int y;
        lv_color_t *disp_buf_first = dest_buf + dest_width * fill_area->y1 + fill_area->x1;
        for (y = 0; y < fill_area_h; y++)
        {
            lv_color_fill(disp_buf_first, color, fill_area_w);
            disp_buf_first += dest_width;
        }
    }
    else
    {
        /*Hardware filling*/
        if (disp_drv->direct_mode || disp_drv->full_refresh)
        {
            // Enter GE2D ->
            ge2dInit(sizeof(lv_color_t) * 8, info.width, info.height, (void *)dest_buf);
        }
        else
        {
            // Enter GE2D ->
            ge2dInit(sizeof(lv_color_t) * 8, fill_area_w, fill_area_h, (void *)dest_buf);
        }

        ge2dClip_SetClip(fill_area->x1, fill_area->y1, fill_area->x2, fill_area->y2);
        if (sizeof(lv_color_t) == 4)
        {
            ge2dFill_Solid(fill_area->x1, fill_area->y1, fill_area_w, fill_area_h, color.full);
        }
        else if (sizeof(lv_color_t) == 2)
        {
            ge2dFill_Solid_RGB565(fill_area->x1, fill_area->y1, fill_area_w, fill_area_h, color.full);
        }
        ge2dClip_SetClip(-1, 0, 0, 0);
        // -> Leave GE2D
    }
}

void nu_perf_monitor(struct _lv_disp_drv_t *disp_drv, uint32_t time, uint32_t px)
{
    rt_kprintf("Elapsed: %dms, Pixel: %d, Bytes:%d, %d%\n", time, px, px * sizeof(lv_color_t), px * 100 / disp_drv->draw_buf->size);
}

void lv_port_disp_init(void)
{
    rt_err_t result;
    void *buf_1 = RT_NULL;
    void *buf_2 = RT_NULL;
    uint32_t u32FBSize;

    lcd_device = rt_device_find("lcd");
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

    RT_ASSERT(info.bits_per_pixel == 8 || info.bits_per_pixel == 16 ||
              info.bits_per_pixel == 24 || info.bits_per_pixel == 32);

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = info.width;
    disp_drv.ver_res = info.height;
    //disp_drv.full_refresh = 1;
    disp_drv.direct_mode = 1;
    u32FBSize = info.height * info.width * (info.bits_per_pixel / 8);

    if (disp_drv.full_refresh || disp_drv.direct_mode)
    {
        buf_1 = (void *)info.framebuffer;
        buf_2 = (void *)((uint32_t)buf_1 + u32FBSize);
        rt_kprintf("LVGL: Two screen-sized buffers(%s) - buf_1@%08x, buf_2@%08x\n", (disp_drv.full_refresh == 1) ? "full_refresh" : "direct_mode", buf_1, buf_2);

        if (disp_drv.direct_mode)
            disp_drv.flush_cb = nu_flush_direct;
        else
            disp_drv.flush_cb = nu_flush_full_refresh;
    }
    else
    {
        buf_1 = (void *)(((uint32_t)info.framebuffer) + u32FBSize);
        buf_2 = (void *)((uint32_t)buf_1 + u32FBSize);
        rt_kprintf("LVGL: Two screen-sized buffers - buf_1@%08x, buf_2@%08x\n", buf_1, buf_2);
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_PAN_DISPLAY, info.framebuffer);

        disp_drv.flush_cb = nu_flush;
    }

    /*Initialize `disp_buf` with the buffer(s).*/
    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, info.width * info.height);

    result = rt_device_open(lcd_device, 0);
    if (result != RT_EOK)
    {
        LOG_E("error!");
        return;
    }

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Fill a memory with a color (GPU only)*/
    disp_drv.gpu_fill_cb = nu_fill_cb;

    /*Called after every refresh cycle to tell the rendering and flushing time + the number of flushed pixels*/
    //disp_drv.monitor_cb = nu_perf_monitor;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}
