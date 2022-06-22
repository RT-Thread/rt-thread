/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-09-07     Urey         the first version
 */

#ifndef _MIPS_CFG_H_
#define _MIPS_CFG_H_

#ifndef __ASSEMBLY__
#include <stdint.h>
typedef struct mips32_core_cfg
{
    uint16_t icache_line_size;
    uint16_t icache_lines_per_way;
    uint16_t icache_ways;
    uint16_t icache_size;
    uint16_t dcache_line_size;
    uint16_t dcache_lines_per_way;
    uint16_t dcache_ways;
    uint16_t dcache_size;

    uint16_t max_tlb_entries;   /* number of tlb entry */
} mips32_core_cfg_t;

extern mips32_core_cfg_t g_mips_core;

#endif /* __ASSEMBLY__ */

#endif /* _MIPS_CFG_H_ */
