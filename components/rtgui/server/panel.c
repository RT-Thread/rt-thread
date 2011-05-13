/*
 * File      : panel.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 */

#include "panel.h"
#include "mouse.h"

#include <rtgui/rtgui_system.h>

/* the global parameter */
struct rtgui_list_node _rtgui_panel_list = {RT_NULL};

void rtgui_panel_register(char* name, rtgui_rect_t* extent)
{
	register rt_base_t temp;
	struct rtgui_panel* panel;

	panel = rtgui_panel_find(name);
	if (panel != RT_NULL )
	{
		/* there are already a same named panel exist. */
		return;
	}

	panel = rtgui_malloc(sizeof(struct rtgui_panel));
	if (panel == RT_NULL)
	{
		/* can't alloc memory */
		return;
	}

	/* copy name */
	for (temp = 0; temp < RTGUI_NAME_MAX; temp ++)
	{
		panel->name[temp] = name[temp];
	}

	/* copy extent */
	panel->extent = *extent;

	panel->wm_thread = RT_NULL;
	panel->is_focusable = RT_TRUE;

	/* init list */
	rtgui_list_init(&(panel->sibling));
	rtgui_list_init(&(panel->thread_list));

	/* add panel to panel list */
	rtgui_list_insert(&_rtgui_panel_list, &(panel->sibling));
}

void rtgui_panel_deregister(char* name)
{
	struct rtgui_panel* panel;

	panel = rtgui_panel_find(name);
	if (panel != RT_NULL)
	{
		rtgui_list_remove(&_rtgui_panel_list, &(panel->sibling));

		/* free pane node */
		rtgui_free(panel);
	}
}

/* set default focused panel, please use it after registered panel */
void rtgui_panel_set_default_focused(char* name)
{
	extern struct rtgui_panel* rtgui_server_focus_panel;
	struct rtgui_panel* panel;
	
	panel = rtgui_panel_find(name);
	if (panel != RT_NULL)
	{
		rtgui_server_focus_panel = panel;
	}
}

void rtgui_panel_set_nofocused(char* name)
{
	extern struct rtgui_panel* rtgui_server_focus_panel;
	struct rtgui_panel* panel;
	
	panel = rtgui_panel_find(name);
	if (panel != RT_NULL)
	{
		panel->is_focusable = RT_FALSE;
	}
}

struct rtgui_panel* rtgui_panel_find(char* name)
{
	struct rtgui_list_node* node;
	struct rtgui_panel* panel;

	rtgui_list_foreach(node, &_rtgui_panel_list)
	{
		panel = rtgui_list_entry(node, struct rtgui_panel, sibling);

		if (rt_strncmp(panel->name, name, RTGUI_NAME_MAX) == 0)
		{
			return panel;
		}
	}

	return RT_NULL;
}

struct rtgui_panel* rtgui_panel_thread_add(char* name, rt_thread_t tid)
{
	struct rtgui_panel* panel;

	panel = rtgui_panel_find(name);
	if (panel != RT_NULL )
	{
		struct rtgui_panel_thread* thread;

		/* allocate panel thread node */
		thread = rtgui_malloc(sizeof(struct rtgui_panel_thread));
		if (thread == RT_NULL)
		{
			return RT_NULL;
		}

		/* construct panel thread node */
		thread->tid = tid;

		/* init list */
		rtgui_list_init(&(thread->list));
		rtgui_list_init(&(thread->monitor_list));

		/* append thread to the list */
		rtgui_list_append(&(panel->thread_list), &(thread->list));
	}

	return panel;
}

void rtgui_panel_thread_remove(rtgui_panel_t* panel, rt_thread_t tid)
{
	if (panel != RT_NULL )
	{
		struct rtgui_list_node* node;
		struct rtgui_panel_thread* thread;

		rtgui_list_foreach(node, &(panel->thread_list))
		{
			thread = rtgui_list_entry(node, struct rtgui_panel_thread, list);
			if (thread->tid == tid)
			{
				/* remove node from list */
				rtgui_list_remove(&(panel->thread_list), &(thread->list));

				/* free the panel thread node */
				rtgui_free(thread);
				return;
			}
		}
	}
}

rt_thread_t rtgui_panel_get_active_thread(rtgui_panel_t* panel)
{
	if (panel != RT_NULL)
	{
		if (panel->thread_list.next != RT_NULL)
		{
			struct rtgui_panel_thread* thread;
			thread = rtgui_list_entry(panel->thread_list.next, struct rtgui_panel_thread, list);

			return thread->tid;
		}
	}

	return RT_NULL;
}

void rtgui_panel_set_active_thread(rtgui_panel_t* panel, rt_thread_t tid)
{
	/* get old active thread */
	rt_thread_t prev_actived = rtgui_panel_get_active_thread(panel);
	if (prev_actived != tid)
	{
		/* de-active old active workbench */
		struct rtgui_event_panel_hide ehide;
		RTGUI_EVENT_PANEL_HIDE_INIT(&ehide);

		ehide.panel = panel;
		ehide.workbench = RT_NULL;
		rtgui_thread_send_urgent(prev_actived, &(ehide.parent), sizeof (ehide));
	}

	if (panel != RT_NULL )
	{
		struct rtgui_list_node* node;
		struct rtgui_panel_thread* thread;

		rtgui_list_foreach(node, &(panel->thread_list))
		{
			thread = rtgui_list_entry(node, struct rtgui_panel_thread, list);
			if (thread->tid == tid)
			{
				/* remove node from list */
				rtgui_list_remove(&(panel->thread_list), &(thread->list));

				/* insert node to the header */
				rtgui_list_insert(&(panel->thread_list), &(thread->list));
				return;
			}
		}
	}
}

/* deactivate current activated thread -- move it to the end of list */
void rtgui_panel_deactive_thread(rtgui_panel_t* panel)
{
	RT_ASSERT(panel == RT_NULL);

	if (panel->thread_list.next != RT_NULL)
	{
		struct rtgui_panel_thread* thread;
		thread = rtgui_list_entry(panel->thread_list.next, struct rtgui_panel_thread, list);

		/* remove it */
		panel->thread_list.next = thread->list.next;

		/* append to the tail of thread list */
		rtgui_list_append(&(panel->thread_list), &(thread->list));
	}
}

/**
 * get the panel which contains a point(x, y)
 */
rtgui_panel_t* rtgui_panel_get_contain(int x, int y)
{
	struct rtgui_list_node* node;
	struct rtgui_panel* panel;

	rtgui_list_foreach(node, &(_rtgui_panel_list))
	{
		panel = rtgui_list_entry(node, struct rtgui_panel, sibling);
		if (rtgui_rect_contains_point(&(panel->extent), x, y) == RT_EOK)
		{
			return panel;
		}
	}

	return RT_NULL;
}

/**
 * append a rect to panel mouse monitor rect list
 */
void rtgui_panel_append_monitor_rect(rtgui_panel_t* panel, rt_thread_t tid, rtgui_rect_t* rect)
{
	if (panel != RT_NULL )
	{
		struct rtgui_list_node* node;
		struct rtgui_panel_thread* thread;

		rtgui_list_foreach(node, &(panel->thread_list))
		{
			thread = rtgui_list_entry(node, struct rtgui_panel_thread, list);
			if (thread->tid == tid)
			{
				/* add the monitor rect to list */
				rtgui_mouse_monitor_append(&(thread->monitor_list), rect);
				return;
			}
		}
	}
}

/**
 * remove a rect from panel mouse monitor rect list
 */
void rtgui_panel_remove_monitor_rect(rtgui_panel_t* panel, rt_thread_t tid, rtgui_rect_t* rect)
{
	if (panel != RT_NULL )
	{
		struct rtgui_list_node* node;
		struct rtgui_panel_thread* thread;

		rtgui_list_foreach(node, &(panel->thread_list))
		{
			thread = rtgui_list_entry(node, struct rtgui_panel_thread, list);
			if (thread->tid == tid)
			{
				/* remove the monitor rect from list */
				rtgui_mouse_monitor_remove(&(thread->monitor_list), rect);
				return;
			}
		}
	}
}

void rtgui_panel_set_wm(rtgui_panel_t* panel, rt_thread_t wm)
{
	RT_ASSERT(wm != RT_NULL);
	RT_ASSERT(panel != RT_NULL);

	panel->wm_thread = wm;
}

