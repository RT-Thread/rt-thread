/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-23     GuEe-GUI     first version
 */

#ifndef __PTP_H__
#define __PTP_H__

#include <rthw.h>
#include <rtthread.h>
#include <drivers/misc.h>

struct rt_ptp_pin;
struct rt_ptp_ops;

struct rt_ptp_clock
{
    struct rt_device parent;

    const struct rt_ptp_ops *ops;

    /* Maximum frequency adjustment in ppb (parts per billion), required when adjfreq is implemented */
    rt_int32_t max_freq;
    rt_int32_t alarm_nr;
    rt_int32_t pins_nr;
    rt_int32_t extts_nr;
    rt_int32_t perout_nr;
    rt_int32_t pps;

    rt_list_t notifier_nodes;
    struct rt_spinlock nodes_lock;

    struct rt_ptp_pin *pins;
    struct rt_mutex pin_mutex;
};
#define rt_device_to_ptp_clock(dev) rt_container_of(dev, struct rt_ptp_clock, parent)

struct rt_ptp_clock_time
{
    rt_int64_t sec;
    rt_int32_t nsec;
};

enum
{
    PTP_CLOCK_EV_ALARM,
    PTP_CLOCK_EV_EXTTS,
    PTP_CLOCK_EV_EXTOFF,
    PTP_CLOCK_EV_PPS,
    PTP_CLOCK_EV_PPSUSR,

    PTP_CLOCK_EV_MAX,
};

struct rt_ptp_clock_event
{
    rt_uint32_t type;
    rt_uint32_t index;

    union
    {
        rt_uint64_t timestamp;
        rt_int64_t offset;
        struct rt_ptp_clock_time pps_times;
    };
};

struct rt_ptp_clock_notifier
{
    rt_list_t list;
    rt_uint32_t event_mask;

    struct rt_ptp_clock *ptp;
    void (*callback)(struct rt_ptp_clock_notifier *notifier, struct rt_ptp_clock_event *ev);

    void *priv;
};

enum
{
    PTP_PIN_FUNC_NONE,
    PTP_PIN_FUNC_EXTTS,
    PTP_PIN_FUNC_PEROUT,
    PTP_PIN_FUNC_PHYSYNC,

    PTP_PIN_FUNC_MAX,
};

struct rt_ptp_pin
{
    char name[64];

    rt_uint32_t func;
    rt_uint32_t chan;
};

struct rt_ptp_request_extts
{
    rt_uint32_t chan;

#define PTP_ENABLE_FEATURE      RT_BIT(0)
#define PTP_RISING_EDGE         RT_BIT(1)
#define PTP_FALLING_EDGE        RT_BIT(2)
#define PTP_STRICT_FLAGS        RT_BIT(3)
#define PTP_EXTTS_EDGES         (PTP_RISING_EDGE | PTP_FALLING_EDGE)
    rt_uint32_t flags;
};

struct rt_ptp_request_perout
{
    rt_uint32_t chan;

#define PTP_PEROUT_ONE_SHOT     RT_BIT(0)
#define PTP_PEROUT_DUTY_CYCLE   RT_BIT(1)
#define PTP_PEROUT_PHASE        RT_BIT(2)
    rt_uint32_t flags;

    /* Desired period, zero means disable */
    struct rt_ptp_clock_time period;
    /* The "on" time of the signal, must be lower than the period */
    struct rt_ptp_clock_time on;
    /* Absolute start time or phase offset */
    struct rt_ptp_clock_time start_phase;
};

enum
{
    PTP_CLK_REQ_EXTTS,
    PTP_CLK_REQ_PEROUT,
    PTP_CLK_REQ_PPS,

    PTP_CLK_REQ_MAX,
};

struct rt_ptp_clock_request
{
    rt_uint32_t type;

    union
    {
        struct rt_ptp_request_extts extts;
        struct rt_ptp_request_perout perout;
    };
};

struct rt_ptp_ops
{
    rt_err_t (*adjfreq)(struct rt_ptp_clock *ptp, rt_base_t freq);
    rt_err_t (*adjphase)(struct rt_ptp_clock *ptp, rt_int32_t phase);
    rt_err_t (*getmaxphase)(struct rt_ptp_clock *ptp, rt_int32_t *out_maxphase);
    rt_err_t (*adjtime)(struct rt_ptp_clock *ptp, rt_int64_t delta);
    rt_err_t (*gettime)(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts);
    rt_err_t (*settime)(struct rt_ptp_clock *ptp, const struct rt_ptp_clock_time *ts);
    rt_err_t (*enable)(struct rt_ptp_clock *ptp, struct rt_ptp_clock_request *request, rt_bool_t on);
    rt_err_t (*verify)(struct rt_ptp_clock *ptp, rt_uint32_t pin, rt_uint32_t func, rt_uint32_t chan);
    rt_err_t (*getsnapshot)(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts);
};

rt_err_t rt_ptp_clock_register(struct rt_ptp_clock *ptp);
rt_err_t rt_ptp_clock_unregister(struct rt_ptp_clock *ptp);

rt_err_t rt_ptp_clock_notifier_register(struct rt_ptp_clock *ptp,
        struct rt_ptp_clock_notifier *notifier);
rt_err_t rt_ptp_clock_notifier_unregister(struct rt_ptp_clock *ptp,
        struct rt_ptp_clock_notifier *notifier);

void rt_ptp_clock_event(struct rt_ptp_clock *ptp, struct rt_ptp_clock_event *ev);

rt_err_t rt_ptp_adjfreq(struct rt_ptp_clock *ptp, rt_base_t freq);

rt_err_t rt_ptp_adjphase(struct rt_ptp_clock *ptp, rt_int32_t phase);
rt_err_t rt_ptp_getmaxphase(struct rt_ptp_clock *ptp, rt_int32_t *out_maxphase);

rt_err_t rt_ptp_adjtime(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts);

rt_err_t rt_ptp_gettime(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts);
rt_err_t rt_ptp_settime(struct rt_ptp_clock *ptp, const struct rt_ptp_clock_time *ts);

rt_err_t rt_ptp_request_extts(struct rt_ptp_clock *ptp,
        struct rt_ptp_request_extts *extts);
rt_err_t rt_ptp_request_perout(struct rt_ptp_clock *ptp,
        struct rt_ptp_request_perout *perout);
rt_err_t rt_ptp_enable_pps(struct rt_ptp_clock *ptp, rt_bool_t on);

rt_err_t rt_ptp_get_pin_func(struct rt_ptp_clock *ptp,
        rt_uint32_t pin, struct rt_ptp_pin *out_pin);
/*
 * Assign pin function only updates pin routing metadata.
 * Call rt_ptp_request_extts() or rt_ptp_request_perout() separately to enable hardware.
 */
rt_err_t rt_ptp_set_pin_func(struct rt_ptp_clock *ptp,
        rt_uint32_t pin, rt_uint32_t func, rt_uint32_t chan);

rt_err_t rt_ptp_getsnapshot(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts);

#endif /* __PTP_H__ */
