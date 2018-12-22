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
#include "drivers/dma.h"
/*****************************************************************************
 * Define section
 * add all #define here
 *****************************************************************************/


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
static rt_err_t rt_dma_init(struct rt_device *dev);
static rt_err_t rt_dma_open(struct rt_device *dev, rt_uint16_t oflag);
static rt_err_t rt_dma_close(struct rt_device *dev);
static rt_err_t rt_dma_control(struct rt_device *dev,
                                    rt_uint8_t        cmd,
                                    void             *args);
/*****************************************************************************
 * Global variables section - Local
 * define global variables(will be refered only in this file) here,
 * static keyword should be used to limit scope of local variable to this file
 * e.g.
 *  static uint8_t ufoo;
 *****************************************************************************/




 /* function body */
/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/
static rt_err_t rt_dma_init(struct rt_device *dev)
{
	struct rt_dma_device *dma;

    RT_ASSERT(dev != RT_NULL);
    dma = (struct rt_dma_device *)dev;
    if (dma->ops->init)
    {
        return (dma->ops->init(dma));
    }

    return (-RT_ENOSYS);
}

static rt_err_t rt_dma_open(struct rt_device *dev, rt_uint16_t oflag)
{
    return (RT_EOK);
}

static rt_err_t rt_dma_close(struct rt_device *dev)
{
	struct rt_dma_device *dma;

    RT_ASSERT(dev != RT_NULL);
    dma = (struct rt_dma_device *)dev;

    if (dma->ops->control(dma, RT_DEVICE_CTRL_DMA_CLOSE, RT_NULL) != RT_EOK)
    {
        return (-RT_ERROR);
    }

    return (RT_EOK);
}

static rt_err_t rt_dma_control(struct rt_device *dev,
                                    rt_uint8_t        cmd,
                                    void             *args)
{
	struct rt_dma_device *dma;

    RT_ASSERT(dev != RT_NULL);
    dma = (struct rt_dma_device *)dev;

    //args is the private data for the soc!!
    return (dma->ops->control(dma, cmd, args));
}

/**
 * This function register a dma device
 */
rt_err_t rt_hw_dma_register(struct rt_dma_device *dma,
                                 const char                *name,
                                 rt_uint32_t                flag,
                                 void                      *data)
{
	rt_uint32_t ret;
    struct rt_device *device;
    RT_ASSERT(dma != RT_NULL);

    device = &(dma->parent);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    device->init        = rt_dma_init;
    device->open        = rt_dma_open;
    device->close       = rt_dma_close;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = rt_dma_control;
    device->user_data   = data;

    /* register a character device */
    ret = rt_device_register(device, name, flag);
    rt_kprintf("dma ret is :%x\n",ret);
    return ret;
}




