/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-26     armink       the first version
 */

#include <fal.h>
#include <rthw.h>
#include <rtthread.h>
#include <dfs_fs.h>

#ifdef BSP_USING_SDMMC
#include "drv_sdmmc.h"

rt_device_t sd_dev;
#define SECTOR_SIZE 512
static int init(void);
static int read(long offset, rt_uint8_t *buf, rt_size_t size);
static int write(long offset, const rt_uint8_t *buf, rt_size_t size);
static int erase(long offset, rt_size_t size);

struct fal_flash_dev sd_card = {
    "sdcard0",  /* name string match yml file */
    0,
    128 * 1024 * 1024,
    512,
    {init, read, write, erase}
};

static int read(long offset, rt_uint8_t *buf, rt_size_t size)
{
    rt_size_t sector_pos;
    rt_size_t sector_offset;
    rt_size_t remain_size = size;
    rt_size_t req_size;
    rt_align(4) rt_uint8_t buffer[SECTOR_SIZE];

    while (remain_size)
    {
        sector_offset = offset & (SECTOR_SIZE - 1);  //块内偏移
        sector_pos = offset / SECTOR_SIZE;          //块位置
        rt_device_read(sd_dev, sector_pos, buffer, SECTOR_SIZE / 512);  //读取一个块
        req_size = (SECTOR_SIZE - sector_offset) > remain_size ? remain_size : (SECTOR_SIZE - sector_offset);
        memcpy(buf, buffer + sector_offset, req_size);
        buf += req_size;
        offset += req_size;
        remain_size -= req_size;
    }

    return size;
}

static int write(long offset, const rt_uint8_t *buf, rt_size_t size)
{
    rt_size_t sector_pos;
    rt_size_t sector_offset;
    rt_size_t remain_size = size;
    rt_size_t req_size;
    rt_align(4) rt_uint8_t buffer[SECTOR_SIZE];

    while (remain_size)
    {
        sector_offset = offset & (SECTOR_SIZE - 1);  //块内偏移
        sector_pos = offset / SECTOR_SIZE;          //块位置

        rt_device_read(sd_dev, sector_pos, buffer, SECTOR_SIZE / 512);  //读取一个块
        req_size = (SECTOR_SIZE - sector_offset) > remain_size ? remain_size : (SECTOR_SIZE - sector_offset);
        memcpy(buffer + sector_offset, buf, req_size);
        rt_device_write(sd_dev, sector_pos, buffer, SECTOR_SIZE / 512); //写回sd卡
        buf += req_size;
        offset += req_size;
        remain_size -= req_size;
    }

    return size;
}

static int erase(long offset, rt_size_t size)
{
    return size;
}

static int init(void)
{
    sd_dev = rt_device_find("sdmmc0");
    if (RT_NULL == sd_dev)
    {
        return -1;
    }
    rt_device_open(sd_dev, RT_DEVICE_OFLAG_RDWR);
    struct dev_sdmmc *dev_sdmmc = (struct dev_sdmmc *)sd_dev->user_data;
    sd_card.len = (rt_size_t)dev_sdmmc->geometry.bytes_per_sector * dev_sdmmc->geometry.sector_count;
    sd_card.blk_size = dev_sdmmc->geometry.bytes_per_sector;

    return 0;
}
#endif
