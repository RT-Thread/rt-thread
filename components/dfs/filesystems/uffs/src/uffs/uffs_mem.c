/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

  UFFS is free software; you can redistribute it and/or modify it under
  the GNU Library General Public License as published by the Free Software 
  Foundation; either version 2 of the License, or (at your option) any
  later version.

  UFFS is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  or GNU Library General Public License, as applicable, for more details.
 
  You should have received a copy of the GNU General Public License
  and GNU Library General Public License along with UFFS; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA  02110-1301, USA.

  As a special exception, if other files instantiate templates or use
  macros or inline functions from this file, or you compile this file
  and link it with other works to produce a work based on this file,
  this file does not by itself cause the resulting work to be covered
  by the GNU General Public License. However the source code for this
  file must still be made available in accordance with section (3) of
  the GNU General Public License v2.
 
  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/

/**
 * \file uffs_mem.c
 * \brief uffs native memory allocator
 * \author Ricky Zheng, created 23th Feb, 2007
 */

#include <string.h>

#include "uffs/uffs_types.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_mem.h"

#define PFX "mem: "

#if CONFIG_USE_NATIVE_MEMORY_ALLOCATOR > 0

#define HEAP_MAGIC_SIZE	8		/* heap magic size, this block is for memory protection */




/* the 'BEST FIT' arithmetic,
 if not defined, the arithmetic
 will be the 'FIRST FIT' */
#define K_HEAP_ALLOCK_BEST_FIT


/* page size may be: 16,32,64,128... */
#define ALLOC_PAGE_BIT_OFFSET	5
#define ALLOC_PAGE_SIZE			(1 << ALLOC_PAGE_BIT_OFFSET)
#define ALLOC_PAGE_MASK			(ALLOC_PAGE_SIZE - 1)
#define ALLOC_THRESHOLD			(ALLOC_PAGE_SIZE * 1)

/* magic mummbers */
#define HEAP_NODE_FREE			0x123455aa
#define HEAP_NODE_ALLOCED		0xaa551234

#define ALLOC_OFFSET	(sizeof(int) + sizeof(int) + sizeof(void *))

/*  Heap memory node type. */
typedef struct HeapNodeSt {
	int	mark;					/*	alloc mark	*/
    int	size;					/*	Size of this node	*/
	struct HeapNodeSt *prev_node;	/*	private node	*/
    struct HeapNodeSt *prev_free;	/*  Link to prev free node */
    struct HeapNodeSt *next_free;	/*	Link to next free node */
} HeapNode;



/*
		p1	|-----------|
			|prev_node	|	NULL
			|mark		|	HEAP_NODE_ALLOCED
			|size		|	p2 - p1
			|prev_free	|	alloc to user
			|next_free	|	not used.
			|			|
			|			|
		p2	|-----------|
			|prev_node	|	p1
			|mark		|	HEAP_NODE_FREE
			|size		|	p3 - p2
			|prev_free	|	NULL
			|next_free	|	p5
			|			|
			|			|
		p3	|-----------|
			|prev_node	|	p2
			|mark		|	HEAP_NODE_ALLOCED
			|size		|	p4 - p3
			|prev_free	|	alloc to user
			|next_free	|	not used.
			|			|
			|			|
		p4	|-----------|
			|prev_node	|	p3
			|mark		|	HEAP_NODE_ALLOCED
			|size		|	p5 - p4
			|prev_free	|	alloc to user
			|next_free	|	not used.
			|			|
			|			|
		p5	|-----------|
			|prev_node	|	p4
			|mark		|	HEAP_NODE_FREE
			|size		|	p6 - p5
			|prev_free	|	p2
			|next_free	|	NULL
			|			|
			|			|
		p6	|-----------|

*/

static HeapNode* volatile m_heapFreeList = NULL;
static HeapNode * m_heapTail = NULL; 
static u32 m_heap_available = 0;
static u32 m_min_heap_avaiable = 0x0fffffff;
static u32 m_kernel_heap_total = 0;

static void HeapDeleteFromFreeList(HeapNode *node);
static void HeapChainToFreeList(HeapNode *node);
static void *_k_allock_node(HeapNode *node, int size);
//static void * _kmalloc_clear(int size);
static int _kfree(void *block);

/*
 *	Delete one node from free list
 *
 */
static void HeapDeleteFromFreeList(HeapNode *node)
{
	if(node->next_free)
		node->next_free->prev_free = node->prev_free;
	if(node->prev_free)
		node->prev_free->next_free = node->next_free;
	if(node == m_heapFreeList)
		m_heapFreeList = node->next_free;
}

/*
 *	Chain the node to free list
 */
static void HeapChainToFreeList(HeapNode *node)
{
	node->next_free = NULL;
	node->prev_free = NULL;
	if(m_heapFreeList == NULL){
		m_heapFreeList = node;
		return;
	}
	else{
		m_heapFreeList->prev_free = node;
		node->next_free = m_heapFreeList;
		m_heapFreeList = node;
	}
}

/*
 * Alloc a block with given node
 * If the node  is larger than the
 * required space plus the space needed for
 * a new node plus a defined threshold, then
 * we split it. The unused portion is put back into
 * the free-list.
 *
 * Attention: Irq is locked when call this routin,
 * so we must unlock irq when return
 */
static void *_k_allock_node(HeapNode *node, int size)
{
	HeapNode *newNode;

	if(node->size >= size + ALLOC_THRESHOLD){
		/*
		 * we need to split it 
		 */
		newNode = (HeapNode *)((char *)node + size);
		newNode->size = node->size - size;
		newNode->mark = HEAP_NODE_FREE;
		newNode->prev_node = node;
		node->size = size;
		/*
		 *	chain the newNode to free list
		 */
		HeapChainToFreeList(newNode);
				
		/*
		 *	fix the next node
		 */
		 ((HeapNode *)((char *)newNode + newNode->size))->prev_node = newNode;
	}
		
	/*
	 *	allock this block
	 */
	node->mark = HEAP_NODE_ALLOCED;

	/*
	 *	delete the node from free list
	 */
	HeapDeleteFromFreeList(node);

	m_heap_available -= node->size;
	if(m_min_heap_avaiable > m_heap_available)
		m_min_heap_avaiable = m_heap_available;
	
	uffs_CriticalExit();	/* exit critical */
	
	return (void *)((char *)node + ALLOC_OFFSET);
}

/*
 * Allocate a block from heap memory.
 *
 * This functions allocates a memory block of the specified
 * size and returns a pointer to that block.
 *
 * The actual size of the allocated block is larger than the
 * requested size because of space required for maintenance
 * information. This additional information is invisible to
 * the application.
 *
 * The routine looks for the smallest block that will meet
 * the required size and releases it to the caller. If the
 * block being requested is usefully smaller than the smallest
 * free block then the block from which the request is being
 * met is split in two. The unused portion is put back into
 * the free-list.
 *
 * The contents of the allocated block is unspecified.
 * To allocate a block with all bytes set to zero use
 * KHeapAllocClear().
 *
 * \note Interrupts are automatically enabled, when this
 *       function returns.
 *
 * \param size Size of the requested memory block.
 *
 * \return Pointer to the allocated memory block if the
 *         function is successful or NULL if the requested
 *         amount of memory is not m_heap_available.
 */
static void *_kmalloc(int size)
{
	HeapNode *node;
#if defined(K_HEAP_ALLOCK_BEST_FIT)
	HeapNode *fit;
#endif
	if(size <= 0)
		return NULL;	/* size is not fit */
		
	/*
	 *	adjust size
	 */
	size += ALLOC_OFFSET;
	if(size & ALLOC_PAGE_MASK){
		size += ALLOC_PAGE_SIZE;
		size &= ~ALLOC_PAGE_MASK;
	}

	uffs_CriticalEnter();	/* enter critical */
	
	node = m_heapFreeList;
	
#if defined(K_HEAP_ALLOCK_BEST_FIT)
    /*
     * Walk through the linked list of free nodes and find the best fit.
     */
	fit = NULL;
	while(node){
        /*
         * Found a note that fits?
         */
		if(node->size >= size){
            /*
             * If it's an exact match, we don't
             * search any further.
             */
			if(node->size == size){
				fit = node;
				break;
			}
			/*
			 *	We search most fit one
			 */
			if(fit){
				if(node->size < fit->size)
					fit = node;
			}
			else
				fit = node;
		}
		node = node->next_free;
	}
	
	if(fit){
		if(fit->size >= size)
			return _k_allock_node(fit, size);
	}
#else
	while(node){
		if(node->size >= size)
			return _k_allock_node(node, size);
		node = node->next_free;
	}
#endif

	uffs_CriticalExit();	/* exit critical */
	
	return NULL;	/*	not found available block	*/

}

#if 0
/* Allocates an array in memory with elements initialized to 0 */
static void *_kcalloc(int num, int size)
{
	return _kmalloc_clear(num * size);
}
#endif

/* Realloc memory.
 * if the size of memblock is small then the new required size, 
 * alloc a new block memory, and copy the contents from the old one,
 * and free the old block.
 * if the size is zero, free the old block, and return NULL. <2004.5.8>
 * if the size of origin block is larger then the new required size,
 * then: 
 *   if the gap is larger then ALLOC_PAGE_SIZE, split the node, and return
 *		the leav memory back to free list.
 *   if the gap is less then ALLOC_PAGE_SIZE, just return current block.
 * If the given block parameter is NULL, _krealloc behaves the same as _kmalloc.
 */
static void *_krealloc(void *block, int size)
{
	HeapNode *node;
	HeapNode *newNode;
	void *p;	/* return pointer */
	int old_data_size; /* old block data size */

	if(block == NULL){
		return _kmalloc(size);
	}
	
	if(size == 0) {
		_kfree(block);
		return NULL;
	}

	uffs_CriticalEnter();	/* enter critical */
	
	node = (HeapNode *)((char *)block - ALLOC_OFFSET);
	old_data_size = node->size - ALLOC_OFFSET;
	if(node->mark != (int)HEAP_NODE_ALLOCED || old_data_size <= 0) {
		uffs_CriticalExit(); /* exit critical */
		return NULL;	/*!!!! at this moment, the heap 
						managment info must be damaged !!!!!*/
	}

	if(old_data_size < size) {
		/* new size is larger then origin block, so need alloc new block */
		p = _kmalloc(size);
		if(!p) {
			uffs_CriticalExit(); /* exit critical */
			return NULL;		/* can't alloc a new block memory, fail... */
		}

		/* alloc a new block, and copy contents from origin block,
		 * and free it finally.
		 */
		memcpy(p, block, old_data_size);
		_kfree(block);
		uffs_CriticalExit(); /* exit critical */
		return p;
	}
	else {
		/* adjust size */
		size += ALLOC_OFFSET;
		if(size & ALLOC_PAGE_MASK) {
			size += ALLOC_PAGE_SIZE;
			size &= ~ALLOC_PAGE_MASK;
		}

		if(node->size - size < ALLOC_PAGE_SIZE) {
			/* the remain memory is too small, so just skip it */
			uffs_CriticalExit(); /* exit critical */
			return block;
		}
		else {
			/* the remain memory is large enough to be splited */
			/* we generate a new 'alloced' node there */
			newNode = (HeapNode *)((char *)node + size);
			newNode->prev_node = node;
			newNode->mark = HEAP_NODE_ALLOCED;
			newNode->size = node->size - size;

			/* split into two node now */
			((HeapNode *)((char *)node + node->size))->prev_node = newNode;
			node->size = size;

			/* put the newNode into free list */
			_kfree((void *)((char *)newNode + ALLOC_OFFSET)); 

			uffs_CriticalExit(); /* exit critical */
			return block;
		}
	}
}

#if 0
static void * _kmalloc_clear(int size)
{
	void *p;
	
	p = _kmalloc(size);
	if(p)
		memset(p, 0, size);
	return p;
}
#endif

/*!
 * \brief Return a block to heap memory.
 *
 * An application calls this function, when a previously
 * allocated memory block is no longer needed.
 *
 * The heap manager checks, if the released block adjoins any
 * other free regions. If it does, then the adjacent free regions
 * are joined together to form one larger region.
 *
 * \note Interrupts are automatically enabled, when this
 *       function returns.
 *
 * \param block Points to a memory block previously allocated
 *              through a call to _kmalloc().
 *
 * \return 0 on success, -1 if the caller tried to free
 *         a block which had been previously released.
 */
static int _kfree(void *block)
{
	HeapNode *node;
	HeapNode *prev;
	HeapNode *next;
	if (block == NULL) {
		return -1;	//the pointer of the memory is invalid.
	}
	uffs_CriticalEnter();	/* enter critical */
	
	node = (HeapNode *)((char *)block - ALLOC_OFFSET);
	if(node->mark != (int)HEAP_NODE_ALLOCED || node->size <= ALLOC_OFFSET) {
		uffs_CriticalExit();/* exit critical */
		return -1;	/*!!!! at this point, the heap 
						management info must be damaged !!!!!*/
	}
	m_heap_available += node->size;
	
	prev = node->prev_node;
	next = (HeapNode *)((char *)node + node->size);

	if(prev->mark == HEAP_NODE_FREE){
        /*
         * If there' s a free node in front of us, merge it.
         */
		prev->size += node->size;
		next->prev_node = prev;
		HeapDeleteFromFreeList(prev);
		node = prev;
	}

	if(next->mark == HEAP_NODE_FREE){
        /*
         * If there' s a free node following us, merge it.
         */
		node->size += next->size;
		((HeapNode *)((char *)next + next->size))->prev_node = node;
		HeapDeleteFromFreeList(next);
	}

	/*
	 *	now, we just chain the node to free list head.
	 */
	node->mark = HEAP_NODE_FREE;
	HeapChainToFreeList(node);
	uffs_CriticalExit();	/* exit critical */
	
	return 0;
}


/*!
 * \brief
 * Add a new memory region to the free heap.
 *
 * This function is called during
 * initialization.
 *
 * Applications typically do not call this function.
 *
 * \param addr Start address of the memory region.
 * \param size Number of bytes of the memory region.
 */
void uffs_MemInitHeap(void *addr, int size)
{
	HeapNode *np;
	
	
	if(!((long)addr & 3)){
		addr = (void *)(((char *)addr) + 4);
		addr = (void *)(((long)addr) & ~3);
	}
	size &= ~ALLOC_PAGE_MASK;
	if(size < ALLOC_PAGE_SIZE * 3) return;

	uffs_CriticalEnter();
	
	/* pre alloc header node, size is ALLOC_PAGE_SIZE */
	np = (HeapNode *)addr;
	np->size = ALLOC_PAGE_SIZE;
	np->mark = HEAP_NODE_ALLOCED;
	np->prev_node = NULL;

	/* pre alloc tail node, size is -1 */
    np = (HeapNode *)((char *)addr + size - ALLOC_PAGE_SIZE);
	np->mark = HEAP_NODE_ALLOCED;
	np->size = -1;
	np->prev_node = (HeapNode *)((char *)addr + ALLOC_PAGE_SIZE);
	m_heapTail = np;

	/* Free list head */
    np = (HeapNode *)((char *)addr + ALLOC_PAGE_SIZE);
    np->mark = HEAP_NODE_FREE;
    np->prev_node = (HeapNode *)addr;
    np->size = size - 2 * ALLOC_PAGE_SIZE;
    np->next_free = NULL;
    np->prev_free = NULL;
	m_heapFreeList = np;
	m_heap_available = np->size;
	m_min_heap_avaiable = m_heap_available;
	
	m_kernel_heap_total += size;

	uffs_CriticalExit();
}

/******************************************************************************************/


static void *__umalloc(uffs_MemAllocator *mem, unsigned int size, HeapHashTable * hash_tbl);
static void *__ucalloc(uffs_MemAllocator *mem, unsigned int num, unsigned int size, HeapHashTable *hash_tbl);
static void *__urealloc(uffs_MemAllocator *mem, void *block, unsigned int size, HeapHashTable *hash_tbl);
static int __ufree(uffs_MemAllocator *mem, void *p, HeapHashTable * hash_tbl);


/* release all alloced memory from hash table,
 * return alloced pointer nummber.
 */
static int ReleaseHeap(uffs_MemAllocator *mem, HeapHashTable *hash_tbl)
{
	int i;
	int count = 0;
	HeapMm volatile * node;

	if (hash_tbl == NULL) 
		return -1;
	for (i = 0; i < HEAP_HASH_SIZE; i++){
		while ((node = hash_tbl[i]) != NULL){
			__ufree(mem, node->p, hash_tbl);
			count++;
		}
	}
	_kfree(hash_tbl);

	return count;
}

static void *uffs_malloc(struct uffs_DeviceSt *dev, unsigned int size)
{
	HeapHashTable * hash_tbl;

	if ((int)size < 0)
		return NULL;

	hash_tbl = dev->mem.tbl;
	if (hash_tbl) {
		return __umalloc(&dev->mem, size, hash_tbl);
	}
	else{
		return NULL;
	}
}


/* alloc one block with given size, return the block pointer */
static void *__umalloc(uffs_MemAllocator *mem, unsigned int size, HeapHashTable *hash_tbl)
{
	void *p;
	HeapMm *node;
	int idx;
	
	/* calling kernel routin allocate bigger size memory block */
	p = _kmalloc(HEAP_MAGIC_SIZE + size + HEAP_MAGIC_SIZE);
	
	if (p) {
		node = (HeapMm *)_kmalloc(sizeof(HeapMm));
		if (node == NULL) {
			_kfree(p);
			return NULL;
		}
		p = (void *)((char *)p + HEAP_MAGIC_SIZE);	/* adjust pointer first */
		node->p = p;
		node->size = size;
		mem->count += size;

		if (mem->maxused < mem->count) 
			mem->maxused = mem->count;

		node->task_id = uffs_OSGetTaskId();	/* get task id */
		
		uffs_CriticalEnter();
		
		/* insert node to hash table */
		idx = GET_HASH_INDEX(p);
		node->next = hash_tbl[idx];
		hash_tbl[idx] = node;
		
		uffs_CriticalExit();

		return p;	/* ok, return the pointer */
	}
	return NULL;
}

/* Allocates an array in memory with elements initialized to 0 */
static void *__ucalloc(uffs_MemAllocator *mem, unsigned int num, unsigned int size, HeapHashTable *hash_tbl)
{
	return __umalloc(mem, num * size, hash_tbl);
}


/* realloc one block with given size, return the block pointer */
static void *__urealloc(uffs_MemAllocator *mem, void *block, unsigned int size, HeapHashTable *hash_tbl)
{
	void *p, *pNew;
	HeapMm *prev, *node;
	int idx;

	if (block == NULL) {
		return __umalloc(mem, size, hash_tbl);
	}

	if (size == 0) {
		__ufree(mem, block, hash_tbl);
		return NULL;
	}

	/* calculate hash idx */
	idx = GET_HASH_INDEX(block);

	/* check whether block pointer is alloc from this heap... */
	uffs_CriticalEnter();
	node = hash_tbl[idx];
	prev = NULL;

	while (node){
		if (node->p == block) {
			break; /* got it! */
		}
		prev = node;
		node = node->next;	/* search for next node */
	}

	if (!node) {
		/* not my duty :-) */
		uffs_CriticalExit();
		return NULL;
	}

	/* ok, begin call kernel API to realloc memory */

	p = (void *)((char *)block - HEAP_MAGIC_SIZE);	/* get real pointer which kernel need */
	pNew = _krealloc(p, HEAP_MAGIC_SIZE + size + HEAP_MAGIC_SIZE);

	if (pNew == NULL) {	/* realloc fail */
		uffs_CriticalExit();
		return NULL;
	}

	if (pNew == p) {
		/* new block is the same as the old block */
		uffs_CriticalExit();
		return block;
	}

	/* new block is difference with old block, we need to change hash table ... */
	if (prev){
		/* prev is not the first */
		prev->next = node->next;
	}
	else{
		/* this node is the first, so.. */
		hash_tbl[idx] = node->next;
	}
	uffs_CriticalExit();

	node->p = (void *)((char *)pNew + HEAP_MAGIC_SIZE);
	node->size = size;
	node->task_id = uffs_OSGetTaskId();

	/* insert node into hash table */
	idx = GET_HASH_INDEX(node->p);
	uffs_CriticalEnter();
	node->next = hash_tbl[idx];
	hash_tbl[idx] = node;
	uffs_CriticalExit();

	return node->p;
	
}


/* free the block, if the pointer(parameter 'p') is 
 * not valid(allocated by this allocate system) or error occur, return -1,
 * else return 0
 */
static int __ufree(uffs_MemAllocator *mem, void *p, HeapHashTable *hash_tbl)
{
	HeapMm *node, *prev;
	
	if (p) {	/* check the pointer */
		uffs_CriticalEnter();
		node = hash_tbl[GET_HASH_INDEX(p)];
		prev = NULL;
		while (node) {
			if (node->p == p) {
				/* we find the node, so begin to release */
				if (prev) {
					/* this node is not the first */
					prev->next = node->next;
				}
				else {
					/* this node is the first node of hash channel */
					hash_tbl[GET_HASH_INDEX(p)] = node->next;
				}

				mem->count -= node->size;
				
				uffs_CriticalExit();
				if (_kfree(node) == -1)	/* calling kernel routine release node */
					return -1;			/* fail, return -1 */
				
				/* calling kernel routine and return */
				return _kfree((void *)((char *)p - HEAP_MAGIC_SIZE)); 
			}
			prev = node;
			node = node->next;	/* search for next node */
		}
		uffs_CriticalExit();
	}

	return -1;
}

static URET uffs_free(struct uffs_DeviceSt *dev, void *block)
{
	HeapHashTable *hash_tbl;
	hash_tbl = dev->mem.tbl;

	if (hash_tbl) {
		if (__ufree(&dev->mem, block, hash_tbl) < 0) {
			uffs_Perror(UFFS_ERR_SERIOUS, "Try to free unmanaged memory ?");
			return U_FAIL;
		}
	}

	return U_SUCC;
}

URET uffs_MemInitNativeAllocator(uffs_Device *dev)
{
	uffs_MemAllocator *mem = &dev->mem;

	memset(mem->tbl, 0, sizeof(mem->tbl));
	mem->malloc = uffs_malloc;
	mem->free = uffs_free;
	mem->blockinfo_pool_size = 0;
	mem->pagebuf_pool_size = 0;
	mem->tree_nodes_pool_size = 0;

	return U_SUCC;
}


URET uffs_MemReleaseNativeAllocator(uffs_Device *dev)
{
	int count;
	URET ret = U_SUCC;

	if (dev) {
		count = ReleaseHeap(&dev->mem, dev->mem.tbl);
		if (count < 0) {
			uffs_Perror(UFFS_ERR_SERIOUS, "Release native memory allocator fail!");
			ret = U_FAIL;
		}
		else if (count > 0) {
			uffs_Perror(UFFS_ERR_NORMAL, "Find %d block memory leak!", count);
		}
	}

	return ret;
}

/**
 * \brief Setup the memory allocator to native memory allocator
 *
 * \param allocator memory allocator to be setup
 */
void uffs_MemSetupNativeAllocator(uffs_MemAllocator *allocator)
{
	memset(allocator, 0, sizeof(uffs_MemAllocator));
	allocator->init = uffs_MemInitNativeAllocator;
	allocator->release = uffs_MemReleaseNativeAllocator;
}

#endif //CONFIG_USE_NATIVE_MEMORY_ALLOCATOR

#if CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR > 0
#include <malloc.h>
static void * sys_malloc(struct uffs_DeviceSt *dev, unsigned int size)
{
	uffs_Perror(UFFS_ERR_NORMAL, "system memory alloc %d bytes", size);
	return malloc(size);
}

static URET sys_free(struct uffs_DeviceSt *dev, void *p)
{
	free(p);
	return U_SUCC;
}

void uffs_MemSetupSystemAllocator(uffs_MemAllocator *allocator)
{
	allocator->malloc = sys_malloc;
	allocator->free = sys_free;
}
#endif //CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR

#if CONFIG_USE_STATIC_MEMORY_ALLOCATOR > 0
static void * static_malloc(struct uffs_DeviceSt *dev, unsigned int size)
{
	struct uffs_memAllocatorSt *mem = &dev->mem;
	void *p = NULL;

	size += (size % sizeof(long) ? sizeof(long) - (size % sizeof(long)) : 0);

	if (mem->buf_size - mem->pos < (int)size) {
		uffs_Perror(UFFS_ERR_SERIOUS, "Memory alloc failed! (alloc %d, free %d)", size, mem->buf_size - mem->pos);
	}
	else {
		p = mem->buf_start + mem->pos;
		mem->pos += size;
		uffs_Perror(UFFS_ERR_NOISY, "0x%p: Allocated %d, free %d", p, size, mem->buf_size - mem->pos);
	}

	return p;
}

void uffs_MemSetupStaticAllocator(uffs_MemAllocator *allocator, void *pool, int size)
{
	allocator->buf_start = (unsigned char *)pool;
	allocator->buf_size = size;
	allocator->pos = 0;
	allocator->malloc = static_malloc;
	allocator->free = NULL;  //never free memory for static memory allocator

	uffs_Perror(UFFS_ERR_NOISY, "System static memory: %d bytes", allocator->buf_size);
	
}

#endif






