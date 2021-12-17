/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     The first version
 */
#include <lvgl.h>
#include <drv_clcd.h>

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

static rt_device_t lcd_device = 0;
static struct rt_device_graphic_info info;

static lv_disp_drv_t disp_drv;  /*Descriptor of a display driver*/

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void lcd_fb_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t x;
    uint32_t y;
    uint32_t location = 0;

    /* 16 bit per pixel */
    lv_color16_t *fbp16 = (lv_color16_t *)info.framebuffer;

    for (y = area->y1; y <area->y2 + 1; y++)
    {
        for (x = area->x1; x <area->x2 + 1; x++)
        {
            location = x + y * info.width;
            fbp16[location].full = color_p->full;
            color_p++;
        }
    }

    lv_disp_flush_ready(disp_drv);
}

void lv_port_disp_init(void)
{
    rt_err_t result;
    lv_color_t *fbuf1, *fbuf2;

    lcd_device = rt_device_find("lcd");
    if (lcd_device == 0)
    {
        rt_kprintf("error!\n");
        return;
    }
    result = rt_device_open(lcd_device, 0);
    if (result != RT_EOK)
    {
        rt_kprintf("error!\n");
        return;
    }
    /* get framebuffer address */
    result = rt_device_control(lcd_device, RTGRAPHIC_CTRL_GET_INFO, &info);
    if (result != RT_EOK)
    {
        rt_kprintf("error!\n");
        /* get device information failed */
        return;
    }

    RT_ASSERT(info.bits_per_pixel == 8 || info.bits_per_pixel == 16 ||
              info.bits_per_pixel == 24 || info.bits_per_pixel == 32);

    fbuf1 = rt_malloc(info.width * info.height * sizeof(lv_color_t));
    if (fbuf1 == RT_NULL)
    {
        rt_kprintf("Error: alloc disp buf fail\n");
        return;
    }

    fbuf2 = rt_malloc(info.width * info.height * sizeof(lv_color_t));
    if (fbuf2 == RT_NULL)
    {
        rt_kprintf("Error: alloc disp buf fail\n");
        rt_free(fbuf1);
        return;
    }

    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, fbuf1, fbuf2, info.width * info.height);

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = info.width;
    disp_drv.ver_res = info.height;

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = lcd_fb_flush;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}
