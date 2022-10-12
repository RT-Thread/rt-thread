/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 */

#include <rtthread.h>
#include "drv_common.h"

#ifdef BSP_USING_ON_CHIP_FLASH
#include "drv_flash.h"

#if defined(RT_USING_FAL)
#include "fal.h"
#endif

//#define DRV_DEBUG
#define LOG_TAG                "drv.flash"
#include <drv_log.h>

/**
  * @brief  gets the page of a given address
  * @param  addr: address of the flash memory
  * @retval the page of a given address
  */
static rt_uint32_t get_page(uint32_t addr)
{
    rt_uint32_t page = 0;

    page = RT_ALIGN_DOWN(addr, FLASH_PAGE_SIZE);

    return page;
}

/**
 * @brief read data from flash.
 * @note this operation's units is word.
 *
 * @param addr flash address
 * @param buf buffer to store read data
 * @param size read bytes size
 *
 * @return result
 */
int at32_flash_read(rt_uint32_t addr, rt_uint8_t *buf, rt_uint32_t size)
{
    rt_uint32_t i;

    if ((addr + size) > AT32_FLASH_END_ADDRESS)
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
 * @brief write data to flash.
 * @note this operation's units is word.
 * @note this operation must after erase. @see flash_erase.
 *
 * @param addr flash address
 * @param buf the write data buffer
 * @param size write bytes size
 *
 * @return result
 */
int at32_flash_write(rt_uint32_t addr, const rt_uint8_t *buf, rt_uint32_t size)
{
    rt_err_t result        = RT_EOK;
    rt_uint32_t end_addr   = addr + size;

    if (addr % 4 != 0)
    {
        LOG_E("write addr must be 4-byte alignment");
        return -RT_EINVAL;
    }

    if ((end_addr) > AT32_FLASH_END_ADDRESS)
    {
        LOG_E("write outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    flash_unlock();

    while (addr < end_addr)
    {
        if (flash_word_program(addr, *((rt_uint32_t *)buf)) == FLASH_OPERATE_DONE)
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

    flash_lock();

    if (result != RT_EOK)
    {
        return result;
    }

    return size;
}

/**
 * @brief erase data on flash .
 * @note this operation is irreversible.
 * @note this operation's units is different which on many chips.
 *
 * @param addr flash address
 * @param size erase bytes size
 *
 * @return result
 */
int at32_flash_erase(rt_uint32_t addr, rt_uint32_t size)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t end_addr = addr + size;
    rt_uint32_t page_addr = 0;

    flash_unlock();

    if ((end_addr) > AT32_FLASH_END_ADDRESS)
    {
        LOG_E("erase outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    while(addr < end_addr)
    {
        page_addr = get_page(addr);

        if(flash_sector_erase(page_addr) != FLASH_OPERATE_DONE)
        {
            result = -RT_ERROR;
            goto __exit;
        }

        addr += FLASH_PAGE_SIZE;
    }

    flash_lock();

__exit:
    if(result != RT_EOK)
    {
        return result;
    }

    return size;
}

#if defined(RT_USING_FAL)

static int fal_flash_read(long offset, rt_uint8_t *buf, rt_uint32_t size);
static int fal_flash_write(long offset, const rt_uint8_t *buf, rt_uint32_t size);
static int fal_flash_erase(long offset, rt_uint32_t size);

const struct fal_flash_dev at32_onchip_flash =
{
    "onchip_flash",
    AT32_FLASH_START_ADRESS,
    AT32_FLASH_SIZE,
    FLASH_PAGE_SIZE,
    {
        NULL,
        fal_flash_read,
        fal_flash_write,
        fal_flash_erase
    }
};

static int fal_flash_read(long offset, rt_uint8_t *buf, rt_uint32_t size)
{
    return at32_flash_read(at32_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_write(long offset, const rt_uint8_t *buf, rt_uint32_t size)
{
    return at32_flash_write(at32_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_erase(long offset, rt_uint32_t size)
{
    return at32_flash_erase(at32_onchip_flash.addr + offset, size);
}

#endif
#endif /* BSP_USING_ON_CHIP_FLASH */
