/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include "pmu.h"

void rt_hw_pmu_dump_feature(void)
{
    unsigned long reg;

    reg = rt_hw_pmu_get_control();
    rt_kprintf("ARM PMU Implementor: %c, ID code: %02x, %d counters\n",
               reg >> 24, (reg >> 16) & 0xff, (reg >> 11) & 0x1f);
    RT_ASSERT(ARM_PMU_CNTER_NR == ((reg >> 11) & 0x1f));
}
