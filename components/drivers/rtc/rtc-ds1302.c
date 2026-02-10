/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include "rtc_dm.h"

#define DBG_TAG "rtc.ds1302"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define RTC_CMD_READ            0x81    /* Read command */
#define RTC_CMD_WRITE           0x80    /* Write command */

#define RTC_CMD_WRITE_ENABLE    0x00    /* Write enable */
#define RTC_CMD_WRITE_DISABLE   0x80    /* Write disable */

#define RTC_ADDR_RAM0           0x20    /* Address of RAM0 */
#define RTC_ADDR_TCR            0x08    /* Address of trickle charge register */
#define RTC_CLCK_BURST          0x1F    /* Address of clock burst */
#define RTC_CLCK_LEN            0x08    /* Size of clock burst */
#define RTC_ADDR_CTRL           0x07    /* Address of control register */
#define RTC_ADDR_YEAR           0x06    /* Address of year register */
#define RTC_ADDR_DAY            0x05    /* Address of day of week register */
#define RTC_ADDR_MON            0x04    /* Address of month register */
#define RTC_ADDR_DATE           0x03    /* Address of day of month register */
#define RTC_ADDR_HOUR           0x02    /* Address of hour register */
#define RTC_ADDR_MIN            0x01    /* Address of minute register */
#define RTC_ADDR_SEC            0x00    /* Address of second register */

static rt_err_t ds1302_rtc_get_time(struct rt_spi_device *spi_dev, time_t *sec)
{
    struct tm tm;
    rt_err_t err;
    rt_uint8_t addr = RTC_CLCK_BURST << 1 | RTC_CMD_READ, buf[RTC_CLCK_LEN - 1];

    err = rt_spi_send_then_recv(spi_dev, &addr, sizeof(addr), buf, sizeof(buf));

    if (err)
    {
        return err;
    }

    /* Decode the registers */
    tm.tm_sec = rt_bcd2bin(buf[RTC_ADDR_SEC]);
    tm.tm_min = rt_bcd2bin(buf[RTC_ADDR_MIN]);
    tm.tm_hour = rt_bcd2bin(buf[RTC_ADDR_HOUR]);
    tm.tm_wday = buf[RTC_ADDR_DAY] - 1;
    tm.tm_mday = rt_bcd2bin(buf[RTC_ADDR_DATE]);
    tm.tm_mon = rt_bcd2bin(buf[RTC_ADDR_MON]) - 1;
    tm.tm_year = rt_bcd2bin(buf[RTC_ADDR_YEAR]) + 100;

    *sec = timegm(&tm);

    return RT_EOK;
}

static rt_err_t ds1302_rtc_set_time(struct rt_spi_device *spi_dev, time_t *sec)
{
    rt_err_t err;
    struct tm *tm;
    rt_uint8_t buf[1 + RTC_CLCK_LEN], *bp;

    tm = localtime(sec);

    /* Enable writing */
    bp = buf;
    *bp++ = RTC_ADDR_CTRL << 1 | RTC_CMD_WRITE;
    *bp++ = RTC_CMD_WRITE_ENABLE;

    err = rt_spi_send_then_recv(spi_dev, buf, 2, RT_NULL, 0);

    if (err)
    {
        return err;
    }

    /* Write registers starting at the first time/date address. */
    bp = buf;
    *bp++ = RTC_CLCK_BURST << 1 | RTC_CMD_WRITE;

    *bp++ = rt_bin2bcd(tm->tm_sec);
    *bp++ = rt_bin2bcd(tm->tm_min);
    *bp++ = rt_bin2bcd(tm->tm_hour);
    *bp++ = rt_bin2bcd(tm->tm_mday);
    *bp++ = rt_bin2bcd(tm->tm_mon + 1);
    *bp++ = tm->tm_wday + 1;
    *bp++ = rt_bin2bcd(tm->tm_year % 100);
    *bp++ = RTC_CMD_WRITE_DISABLE;

    return rt_spi_send_then_recv(spi_dev, buf, sizeof(buf), RT_NULL, 0);
}

static rt_err_t ds1302_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct rt_spi_device *spi_dev = dev->user_data;

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        err = ds1302_rtc_get_time(spi_dev, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        err = ds1302_rtc_set_time(spi_dev, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        err = ds1302_rtc_get_time(spi_dev, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        err = ds1302_rtc_set_time(spi_dev, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        err = -RT_ENOSYS;
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops ds1302_rtc_ops =
{
    .control = ds1302_rtc_control,
};
#endif

static rt_err_t ds1302_rtc_probe(struct rt_spi_device *spi_dev)
{
    rt_err_t err = RT_EOK;
    const char *dev_name;
    rt_uint8_t addr, buf[4];

    if (spi_dev->config.max_hz > 2000000)
    {
        LOG_E("Speed is too high");
        return -RT_EINVAL;
    }
    else if (spi_dev->config.mode & RT_SPI_CPHA)
    {
        LOG_E("Bad mode");
        return -RT_EINVAL;
    }

    addr = RTC_ADDR_CTRL << 1 | RTC_CMD_READ;

    if ((err = rt_spi_send_then_recv(spi_dev, &addr, sizeof(addr), buf, 1)))
    {
        LOG_E("Control register read error = %s", rt_strerror(err));
        return err;
    }

    if ((buf[0] & ~RTC_CMD_WRITE_DISABLE) != 0)
    {
        if ((err = rt_spi_send_then_recv(spi_dev, &addr, sizeof(addr), buf, 1)))
        {
            LOG_E("Control register read error = %s", rt_strerror(err));
            return err;
        }

        if ((buf[0] & ~RTC_CMD_WRITE_DISABLE) != 0)
        {
            LOG_E("Junk in control register");
            return -RT_EIO;
        }
    }

    if (buf[0] == 0)
    {
        buf[0] = RTC_ADDR_CTRL << 1 | RTC_CMD_WRITE;
        buf[1] = RTC_CMD_WRITE_DISABLE;

        if ((err = rt_spi_send_then_recv(spi_dev, buf, 2, RT_NULL, 0)))
        {
            LOG_E("Control register write error = %s", rt_strerror(err));
            return err;
        }

        addr = RTC_ADDR_CTRL << 1 | RTC_CMD_READ;

        if ((err = rt_spi_send_then_recv(spi_dev, &addr, sizeof(addr), buf, 1)))
        {
            LOG_E("Reading control register error = %s", rt_strerror(err));
            return err;
        }

        if (buf[0] != RTC_CMD_WRITE_DISABLE)
        {
            LOG_E("Failed to detect chip");
            return -RT_EIO;
        }
    }

    spi_dev->parent.user_data = spi_dev;

    spi_dev->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    spi_dev->parent.ops = &ds1302_rtc_ops;
#else
    spi_dev->parent.control = ds1302_rtc_control;
#endif

    rtc_dev_set_name(&spi_dev->parent);
    dev_name = rt_dm_dev_get_name(&spi_dev->parent);
    err = rt_device_register(&spi_dev->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    return err;
}

static rt_err_t ds1302_rtc_remove(struct rt_spi_device *spi_dev)
{
    rt_device_unregister(&spi_dev->parent);

    return RT_EOK;
}

static const struct rt_spi_device_id ds1302_rtc_ids[] =
{
    { .name = "ds1302" },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id ds1302_rtc_ofw_ids[] =
{
    { .compatible = "maxim,ds1302" },
    { /* sentinel */ },
};

static struct rt_spi_driver ds1302_rtc_driver =
{
    .ids = ds1302_rtc_ids,
    .ofw_ids = ds1302_rtc_ofw_ids,

    .probe = ds1302_rtc_probe,
    .remove = ds1302_rtc_remove,
};
RT_SPI_DRIVER_EXPORT(ds1302_rtc_driver);
