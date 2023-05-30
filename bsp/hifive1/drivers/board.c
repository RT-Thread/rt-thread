/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <interrupt.h>
#include <rthw.h>

#include <board.h>
#include <platform.h>
#include <encoding.h>
#include <interrupt.h>

extern void use_default_clocks(void);
extern void use_pll(int refsel, int bypass, int r, int f, int q);

#define TICK_COUNT  (2 * RTC_FREQ / RT_TICK_PER_SECOND)

#define MTIME       (*((volatile uint64_t *)(CLINT_CTRL_ADDR + CLINT_MTIME)))
#define MTIMECMP    (*((volatile uint64_t *)(CLINT_CTRL_ADDR + CLINT_MTIMECMP)))

/* system tick interrupt */
void handle_m_time_interrupt()
{
    MTIMECMP = MTIME + TICK_COUNT;
    rt_tick_increase();
}

/* fixed misaligned bug for qemu */
void *__wrap_memset(void *s, int c, size_t n)
{
    return rt_memset(s, c, n);
}

static void rt_hw_clock_init(void)
{
    use_default_clocks();
    use_pll(0, 0, 1, 31, 1);
}

static void rt_hw_timer_init(void)
{
    MTIMECMP = MTIME + TICK_COUNT;

    /*  enable timer interrupt*/
    set_csr(mie, MIP_MTIP);
}

void rt_hw_board_init(void)
{
    /* initialize the system clock */
    rt_hw_clock_init();

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize timer0 */
    rt_hw_timer_init();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    return;
}

