/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/byteorder.h>

#define DBG_TAG "input.ts.ads7846"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/*
 * The ADS7846 has touchscreen and other sensors.
 * Earlier ads784x chips are somewhat compatible.
 */
#define ADS_START        (1 << 7)
#define ADS_A2A1A0_d_y   (1 << 4)    /* Differential */
#define ADS_A2A1A0_d_z1  (3 << 4)    /* Differential */
#define ADS_A2A1A0_d_z2  (4 << 4)    /* Differential */
#define ADS_A2A1A0_d_x   (5 << 4)    /* Differential */
#define ADS_A2A1A0_temp0 (0 << 4)    /* Non-differential */
#define ADS_A2A1A0_vbatt (2 << 4)    /* Non-differential */
#define ADS_A2A1A0_vaux  (6 << 4)    /* Non-differential */
#define ADS_A2A1A0_temp1 (7 << 4)    /* Non-differential */
#define ADS_8_BIT        (1 << 3)
#define ADS_12_BIT       (0 << 3)
#define ADS_SER          (1 << 2)    /* Non-differential */
#define ADS_DFR          (0 << 2)    /* Differential */
#define ADS_PD10_PDOWN   (0 << 0)    /* Low power mode + penirq */
#define ADS_PD10_ADC_ON  (1 << 0)    /* ADC on */
#define ADS_PD10_REF_ON  (2 << 0)    /* vREF on + penirq */
#define ADS_PD10_ALL_ON  (3 << 0)    /* ADC + vREF on */

#define MAX_12BIT ((1 << 12) - 1)

/* Leave ADC powered up (disables penirq) between differential samples */
#define READ_12BIT_DFR(x, adc, vref) (ADS_START | ADS_A2A1A0_d_##x | ADS_12_BIT | ADS_DFR | \
                                      (adc ? ADS_PD10_ADC_ON : 0) | (vref ? ADS_PD10_REF_ON : 0))

#define READ_Y(vref)  (READ_12BIT_DFR(y, 1, vref))
#define READ_Z1(vref) (READ_12BIT_DFR(z1, 1, vref))
#define READ_Z2(vref) (READ_12BIT_DFR(z2, 1, vref))
#define READ_X(vref)  (READ_12BIT_DFR(x, 1, vref))
#define PWRDOWN       (READ_12BIT_DFR(y, 0, 0))  /* LAST */

/*
 * Single-ended samples need to first power up reference voltage;
 * We leave both ADC and VREF powered
 */
#define READ_12BIT_SER(x) (ADS_START | ADS_A2A1A0_##x | ADS_12_BIT | ADS_SER)

#define REF_ON  (READ_12BIT_DFR(x, 1, 1))
#define REF_OFF (READ_12BIT_DFR(y, 0, 0))

#define TS_POLL_DELAY  1   /* ms delay before the first sample */
#define TS_POLL_PERIOD 5   /* ms delay between samples */

/* This driver doesn't aim at the peak continuous sample rate */
#define SAMPLE_BITS (8 /*cmd*/ + 16 /*sample*/ + 2 /* before, after */)

#define NSEC_PER_SEC  1000000000L
#define NSEC_PER_USEC 1000L

/*
 * Order commands in the most optimal way to reduce Vref switching and
 * settling time:
 * Measure:  X; Vref: X+, X-; IN: Y+
 * Measure:  Y; Vref: Y+, Y-; IN: X+
 * Measure: Z1; Vref: Y+, X-; IN: X+
 * Measure: Z2; Vref: Y+, X-; IN: Y-
 */
enum ads7846_cmds
{
    ADS7846_X,
    ADS7846_Y,
    ADS7846_Z1,
    ADS7846_Z2,
    ADS7846_PWDOWN,
};

rt_packed(struct ads7846_buf {
    rt_uint8_t cmd;
    rt_be16_t data;
});

struct ads7846_ser_req
{
    rt_uint8_t ref_on;
    rt_uint8_t command;
    rt_uint8_t ref_off;
    rt_uint16_t scratch;
    struct rt_spi_message msg[6];

    rt_be16_t sample;
};

struct ads7845_ser_req
{
    rt_uint8_t command[3];
    struct rt_spi_message msg[1];
    rt_uint8_t sample[3];
};

struct ads7846_buf_layout
{
    rt_uint32_t offset;
    rt_uint32_t count;
    rt_uint32_t skip;
};

struct ads7846_packet
{
    rt_uint32_t count;
    rt_uint32_t count_skip;
    rt_uint32_t cmds;
    rt_uint32_t last_cmd_idx;
    struct ads7846_buf_layout layout[5];
    struct ads7846_buf *rx;
    struct ads7846_buf *tx;

    struct ads7846_buf pwrdown_cmd;

    rt_bool_t ignore;
    rt_uint16_t x, y, z1, z2;
};

struct ads7846_platform_data
{
    rt_uint16_t model;              /* 7843, 7845, 7846, 7873. */
    rt_uint16_t vref_delay_usecs;   /* 0 for external vref; etc */
    rt_uint16_t vref_mv;            /* external vref value, milliVolts ads7846: if 0, use internal vref */
    rt_bool_t keep_vref_on;         /* set to keep vref on for differential measurements as well */
    rt_bool_t swap_xy;              /* swap x and y axes */

    /*
     * Settling time of the analog signals; a function of Vcc and the
     * capacitance on the X/Y drivers.  If set to non-zero, two samples
     * are taken with settle_delay us apart, and the second one is used.
     * ~150 uSec with 0.01uF caps.
     */
    rt_uint16_t settle_delay_usecs;

    /*
     * If set to non-zero, after samples are taken this delay is applied
     * and penirq is rechecked, to help avoid false events.  This value
     * is affected by the material used to build the touch layer.
     */
    rt_uint16_t penirq_recheck_delay_usecs;

    rt_uint16_t x_plate_ohms;
    rt_uint16_t y_plate_ohms;

    rt_uint16_t x_min, x_max;
    rt_uint16_t y_min, y_max;
    rt_uint16_t pressure_min, pressure_max;

    rt_uint16_t debounce_max;       /* max number of additional readings per sample */
    rt_uint16_t debounce_tol;       /* tolerance used for filtering */
    rt_uint16_t debounce_rep;       /* additional consecutive good readings required after the first two */

    /* platform specific debounce time for the gpio_pendown */
    rt_uint32_t gpio_pendown_debounce;
};

enum ads7846_filter
{
    ADS7846_FILTER_OK,
    ADS7846_FILTER_REPEAT,
    ADS7846_FILTER_IGNORE,
};

struct ads7846
{
    struct rt_input_device parent;

    int irq;
    rt_ubase_t gpio_pendown;
    rt_uint8_t gpio_pendown_active;

    int read_cnt;
    int read_rep;
    int last_read;

    struct rt_spi_message msg[5];

    rt_bool_t pendown;
    rt_bool_t stopped;    /* P: lock */
    rt_bool_t suspended;  /* P: lock */

    struct rt_spi_device *spi;
    struct rt_thread *ts_task;
    struct rt_regulator *supply;

    struct ads7846_packet packet;
    struct ads7846_platform_data pdata;

    rt_bool_t use_internal;

    void *filter_data;
    int (*filter)(void *data, int data_idx, int *val);
};

/*
 * Prefix of struct input_touch_properties in input_touch.c — must stay
 * in sync (ads7846 is single-slot; only used to apply ti,swap-xy).
 */
struct ads7846_input_touch_prop
{
    rt_uint32_t max_x;
    rt_uint32_t max_y;
    rt_bool_t invert_x;
    rt_bool_t invert_y;
    rt_bool_t swap_x_y;
    rt_uint16_t track_id;
    rt_uint32_t num_slots;
    void *touch_dev;
};

static void ads7846_apply_legacy_swap_xy(struct rt_input_device *idev,
                                         rt_bool_t vendor_swap_xy)
{
    struct ads7846_input_touch_prop *prop;
    rt_uint32_t axis_x;
    rt_uint32_t axis_y;
    struct rt_input_absinfo tmp;

    if (!vendor_swap_xy || !idev || !idev->touch)
    {
        return;
    }

    prop = idev->touch;
    if (prop->swap_x_y)
    {
        return;
    }

    axis_x = prop->num_slots ? ABS_MT_POSITION_X : ABS_X;
    axis_y = prop->num_slots ? ABS_MT_POSITION_Y : ABS_Y;

    rt_memcpy(&tmp, &idev->absinfo[axis_x], sizeof(tmp));
    rt_memcpy(&idev->absinfo[axis_x], &idev->absinfo[axis_y], sizeof(tmp));
    rt_memcpy(&idev->absinfo[axis_y], &tmp, sizeof(tmp));

    prop->max_x = idev->absinfo[axis_x].maximum;
    prop->max_y = idev->absinfo[axis_y].maximum;
    prop->swap_x_y = RT_TRUE;

    if (prop->touch_dev)
    {
        struct rt_touch_device *tdev = prop->touch_dev;

        tdev->info.range_x = prop->max_x;
        tdev->info.range_y = prop->max_y;
    }
}

rt_inline rt_uint16_t get_unaligned_be16(const void *p)
{
    const rt_packed(struct { rt_be16_t v; }) *ptr = (typeof(ptr))(p);

    return rt_be16_to_cpu(ptr->v);
}

static void ads7846_report_pen_up(struct ads7846 *ts);

static rt_bool_t ads7846_pendown_active(struct ads7846 *ts)
{
    return ts->gpio_pendown == PIN_NONE ||
           rt_pin_read(ts->gpio_pendown) == ts->gpio_pendown_active;
}

static void ads7846_stop(struct ads7846 *ts)
{
    if (!ts->suspended)
    {
        ts->stopped = RT_TRUE;
        rt_hw_wmb();
    }
}

static void ads7846_restart(struct ads7846 *ts)
{
    if (!ts->suspended)
    {
        /* Check if pen was released since last stop */
        if (ts->pendown && !ads7846_pendown_active(ts))
        {
            ads7846_report_pen_up(ts);
        }

        ts->stopped = RT_FALSE;
        rt_hw_wmb();
    }
}

rt_inline void ads7846_disable(struct ads7846 *ts)
{
    ads7846_stop(ts);
    if (ts->supply)
    {
        rt_regulator_disable(ts->supply);
    }
}

rt_inline void ads7846_enable(struct ads7846 *ts)
{
    if (ts->supply && rt_regulator_enable(ts->supply))
    {
        LOG_E("%s: Failed to enable supply", rt_dm_dev_get_name(&ts->spi->parent));
    }

    ads7846_restart(ts);
}

static int ads7846_debounce_filter(void *ads, int data_idx, int *val)
{
    struct ads7846 *ts = ads;

    if (!ts->read_cnt || (rt_abs(ts->last_read - *val) > ts->pdata.debounce_tol))
    {
        /* Start over collecting consistent readings. */

        ts->read_rep = 0;
        /*
         * Repeat it, if this was the first read or the read
         * wasn't consistent enough.
         */
        if (ts->read_cnt < ts->pdata.debounce_max)
        {
            ts->last_read = *val;
            ts->read_cnt++;

            return ADS7846_FILTER_REPEAT;
        }
        else
        {
            /*
             * Maximum number of debouncing reached and still
             * not enough number of consistent readings. Abort
             * the whole sample, repeat it in the next sampling
             * period.
             */
            ts->read_cnt = 0;

            return ADS7846_FILTER_IGNORE;
        }
    }
    else
    {
        if (++ts->read_rep > ts->pdata.debounce_rep)
        {
            /* Got a good reading for this coordinate, go for the next one. */
            ts->read_cnt = 0;
            ts->read_rep = 0;
            return ADS7846_FILTER_OK;
        }
        else
        {
            /* Read more values that are consistent. */
            ts->read_cnt++;
            return ADS7846_FILTER_REPEAT;
        }
    }
}

static int ads7846_no_filter(void *ads, int data_idx, int *val)
{
    return ADS7846_FILTER_OK;
}

static int ads7846_read12_ser(struct ads7846 *ts, unsigned command)
{
    int status;
    struct ads7846_ser_req req;

    rt_memset(&req, 0, sizeof(req));

    /*
     * Internal VREF (7846 with vref-mv unset): turn ref on, discard one
     * conversion, then wait ti,vref-delay-usecs. Linux does this in one
     * SPI transaction with inter-xfer delay; RT-Thread SPI has no delay
     * field, so CS may deassert between phases — same risk as a gap after
     * the dummy read on some hosts.
     */
    if (ts->use_internal)
    {
        req.ref_on = REF_ON;
        req.msg[0].send_buf = &req.ref_on;
        req.msg[0].length = 1;
        req.msg[0].cs_take = 1;
        req.msg[0].cs_release = 0;
        req.msg[1].recv_buf = &req.scratch;
        req.msg[1].length = 2;
        rt_spi_message_append(&req.msg[0], &req.msg[1]);

        ads7846_stop(ts);
        status = rt_spi_transfer_message(ts->spi, &req.msg[0]) ? -RT_EIO : RT_EOK;
        ads7846_restart(ts);

        if (status)
        {
            return status;
        }

        rt_hw_us_delay(ts->pdata.vref_delay_usecs);
        command |= ADS_PD10_REF_ON;
    }

    /* Enable ADC in every case */
    command |= ADS_PD10_ADC_ON;

    rt_memset(req.msg, 0, sizeof(req.msg));

    /* Take sample */
    req.command = (rt_uint8_t)command;
    req.msg[0].send_buf = &req.command;
    req.msg[0].length = 1;
    req.msg[0].cs_take = 1;

    req.msg[1].recv_buf = &req.sample;
    req.msg[1].length = 2;
    rt_spi_message_append(&req.msg[0], &req.msg[1]);

    /* Converter in low power mode & enable PENIRQ */
    req.ref_off = PWRDOWN;
    req.msg[2].send_buf = &req.ref_off;
    req.msg[2].length = 1;
    rt_spi_message_append(&req.msg[0], &req.msg[2]);

    req.msg[3].recv_buf = &req.scratch;
    req.msg[3].length = 2;
    req.msg[3].cs_take = 0;
    rt_spi_message_append(&req.msg[0], &req.msg[3]);

    ads7846_stop(ts);
    status = rt_spi_transfer_message(ts->spi, &req.msg[0]) ? -RT_EIO : RT_EOK;
    ads7846_restart(ts);

    if (status == 0)
    {
        /* On-wire is a must-ignore bit, a BE12 value, then padding */
        status = rt_be16_to_cpu(req.sample);
        status = status >> 3;
        status &= 0x0fff;
    }

    return status;
}

static int ads7845_read12_ser(struct ads7846 *ts, unsigned command)
{
    int status;
    struct ads7845_ser_req req;

    rt_memset(&req, 0, sizeof(req));

    req.command[0] = (rt_uint8_t)command;
    req.msg[0].send_buf = req.command;
    req.msg[0].recv_buf = req.sample;
    req.msg[0].length = 3;

    ads7846_stop(ts);
    status = rt_spi_transfer_message(ts->spi, &req.msg[0]) ? -RT_EIO : RT_EOK;
    ads7846_restart(ts);

    if (status == 0)
    {
        /* BE12 value, then padding */
        status = get_unaligned_be16(&req.sample[1]);
        status = status >> 3;
        status &= 0x0fff;
    }

    return status;
}

static rt_bool_t ads7846_cmd_need_settle(enum ads7846_cmds cmd_idx)
{
    switch (cmd_idx)
    {
    case ADS7846_X:
    case ADS7846_Y:
    case ADS7846_Z1:
    case ADS7846_Z2:
        return RT_TRUE;

    case ADS7846_PWDOWN:
        return RT_FALSE;

    default:
        break;
    }

    return RT_FALSE;
}

static int ads7846_get_value(struct ads7846_buf *buf)
{
    int value;

    value = rt_be16_to_cpu(buf->data);

    /* Enforce ADC output is 12 bits width */
    return (value >> 3) & 0xfff;
}

static void ads7846_set_cmd_val(struct ads7846 *ts,
                                enum ads7846_cmds cmd_idx, rt_uint16_t val)
{
    struct ads7846_packet *packet = &ts->packet;

    switch (cmd_idx)
    {
    case ADS7846_Y:
        packet->y = val;
        break;

    case ADS7846_X:
        packet->x = val;
        break;

    case ADS7846_Z1:
        packet->z1 = val;
        break;

    case ADS7846_Z2:
        packet->z2 = val;
        break;

    default:
        break;
    }
}

static rt_uint8_t ads7846_get_cmd(enum ads7846_cmds cmd_idx, int vref)
{
    switch (cmd_idx)
    {
    case ADS7846_Y:
        return READ_Y(vref);

    case ADS7846_X:
        return READ_X(vref);

    /* 7846 specific commands  */
    case ADS7846_Z1:
        return READ_Z1(vref);

    case ADS7846_Z2:
        return READ_Z2(vref);

    case ADS7846_PWDOWN:
        return PWRDOWN;

    default:
        break;
    }

    return 0;
}

static rt_err_t ads7846_setup_spi_msg(struct ads7846 *ts)
{
    rt_size_t size = 0, time;
    int vref = ts->pdata.keep_vref_on;
    rt_uint32_t count, offset = 0;
    struct rt_spi_message *m = &ts->msg[0];
    struct ads7846_packet *packet = &ts->packet;

    /* Time per bit */
    time = NSEC_PER_SEC / ts->spi->config.max_hz;

    count = ts->pdata.settle_delay_usecs * NSEC_PER_USEC / time;
    packet->count_skip = RT_DIV_ROUND_UP(count, 24);

    if (ts->pdata.debounce_max && ts->pdata.debounce_rep)
    {
        /*
         * ads7846_debounce_filter() is making ts->debounce_rep + 2
         * reads. So we need to get all samples for normal case.
         */
        packet->count = ts->pdata.debounce_rep + 2;
    }
    else
    {
        packet->count = 1;
    }

    if (ts->pdata.model == 7846)
    {
        packet->cmds = 5; /* x, y, z1, z2, pwdown */
    }
    else
    {
        packet->cmds = 3; /* x, y, pwdown */
    }

    for (rt_uint32_t cmd_idx = 0; cmd_idx < packet->cmds; ++cmd_idx)
    {
        rt_uint32_t max_count;
        struct ads7846_buf_layout *layout = &packet->layout[cmd_idx];

        if (cmd_idx == packet->cmds - 1)
        {
            cmd_idx = ADS7846_PWDOWN;
        }

        if (ads7846_cmd_need_settle(cmd_idx))
        {
            max_count = packet->count + packet->count_skip;
        }
        else
        {
            max_count = packet->count;
        }

        layout->offset = offset;
        offset += max_count;
        layout->count = max_count;
        layout->skip = packet->count_skip;
        size += sizeof(*packet->tx) * max_count;
    }

    if (!(packet->tx = rt_calloc(1, size)))
    {
        return -RT_ENOMEM;
    }

    if (!(packet->rx = rt_calloc(1, size)))
    {
        rt_free(packet->tx);
        packet->tx = RT_NULL;

        return -RT_ENOMEM;
    }

    if (ts->pdata.model == 7873)
    {
        /*
         * The AD7873 is almost identical to the ADS7846
         * keep VREF off during differential/ratiometric conversion modes.
         */
        ts->pdata.model = 7846;
        vref = 0;
    }

    for (rt_uint32_t cmd_idx = 0; cmd_idx < packet->cmds; ++cmd_idx)
    {
        rt_uint8_t cmd;
        struct ads7846_buf_layout *layout = &packet->layout[cmd_idx];

        if (cmd_idx == packet->cmds - 1)
        {
            cmd_idx = ADS7846_PWDOWN;
        }

        cmd = ads7846_get_cmd(cmd_idx, vref);

        for (rt_uint32_t b = 0; b < layout->count; ++b)
        {
            packet->tx[layout->offset + b].cmd = cmd;
        }
    }

    m->send_buf = packet->tx;
    m->recv_buf = packet->rx;
    m->length = size;

    return RT_EOK;
}

static rt_err_t ads7846_filter(struct ads7846 *ts)
{
    int action, val;
    struct ads7846_packet *packet = &ts->packet;

    packet->ignore = RT_FALSE;

    for (rt_uint32_t cmd_idx = packet->last_cmd_idx; cmd_idx < packet->cmds - 1; ++cmd_idx)
    {
        struct ads7846_buf_layout *layout = &packet->layout[cmd_idx];

        packet->last_cmd_idx = cmd_idx;

        for (rt_uint32_t b = layout->skip; b < layout->count; ++b)
        {
            val = ads7846_get_value(&packet->rx[layout->offset + b]);

            action = ts->filter(ts->filter_data, cmd_idx, &val);

            if (action == ADS7846_FILTER_REPEAT)
            {
                if (b == layout->count - 1)
                {
                    return -RT_ERROR;
                }
            }
            else if (action == ADS7846_FILTER_OK)
            {
                ads7846_set_cmd_val(ts, cmd_idx, val);
                break;
            }
            else
            {
                packet->ignore = RT_TRUE;
                return RT_EOK;
            }
        }
    }

    return RT_EOK;
}

static void ads7846_report_pen_up(struct ads7846 *ts)
{
    struct rt_input_device *idev = &ts->parent;

    rt_input_report_key(idev, BTN_TOUCH, 0);
    rt_input_report_abs(idev, ABS_PRESSURE, 0);
    rt_input_sync(idev);

    ts->pendown = RT_FALSE;
}

static void ads7846_read_state(struct ads7846 *ts)
{
    rt_uint32_t msg_idx = 0;
    struct rt_spi_message *m;
    struct ads7846_packet *packet = &ts->packet;

    packet->last_cmd_idx = 0;

    while (RT_TRUE)
    {
        m = &ts->msg[msg_idx];

        if (rt_spi_transfer_message(ts->spi, m))
        {
            packet->ignore = RT_TRUE;
            return;
        }

        if (ads7846_filter(ts))
        {
            continue;
        }

        return;
    }
}

static void ads7846_report_state(struct ads7846 *ts)
{
    rt_uint32_t Rt;
    rt_uint16_t x, y, z1, z2;
    struct ads7846_packet *packet = &ts->packet;

    x = packet->x;
    y = packet->y;

    if (ts->pdata.model == 7845)
    {
        z1 = 0;
        z2 = 0;
    }
    else
    {
        z1 = packet->z1;
        z2 = packet->z2;
    }

    /* Range filtering */
    if (x == MAX_12BIT)
    {
        x = 0;
    }

    if (ts->pdata.model == 7843 || ts->pdata.model == 7845)
    {
        Rt = ts->pdata.pressure_max / 2;
    }
    else if (x && z1)
    {
        /* compute touch pressure resistance using equation #2 */
        Rt = z2;
        Rt -= z1;
        Rt *= ts->pdata.x_plate_ohms;
        Rt = RT_DIV_ROUND_CLOSEST(Rt, 16);
        Rt *= x;
        Rt /= z1;
        Rt = RT_DIV_ROUND_CLOSEST(Rt, 256);
    }
    else
    {
        Rt = 0;
    }

    if (!(packet->ignore || Rt > ts->pdata.pressure_max))
    {
        if (ts->pdata.penirq_recheck_delay_usecs)
        {
            rt_hw_us_delay(ts->pdata.penirq_recheck_delay_usecs);

            if (!ads7846_pendown_active(ts))
            {
                Rt = 0;
            }
        }

        if (Rt)
        {
            struct rt_input_device *idev = &ts->parent;

            if (!ts->pendown)
            {
                rt_input_report_key(idev, BTN_TOUCH, 1);
                ts->pendown = RT_TRUE;
            }

            rt_input_report_touch_inactive(idev, RT_TRUE);
            rt_input_report_touch_position(idev, x, y, RT_FALSE);
            rt_input_report_abs(idev, ABS_PRESSURE, ts->pdata.pressure_max - Rt);

            rt_input_sync(idev);
        }
    }
}

static void ads7846_ts_task(void *param)
{
    rt_tick_t timeout;
    struct ads7846 *ts = param;

    while (RT_TRUE)
    {
        rt_thread_suspend(ts->ts_task);
        rt_schedule();

        rt_thread_mdelay(TS_POLL_DELAY);

        while (!ts->stopped && ads7846_pendown_active(ts))
        {
            /* Pen is down, continue with the measurement */
            ads7846_read_state(ts);

            if (!ts->stopped)
            {
                ads7846_report_state(ts);
            }

            timeout = rt_tick_from_millisecond(TS_POLL_PERIOD);
            timeout += rt_tick_get();

            while (timeout > rt_tick_get() && !ts->stopped)
            {
                rt_thread_yield();
            }
        }

        if (ts->pendown && !ts->stopped)
        {
            ads7846_report_pen_up(ts);
        }
    }
}

static void ads7846_isr(int irq, void *param)
{
    struct ads7846 *ts = param;

    if (ads7846_pendown_active(ts))
    {
        rt_thread_resume(ts->ts_task);
    }
}

#ifdef RT_USING_PM
static rt_err_t ads7846_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    struct ads7846 *ts = rt_container_of(device, struct ads7846, parent.parent);

    if (!ts->suspended)
    {
        ads7846_disable(ts);

        ts->suspended = RT_TRUE;
    }

    return RT_EOK;
}

static void ads7846_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    struct ads7846 *ts = rt_container_of(device, struct ads7846, parent.parent);

    if (ts->suspended)
    {
        ts->suspended = RT_FALSE;

        ads7846_enable(ts);
    }
}

static const struct rt_device_pm_ops ads7846_pm_ops = {
    .suspend = ads7846_pm_suspend,
    .resume = ads7846_pm_resume,
};
#endif /* RT_USING_PM */

static void ads7846_get_platform_data(struct rt_spi_device *spi_dev,
                                      struct ads7846_platform_data *pdata)
{
    rt_uint32_t value;
    struct rt_device *dev = &spi_dev->parent;

    pdata->model = (rt_ubase_t)rt_spi_device_id_data(spi_dev);

    rt_dm_dev_prop_read_u16(dev, "ti,vref-delay-usecs", &pdata->vref_delay_usecs);
    rt_dm_dev_prop_read_u16(dev, "ti,vref-mv", &pdata->vref_mv);

    pdata->keep_vref_on = rt_dm_dev_prop_read_bool(dev, "ti,keep-vref-on");

    pdata->swap_xy = rt_dm_dev_prop_read_bool(dev, "ti,swap-xy");

    rt_dm_dev_prop_read_u16(dev, "ti,settle-delay-usec",
                            &pdata->settle_delay_usecs);
    rt_dm_dev_prop_read_u16(dev, "ti,penirq-recheck-delay-usecs",
                            &pdata->penirq_recheck_delay_usecs);

    rt_dm_dev_prop_read_u16(dev, "ti,x-plate-ohms", &pdata->x_plate_ohms);
    rt_dm_dev_prop_read_u16(dev, "ti,y-plate-ohms", &pdata->y_plate_ohms);

    rt_dm_dev_prop_read_u16(dev, "ti,x-min", &pdata->x_min);
    rt_dm_dev_prop_read_u16(dev, "ti,y-min", &pdata->y_min);
    rt_dm_dev_prop_read_u16(dev, "ti,x-max", &pdata->x_max);
    rt_dm_dev_prop_read_u16(dev, "ti,y-max", &pdata->y_max);

    /*
     * touchscreen-max-pressure gets parsed during
     * touchscreen_parse_properties()
     */
    rt_dm_dev_prop_read_u16(dev, "ti,pressure-min", &pdata->pressure_min);
    if (!rt_dm_dev_prop_read_u32(dev, "touchscreen-min-pressure", &value))
    {
        pdata->pressure_min = (rt_uint16_t)value;
    }
    rt_dm_dev_prop_read_u16(dev, "ti,pressure-max", &pdata->pressure_max);

    rt_dm_dev_prop_read_u16(dev, "ti,debounce-max", &pdata->debounce_max);
    if (!rt_dm_dev_prop_read_u32(dev, "touchscreen-average-samples", &value))
    {
        pdata->debounce_max = (rt_uint16_t)value;
    }
    rt_dm_dev_prop_read_u16(dev, "ti,debounce-tol", &pdata->debounce_tol);
    rt_dm_dev_prop_read_u16(dev, "ti,debounce-rep", &pdata->debounce_rep);

    rt_dm_dev_prop_read_u32(dev, "ti,pendown-gpio-debounce",
                            &pdata->gpio_pendown_debounce);
}

static rt_err_t ads7846_probe(struct rt_spi_device *spi_dev)
{
    rt_err_t err = RT_EOK;
    struct rt_touch_info touch_info = {};
    struct rt_device *dev = &spi_dev->parent;
    struct ads7846 *ts = rt_calloc(1, sizeof(*ts));

    if (!ts)
    {
        return -RT_ENOMEM;
    }
    ts->spi = spi_dev;
    ts->parent.parent.ofw_node = dev->ofw_node;

    ads7846_get_platform_data(spi_dev, &ts->pdata);
    ts->pdata.vref_delay_usecs = ts->pdata.vref_delay_usecs ?: 100;
    ts->pdata.x_plate_ohms = ts->pdata.x_plate_ohms ?: 400;

    /* Linux ads784x_hwmon_register: internal ref when 7846 and no ti,vref-mv */
    if (ts->pdata.model == 7846 && ts->pdata.vref_mv == 0)
    {
        ts->use_internal = RT_TRUE;
    }

    if (ts->pdata.debounce_max)
    {
        if (ts->pdata.debounce_max < 2)
        {
            ts->pdata.debounce_max = 2;
        }
        ts->filter_data = ts;
        ts->filter = ads7846_debounce_filter;
    }
    else
    {
        ts->filter = ads7846_no_filter;
    }

    ts->gpio_pendown = rt_pin_get_named_pin(dev, "pendown", 0,
                                            RT_NULL, &ts->gpio_pendown_active);

    if (ts->gpio_pendown < 0 && ts->gpio_pendown != PIN_NONE)
    {
        err = ts->gpio_pendown;
        goto _free;
    }

    if (ts->pdata.gpio_pendown_debounce)
    {
        rt_pin_debounce(ts->gpio_pendown, ts->pdata.gpio_pendown_debounce);
    }

    err |= rt_input_set_capability(&ts->parent, EV_ABS, ABS_X);
    err |= rt_input_set_capability(&ts->parent, EV_ABS, ABS_Y);
    err |= rt_input_set_capability(&ts->parent, EV_KEY, BTN_TOUCH);

    if (err)
    {
        goto _free_input_config;
    }

    rt_input_set_absinfo(&ts->parent, ABS_X,
                         ts->pdata.x_min ?: 0, ts->pdata.x_max ?: MAX_12BIT, 0, 0);
    rt_input_set_absinfo(&ts->parent, ABS_Y,
                         ts->pdata.y_min ?: 0, ts->pdata.y_max ?: MAX_12BIT, 0, 0);

    if (ts->pdata.model != 7845)
    {
        rt_input_set_absinfo(&ts->parent, ABS_PRESSURE,
                             ts->pdata.pressure_min, ts->pdata.pressure_max, 0, 0);
    }

    touch_info.type = RT_TOUCH_TYPE_RESISTANCE;
    touch_info.vendor = RT_TOUCH_VENDOR_UNKNOWN;

    if ((err = rt_input_setup_touch(&ts->parent, 0, &touch_info)))
    {
        goto _free_input_config;
    }

    ts->pdata.pressure_max = ts->parent.absinfo[ABS_PRESSURE].maximum ?: ~0;

    /*
     * Legacy ti,swap-xy when generic touchscreen-swapped-x-y was not set
     * (Linux ads7846_probe after touchscreen_parse_properties).
     */
    ads7846_apply_legacy_swap_xy(&ts->parent, ts->pdata.swap_xy);

    if ((err = ads7846_setup_spi_msg(ts)))
    {
        goto _free_input_config;
    }

    ts->supply = rt_regulator_get(dev, "vcc");

    if (rt_is_err(ts->supply))
    {
        err = rt_ptr_err(ts->supply);
        goto _free_msg;
    }

    if (ts->supply && (err = rt_regulator_enable(ts->supply)))
    {
        goto _free_regulator;
    }

    if ((ts->irq = rt_dm_dev_get_irq(dev, 0)) < 0)
    {
        err = ts->irq;
        goto _free_disable_regulator;
    }

    if ((err = rt_input_device_register(&ts->parent)))
    {
        goto _free_disable_regulator;
    }

    spi_dev->parent.user_data = ts;

#ifdef RT_USING_PM
    rt_pm_device_register(&ts->parent.parent, &ads7846_pm_ops);
#endif

    ts->ts_task = rt_thread_create(rt_dm_dev_get_name(dev), &ads7846_ts_task,
                                   ts, DM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 2, 10);

    if (!ts->ts_task)
    {
        rt_input_device_unregister(&ts->parent);
        goto _free_disable_regulator;
    }

    if (ts->pdata.model == 7845)
    {
        ads7845_read12_ser(ts, PWRDOWN);
    }
    else
    {
        ads7846_read12_ser(ts, READ_12BIT_SER(vaux));
    }

    rt_hw_interrupt_install(ts->irq, ads7846_isr, ts, rt_dm_dev_get_name(dev));
    rt_hw_interrupt_umask(ts->irq);

    rt_thread_startup(ts->ts_task);

    return RT_EOK;

_free_disable_regulator:
    if (ts->supply)
    {
        rt_regulator_disable(ts->supply);
    }

_free_regulator:
    rt_regulator_put(ts->supply);

_free_msg:
    rt_free(ts->packet.tx);
    rt_free(ts->packet.rx);

_free_input_config:
    rt_input_remove_config(&ts->parent);

_free:
    rt_free(ts);

    return err;
}

static rt_err_t ads7846_remove(struct rt_spi_device *spi_dev)
{
    struct ads7846 *ts = spi_dev->parent.user_data;

#ifdef RT_USING_PM
    rt_pm_device_unregister(&ts->parent.parent);
#endif

    rt_input_device_unregister(&ts->parent);

    ads7846_disable(ts);

    rt_hw_interrupt_mask(ts->irq);
    rt_pic_detach_irq(ts->irq, ts);

    rt_thread_delete(ts->ts_task);

    rt_regulator_put(ts->supply);

    rt_free(ts->packet.tx);
    rt_free(ts->packet.rx);

    rt_free(ts);

    return RT_EOK;
}

static const struct rt_spi_device_id ads7846_ids[] = {
    { .name = "xpt2046", .data = (void *)7846 },
    { .name = "tsc2046", .data = (void *)7846 },
    { .name = "ads7843", .data = (void *)7843 },
    { .name = "ads7845", .data = (void *)7845 },
    { .name = "ads7846", .data = (void *)7846 },
    { .name = "ads7873", .data = (void *)7873 },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id ads7846_ofw_ids[] = {
    { .compatible = "ti,xpt2046", .data = (void *)7846 },
    { .compatible = "ti,tsc2046", .data = (void *)7846 },
    { .compatible = "ti,ads7843", .data = (void *)7843 },
    { .compatible = "ti,ads7845", .data = (void *)7845 },
    { .compatible = "ti,ads7846", .data = (void *)7846 },
    { .compatible = "ti,ads7873", .data = (void *)7873 },
    { /* sentinel */ },
};

static struct rt_spi_driver ads7846_driver = {
    .ids = ads7846_ids,
    .ofw_ids = ads7846_ofw_ids,

    .probe = ads7846_probe,
    .remove = ads7846_remove,
};
RT_SPI_DRIVER_EXPORT(ads7846_driver);
