/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-02     FMD-AE       first version
 */

#include "board.h"
#include "drv_usart.h"
#include "drv_config.h"

#ifdef RT_USING_SERIAL

//#define DRV_DEBUG
#define LOG_TAG             "drv.usart"
#include <drv_log.h>

#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2)
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
};

static struct ft32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif
#ifdef BSP_USING_UART2
    UART2_CONFIG,
#endif
};

static struct ft32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

void UART_MspInit(USART_TypeDef *USARTx)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if (USARTx == USART1)
    {
#if defined(SOC_SERIES_FT32F0)
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
#endif
#if defined(SOC_SERIES_FT32F4)
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
#endif
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

        /*GPIO INIT*/
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
#if defined(SOC_SERIES_FT32F0)
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
#endif
#if defined(SOC_SERIES_FT32F4)
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);
#endif
        /* USART1 interrupt Init */
        NVIC_SetPriority(USART1_IRQn, 5);
        NVIC_EnableIRQ(USART1_IRQn);
    }
    else if (USARTx  == USART2)
    {
#if defined(SOC_SERIES_FT32F0)
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
#endif
#if defined(SOC_SERIES_FT32F4)
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);
#endif

        /*GPIO INIT*/
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
#if defined(SOC_SERIES_FT32F0)
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
#endif
#if defined(SOC_SERIES_FT32F4)
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);
#endif

        /* USART2 interrupt Init */
        NVIC_SetPriority(USART2_IRQn, 5);
        NVIC_EnableIRQ(USART2_IRQn);
    }
}

static rt_err_t ft32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct ft32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct ft32_uart, serial);
    uart->Init.USART_BaudRate = cfg->baud_rate;
#if defined(SOC_SERIES_FT32F0)
    uart->Init.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
#endif
#if defined(SOC_SERIES_FT32F4)
    uart->Init.USART_Mode = USART_MODE_TX_RX;
#endif
    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_NONE:
        uart->Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        break;
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
#if defined(SOC_SERIES_FT32F0)
        uart->Init.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;
#endif
#if defined(SOC_SERIES_FT32F4)
        uart->Init.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_DTR;
#endif
        break;
    default:
        uart->Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        break;
    }

    switch (cfg->data_bits)
    {
#if defined(SOC_SERIES_FT32F0)
    case DATA_BITS_8:
        if (cfg->parity == PARITY_ODD || cfg->parity == PARITY_EVEN)
            uart->Init.USART_WordLength = USART_WordLength_9b;
        else
            uart->Init.USART_WordLength = USART_WordLength_8b;
        break;
    case DATA_BITS_9:
        uart->Init.USART_WordLength = USART_WordLength_9b;
        break;
    default:
        uart->Init.USART_WordLength = USART_WordLength_8b;
        break;
#endif
#if defined(SOC_SERIES_FT32F4)
    case DATA_BITS_9:
        uart->Init.USART_WordLength = USART_CHAR_LENGTH9_ENABLE;
        break;
    case DATA_BITS_8:
        uart->Init.USART_WordLength = USART_CHAR_LENGTH_8BIT;
        break;
    case DATA_BITS_7:
        uart->Init.USART_WordLength = USART_CHAR_LENGTH_7BIT;
        break;
    case DATA_BITS_6:
        uart->Init.USART_WordLength = USART_CHAR_LENGTH_6BIT;
        break;
    case DATA_BITS_5:
        uart->Init.USART_WordLength = USART_CHAR_LENGTH_5BIT;
        break;
    default:
        uart->Init.USART_WordLength = USART_CHAR_LENGTH_8BIT;
        break;
#endif
    }

    switch (cfg->stop_bits)
    {
#if defined(SOC_SERIES_FT32F0)
    case STOP_BITS_1:
        uart->Init.USART_StopBits = USART_StopBits_1;
        break;
    case STOP_BITS_2:
        uart->Init.USART_StopBits   = USART_StopBits_2;
        break;
    default:
        uart->Init.USART_StopBits   = USART_StopBits_1;
        break;
#endif
#if defined(SOC_SERIES_FT32F4)
    case STOP_BITS_1:
        uart->Init.USART_StopBits = USART_STOPBITS_1;
        break;
    case STOP_BITS_2:
        uart->Init.USART_StopBits   = USART_STOPBITS_2;
        break;
    default:
        uart->Init.USART_StopBits   = USART_STOPBITS_1;
        break;
#endif
    }

    switch (cfg->parity)
    {
#if defined(SOC_SERIES_FT32F0)
    case PARITY_NONE:
        uart->Init.USART_Parity     = USART_Parity_No;
        break;
    case PARITY_ODD:
        uart->Init.USART_Parity     = USART_Parity_Odd;
        break;
    case PARITY_EVEN:
        uart->Init.USART_Parity     = USART_Parity_Even;
        break;
    default:
        uart->Init.USART_Parity     = USART_Parity_No;
        break;
#endif
#if defined(SOC_SERIES_FT32F4)
    case PARITY_NONE:
        uart->Init.USART_Parity     = USART_PARITY_NONE;
        break;
    case PARITY_ODD:
        uart->Init.USART_Parity     = USART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        uart->Init.USART_Parity     = USART_PARITY_EVEN;
        break;
    default:
        uart->Init.USART_Parity     = USART_PARITY_NONE;
        break;
#endif
    }

    UART_MspInit(uart->config->Instance);
    USART_Init(uart->config->Instance, &(uart->Init));
    USART_Cmd(uart->config->Instance, ENABLE);
    return RT_EOK;
}

static rt_err_t ft32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct ft32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ft32_uart, serial);

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->config->irq_type);
        /* disable interrupt */
#if defined(SOC_SERIES_FT32F0)
        /* enable interrupt */
        USART_ITConfig(uart->config->Instance, USART_IT_RXNE, DISABLE);
        break;
#endif
#if defined(SOC_SERIES_FT32F4)
        /* enable interrupt */
        USART_ITConfig(uart->config->Instance, USART_IT_RXRDY, DISABLE);
        break;
#endif

        break;

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_SetPriority(uart->config->irq_type, 1);
        NVIC_EnableIRQ(uart->config->irq_type);
#if defined(SOC_SERIES_FT32F0)
        /* enable interrupt */
        USART_ITConfig(uart->config->Instance, USART_IT_RXNE, ENABLE);
        break;
#endif
#if defined(SOC_SERIES_FT32F4)
        /* enable interrupt */
        USART_ITConfig(uart->config->Instance, USART_IT_RXRDY, ENABLE);
        break;
#endif
        break;

    case RT_DEVICE_CTRL_CLOSE:
        USART_DeInit(uart->config->Instance);
        break;

    }
    return RT_EOK;
}

#if defined(SOC_SERIES_FT32F0)
rt_uint32_t ft32_uart_get_mask(rt_uint32_t word_length, rt_uint32_t parity)
{
    rt_uint32_t mask;
    if (word_length == USART_WordLength_8b)
    {
        if (parity == USART_Parity_No)
        {
            mask = 0x00FFU ;
        }
        else
        {
            mask = 0x007FU ;
        }
    }
    else if (word_length == USART_WordLength_9b)
    {
        if (parity == USART_Parity_No)
        {
            mask = 0x01FFU ;
        }
        else
        {
            mask = 0x00FFU ;
        }
    }

    else if (word_length == USART_WordLength_7b)
    {
        if (parity == USART_Parity_No)
        {
            mask = 0x007FU ;
        }
        else
        {
            mask = 0x003FU ;
        }
    }
    else
    {
        mask = 0x0000U;
    }
    return mask;
}
#endif

static int ft32_putc(struct rt_serial_device *serial, char c)
{
    struct ft32_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ft32_uart, serial);
#if defined(SOC_SERIES_FT32F0)
    UART_INSTANCE_CLEAR_FUNCTION(uart->config->Instance, USART_FLAG_TC);
    uart->config->Instance->TDR = c;
#elif defined(SOC_SERIES_FT32F4)
    USART_Transmit(uart->config->Instance, c);
#else
    uart->config->Instance->DR = c;
#endif
#if defined(SOC_SERIES_FT32F0)
    while (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TC) == RESET);
#endif
#if defined(SOC_SERIES_FT32F4)
    while (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TXRDY) == RESET);
#endif
    return 1;
}

static int ft32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct ft32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ft32_uart, serial);

    ch = -1;
#if defined(SOC_SERIES_FT32F0)
    if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXNE) != RESET)
#endif
#if defined(SOC_SERIES_FT32F4)
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXRDY) != RESET)
#endif
        {
#if defined(SOC_SERIES_FT32F0)
            ch = uart->config->Instance->RDR & ft32_uart_get_mask(uart->Init.USART_WordLength, uart->Init.USART_Parity);
#elif defined(SOC_SERIES_FT32F4)
            ch = USART_Receive(uart->config->Instance);
#else
            ch = uart->config->Instance->DR & ft32_uart_get_mask(uart->Init.USART_WordLength, uart->Init.USART_Parity);
#endif
        }
    return ch;
}

static rt_ssize_t ft32_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    if (size == 0)
    {
        return 0;
    }

    if (RT_SERIAL_DMA_TX == direction)
    {
        return size;
    }
    return 0;
}
/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct ft32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ft32_uart, serial);
#if defined(SOC_SERIES_FT32F0)
    /* UART in mode Receiver -------------------------------------------------*/
    if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXNE) != RESET)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
#endif
#if defined(SOC_SERIES_FT32F4)
    /* UART in mode Receiver -------------------------------------------------*/
    if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXRDY) != RESET)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
#endif
#if defined (SOC_SERIES_FT32F0)
    else
    {
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_ORE) != RESET)
        {
            USART_ClearFlag(uart->config->Instance, USART_FLAG_ORE);
        }
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_NE) != RESET)
        {
            USART_ClearFlag(uart->config->Instance, USART_FLAG_NE);
        }
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_FE) != RESET)
        {
            USART_ClearFlag(uart->config->Instance, USART_FLAG_FE);
        }
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_PE) != RESET)
        {
            USART_ClearFlag(uart->config->Instance, USART_FLAG_PE);
        }
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_CTS) != RESET)
        {
            UART_INSTANCE_CLEAR_FUNCTION(uart->config->Instance, USART_FLAG_CTS);
        }
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TXE) != RESET)
        {
            UART_INSTANCE_CLEAR_FUNCTION(uart->config->Instance, USART_FLAG_TXE);
        }
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TC) != RESET)
        {
            UART_INSTANCE_CLEAR_FUNCTION(uart->config->Instance, USART_FLAG_TC);
        }
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXNE) != RESET)
        {
            UART_INSTANCE_CLEAR_FUNCTION(uart->config->Instance, USART_FLAG_RXNE);
        }
    }
#endif
#if defined (SOC_SERIES_FT32F4)
    else
    {

    }
#endif
}

#if defined(SOC_SERIES_FT32F0)
#if defined(BSP_USING_UART1)
void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART1_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
void USART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART2_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART2 */
#endif

#if defined(SOC_SERIES_FT32F4)
#if defined(BSP_USING_UART1)
void USART1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART1_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
void USART2_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART2_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART2 */
#endif

static void ft32_uart_get_dma_config(void)
{
#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].uart_dma_flag = 0;
#endif

#ifdef BSP_USING_UART2
    uart_obj[UART2_INDEX].uart_dma_flag = 0;
#endif
}

static const struct rt_uart_ops ft32_uart_ops =
{
    .configure = ft32_configure,
    .control = ft32_control,
    .putc = ft32_putc,
    .getc = ft32_getc,
    .dma_transmit = ft32_dma_transmit
};

int rt_hw_usart_init(void)
{
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct ft32_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    ft32_uart_get_dma_config();

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].config = &uart_config[i];
        uart_obj[i].serial.ops    = &ft32_uart_ops;
        uart_obj[i].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX
                                       | uart_obj[i].uart_dma_flag
                                       , NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL */
