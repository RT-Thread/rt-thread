/**
 * @file drv_mmheap.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */

#include "drv_mmheap.h"

#define MEM_MANAGE_ALIGNMENT_BYTE_DEFAULT 8
#define MEM_MANAGE_BITS_PER_BYTE          8
#define MEM_MANAGE_MEM_STRUCT_SIZE        mmheap_align_up(sizeof(struct heap_node), MEM_MANAGE_ALIGNMENT_BYTE_DEFAULT)
#define MEM_MANAGE_MINUM_MEM_SIZE         (MEM_MANAGE_MEM_STRUCT_SIZE << 1)
#define MEM_MANAGE_ALLOCA_LABAL           ((size_t)((size_t)1 << (sizeof(size_t) * MEM_MANAGE_BITS_PER_BYTE - 1)))

static inline size_t mmheap_align_down(size_t data, size_t align_byte)
{
    return data & ~(align_byte - 1);
}

static inline size_t mmheap_align_up(size_t data, size_t align_byte)
{
    return (data + align_byte - 1) & ~(align_byte - 1);
}

static inline struct heap_node *mmheap_addr_sub(const void *addr)
{
    return (struct heap_node *)((const uint8_t *)addr - MEM_MANAGE_MEM_STRUCT_SIZE);
}

static inline void *mmheap_addr_add(const struct heap_node *mem_node)
{
    return (void *)((const uint8_t *)mem_node + MEM_MANAGE_MEM_STRUCT_SIZE);
}

/**
 * @brief mmheap_insert_node_to_freelist
 *
 * @param pRoot
 * @param pNode
 */
static inline void mmheap_insert_node_to_freelist(struct heap_info *pRoot, struct heap_node *pNode)
{
    struct heap_node *pPriv_Node;
    struct heap_node *pNext_Node;
    /*Find the node with an address similar to pNode*/
    for (pPriv_Node = pRoot->pStart; pPriv_Node->next_node < pNode; pPriv_Node = pPriv_Node->next_node) {
    }

    pNext_Node = pPriv_Node->next_node;
    /*Try to merge the pNode with the previous block*/
    if ((uint8_t *)mmheap_addr_add(pPriv_Node) + pPriv_Node->mem_size == (uint8_t *)pNode) {
        if (pPriv_Node != pRoot->pStart) { /*can merge if not start block*/
            pPriv_Node->mem_size += MEM_MANAGE_MEM_STRUCT_SIZE + pNode->mem_size;
            pNode = pPriv_Node;
        } else {
            /*The latter is not merged if it is a Start block to avoid wasting memory*/
            pRoot->pStart->next_node = pNode;
        }
    } else {
        /*Insert directly into the free single-chain table when merging is not possible*/
        pPriv_Node->next_node = pNode;
    }
    /*Try to merge the pNode with the next block*/
    if ((uint8_t *)mmheap_addr_add(pNode) + pNode->mem_size == (uint8_t *)pNext_Node) {
        if (pNext_Node != pRoot->pEnd) {
            pNode->mem_size += MEM_MANAGE_MEM_STRUCT_SIZE + pNext_Node->mem_size;
            pNode->next_node = pNext_Node->next_node;
        } else {
            pNode->next_node = pRoot->pEnd;
        }
    } else {
        /*Insert directly into the free single-chain table when merging is not possible*/
        pNode->next_node = pNext_Node;
    }
}

/**
 * @brief mmheap_get_state
 *
 * @param pRoot
 * @param pState
 */
void mmheap_get_state(struct heap_info *pRoot, struct heap_state *pState)
{
    MMHEAP_ASSERT(pRoot->pStart != NULL);
    MMHEAP_ASSERT(pRoot->pEnd != NULL);
    pState->max_node_size = pRoot->pStart->next_node->mem_size;
    pState->min_node_size = pRoot->pStart->next_node->mem_size;
    pState->remain_size = 0;
    pState->free_node_num = 0;
    MMHEAP_LOCK();
    for (struct heap_node *pNode = pRoot->pStart->next_node; pNode->next_node != NULL; pNode = pNode->next_node) {
        pState->remain_size += pNode->mem_size;
        pState->free_node_num++;
        if (pNode->mem_size > pState->max_node_size)
            pState->max_node_size = pNode->mem_size;
        if (pNode->mem_size < pState->min_node_size)
            pState->min_node_size = pNode->mem_size;
    }
    MMHEAP_UNLOCK();
}
/**
 * @brief mmheap_align_alloc
 *
 * @param pRoot
 * @param align_size
 * @param want_size
 * @return void*
 */
void *mmheap_align_alloc(struct heap_info *pRoot, size_t align_size, size_t want_size)
{
    void *pReturn = NULL;
    struct heap_node *pPriv_Node, *pNow_Node;

    MMHEAP_ASSERT(pRoot->pStart != NULL);
    MMHEAP_ASSERT(pRoot->pEnd != NULL);

    if (want_size == 0) {
        return NULL;
    }

    if ((want_size & MEM_MANAGE_ALLOCA_LABAL) != 0) {
        MMHEAP_MALLOC_FAIL();
        return NULL;
    }

    if (align_size & (align_size - 1)) {
        MMHEAP_MALLOC_FAIL();
        return NULL;
    }

    MMHEAP_LOCK();
    if (want_size < MEM_MANAGE_MINUM_MEM_SIZE)
        want_size = MEM_MANAGE_MINUM_MEM_SIZE;
    if (align_size < MEM_MANAGE_ALIGNMENT_BYTE_DEFAULT)
        align_size = MEM_MANAGE_ALIGNMENT_BYTE_DEFAULT;

    want_size = mmheap_align_up(want_size, MEM_MANAGE_ALIGNMENT_BYTE_DEFAULT);

    pPriv_Node = pRoot->pStart;
    pNow_Node = pRoot->pStart->next_node;

    while (pNow_Node->next_node != NULL) {
        if (pNow_Node->mem_size >= want_size + MEM_MANAGE_MEM_STRUCT_SIZE) {
            size_t use_align_size;
            size_t new_size;
            pReturn = (void *)mmheap_align_up((size_t)mmheap_addr_add(pNow_Node), align_size); /*Calculate the aligned address*/
            use_align_size = (uint8_t *)pReturn - (uint8_t *)mmheap_addr_add(pNow_Node);       /*Calculate the memory consumed by the alignment*/
            if (use_align_size != 0) {                                                         /*if Memory misalignment*/
                if (use_align_size < MEM_MANAGE_MINUM_MEM_SIZE + MEM_MANAGE_MEM_STRUCT_SIZE) { /*The unaligned value is too small*/
                    pReturn = (void *)mmheap_align_up(
                        (size_t)mmheap_addr_add(pNow_Node) + MEM_MANAGE_MINUM_MEM_SIZE + MEM_MANAGE_MEM_STRUCT_SIZE, align_size);
                    use_align_size = (uint8_t *)pReturn - (uint8_t *)mmheap_addr_add(pNow_Node);
                }
                if (use_align_size <= pNow_Node->mem_size) {
                    new_size = pNow_Node->mem_size - use_align_size; /*Calculate the remaining memory size by removing the memory consumed by alignment*/
                    if (new_size >= want_size) {                     /*Meet the conditions for distribution*/
                        struct heap_node *pNew_Node = mmheap_addr_sub(pReturn);
                        pNow_Node->mem_size -= new_size + MEM_MANAGE_MEM_STRUCT_SIZE; /*Split Node*/
                        pNew_Node->mem_size = new_size;                               /*The new node is also not in the free chain and does not need to be discharged from the free chain*/
                        pNew_Node->next_node = NULL;
                        pNow_Node = pNew_Node;
                        break;
                    }
                }
            } else { /*Memory is directly aligned*/
                pPriv_Node->next_node = pNow_Node->next_node;
                pNow_Node->next_node = NULL;
                break;
            }
        }
        pPriv_Node = pNow_Node;
        pNow_Node = pNow_Node->next_node;
    }

    if (pNow_Node == pRoot->pEnd) {
        MMHEAP_UNLOCK();
        MMHEAP_MALLOC_FAIL();
        return NULL;
    }

    if (pNow_Node->mem_size >= MEM_MANAGE_MINUM_MEM_SIZE + MEM_MANAGE_MEM_STRUCT_SIZE + want_size) {           /*Node memory is still available*/
        struct heap_node *pNew_Node = (struct heap_node *)((uint8_t *)mmheap_addr_add(pNow_Node) + want_size); /*Calculate the address of the node that will be moved into the free chain table*/
        pNew_Node->mem_size = pNow_Node->mem_size - want_size - MEM_MANAGE_MEM_STRUCT_SIZE;
        pNew_Node->next_node = NULL;
        pNow_Node->mem_size = want_size;
        mmheap_insert_node_to_freelist(pRoot, pNew_Node);
    }
    pNow_Node->mem_size |= MEM_MANAGE_ALLOCA_LABAL;
    MMHEAP_UNLOCK();
    return pReturn;
}
/**
 * @brief mmheap_alloc
 *
 * @param pRoot
 * @param want_size
 * @return void*
 */
void *mmheap_alloc(struct heap_info *pRoot, size_t want_size)
{
    return mmheap_align_alloc(pRoot, MEM_MANAGE_ALIGNMENT_BYTE_DEFAULT, want_size);
}
/**
 * @brief mmheap_realloc
 *
 * @param pRoot
 * @param src_addr
 * @param want_size
 * @return void*
 */
void *mmheap_realloc(struct heap_info *pRoot, void *src_addr, size_t want_size)
{
    void *pReturn = NULL;
    struct heap_node *pNext_Node, *pPriv_Node;
    struct heap_node *pSrc_Node;
    MMHEAP_ASSERT(pRoot->pStart != NULL);
    MMHEAP_ASSERT(pRoot->pEnd != NULL);
    if (src_addr == NULL) {
        return mmheap_align_alloc(pRoot, MEM_MANAGE_ALIGNMENT_BYTE_DEFAULT, want_size);
    }
    if (want_size == 0) {
        mmheap_free(pRoot, src_addr);
        return NULL;
    }

    MMHEAP_LOCK();
    if ((want_size & MEM_MANAGE_ALLOCA_LABAL) != 0) {
        MMHEAP_UNLOCK();
        MMHEAP_MALLOC_FAIL();
        return NULL;
    }

    pSrc_Node = mmheap_addr_sub(src_addr);

    if ((pSrc_Node->mem_size & MEM_MANAGE_ALLOCA_LABAL) == 0) {
        MMHEAP_UNLOCK();
        MMHEAP_ASSERT((pSrc_Node->mem_size & MEM_MANAGE_ALLOCA_LABAL) != 0);
        MMHEAP_MALLOC_FAIL();
        return NULL;
    }

    pSrc_Node->mem_size &= ~MEM_MANAGE_ALLOCA_LABAL;
    if (pSrc_Node->mem_size >= want_size) {
        pSrc_Node->mem_size |= MEM_MANAGE_ALLOCA_LABAL;
        pReturn = src_addr;
        MMHEAP_UNLOCK();
        return pReturn;
    }
    /*Start looking in the free list for blocks similar to this block*/
    for (pPriv_Node = pRoot->pStart; pPriv_Node->next_node < pSrc_Node; pPriv_Node = pPriv_Node->next_node) {
    }
    pNext_Node = pPriv_Node->next_node;

    if (pNext_Node != pRoot->pEnd &&
        ((uint8_t *)src_addr + pSrc_Node->mem_size == (uint8_t *)pNext_Node) &&
        (pSrc_Node->mem_size + pNext_Node->mem_size + MEM_MANAGE_MEM_STRUCT_SIZE >= want_size)) {
        /*Meet next node non-end, memory contiguous, enough memory left*/
        pReturn = src_addr;
        pPriv_Node->next_node = pNext_Node->next_node;
        pSrc_Node->mem_size += MEM_MANAGE_MEM_STRUCT_SIZE + pNext_Node->mem_size;
        want_size = mmheap_align_up(want_size, MEM_MANAGE_ALIGNMENT_BYTE_DEFAULT);
        if (pSrc_Node->mem_size >= MEM_MANAGE_MINUM_MEM_SIZE + MEM_MANAGE_MEM_STRUCT_SIZE + want_size) { /*Removing the remaining space allocated is enough to open new blocks*/
            struct heap_node *pNew_Node = (struct heap_node *)((uint8_t *)mmheap_addr_add(pSrc_Node) + want_size);
            pNew_Node->next_node = NULL;
            pNew_Node->mem_size = pSrc_Node->mem_size - want_size - MEM_MANAGE_MEM_STRUCT_SIZE;
            pSrc_Node->mem_size = want_size;
            mmheap_insert_node_to_freelist(pRoot, pNew_Node);
        }
        pSrc_Node->mem_size |= MEM_MANAGE_ALLOCA_LABAL;
        MMHEAP_UNLOCK();
    } else {
        MMHEAP_UNLOCK();
        pReturn = mmheap_align_alloc(pRoot, MEM_MANAGE_ALIGNMENT_BYTE_DEFAULT, want_size);
        if (pReturn == NULL) {
            pSrc_Node->mem_size |= MEM_MANAGE_ALLOCA_LABAL;
            MMHEAP_MALLOC_FAIL();
            return NULL;
        }
        MMHEAP_LOCK();
        memcpy(pReturn, src_addr, pSrc_Node->mem_size);
        pSrc_Node->mem_size |= MEM_MANAGE_ALLOCA_LABAL;
        MMHEAP_UNLOCK();
        mmheap_free(pRoot, src_addr);
    }
    return pReturn;
}
/**
 * @brief
 *
 * @param pRoot
 * @param num
 * @param size
 * @return void*
 */
void *mmheap_calloc(struct heap_info *pRoot, size_t num, size_t size)
{
    void *pReturn = NULL;

    pReturn = (void *)mmheap_alloc(pRoot, size * num);

    if (pReturn) {
        memset(pReturn, 0, num * size);
    }

    return pReturn;
}
/**
 * @brief mmheap_free
 *
 * @param pRoot
 * @param addr
 */
void mmheap_free(struct heap_info *pRoot, void *addr)
{
    struct heap_node *pFree_Node;
    MMHEAP_ASSERT(pRoot->pStart != NULL);
    MMHEAP_ASSERT(pRoot->pEnd != NULL);
    MMHEAP_LOCK();
    if (addr == NULL) {
        MMHEAP_UNLOCK();
        return;
    }
    pFree_Node = mmheap_addr_sub(addr);

    if ((pFree_Node->mem_size & MEM_MANAGE_ALLOCA_LABAL) == 0) {
        MMHEAP_UNLOCK();
        MMHEAP_ASSERT((pFree_Node->mem_size & MEM_MANAGE_ALLOCA_LABAL) != 0);
        return;
    }

    if (pFree_Node->next_node != NULL) {
        MMHEAP_UNLOCK();
        MMHEAP_ASSERT(pFree_Node->next_node == NULL);
        return;
    }
    pFree_Node->mem_size &= ~MEM_MANAGE_ALLOCA_LABAL;
    mmheap_insert_node_to_freelist(pRoot, pFree_Node);
    MMHEAP_UNLOCK();
}
/**
 * @brief mmheap_init
 *
 * @param pRoot
 * @param pRegion
 */
void mmheap_init(struct heap_info *pRoot, const struct heap_region *pRegion)
{
    struct heap_node *align_addr;
    size_t align_size;
    struct heap_node *pPriv_node = NULL;

    pRoot->total_size = 0;
    pRoot->pEnd = NULL;
    pRoot->pStart = NULL;

    for (; pRegion->addr != NULL; pRegion++) {
        align_addr = (struct heap_node *)mmheap_align_up((size_t)pRegion->addr, MEM_MANAGE_ALIGNMENT_BYTE_DEFAULT); /*Calculate the aligned address*/
        if ((uint8_t *)align_addr > pRegion->mem_size + (uint8_t *)pRegion->addr)                                   /*Alignment consumes more memory than the memory area*/
            continue;
        align_size = pRegion->mem_size - ((uint8_t *)align_addr - (uint8_t *)pRegion->addr); /*Calculate the size of memory left after alignment*/
        if (align_size < MEM_MANAGE_MINUM_MEM_SIZE + MEM_MANAGE_MEM_STRUCT_SIZE)             /*if Aligning the remaining memory is too small*/
            continue;
        align_size -= MEM_MANAGE_MEM_STRUCT_SIZE; /*Find the size of the memory block after removing the table header*/
        align_addr->mem_size = align_size;
        align_addr->next_node = NULL;
        if (pRoot->pStart == NULL) {
            pRoot->pStart = align_addr;                                                                   /*set current addr for start*/
            if (align_size >= MEM_MANAGE_MINUM_MEM_SIZE + MEM_MANAGE_MEM_STRUCT_SIZE) {                   /*If the remaining blocks are large enough*/
                align_size -= MEM_MANAGE_MEM_STRUCT_SIZE;                                                 /*Remove the next block of table headers remaining memory size*/
                align_addr = (struct heap_node *)((uint8_t *)pRoot->pStart + MEM_MANAGE_MEM_STRUCT_SIZE); //the next block addr
                align_addr->mem_size = align_size;
                align_addr->next_node = NULL;
                pRoot->pStart->mem_size = 0;
                pRoot->pStart->next_node = align_addr;
                pRoot->total_size = align_addr->mem_size;
            } else { /*The memory is too small, and the address of the current memory block is recorded as start*/
                pRoot->total_size = 0;
                pRoot->pStart->mem_size = 0;
            }
        } else {
            pPriv_node->next_node = align_addr;
            pRoot->total_size += align_size;
        }
        pPriv_node = align_addr;
    }
    //At this point, pPriv_node is the last block, then place the end of the table at the end of the block, find the address to place the end block, end block is only convenient for traversal, so as small as possible, assigned to MEM_MANAGE_MEM_STRUCT_SIZE
    align_addr = (struct heap_node *)mmheap_align_down(
        (size_t)mmheap_addr_add(pPriv_node) + pPriv_node->mem_size - MEM_MANAGE_MEM_STRUCT_SIZE, MEM_MANAGE_ALIGNMENT_BYTE_DEFAULT);
    align_size = (uint8_t *)align_addr - (uint8_t *)mmheap_addr_add(pPriv_node); /*Find the remaining size of the previous block after the end block is allocated*/
    if (align_size >= MEM_MANAGE_MINUM_MEM_SIZE) {
        pRoot->total_size -= pPriv_node->mem_size - align_size; /*Removing memory consumed by allocating end blocks*/
        pRoot->pEnd = align_addr;                               /*Update the address at the end of the list*/
        pPriv_node->next_node = align_addr;
        pPriv_node->mem_size = align_size;
        align_addr->next_node = NULL;
        align_addr->mem_size = 0; /*The end block is not involved in memory allocation, so a direct 0 is sufficient*/
    } else {                      /*The last block is too small, directly as the end block*/
        pRoot->pEnd = pPriv_node;
        pRoot->total_size -= pPriv_node->mem_size;
    }
    MMHEAP_ASSERT(pRoot->pStart != NULL);
    MMHEAP_ASSERT(pRoot->pEnd != NULL);
}
