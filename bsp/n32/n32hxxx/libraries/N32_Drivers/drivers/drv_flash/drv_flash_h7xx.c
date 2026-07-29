/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 * 2026-06-16     li.mengmeng      implement for N32H7xx
 */

#include <rtconfig.h>
#include <rtdef.h>

#ifdef BSP_USING_ON_CHIP_FLASH
#include "drv_config.h"
#include "drv_flash_h7xx.h"
#include <board.h>
#include "n32h7xx_smu.h"

#if defined(RT_USING_FAL)
#include "fal.h"
#endif

#define DRV_DEBUG
#define LOG_TAG "drv.flash"
#include <drv_log.h>

#define N32_FLASH_SECTOR_SIZE ((rt_uint32_t)0x1000)  /* 4KB per erase sector */
#define N32_FLASH_PAGE_SIZE   ((rt_uint32_t)0x1000)  /* 4KB per page */

/**
  * @brief  Gets the page of a given address
  * @param  addr: Address of the FLASH Memory
  * @retval The page of a given address
  */
static uint32_t GetPage(uint32_t addr)
{
    return RT_ALIGN_DOWN(addr, N32_FLASH_PAGE_SIZE);
}

/**
 * Read data from flash.
 * @note This operation's units is word.
 *
 * @param addr flash address
 * @param buf buffer to store read data
 * @param size read bytes size
 *
 * @return result
 */
int n32_flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size)
{
    size_t i;

    if ((addr + size) > N32_FLASH_END_ADDRESS)
    {
        LOG_E("read outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    for (i = 0; i < size; i++, buf++, addr++)
    {
        *buf = *(rt_uint8_t *)addr;
    }

    return size;
}

/**
 * Write data to flash.
 * @note This operation must after erase. @see n32_flash_erase.
 *
 * @param addr flash address
 * @param buf the write data buffer
 * @param size write bytes size
 *
 * @return result
 */
int n32_flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size)
{
    rt_err_t    result   = RT_EOK;
    rt_uint32_t end_addr = addr + size;

    if ((end_addr) > N32_FLASH_END_ADDRESS)
    {
        LOG_E("write outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    if (size < 1)
    {
        return -RT_EINVAL;
    }

    if (SMU_WriteFlash(addr, (uint8_t *)buf, size) != FLASH_SUCCESS)
    {
        result = -RT_ERROR;
    }

    if (result != RT_EOK)
    {
        return result;
    }

    return size;
}

/**
 * Erase data on flash.
 * @note This operation is irreversible.
 * @note Erase unit is 4KB.
 *
 * @param addr flash address
 * @param size erase bytes size
 *
 * @return result
 */
int n32_flash_erase(rt_uint32_t addr, size_t size)
{
    rt_err_t    result   = RT_EOK;
    rt_uint32_t end_addr = addr + size;
    rt_uint32_t erase_addr;

    if ((end_addr) > N32_FLASH_END_ADDRESS)
    {
        LOG_E("ERROR: erase outrange flash size! addr is (0x%p)\n", (void *)(addr + size));
        return -RT_EINVAL;
    }

    erase_addr = GetPage(addr);

    while (erase_addr < end_addr)
    {
        if (SMU_EraseFlash(erase_addr) != FLASH_SUCCESS)
        {
            result = -RT_ERROR;
            goto __exit;
        }
        erase_addr += N32_FLASH_SECTOR_SIZE;
    }

__exit:
    if (result != RT_EOK)
    {
        return result;
    }

    LOG_D("erase done: addr (0x%p), size %d", (void *)addr, size);
    return size;
}

#if defined(RT_USING_FAL)

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_erase(long offset, size_t size);

const struct fal_flash_dev n32_onchip_flash = { "onchip_flash", N32_FLASH_START_ADRESS, N32_FLASH_SIZE, N32_FLASH_SECTOR_SIZE, { NULL, fal_flash_read, fal_flash_write, fal_flash_erase } };

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size)
{
    return n32_flash_read(n32_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size)
{
    return n32_flash_write(n32_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_erase(long offset, size_t size)
{
    return n32_flash_erase(n32_onchip_flash.addr + offset, size);
}

#endif /* RT_USING_FAL */

#endif /* BSP_USING_ON_CHIP_FLASH */
