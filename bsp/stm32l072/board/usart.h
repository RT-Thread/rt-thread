/*
 * File      : usart.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
