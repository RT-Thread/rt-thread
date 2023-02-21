/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include "pmu.h"

#define DBG_TAG "PMU"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

void rt_hw_pmu_dump_feature(void)
{
    unsigned long reg;

    reg = rt_hw_pmu_get_control();
    LOG_D("ARM PMU Implementor: %c, ID code: %02x, %d counters\n",
        reg >> 24, (reg >> 16) & 0xff, (reg >> 11) & 0x1f);
    RT_ASSERT(ARM_PMU_CNTER_NR == ((reg >> 11) & 0x1f));
}
