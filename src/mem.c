/*
 * File      : mem.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-7-12      Bernard      the first version
 * 2010-06-09     Bernard      fix the end stub of heap
 *                             fix memory check in rt_realloc function
 * 2010-07-13     Bernard      fix RT_ALIGN issue found by kuronca
 * 2010-10-14     Bernard      fix rt_realloc issue when realloc a NULL pointer.
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

/* #define RT_MEM_DEBUG */
#define RT_MEM_STATS

#if defined (RT_USING_HEAP) && defined (RT_USING_SMALL_MEM)
#ifdef RT_USING_HOOK
static void (*rt_malloc_hook)(void *ptr, rt_size_t size);
static void (*rt_free_hook)(void *ptr);

/**
 * @addtogroup Hook
 */

/*@{*/

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is allocated from heap memory.
 *
 * @param hook the hook function
 */
void rt_malloc_sethook(void (*hook)(void *ptr, rt_size_t size))
{
	rt_malloc_hook = hook;
}

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is released to heap memory.
 *
 * @param hook the hook function
 */
void rt_free_sethook(void (*hook)(void *ptr))
{
	rt_free_hook = hook;
}

/*@}*/

#endif

#define HEAP_MAGIC 0x1ea0
struct heap_mem
{
	/* magic and used flag */
	rt_uint16_t magic;
	rt_uint16_t used;

	rt_size_t next, prev;
};

/** pointer to the heap: for alignment, heap_ptr is now a pointer instead of an array */
static rt_uint8_t *heap_ptr;

/** the last entry, always unused! */
static struct heap_mem *heap_end;

#define MIN_SIZE 12
#define MIN_SIZE_ALIGNED     RT_ALIGN(MIN_SIZE, RT_ALIGN_SIZE)
#define SIZEOF_STRUCT_MEM    RT_ALIGN(sizeof(struct heap_mem), RT_ALIGN_SIZE)

static struct heap_mem *lfree;   /* pointer to the lowest free block */

static struct rt_semaphore heap_sem;
static rt_size_t mem_size_aligned;

#ifdef RT_MEM_STATS
static rt_size_t used_mem, max_mem;
#endif

static void plug_holes(struct heap_mem *mem)
{
	struct heap_mem *nmem;
	struct heap_mem *pmem;

	RT_ASSERT((rt_uint8_t *)mem >= heap_ptr);
	RT_ASSERT((rt_uint8_t *)mem < (rt_uint8_t *)heap_end);
	RT_ASSERT(mem->used == 0);

	/* plug hole forward */
	nmem = (struct heap_mem *)&heap_ptr[mem->next];
	if (mem != nmem && nmem->used == 0 && (rt_uint8_t *)nmem != (rt_uint8_t *)heap_end)
	{
		/* if mem->next is unused and not end of heap_ptr, combine mem and mem->next */
		if (lfree == nmem)
		{
			lfree = mem;
		}
		mem->next = nmem->next;
		((struct heap_mem *)&heap_ptr[nmem->next])->prev = (rt_uint8_t *)mem - heap_ptr;
	}

	/* plug hole backward */
	pmem = (struct heap_mem *)&heap_ptr[mem->prev];
	if (pmem != mem && pmem->used == 0)
	{
		/* if mem->prev is unused, combine mem and mem->prev */
		if (lfree == mem)
		{
			lfree = pmem;
		}
		pmem->next = mem->next;
		((struct heap_mem *)&heap_ptr[mem->next])->prev = (rt_uint8_t *)pmem - heap_ptr;
	}
}

/**
 * @ingroup SystemInit
 *
 * This function will init system heap
 *
 * @param begin_addr the beginning address of system page
 * @param end_addr the end address of system page
 */
void rt_system_heap_init(void *begin_addr, void *end_addr)
{
	struct heap_mem *mem;
	rt_uint32_t begin_align = RT_ALIGN((rt_uint32_t)begin_addr, RT_ALIGN_SIZE);
	rt_uint32_t end_align = RT_ALIGN_DOWN((rt_uint32_t)end_addr, RT_ALIGN_SIZE);

	RT_DEBUG_NOT_IN_INTERRUPT;

	/* alignment addr */
	if ((end_align > (2 * SIZEOF_STRUCT_MEM)) &&
		((end_align - 2 * SIZEOF_STRUCT_MEM) >= begin_align))
	{
		/* calculate the aligned memory size */
		mem_size_aligned = end_align - begin_align - 2 * SIZEOF_STRUCT_MEM;
	}
	else
	{
		rt_kprintf("mem init, error begin address 0x%x, and end address 0x%x\n", (rt_uint32_t)begin_addr, (rt_uint32_t)end_addr);
		
		return;
	}

	/* point to begin address of heap */
	heap_ptr = (rt_uint8_t *)begin_align;

	RT_DEBUG_LOG(RT_DEBUG_MEM,
		("mem init, heap begin address 0x%x, size %d\n", (rt_uint32_t)heap_ptr, mem_size_aligned));

	/* initialize the start of the heap */
	mem = (struct heap_mem *)heap_ptr;
	mem->magic= HEAP_MAGIC;
	mem->next = mem_size_aligned + SIZEOF_STRUCT_MEM;
	mem->prev = 0;
	mem->used = 0;

	/* initialize the end of the heap */
	heap_end = (struct heap_mem *)&heap_ptr[mem->next];
	heap_end->magic= HEAP_MAGIC;
	heap_end->used = 1;
	heap_end->next = mem_size_aligned + SIZEOF_STRUCT_MEM;
	heap_end->prev = mem_size_aligned + SIZEOF_STRUCT_MEM;

	rt_sem_init(&heap_sem, "heap", 1, RT_IPC_FLAG_FIFO);

	/* initialize the lowest-free pointer to the start of the heap */
	lfree = (struct heap_mem *)heap_ptr;
}

/**
 * @addtogroup MM
 */

/*@{*/

/**
 * Allocate a block of memory with a minimum of 'size' bytes.
 *
 * @param size is the minimum size of the requested block in bytes.
 *
 * @return pointer to allocated memory or NULL if no free memory was found.
 */
void *rt_malloc(rt_size_t size)
{
	rt_size_t ptr, ptr2;
	struct heap_mem *mem, *mem2;

	RT_DEBUG_NOT_IN_INTERRUPT;

	if (size == 0)
		return RT_NULL;

	if (size != RT_ALIGN(size, RT_ALIGN_SIZE))
		RT_DEBUG_LOG(RT_DEBUG_MEM, ("malloc size %d, but align to %d\n", size, RT_ALIGN(size, RT_ALIGN_SIZE)));
	else
		RT_DEBUG_LOG(RT_DEBUG_MEM, ("malloc size %d\n", size));

	/* alignment size */
	size = RT_ALIGN(size, RT_ALIGN_SIZE);

	if (size > mem_size_aligned)
	{
		RT_DEBUG_LOG(RT_DEBUG_MEM, ("no memory\n"));

		return RT_NULL;
	}

	/* every data block must be at least MIN_SIZE_ALIGNED long */
	if (size < MIN_SIZE_ALIGNED)
		size = MIN_SIZE_ALIGNED;

	/* take memory semaphore */
	rt_sem_take(&heap_sem, RT_WAITING_FOREVER);

	for (ptr = (rt_uint8_t *)lfree - heap_ptr; ptr < mem_size_aligned - size;
		ptr = ((struct heap_mem *)&heap_ptr[ptr])->next)
	{
		mem = (struct heap_mem *)&heap_ptr[ptr];

		if ((!mem->used) && (mem->next - (ptr + SIZEOF_STRUCT_MEM)) >= size)
		{
			/* mem is not used and at least perfect fit is possible:
			 * mem->next - (ptr + SIZEOF_STRUCT_MEM) gives us the 'user data size' of mem */

			if (mem->next - (ptr + SIZEOF_STRUCT_MEM) >= (size + SIZEOF_STRUCT_MEM + MIN_SIZE_ALIGNED))
			{
				/* (in addition to the above, we test if another struct heap_mem (SIZEOF_STRUCT_MEM) containing
				 * at least MIN_SIZE_ALIGNED of data also fits in the 'user data space' of 'mem')
				 * -> split large block, create empty remainder,
				 * remainder must be large enough to contain MIN_SIZE_ALIGNED data: if
				 * mem->next - (ptr + (2*SIZEOF_STRUCT_MEM)) == size,
				 * struct heap_mem would fit in but no data between mem2 and mem2->next
				 * @todo we could leave out MIN_SIZE_ALIGNED. We would create an empty
				 *       region that couldn't hold data, but when mem->next gets freed,
				 *       the 2 regions would be combined, resulting in more free memory
				 */
				ptr2 = ptr + SIZEOF_STRUCT_MEM + size;

				/* create mem2 struct */
				mem2 = (struct heap_mem *)&heap_ptr[ptr2];
				mem2->used = 0;
				mem2->next = mem->next;
				mem2->prev = ptr;

				/* and insert it between mem and mem->next */
				mem->next = ptr2;
				mem->used = 1;

				if (mem2->next != mem_size_aligned + SIZEOF_STRUCT_MEM)
				{
					((struct heap_mem *)&heap_ptr[mem2->next])->prev = ptr2;
				}
#ifdef RT_MEM_STATS
				used_mem += (size + SIZEOF_STRUCT_MEM);
				if (max_mem < used_mem)
					max_mem = used_mem;
#endif
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
				mem->used = 1;
#ifdef RT_MEM_STATS
				used_mem += mem->next - ((rt_uint8_t*)mem - heap_ptr);
				if (max_mem < used_mem)
					max_mem = used_mem;
#endif
			}
			/* set memory block magic */
			mem->magic = HEAP_MAGIC;

			if (mem == lfree)
			{
				/* Find next free block after mem and update lowest free pointer */
				while (lfree->used && lfree != heap_end)
					lfree = (struct heap_mem *)&heap_ptr[lfree->next];

				RT_ASSERT(((lfree == heap_end) || (!lfree->used)));
			}

			rt_sem_release(&heap_sem);
			RT_ASSERT((rt_uint32_t)mem + SIZEOF_STRUCT_MEM + size <= (rt_uint32_t)heap_end);
 			RT_ASSERT((rt_uint32_t)((rt_uint8_t *)mem + SIZEOF_STRUCT_MEM) % RT_ALIGN_SIZE == 0);
			RT_ASSERT((((rt_uint32_t)mem) & (RT_ALIGN_SIZE-1)) == 0);

			RT_DEBUG_LOG(RT_DEBUG_MEM, ("allocate memory at 0x%x, size: %d\n", 
				(rt_uint32_t)((rt_uint8_t *)mem + SIZEOF_STRUCT_MEM),
				(rt_uint32_t)(mem->next - ((rt_uint8_t *)mem - heap_ptr))));

			RT_OBJECT_HOOK_CALL(rt_malloc_hook, (((void*)((rt_uint8_t *)mem + SIZEOF_STRUCT_MEM)), size));
			
			/* return the memory data except mem struct */
			return (rt_uint8_t *)mem + SIZEOF_STRUCT_MEM;
		}
	}

	rt_sem_release(&heap_sem);
	
	return RT_NULL;
}

/**
 * This function will change the previously allocated memory block.
 *
 * @param rmem pointer to memory allocated by rt_malloc
 * @param newsize the required new size
 *
 * @return the changed memory block address
 */
void *rt_realloc(void *rmem, rt_size_t newsize)
{
	rt_size_t size;
	rt_size_t ptr, ptr2;
	struct heap_mem *mem, *mem2;
	void *nmem;

	RT_DEBUG_NOT_IN_INTERRUPT;

	/* alignment size */
	newsize = RT_ALIGN(newsize, RT_ALIGN_SIZE);
	if (newsize > mem_size_aligned)
	{
		RT_DEBUG_LOG(RT_DEBUG_MEM, ("realloc: out of memory\n"));

		return RT_NULL;
	}

	/* allocate a new memory block */
	if (rmem == RT_NULL)
		return rt_malloc(newsize);

	rt_sem_take(&heap_sem, RT_WAITING_FOREVER);

	if ((rt_uint8_t *)rmem < (rt_uint8_t *)heap_ptr ||
		(rt_uint8_t *)rmem >= (rt_uint8_t *)heap_end)
	{
		/* illegal memory */
		rt_sem_release(&heap_sem);

		return rmem;
	}

	mem = (struct heap_mem *)((rt_uint8_t *)rmem - SIZEOF_STRUCT_MEM);

	ptr = (rt_uint8_t *)mem - heap_ptr;
	size = mem->next - ptr - SIZEOF_STRUCT_MEM;
	if (size == newsize)
	{
		/* the size is the same as */
		rt_sem_release(&heap_sem);

		return rmem;
	}

	if (newsize + SIZEOF_STRUCT_MEM + MIN_SIZE < size)
	{
		/* split memory block */
#ifdef RT_MEM_STATS
  		used_mem -= (size - newsize);
#endif

		ptr2 = ptr + SIZEOF_STRUCT_MEM + newsize;
		mem2 = (struct heap_mem *)&heap_ptr[ptr2];
		mem2->magic= HEAP_MAGIC;
		mem2->used = 0;
		mem2->next = mem->next;
		mem2->prev = ptr;
		mem->next = ptr2;
		if (mem2->next != mem_size_aligned + SIZEOF_STRUCT_MEM)
		{
			((struct heap_mem *)&heap_ptr[mem2->next])->prev = ptr2;
		}

		plug_holes(mem2);

		rt_sem_release(&heap_sem);

		return rmem;
	}
	rt_sem_release(&heap_sem);

	/* expand memory */
	nmem = rt_malloc(newsize);
	if (nmem != RT_NULL) /* check memory */
	{
		rt_memcpy(nmem, rmem, size < newsize ? size : newsize);	
		rt_free(rmem);
	}

	return nmem;
}

/**
 * This function will contiguously allocate enough space for count objects
 * that are size bytes of memory each and returns a pointer to the allocated
 * memory.
 *
 * The allocated memory is filled with bytes of value zero.
 *
 * @param count number of objects to allocate
 * @param size size of the objects to allocate
 *
 * @return pointer to allocated memory / NULL pointer if there is an error
 */
void *rt_calloc(rt_size_t count, rt_size_t size)
{
	void *p;

	RT_DEBUG_NOT_IN_INTERRUPT;

	/* allocate 'count' objects of size 'size' */
	p = rt_malloc(count * size);

	/* zero the memory */
	if (p)
		rt_memset(p, 0, count * size);

	return p;
}

/**
 * This function will release the previously allocated memory block by rt_malloc.
 * The released memory block is taken back to system heap.
 *
 * @param rmem the address of memory which will be released
 */
void rt_free(void *rmem)
{
	struct heap_mem *mem;

	RT_DEBUG_NOT_IN_INTERRUPT;

	if (rmem == RT_NULL)
		return;
	RT_ASSERT((((rt_uint32_t)rmem) & (RT_ALIGN_SIZE-1)) == 0);
	RT_ASSERT((rt_uint8_t *)rmem >= (rt_uint8_t *)heap_ptr &&
			  (rt_uint8_t *)rmem < (rt_uint8_t *)heap_end);

	RT_OBJECT_HOOK_CALL(rt_free_hook, (rmem));

	if ((rt_uint8_t *)rmem < (rt_uint8_t *)heap_ptr || (rt_uint8_t *)rmem >= (rt_uint8_t *)heap_end)
	{
		RT_DEBUG_LOG(RT_DEBUG_MEM, ("illegal memory\n"));

		return;
	}

	/* Get the corresponding struct heap_mem ... */
	mem = (struct heap_mem *)((rt_uint8_t *)rmem - SIZEOF_STRUCT_MEM);

	RT_DEBUG_LOG(RT_DEBUG_MEM, ("release memory 0x%x, size: %d\n", 
		(rt_uint32_t)rmem, 
		(rt_uint32_t)(mem->next - ((rt_uint8_t *)mem - heap_ptr))));


	/* protect the heap from concurrent access */
	rt_sem_take(&heap_sem, RT_WAITING_FOREVER);

	/* ... which has to be in a used state ... */
	RT_ASSERT(mem->used);
	RT_ASSERT(mem->magic == HEAP_MAGIC);
	/* ... and is now unused. */
	mem->used = 0;
	mem->magic = 0;

	if (mem < lfree)
	{
		/* the newly freed struct is now the lowest */
		lfree = mem;
	}

#ifdef RT_MEM_STATS
	used_mem -= (mem->next - ((rt_uint8_t*)mem - heap_ptr));
#endif

	/* finally, see if prev or next are free also */
	plug_holes(mem);
	rt_sem_release(&heap_sem);
}

#ifdef RT_MEM_STATS
void rt_memory_info(rt_uint32_t *total, rt_uint32_t *used, rt_uint32_t *max_used)
{
	if (total != RT_NULL) *total = mem_size_aligned;
	if (used  != RT_NULL) *used = used_mem;
	if (max_used != RT_NULL) *max_used = max_mem;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void list_mem(void)
{
	rt_kprintf("total memory: %d\n", mem_size_aligned);
	rt_kprintf("used memory : %d\n", used_mem);
	rt_kprintf("maximum allocated memory: %d\n", max_mem);
}
FINSH_FUNCTION_EXPORT(list_mem, list memory usage information)
#endif
#endif

/*@}*/

#endif
