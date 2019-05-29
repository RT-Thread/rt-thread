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

#ifdef PKG_USING_LSM6DSL
#include "sensor_st_lsm6dsl.h"

int sensor_init(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.type = RT_SENSOR_INTF_I2C;
    cfg.intf.dev_name = "i2c4";
    cfg.intf.user_data = (void *)LSM6DSL_ADDR_DEFAULT;
    cfg.irq_pin.pin  = RT_PIN_NONE;

    rt_hw_lsm6dsl_init("lsm", &cfg);

    return 0;
}
INIT_ENV_EXPORT(sensor_init);

#endif
