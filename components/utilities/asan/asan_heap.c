/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * ASan system heap adapter. Override the default weak heap interfaces and
 * keep the allocator, lock and hooks together. Raw allocations and shadow
 * updates are serialized by the same lock, including realloc and page APIs.
 */

#include <rtthread.h>
#include <rthw.h>
#include "asan.h"

#ifdef RT_USING_ASAN
#ifdef RT_USING_HOOK
static void (*rt_malloc_hook)(void **ptr, rt_size_t size);
static void (*rt_realloc_entry_hook)(void **ptr, rt_size_t size);
static void (*rt_realloc_exit_hook)(void **ptr, rt_size_t size);
static void (*rt_free_hook)(void **ptr);

#if defined(RT_UTEST_ASAN) && defined(RT_HOOK_USING_FUNC_PTR)
rt_bool_t rt_asan_test_hooks_in_use(void)
{
    return rt_malloc_hook || rt_realloc_entry_hook ||
           rt_realloc_exit_hook || rt_free_hook;
}
#endif

void rt_malloc_sethook(void (*hook)(void **ptr, rt_size_t size))
{
    rt_malloc_hook = hook;
}

void rt_realloc_set_entry_hook(void (*hook)(void **ptr, rt_size_t size))
{
    rt_realloc_entry_hook = hook;
}

void rt_realloc_set_exit_hook(void (*hook)(void **ptr, rt_size_t size))
{
    rt_realloc_exit_hook = hook;
}

void rt_free_sethook(void (*hook)(void **ptr))
{
    rt_free_hook = hook;
}

#endif /* RT_USING_HOOK */

#if defined(RT_USING_HEAP_ISR)
static struct rt_spinlock _heap_spinlock;
#elif defined(RT_USING_MUTEX)
static struct rt_mutex _lock;
#endif

rt_inline void _heap_lock_init(void)
{
#if defined(RT_USING_HEAP_ISR)
    rt_spin_lock_init(&_heap_spinlock);
#elif defined(RT_USING_MUTEX)
    rt_mutex_init(&_lock, "heap", RT_IPC_FLAG_PRIO);
#endif
}

rt_inline rt_base_t _heap_lock(void)
{
#if defined(RT_USING_HEAP_ISR)
    return rt_spin_lock_irqsave(&_heap_spinlock);
#elif defined(RT_USING_MUTEX)
    if (rt_thread_self())
    {
        return rt_mutex_take(&_lock, RT_WAITING_FOREVER);
    }
    else
    {
        return RT_EOK;
    }
#else
    rt_enter_critical();
    return RT_EOK;
#endif
}

rt_inline void _heap_unlock(rt_base_t level)
{
#if defined(RT_USING_HEAP_ISR)
    rt_spin_unlock_irqrestore(&_heap_spinlock, level);
#elif defined(RT_USING_MUTEX)
    RT_ASSERT(level == RT_EOK);
    if (rt_thread_self())
    {
        rt_mutex_release(&_lock);
    }
#else
    rt_exit_critical();
#endif
}

#ifdef RT_USING_UTESTCASES
/* Keep heap-observation tests synchronized with the active allocator. */
rt_base_t rt_heap_lock(void);
void rt_heap_unlock(rt_base_t level);

rt_base_t rt_heap_lock(void)
{
    return _heap_lock();
}

void rt_heap_unlock(rt_base_t level)
{
    _heap_unlock(level);
}
#endif

#if defined(RT_USING_SMALL_MEM_AS_HEAP)
static rt_smem_t system_heap;
rt_inline void _smem_info(rt_size_t *total,
                          rt_size_t *used, rt_size_t *max_used)
{
    if (total)
    {
        *total = system_heap->total;
    }
    if (used)
    {
        *used = system_heap->used;
    }
    if (max_used)
    {
        *max_used = system_heap->max;
    }
}
#define _MEM_INIT(_name, _start, _size) \
    system_heap = rt_smem_init(_name, _start, _size)
#define _MEM_MALLOC(_size) \
    rt_smem_alloc(system_heap, _size)
#define _MEM_FREE(_ptr) \
    rt_smem_free(_ptr)
#define _MEM_INFO(_total, _used, _max) \
    _smem_info(_total, _used, _max)
#elif defined(RT_USING_MEMHEAP_AS_HEAP)
static struct rt_memheap system_heap;
void *_memheap_alloc(struct rt_memheap *heap, rt_size_t size);
void _memheap_free(void *rmem);
#define _MEM_INIT(_name, _start, _size)                      \
    do                                                       \
    {                                                        \
        rt_memheap_init(&system_heap, _name, _start, _size); \
        system_heap.locked = RT_TRUE;                        \
    } while (0)
#define _MEM_MALLOC(_size) \
    _memheap_alloc(&system_heap, _size)
#define _MEM_FREE(_ptr) \
    _memheap_free(_ptr)
#define _MEM_INFO(_total, _used, _max) \
    rt_memheap_info(&system_heap, _total, _used, _max)
#elif defined(RT_USING_SLAB_AS_HEAP)
static rt_slab_t system_heap;
rt_inline void _slab_info(rt_size_t *total,
                          rt_size_t *used, rt_size_t *max_used)
{
    if (total)
    {
        *total = system_heap->total;
    }
    if (used)
    {
        *used = system_heap->used;
    }
    if (max_used)
    {
        *max_used = system_heap->max;
    }
}
#define _MEM_INIT(_name, _start, _size) \
    system_heap = rt_slab_init(_name, _start, _size)
#define _MEM_MALLOC(_size) \
    rt_slab_alloc(system_heap, _size)
#define _MEM_FREE(_ptr) \
    rt_slab_free(system_heap, _ptr)
#define _MEM_INFO _slab_info
#else
#define _MEM_INIT(...)
#define _MEM_MALLOC(...) RT_NULL
#define _MEM_FREE(...)
#define _MEM_INFO(...)
#endif

static void *_asan_heap_alloc(rt_size_t size)
{
    return _MEM_MALLOC(size);
}

static void _asan_heap_free(void *ptr)
{
    _MEM_FREE(ptr);
}

void rt_asan_heap_init(void *begin_addr, void *end_addr)
{
    rt_uintptr_t begin_align = RT_ALIGN((rt_uintptr_t)begin_addr, RT_ALIGN_SIZE);
    rt_uintptr_t end_align = RT_ALIGN_DOWN((rt_uintptr_t)end_addr, RT_ALIGN_SIZE);

    RT_ASSERT(end_align > begin_align);

    /* Initialize system memory heap */
    _MEM_INIT("heap", (void *)begin_align, end_align - begin_align);
    /* Initialize multi thread contention lock */
    _heap_lock_init();
}

void *rt_malloc(rt_size_t size)
{
    rt_base_t level;
    void *ptr;

    /* Enter critical zone */
    level = _heap_lock();
    /* allocate memory block from system heap */
    ptr = rt_asan_malloc(size, _asan_heap_alloc);
    /* Exit critical zone */
    _heap_unlock(level);
    /* call 'rt_malloc' hook */
    RT_OBJECT_HOOK_CALL(rt_malloc_hook, (&ptr, size));
    return ptr;
}

void *rt_realloc(void *ptr, rt_size_t newsize)
{
    rt_base_t level;
    void *nptr;

    /* Entry hook */
    RT_OBJECT_HOOK_CALL(rt_realloc_entry_hook, (&ptr, newsize));
    /* Enter critical zone */
    level = _heap_lock();
    /* Change the size of previously allocated memory block */
    nptr = rt_asan_realloc(ptr, newsize, _asan_heap_alloc, _asan_heap_free);
    /* Exit critical zone */
    _heap_unlock(level);
    /* Exit hook */
    RT_OBJECT_HOOK_CALL(rt_realloc_exit_hook, (&nptr, newsize));
    return nptr;
}

void *rt_calloc(rt_size_t count, rt_size_t size)
{
    void *p;

    if (size && count > (rt_size_t)-1 / size)
    {
        return RT_NULL;
    }

    /* allocate 'count' objects of size 'size' */
    p = rt_malloc(count * size);
    /* zero the memory */
    if (p)
    {
        rt_memset(p, 0, count * size);
    }
    return p;
}

void rt_free(void *ptr)
{
    rt_base_t level;

    /* call 'rt_free' hook */
    RT_OBJECT_HOOK_CALL(rt_free_hook, (&ptr));
    /* NULL check */
    if (ptr == RT_NULL)
    {
        return;
    }
    /* Enter critical zone */
    level = _heap_lock();
    rt_asan_free(ptr, _asan_heap_free);
    /* Exit critical zone */
    _heap_unlock(level);
}

void rt_memory_info(rt_size_t *total,
                    rt_size_t *used,
                    rt_size_t *max_used)
{
    rt_base_t level;

    /* Enter critical zone */
    level = _heap_lock();
    _MEM_INFO(total, used, max_used);
    /* Exit critical zone */
    _heap_unlock(level);
}

#if defined(RT_USING_SLAB) && defined(RT_USING_SLAB_AS_HEAP)
void *rt_page_alloc(rt_size_t npages)
{
    rt_base_t level;
    void *ptr;

    /* Enter critical zone */
    level = _heap_lock();
    /* alloc page */
    ptr = rt_slab_page_alloc(system_heap, npages);
    /* Exit critical zone */
    _heap_unlock(level);
    return ptr;
}

void rt_page_free(void *addr, rt_size_t npages)
{
    rt_base_t level;

    /* Enter critical zone */
    level = _heap_lock();
    /* free page */
    rt_slab_page_free(system_heap, addr, npages);
    /* Exit critical zone */
    _heap_unlock(level);
}
#endif

void *rt_malloc_align(rt_size_t size, rt_size_t align)
{
    void *ptr;
    rt_base_t level;

    if (!size || !align || (align & (align - 1)))
    {
        return RT_NULL;
    }
    if (align < sizeof(void *))
    {
        align = sizeof(void *);
    }

    /* Keep the requested size rather than tracking an oversized backing block. */
    level = _heap_lock();
    ptr = rt_asan_malloc_align(size, align, _asan_heap_alloc);
    _heap_unlock(level);
    RT_OBJECT_HOOK_CALL(rt_malloc_hook, (&ptr, size));
    return ptr;
}

void rt_free_align(void *ptr)
{
    if (ptr == RT_NULL)
    {
        return;
    }
    /* The ASan header is read by the non-instrumented runtime under the heap
     * lock. The old pointer-before-buffer layout is not used in this mode.
     */
    rt_free(ptr);
}
#endif /* RT_USING_ASAN */
