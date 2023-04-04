/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-04     Rbb666       The first version
 */
#include <lvgl.h>

#ifdef PKG_USING_ILI9341
    #include "lcd_ili9341.h"
#endif

#define COLOR_BUFFER  (LV_HOR_RES_MAX * LV_VER_RES_MAX)

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

/*Descriptor of a display driver*/
static lv_disp_drv_t disp_drv;
static struct rt_device_graphic_info info;

/*Static or global buffer(s). The second buffer is optional*/
static lv_color_t buf_1[COLOR_BUFFER];

static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
#ifdef PKG_USING_ILI9341
    lcd_fill_array_spi(area->x1, area->y1, area->x2, area->y2, color_p);
#endif
    lv_disp_flush_ready(disp_drv);
}

void lv_port_disp_init(void)
{
#ifdef PKG_USING_ILI9341
    spi_lcd_init(25);
#endif
    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, COLOR_BUFFER);

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}
