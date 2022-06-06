/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    drv_heap.h
  * @version V0.1
  * @brief   heap interface
  *
  * Change Logs:
  * Date           Author          Notes
  * 2019-03-26     Cliff.Chen      first implementation
  *
  ******************************************************************************
  */
#ifndef __DRV_HEAP_H
#define __DRV_HEAP_H

#ifdef RT_USING_UNCACHE_HEAP
rt_err_t rt_uncache_heap_init(void *begin_addr, void *end_addr);
void *rt_malloc_uncache(rt_size_t size);
void rt_free_uncache(void *ptr);
#endif

#ifdef RT_USING_LARGE_HEAP
rt_err_t rt_large_heap_init(void *begin_addr, void *end_addr);
void *rt_malloc_large(rt_size_t size);
void rt_free_large(void *ptr);
void *rt_dma_malloc_large(rt_size_t size);
void rt_dma_free_large(void *ptr);
#endif

#ifdef RT_USING_DTCM_HEAP
void *rt_malloc_dtcm(rt_size_t size);
void rt_free_dtcm(void *ptr);
void *rt_dma_malloc_dtcm(rt_size_t size);
void rt_dma_free_dtcm(void *ptr);
#endif

#ifdef RT_USING_PSRAM_HEAP
void *rt_malloc_psram(rt_size_t size);
void rt_free_psram(void *ptr);
void *rt_dma_malloc_psram(rt_size_t size);
void rt_dma_free_psram(void *ptr);
#endif

#endif
