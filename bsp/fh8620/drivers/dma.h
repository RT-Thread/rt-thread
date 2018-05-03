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

#ifndef DMA_H_
#define DMA_H_
#include <rtthread.h>
/****************************************************************************
* #include section
*	add #include here if any
***************************************************************************/


/****************************************************************************
* #define section
*	add constant #define here if any
***************************************************************************/
#define RT_DEVICE_CTRL_DMA_OPEN						(1)
#define RT_DEVICE_CTRL_DMA_CLOSE					(2)
#define RT_DEVICE_CTRL_DMA_REQUEST_CHANNEL    		(3)
#define RT_DEVICE_CTRL_DMA_RELEASE_CHANNEL   	 	(4)
#define RT_DEVICE_CTRL_DMA_SINGLE_TRANSFER			(5)


//cyclic add func below....


#define RT_DEVICE_CTRL_DMA_CYCLIC_PREPARE			(6)
#define RT_DEVICE_CTRL_DMA_CYCLIC_START				(7)
#define RT_DEVICE_CTRL_DMA_CYCLIC_STOP				(8)
#define RT_DEVICE_CTRL_DMA_CYCLIC_FREE				(9)


//#define RT_DEVICE_CTRL_  	 (3) /* get the left time before reboot(in seconds) */
//#define RT_DEVICE_CTRL_      (4) /* refresh watchdog */
//#define RT_DEVICE_CTRL_      (5) /* start watchdog */
//#define RT_DEVICE_CTRL_      (6) /* stop watchdog */





/****************************************************************************
* ADT section
*	add Abstract Data Type definition here
***************************************************************************/

struct rt_dma_ops;
struct rt_dma_device
{
	// the parent must be the fitst para..
    struct rt_device parent;
    struct rt_dma_ops *ops;
};


struct rt_dma_ops
{
    rt_err_t (*init)(struct rt_dma_device *dma);
    rt_err_t (*control)(struct rt_dma_device *dma, int cmd, void *arg);
};




/****************************************************************************
*  extern variable declaration section
***************************************************************************/

/****************************************************************************
*  section
*	add function prototype here if any
***************************************************************************/
rt_err_t rt_hw_dma_register(struct rt_dma_device *dma,
                                 const char    *name,
                                 rt_uint32_t    flag,
                                 void          *data);

/********************************End Of File********************************/




#endif

