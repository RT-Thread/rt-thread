/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-05     mazhiyuan   first version
 */


#include <rtthread.h>
#include "hal_flash.h"
#include "drv_flash.h"

#define OCFLASH_BLK_SIZE 1024
#define OCFLASH_LEN 1024*512
#define OCFLASH_ADDR 0x08000000

#ifdef OCFLASH_USE_FAL
    #include <fal.h>
#endif

#ifdef OCFLASH_USE_LFS
    #include <dfs_fs.h>
    #define FS_PARTITION_NAME "filesystem"
#endif

static int init(void)
{
    /* do nothing now */
    return 0;
}

static int read(long offset, uint8_t *buf, size_t size)
{
    size_t i;
    uint32_t addr = OCFLASH_ADDR + offset;
    for (i = 0; i < size; i++)
    {
        *buf = *(__IO uint8_t *)addr;
        buf++;
        addr++;
    }
    return size;
}

static int write(long offset, const uint8_t *buf, size_t size)
{
    size_t i;
    uint32_t addr = OCFLASH_ADDR + offset;

    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;
    FLASH->SR = 0x00000001 | 0x00000004 | 0x00000010;
    FLASH->CR |= 0x1;

    i = 0;
    while (i < size)
    {
        *(__IO uint16_t *)addr = *buf | *(buf + 1) << 8;
        addr = addr + 2;
        buf += 2;
        i += 2;
    }
    //Lock flash
    FLASH->CR |= 0x00000080;

    return size;
}

static int erase(long offset, size_t size)
{
    int len;
    RT_ASSERT(offset > 0 && offset < OCFLASH_LEN);
    int page_addr = (offset >> 10) << 10;
    len = size + (offset - page_addr);
    while (len > 0)
    {
        FLASH_Unlock();
        FLASH_ErasePage(page_addr);
        FLASH_Lock();
        len -= OCFLASH_BLK_SIZE;
        page_addr += OCFLASH_BLK_SIZE;
    }

    return size;
}

#ifdef OCFLASH_USE_FAL
const struct fal_flash_dev mm32_onchip_flash =
{
    .name       = "mm32_onchip",
    .addr       = 0x08000000,
    .len        = 1024 * 512,
    .blk_size   = 1024,
    .ops        = {init, read, write, erase},
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

    if (flash_dev == NULL)
    {
        rt_kprintf("Can't create a mtd device on '%s' partition.\n", FS_PARTITION_NAME);
    }
    else
    {
        rt_kprintf("Create a mtd device on the %s partition of flash successful.\n", FS_PARTITION_NAME);
    }

    if (rt_device_find(FS_PARTITION_NAME) != RT_NULL)
    {
        if (dfs_mount(FS_PARTITION_NAME, "/", "lfs", 0, 0) == RT_EOK)
        {
            rt_kprintf("onchip lfs filesystem mount to '/'\n");
        }
        else
        {
            dfs_mkfs("lfs", FS_PARTITION_NAME);
            if (dfs_mount(FS_PARTITION_NAME, "/", "lfs", 0, 0) == RT_EOK)
            {
                rt_kprintf("onchip lfs filesystem mount to '/' with mkfs\n");
            }
            else
            {
                rt_kprintf("onchip lfs filesystem mount to '/' failed!\n");
            }
        }
    }
    else
    {
        rt_kprintf("find filesystem portion failed\r\n");
    }
#endif
    return 0;
}
INIT_APP_EXPORT(flash_init);
