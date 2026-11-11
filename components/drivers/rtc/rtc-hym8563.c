/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#include "rtc_dm.h"

#define DBG_TAG "rtc.hym8563"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define HYM8563_CTL1            0x00
#define HYM8563_CTL1_TEST       RT_BIT(7)
#define HYM8563_CTL1_STOP       RT_BIT(5)
#define HYM8563_CTL1_TESTC      RT_BIT(3)

#define HYM8563_CTL2            0x01
#define HYM8563_CTL2_TI_TP      RT_BIT(4)
#define HYM8563_CTL2_AF         RT_BIT(3)
#define HYM8563_CTL2_TF         RT_BIT(2)
#define HYM8563_CTL2_AIE        RT_BIT(1)
#define HYM8563_CTL2_TIE        RT_BIT(0)

#define HYM8563_SEC             0x02
#define HYM8563_SEC_VL          RT_BIT(7)
#define HYM8563_SEC_MASK        0x7f

#define HYM8563_MIN             0x03
#define HYM8563_MIN_MASK        0x7f

#define HYM8563_HOUR            0x04
#define HYM8563_HOUR_MASK       0x3f

#define HYM8563_DAY             0x05
#define HYM8563_DAY_MASK        0x3f

#define HYM8563_WEEKDAY         0x06
#define HYM8563_WEEKDAY_MASK    0x07

#define HYM8563_MONTH           0x07
#define HYM8563_MONTH_CENTURY   RT_BIT(7)
#define HYM8563_MONTH_MASK      0x1f

#define HYM8563_YEAR            0x08

#define HYM8563_ALM_MIN         0x09
#define HYM8563_ALM_HOUR        0x0a
#define HYM8563_ALM_DAY         0x0b
#define HYM8563_ALM_WEEK        0x0c

/* Each alarm check can be disabled by setting this bit in the register */
#define HYM8563_ALM_BIT_DISABLE RT_BIT(7)

#define HYM8563_CLKOUT          0x0d
#define HYM8563_CLKOUT_ENABLE   RT_BIT(7)
#define HYM8563_CLKOUT_32768    0
#define HYM8563_CLKOUT_1024     1
#define HYM8563_CLKOUT_32       2
#define HYM8563_CLKOUT_1        3
#define HYM8563_CLKOUT_MASK     3

#define HYM8563_TMR_CTL         0x0e
#define HYM8563_TMR_CTL_ENABLE  RT_BIT(7)
#define HYM8563_TMR_CTL_4096    0
#define HYM8563_TMR_CTL_64      1
#define HYM8563_TMR_CTL_1       2
#define HYM8563_TMR_CTL_1_60    3
#define HYM8563_TMR_CTL_MASK    3

#define HYM8563_TMR_CNT         0x0f

struct hym8563_rtc
{
    struct rt_device parent;
    struct rt_clk_node clkout_hw;

    struct rt_clk_cell cell;
    struct rt_clk_cell *cells[1];

    int irq;
    struct rt_i2c_client *client;
    struct rt_thread *irq_thread;

    struct rt_rtc_wkalarm wkalarm;
};

#define raw_to_hym8563_rtc(raw) rt_container_of(raw, struct hym8563_rtc, parent)
#define raw_to_hym8563_clkout(raw) rt_container_of(raw, struct hym8563_rtc, clkout_hw)

static rt_int32_t i2c_smbus_read_byte_data(struct rt_i2c_client *client,
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

static rt_int32_t i2c_smbus_write_byte_data(struct rt_i2c_client *client,
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

/* Returns the number of read bytes */
static rt_int32_t i2c_smbus_read_i2c_block_data(struct rt_i2c_client *client,
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

static rt_int32_t i2c_smbus_write_i2c_block_data(struct rt_i2c_client *client,
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

static void hym8563_rtc_read_time(struct hym8563_rtc *hym8563, time_t *sec)
{
    struct tm tm;
    rt_uint8_t buf[7];

    if (i2c_smbus_read_i2c_block_data(hym8563->client, HYM8563_SEC, 7, buf) < 0)
    {
        return;
    }

    if (buf[0] & HYM8563_SEC_VL)
    {
        LOG_D("no valid clock/calendar values available");
    }

    tm.tm_sec = rt_bcd2bin(buf[0] & HYM8563_SEC_MASK);
    tm.tm_min = rt_bcd2bin(buf[1] & HYM8563_MIN_MASK);
    tm.tm_hour = rt_bcd2bin(buf[2] & HYM8563_HOUR_MASK);
    tm.tm_mday = rt_bcd2bin(buf[3] & HYM8563_DAY_MASK);
    tm.tm_wday = rt_bcd2bin(buf[4] & HYM8563_WEEKDAY_MASK); /* 0 = Sun */
    tm.tm_mon = rt_bcd2bin(buf[5] & HYM8563_MONTH_MASK) - 1; /* 0 = Jan */
    tm.tm_year = rt_bcd2bin(buf[6]) + 100;

    *sec = timegm(&tm);
}

static void hym8563_rtc_set_time(struct hym8563_rtc *hym8563, time_t *sec)
{
    struct tm *tm;
    rt_uint8_t buf[7];
    struct rt_i2c_client *client = hym8563->client;

    tm = localtime(sec);

    /* Years >= 2100 are to far in the future, 19XX is to early */
    if (tm->tm_year < 100 || tm->tm_year >= 200)
    {
        return;
    }

    buf[0] = rt_bin2bcd(tm->tm_sec);
    buf[1] = rt_bin2bcd(tm->tm_min);
    buf[2] = rt_bin2bcd(tm->tm_hour);
    buf[3] = rt_bin2bcd(tm->tm_mday);
    buf[4] = rt_bin2bcd(tm->tm_wday);
    buf[5] = rt_bin2bcd(tm->tm_mon + 1);

    /*
     * While the HYM8563 has a century flag in the month register,
     * it does not seem to carry it over a subsequent write/read.
     * So we'll limit ourself to 100 years, starting at 2000 for now.
     */
    buf[6] = rt_bin2bcd(tm->tm_year - 100);

    /* CTL1 only contains TEST-mode bits apart from stop, so no need to read the value first */
    if (i2c_smbus_write_byte_data(client, HYM8563_CTL1, HYM8563_CTL1_STOP) < 0)
    {
        return;
    }

    if (i2c_smbus_write_i2c_block_data(client, HYM8563_SEC, 7, buf) < 0)
    {
        return;
    }

    if (i2c_smbus_write_byte_data(client, HYM8563_CTL1, 0) < 0)
    {
        return;
    }
}

static int hym8563_rtc_alarm_irq_enable(struct hym8563_rtc *hym8563, rt_bool_t enabled)
{
    int data;
    struct rt_i2c_client *client = hym8563->client;

    data = i2c_smbus_read_byte_data(client, HYM8563_CTL2);

    if (data < 0)
    {
        return data;
    }

    if (enabled)
    {
        data |= HYM8563_CTL2_AIE;
    }
    else
    {
        data &= ~HYM8563_CTL2_AIE;
    }

    return i2c_smbus_write_byte_data(client, HYM8563_CTL2, data);
};

static int hym8563_rtc_read_alarm(struct hym8563_rtc *hym8563,
        struct rt_rtc_wkalarm *alarm)
{
    int res;
    rt_uint8_t buf[4];
    struct rt_i2c_client *client = hym8563->client;

    res = i2c_smbus_read_i2c_block_data(client, HYM8563_ALM_MIN, 4, buf);

    if (res < 0)
    {
        return res;
    }

    /* The alarm only has a minute accuracy */
    alarm->tm_sec = 0;
    alarm->tm_min = (buf[0] & HYM8563_ALM_BIT_DISABLE) ?
            -1 : rt_bcd2bin(buf[0] & HYM8563_MIN_MASK);
    alarm->tm_hour = (buf[1] & HYM8563_ALM_BIT_DISABLE) ?
            -1 : rt_bcd2bin(buf[1] & HYM8563_HOUR_MASK);
    alarm->tm_mday = (buf[2] & HYM8563_ALM_BIT_DISABLE) ?
            -1 : rt_bcd2bin(buf[2] & HYM8563_DAY_MASK);
    /*
     * alarm->tm_wday = (buf[3] & HYM8563_ALM_BIT_DISABLE) ?
     *         -1 : rt_bcd2bin(buf[3] & HYM8563_WEEKDAY_MASK);
     */

    res = i2c_smbus_read_byte_data(client, HYM8563_CTL2);

    if (res < 0)
    {
        return res;
    }

    alarm->enable = res & HYM8563_CTL2_AIE ? RT_TRUE : RT_FALSE;

    return 0;
}

static int hym8563_rtc_set_alarm(struct hym8563_rtc *hym8563,
        struct rt_rtc_wkalarm *alarm)
{
    int res;
    rt_uint8_t buf[4];
    struct rt_i2c_client *client = hym8563->client;
    struct rt_rtc_wkalarm *wkalarm = &hym8563->wkalarm;

    res = i2c_smbus_read_byte_data(client, HYM8563_CTL2);

    if (res < 0)
    {
        return res;
    }

    res &= ~HYM8563_CTL2_AIE;

    res = i2c_smbus_write_byte_data(client, HYM8563_CTL2, res);

    if (res < 0)
    {
        return res;
    }

    buf[0] = (alarm->tm_min < 60 && alarm->tm_min >= 0) ?
            rt_bin2bcd(alarm->tm_min) : HYM8563_ALM_BIT_DISABLE;
    buf[1] = (alarm->tm_hour < 24 && alarm->tm_hour >= 0) ?
            rt_bin2bcd(alarm->tm_hour) : HYM8563_ALM_BIT_DISABLE;
    buf[2] = (alarm->tm_mday <= 31 && alarm->tm_mday >= 1) ?
            rt_bin2bcd(alarm->tm_mday) : HYM8563_ALM_BIT_DISABLE;
    /*
     * buf[3] = (alarm->tm_wday < 7 && alarm->tm_wday >= 0) ?
     *         rt_bin2bcd(alarm->tm_wday) : HYM8563_ALM_BIT_DISABLE;
     */

    res = i2c_smbus_write_i2c_block_data(client, HYM8563_ALM_MIN, 4, buf);

    if (res < 0)
    {
        return res;
    }

    res = hym8563_rtc_alarm_irq_enable(hym8563, alarm->enable);

    if (!(res < 0))
    {
        wkalarm->enable = alarm->enable;
        wkalarm->tm_hour = alarm->tm_hour;
        wkalarm->tm_min = alarm->tm_min;
        wkalarm->tm_sec = alarm->tm_sec;
    }

    return res;
}

static rt_err_t hym8563_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct hym8563_rtc *hym8563 = raw_to_hym8563_rtc(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        hym8563_rtc_read_time(hym8563, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        hym8563_rtc_set_time(hym8563, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        hym8563_rtc_read_time(hym8563, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        hym8563_rtc_set_time(hym8563, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        err = hym8563_rtc_read_alarm(hym8563, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        err = hym8563_rtc_set_alarm(hym8563, args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops hym8563_rtc_ops =
{
    .control = hym8563_rtc_control,
};
#endif

static void hym8563_rtc_thread_isr(void *param)
{
    int data, res;
    struct hym8563_rtc *hym8563 = param;
    struct rt_i2c_client *client = hym8563->client;

    while (RT_TRUE)
    {
        rt_thread_suspend(hym8563->irq_thread);
        rt_schedule();

        data = i2c_smbus_read_byte_data(client, HYM8563_CTL2);

        if (data < 0)
        {
            LOG_E("IRQ: error %sing i2c data %d", "read", data);

            return;
        }

        data &= ~HYM8563_CTL2_AF;

        res = i2c_smbus_write_byte_data(client, HYM8563_CTL2, data);

        if (res < 0)
        {
            LOG_E("IRQ: error %sing i2c data %d", "writ", res);

            return;
        }

        rt_alarm_update(&hym8563->parent, 1);
    }
}

static void hym8563_rtc_isr(int irqno, void *param)
{
    struct hym8563_rtc *hym8563 = param;

    rt_thread_resume(hym8563->irq_thread);
}

static const int clkout_rates[] =
{
    32768, 1024, 32, 1,
};

static int hym8563_clkout_control(struct hym8563_rtc *hym8563, rt_bool_t enable)
{
    int res = i2c_smbus_read_byte_data(hym8563->client, HYM8563_CLKOUT);

    if (res < 0)
    {
        return res;
    }

    if (enable)
    {
        res |= HYM8563_CLKOUT_ENABLE;
    }
    else
    {
        res &= ~HYM8563_CLKOUT_ENABLE;
    }

    return i2c_smbus_write_byte_data(hym8563->client, HYM8563_CLKOUT, res);
}

static rt_err_t hym8563_clkout_prepare(struct rt_clk_cell *cell)
{
    struct hym8563_rtc *hym8563 = raw_to_hym8563_clkout(cell->clk_np);

    return hym8563_clkout_control(hym8563, RT_TRUE);
}

static void hym8563_clkout_unprepare(struct rt_clk_cell *cell)
{
    struct hym8563_rtc *hym8563 = raw_to_hym8563_clkout(cell->clk_np);

    hym8563_clkout_control(hym8563, RT_FALSE);
}

static rt_bool_t hym8563_clkout_is_prepared(struct rt_clk_cell *cell)
{
    int res;
    struct hym8563_rtc *hym8563 = raw_to_hym8563_clkout(cell->clk_np);

    res = i2c_smbus_read_byte_data(hym8563->client, HYM8563_CLKOUT);

    if (res < 0)
    {
        return RT_FALSE;
    }

    return !!(res & HYM8563_CLKOUT_ENABLE);
}

static rt_ubase_t hym8563_clkout_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    int res;
    struct hym8563_rtc *hym8563 = raw_to_hym8563_clkout(cell->clk_np);

    res = i2c_smbus_read_byte_data(hym8563->client, HYM8563_CLKOUT);

    if (res < 0)
    {
        return res;
    }

    res &= HYM8563_CLKOUT_MASK;

    return clkout_rates[res];
}

static rt_base_t hym8563_clkout_round_rate(struct rt_clk_cell *cell, rt_ubase_t drate,
        rt_ubase_t *prate)
{
    for (int i = 0; i < RT_ARRAY_SIZE(clkout_rates); ++i)
    {
        if (clkout_rates[i] <= drate)
        {
            return clkout_rates[i];
        }
    }

    return 0;
}

static rt_err_t hym8563_clkout_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate,
        rt_ubase_t parent_rate)
{
    int res;
    struct hym8563_rtc *hym8563 = raw_to_hym8563_clkout(cell->clk_np);

    res = i2c_smbus_read_byte_data(hym8563->client, HYM8563_CLKOUT);

    if (res < 0)
    {
        return res;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(clkout_rates); ++i)
    {
        if (clkout_rates[i] == rate)
        {
            res &= ~HYM8563_CLKOUT_MASK;
            res |= i;

            res = i2c_smbus_write_byte_data(hym8563->client, HYM8563_CLKOUT, res);

            return res >= 0 ? RT_EOK : res;
        }
    }

    return -RT_EINVAL;
}

static const struct rt_clk_ops hym8563_clkout_ops =
{
    .prepare = hym8563_clkout_prepare,
    .unprepare = hym8563_clkout_unprepare,
    .is_prepared = hym8563_clkout_is_prepared,
    .recalc_rate = hym8563_clkout_recalc_rate,
    .round_rate = hym8563_clkout_round_rate,
    .set_rate = hym8563_clkout_set_rate,
};

static void hym8563_clkout_register_clk(struct hym8563_rtc *hym8563, struct rt_device *dev)
{
    if (i2c_smbus_write_byte_data(hym8563->client, HYM8563_CLKOUT, 0) < 0)
    {
        return;
    }

    hym8563->cells[0] = &hym8563->cell;
    hym8563->cell.name = "hym8563-clkout";
    hym8563->cell.ops = &hym8563_clkout_ops;
    rt_dm_dev_prop_read_string(dev, "clock-output-names", &hym8563->cell.name);

    hym8563->clkout_hw.dev = dev;
    hym8563->clkout_hw.cells_nr = 1;
    hym8563->clkout_hw.cells = hym8563->cells;

    if (rt_clk_register(&hym8563->clkout_hw))
    {
        return;
    }
}

static rt_err_t hym8563_init_device(struct rt_i2c_client *client)
{
    int res;

    /* Clear stop flag if present */
    res = i2c_smbus_write_byte_data(client, HYM8563_CTL1, 0);
    if (res < 0)
    {
        return res;
    }

    res = i2c_smbus_read_byte_data(client, HYM8563_CTL2);
    if (res < 0)
    {
        return res;
    }

    /* Disable alarm and timer interrupts */
    res &= ~HYM8563_CTL2_AIE;
    res &= ~HYM8563_CTL2_TIE;

    /* Clear any pending alarm and timer flags */
    if (res & HYM8563_CTL2_AF)
    {
        res &= ~HYM8563_CTL2_AF;
    }

    if (res & HYM8563_CTL2_TF)
    {
        res &= ~HYM8563_CTL2_TF;
    }

    res &= ~HYM8563_CTL2_TI_TP;

    return i2c_smbus_write_byte_data(client, HYM8563_CTL2, res);
}

static rt_err_t hym8563_rtc_probe(struct rt_i2c_client *client)
{
    rt_err_t err;
    rt_int32_t res;
    const char *dev_name;
    struct rt_device *dev = &client->parent;
    struct hym8563_rtc *hym8563 = rt_calloc(1, sizeof(*hym8563));

    if (!hym8563)
    {
        return -RT_ENOMEM;
    }

    if ((res = hym8563_init_device(client)) < 0)
    {
        err = res;

        goto _fail;
    }

    hym8563->irq = rt_dm_dev_get_irq(dev, 0);
    hym8563->client = client;

    /* check state of calendar information */
    if ((res = i2c_smbus_read_byte_data(client, HYM8563_SEC)) < 0)
    {
        err = res;

        goto _fail;
    }

    LOG_D("rtc information is %s", (res & HYM8563_SEC_VL) ? "invalid" : "valid");

    if (hym8563->irq >= 0)
    {
        hym8563->irq_thread = rt_thread_create("rtc-hym8563", &hym8563_rtc_thread_isr,
                hym8563, DM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 2, 10);

        if (!hym8563->irq_thread)
        {
            err = -RT_ERROR;
            LOG_E("Create RTC IRQ thread fail");
            goto _fail;
        }

        rt_thread_startup(hym8563->irq_thread);

        rt_hw_interrupt_install(hym8563->irq, hym8563_rtc_isr, hym8563, "rtc-hym8563");
        rt_hw_interrupt_umask(hym8563->irq);
    }

    dev->user_data = hym8563;

    hym8563->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    hym8563->parent.ops = &hym8563_rtc_ops;
#else
    hym8563->parent.control = hym8563_rtc_control;
#endif

    rtc_dev_set_name(&hym8563->parent);
    dev_name = rt_dm_dev_get_name(&hym8563->parent);
    rt_device_register(&hym8563->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    hym8563_clkout_register_clk(hym8563, dev);

    return RT_EOK;

_fail:
    if (hym8563->irq_thread)
    {
        rt_thread_delete(hym8563->irq_thread);
    }
    rt_free(hym8563);

    return err;
}

static rt_err_t hym8563_rtc_remove(struct rt_i2c_client *client)
{
    struct hym8563_rtc *hym8563 = client->parent.user_data;

    rt_dm_dev_unbind_fwdata(&client->parent, RT_NULL);

    if (hym8563->irq >= 0)
    {
        if (hym8563->wkalarm.enable)
        {
            hym8563_rtc_alarm_irq_enable(hym8563, RT_FALSE);
        }

        rt_hw_interrupt_mask(hym8563->irq);
        rt_pic_detach_irq(hym8563->irq, hym8563);

        rt_thread_delete(hym8563->irq_thread);
    }

    if (hym8563->cells[0])
    {
        rt_clk_unregister(&hym8563->clkout_hw);
    }

    rt_device_unregister(&hym8563->parent);

    rt_free(hym8563);

    return RT_EOK;
}

static const struct rt_i2c_device_id hym8563_rtc_ids[] =
{
    { .name = "hym8563" },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id hym8563_rtc_ofw_ids[] =
{
    { .compatible = "haoyu,hym8563" },
    { /* sentinel */ },
};

static struct rt_i2c_driver hym8563_rtc_driver =
{
    .ids = hym8563_rtc_ids,
    .ofw_ids = hym8563_rtc_ofw_ids,

    .probe = hym8563_rtc_probe,
    .remove = hym8563_rtc_remove,
};
RT_I2C_DRIVER_EXPORT(hym8563_rtc_driver);
