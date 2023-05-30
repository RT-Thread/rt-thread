/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2018-03-15     flyingcys    add amebaz
 */
#include <rtl8710b.h>
#include <stdint.h>
#include "board.h"
#include "drv_uart.h"

#ifdef __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN         (__segment_end("HEAP"))
#elif  defined(__GNUC__)
extern int __rtt_heap_start;
#define HEAP_BEGIN          (&__rtt_heap_start)
#else
#error "not support toolchain!!!"
#endif

#define HEAP_END           (0x1002FFFF)

#ifdef __GNUC__
void __wrap_rtl_printf(const char *fmt, ...)
{
    va_list args;
    rt_size_t length;
    static char rt_log_buf[RT_CONSOLEBUF_SIZE];

    va_start(args, fmt);
    /* the return value of vsnprintf is the number of bytes that would be
     * written to buffer had if the size of the buffer been sufficiently
     * large excluding the terminating null byte. If the output string
     * would be larger than the rt_log_buf, we have to adjust the output
     * length. */
    length = rt_vsnprintf(rt_log_buf, sizeof(rt_log_buf) - 1, fmt, args);
    if (length > RT_CONSOLEBUF_SIZE - 1)
        length = RT_CONSOLEBUF_SIZE - 1;
    rt_kprintf("%s", rt_log_buf);
    va_end(args);
}
#endif

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

 uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1) > SysTick_LOAD_RELOAD_Msk)  return (1);      /* Reload value impossible */

  SysTick->LOAD  = ticks - 1;                                  /* set reload register */
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Systick Interrupt */
  SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
  return (0);                                                  /* Function successful */
}

/**
 * This function will initial board.
 */
void rt_hw_board_init(void)
{
    extern uint32_t SystemCoreClock;
    SysTick_Config(SystemCoreClock/RT_TICK_PER_SECOND);

#ifdef RT_USING_HEAP
        rt_system_heap_init((void*)HEAP_BEGIN, (void*)HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_hw_uart_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

/*@}*/
