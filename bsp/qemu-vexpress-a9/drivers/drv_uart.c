/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2013-03-30   Bernard     the first version
 * 2025-04-08   Hydevcode   second version
 *
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>

#include "drv_uart.h"
#include "board.h"
#include "mmu.h"


#ifdef RT_USING_SERIAL_V1

struct hw_uart_device
{
    rt_uint32_t hw_base;
    rt_uint32_t irqno;
    struct rt_serial_device *serial;
    char *device_name;
};

#define UART_DR(base)   __REG32(base + 0x00)
#define UART_FR(base)   __REG32(base + 0x18)
#define UART_CR(base)   __REG32(base + 0x30)
#define UART_IMSC(base) __REG32(base + 0x38)
#define UART_ICR(base)  __REG32(base + 0x44)

#define UARTFR_RXFE     0x10
#define UARTFR_TXFF     0x20
#define UARTIMSC_RXIM   0x10
#define UARTIMSC_TXIM   0x20
#define UARTICR_RXIC    0x10
#define UARTICR_TXIC    0x20

#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;
#endif

#if defined(BSP_USING_UART1)
struct rt_serial_device serial1;
#endif

#if defined(BSP_USING_UART2)
struct rt_serial_device serial2;
#endif


#if defined(BSP_USING_UART3)
struct rt_serial_device serial3;
#endif

static struct hw_uart_device _uart_device[] = {
#if defined(BSP_USING_UART0)
{
    REALVIEW_UART0_BASE,
    IRQ_PBA8_UART0,
    &serial0,
    "uart0",
},
#endif

#if defined(BSP_USING_UART1)
{
    REALVIEW_UART1_BASE,
    IRQ_PBA8_UART1,
    &serial1,
    "uart1",
},
#endif

#if defined(BSP_USING_UART2)
{
    REALVIEW_UART2_BASE,
    IRQ_PBA8_UART2,
    &serial2,
    "uart2",
},
#endif

#if defined(BSP_USING_UART3)
{
    REALVIEW_UART3_BASE,
    IRQ_PBA8_UART3,
    &serial3,
    "uart3",
},
#endif

};

/**
 * @brief UART common interrupt process. This
 *
 * @param serial Serial device
 */
static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct hw_uart_device *)serial->parent.user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT:
            /* disable rx irq */
        UART_IMSC(uart->hw_base) &= ~UARTIMSC_RXIM;
            break;

        case RT_DEVICE_CTRL_SET_INT:
            /* enable rx irq */
            UART_IMSC(uart->hw_base) |= UARTIMSC_RXIM;
            rt_hw_interrupt_umask(uart->irqno);
            break;
    }

    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char ch)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    while (UART_FR(uart->hw_base) & UARTFR_TXFF);
    UART_DR(uart->hw_base) = ch;

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    ch = -1;
    if (!(UART_FR(uart->hw_base) & UARTFR_RXFE))
    {
        ch = UART_DR(uart->hw_base) & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops _uart_ops = {
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
};

int rt_hw_uart_init(void)
{

    rt_err_t err = RT_EOK;

    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    for (uint32_t i = 0; i < sizeof(_uart_device) / sizeof(_uart_device[0]); i++)
    {

        #ifdef RT_USING_SMART
            _uart_device[i].hw_base = (uint32_t)rt_ioremap((void*)_uart_device[i].hw_base, 0x1000);
        #endif

        _uart_device[i].serial->ops = &_uart_ops;
        _uart_device[i].serial->config = config;

        /* register UART device */
        err = rt_hw_serial_register(_uart_device[i].serial,
                            _uart_device[i].device_name,
                            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                            (void*)&_uart_device[i]);
        rt_hw_interrupt_install(_uart_device[i].irqno, rt_hw_uart_isr, _uart_device[i].serial, _uart_device[i].device_name);
        /* enable Rx and Tx of UART */
        UART_CR(_uart_device[i].hw_base) = (1 << 0) | (1 << 8) | (1 << 9);
    }

    return err;
}

INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* RT_USING_SERIAL */