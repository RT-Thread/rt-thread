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
#include "rtdbg.h"

#define FLASH_START_ADRESS ((rt_uint32_t)0x1000000)
#define FLASH_SIZE ((rt_uint32_t)4 * 1024 * 1024)
#define FLASH_BLOCK_SIZE ((rt_uint32_t)512)
#define FLASH_END_ADDRESS ((rt_uint32_t)(FLASH_START_ADRESS + FLASH_SIZE))
#define FLASH_PAGE_NBPERBANK 256
#define FLASH_BANK_NUMBER 2
#define FLASH_PAGE_SIZE 256
// #define LOGOPEN
#ifdef LOGOPEN
    #define YC3122_FLASH_DEBUG LOG_D
#else
    #define YC3122_FLASH_DEBUG(...)
#endif
static int read(long offset, rt_uint8_t *buf, rt_size_t size)
{
    rt_uint32_t addr = yc3122_onchip_flash.addr + offset;

    if ((addr + size) > FLASH_END_ADDRESS)
    {
        YC3122_FLASH_DEBUG("ERROR: read outrange flash size! addr is (0x%p)\n", (void *)(addr + size));
        return -1;
    }
    YC3122_FLASH_DEBUG("r_ addr:0x%x,size:0x%x\n", addr, size);
    qspi_flash_read(addr, buf, size);
    return size;
}

static int write(long offset, const rt_uint8_t *buf, rt_size_t size)
{
    rt_uint32_t addr = yc3122_onchip_flash.addr + offset;

    if ((addr + size) > FLASH_END_ADDRESS)
    {
        YC3122_FLASH_DEBUG("ERROR: write outrange flash size! addr is (0x%p)\n", (void *)(addr + size));
        return -1;
    }
    if (size < 1)
    {
        return -1;
    }
    YC3122_FLASH_DEBUG("w_ addr:0x%x,size:0x%x\n", addr, size);
    qspi_flash_write(addr, (rt_uint8_t *)buf, size);

    return size;
}

static int erase(long offset, rt_size_t size)
{
    rt_uint32_t addr = yc3122_onchip_flash.addr + offset;
    if ((addr + size) > FLASH_END_ADDRESS || addr % 0x100 != 0)
    {
        YC3122_FLASH_DEBUG("ERROR: erase outrange flash size! addr is (0x%p)\n", (void *)(addr + size));
        return -1;
    }
    YC3122_FLASH_DEBUG("s_ addr:0x%x,size:0x%x\n", addr, size);
    if (addr % FLASH_PAGE_SIZE != 0)
    {
        YC3122_FLASH_DEBUG("ERROR: erase addr is not page alignment\n");
    }
    for (rt_uint32_t i = 0; i < size; i += 256)
        qspi_flash_pageerase(addr + i);
    return size;
}

const struct fal_flash_dev yc3122_onchip_flash =
{
    "onchip_flash",
    FLASH_START_ADRESS,
    FLASH_SIZE,
    FLASH_BLOCK_SIZE,
    {NULL, read, write, erase},
    8,
};