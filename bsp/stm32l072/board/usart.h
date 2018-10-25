/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-15     bright       the first version
 */

#ifndef __USART_H__
#define __USART_H__

#include <rthw.h>
#include <rtthread.h>
#include "stm32l0xx.h"



#define UART_ENABLE_IRQ(n)            HAL_NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n)           HAL_NVIC_DisableIRQ((n))

#endif
