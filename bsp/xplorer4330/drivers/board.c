/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2014-06-20     xiaonong     ported to LPC43xx
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"


/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

extern void SystemCoreClockUpdate(void);
/**
 * This function will initial LPC43xx board.
 */
void rt_hw_board_init()
{
#ifdef CORE_M4
    /* NVIC Configuration */
#define NVIC_VTOR_MASK              0x3FFFFF80
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x10000000 */
    SCB->VTOR  = (0x10000000 & NVIC_VTOR_MASK);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x00000000 */
    SCB->VTOR  = (0x00000000 & NVIC_VTOR_MASK);
#endif
#endif
    /* update the core clock */
    SystemCoreClockUpdate();

    /* init systick */
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    /* set pend exception priority */
    NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    /* init uart device */
    rt_hw_uart_init();

    /* setup the console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

#if LPC_EXT_SDRAM == 1
    lpc_sdram_hw_init();
    mpu_init();
#endif
}



