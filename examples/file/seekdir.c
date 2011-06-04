/*
 * File      : seekdir.c
 * This file is part of RT-TestCase in RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-06-02     Bernard      first version
 */
#include <dfs_posix.h>

void seekdir_test(void)
{
	DIR * dirp;
	long save3 = 0;
	long cur;
	int i = 0;
	struct dirent *dp;

	dirp = opendir ("/");
	save3 = telldir(dirp);
	for (dp = readdir(dirp); dp != RT_NULL; dp = readdir(dirp))
	{
		rt_kprintf("direntry: %s\n", dp->d_name);

		/* 保存第三个目录项的目录指针 */
		if (i++ == 3)
		{
			save3 = telldir(dirp);
		}
	}

	/* 回到刚才保存的第三个目录项的目录指针 */
	seekdir (dirp, save3);
	rt_kprintf("seek dientry to: %d\n", save3);
	for (dp = readdir(dirp); dp != RT_NULL; dp = readdir(dirp))
	{
		rt_kprintf("direntry: %s\n", dp->d_name);
	}

	/* 关闭目录 */
	closedir (dirp);
} 

#include <finsh.h>
FINSH_FUNCTION_EXPORT(seekdir_test, perform directory seek test);
