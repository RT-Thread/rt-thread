/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2020-01-14     wangyq        the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_uart.h"
#include <ald_gpio.h>
#include <ald_uart.h>
#include <ald_cmu.h>

#ifdef RT_USING_SERIAL

/* es32 uart driver */
struct es32_uart
{
    uart_handle_t huart;
    IRQn_Type irq;
};

static rt_err_t es32f3x_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    gpio_init_t gpio_initstructure;
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    /* Initialize tx pin */
    gpio_initstructure.mode = GPIO_MODE_OUTPUT;
    gpio_initstructure.odos = GPIO_PUSH_PULL;
    gpio_initstructure.pupd = GPIO_PUSH_UP;
    gpio_initstructure.podrv = GPIO_OUT_DRIVE_1;
    gpio_initstructure.nodrv = GPIO_OUT_DRIVE_1;
    gpio_initstructure.flt  = GPIO_FILTER_DISABLE;
    gpio_initstructure.type = GPIO_TYPE_TTL;

#ifdef BSP_USING_UART0
    gpio_initstructure.func = GPIO_FUNC_3;
    ald_gpio_init(GPIOB, GPIO_PIN_10, &gpio_initstructure);

    /* Initialize rx pin ,the same as txpin except mode */
    gpio_initstructure.mode = GPIO_MODE_INPUT;
    ald_gpio_init(GPIOB, GPIO_PIN_11, &gpio_initstructure);

    ald_cmu_perh_clock_config(CMU_PERH_UART0, ENABLE);
#endif /* uart0 gpio init */

#ifdef BSP_USING_UART1
    gpio_initstructure.func = GPIO_FUNC_3;
    ald_gpio_init(GPIOC, GPIO_PIN_10, &gpio_initstructure);

    /* Initialize rx pin ,the same as txpin except mode */
    gpio_initstructure.mode = GPIO_MODE_INPUT;
    ald_gpio_init(GPIOC, GPIO_PIN_11, &gpio_initstructure);

    ald_cmu_perh_clock_config(CMU_PERH_UART1, ENABLE);
#endif /* uart1 gpio init */

#ifdef BSP_USING_UART2
    gpio_initstructure.func = GPIO_FUNC_5;
    ald_gpio_init(GPIOC, GPIO_PIN_12, &gpio_initstructure);

    /* Initialize rx pin ,the same as txpin except mode */
    gpio_initstructure.mode = GPIO_MODE_INPUT;
    ald_gpio_init(GPIOD, GPIO_PIN_2, &gpio_initstructure);

    ald_cmu_perh_clock_config(CMU_PERH_UART2, ENABLE);
#endif /* uart2 gpio init */

#ifdef BSP_USING_UART3
    gpio_initstructure.func = GPIO_FUNC_4;
    ald_gpio_init(GPIOC, GPIO_PIN_4, &gpio_initstructure);

    /* Initialize rx pin ,the same as txpin except mode */
    gpio_initstructure.mode = GPIO_MODE_INPUT;
    ald_gpio_init(GPIOC, GPIO_PIN_5, &gpio_initstructure);

    ald_cmu_perh_clock_config(CMU_PERH_UART3, ENABLE);
#endif /* uart3 gpio init */

#ifdef BSP_USING_UART4
    gpio_initstructure.func = GPIO_FUNC_3;
    ald_gpio_init(GPIOB, GPIO_PIN_6, &gpio_initstructure);

    /* Initialize rx pin ,the same as txpin except mode */
    gpio_initstructure.mode = GPIO_MODE_INPUT;
    ald_gpio_init(GPIOB, GPIO_PIN_7, &gpio_initstructure);

    ald_cmu_perh_clock_config(CMU_PERH_UART4, ENABLE);
#endif /* uart4 gpio init */

#ifdef BSP_USING_UART5
    gpio_initstructure.func = GPIO_FUNC_4;
    ald_gpio_init(GPIOB, GPIO_PIN_9, &gpio_initstructure);

    /* Initialize rx pin ,the same as txpin except mode */
    gpio_initstructure.mode = GPIO_MODE_INPUT;
    ald_gpio_init(GPIOB, GPIO_PIN_8, &gpio_initstructure);

    ald_cmu_perh_clock_config(CMU_PERH_UART5, ENABLE);
#endif /* uart5 gpio init */

    ald_uart_tx_fifo_config(&uart->huart, UART_TXFIFO_EMPTY);
    ald_uart_rx_fifo_config(&uart->huart, UART_RXFIFO_1BYTE);

    uart->huart.init.mode        = UART_MODE_UART;
    uart->huart.init.baud        = cfg->baud_rate;
    uart->huart.init.word_length = (uart_word_length_t)(8 - cfg->data_bits);
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

    return RT_EOK;
}

static rt_err_t es32f3x_control(struct rt_serial_device *serial, int cmd, void *arg)
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
        ald_uart_interrupt_config(&uart->huart, UART_IT_RFTH, DISABLE);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irq);
        /* enable interrupt */
        ald_uart_interrupt_config(&uart->huart, UART_IT_RFTH, ENABLE);
        break;
    }

    return RT_EOK;
}

static int es32f3x_putc(struct rt_serial_device *serial, char c)
{
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    while (ald_uart_get_status(&uart->huart, UART_STATUS_TFEMPTY) == RESET)
        ;
    WRITE_REG(uart->huart.perh->TXBUF, c);

    return 1;
}

static int es32f3x_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct es32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    if (ald_uart_get_status(&uart->huart, UART_STATUS_RFTH))
    {
        ch = (uint8_t)(uart->huart.perh->RXBUF & 0xFF);
    }

    return ch;
}

static const struct rt_uart_ops es32f3x_uart_ops =
{
    es32f3x_configure,
    es32f3x_control,
    es32f3x_putc,
    es32f3x_getc,
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

    if ((ald_uart_get_mask_flag_status(&uart0.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart0.huart, UART_IF_RFTH);
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

    if ((ald_uart_get_mask_flag_status(&uart1.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart1.huart, UART_IF_RFTH);
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
/* UART2 device driver structure */
struct es32_uart uart2 =
{
    {UART2},
    UART2_IRQn
};

struct rt_serial_device serial2;

void UART2_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart2.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart2.huart, UART_IF_RFTH);
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
/* UART3 device driver structure */
struct es32_uart uart3 =
{
    {UART3},
    UART3_IRQn
};

struct rt_serial_device serial3;

void UART3_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart3.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart3.huart, UART_IF_RFTH);
        rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_UART4
/* UART4 device driver structure */
struct es32_uart uart4 =
{
    {UART4},
    UART4_IRQn
};

struct rt_serial_device serial4;

void UART4_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart4.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart4.huart, UART_IF_RFTH);
        rt_hw_serial_isr(&serial4, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#ifdef BSP_USING_UART5
/* UART5 device driver structure */
struct es32_uart uart5 =
{
    {UART5},
    UART5_IRQn
};

struct rt_serial_device serial5;

void UART5_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart5.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart5.huart, UART_IF_RFTH);
        rt_hw_serial_isr(&serial5, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART5 */

int rt_hw_uart_init(void)
{
    struct es32_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0
    uart = &uart0;
    serial0.ops = &es32f3x_uart_ops;
    serial0.config = config;

    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
    uart = &uart1;
    serial1.ops = &es32f3x_uart_ops;
    serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
    uart = &uart2;
    serial2.ops = &es32f3x_uart_ops;
    serial2.config = config;

    /* register UART2 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
    uart = &uart3;
    serial3.ops = &es32f3x_uart_ops;
    serial3.config = config;

    /* register UART3 device */
    rt_hw_serial_register(&serial3, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_UART4
    uart = &uart4;
    serial4.ops = &es32f3x_uart_ops;
    serial4.config = config;

    /* register UART4 device */
    rt_hw_serial_register(&serial4, "uart4",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART4 */

#ifdef BSP_USING_UART5
    uart = &uart5;
    serial5.ops = &es32f3x_uart_ops;
    serial5.config = config;

    /* register UART5 device */
    rt_hw_serial_register(&serial5, "uart5",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART5 */

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif
