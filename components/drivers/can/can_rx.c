/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-08-29     wdfk_prog         first version
 */

/*
 * Generic CAN RX lifetime and FIFO design
 * ---------------------------------------
 *
 * Hardware RX FIFO must be drained promptly in interrupt context, so RX keeps a
 * Generic software FIFO even though TX intentionally has no software queue.
 *
 * RX event flow:
 *   BSP RX IRQ -> rt_can_rx_isr_core()
 *     -> under rx_lock: verify admission and rx_active_isr++
 *     -> outside rx_lock: BSP recvmsg()
 *     -> under rx_lock: allocate/reuse FIFO node, update HDR links/statistics,
 *                       snapshot callback function/arguments
 *     -> outside rx_lock: invoke the user/filter callback
 *     -> under rx_lock: rx_active_isr-- and signal idle when the last pin drains
 *
 * The lifetime pin covers both recvmsg() and the callback. This matters on SMP:
 * disabling the RX interrupt prevents new delivery but does not make an ISR that
 * already entered on another CPU disappear. rt_can_rx_pause() therefore closes
 * admission first, disables the BSP IRQ, then waits for the existing pins to drain.
 *
 * can->rx_lock protects FIFO/HDR ownership, runtime publication and rx_active_isr.
 * It is deliberately not held while touching hardware through recvmsg() or while
 * calling user code, keeping IRQ-off critical sections bounded.
 *
 * When the FIFO is full, the existing policy is preserved: reuse the oldest node
 * so the newest received frame is retained. Disabling a HDR filter detaches its
 * filter-specific links but does not delete historical frames from the global FIFO.
 */

#include "can_internal.h"

#ifdef RT_CAN_USING_HDR
/**
 * @brief Detach one buffered frame from its filter-specific HDR list.
 *
 * The caller holds rx_lock. Global RX FIFO ownership is intentionally unchanged,
 * so disabling/reprogramming a filter does not discard already buffered history.
 *
 * @param can CAN device that owns the HDR table.
 * @param message Buffered frame whose HDR link is detached.
 */
static void _rx_detach_hdr_locked(struct rt_can_device *can,
                                  struct rt_can_msg_list *message)
{
    rt_int32_t hdr;

    if (rt_list_isempty(&message->hdrlist))
    {
        return;
    }

    hdr = message->data.hdr_index;
    rt_list_remove(&message->hdrlist);
    rt_list_init(&message->hdrlist);

    if (can->hdr != RT_NULL && hdr >= 0 && hdr < (rt_int32_t)can->config.maxhdr &&
        can->hdr[hdr].msgs > 0)
    {
        can->hdr[hdr].msgs--;
    }
}
#endif /* RT_CAN_USING_HDR */

/**
 * @brief Allocate and publish the software RX FIFO.
 *
 * @param can CAN device to initialize for interrupt RX.
 * @return RT_EOK on success or a negative allocation/configuration error.
 */
rt_err_t rt_can_rx_open(struct rt_can_device *can)
{
    struct rt_can_rx_fifo *rx_fifo;
    rt_size_t alloc_size;
    rt_uint32_t i;
    rt_base_t level;

    RT_ASSERT(can != RT_NULL);

    if (can->config.msgboxsz == 0 || can->ops == RT_NULL || can->ops->recvmsg == RT_NULL)
    {
        return -RT_EINVAL;
    }

    alloc_size = sizeof(*rx_fifo) + can->config.msgboxsz * sizeof(struct rt_can_msg_list);
    rx_fifo = (struct rt_can_rx_fifo *)rt_calloc(1, alloc_size);
    if (rx_fifo == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    rx_fifo->buffer = (struct rt_can_msg_list *)(rx_fifo + 1);
    rt_completion_init(&rx_fifo->idle_completion);
    rx_fifo->freenumbers = can->config.msgboxsz;
    rt_list_init(&rx_fifo->freelist);
    rt_list_init(&rx_fifo->uselist);

    for (i = 0; i < can->config.msgboxsz; i++)
    {
        rt_list_init(&rx_fifo->buffer[i].list);
#ifdef RT_CAN_USING_HDR
        rt_list_init(&rx_fifo->buffer[i].hdrlist);
#endif /* RT_CAN_USING_HDR */
        rt_list_insert_before(&rx_fifo->freelist, &rx_fifo->buffer[i].list);
    }

    level = rt_spin_lock_irqsave(&can->rx_lock);
    if (can->can_rx != RT_NULL)
    {
        rt_spin_unlock_irqrestore(&can->rx_lock, level);
        rt_free(rx_fifo);
        return -RT_EBUSY;
    }
    can->can_rx = rx_fifo;
    rt_spin_unlock_irqrestore(&can->rx_lock, level);

    return RT_EOK;
}

/**
 * @brief Close RX admission, disable RX IRQ delivery, and wait for pinned RX ISR work.
 *
 * Admission is cleared before the BSP IRQ is disabled, so no new RX handler can
 * acquire a lifetime pin. If an ISR is already outside rx_lock in recvmsg() or a
 * callback, its final unpin completes idle_completion and wakes this management
 * waiter without polling.
 */
rt_err_t rt_can_rx_pause(struct rt_can_device *can)
{
    struct rt_can_rx_fifo *rx_fifo;
    rt_err_t result = RT_EOK;
    rt_err_t wait_result;
    rt_bool_t was_enabled;
    rt_bool_t wait_idle;
    rt_base_t level;

    if (can == RT_NULL || rt_interrupt_get_nest() > 0)
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&can->rx_lock);
    rx_fifo = can->can_rx;
    if (rx_fifo == RT_NULL)
    {
        rt_spin_unlock_irqrestore(&can->rx_lock, level);
        return RT_EOK;
    }

    was_enabled = (can->parent.open_flag & RT_DEVICE_FLAG_INT_RX) != 0;
    can->parent.open_flag &= ~RT_DEVICE_FLAG_INT_RX;
    wait_idle = can->rx_active_isr != 0 ? RT_TRUE : RT_FALSE;
    if (wait_idle)
    {
        /*
         * Initialize while rx_lock still excludes the final unpin. This avoids
         * losing the one transition from active pins to zero between the state
         * snapshot and the management thread starting to wait.
         */
        rt_completion_init(&rx_fifo->idle_completion);
    }
    rt_spin_unlock_irqrestore(&can->rx_lock, level);

    if (was_enabled && can->ops != RT_NULL && can->ops->control != RT_NULL)
    {
        result = can->ops->control(can, RT_DEVICE_CTRL_CLR_INT,
                                   (void *)RT_DEVICE_FLAG_INT_RX);
    }

    if (wait_idle)
    {
        wait_result = rt_completion_wait(&rx_fifo->idle_completion, RT_WAITING_FOREVER);
        if (result == RT_EOK && wait_result != RT_EOK)
        {
            result = wait_result;
        }
    }

    return result;
}

/**
 * @brief Publish RX admission and then enable BSP RX interrupt delivery.
 *
 * Publishing admission first lets a pending IRQ safely acquire a lifetime pin as
 * soon as hardware delivery becomes visible. IRQ-enable failure rolls admission
 * back to the closed state.
 *
 * @param can CAN device to resume.
 * @return RT_EOK on success or the BSP interrupt-control error.
 */
rt_err_t rt_can_rx_resume(struct rt_can_device *can)
{
    rt_err_t result;
    rt_base_t level;

    if (can == RT_NULL || rt_interrupt_get_nest() > 0)
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&can->rx_lock);
    if (can->can_rx == RT_NULL)
    {
        rt_spin_unlock_irqrestore(&can->rx_lock, level);
        return RT_EOK;
    }
    if (can->parent.open_flag & RT_DEVICE_FLAG_INT_RX)
    {
        rt_spin_unlock_irqrestore(&can->rx_lock, level);
        return RT_EOK;
    }

    /* Publish admission before IRQ enable so the first new IRQ can be pinned. */
    can->parent.open_flag |= RT_DEVICE_FLAG_INT_RX;
    rt_spin_unlock_irqrestore(&can->rx_lock, level);

    if (can->ops == RT_NULL || can->ops->control == RT_NULL)
    {
        result = -RT_ENOSYS;
    }
    else
    {
        result = can->ops->control(can, RT_DEVICE_CTRL_SET_INT,
                                   (void *)RT_DEVICE_FLAG_INT_RX);
    }

    if (result != RT_EOK)
    {
        /* Fail closed: no RX admission may remain published after enable failure. */
        level = rt_spin_lock_irqsave(&can->rx_lock);
        can->parent.open_flag &= ~RT_DEVICE_FLAG_INT_RX;
        rt_spin_unlock_irqrestore(&can->rx_lock, level);
    }

    return result;
}

/**
 * @brief Detach and free an RX FIFO after all pinned ISR/callback work has drained.
 *
 * @param can CAN device whose RX runtime is released.
 * @return RT_EOK on success or -RT_EBUSY if an RX lifetime pin unexpectedly remains.
 */
rt_err_t rt_can_rx_close(struct rt_can_device *can)
{
    struct rt_can_rx_fifo *rx_fifo;
    rt_base_t level;
#ifdef RT_CAN_USING_HDR
    rt_uint32_t i;
#endif /* RT_CAN_USING_HDR */

    if (can == RT_NULL)
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&can->rx_lock);
    RT_ASSERT(can->rx_active_isr == 0);
    rx_fifo = can->can_rx;
    can->can_rx = RT_NULL;
    can->parent.open_flag &= ~RT_DEVICE_FLAG_INT_RX;

#ifdef RT_CAN_USING_HDR
    if (can->hdr != RT_NULL)
    {
        for (i = 0; i < can->config.maxhdr; i++)
        {
            can->hdr[i].msgs = 0;
            rt_list_init(&can->hdr[i].list);
        }
    }
#endif /* RT_CAN_USING_HDR */
    rt_spin_unlock_irqrestore(&can->rx_lock, level);

    if (rx_fifo != RT_NULL)
    {
        rt_free(rx_fifo);
    }

    return RT_EOK;
}

/**
 * @brief Copy buffered CAN frames to the caller while holding RX ownership safely.
 *
 * @param can CAN device used for RX.
 * @param messages Destination frame buffer.
 * @param size Destination size in bytes.
 * @return Number of bytes copied, or a negative validation/admission error.
 */
rt_ssize_t rt_can_rx_read_core(struct rt_can_device *can,
                               struct rt_can_msg *messages,
                               rt_ssize_t size)
{
    rt_ssize_t remaining;
    rt_base_t level;

    if (can == RT_NULL || messages == RT_NULL || size <= 0 ||
        (size % (rt_ssize_t)sizeof(struct rt_can_msg)) != 0)
    {
        return -RT_EINVAL;
    }

    remaining = size;
    while (remaining >= (rt_ssize_t)sizeof(struct rt_can_msg))
    {
        struct rt_can_rx_fifo *rx_fifo;
        struct rt_can_msg_list *message = RT_NULL;
#ifdef RT_CAN_USING_HDR
        rt_int32_t hdr;
#endif /* RT_CAN_USING_HDR */

        level = rt_spin_lock_irqsave(&can->rx_lock);
        rx_fifo = can->can_rx;
        if (rx_fifo == RT_NULL || !(can->parent.open_flag & RT_DEVICE_FLAG_INT_RX))
        {
            rt_spin_unlock_irqrestore(&can->rx_lock, level);
            return remaining == size ? -RT_EBUSY : size - remaining;
        }

#ifdef RT_CAN_USING_HDR
        hdr = messages->hdr_index;
        if (hdr >= 0)
        {
            if (can->hdr != RT_NULL && hdr < (rt_int32_t)can->config.maxhdr &&
                !rt_list_isempty(&can->hdr[hdr].list))
            {
                message = rt_list_entry(can->hdr[hdr].list.next,
                                        struct rt_can_msg_list, hdrlist);
                rt_list_remove(&message->list);
                rt_list_init(&message->list);
                _rx_detach_hdr_locked(can, message);
            }
        }
        else
#endif /* RT_CAN_USING_HDR */
        {
            if (!rt_list_isempty(&rx_fifo->uselist))
            {
                message = rt_list_entry(rx_fifo->uselist.next,
                                        struct rt_can_msg_list, list);
                rt_list_remove(&message->list);
                rt_list_init(&message->list);
#ifdef RT_CAN_USING_HDR
                _rx_detach_hdr_locked(can, message);
#endif /* RT_CAN_USING_HDR */
            }
        }

        if (message == RT_NULL)
        {
            rt_spin_unlock_irqrestore(&can->rx_lock, level);
            break;
        }

        rt_memcpy(messages, &message->data, sizeof(*messages));
        rt_list_insert_before(&rx_fifo->freelist, &message->list);
        rx_fifo->freenumbers++;
        rt_spin_unlock_irqrestore(&can->rx_lock, level);

        messages++;
        remaining -= sizeof(struct rt_can_msg);
    }

    return size - remaining;
}

/**
 * @brief Receive one hardware frame while pinning RX/HDR lifetime across lock-free work.
 *
 * Once admission succeeds and rx_active_isr is incremented, this ISR completes the
 * already-started receive even if management closes admission concurrently. Pause
 * only blocks new pins, then waits for this handler (including its callback) to unpin.
 */
void rt_can_rx_isr_core(struct rt_can_device *can, int event, rt_bool_t overflow)
{
    struct rt_can_rx_fifo *rx_fifo;
    struct rt_can_msg_list *message = RT_NULL;
    struct rt_can_msg received = {0};
    rt_size_t rx_length = 0;
    rt_uint32_t fifo;
    rt_ssize_t result;
    rt_base_t level;
    rt_bool_t wake_idle = RT_FALSE;
#ifdef RT_CAN_USING_HDR
    rt_int32_t hdr = -1;
    rt_err_t (*hdr_ind)(rt_device_t, void *, rt_int32_t, rt_size_t) = RT_NULL;
    void *hdr_args = RT_NULL;
    rt_size_t hdr_length = 0;
#endif /* RT_CAN_USING_HDR */

    RT_ASSERT(can != RT_NULL);

    level = rt_spin_lock_irqsave(&can->rx_lock);
    rx_fifo = can->can_rx;
    if (rx_fifo == RT_NULL || !(can->parent.open_flag & RT_DEVICE_FLAG_INT_RX))
    {
        rt_spin_unlock_irqrestore(&can->rx_lock, level);
        return;
    }

    can->rx_active_isr++;
    if (overflow)
    {
        can->status.dropedrcvpkg++;
    }
    rt_spin_unlock_irqrestore(&can->rx_lock, level);

    /* Hardware access is intentionally outside rx_lock. */
    fifo = ((rt_uint32_t)event) >> 8;
    result = can->ops->recvmsg(can, &received, fifo);

    level = rt_spin_lock_irqsave(&can->rx_lock);
    if (result < 0)
    {
        goto release_pin_locked;
    }

    can->status.rcvpkg++;
    can->status.rcvchange = 1;

    if (!rt_list_isempty(&rx_fifo->freelist))
    {
        message = rt_list_entry(rx_fifo->freelist.next,
                                struct rt_can_msg_list, list);
        rt_list_remove(&message->list);
        rt_list_init(&message->list);
        rx_fifo->freenumbers--;
    }
    else if (!rt_list_isempty(&rx_fifo->uselist))
    {
        /* Preserve the existing observable policy: drop oldest, retain newest. */
        message = rt_list_entry(rx_fifo->uselist.next,
                                struct rt_can_msg_list, list);
        rt_list_remove(&message->list);
        rt_list_init(&message->list);
#ifdef RT_CAN_USING_HDR
        _rx_detach_hdr_locked(can, message);
#endif /* RT_CAN_USING_HDR */
        if (!overflow)
        {
            can->status.dropedrcvpkg++;
        }
    }

    if (message == RT_NULL)
    {
        goto release_pin_locked;
    }

    rt_memcpy(&message->data, &received, sizeof(received));
    rt_list_insert_before(&rx_fifo->uselist, &message->list);

#ifdef RT_CAN_USING_HDR
    hdr = received.hdr_index;
    if (can->hdr != RT_NULL && hdr >= 0 && hdr < (rt_int32_t)can->config.maxhdr &&
        can->hdr[hdr].connected)
    {
        rt_list_insert_before(&can->hdr[hdr].list, &message->hdrlist);
        can->hdr[hdr].msgs++;
        if (can->hdr[hdr].filter.ind != RT_NULL)
        {
            /* Callback data stays valid because the RX lifetime pin remains held. */
            hdr_ind = can->hdr[hdr].filter.ind;
            hdr_args = can->hdr[hdr].filter.args;
            hdr_length = can->hdr[hdr].msgs * sizeof(struct rt_can_msg);
        }
    }
#endif /* RT_CAN_USING_HDR */

    rx_length = (can->config.msgboxsz - rx_fifo->freenumbers) *
                sizeof(struct rt_can_msg);

    /* User callbacks run without rx_lock, while rx_active_isr still pins RX/HDR. */
    rt_spin_unlock_irqrestore(&can->rx_lock, level);

#ifdef RT_CAN_USING_HDR
    if (hdr_ind != RT_NULL)
    {
        hdr_ind(&can->parent, hdr_args, hdr, hdr_length);
    }
    else
#endif /* RT_CAN_USING_HDR */
    if (can->parent.rx_indicate != RT_NULL && rx_length != 0)
    {
        can->parent.rx_indicate(&can->parent, rx_length);
    }

    level = rt_spin_lock_irqsave(&can->rx_lock);

release_pin_locked:
    RT_ASSERT(can->rx_active_isr > 0);
    can->rx_active_isr--;
    /*
        * pause() reinitializes idle_completion while holding rx_lock before it
        * starts waiting. The final pinned ISR must signal exactly when admission
        * is closed and the active count reaches zero; otherwise the management
        * thread could wait forever after an ISR/callback race.
        */
    if (can->rx_active_isr == 0 && !(can->parent.open_flag & RT_DEVICE_FLAG_INT_RX))
    {
        wake_idle = RT_TRUE;
    }
    rt_spin_unlock_irqrestore(&can->rx_lock, level);

    if (wake_idle)
    {
        rt_completion_done(&rx_fifo->idle_completion);
    }
}

#ifdef RT_CAN_USING_HDR
/**
 * @brief Commit a successful BSP filter update into Generic HDR routing state.
 *
 * Filter-specific links from previous programming are detached, while frames stay
 * on the global RX queue with their original hdr_index metadata.
 *
 * @param can CAN device whose HDR routing state is updated.
 * @param filter Filter transaction already accepted by the BSP.
 * @return RT_EOK on success or a validation/lifetime error.
 */
rt_err_t rt_can_rx_commit_filter(struct rt_can_device *can,
                                 const struct rt_can_filter_config *filter)
{
    rt_uint32_t i;
    rt_base_t level;

    if (can == RT_NULL || filter == RT_NULL ||
        (filter->count != 0 && filter->items == RT_NULL))
    {
        return -RT_EINVAL;
    }
    if (can->hdr == RT_NULL)
    {
        return RT_EOK;
    }

    level = rt_spin_lock_irqsave(&can->rx_lock);
    RT_ASSERT(can->rx_active_isr == 0);

    for (i = 0; i < filter->count; i++)
    {
        const struct rt_can_filter_item *item = &filter->items[i];
        struct rt_can_hdr *hdr;

        /*
         * hdr_bank == -1 keeps the legacy BSP auto-allocation contract. Generic
         * cannot bind per-bank software routing without an explicit bank and must
         * not rewrite the BSP-owned allocation result into the caller's request.
         */
        if (item->hdr_bank < 0 || item->hdr_bank >= (rt_int32_t)can->config.maxhdr)
        {
            continue;
        }

        hdr = &can->hdr[item->hdr_bank];

        /*
         * A filter bank reprogram changes the meaning of its filter-specific
         * queue. Detach frames matched by the previous programming before
         * committing the new routing state; the global RX history remains available.
         */
        while (!rt_list_isempty(&hdr->list))
        {
            struct rt_can_msg_list *message;

            message = rt_list_entry(hdr->list.next,
                                    struct rt_can_msg_list, hdrlist);
            rt_list_remove(&message->hdrlist);
            rt_list_init(&message->hdrlist);
        }
        hdr->msgs = 0;
        rt_list_init(&hdr->list);

        if (filter->actived)
        {
            rt_memcpy(&hdr->filter, item, sizeof(*item));
            hdr->connected = 1;
        }
        else
        {
            /* Disable only detaches filter-specific ownership; global history remains. */
            hdr->connected = 0;
            rt_memset(&hdr->filter, 0, sizeof(hdr->filter));
        }
    }

    rt_spin_unlock_irqrestore(&can->rx_lock, level);
    return RT_EOK;
}


#endif /* RT_CAN_USING_HDR */
