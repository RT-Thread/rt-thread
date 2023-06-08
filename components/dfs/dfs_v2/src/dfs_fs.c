/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2005-02-22     Bernard      The first version.
 * 2010-06-30     Bernard      Optimize for RT-Thread RTOS
 * 2011-03-12     Bernard      fix the filesystem lookup issue.
 * 2017-11-30     Bernard      fix the filesystem_operation_table issue.
 * 2017-12-05     Bernard      fix the fs type search issue in mkfs.
 * 2023-05-05     Bernard      change to dfs v2.0
 */

#include <dfs_fs.h>
#include <dfs_file.h>
#include <dfs_dentry.h>
#include <dfs_mnt.h>
#include "dfs_private.h"

#define DBG_TAG "DFS.fs"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct dfs_filesystem_type *file_systems = NULL;
extern rt_list_t _mnt_list;

/**
 * @addtogroup FsApi
 */
/*@{*/

static struct dfs_filesystem_type **_find_filesystem(const char *name)
{
    struct dfs_filesystem_type **type;
    for (type = &file_systems; *type; type = &(*type)->next)
    {
        if (strcmp((*type)->fs_ops->name, name) == 0)
            break;
    }

    return type;
}

int dfs_register(struct dfs_filesystem_type *fs)
{
    int ret = 0;
    struct dfs_filesystem_type **type = _find_filesystem(fs->fs_ops->name);

    LOG_D("register %s file system.", fs->fs_ops->name);

    if (*type)
    {
        ret = -EBUSY;
    }
    else
    {
        *type = fs;
    }

    return ret;
}

int dfs_unregister(struct dfs_filesystem_type *fs)
{
    int ret = 0;
    struct dfs_filesystem_type **type;

    if (fs)
    {
        LOG_D("unregister %s file system.", fs->fs_ops->name);

        for (type = &file_systems; *type; type = &(*type)->next)
        {
            if (strcmp((*type)->fs_ops->name, fs->fs_ops->name) == 0)
            {
                *type = (*type)->next;
                break;
            }
        }

        if (!*type) ret = -EINVAL;
    }

    return ret;
}

/*
 *    parent(mount path)
 *    mnt_parent <- - - - - - -  +
 *         |                     |
 *         |- mnt_child <- - - - - -+ (1 refcount)
 *                 |             |
 *                 |- parent - - + (1 refcount)
 */
int dfs_mount(const char *device_name,
              const char *path,
              const char *filesystemtype,
              unsigned long rwflag,
              const void *data)
{
    int ret = RT_EOK;
    char *fullpath = RT_NULL;
    rt_device_t dev_id = RT_NULL;
    struct dfs_mnt *mnt_parent = RT_NULL, *mnt_child = RT_NULL;
    struct dfs_dentry *mntpoint_dentry = RT_NULL;
    struct dfs_filesystem_type *type = *_find_filesystem(filesystemtype);

    if (type)
    {
        fullpath = dfs_normalize_path(RT_NULL, path);
        if (!fullpath)
        {
            rt_set_errno(EPERM);
            ret = -1;
        }
    }
    else
    {
        rt_set_errno(ENOENT);
        ret = -1;
    }

    if (fullpath)
    {
        DLOG(note, "mnt", "mount %s(%s) on path: %s", device_name, filesystemtype, fullpath);

        /* open specific device */
        if (device_name) dev_id = rt_device_find(device_name);

        if (!(type->fs_ops->flags & FS_NEED_DEVICE) ||
            ((type->fs_ops->flags & FS_NEED_DEVICE) && dev_id))
        {
            DLOG(msg, "dfs", "mnt", DLOG_MSG, "mnt_parent = dfs_mnt_lookup(%s)", fullpath);
            mnt_parent = dfs_mnt_lookup(fullpath);
            if ((!mnt_parent && (strcmp(fullpath, "/") == 0 || strcmp(fullpath, "/dev") == 0))
                || (mnt_parent && strcmp(fullpath, "/") == 0 && strcmp(mnt_parent->fullpath, fullpath) != 0))
            {
                LOG_D("no mnt found @ mount point %s, should be root.", fullpath);
                DLOG(msg, "mnt", "dfs", DLOG_MSG_RET, "no mnt");

                /* it's the root file system */
                /* the mount point dentry is the same as root dentry. */

                DLOG(msg, "dfs", "mnt", DLOG_MSG, "mnt_parent = dfs_mnt_create(path)");
                mnt_parent = dfs_mnt_create(fullpath); /* mnt->ref_count should be 1. */
                if (mnt_parent)
                {
                    DLOG(msg, "mnt", "dfs", DLOG_MSG_RET, "return mnt, ref_count=1");

                    mnt_parent->fs_ops = type->fs_ops;
                    mnt_parent->dev_id = dev_id;
                    if (mnt_parent->fs_ops->mount)
                    {
                        DLOG(msg, "dfs", type->fs_ops->name, DLOG_MSG, "fs_ops->mount(mnt_parent, rwflag, data)");
                        ret = mnt_parent->fs_ops->mount(mnt_parent, rwflag, data);
                        if (ret == RT_EOK)
                        {
                            DLOG(msg, type->fs_ops->name, "dfs", DLOG_MSG_RET, "mount OK, ret root_dentry");

                            mnt_child = mnt_parent;
                            DLOG(note_right, "mnt", "mount sucessfully");
                            DLOG(msg, "dfs", "mnt", DLOG_MSG, "dfs_mnt_insert(, mnt_child)");
                            dfs_mnt_insert(RT_NULL, mnt_child);

                            /* unref it, because the ref_count = 1 when create */
                            DLOG(msg, "dfs", "mnt", DLOG_MSG, "dfs_mnt_unref(mnt_parent)");
                            dfs_mnt_unref(mnt_parent);

                            /*
                             * About root mnt:
                             * There are two ref_count:
                             * 1. the gobal root reference.
                             * 1. the mnt->parent reference.
                             */
                        }
                        else
                        {
                            LOG_W("mount %s failed with file system type: %s", fullpath, type->fs_ops->name);
                            DLOG(msg, "dfs", "mnt", DLOG_MSG, "dfs_mnt_destroy(mnt_parent)");
                            dfs_mnt_destroy(mnt_parent);
                            mnt_parent = RT_NULL;
                            rt_set_errno(EPERM);
                            ret = -1;
                        }
                    }
                    else
                    {
                        LOG_W("no mount method on file system type: %s", type->fs_ops->name);
                        DLOG(msg, "dfs", "mnt", DLOG_MSG, "dfs_mnt_destroy(mnt_parent), no mount method");
                        dfs_mnt_destroy(mnt_parent);
                        mnt_parent = RT_NULL;
                        rt_set_errno(EIO);
                        ret = -1;
                    }
                }
                else
                {
                    LOG_E("create a mnt point failed.");
                    rt_set_errno(ENOMEM);
                    ret = -1;
                }
            }
            else if (strcmp(mnt_parent->fullpath, fullpath) != 0)
            {
                DLOG(msg, "dfs", "dentry", DLOG_MSG, "mntpoint_dentry = dfs_dentry_lookup(mnt_parent, %s, 0)", fullpath);
                mntpoint_dentry = dfs_dentry_lookup(mnt_parent, fullpath, 0);
                if (mntpoint_dentry)
                {
                    DLOG(msg, "dentry", "dfs", DLOG_MSG_RET, "dentry exist");
                    DLOG(msg, "dfs", "mnt", DLOG_MSG, "mnt_child = dfs_mnt_create(path)");
                    mnt_child = dfs_mnt_create(fullpath);
                    if (mnt_child)
                    {
                        LOG_D("create mnt point %p", mnt_child);

                        mnt_child->fs_ops = type->fs_ops;
                        mnt_child->dev_id = dev_id;

                        if (mnt_child->fs_ops->mount)
                        {
                            DLOG(msg, "dfs", type->fs_ops->name, DLOG_MSG, "root_dentry = fs_ops->mount(mnt_child, rwflag, data)");
                            ret = mnt_child->fs_ops->mount(mnt_child, rwflag, data);
                            if (ret == RT_EOK)
                            {
                                LOG_D("mount %s sucessfully", fullpath);
                                DLOG(msg, mnt_child->fs_ops->name, "dfs", DLOG_MSG_RET, "mount OK");

                                DLOG(msg, "dfs", "mnt", DLOG_MSG, "dfs_mnt_insert(mnt_parent, mnt_child)");
                                dfs_mnt_insert(mnt_parent, mnt_child);

                                /* unref it, because the ref_count = 1 when create */
                                DLOG(msg, "dfs", "mnt", DLOG_MSG, "dfs_mnt_unref(mnt_child)");
                                dfs_mnt_unref(mnt_child);
                            }
                            else
                            {
                                LOG_W("mount %s failed with file system type: %s", fullpath, type->fs_ops->name);
                                DLOG(msg, mnt_child->fs_ops->name, "dfs", DLOG_MSG_RET, "mount failed");
                                dfs_mnt_destroy(mnt_child);
                                rt_set_errno(EPERM);
                                ret = -1;
                            }
                        }
                        else
                        {
                            LOG_W("no mount method on file system type: %s", type->fs_ops->name);
                            dfs_mnt_destroy(mnt_child);
                            rt_set_errno(EIO);
                            ret = -1;
                        }
                    }
                    else
                    {
                        LOG_E("create a mnt point failed.");
                        rt_set_errno(ENOMEM);
                        ret = -1;
                    }
                    dfs_dentry_unref(mntpoint_dentry);
                }
                else
                {
                    LOG_W("no mount point (%s) in file system: %s", fullpath, mnt_parent->fullpath);
                    rt_set_errno(ENOTDIR);
                    ret = -1;
                }
            }
            else
            {
                LOG_E("mount point (%s) already mounted!", fullpath);
                rt_set_errno(EEXIST);
                ret = -1;
            }
        }
        else
        {
            LOG_E("No device found for this file system.");
            rt_set_errno(ENODEV);
            ret = -1;
        }
        rt_free(fullpath);
    }

    return ret;
}

int dfs_umount(const char *specialfile)
{
    int ret = -RT_ERROR;
    char *fullpath = RT_NULL;
    struct dfs_mnt *mnt = RT_NULL;

    fullpath = dfs_normalize_path(NULL, specialfile);
    if (fullpath)
    {
        DLOG(msg, "dfs", "mnt", DLOG_MSG, "mnt = dfs_mnt_lookup(%s)", fullpath);
        mnt = dfs_mnt_lookup(fullpath);
        if (mnt)
        {
            if (strcmp(mnt->fullpath, fullpath) == 0)
            {
                /* is the mount point */

                if (rt_atomic_load(&(mnt->ref_count)) == 1 && rt_list_isempty(&mnt->child))
                {
                    DLOG(msg, "dfs", mnt->fs_ops->name, DLOG_MSG, "fs_ops->umount(mnt)");
                    ret = mnt->fs_ops->umount(mnt);
                    if (ret == 0)
                    {
                        DLOG(msg, mnt->fs_ops->name, "dfs", DLOG_MSG_RET, "return OK");
                        /* destroy this mount point */
                        DLOG(msg, "dfs", "mnt", DLOG_MSG, "dfs_mnt_destroy(mnt)");
                        dfs_mnt_destroy(mnt);
                    }
                    else
                    {
                        LOG_E("umount file system: %s failed.", fullpath);
                    }
                }
                else
                {
                    LOG_E("the file system is busy!");
                }
            }
            else
            {
                LOG_E("the path:%s is not a mountpoint!", fullpath);
            }
        }
        else
        {
            LOG_E("no filesystem found.");
        }
        rt_free(fullpath);
    }
    else
    {
        rt_set_errno(-ENOTDIR);
    }

    return ret;
}

/* for compatibility */
int dfs_unmount(const char *specialfile)
{
    return dfs_umount(specialfile);
}

int dfs_mkfs(const char *fs_name, const char *device_name)
{
    rt_device_t dev_id = NULL;
    struct dfs_filesystem_type *type;
    int ret = -RT_ERROR;

    type = *_find_filesystem(fs_name);
    if (!type)
    {
        rt_kprintf("no file system: %s found!\n", fs_name);
        return ret;
    }
    else
    {
        if (type->fs_ops->flags & FS_NEED_DEVICE)
        {
            /* check device name, and it should not be NULL */
            if (device_name != NULL)
                dev_id = rt_device_find(device_name);

            if (dev_id == NULL)
            {
                rt_set_errno(-ENODEV);
                rt_kprintf("Device (%s) was not found", device_name);
                return ret;
            }
        }
        else
        {
            dev_id = RT_NULL;
        }
    }

    if (type->fs_ops->mkfs)
    {
        ret = type->fs_ops->mkfs(dev_id, type->fs_ops->name);
    }

    return ret;
}

int dfs_statfs(const char *path, struct statfs *buffer)
{
    struct dfs_mnt *mnt;
    char *fullpath;
    int ret = -RT_ERROR;

    fullpath = dfs_normalize_path(NULL, path);
    if (!fullpath)
    {
        return ret;
    }

    DLOG(msg, "dfs_file", "mnt", DLOG_MSG, "dfs_mnt_lookup(%s)", fullpath);
    mnt = dfs_mnt_lookup(fullpath);
    if (mnt)
    {
        if (mnt->fs_ops->statfs)
        {
            ret = mnt->fs_ops->statfs(mnt, buffer);
        }
    }

    return ret;
}

/**
 * this function will return the mounted path for specified device.
 *
 * @param device the device object which is mounted.
 *
 * @return the mounted path or NULL if none device mounted.
 */
const char *dfs_filesystem_get_mounted_path(struct rt_device *device)
{
    const char *path = NULL;

    return path;
}

/**
 * this function will fetch the partition table on specified buffer.
 *
 * @param part the returned partition structure.
 * @param buf the buffer contains partition table.
 * @param pindex the index of partition table to fetch.
 *
 * @return RT_EOK on successful or -RT_ERROR on failed.
 */
int dfs_filesystem_get_partition(struct dfs_partition *part,
                                 uint8_t *buf,
                                 uint32_t pindex)
{
#define DPT_ADDRESS     0x1be       /* device partition offset in Boot Sector */
#define DPT_ITEM_SIZE   16          /* partition item size */

    uint8_t *dpt;
    uint8_t type;

    RT_ASSERT(part != NULL);
    RT_ASSERT(buf != NULL);

    dpt = buf + DPT_ADDRESS + pindex * DPT_ITEM_SIZE;

    /* check if it is a valid partition table */
    if ((*dpt != 0x80) && (*dpt != 0x00))
        return -EIO;

    /* get partition type */
    type = *(dpt + 4);
    if (type == 0)
        return -EIO;

    /* set partition information
     *    size is the number of 512-Byte */
    part->type = type;
    part->offset = *(dpt + 8) | *(dpt + 9) << 8 | *(dpt + 10) << 16 | *(dpt + 11) << 24;
    part->size = *(dpt + 12) | *(dpt + 13) << 8 | *(dpt + 14) << 16 | *(dpt + 15) << 24;

    rt_kprintf("found part[%d], begin: %ld, size: ",
               pindex, part->offset * 512);
    if ((part->size >> 11) == 0)
        rt_kprintf("%ld%s", part->size >> 1, "KB\n"); /* KB */
    else
    {
        unsigned int part_size;
        part_size = part->size >> 11;                /* MB */
        if ((part_size >> 10) == 0)
            rt_kprintf("%d.%ld%s", part_size, (part->size >> 1) & 0x3FF, "MB\n");
        else
            rt_kprintf("%d.%d%s", part_size >> 10, part_size & 0x3FF, "GB\n");
    }

    return RT_EOK;
}

/* @} */
