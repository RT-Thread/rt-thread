/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-02     Shell        init ver.
 */
#define DBG_TAG "filesystem.ptyfs"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "ptyfs.h"

#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_dentry.h>
#include <dfs_file.h>
#include <dfs_mnt.h>
#include <devfs.h>
#include <rid_bitmap.h>
#include <rthw.h>
#include <rtthread.h>
#include <terminal/terminal.h>

#include <dirent.h>
#include <unistd.h>

#ifndef S_IRWXUGO
#define S_IRWXUGO (S_IRWXU | S_IRWXG | S_IRWXO)
#endif /* S_IRWXUGO */
#ifndef S_IALLUGO
#define S_IALLUGO (S_ISUID | S_ISGID | S_ISVTX | S_IRWXUGO)
#endif /* S_IALLUGO */
#ifndef S_IRUGO
#define S_IRUGO (S_IRUSR | S_IRGRP | S_IROTH)
#endif /* S_IRUGO */
#ifndef S_IWUGO
#define S_IWUGO (S_IWUSR | S_IWGRP | S_IWOTH)
#endif /* S_IWUGO */
#ifndef S_IXUGO
#define S_IXUGO (S_IXUSR | S_IXGRP | S_IXOTH)
#endif /* S_IXUGO */

#define PTYFS_MAGIC           0x9D94A07D
#define PTYFS_TYPE_DIR        0x00
#define PTYFS_TYPE_FILE_PTMX  0x01
#define PTYFS_TYPE_FILE_SLAVE 0x02

/* TODO: using Symbolic permission, but not ours */
#define PTMX_DEFAULT_FILE_MODE (S_IFCHR | 0666)
#define PTS_DEFAULT_FILE_MODE  (S_IFCHR | S_IRUSR | S_IWUSR | S_IRGRP)
#define ROOT_DEFUALT_FILE_MODE (S_IFDIR | S_IRUGO | S_IXUGO | S_IWUSR)

struct ptyfs_sb;

struct ptyfs_file
{
    char basename[DIRENT_NAME_MAX]; /* file name */
    rt_uint32_t mode;               /* file modes allowed */
    rt_uint32_t type;               /* file type */
    rt_list_t subdirs;              /* file subdir list */
    rt_list_t ent_node;             /* entry node in subdir list */
    struct ptyfs_sb *sb;            /* superblock ptr */
    rt_device_t device;             /* device binding on this file */
};

struct ptyfs_sb
{
    struct rt_device ptmx_device; /* ptmx device */
    struct rt_mutex lock;         /* tmpfs lock */
    struct ptyfs_file root_file;  /* root dir */
    struct ptyfs_file ptmx_file;  /* `/ptmx` file */
    struct rid_bitmap ptsno_pool; /* pts number pool */
    rt_uint32_t magic;            /* PTYFS_MAGIC */
    rt_size_t df_size;            /* df size */
    rt_list_t sibling;            /* sb sibling list */
    struct dfs_mnt *mount;        /* mount data */

    /**
     * Note: This upper limit is set to protect kernel memory from draining
     * out by the application if it keeps allocating pty devices.
     *
     * Still, current implementation of bitmap can not efficiently use the
     * memory
     */
    rt_bitmap_t
        ptsno_pool_bitset[LWP_PTY_MAX_PARIS_LIMIT / (sizeof(rt_bitmap_t) * 8)];
};

static struct dfs_file_ops _default_fops;

static int _split_out_subdir(const char *path, char *name)
{
    const char *subpath = path;

    while (*subpath == '/' && *subpath)
    {
        subpath++;
    }

    while (*subpath != '/' && *subpath)
    {
        *name++ = *subpath++;
    }

    *name = '\0';
    return 0;
}

static rt_err_t ptyfile_init(struct ptyfs_file *file, struct ptyfs_sb *sb,
                             const char *name, rt_uint32_t type,
                             rt_uint32_t mode, rt_device_t device)
{
    if (name)
        strncpy(file->basename, name, sizeof(file->basename));

    file->type = type;
    file->mode = mode;
    rt_list_init(&file->subdirs);
    rt_list_init(&file->ent_node);
    file->sb = sb;
    file->device = device;

    return 0;
}

static rt_err_t ptyfile_add_to_root(struct ptyfs_sb *sb,
                                    struct ptyfs_file *new_file)
{
    struct ptyfs_file *root_file = &sb->root_file;

    /* update super block */
    sb->df_size += sizeof(struct ptyfs_file);

    rt_mutex_take(&sb->lock, RT_WAITING_FOREVER);
    rt_list_insert_after(&(root_file->subdirs), &(new_file->ent_node));
    rt_mutex_release(&sb->lock);

    return 0;
}

static rt_err_t ptyfile_remove_from_root(struct ptyfs_sb *sb,
                                         struct ptyfs_file *rm_file)
{
    /* update super block */
    sb->df_size -= sizeof(struct ptyfs_file);

    rt_mutex_take(&sb->lock, RT_WAITING_FOREVER);
    rt_list_remove(&(rm_file->ent_node));
    rt_mutex_release(&sb->lock);

    return 0;
}

static struct ptyfs_file *ptyfile_lookup(struct ptyfs_sb *superblock,
                                         const char *path)
{
    const char *subpath_iter, *curpath_iter, *basename = RT_NULL;
    char subdir_name[DIRENT_NAME_MAX];
    struct ptyfs_file *curfile, *found_file = RT_NULL;
    rt_list_t *list;
    int do_path_resolve = 1;

    subpath_iter = path;

    /* skip starting "/" */
    while (*subpath_iter == '/') subpath_iter++;
    if (!*subpath_iter)
    {
        return &(superblock->root_file);
    }

    curpath_iter = subpath_iter;
    curfile = &superblock->root_file;

    /* resolve chain of files splited from path one by one */
    while (do_path_resolve)
    {
        do_path_resolve = 0;

        /* splitout sub-directory or basename */
        while (*subpath_iter != '/' && *subpath_iter) subpath_iter++;
        if (!*subpath_iter)
        {
            basename = curpath_iter;
        }
        else
        {
            _split_out_subdir(curpath_iter, subdir_name);

            /* skip "/" for next search */
            subpath_iter++;
        }

        rt_mutex_take(&superblock->lock, RT_WAITING_FOREVER);
        rt_list_for_each(list, &curfile->subdirs)
        {
            struct ptyfs_file *file_iter;
            file_iter = rt_list_entry(list, struct ptyfs_file, ent_node);
            if (basename)
            {
                if (strcmp(file_iter->basename, basename) == 0)
                {
                    found_file = file_iter;
                    break;
                }
            }
            else if (strcmp(file_iter->basename, subdir_name) == 0)
            {
                curpath_iter = subpath_iter;
                curfile = file_iter;
                do_path_resolve = 1;
                break;
            }
        }
        rt_mutex_release(&superblock->lock);
    }

    return found_file;
}

const char *ptyfs_get_rootpath(rt_device_t ptmx)
{
    const char *rc;
    struct ptyfs_sb *sb;
    /* allocate id for it and register file */
    sb = rt_container_of(ptmx, struct ptyfs_sb, ptmx_device);
    if (sb->magic != PTYFS_MAGIC)
    {
        rc = 0;
    }
    else
    {
        /* fullpath is always started with /dev/ */
        return sb->mount->fullpath + 5;
    }

    return rc;
}

ptsno_t ptyfs_register_pts(rt_device_t ptmx, rt_device_t pts)
{
    ptsno_t rc;
    struct ptyfs_sb *sb;
    struct ptyfs_file *pts_file;
    struct rid_bitmap *ptsno_pool;

    /* allocate id for it and register file */
    sb = rt_container_of(ptmx, struct ptyfs_sb, ptmx_device);
    if (sb->magic != PTYFS_MAGIC)
    {
        rc = -1;
    }
    else
    {
        ptsno_pool = &sb->ptsno_pool;
        rc = rid_bitmap_get(ptsno_pool);
        if (rc >= 0)
        {
            pts_file = rt_calloc(1, sizeof(struct ptyfs_file));
            if (pts_file)
            {
                snprintf(pts_file->basename, DIRENT_NAME_MAX, "%lu", rc);
                ptyfile_init(pts_file, sb, 0, PTYFS_TYPE_FILE_SLAVE,
                             PTS_DEFAULT_FILE_MODE, pts);
                ptyfile_add_to_root(sb, pts_file);
            }
            else
            {
                rid_bitmap_put(ptsno_pool, rc);
                rc = -1;
            }
        }
        /* else rc == -1 */
    }

    return rc;
}

rt_err_t ptyfs_unregister_pts(rt_device_t ptmx, ptsno_t ptsno)
{
    ptsno_t rc;
    struct ptyfs_sb *sb;
    struct ptyfs_file *pts_file;
    struct rid_bitmap *ptsno_pool;
    char path_buf[DIRENT_NAME_MAX];

    /* allocate id for it and register file */
    sb = rt_container_of(ptmx, struct ptyfs_sb, ptmx_device);
    if (sb->magic != PTYFS_MAGIC || ptsno < 0)
    {
        rc = -EINVAL;
    }
    else
    {
        /* get path and findout device */
        snprintf(path_buf, sizeof(path_buf), "%lu", ptsno);
        pts_file = ptyfile_lookup(sb, path_buf);
        if (pts_file)
        {
            ptyfile_remove_from_root(sb, pts_file);
            ptsno_pool = &sb->ptsno_pool;
            rid_bitmap_put(ptsno_pool, ptsno);
            rc = 0;
        }
        else
        {
            rc = -ENOENT;
        }
    }

    return rc;
}

#define DEVFS_PREFIX     "/dev/"
#define DEVFS_PREFIX_LEN (sizeof(DEVFS_PREFIX) - 1)

/**
 * Create an new instance of ptyfs, and mount on target point
 * 2 basic files are created: root, ptmx.
 *
 * todo: support of mount options?
 */
static int ptyfs_ops_mount(struct dfs_mnt *mnt, unsigned long rwflag,
                           const void *data)
{
    struct ptyfs_sb *sb;
    rt_device_t ptmx_device;
    rt_err_t rc;

    if (strncmp(mnt->fullpath, DEVFS_PREFIX, DEVFS_PREFIX_LEN) != 0)
    {
        LOG_I("%s() Not mounted on `/dev/'", __func__);
        return -EINVAL;
    }

    sb = rt_calloc(1, sizeof(struct ptyfs_sb));
    if (sb)
    {
        rt_mutex_init(&sb->lock, "ptyfs", RT_IPC_FLAG_PRIO);

        /* setup the ptmx device */
        ptmx_device = &sb->ptmx_device;
        rc = lwp_ptmx_init(ptmx_device, mnt->fullpath + DEVFS_PREFIX_LEN);
        if (rc == RT_EOK)
        {
            /* setup 2 basic files */
            ptyfile_init(&sb->root_file, sb, "/", PTYFS_TYPE_DIR,
                         ROOT_DEFUALT_FILE_MODE, 0);
            ptyfile_init(&sb->ptmx_file, sb, "ptmx", PTYFS_TYPE_FILE_PTMX,
                         PTMX_DEFAULT_FILE_MODE, ptmx_device);
            ptyfile_add_to_root(sb, &sb->ptmx_file);

            /* setup rid */
            rid_bitmap_init(&sb->ptsno_pool, 0, LWP_PTY_MAX_PARIS_LIMIT,
                            sb->ptsno_pool_bitset, &sb->lock);

            /* setup properties and members */
            sb->magic = PTYFS_MAGIC;

            sb->df_size = sizeof(struct ptyfs_sb);
            rt_list_init(&sb->sibling);

            /* binding superblocks and mount point */
            mnt->data = sb;
            sb->mount = mnt;
            rc = 0;
        }
        /* else just return rc */
    }
    else
    {
        rc = -ENOMEM;
    }

    return rc;
}

static int ptyfs_ops_umount(struct dfs_mnt *mnt)
{
    /* Not supported yet */
    return -1;
}

static int ptyfs_ops_setattr(struct dfs_dentry *dentry, struct dfs_attr *attr)
{
    struct ptyfs_file *pty_file;
    struct ptyfs_sb *superblock;

    RT_ASSERT(dentry);
    RT_ASSERT(dentry->mnt);

    superblock = (struct ptyfs_sb *)dentry->mnt->data;
    RT_ASSERT(superblock);

    /* find the device related to current pts slave device */
    pty_file = ptyfile_lookup(superblock, dentry->pathname);
    if (pty_file && pty_file->type == PTYFS_TYPE_FILE_SLAVE)
    {
        pty_file->mode &= ~0xFFF;
        pty_file->mode |= attr->st_mode & 0xFFF;
        return 0;
    }

    return -1;
}

#define OPTIMAL_BSIZE 1024

static int ptyfs_ops_statfs(struct dfs_mnt *mnt, struct statfs *buf)
{
    struct ptyfs_sb *superblock;

    RT_ASSERT(mnt != NULL);
    RT_ASSERT(buf != NULL);

    superblock = (struct ptyfs_sb *)mnt->data;
    RT_ASSERT(superblock != NULL);

    buf->f_bsize = OPTIMAL_BSIZE;
    buf->f_blocks = (superblock->df_size + OPTIMAL_BSIZE - 1) / OPTIMAL_BSIZE;
    buf->f_bfree = 1;
    buf->f_bavail = buf->f_bfree;

    return RT_EOK;
}

static int ptyfs_ops_stat(struct dfs_dentry *dentry, struct stat *st)
{
    struct dfs_vnode *vnode;

    if (dentry && dentry->vnode)
    {
        vnode = dentry->vnode;

        /* device id ? */
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

    return 0;
}

static struct dfs_vnode *ptyfs_ops_lookup(struct dfs_dentry *dentry)
{
    struct dfs_vnode *vnode = RT_NULL;
    struct ptyfs_sb *superblock;
    struct ptyfs_file *pty_file;

    if (dentry == NULL || dentry->mnt == NULL || dentry->mnt->data == NULL)
    {
        return NULL;
    }

    superblock = (struct ptyfs_sb *)dentry->mnt->data;

    pty_file = ptyfile_lookup(superblock, dentry->pathname);
    if (pty_file)
    {
        vnode = dfs_vnode_create();
        if (vnode)
        {
            vnode->data = pty_file->device;
            vnode->nlink = 1;
            vnode->size = 0;
            vnode->mnt = dentry->mnt;
            /* if it's root directory */
            vnode->fops = &_default_fops;
            vnode->mode = pty_file->mode;
            vnode->type = pty_file->type == PTYFS_TYPE_DIR ? FT_DIRECTORY : FT_DEVICE;
        }
    }

    return vnode;
}

static struct dfs_vnode *ptyfs_ops_create_vnode(struct dfs_dentry *dentry,
                                                int type, mode_t mode)
{
    struct dfs_vnode *vnode = RT_NULL;
    struct ptyfs_sb *sb;
    struct ptyfs_file *pty_file;
    char *vnode_path;

    if (dentry == NULL || dentry->mnt == NULL || dentry->mnt->data == NULL)
    {
        return NULL;
    }

    sb = (struct ptyfs_sb *)dentry->mnt->data;
    RT_ASSERT(sb != NULL);

    vnode = dfs_vnode_create();
    if (vnode)
    {
        vnode_path = dentry->pathname;

        /* Query if file existed. Filter out illegal open modes */
        pty_file = ptyfile_lookup(sb, vnode_path);
        if (!pty_file || (~pty_file->mode & mode))
        {
            dfs_vnode_destroy(vnode);
            return NULL;
        }

        vnode->data = pty_file->device;
        vnode->nlink = 1;
        vnode->size = 0;
        vnode->mnt = dentry->mnt;
        vnode->fops = pty_file->device ? pty_file->device->fops : RT_NULL;
        vnode->mode &= pty_file->mode;

        if (type == FT_DIRECTORY)
        {
            vnode->mode |= S_IFDIR;
            vnode->type = FT_DIRECTORY;
            LOG_I("%s: S_IFDIR created", __func__);
        }
        else if (type == FT_REGULAR)
        {
            vnode->mode |= S_IFCHR;
            vnode->type = FT_DEVICE;
            LOG_I("%s: S_IFDIR created", __func__);
        }
        else
        {
            /* unsupported types */
            dfs_vnode_destroy(vnode);
            return NULL;
        }
    }

    return vnode;
}

static int ptyfs_ops_free_vnode(struct dfs_vnode *vnode)
{
    return RT_EOK;
}

static int devpty_deffops_getdents(struct dfs_file *file, struct dirent *dirp,
                                   uint32_t count)
{
    struct ptyfs_file *d_file;
    struct ptyfs_sb *superblock;

    RT_ASSERT(file);
    RT_ASSERT(file->dentry);
    RT_ASSERT(file->dentry->mnt);

    superblock = (struct ptyfs_sb *)file->dentry->mnt->data;
    RT_ASSERT(superblock);

    d_file = ptyfile_lookup(superblock, file->dentry->pathname);
    if (d_file)
    {
        rt_size_t index, end;
        struct dirent *d;
        struct ptyfs_file *n_file;
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
                n_file = rt_list_entry(list, struct ptyfs_file, ent_node);

                d = dirp + count;
                if (n_file->type == PTYFS_TYPE_DIR)
                {
                    d->d_type = DT_DIR;
                }
                else
                {
                    /* ptmx(5,2) or slave(136,[0,1048575]) device, on Linux */
                    d->d_type = DT_CHR;
                }

                d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
                rt_strncpy(d->d_name, n_file->basename, DIRENT_NAME_MAX);
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

static const struct dfs_filesystem_ops _ptyfs_ops = {
    .name = "ptyfs",
    .flags = DFS_FS_FLAG_DEFAULT,
    .default_fops = &_default_fops,

    .mount = ptyfs_ops_mount,
    .umount = ptyfs_ops_umount,

    /* don't allow to create symbolic link */
    .symlink = RT_NULL,
    .readlink = RT_NULL,
    .unlink = RT_NULL,

    .setattr = ptyfs_ops_setattr,
    .statfs = ptyfs_ops_statfs,
    .stat = ptyfs_ops_stat,

    .lookup = ptyfs_ops_lookup,
    .create_vnode = ptyfs_ops_create_vnode,
    .free_vnode = ptyfs_ops_free_vnode,
};

static struct dfs_filesystem_type _devptyfs = {
    .fs_ops = &_ptyfs_ops,
};

static int _ptyfs_init(void)
{
    _default_fops = *dfs_devfs_fops();
    _default_fops.getdents = devpty_deffops_getdents;

    /* register file system */
    dfs_register(&_devptyfs);

    return 0;
}
INIT_COMPONENT_EXPORT(_ptyfs_init);
