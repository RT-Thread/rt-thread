/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-05     bigmagic     Initial version
 * 2020-10-28     ma           Buadrate & Multi-Port support
 */
/**
 * @addtogroup ls2k
 */
/*@{*/
#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "drv_uart.h"
#define TRUE 1
#define FALSE 0
const struct serial_configure config_uart0 = {
    BAUD_RATE_115200, /* 921600 bits/s */
    DATA_BITS_8,      /* 8 databits */
    STOP_BITS_1,      /* 1 stopbit */
    PARITY_NONE,      /* No parity  */
    BIT_ORDER_LSB,    /* LSB first sent */
    NRZ_NORMAL,       /* Normal mode */
    RT_SERIAL_RB_BUFSZ, /* Buffer size */
    0
};
struct rt_uart_ls2k
{
    void *base;
    rt_uint32_t IRQ;
};
static rt_err_t ls2k_uart_set_buad(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct rt_uart_ls2k *uart_dev = RT_NULL;
    rt_err_t ret = RT_EOK;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart_dev = (struct rt_uart_ls2k *)serial->parent.user_data;
    uint64_t brtc = (125000000U) / (16 * (cfg->baud_rate));
    UART_LCR(uart_dev->base) = 0x80; // Activate buadcfg
    UART_LSB(uart_dev->base) = brtc & 0xff;
    UART_MSB(uart_dev->base) = brtc >> 8;
    if (((((short)UART_MSB(uart_dev->base)) << 8) | UART_LSB(uart_dev->base)) != brtc) ret = -RT_ERROR;
    UART_LCR(uart_dev->base) = CFCR_8BITS; // Back to normal
    UART_MCR(uart_dev->base) = MCR_IENABLE/* | MCR_DTR | MCR_RTS*/;
    UART_IER(uart_dev->base) = 0;
}
static rt_err_t ls2k_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct rt_uart_ls2k *uart_dev = RT_NULL;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    ls2k_uart_set_buad(serial, cfg);
    uart_dev = (struct rt_uart_ls2k *)serial->parent.user_data;
    HWREG8(0xffffffffbfe10428) = 0x1f; // Enable Multi-Port Support, by default it's 0x11 ,which means UART0 & UART4 Controller is in single port mode.
    UART_IER(uart_dev->base) = 0; /* clear interrupt */
    UART_FCR(uart_dev->base) = 0xc1; /* reset UART Rx/Tx */
    /* set databits, stopbits and parity. (8-bit data, 1 stopbit, no parity) */
    UART_LCR(uart_dev->base) = 0x3;
    UART_MCR(uart_dev->base) = 0x3;
    UART_LSR(uart_dev->base) = 0x60;
    UART_MSR(uart_dev->base) = 0xb0;
    return RT_EOK;
}
static rt_err_t ls2k_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct rt_uart_ls2k *uart_dev = RT_NULL;
    RT_ASSERT(serial != RT_NULL);
    uart_dev = (struct rt_uart_ls2k *)serial->parent.user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT: /* Disable RX IRQ */
        rt_hw_interrupt_mask(uart_dev->IRQ);
        break;
    case RT_DEVICE_CTRL_SET_INT: /* Enable RX IRQ */
        rt_hw_interrupt_umask(uart_dev->IRQ);
        UART_IER(uart_dev->base) |= (IER_IRxE | IER_ILE);
        break;
    default:
        break;
    }
    return RT_EOK;
}
static rt_bool_t uart_is_transmit_empty(struct rt_uart_ls2k *uart_dev)
{
    unsigned char status = UART_LSR(uart_dev->base);
    if (status & (UARTLSR_TE | UARTLSR_TFE))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
static int ls2k_uart_putc(struct rt_serial_device *serial, char c)
{
    struct rt_uart_ls2k *uart_dev = RT_NULL;
    RT_ASSERT(serial != RT_NULL);
    uart_dev = (struct rt_uart_ls2k *)serial->parent.user_data;
    while (FALSE == uart_is_transmit_empty(uart_dev))
        ;
    UART_DAT(uart_dev->base) = c;
    return 1;
}
static int ls2k_uart_getc(struct rt_serial_device *serial)
{
    struct rt_uart_ls2k *uart_dev = RT_NULL;
    RT_ASSERT(serial != RT_NULL);
    uart_dev = (struct rt_uart_ls2k *)serial->parent.user_data;
    if (LSR_RXRDY & UART_LSR(uart_dev->base))
    {
        return UART_DAT(uart_dev->base);
    }
    return -1;
}
/* UART interrupt handler */
static void uart_irq_handler(int vector, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    struct rt_uart_ls2k *uart_dev = RT_NULL;
    RT_ASSERT(serial != RT_NULL);
    uart_dev = (struct rt_uart_ls2k *)serial->parent.user_data;
    unsigned char iir = UART_IIR(uart_dev->base);
    /* Find out interrupt reason */
    if ((IIR_RXTOUT & iir) || (IIR_RXRDY & iir))
    {
        rt_interrupt_enter();
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        rt_interrupt_leave();
    }
}
static const struct rt_uart_ops ls2k_uart_ops =
{
    ls2k_uart_configure,
    ls2k_uart_control,
    ls2k_uart_putc,
    ls2k_uart_getc,
};
struct rt_uart_ls2k uart_dev0 =
{
    (void *)UARTx_BASE(0),
    LS2K_UART_0_1_2_3_IRQ,
};
struct rt_uart_ls2k uart_dev4 =
{
    (void *)UARTx_BASE(4),
    LS2K_UART_4_5_6_7_IRQ,
};

struct rt_serial_device serial, serial4;

void rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART0
    struct rt_uart_ls2k *uart0;
    uart0 = &uart_dev0;
    serial.ops    = &ls2k_uart_ops;
    serial.config = config_uart0;

    rt_hw_interrupt_install(uart0->IRQ, uart_irq_handler, &serial, "UART0");
    /* register UART device */
    rt_hw_serial_register(&serial,
                          "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart0);
#endif

#ifdef RT_USING_UART4
    struct rt_uart_ls2k *uart4;
    uart4 = &uart_dev4;
    serial4.ops = &ls2k_uart_ops;
    serial4.config = config;
    rt_hw_interrupt_install(uart4->IRQ, uart_irq_handler, &serial4, "UART4");
    rt_hw_serial_register(&serial4,
                          "uart4",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &uart_dev4);
#endif
}
/*@}*/
