/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2020-01-14     wangyq        the first version
 */

#ifndef DRV_CAN_H__
#define DRV_CAN_H__

#include <board.h>
#include <rtdevice.h>
#include <rtthread.h>

#include <ald_can.h>
#include <ald_gpio.h>

struct es32f3_baud_rate_tab
{
    rt_uint32_t baud_rate;
    rt_uint32_t config_data;
};

/* es32f3 can device */
struct es32f3_can
{
    can_handle_t CanHandle;
    can_filter_t FilterConfig;
    struct rt_can_device device;     /* inherit from can device */
};

int rt_hw_can_init(void);

#endif /*DRV_CAN_H__ */
