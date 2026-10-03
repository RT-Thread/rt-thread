/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-30     RT-Thread    first version (heap-only AddressSanitizer)
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_ASAN

#include "asan.h"

#define DBG_TAG "asan"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/*
 * Runtime AddressSanitizer (kernel-address) for RT-Thread.
 *
 * The compiler instruments every memory load/store and calls
 * __asan_loadN_noabort / __asan_storeN_noabort. Those helpers check a
 * shadow byte (8 bytes of application memory -> 1 shadow byte) and report
 * when the access touches a poisoned granule.
 *
 * The system heap calls this runtime while holding its allocator lock. Each
 * allocation reserves a header and redzones independently of the tracking table.
 */

/* ---- shadow memory ---- */
static rt_uintptr_t asan_heap_base;                          /* first checked address */
static rt_uintptr_t asan_heap_limit;                         /* base + coverage */
static rt_uint8_t asan_shadow[RT_ASAN_SHADOW_SIZE];         /* 8 bytes -> 1 byte */

/* Use hardware locks: scheduler-aware spinlocks can access heap-allocated
 * thread objects and recursively enter the sanitizer. Never print or call
 * instrumented memory helpers while this lock is held.
 */
#ifdef RT_USING_SMP
static RT_DEFINE_HW_SPINLOCK(asan_spinlock);
#endif

static rt_base_t asan_lock(void)
{
    rt_base_t level = rt_hw_local_irq_disable();
#ifdef RT_USING_SMP
    rt_hw_spin_lock(&asan_spinlock);
#endif
    return level;
}

static void asan_unlock(rt_base_t level)
{
#ifdef RT_USING_SMP
    rt_hw_spin_unlock(&asan_spinlock);
#endif
    rt_hw_local_irq_enable(level);
}

/* total number of violations reported, exposed for utest/CI verification */
static volatile rt_uint32_t asan_report_count;

rt_uint32_t rt_asan_report_count_get(void)
{
    rt_base_t level = asan_lock();
    rt_uint32_t count = asan_report_count;
    asan_unlock(level);
    return count;
}

#define ASAN_SHADOW_SCALE 8
#define ASAN_POISON       0xF8   /* whole granule poisoned */
#define ASAN_MIN(a, b)    ((a) < (b) ? (a) : (b))

/* ---- allocation tracking table ---- */
#ifndef RT_ASAN_TRACK_MAX
#define RT_ASAN_TRACK_MAX 512
#endif

struct asan_track
{
    rt_uintptr_t ptr;
    rt_size_t size;
    rt_uint8_t used;
    char owner[RT_NAME_MAX];
};

static struct asan_track asan_tracks[RT_ASAN_TRACK_MAX];

/* most recently freed block, for use-after-free diagnosis */
static struct asan_track asan_last_freed;

/* ---- helpers ---- */
rt_inline rt_bool_t asan_addr_in_range(rt_uintptr_t addr)
{
    return addr >= asan_heap_base && addr < asan_heap_limit;
}

/* check whether [addr, addr+size) touches any poisoned byte */
static rt_bool_t asan_range_is_poisoned(rt_uintptr_t addr, rt_size_t size)
{
    rt_uintptr_t off;
    rt_size_t n;
    rt_uint8_t shadow;
    rt_bool_t poisoned = RT_FALSE;
    rt_base_t level;

    if (!size || addr >= asan_heap_limit)
    {
        return RT_FALSE;
    }
    if (addr < asan_heap_base)
    {
        n = asan_heap_base - addr;
        if (size <= n)
        {
            return RT_FALSE;
        }
        addr = asan_heap_base;
        size -= n;
    }
    size = ASAN_MIN(size, asan_heap_limit - addr);
    level = asan_lock();
    while (size)
    {
        off = addr - asan_heap_base;
        n = ASAN_MIN(ASAN_SHADOW_SCALE - (off & (ASAN_SHADOW_SCALE - 1)), size);
        shadow = asan_shadow[off >> 3];
        if (shadow && (shadow >= ASAN_SHADOW_SCALE ||
                       (off & (ASAN_SHADOW_SCALE - 1)) + n > shadow))
        {
            poisoned = RT_TRUE;
            break;
        }
        addr += n;
        size -= n;
    }
    asan_unlock(level);
    return poisoned;
}

static void asan_locate_block(rt_uintptr_t addr)
{
    struct asan_track block = { 0 };
    const char *kind = "overflow candidate";
    rt_uintptr_t best_end = 0;
    rt_bool_t freed = RT_FALSE;
    rt_uint32_t i;
    rt_base_t level = asan_lock();

    if (asan_last_freed.used && addr >= asan_last_freed.ptr &&
        addr - asan_last_freed.ptr < asan_last_freed.size)
    {
        block = asan_last_freed;
        kind = "USE-AFTER-FREE";
        freed = RT_TRUE;
    }
    for (i = 0; i < RT_ASAN_TRACK_MAX; i++)
    {
        if (!asan_tracks[i].used)
        {
            continue;
        }
        if (addr >= asan_tracks[i].ptr && addr - asan_tracks[i].ptr < asan_tracks[i].size)
        {
            block = asan_tracks[i];
            kind = "inside block";
            break;
        }
        if (!freed)
        {
            rt_uintptr_t end = asan_tracks[i].ptr + asan_tracks[i].size;
            if (end <= addr && end >= best_end)
            {
                best_end = end;
                block = asan_tracks[i];
            }
        }
    }
    asan_unlock(level);
    if (block.used)
    {
        rt_kprintf("== block  : %p size %lu owner %.*s (%s, offset +%lu)\n",
                   (void *)block.ptr, (unsigned long)block.size,
                   RT_NAME_MAX, block.owner, kind, (unsigned long)(addr - block.ptr));
    }
    else
    {
        rt_kprintf("== block  : (no nearby active allocation)\n");
    }
}

static void asan_report(rt_uintptr_t addr, rt_size_t size, rt_bool_t is_write, rt_uintptr_t pc)
{
    rt_thread_t self = rt_thread_self();

    rt_base_t level = asan_lock();
    asan_report_count++;
    asan_unlock(level);

    rt_kprintf("\n");
    rt_kprintf("=================================================================\n");
    rt_kprintf("== ADDRESS SANITIZER: %s\n",
               is_write ? "invalid heap access on WRITE" : "invalid heap access on READ");
    rt_kprintf("== address: %p  size: %lu\n", (void *)addr, (unsigned long)size);
    rt_kprintf("== pc     : %p\n", (void *)pc);
    if (self)
    {
        rt_kprintf("== thread : %.*s\n", RT_NAME_MAX, self->parent.name);
    }
    asan_locate_block(addr);
#ifdef RT_ASAN_BACKTRACE
    rt_backtrace();
#endif
    rt_kprintf("=================================================================\n");
}

/* ---- instrumented access checks ---- */
#define ASAN_DEFINE_CHECK(_size, _suffix)                           \
    void __asan_load##_suffix##_noabort(rt_uintptr_t addr)          \
    {                                                               \
        if (asan_range_is_poisoned(addr, _size))                    \
            asan_report(addr, _size, RT_FALSE,                      \
                        (rt_uintptr_t)__builtin_return_address(0)); \
    }                                                               \
    void __asan_store##_suffix##_noabort(rt_uintptr_t addr)         \
    {                                                               \
        if (asan_range_is_poisoned(addr, _size))                    \
            asan_report(addr, _size, RT_TRUE,                       \
                        (rt_uintptr_t)__builtin_return_address(0)); \
    }

ASAN_DEFINE_CHECK(1, 1)
ASAN_DEFINE_CHECK(2, 2)
ASAN_DEFINE_CHECK(4, 4)
ASAN_DEFINE_CHECK(8, 8)
ASAN_DEFINE_CHECK(16, 16)

/* variable-length variants */
void __asan_loadN_noabort(rt_uintptr_t addr, rt_size_t size)
{
    if (asan_range_is_poisoned(addr, size))
    {
        asan_report(addr, size, RT_FALSE, (rt_uintptr_t)__builtin_return_address(0));
    }
}

void __asan_storeN_noabort(rt_uintptr_t addr, rt_size_t size)
{
    if (asan_range_is_poisoned(addr, size))
    {
        asan_report(addr, size, RT_TRUE, (rt_uintptr_t)__builtin_return_address(0));
    }
}

/* misc symbols referenced by some GCC versions */
void __asan_init(void) {}
void __asan_handle_no_return(void) {}

/* ---- poison / unpoison (allocator integration) ---- */
static void asan_unpoison_range(rt_uintptr_t addr, rt_size_t size)
{
    rt_uintptr_t a = addr;
    rt_uintptr_t end = addr + size;

    if (size == 0)
    {
        return;
    }

    while (a < end)
    {
        rt_uintptr_t off;
        rt_uint8_t *sh;
        rt_size_t n;
        rt_uint8_t k;

        if (!asan_addr_in_range(a))
        {
            return;
        }

        off = a - asan_heap_base;
        sh = &asan_shadow[off >> 3];
        k = off & (ASAN_SHADOW_SCALE - 1);
        n = ASAN_MIN((rt_size_t)(ASAN_SHADOW_SCALE - k), end - a);

        if (k + n == ASAN_SHADOW_SCALE)
        {
            *sh = 0;                    /* whole granule addressable */
        }
        else
        {
            *sh = (rt_uint8_t)(k + n);   /* addressable prefix through this range */
        }

        a += n;
    }
}

static void asan_poison_range(rt_uintptr_t addr, rt_size_t size)
{
    rt_uintptr_t a = addr;
    rt_uintptr_t end = addr + size;

    if (size == 0)
    {
        return;
    }

    while (a < end)
    {
        rt_uintptr_t off;
        rt_uint8_t *sh;
        rt_size_t n;
        rt_uint8_t k;

        if (!asan_addr_in_range(a))
        {
            return;
        }

        off = a - asan_heap_base;
        sh = &asan_shadow[off >> 3];
        k = off & (ASAN_SHADOW_SCALE - 1);
        n = ASAN_MIN((rt_size_t)(ASAN_SHADOW_SCALE - k), end - a);

        if (n == ASAN_SHADOW_SCALE)
        {
            *sh = ASAN_POISON;          /* whole granule poisoned */
        }
        else
        {
            *sh = k;                    /* only first k bytes stay addressable */
        }

        a += n;
    }
}

/* ---- allocation tracking ---- */
static void asan_track_add(rt_uintptr_t ptr, rt_size_t size, rt_thread_t self)
{
    rt_uint32_t i;

    /* update an existing record (e.g. realloc growing in place keeps the same
     * user pointer but a larger size), otherwise append a new one */
    for (i = 0; i < RT_ASAN_TRACK_MAX; i++)
    {
        if (asan_tracks[i].used && asan_tracks[i].ptr == ptr)
        {
            asan_tracks[i].size = size;
            return;
        }
    }

    for (i = 0; i < RT_ASAN_TRACK_MAX; i++)
    {
        if (!asan_tracks[i].used)
        {
            asan_tracks[i].ptr = ptr;
            asan_tracks[i].size = size;
            asan_tracks[i].used = 1;
            {
                rt_size_t n = 0;
                if (self)
                {
                    while (n < RT_NAME_MAX - 1 && self->parent.name[n])
                    {
                        asan_tracks[i].owner[n] = self->parent.name[n];
                        n++;
                    }
                }
                asan_tracks[i].owner[n] = '\0';
            }
            return;
        }
    }
}

static rt_uint32_t asan_track_find(rt_uintptr_t ptr)
{
    rt_uint32_t i;

    for (i = 0; i < RT_ASAN_TRACK_MAX; i++)
    {
        if (asan_tracks[i].used && asan_tracks[i].ptr == ptr)
        {
            return i;
        }
    }

    return RT_ASAN_TRACK_MAX;   /* not found */
}

/* The user pointer is aligned independently of the underlying heap's alignment.
 * Keep allocation metadata in-band so tracking-table exhaustion is harmless.
 */
#define ASAN_ALIGNMENT ((RT_ALIGN_SIZE > ASAN_SHADOW_SCALE) ? RT_ALIGN_SIZE : ASAN_SHADOW_SCALE)
#define ASAN_REDZONE   ASAN_SHADOW_SCALE
#ifdef RT_USING_SLAB_AS_HEAP
#define ASAN_ALLOC_ALIGNMENT RT_MM_PAGE_SIZE
#else
#define ASAN_ALLOC_ALIGNMENT ASAN_ALIGNMENT
#endif
struct asan_header
{
    void *raw;
    rt_size_t size;
    rt_size_t capacity;
};

void *rt_asan_malloc(rt_size_t size, void *(*alloc)(rt_size_t))
{
    return rt_asan_malloc_align(size, ASAN_ALIGNMENT, alloc);
}

void *rt_asan_malloc_align(rt_size_t size, rt_size_t align, void *(*alloc)(rt_size_t))
{
    rt_size_t overhead;
    struct asan_header *header;
    rt_uintptr_t p;
    void *raw;
    rt_size_t capacity;
    rt_base_t level;
    rt_thread_t self;

    if (!size || !align || (align & (align - 1)))
    {
        return RT_NULL;
    }
    if (align < ASAN_ALIGNMENT)
    {
        align = ASAN_ALIGNMENT;
    }
    /* A power-of-two alignment is at most half the address space, so this
     * addition cannot wrap. Reserve room for both allocator rounding steps.
     */
    overhead = sizeof(struct asan_header) + align - 1 + ASAN_REDZONE;
    if (size > (rt_size_t)-1 - overhead - (ASAN_ALIGNMENT - 1) - (ASAN_ALLOC_ALIGNMENT - 1))
    {
        return RT_NULL;
    }
    capacity = RT_ALIGN(size, ASAN_ALIGNMENT);
    raw = alloc(capacity + overhead);
    if (!raw)
    {
        return RT_NULL;
    }
    p = RT_ALIGN((rt_uintptr_t)raw + sizeof(*header), align);
    header = (struct asan_header *)p - 1;
    header->raw = raw;
    header->size = size;
    header->capacity = capacity;
    self = rt_thread_self();

    level = asan_lock();
    asan_unpoison_range((rt_uintptr_t)raw, p + capacity + ASAN_REDZONE - (rt_uintptr_t)raw);
    asan_poison_range(p - ASAN_REDZONE, ASAN_REDZONE);
    asan_unpoison_range(p, size);
    asan_poison_range(p + size, capacity + ASAN_REDZONE - size);
    if (asan_last_freed.used && asan_last_freed.ptr == p)
    {
        asan_last_freed.used = 0;
    }
    asan_track_add(p, size, self);
    asan_unlock(level);
    return (void *)p;
}

void rt_asan_free(void *ptr, void (*release)(void *))
{
    struct asan_header *header;
    rt_uintptr_t p = (rt_uintptr_t)ptr;
    rt_size_t capacity;
    void *raw;
    rt_uint32_t idx;
    rt_base_t level;

    if (!ptr)
    {
        return;
    }
    header = (struct asan_header *)ptr - 1;
    raw = header->raw;
    capacity = header->capacity;
    level = asan_lock();
    idx = asan_track_find(p);
    if (idx != RT_ASAN_TRACK_MAX)
    {
        asan_last_freed = asan_tracks[idx];
        asan_tracks[idx].used = 0;
    }
    else
    {
        asan_last_freed.ptr = p;
        asan_last_freed.size = header->size;
        asan_last_freed.used = 1;
        asan_last_freed.owner[0] = '\0';
    }
    /* Allocators may reuse any part of the raw block for their metadata. */
    asan_unpoison_range((rt_uintptr_t)raw, p + capacity + ASAN_REDZONE - (rt_uintptr_t)raw);
    asan_unlock(level);
    release(raw);
#if RT_ASAN_HAS_UAF_DETECTION
    /* The heap lock still prevents reuse while the shadow is updated. */
    level = asan_lock();
    asan_poison_range(p, capacity + ASAN_REDZONE);
    asan_unlock(level);
#endif
}

void *rt_asan_realloc(void *ptr, rt_size_t size,
                      void *(*alloc)(rt_size_t), void (*release)(void *))
{
    struct asan_header *header;
    void *result;
    rt_base_t level;
    rt_thread_t self;

    if (!ptr)
    {
        return rt_asan_malloc(size, alloc);
    }
    if (!size)
    {
        rt_asan_free(ptr, release);
        return RT_NULL;
    }
    header = (struct asan_header *)ptr - 1;
    if (size <= header->capacity)
    {
        self = rt_thread_self();
        level = asan_lock();
        header->size = size;
        asan_unpoison_range((rt_uintptr_t)ptr, size);
        asan_poison_range((rt_uintptr_t)ptr + size, header->capacity + ASAN_REDZONE - size);
        asan_track_add((rt_uintptr_t)ptr, size, self);
        asan_unlock(level);
        return ptr;
    }
    result = rt_asan_malloc(size, alloc);
    if (result)
    {
        /* Copy only user bytes, never allocator padding or a redzone. */
        rt_memcpy(result, ptr, header->size);
        rt_asan_free(ptr, release);
    }
    return result;
}

/*
 * Override the weak rt_system_heap_init to capture the heap range and
 * initialize the shadow before the component heap init runs.
 */
void rt_system_heap_init(void *begin_addr, void *end_addr)
{
    rt_uintptr_t begin = (rt_uintptr_t)begin_addr;
    rt_uintptr_t end = (rt_uintptr_t)end_addr;

    /* User pointers are explicitly aligned to shadow granules. */
    RT_ASSERT(end > begin && end - begin >= ASAN_SHADOW_SCALE);
    asan_heap_base = RT_ALIGN(begin, ASAN_SHADOW_SCALE);
    asan_heap_limit = asan_heap_base + ASAN_MIN(end - asan_heap_base,
                                                (rt_uintptr_t)sizeof(asan_shadow) * ASAN_SHADOW_SCALE);

    /*
     * Start with everything addressable: the heap allocators store their own
     * metadata (headers, free lists, the heap object itself) inside the heap
     * region, so an initially-poisoned shadow would report their internal
     * accesses as false positives. Detection is provided by poisoning the
     * block tail on allocation and the whole block on free instead.
     */
    rt_memset(asan_shadow, 0, sizeof(asan_shadow));

    /* Initialize the allocator owned by the ASan adapter. */
    rt_asan_heap_init(begin_addr, end_addr);
}

#ifdef RT_USING_FINSH
#include <finsh.h>

static int asan_info(int argc, char **argv)
{
    rt_uint32_t i;
    rt_uint32_t active = 0;
    struct asan_track block;
    rt_base_t level;

    RT_UNUSED(argc);
    RT_UNUSED(argv);
    rt_kprintf("\n-- AddressSanitizer status --\n");
    rt_kprintf("shadow   : %p, %lu bytes\n", asan_shadow, (unsigned long)sizeof(asan_shadow));
    rt_kprintf("coverage : %p - %p\n", (void *)asan_heap_base, (void *)asan_heap_limit);
    level = asan_lock();
    block = asan_last_freed;
    asan_unlock(level);
    if (block.used)
    {
        rt_kprintf("last free: %p size %lu owner %.*s\n", (void *)block.ptr,
                   (unsigned long)block.size, RT_NAME_MAX, block.owner);
    }
    else
    {
        rt_kprintf("last free: (none)\n");
    }
    rt_kprintf("\n-- active allocations (snapshot per entry) --\n");
    for (i = 0; i < RT_ASAN_TRACK_MAX; i++)
    {
        level = asan_lock();
        block = asan_tracks[i];
        asan_unlock(level);
        if (block.used)
        {
            active++;
            rt_kprintf("  %p  %6lu  %.*s\n", (void *)block.ptr,
                       (unsigned long)block.size, RT_NAME_MAX, block.owner);
        }
    }
    rt_kprintf("total: %u active blocks\n", active);
    return 0;
}
MSH_CMD_EXPORT(asan_info, dump AddressSanitizer status);
#endif /* RT_USING_FINSH */

#endif /* RT_USING_ASAN */
