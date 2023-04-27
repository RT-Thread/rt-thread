/*
 * @Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * @FilePath: mnt.c
 * @Date: 2023-04-21 15:26:26
 * @LastEditTime: 2023-04-21 15:26:26
 * @Description:  This file is for 
 * 
 * @Modify History: 
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 */
/*
 * @Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * @FilePath: mnt.c
 * @Date: 2023-04-19 14:30:05
 * @LastEditTime: 2023-04-19 14:30:05
 * @Description:  This file is for 
 * 
 * @Modify History: 
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 */
/*
 * Copyright (c) 2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-09-19     Gavin        first version
 *
 */

#include <rtthread.h>
#ifdef RT_USING_DFS_RAMFS
#include <dfs_fs.h>

extern struct dfs_ramfs *dfs_ramfs_create(rt_uint8_t *pool, rt_size_t size);

int mnt_init(void)
{
    rt_uint8_t *pool = RT_NULL;
    rt_size_t size = 8*1024*1024;

    pool = rt_malloc(size);
    if (pool == RT_NULL)
        return 0;

    if (dfs_mount(RT_NULL, "/", "ram", 0, (const void *)dfs_ramfs_create(pool, size)) == 0)
        rt_kprintf("RAM file system initializated!\n");
    else
        rt_kprintf("RAM file system initializate failed!\n");

    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif

#ifdef BSP_USING_SDCARD_FATFS
#include <dfs_fs.h>
#include <dfs_file.h>
#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
static int filesystem_mount(void)
{
    while(rt_device_find("sd0") == RT_NULL)
    {
        rt_thread_mdelay(1);
    }
  
    int ret = dfs_mount("sd0", "/", "elm", 0, 0);
    if (ret != 0)
    {
        rt_kprintf("ret: %d\n",ret);
        LOG_E("sd0 mount to '/' failed!");
        return ret;
    }

    return RT_EOK;
}
INIT_ENV_EXPORT(filesystem_mount);
#endif
