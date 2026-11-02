/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-08-06     li.mengmeng      implement for N32H47x/48x
 */

#include <rtconfig.h>
#include <rtthread.h>

#ifdef BSP_USING_ON_CHIP_FLASH

#include <board.h>
#include "drv_flash_h47x_48x.h"
#include "n32h47x_48x_flash.h"
#include "n32h47x_48x_rcc.h"

#ifdef RT_USING_FAL
#include <fal.h>
#endif

#define LOG_TAG "drv.flash"
#include <drv_log.h>

#define N32_FLASH_PAGE_SIZE    ((rt_uint32_t)0x2000U)
#define N32_FLASH_PROGRAM_SIZE ((rt_uint32_t)0x0008U)

static struct rt_mutex _flash_mutex;

static rt_bool_t n32_flash_range_is_valid(rt_uint32_t addr, size_t size)
{
    if ((size == 0U) || (addr < N32_FLASH_START_ADRESS) ||
        (addr >= N32_FLASH_END_ADDRESS))
    {
        return RT_FALSE;
    }

    if (size > (size_t)(N32_FLASH_END_ADDRESS - addr))
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

static rt_err_t n32_flash_prepare(void)
{
    RCC_EnableHsi(ENABLE);
    if (RCC_WaitHsiStable() != SUCCESS)
    {
        LOG_E("HSI is not ready");
        return -RT_ERROR;
    }

    FLASH_Unlock();
    if (Flash_GetLockStatus() != RESET)
    {
        LOG_E("unlock failed");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static int n32_flash_lock_take(void)
{
    if (rt_mutex_take(&_flash_mutex, RT_WAITING_FOREVER) != RT_EOK)
    {
        return -RT_EBUSY;
    }

    return RT_EOK;
}

int n32_flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size)
{
    int result;

    if ((buf == RT_NULL) || !n32_flash_range_is_valid(addr, size))
    {
        LOG_E("invalid read: addr=0x%08x, size=%u", addr, (unsigned int)size);
        return -RT_EINVAL;
    }

    result = n32_flash_lock_take();
    if (result != RT_EOK)
    {
        return result;
    }

    rt_memcpy(buf, (const void *)addr, size);
    rt_mutex_release(&_flash_mutex);

    return (int)size;
}

int n32_flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size)
{
    FLASH_STS status;
    rt_uint32_t data[2];
    rt_uint32_t write_addr;
    size_t offset;
    size_t i;
    int result;

    if ((buf == RT_NULL) || !n32_flash_range_is_valid(addr, size) ||
        ((addr & (N32_FLASH_PROGRAM_SIZE - 1U)) != 0U) ||
        ((size & (N32_FLASH_PROGRAM_SIZE - 1U)) != 0U))
    {
        LOG_E("invalid write: addr=0x%08x, size=%u", addr, (unsigned int)size);
        return -RT_EINVAL;
    }

    result = n32_flash_lock_take();
    if (result != RT_EOK)
    {
        return result;
    }

    for (i = 0; i < size; i++)
    {
        if (*(const rt_uint8_t *)(addr + i) != 0xFFU)
        {
            LOG_E("write target is not erased: addr=0x%08x", addr + (rt_uint32_t)i);
            result = -RT_ERROR;
            goto __exit;
        }
    }

    result = n32_flash_prepare();
    if (result != RT_EOK)
    {
        goto __exit;
    }

    for (offset = 0; offset < size; offset += N32_FLASH_PROGRAM_SIZE)
    {
        write_addr = addr + (rt_uint32_t)offset;
        rt_memcpy(data, buf + offset, sizeof(data));

        status = FLASH_ProgramdoubleWord(write_addr, data[0], data[1]);
        if (status != FLASH_EOP)
        {
            LOG_E("program failed: addr=0x%08x, status=%d", write_addr, status);
            result = -RT_ERROR;
            goto __lock_exit;
        }

        if (rt_memcmp((const void *)write_addr, buf + offset,
                      N32_FLASH_PROGRAM_SIZE) != 0)
        {
            LOG_E("verify failed: addr=0x%08x", write_addr);
            result = -RT_ERROR;
            goto __lock_exit;
        }
    }

    result = (int)size;

__lock_exit:
    FLASH_Lock();
__exit:
    rt_mutex_release(&_flash_mutex);
    return result;
}

int n32_flash_erase(rt_uint32_t addr, size_t size)
{
    FLASH_STS status;
    rt_uint32_t erase_addr;
    rt_uint32_t end_addr;
    int result;

    if (!n32_flash_range_is_valid(addr, size))
    {
        LOG_E("invalid erase: addr=0x%08x, size=%u", addr, (unsigned int)size);
        return -RT_EINVAL;
    }

    result = n32_flash_lock_take();
    if (result != RT_EOK)
    {
        return result;
    }

    result = n32_flash_prepare();
    if (result != RT_EOK)
    {
        goto __exit;
    }

    erase_addr = addr & ~(N32_FLASH_PAGE_SIZE - 1U);
    end_addr = addr + (rt_uint32_t)size;

    while (erase_addr < end_addr)
    {
        status = FLASH_EraseOnePage(erase_addr);
        if (status != FLASH_EOP)
        {
            LOG_E("erase failed: addr=0x%08x, status=%d", erase_addr, status);
            result = -RT_ERROR;
            goto __lock_exit;
        }

        erase_addr += N32_FLASH_PAGE_SIZE;
    }

    result = (int)size;

__lock_exit:
    FLASH_Lock();
__exit:
    rt_mutex_release(&_flash_mutex);
    return result;
}

static int n32_flash_init(void)
{
    return rt_mutex_init(&_flash_mutex, "flash", RT_IPC_FLAG_PRIO);
}
INIT_DEVICE_EXPORT(n32_flash_init);

#ifdef RT_USING_FAL

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_erase(long offset, size_t size);

const struct fal_flash_dev n32_onchip_flash = {
    "onchip_flash",
    N32_FLASH_START_ADRESS,
    N32_FLASH_SIZE,
    N32_FLASH_PAGE_SIZE,
    { RT_NULL, fal_flash_read, fal_flash_write, fal_flash_erase }
};

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size)
{
    return n32_flash_read(n32_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size)
{
    return n32_flash_write(n32_onchip_flash.addr + offset, buf, size);
}

static int fal_flash_erase(long offset, size_t size)
{
    return n32_flash_erase(n32_onchip_flash.addr + offset, size);
}

#endif /* RT_USING_FAL */

#endif /* BSP_USING_ON_CHIP_FLASH */
