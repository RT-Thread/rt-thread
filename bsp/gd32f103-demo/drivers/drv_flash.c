#include <rtconfig.h>
#include <rtdef.h>
#include <board.h>

#ifdef BSP_USING_ONCHIP_FLASH
#include "drv_flash.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME "drv_flash"
#define DBG_LEVEL DBG_LOG
#include <rtdbg.h>

#define GD32_FLASH_END_ADDRESS (FLASH_BASE + (FMC_SIZE*1024))
#define BANK0_PAGESIZE (2*1024)

int32_t GetPageStartAddr(uint32_t addr)
{
    return (FLASH_BASE + (BANK0_PAGESIZE * ((addr - FLASH_BASE) / BANK0_PAGESIZE)));
}

int32_t fmc_flash_write(uint32_t addr, const uint8_t *dataAddr, size_t size)
{
    uint32_t pageStartAddr;
    //uint32_t pageEndAddr;
    uint32_t index, writeCount = 0;
    uint32_t addrTemp = addr;
    uint32_t *pDatatemp;
    fmc_state_enum stateTemp;

    if (size <= 0 || (size % 4 != 0) || (addr % 4 != 0))
    {
        LOG_W("fmc size\%4 != 0 OR addr\%4 != 0");
        return 0;
    }

    if ((addr < FLASH_BASE) || (addr + size) > (FLASH_BASE + (FMC_SIZE * 1024)))
    {
        LOG_E("write outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return 0;
    }

    fmc_unlock();
    fmc_bank0_unlock();
    do
    {
        stateTemp = fmc_word_program(addrTemp, *((rt_uint32_t *)dataAddr));
        if (stateTemp != FMC_READY)
        {
            LOG_E("FMC_READY fail.");
            return 0;
        }
        addrTemp += 4;
        dataAddr += 4;
        writeCount += 4;
    }
    while (writeCount < size);

    fmc_lock();
    fmc_bank0_lock();

    return writeCount;
}


int32_t gd32_flash_read(uint32_t addr, uint8_t *buf, size_t size)
{
    size_t i;

    if ((addr + size) > GD32_FLASH_END_ADDRESS)
    {
        LOG_E("read outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    for (i = 0; i < size; i++, buf++, addr++)
    {
        *buf = *(uint8_t *) addr;
    }

    return size;
}


int32_t gd32_flash_write(uint32_t addr, const uint8_t *buf, size_t size)
{
    rt_err_t result        = RT_EOK;
    rt_uint32_t end_addr   = addr + size;

    if (addr % 4 != 0)
    {
        LOG_E("write addr must be 4-byte alignment");
        return -RT_EINVAL;
    }

    if ((end_addr) > GD32_FLASH_END_ADDRESS)
    {
        LOG_E("write outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    result = fmc_flash_write(addr, buf, size) == 0 ? RT_ERROR : RT_EOK;

    if (result != RT_EOK)
    {
        return result;
    }

    return size;
}

int32_t gd32_flash_erase(uint32_t addr, size_t size)
{
    rt_uint32_t pageStartAddr, pageEndAddr;
    if (size <= 0)
    {
        return size;
    }

    fmc_unlock();
    fmc_bank0_unlock();
    pageStartAddr = GetPageStartAddr(addr);
    do
    {
        pageStartAddr = GetPageStartAddr(pageStartAddr);
        pageEndAddr = (pageStartAddr + BANK0_PAGESIZE - 1);
        fmc_page_erase(pageStartAddr);
        pageStartAddr += BANK0_PAGESIZE;
    }
    while ((pageEndAddr - addr + 1) < size);
    fmc_lock();
    fmc_bank0_lock();
    return size;
}


#endif //BSP_USING_ONCHIP_FLASH
