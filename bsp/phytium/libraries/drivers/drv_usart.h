/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-10-26  huanghe      first commit
 * 2023-04-27  huanghe      support RT-Smart
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
}  FtRtthreadUartConfig;

struct drv_usart
{
    const char *name;
    FPl011 *handle;
    FtRtthreadUartConfig config;
    struct rt_serial_device serial;
};

#endif // !
