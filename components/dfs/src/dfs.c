/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2005-02-22     Bernard      The first version.
 * 2017-12-11     Bernard      Use rt_free to instead of free in fd_is_open().
 * 2018-03-20     Heyuanjie    dynamic allocation FD
 */

#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include "dfs_private.h"
#ifdef RT_USING_LWP
#include <lwp.h>
#endif

#if defined(RT_USING_DFS_DEVFS) && defined(RT_USING_POSIX)
#include <libc.h>
#endif

/* Global variables */
const struct dfs_filesystem_ops *filesystem_operation_table[DFS_FILESYSTEM_TYPES_MAX];
struct dfs_filesystem filesystem_table[DFS_FILESYSTEMS_MAX];

/* device filesystem lock */
static struct rt_mutex fslock;
static struct rt_mutex fdlock;

#ifdef DFS_USING_WORKDIR
char working_directory[DFS_PATH_MAX] = {"/"};
#endif

static struct dfs_fdtable _fdtab;
static int  fd_alloc(struct dfs_fdtable *fdt, int startfd);

/**
 * @addtogroup DFS
 */

/*@{*/

/**
 * this function will initialize device file system.
 */
int dfs_init(void)
{
    static rt_bool_t init_ok = RT_FALSE;

    if (init_ok)
    {
        rt_kprintf("dfs already init.\n");
        return 0;
    }

    /* init fnode hash table */
    dfs_fnode_mgr_init();

    /* clear filesystem operations table */
    memset((void *)filesystem_operation_table, 0, sizeof(filesystem_operation_table));
    /* clear filesystem table */
    memset(filesystem_table, 0, sizeof(filesystem_table));
    /* clean fd table */
    memset(&_fdtab, 0, sizeof(_fdtab));

    /* create device filesystem lock */
    rt_mutex_init(&fslock, "fslock", RT_IPC_FLAG_FIFO);
    rt_mutex_init(&fdlock, "fdlock", RT_IPC_FLAG_FIFO);

#ifdef DFS_USING_WORKDIR
    /* set current working directory */
    memset(working_directory, 0, sizeof(working_directory));
    working_directory[0] = '/';
#endif

#ifdef RT_USING_DFS_DEVFS
    {
        extern int devfs_init(void);

        /* if enable devfs, initialize and mount it as soon as possible */
        devfs_init();

        dfs_mount(NULL, "/dev", "devfs", 0, 0);
    }
#endif

    init_ok = RT_TRUE;

    return 0;
}
INIT_PREV_EXPORT(dfs_init);

/**
 * this function will lock device file system.
 *
 * @note please don't invoke it on ISR.
 */
void dfs_lock(void)
{
    rt_err_t result = -RT_EBUSY;

    while (result == -RT_EBUSY)
    {
        result = rt_mutex_take(&fslock, RT_WAITING_FOREVER);
    }

    if (result != RT_EOK)
    {
        RT_ASSERT(0);
    }
}

void dfs_fd_lock(void)
{
    rt_err_t result = -RT_EBUSY;

    while (result == -RT_EBUSY)
    {
        result = rt_mutex_take(&fdlock, RT_WAITING_FOREVER);
    }

    if (result != RT_EOK)
    {
        RT_ASSERT(0);
    }
}

/**
 * this function will lock device file system.
 *
 * @note please don't invoke it on ISR.
 */
void dfs_unlock(void)
{
    rt_mutex_release(&fslock);
}

void dfs_fd_unlock(void)
{
    rt_mutex_release(&fdlock);
}

static int fd_alloc(struct dfs_fdtable *fdt, int startfd)
{
    int idx = 0;
    struct dfs_fd *fd = NULL;

    /* find an empty fd entry */
    for (idx = startfd; idx < (int)fdt->maxfd; idx++)
    {
        if (fdt->fds[idx] == RT_NULL)
            break;
        if (fdt->fds[idx]->ref_count == 0)
            break;
    }

    /* allocate a larger FD container */
    if (idx == fdt->maxfd && fdt->maxfd < DFS_FD_MAX)
    {
        int cnt = 0;
        int index = 0;
        struct dfs_fd **fds = NULL;

        /* increase the number of FD with 4 step length */
        cnt = fdt->maxfd + 4;
        cnt = cnt > DFS_FD_MAX ? DFS_FD_MAX : cnt;

        fds = (struct dfs_fd **)rt_realloc(fdt->fds, cnt * sizeof(struct dfs_fd *));
        if (fds == NULL) /* return fdt->maxfd */
        {
            return fdt->maxfd;
        }

        /* clean the new allocated fds */
        for (index = fdt->maxfd; index < cnt; index ++)
        {
            fds[index] = NULL;
        }

        fdt->fds   = fds;
        fdt->maxfd = cnt;
    }

    /* allocate  'struct dfs_fd' */
    if (idx < (int)fdt->maxfd && fdt->fds[idx] == RT_NULL)
    {
        fd = (struct dfs_fd *)rt_calloc(1, sizeof(struct dfs_fd));
        if (!fd)
        {
            return fdt->maxfd;
        }
        fd->ref_count = 1;
        fd->magic = DFS_FD_MAGIC;
        fd->fnode = NULL;
        fd->idx = idx;
        fdt->fds[idx] = fd;
    }

    return idx;
}

/**
 * @ingroup Fd
 * This function will allocate a file descriptor.
 *
 * @return -1 on failed or the allocated file descriptor.
 */
int fdt_fd_new(struct dfs_fdtable *fdt)
{
    int idx = 0;

    /* lock filesystem */
    dfs_fd_lock();

    /* find an empty fd entry */
    idx = fd_alloc(fdt, 0);

    /* can't find an empty fd entry */
    if (idx == fdt->maxfd)
    {
        idx = -(1 + DFS_FD_OFFSET);
        LOG_E("DFS fd new is failed! Could not found an empty fd entry.");
        goto __result;
    }

__result:
    dfs_fd_unlock();
    return idx + DFS_FD_OFFSET;
}

int fd_new(void)
{
    struct dfs_fdtable *fdt = NULL;

    fdt = dfs_fdtable_get();
    return fdt_fd_new(fdt);
}

/**
 * @ingroup Fd
 *
 * This function will return a file descriptor structure according to file
 * descriptor.
 *
 * @return NULL on on this file descriptor or the file descriptor structure
 * pointer.
 */

struct dfs_fd *fdt_fd_get(struct dfs_fdtable* fdt, int fd, int ref_inc_nr)
{
    struct dfs_fd *d;

#if defined(RT_USING_DFS_DEVFS) && defined(RT_USING_POSIX)
    if ((0 <= fd) && (fd <= 2))
        fd = libc_stdio_get_console();
#endif

    fd = fd - DFS_FD_OFFSET;
    if (fd < 0 || fd >= (int)fdt->maxfd)
        return NULL;

    dfs_fd_lock();
    d = fdt->fds[fd];

    /* check dfs_fd valid or not */
    if ((d == NULL) || (d->magic != DFS_FD_MAGIC))
    {
        dfs_fd_unlock();
        return NULL;
    }

    d->ref_count += ref_inc_nr;

    dfs_fd_unlock();

    return d;
}

struct dfs_fd *fd_get(int fd, int ref_inc_nr)
{
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();
    return fdt_fd_get(fdt, fd, ref_inc_nr);
}

/**
 * @ingroup Fd
 *
 * This function will put the file descriptor.
 */
void fdt_fd_release(struct dfs_fdtable* fdt, struct dfs_fd *fd)
{
    int idx = -1;

    RT_ASSERT(fdt != NULL);

    dfs_fd_lock();

    if (fd == NULL)
    {
        dfs_fd_unlock();
        return;
    }

    idx = fd->idx;
    /* check fd */
    RT_ASSERT(fdt->fds[idx] == fd);
    RT_ASSERT(fd->magic == DFS_FD_MAGIC);

    fd->ref_count--;

    /* clear this fd entry */
    if (fd->ref_count == 0)
    {
        struct dfs_fnode *fnode = fd->fnode;
        if (fnode)
        {
            fnode->ref_count--;
        }
        rt_free(fd);
        fdt->fds[idx] = 0;
    }
    dfs_fd_unlock();
}

void fd_release(struct dfs_fd *fd)
{
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();
    fdt_fd_release(fdt, fd);
}

int fd_dup(int oldfd)
{
    int newfd = -1;
    struct dfs_fdtable *fdt = NULL;

    dfs_fd_lock();
    /* check old fd */
    fdt = dfs_fdtable_get();
    oldfd -= DFS_FD_OFFSET;
    if ((oldfd < 0) || (oldfd >= fdt->maxfd))
    {
        goto exit;
    }
    if (!fdt->fds[oldfd])
    {
        goto exit;
    }
    /* get a new fd */
    newfd = fd_new();
    if (newfd < 0)
    {
        goto exit;
    }

    newfd -= DFS_FD_OFFSET;
    /* replace newfd ref */
    rt_free(fdt->fds[newfd]);
    fdt->fds[newfd] = fdt->fds[oldfd];
    /* inc ref_count */
    fdt->fds[newfd]->ref_count++;
exit:
    dfs_fd_unlock();
    return (newfd == -1 ? newfd : newfd + DFS_FD_OFFSET);
}

void fd_init(struct dfs_fd *fd)
{
    if (fd)
    {
        fd->idx = -1;
        fd->magic = DFS_FD_MAGIC;
        fd->ref_count = 1;
        fd->pos = 0;
        fd->fnode = NULL;
        fd->data = NULL;
    }
}

/**
 * this function will return a sub-path name under directory.
 *
 * @param directory the parent directory.
 * @param filename the filename.
 *
 * @return the subdir pointer in filename
 */
const char *dfs_subdir(const char *directory, const char *filename)
{
    const char *dir;

    if (strlen(directory) == strlen(filename)) /* it's a same path */
        return NULL;

    dir = filename + strlen(directory);
    if ((*dir != '/') && (dir != filename))
    {
        dir --;
    }

    return dir;
}
RTM_EXPORT(dfs_subdir);

/**
 * this function will normalize a path according to specified parent directory
 * and file name.
 *
 * @param directory the parent path
 * @param filename the file name
 *
 * @return the built full file path (absolute path)
 */
char *dfs_normalize_path(const char *directory, const char *filename)
{
    char *fullpath;
    char *dst0, *dst, *src;

    /* check parameters */
    RT_ASSERT(filename != NULL);

#ifdef DFS_USING_WORKDIR
    if (directory == NULL) /* shall use working directory */
        directory = &working_directory[0];
#else
    if ((directory == NULL) && (filename[0] != '/'))
    {
        rt_kprintf(NO_WORKING_DIR);

        return NULL;
    }
#endif

    if (filename[0] != '/') /* it's a absolute path, use it directly */
    {
        fullpath = (char *)rt_malloc(strlen(directory) + strlen(filename) + 2);

        if (fullpath == NULL)
            return NULL;

        /* join path and file name */
        rt_snprintf(fullpath, strlen(directory) + strlen(filename) + 2,
                    "%s/%s", directory, filename);
    }
    else
    {
        fullpath = rt_strdup(filename); /* copy string */

        if (fullpath == NULL)
            return NULL;
    }

    src = fullpath;
    dst = fullpath;

    dst0 = dst;
    while (1)
    {
        char c = *src;

        if (c == '.')
        {
            if (!src[1]) src ++; /* '.' and ends */
            else if (src[1] == '/')
            {
                /* './' case */
                src += 2;

                while ((*src == '/') && (*src != '\0'))
                    src ++;
                continue;
            }
            else if (src[1] == '.')
            {
                if (!src[2])
                {
                    /* '..' and ends case */
                    src += 2;
                    goto up_one;
                }
                else if (src[2] == '/')
                {
                    /* '../' case */
                    src += 3;

                    while ((*src == '/') && (*src != '\0'))
                        src ++;
                    goto up_one;
                }
            }
        }

        /* copy up the next '/' and erase all '/' */
        while ((c = *src++) != '\0' && c != '/')
            *dst ++ = c;

        if (c == '/')
        {
            *dst ++ = '/';
            while (c == '/')
                c = *src++;

            src --;
        }
        else if (!c)
            break;

        continue;

up_one:
        dst --;
        if (dst < dst0)
        {
            rt_free(fullpath);
            return NULL;
        }
        while (dst0 < dst && dst[-1] != '/')
            dst --;
    }

    *dst = '\0';

    /* remove '/' in the end of path if exist */
    dst --;
    if ((dst != fullpath) && (*dst == '/'))
        *dst = '\0';

    /* final check fullpath is not empty, for the special path of lwext "/.." */
    if ('\0' == fullpath[0])
    {
        fullpath[0] = '/';
        fullpath[1] = '\0';
    }

    return fullpath;
}
RTM_EXPORT(dfs_normalize_path);

/**
 * This function will get the file descriptor table of current process.
 */
struct dfs_fdtable *dfs_fdtable_get(void)
{
    struct dfs_fdtable *fdt;
#ifdef RT_USING_LWP
    struct rt_lwp *lwp;

    lwp = (struct rt_lwp *)rt_thread_self()->lwp;
    if (lwp)
        fdt = &lwp->fdt;
    else
        fdt = &_fdtab;
#else
    fdt = &_fdtab;
#endif

    return fdt;
}

struct dfs_fdtable *dfs_fdtable_get_global(void)
{
    return &_fdtab;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
int list_fd(void)
{
    int index;
    struct dfs_fdtable *fd_table;

    fd_table = dfs_fdtable_get();
    if (!fd_table) return -1;

    rt_enter_critical();

    rt_kprintf("fd type    ref magic  path\n");
    rt_kprintf("-- ------  --- ----- ------\n");
    for (index = 0; index < (int)fd_table->maxfd; index ++)
    {
        struct dfs_fd *fd = fd_table->fds[index];

        if (fd && fd->fnode->fops)
        {
            rt_kprintf("%2d ", index + DFS_FD_OFFSET);
            if (fd->fnode->type == FT_DIRECTORY)    rt_kprintf("%-7.7s ", "dir");
            else if (fd->fnode->type == FT_REGULAR) rt_kprintf("%-7.7s ", "file");
            else if (fd->fnode->type == FT_SOCKET)  rt_kprintf("%-7.7s ", "socket");
            else if (fd->fnode->type == FT_USER)    rt_kprintf("%-7.7s ", "user");
            else if (fd->fnode->type == FT_DEVICE)   rt_kprintf("%-7.7s ", "device");
            else rt_kprintf("%-8.8s ", "unknown");
            rt_kprintf("%3d ", fd->fnode->ref_count);
            rt_kprintf("%04x  ", fd->magic);
            if (fd->fnode->path)
            {
                rt_kprintf("%s\n", fd->fnode->path);
            }
            else
            {
                rt_kprintf("\n");
            }
        }
    }
    rt_exit_critical();

    return 0;
}
MSH_CMD_EXPORT(list_fd, list file descriptor);

/*
 * If no argument is specified, display the mount history;
 * If there are 3 arguments, mount the filesystem.
 * The order of the arguments is:
 * argv[1]: device name
 * argv[2]: mountpoint path
 * argv[3]: filesystem type
 */
int mount(int argc, char *argv[])
{
    if (argc == 1) /* display the mount history */
    {
        struct dfs_filesystem *iter;

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
    { /* mount a filesystem to the specified directory */
        char *device = argv[1];
        char *path = argv[2];
        char *fstype = argv[3];

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
MSH_CMD_EXPORT(mount, mount<device><mountpoint><fstype>);

/* unmount the filesystem from the specified mountpoint */
int unmount(int argc, char *argv[])
{
    if (argc != 2)
    {
        rt_kprintf("Usage: unmount <mountpoint>.\n");
        return -1;
    }

    char *path = argv[1];

    rt_kprintf("unmount %s ... ", path);
    if (dfs_unmount(path) < 0)
    {
        rt_kprintf("failed!\n");
        return -1;
    } else {
        rt_kprintf("succeed!\n");
        return 0;
    }
}
MSH_CMD_EXPORT(unmount, unmount the mountpoint);

#endif
/*@}*/
