/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#ifdef __cplusplus
extern "C" {
#endif

int rt_hw_uart_init(void);

#if defined(SOC_SERIES_MM32F3277)

#include <drv_common.h>

#define DMA_INSTANCE_TYPE               MA_Channel_TypeDef
#define UART_INSTANCE_CLEAR_FUNCTION    __HAL_UART_CLEAR_FLAG

struct dma_config;

struct mm32_uart_config
{
    const char *name;
    UART_Type *Instance;
    IRQn_Type irq_type;
    struct dma_config *dma_rx;
    struct dma_config *dma_tx;
};

struct mm32_uart
{
    UART_Init_Type handle;
    struct mm32_uart_config *config;

#ifdef RT_SERIAL_USING_DMA
    struct
    {
        DMA_Type handle;
        rt_size_t last_index;
    } dma_rx;
#endif

    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};

#endif /* SOC_SERIES_MM32F3277 */

#ifdef __cplusplus
}
#endif

#endif /* __DRV_UART_H__ */
