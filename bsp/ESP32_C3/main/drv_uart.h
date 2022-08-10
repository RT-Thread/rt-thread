/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-04     tangzz98     first version
 *
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_DEVICE
#include <rtdevice.h>
#endif

#include "driver/uart.h"
#include "hal/uart_hal.h"
#include "sdkconfig.h"

int rt_hw_uart_init(void);

#endif /* __DRV_UART_H__ */
