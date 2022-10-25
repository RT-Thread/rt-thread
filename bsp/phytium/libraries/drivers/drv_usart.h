/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: drv_usart.h
 * Date: 2022-10-09 09:30:15
 * LastEditTime: 2022-10-09 09:30:15
 * Description:  This file is for 
 * 
 * Modify History: 
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 */
/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-04     Carl      the first version
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include "fpl011.h"
#include "fpl011_hw.h"

#define RTOS_UART_ISR_OEIM_MASK FPL011IMSC_OEIM  /* Overrun error interrupt mask.  */
#define RTOS_UART_ISR_BEIM_MASK FPL011IMSC_BEIM  /* Break error interrupt mask  */
#define RTOS_UART_ISR_PEIM_MASK FPL011IMSC_PEIM  /* Parity error interrupt mask.  */
#define RTOS_UART_ISR_FEIM_MASK FPL011IMSC_FEIM   /*  Framing error interrupt mask.  */
#define RTOS_UART_ISR_RTIM_MASK FPL011IMSC_RTIM   /* Receive timeout interrupt mask.   */
#define RTOS_UART_ISR_TXIM_MASK FPL011IMSC_TXIM   /* Transmit interrupt mask.  */
#define RTOS_UART_ISR_RXIM_MASK FPL011IMSC_RXIM   /*  Receive interrupt mask.  */


typedef struct
{
    u32 uart_instance; /* select uart global object */
    u32 isr_priority;  /* irq Priority */
    u32 isr_event_mask; /* followed by RTOS_UART_ISR_XX */
    u32 uart_baudrate;
}  FtFreertosUartConfig;


struct drv_usart
{
    FPl011 *handle;
    FtFreertosUartConfig config;
    struct rt_serial_device serial;
};

#endif // !
