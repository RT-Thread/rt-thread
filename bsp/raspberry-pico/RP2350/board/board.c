/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-01-28     flybreak       first version
 * 2023-01-22     rose_man       add RT_USING_SMP
 * 2025-08-04     hydevcode       first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <stdio.h>
#include "board.h"
#include <pico/bootrom.h>
#include <pico/stdlib.h>
#include <hardware/clocks.h>
#include <hardware/structs/systick.h>
#include <drv_uart.h>

#define PLL_SYS_KHZ (150 * 1000)

void SysTick_Handler(void)
{
    rt_interrupt_enter();
    rt_tick_increase();
    rt_interrupt_leave();
}

uint32_t systick_config(uint32_t ticks)
{
    if ((ticks - 1UL) > M33_SYST_RVR_RELOAD_BITS)
    {
        return (1UL);                                                   /* Reload value impossible */
    }

    systick_hw->rvr    = (uint32_t)(ticks - 1UL);                         /* set reload register */
    systick_hw->csr  = M33_SYST_CSR_CLKSOURCE_BITS |
                    M33_SYST_CSR_TICKINT_BITS   |
                    M33_SYST_CSR_ENABLE_BITS;                     /* Enable SysTick IRQ and SysTick Timer */
}
#include "pico/runtime.h"
void rt_hw_board_init()
{
    #ifdef RT_USING_HEAP
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);
    #endif
    set_sys_clock_khz(PLL_SYS_KHZ, true);

    alarm_pool_init_default();
    systick_config(clock_get_hz(clk_sys) / RT_TICK_PER_SECOND);


#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_SERIAL
    stdio_init_all();
    rt_hw_uart_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}