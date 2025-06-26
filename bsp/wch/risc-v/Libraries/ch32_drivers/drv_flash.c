/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-05-20     Chasel       first version
 *
 */

#include <rtconfig.h>
#include <rtdef.h>

#ifdef BSP_USING_ON_CHIP_FLASH
#include "drv_flash.h"
#include <board.h>

#if defined(RT_USING_FAL)
#include "fal.h"
#endif

#define DRV_DEBUG
#define LOG_TAG                "drv.flash"
#include <drv_log.h>

#define FLASH_PAGE_SIZE        4096

/* @note If there is no down-frequency processing, the timeout time needs to be modified */
#ifdef ProgramTimeout
#undef ProgramTimeout
#define ProgramTimeout             ((uint32_t)0x00010000)
#endif


/**
  * @brief  Gets the page of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The page of a given address
  */
static uint32_t GetPage(uint32_t addr)
{
    uint32_t page = 0;
    page = RT_ALIGN_DOWN(addr, FLASH_PAGE_SIZE);
    return page;
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
int ch32_flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size)
{
    size_t i;

    if ((addr + size) > CH32_FLASH_END_ADDRESS)
    {
        LOG_E("read outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    for (i = 0; i < size; i++, buf++, addr++)
    {
        *buf = *(rt_uint8_t *) addr;
    }

    return size;
}

/**
 * Write data to flash.
 * @note This operation's units is word.
 * @note This operation must after erase. @see flash_erase.
 *
 * @param addr flash address
 * @param buf the write data buffer
 * @param size write bytes size
 *
 * @return result
 */
int ch32_flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size)
{
    rt_err_t result        = RT_EOK;
    FLASH_Status status    = 0;
    rt_uint32_t end_addr   = addr + size;

    if (addr % 4 != 0)
    {
        LOG_E("write addr must be 4-byte alignment");
        return -RT_EINVAL;
    }

    if ((end_addr) > CH32_FLASH_END_ADDRESS)
    {
        LOG_E("write outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    if (((addr & 0x000000FF) == 0) && (size & 0xFFFFFF00)) {
        rt_uint32_t fast_size = (size & 0xFFFFFF00);

        status = FLASH_ROM_WRITE(addr, (rt_uint32_t *)buf, fast_size);
        if (status != FLASH_COMPLETE) {
            LOG_E("FLASH ROM Write Fail\r\n");
            return -RT_ERROR;
        }

        addr += fast_size;
        buf  += fast_size;
    }
    if (addr == end_addr) {
        return size;
    }

    FLASH_Access_Clock_Cfg(FLASH_Access_SYSTEM_HALF);
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_WRPRTERR);

    while (addr < end_addr)
    {
        status = FLASH_ProgramWord(addr, *((rt_uint32_t *)buf));
        if (status == FLASH_COMPLETE)
        {
            if (*(rt_uint32_t *)addr != *(rt_uint32_t *)buf)
            {
                result = -RT_ERROR;
                break;
            }
            addr += 4;
            buf  += 4;
        }
        else
        {
            result = -RT_ERROR;
            break;
        }
    }

    FLASH_Lock();
    FLASH_Access_Clock_Cfg(FLASH_Access_SYSTEM);

    if (result != RT_EOK)
    {
        return result;
    }

    return size;
}

/**
 * Erase data on flash .
 * @note This operation is irreversible.
 * @note This operation's units is different which on many chips.
 *
 * @param addr flash address
 * @param size erase bytes size
 *
 * @return result
 */
int ch32_flash_erase(rt_uint32_t addr, size_t size)
{
    rt_err_t result = RT_EOK;
    FLASH_Status status = 0;
    uint32_t num_page = 0;
    uint32_t i = 0;
    rt_uint32_t total_size = size;

    if ((addr + size) > CH32_FLASH_END_ADDRESS)
    {
        LOG_E("ERROR: erase outrange flash size! addr is (0x%p)\n", (void *)(addr + size));
        return -RT_EINVAL;
    }

    if (((addr & 0x000000FF) == 0) && (total_size & 0xFFFFFF00)) {
        rt_uint32_t fast_size = (total_size & 0xFFFFFF00);

        status = FLASH_ROM_ERASE(addr, fast_size);
        if (status != FLASH_COMPLETE) {
            LOG_E("FLASH ROM Erase Fail\r\n");
            return -RT_ERROR;
        }

        addr += fast_size;
        total_size -= fast_size;
    }

    if (0 == total_size) {
        return size;
    }

    FLASH_Access_Clock_Cfg(FLASH_Access_SYSTEM_HALF);
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_WRPRTERR);

    num_page = (total_size + FLASH_PAGE_SIZE - 1) / FLASH_PAGE_SIZE;

    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_WRPRTERR);

    for(i = 0; (i < num_page) && (status == FLASH_COMPLETE); i++)
    {
        status = FLASH_ErasePage(GetPage(addr + i * FLASH_PAGE_SIZE)); //Erase 4KB

        if(status != FLASH_COMPLETE)
        {
            LOG_E("FLASH Erase Fail\r\n");
            result = -RT_ERROR;
            goto __exit;
        }
    }

__exit:
    FLASH_Lock();
    FLASH_Access_Clock_Cfg(FLASH_Access_SYSTEM);

    if (result != RT_EOK)
    {
        return -RT_ERROR;
    }

    return size;
}


#if defined(RT_USING_FAL)

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_erase(long offset, size_t size);

const struct fal_flash_dev ch32_onchip_flash = { "onchip_flash", CH32_FLASH_START_ADRESS, CH32_FLASH_SIZE, FLASH_PAGE_SIZE, {NULL, fal_flash_read, fal_flash_write, fal_flash_erase}, 8, {} ,};

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size)
{
    return ch32_flash_read(ch32_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size)
{
    return ch32_flash_write(ch32_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_erase(long offset, size_t size)
{
    return ch32_flash_erase(ch32_onchip_flash.addr + offset, size);
}

#endif
#endif /* BSP_USING_ON_CHIP_FLASH */
