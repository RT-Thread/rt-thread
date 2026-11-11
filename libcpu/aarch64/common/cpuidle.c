/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <psci.h>

#define DBG_TAG "cpuidle"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct arm_cpuidle
{
    struct rt_dvfs_idle parent;
    struct rt_device device;

    rt_bool_t arch_timer_wakeup_source;
};

#if defined(RT_CLOCK_TIME_ARM_ARCH) || defined(RT_HWTIMER_ARM_ARCH)
#define ARM_CPUIDLE_ARCH_TIMER 1
#endif

#ifdef __GNUC__
__asm__ (
"asm_arm_cpuidle_entry:                 \n\t"
"   stp     x29, x30, [sp, #-0x20]!     \n\t"
"   stp     x19, x20, [sp, #0x10]       \n\t"
"   mov     x19, x0                     \n\t"
#ifdef ARM_CPUIDLE_ARCH_TIMER
"   bl      arm_arch_timer_local_disable\n\t"
#endif
"   mov     x0, x19                     \n\t"
"   mov     x1, xzr                     \n\t"
"   bl      rt_psci_cpu_suspend         \n\t"
"   mov     x20, x0                     \n\t"
#ifdef ARM_CPUIDLE_ARCH_TIMER
"   bl      arm_arch_timer_local_enable \n\t"
#endif
"   mov     x0, x20                     \n\t"
"   ldp     x19, x20, [sp, #0x10]       \n\t"
"   ldp     x29, x30, [sp], #0x20       \n\t"
"   ret                                 \n\t"
    );
#else
#error "No suspend context save"
#endif

extern rt_uint32_t asm_arm_cpuidle_entry(rt_uint32_t psci_param);

static rt_bool_t arm_cpuidle_state_loses_context(rt_uint32_t state)
{
    return PSCI_POWER_STATE_TYPE_VAL(state) == PSCI_POWER_STATE_TYPE_POWER_DOWN;
}

static rt_err_t arm_cpuidle_entry(struct rt_dvfs_idle *idle, struct rt_dvfs_idle_status *status)
{
    return asm_arm_cpuidle_entry((rt_ubase_t)status->priv) >= 0 ? RT_EOK : -RT_ENOSYS;
}

static rt_err_t arm_cpuidle_exit(struct rt_dvfs_idle *idle, struct rt_dvfs_idle_status *status)
{
    return RT_EOK;
}

static rt_bool_t arm_cpuidle_timer_can_stop(struct rt_dvfs_idle *idle)
{
    struct arm_cpuidle *cpuidle = rt_container_of(idle, struct arm_cpuidle, parent);

    return !cpuidle->arch_timer_wakeup_source;
}

static struct rt_dvfs_idle_ops arm_cpuidle_ops =
{
    .entry = arm_cpuidle_entry,
    .exit = arm_cpuidle_exit,
    .timer_can_stop = arm_cpuidle_timer_can_stop,
};

#ifdef ARM_CPUIDLE_ARCH_TIMER
static const struct rt_ofw_node_id arm_arch_timer_ofw_ids[] =
{
    { .compatible = "arm,armv7-timer", },
    { .compatible = "arm,armv8-timer", },
    { /* sentinel */ }
};
#endif

static void arm_cpuidle_status_free(struct rt_dvfs_idle *idle, struct rt_dvfs_idle_status *status)
{
    rt_free(status);
}

static int arm_cpuidle_probe(void)
{
    const char *entry_method;
    struct arm_cpuidle *cpuidle;
    struct rt_ofw_node *np, *child_np, *cpu_np;
    struct rt_dvfs_idle_status *status;
    rt_bool_t timer_wakeup = RT_FALSE;

    if (!(np = rt_ofw_find_node_by_path("/cpus/idle-states")))
    {
        return (int)-RT_ENOSYS;
    }

    if (rt_ofw_prop_read_string(np, "entry-method", &entry_method))
    {
        return (int)-RT_EINVAL;
    }

    if (rt_strcmp(entry_method, "psci") &&
        rt_strcmp(entry_method, "arm,psci"))
    {
        return (int)-RT_ENOSYS;
    }

#ifdef ARM_CPUIDLE_ARCH_TIMER
    /* Check arch timer wakeup source */
    struct rt_ofw_node *timer_np;
    if ((timer_np = rt_ofw_find_node_by_ids(RT_NULL, arm_arch_timer_ofw_ids)))
    {
        timer_wakeup = rt_ofw_prop_read_bool(timer_np, "wakeup-source");
        rt_ofw_node_put(timer_np);
    }
#endif

    /* Iterate over all CPUs and register idle devices */
    rt_ofw_foreach_cpu_node(cpu_np)
    {
        int cpu_id = rt_ofw_get_cpu_id(cpu_np);
        if (cpu_id < 0 || cpu_id >= RT_CPUS_NR)
        {
            continue;
        }

        if (!(cpuidle = rt_calloc(1, sizeof(*cpuidle))))
        {
            return (int)-RT_ENOMEM;
        }

        /* Parse idle states */
        rt_ofw_foreach_child_node(np, child_np)
        {
            rt_uint32_t psci_param;

            if (rt_ofw_prop_read_u32(child_np, "arm,psci-suspend-param", &psci_param))
            {
                psci_param = PSCI_POWER_STATE(
                        PSCI_POWER_STATE_LEVEL_CORES, PSCI_POWER_STATE_TYPE_STANDBY, 0);
            }

            if (arm_cpuidle_state_loses_context(psci_param))
            {
                LOG_W("skip power-down idle state on %s (context save not supported)",
                      rt_ofw_node_full_name(child_np));
                continue;
            }

            status = rt_calloc(1, sizeof(*status));

            if (!status)
            {
                rt_dvfs_idle_remove_status_all(&cpuidle->parent, arm_cpuidle_status_free);
                rt_free(cpuidle);
                return (int)-RT_ENOMEM;
            }

            rt_ofw_prop_read_u32(child_np, "entry-latency-us", &status->entry_latency_us);
            rt_ofw_prop_read_u32(child_np, "exit-latency-us", &status->exit_latency_us);
            rt_ofw_prop_read_u32(child_np, "min-residency-us", &status->min_residency_us);
            status->timer_stop = rt_ofw_prop_read_bool(child_np, "local-timer-stop");
            status->priv = (void *)(rt_ubase_t)psci_param;

            rt_dvfs_idle_add_status(&cpuidle->parent, status);
        }

        /* Check if any idle states were added */
        if (!cpuidle->parent.status_table || rt_list_isempty(&cpuidle->parent.status_table->status_nodes))
        {
            rt_free(cpuidle);
            continue;
        }

        cpuidle->device.ofw_node = cpu_np;
        cpuidle->parent.dev = &cpuidle->device;
        cpuidle->parent.ops = &arm_cpuidle_ops;
        cpuidle->arch_timer_wakeup_source = timer_wakeup;

        rt_dvfs_idle_register(&cpuidle->parent);
    }

    return RT_EOK;
}
INIT_PLATFORM_EXPORT(arm_cpuidle_probe);
