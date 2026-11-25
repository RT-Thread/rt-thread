/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-11     cms           add simulated CAN framework utest
 */

/**
 * Test Case Name: CAN Framework Test
 *
 * Test Objectives:
 * - Validate the Generic CAN device registration and lookup contract.
 * - Validate open/close reference counting and the runtime re-open path.
 * - Validate START(0)/START(1) TX admission gating and BSP error propagation.
 * - Validate the blocking mailbox timeout path without any real controller.
 * - Validate targeted wakeups for two concurrently waiting private mailboxes.
 * - Validate non-blocking TX ownership retirement through a simulated terminal.
 * - Validate the RX ISR to software FIFO to rt_device_read() path.
 *
 * Test Scenarios:
 * - Register a virtual CAN device whose ops callbacks are fully simulated.
 * - Exercise open/close, including a second open and a reopen after final close.
 * - Inject controlled sendmsg/sendmsg_nonblocking errors and verify the error
 *   is returned to the caller; never touch a CAN bus.
 * - Report a TX_DONE terminal through rt_hw_can_isr() and verify the mailbox
 *   slot is released again.
 * - Leave two private mailboxes owned after timeout; suspend one writer for
 *   each, then retire mailbox 0 while the higher-priority mailbox 1 waiter is
 *   still blocked. Complete both new submissions independently.
 * - Report an RX event through rt_hw_can_isr() and read the frame back.
 *
 * Verification Metrics:
 * - rt_device_find() returns the registered device with the CAN class.
 * - ref_count returns to zero after close and rt_device_open() works again.
 * - START(0) rejects TX with -RT_EBUSY and START(1) restores admission.
 * - BSP send errors are propagated unchanged to rt_device_write().
 * - A busy mailbox returns -RT_ETIMEOUT once the TX deadline expires.
 * - A terminal for mailbox 0 enables only the mailbox 0 writer; both writers
 *   complete successfully after their own simulated terminals.
 * - rt_can_tx_drain() observes the simulated terminal and the RX frame read
 *   back matches the frame produced by the simulated recvmsg().
 *
 * Dependencies:
 * - Hardware requirements: none. The test registers a virtual device and does
 *   not depend on a CAN controller, transceiver or bus wiring.
 * - Software configuration:
 *     - RT_USING_UTESTCASES must be enabled.
 *     - RT_USING_CAN must be enabled.
 *     - RT_UTEST_CAN_FRAMEWORK must be enabled.
 * - Environmental Assumptions: a thread context and a running tick source.
 *   The TX deadline must allow the two worker threads and the coordinator to
 *   be scheduled; a very short deadline cannot support this concurrency test.
 *
 * Expected Results:
 * - Final output: "[ PASSED ] [ result ] testcase
 *   (components.drivers.can.can_framework_tc)".
 * - No real CAN hardware is accessed and no frame is transmitted on a bus.
 */

#include <rtthread.h>
#include <rtsched.h>
#include <rtdevice.h>
#include <drivers/dev_can.h>
#include "utest.h"

#ifdef RT_UTEST_CAN_FRAMEWORK

#define CAN_TC_DEV_NAME     "can_tc0"
#define CAN_TC_TX_MAILBOXES 2
#define CAN_TC_RX_BOXES     4
#define CAN_TC_TX_ID        0x123
#define CAN_TC_RX_ID        0x321
#define CAN_TC_DLC          8
#define CAN_TC_RX_SEED      0x40

/**
 * @brief Progress bit for a newly submitted private frame (bits 0-1).
 * @param mailbox Test mailbox index, 0 or 1.
 */
#define CAN_TC_TX_SUBMITTED(mailbox) (1UL << (mailbox))
/**
 * @brief Progress bit for a completed writer call (bits 2-3).
 * @param mailbox Test mailbox index, 0 or 1.
 */
#define CAN_TC_TX_RETURNED(mailbox)  (1UL << ((mailbox) + 2U))
#define CAN_TC_TX_EXIT               (1UL << 4) /**< Coordinator permits worker exit. */
/**
 * @brief Progress bit acknowledging the end of test-data access (bits 5-6).
 * @param mailbox Test mailbox index, 0 or 1.
 */
#define CAN_TC_TX_EXITED(mailbox)    (1UL << ((mailbox) + 5U))
#define CAN_TC_TX_WORKER_STACK       2048       /**< Test writer stack size in bytes. */

/** Simulated BSP state, reached through rt_device.user_data. */
struct can_tc_sim
{
    rt_ssize_t sendmsg_result;    /**< Result returned by the simulated sendmsg. */
    rt_ssize_t sendmsg_nb_result; /**< Result returned by the simulated sendmsg_nonblocking. */
    rt_uint32_t nb_mailbox;       /**< Mailbox reported by a successful non-blocking submit. */
    rt_uint32_t sendmsg_calls;    /**< Number of blocking submits accepted by the simulation. */
    rt_uint32_t sendmsg_nb_calls; /**< Number of non-blocking submits accepted by the simulation. */
    rt_uint32_t rx_calls;         /**< Number of simulated recvmsg calls. */
    rt_uint32_t start_count;      /**< Number of START(1) requests. */
    rt_uint32_t stop_count;       /**< Number of START(0) requests. */
    rt_uint32_t abort_count;      /**< Number of valid ABORT_TX requests. */
    rt_event_t submit_event;      /**< Optional progress event for the concurrent TX test. */
};

/** Context for one private-mailbox test writer. */
struct can_tc_priv_writer
{
    rt_device_t dev;       /**< Virtual CAN device owned by the coordinator. */
    rt_event_t progress;   /**< Shared test progress and exit notifications. */
    rt_uint32_t mailbox;   /**< Private mailbox selected by this writer. */
    rt_ssize_t result;     /**< Return value published before the RETURNED bit. */
};

static struct rt_can_device can_tc_dev;
static struct can_tc_sim can_tc_sim;

/**
 * @brief Apply the simulated controller configuration.
 */
static rt_err_t can_tc_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    RT_UNUSED(can);

    cfg->baud_rate = CAN500kBaud;
    cfg->msgboxsz = CAN_TC_RX_BOXES;
    cfg->sndboxnumber = CAN_TC_TX_MAILBOXES;
    cfg->mode = RT_CAN_MODE_NORMAL;
    cfg->privmode = RT_CAN_MODE_NOPRIV;
    cfg->ticks = RT_TICK_PER_SECOND;
#ifdef RT_CAN_USING_HDR
    cfg->maxhdr = 0;
#endif /* RT_CAN_USING_HDR */

    return RT_EOK;
}

/**
 * @brief Simulate the BSP control surface required by the Generic CAN lifecycle.
 *
 * START(0) returns success on purpose: the framework requires a BSP-confirmed
 * controller stop before it retires stale TX ownership during final close.
 */
static rt_err_t can_tc_control(struct rt_can_device *can, int cmd, void *arg)
{
    struct can_tc_sim *sim = (struct can_tc_sim *)can->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SET_INT:
    case RT_DEVICE_CTRL_CLR_INT:
        return RT_EOK;

    case RT_CAN_CMD_START:
        if ((rt_ubase_t)arg != 0)
        {
            sim->start_count++;
        }
        else
        {
            sim->stop_count++;
        }
        return RT_EOK;

    case RT_CAN_CMD_GET_STATUS:
    case RT_CAN_CMD_SET_PRIV:
        return RT_EOK;

    case RT_CAN_CMD_ABORT_TX:
        sim->abort_count++;
        return RT_EOK;

    default:
        return -RT_ENOSYS;
    }
}

/**
 * @brief Simulate one blocking hardware submit with a controllable result.
 */
static rt_ssize_t can_tc_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    struct can_tc_sim *sim = (struct can_tc_sim *)can->parent.user_data;

    RT_UNUSED(buf);

    sim->sendmsg_calls++;
    if (sim->submit_event != RT_NULL && sim->sendmsg_result == RT_EOK)
    {
        /* The coordinator injects the terminal through the same TX lock domain. */
        (void)rt_event_send(sim->submit_event, CAN_TC_TX_SUBMITTED(boxno));
    }
    return sim->sendmsg_result;
}

/**
 * @brief Simulate one non-blocking hardware submit with a controllable result.
 */
static rt_ssize_t can_tc_sendmsg_nonblocking(struct rt_can_device *can, const void *buf,
                                             rt_uint32_t *mailbox)
{
    struct can_tc_sim *sim = (struct can_tc_sim *)can->parent.user_data;

    RT_UNUSED(buf);

    sim->sendmsg_nb_calls++;
    if (sim->sendmsg_nb_result == RT_EOK)
    {
        *mailbox = sim->nb_mailbox;
    }

    return sim->sendmsg_nb_result;
}

/**
 * @brief Simulate one hardware RX read with a deterministic frame.
 */
static rt_ssize_t can_tc_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    struct can_tc_sim *sim = (struct can_tc_sim *)can->parent.user_data;
    struct rt_can_msg *msg = (struct rt_can_msg *)buf;
    rt_uint32_t i;

    RT_UNUSED(fifo);

    sim->rx_calls++;

    rt_memset(msg, 0, sizeof(*msg));
    msg->id = CAN_TC_RX_ID;
    msg->ide = RT_CAN_STDID;
    msg->rtr = RT_CAN_DTR;
    msg->len = CAN_TC_DLC;
    for (i = 0; i < CAN_TC_DLC; i++)
    {
        msg->data[i] = (rt_uint8_t)(CAN_TC_RX_SEED + i);
    }

    return (rt_ssize_t)sizeof(*msg);
}

static const struct rt_can_ops can_tc_ops = {
    can_tc_configure,
    can_tc_control,
    can_tc_sendmsg,
    can_tc_recvmsg,
    can_tc_sendmsg_nonblocking,
};

/**
 * @brief Register the virtual device once and reset the simulated BSP state.
 */
static rt_err_t can_framework_init(void)
{
    rt_memset(&can_tc_sim, 0, sizeof(can_tc_sim));

    if (rt_device_find(CAN_TC_DEV_NAME) != RT_NULL)
    {
        /* Reuse the device so the suite can run more than once in one boot. */
        return RT_EOK;
    }

    rt_memset(&can_tc_dev, 0, sizeof(can_tc_dev));
    can_tc_dev.config.baud_rate = CAN500kBaud;
    can_tc_dev.config.msgboxsz = CAN_TC_RX_BOXES;
    can_tc_dev.config.sndboxnumber = CAN_TC_TX_MAILBOXES;
    can_tc_dev.config.mode = RT_CAN_MODE_NORMAL;
    can_tc_dev.config.privmode = RT_CAN_MODE_NOPRIV;
    can_tc_dev.config.ticks = RT_TICK_PER_SECOND;
#ifdef RT_CAN_USING_HDR
    can_tc_dev.config.maxhdr = 0;
#endif /* RT_CAN_USING_HDR */

    return rt_hw_can_register(&can_tc_dev, CAN_TC_DEV_NAME, &can_tc_ops, &can_tc_sim);
}

/**
 * @brief Drop every outstanding user reference so the next run starts cleanly.
 */
static rt_err_t can_framework_cleanup(void)
{
    rt_device_t dev = rt_device_find(CAN_TC_DEV_NAME);

    if (dev != RT_NULL)
    {
        while (dev->ref_count > 0)
        {
            if (rt_device_close(dev) != RT_EOK)
            {
                break;
            }
        }
    }

    return RT_EOK;
}

/**
 * @brief Check registration and lookup of the virtual CAN device.
 */
static void test_register_and_find(void)
{
    rt_device_t dev = rt_device_find(CAN_TC_DEV_NAME);

    uassert_not_null(dev);
    uassert_ptr_equal(dev, &can_tc_dev.parent);
    uassert_int_equal(dev->type, RT_Device_Class_CAN);
    uassert_int_equal(dev->ref_count, 0);
}

/**
 * @brief Check open/close reference counting and the reopen path.
 */
static void test_open_close_reopen(void)
{
    rt_device_t dev = rt_device_find(CAN_TC_DEV_NAME);
    rt_uint32_t stop_count = can_tc_sim.stop_count;

    uassert_not_null(dev);

    uassert_int_equal(rt_device_open(dev, RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX), RT_EOK);
    uassert_int_equal(dev->ref_count, 1);
    uassert_not_null(can_tc_dev.can_rx);
    uassert_not_null(can_tc_dev.can_tx);

    /* The Generic runtimes live until the last user closes the device. */
    uassert_int_equal(rt_device_open(dev, RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX), RT_EOK);
    uassert_int_equal(dev->ref_count, 2);
    uassert_int_equal(rt_device_close(dev), RT_EOK);
    uassert_int_equal(dev->ref_count, 1);
    uassert_not_null(can_tc_dev.can_rx);
    uassert_not_null(can_tc_dev.can_tx);

    uassert_int_equal(rt_device_close(dev), RT_EOK);
    uassert_int_equal(dev->ref_count, 0);
    uassert_null(can_tc_dev.can_rx);
    uassert_null(can_tc_dev.can_tx);
    /* Final close must have asked the BSP to stop the controller. */
    uassert_int_equal(can_tc_sim.stop_count, stop_count + 1);

    /* A closed device must be fully reusable. */
    uassert_int_equal(rt_device_open(dev, RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX), RT_EOK);
    uassert_int_equal(dev->ref_count, 1);
    uassert_not_null(can_tc_dev.can_rx);
    uassert_not_null(can_tc_dev.can_tx);
    uassert_int_equal(rt_device_close(dev), RT_EOK);
    uassert_int_equal(dev->ref_count, 0);
}

/**
 * @brief Check RX/TX admission preservation when a device is opened again.
 */
static void test_open_direction_expansion(void)
{
    rt_device_t dev = rt_device_find(CAN_TC_DEV_NAME);
    struct rt_can_msg msg;
    rt_uint16_t both = RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX;

    uassert_not_null(dev);

    /* Open RX first, then extend to RX | TX. */
    uassert_int_equal(rt_device_open(dev, RT_DEVICE_FLAG_INT_RX), RT_EOK);
    uassert_int_equal(rt_device_open(dev, both), RT_EOK);

    uassert_int_equal(dev->ref_count, 2);
    uassert_int_equal(dev->open_flag & both, both);
    uassert_not_null(can_tc_dev.can_rx);
    uassert_not_null(can_tc_dev.can_tx);

    /* Closing one reference must not disable the existing RX path. */
    uassert_int_equal(rt_device_close(dev), RT_EOK);
    uassert_int_equal(dev->ref_count, 1);

    rt_hw_can_isr(&can_tc_dev, RT_CAN_EVENT_RX_IND | (0 << 8));

    rt_memset(&msg, 0, sizeof(msg));
    msg.hdr_index = -1;

    uassert_int_equal(rt_device_read(dev, 0, &msg, sizeof(msg)), sizeof(msg));
    uassert_int_equal(msg.id, CAN_TC_RX_ID);

    uassert_int_equal(rt_device_close(dev), RT_EOK);
    uassert_int_equal(dev->ref_count, 0);

    /* Open TX first, then extend to RX | TX. */
    uassert_int_equal(rt_device_open(dev, RT_DEVICE_FLAG_INT_TX), RT_EOK);
    uassert_int_equal(rt_device_open(dev, both), RT_EOK);

    uassert_int_equal(dev->ref_count, 2);
    uassert_int_equal(dev->open_flag & both, both);
    uassert_not_null(can_tc_dev.can_rx);
    uassert_not_null(can_tc_dev.can_tx);

    /* Verify the original TX direction remains usable. */
    rt_memset(&msg, 0, sizeof(msg));
    msg.id = CAN_TC_TX_ID;
    msg.len = CAN_TC_DLC;
    msg.nonblocking = 1;

    can_tc_sim.sendmsg_nb_result = RT_EOK;
    can_tc_sim.nb_mailbox = 0;

    uassert_int_equal(rt_device_write(dev, 0, &msg, sizeof(msg)), sizeof(msg));

    rt_hw_can_isr(&can_tc_dev, RT_CAN_EVENT_TX_DONE | (0 << 8));
    uassert_int_equal(rt_can_tx_drain(&can_tc_dev, 0), RT_EOK);

    /* Verify the newly enabled RX direction works. */
    rt_hw_can_isr(&can_tc_dev, RT_CAN_EVENT_RX_IND | (0 << 8));

    rt_memset(&msg, 0, sizeof(msg));
    msg.hdr_index = -1;

    uassert_int_equal(rt_device_read(dev, 0, &msg, sizeof(msg)), sizeof(msg));
    uassert_int_equal(msg.id, CAN_TC_RX_ID);

    uassert_int_equal(rt_device_close(dev), RT_EOK);
    uassert_int_equal(rt_device_close(dev), RT_EOK);
    uassert_int_equal(dev->ref_count, 0);
}

/**
 * @brief Check START admission gating, abort forwarding and send error propagation.
 */
static void test_tx_admission_and_errors(void)
{
    rt_device_t dev = rt_device_find(CAN_TC_DEV_NAME);
    struct rt_can_msg msg;
    rt_uint32_t send_count;

    uassert_not_null(dev);
    uassert_int_equal(rt_device_open(dev, RT_DEVICE_FLAG_INT_TX), RT_EOK);

    rt_memset(&msg, 0, sizeof(msg));
    msg.id = CAN_TC_TX_ID;
    msg.len = CAN_TC_DLC;

    /* START(0) closes Generic TX admission without touching the BSP mailbox. */
    uassert_int_equal(rt_device_control(dev, RT_CAN_CMD_START, (void *)0), RT_EOK);
    send_count = can_tc_sim.sendmsg_calls;
    uassert_int_equal(rt_device_write(dev, 0, &msg, sizeof(msg)), -RT_EBUSY);
    uassert_int_equal(can_tc_sim.sendmsg_calls, send_count);

    /* START(1) opens admission again. */
    uassert_int_equal(rt_device_control(dev, RT_CAN_CMD_START, (void *)1), RT_EOK);
    uassert_int_equal(can_tc_sim.start_count, 1);

    /* A blocking submit error must reach the caller unchanged. */
    can_tc_sim.sendmsg_result = -RT_EIO;
    send_count = can_tc_sim.sendmsg_calls;
    uassert_int_equal(rt_device_write(dev, 0, &msg, sizeof(msg)), -RT_EIO);
    uassert_int_equal(can_tc_sim.sendmsg_calls, send_count + 1);

    /* The non-blocking path reports its own BSP error. */
    msg.nonblocking = 1;
    can_tc_sim.sendmsg_result = RT_EOK;
    can_tc_sim.sendmsg_nb_result = -RT_EIO;
    uassert_int_equal(rt_device_write(dev, 0, &msg, sizeof(msg)), -RT_EIO);

    /* A mailbox outside the Generic-visible range is rejected by the framework. */
    can_tc_sim.sendmsg_nb_result = RT_EOK;
    can_tc_sim.nb_mailbox = CAN_TC_TX_MAILBOXES;
    uassert_int_equal(rt_device_write(dev, 0, &msg, sizeof(msg)), -RT_ERROR);

    uassert_int_equal(rt_device_control(dev, RT_CAN_CMD_ABORT_TX, (void *)0), RT_EOK);
    uassert_int_equal(can_tc_sim.abort_count, 1);
    uassert_int_equal(rt_device_control(dev, RT_CAN_CMD_ABORT_TX,
                                        (void *)(rt_ubase_t)CAN_TC_TX_MAILBOXES),
                      -RT_EINVAL);

    uassert_int_equal(rt_device_close(dev), RT_EOK);
}

/**
 * @brief Check that a permanently busy controller ends in -RT_ETIMEOUT.
 *
 * No mailbox is claimed by Generic CAN in this case, so the device can be
 * closed afterwards without any abandoned hardware ownership.
 */
static void test_tx_busy_timeout(void)
{
    rt_device_t dev = rt_device_find(CAN_TC_DEV_NAME);
    struct rt_can_msg msg;
    rt_uint32_t send_count;

    uassert_not_null(dev);
    uassert_int_equal(rt_device_open(dev, RT_DEVICE_FLAG_INT_TX), RT_EOK);

    rt_memset(&msg, 0, sizeof(msg));
    msg.id = CAN_TC_TX_ID;
    msg.len = CAN_TC_DLC;
    msg.nonblocking = 0;

    can_tc_sim.sendmsg_result = -RT_EBUSY;
    send_count = can_tc_sim.sendmsg_calls;
    uassert_int_equal(rt_device_write(dev, 0, &msg, sizeof(msg)), -RT_ETIMEOUT);
    /* Every visible mailbox was probed at least once before the deadline. */
    uassert_value_greater_equal(can_tc_sim.sendmsg_calls, send_count + CAN_TC_TX_MAILBOXES);

    can_tc_sim.sendmsg_result = RT_EOK;
    uassert_int_equal(rt_device_close(dev), RT_EOK);
}

/**
 * @brief Write one private frame and report the result before releasing test data.
 * @param parameter Coordinator-owned writer context, valid until the exit acknowledgement.
 */
static void can_tc_priv_write_entry(void *parameter)
{
    /* Writer context and frame are private to this worker until RETURNED. */
    struct can_tc_priv_writer *writer = (struct can_tc_priv_writer *)parameter;
    struct rt_can_msg msg;

    rt_memset(&msg, 0, sizeof(msg));
    msg.id = CAN_TC_TX_ID;
    msg.len = CAN_TC_DLC;
    msg.priv = writer->mailbox;
    writer->result = rt_device_write(writer->dev, 0, &msg, sizeof(msg));
    (void)rt_event_send(writer->progress, CAN_TC_TX_RETURNED(writer->mailbox));

    /* Keep the thread object alive until the coordinator no longer inspects it. */
    (void)rt_event_recv(writer->progress, CAN_TC_TX_EXIT, RT_EVENT_FLAG_OR, RT_WAITING_FOREVER, RT_NULL);
    (void)rt_event_send(writer->progress, CAN_TC_TX_EXITED(writer->mailbox));
}

/**
 * @brief Wait until a started writer is blocked inside its CAN write.
 * @param thread Started test thread, kept alive by the exit handshake.
 * @param progress Shared test progress event.
 * @param mailbox Target mailbox, used to detect a writer that already returned.
 * @return RT_EOK if suspended before returning, or a negative test error.
 */
static rt_err_t can_tc_wait_priv_writer(rt_thread_t thread, rt_event_t progress, rt_uint32_t mailbox)
{
    /* Bound the setup observation by the same configured TX deadline. */
    rt_tick_t start = rt_tick_get();
    /* Scheduler lock state and the protected snapshot of the worker status. */
    rt_sched_lock_level_t level;
    rt_uint8_t state;

    do
    {
        if (rt_event_recv(progress, CAN_TC_TX_RETURNED(mailbox), RT_EVENT_FLAG_OR, 0, RT_NULL) == RT_EOK)
        {
            return -RT_ERROR;
        }
        /* RT_SCHED_CTX is the public scheduler context; read it under its lock. */
        rt_sched_lock(&level);
        state = RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_MASK;
        rt_sched_unlock(level);
        if (state & RT_THREAD_SUSPEND_MASK)
        {
            return RT_EOK;
        }
        rt_thread_delay(1);
    } while ((rt_tick_get() - start) < RT_CANSND_MSG_TIMEOUT);

    return -RT_ETIMEOUT;
}

/**
 * @brief Verify that releasing one private mailbox cannot wake only the wrong writer.
 *
 * Two timed-out submissions retain both slots until their late terminals. The
 * mailbox 1 writer has higher priority and is suspended first, so either PRIO
 * or FIFO on the old shared semaphore could consume mailbox 0's sole wake.
 * Mailbox 0 must be submitted and completed before mailbox 1 is released.
 */
static void test_private_mailbox_wait(void)
{
    /* Virtual device reference and the frame used to leave both mailboxes owned. */
    rt_device_t dev = rt_device_find(CAN_TC_DEV_NAME);
    struct rt_can_msg msg;
    /* Test event and worker contexts must live until both exit acknowledgements. */
    struct rt_event progress;
    struct can_tc_priv_writer writers[CAN_TC_TX_MAILBOXES];
    /* Dynamic worker handle; the exit handshake prevents premature deletion. */
    rt_thread_t thread;
    /* Masks track only successfully started writers for failure-path cleanup. */
    rt_uint32_t returned_mask = 0;
    rt_uint32_t exited_mask = 0;
    /* Index of the private mailbox being prepared, released or cleaned up. */
    rt_uint32_t mailbox;
    /* Operation result used for assertion and cleanup decisions. */
    rt_err_t result;
    /* Initial write result must show a timeout while retaining ownership. */
    rt_ssize_t written;

    uassert_not_null(dev);
    if (dev == RT_NULL)
    {
        return;
    }
    result = rt_device_open(dev, RT_DEVICE_FLAG_INT_TX);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }
    result = rt_event_init(&progress, "cantc", RT_IPC_FLAG_PRIO);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        (void)rt_device_close(dev);
        return;
    }
    result = rt_device_control(dev, RT_CAN_CMD_SET_PRIV, (void *)(rt_ubase_t)RT_CAN_MODE_PRIV);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        goto out;
    }

    can_tc_sim.sendmsg_result = RT_EOK;
    rt_memset(&msg, 0, sizeof(msg));
    msg.id = CAN_TC_TX_ID;
    msg.len = CAN_TC_DLC;
    for (mailbox = 0; mailbox < CAN_TC_TX_MAILBOXES; mailbox++)
    {
        msg.priv = mailbox;
        /* No terminal is injected yet: timeout must leave the slot hardware-owned. */
        written = rt_device_write(dev, 0, &msg, sizeof(msg));
        uassert_int_equal(written, -RT_ETIMEOUT);
        if (written != -RT_ETIMEOUT)
        {
            goto out;
        }
    }
    uassert_int_equal(can_tc_dev.status.sndchange & 0x3U, 0x3U);
    can_tc_sim.submit_event = &progress;

    /* Start mailbox 1 first and give it the higher priority. */
    for (mailbox = CAN_TC_TX_MAILBOXES; mailbox > 0; )
    {
        mailbox--;
        writers[mailbox].dev = dev;
        writers[mailbox].progress = &progress;
        writers[mailbox].mailbox = mailbox;
        writers[mailbox].result = -RT_ERROR;
        thread = rt_thread_create(mailbox == 0 ? "cantx0" : "cantx1",
                                  can_tc_priv_write_entry, &writers[mailbox], CAN_TC_TX_WORKER_STACK,
                                  RT_THREAD_PRIORITY_MAX / 2 + (mailbox == 0 ? 1 : 0), 1);
        uassert_not_null(thread);
        if (thread == RT_NULL)
        {
            goto out;
        }
        result = rt_thread_startup(thread);
        uassert_int_equal(result, RT_EOK);
        if (result != RT_EOK)
        {
            (void)rt_thread_delete(thread);
            goto out;
        }
        returned_mask |= CAN_TC_TX_RETURNED(mailbox);
        exited_mask |= CAN_TC_TX_EXITED(mailbox);
        result = can_tc_wait_priv_writer(thread, &progress, mailbox);
        uassert_int_equal(result, RT_EOK);
        if (result != RT_EOK)
        {
            goto out;
        }
    }

    for (mailbox = 0; mailbox < CAN_TC_TX_MAILBOXES; mailbox++)
    {
        /* The late terminal of the timed-out owner releases only this mailbox. */
        rt_hw_can_isr(&can_tc_dev, RT_CAN_EVENT_TX_DONE | (mailbox << 8));
        result = rt_event_recv(&progress, CAN_TC_TX_SUBMITTED(mailbox), RT_EVENT_FLAG_OR,
                               RT_CANSND_MSG_TIMEOUT, RT_NULL);
        uassert_int_equal(result, RT_EOK);
        if (result != RT_EOK)
        {
            goto out;
        }
        if (mailbox == 0)
        {
            /* Mailbox 1 is still busy: its writer must not submit or return yet. */
            uassert_int_equal(rt_event_recv(&progress, CAN_TC_TX_SUBMITTED(1) | CAN_TC_TX_RETURNED(1),
                                            RT_EVENT_FLAG_OR, 0, RT_NULL), -RT_ETIMEOUT);
        }
        /* Now complete the newly submitted frame for this writer. */
        rt_hw_can_isr(&can_tc_dev, RT_CAN_EVENT_TX_DONE | (mailbox << 8));
        result = rt_event_recv(&progress, CAN_TC_TX_RETURNED(mailbox), RT_EVENT_FLAG_OR,
                               RT_CANSND_MSG_TIMEOUT, RT_NULL);
        uassert_int_equal(result, RT_EOK);
        if (result != RT_EOK)
        {
            goto out;
        }
        uassert_int_equal(writers[mailbox].result, sizeof(msg));
    }
    uassert_int_equal(rt_can_tx_drain(&can_tc_dev, 0), RT_EOK);

out:
    /* Writers have finite deadlines. Join them before forcing STOP or closing. */
    if (returned_mask != 0)
    {
        (void)rt_event_recv(&progress, returned_mask, RT_EVENT_FLAG_AND, RT_WAITING_FOREVER, RT_NULL);
        (void)rt_event_send(&progress, CAN_TC_TX_EXIT);
        (void)rt_event_recv(&progress, exited_mask, RT_EVENT_FLAG_AND, RT_WAITING_FOREVER, RT_NULL);
    }
    can_tc_sim.submit_event = RT_NULL;
    /* On failure, the fake controller can STOP and retire any orphaned requests. */
    if (rt_can_tx_drain(&can_tc_dev, 0) != RT_EOK)
    {
        uassert_int_equal(rt_device_control(dev, RT_CAN_CMD_FORCE_STOP, RT_NULL), RT_EOK);
        uassert_int_equal(rt_can_tx_drain(&can_tc_dev, 0), RT_EOK);
    }
    uassert_int_equal(rt_device_control(dev, RT_CAN_CMD_SET_PRIV, (void *)(rt_ubase_t)RT_CAN_MODE_NOPRIV), RT_EOK);
    uassert_int_equal(rt_event_detach(&progress), RT_EOK);
    uassert_int_equal(rt_device_close(dev), RT_EOK);
}

/**
 * @brief Check non-blocking ownership retirement through a simulated terminal.
 */
static void test_nonblocking_terminal(void)
{
    rt_device_t dev = rt_device_find(CAN_TC_DEV_NAME);
    struct rt_can_msg msg;
    rt_uint32_t sndpkg;

    uassert_not_null(dev);
    uassert_int_equal(rt_device_open(dev, RT_DEVICE_FLAG_INT_TX), RT_EOK);

    rt_memset(&msg, 0, sizeof(msg));
    msg.id = CAN_TC_TX_ID;
    msg.len = CAN_TC_DLC;
    msg.nonblocking = 1;

    can_tc_sim.sendmsg_nb_result = RT_EOK;
    can_tc_sim.nb_mailbox = 0;
    sndpkg = can_tc_dev.status.sndpkg;

    uassert_int_equal(rt_device_write(dev, 0, &msg, sizeof(msg)), sizeof(msg));

    /* The mailbox stays hardware-owned until the BSP publishes its terminal. */
    uassert_int_equal(rt_can_tx_drain(&can_tc_dev, 0), -RT_ETIMEOUT);
    rt_hw_can_isr(&can_tc_dev, RT_CAN_EVENT_TX_DONE | (0 << 8));
    uassert_int_equal(rt_can_tx_drain(&can_tc_dev, 0), RT_EOK);
    uassert_int_equal(can_tc_dev.status.sndpkg, sndpkg + 1);

    uassert_int_equal(rt_device_close(dev), RT_EOK);
}

/**
 * @brief Check the simulated RX ISR to software FIFO to read path.
 */
static void test_rx_fifo(void)
{
    rt_device_t dev = rt_device_find(CAN_TC_DEV_NAME);
    struct rt_can_msg msg;
    rt_uint32_t rx_calls;

    uassert_not_null(dev);
    uassert_int_equal(rt_device_open(dev, RT_DEVICE_FLAG_INT_RX), RT_EOK);

    rx_calls = can_tc_sim.rx_calls;
    rt_hw_can_isr(&can_tc_dev, RT_CAN_EVENT_RX_IND | (0 << 8));
    uassert_int_equal(can_tc_sim.rx_calls, rx_calls + 1);

    rt_memset(&msg, 0, sizeof(msg));
    /* -1 selects the global RX FIFO when RT_CAN_USING_HDR is enabled. */
    msg.hdr_index = -1;
    uassert_int_equal(rt_device_read(dev, 0, &msg, sizeof(msg)), sizeof(msg));
    uassert_int_equal(msg.id, CAN_TC_RX_ID);
    uassert_int_equal(msg.ide, RT_CAN_STDID);
    uassert_int_equal(msg.len, CAN_TC_DLC);
    uassert_int_equal(msg.data[0], CAN_TC_RX_SEED);
    uassert_int_equal(msg.data[CAN_TC_DLC - 1], CAN_TC_RX_SEED + CAN_TC_DLC - 1);

    uassert_int_equal(rt_device_close(dev), RT_EOK);
}

/**
 * @brief Run every Generic CAN framework unit.
 */
static void can_framework_tc(void)
{
    UTEST_UNIT_RUN(test_register_and_find);
    UTEST_UNIT_RUN(test_open_close_reopen);
    UTEST_UNIT_RUN(test_open_direction_expansion);
    UTEST_UNIT_RUN(test_tx_admission_and_errors);
    UTEST_UNIT_RUN(test_tx_busy_timeout);
    UTEST_UNIT_RUN(test_private_mailbox_wait);
    UTEST_UNIT_RUN(test_nonblocking_terminal);
    UTEST_UNIT_RUN(test_rx_fifo);
}

UTEST_TC_EXPORT(can_framework_tc, "components.drivers.can.can_framework_tc",
                can_framework_init, can_framework_cleanup, 30);

#endif /* RT_UTEST_CAN_FRAMEWORK */
