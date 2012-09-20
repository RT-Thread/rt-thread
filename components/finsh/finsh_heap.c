/*
 * File      : finsh_heap.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#include <finsh.h>

#include "finsh_var.h"

ALIGN(RT_ALIGN_SIZE)
u_char finsh_heap[FINSH_HEAP_MAX];
struct finsh_block_header
{
	u_long length;
	struct finsh_block_header* next;
};
#define BLOCK_HEADER(x)                 (struct finsh_block_header*)(x)
#define finsh_block_get_header(data)    (struct finsh_block_header*)((u_char*)data - sizeof(struct finsh_block_header))
#define finsh_block_get_data(header)    (u_char*)((struct finsh_block_header*)header + 1)
#define HEAP_ALIGN_SIZE(size)			(((size) + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT-1))

static struct finsh_block_header* free_list;
static struct finsh_block_header* allocate_list;

static void finsh_heap_gc(void);

static void finsh_block_insert(struct finsh_block_header** list, struct finsh_block_header* header);
static void finsh_block_remove(struct finsh_block_header** list, struct finsh_block_header* header);
static void finsh_block_split(struct finsh_block_header* header, size_t size);
static void finsh_block_merge(struct finsh_block_header** list, struct finsh_block_header* header);

int finsh_heap_init(void)
{
	/* clear heap to zero */
	memset(&finsh_heap[0], 0, sizeof(finsh_heap));

	/* init free and alloc list */
    free_list           = BLOCK_HEADER(&finsh_heap[0]);
	free_list->length   = FINSH_HEAP_MAX - sizeof(struct finsh_block_header);
    free_list->next     = NULL;

    allocate_list       = NULL;

    return 0;
}

/**
 * allocate a block from heap
 */
void* finsh_heap_allocate(size_t size)
{
	struct finsh_block_header* header;

	size = HEAP_ALIGN_SIZE(size);

    /* find the first fit block */
    for (header = free_list;
        ((header != NULL) && (header->length <= size + sizeof(struct finsh_block_header)));
        header = header->next) ;

	if (header == NULL)
	{
		finsh_heap_gc();

		/* find the first fit block */
		for (header = free_list;
			((header != NULL) && (header->length < size + sizeof(struct finsh_block_header)));
			header = header->next) ;

		/* there is no memory */
		if (header == NULL) return NULL;
	}

    /* split block */
	finsh_block_split(header, size);

	/* remove from free list */
	finsh_block_remove(&free_list, header);
	header->next = NULL;

    /* insert to allocate list */
    finsh_block_insert(&allocate_list, header);

	memset(finsh_block_get_data(header), 0, size);

	return finsh_block_get_data(header);
}

/**
 * release the allocated block
 */
void  finsh_heap_free(void*ptr)
{
    struct finsh_block_header* header;

    /* get block header */
	header = finsh_block_get_header(ptr);

    /* remove from allocate list */
	finsh_block_remove(&allocate_list, header);

	/* insert to free list */
	finsh_block_insert(&free_list, header);
	finsh_block_merge(&free_list, header);
}

/**
 * garbage collector
 */
static void finsh_heap_gc(void)
{
	int i;
	struct finsh_block_header *header, *temp;

	temp = NULL;

    /* find the first fit block */
    for (header = allocate_list; header != NULL; )
    {
    	for (i = 0; i < FINSH_VARIABLE_MAX; i ++)
    	{
    		if (global_variable[i].type != finsh_type_unknown)
    		{
    			if (global_variable[i].value.ptr == finsh_block_get_data(header))
					break;
    		}
    	}

		temp   = header;
		header = header->next;

		/* this block is an unused block, release it */
    	if (i == FINSH_VARIABLE_MAX)
    	{
    		finsh_heap_free(finsh_block_get_data(temp));
    	}
    }
}

/**
 * insert a block to list
 */
void finsh_block_insert(struct finsh_block_header** list, struct finsh_block_header* header)
{
    struct finsh_block_header* node;

    if (*list == NULL)
    {
        *list = header;
        return;
    }

    /* find out insert point */
	node = *list;

	if (node > header)
	{
		/* insert node in the header of list */
		header->next = node;
		*list = header;

		return;
	}
	else
	{
		for (node = *list; node; node = node->next)
		{
    		if (node->next > header) break;

    		if (node->next == NULL) break;
		}
	}

    /* insert node */
    if (node->next != NULL) header->next = node->next;
    node->next      = header;
}

/**
 * remove block from list
 */
void finsh_block_remove(struct finsh_block_header** list, struct finsh_block_header* header)
{
    struct finsh_block_header* node;

    node = *list;
    if (node == header)
    {
        /* remove list header */
        *list = header->next;
        header->next = NULL;

        return;
    }

    for (node = *list; node != NULL; node = node->next)
    {
        if (node->next == header)
        {
            node->next = header->next;
            break;
        }
    }
}

/**
 * split block
 */
void finsh_block_split(struct finsh_block_header* header, size_t size)
{
    struct finsh_block_header* next;

    /*
     * split header into two node:
     * header->next->...
     */
    next = BLOCK_HEADER((u_char*)header + sizeof(struct finsh_block_header) + size);
    next->length = header->length - sizeof(struct finsh_block_header) - size;
    header->length = size;
    next->next = header->next;

    header->next = next;
}

void finsh_block_merge(struct finsh_block_header** list, struct finsh_block_header* header)
{
    struct finsh_block_header* prev_node;
    struct finsh_block_header* next_node;

    next_node = header->next;

    if (*list == header) prev_node = NULL;
    else
    {
        /* find out the previous header */
        for (prev_node = *list; prev_node; prev_node =prev_node->next)
        {
            if (prev_node->next == header)
                break;
        }
    }

    /* try merge node */

    /* merge to previous node */
    if (prev_node != NULL &&
        ((u_char*)prev_node + prev_node->length + sizeof(struct finsh_block_header)
        == (u_char*)header))
    {
        /* is it close to next node? */
        if ((next_node != NULL) &&
            ((u_char*)header + header->length + sizeof(struct finsh_block_header)
            == (u_char*)next_node))
        {
            /* merge three node */
        	prev_node->length += header->length + next_node->length +
                2 * sizeof(struct finsh_block_header);

            prev_node->next = next_node->next;
        }
        else
        {
            prev_node->length += header->length + sizeof(struct finsh_block_header);
            prev_node->next = header->next;
        }
    }
    else /* merge to last node */
    if ( (next_node != NULL) &&
        ((u_char*)header + header->length + sizeof(struct finsh_block_header)
        == (u_char*)next_node))
    {
        header->length += next_node->length + sizeof(struct finsh_block_header);
        header->next = next_node->next;
    }
}
