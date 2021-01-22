/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-24     chinesebear  first version
 * 2020-08-10     lizhirui     porting to ls2k
 */
#include "synopGMAC_plat.h"
#include "synopGMAC_Dev.h"
#include <rthw.h>
#include <rtthread.h>

void flush_cache(unsigned long start_addr, unsigned long size)
{
    /*r4k_dcache_wback_inv(start_addr,size);

    //rt_kprintf("flush_cache:start_addr = 0x%p,size = 0x%p",start_addr,size);
    unsigned long new_addr = start_addr - CACHED_MEMORY_ADDR + UNCACHED_MEMORY_ADDR;
    rt_memcpy(new_addr,start_addr,size);

    if(rt_memcmp(start_addr,new_addr,size) != 0)
    {
        rt_kprintf("flush_cache:data isn't matched!\n");
        while(1);
    }
    else
    {
        //rt_kprintf("flush_cache:data is matched!\n");
    }*/
}

//convert virtual address to physical address
dma_addr_t __attribute__((weak)) gmac_dmamap(unsigned long va, u32 size)
{
    return VA_TO_PA(va);
    //return UNCACHED_TO_PHYS(va);
}

/**
  * This is a wrapper function for Memory allocation routine. In linux Kernel
  * it it kmalloc function
  * @param[in] bytes in bytes to allocate
  */

void *plat_alloc_memory(u32 bytes)
{
//return (void*)malloc((size_t)bytes, M_DEVBUF, M_DONTWAIT);
    void *buf = (void *)rt_malloc((u32)bytes);
    flush_cache((unsigned long)buf, bytes);
    return buf;
}

/**
  * This is a wrapper function for consistent dma-able Memory allocation routine.
  * In linux Kernel, it depends on pci dev structure
  * @param[in] bytes in bytes to allocate
  */

//allocate a space aligned to 16-byte boundary without cache
void *plat_alloc_consistent_dmaable_memory(synopGMACdevice *pcidev, u32 size, u32 *addr)
{
    void *buf;
    buf = (void *)rt_malloc((u32)(size + 16));
    //CPU_IOFlushDCache( buf,size, SYNC_W);
    unsigned long i = (unsigned long)buf;
//    rt_kprintf("size = %d\n", size);
//    rt_kprintf("bufaddr = %p\n", buf);
//    rt_kprintf("i%%16 == %d\n", i%16);
    if (i % 16 == 8)
    {
        i += 8;
    }
    else if (i % 16 == 4)
    {
        i += 12;
    }
    else if (i % 16 == 12)
    {
        i += 4;
    }

    flush_cache(i, size);
    *addr = gmac_dmamap(i, size);
    buf = (unsigned char *)CACHED_TO_UNCACHED(i);
    //rt_kprintf("bufaddr = %p\n", buf);
    return buf;
}

/**
  * This is a wrapper function for freeing consistent dma-able Memory.
  * In linux Kernel, it depends on pci dev structure
  * @param[in] bytes in bytes to allocate
  */
//void plat_free_consistent_dmaable_memory(void * addr)
void plat_free_consistent_dmaable_memory(synopGMACdevice *pcidev, u32 size, void *addr, u64 dma_addr)
{
    rt_free((void *)PHYS_TO_CACHED(UNCACHED_TO_PHYS(addr)));
    return;
}

/**
  * This is a wrapper function for Memory free routine. In linux Kernel
  * it it kfree function
  * @param[in] buffer pointer to be freed
  */
void plat_free_memory(void *buffer)
{
    rt_free(buffer);
    return ;
}

//convert virtual address to physical address and flush cache
dma_addr_t plat_dma_map_single(void *hwdev, void *ptr, u32 size)
{
    unsigned long addr = (unsigned long) ptr;
    //CPU_IOFlushDCache(addr,size, direction);
    flush_cache(addr, size);
    return gmac_dmamap(addr, size);
}

/**
  * This is a wrapper function for platform dependent delay
  * Take care while passing the argument to this function
  * @param[in] buffer pointer to be freed
  */
void plat_delay(u32 delay)
{
    while (delay--);
    return;
}
