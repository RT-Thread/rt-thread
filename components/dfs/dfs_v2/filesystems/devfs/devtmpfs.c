/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     flybreak     the first version
 * 2023-02-01     xqyjlj       fix cannot open the same file repeatedly in 'w' mode
 * 2023-09-20     zmq810150896 adds truncate functionality and standardized unlink adaptations
 * 2023-12-02     Shell        Support of dynamic device
 */

#include <rthw.h>
#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_dentry.h>
#include <dfs_file.h>
#include <dfs_mnt.h>
#include <devfs.h>
#include <unistd.h>


#define TMPFS_MAGIC         0x0B0B0B0B
#define TMPFS_TYPE_FILE     0x00
#define TMPFS_TYPE_DIR      0x01
#define TMPFS_TYPE_DYN_DEV  0x02    /* dynamic device */

struct devtmpfs_sb;

struct devtmpfs_file
{
    char name[DIRENT_NAME_MAX]; /* file name */

    rt_uint32_t     type;       /* file type */
    rt_list_t       subdirs;    /* file subdir list */
    rt_list_t       sibling;    /* file sibling list */

    struct devtmpfs_sb *sb;    /* superblock ptr */

    rt_uint32_t     mode;
    char *link;
};

struct devtmpfs_sb
{
    rt_uint32_t             magic;      /* TMPFS_MAGIC */
    struct devtmpfs_file    root;       /* root dir */
    rt_size_t               df_size;    /* df size */
    rt_list_t               sibling;    /* sb sibling list */
    struct rt_spinlock      lock;       /* tmpfs lock */
};

static struct dfs_file_ops _default_fops = { 0 };

static int _path_separate(const char *path, char *parent_path, char *file_name)
{
    const char *path_p, *path_q;

    RT_ASSERT(path[0] == '/');

    file_name[0] = '\0';
    path_p = path_q = &path[1];
__next_dir:
    while (*path_q != '/' && *path_q != '\0')
    {
        path_q++;
    }
    if (path_q != path_p) /*sub dir*/
    {
        if (*path_q != '\0')
        {
            path_q++;
            path_p = path_q;
            goto __next_dir;
        }
        else /* Last level dir */
        {
            rt_memcpy(parent_path, path, path_p - path - 1);
            parent_path[path_p - path - 1] = '\0';
            rt_memcpy(file_name, path_p, path_q - path_p);
            file_name[path_q - path_p] = '\0';
        }
    }
    if (parent_path[0] == 0)
    {
        parent_path[0] = '/';
        parent_path[1] = '\0';
    }
    //LOG_D("parent_path: %s", parent_path);
    //LOG_D("file_name: %s", file_name);

    return 0;
}

static int _get_subdir(const char *path, char *name)
{
    const char *subpath = path;
    while (*subpath == '/' && *subpath)
        subpath ++;
    while (*subpath != '/' && *subpath)
    {
        *name = *subpath;
        name ++;
        subpath ++;
    }
    return 0;
}

#if 0
static int _free_subdir(struct devtmpfs_file *dfile)
{
    struct devtmpfs_file *file;
    rt_list_t *list, *temp_list;
    struct devtmpfs_sb *superblock;

    RT_ASSERT(dfile->type == TMPFS_TYPE_DIR);

    rt_list_for_each_safe(list, temp_list, &dfile->subdirs)
    {
        file = rt_list_entry(list, struct devtmpfs_file, sibling);
        if (file->type == TMPFS_TYPE_DIR)
        {
            _free_subdir(file);
        }

        if (file->link)
        {
            rt_free(file->link);
        }

        superblock = file->sb;
        RT_ASSERT(superblock);

        rt_spin_lock(&superblock->lock);
        rt_list_remove(&(file->sibling));
        rt_spin_unlock(&superblock->lock);

        rt_free(file);
    }
    return 0;
}
#endif

static int devtmpfs_mount(struct dfs_mnt *mnt, unsigned long rwflag, const void *data)
{
    struct devtmpfs_sb *superblock;

    superblock = rt_calloc(1, sizeof(struct devtmpfs_sb));
    if (superblock)
    {
        superblock->df_size = sizeof(struct devtmpfs_sb);
        superblock->magic = TMPFS_MAGIC;
        rt_list_init(&superblock->sibling);

        superblock->root.name[0] = '/';
        superblock->root.sb = superblock;
        superblock->root.type = TMPFS_TYPE_DIR;
        superblock->root.mode = S_IFDIR | (S_IRUSR | S_IRGRP | S_IROTH) | (S_IXUSR | S_IXGRP | S_IXOTH);
        rt_list_init(&superblock->root.sibling);
        rt_list_init(&superblock->root.subdirs);

        rt_spin_lock_init(&superblock->lock);

        mnt->data = superblock;
    }
    else
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static int devtmpfs_unmount(struct dfs_mnt *mnt)
{
#if 0
    struct devtmpfs_sb *superblock;

    /* FIXME: don't unmount on busy. */
    superblock = (struct devtmpfs_sb *)mnt->data;
    RT_ASSERT(superblock != NULL);

    mnt->data = NULL;
    _free_subdir(&(superblock->root));
    rt_free(superblock);
#endif
    return -RT_ERROR;
}

static struct devtmpfs_file *devtmpfs_file_lookup(struct devtmpfs_sb *superblock, const char *path)
{
    const char *subpath, *curpath, *filename = RT_NULL;
    char subdir_name[DIRENT_NAME_MAX];
    struct devtmpfs_file *file, *curfile;
    rt_list_t *list;

    subpath = path;
    while (*subpath == '/' && *subpath)
        subpath ++;

    if (! *subpath) /* is root directory */
    {
        return &(superblock->root);
    }

    curpath = subpath;
    curfile = &superblock->root;

find_subpath:
    while (*subpath != '/' && *subpath)
        subpath ++;

    if (! *subpath) /* is last directory */
        filename = curpath;
    else
        subpath ++; /* skip '/' */

    memset(subdir_name, 0, DIRENT_NAME_MAX);
    _get_subdir(curpath, subdir_name);

    rt_spin_lock(&superblock->lock);

    rt_list_for_each(list, &curfile->subdirs)
    {
        file = rt_list_entry(list, struct devtmpfs_file, sibling);
        if (filename) /* find file */
        {
            if (rt_strcmp(file->name, filename) == 0)
            {
                rt_spin_unlock(&superblock->lock);
                return file;
            }
        }
        else if (rt_strcmp(file->name, subdir_name) == 0)
        {
            curpath = subpath;
            curfile = file;
            rt_spin_unlock(&superblock->lock);
            goto find_subpath;
        }
    }
    rt_spin_unlock(&superblock->lock);
    /* not found */
    return NULL;
}

static int devtmpfs_statfs(struct dfs_mnt *mnt, struct statfs *buf)
{
    struct devtmpfs_sb *superblock;

    RT_ASSERT(mnt != NULL);
    RT_ASSERT(buf != NULL);

    superblock = (struct devtmpfs_sb *)mnt->data;
    RT_ASSERT(superblock != NULL);

    buf->f_bsize = 512;
    buf->f_blocks = (superblock->df_size + 511) / 512;
    buf->f_bfree = 1;
    buf->f_bavail = buf->f_bfree;

    return RT_EOK;
}

static int devtmpfs_stat(struct dfs_dentry *dentry, struct stat *st)
{
    struct dfs_vnode *vnode;

    if (dentry && dentry->vnode)
    {
        vnode = dentry->vnode;

        st->st_dev = (dev_t)(long)(dentry->mnt->dev_id);
        st->st_ino = (ino_t)dfs_dentry_full_path_crc32(dentry);

        st->st_gid = vnode->gid;
        st->st_uid = vnode->uid;
        st->st_mode = vnode->mode;
        st->st_nlink = vnode->nlink;
        st->st_size = vnode->size;
        st->st_mtim.tv_nsec = vnode->mtime.tv_nsec;
        st->st_mtim.tv_sec = vnode->mtime.tv_sec;
        st->st_ctim.tv_nsec = vnode->ctime.tv_nsec;
        st->st_ctim.tv_sec = vnode->ctime.tv_sec;
        st->st_atim.tv_nsec = vnode->atime.tv_nsec;
        st->st_atim.tv_sec = vnode->atime.tv_sec;
    }

    return RT_EOK;
}

static int devtmpfs_getdents(struct dfs_file *file, struct dirent *dirp, uint32_t count)
{
    struct devtmpfs_file *d_file;
    struct devtmpfs_sb *superblock;

    RT_ASSERT(file);
    RT_ASSERT(file->dentry);
    RT_ASSERT(file->dentry->mnt);

    superblock = (struct devtmpfs_sb *)file->dentry->mnt->data;
    RT_ASSERT(superblock);

    d_file = devtmpfs_file_lookup(superblock, file->dentry->pathname);
    if (d_file)
    {
        rt_size_t index, end;
        struct dirent *d;
        struct devtmpfs_file *n_file;
        rt_list_t *list;

        /* make integer count */
        count = (count / sizeof(struct dirent));
        if (count == 0)
        {
            return -EINVAL;
        }

        end = file->fpos + count;
        index = 0;
        count = 0;

        rt_list_for_each(list, &d_file->subdirs)
        {
            if (index >= (rt_size_t)file->fpos)
            {
                n_file = rt_list_entry(list, struct devtmpfs_file, sibling);

                d = dirp + count;
                if (n_file->type == TMPFS_TYPE_FILE)
                {
                    d->d_type = DT_REG;
                }
                if (n_file->type == TMPFS_TYPE_DIR)
                {
                    d->d_type = DT_DIR;
                }

                d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
                rt_strncpy(d->d_name, n_file->name, DIRENT_NAME_MAX);
                d->d_namlen = rt_strlen(d->d_name);

                count += 1;
                file->fpos += 1;
            }
            index += 1;
            if (index >= end)
            {
                break;
            }
        }
    }

    return count * sizeof(struct dirent);
}

static int devtmpfs_symlink(struct dfs_dentry *parent_dentry, const char *target, const char *linkpath)
{
    int ret = RT_EOK;
    struct devtmpfs_file *p_file, *l_file;
    struct devtmpfs_sb *superblock;

    RT_ASSERT(parent_dentry);
    RT_ASSERT(parent_dentry->mnt);

    superblock = (struct devtmpfs_sb *)parent_dentry->mnt->data;
    RT_ASSERT(superblock);

    p_file = devtmpfs_file_lookup(superblock, parent_dentry->pathname);
    if (p_file)
    {
        l_file = (struct devtmpfs_file *)rt_calloc(1, sizeof(struct devtmpfs_file));
        if (l_file)
        {
            superblock->df_size += sizeof(struct devtmpfs_file);

            strncpy(l_file->name, linkpath, DIRENT_NAME_MAX - 1);

            rt_list_init(&(l_file->subdirs));
            rt_list_init(&(l_file->sibling));
            l_file->sb = superblock;
            l_file->type = TMPFS_TYPE_FILE;
            l_file->mode = p_file->mode;
            l_file->mode &= ~S_IFMT;
            l_file->mode |= S_IFLNK;
            l_file->link = rt_strdup(target);

            rt_spin_lock(&superblock->lock);
            rt_list_insert_after(&(p_file->subdirs), &(l_file->sibling));
            rt_spin_unlock(&superblock->lock);
        }
    }

    return ret;
}

static int devtmpfs_readlink(struct dfs_dentry *dentry, char *buf, int len)
{
    int ret = 0;
    struct devtmpfs_file *d_file;
    struct devtmpfs_sb *superblock;

    RT_ASSERT(dentry);
    RT_ASSERT(dentry->mnt);

    superblock = (struct devtmpfs_sb *)dentry->mnt->data;
    RT_ASSERT(superblock);

    d_file = devtmpfs_file_lookup(superblock, dentry->pathname);
    if (d_file)
    {
        if (d_file->link)
        {
            if (d_file->type == TMPFS_TYPE_DYN_DEV)
            {
                rt_device_t device = (void *)d_file->link;
                buf[0] = '\0';
                ret = device->readlink(device, buf, len);
                if (ret == 0)
                {
                    buf[len - 1] = '\0';
                    ret = rt_strlen(buf);
                }
                else
                {
                    ret = 0;
                }
            }
            else
            {
                rt_strncpy(buf, (const char *)d_file->link, len);
                buf[len - 1] = '\0';
                ret = rt_strlen(buf);
            }
        }
    }

    return ret;
}

static int devtmpfs_unlink(struct dfs_dentry *dentry)
{
    struct devtmpfs_file *d_file;
    struct devtmpfs_sb *superblock;

    RT_ASSERT(dentry);
    RT_ASSERT(dentry->mnt);

    superblock = (struct devtmpfs_sb *)dentry->mnt->data;
    RT_ASSERT(superblock);

    d_file = devtmpfs_file_lookup(superblock, dentry->pathname);
    if (d_file)
    {
        if (d_file->link && d_file->type != TMPFS_TYPE_DYN_DEV)
        {
            rt_free(d_file->link);
        }

        rt_spin_lock(&superblock->lock);
        rt_list_remove(&(d_file->sibling));
        rt_spin_unlock(&superblock->lock);

        rt_free(d_file);
    }

    return RT_EOK;
}

static int devtmpfs_setattr(struct dfs_dentry *dentry, struct dfs_attr *attr)
{
    struct devtmpfs_file *d_file;
    struct devtmpfs_sb *superblock;

    RT_ASSERT(dentry);
    RT_ASSERT(dentry->mnt);

    superblock = (struct devtmpfs_sb *)dentry->mnt->data;
    RT_ASSERT(superblock);

    d_file = devtmpfs_file_lookup(superblock, dentry->pathname);
    if (d_file)
    {
        d_file->mode &= ~0xFFF;
        d_file->mode |= attr->st_mode & 0xFFF;
        return RT_EOK;
    }

    return -RT_ERROR;
}

static struct dfs_vnode *devtmpfs_create_vnode(struct dfs_dentry *dentry, int type, mode_t mode)
{
    struct dfs_vnode *vnode = RT_NULL;
    struct devtmpfs_sb *superblock;
    struct devtmpfs_file *d_file, *p_file;
    char parent_path[DFS_PATH_MAX], file_name[DIRENT_NAME_MAX];

    if (dentry == NULL || dentry->mnt == NULL || dentry->mnt->data == NULL)
    {
        return NULL;
    }

    superblock = (struct devtmpfs_sb *)dentry->mnt->data;
    RT_ASSERT(superblock != NULL);

    vnode = dfs_vnode_create();
    if (vnode)
    {
        /* find parent file */
        _path_separate(dentry->pathname, parent_path, file_name);
        if (file_name[0] == '\0') /* it's root dir */
        {
            dfs_vnode_destroy(vnode);
            return NULL;
        }

        /* open parent directory */
        p_file = devtmpfs_file_lookup(superblock, parent_path);
        if (p_file == NULL)
        {
            dfs_vnode_destroy(vnode);
            return NULL;
        }

        /* create a file entry */
        d_file = (struct devtmpfs_file *)rt_calloc(1, sizeof(struct devtmpfs_file));
        if (d_file == NULL)
        {
            dfs_vnode_destroy(vnode);
            return NULL;
        }

        superblock->df_size += sizeof(struct devtmpfs_file);

        strncpy(d_file->name, file_name, DIRENT_NAME_MAX);

        rt_list_init(&(d_file->subdirs));
        rt_list_init(&(d_file->sibling));
        d_file->sb = superblock;

        vnode->nlink = 1;
        vnode->size = 0;
        vnode->mode = mode;
        vnode->mnt = dentry->mnt;
        vnode->fops = &_default_fops;

        if (type == FT_DIRECTORY)
        {
            d_file->type = TMPFS_TYPE_DIR;
            vnode->type = FT_DIRECTORY;
            vnode->mode &= ~S_IFMT;
            vnode->mode |= S_IFDIR;
        }
        else
        {
            d_file->type = TMPFS_TYPE_FILE;
            vnode->type = FT_DEVICE;
        }

        d_file->mode = vnode->mode;

        rt_spin_lock(&superblock->lock);
        rt_list_insert_after(&(p_file->subdirs), &(d_file->sibling));
        rt_spin_unlock(&superblock->lock);
    }

    return vnode;
}

static struct dfs_vnode *devtmpfs_lookup(struct dfs_dentry *dentry)
{
    struct dfs_vnode *vnode = RT_NULL;
    struct devtmpfs_sb *superblock;
    struct devtmpfs_file *d_file;

    if (dentry == NULL || dentry->mnt == NULL || dentry->mnt->data == NULL)
    {
        return NULL;
    }

    superblock = (struct devtmpfs_sb *)dentry->mnt->data;

    d_file = devtmpfs_file_lookup(superblock, dentry->pathname);
    if (d_file)
    {
        vnode = dfs_vnode_create();
        if (vnode)
        {
            vnode->nlink = 1;
            vnode->size = 0;
            vnode->mnt = dentry->mnt;
            vnode->fops = &_default_fops;
            vnode->mode = d_file->mode;

            if (d_file->type == TMPFS_TYPE_DIR)
            {
                vnode->type = FT_DIRECTORY;
            }
            else if (d_file->link)
            {
                vnode->type = FT_SYMLINK;
            }
            else
            {
                vnode->type = FT_DEVICE;
            }
        }
    }
    else
    {
        rt_device_t device = RT_NULL;

        device = rt_device_find(&dentry->pathname[1]);
        if (device)
        {
            vnode = devtmpfs_create_vnode(dentry, FT_REGULAR, dfs_devfs_device_to_mode(device));
            if (device->flag & RT_DEVICE_FLAG_DYNAMIC)
            {
                d_file = devtmpfs_file_lookup(superblock, dentry->pathname);
                d_file->type = TMPFS_TYPE_DYN_DEV;
                d_file->link = (char *)device;
            }
        }
    }

    return vnode;
}

static int devtmpfs_free_vnode(struct dfs_vnode *vnode)
{
    return RT_EOK;
}

static const struct dfs_filesystem_ops _devtmpfs_ops =
{
    .name = "devtmpfs",
    .flags = DFS_FS_FLAG_DEFAULT,
    .default_fops = &_default_fops,

    .mount = devtmpfs_mount,
    .umount = devtmpfs_unmount,

    .symlink = devtmpfs_symlink,
    .readlink = devtmpfs_readlink,

    .unlink = devtmpfs_unlink,
    .setattr = devtmpfs_setattr,

    .statfs = devtmpfs_statfs,
    .stat = devtmpfs_stat,

    .lookup = devtmpfs_lookup,
    .create_vnode = devtmpfs_create_vnode,
    .free_vnode = devtmpfs_free_vnode
};

static struct dfs_filesystem_type _devtmpfs =
{
    .fs_ops = &_devtmpfs_ops,
};

int dfs_devtmpfs_init(void)
{
    _default_fops = *dfs_devfs_fops();
    _default_fops.getdents = devtmpfs_getdents;

    /* register file system */
    dfs_register(&_devtmpfs);

    dfs_mount(RT_NULL, "/dev", "devtmpfs", 0, RT_NULL);
    dfs_devfs_update();

    return 0;
}
INIT_COMPONENT_EXPORT(dfs_devtmpfs_init);
