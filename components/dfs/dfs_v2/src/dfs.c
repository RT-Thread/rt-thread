/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
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
#ifdef RT_USING_SMART
#include <lwp.h>
#endif

#ifdef RT_USING_POSIX_STDIO
#include <libc.h>
#endif /* RT_USING_POSIX_STDIO */

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

    /* init vnode hash table */
    dfs_vnode_mgr_init();

    /* clear filesystem operations table */
    rt_memset((void *)filesystem_operation_table, 0, sizeof(filesystem_operation_table));
    /* clear filesystem table */
    rt_memset(filesystem_table, 0, sizeof(filesystem_table));
    /* clean fd table */
    rt_memset(&_fdtab, 0, sizeof(_fdtab));

    /* create device filesystem lock */
    rt_mutex_init(&fslock, "fslock", RT_IPC_FLAG_PRIO);
    rt_mutex_init(&fdlock, "fdlock", RT_IPC_FLAG_PRIO);

#ifdef DFS_USING_WORKDIR
    /* set current working directory */
    rt_memset(working_directory, 0, sizeof(working_directory));
    working_directory[0] = '/';
#endif

#ifdef RT_USING_DFS_TMPFS
    {
        extern int dfs_tmpfs_init(void);
        dfs_tmpfs_init();
    }
#endif

#ifdef RT_USING_DFS_DEVFS
    {
        extern int devfs_init(void);

        /* if enable devfs, initialize and mount it as soon as possible */
        devfs_init();

        dfs_mount(NULL, "/dev", "devfs", 0, 0);
    }
#if defined(RT_USING_DEV_BUS) && defined(RT_USING_DFS_TMPFS)
    mkdir("/dev/shm", 0x777);
    if (dfs_mount(RT_NULL, "/dev/shm", "tmp", 0, 0) != 0)
    {
        rt_kprintf("Dir /dev/shm mount failed!\n");
    }
#endif
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

void dfs_file_lock(void)
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

#ifdef DFS_USING_POSIX

void dfs_file_unlock(void)
{
    rt_mutex_release(&fdlock);
}

static int fd_slot_expand(struct dfs_fdtable *fdt, int fd)
{
    int nr;
    int index;
    struct dfs_file **fds = NULL;

    if (fd < fdt->maxfd)
    {
        return fd;
    }
    if (fd >= DFS_FD_MAX)
    {
        return -1;
    }

    nr = ((fd + 4) & ~3);
    if (nr > DFS_FD_MAX)
    {
        nr = DFS_FD_MAX;
    }
    fds = (struct dfs_file **)rt_realloc(fdt->fds, nr * sizeof(struct dfs_file *));
    if (!fds)
    {
        return -1;
    }

    /* clean the new allocated fds */
    for (index = fdt->maxfd; index < nr; index++)
    {
        fds[index] = NULL;
    }
    fdt->fds   = fds;
    fdt->maxfd = nr;

    return fd;
}

static int fd_slot_alloc(struct dfs_fdtable *fdt, int startfd)
{
    int idx;

    /* find an empty fd slot */
    for (idx = startfd; idx < (int)fdt->maxfd; idx++)
    {
        if (fdt->fds[idx] == RT_NULL)
        {
            return idx;
        }
    }

    idx = fdt->maxfd;
    if (idx < startfd)
    {
        idx = startfd;
    }
    if (fd_slot_expand(fdt, idx) < 0)
    {
        return -1;
    }
    return idx;
}
static int fd_alloc(struct dfs_fdtable *fdt, int startfd)
{
    int idx;
    struct dfs_file *fd = NULL;

    idx = fd_slot_alloc(fdt, startfd);

    /* allocate  'struct dfs_file' */
    if (idx < 0)
    {
        return -1;
    }
    fd = (struct dfs_file *)rt_calloc(1, sizeof(struct dfs_file));
    if (!fd)
    {
        return -1;
    }
    fd->ref_count = 1;
    fd->magic = DFS_FD_MAGIC;
    fd->vnode = NULL;
    fdt->fds[idx] = fd;

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
    int idx;

    /* lock filesystem */
    dfs_file_lock();

    /* find an empty fd entry */
    idx = fd_alloc(fdt, DFS_STDIO_OFFSET);

    /* can't find an empty fd entry */
    if (idx < 0)
    {
        LOG_E("DFS fd new is failed! Could not found an empty fd entry.");
    }

    dfs_file_unlock();
    return idx;
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

struct dfs_file *fdt_fd_get(struct dfs_fdtable* fdt, int fd)
{
    struct dfs_file *d;

    if (fd < 0 || fd >= (int)fdt->maxfd)
    {
        return NULL;
    }

    dfs_file_lock();
    d = fdt->fds[fd];

    /* check dfs_file valid or not */
    if ((d == NULL) || (d->magic != DFS_FD_MAGIC))
    {
        dfs_file_unlock();
        return NULL;
    }

    dfs_file_unlock();

    return d;
}

struct dfs_file *fd_get(int fd)
{
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();
    return fdt_fd_get(fdt, fd);
}

/**
 * @ingroup Fd
 *
 * This function will put the file descriptor.
 */
void fdt_fd_release(struct dfs_fdtable* fdt, int fd)
{
    struct dfs_file *fd_slot = NULL;

    RT_ASSERT(fdt != NULL);

    dfs_file_lock();

    if ((fd < 0) || (fd >= fdt->maxfd))
    {
        dfs_file_unlock();
        return;
    }

    fd_slot = fdt->fds[fd];
    if (fd_slot == NULL)
    {
        dfs_file_unlock();
        return;
    }
    fdt->fds[fd] = NULL;

    /* check fd */
    RT_ASSERT(fd_slot->magic == DFS_FD_MAGIC);

    fd_slot->ref_count--;

    /* clear this fd entry */
    if (fd_slot->ref_count == 0)
    {
        struct dfs_vnode *vnode = fd_slot->vnode;
        if (vnode)
        {
            vnode->ref_count--;
        }
        rt_free(fd_slot);
    }
    dfs_file_unlock();
}

void fd_release(int fd)
{
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();
    fdt_fd_release(fdt, fd);
}

rt_err_t sys_dup(int oldfd)
{
    int newfd = -1;
    struct dfs_fdtable *fdt = NULL;

    dfs_file_lock();
    /* check old fd */
    fdt = dfs_fdtable_get();
    if ((oldfd < 0) || (oldfd >= fdt->maxfd))
    {
        goto exit;
    }
    if (!fdt->fds[oldfd])
    {
        goto exit;
    }
    /* get a new fd */
    newfd = fd_slot_alloc(fdt, DFS_STDIO_OFFSET);
    if (newfd >= 0)
    {
        fdt->fds[newfd] = fdt->fds[oldfd];
        /* inc ref_count */
        fdt->fds[newfd]->ref_count++;
    }
exit:
    dfs_file_unlock();
    return newfd;
}

#endif /* DFS_USING_POSIX */

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
    struct dfs_file *fd;
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
            if (fd == NULL || fd->vnode->fops == NULL || fd->vnode->path == NULL) continue;

            if (fd->vnode->fs == fs && strcmp(fd->vnode->path, mountpath) == 0)
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

rt_err_t sys_dup2(int oldfd, int newfd)
{
    struct dfs_fdtable *fdt = NULL;
    int ret = 0;
    int retfd = -1;

    dfs_file_lock();
    /* check old fd */
    fdt = dfs_fdtable_get();
    if ((oldfd < 0) || (oldfd >= fdt->maxfd))
    {
        goto exit;
    }
    if (!fdt->fds[oldfd])
    {
        goto exit;
    }
    if (newfd < 0)
    {
        goto exit;
    }
    if (newfd >= fdt->maxfd)
    {
        newfd = fd_slot_expand(fdt, newfd);
        if (newfd < 0)
        {
            goto exit;
        }
    }
    if (fdt->fds[newfd] == fdt->fds[oldfd])
    {
        /* ok, return newfd */
        retfd = newfd;
        goto exit;
    }

    if (fdt->fds[newfd])
    {
        ret = dfs_file_close(fdt->fds[newfd]);
        if (ret < 0)
        {
            goto exit;
        }
        fd_release(newfd);
    }

    fdt->fds[newfd] = fdt->fds[oldfd];
    /* inc ref_count */
    fdt->fds[newfd]->ref_count++;
    retfd = newfd;
exit:
    dfs_file_unlock();
    return retfd;
}

static int fd_get_fd_index_form_fdt(struct dfs_fdtable *fdt, struct dfs_file *file)
{
    int fd = -1;

    if (file == RT_NULL)
    {
        return -1;
    }

    dfs_file_lock();

    for(int index = 0; index < (int)fdt->maxfd; index++)
    {
        if(fdt->fds[index] == file)
        {
            fd = index;
            break;
        }
    }

    dfs_file_unlock();

    return fd;
}

int fd_get_fd_index(struct dfs_file *file)
{
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();
    return fd_get_fd_index_form_fdt(fdt, file);
}

int fd_associate(struct dfs_fdtable *fdt, int fd, struct dfs_file *file)
{
    int retfd = -1;

    if (!file)
    {
        return retfd;
    }
    if (!fdt)
    {
        return retfd;
    }

    dfs_file_lock();
    /* check old fd */
    if ((fd < 0) || (fd >= fdt->maxfd))
    {
        goto exit;
    }

    if (fdt->fds[fd])
    {
        goto exit;
    }
    /* inc ref_count */
    file->ref_count++;
    fdt->fds[fd] = file;
    retfd = fd;
exit:
    dfs_file_unlock();
    return retfd;
}

void fd_init(struct dfs_file *fd)
{
    if (fd)
    {
        fd->magic = DFS_FD_MAGIC;
        fd->ref_count = 1;
        fd->pos = 0;
        fd->vnode = NULL;
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
    {
#ifdef RT_USING_SMART
        directory = lwp_getcwd();
#else
        directory = &working_directory[0];
#endif
    }
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
            if (!src[1]) src++; /* '.' and ends */
            else if (src[1] == '/')
            {
                /* './' case */
                src += 2;

                while ((*src == '/') && (*src != '\0'))
                    src++;
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
                        src++;
                    goto up_one;
                }
            }
        }

        /* copy up the next '/' and erase all '/' */
        while ((c = *src++) != '\0' && c != '/')
            *dst++ = c;

        if (c == '/')
        {
            *dst++ = '/';
            while (c == '/')
                c = *src++;

            src--;
        }
        else if (!c)
            break;

        continue;

up_one:
        /* keep the topmost root directory */
        if (dst - dst0 != 1 || dst[-1] != '/')
        {
            dst--;

            if (dst < dst0)
            {
                rt_free(fullpath);
                return NULL;
            }
        }
        while (dst0 < dst && dst[-1] != '/')
            dst--;
    }

    *dst = '\0';

    /* remove '/' in the end of path if exist */
    dst--;
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
#ifdef RT_USING_SMART
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

#ifdef RT_USING_SMART
struct dfs_fdtable *dfs_fdtable_get_pid(int pid)
{
    struct rt_lwp *lwp = RT_NULL;
    struct dfs_fdtable *fdt = RT_NULL;

    lwp = lwp_from_pid(pid);
    if (lwp)
    {
        fdt = &lwp->fdt;
    }

    return fdt;
}
#endif

struct dfs_fdtable *dfs_fdtable_get_global(void)
{
    return &_fdtab;
}

#ifdef RT_USING_FINSH
int list_fd(void)
{
    int index;
    struct dfs_fdtable *fd_table;

    fd_table = dfs_fdtable_get();
    if (!fd_table) return -1;

    dfs_lock();

    rt_kprintf("fd type    ref magic  path\n");
    rt_kprintf("-- ------  --- ----- ------\n");
    for (index = 0; index < (int)fd_table->maxfd; index++)
    {
        struct dfs_file *fd = fd_table->fds[index];

        if (fd && fd->vnode->fops)
        {
            rt_kprintf("%2d ", index);
            if (fd->vnode->type == FT_DIRECTORY)    rt_kprintf("%-7.7s ", "dir");
            else if (fd->vnode->type == FT_REGULAR) rt_kprintf("%-7.7s ", "file");
            else if (fd->vnode->type == FT_SOCKET)  rt_kprintf("%-7.7s ", "socket");
            else if (fd->vnode->type == FT_USER)    rt_kprintf("%-7.7s ", "user");
            else if (fd->vnode->type == FT_DEVICE)  rt_kprintf("%-7.7s ", "device");
            else rt_kprintf("%-8.8s ", "unknown");
            rt_kprintf("%3d ", fd->vnode->ref_count);
            rt_kprintf("%04x  ", fd->magic);
            if (fd->vnode->path)
            {
                rt_kprintf("%s\n", fd->vnode->path);
            }
            else
            {
                rt_kprintf("\n");
            }
        }
    }
    dfs_unlock();

    return 0;
}

#ifdef RT_USING_SMART
static int lsofp(int pid)
{
    int index;
    struct dfs_fdtable *fd_table = RT_NULL;

    if (pid == (-1))
    {
        fd_table = dfs_fdtable_get();
        if (!fd_table) return -1;
    }
    else
    {
        fd_table = dfs_fdtable_get_pid(pid);
        if (!fd_table)
        {
            rt_kprintf("PID %s is not a applet(lwp)\n", pid);
            return -1;
        }
    }

    rt_kprintf("--- -- ------  ------ ----- ---------- ---------- ---------- ------\n");

    rt_enter_critical();
    for (index = 0; index < (int)fd_table->maxfd; index++)
    {
        struct dfs_file *fd = fd_table->fds[index];

        if (fd && fd->vnode->fops)
        {
            if(pid == (-1))
            {
                rt_kprintf("  K ");
            }
            else
            {
                rt_kprintf("%3d ", pid);
            }

            rt_kprintf("%2d ", index);
            if (fd->vnode->type == FT_DIRECTORY)    rt_kprintf("%-7.7s ", "dir");
            else if (fd->vnode->type == FT_REGULAR) rt_kprintf("%-7.7s ", "file");
            else if (fd->vnode->type == FT_SOCKET)  rt_kprintf("%-7.7s ", "socket");
            else if (fd->vnode->type == FT_USER)    rt_kprintf("%-7.7s ", "user");
            else if (fd->vnode->type == FT_DEVICE)  rt_kprintf("%-7.7s ", "device");
            else rt_kprintf("%-8.8s ", "unknown");
            rt_kprintf("%6d ", fd->vnode->ref_count);
            rt_kprintf("%04x  0x%.8x ", fd->magic, (int)(size_t)fd->vnode);

            if(fd->vnode == RT_NULL)
            {
                rt_kprintf("0x%.8x 0x%.8x ", (int)0x00000000, (int)(size_t)fd);
            }
            else
            {
                rt_kprintf("0x%.8x 0x%.8x ", (int)(size_t)(fd->vnode->data), (int)(size_t)fd);
            }

            if (fd->vnode->path)
            {
                rt_kprintf("%s \n", fd->vnode->path);
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

int lsof(int argc, char *argv[])
{
    rt_kprintf("PID fd type    fd-ref magic vnode      vnode/data addr       path  \n");

    if (argc == 1)
    {
        struct rt_list_node *node, *list;
        struct lwp_avl_struct *pids = lwp_get_pid_ary();

        lsofp(-1);

        for (int index = 0; index < RT_LWP_MAX_NR; index++)
        {
            struct rt_lwp *lwp = (struct rt_lwp *)pids[index].data;

            if (lwp)
            {
                list = &lwp->t_grp;
                for (node = list->next; node != list; node = node->next)
                {
                    lsofp(lwp_to_pid(lwp));
                }
            }
        }
    }
    else if (argc == 3)
    {
        if (argv[1][0] == '-' && argv[1][1] == 'p')
        {
            int pid = atoi(argv[2]);
            lsofp(pid);
        }
    }

    return 0;
}
MSH_CMD_EXPORT(lsof, list open files);
#endif /* RT_USING_SMART */

#endif
/*@}*/

