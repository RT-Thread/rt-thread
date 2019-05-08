/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-08     flaybreak    add sensor port file
 */

#include <board.h>

#ifdef BSP_USING_ICM20608
#include "sensor_inven_mpu6xxx.h"

int sensor_init(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.type = RT_SENSOR_INTF_I2C;
    cfg.intf.dev_name = "i2c3";
    cfg.intf.user_data = (void*)MPU6XXX_ADDR_DEFAULT;
    cfg.irq_pin.pin  = RT_PIN_NONE;

    rt_hw_mpu6xxx_init("icm", &cfg);

    return 0;
}
INIT_ENV_EXPORT(sensor_init);

#endif
