/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-27     swkyer       first version
 */
#ifndef __MIPSCFG_H__
#define __MIPSCFG_H__


typedef struct mips32_core_cfg
{
    rt_uint16_t icache_line_size;
    rt_uint16_t icache_lines_per_way;
    rt_uint16_t icache_ways;
    rt_uint16_t dcache_line_size;
    rt_uint16_t dcache_lines_per_way;
    rt_uint16_t dcache_ways;

    rt_uint16_t max_tlb_entries;	/* number of tlb entry */
} mips32_core_cfg_t;

extern mips32_core_cfg_t g_mips_core;

#endif /* end of __MIPSCFG_H__ */
