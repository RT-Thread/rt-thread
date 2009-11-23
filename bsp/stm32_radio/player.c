#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>
#include <string.h>

#include "listview.h"

static rtgui_image_t *background = RT_NULL;

static struct rtgui_view* function_view;
static struct rtgui_view* home_view;
static struct rtgui_workbench* workbench;

void function_filelist(void* parameter)
{
	rtgui_rect_t rect;
	rtgui_view_t *view;
	extern rtgui_view_t* filelist_view_create(rtgui_workbench_t* workbench,
		const char* directory, const char* pattern, rtgui_rect_t* rect);

	rtgui_widget_get_rect(RTGUI_WIDGET(workbench), &rect);
	view = (rtgui_view_t*)filelist_view_create(workbench, "/", "*.*", &rect);
	if (view != RT_NULL)
	{
	    rtgui_view_show(view, RT_FALSE);
	}

	return;
}

void function_device(void* parameter)
{
	rtgui_view_t *view;
	extern rtgui_view_t* device_view_create(rtgui_workbench_t* workbench);
	
	view = device_view_create(workbench);
	if (view != RT_NULL)
	{
	    rtgui_view_show(view, RT_FALSE);
	}

	return;
}

void function_player(void* parameter)
{
    rtgui_view_show(home_view, RT_FALSE);
	return;
}

void function_action(void* parameter)
{
	rt_kprintf("item action!\n");
	return;
}

struct list_item function_list[] =
{
	{"选择电台", RT_NULL, function_action, RT_NULL},
	{"更新电台", RT_NULL, function_action, RT_NULL},
	{"播放文件", RT_NULL, function_filelist, RT_NULL},
	{"设备信息", RT_NULL, function_device, RT_NULL},
	{"返回播放器", RT_NULL, function_player, RT_NULL},
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
	else if (event->type == RTGUI_EVENT_KBD)
	{
		struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
		if (ekbd->type == RTGUI_KEYDOWN)
		{
			switch (ekbd->key)
			{
			case RTGUIK_RIGHT:
			case RTGUIK_LEFT:
				break;

			case RTGUIK_DOWN:
                rtgui_view_show(function_view, RT_FALSE);
				break;
			}
		}
		return RT_FALSE;
	}

	return rtgui_view_event_handler(widget, event);
}

rt_bool_t today_workbench_event_handler(rtgui_widget_t *widget, rtgui_event_t *event)
{
    if (event->type == RTGUI_EVENT_KBD)
    {
        struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
        if ((ekbd->type == RTGUI_KEYUP) && ekbd->key == RTGUIK_HOME)
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

static void player_entry(void* parameter)
{
	rt_mq_t mq;
	rtgui_rect_t rect;

	mq = rt_mq_create("qPlayer", 256, 4, RT_IPC_FLAG_FIFO);
	rtgui_thread_register(rt_thread_self(), mq);

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
	function_view = (struct rtgui_view*)list_view_create(function_list,
		sizeof(function_list)/sizeof(struct list_item),
		&rect);
	rtgui_workbench_add_view(workbench, function_view);

	rtgui_workbench_event_loop(workbench);

	rtgui_thread_deregister(rt_thread_self());
	rt_mq_delete(mq);
}

void player_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("player",
        player_entry, RT_NULL,
        2048, 25, 10);

    if (tid != RT_NULL) rt_thread_startup(tid);
}
