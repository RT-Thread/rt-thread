/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-23     Jonas        first version
 */

#ifndef __DRV_USART_V2_H__
#define __DRV_USART_V2_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_common.h>

struct at32_usart
{
    char *name;
    usart_type *usart_x;
    IRQn_Type irqn;
    struct rt_serial_device serial;
};

int rt_hw_usart_init(void);

#endif /* __DRV_USART_V2_H__ */
