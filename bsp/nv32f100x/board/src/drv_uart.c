/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-19     Quintin.Z    the first version
 */

#include <rtdevice.h>
#include <board.h>
#include "drv_uart.h"
#include "nv32.h"
#include "uart.h"
#include "sim.h"

/* NV32 uart driver */
struct nv32_uart
{
    UART_Type* uart_device;
    IRQn_Type irq;
};

static rt_err_t nv32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct nv32_uart* uart;

    UART_ConfigBaudrateType uart_config;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct nv32_uart *)serial->parent.user_data;

    uart_config.u32SysClkHz = BUS_CLK_HZ;
    uart_config.u32Baudrate = cfg->baud_rate;

    UART_SetBaudrate(uart->uart_device, &uart_config);


    if (cfg->data_bits == DATA_BITS_8)
    {
        UART_Set8BitMode(uart->uart_device);
    }
    else if(cfg->data_bits == DATA_BITS_9)
    {
        UART_Set9BitMode(uart->uart_device);
    }

    if (cfg->stop_bits == STOP_BITS_1)
    {
        uart->uart_device->BDH  &= (~UART_BDH_SBNS_MASK);
    }
    else if (cfg->stop_bits == STOP_BITS_2)
    {
        uart->uart_device->BDH  |= UART_BDH_SBNS_MASK;
    }

    /* Enable receiver and transmitter */
    uart->uart_device->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK );


    UART_EnableInterrupt(UART0, UART_RxBuffFullInt);
    NVIC_EnableIRQ(UART0_IRQn);


    return RT_EOK;
}

static rt_err_t nv32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct nv32_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct nv32_uart *)serial->parent.user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT:
            /* disable rx irq */
            NVIC_DisableIRQ(uart->irq);
            break;
        case RT_DEVICE_CTRL_SET_INT:
            /* enable rx irq */
            NVIC_EnableIRQ(uart->irq);
            break;
    }

    return RT_EOK;
}

static int nv32_putc(struct rt_serial_device *serial, char c)
{
    struct nv32_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct nv32_uart *)serial->parent.user_data;

    while (!(uart->uart_device->S1 & UART_S1_TDRE_MASK));

    uart->uart_device->D = (uint8_t)c;

    return 1;
}


static int nv32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct nv32_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct nv32_uart *)serial->parent.user_data;

    ch = -1;
    if (uart->uart_device->S1 & UART_S1_RDRF_MASK)
    {
        ch = uart->uart_device->D;
    }

    return ch;
}

static const struct rt_uart_ops nv32_uart_ops =
{
    nv32_configure,
    nv32_control,
    nv32_putc,
    nv32_getc,
};

#ifdef RT_USING_UART0

struct nv32_uart uart0 =
{
    UART0,
    UART0_IRQn,
};

struct rt_serial_device serial0;

void UART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(UART0->S1 & UART_S1_RDRF_MASK)
    {
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif


void rt_hw_uart_init(void)
{
    struct nv32_uart* uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART0
    uart = &uart0;

    serial0.ops    = &nv32_uart_ops;
    serial0.config = config;


    SIM->PINSEL |= SIM_PINSEL_UART0PS_MASK;

    SIM->SCGC |= SIM_SCGC_UART0_MASK;

    uart->uart_device->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );

    /* Configure the UART for 8-bit mode, no parity */
    uart->uart_device->C1 = 0;

    rt_hw_serial_register(&serial0, "uart0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
#endif

}

