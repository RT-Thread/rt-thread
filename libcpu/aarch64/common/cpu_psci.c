/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-21     GuEe-GUI     replace with drivers/psci
 */
#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG "cpu.aa64"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpu.h>
#include <cpuport.h>

#ifdef RT_FIRMWARE_PSCI
#include <drivers/psci.h>

static int psci_cpu_boot(rt_uint32_t cpuid, rt_uint64_t entry)
{
    return rt_psci_cpu_on(cpuid, entry);
}

static void psci_cpu_shutdown(void)
{
    rt_uint32_t state, state_id = PSCI_POWER_STATE_ID(0, 0, 0, PSCI_POWER_STATE_ID_POWERDOWN);

    state = PSCI_POWER_STATE(PSCI_POWER_STATE_LEVEL_CORES, PSCI_POWER_STATE_TYPE_STANDBY, state_id);

    rt_psci_cpu_off(state);
}
#endif /* RT_FIRMWARE_PSCI */

struct cpu_ops_t cpu_psci_ops =
{
#ifdef RT_FIRMWARE_PSCI
    .method = "psci",
    .cpu_boot = psci_cpu_boot,
    .cpu_shutdown = psci_cpu_shutdown,
#endif /* RT_FIRMWARE_PSCI */
};
