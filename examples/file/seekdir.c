/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-06-02     Bernard      first version
 * 2020-04-12     Jianjia Ma   add msh cmd
 */
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>

void seekdir_test(void)
{
    DIR * dirp;
    long save3 = 0;
    int i = 0;
    struct dirent *dp;

    dirp = opendir ("/");
    save3 = telldir(dirp);
    for (dp = readdir(dirp); dp != RT_NULL; dp = readdir(dirp))
    {
        rt_kprintf("direntry: %s\n", dp->d_name);

        /* save the pointer of the third directory */
        if (i++ == 3)
        {
            save3 = telldir(dirp);
        }
    }

    /* get back to the third directory */
    seekdir (dirp, save3);
    rt_kprintf("seek dientry to: %d\n", save3);
    for (dp = readdir(dirp); dp != RT_NULL; dp = readdir(dirp))
    {
        rt_kprintf("direntry: %s\n", dp->d_name);
    }

    /* close the directory */
    closedir (dirp);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(seekdir_test, perform directory seek test);
MSH_CMD_EXPORT(seekdir_test, perform directory seek test);
#endif /* RT_USING_FINSH */
