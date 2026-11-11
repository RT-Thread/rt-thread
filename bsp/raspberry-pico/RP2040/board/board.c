/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-01-28     flybreak       first version
 * 2023-01-22     rose_man       add RT_USING_SMP
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

#define PLL_SYS_KHZ (133 * 1000)

void isr_systick(void)
{
    /* enter interrupt */
#ifndef RT_USING_SMP
    rt_interrupt_enter();
#endif

    rt_tick_increase();

    /* leave interrupt */
#ifndef RT_USING_SMP
    rt_interrupt_leave();
#endif
}

uint32_t systick_config(uint32_t ticks)
{
    if ((ticks - 1UL) > M0PLUS_SYST_RVR_RELOAD_BITS)
    {
        return (1UL);                                                   /* Reload value impossible */
    }

    systick_hw->rvr    = (uint32_t)(ticks - 1UL);                         /* set reload register */
    systick_hw->csr  = M0PLUS_SYST_CSR_CLKSOURCE_BITS |
                   M0PLUS_SYST_CSR_TICKINT_BITS   |
                   M0PLUS_SYST_CSR_ENABLE_BITS;                     /* Enable SysTick IRQ and SysTick Timer */
    return (0UL);                                                     /* Function successful */
}

void rt_hw_board_init()
{
    set_sys_clock_khz(PLL_SYS_KHZ, true);

#ifdef RT_USING_HEAP
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);
#endif

#ifdef RT_USING_SMP
    extern rt_hw_spinlock_t _cpus_lock;
    rt_hw_spin_lock_init(&_cpus_lock);
#endif

    alarm_pool_init_default();

    // Start and end points of the constructor list,
    // defined by the linker script.
    extern void (*__init_array_start)();
    extern void (*__init_array_end)();

    // Call each function in the list.
    // We have to take the address of the symbols, as __init_array_start *is*
    // the first function pointer, not the address of it.
    for (void (**p)() = &__init_array_start; p < &__init_array_end; ++p)
    {
        (*p)();
    }

    /* Configure the SysTick */
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

#ifdef RT_USING_MSH
static int pico_reboot(int argc, char *argv[])
{
    reset_usb_boot(0, 0);
    return 0;
}
MSH_CMD_EXPORT_ALIAS(pico_reboot, reboot, reset Pico to BOOTSEL mode);
#endif
