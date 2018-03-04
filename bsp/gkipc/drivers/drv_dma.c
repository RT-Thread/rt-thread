/*
 * File      : drv_dma.c
 * This file is part of gkipc BSP for RT-Thread distribution.
 *
 * Copyright (c) 2017 ChengDu goke Microelectronics Co., Ltd.
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
 *  Visit http://www.goke.com to get contact with goke.
 *
 * Change Logs:
 * Date           Author       Notes
 */

/*****************************************************************************
 *  Include Section
 *  add all #include here
 *****************************************************************************/
#include "drivers/drv_dma.h"

#include "gd_dma.h"

/*****************************************************************************
 * Define section
 * add all #define here
 *****************************************************************************/

//#define GK_DMA_DEBUG
#ifndef GK_DMA_DEBUG
#define DMA_PRINT_DBG(fmt, args...)
#define DMA_PRINT_ERR(fmt, args...) rt_kprintf(fmt, ##args);
#else
#define DMA_PRINT_DBG(fmt, args...) rt_kprintf(fmt, ##args);
#define DMA_PRINT_ERR(fmt, args...) rt_kprintf(fmt, ##args);
#endif

/****************************************************************************
 * ADT section
 *  add definition of user defined Data Type that only be used in this file here
 ***************************************************************************/

static struct rt_dma_device _dma_device;


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
static rt_err_t rt_dma_control(struct rt_device *dev, int cmd,void *args);
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
    return (RT_EOK);
}

static rt_err_t rt_dma_open(struct rt_device *dev, rt_uint16_t oflag)
{
    rt_uint32_t retVal = 0;
    struct rt_dma_device *dma;

    RT_ASSERT(dev != RT_NULL);
    dma = (struct rt_dma_device *)dev->user_data;

    retVal = GD_DMA_Open((GD_DMA_OPEN_PARAM_S *)&dma->openParam,(GD_HANDLE *)&dma->handle);
    if(retVal != RT_EOK)
    {
        DMA_PRINT_ERR("GD_DMA_Open failed!\n");
        return (-RT_ERROR);
    }

    return (RT_EOK);
}

static rt_err_t rt_dma_close(struct rt_device *dev)
{
    rt_uint32_t retVal = 0;
    struct rt_dma_device *dma;

    RT_ASSERT(dev != RT_NULL);
    dma = (struct rt_dma_device *)dev->user_data;

    GD_DMA_Stop((GD_HANDLE)dma->handle);

    retVal = GD_DMA_Close((GD_HANDLE)dma->handle);
    if (retVal != RT_EOK)
    {
        DMA_PRINT_ERR("GD_DMA_Close failed!\n");
        return (-RT_ERROR);
    }

    return (RT_EOK);
}

static rt_err_t rt_dma_control(struct rt_device *dev, int cmd,void *args)
{
    rt_uint32_t retVal = 0;
    rt_uint32_t des    = 0;
    RT_DMA_DESCRIPTOR_S *descriptor;

    struct rt_dma_device *dma;
    RT_ASSERT(dev != RT_NULL);
    dma = (struct rt_dma_device *)dev->user_data;

    switch(cmd)
    {
        case DMA_CMD_ADD_DESCRIPTOR:
            descriptor = (RT_DMA_DESCRIPTOR_S *)args;
            retVal = GD_DMA_AddDescriptor((GD_HANDLE)dma->handle,(GD_DMA_DESCRIPTOR_S *)descriptor);
            if (retVal != RT_EOK)
            {
                DMA_PRINT_ERR("GD_DMA_AddDescriptor failed!\n");
                return (-RT_ERROR);
            }

            break;

        case DMA_CMD_START:
            des = *(rt_uint32_t*)args;
            retVal = GD_DMA_Start((GD_HANDLE)dma->handle,des);
            if (retVal != RT_EOK)
            {
                DMA_PRINT_ERR("GD_DMA_Start failed!\n");
                return (-RT_ERROR);
            }

            break;

        case DMA_CMD_STOP:
            GD_DMA_Stop((GD_HANDLE)dma->handle);
            break;

        default:break;


    }

    return (RT_EOK);
}

/**
 * This function register a dma device
 */
static rt_err_t rt_hw_dma_register(const char *name,rt_uint32_t flag)
{
    rt_uint32_t ret;
    struct rt_device *device;

    device = &(_dma_device.parent);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    device->init      = rt_dma_init;
    device->open      = rt_dma_open;
    device->close     = rt_dma_close;
    device->read      = RT_NULL;
    device->write     = RT_NULL;
    device->control   = rt_dma_control;
    device->user_data = (void *)&_dma_device;

    /* register a character device */
    ret = rt_device_register(device, name, flag);

    return ret;
}

void rt_gk_dma_init(void)
{
    rt_uint32_t retVal = 0;

    retVal = GD_DMA_Init();
    if (retVal != RT_EOK)
    {
        DMA_PRINT_ERR("GD_DMA_Init failed!\n");
		return;
    }

    rt_hw_dma_register("gk_dma",RT_DEVICE_FLAG_RDWR);
}

