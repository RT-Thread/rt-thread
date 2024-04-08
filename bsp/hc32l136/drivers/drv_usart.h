/*
 * Copyright (C) 2021, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-19     pjq          first version
 */


#ifndef __DRV_USART_H__
#define __DRV_USART_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include "rtdevice.h"

#include "ddl.h"
#include "uart.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/* HC32 config uart class */
struct hc32_uart_config
{
    const char *name;
    rt_uint8_t idx;
    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};

/* stm32 uart dirver class */
struct hc32_uart
{
    struct hc32_uart_config *config;
#ifdef RT_SERIAL_USING_DMA

#endif
    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
int rt_hw_uart_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_USART_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
