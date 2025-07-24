/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
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

static rt_bool_t _dfs_init_ok = RT_FALSE;

/* device filesystem lock */
static struct rt_mutex fslock;
static struct rt_mutex fdlock;
static struct dfs_fdtable _fdtab = {0};

/**
 * @brief Expand the file descriptor table to accommodate a specified file descriptor
 *
 * This function ensures that the file descriptor table in the given `dfs_fdtable` structure
 * has sufficient capacity to include the specified file descriptor `fd`. If the table
 * needs to be expanded, it reallocates memory and initializes new slots to `NULL`.
 *
 * @param[in,out] fdt Pointer to the file descriptor table to be expanded
 * @param[in] fd The file descriptor that needs to be accommodated
 *
 * @return int The input file descriptor if successful (fd >= 0),
 *         -1 if expansion failed or fd exceeds maximum allowed value (DFS_FD_MAX)
 *
 * @note Expand table size to next multiple of 4 (but not exceeding DFS_FD_MAX)
 */
static int _fdt_slot_expand(struct dfs_fdtable *fdt, int fd)
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

/**
 * @brief Allocate an available file descriptor slot in the file descriptor table
 *
 * @param[in,out] fdt Pointer to the file descriptor table to allocate from
 * @param[in] startfd The starting file descriptor index to begin searching
 *
 * @return int The allocated file descriptor index if successful (>= 0),
 *         -1 if allocation failed (table expansion failed)
 *
 * @note If no empty slot found, expand the table and return the new index.
 */
static int _fdt_slot_alloc(struct dfs_fdtable *fdt, int startfd)
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

    if (_fdt_slot_expand(fdt, idx) < 0)
    {
        return -1;
    }

    return idx;
}

/**
 * @brief Allocate a file descriptor from the file descriptor table
 *
 * @param[in,out] fdt Pointer to the file descriptor table to allocate from
 * @param[in] startfd The starting file descriptor index to begin searching
 *
 * @return int The allocated file descriptor index if successful (>= 0),
 *         -1 if allocation failed
 *
 * @note This is a wrapper function that calls _fdt_slot_alloc() to perform
 *       the actual allocation. It maintains the same behavior as _fdt_slot_alloc().
 */
static int _fdt_fd_alloc(struct dfs_fdtable *fdt, int startfd)
{
    int idx;

    idx = _fdt_slot_alloc(fdt, startfd);

    return idx;
}

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
 * this function will unlock device file system.
 *
 * @note please don't invoke it on ISR.
 */
void dfs_unlock(void)
{
    rt_mutex_release(&fslock);
}

/** @addtogroup group_device_virtual_file_system
 *
 *
 *  @{
 */

/**
 * @brief Lock the file descriptor table mutex
 *
 * @return rt_err_t RT_EOK if lock acquired successfully,
 *         -RT_ENOSYS if filesystem not initialized,
 *         -RT_EBUSY if mutex is already locked (retries until acquired)
 *
 * @note This function will block indefinitely until the lock is acquired.
 *       Should not be called from interrupt service routines.
 */
rt_err_t dfs_file_lock(void)
{
    rt_err_t result = -RT_EBUSY;

    if (!_dfs_init_ok)
    {
        return -RT_ENOSYS;
    }

    while (result == -RT_EBUSY)
    {
        result = rt_mutex_take(&fdlock, RT_WAITING_FOREVER);
    }

    return result;
}

/**
 * @brief Unlock the file descriptor table mutex
 *
 * @note This function releases the lock acquired by dfs_file_lock().
 *       Should be called in the same context as the corresponding lock.
 *       Should not be called from interrupt service routines.
 */
void dfs_file_unlock(void)
{
    rt_mutex_release(&fdlock);
}

/**
 * this function will initialize device file system.
 */
int dfs_init(void)
{
    if (_dfs_init_ok)
    {
        LOG_E("DFS was already initialized.\n");
        return 0;
    }

    /* create device filesystem lock */
    rt_mutex_init(&fslock, "fslock", RT_IPC_FLAG_FIFO);
    rt_mutex_init(&fdlock, "fdlock", RT_IPC_FLAG_FIFO);

    /* Initialize dentry system */
    dfs_dentry_init();

    _dfs_init_ok = RT_TRUE;

    return 0;
}
INIT_PREV_EXPORT(dfs_init);

/**
 * @brief Create and initialize a new file descriptor structure
 *
 * @return struct dfs_file* Pointer to the newly created file descriptor structure,
 *         NULL if memory allocation failed
 */
struct dfs_file* dfs_file_create(void)
{
    struct dfs_file *file;

    file = (struct dfs_file *)rt_calloc(1, sizeof(struct dfs_file));
    if (file)
    {
        file->magic = DFS_FD_MAGIC;
        file->ref_count = 1;
        rt_mutex_init(&file->pos_lock, "fpos", RT_IPC_FLAG_PRIO);
    }

    return file;
}

/**
 * @brief Destroy and free a file descriptor structure
 *
 * @param[in] file Pointer to the file descriptor structure to be destroyed
 */
void dfs_file_destroy(struct dfs_file *file)
{
    rt_mutex_detach(&file->pos_lock);

    if (file->mmap_context)
    {
        rt_free(file->mmap_context);
    }

    rt_free(file);
}

/**
 * @ingroup group_fs_file_descriptor
 *
 * @brief Allocate a new file descriptor in the file descriptor table
 *
 * @param[in,out] fdt Pointer to the file descriptor table to allocate from
 *
 * @return int The allocated file descriptor index if successful (>= 0),
 *         -RT_ENOSYS if filesystem lock failed,
 *         -1 if allocation failed (no empty slots or memory allocation failed)
 */
int fdt_fd_new(struct dfs_fdtable *fdt)
{
    int idx = -1;

    /* lock filesystem */
    if (dfs_file_lock() != RT_EOK)
    {
        return -RT_ENOSYS;
    }

    /* find an empty fd entry */
    idx = _fdt_fd_alloc(fdt, (fdt == &_fdtab) ? DFS_STDIO_OFFSET : 0);
    /* can't find an empty fd entry */
    if (idx < 0)
    {
        LOG_E("DFS fd new is failed! Could not found an empty fd entry.");
    }
    else if (!fdt->fds[idx])
    {
        struct dfs_file *file;

        file = dfs_file_create();

        if (file)
        {
            fdt->fds[idx] = file;

            LOG_D("allocate a new fd @ %d", idx);
        }
        else
        {
            fdt->fds[idx] = RT_NULL;
            idx = -1;
        }
    }
    else
    {
        LOG_E("DFS not found an empty fds entry.");
        idx = -1;
    }

    dfs_file_unlock();

    return idx;
}

/**
 * @brief Release a file descriptor from the file descriptor table
 *
 * @param[in,out] fdt Pointer to the file descriptor table
 * @param[in] fd The file descriptor to be released
 */
void fdt_fd_release(struct dfs_fdtable *fdt, int fd)
{
    if (fd < fdt->maxfd)
    {
        struct dfs_file *file;

        file = fdt_get_file(fdt, fd);

        if (file && file->ref_count == 1)
        {
            dfs_file_destroy(file);
        }
        else
        {
            rt_atomic_sub(&(file->ref_count), 1);
        }

        fdt->fds[fd] = RT_NULL;
    }
}

/**
 * @ingroup group_fs_file_descriptor
 *
 * This function will return a file descriptor structure according to file
 * descriptor.
 *
 * @return NULL on on this file descriptor or the file descriptor structure
 * pointer.
 */

struct dfs_file *fdt_get_file(struct dfs_fdtable *fdt, int fd)
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

/**
 * @brief Associate a file structure with a file descriptor in the file descriptor table
 *
 * @param[in,out] fdt Pointer to the file descriptor table
 * @param[in] fd The file descriptor to associate with
 * @param[in] file Pointer to the file structure to associate
 *
 * @return int The file descriptor if successful (>= 0),
 *         -1 if association failed (invalid parameters or fd already in use),
 *         -RT_ENOSYS if filesystem lock failed
 */
int fdt_fd_associate_file(struct dfs_fdtable *fdt, int fd, struct dfs_file *file)
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

    if (dfs_file_lock() != RT_EOK)
    {
        return -RT_ENOSYS;
    }

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
 * @brief Allocate a new file descriptor in current process's file descriptor table
 *
 * @return int The allocated file descriptor index if successful (>= 0),
 *         -1 if allocation failed
 */
int fd_new(void)
{
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();

    return fdt_fd_new(fdt);
}

/**
 * @ingroup group_fs_file_descriptor
 *
 * This function will put the file descriptor.
 */
void fd_release(int fd)
{
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();
    fdt_fd_release(fdt, fd);
}

/**
 * @brief Get file structure by file descriptor from current process's fd table
 *
 * @param[in] fd The file descriptor to lookup
 *
 * @return struct dfs_file* Pointer to the file structure if found,
 *         NULL if invalid fd or file not found
 */
struct dfs_file *fd_get(int fd)
{
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();

    return fdt_get_file(fdt, fd);
}

/**
 * This function will get the file descriptor table of current process.
 */
struct dfs_fdtable *dfs_fdtable_get(void)
{
    struct dfs_fdtable *fdt;
#ifdef RT_USING_SMART
    struct rt_lwp *lwp = NULL;
    rt_thread_t thread = rt_thread_self();

    if (thread)
    {
        lwp = (struct rt_lwp *)thread->lwp;
    }

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
/**
 * @brief Get file structure by file descriptor from current process's fd table
 *
 * @param[in] fd The file descriptor to lookup
 *
 * @return struct dfs_file* Pointer to the file structure if found,
 *         NULL if invalid fd or file not found
 */
struct dfs_fdtable *dfs_fdtable_get_from_pid(int pid)
{
    struct rt_lwp *lwp = RT_NULL;
    struct dfs_fdtable *fdt = RT_NULL;

    lwp_pid_lock_take();
    lwp = lwp_from_pid_locked(pid);
    if (lwp)
    {
        fdt = &lwp->fdt;
    }
    lwp_pid_lock_release();

    return fdt;
}
#endif

/**
 * @brief Get the global file descriptor table
 *
 * @return struct dfs_fdtable* Pointer to the global file descriptor table
 */
struct dfs_fdtable *dfs_fdtable_get_global(void)
{
    return &_fdtab;
}

/**
 * @brief  Dup the specified fd_src from fdt_src to fdt_dst.
 *
 * @param[out]  fdt_dst is the fd table for destination, if empty, use global (_fdtab).
 *
 * @param[in]  fdt_src is the fd table for source, if empty, use global (_fdtab).
 *
 * @param[in]  fd_src is the fd in the designate fdt_src table.
 *
 * @return -1 on failed or the allocated file descriptor.
 */
int dfs_fdtable_dup(struct dfs_fdtable *fdt_dst, struct dfs_fdtable *fdt_src, int fd_src)
{
    int newfd = -1;

    if (dfs_file_lock() != RT_EOK)
    {
        return -RT_ENOSYS;
    }

    if (fdt_src == NULL)
    {
        fdt_src = &_fdtab;
    }

    if (fdt_dst == NULL)
    {
        fdt_dst = &_fdtab;
    }

    /* check fd */
    if ((fd_src < 0) || (fd_src >= fdt_src->maxfd))
    {
        goto _EXIT;
    }
    if (!fdt_src->fds[fd_src])
    {
        goto _EXIT;
    }

    /* get a new fd*/
    newfd = fdt_fd_new(fdt_dst);
    if (newfd >= 0)
    {
        fdt_dst->fds[newfd]->mode = fdt_src->fds[fd_src]->mode;
        fdt_dst->fds[newfd]->flags = fdt_src->fds[fd_src]->flags;
        fdt_dst->fds[newfd]->fops = fdt_src->fds[fd_src]->fops;
        fdt_dst->fds[newfd]->dentry = dfs_dentry_ref(fdt_src->fds[fd_src]->dentry);
        fdt_dst->fds[newfd]->vnode = fdt_src->fds[fd_src]->vnode;
        fdt_dst->fds[newfd]->mmap_context = RT_NULL;
        fdt_dst->fds[newfd]->data = fdt_src->fds[fd_src]->data;

        /*
        * dma-buf/socket fd is without dentry, so should used the vnode reference.
        */
        if (!fdt_dst->fds[newfd]->dentry)
        {
            rt_atomic_add(&(fdt_dst->fds[newfd]->vnode->ref_count), 1);
        }
    }

_EXIT:
    dfs_file_unlock();

    return newfd;
}

/**
 * @brief  drop fd from the fd table.
 *
 * @param  fdt is the fd table, if empty, use global (_fdtab).
 *
 * @param  fd is the fd in the designate fd table.
 *
 * @return -1 on failed the drop file descriptor.
 */
int dfs_fdtable_drop_fd(struct dfs_fdtable *fdt, int fd)
{
    int err = 0;

    if (fdt == NULL)
    {
        fdt = &_fdtab;
    }

    if (dfs_file_lock() != RT_EOK)
    {
        return -RT_ENOSYS;
    }

    err = dfs_file_close(fdt->fds[fd]);
    if (!err)
    {
        fdt_fd_release(fdt, fd);
    }

    dfs_file_unlock();

    return err;
}

/**
 * @brief Duplicate a file descriptor in the current process's file descriptor table
 *
 * @param[in] oldfd The file descriptor to duplicate
 * @param[in] startfd The starting index to search for an available file descriptor slot
 *
 * @return int The new file descriptor if successful (>=0),
 *         -1 if failed (invalid fd or allocation failed),
 *         -RT_ENOSYS if filesystem lock failed
 */
int dfs_dup(int oldfd, int startfd)
{
    int newfd = -1;
    struct dfs_fdtable *fdt = NULL;

    if (dfs_file_lock() != RT_EOK)
    {
        return -RT_ENOSYS;
    }

    /* check old fd */
    fdt = dfs_fdtable_get();
    if ((oldfd < 0) || (oldfd >= fdt->maxfd))
    {
        rt_set_errno(-EBADF);
        goto exit;
    }
    if (!fdt->fds[oldfd])
    {
        goto exit;
    }
    /* get a new fd */
    newfd = _fdt_slot_alloc(fdt, startfd);
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

/**
 * @brief Duplicate a file descriptor from current process to target file descriptor table
 *
 * @param[in]  oldfd is the fd in current process.
 * @param[in,out]  fdtab is the fd table to dup, if empty, use global (_fdtab).
 *
 * @return -1 on failed or the allocated file descriptor.
 */
int dfs_dup_to(int oldfd, struct dfs_fdtable *fdtab)
{
    int newfd = -1;
    struct dfs_fdtable *fdt = NULL;

    if (dfs_file_lock() != RT_EOK)
    {
        return -RT_ENOSYS;
    }

    if (fdtab == NULL)
    {
        fdtab = &_fdtab;
    }

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
    /* get a new fd*/
    newfd = _fdt_slot_alloc(fdtab, DFS_STDIO_OFFSET);
    if (newfd >= 0)
    {
        fdtab->fds[newfd] = fdt->fds[oldfd];

        /* inc ref_count */
        rt_atomic_add(&(fdtab->fds[newfd]->ref_count), 1);
    }
exit:
    dfs_file_unlock();

    return newfd;
}

/**
 * @brief  Duplicate a file descriptor from source table to current process
 *
 * @param[in]  oldfd is the fd in the designate fd table.
 * @param[in,out]  fdtab is the fd table for oldfd, if empty, use global (_fdtab).
 *
 * @return -1 on failed or the allocated file descriptor.
 */
int dfs_dup_from(int oldfd, struct dfs_fdtable *fdtab)
{
    int newfd = -1;
    struct dfs_file *file;

    if (dfs_file_lock() != RT_EOK)
    {
        return -RT_ENOSYS;
    }

    if (fdtab == NULL)
    {
        fdtab = &_fdtab;
    }

    /* check old fd */
    if ((oldfd < 0) || (oldfd >= fdtab->maxfd))
    {
        goto exit;
    }
    if (!fdtab->fds[oldfd])
    {
        goto exit;
    }
    /* get a new fd*/
    newfd = fd_new();
    file = fd_get(newfd);
    if (newfd >= 0 && file)
    {
        file->mode = fdtab->fds[oldfd]->mode;
        file->flags = fdtab->fds[oldfd]->flags;
        file->fops = fdtab->fds[oldfd]->fops;
        file->dentry = dfs_dentry_ref(fdtab->fds[oldfd]->dentry);
        file->vnode = fdtab->fds[oldfd]->vnode;
        file->mmap_context = RT_NULL;
        file->data = fdtab->fds[oldfd]->data;
    }

    dfs_file_close(fdtab->fds[oldfd]);

exit:
    fdt_fd_release(fdtab, oldfd);
    dfs_file_unlock();

    return newfd;
}

/**
 * @brief System call to duplicate a file descriptor
 *
 * @param[in] oldfd The file descriptor to duplicate
 *
 * @return sysret_t/int The new file descriptor if successful (>=0),
 *         negative error code if failed
 */
#ifdef RT_USING_SMART
sysret_t sys_dup(int oldfd)
#else
int sys_dup(int oldfd)
#endif
{
    int err = 0;
    int newfd = dfs_dup(oldfd, (dfs_fdtable_get() == &_fdtab) ? DFS_STDIO_OFFSET : 0);
    if(newfd < 0)
    {
        err = rt_get_errno();
    }

#ifdef RT_USING_SMART
    return err < 0 ? err : newfd;
#else
    return err < 0 ? err : newfd;
#endif
}

/**
 * @brief System call to duplicate a file descriptor to a specific descriptor number
 *
 * @param[in] oldfd The file descriptor to duplicate
 * @param[in] newfd The desired file descriptor number
 *
 * @return rt_err_t The new file descriptor number if successful (>=0),
 *         -RT_ENOSYS if filesystem lock failed,
 *         -1 if operation failed (invalid descriptors or allocation failed)
 */
rt_err_t sys_dup2(int oldfd, int newfd)
{
    struct dfs_fdtable *fdt = NULL;
    int ret = 0;
    int retfd = -1;

    if (dfs_file_lock() != RT_EOK)
    {
        return -RT_ENOSYS;
    }

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
        newfd = _fdt_slot_expand(fdt, newfd);
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
 * @brief Get the subdirectory path relative to a parent directory
 *
 * @param[in] directory The parent directory path
 * @param[in] filename The full path including parent directory and subpath
 *
 * @return const char* Pointer to the subdirectory portion of filename,
 *         NULL if paths are identical or invalid
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
 * @brief Normalize a path by combining directory and filename into an absolute path
 *
 * @param[in] directory The parent directory path (NULL means use working directory)
 * @param[in] filename The filename or relative path to be normalized
 *
 * @return char* The normalized absolute path (must be freed by caller),
 *         NULL if path is invalid or memory allocation fails
 *
 * @note This function will:
 *       - Handle working directory when directory is NULL
 *       - Join directory and filename with proper separators
 *       - Resolve . and .. in paths
 *       - Remove redundant slashes
 *       - Ensure path starts with /
 *       - Allocate memory for the returned path string
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

    if (filename[0] != '/')
    {
        int path_len;

        path_len = strlen(directory) + strlen(filename) + 2;
        if (path_len > DFS_PATH_MAX)
        {
            return NULL;
        }

        fullpath = (char *)rt_malloc(path_len);
        if (fullpath == NULL)
        {
            return NULL;
        }

        /* join path and file name */
        rt_snprintf(fullpath, strlen(directory) + strlen(filename) + 2,
                    "%s/%s", directory, filename);
    }
    else /* it's a absolute path, use it directly */
    {
        fullpath = rt_strdup(filename); /* copy string */

        if (fullpath == NULL)
            return NULL;
    }

    /* Initialize source and destination pointers to start of path */
    src = fullpath;
    dst = fullpath;

    /* Save initial position for boundary checking */
    dst0 = dst;
    while (1)
    {
        char c = *src;

        /* Handle '.' and '..' path components */
        if (c == '.')
        {
            /* Single dot at end of path */
            if (!src[1])
                src++; /* '.' and ends, Skip single dot */
            else if (src[1] == '/')
            {
                /* './' case */
                src += 2;

                /* Skip consecutive slashes */
                while ((*src == '/') && (*src != '\0'))
                    src++;
                continue;
            }
            else if (src[1] == '.')
            {
                /* Parent directory reference */
                if (!src[2])
                {
                    /* '..' and ends case */
                    src += 2;
                    goto up_one;
                }
                else if (src[2] == '/')
                {
                    /* '../' case: parent directory reference */
                    src += 3;

                    /* Skip consecutive slashes */
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
            /* Add single slash */
            *dst++ = '/';
            while (c == '/')
                c = *src++;

            src--;
        }
        else if (!c)
            break; /* End of string */

        continue;

    /* Handle parent directory reference */
    up_one:
        /* Move back one directory level */
        dst--;
        if (dst < dst0) /* Check for path traversal underflow */
        {
            rt_free(fullpath);
            return NULL;
        }
        /* Find previous directory separator */
        while (dst0 < dst && dst[-1] != '/')
            dst--;
    }

    /* Null-terminate the path */
    *dst = '\0';

    /* remove '/' in the end of path if exist */
    dst--;
    if (dst > fullpath && (*dst == '/'))
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
/**
 * @brief List all open file descriptors in the current process
 *
 * @return int 0 on success, -1 if failed to get file descriptor table
 */
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

/**
 * @brief Dump all file descriptors information in the global file descriptor table
 *
 * @param[in] argc Number of command line arguments (unused)
 * @param[in] argv Array of command line arguments (unused)
 *
 * @return int 0 on success,
 *         -RT_ENOSYS if failed to acquire file system lock
 */
int dfs_fd_dump(int argc, char** argv)
{
    int index;

    if (dfs_file_lock() != RT_EOK)
    {
        return -RT_ENOSYS;
    }

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
/**
 * @brief Control the DFS (Device File System) debug logging functionality
 *
 * @param[in] argc Number of command line arguments (must be 2)
 * @param[in] argv Array of command line arguments:
 *                - argv[1]: "on" to enable logging, "off" to disable logging
 *
 * @return int Always returns 0 (success)
 *
 * @note When enabled, this function activates logging for multiple DFS components:
 *       - dfs: Core DFS functionality
 *       - dfs_file: File operations
 *       - dentry: Directory entries
 *       - vnode: Virtual nodes
 *       - mnt: Mount points
 *       - rom: ROM filesystem
 *       - devfs: Device filesystem
 */
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
/** @} */