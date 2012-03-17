/*
 * File      : rtm.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
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
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* some buildin kernel symbol */

#ifdef RT_USING_MODULE
#include <rtm.h>

RTM_EXPORT(rt_object_get_information);

/*
 * thread  interface symbol 
 */
 
RTM_EXPORT(rt_thread_init);
RTM_EXPORT(rt_thread_detach);
RTM_EXPORT(rt_thread_create);
RTM_EXPORT(rt_thread_self);
RTM_EXPORT(rt_thread_find);
RTM_EXPORT(rt_thread_startup);
RTM_EXPORT(rt_thread_delete);
RTM_EXPORT(rt_thread_yield);
RTM_EXPORT(rt_thread_delay);
RTM_EXPORT(rt_thread_control);
RTM_EXPORT(rt_thread_suspend);
RTM_EXPORT(rt_thread_resume);
RTM_EXPORT(rt_thread_timeout);

#ifdef RT_USING_SEMAPHORE
/*
 * semaphore interface symbol
 */
RTM_EXPORT(rt_sem_init);
RTM_EXPORT(rt_sem_detach);
RTM_EXPORT(rt_sem_create);
RTM_EXPORT(rt_sem_delete);
RTM_EXPORT(rt_sem_take);
RTM_EXPORT(rt_sem_trytake);
RTM_EXPORT(rt_sem_release);
RTM_EXPORT(rt_sem_control);
#endif

#ifdef RT_USING_MUTEX
/*
 * mutex interface symbol
 */
RTM_EXPORT(rt_mutex_init);
RTM_EXPORT(rt_mutex_detach);
RTM_EXPORT(rt_mutex_create);
RTM_EXPORT(rt_mutex_delete);
RTM_EXPORT(rt_mutex_take);
RTM_EXPORT(rt_mutex_release);
RTM_EXPORT(rt_mutex_control);
#endif

#ifdef RT_USING_EVENT
/*
 * event interface symbol
 */
RTM_EXPORT(rt_event_init);
RTM_EXPORT(rt_event_detach);
RTM_EXPORT(rt_event_create);
RTM_EXPORT(rt_event_delete);
RTM_EXPORT(rt_event_send);
RTM_EXPORT(rt_event_recv);
RTM_EXPORT(rt_event_control); 
#endif

#ifdef RT_USING_MAILBOX
/*
 * mailbox interface symbol
 */
RTM_EXPORT(rt_mb_init);
RTM_EXPORT(rt_mb_detach);
RTM_EXPORT(rt_mb_create);
RTM_EXPORT(rt_mb_delete);
RTM_EXPORT(rt_mb_send);
RTM_EXPORT(rt_mb_recv);
RTM_EXPORT(rt_mb_control); 
#endif

#ifdef RT_USING_MESSAGEQUEUE
/*
 * message queue interface symbol
 */
RTM_EXPORT(rt_mq_init);
RTM_EXPORT(rt_mq_detach);
RTM_EXPORT(rt_mq_create);
RTM_EXPORT(rt_mq_delete);
RTM_EXPORT(rt_mq_send);
RTM_EXPORT(rt_mq_urgent);
RTM_EXPORT(rt_mq_recv);  
RTM_EXPORT(rt_mq_control);  
#endif

#ifdef RT_USING_MEMPOOL
/*
 * memory pool interface symbol
 */
RTM_EXPORT(rt_mp_init);
RTM_EXPORT(rt_mp_detach);
RTM_EXPORT(rt_mp_create);
RTM_EXPORT(rt_mp_delete);
RTM_EXPORT(rt_mp_alloc);
RTM_EXPORT(rt_mp_free);
#endif

#ifdef RT_USING_HEAP
/*
 * heap memory interface symbol
 */
RTM_EXPORT(rt_malloc);
RTM_EXPORT(rt_free);
RTM_EXPORT(rt_realloc);
RTM_EXPORT(rt_calloc);
#endif
/*
 * clock & timer interface symbol
 */
RTM_EXPORT(rt_tick_get);
RTM_EXPORT(rt_tick_from_millisecond);
RTM_EXPORT(rt_system_timer_init);
RTM_EXPORT(rt_system_timer_thread_init);
RTM_EXPORT(rt_timer_init);
RTM_EXPORT(rt_timer_detach);
RTM_EXPORT(rt_timer_create);
RTM_EXPORT(rt_timer_delete);
RTM_EXPORT(rt_timer_start);
RTM_EXPORT(rt_timer_stop);
RTM_EXPORT(rt_timer_control);

/* 
 * kservice interface symbol
 */
RTM_EXPORT(rt_memcpy);
RTM_EXPORT(rt_memcmp);
RTM_EXPORT(rt_memset);
RTM_EXPORT(rt_kprintf);
RTM_EXPORT(rt_sprintf);
RTM_EXPORT(rt_strstr);
RTM_EXPORT(rt_snprintf);

/* 
 * misc interface symbol
 */
extern int __aeabi_idiv; 
extern int __aeabi_ddiv; 
extern int __aeabi_dmul;
extern int __aeabi_i2d;
extern int __aeabi_uidiv;
extern int __aeabi_uidivmod;
extern int __aeabi_idivmod;
extern int __aeabi_d2iz;

RTM_EXPORT(__aeabi_ddiv);
RTM_EXPORT(__aeabi_dmul);
RTM_EXPORT(__aeabi_i2d);
RTM_EXPORT(__aeabi_uidiv);
RTM_EXPORT(__aeabi_idiv);
RTM_EXPORT(__aeabi_idivmod);
RTM_EXPORT(__aeabi_uidivmod);
RTM_EXPORT(__aeabi_d2iz);
RTM_EXPORT(strcmp);
RTM_EXPORT(strcpy);
RTM_EXPORT(strlen);
RTM_EXPORT(rand);
RTM_EXPORT(memset);
RTM_EXPORT(memcpy);

#if defined(RT_USING_NEWLIB) && defined(RT_USING_PTHREADS)

#include <unistd.h>

RTM_EXPORT(printf);
RTM_EXPORT(snprintf);
RTM_EXPORT(access);
RTM_EXPORT(__assert_func);

#include <time.h>
RTM_EXPORT(localtime);
RTM_EXPORT(time);

#include <math.h>
RTM_EXPORT(sin);
RTM_EXPORT(cos);

#endif

#ifdef RT_USING_DFS
#include <dfs_posix.h>

RTM_EXPORT(open);
RTM_EXPORT(close);
RTM_EXPORT(read);
RTM_EXPORT(write);
RTM_EXPORT(stat);
#endif

#ifdef RT_USING_RTGUI
/* FIX ME , should be removed from here */
#include <rtgui/dc.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/list_view.h>
#include <rtgui/widgets/listctrl.h>
#include <rtgui/widgets/filelist_view.h>

RTM_EXPORT(rtgui_label_create);
RTM_EXPORT(rtgui_view_show);
RTM_EXPORT(rtgui_view_create);
RTM_EXPORT(rtgui_view_destroy);
RTM_EXPORT(rtgui_view_event_handler);
RTM_EXPORT(rtgui_dc_draw_text);
RTM_EXPORT(rtgui_dc_begin_drawing);
RTM_EXPORT(rtgui_dc_end_drawing);
RTM_EXPORT(rtgui_workbench_event_loop);
RTM_EXPORT(rtgui_workbench_event_handler);
RTM_EXPORT(rtgui_workbench_add_view);
RTM_EXPORT(rtgui_workbench_create);
RTM_EXPORT(rtgui_workbench_destroy);
RTM_EXPORT(rtgui_workbench_close);
RTM_EXPORT(rtgui_timer_start);
RTM_EXPORT(rtgui_timer_create);
RTM_EXPORT(rtgui_timer_destory);
RTM_EXPORT(rtgui_timer_stop);
RTM_EXPORT(rtgui_thread_register);
RTM_EXPORT(rtgui_thread_deregister);
RTM_EXPORT(rtgui_widget_focus);
RTM_EXPORT(rtgui_widget_set_event_handler);
RTM_EXPORT(rtgui_widget_rect_to_device);
RTM_EXPORT(rtgui_widget_update);
RTM_EXPORT(rtgui_widget_get_rect);
RTM_EXPORT(rtgui_widget_set_rect);
RTM_EXPORT(rtgui_widget_get_toplevel);
RTM_EXPORT(rtgui_panel_register);
RTM_EXPORT(rtgui_panel_set_default_focused);
RTM_EXPORT(rtgui_button_create);
RTM_EXPORT(rtgui_button_destroy);
RTM_EXPORT(rtgui_button_set_onbutton);
RTM_EXPORT(rtgui_container_add_child);
RTM_EXPORT(rtgui_filelist_view_create);
RTM_EXPORT(rtgui_filelist_view_get_fullpath);
RTM_EXPORT(rtgui_list_view_create);
RTM_EXPORT(rtgui_list_view_destroy);
RTM_EXPORT(rtgui_listctrl_set_onitem);
RTM_EXPORT(rtgui_image_create_from_mem);
RTM_EXPORT(rtgui_listctrl_create);
RTM_EXPORT(rtgui_listctrl_set_items);

#endif
#endif

