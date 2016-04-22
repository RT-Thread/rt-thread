/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
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
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
/*****************************************************************************
 *  Include Section
 *  add all #include here
 *****************************************************************************/


#include "dma_mem.h"
#ifdef RT_USING_DMA_MEM

/*****************************************************************************
 * Define section
 * add all #define here
 *****************************************************************************/
//#define FH_TEST_DMA_MEM

/****************************************************************************
 * ADT section
 *  add definition of user defined Data Type that only be used in this file  here
 ***************************************************************************/


/******************************************************************************
 * Function prototype section
 * add prototypes for all functions called by this file,execepting those
 * declared in header file
 *****************************************************************************/


/*****************************************************************************
 * Global variables section - Exported
 * add declaration of global variables that will be exported here
 * e.g.
 *  int8_t foo;
 ****************************************************************************/


/*****************************************************************************

 *  static fun;
 *****************************************************************************/

/*****************************************************************************
 * Global variables section - Local
 * define global variables(will be refered only in this file) here,
 * static keyword should be used to limit scope of local variable to this file
 * e.g.
 *  static uint8_t ufoo;
 *****************************************************************************/

static struct rt_memheap dma_heap = {0};


 /* function body */
/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/
rt_err_t fh_dma_mem_init(rt_uint32_t *mem_start,rt_uint32_t size){
	return rt_memheap_init(&dma_heap,"dma_heap",mem_start,size);
}


void *fh_dma_mem_malloc(rt_uint32_t size){
	return rt_memheap_alloc(&dma_heap, size);
}


void fh_dma_mem_free(void *ptr){
	rt_memheap_free(ptr);
}

#ifdef FH_TEST_DMA_MEM
int dma_mem_debug(void *ptr){
	//rt_memheap_free(ptr);
	rt_kprintf("dma mem start 0x%08x\n",(rt_uint32_t)dma_heap.start_addr);
	rt_kprintf("dma mem total size 0x%08x\n",dma_heap.pool_size);
	rt_kprintf("dma mem left size 0x%08x\n",dma_heap.available_size);
	rt_kprintf("dma mem max use size 0x%08x\n",dma_heap.max_used_size);
	return 0;
}
#endif

#ifdef RT_USING_FINSH
#include <finsh.h>
#ifdef FH_TEST_DMA_MEM
FINSH_FUNCTION_EXPORT(dma_mem_debug, dma_start & left size & max_use);
#endif
#endif


#endif

