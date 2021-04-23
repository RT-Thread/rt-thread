/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-30     Kyle         First version
 */

#ifndef RTCONFIG_H_
#define RTCONFIG_H_

/* RT_NAME_MAX*/
#define RT_NAME_MAX 8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE   4

/* PRIORITY_MAX*/
#define RT_THREAD_PRIORITY_MAX  32

/* Tick per Second*/
#define RT_TICK_PER_SECOND  100

/* SECTION: RT_DEBUG */
/* Thread Debug*/
//#define RT_DEBUG
/* #define RT_THREAD_DEBUG */

#define RT_USING_OVERFLOW_CHECK

/* Using Hook*/
//#define RT_USING_HOOK

/* SECTION: IPC */
/* Using Semaphore*/
#define RT_USING_SEMAPHORE

/* Using Mutex*/
//#define RT_USING_MUTEX

/* Using Event*/
//#define RT_USING_EVENT

/* Using MailBox*/
//#define RT_USING_MAILBOX

/* Using Message Queue*/
//#define RT_USING_MESSAGEQUEUE

/* SECTION: Memory Management */
/* Using Memory Pool Management*/
#define RT_USING_MEMPOOL

/* Using Dynamic Heap Management*/
#define RT_USING_HEAP

/* Using Small MM*/
#define RT_USING_SMALL_MEM

/* Using SLAB Allocator*/
/* #define RT_USING_SLAB */

/* SECTION: Device System */
/* Using Device System*/
#define RT_USING_DEVICE

/* SECTION: Console options */
/* the buffer size of console*/
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE  128

/* SECTION: FinSH shell options */
/* Using FinSH as Shell*/
#define RT_USING_FINSH
/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_DEVICE_NAME   "uart1"

/* SECTION: RT-Thread/GUI */
//#define RT_USING_DFS

#define RT_USING_DFS_ELMFAT
#define RT_DFS_ELM_WORD_ACCESS
#define RT_DFS_ELM_DRIVES           2

/* SECTION: DFS options */
/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX         2
/* the max number of opened files       */
#define DFS_FD_MAX                  8
/* the max number of cached sector      */
#define DFS_CACHE_MAX_NUM           4

/* SECTION: RT-Thread/GUI */
//#define RT_USING_RTGUI

/* name length of RTGUI object */
#define RTGUI_NAME_MAX      12
/* support 16 weight font */
#define RTGUI_USING_FONT16
/* support Chinese font */
#define RTGUI_USING_FONTHZ
/* use DFS as file interface */
#define RTGUI_USING_DFS_FILERW
/* use font file as Chinese font */
#define RTGUI_USING_HZ_FILE
/* use small size in RTGUI */
#define RTGUI_USING_SMALL_SIZE
/* use mouse cursor */
/* #define RTGUI_USING_MOUSE_CURSOR */
/* default font size in RTGUI */
#define RTGUI_DEFAULT_FONT_SIZE 16

#endif /* RTCONFIG_H_ */
