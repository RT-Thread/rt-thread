/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

