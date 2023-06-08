/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-11     Bernard      Ignore O_CREAT flag in open.
 */
#include <rthw.h>
#include <rtdbg.h>
#include <rtdevice.h>

#include <fcntl.h>
#include <errno.h>

#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <dfs_dentry.h>
#include <dfs_mnt.h>

#include "devfs.h"

struct device_dirent
{
    struct rt_device **devices;
    uint32_t device_count;
};

int dfs_devfs_open(struct dfs_file *file);
int dfs_devfs_close(struct dfs_file *file);
int generic_dfs_lseek(struct dfs_file *file, off_t offset, int whence);
int dfs_devfs_read(struct dfs_file *file, void *buf, size_t count, off_t *pos);
int dfs_devfs_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos);
int dfs_devfs_ioctl(struct dfs_file *file, int cmd, void *args);
int dfs_devfs_getdents(struct dfs_file *file, struct dirent *dirp, uint32_t count);
static int dfs_devfs_poll(struct dfs_file *file, struct rt_pollreq *req);

int dfs_devfs_mount(struct dfs_mnt *mnt, unsigned long rwflag, const void *data);
int dfs_devfs_umount(struct dfs_mnt *mnt);
int dfs_devfs_unlink(struct dfs_dentry *dentry);
int dfs_devfs_stat(struct dfs_dentry *dentry, struct stat *st);
int dfs_devfs_statfs(struct dfs_mnt *mnt, struct statfs *buf);
static struct dfs_vnode *dfs_devfs_lookup(struct dfs_dentry *dentry);
struct dfs_vnode *dfs_devfs_create_vnode(struct dfs_dentry *dentry, int type, mode_t mode);
static int dfs_devfs_free_vnode(struct dfs_vnode *vnode);

static const struct dfs_file_ops _dev_fops =
{
    .open = dfs_devfs_open,
    .close = dfs_devfs_close,
    .lseek = generic_dfs_lseek,
    .read = dfs_devfs_read,
    .write = dfs_devfs_write,
    .ioctl = dfs_devfs_ioctl,
    .getdents = dfs_devfs_getdents,
    .poll = dfs_devfs_poll,
};

static const struct dfs_filesystem_ops _devfs_ops =
{
    .name = "devfs",

    .default_fops = &_dev_fops,
    .mount = dfs_devfs_mount,
    .umount = dfs_devfs_umount,
    .unlink = dfs_devfs_unlink,
    .stat = dfs_devfs_stat,
    .statfs = dfs_devfs_statfs,
    .lookup = dfs_devfs_lookup,
    .create_vnode = dfs_devfs_create_vnode,
    .free_vnode = dfs_devfs_free_vnode,
};

static struct dfs_filesystem_type _devfs =
{
    .fs_ops = &_devfs_ops,
};

static int _device_to_mode(struct rt_device *device)
{
    int mode = 0;

    switch (device->type)
    {
    case RT_Device_Class_Char:
        mode = S_IFCHR | 0777;
        break;
    case RT_Device_Class_Block:
        mode = S_IFBLK | 0777;
        break;
    case RT_Device_Class_Pipe:
        mode = S_IFIFO | 0777;
        break;
    default:
        mode = S_IFCHR | 0777;
        break;
    }

    return mode;
}

static int _devfs_root_dirent_update(struct dfs_vnode *vnode)
{
    rt_err_t result = RT_EOK;

    if (vnode)
    {
        // result = rt_mutex_take(&vnode->lock, RT_WAITING_FOREVER);
        result = dfs_file_lock();
        if (result == RT_EOK)
        {
            rt_uint32_t count = 0;
            struct device_dirent *root_dirent = (struct device_dirent*) vnode->data;
            if (root_dirent) rt_free(root_dirent);

            count = rt_object_get_length(RT_Object_Class_Device);
            root_dirent = (struct device_dirent *)rt_malloc(sizeof(struct device_dirent) + count * sizeof(rt_device_t));
            if (root_dirent != RT_NULL)
            {
                root_dirent->device_count = count;
                if (count != 0)
                {
                    root_dirent->devices = (rt_device_t *)(root_dirent + 1);
                    rt_object_get_pointers(RT_Object_Class_Device, (rt_object_t *)root_dirent->devices, count);
                }
                else
                {
                    root_dirent->devices = RT_NULL;
                }
            }

            vnode->data = root_dirent;
            result = count;
            dfs_file_unlock();
        }
    }

    return result;
}

static struct dfs_vnode *dfs_devfs_lookup(struct dfs_dentry *dentry)
{
    rt_device_t device = RT_NULL;
    struct dfs_vnode *vnode = RT_NULL;
    const char *pathname = dentry->pathname;

    DLOG(msg, "devfs", "vnode", DLOG_MSG, "dfs_vnode_create");
    vnode = dfs_vnode_create();
    if (vnode)
    {
        if (pathname[0] == '/' && pathname[1] == '\0')
        {
            int count = _devfs_root_dirent_update(vnode);

            vnode->mode = S_IFDIR | 0644;
            vnode->size = count;
            vnode->nlink = 1;
            vnode->fops = &_dev_fops;
            vnode->mnt = dentry->mnt;
            vnode->type = FT_DIRECTORY;
        }
        else
        {
            device = rt_device_find(&pathname[1]);
            if (!device)
            {
                DLOG(msg, "devfs", "vnode", DLOG_MSG, "dfs_vnode_destroy(vnode), no-device");
                dfs_vnode_destroy(vnode);
                vnode = RT_NULL;
            }
            else
            {
                vnode->mode = _device_to_mode(device);
                vnode->size = device->ref_count;
                vnode->nlink = 1;
                if (device->fops)
                {
                    vnode->fops = device->fops;
                }
                else
                {
                    vnode->fops = &_dev_fops;
                }
                vnode->data = device;
                vnode->mnt = dentry->mnt;
                vnode->type = FT_DEVICE;
            }
        }
    }

    return vnode;
}

struct dfs_vnode *dfs_devfs_create_vnode(struct dfs_dentry *dentry, int type, mode_t mode)
{
#ifdef RT_USING_DEV_BUS
    if (dentry && type == FT_DIRECTORY)
    {
        /* regester bus device */
        if (rt_device_bus_create(&dentry->pathname[1], 0))
        {
            return dfs_devfs_lookup(dentry);
        }
    }
#endif

    return RT_NULL;
}

int dfs_devfs_free_vnode(struct dfs_vnode *vnode)
{
    if (S_ISDIR(vnode->mode))
    {
        struct device_dirent *root_dirent;

        root_dirent = (struct device_dirent *)vnode->data;
        RT_ASSERT(root_dirent != RT_NULL);

        /* release dirent */
        DLOG(msg, "devfs", "devfs", DLOG_MSG, "free root_dirent");
        rt_free(root_dirent);
        return RT_EOK;
    }

    /* which is a device */
    vnode->data = RT_NULL;
    return 0;
}

int dfs_devfs_mount(struct dfs_mnt *mnt, unsigned long rwflag, const void *data)
{
    RT_ASSERT(mnt != RT_NULL);
    return RT_EOK;
}

int dfs_devfs_umount(struct dfs_mnt *mnt)
{
    return RT_EOK;
}

int dfs_devfs_statfs(struct dfs_mnt *mnt, struct statfs *buf)
{
    if (mnt && buf)
    {
        buf->f_bsize  = 512;
        buf->f_blocks = 2048 * 64; // 64M
        buf->f_bfree  = buf->f_blocks;
        buf->f_bavail = buf->f_bfree;
    }

    return RT_EOK;
}

int dfs_devfs_ioctl(struct dfs_file *file, int cmd, void *args)
{
    rt_err_t result;
    rt_device_t dev_id;

    RT_ASSERT(file != RT_NULL);

    /* get device handler */
    dev_id = (rt_device_t)file->vnode->data;
    RT_ASSERT(dev_id != RT_NULL);

    if ((file->dentry->pathname[0] == '/') && (file->dentry->pathname[1] == '\0'))
        return -RT_ENOSYS;

    /* close device handler */
    result = rt_device_control(dev_id, cmd, args);
    if (result == RT_EOK)
        return RT_EOK;

    return result;
}

int dfs_devfs_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    int result;
    rt_device_t dev_id;

    RT_ASSERT(file != RT_NULL);

    /* get device handler */
    dev_id = (rt_device_t)file->vnode->data;
    RT_ASSERT(dev_id != RT_NULL);

    if ((file->dentry->pathname[0] == '/') && (file->dentry->pathname[1] == '\0'))
        return -RT_ENOSYS;

    /* read device data */
    result = rt_device_read(dev_id, *pos, buf, count);
    *pos += result;

    return result;
}

int dfs_devfs_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
{
    int result;
    rt_device_t dev_id;

    RT_ASSERT(file != RT_NULL);

    /* get device handler */
    dev_id = (rt_device_t)file->vnode->data;
    RT_ASSERT(dev_id != RT_NULL);

    if ((file->dentry->pathname[0] == '/') && (file->dentry->pathname[1] == '\0'))
        return -RT_ENOSYS;

    /* read device data */
    result = rt_device_write(dev_id, *pos, buf, count);
    *pos += result;

    return result;
}

int dfs_devfs_close(struct dfs_file *file)
{
    rt_err_t result = RT_EOK;
    rt_device_t device;

    RT_ASSERT(file != RT_NULL);

    if (!S_ISDIR(file->vnode->mode))
    {
        /* get device handler */
        device = (rt_device_t)file->vnode->data;
        RT_ASSERT(device != RT_NULL);

        /* close device handler */
        result = rt_device_close(device);
    }

    return result;
}

int dfs_devfs_open(struct dfs_file *file)
{
    rt_err_t result = RT_EOK;

    /* open root directory */
    if ((file->dentry->pathname[0] == '/' && file->dentry->pathname[1] == '\0') ||
        (S_ISDIR(file->vnode->mode)))
    {
        /* re-open the root directory for re-scan devices */
        _devfs_root_dirent_update(file->vnode);
        return RT_EOK;
    }
    else
    {
        rt_device_t device = RT_NULL;

        device = (struct rt_device *)file->vnode->data;
        if (device)
        {
#ifdef RT_USING_POSIX_DEVIO
            if (device->fops)
            {
                /* use device fops */
                file->fops = device->fops;
                /* use fops->open */
                if (file->vnode->fops->open)
                {
                    result = file->vnode->fops->open(file);
                    if (result == RT_EOK || result == -RT_ENOSYS)
                    {
                        return RT_EOK;
                    }
                }
            }
            else
#endif /* RT_USING_POSIX_DEVIO */
            {
                result = rt_device_open(device, RT_DEVICE_OFLAG_RDWR);
                if (result == RT_EOK || result == -RT_ENOSYS)
                {
                    file->fops = &_dev_fops;
                    return RT_EOK;
                }
            }
        }
    }

    /* open device failed. */
    return -EIO;
}

int dfs_devfs_unlink(struct dfs_dentry *dentry)
{
#ifdef RT_USING_DEV_BUS
    rt_device_t dev_id;

    dev_id = rt_device_find(&dentry->pathname[1]);
    if (dev_id == RT_NULL)
    {
        return -1;
    }
    if (dev_id->type != RT_Device_Class_Bus)
    {
        return -1;
    }
    rt_device_bus_destroy(dev_id);
#endif
    return RT_EOK;
}

int dfs_devfs_stat(struct dfs_dentry *dentry, struct stat *st)
{
    int ret = RT_EOK;
    const char *path = RT_NULL;
    struct dfs_vnode *vnode = RT_NULL;

    if (dentry && dentry->vnode)
    {
        path = dentry->pathname;
        vnode = dentry->vnode;

        /* stat root directory */
        if ((path[0] == '/') && (path[1] == '\0'))
        {
            st->st_dev = 0;
            st->st_gid = vnode->gid;
            st->st_uid = vnode->uid;
            st->st_ino = 0;
            st->st_mode  = vnode->mode;
            st->st_nlink = vnode->nlink;
            st->st_size  = vnode->size;
            st->st_mtim.tv_nsec = vnode->mtime.tv_nsec;
            st->st_mtim.tv_sec  = vnode->mtime.tv_sec;
            st->st_ctim.tv_nsec = vnode->ctime.tv_nsec;
            st->st_ctim.tv_sec  = vnode->ctime.tv_sec;
            st->st_atim.tv_nsec = vnode->atime.tv_nsec;
            st->st_atim.tv_sec  = vnode->atime.tv_sec;
        }
        else
        {
            rt_device_t dev_id;

            dev_id = rt_device_find(&path[1]);
            if (dev_id != RT_NULL)
            {
                st->st_dev = 0;
                st->st_gid = vnode->gid;
                st->st_uid = vnode->uid;
                st->st_ino = 0;
                st->st_mode  = vnode->mode;
                st->st_nlink = vnode->nlink;
                st->st_size  = vnode->size;
                st->st_mtim.tv_nsec = vnode->mtime.tv_nsec;
                st->st_mtim.tv_sec  = vnode->mtime.tv_sec;
                st->st_ctim.tv_nsec = vnode->ctime.tv_nsec;
                st->st_ctim.tv_sec  = vnode->ctime.tv_sec;
                st->st_atim.tv_nsec = vnode->atime.tv_nsec;
                st->st_atim.tv_sec  = vnode->atime.tv_sec;
            }
            else
            {
                ret = -ENOENT;
            }
        }
    }

    return ret;
}

int dfs_devfs_getdents(struct dfs_file *file, struct dirent *dirp, uint32_t count)
{
    rt_uint32_t index;
    rt_object_t object;
    struct dirent *d;
    struct device_dirent *root_dirent;

    root_dirent = (struct device_dirent *)file->vnode->data;
    RT_ASSERT(root_dirent != RT_NULL);

    /* make integer count */
    count = (count / sizeof(struct dirent));
    if (count == 0)
        return -EINVAL;

    for (index = 0; index < count && index + file->fpos < root_dirent->device_count; index ++)
    {
        object = (rt_object_t)root_dirent->devices[file->fpos + index];

        d = dirp + index;
        d->d_type = DT_REG;
        d->d_namlen = RT_NAME_MAX;
        d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
        rt_strncpy(d->d_name, object->name, RT_NAME_MAX);
        d->d_name[RT_NAME_MAX] = '\0';
    }

    file->fpos += index;

    return index * sizeof(struct dirent);
}

static int dfs_devfs_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    int mask = 0;

    return mask;
}

int dfs_devfs_init(void)
{
    /* register devfs file system */
    dfs_register(&_devfs);

    dfs_mount(RT_NULL, "/dev", "devfs", 0, RT_NULL);

    return 0;
}
INIT_COMPONENT_EXPORT(dfs_devfs_init);

