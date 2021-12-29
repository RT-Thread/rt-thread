/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-28     Eric   	create_file_system
 */

#include "w25qxx.h"
/*************************************************
* Function:				create_file_system
* Description:
* Author:
* Returns: 
* Parameter:
* History:
*************************************************/

static void create_file_system(void)
{
	/*格式化指定存储设备，并创建文件系统*/
	if(dfs_mkfs("elm", "W25Q128") == RT_EOK)
	{
		rt_kprintf("create file system succeed!\n");
	}
	else
	{
		rt_kprintf("create file system failed!\n");
	}
}
/*************************************************
* Function:				w25q128_mount
* Description:
* Author:
* Returns: 
* Parameter:
* History:
*************************************************/
static void w25q128_mount(void)
{
	/*查找Flash设备*/
	if(rt_device_find("W25Q128") != RT_NULL) 
	{
		/*挂载Flash*/
		if(dfs_mount("W25Q128", "/", "elm", 0, 0) == 0)
		{
			rt_kprintf("spi_flash mount to spi!\n");
		} 
		else 
		{
			rt_kprintf("spi_flash mount to spi failed!\n");
		}
	}
}

MSH_CMD_EXPORT(create_file_system,create file system);
MSH_CMD_EXPORT(w25q128_mount,w25q128 mount);


