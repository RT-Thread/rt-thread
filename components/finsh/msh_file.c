/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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
#ifdef RT_USING_DFS_V2
#include <dfs_mnt.h>
#endif

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

#ifdef RT_USING_DFS_V2
static int cmd_ln(int argc, char **argv)
{
    if (argc < 3)
    {
        rt_kprintf("Usage: ln target link_name\n");
        rt_kprintf("Make symbolic link between files.\n");
    }
    else
    {
        for(int i = 0; i + 3 <= argc; i ++)
        {
            dfs_file_symlink(argv[1], argv[2 + i]);
        }
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_ln, ln, Make symbolic link between files);

static int cmd_link(int argc, char **argv)
{
    if (argc < 3)
    {
        rt_kprintf("Usage: link target link_name\n");
        rt_kprintf("Make link between files.\n");
    }
    else
    {
        for(int i = 0; i + 3 <= argc; i ++)
        {
            dfs_file_link(argv[1], argv[2 + i]);
        }
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_link, link, Make link between files);
#endif

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
            if (strlen(pathname) + 1 + strlen(dirent->d_name) > DFS_PATH_MAX)
            {
                rt_kprintf("cannot remove '%s/%s', path too long.\n", pathname, dirent->d_name);
                continue;
            }
            rt_sprintf(full_path, "%s/%s", pathname, dirent->d_name);
            if (dirent->d_type != DT_DIR)
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
            else
            {
                directory_delete_for_msh(full_path, f, v);
            }
        }
    }
    closedir(dir);
    rt_free(full_path);
    if (rmdir(pathname) != 0)
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
#ifdef RT_USING_DFS_V2
        if (dfs_file_lstat(argv[index], &s) == 0)
#else
        if (stat(argv[index], &s) == 0)
#endif
        {
            if (S_ISDIR(s.st_mode))
            {
                if (r == 0)
                    rt_kprintf("cannot remove '%s': Is a directory\n", argv[index]);
                else
                    directory_delete_for_msh(argv[index], f, v);
            }
            else
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

/*
 * If no argument is specified, display the mount history;
 * If there are 3 arguments, mount the filesystem.
 * The order of the arguments is:
 * argv[1]: device name
 * argv[2]: mountpoint path
 * argv[3]: filesystem type
 */
static int cmd_mount(int argc, char **argv)
{
    if (argc == 1)
    {
#ifdef RT_USING_DFS_V2
        /* display the mount history */
        rt_kprintf("filesystem  device  mountpoint  refcount\n");
        rt_kprintf("----------  ------  ----------  --------\n");

        dfs_mnt_list(RT_NULL);
#else
        extern struct dfs_filesystem filesystem_table[];
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
#endif
        return 0;
    }
    else if (argc == 4)
    {
        char *device = argv[1];
        char *path = argv[2];
        char *fstype = argv[3];
        char *data = 0;

        /* mount a filesystem to the specified directory */
        rt_kprintf("mount device %s(%s) onto %s ... ", device, fstype, path);
        if (strcmp(fstype, "nfs") == 0)
        {
            data = argv[1];
            device = 0;
        }

        if (dfs_mount(device, path, fstype, 0, data) == 0)
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
    else if (argc == 3)
    {
        char *path = argv[1];
        char *fstype = argv[2];

        /* mount a filesystem to the specified directory */
        rt_kprintf("mount (%s) onto %s ... ", fstype, path);
        if (dfs_mount(NULL, path, fstype, 0, 0) == 0)
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
#ifndef RT_USING_DFS_V2
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
#else
    int flags = 0;
    char *path = argv[1];

    if (argc < 2)
    {
        rt_kprintf("Usage: unmount [-f] <mountpoint>.\n");
        return -1;
    }

    if (argc > 2)
    {
        flags = strcmp(argv[1], "-f") == 0 ? MNT_FORCE : 0;
        path  = argv[2];
    }

    rt_kprintf("unmount %s ... ", path);
    if (dfs_umount(path, flags) < 0)
    {
        rt_kprintf("failed!\n");
        return -1;
    }
    else
    {
        rt_kprintf("succeed!\n");
        return 0;
    }
#endif
}
MSH_CMD_EXPORT_ALIAS(cmd_umount, umount, Unmount the mountpoint);

static int cmd_df(int argc, char **argv)
{
#ifndef RT_USING_DFS_V2
    extern int df(const char *path);

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
#endif

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

#ifdef RT_USING_DFS_V2

static void directory_setattr(const char *pathname, struct dfs_attr *attr, char f, char v)
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
            rt_kprintf("cannot open '%s'\n", pathname);
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
            if (strlen(pathname) + 1 + strlen(dirent->d_name) > DFS_PATH_MAX)
            {
                rt_kprintf("'%s/%s' setattr failed, path too long.\n", pathname, dirent->d_name);
                continue;
            }
            rt_sprintf(full_path, "%s/%s", pathname, dirent->d_name);
            if (dirent->d_type == DT_REG)
            {
                if (dfs_file_setattr(full_path, attr) != 0)
                {
                    if (f == 0)
                    {
                        rt_kprintf("'%s' setattr failed, no such file or directory\n", full_path);
                    }
                }
                else if (v)
                {
                    rt_kprintf("'%s' setattr 0x%X\n", full_path, attr->st_mode);
                }
            }
            else if (dirent->d_type == DT_DIR)
            {
                directory_setattr(full_path, attr, f, v);
            }
        }
    }
    closedir(dir);
    rt_free(full_path);
    if (dfs_file_setattr(pathname, attr) != 0)
    {
        if (f == 0)
        {
            rt_kprintf("'%s' setattr failed, no such file or directory\n", pathname);
        }
    }
    else if (v)
    {
        rt_kprintf("'%s' setattr 0x%X\n", pathname, attr->st_mode);
    }
}

static int cmd_chmod(int argc, char **argv)
{
    if (argc < 3)
    {
        rt_kprintf("Usage: chmod [OPTION]... MODE[,MODE]... FILE...\n");
        rt_kprintf("  chmod [-f|v|r] [u|g|o|a][+/-/=][r|w|x] file...\n");
        rt_kprintf("  -f  suppress most error messages\n");
        rt_kprintf("  -v  output a diagnostic for every file processed\n");
        rt_kprintf("  -r  change files and directories recursively\n");
        rt_kprintf("Change the mode of each FILE to MODE.\n");
    }
    else
    {
        int argv_c = 1;
        char f = 0, r = 0, v = 0;

        if (argv[argv_c][0] == '-')
        {
            for (int i = 1; argv[argv_c][i]; i++)
            {
                switch (argv[argv_c][i])
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
                default:
                    rt_kprintf("Error: Bad option: %c\n", argv[argv_c][i]);
                    return 0;
                }
            }
            argv_c++;
        }

        if (argc - argv_c > 1)
        {
            int U = 1, G = 2, O = 4, ALL = 7;
            int off[5] = {0, 6, 3, 0, 0};
            int ADD = 1, SUB = 2, SET = 4;
            int R = 4, W = 2, X = 1;
            int user[3] = {0}, change[3] = {0}, mode[3] = {0};
            struct dfs_attr attr;
            char *cmd = argv[argv_c];
            int index = 0, num = 0;

            while (cmd[index] != '\0')
            {
                switch (cmd[index])
                {
                case 'u':
                    user[num] |= U;
                    break;
                case 'g':
                    user[num] |= G;
                    break;
                case 'o':
                    user[num] |= O;
                    break;
                case 'a':
                    user[num] |= ALL;
                    break;
                case ',':
                    if (num < 2)
                        num++;
                    break;
                }
                index++;
            }

            index = 0;
            num = 0;

            while (cmd[index] != '\0')
            {
                switch (cmd[index])
                {
                case '+':
                    change[num] = ADD;
                    break;
                case '-':
                    change[num] = SUB;
                    break;
                case '=':
                    change[num] = SET;
                    break;
                case ',':
                    if (num < 2)
                        num++;
                    break;
                }
                index++;
            }

            index = 0;
            num = 0;

            while (cmd[index] != '\0')
            {
                switch (cmd[index])
                {
                case 'r':
                    mode[num] |= R;
                    break;
                case 'w':
                    mode[num] |= W;
                    break;
                case 'x':
                    mode[num] |= X;
                    break;
                case ',':
                    if (num < 2)
                        num++;
                    break;
                }
                index++;
            }

            attr.st_mode = 0;

            for (int i = 0; i <= num; i++)
            {
                if (change[i] == ADD)
                {
                    if (user[i] & U)
                    {
                        attr.st_mode |= mode[i] << off[user[i] & U];
                    }

                    if (user[i] & G)
                    {
                        attr.st_mode |= mode[i] << off[user[i] & G];
                    }

                    if (user[i] & O)
                    {
                        attr.st_mode |= mode[i] << off[user[i] & O];
                    }
                }
                else if (change[i] == SUB)
                {
                    if (user[i] & U)
                    {
                        attr.st_mode &= ~(mode[i] << off[user[i] & U]);
                    }

                    if (user[i] & G)
                    {
                        attr.st_mode &= ~(mode[i] << off[user[i] & G]);
                    }

                    if (user[i] & O)
                    {
                        attr.st_mode &= ~(mode[i] << off[user[i] & O]);
                    }
                }
                else if (change[i] == SET)
                {
                    if (user[i] & U)
                    {
                        attr.st_mode &= ~(7 << off[user[i] & U]);
                        attr.st_mode |= mode[i] << off[user[i] & U];
                    }

                    if (user[i] & G)
                    {
                        attr.st_mode &= ~(7 << off[user[i] & G]);
                        attr.st_mode |= mode[i] << off[user[i] & G];
                    }

                    if (user[i] & O)
                    {
                        attr.st_mode &= ~(7 << off[user[i] & O]);
                        attr.st_mode |= mode[i] << off[user[i] & O];
                    }
                }
            }

            argv_c++;

            for (int i = argv_c; i < argc; i++)
            {
                if (r)
                {
                    struct stat s;
                    if (stat(argv[i], &s) == 0)
                    {
                        if (S_ISDIR(s.st_mode))
                        {
                            directory_setattr(argv[i], &attr, f, v);
                        }
                        else if (f == 0)
                        {
                            rt_kprintf("'%s' is not a directory\n", argv[i]);
                        }
                    }
                }
                else
                {
                    if (dfs_file_setattr(argv[i], &attr) != 0)
                    {
                        if (f == 0)
                        {
                            rt_kprintf("'%s' setattr failed, no such file or directory\n", argv[i]);
                        }
                    }
                    else if (v)
                    {
                        rt_kprintf("'%s' setattr 0x%X\n", argv[i], attr.st_mode);
                    }
                }
            }
        }
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_chmod, chmod, Change the file attr.);

#endif

#endif /* defined(RT_USING_FINSH) && defined(DFS_USING_POSIX) */
