/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fdrivers_port.c
 * Created Date: 2023-10-17 08:29:18
 * Last Modified: 2023-10-26 10:49:19
 * Description:  This file is for drive layer code decoupling
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/10/17    first release
 */
#include "fdrivers_port.h"
#include "cache.h"
#include "rtthread.h"

#ifdef __aarch64__
/* cache */
void FDriverDCacheRangeFlush(uintptr_t adr, size_t len)
{
    rt_hw_cpu_dcache_clean((void *)adr, len);
}

void FDriverDCacheRangeInvalidate(uintptr_t adr, size_t len)
{
    rt_hw_cpu_dcache_invalidate((void *)adr, len);
}

void FDriverICacheRangeInvalidate(uintptr_t adr, size_t len)
{
    __asm_invalidate_icache_all();
}

#else
#include "rthw.h"
/* cache */
void FDriverDCacheRangeFlush(uintptr_t adr, size_t len)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)adr, len);
}

void FDriverDCacheRangeInvalidate(uintptr_t adr, size_t len)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)adr, len);
}

void FDriverICacheRangeInvalidate(uintptr_t adr, size_t len)
{
    rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, (void *)adr, len);
}

#endif

/* time delay */

void FDriverUdelay(u32 usec)
{
    rt_thread_delay(usec);
}

void FDriverSdelay(u32 sec)
{
    u32 msec = sec * 1000;
    rt_thread_mdelay(msec);
}

void FDriverMdelay(u32 msec)
{
    rt_thread_mdelay(msec);
}
