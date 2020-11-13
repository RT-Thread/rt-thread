/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-28     lizhirui       first version
 */
#include <rtthread.h>
#include <mips.h>

mips32_core_cfg_t g_mips_core =
{
    64,        /* icache_line_size */
    128,       /* icache_lines_per_way */
    4,         /* icache_ways */
    32768,
    64,        /* dcache_line_size */
    128,       /* dcache_lines_per_way */
    4,         /* dcache_ways */
    32768,
    64,        /* max_tlb_entries */
};

static rt_uint16_t m_pow(rt_uint16_t b, rt_uint16_t n)
{
    rt_uint16_t rets = 1;

    while (n--)
        rets *= b;

    return rets;
}

static rt_uint16_t m_log2(rt_uint16_t b)
{
    rt_uint16_t rets = 0;

    while (b != 1)
    {
        b /= 2;
        rets++;
    }

    return rets;
}

/**
 * read core attribute
 */
void mips32_cfg_init(void)
{
    rt_uint16_t val;
    rt_uint32_t cp0_config1;

    cp0_config1 = read_c0_config();
    if (cp0_config1 & 0x80000000)
    {
        cp0_config1 = read_c0_config1();

        val = (cp0_config1 & (7<<22))>>22;
        g_mips_core.icache_lines_per_way = 64 * m_pow(2, val);
        val = (cp0_config1 & (7<<19))>>19;
        g_mips_core.icache_line_size = 2 * m_pow(2, val);
        val = (cp0_config1 & (7<<16))>>16;
        g_mips_core.icache_ways = val + 1;

        val = (cp0_config1 & (7<<13))>>13;
        g_mips_core.dcache_lines_per_way = 64 * m_pow(2, val);
        val = (cp0_config1 & (7<<10))>>10;
        g_mips_core.dcache_line_size = 2 * m_pow(2, val);
        val = (cp0_config1 & (7<<7))>>7;
        g_mips_core.dcache_ways = val + 1;

        val = (cp0_config1 & (0x3F<<25))>>25;
        g_mips_core.max_tlb_entries = val + 1;
    }
}
