/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-07-26     Ltbonewstart  the first version
 *
 */
#include "fsl_romapi.h"

#include <rtdevice.h>

//#define DRV_DEBUG
#define LOG_TAG             "drv.flash"
#include <drv_log.h>

#define SECTOR_INDEX_FROM_END   2U /* start from the last 2 Sector */

struct mcx_mtd_chipflash
{
    struct rt_mtd_nor_device mtd_device;
    struct rt_mutex flash_lock;
    flash_config_t s_flashDriver;   /* flash driver */
    uint32_t destAdrss;             /* Address of the target location */
    uint32_t pflashBlockBase;       /* 块基地址 */
    uint32_t pflashBlockSize;       /* 块大小 */
    uint32_t pflashBlockCount;      /* 块数量 */
    uint32_t pflashTotalSize;       /* 总大小 */
    uint32_t pflashSectorSize;      /* 扇区大小 */
    uint32_t PflashPageSize;        /* 页大小 */
};

struct mcx_mtd_chipflash mtd;

/**
 * device MTD nor 设备句柄
 * offset 偏移量
 * data 读取的数据
 * length 读取的数据长度
 */
rt_ssize_t nxp_chipflash_read(struct rt_mtd_nor_device *device, rt_off_t offset, rt_uint8_t *data, rt_size_t length)
{
    rt_mutex_take(&mtd.flash_lock, RT_WAITING_FOREVER);
    memcpy(data, ((const void *)(mtd.destAdrss + offset)), length);
    rt_mutex_release(&mtd.flash_lock);
    return length;
}

/**
 * device MTD nor 设备句柄
 * offset 偏移量
 * data 读取的数据
 * length 读取的数据长度
 */
rt_ssize_t nxp_chipflash_write(struct rt_mtd_nor_device *device, rt_off_t offset, const rt_uint8_t *data, rt_size_t length)
{
    rt_mutex_take(&mtd.flash_lock, RT_WAITING_FOREVER);
    int32_t status = FLASH_ProgramPhrase(&mtd.s_flashDriver, mtd.destAdrss + offset, (uint8_t *)data, length);
    if (status != kStatus_Success)
    {
        length = 0;
    }
    rt_mutex_release(&mtd.flash_lock);
    return length;
}

/**
 * device MTD nor 设备句柄
 * offset 偏移量
 * length 长度
 */
rt_err_t nxp_chipflash_erase_block(struct rt_mtd_nor_device *device, rt_off_t offset, rt_size_t length)
{
    rt_mutex_take(&mtd.flash_lock, RT_WAITING_FOREVER);
    FLASH_EraseSector(&mtd.s_flashDriver, mtd.destAdrss + offset, mtd.pflashSectorSize, kFLASH_ApiEraseKey);
    rt_mutex_release(&mtd.flash_lock);
    return RT_EOK;
}

struct rt_mtd_nor_driver_ops mcx_mtd_chipflashops =
{
    RT_NULL,
    nxp_chipflash_read,
    nxp_chipflash_write,
    nxp_chipflash_erase_block,
};

int rt_onchip_flash_init(void)
{
    rt_err_t result = RT_EOK;

    memset(&mtd.s_flashDriver, 0, sizeof(flash_config_t));
    if (FLASH_Init(&mtd.s_flashDriver) != kStatus_Success)
    {
        result = -RT_ERROR;
    }

    /* 获取参数 */
    FLASH_GetProperty(&mtd.s_flashDriver, kFLASH_PropertyPflashBlockBaseAddr, &mtd.pflashBlockBase);
    FLASH_GetProperty(&mtd.s_flashDriver, kFLASH_PropertyPflashSectorSize, &mtd.pflashSectorSize);
    FLASH_GetProperty(&mtd.s_flashDriver, kFLASH_PropertyPflashTotalSize, &mtd.pflashTotalSize);
    FLASH_GetProperty(&mtd.s_flashDriver, kFLASH_PropertyPflashPageSize, &mtd.PflashPageSize);
    FLASH_GetProperty(&mtd.s_flashDriver, kFLASH_PropertyPflashBlockSize, &mtd.pflashBlockSize);
    FLASH_GetProperty(&mtd.s_flashDriver, kFLASH_PropertyPflashBlockCount, &mtd.pflashBlockCount);

    LOG_D("flash_BlockBase:     %d", mtd.pflashBlockBase);
    LOG_D("flash_BlockCount:    %d", mtd.pflashBlockCount);
    LOG_D("flash_BlockSize:     %d", mtd.pflashBlockSize);
    LOG_D("flash_SectorSize:    %d", mtd.pflashSectorSize);
    LOG_D("flash_TotalSize:     %d", mtd.pflashTotalSize);
    LOG_D("flash_PageSize:      %d", mtd.PflashPageSize);

    /* 设置要测试flash的基地址 */
    /* flash基地址+ flash总大小 - 数量*扇区大小 */
    mtd.destAdrss = mtd.pflashBlockBase + (mtd.pflashTotalSize - (SECTOR_INDEX_FROM_END) * mtd.pflashSectorSize);
    LOG_D("flash_destAdrss:     %#x", mtd.destAdrss);

    /* initialize mutex */
    if (rt_mutex_init(&mtd.flash_lock, "m_flash", RT_IPC_FLAG_PRIO) != RT_EOK)
    {
        rt_kprintf("init mflash lock mutex failed\n");
        return -RT_ERROR;
    }

    mtd.mtd_device.block_start = 0;
    mtd.mtd_device.block_end = (mtd.pflashTotalSize - mtd.destAdrss) / mtd.pflashSectorSize;
    mtd.mtd_device.block_size = mtd.pflashSectorSize;

    /* set ops */
    mtd.mtd_device.ops = &mcx_mtd_chipflashops;
    rt_mtd_nor_register_device("mflash", &(mtd.mtd_device));

    return result;
}
INIT_DEVICE_EXPORT(rt_onchip_flash_init);
