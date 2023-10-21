/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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

/*
 * rw_verify_area doesn't like huge counts. We limit
 * them to something that fits in "int" so that others
 * won't have to do range checks all the time.
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

void dfs_file_deinit(struct dfs_file *file)
{
    if (file)
    {
        rt_mutex_detach(&file->pos_lock);
    }
}

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

struct dfs_dentry* dfs_file_follow_link(struct dfs_dentry *dentry)
{
    int ret = 0;
    struct dfs_dentry *tmp = dfs_dentry_ref(dentry);

    if (dentry && dentry->vnode && dentry->vnode->type == FT_SYMLINK)
    {
        char *buf = NULL;

        buf = (char *) rt_malloc (DFS_PATH_MAX);
        if (buf)
        {
            do
            {
                if (dfs_is_mounted(tmp->mnt) == 0)
                {
                    ret = tmp->mnt->fs_ops->readlink(tmp, buf, DFS_PATH_MAX);
                }

                if (ret > 0)
                {
                    struct dfs_mnt *mnt = NULL;

                    if (buf[0] != '/')
                    {
                        char *dir = dfs_dentry_pathname(tmp);

                        /* is the relative directory */
                        if (dir)
                        {
                            char *fullpath = dfs_normalize_path(dir, buf);
                            if (fullpath)
                            {
                                strncpy(buf, fullpath, DFS_PATH_MAX);

                                rt_free(fullpath);
                            }
                            rt_free(dir);
                        }
                    }

                    mnt = dfs_mnt_lookup(buf);
                    if (mnt)
                    {
                        struct dfs_dentry *de = dfs_dentry_lookup(mnt, buf, 0);

                        /* release the old dentry */
                        dfs_dentry_unref(tmp);
                        tmp = de;
                    }
                }
                else
                {
                    break;
                }
            } while (tmp && tmp->vnode->type == FT_SYMLINK);
        }

        rt_free(buf);
    }

    return tmp;
}

/*
 * this function is creat a nolink path.
 *
 * @param mnt
 * @param fullpath
 * @param mode 0 middle path nolink; 1 all path nolink.
 *
 * @return new path.
 */
static char *dfs_nolink_path(struct dfs_mnt **mnt, char *fullpath, int mode)
{
    int index = 0;
    char *path = RT_NULL;
    char link_fn[DFS_PATH_MAX] = {0};
    struct dfs_dentry *dentry = RT_NULL;

    path = (char *)rt_malloc((DFS_PATH_MAX * 2) + 1); // path + syslink + \0
    if (!path)
    {
        return path;
    }

    if (*mnt && fullpath)
    {
        int i = 0;
        char *fp = fullpath;

        while (*fp != '\0')
        {
            fp++;
            i++;
            if (*fp == '/')
            {
                rt_memcpy(path + index, fp - i, i);
                path[index + i] = '\0';

                dentry = dfs_dentry_lookup(*mnt, path, 0);
                if (dentry && dentry->vnode->type == FT_SYMLINK)
                {
                    int ret = -1;

                    if ((*mnt)->fs_ops->readlink)
                    {
                        if (dfs_is_mounted((*mnt)) == 0)
                        {
                            ret = (*mnt)->fs_ops->readlink(dentry, link_fn, DFS_PATH_MAX);
                        }
                    }

                    if (ret > 0)
                    {
                        int len = rt_strlen(link_fn);
                        if (link_fn[0] == '/')
                        {
                            rt_memcpy(path, link_fn, len);
                            index = len;
                        }
                        else
                        {
                            path[index] = '/';
                            index++;
                            rt_memcpy(path + index, link_fn, len);
                            index += len;
                        }
                        path[index] = '\0';
                        *mnt = dfs_mnt_lookup(path);
                    }
                    else
                    {
                        rt_kprintf("link error: %s\n", path);
                    }
                }
                else
                {
                    index += i;
                }
                dfs_dentry_unref(dentry);
                i = 0;
            }
        }

        if (i)
        {
            rt_memcpy(path + index, fp - i, i);
            path[index + i] = '\0';

            if (mode)
            {
                dentry = dfs_dentry_lookup(*mnt, path, 0);
                if (dentry && dentry->vnode->type == FT_SYMLINK)
                {
                    int ret = -1;

                    if ((*mnt)->fs_ops->readlink)
                    {
                        if (dfs_is_mounted((*mnt)) == 0)
                        {
                            ret = (*mnt)->fs_ops->readlink(dentry, link_fn, DFS_PATH_MAX);
                        }
                    }

                    if (ret > 0)
                    {
                        int len = rt_strlen(link_fn);
                        if (link_fn[0] == '/')
                        {
                            rt_memcpy(path, link_fn, len);
                            index = len;
                        }
                        else
                        {
                            path[index] = '/';
                            index++;
                            rt_memcpy(path + index, link_fn, len);
                            index += len;
                        }
                        path[index] = '\0';
                        *mnt = dfs_mnt_lookup(path);
                    }
                    else
                    {
                        rt_kprintf("link error: %s\n", path);
                    }

                    char *_fullpath = dfs_normalize_path(RT_NULL, path);
                    if (_fullpath)
                    {
                        strncpy(path, _fullpath, DFS_PATH_MAX);
                        rt_free(_fullpath);
                    }
                }
                dfs_dentry_unref(dentry);
            }
        }
    }
    else
    {
        rt_free(path);
        path = RT_NULL;
    }

    //rt_kprintf("%s: %s => %s\n", __FUNCTION__, fullpath, path);

    return path;
}

/**
 * this function will open a file which specified by path with specified oflags.
 *
 * @param fd the file descriptor pointer to return the corresponding result.
 * @param path the specified file path.
 * @param oflags the oflags for open operator.
 *
 * @return 0 on successful, -1 on failed.
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
                char *tmp = dfs_nolink_path(&mnt, fullpath, 0);
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

                        /* follow symbol link */
                        target_dentry = dfs_file_follow_link(dentry);
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
                                mode &= ~S_IFMT;
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
                            LOG_E("open %s failed in file system: %s", path, dentry->mnt->fs_ops->name);
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

ssize_t dfs_file_write(struct dfs_file *file, const void *buf, size_t len)
{
    size_t ret = -EBADF;

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
            /* fpos lock */
            off_t pos = dfs_file_get_fpos(file);

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
            /* fpos unlock */
            dfs_file_set_fpos(file, pos);
        }
    }

    return ret;
}

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
            char *tmp = dfs_nolink_path(&mnt, fullpath, 1);
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
            char *tmp = dfs_nolink_path(&mnt, fullpath, 0);
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

int dfs_file_fstat(struct dfs_file *file, struct stat *buf)
{
    size_t ret = -EBADF;

    if (file)
    {
        if (file->fops && file->fops->ioctl)
        {
            // ret = file->fops->fstat(file, buf);
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
            char *tmp = dfs_nolink_path(&mnt, fullpath, 0);
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
            char *tmp = dfs_nolink_path(&mnt, fullpath, 0);
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

int dfs_file_link(const char *oldname, const char *newname)
{
    int ret = -1;
    struct stat stat;
    struct dfs_mnt *mnt = RT_NULL;
    char *old_fullpath, *new_fullpath;

    if (dfs_file_isdir(oldname) == 0)
    {
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

        char *tmp = dfs_nolink_path(&mnt, old_fullpath, 0);
        if (tmp)
        {
            rt_free(old_fullpath);
            old_fullpath = tmp;
        }
    }

    new_fullpath = dfs_normalize_path(NULL, newname);
    if (new_fullpath)
    {
        char *tmp = dfs_nolink_path(&mnt, new_fullpath, 0);
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

/* symlink creates a symbolic link named `linkpath` which contains the string `target`. */
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
                    char *tmp = dfs_nolink_path(&mnt, parent, 0);
                    if (tmp)
                    {
                        rt_free(parent);
                        parent = tmp;
                    }

                    DLOG(msg, "dfs_file", "dentry", DLOG_MSG, "dfs_dentry_lookup(mnt, %s)", fullpath);
                    dentry = dfs_dentry_lookup(mnt, parent, 0);
                    if (dentry)
                    {
                        if (dentry->mnt->fs_ops->symlink)
                        {
                            char *path = dfs_normalize_path(parent, target);
                            if (path)
                            {
                                char *tmp = dfs_nolink_path(&mnt, path, 0);
                                if (tmp)
                                {
                                    rt_free(path);
                                    path = tmp;
                                }
                                else
                                {
                                    tmp = path;
                                }

                                ret = rt_strncmp(parent, path, strlen(parent));
                                if (ret == 0)
                                {
                                    tmp = path + strlen(parent);
                                    if (*tmp == '/')
                                    {
                                        tmp ++;
                                    }
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

        if (fullpath != linkpath)
            rt_free(fullpath);
    }
    else
    {
        ret = -EINVAL;
    }

    return ret;
}

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
            char *tmp = dfs_nolink_path(&mnt, fullpath, 0);
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

        char *tmp = dfs_nolink_path(&mnt, old_fullpath, 0);
        if (tmp)
        {
            rt_free(old_fullpath);
            old_fullpath = tmp;
        }
    }

    new_fullpath = dfs_normalize_path(NULL, new_file);
    if (new_fullpath)
    {
        char *tmp = dfs_nolink_path(&mnt, new_fullpath, 0);
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
 * this function will check the path is it a directory.
 *
 * @param path the file path.
 *
 * @return 0 on is dir, -1 on not dir.
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
            char *tmp = dfs_nolink_path(&mnt, fullpath, 1);
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
#define _COLOR_BLUE     "\033[34m"
#define _COLOR_CYAN     "\033[36m"
#define _COLOR_WHITE    "\033[37m"
#define _COLOR_NORMAL   "\033[0m"

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
        char *link_fn = (char *) rt_malloc (DFS_PATH_MAX);
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
                            rt_kprintf("%-25s\n", "<DIR>");
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
                                    char *tmp = dfs_nolink_path(&mnt, fullpath, 0);
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
                            rt_kprintf("%-25lu\n", (unsigned long)stat.st_size);
                        }
                        else
                        {
                            rt_kprintf("%-20s", dirent.d_name);
                            rt_kprintf("%-25lu\n", (unsigned long)stat.st_size);
                        }
                    }
                    else
                    {
                        rt_kprintf(_COLOR_RED "%-20s" _COLOR_NORMAL, dirent.d_name);
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

static const char *_get_path_lastname(const char *path)
{
    char *ptr;
    if ((ptr = (char *)strrchr(path, '/')) == NULL)
        return path;

    /* skip the '/' then return */
    return ++ptr;
}

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

    //2. check status
    if ((flag & FLAG_SRC_IS_DIR) && (flag & FLAG_DST_IS_FILE))
    {
        rt_kprintf("cp faild, cp dir to file is not permitted!\n");
        return ;
    }

    //3. do copy
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
    else //flag & FLAG_SRC_IS_DIR
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
