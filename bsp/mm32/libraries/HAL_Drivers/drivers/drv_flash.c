/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include "hal_flash.h"
#include "drv_flash.h"

#if defined(BSP_USING_OCFLASH)

#define LOG_TAG             "drv.flash"
#include <rtdbg.h>

#if defined(SOC_SERIES_MM32F526)
#define OCFLASH_LEN         (256 * 1024)
#elif defined(SOC_SERIES_MM32F327) || defined(SOC_SERIES_MM32F3277)
#define OCFLASH_LEN         (512 * 1024)
#else
#error "Unsupported MM32 on-chip flash series"
#endif

#ifndef OCFLASH_ADDR
#define OCFLASH_ADDR        (0x08000000UL)
#endif

#ifndef OCFLASH_BLK_SIZE
#define OCFLASH_BLK_SIZE    (1024UL)
#endif

#ifdef OCFLASH_USE_FAL
#include <fal.h>
#endif

#ifdef OCFLASH_USE_LFS
#include <dfs_fs.h>
#define FS_PARTITION_NAME   "filesystem"
#endif

static int fal_flash_init(void)
{
    return 0;
}

static int fal_flash_read(long offset, rt_uint8_t *buf, size_t size)
{
    size_t i;
    rt_uint32_t addr = OCFLASH_ADDR + offset;

    RT_ASSERT(buf != RT_NULL);

    if ((offset < 0) || ((rt_uint32_t)offset + size > OCFLASH_LEN))
    {
        LOG_E("read outrange flash size! addr is (0x%08x)", addr + size);
        return -RT_EINVAL;
    }

    for (i = 0; i < size; i++)
    {
        buf[i] = *(__IO rt_uint8_t *)(addr + i);
    }

    return (int)size;
}

static int fal_flash_write(long offset, const rt_uint8_t *buf, size_t size)
{
    size_t i = 0;
    rt_uint32_t addr = OCFLASH_ADDR + offset;

    RT_ASSERT(buf != RT_NULL);

    if ((offset < 0) || ((rt_uint32_t)offset + size > OCFLASH_LEN))
    {
        LOG_E("write outrange flash size! addr is (0x%08x)", addr + size);
        return -RT_EINVAL;
    }

    if ((addr & 0x1U) || (size & 0x1U))
    {
        LOG_E("write addr and size must be halfword aligned");
        return -RT_EINVAL;
    }

    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;
    FLASH->SR = 0x00000001 | 0x00000004 | 0x00000010;
    FLASH->CR |= 0x1;

    while (i < size)
    {
        *(__IO rt_uint16_t *)(addr + i) = (rt_uint16_t)(buf[i] | (buf[i + 1] << 8));
        i += 2;
    }

    FLASH->CR |= 0x00000080;

    return (int)size;
}

static int fal_flash_erase(long offset, size_t size)
{
    rt_uint32_t erase_addr;
    rt_uint32_t erase_size;

    if ((offset < 0) || ((rt_uint32_t)offset + size > OCFLASH_LEN))
    {
        LOG_E("erase outrange flash size! offset is (0x%08x)", offset + size);
        return -RT_EINVAL;
    }

    erase_addr = (OCFLASH_ADDR + offset) & ~(OCFLASH_BLK_SIZE - 1);
    erase_size = size + ((OCFLASH_ADDR + offset) - erase_addr);

    while (erase_size > 0)
    {
        FLASH_Unlock();
        FLASH_ErasePage(erase_addr);
        FLASH_Lock();

        erase_addr += OCFLASH_BLK_SIZE;
        erase_size = (erase_size > OCFLASH_BLK_SIZE) ? (erase_size - OCFLASH_BLK_SIZE) : 0;
    }

    return (int)size;
}

#ifdef OCFLASH_USE_FAL
const struct fal_flash_dev mm32_onchip_flash =
{
    .name       = "mm32_onchip",
    .addr       = OCFLASH_ADDR,
    .len        = OCFLASH_LEN,
    .blk_size   = OCFLASH_BLK_SIZE,
    .ops        = {fal_flash_init, fal_flash_read, fal_flash_write, fal_flash_erase},
    .write_gran = 2
};
#endif

int flash_init(void)
{
#ifdef OCFLASH_USE_FAL
    fal_init();
#endif

#ifdef OCFLASH_USE_LFS
    struct rt_device *flash_dev = fal_mtd_nor_device_create(FS_PARTITION_NAME);

    if (flash_dev == RT_NULL)
    {
        LOG_E("Can't create a mtd device on '%s' partition.", FS_PARTITION_NAME);
        return -RT_ERROR;
    }

    if (rt_device_find(FS_PARTITION_NAME) != RT_NULL)
    {
        if (dfs_mount(FS_PARTITION_NAME, "/", "lfs", 0, 0) != RT_EOK)
        {
            dfs_mkfs("lfs", FS_PARTITION_NAME);
            if (dfs_mount(FS_PARTITION_NAME, "/", "lfs", 0, 0) != RT_EOK)
            {
                LOG_E("onchip lfs filesystem mount to '/' failed");
                return -RT_ERROR;
            }
        }
    }
    else
    {
        LOG_E("find filesystem partition failed");
        return -RT_ERROR;
    }
#endif

    return 0;
}
INIT_APP_EXPORT(flash_init);

#endif /* BSP_USING_OCFLASH */
