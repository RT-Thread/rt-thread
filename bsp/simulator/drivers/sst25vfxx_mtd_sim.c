/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-21     prife        the first version
 */

#include <rtdevice.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sst25vfxx_mtd.h"

#ifdef RT_USING_MTD_NOR
#define NOR_SIM "nor.bin"
/* JEDEC Manufacturer’s ID */
#define MF_ID           (0xBF)
/* JEDEC Device ID : Memory Type */
#define MT_ID           (0x25)
/* JEDEC Device ID: Memory Capacity */
#define MC_ID_SST25VF016               (0x41)
#define MC_ID_SST25VF032               (0x4A)
#define MC_ID_SST25VF064               (0x4B)

#define BLOCK_SIZE   (64*1024)


#define SST25_MTD(device)       ((struct sst25_mtd*)(device))
struct sst25_mtd
{
    struct rt_mtd_nor_device parent;
    FILE *file;
};
static struct sst25_mtd _sst25_mtd;

static struct rt_mutex flash_lock;

/* RT-Thread MTD device interface */
static rt_uint32_t sst25vfxx_read_id(struct rt_mtd_nor_device *device)
{
    rt_uint8_t id_recv[3] = {MF_ID, MT_ID, MC_ID_SST25VF016};

    return (id_recv[0] << 16) | (id_recv[1] << 8) | id_recv[2];
}

static int sst25vfxx_read(struct rt_mtd_nor_device *device, rt_off_t position, rt_uint8_t *data, rt_size_t size)
{
    struct sst25_mtd *sst25;
    int result;

    sst25 = SST25_MTD(device);
    RT_ASSERT(sst25 != RT_NULL);

    result = rt_mutex_take(&flash_lock, RT_WAITING_FOREVER);
    if (result == -RT_ETIMEOUT)
    {
        rt_kprintf("Take mutex time out.\n");
        return result;
    }
    else if (result == -RT_ERROR)
    {
        rt_kprintf("Take mutex error.\n");
        return result;
    }

    fseek(sst25->file, position, SEEK_SET);
    result = fread(data, size, 1, sst25->file);
    if (result < 0)
        rt_kprintf("sst read error.\n");

    rt_mutex_release(&flash_lock);
    return size;
}

static int sst25vfxx_write(struct rt_mtd_nor_device *device, rt_off_t position,
                           const rt_uint8_t *data, rt_size_t size)
{
    struct sst25_mtd *sst25;
    int result;

    sst25 = SST25_MTD(device);
    RT_ASSERT(sst25 != RT_NULL);

    result = rt_mutex_take(&flash_lock, RT_WAITING_FOREVER);
    if (result == -RT_ETIMEOUT)
    {
        rt_kprintf("Take mutex time out.\n");
        return result;
    }
    else if (result == -RT_ERROR)
    {
        rt_kprintf("Take mutex error.\n");
        return result;
    }

    fseek(sst25->file, position, SEEK_SET);
    result = fwrite(data, size, 1, sst25->file);
    if (result < 0)
        rt_kprintf("sst write error.\n");

    rt_mutex_release(&flash_lock);
    return size;
}

static char block_buffer[BLOCK_SIZE];
static rt_err_t sst25vfxx_erase_block(struct rt_mtd_nor_device *device, rt_off_t offset, rt_uint32_t length)
{
    struct sst25_mtd *sst25;
    int result;

    sst25 = SST25_MTD(device);

    RT_ASSERT(sst25 != RT_NULL);

    result = rt_mutex_take(&flash_lock, RT_WAITING_FOREVER);
    if (result == -RT_ETIMEOUT)
    {
        rt_kprintf("Take mutex time out.\n");
        return -RT_ETIMEOUT;
    }
    else if (result == -RT_ERROR)
    {
        rt_kprintf("Take mutex error.\n");
        return -RT_ERROR;
    }

    memset(block_buffer, 0xFF, BLOCK_SIZE);
    fseek(sst25->file, offset, SEEK_SET);

    result = fwrite(block_buffer, BLOCK_SIZE, 1, sst25->file);
    if (result < 0)
        rt_kprintf("sst write error.\n");

    rt_mutex_release(&flash_lock);
    return RT_EOK;
}

const static struct rt_mtd_nor_driver_ops sst25vfxx_mtd_ops =
{
    sst25vfxx_read_id,
    sst25vfxx_read,
    sst25vfxx_write,
    sst25vfxx_erase_block,
};
static rt_err_t sst25vfxx_hw_init(struct sst25_mtd *mtd)
{
    mtd = mtd;
    return RT_EOK;
}

/**
 * SST25vfxx API
 */
rt_err_t sst25vfxx_mtd_init(const char *nor_name,
                            rt_uint32_t block_start,
                            rt_uint32_t block_end)
{
    rt_uint32_t id, total_block;
    struct sst25_mtd *sst25;
    struct rt_mtd_nor_device *mtd;


    sst25 = &_sst25_mtd;
    mtd = &(sst25->parent);

    /* set page size and block size */
    mtd->block_size = 64 * 1024; /* 64kByte */
    mtd->ops = &sst25vfxx_mtd_ops;

    /* initialize mutex */
    if (rt_mutex_init(&flash_lock, nor_name, RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        rt_kprintf("init sd lock mutex failed\n");
    }

    /* initialize flash */
    id = sst25vfxx_read_id(mtd);
    switch (id & 0xff)
    {
    case MC_ID_SST25VF016:
        total_block = (16 * 1024 * 1024 / 8) / mtd->block_size;
        break;
    case MC_ID_SST25VF032:
        total_block = (32 * 1024 * 1024 / 8) / mtd->block_size;
        break;
    case MC_ID_SST25VF064:
        total_block = (64 * 1024 * 1024 / 8) / mtd->block_size;
        break;
    default:
        rt_kprintf("SST25 detection error, id: %x\n", id);
        return -RT_ERROR;
    }

    if ((block_end == RT_UINT32_MAX) || (block_end == 0))
    {
        block_end = total_block;
    }
    else if (block_end > total_block)
    {
        rt_kprintf("SST25 total block: %d, out of block\n", total_block);
        return -RT_ERROR;
    }

    mtd->block_start = block_start;
    mtd->block_end   = block_end;

    /* open nor file, if not exist, then create it  */
    sst25->file = fopen(NOR_SIM, "rb+");
    if (sst25->file == NULL)
    {
        rt_uint32_t i;
        /* create a file to simulate nor */
        sst25->file = fopen(NOR_SIM, "wb+");

        memset(block_buffer, 0xFF, sizeof(block_buffer));
        for (i = 0; i < total_block; i++)
        {
            fseek(sst25->file, i * BLOCK_SIZE, SEEK_SET);
            fwrite(block_buffer, BLOCK_SIZE, 1, sst25->file);
        }
    }

    fseek(sst25->file, 0, SEEK_SET);

    /* initialize hardware */
    sst25vfxx_hw_init(&_sst25_mtd);

    /* register MTD device */
    rt_mtd_nor_register_device("nor", mtd);

    return RT_EOK;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void nor_erase(void)
{
    rt_uint32_t index;
    struct rt_mtd_nor_device *mtd;

    mtd = RT_MTD_NOR_DEVICE(&_sst25_mtd);
    for (index = mtd->block_start; index < mtd->block_end; index ++)
    {
        sst25vfxx_erase_block(mtd, index * mtd->block_size, BLOCK_SIZE);
    }
}
FINSH_FUNCTION_EXPORT(nor_erase, erase all block in SPI flash);
#endif

#endif
