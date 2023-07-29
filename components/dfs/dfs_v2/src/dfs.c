/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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
#include <dfs_dentry.h>
#include <dfs_file.h>
#include <dfs_mnt.h>

#include <rtservice.h>

#include "dfs_private.h"

#define DBG_TAG    "DFS"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_SMART
#include <lwp.h>
#endif

#ifdef DFS_USING_WORKDIR
char working_directory[DFS_PATH_MAX] = {"/"};
#endif

/* device filesystem lock */
static struct rt_mutex fslock;
static struct rt_mutex fdlock;
static struct dfs_fdtable _fdtab = {0};
static int fd_alloc(struct dfs_fdtable *fdt, int startfd);

/**
 * this function will lock device file system.
 *
 * @note please don't invoke it on ISR.
 */
rt_err_t dfs_lock(void)
{
    rt_err_t result = -RT_EBUSY;

    while (result == -RT_EBUSY)
    {
        result = rt_mutex_take(&fslock, RT_WAITING_FOREVER);
    }

    return result;
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

/**
 * @addtogroup DFS
 */

/*@{*/

rt_err_t dfs_file_lock(void)
{
    rt_err_t result = -RT_EBUSY;

    while (result == -RT_EBUSY)
    {
        result = rt_mutex_take(&fdlock, RT_WAITING_FOREVER);
    }

    return result;
}

void dfs_file_unlock(void)
{
    rt_mutex_release(&fdlock);
}

/**
 * this function will initialize device file system.
 */
int dfs_init(void)
{
    static rt_bool_t init_ok = RT_FALSE;
    if (init_ok)
    {
        LOG_E("DFS was already initialized.\n");
        return 0;
    }

    /* create device filesystem lock */
    rt_mutex_init(&fslock, "fslock", RT_IPC_FLAG_FIFO);
    rt_mutex_init(&fdlock, "fdlock", RT_IPC_FLAG_FIFO);

    /* clean fd table */
    dfs_dentry_init();

    init_ok = RT_TRUE;

    return 0;
}
INIT_PREV_EXPORT(dfs_init);

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
    fdt->fds = fds;
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

    idx = fd_slot_alloc(fdt, startfd);
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
    idx = fd_alloc(fdt, (fdt == &_fdtab) ? DFS_STDIO_OFFSET : 0);
    /* can't find an empty fd entry */
    if (idx < 0)
    {
        LOG_E("DFS fd new is failed! Could not found an empty fd entry.");
    }
    else
    {
        struct dfs_file *file;

        file = (struct dfs_file *)rt_calloc(1, sizeof(struct dfs_file));
        if (file)
        {
            file->magic = DFS_FD_MAGIC;
            file->ref_count = 1;
            rt_mutex_init(&file->pos_lock, "fpos", RT_IPC_FLAG_PRIO);
            RT_ASSERT(fdt->fds[idx] == NULL);
            fdt->fds[idx] = file;
            LOG_D("allocate a new fd @ %d", idx);
        }
        else
        {
            fdt->fds[idx] = RT_NULL;
            idx = -1;
        }
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

struct dfs_file *fdt_fd_get(struct dfs_fdtable *fdt, int fd)
{
    struct dfs_file *f;

    if (fd < 0 || fd >= (int)fdt->maxfd)
    {
        return NULL;
    }

    f = fdt->fds[fd];

    /* check file valid or not */
    if ((f == NULL) || (f->magic != DFS_FD_MAGIC))
    {
        return NULL;
    }

    return f;
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
void fd_release(int fd)
{
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();
    fdt_fd_release(fdt, fd);
}

void fdt_fd_release(struct dfs_fdtable *fdt, int fd)
{
    if (fd < fdt->maxfd)
    {
        struct dfs_file *file = fdt_fd_get(fdt, fd);
        if (file && file->ref_count == 1)
        {
            rt_mutex_detach(&file->pos_lock);
            rt_free(file);
        }
        else
        {
            rt_atomic_sub(&(file->ref_count), 1);
        }
        fdt->fds[fd] = RT_NULL;
    }
}

static int fd_get_fd_index_form_fdt(struct dfs_fdtable *fdt, struct dfs_file *file)
{
    int fd = -1;

    if (file == RT_NULL)
    {
        return -1;
    }

    dfs_file_lock();

    for (int index = 0; index < (int)fdt->maxfd; index++)
    {
        if (fdt->fds[index] == file)
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
    rt_atomic_add(&(file->ref_count), 1);
    fdt->fds[fd] = file;
    retfd = fd;

exit:
    dfs_file_unlock();
    return retfd;
}

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

int dfs_dup(int oldfd, int startfd)
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
    newfd = fd_slot_alloc(fdt, startfd);
    if (newfd >= 0)
    {
        fdt->fds[newfd] = fdt->fds[oldfd];

        /* inc ref_count */
        rt_atomic_add(&(fdt->fds[newfd]->ref_count), 1);
    }
exit:
    dfs_file_unlock();
    return newfd;
}

#ifdef RT_USING_SMART
sysret_t sys_dup(int oldfd)
#else
int sys_dup(int oldfd)
#endif
{
    int newfd = dfs_dup(oldfd, (dfs_fdtable_get() == &_fdtab) ? DFS_STDIO_OFFSET : 0);

#ifdef RT_USING_SMART
    return (sysret_t)newfd;
#else
    return newfd;
#endif
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
    rt_atomic_add(&(fdt->fds[newfd]->ref_count), 1);
    retfd = newfd;
exit:
    dfs_file_unlock();
    return retfd;
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
        dir--;
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
            if (!src[1])
                src++; /* '.' and ends */
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
        dst--;
        if (dst < dst0)
        {
            rt_free(fullpath);
            return NULL;
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
    for (index = 0; index < (int)fd_table->maxfd; index++)
    {
        struct dfs_file *file = fd_table->fds[index];

        if (file && file->vnode)
        {
            rt_kprintf("%2d ", index);
            if (file->vnode->type == FT_DIRECTORY)    rt_kprintf("%-7.7s ", "dir");
            else if (file->vnode->type == FT_REGULAR) rt_kprintf("%-7.7s ", "file");
            else if (file->vnode->type == FT_SOCKET)  rt_kprintf("%-7.7s ", "socket");
            else if (file->vnode->type == FT_USER)    rt_kprintf("%-7.7s ", "user");
            else if (file->vnode->type == FT_DEVICE)  rt_kprintf("%-7.7s ", "device");
            else rt_kprintf("%-8.8s ", "unknown");
            rt_kprintf("%3d ", file->ref_count);
            rt_kprintf("%04x  ", file->magic);

            if (file->dentry)
            {
                rt_kprintf("%s%s\n", file->dentry->mnt->fullpath, file->dentry->pathname);
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

int dfs_fd_dump(int argc, char** argv)
{
    int index;

    dfs_file_lock();
    for (index = 0; index < _fdtab.maxfd; index++)
    {
        struct dfs_file *file = _fdtab.fds[index];
        if (file)
        {
            char* fullpath = dfs_dentry_full_path(file->dentry);
            if (fullpath)
            {
                printf("[%d] - %s, ref_count %zd\n", index,
                    fullpath, (size_t)rt_atomic_load(&(file->ref_count)));
                rt_free(fullpath);
            }
            else
            {
                printf("[%d] - %s, ref_count %zd\n", index,
                    file->dentry->pathname, (size_t)rt_atomic_load(&(file->ref_count)));
            }
        }
    }
    dfs_file_unlock();

    return 0;
}
MSH_CMD_EXPORT_ALIAS(dfs_fd_dump, fd_dump, fd dump);

#ifdef PKG_USING_DLOG

int dfs_dlog(int argc, char** argv)
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            dlog_session_start();
            dlog_participant("dfs");
            dlog_participant("dfs_file");
            dlog_participant("dentry");
            dlog_participant("vnode");
            dlog_participant("mnt");
            dlog_participant("rom");
            dlog_participant("devfs");
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            dlog_session_stop();
        }
    }

    return 0;
}
MSH_CMD_EXPORT(dfs_dlog, dfs dlog on|off);

#endif

#endif
/**@}*/

