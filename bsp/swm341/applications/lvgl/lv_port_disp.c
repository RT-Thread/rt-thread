/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-01     Rudy Lo      The first version
 */

#include <lvgl.h>
#include <rtthread.h>
#include "lv_conf.h"
#include "drv_rgb_lcd.h"

#define DRV_DEBUG
#define LOG_TAG "drv.lvgl"
#include <drv_log.h>

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

/*Descriptor of a display driver*/
static lv_disp_drv_t disp_drv;

static lv_color_t *lcdbuf_1;
static lv_color_t *lcdbuf_2;

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /* color_p is a buffer pointer; the buffer is provided by LVGL */
    LCD->L[0].ADDR = (uint32_t)color_p;
    LCD->CR |= (1 << LCD_CR_VBPRELOAD_Pos);
    while(LCD->CR & LCD_CR_VBPRELOAD_Msk) __NOP();
    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}

void lv_port_disp_init(void)
{
    struct swm_rgb_lcd_device *rgb_lcd;
    rgb_lcd = (struct swm_rgb_lcd_device *)rt_device_find("rgb_lcd");
    lcdbuf_1 = (lv_color_t *)rgb_lcd->lcd_info.framebuffer;
    lcdbuf_2 = (lv_color_t *)rt_malloc_align(LCD_BUF_SIZE,4);
    if(lcdbuf_2 == RT_NULL)
    {
        LOG_E("init lcd buffer failed!\n");
        return;
    }
    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, lcdbuf_1, lcdbuf_2, LV_HOR_RES * LV_VER_RES);

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LV_HOR_RES;
    disp_drv.ver_res = LV_VER_RES;

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Required for Example 3)*/
    disp_drv.full_refresh = 1;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}
