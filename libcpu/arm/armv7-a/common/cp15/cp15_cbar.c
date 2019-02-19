/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include "cp15.h"
#include <rtthread.h>

/*
 * CBAR, Configuration Base Address Register
 * [ref]DDI0388I_cortex_a9_r4p1_trm.pdf: 4.3.24 Configuration Base Address Register
 *      Bit     Field               Description                                     cortex-a9               cortex-a8
 *      31-0    Base address        Indicates the implementor.                      supported
 *      MRC p15, 4, <Rd>, c15, c0, 0; Read Configuration Base Address Register
 *      MCR p15, 4, <Rd>, c15, c0, 0; Write Configuration Base Address Register
 */
#define _ARM_CP_CBAR_R(cbar)    _ARM_CP_R(p15, 4, cbar, c15, c0, 0)
uint32_t rt_cpu_cbar_get(void)
{
    RT_ASSERT(armv7_get_cortex_type() == CORTEX_TYPE_A9);
    uint32_t cbar;
    _ARM_CP_CBAR_R(cbar);
    return cbar;
}

