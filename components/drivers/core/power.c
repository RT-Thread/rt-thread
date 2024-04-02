/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-24     GuEe-GUI     the first version
 */

#include <rtdevice.h>

#define DBG_TAG "rtdm.power"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct power_off_track
{
    rt_slist_t list;

    struct rt_device *dev;
    rt_err_t (*callback)(struct rt_device *);
};

void (*rt_dm_machine_shutdown)(void) = RT_NULL;
void (*rt_dm_machine_reset)(void) = RT_NULL;

static struct rt_spinlock _power_off_lock = {};
static rt_slist_t _power_off_handler_nodes[RT_DM_POWER_OFF_MODE_NR][RT_DM_POWER_OFF_PRIO_NR] =
{
    [0 ... RT_DM_POWER_OFF_MODE_NR - 1] =
    {
        [0 ... RT_DM_POWER_OFF_PRIO_NR - 1] =
        {
            RT_NULL,
        }
    }
};

static rt_used char * const _mode_name[] =
{
    [RT_DM_POWER_OFF_MODE_SHUTDOWN]         = "SHUTDOWN",
    [RT_DM_POWER_OFF_MODE_RESET]            = "RESET",
};

rt_err_t rt_dm_power_off_handler(struct rt_device *dev, int mode, int priority,
        rt_err_t (*callback)(struct rt_device *dev))
{
    struct power_off_track *track;

    RT_ASSERT(mode < RT_DM_POWER_OFF_MODE_NR);
    RT_ASSERT(priority < RT_DM_POWER_OFF_PRIO_NR);

    track = rt_malloc(sizeof(*track));

    if (!track)
    {
        return -RT_ENOMEM;
    }

    rt_slist_init(&track->list);
    track->dev = dev;
    track->callback = callback;

    rt_hw_spin_lock(&_power_off_lock.lock);

    rt_slist_insert(&_power_off_handler_nodes[mode][priority], &track->list);

    rt_hw_spin_unlock(&_power_off_lock.lock);

    return RT_EOK;
}

static void dm_power_off_handler(int mode)
{
    struct power_off_track *track;

    rt_hw_spin_lock(&_power_off_lock.lock);

    for (int i = 0; i < RT_DM_POWER_OFF_PRIO_NR; ++i)
    {
        rt_slist_t *nodes = &_power_off_handler_nodes[mode][i];

        rt_slist_for_each_entry(track, nodes, list)
        {
            rt_err_t err;
            struct rt_device *dev = track->dev;

            if ((err = track->callback(dev)))
            {
                LOG_E("%s: %s fail error = %s", dev ? rt_dm_dev_get_name(dev) : RT_NULL,
                    _mode_name[mode], rt_strerror(err));
            }
        }
    }

    rt_hw_spin_unlock(&_power_off_lock.lock);
}

struct reboot_mode_track
{
    rt_slist_t list;

    struct rt_device *dev;
    rt_err_t (*callback)(struct rt_device *, char *cmd);
};

static char *_reboot_mode_cmd = "normal";
static struct rt_spinlock _reboot_mode_lock = {};
static rt_slist_t _reboot_mode_handler_nodes = { RT_NULL };

rt_err_t rt_dm_reboot_mode_register(struct rt_device *dev,
        rt_err_t (*callback)(struct rt_device *, char *cmd))
{
    struct reboot_mode_track *track;

    track = rt_malloc(sizeof(*track));

    if (!track)
    {
        return -RT_ENOMEM;
    }

    rt_slist_init(&track->list);
    track->dev = dev;
    track->callback = callback;

    rt_hw_spin_lock(&_reboot_mode_lock.lock);

    rt_slist_insert(&_reboot_mode_handler_nodes, &track->list);

    rt_hw_spin_unlock(&_reboot_mode_lock.lock);

    return RT_EOK;
}

static rt_err_t dm_reboot_notifiy(struct rt_device *dev)
{
    struct reboot_mode_track *track;

    rt_hw_spin_lock(&_reboot_mode_lock.lock);

    rt_slist_for_each_entry(track, &_reboot_mode_handler_nodes, list)
    {
        rt_err_t err;
        struct rt_device *dev = track->dev;

        if ((err = track->callback(dev, _reboot_mode_cmd)))
        {
            LOG_E("%s: %s fail error = %s", dev ? rt_dm_dev_get_name(dev) : RT_NULL,
                "reboot mode apply", rt_strerror(err));
        }
    }

    rt_hw_spin_unlock(&_reboot_mode_lock.lock);

    return RT_EOK;
}

static int reboot_mode_init(void)
{
    return rt_dm_power_off_handler(RT_NULL, RT_DM_POWER_OFF_MODE_RESET,
                RT_DM_POWER_OFF_PRIO_HIGH, &dm_reboot_notifiy);
}
INIT_CORE_EXPORT(reboot_mode_init);

void rt_hw_cpu_reset_mode(char *cmd)
{
    static struct rt_spinlock pe_lock = {};

    rt_hw_spin_lock(&pe_lock.lock);

    _reboot_mode_cmd = cmd ? : _reboot_mode_cmd;

    rt_hw_cpu_reset();

    /* Unreachable */
    rt_hw_spin_unlock(&pe_lock.lock);
}

static void power_task_async(void (*fn)(void));

void rt_hw_cpu_shutdown(void)
{
    register rt_ubase_t level;

    if (rt_thread_self() && rt_interrupt_get_nest())
    {
        power_task_async(&rt_hw_cpu_shutdown);

        return;
    }

    dm_power_off_handler(RT_DM_POWER_OFF_MODE_SHUTDOWN);

    rt_bus_shutdown();

#ifdef RT_USING_PIC
    rt_pic_irq_finit();
#endif

    LOG_I("Shutdown");

    /* Machine shutdown */
    if (rt_dm_machine_shutdown)
    {
        rt_dm_machine_shutdown();
    }

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_shutdown, shutdown, shutdown machine);

void rt_hw_cpu_reset(void)
{
    register rt_ubase_t level;

    dm_power_off_handler(RT_DM_POWER_OFF_MODE_RESET);

    if (rt_thread_self() && rt_interrupt_get_nest())
    {
        power_task_async(&rt_hw_cpu_reset);

        return;
    }

    rt_bus_shutdown();

#ifdef RT_USING_PIC
    rt_pic_irq_finit();
#endif

    LOG_I("Reset");

    /* Machine reset */
    if (rt_dm_machine_reset)
    {
        rt_dm_machine_reset();
    }

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reset, reset machine);

static struct rt_thread power_task;

static void power_task_entry(void *arg)
{
    void (*fn)(void) = rt_thread_self()->parameter;

    fn();
}

static void power_task_async(void (*fn)(void))
{
    power_task.parameter = fn;

    rt_thread_startup(&power_task);
}

static int power_init(void)
{
    static rt_uint8_t power_task_stack[SYSTEM_THREAD_STACK_SIZE];

    return rt_thread_init(&power_task, "pwr", power_task_entry, RT_NULL,
            &power_task_stack, sizeof(power_task_stack),
            RT_THREAD_PRIORITY_MAX / 2, 32);
}
INIT_CORE_EXPORT(power_init);
