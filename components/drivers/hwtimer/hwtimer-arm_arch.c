/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-20     GuEe-GUI     first version
 * 2022-08-24     GuEe-GUI     Add OFW support
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

/* support registers access and timer registers in libcpu */
#include <cpu.h>
#include <cpuport.h>

typedef void (*timer_ctrl_handle)(rt_bool_t enable);
typedef rt_uint64_t (*timer_value_handle)(rt_uint64_t val);

static volatile rt_uint64_t timer_step;

static int arm_arch_timer_irq = -1;
static timer_ctrl_handle arm_arch_timer_ctrl_handle = RT_NULL;
static timer_value_handle arm_arch_timer_value_handle = RT_NULL;

/* CTL */
static void mon_ptimer_ctrl(rt_bool_t enable)
{
    rt_hw_sysreg_write(CNTPS_CTL, !!enable);
}

static void hyp_s_ptimer_ctrl(rt_bool_t enable)
{
#if ARCH_ARMV8_EXTENSIONS > 1
    rt_hw_sysreg_write(CNTHPS_CTL, !!enable);
#endif
}

static void hyp_ns_ptimer_ctrl(rt_bool_t enable)
{
    rt_hw_sysreg_write(CNTHP_CTL, !!enable);
}

static void hyp_s_vtimer_ctrl(rt_bool_t enable)
{
#if ARCH_ARMV8_EXTENSIONS > 1
    rt_hw_sysreg_write(CNTHVS_CTL, !!enable);
#endif
}

static void hyp_ns_vtimer_ctrl(rt_bool_t enable)
{
#if ARCH_ARMV8_EXTENSIONS > 1
    rt_hw_sysreg_write(CNTHV_CTL, !!enable);
#endif
}

static void os_ptimer_ctrl(rt_bool_t enable)
{
    rt_hw_sysreg_write(CNTP_CTL, !!enable);
}

static void os_vtimer_ctrl(rt_bool_t enable)
{
    rt_hw_sysreg_write(CNTV_CTL, !!enable);
}

/* TVAL */
static rt_uint64_t mon_ptimer_value(rt_uint64_t val)
{
    if (val)
    {
        rt_hw_sysreg_write(CNTPS_TVAL, val);
    }
    else
    {
        rt_hw_sysreg_read(CNTPS_TVAL, val);
    }

    return val;
}

static rt_uint64_t hyp_s_ptimer_value(rt_uint64_t val)
{
#if ARCH_ARMV8_EXTENSIONS > 1
    if (val)
    {
        rt_hw_sysreg_write(CNTHPS_TVAL, val);
    }
    else
    {
        rt_hw_sysreg_read(CNTHPS_TVAL, val);
    }

    return val;
#else
    return 0;
#endif
}

static rt_uint64_t hyp_ns_ptimer_value(rt_uint64_t val)
{
    if (val)
    {
        rt_hw_sysreg_write(CNTHP_TVAL, val);
    }
    else
    {
        rt_hw_sysreg_read(CNTHP_TVAL, val);
    }

    return val;
}

static rt_uint64_t hyp_s_vtimer_value(rt_uint64_t val)
{
#if ARCH_ARMV8_EXTENSIONS > 1
    if (val)
    {
        rt_hw_sysreg_write(CNTHVS_TVAL, val);
    }
    else
    {
        rt_hw_sysreg_read(CNTHVS_TVAL, val);
    }

    return val;
#else
    return 0;
#endif
}

static rt_uint64_t hyp_ns_vtimer_value(rt_uint64_t val)
{
#if ARCH_ARMV8_EXTENSIONS > 1
    if (val)
    {
        rt_hw_sysreg_write(CNTHV_TVAL, val);
    }
    else
    {
        rt_hw_sysreg_read(CNTHV_TVAL, val);
    }

    return val;
#else
    return 0;
#endif
}

static rt_uint64_t os_ptimer_value(rt_uint64_t val)
{
    if (val)
    {
        rt_hw_sysreg_write(CNTP_TVAL, val);
    }
    else
    {
        rt_hw_sysreg_read(CNTP_TVAL, val);
    }

    return val;
}

static rt_uint64_t os_vtimer_value(rt_uint64_t val)
{
    if (val)
    {
        rt_hw_sysreg_write(CNTV_TVAL, val);
    }
    else
    {
        rt_hw_sysreg_read(CNTV_TVAL, val);
    }

    return val;
}

static timer_ctrl_handle ctrl_handle[] =
{
    mon_ptimer_ctrl,
    hyp_s_ptimer_ctrl,
    hyp_ns_ptimer_ctrl,
    hyp_s_vtimer_ctrl,
    hyp_ns_vtimer_ctrl,
    os_ptimer_ctrl,
    os_vtimer_ctrl,
};

static timer_value_handle value_handle[] =
{
    mon_ptimer_value,
    hyp_s_ptimer_value,
    hyp_ns_ptimer_value,
    hyp_s_vtimer_value,
    hyp_ns_vtimer_value,
    os_ptimer_value,
    os_vtimer_value,
};

static rt_err_t arm_arch_timer_local_enable(void)
{
    rt_err_t ret = RT_EOK;

    if (arm_arch_timer_irq >= 0)
    {
        arm_arch_timer_ctrl_handle(RT_FALSE);
        arm_arch_timer_value_handle(timer_step);

        rt_hw_interrupt_umask(arm_arch_timer_irq);

        arm_arch_timer_ctrl_handle(RT_TRUE);
    }
    else
    {
        ret = -RT_ENOSYS;
    }

    return ret;
}

rt_used
static rt_err_t arm_arch_timer_local_disable(void)
{
    rt_err_t ret = RT_EOK;

    if (arm_arch_timer_ctrl_handle)
    {
        arm_arch_timer_ctrl_handle(RT_FALSE);
        rt_hw_interrupt_mask(arm_arch_timer_irq);
    }
    else
    {
        ret = -RT_ENOSYS;
    }

    return ret;
}

rt_used
static rt_err_t arm_arch_timer_set_frequency(rt_uint64_t frq)
{
    rt_err_t ret = RT_EOK;

#ifdef ARCH_SUPPORT_TEE
    rt_hw_isb();
    rt_hw_sysreg_write(CNTFRQ, frq);
    rt_hw_dsb();
#else
    ret = -RT_ENOSYS;
#endif

    return ret;
}

rt_used
static rt_uint64_t arm_arch_timer_get_frequency(void)
{
    rt_uint64_t frq;

    rt_hw_isb();
    rt_hw_sysreg_read(CNTFRQ, frq);
    rt_hw_isb();

    return frq;
}

rt_used
static rt_err_t arm_arch_timer_set_value(rt_uint64_t val)
{
    rt_err_t ret = RT_EOK;

    if (arm_arch_timer_value_handle)
    {
        val = arm_arch_timer_value_handle(val);
    }
    else
    {
        ret = -RT_ENOSYS;
    }

    return ret;
}

rt_used
static rt_uint64_t arm_arch_timer_get_value(void)
{
    rt_uint64_t val = 0;

    if (arm_arch_timer_value_handle)
    {
        val = arm_arch_timer_value_handle(0);
    }

    return val;
}

static void arm_arch_timer_isr(int vector, void *param)
{
    arm_arch_timer_set_value(timer_step);

    rt_tick_increase();
}

static int arm_arch_timer_post_init(void)
{
    arm_arch_timer_local_enable();

    return 0;
}
INIT_SECONDARY_CPU_EXPORT(arm_arch_timer_post_init);

static rt_err_t arm_arch_timer_probe(struct rt_platform_device *pdev)
{
    int mode_idx, irq_idx;
    const char *irq_name[] =
    {
        "phys",     /* Secure Phys IRQ */
        "virt",     /* Non-secure Phys IRQ */
        "hyp-phys", /* Virt IRQ */
        "hyp-virt", /* Hyp IRQ */
    };

#if defined(ARCH_SUPPORT_TEE)
    mode_idx = 0;
    irq_idx = 0;
#elif defined(ARCH_SUPPORT_HYP)
    mode_idx = 2;
    irq_idx = 3;
#else
    mode_idx = 5;
    irq_idx = 1;
#endif

    arm_arch_timer_irq = rt_dm_dev_get_irq_by_name(&pdev->parent, irq_name[irq_idx]);

    if (arm_arch_timer_irq < 0)
    {
        arm_arch_timer_irq = rt_dm_dev_get_irq(&pdev->parent, irq_idx);
    }

    if (arm_arch_timer_irq < 0)
    {
        return -RT_EEMPTY;
    }

    arm_arch_timer_ctrl_handle = ctrl_handle[mode_idx];
    arm_arch_timer_value_handle = value_handle[mode_idx];

    rt_hw_interrupt_install(arm_arch_timer_irq, arm_arch_timer_isr, RT_NULL, "tick-arm-timer");

    timer_step = arm_arch_timer_get_frequency() / RT_TICK_PER_SECOND;

    arm_arch_timer_local_enable();

    return RT_EOK;
}

static const struct rt_ofw_node_id arm_arch_timer_ofw_ids[] =
{
    { .compatible = "arm,armv7-timer", },
    { .compatible = "arm,armv8-timer", },
    { /* sentinel */ }
};

static struct rt_platform_driver arm_arch_timer_driver =
{
    .name = "arm-arch-timer",
    .ids = arm_arch_timer_ofw_ids,

    .probe = arm_arch_timer_probe,
};

static int arm_arch_timer_drv_register(void)
{
    rt_platform_driver_register(&arm_arch_timer_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(arm_arch_timer_drv_register);
