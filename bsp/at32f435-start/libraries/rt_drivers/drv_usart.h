/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author              Notes
 * 2022-04-18     Dozingfiretruck     first version
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_common.h>

int rt_hw_usart_init(void);

/* at32 config class */
struct at32_uart_config
{
    const char *name;
    usart_type *Instance;
    IRQn_Type irq_type;
};

/* at32 uart dirver class */
struct at32_uart
{
    struct at32_uart_config *config;
    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};

#endif /* __DRV_USART_H__ */

/******************* end of file *******************/
