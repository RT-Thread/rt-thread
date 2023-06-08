/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-05     Bernard      Implement vnode in dfs v2.0
 */

#include <dfs_file.h>
#include <dfs_mnt.h>

#define DBG_TAG    "DFS.vnode"
#define DBG_LVL    DBG_WARNING
#include <rtdbg.h>

int dfs_vnode_init(struct dfs_vnode *vnode, int type, const struct dfs_file_ops *fops)
{
    if (vnode)
    {
        rt_memset(vnode, 0, sizeof(struct dfs_vnode));

        vnode->type = type;
        rt_atomic_store(&(vnode->ref_count), 1);
        vnode->mnt = RT_NULL;
        vnode->fops = fops;
    }

    return 0;
}

struct dfs_vnode *dfs_vnode_create(void)
{
    struct dfs_vnode *vnode = rt_calloc(1, sizeof(struct dfs_vnode));
    if (!vnode)
    {
        LOG_E("create a vnode failed.");
        return RT_NULL;
    }

    rt_atomic_store(&(vnode->ref_count), 1);

    LOG_I("create a vnode: %p", vnode);

    return vnode;
}

int dfs_vnode_destroy(struct dfs_vnode* vnode)
{
    rt_err_t ret = RT_EOK;

    if (vnode)
    {
        ret = dfs_file_lock();
        if (ret == RT_EOK)
        {
            if (rt_atomic_load(&(vnode->ref_count)) == 1)
            {
                LOG_I("free a vnode: %p", vnode);

                if (vnode->mnt)
                {
                    DLOG(msg, "vnode", vnode->mnt->fs_ops->name, DLOG_MSG, "fs_ops->free_vnode");
                    vnode->mnt->fs_ops->free_vnode(vnode);
                }
                else
                {
                    DLOG(msg, "vnode", "vnode", DLOG_MSG, "destroy vnode(mnt=NULL)");
                }

                dfs_file_unlock();

                rt_free(vnode);
            }
            else
            {
                dfs_file_unlock();
            }
        }
    }

    return 0;
}

struct dfs_vnode *dfs_vnode_ref(struct dfs_vnode *vnode)
{
    if (vnode)
    {
        rt_atomic_add(&(vnode->ref_count), 1);

        DLOG(note, "vnode", "vnode ref_count=%d", rt_atomic_load(&(vnode->ref_count)));
    }

    return vnode;
}

void dfs_vnode_unref(struct dfs_vnode *vnode)
{
    rt_err_t ret = RT_EOK;

    if (vnode)
    {
        ret = dfs_file_lock();
        if (ret == RT_EOK)
        {
            rt_atomic_sub(&(vnode->ref_count), 1);
            DLOG(note, "vnode", "vnode ref_count=%d", rt_atomic_load(&(vnode->ref_count)));

            if (rt_atomic_load(&(vnode->ref_count)) == 0)
            {
                LOG_I("free a vnode: %p", vnode);
                DLOG(msg, "vnode", "vnode", DLOG_MSG, "free vnode, ref_count=0");

                if (vnode->mnt)
                {
                    DLOG(msg, "vnode", vnode->mnt->fs_ops->name, DLOG_MSG, "fs_ops->free_vnode");
                    vnode->mnt->fs_ops->free_vnode(vnode);
                }

                dfs_file_unlock();

                rt_free(vnode);
            }
            else
            {
                dfs_file_unlock();
                DLOG(note, "vnode", "vnode ref_count=%d", rt_atomic_load(&(vnode->ref_count)));
            }
        }
    }

    return;
}
