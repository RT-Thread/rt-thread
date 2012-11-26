/*
 * File      : dc_buffer.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-04-10     Bernard      first version
 * 2010-06-14     Bernard      embedded hardware dc to each widget
 * 2010-08-09     Bernard      rename hardware dc to client dc
 */

#ifndef __RTGUI_DC_CLIENT_H__
#define __RTGUI_DC_CLIENT_H__

#include <rtgui/dc.h>

/* create a hardware dc */
struct rtgui_dc *rtgui_dc_client_create(rtgui_widget_t *owner);
void rtgui_dc_client_init(rtgui_widget_t *owner);

#endif

