/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-04-08     wcx1024979076     first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_flash.h"

#ifdef BSP_USING_ON_CHIP_FLASH

#define DBG_LEVEL DBG_LOG
#define LOG_TAG  "DRV.FLASH"
#include <rtdbg.h>

#define BFLB_FLASH_START_ADRESS 0x0000000
#define BFLB_FLASH_END_ADDRESS  0x1000000
#define BFLB_FLASH_SIZE         16 * 1024 * 1024
#define BFLB_FLASH_PAGE_SIZE    4 * 1024

int _flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size)
{
    rt_err_t result = RT_EOK;

    if ((addr + size) > BFLB_FLASH_END_ADDRESS)
    {
        LOG_E("read outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    result = bflb_flash_read(addr - BFLB_FLASH_START_ADRESS, buf, size);

    if(result != RT_EOK)
    {
        LOG_E("READ ERROR result = %d, addr = %d, addr1 = %d, len = %d", result, addr, addr - BFLB_FLASH_START_ADRESS, size);
        return -RT_ERROR;
    }
    else
    {
        return size;
    }
}

int _flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size)
{
    rt_err_t result        = RT_EOK;
    rt_uint32_t end_addr   = addr + size;

    if (addr % 4 != 0)
    {
        LOG_E("write addr must be 4-byte alignment");
        return -RT_EINVAL;
    }

    if ((end_addr) > BFLB_FLASH_END_ADDRESS)
    {
        LOG_E("write outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    result = bflb_flash_write(addr - BFLB_FLASH_START_ADRESS, buf, size);

    if(result != RT_EOK)
    {
        LOG_E("WRITE ERROR result = %d, addr = %d, addr1 = %d, len = %d", result, addr,  addr - BFLB_FLASH_START_ADRESS, size);
        return -RT_ERROR;
    }
    else
    {
        return size;
    }
}

int _flash_erase(rt_uint32_t addr, size_t size)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t end_addr = addr + size;
    rt_uint32_t page_addr = 0;

    if ((end_addr) > BFLB_FLASH_END_ADDRESS)
    {
        LOG_E("erase outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    result = bflb_flash_erase(addr - BFLB_FLASH_START_ADRESS, size);

    if (result != RT_EOK)
    {
        LOG_E("ERASE ERROR result = %d, addr = %d, addr1 = %d, size = %d", result, addr,  addr - BFLB_FLASH_START_ADRESS, size);
        return -RT_ERROR;
    }
    else
    {
        return size;
    }
}

#ifdef RT_USING_FAL

#include "fal.h"

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_erase(long offset, size_t size);

const struct fal_flash_dev _onchip_flash =
{
    "bflb_onchip",
    BFLB_FLASH_START_ADRESS,
    BFLB_FLASH_SIZE,
    BFLB_FLASH_PAGE_SIZE,
    {
        NULL,
        fal_flash_read,
        fal_flash_write,
        fal_flash_erase
    }
};

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size)
{
    return _flash_read(_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size)
{
    return _flash_write(_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_erase(long offset, size_t size)
{
    return _flash_erase(_onchip_flash.addr + offset, size);
}

static int rt_hw_on_chip_flash_init(void)
{
    fal_init();
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_on_chip_flash_init);

#endif /* RT_USING_FAL */
#endif /* BSP_USING_ON_CHIP_FLASH */
