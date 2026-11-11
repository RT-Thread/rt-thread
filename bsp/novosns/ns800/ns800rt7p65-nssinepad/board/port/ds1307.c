/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-24     wenzhi346    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_rtc.h"
#include "ds1307.h"

#ifndef BSP_RTC_DS1307_I2C_BUS_NAME
#define BSP_RTC_DS1307_I2C_BUS_NAME    "hwi2c1"
#endif

#ifndef BSP_RTC_DS1307_I2C_ADDR
#define BSP_RTC_DS1307_I2C_ADDR        0x68
#endif

#define DS1307_REG_SEC                 0x00
#define DS1307_REG_MIN                 0x01
#define DS1307_REG_HOUR                0x02
#define DS1307_REG_WDAY                0x03
#define DS1307_REG_MDAY                0x04
#define DS1307_REG_MON                 0x05
#define DS1307_REG_YEAR                0x06

#define DS1307_SEC_CH                  0x80
#define DS1307_HOUR_12H                0x40
#define DS1307_HOUR_PM                 0x20

struct ds1307_device
{
    const char *bus_name;
    rt_uint16_t addr;
    struct rt_i2c_bus_device *i2c;
    rt_bool_t clock_halt_reported;
};

static struct ds1307_device g_ds1307 =
{
    BSP_RTC_DS1307_I2C_BUS_NAME,
    BSP_RTC_DS1307_I2C_ADDR,
    RT_NULL,
    RT_FALSE,
};

static rt_uint8_t bcd2bin(rt_uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

static rt_uint8_t bin2bcd(rt_uint8_t val)
{
    return ((val / 10) << 4) | (val % 10);
}

static rt_bool_t bcd_in_range(rt_uint8_t bcd, rt_uint8_t min, rt_uint8_t max)
{
    rt_uint8_t val;

    if (((bcd & 0x0F) > 9) || (((bcd >> 4) & 0x0F) > 9))
    {
        return RT_FALSE;
    }

    val = bcd2bin(bcd);
    return ((val >= min) && (val <= max)) ? RT_TRUE : RT_FALSE;
}

static rt_bool_t is_leap_year(int year)
{
    return (((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0))) ? RT_TRUE : RT_FALSE;
}

static rt_uint8_t month_days(int year, int mon)
{
    static const rt_uint8_t days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((mon == 1) && is_leap_year(year))
    {
        return 29;
    }

    return days[mon];
}

static rt_bool_t tm_is_valid(const struct tm *tm)
{
    int year;

    if (tm == RT_NULL)
    {
        return RT_FALSE;
    }

    year = tm->tm_year + 1900;
    if ((year < 2000) || (year > 2099))
    {
        return RT_FALSE;
    }

    if ((tm->tm_mon < 0) || (tm->tm_mon > 11))
    {
        return RT_FALSE;
    }

    if ((tm->tm_mday < 1) || (tm->tm_mday > month_days(year, tm->tm_mon)))
    {
        return RT_FALSE;
    }

    if ((tm->tm_wday < 0) || (tm->tm_wday > 6))
    {
        return RT_FALSE;
    }

    if ((tm->tm_hour < 0) || (tm->tm_hour > 23) ||
        (tm->tm_min < 0) || (tm->tm_min > 59) ||
        (tm->tm_sec < 0) || (tm->tm_sec > 59))
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

static rt_err_t ds1307_read_regs(struct ds1307_device *dev, rt_uint8_t reg, rt_uint8_t *buf, rt_uint8_t len)
{
    struct rt_i2c_msg msgs[2];

    if ((dev == RT_NULL) || (dev->i2c == RT_NULL) || (buf == RT_NULL) || (len == 0))
    {
        return -RT_EINVAL;
    }

    msgs[0].addr  = dev->addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].len   = 1;
    msgs[0].buf   = &reg;

    msgs[1].addr  = dev->addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].len   = len;
    msgs[1].buf   = buf;

    return (rt_i2c_transfer(dev->i2c, msgs, 2) == 2) ? RT_EOK : -RT_ERROR;
}

static rt_err_t ds1307_write_regs(struct ds1307_device *dev, rt_uint8_t reg, const rt_uint8_t *buf, rt_uint8_t len)
{
    rt_uint8_t data[8];

    if ((dev == RT_NULL) || (dev->i2c == RT_NULL) || (buf == RT_NULL) ||
        (len == 0) || (len >= sizeof(data)))
    {
        return -RT_EINVAL;
    }

    data[0] = reg;
    rt_memcpy(&data[1], buf, len);

    return (rt_i2c_master_send(dev->i2c, dev->addr, 0, data, len + 1) == (len + 1))
           ? RT_EOK : -RT_ERROR;
}

static rt_err_t ds1307_probe(struct ds1307_device *dev)
{
    rt_uint8_t sec;

    return ds1307_read_regs(dev, DS1307_REG_SEC, &sec, 1);
}

rt_err_t ds1307_init(void)
{
    if (g_ds1307.i2c == RT_NULL)
    {
        g_ds1307.i2c = rt_i2c_bus_device_find(g_ds1307.bus_name);
        if (g_ds1307.i2c == RT_NULL)
        {
            rt_kprintf("ds1307: i2c bus %s not found\n", g_ds1307.bus_name);
            return -RT_ENOSYS;
        }
    }

    return ds1307_probe(&g_ds1307);
}

rt_err_t ds1307_get_time(struct tm *tm)
{
    rt_uint8_t buf[7];
    rt_uint8_t hour;
    rt_uint8_t wday;

    if (tm == RT_NULL)
    {
        return -RT_EINVAL;
    }

    if (ds1307_read_regs(&g_ds1307, DS1307_REG_SEC, buf, sizeof(buf)) != RT_EOK)
    {
        return -RT_ERROR;
    }

    if ((buf[DS1307_REG_SEC] & DS1307_SEC_CH) != 0)
    {
        if (!g_ds1307.clock_halt_reported)
        {
            rt_kprintf("ds1307: clock halted, please set time\n");
            g_ds1307.clock_halt_reported = RT_TRUE;
        }
        return -RT_ERROR;
    }

    if (!bcd_in_range(buf[DS1307_REG_SEC] & 0x7F, 0, 59) ||
        !bcd_in_range(buf[DS1307_REG_MIN] & 0x7F, 0, 59) ||
        !bcd_in_range(buf[DS1307_REG_MDAY] & 0x3F, 1, 31) ||
        !bcd_in_range(buf[DS1307_REG_MON] & 0x1F, 1, 12) ||
        !bcd_in_range(buf[DS1307_REG_YEAR], 0, 99))
    {
        return -RT_ERROR;
    }

    if ((buf[DS1307_REG_HOUR] & DS1307_HOUR_12H) != 0)
    {
        hour = bcd2bin(buf[DS1307_REG_HOUR] & 0x1F);
        if ((hour < 1) || (hour > 12))
        {
            return -RT_ERROR;
        }

        if ((buf[DS1307_REG_HOUR] & DS1307_HOUR_PM) != 0)
        {
            if (hour != 12)
            {
                hour += 12;
            }
        }
        else if (hour == 12)
        {
            hour = 0;
        }
    }
    else
    {
        if (!bcd_in_range(buf[DS1307_REG_HOUR] & 0x3F, 0, 23))
        {
            return -RT_ERROR;
        }
        hour = bcd2bin(buf[DS1307_REG_HOUR] & 0x3F);
    }

    if (!bcd_in_range(buf[DS1307_REG_WDAY] & 0x07, 1, 7))
    {
        return -RT_ERROR;
    }
    wday = bcd2bin(buf[DS1307_REG_WDAY] & 0x07);

    rt_memset(tm, 0, sizeof(*tm));
    tm->tm_sec  = bcd2bin(buf[DS1307_REG_SEC] & 0x7F);
    tm->tm_min  = bcd2bin(buf[DS1307_REG_MIN] & 0x7F);
    tm->tm_hour = hour;
    tm->tm_wday = wday - 1;
    tm->tm_mday = bcd2bin(buf[DS1307_REG_MDAY] & 0x3F);
    tm->tm_mon  = bcd2bin(buf[DS1307_REG_MON] & 0x1F) - 1;
    tm->tm_year = bcd2bin(buf[DS1307_REG_YEAR]) + 100;
    tm->tm_isdst = -1;

    if (!tm_is_valid(tm))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

rt_err_t ds1307_set_time(const struct tm *tm)
{
    rt_uint8_t buf[7];

    if (!tm_is_valid(tm))
    {
        return -RT_EINVAL;
    }

    buf[DS1307_REG_SEC]  = bin2bcd(tm->tm_sec);
    buf[DS1307_REG_MIN]  = bin2bcd(tm->tm_min);
    buf[DS1307_REG_HOUR] = bin2bcd(tm->tm_hour);
    buf[DS1307_REG_WDAY] = bin2bcd(tm->tm_wday + 1);
    buf[DS1307_REG_MDAY] = bin2bcd(tm->tm_mday);
    buf[DS1307_REG_MON]  = bin2bcd(tm->tm_mon + 1);
    buf[DS1307_REG_YEAR] = bin2bcd(tm->tm_year - 100);

    g_ds1307.clock_halt_reported = RT_FALSE;

    return ds1307_write_regs(&g_ds1307, DS1307_REG_SEC, buf, sizeof(buf));
}

static rt_err_t ds1307_backend_init(void *user_data)
{
    RT_UNUSED(user_data);

    return ds1307_init();
}

static rt_err_t ds1307_backend_get_time(void *user_data, struct tm *tm)
{
    RT_UNUSED(user_data);

    return ds1307_get_time(tm);
}

static rt_err_t ds1307_backend_set_time(void *user_data, const struct tm *tm)
{
    RT_UNUSED(user_data);

    return ds1307_set_time(tm);
}

static const struct ns800_rtc_ops ds1307_rtc_ops =
{
    ds1307_backend_init,
    ds1307_backend_get_time,
    ds1307_backend_set_time,
};

int rt_hw_ds1307_init(void)
{
    rt_err_t result;

    result = ns800_rtc_register("ds1307", &ds1307_rtc_ops, &g_ds1307);
    if (result != RT_EOK)
    {
        rt_kprintf("ds1307: register rtc backend failed, result %d\n", result);
        return -1;
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_ds1307_init);

