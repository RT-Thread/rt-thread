/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-12     Vandoul      the first version
 */

#ifndef __DRV_I2S_H__
#define __DRV_I2S_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtthread.h>

#pragma pack(push,1)
struct lpc_i2s_config
{
    uint32_t sampling_rate;
    uint8_t mode;
    uint8_t data_bits;
    uint8_t channels;
    uint8_t is_blocking;
};
#pragma pack(pop)

#define LPC_I2S_CONFIG_MODE_NULL                0
#define LPC_I2S_CONFIG_MODE_SLAVE               1
#define LPC_I2S_CONFIG_MODE_MASTER              2

#define RT_I2S_CTRL_RESET                       (RT_DEVICE_CTRL_BASE(Bus) + 1)
#define RT_I2S_CTRL_SET_CONFIG                  (RT_DEVICE_CTRL_BASE(Bus) + 2)

#ifdef __cplusplus
}
#endif

#endif

