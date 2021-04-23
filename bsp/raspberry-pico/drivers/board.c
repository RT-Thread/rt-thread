/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-01-28     flybreak       first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <stdio.h>

#include "board.h"
#include "hardware/structs/systick.h"

void isr_systick(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

uint32_t systick_config(uint32_t ticks)
{
  if ((ticks - 1UL) > M0PLUS_SYST_RVR_RELOAD_BITS)
  {
    return (1UL);                                                   /* Reload value impossible */
  }

  mpu_hw->rvr    = (uint32_t)(ticks - 1UL);                         /* set reload register */
  mpu_hw->csr  = M0PLUS_SYST_CSR_CLKSOURCE_BITS |
                   M0PLUS_SYST_CSR_TICKINT_BITS   |
                   M0PLUS_SYST_CSR_ENABLE_BITS;                     /* Enable SysTick IRQ and SysTick Timer */
  return (0UL);                                                     /* Function successful */
}

void rt_hw_board_init()
{
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);

    alarm_pool_init_default();

    // Start and end points of the constructor list,
    // defined by the linker script.
    extern void (*__init_array_start)();
    extern void (*__init_array_end)();

    // Call each function in the list.
    // We have to take the address of the symbols, as __init_array_start *is*
    // the first function pointer, not the address of it.
    for (void (**p)() = &__init_array_start; p < &__init_array_end; ++p) {
        (*p)();
    }

    /* Configure the SysTick */
    systick_config(frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC)*10000/RT_TICK_PER_SECOND);

    stdio_init_all();
    rt_hw_uart_init();

#ifdef RT_USING_CONSOLE
   rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}
