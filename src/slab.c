/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * File      : slab.c
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-07-12     Bernard      the first version
 * 2010-07-13     Bernard      fix RT_ALIGN issue found by kuronca
 * 2010-10-23     yi.qiu       add module memory allocator
 * 2010-12-18     yi.qiu       fix zone release bug
 */

/*
 * KERN_SLABALLOC.C - Kernel SLAB memory allocator
 *
 * Copyright (c) 2003,2004 The DragonFly Project.  All rights reserved.
 *
 * This code is derived from software contributed to The DragonFly Project
 * by Matthew Dillon <dillon@backplane.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of The DragonFly Project nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <rthw.h>
#include <rtthread.h>

#if defined (RT_USING_SLAB)
/*
 * slab allocator implementation
 *
 * A slab allocator reserves a ZONE for each chunk size, then lays the
 * chunks out in an array within the zone.  Allocation and deallocation
 * is nearly instantanious, and fragmentation/overhead losses are limited
 * to a fixed worst-case amount.
 *
 * The downside of this slab implementation is in the chunk size
 * multiplied by the number of zones.  ~80 zones * 128K = 10MB of VM per cpu.
 * In a kernel implementation all this memory will be physical so
 * the zone size is adjusted downward on machines with less physical
 * memory.  The upside is that overhead is bounded... this is the *worst*
 * case overhead.
 *
 * Slab management is done on a per-cpu basis and no locking or mutexes
 * are required, only a critical section.  When one cpu frees memory
 * belonging to another cpu's slab manager an asynchronous IPI message
 * will be queued to execute the operation.   In addition, both the
 * high level slab allocator and the low level zone allocator optimize
 * M_ZERO requests, and the slab allocator does not have to pre initialize
 * the linked list of chunks.
 *
 * XXX Balancing is needed between cpus.  Balance will be handled through
 * asynchronous IPIs primarily by reassigning the z_Cpu ownership of chunks.
 *
 * XXX If we have to allocate a new zone and M_USE_RESERVE is set, use of
 * the new zone should be restricted to M_USE_RESERVE requests only.
 *
 *  Alloc Size  Chunking        Number of zones
 *  0-127       8               16
 *  128-255     16              8
 *  256-511     32              8
 *  512-1023    64              8
 *  1024-2047   128             8
 *  2048-4095   256             8
 *  4096-8191   512             8
 *  8192-16383  1024            8
 *  16384-32767 2048            8
 *  (if RT_MM_PAGE_SIZE is 4K the maximum zone allocation is 16383)
 *
 *  Allocations >= zone_limit go directly to kmem.
 *
 *          API REQUIREMENTS AND SIDE EFFECTS
 *
 *    To operate as a drop-in replacement to the FreeBSD-4.x malloc() we
 *    have remained compatible with the following API requirements:
 *
 *    + small power-of-2 sized allocations are power-of-2 aligned (kern_tty)
 *    + all power-of-2 sized allocations are power-of-2 aligned (twe)
 *    + malloc(0) is allowed and returns non-RT_NULL (ahc driver)
 *    + ability to allocate arbitrarily large chunks of memory
 */

#define ZALLOC_SLAB_MAGIC       0x51ab51ab
#define ZALLOC_ZONE_LIMIT       (16 * 1024)     /* max slab-managed alloc */
#define ZALLOC_MIN_ZONE_SIZE    (32 * 1024)     /* minimum zone size */
#define ZALLOC_MAX_ZONE_SIZE    (128 * 1024)    /* maximum zone size */
#define ZONE_RELEASE_THRESH     2               /* threshold number of zones */

/*
 * Misc constants.  Note that allocations that are exact multiples of
 * RT_MM_PAGE_SIZE, or exceed the zone limit, fall through to the kmem module.
 */
#define MIN_CHUNK_SIZE      8       /* in bytes */
#define MIN_CHUNK_MASK      (MIN_CHUNK_SIZE - 1)

/*
 * Array of descriptors that describe the contents of each page
 */
#define PAGE_TYPE_FREE      0x00
#define PAGE_TYPE_SMALL     0x01
#define PAGE_TYPE_LARGE     0x02

#define btokup(addr)    \
    (&slab->memusage[((rt_ubase_t)(addr) - slab->heap_start) >> RT_MM_PAGE_BITS])

/**
 * Base structure of slab memory object
 */

/*
 * The IN-BAND zone header is placed at the beginning of each zone.
 */
struct rt_slab_zone
{
    rt_uint32_t  z_magic;                    /**< magic number for sanity check */
    rt_uint32_t  z_nfree;                    /**< total free chunks / ualloc space in zone */
    rt_uint32_t  z_nmax;                     /**< maximum free chunks */
    struct rt_slab_zone *z_next;            /**< zoneary[] link if z_nfree non-zero */
    rt_uint8_t  *z_baseptr;                 /**< pointer to start of chunk array */

    rt_uint32_t  z_uindex;                   /**< current initial allocation index */
    rt_uint32_t  z_chunksize;                /**< chunk size for validation */

    rt_uint32_t  z_zoneindex;                /**< zone index */
    struct rt_slab_chunk  *z_freechunk;     /**< free chunk list */
};

/*
 * Chunk structure for free elements
 */
struct rt_slab_chunk
{
    struct rt_slab_chunk *c_next;
};

struct rt_slab_memusage
{
    rt_uint32_t     type: 2 ;               /**< page type */
    rt_uint32_t     size: 30;               /**< pages allocated or offset from zone */
};

/*
 * slab page allocator
 */
struct rt_slab_page
{
    struct rt_slab_page *next;      /**< next valid page */
    rt_size_t page;                 /**< number of page  */

    /* dummy */
    char dummy[RT_MM_PAGE_SIZE - (sizeof(struct rt_slab_page *) + sizeof(rt_size_t))];
};

#define RT_SLAB_NZONES                  72              /* number of zones */

/*
 * slab object
 */
struct rt_slab
{
    struct rt_memory            parent;                         /**< inherit from rt_memory */
    rt_ubase_t                  heap_start;                     /**< memory start address */
    rt_ubase_t                  heap_end;                       /**< memory end address */
    struct rt_slab_memusage    *memusage;
    struct rt_slab_zone        *zone_array[RT_SLAB_NZONES];     /* linked list of zones NFree > 0 */
    struct rt_slab_zone        *zone_free;                      /* whole zones that have become free */
    rt_uint32_t                 zone_free_cnt;
    rt_uint32_t                 zone_size;
    rt_uint32_t                 zone_limit;
    rt_uint32_t                 zone_page_cnt;
    struct rt_slab_page        *page_list;
};

/**
 * @brief Alloc memory size by page.
 *
 * @param m the slab memory management object.
 *
 * @param npages the number of pages.
 */
void *rt_slab_page_alloc(rt_slab_t m, rt_size_t npages)
{
    struct rt_slab_page *b, *n;
    struct rt_slab_page **prev;
    struct rt_slab *slab = (struct rt_slab *)m;

    if (npages == 0)
        return RT_NULL;

    for (prev = &slab->page_list; (b = *prev) != RT_NULL; prev = &(b->next))
    {
        if (b->page > npages)
        {
            /* splite pages */
            n       = b + npages;
            n->next = b->next;
            n->page = b->page - npages;
            *prev   = n;
            break;
        }

        if (b->page == npages)
        {
            /* this node fit, remove this node */
            *prev = b->next;
            break;
        }
    }

    return b;
}

/**
 * @brief Free memory by page.
 *
 * @param m the slab memory management object.
 *
 * @param addr is the head address of first page.
 *
 * @param npages is the number of pages.
 */
void rt_slab_page_free(rt_slab_t m, void *addr, rt_size_t npages)
{
    struct rt_slab_page *b, *n;
    struct rt_slab_page **prev;
    struct rt_slab *slab = (struct rt_slab *)m;

    RT_ASSERT(addr != RT_NULL);
    RT_ASSERT((rt_ubase_t)addr % RT_MM_PAGE_SIZE == 0);
    RT_ASSERT(npages != 0);

    n = (struct rt_slab_page *)addr;

    for (prev = &slab->page_list; (b = *prev) != RT_NULL; prev = &(b->next))
    {
        RT_ASSERT(b->page > 0);
        RT_ASSERT(b > n || b + b->page <= n);

        if (b + b->page == n)
        {
            if (b + (b->page += npages) == b->next)
            {
                b->page += b->next->page;
                b->next  = b->next->next;
            }
            return;
        }

        if (b == n + npages)
        {
            n->page = b->page + npages;
            n->next = b->next;
            *prev   = n;
            return;
        }

        if (b > n + npages)
            break;
    }

    n->page = npages;
    n->next = b;
    *prev   = n;
}

/*
 * Initialize the page allocator
 */
static void rt_slab_page_init(struct rt_slab *slab, void *addr, rt_size_t npages)
{
    RT_ASSERT(addr != RT_NULL);
    RT_ASSERT(npages != 0);

    slab->page_list = RT_NULL;
    rt_slab_page_free((rt_slab_t)(&slab->parent), addr, npages);
}

/**
 * @brief This function will init slab memory management algorithm
 *
 * @param name is the name of the slab memory management object.
 *
 * @param begin_addr the beginning address of system page.
 *
 * @param size is the size of the memory.
 *
 * @return Return a pointer to the slab memory object.
 */
rt_slab_t rt_slab_init(const char *name, void *begin_addr, rt_size_t size)
{
    rt_uint32_t limsize, npages;
    rt_ubase_t start_addr, begin_align, end_align;
    struct rt_slab *slab;

    slab = (struct rt_slab *)RT_ALIGN((rt_ubase_t)begin_addr, RT_ALIGN_SIZE);
    start_addr = (rt_ubase_t)slab + sizeof(*slab);
    /* align begin and end addr to page */
    begin_align = RT_ALIGN((rt_ubase_t)start_addr, RT_MM_PAGE_SIZE);
    end_align   = RT_ALIGN_DOWN((rt_ubase_t)begin_addr + size, RT_MM_PAGE_SIZE);
    if (begin_align >= end_align)
    {
        rt_kprintf("slab init errr. wrong address[0x%x - 0x%x]\n",
                   (rt_ubase_t)begin_addr, (rt_ubase_t)begin_addr + size);
        return RT_NULL;
    }

    limsize = end_align - begin_align;
    npages  = limsize / RT_MM_PAGE_SIZE;
    RT_DEBUG_LOG(RT_DEBUG_SLAB, ("heap[0x%x - 0x%x], size 0x%x, 0x%x pages\n",
                                begin_align, end_align, limsize, npages));

    rt_memset(slab, 0, sizeof(*slab));
    /* initialize slab memory object */
    rt_object_init(&(slab->parent.parent), RT_Object_Class_Memory, name);
    slab->parent.algorithm = "slab";
    slab->parent.address = begin_align;
    slab->parent.total = limsize;
    slab->parent.used = 0;
    slab->parent.max = 0;
    slab->heap_start = begin_align;
    slab->heap_end = end_align;

    /* init pages */
    rt_slab_page_init(slab, (void *)slab->heap_start, npages);

    /* calculate zone size */
    slab->zone_size = ZALLOC_MIN_ZONE_SIZE;
    while (slab->zone_size < ZALLOC_MAX_ZONE_SIZE && (slab->zone_size << 1) < (limsize / 1024))
        slab->zone_size <<= 1;

    slab->zone_limit = slab->zone_size / 4;
    if (slab->zone_limit > ZALLOC_ZONE_LIMIT)
        slab->zone_limit = ZALLOC_ZONE_LIMIT;

    slab->zone_page_cnt = slab->zone_size / RT_MM_PAGE_SIZE;

    RT_DEBUG_LOG(RT_DEBUG_SLAB, ("zone size 0x%x, zone page count 0x%x\n",
                                 slab->zone_size, slab->zone_page_cnt));

    /* allocate slab->memusage array */
    limsize  = npages * sizeof(struct rt_slab_memusage);
    limsize  = RT_ALIGN(limsize, RT_MM_PAGE_SIZE);
    slab->memusage = rt_slab_page_alloc((rt_slab_t)(&slab->parent), limsize / RT_MM_PAGE_SIZE);

    RT_DEBUG_LOG(RT_DEBUG_SLAB, ("slab->memusage 0x%x, size 0x%x\n",
                                 (rt_ubase_t)slab->memusage, limsize));
    return &slab->parent;
}
RTM_EXPORT(rt_slab_init);

/**
 * @brief This function will remove a slab object from the system.
 *
 * @param m the slab memory management object.
 *
 * @return RT_EOK
 */
rt_err_t rt_slab_detach(rt_slab_t m)
{
    struct rt_slab *slab = (struct rt_slab *)m;

    RT_ASSERT(slab != RT_NULL);
    RT_ASSERT(rt_object_get_type(&slab->parent.parent) == RT_Object_Class_Memory);
    RT_ASSERT(rt_object_is_systemobject(&slab->parent.parent));

    rt_object_detach(&(slab->parent.parent));

    return RT_EOK;
}
RTM_EXPORT(rt_slab_detach);

/*
 * Calculate the zone index for the allocation request size and set the
 * allocation request size to that particular zone's chunk size.
 */
rt_inline int zoneindex(rt_size_t *bytes)
{
    /* unsigned for shift opt */
    rt_ubase_t n = (rt_ubase_t)(*bytes);

    if (n < 128)
    {
        *bytes = n = (n + 7) & ~7;

        /* 8 byte chunks, 16 zones */
        return (n / 8 - 1);
    }
    if (n < 256)
    {
        *bytes = n = (n + 15) & ~15;

        return (n / 16 + 7);
    }
    if (n < 8192)
    {
        if (n < 512)
        {
            *bytes = n = (n + 31) & ~31;

            return (n / 32 + 15);
        }
        if (n < 1024)
        {
            *bytes = n = (n + 63) & ~63;

            return (n / 64 + 23);
        }
        if (n < 2048)
        {
            *bytes = n = (n + 127) & ~127;

            return (n / 128 + 31);
        }
        if (n < 4096)
        {
            *bytes = n = (n + 255) & ~255;

            return (n / 256 + 39);
        }
        *bytes = n = (n + 511) & ~511;

        return (n / 512 + 47);
    }
    if (n < 16384)
    {
        *bytes = n = (n + 1023) & ~1023;

        return (n / 1024 + 55);
    }

    rt_kprintf("Unexpected byte count %d", n);

    return 0;
}

/**
 * @addtogroup MM
 */

/**@{*/

/**
 * @brief This function will allocate a block from slab object.
 *
 * @note the RT_NULL is returned if
 *         - the nbytes is less than zero.
 *         - there is no nbytes sized memory valid in system.
 *
 * @param m the slab memory management object.
 *
 * @param size is the size of memory to be allocated.
 *
 * @return the allocated memory.
 */
void *rt_slab_alloc(rt_slab_t m, rt_size_t size)
{
    struct rt_slab_zone *z;
    rt_int32_t zi;
    struct rt_slab_chunk *chunk;
    struct rt_slab_memusage *kup;
    struct rt_slab *slab = (struct rt_slab *)m;

    /* zero size, return RT_NULL */
    if (size == 0)
        return RT_NULL;

    /*
     * Handle large allocations directly.  There should not be very many of
     * these so performance is not a big issue.
     */
    if (size >= slab->zone_limit)
    {
        size = RT_ALIGN(size, RT_MM_PAGE_SIZE);

        chunk = rt_slab_page_alloc(m, size >> RT_MM_PAGE_BITS);
        if (chunk == RT_NULL)
            return RT_NULL;

        /* set kup */
        kup = btokup(chunk);
        kup->type = PAGE_TYPE_LARGE;
        kup->size = size >> RT_MM_PAGE_BITS;

        RT_DEBUG_LOG(RT_DEBUG_SLAB,
                     ("alloc a large memory 0x%x, page cnt %d, kup %d\n",
                      size,
                      size >> RT_MM_PAGE_BITS,
                      ((rt_ubase_t)chunk - slab->heap_start) >> RT_MM_PAGE_BITS));
        /* mem stat */
        slab->parent.used += size;
        if (slab->parent.used > slab->parent.max)
            slab->parent.max = slab->parent.used;
        return chunk;
    }

    /*
     * Attempt to allocate out of an existing zone.  First try the free list,
     * then allocate out of unallocated space.  If we find a good zone move
     * it to the head of the list so later allocations find it quickly
     * (we might have thousands of zones in the list).
     *
     * Note: zoneindex() will panic of size is too large.
     */
    zi = zoneindex(&size);
    RT_ASSERT(zi < RT_SLAB_NZONES);

    RT_DEBUG_LOG(RT_DEBUG_SLAB, ("try to alloc 0x%x on zone: %d\n", size, zi));

    if ((z = slab->zone_array[zi]) != RT_NULL)
    {
        RT_ASSERT(z->z_nfree > 0);

        /* Remove us from the zone_array[] when we become full */
        if (--z->z_nfree == 0)
        {
            slab->zone_array[zi] = z->z_next;
            z->z_next = RT_NULL;
        }

        /*
         * No chunks are available but nfree said we had some memory, so
         * it must be available in the never-before-used-memory area
         * governed by uindex.  The consequences are very serious if our zone
         * got corrupted so we use an explicit rt_kprintf rather then a KASSERT.
         */
        if (z->z_uindex + 1 != z->z_nmax)
        {
            z->z_uindex = z->z_uindex + 1;
            chunk = (struct rt_slab_chunk *)(z->z_baseptr + z->z_uindex * size);
        }
        else
        {
            /* find on free chunk list */
            chunk = z->z_freechunk;

            /* remove this chunk from list */
            z->z_freechunk = z->z_freechunk->c_next;
        }
        /* mem stats */
        slab->parent.used += z->z_chunksize;
        if (slab->parent.used > slab->parent.max)
            slab->parent.max = slab->parent.used;

        return chunk;
    }

    /*
     * If all zones are exhausted we need to allocate a new zone for this
     * index.
     *
     * At least one subsystem, the tty code (see CROUND) expects power-of-2
     * allocations to be power-of-2 aligned.  We maintain compatibility by
     * adjusting the base offset below.
     */
    {
        rt_uint32_t off;

        if ((z = slab->zone_free) != RT_NULL)
        {
            /* remove zone from free zone list */
            slab->zone_free = z->z_next;
            -- slab->zone_free_cnt;
        }
        else
        {
            /* allocate a zone from page */
            z = rt_slab_page_alloc(m, slab->zone_size / RT_MM_PAGE_SIZE);
            if (z == RT_NULL)
            {
                return RT_NULL;
            }

            RT_DEBUG_LOG(RT_DEBUG_SLAB, ("alloc a new zone: 0x%x\n",
                                         (rt_ubase_t)z));

            /* set message usage */
            for (off = 0, kup = btokup(z); off < slab->zone_page_cnt; off ++)
            {
                kup->type = PAGE_TYPE_SMALL;
                kup->size = off;

                kup ++;
            }
        }

        /* clear to zero */
        rt_memset(z, 0, sizeof(struct rt_slab_zone));

        /* offset of slab zone struct in zone */
        off = sizeof(struct rt_slab_zone);

        /*
         * Guarentee power-of-2 alignment for power-of-2-sized chunks.
         * Otherwise just 8-byte align the data.
         */
        if ((size | (size - 1)) + 1 == (size << 1))
            off = (off + size - 1) & ~(size - 1);
        else
            off = (off + MIN_CHUNK_MASK) & ~MIN_CHUNK_MASK;

        z->z_magic     = ZALLOC_SLAB_MAGIC;
        z->z_zoneindex = zi;
        z->z_nmax      = (slab->zone_size - off) / size;
        z->z_nfree     = z->z_nmax - 1;
        z->z_baseptr   = (rt_uint8_t *)z + off;
        z->z_uindex    = 0;
        z->z_chunksize = size;

        chunk = (struct rt_slab_chunk *)(z->z_baseptr + z->z_uindex * size);

        /* link to zone array */
        z->z_next = slab->zone_array[zi];
        slab->zone_array[zi] = z;
        /* mem stats */
        slab->parent.used += z->z_chunksize;
        if (slab->parent.used > slab->parent.max)
            slab->parent.max = slab->parent.used;
    }

    return chunk;
}
RTM_EXPORT(rt_slab_alloc);

/**
 * @brief This function will change the size of previously allocated memory block.
 *
 * @param m the slab memory management object.
 *
 * @param ptr is the previously allocated memory block.
 *
 * @param size is the new size of memory block.
 *
 * @return the allocated memory.
 */
void *rt_slab_realloc(rt_slab_t m, void *ptr, rt_size_t size)
{
    void *nptr;
    struct rt_slab_zone *z;
    struct rt_slab_memusage *kup;
    struct rt_slab *slab = (struct rt_slab *)m;

    if (ptr == RT_NULL)
        return rt_slab_alloc(m, size);

    if (size == 0)
    {
        rt_slab_free(m, ptr);
        return RT_NULL;
    }

    /*
     * Get the original allocation's zone.  If the new request winds up
     * using the same chunk size we do not have to do anything.
     */
    kup = btokup((rt_ubase_t)ptr & ~RT_MM_PAGE_MASK);
    if (kup->type == PAGE_TYPE_LARGE)
    {
        rt_size_t osize;

        osize = kup->size << RT_MM_PAGE_BITS;
        if ((nptr = rt_slab_alloc(m, size)) == RT_NULL)
            return RT_NULL;
        rt_memcpy(nptr, ptr, size > osize ? osize : size);
        rt_slab_free(m, ptr);

        return nptr;
    }
    else if (kup->type == PAGE_TYPE_SMALL)
    {
        z = (struct rt_slab_zone *)(((rt_ubase_t)ptr & ~RT_MM_PAGE_MASK) -
                          kup->size * RT_MM_PAGE_SIZE);
        RT_ASSERT(z->z_magic == ZALLOC_SLAB_MAGIC);

        zoneindex(&size);
        if (z->z_chunksize == size)
            return (ptr); /* same chunk */

        /*
         * Allocate memory for the new request size.  Note that zoneindex has
         * already adjusted the request size to the appropriate chunk size, which
         * should optimize our bcopy().  Then copy and return the new pointer.
         */
        if ((nptr = rt_slab_alloc(m, size)) == RT_NULL)
            return RT_NULL;

        rt_memcpy(nptr, ptr, size > z->z_chunksize ? z->z_chunksize : size);
        rt_slab_free(m, ptr);

        return nptr;
    }

    return RT_NULL;
}
RTM_EXPORT(rt_slab_realloc);

/**
 * @brief This function will release the previous allocated memory block by rt_slab_alloc.
 *
 * @note The released memory block is taken back to system heap.
 *
 * @param m the slab memory management object.
 * @param ptr is the address of memory which will be released
 */
void rt_slab_free(rt_slab_t m, void *ptr)
{
    struct rt_slab_zone *z;
    struct rt_slab_chunk *chunk;
    struct rt_slab_memusage *kup;
    struct rt_slab *slab = (struct rt_slab *)m;

    /* free a RT_NULL pointer */
    if (ptr == RT_NULL)
        return ;

    /* get memory usage */
#if RT_DEBUG_SLAB
    {
        rt_ubase_t addr = ((rt_ubase_t)ptr & ~RT_MM_PAGE_MASK);
        RT_DEBUG_LOG(RT_DEBUG_SLAB,
                     ("free a memory 0x%x and align to 0x%x, kup index %d\n",
                      (rt_ubase_t)ptr,
                      (rt_ubase_t)addr,
                      ((rt_ubase_t)(addr) - slab->heap_start) >> RT_MM_PAGE_BITS));
    }
#endif /* RT_DEBUG_SLAB */

    kup = btokup((rt_ubase_t)ptr & ~RT_MM_PAGE_MASK);
    /* release large allocation */
    if (kup->type == PAGE_TYPE_LARGE)
    {
        rt_ubase_t size;

        /* clear page counter */
        size = kup->size;
        kup->size = 0;
        /* mem stats */
        slab->parent.used -= size * RT_MM_PAGE_SIZE;

        RT_DEBUG_LOG(RT_DEBUG_SLAB,
                     ("free large memory block 0x%x, page count %d\n",
                      (rt_ubase_t)ptr, size));

        /* free this page */
        rt_slab_page_free(m, ptr, size);

        return;
    }

    /* zone case. get out zone. */
    z = (struct rt_slab_zone *)(((rt_ubase_t)ptr & ~RT_MM_PAGE_MASK) -
                      kup->size * RT_MM_PAGE_SIZE);
    RT_ASSERT(z->z_magic == ZALLOC_SLAB_MAGIC);

    chunk          = (struct rt_slab_chunk *)ptr;
    chunk->c_next  = z->z_freechunk;
    z->z_freechunk = chunk;
    /* mem stats */
    slab->parent.used -= z->z_chunksize;

    /*
     * Bump the number of free chunks.  If it becomes non-zero the zone
     * must be added back onto the appropriate list.
     */
    if (z->z_nfree++ == 0)
    {
        z->z_next = slab->zone_array[z->z_zoneindex];
        slab->zone_array[z->z_zoneindex] = z;
    }

    /*
     * If the zone becomes totally free, and there are other zones we
     * can allocate from, move this zone to the FreeZones list.  Since
     * this code can be called from an IPI callback, do *NOT* try to mess
     * with kernel_map here.  Hysteresis will be performed at malloc() time.
     */
    if (z->z_nfree == z->z_nmax &&
        (z->z_next || slab->zone_array[z->z_zoneindex] != z))
    {
        struct rt_slab_zone **pz;

        RT_DEBUG_LOG(RT_DEBUG_SLAB, ("free zone 0x%x\n",
                                     (rt_ubase_t)z, z->z_zoneindex));

        /* remove zone from zone array list */
        for (pz = &slab->zone_array[z->z_zoneindex]; z != *pz; pz = &(*pz)->z_next)
            ;
        *pz = z->z_next;

        /* reset zone */
        z->z_magic = RT_UINT32_MAX;

        /* insert to free zone list */
        z->z_next = slab->zone_free;
        slab->zone_free = z;

        ++ slab->zone_free_cnt;

        /* release zone to page allocator */
        if (slab->zone_free_cnt > ZONE_RELEASE_THRESH)
        {
            register rt_uint32_t i;

            z         = slab->zone_free;
            slab->zone_free = z->z_next;
            -- slab->zone_free_cnt;

            /* set message usage */
            for (i = 0, kup = btokup(z); i < slab->zone_page_cnt; i ++)
            {
                kup->type = PAGE_TYPE_FREE;
                kup->size = 0;
                kup ++;
            }

            /* release pages */
            rt_slab_page_free(m, z, slab->zone_size / RT_MM_PAGE_SIZE);

            return;
        }
    }
}
RTM_EXPORT(rt_slab_free);

#endif /* defined (RT_USING_SLAB) */
