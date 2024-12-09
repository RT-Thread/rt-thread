/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtdm.dma"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_list_t dmac_nodes = RT_LIST_OBJECT_INIT(dmac_nodes);
static struct rt_spinlock dmac_nodes_lock = {};

rt_err_t rt_dma_controller_register(struct rt_dma_controller *ctrl)
{
    const char *dev_name;
    char dma_name[RT_NAME_MAX];

    if (!ctrl || !ctrl->dev || !ctrl->ops)
    {
        return -RT_EINVAL;
    }

    dev_name = rt_dm_dev_get_name(ctrl->dev);

    if (rt_bitmap_next_set_bit(ctrl->dir_cap, 0, RT_DMA_DIR_MAX) == RT_DMA_DIR_MAX)
    {
        LOG_E("%s: Not direction capability", dev_name);

        return -RT_EINVAL;
    }

    rt_snprintf(dma_name, sizeof(dma_name), "%s-dmac", dev_name);

    rt_list_init(&ctrl->list);

    rt_spin_lock(&dmac_nodes_lock);
    rt_list_insert_before(&dmac_nodes, &ctrl->list);
    rt_spin_unlock(&dmac_nodes_lock);

    rt_list_init(&ctrl->channels_nodes);
    rt_mutex_init(&ctrl->mutex, dma_name, RT_IPC_FLAG_PRIO);

    if (ctrl->dev->ofw_node)
    {
        rt_dm_dev_bind_fwdata(ctrl->dev, RT_NULL, ctrl);
    }

    return RT_EOK;
}

rt_err_t rt_dma_controller_unregister(struct rt_dma_controller *ctrl)
{
    if (!ctrl)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&ctrl->mutex, RT_WAITING_FOREVER);

    if (!rt_list_isempty(&ctrl->channels_nodes))
    {
        rt_mutex_release(&ctrl->mutex);
        return -RT_EBUSY;
    }

    if (ctrl->dev->ofw_node)
    {
        rt_dm_dev_unbind_fwdata(ctrl->dev, RT_NULL);
    }

    rt_mutex_release(&ctrl->mutex);
    rt_mutex_detach(&ctrl->mutex);

    rt_spin_lock(&dmac_nodes_lock);
    rt_list_remove(&ctrl->list);
    rt_spin_unlock(&dmac_nodes_lock);

    return RT_EOK;
}

rt_err_t rt_dma_chan_start(struct rt_dma_chan *chan)
{
    rt_err_t err;
    struct rt_dma_controller *ctrl;

    if (!chan)
    {
        return -RT_EINVAL;
    }

    if (chan->prep_err)
    {
        LOG_D("%s: Not config done", rt_dm_dev_get_name(chan->slave));

        return chan->prep_err;
    }

    ctrl = chan->ctrl;

    rt_mutex_take(&ctrl->mutex, RT_WAITING_FOREVER);

    err = ctrl->ops->start(chan);

    rt_mutex_release(&ctrl->mutex);

    return err;
}

rt_err_t rt_dma_chan_stop(struct rt_dma_chan *chan)
{
    rt_err_t err;
    struct rt_dma_controller *ctrl;

    if (!chan)
    {
        return -RT_EINVAL;
    }

    if (chan->prep_err)
    {
        LOG_D("%s: Not prepare done", rt_dm_dev_get_name(chan->slave));

        return chan->prep_err;
    }

    ctrl = chan->ctrl;

    rt_mutex_take(&ctrl->mutex, RT_WAITING_FOREVER);

    err = ctrl->ops->stop(chan);

    rt_mutex_release(&ctrl->mutex);

    return err;
}

rt_err_t rt_dma_chan_config(struct rt_dma_chan *chan,
        struct rt_dma_slave_config *conf)
{
    rt_err_t err;
    struct rt_dma_controller *ctrl;
    enum rt_dma_transfer_direction dir;

    if (!chan || !conf)
    {
        err = -RT_EINVAL;
        goto _end;
    }

    dir = conf->direction;

    if (dir >= RT_DMA_DIR_MAX)
    {
        err = -RT_EINVAL;
        goto _end;
    }

    if (conf->src_addr_width >= RT_DMA_SLAVE_BUSWIDTH_BYTES_MAX ||
        conf->dst_addr_width >= RT_DMA_SLAVE_BUSWIDTH_BYTES_MAX)
    {
        err = -RT_EINVAL;
        goto _end;
    }

    ctrl = chan->ctrl;

    if (!rt_bitmap_test_bit(ctrl->dir_cap, dir))
    {
        err = -RT_ENOSYS;
        goto _end;
    }

    if (!chan->name && dir != RT_DMA_MEM_TO_MEM)
    {
        LOG_E("%s: illegal config for uname channels",
                rt_dm_dev_get_name(ctrl->dev));

        err = -RT_EINVAL;
        goto _end;
    }

    rt_mutex_take(&ctrl->mutex, RT_WAITING_FOREVER);

    err = ctrl->ops->config(chan, conf);

    rt_mutex_release(&ctrl->mutex);

    if (!err)
    {
        rt_memcpy(&chan->conf, conf, sizeof(*conf));
    }

_end:
    chan->conf_err = err;

    return err;
}

rt_err_t rt_dma_chan_done(struct rt_dma_chan *chan, rt_size_t size)
{
    if (!chan)
    {
        return -RT_EINVAL;
    }

    if (chan->callback)
    {
        chan->callback(chan, size);
    }

    return RT_EOK;
}

static rt_bool_t range_is_illegal(const char *name, const char *desc,
        rt_ubase_t addr0, rt_ubase_t addr1)
{
    rt_bool_t illegal = addr0 < addr1;

    if (illegal)
    {
        LOG_E("%s: %s %p is out of config %p", name, desc, addr0, addr1);
    }

    return illegal;
}

rt_err_t rt_dma_prep_memcpy(struct rt_dma_chan *chan,
        struct rt_dma_slave_transfer *transfer)
{
    rt_err_t err;
    rt_size_t len;
    rt_ubase_t dma_addr_src, dma_addr_dst;
    struct rt_dma_controller *ctrl;
    struct rt_dma_slave_config *conf;

    if (!chan || !transfer)
    {
        return -RT_EINVAL;
    }

    ctrl = chan->ctrl;
    conf = &chan->conf;

    if (chan->conf_err)
    {
        LOG_D("%s: Not config done", rt_dm_dev_get_name(chan->slave));

        return chan->conf_err;
    }

    RT_ASSERT(chan->conf.direction == RT_DMA_MEM_TO_MEM);
    dma_addr_src = transfer->src_addr;
    dma_addr_dst = transfer->dst_addr;
    len = transfer->buffer_len;

    if (range_is_illegal(rt_dm_dev_get_name(ctrl->dev), "source",
        dma_addr_src, conf->src_addr))
    {
        return -RT_EINVAL;
    }

    if (range_is_illegal(rt_dm_dev_get_name(ctrl->dev), "dest",
        dma_addr_dst, conf->dst_addr))
    {
        return -RT_EINVAL;
    }

    if (ctrl->ops->prep_memcpy)
    {
        rt_mutex_take(&ctrl->mutex, RT_WAITING_FOREVER);

        err = ctrl->ops->prep_memcpy(chan, dma_addr_dst, dma_addr_src, len);

        rt_mutex_release(&ctrl->mutex);
    }
    else
    {
        err = -RT_ENOSYS;
    }

    if (!err)
    {
        rt_memcpy(&chan->transfer, transfer, sizeof(*transfer));
    }

    chan->prep_err = err;

    return err;
}

rt_err_t rt_dma_prep_cyclic(struct rt_dma_chan *chan,
        struct rt_dma_slave_transfer *transfer)
{
    rt_err_t err;
    rt_ubase_t dma_buf_addr;
    struct rt_dma_controller *ctrl;
    struct rt_dma_slave_config *conf;
    enum rt_dma_transfer_direction dir;

    if (!chan || !transfer)
    {
        return -RT_EINVAL;
    }

    ctrl = chan->ctrl;
    conf = &chan->conf;

    if (chan->conf_err)
    {
        LOG_D("%s: Not config done", rt_dm_dev_get_name(chan->slave));

        return chan->conf_err;
    }

    dir = chan->conf.direction;

    if (dir == RT_DMA_MEM_TO_DEV || dir == RT_DMA_MEM_TO_MEM)
    {
        dma_buf_addr = transfer->src_addr;

        if (range_is_illegal(rt_dm_dev_get_name(ctrl->dev), "source",
            dma_buf_addr, conf->src_addr))
        {
            return -RT_EINVAL;
        }
    }
    else if (dir == RT_DMA_DEV_TO_MEM)
    {
        dma_buf_addr = transfer->dst_addr;

        if (range_is_illegal(rt_dm_dev_get_name(ctrl->dev), "dest",
            dma_buf_addr, conf->dst_addr))
        {
            return -RT_EINVAL;
        }
    }
    else
    {
        dma_buf_addr = ~0UL;
    }

    if (ctrl->ops->prep_cyclic)
    {
        rt_mutex_take(&ctrl->mutex, RT_WAITING_FOREVER);

        err = ctrl->ops->prep_cyclic(chan, dma_buf_addr,
                transfer->buffer_len, transfer->period_len, dir);

        rt_mutex_release(&ctrl->mutex);
    }
    else
    {
        err = -RT_ENOSYS;
    }

    if (!err)
    {
        rt_memcpy(&chan->transfer, transfer, sizeof(*transfer));
    }

    chan->prep_err = err;

    return err;
}

rt_err_t rt_dma_prep_single(struct rt_dma_chan *chan,
        struct rt_dma_slave_transfer *transfer)
{
    rt_err_t err;
    rt_ubase_t dma_buf_addr;
    struct rt_dma_controller *ctrl;
    struct rt_dma_slave_config *conf;
    enum rt_dma_transfer_direction dir;

    if (!chan || !transfer)
    {
        return -RT_EINVAL;
    }

    ctrl = chan->ctrl;
    conf = &chan->conf;

    if (chan->conf_err)
    {
        LOG_D("%s: Not config done", rt_dm_dev_get_name(chan->slave));

        return chan->conf_err;
    }

    dir = chan->conf.direction;

    if (dir == RT_DMA_MEM_TO_DEV || dir == RT_DMA_MEM_TO_MEM)
    {
        dma_buf_addr = transfer->src_addr;

        if (range_is_illegal(rt_dm_dev_get_name(ctrl->dev), "source",
            dma_buf_addr, conf->src_addr))
        {
            return -RT_EINVAL;
        }
    }
    else if (dir == RT_DMA_DEV_TO_MEM)
    {
        dma_buf_addr = transfer->dst_addr;

        if (range_is_illegal(rt_dm_dev_get_name(ctrl->dev), "dest",
            dma_buf_addr, conf->dst_addr))
        {
            return -RT_EINVAL;
        }
    }
    else
    {
        dma_buf_addr = ~0UL;
    }

    if (ctrl->ops->prep_single)
    {
        rt_mutex_take(&ctrl->mutex, RT_WAITING_FOREVER);

        err = ctrl->ops->prep_single(chan, dma_buf_addr,
                transfer->buffer_len, dir);

        rt_mutex_release(&ctrl->mutex);
    }
    else
    {
        err = -RT_ENOSYS;
    }

    if (!err)
    {
        rt_memcpy(&chan->transfer, transfer, sizeof(*transfer));
    }

    chan->prep_err = err;

    return err;
}

static struct rt_dma_controller *ofw_find_dma_controller(struct rt_device *dev,
        const char *name, struct rt_ofw_cell_args *args)
{
    struct rt_dma_controller *ctrl = RT_NULL;
#ifdef RT_USING_OFW
    int index;
    struct rt_ofw_node *np = dev->ofw_node, *ctrl_np;

    if (!np)
    {
        return RT_NULL;
    }

    index = rt_ofw_prop_index_of_string(np, "dma-names", name);

    if (index < 0)
    {
        return RT_NULL;
    }

    if (!rt_ofw_parse_phandle_cells(np, "dmas", "#dma-cells", index, args))
    {
        ctrl_np = args->data;

        if (!rt_ofw_data(ctrl_np))
        {
            rt_platform_ofw_request(ctrl_np);
        }

        ctrl = rt_ofw_data(ctrl_np);
        rt_ofw_node_put(ctrl_np);
    }
#endif /* RT_USING_OFW */
    return ctrl;
}

struct rt_dma_chan *rt_dma_chan_request(struct rt_device *dev, const char *name)
{
    void *fw_data = RT_NULL;
    struct rt_dma_chan *chan;
    struct rt_ofw_cell_args dma_args;
    struct rt_dma_controller *ctrl = RT_NULL;

    if (!dev)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

    if (name)
    {
        fw_data = &dma_args;
        ctrl = ofw_find_dma_controller(dev, name, &dma_args);
    }
    else
    {
        struct rt_dma_controller *ctrl_tmp;

        rt_spin_lock(&dmac_nodes_lock);
        rt_list_for_each_entry(ctrl_tmp, &dmac_nodes, list)
        {
            /* Only memory to memory for uname request */
            if (rt_bitmap_test_bit(ctrl_tmp->dir_cap, RT_DMA_MEM_TO_MEM))
            {
                ctrl = ctrl_tmp;
                break;
            }
        }
        rt_spin_unlock(&dmac_nodes_lock);
    }

    if (rt_is_err_or_null(ctrl))
    {
        return ctrl ? ctrl : rt_err_ptr(-RT_ENOSYS);
    }

    if (ctrl->ops->request_chan)
    {
        chan = ctrl->ops->request_chan(ctrl, dev, fw_data);
    }
    else
    {
        chan = rt_calloc(1, sizeof(*chan));

        if (!chan)
        {
            chan = rt_err_ptr(-RT_ENOMEM);
        }
    }

    if (rt_is_err(chan))
    {
        return chan;
    }

    if (!chan)
    {
        LOG_E("%s: unset request channels error", rt_dm_dev_get_name(ctrl->dev));

        return rt_err_ptr(-RT_ERROR);
    }

    chan->name = name;
    chan->ctrl = ctrl;
    chan->slave = dev;

    rt_list_init(&chan->list);
    chan->conf_err = -RT_ERROR;
    chan->prep_err = -RT_ERROR;

    rt_mutex_take(&ctrl->mutex, RT_WAITING_FOREVER);
    rt_list_insert_before(&ctrl->channels_nodes, &chan->list);
    rt_mutex_release(&ctrl->mutex);

    return chan;
}

rt_err_t rt_dma_chan_release(struct rt_dma_chan *chan)
{
    rt_err_t err = RT_EOK;

    if (!chan)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&chan->ctrl->mutex, RT_WAITING_FOREVER);
    rt_list_remove(&chan->list);
    rt_mutex_release(&chan->ctrl->mutex);

    if (chan->ctrl->ops->release_chan)
    {
        err = chan->ctrl->ops->release_chan(chan);
    }
    else
    {
        rt_free(chan);
    }

    return err;
}
