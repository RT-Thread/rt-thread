/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-27     huanghe      first version
 *
 */

#include "rtconfig.h"
#include <board.h>
#include <mmu.h>

/* mmu config */
#ifdef RT_USING_SMART
#if defined(TARGET_ARMV8_AARCH64)
struct mem_desc platform_mem_desc[] =
{
    {   KERNEL_VADDR_START,
        KERNEL_VADDR_START + 0x0fffffff,
        (rt_size_t)ARCH_MAP_FAILED,
        NORMAL_MEM
    }
};
#else
struct mem_desc platform_mem_desc[] =
{
    {   KERNEL_VADDR_START,
        KERNEL_VADDR_START + 0x10000000,
        (rt_size_t)ARCH_MAP_FAILED,
        NORMAL_MEM
    }
};
#endif
#else

#if defined(TARGET_ARMV8_AARCH64)

struct mem_desc platform_mem_desc[] = {
    {KERNEL_VADDR_START, DDR_END_ADDRESS , KERNEL_VADDR_START, NORMAL_MEM},
    {
        0x28000000U,
        0x32B36FFFU,
        0x28000000U,
        DEVICE_MEM
    },
};
#else
struct mem_desc platform_mem_desc[] =
{
    {
        0x00U,
        0x00U + 0x40000000U,
        0x00U,
        DEVICE_MEM
    },
    {
        0x40000000U,
        0x40000000U + 0x10000000U,
        0x40000000U,
        DEVICE_MEM
    },
    {
        0x50000000U,
        0x50000000U + 0x30000000U,
        0x50000000U,
        DEVICE_MEM
    },
    {
        0x80000000U,
        0xffffffffU,
        0x80000000U,
        NORMAL_MEM
    },
#if defined(TARGET_ARMV8_AARCH64)
    {
        0x1000000000,
        0x1000000000 + 0x1000000000,
        0x1000000000,
        DEVICE_MEM
    },
    {
        0x2000000000,
        0x2000000000 + 0x2000000000,
        0x2000000000,
        NORMAL_MEM
    },
#endif
};

#endif

#endif

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]);
