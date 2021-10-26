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
#include <lcd_port.h>

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

rt_device_t lcd_device = 0;
static struct rt_device_graphic_info info;

static lv_disp_drv_t disp_drv;  /*Descriptor of a display driver*/

typedef struct
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} lv_color24_t;

static void color_to16_maybe(lv_color16_t *dst, lv_color_t *src)
{
#if (LV_COLOR_DEPTH == 16)
    dst->full = src->full;
#else
    dst->ch.blue = src->ch.blue;
    dst->ch.green = src->ch.green;
    dst->ch.red = src->ch.red;
#endif
}

static void color_to24(lv_color24_t *dst, lv_color_t *src)
{
    dst->blue = src->ch.blue;
    dst->green = src->ch.green;
    dst->red = src->ch.red;
}

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void lcd_fb_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    int x1, x2, y1, y2;

    x1 = area->x1;
    x2 = area->x2;
    y1 = area->y1;
    y2 = area->y2;

    /*Return if the area is out the screen*/
    if (x2 < 0)
        return;
    if (y2 < 0)
        return;
    if (x1 > info.width - 1)
        return;
    if (y1 > info.height - 1)
        return;

    /*Truncate the area to the screen*/
    int32_t act_x1 = x1 < 0 ? 0 : x1;
    int32_t act_y1 = y1 < 0 ? 0 : y1;
    int32_t act_x2 = x2 > info.width - 1 ? info.width - 1 : x2;
    int32_t act_y2 = y2 > info.height - 1 ? info.height - 1 : y2;

    uint32_t x;
    uint32_t y;
    long int location = 0;

    /* 8 bit per pixel */
    if (info.bits_per_pixel == 8)
    {
        uint8_t *fbp8 = (uint8_t *)info.framebuffer;
        //TODO color convert maybe
        for (y = act_y1; y <= act_y2; y++)
        {
            for (x = act_x1; x <= act_x2; x++)
            {
                location = (x) + (y)*info.width;
                fbp8[location] = color_p->full;
                color_p++;
            }

            color_p += x2 - act_x2;
        }
    }

    /* 16 bit per pixel */
    else if (info.bits_per_pixel == 16)
    {
        lv_color16_t *fbp16 = (lv_color16_t *)info.framebuffer;

        for (y = act_y1; y <= act_y2; y++)
        {
            for (x = act_x1; x <= act_x2; x++)
            {
                location = (x) + (y)*info.width;
                color_to16_maybe(&fbp16[location], color_p);
                color_p++;
            }

            color_p += x2 - act_x2;
        }
    }

    /* 24 bit per pixel */
    else if (info.bits_per_pixel == 24)
    {
        lv_color24_t *fbp24 = (lv_color24_t *)info.framebuffer;

        for (y = act_y1; y <= act_y2; y++)
        {
            for (x = act_x1; x <= act_x2; x++)
            {
                location = (x) + (y)*info.width;
                color_to24(&fbp24[location], color_p);
                color_p++;
            }

            color_p += x2 - act_x2;
        }
    }

    /* 32 bit per pixel */
    else if (info.bits_per_pixel == 32)
    {
        uint32_t *fbp32 = (uint32_t *)info.framebuffer;
        //TODO
        for (y = act_y1; y <= act_y2; y++)
        {
            for (x = act_x1; x <= act_x2; x++)
            {
                location = (x) + (y)*info.width;
                fbp32[location] = color_p->full;
                color_p++;
            }

            color_p += x2 - act_x2;
        }
    }

    struct rt_device_rect_info rect_info;

    rect_info.x = x1;
    rect_info.y = y1;
    rect_info.width = x2 - x1 + 1;
    rect_info.height = y2 - y1 + 1;
    rt_device_control(lcd_device, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);

    lv_disp_flush_ready(disp_drv);
}

void lv_port_disp_init(void)
{
    rt_err_t result;
    lv_color_t *fbuf;

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

    fbuf = rt_malloc(info.width * info.height / 10);
    if (!fbuf)
    {
        rt_kprintf("Error: alloc disp buf fail\n");
        return;
    }

    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, fbuf, RT_NULL, info.width * 10);

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
