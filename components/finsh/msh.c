/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-30     Bernard      the first verion for finsh
 * 2014-01-03     Bernard      msh can execute module.
 * 2017-07-19     Aubr.Cool    limit argc to RT_FINSH_ARG_MAX
 */
#include <rtthread.h>
#include <string.h>

#ifdef RT_USING_FINSH

#ifndef FINSH_ARG_MAX
#define FINSH_ARG_MAX    8
#endif /* FINSH_ARG_MAX */

#include "msh.h"
#include "shell.h"
#ifdef DFS_USING_POSIX
#include <dfs_posix.h>
#endif /* DFS_USING_POSIX */
#ifdef RT_USING_MODULE
#include <dlmodule.h>
#endif /* RT_USING_MODULE */

typedef int (*cmd_function_t)(int argc, char **argv);

int msh_help(int argc, char **argv)
{
    rt_kprintf("RT-Thread shell commands:\n");
    {
        struct finsh_syscall *index;

        for (index = _syscall_table_begin;
                index < _syscall_table_end;
                FINSH_NEXT_SYSCALL(index))
        {
#if defined(FINSH_USING_DESCRIPTION) && defined(FINSH_USING_SYMTAB)
            rt_kprintf("%-16s - %s\n", index->name, index->desc);
#else
            rt_kprintf("%s ", index->name);
#endif
        }
    }
    rt_kprintf("\n");

    return 0;
}
MSH_CMD_EXPORT_ALIAS(msh_help, help, RT - Thread shell help.);

#ifdef MSH_USING_BUILT_IN_COMMANDS
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
MSH_CMD_EXPORT_ALIAS(cmd_ps, ps, List threads in the system.);

#ifdef RT_USING_HEAP
int cmd_free(int argc, char **argv)
{
    extern void list_mem(void);
    extern void list_memheap(void);

#ifdef RT_USING_MEMHEAP_AS_HEAP
    list_memheap();
#else /* RT_USING_MEMHEAP_AS_HEAP */
    list_mem();
#endif
    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_free, free, Show the memory usage in the system.);
#endif /* RT_USING_HEAP */
#endif /* MSH_USING_BUILT_IN_COMMANDS */

static int msh_split(char *cmd, rt_size_t length, char *argv[FINSH_ARG_MAX])
{
    char *ptr;
    rt_size_t position;
    rt_size_t argc;
    rt_size_t i;

    ptr = cmd;
    position = 0;
    argc = 0;

    while (position < length)
    {
        /* strip bank and tab */
        while ((*ptr == ' ' || *ptr == '\t') && position < length)
        {
            *ptr = '\0';
            ptr ++;
            position ++;
        }

        if (argc >= FINSH_ARG_MAX)
        {
            rt_kprintf("Too many args ! We only Use:\n");
            for (i = 0; i < argc; i++)
            {
                rt_kprintf("%s ", argv[i]);
            }
            rt_kprintf("\n");
            break;
        }

        if (position >= length) break;

        /* handle string */
        if (*ptr == '"')
        {
            ptr ++;
            position ++;
            argv[argc] = ptr;
            argc ++;

            /* skip this string */
            while (*ptr != '"' && position < length)
            {
                if (*ptr == '\\')
                {
                    if (*(ptr + 1) == '"')
                    {
                        ptr ++;
                        position ++;
                    }
                }
                ptr ++;
                position ++;
            }
            if (position >= length) break;

            /* skip '"' */
            *ptr = '\0';
            ptr ++;
            position ++;
        }
        else
        {
            argv[argc] = ptr;
            argc ++;
            while ((*ptr != ' ' && *ptr != '\t') && position < length)
            {
                ptr ++;
                position ++;
            }
            if (position >= length) break;
        }
    }

    return argc;
}

static cmd_function_t msh_get_cmd(char *cmd, int size)
{
    struct finsh_syscall *index;
    cmd_function_t cmd_func = RT_NULL;

    for (index = _syscall_table_begin;
            index < _syscall_table_end;
            FINSH_NEXT_SYSCALL(index))
    {
        if (strncmp(index->name, cmd, size) == 0 &&
                index->name[size] == '\0')
        {
            cmd_func = (cmd_function_t)index->func;
            break;
        }
    }

    return cmd_func;
}

#if defined(RT_USING_MODULE) && defined(DFS_USING_POSIX)
/* Return 0 on module executed. Other value indicate error.
 */
int msh_exec_module(const char *cmd_line, int size)
{
    int ret;
    int fd = -1;
    char *pg_name;
    int length, cmd_length = 0;

    if (size == 0)
        return -RT_ERROR;
    /* get the length of command0 */
    while ((cmd_line[cmd_length] != ' ' && cmd_line[cmd_length] != '\t') && cmd_length < size)
        cmd_length ++;

    /* get name length */
    length = cmd_length + 32;

    /* allocate program name memory */
    pg_name = (char *) rt_malloc(length);
    if (pg_name == RT_NULL)
        return -RT_ENOMEM;

    /* copy command0 */
    memcpy(pg_name, cmd_line, cmd_length);
    pg_name[cmd_length] = '\0';

    if (strstr(pg_name, ".mo") != RT_NULL || strstr(pg_name, ".MO") != RT_NULL)
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
    else
    {
        /* add .mo and open program */

        /* try to open program */
        strcat(pg_name, ".mo");
        fd = open(pg_name, O_RDONLY, 0);

        /* search in /bin path */
        if (fd < 0)
        {
            rt_snprintf(pg_name, length - 1, "/bin/%.*s.mo", cmd_length, cmd_line);
            fd = open(pg_name, O_RDONLY, 0);
        }
    }

    if (fd >= 0)
    {
        /* found program */
        close(fd);
        dlmodule_exec(pg_name, cmd_line, size);
        ret = 0;
    }
    else
    {
        ret = -1;
    }

    rt_free(pg_name);
    return ret;
}
#endif /* defined(RT_USING_MODULE) && defined(DFS_USING_POSIX) */

static int _msh_exec_cmd(char *cmd, rt_size_t length, int *retp)
{
    int argc;
    rt_size_t cmd0_size = 0;
    cmd_function_t cmd_func;
    char *argv[FINSH_ARG_MAX];

    RT_ASSERT(cmd);
    RT_ASSERT(retp);

    /* find the size of first command */
    while ((cmd[cmd0_size] != ' ' && cmd[cmd0_size] != '\t') && cmd0_size < length)
        cmd0_size ++;
    if (cmd0_size == 0)
        return -RT_ERROR;

    cmd_func = msh_get_cmd(cmd, cmd0_size);
    if (cmd_func == RT_NULL)
        return -RT_ERROR;

    /* split arguments */
    memset(argv, 0x00, sizeof(argv));
    argc = msh_split(cmd, length, argv);
    if (argc == 0)
        return -RT_ERROR;

    /* exec this command */
    *retp = cmd_func(argc, argv);
    return 0;
}

#if defined(RT_USING_LWP) && defined(DFS_USING_POSIX)
static int _msh_exec_lwp(char *cmd, rt_size_t length)
{
    int argc;
    int cmd0_size = 0;
    char *argv[FINSH_ARG_MAX];
    int fd = -1;
    char *pg_name;

    extern int exec(char *, int, char **);

    /* find the size of first command */
    while ((cmd[cmd0_size] != ' ' && cmd[cmd0_size] != '\t') && cmd0_size < length)
        cmd0_size ++;
    if (cmd0_size == 0)
        return -1;

    /* split arguments */
    rt_memset(argv, 0x00, sizeof(argv));
    argc = msh_split(cmd, length, argv);
    if (argc == 0)
        return -1;

    pg_name = argv[0];
    /* try to open program */
    fd = open(pg_name, O_RDONLY, 0);

    if (fd < 0)
        return -1;

    /* found program */
    close(fd);
    exec(pg_name, argc, argv);

    return 0;
}
#endif /* defined(RT_USING_LWP) && defined(DFS_USING_POSIX) */

int msh_exec(char *cmd, rt_size_t length)
{
    int cmd_ret;

    /* strim the beginning of command */
    while ((length > 0) && (*cmd  == ' ' || *cmd == '\t'))
    {
        cmd++;
        length--;
    }

    if (length == 0)
        return 0;

    /* Exec sequence:
     * 1. built-in command
     * 2. module(if enabled)
     */
    if (_msh_exec_cmd(cmd, length, &cmd_ret) == 0)
    {
        return cmd_ret;
    }
#ifdef DFS_USING_POSIX
#ifdef DFS_USING_WORKDIR
    if (msh_exec_script(cmd, length) == 0)
    {
        return 0;
    }
#endif

#ifdef RT_USING_MODULE
    if (msh_exec_module(cmd, length) == 0)
    {
        return 0;
    }
#endif /* RT_USING_MODULE */

#ifdef RT_USING_LWP
    if (_msh_exec_lwp(cmd, length) == 0)
    {
        return 0;
    }
#endif /* RT_USING_LWP */
#endif /* DFS_USING_POSIX */

    /* truncate the cmd at the first space. */
    {
        char *tcmd;
        tcmd = cmd;
        while (*tcmd != ' ' && *tcmd != '\0')
        {
            tcmd++;
        }
        *tcmd = '\0';
    }
    rt_kprintf("%s: command not found.\n", cmd);
    return -1;
}

static int str_common(const char *str1, const char *str2)
{
    const char *str = str1;

    while ((*str != 0) && (*str2 != 0) && (*str == *str2))
    {
        str ++;
        str2 ++;
    }

    return (str - str1);
}

#ifdef DFS_USING_POSIX
void msh_auto_complete_path(char *path)
{
    DIR *dir = RT_NULL;
    struct dirent *dirent = RT_NULL;
    char *full_path, *ptr, *index;

    if (!path)
        return;

    full_path = (char *)rt_malloc(256);
    if (full_path == RT_NULL) return; /* out of memory */

    if (*path != '/')
    {
        getcwd(full_path, 256);
        if (full_path[rt_strlen(full_path) - 1]  != '/')
            strcat(full_path, "/");
    }
    else *full_path = '\0';

    index = RT_NULL;
    ptr = path;
    for (;;)
    {
        if (*ptr == '/') index = ptr + 1;
        if (!*ptr) break;

        ptr ++;
    }
    if (index == RT_NULL) index = path;

    if (index != RT_NULL)
    {
        char *dest = index;

        /* fill the parent path */
        ptr = full_path;
        while (*ptr) ptr ++;

        for (index = path; index != dest;)
            *ptr++ = *index++;
        *ptr = '\0';

        dir = opendir(full_path);
        if (dir == RT_NULL) /* open directory failed! */
        {
            rt_free(full_path);
            return;
        }

        /* restore the index position */
        index = dest;
    }

    /* auto complete the file or directory name */
    if (*index == '\0') /* display all of files and directories */
    {
        for (;;)
        {
            dirent = readdir(dir);
            if (dirent == RT_NULL) break;

            rt_kprintf("%s\n", dirent->d_name);
        }
    }
    else
    {
        rt_size_t length, min_length;

        min_length = 0;
        for (;;)
        {
            dirent = readdir(dir);
            if (dirent == RT_NULL) break;

            /* matched the prefix string */
            if (strncmp(index, dirent->d_name, rt_strlen(index)) == 0)
            {
                if (min_length == 0)
                {
                    min_length = rt_strlen(dirent->d_name);
                    /* save dirent name */
                    strcpy(full_path, dirent->d_name);
                }

                length = str_common(dirent->d_name, full_path);

                if (length < min_length)
                {
                    min_length = length;
                }
            }
        }

        if (min_length)
        {
            if (min_length < rt_strlen(full_path))
            {
                /* list the candidate */
                rewinddir(dir);

                for (;;)
                {
                    dirent = readdir(dir);
                    if (dirent == RT_NULL) break;

                    if (strncmp(index, dirent->d_name, rt_strlen(index)) == 0)
                        rt_kprintf("%s\n", dirent->d_name);
                }
            }

            length = index - path;
            memcpy(index, full_path, min_length);
            path[length + min_length] = '\0';
        }
    }

    closedir(dir);
    rt_free(full_path);
}
#endif /* DFS_USING_POSIX */

void msh_auto_complete(char *prefix)
{
    int length, min_length;
    const char *name_ptr, *cmd_name;
    struct finsh_syscall *index;

    min_length = 0;
    name_ptr = RT_NULL;

    if (*prefix == '\0')
    {
        msh_help(0, RT_NULL);
        return;
    }

#ifdef DFS_USING_POSIX
    /* check whether a spare in the command */
    {
        char *ptr;

        ptr = prefix + rt_strlen(prefix);
        while (ptr != prefix)
        {
            if (*ptr == ' ')
            {
                msh_auto_complete_path(ptr + 1);
                break;
            }

            ptr --;
        }
#ifdef RT_USING_MODULE
        /* There is a chance that the user want to run the module directly. So
         * try to complete the file names. If the completed path is not a
         * module, the system won't crash anyway. */
        if (ptr == prefix)
        {
            msh_auto_complete_path(ptr);
        }
#endif /* RT_USING_MODULE */
    }
#endif /* DFS_USING_POSIX */

    /* checks in internal command */
    {
        for (index = _syscall_table_begin; index < _syscall_table_end; FINSH_NEXT_SYSCALL(index))
        {
            /* skip finsh shell function */
            cmd_name = (const char *) index->name;
            if (strncmp(prefix, cmd_name, strlen(prefix)) == 0)
            {
                if (min_length == 0)
                {
                    /* set name_ptr */
                    name_ptr = cmd_name;
                    /* set initial length */
                    min_length = strlen(name_ptr);
                }

                length = str_common(name_ptr, cmd_name);
                if (length < min_length)
                    min_length = length;

                rt_kprintf("%s\n", cmd_name);
            }
        }
    }

    /* auto complete string */
    if (name_ptr != NULL)
    {
        rt_strncpy(prefix, name_ptr, min_length);
    }

    return ;
}
#endif /* RT_USING_FINSH */
