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

#define DBG_TAG "rtc.ds1307"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define RTC_SEC_REG_ADDR            0x00
#define RTC_MIN_REG_ADDR            0x01
#define RTC_HR_REG_ADDR             0x02
#define RTC_DAY_REG_ADDR            0x03
#define RTC_DATE_REG_ADDR           0x04
#define RTC_MON_REG_ADDR            0x05
#define RTC_YR_REG_ADDR             0x06
#define RTC_CTL_REG_ADDR            0x07

#define DS1337_CTL_REG_ADDR         0x0e
#define DS1337_STAT_REG_ADDR        0x0f
#define DS1340_STAT_REG_ADDR        0x09

#define RTC_STAT_BIT_A1I            0x01
#define RTC_STAT_BIT_A2I            0x02
#define RTC_STAT_BIT_OSF            0x80

#define RTC_SEC_BIT_CH              0x80    /* Clock Halt (in Register 0) */

/* DS1307-specific bits */
#define RTC_CTL_BIT_RS0             0x01    /* Rate select 0 */
#define RTC_CTL_BIT_RS1             0x02    /* Rate select 1 */
#define RTC_CTL_BIT_SQWE            0x10    /* Square Wave Enable */
#define RTC_CTL_BIT_OUT             0x80    /* Output Control */

/* DS1337-specific bits */
#define DS1337_CTL_BIT_A1IE         0x01
#define DS1337_CTL_BIT_A2IE         0x02
#define DS1337_CTL_BIT_RS1          0x08    /* Rate select 1 */
#define DS1337_CTL_BIT_RS2          0x10    /* Rate select 2 */
#define DS1337_CTL_BIT_EOSC         0x80    /* Enable Oscillator */

/* DS1339-specific bits */
#define DS1339_ALARM1_REG_SECS      0x07

/* DS1340-specific bits */
#define DS1340_SEC_BIT_EOSC         0x80    /* Enable Oscillator */
#define DS1340_CTL_BIT_OUT          0x80    /* Output Control */

/* MCP7941X-specific bits */
#define MCP794XX_ALARM0_REG_ADDR    0x0d
#define MCP794XX_BIT_ALMX_IF        RT_BIT(3)
#define MCP794XX_BIT_ALMX_C0        RT_BIT(4)
#define MCP794XX_BIT_ALMX_C1        RT_BIT(5)
#define MCP794XX_BIT_ALMX_C2        RT_BIT(6)
#define MCP794XX_BIT_ALMX_POL       RT_BIT(7)
#define MCP794XX_MSK_ALMX_MATCH     (MCP794XX_BIT_ALMX_C0 | MCP794XX_BIT_ALMX_C1 | MCP794XX_BIT_ALMX_C2)
#define MCP794XX_BIT_ALM0_EN        0x10
#define MCP7941X_BIT_ST             0x80
#define MCP7941X_BIT_VBATEN         0x08

enum ds_type
{
    ds1307,
    ds1337,
    ds1338,
    ds1339,
    ds1340,
    m41t11,
    mcp794xx,
};

struct ds1307_rtc
{
    struct rt_device parent;

    int irq;
    enum ds_type type;
    struct rt_i2c_client *client;
    struct rt_thread *irq_thread;

    struct rt_rtc_wkalarm wkalarm;
};

#define raw_to_ds1307_rtc(raw) rt_container_of(raw, struct ds1307_rtc, parent)

static rt_int32_t i2c_read_byte(struct rt_i2c_client *client,
        rt_uint8_t command)
{
    rt_int32_t res;
    rt_uint8_t ret = 0;
    struct rt_i2c_msg msg[2];

    msg[0].buf = &command;
    msg[0].addr = client->client_addr;
    msg[0].len = 1;
    msg[0].flags = RT_I2C_WR;

    msg[1].buf = &ret;
    msg[1].addr = client->client_addr;
    msg[1].len = 1;
    msg[1].flags = RT_I2C_RD;

    res = rt_i2c_transfer(client->bus, msg, 2);

    return res == 2 ? ret : res;
}

static rt_int32_t i2c_write_byte(struct rt_i2c_client *client,
        rt_uint8_t command, rt_uint8_t value)
{
    rt_int32_t res;
    struct rt_i2c_msg msg[1];
    rt_uint8_t data[2] = { command, value };

    msg[0].buf = data;
    msg[0].addr = client->client_addr;
    msg[0].len = 2;
    msg[0].flags = RT_I2C_WR;

    res = rt_i2c_transfer(client->bus, msg, 1);

    return res == 1 ? 0 : res;
}

static rt_int32_t i2c_update_byte_bits(struct rt_i2c_client *client,
        rt_uint8_t command, rt_uint8_t mask, rt_uint8_t value)
{
    rt_int32_t res = i2c_read_byte(client, command);

    if (res < 0)
    {
        return res;
    }

    res &= ~mask;
    res |= value;

    return i2c_write_byte(client, command, res);
}

/* Returns the number of read bytes */
static rt_int32_t i2c_read_block(struct rt_i2c_client *client,
        rt_uint8_t command, rt_uint8_t length, rt_uint8_t *values)
{
    struct rt_i2c_msg msg[2];

    msg[0].buf = &command;
    msg[0].addr = client->client_addr;
    msg[0].len = 1;
    msg[0].flags = RT_I2C_WR;

    msg[1].buf = values;
    msg[1].addr = client->client_addr;
    msg[1].len = length;
    msg[1].flags = RT_I2C_RD;

    return rt_i2c_transfer(client->bus, msg, 2);
}

static rt_int32_t i2c_write_block(struct rt_i2c_client *client,
        rt_uint8_t command, rt_uint8_t length, const rt_uint8_t *values)
{
    rt_uint8_t data[32];
    struct rt_i2c_msg msg[1];

    length = rt_min_t(rt_uint8_t, length, RT_ARRAY_SIZE(data) - 1);

    data[0] = command;
    rt_memcpy(&data[1], values, length);

    msg[0].buf = data;
    msg[0].addr = client->client_addr;
    msg[0].len = length + 1;
    msg[0].flags = RT_I2C_WR;

    return rt_i2c_transfer(client->bus, msg, 1);
}

static void ds1307_rtc_read_time(struct ds1307_rtc *ds1307, time_t *sec)
{
    rt_uint8_t data[7];
    struct tm tm;
    struct rt_i2c_client *client = ds1307->client;

    if (i2c_read_block(client, 0, sizeof(data), data) > 0)
    {
        int reg = -1;

        if (ds1307->type == ds1337)
        {
            reg = DS1337_STAT_REG_ADDR;
        }
        if (ds1307->type == ds1340)
        {
            reg = DS1340_STAT_REG_ADDR;
        }

        if (reg >= 0)
        {
            rt_int32_t status = i2c_read_byte(client, reg);

            if (status >= 0 && (status & RTC_STAT_BIT_OSF))
            {
                status &= ~RTC_STAT_BIT_OSF;

                i2c_write_byte(client, reg, status);
            }
        }

        tm.tm_sec  = rt_bcd2bin(data[RTC_SEC_REG_ADDR] & 0x7f);
        tm.tm_min  = rt_bcd2bin(data[RTC_MIN_REG_ADDR] & 0x7f);
        tm.tm_hour = rt_bcd2bin(data[RTC_HR_REG_ADDR] & 0x3f);
        tm.tm_mday = rt_bcd2bin(data[RTC_DATE_REG_ADDR] & 0x3f);
        tm.tm_mon  = rt_bcd2bin(data[RTC_MON_REG_ADDR] & 0x1f) - 1;
        tm.tm_year = rt_bcd2bin(data[RTC_YR_REG_ADDR]) + 100;
        tm.tm_wday = rt_bcd2bin(data[RTC_DAY_REG_ADDR] & 0x07) - 1;
        tm.tm_yday = 0;
        tm.tm_isdst = 0;

        *sec = timegm(&tm);
    }
}

static void ds1307_rtc_set_time(struct ds1307_rtc *ds1307, time_t *sec)
{
    rt_uint8_t buf[7];
    struct tm *tm;
    struct rt_i2c_client *client = ds1307->client;

    tm = localtime(sec);

    buf[RTC_YR_REG_ADDR] = rt_bin2bcd(tm->tm_year - 100);
    buf[RTC_MON_REG_ADDR] = rt_bin2bcd(tm->tm_mon + 1);
    buf[RTC_DAY_REG_ADDR] = rt_bin2bcd(tm->tm_wday + 1);
    buf[RTC_DATE_REG_ADDR] = rt_bin2bcd(tm->tm_mday);
    buf[RTC_HR_REG_ADDR] = rt_bin2bcd(tm->tm_hour);
    buf[RTC_MIN_REG_ADDR] = rt_bin2bcd(tm->tm_min);
    buf[RTC_SEC_REG_ADDR] = rt_bin2bcd(tm->tm_sec);

    if (ds1307->type == mcp794xx)
    {
        buf[RTC_DAY_REG_ADDR] |= MCP7941X_BIT_VBATEN;
        buf[RTC_SEC_REG_ADDR] |= MCP7941X_BIT_ST;
    }

    if (i2c_write_block(client, 0, sizeof(buf), buf) >= 0)
    {
        if (ds1307->type == ds1337)
        {
            i2c_write_byte(client, DS1337_CTL_REG_ADDR, 0);
        }
    }
}

static int ds1307_rtc_alarm_irq_enable(struct ds1307_rtc *ds1307, rt_bool_t enabled)
{
    struct rt_i2c_client *client = ds1307->client;

    if (ds1307->type == mcp794xx)
    {
        return i2c_update_byte_bits(client, RTC_CTL_REG_ADDR,
                MCP794XX_BIT_ALM0_EN, enabled ? MCP794XX_BIT_ALM0_EN : 0);
    }

    return i2c_update_byte_bits(client, DS1337_CTL_REG_ADDR,
            DS1337_CTL_BIT_A1IE, enabled ? DS1337_CTL_BIT_A1IE : 0);
}

static int ds1307_rtc_read_alarm(struct ds1307_rtc *ds1307,
        struct rt_rtc_wkalarm *alarm)
{
    int res;
    struct rt_i2c_client *client = ds1307->client;

    if (ds1307->type == mcp794xx)
    {
        rt_uint8_t regs[10];

        res = i2c_read_block(client, RTC_CTL_REG_ADDR, sizeof(regs), regs);

        if (res < 0)
        {
            return res;
        }

        alarm->enable = !!(regs[0] & MCP794XX_BIT_ALM0_EN);

        /* Report alarm 0 time assuming 24-hour and day-of-month modes. */
        alarm->tm_sec = rt_bcd2bin(regs[3] & 0x7f);
        alarm->tm_min = rt_bcd2bin(regs[4] & 0x7f);
        alarm->tm_hour = rt_bcd2bin(regs[5] & 0x3f);
        /* alarm->tm_wday = rt_bcd2bin(regs[6] & 0x7) - 1; */
        alarm->tm_mday = rt_bcd2bin(regs[7] & 0x3f);
        alarm->tm_mon = rt_bcd2bin(regs[8] & 0x1f) - 1;
        alarm->tm_year = -1;
    }
    else
    {
        rt_uint8_t regs[9];

        res = i2c_read_block(client, DS1339_ALARM1_REG_SECS, sizeof(regs), regs);

        if (res < 0)
        {
            return res;
        }

        alarm->tm_sec = rt_bcd2bin(regs[0] & 0x7f);
        alarm->tm_min = rt_bcd2bin(regs[1] & 0x7f);
        alarm->tm_hour = rt_bcd2bin(regs[2] & 0x3f);
        alarm->tm_mday = rt_bcd2bin(regs[3] & 0x3f);
        alarm->enable = !!(regs[7] & DS1337_CTL_BIT_A1IE);
    }

    return RT_EOK;
}

static int ds1307_rtc_set_alarm(struct ds1307_rtc *ds1307,
        struct rt_rtc_wkalarm *alarm)
{
    int res;
    struct rt_i2c_client *client = ds1307->client;
    struct rt_rtc_wkalarm *wkalarm = &ds1307->wkalarm;

    if (ds1307->type == mcp794xx)
    {
        rt_uint8_t regs[7];

        res = i2c_read_block(client, RTC_CTL_REG_ADDR, sizeof(regs), regs);

        if (res < 0)
        {
            return res;
        }

        /* Set alarm 0, using 24-hour and day-of-month modes. */
        regs[3] = rt_bin2bcd(alarm->tm_sec);
        regs[4] = rt_bin2bcd(alarm->tm_min);
        regs[5] = rt_bin2bcd(alarm->tm_hour);
        regs[6] = MCP7941X_BIT_VBATEN;
        regs[7] = rt_bin2bcd(alarm->tm_mday);
        regs[8] = rt_bin2bcd(alarm->tm_mon + 1);

        /* Clear the alarm 0 interrupt flag. */
        regs[6] &= ~MCP794XX_BIT_ALMX_IF;
        /* Set alarm match: second, minute, hour, day, date, month. */
        regs[6] |= MCP794XX_MSK_ALMX_MATCH;
        /* Disable interrupt. We will not enable until completely programmed */
        regs[0] &= ~MCP794XX_BIT_ALM0_EN;

        res = i2c_write_block(client, RTC_CTL_REG_ADDR, sizeof(regs), regs);

        if (res < 0)
        {
            return res;
        }
    }
    else
    {
        rt_uint8_t regs[9], control, status;

        res = i2c_read_block(client, DS1339_ALARM1_REG_SECS, sizeof(regs), regs);

        if (res < 0)
        {
            return res;
        }

        control = regs[7];
        status = regs[8];

        /* Set ALARM1, using 24 hour and day-of-month modes */
        regs[0] = rt_bin2bcd(alarm->tm_sec);
        regs[1] = rt_bin2bcd(alarm->tm_min);
        regs[2] = rt_bin2bcd(alarm->tm_hour);
        regs[3] = rt_bin2bcd(alarm->tm_mday);

        /* Set ALARM2 to non-garbage */
        regs[4] = 0;
        regs[5] = 0;
        regs[6] = 0;

        /* Disable alarms */
        regs[7] = control & ~(DS1337_CTL_BIT_A1IE | DS1337_CTL_BIT_A2IE);
        regs[8] = status & ~(RTC_STAT_BIT_A1I | RTC_STAT_BIT_A2I);

        res = i2c_write_block(client, DS1339_ALARM1_REG_SECS, sizeof(regs), regs);

        if (res < 0)
        {
            return res;
        }
    }

    res = ds1307_rtc_alarm_irq_enable(ds1307, wkalarm->enable);

    if (!(res < 0))
    {
        wkalarm->enable = alarm->enable;
        wkalarm->tm_hour = alarm->tm_hour;
        wkalarm->tm_min = alarm->tm_min;
        wkalarm->tm_sec = alarm->tm_sec;
    }

    return res;
}

static rt_err_t ds1307_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct ds1307_rtc *ds1307 = raw_to_ds1307_rtc(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        ds1307_rtc_read_time(ds1307, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        ds1307_rtc_set_time(ds1307, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        ds1307_rtc_read_time(ds1307, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        ds1307_rtc_set_time(ds1307, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        err = ds1307_rtc_read_alarm(ds1307, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        err = ds1307_rtc_set_alarm(ds1307, args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops ds1307_rtc_ops =
{
    .control = ds1307_rtc_control,
};
#endif

static void ds1307_rtc_thread_isr(void *param)
{
    struct ds1307_rtc *ds1307 = param;
    struct rt_i2c_client *client = ds1307->client;

    while (RT_TRUE)
    {
        rt_thread_suspend(ds1307->irq_thread);
        rt_schedule();

        if (ds1307->type == mcp794xx)
        {
            rt_int32_t reg = i2c_read_byte(client, MCP794XX_ALARM0_REG_ADDR);

            if (reg < 0 || !(reg & MCP794XX_BIT_ALMX_IF))
            {
                continue;
            }

            reg &= ~MCP794XX_BIT_ALMX_IF;

            if (i2c_write_byte(client, MCP794XX_ALARM0_REG_ADDR, reg) < 0)
            {
                continue;
            }

            if (i2c_update_byte_bits(client, RTC_CTL_REG_ADDR, MCP794XX_BIT_ALM0_EN, 0) < 0)
            {
                continue;
            }
        }
        else
        {
            rt_int32_t reg = i2c_read_byte(client, DS1337_STAT_REG_ADDR);

            if (reg < 0 || !(reg & RTC_STAT_BIT_A1I))
            {
                continue;
            }

            reg &= ~RTC_STAT_BIT_A1I;
            i2c_write_byte(client, DS1337_STAT_REG_ADDR, reg);

            if (i2c_update_byte_bits(client, DS1337_CTL_REG_ADDR, DS1337_CTL_BIT_A1IE, 0) < 0)
            {
                continue;
            }
        }

        rt_alarm_update(&ds1307->parent, 1);
    }
}

static void ds1307_rtc_isr(int irqno, void *param)
{
    struct ds1307_rtc *ds1307 = param;

    rt_thread_resume(ds1307->irq_thread);
}

static rt_err_t ds1307_rtc_probe(struct rt_i2c_client *client)
{
    rt_err_t err;
    const char *dev_name;
    struct rt_device *dev = &client->parent;
    struct ds1307_rtc *ds1307 = rt_calloc(1, sizeof(*ds1307));

    if (!ds1307)
    {
        return -RT_ENOMEM;
    }

    ds1307->type = (rt_ubase_t)rt_i2c_client_id_data(client);
    ds1307->irq = rt_dm_dev_get_irq(dev, 0);
    ds1307->client = client;

    if (ds1307->irq >= 0)
    {
        ds1307->irq_thread = rt_thread_create("rtc-ds1307", &ds1307_rtc_thread_isr,
                ds1307, DM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 2, 10);

        if (!ds1307->irq_thread)
        {
            err = -RT_ERROR;
            LOG_E("Create RTC IRQ thread fail");
            goto _fail;
        }

        rt_thread_startup(ds1307->irq_thread);

        rt_hw_interrupt_install(ds1307->irq, ds1307_rtc_isr, ds1307, "rtc-ds1307");
        rt_hw_interrupt_umask(ds1307->irq);
    }

    dev->user_data = ds1307;

    ds1307->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    ds1307->parent.ops = &ds1307_rtc_ops;
#else
    ds1307->parent.control = ds1307_rtc_control;
#endif

    rtc_dev_set_name(&ds1307->parent);
    dev_name = rt_dm_dev_get_name(&ds1307->parent);
    rt_device_register(&ds1307->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    return RT_EOK;

_fail:
    if (ds1307->irq_thread)
    {
        rt_thread_delete(ds1307->irq_thread);
    }
    rt_free(ds1307);

    return err;
}

static rt_err_t ds1307_rtc_remove(struct rt_i2c_client *client)
{
    struct ds1307_rtc *ds1307 = client->parent.user_data;

    if (ds1307->irq >= 0)
    {
        if (ds1307->wkalarm.enable)
        {
            ds1307_rtc_alarm_irq_enable(ds1307, RT_FALSE);
        }

        rt_hw_interrupt_mask(ds1307->irq);
        rt_pic_detach_irq(ds1307->irq, ds1307);

        rt_thread_delete(ds1307->irq_thread);
    }

    rt_device_unregister(&ds1307->parent);

    rt_free(ds1307);

    return RT_EOK;
}

static const struct rt_i2c_device_id ds1307_rtc_ids[] =
{
    { .name = "ds1307", .data = (void *)ds1307 },
    { .name = "ds1337", .data = (void *)ds1337 },
    { .name = "ds1338", .data = (void *)ds1338 },
    { .name = "ds1339", .data = (void *)ds1339 },
    { .name = "ds1340", .data = (void *)ds1340 },
    { .name = "m41t11", .data = (void *)m41t11 },
    { .name = "mcp7940x", .data = (void *)mcp794xx },
    { .name = "mcp7941x", .data = (void *)mcp794xx },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id ds1307_rtc_ofw_ids[] =
{
    { .compatible = "dallas,ds1307", .data = (void *)ds1307 },
    { .compatible = "dallas,ds1337", .data = (void *)ds1337 },
    { .compatible = "dallas,ds1338", .data = (void *)ds1338 },
    { .compatible = "dallas,ds1339", .data = (void *)ds1339 },
    { .compatible = "dallas,ds1340", .data = (void *)ds1340 },
    { .compatible = "microchip,mcp7940x", .data = (void *)mcp794xx },
    { .compatible = "microchip,mcp7941x", .data = (void *)mcp794xx },
    { .compatible = "st,m41t11", .data = (void *)m41t11 },
    { /* sentinel */ },
};

static struct rt_i2c_driver ds1307_rtc_driver =
{
    .ids = ds1307_rtc_ids,
    .ofw_ids = ds1307_rtc_ofw_ids,

    .probe = ds1307_rtc_probe,
    .remove = ds1307_rtc_remove,
};
RT_I2C_DRIVER_EXPORT(ds1307_rtc_driver);
