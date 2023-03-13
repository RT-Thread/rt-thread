/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-24     Rbb666       The first version
 */
#include <lvgl.h>
#include "hal_data.h"

#ifdef BSP_USING_SPI_LCD
    #include "lcd_ili9341.h"
#endif

#define COLOR_BUFFER  (LV_HOR_RES_MAX * LV_VER_RES_MAX / 4)

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

/*Descriptor of a display driver*/
static lv_disp_drv_t disp_drv;

/*Static or global buffer(s). The second buffer is optional*/
// 0x1FFE0000    0x20040000
static lv_color_t buf_1[COLOR_BUFFER];
static lv_color_t buf_2[COLOR_BUFFER];

static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
#ifdef BSP_USING_SPI_LCD
    lcd_fill_array_spi(area->x1, area->y1, area->x2, area->y2, color_p);
#endif
    lv_disp_flush_ready(disp_drv);
}

void lv_port_disp_init(void)
{
#ifdef BSP_USING_SPI_LCD
    spi_lcd_init();
#endif
    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, COLOR_BUFFER);

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
