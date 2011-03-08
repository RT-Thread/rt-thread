#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>

#include "adc.h"
#include <rtthread.h>

extern rt_uint16_t adc_value;

static rt_bool_t view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	if(event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		struct rtgui_rect rect;

		dc = rtgui_dc_begin_drawing(widget);
		if(dc == RT_NULL) 
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
        rect.x1 += 1;
        rect.y1 += 1;        
		rtgui_dc_draw_text(dc, "FM3 Easy Kit Demo", &rect);
        rect.y1 += 10;
        rtgui_dc_draw_text(dc, "[rt-thread/RTGUI]", &rect);
        
		rtgui_dc_end_drawing(dc);

		return RT_FALSE;
	}
    else if(event->type == RTGUI_EVENT_KBD)
    {
        struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
        if(ekbd->type == RTGUI_KEYDOWN)
        {
            char key_str[16];
            struct rtgui_dc* dc;
            struct rtgui_rect rect;

            switch(ekbd->key)
            {
                case RTGUIK_LEFT:
                rt_sprintf(key_str, "KEY = %s", "LEFT");
                break;
                case RTGUIK_RIGHT:
                rt_sprintf(key_str, "KEY = %s", "RIGHT");
                break;
                case RTGUIK_DOWN:
                rt_sprintf(key_str, "KEY = %s", "DOWN");
                break;
                case RTGUIK_UP:
                rt_sprintf(key_str, "KEY = %s", "UP");
                break;                
                default:
                rt_sprintf(key_str, "KEY = %s", "UNKNOWN");
                break;
            }
            dc = rtgui_dc_begin_drawing(widget);
            if(dc == RT_NULL) 
                return RT_FALSE;
            rect.x1 = 10;
            rect.y1 = 30;  
            rect.x2 = 120;
            rect.y2 = 40;       
            rtgui_dc_fill_rect(dc, &rect);
            rtgui_dc_draw_text(dc, key_str, &rect);
            rtgui_dc_end_drawing(dc);
        }
    }
    else if(event->type == RTGUI_EVENT_COMMAND)
    {
        char adc_str[10];
        struct rtgui_dc* dc;
        struct rtgui_rect rect;
        dc = rtgui_dc_begin_drawing(widget);
        if(dc == RT_NULL) 
            return RT_FALSE;
            
        struct rtgui_event_command* ecmd = (struct rtgui_event_command*)event;
        switch(ecmd->command_id)
        {   
            case ADC_UPDATE:
            rect.x1 = 10;
            rect.y1 = 40;  
            rect.x2 = 120;
            rect.y2 = 50;       
            rtgui_dc_fill_rect(dc, &rect);     
			rt_sprintf(adc_str, "ADC = %d mv", adc_value);
			rtgui_dc_draw_text(dc, adc_str, &rect);	
            rtgui_dc_end_drawing(dc);
        }
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
        2048, 26, 10);

    if (info_tid != RT_NULL) rt_thread_startup(info_tid);
}

void rtgui_startup()
{
    rtgui_rect_t rect;
    
	/* GUI系统初始化 */
    rtgui_system_server_init();
        
    /* register dock panel */
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 128;
    rect.y2 = 64;
    rtgui_panel_register("info", &rect);
    rtgui_panel_set_default_focused("info");
    
	/* 启动info workbench */
	info_init();
}

