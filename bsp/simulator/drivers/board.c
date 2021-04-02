/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 */
#include <rthw.h>
#include <rtthread.h>

#include <stdlib.h>

#include "board.h"
#include "uart_console.h"

/**
 * @addtogroup simulator on win32
 */

rt_uint8_t *rt_hw_sram_init(void)
{
    rt_uint8_t *heap;
    heap = malloc(RT_HEAP_SIZE);
    if (heap == RT_NULL)
    {
        rt_kprintf("there is no memory in pc.");
#ifdef _WIN32
        _exit(1);
#else
        exit(1);
#endif
    }
#ifdef RT_USING_HEAP
    /* init memory system */
    rt_system_heap_init((void*)heap, (void*)&heap[RT_HEAP_SIZE - 1]);
#endif
    return heap;
}

#ifdef _WIN32
#include <windows.h>
#endif

void rt_hw_win32_low_cpu(void)
{
#ifdef _WIN32
    /* in windows */
    Sleep(1000);
#else
    /* in linux */
    sleep(1);
#endif
}

#ifdef _MSC_VER
#ifndef _CRT_TERMINATE_DEFINED
#define _CRT_TERMINATE_DEFINED
_CRTIMP __declspec(noreturn) void __cdecl exit(__in int _Code);
_CRTIMP __declspec(noreturn) void __cdecl _exit(__in int _Code);
_CRTIMP void __cdecl abort(void);
#endif
#endif

void rt_hw_exit(void)
{
    rt_kprintf("RT-Thread, bye\n");
#if !defined(_WIN32) && defined(__GNUC__)
    /* *
     * getchar reads key from buffer, while finsh need an non-buffer getchar
     * in windows, getch is such an function, in linux, we had to change
     * the behaviour of terminal to get an non-buffer getchar.
     * in usart_sim.c, set_stty is called to do this work
     * */
    {
        extern void restore_stty(void);
        restore_stty();
    }
#endif
    exit(0);
}

#if defined(RT_USING_FINSH)
#include <finsh.h>
FINSH_FUNCTION_EXPORT_ALIAS(rt_hw_exit, exit, exit rt - thread);
FINSH_FUNCTION_EXPORT_ALIAS(rt_hw_exit, __cmd_quit, exit rt-thread);
#endif /* RT_USING_FINSH */

/**
 * This function will initial win32
 */
int rt_hw_board_init(void)
{
    /* init system memory */
    rt_hw_sram_init();

    uart_console_init();

#ifdef _WIN32
    rt_thread_idle_sethook(rt_hw_win32_low_cpu);
#endif

#if defined(RT_USING_CONSOLE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    /* init board */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
    return 0;
}
/*@}*/
