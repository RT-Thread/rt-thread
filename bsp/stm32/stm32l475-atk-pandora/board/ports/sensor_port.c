/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-08     flaybreak    add sensor port file
 */

#include <board.h>

#ifdef BSP_USING_ICM20608
#include <sensor_inven_mpu6xxx.h>

static int rt_hw_icm20608_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i2c3";
    cfg.intf.type = RT_SENSOR_INTF_I2C;
    cfg.intf.arg = (void *)MPU6XXX_ADDR_DEFAULT;
    cfg.irq_pin.pin  = RT_PIN_NONE;

    rt_hw_mpu6xxx_init("icm", &cfg);

    return RT_EOK;
}
INIT_ENV_EXPORT(rt_hw_icm20608_port);

#endif

#ifdef BSP_USING_AHT10
#include <sensor_asair_aht10.h>

static int rt_hw_aht10_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name  = "i2c4";
    cfg.intf.type = RT_SENSOR_INTF_I2C;
    cfg.intf.arg = (void *)AHT10_I2C_ADDR;
    cfg.irq_pin.pin  = RT_PIN_NONE;

    rt_hw_aht10_init("aht10", &cfg);

    return RT_EOK;
}
INIT_ENV_EXPORT(rt_hw_aht10_port);
#endif
