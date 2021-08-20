/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-5      SummerGift   first version
 * 2019-3-2       jinsheng     add Macro judgment
 * 2020-1-6       duminmin     support single bank mode
 * 2020-5-17      yufanyufan77 support support H7
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
#define ADDR_FLASH_SECTOR_0     ((rt_uint32_t)0x08000000) /* Base address of Sector 0, 128 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((rt_uint32_t)0x08020000) /* Base address of Sector 1, 128 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((rt_uint32_t)0x08040000) /* Base address of Sector 2, 128 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((rt_uint32_t)0x08060000) /* Base address of Sector 3, 128 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((rt_uint32_t)0x08080000) /* Base address of Sector 4, 128 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((rt_uint32_t)0x080A0000) /* Base address of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((rt_uint32_t)0x080C0000) /* Base address of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((rt_uint32_t)0x080E0000) /* Base address of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((rt_uint32_t)0x08100000) /* Base address of Sector 8, 128 Kbytes */

#define FLASH_SECTOR_0             0U       /* Sector Number 0   */
#define FLASH_SECTOR_1             1U       /* Sector Number 1   */
#define FLASH_SECTOR_2             2U       /* Sector Number 2   */
#define FLASH_SECTOR_3             3U       /* Sector Number 3   */
#define FLASH_SECTOR_4             4U       /* Sector Number 4   */
#define FLASH_SECTOR_5             5U       /* Sector Number 5   */
#define FLASH_SECTOR_6             6U       /* Sector Number 6   */
#define FLASH_SECTOR_7             7U       /* Sector Number 7   */
/**
  * @brief  Gets the sector of a given address
  * @param  addr flash address
  * @param  flash bank
  * @param  flash sector
  * @retval The sector of a given address
  */
static void GetSector(rt_uint32_t Address,uint32_t* bank,uint32_t* sector)
{
#if defined (FLASH_OPTCR_nDBANK)
    FLASH_OBProgramInitTypeDef OBInit;
    uint32_t nbank = 0;

    /* get duel bank ability:nDBANK(Bit29) */
    HAL_FLASHEx_OBGetConfig(&OBInit);
    nbank = ((OBInit.USERConfig & 0x20000000U) >> 29);
    /* 1:single bank mode */
    if (1 == nbank)
    {  
        if ((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
        {
            sector = FLASH_SECTOR_0;
        }
        else if ((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
        {
            sector = FLASH_SECTOR_1;
        }
        else if ((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
        {
            sector = FLASH_SECTOR_2;
        }
        else if ((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
        {
            sector = FLASH_SECTOR_3;
        }
        else if ((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
        {
            sector = FLASH_SECTOR_4;
        }
        else if ((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
        {
            sector = FLASH_SECTOR_5;
        }
        else if ((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
        {
            sector = FLASH_SECTOR_6;
        }
        else if ((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
        {
            sector = FLASH_SECTOR_7;
        }
        else if ((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
        {
            sector = FLASH_SECTOR_8;
        }
        else if ((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
        {
            sector = FLASH_SECTOR_9;
        }
        else if ((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
        {
            sector = FLASH_SECTOR_10;
        }
        else 
        {
            sector = FLASH_SECTOR_11;
        }
    }
    else  /* 0:dual bank mode */
    {
        LOG_E("rtthread doesn't support duel bank mode yet!");
        RT_ASSERT(0);
    }
#else /* no dual bank ability */	
    *sector = (Address&0xffffff)/FLASH_SIZE_GRANULARITY_128K;
    if(*sector>7)
    {
        *bank = FLASH_BANK_1;
        *sector = *sector/2;
    }
    else
    {
        *bank = FLASH_BANK_2;
    }
#endif
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
        LOG_E("read outrange flash size! addr is (0x%p)", (void *)(addr + size));
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
    rt_uint32_t bank = addr/ADDR_FLASH_SECTOR_8;;

    if ((end_addr) > STM32_FLASH_END_ADDRESS)
    {
        LOG_E("write outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    if (size < 1)
    {
        return -RT_EINVAL;
    }

    /* Unlock the Flash to enable the flash control register access */
    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR );

    for (size_t i = 0; i < size/32; i++, addr+=32, buf+=32)
    {
        /* write data to flash */
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, addr,  (uint64_t)((uint32_t)buf)) == HAL_OK)
        {
            if (*(rt_uint8_t *)addr != *buf)
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
    rt_uint32_t bank = 0;

    if ((addr + size) > STM32_FLASH_END_ADDRESS)
    {
        LOG_E("ERROR: erase outrange flash size! addr is (0x%p)\n", (void *)(addr + size));
        return -RT_EINVAL;
    }

    /*Variable used for Erase procedure*/
    FLASH_EraseInitTypeDef EraseInitStruct;

    /* Unlock the Flash to enable the flash control register access */
    HAL_FLASH_Unlock();

    /* Get the 1st sector to erase */
    GetSector(addr,&bank,&FirstSector);
    /* Get the number of sector to erase from 1st sector */
    GetSector(addr + size,0,&NbOfSectors);
    NbOfSectors = NbOfSectors - FirstSector + 1;
    /* Fill EraseInit structure */
    EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector        = FirstSector;
    EraseInitStruct.NbSectors     = NbOfSectors;
    EraseInitStruct.Banks         = bank;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
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

    LOG_D("erase done: addr (0x%p), size %d", (void *)addr, size);
    return size;
}

#if defined(PKG_USING_FAL)
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
