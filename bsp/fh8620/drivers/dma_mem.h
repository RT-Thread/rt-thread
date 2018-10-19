/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef DMA_MEM_H_
#define DMA_MEM_H_



#ifndef RT_USING_MEMHEAP
#define RT_USING_MEMHEAP
#endif

#include <rtthread.h>
/****************************************************************************
* #include section
*	add #include here if any
***************************************************************************/


/****************************************************************************
* #define section
*	add constant #define here if any
***************************************************************************/



/****************************************************************************
* ADT section
*	add Abstract Data Type definition here
***************************************************************************/




/****************************************************************************
*  extern variable declaration section
***************************************************************************/

/****************************************************************************
*  section
*	add function prototype here if any
***************************************************************************/
#ifdef RT_USING_DMA_MEM
rt_err_t fh_dma_mem_init(rt_uint32_t *mem_start,rt_uint32_t size);
void *fh_dma_mem_malloc(rt_uint32_t size);
void fh_dma_mem_free(void *ptr);
/********************************End Of File********************************/


#endif

#endif

