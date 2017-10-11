/*
 * File      : rtgui_config.h
 * This file is part of RT-Thread GUI Engine
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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

