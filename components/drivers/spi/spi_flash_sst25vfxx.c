/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-16     aozima       the first version
 */

#include <stdint.h>
#include "spi_flash_sst25vfxx.h"

#define FLASH_DEBUG

#ifdef FLASH_DEBUG
#define FLASH_TRACE         rt_kprintf
#else
#define FLASH_TRACE(...)
#endif /* #ifdef FLASH_DEBUG */

/* JEDEC Manufacturer’s ID */
#define MF_ID                       (0xBF)
/* JEDEC Device ID : Memory Type */
#define MT_ID                       (0x25)
/* JEDEC Device ID: Memory Capacity */
#define MC_ID_SST25VF020B            (0x8C) /* 2Mbit  */
#define MC_ID_SST25VF040B            (0x8D) /* 4Mbit  */
#define MC_ID_SST25VF080B            (0x8E) /* 8Mbit  */
#define MC_ID_SST25VF016B            (0x41) /* 16Mbit */
#define MC_ID_SST25VF032B            (0x4A) /* 32Mbit */
#define MC_ID_SST25VF064C            (0x4B) /* 64Mbit */

/* command list */
#define CMD_RDSR                    (0x05)
#define CMD_WRSR                    (0x01)
#define CMD_EWSR                    (0x50)
#define CMD_WRDI                    (0x04)
#define CMD_WREN                    (0x06)
#define CMD_READ                    (0x03)
#define CMD_FAST_READ               (0x0B)
#define CMD_BP                      (0x02)
#define CMD_AAIP                    (0xAD)
#define CMD_ERASE_4K                (0x20)
#define CMD_ERASE_32K               (0x52)
#define CMD_ERASE_64K               (0xD8)
#define CMD_ERASE_full              (0xC7)
#define CMD_JEDEC_ID                (0x9F)
#define CMD_EBSY                    (0x70)
#define CMD_DBSY                    (0x80)

#define DUMMY                       (0xFF)

static struct spi_flash_sst25vfxx  spi_flash_sst25vfxx;

static uint8_t sst25vfxx_read_status(struct spi_flash_sst25vfxx * spi_flash)
{
    return rt_spi_sendrecv8(spi_flash->rt_spi_device, CMD_RDSR);
}

static void sst25vfxx_wait_busy(struct spi_flash_sst25vfxx * spi_flash)
{
    while( sst25vfxx_read_status(spi_flash) & (0x01));
}

/** \brief write N page on [page]
 *
 * \param page uint32_t unit : byte (4096 * N,1 page = 4096byte)
 * \param buffer const uint8_t*
 * \param size uint32_t unit : byte ( 4096*N )
 * \return uint32_t
 *
 */
static uint32_t sst25vfxx_page_write(struct spi_flash_sst25vfxx * spi_flash, uint32_t page, const uint8_t * buffer, uint32_t size)
{
    uint32_t index;
    uint32_t need_wirte = size;
    uint8_t send_buffer[6];

    page &= ~0xFFF; // page size = 4096byte

    send_buffer[0] = CMD_WREN;
    rt_spi_send(spi_flash->rt_spi_device, send_buffer, 1);

    send_buffer[0] = CMD_ERASE_4K;
    send_buffer[1] = (page >> 16);
    send_buffer[2] = (page >> 8);
    send_buffer[3] = (page);
    rt_spi_send(spi_flash->rt_spi_device, send_buffer, 4);

    sst25vfxx_wait_busy(spi_flash); // wait erase done.

    send_buffer[0] = CMD_WREN;
    rt_spi_send(spi_flash->rt_spi_device, send_buffer, 1);

    send_buffer[0] = CMD_AAIP;
    send_buffer[1] = (uint8_t)(page >> 16);
    send_buffer[2] = (uint8_t)(page >> 8);
    send_buffer[3] = (uint8_t)(page);
    send_buffer[4] = *buffer++;
    send_buffer[5] = *buffer++;
    need_wirte -= 2;
    rt_spi_send(spi_flash->rt_spi_device, send_buffer, 6);

    sst25vfxx_wait_busy(spi_flash);

    for(index=0; index < need_wirte/2; index++)
    {
        send_buffer[0] = CMD_AAIP;
        send_buffer[1] = *buffer++;
        send_buffer[2] = *buffer++;
        rt_spi_send(spi_flash->rt_spi_device, send_buffer, 3);
        sst25vfxx_wait_busy(spi_flash);
    }

    send_buffer[0] = CMD_WRDI;
    rt_spi_send(spi_flash->rt_spi_device, send_buffer, 1);

    return size;
}

/* RT-Thread device interface */
static rt_err_t sst25vfxx_flash_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t sst25vfxx_flash_open(rt_device_t dev, rt_uint16_t oflag)
{
    rt_err_t result;
    uint8_t send_buffer[2];
    struct spi_flash_sst25vfxx * spi_flash = (struct spi_flash_sst25vfxx *)dev;

    /* lock spi flash */
    result = rt_mutex_take(&(spi_flash->lock), RT_WAITING_FOREVER);
    if(result != RT_EOK)
    {
        return result;
    }

    send_buffer[0] = CMD_DBSY;
    rt_spi_send(spi_flash->rt_spi_device, send_buffer, 1);

    send_buffer[0] = CMD_EWSR;
    rt_spi_send(spi_flash->rt_spi_device, send_buffer, 1);

    send_buffer[0] = CMD_WRSR;
    send_buffer[1] = 0;
    rt_spi_send(spi_flash->rt_spi_device, send_buffer, 2);

    /* release lock */
    rt_mutex_release(&(spi_flash->lock));

    return RT_EOK;
}

static rt_err_t sst25vfxx_flash_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t sst25vfxx_flash_control(rt_device_t dev, int cmd, void *args)
{
    struct spi_flash_sst25vfxx * spi_flash;

    spi_flash = (struct spi_flash_sst25vfxx *)dev;

    RT_ASSERT(dev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = spi_flash->geometry.bytes_per_sector;
        geometry->sector_count = spi_flash->geometry.sector_count;
        geometry->block_size = spi_flash->geometry.block_size;
    }

    return RT_EOK;
}

static rt_size_t sst25vfxx_flash_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_err_t result;
    uint8_t send_buffer[4];
    struct spi_flash_sst25vfxx * spi_flash = (struct spi_flash_sst25vfxx *)dev;
    uint32_t offset = pos * spi_flash->geometry.bytes_per_sector;

    /* lock spi flash */
    result = rt_mutex_take(&(spi_flash->lock), RT_WAITING_FOREVER);
    if(result != RT_EOK)
    {
        return 0;
    }

    send_buffer[0] = CMD_WRDI;
    rt_spi_send(spi_flash->rt_spi_device, send_buffer, 1);

    send_buffer[0] = CMD_READ;
    send_buffer[1] = (uint8_t)(offset>>16);
    send_buffer[2] = (uint8_t)(offset>>8);
    send_buffer[3] = (uint8_t)(offset);
    rt_spi_send_then_recv(spi_flash->rt_spi_device, send_buffer, 4, buffer, size * spi_flash->geometry.bytes_per_sector);

    /* release lock */
    rt_mutex_release(&(spi_flash->lock));

    return size;
}

static rt_size_t sst25vfxx_flash_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    uint32_t i;
    rt_err_t result;
    const uint8_t * write_buffer = buffer;
    struct spi_flash_sst25vfxx * spi_flash = (struct spi_flash_sst25vfxx *)dev;

    /* lock spi flash */
    result = rt_mutex_take(&(spi_flash->lock), RT_WAITING_FOREVER);
    if(result != RT_EOK)
    {
        return 0;
    }

    for(i=0; i<size; i++)
    {
        sst25vfxx_page_write(spi_flash,
                             (pos + i) * spi_flash->geometry.bytes_per_sector,
                             write_buffer,
                             spi_flash->geometry.bytes_per_sector);
        write_buffer += spi_flash->geometry.bytes_per_sector;
    }

    /* release lock */
    rt_mutex_release(&(spi_flash->lock));

    return size;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops sst25vfxx_device_ops =
{
    sst25vfxx_flash_init,
    sst25vfxx_flash_open,
    sst25vfxx_flash_close,
    sst25vfxx_flash_read,
    sst25vfxx_flash_write,
    sst25vfxx_flash_control
};
#endif

rt_err_t sst25vfxx_init(const char * flash_device_name, const char * spi_device_name)
{
    struct rt_spi_device * rt_spi_device;
    struct spi_flash_sst25vfxx * spi_flash = &spi_flash_sst25vfxx;

    rt_spi_device = (struct rt_spi_device *)rt_device_find(spi_device_name);
    if(rt_spi_device == RT_NULL)
    {
        FLASH_TRACE("spi device %s not found!\r\n", spi_device_name);
        return -RT_ENOSYS;
    }
    spi_flash->rt_spi_device = rt_spi_device;

    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0 and Mode 3 */
        cfg.max_hz = 50000000; /* 50M */
        rt_spi_configure(spi_flash->rt_spi_device, &cfg);
    }

    /* init flash */
    {
        rt_uint8_t cmd;
        rt_uint8_t id_recv[3];

        cmd = CMD_WRDI;
        rt_spi_send(spi_flash->rt_spi_device, &cmd, 1);

        /* read flash id */
        cmd = CMD_JEDEC_ID;
        rt_spi_send_then_recv(spi_flash->rt_spi_device, &cmd, 1, id_recv, 3);

        if(id_recv[0] != MF_ID || id_recv[1] != MT_ID)
        {
            FLASH_TRACE("Manufacturer’s ID or Memory Type error!\r\n");
            FLASH_TRACE("JEDEC Read-ID Data : %02X %02X %02X\r\n", id_recv[0], id_recv[1], id_recv[2]);
            return -RT_ENOSYS;
        }

        spi_flash->geometry.bytes_per_sector = 4096;
        spi_flash->geometry.block_size = 4096; /* block erase: 4k */

        if(id_recv[2] == MC_ID_SST25VF020B)
        {
            FLASH_TRACE("SST25VF020B detection\r\n");
            spi_flash->geometry.sector_count = 64;
        }
        else if(id_recv[2] == MC_ID_SST25VF040B)
        {
            FLASH_TRACE("SST25VF040B detection\r\n");
            spi_flash->geometry.sector_count = 128;
        }
        else if(id_recv[2] == MC_ID_SST25VF080B)
        {
            FLASH_TRACE("SST25VF080B detection\r\n");
            spi_flash->geometry.sector_count = 256;
        }
        else if(id_recv[2] == MC_ID_SST25VF016B)
        {
            FLASH_TRACE("SST25VF016B detection\r\n");
            spi_flash->geometry.sector_count = 512;
        }
        else if(id_recv[2] == MC_ID_SST25VF032B)
        {
            FLASH_TRACE("SST25VF032B detection\r\n");
            spi_flash->geometry.sector_count = 1024;
        }
        else if(id_recv[2] == MC_ID_SST25VF064C)
        {
            FLASH_TRACE("SST25VF064C detection\r\n");
            spi_flash->geometry.sector_count = 2048;
        }
        else
        {
            FLASH_TRACE("Memory Capacity error!\r\n");
            return -RT_ENOSYS;
        }
    }

    /* initialize mutex lock */
    rt_mutex_init(&spi_flash->lock, flash_device_name, RT_IPC_FLAG_PRIO);

    /* register device */
    spi_flash->flash_device.type    = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
    spi_flash->flash_device.ops     = &sst25vfxx_device_ops;
#else
    spi_flash->flash_device.init    = sst25vfxx_flash_init;
    spi_flash->flash_device.open    = sst25vfxx_flash_open;
    spi_flash->flash_device.close   = sst25vfxx_flash_close;
    spi_flash->flash_device.read    = sst25vfxx_flash_read;
    spi_flash->flash_device.write   = sst25vfxx_flash_write;
    spi_flash->flash_device.control = sst25vfxx_flash_control;
#endif
    /* no private */
    spi_flash->flash_device.user_data = RT_NULL;

    rt_device_register(&spi_flash->flash_device, flash_device_name,
                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);

    return RT_EOK;
}
