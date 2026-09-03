/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2015-05-14     aubrcool@qq.com   first version
 * 2015-07-06     Bernard           code cleanup and remove RT_CAN_USING_LED;
 * 2025-09-20     wdfk_prog         Implemented non-blocking, ISR-safe send logic unified under rt_device_write.
 * 2026-08-29     wdfk_prog         Unified blocking and non-blocking TX request handling.
 * 2026-08-30     wdfk_prog         Stop maintenance timer before final controller stop.
 */

/*
 * Generic CAN device-adapter design
 * ---------------------------------
 *
 * This file is the RT-Thread device-framework boundary. It owns registration,
 * init/open/close, read/write routing, controller management and ISR dispatch;
 * can_tx.c owns TX mailbox synchronization and can_rx.c owns RX FIFO/lifetime.
 *
 * Normal runtime:
 *   register -> init/configure -> open -> allocate RX/TX runtime -> enable IRQs
 *   read  -> can_rx.c software FIFO
 *   write -> blocking mailbox+completion or one-shot non-blocking hardware submit
 *   BSP IRQ -> rt_hw_can_isr() -> RX/TX private core
 *
 * Controller-management runtime:
 *   application stops TX producers
 *     -> can->lock serializes the management operation
 *     -> close TX admission and verify complete TX idle
 *     -> pause RX and drain already-entered RX ISR/callback work
 *     -> call BSP configure/control
 *     -> resume RX, then restore TX admission
 *
 * Generic CAN deliberately does not retain or replay BSP hardware-filter
 * programming. If a controller-mutating BSP operation clears filters, the caller
 * must configure them again before depending on filtered RX. A failure after RX/TX
 * are quiesced is fail-closed: the function returns the hardware error without
 * reopening a data path whose controller state is uncertain. Generic CAN does not
 * automatically abort active TX to make a
 * configuration command succeed.
 *
 * Final close follows the same ownership rule: stop new TX, drain accepted TX,
 * pause RX, disable IRQ/controller activity, then detach/free Generic runtimes.
 * can->lock is the sleeping management mutex; tx_lock/rx_lock remain the IRQ-safe
 * publication/ownership boundaries used by the data paths.
 */

#include "can_internal.h"

#define CAN_LOCK(can)   rt_mutex_take(&(can)->lock, RT_WAITING_FOREVER)
#define CAN_UNLOCK(can) rt_mutex_release(&(can)->lock)

#if defined(RT_CAN_USING_STATUS_POLLING) || defined(RT_CAN_USING_BUS_HOOK)
static void cantimeout(void *arg);

/**
 * @brief Query whether the periodic CAN maintenance timer is active.
 * @param can CAN device whose timer is inspected.
 * @return RT_TRUE when the timer is active, otherwise RT_FALSE.
 */
static rt_bool_t _can_maintenance_timer_active(struct rt_can_device *can)
{
    rt_uint32_t state = RT_TIMER_FLAG_DEACTIVATED;

    if (rt_timer_control(&can->timer, RT_TIMER_CTRL_GET_STATE, &state) != RT_EOK)
    {
        return RT_FALSE;
    }

    return state == RT_TIMER_FLAG_ACTIVATED;
}
#endif

/**
 * @brief Initialize Generic CAN runtime pointers and apply the BSP configuration.
 * @param dev RT-Thread device object.
 * @return RT_EOK on success or the BSP configure error.
 */
static rt_err_t rt_can_init(struct rt_device *dev)
{
    struct rt_can_device *can;

    if (dev == RT_NULL)
    {
        return -RT_EINVAL;
    }

    can = (struct rt_can_device *)dev;
    can->can_rx = RT_NULL;
    can->can_tx = RT_NULL;
    can->rx_active_isr = 0;
#ifdef RT_CAN_USING_HDR
    can->hdr = RT_NULL;
#endif /* RT_CAN_USING_HDR */

    if (can->ops == RT_NULL || can->ops->configure == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    return can->ops->configure(can, &can->config);
}

#ifdef RT_CAN_USING_HDR
/**
 * @brief Allocate the optional Generic per-bank HDR routing table.
 * @param can CAN device whose HDR table is allocated.
 * @return RT_EOK on success or -RT_ENOMEM.
 */
static rt_err_t _can_hdr_open(struct rt_can_device *can)
{
    rt_uint32_t i;

    if (can->hdr != RT_NULL || can->config.maxhdr == 0)
    {
        return RT_EOK;
    }

    can->hdr = (struct rt_can_hdr *)rt_calloc(can->config.maxhdr, sizeof(*can->hdr));
    if (can->hdr == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    for (i = 0; i < can->config.maxhdr; i++)
    {
        rt_list_init(&can->hdr[i].list);
    }

    return RT_EOK;
}
#endif /* RT_CAN_USING_HDR */

/**
 * @brief Allocate requested Generic CAN RX/TX resources and enable BSP interrupts.
 *
 * Runtime pointers are published before their IRQ sources become visible. Any
 * partial-open failure disables acquired IRQ sources and rolls back only resources
 * created by this open attempt.
 *
 * @param dev RT-Thread CAN device object.
 * @param oflag Requested device open flags.
 * @return RT_EOK on success or the first allocation/BSP control error.
 */
static rt_err_t rt_can_open(struct rt_device *dev, rt_uint16_t oflag)
{
    struct rt_can_device *can;
    rt_uint16_t previous_open_flag;
    rt_bool_t tx_created = RT_FALSE;
    rt_bool_t rx_created = RT_FALSE;
    rt_bool_t tx_irq_enabled = RT_FALSE;
    rt_bool_t rx_irq_enabled = RT_FALSE;
    rt_bool_t err_irq_enabled = RT_FALSE;
#ifdef RT_CAN_USING_HDR
    rt_bool_t hdr_created = RT_FALSE;
#endif /* RT_CAN_USING_HDR */
    rt_err_t result;

    if (dev == RT_NULL)
    {
        return -RT_EINVAL;
    }

    can = (struct rt_can_device *)dev;
    if (can->ops == RT_NULL || can->ops->control == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    result = CAN_LOCK(can);
    if (result != RT_EOK)
    {
        return result;
    }

    previous_open_flag = dev->open_flag;
    if (!(previous_open_flag & RT_DEVICE_OFLAG_OPEN) &&
        (can->can_tx != RT_NULL || can->can_rx != RT_NULL
#ifdef RT_CAN_USING_HDR
         || can->hdr != RT_NULL
#endif /* RT_CAN_USING_HDR */
         ))
    {
        result = -RT_EBUSY;
        goto out_unlock;
    }

    /*
     * Start with RX/TX admission closed while runtimes are allocated. RX resume
     * later publishes admission immediately before enabling its BSP IRQ so the
     * first interrupt cannot race an unpublished Generic RX path.
     */
    dev->open_flag = (oflag & 0xff) &
                     ~(RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX);

    if ((oflag & RT_DEVICE_FLAG_INT_TX) && can->can_tx == RT_NULL)
    {
        result = rt_can_tx_open(can);
        if (result != RT_EOK)
        {
            goto fail;
        }
        tx_created = RT_TRUE;
    }

#ifdef RT_CAN_USING_HDR
    if (can->hdr == RT_NULL)
    {
        result = _can_hdr_open(can);
        if (result != RT_EOK)
        {
            goto fail;
        }
        hdr_created = can->hdr != RT_NULL ? RT_TRUE : RT_FALSE;
    }
#endif /* RT_CAN_USING_HDR */

    if ((oflag & RT_DEVICE_FLAG_INT_RX) && can->can_rx == RT_NULL)
    {
        result = rt_can_rx_open(can);
        if (result != RT_EOK)
        {
            goto fail;
        }
        rx_created = RT_TRUE;

        result = rt_can_rx_resume(can);
        if (result != RT_EOK)
        {
            goto fail;
        }
        rx_irq_enabled = RT_TRUE;
    }

    if (tx_created)
    {
        result = can->ops->control(can, RT_DEVICE_CTRL_SET_INT,
                                   (void *)RT_DEVICE_FLAG_INT_TX);
        if (result != RT_EOK)
        {
            goto fail;
        }
        dev->open_flag |= RT_DEVICE_FLAG_INT_TX;
        tx_irq_enabled = RT_TRUE;
    }

    result = can->ops->control(can, RT_DEVICE_CTRL_SET_INT,
                               (void *)RT_DEVICE_CAN_INT_ERR);
    if (result != RT_EOK)
    {
        goto fail;
    }
    err_irq_enabled = RT_TRUE;

#if defined(RT_CAN_USING_STATUS_POLLING) || defined(RT_CAN_USING_BUS_HOOK)
    if (!_can_maintenance_timer_active(can))
    {
        (void)rt_timer_start(&can->timer);
    }
#endif

    CAN_UNLOCK(can);
    return RT_EOK;

fail:
    if (err_irq_enabled)
    {
        (void)can->ops->control(can, RT_DEVICE_CTRL_CLR_INT,
                                (void *)RT_DEVICE_CAN_INT_ERR);
    }
    if (tx_irq_enabled)
    {
        (void)can->ops->control(can, RT_DEVICE_CTRL_CLR_INT,
                                (void *)RT_DEVICE_FLAG_INT_TX);
    }
    if (rx_irq_enabled)
    {
        (void)rt_can_rx_pause(can);
    }
    if (rx_created)
    {
        (void)rt_can_rx_close(can);
    }
#ifdef RT_CAN_USING_HDR
    if (hdr_created)
    {
        rt_free(can->hdr);
        can->hdr = RT_NULL;
    }
#endif /* RT_CAN_USING_HDR */
    if (tx_created)
    {
        rt_can_tx_close(can);
    }
    dev->open_flag = previous_open_flag;

out_unlock:
    CAN_UNLOCK(can);
    return result;
}


/**
 * @brief Perform final CAN software teardown after the application has stopped TX producers.
 *
 * Recoverable drain/abort/recovery decisions belong before rt_device_close(). The
 * RT-Thread device core owns ref_count and decrements the final reference before
 * entering this callback, so Generic CAN never writes ref_count to manufacture a
 * retry. Non-STOP cleanup errors are collected while teardown proceeds. A BSP
 * STOP failure is different: it is returned immediately after the quiet/IRQ-off
 * boundary, with Generic runtimes still allocated, so recovery remains user/BSP
 * policy instead of being hidden behind framework retry or state shadowing.
 */
static rt_err_t rt_can_close(struct rt_device *dev)
{
    struct rt_can_device *can;
    rt_uint16_t close_open_flag;
    rt_err_t result = RT_EOK;
    rt_err_t tmp_result;

    if (dev == RT_NULL)
    {
        return -RT_EINVAL;
    }

    can = (struct rt_can_device *)dev;
    tmp_result = CAN_LOCK(can);
    if (tmp_result != RT_EOK)
    {
        return tmp_result;
    }

    close_open_flag = dev->open_flag;
    (void)rt_can_tx_set_accepting(can, RT_FALSE);

    /*
     * Recoverable finite drain/abort policy belongs before rt_device_close().
     * Final close waits for ownership retirement instead of modifying core-owned
     * ref_count to manufacture a retry path.
     */
    tmp_result = rt_can_tx_drain_core(can, RT_WAITING_FOREVER);
    if (result == RT_EOK && tmp_result != RT_EOK)
    {
        result = tmp_result;
    }

#if defined(RT_CAN_USING_STATUS_POLLING) || defined(RT_CAN_USING_BUS_HOOK)
    if (_can_maintenance_timer_active(can))
    {
        tmp_result = rt_timer_stop(&can->timer);
        if (result == RT_EOK && tmp_result != RT_EOK)
        {
            result = tmp_result;
        }
    }
#endif

    tmp_result = rt_can_rx_pause(can);
    if (result == RT_EOK && tmp_result != RT_EOK)
    {
        result = tmp_result;
    }

    if (close_open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        tmp_result = can->ops->control(can, RT_DEVICE_CTRL_CLR_INT,
                                       (void *)RT_DEVICE_FLAG_INT_TX);
        if (result == RT_EOK && tmp_result != RT_EOK)
        {
            result = tmp_result;
        }
    }

    tmp_result = can->ops->control(can, RT_DEVICE_CTRL_CLR_INT,
                                   (void *)RT_DEVICE_CAN_INT_ERR);
    if (result == RT_EOK && tmp_result != RT_EOK)
    {
        result = tmp_result;
    }

    /*
     * STOP failure is reported directly to the caller. Generic CAN does not retry,
     * roll back the quiet window, recover the controller, or keep a second
     * START/STOP state shadow. The user/BSP owns the recovery decision.
     */
    tmp_result = can->ops->control(can, RT_CAN_CMD_START, (void *)(rt_ubase_t)0);
    if (tmp_result != RT_EOK)
    {
        CAN_UNLOCK(can);
        return tmp_result;
    }

    tmp_result = rt_can_rx_close(can);
    if (result == RT_EOK && tmp_result != RT_EOK)
    {
        result = tmp_result;
    }
#ifdef RT_CAN_USING_HDR
    if (can->hdr != RT_NULL)
    {
        rt_free(can->hdr);
        can->hdr = RT_NULL;
    }
#endif /* RT_CAN_USING_HDR */
    rt_can_tx_close(can);

#ifdef RT_CAN_USING_STATUS_POLLING
    can->status_indicate.ind = RT_NULL;
    can->status_indicate.args = RT_NULL;
#endif /* RT_CAN_USING_STATUS_POLLING */
#ifdef RT_CAN_USING_BUS_HOOK
    can->bus_hook = RT_NULL;
#endif /* RT_CAN_USING_BUS_HOOK */

    /*
    * Final close has deinitialized the BSP controller via
    * RT_CAN_CMD_START(0). Mark the RT-Thread device uninitialized
    * so the next rt_device_open() runs rt_can_init() again.
    */
    dev->flag &= ~RT_DEVICE_FLAG_ACTIVATED;
    dev->open_flag = RT_DEVICE_OFLAG_CLOSE;
    CAN_UNLOCK(can);
    return result;
}

/**
 * @brief Read frames from the interrupt-driven software RX FIFO.
 * @param dev RT-Thread CAN device object.
 * @param pos Unused device position.
 * @param buffer Destination frame buffer.
 * @param size Destination size in bytes.
 * @return Number of bytes read or a negative error.
 */
static rt_ssize_t rt_can_read(struct rt_device *dev, rt_off_t pos,
                              void *buffer, rt_size_t size)
{
    RT_UNUSED(pos);

    if (dev == RT_NULL || buffer == RT_NULL || size == 0)
    {
        return -RT_EINVAL;
    }
    if (dev->ref_count == 0 || !(dev->open_flag & RT_DEVICE_FLAG_INT_RX))
    {
        return -RT_ENOSYS;
    }

    return rt_can_rx_read_core((struct rt_can_device *)dev,
                               (struct rt_can_msg *)buffer, (rt_ssize_t)size);
}

/**
 * @brief Send CAN frames using blocking or one-shot non-blocking semantics.
 * @param dev RT-Thread CAN device object.
 * @param pos Unused device position.
 * @param buffer Source frame buffer.
 * @param size Source size in bytes.
 * @return Accepted byte count or a negative error.
 */
static rt_ssize_t rt_can_write(struct rt_device *dev, rt_off_t pos,
                               const void *buffer, rt_size_t size)
{
    const struct rt_can_msg *message;
    rt_bool_t blocking;

    RT_UNUSED(pos);

    if (dev == RT_NULL || buffer == RT_NULL || size == 0 ||
        (size % sizeof(struct rt_can_msg)) != 0)
    {
        return -RT_EINVAL;
    }
    if (dev->ref_count == 0 || !(dev->open_flag & RT_DEVICE_FLAG_INT_TX))
    {
        return -RT_ENOSYS;
    }

    message = (const struct rt_can_msg *)buffer;
    blocking = rt_interrupt_get_nest() == 0 && !message->nonblocking ? RT_TRUE : RT_FALSE;

    return rt_can_tx_write_core((struct rt_can_device *)dev, message, size, blocking);
}

/**
 * @brief Validate a non-NULL explicit filter before the BSP receives it.
 * @param can CAN device whose filter limits are checked.
 * @param filter Non-NULL requested filter transaction.
 * @return RT_EOK when every Generic field is valid, otherwise -RT_EINVAL.
 */
static rt_err_t _can_validate_filter(struct rt_can_device *can,
                                     const struct rt_can_filter_config *filter)
{
    rt_uint32_t i;

    if (filter == RT_NULL || filter->actived > 1U ||
        (filter->count != 0 && filter->items == RT_NULL))
    {
        return -RT_EINVAL;
    }

    for (i = 0; i < filter->count; i++)
    {
        const struct rt_can_filter_item *item = &filter->items[i];

        if (item->hdr_bank < -1 ||
#ifdef RT_CAN_USING_HDR
            item->hdr_bank >= (rt_int32_t)can->config.maxhdr ||
#endif /* RT_CAN_USING_HDR */
            (item->ide != RT_CAN_STDID && item->ide != RT_CAN_EXTID) ||
            (item->rtr != RT_CAN_DTR && item->rtr != RT_CAN_RTR) ||
            (item->mode != RT_CAN_MODE_MASK && item->mode != RT_CAN_MODE_LIST) ||
            (item->rxfifo != CAN_RX_FIFO0 && item->rxfifo != CAN_RX_FIFO1) ||
            (item->ide == RT_CAN_STDID && item->id > 0x7FFU))
        {
            return -RT_EINVAL;
        }
    }

    return RT_EOK;
}


/**
 * @brief Execute a controller-management command from a TX-idle/RX-paused boundary.
 *
 * can->lock serializes management operations. TX admission is closed atomically
 * with the idle check; RX admission is then paused and pinned ISR/callback work is
 * drained before hardware state changes. A failed BSP operation or RX resume keeps
 * data paths fail-closed instead of resuming on uncertain hardware state. Generic
 * CAN does not retain or replay hardware filter programming across reconfiguration.
 *
 * @param can CAN device to reconfigure.
 * @param cmd CAN control command when use_configure is RT_FALSE.
 * @param args Command/configuration arguments.
 * @param use_configure Select ops->configure() instead of ops->control().
 * @return RT_EOK on success or a validation/quiesce/BSP/resume error.
 */
static rt_err_t _can_reconfigure(struct rt_can_device *can, int cmd, void *args,
                                 rt_bool_t use_configure)
{
    rt_bool_t was_accepting = RT_FALSE;
    rt_bool_t rx_was_enabled;
    rt_bool_t start_enable = RT_FALSE;
    rt_bool_t keep_rx_paused = RT_FALSE;
    rt_err_t result;

    if (can == RT_NULL || can->ops == RT_NULL ||
        (use_configure && can->ops->configure == RT_NULL) ||
        (!use_configure && can->ops->control == RT_NULL))
    {
        return -RT_ENOSYS;
    }
    if (rt_interrupt_get_nest() > 0)
    {
        return -RT_EINVAL;
    }
    if (use_configure && args == RT_NULL)
    {
        return -RT_EINVAL;
    }

    if (!use_configure && cmd == RT_CAN_CMD_SET_FILTER && args != RT_NULL)
    {
        result = _can_validate_filter(can, (const struct rt_can_filter_config *)args);
        if (result != RT_EOK)
        {
            return result;
        }
    }

    result = CAN_LOCK(can);
    if (result != RT_EOK)
    {
        return result;
    }

    if (use_configure)
    {
        const struct can_configure *config = (const struct can_configure *)args;

        if ((can->can_tx != RT_NULL && config->sndboxnumber != can->config.sndboxnumber) ||
            (can->can_rx != RT_NULL && config->msgboxsz != can->config.msgboxsz)
#ifdef RT_CAN_USING_HDR
            || (can->hdr != RT_NULL && config->maxhdr != can->config.maxhdr)
#endif /* RT_CAN_USING_HDR */
        )
        {
            result = -RT_EBUSY;
            goto out_unlock;
        }
    }

    /* Stage 1: close TX admission and verify no frame is hardware-owned. */
    result = rt_can_tx_begin_management(can, &was_accepting);
    if (result != RT_EOK)
    {
        goto out_unlock;
    }

    if (!use_configure && cmd == RT_CAN_CMD_SET_PRIV)
    {
        rt_uint32_t privmode = (rt_uint32_t)(rt_ubase_t)args;

        if (privmode != RT_CAN_MODE_PRIV && privmode != RT_CAN_MODE_NOPRIV)
        {
            result = -RT_EINVAL;
            (void)rt_can_tx_set_accepting(can, was_accepting);
            goto out_unlock;
        }
    }

    rx_was_enabled = can->can_rx != RT_NULL &&
                     (can->parent.open_flag & RT_DEVICE_FLAG_INT_RX);
    if (rx_was_enabled)
    {
        /* Stage 2: stop new RX and drain ISR/callback lifetime pins. */
        result = rt_can_rx_pause(can);
        if (result != RT_EOK)
        {
            goto out_unlock;
        }
    }

    if (!use_configure && cmd == RT_CAN_CMD_START)
    {
        start_enable = (rt_uint32_t)(rt_ubase_t)args != 0 ? RT_TRUE : RT_FALSE;
        keep_rx_paused = start_enable ? RT_FALSE : RT_TRUE;
    }

    /* Stage 3: hardware mutation is allowed only inside the quiet window. */
    if (use_configure)
    {
        result = can->ops->configure(can, (struct can_configure *)args);
    }
    else
    {
        result = can->ops->control(can, cmd, args);
    }
    if (result != RT_EOK)
    {
        /*
         * No automatic controller recovery is attempted. In particular, a
         * failed STOP is returned to the caller with the quiet window kept
         * closed; the user/BSP decides how to recover the controller.
         */
        goto out_unlock;
    }

    if (use_configure)
    {
        rt_memcpy(&can->config, args, sizeof(can->config));
#if defined(RT_CAN_USING_STATUS_POLLING) || defined(RT_CAN_USING_BUS_HOOK)
        (void)rt_timer_control(&can->timer, RT_TIMER_CTRL_SET_TIME, &can->config.ticks);
#endif
    }
#ifdef RT_CAN_USING_HDR
    if (!use_configure && cmd == RT_CAN_CMD_SET_FILTER && args != RT_NULL)
    {
        result = rt_can_rx_commit_filter(can,
                                         (const struct rt_can_filter_config *)args);
        if (result != RT_EOK)
        {
            goto out_unlock;
        }
    }
#endif /* RT_CAN_USING_HDR */

    if (!use_configure && cmd == RT_CAN_CMD_SET_PRIV)
    {
        /* Preserve the legacy BSP control contract; commit Generic policy only after BSP success. */
        can->config.privmode = (rt_uint32_t)(rt_ubase_t)args;
    }

    /* Stage 4: reopen RX after the requested BSP operation is complete. */
    if (!keep_rx_paused && can->can_rx != RT_NULL &&
        (rx_was_enabled || (!use_configure && cmd == RT_CAN_CMD_START && start_enable)))
    {
        result = rt_can_rx_resume(can);
        if (result != RT_EOK)
        {
            /* RX enable failure keeps both data paths closed. */
            goto out_unlock;
        }
    }

    /* Stage 5: TX admission is the last data path reopened. */
    if (!use_configure && cmd == RT_CAN_CMD_START)
    {
        (void)rt_can_tx_set_accepting(can, start_enable ? RT_TRUE : RT_FALSE);
    }
    else
    {
        (void)rt_can_tx_set_accepting(can, was_accepting);
    }

out_unlock:
    CAN_UNLOCK(can);
    return result;
}

/**
 * @brief Dispatch RT-Thread and CAN-specific control operations.
 * @param dev RT-Thread CAN device object.
 * @param cmd Control command.
 * @param args Command-specific argument.
 * @return RT_EOK on success or a command-specific error.
 */
static rt_err_t rt_can_control(struct rt_device *dev, int cmd, void *args)
{
    struct rt_can_device *can;
    rt_err_t result = RT_EOK;

    if (dev == RT_NULL)
    {
        return -RT_EINVAL;
    }

    can = (struct rt_can_device *)dev;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SUSPEND:
        dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
        break;

    case RT_DEVICE_CTRL_RESUME:
        dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
        break;

    case RT_DEVICE_CTRL_CONFIG:
        result = _can_reconfigure(can, cmd, args, RT_TRUE);
        break;

    case RT_CAN_CMD_SET_FILTER:
    case RT_CAN_CMD_SET_BAUD:
    case RT_CAN_CMD_SET_BAUD_FD:
    case RT_CAN_CMD_SET_MODE:
    case RT_CAN_CMD_SET_BITTIMING:
    case RT_CAN_CMD_SET_CANFD:
    case RT_CAN_CMD_START:
        result = _can_reconfigure(can, cmd, args, RT_FALSE);
        break;

    case RT_CAN_CMD_SET_PRIV:
        if ((rt_uint32_t)(rt_ubase_t)args != can->config.privmode)
        {
            result = _can_reconfigure(can, cmd, args, RT_FALSE);
        }
        break;

    case RT_CAN_CMD_ABORT_TX:
        result = rt_can_tx_abort(can, (rt_uint32_t)(rt_ubase_t)args);
        break;

    case RT_CAN_CMD_ABORT_ALL:
    {
        rt_uint32_t mailbox;

        if (rt_interrupt_get_nest() > 0)
        {
            result = -RT_EINVAL;
            break;
        }
        result = CAN_LOCK(can);
        if (result != RT_EOK)
        {
            break;
        }
        for (mailbox = 0; mailbox < can->config.sndboxnumber; mailbox++)
        {
            rt_err_t abort_result = rt_can_tx_abort(can, mailbox);
            if (result == RT_EOK && abort_result != RT_EOK)
            {
                result = abort_result;
            }
        }
        CAN_UNLOCK(can);
        break;
    }

    case RT_CAN_CMD_SET_STATUS_IND:
#ifdef RT_CAN_USING_STATUS_POLLING
        if (args == RT_NULL)
        {
            result = -RT_EINVAL;
            break;
        }
        can->status_indicate.ind = ((rt_can_status_ind_type_t)args)->ind;
        can->status_indicate.args = ((rt_can_status_ind_type_t)args)->args;
#else
        result = -RT_ENOSYS;
#endif /* RT_CAN_USING_STATUS_POLLING */
        break;

#ifdef RT_CAN_USING_BUS_HOOK
    case RT_CAN_CMD_SET_BUS_HOOK:
        can->bus_hook = (rt_can_bus_hook)args;
        break;
#endif /* RT_CAN_USING_BUS_HOOK */

    default:
        result = can->ops != RT_NULL && can->ops->control != RT_NULL ? can->ops->control(can, cmd, args) : -RT_ENOSYS;
        break;
    }

    return result;
}

#if defined(RT_CAN_USING_STATUS_POLLING) || defined(RT_CAN_USING_BUS_HOOK)
/**
 * @brief Run optional periodic status polling and bus hook callbacks.
 * @param arg CAN device supplied when the timer was initialized.
 */
static void cantimeout(void *arg)
{
    rt_can_t can = (rt_can_t)arg;

    if (can == RT_NULL || can->parent.ref_count == 0)
    {
        return;
    }

#ifdef RT_CAN_USING_STATUS_POLLING
    if (can->ops != RT_NULL && can->ops->control != RT_NULL)
    {
        (void)can->ops->control(can, RT_CAN_CMD_GET_STATUS, (void *)&can->status);
    }
    if (can->status_indicate.ind != RT_NULL)
    {
        can->status_indicate.ind(can, can->status_indicate.args);
    }
#endif /* RT_CAN_USING_STATUS_POLLING */
#ifdef RT_CAN_USING_BUS_HOOK
    if (can->bus_hook != RT_NULL)
    {
        can->bus_hook(can);
    }
#endif /* RT_CAN_USING_BUS_HOOK */
}
#endif

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops can_device_ops = {
    rt_can_init,
    rt_can_open,
    rt_can_close,
    rt_can_read,
    rt_can_write,
    rt_can_control,
};
#endif /* RT_USING_DEVICE_OPS */

/**
 * @brief Register a CAN controller with the RT-Thread device framework.
 * @param can CAN device object provided by the BSP.
 * @param name Device registration name.
 * @param ops Low-level CAN operation table.
 * @param data BSP private data exposed as parent.user_data.
 * @return Result of rt_device_register().
 */
rt_err_t rt_hw_can_register(struct rt_can_device *can,
                            const char *name,
                            const struct rt_can_ops *ops,
                            void *data)
{
    struct rt_device *device;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(name != RT_NULL);
    RT_ASSERT(ops != RT_NULL);

    device = &can->parent;
    device->type = RT_Device_Class_CAN;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    can->ops = ops;
    can->can_rx = RT_NULL;
    can->can_tx = RT_NULL;
    can->rx_active_isr = 0;
#ifdef RT_CAN_USING_HDR
    can->hdr = RT_NULL;
#endif /* RT_CAN_USING_HDR */
#ifdef RT_CAN_USING_STATUS_POLLING
    can->status_indicate.ind = RT_NULL;
    can->status_indicate.args = RT_NULL;
#endif /* RT_CAN_USING_STATUS_POLLING */
#ifdef RT_CAN_USING_BUS_HOOK
    can->bus_hook = RT_NULL;
#endif /* RT_CAN_USING_BUS_HOOK */

    rt_mutex_init(&can->lock, "can", RT_IPC_FLAG_PRIO);
    rt_spin_lock_init(&can->tx_lock);
    rt_spin_lock_init(&can->rx_lock);
    rt_memset(&can->status, 0, sizeof(can->status));

#ifdef RT_USING_DEVICE_OPS
    device->ops = &can_device_ops;
#else
    device->init = rt_can_init;
    device->open = rt_can_open;
    device->close = rt_can_close;
    device->read = rt_can_read;
    device->write = rt_can_write;
    device->control = rt_can_control;
#endif /* RT_USING_DEVICE_OPS */

    device->user_data = data;

#if defined(RT_CAN_USING_STATUS_POLLING) || defined(RT_CAN_USING_BUS_HOOK)
    rt_timer_init(&can->timer, name, cantimeout, can, can->config.ticks,
                  RT_TIMER_FLAG_PERIODIC);
#endif

    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);
}

/**
 * @brief Dispatch a low-level CAN RX or TX terminal event into Generic CAN.
 * @param can CAN device reporting the event.
 * @param event Event type with optional FIFO/mailbox index in the upper bits.
 */
void rt_hw_can_isr(struct rt_can_device *can, int event)
{
    if (can == RT_NULL)
    {
        return;
    }

    switch (event & 0xff)
    {
    case RT_CAN_EVENT_RXOF_IND:
        rt_can_rx_isr_core(can, event, RT_TRUE);
        break;

    case RT_CAN_EVENT_RX_IND:
        rt_can_rx_isr_core(can, event, RT_FALSE);
        break;

    case RT_CAN_EVENT_TX_DONE:
    case RT_CAN_EVENT_TX_FAIL:
        rt_can_tx_isr_core(can, event);
        break;

    default:
        break;
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>

/**
 * @brief Print CAN controller status counters from the MSH shell.
 *
 * @param argc Number of shell arguments.
 * @param argv Shell argument vector.
 * @return 0 after handling the command, or -1 when the device cannot be found.
 */
int cmd_canstat(int argc, void **argv)
{
    static const char *ErrCode[] = {
        "No Error!",
        "Warning !",
        "Passive !",
        "Bus Off !"
    };

    if (argc >= 2)
    {
        struct rt_can_status status;
        rt_device_t candev = rt_device_find(argv[1]);
        if (candev == RT_NULL)
        {
            rt_kprintf(" Can't find can device %s\n", argv[1]);
            return -1;
        }

        rt_kprintf(" Found can device: %s...", argv[1]);
        rt_device_control(candev, RT_CAN_CMD_GET_STATUS, &status);
        rt_kprintf("\n Receive...error..count: %010ld. Send.....error....count: %010ld.",
                   status.rcverrcnt, status.snderrcnt);
        rt_kprintf("\n Bit..pad..error..count: %010ld. Format...error....count: %010ld",
                   status.bitpaderrcnt, status.formaterrcnt);
        rt_kprintf("\n Ack.......error..count: %010ld. Bit......error....count: %010ld.",
                   status.ackerrcnt, status.biterrcnt);
        rt_kprintf("\n CRC.......error..count: %010ld. Error.code.[%010ld]: ",
                   status.crcerrcnt, status.errcode);
        switch (status.errcode)
        {
        case 0:
            rt_kprintf("%s.", ErrCode[0]);
            break;
        case 1:
            rt_kprintf("%s.", ErrCode[1]);
            break;
        case 2:
        case 3:
            rt_kprintf("%s.", ErrCode[2]);
            break;
        default:
            rt_kprintf("%s.", ErrCode[3]);
            break;
        }
        rt_kprintf("\n Total.receive.packages: %010ld. Dropped.receive.packages: %010ld.",
                   status.rcvpkg, status.dropedrcvpkg);
        rt_kprintf("\n Total..send...packages: %010ld. Dropped...send..packages: %010ld.\n",
                   status.sndpkg + status.dropedsndpkg, status.dropedsndpkg);
    }
    else
    {
        rt_kprintf(" Invalid Call %s\n", argv[0]);
        rt_kprintf(" Please using %s cannamex. Here canname is driver name and x is candrive number.\n",
                   argv[0]);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_canstat, canstat, stat can device status);
#endif /* RT_USING_FINSH */
