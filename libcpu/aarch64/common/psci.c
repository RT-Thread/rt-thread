/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     GuEe-GUI     The first version
 * 2022-09-24     GuEe-GUI     Add operations and fdt init support
 */

#include <rtthread.h>

#define DBG_TAG "osi.psci"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* support cpu mpidr and smccc from libcpu */
#include <cpu.h>
#include <smccc.h>
#include <psci.h>
#include <drivers/ofw.h>
#include <drivers/platform.h>
#include <drivers/core/dm.h>

struct psci_ops
{
    rt_uint32_t (*get_version)(void);
    rt_uint32_t (*cpu_on)(int cpuid, rt_ubase_t entry_point);
    rt_uint32_t (*cpu_off)(rt_uint32_t state);
    rt_uint32_t (*cpu_suspend)(rt_uint32_t power_state, rt_ubase_t entry_point);
    rt_uint32_t (*migrate)(int cpuid);
    rt_uint32_t (*get_affinity_info)(rt_ubase_t target_affinity, rt_ubase_t lowest_affinity_level);
    rt_uint32_t (*migrate_info_type)(void);
};

struct psci_0_1_func_ids
{
    rt_uint32_t cpu_on;
    rt_uint32_t cpu_off;
    rt_uint32_t cpu_suspend;
    rt_uint32_t migrate;
};

typedef rt_err_t (*psci_init_ofw_handle)(struct rt_ofw_node *np);
typedef rt_ubase_t (*psci_call_handle)(rt_uint32_t fn, rt_ubase_t arg0, rt_ubase_t arg1, rt_ubase_t arg2);

/* [40:63] and [24:31] must be zero, other is aff3 (64bit), aff2, aff1, aff0 */
#ifdef ARCH_CPU_64BIT
#define PSCI_FNC_ID(version_major, version_min, name)   PSCI_##version_major##_##version_min##_FN64_##name
#define MPIDR_MASK 0xff00ffffff
#else
#define PSCI_FNC_ID(version_major, version_min, name)   PSCI_##version_major##_##version_min##_FN_##name
#define MPIDR_MASK 0x00ffffff
#endif

static struct psci_ops _psci_ops = {};

static struct psci_0_1_func_ids psci_0_1_func_ids = {};
static psci_call_handle psci_call;

/* PSCI SMCCC */
static rt_ubase_t psci_smc_call(rt_uint32_t fn, rt_ubase_t arg0, rt_ubase_t arg1, rt_ubase_t arg2)
{
    struct arm_smccc_res_t res;

    arm_smccc_smc(fn, arg0, arg1, arg2, 0, 0, 0, 0, &res, RT_NULL);

    return res.a0;
}

static rt_ubase_t psci_hvc_call(rt_uint32_t fn, rt_ubase_t arg0, rt_ubase_t arg1, rt_ubase_t arg2)
{
    struct arm_smccc_res_t res;

    arm_smccc_hvc(fn, arg0, arg1, arg2, 0, 0, 0, 0, &res, RT_NULL);

    return res.a0;
}

/* PSCI VERSION */
static rt_uint32_t psci_0_1_get_version(void)
{
    return PSCI_VERSION(0, 1);
}

static rt_uint32_t psci_0_2_get_version(void)
{
    return (rt_uint32_t)psci_call(PSCI_0_2_FN_PSCI_VERSION, 0, 0, 0);
}

/* PSCI FEATURES */
static rt_uint32_t psci_get_features(rt_uint32_t psci_func_id)
{
    return (rt_uint32_t)psci_call(PSCI_1_0_FN_PSCI_FEATURES, psci_func_id, 0, 0);
}

/* PSCI CPU_ON */
static rt_uint32_t psci_cpu_on(rt_uint32_t func_id, int cpuid, rt_ubase_t entry_point)
{
    rt_uint32_t ret = -PSCI_RET_INVALID_PARAMETERS;

    if (cpuid < RT_CPUS_NR)
    {
        rt_ubase_t mpid = rt_cpu_mpidr_table[cpuid] & MPIDR_MASK;

        ret = (rt_uint32_t)psci_call(func_id, mpid, entry_point, 0);
    }

    return ret;
}

static rt_uint32_t psci_0_1_cpu_on(int cpuid, rt_ubase_t entry_point)
{
    return psci_cpu_on(psci_0_1_func_ids.cpu_on, cpuid, entry_point);
}

static rt_uint32_t psci_0_2_cpu_on(int cpuid, rt_ubase_t entry_point)
{
    return psci_cpu_on(PSCI_FNC_ID(0, 2, CPU_ON), cpuid, entry_point);
}

/* PSCI CPU_OFF */
static rt_uint32_t psci_cpu_off(rt_uint32_t func_id, rt_uint32_t state)
{
    return (rt_uint32_t)psci_call(func_id, state, 0, 0);
}

static rt_uint32_t psci_0_1_cpu_off(rt_uint32_t state)
{
    return psci_cpu_off(psci_0_1_func_ids.cpu_off, state);
}

static rt_uint32_t psci_0_2_cpu_off(rt_uint32_t state)
{
    return psci_cpu_off(PSCI_0_2_FN_CPU_OFF, state);
}

/* PSCI CPU_SUSPEND */
static rt_uint32_t psci_cpu_suspend(rt_uint32_t func_id, rt_uint32_t power_state, rt_ubase_t entry_point)
{
    return (rt_uint32_t)psci_call(func_id, power_state, entry_point, 0);
}

static rt_uint32_t psci_0_1_cpu_suspend(rt_uint32_t power_state, rt_ubase_t entry_point)
{
    return psci_cpu_suspend(psci_0_1_func_ids.cpu_suspend, power_state, entry_point);
}

static rt_uint32_t psci_0_2_cpu_suspend(rt_uint32_t power_state, rt_ubase_t entry_point)
{
    return psci_cpu_suspend(PSCI_FNC_ID(0, 2, CPU_SUSPEND), power_state, entry_point);
}

/* PSCI CPU_MIGRATE */
static rt_uint32_t psci_migrate(rt_uint32_t func_id, int cpuid)
{
    rt_uint32_t ret = -PSCI_RET_INVALID_PARAMETERS;

    if (cpuid < RT_CPUS_NR)
    {
        rt_ubase_t mpid = rt_cpu_mpidr_table[cpuid] & MPIDR_MASK;

        ret = (rt_uint32_t)psci_call(func_id, mpid, 0, 0);
    }

    return ret;
}

static rt_uint32_t psci_0_1_migrate(int cpuid)
{
    return psci_migrate(psci_0_1_func_ids.migrate, cpuid);
}

static rt_uint32_t psci_0_2_migrate(int cpuid)
{
    return psci_migrate(PSCI_FNC_ID(0, 2, MIGRATE), cpuid);
}

/* PSCI AFFINITY_INFO */
static rt_uint32_t psci_affinity_info(rt_ubase_t target_affinity, rt_ubase_t lowest_affinity_level)
{
    return (rt_uint32_t)psci_call(PSCI_FNC_ID(0, 2, AFFINITY_INFO), target_affinity, lowest_affinity_level, 0);
}

/* PSCI MIGRATE_INFO_TYPE */
static rt_uint32_t psci_migrate_info_type(void)
{
    return (rt_uint32_t)psci_call(PSCI_0_2_FN_MIGRATE_INFO_TYPE, 0, 0, 0);
}

/* PSCI SYSTEM_OFF */
void psci_system_off(void)
{
    psci_call(PSCI_0_2_FN_SYSTEM_OFF, 0, 0, 0);
}

/* PSCI SYSTEM_RESET */
void psci_system_reboot(void)
{
    if (psci_get_features(PSCI_FNC_ID(1, 1, SYSTEM_RESET2)) != PSCI_RET_NOT_SUPPORTED)
    {
        /*
         * reset_type[31] = 0 (architectural)
         * reset_type[30:0] = 0 (SYSTEM_WARM_RESET)
         * cookie = 0 (ignored by the implementation)
         */
        psci_call(PSCI_FNC_ID(1, 1, SYSTEM_RESET2), 0, 0, 0);
    }
    else
    {
        psci_call(PSCI_0_2_FN_SYSTEM_RESET, 0, 0, 0);
    }

}

#define PSCI_CALL_FN_RET(fn, ...)       \
({                                      \
    rt_uint32_t rc;                     \
    rc = PSCI_RET_NOT_SUPPORTED;        \
    if (_psci_ops.fn)                   \
        rc = _psci_ops.fn(__VA_ARGS__); \
    rc;                                 \
})

#define PSCI_CALL_FN(fn, ...)       \
({                                  \
    if (_psci_ops.fn)               \
        _psci_ops.fn(__VA_ARGS__);  \
})

rt_uint32_t rt_psci_get_version(void)
{
    return PSCI_CALL_FN_RET(get_version);
}

rt_uint32_t rt_psci_cpu_on(int cpuid, rt_ubase_t entry_point)
{
    return PSCI_CALL_FN_RET(cpu_on, cpuid, entry_point);
}

rt_uint32_t rt_psci_cpu_off(rt_uint32_t state)
{
    return PSCI_CALL_FN_RET(cpu_off, state);
}

rt_uint32_t rt_psci_cpu_suspend(rt_uint32_t power_state, rt_ubase_t entry_point)
{
    return PSCI_CALL_FN_RET(cpu_suspend, power_state, entry_point);
}

rt_uint32_t rt_psci_migrate(int cpuid)
{
    return PSCI_CALL_FN_RET(migrate, cpuid);
}

rt_uint32_t rt_psci_get_affinity_info(rt_ubase_t target_affinity, rt_ubase_t lowest_affinity_level)
{
    return PSCI_CALL_FN_RET(get_affinity_info, target_affinity, lowest_affinity_level);
}

rt_uint32_t rt_psci_migrate_info_type(void)
{
    return PSCI_CALL_FN_RET(migrate_info_type);
}

#undef PSCI_CALL_FN_RET
#undef PSCI_CALL_FN

/* PSCI INIT */
static rt_err_t psci_0_1_init(struct rt_ofw_node *np)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t func_id;

    _psci_ops.get_version = psci_0_1_get_version;

    if (!rt_ofw_prop_read_u32(np, "cpu_on", &func_id))
    {
        psci_0_1_func_ids.cpu_on = func_id;
        _psci_ops.cpu_on = psci_0_1_cpu_on;
    }

    if (!rt_ofw_prop_read_u32(np, "cpu_off", &func_id))
    {
        psci_0_1_func_ids.cpu_off = func_id;
        _psci_ops.cpu_off = psci_0_1_cpu_off;
    }

    if (!rt_ofw_prop_read_u32(np, "cpu_suspend", &func_id))
    {
        psci_0_1_func_ids.cpu_suspend = func_id;
        _psci_ops.cpu_suspend = psci_0_1_cpu_suspend;
    }

    if (!rt_ofw_prop_read_u32(np, "migrate", &func_id))
    {
        psci_0_1_func_ids.migrate = func_id;
        _psci_ops.migrate = psci_0_1_migrate;
    }

    return err;
}

static rt_err_t psci_0_2_init(struct rt_ofw_node *np)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t version = psci_0_2_get_version();

    if (version >= PSCI_VERSION(0, 2))
    {
        _psci_ops.get_version       = psci_0_2_get_version;
        _psci_ops.cpu_on            = psci_0_2_cpu_on;
        _psci_ops.cpu_off           = psci_0_2_cpu_off;
        _psci_ops.cpu_suspend       = psci_0_2_cpu_suspend;
        _psci_ops.migrate           = psci_0_2_migrate;
        _psci_ops.get_affinity_info = psci_affinity_info;
        _psci_ops.migrate_info_type = psci_migrate_info_type;
    }
    else
    {
        LOG_E("PSCI version detected");
        err = -RT_EINVAL;
    }

    return err;
}

static rt_err_t psci_1_0_init(struct rt_ofw_node *np)
{
    rt_err_t err;

    err = psci_0_2_init(np);

    return err;
}

static rt_err_t psci_ofw_init(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    const char *method;
    const struct rt_ofw_node_id *id = pdev->id;
    struct rt_ofw_node *np = pdev->parent.ofw_node;

    if (!rt_ofw_prop_read_string(np, "method", &method))
    {
        if (!rt_strcmp(method, "smc"))
        {
            psci_call = psci_smc_call;
        }
        else if (!rt_strcmp(method, "hvc"))
        {
            psci_call = psci_hvc_call;
        }
        else
        {
            LOG_E("Invalid \"method\" property: %s", method);
            err = -RT_EINVAL;
        }

        if (!err)
        {
            psci_init_ofw_handle psci_init = (psci_init_ofw_handle)id->data;

            err = psci_init(np);

            if (!err)
            {
                rt_uint32_t version = rt_psci_get_version();

                rt_ofw_data(np) = &_psci_ops;

                RT_UNUSED(version);

                LOG_I("Using PSCI v%d.%d Function IDs", PSCI_VERSION_MAJOR(version), PSCI_VERSION_MINOR(version));
            }
        }
    }
    else
    {
        err = -RT_ENOSYS;
    }

    return err;
}

static rt_err_t psci_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;

    err = psci_ofw_init(pdev);

    return err;
}

static const struct rt_ofw_node_id psci_ofw_ids[] =
{
    { .compatible = "arm,psci",     .data = psci_0_1_init },
    { .compatible = "arm,psci-0.2", .data = psci_0_2_init },
    { .compatible = "arm,psci-1.0", .data = psci_1_0_init },
    { /* sentinel */ }
};

static struct rt_platform_driver psci_driver =
{
    .name = "arm-psci",
    .ids = psci_ofw_ids,

    .probe = psci_probe,
};

static int psci_drv_register(void)
{
    rt_platform_driver_register(&psci_driver);

    return 0;
}
INIT_PLATFORM_EXPORT(psci_drv_register);
