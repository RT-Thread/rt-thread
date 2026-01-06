/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-05     Bernard      Implement vnode in dfs v2.0
 */

#include <dfs_file.h>
#include <dfs_mnt.h>
#ifdef RT_USING_PAGECACHE
#include "dfs_pcache.h"
#endif

#define DBG_TAG    "DFS.vnode"
#define DBG_LVL    DBG_WARNING
#include <rtdbg.h>

/**
 * @brief Initialize a virtual node (vnode) structure
 *
 * @param[in,out] vnode Pointer to the vnode to be initialized
 * @param[in] type Type of the vnode
 * @param[in] fops Pointer to file operations structure
 *
 * @return int Always returns 0 indicating success
 */
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

/**
 * @brief Create and initialize a new virtual node (vnode)
 *
 * @return struct dfs_vnode* Pointer to the newly created vnode, or NULL if creation failed
 */
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

/**
 * @brief Destroy a virtual node (vnode) and free its resources
 *
 * @param[in] vnode Pointer to the vnode to be destroyed
 *
 * @return int Always returns 0. Note that this does not guarantee success, as errors may occur internally.
 */
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
#ifdef RT_USING_PAGECACHE
                if (vnode->aspace)
                {
                    dfs_aspace_destroy(vnode->aspace);
                }
#endif
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

/**
 * @brief Increase reference count of a virtual node (vnode)
 *
 * @param[in,out] vnode Pointer to the vnode to be referenced
 *
 * @return struct dfs_vnode* The same vnode pointer that was passed in
 */
struct dfs_vnode *dfs_vnode_ref(struct dfs_vnode *vnode)
{
    if (vnode)
    {
        rt_atomic_add(&(vnode->ref_count), 1);

        DLOG(note, "vnode", "vnode ref_count=%d", rt_atomic_load(&(vnode->ref_count)));
    }

    return vnode;
}

/**
 * @brief Decrease reference count of a virtual node (vnode) and potentially free it
 *
 * @param[in,out] vnode Pointer to the vnode to be unreferenced
 */
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
#ifdef RT_USING_PAGECACHE
            if (vnode->aspace)
            {
                dfs_aspace_destroy(vnode->aspace);
            }
#endif
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
