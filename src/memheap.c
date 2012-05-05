/*
 * File      : memheap.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-04-10     Bernard      first implementation
 */
#include <rtthread.h>

#ifdef RT_USING_MEMHEAP

/* dynamic pool magic and mask */
#define RT_MEMHEAP_MAGIC		0x1ea01ea0
#define RT_MEMHEAP_MASK		0xfffffffe
#define RT_MEMHEAP_USED		0x01
#define RT_MEMHEAP_FREED		0x00

#define RT_MEMHEAP_IS_USED(i)	((i)->magic & RT_MEMHEAP_USED)
#define RT_MEMHEAP_MINIALLOC	12

#define RT_MEMHEAP_SIZE		RT_ALIGN(sizeof(struct rt_memheap_item), RT_ALIGN_SIZE)

/*
 * The initialized memory pool will be:
 * +-----------------------------------+--------------------------+
 * | whole freed memory block          | Used Memory Block Tailer |
 * +-----------------------------------+--------------------------+
 *
 * block_list --> whole freed memory block
 *
 * The length of Used Memory Block Tailer is 0, which is prevents block merging across list
 */
rt_err_t rt_memheap_init(struct rt_memheap* memheap, const char* name,
	void *start_addr,
	rt_uint32_t size)
{
	struct rt_memheap_item *item;

	RT_ASSERT(memheap != RT_NULL);

	/* initialize pool object */
	rt_object_init(&(memheap->parent), RT_Object_Class_MemHeap, name);

	memheap->start_addr = start_addr;
	memheap->pool_size = RT_ALIGN_DOWN(size, RT_ALIGN_SIZE);
    memheap->available_size = memheap->pool_size - (2 * RT_MEMHEAP_SIZE);

	/* initialize the free list header */
	item = &(memheap->free_header);
    item->magic = RT_MEMHEAP_MAGIC;
    item->pool_ptr = memheap;
    item->next = RT_NULL;
    item->prev = RT_NULL;
    item->next_free = item;
    item->prev_free = item;

	/* set the free list to free list header */
	memheap->free_list = item;

	/* initialize the first big memory block */
	item = (struct rt_memheap_item*) start_addr;
    item->magic = RT_MEMHEAP_MAGIC;
    item->pool_ptr = memheap;
    item->next = RT_NULL;
    item->prev = RT_NULL;
    item->next_free = item;
    item->prev_free = item;

    item->next = (struct rt_memheap_item *)
           ((rt_uint8_t*) item + memheap->available_size + RT_MEMHEAP_SIZE);
    item->prev =  item->next;

	/* block list header */
	memheap->block_list = item;

	/* place the big memory block to free list */
	item->next_free = memheap->free_list->next_free;
	item->prev_free = memheap->free_list;
	memheap->free_list->next_free->prev_free = item;
	memheap->free_list->next_free = item;

	/* move to the end of memory pool to build a small tailer block, which prevents block merging */
    item =  item->next;
	/* it's a used memory block */
    item->magic = RT_MEMHEAP_MAGIC | RT_MEMHEAP_USED;
    item->pool_ptr = memheap;
    item->next = (struct rt_memheap_item *) start_addr;
    item->prev = (struct rt_memheap_item *) start_addr;
	/* not in free list */
    item->next_free = item->prev_free = RT_NULL;

    RT_DEBUG_LOG(RT_DEBUG_MEMHEAP, ("memory heap: start addr 0x%08x, size %d, free list header 0x%08x",
    		start_addr,	size, &(memheap->free_header)));

    return RT_EOK;
}

rt_err_t rt_memheap_detach(struct rt_memheap* heap)
{
	rt_object_detach(&(heap->parent));

    /* Return a successful completion.  */
    return RT_EOK;
}

void* rt_memheap_alloc(struct rt_memheap *pool_ptr, rt_uint32_t size)
{
	rt_uint32_t free_size;
	struct rt_memheap_item *header_ptr;

	RT_ASSERT(pool_ptr != RT_NULL);

	/* align allocated size */
	size = RT_ALIGN(size, RT_ALIGN_SIZE);
	if (size < RT_MEMHEAP_MINIALLOC) size = RT_MEMHEAP_MINIALLOC;

	RT_DEBUG_LOG(RT_DEBUG_MEMHEAP, ("allocate %d", size));

	if (size < pool_ptr->available_size)
	{
		/* search on free list */
		free_size = 0;
		/* get the first free memory block */
		header_ptr = pool_ptr->free_list->next_free;
		while (header_ptr != pool_ptr->free_list && free_size < size)
		{
			/* get current freed memory block size */
			free_size = (rt_uint32_t)(header_ptr->next) - (rt_uint32_t)header_ptr - RT_MEMHEAP_SIZE;

			if (free_size < size)
			{
				/* move to next free memory block */
				header_ptr = header_ptr->next_free;
			}
		}

		/* determine if the memory is available.  */
		if (free_size >= size)
		{
			/* a block that satisfies the request has been found.  */

			/* determine if the block needs to be split.  */
			if (free_size >= (size + RT_MEMHEAP_SIZE + RT_MEMHEAP_MINIALLOC))
			{
				struct rt_memheap_item* new_ptr;

				/* split the block.  */
				new_ptr =  (struct rt_memheap_item*) (((rt_uint8_t*) header_ptr) + size + RT_MEMHEAP_SIZE);

				RT_DEBUG_LOG(RT_DEBUG_MEMHEAP, ("split: h[0x%08x] nm[0x%08x] pm[0x%08x] to n[0x%08x]", header_ptr,
					header_ptr->next, header_ptr->prev,
					new_ptr));

				/* mark the new block as a memory block and freed. */
				new_ptr->magic = RT_MEMHEAP_MAGIC;

				/* put the pool pointer into the new block.  */
				new_ptr->pool_ptr = pool_ptr;

				/* break down the block list */
				new_ptr->prev = header_ptr;
				new_ptr->next = header_ptr->next;
				header_ptr->next->prev = new_ptr;
				header_ptr->next = new_ptr;

				/* remove header ptr from free list */
				header_ptr->next_free->prev_free = header_ptr->prev_free;
				header_ptr->prev_free->next_free = header_ptr->next_free;
				header_ptr->next_free = RT_NULL;
				header_ptr->prev_free = RT_NULL;

				/* insert new_ptr to free list */
				new_ptr->next_free = pool_ptr->free_list->next_free;
				new_ptr->prev_free = pool_ptr->free_list;
				pool_ptr->free_list->next_free->prev_free = new_ptr;
				pool_ptr->free_list->next_free = new_ptr;
				RT_DEBUG_LOG(RT_DEBUG_MEMHEAP, ("new ptr: nf 0x%08x, pf 0x%08x",
						new_ptr->next_free, new_ptr->prev_free));

				/* decrement the available byte count.  */
				pool_ptr->available_size = pool_ptr->available_size - size - RT_MEMHEAP_SIZE;
			}
			else
			{
				/* decrement the entire free size from the available bytes count.  */
				pool_ptr->available_size =  pool_ptr->available_size - free_size;

				/* remove header_ptr from free list */
				RT_DEBUG_LOG(RT_DEBUG_MEMHEAP, ("one block: h[0x%08x], nf 0x%08x, pf 0x%08x", header_ptr,
					header_ptr->next_free, header_ptr->prev_free));

				header_ptr->next_free->prev_free = header_ptr->prev_free;
				header_ptr->prev_free->next_free = header_ptr->next_free;
				header_ptr->next_free = RT_NULL;
				header_ptr->prev_free = RT_NULL;
			}

			/* Mark the allocated block as not available.  */
			header_ptr->magic |=  RT_MEMHEAP_USED;

			/* Return a memory address to the caller.  */
			RT_DEBUG_LOG(RT_DEBUG_MEMHEAP, ("am: m[0x%08x], h[0x%08x], size: %d",
					(void*) ((rt_uint8_t*)header_ptr + RT_MEMHEAP_SIZE), header_ptr, size);
			return (void*) ((rt_uint8_t*)header_ptr + RT_MEMHEAP_SIZE));
		}
	}

	RT_DEBUG_LOG(RT_DEBUG_MEMHEAP, ("allocate memory: failed\n"));

    /* Return the completion status.  */
    return RT_NULL;
}

void rt_memheap_free(void* ptr)
{
	struct rt_memheap *pool_ptr;
	struct rt_memheap_item *header_ptr, *new_ptr;
	rt_uint32_t insert_header;

	/* set initial status as OK */
	insert_header = 1; new_ptr = RT_NULL;
	header_ptr = (struct rt_memheap_item*)((rt_uint8_t*)ptr - RT_MEMHEAP_SIZE);

	RT_DEBUG_LOG(RT_DEBUG_MEMHEAP, ("free memory: m[0x%08x], h[0x%08x]", ptr, header_ptr));

	/* check magic */
	RT_ASSERT((header_ptr->magic & RT_MEMHEAP_MASK) == RT_MEMHEAP_MAGIC);

	/* get pool ptr */
	pool_ptr = header_ptr->pool_ptr;

    /* Mark the memory as available.  */
    header_ptr->magic &= ~RT_MEMHEAP_USED;

    /* Adjust the available number of bytes.  */
    pool_ptr->available_size =  pool_ptr->available_size +
                        ((rt_uint32_t)(header_ptr->next) -
                        (rt_uint32_t)header_ptr) - RT_MEMHEAP_SIZE;

    /* Determine if the block can be merged with the previous neighbor.  */
    if (!RT_MEMHEAP_IS_USED(header_ptr->prev))
    {
    	RT_DEBUG_LOG(RT_DEBUG_MEMHEAP, ("merge: left node 0x%08x", header_ptr->prev));

        /* adjust the available number of bytes.  */
        pool_ptr->available_size =  pool_ptr->available_size + RT_MEMHEAP_SIZE;

        /* yes, merge block with previous neighbor.  */
        (header_ptr->prev)->next = header_ptr->next;
        (header_ptr->next)->prev = header_ptr->prev;

        /* move header pointer to previous.  */
        header_ptr = header_ptr->prev;
		insert_header = 0;	/* don't insert header to free list */
    }

    /* determine if the block can be merged with the next neighbor.  */
    if (!RT_MEMHEAP_IS_USED(header_ptr->next))
    {
        /* adjust the available number of bytes.  */
        pool_ptr->available_size =  pool_ptr->available_size + RT_MEMHEAP_SIZE;

        /* merge block with next neighbor.  */
        new_ptr =  header_ptr->next;

        RT_DEBUG_LOG(RT_DEBUG_MEMHEAP, ("merge: right node 0x%08x, nf 0x%08x, pf 0x%08x",
        		new_ptr, new_ptr->next_free, new_ptr->prev_free));

        new_ptr->next->prev = header_ptr;
        header_ptr->next = new_ptr->next;

		/* remove new ptr from free list */
		new_ptr->next_free->prev_free = new_ptr->prev_free;
		new_ptr->prev_free->next_free = new_ptr->next_free;
    }

	if (insert_header)
	{
		/* no left merge, insert to free list */
		header_ptr->next_free = pool_ptr->free_list->next_free;
		header_ptr->prev_free = pool_ptr->free_list;
		pool_ptr->free_list->next_free->prev_free = header_ptr;
		pool_ptr->free_list->next_free = header_ptr;

		RT_DEBUG_LOG(RT_DEBUG_MEMHEAP, ("insert to free list: nf 0x%08x, pf 0x%08x",
				header_ptr->next_free, header_ptr->prev_free));
	}
}

#endif
