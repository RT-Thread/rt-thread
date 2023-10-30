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
#include <dfs_file.h>
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

int dfs_mqueue_mount(struct dfs_filesystem *fs, unsigned long rwflag, const void *data) {
    return RT_EOK;
}

int dfs_mqueue_unmount(struct dfs_filesystem *fs) { return RT_EOK; }

int dfs_mqueue_statfs(struct dfs_filesystem *fs, struct statfs *buf) { return RT_EOK; }

int dfs_mqueue_close(struct dfs_file *file) { return RT_EOK; }

int dfs_mqueue_open(struct dfs_file *file) {
    rt_size_t size;
    if ((file->vnode->path[0] == '/') && (file->vnode->path[1] == '\0'))
        return 0;

    if (file->flags & O_DIRECTORY)
        return -ENOENT;

    struct mqueue_file *mq_file;

    mq_file = dfs_mqueue_lookup(file->vnode->path + 1, &size);
    if (mq_file == RT_NULL && !(file->flags & O_CREAT))
        return -ENOENT;
    if (mq_file == RT_NULL) {
        mq_file = (struct mqueue_file *)rt_malloc(sizeof(struct mqueue_file));
        if (mq_file == RT_NULL) {
            return -ENFILE;
        }
        mq_file->msg_size = 8192;
        mq_file->max_msgs = 10;
        strncpy(mq_file->name, file->vnode->path + 1, RT_NAME_MAX);
        dfs_mqueue_insert_after(&(mq_file->list));
    }

    if (file->flags & O_CREAT) {
        rt_mq_t mq = rt_mq_create(file->vnode->path + 1, mq_file->msg_size, mq_file->max_msgs,
                                  RT_IPC_FLAG_FIFO);
        mq_file->data = (void *)mq;
        file->vnode->data = mq_file;
        file->vnode->size = 0;
    }

    return 0;
}

int dfs_mqueue_stat(struct dfs_filesystem *fs, const char *path, struct stat *st) {
    st->st_dev = 0;
    st->st_mode = S_IFREG | S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH;
    st->st_size = 0;
    st->st_mtime = 0;
    return RT_EOK;
}

int dfs_mqueue_getdents(struct dfs_file *file, struct dirent *dirp, uint32_t count) {
    rt_size_t index, end;
    struct dirent *d;
    count = (count / sizeof(struct dirent));
    end = file->pos + count;
    index = 0;
    count = 0;
    struct mqueue_file *mq_file;
    rt_list_t *node;
    rt_spin_lock(&mqueue_lock);
    rt_list_for_each(node, &_mqueue_file_list) {
        if (index >= (rt_size_t)file->pos) {
            mq_file = rt_list_entry(node, struct mqueue_file, list);
            d = dirp + count;
            d->d_namlen = RT_NAME_MAX;
            d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
            rt_strncpy(d->d_name, mq_file->name, RT_NAME_MAX);
            count += 1;
            file->pos += 1;
        }
        index += 1;
        if (index >= end) {
            break;
        }
    }
    rt_spin_unlock(&mqueue_lock);
    return count * sizeof(struct dirent);
}

int dfs_mqueue_unlink(struct dfs_filesystem *fs, const char *path) {
    rt_size_t size;
    struct mqueue_file *mq_file;
    mq_file = dfs_mqueue_lookup(path + 1, &size);
    if (mq_file == RT_NULL)
        return -ENOENT;
    rt_list_remove(&(mq_file->list));
    if (mq_file->data != RT_NULL)
        rt_mq_delete((rt_mq_t)mq_file->data);
    rt_free(mq_file);
    return RT_EOK;
}

static const struct dfs_file_ops _mqueue_fops = {
    .open = dfs_mqueue_open,
    .close = dfs_mqueue_close,
    .getdents = dfs_mqueue_getdents,
};

static const struct dfs_filesystem_ops _mqueue = {
    .name = "mqueue",
    .flags = DFS_FS_FLAG_DEFAULT,
    .fops = &_mqueue_fops,

    .mount = dfs_mqueue_mount,
    .unmount = dfs_mqueue_unmount,
    .statfs = dfs_mqueue_statfs,

    .unlink = dfs_mqueue_unlink,
    .stat = dfs_mqueue_stat,
};

int dfs_mqueue_init(void) {
    /* register mqueue file system */
    dfs_register(&_mqueue);
    mkdir("/dev/mqueue", 0x777);
    if (dfs_mount(RT_NULL, "/dev/mqueue", "mqueue", 0, 0) != 0) {
        rt_kprintf("Dir /dev/mqueue mount failed!\n");
    }
    return 0;
}
INIT_ENV_EXPORT(dfs_mqueue_init);
