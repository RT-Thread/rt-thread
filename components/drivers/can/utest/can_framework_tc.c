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
 * - Report an RX event through rt_hw_can_isr() and read the frame back.
 *
 * Verification Metrics:
 * - rt_device_find() returns the registered device with the CAN class.
 * - ref_count returns to zero after close and rt_device_open() works again.
 * - START(0) rejects TX with -RT_EBUSY and START(1) restores admission.
 * - BSP send errors are propagated unchanged to rt_device_write().
 * - A busy mailbox returns -RT_ETIMEOUT once the TX deadline expires.
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
 *
 * Expected Results:
 * - Final output: "[ PASSED ] [ result ] testcase
 *   (components.drivers.can.can_framework_tc)".
 * - No real CAN hardware is accessed and no frame is transmitted on a bus.
 */

#include <rtthread.h>
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
    RT_UNUSED(boxno);

    sim->sendmsg_calls++;
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
    UTEST_UNIT_RUN(test_tx_admission_and_errors);
    UTEST_UNIT_RUN(test_tx_busy_timeout);
    UTEST_UNIT_RUN(test_nonblocking_terminal);
    UTEST_UNIT_RUN(test_rx_fifo);
}

UTEST_TC_EXPORT(can_framework_tc, "components.drivers.can.can_framework_tc",
                can_framework_init, can_framework_cleanup, 30);

#endif /* RT_UTEST_CAN_FRAMEWORK */
