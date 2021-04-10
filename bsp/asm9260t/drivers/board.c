/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 * 2015-05-02     ArdaFu     Port from AT91SAM9260 BSP
 */

#include <rtthread.h>
#include <rthw.h>
#include <timer0.h>
#include "board.h"
#include <mmu.h>
#include "interrupt.h"

extern void rt_hw_interrupt_init(void);
extern void rt_hw_clock_init(void);
extern void rt_hw_uart_init(void);

static struct mem_desc hw_mem_desc[] =
{
    { 0x00000000, 0xFFFFFFFF, 0x00000000, RW_NCNB },/* None cached for 4G memory */
//  visual start, visual end, phy start , props
    { 0x00000000, 0x000FFFFF, 0x20000000, RW_CB },  /* ISR Vector table */
    { 0x00200000, 0x00001FFF, 0x40000000, RW_CB },  /* 8K cached SRAM 0/1 */
    { 0x20000000, 0x21FFFFFF, 0x20000000, RW_CB },  /* 32M cached SDRAM */
    { 0x90000000, 0x90001FFF, 0x40000000, RW_NCNB },/* 4K SRAM0 + 4k SRAM1 */
    { 0xA0000000, 0xA1FFFFFF, 0x20000000, RW_NCNB },/* 32M none-cached SDRAM */
};

/**
 * This function will handle rtos timer
 */
static void rt_systick_handler(int vector, void *param)
{
    uint32_t ir = inl(HW_TIMER0_IR);
    if (ir & 1UL)
        rt_tick_increase();
    outl(ir, REG_SET(HW_TIMER0_IR));
}

/**
 * This function will init pit for system ticks
 */
static void rt_hw_timer_init()
{
    hw_timer0_init();
    /* install interrupt handler */
    rt_hw_interrupt_install(INT_TIMER0, rt_systick_handler, RT_NULL, "SysTick");
    rt_hw_interrupt_umask(INT_TIMER0);

}

/**
 * This function will init at91sam9260 board
 */
void rt_hw_board_init(void)
{
    /* initialize mmu */
    rt_hw_mmu_init(hw_mem_desc, sizeof(hw_mem_desc)/sizeof(hw_mem_desc[0]));
    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize the system clock */
    //rt_hw_clock_init(); //set each pll etc.

    /* initialize uart */
    rt_hw_uart_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

    /* initialize timer0 */
    rt_hw_timer_init();
}
