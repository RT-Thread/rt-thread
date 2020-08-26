/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-07-12     wangyq        the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_uart.h"
#include <lib_gpio.h>
#include <lib_uart.h>

#ifdef RT_USING_SERIAL

/* es8p uart driver */
struct es8p_uart
{
    UART_TypeDef *huart;
    IRQn_Type irq;
};

static rt_err_t es8px_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    GPIO_InitStruType gpio_initstruct;
    UART_InitStruType uart_initstruct;
    struct es8p_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct es8p_uart *)serial->parent.user_data;

    gpio_initstruct.GPIO_Signal = GPIO_Pin_Signal_Digital;
    gpio_initstruct.GPIO_OD = GPIO_ODE_Output_Disable;
    gpio_initstruct.GPIO_PUEN = GPIO_PUE_Input_Enable;
    gpio_initstruct.GPIO_PDEN = GPIO_PDE_Input_Disable;
    gpio_initstruct.GPIO_DS = GPIO_DS_Output_Normal;

#ifdef BSP_USING_UART0
    gpio_initstruct.GPIO_Func = GPIO_Func_2;
    /* Initialize rx pin */
    gpio_initstruct.GPIO_Direction = GPIO_Dir_In;
    GPIO_Init(GPIOB, GPIO_Pin_0, &gpio_initstruct);
    /* Initialize tx pin ,the same as rx pin except mode */
    gpio_initstruct.GPIO_Direction = GPIO_Dir_Out;
    GPIO_Init(GPIOB, GPIO_Pin_1, &gpio_initstruct);
#endif

#ifdef BSP_USING_UART1
    gpio_initstruct.GPIO_Func = GPIO_Func_1;
    /* Initialize rx pin */
    gpio_initstruct.GPIO_Direction = GPIO_Dir_In;
    GPIO_Init(GPIOA, GPIO_Pin_18, &gpio_initstruct);
    /* Initialize tx pin ,the same as rx pin except mode */
    gpio_initstruct.GPIO_Direction = GPIO_Dir_Out;
    GPIO_Init(GPIOA, GPIO_Pin_17, &gpio_initstruct);
#endif

#ifdef BSP_USING_UART2
    gpio_initstruct.GPIO_Func = GPIO_Func_2;
    /* Initialize rx pin */
    gpio_initstruct.GPIO_Direction = GPIO_Dir_In;
    GPIO_Init(GPIOA, GPIO_Pin_4, &gpio_initstruct);
    /* Initialize tx pin ,the same as rx pin except mode */
    gpio_initstruct.GPIO_Direction = GPIO_Dir_Out;
    GPIO_Init(GPIOA, GPIO_Pin_5, &gpio_initstruct);
#endif

#ifdef BSP_USING_UART3
    gpio_initstruct.GPIO_Func = GPIO_Func_2;
    /* Initialize rx pin */
    gpio_initstruct.GPIO_Direction = GPIO_Dir_In;
    GPIO_Init(GPIOA, GPIO_Pin_30, &gpio_initstruct);
    /* Initialize tx pin ,the same as rx pin except mode */
    gpio_initstruct.GPIO_Direction = GPIO_Dir_Out;
    GPIO_Init(GPIOA, GPIO_Pin_29, &gpio_initstruct);
#endif

#ifdef BSP_USING_UART4
    gpio_initstruct.GPIO_Func = GPIO_Func_1;
    /* Initialize rx pin */
    gpio_initstruct.GPIO_Direction = GPIO_Dir_In;
    GPIO_Init(GPIOB, GPIO_Pin_10, &gpio_initstruct);
    /* Initialize tx pin ,the same as rx pin except mode */
    gpio_initstruct.GPIO_Direction = GPIO_Dir_Out;
    GPIO_Init(GPIOB, GPIO_Pin_11, &gpio_initstruct);
#endif

#ifdef BSP_USING_UART5
    gpio_initstruct.GPIO_Func = GPIO_Func_1;
    /* Initialize rx pin */
    gpio_initstruct.GPIO_Direction = GPIO_Dir_In;
    GPIO_Init(GPIOB, GPIO_Pin_12, &gpio_initstruct);
    /* Initialize tx pin ,the same as rx pin except mode */
    gpio_initstruct.GPIO_Direction = GPIO_Dir_Out;
    GPIO_Init(GPIOB, GPIO_Pin_13, &gpio_initstruct);
#endif

    uart_initstruct.UART_ClockSet = UART_Clock_1;
    uart_initstruct.UART_BaudRate = cfg->baud_rate;
    uart_initstruct.UART_RxPolar = UART_Polar_Normal;
    uart_initstruct.UART_TxPolar = UART_Polar_Normal;

    if (cfg->data_bits == DATA_BITS_7)
    {
        uart_initstruct.UART_RxMode = UART_DataMode_7;
        uart_initstruct.UART_TxMode = UART_DataMode_7;

        if (cfg->parity == PARITY_EVEN)
        {
            uart_initstruct.UART_RxMode = UART_DataMode_7Even;
            uart_initstruct.UART_TxMode = UART_DataMode_7Even;
        }
        else if (cfg->parity == PARITY_ODD)
        {
            uart_initstruct.UART_RxMode = UART_DataMode_7Odd;
            uart_initstruct.UART_TxMode = UART_DataMode_7Odd;
        }
    }
    else if (cfg->data_bits == DATA_BITS_8)
    {
        uart_initstruct.UART_RxMode = UART_DataMode_8;
        uart_initstruct.UART_TxMode = UART_DataMode_8;

        if (cfg->parity == PARITY_EVEN)
        {
            uart_initstruct.UART_RxMode = UART_DataMode_8Even;
            uart_initstruct.UART_TxMode = UART_DataMode_8Even;
        }
        else if (cfg->parity == PARITY_ODD)
        {
            uart_initstruct.UART_RxMode = UART_DataMode_8Odd;
            uart_initstruct.UART_TxMode = UART_DataMode_8Odd;
        }
    }
    else if (cfg->data_bits == DATA_BITS_9)
    {
        uart_initstruct.UART_RxMode = UART_DataMode_9;
        uart_initstruct.UART_TxMode = UART_DataMode_9;
    }

    if (cfg->bit_order == BIT_ORDER_MSB)
    {
        return RT_EINVAL;
    }

    if (cfg->invert == NRZ_INVERTED)
    {
        uart_initstruct.UART_RxPolar = UART_Polar_Opposite;
        uart_initstruct.UART_TxPolar = UART_Polar_Opposite;
    }

    /* config uart function */
    UART_Init(uart->huart, &uart_initstruct);
    /* enable rx and tx */
    uart->huart->CON.RXEN = 1;
    uart->huart->CON.TXEN = 1;

    NVIC_SetPriority(uart->irq, 1);

    return RT_EOK;
}

static rt_err_t es8px_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct es8p_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = (struct es8p_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irq);
        /* disable interrupt */
        UART_ITConfig(uart->huart, UART_IT_RB, DISABLE);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irq);
        /* enable interrupt */
        UART_ITConfig(uart->huart, UART_IT_RB, ENABLE);
        break;
    }

    return RT_EOK;
}

static int es8px_putc(struct rt_serial_device *serial, char c)
{
    struct es8p_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct es8p_uart *)serial->parent.user_data;

    while (UART_GetFlagStatus(uart->huart, UART_FLAG_TB) == RESET) ;
    UART_SendByte(uart->huart, c);

    return 1;
}

static int es8px_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct es8p_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct es8p_uart *)serial->parent.user_data;

    if (UART_GetFlagStatus(uart->huart, UART_FLAG_RB))
    {
        ch = UART_RecByte(uart->huart);
    }

    return ch;
}

static const struct rt_uart_ops es8px_uart_ops =
{
    es8px_configure,
    es8px_control,
    es8px_putc,
    es8px_getc,
};

#ifdef BSP_USING_UART0
/* UART0 device driver structure */
struct es8p_uart uart0 =
{
    UART0,
    UART0_IRQn
};

struct rt_serial_device serial0;

void UART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART0->IF.RBIF)
    {
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
/* UART1 device driver structure */
struct es8p_uart uart1 =
{
    UART1,
    UART1_IRQn
};

struct rt_serial_device serial1;

void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART1->IF.RBIF)
    {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
/* UART1 device driver structure */
struct es8p_uart uart2 =
{
    UART2,
    UART2_IRQn
};

struct rt_serial_device serial2;

void UART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART2->IF.RBIF)
    {
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
/* UART3 device driver structure */
struct es8p_uart uart3 =
{
    UART3,
    UART3_IRQn
};

struct rt_serial_device serial3;

void UART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART3->IF.RBIF)
    {
        rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_UART4
/* UART4 device driver structure */
struct es8p_uart uart4 =
{
    UART4,
    UART4_IRQn
};

struct rt_serial_device serial4;

void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART4->IF.RBIF)
    {
        rt_hw_serial_isr(&serial4, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#ifdef BSP_USING_UART5
/* UART5 device driver structure */
struct es8p_uart uart5 =
{
    UART5,
    UART5_IRQn
};

struct rt_serial_device serial5;

void UART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART5->IF.RBIF)
    {
        rt_hw_serial_isr(&serial5, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART5 */

int rt_hw_uart_init(void)
{
    struct es8p_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0
    uart = &uart0;
    serial0.ops = &es8px_uart_ops;
    serial0.config = config;

    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
    uart = &uart1;
    serial1.ops = &es8px_uart_ops;
    serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
    uart = &uart2;
    serial2.ops = &es8px_uart_ops;
    serial2.config = config;

    /* register UART2 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
    uart = &uart3;
    serial3.ops = &es8px_uart_ops;
    serial3.config = config;

    /* register UART3 device */
    rt_hw_serial_register(&serial3, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_UART4
    uart = &uart4;
    serial4.ops = &es8px_uart_ops;
    serial4.config = config;

    /* register UART4 device */
    rt_hw_serial_register(&serial4, "uart4",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
#endif /* BSP_USING_UART4 */

#ifdef BSP_USING_UART5
    uart = &uart5;
    serial5.ops = &es8px_uart_ops;
    serial5.config = config;

    /* register UART5 device */
    rt_hw_serial_register(&serial5, "uart5",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
#endif /* BSP_USING_UART5 */

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif
