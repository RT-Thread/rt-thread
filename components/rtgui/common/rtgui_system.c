/*
 * File      : rtgui_system.c
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

#include <rtgui/rtgui.h>
#include <rtgui/driver.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/widgets/window.h>

// #define RTGUI_EVENT_DEBUG

#ifdef __WIN32__
#define RTGUI_EVENT_DEBUG
#define RTGUI_MEM_TRACE
#endif

void rtgui_system_server_init()
{
	/* init image */
	rtgui_system_image_init();
	/* init font */
	rtgui_font_system_init();

	/* init rtgui server */
	rtgui_panel_init();
	rtgui_topwin_init();
	rtgui_server_init();

	/* init theme */
	rtgui_system_theme_init();
}

/************************************************************************/
/* RTGUI Thread Wrapper                                                 */
/************************************************************************/
#ifdef RTGUI_EVENT_DEBUG
const char *event_string[] =
{
	/* panel event */
	"PANEL_ATTACH",			/* attach to a panel	*/
	"PANEL_DETACH",			/* detach from a panel	*/
	"PANEL_SHOW",			/* show in a panel		*/
	"PANEL_HIDE",			/* hide from a panel	*/
	"PANEL_INFO",			/* panel information 	*/
	"PANEL_RESIZE",			/* resize panel 		*/
	"PANEL_FULLSCREEN",		/* to full screen 		*/
	"PANEL_NORMAL",			/* to normal screen 	*/

	/* window event */
	"WIN_CREATE",			/* create a window 	*/
	"WIN_DESTROY",			/* destroy a window 	*/
	"WIN_SHOW",				/* show a window 		*/
	"WIN_HIDE",				/* hide a window 		*/
	"WIN_ACTIVATE", 		/* activate a window 	*/
	"WIN_DEACTIVATE",		/* deactivate a window 	*/
	"WIN_CLOSE",			/* close a window 		*/
	"WIN_MOVE",				/* move a window 		*/
	"WIN_RESIZE", 			/* resize a window 		*/

	"SET_WM", 				/* set window manager	*/

	"UPDATE_BEGIN",			/* begin of update rect */
	"UPDATE_END",			/* end of update rect	*/
	"MONITOR_ADD",			/* add a monitor rect 	*/
	"MONITOR_REMOVE", 		/* remove a monitor rect*/
	"PAINT",				/* paint on screen 		*/
	"TIMER",				/* timer 				*/

	/* clip rect information */
	"CLIP_INFO",			/* clip rect info		*/

	/* mouse and keyboard event */
	"MOUSE_MOTION",			/* mouse motion */
	"MOUSE_BUTTON",			/* mouse button info 	*/
	"KBD",					/* keyboard info		*/

	/* user command event */
	"COMMAND",				/* user command 		*/

	/* request's status event */
	"STATUS",				/* request result 		*/
	"SCROLLED",           	/* scroll bar scrolled  */
	"RESIZE",				/* widget resize 		*/
};

#define DBG_MSG(x)	rt_kprintf x

static void rtgui_event_dump(rt_thread_t tid, rtgui_event_t* event)
{
	char* sender = "(unknown)";

	if (event->sender != RT_NULL) sender = event->sender->name;

	if (event->type == RTGUI_EVENT_TIMER)
	{
		/* don't dump timer event */
		return ;
	}

	rt_kprintf("%s -- %s --> %s ", sender, event_string[event->type], tid->name);
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		{
			struct rtgui_event_paint *paint = (struct rtgui_event_paint *)event;

			if(paint->wid != RT_NULL)
				rt_kprintf("win: %s", paint->wid->title);
		}
		break;

	case RTGUI_EVENT_KBD:
		{
			struct rtgui_event_kbd *ekbd = (struct rtgui_event_kbd*) event;
			if (ekbd->wid != RT_NULL)
				rt_kprintf("win: %s", ekbd->wid->title);
		}
		break;

	case RTGUI_EVENT_CLIP_INFO:
		{
			struct rtgui_event_clip_info *info = (struct rtgui_event_clip_info *)event;

			if(info->wid != RT_NULL)
				rt_kprintf("win: %s", info->wid->title);
#ifdef RTGUI_USING_SMALL_SIZE
			rt_kprintf(" clip no. %d", info->num_rect);
#else
			{
				rtgui_rect_t *rect;
				rt_uint32_t index;

				rect = (rtgui_rect_t*)(info + 1);
				for (index = 0; index < info->num_rect; index ++)
				{
					rt_kprintf(" (x1:%d, y1:%d, x2:%d, y2:%d)", rect->x1, rect->y1, rect->x2, rect->y2);
					rect ++;
				}
			}
#endif
		}
		break;

	case RTGUI_EVENT_WIN_CREATE:
		{
			struct rtgui_event_win_create *create = (struct rtgui_event_win_create*)event;

			rt_kprintf(" win: %s at (x1:%d, y1:%d, x2:%d, y2:%d)",
#ifdef RTGUI_USING_SMALL_SIZE
				create->wid->title,
				RTGUI_WIDGET(create->wid)->extent.x1,
				RTGUI_WIDGET(create->wid)->extent.y1,
				RTGUI_WIDGET(create->wid)->extent.x2,
				RTGUI_WIDGET(create->wid)->extent.y2);
#else
				create->title,
				create->extent.x1,
				create->extent.y1,
				create->extent.x2,
				create->extent.y2);
#endif
		}
		break;

	case RTGUI_EVENT_UPDATE_END:
		{
			struct rtgui_event_update_end* update_end = (struct rtgui_event_update_end*)event;
			rt_kprintf("(x:%d, y1:%d, x2:%d, y2:%d)", update_end->rect.x1,
				update_end->rect.y1,
				update_end->rect.x2,
				update_end->rect.y2);
		}
		break;

	case RTGUI_EVENT_WIN_ACTIVATE:
	case RTGUI_EVENT_WIN_DEACTIVATE:
	case RTGUI_EVENT_WIN_SHOW:
		{
			struct rtgui_event_win *win = (struct rtgui_event_win *)event;

			if(win->wid != RT_NULL)
				rt_kprintf("win: %s", win->wid->title);
		}
		break;

	case RTGUI_EVENT_WIN_MOVE:
		{
			struct rtgui_event_win_move *win = (struct rtgui_event_win_move *)event;

			if(win->wid != RT_NULL)
			{
				rt_kprintf("win: %s", win->wid->title);
				rt_kprintf(" to (x:%d, y:%d)", win->x, win->y);
			}
		}
		break;

	case RTGUI_EVENT_WIN_RESIZE:
		{
			struct rtgui_event_win_resize* win = (struct rtgui_event_win_resize *)event;

			if (win->wid != RT_NULL)
			{
				rt_kprintf("win: %s, rect(x1:%d, y1:%d, x2:%d, y2:%d)", win->wid->title,
					RTGUI_WIDGET(win->wid)->extent.x1,
					RTGUI_WIDGET(win->wid)->extent.y1,
					RTGUI_WIDGET(win->wid)->extent.x2,
					RTGUI_WIDGET(win->wid)->extent.y2);
			}
		}
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
	case RTGUI_EVENT_MOUSE_MOTION:
		{
			struct rtgui_event_mouse *mouse = (struct rtgui_event_mouse*)event;

			if (mouse->button & RTGUI_MOUSE_BUTTON_LEFT) rt_kprintf("left ");
			else rt_kprintf("right ");

			if (mouse->button & RTGUI_MOUSE_BUTTON_DOWN) rt_kprintf("down ");
			else rt_kprintf("up ");

			if (mouse->wid != RT_NULL)
				rt_kprintf("win: %s at (%d, %d)", mouse->wid->title,
				mouse->x, mouse->y);
			else
				rt_kprintf("(%d, %d)", mouse->x, mouse->y);
		}
		break;

	case RTGUI_EVENT_MONITOR_ADD:
		{
			struct rtgui_event_monitor *monitor = (struct rtgui_event_monitor*)event;
			if (monitor->panel != RT_NULL)
			{
#if 0
				rt_kprintf("panel: %s, the rect is:(%d, %d) - (%d, %d)", monitor->panel->name,
					monitor->rect.x1, monitor->rect.y1,
					monitor->rect.x2, monitor->rect.y2);
#endif
				rt_kprintf("the rect is:(%d, %d) - (%d, %d)",
					monitor->rect.x1, monitor->rect.y1,
					monitor->rect.x2, monitor->rect.y2);
			}
			else if (monitor->wid != RT_NULL)
			{
				rt_kprintf("win: %s, the rect is:(%d, %d) - (%d, %d)", monitor->wid->title,
					monitor->rect.x1, monitor->rect.y1,
					monitor->rect.x2, monitor->rect.y2);
			}
		}
		break;
	}

	rt_kprintf("\n");
}
#else
#define DBG_MSG(x)
#define rtgui_event_dump(tid, event)
#endif

rtgui_thread_t* rtgui_thread_register(rt_thread_t tid, rt_mq_t mq)
{
	rtgui_thread_t* thread = rtgui_malloc(sizeof(struct rtgui_thread));

	if (thread != RT_NULL)
	{
		DBG_MSG(("register a rtgui thread: %s, tid: 0x%p\n", tid->name, tid));

		/* set tid and mq */
		thread->tid			= tid;
		thread->mq			= mq;
		thread->widget		= RT_NULL;

		/* set user thread */
		tid->user_data = (rt_uint32_t)thread;
	}

	return thread;
}

void rtgui_thread_deregister(rt_thread_t tid)
{
	struct rtgui_thread* thread;

	/* find rtgui_thread */
	thread = (struct rtgui_thread*) (tid->user_data);

	if (thread != RT_NULL)
	{
		/* remove rtgui_thread */
		tid->user_data = 0;

		/* free rtgui_thread */
		rtgui_free(thread);
	}
}

/* get current gui thread */
rtgui_thread_t* rtgui_thread_self()
{
	struct rtgui_thread* thread;
	rt_thread_t self;

	/* get current thread */
	self = rt_thread_self();
	thread = (struct rtgui_thread*)(self->user_data);

	return thread;
}

extern rt_thread_t rt_thread_find(char* name);
rt_thread_t rtgui_thread_get_server()
{
	return rt_thread_find("rtgui");
}

void rtgui_thread_set_widget(struct rtgui_widget* widget)
{
	struct rtgui_thread* thread;

	/* get rtgui_thread */
	thread = (struct rtgui_thread*) (rt_thread_self()->user_data);

	if (thread != RT_NULL) thread->widget = widget;
}

struct rtgui_widget* rtgui_thread_get_widget()
{
	struct rtgui_thread* thread;

	/* get rtgui_thread */
	thread = (struct rtgui_thread*) (rt_thread_self()->user_data);

	return thread == RT_NULL? RT_NULL : thread->widget;
}

rt_err_t rtgui_thread_send(rt_thread_t tid, rtgui_event_t* event, rt_size_t event_size)
{
	rt_err_t result;
	struct rtgui_thread* thread;

	rtgui_event_dump(tid, event);
	/* if (event->type != RTGUI_EVENT_TIMER)
		rt_kprintf("event size: %d\n", event_size); */

	/* find rtgui_thread */
	thread = (struct rtgui_thread*) (tid->user_data);
	if (thread == RT_NULL) return -RT_ERROR;

	result = rt_mq_send(thread->mq, event, event_size);
	if (result != RT_EOK)
	{
		if (event->type != RTGUI_EVENT_TIMER)
			rt_kprintf("send event to %s failed\n", thread->tid->name);
	}

	return result;
}

rt_err_t rtgui_thread_send_urgent(rt_thread_t tid, rtgui_event_t* event, rt_size_t event_size)
{
	rt_err_t result;
	struct rtgui_thread* thread;

	rtgui_event_dump(tid, event);
	rt_kprintf("event size: %d\n", event_size);

	/* find rtgui_thread */
	thread = (struct rtgui_thread*) (tid->user_data);
	if (thread == RT_NULL) return -RT_ERROR;

	result = rt_mq_urgent(thread->mq, event, event_size);
	if (result != RT_EOK)
		rt_kprintf("send ergent event failed\n");

	return result;
}

rt_err_t rtgui_thread_send_sync(rt_thread_t tid, rtgui_event_t* event, rt_size_t event_size)
{
	rt_err_t r;
	struct rtgui_thread* thread;
	rt_int32_t ack_buffer, ack_status;
	struct rt_mailbox ack_mb;

	rtgui_event_dump(tid, event);
	rt_kprintf("event size: %d\n", event_size);

	/* init ack mailbox */
	r = rt_mb_init(&ack_mb, "ack", &ack_buffer, 1, 0);
	if ( r!= RT_EOK) goto __return;

	/* find rtgui_thread */
	thread = (struct rtgui_thread*) (tid->user_data);
	if (thread == RT_NULL){ r = RT_ERROR; goto __return; }

	event->ack = &ack_mb;
	r = rt_mq_send(thread->mq, event, event_size);
	if (r != RT_EOK) 
	{
		rt_kprintf("send sync event failed\n");
		goto __return;
	}

	r = rt_mb_recv(&ack_mb, (rt_uint32_t*)&ack_status, RT_WAITING_FOREVER);
	if ( r!= RT_EOK) goto __return;

	if (ack_status != RTGUI_STATUS_OK) r = -RT_ERROR;
	else r = RT_EOK;

	/* fini ack mailbox */
	rt_mb_detach(&ack_mb);

__return:
	return r;
}

rt_err_t rtgui_thread_ack(rtgui_event_t* event, rt_int32_t status)
{
	if (event != RT_NULL &&
		event->ack != RT_NULL)
	{
		rt_mb_send(event->ack, status);
	}

	return RT_EOK;
}

rt_err_t rtgui_thread_recv(rtgui_event_t* event, rt_size_t event_size)
{
	struct rtgui_thread* thread;
	rt_err_t r;

	/* find rtgui_thread */
	thread = (struct rtgui_thread*) (rt_thread_self()->user_data);
	if (thread == RT_NULL) return -RT_ERROR;

	r = rt_mq_recv(thread->mq, event, event_size, RT_WAITING_FOREVER);

	return r;
}

rt_err_t rtgui_thread_recv_filter(rt_uint32_t type, rtgui_event_t* event, rt_size_t event_size)
{
	struct rtgui_thread* thread;

	/* find rtgui_thread */
	thread = (struct rtgui_thread*) (rt_thread_self()->user_data);
	if (thread == RT_NULL) return -RT_ERROR;

	while (rt_mq_recv(thread->mq, event, event_size, RT_WAITING_FOREVER) == RT_EOK)
	{
		if (event->type == type)
		{
			return RT_EOK;
		}
		else
		{
			/* let widget to handle event */
			if (thread->widget != RT_NULL &&
				thread->widget->event_handler != RT_NULL)
			{
				thread->widget->event_handler(thread->widget, event);
			}
		}
	}

	return -RT_ERROR;
}

/************************************************************************/
/* RTGUI Timer                                                          */
/************************************************************************/
static void rtgui_time_out(void* parameter)
{
	rtgui_timer_t* timer;
	struct rtgui_event_timer event;
	timer = (rtgui_timer_t*)parameter;

	/*
	* Note: event_timer can not use RTGUI_EVENT_TIMER_INIT to init, for there is no
	* thread context
	*/
	event.parent.type = RTGUI_EVENT_TIMER;
	event.parent.sender = RT_NULL;

	event.timer = timer;

	rtgui_thread_send(timer->tid, &(event.parent), sizeof(struct rtgui_event_timer));
}

rtgui_timer_t* rtgui_timer_create(rt_int32_t time, rt_base_t flag, rtgui_timeout_func timeout, void* parameter)
{
	rtgui_timer_t* timer;

	timer = (rtgui_timer_t*) rtgui_malloc(sizeof(struct rtgui_timer));
	timer->tid = rt_thread_self();
	timer->timeout = timeout;
	timer->user_data = parameter;

	/* init rt-thread timer */
	rt_timer_init(&(timer->timer), "rtgui", rtgui_time_out, timer, time, (rt_uint8_t)flag);

	return timer;
}

void rtgui_timer_destory(rtgui_timer_t* timer)
{
	RT_ASSERT(timer != RT_NULL);

	/* stop timer firstly */
	rtgui_timer_stop(timer);

	/* detach rt-thread timer */
	rt_timer_detach(&(timer->timer));

	rtgui_free(timer);
}

void rtgui_timer_start(rtgui_timer_t* timer)
{
	RT_ASSERT(timer != RT_NULL);

	/* start rt-thread timer */
	rt_timer_start(&(timer->timer));
}

void rtgui_timer_stop (rtgui_timer_t* timer)
{
	RT_ASSERT(timer != RT_NULL);

	/* stop rt-thread timer */
	rt_timer_stop(&(timer->timer));
}

/************************************************************************/
/* RTGUI Memory Management                                              */
/************************************************************************/
#ifdef RTGUI_MEM_TRACE
struct rtgui_mem_info
{
	rt_uint32_t allocated_size;
	rt_uint32_t max_allocated;
};
struct rtgui_mem_info mem_info;

#define MEMTRACE_MAX		4096
#define MEMTRACE_HASH_SIZE	256

struct rti_memtrace_item
{
	void*		mb_ptr;		/* memory block pointer */
	rt_uint32_t mb_len;		/* memory block length */

	struct rti_memtrace_item* next;
};
struct rti_memtrace_item trace_list[MEMTRACE_MAX];
struct rti_memtrace_item *item_hash[MEMTRACE_HASH_SIZE];
struct rti_memtrace_item *item_free;

rt_bool_t rti_memtrace_inited = 0;
void rti_memtrace_init()
{
	struct rti_memtrace_item *item;
	rt_uint32_t index;

	rt_memset(trace_list, 0, sizeof(trace_list));
	rt_memset(item_hash, 0, sizeof(item_hash));

	item_free = &trace_list[0];
	item = &trace_list[0];

	for (index = 1; index < MEMTRACE_HASH_SIZE; index ++)
	{
		item->next = &trace_list[index];
		item = item->next;
	}

	item->next = RT_NULL;
}

void rti_malloc_hook(void* ptr, rt_uint32_t len)
{
	rt_uint32_t index;
	struct rti_memtrace_item* item;

	if (item_free == RT_NULL) return;

	mem_info.allocated_size += len;
	if (mem_info.max_allocated < mem_info.allocated_size)
		mem_info.max_allocated = mem_info.allocated_size;

	/* lock context */
	item = item_free;
	item_free = item->next;

	item->mb_ptr = ptr;
	item->mb_len = len;
	item->next   = RT_NULL;

	/* get hash item index */
	index = ((rt_uint32_t)ptr) % MEMTRACE_HASH_SIZE;
	if (item_hash[index] != RT_NULL)
	{
		/* add to list */
		item->next = item_hash[index];
		item_hash[index] = item;
	}
	else
	{
		/* set list header */
		item_hash[index] = item;
	}
	/* unlock context */
}

void rti_free_hook(void* ptr)
{
	rt_uint32_t index;
	struct rti_memtrace_item *item;

	/* get hash item index */
	index = ((rt_uint32_t)ptr) % MEMTRACE_HASH_SIZE;
	if (item_hash[index] != RT_NULL)
	{
		item = item_hash[index];
		if (item->mb_ptr == ptr)
		{
			/* delete item from list */
			item_hash[index] = item->next;
		}
		else
		{
			/* find ptr in list */
			while (item->next != RT_NULL && item->next->mb_ptr != ptr)
				item = item->next;

			/* delete item from list */
			if (item->next != RT_NULL)
			{
				struct rti_memtrace_item* i;

				i = item->next;
				item->next = item->next->next;

				item = i;
			}
			else
			{
				/* not found */
				return;
			}
		}

		/* reduce allocated size */
		mem_info.allocated_size -= item->mb_len;

		/* clear item */
		rt_memset(item, 0, sizeof(struct rti_memtrace_item));

		/* add item to the free list */
		item->next = item_free;
		item_free = item;
	}
}
#endif

void* rtgui_malloc(rt_size_t size)
{
	void* ptr;

	ptr = rt_malloc(size);
#ifdef RTGUI_MEM_TRACE
	if (rti_memtrace_inited == 0)
	{
		rti_memtrace_init();
		rti_memtrace_inited = 1;
	}

	if (ptr != RT_NULL)
		rti_malloc_hook(ptr, size);
#endif

	return ptr;
}

void rtgui_free(void* ptr)
{
#ifdef RTGUI_MEM_TRACE
	if (ptr != RT_NULL)
		rti_free_hook(ptr);
#endif

	rt_free(ptr);
}

