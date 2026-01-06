/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-05     Bernard      Implement file APIs in dfs v2.0
 */

#include "errno.h"
#include "fcntl.h"

#include <dfs.h>

#include "dfs_file.h"
#include "dfs_dentry.h"
#include "dfs_fs.h"
#include "dfs_mnt.h"
#include "dfs_private.h"

#ifdef RT_USING_PAGECACHE
#include "dfs_pcache.h"
#endif

#define DBG_TAG    "DFS.file"
#define DBG_LVL    DBG_WARNING
#include <rtdbg.h>

#define MAX_RW_COUNT 0xfffc0000

/**
 * @brief Get the length of the first path component
 *
 * This function calculates the length of the first path component in a given path string.
 * For absolute paths (starting with '/'), it returns the length from the first '/' to
 * the next '/' or end of string. For relative paths, it returns 0.
 *
 * @param[in] path The input path string to analyze
 *
 * @return int The length of the first path component, or 0 if not found
 */
rt_inline int _first_path_len(const char *path)
{
    int i = 0;

    if (path[i] == '/')
    {
        i++;
        while (path[i] != '\0' && path[i] != '/')
        {
            i++;
        }
    }

    return i;
}

/**
 * @brief Get the parent directory path from a given full path
 *
 * This function extracts the parent directory path from a given full path string.
 * It handles paths ending with '/' correctly by skipping the trailing slash.
 *
 * @param[in] fullpath The input full path string to analyze
 * @param[out] path Buffer to store the extracted parent directory path
 *
 * @return int Length of the parent directory path, or 0 if no parent found
 */
static int _get_parent_path(const char *fullpath, char *path)
{
    int len = 0;
    char *str = 0;

    char *full_path = rt_strdup(fullpath);
    if (full_path == NULL)
    {
        rt_set_errno(ENOMEM);
        return -1;
    }

    str = strrchr(full_path, '/');

    /* skip last '/' */
    if (str && *(str + 1) == '\0')
    {
        *str = '\0';
        str = strrchr(full_path, '/');
    }

    if (str)
    {
        len = str - full_path;
        if (len > 0)
        {
            rt_memcpy(path, full_path, len);
            path[len] = '\0';
        }
        else if (len == 0) /* parent path is root path. */
        {
            path[0] = '/';
            path[1] = '\0';
            len = 1;
        }
    }

    rt_free(full_path);
    return len;
}

/**
 * @brief Attempt to read the target of a symbolic link
 *
 * This function tries to read the contents of a symbolic link file. It first looks up
 * the dentry for the given path, checks if it's a symlink, and then calls the filesystem's
 * readlink operation if available.
 *
 * @param[in] path The path of the symbolic link to read
 * @param[in] mnt The mount point containing the symbolic link
 * @param[out] link Buffer to store the link target (contents of the symlink)
 *
 * @return int Length of the link target on success, -1 on failure
 */
static int _try_readlink(const char *path, struct dfs_mnt *mnt, char *link)
{
    int ret = -1;
    struct dfs_dentry *dentry = dfs_dentry_lookup(mnt, path, 0);

    if (dentry && dentry->vnode->type == FT_SYMLINK)
    {
        if (mnt->fs_ops->readlink)
        {
            if (dfs_is_mounted(mnt) == 0)
            {
                ret = mnt->fs_ops->readlink(dentry, link, DFS_PATH_MAX);
            }
        }
    }
    dfs_dentry_unref(dentry);

    return ret;
}

/**
 * @brief Normalize a path by combining base path and link path
 *
 * This function creates a temporary path by combining the base path and link path,
 * then normalizes it using dfs_normalize_path(). It handles memory allocation and
 * cleanup internally.
 *
 * @param[in] path The base path to combine with the link
 * @param[in] path_len Length of the base path
 * @param[in] link_fn The link path to combine with the base path
 * @param[in] link_len Length of the link path
 *
 * @return char* Normalized path string on success, RT_NULL on failure
 *
 * @note The caller is responsible for freeing the returned path
 */
static char *_dfs_normalize_path(const char *path, int path_len, const char *link_fn, int link_len)
{
    char *tmp_path, *fp;

    tmp_path = (char *)rt_malloc(path_len + link_len + 2);
    if (!tmp_path)
    {
        return RT_NULL;
    }

    memcpy(tmp_path, path, path_len);
    tmp_path[path_len] = '/';
    memcpy(tmp_path + path_len + 1, link_fn, link_len);
    tmp_path[path_len + 1 + link_len] = '\0';

    fp = dfs_normalize_path(NULL, tmp_path);
    rt_free(tmp_path);

    return fp;
}

/**
 * @brief Insert a link path into temporary path buffer
 *
 * This function inserts a symbolic link path into a temporary path buffer before
 * the specified index position. It handles both relative and absolute paths.
 *
 * @param[in] link_fn The link path to insert
 * @param[in] link_len Length of the link path
 * @param[in,out] tmp_path The temporary path buffer to insert into
 * @param[in,out] index Pointer to the insertion position index (updated after insertion)
 *
 * @return int 0 for relative path, 1 for absolute path, -1 on failure
 * @note The index is modified to reflect the new insertion position
 */
static int _insert_link_path(const char *link_fn, int link_len, char *tmp_path, int *index)
{
    int ret = -1;

    if (link_fn[0] != '/')
    {
        if (link_len + 1 <= *index)
        {
            *index -= link_len;
            rt_memcpy(tmp_path + *index, link_fn, link_len);
            *index -= 1;
            tmp_path[*index] = '/';
            ret = 0;
        }
    }
    else if (link_len <= *index)
    {
        *index -= link_len;
        rt_memcpy(tmp_path + *index, link_fn, link_len);
        ret = 1;
    }

    return ret;
}

/**
 * @brief Verify read/write area parameters and limit count size
 *
 * This function checks the validity of read/write parameters and limits the count
 * to a maximum value (MAX_RW_COUNT) to prevent overflow. It ensures the position
 * and count values are within valid ranges.
 *
 * @param[in] file Pointer to the file structure (unused in current implementation)
 * @param[in] ppos Pointer to the position offset (input/output)
 * @param[in] count Requested read/write count (input)
 *
 * @return ssize_t The verified count value (limited to MAX_RW_COUNT) or negative error code:
 *         -EINVAL for invalid parameters
 *         -EOVERFLOW if position + count would overflow
 *
 * @note rw_verify_area doesn't like huge counts. We limit them to something that fits in "int"
 *       so that others won't have to do range checks all the time.
 */
ssize_t rw_verify_area(struct dfs_file *file, off_t *ppos, size_t count)
{
    off_t pos;
    ssize_t retval = -EINVAL;

    if ((size_t)count < 0)
        return retval;
    pos = *ppos;
    if (pos < 0)
    {
        if (count >= -pos) /* both values are in 0..LLONG_MAX */
            return -EOVERFLOW;
    }

    return count > MAX_RW_COUNT ? MAX_RW_COUNT : count;
}

/**
 * @brief Get the current file position
 *
 * This function retrieves the current file position (offset) from the file structure.
 * For regular files, it acquires a mutex lock before accessing the position to ensure
 * thread safety. For other file types, it directly returns the position without locking.
 *
 * @param[in] file Pointer to the file structure containing position information
 *
 * @return off_t Current file position, or 0 if file pointer is NULL
 */
off_t dfs_file_get_fpos(struct dfs_file *file)
{
    if (file)
    {
        if (file->vnode->type == FT_REGULAR)
        {
            rt_mutex_take(&file->pos_lock, RT_WAITING_FOREVER);
        }
        return file->fpos;
    }

    return 0;
}

/**
 * @brief Set the current file position
 *
 * This function sets the file position (offset) in the file structure.
 * It must be used as a pair of dfs_file_get_fpos(). For regular files, pos lock is acquared
 * in dfs_file_get_fpos(), so it can be released directly after setting the position.
 * Otherwise, pos lock should be acquired first to avoid releasing it without being acquired.
 *
 * @param[in] file Pointer to the file structure to modify
 * @param[in] fpos The new file position to set
 */
void dfs_file_set_fpos(struct dfs_file *file, off_t fpos)
{
    if (file)
    {
        if (file->vnode->type != FT_REGULAR)
        {
            rt_mutex_take(&file->pos_lock, RT_WAITING_FOREVER);
        }
        file->fpos = fpos;
        rt_mutex_release(&file->pos_lock);
    }
}

/**
 * @brief Initialize a file structure
 *
 * @param[in,out] file Pointer to the file structure to be initialized
 *
 * @note This function must be called before using any file operations
 *       on a newly allocated file structure
 */
void dfs_file_init(struct dfs_file *file)
{
    if (file)
    {
        rt_memset(file, 0x00, sizeof(struct dfs_file));
        file->magic = DFS_FD_MAGIC;
        rt_mutex_init(&file->pos_lock, "fpos", RT_IPC_FLAG_PRIO);
        rt_atomic_store(&(file->ref_count), 1);
    }
}

/**
 * @brief Deinitialize a file structure
 *
 * @param[in,out] file Pointer to the file structure to be deinitialized
 */
void dfs_file_deinit(struct dfs_file *file)
{
    if (file)
    {
        rt_mutex_detach(&file->pos_lock);
    }
}

/**
 * @brief Decrement reference count and release file resources when count reaches zero
 *
 * This function safely decrements the reference count of a file structure and releases
 * associated resources (dentry or vnode) when the reference count drops to zero.
 *
 * @param[in,out] file Pointer to the file structure to be unreferenced
 */
static void dfs_file_unref(struct dfs_file *file)
{
    rt_err_t ret = RT_EOK;

    ret = dfs_file_lock();
    if (ret == RT_EOK)
    {
        if (rt_atomic_load(&(file->ref_count)) == 1)
        {
            /* should release this file */
            if (file->dentry)
            {
                DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_unref(dentry(%s))", file->dentry->pathname);
                dfs_dentry_unref(file->dentry);
                file->dentry = RT_NULL;
            }
            else if (file->vnode)
            {
                if (file->vnode->ref_count > 1)
                {
                    rt_atomic_sub(&(file->vnode->ref_count), 1);
                }
                else if (file->vnode->ref_count == 1)
                {
                    rt_free(file->vnode);
                    file->vnode = RT_NULL;
                }
            }

            LOG_I("release a file: %p", file);
        }

        dfs_file_unlock();
    }
}

/**
 * @brief Resolve the real path by resolving symbolic links and normalizing the path
 *
 * This function resolves the real path of a given file path by handling symbolic links
 * and normalizing the path components. It supports two modes of operation:
 * - DFS_REALPATH_EXCEPT_LAST: Resolve all path components except the last one
 * - DFS_REALPATH_ONLY_LAST: Resolve only the last path component
 * - DFS_REALPATH_EXCEPT_NONE: Resolve all path components
 *
 * @param[in,out] mnt Pointer to the mount point structure (updated if path changes)
 * @param[in] fullpath The input path to resolve
 * @param[in] mode Resolution mode (DFS_REALPATH_EXCEPT_LAST or DFS_REALPATH_ONLY_LAST)
 *
 * @return char* The resolved real path on success, RT_NULL on failure
 */
char *dfs_file_realpath(struct dfs_mnt **mnt, const char *fullpath, int mode)
{
    int path_len = 0, index = 0;
    char *path = RT_NULL, *link_fn, *tmp_path;
    struct dfs_mnt *tmp_mnt;

    if (*mnt && fullpath)
    {
        int len, link_len;

        path = (char *)rt_malloc((DFS_PATH_MAX * 3) + 3); /* path + \0 + link_fn + \0 + tmp_path + \0 */
        if (!path)
        {
            return RT_NULL;
        }

        link_fn = path + DFS_PATH_MAX + 1;
        tmp_path = link_fn + (DFS_PATH_MAX + 1);

        len = rt_strlen(fullpath);
        if (len > DFS_PATH_MAX)
        {
            goto _ERR_RET;
        }

        index = (DFS_PATH_MAX - len);
        rt_strcpy(tmp_path + index, fullpath);

        if (mode == DFS_REALPATH_ONLY_LAST)
        {
            path_len = _get_parent_path(fullpath, path);
            index += path_len;
        }

        while ((len = _first_path_len(tmp_path + index)) > 0)
        {
            if (len + path_len > DFS_PATH_MAX)
            {
                goto _ERR_RET;
            }

            rt_memcpy(path + path_len, tmp_path + index, len);
            path[path_len + len] = '\0';
            index += len;

            tmp_mnt = dfs_mnt_lookup(path);
            if (tmp_mnt == RT_NULL)
            {
                goto _ERR_RET;
            }

            *mnt = tmp_mnt;

            /* the last should by mode process. */
            if ((tmp_path[index] == '\0') && (mode == DFS_REALPATH_EXCEPT_LAST))
            {
                break;
            }

            /* Process symbolic links if found */
            link_len = _try_readlink(path, *mnt, link_fn);
            if (link_len > 0)
            {
                if (link_fn[0] == '/') /* Handle absolute path symlinks */
                {
                    int ret = _insert_link_path(link_fn, link_len, tmp_path, &index);
                    if (ret < 0)
                    {
                        goto _ERR_RET;
                    }
                    path_len = 0;
                }
                else /* Handle relative path symlinks */
                {
                    char *fp = _dfs_normalize_path(path, path_len, link_fn, link_len);
                    if (fp)
                    {
                        int pos = rt_strncmp(path, fp, path_len);
                        if (pos == 0)
                        {
                            int ret = _insert_link_path(fp + path_len, rt_strlen(fp + path_len), tmp_path, &index);
                            if (ret < 0)
                            {
                                rt_free(fp);
                                goto _ERR_RET;
                            }
                        }
                        else
                        {
                            int pos;

                            while(1)
                            {
                                while(path_len > 0 && path[path_len] != '/')
                                {
                                    path_len--;
                                }

                                if (path_len > 0)
                                {
                                    pos = rt_strncmp(path, fp, path_len);
                                }
                                else
                                {
                                    pos = -1;
                                }

                                if (pos == 0 || path_len == 0)
                                {
                                    int ret;

                                    ret = _insert_link_path(fp + path_len, rt_strlen(fp + path_len), tmp_path, &index);
                                    if (ret < 0)
                                    {
                                        rt_free(fp);
                                        goto _ERR_RET;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                                else
                                {
                                    path_len--;
                                }
                            }
                        }
                        rt_free(fp);
                    }
                }
            }
            else
            {
                path_len += len; /* Not a symlink, just advance path length */
            }
        }

        return path;

_ERR_RET:
        rt_free(path);
        path = RT_NULL;
    }

    return path;
}

/**
 * @brief Open a file which specified by path with specified oflags.
 *
 * This function opens or creates a file with given path and flags. It handles:
 * - Path normalization and resolution (including symbolic links)
 * - File creation when O_CREAT is specified
 * - Permission checking
 * - Directory vs regular file validation
 * - Symbolic link following (unless O_NOFOLLOW is set)
 *
 * @param[in,out] file Pointer to file structure to be initialized
 * @param[in] path the specified file path.
 * @param[in] oflags the oflags for open operator. (O_RDONLY, O_WRONLY, O_CREAT, etc)
 * @param[in] mode File permission mode (used when O_CREAT is specified)
 *
 * @return 0 on successful, -1 on failure:
 *         -ENOENT if file doesn't exist and O_CREAT not set
 *         -EEXIST if file exists and O_EXCL|O_CREAT set
 *         -EPERM if permission denied
 *         -ENOTDIR if path is not a directory when O_DIRECTORY set
 *         -EISDIR if path is directory when opening as regular file
 */
int dfs_file_open(struct dfs_file *file, const char *path, int oflags, mode_t mode)
{
    int ret = -RT_ERROR;
    char *fullpath = RT_NULL;
    struct dfs_dentry *dentry = RT_NULL;
    int fflags = dfs_fflags(oflags);

    if (mode == 0)
    {
        mode = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* 0666 */
    }

    if (file && path)
    {
        fullpath = dfs_normalize_path(NULL, path);
        if (fullpath)
        {
            struct dfs_mnt *mnt = RT_NULL;

            DLOG(msg, "dfs_file", "mnt", DLOG_MSG, "dfs_mnt_lookup(%s)", fullpath);
            mnt = dfs_mnt_lookup(fullpath);
            if (mnt)
            {
                char *tmp = dfs_file_realpath(&mnt, fullpath, DFS_REALPATH_EXCEPT_LAST);
                if (tmp)
                {
                    rt_free(fullpath);
                    fullpath = tmp;
                }

                DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_lookup(mnt, %s)", fullpath);
                dentry = dfs_dentry_lookup(mnt, fullpath, oflags);
                if (dentry && dentry->vnode->type == FT_SYMLINK)
                {
                    /* it's a symbol link but not follow */
                    if (oflags & O_NOFOLLOW)
                    {
                        /* no follow symbol link */
                        dfs_dentry_unref(dentry);
                        dentry = RT_NULL;
                    }
                    else
                    {
                        struct dfs_dentry *target_dentry = RT_NULL;
                        char *path = dfs_file_realpath(&mnt, fullpath, DFS_REALPATH_ONLY_LAST);
                        if (path)
                        {
                            target_dentry = dfs_dentry_lookup(mnt, path, oflags);
                            rt_free(path);
                        }
                        dfs_dentry_unref(dentry);
                        dentry = target_dentry;
                    }
                }

                if (dentry)
                {
                    if (oflags & O_DIRECTORY)
                    {
                        if (dentry->vnode->type != FT_DIRECTORY)
                        {
                            dfs_dentry_unref(dentry);
                            dentry = RT_NULL;
                        }
                    }
                    else if (dentry->vnode->type == FT_DIRECTORY)
                    {
                        if (fflags & (DFS_F_FWRITE))
                        {
                            dfs_dentry_unref(dentry);
                            dentry = RT_NULL;
                        }
                        else
                        {
                            oflags |= O_DIRECTORY;
                        }
                    }
                }

                if (oflags & O_CREAT)
                {
                    if (dentry)
                    {
                        oflags &= ~O_CREAT;

                        if (oflags & O_EXCL)
                        {
                            oflags &= ~O_EXCL;
                            /* the dentry already exists */
                            dfs_dentry_unref(dentry);
                            ret = -EEXIST;
                            goto _ERR_RET;
                        }
                    }
                    else
                    {
                        /* create file/directory */
                        if (mnt->fs_ops->create_vnode)
                        {
                            struct dfs_vnode *vnode = RT_NULL;

                            DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_create(%s)", fullpath);
                            dfs_file_lock();
                            dentry = dfs_dentry_create(mnt, fullpath);
                            if (dentry)
                            {
                                DLOG(msg, "dfs_file", mnt->fs_ops->name, DLOG_MSG, "fs_ops->create_vnode");

                                if (dfs_is_mounted(mnt) == 0)
                                {
                                    vnode = mnt->fs_ops->create_vnode(dentry, oflags & O_DIRECTORY ? FT_DIRECTORY:FT_REGULAR, mode);
                                }

                                if (vnode)
                                {
                                    /* set vnode */
                                    dentry->vnode = vnode;  /* the refcount of created vnode is 1. no need to reference */
                                    dfs_dentry_insert(dentry);
                                }
                                else
                                {
                                    DLOG(msg, mnt->fs_ops->name, "dfs_file", DLOG_MSG_RET, "create failed.");
                                    dfs_dentry_unref(dentry);
                                    dentry = RT_NULL;
                                }
                            }
                            dfs_file_unlock();
                        }
                    }
                }

                if (dentry)
                {
                    rt_bool_t permission = RT_TRUE;
                    file->dentry = dentry;
                    file->vnode = dentry->vnode;
                    file->fops  = dentry->mnt->fs_ops->default_fops;
                    file->flags = oflags;

                    /* check permission */
                    if (!(oflags & O_CREAT))
                    {
                        if (fflags & DFS_F_FWRITE)
                        {
                            if (!(file->vnode->mode & S_IWUSR))
                            {
                                permission = RT_FALSE;
                            }
                        }

                        if (fflags & DFS_F_FREAD)
                        {
                            if (!(file->vnode->mode & S_IRUSR))
                            {
                                permission = RT_FALSE;
                            }
                        }

                        if (oflags & O_EXEC)
                        {
                            if (!(file->vnode->mode & S_IXUSR))
                            {
                                permission = RT_FALSE;
                            }
                        }
                    }

                    if (permission && file->fops->open)
                    {
                        DLOG(msg, "dfs_file", mnt->fs_ops->name, DLOG_MSG, "fops->open(file)");

                        if (dfs_is_mounted(file->vnode->mnt) == 0)
                        {
                            dfs_file_lock();
                            ret = file->fops->open(file);
                            dfs_file_unlock();
                        }
                        else
                        {
                            ret = -EINVAL;
                        }

                        if (ret < 0)
                        {
                            LOG_I("open %s failed in file system: %s", path, dentry->mnt->fs_ops->name);
                            DLOG(msg, mnt->fs_ops->name, "dfs_file", DLOG_MSG_RET, "open failed.");
                            dfs_file_unref(file);
                        }
                        else
                        {
                            /* for char/block device */
                            if ((S_ISCHR(file->vnode->mode)) || (S_ISBLK(file->vnode->mode)))
                            {
                                file->fops = file->vnode->fops;
                            }
                        }
                    }
                    else
                    {
                        DLOG(msg, "dfs_file", mnt->fs_ops->name, DLOG_MSG, "no permission or fops->open");
                        dfs_file_unref(file);
                        ret = -EPERM;
                    }
                }
                else
                {
                    LOG_I("lookup file:%s failed in file system", path);
                    ret = -ENOENT;
                }
            }
        }

        if (ret >= 0 && (oflags & O_TRUNC))
        {
            /* trunc file */
            if (!(fflags & DFS_F_FWRITE) || file->vnode->type == FT_DIRECTORY)
            {
                /* truncate on read a only file or a directory */
                DLOG(msg, "dfs_file", "dfs_file", DLOG_MSG, "dfs_file_unref(file), trunc on RDOnly or directory");
                ret = -RT_ERROR;
            }
            else
            {
                if (file->fops->truncate)
                {
                    DLOG(msg, "dfs_file", dentry->mnt->fs_ops->name, DLOG_MSG, "fops->truncate(file, 0)");

                    if (dfs_is_mounted(file->vnode->mnt) == 0)
                    {
#ifdef RT_USING_PAGECACHE
                        if (file->vnode->aspace)
                        {
                            dfs_aspace_clean(file->vnode->aspace);
                        }
#endif
                        ret = file->fops->truncate(file, 0);
                    }
                    else
                    {
                        ret = -EINVAL;
                    }
                }
            }

            if (ret < 0)
            {
                dfs_file_unref(file);
            }

            file->flags &= ~O_TRUNC;
        }
    }

_ERR_RET:
    if (fullpath != NULL)
    {
        rt_free(fullpath);
    }
    return ret;
}

/**
 * @brief Close a file and release associated resources
 *
 * This function closes a file and performs necessary cleanup operations:
 * - Flushes page cache if enabled (RT_USING_PAGECACHE)
 * - Calls filesystem-specific close operation if available
 * - Decrements reference count and releases resources when count reaches zero
 *
 * @param[in,out] file Pointer to the file structure to close
 *
 * @return int Operation result:
 *         - 0 on success
 *         - Negative error code on failure
 */
int dfs_file_close(struct dfs_file *file)
{
    int ret = -RT_ERROR;

    if (file)
    {
        if (dfs_file_lock() == RT_EOK)
        {
            rt_atomic_t ref_count = rt_atomic_load(&(file->ref_count));

            if (ref_count == 1 && file->fops && file->fops->close)
            {
                DLOG(msg, "dfs_file", file->dentry->mnt->fs_ops->name, DLOG_MSG, "fops->close(file)");
#ifdef RT_USING_PAGECACHE
                if (file->vnode->aspace)
                {
                    dfs_aspace_flush(file->vnode->aspace);
                }
#endif
                ret = file->fops->close(file);

                if (ret == 0) /* close file sucessfully */
                {
                    DLOG(msg, "dfs_file", "dfs_file", DLOG_MSG, "dfs_file_unref(file)");
                    dfs_file_unref(file);
                }
                else
                {
                    LOG_W("close file:%s failed on low level file system", file->dentry->pathname);
                }
            }
            else
            {
                DLOG(msg, "dfs_file", "dfs_file", DLOG_MSG, "dfs_file_unref(file)");
                dfs_file_unref(file);
                ret = 0;
            }
            dfs_file_unlock();
        }
    }

    return ret;
}

/**
 * @brief Read data from a file at specified offset
 *
 * @param[in] file Pointer to the file structure to read from
 * @param[out] buf Buffer to store the read data
 * @param[in] len Number of bytes to read
 * @param[in] offset Offset in the file to start reading from
 *
 * @return ssize_t Number of bytes read on success, or negative error code:
 *         -EBADF if invalid file descriptor
 *         -EPERM if read permission denied
 *         -ENOSYS if read operation not supported
 *         -EINVAL if invalid parameters or not mounted
 */
ssize_t dfs_file_pread(struct dfs_file *file, void *buf, size_t len, off_t offset)
{
    ssize_t ret = -EBADF;

    if (file)
    {
        /* check whether read */
        if (!(dfs_fflags(file->flags) & DFS_F_FREAD))
        {
            ret = -EPERM;
        }
        else if (!file->fops || !file->fops->read)
        {
            ret = -ENOSYS;
        }
        else if (file->vnode && file->vnode->type != FT_DIRECTORY)
        {
            off_t pos = offset;

            ret = rw_verify_area(file, &pos, len);
            if (ret > 0)
            {
                len = ret;

                if (dfs_is_mounted(file->vnode->mnt) == 0)
                {
#ifdef RT_USING_PAGECACHE
                    if (file->vnode->aspace && !(file->flags & O_DIRECT))
                    {
                        ret = dfs_aspace_read(file, buf, len, &pos);
                    }
                    else
#endif
                    {
                        ret = file->fops->read(file, buf, len, &pos);
                    }
                }
                else
                {
                    ret = -EINVAL;
                }
            }
        }
    }

    return ret;
}

/**
 * @brief Read data from a file at current position
 *
 * @param[in] file Pointer to the file structure to read from
 * @param[out] buf Buffer to store the read data
 * @param[in] len Number of bytes to read
 *
 * @return ssize_t Number of bytes read on success, or negative error code:
 *         -EBADF if invalid file descriptor
 *         -EPERM if read permission denied
 *         -ENOSYS if read operation not supported
 *         -EINVAL if invalid parameters or not mounted
 */
ssize_t dfs_file_read(struct dfs_file *file, void *buf, size_t len)
{
    ssize_t ret = -EBADF;

    if (file)
    {
        /* check whether read */
        if (!(dfs_fflags(file->flags) & DFS_F_FREAD))
        {
            ret = -EPERM;
        }
        else if (!file->fops || !file->fops->read)
        {
            ret = -ENOSYS;
        }
        else if (file->vnode && file->vnode->type != FT_DIRECTORY)
        {
            /* fpos lock */
            off_t pos = dfs_file_get_fpos(file);

            ret = rw_verify_area(file, &pos, len);
            if (ret > 0)
            {
                len = ret;

                if (dfs_is_mounted(file->vnode->mnt) == 0)
                {
#ifdef RT_USING_PAGECACHE
                    if (file->vnode->aspace && !(file->flags & O_DIRECT))
                    {
                        ret = dfs_aspace_read(file, buf, len, &pos);
                    }
                    else
#endif
                    {
                        ret = file->fops->read(file, buf, len, &pos);
                    }
                }
                else
                {
                    ret = -EINVAL;
                }
            }
            /* fpos unlock */
            dfs_file_set_fpos(file, pos);
        }
    }

    return ret;
}

/**
 * @brief Write data to a file at specified offset
 *
 * @param[in] file Pointer to the file structure to write to
 * @param[in] buf Buffer containing data to write
 * @param[in] len Number of bytes to write
 * @param[in] offset Offset in the file to start writing from
 *
 * @return ssize_t Number of bytes written on success, or negative error code:
 *         -EBADF if invalid file descriptor or bad write flags
 *         -ENOSYS if write operation not supported
 *         -EINVAL if invalid parameters or not mounted
 *
 * @note If O_SYNC flag is set, the data will be immediately flushed to storage device
 *       after write operation.
 */
ssize_t dfs_file_pwrite(struct dfs_file *file, const void *buf, size_t len, off_t offset)
{
    ssize_t ret = -EBADF;

    if (file)
    {
        if (!(dfs_fflags(file->flags) & DFS_F_FWRITE))
        {
            LOG_W("bad write flags.");
            ret = -EBADF;
        }
        else if (!file->fops || !file->fops->write)
        {
            LOG_W("no fops write.");
            ret = -ENOSYS;
        }
        else if (file->vnode && file->vnode->type != FT_DIRECTORY)
        {
            off_t pos = offset;

            ret = rw_verify_area(file, &pos, len);
            if (ret > 0)
            {
                len = ret;
                DLOG(msg, "dfs_file", file->dentry->mnt->fs_ops->name, DLOG_MSG,
                    "dfs_file_write(fd, buf, %d)", len);

                if (dfs_is_mounted(file->vnode->mnt) == 0)
                {
#ifdef RT_USING_PAGECACHE
                    if (file->vnode->aspace && !(file->flags & O_DIRECT))
                    {
                        ret = dfs_aspace_write(file, buf, len, &pos);
                    }
                    else
#endif
                    {
                        ret = file->fops->write(file, buf, len, &pos);
                    }

                    if (file->flags & O_SYNC)
                    {
                        file->fops->flush(file);
                    }
                }
                else
                {
                    ret = -EINVAL;
                }
            }
        }
    }

    return ret;
}

/**
 * @brief Write data to a file at current position
 *
 * This function writes data to a file at the current position or at the end if O_APPEND flag is set.
 *
 * @param[in,out] file Pointer to the file structure to write to
 * @param[in] buf Buffer containing data to write
 * @param[in] len Number of bytes to write
 *
 * @return ssize_t Number of bytes written on success, or negative error code:
 *         -EBADF if invalid file descriptor or bad write flags
 *         -ENOSYS if write operation not supported
 *         -EINVAL if invalid parameters or not mounted
 *
 * @note If O_SYNC flag is set, the data will be immediately flushed to storage device
 * @note In append mode (O_APPEND), data is always written at the end of file
 */
ssize_t dfs_file_write(struct dfs_file *file, const void *buf, size_t len)
{
    ssize_t ret = -EBADF;

    if (file)
    {
        if (!(dfs_fflags(file->flags) & DFS_F_FWRITE))
        {
            LOG_W("bad write flags.");
            ret = -EBADF;
        }
        else if (!file->fops || !file->fops->write)
        {
            LOG_W("no fops write.");
            ret = -ENOSYS;
        }
        else if (file->vnode && file->vnode->type != FT_DIRECTORY)
        {
            off_t pos;

            if (!(file->flags & O_APPEND))
            {
                /* fpos lock */
                pos = dfs_file_get_fpos(file);
            }
            else
            {
                pos = file->vnode->size;
            }

            ret = rw_verify_area(file, &pos, len);
            if (ret > 0)
            {
                len = ret;
                DLOG(msg, "dfs_file", file->dentry->mnt->fs_ops->name, DLOG_MSG,
                    "dfs_file_write(fd, buf, %d)", len);

                if (dfs_is_mounted(file->vnode->mnt) == 0)
                {
#ifdef RT_USING_PAGECACHE
                    if (file->vnode->aspace && !(file->flags & O_DIRECT))
                    {
                        ret = dfs_aspace_write(file, buf, len, &pos);
                    }
                    else
#endif
                    {
                        ret = file->fops->write(file, buf, len, &pos);
                    }

                    if (file->flags & O_SYNC)
                    {
                        file->fops->flush(file);
                    }
                }
                else
                {
                    ret = -EINVAL;
                }
            }
            if (!(file->flags & O_APPEND))
            {
                /* fpos unlock */
                dfs_file_set_fpos(file, pos);
            }
        }
    }

    return ret;
}

/**
 * @brief Generic file seek implementation
 *
 * This function calculates the new file position based on the specified offset and whence parameter.
 * It supports three seek modes:
 * - SEEK_SET: Set position relative to start of file
 * - SEEK_CUR: Set position relative to current position
 * - SEEK_END: Set position relative to end of file
 *
 * @param[in] file Pointer to the file structure containing current position
 * @param[in] offset Offset value to seek
 * @param[in] whence Seek mode (SEEK_SET/SEEK_CUR/SEEK_END)
 *
 * @return off_t The calculated new file position, or -EINVAL for invalid whence
 */
off_t generic_dfs_lseek(struct dfs_file *file, off_t offset, int whence)
{
    off_t foffset;

    if (whence == SEEK_SET)
        foffset = offset;
    else if (whence == SEEK_CUR)
        foffset = file->fpos + offset;
    else if (whence == SEEK_END)
        foffset = file->vnode->size + offset;
    else
        return -EINVAL;

    return foffset;
}

/**
 * @brief Change the file position indicator
 *
 * This function sets the file position indicator for the file referenced by the file descriptor
 * based on the offset and whence parameters.
 *
 * @param[in,out] file Pointer to the file structure (position will be modified)
 * @param[in] offset Number of bytes to offset from position
 * @param[in] whence Reference position (SEEK_SET/SEEK_CUR/SEEK_END)
 *
 * @return off_t New file position on success, or negative error code:
 *         -EINVAL if invalid parameters or not mounted
 */
off_t dfs_file_lseek(struct dfs_file *file, off_t offset, int wherece)
{
    off_t retval = -EINVAL;

    if (file && file->fops->lseek)
    {
        if (dfs_is_mounted(file->vnode->mnt) == 0)
        {
            /* fpos lock */
            off_t pos = dfs_file_get_fpos(file);
            retval = file->fops->lseek(file, offset, wherece);
            if (retval >= 0)
            {
                pos = retval;
            }
            /* fpos unlock */
            dfs_file_set_fpos(file, pos);
        }
    }

    return retval;
}

/**
 * @brief Get file status information
 *
 * @param[in] path The file path to get status for
 * @param[out] buf Pointer to stat structure to store the status information
 *
 * @return int Operation result:
 *         - 0 on success
 *         -ENOENT if file not found
 *         -ENOMEM if memory allocation failed
 *         Other negative error codes from filesystem operations
 */
int dfs_file_stat(const char *path, struct stat *buf)
{
    int ret = -ENOENT;
    char *fullpath = RT_NULL;
    struct dfs_mnt *mnt = RT_NULL;
    struct dfs_dentry *dentry = RT_NULL;

    fullpath = dfs_normalize_path(NULL, path);
    if (fullpath)
    {
        DLOG(msg, "dfs_file", "mnt", DLOG_MSG, "dfs_mnt_lookup(%s)", fullpath);
        mnt = dfs_mnt_lookup(fullpath);
        if (mnt)
        {
            char *tmp = dfs_file_realpath(&mnt, fullpath, DFS_REALPATH_EXCEPT_NONE);
            if (tmp)
            {
                rt_free(fullpath);
                fullpath = tmp;
            }

            DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dentry = dfs_dentry_lookup(mnt, %s)", fullpath);
            dentry = dfs_dentry_lookup(mnt, fullpath, 0);
            if (dentry)
            {
                DLOG(msg, "dentry", "dfs_file", DLOG_MSG_RET, "return dentry");
                if (mnt->fs_ops->stat)
                {
                    DLOG(msg, "dfs_file", mnt->fs_ops->name, DLOG_MSG, "fs_ops->stat(dentry, buf)");

                    if (dfs_is_mounted(mnt) == 0)
                    {
                        ret = mnt->fs_ops->stat(dentry, buf);
                    }
                }

                /* unref dentry */
                DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_unref(dentry)");
                dfs_dentry_unref(dentry);
                dentry = RT_NULL;
            }
        }

        rt_free(fullpath);
        fullpath = RT_NULL;
    }
    else
    {
        ret = -ENOMEM;
    }

    return ret;
}

/**
 * @brief Get file status information without following symbolic links
 *
 * @param[in] path The file path to get status for (does not follow symlinks)
 * @param[out] buf Pointer to stat structure to store the status information
 *
 * @return int Operation result:
 *         - 0 on success
 *         -ENOENT if file not found
 *         -ENOMEM if memory allocation failed
 *         Other negative error codes from filesystem operations
 *
 * @note Unlike dfs_file_stat(), this function does not follow symbolic links
 * @see dfs_file_stat()
 */
int dfs_file_lstat(const char *path, struct stat *buf)
{
    int ret = -ENOENT;
    char *fullpath = RT_NULL;
    struct dfs_mnt *mnt = RT_NULL;
    struct dfs_dentry *dentry = RT_NULL;

    fullpath = dfs_normalize_path(NULL, path);
    if (fullpath)
    {
        DLOG(msg, "dfs_file", "mnt", DLOG_MSG, "dfs_mnt_lookup(%s)", fullpath);
        mnt = dfs_mnt_lookup(fullpath);
        if (mnt)
        {
            char *tmp = dfs_file_realpath(&mnt, fullpath, DFS_REALPATH_EXCEPT_LAST);
            if (tmp)
            {
                rt_free(fullpath);
                fullpath = tmp;
            }

            DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dentry = dfs_dentry_lookup(mnt, %s)", fullpath);
            dentry = dfs_dentry_lookup(mnt, fullpath, 0);
            if (dentry)
            {
                DLOG(msg, "dentry", "dfs_file", DLOG_MSG_RET, "return dentry");
                if (mnt->fs_ops->stat)
                {
                    DLOG(msg, "dfs_file", mnt->fs_ops->name, DLOG_MSG, "fs_ops->stat(dentry, buf)");

                    if (dfs_is_mounted(mnt) == 0)
                    {
                        ret = mnt->fs_ops->stat(dentry, buf);
                    }
                }

                /* unref dentry */
                DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_unref(dentry)");
                dfs_dentry_unref(dentry);
                dentry = RT_NULL;
            }
        }

        rt_free(fullpath);
        fullpath = RT_NULL;
    }
    else
    {
        ret = -ENOMEM;
    }

    rt_set_errno(-ret);

    return ret;
}

/**
 * @brief Get file status information using file descriptor
 *
 * @param[in] file Pointer to the open file structure
 * @param[out] buf Pointer to stat structure to store status information
 *
 * @return int Operation result:
 *         - 0 on success
 *         -EBADF if invalid file descriptor
 *         -ENOSYS if operation not supported
 *
 * @note Currently unimplemented (returns -ENOSYS)
 */
int dfs_file_fstat(struct dfs_file *file, struct stat *buf)
{
    size_t ret = -EBADF;

    if (file)
    {
        if (file->fops && file->fops->ioctl)
        {
            /* ret = file->fops->fstat(file, buf); */
        }
        else
        {
            ret = -ENOSYS;
        }
    }
    else
    {
        ret = -EBADF;
    }

    return ret;
}

/**
 * @brief Set file attributes for the specified path
 *
 * This function sets file attributes (permissions, ownership, timestamps, etc.)
 * for the file specified by path.
 *
 * @param[in] path The file path to set attributes for
 * @param[in] attr Pointer to attribute structure containing new attributes
 *
 * @return int Operation result:
 *         - 0 on success
 *         -RT_ERROR if general error occurred
 *         -ENOENT if file not found
 *         Other negative error codes from filesystem operations
 *
 * @note The actual supported attributes depend on the underlying filesystem
 */
int dfs_file_setattr(const char *path, struct dfs_attr *attr)
{
    int ret = -RT_ERROR;
    char *fullpath = RT_NULL;
    struct dfs_mnt *mnt = RT_NULL;
    struct dfs_dentry *dentry = RT_NULL;

    fullpath = dfs_normalize_path(NULL, path);
    if (fullpath)
    {
        DLOG(msg, "dfs_file", "mnt", DLOG_MSG, "dfs_mnt_lookup(%s)", fullpath);
        mnt = dfs_mnt_lookup(fullpath);
        if (mnt)
        {
            char *tmp = dfs_file_realpath(&mnt, fullpath, DFS_REALPATH_EXCEPT_LAST);
            if (tmp)
            {
                rt_free(fullpath);
                fullpath = tmp;
            }

            DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dentry = dfs_dentry_lookup(mnt, %s)", fullpath);
            dentry = dfs_dentry_lookup(mnt, fullpath, 0);
            if (dentry)
            {
                DLOG(msg, "dentry", "dfs_file", DLOG_MSG_RET, "return dentry");
                if (mnt->fs_ops->setattr)
                {
                    DLOG(msg, "dfs_file", mnt->fs_ops->name, DLOG_MSG, "fs_ops->setattr(dentry, attr)");

                    if (dfs_is_mounted(mnt) == 0)
                    {
                        ret = mnt->fs_ops->setattr(dentry, attr);
                    }
                }

                /* unref dentry */
                DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_unref(dentry)");
                dfs_dentry_unref(dentry);
                dentry = RT_NULL;
            }
        }

        rt_free(fullpath);
        fullpath = RT_NULL;
    }

    return ret;
}

/**
 * @brief Perform device-specific control operations
 *
 * This function performs device-specific control operations on an open file descriptor.
 * It is typically used for operations that cannot be expressed by regular file operations.
 *
 * @param[in] file Pointer to the file structure to perform ioctl on
 * @param[in] cmd Device-dependent request code
 * @param[in,out] args Pointer to optional argument buffer (input/output depends on cmd)
 *
 * @return int Operation result:
 *         - 0 or positive value on success (meaning depends on cmd)
 *         -EBADF if invalid file descriptor
 *         -ENOSYS if ioctl operation not supported
 *         -EINVAL if invalid parameters or not mounted
 *
 * @note The actual supported commands and their semantics depend on the underlying device driver
 */
int dfs_file_ioctl(struct dfs_file *file, int cmd, void *args)
{
    size_t ret = 0;

    if (file)
    {
        if (file->fops && file->fops->ioctl)
        {
            if (dfs_is_mounted(file->vnode->mnt) == 0)
            {
                ret = file->fops->ioctl(file, cmd, args);
            }
            else
            {
                ret = -EINVAL;
            }
        }
        else
        {
            ret = -ENOSYS;
        }
    }
    else
    {
        ret = -EBADF;
    }

    return ret;
}

/**
 * @brief Perform file control operations
 *
 * This function performs various control operations on an open file descriptor.
 * It supports the following operations:
 * - F_DUPFD: Duplicate file descriptor
 * - F_GETFD: Get file descriptor flags
 * - F_SETFD: Set file descriptor flags
 * - F_GETFL: Get file status flags
 * - F_SETFL: Set file status flags
 * - F_GETLK/F_SETLK/F_SETLKW: File locking operations (unimplemented)
 * - F_DUPFD_CLOEXEC: Duplicate file descriptor with close-on-exec flag (if supported)
 *
 * @param[in] fd File descriptor to operate on
 * @param[in] cmd Control command (F_DUPFD/F_GETFD/F_SETFD/F_GETFL/F_SETFL/etc)
 * @param[in,out] arg Command-specific argument (input/output depends on cmd)
 *
 * @return int Operation result:
 *         - For F_DUPFD: new file descriptor on success
 *         - For F_GETFD/F_GETFL: current flags on success
 *         - 0 on success for other commands
 *         -EBADF if invalid file descriptor
 *         -EINVAL if invalid command (F_DUPFD_CLOEXEC when not supported)
 *         -EPERM for unsupported commands
 *
 * @note Not all commands may be supported by all filesystems
 * @note File locking operations (F_GETLK/F_SETLK/F_SETLKW) are currently unimplemented
 */
int dfs_file_fcntl(int fd, int cmd, unsigned long arg)
{
    int ret = 0;
    struct dfs_file *file;

    file = fd_get(fd);
    if (file)
    {
        switch (cmd)
        {
        case F_DUPFD:
            ret = dfs_dup(fd, arg);
            break;
        case F_GETFD:
            ret = file->mode;
            break;
        case F_SETFD:
            file->mode = arg;
            break;
        case F_GETFL:
            ret = file->flags;
            break;
        case F_SETFL:
        {
            int flags = (int)(rt_base_t)arg;
            int mask =
#ifdef O_ASYNC
                        O_ASYNC |
#endif
#ifdef O_DIRECT
                        O_DIRECT |
#endif
#ifdef O_NOATIME
                        O_NOATIME |
#endif
                        O_APPEND | O_NONBLOCK;

            flags &= mask;
            file->flags &= ~mask;
            file->flags |= flags;
            break;
        }
        case F_GETLK:
            break;
        case F_SETLK:
        case F_SETLKW:
            break;
#ifdef RT_USING_MUSLLIBC
        case F_DUPFD_CLOEXEC:
            ret = -EINVAL;
            break;
#endif
        default:
            ret = -EPERM;
            break;
        }
    }
    else
    {
        ret = -EBADF;
    }

    return ret;
}

/**
 * @brief Synchronize file data to storage device
 *
 * This function flushes all modified file data and metadata to the underlying storage device.
 * It ensures data integrity by:
 * - Flushing page cache if enabled (RT_USING_PAGECACHE)
 * - Calling filesystem-specific flush operation
 *
 * @param[in] file Pointer to the file structure to synchronize
 *
 * @return int Operation result:
 *         - 0 on success
 *         -EBADF if invalid file descriptor
 *         -EINVAL if not mounted or invalid parameters
 *
 * @note This function provides stronger guarantees than regular writes
 *       about data persistence on storage media
 */
int dfs_file_fsync(struct dfs_file *file)
{
    int ret = -EBADF;

    if (file)
    {
        if (file->fops->flush)
        {
            if (dfs_is_mounted(file->vnode->mnt) == 0)
            {
#ifdef RT_USING_PAGECACHE
                if (file->vnode->aspace)
                {
                    dfs_aspace_flush(file->vnode->aspace);
                }
#endif
                ret = file->fops->flush(file);
            }
            else
            {
                ret = -EINVAL;
            }
        }
    }

    return ret;
}

/**
 * @brief Delete a file or directory entry from the filesystem
 *
 * This function removes a filesystem entry (file or empty directory) specified by path.
 *
 * @param[in] path The filesystem path to be deleted
 *
 * @return int Operation result:
 *         - 0 on success
 *         -RT_ERROR if general error occurred
 *         -ENOENT if file not found
 *         -ENOMEM if memory allocation failed
 *         -EBUSY if file is in use (mount point or has child mounts)
 *         Other negative error codes from filesystem operations
 *
 * @note This function cannot remove non-empty directories
 * @note Mount points cannot be removed while mounted
 */
int dfs_file_unlink(const char *path)
{
    int ret = -RT_ERROR;
    char *fullpath = RT_NULL;
    struct dfs_mnt *mnt = RT_NULL;
    struct dfs_dentry *dentry = RT_NULL;

    fullpath = dfs_normalize_path(NULL, path);
    if (fullpath)
    {
        DLOG(msg, "dfs_file", "mnt", DLOG_MSG, "dfs_mnt_lookup(%s)", fullpath);
        mnt = dfs_mnt_lookup(fullpath);
        if (mnt)
        {
            char *tmp = dfs_file_realpath(&mnt, fullpath, DFS_REALPATH_EXCEPT_LAST);
            if (tmp)
            {
                rt_free(fullpath);
                fullpath = tmp;
            }

            if (strcmp(mnt->fullpath, fullpath) != 0)
            {
                DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_lookup(mnt, %s)", fullpath);
                dentry = dfs_dentry_lookup(mnt, fullpath, 0);
                if (dentry)
                {
                    rt_bool_t has_child = RT_FALSE;

                    has_child = dfs_mnt_has_child_mnt(mnt, fullpath);
#ifdef RT_USING_PAGECACHE
                    if (dentry->vnode->aspace)
                    {
                        dfs_aspace_clean(dentry->vnode->aspace);
                    }
#endif
                    dfs_file_lock();

                    if (has_child == RT_FALSE)
                    {
                        /* no child mnt point, unlink it */
                        ret = -RT_ERROR;

                        if (mnt->fs_ops->unlink)
                        {
                            if (dfs_is_mounted(mnt) == 0)
                            {
                                ret = mnt->fs_ops->unlink(dentry);
                            }
                        }
                    }
                    else
                    {
                        ret = -EBUSY;
                    }
                    dfs_file_unlock();

                    /* release this dentry */
                    dfs_dentry_unref(dentry);
                }
                else
                {
                    /* no this entry */
                    ret = -ENOENT;
                }
            }
            else
            {
                /* it's a mount point, failed for busy */
                ret = -EBUSY;
            }
        }
        else
        {
            ret = -ENOENT;
        }

        /* release fullpath */
        rt_free(fullpath);
    }
    else
    {
        ret = -ENOMEM;
    }

    return ret;
}

/**
 * @brief Create a hard link between files
 *
 * This function creates a hard link named 'newname' which refers to the same file as 'oldname'.
 *
 * @param[in] oldname Path to the existing file to link from
 * @param[in] newname Path to the new link to be created
 *
 * @return int Operation result:
 *         - 0 on success
 *         -1 on general error
 *         -EPERM if oldname is a directory
 *         Other negative error codes from filesystem operations
 *
 * @note Both files must reside on the same filesystem
 * @note The function will fail if newname already exists
 */
int dfs_file_link(const char *oldname, const char *newname)
{
    int ret = -1;
    struct stat stat;
    struct dfs_mnt *mnt = RT_NULL;
    char *old_fullpath, *new_fullpath;

    if (dfs_file_isdir(oldname) == 0)
    {
        rt_set_errno(-EPERM);
        return ret;
    }

    if (dfs_file_lstat(newname, &stat) >= 0)
    {
        return ret;
    }

    old_fullpath = dfs_normalize_path(NULL, oldname);
    if (old_fullpath)
    {
        DLOG(msg, "dfs_file", "mnt", DLOG_MSG, "dfs_mnt_lookup(%s)", old_fullpath);
        mnt = dfs_mnt_lookup(old_fullpath);
        if (mnt == RT_NULL)
        {
            rt_free(old_fullpath);
            return -1;
        }

        char *tmp = dfs_file_realpath(&mnt, old_fullpath, DFS_REALPATH_EXCEPT_LAST);
        if (tmp)
        {
            rt_free(old_fullpath);
            old_fullpath = tmp;
        }
    }

    new_fullpath = dfs_normalize_path(NULL, newname);
    if (new_fullpath)
    {
        char *tmp = dfs_file_realpath(&mnt, new_fullpath, DFS_REALPATH_EXCEPT_LAST);
        if (tmp)
        {
            rt_free(new_fullpath);
            new_fullpath = tmp;
        }
    }

    if (old_fullpath && new_fullpath)
    {
        struct dfs_dentry *old_dentry, *new_dentry;

        DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_lookup(mnt, %s)", old_fullpath);
        old_dentry = dfs_dentry_lookup(mnt, old_fullpath, 0);
        DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_create(%s)", new_fullpath);
        new_dentry = dfs_dentry_create(mnt, new_fullpath);

        if (old_dentry && new_dentry)
        {
            if (mnt->fs_ops->link)
            {
                if (dfs_is_mounted(mnt) == 0)
                {
                    ret = mnt->fs_ops->link(old_dentry, new_dentry);
                }
            }
        }

        dfs_dentry_unref(old_dentry);
        dfs_dentry_unref(new_dentry);
    }

    if (old_fullpath)
    {
        rt_free(old_fullpath);
    }

    if (new_fullpath)
    {
        rt_free(new_fullpath);
    }

    return ret;
}

/**
 * @brief Create a symbolic link named 'linkpath' containing the string 'target'
 *
 * This function creates a symbolic link which refers to the specified target path.
 * The linkpath should not exist before calling this function.
 *
 * @param[in] target The path string that the symbolic link will point to
 * @param[in] linkpath The path where the symbolic link will be created
 *
 * @return int Operation status:
 *         - 0 on success
 *         -ENOSYS if symlink operation not supported by filesystem
 *         -ENOENT if parent directory doesn't exist
 *         -EPERM if linkpath already exists
 *         -EINVAL if invalid parameters
 *         -RT_ERROR for general errors
 */
int dfs_file_symlink(const char *target, const char *linkpath)
{
    int ret = -RT_ERROR;
    char *fullpath = RT_NULL, *parent = RT_NULL;
    struct dfs_mnt *mnt = RT_NULL;
    struct dfs_dentry *dentry = RT_NULL;

    if (target && linkpath)
    {
        if (linkpath[0] != '/')
        {
           fullpath = dfs_normalize_path(NULL, linkpath);
        }
        else
        {
            fullpath = (char*)linkpath;
        }

        /* linkpath should be not exist */
        if (dfs_file_access(fullpath, O_RDONLY) != 0)
        {
            char *index;

            /* get parent path */
            index = strrchr(fullpath, '/');
            if (index)
            {
                int length = index - fullpath;
                if (length > 0)
                {
                    parent = (char*) rt_malloc (length + 1);
                    if (parent)
                    {
                        memcpy(parent, fullpath, length);
                        parent[length] = '\0';
                    }
                }
                else
                {
                    parent = (char*) rt_malloc (1 + 1);
                    if (parent)
                    {
                        parent[0] = '/';
                        parent[1] = '\0';
                    }
                }
            }

            if (parent)
            {
                DLOG(msg, "dfs_file", "mnt", DLOG_MSG, "dfs_mnt_lookup(%s)", fullpath);
                mnt = dfs_mnt_lookup(parent);
                if (mnt)
                {
                    char *tmp = dfs_file_realpath(&mnt, parent, DFS_REALPATH_EXCEPT_LAST);
                    if (tmp)
                    {
                        rt_free(parent);
                        parent = tmp;
                    }

                    DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_lookup(mnt, %s)", fullpath);
                    dentry = dfs_dentry_lookup(mnt, parent, DFS_REALPATH_EXCEPT_LAST);
                    if (dentry)
                    {
                        if (dentry->mnt->fs_ops->symlink)
                        {
                            char *path = dfs_normalize_path(parent, target);
                            if (path)
                            {
                                ret = rt_strncmp(parent, path, strlen(parent));
                                if (ret == 0)
                                {
                                    tmp = path + strlen(parent);
                                    if (*tmp == '/')
                                    {
                                        tmp ++;
                                    }
                                }
                                else
                                {
                                    tmp = path;
                                }

                                if (dfs_is_mounted(mnt) == 0)
                                {
                                    ret = mnt->fs_ops->symlink(dentry, tmp, index + 1);
                                }

                                rt_free(path);
                            }
                        }
                        else
                        {
                            ret = -ENOSYS;
                        }

                        dfs_dentry_unref(dentry);
                    }
                    else
                    {
                        ret = -ENOENT;
                    }
                }
                else
                {
                    ret = -ENOENT;
                }

                rt_free(parent);
            }
        }
        else
        {
            rt_set_errno(-EPERM);
        }

        if (fullpath != linkpath)
            rt_free(fullpath);
    }
    else
    {
        ret = -EINVAL;
    }

    return ret;
}

/**
 * @brief Read the contents of a symbolic link
 *
 * This function reads the contents of the symbolic link specified by path into
 * the buffer provided.
 *
 * @param[in] path The path to the symbolic link to be read
 * @param[out] buf Buffer to store the link contents
 * @param[in] bufsize Size of the buffer in bytes
 *
 * @return int Number of bytes placed in buffer on success, or negative error code:
 *         -ENOSYS if readlink operation not supported by filesystem
 *         -ENOENT if symbolic link does not exist
 *         -ENOMEM if memory allocation failed
 *         -EINVAL if invalid parameters
 *         -RT_ERROR for general errors
 */
int dfs_file_readlink(const char *path, char *buf, int bufsize)
{
    int ret = -RT_ERROR;
    char *fullpath = RT_NULL;
    struct dfs_mnt *mnt = RT_NULL;
    struct dfs_dentry *dentry = RT_NULL;

    fullpath = dfs_normalize_path(NULL, path);
    if (fullpath)
    {
        DLOG(msg, "dfs_file", "mnt", DLOG_MSG, "dfs_mnt_lookup(%s)", fullpath);
        mnt = dfs_mnt_lookup(fullpath);
        if (mnt)
        {
            char *tmp = dfs_file_realpath(&mnt, fullpath, DFS_REALPATH_EXCEPT_LAST);
            if (tmp)
            {
                rt_free(fullpath);
                fullpath = tmp;
            }

            DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_lookup(mnt, %s)", fullpath);
            dentry = dfs_dentry_lookup(mnt, fullpath, 0);
            if (dentry)
            {
                if (mnt->fs_ops->readlink)
                {
                    if (dfs_is_mounted(mnt) == 0)
                    {
                        ret = mnt->fs_ops->readlink(dentry, buf, bufsize);
                    }
                }
                else
                {
                    ret = -ENOSYS;
                }

                /* release this dentry */
                dfs_dentry_unref(dentry);
            }
            else
            {
                /* no this entry */
                ret = -ENOENT;
            }
        }
        else
        {
            ret = -ENOENT;
        }

        /* release fullpath */
        rt_free(fullpath);
    }
    else
    {
        ret = -ENOMEM;
    }

    return ret;
}

/**
 * @brief Rename a file/directory
 *
 * This function renames a filesystem entry from old_file to new_file.
 *
 * @param[in] old_file Path to the existing file/directory to be renamed
 * @param[in] new_file New path for the file/directory
 *
 * @return int Operation result:
 *         - 0 on success
 *         -1 on general error
 *         -ENOMEM if memory allocation failed
 *         -ENOSYS if rename operation not supported
 *         -EINVAL if invalid parameters or not mounted
 *
 * @note Page cache will be cleaned if RT_USING_PAGECACHE is enabled
 */
int dfs_file_rename(const char *old_file, const char *new_file)
{
    int ret = -1;
    struct dfs_mnt *mnt = RT_NULL;
    char *old_fullpath, *new_fullpath;

    old_fullpath = dfs_normalize_path(NULL, old_file);
    if (old_fullpath)
    {
        DLOG(msg, "dfs_file", "mnt", DLOG_MSG, "dfs_mnt_lookup(%s)", old_fullpath);
        mnt = dfs_mnt_lookup(old_fullpath);
        if (mnt == RT_NULL)
        {
            rt_free(old_fullpath);
            return -1;
        }

        char *tmp = dfs_file_realpath(&mnt, old_fullpath, DFS_REALPATH_EXCEPT_LAST);
        if (tmp)
        {
            rt_free(old_fullpath);
            old_fullpath = tmp;
        }
    }

    new_fullpath = dfs_normalize_path(NULL, new_file);
    if (new_fullpath)
    {
        char *tmp = dfs_file_realpath(&mnt, new_fullpath, DFS_REALPATH_EXCEPT_LAST);
        if (tmp)
        {
            rt_free(new_fullpath);
            new_fullpath = tmp;
        }
    }

    if (old_fullpath && new_fullpath)
    {
        struct dfs_dentry *old_dentry, *new_dentry;

        DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_lookup(mnt, %s)", old_fullpath);
        old_dentry = dfs_dentry_lookup(mnt, old_fullpath, 0);
        DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_create(%s)", new_fullpath);
        new_dentry = dfs_dentry_create(mnt, new_fullpath);

        if (old_dentry && new_dentry)
        {
            if (mnt->fs_ops->rename)
            {
                if (dfs_is_mounted(mnt) == 0)
                {
#ifdef RT_USING_PAGECACHE
                    if (old_dentry->vnode->aspace)
                    {
                        dfs_aspace_clean(old_dentry->vnode->aspace);
                    }
#endif
                    ret = mnt->fs_ops->rename(old_dentry, new_dentry);
                }
            }
        }

        dfs_dentry_unref(old_dentry);
        dfs_dentry_unref(new_dentry);
    }

    if (old_fullpath)
    {
        rt_free(old_fullpath);
    }

    if (new_fullpath)
    {
        rt_free(new_fullpath);
    }

    return ret;
}

/**
 * @brief Truncate or extend a file to the specified length
 *
 * This function changes the size of the file referenced by the file descriptor.
 * If the new size is smaller than current size, the file is truncated.
 * If larger, the file is extended and the extended area is filled with zeros.
 *
 * @param[in] file Pointer to the file structure to truncate
 * @param[in] length New length of the file in bytes
 *
 * @return int Operation result:
 *         - 0 on success
 *         -EBADF if invalid file descriptor
 *         -ENOSYS if truncate operation not supported
 *         -EINVAL if invalid parameters or not mounted
 *
 * @note If RT_USING_PAGECACHE is enabled, the page cache will be cleaned
 *       before truncation to ensure data consistency
 */
int dfs_file_ftruncate(struct dfs_file *file, off_t length)
{
    int ret = 0;

    if (file)
    {
        if (file->fops->truncate)
        {
            if (dfs_is_mounted(file->vnode->mnt) == 0)
            {
#ifdef RT_USING_PAGECACHE
                if (file->vnode->aspace)
                {
                    dfs_aspace_clean(file->vnode->aspace);
                }
#endif
                ret = file->fops->truncate(file, length);
            }
            else
            {
                ret = -EINVAL;
            }
        }
        else
        {
            ret = -ENOSYS;
        }
    }
    else
    {
        ret = -EBADF;
    }

    return ret;
}

/**
 * @brief Flush file buffers to storage device
 *
 * This function forces any buffered data to be written to the underlying storage device.
 *
 * @param[in,out] file Pointer to the file structure to flush (both input and output)
 *
 * @return int Operation result:
 *         - 0 on success
 *         -EBADF if invalid file descriptor
 *         -ENOSYS if flush operation not supported
 *         -EINVAL if invalid parameters or not mounted
 *
 * @note This function provides stronger guarantees than regular writes
 *       about data persistence on storage media
 * @note If RT_USING_PAGECACHE is enabled, the page cache will be flushed first
 */
int dfs_file_flush(struct dfs_file *file)
{
    int ret = 0;

    if (file)
    {
        if (file->fops->flush)
        {
            if (dfs_is_mounted(file->vnode->mnt) == 0)
            {
#ifdef RT_USING_PAGECACHE
                if (file->vnode->aspace)
                {
                    dfs_aspace_flush(file->vnode->aspace);
                }
#endif
                ret = file->fops->flush(file);
            }
            else
            {
                ret = -EINVAL;
            }
        }
        else
        {
            ret = -ENOSYS;
        }
    }
    else
    {
        ret = -EBADF;
    }

    return ret;
}

/**
 * @brief Read directory entries
 *
 * This function reads directory entries from the directory file descriptor into
 * the buffer provided. Each entry is stored as a struct dirent.
 *
 * @param[in] file Pointer to the directory file structure
 * @param[out] dirp Buffer to store directory entries
 * @param[in] nbytes Size of the buffer in bytes
 *
 * @return int Number of bytes read on success, or negative error code:
 *         -EBADF if invalid file descriptor
 *         -ENOTDIR if not a directory
 *         -EINVAL if not mounted or invalid parameters
 *         -RT_ERROR for general errors
 */
int dfs_file_getdents(struct dfs_file *file, struct dirent *dirp, size_t nbytes)
{
    int ret = -RT_ERROR;

    if (file)
    {
        if (file->vnode && S_ISDIR(file->vnode->mode))
        {
            if (file->fops && file->fops->getdents)
            {
                DLOG(msg, "dfs_file", file->dentry->mnt->fs_ops->name, DLOG_MSG, "fops->getdents()");

                if (dfs_is_mounted(file->vnode->mnt) == 0)
                {
                    ret = file->fops->getdents(file, dirp, nbytes);
                }
                else
                {
                    ret = -EINVAL;
                }
            }
        }
    }
    else
    {
        ret = -EBADF;
    }

    return ret;
}

/**
 * @brief Check if a path refers to a directory
 *
 * This function checks whether the specified path exists and is a directory.
 *
 * @param[in] path The filesystem path to check
 *
 * @return int Operation result:
 *         - 0 if path exists and is a directory
 *         -RT_ERROR if path doesn't exist or isn't a directory
 */
int dfs_file_isdir(const char *path)
{
    int ret = -RT_ERROR;
    char *fullpath = RT_NULL;
    struct dfs_mnt *mnt = RT_NULL;
    struct dfs_dentry *dentry = RT_NULL;

    fullpath = dfs_normalize_path(NULL, path);
    if (fullpath)
    {
        DLOG(msg, "dfs_file", "mnt", DLOG_MSG, "dfs_mnt_lookup(%s)", fullpath);
        mnt = dfs_mnt_lookup(fullpath);
        if (mnt)
        {
            char *tmp = dfs_file_realpath(&mnt, fullpath, DFS_REALPATH_EXCEPT_NONE);
            if (tmp)
            {
                rt_free(fullpath);
                fullpath = tmp;
            }

            DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dentry = dfs_dentry_lookup(mnt, %s)", fullpath);
            dentry = dfs_dentry_lookup(mnt, fullpath, 0);
            if (dentry)
            {
                DLOG(msg, "dentry", "dfs_file", DLOG_MSG_RET, "return dentry");
                if (mnt->fs_ops->stat)
                {
                    struct stat stat = {0};
                    DLOG(msg, "dfs_file", mnt->fs_ops->name, DLOG_MSG, "fs_ops->stat(dentry, buf)");

                    if (dfs_is_mounted(mnt) == 0)
                    {
                        ret = mnt->fs_ops->stat(dentry, &stat);
                    }

                    if (ret == RT_EOK && S_ISDIR(stat.st_mode))
                    {
                        ret = RT_EOK;
                    }
                    else
                    {
                        ret = -RT_ERROR;
                    }
                }

                /* unref dentry */
                DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_unref(dentry)");
                dfs_dentry_unref(dentry);
                dentry = RT_NULL;
            }
        }

        rt_free(fullpath);
        fullpath = RT_NULL;
    }

    return ret;
}

/**
 * @brief Check file accessibility with specified mode
 *
 * This function checks whether the file specified by path can be accessed
 * with the given mode.
 *
 * @param[in] path The file path to check accessibility
 * @param[in] mode The access mode to check (read/write/execute permissions)
 *
 * @return int Access status:
 *         - 0 if file is accessible with specified mode
 *         - -1 if file is not accessible
 */
int dfs_file_access(const char *path, mode_t mode)
{
    int ret;
    struct dfs_file file;

    dfs_file_init(&file);

    if (dfs_file_open(&file, path, O_RDONLY, mode) >= 0)
    {
        ret = 0;
        dfs_file_close(&file);
    }
    else
    {
        ret = -1;
    }

    dfs_file_deinit(&file);

    return ret;
}

#ifdef RT_USING_SMART
/**
 * @brief Memory map a file or device into process address space
 *
 * This function maps a file or device into the calling process's address space.
 * It handles both regular files and device files differently:
 * - For regular files: uses standard mmap operation
 * - For device files: uses device-specific ioctl with RT_FIOMMAP2 command
 *
 * @param[in] file Pointer to the file structure to be mapped
 * @param[in,out] mmap2 Pointer to mmap arguments structure (both input and output)
 *
 * @return int Operation result:
 *         - RT_EOK on success
 *         - EINVAL if invalid parameters or operation not supported
 *         - Other error codes from underlying mmap/ioctl operations
 *
 * @note For device files, the actual mapping behavior depends on the device driver
 */
int dfs_file_mmap2(struct dfs_file *file, struct dfs_mmap2_args *mmap2)
{
    int ret = RT_EOK;

    if (file && mmap2)
    {
        if (file->vnode->type == FT_REGULAR)
        {
            ret = dfs_file_mmap(file, mmap2);
            if (ret != 0)
            {
                ret = ret > 0 ? ret : -ret;
                rt_set_errno(ret);
            }
        }
        else if (file->vnode->type != FT_DEVICE || !file->vnode->fops->ioctl)
        {
            rt_set_errno(EINVAL);
        }
        else if (file->vnode->type == FT_DEVICE && file->vnode->fops->ioctl)
        {
            if (dfs_is_mounted(file->vnode->mnt) == 0)
            {
                ret = file->vnode->fops->ioctl(file, RT_FIOMMAP2, mmap2);
            }
            else
            {
                ret = EINVAL;
            }

            if (ret != 0)
            {
                ret = ret > 0 ? ret : -ret;
                rt_set_errno(ret);
            }
        }
    }

    return ret;
}
#endif

#ifdef RT_USING_FINSH

#define _COLOR_RED      "\033[31m"
#define _COLOR_GREEN    "\033[32m"
#define _COLOR_YELLOW   "\033[33m"
#define _COLOR_BLUE     "\033[34m"
#define _COLOR_CYAN     "\033[36m"
#define _COLOR_WHITE    "\033[37m"
#define _COLOR_NORMAL   "\033[0m"

/**
 * @brief List directory contents with colored output
 *
 * This function lists all entries in the specified directory with colored output
 * that distinguishes different file types. It handles:
 * - Directories (blue)
 * - Symbolic links (cyan with target path)
 * - Executable files (green)
 * - Character devices (yellow)
 * - Regular files (default color)
 *
 * @param[in] pathname The directory path to list (NULL for current directory)
 */
void ls(const char *pathname)
{
    struct dirent dirent;
    struct stat stat;
    int length;
    char *fullpath, *path;
    struct dfs_file file;

    if (pathname == NULL)
    {
#ifdef DFS_USING_WORKDIR
        /* open current working directory */
        path = rt_strdup(working_directory);
#else
        path = rt_strdup("/");
#endif
        if (path == NULL)
        {
            return; /* out of memory */
        }
    }
    else
    {
        path = dfs_normalize_path(NULL, (char *)pathname);
        if (path == NULL)
        {
            return; /* out of memory */
        }
    }

    dfs_file_init(&file);

    /* list directory */
    DLOG(msg, "dfs", "dfs_file", DLOG_MSG, "dfs_file_open(%s, O_DIRECTORY, 0)", path);
    if (dfs_file_open(&file, path, O_DIRECTORY, 0) >= 0)
    {
        char *link_fn = (char *)rt_malloc(DFS_PATH_MAX);
        if (link_fn)
        {
            rt_kprintf("Directory %s:\n", path);
            do
            {
                memset(&dirent, 0, sizeof(struct dirent));

                DLOG(group, "foreach_item");
                DLOG(msg, "dfs", "dfs_file", DLOG_MSG, "dfs_file_getdents(&dirent)");
                length = dfs_file_getdents(&file, &dirent, sizeof(struct dirent));
                if (length > 0)
                {
                    DLOG(msg, "dfs_file", "dfs", DLOG_MSG_RET, "dirent.d_name=%s", dirent.d_name);
                    memset(&stat, 0, sizeof(struct stat));

                    /* build full path for each file */
                    fullpath = dfs_normalize_path(path, dirent.d_name);
                    if (fullpath == NULL)
                        break;

                    DLOG(msg, "dfs", "dfs_file", DLOG_MSG, "dfs_file_lstat(%s, &stat)", fullpath);
                    if (dfs_file_lstat(fullpath, &stat) == 0)
                    {
                        if (S_ISDIR(stat.st_mode))
                        {
                            rt_kprintf(_COLOR_BLUE "%-20s" _COLOR_NORMAL, dirent.d_name);
                            rt_kprintf(" %-25s\n", "<DIR>");
                        }
                        else if (S_ISLNK(stat.st_mode))
                        {
                            int ret = 0;

                            rt_kprintf(_COLOR_CYAN "%-20s" _COLOR_NORMAL, dirent.d_name);

                            ret = dfs_file_readlink(fullpath, link_fn, DFS_PATH_MAX);
                            if (ret > 0)
                            {
                                char *link_path = link_fn;
                                struct dfs_mnt *mnt = RT_NULL;

                                mnt = dfs_mnt_lookup(fullpath);
                                if (mnt)
                                {
                                    char *tmp = dfs_file_realpath(&mnt, fullpath, DFS_REALPATH_EXCEPT_LAST);
                                    if (tmp)
                                    {
                                        char *index;

                                        index = strrchr(fullpath, '/');
                                        if (index)
                                        {
                                            int length = index - fullpath;
                                            char *parent = (char*) rt_malloc (length + 1);
                                            if (parent)
                                            {
                                                rt_memcpy(parent, fullpath, length);
                                                parent[length] = '\0';

                                                ret = rt_strncmp(parent, link_fn, length);
                                                if (ret == 0)
                                                {
                                                    link_path = link_fn + length;
                                                    if (*link_path == '/')
                                                    {
                                                        link_path ++;
                                                    }
                                                }
                                                rt_free(parent);
                                            }
                                        }
                                        rt_free(tmp);
                                    }
                                }

                                rt_kprintf("-> %s\n", link_path);
                            }
                            else
                            {
                                rt_kprintf(_COLOR_RED "-> link_error\n" _COLOR_NORMAL);
                            }
                        }
                        else if (stat.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                        {
                            rt_kprintf(_COLOR_GREEN "%-20s" _COLOR_NORMAL, dirent.d_name);
                            rt_kprintf(" %-25lu\n", (unsigned long)stat.st_size);
                        }
                        else if (S_ISCHR(stat.st_mode))
                        {
                            rt_kprintf(_COLOR_YELLOW "%-20s" _COLOR_NORMAL, dirent.d_name);
                            rt_kprintf(" %-25s\n", "<CHR>");
                        }
                        else
                        {
                            rt_kprintf("%-20s", dirent.d_name);
                            rt_kprintf(" %-25lu\n", (unsigned long)stat.st_size);
                        }
                    }
                    else
                    {
                        rt_kprintf(_COLOR_RED "%-20s\n" _COLOR_NORMAL, dirent.d_name);
                    }

                    rt_free(fullpath);
                }
                else
                {
                    DLOG(msg, "dfs_file", "dfs", DLOG_MSG_RET, "return NULL");
                }

                DLOG(group_end);
            } while (length > 0);

            rt_free(link_fn);
        }

        DLOG(msg, "dfs", "dfs_file", DLOG_MSG, "dfs_file_close()");
        dfs_file_close(&file);
    }
    else
    {
        rt_kprintf("No such directory\n");
    }

    dfs_file_deinit(&file);

    DLOG(msg, "dfs_file", "dfs", DLOG_MSG_RET, "return");
    rt_free(path);
}

/**
 * @brief Display file contents to standard output
 *
 * This function reads and prints the contents of the specified file to the console.
 * It handles both text and binary files by reading in chunks and printing the output.
 *
 * @param[in] filename Path to the file to be displayed
 */
void cat(const char *filename)
{
    int length = 0;
    char buffer[81];
    struct dfs_file file;

    if (filename && dfs_file_isdir(filename) == 0)
    {
        rt_kprintf("cat: %s Is a directory\n", filename);
        return;
    }

    dfs_file_init(&file);

    DLOG(msg, "dfs", "dfs_file", DLOG_MSG, "dfs_file_open(%s, O_RDONLY, 0)", filename);
    if (dfs_file_open(&file, filename, O_RDONLY, 0) < 0)
    {
        rt_kprintf("Open %s failed\n", filename);
        dfs_file_deinit(&file);
        return;
    }

    do
    {
        rt_memset(buffer, 0x0, sizeof(buffer));
        DLOG(msg, "dfs", "dfs_file", DLOG_MSG, "dfs_file_read(fd, buffer, %d)", sizeof(buffer) - 1);
        length = dfs_file_read(&file, (void *)buffer, sizeof(buffer) - 1);
        if (length > 0)
        {
            buffer[length] = '\0';
            rt_kprintf("%s", buffer);
        }
    } while (length > 0);
    rt_kprintf("\n");

    DLOG(msg, "dfs", "dfs_file", DLOG_MSG, "dfs_file_close()");
    dfs_file_close(&file);
    dfs_file_deinit(&file);
}

#define BUF_SZ  4096
/**
 * @brief Copy file contents from source to destination
 *
 * This function copies the contents of a source file to a destination file.
 * It handles memory allocation, file operations, and error checking.
 *
 * @param[in] src Path to the source file to be copied
 * @param[in] dst Path to the destination file to be created/overwritten
 */
static void copyfile(const char *src, const char *dst)
{
    int ret;
    struct dfs_file src_file, dst_file;
    rt_uint8_t *block_ptr;
    rt_int32_t read_bytes;

    block_ptr = (rt_uint8_t *)rt_malloc(BUF_SZ);
    if (block_ptr == NULL)
    {
        rt_kprintf("out of memory\n");
        return;
    }

    dfs_file_init(&src_file);

    ret = dfs_file_open(&src_file, src, O_RDONLY, 0);
    if (ret < 0)
    {
        dfs_file_deinit(&src_file);
        rt_free(block_ptr);
        rt_kprintf("Read %s failed\n", src);
        return;
    }

    dfs_file_init(&dst_file);

    ret = dfs_file_open(&dst_file, dst, O_WRONLY | O_CREAT | O_TRUNC, 0);
    if (ret < 0)
    {
        dfs_file_deinit(&dst_file);
        dfs_file_close(&src_file);
        dfs_file_deinit(&src_file);
        rt_free(block_ptr);
        rt_kprintf("Write %s failed\n", dst);
        return;
    }

    do
    {
        read_bytes = dfs_file_read(&src_file, block_ptr, BUF_SZ);
        if (read_bytes > 0)
        {
            int length;

            length = dfs_file_write(&dst_file, block_ptr, read_bytes);
            if (length != read_bytes)
            {
                /* write failed. */
                rt_kprintf("Write file data failed, errno=%d\n", length);
                break;
            }
        }
    } while (read_bytes > 0);

    dfs_file_close(&dst_file);
    dfs_file_deinit(&dst_file);
    dfs_file_close(&src_file);
    dfs_file_deinit(&src_file);
    rt_free(block_ptr);
}

extern int mkdir(const char *path, mode_t mode);

/**
 * @brief Recursively copy directory contents from source to destination
 *
 * This function recursively copies all files and subdirectories from the source
 * directory to the destination directory. It handles both files and directories
 * appropriately.
 *
 * @param[in] src Path to the source directory to be copied
 * @param[in] dst Path to the destination directory to be created
 */
static void copydir(const char *src, const char *dst)
{
    struct dirent dirent;
    struct stat stat;
    int length;
    struct dfs_file file;

    dfs_file_init(&file);

    if (dfs_file_open(&file, src, O_DIRECTORY, 0) < 0)
    {
        rt_kprintf("open %s failed\n", src);
        dfs_file_deinit(&file);
        return ;
    }

    do
    {
        rt_memset(&dirent, 0, sizeof(struct dirent));

        length = dfs_file_getdents(&file, &dirent, sizeof(struct dirent));
        if (length > 0)
        {
            char *src_entry_full = NULL;
            char *dst_entry_full = NULL;

            if (strcmp(dirent.d_name, "..") == 0 || strcmp(dirent.d_name, ".") == 0)
                continue;

            /* build full path for each file */
            if ((src_entry_full = dfs_normalize_path(src, dirent.d_name)) == NULL)
            {
                rt_kprintf("out of memory!\n");
                break;
            }
            if ((dst_entry_full = dfs_normalize_path(dst, dirent.d_name)) == NULL)
            {
                rt_kprintf("out of memory!\n");
                rt_free(src_entry_full);
                break;
            }

            rt_memset(&stat, 0, sizeof(struct stat));
            if (dfs_file_lstat(src_entry_full, &stat) != 0)
            {
                rt_kprintf("open file: %s failed\n", dirent.d_name);
                continue;
            }

            if (S_ISDIR(stat.st_mode))
            {
                mkdir(dst_entry_full, 0);
                copydir(src_entry_full, dst_entry_full);
            }
            else
            {
                copyfile(src_entry_full, dst_entry_full);
            }
            rt_free(src_entry_full);
            rt_free(dst_entry_full);
        }
    }
    while (length > 0);

    dfs_file_close(&file);
    dfs_file_deinit(&file);
}

/**
 * @brief Extract the last component from a path string
 *
 * This function extracts the filename or last directory name from a given path.
 * It searches for the last '/' character and returns the substring after it.
 *
 * @param[in] path The input path string to process
 *
 * @return const char* Pointer to:
 *         - The last path component if '/' is found
 *         - The original path if no '/' is found
 *         - NULL if input path is NULL
 */
static const char *_get_path_lastname(const char *path)
{
    char *ptr;
    if ((ptr = (char *)strrchr(path, '/')) == NULL)
        return path;

    /* skip the '/' then return */
    return ++ptr;
}

/**
 * @brief Copy files or directories from source to destination
 *
 * This function handles copying operations between files and directories with
 * various combinations of source and destination types. It supports:
 * - File to file copy
 * - File to directory copy (copies into directory with original filename)
 * - Directory to directory copy (recursive)
 * - Directory to new directory creation and copy
 *
 * @param[in] src Path to the source file/directory to copy
 * @param[in] dst Path to the destination file/directory
 */
void copy(const char *src, const char *dst)
{
#define FLAG_SRC_TYPE      0x03
#define FLAG_SRC_IS_DIR    0x01
#define FLAG_SRC_IS_FILE   0x02
#define FLAG_SRC_NON_EXSIT 0x00

#define FLAG_DST_TYPE      0x0C
#define FLAG_DST_IS_DIR    0x04
#define FLAG_DST_IS_FILE   0x08
#define FLAG_DST_NON_EXSIT 0x00

    struct stat stat;
    uint32_t flag = 0;

    /* check the staus of src and dst */
    if (dfs_file_lstat(src, &stat) < 0)
    {
        rt_kprintf("copy failed, bad %s\n", src);
        return;
    }
    if (S_ISDIR(stat.st_mode))
        flag |= FLAG_SRC_IS_DIR;
    else
        flag |= FLAG_SRC_IS_FILE;

    if (dfs_file_stat(dst, &stat) < 0)
    {
        flag |= FLAG_DST_NON_EXSIT;
    }
    else
    {
        if (S_ISDIR(stat.st_mode))
            flag |= FLAG_DST_IS_DIR;
        else
            flag |= FLAG_DST_IS_FILE;
    }

    /* 2. check status */
    if ((flag & FLAG_SRC_IS_DIR) && (flag & FLAG_DST_IS_FILE))
    {
        rt_kprintf("cp faild, cp dir to file is not permitted!\n");
        return ;
    }

    /* 3. do copy */
    if (flag & FLAG_SRC_IS_FILE)
    {
        if (flag & FLAG_DST_IS_DIR)
        {
            char *fdst;
            fdst = dfs_normalize_path(dst, _get_path_lastname(src));
            if (fdst == NULL)
            {
                rt_kprintf("out of memory\n");
                return;
            }
            copyfile(src, fdst);
            rt_free(fdst);
        }
        else
        {
            copyfile(src, dst);
        }
    }
    else /* flag & FLAG_SRC_IS_DIR */
    {
        if (flag & FLAG_DST_IS_DIR)
        {
            char *fdst;
            fdst = dfs_normalize_path(dst, _get_path_lastname(src));
            if (fdst == NULL)
            {
                rt_kprintf("out of memory\n");
                return;
            }
            mkdir(fdst, 0);
            copydir(src, fdst);
            rt_free(fdst);
        }
        else if ((flag & FLAG_DST_TYPE) == FLAG_DST_NON_EXSIT)
        {
            mkdir(dst, 0);
            copydir(src, dst);
        }
        else
        {
            copydir(src, dst);
        }
    }
}
FINSH_FUNCTION_EXPORT(copy, copy file or dir)

#endif