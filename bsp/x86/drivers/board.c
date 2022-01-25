/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-15     QiuYi        the first version
 * 2006-10-10     Bernard      add hardware related of finsh
 */

#include <rthw.h>
#include <rtthread.h>

#include <bsp.h>

extern unsigned char __bss_start[];
extern unsigned char __bss_end[];
extern void rt_hw_console_init(void);

/**
 * @addtogroup QEMU
 */
/*@{*/
static void rt_timer_handler(int vector, void* param)
{
    rt_tick_increase();
}

#ifdef RT_USING_HOOK
static void idle_hook(void)
{
    asm volatile("sti; hlt": : :"memory");
}
#endif

/* clear .bss */
void rt_hw_clear_bss(void)
{
    unsigned char *dst;
    dst = __bss_start;
    while (dst < __bss_end)
        *dst++ = 0;
}

/**
 * This function will init QEMU
 *
 */
void rt_hw_board_init(void)
{
    /* clear .bss */
    rt_hw_clear_bss();

    /* init hardware interrupt */
    rt_hw_interrupt_init();

    /* init the console */
    rt_hw_console_init();
    rt_console_set_device("console");

    /* initialize 8253 clock to interrupt 1000 times/sec */
    outb(TIMER_MODE, TIMER_SEL0|TIMER_RATEGEN|TIMER_16BIT);
    outb(IO_TIMER1, TIMER_DIV(RT_TICK_PER_SECOND) % 256);
    outb(IO_TIMER1, TIMER_DIV(RT_TICK_PER_SECOND) / 256);

    /* install interrupt handler */
    rt_hw_interrupt_install(INTTIMER0, rt_timer_handler, RT_NULL, "tick");
    rt_hw_interrupt_umask(INTTIMER0);

    /* init memory system */
#ifdef RT_USING_HEAP
    /* RAM 16M */
    rt_system_heap_init((void *)&__bss_end, (void *)(1024UL*1024*8));
#endif

#ifdef RT_USING_HOOK
    rt_thread_idle_sethook(idle_hook);
#endif
}

static int reboot(void)
{
    outb(KBSTATP, 0xFE); /* pulse reset low */

    return 0;
}
MSH_CMD_EXPORT(reboot, reboot system);
/*@}*/
