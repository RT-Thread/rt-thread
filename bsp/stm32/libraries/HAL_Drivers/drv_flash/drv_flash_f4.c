/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-5      SummerGift   first version
 */

#include "board.h"

#ifdef BSP_USING_ON_CHIP_FLASH
#include "drv_config.h"
#include "drv_flash.h"

#if defined(PKG_USING_FAL)
#include "fal.h"
#endif

//#define DRV_DEBUG
#define LOG_TAG                "drv.flash"
#include <drv_log.h>

/* Base address of the Flash sectors Bank 1 */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

/* Base address of the Flash sectors Bank 2 */
#define ADDR_FLASH_SECTOR_12     ((uint32_t)0x08100000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_13     ((uint32_t)0x08104000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_14     ((uint32_t)0x08108000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_15     ((uint32_t)0x0810C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_16     ((uint32_t)0x08110000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_17     ((uint32_t)0x08120000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_18     ((uint32_t)0x08140000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_19     ((uint32_t)0x08160000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_20     ((uint32_t)0x08180000) /* Base @ of Sector 8, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_21     ((uint32_t)0x081A0000) /* Base @ of Sector 9, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_22     ((uint32_t)0x081C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_23     ((uint32_t)0x081E0000) /* Base @ of Sector 11, 128 Kbytes */

/**
  * @brief  Gets the sector of a given address
  * @param  None
  * @retval The sector of a given address
  */
static rt_uint32_t GetSector(rt_uint32_t Address)
{
    rt_uint32_t sector = 0;

    if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
    {
        sector = FLASH_SECTOR_0;
    }
    else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
    {
        sector = FLASH_SECTOR_1;
    }
    else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
    {
        sector = FLASH_SECTOR_2;
    }
    else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
    {
        sector = FLASH_SECTOR_3;
    }
    else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
    {
        sector = FLASH_SECTOR_4;
    }
    else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
    {
        sector = FLASH_SECTOR_5;
    }
    else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
    {
        sector = FLASH_SECTOR_6;
    }
    else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
    {
        sector = FLASH_SECTOR_7;
    }
#if defined(FLASH_SECTOR_8)
    else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
    {
        sector = FLASH_SECTOR_8;
    }
#endif
#if defined(FLASH_SECTOR_9)
    else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
    {
        sector = FLASH_SECTOR_9;
    }
#endif
#if defined(FLASH_SECTOR_10)
    else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
    {
        sector = FLASH_SECTOR_10;
    }
#endif
#if defined(FLASH_SECTOR_11)
    else if((Address < ADDR_FLASH_SECTOR_12) && (Address >= ADDR_FLASH_SECTOR_11))
    {
        sector = FLASH_SECTOR_11;
    }
#endif
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
    else if((Address < ADDR_FLASH_SECTOR_13) && (Address >= ADDR_FLASH_SECTOR_12))
    {
        sector = FLASH_SECTOR_12;
    }
    else if((Address < ADDR_FLASH_SECTOR_14) && (Address >= ADDR_FLASH_SECTOR_13))
    {
        sector = FLASH_SECTOR_13;
    }
    else if((Address < ADDR_FLASH_SECTOR_15) && (Address >= ADDR_FLASH_SECTOR_14))
    {
        sector = FLASH_SECTOR_14;
    }
    else if((Address < ADDR_FLASH_SECTOR_16) && (Address >= ADDR_FLASH_SECTOR_15))
    {
        sector = FLASH_SECTOR_15;
    }
    else if((Address < ADDR_FLASH_SECTOR_17) && (Address >= ADDR_FLASH_SECTOR_16))
    {
        sector = FLASH_SECTOR_16;
    }
    else if((Address < ADDR_FLASH_SECTOR_18) && (Address >= ADDR_FLASH_SECTOR_17))
    {
        sector = FLASH_SECTOR_17;
    }
    else if((Address < ADDR_FLASH_SECTOR_19) && (Address >= ADDR_FLASH_SECTOR_18))
    {
        sector = FLASH_SECTOR_18;
    }
    else if((Address < ADDR_FLASH_SECTOR_20) && (Address >= ADDR_FLASH_SECTOR_19))
    {
        sector = FLASH_SECTOR_19;
    }
    else if((Address < ADDR_FLASH_SECTOR_21) && (Address >= ADDR_FLASH_SECTOR_20))
    {
        sector = FLASH_SECTOR_20;
    }
    else if((Address < ADDR_FLASH_SECTOR_22) && (Address >= ADDR_FLASH_SECTOR_21))
    {
        sector = FLASH_SECTOR_21;
    }
    else if((Address < ADDR_FLASH_SECTOR_23) && (Address >= ADDR_FLASH_SECTOR_22))
    {
        sector = FLASH_SECTOR_22;
    }
    else /* (Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_23) */
    {
        sector = FLASH_SECTOR_23;
    }
#endif
    return sector;
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
int stm32_flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size)
{
    size_t i;

    if ((addr + size) > STM32_FLASH_END_ADDRESS)
    {
        LOG_E("read outrange flash size! addr is (0x%p)", (void*)(addr + size));
        return -1;
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
int stm32_flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size)
{
    rt_err_t result      = RT_EOK;
    rt_uint32_t end_addr = addr + size;
    rt_uint32_t written_size = 0;
    rt_uint32_t write_size = 0;

    if ((end_addr) > STM32_FLASH_END_ADDRESS)
    {
        LOG_E("write outrange flash size! addr is (0x%p)", (void*)(addr + size));
        return -RT_EINVAL;
    }

    if (size < 1)
    {
        return -RT_EINVAL;
    }

    HAL_FLASH_Unlock();

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

    while (written_size < size)
    {
        if (((addr + written_size) % 4 == 0) && (size - written_size >= 4))
        {
            if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr + written_size, *((rt_uint32_t *)(buf + written_size))) == HAL_OK)
            {
                if (*(rt_uint32_t *)(addr + written_size) != *(rt_uint32_t *)(buf + written_size))
                {
                    result = -RT_ERROR;
                    break;
                }
            }
            else
            {
                result = -RT_ERROR;
                break;
            }
            write_size = 4;
        }
        else if (((addr + written_size) % 2 == 0) && (size - written_size >= 2))
        {
            if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addr + written_size, *((rt_uint16_t *)(buf + written_size))) == HAL_OK)
            {
                if (*(rt_uint16_t *)(addr + written_size) != *(rt_uint16_t *)(buf + written_size))
                {
                    result = -RT_ERROR;
                    break;
                }
            }
            else
            {
                result = -RT_ERROR;
                break;
            }
            write_size = 2;
        }
        else
        {
            if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, addr + written_size, *((rt_uint8_t *)(buf + written_size))) == HAL_OK)
            {
                if (*(rt_uint8_t *)(addr + written_size) != *(rt_uint8_t *)(buf + written_size))
                {
                    result = -RT_ERROR;
                    break;
                }
            }
            else
            {
                result = -RT_ERROR;
                break;
            }
            write_size = 1;
        }

        written_size += write_size;
    }

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
    rt_uint32_t FirstSector = 0, NbOfSectors = 0;
    rt_uint32_t SECTORError = 0;

    if ((addr + size) > STM32_FLASH_END_ADDRESS)
    {
        LOG_E("ERROR: erase outrange flash size! addr is (0x%p)\n", (void*)(addr + size));
        return -RT_EINVAL;
    }

    if (size < 1)
    {
        return -RT_EINVAL;
    }

    /*Variable used for Erase procedure*/
    FLASH_EraseInitTypeDef EraseInitStruct;

    /* Unlock the Flash to enable the flash control register access */
    HAL_FLASH_Unlock();

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

    /* Get the 1st sector to erase */
    FirstSector = GetSector(addr);
    /* Get the number of sector to erase from 1st sector*/
    NbOfSectors = GetSector(addr + size - 1) - FirstSector + 1;
    /* Fill EraseInit structure*/
    EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector        = FirstSector;
    EraseInitStruct.NbSectors     = NbOfSectors;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, (uint32_t *)&SECTORError) != HAL_OK)
    {
        result = -RT_ERROR;
        goto __exit;
    }

__exit:
    HAL_FLASH_Lock();

    if (result != RT_EOK)
    {
        return result;
    }

    LOG_D("erase done: addr (0x%p), size %d", (void*)addr, size);
    return size;
}

#if defined(PKG_USING_FAL)

static int fal_flash_read_16k(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_read_64k(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_read_128k(long offset, rt_uint8_t *buf, size_t size);

static int fal_flash_write_16k(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_write_64k(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_write_128k(long offset, const rt_uint8_t *buf, size_t size);

static int fal_flash_erase_16k(long offset, size_t size);
static int fal_flash_erase_64k(long offset, size_t size);
static int fal_flash_erase_128k(long offset, size_t size);

const struct fal_flash_dev stm32_onchip_flash_16k = { "onchip_flash_16k", STM32_FLASH_START_ADRESS_16K, FLASH_SIZE_GRANULARITY_16K, (16 * 1024), {NULL, fal_flash_read_16k, fal_flash_write_16k, fal_flash_erase_16k} };
const struct fal_flash_dev stm32_onchip_flash_64k = { "onchip_flash_64k", STM32_FLASH_START_ADRESS_64K, FLASH_SIZE_GRANULARITY_64K, (64 * 1024), {NULL, fal_flash_read_64k, fal_flash_write_64k, fal_flash_erase_64k} };
const struct fal_flash_dev stm32_onchip_flash_128k = { "onchip_flash_128k", STM32_FLASH_START_ADRESS_128K, FLASH_SIZE_GRANULARITY_128K, (128 * 1024), {NULL, fal_flash_read_128k, fal_flash_write_128k, fal_flash_erase_128k} };

static int fal_flash_read_16k(long offset, rt_uint8_t *buf, size_t size)
{
    return stm32_flash_read(stm32_onchip_flash_16k.addr + offset, buf, size);
}
static int fal_flash_read_64k(long offset, rt_uint8_t *buf, size_t size)
{
    return stm32_flash_read(stm32_onchip_flash_64k.addr + offset, buf, size);
}
static int fal_flash_read_128k(long offset, rt_uint8_t *buf, size_t size)
{
    return stm32_flash_read(stm32_onchip_flash_128k.addr + offset, buf, size);
}

static int fal_flash_write_16k(long offset, const rt_uint8_t *buf, size_t size)
{
    return stm32_flash_write(stm32_onchip_flash_16k.addr + offset, buf, size);
}
static int fal_flash_write_64k(long offset, const rt_uint8_t *buf, size_t size)
{
    return stm32_flash_write(stm32_onchip_flash_64k.addr + offset, buf, size);
}
static int fal_flash_write_128k(long offset, const rt_uint8_t *buf, size_t size)
{
    return stm32_flash_write(stm32_onchip_flash_128k.addr + offset, buf, size);
}

static int fal_flash_erase_16k(long offset, size_t size)
{
    return stm32_flash_erase(stm32_onchip_flash_16k.addr + offset, size);
}
static int fal_flash_erase_64k(long offset, size_t size)
{
    return stm32_flash_erase(stm32_onchip_flash_64k.addr + offset, size);
}
static int fal_flash_erase_128k(long offset, size_t size)
{
    return stm32_flash_erase(stm32_onchip_flash_128k.addr + offset, size);
}

#endif
#endif /* BSP_USING_ON_CHIP_FLASH */
