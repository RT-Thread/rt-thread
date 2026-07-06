/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-06     yandld       first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "clock_config.h"
#include "drv_uart.h"

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initial board.
 */
void rt_hw_board_init()
{
    BOARD_InitBootPins();

    /* This init has finished in secure side of TF-M  */
    BOARD_InitBootClocks();

    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    /* set pend exception priority */
    NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    /*init uart device*/
    rt_hw_uart_init();

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization board with RT-Thread Components */
    rt_components_board_init();
#endif

#ifdef RT_USING_HEAP
    rt_kprintf("sram heap, begin: 0x%p, end: 0x%p\n", HEAP_BEGIN, HEAP_END);
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)(HEAP_END));
#endif
}



void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    ticks = us * reload / (1000000 / RT_TICK_PER_SECOND);
    told = SysTick->VAL;
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

/**
 * This function will called when memory fault.
 */
void MemManage_Handler(void)
{
    extern void HardFault_Handler(void);

    rt_kprintf("Memory Fault!\n");
    HardFault_Handler();
}

#ifndef NDEBUG
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
void __aeabi_assert(const char *failedExpr, const char *file, int line)
{
    rt_kprintf("ASSERT ERROR \" %s \": file \"%s\" Line \"%d\" \n", failedExpr, file, line);
    for (;;)
    {
        __BKPT(0);
    }
}
#elif defined(__GNUC__)
void __assert_func(const char *file, int line, const char *func, const char *failedExpr)
{
    rt_kprintf("ASSERT ERROR \" %s \": file \"%s\" Line \"%d\" function \"%s\" \n", failedExpr, file, line, func);
    for (;;)
    {
        __BKPT(0);
    }
}
#endif /* __ARMCC_VERSION || __ICCARM__ */
#endif /* NDEBUG */
