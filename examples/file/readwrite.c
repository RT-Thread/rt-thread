/*
 * File      : readwrite.c
 * This file is part of RT-TestCase in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-02-10     Bernard      first version
 */
#include <rtthread.h>
#include <dfs_posix.h>

/* 文件读写测试 */
void readwrite(const char* filename)
{
	int fd;

	/* 只写打开 */

	/* 只写并在末尾添加打开 */

	/* 只读打开进行数据校验 */

	/* lseek测试，读出并校验数据 */
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(readwrite, perform file read and write test);
#endif
