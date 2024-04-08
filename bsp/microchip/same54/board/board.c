/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date        Author    Email                    Notes
 * 2019-07-16  Kevin.Liu kevin.liu.mchp@gmail.com First Release
 */

#include <string.h>

#include <atmel_start.h>
#include "peripheral_clk_config.h"

#include <rtthread.h>
#include "board.h"

#ifdef RT_USING_SERIAL
extern int rt_hw_uart_init(void);
#endif

static struct io_descriptor* g_stdio;
static uint8_t board_info[16] = "Microchip SAME54";

void rt_hw_console_output(const char *str)
{
    io_write(g_stdio, (uint8_t *)str, strlen(str));
    while (TARGET_IO.stat != 0);
}
RTM_EXPORT(rt_hw_console_output);

static inline void hw_board_init_usart(void)
{
    usart_async_get_io_descriptor(&TARGET_IO, &g_stdio);
    usart_async_enable(&TARGET_IO);
    io_write(g_stdio, board_info, 16);
}

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
 * This function will initial SAME54 board.
 */
void rt_hw_board_init(void)
{
    /* Initializes MCU, drivers and middleware */
    atmel_start_init();

    /* enable USART stdout module */
    hw_board_init_usart();

    /* UART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

    /* init systick */
    SysTick_Config(CONF_CPU_FREQUENCY / RT_TICK_PER_SECOND);

    /* set pend exception priority */
    NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

#ifdef RT_USING_HEAP
    #if defined(__ARMCC_VERSION)
        rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)HEAP_END);
    #elif __ICCARM__
        rt_system_heap_init((void*)HEAP_BEGIN, (void*)HEAP_END);
    #else
        /* init memory system */
        rt_system_heap_init((void*)&__bss_end, (void*)HEAP_END);
    #endif
#endif

    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

/*@}*/
