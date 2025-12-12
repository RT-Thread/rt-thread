/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-07-22     kurisaw           first version
 */

#ifndef __DRV_RS485_H__
#define __DRV_RS485_H__

#include <rtthread.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RS485_SEND_MODE      0
#define RS485_RECV_MODE      1

extern int rs485_send_data(const void *tbuf, rt_uint16_t t_len);
extern int rs485_init(void);
#ifdef __cplusplus
}
#endif

#endif /* drv_rs485.h */
