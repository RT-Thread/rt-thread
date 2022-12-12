/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    drv_heap.c
  * @version V0.2
  * @brief   heap interface
  *
  * Change Logs:
  * Date           Author          Notes
  * 2019-03-26     Cliff.Chen      first implementation
  * 2019-05-15     Cliff.Chen      Add large heap
  *
  ******************************************************************************
  */
#include <rtthread.h>
#include "drv_heap.h"

#ifdef RT_USING_UNCACHE_HEAP
static struct rt_memheap _uncache_heap;

rt_err_t rt_uncache_heap_init(void *begin_addr, void *end_addr)
{
    /* initialize a default heap in the system */
    return rt_memheap_init(&_uncache_heap,
                           "ucheap",
                           begin_addr,
                           (rt_uint32_t)end_addr - (rt_uint32_t)begin_addr);
}

void *rt_malloc_uncache(rt_size_t size)
{
    return rt_memheap_alloc(&_uncache_heap, size);
}

void rt_free_uncache(void *ptr)
{
    rt_memheap_free(ptr);
}
#endif

#ifdef RT_USING_LARGE_HEAP
#include "hal_base.h"

static struct rt_memheap _large_heap;

rt_err_t rt_large_heap_init(void *begin_addr, void *end_addr)
{
    /* initialize a default heap in the system */
    return rt_memheap_init(&_large_heap,
                           "large",
                           begin_addr,
                           (rt_uint32_t)end_addr - (rt_uint32_t)begin_addr);
}

void *rt_malloc_large(rt_size_t size)
{
    if (size < RT_LARGE_MALLOC_THRRESH)
        return NULL;

    return rt_memheap_alloc(&_large_heap, size);
}
RTM_EXPORT(rt_malloc_large);

void rt_free_large(void *ptr)
{
    rt_memheap_free(ptr);
}
RTM_EXPORT(rt_free_large);

void *rt_dma_malloc_large(rt_size_t size)
{
    void *align_ptr;
    void *ptr;
    rt_size_t align, align_size;

    if (size < RT_LARGE_MALLOC_THRRESH)
        return NULL;

    align = 4;
    align_size = 0;

#ifdef CACHE_LINE_SIZE
    align = CACHE_LINE_SIZE;
#endif

#ifdef DMA_ALIGN_SIZE
    align = align > DMA_ALIGN_SIZE ? align : DMA_ALIGN_SIZE;
#endif

    align_size = RT_ALIGN(size, align) + align;
    ptr = rt_memheap_alloc(&_large_heap, align_size);
    if (ptr != RT_NULL)
    {
        /* the allocated memory block is aligned */
        if (((rt_uint32_t)ptr & (align - 1)) == 0)
        {
            align_ptr = (void *)((rt_uint32_t)ptr + align);
        }
        else
        {
            align_ptr = (void *)(((rt_uint32_t)ptr + (align - 1)) & ~(align - 1));
        }

        /* set the pointer before alignment pointer to the real pointer */
        *((rt_uint32_t *)((rt_uint32_t)align_ptr - sizeof(void *))) = (rt_uint32_t)ptr;

        ptr = align_ptr;
    }

    return ptr;
}
RTM_EXPORT(rt_dma_malloc_large);

void rt_dma_free_large(void *ptr)
{
    void *real_ptr;

    real_ptr = (void *) * (rt_uint32_t *)((rt_uint32_t)ptr - sizeof(void *));
    rt_memheap_free(real_ptr);
}
RTM_EXPORT(rt_dma_free_large);

#endif


#ifdef RT_USING_DTCM_HEAP
#include "hal_base.h"

static struct rt_memheap _dtcm_heap;
extern int __dtcm_start__, __dtcm_end__;

#define RK_DTCM_BEGIN   (&__dtcm_start__)
#define RK_DTCM_END     (&__dtcm_end__)

int rt_dtcm_heap_init(void)
{
    rt_err_t ret;
    rt_device_t dsp;

    dsp = rt_device_find("dsp0");
    RT_ASSERT(dsp != RT_NULL);

    ret = rt_device_open(dsp, RT_DEVICE_FLAG_RDWR);
    RT_ASSERT(ret == RT_EOK);

    return rt_memheap_init(&_dtcm_heap,
                           "dtcmheap",
                           RK_DTCM_BEGIN,
                           (rt_uint32_t)RK_DTCM_END - (rt_uint32_t)RK_DTCM_BEGIN);

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_dtcm_heap_init);

void *rt_malloc_dtcm(rt_size_t size)
{
    //rt_kprintf("rt_malloc_dtcm: size = %d\n", size);
    if (size < RT_DTCM_MALLOC_THRRESH)
        return NULL;

    return rt_memheap_alloc(&_dtcm_heap, size);
}
RTM_EXPORT(rt_malloc_dtcm);

void rt_free_dtcm(void *ptr)
{
    rt_memheap_free(ptr);
}
RTM_EXPORT(rt_free_dtcm);

void *rt_dma_malloc_dtcm(rt_size_t size)
{
    void *align_ptr;
    void *ptr;
    rt_size_t align, align_size;

    //rt_kprintf("rt_dma_malloc_dtcm: size = %d\n", size);
    if (size < RT_DTCM_MALLOC_THRRESH)
        return NULL;

    align = 4;
    align_size = 0;

#ifdef CACHE_LINE_SIZE
    align = CACHE_LINE_SIZE;
#endif

#ifdef DMA_ALIGN_SIZE
    align = align > DMA_ALIGN_SIZE ? align : DMA_ALIGN_SIZE;
#endif

    align_size = RT_ALIGN(size, align) + align;
    ptr = rt_memheap_alloc(&_dtcm_heap, align_size);
    if (ptr != RT_NULL)
    {
        /* the allocated memory block is aligned */
        if (((rt_uint32_t)ptr & (align - 1)) == 0)
        {
            align_ptr = (void *)((rt_uint32_t)ptr + align);
        }
        else
        {
            align_ptr = (void *)(((rt_uint32_t)ptr + (align - 1)) & ~(align - 1));
        }

        /* set the pointer before alignment pointer to the real pointer */
        *((rt_uint32_t *)((rt_uint32_t)align_ptr - sizeof(void *))) = (rt_uint32_t)ptr;

        ptr = align_ptr;
    }

    return ptr;
}
RTM_EXPORT(rt_dma_malloc_dtcm);

void rt_dma_free_dtcm(void *ptr)
{
    void *real_ptr;

    real_ptr = (void *) * (rt_uint32_t *)((rt_uint32_t)ptr - sizeof(void *));
    rt_memheap_free(real_ptr);
}
RTM_EXPORT(rt_dma_free_dtcm);

#endif


#ifdef RT_USING_PSRAM_HEAP
#include "hal_base.h"

static struct rt_memheap _psram_heap;
extern int __psramheap_start__, __psramheap_end__;

#define RK_PSRAMHEAP_BEGIN   (&__psramheap_start__)
#define RK_PSRAMHEAP_END     (&__psramheap_end__)

int rt_psram_heap_init(void)
{
    return rt_memheap_init(&_psram_heap,
                           "psramheap",
                           RK_PSRAMHEAP_BEGIN,
                           (rt_uint32_t)RK_PSRAMHEAP_END - (rt_uint32_t)RK_PSRAMHEAP_BEGIN);
}
INIT_COMPONENT_EXPORT(rt_psram_heap_init);

void *rt_malloc_psram(rt_size_t size)
{
    //rt_kprintf("rt_malloc_dtcm: size = %d\n", size);
    if (size < RT_PSRAM_MALLOC_THRRESH)
        return NULL;

    return rt_memheap_alloc(&_psram_heap, size);
}
RTM_EXPORT(rt_malloc_psram);

void rt_free_psram(void *ptr)
{
    rt_memheap_free(ptr);
}
RTM_EXPORT(rt_free_psram);

void *rt_dma_malloc_psram(rt_size_t size)
{
    void *align_ptr;
    void *ptr;
    rt_size_t align, align_size;

    //rt_kprintf("rt_dma_malloc_dtcm: size = %d\n", size);
    if (size < RT_PSRAM_MALLOC_THRRESH)
        return NULL;

    align = 4;
    align_size = 0;

#ifdef CACHE_LINE_SIZE
    align = CACHE_LINE_SIZE;
#endif

#ifdef DMA_ALIGN_SIZE
    align = align > DMA_ALIGN_SIZE ? align : DMA_ALIGN_SIZE;
#endif

    align_size = RT_ALIGN(size, align) + align;
    ptr = rt_memheap_alloc(&_psram_heap, align_size);
    if (ptr != RT_NULL)
    {
        /* the allocated memory block is aligned */
        if (((rt_uint32_t)ptr & (align - 1)) == 0)
        {
            align_ptr = (void *)((rt_uint32_t)ptr + align);
        }
        else
        {
            align_ptr = (void *)(((rt_uint32_t)ptr + (align - 1)) & ~(align - 1));
        }

        /* set the pointer before alignment pointer to the real pointer */
        *((rt_uint32_t *)((rt_uint32_t)align_ptr - sizeof(void *))) = (rt_uint32_t)ptr;

        ptr = align_ptr;
    }

    return ptr;
}
RTM_EXPORT(rt_dma_malloc_psram);

void rt_dma_free_psram(void *ptr)
{
    void *real_ptr;

    real_ptr = (void *) * (rt_uint32_t *)((rt_uint32_t)ptr - sizeof(void *));
    rt_memheap_free(real_ptr);
}
RTM_EXPORT(rt_dma_free_psram);

#endif
