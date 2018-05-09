/*
 * File      : drv_usart.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-25     LongfeiMa    the first version for stm32h7xx
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rthw.h>
#include <rtthread.h>

#define UART_ENABLE_IRQ(n)            NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n)           NVIC_DisableIRQ((n))

int stm32_hw_usart_init(void);

#endif
