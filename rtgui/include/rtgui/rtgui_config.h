/*
 * File      : rtgui_config.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */

#ifndef __RTGUI_CONFIG_H__
#define __RTGUI_CONFIG_H__

/* RTGUI options */

/* name length of RTGUI object */
#define RTGUI_NAME_MAX		32

/* #define RTGUI_USING_MOUSE_CURSOR */

/* #define RTGUI_USING_FONT16 */

#define RT_USING_STDIO_FILERW
#define RTGUI_IMAGE_PNG

#define RTGUI_SVR_THREAD_PRIORITY		15
#define RTGUI_SVR_THREAD_TIMESLICE		5

#define RTGUI_APP_THREAD_PRIORITY		25
#define RTGUI_APP_THREAD_TIMESLICE		8

#endif

