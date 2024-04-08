/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-01     KyleChan     first version
 */

#ifndef __DRV_USART_V2_H__
#define __DRV_USART_V2_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_common.h>
#include <drv_dma.h>
#include <drv_config.h>

int rt_hw_usart_init(void);

#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32F0) \
    || defined(SOC_SERIES_STM32L0) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32H7) \
    || defined(SOC_SERIES_STM32G4)
#define UART_SET_TDR(__HANDLE__, __DATA__)  ((__HANDLE__)->Instance->TDR = (__DATA__))
#define UART_GET_RDR(__HANDLE__, MASK)            ((__HANDLE__)->Instance->RDR & MASK)

#else
#define UART_SET_TDR(__HANDLE__, __DATA__)  ((__HANDLE__)->Instance->DR = (__DATA__))
#define UART_GET_RDR(__HANDLE__, MASK)            ((__HANDLE__)->Instance->DR & MASK)
#endif


#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F2) \
    || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32L0) || defined(SOC_SERIES_STM32G0) \
    || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32WB)
#define UART_INSTANCE_CLEAR_FUNCTION    __HAL_UART_CLEAR_FLAG
#elif defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) \
    || defined(SOC_SERIES_STM32MP1)
#define UART_INSTANCE_CLEAR_FUNCTION    __HAL_UART_CLEAR_IT
#endif

#define UART_RX_DMA_IT_IDLE_FLAG        0x00
#define UART_RX_DMA_IT_HT_FLAG          0x01
#define UART_RX_DMA_IT_TC_FLAG          0x02


/* stm32 config class */
struct stm32_uart_config
{
    const char *name;
    USART_TypeDef *Instance;
    IRQn_Type irq_type;

#ifdef RT_SERIAL_USING_DMA
    struct dma_config *dma_rx;
    struct dma_config *dma_tx;
#endif
};

/* stm32 uart dirver class */
struct stm32_uart
{
    UART_HandleTypeDef handle;
    struct stm32_uart_config *config;

#ifdef RT_SERIAL_USING_DMA
    struct
    {
        DMA_HandleTypeDef handle;
        rt_size_t remaining_cnt;
    } dma_rx;
    struct
    {
        DMA_HandleTypeDef handle;
    } dma_tx;
#endif
    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};

#endif  /* __DRV_USART_H__ */
