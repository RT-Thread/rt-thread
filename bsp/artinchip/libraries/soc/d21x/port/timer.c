/*
 * Copyright (c) 2022-2026, ArtInChip Technology Co., Ltd
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * D213 timer access adapted from the ArtInChip D21x RT-Thread port.
 */

#include <riscv_timer.h>
#include "aic_soc.h"

/* D213 keeps mtime in the time CSR; mtimecmp uses two 32-bit stores. */
rt_uint64_t riscv_timer_rdtime(void)
{
    rt_uint64_t value;

    __asm__ volatile("rdtime %0" : "=r"(value));
    return value;
}

void riscv_timer_set_compare(rt_uint64_t value)
{
    rt_ubase_t cmp = AIC_CLINT_BASE + 0x4000;

    /* Prevent a transient expired value while updating the low word. */
    aic_write32(cmp + 4, RT_UINT32_MAX);
    aic_write32(cmp, (rt_uint32_t)value);
    aic_write32(cmp + 4, (rt_uint32_t)(value >> 32));
}

rt_uint64_t rt_hw_get_clock_timer_freq(void)
{
    return BSP_CLINT_FREQ;
}
