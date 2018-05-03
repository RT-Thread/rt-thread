/*
 * File      : drv_mmc.c
 * This file is part of gkipc BSP for RT-Thread distribution.
 *
 * Copyright (c) 2017 chengdu goke Microelectronics Co., Ltd.
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

#include "platform.h"
#include <rtdef.h>
#include <rtdevice.h>
#include <drivers/mmcsd_core.h>
#include <dfs_fs.h>

#include "gd_sdio.h"
#include "drv_mmc.h"


//#define GK_MMC_DEBUG

#if defined(GK_MMC_DEBUG) && defined(RT_DEBUG)
#define PRINT_MMC_DBG(fmt, args...)                           \
    do                                                        \
    {                                                         \
        rt_kprintf("FH_MMC_DEBUG: tick-%d, ", rt_tick_get()); \
        rt_kprintf(fmt, ##args);                              \
    } while (0)
#else
#define PRINT_MMC_DBG(fmt, args...) \
    do                              \
    {                               \
    } while (0)
#endif


#define RT_SDIO_MAX_BLOCK_LEN       512    /*block size*/


/*GLOBAL SD DEVICE PONITER*/
static gk_mmc_driver_s sd_driver;
fs_sdio_notify_func_t notifyFunc = NULL;


static rt_err_t rt_sdcard_init(rt_device_t dev)
{
    gk_mmc_driver_s *mmc_drv = (gk_mmc_driver_s *)dev->user_data;
    rt_uint32_t index        = mmc_drv->handle.index;
    rt_uint32_t retVal       = RT_EOK;


    return RT_EOK;
}

static rt_err_t rt_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{
    gk_mmc_driver_s *mmc_drv = (gk_mmc_driver_s *)dev->user_data;
    rt_uint32_t index        = mmc_drv->handle.index;
    rt_uint32_t retVal       = RT_EOK;

    if (mmc_drv->handle.inUse == 0)
    {
        mmc_drv->openParams.isUseDmaWay      = 0;
        retVal = GD_SDIO_Open((GD_SDIO_OpenParamsT *)&mmc_drv->openParams,(sdioHandleT *)&mmc_drv->handle,index);
        if (retVal != RT_EOK)    {
            rt_kprintf("[%s:%d]GD_SDIO_Open failed!\n",__func__,__LINE__);
            return-RT_ENOMEM;
        }
    }
    else
    {
        PRINT_MMC_DBG("----ALREADY_OPEN SDIO_%d----\n",index);
    }

	return RT_EOK;
}

static rt_err_t rt_sdcard_close(rt_device_t dev)
{
    gk_mmc_driver_s *mmc_drv = (gk_mmc_driver_s *)dev->user_data;
    rt_uint32_t index        = mmc_drv->handle.index;
    rt_uint32_t retVal       = RT_EOK;


    retVal = GD_SDIO_Close((sdioHandleT *)&mmc_drv->handle,index);
    if (retVal != RT_EOK)
    {
        rt_kprintf("[%s-%s:%d] failed!,retVal = %d\n",__FILE__,__func__,__LINE__,retVal);
        return-RT_ENOMEM;
    }


    rt_device_unregister(mmc_drv->deviceP[index]);

    if (mmc_drv->deviceP[index] != NULL){
        rt_free(mmc_drv->deviceP[index]);
        mmc_drv->deviceP[index] = NULL;
    }

    if (mmc_drv->partP[index] != NULL)
    {
        rt_free(mmc_drv->partP[index]);
        mmc_drv->partP[index] = NULL;
    }

	return RT_EOK;
}

static rt_size_t rt_sdcard_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    gk_mmc_driver_s *mmc_drv   = (gk_mmc_driver_s *)dev->user_data;
    rt_uint32_t index          = mmc_drv->handle.index;
    struct dfs_partition *part = (struct dfs_partition *)mmc_drv->partP[index];
    rt_uint32_t retVal         = RT_EOK;

    rt_sem_take(part->lock, RT_WAITING_FOREVER);
    retVal = GD_SDIO_ReadSector((sdioHandleT *)&mmc_drv->handle, pos, buffer, size);
    if (retVal != RT_EOK)
    {
        rt_kprintf("[%s-%s:%d]error!,retVal = %d\n",__FILE__,__func__,__LINE__,retVal);
        rt_sem_release(part->lock);
        return -RT_ENOMEM;
    }
    rt_sem_release(part->lock);

    return size;

}

static rt_size_t rt_sdcard_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    gk_mmc_driver_s *mmc_drv   = (gk_mmc_driver_s *)dev->user_data;
    rt_uint32_t index          = mmc_drv->handle.index;
    struct dfs_partition *part = (struct dfs_partition *)mmc_drv->partP[index];
    rt_uint32_t retVal         = RT_EOK;

    rt_sem_take(part->lock, RT_WAITING_FOREVER);
    retVal = GD_SDIO_WriteSector((sdioHandleT *)&mmc_drv->handle,pos,(void*)buffer,size);
    if (retVal != RT_EOK)
    {
        rt_kprintf("[%s-%s:%d]GD_SDIO_WriteSector failed!\n",__FILE__,__func__,__LINE__);
        rt_sem_release(part->lock);
        return -RT_ENOMEM;
    }
    rt_sem_release(part->lock);

    return size;
}

static rt_err_t rt_sdcard_control(rt_device_t dev, int cmd, void *args)
{
    gk_mmc_driver_s *mmc_drv   = (gk_mmc_driver_s *)dev->user_data;
    rt_uint32_t index          = mmc_drv->handle.index;
    struct dfs_partition *part = (struct dfs_partition *)mmc_drv->partP[index];
    rt_uint32_t retVal         = RT_EOK;


    switch(cmd)
    {
        case RT_DEVICE_CTRL_BLK_GETGEOME:
        {
            struct rt_device_blk_geometry *geometry;
            GD_SDIO_VolumeInfoT sdInfo;
            rt_memset(&sdInfo,0,sizeof(sdInfo));
            geometry = (struct rt_device_blk_geometry *)args;
            retVal = GD_SDIO_GetCardInfo((sdioHandleT *)&mmc_drv->handle,&sdInfo,index);
            if (retVal != RT_EOK)
            {
                rt_kprintf("[%s:%d]GD_SDIO_GetCardInfo failed!\n",__func__,__LINE__);
                return-RT_ENOMEM;
            }

            geometry->block_size       = sdInfo.sectorSize;
            geometry->sector_count     = sdInfo.sectorCount;
            geometry->bytes_per_sector = sdInfo.sectorSize;
            PRINT_MMC_DBG("[%s:%d]sd card block_size:%d,sector_count:%d!\n",__func__,__LINE__,
                                                        geometry->block_size,geometry->sector_count);

            break;
        }

        case RT_DEVICE_CTRL_BLK_ERASE:
        {
            unsigned int eraseAdress = 0x00;
            unsigned short blkcnt = *(unsigned short *)args;
            retVal = GD_SDIO_EraseSector((sdioHandleT *)&mmc_drv->handle,eraseAdress,blkcnt);
            if (retVal != RT_EOK)
            {
                rt_kprintf("[%s-%s:%d]GD_SDIO_EraseSector failed!\n",__FILE__,__func__,__LINE__);
                return-RT_ENOMEM;
            }

            break;
        }

        default:break;
    }


	return RT_EOK;
}


int rt_hw_mmc_init(gk_mmc_driver_s *pMmcParams)
{
    gk_mmc_driver_s *mmc_drv   = &sd_driver;
    rt_uint32_t index          = pMmcParams->handle.index;
    rt_uint32_t retVal         = RT_EOK;
    rt_uint8_t *sector         = NULL;
    rt_uint8_t sname[8]        = {0};
    rt_uint8_t sdDeviceName[4] = {0};

    if (pMmcParams == NULL)
    {
        rt_kprintf("[%s:%d] sdio init params is error!\n",__func__,__LINE__);
        return -RT_ENOMEM;
    }

    mmc_drv->openParams.isUseDmaWay      = pMmcParams->openParams.isUseDmaWay;
    mmc_drv->openParams.notifyFunc       = pMmcParams->openParams.notifyFunc;
    mmc_drv->openParams.notifyFuncOptPtr = pMmcParams->openParams.notifyFuncOptPtr;
    retVal = GD_SDIO_Open((GD_SDIO_OpenParamsT *)&mmc_drv->openParams,(sdioHandleT *)&mmc_drv->handle,index);
    if (retVal != RT_EOK)    {
        rt_kprintf("[%s:%d]GD_SDIO_Open failed!\n",__func__,__LINE__);
        return -RT_ENOMEM;
    }

    /* get the first sector to read partition table */
    sector = (rt_uint8_t*) rt_malloc (RT_SDIO_MAX_BLOCK_LEN);
    if (sector == RT_NULL)
    {
        rt_kprintf("allocate partition sector buffer failed\n");
        GD_SDIO_Close((sdioHandleT *)&mmc_drv->handle,index);
        return -RT_ENOMEM;
    }

    /*alloc device buffer*/
    mmc_drv->deviceP[index] = (struct rt_device*)rt_malloc(sizeof(struct rt_device));
    if(mmc_drv->deviceP[index] == RT_NULL)
    {
         rt_kprintf("[%s:%d]allocate device failed\n",__func__,__LINE__);
         GD_SDIO_Close((sdioHandleT *)&mmc_drv->handle,index);
         return -RT_ENOMEM;
    }

    mmc_drv->partP[index] = (struct dfs_partition*)rt_malloc(sizeof(struct dfs_partition));
    if(mmc_drv->partP[index] == RT_NULL)
    {
         rt_kprintf("[%s:%d]allocate partP failed\n",__func__,__LINE__);
         GD_SDIO_Close((sdioHandleT *)&mmc_drv->handle,index);
         return -RT_ENOMEM;
    }

    retVal = GD_SDIO_ReadSector((sdioHandleT *)&mmc_drv->handle, 0, sector, 1);
    if (retVal != RT_EOK)
    {
        rt_kprintf("[%s-%s:%d]GD_SDIO_ReadSector failed!\n",__FILE__,__func__,__LINE__);
        GD_SDIO_Close((sdioHandleT *)&mmc_drv->handle,index);
        goto err;
    }

    /* get the first partition */
    retVal = dfs_filesystem_get_partition(mmc_drv->partP[index], sector, 0);
    if (retVal != RT_EOK)
    {
        rt_kprintf("[%s-%s:%d] failed!,retVal = %d\n",__FILE__,__func__,__LINE__,retVal);
        GD_SDIO_Close((sdioHandleT *)&mmc_drv->handle,index);
        goto err;
    }
    rt_snprintf(sname, 8, "sem_sd%d", index);
    mmc_drv->partP[index]->lock = rt_sem_create(sname, 1, RT_IPC_FLAG_FIFO);

    /* sdcard hardware init */
    rt_memset(mmc_drv->deviceP[index],0,sizeof(struct rt_device));
    mmc_drv->deviceP[index]->type       = RT_Device_Class_Block;
    mmc_drv->deviceP[index]->init       = rt_sdcard_init;
    mmc_drv->deviceP[index]->open       = rt_sdcard_open;
    mmc_drv->deviceP[index]->close      = rt_sdcard_close;
    mmc_drv->deviceP[index]->read       = rt_sdcard_read;
    mmc_drv->deviceP[index]->write      = rt_sdcard_write;
    mmc_drv->deviceP[index]->control    = rt_sdcard_control;
    mmc_drv->deviceP[index]->user_data  = (void *)mmc_drv;


    rt_snprintf(sdDeviceName, 4, "sd%d",index);
    retVal = rt_device_register(mmc_drv->deviceP[index], sdDeviceName,
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

    if (retVal != RT_EOK)
    {
        rt_kprintf("[%s:%d]rt_device_register name :%s failed!\n",__func__,__LINE__,sdDeviceName);
        GD_SDIO_Close((sdioHandleT *)&mmc_drv->handle,index);
        goto err;
    }

    /* release sector buffer */
    if (sector != NULL){
        rt_free(sector);
        sector = NULL;
    }

    return RT_EOK;

err:
    if (mmc_drv->deviceP[index] != NULL){
        rt_free(mmc_drv->deviceP[index]);
        mmc_drv->deviceP[index] = NULL;
    }

    if (mmc_drv->partP[index] != NULL)
    {
        rt_free(mmc_drv->partP[index]);
        mmc_drv->partP[index] = NULL;
    }

    if (sector != NULL){
        rt_free(sector);
        sector = NULL;
    }

    return -RT_ETIMEOUT;

}

