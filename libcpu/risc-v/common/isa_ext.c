/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     The first version
 */

#include <rthw.h>

#include <cpuport.h>
#include <isa_ext.h>

#define RISCV_ISA_WORD_BITS  (sizeof(rt_ubase_t) * 8)
#define RISCV_ISA_WORDS      ((RISCV_ISA_EXT_MAX + RISCV_ISA_WORD_BITS - 1) / \
                              RISCV_ISA_WORD_BITS)

static rt_ubase_t isa_map[RISCV_ISA_WORDS];

void riscv_isa_ext_set_raw(rt_uint32_t isa)
{
    if (isa < RISCV_ISA_EXT_MAX)
    {
        isa_map[isa / RISCV_ISA_WORD_BITS] |=
                (rt_ubase_t)1 << (isa % RISCV_ISA_WORD_BITS);
        rt_hw_wmb();
    }
}

void riscv_isa_ext_clear_raw(rt_uint32_t isa)
{
    if (isa < RISCV_ISA_EXT_MAX)
    {
        isa_map[isa / RISCV_ISA_WORD_BITS] &=
                ~((rt_ubase_t)1 << (isa % RISCV_ISA_WORD_BITS));
        rt_hw_wmb();
    }
}

rt_bool_t riscv_isa_ext_test_raw(rt_uint32_t isa)
{
    rt_hw_rmb();

    return isa < RISCV_ISA_EXT_MAX &&
            !!(isa_map[isa / RISCV_ISA_WORD_BITS] &
            ((rt_ubase_t)1 << (isa % RISCV_ISA_WORD_BITS)));
}
