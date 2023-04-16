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

#ifdef RT_SERIAL_USING_DMA
    static void ft32_dma_config(struct rt_serial_device *serial, rt_ubase_t flag);
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
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

        /*GPIO INIT*/
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

        /* USART1 interrupt Init */
        NVIC_SetPriority(USART1_IRQn, 5);
        NVIC_EnableIRQ(USART1_IRQn);
    }
    else if (USARTx  == USART2)
    {
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

        /*GPIO INIT*/
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);

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
    uart->Init.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_NONE:
        uart->Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        break;
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
        uart->Init.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;
        break;
    default:
        uart->Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        break;
    }

    switch (cfg->data_bits)
    {
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
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->Init.USART_StopBits = USART_StopBits_1;
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
    }

#ifdef RT_SERIAL_USING_DMA
    uart->dma_rx.last_index = 0;
#endif
    UART_MspInit(uart->config->Instance);
    USART_Init(uart->config->Instance, &(uart->Init));
    USART_Cmd(uart->config->Instance, ENABLE);
    return RT_EOK;
}

static rt_err_t ft32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct ft32_uart *uart;
#ifdef RT_SERIAL_USING_DMA
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ft32_uart, serial);

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->config->irq_type);
        /* disable interrupt */
        USART_ITConfig(uart->config->Instance, USART_IT_RXNE, DISABLE);

#ifdef RT_SERIAL_USING_DMA
        /* disable DMA */
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX)
        {
            NVIC_DisableIRQ(uart->config->dma_rx->dma_irq);
            DMA_DeInit(uart->dma_rx.Instance);
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX)
        {
            NVIC_DisableIRQ(uart->config->dma_tx->dma_irq);
            DMA_DeInit(uart->dma_rx.Instance);
        }
#endif
        break;

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_SetPriority(uart->config->irq_type, 1);
        NVIC_EnableIRQ(uart->config->irq_type);
        /* enable interrupt */
        USART_ITConfig(uart->config->Instance, USART_IT_RXNE, ENABLE);
        break;

#ifdef RT_SERIAL_USING_DMA
    case RT_DEVICE_CTRL_CONFIG:
        ft32_dma_config(serial, ctrl_arg);
        break;
#endif

    case RT_DEVICE_CTRL_CLOSE:
        USART_DeInit(uart->config->Instance);
        break;

    }
    return RT_EOK;
}

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

static int ft32_putc(struct rt_serial_device *serial, char c)
{
    struct ft32_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ft32_uart, serial);
    UART_INSTANCE_CLEAR_FUNCTION(uart->config->Instance, USART_FLAG_TC);
#if defined(SOC_SERIES_FT32F0)
    uart->config->Instance->TDR = c;
#else
    uart->config->Instance->DR = c;
#endif
    while (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TC) == RESET);
    return 1;
}

static int ft32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct ft32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ft32_uart, serial);

    ch = -1;
    if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXNE) != RESET)
    {
#if defined(SOC_SERIES_FT32F0)
        ch = uart->config->Instance->RDR & ft32_uart_get_mask(uart->Init.USART_WordLength, uart->Init.USART_Parity);
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
#ifdef RT_SERIAL_USING_DMA
    rt_size_t recv_total_index, recv_len;
    rt_base_t level;
#endif

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ft32_uart, serial);

    /* UART in mode Receiver -------------------------------------------------*/
    if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXNE) != RESET)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
#ifdef RT_SERIAL_USING_DMA
    else if ((uart->uart_dma_flag) && (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXNE) != RESET))
    {
        level = rt_hw_interrupt_disable();
        recv_total_index = serial->config.bufsz - DMA_GetCurrDataCounter(&(uart->dma_rx.Instance));
        recv_len = recv_total_index - uart->dma_rx.last_index;
        uart->dma_rx.last_index = recv_total_index;
        rt_hw_interrupt_enable(level);

        if (recv_len)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
        }
        USART_ClearFlag(uart->config->Instance, USART_IT_IDLE);
    }
    else if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TC) != RESET)
    {
        if ((serial->parent.open_flag & RT_DEVICE_FLAG_DMA_TX) != 0)
        {

        }
        UART_INSTANCE_CLEAR_FUNCTION(uart->config->Instance, USART_FLAG_TC);
    }
#endif
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
#if !defined(SOC_SERIES_FT32F0)
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_LBD) != RESET)
        {
            UART_INSTANCE_CLEAR_FUNCTION(uart->config->Instance, USART_FLAG_LBD);
        }
#endif
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
}

#ifdef RT_SERIAL_USING_DMA
static void dma_isr(struct rt_serial_device *serial)
{
    struct ft32_uart *uart;
    rt_size_t recv_total_index, recv_len;
    rt_base_t level;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ft32_uart, serial);

    if ((DMA_GetITStatus(uart->dma_rx.Instance, DMA_IT_TC) != RESET) ||
            (DMA_GetITStatus(uart->dma_rx.Instance, DMA_IT_HT) != RESET))
    {
        level = rt_hw_interrupt_disable();
        recv_total_index = serial->config.bufsz - DMA_GetCurrDataCounter(uart->dma_rx.Instance);
        if (recv_total_index == 0)
        {
            recv_len = serial->config.bufsz - uart->dma_rx.last_index;
        }
        else
        {
            recv_len = recv_total_index - uart->dma_rx.last_index;
        }
        uart->dma_rx.last_index = recv_total_index;
        rt_hw_interrupt_enable(level);

        if (recv_len)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
        }
    }
}
#endif

#if defined(BSP_USING_UART1)
void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART1_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_RX_USING_DMA)
void UART1_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    __DMA_IRQHandler(uart_obj[UART1_INDEX].dma_rx.Instance);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA)
void UART1_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    __DMA_IRQHandler(uart_obj[UART1_INDEX].dma_tx.Instance);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA) */
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
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_RX_USING_DMA)
void UART2_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    __DMA_IRQHandler(uart_obj[UART2_INDEX].dma_rx.Instance);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_TX_USING_DMA)
void UART2_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    __DMA_IRQHandler(uart_obj[UART2_INDEX].dma_tx.Instance);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_TX_USING_DMA) */
#endif /* BSP_USING_UART2 */


static void ft32_uart_get_dma_config(void)
{
#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART1_RX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart1_dma_rx = UART1_DMA_RX_CONFIG;
    uart_config[UART1_INDEX].dma_rx = &uart1_dma_rx;
#endif
#ifdef BSP_UART1_TX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart1_dma_tx = UART1_DMA_TX_CONFIG;
    uart_config[UART1_INDEX].dma_tx = &uart1_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART2
    uart_obj[UART2_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART2_RX_USING_DMA
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart2_dma_rx = UART2_DMA_RX_CONFIG;
    uart_config[UART2_INDEX].dma_rx = &uart2_dma_rx;
#endif
#ifdef BSP_UART2_TX_USING_DMA
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart2_dma_tx = UART2_DMA_TX_CONFIG;
    uart_config[UART2_INDEX].dma_tx = &uart2_dma_tx;
#endif
#endif
}

#ifdef RT_SERIAL_USING_DMA
static void ft32_dma_config(struct rt_serial_device *serial, rt_ubase_t flag)
{
    struct rt_serial_rx_fifo *rx_fifo;

    DMA_InitTypeDef Init;
    struct dma_config *dma_config;
    struct ft32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(flag == RT_DEVICE_FLAG_DMA_TX || flag == RT_DEVICE_FLAG_DMA_RX);
    uart = rt_container_of(serial, struct ft32_uart, serial);

    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        Init = &uart->dma_rx.Init;
        dma_config = uart->config->dma_rx;
    }
    else /* RT_DEVICE_FLAG_DMA_TX == flag */
    {
        Init = &uart->dma_tx.Init;
        dma_config = uart->config->dma_tx;
    }
    LOG_D("%s dma config start", uart->config->name);

    {
        rt_uint32_t tmpreg = 0x00U;
#if defined(SOC_SERIES_FT32F0)
        /* enable DMA clock && Delay after an RCC peripheral clock enabling*/
        SET_BIT(RCC->AHBENR, dma_config->dma_rcc);
        tmpreg = READ_BIT(RCC->AHBENR, dma_config->dma_rcc);
#endif

        (void)(tmpreg);   /* To avoid compiler warnings */
    }

    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
    }
    else if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
    }

    Init.DMA_PeripheralInc   =  DMA_PeripheralInc_Disable;
    Init.MemInc              = DMA_MemoryInc_Enable;
    Init.PeriphDataAlignment = DMA_PeripheralDataSize_Byte;
    Init.MemDataAlignment    = DMA_MemoryDataSize_Byte;

    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        Init.Direction           = DMA_DIR_PeripheralSRC;
        Init.Mode                = DMA_Mode_Circular;
    }
    else if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
        Init.Direction           = DMA_DIR_PeripheralDST;
        Init.Mode                = DMA_Mode_Normal;
    }

    Init.Priority            = DMA_Priority_Medium;
    DMA_DeInit(dma_config->Instance);
    DMA_Init(dma_config->Instance);

    /* enable interrupt */
    if (flag == RT_DEVICE_FLAG_DMA_RX)
    {
        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
        /* Start DMA transfer */
        UART_Receive_DMA(uart->config->Instance, rx_fifo->buffer, serial->config.bufsz);
        CLEAR_BIT(uart->handle.Instance->CR3, USART_CR3_EIE);
        USART_ITConfig(uart->config->Instance, USART_IT_IDLE, ENABLE);
    }

    /* DMA irq should set in DMA TX mode, or HAL_UART_TxCpltCallback function will not be called */
    NVIC_SetPriority(dma_config->dma_irq, 0, 0);
    NVIC_EnableIRQ(dma_config->dma_irq);

    NVIC_SetPriority(uart->config->irq_type, 1, 0);
    NVIC_EnableIRQ(uart->config->irq_type);

    LOG_D("%s dma %s instance: %x", uart->config->name, flag == RT_DEVICE_FLAG_DMA_RX ? "RX" : "TX", DMA_Handle->Instance);
    LOG_D("%s dma config done", uart->config->name);
}

static void _dma_tx_complete(struct rt_serial_device *serial)
{
    struct ft32_uart *uart;
    rt_size_t trans_total_index;
    rt_base_t level;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ft32_uart, serial);

    level = rt_hw_interrupt_disable();
    trans_total_index = DMA_GetCurrDataCounter(uart->dma_tx.Instance);
    rt_hw_interrupt_enable(level);

    if (trans_total_index == 0)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
    }
}


#endif  /* RT_SERIAL_USING_DMA */

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
