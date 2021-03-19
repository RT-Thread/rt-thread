/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-09-25     Bernard      the first verion for FinSH
 */

#include <rtthread.h>
#include "msh.h"

#if defined(RT_USING_MSH) && defined(RT_USING_DFS)
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
MSH_CMD_EXPORT_ALIAS(cmd_ls, ls, List information about the FILEs.);

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
MSH_CMD_EXPORT_ALIAS(cmd_cp, cp, Copy SOURCE to DEST.);

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
MSH_CMD_EXPORT_ALIAS(cmd_mv, mv, Rename SOURCE to DEST.);

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
MSH_CMD_EXPORT_ALIAS(cmd_cat, cat, Concatenate FILE(s));

static void msh_deltree(const char *pathname, char f, char v)
{
    DIR *dir = NULL;
    struct dirent *dirent = NULL;
    char *full_path;

    if (pathname == RT_NULL)
        return;

    full_path = (char *)rt_malloc(DFS_PATH_MAX);
    if (full_path == RT_NULL)
        return;

    dir = opendir(pathname);
    if (dir == RT_NULL)
    {
        if (f == 0)
        {
            rt_kprintf("cannot remove '%s'\n", pathname);
        }
        rt_free(full_path);
        return;
    }

    while (1)
    {
        dirent = readdir(dir);
        if (dirent == RT_NULL)
            break;
        if (rt_strcmp(".", dirent->d_name) != 0 &&
            rt_strcmp("..", dirent->d_name) != 0)
        {
            rt_sprintf(full_path, "%s/%s", pathname, dirent->d_name);
            if (dirent->d_type == DT_REG)
            {
                if (unlink(full_path) != 0)
                {
                    if (f == 0)
                        rt_kprintf("cannot remove '%s'\n", full_path);
                }
                else if (v)
                {
                    rt_kprintf("removed '%s'\n", full_path);
                }
            }
            else if (dirent->d_type == DT_DIR)
            {
                msh_deltree(full_path, f, v);
            }
        }
    }
    closedir(dir);
    rt_free(full_path);
    if (unlink(pathname) != 0)
    {
        if (f == 0)
            rt_kprintf("cannot remove '%s'\n", pathname);
    }
    else if (v)
    {
        rt_kprintf("removed directory '%s'\n", pathname);
    }
}

int cmd_rm(int argc, char **argv)
{
    int index, n;
    char f = 0, r = 0, v = 0;

    if (argc == 1)
    {
        rt_kprintf("Usage: rm option(s) FILE...\n");
        rt_kprintf("Remove (unlink) the FILE(s).\n");
        return 0;
    }

    if (argv[1][0] == '-')
    {
        for (n = 0; argv[1][n]; n++)
        {
            switch (argv[1][n])
            {
                case 'f': f = 1; break;
                case 'r': r = 1; break;
                case 'v': v = 1; break;
                case '-': break;
                default:
                    rt_kprintf("Error: Bad option: %c\n", argv[1][n]);
                    return 0;
            }
        }
        argc -= 1;
        argv = argv + 1;
    }

    for (index = 1; index < argc; index ++)
    {
        struct stat s;
        if (stat (argv[index], &s) == 0)
        {
            if (s.st_mode & S_IFDIR)
            {
                if (r == 0)
                    rt_kprintf("cannot remove '%s': Is a directory\n", argv[index]);
                else
                    msh_deltree(argv[index], f, v);
            }
            else if (s.st_mode & S_IFREG)
            {
                if (unlink(argv[index]) != 0)
                {
                    if (f == 0)
                        rt_kprintf("cannot remove '%s'\n", argv[index]);
                }
                else if (v)
                {
                    rt_kprintf("removed '%s'\n", argv[index]);
                }
            }
        }
        else if (f == 0)
        {
            rt_kprintf("cannot remove '%s': No such file or directory\n", argv[index]);
        }
    }
    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_rm, rm, Remove(unlink) the FILE(s).);

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
MSH_CMD_EXPORT_ALIAS(cmd_cd, cd, Change the shell working directory.);

int cmd_pwd(int argc, char **argv)
{
    rt_kprintf("%s\n", working_directory);
    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_pwd, pwd, Print the name of the current working directory.);
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
MSH_CMD_EXPORT_ALIAS(cmd_mkdir, mkdir, Create the DIRECTORY.);

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
MSH_CMD_EXPORT_ALIAS(cmd_mkfs, mkfs, format disk with file system);

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
MSH_CMD_EXPORT_ALIAS(cmd_df, df, disk free);

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
MSH_CMD_EXPORT_ALIAS(cmd_echo, echo, echo string to file);

#endif /* defined(RT_USING_MSH) && defined(RT_USING_DFS) */
