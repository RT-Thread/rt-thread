/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <rtthread.h>
#include <dfs.h>

#define DBG_TAG    "sd.sim"
#define DBG_LVL    DBG_WARNING
#include <rtdbg.h>

#define SDCARD_SIM  "sd.bin"
#define SDCARD_SIZE (16*1024*1024)  //16M

struct sdcard_device
{
    struct rt_device parent;
    FILE *file;
};
static struct sdcard_device _sdcard;

#define SDCARD_DEVICE(device)       (( struct sdcard_device*)(device))

static rt_mutex_t lock;

/* RT-Thread device interface */

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

/* position: block page address, not bytes address
 * buffer:
 * size  : how many blocks
 */
static rt_ssize_t rt_sdcard_read(rt_device_t device, rt_off_t position, void *buffer, rt_size_t size)
{
    struct sdcard_device *sd;
    int result = 0;

    LOG_I("sd read: pos %d, size %d", position, size);

    rt_mutex_take(lock, RT_WAITING_FOREVER);
    sd = SDCARD_DEVICE(device);
    fseek(sd->file, position * SECTOR_SIZE, SEEK_SET);

    result = fread(buffer, size * SECTOR_SIZE, 1, sd->file);
    if (result < 0)
        goto _err;

    rt_mutex_release(lock);
    return size;

_err:
    LOG_E("sd read errors!");
    rt_mutex_release(lock);
    return 0;
}

/* position: block page address, not bytes address
 * buffer:
 * size  : how many blocks
 */
static rt_ssize_t rt_sdcard_write(rt_device_t device, rt_off_t position, const void *buffer, rt_size_t size)
{
    struct sdcard_device *sd;
    int result = 0;

    LOG_I("sst write: pos %d, size %d", position, size);

    rt_mutex_take(lock, RT_WAITING_FOREVER);
    sd = SDCARD_DEVICE(device);
    fseek(sd->file, position * SECTOR_SIZE, SEEK_SET);

    result = fwrite(buffer, size * SECTOR_SIZE, 1, sd->file);
    if (result < 0)
        goto _err;

    rt_mutex_release(lock);
    return size;

_err:
    LOG_E("sd write errors!");
    rt_mutex_release(lock);
    return 0;
}

static rt_err_t rt_sdcard_control(rt_device_t dev, int cmd, void *args)
{
    struct sdcard_device *sd;
    unsigned int size;

    RT_ASSERT(dev != RT_NULL);

    sd = SDCARD_DEVICE(dev);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = SECTOR_SIZE;
        geometry->block_size = SECTOR_SIZE;

        fseek(sd->file, 0, SEEK_END);
        size = ftell(sd->file);

        geometry->sector_count = size / SECTOR_SIZE;
    }
    return RT_EOK;
}

rt_err_t rt_hw_sdcard_init(const char *spi_device_name)
{
    int size;
    struct sdcard_device *sd;
    struct rt_device *device;

    sd = &_sdcard;
    device = &(sd->parent);

    lock = rt_mutex_create("lock", RT_IPC_FLAG_PRIO);
    if (lock == RT_NULL)
    {
        LOG_E("Create mutex in rt_hw_sdcard_init failed!");
        return -RT_ERROR;
    }

    /* open sd card file, if not exist, then create it  */
    sd->file = fopen(SDCARD_SIM, "rb+");
    if (sd->file == NULL)
    {
        /* create a file to simulate sd card */
        sd->file = fopen(SDCARD_SIM, "wb+");

        fseek(sd->file, 0, SEEK_END);
        size = ftell(sd->file);

        fseek(sd->file, 0, SEEK_SET);
        if (size < SDCARD_SIZE)
        {
            int i;
            unsigned char *ptr;

            ptr = (unsigned char *) malloc(1024 * 1024);
            if (ptr == NULL)
            {
                LOG_E("malloc error, no memory!");
                return RT_ERROR;
            }
            memset(ptr, 0x0, 1024 * 1024);

            fseek(sd->file, 0, SEEK_SET);

            for (i = 0; i < (SDCARD_SIZE / (1024 * 1024)); i++)
                fwrite(ptr, 1024 * 1024, 1, sd->file);

            free(ptr);
        }
    }
    fseek(sd->file, 0, SEEK_SET);

    device->type  = RT_Device_Class_Block;
    device->init = rt_sdcard_init;
    device->open = rt_sdcard_open;
    device->close = rt_sdcard_close;
    device->read = rt_sdcard_read;
    device->write = rt_sdcard_write;
    device->control = rt_sdcard_control;
    device->user_data = NULL;

    rt_device_register(device, "sd0",
                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

    return RT_EOK;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
int sd_erase(void)
{
    rt_uint32_t index;
    char * buffer;
    struct rt_device *device;
    device = &_sdcard.parent;
    if ((buffer = rt_malloc(SECTOR_SIZE)) == RT_NULL)
    {
        rt_kprintf("out of memory\n");
        return -1;
    }

    memset(buffer, 0, SECTOR_SIZE);
    /* just erase the MBR! */
    for (index = 0; index < 2; index ++)
    {
        rt_sdcard_write(device, index, buffer, SECTOR_SIZE);
    }
    rt_free(buffer);
    return 0;
}
FINSH_FUNCTION_EXPORT(sd_erase, erase all block in SPI flash);
#endif
