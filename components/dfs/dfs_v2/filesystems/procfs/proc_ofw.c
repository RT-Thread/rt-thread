/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <rthw.h>
#include <string.h>

#define DBG_TAG "proc.ofw"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/ofw.h>

#include "proc.h"

static ssize_t proc_ofw_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    struct proc_dentry *entry;
    const struct rt_ofw_prop *prop;
    rt_size_t remaining;

    if (!file || !pos || *pos < 0)
    {
        return -EINVAL;
    }

    if (count == 0)
    {
        return 0;
    }

    if (!buf)
    {
        return -EINVAL;
    }

    entry = (struct proc_dentry *)file->vnode->data;
    prop = entry ? (const struct rt_ofw_prop *)entry->data : RT_NULL;
    if (!prop || prop->length < 0)
    {
        return -EINVAL;
    }

    if ((rt_size_t)*pos >= (rt_size_t)prop->length)
    {
        return 0;
    }

    remaining = (rt_size_t)prop->length - (rt_size_t)*pos;
    if (count > remaining)
    {
        count = remaining;
    }

    if (count && !prop->value)
    {
        return -EINVAL;
    }

    rt_memcpy(buf, (const rt_uint8_t *)prop->value + *pos, count);
    *pos += count;

    return (ssize_t)count;
}

static const struct dfs_file_ops proc_ofw_file_ops =
{
    .read = proc_ofw_read,
    .lseek = generic_dfs_lseek,
};

static int proc_ofw_populate_node(const struct rt_ofw_node *node, struct proc_dentry *parent)
{
    struct rt_ofw_prop *prop;
    struct rt_ofw_node *child;
    struct proc_dentry *dentry;
    int ret = RT_EOK;

    for (prop = node->props; prop; prop = prop->next)
    {
        if (!prop->name || prop->length < 0)
        {
            return -RT_ERROR;
        }

        dentry = proc_create_data(prop->name, 0, parent, &proc_ofw_file_ops, prop);
        if (!dentry)
        {
            return -RT_ERROR;
        }

        dentry->size = (rt_size_t)prop->length;
        proc_release(dentry);
    }

    child = rt_ofw_get_next_child(node, RT_NULL);
    while (child)
    {
        const char *name = rt_ofw_node_full_name(child);

        if (!name || !name[0] || strchr(name, '/'))
        {
            rt_ofw_node_put(child);
            return -RT_ERROR;
        }

        dentry = proc_mkdir(name, parent);
        if (!dentry)
        {
            rt_ofw_node_put(child);
            return -RT_ERROR;
        }

        ret = proc_ofw_populate_node(child, dentry);
        proc_release(dentry);
        if (ret != RT_EOK)
        {
            rt_ofw_node_put(child);
            return ret;
        }

        child = rt_ofw_get_next_child(node, child);
    }

    return ret;
}

static int proc_ofw_init(void)
{
    struct rt_ofw_node *root;
    struct proc_dentry *dentry;
    int ret;

    root = rt_ofw_find_node_by_path("/");
    if (!root)
    {
        LOG_W("OFW tree is unavailable");
        return RT_EOK;
    }

    dentry = proc_mkdir("device-tree", RT_NULL);
    if (!dentry)
    {
        rt_ofw_node_put(root);
        LOG_E("failed to create /proc/device-tree");
        return -RT_ERROR;
    }

    ret = proc_ofw_populate_node(root, dentry);
    proc_release(dentry);
    rt_ofw_node_put(root);

    if (ret != RT_EOK)
    {
        LOG_E("failed to export the OFW tree through procfs");
    }

    return ret;
}
INIT_ENV_EXPORT(proc_ofw_init);
