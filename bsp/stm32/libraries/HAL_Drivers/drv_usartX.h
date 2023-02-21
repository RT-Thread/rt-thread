/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-10     THEWON       first version for serialX
 */

#ifndef __DRV_USARTX_H__
#define __DRV_USARTX_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "drv_dma.h"

int rt_hw_usart_init(void);

#if defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) \
    || defined(SOC_SERIES_STM32L0) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32WB)|| defined(SOC_SERIES_STM32F3)
#define DMA_INSTANCE_TYPE              DMA_Channel_TypeDef
#elif defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) \
    || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32MP1)
#define DMA_INSTANCE_TYPE              DMA_Stream_TypeDef
#endif /*  defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) */

#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32F2) \
    || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32L0) || defined(SOC_SERIES_STM32G0) \
    || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32WB)|| defined(SOC_SERIES_STM32F3)
#define UART_INSTANCE_CLEAR_FUNCTION    __HAL_UART_CLEAR_FLAG
#elif defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32H7) \
    || defined(SOC_SERIES_STM32MP1)
#define UART_INSTANCE_CLEAR_FUNCTION    __HAL_UART_CLEAR_IT
#endif

/* stm32 config class */
struct stm32_uart_config
{
    const char *name;
    USART_TypeDef *Instance;
    IRQn_Type irq_type;
    rt_uint32_t mask;
#ifdef RT_SERIAL_USING_DMA
    struct dma_config *dma_conf_rx;
    struct dma_config *dma_conf_tx;
#endif
};

/* stm32 uart driver class */
struct stm32_uart
{
    UART_HandleTypeDef handle;
    struct rt_serial_device serial;
    struct stm32_uart_config *uart_config;

#ifdef RT_SERIAL_USING_DMA
    rt_bool_t dmaTxing;
    struct
    {
        DMA_HandleTypeDef handle;
    } dma_rx;
    struct
    {
        DMA_HandleTypeDef handle;
    } dma_tx;
    rt_uint16_t uart_dma_flag;
#endif
};

#endif  /* __DRV_USART_H__ */
