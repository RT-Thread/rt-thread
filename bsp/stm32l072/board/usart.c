/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-08-30     Aubr.Cool       the first version
 */

#include <stm32l0xx.h>
#include <rtdevice.h>
#include <board.h>
#include "usart.h"

/* USART1 */
#ifdef RT_USING_UART1

#define UART1_GPIO				GPIOA
#endif

/* STM32 uart driver */
struct stm32_uart
{
    USART_TypeDef* uart_device;
    IRQn_Type irq;
};
typedef struct {
    USART_TypeDef     *Instance;
} stm32_hw_uart_def;

static rt_err_t stm32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    UART_HandleTypeDef huart1;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    struct stm32_uart* uart;
    uart = (struct stm32_uart *)serial->parent.user_data;
    huart1.Instance = uart->uart_device;
    huart1.Init.BaudRate = cfg->baud_rate;
    switch(cfg->data_bits) {
    case DATA_BITS_7:
        if(!cfg->parity) {
            huart1.Init.WordLength = UART_WORDLENGTH_7B;
        } else {
            huart1.Init.WordLength = UART_WORDLENGTH_8B;
        }
        break;
    case DATA_BITS_8:
        if(!cfg->parity) {
            huart1.Init.WordLength = UART_WORDLENGTH_8B;
        } else {
            huart1.Init.WordLength = UART_WORDLENGTH_9B;
        }
        break;
    case DATA_BITS_9:
        if(!cfg->parity) {
            huart1.Init.WordLength = UART_WORDLENGTH_9B;
        } else {
            return RT_EIO;
        }
        break;
    default:
        return RT_EIO;
    }
    switch(cfg->stop_bits) {
    case STOP_BITS_1:
        huart1.Init.StopBits = UART_STOPBITS_1;
        break;
    case STOP_BITS_2:
        huart1.Init.StopBits = UART_STOPBITS_2;
        break;
    default:
        return RT_EIO;
    }
    switch(cfg->parity) {
    case PARITY_NONE:
        huart1.Init.Parity = UART_PARITY_NONE;
        break;
    case PARITY_ODD:
        huart1.Init.Parity = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        huart1.Init.Parity = UART_PARITY_EVEN;
        break;
    default:
        return RT_EIO;
    }
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        return RT_EIO;
    }
    return RT_EOK;
}
static rt_err_t stm32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct stm32_uart* uart;
    stm32_hw_uart_def huart1;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct stm32_uart *)serial->parent.user_data;
    huart1.Instance = uart->uart_device;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        __HAL_UART_DISABLE_IT((&huart1), UART_IT_RXNE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        __HAL_UART_ENABLE_IT((&huart1), UART_IT_RXNE);
        break;
    }

    return RT_EOK;
}

static int stm32_putc(struct rt_serial_device *serial, char c)
{
    struct stm32_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct stm32_uart *)serial->parent.user_data;
    stm32_hw_uart_def huart1;
    huart1.Instance = uart->uart_device;
    if(serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX) {
        if(!(uart->uart_device->ISR & UART_FLAG_TXE)) {
            __HAL_UART_ENABLE_IT((&huart1), UART_IT_TC);
            return -1;
        }
        uart->uart_device->TDR = c;
        __HAL_UART_ENABLE_IT((&huart1), UART_IT_TC);
    } else {
        while(!(uart->uart_device->ISR & UART_FLAG_TXE));
        uart->uart_device->TDR = c;
    }
    return 1;
}

static int stm32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct stm32_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct stm32_uart *)serial->parent.user_data;

    ch = -1;
    if (uart->uart_device->ISR & UART_FLAG_RXNE)
    {
        ch = uart->uart_device->RDR & 0xff;
    }
    return ch;
}

static const struct rt_uart_ops stm32_uart_ops =
{
    stm32_configure,
    stm32_control,
    stm32_putc,
    stm32_getc,
};

#if defined(RT_USING_UART1)
/* UART1 device driver structure */
struct stm32_uart uart1 =
{
    USART1,
    USART1_IRQn,
};
struct rt_serial_device serial1;

void USART1_IRQHandler(void)
{
    struct stm32_uart* uart;
    uart = &uart1;
    stm32_hw_uart_def huart1;
    huart1.Instance = uart->uart_device;
    /* enter interrupt */
    rt_interrupt_enter();
    if(__HAL_UART_GET_IT(&huart1, UART_IT_RXNE))// RXIRQ
    {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    if (__HAL_UART_GET_IT(&huart1, UART_IT_TC))
    {
        /* clear interrupt */
        __HAL_UART_DISABLE_IT((&huart1), UART_IT_TC);
        __HAL_UART_CLEAR_IT(&huart1, UART_CLEAR_TCF);
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_TX_DONE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART1 */

static void RCC_Configuration(void)
{
#ifdef RT_USING_UART1
      __HAL_RCC_GPIOA_CLK_ENABLE();
      __HAL_RCC_USART1_CLK_ENABLE();
#endif /* RT_USING_UART1 */
}

static void GPIO_Configuration(void)
{
#ifdef RT_USING_UART1
    {
        rt_uint32_t mode;
        mode = (UART1_GPIO_AF << 8) | GPIO_MODE_AF_PP;
        stm32_pin_mode_early(UART1_GPIO_TX, mode);
        stm32_pin_mode_early(UART1_GPIO_RX, mode);
    }
#endif /* RT_USING_UART1 */
}

static void NVIC_Configuration(struct stm32_uart* uart)
{
      HAL_NVIC_SetPriority(uart->irq, 0, 0);
      UART_ENABLE_IRQ(uart->irq);
}

int rt_hw_usart_init(void)
{
    struct stm32_uart* uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    RCC_Configuration();
    GPIO_Configuration();

#ifdef RT_USING_UART1
    uart = &uart1;
    config.baud_rate = BAUD_RATE_115200;

    serial1.ops    = &stm32_uart_ops;
    serial1.config = config;

    NVIC_Configuration(&uart1);

    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR |
                        RT_DEVICE_FLAG_INT_RX |
                          RT_DEVICE_FLAG_INT_TX,
                          uart);
#endif /* RT_USING_UART1 */
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);
