/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021/04/22     Juice             Add isrtable for JuiceVm.
 */
typedef void (*irq_handler_t)(void);
// #define DEFINE_IRQ_HANDLER(irq_handler, driver_irq_handler) \
//     void __attribute__((weak)) irq_handler(void) { driver_irq_handler();}

// #define DEFINE_DEFAULT_IRQ_HANDLER(irq_handler) void irq_handler() __attribute__((weak, alias("DefaultIRQHandler")))

// DEFINE_IRQ_HANDLER(UART0_IRQHandler, UART0_DriverIRQHandler);
extern void UART0_DriverIRQHandler(void);

const irq_handler_t isrTable[] =
{
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    UART0_DriverIRQHandler, // uart0_irq_ecode = 24

};
