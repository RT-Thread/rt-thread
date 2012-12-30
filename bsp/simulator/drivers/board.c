/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include <stdlib.h>
#include <windows.h>

/**
 * @addtogroup simulator on win32
 */
rt_uint8_t *heap;

rt_uint8_t *rt_hw_sram_init(void)
{
    rt_uint8_t *heap;
    heap = malloc(RT_HEAP_SIZE);
    if (heap == RT_NULL)
    {
        rt_kprintf("there is no memory in pc.");
        _exit(1);
    }
    return heap;
}

void rt_hw_win32_low_cpu(void)
{
    Sleep(1000);
}

#if defined(RT_USING_FINSH)

#ifndef _CRT_TERMINATE_DEFINED
#define _CRT_TERMINATE_DEFINED
_CRTIMP __declspec(noreturn) void __cdecl exit(__in int _Code);
_CRTIMP __declspec(noreturn) void __cdecl _exit(__in int _Code);
_CRTIMP void __cdecl abort(void);
#endif

#include <finsh.h>
void rt_hw_exit(void)
{
    rt_kprintf("RT-Thread, bye\n");
    exit(0);
}
FINSH_FUNCTION_EXPORT_ALIAS(rt_hw_exit, exit, exit rt - thread);
#endif /* RT_USING_FINSH */

/**
 * This function will initial win32
 */
void rt_hw_board_init()
{
    /* init system memory */
    heap = rt_hw_sram_init();

#if defined(RT_USING_CONSOLE)
    rt_hw_usart_init();
    rt_hw_serial_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}
/*@}*/
