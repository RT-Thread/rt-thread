/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-10-19     ChuShicheng       first version
 */
#include "drv_flash.h"
#include "board.h"
#include "hardware/flash.h"

#ifdef BSP_USING_ON_CHIP_FLASH

#define DBG_LEVEL DBG_LOG
#define LOG_TAG  "DRV.FLASH"
#include <rtdbg.h>

#define FLASH_SIZE           2 * 1024 * 1024
#define FLASH_START_ADRESS   0x0000000

int _flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size)
{
    rt_memcpy(buf, (const void *)(XIP_BASE + addr), size);

    return size;
}

int _flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size)
{
    if (addr % FLASH_PAGE_SIZE != 0)
    {
        LOG_E("write addr must be %d-byte alignment", FLASH_PAGE_SIZE);
        return -RT_EINVAL;
    }

    if (size % FLASH_PAGE_SIZE != 0)
    {
        LOG_E("write size must be %d-byte alignment", FLASH_PAGE_SIZE);
        return -RT_EINVAL;
    }

    flash_range_program(addr, buf, size);

    return size;
}

int _flash_erase(rt_uint32_t addr, size_t size)
{
    if(size % FLASH_SECTOR_SIZE)
    {
        LOG_E("erase size must be %d-byte alignment", FLASH_SECTOR_SIZE);
    }

    flash_range_erase(addr, size);

    return size;
}

#ifdef RT_USING_FAL

#include "fal.h"

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_erase(long offset, size_t size);

const struct fal_flash_dev _onchip_flash =
{
    "onchip_flash",
    FLASH_START_ADRESS,
    FLASH_SIZE,
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
