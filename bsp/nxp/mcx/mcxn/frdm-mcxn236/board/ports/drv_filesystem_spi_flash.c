/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
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

#define DBG_TAG    "spi-flash"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#if DFS_FILESYSTEMS_MAX < 4
#error "Please define DFS_FILESYSTEMS_MAX more than 4"
#endif
#if DFS_FILESYSTEM_TYPES_MAX < 4
#error "Please define DFS_FILESYSTEM_TYPES_MAX more than 4"
#endif


#define DBG_TAG "app.filesystem_spi_flash"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>


#define W25Q64_SPI_DEVICE_NAME      "spi70"
#define W25Q64_SPI_BUS_NAME         "spi7"
#define W25Q64_SPI_FLASH_NAME       "w25qxx"

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t pin);

static int filesystem_mount(void)
{
    struct rt_spi_device *spi70 = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));

    if(!spi70)
    {
        LOG_W("spi sample run failed! can't find %s device!\n","spi7");
        return -RT_ERROR;
    }

    struct rt_spi_configuration cfg;
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_3 | RT_SPI_MSB;
    cfg.max_hz = 50 * 1000 *1000;
    rt_spi_configure(spi70, &cfg);

    /* legcy issue */

    rt_hw_spi_device_attach(W25Q64_SPI_BUS_NAME, W25Q64_SPI_DEVICE_NAME, 96);

    if(RT_NULL == rt_sfud_flash_probe(W25Q64_SPI_FLASH_NAME, W25Q64_SPI_DEVICE_NAME))
    {
        LOG_E("Flash sfud Failed!\n");
        return -RT_ERROR;
    }
    if(dfs_mount(W25Q64_SPI_FLASH_NAME, "/", "elm", 0, 0))
    {
        LOG_E("dfs mount dev:%s failed!\n", W25Q64_SPI_FLASH_NAME);
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_APP_EXPORT(filesystem_mount);

#endif /* BSP_USING_SPI7/RT_USING_SFUD/RT_USING_DFS/RT_USING_DFS_ELMFAT */
