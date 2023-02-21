/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-9-1        Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#include <sys/time.h>
#include "sensor_nct7717u.h"

#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "sensor.nct7717u"
#define DBG_COLOR
#include <rtdbg.h>

#define NCT7717U_I2C_SLAVE_ADDR          0x48

#define REG_NCT7717U_LDT                  0x0
#define REG_NCT7717U_ALERT_STATUS         0x2
#define REG_NCT7717U_CONFIGURATION_R      0x3
#define REG_NCT7717U_CONVERSION_RATE_R    0x4
#define REG_NCT7717U_LH_HAT_R             0x5

#define REG_NCT7717U_CONFIGURATION_W      0x9
#define REG_NCT7717U_CONVERSION_RATE_W    0xA
#define REG_NCT7717U_LH_HAT_W             0xB
#define REG_NCT7717U_ONESHOT_CONVERSION   0xF
#define REG_NCT7717U_CUSTOMER_LOG_1      0x2D
#define REG_NCT7717U_CUSTOMER_LOG_2      0x2E
#define REG_NCT7717U_CUSTOMER_LOG_3      0x2F
#define REG_NCT7717U_ALERT_MODE          0xBF

#define REG_NCT7717U_CID                 0xFD
#define REG_NCT7717U_VID                 0xFE
#define REG_NCT7717U_DID                 0xFF

static rt_err_t nct7717u_i2c_read_reg(struct rt_i2c_bus_device *i2c_bus_dev, const char *reg, int reg_length, char *data, int length)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = NCT7717U_I2C_SLAVE_ADDR;        /* Slave address */
    msgs[0].flags = RT_I2C_WR;                      /* Write flag */
    msgs[0].buf   = (rt_uint8_t *)reg;              /* Slave register address */
    msgs[0].len   = reg_length;                     /* Number of bytes sent */

    msgs[1].addr  = NCT7717U_I2C_SLAVE_ADDR;        /* Slave address */
    msgs[1].flags = RT_I2C_RD;                      /* Read flag without READ_ACK */
    msgs[1].buf   = (rt_uint8_t *)data;             /* Read data pointer */
    msgs[1].len   = length;                         /* Number of bytes read */

    if (rt_i2c_transfer(i2c_bus_dev, &msgs[0], 2) != 2)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t nct7717u_read_cid(struct rt_i2c_bus_device *i2c_bus_dev, uint8_t *u8Temp)
{
    uint8_t u8Reg = REG_NCT7717U_CID;
    return nct7717u_i2c_read_reg(i2c_bus_dev, (const char *)&u8Reg, sizeof(u8Reg), (char *)u8Temp, sizeof(uint8_t));
}

static rt_err_t nct7717u_read_vid(struct rt_i2c_bus_device *i2c_bus_dev, uint8_t *u8Temp)
{
    uint8_t u8Reg = REG_NCT7717U_VID;
    return nct7717u_i2c_read_reg(i2c_bus_dev, (const char *)&u8Reg, sizeof(u8Reg), (char *)u8Temp, sizeof(uint8_t));
}

static rt_err_t nct7717u_read_did(struct rt_i2c_bus_device *i2c_bus_dev, uint8_t *u8Temp)
{
    uint8_t u8Reg = REG_NCT7717U_DID;
    return nct7717u_i2c_read_reg(i2c_bus_dev, (const char *)&u8Reg, sizeof(u8Reg), (char *)u8Temp, sizeof(uint8_t));
}

static rt_err_t nct7717u_probe(struct rt_i2c_bus_device *i2c_bus_dev)
{
    uint8_t u8Cid, u8Vid, u8Did;

    if (nct7717u_read_cid(i2c_bus_dev, &u8Cid) != RT_EOK)
        goto exit_nct7717u_probe;

    if (nct7717u_read_vid(i2c_bus_dev, &u8Vid) != RT_EOK)
        goto exit_nct7717u_probe;

    if (nct7717u_read_did(i2c_bus_dev, &u8Did) != RT_EOK)
        goto exit_nct7717u_probe;

    LOG_I("CID=%02x VID=%02x DID=%02x", u8Cid, u8Vid, u8Did);

    if ((u8Cid != 0x50) || (u8Vid != 0x50) || ((u8Did & 0x90) != 0x90))
    {
        LOG_E("Failed to detect NCT7717U");
        goto exit_nct7717u_probe;
    }
    return RT_EOK;

exit_nct7717u_probe:

    return -RT_ERROR;
}

static rt_err_t nct7717u_ldt_readout(struct rt_i2c_bus_device *i2c_bus_dev, uint8_t *u8Temp)
{
    uint8_t u8Reg = REG_NCT7717U_LDT;
    return nct7717u_i2c_read_reg(i2c_bus_dev, (const char *)&u8Reg, sizeof(u8Reg), (char *)u8Temp, sizeof(uint8_t));
}

static rt_ssize_t nct7717u_fetch_data(rt_sensor_t sensor, rt_sensor_data_t data, rt_size_t len)
{
    RT_ASSERT(data);

    if (sensor->info.type == RT_SENSOR_TYPE_TEMP)
    {
        rt_int8_t i8Temp;
        struct rt_i2c_bus_device *i2c_bus_dev = sensor->config.intf.arg;

        if (nct7717u_ldt_readout(i2c_bus_dev, (uint8_t *)&i8Temp) == RT_EOK)
        {
            rt_int32_t i32TempValue = i8Temp;
            data->type = RT_SENSOR_TYPE_TEMP;
            data->data.temp = i32TempValue * 10;
            data->timestamp = rt_sensor_get_ts();
            return 1;
        }
    }
    return 0;
}

static rt_err_t nct7717u_control(struct rt_sensor_device *sensor, int cmd, void *args)
{
    switch (cmd)
    {
    case RT_SENSOR_CTRL_GET_ID:
    {
        struct rt_i2c_bus_device *i2c_bus_dev = sensor->config.intf.arg;
        uint8_t u8Did;

        RT_ASSERT(args);
        nct7717u_read_did(i2c_bus_dev, &u8Did);
        *((uint8_t *)args) = u8Did;
    }
    break;

    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

static struct rt_sensor_ops sensor_ops =
{
    nct7717u_fetch_data,
    nct7717u_control
};

int rt_hw_nct7717u_temp_init(const char *name, struct rt_sensor_config *cfg)
{
    rt_int8_t result;
    rt_sensor_t sensor = RT_NULL;

    sensor = rt_calloc(1, sizeof(struct rt_sensor_device));
    if (sensor == RT_NULL)
        return -(RT_ENOMEM);

    sensor->info.type            = RT_SENSOR_TYPE_TEMP;
    sensor->info.vendor          = RT_SENSOR_VENDOR_UNKNOWN;
    sensor->info.name            = "nct7717u_temp";
    sensor->info.unit            = RT_SENSOR_UNIT_CELSIUS;
    sensor->info.intf_type       = RT_SENSOR_INTF_I2C;
    sensor->info.scale.range_max = 127;
    sensor->info.scale.range_min = -128;
    sensor->info.acquire_min     = 100; //100ms

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

int rt_hw_nct7717u_init(const char *name, struct rt_sensor_config *cfg)
{
    struct rt_sensor_intf *intf;
    struct rt_i2c_bus_device *i2c_bus_dev;

    RT_ASSERT(name != NULL);
    RT_ASSERT(cfg != NULL);

    intf = &cfg->intf;

    /* Find I2C bus */
    i2c_bus_dev = (struct rt_i2c_bus_device *)rt_device_find(intf->dev_name);
    if (i2c_bus_dev == RT_NULL)
    {
        goto exit_rt_hw_nct7717u_init;
    }
    intf->arg = i2c_bus_dev;

    if (nct7717u_probe(i2c_bus_dev) != RT_EOK)
        goto exit_rt_hw_nct7717u_init;

    return rt_hw_nct7717u_temp_init(name, cfg);

exit_rt_hw_nct7717u_init:

    return -(RT_ERROR);
}
