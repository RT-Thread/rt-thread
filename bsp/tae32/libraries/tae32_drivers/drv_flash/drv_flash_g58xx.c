/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-02-22     yeml   first version
 *
 */
#include <rtconfig.h>
#include <rtdef.h>


#ifdef BSP_USING_ON_CHIP_FLASH
#include "drv_flash.h"
#include "board.h"

#if defined(RT_USING_FAL)
    #include "fal.h"
#endif

#define DBG_TAG             "FLASH"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"
int tae32_flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size)
{
    size_t i;

    if ((addr + size) > TAE32_FLASH_END_ADDRESS)
    {
        LOG_E("read outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }
    for (i = 0; i < size; i++)
    {
        *buf = *((rt_uint8_t *)addr);
        addr++;
        buf++;
    }
    return i;
}

int tae32_flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size)
{
    rt_err_t result        = RT_EOK;
    rt_uint32_t end_addr   = addr + size;

    if (addr % 4 != 0)
    {
        LOG_E("write addr must be 4-byte alignment");
        return -RT_EINVAL;
    }

    if ((end_addr) > TAE32_FLASH_END_ADDRESS)
    {
        LOG_E("write outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    LL_EFLASH_ProgErase_Unlock(EFLASH);

    if (0 == LL_EFLASH_Program(EFLASH, addr, (rt_uint8_t *)buf, size))
    {
        LOG_E("write size must be 8-byte alignment");
        result = -RT_ERROR;
    }

    LL_EFLASH_ProgErase_Lock(EFLASH);

    if (result != RT_EOK)
    {
        return result;
    }
    else
    {
        return size;
    }
}

int tae32_flash_erase(rt_uint32_t addr, size_t size)
{
    rt_err_t result        = RT_EOK;

    rt_uint32_t sector_num = 0;
    rt_uint32_t sector_cnt = 0;
    rt_uint32_t sector_size = 0;
    rt_uint32_t flash_sec_nums    = 0;
    size_t i = 0;

    if ((addr + size) > TAE32_FLASH_END_ADDRESS)
    {
        LOG_E("read outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    if (size < 1)
    {
        return -RT_EINVAL;
    }

    flash_sec_nums = LL_EFLASH_SectorNums_Get(EFLASH);
    if (flash_sec_nums == EFLASH_SECTOR_NUM_256_S)
    {
        sector_size = EFLASH_SECTOR_SIZE_256_S;
    }
    else
    {
        sector_size = EFLASH_SECTOR_SIZE_256_D;
    }

    sector_cnt = size / sector_size;
    if(size % sector_size)
    {
        sector_cnt++;
    }
    sector_num = (addr -  0x08000000) / sector_size;

    LL_EFLASH_ProgErase_Unlock(EFLASH);
    for (i = 0; i < sector_cnt; i++)
    {
        if (LL_EFLASH_EraseSector(EFLASH, sector_num) != LL_OK)
        {
            result = -RT_ERROR;
            break;
        }
        sector_num++;
    }
    LL_EFLASH_ProgErase_Lock(EFLASH);

    if (result != RT_EOK)
    {
        return result;
    }
    else
    {
        return size;
    }
}

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_erase(long offset, size_t size);

const struct fal_flash_dev tae32_onchip_flash =
{
    "onchip_flash",
    ((uint32_t)0x08000000),
#ifdef BSP_USING_FLASH_SBANK
    (EFLASH_SECTOR_NUM_256_S * EFLASH_SECTOR_SIZE_256_S),
    EFLASH_SECTOR_SIZE_256_S,
#else
    (EFLASH_SECTOR_NUM_256_D * EFLASH_SECTOR_SIZE_256_D),
    EFLASH_SECTOR_SIZE_256_D,
#endif
    {
        NULL,
        fal_flash_read,
        fal_flash_write,
        fal_flash_erase
    }
};


static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size)
{
    return tae32_flash_read(tae32_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size)
{
    return tae32_flash_write(tae32_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_erase(long offset, size_t size)
{
    return tae32_flash_erase(tae32_onchip_flash.addr + offset, size);
}


#endif /* BSP_USING_ON_CHIP_FLASH */