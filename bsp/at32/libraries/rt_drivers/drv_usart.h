/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-04     shelton      first version
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_dma.h"

struct at32_uart {
    char *name;
    usart_type *uart_x;
    IRQn_Type irqn;
    struct dma_config *dma_rx;
    rt_size_t last_index;
    struct dma_config *dma_tx;
    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};

int rt_hw_usart_init(void);

#endif /* __DRV_USART_H__ */

/******************* end of file *******************/
