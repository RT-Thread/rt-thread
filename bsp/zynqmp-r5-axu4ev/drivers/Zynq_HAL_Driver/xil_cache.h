/*
 * Copyright (c) 2020-2021, WangHuachen
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-30     WangHuachen  the first version
 */
#ifndef XIL_CACHE_H
#define XIL_CACHE_H

#include <rthw.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Xil_DCacheFlushRange(addr, size)  rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void*)(addr), (size))
#define Xil_DCacheInvalidateRange(addr, size)  rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void*)(addr), (size))

#ifdef __cplusplus
}
#endif

#endif
/**
* @} End of "addtogroup r5_cache_apis".
*/
