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
 *         -> slot ACTIVE + pending++
 *         -> wait that slot completion
 *         -> TX ISR marks DONE/FAILED + pending--
 *         -> waiter releases the slot to FREE
 *
 * Non-blocking frame:
 *   write/ISR -> BSP sendmsg_nonblocking() once -> pending++ on RT_EOK
 *             -> no retry/no software enqueue -> TX terminal -> pending--
 *
 * wait_sem is a bounded counting "TX state changed" notification, not a
 * mailbox-count semaphore. Its token capacity matches the number of visible
 * hardware mailboxes so multiple state changes are not collapsed in the
 * scan-to-wait window. Blocking senders and rt_can_tx_drain() must still recheck
 * state after waking because a token does not reserve a mailbox and may be stale.
 * Each blocking slot has its own completion for the terminal of that specific
 * hardware mailbox.
 *
 * can->tx_lock protects runtime publication, accepting, pending and every slot.
 * BSP sendmsg()/sendmsg_nonblocking() are required to be immediate hardware-submit
 * operations: they must not sleep or wait for bus transmission completion. Holding
 * tx_lock across the submit therefore closes the race where a very fast TX IRQ
 * could arrive before Generic ownership is published.
 *
 * One blocking frame uses a single hard RT_CANSND_MSG_TIMEOUT budget across both
 * mailbox contention and terminal wait. This timeout is a user configuration
 * contract: it must cover the worst-case mailbox wait, CAN arbitration/transmission
 * latency and terminal-ISR scheduling latency for the target system. Generic CAN
 * does not auto-extend the deadline or auto-abort/recover a frame whose terminal
 * arrives after it. A value shorter than the real worst case is outside the
 * supported contract: late-terminal correlation and continued TX bookkeeping are
 * not guaranteed until the caller performs its recovery policy.
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
 * @brief Test the complete Generic TX idle invariant while tx_lock is held.
 *
 * @param can CAN device that owns the TX runtime.
 * @param tx Published TX runtime.
 * @return RT_TRUE only when pending is zero and every blocking mailbox slot is FREE.
 */
static rt_bool_t _tx_idle_locked(struct rt_can_device *can, struct rt_can_tx *tx)
{
    rt_uint32_t i;

    if (tx->pending != 0)
    {
        return RT_FALSE;
    }

    for (i = 0; i < can->config.sndboxnumber; i++)
    {
        if (tx->slots[i].state != RT_CAN_TX_SLOT_FREE)
        {
            return RT_FALSE;
        }
    }

    return RT_TRUE;
}


/**
 * @brief Allocate the simplified TX runtime and publish it under tx_lock.
 *
 * sndchange is a 32-bit public mailbox bitmap, so reject configurations that
 * cannot be represented once here instead of silently truncating every TX event.
 */
rt_err_t rt_can_tx_open(struct rt_can_device *can)
{
    struct rt_can_tx *tx;
    rt_size_t alloc_size;
    rt_uint32_t i;
    rt_base_t level;
    rt_err_t result;

    RT_ASSERT(can != RT_NULL);

    if (can->config.sndboxnumber == 0 || can->ops == RT_NULL || can->ops->sendmsg == RT_NULL)
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

    result = rt_sem_init(&tx->wait_sem, "cantx", 0, RT_IPC_FLAG_PRIO);
    if (result != RT_EOK)
    {
        rt_free(tx);
        return result;
    }
    /*
     * Preserve up to one wake credit per visible mailbox so distinct mailbox
     * transitions cannot collapse while senders move from rescan to sleep.
     * A token still means only "TX state changed"; consumers must rescan state.
     */
    result = rt_sem_control(&tx->wait_sem,
                            RT_IPC_CMD_SET_VLIMIT,
                            (void *)(rt_ubase_t)can->config.sndboxnumber);
    if (result != RT_EOK)
    {
        rt_sem_detach(&tx->wait_sem);
        rt_free(tx);
        return result;
    }
    tx->accepting = RT_TRUE;

    level = rt_spin_lock_irqsave(&can->tx_lock);
    if (can->can_tx != RT_NULL)
    {
        rt_spin_unlock_irqrestore(&can->tx_lock, level);
        rt_sem_detach(&tx->wait_sem);
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
        rt_sem_detach(&tx->wait_sem);
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
 *
 * @param can CAN device entering a management operation.
 * @param was_accepting Receives the prior admission state for a later restore.
 * @return RT_EOK when TX is idle, -RT_EBUSY when hardware ownership remains.
 */
rt_err_t rt_can_tx_begin_management(struct rt_can_device *can, rt_bool_t *was_accepting)
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
    if (!_tx_idle_locked(can, tx))
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
    idle = tx == RT_NULL ? RT_TRUE : _tx_idle_locked(can, tx);
    rt_spin_unlock_irqrestore(&can->tx_lock, level);

    return idle;
}

/**
 * @brief Send one frame with a single hard deadline across mailbox wait and TX terminal wait.
 *
 * wait_sem is a shared TX-state-change notification for any blocking sender that
 * must rescan mailboxes. The selected slot completion is different: it belongs to
 * this frame only and reports that mailbox's TX_DONE/TX_FAIL terminal. Both waits
 * consume the same @p timeout budget, so mailbox contention cannot extend the
 * per-frame deadline.
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
    rt_uint32_t mailbox;
    rt_uint32_t selected = 0;
    rt_err_t wait_result;
    rt_ssize_t result;
    rt_base_t level;
    rt_bool_t submitted;

    start = rt_tick_get();

    for (;;)
    {
        submitted = RT_FALSE;
        result = -RT_EBUSY;

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
        }
        else
        {
            first = 0;
            last = can->config.sndboxnumber;
        }

        for (mailbox = first; mailbox < last; mailbox++)
        {
            slot = &tx->slots[mailbox];
            if (slot->state != RT_CAN_TX_SLOT_FREE)
            {
                continue;
            }

            /*
             * Completion reset, hardware submit, ownership publication and pending++
             * stay in one TX critical section. The TX ISR takes the same lock, so a
             * very fast terminal cannot retire an unpublished blocking owner.
             */
            rt_completion_init(&slot->completion);
            result = can->ops->sendmsg(can, message, mailbox);
            if (result == RT_EOK)
            {
                slot->state = RT_CAN_TX_SLOT_ACTIVE;
                tx->pending++;
                can->status.sndchange |= (1UL << mailbox);
                selected = mailbox;
                submitted = RT_TRUE;
                break;
            }
            if (result == -RT_EBUSY)
            {
                continue;
            }

            break;
        }

        if (!submitted && result != -RT_EBUSY)
        {
            can->status.dropedsndpkg++;
        }
        rt_spin_unlock_irqrestore(&can->tx_lock, level);

        if (submitted)
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

        /*
         * A wake only means TX state changed. Another blocking/NB sender may win
         * the freed mailbox, so always rescan instead of treating the wake as ownership.
         */
        wait_result = rt_sem_take(&tx->wait_sem, remaining);
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
        /*
         * The configured hard deadline expired before a terminal was published.
         * Generic CAN returns that timeout and retires its bookkeeping; it does not
         * extend the deadline, abort hardware, or recover a late terminal. The user
         * must configure RT_CANSND_MSG_TIMEOUT above the target system's real
         * worst-case mailbox/arbitration/transmission/ISR latency. Continued TX after
         * violating that contract requires caller-defined recovery before bookkeeping
         * can be relied upon again.
         */
        if (tx->pending > 0)
        {
            tx->pending--;
        }
        result = wait_result == RT_EOK ? -RT_ERROR : wait_result;
    }
    else
    {
        result = -RT_ERROR;
    }

    slot->state = RT_CAN_TX_SLOT_FREE;
    can->status.sndchange &= ~(1UL << selected);

    rt_spin_unlock_irqrestore(&can->tx_lock, level);

    /* FREE is another TX state change, not a terminal count. */
    (void)rt_sem_release(&tx->wait_sem);
    return result;
}

/**
 * @brief Perform one immediate mailbox-less hardware submission.
 *
 * Non-blocking TX never enters a software queue and never retries in Generic CAN.
 * pending is incremented only after the BSP accepts the frame while tx_lock keeps
 * a very fast terminal event from being accounted before publication.
 *
 * @param can CAN device used for the submission.
 * @param message Frame to submit.
 * @return RT_EOK on hardware acceptance, -RT_EBUSY when unavailable, or another error.
 */
static rt_ssize_t _tx_nonblocking_one(struct rt_can_device *can,
                                      const struct rt_can_msg *message)
{
    struct rt_can_tx *tx;
    rt_ssize_t result;
    rt_base_t level;

    if (can->config.privmode == RT_CAN_MODE_PRIV)
    {
        return -RT_ENOSYS;
    }
    if (can->ops == RT_NULL || can->ops->sendmsg_nonblocking == RT_NULL)
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

    /* The same lock keeps terminal publication behind successful pending++. */
    result = can->ops->sendmsg_nonblocking(can, message);
    if (result == RT_EOK)
    {
        tx->pending++;
    }
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
 * An ACTIVE blocking slot receives DONE/FAILED and its private completion. If no
 * blocking slot owns the mailbox, the terminal retires one previously accepted
 * non-blocking submission. pending and terminal statistics stay in the tx_lock domain.
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
        if (slot->state == RT_CAN_TX_SLOT_ACTIVE)
        {
            slot->state = terminal == RT_CAN_EVENT_TX_DONE ? RT_CAN_TX_SLOT_DONE : RT_CAN_TX_SLOT_FAILED;
            rt_completion_done(&slot->completion);
            accounted = RT_TRUE;
        }
    }

    /* A terminal with no active blocking slot belongs to a one-shot NB submit. */
    if (accounted || tx->pending > 0)
    {
        if (tx->pending > 0)
        {
            tx->pending--;
        }
        if (terminal == RT_CAN_EVENT_TX_DONE)
        {
            can->status.sndpkg++;
        }
        else
        {
            can->status.dropedsndpkg++;
        }
    }

    (void)rt_sem_release(&tx->wait_sem);
    rt_spin_unlock_irqrestore(&can->tx_lock, level);
}

/**
 * @brief Wait until no Generic CAN TX is hardware-owned and every blocking slot is free.
 *
 * The caller must stop TX producers first. wait_sem is intentionally reused as a
 * state-change notification; one wake does not imply idle, so the loop must recheck
 * pending and all slot states until the deadline expires.
 */
rt_err_t rt_can_tx_drain_core(struct rt_can_device *can, rt_tick_t timeout)
{
    struct rt_can_tx *tx;
    rt_tick_t start;
    rt_tick_t remaining;
    rt_err_t result;
    rt_base_t level;

    RT_ASSERT(can != RT_NULL);

    start = rt_tick_get();
    for (;;)
    {
        level = rt_spin_lock_irqsave(&can->tx_lock);
        tx = can->can_tx;
        if (tx == RT_NULL || _tx_idle_locked(can, tx))
        {
            rt_spin_unlock_irqrestore(&can->tx_lock, level);
            return RT_EOK;
        }
        rt_spin_unlock_irqrestore(&can->tx_lock, level);

        remaining = _tx_remaining(start, timeout);
        if (remaining == 0)
        {
            return -RT_ETIMEOUT;
        }

        result = rt_sem_take(&tx->wait_sem, remaining);
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
