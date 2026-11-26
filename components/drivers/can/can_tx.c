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
 * Simplified Generic CAN TX design
 * --------------------------------
 *
 * There is no Generic TX software queue or scheduler. The hardware mailboxes are
 * the queueing resource and every accepted frame must later produce exactly one
 * TX_DONE/TX_FAIL terminal from the BSP.
 *
 * Blocking frame:
 *   write -> scan fixed mailbox slots -> BSP sendmsg(mailbox)
 *         -> slot ACTIVE + slot.pending=true -> wait completion
 *         -> TX terminal clears slot.pending and reports DONE/FAILED
 *         -> waiter releases the slot; a timeout leaves ownership until terminal
 *
 * Non-blocking frame:
 *   write -> scan fixed mailbox slots once -> BSP sendmsg(mailbox)
 *         -> slot NONBLOCKING + slot.pending=true -> return immediately
 *         -> TX terminal releases that mailbox, with no retry or software queue.
 *
 * wait_event has one bit per visible mailbox. A private sender waits for its
 * mailbox bit, while ordinary senders and drain wait for eligible mailbox changes.
 * Waiters do not consume bits on wake: a competing waiter could otherwise lose a
 * notification between its scan and sleep. Only a failed state scan clears the
 * relevant bits under tx_lock, and all notifications are published under that
 * same lock. A bit is not a mailbox reservation. Each blocking slot retains its
 * own completion for the terminal of that specific hardware mailbox.
 *
 * can->tx_lock protects runtime publication, accepting and per-mailbox slots.
 * BSP send callbacks are required to be immediate hardware-submit
 * operations: they must not sleep or wait for bus transmission completion. Holding
 * tx_lock across the submit therefore closes the race where a very fast TX IRQ
 * could arrive before Generic ownership is published.
 *
 * One blocking frame uses a single hard RT_CANSND_MSG_TIMEOUT budget across both
 * mailbox contention and terminal wait. This timeout is a user configuration
 * contract: it must cover the worst-case mailbox wait, CAN arbitration/transmission
 * latency and terminal-ISR scheduling latency for the target system. Generic CAN
 * does not auto-extend the deadline or auto-abort/recover a frame whose terminal
 * arrives after it. On timeout the slot retains hardware ownership until the BSP
 * publishes TX_DONE/TX_FAIL; external recovery remains caller/BSP policy.
 */

#include "can_internal.h"

/**
 * @brief Calculate the remaining portion of one hard TX deadline.
 *
 * The same start tick is reused for mailbox contention and terminal completion,
 * so successive waits cannot each consume a fresh timeout interval.
 *
 * @param start Tick captured when the frame send attempt started.
 * @param timeout Total deadline in ticks, or RT_WAITING_FOREVER.
 * @return Remaining ticks, zero after expiry, or RT_WAITING_FOREVER.
 */
static rt_tick_t _tx_remaining(rt_tick_t start, rt_tick_t timeout)
{
    rt_tick_t elapsed;

    if (timeout == RT_WAITING_FOREVER)
    {
        return RT_WAITING_FOREVER;
    }

    elapsed = rt_tick_get() - start;
    if (elapsed >= timeout)
    {
        return 0;
    }

    return timeout - elapsed;
}

/**
 * @brief Return the mailboxes that prevent TX from being idle, under tx_lock.
 *
 * @param can CAN device that owns the TX runtime.
 * @param tx Published TX runtime.
 * @return Mask of pending or non-FREE slots; zero means TX is idle.
 */
static rt_uint32_t _tx_busy_mask_locked(struct rt_can_device *can, struct rt_can_tx *tx)
{
    rt_uint32_t i;
    /* Each bit records a slot that still prevents drain completion. */
    rt_uint32_t busy_mask = 0;

    for (i = 0; i < can->config.sndboxnumber; i++)
    {
        if (tx->slots[i].pending || tx->slots[i].state != RT_CAN_TX_SLOT_FREE)
        {
            busy_mask |= 1UL << i;
        }
    }

    return busy_mask;
}

/**
 * @brief Return the event mask covering all configured TX mailboxes.
 *
 * The open path validates the mailbox count as 1 through 32. Shifting a full
 * 32-bit mask right avoids an undefined shift when all 32 bits are needed.
 *
 * @param can CAN device with a validated TX runtime.
 * @return Mask with one bit per visible mailbox.
 */
static rt_uint32_t _tx_mailbox_mask(struct rt_can_device *can)
{
    return (rt_uint32_t)(0xffffffffUL >> (32U - can->config.sndboxnumber));
}

/**
 * @brief Discard stale notifications after a failed scan, under tx_lock.
 *
 * The caller holds tx_lock across the scan and this clear; every publisher also
 * holds tx_lock. Use the event's own spinlock for the bitmap, in that lock order.
 * rt_event_recv(CLEAR, 0) is not usable here: even a zero-time receive requires
 * scheduler availability. A non-clearing receive after unlocking cannot steal
 * another waiter's notification, including in the scan-to-wait window.
 *
 * @param tx Published TX runtime.
 * @param mask Mailboxes whose current wait condition is unsatisfied.
 */
static void _tx_clear_wait_event_locked(struct rt_can_tx *tx, rt_uint32_t mask)
{
    /* Serialize the event bitmap update against rt_event_send/recv. */
    rt_base_t level = rt_spin_lock_irqsave(&tx->wait_event.spinlock);

    tx->wait_event.set &= ~mask;
    rt_spin_unlock_irqrestore(&tx->wait_event.spinlock, level);
}

/**
 * @brief Allocate the simplified TX runtime and publish it under tx_lock.
 *
 * sndchange and the event mask are 32-bit mailbox bitmaps. Reject configurations
 * that cannot be represented before allocating or shifting any mailbox bits.
 */
rt_err_t rt_can_tx_open(struct rt_can_device *can)
{
    struct rt_can_tx *tx;
    rt_size_t alloc_size;
    rt_uint32_t i;
    rt_base_t level;
    rt_err_t result;

    RT_ASSERT(can != RT_NULL);

    if (can->config.sndboxnumber == 0 || can->config.sndboxnumber > 32U || can->ops == RT_NULL || can->ops->sendmsg == RT_NULL)
    {
        return -RT_EINVAL;
    }

    alloc_size = sizeof(*tx) + can->config.sndboxnumber * sizeof(struct rt_can_tx_slot);
    tx = (struct rt_can_tx *)rt_calloc(1, alloc_size);
    if (tx == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    tx->slots = (struct rt_can_tx_slot *)(tx + 1);
    for (i = 0; i < can->config.sndboxnumber; i++)
    {
        rt_completion_init(&tx->slots[i].completion);
        tx->slots[i].state = RT_CAN_TX_SLOT_FREE;
    }

    result = rt_event_init(&tx->wait_event, "cantx", RT_IPC_FLAG_PRIO);
    if (result != RT_EOK)
    {
        rt_free(tx);
        return result;
    }
    tx->accepting = RT_TRUE;

    level = rt_spin_lock_irqsave(&can->tx_lock);
    if (can->can_tx != RT_NULL)
    {
        rt_spin_unlock_irqrestore(&can->tx_lock, level);
        rt_event_detach(&tx->wait_event);
        rt_free(tx);
        return -RT_EBUSY;
    }
    can->can_tx = tx;
    rt_spin_unlock_irqrestore(&can->tx_lock, level);

    return RT_EOK;
}

/**
 * @brief Detach and free the TX runtime during final device teardown.
 *
 * Final close has stopped normal TX API entry and attempted hardware quiesce. The
 * pointer is detached under tx_lock so a late terminal ISR observes RT_NULL before
 * the storage is released.
 */
void rt_can_tx_close(struct rt_can_device *can)
{
    struct rt_can_tx *tx;
    rt_base_t level;

    RT_ASSERT(can != RT_NULL);

    level = rt_spin_lock_irqsave(&can->tx_lock);
    tx = can->can_tx;
    if (tx != RT_NULL)
    {
        /* Final close already stopped producer/API entry and hardware IRQ delivery. */
        tx->accepting = RT_FALSE;
        can->status.sndchange = 0;
        can->can_tx = RT_NULL;
    }
    rt_spin_unlock_irqrestore(&can->tx_lock, level);

    if (tx != RT_NULL)
    {
        rt_event_detach(&tx->wait_event);
        rt_free(tx);
    }
}

/**
 * @brief Open or close TX admission under the TX synchronization domain.
 *
 * @param can CAN device to update.
 * @param accepting New admission state.
 * @return RT_EOK after the state update.
 */
rt_err_t rt_can_tx_set_accepting(struct rt_can_device *can, rt_bool_t accepting)
{
    struct rt_can_tx *tx;
    rt_base_t level;

    RT_ASSERT(can != RT_NULL);

    level = rt_spin_lock_irqsave(&can->tx_lock);
    tx = can->can_tx;
    if (tx != RT_NULL)
    {
        tx->accepting = accepting;
    }
    rt_spin_unlock_irqrestore(&can->tx_lock, level);

    return RT_EOK;
}

/**
 * @brief Atomically close TX admission and verify that management may proceed.
 *
 * A sender that acquired tx_lock first either submits and makes TX non-idle, or
 * finishes before this check. A sender arriving later observes accepting=false.
 * Only an explicit forced controller stop may bypass the normal idle gate.
 *
 * @param can CAN device entering a management operation.
 * @param was_accepting Receives the prior admission state for a later restore.
 * @param force Permit explicit controller deinitialization without waiting for TX idle.
 * @return RT_EOK when management may proceed, -RT_EBUSY when TX is not idle.
 */
rt_err_t rt_can_tx_begin_management(struct rt_can_device *can, rt_bool_t *was_accepting, rt_bool_t force)
{
    struct rt_can_tx *tx;
    rt_base_t level;

    if (can == RT_NULL || was_accepting == RT_NULL)
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&can->tx_lock);
    tx = can->can_tx;
    if (tx == RT_NULL)
    {
        *was_accepting = RT_FALSE;
        rt_spin_unlock_irqrestore(&can->tx_lock, level);
        return RT_EOK;
    }

    *was_accepting = tx->accepting;
    tx->accepting = RT_FALSE;
    if (!force && _tx_busy_mask_locked(can, tx) != 0)
    {
        tx->accepting = *was_accepting;
        rt_spin_unlock_irqrestore(&can->tx_lock, level);
        return -RT_EBUSY;
    }

    rt_spin_unlock_irqrestore(&can->tx_lock, level);
    return RT_EOK;
}

/**
 * @brief Query the TX idle invariant under tx_lock.
 *
 * @param can CAN device to inspect.
 * @return RT_TRUE when no Generic TX ownership remains.
 */
rt_bool_t rt_can_tx_is_idle(struct rt_can_device *can)
{
    struct rt_can_tx *tx;
    rt_bool_t idle;
    rt_base_t level;

    RT_ASSERT(can != RT_NULL);

    level = rt_spin_lock_irqsave(&can->tx_lock);
    tx = can->can_tx;
    idle = (tx == RT_NULL || _tx_busy_mask_locked(can, tx) == 0) ? RT_TRUE : RT_FALSE;
    rt_spin_unlock_irqrestore(&can->tx_lock, level);

    return idle;
}

/**
 * @brief Release abandoned TX ownership after a confirmed forced controller stop.
 *
 * A successful hardware stop must suppress old TX terminals before this call.
 * ACTIVE blocking waiters become FAILED and retain their slot until the waiter
 * returns; nonblocking/timed-out slots may be released immediately.
 */
void rt_can_tx_retire_after_stop(struct rt_can_device *can)
{
    /* Published TX runtime, IRQ-save lock state and affected mailbox index. */
    struct rt_can_tx *tx;
    rt_base_t level;
    rt_uint32_t mailbox;

    RT_ASSERT(can != RT_NULL);

    level = rt_spin_lock_irqsave(&can->tx_lock);
    tx = can->can_tx;
    if (tx != RT_NULL)
    {
        for (mailbox = 0; mailbox < can->config.sndboxnumber; mailbox++)
        {
            /* Current hardware-mailbox owner, invalidated by controller deinit. */
            struct rt_can_tx_slot *slot = &tx->slots[mailbox];

            slot->pending = RT_FALSE;
            if (slot->state == RT_CAN_TX_SLOT_ACTIVE)
            {
                /* Wake the owner, but do not reuse its slot before it consumes FAILED. */
                slot->state = RT_CAN_TX_SLOT_FAILED;
                rt_completion_done(&slot->completion);
            }
            else if (slot->state != RT_CAN_TX_SLOT_DONE && slot->state != RT_CAN_TX_SLOT_FAILED)
            {
                slot->state = RT_CAN_TX_SLOT_FREE;
                can->status.sndchange &= ~(1UL << mailbox);
            }
        }
        tx->accepting = RT_FALSE;
        /* FORCE_STOP requires quiesced writers; wake all masks to recheck admission/idle. */
        (void)rt_event_send(&tx->wait_event, _tx_mailbox_mask(can));
    }
    rt_spin_unlock_irqrestore(&can->tx_lock, level);
}

/**
 * @brief Scan eligible slots once and submit to the first available hardware mailbox.
 * @param can CAN device; caller holds tx_lock with interrupts saved.
 * @param tx Published TX runtime protected by tx_lock.
 * @param message Frame to submit.
 * @param first First eligible logical mailbox index.
 * @param last Exclusive end of the eligible mailbox range.
 * @param blocking Whether the slot retains a blocking waiter.
 * @param selected Receives the selected mailbox only on acceptance.
 * @return RT_EOK on hardware acceptance, -RT_EBUSY if unavailable, or a submit error.
 */
static rt_ssize_t _tx_submit_locked(struct rt_can_device *can, struct rt_can_tx *tx,
                                    const struct rt_can_msg *message, rt_uint32_t first,
                                    rt_uint32_t last, rt_bool_t blocking, rt_uint32_t *selected)
{
    rt_uint32_t mailbox;         /* Candidate logical mailbox in the eligible range. */
    struct rt_can_tx_slot *slot; /* Generic ownership of the candidate mailbox. */
    rt_ssize_t result;           /* Immediate BSP submission result. */

    for (mailbox = first; mailbox < last; mailbox++)
    {
        slot = &tx->slots[mailbox];
        /* A completed blocking waiter still owns its slot until it reclaims it. */
        if (slot->state != RT_CAN_TX_SLOT_FREE || slot->pending)
        {
            continue;
        }

        if (blocking)
        {
            rt_completion_init(&slot->completion);
        }
        /* Submit and publish ownership under the same lock as the terminal ISR. */
        result = can->ops->sendmsg(can, message, mailbox);
        if (result == RT_EOK)
        {
            slot->state = blocking ? RT_CAN_TX_SLOT_ACTIVE : RT_CAN_TX_SLOT_NONBLOCKING;
            slot->pending = RT_TRUE;
            if (blocking)
            {
                can->status.sndchange |= (1UL << mailbox);
            }
            *selected = mailbox;
            return RT_EOK;
        }
        if (result != -RT_EBUSY)
        {
            return result;
        }
    }

    return -RT_EBUSY;
}

/**
 * @brief Send one frame with a single hard deadline across mailbox wait and TX terminal wait.
 *
 * wait_event notifies blocking senders about changes to their eligible mailboxes.
 * The selected slot completion is different: it belongs to this frame only and
 * reports that mailbox's TX_DONE/TX_FAIL terminal. Both waits consume the same
 * @p timeout budget, so mailbox contention cannot extend the per-frame deadline.
 */
static rt_ssize_t _tx_blocking_one(struct rt_can_device *can,
                                   const struct rt_can_msg *message,
                                   rt_tick_t timeout)
{
    struct rt_can_tx *tx;
    struct rt_can_tx_slot *slot;
    rt_tick_t start;
    rt_tick_t remaining;
    rt_uint32_t first;
    rt_uint32_t last;
    rt_uint32_t selected = 0;
    /* Event bits for the mailbox or mailboxes this sender is allowed to use. */
    rt_uint32_t wait_mask;
    rt_err_t wait_result;
    rt_ssize_t result;
    rt_base_t level;

    start = rt_tick_get();

    for (;;)
    {
        level = rt_spin_lock_irqsave(&can->tx_lock);
        tx = can->can_tx;
        if (tx == RT_NULL || !tx->accepting)
        {
            rt_spin_unlock_irqrestore(&can->tx_lock, level);
            return -RT_EBUSY;
        }

        if (can->config.privmode == RT_CAN_MODE_PRIV)
        {
            if (message->priv >= can->config.sndboxnumber)
            {
                can->status.dropedsndpkg++;
                rt_spin_unlock_irqrestore(&can->tx_lock, level);
                return -RT_EINVAL;
            }
            first = message->priv;
            last = message->priv + 1U;
            wait_mask = 1UL << first;
        }
        else
        {
            first = 0;
            last = can->config.sndboxnumber;
            wait_mask = _tx_mailbox_mask(can);
        }

        result = _tx_submit_locked(can, tx, message, first, last, RT_TRUE, &selected);

        if (result != RT_EOK && result != -RT_EBUSY)
        {
            can->status.dropedsndpkg++;
        }
        else if (result == -RT_EBUSY)
        {
            /* All eligible mailboxes are busy; discard only their stale notifications. */
            _tx_clear_wait_event_locked(tx, wait_mask);
        }
        rt_spin_unlock_irqrestore(&can->tx_lock, level);

        if (result == RT_EOK)
        {
            break;
        }
        if (result != -RT_EBUSY)
        {
            return result;
        }

        remaining = _tx_remaining(start, timeout);
        if (remaining == 0)
        {
            return -RT_ETIMEOUT;
        }

        /* A non-clearing wake only requests a rescan; it does not reserve a mailbox. */
        wait_result = rt_event_recv(&tx->wait_event, wait_mask, RT_EVENT_FLAG_OR, remaining, RT_NULL);
        if (wait_result != RT_EOK)
        {
            return wait_result;
        }
    }

    remaining = _tx_remaining(start, timeout);
    if (remaining == 0)
    {
        wait_result = -RT_ETIMEOUT;
    }
    else
    {
        /* This completion is private to the selected blocking mailbox slot. */
        wait_result = rt_completion_wait(&tx->slots[selected].completion, remaining);
    }

    level = rt_spin_lock_irqsave(&can->tx_lock);
    tx = can->can_tx;
    if (tx == RT_NULL)
    {
        rt_spin_unlock_irqrestore(&can->tx_lock, level);
        return -RT_ERROR;
    }

    slot = &tx->slots[selected];
    if (slot->state == RT_CAN_TX_SLOT_DONE)
    {
        result = RT_EOK;
    }
    else if (slot->state == RT_CAN_TX_SLOT_FAILED)
    {
        result = -RT_ERROR;
    }
    else if (slot->state == RT_CAN_TX_SLOT_ACTIVE)
    {
        /* Waiting expired, but the BSP still owns this mailbox until its terminal. */
        slot->state = RT_CAN_TX_SLOT_TIMED_OUT;
        result = wait_result == RT_EOK ? -RT_ERROR : wait_result;
        rt_spin_unlock_irqrestore(&can->tx_lock, level);
        return result;
    }
    else
    {
        result = -RT_ERROR;
    }

    slot->state = RT_CAN_TX_SLOT_FREE;
    can->status.sndchange &= ~(1UL << selected);

    /* Publish FREE before unlocking so a failed scan cannot erase this notification. */
    (void)rt_event_send(&tx->wait_event, 1UL << selected);
    rt_spin_unlock_irqrestore(&can->tx_lock, level);
    return result;
}

/**
 * @brief Scan eligible mailboxes once without waiting or software queueing.
 * @param can CAN device used for the submission.
 * @param message Frame to submit.
 * @return RT_EOK on hardware acceptance, -RT_EBUSY when unavailable,
 *         -RT_ENOSYS for unsupported mode/backend, or another submit error.
 */
static rt_ssize_t _tx_nonblocking_one(struct rt_can_device *can,
                                      const struct rt_can_msg *message)
{
    struct rt_can_tx *tx;
    rt_ssize_t result;
    rt_base_t level;
    /* Selected logical mailbox; ownership is published by the shared submit path. */
    rt_uint32_t mailbox;

    if (can->config.privmode == RT_CAN_MODE_PRIV)
    {
        return -RT_ENOSYS;
    }
    if (can->ops == RT_NULL || can->ops->sendmsg == RT_NULL || !can->ops->nonblocking_supported)
    {
        return -RT_ENOSYS;
    }

    level = rt_spin_lock_irqsave(&can->tx_lock);
    tx = can->can_tx;
    if (tx == RT_NULL || !tx->accepting)
    {
        rt_spin_unlock_irqrestore(&can->tx_lock, level);
        return -RT_EBUSY;
    }

    result = _tx_submit_locked(can, tx, message, 0, can->config.sndboxnumber, RT_FALSE, &mailbox);
    rt_spin_unlock_irqrestore(&can->tx_lock, level);

    return result;
}

/**
 * @brief Send a frame array through blocking or one-shot non-blocking TX.
 *
 * @param can CAN device used for TX.
 * @param messages Array of CAN frames.
 * @param size Buffer size in bytes; it must contain whole rt_can_msg objects.
 * @param blocking RT_TRUE for per-frame terminal wait, RT_FALSE for one-shot submission.
 * @return Accepted byte count, or a negative error when no frame was accepted.
 */
rt_ssize_t rt_can_tx_write_core(struct rt_can_device *can,
                                const struct rt_can_msg *messages,
                                rt_size_t size,
                                rt_bool_t blocking)
{
    rt_size_t count;
    rt_size_t i;
    rt_size_t accepted = 0;
    rt_ssize_t result = RT_EOK;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(messages != RT_NULL);

    if (size == 0 || (size % sizeof(struct rt_can_msg)) != 0)
    {
        return -RT_EINVAL;
    }

    count = size / sizeof(struct rt_can_msg);
    for (i = 0; i < count; i++)
    {
        if (blocking)
        {
            result = _tx_blocking_one(can, &messages[i], RT_CANSND_MSG_TIMEOUT);
        }
        else
        {
            result = _tx_nonblocking_one(can, &messages[i]);
        }

        if (result != RT_EOK)
        {
            return accepted != 0 ? (rt_ssize_t)accepted : result;
        }
        accepted += sizeof(struct rt_can_msg);
    }

    return (rt_ssize_t)accepted;
}

/**
 * @brief Retire one hardware TX terminal event.
 *
 * The terminal updates only its mailbox slot (blocking or non-blocking).
 * An unowned terminal does not consume another mailbox's pending request.
 * Ownership and terminal statistics stay inside the tx_lock domain.
 *
 * @param can CAN device reporting the terminal.
 * @param event TX_DONE/TX_FAIL with mailbox index encoded in the upper bits.
 */
void rt_can_tx_isr_core(struct rt_can_device *can, int event)
{
    struct rt_can_tx *tx;
    struct rt_can_tx_slot *slot;
    rt_uint32_t mailbox;
    rt_uint32_t terminal;
    rt_base_t level;
    rt_bool_t accounted = RT_FALSE;

    RT_ASSERT(can != RT_NULL);

    mailbox = ((rt_uint32_t)event) >> 8;
    terminal = (rt_uint32_t)event & 0xffU;

    level = rt_spin_lock_irqsave(&can->tx_lock);
    tx = can->can_tx;
    if (tx == RT_NULL)
    {
        rt_spin_unlock_irqrestore(&can->tx_lock, level);
        return;
    }

    if (mailbox < can->config.sndboxnumber)
    {
        slot = &tx->slots[mailbox];
        if (slot->pending)
        {
            slot->pending = RT_FALSE;
            if (slot->state == RT_CAN_TX_SLOT_ACTIVE)
            {
                slot->state = terminal == RT_CAN_EVENT_TX_DONE ? RT_CAN_TX_SLOT_DONE : RT_CAN_TX_SLOT_FAILED;
                rt_completion_done(&slot->completion);
            }
            else if (slot->state == RT_CAN_TX_SLOT_TIMED_OUT)
            {
                can->status.sndchange &= ~(1UL << mailbox);
                slot->state = RT_CAN_TX_SLOT_FREE;
            }
            else if (slot->state == RT_CAN_TX_SLOT_NONBLOCKING)
            {
                slot->state = RT_CAN_TX_SLOT_FREE;
            }
            accounted = RT_TRUE;
        }
    }

    if (accounted)
    {
        if (terminal == RT_CAN_EVENT_TX_DONE)
        {
            can->status.sndpkg++;
        }
        else
        {
            can->status.dropedsndpkg++;
        }
    }

    if (mailbox < can->config.sndboxnumber && tx->slots[mailbox].state == RT_CAN_TX_SLOT_FREE)
    {
        /* ACTIVE terminal owners notify mailbox availability only when they release the slot. */
        (void)rt_event_send(&tx->wait_event, 1UL << mailbox);
    }
    rt_spin_unlock_irqrestore(&can->tx_lock, level);
}

/**
 * @brief Wait until no Generic CAN TX is hardware-owned and every blocking slot is free.
 *
 * The caller must stop TX producers first. Wait for mailbox changes using the
 * shared event; a wake does not imply idle, so recheck all slots. Clear stale
 * bits only after a non-idle scan under tx_lock.
 */
rt_err_t rt_can_tx_drain_core(struct rt_can_device *can, rt_tick_t timeout)
{
    struct rt_can_tx *tx;
    rt_tick_t start;
    rt_tick_t remaining;
    /* Mask of currently busy mailboxes, whose changes may make TX idle. */
    rt_uint32_t wait_mask;
    rt_err_t result;
    rt_base_t level;

    RT_ASSERT(can != RT_NULL);

    start = rt_tick_get();
    for (;;)
    {
        level = rt_spin_lock_irqsave(&can->tx_lock);
        tx = can->can_tx;
        if (tx == RT_NULL)
        {
            rt_spin_unlock_irqrestore(&can->tx_lock, level);
            return RT_EOK;
        }
        wait_mask = _tx_busy_mask_locked(can, tx);
        if (wait_mask == 0)
        {
            rt_spin_unlock_irqrestore(&can->tx_lock, level);
            return RT_EOK;
        }
        _tx_clear_wait_event_locked(tx, wait_mask);
        rt_spin_unlock_irqrestore(&can->tx_lock, level);

        remaining = _tx_remaining(start, timeout);
        if (remaining == 0)
        {
            return -RT_ETIMEOUT;
        }

        result = rt_event_recv(&tx->wait_event, wait_mask, RT_EVENT_FLAG_OR, remaining, RT_NULL);
        if (result != RT_EOK)
        {
            return result;
        }
    }
}

/**
 * @brief Public TX drain entry with a defensive device-lifetime misuse check.
 *
 * The check intentionally does not claim to make concurrent final close safe; callers
 * must still serialize drain against rt_device_close(). It only rejects calls that
 * arrive after the device core has already dropped the last reference.
 */
rt_err_t rt_can_tx_drain(struct rt_can_device *can, rt_tick_t timeout)
{
    if (can == RT_NULL || rt_interrupt_get_nest() > 0)
    {
        return -RT_EINVAL;
    }
    if (can->parent.ref_count == 0)
    {
        return -RT_EBUSY;
    }

    return rt_can_tx_drain_core(can, timeout);
}

/**
 * @brief Request hardware abort for one Generic-visible TX mailbox.
 *
 * The control request itself does not retire pending ownership. The BSP must later
 * report TX_FAIL for that mailbox when abort completion becomes observable.
 *
 * @param can CAN device whose mailbox is aborted.
 * @param mailbox Generic-visible hardware mailbox index.
 * @return BSP control result, -RT_EINVAL for an invalid mailbox, or -RT_ENOSYS.
 */
rt_err_t rt_can_tx_abort(struct rt_can_device *can, rt_uint32_t mailbox)
{
    if (can == RT_NULL || rt_interrupt_get_nest() > 0 ||
        mailbox >= can->config.sndboxnumber)
    {
        return -RT_EINVAL;
    }
    if (can->ops == RT_NULL || can->ops->control == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    return can->ops->control(can, RT_CAN_CMD_ABORT_TX,
                             (void *)(rt_ubase_t)mailbox);
}
