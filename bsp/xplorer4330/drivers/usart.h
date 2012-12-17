/*
 * File      : usart.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-15     lgnq         modified according bernard's implementaion.
 */

#ifndef __USART_H__
#define __USART_H__

#include <rtthread.h>

#include "chip_lpc43xx.h"
#include "cmsis.h"

/**
 *  Enable/DISABLE Interrupt Controller
 */
#define UART_ENABLE_IRQ(n)            NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n)           NVIC_DisableIRQ((n))

struct uart_device
{
    LPC_USART_Type *uart_regs;

    /* irq number */
    IRQn_Type irq_num;
};

void rt_hw_serial_init(void);

#endif
