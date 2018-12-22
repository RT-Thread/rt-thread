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

