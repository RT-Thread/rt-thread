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
#include "mbox.h"

#ifdef BSP_USING_CORETIMER
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
#endif

void rt_hw_timer_isr(int vector, void *parameter)
{
#ifdef BSP_USING_CORETIMER
    rt_hw_set_gtimer_val(timerStep);
#else
    ARM_TIMER_IRQCLR = 0;
#endif
    rt_tick_increase();
}

void rt_hw_timer_init(void)
{
#ifdef BSP_USING_CORETIMER
    rt_hw_interrupt_install(TIMER_IRQ, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(TIMER_IRQ);
    __ISB();
    timerStep = rt_hw_get_gtimer_frq();
    __DSB();
    timerStep /= RT_TICK_PER_SECOND;

    rt_hw_gtimer_enable();
    rt_hw_set_gtimer_val(timerStep);
    core0_timer_enable_interrupt_controller();
#else
    rt_uint32_t apb_clock = 0;
    rt_uint32_t timer_clock = 1000000;

    apb_clock = bcm271x_mbox_clock_get_rate(CORE_CLK_ID);
    ARM_TIMER_PREDIV = (apb_clock/timer_clock - 1);

    ARM_TIMER_RELOAD = 0;
    ARM_TIMER_LOAD   = 0;
    ARM_TIMER_IRQCLR = 0;
    ARM_TIMER_CTRL   = 0;

    ARM_TIMER_RELOAD = 1000000 / RT_TICK_PER_SECOND;
    ARM_TIMER_LOAD   = 1000000 / RT_TICK_PER_SECOND;

    /* 23-bit counter, enable interrupt, enable timer */
    ARM_TIMER_CTRL   = (1 << 1) | (1 << 5) | (1 << 7);

    rt_hw_interrupt_install(ARM_TIMER_IRQ, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(ARM_TIMER_IRQ);
#endif
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
    armv8_map(ARM_TIMER_BASE, ARM_TIMER_BASE, 0x200000, MEM_ATTR_IO);//arm timer
    armv8_map(STIMER_BASE, STIMER_BASE, 0x200000, MEM_ATTR_IO);//stimer
    armv8_map(MMC2_BASE_ADDR, MMC2_BASE_ADDR, 0x200000, MEM_ATTR_IO);//mmc
    armv8_map(MBOX_ADDR, MBOX_ADDR, 0x200000, MEM_ATTR_IO);//mbox msg
    armv8_map((unsigned long)MAC_REG_BASE_ADDR, (unsigned long)MAC_REG_BASE_ADDR, 0x80000, MEM_ATTR_IO);//mac
    armv8_map(SEND_DATA_NO_CACHE, SEND_DATA_NO_CACHE, 0x200000, MEM_ATTR_MEMORY);//eth send
    armv8_map(RECV_DATA_NO_CACHE, RECV_DATA_NO_CACHE, 0x200000, MEM_ATTR_MEMORY);//eth recv
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
