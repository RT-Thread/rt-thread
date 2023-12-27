/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-5      SummerGift   first version
 * 2019-3-2       jinsheng     add Macro judgment
 * 2020-1-6       duminmin     support single bank mode
 * 2020-5-17      yufanyufan77 support support H7
 * 2021-3-3       zhuyf233     fix some bugs
 */

#include <rtconfig.h>
#include <rtdef.h>

#ifdef BSP_USING_ON_CHIP_FLASH
#include "drv_config.h"
#include "drv_flash.h"
#include <board.h>

#if defined(RT_USING_FAL)
#include "fal.h"
#endif

//#define DRV_DEBUG
#define LOG_TAG                "drv.flash"
#include <drv_log.h>

/**
 * Read data from flash.
 * @note This operation's units is word.
 *
 * @param addr flash address
 * @param buf buffer to store read data
 * @param size read bytes size
 *
 * @retval The length of bytes that have been read
 */
int stm32_flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size)
{
    size_t i;

    if ((addr + size - 1) > FLASH_END)
    {
        LOG_E("read outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_ERROR;
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
 * @return The length of bytes that have been written
 */
int stm32_flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size)
{
    rt_err_t result      = RT_EOK;
    rt_uint32_t end_addr = addr + size - 1, write_addr;
    rt_uint32_t write_granularity = FLASH_NB_32BITWORD_IN_FLASHWORD * 4;
    rt_uint32_t write_size = write_granularity;
    rt_uint8_t write_buffer[32] = {0};

    if ((end_addr) > FLASH_END)
    {
        LOG_E("write outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    if(addr % 32 != 0)
    {
        LOG_E("write addr must be 32-byte alignment");
        return -RT_EINVAL;
    }

    if (size < 1)
    {
        return -RT_EINVAL;
    }

    HAL_FLASH_Unlock();
    write_addr = (uint32_t)buf;
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR);
    while (addr < end_addr)
    {
        if(end_addr - addr + 1 < write_granularity)
        {
            write_size = end_addr - addr + 1;
            for(size_t i = 0; i < write_size; i++)
            {
                write_buffer[i] = *((uint8_t *)(write_addr + i));
            }
            write_addr = (uint32_t)((rt_uint32_t *)write_buffer);
        }
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, addr, write_addr) == HAL_OK)
        {
            for(rt_uint8_t i = 0; i < write_size; i++)
            {
                if (*(rt_uint8_t *)(addr + i) != *(rt_uint8_t *)(write_addr + i))
                {
                    result = -RT_ERROR;
                    goto __exit;
                }
            }
            addr += write_granularity;
            write_addr  += write_granularity;
        }
        else
        {
            result = -RT_ERROR;
            goto __exit;
        }
    }

__exit:
    HAL_FLASH_Lock();

    if (result != RT_EOK)
    {
        return result;
    }

    return size;
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
int stm32_flash_erase(rt_uint32_t addr, size_t size)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t SECTORError = 0;

    if ((addr + size - 1) > FLASH_END)
    {
        LOG_E("ERROR: erase outrange flash size! addr is (0x%p)\n", (void *)(addr + size));
        return -RT_EINVAL;
    }

    rt_uint32_t addr_bank1 = 0;
    rt_uint32_t size_bank1 = 0;
#ifdef FLASH_BANK_2
    rt_uint32_t addr_bank2 = 0;
    rt_uint32_t size_bank2 = 0;
#endif

    if((addr + size) < FLASH_BANK2_BASE)
    {
        addr_bank1 = addr;
        size_bank1 = size;
#ifdef FLASH_BANK_2
        size_bank2 = 0;
#endif
    }
    else if(addr >= FLASH_BANK2_BASE)
    {
        size_bank1 = 0;
#ifdef FLASH_BANK_2
        addr_bank2 = addr;
        size_bank2 = size;
#endif
    }
    else
    {
        addr_bank1 = addr;
        size_bank1 = FLASH_BANK2_BASE - addr_bank1;
#ifdef FLASH_BANK_2
        addr_bank2 = FLASH_BANK2_BASE;
        size_bank2 = addr + size - FLASH_BANK2_BASE;
#endif
    }

    /*Variable used for Erase procedure*/
    FLASH_EraseInitTypeDef EraseInitStruct;
    /* Unlock the Flash to enable the flash control register access */
    HAL_FLASH_Unlock();
    EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
    SCB_DisableDCache();

    if(size_bank1)
    {
        EraseInitStruct.Sector    = (addr_bank1 - FLASH_BANK1_BASE) / FLASH_SECTOR_SIZE;
        EraseInitStruct.NbSectors = (addr_bank1 + size_bank1 -1 - FLASH_BANK1_BASE) / FLASH_SECTOR_SIZE - EraseInitStruct.Sector + 1;
        EraseInitStruct.Banks = FLASH_BANK_1;
        if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
        {
            result = -RT_ERROR;
            goto __exit;
        }
    }

#ifdef FLASH_BANK_2
    if(size_bank2)
    {
        EraseInitStruct.Sector    = (addr_bank2 - FLASH_BANK2_BASE) / FLASH_SECTOR_SIZE;
        EraseInitStruct.NbSectors = (addr_bank2 + size_bank2 -1 - FLASH_BANK2_BASE) / FLASH_SECTOR_SIZE - EraseInitStruct.Sector + 1;
        EraseInitStruct.Banks = FLASH_BANK_2;
        if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
        {
            result = -RT_ERROR;
            goto __exit;
        }
    }
#endif

__exit:

    SCB_EnableDCache();
    HAL_FLASH_Lock();

    if (result != RT_EOK)
    {
        return result;
    }

    LOG_D("erase done: addr (0x%p), size %d", (void *)addr, size);
    return size;
}

#if defined(RT_USING_FAL)
static int fal_flash_read_128k(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_write_128k(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_erase_128k(long offset, size_t size);
const struct fal_flash_dev stm32_onchip_flash_128k = { "onchip_flash_128k", STM32_FLASH_START_ADRESS, FLASH_SIZE_GRANULARITY_128K, (128 * 1024), {NULL, fal_flash_read_128k, fal_flash_write_128k, fal_flash_erase_128k} };

static int fal_flash_read_128k(long offset, rt_uint8_t *buf, size_t size)
{
    return stm32_flash_read(stm32_onchip_flash_128k.addr + offset, buf, size);
}
static int fal_flash_write_128k(long offset, const rt_uint8_t *buf, size_t size)
{
    return stm32_flash_write(stm32_onchip_flash_128k.addr + offset, buf, size);
}

static int fal_flash_erase_128k(long offset, size_t size)
{
    return stm32_flash_erase(stm32_onchip_flash_128k.addr + offset, size);
}

#endif
#endif /* BSP_USING_ON_CHIP_FLASH */
