/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-16 14:00:59
 * @LastEditTime: 2021-04-16 16:07:27
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_cache.h"

__STATIC_INLINE u32 FCache_cacheLineSize(void)
{
    u32 ctr;
    asm volatile("mrc p15, 0, %0, c0, c0, 1"
                 : "=r"(ctr));
    return 4 << ((ctr >> 16) & 0xF);
}

void FCache_cpuDcacheInvalidate(void *addr, ft_base_t size)
{
    u32 lineSize = FCache_cacheLineSize();
    u32 startAddr = (u32)addr;
    u32 endAddr = (u32)addr + size + lineSize - 1;

    asm volatile("dmb" ::
                     : "memory");

    startAddr &= ~(lineSize - 1);
    endAddr &= ~(lineSize - 1);

    while (startAddr < endAddr)
    {
        asm volatile("mcr p15, 0, %0, c7, c6, 1" ::"r"(startAddr)); /* dcimvac */
        startAddr += lineSize;
    }

    asm volatile("dsb" ::
                     : "memory");
}

void FCache_cpuDcacheClean(void *addr, ft_base_t size)
{
    u32 lineSize = FCache_cacheLineSize();
    u32 startAddr = (u32)addr;
    u32 endAddr = (u32)addr + size + lineSize - 1;

    asm volatile("dmb" ::
                     : "memory");

    startAddr &= ~(lineSize - 1);
    endAddr &= ~(lineSize - 1);

    while (startAddr < endAddr)
    {
        asm volatile("mcr p15, 0, %0, c7, c10, 1" ::"r"(startAddr)); /* dccmvac */
        startAddr += lineSize;
    }

    asm volatile("dsb" ::
                     : "memory");
}

void FCache_cpuIcacheInvalidate(void *addr, ft_base_t size)
{
    u32 lineSize = FCache_cacheLineSize();
    u32 startAddr = (u32)addr;
    u32 endAddr = (u32)addr + size + lineSize - 1;

    asm volatile("dmb" ::
                     : "memory");
    startAddr &= ~(lineSize - 1);
    endAddr &= ~(lineSize - 1);
    while (startAddr < endAddr)
    {
        asm volatile("mcr p15, 0, %0, c7, c5, 1" ::"r"(startAddr)); /* icimvau */
        startAddr += lineSize;
    }
    asm volatile("dsb\n\tisb" ::
                     : "memory");
}
