/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-28     xckhmf       Modify for <nrfx>
 * 2020-10-31     xckhmf       Support for UART1
 *
 */
#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#define RT_DEVICE_CTRL_CUSTOM   0x20
#define RT_DEVICE_CTRL_PIN      0x21
#define RT_DEVICE_POWERSAVE     0x22
#define RT_DEVICE_WAKEUP        0x23

#define UART_CONFIG_BAUD_RATE_9600      1
#define UART_CONFIG_BAUD_RATE_115200    2

void rt_hw_uart_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_UART_H__ */
