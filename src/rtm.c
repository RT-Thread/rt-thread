/*
 * File      : rtm.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2010-04-12      yi.qiu	first version
 */

#include <rtthread.h> 

/* some buildin kernel symbol */

#ifdef RT_USING_MODULE
#include <rtm.h>

/*
 * thread  interface symbol 
 */
RTM_EXPORT(rt_thread_init)
RTM_EXPORT(rt_thread_detach)
RTM_EXPORT(rt_thread_create)
RTM_EXPORT(rt_thread_self)
RTM_EXPORT(rt_thread_find)
RTM_EXPORT(rt_thread_startup)
RTM_EXPORT(rt_thread_delete)
RTM_EXPORT(rt_thread_yield)
RTM_EXPORT(rt_thread_delay)
RTM_EXPORT(rt_thread_control)
RTM_EXPORT(rt_thread_suspend)
RTM_EXPORT(rt_thread_resume)
RTM_EXPORT(rt_thread_timeout)

#ifdef RT_USING_SEMAPHORE
/*
 * semaphore interface symbol
 */
RTM_EXPORT(rt_sem_init)
RTM_EXPORT(rt_sem_detach)
RTM_EXPORT(rt_sem_create)
RTM_EXPORT(rt_sem_delete)
RTM_EXPORT(rt_sem_take)
RTM_EXPORT(rt_sem_trytake)
RTM_EXPORT(rt_sem_release)
RTM_EXPORT(rt_sem_control)
#endif

#ifdef RT_USING_MUTEX
/*
 * mutex interface symbol
 */
RTM_EXPORT(rt_mutex_init)
RTM_EXPORT(rt_mutex_detach)
RTM_EXPORT(rt_mutex_create)
RTM_EXPORT(rt_mutex_delete)
RTM_EXPORT(rt_mutex_take)
RTM_EXPORT(rt_mutex_release)
RTM_EXPORT(rt_mutex_control)
#endif

#ifdef RT_USING_EVENT
/*
 * event interface symbol
 */
RTM_EXPORT(rt_event_init)
RTM_EXPORT(rt_event_detach)
RTM_EXPORT(rt_event_create)
RTM_EXPORT(rt_event_delete)
RTM_EXPORT(rt_event_send)
RTM_EXPORT(rt_event_recv)
RTM_EXPORT(rt_event_control) 
#endif

#ifdef RT_USING_MAILBOX
/*
 * mailbox interface symbol
 */
RTM_EXPORT(rt_mb_init)
RTM_EXPORT(rt_mb_detach)
RTM_EXPORT(rt_mb_create)
RTM_EXPORT(rt_mb_delete)
RTM_EXPORT(rt_mb_send)
RTM_EXPORT(rt_mb_recv)
RTM_EXPORT(rt_mb_control) 
#endif

#ifdef RT_USING_MESSAGEQUEUE
/*
 * message queue interface symbol
 */
RTM_EXPORT(rt_mq_init)
RTM_EXPORT(rt_mq_detach)
RTM_EXPORT(rt_mq_create)
RTM_EXPORT(rt_mq_delete)
RTM_EXPORT(rt_mq_send)
RTM_EXPORT(rt_mq_urgent)
RTM_EXPORT(rt_mq_recv)  
RTM_EXPORT(rt_mq_control)  
#endif

#ifdef RT_USING_MEMPOOL
/*
 * memory pool interface symbol
 */
RTM_EXPORT(rt_mp_init)
RTM_EXPORT(rt_mp_detach)
RTM_EXPORT(rt_mp_create)
RTM_EXPORT(rt_mp_delete)
RTM_EXPORT(rt_mp_alloc)
RTM_EXPORT(rt_mp_free)
#endif

#ifdef RT_USING_HEAP
/*
 * heap memory interface symbol
 */
RTM_EXPORT(rt_malloc)
RTM_EXPORT(rt_free)
RTM_EXPORT(rt_realloc)
RTM_EXPORT(rt_calloc)
#endif
/*
 * clock & timer interface symbol
 */
RTM_EXPORT(rt_tick_get)
RTM_EXPORT(rt_tick_from_millisecond)
RTM_EXPORT(rt_system_timer_init)
RTM_EXPORT(rt_system_timer_thread_init)
RTM_EXPORT(rt_timer_init)
RTM_EXPORT(rt_timer_detach)
RTM_EXPORT(rt_timer_create)
RTM_EXPORT(rt_timer_delete)
RTM_EXPORT(rt_timer_start)
RTM_EXPORT(rt_timer_stop)
RTM_EXPORT(rt_timer_control)

/* 
 * kservice interface symbol
 */
extern int __aeabi_ddiv; 
extern int __aeabi_dmul;
extern int __aeabi_i2d;
extern int __aeabi_uidiv;
extern int __aeabi_uidivmod;
extern int __aeabi_d2iz;
extern int rand;

RTM_EXPORT(rt_kprintf)
RTM_EXPORT(rt_memcpy)
RTM_EXPORT(rt_memset)
RTM_EXPORT(rt_sprintf)
RTM_EXPORT(__aeabi_ddiv)
RTM_EXPORT(__aeabi_dmul)
RTM_EXPORT(__aeabi_i2d)
RTM_EXPORT(__aeabi_uidiv)
RTM_EXPORT(__aeabi_uidivmod)
RTM_EXPORT(__aeabi_d2iz)
RTM_EXPORT(rand)

#ifdef RT_USING_RTGUI
/* FIX ME , should be removed from here */
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>
#include <rtgui/widgets/widget.h>

RTM_EXPORT(rtgui_view_show)
RTM_EXPORT(rtgui_view_create)
RTM_EXPORT(rtgui_view_destroy)
RTM_EXPORT(rtgui_view_event_handler)
RTM_EXPORT(rtgui_dc_draw_text)
RTM_EXPORT(rtgui_dc_begin_drawing)
RTM_EXPORT(rtgui_dc_end_drawing)
RTM_EXPORT(rtgui_workbench_event_loop)
RTM_EXPORT(rtgui_workbench_event_handler)
RTM_EXPORT(rtgui_workbench_add_view)
RTM_EXPORT(rtgui_workbench_create)
RTM_EXPORT(rtgui_workbench_destroy)
RTM_EXPORT(rtgui_workbench_close)
RTM_EXPORT(rtgui_timer_start)
RTM_EXPORT(rtgui_timer_create)
RTM_EXPORT(rtgui_timer_stop)
RTM_EXPORT(rtgui_widget_focus)
RTM_EXPORT(rtgui_widget_set_event_handler)
RTM_EXPORT(rtgui_thread_register)
RTM_EXPORT(rtgui_thread_deregister)

#endif
#endif
