/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-12     Yi Qiu      first version
 */

#include <rtthread.h>
#include <dfs_fs.h>
#include <drivers/usb_host.h>
#include "mass.h"

#ifdef RT_USBH_MSTORAGE

#define UDISK_MAX_COUNT        8
static rt_uint8_t _udisk_idset = 0;

static int udisk_get_id(void)
{
    int i;

    for(i=0; i< UDISK_MAX_COUNT; i++)
    {
        if((_udisk_idset & (1 << i)) != 0) continue;
        else break;
    }

    /* it should not happen */
    if(i == UDISK_MAX_COUNT) RT_ASSERT(0);

    _udisk_idset |= (1 << i);
    return i;
}

static void udisk_free_id(int id)
{
    RT_ASSERT(id < UDISK_MAX_COUNT)

    _udisk_idset &= ~(1 << id);
}

/**
 * This function will initialize the udisk device
 *
 * @param dev the pointer of device driver structure
 *
 * @return RT_EOK
 */
static rt_err_t rt_udisk_init(rt_device_t dev)
{
    return RT_EOK;
}

/**
 * This function will read some data from a device.
 *
 * @param dev the pointer of device driver structure
 * @param pos the position of reading
 * @param buffer the data buffer to save read data
 * @param size the size of buffer
 *
 * @return the actually read size on successful, otherwise negative returned.
 */
static rt_size_t rt_udisk_read(rt_device_t dev, rt_off_t pos, void* buffer,
    rt_size_t size)
{
    rt_err_t ret;
    struct uhintf* intf;
    struct ustor_data* data;
    int timeout = USB_TIMEOUT_LONG;

    /* check parameter */
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    if(size > 4096) timeout *= 2;

    data = (struct ustor_data*)dev->user_data;
    intf = data->intf;

    ret = rt_usbh_storage_read10(intf, (rt_uint8_t*)buffer, pos, size, timeout);

    if (ret != RT_EOK)
    {
        rt_kprintf("usb mass_storage read failed\n");
        return 0;
    }

    return size;
}

/**
 * This function will write some data to a device.
 *
 * @param dev the pointer of device driver structure
 * @param pos the position of written
 * @param buffer the data buffer to be written to device
 * @param size the size of buffer
 *
 * @return the actually written size on successful, otherwise negative returned.
 */
static rt_size_t rt_udisk_write (rt_device_t dev, rt_off_t pos, const void* buffer,
    rt_size_t size)
{
    rt_err_t ret;
    struct uhintf* intf;
    struct ustor_data* data;
    int timeout = USB_TIMEOUT_LONG;

    /* check parameter */
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    if(size * SECTOR_SIZE > 4096) timeout *= 2;

    data = (struct ustor_data*)dev->user_data;
    intf = data->intf;

    ret = rt_usbh_storage_write10(intf, (rt_uint8_t*)buffer, pos, size, timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("usb mass_storage write %d sector failed\n", size);
        return 0;
    }

    return size;
}

/**
 * This function will execute SCSI_INQUIRY_CMD command to get inquiry data.
 *
 * @param intf the interface instance.
 * @param buffer the data buffer to save inquiry data
 *
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_udisk_control(rt_device_t dev, int cmd, void *args)
{
    ustor_t stor;
    struct ustor_data* data;

    /* check parameter */
    RT_ASSERT(dev != RT_NULL);

    data = (struct ustor_data*)dev->user_data;
    stor = (ustor_t)data->intf->user_data;

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = SECTOR_SIZE;
        geometry->block_size = stor->capicity[1];
        geometry->sector_count = stor->capicity[0];
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops udisk_device_ops =
{
    rt_udisk_init,
    RT_NULL,
    RT_NULL,
    rt_udisk_read,
    rt_udisk_write,
    rt_udisk_control
};
#endif

/**
 * This function will run udisk driver when usb disk is detected.
 *
 * @param intf the usb interface instance.
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_udisk_run(struct uhintf* intf)
{
    int i = 0;
    rt_err_t ret;
    char dname[8];
    char sname[8];
    rt_uint8_t max_lun, *sector, sense[18], inquiry[36];
    struct dfs_partition part[MAX_PARTITION_COUNT];
    ustor_t stor;

    /* check parameter */
    RT_ASSERT(intf != RT_NULL);

    /* set interface */
//    ret = rt_usbh_set_interface(intf->device, intf->intf_desc->bInterfaceNumber);
//    if(ret != RT_EOK)
//        rt_usbh_clear_feature(intf->device, 0, USB_FEATURE_ENDPOINT_HALT);
    /* reset mass storage class device */
    ret = rt_usbh_storage_reset(intf);
    if(ret != RT_EOK) return ret;

    stor = (ustor_t)intf->user_data;

    /* get max logic unit number */
    ret = rt_usbh_storage_get_max_lun(intf, &max_lun);
    if(ret != RT_EOK)
        rt_usbh_clear_feature(intf->device, 0, USB_FEATURE_ENDPOINT_HALT);

    /* reset pipe in endpoint */
    if(stor->pipe_in->status == UPIPE_STATUS_STALL)
    {
        ret = rt_usbh_clear_feature(intf->device,
        stor->pipe_in->ep.bEndpointAddress, USB_FEATURE_ENDPOINT_HALT);
        if(ret != RT_EOK) return ret;
    }


    /* reset pipe out endpoint */
    if(stor->pipe_out->status == UPIPE_STATUS_STALL)
    {
        ret = rt_usbh_clear_feature(intf->device,
        stor->pipe_out->ep.bEndpointAddress, USB_FEATURE_ENDPOINT_HALT);
        if(ret != RT_EOK) return ret;
    }

    while((ret = rt_usbh_storage_inquiry(intf, inquiry)) != RT_EOK)
    {
        if(ret == -RT_EIO) return ret;

        rt_thread_delay(5);
        if(i++ < 10) continue;
        rt_kprintf("rt_usbh_storage_inquiry error\n");
        return -RT_ERROR;
    }

    i = 0;

    /* wait device ready */
    while((ret = rt_usbh_storage_test_unit_ready(intf)) != RT_EOK)
    {
        if(ret == -RT_EIO) return ret;

        ret = rt_usbh_storage_request_sense(intf, sense);
        if(ret == -RT_EIO) return ret;

        rt_thread_delay(10);
        if(i++ < 10) continue;

        rt_kprintf("rt_usbh_storage_test_unit_ready error\n");
        return -RT_ERROR;
    }

    i = 0;
    rt_memset(stor->capicity, 0, sizeof(stor->capicity));

    /* get storage capacity */
    while((ret = rt_usbh_storage_get_capacity(intf,
        (rt_uint8_t*)stor->capicity)) != RT_EOK)
    {
        if(ret == -RT_EIO) return ret;

        rt_thread_delay(50);
        if(i++ < 10) continue;

        stor->capicity[0] = 2880;
        stor->capicity[1] = 0x200;

        rt_kprintf("rt_usbh_storage_get_capacity error\n");
        break;
    }

    stor->capicity[0] = uswap_32(stor->capicity[0]);
    stor->capicity[1] = uswap_32(stor->capicity[1]);
    stor->capicity[0] += 1;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("capicity %d, block size %d\n",
        stor->capicity[0], stor->capicity[1]));

    /* get the first sector to read partition table */
    sector = (rt_uint8_t*) rt_malloc (SECTOR_SIZE);
    if (sector == RT_NULL)
    {
        rt_kprintf("allocate partition sector buffer failed\n");
        return -RT_ERROR;
    }

    rt_memset(sector, 0, SECTOR_SIZE);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("read partition table\n"));

    /* get the partition table */
    ret = rt_usbh_storage_read10(intf, sector, 0, 1, USB_TIMEOUT_LONG);
    if(ret != RT_EOK)
    {
        rt_kprintf("read parition table error\n");

        rt_free(sector);
        return -RT_ERROR;
    }

    RT_DEBUG_LOG(RT_DEBUG_USB, ("finished reading partition\n"));

    for(i=0; i<MAX_PARTITION_COUNT; i++)
    {
        /* get the first partition */
        ret = dfs_filesystem_get_partition(&part[i], sector, i);
        if (ret == RT_EOK)
        {
            struct ustor_data* data = rt_malloc(sizeof(struct ustor_data));
            rt_memset(data, 0, sizeof(struct ustor_data));
            data->intf = intf;
            data->udisk_id = udisk_get_id();
            rt_snprintf(dname, 6, "ud%d-%d", data->udisk_id, i);
            rt_snprintf(sname, 8, "sem_ud%d",  i);
            data->part.lock = rt_sem_create(sname, 1, RT_IPC_FLAG_FIFO);

            /* register sdcard device */
            stor->dev[i].type    = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
            stor->dev[i].ops     = &udisk_device_ops;
#else
            stor->dev[i].init    = rt_udisk_init;
            stor->dev[i].read    = rt_udisk_read;
            stor->dev[i].write   = rt_udisk_write;
            stor->dev[i].control = rt_udisk_control;
#endif
            stor->dev[i].user_data = (void*)data;

            rt_device_register(&stor->dev[i], dname, RT_DEVICE_FLAG_RDWR |
                RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

            stor->dev_cnt++;
            if (dfs_mount(stor->dev[i].parent.name, UDISK_MOUNTPOINT, "elm",
                0, 0) == 0)
            {
                RT_DEBUG_LOG(RT_DEBUG_USB, ("udisk part %d mount successfully\n", i));
            }
            else
            {
                RT_DEBUG_LOG(RT_DEBUG_USB, ("udisk part %d mount failed\n", i));
            }
        }
        else
        {
            if(i == 0)
            {
                struct ustor_data* data = rt_malloc(sizeof(struct ustor_data));
                rt_memset(data, 0, sizeof(struct ustor_data));
                data->udisk_id = udisk_get_id();

                /* there is no partition table */
                data->part.offset = 0;
                data->part.size   = 0;
                data->intf = intf;
                data->part.lock = rt_sem_create("sem_ud", 1, RT_IPC_FLAG_FIFO);

                rt_snprintf(dname, 7, "udisk%d", data->udisk_id);

                /* register sdcard device */
                stor->dev[0].type    = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
                stor->dev[i].ops     = &udisk_device_ops;
#else
                stor->dev[0].init    = rt_udisk_init;
                stor->dev[0].read    = rt_udisk_read;
                stor->dev[0].write   = rt_udisk_write;
                stor->dev[0].control = rt_udisk_control;
#endif
                stor->dev[0].user_data = (void*)data;

                rt_device_register(&stor->dev[0], dname,
                    RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE
                    | RT_DEVICE_FLAG_STANDALONE);

                stor->dev_cnt++;
                if (dfs_mount(stor->dev[0].parent.name, UDISK_MOUNTPOINT,
                    "elm", 0, 0) == 0)
                {
                    rt_kprintf("Mount FAT on Udisk successful.\n");
                }
                else
                {
                    rt_kprintf("Mount FAT on Udisk failed.\n");
                }
            }

            break;
        }
    }

    rt_free(sector);

    return RT_EOK;
}

/**
 * This function will be invoked when usb disk plug out is detected and it would clean
 * and release all udisk related resources.
 *
 * @param intf the usb interface instance.
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_udisk_stop(struct uhintf* intf)
{
    int i;
    ustor_t stor;
    struct ustor_data* data;

    /* check parameter */
    RT_ASSERT(intf != RT_NULL);
    RT_ASSERT(intf->device != RT_NULL);

    stor = (ustor_t)intf->user_data;
    RT_ASSERT(stor != RT_NULL);

    for(i=0; i<stor->dev_cnt; i++)
    {
        rt_device_t dev = &stor->dev[i];
        data = (struct ustor_data*)dev->user_data;

        /* unmount filesystem */
        dfs_unmount(UDISK_MOUNTPOINT);

        /* delete semaphore */
        rt_sem_delete(data->part.lock);
        udisk_free_id(data->udisk_id);
        rt_free(data);

        /* unregister device */
        rt_device_unregister(&stor->dev[i]);
    }

    return RT_EOK;
}

#endif

