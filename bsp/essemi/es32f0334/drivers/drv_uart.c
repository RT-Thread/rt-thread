/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-03-01     wangyq        the first version
 * 2019-11-01     wangyq        update libraries
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_uart.h"
#include <ald_gpio.h>
#include <ald_uart.h>

#ifdef RT_USING_SERIAL

/* es32 uart driver */
struct es32_uart
{
    uart_handle_t huart;
    IRQn_Type irq;
};

static rt_err_t es32f0x_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    gpio_init_t gpio_init_initstructure;
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    /* Initialize tx pin */
    gpio_init_initstructure.mode = GPIO_MODE_OUTPUT;
    gpio_init_initstructure.odos = GPIO_PUSH_PULL;
    gpio_init_initstructure.pupd = GPIO_PUSH_UP;
    gpio_init_initstructure.odrv = GPIO_OUT_DRIVE_NORMAL;
    gpio_init_initstructure.flt  = GPIO_FILTER_DISABLE;
    gpio_init_initstructure.type = GPIO_TYPE_TTL;

#ifdef BSP_USING_UART0
    gpio_init_initstructure.func = GPIO_FUNC_3;
    ald_gpio_init(GPIOB, GPIO_PIN_10, &gpio_init_initstructure);

    /* Initialize rx pin ,the same as txpin except mode */
    gpio_init_initstructure.mode = GPIO_MODE_INPUT;
    ald_gpio_init(GPIOB, GPIO_PIN_11, &gpio_init_initstructure);
#endif

#ifdef BSP_USING_UART1
    /* Initialize tx pin */
    gpio_init_initstructure.func = GPIO_FUNC_3;
    ald_gpio_init(GPIOC, GPIO_PIN_10, &gpio_init_initstructure);

    /* Initialize rx pin ,the same as txpin except mode*/
    gpio_init_initstructure.mode = GPIO_MODE_INPUT;
    ald_gpio_init(GPIOC, GPIO_PIN_11, &gpio_init_initstructure);
#endif

    uart->huart.init.mode        = UART_MODE_UART;
    uart->huart.init.baud        = cfg->baud_rate;
    uart->huart.init.word_length = (uart_word_length_t)(cfg->data_bits - 5);
    uart->huart.init.parity = (uart_parity_t)(cfg->parity == PARITY_EVEN ? UART_PARITY_EVEN : cfg->parity);
    uart->huart.init.fctl        = UART_HW_FLOW_CTL_DISABLE;
    ald_uart_init(&uart->huart);

    if (cfg->bit_order == BIT_ORDER_MSB)
    {
        UART_MSB_FIRST_ENABLE(&uart->huart);
    }
    else
    {
        UART_MSB_FIRST_DISABLE(&uart->huart);
    }

    if (cfg->invert == NRZ_INVERTED)
    {
        UART_DATA_INV_ENABLE(&uart->huart);
    }
    else
    {
        UART_DATA_INV_DISABLE(&uart->huart);
    }

    /* enable rx int */
    ald_uart_interrupt_config(&uart->huart, UART_IT_RXRD, ENABLE);

    return RT_EOK;
}

static rt_err_t es32f0x_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = (struct es32_uart *)serial->parent.user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irq);
        /* disable interrupt */
        ald_uart_interrupt_config(&uart->huart, UART_IT_RXRD, DISABLE);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irq);
        /* enable interrupt */
        ald_uart_interrupt_config(&uart->huart, UART_IT_RXRD, ENABLE);
        break;
    }

    return RT_EOK;
}

static int es32f0x_putc(struct rt_serial_device *serial, char c)
{
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    while (!(uart->huart.perh->SR & 0x40)) ;
    WRITE_REG(uart->huart.perh->TBR, c);

    return 1;
}

static int es32f0x_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct es32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    if (uart->huart.perh->SR & 0x01)
    {
        ch = (uint8_t)(uart->huart.perh->RBR & 0xFF);
    }

    return ch;
}

static const struct rt_uart_ops es32f0x_uart_ops =
{
    es32f0x_configure,
    es32f0x_control,
    es32f0x_putc,
    es32f0x_getc,
};

#ifdef BSP_USING_UART0
/* UART0 device driver structure */
struct es32_uart uart0 =
{
    {UART0},
    UART0_IRQn
};

struct rt_serial_device serial0;

void UART0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART0->RIF & 0x01)
    {
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
/* UART1 device driver structure */
struct es32_uart uart1 =
{
    {UART1},
    UART1_IRQn
};

struct rt_serial_device serial1;

void UART1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART1->RIF & 0x01)
    {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

int rt_hw_uart_init(void)
{
    struct es32_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0
    uart = &uart0;
    serial0.ops = &es32f0x_uart_ops;
    serial0.config = config;

    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
    uart = &uart1;
    serial1.ops = &es32f0x_uart_ops;
    serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART1 */

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif
