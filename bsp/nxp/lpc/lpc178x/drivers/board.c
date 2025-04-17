/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2010-02-04     Magicoe      ported to LPC17xx
 * 2010-05-02     Aozima       update CMSIS to 130
 */

#include <rthw.h>
#include <rtthread.h>

#include "uart.h"
#include "board.h"
#include "LPC177x_8x.h"
#include "system_LPC177x_8x.h"
#include "sdram.h"

/**
 * @addtogroup LPC17xx
 */

/*@{*/

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
 * This function will initial LPC17xx board.
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

    /* init systick */
    SysTick_Config(SystemCoreClock/RT_TICK_PER_SECOND);
    /* set pend exception priority */
    NVIC_SetPriority(PendSV_IRQn, (1<<__NVIC_PRIO_BITS) - 1);

#ifdef RT_USING_HEAP
    /* initialize memory system */
    #ifdef __CC_ARM
        rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)(0x10000000 + 1024*64));
    #elif __ICCARM__
        rt_system_heap_init(__segment_end("HEAP"), (void*)(0x10000000 + 1024*64));
    #else
        rt_system_heap_init((void*)&__bss_end, (void*)(0x10000000 + 1024*64));
    #endif
#endif

    /* USART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif

    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if LPC_EXT_SDRAM == 1
    {
        SDRAM_Init();
    }
#endif
}

/*@}*/
