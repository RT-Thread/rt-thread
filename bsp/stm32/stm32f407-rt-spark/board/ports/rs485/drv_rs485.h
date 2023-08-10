/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-10-24     thread-liu        first version
 */

#ifndef __DRV_RS485_H__
#define __DRV_RS485_H__

#ifdef __cplusplus
extern "C" {
#endif

#define RS485_SEND_MODE      0
#define RS485_RECV_MODE      1

extern rt_device_t rs485_serial;
extern struct rt_semaphore rs485_rx_sem;
extern int rs485_send_data(char *tbuf, rt_uint16_t t_len);
extern int rs485_init(void);
#ifdef __cplusplus
}
#endif

#endif /* drv_rs485.h */
