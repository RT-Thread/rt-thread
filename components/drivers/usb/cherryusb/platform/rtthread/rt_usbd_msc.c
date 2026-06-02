/*
 * Copyright (c) 2026, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_msc.h"

#include <rtthread.h>
#include <rtdevice.h>

#ifndef CONFIG_USBDEV_MSC_THREAD
#error "Please enable CONFIG_USBDEV_MSC_THREAD, move msc read & write from isr to thread"
#endif

#ifndef CONFIG_USBDEV_MSC_BLOCK_DEV_NAME
#define CONFIG_USBDEV_MSC_BLOCK_DEV_NAME "sd0"
#endif

static rt_device_t blk_dev = RT_NULL;
static struct rt_device_blk_geometry geometry = { 0 };
static struct usbd_interface msc_intf;

void usbd_msc_get_cap(uint8_t busid, uint8_t lun, uint32_t *block_num, uint32_t *block_size)
{
    rt_device_control(blk_dev, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry);

    *block_num = geometry.sector_count;
    *block_size = geometry.bytes_per_sector;
}

int usbd_msc_sector_read(uint8_t busid, uint8_t lun, uint32_t sector, uint8_t *buffer, uint32_t length)
{
    rt_device_read(blk_dev, sector, buffer, length / geometry.bytes_per_sector);
    return 0;
}

int usbd_msc_sector_write(uint8_t busid, uint8_t lun, uint32_t sector, uint8_t *buffer, uint32_t length)
{
    rt_device_write(blk_dev, sector, buffer, length / geometry.bytes_per_sector);
    return 0;
}

void usbd_msc_blkdev_init(uint8_t busid, uint8_t in_ep, uint8_t out_ep)
{
    rt_err_t res;

    blk_dev = rt_device_find(CONFIG_USBDEV_MSC_BLOCK_DEV_NAME);
    RT_ASSERT(blk_dev);

    res = rt_device_open(blk_dev, RT_DEVICE_OFLAG_RDWR);
    RT_ASSERT(res == RT_EOK);

    usbd_add_interface(busid, usbd_msc_init_intf(busid, &msc_intf, out_ep, in_ep));
}