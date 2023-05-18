/*
 * File      : fal_flash_stm32l4_port.c
 * COPYRIGHT (C) 2012-2018, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-17     MurphyZhao   the first version
 */

#include <fal.h>

#ifdef FAL_FLASH_PORT_DRIVER_STM32L4
#include <stm32l4xx_hal.h>
#include "board.h"

// #define STM32L4_FLASH_DEBUG

#define FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define FLASH_END_ADDRESS      ((uint32_t)(0x08000000 + 512 * 1024))
#define FLASH_PAGE_NBPERBANK   128
#define FLASH_BANK_NUMBER      2

static int read(long offset, uint8_t *buf, size_t size)
{
    size_t i;
    uint32_t addr = stm32l4_onchip_flash.addr + offset;

    if ((addr + size) > FLASH_END_ADDRESS)
    {
        rt_kprintf("ERROR: read outrange flash size! addr is (0x%p)\n", (void*)(addr + size));
        return -1;
    }

    for (i = 0; i < size; i++, buf++, addr++)
    {
        *buf = *(uint8_t *) addr;
    }

    return size;
}

static int write(long offset, const uint8_t *buf, size_t size)
{
    size_t i, j;
    int8_t status = 0;
    uint64_t write_data = 0, temp_data = 0;
    uint32_t addr = stm32l4_onchip_flash.addr + offset;

    if ((addr + size) > FLASH_END_ADDRESS)
    {
        rt_kprintf("ERROR: write outrange flash size! addr is (0x%p)\n", (void*)(addr + size));
        return -1;
    }

    HAL_FLASH_Unlock();

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGSERR);

    if (size < 1)
    {
        return -1;
    }

    for (i = 0; i < size;)
    {
        if ((size - i) < 8)
        {
            for (j = 0; (size - i) > 0; i++, j++)
            {
                temp_data = *buf;
                write_data = (write_data) | (temp_data << 8*j);

                buf ++;
            }
        }
        else
        {
            for (j = 0; j < 8; j++, i++)
            {
                temp_data = *buf;
                write_data = (write_data) | (temp_data << 8*j);
                buf ++;
            }
        }

        /* write data */
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addr, write_data) == HAL_OK)
        {
            /* Check the written value */
            if (*(uint64_t*)addr != write_data)
            {
                rt_kprintf("ERROR: write data != read data\n");
                status = -1;
                goto exit;
            }
        }
        else
        {
            status = -1;
            goto exit;
        }
        
        temp_data = 0;
        write_data = 0;

        addr +=8;
    }

exit:
    HAL_FLASH_Lock();
    if (status != 0)
    {
        return status;
    }

    return size;
}

static int erase(long offset, size_t size)
{
    uint32_t NbrOfPages = 0;
    uint32_t PageError  = 0;
    HAL_StatusTypeDef status = HAL_OK;
    FLASH_EraseInitTypeDef pEraseInit;

    uint32_t addr = stm32l4_onchip_flash.addr + offset;

    if ((addr + size) > FLASH_END_ADDRESS)
    {
        rt_kprintf("ERROR: erase outrange flash size! addr is (0x%p)\n", (void*)(addr + size));
        return -1;
    }

    pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;   // FLASH_TYPEERASE_MASSERASE or FLASH_TYPEERASE_PAGES

    if (addr < 0x08040000) // bank1
    {
        pEraseInit.Banks = FLASH_BANK_1;
        pEraseInit.Page  = (addr - FLASH_START_ADRESS)/FLASH_PAGE_SIZE;  // Calculate the page where the start address is located
    }
    else // bank2
    {
        pEraseInit.Banks = FLASH_BANK_2;
        pEraseInit.Page  = (addr - FLASH_START_ADRESS)/FLASH_PAGE_SIZE + 128;
    }

    if (size%FLASH_PAGE_SIZE == 0)
        NbrOfPages = size/FLASH_PAGE_SIZE;            // Calculate the number of pages
    else
        NbrOfPages = size/FLASH_PAGE_SIZE + 1;        // Calculate the number of pages

    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGSERR);

    if ( pEraseInit.Page < 128 && (NbrOfPages + pEraseInit.Page) > 128 )
    {
        if ((NbrOfPages + pEraseInit.Page) > 256)
        {
            rt_kprintf("ERROR: erase outrange flash size!\n");
            goto exit;
        }

        pEraseInit.NbPages = 128 - pEraseInit.Page;

        status = HAL_FLASHEx_Erase(&pEraseInit, &PageError);
        if (status != HAL_OK)
            goto exit;
        
        pEraseInit.Banks   = FLASH_BANK_2;
        pEraseInit.Page    = 256;
        pEraseInit.NbPages = NbrOfPages - pEraseInit.NbPages;

        status = HAL_FLASHEx_Erase(&pEraseInit, &PageError);
        if (status != HAL_OK)
            goto exit;
    }
    else if (pEraseInit.Page < 128 && (NbrOfPages + pEraseInit.Page) <= 128)
    {
        pEraseInit.Banks   = FLASH_BANK_1;
        pEraseInit.NbPages = NbrOfPages;
        status = HAL_FLASHEx_Erase(&pEraseInit, &PageError);
        if (status != HAL_OK)
            goto exit;
    }
    else if (pEraseInit.Page >= 256 && (NbrOfPages + pEraseInit.Page <= 384))
    {
        pEraseInit.Banks   = FLASH_BANK_2;
        pEraseInit.NbPages = NbrOfPages;
        status = HAL_FLASHEx_Erase(&pEraseInit, &PageError);
        if (status != HAL_OK)
            goto exit;
    }
    else
    {
        rt_kprintf("ERROR: erase outrange flash size!\n");
    }

exit:
    HAL_FLASH_Lock();

#ifdef STM32L4_FLASH_DEBUG
    rt_kprintf("stm32l4xx erase finish!\n");
#endif

    return size;
}

const struct fal_flash_dev stm32l4_onchip_flash = { "onchip_flash", 0x08000000, (512 * 1024), 2048, {NULL, read, write, erase} };
#endif /* FAL_FLASH_PORT_DRIVER_STM32F2 */
