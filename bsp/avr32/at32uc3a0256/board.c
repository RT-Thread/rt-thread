/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2010-03-30     Kyle            First version
 * 2023-10-13     Raman Gopalan   Move UART specific code sections into the drv_uart files
 * 2023-10-20     Raman Gopalan   Initialize GPIO sub-system
 */

#include <rtthread.h>
#include "compiler.h"
#include "pm.h"
#include "gpio.h"
#include "usart.h"
#include "intc.h"
#include "drv_uart.h"
#include "drv_gpio.h"

/**
 * System tick interrupt handler.
 */
static void rt_hw_timer_handler(void)
{
    // Clears the interrupt request.
    Set_system_register(AVR32_COMPARE, FCPU / RT_TICK_PER_SECOND);

    rt_tick_increase();
}

/**
 * Initialize system clock and all peripherals.
 */
static void peripherals_init(void)
{
    /*
     * PM initialization: OSC0 = 12MHz XTAL, PLL0 = 60MHz System Clock
     */
    pm_freq_param_t pm_freq_param =
    {
        .cpu_f = FCPU,
        .pba_f = FPBA,
        .osc0_f = FOSC0,
        .osc0_startup = AVR32_PM_OSCCTRL0_STARTUP_2048_RCOSC
    };
    pm_configure_clocks(&pm_freq_param);
    INTC_init_interrupts();
}

/**
 * Initialize CPU cycle counter for system tick.
 */
static void cpu_counter_init(void)
{
    INTC_register_interrupt(&rt_hw_timer_handler, AVR32_CORE_COMPARE_IRQ, AVR32_INTC_INT3);
    Set_system_register(AVR32_COMPARE, FCPU / RT_TICK_PER_SECOND);
    Set_system_register(AVR32_COUNT, 0);
}

void rt_hw_board_init(void)
{
    Disable_global_interrupt();

    peripherals_init();
    cpu_counter_init();

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

#ifdef RT_USING_PIN
    rt_hw_gpio_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}
