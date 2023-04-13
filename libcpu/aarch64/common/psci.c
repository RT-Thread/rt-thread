/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "cpu.h"
#include "psci.h"
#include "psci_api.h"
#include "smccc.h"

#define DBG_TAG "libcpu.aarch64.psci"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/** template for creating 4 PSCI ops: SUSPEND, OFF, ON, MIGRATE */
#define COMMON_PSCI_OPS_TEMPLATE(VER, SUSPEND, OFF, ON, MIGRATE)                   \
    static int psci_##VER##_cpu_suspend(uint32_t state, unsigned long entry_point) \
    {                                                                              \
        return psci_call((SUSPEND), state, entry_point, 0);                        \
    }                                                                              \
    static int psci_##VER##_cpu_off(uint32_t state)                                \
    {                                                                              \
        return psci_call((OFF), state, 0, 0);                                      \
    }                                                                              \
    static int psci_##VER##_cpu_on(unsigned long cpuid, unsigned long entry_point) \
    {                                                                              \
        return psci_call((ON), cpuid, entry_point, 0);                             \
    }                                                                              \
    static int psci_##VER##_migrate(unsigned long cpuid)                           \
    {                                                                              \
        return psci_call((MIGRATE), cpuid, 0, 0);                                  \
    }

struct psci_ops_t psci_ops;

#ifdef RT_USING_FDT
#include "dtb_node.h"

#if __SIZE_WIDTH__ == 64
#define PSCI_FN_NATIVE(version, name) PSCI_##version##_FN64_##name
#else
#define PSCI_FN_NATIVE(version, name) PSCI_##version##_FN_##name
#endif

/**
 * SMCCC can use either smc or hvc method
 * smccc_call will be init to proper interface when psci_init() was executed
 */
static void (*smccc_call)(unsigned long a0, unsigned long a1, unsigned long a2,
                          unsigned long a3, unsigned long a4, unsigned long a5,
                          unsigned long a6, unsigned long a7, struct arm_smccc_res_t *res,
                          struct arm_smccc_quirk_t *quirk);

static rt_uint32_t psci_call(unsigned long a0, unsigned long a1, unsigned long a2, unsigned long a3)
{
    struct arm_smccc_res_t res;
    smccc_call(a0, a1, a2, a3, 0, 0, 0, 0, &res, (void *)0);
    return res.a0;
}

static int _psci_probe_version(char *version, int *major, int *minor);
static int _psci_init_with_version(int major, int minor);

static struct dtb_node *psci_node;

static int psci_ver_major;
static int psci_ver_minor;

/**
 * @brief init psci operations.
 * using device tree to probe version and psci-method,
 * setup psci ops for future use
 *
 * @return int 0 on success
 */
int psci_init()
{
    void *root = get_dtb_node_head();
    psci_node = dtb_node_get_dtb_node_by_path(root, "/psci");
    if (!psci_node)
    {
        LOG_E("No PSCI node found");
        return -1;
    }
    char *compatible = dtb_node_get_dtb_node_property_value(psci_node, "compatible", NULL);
    char *method = dtb_node_get_dtb_node_property_value(psci_node, "method", NULL);

    int retval = 0;

    // setup psci-method
    if (!strcmp("hvc", method))
    {
        smccc_call = arm_smccc_hvc;
    }
    else if (!strcmp("smc", method))
    {
        smccc_call = arm_smccc_smc;
    }
    else
    {
        LOG_E("Unknown PSCI method: %s", method);
        return -1;
    }
    LOG_D("Using psci method %s", method);

    retval = _psci_probe_version(compatible, &psci_ver_major, &psci_ver_minor);
    if (retval != 0)
        return retval;

    // init psci_ops with specified psci version
    retval = _psci_init_with_version(psci_ver_major, psci_ver_minor);

    return retval;
}

/* function id of PSCI v0.1 should be probed in FDT, they are implementation defined value */
static rt_uint32_t cpu_suspend_0_1;
static rt_uint32_t cpu_off_0_1;
static rt_uint32_t cpu_on_0_1;
static rt_uint32_t migrate_0_1;

/* basic operations TEMPLATE for API since 0.1 version */
COMMON_PSCI_OPS_TEMPLATE(0_1, cpu_suspend_0_1, cpu_off_0_1, cpu_on_0_1, migrate_0_1);

/* used for v0.1 only, rely on FDT to probe function id */
#define PROBE_AND_SET(FUNC_NAME)                                                       \
    do                                                                                 \
    {                                                                                  \
        int num_of_elem;                                                               \
        funcid =                                                                       \
            dtb_node_get_dtb_node_property_value(psci_node, #FUNC_NAME, &num_of_elem); \
        if (num_of_elem != 4 || funcid == 0 || *funcid == 0)                           \
        {                                                                              \
            LOG_E("Failed to probe " #FUNC_NAME " in FDT");                            \
        }                                                                              \
        else                                                                           \
        {                                                                              \
            FUNC_NAME##_0_1 = (rt_uint32_t)fdt32_to_cpu(*funcid);                      \
            psci_ops.FUNC_NAME = psci_0_1_##FUNC_NAME;                                 \
        }                                                                              \
    } while (0)

static int psci_0_1_init()
{
    // reading function id from fdt
    rt_uint32_t *funcid;
    PROBE_AND_SET(cpu_suspend);
    PROBE_AND_SET(cpu_off);
    PROBE_AND_SET(cpu_on);
    PROBE_AND_SET(migrate);
    return 0;
}

COMMON_PSCI_OPS_TEMPLATE(0_2, PSCI_FN_NATIVE(0_2, CPU_SUSPEND), PSCI_0_2_FN_CPU_OFF, PSCI_FN_NATIVE(0_2, CPU_ON), PSCI_FN_NATIVE(0_2, MIGRATE));

static rt_uint32_t psci_0_2_get_version(void)
{
    return psci_call(PSCI_0_2_FN_PSCI_VERSION, 0, 0, 0);
}

static void psci_0_2_set_basic_ops()
{
    psci_ops = (struct psci_ops_t){
        .get_version = psci_0_2_get_version,

        // followings API are v0.1 compatible
        .cpu_suspend = psci_0_2_cpu_suspend,
        .cpu_off = psci_0_2_cpu_off,
        .cpu_on = psci_0_2_cpu_on,
        .migrate = psci_0_2_migrate,
    };
}

static void psci_0_2_system_off(void)
{
    psci_call(PSCI_0_2_FN_SYSTEM_OFF, 0, 0, 0);
}

static void psci_0_2_system_reset(void)
{
    psci_call(PSCI_0_2_FN_SYSTEM_RESET, 0, 0, 0);
}

static int psci_0_2_init()
{
    psci_0_2_set_basic_ops();

    // TODO init other version 0.2 features...
    // psci system off and reset which controlling machine
    psci_ops.system_off = psci_0_2_system_off;
    psci_ops.system_reset = psci_0_2_system_reset;

    system_off = psci_0_2_system_off;
    return 0;
}

/* PSCI v1.0 & after */
static int psci_1_0_features(uint32_t psci_func_id)
{
    return psci_call(PSCI_1_0_FN_PSCI_FEATURES,
                     psci_func_id, 0, 0);
}

static int psci_1_0_init()
{
    psci_0_2_init();

    // TODO init other version 1.0 features...
    // remove unsupported features
    if (psci_1_0_features(PSCI_0_2_FN_SYSTEM_OFF) == PSCI_RET_NOT_SUPPORTED)
    {
        psci_ops.system_off = RT_NULL;
        system_off = RT_NULL;
    }
    else
        LOG_D("Using SYSTEM OFF feature");
    if (psci_1_0_features(PSCI_0_2_FN_SYSTEM_RESET) == PSCI_RET_NOT_SUPPORTED)
        psci_ops.system_reset = RT_NULL;
    else
        LOG_D("Using SYSTEM RESET feature");

    return 0;
}

/* probe psci version from fdt or SMC call */
static int _psci_probe_version(char *version, int *major, int *minor)
{
    int retval = 0;
    // if strcmp compatible 'arm,psci-0.1'
    if (!strcmp(version, "arm,psci"))
    {
        *major = 0;
        *minor = 1;
    }
    else if (!strncmp(version, "arm,psci-", 8))
    {
        // since psci-0.2, using psci call to probe version
        rt_uint32_t ret = psci_0_2_get_version();
        *major = PSCI_VERSION_MAJOR(ret);
        *minor = PSCI_VERSION_MINOR(ret);
    }
    else
    {
        LOG_E("[%s] was not a proper PSCI version", version);
        retval = -1;
    }
    LOG_D("Using PSCI v%d.%d", *major, *minor);
    return retval;
}

/* init psci ops with version info */
static int _psci_init_with_version(int major, int minor)
{
    int retval = -0xbeef; // mark unsupported
    if (major == 0)
    {
        // for v0.1, psci function id was provided fdt
        if (minor == 1)
        {
            retval = psci_0_1_init();
        }
        else if (minor == 2)
        {
            retval = psci_0_2_init();
        }
    }
    else if (major == 1)
    {
        // psci_1_0_init is a base setup for version after v1.0
        retval = psci_1_0_init();
    }

    if (retval == -0xbeef)
    {
        LOG_E("PSCI init with incompatible version %d.%d", major, minor);
    }
    return retval;
}

#endif /* RT_USING_FDT */