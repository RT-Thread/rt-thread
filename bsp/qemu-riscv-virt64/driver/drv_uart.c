/*
 * Copyright (c) 2019-2020, Xim
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <rthw.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_uart.h"

#include <stdio.h>
#include "sbi.h"

#define UART_DEFAULT_BAUDRATE               115200

struct device_uart
{
    rt_ubase_t  hw_base;
    rt_uint32_t irqno;
};

static rt_err_t  rt_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int       drv_uart_putc(struct rt_serial_device *serial, char c);
static int       drv_uart_getc(struct rt_serial_device *serial);

const struct rt_uart_ops _uart_ops =
{
    rt_uart_configure,
    uart_control,
    drv_uart_putc,
    drv_uart_getc,
    //TODO: add DMA support
    RT_NULL
};

void uart_init(void)
{
    return ;
}

struct rt_serial_device  serial1;
struct device_uart       uart1;

/*
 * UART interface
 */
static rt_err_t rt_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct device_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    serial->config = *cfg;

    return (RT_EOK);
}

#define UART_LSR_DR     0x01            /* Data ready */
#define UART_LSR_THRE   0x20            /* Xmit holding register empty */

#define UART_RBR(hw)    HWREG32(hw + 0x00)
#define UART_IER(hw)    HWREG32(hw + 0x04)
#define UART_LSR(hw)    HWREG32(hw + 0x14)

static volatile uint64_t uart_hwbase = 0x10000000;

void uart_putc(char c)
{
    while ((UART_LSR(uart_hwbase) & UART_LSR_THRE) == 0);

    UART_RBR(uart_hwbase) = c;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct device_uart *uart;

    uart = serial->parent.user_data;
    rt_uint32_t channel = 1;

    RT_ASSERT(uart != RT_NULL);
    RT_ASSERT(channel != 3);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        break;

    case RT_DEVICE_CTRL_SET_INT:
        break;
    }

    return (RT_EOK);
}

static int drv_uart_putc(struct rt_serial_device *serial, char c)
{
    sbi_console_putchar(c);
    return (1);
}

static int drv_uart_getc(struct rt_serial_device *serial)
{
    return sbi_console_getchar();
}

char rt_hw_console_getchar(void)
{
    return sbi_console_getchar();
}

static void uart_rx(void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    while(1)
    {
        rt_hw_serial_isr((struct rt_serial_device *)serial,RT_SERIAL_EVENT_RX_IND);
        rt_thread_mdelay(10);
    }
}

void rt_hw_uart_start_rx_thread()
{
    rt_thread_t th;
    RT_ASSERT((th = rt_thread_create("uartrx",uart_rx,(void *)&serial1,8192,8,20)) != RT_NULL);
    RT_ASSERT(rt_thread_startup(th) == RT_EOK);
}

/*
 * UART Initiation
 */
int rt_hw_uart_init(void)
{
    struct rt_serial_device *serial;
    struct device_uart      *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    {
        serial  = &serial1;
        uart    = &uart1;

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = UART_DEFAULT_BAUDRATE;

        uart->hw_base   = 0x10000000;
        uart->irqno     = 0xa;

        rt_hw_serial_register(serial,
                              "uart",
                              RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
    
    return 0;
}

/* WEAK for SDK 0.5.6 */
RT_WEAK void uart_debug_init(int uart_channel)
{
}
