/*
 * Copyright (c) 2020-2022, CQ 100ask Development Team
 *
 * Change Logs:
 *   Date           Author          Notes
 * 2022-05-29        Alen       first version
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>

int rt_hw_uart_init(void);

#define DMA_INSTANCE_TYPE               MA_Channel_TypeDef

#define UART_INSTANCE_CLEAR_FUNCTION    __HAL_UART_CLEAR_FLAG


/* mm32 config class */
struct mm32_uart_config
{
    const char *name;
    UART_Type *Instance;
    IRQn_Type irq_type;
    struct dma_config *dma_rx;
    struct dma_config *dma_tx;
};

/* mm32 uart dirver class */
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

#endif  /* __DRV_USART_H__ */
