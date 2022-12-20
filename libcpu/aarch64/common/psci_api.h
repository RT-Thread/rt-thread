/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __PSCI_API_H__
#define __PSCI_API_H__

#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>
#include "psci_api.h"

/** generic psci ops supported v0.1 v0.2 v1.0 v1.1 */
struct psci_ops_t
{
    uint32_t (*get_version)(void);
    int32_t (*cpu_suspend)(uint32_t state, unsigned long entry_point);
    int32_t (*cpu_off)(uint32_t state);
    int32_t (*cpu_on)(unsigned long cpuid, unsigned long entry_point);
    int32_t (*migrate)(unsigned long cpuid);

    void (*system_off)(void);
    void (*system_reset)(void);
};

extern struct psci_ops_t psci_ops;

extern int psci_init(void);

#endif // __PSCI_API_H__
