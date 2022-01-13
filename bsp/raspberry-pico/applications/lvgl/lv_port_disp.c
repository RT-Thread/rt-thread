/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     The first version
 * 2021-12-24     	Rb         Refresh using dma2d
 */
#include <lvgl.h>
#include "drv_lcd.h"

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;
static lv_disp_drv_t disp_drv; /*Descriptor of a display driver*/

#define DISP_BUF_SIZE        (LV_HOR_RES_MAX * LV_VER_RES_MAX)

static const lv_color_t * buf_to_flush;

static lv_disp_drv_t g_disp_drv;
static lv_color_t lv_disp_buf1[DISP_BUF_SIZE];

static void lcd_fb_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    LCD_DisplayWindows(area->x1, area->y1, area->x2, area->y2, (uint16_t*) color_p);
    lv_disp_flush_ready(disp_drv);
}

void lv_port_disp_init(void)
{
    rt_err_t result;

    SPI_Init();
    LCD_Init(HORIZONTAL);

    /*Initialize `disp_buf` with the buffer(s).*/
    lv_disp_draw_buf_init(&disp_buf, lv_disp_buf1, RT_NULL, DISP_BUF_SIZE);

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LV_VER_RES_MAX;
    disp_drv.ver_res = LV_HOR_RES_MAX;

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = lcd_fb_flush;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);

    g_disp_drv = disp_drv;
}
