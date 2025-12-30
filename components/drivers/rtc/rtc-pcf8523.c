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

#define DBG_TAG "rtc.pcf8523"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define PCF8523_REG_CONTROL1        0x00
#define PCF8523_CONTROL1_CAP_SEL    RT_BIT(7)
#define PCF8523_CONTROL1_STOP       RT_BIT(5)
#define PCF8523_CONTROL1_AIE        RT_BIT(1)

#define PCF8523_REG_CONTROL2        0x01
#define PCF8523_CONTROL2_AF         RT_BIT(3)

#define PCF8523_REG_CONTROL3        0x02
#define PCF8523_CONTROL3_PM         RT_GENMASK(7, 5)
#define PCF8523_PM_STANDBY          0x7
#define PCF8523_CONTROL3_BLF        RT_BIT(2) /* battery low bit, read-only */
#define PCF8523_CONTROL3_BSF        RT_BIT(3)

#define PCF8523_REG_SECONDS         0x03
#define PCF8523_SECONDS_OS          RT_BIT(7)

#define PCF8523_REG_MINUTES         0x04
#define PCF8523_REG_HOURS           0x05
#define PCF8523_REG_DAYS            0x06
#define PCF8523_REG_WEEKDAYS        0x07
#define PCF8523_REG_MONTHS          0x08
#define PCF8523_REG_YEARS           0x09

#define PCF8523_REG_MINUTE_ALARM    0x0a
#define PCF8523_REG_HOUR_ALARM      0x0b
#define PCF8523_REG_DAY_ALARM       0x0c
#define PCF8523_REG_WEEKDAY_ALARM   0x0d
#define ALARM_DIS                   RT_BIT(7)

#define PCF8523_REG_OFFSET          0x0e
#define PCF8523_OFFSET_MODE         RT_BIT(7)

#define PCF8523_TMR_CLKOUT_CTRL     0x0f

struct pcf8523_rtc
{
    struct rt_device parent;
    struct rt_clk_node clkout_hw;

    int irq;
    struct rt_i2c_client *client;
    struct rt_thread *irq_thread;

    struct rt_rtc_wkalarm wkalarm;
};

#define raw_to_pcf8523_rtc(raw) rt_container_of(raw, struct pcf8523_rtc, parent)

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

static void pcf8523_rtc_read_time(struct pcf8523_rtc *pcf8523, time_t *sec)
{
    rt_uint8_t regs[10];
    struct tm tm;
    struct rt_i2c_client *client = pcf8523->client;

    if (i2c_read_block(client, PCF8523_REG_CONTROL1, sizeof(regs), regs) < 0)
    {
        return;
    }

    if ((regs[0] & PCF8523_CONTROL1_STOP) || (regs[3] & PCF8523_SECONDS_OS))
    {
        return;
    }

    tm.tm_sec = rt_bcd2bin(regs[3] & 0x7f);
    tm.tm_min = rt_bcd2bin(regs[4] & 0x7f);
    tm.tm_hour = rt_bcd2bin(regs[5] & 0x3f);
    tm.tm_mday = rt_bcd2bin(regs[6] & 0x3f);
    tm.tm_wday = regs[7] & 0x7;
    tm.tm_mon = rt_bcd2bin(regs[8] & 0x1f) - 1;
    tm.tm_year = rt_bcd2bin(regs[9]) + 100;

    *sec = timegm(&tm);
}

static void pcf8523_rtc_set_time(struct pcf8523_rtc *pcf8523, time_t *sec)
{
    rt_uint8_t regs[7];
    struct tm *tm;
    struct rt_i2c_client *client = pcf8523->client;

    if (i2c_update_byte_bits(client, PCF8523_REG_CONTROL1,
            PCF8523_CONTROL1_STOP, PCF8523_CONTROL1_STOP) < 0)
    {
        return;
    }

    tm = localtime(sec);

    regs[0] = rt_bin2bcd(tm->tm_sec);
    regs[1] = rt_bin2bcd(tm->tm_min);
    regs[2] = rt_bin2bcd(tm->tm_hour);
    regs[3] = rt_bin2bcd(tm->tm_mday);
    regs[4] = 0;
    regs[5] = rt_bin2bcd(tm->tm_mon + 1);
    regs[6] = rt_bin2bcd(tm->tm_year - 100);

    if (i2c_write_block(client, PCF8523_REG_SECONDS, sizeof(regs), regs) < 0)
    {
        i2c_update_byte_bits(client, PCF8523_REG_CONTROL1, PCF8523_CONTROL1_STOP, 0);

        return;
    }

    i2c_update_byte_bits(client, PCF8523_REG_CONTROL1, PCF8523_CONTROL1_STOP, 0);
}

static int pcf8523_rtc_alarm_irq_enable(struct pcf8523_rtc *pcf8523, rt_bool_t enabled)
{
    struct rt_i2c_client *client = pcf8523->client;

    return i2c_update_byte_bits(client, PCF8523_REG_CONTROL1,
            PCF8523_CONTROL1_AIE, enabled ? PCF8523_CONTROL1_AIE : 0);
}

static int pcf8523_rtc_read_alarm(struct pcf8523_rtc *pcf8523,
        struct rt_rtc_wkalarm *alarm)
{
    int res;
    rt_uint8_t regs[4];
    struct rt_i2c_client *client = pcf8523->client;

    if ((res = i2c_read_block(client, PCF8523_REG_MINUTE_ALARM, sizeof(regs), regs)))
    {
        return res;
    }

    alarm->tm_sec = 0;
    alarm->tm_min = rt_bcd2bin(regs[0] & 0x7F);
    alarm->tm_hour = rt_bcd2bin(regs[1] & 0x3F);
    alarm->tm_mday = rt_bcd2bin(regs[2] & 0x3F);
    /* alarm->tm_wday = rt_bcd2bin(regs[3] & 0x7); */

    if ((res = i2c_read_byte(client, PCF8523_REG_CONTROL1)) < 0)
    {
        return res;
    }

    alarm->enable = !!(res & PCF8523_CONTROL1_AIE);

    return RT_EOK;
}

static int pcf8523_rtc_set_alarm(struct pcf8523_rtc *pcf8523,
        struct rt_rtc_wkalarm *alarm)
{
    int res;
    rt_uint8_t regs[5];
    struct rt_i2c_client *client = pcf8523->client;
    struct rt_rtc_wkalarm *wkalarm = &pcf8523->wkalarm;

    if ((res = pcf8523_rtc_alarm_irq_enable(pcf8523, RT_FALSE)) < 0)
    {
        return res;
    }

    if ((res = i2c_write_byte(client, PCF8523_REG_CONTROL2, 0)) < 0)
    {
        return res;
    }

    regs[0] = rt_bin2bcd(alarm->tm_min);
    regs[1] = rt_bin2bcd(alarm->tm_hour);
    regs[2] = rt_bin2bcd(alarm->tm_mday);
    regs[3] = ALARM_DIS;

    if ((res = i2c_write_block(client, PCF8523_REG_MINUTE_ALARM, sizeof(regs), regs)))
    {
        return res;
    }

    res = pcf8523_rtc_alarm_irq_enable(pcf8523, alarm->enable);

    if (!(res < 0))
    {
        wkalarm->enable = alarm->enable;
        wkalarm->tm_hour = alarm->tm_hour;
        wkalarm->tm_min = alarm->tm_min;
        wkalarm->tm_sec = alarm->tm_sec;
    }

    return res;
}

static rt_err_t pcf8523_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct pcf8523_rtc *pcf8523 = raw_to_pcf8523_rtc(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        pcf8523_rtc_read_time(pcf8523, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        pcf8523_rtc_set_time(pcf8523, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        pcf8523_rtc_read_time(pcf8523, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        pcf8523_rtc_set_time(pcf8523, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        err = pcf8523_rtc_read_alarm(pcf8523, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        err = pcf8523_rtc_set_alarm(pcf8523, args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops pcf8523_rtc_ops =
{
    .control = pcf8523_rtc_control,
};
#endif

static void pcf8523_rtc_thread_isr(void *param)
{
    rt_int32_t res;
    struct pcf8523_rtc *pcf8523 = param;
    struct rt_i2c_client *client = pcf8523->client;

    while (RT_TRUE)
    {
        rt_thread_suspend(pcf8523->irq_thread);
        rt_schedule();

        if ((res = i2c_read_byte(client, PCF8523_REG_CONTROL2)) < 0)
        {
            continue;
        }

        if (res & PCF8523_CONTROL2_AF)
        {
            res &= ~PCF8523_CONTROL2_AF;
            i2c_write_byte(client, PCF8523_REG_CONTROL2, res);

            rt_alarm_update(&pcf8523->parent, 1);
        }
    }
}

static void pcf8523_rtc_isr(int irqno, void *param)
{
    struct pcf8523_rtc *pcf8523 = param;

    rt_thread_resume(pcf8523->irq_thread);
}

static rt_err_t pcf8523_rtc_probe(struct rt_i2c_client *client)
{
    rt_err_t err;
    rt_int32_t res;
    const char *dev_name;
    struct rt_device *dev = &client->parent;
    struct pcf8523_rtc *pcf8523 = rt_calloc(1, sizeof(*pcf8523));

    if (!pcf8523)
    {
        return -RT_ENOMEM;
    }

    pcf8523->irq = rt_dm_dev_get_irq(dev, 0);
    pcf8523->client = client;

#ifdef RT_USING_OFW
    if (dev->ofw_node)
    {
        rt_uint32_t load = 12500, value = 0;

        rt_ofw_prop_read_u32(dev->ofw_node, "quartz-load-femtofarads", &load);

        if (load != 7000)
        {
            value = PCF8523_CONTROL1_CAP_SEL;
        }

        if ((res = i2c_update_byte_bits(client, PCF8523_REG_CONTROL1,
                PCF8523_CONTROL1_CAP_SEL, value)) < 0)
        {
            err = res;
            goto _fail;
        }
    }
#endif /* RT_USING_OFW */

    if ((res = i2c_read_byte(client, PCF8523_REG_SECONDS)) < 0)
    {
        err = res;
        goto _fail;
    }

    if (res & PCF8523_SECONDS_OS)
    {
        if ((res = i2c_read_byte(client, PCF8523_REG_CONTROL3)) < 0)
        {
            err = res;
            goto _fail;
        }

        if (RT_FIELD_GET(PCF8523_CONTROL3_PM, res) == PCF8523_PM_STANDBY)
        {
            res &= ~PCF8523_CONTROL3_PM;

            if ((res = i2c_write_byte(client, PCF8523_REG_CONTROL3, res)) < 0)
            {
                err = res;
                goto _fail;
            }
        }
    }

    if (pcf8523->irq >= 0)
    {
        if ((res = i2c_write_byte(client, PCF8523_TMR_CLKOUT_CTRL, 0x38)) < 0)
        {
            err = res;
            goto _fail;
        }

        pcf8523->irq_thread = rt_thread_create("rtc-pcf8523", &pcf8523_rtc_thread_isr,
                pcf8523, DM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 2, 10);

        if (!pcf8523->irq_thread)
        {
            err = -RT_ERROR;
            LOG_E("Create RTC IRQ thread fail");
            goto _fail;
        }

        rt_thread_startup(pcf8523->irq_thread);

        rt_hw_interrupt_install(pcf8523->irq, pcf8523_rtc_isr, pcf8523, "rtc-pcf8523");
        rt_hw_interrupt_umask(pcf8523->irq);
    }

    dev->user_data = pcf8523;

    pcf8523->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    pcf8523->parent.ops = &pcf8523_rtc_ops;
#else
    pcf8523->parent.control = pcf8523_rtc_control;
#endif

    rtc_dev_set_name(&pcf8523->parent);
    dev_name = rt_dm_dev_get_name(&pcf8523->parent);
    rt_device_register(&pcf8523->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    return RT_EOK;

_fail:
    if (pcf8523->irq_thread)
    {
        rt_thread_delete(pcf8523->irq_thread);
    }
    rt_free(pcf8523);

    return err;
}

static rt_err_t pcf8523_rtc_remove(struct rt_i2c_client *client)
{
    struct pcf8523_rtc *pcf8523 = client->parent.user_data;

    rt_dm_dev_unbind_fwdata(&client->parent, RT_NULL);

    if (pcf8523->irq >= 0)
    {
        if (pcf8523->wkalarm.enable)
        {
            pcf8523_rtc_alarm_irq_enable(pcf8523, RT_FALSE);
        }

        rt_hw_interrupt_mask(pcf8523->irq);
        rt_pic_detach_irq(pcf8523->irq, pcf8523);

        rt_thread_delete(pcf8523->irq_thread);
    }

    rt_device_unregister(&pcf8523->parent);

    rt_free(pcf8523);

    return RT_EOK;
}

static const struct rt_i2c_device_id pcf8523_rtc_ids[] =
{
    { .name = "pcf8523" },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id pcf8523_rtc_ofw_ids[] =
{
    { .compatible = "nxp,pcf8523" },
    { .compatible = "microcrystal,rv8523" },
    { /* sentinel */ },
};

static struct rt_i2c_driver pcf8523_rtc_driver =
{
    .ids = pcf8523_rtc_ids,
    .ofw_ids = pcf8523_rtc_ofw_ids,

    .probe = pcf8523_rtc_probe,
    .remove = pcf8523_rtc_remove,
};
RT_I2C_DRIVER_EXPORT(pcf8523_rtc_driver);
