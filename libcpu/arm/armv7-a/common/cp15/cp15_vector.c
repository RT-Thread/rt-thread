/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include "cp15.h"

/*
 * VBAR, Vector Base Address Register
 * [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.156 VBAR, Vector Base Address Register, Security Extensions
 *      Bit     Field                   Description
 *      31-5    Vector base address     Holds the base address
 *      4-0     Reverse
 *      The high exception vectors always have the base address 0xFFFF0000 and are not affected by the value of VBAR.
 *      MRC p15, 0, <Rt>, c12, c0, 0; Read VBAR into Rt
 *      MCR p15, 0, <Rt>, c12, c0, 0; Write Rt to VBAR
 */
#define _ARM_CP_VBAR_R(vbar)    _ARM_CP_R(p15, 0, vbar, c12, c0, 0)
#define _ARM_CP_VBAR_W(vbar)    _ARM_CP_W(p15, 0, vbar, c12, c0, 0)

void rt_cpu_vector_set_base(uint32_t addr)
{
    rt_cpu_ctl_feature_disable(CP15_SCTLR_V); /* disable high exception vectors(0xFFFF0000) */
    _ARM_CP_VBAR_W(addr);
    _ARM_DSB();
}
