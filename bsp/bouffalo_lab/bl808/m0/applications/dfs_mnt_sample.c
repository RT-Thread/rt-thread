/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-04-08     wcx1024979076     first version
 */
 /*
 * 程序清单：这是一个 dfs 虚拟文件系统挂载文件系统使用例程
 * 例程导出了 mnt_init 命令到应用初始化中
 * 程序功能：挂载 elm 文件系统到片上flash filesystem 分区中
 * 使用前参考文章 https://blog.csdn.net/h451884098/article/details/118544347 和 https://blog.csdn.net/u013213069/article/details/117384971 开启以下配置：
 * 1、修改 menuconfig 打开RT_USING_DFS 和 elm-chan 文件系统并修改扇区 sector 大小为 4096
 * 2、修改 components/dfs/dfs_v1/include/dfs.h 和 components/dfs/dfs_v2/include/dfs.h 中 SECTOR_SIZE 改为 4096
 * 3、修改芯片外设配置打开 BSP_USING_ON_CHIP_FLASH
 * 4、修改 menuconfig 打开 RT_USING_FAL 配置
*/
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_DFS
#ifdef RT_USING_FAL
#ifdef BSP_USING_ON_CHIP_FLASH

#include "dfs_file.h"
#include "fal.h"

int mnt_init(void)
{
    struct rt_device *rootfs = RT_NULL;

    /* 使用 filesystem 分区创建块设备，块设备名称为 filesystem */
    rootfs = fal_blk_device_create("filesystem");
    if(rootfs == RT_NULL)
        return -RT_ERROR;

    /* 将 elm fat 文件系统挂载 filesystem 分区 */
    if (dfs_mount("filesystem", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("file system initialization done!\n");
    }
    else
    {
        if(dfs_mkfs("elm", "filesystem") == 0)
        {
            if (dfs_mount("filesystem", "/", "elm", 0, 0) == 0)
            {
                rt_kprintf("file system initialization done!\n");
            }
            else
            {
                rt_kprintf("file system initialization failed!\n");
            }
        }
    }

    return RT_EOK;
}

INIT_APP_EXPORT(mnt_init);

#endif /* RT_USING_DFS */
#endif /* RT_USING_FAL */
#endif /* BSP_USING_ON_CHIP_FLASH */
