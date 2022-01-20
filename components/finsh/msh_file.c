/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-09-25     Bernard      the first verion for FinSH
 * 2021-06-09     Meco Man     implement tail command
 */

#include <rtthread.h>

#if defined(RT_USING_FINSH) && defined(DFS_USING_POSIX)

#include <finsh.h>
#include "msh.h"
#include <dfs_file.h>
#include <unistd.h>
#include <fcntl.h>

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
    rt_memcpy(pg_name, cmd_line, cmd_length);
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

static int cmd_ls(int argc, char **argv)
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

static int cmd_cp(int argc, char **argv)
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

static int cmd_mv(int argc, char **argv)
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

static int cmd_cat(int argc, char **argv)
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

static void directory_delete_for_msh(const char *pathname, char f, char v)
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
                directory_delete_for_msh(full_path, f, v);
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

static int cmd_rm(int argc, char **argv)
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
            case 'f':
                f = 1;
                break;
            case 'r':
                r = 1;
                break;
            case 'v':
                v = 1;
                break;
            case '-':
                break;
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
        if (stat(argv[index], &s) == 0)
        {
            if (s.st_mode & S_IFDIR)
            {
                if (r == 0)
                    rt_kprintf("cannot remove '%s': Is a directory\n", argv[index]);
                else
                    directory_delete_for_msh(argv[index], f, v);
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
static int cmd_cd(int argc, char **argv)
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

static int cmd_pwd(int argc, char **argv)
{
    rt_kprintf("%s\n", working_directory);
    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_pwd, pwd, Print the name of the current working directory.);
#endif

static int cmd_mkdir(int argc, char **argv)
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

static int cmd_mkfs(int argc, char **argv)
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

extern struct dfs_filesystem filesystem_table[];
static int cmd_mount(int argc, char **argv)
{
    if (argc == 1)
    {
        struct dfs_filesystem *iter;

        /* display the mount history */
        rt_kprintf("filesystem  device  mountpoint\n");
        rt_kprintf("----------  ------  ----------\n");
        for (iter = &filesystem_table[0];
                iter < &filesystem_table[DFS_FILESYSTEMS_MAX]; iter++)
        {
            if ((iter != NULL) && (iter->path != NULL))
            {
                rt_kprintf("%-10s  %-6s  %-s\n",
                           iter->ops->name, iter->dev_id->parent.name, iter->path);
            }
        }
        return 0;
    }
    else if (argc == 4)
    {
        char *device = argv[1];
        char *path = argv[2];
        char *fstype = argv[3];

        /* mount a filesystem to the specified directory */
        rt_kprintf("mount device %s(%s) onto %s ... ", device, fstype, path);
        if (dfs_mount(device, path, fstype, 0, 0) == 0)
        {
            rt_kprintf("succeed!\n");
            return 0;
        }
        else
        {
            rt_kprintf("failed!\n");
            return -1;
        }
    }
    else
    {
        rt_kprintf("Usage: mount <device> <mountpoint> <fstype>.\n");
        return -1;
    }
}
MSH_CMD_EXPORT_ALIAS(cmd_mount, mount, mount <device> <mountpoint> <fstype>);

/* unmount the filesystem from the specified mountpoint */
static int cmd_umount(int argc, char **argv)
{
    char *path = argv[1];

    if (argc != 2)
    {
        rt_kprintf("Usage: unmount <mountpoint>.\n");
        return -1;
    }

    rt_kprintf("unmount %s ... ", path);
    if (dfs_unmount(path) < 0)
    {
        rt_kprintf("failed!\n");
        return -1;
    }
    else
    {
        rt_kprintf("succeed!\n");
        return 0;
    }
}
MSH_CMD_EXPORT_ALIAS(cmd_umount, umount, Unmount device from file system);

extern int df(const char *path);
static int cmd_df(int argc, char **argv)
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

static int cmd_echo(int argc, char **argv)
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
            write(fd, argv[1], strlen(argv[1]));
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

static int cmd_tail(int argc, char **argv)
{
    int fd;
    char c = RT_NULL;
    char *file_name = RT_NULL;
    rt_uint32_t total_lines = 0;
    rt_uint32_t target_line = 0;
    rt_uint32_t current_line = 0;
    rt_uint32_t required_lines = 0;
    rt_uint32_t start_line = 0;

    if (argc < 2)
    {
        rt_kprintf("Usage: tail [-n numbers] <filename>\n");
        return -1;
    }
    else if (argc == 2)
    {
        required_lines = 10; /* default: 10 lines from tail */
        file_name = argv[1];
    }
    else if (rt_strcmp(argv[1], "-n") == 0)
    {
        if (argv[2][0] != '+')
        {
            required_lines = atoi(argv[2]);
        }
        else
        {
            start_line = atoi(&argv[2][1]); /* eg: +100, to get the 100 */
        }
        file_name = argv[3];
    }
    else
    {
        rt_kprintf("Usage: tail [-n numbers] <filename>\n");
        return -1;
    }

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
        rt_kprintf("File doesn't exist\n");
        return -1;
    }

    while ((read(fd, &c, sizeof(char))) > 0)
    {
        if(total_lines == 0)
        {
            total_lines++;
        }
        if (c == '\n')
        {
            total_lines++;
        }
    }

    rt_kprintf("\nTotal Number of lines:%d\n", total_lines);

    if (start_line != 0)
    {
        if (total_lines >= start_line)
        {
            required_lines = total_lines - start_line + 1;
        }
        else
        {
            rt_kprintf("\nError:Required lines are more than total number of lines\n");
            close(fd);
            return -1;
        }
    }

    if (required_lines > total_lines)
    {
        rt_kprintf("\nError:Required lines are more than total number of lines\n");
        close(fd);
        return -1;
    }
    rt_kprintf("Required Number of lines:%d\n", required_lines);

    target_line = total_lines - required_lines;
    lseek(fd, 0, SEEK_SET); /* back to head */

    while ((read(fd, &c, sizeof(char))) > 0)
    {
        if (current_line >= target_line)
        {
            rt_kprintf("%c", c);
        }
        if (c == '\n')
        {
            current_line++;
        }
    }
    rt_kprintf("\n");

    close(fd);
    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_tail, tail, print the last N - lines data of the given file);

#endif /* defined(RT_USING_FINSH) && defined(DFS_USING_POSIX) */
