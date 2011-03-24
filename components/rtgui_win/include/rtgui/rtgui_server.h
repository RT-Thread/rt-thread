/*
 * File      : rtgui_server.h
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
#ifndef __RTGUI_SERVER_H__
#define __RTGUI_SERVER_H__

#include <rtgui/list.h>

/* RTGUI server definitions */

#define WINTITLE_HEIGHT			20
#define WINTITLE_BORDER_SIZE	2

/* top win manager init */
void rtgui_win_init(void);
void rtgui_server_init(void);

/* post an event to server */
void rtgui_server_post_event(rtgui_event_t* event, rt_size_t size);

#endif

