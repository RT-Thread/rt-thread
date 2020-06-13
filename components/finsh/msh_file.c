/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-09-25     Bernard      the first verion for FinSH
 */

#include <rtthread.h>

#if defined(FINSH_USING_MSH) && defined(RT_USING_DFS)

#include <finsh.h>
#include "msh.h"
#include <dfs_posix.h>

static int msh_readline(int fd, char *line_buf, int size)
{
    char ch;
    int index = 0;

    do
    {
        if (read(fd, &ch, 1) != 1)
        {
            /* nothing in this file */
            return 0;
        }
    }
    while (ch == '\n' || ch == '\r');

    /* set the first character */
    line_buf[index ++] = ch;

    while (index < size)
    {
        if (read(fd, &ch, 1) == 1)
        {
            if (ch == '\n' || ch == '\r')
            {
                line_buf[index] = '\0';
                break;
            }

            line_buf[index++] = ch;
        }
        else
        {
            line_buf[index] = '\0';
            break;
        }
    }

    return index;
}

int msh_exec_script(const char *cmd_line, int size)
{
    int ret;
    int fd = -1;
    char *pg_name;
    int length, cmd_length = 0;

    if (size == 0) return -RT_ERROR;

    /* get the length of command0 */
    while ((cmd_line[cmd_length] != ' ' && cmd_line[cmd_length] != '\t') && cmd_length < size)
        cmd_length ++;

    /* get name length */
    length = cmd_length + 32;

    /* allocate program name memory */
    pg_name = (char *) rt_malloc(length);
    if (pg_name == RT_NULL) return -RT_ENOMEM;

    /* copy command0 */
    memcpy(pg_name, cmd_line, cmd_length);
    pg_name[cmd_length] = '\0';

    if (strstr(pg_name, ".sh") != RT_NULL || strstr(pg_name, ".SH") != RT_NULL)
    {
        /* try to open program */
        fd = open(pg_name, O_RDONLY, 0);

        /* search in /bin path */
        if (fd < 0)
        {
            rt_snprintf(pg_name, length - 1, "/bin/%.*s", cmd_length, cmd_line);
            fd = open(pg_name, O_RDONLY, 0);
        }
    }

    rt_free(pg_name);
    if (fd >= 0)
    {
        /* found script */
        char *line_buf;
        int length;

        line_buf = (char *) rt_malloc(RT_CONSOLEBUF_SIZE);
        if (line_buf == RT_NULL) 
        {
            close(fd);
            return -RT_ENOMEM;
        }

        /* read line by line and then exec it */
        do
        {
            length = msh_readline(fd, line_buf, RT_CONSOLEBUF_SIZE);
            if (length > 0)
            {
                char ch = '\0';
                int index;

                for (index = 0; index < length; index ++)
                {
                    ch = line_buf[index];
                    if (ch == ' ' || ch == '\t') continue;
                    else break;
                }

                if (ch != '#') /* not a comment */
                    msh_exec(line_buf, length);
            }
        }
        while (length > 0);

        close(fd);
        rt_free(line_buf);

        ret = 0;
    }
    else
    {
        ret = -1;
    }

    return ret;
}

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

#endif /* defined(FINSH_USING_MSH) && defined(RT_USING_DFS) */

