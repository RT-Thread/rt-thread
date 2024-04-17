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
<<<<<<< HEAD
=======

#if defined(BSP_USING_SPI7) && defined(RT_USING_SFUD) && defined(RT_USING_DFS) && defined(RT_USING_DFS_ELMFAT)
>>>>>>> 0bcf5968c20f167e864c9aae89468e965e2ca7d6
#include <dfs_elm.h>
#include "spi_flash_sfud.h"
#include "dfs_fs.h"
#include "dfs.h"
<<<<<<< HEAD
#include "dfs_elm.h"
=======
>>>>>>> 0bcf5968c20f167e864c9aae89468e965e2ca7d6
#include "dfs_file.h"

#if DFS_FILESYSTEMS_MAX < 4
#error "Please define DFS_FILESYSTEMS_MAX more than 4"
#endif
#if DFS_FILESYSTEM_TYPES_MAX < 4
#error "Please define DFS_FILESYSTEM_TYPES_MAX more than 4"
#endif
<<<<<<< HEAD

=======
#if RT_DFS_ELM_MAX_SECTOR_SIZE == 512
#define RT_DFS_ELM_MAX_SECTOR_SIZE 4096
#endif
>>>>>>> 0bcf5968c20f167e864c9aae89468e965e2ca7d6
#define DBG_TAG "app.filesystem_spi_flash"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>


#define W25Q64_SPI_DEVICE_NAME      "spi70"
#define W25Q64_SPI_BUS_NAME         "spi7"
#define W25Q64_SPI_FLASH_NAME       "w25qxx"

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t pin);
<<<<<<< HEAD
    
static int filesystem_mount(void)
{
    struct rt_spi_device *spi70 = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    
	if(!spi70)
	{
		rt_kprintf("spi sample run failed! can't find %s device!\n","spi7");
        return -RT_ERROR;
	}
=======

static int filesystem_mount(void)
{
    struct rt_spi_device *spi70 = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));

    if(!spi70)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n","spi7");
        return -RT_ERROR;
    }
>>>>>>> 0bcf5968c20f167e864c9aae89468e965e2ca7d6

    struct rt_spi_configuration cfg;
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_3 | RT_SPI_MSB;
    cfg.max_hz = 50 * 1000 *1000;
    rt_spi_configure(spi70, &cfg);

    /* legcy issue */
<<<<<<< HEAD
    
	//rt_spi_bus_attach_device_cspin(spi70, W25Q64_SPI_DEVICE_NAME, W25Q64_SPI_BUS_NAME, 96, RT_NULL);
    rt_hw_spi_device_attach(W25Q64_SPI_BUS_NAME, W25Q64_SPI_DEVICE_NAME, 96);
    
=======

//    rt_spi_bus_attach_device_cspin(spi70, W25Q64_SPI_DEVICE_NAME, W25Q64_SPI_BUS_NAME, 96, RT_NULL);
    rt_hw_spi_device_attach(W25Q64_SPI_BUS_NAME, W25Q64_SPI_DEVICE_NAME, 96);

>>>>>>> 0bcf5968c20f167e864c9aae89468e965e2ca7d6
    if(RT_NULL == rt_sfud_flash_probe(W25Q64_SPI_FLASH_NAME, W25Q64_SPI_DEVICE_NAME))
    {
        rt_kprintf("Flash sfud Failed!\n");
        return -RT_ERROR;
<<<<<<< HEAD
    };

=======
    }
//    dfs_mkfs("elm", "W25Q64_SPI_FLASH_NAME");
>>>>>>> 0bcf5968c20f167e864c9aae89468e965e2ca7d6
    if(dfs_mount(W25Q64_SPI_FLASH_NAME, "/", "elm", 0, 0))
    {
        rt_kprintf("dfs mount dev:%s failed!\n", W25Q64_SPI_FLASH_NAME);
        return -RT_ERROR;
    }
<<<<<<< HEAD
        
    return RT_EOK;
    
}
INIT_APP_EXPORT(filesystem_mount);
=======

    return RT_EOK;
}
INIT_APP_EXPORT(filesystem_mount);

#endif /* BSP_USING_SPI7/RT_USING_SFUD/RT_USING_DFS/RT_USING_DFS_ELMFAT */
>>>>>>> 0bcf5968c20f167e864c9aae89468e965e2ca7d6
