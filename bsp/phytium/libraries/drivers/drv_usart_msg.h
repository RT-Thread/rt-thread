/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2025-05-23  liyilun      first commit

 */

#ifndef __DRV_USART_MSG_H__
#define __DRV_USART_MSG_H__

#include <rtthread.h>
#include "rtdevice.h"

#include "fuart_msg.h"
#include "fuart_msg_hw.h"


#define RTOS_UART_MSG_RX_ISR_MASK         0x01
#define RTOS_UART_MSG_TX_ISR_MASK         0x02

typedef struct
{
    u32 uart_instance; /* select uart global object */
    u32 isr_priority;  /* irq Priority */
    u32 isr_event_mask; /* followed by RTOS_UART_ISR_XX */
    u32 uart_baudrate;
}  FtRtthreadUartMsgConfig;

struct drv_usart_msg
{
    const char *name;
    FUartMsg *handle;
    FtRtthreadUartMsgConfig config;
    struct rt_serial_device serial;
};

#endif // !
