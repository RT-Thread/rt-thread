/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>

#include "adc.h"
#include "cpuusage.h"

extern rt_uint16_t adc_value;
static rt_uint8_t index = 0 ;
static rt_bool_t view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
    if (event->type == RTGUI_EVENT_PAINT)
    {
        struct rtgui_dc* dc;
        struct rtgui_rect rect;

        dc = rtgui_dc_begin_drawing(widget);
        if (dc == RT_NULL)
            return RT_FALSE;
        rtgui_widget_get_rect(widget, &rect);

        rtgui_dc_fill_rect(dc, &rect);
        rect.x2 -= 1; rect.y2 -= 1;
        rtgui_dc_draw_hline(dc, rect.x1, rect.x2, rect.y1);
        rtgui_dc_draw_vline(dc, rect.x1, rect.y1, rect.y2);

        rtgui_dc_draw_hline(dc, rect.x1, rect.x2, rect.y2);
        rtgui_dc_draw_vline(dc, rect.x2, rect.y1, rect.y2 + 1);

        /* shrink border */
        rtgui_rect_inflate(&rect, -1);

        /* draw text */
        rtgui_widget_get_rect(widget, &rect);
        rect.y1 += 25;
        rtgui_dc_draw_text(dc, "  FM3 Easy Kit Demo", &rect);
        rect.y1 += 10;
        rtgui_dc_draw_text(dc, "  rt-thread / RTGUI", &rect);
        rtgui_dc_end_drawing(dc, RT_TRUE);

        return RT_FALSE;
    }
    else if (event->type == RTGUI_EVENT_KBD)
    {
        struct rtgui_dc* dc;
        struct rtgui_rect rect;
        struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
        if (ekbd->type == RTGUI_KEYDOWN)
        {
            char key_str[16];
            switch (ekbd->key)
            {
                case RTGUIK_LEFT:
                rt_sprintf(key_str, "%s", "L");
                break;
                case RTGUIK_RIGHT:
                rt_sprintf(key_str, "%s", "R");
                break;
                case RTGUIK_DOWN:
                rt_sprintf(key_str, "%s", "D");
                break;
                case RTGUIK_UP:
                rt_sprintf(key_str, "%s", "U");
                break;
                default:
                rt_sprintf(key_str, "%s", "S");
                break;
            }
            dc = rtgui_dc_begin_drawing(widget);
            if (dc == RT_NULL)
                return RT_FALSE;
            rect.x1 = 118;
            rect.y1 = 1;
            rect.x2 = 127;
            rect.y2 = 10;
            rtgui_dc_fill_rect(dc, &rect);
            rtgui_dc_draw_text(dc, key_str, &rect);
            rtgui_dc_end_drawing(dc, RT_TRUE);
        }
        else if (ekbd->type == RTGUI_KEYUP)
        {
            dc = rtgui_dc_begin_drawing(widget);
            if (dc == RT_NULL)
                return RT_FALSE;
            rect.x1 = 118;
            rect.y1 = 1;
            rect.x2 = 127;
            rect.y2 = 10;
            rtgui_dc_fill_rect(dc, &rect);
            //rtgui_dc_draw_text(dc, key_str, &rect);
            rtgui_dc_end_drawing(dc, RT_TRUE);
        }
    }
    else if (event->type == RTGUI_EVENT_COMMAND)
    {
        char str[16];
        struct rtgui_dc* dc;
        struct rtgui_rect rect;
        struct rtgui_event_command* ecmd;
        rt_uint8_t major,minor;
        dc = rtgui_dc_begin_drawing(widget);
        if (dc == RT_NULL)
            return RT_FALSE;

        ecmd = (struct rtgui_event_command*)event;
        switch (ecmd->command_id)
        {
            case ADC_UPDATE:
                rect.x1 = 1;
                rect.y1 = 1;
                rect.x2 = 117;
                rect.y2 = 10;
                rtgui_dc_fill_rect(dc, &rect);
                rt_sprintf(str, "ADC = %d mv", adc_value);
                rtgui_dc_draw_text(dc, str, &rect);
            break;
            case CPU_UPDATE:
                cpu_usage_get(&major, &minor);
                rect.x1 = 1;
                rect.y1 = 12;
                rect.x2 = 127;
                rect.y2 = 22;
                rtgui_dc_fill_rect(dc, &rect);
                rt_sprintf(str, "CPU : %d.%d%", major, minor);
                rtgui_dc_draw_text(dc, str, &rect);

                rect.y1 = 23;
                rect.y2 = 63;
                index++;
                if (index == 127)
                {
                    index = 1;
                    rtgui_dc_fill_rect(dc, &rect);
                }
                if (major>40)
                    rtgui_dc_draw_vline(dc, index, rect.y1, rect.y2);
                else
                    rtgui_dc_draw_vline(dc, index, rect.y2-major, rect.y2);
                break;
        }
        rtgui_dc_end_drawing(dc, RT_TRUE);
    }

    return rtgui_view_event_handler(widget, event);
}

static void info_entry(void* parameter)
{
    rt_mq_t mq;
    struct rtgui_view* view;
    struct rtgui_workbench* workbench;

    mq = rt_mq_create("qInfo", 256, 4, RT_IPC_FLAG_FIFO);
    rtgui_thread_register(rt_thread_self(), mq);

    workbench = rtgui_workbench_create("info", "workbench");
    if(workbench == RT_NULL)
        return;

    view = rtgui_view_create("view");
    RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(view)) = white;
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(view)) = black;
    rtgui_widget_set_event_handler(RTGUI_WIDGET(view), view_event_handler);

    rtgui_workbench_add_view(workbench, view);
    /* this view can be focused */
    RTGUI_WIDGET(view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
    /* set widget focus */
    rtgui_widget_focus(RTGUI_WIDGET(view));

    rtgui_view_show(view, RT_FALSE);

    rtgui_workbench_event_loop(workbench);

    rtgui_thread_deregister(rt_thread_self());
    rt_mq_delete(mq);
}

rt_thread_t info_tid;
void info_init()
{
    info_tid = rt_thread_create("info",
        info_entry, RT_NULL,
        2048, 25, 10);

    if (info_tid != RT_NULL) rt_thread_startup(info_tid);
}

void rtgui_startup()
{
    rtgui_rect_t rect;

    rtgui_system_server_init();

    /* register dock panel */
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 128;
    rect.y2 = 64;
    rtgui_panel_register("info", &rect);
    rtgui_panel_set_default_focused("info");

    /*init info workbench */
    info_init();
}

#endif
