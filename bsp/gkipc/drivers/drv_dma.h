/*
 * File      : drv_dma.h
 * This file is part of FH8620 BSP for RT-Thread distribution.
 *
 * Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd.
 * All rights reserved
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
 *  Visit http://www.fullhan.com to get contact with Fullhan.
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
#define RT_DEVICE_CTRL_DMA_OPEN (1)
#define RT_DEVICE_CTRL_DMA_CLOSE (2)
#define RT_DEVICE_CTRL_DMA_REQUEST_CHANNEL (3)
#define RT_DEVICE_CTRL_DMA_RELEASE_CHANNEL (4)
#define RT_DEVICE_CTRL_DMA_SINGLE_TRANSFER (5)

// cyclic add func below....

#define RT_DEVICE_CTRL_DMA_CYCLIC_PREPARE (6)
#define RT_DEVICE_CTRL_DMA_CYCLIC_START (7)
#define RT_DEVICE_CTRL_DMA_CYCLIC_STOP (8)
#define RT_DEVICE_CTRL_DMA_CYCLIC_FREE (9)
#define RT_DEVICE_CTRL_DMA_PAUSE (10)
#define RT_DEVICE_CTRL_DMA_RESUME (11)

//#define RT_DEVICE_CTRL_  	 (3) /* get the left time before reboot(in
//seconds) */
//#define RT_DEVICE_CTRL_      (4) /* refresh watchdog */
//#define RT_DEVICE_CTRL_      (5) /* start watchdog */
//#define RT_DEVICE_CTRL_      (6) /* stop watchdog */

/****************************************************************************
* ADT section
*	add Abstract Data Type definition here
***************************************************************************/

#define ADC_CMD_READ_RAW_DATA (0x22)
#define ADC_CMD_DISABLE (0x44)


/*dma cmd */
typedef enum
{
    DMA_CMD_ADD_DESCRIPTOR = 0,
    DMA_CMD_START,
    DMA_CMD_STOP,
}RT_DMA_DMD;



typedef void (*RT_DMA_NOTIFIER_F)(void);

typedef struct rt_dma_descriptor_s
{
    rt_uint32_t srcAddr;        /*  Source address */
    rt_uint32_t dstAddr;        /* Destination address */
    struct dma_descriptor_s *next; /* Pointing to next descriptor */
    rt_uint32_t reportAddr;     /* The physical address to store DMA hardware reporting status */
    rt_uint32_t dataLength;     /* Transfer byte count , max value = 2^22 */
    rt_uint32_t descAttr;       /* Descriptor 's attribute */
}RT_DMA_DESCRIPTOR_S;

typedef struct
{
    rt_uint32_t      channel;
    rt_uint32_t      mode;
	RT_DMA_NOTIFIER_F intNotifier;
}RT_DMA_OPEN_PARAM_S;

typedef struct rt_dma_device
{
    // the parent must be the fitst para..
    rt_uint32_t         handle;
    struct rt_device    parent;
    RT_DMA_OPEN_PARAM_S openParam;
}rt_dma_device_s;


/****************************************************************************
*  extern variable declaration section
***************************************************************************/

/****************************************************************************
*  section
*	add function prototype here if any
***************************************************************************/

void rt_gk_dma_init(void);

/********************************End Of File********************************/

#endif
