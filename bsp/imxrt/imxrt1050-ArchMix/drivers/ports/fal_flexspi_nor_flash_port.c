/*
 * File      : rt_ota_flash_sfud_port.c
 * COPYRIGHT (C) 2012-2018, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-26     armink       the first version
 */

#include <rtthread.h>
#include <fal.h>
#include <drv_flexspi.h>
#include <rthw.h>

static int read(long offset, uint8_t *buf, size_t size)
{
    memcpy(buf,(const void *)(FLEXSPI_AMBA_BASE+offset),size);
    return size;
}

static int write(long offset, const uint8_t *buf, size_t size)
{
    static char write_buffer[FLASH_PAGE_SIZE];
    size_t writen_size = 0;
    rt_uint32_t level;
    level = rt_hw_interrupt_disable();
    while(size)
    {
        if(size >= FLASH_PAGE_SIZE)
        {
            flexspi_nor_flash_page_program(FLEXSPI,offset,(const unsigned int *)buf);
            size -= FLASH_PAGE_SIZE;
            writen_size += FLASH_PAGE_SIZE;
        }
        else
        {
            memcpy(write_buffer,(const void *)(FLEXSPI_AMBA_BASE+offset),FLASH_PAGE_SIZE);
            memcpy(write_buffer,buf,size);
            flexspi_nor_flash_page_program(FLEXSPI,offset,(const unsigned int *)write_buffer);
            writen_size += size;
            size = 0;
        }
        offset += FLASH_PAGE_SIZE;
        buf += FLASH_PAGE_SIZE;
    }
    rt_hw_interrupt_enable(level);
    return writen_size;
}

static int erase(long offset, size_t size)
{
    size_t erase_size = size;
    rt_uint32_t level;
    level = rt_hw_interrupt_disable();
    size = offset;
    offset = (offset/FLEXSPI_NOR_SECTOR_SIZE)*FLEXSPI_NOR_SECTOR_SIZE;
    size = erase_size + size - offset;
    while(size)
    {
        flexspi_nor_flash_erase_sector(FLEXSPI,offset);
        if(size >= FLEXSPI_NOR_SECTOR_SIZE)
        {
            size -= FLEXSPI_NOR_SECTOR_SIZE;
        }
        else
        {
            size = 0;
        }
        offset += FLEXSPI_NOR_SECTOR_SIZE;
    }
    rt_hw_interrupt_enable(level);
    return erase_size;
}
struct fal_flash_dev nor_flash0 = { "norflash0", 0, FLASH_SIZE*1024, FLEXSPI_NOR_SECTOR_SIZE, {NULL, read, write, erase} };

