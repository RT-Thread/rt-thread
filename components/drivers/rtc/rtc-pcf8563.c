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

#define DBG_TAG "rtc.pcf8563"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rtc_dm.h"

#define PCF8563_REG_ST1             0x00 /* status */
#define PCF8563_REG_ST2             0x01
#define PCF8563_BIT_AIE             RT_BIT(1)
#define PCF8563_BIT_AF              RT_BIT(3)
#define PCF8563_BITS_ST2_N          (7 << 5)

#define PCF8563_REG_SC              0x02 /* datetime */
#define PCF8563_REG_MN              0x03
#define PCF8563_REG_HR              0x04
#define PCF8563_REG_DM              0x05
#define PCF8563_REG_DW              0x06
#define PCF8563_REG_MO              0x07
#define PCF8563_REG_YR              0x08

#define PCF8563_REG_AMN             0x09 /* alarm */

#define PCF8563_REG_CLKO            0x0d /* clock out */
#define PCF8563_REG_CLKO_FE         0x80 /* clock out enabled */
#define PCF8563_REG_CLKO_F_MASK     0x03 /* frequenc mask */
#define PCF8563_REG_CLKO_F_32768H   0x00
#define PCF8563_REG_CLKO_F_1024HZ   0x01
#define PCF8563_REG_CLKO_F_32HZ     0x02
#define PCF8563_REG_CLKO_F_1HZ      0x03

#define PCF8563_REG_TMRC            0x0e /* timer control */
#define PCF8563_TMRC_ENABLE         RT_BIT(7)
#define PCF8563_TMRC_4096           0
#define PCF8563_TMRC_64             1
#define PCF8563_TMRC_1              2
#define PCF8563_TMRC_1_60           3
#define PCF8563_TMRC_MASK           3

#define PCF8563_REG_TMR             0x0f /* timer */

#define PCF8563_SC_LV               0x80 /* low voltage */
#define PCF8563_MO_C                0x80 /* century */

struct pcf8563_rtc
{
    struct rt_device parent;
    struct rt_clk_node clkout_hw;

    struct rt_clk_cell cell;
    struct rt_clk_cell *cells[1];

    int irq;
    int c_polarity;

    struct rt_i2c_client *client;
    struct rt_thread *irq_thread;

    struct rt_rtc_wkalarm wkalarm;
};

#define raw_to_pcf8563_rtc(raw) rt_container_of(raw, struct pcf8563_rtc, parent)
#define raw_to_pcf8563_clkout(raw) rt_container_of(raw, struct pcf8563_rtc, clkout_hw)

static rt_err_t pcf8563_read_block_data(struct pcf8563_rtc *pcf8563,
        rt_uint8_t reg, rt_uint8_t length, rt_uint8_t *buf)
{
    rt_int32_t res;
    struct rt_i2c_msg msg[2];
    struct rt_i2c_client *client = pcf8563->client;

    msg[0].buf = &reg;
    msg[0].addr = client->client_addr;
    msg[0].len = 1;
    msg[0].flags = RT_I2C_WR;

    msg[1].buf = buf;
    msg[1].addr = client->client_addr;
    msg[1].len = length;
    msg[1].flags = RT_I2C_RD;

    res = rt_i2c_transfer(client->bus, msg, 2);

    return res > 0 ? RT_EOK : res;
}

static rt_err_t pcf8563_write_block_data(struct pcf8563_rtc *pcf8563,
        rt_uint8_t reg, rt_uint8_t length, rt_uint8_t *buf)
{
    rt_int32_t res;
    struct rt_i2c_client *client = pcf8563->client;

    for (int i = 0; i < length; i++)
    {
        rt_uint8_t data[2] = { reg + i, buf[i] };

        res = rt_i2c_master_send(client->bus, client->client_addr,
                RT_I2C_WR, data, sizeof(data));

        if (res != sizeof(data))
        {
            return -RT_EIO;
        }
    }

    return RT_EOK;
}

static rt_err_t pcf8563_set_alarm_mode(struct pcf8563_rtc *pcf8563, rt_bool_t on)
{
    rt_err_t err;
    rt_uint8_t buf;

    err = pcf8563_read_block_data(pcf8563, PCF8563_REG_ST2, 1, &buf);

    if (err)
    {
        return err;
    }

    if (on)
    {
        buf |= PCF8563_BIT_AIE;
    }
    else
    {
        buf &= ~PCF8563_BIT_AIE;
    }

    buf &= ~(PCF8563_BIT_AF | PCF8563_BITS_ST2_N);

    err = pcf8563_write_block_data(pcf8563, PCF8563_REG_ST2, 1, &buf);

    if (err)
    {
        LOG_E("Write %s error", "PCF8563_REG_ST2");

        return -RT_EIO;
    }

    return RT_EOK;
}

static rt_err_t pcf8563_get_alarm_mode(struct pcf8563_rtc *pcf8563,
        rt_uint8_t *en, rt_uint8_t *pen)
{
    rt_err_t err;
    rt_uint8_t buf;

    err = pcf8563_read_block_data(pcf8563, PCF8563_REG_ST2, 1, &buf);

    if (err)
    {
        return err;
    }

    if (en)
    {
        *en = !!(buf & PCF8563_BIT_AIE);
    }

    if (pen)
    {
        *pen = !!(buf & PCF8563_BIT_AF);
    }

    return RT_EOK;
}

static int pcf8563_rtc_read_time(struct pcf8563_rtc *pcf8563, time_t *sec)
{
    rt_err_t err;
    struct tm tm;
    rt_uint8_t buf[9];

    err = pcf8563_read_block_data(pcf8563, PCF8563_REG_ST1, 9, buf);

    if (err)
    {
        return err;
    }

    if (buf[PCF8563_REG_SC] & PCF8563_SC_LV)
    {
        LOG_E("Low voltage detected, date/time is not reliable");

        return -RT_EINVAL;
    }

    tm.tm_sec = rt_bcd2bin(buf[PCF8563_REG_SC] & 0x7f);
    tm.tm_min = rt_bcd2bin(buf[PCF8563_REG_MN] & 0x7f);
    tm.tm_hour = rt_bcd2bin(buf[PCF8563_REG_HR] & 0x3f); /* rtc hr 0-23 */
    tm.tm_mday = rt_bcd2bin(buf[PCF8563_REG_DM] & 0x3f);
    tm.tm_wday = buf[PCF8563_REG_DW] & 0x07;
    tm.tm_mon = rt_bcd2bin(buf[PCF8563_REG_MO] & 0x1f) - 1; /* rtc mn 1-12 */
    tm.tm_year = rt_bcd2bin(buf[PCF8563_REG_YR]) + 100;

    /* detect the polarity heuristically. see note above. */
    pcf8563->c_polarity = (buf[PCF8563_REG_MO] & PCF8563_MO_C) ?
            (tm.tm_year >= 100) : (tm.tm_year < 100);

    *sec = timegm(&tm);

    return RT_EOK;
}

static int pcf8563_rtc_set_time(struct pcf8563_rtc *pcf8563, time_t *sec)
{
    struct tm *tm;
    rt_uint8_t buf[9];

    tm = localtime(sec);

    /* hours, minutes and seconds */
    buf[PCF8563_REG_SC] = rt_bin2bcd(tm->tm_sec);
    buf[PCF8563_REG_MN] = rt_bin2bcd(tm->tm_min);
    buf[PCF8563_REG_HR] = rt_bin2bcd(tm->tm_hour);

    buf[PCF8563_REG_DM] = rt_bin2bcd(tm->tm_mday);

    /* month, 1 - 12 */
    buf[PCF8563_REG_MO] = rt_bin2bcd(tm->tm_mon + 1);

    /* year and century */
    buf[PCF8563_REG_YR] = rt_bin2bcd(tm->tm_year - 100);
    if (pcf8563->c_polarity ? (tm->tm_year >= 100) : (tm->tm_year < 100))
    {
        buf[PCF8563_REG_MO] |= PCF8563_MO_C;
    }

    buf[PCF8563_REG_DW] = tm->tm_wday & 0x07;

    return pcf8563_write_block_data(pcf8563, PCF8563_REG_SC,
            9 - PCF8563_REG_SC, buf + PCF8563_REG_SC);
}

static int pcf8563_rtc_read_alarm(struct pcf8563_rtc *pcf8563,
        struct rt_rtc_wkalarm *alarm)
{
    rt_err_t err;
    rt_uint8_t pending, buf[4];

    err = pcf8563_read_block_data(pcf8563, PCF8563_REG_AMN, 4, buf);

    if (err)
    {
        return err;
    }

    alarm->tm_sec = 0;
    alarm->tm_min = rt_bcd2bin(buf[0] & 0x7f);
    alarm->tm_hour = rt_bcd2bin(buf[1] & 0x3f);
    alarm->tm_mday = rt_bcd2bin(buf[2] & 0x3f);
    /* alarm->tm_wday = rt_bcd2bin(buf[3] & 0x7); */

    return pcf8563_get_alarm_mode(pcf8563, (rt_uint8_t *)&alarm->enable, &pending);
}

static int pcf8563_rtc_set_alarm(struct pcf8563_rtc *pcf8563,
        struct rt_rtc_wkalarm *alarm)
{
    rt_err_t err;
    rt_uint8_t buf[4];
    struct rt_rtc_wkalarm *wkalarm = &pcf8563->wkalarm;

    buf[0] = rt_bin2bcd(alarm->tm_min);
    buf[1] = rt_bin2bcd(alarm->tm_hour);
    buf[2] = rt_bin2bcd(alarm->tm_mday);
    buf[3] = 0 & 0x07; /* alarm->tm_wday */

    err = pcf8563_write_block_data(pcf8563, PCF8563_REG_AMN, 4, buf);

    if (err)
    {
        return err;
    }

    err = pcf8563_set_alarm_mode(pcf8563, alarm->enable);

    if (!err)
    {
        wkalarm->enable = alarm->enable;
        wkalarm->tm_hour = alarm->tm_hour;
        wkalarm->tm_min = alarm->tm_min;
        wkalarm->tm_sec = alarm->tm_sec;
    }

    return err;
}

static rt_err_t pcf8563_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct pcf8563_rtc *pcf8563 = raw_to_pcf8563_rtc(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        err = pcf8563_rtc_read_time(pcf8563, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        err = pcf8563_rtc_set_time(pcf8563, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        err = pcf8563_rtc_read_time(pcf8563, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        err = pcf8563_rtc_set_time(pcf8563, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        err = pcf8563_rtc_read_alarm(pcf8563, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        err = pcf8563_rtc_set_alarm(pcf8563, args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops pcf8563_rtc_ops =
{
    .control = pcf8563_rtc_control,
};
#endif

static void pcf8563_rtc_thread_isr(void *param)
{
    rt_err_t err;
    rt_uint8_t pending;
    struct pcf8563_rtc *pcf8563 = param;

    while (RT_TRUE)
    {
        rt_thread_suspend(pcf8563->irq_thread);
        rt_schedule();

        err = pcf8563_get_alarm_mode(pcf8563, NULL, &pending);

        if (err)
        {
            continue;
        }

        if (pending)
        {
            rt_alarm_update(&pcf8563->parent, 1);

            pcf8563_set_alarm_mode(pcf8563, 1);
        }
    }
}

static void pcf8563_rtc_isr(int irqno, void *param)
{
    struct pcf8563_rtc *pcf8563 = param;

    rt_thread_resume(pcf8563->irq_thread);
}

static const int clkout_rates[] =
{
    32768, 1024, 32, 1,
};

static rt_err_t pcf8563_clkout_control(struct pcf8563_rtc *pcf8563, rt_bool_t enable)
{
    rt_err_t err;
    rt_uint8_t buf;

    if ((err = pcf8563_read_block_data(pcf8563, PCF8563_REG_CLKO, 1, &buf)))
    {
        return err;
    }

    if (enable)
    {
        buf |= PCF8563_REG_CLKO_FE;
    }
    else
    {
        buf &= ~PCF8563_REG_CLKO_FE;
    }

    return pcf8563_write_block_data(pcf8563, PCF8563_REG_CLKO, 1, &buf);
}

static rt_err_t pcf8563_clkout_prepare(struct rt_clk_cell *cell)
{
    struct pcf8563_rtc *pcf8563 = raw_to_pcf8563_clkout(cell->clk_np);

    return pcf8563_clkout_control(pcf8563, RT_TRUE);
}

static void pcf8563_clkout_unprepare(struct rt_clk_cell *cell)
{
    struct pcf8563_rtc *pcf8563 = raw_to_pcf8563_clkout(cell->clk_np);

    pcf8563_clkout_control(pcf8563, RT_FALSE);
}

static rt_bool_t pcf8563_clkout_is_prepared(struct rt_clk_cell *cell)
{
    rt_uint8_t buf;
    struct pcf8563_rtc *pcf8563 = raw_to_pcf8563_clkout(cell->clk_np);

    if (pcf8563_read_block_data(pcf8563, PCF8563_REG_CLKO, 1, &buf))
    {
        return RT_FALSE;
    }

    return !!(buf & PCF8563_REG_CLKO_FE);
}

static rt_ubase_t pcf8563_clkout_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_err_t err;
    rt_uint8_t buf;
    struct pcf8563_rtc *pcf8563 = raw_to_pcf8563_clkout(cell->clk_np);

    err = pcf8563_read_block_data(pcf8563, PCF8563_REG_CLKO, 1, &buf);

    if (err)
    {
        return err;
    }

    buf &= PCF8563_REG_CLKO_F_MASK;

    return clkout_rates[buf];
}

static rt_base_t pcf8563_clkout_round_rate(struct rt_clk_cell *cell, rt_ubase_t drate,
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

static rt_err_t pcf8563_clkout_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate,
        rt_ubase_t parent_rate)
{
    rt_err_t err;
    rt_uint8_t buf;
    struct pcf8563_rtc *pcf8563 = raw_to_pcf8563_clkout(cell->clk_np);

    err = pcf8563_read_block_data(pcf8563, PCF8563_REG_CLKO, 1, &buf);

    if (err)
    {
        return err;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(clkout_rates); ++i)
    {
        if (clkout_rates[i] == rate)
        {
            buf &= ~PCF8563_REG_CLKO_F_MASK;
            buf |= i;

            return pcf8563_write_block_data(pcf8563, PCF8563_REG_CLKO, 1, &buf);
        }
    }


    return -RT_EINVAL;
}

static const struct rt_clk_ops pcf8563_clkout_ops =
{
    .prepare = pcf8563_clkout_prepare,
    .unprepare = pcf8563_clkout_unprepare,
    .is_prepared = pcf8563_clkout_is_prepared,
    .recalc_rate = pcf8563_clkout_recalc_rate,
    .round_rate = pcf8563_clkout_round_rate,
    .set_rate = pcf8563_clkout_set_rate,
};

static void pcf8563_clkout_register_clk(struct pcf8563_rtc *pcf8563, struct rt_device *dev)
{
    rt_uint8_t buf = 0;

    /* Disable the clkout output */
    if (pcf8563_write_block_data(pcf8563, PCF8563_REG_CLKO, 1, &buf))
    {
        return;
    }

    pcf8563->cells[0] = &pcf8563->cell;
    pcf8563->cell.name = "pcf8563-clkout";
    pcf8563->cell.ops = &pcf8563_clkout_ops;
    rt_dm_dev_prop_read_string(dev, "clock-output-names", &pcf8563->cell.name);

    pcf8563->clkout_hw.dev = dev;
    pcf8563->clkout_hw.cells_nr = 1;
    pcf8563->clkout_hw.cells = pcf8563->cells;

    if (rt_clk_register(&pcf8563->clkout_hw))
    {
        return;
    }
}

static rt_err_t pcf8563_rtc_probe(struct rt_i2c_client *client)
{
    rt_err_t err;
    rt_uint8_t buf;
    const char *dev_name;
    struct rt_device *dev = &client->parent;
    struct pcf8563_rtc *pcf8563 = rt_calloc(1, sizeof(*pcf8563));

    if (!pcf8563)
    {
        return -RT_ENOMEM;
    }

    pcf8563->irq = rt_dm_dev_get_irq(dev, 0);
    pcf8563->client = client;

    /* Set timer to lowest frequency to save power (ref Haoyu datasheet) */
    buf = PCF8563_TMRC_1_60;

    if ((err = pcf8563_write_block_data(pcf8563, PCF8563_REG_TMRC, 1, &buf)))
    {
        LOG_E("Write %s error", "PCF8563_REG_TMRC");
        goto _fail;
    }

    /* Clear flags and disable interrupts */
    buf = 0;

    if ((err = pcf8563_write_block_data(pcf8563, PCF8563_REG_ST2, 1, &buf)))
    {
        LOG_E("Write %s error", "PCF8563_REG_ST2");
        goto _fail;
    }

    if (pcf8563->irq >= 0)
    {
        pcf8563->irq_thread = rt_thread_create("rtc-pcf8563", &pcf8563_rtc_thread_isr,
                pcf8563, DM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 2, 10);

        if (!pcf8563->irq_thread)
        {
            err = -RT_ERROR;
            LOG_E("Create RTC IRQ thread fail");
            goto _fail;
        }

        rt_thread_startup(pcf8563->irq_thread);

        rt_hw_interrupt_install(pcf8563->irq, pcf8563_rtc_isr, pcf8563, "rtc-pcf8563");
        rt_hw_interrupt_umask(pcf8563->irq);
    }

    dev->user_data = pcf8563;

    pcf8563->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    pcf8563->parent.ops = &pcf8563_rtc_ops;
#else
    pcf8563->parent.control = pcf8563_rtc_control;
#endif

    rtc_dev_set_name(&pcf8563->parent);
    dev_name = rt_dm_dev_get_name(&pcf8563->parent);
    rt_device_register(&pcf8563->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    pcf8563_clkout_register_clk(pcf8563, dev);

    return RT_EOK;

_fail:
    if (pcf8563->irq_thread)
    {
        rt_thread_delete(pcf8563->irq_thread);
    }
    rt_free(pcf8563);

    return err;
}

static rt_err_t pcf8563_rtc_remove(struct rt_i2c_client *client)
{
    struct pcf8563_rtc *pcf8563 = client->parent.user_data;

    rt_dm_dev_unbind_fwdata(&client->parent, RT_NULL);

    if (pcf8563->irq >= 0)
    {
        if (pcf8563->wkalarm.enable)
        {
            pcf8563_set_alarm_mode(pcf8563, RT_FALSE);
        }

        rt_hw_interrupt_mask(pcf8563->irq);
        rt_pic_detach_irq(pcf8563->irq, pcf8563);

        rt_thread_delete(pcf8563->irq_thread);
    }

    if (pcf8563->cells[0])
    {
        rt_clk_unregister(&pcf8563->clkout_hw);
    }

    rt_device_unregister(&pcf8563->parent);

    rt_free(pcf8563);

    return RT_EOK;
}

static const struct rt_i2c_device_id pcf8563_rtc_ids[] =
{
    { .name = "pcf8563" },
    { .name = "rtc8564" },
    { .name = "pca8565" },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id pcf8563_rtc_ofw_ids[] =
{
    { .compatible = "nxp,pcf8563" },
    { .compatible = "epson,rtc8564" },
    { .compatible = "microcrystal,rv8564" },
    { .compatible = "nxp,pca8565" },
    { /* sentinel */ },
};

static struct rt_i2c_driver pcf8563_rtc_driver =
{
    .ids = pcf8563_rtc_ids,
    .ofw_ids = pcf8563_rtc_ofw_ids,

    .probe = pcf8563_rtc_probe,
    .remove = pcf8563_rtc_remove,
};
RT_I2C_DRIVER_EXPORT(pcf8563_rtc_driver);
