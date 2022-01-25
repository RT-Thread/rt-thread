/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      first implementation
 */

#include <rtthread.h>

#ifdef RT_USING_CONSOLE

#include <rthw.h>
#include <rtdevice.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "board.h"
#include "soc.h"
#include "ck_usart.h"
#include "drv_usart.h"
#include "pin_name.h"



__attribute__((isr)) void ck_usart0_irqhandler(void);

struct
{
    uint32_t base;
    uint32_t irq;
    void *handler;
}
const sg_usart_config[CONFIG_USART_NUM] =
{
    {CSKY_UART_BASE, UART_IRQn, ck_usart0_irqhandler},
};


int32_t target_usart_init(int32_t idx, uint32_t *base, uint32_t *irq, void **handler)
{
    if (idx >= CONFIG_USART_NUM)
    {
        return -1;
    }

    if (base != NULL)
    {
        *base = sg_usart_config[idx].base;
    }

    if (irq != NULL)
    {
        *irq = sg_usart_config[idx].irq;
    }

    if (handler != NULL)
    {
        *handler = sg_usart_config[idx].handler;
    }

    return idx;
}


#ifdef RT_USING_UART1
#define UART_TXD1     PA10_TXD1_PWM1_XX_SIROUT1
#define UART_RXD1     PA11_RXD1_PWM2_XX_SIRIN1

static  usart_handle_t uart1_handle;
static struct rt_serial_device  serial1;

__attribute__((isr)) void ck_usart0_irqhandler(void)
{
    rt_hw_serial_isr(&serial1,RT_SERIAL_EVENT_RX_IND);
}
#endif

/*
 * UART interface
 */
static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    int ret;
    usart_handle_t uart;

    uint32_t bauds;
    usart_mode_e mode;
    usart_parity_e parity;
    usart_stop_bits_e stopbits;
    usart_data_bits_e databits;

    RT_ASSERT(serial != RT_NULL);
    uart = (usart_handle_t)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    /* set baudrate parity...*/
    bauds = cfg->baud_rate;
    mode = USART_MODE_ASYNCHRONOUS;

    if (cfg->parity == PARITY_EVEN)
        parity = USART_PARITY_EVEN;
    else if (cfg->parity == PARITY_ODD)
        parity = USART_PARITY_ODD;
    else
        parity = USART_PARITY_NONE;

    stopbits = USART_STOP_BITS_1 ;
    databits = USART_DATA_BITS_8;

    ret = csi_usart_config(uart, bauds, USART_MODE_ASYNCHRONOUS, parity, stopbits, databits);

    if (ret < 0)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    usart_handle_t uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (usart_handle_t)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable the UART Interrupt */
        ck_usart_clr_int_flag(uart,IER_RDA_INT_ENABLE);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* Enable the UART Interrupt */
        ck_usart_set_int_flag(uart,IER_RDA_INT_ENABLE);
        break;
    }

    return (RT_EOK);
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    usart_handle_t uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (usart_handle_t)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);
    csi_usart_putchar(uart,c);

    return (1);
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    usart_handle_t uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (usart_handle_t)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);


    ch = csi_uart_getchar(uart);

    return ch;
}

const struct rt_uart_ops _uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
};


int rt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART1
    serial1.ops                 = & _uart_ops;
    serial1.config              = config;
    serial1.config.bufsz        = 2048;
    serial1.config.baud_rate    = 115200;

    uart1_handle = csi_usart_initialize(0, NULL);

    rt_hw_serial_register(&serial1,
                          "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart1_handle);
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);
#endif
