/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include <dfs_fs.h>
#include <lpc214x.h>

#include "sd.h"

static struct rt_device sd;
static struct dfs_partition part;

static rt_err_t rt_sdcard_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_sdcard_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rt_sdcard_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    /* append partition offset */
    pos += part.offset * 512;

    return 0;
}

static rt_ssize_t rt_sdcard_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    /* append partition offset */
    pos += part.offset * 512;

    return 0;
}

static rt_err_t rt_sdcard_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

void rt_hw_sdcard_init()
{
    rt_size_t length;
    rt_uint8_t* sector;

    /* sdcard hardware init */

    sd.type     = RT_Device_Class_Block;
    sd.init     = rt_sdcard_init;
    sd.open     = rt_sdcard_open;
    sd.close    = rt_sdcard_close;
    sd.read     = rt_sdcard_read;
    sd.write    = rt_sdcard_write;
    sd.control  = rt_sdcard_control;
    sd.user_data  = RT_NULL;

    /* get the first sector to read partition table */
    sector = (rt_uint8_t*) rt_malloc (512);
    if (sector == RT_NULL)
    {
        rt_kprintf("allocate partition sector buffer failed\n");
        return;
    }

    length = rt_sdcard_read((rt_device_t)&sd, 0, sector, 512);
    if (length == 512)
    {
        rt_err_t status;

        /* get the first partition */
        status = dfs_filesystem_get_partition(&part, sector, 0);
        if (status != RT_EOK)
        {
            /* there is no partition table */
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

    rt_device_register(&sd,
        "sd", RT_DEVICE_FLAG_RDWR);
}
