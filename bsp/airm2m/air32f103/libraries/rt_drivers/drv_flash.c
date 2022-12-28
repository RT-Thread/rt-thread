/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include <rtthread.h>
#include <board.h>

#ifdef BSP_USING_ON_CHIP_FLASH

#include "drv_flash.h"

#if defined(RT_USING_FAL)
#include "fal.h"
#endif


#define LOG_TAG                "drv.flash"
#include <drv_log.h>

/**
  * @brief  Gets the page of a given address
  * @param  addr: address of the flash memory
  * @retval The page of a given address
  */
static rt_uint32_t get_page(uint32_t addr)
{
    rt_uint32_t page = 0;

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
int air32_flash_read(rt_uint32_t addr, rt_uint8_t *buf, rt_size_t size)
{
    rt_size_t i;

    if ((addr + size) > AIR32_FLASH_END_ADDRESS)
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
int air32_flash_write(rt_uint32_t addr, const rt_uint8_t *buf, rt_size_t size)
{
    rt_err_t result        = RT_EOK;
    rt_uint32_t end_addr   = addr + size;

    if (addr % 4 != 0)
    {
        LOG_E("write addr must be 4-byte alignment");
        return -RT_EINVAL;
    }

    if ((end_addr) > AIR32_FLASH_END_ADDRESS)
    {
        LOG_E("write outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    FLASH_Unlock();

    while (addr < end_addr)
    {
        if (FLASH_ProgramWord(addr, *((rt_uint32_t *)buf)) == FLASH_COMPLETE)
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
int air32_flash_erase(rt_uint32_t addr, rt_size_t size)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t end_addr = addr + size;
    rt_uint32_t page_addr = 0;

    FLASH_Unlock();

    if ((end_addr) > AIR32_FLASH_END_ADDRESS)
    {
        LOG_E("erase outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    while(addr < end_addr)
    {
        page_addr = get_page(addr);

        if(FLASH_ErasePage(page_addr) != FLASH_COMPLETE)
        {
            result = -RT_ERROR;
            goto __exit;
        }

        addr += FLASH_PAGE_SIZE;
    }

        FLASH_Lock();

__exit:
    if(result != RT_EOK)
    {
        return result;
    }

    return size;
}

#if defined(RT_USING_FAL)

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_erase(long offset, size_t size);

/*fal_cfg.h use it*/
const struct fal_flash_dev air32_onchip_flash =
{
    "onchip_flash",
    AIR32_FLASH_START_ADRESS,
    AIR32_FLASH_SIZE,
    FLASH_PAGE_SIZE,
    {
        NULL,
        fal_flash_read,
        fal_flash_write,
        fal_flash_erase
    }
};

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size)
{
    return air32_flash_read(air32_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size)
{
    return air32_flash_write(air32_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_erase(long offset, size_t size)
{
    return air32_flash_erase(air32_onchip_flash.addr + offset, size);
}

#endif /* RT_USING_FAL */

#endif /* BSP_USING_ON_CHIP_FLASH */
