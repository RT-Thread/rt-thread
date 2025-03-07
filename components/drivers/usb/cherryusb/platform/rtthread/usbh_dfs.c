/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_msc.h"

#include "rtthread.h"
#include <dfs_fs.h>

#define DEV_FORMAT "/dev/sd%c"

#ifndef CONFIG_USB_DFS_MOUNT_POINT
#define CONFIG_USB_DFS_MOUNT_POINT "/"
#endif

#if defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7) || \
    defined(SOC_HPM5000) || defined(SOC_HPM6000) || defined(SOC_HPM6E00) || defined(BSP_USING_BL61X)
#ifndef RT_USING_CACHE
#error usbh msc must enable RT_USING_CACHE in this chip
#endif
#if RT_ALIGN_SIZE != 32 && RT_ALIGN_SIZE != 64
#error usbh msc must set cache line to 32 or 64
#endif
#endif

#if defined(BSP_USING_BL61X)
#include "bflb_l1c.h"

void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_FLUSH) {
        bflb_l1c_dcache_clean_range(addr, size);
    } else {
        bflb_l1c_dcache_invalidate_range(addr, size);
    }
}
#endif

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t msc_sector[512];

static rt_err_t rt_udisk_init(rt_device_t dev)
{
    struct usbh_msc *msc_class = (struct usbh_msc *)dev->user_data;

    if (usbh_msc_scsi_init(msc_class) < 0) {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static ssize_t rt_udisk_read(rt_device_t dev, rt_off_t pos, void *buffer,
                             rt_size_t size)
{
    struct usbh_msc *msc_class = (struct usbh_msc *)dev->user_data;
    int ret;

#ifdef RT_USING_CACHE
    rt_uint32_t *align_buf;

    if ((uint32_t)buffer & (RT_ALIGN_SIZE - 1)) {
        align_buf = rt_malloc_align(size * msc_class->blocksize, RT_ALIGN_SIZE);
        if (!align_buf) {
            rt_kprintf("msc get align buf failed\n");
            return 0;
        }
    } else {
        align_buf = (rt_uint32_t *)buffer;
    }

    ret = usbh_msc_scsi_read10(msc_class, pos, (uint8_t *)align_buf, size);
    if (ret < 0) {
        rt_kprintf("usb mass_storage read failed\n");
        return 0;
    }
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, align_buf, size * msc_class->blocksize);
    if ((uint32_t)buffer & (RT_ALIGN_SIZE - 1)) {
        rt_memcpy(buffer, align_buf, size * msc_class->blocksize);
        rt_free_align(align_buf);
    }
#else
    ret = usbh_msc_scsi_read10(msc_class, pos, buffer, size);
    if (ret < 0) {
        rt_kprintf("usb mass_storage read failed\n");
        return 0;
    }
#endif
    return size;
}

static ssize_t rt_udisk_write(rt_device_t dev, rt_off_t pos, const void *buffer,
                              rt_size_t size)
{
    struct usbh_msc *msc_class = (struct usbh_msc *)dev->user_data;
    int ret;

#ifdef RT_USING_CACHE
    rt_uint32_t *align_buf;

    if ((uint32_t)buffer & (RT_ALIGN_SIZE - 1)) {
        align_buf = rt_malloc_align(size * msc_class->blocksize, RT_ALIGN_SIZE);
        if (!align_buf) {
            rt_kprintf("msc get align buf failed\n");
            return 0;
        }

        rt_memcpy(align_buf, buffer, size * msc_class->blocksize);
    } else {
        align_buf = (rt_uint32_t *)buffer;
    }

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, align_buf, size * msc_class->blocksize);
    ret = usbh_msc_scsi_write10(msc_class, pos, (uint8_t *)align_buf, size);
    if (ret < 0) {
        rt_kprintf("usb mass_storage write failed\n");
        return 0;
    }
    if ((uint32_t)buffer & (RT_ALIGN_SIZE - 1)) {
        rt_free_align(align_buf);
    }
#else
    ret = usbh_msc_scsi_write10(msc_class, pos, buffer, size);
    if (ret < 0) {
        rt_kprintf("usb mass_storage write failed\n");
        return 0;
    }
#endif

    return size;
}

static rt_err_t rt_udisk_control(rt_device_t dev, int cmd, void *args)
{
    /* check parameter */
    RT_ASSERT(dev != RT_NULL);
    struct usbh_msc *msc_class = (struct usbh_msc *)dev->user_data;

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME) {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL)
            return -RT_ERROR;

        geometry->bytes_per_sector = msc_class->blocksize;
        geometry->block_size = msc_class->blocksize;
        geometry->sector_count = msc_class->blocknum;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops udisk_device_ops = {
    rt_udisk_init,
    RT_NULL,
    RT_NULL,
    rt_udisk_read,
    rt_udisk_write,
    rt_udisk_control
};
#endif

static void usbh_msc_thread(CONFIG_USB_OSAL_THREAD_SET_ARGV)
{
    struct usbh_msc *msc_class = (struct usbh_msc *)CONFIG_USB_OSAL_THREAD_GET_ARGV;
    char name[CONFIG_USBHOST_DEV_NAMELEN];
    char mount_point[CONFIG_USBHOST_DEV_NAMELEN];
    int ret;

    snprintf(name, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT, msc_class->sdchar);
    snprintf(mount_point, CONFIG_USBHOST_DEV_NAMELEN, CONFIG_USB_DFS_MOUNT_POINT, msc_class->sdchar);

    ret = dfs_mount(name, mount_point, "elm", 0, 0);
    if (ret == 0) {
        rt_kprintf("udisk: %s mount successfully\n", name);
    } else {
        rt_kprintf("udisk: %s mount failed, ret = %d\n", name, ret);
    }

    usb_osal_thread_delete(NULL);
}

void usbh_msc_run(struct usbh_msc *msc_class)
{
    struct rt_device *dev;
    char name[CONFIG_USBHOST_DEV_NAMELEN];

    dev = rt_malloc(sizeof(struct rt_device));
    memset(dev, 0, sizeof(struct rt_device));

    snprintf(name, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT, msc_class->sdchar);

    dev->type = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
    dev->ops = &udisk_device_ops;
#else
    dev->init = rt_udisk_init;
    dev->read = rt_udisk_read;
    dev->write = rt_udisk_write;
    dev->control = rt_udisk_control;
#endif
    dev->user_data = msc_class;

    rt_device_register(dev, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

    usb_osal_thread_create("usbh_msc", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_msc_thread, msc_class);
}

void usbh_msc_stop(struct usbh_msc *msc_class)
{
    struct rt_device *dev;

    char name[CONFIG_USBHOST_DEV_NAMELEN];
    char mount_point[CONFIG_USBHOST_DEV_NAMELEN];

    snprintf(name, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT, msc_class->sdchar);
    snprintf(mount_point, CONFIG_USBHOST_DEV_NAMELEN, CONFIG_USB_DFS_MOUNT_POINT, msc_class->sdchar);

    dfs_unmount(mount_point);
    dev = rt_device_find(name);
    if (dev) {
        rt_device_unregister(dev);
        rt_free(dev);
    }
}
