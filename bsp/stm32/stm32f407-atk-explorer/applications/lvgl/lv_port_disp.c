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
#include <board.h>
#include <drv_lcd.h>

#define LCD_DEV_NAME "lcd"
// #define MY_DISP_HOR_RES LCD_W
// #define DISP_BUFFER_LINES 70

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

/*Descriptor of a display driver*/
static lv_disp_drv_t disp_drv;

/*Static or global buffer(s). The second buffer is optional*/
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma location=0x68000000
lv_color_t buf_1[LCD_H * LCD_W];
#elif defined ( __CC_ARM )  /* MDK ARM Compiler */
__attribute__((at(0x68000000))) lv_color_t buf_1[LCD_H * LCD_W];
#elif defined ( __clang__ ) /* MDK ARM Compiler v6 */
__attribute__((section(".ARM.__at_0x68000000"))) lv_color_t buf_1[LCD_H * LCD_W];
#elif defined ( __GNUC__ ) /* GNU Compiler */
lv_color_t buf_1[LCD_H * LCD_W] __attribute__((section(".MCUlcdgrambysram")));
#ifdef RT_USING_MEMHEAP_AS_HEAP
#error "You should modify this logic, such as use 'rt_malloc' to create lvgl buf"
#endif
#endif

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /* color_p is a buffer pointer; the buffer is provided by LVGL */
    lcd_fill_array(area->x1, area->y1, area->x2, area->y2, color_p);

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}

void lv_port_disp_init(void)
{
    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, LCD_H * LCD_W);

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LCD_W;
    disp_drv.ver_res = LCD_H;

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Init lcd device*/
    rt_device_t lcd_dev = rt_device_find(LCD_DEV_NAME);
    rt_device_open(lcd_dev, RT_DEVICE_FLAG_STANDALONE);
    disp_drv.user_data = lcd_dev;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}
