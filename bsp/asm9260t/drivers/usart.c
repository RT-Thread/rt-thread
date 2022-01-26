/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety       first version
 * 2013-07-21     weety       using serial component
 * 2015-05-02     ArdaFu      Port from AT91SAM9260 BSP
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include "interrupt.h"
#include <asm9260t.h>
#include "gpio.h"

#include "uart.h"

typedef struct
{
    HW_USART_TypeDef *port;
    int irq;
} asm_uart_t;


/**
 * This function will handle serial
 */
void rt_asm_usart_handler(int vector, void *param)
{
    rt_uint32_t status;
    asm_uart_t *uart;
    rt_device_t dev = (rt_device_t)param;
    uart = (asm_uart_t *)dev->user_data;
    status = uart->port->INTR[R_VAL];

    if(!(status & (ASM_UART_INTR_RXIS | ASM_UART_INTR_RTIS)))
        return;
    uart->port->INTR[R_CLR] = ASM_UART_INTR_RXIS|ASM_UART_INTR_RTIS;
    //rt_interrupt_enter();
    rt_hw_serial_isr((struct rt_serial_device *)dev, RT_SERIAL_EVENT_RX_IND);
    //rt_interrupt_leave();

}


/**
* UART device in RT-Thread
*/
static rt_err_t asm_usart_configure(struct rt_serial_device *serial,
                                    struct serial_configure *cfg)
{
    asm_uart_t *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (asm_uart_t *)serial->parent.user_data;

    Hw_UartDisable(uart->port);

    Hw_UartReset(uart->port);

    Hw_UartConfig(uart->port, cfg->baud_rate, cfg->data_bits,
                  cfg->stop_bits, cfg->parity);

    Hw_UartEnable(uart->port);

    return RT_EOK;
}

static rt_err_t asm_usart_control(struct rt_serial_device *serial,
                                  int cmd, void *arg)
{
    asm_uart_t* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (asm_uart_t *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        rt_hw_interrupt_mask(uart->irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        rt_hw_interrupt_umask(uart->irq);
        break;
    }

    return RT_EOK;
}


static int asm_usart_putc(struct rt_serial_device *serial, char c)
{
    //rt_uint32_t level;
    asm_uart_t *uart = serial->parent.user_data;

    while ((uart->port->STAT[R_VAL] & ASM_UART_STAT_TXFF));
    uart->port->DATA[R_VAL] = c;

    return 1;
}

static int asm_usart_getc(struct rt_serial_device *serial)
{
    asm_uart_t *uart = serial->parent.user_data;

    if (uart->port->STAT[R_VAL] & ASM_UART_STAT_RXFE)
        return -1;
    return  uart->port->DATA[R_VAL] & 0xff;
}

static const struct rt_uart_ops asm_usart_ops =
{
    asm_usart_configure,
    asm_usart_control,
    asm_usart_putc,
    asm_usart_getc,
};


#if defined(RT_USING_UART0)
static struct rt_serial_device serial0;
asm_uart_t uart0 =
{
    USART0,
    INT_UART0
};
#endif

#if defined(RT_USING_UART3)
static struct rt_serial_device serial3;
asm_uart_t uart3 =
{
    USART3,
    INT_UART3
};
#endif

#if defined(RT_USING_UART4)
static struct rt_serial_device serial4;
asm_uart_t uart4 =
{
    USART4,
    INT_UART4
};
#endif

//USART0 PINS TX=GP14_0:5 , RX=GP14_1:5
//USART3 PINS TX=GP8_6:2 , RX=GP8_7:2
//USART4 PINS TX=GP3_0:2 , RX=GP3_1:2

void asm_usart_gpio_init(void)
{
    // enable IOCONFIG GPIO
    outl(((1UL<<25) | (1UL<<4)) ,REG_SET(HW_AHBCLKCTRL0));
#ifdef RT_USING_UART0
    HW_SetPinMux(14, 0, 5);
    HW_SetPinMux(14, 1, 5);
#endif

#ifdef RT_USING_UART3
    HW_SetPinMux(8, 6, 2);
    HW_SetPinMux(8, 7, 2);
#endif

#ifdef RT_USING_UART4
    HW_SetPinMux(3, 0, 2);
    HW_SetPinMux(3, 1, 2);
#endif
}

void asm_serial_config_set_default(struct rt_serial_device* serial)
{
    serial->ops = &asm_usart_ops;

    serial->config.baud_rate = BAUD_RATE_115200;
    serial->config.bit_order = BIT_ORDER_LSB;
    serial->config.data_bits = DATA_BITS_8;
    serial->config.parity    = PARITY_NONE;
    serial->config.stop_bits = STOP_BITS_1;
    serial->config.invert    = NRZ_NORMAL;
    serial->config.bufsz     = RT_SERIAL_RB_BUFSZ;
}
#define DRV_REG_OPS (RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM)
/**
 * This function will handle init uart
 */
int rt_hw_uart_init(void)
{
    asm_usart_gpio_init();

#if defined(RT_USING_UART0)
    Hw_UartInit(0);
    asm_serial_config_set_default(&serial0);

    /* register uart device */
    rt_hw_serial_register(&serial0, "uart0", DRV_REG_OPS, &uart0);
    rt_hw_interrupt_install(uart0.irq, rt_asm_usart_handler,
                            (void *)&(serial0.parent), "UART0");
    rt_hw_interrupt_umask(uart0.irq);
#endif

#if defined(RT_USING_UART3)
    Hw_UartInit(3);
    asm_serial_config_set_default(&serial3);

    /* register uart device */
    rt_hw_serial_register(&serial3, "uart3",  DRV_REG_OPS, &uart3);
    rt_hw_interrupt_install(uart3.irq, rt_asm_usart_handler,
                            (void *)&(serial3.parent), "UART3");
    rt_hw_interrupt_umask(uart3.irq);
#endif

#if defined(RT_USING_UART4)
    Hw_UartInit(4);
    asm_serial_config_set_default(&serial4);

    /* register uart device */
    rt_hw_serial_register(&serial4, "uart4", DRV_REG_OPS, &uart4);
    rt_hw_interrupt_install(uart4.irq, rt_asm_usart_handler,
                            (void *)&(serial4.parent), "UART4");
    rt_hw_interrupt_umask(uart4.irq);
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
