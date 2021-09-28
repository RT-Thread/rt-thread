/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-30     Kyle         First version
 */

#include <rtthread.h>
#include "compiler.h"
#include "pm.h"
#include "gpio.h"
#include "usart.h"
#include "intc.h"
#include "serial.h"

#define FOSC0   12000000
#define FCPU    60000000
#define FHSB    FCPU
#define FPBA    FCPU
#define FPBB    FCPU

extern void rt_hw_serial_isr(void);
extern void rt_hw_usart_init(void);

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

    /*
     * USART1 initialization
     */
    gpio_enable_module_pin(AVR32_USART1_TXD_0_1_PIN, AVR32_USART1_TXD_0_1_FUNCTION);
    gpio_enable_module_pin(AVR32_USART1_RXD_0_1_PIN, AVR32_USART1_RXD_0_1_FUNCTION);
    static const usart_options_t usartOptions = {
        .baudrate = 115200,
        .charlength = 8,
        .paritytype = USART_NO_PARITY,
        .stopbits = USART_1_STOPBIT,
        .channelmode = USART_NORMAL_CHMODE
    };
    usart_init_rs232(&AVR32_USART1, &usartOptions, FCPU);

    INTC_init_interrupts();
    INTC_register_interrupt(&rt_hw_serial_isr, AVR32_USART1_IRQ, AVR32_INTC_INT0);
    AVR32_USART1.ier = AVR32_USART_IER_RXRDY_MASK;
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
    extern struct rt_device _rt_usart_device;
    extern struct avr32_serial_device uart;

    Disable_global_interrupt();

    peripherals_init();
    cpu_counter_init();

    rt_hw_serial_register(&_rt_usart_device, "uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM, &uart);
    rt_console_set_device("uart1");
}
