/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
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
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
/*****************************************************************************
 *  Include Section
 *  add all #include here
 *  those macro below should define....
 *  or the dsp or isp lib will not be supported
 *****************************************************************************/
#include <rtconfig.h>

//#pragma comment ( linker, "/EXPORT: MyExportFunction = _MyExportFunctio" )
//#pragma message
//#warning RT_NAME_MAX=32
//#error ....

//#define yu_error(macro) #error  ##macro


/**************************
 *
 *
 * define value below.
 *
 *
 **************************/
#if RT_NAME_MAX	!= 16
#error "define RT_NAME_MAX 16"
#endif

#if RT_TICK_PER_SECOND	!= 100
#warning "RT_TICK_PER_SECOND = 100"
#endif


#if RT_ALIGN_SIZE  != 4
#error "define RT_ALIGN_SIZE 4"
#endif

/**************************
 *
 *
 * should define below..
 *
 *
 **************************/
#ifndef RT_USING_SEMAPHORE
#error need define "RT_USING_SEMAPHORE"
#endif

#ifndef RT_USING_MUTEX
#error need define "RT_USING_MUTEX"
#endif

#ifndef RT_USING_EVENT
#error need define "RT_USING_EVENT"
#endif

#ifndef RT_USING_MAILBOX
#error need define "RT_USING_MAILBOX"
#endif

#ifndef RT_USING_MESSAGEQUEUE
#warning need define "RT_USING_MESSAGEQUEUE"
#endif

#ifndef RT_USING_MEMPOOL
#warning need define "RT_USING_MEMPOOL"
#endif

#ifndef RT_USING_HEAP
#error need define "RT_USING_HEAP"
#endif

#ifndef RT_USING_MEMHEAP
#warning need define "RT_USING_MEMHEAP"
#endif

#ifndef RT_USING_DEVICE
#error need define "RT_USING_DEVICE"
#endif

#ifndef RT_USING_CONSOLE
#error need define "RT_USING_CONSOLE"
#endif

#ifndef RT_USING_FINSH
#error need define "RT_USING_FINSH"
#endif

#ifndef RT_USING_I2C
#error need define "RT_USING_I2C"
#endif




