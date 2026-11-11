/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#ifndef __DVFS_H__
#define __DVFS_H__

#include <rtthread.h>
#include <drivers/ofw.h>
#include <drivers/misc.h>
#include <drivers/core/dm.h>

#include <ref.h>
#include <bitmap.h>

enum
{
    /* Run the device at the maximum frequency */
    RT_DVFS_GOVERNOR_TYPE_PERFORMANCE = 0,
    /* Run the device at the minimum frequency */
    RT_DVFS_GOVERNOR_TYPE_POWERSAVE,
    /* Run the device at user specified frequencies */
    RT_DVFS_GOVERNOR_TYPE_FREEDOM,
    /*
     * Scales the frequency dynamically according to current load.
     * Jumps to the highest frequency and then possibly back off as
     * the idle time increases.
     */
    RT_DVFS_GOVERNOR_TYPE_ONDEMAND,
    /*
     * Scales the frequency dynamically according to current load.
     * Scales the frequency more gradually than ondemand.
     */
    RT_DVFS_GOVERNOR_TYPE_CONSERVATIVE,
    /* Scheduler-driven CPU frequency selection */
    RT_DVFS_GOVERNOR_TYPE_SCHEDUTIL,

    /* Custom for user start */
    RT_DVFS_GOVERNOR_TYPE_CUSTOM,
};

struct rt_dvfs_opp;
struct rt_dvfs_opp_table;
struct rt_dvfs_governor;
struct rt_dvfs_scaling_ops;
struct rt_dvfs_event_ops;
struct rt_dvfs_idle_ops;
struct rt_dvfs_idle_status;
struct rt_dvfs_idle_status_table;

/* CPU load statistics */
struct rt_dvfs_cpu_load
{
    rt_uint64_t total_tick;            /* Total ticks in sampling period */
    rt_uint64_t idle_tick;             /* Idle ticks in sampling period */
    rt_uint32_t load_percentage;       /* Load percentage (0-100) */
    rt_tick_t last_update;             /* Last update tick */
};

/* Governor parameters (Linux-like defaults) */
struct rt_dvfs_governor_params
{
    rt_uint32_t sampling_rate_ms;      /* Sampling interval in ms, default 1000 */
    rt_uint32_t up_threshold;          /* Up threshold percentage, default 80 */
    rt_uint32_t down_differential;     /* Down differential percentage, default 20 */
    rt_uint32_t sampling_down_factor;  /* Sampling down factor for conservative, default 1 */
    rt_uint32_t freq_step;             /* Frequency step percentage for conservative, default 5 */
    rt_bool_t ignore_nice_load;        /* Ignore nice tasks, default RT_FALSE */
    rt_uint32_t powersave_bias;        /* Powersave bias percentage, default 0 */
};

struct rt_dvfs_scaling
{
    struct rt_device *dev;

    struct rt_clk *clk;
    struct rt_regulator *supply;

    const struct rt_dvfs_scaling_ops *ops;

    /* Hz */
    rt_ubase_t min_freq;
    rt_ubase_t max_freq;
    rt_ubase_t cur_freq;
    rt_ubase_t suspend_freq;

    /* NS */
    rt_uint32_t retry_delay;
    rt_uint32_t transition_latency;

    struct rt_dvfs_opp_table *opp_table;

    struct rt_dvfs_governor *gov;
    struct rt_dvfs_governor_params gov_params;
    void *gov_data;

    /* CPU load statistics */
    struct rt_dvfs_cpu_load cpu_load;
    void (*load_update)(struct rt_dvfs_scaling *dvfs);

    void *priv;
};

struct rt_dvfs_scaling_ops
{
    rt_err_t (*suspend)(struct rt_dvfs_scaling *dvfs);
    rt_err_t (*resume)(struct rt_dvfs_scaling *dvfs);
    rt_err_t (*set_opp)(struct rt_dvfs_scaling *dvfs, struct rt_dvfs_opp *opp);

    rt_err_t (*parse_opp)(struct rt_dvfs_scaling *dvfs, struct rt_dvfs_opp *opp, void *fw_np);
};

/*
 * DVFS device hierarchy:
 *   rt_dvfs_scaling  - internal core (OPP / governor / frequency)
 *   rt_dvfs_devfreq  - DVFS device (clk/regulator + optional event)
 *   rt_dvfs_cpufreq  - CPU DVFS, extends devfreq (idle-hook load)
 */
struct rt_dvfs_devfreq
{
    struct rt_dvfs_scaling parent;

    struct rt_dvfs_event *ev;
};

struct rt_dvfs_cpufreq
{
    struct rt_dvfs_devfreq parent;

    int master_cpu;
    RT_BITMAP_DECLARE(cpus_map, RT_CPUS_NR);
};

rt_inline struct rt_dvfs_scaling *rt_dvfs_devfreq_to_scaling(struct rt_dvfs_devfreq *devfreq)
{
    return &devfreq->parent;
}

rt_inline struct rt_dvfs_devfreq *rt_dvfs_cpufreq_to_devfreq(struct rt_dvfs_cpufreq *cpufreq)
{
    return &cpufreq->parent;
}

rt_inline struct rt_dvfs_scaling *rt_dvfs_cpufreq_to_scaling(struct rt_dvfs_cpufreq *cpufreq)
{
    return &cpufreq->parent.parent;
}

extern struct rt_dvfs_scaling_ops rt_dvfs_devfreq_ops;

struct rt_dvfs_idle
{
    struct rt_device *dev;

    rt_uint32_t ref_count;
    rt_uint32_t entry_count;

    const struct rt_dvfs_idle_ops *ops;

    struct rt_dvfs_idle_status_table *status_table;

    void *priv;
};

struct rt_dvfs_idle_ops
{
    rt_err_t (*entry)(struct rt_dvfs_idle *idle, struct rt_dvfs_idle_status *status);
    rt_err_t (*exit)(struct rt_dvfs_idle *idle, struct rt_dvfs_idle_status *status);

    rt_bool_t (*timer_can_stop)(struct rt_dvfs_idle *idle);
};

struct rt_dvfs_idle_status
{
    rt_list_t list;

    rt_uint32_t entry_latency_us;
    rt_uint32_t exit_latency_us;
    rt_uint32_t min_residency_us;

    rt_bool_t timer_stop;

    void *priv;
};

struct rt_dvfs_idle_status_table
{
    rt_list_t status_nodes;
    struct rt_dvfs_idle_status *current_status;

    void *priv;
};

struct rt_dvfs_opp
{
    rt_list_t list;

    rt_ubase_t freq;    /* Hz */
    rt_ubase_t uvolt;   /* uV */
    rt_ubase_t power;   /* mW */
    rt_bool_t available;

    void *priv;
};

struct rt_dvfs_opp_table
{
    rt_bool_t share;

    rt_list_t opp_nodes;
    struct rt_dvfs_opp *current_opp;

    void *priv;
};

struct rt_dvfs_event_data
{
    /* Load count of dvfs-event device for the given period */
    rt_ubase_t load_count;
    /* Total count of dvfs-event device for the given period */
    rt_ubase_t total_count;
};

struct rt_dvfs_event
{
    struct rt_device *dev;

    const struct rt_dvfs_event_ops *ops;

    rt_uint32_t enable_count;
    struct rt_spinlock lock;

    void *priv;
};

struct rt_dvfs_event_ops
{
    rt_err_t (*ready)(struct rt_dvfs_event *ev);
    rt_err_t (*read)(struct rt_dvfs_event *ev, struct rt_dvfs_event_data *evd);

    rt_err_t (*enable)(struct rt_dvfs_event *ev);
    rt_err_t (*disable)(struct rt_dvfs_event *ev);
    rt_err_t (*reset)(struct rt_dvfs_event *ev);
};

struct rt_dvfs_governor
{
    rt_list_t list;
    char name[16];

    rt_uint32_t type;
    struct rt_ref ref;

    rt_err_t (*start)(struct rt_dvfs_scaling *dvfs);
    rt_err_t (*stop)(struct rt_dvfs_scaling *dvfs);
    rt_err_t (*suspend)(struct rt_dvfs_scaling *dvfs);
    rt_err_t (*resume)(struct rt_dvfs_scaling *dvfs);
    rt_err_t (*set_interval)(struct rt_dvfs_scaling *dvfs, rt_uint32_t interval_ms);
    rt_err_t (*set_frequency)(struct rt_dvfs_scaling *dvfs, rt_ubase_t *out_freq);
};

/* DVFS */
rt_err_t rt_dvfs_scaling_register(struct rt_dvfs_scaling *dvfs);
rt_err_t rt_dvfs_scaling_unregister(struct rt_dvfs_scaling *dvfs);

void rt_dvfs_scaling_enter(struct rt_dvfs_scaling *dvfs);
void rt_dvfs_scaling_leave(struct rt_dvfs_scaling *dvfs);

void rt_dvfs_ns_sleep(rt_uint32_t ns);

rt_err_t rt_dvfs_scaling_suspend(struct rt_dvfs_scaling *dvfs);
rt_err_t rt_dvfs_scaling_resume(struct rt_dvfs_scaling *dvfs);
rt_err_t rt_dvfs_scaling_set_governor(struct rt_dvfs_scaling *dvfs, rt_uint32_t governor);
rt_err_t rt_dvfs_scaling_set_frequency(struct rt_dvfs_scaling *dvfs, rt_ubase_t frequency);
rt_err_t rt_dvfs_scaling_apply_opp(struct rt_dvfs_scaling *dvfs, struct rt_dvfs_opp *opp);

/* OPP */
struct rt_dvfs_opp *rt_dvfs_scaling_add_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq, rt_ubase_t uvolt);
rt_err_t rt_dvfs_scaling_remove_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq);
rt_err_t rt_dvfs_scaling_remove_opp_all(struct rt_dvfs_scaling *dvfs);

rt_err_t rt_dvfs_scaling_enable_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq);
rt_err_t rt_dvfs_scaling_disable_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq);

struct rt_dvfs_opp *rt_dvfs_scaling_find_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq);
struct rt_dvfs_opp *rt_dvfs_scaling_find_ceil_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq);
struct rt_dvfs_opp *rt_dvfs_scaling_find_floor_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq);

/* CPU */
rt_err_t rt_dvfs_cpufreq_register(struct rt_dvfs_cpufreq *cpufreq);
rt_err_t rt_dvfs_cpufreq_unregister(struct rt_dvfs_cpufreq *cpufreq);

rt_err_t rt_dvfs_devfreq_register(struct rt_dvfs_devfreq *devfreq);
rt_err_t rt_dvfs_devfreq_unregister(struct rt_dvfs_devfreq *devfreq);

/* CPU-Idle */
rt_err_t rt_dvfs_idle_register(struct rt_dvfs_idle *idle);
rt_err_t rt_dvfs_idle_unregister(struct rt_dvfs_idle *idle);

rt_err_t rt_dvfs_idle_add_status(struct rt_dvfs_idle *idle, struct rt_dvfs_idle_status *status);
void rt_dvfs_idle_remove_status(struct rt_dvfs_idle *idle, struct rt_dvfs_idle_status *status);
void rt_dvfs_idle_remove_status_all(struct rt_dvfs_idle *idle,
        void (*release)(struct rt_dvfs_idle *, struct rt_dvfs_idle_status *));

rt_err_t rt_dvfs_idle_entry(struct rt_dvfs_idle *idle);
rt_err_t rt_dvfs_idle_exit(struct rt_dvfs_idle *idle);

struct rt_dvfs_idle *rt_dvfs_idle_get(struct rt_device *dev);
void rt_dvfs_idle_put(struct rt_dvfs_idle *idle);

/* Event */
rt_err_t rt_dvfs_event_register(struct rt_dvfs_event *ev);
rt_err_t rt_dvfs_event_unregister(struct rt_dvfs_event *ev);

rt_err_t rt_dvfs_event_ready(struct rt_dvfs_event *ev);
rt_err_t rt_dvfs_event_read(struct rt_dvfs_event *ev, struct rt_dvfs_event_data *evd);
rt_err_t rt_dvfs_event_enable(struct rt_dvfs_event *ev);
rt_err_t rt_dvfs_event_disable(struct rt_dvfs_event *ev);
rt_bool_t rt_dvfs_event_is_enabled(struct rt_dvfs_event *ev);
rt_err_t rt_dvfs_event_reset(struct rt_dvfs_event *ev);

struct rt_dvfs_event *rt_dvfs_event_get(struct rt_device *dev, const char *name, int index);
void rt_dvfs_event_put(struct rt_dvfs_event *ev);

/* Governor */
rt_err_t rt_dvfs_governor_register(struct rt_dvfs_governor *gov);
rt_err_t rt_dvfs_governor_unregister(struct rt_dvfs_governor *gov);
struct rt_dvfs_governor *rt_dvfs_governor_get(rt_uint32_t governor);
struct rt_dvfs_governor *rt_dvfs_governor_get_by_name(const char *name);
void rt_dvfs_governor_put(struct rt_dvfs_governor *gov);

rt_err_t rt_dvfs_governor_set_params(struct rt_dvfs_scaling *dvfs, struct rt_dvfs_governor_params *params);
rt_err_t rt_dvfs_governor_get_params(struct rt_dvfs_scaling *dvfs, struct rt_dvfs_governor_params *params);

/* Load */
void rt_dvfs_load_update(struct rt_dvfs_scaling *dvfs);
void rt_dvfs_cpu_load_update(struct rt_dvfs_cpu_load *load);
rt_uint32_t rt_dvfs_cpu_load_get(struct rt_dvfs_cpu_load *load);

/* PM */
struct rt_device_pm;

rt_err_t rt_dvfs_scaling_pm_suspend(struct rt_device_pm *device_pm, rt_uint8_t mode);
rt_err_t rt_dvfs_scaling_pm_resume(struct rt_device_pm *device_pm, rt_uint8_t mode);
rt_err_t rt_dvfs_scaling_pm_frequency_change(struct rt_device_pm *device_pm, rt_uint8_t mode);

#endif /* __DVFS_H__ */
