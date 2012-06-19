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
#include <rtgui/image.h>
#include <rtgui/font.h>
#include <rtgui/event.h>
#include <rtgui/rtgui_application.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>
#include <rtgui/rtgui_theme.h>

#ifdef _WIN32
#define RTGUI_MEM_TRACE
#endif

void rtgui_system_server_init(void)
{
	/* init image */
	rtgui_system_image_init();
	/* init font */
	rtgui_font_system_init();

	/* init rtgui server */
	rtgui_topwin_init();
	rtgui_server_init();

	/* init theme */
	rtgui_system_theme_init();
}

/************************************************************************/
/* RTGUI Timer                                                          */
/************************************************************************/
static void rtgui_time_out(void* parameter)
{
	rtgui_timer_t* timer;
	rtgui_event_timer_t event;
	timer = (rtgui_timer_t*)parameter;

	/*
	* Note: event_timer can not use RTGUI_EVENT_TIMER_INIT to init, for there is no
	* thread context
	*/
	event.parent.type = RTGUI_EVENT_TIMER;
	event.parent.sender = RT_NULL;

	event.timer = timer;

	rtgui_application_send(timer->tid, &(event.parent), sizeof(rtgui_event_timer_t));
}

rtgui_timer_t* rtgui_timer_create(rt_int32_t time, rt_int32_t flag, rtgui_timeout_func timeout, void* parameter)
{
	rtgui_timer_t* timer;

	timer = (rtgui_timer_t*) rtgui_malloc(sizeof(rtgui_timer_t));
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

void* rtgui_realloc(void* ptr, rt_size_t size)
{
	void* new_ptr;

#ifdef RTGUI_MEM_TRACE
	new_ptr = rtgui_malloc(size);
	if ((new_ptr != RT_NULL) && (ptr != RT_NULL))
	{
		rt_memcpy(new_ptr, ptr, size);
		rtgui_free(ptr);
	}
#else
	new_ptr = rt_realloc(ptr, size);
#endif

	return new_ptr;
}

void rtgui_free(void* ptr)
{
#ifdef RTGUI_MEM_TRACE
	if (ptr != RT_NULL)
		rti_free_hook(ptr);
#endif

	rt_free(ptr);
}

