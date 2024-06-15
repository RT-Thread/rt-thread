/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-10-29     mazhiyuan         first version
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_common.h>
#include <drv_config.h>
#include <hal_data.h>

/* renesas config class */
struct ra_can_config
{
    const char *name;
    int num_of_mailboxs;
    can_ctrl_t *const p_api_ctrl;
    can_cfg_t const *const p_cfg;
};

struct ra_can
{
    struct rt_can_device can_dev;
    struct ra_can_config *config;
    can_callback_args_t *callback_args;
};

struct ra_baud_rate_tab
{
    rt_uint32_t baud_rate;
    rt_uint32_t sjw;
    rt_uint32_t ts1;
    rt_uint32_t ts2;
    rt_uint32_t prescaler;
};

int rt_hw_can_init(void);

#endif
