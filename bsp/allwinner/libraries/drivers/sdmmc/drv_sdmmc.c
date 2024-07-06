/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-29     JasonHu      first version
 */

#define DBG_TAG "drv-sdmmc"
#include <rtdbg.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <rtthread.h>

#ifdef BSP_USING_SDMMC

#include <typedef.h>
#include <kapi.h>
#include <init.h>
#include <blkpart.h>
#include <sdmmc/hal_sdhost.h>
#include <sdmmc/card.h>
#include <sdmmc/sys/sys_debug.h>
#include <sdmmc/sdmmc.h>
#include <sdmmc/sd_test.h>
#include <drv_sdmmc.h>

#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h> /* rename() */
#include <sys/stat.h>
#include <sys/statfs.h> /* statfs() */
#include "partition.h"

#ifdef CONFIG_SUPPORT_SDMMC_CACHE
#include "sdmmc_cache.h"
#endif

// #define DETECT_BY_GPIO

#ifndef CONFIG_SDC_DMA_BUF_SIZE
#define SDC_ALIGN_DMA_BUF_SIZE (64 * 1024)
#else
#define SDC_ALIGN_DMA_BUF_SIZE (CONFIG_SDC_DMA_BUF_SIZE * 1024)
#endif

#define SDXC_MAX_TRANS_LEN SDC_ALIGN_DMA_BUF_SIZE

#ifndef ALIGN_DOWN
#define ALIGN_DOWN(size, align) ((size) & ~((align)-1))
#endif

#ifndef MIN
#define MIN(a, b) (a > b ? b : a)
#endif

static int _register_blk_part_device(rt_device_t dev, const char *dev_name)
{
    uint8_t *mbr_buf = NULL;
    int ret = 0;
    int i = 0;
    struct rt_partition *part_table;
    int part_count = 0;
    int alloc_part_count = 2;

    /* NOTICE: get block geometry fisrt time here, then you can read/write sdmmc. */
    struct dev_sdmmc *dev_sdmmc = (struct dev_sdmmc *)dev->user_data;
    if (rt_dev_control(dev, RT_DEVICE_CTRL_BLK_GETGEOME, &dev_sdmmc->geometry) != RT_EOK)
    {
        LOG_E("device get geometry failed!");
        return -RT_EIO;
    }

    rt_kprintf("sdmmc bytes_per_secotr:%x, sector count:%x\n", dev_sdmmc->geometry.bytes_per_sector, dev_sdmmc->geometry.sector_count);

    /*read the mbr*/
    mbr_buf = rt_malloc(dev_sdmmc->geometry.bytes_per_sector);
    if (!mbr_buf)
    {
        return -RT_ENOMEM;
    }
    rt_memset(mbr_buf, 0, dev_sdmmc->geometry.bytes_per_sector);

    part_table = rt_malloc(sizeof(struct rt_partition) * alloc_part_count);
    if (!part_table)
    {
        return -RT_ENOMEM;
    }

    if (rt_dev_read(dev, 0, mbr_buf, 1) != 1)
    {
        LOG_E("device read mbr 1-sector failure\n");
        ret = -RT_ERROR;
        goto err;
    }

    for (i = 0;; i++)
    {
        rt_err_t status;
        struct dfs_partition part;

        status = dfs_filesystem_get_partition(&part, mbr_buf, i);
        if (status != RT_EOK)
        {
            if (i == 0)
            {
                snprintf(part_table[0].name, 6, "sd%dp%d", dev_sdmmc->host_id, i);
                part_table[0].offset = 8 * 1024 * 1024;
                part_table[0].size = dev_sdmmc->geometry.bytes_per_sector * dev_sdmmc->geometry.sector_count - part_table[0].offset;
                part_table[0].flags = PARTITION_WRITEABLE;
                part_count = 1;

                rt_kprintf("not found partition of mbr, construct sd0 at offset 8M, size:%p\n", part_table[0].size);
            }
            break;
        }
        else
        {
            if (part_count >= alloc_part_count)
            {
                rt_kprintf("part_count1:%d\n", part_count);

                struct rt_partition *new_part_table;

                alloc_part_count *= 2;

                new_part_table = rt_realloc(part_table, alloc_part_count * sizeof(struct rt_partition));
                if (new_part_table != RT_NULL)
                {
                    part_table = new_part_table;
                }
                else
                {
                    break;
                }
            }
            rt_kprintf("found partition:sd%d of mbr at offset %p, size:%p\n", i, part.offset, part.size);
            snprintf(part_table[part_count].name, 6, "sd%dp%d", dev_sdmmc->host_id, i);
            part_table[part_count].offset = part.offset * dev_sdmmc->geometry.bytes_per_sector;
            // rt_kprintf("bytes_per_sector:%d\n", dev_sdmmc->geometry.bytes_per_sector);
            // rt_kprintf("part_table_offset:%d\n", part.offset * dev_sdmmc->geometry.bytes_per_sector);
            part_table[part_count].size = part.size * dev_sdmmc->geometry.bytes_per_sector;
            part_table[part_count].flags = PARTITION_WRITEABLE;
            part_count++;
        }
    }

err:
    if (part_count > 0)
    {
        ret = rt_partition_init(dev_name, part_table, part_count);
    }
    if (mbr_buf != NULL)
    {
        rt_free(mbr_buf);
    }

    if (ret != 0)
    {
        if (part_table != NULL)
        {
            rt_free(part_table);
        }
    }

    return ret;
}

rt_err_t sdmmc_init(rt_device_t dev)
{
    int ret = -1;

    struct dev_sdmmc *dev_priv = (struct dev_sdmmc *)dev->user_data;
    int host_id = dev_priv->host_id;

    dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
    int32_t internal_card = 0x00;

    SDC_InitTypeDef sdc_param = {0};
    sdc_param.debug_mask = (ROM_INF_MASK |
                            ROM_WRN_MASK | ROM_ERR_MASK | ROM_ANY_MASK);

    esCFG_GetKeyValue("sdcard_global", "internal_card", (int32_t *)&internal_card, 1);

    if (((internal_card >> host_id) & 0x01) == 1)
    {
        sdc_param.cd_mode = CARD_ALWAYS_PRESENT;
        LOG_D("cd_mode CARD_ALWAYS_PRESENT!");
    }
    else
    {
#ifndef DETECT_BY_GPIO
        sdc_param.cd_mode = CARD_ALWAYS_PRESENT;
#else
        sdc_param.cd_mode = CARD_DETECT_BY_GPIO_IRQ;
#endif
    }
    sdc_param.cd_cb = &card_detect;
    sdc_param.dma_use = 1;

    if (mmc_test_init(host_id, &sdc_param, 1))
    {
        dev->flag &= ~RT_DEVICE_FLAG_ACTIVATED;
        LOG_E("init sdmmc failed!");
        return ret;
    }
    LOG_D("host_id =%d!", host_id);

    /* wait timeout to sync with sdmmc init done */
    int mdelay = 500;
    while (!hal_sdc_init_timeout() && mdelay > 0)
    {
        rt_thread_mdelay(50);
        mdelay -= 50;
    }
    return 0;
}

rt_err_t sdmmc_deinit(rt_device_t dev)
{
    struct dev_sdmmc *dev_priv = (struct dev_sdmmc *)dev->user_data;
    int host_id = dev_priv->host_id;
    mmc_test_exit(host_id, host_id);
    return 0;
}

static rt_ssize_t sdmmc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    ssize_t ret, rsz, trsz, msz = 0;
    struct rt_device_blk_geometry *geometry;
    uint8_t *data = buffer;
    struct dev_sdmmc *dev_priv = (struct dev_sdmmc *)dev->user_data;
    struct mmc_card *card = mmc_card_open(dev_priv->host_id);

    if (card == NULL)
    {
        LOG_E("mmc open fail");
        return 0;
    }

    if (size == 0)
    {
        return 0;
    }

    // rt_kprintf("sd read, pos:%llu, blkcnt:%llu\n", pos, size);

    geometry = &dev_priv->geometry;

    if (pos >= geometry->sector_count)
    {
        LOG_E("read offset %lu over part sector %llu", pos, geometry->sector_count);
        return 0;
    }

    if (pos + size > geometry->sector_count)
    {
        LOG_E("over limit: offset %lu + size %lu over %llu",
              pos, size, geometry->sector_count);
        return 0;
    }

    trsz = 0;
    msz = SDXC_MAX_TRANS_LEN / geometry->bytes_per_sector;
    while (size > 0)
    {
        if (size < msz)
        {
            rsz = size;
        }
        else
        {
            rsz = msz;
        }

        ret = mmc_block_read(card, data, pos, rsz);
        if (ret)
        {
            LOG_E("read failed - %d", (int)ret);
            break;
        }

        trsz += rsz;
        size -= rsz;
        data += rsz * geometry->bytes_per_sector;
        pos += rsz;
    }

    mmc_card_close(dev_priv->host_id);

    return trsz;
}

static rt_err_t sdmmc_open(rt_device_t dev, rt_uint16_t oflag)
{
    return 0;
}

static rt_err_t sdmmc_close(rt_device_t dev)
{
    return 0;
}

static rt_ssize_t sdmmc_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    int err = -1;
    ssize_t ret, wsz, twsz, msz = 0;
    struct rt_device_blk_geometry *geometry;
    uint8_t *data = (uint8_t *)buffer;

    struct dev_sdmmc *dev_priv = (struct dev_sdmmc *)dev->user_data;
    struct mmc_card *card = mmc_card_open(dev_priv->host_id);
    if (card == NULL)
    {
        LOG_E("mmc open fail");
        return -EIO;
    }

    if (size == 0)
    {
        return 0;
    }

    geometry = &dev_priv->geometry;

    if (pos >= geometry->sector_count)
    {
        LOG_E("read offset %lu over part size %llu", pos, geometry->sector_count);
        return 0;
    }

    if (pos + size > geometry->sector_count)
    {
        LOG_E("over limit: offset %lu + size %lu over %llu",
              pos, size, geometry->sector_count);
        return 0;
    }

    twsz = 0;
    msz = SDXC_MAX_TRANS_LEN / geometry->bytes_per_sector;
    while (size > 0)
    {
        if (size < msz)
        {
            wsz = size;
        }
        else
        {
            wsz = msz;
        }

        ret = mmc_block_write(card, data, pos, wsz);
        if (ret)
        {
            LOG_E("read failed - %d", (int)ret);
            break;
        }

        twsz += wsz;
        size -= wsz;
        data += wsz * geometry->bytes_per_sector;
        pos += wsz;
    }

    mmc_card_close(dev_priv->host_id);

    return twsz;
}

static rt_err_t sdmmc_control(rt_device_t dev, int cmd, void *args)
{
    int ret = -RT_ERROR;
    struct rt_device_blk_geometry *geometry;
    int flag = 0;
    if (!dev)
    {
        return -EINVAL;
    }

    struct dev_sdmmc *dev_priv = (struct dev_sdmmc *)dev->user_data;
    struct mmc_card *card = mmc_card_open(dev_priv->host_id);
    if (!card)
    {
        return ret;
    }

    switch (cmd)
    {
    case BLOCK_DEVICE_CMD_ERASE_ALL:
        break;
    case BLOCK_DEVICE_CMD_ERASE_SECTOR:
        break;
    case BLOCK_DEVICE_CMD_GET_TOTAL_SIZE:
        *(uint64_t *)args = card->csd.capacity * 1024ull;
        ret = 0;
        break;
    case BLOCK_DEVICE_CMD_GET_PAGE_SIZE:
        *(uint32_t *)args = 512;
        ret = 0;
        break;
    case BLOCK_DEVICE_CMD_GET_BLOCK_SIZE:
        *(uint32_t *)args = 512;
        ret = 0;
        break;
    case RT_DEVICE_CTRL_BLK_GETGEOME:
        geometry = (struct rt_device_blk_geometry *)args;
        rt_memset(geometry, 0, sizeof(struct rt_device_blk_geometry));
        geometry->block_size = 512;
        geometry->bytes_per_sector = 512;
        geometry->sector_count = (card->csd.capacity * 1024ull) / geometry->bytes_per_sector;
        LOG_D("[sdmmc] getgeome: bytes_per_sector:%ld, block_size:%ld, sector_count:%ld",
              geometry->bytes_per_sector, geometry->block_size, geometry->sector_count);
        ret = RT_EOK;
        break;

    default:
        break;
    }

    mmc_card_close(dev_priv->host_id);
    return ret;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops _sdmmc_ops =
{
    .init = sdmmc_init,
    .open = sdmmc_open,
    .close = sdmmc_close,
    .read = sdmmc_read,
    .write = sdmmc_write,
    .control = sdmmc_control
};
#endif /* RT_USING_DEVICE_OPS */

static int init_sdmmc_device(rt_device_t device, void *usr_data, char *dev_name)
{
    int ret = -1;

    device = rt_device_create(RT_Device_Class_Block, 0);
    if (!device)
    {
        return ret;
    }

#ifndef RT_USING_DEVICE_OPS
    device->init = sdmmc_init;
    device->open = sdmmc_open;
    device->close = sdmmc_close;
    device->read = sdmmc_read;
    device->write = sdmmc_write;
    device->control = sdmmc_control;
#else
    device->ops = &_sdmmc_ops;
#endif /* RT_USING_DEVICE_OPS */
    device->user_data = usr_data;

    ret = rt_device_register(device, dev_name, RT_DEVICE_FLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_device_destroy(device);
        return ret;
    }

    // int sdmmc_blkpart_init(const char *name);
    // ret = sdmmc_blkpart_init(dev_name);
    if (sdmmc_init(device))
    {
        LOG_E("sdmmc_init failed!");
        return -1;
    }

    /* NOTICE: get block geometry fisrt time here, then you can read/write sdmmc. */
    struct dev_sdmmc *dev_sdmmc = (struct dev_sdmmc *)device->user_data;
    if (rt_dev_control(device, RT_DEVICE_CTRL_BLK_GETGEOME, &dev_sdmmc->geometry) != RT_EOK)
    {
        LOG_E("device get geometry failed!");
        ret = -ENOSYS;
    }

    _register_blk_part_device(device, dev_name);

    return ret;
}

static struct dev_sdmmc dev_sdmmc[SDMMC_CARD_NR];

int driver_sdmmc_init(void)
{
    int ret = -1;
    int i = 0;
    rt_device_t device[SDMMC_CARD_NR];
    int32_t used_card_no = 0x01;
    char name[12];

    ret = esCFG_GetKeyValue("sdcard_global", "used_card_no", (int32_t *)&used_card_no, 1);
    if (ret)
    {
        used_card_no = 0x00;
        LOG_E("get card no failed, card no: %d", used_card_no);
        return ret;
    }

    for (i = 0; i < SDMMC_CARD_NR; ++i)
    {
        rt_sprintf(name, "sdmmc%d", i);
        dev_sdmmc[i].host_id = i;
        ret = init_sdmmc_device(device[i], (void *)&dev_sdmmc[i], name);
    }
    return ret;
}

void sd_mmc1_init(void)
{
    rt_device_t device = NULL;
    device = rt_device_find("sdmmc1");
    sdmmc_init(device);

    _register_blk_part_device(device, "sdmmc1");
}

void sd_mmc1_deinit(void)
{
    rt_device_t device = NULL;
    device = rt_device_find("sdmmc1");
    sdmmc_deinit(device);
}

INIT_DEVICE_EXPORT(driver_sdmmc_init);

#endif
