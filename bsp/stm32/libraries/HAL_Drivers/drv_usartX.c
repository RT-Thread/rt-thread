/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-10     THEWON       first version for serialX
 */

#include "board.h"
#include "drv_usartX.h"
#include "drv_config.h"

#ifdef RT_USING_SERIAL

//#define DRV_DEBUG
#define LOG_TAG             "drv.usart"
#include <drv_log.h>

#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && \
    !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8) && !defined(BSP_USING_LPUART1)
#error "Please define at least one BSP_USING_UARTx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

#ifdef RT_SERIAL_USING_DMA
static void stm32_dma_rx_config(struct rt_serial_device *serial);
static void stm32_dma_tx_config(struct rt_serial_device *serial);
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
#ifdef BSP_USING_LPUART1
    LPUART1_INDEX,
#endif
};

static struct stm32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif
#ifdef BSP_USING_UART2
    UART2_CONFIG,
#endif
#ifdef BSP_USING_UART3
    UART3_CONFIG,
#endif
#ifdef BSP_USING_UART4
    UART4_CONFIG,
#endif
#ifdef BSP_USING_UART5
    UART5_CONFIG,
#endif
#ifdef BSP_USING_UART6
    UART6_CONFIG,
#endif
#ifdef BSP_USING_UART7
    UART7_CONFIG,
#endif
#ifdef BSP_USING_UART8
    UART8_CONFIG,
#endif
#ifdef BSP_USING_LPUART1
    LPUART1_CONFIG,
#endif
};

static struct stm32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static rt_uint32_t stm32_uart_get_mask(rt_uint32_t word_length, rt_uint32_t parity)
{
    rt_uint32_t mask;
    if (word_length == UART_WORDLENGTH_8B)
    {
        if (parity == UART_PARITY_NONE)
        {
            mask = 0x00FFU ;
        }
        else
        {
            mask = 0x007FU ;
        }
    }
#ifdef UART_WORDLENGTH_9B
    else if (word_length == UART_WORDLENGTH_9B)
    {
        if (parity == UART_PARITY_NONE)
        {
            mask = 0x01FFU ;
        }
        else
        {
            mask = 0x00FFU ;
        }
    }
#endif
#ifdef UART_WORDLENGTH_7B
    else if (word_length == UART_WORDLENGTH_7B)
    {
        if (parity == UART_PARITY_NONE)
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
#endif
    return mask;
}

static rt_err_t stm32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct stm32_uart, serial);
    uart->handle.Instance          = uart->uart_config->Instance;
    uart->handle.Init.BaudRate     = cfg->baud_rate;
    uart->handle.Init.Mode         = UART_MODE_TX_RX;
    uart->handle.Init.OverSampling = UART_OVERSAMPLING_16;

    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_NONE:
        uart->handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        break;
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
        uart->handle.Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS;
        break;
    default:
        uart->handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        break;
    }

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        if (cfg->parity == PARITY_ODD || cfg->parity == PARITY_EVEN)
            uart->handle.Init.WordLength = UART_WORDLENGTH_9B;
        else
            uart->handle.Init.WordLength = UART_WORDLENGTH_8B;
        break;
    case DATA_BITS_9:
        uart->handle.Init.WordLength = UART_WORDLENGTH_9B;
        break;
    default:
        uart->handle.Init.WordLength = UART_WORDLENGTH_8B;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->handle.Init.StopBits   = UART_STOPBITS_1;
        break;
    case STOP_BITS_2:
        uart->handle.Init.StopBits   = UART_STOPBITS_2;
        break;
    default:
        uart->handle.Init.StopBits   = UART_STOPBITS_1;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart->handle.Init.Parity     = UART_PARITY_NONE;
        break;
    case PARITY_ODD:
        uart->handle.Init.Parity     = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        uart->handle.Init.Parity     = UART_PARITY_EVEN;
        break;
    default:
        uart->handle.Init.Parity     = UART_PARITY_NONE;
        break;
    }

    uart->uart_config->mask = stm32_uart_get_mask(uart->handle.Init.WordLength, uart->handle.Init.Parity);
    if (HAL_UART_Init(&uart->handle) != HAL_OK)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t stm32_init(struct rt_serial_device *serial)
{
    if (stm32_configure(serial, &serial->config) != RT_EOK)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t stm32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct stm32_uart *uart;
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct stm32_uart, serial);

    switch (cmd) {
    case RT_DEVICE_CTRL_OPEN:
        __HAL_UART_DISABLE_IT(&(uart->handle), UART_IT_TXE);
        UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_RXNE);
        UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_TXE);
        UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_TC);
        /* enable interrupt */
        HAL_NVIC_SetPriority(uart->uart_config->irq_type, 1, 0);
        HAL_NVIC_EnableIRQ(uart->uart_config->irq_type);
#ifdef RT_SERIAL_USING_DMA
        uart->dmaTxing = RT_FALSE;
#endif
    break;
    case RT_DEVICE_CTRL_CLOSE:
        HAL_NVIC_DisableIRQ(uart->uart_config->irq_type);
#ifdef RT_SERIAL_USING_DMA
        HAL_NVIC_DisableIRQ(uart->uart_config->dma_conf_rx->dma_irq);
        if (HAL_DMA_Abort(&(uart->dma_rx.handle)) != HAL_OK) {
            RT_ASSERT(0);
        }
        if (HAL_DMA_DeInit(&(uart->dma_rx.handle)) != HAL_OK) {
            RT_ASSERT(0);
        }

        HAL_NVIC_DisableIRQ(uart->uart_config->dma_conf_tx->dma_irq);
        if (HAL_DMA_Abort(&(uart->dma_tx.handle)) != HAL_OK) {
            RT_ASSERT(0);
        }
        if (HAL_DMA_DeInit(&(uart->dma_tx.handle)) != HAL_OK) {
            RT_ASSERT(0);
        }
#endif
        __HAL_UART_DISABLE_IT(&(uart->handle), UART_IT_RXNE);
        __HAL_UART_DISABLE_IT(&(uart->handle), UART_IT_TXE);
        if (HAL_UART_DeInit(&(uart->handle)) != HAL_OK ) {
        }
    break;
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable interrupt */
        if (ctrl_arg & RT_DEVICE_FLAG_INT_RX) {
            __HAL_UART_DISABLE_IT(&(uart->handle), UART_IT_RXNE);
        }

#ifdef RT_SERIAL_USING_DMA
        /* disable DMA */
        if (ctrl_arg & RT_DEVICE_FLAG_DMA_RX) {
            HAL_NVIC_DisableIRQ(uart->uart_config->dma_conf_rx->dma_irq);
        }
        if(ctrl_arg & RT_DEVICE_FLAG_DMA_TX) {
            HAL_NVIC_DisableIRQ(uart->uart_config->dma_conf_tx->dma_irq);
        }
#endif
    break;
    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        if (ctrl_arg & RT_DEVICE_FLAG_INT_RX) {
            __HAL_UART_ENABLE_IT(&(uart->handle), UART_IT_RXNE);
        }
    break;
#ifdef RT_SERIAL_USING_DMA
    case RT_DEVICE_CTRL_CONFIG:
        if (ctrl_arg & RT_DEVICE_FLAG_DMA_RX) {
            stm32_dma_rx_config(serial);
        } else if (ctrl_arg & RT_DEVICE_FLAG_DMA_TX) {
            stm32_dma_tx_config(serial);
        }
    break;
#endif
    default :
    break;
    }
    return RT_EOK;
}

static int stm32_putc(struct rt_serial_device *serial, char c)
{
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct stm32_uart, serial);

    while (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_TXE) == RESET);
    UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_TC);
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32F0) \
    || defined(SOC_SERIES_STM32L0) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32H7) \
    || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32F3)
    uart->handle.Instance->TDR = c;
#else
    uart->handle.Instance->DR = c;
#endif
    return 1;
}

static int stm32_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct stm32_uart, serial);

    if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_RXNE) == RESET)
    {
        return -1;
    }
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32F0) \
    || defined(SOC_SERIES_STM32L0) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32H7) \
    || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB)|| defined(SOC_SERIES_STM32F3)
    ch = uart->handle.Instance->RDR & uart->uart_config->mask;
#else
    ch = uart->handle.Instance->DR & uart->uart_config->mask;
#endif
    return ch;
}

static int stm32_flush(struct rt_serial_device *serial)
{
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct stm32_uart, serial);
    while (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_TC) == RESET);

    return 1;
}

static void stm32_start_tx(struct rt_serial_device *serial)
{
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct stm32_uart, serial);
    __HAL_UART_ENABLE_IT(&(uart->handle), UART_IT_TXE);
}

static void stm32_stop_tx(struct rt_serial_device *serial)
{
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct stm32_uart, serial);
    __HAL_UART_DISABLE_IT(&(uart->handle), UART_IT_TXE);
}

#ifdef RT_SERIAL_USING_DMA
static rt_bool_t stm32_is_dma_txing(struct rt_serial_device *serial)
{
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct stm32_uart, serial);

    return uart->dmaTxing;  //RT_FALSE;
}

static void stm32_start_dma_tx(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size)
{
    struct stm32_uart *uart;
    HAL_StatusTypeDef status;
    DMA_HandleTypeDef *hdma;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct stm32_uart, serial);

    do {        // may fallin dead loop
        status = HAL_UART_Transmit_DMA(&uart->handle, buf, size);
    } while (status != HAL_OK);
    uart->dmaTxing = RT_TRUE;
}

static void stm32_stop_dma_tx(struct rt_serial_device *serial)
{
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct stm32_uart, serial);

    if ((uart->dma_tx.handle.Instance->CR & DMA_SxCR_EN) == DMA_SxCR_EN) {
        return;
    }
    __HAL_DMA_DISABLE(&uart->dma_tx.handle);
    uart->dmaTxing = RT_FALSE;
}
#endif

static void stm32_enable_interrupt(struct rt_serial_device *serial)
{
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct stm32_uart, serial);

    HAL_NVIC_EnableIRQ(uart->uart_config->irq_type);
#ifdef RT_SERIAL_USING_DMA
    if (uart->uart_dma_flag) {
        HAL_NVIC_EnableIRQ(uart->uart_config->dma_conf_rx->dma_irq);
    }
#endif
}

static void stm32_disable_interrupt(struct rt_serial_device *serial)
{
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct stm32_uart, serial);

    HAL_NVIC_DisableIRQ(uart->uart_config->irq_type);
#ifdef RT_SERIAL_USING_DMA
    if (uart->uart_dma_flag) {
        HAL_NVIC_DisableIRQ(uart->uart_config->dma_conf_rx->dma_irq);
    }
#endif
}

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct stm32_uart *uart;
#ifdef RT_SERIAL_USING_DMA
    rt_size_t dma_cnt;
#endif

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct stm32_uart, serial);

    /* UART in mode Receiver -------------------------------------------------*/
    if ((__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_RXNE) != RESET) &&
        (__HAL_UART_GET_IT_SOURCE(&(uart->handle), UART_IT_RXNE) != RESET))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    if ((__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_TXE) != RESET) &&
        (__HAL_UART_GET_IT_SOURCE(&(uart->handle), UART_IT_TXE) != RESET))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
    }
#ifdef RT_SERIAL_USING_DMA
    else if ((uart->uart_dma_flag) && (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_IDLE) != RESET)
             && (__HAL_UART_GET_IT_SOURCE(&(uart->handle), UART_IT_IDLE) != RESET))
    {
        __HAL_UART_CLEAR_IDLEFLAG(&uart->handle);
        dma_cnt = RT_SERIAL_DMA_BUFSZ - __HAL_DMA_GET_COUNTER(&(uart->dma_rx.handle));

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (dma_cnt << 8));
    }
    else if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_TC) &&
            (__HAL_UART_GET_IT_SOURCE(&(uart->handle), UART_IT_TC) != RESET))
    {
        if ((serial->parent.open_flag & RT_DEVICE_FLAG_DMA_TX) != 0)
        {
            HAL_UART_IRQHandler(&(uart->handle));
        }
    }
#endif
    else
    {
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_ORE) != RESET)
        {
            __HAL_UART_CLEAR_OREFLAG(&uart->handle);
        }
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_NE) != RESET)
        {
            __HAL_UART_CLEAR_NEFLAG(&uart->handle);
        }
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_FE) != RESET)
        {
            __HAL_UART_CLEAR_FEFLAG(&uart->handle);
        }
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_PE) != RESET)
        {
            __HAL_UART_CLEAR_PEFLAG(&uart->handle);
        }
#if !defined(SOC_SERIES_STM32L4) && !defined(SOC_SERIES_STM32WL) && !defined(SOC_SERIES_STM32F7) && !defined(SOC_SERIES_STM32F0) \
    && !defined(SOC_SERIES_STM32L0) && !defined(SOC_SERIES_STM32G0) && !defined(SOC_SERIES_STM32H7) \
    && !defined(SOC_SERIES_STM32G4) && !defined(SOC_SERIES_STM32MP1) && !defined(SOC_SERIES_STM32WB)
#ifdef SOC_SERIES_STM32F3
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_LBDF) != RESET)
        {
            UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_LBDF);
        }
#else
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_LBD) != RESET)
        {
            UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_LBD);
        }
#endif
#endif
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_CTS) != RESET)
        {
            UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_CTS);
        }
//        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_TXE) != RESET)
//        {
//            UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_TXE);
//        }
//        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_TC) != RESET)
//        {
//            UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_TC);
//        }
//        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_RXNE) != RESET)
//        {
//            UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_RXNE);
//        }
    }
}

#ifdef RT_SERIAL_USING_DMA
static void dma_isr(struct rt_serial_device *serial)
{
    struct stm32_uart *uart;
    rt_size_t dma_cnt;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct stm32_uart, serial);

    if ((__HAL_DMA_GET_IT_SOURCE(&(uart->dma_rx.handle), DMA_IT_TC) != RESET) ||
        (__HAL_DMA_GET_IT_SOURCE(&(uart->dma_rx.handle), DMA_IT_HT) != RESET))
    {
        dma_cnt = RT_SERIAL_DMA_BUFSZ - __HAL_DMA_GET_COUNTER(&(uart->dma_rx.handle));

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (dma_cnt << 8));
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

    HAL_DMA_IRQHandler(&uart_obj[UART1_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA)
void UART1_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART1_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA) */
#endif /* BSP_USING_UART1 */

#ifdef RT_SERIAL_USING_DMA
static void stm32_uart_get_dma_config(void)
{
#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART1_RX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart1_dma_rx = UART1_DMA_RX_CONFIG;
    uart_config[UART1_INDEX].dma_conf_rx = &uart1_dma_rx;
#endif
#ifdef BSP_UART1_TX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart1_dma_tx = UART1_DMA_TX_CONFIG;
    uart_config[UART1_INDEX].dma_conf_tx = &uart1_dma_tx;
#endif
#endif
}

static void stm32_dma_rx_config(struct rt_serial_device *serial)
{
    DMA_HandleTypeDef *DMA_Handle;
    struct dma_config *dma_config;
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct stm32_uart, serial);

    DMA_Handle = &uart->dma_rx.handle;
    dma_config = uart->uart_config->dma_conf_rx;

    LOG_D("%s dma config start", uart->uart_config->name);

    {
        rt_uint32_t tmpreg = 0x00U;
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0) \
    || defined(SOC_SERIES_STM32L0)|| defined(SOC_SERIES_STM32F3) || defined(SOC_SERIES_STM32L1)
        /* enable DMA clock && Delay after an RCC peripheral clock enabling*/
        SET_BIT(RCC->AHBENR, dma_config->dma_rcc);
        tmpreg = READ_BIT(RCC->AHBENR, dma_config->dma_rcc);
#elif defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) \
    || defined(SOC_SERIES_STM32G4)|| defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32WB)
        /* enable DMA clock && Delay after an RCC peripheral clock enabling*/
        SET_BIT(RCC->AHB1ENR, dma_config->dma_rcc);
        tmpreg = READ_BIT(RCC->AHB1ENR, dma_config->dma_rcc);
#elif defined(SOC_SERIES_STM32MP1)
        /* enable DMA clock && Delay after an RCC peripheral clock enabling*/
        SET_BIT(RCC->MP_AHB2ENSETR, dma_config->dma_rcc);
        tmpreg = READ_BIT(RCC->MP_AHB2ENSETR, dma_config->dma_rcc);
#endif

#if (defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32WB)) && defined(DMAMUX1)
        /* enable DMAMUX clock for L4+ and G4 */
        __HAL_RCC_DMAMUX1_CLK_ENABLE();
#elif defined(SOC_SERIES_STM32MP1)
        __HAL_RCC_DMAMUX_CLK_ENABLE();
#endif

        UNUSED(tmpreg);   /* To avoid compiler warnings */
    }

    __HAL_LINKDMA(&(uart->handle), hdmarx, uart->dma_rx.handle);

#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32L0)|| defined(SOC_SERIES_STM32F3) || defined(SOC_SERIES_STM32L1)
    DMA_Handle->Instance                 = dma_config->Instance;
#elif defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
    DMA_Handle->Instance                 = dma_config->Instance;
    DMA_Handle->Init.Channel             = dma_config->channel;
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32WB)\
    || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32MP1)
    DMA_Handle->Instance                 = dma_config->Instance;
    DMA_Handle->Init.Request             = dma_config->request;
#endif
    DMA_Handle->Init.PeriphInc           = DMA_PINC_DISABLE;
    DMA_Handle->Init.MemInc              = DMA_MINC_ENABLE;
    DMA_Handle->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    DMA_Handle->Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;

    DMA_Handle->Init.Direction           = DMA_PERIPH_TO_MEMORY;
    DMA_Handle->Init.Mode                = DMA_CIRCULAR;

    DMA_Handle->Init.Priority            = DMA_PRIORITY_MEDIUM;
#if defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32MP1)
    DMA_Handle->Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
#endif
    if (HAL_DMA_DeInit(DMA_Handle) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    if (HAL_DMA_Init(DMA_Handle) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    /* enable interrupt */
    /* Start DMA transfer */
    if (HAL_UART_Receive_DMA(&(uart->handle), serial->serial_dma_rx, RT_SERIAL_DMA_BUFSZ) != HAL_OK)
    {
        /* Transfer error in reception process */
        RT_ASSERT(0);
    }
    CLEAR_BIT(uart->handle.Instance->CR3, USART_CR3_EIE);
    __HAL_UART_ENABLE_IT(&(uart->handle), UART_IT_IDLE);

    /* DMA irq should set in DMA TX mode, or HAL_UART_TxCpltCallback function will not be called */
    HAL_NVIC_SetPriority(dma_config->dma_irq, 0, 0);
    HAL_NVIC_EnableIRQ(dma_config->dma_irq);
}

static void stm32_dma_tx_config(struct rt_serial_device *serial)
{
    DMA_HandleTypeDef *DMA_Handle;
    struct dma_config *dma_config;
    struct stm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct stm32_uart, serial);

    DMA_Handle = &uart->dma_tx.handle;
    dma_config = uart->uart_config->dma_conf_tx;

    LOG_D("%s dma config start", uart->uart_config->name);

    {
        rt_uint32_t tmpreg = 0x00U;
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0) \
    || defined(SOC_SERIES_STM32L0)|| defined(SOC_SERIES_STM32F3) || defined(SOC_SERIES_STM32L1)
        /* enable DMA clock && Delay after an RCC peripheral clock enabling*/
        SET_BIT(RCC->AHBENR, dma_config->dma_rcc);
        tmpreg = READ_BIT(RCC->AHBENR, dma_config->dma_rcc);
#elif defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) \
    || defined(SOC_SERIES_STM32G4)|| defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32WB)
        /* enable DMA clock && Delay after an RCC peripheral clock enabling*/
        SET_BIT(RCC->AHB1ENR, dma_config->dma_rcc);
        tmpreg = READ_BIT(RCC->AHB1ENR, dma_config->dma_rcc);
#elif defined(SOC_SERIES_STM32MP1)
        /* enable DMA clock && Delay after an RCC peripheral clock enabling*/
        SET_BIT(RCC->MP_AHB2ENSETR, dma_config->dma_rcc);
        tmpreg = READ_BIT(RCC->MP_AHB2ENSETR, dma_config->dma_rcc);
#endif

#if (defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32WB)) && defined(DMAMUX1)
        /* enable DMAMUX clock for L4+ and G4 */
        __HAL_RCC_DMAMUX1_CLK_ENABLE();
#elif defined(SOC_SERIES_STM32MP1)
        __HAL_RCC_DMAMUX_CLK_ENABLE();
#endif

        UNUSED(tmpreg);   /* To avoid compiler warnings */
    }

    __HAL_LINKDMA(&(uart->handle), hdmatx, uart->dma_tx.handle);


#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32L0)|| defined(SOC_SERIES_STM32F3) || defined(SOC_SERIES_STM32L1)
    DMA_Handle->Instance                 = dma_config->Instance;
#elif defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
    DMA_Handle->Instance                 = dma_config->Instance;
    DMA_Handle->Init.Channel             = dma_config->channel;
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32WB)\
    || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32MP1)
    DMA_Handle->Instance                 = dma_config->Instance;
    DMA_Handle->Init.Request             = dma_config->request;
#endif
    DMA_Handle->Init.PeriphInc           = DMA_PINC_DISABLE;
    DMA_Handle->Init.MemInc              = DMA_MINC_ENABLE;
    DMA_Handle->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    DMA_Handle->Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;

    DMA_Handle->Init.Direction           = DMA_MEMORY_TO_PERIPH;
    DMA_Handle->Init.Mode                = DMA_NORMAL;

    DMA_Handle->Init.Priority            = DMA_PRIORITY_MEDIUM;
#if defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32MP1)
    DMA_Handle->Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
#endif
    if (HAL_DMA_DeInit(DMA_Handle) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    if (HAL_DMA_Init(DMA_Handle) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    /* DMA irq should set in DMA TX mode, or HAL_UART_TxCpltCallback function will not be called */
    HAL_NVIC_SetPriority(dma_config->dma_irq, 0, 0);
    HAL_NVIC_EnableIRQ(dma_config->dma_irq);
}

/**
  * @brief  UART error callbacks
  * @param  huart: UART handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    struct stm32_uart *uart;

    RT_ASSERT(huart != NULL);

    uart = (struct stm32_uart *)huart;
    LOG_D("%s: %s %d\n", __FUNCTION__, uart->uart_config->name, huart->ErrorCode);
    UNUSED(uart);
}

/**
  * @brief  Rx Transfer completed callback
  * @param  huart: UART handle
  * @note   This example shows a simple way to report end of DMA Rx transfer, and
  *         you can add your own implementation.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    struct stm32_uart *uart;

    RT_ASSERT(huart != NULL);

    uart = (struct stm32_uart *)huart;
    dma_isr(&uart->serial);
}

/**
  * @brief  Rx Half transfer completed callback
  * @param  huart: UART handle
  * @note   This example shows a simple way to report end of DMA Rx Half transfer,
  *         and you can add your own implementation.
  * @retval None
  */
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
    struct stm32_uart *uart;

    RT_ASSERT(huart != NULL);

    uart = (struct stm32_uart *)huart;
    dma_isr(&uart->serial);
}

/**
  * @brief  HAL_UART_TxCpltCallback
  * @param  huart: UART handle
  * @note   This callback can be called by two functions, first in UART_EndTransmit_IT when
  *         UART Tx complete and second in UART_DMATransmitCplt function in DMA Circular mode.
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    struct stm32_uart *uart;
    rt_size_t dma_cnt;

    RT_ASSERT(huart != NULL);

    uart = (struct stm32_uart *)huart;

    dma_cnt = __HAL_DMA_GET_COUNTER(&(uart->dma_tx.handle));

    if (dma_cnt == 0)
    {
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DMADONE);
    }
}
#endif  /* RT_SERIAL_USING_DMA */

static const struct rt_uart_ops stm32_uart_ops =
{
    .init = stm32_init,
    .configure = stm32_configure,
    .control = stm32_control,
    .putc = stm32_putc,
    .getc = stm32_getc,
    .flush = stm32_flush,
    .start_tx = stm32_start_tx,
    .stop_tx = stm32_stop_tx,
#ifdef RT_SERIAL_USING_DMA
    .is_dma_txing = stm32_is_dma_txing,
    .start_dma_tx = stm32_start_dma_tx,
    .stop_dma_tx = stm32_stop_dma_tx,
#endif
    .enable_interrupt = stm32_enable_interrupt,
    .disable_interrupt = stm32_disable_interrupt,
};

int rt_hw_usart_init(void)
{
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct stm32_uart);
    rt_err_t result = 0;

#ifdef RT_SERIAL_USING_DMA
    stm32_uart_get_dma_config();
#endif

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].uart_config = &uart_config[i];
        uart_obj[i].serial.ops = &stm32_uart_ops;

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].uart_config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX
#ifdef RT_SERIAL_USING_DMA
                                       | uart_obj[i].uart_dma_flag
#endif
                                       , NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL */
