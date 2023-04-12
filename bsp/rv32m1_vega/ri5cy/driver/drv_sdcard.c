/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtdevice.h>
#include <rtthread.h>
#include <dfs_fs.h>

#include "drv_sdcard.h"
#include "fsl_card.h"

static sd_card_t g_sd;
static sd_card_t *card = &g_sd;

static struct rt_device sdcard_device;
static struct dfs_partition part;

static rt_err_t vega_sdcard_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t vega_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t vega_sdcard_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t vega_sdcard_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    status_t status;

    status = SD_ReadBlocks(card, buffer, part.offset + pos, size);

    if (status == kStatus_Success) return size;

    rt_kprintf("read failed: %d, pos 0x%08x, size %d\n", status, pos, size);
    return 0;
}

static rt_ssize_t vega_sdcard_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    status_t status;

    status = SD_WriteBlocks(card, buffer, part.offset + pos, size);

    if (status == kStatus_Success) return size;

    rt_kprintf("write failed: %d, pos 0x%08x, size %d\n", status, pos, size);
    return 0;
}

static rt_err_t vega_sdcard_control(rt_device_t dev, int cmd, void *args)
{
    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;

        if (geometry == RT_NULL) return -RT_ERROR;
        if (dev->user_data == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = card->blockSize;
        geometry->block_size       = card->blockSize;
        geometry->sector_count     = card->blockCount;
    }

    return RT_EOK;
}

int rt_hw_sdcard_init(void)
{
    /* set SDHC0 clock source */
    CLOCK_SetIpSrc(kCLOCK_Sdhc0, kCLOCK_IpSrcLpFllAsync);

    /* Save host information. */
    card->host.base = USDHC0;
    card->host.sourceClock_Hz = CLOCK_GetIpFreq(kCLOCK_Sdhc0);

    /* Init card. */
    if (SD_Init(card))
    {
        rt_kprintf("SD card init failed.\r\n");
        return -1;
    }
    else
    {
        bool status;
        rt_uint8_t *sector;

        /* get the first sector to read partition table */
        sector = (rt_uint8_t *) rt_malloc(card->blockSize);
        if (sector == RT_NULL)
        {
            rt_kprintf("allocate partition sector buffer failed\n");
            return -1;
        }

        status = SD_ReadBlocks(card, sector, 0, 1);
        if (status == true)
        {
            /* get the first partition */
            if (dfs_filesystem_get_partition(&part, sector, 0) != 0)
            {
                /* there is no partition */
                part.offset = 0;
                part.size   = 0;
            }
        }
        else
        {
            /* there is no partition table */
            part.offset = 0;
            part.size   = 0;
        }

        /* release sector buffer */
        rt_free(sector);

        /* register sdcard device */
        sdcard_device.type    = RT_Device_Class_Block;
        sdcard_device.init    = vega_sdcard_init;
        sdcard_device.open    = vega_sdcard_open;
        sdcard_device.close   = vega_sdcard_close;
        sdcard_device.read    = vega_sdcard_read;
        sdcard_device.write   = vega_sdcard_write;
        sdcard_device.control = vega_sdcard_control;

        /* no private */
        sdcard_device.user_data = (void*)card;

        rt_device_register(&sdcard_device, "sd0",
                           RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_sdcard_init);
