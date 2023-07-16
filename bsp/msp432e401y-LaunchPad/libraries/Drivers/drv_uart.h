/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-15     yby          the first version
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include "board.h"

/* msp432 config class */
struct msp432_uart_config
{
    const char *name;
    uint32_t    uartbase;
    uint32_t    baudrate;
    uint32_t    mode;
};

/* msp432 uart dirver class */
struct msp432_uart
{
    struct msp432_uart_config *config;
    uint32_t   uartintbase;
#ifdef RT_SERIAL_USING_DMA

#endif
    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};

extern int rt_hw_usart_init(void);

#endif /*__DRV_UART_H__*/

/************************** end of file ******************/
