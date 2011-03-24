/*
 * File      : rtgui_system.h
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
#ifndef __RTGUI_SYSTEM_H__
#define __RTGUI_SYSTEM_H__

#include <rtthread.h>
#include <rtgui/rtgui.h>

#ifdef RTGUI_USING_SMALL_SIZE
#define RTGUI_EVENT_BUFFER_SIZE	64
#else
#define RTGUI_EVENT_BUFFER_SIZE	256
#endif

struct rtgui_thread
{
	/* the thread id */
	struct rt_thread* tid;

	/* the message queue of thread */
	struct rt_messagequeue* mq;

	/* the owner of thread */
	PVOID widget;
	/* event buffer */
	rt_uint8_t event_buffer[RTGUI_EVENT_BUFFER_SIZE];

	/* on idle event handler */
	void (*on_idle)(PVOID wdt, rtgui_event_t *event);
};
typedef struct rtgui_thread rtgui_thread_t;

typedef struct rtgui_timer rtgui_timer_t;
typedef void (*rtgui_timeout_func)(rtgui_timer_t* timer, void* parameter);
typedef void (*rtgui_idle_func)(PVOID wdt, rtgui_event_t *event);

struct rtgui_timer
{
	/* context thread id */
	struct rt_thread* tid;
	/* rt timer */
	struct rt_timer timer;

	/* timeout function and user data */
	rtgui_timeout_func timeout;
	void* user_data;
};


rtgui_timer_t* rtgui_timer_create(rt_int32_t time, rt_int32_t flag, rtgui_timeout_func timeout, void* parameter);
void rtgui_timer_destory(rtgui_timer_t* timer);

void rtgui_timer_start(rtgui_timer_t* timer);
void rtgui_timer_stop(rtgui_timer_t* timer);

void rtgui_thread_register(struct rt_thread* tid, struct rt_messagequeue* mq);
void rtgui_thread_deregister(struct rt_thread* tid);
rtgui_thread_t* rtgui_thread_self(void);
void rtgui_thread_set_onidle(rtgui_idle_func onidle);
rtgui_idle_func rtgui_thread_get_onidle(void);

struct rt_thread* rtgui_thread_get_server(void);

void rtgui_thread_set_widget(PVOID widget);
PVOID rtgui_thread_get_widget(void);

rt_err_t rtgui_thread_send(struct rt_thread* tid, rtgui_event_t* event, rt_size_t event_size);
rt_err_t rtgui_thread_send_urgent(struct rt_thread* tid, rtgui_event_t* event, rt_size_t event_size);
rt_err_t rtgui_thread_send_sync(struct rt_thread* tid, rtgui_event_t* event, rt_size_t event_size);
rt_err_t rtgui_thread_recv(rtgui_event_t* event, rt_size_t event_size);
rt_err_t rtgui_thread_recv_nosuspend(rtgui_event_t* event, rt_size_t event_size);
rt_err_t rtgui_thread_recv_filter(rt_uint32_t type, rtgui_event_t* event, rt_size_t event_size);
rt_err_t rtgui_thread_ack(rtgui_event_t* event, rt_err_t errcode);

/* rtgui system initialization function */
void rtgui_system_server_init(void);

void* rtgui_malloc(rt_size_t size);
void rtgui_free(void* ptr);
void* rtgui_realloc(void* ptr, rt_size_t size);

#endif

