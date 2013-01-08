/*
 * File      : tetris_ui.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-08-14     Yi.Qiu      first version
 */
 
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/list_view.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/workbench.h>
#include <rtgui/dc.h>
#include "tetris.h"

struct app_info
{
	rtgui_workbench_t* workbench;
	rtgui_view_t* game_view;
	rtgui_list_view_t* function_view;
	
	rt_tetris_t * tetris;
	rt_tetris_view_t* tetris_view;
	rtgui_timer_t* _timer;
};
typedef struct app_info app_info;
static app_info g_app_info;

static void _game_over(void)
{
	rtgui_timer_destory(g_app_info._timer);
	rt_tetris_destory(g_app_info.tetris);
	rt_tetris_view_destroy(g_app_info.tetris_view);	
	rt_kprintf("GAME OVER\n");
	
	rtgui_view_show(g_app_info.function_view, RT_FALSE);
}

static rt_bool_t game_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		rtgui_rect_t rect;

		/* draw child */
		rtgui_view_event_handler(widget, event);

		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) return -RT_ERROR;
		rect.x1 = 96;
		rect.y1 = 0;
		rect.x2 = 128;
		rect.y2 = 16;
		rtgui_dc_draw_text(dc, "next", &rect);
		rect.y1 += 30;
		rect.y2 = rect.y1 + 16;
		rtgui_dc_draw_text(dc, "level", &rect);
		rect.y1 += 22;
		rect.y2 = rect.y1 + 16;
		rtgui_dc_draw_text(dc, "lines", &rect);
		rect.y1 += 22;
		rect.y2 = rect.y1 + 16;
		rtgui_dc_draw_text(dc, "score", &rect);
		rtgui_dc_end_drawing(dc);

		/* start tetris game, removed later */
	   	rt_tetris_start(g_app_info.tetris);
		return RT_FALSE;
	}
	else if ((event->type == RTGUI_EVENT_KBD))
	{
		struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
		
		if (ekbd->type == RTGUI_KEYDOWN)
		{
			if (ekbd->key == RTGUIK_RIGHT)
			{
				rt_tetris_right(g_app_info.tetris);	
			}
			else if (ekbd->key == RTGUIK_LEFT)
			{
				rt_tetris_left(g_app_info.tetris);	
			}
			else if (ekbd->key == RTGUIK_UP)
			{
				rt_tetris_rotate(g_app_info.tetris, RT_EOK);				
			}
			else if (ekbd->key == RTGUIK_DOWN)
			{
				if( rt_tetris_drop(g_app_info.tetris) == -RT_ETIMEOUT
					&& rt_tetris_status(g_app_info.tetris) != RT_FALSE)
				{
					_game_over();
				}
			}
		}
	}

	return rtgui_view_event_handler(widget, event);
}

static void _timer_timeout(rtgui_timer_t* timer, void* parameter)
{
	if( rt_tetris_down(g_app_info.tetris) == -RT_ETIMEOUT)
	{
		_game_over();
	}		
}

static rt_bool_t workbench_event_handler(rtgui_widget_t *widget, rtgui_event_t *event)
{
	if (event->type == RTGUI_EVENT_KBD)
	{
		struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
		if (((ekbd->type == RTGUI_KEYUP) && ekbd->key == RTGUIK_HOME)
				&& !RTGUI_WORKBENCH_IS_MODAL_MODE(g_app_info.workbench))
		{
			/* active home view */
			if (g_app_info.workbench->current_view != g_app_info.game_view)
			{
				rtgui_view_show(g_app_info.game_view, RT_FALSE);
				return RT_TRUE;
			}
		}
	}

	return rtgui_workbench_event_handler(widget, event);
}

static void listitem_action_return(void)
{
	rtgui_view_destroy(g_app_info.game_view);
	rtgui_list_view_destroy(g_app_info.function_view);
	rtgui_workbench_close(g_app_info.workbench);	
}	

static void listitem_action_start(void)
{
	/* create tetris modal instance */
	g_app_info.tetris = rt_tetris_create(16, 17);

	/* create tetris view instance */
	g_app_info.tetris_view = rt_tetris_view_create(RTGUI_WIDGET(g_app_info.game_view));	

	/* register tetris view to tetris modal */
	rt_tetris_add_view(g_app_info.tetris, g_app_info.tetris_view);

	/* create timer */
	g_app_info._timer = rtgui_timer_create(40, RT_TIMER_FLAG_PERIODIC, _timer_timeout, RT_NULL);

	/* this view can be focused */
	RTGUI_WIDGET(g_app_info.game_view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	
	/* set widget focus */
	rtgui_widget_focus(RTGUI_WIDGET(g_app_info.game_view));
	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(g_app_info.game_view)) = RTGUI_RGB(0xff, 0xff, 0xff);	
	
	rtgui_view_show(g_app_info.game_view, RT_FALSE);
	rtgui_timer_start(g_app_info._timer);
}

static void listitem_action_continue(void)
{

}	

static void listitem_action_adjust(void)
{

}	

static void listitem_action_description(void)
{

}

static const struct rtgui_list_item function_list[] =
{
	{"新游戏", RT_NULL, listitem_action_start, RT_NULL},
	{"继续", RT_NULL, listitem_action_continue, RT_NULL},
	{"等级", RT_NULL, listitem_action_adjust, RT_NULL},
	{"游戏说明", RT_NULL, listitem_action_description, RT_NULL},
	{"退出游戏", RT_NULL, listitem_action_return, RT_NULL},
};

void main(void)
{
	rt_mq_t mq;
	rtgui_rect_t rect;

	mq = rt_mq_create("tetris_ui", 256, 4, RT_IPC_FLAG_FIFO);
	rtgui_thread_register(rt_thread_self(), mq);

	g_app_info.workbench = rtgui_workbench_create("main", "tetris");
	if (g_app_info.workbench == RT_NULL) 
	{
		rt_kprintf("can't find panel 'main'\n");
		rt_mq_delete(mq);
	
		return;
	}
	rtgui_widget_set_event_handler(RTGUI_WIDGET(g_app_info.workbench), workbench_event_handler);

	/* add function view */
	rtgui_widget_get_rect(RTGUI_WIDGET(g_app_info.workbench), &rect);

	g_app_info.function_view = rtgui_list_view_create(function_list,
	                                       sizeof(function_list) / sizeof(struct rtgui_list_item),
	                                       &rect,
	                                       RTGUI_LIST_VIEW_LIST);
	
	rtgui_workbench_add_view(g_app_info.workbench, RTGUI_VIEW(g_app_info.function_view));

	/* add home view */
	g_app_info.game_view = rtgui_view_create("game");
	
	rtgui_widget_set_event_handler(RTGUI_WIDGET(g_app_info.game_view), game_view_event_handler);
	rtgui_workbench_add_view(g_app_info.workbench, g_app_info.game_view);

	rtgui_view_show(RTGUI_VIEW(g_app_info.function_view), RT_FALSE);

	rtgui_workbench_event_loop(g_app_info.workbench);
	rtgui_workbench_destroy(g_app_info.workbench);

	rtgui_thread_deregister(rt_thread_self());
	rt_mq_delete(mq);
}

