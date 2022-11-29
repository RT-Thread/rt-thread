/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2010-02-04     Magicoe      ported to LPC17xx
 * 2010-05-02     Aozima       update CMSIS to 130
 * 2017-08-02     XiaoYang     porting to LPC54608 bsp
 * 2019-08-05     Magicoe      porting to LPC55S69-EVK bsp
 * 2020-01-01     Karl         Add PKG_USING_TFM support
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "clock_config.h"
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

/**
 * This function will initial LPC55Sxx board.
 */
void rt_hw_board_init()
{
    /* Hardware Initialization */
    BOARD_InitPins();

    CLOCK_EnableClock(kCLOCK_InputMux);

    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);

    GPIO_PortInit(GPIO, 0);
    GPIO_PortInit(GPIO, 1);

    /* NVIC Configuration */
#define NVIC_VTOR_MASK              0x3FFFFF80
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x10000000 */
    SCB->VTOR  = (0x10000000 & NVIC_VTOR_MASK);
#else  /* VECT_TAB_FLASH  */

#ifdef PKG_USING_TFM
    /* Set the Vector Table base location at 0x00020000 when RTT with TF-M*/
    SCB->VTOR  = (0x00020000 & NVIC_VTOR_MASK);
#else
    /* Set the Vector Table base location at 0x00000000 */
    SCB->VTOR  = (0x00000000 & NVIC_VTOR_MASK);
#endif
#endif

#ifndef PKG_USING_TFM
    /* This init has finished in secure side of TF-M  */
    BOARD_BootClockPLL150M();
#endif
    //BOARD_BootClockFROHF96M();

    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    /* set pend exception priority */
    NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    /*init uart device*/
    rt_hw_uart_init();

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization board with RT-Thread Components */
    rt_components_board_init();
#endif

#ifdef RT_USING_HEAP
    rt_kprintf("sram heap, begin: 0x%p, end: 0x%p\n", HEAP_BEGIN, HEAP_END);
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
}

/**
 * This function will called when memory fault.
 */
void MemManage_Handler(void)
{
    extern void HardFault_Handler(void);

    rt_kprintf("Memory Fault!\n");
    HardFault_Handler();
}

void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    ticks = us * reload / (1000000 / RT_TICK_PER_SECOND);
    told = SysTick->VAL;
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}
