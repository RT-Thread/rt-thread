/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-02-17     yeml           the first version
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef SOC_SERIES_TAE32G58xx
#include "tae32g58xx_ll_uart.h"
#include "config/g58xx/uart_config.h"
#endif

/*tae32_uart_config*/
struct tae32_uart_config
{
    const char *name;
    IRQn_Type irq_type;
};

/* tae32 uart dirver class */
struct tae32_uart
{
    struct rt_serial_device serial;

    UART_TypeDef *Instance;
    struct tae32_uart_config *config;
    rt_uint16_t dma_flag;
};


#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */
