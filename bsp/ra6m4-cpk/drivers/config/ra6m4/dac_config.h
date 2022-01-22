/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-19     Mr.Tiger     first version
 */

#ifndef __DAC_CONFIG_H__
#define __DAC_CONFIG_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "hal_data.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_DAC
struct ra_dac_map
{
    char name;
    const struct st_dac_cfg *g_cfg;
    const struct st_dac_instance_ctrl *g_ctrl;
};

struct ra_dac_dev
{
    rt_dac_device_t       ra_dac_device_t;
    struct ra_dac_map    *ra_dac_map_dev;
};
#endif

#endif

#ifdef __cplusplus
}
#endif

