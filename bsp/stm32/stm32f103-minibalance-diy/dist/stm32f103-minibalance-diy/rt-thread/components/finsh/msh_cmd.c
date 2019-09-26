/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-30     Bernard      the first verion for FinSH
 * 2015-08-28     Bernard      Add mkfs command.
 */

#include <rtthread.h>

#ifdef FINSH_USING_MSH

#include <finsh.h>
#include "msh.h"

#ifdef RT_USING_DFS
#include <dfs_posix.h>

#ifdef DFS_USING_WORKDIR
extern char working_directory[];
#endif

int cmd_ls(int argc, char **argv)
{
    extern void ls(const char *pathname);

    if (argc == 1)
    {
#ifdef DFS_USING_WORKDIR
        ls(working_directory);
#else
        ls("/");
#endif
    }
    else
    {
        ls(argv[1]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_ls, __cmd_ls, List information about the FILEs.);

int cmd_cp(int argc, char **argv)
{
    void copy(const char *src, const char *dst);

    if (argc != 3)
    {
        rt_kprintf("Usage: cp SOURCE DEST\n");
        rt_kprintf("Copy SOURCE to DEST.\n");
    }
    else
    {
        copy(argv[1], argv[2]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_cp, __cmd_cp, Copy SOURCE to DEST.);

int cmd_mv(int argc, char **argv)
{
    if (argc != 3)
    {
        rt_kprintf("Usage: mv SOURCE DEST\n");
        rt_kprintf("Rename SOURCE to DEST, or move SOURCE(s) to DIRECTORY.\n");
    }
    else
    {
        int fd;
        char *dest = RT_NULL;

        rt_kprintf("%s => %s\n", argv[1], argv[2]);

        fd = open(argv[2], O_DIRECTORY, 0);
        if (fd >= 0)
        {
            char *src;

            close(fd);

            /* it's a directory */
            dest = (char *)rt_malloc(DFS_PATH_MAX);
            if (dest == RT_NULL)
            {
                rt_kprintf("out of memory\n");
                return -RT_ENOMEM;
            }

            src = argv[1] + rt_strlen(argv[1]);
            while (src != argv[1])
            {
                if (*src == '/') break;
                src --;
            }

            rt_snprintf(dest, DFS_PATH_MAX - 1, "%s/%s", argv[2], src);
        }
        else
        {
            fd = open(argv[2], O_RDONLY, 0);
            if (fd >= 0)
            {
                close(fd);

                unlink(argv[2]);
            }

            dest = argv[2];
        }

        rename(argv[1], dest);
        if (dest != RT_NULL && dest != argv[2]) rt_free(dest);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_mv, __cmd_mv, Rename SOURCE to DEST.);

int cmd_cat(int argc, char **argv)
{
    int index;
    extern void cat(const char *filename);

    if (argc == 1)
    {
        rt_kprintf("Usage: cat [FILE]...\n");
        rt_kprintf("Concatenate FILE(s)\n");
        return 0;
    }

    for (index = 1; index < argc; index ++)
    {
        cat(argv[index]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_cat, __cmd_cat, Concatenate FILE(s));

int cmd_rm(int argc, char **argv)
{
    int index;

    if (argc == 1)
    {
        rt_kprintf("Usage: rm FILE...\n");
        rt_kprintf("Remove (unlink) the FILE(s).\n");
        return 0;
    }

    for (index = 1; index < argc; index ++)
    {
        unlink(argv[index]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_rm, __cmd_rm, Remove(unlink) the FILE(s).);

#ifdef DFS_USING_WORKDIR
int cmd_cd(int argc, char **argv)
{
    if (argc == 1)
    {
        rt_kprintf("%s\n", working_directory);
    }
    else if (argc == 2)
    {
        if (chdir(argv[1]) != 0)
        {
            rt_kprintf("No such directory: %s\n", argv[1]);
        }
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_cd, __cmd_cd, Change the shell working directory.);

int cmd_pwd(int argc, char **argv)
{
    rt_kprintf("%s\n", working_directory);
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_pwd, __cmd_pwd, Print the name of the current working directory.);
#endif

int cmd_mkdir(int argc, char **argv)
{
    if (argc == 1)
    {
        rt_kprintf("Usage: mkdir [OPTION] DIRECTORY\n");
        rt_kprintf("Create the DIRECTORY, if they do not already exist.\n");
    }
    else
    {
        mkdir(argv[1], 0);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_mkdir, __cmd_mkdir, Create the DIRECTORY.);

int cmd_mkfs(int argc, char **argv)
{
    int result = 0;
    char *type = "elm"; /* use the default file system type as 'fatfs' */

    if (argc == 2)
    {
        result = dfs_mkfs(type, argv[1]);
    }
    else if (argc == 4)
    {
        if (strcmp(argv[1], "-t") == 0)
        {
            type = argv[2];
            result = dfs_mkfs(type, argv[3]);
        }
    }
    else
    {
        rt_kprintf("Usage: mkfs [-t type] device\n");
        return 0;
    }

    if (result != RT_EOK)
    {
        rt_kprintf("mkfs failed, result=%d\n", result);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_mkfs, __cmd_mkfs, format disk with file system);

extern int df(const char *path);
int cmd_df(int argc, char** argv)
{
    if (argc != 2)
    {
        df("/");
    }
    else
    {
        if ((strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0))
        {
            rt_kprintf("df [path]\n");
        }
        else
        {
            df(argv[1]);
        }
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_df, __cmd_df, disk free);

int cmd_echo(int argc, char** argv)
{
    if (argc == 2)
    {
        rt_kprintf("%s\n", argv[1]);
    }
    else if (argc == 3)
    {
        int fd;

        fd = open(argv[2], O_RDWR | O_APPEND | O_CREAT, 0);
        if (fd >= 0)
        {
            write (fd, argv[1], strlen(argv[1]));
            close(fd);
        }
        else
        {
            rt_kprintf("open file:%s failed!\n", argv[2]);
        }
    }
    else
    {
        rt_kprintf("Usage: echo \"string\" [filename]\n");
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_echo, __cmd_echo, echo string to file);
#endif

int cmd_ps(int argc, char **argv)
{
    extern long list_thread(void);
    extern int list_module(void);

#ifdef RT_USING_MODULE
    if ((argc == 2) && (strcmp(argv[1], "-m") == 0))
        list_module();
    else
#endif
        list_thread();
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_ps, __cmd_ps, List threads in the system.);

int cmd_time(int argc, char **argv)
{
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_time, __cmd_time, Execute command with time.);

#ifdef RT_USING_HEAP
int cmd_free(int argc, char **argv)
{
    extern void list_mem(void);
    extern void list_memheap(void);

#ifdef RT_USING_MEMHEAP_AS_HEAP
    list_memheap();
#else
    list_mem();
#endif
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_free, __cmd_free, Show the memory usage in the system.);
#endif

#endif /* FINSH_USING_MSH */
