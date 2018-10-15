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
#include "spi_flash_at45dbxx.h"

#define FLASH_DEBUG
#define DMA_BUFFER_SIZE                         512

#ifdef FLASH_DEBUG
#define FLASH_TRACE         rt_kprintf
#else
#define FLASH_TRACE(...)
#endif /**< #ifdef FLASH_DEBUG */

/* JEDEC Manufacturer’s ID */
#define MF_ID                (0x1F) /* atmel */
#define DENSITY_CODE_011D    (0x02) /* AT45DB011D Density Code : 00010 = 1-Mbit */
#define DENSITY_CODE_021D    (0x03) /* AT45DB021D Density Code : 00011 = 2-Mbit */
#define DENSITY_CODE_041D    (0x04) /* AT45DB041D Density Code : 00100 = 4-Mbit */
#define DENSITY_CODE_081D    (0x05) /* AT45DB081D Density Code : 00101 = 8-Mbit */
#define DENSITY_CODE_161D    (0x06) /* AT45DB161D Density Code : 00110 = 16-Mbit */
#define DENSITY_CODE_321D    (0x07) /* AT45DB321D Density Code : 00111 = 32-Mbit */
#define DENSITY_CODE_642D    (0x08) /* AT45DB642D Density Code : 01000 = 64-Mbit */

struct JEDEC_ID
{
    uint8_t manufacturer_id;          /* Manufacturer ID */
    uint8_t density_code:5; /* Density Code */
    uint8_t family_code:3;  /* Family Code */
    uint8_t version_code:5; /* Product Version Code */
    uint8_t mlc_code:3;     /* MLC Code */
    uint8_t byte_count;     /* Byte Count */
};

#define AT45DB_BUFFER_1_WRITE                 0x84
#define AT45DB_BUFFER_2_WRITE                 0x87
#define AT45DB_BUFFER_1_READ                  0xD4
#define AT45DB_BUFFER_2_READ                  0xD6
#define AT45DB_B1_TO_MM_PAGE_PROG_WITH_ERASE  0x83
#define AT45DB_B2_TO_MM_PAGE_PROG_WITH_ERASE  0x86
#define AT45DB_MM_PAGE_TO_B1_XFER             0x53
#define AT45DB_MM_PAGE_TO_B2_XFER             0x55
#define AT45DB_PAGE_ERASE                     0x81
#define AT45DB_SECTOR_ERASE                   0x7C
#define AT45DB_READ_STATE_REGISTER            0xD7
#define AT45DB_MM_PAGE_READ                   0xD2
#define AT45DB_MM_PAGE_PROG_THRU_BUFFER1      0x82
#define AT45DB_CMD_JEDEC_ID                   0x9F

static struct spi_flash_at45dbxx  spi_flash_at45dbxx;

/*****************************************************************************/
/*Status Register Format:                                   */
/* ------------------------------------------------------------------------- */
/* | bit7   | bit6   | bit5   | bit4   | bit3   | bit2   | bit1   | bit0   | */
/* |--------|--------|--------|--------|--------|--------|--------|--------| */
/* |RDY/BUSY| COMP   |         device density            |   X    |   X    | */
/* ------------------------------------------------------------------------- */
/* 0:busy   |        |        AT45DB041:0111             | protect|page size */
/* 1:ready  |        |        AT45DB161:1011             |                   */
/* --------------------------------------------------------------------------*/
/*****************************************************************************/
static uint8_t AT45DB_StatusRegisterRead(void)
{
    return rt_spi_sendrecv8(spi_flash_at45dbxx.rt_spi_device, AT45DB_READ_STATE_REGISTER);
}

static void wait_busy(void)
{
    uint16_t i = 0;
    while (i++ < 10000)
    {
        if (AT45DB_StatusRegisterRead() & 0x80)
        {
            return;
        }
    }
    FLASH_TRACE("\r\nSPI_FLASH timeout!!!\r\n");
}

/* RT-Thread Device Driver Interface */
static rt_err_t AT45DB_flash_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t AT45DB_flash_open(rt_device_t dev, rt_uint16_t oflag)
{

    return RT_EOK;
}

static rt_err_t AT45DB_flash_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t AT45DB_flash_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = 512;
        geometry->sector_count = 4096;
        geometry->block_size = 4096; /* block erase: 4k */
    }

    return RT_EOK;
}

static rt_size_t AT45DB_flash_read_page_256(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    uint32_t index, nr;
    uint8_t * read_buffer = buffer;
    uint32_t  page = pos;

    nr = size;

    for (index = 0; index < nr; index++)
    {
        uint8_t send_buffer[8];
        uint32_t i;

        for(i=0; i<sizeof(send_buffer); i++)
        {
            send_buffer[i] = 0;
        }

        send_buffer[0] = AT45DB_MM_PAGE_READ;
        send_buffer[1] = (uint8_t)(page >> 7);
        send_buffer[2] = (uint8_t)(page << 1);

        rt_spi_send_then_recv(spi_flash_at45dbxx.rt_spi_device, send_buffer, 8, read_buffer, 256);
        read_buffer += 256;
        page++;
    }

    return size;
}

static rt_size_t AT45DB_flash_read_page_512(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    uint32_t index, nr;
    uint8_t * read_buffer = buffer;
    uint32_t  page = pos;

    nr = size;

    for (index = 0; index < nr; index++)
    {
        uint8_t send_buffer[8];
        uint32_t i;

        for(i=0; i<sizeof(send_buffer); i++)
        {
            send_buffer[i] = 0;
        }

        send_buffer[0] = AT45DB_MM_PAGE_READ;
        send_buffer[1] = (uint8_t)(page >> 6);
        send_buffer[2] = (uint8_t)(page << 2);

        rt_spi_send_then_recv(spi_flash_at45dbxx.rt_spi_device, send_buffer, 8, read_buffer, 512);
        read_buffer += 512;
        page++;
    }

    return size;
}

static rt_size_t AT45DB_flash_read_page_1024(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    uint32_t index, nr;
    uint8_t * read_buffer = buffer;
    uint32_t  page = pos;

    nr = size;

    for (index = 0; index < nr; index++)
    {
        uint8_t send_buffer[8];
        uint32_t i;

        for(i=0; i<sizeof(send_buffer); i++)
        {
            send_buffer[i] = 0;
        }

        send_buffer[0] = AT45DB_MM_PAGE_READ;
        send_buffer[1] = (uint8_t)(page >> 5);
        send_buffer[2] = (uint8_t)(page << 3);

        rt_spi_send_then_recv(spi_flash_at45dbxx.rt_spi_device, send_buffer, 8, read_buffer, 1024);
        read_buffer += 1024;
        page++;
    }

    return size;
}

static rt_size_t AT45DB_flash_write_page_256(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_uint32_t index, nr;
    const uint8_t * write_buffer = buffer;
    uint32_t  page = pos;

    nr = size;

    for (index = 0; index < nr; index++)
    {
        uint8_t send_buffer[4];

        send_buffer[0] = AT45DB_MM_PAGE_PROG_THRU_BUFFER1;
        send_buffer[1] = (uint8_t) (page >> 7);
        send_buffer[2] = (uint8_t) (page << 1);
        send_buffer[3] = 0;

        rt_spi_send_then_send(spi_flash_at45dbxx.rt_spi_device, send_buffer, 4, write_buffer, 256);

        write_buffer += 256;
        page++;

        wait_busy();
    }

    return size;
}

static rt_size_t AT45DB_flash_write_page_512(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_uint32_t index, nr;
    const uint8_t * write_buffer = buffer;
    uint32_t  page = pos;

    nr = size;

    for (index = 0; index < nr; index++)
    {
        uint8_t send_buffer[4];

        send_buffer[0] = AT45DB_MM_PAGE_PROG_THRU_BUFFER1;
        send_buffer[1] = (uint8_t) (page >> 6);
        send_buffer[2] = (uint8_t) (page << 2);
        send_buffer[3] = 0;

        rt_spi_send_then_send(spi_flash_at45dbxx.rt_spi_device, send_buffer, 4, write_buffer, 512);

        write_buffer += 512;
        page++;

        wait_busy();
    }

    return size;
}

static rt_size_t AT45DB_flash_write_page_1024(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_uint32_t index, nr;
    const uint8_t * write_buffer = buffer;
    uint32_t  page = pos;

    nr = size;

    for (index = 0; index < nr; index++)
    {
        uint8_t send_buffer[4];

        send_buffer[0] = AT45DB_MM_PAGE_PROG_THRU_BUFFER1;
        send_buffer[1] = (uint8_t) (page >> 5);
        send_buffer[2] = (uint8_t) (page << 3);
        send_buffer[3] = 0;

        rt_spi_send_then_send(spi_flash_at45dbxx.rt_spi_device, send_buffer, 4, write_buffer, 1024);

        write_buffer += 1024;
        page++;

        wait_busy();
    }

    return size;
}

rt_err_t at45dbxx_init(const char * flash_device_name, const char * spi_device_name)
{
    struct rt_spi_device * rt_spi_device;
    struct JEDEC_ID * JEDEC_ID;

    rt_spi_device = (struct rt_spi_device *)rt_device_find(spi_device_name);
    if(rt_spi_device == RT_NULL)
    {
        FLASH_TRACE("spi device %s not found!\r\n", spi_device_name);
        return -RT_ENOSYS;
    }
    spi_flash_at45dbxx.rt_spi_device = rt_spi_device;

    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible Modes 0 and 3 */
        cfg.max_hz = 66000000; /* Atmel RapidS Serial Interface: 66MHz Maximum Clock Frequency */
        rt_spi_configure(spi_flash_at45dbxx.rt_spi_device, &cfg);
    }

    /* read JEDEC ID */
    {
        uint8_t cmd;
        uint8_t id_recv[6];
        JEDEC_ID = (struct JEDEC_ID *)id_recv;

        cmd = AT45DB_CMD_JEDEC_ID;
        rt_spi_send_then_recv(spi_flash_at45dbxx.rt_spi_device, &cmd, 1, id_recv, 6);

        /**< 1FH = Atmel */
        /**< 001 = Atmel DataFlash */
        if(JEDEC_ID->manufacturer_id != 0x1F || JEDEC_ID->family_code != 0x01)
        {
            FLASH_TRACE("Manufacturer’s ID or Memory Type error!\r\n");
            FLASH_TRACE("JEDEC Read-ID Data : %02X %02X %02X\r\n", id_recv[0], id_recv[1], id_recv[2]);
            return -RT_ENOSYS;
        }

        if(JEDEC_ID->density_code == DENSITY_CODE_011D)
        {
            /**< AT45DB011D Density Code : 00010 = 1-Mbit */
            FLASH_TRACE("AT45DB011D detection\r\n");
            spi_flash_at45dbxx.geometry.bytes_per_sector = 256; /* Page Erase (256 Bytes) */
            spi_flash_at45dbxx.geometry.sector_count = 512;     /* 1-Mbit / 8 / 256 = 512 */
            spi_flash_at45dbxx.geometry.block_size = 1024*2;    /* Block Erase (2-Kbytes) */
        }
        else if(JEDEC_ID->density_code == DENSITY_CODE_021D)
        {
            /**< AT45DB021D Density Code : 00011 = 2-Mbit */
            FLASH_TRACE("AT45DB021D detection\r\n");
            spi_flash_at45dbxx.geometry.bytes_per_sector = 256; /* Page Erase (256 Bytes) */
            spi_flash_at45dbxx.geometry.sector_count = 512*2;   /* 2-Mbit / 8 / 256 = 1024 */
            spi_flash_at45dbxx.geometry.block_size = 1024*2;    /* Block Erase (2-Kbytes) */
        }
        else if(JEDEC_ID->density_code == DENSITY_CODE_041D)
        {
            /**< AT45DB041D Density Code : 00100 = 4-Mbit */
            FLASH_TRACE("AT45DB041D detection\r\n");
            spi_flash_at45dbxx.geometry.bytes_per_sector = 256; /* Page Erase (256 Bytes) */
            spi_flash_at45dbxx.geometry.sector_count = 512*4;   /* 4-Mbit / 8 / 256 = 2048 */
            spi_flash_at45dbxx.geometry.block_size = 1024*2;    /* Block Erase (2-Kbytes) */
        }
        else if(JEDEC_ID->density_code == DENSITY_CODE_081D)
        {
            /**< AT45DB081D Density Code : 00101 = 8-Mbit */
            FLASH_TRACE("AT45DB081D detection\r\n");
            spi_flash_at45dbxx.geometry.bytes_per_sector = 256; /* Page Erase (256 Bytes) */
            spi_flash_at45dbxx.geometry.sector_count = 512*8;   /* 8-Mbit / 8 / 256 = 4096 */
            spi_flash_at45dbxx.geometry.block_size = 1024*2;    /* Block Erase (2-Kbytes) */
        }
        else if(JEDEC_ID->density_code == DENSITY_CODE_161D)
        {
            /**< AT45DB161D Density Code : 00110 = 16-Mbit */
            FLASH_TRACE("AT45DB161D detection\r\n");
            spi_flash_at45dbxx.geometry.bytes_per_sector = 512; /* Page Erase (512 Bytes) */
            spi_flash_at45dbxx.geometry.sector_count = 256*16;  /* 16-Mbit / 8 / 512 = 4096 */
            spi_flash_at45dbxx.geometry.block_size = 1024*4;    /* Block Erase (4-Kbytes) */
        }
        else if(JEDEC_ID->density_code == DENSITY_CODE_321D)
        {
            /**< AT45DB321D Density Code : 00111 = 32-Mbit */
            FLASH_TRACE("AT45DB321D detection\r\n");
            spi_flash_at45dbxx.geometry.bytes_per_sector = 512; /* Page Erase (512 Bytes) */
            spi_flash_at45dbxx.geometry.sector_count = 256*32;  /* 32-Mbit / 8 / 512 = 8192 */
            spi_flash_at45dbxx.geometry.block_size = 1024*4;    /* Block Erase (4-Kbytes) */
        }
        else if(JEDEC_ID->density_code == DENSITY_CODE_642D)
        {
            /**< AT45DB642D Density Code : 01000 = 64-Mbit */
            FLASH_TRACE("AT45DB642D detection\r\n");
            spi_flash_at45dbxx.geometry.bytes_per_sector = 1024; /* Page Erase (1 Kbyte) */
            spi_flash_at45dbxx.geometry.sector_count = 128*64;   /* 64-Mbit / 8 / 1024 = 8192 */
            spi_flash_at45dbxx.geometry.block_size = 1024*8;     /* Block Erase (8 Kbytes) */
        }
        else
        {
            FLASH_TRACE("Memory Capacity error!\r\n");
            return -RT_ENOSYS;
        }
    }

    /* register device */
    spi_flash_at45dbxx.flash_device.type    = RT_Device_Class_Block;
    spi_flash_at45dbxx.flash_device.init    = AT45DB_flash_init;
    spi_flash_at45dbxx.flash_device.open    = AT45DB_flash_open;
    spi_flash_at45dbxx.flash_device.close   = AT45DB_flash_close;
    spi_flash_at45dbxx.flash_device.control = AT45DB_flash_control;

    if(JEDEC_ID->density_code == DENSITY_CODE_642D)
    {
        spi_flash_at45dbxx.flash_device.read 	  = AT45DB_flash_read_page_1024;
        spi_flash_at45dbxx.flash_device.write   = AT45DB_flash_write_page_1024;
    }
    else if(JEDEC_ID->density_code == DENSITY_CODE_161D
            || JEDEC_ID->density_code == DENSITY_CODE_321D )
    {
        spi_flash_at45dbxx.flash_device.read 	  = AT45DB_flash_read_page_512;
        spi_flash_at45dbxx.flash_device.write   = AT45DB_flash_write_page_512;
    }
    else
    {
        spi_flash_at45dbxx.flash_device.read 	  = AT45DB_flash_read_page_256;
        spi_flash_at45dbxx.flash_device.write   = AT45DB_flash_write_page_256;
    }

    /* no private */
    spi_flash_at45dbxx.flash_device.user_data = RT_NULL;

    rt_device_register(&spi_flash_at45dbxx.flash_device, flash_device_name,
                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);

    return RT_EOK;
}
