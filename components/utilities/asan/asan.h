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

#if defined(RT_UTEST_ASAN) && defined(RT_HOOK_USING_FUNC_PTR)
/* Test-only query: never replace hooks already installed by the application.
 * Hook registration must remain quiescent while the hook unit test runs.
 */
rt_bool_t rt_asan_test_hooks_in_use(void);
#endif

void rt_asan_heap_init(void *begin_addr, void *end_addr);

/* Internal system-heap integration. The caller must hold the heap lock.
 * Callbacks operate on the underlying allocator, never rt_malloc/rt_free.
 */
void *rt_asan_malloc(rt_size_t size, void *(*alloc)(rt_size_t));
void *rt_asan_malloc_align(rt_size_t size, rt_size_t align, void *(*alloc)(rt_size_t));
void rt_asan_free(void *ptr, void (*release)(void *));
void *rt_asan_realloc(void *ptr, rt_size_t size,
                      void *(*alloc)(rt_size_t), void (*release)(void *));

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
