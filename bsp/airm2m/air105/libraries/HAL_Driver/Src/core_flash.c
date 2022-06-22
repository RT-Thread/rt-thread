/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "bl_inc.h"
#if 0
void CACHE_CleanAll(CACHE_TypeDef *Cache)
{
    while (Cache->CACHE_CS & CACHE_IS_BUSY);

    Cache->CACHE_REF = CACHE_REFRESH_ALLTAG;
    Cache->CACHE_REF |= CACHE_REFRESH;
    while ((Cache->CACHE_REF & CACHE_REFRESH));
}

/**
  * @brief  Flash Erase Sector.
  * @param  sectorAddress: The sector address to be erased
  * @retval FLASH Status:  The returned value can be: QSPI_STATUS_ERROR, QSPI_STATUS_OK
  */
uint8_t FLASH_EraseSector(uint32_t sectorAddress)
{
    uint8_t ret;

    __disable_irq();
    //__disable_fault_irq();

    ret = ROM_QSPI_EraseSector(NULL, sectorAddress);

    //__enable_fault_irq();
    __enable_irq();

    return ret;
}

/**
  * @brief  Flash Program Interface.
  * @param  addr:          specifies the address to be programmed.
  * @param  size:          specifies the size to be programmed.
  * @param  buffer:        pointer to the data to be programmed, need word aligned
  * @retval FLASH Status:  The returned value can be: QSPI_STATUS_ERROR, QSPI_STATUS_OK
  */
uint8_t FLASH_ProgramPage(uint32_t addr, uint32_t size, uint8_t *buffer)
{
    uint8_t ret;
    QSPI_CommandTypeDef cmdType;

    cmdType.Instruction = QUAD_INPUT_PAGE_PROG_CMD;
    cmdType.BusMode = QSPI_BUSMODE_114;
    cmdType.CmdFormat = QSPI_CMDFORMAT_CMD8_ADDR24_PDAT;

    __disable_irq();
    //__disable_fault_irq();

    ret = ROM_QSPI_ProgramPage(&cmdType, DMA_Channel_1, addr, size, buffer);

    //__enable_fault_irq();
    __enable_irq();

    return ret;
}


int Flash_EraseSector(uint32_t address, uint8_t NeedCheck)
{
    uint8_t buf[256];
    uint32_t i;
    uint8_t retry = 1;
    void *res;
    memset(buf, 0xff, 256);
BL_ERASESECTOR_AGAIN:
    FLASH_EraseSector(address);
    CACHE_CleanAll(CACHE);
    if (!NeedCheck) return ERROR_NONE;
    for(i = 0; i < 4096; i+=256)
    {
        res = memcmp(address + i, buf, 256);
        if (res)
        {
            DBG_INFO("%x", res);
            if (retry)
            {
                retry = 0;
                goto BL_ERASESECTOR_AGAIN;
            }
            else
            {
                return -1;
            }
        }
    }
    return 0;
}

int Flash_ProgramData(uint32_t address, uint32_t *Data, uint32_t Len, uint8_t NeedCheck)
{
    void *res;
    uint32_t size = (Len + (4 - 1)) & (~(4 - 1));
    if (size > 256)
    {
        size = 256;
    }
    FLASH_ProgramPage(address, size, Data);
    CACHE_CleanAll(CACHE);
    if (!NeedCheck) return ERROR_NONE;
    res = memcmp(address, Data, Len);
    if (res)
    {
        DBG_INFO("%x", res);
        FLASH_ProgramPage(address, size, Data);
        CACHE_CleanAll(CACHE);
        res = memcmp(address, Data, size);
        if (res)
        {
            DBG_INFO("%x", res);
            return -1;
        }
    }
    return 0;
}

#endif
