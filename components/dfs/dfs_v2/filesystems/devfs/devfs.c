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
#include <sys/unistd.h>

#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <dfs_dentry.h>
#include <dfs_mnt.h>

static int dfs_devfs_open(struct dfs_file *file)
{
    int ret = RT_EOK;

    RT_ASSERT(file != RT_NULL);
    RT_ASSERT(file->vnode->ref_count > 0);

    if (file->vnode->ref_count > 1)
    {
        if (file->vnode->type == FT_DIRECTORY
            && !(file->flags & O_DIRECTORY))
        {
            return -ENOENT;
        }
        file->fpos = 0;
    }

    if (!S_ISDIR(file->vnode->mode))
    {
        rt_device_t device = RT_NULL;
        struct dfs_dentry *de = file->dentry;
        char *device_name = rt_malloc(DFS_PATH_MAX);

        if (!device_name)
        {
            return -ENOMEM;
        }

        /* skip `/dev` */
        rt_snprintf(device_name, DFS_PATH_MAX, "%s%s", de->mnt->fullpath + sizeof("/dev") - 1, de->pathname);

        device = rt_device_find(device_name + 1);
        if (device)
        {
            file->vnode->data = device;
#ifdef RT_USING_POSIX_DEVIO
            if (device->fops && device->fops->open)
            {
                ret = device->fops->open(file);
                if (ret == RT_EOK || ret == -RT_ENOSYS)
                {
                    ret = RT_EOK;
                }
            }
            else if (device->ops && file->vnode->ref_count == 1)
#else
            if (device->ops && file->vnode->ref_count == 1)
#endif /* RT_USING_POSIX_DEVIO */
            {
                ret = rt_device_open(device, RT_DEVICE_OFLAG_RDWR);
                if (ret == RT_EOK || ret == -RT_ENOSYS)
                {
                    ret = RT_EOK;
                }
            }
        }
        rt_free(device_name);
    }

    return ret;
}

static int dfs_devfs_close(struct dfs_file *file)
{
    int ret = RT_EOK;
    rt_device_t device;

    RT_ASSERT(file != RT_NULL);
    RT_ASSERT(file->vnode->ref_count > 0);

    if (file->vnode && file->vnode->data)
    {
        /* get device handler */
        device = (rt_device_t)file->vnode->data;

#ifdef RT_USING_POSIX_DEVIO
        if (device->fops && device->fops->close)
        {
            ret = device->fops->close(file);
        }
        else if (file->vnode->ref_count == 1)
#else
        if (device->ops && file->vnode->ref_count == 1)
#endif /* RT_USING_POSIX_DEVIO */
        {
            /* close device handler */
            ret = rt_device_close(device);
        }
    }

    return ret;
}

static rt_ubase_t _get_unit_shift(rt_device_t device)
{
    rt_ubase_t shift = 0;

    /**
     * transfer unit size from POSIX RW(in bytes) to rt_device_R/W
     * (block size for blk device, otherwise in bytes).
     */
    if (device->type == RT_Device_Class_Block)
    {
        struct rt_device_blk_geometry geometry = {0};

        /* default to 512 */
        shift = 9;
        if (!rt_device_control(device, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry))
        {
            shift = __rt_ffs(geometry.block_size) - 1;
        }
    }

    return shift;
}

static ssize_t dfs_devfs_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    ssize_t ret = -RT_EIO;
    rt_device_t device;

    RT_ASSERT(file != RT_NULL);

    if (file->vnode && file->vnode->data)
    {
        /* get device handler */
        device = (rt_device_t)file->vnode->data;

#ifdef RT_USING_POSIX_DEVIO
        if (device->fops && device->fops->read)
        {
            ret = device->fops->read(file, buf, count, pos);
        }
        else
#else
        if (device->ops)
#endif /* RT_USING_POSIX_DEVIO */
        {
            rt_ubase_t shift = _get_unit_shift(device);

            ret = rt_device_read(device, *pos, buf, count >> shift);
            if (ret > 0)
            {
                ret <<= shift;
                *pos += ret;
            }
        }
    }

    return ret;
}

static ssize_t dfs_devfs_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
{
    ssize_t ret = -RT_EIO;
    rt_device_t device;

    RT_ASSERT(file != RT_NULL);

    if(file->vnode->data)
    {
        /* get device handler */
        device = (rt_device_t)file->vnode->data;

        if ((file->dentry->pathname[0] == '/') && (file->dentry->pathname[1] == '\0'))
            return -RT_ENOSYS;

#ifdef RT_USING_POSIX_DEVIO
        if (device->fops && device->fops->write)
        {
            ret = device->fops->write(file, buf, count, pos);
        }
        else
#else
        if (device->ops)
#endif /* RT_USING_POSIX_DEVIO */
        {
            rt_ubase_t shift = _get_unit_shift(device);

            /* read device data */
            ret = rt_device_write(device, *pos, buf, count >> shift);
            if (ret > 0)
            {
                ret <<= shift;
                *pos += ret;
            }
        }
    }

    return ret;
}

static int dfs_devfs_ioctl(struct dfs_file *file, int cmd, void *args)
{
    int ret = RT_EOK;
    rt_device_t device;

    RT_ASSERT(file != RT_NULL);

    if (file->vnode && file->vnode->data)
    {
        /* get device handler */
        device = (rt_device_t)file->vnode->data;

        if ((file->dentry->pathname[0] == '/') && (file->dentry->pathname[1] == '\0'))
            return -RT_ENOSYS;

#ifdef RT_USING_POSIX_DEVIO
        if (device->fops && device->fops->ioctl)
        {
            ret = device->fops->ioctl(file, cmd, args);
        }
        else
#endif /* RT_USING_POSIX_DEVIO */
        {
            ret = rt_device_control(device, cmd, args);
        }
    }

    return ret;
}

static int dfs_devfs_getdents(struct dfs_file *file, struct dirent *dirp, uint32_t count)
{
    int ret = -RT_ENOSYS;

    RT_ASSERT(file != RT_NULL);

    return ret;
}

static int dfs_devfs_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    int mask = 0;
    rt_device_t device;

    RT_ASSERT(file != RT_NULL);

    if (file->vnode && file->vnode->data)
    {
        /* get device handler */
        device = (rt_device_t)file->vnode->data;

#ifdef RT_USING_POSIX_DEVIO
        if (device->fops && device->fops->poll)
        {
            mask = device->fops->poll(file, req);
        }
#endif /* RT_USING_POSIX_DEVIO */
    }

    return mask;
}

static int dfs_devfs_flush(struct dfs_file *file)
{
    int ret = RT_EOK;
    rt_device_t device;

    RT_ASSERT(file != RT_NULL);

    if (file->vnode && file->vnode->data)
    {
        /* get device handler */
        device = (rt_device_t)file->vnode->data;

#ifdef RT_USING_POSIX_DEVIO
        if (device->fops && device->fops->flush)
        {
            ret = device->fops->flush(file);
        }
#endif /* RT_USING_POSIX_DEVIO */
    }

    return ret;
}

static off_t dfs_devfs_lseek(struct dfs_file *file, off_t offset, int wherece)
{
    off_t ret = -EPERM;
    rt_device_t device;

    RT_ASSERT(file != RT_NULL);

    if (file->vnode && file->vnode->data)
    {
        /* get device handler */
        device = (rt_device_t)file->vnode->data;

#ifdef RT_USING_POSIX_DEVIO
        if (device->fops && device->fops->lseek)
        {
            ret = device->fops->lseek(file, offset, wherece);
        }
#endif /* RT_USING_POSIX_DEVIO */
    }

    return ret;
}

static int dfs_devfs_truncate(struct dfs_file *file, off_t offset)
{
    int ret = RT_EOK;
    rt_device_t device;

    RT_ASSERT(file != RT_NULL);

    if (file->vnode && file->vnode->data)
    {
        /* get device handler */
        device = (rt_device_t)file->vnode->data;

#ifdef RT_USING_POSIX_DEVIO
        if (device->fops && device->fops->truncate)
        {
            ret = device->fops->truncate(file, offset);
        }
#endif /* RT_USING_POSIX_DEVIO */
    }

    return ret;
}

static int dfs_devfs_mmap(struct dfs_file *file, struct lwp_avl_struct *mmap)
{
    int ret = RT_EOK;
    rt_device_t device;

    RT_ASSERT(file != RT_NULL);

    if (file->vnode && file->vnode->data)
    {
        /* get device handler */
        device = (rt_device_t)file->vnode->data;

#ifdef RT_USING_POSIX_DEVIO
        if (device->fops && device->fops->mmap)
        {
            ret = device->fops->mmap(file, mmap);
        }
#endif /* RT_USING_POSIX_DEVIO */
    }

    return ret;
}

static int dfs_devfs_lock(struct dfs_file *file, struct file_lock *flock)
{
    int ret = RT_EOK;
    rt_device_t device;

    RT_ASSERT(file != RT_NULL);

    if (file->vnode && file->vnode->data)
    {
        /* get device handler */
        device = (rt_device_t)file->vnode->data;

#ifdef RT_USING_POSIX_DEVIO
        if (device->fops && device->fops->lock)
        {
            ret = device->fops->lock(file, flock);
        }
#endif /* RT_USING_POSIX_DEVIO */
    }

    return ret;
}

static int dfs_devfs_flock(struct dfs_file *file, int operation, struct file_lock *flock)
{
    int ret = RT_EOK;
    rt_device_t device;

    RT_ASSERT(file != RT_NULL);

    if (file->vnode && file->vnode->data)
    {
        /* get device handler */
        device = (rt_device_t)file->vnode->data;

#ifdef RT_USING_POSIX_DEVIO
        if (device->fops && device->fops->flock)
        {
            ret = device->fops->flock(file, operation, flock);
        }
#endif /* RT_USING_POSIX_DEVIO */
    }

    return ret;
}

static const struct dfs_file_ops _dev_fops =
{
    .open = dfs_devfs_open,
    .close = dfs_devfs_close,
    .read = dfs_devfs_read,
    .write = dfs_devfs_write,
    .ioctl = dfs_devfs_ioctl,
    .getdents = dfs_devfs_getdents,
    .poll = dfs_devfs_poll,

    .flush = dfs_devfs_flush,
    .lseek = dfs_devfs_lseek,
    .truncate = dfs_devfs_truncate,
    .mmap = dfs_devfs_mmap,
    .lock = dfs_devfs_lock,
    .flock = dfs_devfs_flock,
};

const struct dfs_file_ops *dfs_devfs_fops(void)
{
    return &_dev_fops;
}

mode_t dfs_devfs_device_to_mode(struct rt_device *device)
{
    mode_t mode = 0;

    switch (device->type)
    {
    case RT_Device_Class_Char:
        mode = S_IFCHR | 0666;
        break;
    case RT_Device_Class_Block:
        mode = S_IFBLK | 0666;
        break;
    case RT_Device_Class_Pipe:
        mode = S_IFIFO | 0666;
        break;
    default:
        mode = S_IFCHR | 0666;
        break;
    }

    return mode;
}

static void dfs_devfs_mkdir(const char *fullpath, mode_t mode)
{
    int len = rt_strlen(fullpath);
    char *path = (char *)rt_malloc(len + 1);

    if (path)
    {
        int index = len - 1;

        rt_strcpy(path, fullpath);

        if (path[index] == '/')
        {
            path[index] = '\0';
            index --;
        }

        while (path[index] != '/' && index >= 0)
        {
            index --;
        }

        path[index] = '\0';

        if (index > 0 && access(path, 0) != 0)
        {
            int i = 0;

            if (path[i] == '/')
            {
                i ++;
            }

            while (index > i)
            {
                if (path[i] == '/')
                {
                    path[i] = '\0';
                    mkdir(path, mode);
                    path[i] = '/';
                }

                i ++;
            }

            mkdir(path, mode);
        }
    }
}

void dfs_devfs_device_add(rt_device_t device)
{
    int fd;
    char path[512];

    if (device)
    {
        rt_snprintf(path, 512, "/dev/%s", device->parent.name);

        if (access(path, 0) != 0)
        {
            mode_t mode = dfs_devfs_device_to_mode(device);

            dfs_devfs_mkdir(path, mode);

            fd = open(path, O_RDWR | O_CREAT, mode);
            if (fd >= 0)
            {
                close(fd);
            }
        }
    }
}

int dfs_devfs_update(void)
{
    int count = rt_object_get_length(RT_Object_Class_Device);
    if (count > 0)
    {
        rt_device_t *devices = rt_malloc(count * sizeof(rt_device_t));
        if (devices)
        {
            rt_object_get_pointers(RT_Object_Class_Device, (rt_object_t *)devices, count);

            for (int index = 0; index < count; index ++)
            {
                dfs_devfs_device_add(devices[index]);
            }
            rt_free(devices);
        }
    }

    return count;
}
