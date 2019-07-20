/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-09-10     Urey         first version
 * 2019-07-21     Zhou Yanjie  modified for LS1B and LS1C
 */

#ifndef _MIPS_CFG_H_
#define _MIPS_CFG_H_

#ifndef __ASSEMBLY__

typedef struct mips32_core_cfg
{
    rt_uint16_t icache_line_size;
    rt_uint16_t icache_sets_per_way;
    rt_uint16_t icache_ways;
    rt_uint16_t dcache_line_size;
    rt_uint16_t dcache_sets_per_way;
    rt_uint16_t dcache_ways;

    rt_uint16_t max_tlb_entries;	/* number of tlb entry */
} mips32_core_cfg_t;

extern mips32_core_cfg_t g_mips_core;

#endif /* __ASSEMBLY__ */

#endif /* _MIPS_CFG_H_ */
