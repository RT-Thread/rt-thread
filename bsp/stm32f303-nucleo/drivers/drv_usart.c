/*
* File      : drv_usart.c
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2015, RT-Thread Development Team
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
* 2018-06-23     BC           the first version for stm32f303ze with STM32 HAL
*/
#include "drv_usart.h"
#include "board.h"
#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>
/* STM32 uart driver */
struct drv_uart
{
    UART_HandleTypeDef UartHandle;
    IRQn_Type irq;
};

static rt_err_t drv_configure(struct rt_serial_device *serial,
                              struct serial_configure *cfg)
{
    struct drv_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct drv_uart *)serial->parent.user_data;
    uart->UartHandle.Init.BaudRate   = cfg->baud_rate;
    uart->UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    uart->UartHandle.Init.Mode       = UART_MODE_TX_RX;
    uart->UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    uart->UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        uart->UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
        break;
    case DATA_BITS_9:
        uart->UartHandle.Init.WordLength = UART_WORDLENGTH_9B;
        break;
    default:
        uart->UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
        break;
    }
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->UartHandle.Init.StopBits   = UART_STOPBITS_1;
        break;
    case STOP_BITS_2:
        uart->UartHandle.Init.StopBits   = UART_STOPBITS_2;
        break;
    default:
        uart->UartHandle.Init.StopBits   = UART_STOPBITS_1;
        break;
    }
    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart->UartHandle.Init.Parity     = UART_PARITY_NONE;
        break;
    case PARITY_ODD:
        uart->UartHandle.Init.Parity     = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        uart->UartHandle.Init.Parity     = UART_PARITY_EVEN;
        break;
    default:
        uart->UartHandle.Init.Parity     = UART_PARITY_NONE;
        break;
    }
    if (HAL_UART_Init(&uart->UartHandle) != HAL_OK)
    {
        return RT_ERROR;
    }
    return RT_EOK;
}

static rt_err_t drv_control(struct rt_serial_device *serial,
                            int cmd, void *arg)
{
    struct drv_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct drv_uart *)serial->parent.user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irq);
        /* disable interrupt */
        __HAL_UART_DISABLE_IT(&uart->UartHandle, UART_IT_RXNE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        HAL_NVIC_SetPriority(uart->irq, 5, 0);
        NVIC_EnableIRQ(uart->irq);
        /* enable interrupt */
        __HAL_UART_ENABLE_IT(&uart->UartHandle, UART_IT_RXNE);
        break;
    }
    return RT_EOK;
}

static int drv_putc(struct rt_serial_device *serial, char c)
{
    struct drv_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct drv_uart *)serial->parent.user_data;
    while ((__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_TXE) == RESET));
    uart->UartHandle.Instance->TDR = c;
    return 1;
}

static int drv_getc(struct rt_serial_device *serial)
{
    int ch;
    struct drv_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct drv_uart *)serial->parent.user_data;
    ch = -1;
    if (__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_RXNE) != RESET)
        ch = uart->UartHandle.Instance->RDR & 0xff;
    return ch;
}

static const struct rt_uart_ops drv_uart_ops =
{
    drv_configure,
    drv_control,
    drv_putc,
    drv_getc,
};

#if defined(RT_USING_UART1)
/* UART1 device driver structure */
static struct drv_uart uart1;
struct rt_serial_device serial1;
void USART1_IRQHandler(void)
{
    struct drv_uart *uart;
    uart = &uart1;
    /* enter interrupt */
    rt_interrupt_enter();
    /* UART in mode Receiver -------------------------------------------------*/
    if ((__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_RXNE) != RESET) &&
            (__HAL_UART_GET_IT_SOURCE(&uart->UartHandle, UART_IT_RXNE) != RESET))
    {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        __HAL_UART_CLEAR_FLAG(&uart->UartHandle, UART_FLAG_RXNE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART1 */

#if defined(RT_USING_UART2)
/* UART2 device driver structure */
static struct drv_uart uart2;
struct rt_serial_device serial2;
void USART2_IRQHandler(void)
{
    struct drv_uart *uart;
    uart = &uart2;
    /* enter interrupt */
    rt_interrupt_enter();
    /* UART in mode Receiver -------------------------------------------------*/
    if ((__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_RXNE) != RESET) &&
            (__HAL_UART_GET_IT_SOURCE(&uart->UartHandle, UART_IT_RXNE) != RESET))
    {
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        __HAL_UART_CLEAR_FLAG(&uart->UartHandle, UART_FLAG_RXNE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART2 */

#if defined(RT_USING_UART3)
/* UART3 device driver structure */
static struct drv_uart uart3;
struct rt_serial_device serial3;
void USART3_IRQHandler(void)
{
    struct drv_uart *uart;
    uart = &uart3;
    /* enter interrupt */
    rt_interrupt_enter();
    /* UART in mode Receiver -------------------------------------------------*/
    if ((__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_RXNE) != RESET) &&
            (__HAL_UART_GET_IT_SOURCE(&uart->UartHandle, UART_IT_RXNE) != RESET))
    {
        rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        __HAL_UART_CLEAR_FLAG(&uart->UartHandle, UART_FLAG_RXNE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART3 */

/**
* @brief UART MSP Initialization
*        This function configures the hardware resources used in this example:
*           - Peripheral's clock enable
*           - Peripheral's GPIO Configuration
*           - NVIC configuration for UART interrupt request enable
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if (uartHandle->Instance == USART1)
    {
        /* USART1 clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();
        /* GPIOA clock enable */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (uartHandle->Instance == USART2)
    {
        /* USART2 clock enable */
        __HAL_RCC_USART2_CLK_ENABLE();
        /* GPIOA clock enable */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (uartHandle->Instance == USART3)
    {
        /* USART3 clock enable */
        __HAL_RCC_USART3_CLK_ENABLE();
        /* GPIOD clock enable */
        __HAL_RCC_GPIOD_CLK_ENABLE();
        /**USART3 GPIO Configuration
        PD8     ------> USART3_TX
        PD9     ------> USART3_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle)
{
    if (uartHandle->Instance == USART1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USART1_CLK_DISABLE();
        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
    }
    else if (uartHandle->Instance == USART2)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USART2_CLK_DISABLE();
        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
    }
    else if (uartHandle->Instance == USART3)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USART3_CLK_DISABLE();
        /**USART3 GPIO Configuration
        PD8     ------> USART3_TX
        PD9     ------> USART3_RX
        */
        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8 | GPIO_PIN_9);
    }
}

int hw_usart_init(void)
{
    struct drv_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
#ifdef RT_USING_UART1
    uart = &uart1;
    uart->UartHandle.Instance = USART1;
    uart->irq = USART1_IRQn;
    serial1.ops    = &drv_uart_ops;
    serial1.config = config;
    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART1 */
#ifdef RT_USING_UART2
    uart = &uart2;
    uart->UartHandle.Instance = USART2;
    uart->irq = USART2_IRQn;
    serial2.ops    = &drv_uart_ops;
    serial2.config = config;
    /* register UART2 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART2 */
#ifdef RT_USING_UART3
    uart = &uart3;
    uart->UartHandle.Instance = USART3;
    uart->irq = USART3_IRQn;
    serial3.ops    = &drv_uart_ops;
    serial3.config = config;
    /* register UART3 device */
    rt_hw_serial_register(&serial3, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART3 */
    return 0;
}
INIT_BOARD_EXPORT(hw_usart_init);
