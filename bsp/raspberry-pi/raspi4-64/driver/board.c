/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"

#include "cp15.h"
#include "mmu.h"

static rt_uint64_t timerStep;

int rt_hw_get_gtimer_frq(void);
void rt_hw_set_gtimer_val(rt_uint64_t value);
int rt_hw_get_gtimer_val(void);
int rt_hw_get_cntpct_val(void);
void rt_hw_gtimer_enable(void);

void core0_timer_enable_interrupt_controller(void)
{
    CORE0_TIMER_IRQ_CTRL |= NON_SECURE_TIMER_IRQ;
}

void rt_hw_timer_isr(int vector, void *parameter)
{
    rt_hw_set_gtimer_val(timerStep);
    rt_tick_increase();
}

void rt_hw_timer_init(void)
{
    rt_hw_interrupt_install(TIMER_IRQ, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(TIMER_IRQ);
    __ISB();
    timerStep = rt_hw_get_gtimer_frq();
    __DSB();
    timerStep /= RT_TICK_PER_SECOND;

    rt_hw_gtimer_enable();
    rt_hw_set_gtimer_val(timerStep);
    core0_timer_enable_interrupt_controller();
}

void idle_wfi(void)
{
    asm volatile ("wfi");
}

/**
 *  Initialize the Hardware related stuffs. Called from rtthread_startup()
 *  after interrupt disabled.
 */
void rt_hw_board_init(void)
{
    mmu_init();
    armv8_map(0, 0, 0x6400000, MEM_ATTR_MEMORY);
    armv8_map(0xFE200000, 0xFE200000, 0x200000, MEM_ATTR_IO);//uart gpio
    armv8_map(0xFF800000, 0xFF800000, 0x200000, MEM_ATTR_IO);//gic timer
    mmu_enable();

    /* initialize hardware interrupt */
    rt_hw_interrupt_init(); // in libcpu/interrupt.c. Set some data structures, no operation on device
    rt_hw_vector_init();    // in libcpu/interrupt.c. == rt_cpu_vector_set_base((rt_ubase_t)&system_vectors);

    /* initialize uart */
    rt_hw_uart_init();      // driver/drv_uart.c
#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif /* RT_USING_CONSOLE */

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_kprintf("heap: 0x%08x - 0x%08x\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif
        /* initialize timer for os tick */
    rt_hw_timer_init();
    rt_thread_idle_sethook(idle_wfi);

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
