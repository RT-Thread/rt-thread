/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-19     liYony       first version
 */

#include <rtthread.h>
#include "mpu6xxx.h"

#define DBG_TAG "mpu6050"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define MPU6050_DEVICE_NAME  "i2c1"

static void mpu6050_accel_entry(void *parameter)
{
    struct mpu6xxx_device *dev;
    struct mpu6xxx_3axes accel;

    /* Initialize mpu6050, The parameter is RT_NULL, means auto probing for i2c*/
    dev = mpu6xxx_init(MPU6050_DEVICE_NAME, RT_NULL);

    if (dev == RT_NULL)
    {
        LOG_E("mpu6050 init failed.");
        return;
    }
    LOG_I("mpu6050 init succeed.");

    while(1)
    {
        mpu6xxx_get_accel(dev, &accel);

        LOG_D("accel.x = %3d, accel.y = %3d, accel.z = %3d", accel.x, accel.y, accel.z);

        rt_thread_mdelay(1000);
    }
}

static int rt_hw_mpu6050_init()
{
    rt_thread_t tid_mpu;

    tid_mpu = rt_thread_create("mpu_accel", mpu6050_accel_entry, RT_NULL, 1024, 10, 10);
    if (tid_mpu == RT_NULL)
    {
        return -RT_ERROR;
    }

    rt_thread_startup(tid_mpu);

    return RT_EOK;
}

INIT_APP_EXPORT(rt_hw_mpu6050_init);
