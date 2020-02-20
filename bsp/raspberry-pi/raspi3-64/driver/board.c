/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
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
#include "mmu.h"

#ifdef RT_USING_SMP
extern void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler);

void ipi_handler(){
    rt_scheduler_ipi_handler(0,RT_NULL);
}
#endif

void rt_hw_timer_isr(int vector, void *parameter)
{
    ARM_TIMER_IRQCLR = 0;
    rt_tick_increase();
}

int rt_hw_timer_init()
{
    __DSB();
    rt_hw_interrupt_install(IRQ_ARM_TIMER, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(IRQ_ARM_TIMER);
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
    mmu_init();//初始化mmu
    armv8_map(0, 0, 0x800000, MEM_ATTR_MEMORY);
    armv8_map(0x3f00B000, 0x3f00B000, 0x1000, MEM_ATTR_IO);//timer
    armv8_map(0x3f200000, 0x3f200000, 0x16000, MEM_ATTR_IO);//uart
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
    rt_kprintf("heap: 0x%08x - 0x%08x\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

}

#ifdef RT_USING_SMP
void _reset(void);
void secondary_cpu_start(void);

void rt_hw_secondary_cpu_up(void)
{
    int i;
    int retry,val;
    rt_cpu_dcache_clean_flush();
    rt_cpu_icache_flush();
    /*TODO maybe, there is some bug */
    for(i=RT_CPUS_NR-1; i>0; i-- )
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
        }while (1);
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
