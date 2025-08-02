/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
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

#ifdef RT_USING_PAGECACHE
#include "dfs_pcache.h"
#endif

#define DBG_TAG "DFS.fs"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct dfs_filesystem_type *file_systems = NULL;
extern rt_list_t _mnt_list;

/**
 * @addtogroup group_fs_api
 */
/*@{*/

/**
 * @brief Find a filesystem type by name
 *
 * This function searches the global filesystem type list for a filesystem
 * matching the given name. It returns a pointer to the pointer that holds
 * the matching filesystem type (or the end-of-list pointer if not found).
 *
 * @param[in] name The name of the filesystem type to find
 * @return struct dfs_filesystem_type** Pointer to the pointer containing
 *         the matching filesystem type, or the end-of-list pointer if not found
 */
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

/**
 * @brief Get the list of registered filesystem types
 *
 * This function returns a pointer to the head of the global filesystem type list.
 *
 * @return struct dfs_filesystem_type* Pointer to the head of the filesystem type list
 */
struct dfs_filesystem_type *dfs_filesystems(void)
{
    return file_systems;
}

/**
 * @brief Register a filesystem type
 *
 * This function registers a new filesystem type with the global filesystem type list.
 *
 * @param[in] fs Pointer to the filesystem type to register
 * @return int 0 on success, or a negative error code on failure
 */
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

/**
 * @brief Unregister a filesystem type
 *
 * This function unregisters a filesystem type from the global filesystem type list.
 *
 * @param[in] fs Pointer to the filesystem type to unregister
 * @return int 0 on success, or a negative error code on failure
 */
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

#define REMNT_UNSUPP_FLAGS (~(MS_REMOUNT | MS_RMT_MASK)) /* remount unsupported flags */

/**
 * @brief Remount a filesystem
 *
 * This function remounts a filesystem at the specified path with the given flags.
 *
 * @param[in] path The path of the filesystem to remount
 * @param[in] flags The remount flags (see MS_REMOUNT and MS_RMT_MASK)
 * @param[in] data Pointer to additional data required for remounting
 * @return int 0 on success, or a negative error code on failure
 */
int dfs_remount(const char *path, rt_ubase_t flags, void *data)
{
    int rc = 0;
    char *fullpath = RT_NULL;
    struct dfs_mnt *mnt = RT_NULL;

    if (flags & REMNT_UNSUPP_FLAGS)
    {
        return -EINVAL;
    }

    fullpath = dfs_normalize_path(RT_NULL, path);
    if (!fullpath)
    {
        rc = -ENOENT;
    }
    else
    {
        DLOG(msg, "dfs", "mnt", DLOG_MSG, "mnt = dfs_mnt_lookup(%s)", fullpath);
        mnt = dfs_mnt_lookup(fullpath);
        if (mnt)
        {
            dfs_lock();
            dfs_mnt_setflags(mnt, flags);
            dfs_unlock();
        }
        else
        {
            struct stat buf = {0};
            if (dfs_file_stat(fullpath, &buf) == 0 && S_ISBLK(buf.st_mode))
            {
                /* path was not already mounted on target */
                rc = -EINVAL;
            }
            else
            {
                /* path is not a directory */
                rc = -ENOTDIR;
            }
        }
    }

    return rc;
}

/*
 *    parent(mount path)
 *    mnt_parent <- - - - - - -  +
 *         |                     |
 *         |- mnt_child <- - - - - -+ (1 refcount)
 *                 |             |
 *                 |- parent - - + (1 refcount)
 */

/**
 * @brief Mount a filesystem at the specified path
 *
 * This function mounts a filesystem of the specified type at the given path with optional device.
 * It handles both root filesystem mounting and regular filesystem mounting scenarios.
 *
 * @param[in] device_name The name of the device to mount (optional)
 * @param[in] path The path of the mount point
 * @param[in] filesystemtype The type of the filesystem to mount
 * @param[in] rwflag The read/write flags (see MS_RDONLY, MS_RDWR, etc.)
 * @param[in] data Pointer to additional data required for mounting
 *
 * @return int RT_EOK on success, negative error code on failure:
 *             - EPERM: Path normalization failed or mount operation failed
 *             - ENODEV: Filesystem type not found or device not available
 *             - ENOMEM: Memory allocation failure
 *             - EIO: Filesystem lacks mount method
 *             - ENOTDIR: Mount point doesn't exist
 *             - EEXIST: Mount point already mounted
 *
 * @note Special handling for root filesystem ("/")
 * @note Automatic reference counting management for mount points
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

    /* normalize the mount path */
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
        rt_set_errno(ENODEV);
        ret = -1;
    }

    /* Main mounting procedure */
    if (fullpath)
    {
        DLOG(note, "mnt", "mount %s(%s) on path: %s", device_name, filesystemtype, fullpath);

        /* open specific device */
        if (device_name) dev_id = rt_device_find(device_name);

        /* Check device requirements */
        if (!(type->fs_ops->flags & FS_NEED_DEVICE) ||
            ((type->fs_ops->flags & FS_NEED_DEVICE) && dev_id))
        {
            DLOG(msg, "dfs", "mnt", DLOG_MSG, "mnt_parent = dfs_mnt_lookup(%s)", fullpath);
            mnt_parent = dfs_mnt_lookup(fullpath); /* Find parent mount point */

            /* Handle root filesystem mounting */
            if ((!mnt_parent && (strcmp(fullpath, "/") == 0 || strcmp(fullpath, "/dev") == 0))
                || (mnt_parent && strcmp(fullpath, "/") == 0 && strcmp(mnt_parent->fullpath, fullpath) != 0))
            {
                LOG_D("no mnt found @ mount point %s, should be root.", fullpath);
                DLOG(msg, "mnt", "dfs", DLOG_MSG_RET, "no mnt");

                /* it's the root file system */
                /* the mount point dentry is the same as root dentry. */
                /* Create root filesystem mount point */
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

                            /* Mark as mounted and insert into mount table */
                            mnt_child = mnt_parent;
                            mnt_child->flags |= MNT_IS_MOUNTED;

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
            else if (mnt_parent && (strcmp(mnt_parent->fullpath, fullpath) != 0)) /* Handle regular filesystem mounting */
            {
                DLOG(msg, "dfs", "dentry", DLOG_MSG, "mntpoint_dentry = dfs_dentry_lookup(mnt_parent, %s, 0)", fullpath);
                mntpoint_dentry = dfs_dentry_lookup(mnt_parent, fullpath, 0); /* Find mount point directory entry */
                if (mntpoint_dentry)
                {
                    DLOG(msg, "dentry", "dfs", DLOG_MSG_RET, "dentry exist");
                    DLOG(msg, "dfs", "mnt", DLOG_MSG, "mnt_child = dfs_mnt_create(path)");
                    mnt_child = dfs_mnt_create(fullpath); /* Create child mount point */
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
                                mnt_child->flags |= MNT_IS_MOUNTED;

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

/**
 * @brief Unmount a filesystem from the specified path
 *
 * This function unmounts a filesystem from the given path. It performs the following operations:
 * 1. Normalizes the target path
 * 2. Looks up the mount point
 * 3. Checks if the filesystem can be safely unmounted
 * 4. Performs cleanup operations if unmounting is successful
 *
 * @param[in] specialfile The path of the filesystem to unmount
 * @param[in] flags Unmount flags (MNT_FORCE for forced unmount)
 *
 * @return int RT_EOK on success, negative error code on failure:
 *             - EBUSY: Filesystem is busy (in use or has child mounts)
 *             - EINVAL: Path is not a mount point
 *             - ENOTDIR: Invalid path format
 *
 * @note Forced unmount (MNT_FORCE) can unmount even if reference count > 1
 * @note Automatically handles page cache cleanup if RT_USING_PAGECACHE is enabled
 * @note The function will fail if:
 *       - The mount point is locked (MNT_IS_LOCKED)
 *       - There are child mounts present
 *       - Reference count > 1 and MNT_FORCE not specified
 */
int dfs_umount(const char *specialfile, int flags)
{
    int ret = -1;
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
                rt_base_t ref_count = rt_atomic_load(&(mnt->ref_count));

                if (!(mnt->flags & MNT_IS_LOCKED) && rt_list_isempty(&mnt->child) && (ref_count == 1 || (flags & MNT_FORCE)))
                {
#ifdef RT_USING_PAGECACHE
                    dfs_pcache_unmount(mnt);
#endif
                    /* destroy this mount point */
                    DLOG(msg, "dfs", "mnt", DLOG_MSG, "dfs_mnt_destroy(mnt)");
                    ret = dfs_mnt_destroy(mnt);
                }
                else
                {
                    LOG_I("the file system is busy!");
                    ret = -EBUSY;
                }
            }
            else
            {
                LOG_I("the path:%s is not a mountpoint!", fullpath);
                ret = -EINVAL;
            }
        }
        else
        {
            LOG_I("no filesystem found.");
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
    return dfs_umount(specialfile, 0);
}

/**
 * @brief Check if a mount point is mounted
 *
 * This function checks if the given mount point is mounted. It returns 0 if the mount point is mounted,
 * and -1 otherwise.
 *
 * @param[in] mnt The mount point to check
 *
 * @return int 0 if mounted, -1 otherwise
 */
int dfs_is_mounted(struct dfs_mnt *mnt)
{
    int ret = 0;

    if (mnt && !(mnt->flags & MNT_IS_MOUNTED))
    {
        ret = -1;
    }

    return ret;
}

/**
 * @brief Create a filesystem on the specified device
 *
 * This function creates a filesystem of the specified type on the given device.
 * It performs the following operations:
 * 1. Looks up the filesystem type
 * 2. Validates device requirements
 * 3. Calls the filesystem-specific mkfs operation
 * 4. Handles page cache cleanup if successful (when RT_USING_PAGECACHE is enabled)
 *
 * @param[in] fs_name Name of the filesystem type to create (e.g., "elm", "romfs")
 * @param[in] device_name Name of the device to create filesystem on (optional)
 *
 * @return int RT_EOK on success, negative error code on failure:
 *             - RT_ERROR: General error
 *             - ENODEV: Filesystem type not found or device not available
 *
 * @note For filesystems that don't require a device (FS_NEED_DEVICE not set),
 *       the device_name parameter can be NULL
 * @note Automatically unmounts any existing filesystem on the device
 *       when RT_USING_PAGECACHE is enabled
 * @note The function will fail if:
 *       - The filesystem type is not found
 *       - Device is required but not found
 *       - The filesystem doesn't implement mkfs operation
 */
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
#ifdef RT_USING_PAGECACHE
        if (ret == RT_EOK)
        {
            struct dfs_mnt *mnt = RT_NULL;

            mnt = dfs_mnt_dev_lookup(dev_id);
            if (mnt)
            {
                dfs_pcache_unmount(mnt);
            }
        }
#endif
    }

    return ret;
}

/**
 * @brief Get filesystem statistics for the specified path
 *
 * This function retrieves filesystem statistics (like total/available space)
 * for the filesystem containing the given path. It performs the following operations:
 * 1. Normalizes the input path
 * 2. Looks up the mount point for the path
 * 3. Calls the filesystem-specific statfs operation if available
 *
 * @param[in] path The path to query filesystem statistics for
 * @param[out] buffer Pointer to statfs structure to store the results
 *
 * @return int RT_EOK on success, negative error code on failure:
 *             - RT_ERROR: General error (invalid path or filesystem not found)
 *
 * @note The function will fail if:
 *       - The path cannot be normalized
 *       - No mount point is found for the path
 *       - The filesystem doesn't implement statfs operation
 *       - The filesystem is not currently mounted
 * @note The buffer parameter must point to valid memory allocated by the caller
 */
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
            if (dfs_is_mounted(mnt) == 0)
            {
                ret = mnt->fs_ops->statfs(mnt, buffer);
            }
        }
    }

    return ret;
}

/**
 * this function will return the mounted path for specified device.
 *
 * @param[in] device the device object which is mounted.
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
 * @param[out] part the returned partition structure.
 * @param[in] buf the buffer contains partition table.
 * @param[in] pindex the index of partition table to fetch.
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