/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"
#include "drv_timer.h"

#include "cp15.h"

#ifdef RT_USING_SMP
unsigned int cntfrq;
#endif

void rt_hw_timer_isr(int vector, void *parameter)
{
    rt_tick_increase();
#ifndef RT_USING_SMP
    ARM_TIMER_IRQCLR = 0;
#else
    mask_cntv();
    __DSB();
    write_cntv_tval(cntfrq);
    __DSB();
    unmask_cntv();
    __DSB();
#endif
}

int rt_hw_timer_init()
{
#ifndef RT_USING_SMP
    /* timer_clock = apb_clock/(pre_divider + 1) */
    ARM_TIMER_PREDIV = (250 - 1);

    ARM_TIMER_RELOAD = 0;
    ARM_TIMER_LOAD   = 0;
    ARM_TIMER_IRQCLR = 0;
    ARM_TIMER_CTRL   = 0;

    ARM_TIMER_RELOAD = 10000;
    ARM_TIMER_LOAD   = 10000;

    /* 23-bit counter, enable interrupt, enable timer */
    ARM_TIMER_CTRL   = (1 << 1) | (1 << 5) | (1 << 7);
#else
    __DSB();
    cntfrq = 35000;
    write_cntv_tval(cntfrq);
    enable_cntv();
    __DSB();
    enable_cpu_timer_intr(rt_hw_cpu_id());
#endif

    rt_hw_interrupt_install(IRQ_ARM_TIMER, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(IRQ_ARM_TIMER);
    return 0;
}
#ifdef RT_USING_SMP
extern void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler);

void ipi_handler()
{
    rt_scheduler_ipi_handler(0,RT_NULL);
}
#endif

void idle_wfi(void)
{
    asm volatile ("wfi");
}

void rt_hw_board_init(void)
{
    /* initialize hardware interrupt */
    rt_hw_interrupt_init();
    rt_hw_vector_init();
    /* initialize uart */
    rt_hw_uart_init();
    /* initialize timer for os tick */
    rt_hw_timer_init();
    rt_thread_idle_sethook(idle_wfi);
#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif /* RT_USING_CONSOLE */
#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_kprintf("heap: 0x%08x - 0x%08x\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

#ifdef RT_USING_SMP
    /* install IPI handle */
    rt_hw_ipi_handler_install(IRQ_ARM_MAILBOX, ipi_handler);
    rt_hw_interrupt_umask(IRQ_ARM_MAILBOX);
    enable_cpu_ipi_intr(0);
#endif
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

}


void _reset(void);
void secondary_cpu_start(void);

#ifdef RT_USING_SMP
void rt_hw_secondary_cpu_up(void)
{
    int i;
    int retry,val;
    rt_cpu_dcache_clean_flush();
    rt_cpu_icache_flush();
    /*TODO maybe, there is some bug */
    for (i = RT_CPUS_NR - 1; i>0; i-- )
    {
        rt_kprintf("boot cpu:%d\n", i);
        setup_bootstrap_addr(i, (int)_reset);
        __SEV();
        __DSB();
        __ISB();
        retry = 10;
        rt_thread_delay(RT_TICK_PER_SECOND/1000);
        do
        {
            val = CORE_MAILBOX3_CLEAR(i);
            if (val == 0)
            {
                rt_kprintf("start OK: CPU %d \n",i);
                break;
            }
            rt_thread_delay(RT_TICK_PER_SECOND);

            retry --;
            if (retry <= 0)
            {
                rt_kprintf("can't start for CPU %d \n",i);
                break;
            }
        } while (1);
    }
    __DSB();
    __SEV();
}

void secondary_cpu_c_start(void)
{
    uint32_t id;
    id = rt_hw_cpu_id();
    rt_kprintf("cpu = 0x%08x\n",id);
    rt_hw_timer_init();
    rt_kprintf("cpu %d startup.\n",id);
    rt_hw_vector_init();
    enable_cpu_ipi_intr(id);
    rt_hw_spin_lock(&_cpus_lock);
    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    __WFE();
}

#endif


