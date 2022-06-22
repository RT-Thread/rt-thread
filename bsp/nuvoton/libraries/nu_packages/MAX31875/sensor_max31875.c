/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(NU_PKG_USING_MAX31875)

#include <sys/time.h>
#include "sensor.h"
#include "max31875_c.h"

#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "sensor.max31875"
#define DBG_COLOR
#include <rtdbg.h>

static S_MAX31875 g_sMax31875;
static struct rt_i2c_bus_device *i2c_bus_dev;

static int max31875_i2c_write_reg(int address, const char *data, int length)
{
    struct rt_i2c_msg msg;

    msg.addr  = address;              /* Slave address */
    msg.flags = RT_I2C_WR;            /* Write flag */
    msg.buf   = (rt_uint8_t *)data;   /* Slave register address */
    msg.len   = length;               /* Number of bytes sent */

    if (rt_i2c_transfer(i2c_bus_dev, &msg, 1) != 1)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static int max31875_i2c_read_reg(int address, const char *reg, int reg_length, char *data, int length)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = address;                        /* Slave address */
    msgs[0].flags = RT_I2C_WR;                      /* Write flag */
    msgs[0].buf   = (rt_uint8_t *)reg;              /* Slave register address */
    msgs[0].len   = reg_length;                     /* Number of bytes sent */
    msgs[1].addr  = address;                        /* Slave address */
    msgs[1].flags = RT_I2C_RD; /* Read flag without READ_ACK */
    msgs[1].buf   = (rt_uint8_t *)data;             /* Read data pointer */
    msgs[1].len   = length;                         /* Number of bytes read */

    if (rt_i2c_transfer(i2c_bus_dev, &msgs[0], 2) != 2)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_size_t max31875_fetch_data(struct rt_sensor_device *sensor, void *buf, rt_size_t len)
{
    struct rt_sensor_data *data = (struct rt_sensor_data *)buf;

    if (sensor->info.type == RT_SENSOR_CLASS_TEMP)
    {
        float temp_value;
        temp_value = max31875_read_reg_as_temperature(MAX31875_REG_TEMPERATURE, &g_sMax31875);
        data->type = RT_SENSOR_CLASS_TEMP;
        data->data.temp = (rt_int32_t)(temp_value * 10);
        data->timestamp = rt_sensor_get_ts();
    }

    return 1;
}

static rt_err_t max31875_control(struct rt_sensor_device *sensor, int cmd, void *args)
{
    return -RT_ERROR;
}

static struct rt_sensor_ops sensor_ops =
{
    max31875_fetch_data,
    max31875_control
};

int rt_hw_max31875_temp_init(const char *name, struct rt_sensor_config *cfg)
{
    rt_int8_t result;
    rt_sensor_t sensor = RT_NULL;

    sensor = rt_calloc(1, sizeof(struct rt_sensor_device));
    if (sensor == RT_NULL)
        return -(RT_ENOMEM);

    sensor->info.type       = RT_SENSOR_CLASS_TEMP;
    sensor->info.vendor     = RT_SENSOR_VENDOR_UNKNOWN;
    sensor->info.model      = "max31875_temp";
    sensor->info.unit       = RT_SENSOR_UNIT_DCELSIUS;
    sensor->info.intf_type  = RT_SENSOR_INTF_I2C;
    sensor->info.range_max  = 70;
    sensor->info.range_min  = 0;
    sensor->info.period_min = 100; //100ms

    rt_memcpy(&sensor->config, cfg, sizeof(struct rt_sensor_config));
    sensor->ops = &sensor_ops;

    result = rt_hw_sensor_register(sensor, name, RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("device register: %d", result);
        rt_free(sensor);
        return -RT_ERROR;
    }

    return RT_EOK;
}

int rt_hw_max31875_init(const char *name, struct rt_sensor_config *cfg)
{
    struct rt_sensor_intf *intf;
    rt_err_t  ret = RT_ERROR;

    RT_ASSERT(name != NULL);
    RT_ASSERT(cfg != NULL);

    intf = &cfg->intf;

    /* Find I2C bus */
    i2c_bus_dev = (struct rt_i2c_bus_device *)rt_device_find(intf->dev_name);
    if (i2c_bus_dev == RT_NULL)
    {
        goto exit_rt_hw_max31875_init;
    }

    g_sMax31875.read    = max31875_i2c_read_reg;
    g_sMax31875.write   = max31875_i2c_write_reg;
    g_sMax31875.address = (uint32_t)(intf->user_data) & 0xff;

    if ((ret = max31875_init(g_sMax31875.address)) != RT_EOK)
    {
        LOG_E("Init..!\n");
    }
    else if ((ret = max31875_write_cfg(MAX31875_CFG_CONV_RATE_8 | MAX31875_CFG_RESOLUTION_12BIT, &g_sMax31875)) != RT_EOK)
    {
        LOG_E("Write_cfg..!\n");
    }
    else
        return rt_hw_max31875_temp_init(name, cfg);

exit_rt_hw_max31875_init:

    return -(ret);
}

#endif //#if defined(NU_PKG_USING_MAX31875)
