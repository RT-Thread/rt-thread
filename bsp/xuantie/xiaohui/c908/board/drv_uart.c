/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <rthw.h>
#include <rtdevice.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"

#ifdef RT_USING_SMART
#include <ioremap.h>
#endif

struct device_uart
{
    rt_ubase_t hw_base;
    rt_uint32_t irqno;
};

static void *uart0_base = (void *)XIAOHUI_UART0_PHY_ADDR;
static struct rt_serial_device serial0;
static struct device_uart uart0;

/* 32-bit stride register access */
rt_inline rt_uint32_t uart_read(int reg)
{
    return *(volatile rt_uint32_t *)((rt_ubase_t)uart0_base + ((rt_ubase_t)reg << 2));
}

rt_inline void uart_write(int reg, rt_uint32_t val)
{
    *(volatile rt_uint32_t *)((rt_ubase_t)uart0_base + ((rt_ubase_t)reg << 2)) = val;
}

static rt_err_t _uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    /* the boot firmware/QEMU model already configured the line; enable FIFO */
    uart_write(UART_FCR, UART_FCR_FIFO_ENABLE | UART_FCR_FIFO_CLEAR);
    return RT_EOK;
}

static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        if ((size_t)arg == RT_DEVICE_FLAG_INT_RX)
        {
            uart_write(UART_IER, uart_read(UART_IER) & ~UART_IER_RX_ENABLE);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        if ((size_t)arg == RT_DEVICE_FLAG_INT_RX)
        {
            uart_write(UART_IER, uart_read(UART_IER) | UART_IER_RX_ENABLE);
        }
        break;
    }

    return RT_EOK;
}

static int _uart_putc(struct rt_serial_device *serial, char c)
{
    while ((uart_read(UART_LSR) & UART_LSR_TX_IDLE) == 0);
    uart_write(UART_THR, (rt_uint32_t)(rt_uint8_t)c);

    return 1;
}

static int _uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;

    if (uart_read(UART_LSR) & UART_LSR_RX_READY)
    {
        ch = (int)(uart_read(UART_RHR) & 0xFF);
    }
    return ch;
}

static const struct rt_uart_ops _uart_ops = {
    _uart_configure,
    _uart_control,
    _uart_putc,
    _uart_getc,
    RT_NULL,
};

static void _uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

/*
 * UART Initiation
 */
int rt_hw_uart_init(void)
{
    struct rt_serial_device *serial;
    struct device_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_SMART
    uart0_base = rt_ioremap((void *)XIAOHUI_UART0_PHY_ADDR, 4096);
#endif

    serial = &serial0;
    uart = &uart0;

    serial->ops = &_uart_ops;
    serial->config = config;
    serial->config.baud_rate = 115200;
    uart->hw_base = (rt_ubase_t)uart0_base;
    uart->irqno = XIAOHUI_UART0_IRQ;

    rt_hw_serial_register(serial,
                          RT_CONSOLE_DEVICE_NAME,
                          RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
    rt_hw_interrupt_install(uart->irqno, _uart_isr, serial, RT_CONSOLE_DEVICE_NAME);
    rt_hw_interrupt_umask(uart->irqno);
    return 0;
}
