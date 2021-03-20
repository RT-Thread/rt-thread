/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-29     supperthomas first version
 */

#include "board.h"
#include <nrfx.h>
#include "nrfx_nvmc.h"

#ifdef BSP_USING_ON_CHIP_FLASH

#if defined(PKG_USING_FAL)
#include "fal.h"
#endif

#include <rtdbg.h>
#define LOG_TAG                "drv.flash"



/**
  * @brief  Gets the page of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The page of a given address
  */
static uint32_t GetPage(uint32_t Addr)
{
    uint32_t page = 0;
    if (Addr < (MCU_FLASH_START_ADDRESS + MCU_FLASH_SIZE))
    {
        page = (Addr - MCU_FLASH_START_ADDRESS) / MCU_FLASH_PAGE_SIZE;
    }
    else
    {
        return 0xffffffff;
    }
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
int mcu_flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size)
{

    size_t i;

    if ((addr + size) > MCU_FLASH_END_ADDRESS)
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
int mcu_flash_write(rt_uint32_t addr, const uint8_t *buf, size_t size)
{
    if ((addr + size) > MCU_FLASH_END_ADDRESS)
    {
        LOG_E("ERROR: write outrange flash size! addr is (0x%p)\n", (void *)(addr + size));
        return -RT_EINVAL;
    }


    if (addr % 4 != 0)
    {
        LOG_E("write addr should be 4-byte alignment");
        //4byte write
        //else byts
        return -RT_EINVAL;
    }

    if (size < 1)
    {
        return -RT_ERROR;
    }
    if (size % 4 != 0)
    {
        nrfx_nvmc_bytes_write(addr, buf, size);
        return size;
    }
    else
    {
        nrfx_nvmc_words_write(addr, buf, size / 4);
        return size;
    }

}

/**
 * Erase data on flash.
 * @note This operation is irreversible.
 * @note This operation's units is different which on many chips.
 *
 * @param addr flash address
 * @param size erase bytes size
 *
 * @return result
 */
int mcu_flash_erase(rt_uint32_t addr, size_t size)
{
    nrfx_err_t result = RT_EOK;

    uint32_t FirstPage = 0, NbOfPages = 0;

    if ((addr + size) > MCU_FLASH_END_ADDRESS)
    {
        LOG_E("ERROR: erase outrange flash size! addr is (0x%p)\n", (void *)(addr + size));
        return -RT_EINVAL;
    }

    FirstPage = GetPage(addr);
    NbOfPages = GetPage(addr + size - 1) - FirstPage + 1;

    for (int i = 0; i < NbOfPages ; i++)
    {
        result = nrfx_nvmc_page_erase((FirstPage + i) * MCU_FLASH_PAGE_SIZE);
        if (NRFX_SUCCESS != result)
        {
            LOG_E("ERROR: erase flash page %d ! error code  is (%x)\n", FirstPage + i, result);
            return -RT_EINVAL;
        }
    }
    LOG_D("erase done: addr (0x%p), size %d", (void *)addr, NbOfPages * MCU_FLASH_PAGE_SIZE);
    return size;
}

#if defined(PKG_USING_FAL)

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_erase(long offset, size_t size);

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size)
{
    return mcu_flash_read(mcu_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size)
{
    return mcu_flash_write(mcu_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_erase(long offset, size_t size)
{
    return mcu_flash_erase(mcu_onchip_flash.addr + offset, size);
}
const struct fal_flash_dev mcu_onchip_flash =
{
    .name       = ON_CHIP_FLASH_DEV_NAME,
    .addr       = MCU_FLASH_START_ADDRESS,
    .len        = MCU_FLASH_SIZE,
    .blk_size   = MCU_FLASH_PAGE_SIZE,
    .ops        = {NULL, fal_flash_read, fal_flash_write, fal_flash_erase},
    .write_gran = 8
};
#endif
#endif /* BSP_USING_ON_CHIP_FLASH */
