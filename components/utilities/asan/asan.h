/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-30     RT-Thread    the first version
 */

#ifndef __ASAN_H__
#define __ASAN_H__

#include <rtthread.h>

/*
 * Use-after-free detection requires poisoning a whole freed block. This is only
 * safe for allocators whose internal metadata is written by non-instrumented
 * code (small mem). memheap/slab reuse freed blocks for metadata written via
 * instrumented rt_memset/rt_memcpy, so their freed blocks must not be poisoned.
 */
#if defined(RT_USING_SMALL_MEM_AS_HEAP)
#define RT_ASAN_HAS_UAF_DETECTION 1
#else
#define RT_ASAN_HAS_UAF_DETECTION 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the total number of AddressSanitizer violations reported.
 *
 * This is used by the utest/CI harness to verify that a deliberate
 * heap-buffer-overflow or use-after-free is actually detected at runtime.
 *
 * @return The accumulated report count.
 */
rt_uint32_t rt_asan_report_count_get(void);

#ifdef __cplusplus
}
#endif

#endif /* __ASAN_H__ */
