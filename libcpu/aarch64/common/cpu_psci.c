/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#ifdef RT_USING_SMP

#define DBG_TAG "libcpu.aarch64.cpu_psci"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
#include "cpu_ops_common.h"

#include "cpu.h"
#include "errno.h"
#include "psci.h"
#include "psci_api.h"

static int (*_psci_init)(void) = psci_init;

static int __call_method_init()
{
    int (*init)(void) = _psci_init;
    _psci_init = RT_NULL;

    return init();
}

/** return 0 on success, otherwise failed */
#define _call_method_init() ((_psci_init) ? __call_method_init() : 0);

static int cpu_psci_cpu_init(rt_uint32_t cpuid)
{
    // init psci only once
    return _call_method_init();
}

static int cpu_psci_cpu_boot(rt_uint32_t cpuid)
{
    rt_uint64_t secondary_entry_pa = get_secondary_entry_pa();

    if (!secondary_entry_pa)
        return -1;

    if (!psci_ops.cpu_on) {
        LOG_E("Uninitialized psci operation");
        return -1;
    }
    return psci_ops.cpu_on(cpuid_to_hwid(cpuid), secondary_entry_pa);
}

static void cpu_psci_cpu_shutdown()
{
    psci_ops.cpu_off(cpuid_to_hwid(rt_hw_cpu_id()));
}

struct cpu_ops_t cpu_ops_psci = {
    .method = "psci",
    .cpu_boot = cpu_psci_cpu_boot,
    .cpu_init = cpu_psci_cpu_init,
    .cpu_shutdown = cpu_psci_cpu_shutdown,
};

#endif /* RT_USING_SMP */