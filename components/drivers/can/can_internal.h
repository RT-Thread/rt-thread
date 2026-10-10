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
 * Simplified Generic CAN private contract
 * ---------------------------------------
 *
 * This header is the private boundary between dev_can.c, can_tx.c and can_rx.c.
 * The design intentionally keeps only hardware-facing state that cannot be
 * derived elsewhere; there is no TX software queue, request scheduler or
 * secondary lifecycle state machine.
 *
 * Runtime flow:
 *
 *   open
 *     -> allocate/publish RX and TX runtimes
 *     -> enable the requested hardware IRQ sources
 *
 *   blocking TX
 *     -> reserve one fixed mailbox slot
 *     -> BSP sendmsg(mailbox)
 *     -> wait for that slot completion
 *     -> TX_DONE/TX_FAIL retires the hardware ownership
 *
 *   non-blocking TX
 *     -> one immediate BSP sendmsg_nonblocking() attempt
 *     -> no Generic retry or software enqueue
 *     -> TX_DONE/TX_FAIL decrements the shared hardware-pending count
 *
 *   RX IRQ
 *     -> acquire an RX lifetime pin under rx_lock
 *     -> BSP recvmsg() outside rx_lock
 *     -> publish into the Generic RX FIFO and snapshot callback state
 *     -> run callback outside rx_lock
 *     -> release the lifetime pin
 *
 *   management/configuration
 *     -> application first stops TX producers
 *     -> close TX admission and verify TX idle
 *     -> pause RX and drain already-pinned ISR/callback work
 *     -> apply the BSP operation
 *     -> restore RX/TX admission only when the resulting hardware state is safe
 *
 * Synchronization:
 * - can->lock serializes thread-side open/close/control operations that may sleep.
 * - can->tx_lock protects TX runtime publication, mailbox slots, pending and
 *   accepting. TX terminal ISR handling stays inside this lock domain.
 * - can->rx_lock protects RX runtime/FIFO/filter publication and rx_active_isr.
 *   RX hardware reads and user callbacks deliberately execute outside the lock
 *   while rx_active_isr keeps the referenced runtime alive.
 */

#ifndef __CAN_INTERNAL_H__
#define __CAN_INTERNAL_H__

#include <drivers/dev_can.h>

/** Blocking ownership state for one framework-visible hardware mailbox. */
enum rt_can_tx_slot_state
{
    RT_CAN_TX_SLOT_FREE = 0, /**< No blocking caller owns this mailbox slot. */
    RT_CAN_TX_SLOT_ACTIVE,  /**< Hardware accepted the blocking frame; terminal is pending. */
    RT_CAN_TX_SLOT_DONE,    /**< TX_DONE arrived; the blocking waiter still owns cleanup. */
    RT_CAN_TX_SLOT_FAILED,  /**< TX_FAIL arrived; the blocking waiter still owns cleanup. */
};

/** Per-mailbox blocking TX waiter state. */
struct rt_can_tx_slot
{
    struct rt_completion completion;       /**< Wakes the owner on this mailbox terminal. */
    enum rt_can_tx_slot_state state;       /**< Blocking ownership/terminal state. */
};

/** Simplified Generic CAN TX runtime. All fields are protected by can->tx_lock. */
struct rt_can_tx
{
    struct rt_can_tx_slot *slots;           /**< Fixed slot array, one per visible mailbox. */
    struct rt_semaphore wait_sem;           /**< Bounded TX-state-change notification. */
    rt_uint16_t pending;                    /**< Hardware-accepted frames not yet retired. */
    rt_bool_t accepting;                    /**< Whether normal TX admission is open. */
};

/**
 * @brief Allocate and publish the Generic TX runtime.
 *
 * Creates one blocking slot per framework-visible hardware mailbox and a bounded
 * counting TX-state-change semaphore. Tokens are wake credits, not mailbox
 * reservations, so waiters must rescan TX state after waking. Publication is
 * serialized by can->tx_lock.
 *
 * @param can CAN device being opened.
 * @return RT_EOK on success, or a negative allocation/configuration error.
 * @note Thread context only; this function may allocate memory and initialize IPC objects.
 */
rt_err_t rt_can_tx_open(struct rt_can_device *can);

/**
 * @brief Detach and release the Generic TX runtime during final close.
 *
 * The caller must have stopped new TX entry and established the final teardown
 * boundary before calling this function. The runtime pointer is detached under
 * can->tx_lock before its storage is freed so a late TX ISR observes RT_NULL.
 *
 * @param can CAN device being closed.
 * @note Thread context only. This function does not drain or abort hardware TX.
 */
void rt_can_tx_close(struct rt_can_device *can);

/**
 * @brief Send one or more CAN frames through the simplified TX data path.
 *
 * Blocking mode uses a fixed hardware-mailbox slot and waits for its terminal
 * completion. Non-blocking mode performs one immediate BSP submission and never
 * enters a Generic software queue. The buffer must contain whole rt_can_msg objects.
 *
 * @param can CAN device used for transmission.
 * @param messages Frame array to transmit.
 * @param size Buffer size in bytes.
 * @param blocking RT_TRUE to wait for each frame terminal, RT_FALSE for one-shot TX.
 * @return Accepted/completed byte count, or a negative error if no frame was accepted.
 * @note Blocking mode requires thread context; ISR callers must use non-blocking mode.
 */
rt_ssize_t rt_can_tx_write_core(struct rt_can_device *can,
                                const struct rt_can_msg *messages,
                                rt_size_t size,
                                rt_bool_t blocking);

/**
 * @brief Retire one hardware TX terminal reported by the BSP ISR.
 *
 * The mailbox index is encoded in event bits [15:8]. An ACTIVE blocking slot is
 * completed for its owner; otherwise the terminal retires one accepted one-shot
 * non-blocking submission. pending/statistics are updated under can->tx_lock.
 *
 * @param can CAN device reporting the terminal.
 * @param event RT_CAN_EVENT_TX_DONE or RT_CAN_EVENT_TX_FAIL plus mailbox index.
 * @note ISR-safe. This function does not sleep, submit another frame or run a scheduler.
 */
void rt_can_tx_isr_core(struct rt_can_device *can, int event);

/**
 * @brief Open or close normal TX admission.
 *
 * This changes only the Generic accepting gate; it does not wait for already
 * accepted hardware TX and does not enable/disable BSP interrupts.
 *
 * @param can CAN device whose admission gate is changed.
 * @param accepting RT_TRUE to allow new TX, RT_FALSE to reject new TX.
 * @return RT_EOK after the update; an unpublished TX runtime is treated as a no-op.
 */
rt_err_t rt_can_tx_set_accepting(struct rt_can_device *can, rt_bool_t accepting);

/**
 * @brief Establish the TX side of a controller-management quiet window.
 *
 * Atomically closes new TX admission and checks the complete TX-idle invariant.
 * If hardware ownership is still active, the previous admission state is restored
 * before -RT_EBUSY is returned. The application is responsible for stopping TX
 * producers before entering management; Generic CAN does not abort them implicitly.
 *
 * @param can CAN device entering a management operation.
 * @param was_accepting Receives the previous admission state for later restoration.
 * @return RT_EOK when TX is idle, -RT_EBUSY when work is still active, or an error.
 * @note Thread-side management helper; caller serializes management with can->lock.
 */
rt_err_t rt_can_tx_begin_management(struct rt_can_device *can, rt_bool_t *was_accepting);

/**
 * @brief Query the complete Generic TX-idle invariant.
 *
 * Idle means pending is zero and every blocking mailbox slot is FREE.
 *
 * @param can CAN device to inspect.
 * @return RT_TRUE when no Generic TX is hardware-owned, otherwise RT_FALSE.
 * @note Safe from thread context; state is sampled under can->tx_lock.
 */
rt_bool_t rt_can_tx_is_idle(struct rt_can_device *can);

/**
 * @brief Drain TX after the caller has already established device lifetime serialization.
 *
 * Unlike the public rt_can_tx_drain(), this helper intentionally skips the ref_count
 * misuse guard so final close can drain after the device core drops the last reference.
 *
 * @param can CAN device whose TX ownership is drained.
 * @param timeout Maximum wait in OS ticks, or RT_WAITING_FOREVER.
 * @return RT_EOK when idle, -RT_ETIMEOUT on deadline expiry, or an IPC error.
 * @note Thread context only; caller must serialize final-close lifetime.
 */
rt_err_t rt_can_tx_drain_core(struct rt_can_device *can, rt_tick_t timeout);

/**
 * @brief Allocate and publish the Generic software RX FIFO.
 *
 * The RX runtime is published under can->rx_lock before the caller enables the
 * hardware RX interrupt source.
 *
 * @param can CAN device being opened for interrupt RX.
 * @return RT_EOK on success, or a negative allocation/configuration error.
 * @note Thread context only; this function allocates memory.
 */
rt_err_t rt_can_rx_open(struct rt_can_device *can);

/**
 * @brief Detach and release the Generic RX runtime.
 *
 * The caller must first close RX admission and wait until rx_active_isr reaches
 * zero. This function refuses teardown while an ISR/callback lifetime pin remains.
 *
 * @param can CAN device being closed.
 * @return RT_EOK on success, -RT_EBUSY while RX is pinned, or another error.
 * @note Thread context only; does not disable the BSP RX interrupt by itself.
 */
rt_err_t rt_can_rx_close(struct rt_can_device *can);

/**
 * @brief Pause RX admission and wait for already-entered RX work to finish.
 *
 * Admission is closed under can->rx_lock before the BSP RX interrupt is disabled.
 * Disabling an IRQ does not force an ISR already executing on another CPU to exit,
 * so the function waits on idle_completion until every recvmsg/callback pin drains.
 *
 * @param can CAN device entering a management operation.
 * @return RT_EOK after RX is quiescent, or a BSP/IPC error.
 * @note Thread context only; this function may block.
 */
rt_err_t rt_can_rx_pause(struct rt_can_device *can);

/**
 * @brief Resume Generic RX admission and BSP RX interrupt delivery.
 *
 * Software admission is published before the BSP IRQ is enabled so an immediate
 * interrupt cannot observe an unready Generic RX path. IRQ-enable failure rolls
 * admission back to fail closed.
 *
 * @param can CAN device leaving a management operation.
 * @return RT_EOK on success or the BSP interrupt-control error.
 * @note Thread context only.
 */
rt_err_t rt_can_rx_resume(struct rt_can_device *can);

/**
 * @brief Copy buffered frames from the Generic RX FIFO to a caller buffer.
 *
 * FIFO and optional filter-list bookkeeping are updated while can->rx_lock is held.
 *
 * @param can CAN device used for reception.
 * @param messages Destination frame array.
 * @param size Destination size in bytes; it must contain whole rt_can_msg objects.
 * @return Number of bytes copied, or a negative validation error.
 */
rt_ssize_t rt_can_rx_read_core(struct rt_can_device *can,
                               struct rt_can_msg *messages,
                               rt_ssize_t size);

/**
 * @brief Consume one hardware RX event and publish the frame into the software FIFO.
 *
 * The ISR first acquires an RX lifetime pin, then calls BSP recvmsg() outside
 * can->rx_lock. FIFO/HDR metadata and callback state are published under the lock;
 * user callbacks execute unlocked while the lifetime pin remains held. A paused
 * management waiter is woken only when the final pin is released.
 *
 * @param can CAN device reporting RX.
 * @param event RX event with hardware FIFO index encoded in bits [15:8].
 * @param overflow RT_TRUE when the BSP also reports RX FIFO overflow.
 * @note ISR-safe. The callback executes in the BSP interrupt context.
 */
void rt_can_rx_isr_core(struct rt_can_device *can, int event, rt_bool_t overflow);

#ifdef RT_CAN_USING_HDR
/**
 * @brief Commit a successfully programmed explicit filter bank to Generic HDR routing state.
 *
 * Existing buffered frames remain in the global RX FIFO. Frames linked to filters
 * that are disabled/replaced are detached only from the filter-specific lists.
 * BSP-owned auto-bank requests (hdr_bank == -1) are intentionally not mapped to
 * Generic per-bank routing state.
 *
 * @param can CAN device whose HDR routing state is updated.
 * @param filter Filter configuration already accepted by the BSP.
 * @return RT_EOK on success or a validation error.
 * @note Caller must already hold the management quiet window with RX paused.
 */
rt_err_t rt_can_rx_commit_filter(struct rt_can_device *can,
                                 const struct rt_can_filter_config *filter);
#endif /* RT_CAN_USING_HDR */

#endif /* __CAN_INTERNAL_H__ */
