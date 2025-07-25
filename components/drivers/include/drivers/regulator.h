/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __REGULATOR_H__
#define __REGULATOR_H__

#include <ref.h>
#include <rthw.h>
#include <rtthread.h>

#include <drivers/misc.h>

#define RT_REGULATOR_UVOLT_INVALID  (((int)(RT_UINT32_MAX >> 1)))

struct rt_regulator_param
{
    const char *name;

    int min_uvolt;      /* In uV */
    int max_uvolt;      /* In uV */
    int min_uamp;       /* In uA */
    int max_uamp;       /* In uA */
    int ramp_delay;     /* In uV/usec */
    int enable_delay;   /* In usec */
    int off_on_delay;   /* In usec */

    rt_uint32_t enable_active_high:1;
    rt_uint32_t boot_on:1;                  /* Is enabled on boot */
    rt_uint32_t always_on:1;                /* Must be enabled */
    rt_uint32_t soft_start:1;               /* Ramp voltage slowly */
    rt_uint32_t pull_down:1;                /* Pull down resistor when regulator off */
    rt_uint32_t over_current_protection:1;  /* Auto disable on over current */
};

struct rt_regulator_ops;

struct rt_regulator_node
{
    rt_list_t list;
    rt_list_t children_nodes;

    struct rt_device *dev;
    struct rt_regulator_node *parent;

    const char *supply_name;
    const struct rt_regulator_ops *ops;

    struct rt_ref ref;
    rt_atomic_t enabled_count;

    const struct rt_regulator_param *param;

    rt_list_t notifier_nodes;

    void *priv;
};

/*
 * NOTE: Power regulator control is dangerous work. We don't want non-internal
 * consumer could access the power regulator tree without regulator's API. So
 * we defined the `rt_regulator` member in core instead of here.
 */
struct rt_regulator;

#define RT_REGULATOR_MODE_INVALID           0
#define RT_REGULATOR_MODE_FAST              RT_BIT(0)
#define RT_REGULATOR_MODE_NORMAL            RT_BIT(1)
#define RT_REGULATOR_MODE_IDLE              RT_BIT(2)
#define RT_REGULATOR_MODE_STANDBY           RT_BIT(3)

struct rt_regulator_ops
{
    rt_err_t    (*enable)(struct rt_regulator_node *reg);
    rt_err_t    (*disable)(struct rt_regulator_node *reg);
    rt_bool_t   (*is_enabled)(struct rt_regulator_node *reg);
    rt_err_t    (*set_voltage)(struct rt_regulator_node *reg, int min_uvolt, int max_uvolt);
    int         (*get_voltage)(struct rt_regulator_node *reg);
    rt_err_t    (*set_mode)(struct rt_regulator_node *reg, rt_uint32_t mode);
    rt_int32_t  (*get_mode)(struct rt_regulator_node *reg);
    rt_err_t    (*set_ramp_delay)(struct rt_regulator_node *reg, int ramp);
    rt_uint32_t (*enable_time)(struct rt_regulator_node *reg);
};

struct rt_regulator_notifier;

#define RT_REGULATOR_MSG_ENABLE             RT_BIT(0)
#define RT_REGULATOR_MSG_DISABLE            RT_BIT(1)
#define RT_REGULATOR_MSG_VOLTAGE_CHANGE     RT_BIT(2)
#define RT_REGULATOR_MSG_VOLTAGE_CHANGE_ERR RT_BIT(3)

union rt_regulator_notifier_args
{
    struct
    {
        int old_uvolt;
        int min_uvolt;
        int max_uvolt;
    };
};

typedef rt_err_t (*rt_regulator_notifier_callback)(struct rt_regulator_notifier *notifier,
        rt_ubase_t msg, void *data);

struct rt_regulator_notifier
{
    rt_list_t list;

    struct rt_regulator *regulator;
    rt_regulator_notifier_callback callback;
    void *priv;
};

rt_err_t rt_regulator_register(struct rt_regulator_node *reg_np);
rt_err_t rt_regulator_unregister(struct rt_regulator_node *reg_np);

rt_err_t rt_regulator_notifier_register(struct rt_regulator *reg,
        struct rt_regulator_notifier *notifier);
rt_err_t rt_regulator_notifier_unregister(struct rt_regulator *reg,
        struct rt_regulator_notifier *notifier);

struct rt_regulator *rt_regulator_get(struct rt_device *dev, const char *id);
void rt_regulator_put(struct rt_regulator *reg);

rt_err_t rt_regulator_enable(struct rt_regulator *reg);
rt_err_t rt_regulator_disable(struct rt_regulator *reg);
rt_bool_t rt_regulator_is_enabled(struct rt_regulator *reg);

rt_bool_t rt_regulator_is_supported_voltage(struct rt_regulator *reg, int min_uvolt, int max_uvolt);
rt_err_t rt_regulator_set_voltage(struct rt_regulator *reg, int min_uvolt, int max_uvolt);
int rt_regulator_get_voltage(struct rt_regulator *reg);

rt_err_t rt_regulator_set_mode(struct rt_regulator *reg, rt_uint32_t mode);
rt_int32_t rt_regulator_get_mode(struct rt_regulator *reg);

rt_inline rt_err_t rt_regulator_set_voltage_triplet(struct rt_regulator *reg,
        int min_uvolt, int target_uvolt, int max_uvolt)
{
    if (!rt_regulator_set_voltage(reg, target_uvolt, max_uvolt))
    {
        return RT_EOK;
    }

    return rt_regulator_set_voltage(reg, min_uvolt, max_uvolt);
}

#endif /* __REGULATOR_H__ */
