/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtc.rx8010"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rtc_dm.h"

#define RX8010_SEC              0x10
#define RX8010_MIN              0x11
#define RX8010_HOUR             0x12
#define RX8010_WDAY             0x13
#define RX8010_MDAY             0x14
#define RX8010_MONTH            0x15
#define RX8010_YEAR             0x16
#define RX8010_RESV17           0x17
#define RX8010_ALMIN            0x18
#define RX8010_ALHOUR           0x19
#define RX8010_ALWDAY           0x1a
#define RX8010_TCOUNT0          0x1b
#define RX8010_TCOUNT1          0x1c
#define RX8010_EXT              0x1d
#define RX8010_FLAG             0x1e
#define RX8010_CTRL             0x1f
/* 0x20 to 0x2F are user registers */
#define RX8010_RESV30           0x30
#define RX8010_RESV31           0x31
#define RX8010_IRQ              0x32

#define RX8010_EXT_WADA         RT_BIT(3)

#define RX8010_FLAG_VLF         RT_BIT(1)
#define RX8010_FLAG_AF          RT_BIT(3)
#define RX8010_FLAG_TF          RT_BIT(4)
#define RX8010_FLAG_UF          RT_BIT(5)

#define RX8010_CTRL_AIE         RT_BIT(3)
#define RX8010_CTRL_UIE         RT_BIT(5)
#define RX8010_CTRL_STOP        RT_BIT(6)
#define RX8010_CTRL_TEST        RT_BIT(7)

#define RX8010_ALARM_AE         RT_BIT(7)

struct rx8010_rtc
{
    struct rt_device parent;

    int irq;
    rt_uint8_t ctrlreg;

    struct rt_i2c_client *client;
    struct rt_thread *irq_thread;

    struct rt_rtc_wkalarm wkalarm;
};

#define raw_to_rx8010_rtc(raw) rt_container_of(raw, struct rx8010_rtc, parent)

static rt_err_t rx8010_rtc_write(struct rx8010_rtc *rx8010,
        rt_uint8_t reg, rt_uint8_t value)
{
    rt_int32_t res;
    struct rt_i2c_msg msg[1];
    rt_uint8_t data[sizeof(reg) + sizeof(value)] = { reg };
    struct rt_i2c_client *client = rx8010->client;

    rt_memcpy(&data[sizeof(reg)], &value, sizeof(value));

    msg[0].buf = data;
    msg[0].addr = client->client_addr;
    msg[0].len = sizeof(data);
    msg[0].flags = RT_I2C_WR;

    res = rt_i2c_transfer(client->bus, msg, 1);

    return res > 0 ? RT_EOK : res;
}

static rt_err_t rx8010_rtc_read(struct rx8010_rtc *rx8010,
        rt_uint8_t reg, rt_uint8_t *values)
{
    rt_int32_t res;
    struct rt_i2c_msg msg[2];
    struct rt_i2c_client *client = rx8010->client;

    msg[0].buf = &reg;
    msg[0].addr = client->client_addr;
    msg[0].len = sizeof(reg);
    msg[0].flags = RT_I2C_WR;

    msg[1].buf = (rt_uint8_t *)values;
    msg[1].addr = client->client_addr;
    msg[1].len = sizeof(*values);
    msg[1].flags = RT_I2C_RD;

    res = rt_i2c_transfer(client->bus, msg, 2);

    return res > 0 ? RT_EOK : res;
}

static rt_err_t rx8010_rtc_set_bit(struct rx8010_rtc *rx8010,
        rt_uint8_t reg, rt_uint8_t bit)
{
    rt_err_t err;
    rt_uint8_t value;

    if ((err = rx8010_rtc_read(rx8010, reg, &value)))
    {
        return err;
    }

    return rx8010_rtc_write(rx8010, reg, value | bit);
}

static rt_err_t rx8010_rtc_clear_bit(struct rx8010_rtc *rx8010,
        rt_uint8_t reg, rt_uint8_t bit)
{
    rt_err_t err;
    rt_uint8_t value;

    if ((err = rx8010_rtc_read(rx8010, reg, &value)))
    {
        return err;
    }

    return rx8010_rtc_write(rx8010, reg, value & ~bit);
}

static rt_err_t rx8010_rtc_read_time(struct rx8010_rtc *rx8010, time_t *sec)
{
    struct tm tm;
    rt_err_t err;
    rt_uint8_t flagreg, date[RX8010_YEAR - RX8010_SEC + 1];

    if ((err = rx8010_rtc_read(rx8010, RX8010_FLAG, &flagreg)))
    {
        return err;
    }

    if (flagreg & RX8010_FLAG_VLF)
    {
        LOG_W("Frequency stop detected");

        return -RT_EINVAL;
    }

    for (int i = 0; i < sizeof(date); ++i)
    {
        if ((err = rx8010_rtc_read(rx8010, RX8010_SEC + i, &date[i])))
        {
            return err;
        }
    }

    tm.tm_sec = rt_bcd2bin(date[RX8010_SEC - RX8010_SEC] & 0x7f);
    tm.tm_min = rt_bcd2bin(date[RX8010_MIN - RX8010_SEC] & 0x7f);
    tm.tm_hour = rt_bcd2bin(date[RX8010_HOUR - RX8010_SEC] & 0x3f);
    tm.tm_mday = rt_bcd2bin(date[RX8010_MDAY - RX8010_SEC] & 0x3f);
    tm.tm_mon = rt_bcd2bin(date[RX8010_MONTH - RX8010_SEC] & 0x1f) - 1;
    tm.tm_year = rt_bcd2bin(date[RX8010_YEAR - RX8010_SEC]) + 100;
    tm.tm_wday = __rt_ffs(date[RX8010_WDAY - RX8010_SEC] & 0x7f);

    *sec = timegm(&tm);

    return RT_EOK;
}

static rt_err_t rx8010_rtc_set_time(struct rx8010_rtc *rx8010, time_t *sec)
{
    rt_err_t err;
    struct tm *tm;
    rt_uint8_t date[RX8010_YEAR - RX8010_SEC + 1];

    /* Set STOP bit before changing clock/calendar */
    if ((err = rx8010_rtc_set_bit(rx8010, RX8010_CTRL, RX8010_CTRL_STOP)))
    {
        return err;
    }

    tm = localtime(sec);

    date[RX8010_SEC - RX8010_SEC] = rt_bin2bcd(tm->tm_sec);
    date[RX8010_MIN - RX8010_SEC] = rt_bin2bcd(tm->tm_min);
    date[RX8010_HOUR - RX8010_SEC] = rt_bin2bcd(tm->tm_hour);
    date[RX8010_MDAY - RX8010_SEC] = rt_bin2bcd(tm->tm_mday);
    date[RX8010_MONTH - RX8010_SEC] = rt_bin2bcd(tm->tm_mon + 1);
    date[RX8010_YEAR - RX8010_SEC] = rt_bin2bcd(tm->tm_year - 100);
    date[RX8010_WDAY - RX8010_SEC] = rt_bin2bcd(1 << tm->tm_wday);

    for (int i = 0; i < sizeof(date); ++i)
    {
        if ((err = rx8010_rtc_write(rx8010, RX8010_SEC + i, date[i])))
        {
            return err;
        }
    }

    /* Clear STOP bit after changing clock/calendar */
    if ((err = rx8010_rtc_clear_bit(rx8010, RX8010_CTRL, RX8010_CTRL_STOP)))
    {
        return err;
    }

    if ((err = rx8010_rtc_clear_bit(rx8010, RX8010_FLAG, RX8010_FLAG_VLF)))
    {
        return err;
    }

    return RT_EOK;
}

static rt_err_t rx8010_rtc_read_alarm(struct rx8010_rtc *rx8010,
        struct rt_rtc_wkalarm *alarm)
{
    rt_err_t err;
    rt_uint8_t alarmvals[3], flagreg;

    for (int i = 0; i < RT_ARRAY_SIZE(alarmvals); ++i)
    {
        if ((err = rx8010_rtc_read(rx8010, RX8010_ALMIN + i, &alarmvals[i])))
        {
            return err;
        }
    }

    if ((err = rx8010_rtc_read(rx8010, RX8010_FLAG, &flagreg)))
    {
        return err;
    }

    alarm->tm_sec = 0;
    alarm->tm_min = rt_bcd2bin(alarmvals[0] & 0x7f);
    alarm->tm_hour = rt_bcd2bin(alarmvals[1] & 0x3f);

    if (!(alarmvals[2] & RX8010_ALARM_AE))
    {
        alarm->tm_mday = rt_bcd2bin(alarmvals[2] & 0x7f);
    }

    alarm->enable = !!(rx8010->ctrlreg & RX8010_CTRL_AIE);

    return RT_EOK;
}

static rt_err_t rx8010_alarm_irq_enable(struct rx8010_rtc *rx8010, rt_bool_t enabled)
{
    rt_err_t err;
    rt_uint8_t ctrl;

    ctrl = rx8010->ctrlreg;

    if (enabled)
    {
        ctrl |= RX8010_CTRL_AIE | RX8010_CTRL_UIE;
    }
    else
    {
        ctrl &= ~(RX8010_CTRL_UIE | RX8010_CTRL_AIE);
    }

    if ((err = rx8010_rtc_clear_bit(rx8010, RX8010_FLAG, RX8010_FLAG_AF)))
    {
        return err;
    }

    if (ctrl != rx8010->ctrlreg)
    {
        rx8010->ctrlreg = ctrl;

        if ((err = rx8010_rtc_write(rx8010, RX8010_CTRL, rx8010->ctrlreg)))
        {
            return err;
        }
    }

    return RT_EOK;
}

static rt_err_t rx8010_rtc_set_alarm(struct rx8010_rtc *rx8010,
        struct rt_rtc_wkalarm *alarm)
{
    rt_err_t err;
    rt_uint8_t alarmvals[3];
    struct rt_rtc_wkalarm *wkalarm = &rx8010->wkalarm;

    if (rx8010->ctrlreg & (RX8010_CTRL_AIE | RX8010_CTRL_UIE))
    {
        rx8010->ctrlreg &= ~(RX8010_CTRL_AIE | RX8010_CTRL_UIE);

        if ((err = rx8010_rtc_write(rx8010, RX8010_CTRL, rx8010->ctrlreg)))
        {
            return err;
        }
    }

    if ((err = rx8010_rtc_clear_bit(rx8010, RX8010_FLAG, RX8010_FLAG_AF)))
    {
        return err;
    }

    alarmvals[0] = rt_bin2bcd(alarm->tm_min);
    alarmvals[1] = rt_bin2bcd(alarm->tm_hour);
    alarmvals[2] = rt_bin2bcd(alarm->tm_mday);

    for (int i = 0; i < RT_ARRAY_SIZE(alarmvals) - 1; ++i)
    {
        if ((err = rx8010_rtc_write(rx8010, RX8010_ALMIN + i, alarmvals[i])))
        {
            return err;
        }
    }

    if ((err = rx8010_rtc_clear_bit(rx8010, RX8010_EXT, RX8010_EXT_WADA)))
    {
        return err;
    }

    if (alarmvals[2] == 0)
    {
        alarmvals[2] |= RX8010_ALARM_AE;
    }

    if ((err = rx8010_rtc_write(rx8010, RX8010_ALWDAY, alarmvals[2])))
    {
        return err;
    }

    if (alarm->enable)
    {
        rx8010->ctrlreg |= RX8010_CTRL_UIE | RX8010_CTRL_AIE;

        if ((err = rx8010_rtc_write(rx8010, RX8010_CTRL, rx8010->ctrlreg)))
        {
            return err;
        }
    }

    if (!(err = rx8010_alarm_irq_enable(rx8010, alarm->enable)))
    {
        wkalarm->enable = alarm->enable;
        wkalarm->tm_hour = alarm->tm_hour;
        wkalarm->tm_min = alarm->tm_min;
        wkalarm->tm_sec = alarm->tm_sec;
    }

    return err;
}

static rt_err_t rx8010_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct rx8010_rtc *rx8010 = raw_to_rx8010_rtc(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        err = rx8010_rtc_read_time(rx8010, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        err = rx8010_rtc_set_time(rx8010, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        err = rx8010_rtc_read_time(rx8010, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        err = rx8010_rtc_set_time(rx8010, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        err = rx8010_rtc_read_alarm(rx8010, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        err = rx8010_rtc_set_alarm(rx8010, args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rx8010_rtc_ops =
{
    .control = rx8010_rtc_control,
};
#endif

static void rx8010_rtc_thread_isr(void *param)
{
    rt_err_t err;
    rt_uint8_t flagreg;
    struct rx8010_rtc *rx8010 = param;

    while (RT_TRUE)
    {
        rt_thread_suspend(rx8010->irq_thread);
        rt_schedule();

        if ((err = rx8010_rtc_read(rx8010, RX8010_FLAG, &flagreg)))
        {
            LOG_E("Read flag error = %s", rt_strerror(err));
            continue;
        }

        if (flagreg & RX8010_FLAG_VLF)
        {
            LOG_W("Frequency stop detected");
        }

        if (flagreg & RX8010_FLAG_TF)
        {
            flagreg &= ~RX8010_FLAG_TF;
            rt_alarm_update(&rx8010->parent, 1);
        }

        if (flagreg & RX8010_FLAG_AF)
        {
            flagreg &= ~RX8010_FLAG_AF;
            rt_alarm_update(&rx8010->parent, 1);
        }

        if (flagreg & RX8010_FLAG_UF)
        {
            flagreg &= ~RX8010_FLAG_UF;
            rt_alarm_update(&rx8010->parent, 1);
        }

        if ((err = rx8010_rtc_write(rx8010, RX8010_FLAG, flagreg)))
        {
            LOG_E("Write flag error = %s", rt_strerror(err));
        }
    }
}

static void rx8010_rtc_isr(int irqno, void *param)
{
    struct rx8010_rtc *rx8010 = param;

    rt_thread_resume(rx8010->irq_thread);
}

static rt_err_t rx8010_init(struct rx8010_rtc *rx8010)
{
    rt_err_t err;
    rt_uint8_t ctrl[2];
    int need_clear = 0;

    /* Initialize reserved registers as specified in datasheet */
    if ((err = rx8010_rtc_write(rx8010, RX8010_RESV17, 0xd8)))
    {
        return err;
    }

    if ((err = rx8010_rtc_write(rx8010, RX8010_RESV30, 0x00)))
    {
        return err;
    }

    if ((err = rx8010_rtc_write(rx8010, RX8010_RESV31, 0x08)))
    {
        return err;
    }

    if ((err = rx8010_rtc_write(rx8010, RX8010_IRQ, 0x00)))
    {
        return err;
    }

    err |= rx8010_rtc_read(rx8010, RX8010_FLAG, &ctrl[0]);
    err |= rx8010_rtc_read(rx8010, RX8010_FLAG + 1, &ctrl[1]);

    if (err)
    {
        return err;
    }

    if (ctrl[0] & RX8010_FLAG_VLF)
    {
        LOG_W("Frequency stop was detected");
    }

    if (ctrl[0] & RX8010_FLAG_AF)
    {
        LOG_W("Alarm was detected");
        need_clear = 1;
    }

    if (ctrl[0] & (RX8010_FLAG_TF | RX8010_FLAG_UF))
    {
        need_clear = 1;
    }

    if (need_clear)
    {
        ctrl[0] &= ~(RX8010_FLAG_AF | RX8010_FLAG_TF | RX8010_FLAG_UF);

        if ((err = rx8010_rtc_write(rx8010, RX8010_FLAG, ctrl[0])))
        {
            return err;
        }
    }

    rx8010->ctrlreg = ctrl[1] & ~RX8010_CTRL_TEST;

    return RT_EOK;
}

static rt_err_t rx8010_rtc_probe(struct rt_i2c_client *client)
{
    rt_err_t err;
    const char *dev_name;
    struct rt_device *dev = &client->parent;
    struct rx8010_rtc *rx8010 = rt_calloc(1, sizeof(*rx8010));

    if (!rx8010)
    {
        return -RT_ENOMEM;
    }

    rx8010->client = client;

    if ((err = rx8010_init(rx8010)))
    {
        goto _fail;
    }

    rx8010->irq = rt_dm_dev_get_irq(dev, 0);

    if (rx8010->irq >= 0)
    {
        rx8010->irq_thread = rt_thread_create("rtc-rx8010", &rx8010_rtc_thread_isr,
                rx8010, DM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 2, 10);

        if (!rx8010->irq_thread)
        {
            err = -RT_ERROR;
            LOG_E("Create RTC IRQ thread fail");
            goto _fail;
        }

        rt_thread_startup(rx8010->irq_thread);

        rt_hw_interrupt_install(rx8010->irq, rx8010_rtc_isr, rx8010, "rtc-rx8010");
        rt_hw_interrupt_umask(rx8010->irq);
    }

    dev->user_data = rx8010;

    rx8010->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    rx8010->parent.ops = &rx8010_rtc_ops;
#else
    rx8010->parent.control = rx8010_rtc_control;
#endif

    rtc_dev_set_name(&rx8010->parent);
    dev_name = rt_dm_dev_get_name(&rx8010->parent);
    rt_device_register(&rx8010->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    return RT_EOK;

_fail:
    if (rx8010->irq_thread)
    {
        rt_thread_delete(rx8010->irq_thread);
    }

    rt_free(rx8010);

    return err;
}

static rt_err_t rx8010_rtc_remove(struct rt_i2c_client *client)
{
    struct rx8010_rtc *rx8010 = client->parent.user_data;

    rx8010_rtc_set_bit(rx8010, RX8010_CTRL, RX8010_CTRL_STOP);

    if (rx8010->irq >= 0)
    {
        rt_hw_interrupt_mask(rx8010->irq);
        rt_pic_detach_irq(rx8010->irq, rx8010);

        rt_thread_delete(rx8010->irq_thread);
    }

    rt_device_unregister(&rx8010->parent);

    rt_free(rx8010);

    return RT_EOK;
}

static const struct rt_i2c_device_id rx8010_rtc_ids[] =
{
    { .name = "rx8010" },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id rx8010_rtc_ofw_ids[] =
{
    { .compatible = "epson,rx8010" },
    { /* sentinel */ },
};

static struct rt_i2c_driver rx8010_rtc_driver =
{
    .ids = rx8010_rtc_ids,
    .ofw_ids = rx8010_rtc_ofw_ids,

    .probe = rx8010_rtc_probe,
    .remove = rx8010_rtc_remove,
};
RT_I2C_DRIVER_EXPORT(rx8010_rtc_driver);
