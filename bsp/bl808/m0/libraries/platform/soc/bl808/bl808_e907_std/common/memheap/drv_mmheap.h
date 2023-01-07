/**
 * @file drv_mmheap.h
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
#ifndef __DRV_MMHEAP_H
#define __DRV_MMHEAP_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef MMHEAP_LOCK
#define MMHEAP_LOCK()
#endif

#ifndef MMHEAP_UNLOCK
#define MMHEAP_UNLOCK()
#endif

#ifndef MMHEAP_ASSERT
#define MMHEAP_ASSERT(A) \
    if (!(A))            \
    printf("mmheap malloc error:drv_mmheap,%d\r\n", __LINE__)

#endif

#ifndef MMHEAP_MALLOC_FAIL
#define MMHEAP_MALLOC_FAIL() printf("mmheap malloc fail:drv_mmheap,%d\r\n", __LINE__)
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct heap_region {
    void *addr;
    size_t mem_size;
};

struct heap_node {
    struct heap_node *next_node;
    size_t mem_size;
};

struct heap_info {
    struct heap_node *pStart;
    struct heap_node *pEnd;
    size_t total_size;
};

struct heap_state {
    size_t remain_size;
    size_t free_node_num;
    size_t max_node_size;
    size_t min_node_size;
};

void mmheap_init(struct heap_info *pRoot, const struct heap_region *pRigon);
/**
 * @brief Alloc start address aligned memory from the heap.
 * Alloc aligned address and specified size memory from the heap.
 *
 * @attention
 *
 * @param[in]   pRoot    heap info.
 * @param[in]   align_size   address align mask of the memory.
 * @param[in]   want_size    size of the memory.
 *
 * @return  the pointer to the allocated memory.
 */
void *mmheap_align_alloc(struct heap_info *pRoot, size_t align_size, size_t want_size);
/**
 * @brief Alloc memory.
 * Allocate size bytes and returns a pointer to the allocated memory.
 *
 * @attention size should no bigger than MMHEAP_BLK_SIZE_MAX.
 *
 * @param[in]   pRoot    heap info.
 * @param[in]   want_size    size of the memory.
 *
 * @return  the pointer to the allocated memory.
 */
void *mmheap_alloc(struct heap_info *pRoot, size_t want_size);
/**
 * @brief Realloc memory from the heap.
 * Change the size of the memory block pointed to by ptr to size bytes.
 *
 * @attention
 * <ul>
 * <li> if ptr is NULL, then the call is equivalent to mmheap_alloc(size), for all values of size.
 * <li> if ptr is if size is equal to zero, and ptr is not NULL, then the call is equivalent to mmheap_free(ptr).
 * </ul>
 *
 * @param[in]   pRoot    heap info.
 * @param[in]   src_addr     old pointer to the memory space.
 * @param[in]   want_size    new size of the memory space.
 *
 * @return  the new pointer to the allocated memory.
 */
void *mmheap_realloc(struct heap_info *pRoot, void *src_addr, size_t want_size);
/**
 * @brief Cealloc memory from the heap.
 * Change the size of the memory block pointed to by ptr to size bytes.
 *
 * @attention
 * <ul>
 * <li> if ptr is NULL, then the call is equivalent to mmheap_alloc(size), for all values of size.
 * <li> if ptr is if size is equal to zero, and ptr is not NULL, then the call is equivalent to mmheap_free(ptr).
 * </ul>
 *
 * @param[in]   pRoot    heap info.
 * @param[in]   num     size number.
 * @param[in]   size    new size of the memory space.
 *
 * @return  the new pointer to the allocated memory.
 */
void *mmheap_calloc(struct heap_info *pRoot, size_t num, size_t size);
/**
 * @brief Free the memory.
 * Free the memory space pointed to by ptr, which must have been returned by a previous call to mmheap_alloc(), mmheap_aligned_alloc(), or mmheap_realloc().
 *
 * @attention
 *
 * @param[in]   pRoot    heap info.
 * @param[in]   addr     pointer to the memory.
 *
 * @return  None.
 */
void mmheap_free(struct heap_info *pRoot, void *addr);
/**
 * @brief get mmheap state
 *
 * @param pRoot heap info.
 * @param pState heap state
 */
void mmheap_get_state(struct heap_info *pRoot, struct heap_state *pState);
#ifdef __cplusplus
}
#endif

#endif