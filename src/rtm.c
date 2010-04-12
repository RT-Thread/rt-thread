/*
 * File      : module.c
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
#include <rtm.h>

/* some buildin kernel symbol */

/* thread symbol */
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

/* kservice symbol */
RTM_EXPORT(rt_kprintf)
