/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

/**
 * @file dma.c
 * @brief DMA (Direct Memory Access) controller framework core API
 *
 * Provides a unified interface for DMA controller management, channel
 * lifecycle, transfer configuration, and transfer preparation (memcpy,
 * cyclic, single). Controllers register themselves via
 * rt_dma_controller_register(), and slave devices request channels
 * via rt_dma_chan_request().
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtdm.dma"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/** @brief Global list of registered DMA controllers */
static rt_list_t dmac_nodes = RT_LIST_OBJECT_INIT(dmac_nodes);
static RT_DEFINE_SPINLOCK(dmac_nodes_lock);

/**
 * @brief Acquire the DMA controller mutex lock
 *
 * Only acquires the lock in thread context (not ISR) since mutex
 * operations are not ISR-safe.
 *
 * @param[in] ctrl  DMA controller to lock
 */
static void dma_lock(struct rt_dma_controller *ctrl)
{
    if (rt_thread_self())
    {
        rt_mutex_take(&ctrl->mutex, RT_WAITING_FOREVER);
    }
}

/**
 * @brief Release the DMA controller mutex lock
 *
 * @param[in] ctrl  DMA controller to unlock
 */
static void dma_unlock(struct rt_dma_controller *ctrl)
{
    if (rt_thread_self())
    {
        rt_mutex_release(&ctrl->mutex);
    }
}

/**
 * @brief Register a DMA controller with the framework
 *
 * Validates that the controller has valid dev and ops pointers, and
 * that at least one direction capability is set. The controller is
 * added to the global dmac_nodes list for later channel allocation.
 * If the device has a device tree node, firmware data is bound.
 *
 * @param[in] ctrl  DMA controller to register
 *
 * @return RT_EOK on success, -RT_EINVAL if ctrl, dev, or ops are NULL
 *         or no direction capability is set
 */
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

/**
 * @brief Unregister a DMA controller from the framework
 *
 * Fails with -RT_EBUSY if any channels are still active.
 * Unbinds firmware data if device tree was used, detaches the mutex,
 * and removes the controller from the global list.
 *
 * @param[in] ctrl  DMA controller to unregister
 *
 * @return RT_EOK on success, -RT_EINVAL if ctrl is NULL,
 *         -RT_EBUSY if channels are still open
 */
rt_err_t rt_dma_controller_unregister(struct rt_dma_controller *ctrl)
{
    if (!ctrl)
    {
        return -RT_EINVAL;
    }

    dma_lock(ctrl);

    if (!rt_list_isempty(&ctrl->channels_nodes))
    {
        dma_unlock(ctrl);
        return -RT_EBUSY;
    }

    if (ctrl->dev->ofw_node)
    {
        rt_dm_dev_unbind_fwdata(ctrl->dev, RT_NULL);
    }

    dma_unlock(ctrl);
    rt_mutex_detach(&ctrl->mutex);

    rt_spin_lock(&dmac_nodes_lock);
    rt_list_remove(&ctrl->list);
    rt_spin_unlock(&dmac_nodes_lock);

    return RT_EOK;
}

/**
 * @brief Start a DMA transfer on a channel
 *
 * The channel must have been successfully prepared (no prep_err).
 *
 * @param[in] chan  DMA channel to start
 *
 * @return RT_EOK on success, -RT_EINVAL if chan is NULL,
 *         or the last preparation error code
 */
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

    dma_lock(ctrl);

    err = ctrl->ops->start(chan);

    dma_unlock(ctrl);

    return err;
}

/**
 * @brief Pause a DMA transfer on a channel
 *
 * If the controller does not support pause, falls back to stop.
 *
 * @param[in] chan  DMA channel to pause
 *
 * @return RT_EOK on success, -RT_EINVAL if chan is NULL,
 *         or the last preparation error code
 */
rt_err_t rt_dma_chan_pause(struct rt_dma_chan *chan)
{
    rt_err_t err;
    struct rt_dma_controller *ctrl;

    if (!chan)
    {
        return -RT_EINVAL;
    }

    if (!chan->ctrl->ops->pause)
    {
        LOG_D("%s: No pause, try stop", rt_dm_dev_get_name(chan->ctrl->dev));
        return rt_dma_chan_stop(chan);
    }

    if (chan->prep_err)
    {
        LOG_D("%s: Not config done", rt_dm_dev_get_name(chan->slave));

        return chan->prep_err;
    }

    ctrl = chan->ctrl;

    dma_lock(ctrl);

    err = ctrl->ops->pause(chan);

    dma_unlock(ctrl);

    return err;
}

/**
 * @brief Stop a DMA transfer on a channel
 *
 * @param[in] chan  DMA channel to stop
 *
 * @return RT_EOK on success, -RT_EINVAL if chan is NULL,
 *         or the last preparation error code
 */
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

    dma_lock(ctrl);

    err = ctrl->ops->stop(chan);

    dma_unlock(ctrl);

    return err;
}

/**
 * @brief Configure a DMA channel with slave-specific settings
 *
 * Validates direction, address width, and that the controller supports
 * the requested direction. Saves the configuration to chan->conf on success.
 *
 * @param[in] chan  DMA channel to configure
 * @param[in] conf  Slave configuration (direction, address widths, maxburst,
 *                  source/destination addresses)
 *
 * @return RT_EOK on success, -RT_EINVAL on invalid parameters,
 *         -RT_ENOSYS if direction not supported
 */
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

    dma_lock(ctrl);

    err = ctrl->ops->config(chan, conf);

    dma_unlock(ctrl);

    if (!err)
    {
        rt_memcpy(&chan->conf, conf, sizeof(*conf));
    }

_end:
    chan->conf_err = err;

    return err;
}

/**
 * @brief Signal transfer completion on a DMA channel
 *
 * Calls the channel's registered callback with the transfer size.
 * The controller driver calls this from its ISR when a transfer completes.
 *
 * @param[in] chan  DMA channel that completed
 * @param[in] size  Number of bytes transferred (0 indicates an error)
 *
 * @return RT_EOK on success, -RT_EINVAL if chan is NULL
 */
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

/**
 * @brief Check if an address falls below the configured boundary
 *
 * @param[in] name   Controller name for error logging
 * @param[in] desc   Description of the address (e.g., "source", "dest")
 * @param[in] addr0  Configured address
 * @param[in] addr1  Transfer address to validate
 *
 * @return RT_TRUE if addr0 is below addr1 (illegal), RT_FALSE otherwise
 */
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

/**
 * @brief Check if an address is within the controller's address mask
 *
 * @param[in] name   Controller name for error logging
 * @param[in] desc   Description of the address (e.g., "source", "dest")
 * @param[in] mask   Controller's address mask
 * @param[in] addr   Address to validate
 *
 * @return RT_TRUE if any bits outside the mask are set (unsupported), RT_FALSE otherwise
 */
static rt_bool_t addr_is_supported(const char *name, const char *desc,
                                   rt_uint64_t mask, rt_ubase_t addr)
{
    rt_bool_t illegal = !!(addr & ~mask);

    if (illegal)
    {
        LOG_E("%s: %s %p is out of mask %p", name, desc, addr, mask);
    }

    return illegal;
}

/**
 * @brief Prepare a memory-to-memory DMA transfer
 *
 * Validates source and destination addresses against the controller's
 * address mask and the configured boundary ranges.
 *
 * @param[in] chan      DMA channel (must be configured for RT_DMA_MEM_TO_MEM)
 * @param[in] transfer  Transfer descriptor (src_addr, dst_addr, buffer_len)
 *
 * @return RT_EOK on success, -RT_EINVAL on invalid parameters or address
 *         range violations, -RT_ENOSYS if prep_memcpy not supported
 */
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

    if (addr_is_supported(rt_dm_dev_get_name(ctrl->dev), "source",
                          ctrl->addr_mask, conf->src_addr))
    {
        return -RT_ENOSYS;
    }

    if (addr_is_supported(rt_dm_dev_get_name(ctrl->dev), "dest",
                          ctrl->addr_mask, conf->dst_addr))
    {
        return -RT_ENOSYS;
    }

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
        dma_lock(ctrl);

        err = ctrl->ops->prep_memcpy(chan, dma_addr_src, dma_addr_dst, len);

        dma_unlock(ctrl);
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

/**
 * @brief Prepare a cyclic (repeating) DMA transfer
 *
 * Cyclic transfers repeat automatically, useful for audio, ADC/DAC
 * streaming, and other periodic data transfers. The buffer is divided
 * into periods; each period completion triggers a callback.
 *
 * @param[in] chan      DMA channel
 * @param[in] transfer  Transfer descriptor with buffer details and period_len
 *
 * @return RT_EOK on success, -RT_EINVAL on invalid parameters,
 *         -RT_ENOSYS if prep_cyclic not supported
 */
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

        if (addr_is_supported(rt_dm_dev_get_name(ctrl->dev), "source",
                              ctrl->addr_mask, conf->src_addr))
        {
            return -RT_ENOSYS;
        }

        if (range_is_illegal(rt_dm_dev_get_name(ctrl->dev), "source",
                             dma_buf_addr, conf->src_addr))
        {
            return -RT_EINVAL;
        }
    }
    else if (dir == RT_DMA_DEV_TO_MEM)
    {
        dma_buf_addr = transfer->dst_addr;

        if (addr_is_supported(rt_dm_dev_get_name(ctrl->dev), "dest",
                              ctrl->addr_mask, conf->dst_addr))
        {
            return -RT_ENOSYS;
        }

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
        dma_lock(ctrl);

        err = ctrl->ops->prep_cyclic(chan, dma_buf_addr,
                                     transfer->buffer_len, transfer->period_len, dir);

        dma_unlock(ctrl);
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

/**
 * @brief Prepare a single (one-shot) DMA transfer
 *
 * Used for simple device-to-memory or memory-to-device transfers
 * that are not repeating.
 *
 * @param[in] chan      DMA channel
 * @param[in] transfer  Transfer descriptor (src_addr or dst_addr, buffer_len)
 *
 * @return RT_EOK on success, -RT_EINVAL on invalid parameters,
 *         -RT_ENOSYS if prep_single not supported
 */
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

        if (addr_is_supported(rt_dm_dev_get_name(ctrl->dev), "source",
                              ctrl->addr_mask, conf->src_addr))
        {
            return -RT_ENOSYS;
        }

        if (range_is_illegal(rt_dm_dev_get_name(ctrl->dev), "source",
                             dma_buf_addr, conf->src_addr))
        {
            return -RT_EINVAL;
        }
    }
    else if (dir == RT_DMA_DEV_TO_MEM)
    {
        dma_buf_addr = transfer->dst_addr;

        if (addr_is_supported(rt_dm_dev_get_name(ctrl->dev), "dest",
                              ctrl->addr_mask, conf->dst_addr))
        {
            return -RT_ENOSYS;
        }

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
        dma_lock(ctrl);

        err = ctrl->ops->prep_single(chan, dma_buf_addr,
                                     transfer->buffer_len, dir);

        dma_unlock(ctrl);
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

/**
 * @brief Find a DMA controller from device tree by name
 *
 * Looks up the "dmas" and "dma-names" properties in the device's
 * device tree node. The controller must have been probed and registered
 * via rt_dma_controller_register().
 *
 * @param[in]  dev   Slave device requesting a DMA channel
 * @param[in]  name  DMA channel name (matches dma-names entry in DT)
 * @param[out] args  Parsed DMA specifier from the dmas property
 *
 * @return DMA controller pointer on success, RT_NULL if not found
 */
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

/**
 * @brief Request a DMA channel for a slave device
 *
 * If a name is provided, the channel is looked up from device tree
 * via the "dmas" property. If no name is provided, any available
 * memory-to-memory capable controller is selected.
 *
 * The channel is added to the controller's channels_nodes list.
 *
 * @param[in] dev   Slave device requesting DMA service
 * @param[in] name  Channel name (from dma-names in DT), or NULL for
 *                  unnamed memory-to-memory allocation
 *
 * @return Pointer to the DMA channel on success, or an error pointer
 *         (rt_err_ptr(-RT_ENOMEM), rt_err_ptr(-RT_ENOSYS), etc.)
 */
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

    dma_lock(ctrl);
    rt_list_insert_before(&ctrl->channels_nodes, &chan->list);
    dma_unlock(ctrl);

    return chan;
}

/**
 * @brief Release a DMA channel back to the controller
 *
 * Removes the channel from the controller's list. If the controller
 * provides a release_chan operation, it is called; otherwise the
 * channel memory is simply freed.
 *
 * @param[in] chan  DMA channel to release
 *
 * @return RT_EOK on success, -RT_EINVAL if chan is NULL
 */
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
