/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-31     CYFS         add GD32VW553 board port with hardware reset
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_GD32VW553_AT

#include <at_device_gd32vw553.h>

#define GD32VW553_DEVICE_NAME           "wifi0"
#define GD32VW553_CLIENT_NAME           "uart4"
#define GD32VW553_RESET_PIN             GET_PIN(C, 5)
#define GD32VW553_RECV_LINE_NUM         1024

static struct at_device_gd32vw553 gd32vw5530 =
{
    .device_name = GD32VW553_DEVICE_NAME,
    .client_name = GD32VW553_CLIENT_NAME,
    .wifi_ssid = BSP_GD32VW553_WIFI_SSID,
    .wifi_password = BSP_GD32VW553_WIFI_PASSWORD,
    .baudrate = BSP_GD32VW553_AT_BAUDRATE,
    .recv_line_num = GD32VW553_RECV_LINE_NUM,
    .use_reset_pin = RT_TRUE,
    .reset_pin = GD32VW553_RESET_PIN,
    .reset_active_level = PIN_LOW,
};

static int gd32vw553_device_register(void)
{
    return at_device_register(&gd32vw5530.device,
                              gd32vw5530.device_name,
                              gd32vw5530.client_name,
                              AT_DEVICE_CLASS_GD32VW553,
                              &gd32vw5530);
}
INIT_APP_EXPORT(gd32vw553_device_register);

#endif /* BSP_USING_GD32VW553_AT */
