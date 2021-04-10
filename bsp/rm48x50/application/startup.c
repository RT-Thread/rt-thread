/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     xuxinming    first version
 * 2010-4-3       LiJin        add init soft timer thread
 * 2013-05-24     Grissiom     port to RM48x50
 */

#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
extern int finsh_system_init(void);
#endif

#include <board.h>

/**
 * @addtogroup LPC2478
 */
/*@{*/

extern int  rt_application_init(void);
#ifdef RT_USING_DEVICE
extern rt_err_t rt_hw_serial_init(void);
#endif

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#elif defined(__GNUC__)
extern int __bss_end;
#elif defined(__TI_COMPILER_VERSION__)
extern unsigned char * const system_data_end;
#endif
#define MEMEND 0x08040000

void rt_hw_pmu_enable_cnt(void)
{
    unsigned long tmp;

    __asm ("    MRC p15, #0, r0, c9, c12, #0");
    __asm ("    ORR r0, r0, #0x09\n");
    __asm ("    MCR p15, #0, r0, c9, c12, #0\n");
    __asm ("    MOV r0, #1\n");
    __asm ("    RBIT r0, r0\n");
    __asm ("    MCR p15, #0, r0, c9, c12, #1\n");
}

void rt_hw_pmu_setcnt(unsigned long val)
{
    __asm ("    MCR   p15, #0, r0, c9, c13, #0");
}

unsigned long rt_hw_pmu_getcnt(void)
{
    __asm ("    MRC   p15, #0, r0, c9, c13, #0");
}

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    /*// RM48 does not have cache implemented
     *rt_hw_cpu_icache_enable();
     *rt_hw_cpu_dcache_enable();
     */

    /* init hardware interrupt */
    rt_hw_interrupt_init();

    /* init board */
    rt_hw_board_init();

    rt_show_version();

    /* init timer system */
    rt_system_timer_init();

    /* init memory system */
#ifdef RT_USING_HEAP
#ifdef __CC_ARM
    rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)MEMEND);
#elif defined(__GNUC__)
    rt_system_heap_init((void*)&__bss_end, (void*)MEMEND);
#elif defined(__TI_COMPILER_VERSION__)
    rt_system_heap_init((void*)&system_data_end, (void*)MEMEND);
#else
#error Unkown compiler
#endif
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init application */
    rt_application_init();

#ifdef RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
    finsh_set_device("sci2");
#endif

    /* init soft timer thread */
    rt_system_timer_thread_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;
}

int main(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* invoke rtthread_startup */
    rtthread_startup();

    return 0;
}

/*@}*/
