/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtdevice.h>
#include <rtthread.h>
#include "drv_common.h"

struct at32_baud_rate
{
    rt_uint32_t baud_rate;
    can_baudrate_type baud_struct;
};

struct can_config
{
    can_type *can_x;
    can_base_type base_init_struct;
    can_baudrate_type baudrate_init_struct;
    can_filter_init_type filter_init_struct;
};

/* at32 can device */
struct at32_can
{
    char *name;
    struct can_config config;
    struct rt_can_device device;     /* inherit from can device */
};

int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_CAN_H__ */

/************************** end of file ******************/
