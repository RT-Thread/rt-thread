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

struct rtgui_dc;
struct rtgui_event;
struct rtgui_widget;

#ifdef RTGUI_USING_SMALL_SIZE
#define RTGUI_EVENT_BUFFER_SIZE	64
#else
#define RTGUI_EVENT_BUFFER_SIZE	256
#endif

struct rtgui_thread
{
	/* the thread id */
	rt_thread_t tid;

	/* the message queue of thread */
	rt_mq_t mq;

	/* the owner of thread */
	struct rtgui_widget* widget;
	/* event buffer */
	rt_uint8_t event_buffer[RTGUI_EVENT_BUFFER_SIZE];

	/* on idle event handler */
	void (*on_idle)(struct rtgui_widget* widget, struct rtgui_event *event);
};
typedef struct rtgui_thread rtgui_thread_t;
struct rtgui_timer;
typedef void (*rtgui_timeout_func)(struct rtgui_timer* timer, void* parameter);
typedef void (*rtgui_idle_func)(struct rtgui_widget* widget, struct rtgui_event *event);

struct rtgui_timer
{
	/* context thread id */
	rt_thread_t tid;
	/* rt timer */
	struct rt_timer timer;

	/* timeout function and user data */
	rtgui_timeout_func timeout;
	void* user_data;
};
typedef struct rtgui_timer rtgui_timer_t;

rtgui_timer_t* rtgui_timer_create(rt_int32_t time, rt_base_t flag, rtgui_timeout_func timeout, void* parameter);
void rtgui_timer_destory(rtgui_timer_t* timer);

void rtgui_timer_start(rtgui_timer_t* timer);
void rtgui_timer_stop (rtgui_timer_t* timer);

rtgui_thread_t* rtgui_thread_register(rt_thread_t tid, rt_mq_t mq);
void rtgui_thread_deregister(rt_thread_t tid);
void rtgui_thread_set_onidle(rtgui_idle_func onidle);
rtgui_idle_func rtgui_thread_get_onidle(void);
rtgui_thread_t* rtgui_thread_self(void);

rt_thread_t rtgui_thread_get_server(void);

void rtgui_thread_set_widget(struct rtgui_widget* widget);
struct rtgui_widget* rtgui_thread_get_widget(void);

rt_err_t rtgui_thread_send(rt_thread_t tid, struct rtgui_event* event, rt_size_t event_size);
rt_err_t rtgui_thread_send_urgent(rt_thread_t tid, struct rtgui_event* event, rt_size_t event_size);
rt_err_t rtgui_thread_send_sync(rt_thread_t tid, struct rtgui_event* event, rt_size_t event_size);
rt_err_t rtgui_thread_recv(struct rtgui_event* event, rt_size_t event_size);
rt_err_t rtgui_thread_recv_nosuspend(struct rtgui_event* event, rt_size_t event_size);
rt_err_t rtgui_thread_recv_filter(rt_uint32_t type, struct rtgui_event* event, rt_size_t event_size);
rt_err_t rtgui_thread_ack(struct rtgui_event* event, rt_int32_t status);

/* rtgui system initialization function */
void rtgui_system_server_init(void);

void* rtgui_malloc(rt_size_t size);
void rtgui_free(void* ptr);
void* rtgui_realloc(void* ptr, rt_size_t size);

#define rtgui_enter_critical	rt_enter_critical
#define rtgui_exit_critical		rt_exit_critical

#endif

