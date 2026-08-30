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
 * The system heap is poisoned/unpoisoned via the existing rt_malloc/rt_free
 * hooks, which gives heap buffer overflow and use-after-free detection.
 */

/* ---- shadow memory ---- */
static rt_uintptr_t asan_heap_base;                          /* first checked address */
static rt_uintptr_t asan_heap_limit;                         /* base + coverage */
static rt_uint8_t asan_shadow[RT_ASAN_SHADOW_SIZE];         /* 8 bytes -> 1 byte */

#define ASAN_SHADOW_SCALE 8
#define ASAN_POISON       0xF8   /* whole granule poisoned */
#define ASAN_MIN(a, b)    ((a) < (b) ? (a) : (b))

/*
 * Poisoning a freed block enables use-after-free detection. This is only safe
 * for allocators whose internal metadata is written by non-instrumented code:
 * small mem assigns its header fields directly, but memheap/slab write their
 * internal structures (memheap item headers, slab zone structs) through
 * instrumented rt_memset/rt_memcpy and place them inside freed blocks, so
 * poisoning the whole block would report those allocator-internal writes as
 * false positives. For those allocators only the tail redzone (overflow) is
 * kept.
 */
#if defined(RT_USING_SMALL_MEM_AS_HEAP)
#define ASAN_POISON_FREED_BLOCK 1
#else
#define ASAN_POISON_FREED_BLOCK 0
#endif

/* ---- allocation tracking table ---- */
#ifndef RT_ASAN_TRACK_MAX
#define RT_ASAN_TRACK_MAX 512
#endif

struct asan_track
{
    rt_uintptr_t ptr;
    rt_uint32_t size;
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
    rt_uintptr_t a = addr;
    rt_uintptr_t end = addr + size;

    if (size == 0)
    {
        return RT_FALSE;
    }

    while (a < end)
    {
        rt_uintptr_t off;
        rt_uint8_t s;
        rt_size_t n;

        if (!asan_addr_in_range(a))
        {
            return RT_FALSE;   /* outside shadow coverage: not checked */
        }

        off = a - asan_heap_base;
        s = asan_shadow[off >> 3];

        if (s == 0)
        {
            /* whole granule addressable */
            n = ASAN_SHADOW_SCALE - (off & (ASAN_SHADOW_SCALE - 1));
        }
        else if (s >= ASAN_SHADOW_SCALE)
        {
            return RT_TRUE;    /* whole granule poisoned */
        }
        else
        {
            /* partial granule: first s bytes addressable */
            if ((off & (ASAN_SHADOW_SCALE - 1)) >= s)
            {
                return RT_TRUE;
            }
            n = s - (off & (ASAN_SHADOW_SCALE - 1));
        }

        if (n >= end - a)
        {
            return RT_FALSE;   /* remaining bytes are addressable */
        }
        a += n;
    }

    return RT_FALSE;
}

static void asan_locate_block(rt_uintptr_t addr)
{
    rt_uint32_t i;
    rt_uint32_t best = RT_ASAN_TRACK_MAX;
    rt_uintptr_t best_end = 0;

    /* 1. exact match: addr is inside an active block */
    for (i = 0; i < RT_ASAN_TRACK_MAX; i++)
    {
        if (asan_tracks[i].used &&
            addr >= asan_tracks[i].ptr &&
            addr < asan_tracks[i].ptr + asan_tracks[i].size)
        {
            rt_kprintf("== block  : 0x%08x size %d owner %.*s (inside block, offset +%d)\n",
                       asan_tracks[i].ptr, asan_tracks[i].size,
                       RT_NAME_MAX, asan_tracks[i].owner,
                       addr - asan_tracks[i].ptr);
            return;
        }
    }

    /* 2. use-after-free: addr is inside the most recently freed block */
    if (asan_last_freed.used &&
        addr >= asan_last_freed.ptr &&
        addr < asan_last_freed.ptr + asan_last_freed.size)
    {
        rt_kprintf("== block  : 0x%08x size %d owner %.*s (USE-AFTER-FREE, offset +%d)\n",
                   asan_last_freed.ptr, asan_last_freed.size,
                   RT_NAME_MAX, asan_last_freed.owner,
                   addr - asan_last_freed.ptr);
        return;
    }

    /* 3. overflow candidate: the active block whose tail is closest below addr */
    for (i = 0; i < RT_ASAN_TRACK_MAX; i++)
    {
        rt_uintptr_t blk_end;

        if (!asan_tracks[i].used)
        {
            continue;
        }

        blk_end = asan_tracks[i].ptr + asan_tracks[i].size;
        if (blk_end <= addr && blk_end >= best_end)
        {
            best = i;
            best_end = blk_end;
        }
    }

    if (best != RT_ASAN_TRACK_MAX)
    {
        rt_kprintf("== block  : 0x%08x size %d owner %.*s (overflow by %d bytes)\n",
                   asan_tracks[best].ptr, asan_tracks[best].size,
                   RT_NAME_MAX, asan_tracks[best].owner,
                   addr - best_end);
    }
    else
    {
        rt_kprintf("== block  : (no nearby active allocation)\n");
    }
}

static void asan_report(rt_uintptr_t addr, rt_size_t size, rt_bool_t is_write, rt_uintptr_t pc)
{
    rt_thread_t self = rt_thread_self();

    rt_kprintf("\n");
    rt_kprintf("=================================================================\n");
    rt_kprintf("== ADDRESS SANITIZER: %s\n",
               is_write ? "heap-buffer-overflow on WRITE" : "heap-buffer-overflow on READ");
    rt_kprintf("== address: 0x%08x  size: %d\n", addr, size);
    rt_kprintf("== pc     : 0x%08x\n", pc);
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
        n = ASAN_MIN(ASAN_SHADOW_SCALE - k, end - a);

        if (n == ASAN_SHADOW_SCALE)
        {
            *sh = 0;                    /* whole granule addressable */
        }
        else
        {
            *sh = (rt_uint8_t)n;        /* first n bytes addressable */
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
        n = ASAN_MIN(ASAN_SHADOW_SCALE - k, end - a);

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
static void asan_track_add(rt_uintptr_t ptr, rt_size_t size)
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
            if (rt_thread_self())
            {
                rt_strncpy(asan_tracks[i].owner, rt_thread_self()->parent.name, RT_NAME_MAX - 1);
            }
            else
            {
                rt_memset(asan_tracks[i].owner, 0, RT_NAME_MAX);
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

static void asan_malloc_hook(void **ptr, rt_size_t size)
{
    rt_uintptr_t p;
    rt_size_t aligned;

    if (!*ptr)
    {
        return;
    }

    p = (rt_uintptr_t)*ptr;
    aligned = RT_ALIGN(size, ASAN_SHADOW_SCALE);

    /* address reuse: this block was freed before, clear the stale record */
    if (asan_last_freed.used && asan_last_freed.ptr == p)
    {
        asan_last_freed.used = 0;
    }

    asan_track_add(p, size);
    asan_unpoison_range(p, size);
    if (aligned > size)
    {
        asan_poison_range(p + size, aligned - size);
    }
}

static void asan_free_hook(void **ptr)
{
    rt_uintptr_t p;
    rt_uint32_t idx;

    if (!*ptr)
    {
        return;
    }

    p = (rt_uintptr_t)*ptr;
    idx = asan_track_find(p);
    if (idx == RT_ASAN_TRACK_MAX)
    {
        return;   /* unknown block, skip */
    }

#if ASAN_POISON_FREED_BLOCK
    {
        rt_size_t aligned = RT_ALIGN(asan_tracks[idx].size, ASAN_SHADOW_SCALE);
        asan_poison_range(p, aligned);   /* poison whole block -> use-after-free */
    }
#endif

    /* remember it for use-after-free diagnosis */
    asan_last_freed = asan_tracks[idx];
    asan_last_freed.used = 1;

    asan_tracks[idx].used = 0;
}

/* rt_realloc frees/moves the old block and allocates a new one without going
 * through rt_free/rt_malloc, so its hooks must be handled separately. */
static rt_uintptr_t asan_realloc_old_ptr;

static void asan_realloc_entry_hook(void **ptr, rt_size_t size)
{
    RT_UNUSED(size);
    asan_realloc_old_ptr = (rt_uintptr_t)*ptr;
}

static void asan_realloc_exit_hook(void **ptr, rt_size_t size)
{
    rt_uintptr_t p;
    rt_size_t aligned;
    rt_uint32_t idx;

    if (!*ptr)
    {
        return;
    }

    p = (rt_uintptr_t)*ptr;
    aligned = RT_ALIGN(size, ASAN_SHADOW_SCALE);

    /* when realloc moves the block, poison the old block so that a stale
     * pointer to it is still detected as use-after-free */
    if (asan_realloc_old_ptr && asan_realloc_old_ptr != p)
    {
        idx = asan_track_find(asan_realloc_old_ptr);
        if (idx != RT_ASAN_TRACK_MAX)
        {
#if ASAN_POISON_FREED_BLOCK
            rt_size_t old_aligned = RT_ALIGN(asan_tracks[idx].size, ASAN_SHADOW_SCALE);

            asan_poison_range(asan_realloc_old_ptr, old_aligned);
#endif
            asan_tracks[idx].used = 0;
        }
    }

    /* address may have been reused internally by the allocator, drop any
     * stale use-after-free record for it */
    if (asan_last_freed.used && asan_last_freed.ptr == p)
    {
        asan_last_freed.used = 0;
    }

    /* track and unpoison the new block, poison its tail redzone */
    asan_track_add(p, size);
    asan_unpoison_range(p, size);
    if (aligned > size)
    {
        asan_poison_range(p + size, aligned - size);
    }
}

/*
 * Override the weak rt_system_heap_init to capture the heap range and
 * install the allocator hooks before the generic heap init runs.
 */
void rt_system_heap_init(void *begin_addr, void *end_addr)
{
    rt_uintptr_t begin = (rt_uintptr_t)begin_addr;
    rt_uintptr_t end = (rt_uintptr_t)end_addr;

    /*
     * The shadow maps one byte per ASAN_SHADOW_SCALE (8) bytes. Heap blocks
     * are RT_ALIGN_SIZE (8) aligned, so align the shadow base to the same
     * granularity to keep every block boundary on a shadow byte boundary.
     * Otherwise (e.g. __bss_end is only 4-aligned) the partial-granule
     * state cannot represent an addressable region and false positives occur
     * right at block start.
     */
    asan_heap_base = RT_ALIGN(begin, ASAN_SHADOW_SCALE);
    asan_heap_limit = ASAN_MIN(end, asan_heap_base +
                                        (rt_uintptr_t)sizeof(asan_shadow) * ASAN_SHADOW_SCALE);

    /*
     * Start with everything addressable: the heap allocators store their own
     * metadata (headers, free lists, the heap object itself) inside the heap
     * region, so an initially-poisoned shadow would report their internal
     * accesses as false positives. Detection is provided by poisoning the
     * block tail on allocation and the whole block on free instead.
     */
    rt_memset(asan_shadow, 0, sizeof(asan_shadow));

    /* install allocator hooks */
    rt_malloc_sethook(asan_malloc_hook);
    rt_free_sethook(asan_free_hook);
    rt_realloc_set_entry_hook(asan_realloc_entry_hook);
    rt_realloc_set_exit_hook(asan_realloc_exit_hook);

    /* run the original heap init */
    rt_system_heap_init_generic(begin_addr, end_addr);
}

#ifdef RT_USING_FINSH
#include <finsh.h>

static int asan_info(int argc, char **argv)
{
    rt_uint32_t i;
    rt_uint32_t active = 0;

    rt_kprintf("\n-- AddressSanitizer status --\n");
    rt_kprintf("shadow   : %p, %d bytes\n", asan_shadow, sizeof(asan_shadow));
    rt_kprintf("coverage : 0x%08x - 0x%08x (%d bytes)\n",
               asan_heap_base, asan_heap_limit,
               asan_heap_limit - asan_heap_base);

    if (asan_last_freed.used)
    {
        rt_kprintf("last free: 0x%08x size %d owner %.*s\n",
                   asan_last_freed.ptr, asan_last_freed.size,
                   RT_NAME_MAX, asan_last_freed.owner);
    }
    else
    {
        rt_kprintf("last free: (none)\n");
    }

    rt_kprintf("\n-- active allocations --\n");
    for (i = 0; i < RT_ASAN_TRACK_MAX; i++)
    {
        if (asan_tracks[i].used)
        {
            active++;
            rt_kprintf("  0x%08x  %6d  %.*s\n",
                       asan_tracks[i].ptr, asan_tracks[i].size,
                       RT_NAME_MAX, asan_tracks[i].owner);
        }
    }
    rt_kprintf("total: %d active blocks\n", active);

    return 0;
}
MSH_CMD_EXPORT(asan_info, dump AddressSanitizer status);
#endif /* RT_USING_FINSH */

#endif /* RT_USING_ASAN */
