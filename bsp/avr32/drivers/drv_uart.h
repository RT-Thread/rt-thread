/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2009-01-05     Bernard         first version
 * 2010-03-29     Bernard         remove interrupt tx and DMA rx mode.
 * 2010-03-30     Kyle            Ported from STM32 to AVR32.
 * 2023-10-25     Raman Gopalan   UART driver for at32uc3a: Initial version
 * 2023-11-06     Raman Gopalan   Driver abstractions for uc3a and uc3b devices
 */

#ifndef __RT_HW_SERIAL_H__
#define __RT_HW_SERIAL_H__

#include <rthw.h>
#include <rtthread.h>
#include "compiler.h"
#include "usart.h"

#define FOSC0   12000000

#ifndef BSP_BOARD_MIZAR32B
#define FCPU    60000000
#define FHSB    FCPU
#define FPBA    FCPU
#define FPBB    FCPU
#else
#define FCPU    66000000
#define FHSB    FCPU
#define FPBA    16500000
#define FPBB    FCPU
#endif

#define UART_RX_BUFFER_SIZE     64
#define UART_TX_DMA_NODE_SIZE   4

#ifdef RT_USING_SERIAL
int rt_hw_uart_init(void);
#endif

#endif
