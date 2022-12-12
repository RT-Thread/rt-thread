/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-29     supperthomas first version
 *
 */
#include <rtthread.h>
#include <rthw.h>
#include <nrfx_systick.h>

#include "board.h"
#include "drv_uart.h"
#include <nrfx_clock.h>

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

static void clk_event_handler(nrfx_clock_evt_type_t event){}

void SysTick_Configuration(void)
{
    nrfx_clock_init(clk_event_handler);
    nrfx_clock_enable();
    nrfx_clock_lfclk_start();
    /* Set interrupt priority */
    NVIC_SetPriority(SysTick_IRQn, 0xf);

    /* Configure SysTick to interrupt at the requested rate. */
    nrf_systick_load_set(SystemCoreClock / RT_TICK_PER_SECOND);
    nrf_systick_val_clear();
    nrf_systick_csr_set(NRF_SYSTICK_CSR_CLKSOURCE_CPU | NRF_SYSTICK_CSR_TICKINT_ENABLE
                        | NRF_SYSTICK_CSR_ENABLE);

}

/**
 * The time delay function.
 *
 * @param microseconds.
 */
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

void rt_hw_board_init(void)
{
    rt_hw_interrupt_enable(0);
    // sd_power_dcdc_mode_set(NRF_POWER_DCDC_ENABLE);
    /* Activate deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    SysTick_Configuration();

#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef BSP_USING_SOFTDEVICE
    extern uint32_t  Image$$RW_IRAM1$$Base;
    uint32_t const *const m_ram_start  = &Image$$RW_IRAM1$$Base;
    if ((uint32_t)m_ram_start == 0x20000000)
    {
        rt_kprintf("\r\n using softdevice the RAM couldn't be %p,please use the templete from package\r\n", m_ram_start);
        while (1);
    }
    else
    {
        rt_kprintf("\r\n using softdevice the RAM at %p\r\n", m_ram_start);
    }
#endif

}

