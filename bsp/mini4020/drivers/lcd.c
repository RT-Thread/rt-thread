/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "lcdc.h"
#include "rtthread.h"
#include "board.h"

#include <rtgui/rtgui.h>
#include <rtgui/driver.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>

extern rt_err_t sep4020_lcd_init(void);
extern unsigned long pVideoBuffer;

struct rtgui_graphic_driver _rtgui_lcd_driver;
struct rtgui_graphic_driver_ops _rtgui_graphic_driver_ops;

void radio_rtgui_init(void)
{
    rtgui_rect_t rect;
    rtgui_system_server_init();

    /* register dock panel */
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 320;
    rect.y2 = 25;
    rtgui_panel_register("info", &rect);
    rtgui_panel_set_nofocused("info");

    /* register main panel */
    rect.x1 = 0;
    rect.y1 = 25;
    rect.x2 = 320;
    rect.y2 = 240;
    rtgui_panel_register("main", &rect);
    rtgui_panel_set_default_focused("main");

    _rtgui_graphic_driver_ops.set_pixel=lcd_set_pixel;
    _rtgui_graphic_driver_ops.get_pixel=lcd_get_pixel;
    _rtgui_graphic_driver_ops.draw_hline=lcd_draw_hline;
    _rtgui_graphic_driver_ops.draw_vline=lcd_draw_vline;
    _rtgui_graphic_driver_ops.draw_raw_hline=lcd_draw_raw_hline;

    _rtgui_lcd_driver.bits_per_pixel  = 16;
    _rtgui_lcd_driver.width           = 320;
    _rtgui_lcd_driver.height          = 240;

    _rtgui_lcd_driver.ops = &_rtgui_graphic_driver_ops;

    //_rtgui_lcd_driver.screen_update   = lcd_update;
    //_rtgui_lcd_driver.get_framebuffer = lcd_get_framebuffer;

    sep4020_lcd_init();

    rt_memset((char*)pVideoBuffer,0xff,320*240*2);
    //rt_memcpy((char*)pVideoBuffer,pic,320*240*2);  //TESTING IMAGE

    //此处待修正
    /* add lcd driver into graphic driver */
    // rtgui_graphic_driver_add(&_rtgui_lcd_driver);
}

