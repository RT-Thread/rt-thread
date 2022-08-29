/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018.10.30     SummerGift   first version
 * 2019.03.05     whj4674672   add stm32h7
 * 2020-10-14     Dozingfiretruck   Porting for stm32wbxx
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "board.h"

int rt_hw_usart_init(void);


/* stm32 config class */
struct _uart_config
{
    const char *name;
    void *InitTypeDef;
    IRQn_Type irq_type;
    uint32_t clockSrc;
};

/* stm32 uart dirver class */
struct _uart
{
    FL_UART_InitTypeDef  handle;
    struct _uart_config *config;
    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};

#endif  /* __DRV_USART_H__ */
