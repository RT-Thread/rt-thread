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
 * 2010-02-08     Bernard      move some RTGUI options to bsp
 */

#ifndef __RTGUI_CONFIG_H__
#define __RTGUI_CONFIG_H__

/* RTGUI options */

#ifndef RT_USING_DFS
#undef RTGUI_USING_DFS_FILERW
#undef RTGUI_USING_HZ_FILE
#endif

#ifdef RT_USING_DFS
/* if file system is used, the DFS_FILERW will be defined */
#ifndef RTGUI_USING_DFS_FILERW
#define RTGUI_USING_DFS_FILERW
#endif
#endif

#if RTGUI_DEFAULT_FONT_SIZE == 0
#define RTGUI_DEFAULT_FONT_SIZE 12
#endif

#define RTGUI_SVR_THREAD_PRIORITY       15
#define RTGUI_SVR_THREAD_TIMESLICE      5
#ifndef RTGUI_SVR_THREAD_STACK_SIZE
#ifdef RTGUI_USING_SMALL_SIZE
#define RTGUI_SVR_THREAD_STACK_SIZE     1024
#else
#define RTGUI_SVR_THREAD_STACK_SIZE     2048
#endif
#endif

#define RTGUI_APP_THREAD_PRIORITY       25
#define RTGUI_APP_THREAD_TIMESLICE      5
#ifdef RTGUI_USING_SMALL_SIZE
#define RTGUI_APP_THREAD_STACK_SIZE     1024
#else
#define RTGUI_APP_THREAD_STACK_SIZE     2048
#endif

// #define RTGUI_USING_CAST_CHECK

// #define RTGUI_USING_DESKTOP_WINDOW
// #undef RTGUI_USING_SMALL_SIZE

//#define RTGUI_USING_CALIBRATION

#define RTGUI_USING_VFRAMEBUFFER

#ifdef DEBUG_MEMLEAK
#define rtgui_malloc     rt_malloc
#define rtgui_realloc    rt_realloc
#define rtgui_free       rt_free
#endif

#endif

