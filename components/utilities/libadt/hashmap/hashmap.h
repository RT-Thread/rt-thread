/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-01     GuEe-GUI     first version
 */

#ifndef __UTIL_HASHMAP_H__
#define __UTIL_HASHMAP_H__

#include <rtdef.h>

/*
 * http://www.citi.umich.edu/techreports/reports/citi-tr-00-1.pdf
 *
 * GoldenRatio = ~(Math.pow(2, 32) / ((Math.sqrt(5) - 1) / 2)) + 1
 */
#define RT_HASHMAP_GOLDEN_RATIO_32  0x61C88647
#define RT_HASHMAP_GOLDEN_RATIO_64  0X61C8864680B583EBULL

rt_inline rt_uint32_t rt_hashmap_32(rt_uint32_t val, rt_uint32_t bits)
{
    /* High bits are more random, so use them. */
    return (val * RT_HASHMAP_GOLDEN_RATIO_32) >> (32 - bits);
}

rt_inline rt_uint32_t rt_hashmap_64(rt_uint64_t val, rt_uint32_t bits)
{
#ifdef ARCH_CPU_64BIT
    /* 64x64-bit multiply is efficient on all 64-bit processors */
    return val * RT_HASHMAP_GOLDEN_RATIO_64 >> (64 - bits);
#else
    /* Hash 64 bits using only 32x32-bit multiply. */
    return rt_hashmap_32((rt_uint32_t)val ^ ((val >> 32) * RT_HASHMAP_GOLDEN_RATIO_32), bits);
#endif
}

#endif /* __UTIL_HASHMAP_H__ */
