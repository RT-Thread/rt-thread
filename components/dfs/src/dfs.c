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

    /* clear filesystem operations table */
    memset((void *)filesystem_operation_table, 0, sizeof(filesystem_operation_table));
    /* clear filesystem table */
    memset(filesystem_table, 0, sizeof(filesystem_table));
    /* clean fd table */
    memset(&_fdtab, 0, sizeof(_fdtab));

    /* create device filesystem lock */
    rt_mutex_init(&fslock, "fslock", RT_IPC_FLAG_FIFO);

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

/**
 * this function will lock device file system.
 *
 * @note please don't invoke it on ISR.
 */
void dfs_unlock(void)
{
    rt_mutex_release(&fslock);
}

static int fd_alloc(struct dfs_fdtable *fdt, int startfd)
{
    int idx;

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
        int cnt, index;
        struct dfs_fd **fds;

        /* increase the number of FD with 4 step length */
        cnt = fdt->maxfd + 4;
        cnt = cnt > DFS_FD_MAX? DFS_FD_MAX : cnt;

        fds = rt_realloc(fdt->fds, cnt * sizeof(struct dfs_fd *));
        if (fds == NULL) goto __exit; /* return fdt->maxfd */

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
        fdt->fds[idx] = rt_calloc(1, sizeof(struct dfs_fd));
        if (fdt->fds[idx] == RT_NULL)
            idx = fdt->maxfd;
    }

__exit:
    return idx;
}

/**
 * @ingroup Fd
 * This function will allocate a file descriptor.
 *
 * @return -1 on failed or the allocated file descriptor.
 */
int fd_new(void)
{
    struct dfs_fd *d;
    int idx;
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();
    /* lock filesystem */
    dfs_lock();

    /* find an empty fd entry */
    idx = fd_alloc(fdt, 0);

    /* can't find an empty fd entry */
    if (idx == fdt->maxfd)
    {
        idx = -(1 + DFS_FD_OFFSET);
        LOG_E( "DFS fd new is failed! Could not found an empty fd entry.");
        goto __result;
    }

    d = fdt->fds[idx];
    d->ref_count = 1;
    d->magic = DFS_FD_MAGIC;

__result:
    dfs_unlock();
    return idx + DFS_FD_OFFSET;
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
struct dfs_fd *fd_get(int fd)
{
    struct dfs_fd *d;
    struct dfs_fdtable *fdt;

#if defined(RT_USING_DFS_DEVFS) && defined(RT_USING_POSIX)
    if ((0 <= fd) && (fd <= 2))
        fd = libc_stdio_get_console();
#endif

    fdt = dfs_fdtable_get();
    fd = fd - DFS_FD_OFFSET;
    if (fd < 0 || fd >= (int)fdt->maxfd)
        return NULL;

    dfs_lock();
    d = fdt->fds[fd];

    /* check dfs_fd valid or not */
    if ((d == NULL) || (d->magic != DFS_FD_MAGIC))
    {
        dfs_unlock();
        return NULL;
    }

    /* increase the reference count */
    d->ref_count ++;
    dfs_unlock();

    return d;
}

/**
 * @ingroup Fd
 *
 * This function will put the file descriptor.
 */
void fd_put(struct dfs_fd *fd)
{
    RT_ASSERT(fd != NULL);

    dfs_lock();

    fd->ref_count --;

    /* clear this fd entry */
    if (fd->ref_count == 0)
    {
        int index;
        struct dfs_fdtable *fdt;

        fdt = dfs_fdtable_get();
        for (index = 0; index < (int)fdt->maxfd; index ++)
        {
            if (fdt->fds[index] == fd)
            {
                rt_free(fd);
                fdt->fds[index] = 0;
                break;
            }
        }
    }
    dfs_unlock();
}

/**
 * @ingroup Fd
 *
 * This function will return whether this file has been opend.
 *
 * @param pathname the file path name.
 *
 * @return 0 on file has been open successfully, -1 on open failed.
 */
int fd_is_open(const char *pathname)
{
    char *fullpath;
    unsigned int index;
    struct dfs_filesystem *fs;
    struct dfs_fd *fd;
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();
    fullpath = dfs_normalize_path(NULL, pathname);
    if (fullpath != NULL)
    {
        char *mountpath;
        fs = dfs_filesystem_lookup(fullpath);
        if (fs == NULL)
        {
            /* can't find mounted file system */
            rt_free(fullpath);

            return -1;
        }

        /* get file path name under mounted file system */
        if (fs->path[0] == '/' && fs->path[1] == '\0')
            mountpath = fullpath;
        else
            mountpath = fullpath + strlen(fs->path);

        dfs_lock();

        for (index = 0; index < fdt->maxfd; index++)
        {
            fd = fdt->fds[index];
            if (fd == NULL || fd->fops == NULL || fd->path == NULL) continue;

            if (fd->fs == fs && strcmp(fd->path, mountpath) == 0)
            {
                /* found file in file descriptor table */
                rt_free(fullpath);
                dfs_unlock();

                return 0;
            }
        }
        dfs_unlock();

        rt_free(fullpath);
    }

    return -1;
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
        fullpath = rt_malloc(strlen(directory) + strlen(filename) + 2);

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
struct dfs_fdtable* dfs_fdtable_get(void)
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

        if (fd && fd->fops)
        {
            rt_kprintf("%2d ", index);
            if (fd->type == FT_DIRECTORY)    rt_kprintf("%-7.7s ", "dir");
            else if (fd->type == FT_REGULAR) rt_kprintf("%-7.7s ", "file");
            else if (fd->type == FT_SOCKET)  rt_kprintf("%-7.7s ", "socket");
            else if (fd->type == FT_USER)    rt_kprintf("%-7.7s ", "user");
            else rt_kprintf("%-8.8s ", "unknown");
            rt_kprintf("%3d ", fd->ref_count);
            rt_kprintf("%04x  ", fd->magic);
            if (fd->path)
            {
                rt_kprintf("%s\n", fd->path);
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
#endif
/*@}*/

