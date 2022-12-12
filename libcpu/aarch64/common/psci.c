/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     GuEe-GUI     The first version
 */

#include <psci.h>
#include <smccc.h>
#include <armv8.h>

typedef uint64_t (*psci_call_handle)(uint32_t fn, uint64_t arg0, uint64_t arg1, uint64_t arg2);

static uint64_t psci_smc_call(uint32_t fn, uint64_t arg0, uint64_t arg1, uint64_t arg2)
{
    return arm_smc_call(fn, arg0, arg1, arg2, 0, 0, 0, 0).x0;
}

static uint64_t psci_hvc_call(uint32_t fn, uint64_t arg0, uint64_t arg1, uint64_t arg2)
{
    return arm_hvc_call(fn, arg0, arg1, arg2, 0, 0, 0, 0).x0;
}

static psci_call_handle psci_call = psci_smc_call;

static uint64_t shutdown_args[3] = {0, 0, 0};
static uint64_t reboot_args[3] = {0, 0, 0};

void arm_psci_init(uint64_t method, uint64_t *platform_shutdown_args, uint64_t *platform_reboot_args)
{
    switch (method)
    {
    case PSCI_METHOD_SMC:
        psci_call = psci_smc_call;
        break;
    case PSCI_METHOD_HVC:
        if (rt_hw_get_current_el() < 2)
        {
            psci_call = psci_hvc_call;
        }
        break;
    }

    if (platform_shutdown_args != RT_NULL)
    {
        shutdown_args[0] = platform_shutdown_args[0];
        shutdown_args[1] = platform_shutdown_args[1];
        shutdown_args[2] = platform_shutdown_args[2];
    }

    if (platform_reboot_args != RT_NULL)
    {
        reboot_args[0] = platform_reboot_args[0];
        reboot_args[1] = platform_reboot_args[1];
        reboot_args[2] = platform_reboot_args[2];
    }
}

uint32_t arm_psci_get_version()
{
    return (uint32_t)psci_call(PSCI_0_2_FN_PSCI_VERSION, 0, 0, 0);
}

uint32_t arm_psci_get_affinity_info(uint64_t target_affinity, uint64_t lowest_affinity_level)
{
    return (uint32_t)psci_call(PSCI_0_2_FN_AFFINITY_INFO, target_affinity, lowest_affinity_level, 0);
}

uint32_t arm_psci_get_feature(uint32_t psci_func_id)
{
    return (uint32_t)psci_call(PSCI_1_0_FN_PSCI_FEATURES, psci_func_id, 0, 0);
}

uint32_t arm_psci_cpu_off(uint64_t state)
{
    return (uint32_t)psci_call(PSCI_0_2_FN_CPU_OFF, state, 0, 0);
}

uint32_t arm_psci_cpu_on(uint64_t mpid, uint64_t entry)
{
    /* [40:63] and [24:31] must be zero, other is aff3, aff2, aff1, aff0 */
    mpid = mpid & 0xff00ffffff;

    return (uint32_t)psci_call(PSCI_0_2_FN_CPU_ON, mpid, entry, 0);
}

uint32_t arm_psci_cpu_suspend(uint32_t power_state, uint64_t entry)
{
    return (uint32_t)psci_call(PSCI_0_2_FN_CPU_SUSPEND, power_state, entry, 0);
}

void arm_psci_system_off()
{
    psci_call(PSCI_0_2_FN_SYSTEM_OFF, shutdown_args[0], shutdown_args[1], shutdown_args[2]);
}

void arm_psci_system_reboot()
{
    psci_call(PSCI_0_2_FN_SYSTEM_RESET, reboot_args[0], reboot_args[1], reboot_args[2]);
}
