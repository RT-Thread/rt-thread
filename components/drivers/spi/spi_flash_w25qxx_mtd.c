/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "spi_flash.h"
#include "spi_flash_w25qxx_mtd.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FLASH_DEBUG

#ifdef FLASH_DEBUG
#define FLASH_TRACE         printf
#else
#define FLASH_TRACE(...)
#endif /* #ifdef FLASH_DEBUG */

/* JEDEC Manufacturer’s ID */
#define MF_ID           (0xEF)
/* JEDEC Device ID: Memory type and Capacity */
#define MTC_W25Q80_BV         (0x4014) /* W25Q80BV */
#define MTC_W25Q16_BV_CL_CV   (0x4015) /* W25Q16BV W25Q16CL W25Q16CV  */
#define MTC_W25Q16_DW         (0x6015) /* W25Q16DW  */
#define MTC_W25Q32_BV         (0x4016) /* W25Q32BV */
#define MTC_W25Q32_DW         (0x6016) /* W25Q32DW */
#define MTC_W25Q64_BV_CV      (0x4017) /* W25Q64BV W25Q64CV */
#define MTC_W25Q64_DW         (0x4017) /* W25Q64DW */
#define MTC_W25Q128_BV        (0x4018) /* W25Q128BV */
#define MTC_W25Q256_FV        (TBD)    /* W25Q256FV */

#define MTC_W25X80            (0x3014)

/* command list */
#define CMD_WRSR                    (0x01)  /* Write Status Register */
#define CMD_PP                      (0x02)  /* Page Program */
#define CMD_READ                    (0x03)  /* Read Data */
#define CMD_WRDI                    (0x04)  /* Write Disable */
#define CMD_RDSR1                   (0x05)  /* Read Status Register-1 */
#define CMD_WREN                    (0x06)  /* Write Enable */
#define CMD_FAST_READ               (0x0B)  /* Fast Read */
#define CMD_ERASE_4K                (0x20)  /* Sector Erase:4K */
#define CMD_RDSR2                   (0x35)  /* Read Status Register-2 */
#define CMD_ERASE_32K               (0x52)  /* 32KB Block Erase */
#define CMD_JEDEC_ID                (0x9F)  /* Read JEDEC ID */
#define CMD_ERASE_full              (0xC7)  /* Chip Erase */
#define CMD_ERASE_64K               (0xD8)  /* 64KB Block Erase */
#define CMD_MANU_ID                 (0x90)

#define DUMMY                       (0xFF)

#define FLASH_ERASE_CMD             CMD_ERASE_4K
#define FLASH_BLOCK_SIZE            4096
#define FLASH_PAGE_SIZE             256

static void w25qxx_lock(struct rt_mtd_nor_device *device)
{
    struct spi_flash_mtd *mtd = (struct spi_flash_mtd *)device;
    rt_mutex_take(&mtd->lock, RT_WAITING_FOREVER);
}

static void w25qxx_unlock(struct rt_mtd_nor_device *device)
{
    struct spi_flash_mtd *mtd = (struct spi_flash_mtd *)device;
    rt_mutex_release(&mtd->lock);
}

static rt_uint8_t w25qxx_read_status(struct rt_mtd_nor_device *device)
{
    struct spi_flash_mtd *mtd = (struct spi_flash_mtd *)device;
    return rt_spi_sendrecv8(mtd->rt_spi_device, CMD_RDSR1);
}

static void w25qxx_wait_busy(struct rt_mtd_nor_device *device)
{
    while( w25qxx_read_status(device) & (0x01));
}

static rt_err_t w25qxx_read_id(struct rt_mtd_nor_device *device)
{
    rt_uint8_t cmd;
    rt_uint8_t id_recv[3];

    struct spi_flash_mtd *mtd = (struct spi_flash_mtd *)device;

    w25qxx_lock(device);

    cmd = 0xFF; /* reset SPI FLASH, cancel all cmd in processing. */
    rt_spi_send(mtd->rt_spi_device, &cmd, 1);

    cmd = CMD_WRDI;
    rt_spi_send(mtd->rt_spi_device, &cmd, 1);

    /* read flash id */
    cmd = CMD_JEDEC_ID;
    rt_spi_send_then_recv(mtd->rt_spi_device, &cmd, 1, id_recv, 3);

    w25qxx_unlock(device);

    return (rt_uint32_t)(id_recv[0] << 16) | (id_recv[1] << 8) | id_recv[2];
}

static rt_size_t w25qxx_read(struct rt_mtd_nor_device *device, rt_off_t offset, rt_uint8_t *buffer, rt_size_t length)
{
    struct spi_flash_mtd *mtd = (struct spi_flash_mtd *)device;
    rt_uint8_t send_buffer[4];

    if((offset + length) > device->block_end * FLASH_BLOCK_SIZE)
        return 0;


    w25qxx_lock(device);

    send_buffer[0] = CMD_WRDI;
    rt_spi_send(mtd->rt_spi_device, send_buffer, 1);

    send_buffer[0] = CMD_READ;
    send_buffer[1] = (rt_uint8_t)(offset>>16);
    send_buffer[2] = (rt_uint8_t)(offset>>8);
    send_buffer[3] = (rt_uint8_t)(offset);
    rt_spi_send_then_recv(mtd->rt_spi_device,
                          send_buffer, 4,
                          buffer, length);

    w25qxx_unlock(device);
    return length;
}

static rt_size_t w25qxx_write(struct rt_mtd_nor_device *device, rt_off_t offset, const rt_uint8_t *buffer, rt_size_t length)
{
    struct spi_flash_mtd *mtd = (struct spi_flash_mtd *)device;
    rt_uint8_t send_buffer[4];
    rt_uint8_t *write_ptr ;
    rt_size_t   write_size,write_total;

    if((offset + length) > device->block_end * FLASH_BLOCK_SIZE)
        return 0;

    w25qxx_lock(device);

    send_buffer[0] = CMD_WREN;
    rt_spi_send(mtd->rt_spi_device, send_buffer, 1);
    w25qxx_wait_busy(device); // wait erase done.

    write_size  = 0;
    write_total = 0;
    write_ptr   = (rt_uint8_t *)buffer;
    while(write_total < length)
    {
        send_buffer[0] = CMD_WREN;
        rt_spi_send(mtd->rt_spi_device, send_buffer, 1);

        //write first page...
        send_buffer[0] = CMD_PP;
        send_buffer[1] = (rt_uint8_t)(offset >> 16);
        send_buffer[2] = (rt_uint8_t)(offset >> 8);
        send_buffer[3] = (rt_uint8_t)(offset);

        //address % FLASH_PAGE_SIZE + length
        if(((offset & (FLASH_PAGE_SIZE - 1)) + (length - write_total)) > FLASH_PAGE_SIZE)
        {
            write_size = FLASH_PAGE_SIZE - (offset & (FLASH_PAGE_SIZE - 1));
        }
        else
        {
            write_size = (length - write_total);
        }

        rt_spi_send_then_send(mtd->rt_spi_device,
                              send_buffer, 4,
                              write_ptr + write_total, write_size);
        w25qxx_wait_busy(device);


        offset      += write_size;
        write_total += write_size;
    }

    send_buffer[0] = CMD_WRDI;
    rt_spi_send(mtd->rt_spi_device, send_buffer, 1);

    w25qxx_unlock(device);

    return length;
}

static rt_err_t w25qxx_erase_block(struct rt_mtd_nor_device *device, rt_off_t offset, rt_uint32_t length)
{
    struct spi_flash_mtd *mtd = (struct spi_flash_mtd *)device;
    rt_uint8_t  send_buffer[4];
    rt_uint32_t erase_size = 0;

    //offset must be ALIGN_DOWN to BLOCKSIZE
    if(offset != RT_ALIGN_DOWN(offset,FLASH_BLOCK_SIZE))
        return 0;

    if((offset + length) > device->block_end * FLASH_BLOCK_SIZE)
        return 0;

    /* check length must align to block size */
    if(length %  device->block_size != 0)
    {
        rt_kprintf("param length = %d ,error\n",length);
        return 0;
    }

    w25qxx_lock(device);

    send_buffer[0] = CMD_WREN;
    rt_spi_send(mtd->rt_spi_device, send_buffer, 1);
    w25qxx_wait_busy(device); // wait erase done.
    while (erase_size < length)
    {
        send_buffer[0] = CMD_ERASE_4K;
        send_buffer[1] = (rt_uint8_t) (offset >> 16);
        send_buffer[2] = (rt_uint8_t) (offset >> 8);
        send_buffer[3] = (rt_uint8_t) (offset);
        rt_spi_send(mtd->rt_spi_device, send_buffer, 4);
        w25qxx_wait_busy(device);    // wait erase done.

        erase_size += 4096;
        offset += 4096;
    }
    send_buffer[0] = CMD_WRDI;
    rt_spi_send(mtd->rt_spi_device, send_buffer, 1);

    w25qxx_unlock(device);
    return RT_EOK;
}

const static struct rt_mtd_nor_driver_ops w25qxx_mtd_ops =
{
    w25qxx_read_id,
    w25qxx_read,
    w25qxx_write,
    w25qxx_erase_block,
};

rt_err_t w25qxx_mtd_init(const char *mtd_name,const char * spi_device_name)
{
    rt_err_t    result = RT_EOK;
    rt_uint32_t id;
    rt_uint8_t  send_buffer[3];

    struct rt_spi_device*   rt_spi_device;
    struct spi_flash_mtd*   mtd = (struct spi_flash_mtd *)rt_malloc(sizeof(struct spi_flash_mtd));

    RT_ASSERT(mtd != RT_NULL);

    /* initialize mutex */
    if (rt_mutex_init(&mtd->lock, mtd_name, RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        FLASH_TRACE("init mtd lock mutex failed\n");
        result = -RT_ENOSYS;

        goto _error_exit;
    }

    rt_spi_device = (struct rt_spi_device *)rt_device_find(spi_device_name);
    if(rt_spi_device == RT_NULL)
    {
        FLASH_TRACE("spi device %s not found!\r\n", spi_device_name);
        result = -RT_ENOSYS;

        goto _error_exit;
    }
    mtd->rt_spi_device = rt_spi_device;
    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0 and Mode 3 */
        cfg.max_hz = 20 * 1000 * 1000; /* 20 */
        rt_spi_configure(rt_spi_device, &cfg);
    }

    /* Init Flash device */
    {
        w25qxx_lock(&mtd->mtd_device);

        send_buffer[0] = CMD_WREN;
        rt_spi_send(mtd->rt_spi_device, send_buffer, 1);
        w25qxx_wait_busy(&mtd->mtd_device);

        send_buffer[0] = CMD_WRSR;
        send_buffer[1] = 0;
        send_buffer[2] = 0;
        rt_spi_send(mtd->rt_spi_device, send_buffer, 3);
        w25qxx_wait_busy(&mtd->mtd_device);

        w25qxx_unlock(&mtd->mtd_device);
    }

    id = w25qxx_read_id(&mtd->mtd_device);

    mtd->mtd_device.block_size  = 4096;
    mtd->mtd_device.block_start = 0;
    switch(id & 0xFFFF)
    {
        case MTC_W25Q80_BV: /* W25Q80BV */
            mtd->mtd_device.block_end = 256;
            break;
        case MTC_W25Q16_BV_CL_CV: /* W25Q16BV W25Q16CL W25Q16CV  */
        case MTC_W25Q16_DW: /* W25Q16DW  */
            mtd->mtd_device.block_end = 512;
            break;
        case MTC_W25Q32_BV: /* W25Q32BV */
        case MTC_W25Q32_DW: /* W25Q32DW */
            mtd->mtd_device.block_end = 1024;
            break;
        case MTC_W25Q64_BV_CV: /* W25Q64BV W25Q64CV */
            mtd->mtd_device.block_end = 2048;
            break;
        case MTC_W25Q128_BV: /* W25Q128BV */
            mtd->mtd_device.block_end = 4086;
            break;
    }
    mtd->mtd_device.ops = &w25qxx_mtd_ops;
    rt_mtd_nor_register_device(mtd_name,&mtd->mtd_device);

    return RT_EOK;

_error_exit:
    if(mtd != RT_NULL)
        rt_free(mtd);
    return result;
}
