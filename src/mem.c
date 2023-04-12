/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-7-12      Bernard      the first version
 * 2010-06-09     Bernard      fix the end stub of heap
 *                             fix memory check in rt_realloc function
 * 2010-07-13     Bernard      fix RT_ALIGN issue found by kuronca
 * 2010-10-14     Bernard      fix rt_realloc issue when realloc a NULL pointer.
 * 2017-07-14     armink       fix rt_realloc issue when new size is 0
 * 2018-10-02     Bernard      Add 64bit support
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *         Simon Goldschmidt
 *
 */

#include <rthw.h>
#include <rtthread.h>

#if defined (RT_USING_SMALL_MEM)
 /**
  * memory item on the small mem
  */
struct rt_small_mem_item
{
    rt_ubase_t              pool_ptr;         /**< small memory object addr */
#ifdef ARCH_CPU_64BIT
    rt_uint32_t             resv;
#endif /* ARCH_CPU_64BIT */
    rt_size_t               next;             /**< next free item */
    rt_size_t               prev;             /**< prev free item */
#ifdef RT_USING_MEMTRACE
#ifdef ARCH_CPU_64BIT
    rt_uint8_t              thread[8];       /**< thread name */
#else
    rt_uint8_t              thread[4];       /**< thread name */
#endif /* ARCH_CPU_64BIT */
#endif /* RT_USING_MEMTRACE */
};

/**
 * Base structure of small memory object
 */
struct rt_small_mem
{
    struct rt_memory            parent;                 /**< inherit from rt_memory */
    rt_uint8_t                 *heap_ptr;               /**< pointer to the heap */
    struct rt_small_mem_item   *heap_end;
    struct rt_small_mem_item   *lfree;
    rt_size_t                   mem_size_aligned;       /**< aligned memory size */
};

#define HEAP_MAGIC 0x1ea0

#ifdef ARCH_CPU_64BIT
#define MIN_SIZE 24
#else
#define MIN_SIZE 12
#endif /* ARCH_CPU_64BIT */

#define MEM_MASK             0xfffffffe
#define MEM_USED()         ((((rt_base_t)(small_mem)) & MEM_MASK) | 0x1)
#define MEM_FREED()        ((((rt_base_t)(small_mem)) & MEM_MASK) | 0x0)
#define MEM_ISUSED(_mem)   \
                      (((rt_base_t)(((struct rt_small_mem_item *)(_mem))->pool_ptr)) & (~MEM_MASK))
#define MEM_POOL(_mem)     \
    ((struct rt_small_mem *)(((rt_base_t)(((struct rt_small_mem_item *)(_mem))->pool_ptr)) & (MEM_MASK)))
#define MEM_SIZE(_heap, _mem)      \
    (((struct rt_small_mem_item *)(_mem))->next - ((rt_ubase_t)(_mem) - \
    (rt_ubase_t)((_heap)->heap_ptr)) - RT_ALIGN(sizeof(struct rt_small_mem_item), RT_ALIGN_SIZE))

#define MIN_SIZE_ALIGNED     RT_ALIGN(MIN_SIZE, RT_ALIGN_SIZE)
#define SIZEOF_STRUCT_MEM    RT_ALIGN(sizeof(struct rt_small_mem_item), RT_ALIGN_SIZE)

#ifdef RT_USING_MEMTRACE
rt_inline void rt_smem_setname(struct rt_small_mem_item *mem, const char *name)
{
    int index;
    for (index = 0; index < sizeof(mem->thread); index ++)
    {
        if (name[index] == '\0') break;
        mem->thread[index] = name[index];
    }

    for (; index < sizeof(mem->thread); index ++)
    {
        mem->thread[index] = ' ';
    }
}
#endif /* RT_USING_MEMTRACE */

static void plug_holes(struct rt_small_mem *m, struct rt_small_mem_item *mem)
{
    struct rt_small_mem_item *nmem;
    struct rt_small_mem_item *pmem;

    RT_ASSERT((rt_uint8_t *)mem >= m->heap_ptr);
    RT_ASSERT((rt_uint8_t *)mem < (rt_uint8_t *)m->heap_end);

    /* plug hole forward */
    nmem = (struct rt_small_mem_item *)&m->heap_ptr[mem->next];
    if (mem != nmem && !MEM_ISUSED(nmem) &&
        (rt_uint8_t *)nmem != (rt_uint8_t *)m->heap_end)
    {
        /* if mem->next is unused and not end of m->heap_ptr,
         * combine mem and mem->next
         */
        if (m->lfree == nmem)
        {
            m->lfree = mem;
        }
        nmem->pool_ptr = 0;
        mem->next = nmem->next;
        ((struct rt_small_mem_item *)&m->heap_ptr[nmem->next])->prev = (rt_uint8_t *)mem - m->heap_ptr;
    }

    /* plug hole backward */
    pmem = (struct rt_small_mem_item *)&m->heap_ptr[mem->prev];
    if (pmem != mem && !MEM_ISUSED(pmem))
    {
        /* if mem->prev is unused, combine mem and mem->prev */
        if (m->lfree == mem)
        {
            m->lfree = pmem;
        }
        mem->pool_ptr = 0;
        pmem->next = mem->next;
        ((struct rt_small_mem_item *)&m->heap_ptr[mem->next])->prev = (rt_uint8_t *)pmem - m->heap_ptr;
    }
}

/**
 * @brief This function will initialize small memory management algorithm.
 *
 * @param name is the name of the small memory management object.
 *
 * @param begin_addr the beginning address of memory.
 *
 * @param size is the size of the memory.
 *
 * @return Return a pointer to the memory object. When the return value is RT_NULL, it means the init failed.
 */
rt_smem_t rt_smem_init(const char    *name,
                     void          *begin_addr,
                     rt_size_t      size)
{
    struct rt_small_mem_item *mem;
    struct rt_small_mem *small_mem;
    rt_ubase_t start_addr, begin_align, end_align, mem_size;

    small_mem = (struct rt_small_mem *)RT_ALIGN((rt_ubase_t)begin_addr, RT_ALIGN_SIZE);
    start_addr = (rt_ubase_t)small_mem + sizeof(*small_mem);
    begin_align = RT_ALIGN((rt_ubase_t)start_addr, RT_ALIGN_SIZE);
    end_align   = RT_ALIGN_DOWN((rt_ubase_t)begin_addr + size, RT_ALIGN_SIZE);

    /* alignment addr */
    if ((end_align > (2 * SIZEOF_STRUCT_MEM)) &&
        ((end_align - 2 * SIZEOF_STRUCT_MEM) >= start_addr))
    {
        /* calculate the aligned memory size */
        mem_size = end_align - begin_align - 2 * SIZEOF_STRUCT_MEM;
    }
    else
    {
        rt_kprintf("mem init, error begin address 0x%x, and end address 0x%x\n",
                   (rt_ubase_t)begin_addr, (rt_ubase_t)begin_addr + size);

        return RT_NULL;
    }

    rt_memset(small_mem, 0, sizeof(*small_mem));
    /* initialize small memory object */
    rt_object_init(&(small_mem->parent.parent), RT_Object_Class_Memory, name);
    small_mem->parent.algorithm = "small";
    small_mem->parent.address = begin_align;
    small_mem->parent.total = mem_size;
    small_mem->mem_size_aligned = mem_size;

    /* point to begin address of heap */
    small_mem->heap_ptr = (rt_uint8_t *)begin_align;

    RT_DEBUG_LOG(RT_DEBUG_MEM, ("mem init, heap begin address 0x%x, size %d\n",
                                (rt_ubase_t)small_mem->heap_ptr, small_mem->mem_size_aligned));

    /* initialize the start of the heap */
    mem        = (struct rt_small_mem_item *)small_mem->heap_ptr;
    mem->pool_ptr = MEM_FREED();
    mem->next  = small_mem->mem_size_aligned + SIZEOF_STRUCT_MEM;
    mem->prev  = 0;
#ifdef RT_USING_MEMTRACE
    rt_smem_setname(mem, "INIT");
#endif /* RT_USING_MEMTRACE */

    /* initialize the end of the heap */
    small_mem->heap_end        = (struct rt_small_mem_item *)&small_mem->heap_ptr[mem->next];
    small_mem->heap_end->pool_ptr = MEM_USED();
    small_mem->heap_end->next  = small_mem->mem_size_aligned + SIZEOF_STRUCT_MEM;
    small_mem->heap_end->prev  = small_mem->mem_size_aligned + SIZEOF_STRUCT_MEM;
#ifdef RT_USING_MEMTRACE
    rt_smem_setname(small_mem->heap_end, "INIT");
#endif /* RT_USING_MEMTRACE */

    /* initialize the lowest-free pointer to the start of the heap */
    small_mem->lfree = (struct rt_small_mem_item *)small_mem->heap_ptr;

    return &small_mem->parent;
}
RTM_EXPORT(rt_smem_init);

/**
 * @brief This function will remove a small mem from the system.
 *
 * @param m the small memory management object.
 *
 * @return RT_EOK
 */
rt_err_t rt_smem_detach(rt_smem_t m)
{
    RT_ASSERT(m != RT_NULL);
    RT_ASSERT(rt_object_get_type(&m->parent) == RT_Object_Class_Memory);
    RT_ASSERT(rt_object_is_systemobject(&m->parent));

    rt_object_detach(&(m->parent));

    return RT_EOK;
}
RTM_EXPORT(rt_smem_detach);

/**
 * @addtogroup MM
 */

/**@{*/

/**
 * @brief Allocate a block of memory with a minimum of 'size' bytes.
 *
 * @param m the small memory management object.
 *
 * @param size is the minimum size of the requested block in bytes.
 *
 * @return the pointer to allocated memory or NULL if no free memory was found.
 */
void *rt_smem_alloc(rt_smem_t m, rt_size_t size)
{
    rt_size_t ptr, ptr2;
    struct rt_small_mem_item *mem, *mem2;
    struct rt_small_mem *small_mem;

    if (size == 0)
        return RT_NULL;

    RT_ASSERT(m != RT_NULL);
    RT_ASSERT(rt_object_get_type(&m->parent) == RT_Object_Class_Memory);
    RT_ASSERT(rt_object_is_systemobject(&m->parent));

    if (size != RT_ALIGN(size, RT_ALIGN_SIZE))
    {
        RT_DEBUG_LOG(RT_DEBUG_MEM, ("malloc size %d, but align to %d\n",
                                    size, RT_ALIGN(size, RT_ALIGN_SIZE)));
    }
    else
    {
        RT_DEBUG_LOG(RT_DEBUG_MEM, ("malloc size %d\n", size));
    }

    small_mem = (struct rt_small_mem *)m;
    /* alignment size */
    size = RT_ALIGN(size, RT_ALIGN_SIZE);

    /* every data block must be at least MIN_SIZE_ALIGNED long */
    if (size < MIN_SIZE_ALIGNED)
        size = MIN_SIZE_ALIGNED;

    if (size > small_mem->mem_size_aligned)
    {
        RT_DEBUG_LOG(RT_DEBUG_MEM, ("no memory\n"));

        return RT_NULL;
    }

    for (ptr = (rt_uint8_t *)small_mem->lfree - small_mem->heap_ptr;
         ptr <= small_mem->mem_size_aligned - size;
         ptr = ((struct rt_small_mem_item *)&small_mem->heap_ptr[ptr])->next)
    {
        mem = (struct rt_small_mem_item *)&small_mem->heap_ptr[ptr];

        if ((!MEM_ISUSED(mem)) && (mem->next - (ptr + SIZEOF_STRUCT_MEM)) >= size)
        {
            /* mem is not used and at least perfect fit is possible:
             * mem->next - (ptr + SIZEOF_STRUCT_MEM) gives us the 'user data size' of mem */

            if (mem->next - (ptr + SIZEOF_STRUCT_MEM) >=
                (size + SIZEOF_STRUCT_MEM + MIN_SIZE_ALIGNED))
            {
                /* (in addition to the above, we test if another struct rt_small_mem_item (SIZEOF_STRUCT_MEM) containing
                 * at least MIN_SIZE_ALIGNED of data also fits in the 'user data space' of 'mem')
                 * -> split large block, create empty remainder,
                 * remainder must be large enough to contain MIN_SIZE_ALIGNED data: if
                 * mem->next - (ptr + (2*SIZEOF_STRUCT_MEM)) == size,
                 * struct rt_small_mem_item would fit in but no data between mem2 and mem2->next
                 * @todo we could leave out MIN_SIZE_ALIGNED. We would create an empty
                 *       region that couldn't hold data, but when mem->next gets freed,
                 *       the 2 regions would be combined, resulting in more free memory
                 */
                ptr2 = ptr + SIZEOF_STRUCT_MEM + size;

                /* create mem2 struct */
                mem2       = (struct rt_small_mem_item *)&small_mem->heap_ptr[ptr2];
                mem2->pool_ptr = MEM_FREED();
                mem2->next = mem->next;
                mem2->prev = ptr;
#ifdef RT_USING_MEMTRACE
                rt_smem_setname(mem2, "    ");
#endif /* RT_USING_MEMTRACE */

                /* and insert it between mem and mem->next */
                mem->next = ptr2;

                if (mem2->next != small_mem->mem_size_aligned + SIZEOF_STRUCT_MEM)
                {
                    ((struct rt_small_mem_item *)&small_mem->heap_ptr[mem2->next])->prev = ptr2;
                }
                small_mem->parent.used += (size + SIZEOF_STRUCT_MEM);
                if (small_mem->parent.max < small_mem->parent.used)
                    small_mem->parent.max = small_mem->parent.used;
            }
            else
            {
                /* (a mem2 struct does no fit into the user data space of mem and mem->next will always
                 * be used at this point: if not we have 2 unused structs in a row, plug_holes should have
                 * take care of this).
                 * -> near fit or excact fit: do not split, no mem2 creation
                 * also can't move mem->next directly behind mem, since mem->next
                 * will always be used at this point!
                 */
                small_mem->parent.used += mem->next - ((rt_uint8_t *)mem - small_mem->heap_ptr);
                if (small_mem->parent.max < small_mem->parent.used)
                    small_mem->parent.max = small_mem->parent.used;
            }
            /* set small memory object */
            mem->pool_ptr = MEM_USED();
#ifdef RT_USING_MEMTRACE
            if (rt_thread_self())
                rt_smem_setname(mem, rt_thread_self()->parent.name);
            else
                rt_smem_setname(mem, "NONE");
#endif /* RT_USING_MEMTRACE */

            if (mem == small_mem->lfree)
            {
                /* Find next free block after mem and update lowest free pointer */
                while (MEM_ISUSED(small_mem->lfree) && small_mem->lfree != small_mem->heap_end)
                    small_mem->lfree = (struct rt_small_mem_item *)&small_mem->heap_ptr[small_mem->lfree->next];

                RT_ASSERT(((small_mem->lfree == small_mem->heap_end) || (!MEM_ISUSED(small_mem->lfree))));
            }
            RT_ASSERT((rt_ubase_t)mem + SIZEOF_STRUCT_MEM + size <= (rt_ubase_t)small_mem->heap_end);
            RT_ASSERT((rt_ubase_t)((rt_uint8_t *)mem + SIZEOF_STRUCT_MEM) % RT_ALIGN_SIZE == 0);
            RT_ASSERT((((rt_ubase_t)mem) & (RT_ALIGN_SIZE - 1)) == 0);

            RT_DEBUG_LOG(RT_DEBUG_MEM,
                         ("allocate memory at 0x%x, size: %d\n",
                          (rt_ubase_t)((rt_uint8_t *)mem + SIZEOF_STRUCT_MEM),
                          (rt_ubase_t)(mem->next - ((rt_uint8_t *)mem - small_mem->heap_ptr))));

            /* return the memory data except mem struct */
            return (rt_uint8_t *)mem + SIZEOF_STRUCT_MEM;
        }
    }

    return RT_NULL;
}
RTM_EXPORT(rt_smem_alloc);

/**
 * @brief This function will change the size of previously allocated memory block.
 *
 * @param m the small memory management object.
 *
 * @param rmem is the pointer to memory allocated by rt_mem_alloc.
 *
 * @param newsize is the required new size.
 *
 * @return the changed memory block address.
 */
void *rt_smem_realloc(rt_smem_t m, void *rmem, rt_size_t newsize)
{
    rt_size_t size;
    rt_size_t ptr, ptr2;
    struct rt_small_mem_item *mem, *mem2;
    struct rt_small_mem *small_mem;
    void *nmem;

    RT_ASSERT(m != RT_NULL);
    RT_ASSERT(rt_object_get_type(&m->parent) == RT_Object_Class_Memory);
    RT_ASSERT(rt_object_is_systemobject(&m->parent));

    small_mem = (struct rt_small_mem *)m;
    /* alignment size */
    newsize = RT_ALIGN(newsize, RT_ALIGN_SIZE);
    if (newsize > small_mem->mem_size_aligned)
    {
        RT_DEBUG_LOG(RT_DEBUG_MEM, ("realloc: out of memory\n"));

        return RT_NULL;
    }
    else if (newsize == 0)
    {
        rt_smem_free(rmem);
        return RT_NULL;
    }

    /* allocate a new memory block */
    if (rmem == RT_NULL)
        return rt_smem_alloc(&small_mem->parent, newsize);

    RT_ASSERT((((rt_ubase_t)rmem) & (RT_ALIGN_SIZE - 1)) == 0);
    RT_ASSERT((rt_uint8_t *)rmem >= (rt_uint8_t *)small_mem->heap_ptr);
    RT_ASSERT((rt_uint8_t *)rmem < (rt_uint8_t *)small_mem->heap_end);

    mem = (struct rt_small_mem_item *)((rt_uint8_t *)rmem - SIZEOF_STRUCT_MEM);

    /* current memory block size */
    ptr = (rt_uint8_t *)mem - small_mem->heap_ptr;
    size = mem->next - ptr - SIZEOF_STRUCT_MEM;
    if (size == newsize)
    {
        /* the size is the same as */
        return rmem;
    }

    if (newsize + SIZEOF_STRUCT_MEM + MIN_SIZE < size)
    {
        /* split memory block */
        small_mem->parent.used -= (size - newsize);

        ptr2 = ptr + SIZEOF_STRUCT_MEM + newsize;
        mem2 = (struct rt_small_mem_item *)&small_mem->heap_ptr[ptr2];
        mem2->pool_ptr = MEM_FREED();
        mem2->next = mem->next;
        mem2->prev = ptr;
#ifdef RT_USING_MEMTRACE
        rt_smem_setname(mem2, "    ");
#endif /* RT_USING_MEMTRACE */
        mem->next = ptr2;
        if (mem2->next != small_mem->mem_size_aligned + SIZEOF_STRUCT_MEM)
        {
            ((struct rt_small_mem_item *)&small_mem->heap_ptr[mem2->next])->prev = ptr2;
        }

        if (mem2 < small_mem->lfree)
        {
            /* the splited struct is now the lowest */
            small_mem->lfree = mem2;
        }

        plug_holes(small_mem, mem2);

        return rmem;
    }

    /* expand memory */
    nmem = rt_smem_alloc(&small_mem->parent, newsize);
    if (nmem != RT_NULL) /* check memory */
    {
        rt_memcpy(nmem, rmem, size < newsize ? size : newsize);
        rt_smem_free(rmem);
    }

    return nmem;
}
RTM_EXPORT(rt_smem_realloc);

/**
 * @brief This function will release the previously allocated memory block by
 *        rt_mem_alloc. The released memory block is taken back to system heap.
 *
 * @param rmem the address of memory which will be released.
 */
void rt_smem_free(void *rmem)
{
    struct rt_small_mem_item *mem;
    struct rt_small_mem *small_mem;

    if (rmem == RT_NULL)
        return;

    RT_ASSERT((((rt_ubase_t)rmem) & (RT_ALIGN_SIZE - 1)) == 0);

    /* Get the corresponding struct rt_small_mem_item ... */
    mem = (struct rt_small_mem_item *)((rt_uint8_t *)rmem - SIZEOF_STRUCT_MEM);
    /* ... which has to be in a used state ... */
    small_mem = MEM_POOL(mem);
    RT_ASSERT(small_mem != RT_NULL);
    RT_ASSERT(MEM_ISUSED(mem));
    RT_ASSERT(rt_object_get_type(&small_mem->parent.parent) == RT_Object_Class_Memory);
    RT_ASSERT(rt_object_is_systemobject(&small_mem->parent.parent));
    RT_ASSERT((rt_uint8_t *)rmem >= (rt_uint8_t *)small_mem->heap_ptr &&
              (rt_uint8_t *)rmem < (rt_uint8_t *)small_mem->heap_end);
    RT_ASSERT(MEM_POOL(&small_mem->heap_ptr[mem->next]) == small_mem);

    RT_DEBUG_LOG(RT_DEBUG_MEM,
                 ("release memory 0x%x, size: %d\n",
                  (rt_ubase_t)rmem,
                  (rt_ubase_t)(mem->next - ((rt_uint8_t *)mem - small_mem->heap_ptr))));

    /* ... and is now unused. */
    mem->pool_ptr = MEM_FREED();
#ifdef RT_USING_MEMTRACE
    rt_smem_setname(mem, "    ");
#endif /* RT_USING_MEMTRACE */

    if (mem < small_mem->lfree)
    {
        /* the newly freed struct is now the lowest */
        small_mem->lfree = mem;
    }

    small_mem->parent.used -= (mem->next - ((rt_uint8_t *)mem - small_mem->heap_ptr));

    /* finally, see if prev or next are free also */
    plug_holes(small_mem, mem);
}
RTM_EXPORT(rt_smem_free);

#ifdef RT_USING_FINSH
#include <finsh.h>

#ifdef RT_USING_MEMTRACE
int memcheck(int argc, char *argv[])
{
    int position;
    rt_base_t level;
    struct rt_small_mem_item *mem;
    struct rt_small_mem *m;
    struct rt_object_information *information;
    struct rt_list_node *node;
    struct rt_object *object;
    char *name;

    name = argc > 1 ? argv[1] : RT_NULL;
    level = rt_hw_interrupt_disable();
    /* get mem object */
    information = rt_object_get_information(RT_Object_Class_Memory);
    for (node = information->object_list.next;
         node != &(information->object_list);
         node  = node->next)
    {
        object = rt_list_entry(node, struct rt_object, list);
        /* find the specified object */
        if (name != RT_NULL && rt_strncmp(name, object->name, RT_NAME_MAX) != 0)
            continue;
        /* mem object */
        m = (struct rt_small_mem *)object;
        /* check mem */
        for (mem = (struct rt_small_mem_item *)m->heap_ptr; mem != m->heap_end; mem = (struct rt_small_mem_item *)&m->heap_ptr[mem->next])
        {
            position = (rt_ubase_t)mem - (rt_ubase_t)m->heap_ptr;
            if (position < 0) goto __exit;
            if (position > (int)m->mem_size_aligned) goto __exit;
            if (MEM_POOL(mem) != m) goto __exit;
        }
    }
    rt_hw_interrupt_enable(level);

    return 0;
__exit:
    rt_kprintf("Memory block wrong:\n");
    rt_kprintf("   name: %s\n", m->parent.parent.name);
    rt_kprintf("address: 0x%08x\n", mem);
    rt_kprintf("   pool: 0x%04x\n", mem->pool_ptr);
    rt_kprintf("   size: %d\n", mem->next - position - SIZEOF_STRUCT_MEM);
    rt_hw_interrupt_enable(level);

    return 0;
}
MSH_CMD_EXPORT(memcheck, check memory data);

int memtrace(int argc, char **argv)
{
    struct rt_small_mem_item *mem;
    struct rt_small_mem *m;
    struct rt_object_information *information;
    struct rt_list_node *node;
    struct rt_object *object;
    char *name;

    name = argc > 1 ? argv[1] : RT_NULL;
    /* get mem object */
    information = rt_object_get_information(RT_Object_Class_Memory);
    for (node = information->object_list.next;
         node != &(information->object_list);
         node  = node->next)
    {
        object = rt_list_entry(node, struct rt_object, list);
        /* find the specified object */
        if (name != RT_NULL && rt_strncmp(name, object->name, RT_NAME_MAX) != 0)
            continue;
        /* mem object */
        m = (struct rt_small_mem *)object;
        /* show memory information */
        rt_kprintf("\nmemory heap address:\n");
        rt_kprintf("name    : %s\n", m->parent.parent.name);
        rt_kprintf("total   : 0x%d\n", m->parent.total);
        rt_kprintf("used    : 0x%d\n", m->parent.used);
        rt_kprintf("max_used: 0x%d\n", m->parent.max);
        rt_kprintf("heap_ptr: 0x%08x\n", m->heap_ptr);
        rt_kprintf("lfree   : 0x%08x\n", m->lfree);
        rt_kprintf("heap_end: 0x%08x\n", m->heap_end);
        rt_kprintf("\n--memory item information --\n");
        for (mem = (struct rt_small_mem_item *)m->heap_ptr; mem != m->heap_end; mem = (struct rt_small_mem_item *)&m->heap_ptr[mem->next])
        {
            int size = MEM_SIZE(m, mem);

            rt_kprintf("[0x%08x - ", mem);
            if (size < 1024)
                rt_kprintf("%5d", size);
            else if (size < 1024 * 1024)
                rt_kprintf("%4dK", size / 1024);
            else
                rt_kprintf("%4dM", size / (1024 * 1024));

            rt_kprintf("] %c%c%c%c", mem->thread[0], mem->thread[1], mem->thread[2], mem->thread[3]);
            if (MEM_POOL(mem) != m)
                rt_kprintf(": ***\n");
            else
                rt_kprintf("\n");
        }
    }
    return 0;
}
MSH_CMD_EXPORT(memtrace, dump memory trace information);
#endif /* RT_USING_MEMTRACE */
#endif /* RT_USING_FINSH */

#endif /* defined (RT_USING_SMALL_MEM) */

/**@}*/
