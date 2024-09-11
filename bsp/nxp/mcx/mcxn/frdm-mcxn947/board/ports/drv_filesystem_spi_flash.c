/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-14     balanceTWK   add sdcard port file
 * 2021-02-26     Meco Man     fix a bug that cannot use fatfs in the main thread at starting up
 */

#include <rtthread.h>

#if defined(BSP_USING_SPI7) && defined(RT_USING_SFUD) && defined(RT_USING_DFS) && defined(RT_USING_DFS_ELMFAT)
#include <dfs_elm.h>
#include "dev_spi_flash_sfud.h"
#include "dfs_fs.h"
#include "dfs.h"
#include "dfs_file.h"

#define DBG_TAG "app.filesystem_spi_flash"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define W25Q64_SPI_DEVICE_NAME      "spi70"
#define W25Q64_SPI_BUS_NAME         "spi7"
#define W25Q64_SPI_FLASH_NAME       "w25qxx"
#define W25Q64_SPI_FLASH_CS_PIN     96

#define W25Q64_FS_MOUNT_PATH "/"

static int app_filesystem_init(void)
{
    rt_err_t ret = RT_EOK;
    struct rt_spi_device *spi_device = rt_malloc(sizeof(struct rt_spi_device));

    if (!spi_device)
    {
        LOG_W("spi sample run failed! can't find %s device!\n", W25Q64_SPI_BUS_NAME);
        return -RT_ERROR;
    }

    struct rt_spi_configuration cfg =
    {
        .data_width = 8,
        .mode = RT_SPI_MASTER | RT_SPI_MODE_3 | RT_SPI_MSB,
        .max_hz = 50 * 1000 * 1000,
    };
    ret = rt_spi_configure(spi_device, &cfg);
    if (ret != RT_EOK)
    {
        LOG_E("SPI bus configuration failed.\n");
        return -RT_ERROR;
    }

    ret = rt_spi_bus_attach_device_cspin(spi_device, W25Q64_SPI_DEVICE_NAME, W25Q64_SPI_BUS_NAME, W25Q64_SPI_FLASH_CS_PIN, RT_NULL);
    if (ret != RT_EOK)
    {
        LOG_E("SPI flash device attach failed.\n");
        return -RT_ERROR;
    }

    if (RT_NULL == rt_sfud_flash_probe(W25Q64_SPI_FLASH_NAME, W25Q64_SPI_DEVICE_NAME))
    {
        LOG_E("Flash sfud Failed!\n");
        return -RT_ERROR;
    }

    if (dfs_mount(W25Q64_SPI_FLASH_NAME, W25Q64_FS_MOUNT_PATH, "elm", 0, 0) != 0)
    {
        LOG_W("Initial ELM FAT mount failed, trying to format block device.\n");

        if (dfs_mkfs("elm", W25Q64_SPI_FLASH_NAME) != 0)
        {
            LOG_E("Failed to create ELM FAT filesystem.\n");
            return -4;
        }

        if (dfs_mount(W25Q64_SPI_FLASH_NAME, W25Q64_FS_MOUNT_PATH, "elm", 0, 0) != 0)
        {
            LOG_E("Failed to mount ELM FAT filesystem, check mount point.\n");
            return -5;
        }
    }

    LOG_I("ELM FAT filesystem mounted.\n");

    return RT_EOK;
}

INIT_APP_EXPORT(app_filesystem_init);

#endif /* BSP_USING_SPI7/RT_USING_SFUD/RT_USING_DFS/RT_USING_DFS_ELMFAT */
