/*
 * File      : listdir.c
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

static char fullpath[256];
void list_dir(const char* path)
{
	DIR *dir;

	dir = opendir(path);
	if (dir != RT_NULL)
	{
		struct dirent* dirent;
		struct stat s;

		do
		{
			dirent = readdir(dir);
			if (dirent == RT_NULL) break;
			rt_memset(&s, 0, sizeof(struct stat));

			/* build full path for each file */
			rt_sprintf(fullpath, "%s/%s", path, dirent->d_name);

			stat(fullpath, &s);
			if ( s.st_mode & DFS_S_IFDIR )
			{
				rt_kprintf("%s\t\t<DIR>\n", dirent->d_name);
			}
			else
			{
				rt_kprintf("%s\t\t%lu\n", dirent->d_name, s.st_size);
			}
		} while (dirent != RT_NULL);

		closedir(dir);
	}
	else rt_kprintf("open %s directory failed\n", path);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(list_dir, list directory);
#endif
