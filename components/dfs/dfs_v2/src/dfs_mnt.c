/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-05     Bernard      Implement mnt in dfs v2.0
 */

#include <rtthread.h>

#include "dfs.h"
#include "dfs_mnt.h"
#include "dfs_dentry.h"
#include "dfs_private.h"

#define DBG_TAG "DFS.mnt"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

static struct dfs_mnt *_root_mnt = RT_NULL;

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

/* remove mnt from mnt_tree */
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
 * this function will return the file system mounted on specified path.
 *
 * @param path the specified path string.
 *
 * @return the found file system or NULL if no file system mounted on
 * specified path
 */
struct dfs_mnt* dfs_mnt_lookup(const char* fullpath)
{
    struct dfs_mnt *mnt = _root_mnt;
    struct dfs_mnt *iter = RT_NULL;

    if (mnt)
    {
        dfs_lock();
        if (strncmp(mnt->fullpath, fullpath, strlen(fullpath))!= 0)
        {
            while (!rt_list_isempty(&mnt->child))
            {
                rt_list_for_each_entry(iter, &mnt->child, sibling)
                {
                    int mnt_len = rt_strlen(iter->fullpath);
                    if ((strncmp(iter->fullpath, fullpath, mnt_len) == 0) &&
                        ((fullpath[mnt_len] == '\0') ||
                        (fullpath[mnt_len] == '/')))
                    {
                        mnt = iter;
                        break;
                    }
                }

                if (mnt != iter) break;
            }
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

struct dfs_mnt* dfs_mnt_ref(struct dfs_mnt* mnt)
{
    if (mnt)
    {
        rt_atomic_add(&(mnt->ref_count), 1);
        DLOG(note, "mnt", "mnt(%s),ref_count=%d", mnt->fs_ops->name, rt_atomic_load(&(mnt->ref_count)));
    }

    return mnt;
}

int dfs_mnt_unref(struct dfs_mnt* mnt)
{
    rt_err_t ret = RT_EOK;

    if (mnt)
    {
        rt_atomic_sub(&(mnt->ref_count), 1);

        if (rt_atomic_load(&(mnt->ref_count)) == 0)
        {
            dfs_lock();

            if (mnt->flags & MNT_IS_UMOUNT)
            {
                mnt->fs_ops->umount(mnt);
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
 * @param device the device object which is mounted.
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

int dfs_mnt_foreach(struct dfs_mnt* (*func)(struct dfs_mnt *mnt, void *parameter), void *parameter)
{
    /* lock file system */
    dfs_lock();
    _dfs_mnt_foreach(_root_mnt, func, parameter);
    /* unlock file system */
    dfs_unlock();

    return 0;
}
