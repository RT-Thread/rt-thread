/*
 * File      : cpu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013-2018, RT-Thread Development Team
 * 
 */

#include <rthw.h>
#include <rtthread.h>

RT_WEAK void machine_reset(void)
{
    rt_kprintf("reboot system...\n");
    rt_hw_interrupt_disable();
    while(1);
}

RT_WEAK void machine_shutdown(void)
{
    rt_kprintf("shutdown...\n");
	rt_hw_interrupt_disable();
    while(1);
}

