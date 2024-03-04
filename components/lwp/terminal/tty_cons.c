/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-11     Shell        init ver.
 */

#define DBG_TAG "lwp.tty"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "tty_config.h"
#include "tty_internal.h"
#include "bsd_porting.h"
#include "terminal.h"

#include <fcntl.h>

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops cons_rtdev_ops;
#endif

struct backend_entry
{
    rt_list_t bakend_list_node;
    int prio;

    rt_device_t bakdev;
};

static rt_list_t _bakend_list;

static void _bent_enqueue(struct backend_entry *bent)
{
    struct backend_entry *idx;
    rt_bool_t inserted = RT_FALSE;
    rt_list_for_each_entry(idx, &_bakend_list, bakend_list_node)
    {
        if (idx->prio < bent->prio)
        {
            rt_list_insert_before(&idx->bakend_list_node, &bent->bakend_list_node);
            inserted = RT_TRUE;
            break;
        }
    }

    if (!inserted)
        rt_list_insert_after(&_bakend_list, &bent->bakend_list_node);
    return ;
}

rt_err_t lwp_console_register_backend(struct rt_device *bakdev, int prio)
{
    rt_err_t ret = RT_EOK;
    struct backend_entry *bent;
    bent = rt_malloc(sizeof(struct backend_entry));
    if (bent)
    {
        rt_list_init(&bent->bakend_list_node);
        bent->prio = prio;
        bent->bakdev = bakdev;

        _bent_enqueue(bent);
    }
    else
    {
        ret = -RT_ENOMEM;
    }
    return ret;
}

static struct rt_device _cons_rtdev;

static int fops_open(struct dfs_file *file)
{
    return -EINVAL;
}

static struct dfs_file_ops _cons_fops = {
    .open = fops_open,
};

static rt_err_t _cons_readlink(struct rt_device *dev, char *buf, int len)
{
    int rc = -EIO;
    struct backend_entry *bent;
    if (!rt_list_isempty(&_bakend_list))
    {
        bent = rt_list_first_entry(&_bakend_list, struct backend_entry, bakend_list_node);
        if (bent)
        {
            RT_ASSERT(bent->bakdev);
            strncpy(buf, bent->bakdev->parent.name, MIN(len, RT_NAME_MAX));
            LOG_D("%s: backend device %s", __func__, buf);
            rc = 0;
        }
    }

    if (rc != 0)
    {
        LOG_W("%s: No backend device", __func__);
    }

    return rc;
}

static int _cons_init(void)
{
    rt_err_t rc;

    rt_list_init(&_bakend_list);

    /* setup system level device */
    _cons_rtdev.type = RT_Device_Class_Char;
    _cons_rtdev.ops = &cons_rtdev_ops;
    rc = rt_device_register(&_cons_rtdev, "console", RT_DEVICE_FLAG_DYNAMIC);
    if (rc == RT_EOK)
    {
        _cons_rtdev.readlink = &_cons_readlink;
        _cons_rtdev.fops = &_cons_fops;
    }

    return rc;
}
INIT_DEVICE_EXPORT(_cons_init);
