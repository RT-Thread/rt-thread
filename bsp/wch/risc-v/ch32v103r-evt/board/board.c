/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-24     Tanek        the first version
 * 2018-11-12     Ernest Chen  modify copyright
 */

#include "board.h"

#include <stdint.h>
#include "drv_usart.h"
#include "drv_gpio.h"

#include <rthw.h>
#include <rtthread.h>


/* Updates the variable SystemCoreClock and must be called
 * whenever the core clock is changed during program execution.
 */
extern void SystemCoreClockUpdate(void);

/* core clock */
extern uint32_t SystemCoreClock;

volatile rt_uint32_t g_ticks=0;

static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
    g_ticks=ticks;
    /* disable hardware pushing stack automatically and disable interrupt nesting */
    PFIC->CFGR=0xFA050003;
    NVIC_SetPriority(SysTicK_IRQn,0xf0);
    NVIC_SetPriority(Software_IRQn,0xf0);
    SysTick->CTLR=0;
    SysTick->CNTL0=0;SysTick->CNTL1=0;SysTick->CNTL2=0;SysTick->CNTL3=0;
    SysTick->CNTH0=0;SysTick->CNTH1=0;SysTick->CNTH2=0;SysTick->CNTH3=0;
    SysTick->CMPLR0=(rt_uint8_t)(g_ticks-1);
    SysTick->CMPLR1=(rt_uint8_t)((g_ticks-1)>>8);
    SysTick->CMPLR2=(rt_uint8_t)((g_ticks-1)>>16);
    SysTick->CMPLR3=(rt_uint8_t)((g_ticks-1)>>24);
    SysTick->CMPHR0=0;SysTick->CMPHR1=0;SysTick->CMPHR2=0;SysTick->CMPHR3=0;
    SysTick->CTLR=0x1;
    NVIC_EnableIRQ(SysTicK_IRQn);
    NVIC_EnableIRQ(Software_IRQn);
    return 0;
}

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE (1024)
/* heap default size: 4K(1024 * 4) */
static uint32_t rt_heap[RT_HEAP_SIZE];
rt_weak void *rt_heap_begin_get(void)
{
    return rt_heap;
}

rt_weak void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{
    /* System Clock Update */
    SystemCoreClockUpdate();

    /* System Tick Configuration, systick clock is HCLK/8 */
    _SysTick_Config(SystemCoreClock / 8 / RT_TICK_PER_SECOND);
    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_PIN
    /* pin must initialized before i2c */
    rt_hw_pin_init();
#endif
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}


void SysTick_Handler(void) __attribute__((interrupt()));
void SysTick_Handler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();
    SysTick->CTLR=0;
    SysTick->CNTL0=0;SysTick->CNTL1=0;SysTick->CNTL2=0;SysTick->CNTL3=0;
    SysTick->CNTH0=0;SysTick->CNTH1=0;SysTick->CNTH2=0;SysTick->CNTH3=0;
    SysTick->CTLR=0x1;
    rt_tick_increase();
    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();

}
