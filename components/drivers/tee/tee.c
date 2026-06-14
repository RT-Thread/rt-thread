/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-23     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtdm.tee"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mm_page.h>

static struct rt_dm_ida tee_ida = RT_DM_IDA_INIT(TEE);

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops _tee_ops =
{
};
#endif

rt_err_t rt_tee_device_register(struct rt_tee_device *tdev)
{
    rt_err_t err;
    int device_id;
    const char *dev_name;

    if (!tdev || !tdev->ops)
    {
        return -RT_EINVAL;
    }

    if ((device_id = rt_dm_ida_alloc(&tee_ida)) < 0)
    {
        return -RT_EFULL;
    }

    rt_dm_dev_set_name(&tdev->parent, "tee%u", device_id);
    dev_name = rt_dm_dev_get_name(&tdev->parent);

    rt_list_init(&tdev->shm_nodes);
    rt_mutex_init(&tdev->mutex, dev_name, RT_IPC_FLAG_PRIO);

    /* Just make a search interface */
    tdev->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    tdev->parent.ops = tdev->parent.ops ? : &_tee_ops;
#endif
    tdev->parent.master_id = tee_ida.master_id;
    tdev->parent.device_id = device_id;

    if ((err = rt_device_register(&tdev->parent, dev_name, RT_DEVICE_FLAG_DEACTIVATE)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_dm_ida_free(&tee_ida, device_id);

    rt_mutex_detach(&tdev->mutex);

    return err;
}

rt_err_t rt_tee_device_unregister(struct rt_tee_device *tdev)
{
    rt_err_t err;
    struct rt_tee_shm *shm, *shm_next;

    if (!tdev)
    {
        return -RT_EINVAL;
    }

    if (tdev->parent.ref_count)
    {
        LOG_E("%s: there is %u user",
                rt_dm_dev_get_name(&tdev->parent), tdev->parent.ref_count);
        return -RT_EINVAL;
    }

    rt_mutex_take(&tdev->mutex, RT_WAITING_FOREVER);

    if (!rt_list_isempty(&tdev->shm_nodes))
    {
        LOG_W("%s: shm not unregister", rt_dm_dev_get_name(&tdev->parent));

        rt_list_for_each_entry_safe(shm, shm_next, &tdev->shm_nodes, list)
        {
            tdev->ops->shm_unregister(tdev, shm);
        }
    }

    rt_mutex_release(&tdev->mutex);

    rt_dm_ida_free(&tee_ida, tdev->parent.device_id);

    if (!(err = rt_device_unregister(&tdev->parent)))
    {
        rt_mutex_detach(&tdev->mutex);
    }

    return err;
}

rt_err_t rt_tee_get_version(struct rt_tee_device *tdev,
        struct rt_tee_version *out_version)
{
    rt_err_t err;

    if (!tdev || !out_version)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&tdev->mutex, RT_WAITING_FOREVER);

    err = tdev->ops->get_version(tdev, out_version);

    rt_mutex_release(&tdev->mutex);

    return err;
}

rt_err_t rt_tee_open_session(struct rt_tee_device *tdev,
        struct rt_tee_open_session_arg *arg)
{
    rt_err_t err;

    if (!tdev || !arg)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&tdev->mutex, RT_WAITING_FOREVER);

    err = tdev->ops->open_session(tdev, arg);

    rt_mutex_release(&tdev->mutex);

    return err;
}

rt_err_t rt_tee_close_session(struct rt_tee_device *tdev, rt_uint32_t session)
{
    rt_err_t err;

    if (!tdev)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&tdev->mutex, RT_WAITING_FOREVER);

    err = tdev->ops->close_session(tdev, session);

    rt_mutex_release(&tdev->mutex);

    return err;
}

rt_err_t rt_tee_invoke(struct rt_tee_device *tdev,
        struct rt_tee_invoke_arg *arg)
{
    rt_err_t err;

    if (!tdev || !arg)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&tdev->mutex, RT_WAITING_FOREVER);

    err = tdev->ops->invoke(tdev, arg);

    rt_mutex_release(&tdev->mutex);

    return err;
}

rt_err_t rt_tee_cancel(struct rt_tee_device *tdev,
        rt_uint32_t session, rt_uint32_t cancel_id)
{
    rt_err_t err;

    if (!tdev)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&tdev->mutex, RT_WAITING_FOREVER);

    err = tdev->ops->cancel(tdev, session, cancel_id);

    rt_mutex_release(&tdev->mutex);

    return err;
}

rt_err_t rt_tee_shm_alloc_helper(struct rt_tee_shm *shm)
{
    if (!shm || !shm->size)
    {
        return -RT_EINVAL;
    }

    if (shm->align && shm->align != ARCH_PAGE_SIZE)
    {
        shm->vaddr = rt_malloc_align(shm->size, shm->align);
    }
    else
    {
        shm->vaddr = rt_pages_alloc(rt_page_bits(shm->size));
    }

    if (!shm->vaddr)
    {
        return -RT_ENOMEM;
    }

    if (!shm->paddr)
    {
        shm->paddr = (rt_ubase_t)rt_kmem_v2p(shm->vaddr);
    }

    return RT_EOK;
}

rt_err_t rt_tee_shm_free_helper(struct rt_tee_shm *shm)
{
    if (!shm || !shm->size)
    {
        return -RT_EINVAL;
    }

    if (shm->align && shm->align != ARCH_PAGE_SIZE)
    {
        rt_free_align(shm->vaddr);
    }
    else
    {
        rt_pages_free(shm->vaddr, rt_page_bits(shm->size));
    }

    return RT_EOK;
}

rt_err_t rt_tee_shm_register(struct rt_tee_device *tdev, struct rt_tee_shm *shm)
{
    rt_err_t err;
    rt_bool_t allocated = RT_FALSE;

    if (!tdev || !shm || !shm->size)
    {
        return -RT_EINVAL;
    }

    if (shm->flags & TEE_SHM_USER)
    {
        if (!shm->vaddr)
        {
            return -RT_EINVAL;
        }

        if (!shm->paddr)
        {
            shm->paddr = (rt_ubase_t)rt_kmem_v2p(shm->vaddr);
        }
    }
    else if ((shm->flags & TEE_SHM_SYS) && (shm->flags & ~TEE_SHM_DRV))
    {
        if ((err = rt_tee_shm_alloc_helper(shm)))
        {
            return err;
        }
        allocated = RT_TRUE;
    }

    rt_mutex_take(&tdev->mutex, RT_WAITING_FOREVER);

    if (!(err = tdev->ops->shm_register(tdev, shm)))
    {
        rt_list_init(&shm->list);
        rt_list_insert_before(&tdev->shm_nodes, &shm->list);
    }

    rt_mutex_release(&tdev->mutex);

    if (err && allocated)
    {
        rt_tee_shm_free_helper(shm);
        shm->vaddr = RT_NULL;
        shm->paddr = 0;
    }

    return err;
}

rt_err_t rt_tee_shm_unregister(struct rt_tee_device *tdev, struct rt_tee_shm *shm)
{
    rt_err_t err;

    if (!tdev || !shm)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&tdev->mutex, RT_WAITING_FOREVER);

    if (!(err = tdev->ops->shm_unregister(tdev, shm)))
    {
        rt_list_remove(&shm->list);
    }

    rt_mutex_release(&tdev->mutex);

    return err;
}
