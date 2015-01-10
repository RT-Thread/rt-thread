/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2010-02-04     Magicoe      ported to LPC17xx
 * 2010-05-02     Aozima       update CMSIS to 130
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"

#ifdef RT_USING_COMPONENTS_INIT
#include <components.h>
#endif



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




/**
 * This function will initial LPC54xx board.
 */
void rt_hw_board_init()
{
    /* NVIC Configuration */
#define NVIC_VTOR_MASK              0x3FFFFF80
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x10000000 */
    SCB->VTOR  = (0x10000000 & NVIC_VTOR_MASK);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x00000000 */
    SCB->VTOR  = (0x00000000 & NVIC_VTOR_MASK);
#endif
		SystemCoreClockUpdate();
    /* init systick  1 systick = 1/(100M / 100) 100¸ösystick = 1s*/
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    /* set pend exception priority */
    NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    /*init uart device*/
    rt_hw_uart_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

#if LPC_EXT_SDRAM == 1
    lpc_sdram_hw_init();
    mpu_init();
#endif

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization board with RT-Thread Components */
    rt_components_board_init();
#endif
}


/* initialization for system heap */
int rt_hw_board_heap_init(void)
{
#ifdef RT_USING_HEAP
#if LPC_EXT_SDRAM
#include "drv_sram.h"
    rt_system_heap_init((void *)LPC_EXT_SDRAM_BEGIN, (void *)LPC_EXT_SDRAM_END);
    sram_init();
#else
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
#endif

    return 0;
}

void MemManage_Handler(void)
{
    extern void HardFault_Handler(void);

    rt_kprintf("Memory Fault!\n");
    HardFault_Handler();
}
