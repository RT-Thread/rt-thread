/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-18     Bernard      The first version for LPC40xx
 * 2014-07-18     ArdaFu       Port to TM4C129X
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"

#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
typedef struct hw_uart_device
{
    uint32_t hw_base; // base address
}hw_uart_t;

#define mUartGetHwPtr(serial) ((hw_uart_t*)(serial->parent.user_data))

static rt_err_t hw_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    uint32_t config = 0;
    hw_uart_t* uart;
    RT_ASSERT(serial != RT_NULL);
    uart = mUartGetHwPtr(serial);

    MAP_UARTDisable(uart->hw_base);
    // build UART Configuration parameter structure
    switch(cfg->data_bits)
    {
    case DATA_BITS_9:
        // enable 9bit address mode and set DATA_BIT_8
        MAP_UART9BitEnable(uart->hw_base);
    case DATA_BITS_8:
        config |= UART_CONFIG_WLEN_8;
        break;
    case DATA_BITS_7:
        config |= UART_CONFIG_WLEN_7;
        break;
    case DATA_BITS_6:
        config |= UART_CONFIG_WLEN_6;
        break;
    case DATA_BITS_5:
        config |= UART_CONFIG_WLEN_5;
        break;
    default:
        RT_ASSERT(0);
        break;
    }
    switch(cfg->parity)
    {
    case PARITY_ODD:
        config |= UART_CONFIG_PAR_ODD;
        break;
    case PARITY_EVEN:
        config |= UART_CONFIG_PAR_EVEN;
        break;
    case PARITY_NONE:
        config |= UART_CONFIG_PAR_NONE;
        break;
    default:
        RT_ASSERT(0);
        break;
    }
    switch(cfg->stop_bits)
    {
    case STOP_BITS_1:
        config |= UART_CONFIG_STOP_ONE;
        break;
    case STOP_BITS_2:
        config |= UART_CONFIG_STOP_TWO;
        break;
    default:
        RT_ASSERT(0);
        break;
    }

    // Initialize UART0 peripheral with given to corresponding parameter
    MAP_UARTConfigSetExpClk(uart->hw_base, SystemCoreClock, cfg->baud_rate, config);
    MAP_UARTFIFOEnable(uart->hw_base);

    // Enable the UART.
    MAP_UARTEnable(uart->hw_base);
    return RT_EOK;
}

static rt_err_t hw_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    hw_uart_t* uart;
    RT_ASSERT(serial != RT_NULL);
    uart = mUartGetHwPtr(serial);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        MAP_UARTIntDisable(uart->hw_base, UART_INT_RX | UART_INT_RT);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        MAP_UARTIntEnable(uart->hw_base, UART_INT_RX | UART_INT_RT);
        break;
    }

    return RT_EOK;
}

static int hw_putc(struct rt_serial_device *serial, char c)
{
    hw_uart_t* uart;
    RT_ASSERT(serial != RT_NULL);
    uart = mUartGetHwPtr(serial);

    MAP_UARTCharPut(uart->hw_base, *((uint8_t *)&c));
    return 1;
}

static int hw_getc(struct rt_serial_device *serial)
{
    hw_uart_t* uart;
    RT_ASSERT(serial != RT_NULL);
    uart = mUartGetHwPtr(serial);

    return MAP_UARTCharGetNonBlocking(uart->hw_base);
}

static const struct rt_uart_ops hw_uart_ops =
{
    hw_configure,
    hw_control,
    hw_putc,
    hw_getc,
};

#if defined(RT_USING_UART0)
/* UART0 device driver structure */
struct rt_serial_device serial0;
hw_uart_t uart0 =
{
    UART0_BASE,
};

void UART0_IRQHandler(void)
{
    uint32_t intsrc;
    hw_uart_t *uart = &uart0;

    /* enter interrupt */
    rt_interrupt_enter();

    /* Determine the interrupt source */
    intsrc = MAP_UARTIntStatus(uart->hw_base, true);

    // Receive Data Available or Character time-out
    if (intsrc & (UART_INT_RX | UART_INT_RT))
    {
        MAP_UARTIntClear(uart->hw_base, intsrc);
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

int rt_hw_uart_init(void)
{
    hw_uart_t* uart;
    struct serial_configure config;

    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

#ifdef RT_USING_UART0
    uart = &uart0;
    serial0.ops    = &hw_uart_ops;
    serial0.config = config;

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);

    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    /* preemption = 1, sub-priority = 1 */
    //IntPrioritySet(INT_UART0, ((0x01 << 5) | 0x01));

    /* Enable Interrupt for UART channel */
      UARTIntRegister(uart->hw_base, UART0_IRQHandler);
      MAP_IntEnable(INT_UART0);
      MAP_UARTEnable(uart->hw_base);

    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
