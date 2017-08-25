/**\file
 *  This file defines the wrapper for the platform/OS related functions
 *  The function definitions needs to be modified according to the platform 
 *  and the Operating system used.
 *  This file should be handled with greatest care while porting the driver
 *  to a different platform running different operating system other than
 *  Linux 2.6.xx.
 * \internal
 * ----------------------------REVISION HISTORY-----------------------------
 * Synopsys			01/Aug/2007			Created
 */


/*
 * File      : synopGMAC_plat.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) chinesebear
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-24     chinesebear  first version
 */

 
#include "synopGMAC_plat.h"
#include "synopGMAC_Dev.h"
#include <rthw.h>
#include <rtthread.h>
extern void flush_cache(unsigned long start_addr, unsigned long size);
dma_addr_t __attribute__((weak)) gmac_dmamap(unsigned long va,u32 size)
{
	return VA_TO_PA (va);
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
	void *buf = (void*)rt_malloc((u32)bytes);

	flush_cache((unsigned long)buf, bytes);
	return buf;
}

/**
  * This is a wrapper function for consistent dma-able Memory allocation routine. 
  * In linux Kernel, it depends on pci dev structure
  * @param[in] bytes in bytes to allocate
  */

//void *plat_alloc_consistent_dmaable_memory(struct synopGMACdevice *dev, u32 size, u32 *addr) 
void *plat_alloc_consistent_dmaable_memory(synopGMACdevice *pcidev, u32 size, u32 *addr) 
{
	void *buf;
	buf = (void*)rt_malloc((u32)(size+16));
	//CPU_IOFlushDCache( buf,size, SYNC_W);
	unsigned long i = (unsigned long)buf;
//	rt_kprintf("size = %d\n", size);
//	rt_kprintf("bufaddr = %p\n", buf);
//	rt_kprintf("i%%16 == %d\n", i%16);
	if(i%16 == 8){
		i += 8;
	}
	else if(i%16 == 4){
		i += 12;
	}
	else if(i%16 == 12){
		i += 4;
	}

	flush_cache(i, size);
	*addr =gmac_dmamap(i, size);
	buf = (unsigned char *)CACHED_TO_UNCACHED(i);
//	rt_kprintf("bufaddr = %p\n", buf);
	return buf;
}


/**
  * This is a wrapper function for freeing consistent dma-able Memory.
  * In linux Kernel, it depends on pci dev structure
  * @param[in] bytes in bytes to allocate
  */


//void plat_free_consistent_dmaable_memory(void * addr) 
void plat_free_consistent_dmaable_memory(synopGMACdevice *pcidev, u32 size, void * addr,u32 dma_addr) 
{
	rt_free((void*)PHYS_TO_CACHED(UNCACHED_TO_PHYS(addr)));
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



dma_addr_t plat_dma_map_single(void *hwdev, void *ptr,
		                    u32 size)
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


