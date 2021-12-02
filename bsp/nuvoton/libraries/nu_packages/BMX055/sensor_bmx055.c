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

#if defined(NU_PKG_USING_BMX055)

#include <sys/time.h>
#include <string.h>
#include "sensor_bmx055.h"

#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "sensor.bmx055"
#define DBG_COLOR
#include <rtdbg.h>

struct bmx055
{
    /* Structure used for Magnetometer */
    struct bmm050_t mag;

    /* Structure used for read the mag xyz data*/
    struct bmm050_mag_data_s16_t mag_data;

    /* Structure used for Accelerometer */
    struct bma2x2_t accel;

    /* Structure used to read accel xyz and temperature data*/
    struct bma2x2_accel_data_temp accel_xyzt;

    /* Structure used for Gyroscope */
    struct bmg160_t gyro;

    /* structure used to read gyro xyz and interrupt status*/
    struct bmg160_data_t gyro_xyzi;

} ;
typedef struct bmx055 *bmx055_t;

struct bmx055_param_pair
{
    int val;
    int reg;
};
typedef struct bmx055_param_pair *bmx055_param_pair_t;

static const struct bmx055_param_pair accel_ranges[] =
{
    {2000, BMA2x2_RANGE_2G},
    {4000, BMA2x2_RANGE_4G},
    {8000, BMA2x2_RANGE_8G},
    {16000, BMA2x2_RANGE_16G},
};

static const struct bmx055_param_pair gyro_ranges[] =
{
    {125, BMG160_RANGE_125},
    {250, BMG160_RANGE_250},
    {500, BMG160_RANGE_500},
    {1000, BMG160_RANGE_1000},
    {2000, BMG160_RANGE_2000},
};

static const struct bmx055_param_pair accel_odr[] =
{
    {8, BMA2x2_BW_7_81HZ},
    {16, BMA2x2_BW_15_63HZ},
    {32, BMA2x2_BW_31_25HZ},
    {63, BMA2x2_BW_62_50HZ},
    {125, BMA2x2_BW_125HZ},
    {250, BMA2x2_BW_250HZ},
    {500, BMA2x2_BW_500HZ},
    {1000, BMA2x2_BW_1000HZ},
};

static const struct bmx055_param_pair gyro_odr[] =
{
    {12, BMG160_BW_12_HZ},
    {23, BMG160_BW_23_HZ},
    {32, BMG160_BW_32_HZ},
    {47, BMG160_BW_47_HZ},
    {64, BMG160_BW_64_HZ},
    {116, BMG160_BW_116_HZ},
    {230, BMG160_BW_230_HZ},
    {500, BMG160_BW_500_HZ},
};

static const struct bmx055_param_pair mag_odr[] =
{
    {2, BMM050_DR_02HZ},
    {6, BMM050_DR_06HZ},
    {8, BMM050_DR_08HZ},
    {15, BMM050_DR_15HZ},
    {20, BMM050_DR_20HZ},
    {25, BMM050_DR_25HZ},
    {30, BMM050_DR_30HZ},
};

static struct bmx055 g_sbmx055;
static struct rt_i2c_bus_device *i2c_bus_dev;
static uint8_t g_u8Range_accel = 0;
static uint8_t g_u8Range_gyro = 0;

static int8_t bmx055_i2c_write_reg(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint8_t len)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = dev_id;                          /* Slave address */
    msgs[0].flags = RT_I2C_WR;                       /* Write flag */
    msgs[0].buf   = (rt_uint8_t *)&reg_addr;         /* Slave register address */
    msgs[0].len   = 1;                               /* Number of bytes sent */

    msgs[1].addr  = dev_id;                          /* Slave address */
    msgs[1].flags = RT_I2C_WR | RT_I2C_NO_START;     /* Read flag without NO_START */
    msgs[1].buf   = (rt_uint8_t *)reg_data;          /* Read data pointer */
    msgs[1].len   = len;                             /* Number of bytes read */

    if (rt_i2c_transfer(i2c_bus_dev, &msgs[0], 2) != 2)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static int8_t bmx055_i2c_read_reg(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint8_t len)
{
    struct rt_i2c_msg msgs[3];

    msgs[0].addr  = dev_id;                           /* Slave address */
    msgs[0].flags = RT_I2C_WR;                        /* Write flag */
    msgs[0].buf   = (rt_uint8_t *)&reg_addr;          /* Slave register address */
    msgs[0].len   = 1;                                /* Number of bytes sent */


    msgs[1].addr  = dev_id;                           /* Slave address */
    msgs[1].flags = RT_I2C_RD ;                       /* Read flag */
    msgs[1].buf   = (rt_uint8_t *)&reg_data[0];       /* Read data pointer */
    msgs[1].len   = len;

    if (rt_i2c_transfer(i2c_bus_dev, &msgs[0], 2) != 2)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

void bmx055_delay_ms(BMM050_MDELAY_DATA_TYPE ms)
{
    rt_thread_mdelay(ms);
}

static int8_t bmx055_init_mag(struct bmm050_t *mag)
{
    int8_t com_rslt = 0;
    u8 v_data_rate_u8 = BMM050_INIT_VALUE;

    mag->dev_addr = BMM050_I2C_ADDRESS;
    mag->bus_write = bmx055_i2c_write_reg;
    mag->bus_read = bmx055_i2c_read_reg;
    mag->delay_msec = bmx055_delay_ms;

    com_rslt = bmm050_init(mag);
    com_rslt += bmm050_set_functional_state(BMM050_NORMAL_MODE);
    com_rslt += bmm050_set_data_rate(BMM050_DATA_RATE_30HZ);
    com_rslt += bmm050_get_data_rate(&v_data_rate_u8);

    return com_rslt;
}

static int8_t bmx055_init_accel(struct bma2x2_t *accel)
{
    int8_t com_rslt = 0;
    uint8_t bandwidth = 0x08;   // bandwidth of 7.81Hz

    accel->dev_addr = BMA2x2_I2C_ADDR1;
    accel->bus_write = bmx055_i2c_write_reg;
    accel->bus_read = bmx055_i2c_read_reg;
    accel->delay_msec = bmx055_delay_ms;

    com_rslt = bma2x2_init(accel);
    com_rslt += bma2x2_set_power_mode(BMA2x2_MODE_NORMAL);
    com_rslt += bma2x2_set_bw(bandwidth);
    com_rslt += bma2x2_get_range(&g_u8Range_accel);

    return com_rslt;
}

static int8_t bmx055_init_gyro(struct bmg160_t *gyro)
{
    int8_t com_rslt = 0;

    gyro->dev_addr = BMG160_I2C_ADDR1;
    gyro->bus_write = bmx055_i2c_write_reg;
    gyro->bus_read = bmx055_i2c_read_reg;
    gyro->delay_msec = bmx055_delay_ms;

    com_rslt = bmg160_init(gyro);
    com_rslt += bmg160_set_power_mode(BMG160_MODE_NORMAL);
    com_rslt += bmg160_set_bw(C_BMG160_BW_230HZ_U8X);
    com_rslt += bmg160_get_range_reg(&g_u8Range_gyro);

    return com_rslt;
}

static double get_mg_value(int32_t i32AccelVal)
{
    switch (g_u8Range_accel)
    {
    case BMA2x2_RANGE_2G:
        return (double)i32AccelVal * 0.98;   //res: 0.98,
    case BMA2x2_RANGE_4G:
        return (double)i32AccelVal * 1.95;
    case BMA2x2_RANGE_8G:
        return (double)i32AccelVal * 3.91;
    case BMA2x2_RANGE_16G:
        return (double)i32AccelVal * 7.81;
    }
    return 0.0f;
}

static double get_mdps_value(int32_t i32AccelVal)
{
    switch (g_u8Range_gyro)
    {
    case BMG160_RANGE_125:
        return (double)i32AccelVal * 3.8;
    case BMG160_RANGE_250:
        return (double)i32AccelVal * 7.6;
    case BMG160_RANGE_500:
        return (double)i32AccelVal * 15.3;
    case BMG160_RANGE_1000:
        return (double)i32AccelVal * 30.5;
    case BMG160_RANGE_2000:
        return (double)i32AccelVal * 61;
    }
    return 0.0f;
}

static rt_size_t bmx055_fetch_data(rt_sensor_t sensor, void *buf, rt_size_t len)
{
    struct rt_sensor_data *data = (struct rt_sensor_data *)buf;
    switch (sensor->info.type)
    {
    case RT_SENSOR_CLASS_ACCE:
        bma2x2_read_accel_xyzt(&g_sbmx055.accel_xyzt);
        data->type = RT_SENSOR_CLASS_ACCE;

        /* Report mg */
        data->data.acce.x = (int32_t)get_mg_value(g_sbmx055.accel_xyzt.x);
        data->data.acce.y = (int32_t)get_mg_value(g_sbmx055.accel_xyzt.y);
        data->data.acce.z = (int32_t)get_mg_value(g_sbmx055.accel_xyzt.z);
        break;

    case RT_SENSOR_CLASS_GYRO:
        bmg160_get_data_XYZI(&g_sbmx055.gyro_xyzi);
        data->type = RT_SENSOR_CLASS_GYRO;

        /* Report mdps */
        data->data.gyro.x = (int32_t)get_mdps_value(g_sbmx055.gyro_xyzi.datax);
        data->data.gyro.y = (int32_t)get_mdps_value(g_sbmx055.gyro_xyzi.datay);
        data->data.gyro.z = (int32_t)get_mdps_value(g_sbmx055.gyro_xyzi.dataz);
        break;

    case RT_SENSOR_CLASS_MAG:
        bmm050_read_mag_data_XYZ(&g_sbmx055.mag_data);
        data->type = RT_SENSOR_CLASS_MAG;

        /* Report mquass */
        data->data.mag.x = g_sbmx055.mag_data.datax;
        data->data.mag.y = g_sbmx055.mag_data.datay;
        data->data.mag.z = g_sbmx055.mag_data.dataz;
        break;

    default:
        return 0;
    }
    data->timestamp = rt_sensor_get_ts();
    return 1;
}

static int find_param_index(const int eng_val, const struct bmx055_param_pair *pairs, const int size)
{
    int i = 0;

    while (i < size)
    {
        if (eng_val <= pairs[i].val)
            return i;
        i++;
    }
    return i - 1;
}

static rt_err_t bmx055_getid(rt_sensor_t sensor, rt_uint8_t *pu8)
{
    switch (sensor->info.type)
    {
    case RT_SENSOR_CLASS_ACCE:
        *pu8 = g_sbmx055.accel.chip_id;
        break;

    case RT_SENSOR_CLASS_GYRO:
        *pu8 = g_sbmx055.gyro.chip_id;
        break;

    case RT_SENSOR_CLASS_MAG:
        *pu8 = g_sbmx055.mag.company_id;
        break;
    }
    return -RT_EINVAL;
}


static rt_err_t bmx055_set_power(rt_sensor_t sensor, rt_uint8_t power_mode)
{
    uint8_t power_ctr;

    switch (sensor->info.type)
    {
    case RT_SENSOR_CLASS_ACCE:
    {
        switch (power_mode)
        {
        case RT_SENSOR_POWER_DOWN:
            power_ctr = BMA2x2_MODE_STANDBY;
            break;

        case RT_SENSOR_POWER_NORMAL:
            power_ctr = BMA2x2_MODE_NORMAL;
            break;

        case RT_SENSOR_POWER_LOW:
            power_ctr = BMA2x2_MODE_LOWPOWER1;
            break;

        default:
            return -RT_EINVAL;
        }

        if (bma2x2_set_power_mode(power_ctr) != 0)
            goto exit_bmx055_set_power;

    }
    break;

    case RT_SENSOR_CLASS_GYRO:
    {
        switch (power_mode)
        {
        case RT_SENSOR_POWER_DOWN:
            power_ctr = BMG160_MODE_DEEPSUSPEND;
            break;

        case RT_SENSOR_POWER_NORMAL:
            power_ctr = BMG160_MODE_NORMAL;
            break;

        default:
            return -RT_EINVAL;
        }

        if (bmg160_set_power_mode(power_ctr) != 0)
            goto exit_bmx055_set_power;

    }
    break;

    case RT_SENSOR_CLASS_MAG:
    {
        switch (power_mode)
        {
        case RT_SENSOR_POWER_DOWN:
            power_ctr = 0;
            break;

        case RT_SENSOR_POWER_NORMAL:
            power_ctr = 1;
            break;

        default:
            return -RT_EINVAL;
        }
        if (bmm050_set_power_mode(power_ctr) != 0)
            goto exit_bmx055_set_power;
    }
    break;

    default:
        return -RT_EINVAL;
    }

exit_bmx055_set_power:

    return -RT_ERROR;
}

static rt_err_t bmx055_set_range(rt_sensor_t sensor, rt_uint16_t range)
{
    int idx;

    switch (sensor->info.type)
    {
    case RT_SENSOR_CLASS_ACCE:
    {
        idx = find_param_index(range, accel_ranges, sizeof(accel_ranges));
        if (bma2x2_set_range(accel_ranges[idx].reg) != 0)
            goto exit_bmx055_set_range;
        else if (bma2x2_get_range(&g_u8Range_accel) != 0)
            goto exit_bmx055_set_range;
    }
    break;

    case RT_SENSOR_CLASS_GYRO:
    {
        idx = find_param_index(range, gyro_ranges, sizeof(gyro_ranges));
        if (bmg160_set_range_reg(gyro_ranges[idx].reg) != 0)
            goto exit_bmx055_set_range;
        else if (bmg160_get_range_reg(&g_u8Range_gyro) != 0)
            goto exit_bmx055_set_range;
    }
    break;

    default:
        return -RT_EINVAL;
    }

exit_bmx055_set_range:

    return -RT_ERROR;
}

static rt_err_t bmx055_set_odr(rt_sensor_t sensor, rt_uint16_t odr_hz)
{
    int idx;
    switch (sensor->info.type)
    {
    case RT_SENSOR_CLASS_ACCE:
    {
        idx = find_param_index(odr_hz, accel_odr, sizeof(accel_odr));
        if (bma2x2_set_bw(accel_odr[idx].reg) != 0)
            goto exit_bmx055_set_power;
    }
    break;

    case RT_SENSOR_CLASS_GYRO:
    {
        idx = find_param_index(odr_hz, gyro_odr, sizeof(gyro_odr));
        if (bmg160_set_bw(gyro_odr[idx].reg) != 0)
            goto exit_bmx055_set_power;
    }
    break;

    case RT_SENSOR_CLASS_MAG:
    {
        idx = find_param_index(odr_hz, mag_odr, sizeof(mag_odr));
        if (bmm050_set_data_rate(mag_odr[idx].reg) != 0)
            goto exit_bmx055_set_power;
    }
    break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;

exit_bmx055_set_power:

    return -RT_ERROR;
}

static rt_err_t bmx055_control(rt_sensor_t sensor, int cmd, void *args)
{
    RT_ASSERT(sensor != RT_NULL);
    RT_ASSERT(args != RT_NULL);

    switch (cmd)
    {
    case RT_SENSOR_CTRL_GET_ID:
    {
        rt_uint8_t *pu8id = (rt_uint8_t *)args;
        return bmx055_getid(sensor, pu8id);
    }
    case RT_SENSOR_CTRL_SET_RANGE:
        return bmx055_set_range(sensor, (rt_uint32_t)args);

    case RT_SENSOR_CTRL_SET_POWER:
        return bmx055_set_power(sensor, ((rt_uint32_t)args & 0xff));

    case RT_SENSOR_CTRL_SET_ODR:
        return bmx055_set_odr(sensor, ((rt_uint32_t)args & 0xff));

    }
    return -RT_EINVAL;
}

static struct rt_sensor_ops sensor_ops =
{
    bmx055_fetch_data,
    bmx055_control
};

static int rt_hw_bmx055_accel_init(const char *name, struct rt_sensor_config *cfg)
{
    rt_int8_t result;
    rt_sensor_t sensor = RT_NULL;

    sensor = rt_calloc(1, sizeof(struct rt_sensor_device));
    if (sensor == RT_NULL)
        return -(RT_ENOMEM);

    sensor->info.type       = RT_SENSOR_CLASS_ACCE;
    sensor->info.vendor     = RT_SENSOR_VENDOR_BOSCH;
    sensor->info.model      = "bmx055_acce";
    sensor->info.unit       = RT_SENSOR_UNIT_MG;
    sensor->info.intf_type  = RT_SENSOR_INTF_I2C;
    sensor->info.range_max  = 16000;
    sensor->info.range_min  = 2000;
    sensor->info.period_min = 100;

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

static int rt_hw_bmx055_gyro_init(const char *name, struct rt_sensor_config *cfg)
{
    rt_int8_t result;
    rt_sensor_t sensor = RT_NULL;

    sensor = rt_calloc(1, sizeof(struct rt_sensor_device));
    if (sensor == RT_NULL)
        return -(RT_ENOMEM);

    sensor->info.type       = RT_SENSOR_CLASS_GYRO;
    sensor->info.vendor     = RT_SENSOR_VENDOR_BOSCH;
    sensor->info.model      = "bmx055_gyro";
    sensor->info.unit       = RT_SENSOR_UNIT_MDPS;
    sensor->info.intf_type  = RT_SENSOR_INTF_I2C;
    sensor->info.range_max  = 2000;
    sensor->info.range_min  = 125;
    sensor->info.period_min = 100;

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

static int rt_hw_bmx055_mag_init(const char *name, struct rt_sensor_config *cfg)
{
    rt_int8_t result;
    rt_sensor_t sensor = RT_NULL;

    sensor = rt_calloc(1, sizeof(struct rt_sensor_device));
    if (sensor == RT_NULL)
        return -(RT_ENOMEM);

    sensor->info.type       = RT_SENSOR_CLASS_MAG;
    sensor->info.vendor     = RT_SENSOR_VENDOR_BOSCH;
    sensor->info.model      = "bmx055_mag";
    sensor->info.unit       = RT_SENSOR_UNIT_MGAUSS;
    sensor->info.intf_type  = RT_SENSOR_INTF_I2C;
    sensor->info.range_max  = 25000; // 1uT = 10*mGauss, X/Y: 1300uT=13000mGauss, Z: 2500uT=25000mG
    sensor->info.range_min  = 0;
    sensor->info.period_min = 100;

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

int rt_hw_bmx055_init(const char *name, struct rt_sensor_config *cfg)
{
    struct rt_sensor_intf *intf;
    rt_err_t  ret = -RT_ERROR;

    RT_ASSERT(name != NULL);
    RT_ASSERT(cfg != NULL);

    intf = &cfg->intf;

    /* Find I2C bus */
    i2c_bus_dev = (struct rt_i2c_bus_device *)rt_device_find(intf->dev_name);
    if (i2c_bus_dev == RT_NULL)
    {
        LOG_E("Can't found I2C bus..!\n");
        goto exit_rt_hw_bmx055_init;
    }

    if (bmx055_init_mag(&g_sbmx055.mag) != 0)
    {
        LOG_E("Init mag..!\n");
    }
    else if ((ret = rt_hw_bmx055_mag_init(name, cfg)) != RT_EOK)
    {
        LOG_E("Register mag..!\n");
    }

    if (bmx055_init_accel(&g_sbmx055.accel) != 0)
    {
        LOG_E("Init accel..!\n");
    }
    else if ((ret = rt_hw_bmx055_accel_init(name, cfg)) != RT_EOK)
    {
        LOG_E("Register accel..!\n");
    }

    if (bmx055_init_gyro(&g_sbmx055.gyro) != 0)
    {
        LOG_E("Init gyro..!\n");
    }
    else if ((ret = rt_hw_bmx055_gyro_init(name, cfg)) != RT_EOK)
    {
        LOG_E("Register gyro..!\n");
    }

exit_rt_hw_bmx055_init:
    return ret;
}

#endif //#if defined(NU_PKG_USING_BMX055)
