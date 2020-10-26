/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-11     wangk        bme280 port
 */

#include <rtthread.h>
#include <stdbool.h>
#include "sensor_bosch_bme280.h"

#if defined(BSP_USING_BME280_SENSOR)

#define BME280_DEBUG

#ifdef BME280_DEBUG
    #define BME280_TRACE	rt_kprintf
#else
    #define BME280_TRACE(...)
#endif /* BME280_DEBUG */

/* I2C总线名 */
#define BME280_I2C_BUS_NAME "i2c2"

/* 初始化BME280传感器驱动 */
static int bme280_port(void)
{
    struct rt_sensor_config cfg;
    
    cfg.intf.dev_name = BME280_I2C_BUS_NAME;
	cfg.intf.type = RT_SENSOR_INTF_I2C;
    cfg.intf.user_data = (void *)BME280_ADDR_DEFAULT;
    cfg.irq_pin.pin = RT_PIN_NONE;

    rt_hw_bme280_init("bme280", &cfg);
    return 0;
}
INIT_APP_EXPORT(bme280_port);

#endif /* BSP_USING_BME280_SENSOR */
