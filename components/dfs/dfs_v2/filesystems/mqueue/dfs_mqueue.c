/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-04     zhkag        first Version
 */

#include <rtthread.h>
#include <rthw.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <dfs_dentry.h>
#include <dfs_mnt.h>
#include "dfs_mqueue.h"

static rt_list_t _mqueue_file_list = RT_LIST_OBJECT_INIT(_mqueue_file_list);
struct rt_spinlock mqueue_lock;

void dfs_mqueue_insert_after(rt_list_t *n) {
    rt_spin_lock(&mqueue_lock);
    rt_list_insert_after(&(_mqueue_file_list), n);
    rt_spin_unlock(&mqueue_lock);
}

struct mqueue_file *dfs_mqueue_lookup(const char *path, rt_size_t *size) {
    struct mqueue_file *file;
    rt_list_t *node;
    rt_spin_lock(&mqueue_lock);
    rt_list_for_each(node, &_mqueue_file_list) {
        file = rt_list_entry(node, struct mqueue_file, list);

        if (rt_strncmp(file->name, path, RT_NAME_MAX) == 0) {
            *size = file->size;
            rt_spin_unlock(&mqueue_lock);
            return file;
        }
    }
    rt_spin_unlock(&mqueue_lock);
    return RT_NULL;
}

int dfs_mqueue_mount(struct dfs_mnt *mnt, unsigned long rwflag, const void *data) {
    return RT_EOK;
}

int dfs_mqueue_umount(struct dfs_mnt *mnt) {
    return RT_EOK;
}

int dfs_mqueue_statfs(struct dfs_mnt *mnt, struct statfs *buf) {
    return RT_EOK;
}

int dfs_mqueue_close(struct dfs_file *file) {
    return RT_EOK;
}

int dfs_mqueue_open(struct dfs_file *file) {
    return 0;
}

int dfs_mqueue_stat(struct dfs_dentry *dentry, struct stat *st) {
    struct dfs_vnode *vnode = RT_NULL;
    if (dentry && dentry->vnode) {
        vnode = dentry->vnode;
        st->st_dev = 0;
        st->st_gid = vnode->gid;
        st->st_uid = vnode->uid;
        st->st_ino = 0;
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

int dfs_mqueue_getdents(struct dfs_file *file, struct dirent *dirp, uint32_t count) {
    rt_size_t index, end;
    struct dirent *d;
    count = (count / sizeof(struct dirent));
    end = file->fpos + count;
    index = 0;
    count = 0;
    struct mqueue_file *mq_file;
    rt_list_t *node;
    rt_spin_lock(&mqueue_lock);
    rt_list_for_each(node, &_mqueue_file_list) {
        if (index >= (rt_size_t)file->fpos) {
            mq_file = rt_list_entry(node, struct mqueue_file, list);
            d = dirp + count;
            d->d_namlen = RT_NAME_MAX;
            d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
            rt_strncpy(d->d_name, mq_file->name, RT_NAME_MAX);
            count += 1;
            file->fpos += 1;
        }
        index += 1;
        if (index >= end) {
            break;
        }
    }
    rt_spin_unlock(&mqueue_lock);
    return count * sizeof(struct dirent);
}

int dfs_mqueue_unlink(struct dfs_dentry *dentry) {
    rt_size_t size;
    struct mqueue_file *mq_file;
    mq_file = dfs_mqueue_lookup(dentry->pathname + 1, &size);
    if (mq_file == RT_NULL)
        return -ENOENT;
    rt_list_remove(&(mq_file->list));
    if (mq_file->data != RT_NULL)
        rt_mq_delete((rt_mq_t)mq_file->data);
    rt_free(mq_file);
    return RT_EOK;
}

static struct dfs_vnode *dfs_mqueue_create_vnode(struct dfs_dentry *dentry, int type, mode_t mode) {
    struct dfs_vnode *vnode = RT_NULL;
    rt_size_t size;
    struct mqueue_file *mq_file;

    if (dentry == NULL || dentry->mnt == NULL) {
        return NULL;
    }

    vnode = dfs_vnode_create();
    if (vnode) {
        mq_file = dfs_mqueue_lookup(dentry->pathname + 1, &size);
        if (mq_file == RT_NULL) {
            mq_file = (struct mqueue_file *)rt_malloc(sizeof(struct mqueue_file));
            if (mq_file == RT_NULL) {
                return NULL;
            }
            mq_file->msg_size = 8192;
            mq_file->max_msgs = 10;
            strncpy(mq_file->name, dentry->pathname + 1, RT_NAME_MAX);
            dfs_mqueue_insert_after(&(mq_file->list));
        }

        vnode->mode = S_IFREG | (S_IRWXU | S_IRWXG | S_IRWXO);
        vnode->type = FT_REGULAR;
        rt_mq_t mq = rt_mq_create(dentry->pathname + 1, mq_file->msg_size, mq_file->max_msgs,
                                  RT_IPC_FLAG_FIFO);
        mq_file->data = (void *)mq;
        vnode->data = mq_file;
        vnode->size = 0;
    }
    return vnode;
}

static int dfs_mqueue_free_vnode(struct dfs_vnode *vnode) {
    /* nothing to be freed */
    if (vnode && vnode->ref_count <= 1) {
        vnode->data = NULL;
    }
    return 0;
}

static const struct dfs_file_ops _mqueue_fops = {
    .open = dfs_mqueue_open,
    .close = dfs_mqueue_close,
    .getdents = dfs_mqueue_getdents,
};

struct dfs_vnode *_dfs_mqueue_lookup(struct dfs_dentry *dentry) {
    struct dfs_vnode *vnode = RT_NULL;
    rt_size_t size;
    // struct tmpfs_sb *superblock;
    struct mqueue_file *mq_file;

    if (dentry == NULL || dentry->mnt == NULL) {
        return NULL;
    }

    if (dentry->pathname[0] == '/' && dentry->pathname[1] == '\0') {
    }

    mq_file = dfs_mqueue_lookup(dentry->pathname + 1, &size);

    vnode = dfs_vnode_create();
    if (mq_file && mq_file->data) {
        vnode->mode = S_IFREG | (S_IRWXU | S_IRWXG | S_IRWXO);
        vnode->type = FT_REGULAR;
        vnode->mnt = dentry->mnt;
        vnode->data = mq_file;
        vnode->size = mq_file->size;
    } else {
        vnode->size = 0;
        vnode->nlink = 1;
        vnode->fops = &_mqueue_fops;
        vnode->mnt = dentry->mnt;
        vnode->type = FT_DIRECTORY;
        vnode->mode = S_IFDIR | (S_IRUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    }
    return vnode;
}

static const struct dfs_filesystem_ops _mqueue_ops = {
    .name = "mqueue",
    .flags = DFS_FS_FLAG_DEFAULT,
    .default_fops = &_mqueue_fops,

    .mount = dfs_mqueue_mount,
    .umount = dfs_mqueue_umount,
    .statfs = dfs_mqueue_statfs,

    .unlink = dfs_mqueue_unlink,
    .stat = dfs_mqueue_stat,

    .lookup = _dfs_mqueue_lookup,
    .create_vnode = dfs_mqueue_create_vnode,
    .free_vnode = dfs_mqueue_free_vnode
};

static struct dfs_filesystem_type _mqueue = {
    .fs_ops = &_mqueue_ops,
};

int dfs_mqueue_init(void) {
    /* register mqueue file system */
    dfs_register(&_mqueue);
    mkdir("/dev/mqueue", 0x777);
    if (dfs_mount(RT_NULL, "/dev/mqueue", "mqueue", 0, 0) != 0)
    {
        rt_kprintf("Dir /dev/mqueue mount failed!\n");
    }
    return 0;
}
INIT_ENV_EXPORT(dfs_mqueue_init);
