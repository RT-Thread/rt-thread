/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022.03.02     FMD-AE       first version
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include "drv_dma.h"

int rt_hw_usart_init(void);

#if defined(SOC_SERIES_FT32F0)
    #define DMA_INSTANCE_TYPE              DMA_Channel_TypeDef
#endif

#if defined(SOC_SERIES_FT32F0)
    #define UART_INSTANCE_CLEAR_FUNCTION    USART_ClearITPendingBit
#endif

#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA

/* ft32 config class */
struct ft32_uart_config
{
    const char *name;
    USART_TypeDef *Instance;
    IRQn_Type irq_type;
    struct dma_config *dma_rx;
    struct dma_config *dma_tx;
};

/* ft32 uart dirver class */
struct ft32_uart
{
    USART_InitTypeDef Init;
    struct ft32_uart_config *config;

#ifdef RT_SERIAL_USING_DMA
    struct
    {
        DMA_InitTypeDef Init;
        DMA_Channel_TypeDef   *Instance;
        rt_size_t last_index;
    } dma_rx;
    struct
    {
        DMA_InitTypeDef Init;
        DMA_Channel_TypeDef   *Instance;
    } dma_tx;
#endif
    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};

#endif  /* __DRV_USART_H__ */
