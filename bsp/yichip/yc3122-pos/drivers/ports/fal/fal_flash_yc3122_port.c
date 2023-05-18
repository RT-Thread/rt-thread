/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     
 * @brief    
 *
 * Change Logs:
 * Date            Author             Version        Notes
 * 2020-11-06      dengzhiqian         V1.0.0         the first version
 */
 
#include <fal.h>
#include "board.h"
#include "yc_qspi.h"

#define FLASH_START_ADRESS     ((uint32_t)0x1000000)
#define FLASH_SIZE             ((uint32_t)4*1024*1024)
#define FLASH_BLOCK_SIZE       ((uint32_t)512)
#define FLASH_END_ADDRESS      ((uint32_t)(FLASH_START_ADRESS + FLASH_SIZE))
#define FLASH_PAGE_NBPERBANK   128
#define FLASH_BANK_NUMBER      2

// #define YC3122_FLASH_DEBUG

static int read(long offset, uint8_t *buf, size_t size)
{
    uint32_t addr = yc3122_onchip_flash.addr + offset;

    if ((addr + size) > FLASH_END_ADDRESS)
    {
        rt_kprintf("ERROR: read outrange flash size! addr is (0x%p)\n", (void*)(addr + size));
        return -1;
    }

    qspi_flash_read(addr,buf,size);
    return size;
}


static int write(long offset, const uint8_t *buf, size_t size)
{
    uint32_t addr = yc3122_onchip_flash.addr + offset;

    if ((addr + size) > FLASH_END_ADDRESS)
    {
        rt_kprintf("ERROR: write outrange flash size! addr is (0x%p)\n", (void*)(addr + size));
        return -1;
    }
    if (size < 1)
    {
        return -1;
    }
    
    qspi_flash_write(addr,(uint8_t*)buf,size);

    return size;
}


static int erase(long offset, size_t size)
{
    uint32_t addr = yc3122_onchip_flash.addr + offset;

    rt_kprintf("addr:0x%x,size:0x%x\n", addr,size);
    if ((addr + size) > FLASH_END_ADDRESS)
    {
        rt_kprintf("ERROR: erase outrange flash size! addr is (0x%p)\n", (void*)(addr + size));
        return -1;
    }
    qspi_flash_sectorerase(addr);
    
#ifdef YC3122_FLASH_DEBUG
    rt_kprintf("stm32l4xx erase finish!\n");
#endif

    return size;
}

const struct fal_flash_dev yc3122_onchip_flash = 
{ 
    "onchip_flash",
    FLASH_START_ADRESS, 
    FLASH_SIZE, 
    FLASH_BLOCK_SIZE, 
    {NULL, read, write, erase} ,
    8,
};
