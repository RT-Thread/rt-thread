/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-02-10     Bernard      first version
 * 2020-04-12     Jianjia Ma   add msh cmd
 */
#include <rtthread.h>
#include <dfs_posix.h>

void list_dir(const char* path)
{
    char * fullpath;
    DIR *dir;

    dir = opendir(path);
    if (dir != RT_NULL)
    {
        struct dirent* dirent;
        struct stat s;

        fullpath = rt_malloc(256);
        if (fullpath == RT_NULL)
        {
            closedir(dir);
            rt_kprintf("no memory\n");
            return;
        }

        do
        {
            dirent = readdir(dir);
            if (dirent == RT_NULL) break;
            rt_memset(&s, 0, sizeof(struct stat));

            /* build full path for each file */
            rt_sprintf(fullpath, "%s/%s", path, dirent->d_name);

            stat(fullpath, &s);
            if ( s.st_mode & S_IFDIR )
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
    else
    {
        rt_kprintf("open %s directory failed\n", path);
    }

    rt_free(fullpath);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(list_dir, list directory);

#ifdef FINSH_USING_MSH
static void cmd_list_dir(int argc, char *argv[])
{
    char* filename;

    if(argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        rt_kprintf("Usage: list_dir [file_path]\n");
        return;
    }
    list_dir(filename);
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_list_dir, __cmd_list_dir, list directory);
#endif /* FINSH_USING_MSH */
#endif /* RT_USING_FINSH */
