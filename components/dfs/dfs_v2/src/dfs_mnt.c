/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-05     Bernard      Implement mnt in dfs v2.0
 */

#include <rtthread.h>

#include "dfs_private.h"

#include <dfs.h>
#include <dfs_dentry.h>
#include <dfs_mnt.h>
#include <dfs_pcache.h>

#define DBG_TAG "DFS.mnt"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

static struct dfs_mnt *_root_mnt = RT_NULL;

RT_OBJECT_HOOKLIST_DEFINE(dfs_mnt_umnt);

/*
 * mnt tree structure
 *
 * mnt_root <----------------------------------------+
 *   | (child)                +----------+           |
 *   v          (sibling)     v          |           |
 *   mnt_child0     ->    mnt_child1     |           |
 *                            | (child)  |           |
 *                            v         / (parent)   | (root)
 *                            mnt_child10         ---/
 *
 */

 /**
 * @brief Create a new dfs_mnt structure instance.
 *
 * This function allocates memory to create a new dfs_mnt structure instance and initializes it.
 * If the memory allocation is successful, it copies the input path string into the instance and initializes related lists and flags.
 *
 * @param[in] path The path string to be mounted. This path information will be copied to the newly created dfs_mnt instance.
 *
 * @return If the memory allocation is successful, returns a pointer to the newly created dfs_mnt structure;
 *         if the memory allocation fails, returns RT_NULL.
 */
struct dfs_mnt *dfs_mnt_create(const char *path)
{
    struct dfs_mnt *mnt = rt_calloc(1, sizeof(struct dfs_mnt));
    if (mnt)
    {
        LOG_I("create mnt at %s", path);

        mnt->fullpath = rt_strdup(path);
        rt_list_init(&mnt->sibling);
        rt_list_init(&mnt->child);
        mnt->flags |= MNT_IS_ALLOCED;
        rt_atomic_store(&(mnt->ref_count), 1);
    }
    else
    {
        rt_set_errno(-ENOMEM);
    }

    return mnt;
}

/**
 * @brief Insert a child mount point into the mount tree.
 *
 * This function inserts a child mount point into the specified parent mount point's child list.
 * If the parent mount point is not provided, it will try to find the appropriate mount point based on the child's path.
 * If the child mount point is the root, it will update the global root mount point accordingly.
 *
 * @param[in,out] mnt Pointer to the parent dfs_mnt structure. If NULL, it will be updated to the appropriate mount point.
 * @param[in] child Pointer to the child dfs_mnt structure to be inserted.
 *
 * @return Always returns 0 to indicate success.
 */
int dfs_mnt_insert(struct dfs_mnt* mnt, struct dfs_mnt* child)
{
    if (child)
    {
        if (mnt == RT_NULL)
        {
            /* insert into root */
            mnt = dfs_mnt_lookup(child->fullpath);
            if (mnt == RT_NULL || (strcmp(child->fullpath, "/") == 0))
            {
                /* it's root mnt */
                mnt = child;
                mnt->flags |= MNT_IS_LOCKED;

                /* ref to gobal root */
                if (_root_mnt)
                {
                    child = _root_mnt;
                    rt_atomic_sub(&(_root_mnt->parent->ref_count), 1);
                    rt_atomic_sub(&(_root_mnt->ref_count), 1);
                    _root_mnt->flags &= ~MNT_IS_LOCKED;

                    _root_mnt = dfs_mnt_ref(mnt);
                    mnt->parent = dfs_mnt_ref(mnt);
                    mnt->flags |= MNT_IS_ADDLIST;

                    mkdir("/dev", 0777);
                }
                else
                {
                    _root_mnt = dfs_mnt_ref(mnt);
                }
            }
        }

        if (mnt)
        {
            child->flags |= MNT_IS_ADDLIST;
            if (child != mnt)
            {
                /* not the root, insert into the child list */
                rt_list_insert_before(&mnt->child, &child->sibling);
                /* child ref self */
                dfs_mnt_ref(child);
            }
            /* parent ref parent */
            child->parent = dfs_mnt_ref(mnt);
        }
    }

    return 0;
}

/**
 * @brief Remove a mount point from the mount tree.
 *
 * This function attempts to remove a specified mount point from the mount tree.
 * It can only remove a mount point if it has no child mount points. If the mount point
 * has children, it logs a warning message instead of performing the removal.
 *
 * @param[in] mnt Pointer to the dfs_mnt structure representing the mount point to be removed.
 *
 * @return Returns RT_EOK if the mount point is successfully removed.
 *         Returns -RT_ERROR if the mount point has child mount points and cannot be removed.
 */
int dfs_mnt_remove(struct dfs_mnt* mnt)
{
    int ret = -RT_ERROR;

    if (rt_list_isempty(&mnt->child))
    {
        rt_list_remove(&mnt->sibling);
        if (mnt->parent)
        {
            /* parent unref parent */
            rt_atomic_sub(&(mnt->parent->ref_count), 1);
        }

        ret = RT_EOK;
    }
    else
    {
        LOG_W("remove a mnt point:%s with child.", mnt->fullpath);
    }

    return ret;
}

/**
 * @brief Recursively search for a mount point associated with a specific device ID in the mount tree.
 *
 * This function traverses the mount tree starting from the given mount point `mnt` to find
 * a mount point that is associated with the specified device ID `dev_id`. It uses a depth-first
 * search algorithm to iterate through the child mount points.
 *
 * @param[in] mnt Pointer to the root dfs_mnt structure from which the search will start.
 * @param[in] dev_id Pointer to the device ID to search for.
 *
 * @return If a mount point associated with the given device ID is found, returns a pointer to the corresponding dfs_mnt structure.
 *         Otherwise, returns RT_NULL.
 */
static struct dfs_mnt *_dfs_mnt_dev_lookup(struct dfs_mnt *mnt, rt_device_t dev_id)
{
    struct dfs_mnt *ret = RT_NULL, *iter = RT_NULL;

    rt_list_for_each_entry(iter, &mnt->child, sibling)
    {
        if (iter->dev_id == dev_id)
        {
            ret = iter;
            break;
        }
        else
        {
            ret = _dfs_mnt_dev_lookup(iter, dev_id);
            if (ret)
            {
                break;
            }
        }
    }

    return ret;
}

/**
 * @brief Search for a mount point associated with a specific device ID in the mount tree.
 *
 * This function initiates a search for a mount point that is associated with the specified
 * device ID `dev_id` starting from the root mount point. It first checks the root mount point
 * directly, and if not found, it recursively searches the entire mount tree using the
 * internal helper function `_dfs_mnt_dev_lookup`.
 *
 * @param[in] dev_id Pointer to the device ID to search for.
 *
 * @return If a mount point associated with the given device ID is found, returns a pointer to the corresponding dfs_mnt structure.
 *         Otherwise, returns RT_NULL.
 */
struct dfs_mnt *dfs_mnt_dev_lookup(rt_device_t dev_id)
{
    struct dfs_mnt *mnt = _root_mnt;
    struct dfs_mnt *ret = RT_NULL;

    if (mnt)
    {
        dfs_lock();

        if (mnt->dev_id == dev_id)
        {
            dfs_unlock();
            return mnt;
        }

        ret = _dfs_mnt_dev_lookup(mnt, dev_id);

        dfs_unlock();
    }

    return ret;
}

/**
 * @brief Look up the mount point associated with a given full path.
 *
 * This function searches the mount tree starting from the root mount point to find
 * the most specific mount point that matches the given full path. It traverses down
 * the mount tree to identify the deepest mount point that is a prefix of the given path.
 *
 * @param[in] fullpath The full path string for which to find the associated mount point.
 *
 * @return If a matching mount point is found, returns a pointer to the corresponding dfs_mnt structure.
 *         Otherwise, returns RT_NULL.
 */
struct dfs_mnt *dfs_mnt_lookup(const char *fullpath)
{
    struct dfs_mnt *mnt = _root_mnt;
    struct dfs_mnt *iter = RT_NULL;

    if (mnt)
    {
        int mnt_len = rt_strlen(mnt->fullpath);

        dfs_lock();
        if ((strncmp(mnt->fullpath, fullpath, mnt_len) == 0) &&
            (mnt_len == 1 || (fullpath[mnt_len] == '\0') || (fullpath[mnt_len] == '/')))
        {
            while (!rt_list_isempty(&mnt->child))
            {
                rt_list_for_each_entry(iter, &mnt->child, sibling)
                {
                    mnt_len = rt_strlen(iter->fullpath);
                    if ((strncmp(iter->fullpath, fullpath, mnt_len) == 0) &&
                        ((fullpath[mnt_len] == '\0') || (fullpath[mnt_len] == '/')))
                    {
                        mnt = iter;
                        break;
                    }
                }

                if (mnt != iter) break;
            }
        }
        else
        {
            mnt = RT_NULL;
        }
        dfs_unlock();

        if (mnt)
        {
            LOG_D("mnt_lookup: %s path @ mount point %p", fullpath, mnt);
            DLOG(note, "mnt", "found mnt(%s)", mnt->fs_ops->name);
        }
    }

    return mnt;
}

/**
 * @brief Increase the reference count of a dfs_mnt structure instance.
 *
 * This function increments the reference count of the specified dfs_mnt structure.
 * The reference count is used to track how many parts of the system are currently
 * using this mount point.
 *
 * @param[in,out] mnt Pointer to the dfs_mnt structure whose reference count is to be increased.
 *                    If the pointer is valid, the reference count within the structure will be modified.
 * @return Returns the same pointer to the dfs_mnt structure that was passed in.
 *         If the input pointer is NULL, it simply returns NULL.
 */
struct dfs_mnt* dfs_mnt_ref(struct dfs_mnt* mnt)
{
    if (mnt)
    {
        rt_atomic_add(&(mnt->ref_count), 1);
        DLOG(note, "mnt", "mnt(%s),ref_count=%d", mnt->fs_ops->name, rt_atomic_load(&(mnt->ref_count)));
    }

    return mnt;
}

/**
 * @brief Decrease the reference count of a dfs_mnt structure instance and free it if necessary.
 *
 * This function decrements the reference count of the specified dfs_mnt structure.
 * If the reference count reaches zero after the decrement, it will perform the unmount operation,
 * trigger the unmount hook, free the allocated path memory, and finally free the dfs_mnt structure itself.
 *
 * @param[in,out] mnt Pointer to the dfs_mnt structure whose reference count is to be decreased.
 *                    If the reference count reaches zero, the structure will be freed.
 *
 * @return returns RT_EOK to indicate success.
 */
int dfs_mnt_unref(struct dfs_mnt *mnt)
{
    rt_err_t ret = RT_EOK;
    rt_base_t ref_count;

    if (mnt)
    {
        ref_count = rt_atomic_sub(&(mnt->ref_count), 1) - 1;

        if (ref_count == 0)
        {
            dfs_lock();

            if (mnt->flags & MNT_IS_UMOUNT)
            {
                mnt->fs_ops->umount(mnt);

                RT_OBJECT_HOOKLIST_CALL(dfs_mnt_umnt, (mnt));
            }

            /* free full path */
            rt_free(mnt->fullpath);
            mnt->fullpath = RT_NULL;

            /* destroy self and the ref_count should be 0 */
            DLOG(msg, "mnt", "mnt", DLOG_MSG, "free mnt(%s)", mnt->fs_ops->name);
            rt_free(mnt);

            dfs_unlock();
        }
        else
        {
            DLOG(note, "mnt", "mnt(%s),ref_count=%d", mnt->fs_ops->name, rt_atomic_load(&(mnt->ref_count)));
        }
    }

    return ret;
}

/**
 * @brief Set specific flags for a dfs_mnt structure instance.
 *
 * This function sets specific flags for the given dfs_mnt structure.
 * If the MS_RDONLY flag is included in the input flags, it sets the MNT_RDONLY flag
 * for the mount point and cleans the page cache if the page cache feature is enabled.
 *
 * @param[in,out] mnt Pointer to the dfs_mnt structure for which flags are to be set.
 *                    The structure's `flags` member will be modified if necessary.
 * @param[in] flags The flags to be set for the mount point. This includes the MS_RDONLY flag.
 *
 * @return returns 0 to indicate success.
 */
int dfs_mnt_setflags(struct dfs_mnt *mnt, int flags)
{
    int error = 0;

    if (flags & MS_RDONLY)
    {
        mnt->flags |= MNT_RDONLY;
#ifdef RT_USING_PAGECACHE
        dfs_pcache_clean(mnt);
#endif
    }

    return error;
}

/**
 * @brief Destroy a dfs_mnt structure instance and unmount it if necessary.
 *
 * This function attempts to destroy the specified dfs_mnt structure instance.
 * If the mount point is currently mounted, it marks the mount point as unmounted,
 * sets the unmount flag, and removes it from the mount list if it was added.
 * Finally, it decreases the reference count of the mount point and frees the
 * structure if the reference count reaches zero.
 *
 * @param[in,out] mnt Pointer to the dfs_mnt structure to be destroyed.
 *
 * @return Returns RT_EOK to indicate success.
 */
int dfs_mnt_destroy(struct dfs_mnt* mnt)
{
    rt_err_t ret = RT_EOK;

    if (mnt)
    {
        if (mnt->flags & MNT_IS_MOUNTED)
        {
            mnt->flags &= ~MNT_IS_MOUNTED;
            mnt->flags |= MNT_IS_UMOUNT;
            /* remote it from mnt list */
            if (mnt->flags & MNT_IS_ADDLIST)
            {
                dfs_mnt_remove(mnt);
            }
        }

        dfs_mnt_unref(mnt);
    }

    return ret;
}

/**
 * @brief Recursively traverse the mount point tree and apply a callback function.
 *
 * This function performs a depth-first traversal of the mount point tree starting from the given mount point.
 * It applies the specified callback function to each mount point in the tree. If the callback function returns
 * a non-NULL pointer, the traversal stops and the result is returned immediately.
 *
 * @param[in] mnt Pointer to the root dfs_mnt structure from which the traversal will start.
 *                If NULL, the function will return RT_NULL without performing any traversal.
 * @param[in] func Pointer to the callback function to be applied to each mount point.
 *                 The callback function takes a pointer to a dfs_mnt structure and a generic parameter,
 *                 and returns a pointer to a dfs_mnt structure or RT_NULL.
 * @param[in] parameter Generic pointer to a parameter that will be passed to the callback function.
 *
 * @return If the callback function returns a non-NULL pointer during the traversal, returns that pointer.
 *         Otherwise, returns RT_NULL.
 */
static struct dfs_mnt* _dfs_mnt_foreach(struct dfs_mnt *mnt, struct dfs_mnt* (*func)(struct dfs_mnt *mnt, void *parameter), void *parameter)
{
    struct dfs_mnt *iter, *ret = NULL;

    if (mnt)
    {
        ret = func(mnt, parameter);
        if (ret == RT_NULL)
        {
            if (!rt_list_isempty(&mnt->child))
            {
                /* for each in mount point list */
                rt_list_for_each_entry(iter, &mnt->child, sibling)
                {
                    ret = _dfs_mnt_foreach(iter, func, parameter);
                    if (ret != RT_NULL)
                    {
                        break;
                    }
                }
            }
        }
    }
    else
    {
        ret = RT_NULL;
    }

    return ret;
}

/**
 * @brief Compare a mount point's device ID with a given device object.
 *
 * This function checks if the device ID associated with a specified mount point
 * matches the given device object. If a match is found, it returns a pointer to
 * the corresponding dfs_mnt structure; otherwise, it returns RT_NULL.
 *
 * @param[in] mnt Pointer to the dfs_mnt structure representing the mount point to be checked.
 * @param[in] device Pointer to the device object to compare against the mount point's device ID.
 *
 * @return If the device ID of the mount point matches the given device object, returns a pointer to the dfs_mnt structure.
 *         Otherwise, returns RT_NULL.
 */
static struct dfs_mnt* _mnt_cmp_devid(struct dfs_mnt *mnt, void *device)
{
    struct dfs_mnt *ret = RT_NULL;
    struct rt_device *dev = (struct rt_device*)device;

    if (dev && mnt)
    {
        if (mnt->dev_id == dev)
        {
            ret = mnt;
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
const char *dfs_mnt_get_mounted_path(struct rt_device *device)
{
    const char* path = RT_NULL;

    if (_root_mnt)
    {
        struct dfs_mnt* mnt;

        dfs_lock();
        mnt = _dfs_mnt_foreach(_root_mnt, _mnt_cmp_devid, device);
        dfs_unlock();

        if (mnt) path = mnt->fullpath;
    }

    return path;
}

/**
 * @brief Print information about a mount point to the console.
 *
 * This function is designed to be used as a callback in the mount point tree traversal.
 * It prints the file system name, device name (or `(NULL)` if no device is associated),
 * mount path, and reference count of the specified mount point to the console using `rt_kprintf`.
 *
 * @param[in] mnt Pointer to the dfs_mnt structure representing the mount point to be printed.
 *                If NULL, the function does nothing.
 * @param[in] parameter A generic pointer to a parameter. This parameter is not used in this function.
 *
 * @return Always returns RT_NULL as it is a callback function mainly used for side - effects (printing).
 */
static struct dfs_mnt* _mnt_dump(struct dfs_mnt *mnt, void *parameter)
{
    if (mnt)
    {
        if (mnt->dev_id)
        {
            rt_kprintf("%-10s  %-6s  %-10s   %d\n",
                       mnt->fs_ops->name, mnt->dev_id->parent.name, mnt->fullpath, rt_atomic_load(&(mnt->ref_count)));
        }
        else
        {
            rt_kprintf("%-10s  (NULL)  %-10s   %d\n",
                       mnt->fs_ops->name, mnt->fullpath, rt_atomic_load(&(mnt->ref_count)));
        }
    }

    return RT_NULL;
}

/**
 * @brief Compare a mount point's full path with a given path.
 *
 * This function is designed to be used as a callback in the mount point tree traversal.
 * It compares the full path of the specified mount point with the given path.
 * If the mount point's full path starts with the given path, it returns a pointer to the dfs_mnt structure;
 * otherwise, it returns RT_NULL.
 *
 * @param[in] mnt Pointer to the dfs_mnt structure representing the mount point to be checked.
 *                If NULL, the function will not perform the comparison and return RT_NULL.
 * @param[in] parameter A generic pointer to a parameter, which should be cast to a `const char*`
 *                      representing the path to compare against the mount point's full path.
 *
 * @return If the mount point's full path starts with the given path, returns a pointer to the dfs_mnt structure.
 *         Otherwise, returns RT_NULL.
 */
static struct dfs_mnt* _mnt_cmp_path(struct dfs_mnt* mnt, void *parameter)
{
    const char* fullpath = (const char*)parameter;
    struct dfs_mnt *ret = RT_NULL;

    if (strncmp(mnt->fullpath, fullpath, rt_strlen(fullpath)) == 0)
    {
        ret = mnt;
    }

    return ret;
}

/**
 * @brief Check if a mount point has a child mount point matching the given path.
 *
 * This function checks whether the specified mount point has a child mount point
 * whose full path starts with the given path. It uses a depth-first traversal of
 * the mount point tree starting from the provided mount point and applies the
 * `_mnt_cmp_path` callback function to each mount point.
 *
 * @param[in] mnt Pointer to the root dfs_mnt structure from which the search will start.
 *                If NULL, the function will return RT_FALSE without performing any search.
 * @param[in] fullpath The full path string to compare against the child mount points' paths.
 *                     If NULL, the function will return RT_FALSE without performing any search.
 *
 * @return Returns RT_TRUE if a child mount point with a matching path is found.
 *         Returns RT_FALSE if no matching child mount point is found, or if either input parameter is NULL.
 */
rt_bool_t dfs_mnt_has_child_mnt(struct dfs_mnt *mnt, const char* fullpath)
{
    int ret = RT_FALSE;

    if (mnt && fullpath)
    {
        struct dfs_mnt *m = RT_NULL;

        dfs_lock();
        m = _dfs_mnt_foreach(mnt, _mnt_cmp_path, (void*)fullpath);
        dfs_unlock();

        if (m)
        {
            ret = RT_TRUE;
        }
    }

    return ret;
}

/**
 * @brief List all mount points starting from a specified mount point.
 *
 * This function lists information about all mount points in the mount point tree,
 * starting from the specified mount point. If the input mount point is NULL,
 * it starts from the root mount point. It uses the `_dfs_mnt_foreach` function
 * with the `_mnt_dump` callback to print mount point information.
 *
 * @param[in] mnt Pointer to the dfs_mnt structure from which to start listing mount points.
 *                If NULL, the function will start from the root mount point.
 *
 * @return Always returns 0 to indicate success.
 */
int dfs_mnt_list(struct dfs_mnt *mnt)
{
    if (!mnt) mnt = _root_mnt;

    /* lock file system */
    dfs_lock();
    _dfs_mnt_foreach(mnt, _mnt_dump, RT_NULL);
    /* unlock file system */
    dfs_unlock();

    return 0;
}

/**
 * @brief Traverse all mount points in the mount tree and apply a callback function.
 *
 * @param[in] func Pointer to the callback function to be applied to each mount point.
 *                 The callback function takes a pointer to a `dfs_mnt` structure and a generic parameter,
 *                 and returns a pointer to a `dfs_mnt` structure or `RT_NULL`.
 * @param[in] parameter Generic pointer to a parameter that will be passed to the callback function.
 *
 * @return Always returns 0.
 */
int dfs_mnt_foreach(struct dfs_mnt* (*func)(struct dfs_mnt *mnt, void *parameter), void *parameter)
{
    /* lock file system */
    dfs_lock();
    _dfs_mnt_foreach(_root_mnt, func, parameter);
    /* unlock file system */
    dfs_unlock();

    return 0;
}