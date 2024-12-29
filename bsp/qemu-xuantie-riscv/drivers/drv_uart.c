/*
 * serial.c UART driver
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/12/11     flyingcys    The first version
 */

#include <rthw.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_uart.h"

#define DBG_TAG "DRV.UART"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

struct hw_uart_device
{
    rt_size_t hw_base;
    rt_size_t irqno;
};

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}
static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct hw_uart_device *uart;
    int32_t ret = 0;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    dw_uart_regs_t *dw_uart = (dw_uart_regs_t *)uart->hw_base;

    dw_uart_fifo_init(dw_uart);

    dw_uart_disable_trans_irq(dw_uart);
    dw_uart_disable_recv_irq(dw_uart);
    dw_uart_disable_auto_flow_control(dw_uart);

    ret = dw_uart_config_baudrate(dw_uart, cfg->baud_rate, BSP_UART_FREQ);
    if (ret != 0)
    {
        return -RT_ERROR;
    }

    switch (cfg->data_bits)
    {
        case DATA_BITS_5:
            ret = dw_uart_config_data_bits(dw_uart, 5U);
            break;

        case DATA_BITS_6:
            ret = dw_uart_config_data_bits(dw_uart, 6U);
            break;

        case DATA_BITS_7:
            ret = dw_uart_config_data_bits(dw_uart, 7U);
            break;

        case DATA_BITS_8:
            ret = dw_uart_config_data_bits(dw_uart, 8U);
            break;

        default:
            LOG_E("unsupported data bits %d\n", cfg->data_bits);
            ret = -1;
            break;
    }

    if (ret != 0)
    {
        return -RT_ERROR;
    }

    switch (cfg->stop_bits)
    {
        case STOP_BITS_1:
            ret = dw_uart_config_stop_bits(dw_uart, 1U);
            break;

        case STOP_BITS_2:
            ret = dw_uart_config_stop_bits(dw_uart, 2U);
            break;

        default:
            LOG_E("unsupported data bits %d\n", cfg->stop_bits);
            ret = -1;
            break;
    }

    if (ret != 0)
    {
        return -RT_ERROR;
    }

    switch (cfg->parity)
    {
        case PARITY_NONE:
            ret = dw_uart_config_parity_none(dw_uart);
            break;

        case PARITY_ODD:
            ret = dw_uart_config_parity_odd(dw_uart);
            break;

        case PARITY_EVEN:
            ret = dw_uart_config_parity_even(dw_uart);
            break;

        default:
            LOG_E("unsupported data bits %d\n", cfg->parity);
            ret = -1;
            break;
    }

    if (ret != 0)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    dw_uart_regs_t *dw_uart = (dw_uart_regs_t *)uart->hw_base;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        if ((size_t)arg == RT_DEVICE_FLAG_INT_RX)
        {
            dw_uart_disable_recv_irq(dw_uart);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        if ((size_t)arg == RT_DEVICE_FLAG_INT_RX)
        {
            dw_uart_enable_recv_irq(dw_uart);
        }
        break;

    default:
        return -1;
    }

    return RT_EOK;
}
static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    dw_uart_regs_t *dw_uart = (dw_uart_regs_t *)uart->hw_base;

    while (!dw_uart_putready(dw_uart));
    dw_uart_putchar(dw_uart, c);

    return 1;
}
static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    dw_uart_regs_t *dw_uart = (dw_uart_regs_t *)uart->hw_base;

    ch = -1;
    if (dw_uart_getready(dw_uart))
    {
        ch = dw_uart_getchar(dw_uart);
    }

    return ch;
}
static const struct rt_uart_ops _uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
};

/* UART device driver structure */
static struct hw_uart_device _uart0_device =
{
    DW_UART0_BASE,
    DW_UART0_IRQn,
};
static struct rt_serial_device _serial0;

int rt_hw_uart_init(void)
{
    struct hw_uart_device *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    uart = &_uart0_device;

    _serial0.ops    = &_uart_ops;
    _serial0.config = config;

    rt_hw_serial_register(&_serial0,
                            RT_CONSOLE_DEVICE_NAME,
                            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                            uart);

    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, &_serial0, RT_CONSOLE_DEVICE_NAME);
    rt_hw_interrupt_umask(uart->irqno);

    return 0;
}