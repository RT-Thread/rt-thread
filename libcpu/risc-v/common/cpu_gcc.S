/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     The first version
 */

#include <csr.h>

#ifdef RT_USING_SMP
#define rt_hw_interrupt_disable rt_hw_local_irq_disable
#define rt_hw_interrupt_enable rt_hw_local_irq_enable
#endif

    .section ".text","ax"

START_POINT(rt_hw_interrupt_is_disabled)
    csrr    a0, CSR_STATUS
    andi    a0, a0, SR_IE
    seqz    a0, a0
    ret
START_POINT_END(rt_hw_interrupt_is_disabled)

START_POINT(rt_hw_interrupt_enable)
    /* Restore to old csr */
    csrs    CSR_STATUS, a0
    ret
START_POINT_END(rt_hw_interrupt_enable)

START_POINT(rt_hw_interrupt_disable)
    /* Clear IE */
    csrrci  a0, CSR_STATUS, SR_IE
    ret
START_POINT_END(rt_hw_interrupt_disable)
