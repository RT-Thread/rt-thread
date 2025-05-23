/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     The first version
 */

#include <bitmap.h>
#include <isa_ext.h>

static RT_BITMAP_DECLARE(isa_map, RISCV_ISA_EXT_MAX);

void riscv_isa_ext_set_raw(rt_uint32_t isa)
{
    rt_bitmap_set_bit(isa_map, isa);
}

void riscv_isa_ext_clear_raw(rt_uint32_t isa)
{
    rt_bitmap_clear_bit(isa_map, isa);
}

rt_bool_t riscv_isa_ext_test_raw(rt_uint32_t isa)
{
    return rt_bitmap_test_bit(isa_map, isa);
}
