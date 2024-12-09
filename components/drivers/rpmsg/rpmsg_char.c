/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rpmsg.char"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct rpmsg_char_ctrl;

struct rpmsg_char
{
    struct rt_device parent;
    rt_list_t list;

    struct rpmsg_char_ctrl *rchc;
    struct rt_rpmsg_endpoint *ept;

    rt_bool_t is_overwrite;
    struct rt_ringbuffer msg_ring;
    rt_uint8_t msg_pool[RT_RPMSG_CHAR_MSG_SIZE_MAX * RT_RPMSG_CHAR_MSG_MAX];
};

struct rpmsg_char_ctrl
{
    struct rt_device parent;

    struct rt_rpmsg_device *rdev;

    rt_list_t ept_nodes;
    rt_list_t del_ept_nodes;
    struct rt_spinlock lock;
    struct rt_work del_ept_work;
};

#define raw_to_rpmsg_char(raw)      rt_container_of(raw, struct rpmsg_char, parent)
#define raw_to_rpmsg_char_ctrl(raw) rt_container_of(raw, struct rpmsg_char_ctrl, parent)

static struct rt_dm_ida rpmsg_ept_ida = RT_DM_IDA_INIT(RPMSG_EPT);
static struct rt_dm_ida rpmsg_char_ida = RT_DM_IDA_INIT(RPMSG_CHAR);

static rt_err_t rpmsg_char_open(rt_device_t dev, rt_uint16_t oflag)
{
    rt_ubase_t level;
    rt_err_t err = RT_EOK;
    struct rpmsg_char_ctrl *rchc;
    struct rpmsg_char *this_rch = raw_to_rpmsg_char(dev), *rch, *rch_next;

    rchc = this_rch->rchc;

    level = rt_spin_lock_irqsave(&rchc->lock);

    rt_list_for_each_entry_safe(rch, rch_next, &rchc->del_ept_nodes, list)
    {
        if (rch == this_rch)
        {
            /* It's been cleaned. Don't open it. */
            err = -RT_EIO;
            break;
        }
    }

    rt_spin_unlock_irqrestore(&rchc->lock, level);

    return err;
}

static rt_ssize_t rpmsg_char_read(rt_device_t dev,
        rt_off_t pos, void *buffer, rt_size_t size)
{
    struct rpmsg_char *rch = raw_to_rpmsg_char(dev);

    return rt_ringbuffer_get(&rch->msg_ring, buffer, size);
}

static rt_ssize_t rpmsg_char_write(rt_device_t dev,
        rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct rpmsg_char *rch = raw_to_rpmsg_char(dev);

    return rt_rpmsg_send(rch->ept, buffer, size) ? : size;
}

static rt_err_t rpmsg_char_control(rt_device_t dev, int cmd, void *args)
{
    struct rpmsg_char *rch = raw_to_rpmsg_char(dev);

    if (cmd == RT_DEVICE_CTRL_RPMSG_DESTROY_EPT)
    {
        if (dev->ref_count == 1)
        {
            rt_ubase_t level;

            level = rt_spin_lock_irqsave(&rch->rchc->lock);
            rt_list_remove(&rch->list);
            rt_list_insert_before(&rch->rchc->del_ept_nodes, &rch->list);
            rt_spin_unlock_irqrestore(&rch->rchc->lock, level);

            rt_work_submit(&rch->rchc->del_ept_work, rt_thread_self()->remaining_tick);
        }

        return RT_EOK;
    }

    if (cmd == RT_DEVICE_CTRL_RPMSG_DATA_OVERWRITE)
    {
        rch->is_overwrite = !!args;

        return RT_EOK;
    }

    return -RT_EINVAL;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rpmsg_char_ops =
{
    .open = rpmsg_char_open,
    .read = rpmsg_char_read,
    .write = rpmsg_char_write,
    .control = rpmsg_char_control,
};
#endif

static rt_err_t rpmsg_char_rx_callback(struct rt_rpmsg_device *rdev,
        rt_uint32_t src, void *data, rt_size_t len)
{
    rt_size_t res_size;
    struct rpmsg_char *rch;
    struct rt_rpmsg_endpoint *ept;
    struct rt_rpmsg_endpoint_info info;

    RT_ASSERT(len <= RT_RPMSG_CHAR_MSG_SIZE_MAX);

    info.src = src;
    info.dst = RT_RPMSG_ADDR_ANY;
    info.name[0] = '\0';
    ept = rt_rpmsg_find_endpoint(rdev, &info);

    if (ept)
    {
        rch = ept->priv;

        if (rch->is_overwrite)
        {
            res_size = rt_ringbuffer_put_force(&rch->msg_ring, data, len);
        }
        else
        {
            res_size = rt_ringbuffer_put(&rch->msg_ring, data, len);
        }
    }
    else
    {
        return -RT_EINVAL;
    }

    return res_size ? RT_EOK : -RT_ENOMEM;
}

static void rpmsg_char_ctrl_del_ept_work(struct rt_work *work, void *work_data)
{
    rt_ubase_t level;
    rt_size_t clean_size = 0;
    struct rpmsg_char *rch, *rch_next;
    struct rpmsg_char_ctrl *rchc = work_data;

    level = rt_spin_lock_irqsave(&rchc->lock);

    rt_list_for_each_entry_safe(rch, rch_next, &rchc->del_ept_nodes, list)
    {
        if (rch->parent.open_flag == RT_DEVICE_OFLAG_CLOSE)
        {
            rt_spin_unlock_irqrestore(&rchc->lock, level);

            rt_rpmsg_destroy_endpoint(rchc->rdev, rch->ept);

            level = rt_spin_lock_irqsave(&rchc->lock);

            rt_list_remove(&rch->list);
            ++clean_size;
        }
    }

    rt_spin_unlock_irqrestore(&rchc->lock, level);

    if (!clean_size)
    {
        /* Try again */
        rt_work_submit(&rchc->del_ept_work, RT_TICK_PER_SECOND);
    }
}

static rt_err_t rpmsg_char_ctrl_control(rt_device_t dev, int cmd, void *args)
{
    struct rpmsg_char_ctrl *rchc = raw_to_rpmsg_char_ctrl(dev);

    if (cmd == RT_DEVICE_CTRL_RPMSG_CREATE_EPT && args)
    {
        int device_id;
        rt_ubase_t level;
        struct rpmsg_char *rch;
        struct rt_rpmsg_endpoint *ept;
        struct rt_rpmsg_endpoint_info *info = args;

        ept = rt_rpmsg_create_endpoint(rchc->rdev, info, &rpmsg_char_rx_callback);

        if (rt_is_err(ept))
        {
            return rt_ptr_err(ept);
        }

        rch = rt_calloc(1, sizeof(*rch));

        if (!rch)
        {
            rt_rpmsg_destroy_endpoint(rchc->rdev, ept);
            return -RT_ENOMEM;
        }

        if ((device_id = rt_dm_ida_alloc(&rpmsg_ept_ida)) < 0)
        {
            return -RT_EFULL;
        }

        ept->priv = rch;
        rch->ept = ept;
        rch->rchc = rchc;

        rch->parent.type = RT_Device_Class_Char;
    #ifdef RT_USING_DEVICE_OPS
        rch->parent.ops = &rpmsg_char_ops;
    #else
        rch->parent.read = rpmsg_char_read;
        rch->parent.write = rpmsg_char_write;
        rch->parent.control = rpmsg_char_control;
    #endif
        rch->parent.master_id = rpmsg_ept_ida.master_id;
        rch->parent.device_id = device_id;

        rt_ringbuffer_init(&rch->msg_ring, rch->msg_pool, sizeof(rch->msg_pool));
        rt_dm_dev_set_name(&rch->parent, "rpmsg_%ux%u", ept->info.src, ept->info.dst);

        rt_list_init(&rch->list);

        level = rt_spin_lock_irqsave(&rchc->lock);
        rt_list_insert_before(&rchc->ept_nodes, &rch->list);
        rt_spin_unlock_irqrestore(&rchc->lock, level);

        rt_device_register(&rch->parent, rt_dm_dev_get_name(&rch->parent),
                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE);
    }

    return -RT_EINVAL;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rpmsg_char_ctrl_ops =
{
    .control = rpmsg_char_ctrl_control,
};
#endif

static rt_err_t rpmsg_char_probe(struct rt_rpmsg_device *rdev)
{
    int device_id;
    struct rpmsg_char_ctrl *rchc = rt_calloc(1, sizeof(*rchc));

    if (!rchc)
    {
        return -RT_ENOMEM;
    }

    if ((device_id = rt_dm_ida_alloc(&rpmsg_char_ida)) < 0)
    {
        return -RT_EFULL;
    }

    rchc->rdev = rdev;
    rdev->parent.user_data = rchc;

    rt_list_init(&rchc->ept_nodes);
    rt_list_init(&rchc->del_ept_nodes);
    rt_spin_lock_init(&rchc->lock);
    rt_work_init(&rchc->del_ept_work, rpmsg_char_ctrl_del_ept_work, rchc);

    rt_dm_dev_set_name(&rchc->parent, "rpmsg_char%u", device_id);

    rchc->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    rchc->parent.ops = &rpmsg_char_ctrl_ops;
#else
    rchc->parent.control = rpmsg_char_control;
#endif
    rchc->parent.master_id = rpmsg_char_ida.master_id;
    rchc->parent.device_id = device_id;

    rt_device_register(&rchc->parent, rt_dm_dev_get_name(&rchc->parent),
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE);

    return RT_EOK;
}

static rt_err_t rpmsg_char_remove(struct rt_rpmsg_device *rdev)
{
    rt_ubase_t level;
    struct rpmsg_char *rch, *rch_next;
    struct rpmsg_char_ctrl *rchc = rdev->parent.user_data;

    level = rt_spin_lock_irqsave(&rchc->lock);

    rt_list_for_each_entry_safe(rch, rch_next, &rchc->ept_nodes, list)
    {
        rt_list_remove(&rch->list);

        rt_spin_unlock_irqrestore(&rchc->lock, level);

        rt_rpmsg_destroy_endpoint(rchc->rdev, rch->ept);
        rt_device_unregister(&rch->parent);
        rt_free(rch);

        level = rt_spin_lock_irqsave(&rchc->lock);
    }

    rt_list_for_each_entry_safe(rch, rch_next, &rchc->del_ept_nodes, list)
    {
        rt_list_remove(&rch->list);

        rt_spin_unlock_irqrestore(&rchc->lock, level);

        rt_rpmsg_destroy_endpoint(rchc->rdev, rch->ept);

        rt_dm_ida_free(&rpmsg_ept_ida, rch->parent.device_id);

        rt_device_unregister(&rch->parent);
        rt_free(rch);

        level = rt_spin_lock_irqsave(&rchc->lock);
    }

    rt_spin_unlock_irqrestore(&rchc->lock, level);

    rt_dm_ida_free(&rpmsg_char_ida, rchc->parent.device_id);

    rt_device_unregister(&rchc->parent);

    rt_free(rchc);

    return RT_EOK;
}

static struct rt_rpmsg_device_id rpmsg_char_ids[] =
{
    { .name = "rpmsg-char" },
    { /* sentinel */ }
};

static struct rt_rpmsg_driver rpmsg_char_driver =
{
    .parent.parent =
    {
        .name = "rpmsg-char",
    },
    .ids = rpmsg_char_ids,

    .probe = rpmsg_char_probe,
    .remove = rpmsg_char_remove,
};
RT_RPMSG_DRIVER_EXPORT(rpmsg_char_driver);
