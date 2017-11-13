/*
 * File      : rtgui_demo.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-8      Tangyuxin    first version
 */

#include <rtthread.h>

// #define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...)   rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)   
#endif

#ifdef RT_USING_GUIENGINE

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_app.h>

#include <rtgui/widgets/window.h>
#include <rtgui/dc.h>

struct rtgui_win *main_win;
rt_bool_t dc_event_handler(struct rtgui_object *object, rtgui_event_t *event);

static void rt_gui_demo_entry(void *parameter)
{
    struct rtgui_app *app;

    DEBUG_PRINTF("gui demo entry\n");

    /* create gui app */
    app = rtgui_app_create("gui_demo");
    if (app == RT_NULL)
    {
        DEBUG_PRINTF("rtgui_app_create faild\n");
        return;    
    }
    
    /* create main window */
    main_win = rtgui_mainwin_create(RT_NULL, 
                                    "UiWindow", RTGUI_WIN_STYLE_NO_TITLE | RTGUI_WIN_STYLE_NO_BORDER);
    if (main_win == RT_NULL)
    {
        DEBUG_PRINTF("main_win is null\n");
        rtgui_app_destroy(app);
        return;
    }

    rtgui_object_set_event_handler(RTGUI_OBJECT(main_win), dc_event_handler);

    DEBUG_PRINTF("rtgui_win_show\n");
    rtgui_win_show(main_win, RT_FALSE);

    DEBUG_PRINTF("rtgui_app_run\n");
    rtgui_app_run(app);

    DEBUG_PRINTF("rtgui_win_destroy\n");
    rtgui_win_destroy(main_win);

    DEBUG_PRINTF("rtgui_app_destroy\n");
    rtgui_app_destroy(app);    
}

rt_bool_t dc_event_handler(struct rtgui_object *object, rtgui_event_t *event)
{
    struct rtgui_widget *widget = RTGUI_WIDGET(object);

    if (event->type == RTGUI_EVENT_PAINT)
    {
        struct rtgui_dc *dc;
        rtgui_rect_t rect;

        DEBUG_PRINTF("\r\n RTGUI_EVENT_PAINT \r\n");
        rtgui_win_event_handler(RTGUI_OBJECT(widget), event);

        rtgui_widget_get_rect(widget, &rect);
        DEBUG_PRINTF("widget react x1: %d, y1: %d, x2: %d, y2: %d\r\n",
                                rect.x1, rect.y1, rect.x2, rect.y2);

        dc = rtgui_dc_begin_drawing(widget);
        if (dc == RT_NULL)
        {
            DEBUG_PRINTF("\r\n dc is null \r\n");
            return RT_FALSE;
        }

        rtgui_dc_draw_line(dc, rect.x1, rect.y1, rect.x2, rect.y2);
        rtgui_dc_draw_line(dc, rect.x1, rect.y2, rect.x2, rect.y1);
        
        rect.x1 += (rect.x2 - rect.x1) / 2;
        rect.y1 += (rect.y2 - rect.y1) / 2;
        rtgui_dc_draw_text_stroke(dc, __DATE__"--"__TIME__, &rect, HIGH_LIGHT, BLUE);

        rtgui_dc_end_drawing(dc,RT_TRUE);
    }
    return RT_FALSE;
}

int rt_gui_demo_init(void)
{
    rt_thread_t tid;
    rt_device_t device;
    rt_err_t  err;
    
    device = rt_device_find("lcd");
    if (device == RT_NULL)
    {
        rt_kprintf("Not found LCD driver\n");
        return RT_ERROR;
    }
    
    err = rt_device_open(device, RT_DEVICE_OFLAG_RDWR);
    if (err != RT_EOK)
    {
        rt_kprintf("Open LCD driver fail\n");
        return RT_ERROR;
    }
    
    /* set graphic device */
    rtgui_graphic_set_device(device);
    
    tid = rt_thread_create("mygui",
        rt_gui_demo_entry, RT_NULL,
        2048, 25, 10);

    if (tid != RT_NULL)
        rt_thread_startup(tid);
    
    return 0;
}
INIT_APP_EXPORT(rt_gui_demo_init);
#endif /* RT_USING_GUIENGINE */
