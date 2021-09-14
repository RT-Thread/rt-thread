/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 * 2021-07-31     GuEe-GUI       config the memory/io address map
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include <mmu.h>
#include "drv_uart.h"

void rt_hw_vector_init(void);

static uint64_t tickval = 0;

void rt_hw_timer_isr(int vector, void *parameter)
{
    uint64_t cntvct_el0;

    do
    {
        tickval += 0xF424;
        __asm__ volatile ("msr CNTV_CVAL_EL0, %0"::"r"(tickval));
        __asm__ volatile ("mrs %0, CNTVCT_EL0":"=r"(cntvct_el0));
    }
    while (cntvct_el0 >= tickval);

    rt_tick_increase();
}

int rt_hw_timer_init()
{
    uint64_t val;

    rt_hw_interrupt_install(27, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(27);

    val = 0;
    __asm__ volatile ("msr CNTV_CTL_EL0, %0"::"r"(val));
    val = 0x03B9ACA0;
    __asm__ volatile ("msr CNTFRQ_EL0, %0"::"r"(val));
    tickval += 0xF424;
    __asm__ volatile ("msr CNTV_CVAL_EL0, %0"::"r"(tickval));
    val = 1;
    __asm__ volatile ("msr CNTV_CTL_EL0, %0"::"r"(val));
    return 0;
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
    uint64_t cont;

    mmu_init();
    cont = (uint64_t)RT_HW_HEAP_END + 0x1fffff;
    cont &= ~0x1fffff;
    cont -= 0x40000000;
    cont >>= 21;
    /* memory location */
    armv8_map_2M(0x40000000, 0x40000000, cont, MEM_ATTR_MEMORY);
    /* uart location*/
    armv8_map_2M(PL011_UART0_BASE, PL011_UART0_BASE, 0x1, MEM_ATTR_IO);
    /* gic location*/
    armv8_map_2M(GIC_PL390_DISTRIBUTOR_PPTR, GIC_PL390_DISTRIBUTOR_PPTR, 0x1, MEM_ATTR_IO);
    mmu_enable();

    /* initialize hardware interrupt */
    rt_hw_interrupt_init(); // in libcpu/interrupt.c. Set some data structures, no operation on device
    rt_hw_vector_init();    // in libcpu/interrupt.c. == rt_cpu_vector_set_base((rt_ubase_t)&system_vectors);

    /* initialize uart */
    rt_hw_uart_init();      // driver/drv_uart.c
    /* initialize timer for os tick */
    rt_hw_timer_init();
    rt_thread_idle_sethook(idle_wfi);

#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif /* RT_USING_CONSOLE */

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_kprintf("heap: [0x%08x - 0x%08x]\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
