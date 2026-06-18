/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-18     coworkspace  first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include "ds1307.h"

#define DS1307_ADDR     0x68

static struct rt_i2c_bus_device *ds1307_i2c = RT_NULL;

rt_err_t ds1307_init(void)
{
    ds1307_i2c = (struct rt_i2c_bus_device *)rt_device_find("i2c1");
    if (ds1307_i2c == RT_NULL)
        return -RT_ERROR;

    return RT_EOK;
}

static rt_err_t read_regs(uint8_t reg, uint8_t *buf, uint8_t len)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = DS1307_ADDR;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].len   = 1;
    msgs[0].buf   = &reg;

    msgs[1].addr  = DS1307_ADDR;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].len   = len;
    msgs[1].buf   = buf;

    return (rt_i2c_transfer(ds1307_i2c, msgs, 2) == 2) ? RT_EOK : -RT_ERROR;
}

static rt_err_t write_reg(uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = {reg, val};

    return (rt_i2c_master_send(ds1307_i2c, DS1307_ADDR, 0, buf, 2) == 2)
           ? RT_EOK : -RT_ERROR;
}

static uint8_t bcd2bin(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

static uint8_t bin2bcd(uint8_t val)
{
    return ((val / 10) << 4) | (val % 10);
}

rt_err_t ds1307_get_time(struct tm *tm)
{
    uint8_t buf[7];

    if (read_regs(0x00, buf, 7) != RT_EOK)
        return -RT_ERROR;

    memset(tm, 0, sizeof(*tm));
    tm->tm_sec  = bcd2bin(buf[0] & 0x7F);
    tm->tm_min  = bcd2bin(buf[1] & 0x7F);
    tm->tm_hour = bcd2bin(buf[2] & 0x3F);
    tm->tm_mday = bcd2bin(buf[3] & 0x3F);
    tm->tm_wday = buf[4] & 0x07;
    tm->tm_mon  = bcd2bin(buf[5] & 0x1F) - 1;
    tm->tm_year = bcd2bin(buf[6]) + 100;

    return RT_EOK;
}

rt_err_t ds1307_set_time(struct tm *tm)
{
    uint8_t v;

    v = bin2bcd(tm->tm_year - 100);
    if (write_reg(0x06, v) != RT_EOK) return -RT_ERROR;

    v = bin2bcd(tm->tm_mon + 1);
    if (write_reg(0x05, v) != RT_EOK) return -RT_ERROR;

    v = bin2bcd(tm->tm_mday);
    if (write_reg(0x04, v) != RT_EOK) return -RT_ERROR;

    v = tm->tm_wday & 0x07;
    if (write_reg(0x03, v) != RT_EOK) return -RT_ERROR;

    v = bin2bcd(tm->tm_hour);
    if (write_reg(0x02, v) != RT_EOK) return -RT_ERROR;

    v = bin2bcd(tm->tm_min);
    if (write_reg(0x01, v) != RT_EOK) return -RT_ERROR;

    v = bin2bcd(tm->tm_sec);
    if (write_reg(0x00, v) != RT_EOK) return -RT_ERROR;

    return RT_EOK;
}
