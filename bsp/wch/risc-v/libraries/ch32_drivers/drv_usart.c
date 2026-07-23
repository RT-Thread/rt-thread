/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-27     liYony       the first version
 */

#include "board.h"
#include <rtdevice.h>
#include <drv_usart.h>

#ifdef RT_USING_SERIAL

//#define DRV_DEBUG
#define LOG_TAG              "drv.uart"
#include <drv_log.h>

#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && !defined(BSP_USING_UART4) && \
    !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

enum
{
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    UART3_INDEX,
#endif
#ifdef BSP_USING_UART4
    UART4_INDEX,
#endif
#ifdef BSP_USING_UART5
    UART5_INDEX,
#endif
#ifdef BSP_USING_UART6
    UART6_INDEX,
#endif
#ifdef BSP_USING_UART7
    UART7_INDEX,
#endif
#ifdef BSP_USING_UART8
    UART8_INDEX,
#endif
};

/* If you want to use other serial ports, please follow UART1 to complete other
  serial ports. For clock configuration,  */
static struct ch32_uart_hw_config uart_hw_config[] =
{
#ifdef BSP_USING_UART1
    {
        /* clock configuration, please refer to ch32v30x_rcc.h */
        RCC_APB2Periph_USART1, RCC_APB2Periph_GPIOA,
        /* GPIO  configuration : TX_Port,TX_Pin, RX_Port,RX_Pin */
        GPIOA, GPIO_Pin_9, /* Tx */GPIOA, GPIO_Pin_10, /* Rx */
        /* Whether to enable port remapping, you can refer to ch32v30x_gpio.h file,
        for example, USART1 needs to be turned on, you can use GPIO_Remap_USART1 */
        GPIO_Remap_NONE,
    },
#endif
#ifdef BSP_USING_UART2
    {
        /* clock configuration, please refer to ch32v30x_rcc.h */
        RCC_APB1Periph_USART2, RCC_APB2Periph_GPIOA,
        /* GPIO  configuration : TX_Port,TX_Pin, RX_Port,RX_Pin */
        GPIOA, GPIO_Pin_2, /* Tx */GPIOA, GPIO_Pin_3, /* Rx */
        /* Whether to enable port remapping, you can refer to ch32v30x_gpio.h file,
        for example, USART1 needs to be turned on, you can use GPIO_Remap_USART1 */
        GPIO_Remap_NONE,
    },
#endif
#ifdef BSP_USING_UART3
    {
        /* clock configuration, please refer to ch32v30x_rcc.h */
        RCC_APB1Periph_USART3, RCC_APB2Periph_GPIOB,
        /* GPIO  configuration : TX_Port,TX_Pin, RX_Port,RX_Pin */
        GPIOB, GPIO_Pin_10, /* Tx */GPIOB, GPIO_Pin_11, /* Rx */
        /* Whether to enable port remapping, you can refer to ch32v30x_gpio.h file,
        for example, USART1 needs to be turned on, you can use GPIO_Remap_USART1 */
        GPIO_Remap_NONE,
    },
#endif
#ifdef BSP_USING_UART4
    {
        /* clock configuration, please refer to ch32v30x_rcc.h */
        RCC_APB1Periph_UART4, RCC_APB2Periph_GPIOC,
        /* GPIO  configuration : TX_Port,TX_Pin, RX_Port,RX_Pin */
        GPIOC, GPIO_Pin_10, /* Tx */GPIOC, GPIO_Pin_11, /* Rx */
        /* Whether to enable port remapping, you can refer to ch32v30x_gpio.h file,
        for example, USART1 needs to be turned on, you can use GPIO_Remap_USART1 */
        GPIO_Remap_NONE,
    },
#endif
#ifdef BSP_USING_UART5
    {
        /* clock configuration, please refer to ch32v30x_rcc.h */
        RCC_APB1Periph_UART5, RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,
        /* GPIO  configuration : TX_Port,TX_Pin, RX_Port,RX_Pin */
        GPIOC, GPIO_Pin_12, /* Tx */GPIOD, GPIO_Pin_2, /* Rx */
        /* Whether to enable port remapping, you can refer to ch32v30x_gpio.h file,
        for example, USART1 needs to be turned on, you can use GPIO_Remap_USART1 */
        GPIO_Remap_NONE,
    },
#endif
#ifdef BSP_USING_UART6
    {
        /* clock configuration, please refer to ch32v30x_rcc.h */
        RCC_APB1Periph_UART6, RCC_APB2Periph_GPIOC,
        /* GPIO  configuration : TX_Port,TX_Pin, RX_Port,RX_Pin */
        GPIOC, GPIO_Pin_0, /* Tx */GPIOC, GPIO_Pin_1, /* Rx */
        /* Whether to enable port remapping, you can refer to ch32v30x_gpio.h file,
        for example, USART1 needs to be turned on, you can use GPIO_Remap_USART1 */
        GPIO_Remap_NONE,
    },
#endif
#ifdef BSP_USING_UART7
    {
        /* clock configuration, please refer to ch32v30x_rcc.h */
        RCC_APB1Periph_UART7, RCC_APB2Periph_GPIOC,
        /* GPIO  configuration : TX_Port,TX_Pin, RX_Port,RX_Pin */
        GPIOC, GPIO_Pin_2, /* Tx */GPIOC, GPIO_Pin_3, /* Rx */
        /* Whether to enable port remapping, you can refer to ch32v30x_gpio.h file,
        for example, USART1 needs to be turned on, you can use GPIO_Remap_USART1 */
        GPIO_Remap_NONE,
    },
#endif
#ifdef BSP_USING_UART8
    {
        /* clock configuration, please refer to ch32v30x_rcc.h */
        RCC_APB1Periph_UART8, RCC_APB2Periph_GPIOC,
        /* GPIO  configuration : TX_Port,TX_Pin, RX_Port,RX_Pin */
        GPIOC, GPIO_Pin_4, /* Tx */GPIOC, GPIO_Pin_5, /* Rx */
        /* Whether to enable port remapping, you can refer to ch32v30x_gpio.h file,
        for example, USART1 needs to be turned on, you can use GPIO_Remap_USART1 */
        GPIO_Remap_NONE,
    },
#endif
};

static struct ch32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART1
    {
        "uart1",
        USART1,
        USART1_IRQn,
    },
#endif
#ifdef BSP_USING_UART2
    {
        "uart2",
        USART2,
        USART2_IRQn,
    },
#endif
#ifdef BSP_USING_UART3
    {
        "uart3",
        USART3,
        USART3_IRQn,
    },
#endif
#ifdef BSP_USING_UART4
    {
        "uart4",
        UART4,
        UART4_IRQn,
    },
#endif
#ifdef BSP_USING_UART5
    {
        "uart5",
        UART5,
        UART5_IRQn,
    },
#endif
#ifdef BSP_USING_UART6
    {
        "uart6",
        UART6,
        UART6_IRQn,
    },
#endif
#ifdef BSP_USING_UART7
    {
        "uart7",
        UART7,
        UART7_IRQn,
    },
#endif
#ifdef BSP_USING_UART8
    {
        "uart8",
        UART8,
        UART8_IRQn,
    },
#endif
};

static struct ch32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static rt_err_t ch32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct ch32_uart *uart;
    GPIO_InitTypeDef GPIO_InitStructure={0};

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct ch32_uart *) serial->parent.user_data;

    uart->Init.USART_BaudRate             = cfg->baud_rate;
    uart->Init.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
    uart->Init.USART_Mode                 = USART_Mode_Rx|USART_Mode_Tx;

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        uart->Init.USART_WordLength = USART_WordLength_8b;
        break;
    case DATA_BITS_9:
        uart->Init.USART_WordLength = USART_WordLength_9b;
        break;
    default:
        uart->Init.USART_WordLength = USART_WordLength_8b;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->Init.USART_StopBits   = USART_StopBits_1;
        break;
    case STOP_BITS_2:
        uart->Init.USART_StopBits   = USART_StopBits_2;
        break;
    default:
        uart->Init.USART_StopBits   = USART_StopBits_1;
        break;
    }
    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart->Init.USART_Parity    = USART_Parity_No;
        break;
    case PARITY_ODD:
        uart->Init.USART_Parity    = USART_Parity_Odd;
        break;
    case PARITY_EVEN:
        uart->Init.USART_Parity    = USART_Parity_Even;
        break;
    default:
        uart->Init.USART_Parity     = USART_Parity_No;
        break;
    }

    /* UART hardware configuration, including clock and GPIO, etc. */
    RCC_APB2PeriphClockCmd(uart->hw_config->gpio_periph_clock, ENABLE);
    if(uart->config->Instance == USART1)
    {
        RCC_APB2PeriphClockCmd(uart->hw_config->uart_periph_clock, ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(uart->hw_config->uart_periph_clock, ENABLE);
    }

    if(uart->hw_config->remap != GPIO_Remap_NONE)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        GPIO_PinRemapConfig(uart->hw_config->remap, ENABLE);
    }
    GPIO_InitStructure.GPIO_Pin = uart->hw_config->tx_gpio_pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(uart->hw_config->tx_gpio_port, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = uart->hw_config->rx_gpio_pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(uart->hw_config->rx_gpio_port, &GPIO_InitStructure);

    USART_Init(uart->config->Instance,&uart->Init);
    USART_Cmd(uart->config->Instance, ENABLE);

    return RT_EOK;
}

static rt_err_t ch32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct ch32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct ch32_uart *)serial->parent.user_data;
    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->config->irq_type);
        /* disable interrupt */
        USART_ITConfig(uart->config->Instance,USART_IT_RXNE,DISABLE);
        break;
    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->config->irq_type);
        /* enable interrupt */
        USART_ITConfig(uart->config->Instance, USART_IT_RXNE,ENABLE);
        break;
    }
    return RT_EOK;
}

static int ch32_putc(struct rt_serial_device *serial, char c)
{
    struct ch32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct ch32_uart *)serial->parent.user_data;
    while (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TC) == RESET);
    uart->config->Instance->DATAR = c;
    return 1;
}

static int ch32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct ch32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct ch32_uart *)serial->parent.user_data;
    ch = -1;
    if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXNE) != RESET)
    {
        ch = uart->config->Instance->DATAR & 0xff;
    }
    return ch;
}

static rt_ssize_t ch32dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    return -RT_EIO;
}

static void uart_isr(struct rt_serial_device *serial)
{
    struct ch32_uart *uart = (struct ch32_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);
    if (USART_GetITStatus(uart->config->Instance, USART_IT_RXNE) != RESET)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        USART_ClearITPendingBit(uart->config->Instance, USART_IT_RXNE);
    }
}

static const struct rt_uart_ops ch32_uart_ops =
{
    ch32_configure,
    ch32_control,
    ch32_putc,
    ch32_getc,
    ch32dma_transmit
};

#ifdef BSP_USING_UART1
#if defined (SOC_RISCV_SERIES_CH32V2)
void USART1_IRQHandler(void) __attribute__((interrupt()));
#else
void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void USART1_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    uart_isr(&(uart_obj[UART1_INDEX].serial));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif

#ifdef BSP_USING_UART2
#if defined (SOC_RISCV_SERIES_CH32V2)
void USART2_IRQHandler(void) __attribute__((interrupt()));
#else
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void USART2_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    uart_isr(&(uart_obj[UART2_INDEX].serial));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif

#ifdef BSP_USING_UART3
#if defined (SOC_RISCV_SERIES_CH32V2)
void USART3_IRQHandler(void) __attribute__((interrupt()));
#else
void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void USART3_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    uart_isr(&(uart_obj[UART3_INDEX].serial));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif

#ifdef BSP_USING_UART4
#if defined (SOC_RISCV_SERIES_CH32V2)
void UART4_IRQHandler(void) __attribute__((interrupt()));
#else
void UART4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void UART4_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    uart_isr(&(uart_obj[UART4_INDEX].serial));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif

#ifdef BSP_USING_UART5
#if defined (SOC_RISCV_SERIES_CH32V2)
void UART5_IRQHandler(void) __attribute__((interrupt()));
#else
void UART5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void UART5_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    uart_isr(&(uart_obj[UART5_INDEX].serial));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif

#ifdef BSP_USING_UART6
#if defined (SOC_RISCV_SERIES_CH32V2)
void UART6_IRQHandler(void) __attribute__((interrupt()));
#else
void UART6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void UART6_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    uart_isr(&(uart_obj[UART6_INDEX].serial));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif

#ifdef BSP_USING_UART7
#if defined (SOC_RISCV_SERIES_CH32V2)
void UART7_IRQHandler(void) __attribute__((interrupt()));
#else
void UART7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void UART7_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    uart_isr(&(uart_obj[UART7_INDEX].serial));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif

#ifdef BSP_USING_UART8
#if defined (SOC_RISCV_SERIES_CH32V2)
void UART8_IRQHandler(void) __attribute__((interrupt()));
#else
void UART8_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void UART8_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    uart_isr(&(uart_obj[UART8_INDEX].serial));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif

int rt_hw_usart_init(void)
{
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct ch32_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].config        = &uart_config[i];
        uart_obj[i].hw_config     = &uart_hw_config[i];
        uart_obj[i].serial.ops    = &ch32_uart_ops;
        uart_obj[i].serial.config = config;
        /* Hardware initialization is required, otherwise it
        will not be registered into the device framework */
        if(uart_obj[i].hw_config->gpio_periph_clock == 0)
        {
            LOG_E("You did not perform hardware initialization for %s", uart_obj[i].config->name);
            continue;
        }
        if(uart_obj[i].hw_config->uart_periph_clock == 0)
        {
            LOG_E("You did not perform hardware initialization for %s", uart_obj[i].config->name);
            continue;
        }
        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       , &uart_obj[i]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL */
