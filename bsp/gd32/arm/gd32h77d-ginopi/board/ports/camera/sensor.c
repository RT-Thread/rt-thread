/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Minimal OpenMV-compatible sensor layer for OV7670.
 */
#include <string.h>

#include "cam_boardconfig.h"
#include "sensor.h"

sensor_t sensor;

int sensor_init(void)
{
    rt_uint8_t pid;
    rt_uint8_t ver;

    memset(&sensor, 0, sizeof(sensor));
    sensor.slv_addr = 0x42U;

    if (omv_i2c_init(&sensor.i2c_bus, ISC_I2C_ID, ISC_I2C_SPEED) != 0)
    {
        return -1;
    }

    if (omv_i2c_readb(&sensor.i2c_bus, sensor.slv_addr, 0x0AU, &pid) != 0)
    {
        return -1;
    }
    if (omv_i2c_readb(&sensor.i2c_bus, sensor.slv_addr, 0x0BU, &ver) != 0)
    {
        return -1;
    }
    if (pid != OV7670_ID)
    {
        return -1;
    }

    sensor.chip_id = pid;
    if (ov7670_init(&sensor) != 0)
    {
        return -1;
    }

    sensor.detected = true;
    RT_UNUSED(ver);
    return 0;
}

int sensor_reset(void)
{
    return (sensor.reset != RT_NULL) ? sensor.reset(&sensor) : -1;
}

int sensor_read_reg(uint16_t reg_addr)
{
    return (sensor.read_reg != RT_NULL) ? sensor.read_reg(&sensor, reg_addr) : -1;
}

int sensor_write_reg(uint16_t reg_addr, uint16_t reg_data)
{
    return (sensor.write_reg != RT_NULL) ?
           sensor.write_reg(&sensor, reg_addr, reg_data) : -1;
}

int sensor_set_pixformat(pixformat_t pixformat)
{
    int ret;

    if (sensor.set_pixformat == RT_NULL)
    {
        return -1;
    }
    ret = sensor.set_pixformat(&sensor, pixformat);
    if (ret == 0)
    {
        sensor.pixformat = pixformat;
    }
    return ret;
}

int sensor_set_framesize(framesize_t framesize)
{
    int ret;

    if (sensor.set_framesize == RT_NULL)
    {
        return -1;
    }
    ret = sensor.set_framesize(&sensor, framesize);
    if (ret == 0)
    {
        sensor.framesize = framesize;
    }
    return ret;
}

int sensor_set_hmirror(int enable)
{
    int ret;

    if (sensor.set_hmirror == RT_NULL)
    {
        return -1;
    }
    ret = sensor.set_hmirror(&sensor, enable);
    if (ret == 0)
    {
        sensor.hmirror = (enable != 0);
    }
    return ret;
}

int sensor_set_vflip(int enable)
{
    int ret;

    if (sensor.set_vflip == RT_NULL)
    {
        return -1;
    }
    ret = sensor.set_vflip(&sensor, enable);
    if (ret == 0)
    {
        sensor.vflip = (enable != 0);
    }
    return ret;
}

bool sensor_is_detected(void)
{
    return sensor.detected;
}
