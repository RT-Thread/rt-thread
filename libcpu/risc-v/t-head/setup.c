/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     the first version
 */

#include <cache.h>
#include <isa_ext.h>

rt_weak void fdt_thead_install_early(void *fdt)
{
    RT_UNUSED(fdt);
}

void rt_hw_fdt_vendor_install_early(void *fdt)
{
    fdt_thead_install_early(fdt);

    riscv_isa_ext_set(ZICBOM);
    riscv_cache_set_cbom_block_size(L1_CACHE_BYTES);
}
