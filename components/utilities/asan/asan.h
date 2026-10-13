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
 * Use-after-free detection is currently enabled only for the small-mem heap.
 * memheap/slab reuse freed storage for allocator metadata; integration with
 * poisoned freed blocks is not supported, so their freed blocks stay accessible.
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

/* Check library accesses against the covered system-heap shadow. Return
 * RT_FALSE after reporting poison; RT_TRUE means no covered poison was found,
 * not that memory outside the coverage is valid. These checks do not abort.
 */
rt_bool_t rt_asan_check_read(const void *addr, rt_size_t size);
rt_bool_t rt_asan_check_write(void *addr, rt_size_t size);

#ifdef RT_ASAN_USING_LIBC
/* Return RT_TRUE only when the covered shadow contains a poisoned boundary
 * at/after addr. *size is the readable/writable prefix before that boundary.
 * RT_FALSE means the boundary is unknown, including coverage ending first.
 */
rt_bool_t rt_asan_accessible_size(const void *addr, rt_size_t *size);
#endif

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
