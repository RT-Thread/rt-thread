#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/list_view.h>
#include <rtgui/widgets/workbench.h>
#include <rtgui/widgets/filelist_view.h>
#include <string.h>

#include "picture.h"

static rtgui_image_t *background = RT_NULL;
rtgui_image_t *selected_image = RT_NULL;

static struct rtgui_view* function_view;
static struct rtgui_view* home_view;
static struct rtgui_workbench* workbench;

const char *introduction_list[] = 
{
	"/rtt/01.hdc", 
	"/rtt/02.hdc", 
	"/rtt/03.hdc", 
	"/rtt/04.hdc", 
	"/rtt/05.hdc", 
	"/rtt/06.hdc", 
	"/rtt/07.hdc", 
	"/rtt/08.hdc", 
};

void function_introduction(void* parameter)
{
	rtgui_view_t *view;

	view = picture_view_create_view_list(workbench, introduction_list, 
		sizeof(introduction_list)/sizeof(char*));
	if (view != RT_NULL)
	{
	    rtgui_view_show(view, RT_FALSE);
	}

	return;
}

void function_filelist(void* parameter)
{
	rtgui_rect_t rect;
	rtgui_view_t *view;

	rtgui_widget_get_rect(RTGUI_WIDGET(workbench), &rect);
	view = (rtgui_view_t*)rtgui_filelist_view_create(workbench, "/", "*.*", &rect);
	if (view != RT_NULL)
	{
	    rtgui_view_show(view, RT_FALSE);
	}

	return;
}

void function_osc(void* parameter)
{
	rtgui_view_t *view;
	extern rtgui_view_t *osc_view_create(rtgui_workbench_t *workbench);

	view = osc_view_create(workbench);
	if (view != RT_NULL)
	{
	    rtgui_view_show(view, RT_FALSE);
	}

	return;
}

void function_device(void* parameter)
{
	rtgui_view_t *view;
	extern rtgui_view_t *device_view_create(rtgui_workbench_t *workbench);

	view = device_view_create(workbench);
	if (view != RT_NULL)
	{
	    rtgui_view_show(view, RT_FALSE);
	}

	return;
}

void function_action(void* parameter)
{
	rt_kprintf("item action!\n");
	return;
}

struct rtgui_list_item function_list[] =
{
	{"RT-Thread介绍", RT_NULL, function_introduction, RT_NULL},
	{"文件浏览", RT_NULL, function_filelist, RT_NULL},
	{"波形演示", RT_NULL, function_osc, RT_NULL},
	{"设备信息", RT_NULL, function_device, RT_NULL},
};

static rt_bool_t home_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		struct rtgui_rect rect;

		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) return RT_FALSE;
		rtgui_widget_get_rect(widget, &rect);

		/* draw background */
		background = rtgui_image_create_from_file("hdc", 
			"/resource/bg.hdc", RT_FALSE);
		if (background != RT_NULL)
		{
			rtgui_image_blit(background, dc, &rect);
			rtgui_image_destroy(background);
			
			background = RT_NULL;
		}
		else
		{
			rtgui_dc_fill_rect(dc, &rect);
		}
		rtgui_dc_end_drawing(dc);

		return RT_FALSE;
	}
	else if (event->type == RTGUI_EVENT_MOUSE_BUTTON)
	{
		struct rtgui_event_mouse* emouse = (struct rtgui_event_mouse*)event;
        	if (emouse->button == RTGUI_MOUSE_BUTTON_UP | RTGUI_MOUSE_BUTTON_LEFT)
        	{
			rtgui_view_show(function_view, RT_FALSE);
		}
		return RT_FALSE;
	}

	return rtgui_view_event_handler(widget, event);
}

rt_bool_t today_workbench_event_handler(rtgui_widget_t *widget, rtgui_event_t *event)
{			
    if (event->type == RTGUI_EVENT_MOUSE_BUTTON)
    {
        struct rtgui_event_mouse* emouse = (struct rtgui_event_mouse*)event;
        //if (emouse->button == RTGUI_MOUSE_BUTTON_UP | RTGUI_MOUSE_BUTTON_LEFT)
		if(0)
		{
            /* active home view */
            if (workbench->current_view != home_view)
            {
                rtgui_view_show(home_view, RT_FALSE);
                return RT_FALSE;
            }
        }
    }

    return rtgui_workbench_event_handler(widget, event);
}

static void today_entry(void* parameter)
{
	rt_mq_t mq;
	rtgui_rect_t rect;

	mq = rt_mq_create("qToday", 256, 4, RT_IPC_FLAG_FIFO);
	rtgui_thread_register(rt_thread_self(), mq);

	selected_image = rtgui_image_create_from_file("hdc",
		"/resource/select.hdc", RT_FALSE);

	workbench = rtgui_workbench_create("main", "workbench");
	if (workbench == RT_NULL) return;
	rtgui_widget_set_event_handler(RTGUI_WIDGET(workbench), today_workbench_event_handler);

    /* add home view */
	home_view = rtgui_view_create("Home");
	rtgui_widget_set_event_handler(RTGUI_WIDGET(home_view), home_view_event_handler);

	rtgui_workbench_add_view(workbench, home_view);
	/* this view can be focused */
	RTGUI_WIDGET(home_view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	/* set widget focus */
	rtgui_widget_focus(RTGUI_WIDGET(home_view));

	rtgui_view_show(home_view, RT_FALSE);

    /* add function view */
	rtgui_widget_get_rect(RTGUI_WIDGET(workbench), &rect);
	function_view = (struct rtgui_view*)rtgui_list_view_create(function_list,
		sizeof(function_list)/sizeof(struct rtgui_list_item), &rect, RTGUI_LIST_VIEW_LIST);
	rtgui_workbench_add_view(workbench, function_view);

	rtgui_workbench_event_loop(workbench);

	rtgui_thread_deregister(rt_thread_self());
	rt_mq_delete(mq);
}

void today_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("today",
        today_entry, RT_NULL,
        2048, 25, 10);

    if (tid != RT_NULL) rt_thread_startup(tid);
}
