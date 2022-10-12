/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-08     zhuangwei    the first version
 * 2021-02-02     michael5hzg@gmail.com    adapt to ls1b
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "drv_uart.h"
#include "ls1b_pin.h"
#include "ls1b_uart.h"

/* STM32 uart driver */
struct rt_uart_ls1b
{
    ls1b_uart_t UARTx;
    rt_uint32_t IRQ;
};

static rt_err_t ls1b_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct rt_uart_ls1b *uart_dev = RT_NULL;
    ls1b_uart_info_t uart_info = {0};

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart_dev = (struct rt_uart_ls1b *)serial->parent.user_data;

    // 初始化串口
    uart_info.UARTx    = uart_dev->UARTx;
    uart_info.baudrate = cfg->baud_rate;
    uart_info.rx_enable = TRUE;
    uart_init(&uart_info);

    return RT_EOK;

}

static rt_err_t ls1b_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct rt_uart_ls1b *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);
    uart_dev = (struct rt_uart_ls1b *)serial->parent.user_data;

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

static int ls1b_uart_putc(struct rt_serial_device *serial, char c)
{
    struct rt_uart_ls1b *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);

    uart_dev = (struct rt_uart_ls1b *)serial->parent.user_data;
    uart_putc(uart_dev->UARTx, c);

    return 1;
}

static int ls1b_uart_getc(struct rt_serial_device *serial)
{
    struct rt_uart_ls1b *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);

    uart_dev = (struct rt_uart_ls1b *)serial->parent.user_data;
    void *uart_base = uart_get_base(uart_dev->UARTx);

    if (LSR_RXRDY & reg_read_8(uart_base + LS1B_UART_LSR_OFFSET))
    {
        return reg_read_8(uart_base + LS1B_UART_DAT_OFFSET);
    }

    return -1;
}

/* UART interrupt handler */
static void uart_irq_handler(int vector, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    struct rt_uart_ls1b *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);

    uart_dev = (struct rt_uart_ls1b *)serial->parent.user_data;
    void *uart_base = uart_get_base(uart_dev->UARTx);
    unsigned char iir = reg_read_8(uart_base + LS1B_UART_IIR_OFFSET);

    // 判断是否为接收超时或接收到有效数据
    if ((IIR_RXTOUT & iir) || (IIR_RXRDY & iir))
    {
        rt_interrupt_enter();
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        rt_interrupt_leave();
    }

}

static const struct rt_uart_ops ls1b_uart_ops =
{
    ls1b_uart_configure,
    ls1b_uart_control,
    ls1b_uart_putc,
    ls1b_uart_getc,
};


#if defined(RT_USING_UART1)
struct rt_uart_ls1b uart1 =
{
    LS1B_UART1,
    LS1B_UART1_IRQ,
};
struct rt_serial_device serial1;
#endif /* RT_USING_UART1 */

#if defined(RT_USING_UART2)
struct rt_uart_ls1b uart2 =
{
    LS1B_UART2,
    LS1B_UART2_IRQ,
};
struct rt_serial_device serial2;
#endif /* RT_USING_UART2 */


#if defined(RT_USING_UART3)
struct rt_uart_ls1b uart3 =
{
    LS1B_UART3,
    LS1B_UART3_IRQ,
};
struct rt_serial_device serial3;
#endif /* RT_USING_UART3 */

#if defined(RT_USING_UART4)
struct rt_uart_ls1b uart4 =
{
    LS1B_UART4,
    LS1B_UART4_IRQ,
};
struct rt_serial_device serial4;
#endif /* RT_USING_UART4 */

#if defined(RT_USING_UART5)
struct rt_uart_ls1b uart5 =
{
    LS1B_UART5,
    LS1B_UART5_IRQ,
};
struct rt_serial_device serial5;
#endif /* RT_USING_UART5 */



void rt_hw_uart_init(void)
{
    struct rt_uart_ls1b *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART5
        uart = &uart5;

        serial5.ops    = &ls1b_uart_ops;
        serial5.config = config;

        rt_hw_interrupt_install(uart->IRQ, uart_irq_handler, &serial5, "UART5");

        /* register UART5 device */
        rt_hw_serial_register(&serial5,
                              "uart5",
                              //RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_RX,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
#endif /* RT_USING_UART5 */


#ifdef RT_USING_UART2
    uart = &uart2;

    serial2.ops    = &ls1b_uart_ops;
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

}

