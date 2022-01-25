/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-02     spaceman           first version
 */

#ifndef DRV_UART_H__
#define DRV_UART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>


int rt_hw_uart_init(void);

/* uart driver */
struct tkm32_uart
{
    UART_TypeDef *uart;
    IRQn_Type irq;
};



#endif
