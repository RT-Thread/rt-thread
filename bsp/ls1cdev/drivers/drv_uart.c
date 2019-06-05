/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-08     zhuangwei    the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "drv_uart.h"
#include "ls1c_pin.h"
#include "ls1c_uart.h"

/* STM32 uart driver */
struct rt_uart_ls1c
{
    ls1c_uart_t UARTx;
    rt_uint32_t IRQ;
};

static rt_err_t ls1c_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct rt_uart_ls1c *uart_dev = RT_NULL;
    ls1c_uart_info_t uart_info = {0};

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart_dev = (struct rt_uart_ls1c *)serial->parent.user_data;

    // 初始化串口
    uart_info.UARTx    = uart_dev->UARTx;
    uart_info.baudrate = cfg->baud_rate;
    uart_info.rx_enable = TRUE;
    uart_init(&uart_info);

    return RT_EOK;

}

static rt_err_t ls1c_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct rt_uart_ls1c *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);
    uart_dev = (struct rt_uart_ls1c *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT: /* disable rx irq */
        rt_hw_interrupt_mask(uart_dev->IRQ);
        break;

    case RT_DEVICE_CTRL_SET_INT: /* enable rx irq */
        rt_hw_interrupt_umask(uart_dev->IRQ);
        break;

    default:
        break;
    }

    return RT_EOK;

}

static int ls1c_uart_putc(struct rt_serial_device *serial, char c)
{
    struct rt_uart_ls1c *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);

    uart_dev = (struct rt_uart_ls1c *)serial->parent.user_data;
    uart_putc(uart_dev->UARTx, c);

    return 1;
}

static int ls1c_uart_getc(struct rt_serial_device *serial)
{
    struct rt_uart_ls1c *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);

    uart_dev = (struct rt_uart_ls1c *)serial->parent.user_data;
    void *uart_base = uart_get_base(uart_dev->UARTx);

    if (LSR_RXRDY & reg_read_8(uart_base + LS1C_UART_LSR_OFFSET))
    {
        return reg_read_8(uart_base + LS1C_UART_DAT_OFFSET);
    }

    return -1;
}

/* UART interrupt handler */
static void uart_irq_handler(int vector, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    struct rt_uart_ls1c *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);

    uart_dev = (struct rt_uart_ls1c *)serial->parent.user_data;
    void *uart_base = uart_get_base(uart_dev->UARTx);
    unsigned char iir = reg_read_8(uart_base + LS1C_UART_IIR_OFFSET);

    // 判断是否为接收超时或接收到有效数据
    if ((IIR_RXTOUT & iir) || (IIR_RXRDY & iir))
    {
        rt_interrupt_enter();
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        rt_interrupt_leave();
    }

}

static const struct rt_uart_ops ls1c_uart_ops =
{
    ls1c_uart_configure,
    ls1c_uart_control,
    ls1c_uart_putc,
    ls1c_uart_getc,
};

#if defined(RT_USING_UART2)
struct rt_uart_ls1c uart2 =
{
    LS1C_UART2,
    LS1C_UART2_IRQ,
};
struct rt_serial_device serial2;
#endif /* RT_USING_UART2 */

#if defined(RT_USING_UART1)
struct rt_uart_ls1c uart1 =
{
    LS1C_UART1,
    LS1C_UART1_IRQ,
};
struct rt_serial_device serial1;
#endif /* RT_USING_UART1 */

#if defined(RT_USING_UART3)
struct rt_uart_ls1c uart3 =
{
    LS1C_UART3,
    LS1C_UART3_IRQ,
};
struct rt_serial_device serial3;
#endif /* RT_USING_UART3 */

void rt_hw_uart_init(void)
{
    struct rt_uart_ls1c *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART2
    uart = &uart2;

    serial2.ops    = &ls1c_uart_ops;
    serial2.config = config;

    pin_set_purpose(36, PIN_PURPOSE_OTHER);
    pin_set_purpose(37, PIN_PURPOSE_OTHER);
    pin_set_remap(36, PIN_REMAP_SECOND);
    pin_set_remap(37, PIN_REMAP_SECOND);

    rt_hw_interrupt_install(uart->IRQ, uart_irq_handler, &serial2, "UART2");

    /* register UART2 device */
    rt_hw_serial_register(&serial2,
                          "uart2",
                          //RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_RX,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART2 */

#ifdef RT_USING_UART1
    uart = &uart1;

    serial1.ops    = &ls1c_uart_ops;
    serial1.config = config;

    pin_set_purpose(2, PIN_PURPOSE_OTHER);
    pin_set_purpose(3, PIN_PURPOSE_OTHER);
    pin_set_remap(2, PIN_REMAP_FOURTH);
    pin_set_remap(3, PIN_REMAP_FOURTH);

    rt_hw_interrupt_install(uart->IRQ, uart_irq_handler, &serial1, "UART1");

    /* register UART1 device */
    rt_hw_serial_register(&serial1,
                          "uart1",
                          //RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_RX,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART1 */

#ifdef RT_USING_UART3
    uart = &uart3;

    serial3.ops    = &ls1c_uart_ops;
    serial3.config = config;

    pin_set_purpose(0, PIN_PURPOSE_OTHER);
    pin_set_purpose(1, PIN_PURPOSE_OTHER);
    pin_set_remap(0, PIN_REMAP_FOURTH);
    pin_set_remap(1, PIN_REMAP_FOURTH);

    rt_hw_interrupt_install(uart->IRQ, uart_irq_handler, &serial3, "UART3");

    /* register UART1 device */
    rt_hw_serial_register(&serial3,
                          "uart3",
                          //RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_RX,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART3 */

}

