/*
 * File      : drv_usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtdevice.h>

#include <encoding.h>
#include <platform.h>
#include <interrupt.h>

static void usart_handler(int vector, void *param)
{
    rt_hw_serial_isr((struct rt_serial_device *)param, RT_SERIAL_EVENT_RX_IND);
}

static rt_err_t usart_configure(struct rt_serial_device *serial,
                                struct serial_configure *cfg)
{
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    GPIO_REG(GPIO_IOF_SEL) &= ~IOF0_UART0_MASK;
    GPIO_REG(GPIO_IOF_EN) |= IOF0_UART0_MASK;

    UART0_REG(UART_REG_DIV) = get_cpu_freq() / cfg->baud_rate - 1;
    UART0_REG(UART_REG_TXCTRL) |= UART_TXEN;
    UART0_REG(UART_REG_RXCTRL) |= UART_RXEN;
    UART0_REG(UART_REG_IE) = UART_IP_RXWM;

    return RT_EOK;
}

static rt_err_t usart_control(struct rt_serial_device *serial,
                              int cmd, void *arg)
{
    RT_ASSERT(serial != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        break;
    case RT_DEVICE_CTRL_SET_INT:
        break;
    }

    return RT_EOK;
}

static int usart_putc(struct rt_serial_device *serial, char c)
{
    while (UART0_REG(UART_REG_TXFIFO) & 0x80000000) ;
    UART0_REG(UART_REG_TXFIFO) = c;

    return 0;
}

static int usart_getc(struct rt_serial_device *serial)
{
    rt_int32_t val = UART0_REG(UART_REG_RXFIFO);
    if (val > 0)
        return (rt_uint8_t)val;
    else
        return -1;
}

static struct rt_uart_ops ops =
{
    usart_configure,
    usart_control,
    usart_putc,
    usart_getc,
};

static struct rt_serial_device serial =
{
    .ops = &ops,
    .config.baud_rate = BAUD_RATE_115200,
    .config.bit_order = BIT_ORDER_LSB,
    .config.data_bits = DATA_BITS_8,
    .config.parity    = PARITY_NONE,
    .config.stop_bits = STOP_BITS_1,
    .config.invert    = NRZ_NORMAL,
    .config.bufsz     = RT_SERIAL_RB_BUFSZ,
};

int rt_hw_uart_init(void)
{
    rt_hw_serial_register(
        &serial,
        "dusart",
        RT_DEVICE_FLAG_STREAM
        | RT_DEVICE_FLAG_RDWR
        | RT_DEVICE_FLAG_INT_RX, RT_NULL);

    rt_hw_interrupt_install(
        INT_UART0_BASE,
        usart_handler,
        (void *) & (serial.parent),
        "uart interrupt");

    rt_hw_interrupt_unmask(INT_UART0_BASE);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

