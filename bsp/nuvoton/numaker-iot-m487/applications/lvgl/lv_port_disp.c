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

#define LOG_TAG             "lvgl.disp"
#define DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL DBG_ERROR
#define DBG_COLOR
#include <rtdbg.h>

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;
static lv_disp_drv_t disp_drv;  /*Descriptor of a display driver*/

static rt_device_t lcd_device = 0;
static struct rt_device_graphic_info info;

static void lcd_fb_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    /* Rendering */
    struct rt_device_rect_info rect;

    rect.x = area->x1;
    rect.y = area->y1;
    rect.width = area->x2 - area->x1 + 1;
    rect.height = area->y2 - area->y1 + 1;

    rt_device_control(lcd_device, RTGRAPHIC_CTRL_RECT_UPDATE, &rect);
    lv_disp_flush_ready(disp_drv);
}

void lcd_perf_monitor(struct _lv_disp_drv_t *disp_drv, uint32_t time, uint32_t px)
{
    rt_kprintf("Elapsed: %dms, Pixel: %d, Bytes:%d\n", time, px, px * sizeof(lv_color_t));
}

void lv_port_disp_init(void)
{
    rt_err_t result;
    void *buf1 = RT_NULL;

    lcd_device = rt_device_find("lcd");
    if (lcd_device == 0)
    {
        LOG_E("error!");
        return;
    }

    /* get framebuffer address */
    result = rt_device_control(lcd_device, RTGRAPHIC_CTRL_GET_INFO, &info);
    if (result != RT_EOK && info.framebuffer == RT_NULL)
    {
        LOG_E("error!");
        /* get device information failed */
        return;
    }

    RT_ASSERT(info.bits_per_pixel == 8 || info.bits_per_pixel == 16 ||
              info.bits_per_pixel == 24 || info.bits_per_pixel == 32);

    buf1 = (void *)info.framebuffer;
    rt_kprintf("LVGL: Use one buffers - buf1@%08x, size: %d bytes\n", buf1, info.smem_len);

    /*Initialize `disp_buf` with the buffer(s).*/
    lv_disp_draw_buf_init(&disp_buf, buf1, RT_NULL, info.smem_len / (info.bits_per_pixel / 8));

    result = rt_device_open(lcd_device, 0);
    if (result != RT_EOK)
    {
        LOG_E("error!");
        return;
    }

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = info.width;
    disp_drv.ver_res = info.height;

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Write the internal buffer (draw_buf) to the display*/
    disp_drv.flush_cb = lcd_fb_flush;

    /* Called after every refresh cycle to tell the rendering and flushing time + the number of flushed pixels */
    //disp_drv.monitor_cb = lcd_perf_monitor;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}
