/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-07-17     aubrcool@qq.com   1st version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "i2c/fm24clxx.h"

const struct fm24clxx_config fm24cl64_cfg =
{
    .size  = 8 * 1024,
    .addr  = 0x50,
    .flags = 0,
};

int rt_hw_fm24cl64_init(const char *fm_device_name, const char *i2c_bus)
{
    return fm24clxx_register(fm_device_name, i2c_bus, (void *)&fm24cl64_cfg);
}
