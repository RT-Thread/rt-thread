/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-02     CYFS         add CAN send and receive utest
 * 2026-07-17     CYFS         add baud-rate matrix and CAN FD coverage
 */

/**
 * Test Case Name: CAN Send and Receive Test
 *
 * Test Objectives:
 * - Verify CAN blocking send and interrupt receive paths.
 * - Verify standard arbitration rates with self-loopback or two connected CAN
 *   devices. An external node uses one selected rate because it cannot be
 *   switched automatically.
 * - Optionally verify CAN FD payloads, raw DLC handling, and bit-rate switching.
 * - Optionally verify the nonblocking send acceptance path.
 *
 * Test Topologies:
 * - Single CAN self-loopback.
 * - Single CAN connected to an external CAN node.
 * - Two CAN devices connected to the same bus.
 *
 * Expected Results:
 * - Every configured phase can send and receive the expected frame without
 *   changing the device's original configuration after cleanup.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/dev_can.h>
#include "utest.h"

#ifdef RT_UTEST_CAN

#if defined(RT_CAN_TC_USING_CANFD) && !defined(RT_CAN_USING_CANFD)
#error "RT_CAN_TC_USING_CANFD requires RT_CAN_USING_CANFD"
#endif

#define CAN_TC_FRAME_ID_BASE                 0x321
#define CAN_TC_CLASSIC_DLC                   CAN_MSG_8BYTES
#define CAN_TC_FD_FRAME_ID_BASE              (CAN_TC_FRAME_ID_BASE + 3)
#define CAN_TC_REVERSE_FD_FRAME_ID_BASE      (CAN_TC_FRAME_ID_BASE + 5)
#define CAN_TC_TX_SEED                       0x10
#define CAN_TC_RX_SEED                       0x20
#define CAN_TC_EXTERNAL_TX_DRAIN_MS          50

#ifndef RT_CAN_TC_TIMEOUT_MS
#define RT_CAN_TC_TIMEOUT_MS                 1000
#endif

#ifndef RT_CAN_TC_BAUD_RATE
#define RT_CAN_TC_BAUD_RATE                  CAN500kBaud
#endif

#ifndef RT_CAN_TC_TX_FRAME_ID
#define RT_CAN_TC_TX_FRAME_ID                CAN_TC_FRAME_ID_BASE
#endif

#ifndef RT_CAN_TC_RX_FRAME_ID
#define RT_CAN_TC_RX_FRAME_ID                (CAN_TC_FRAME_ID_BASE + 1)
#endif

#ifndef RT_CAN_TC_NONBLOCKING_TX_FRAME_ID
#define RT_CAN_TC_NONBLOCKING_TX_FRAME_ID    (CAN_TC_FRAME_ID_BASE + 2)
#endif

#ifndef RT_CAN_TC_EXTERNAL_READY_DELAY_MS
#define RT_CAN_TC_EXTERNAL_READY_DELAY_MS    1000
#endif

#ifdef RT_CAN_TC_USING_CANFD
#ifndef RT_CAN_TC_CANFD_DATA_BAUD_RATE
#define RT_CAN_TC_CANFD_DATA_BAUD_RATE       2000000
#endif
#ifndef RT_CAN_TC_CANFD_DATA_LENGTH
#define RT_CAN_TC_CANFD_DATA_LENGTH          16
#endif
#ifdef RT_CAN_TC_CANFD_BRS
#define CAN_TC_SELECTED_FD_BRS               RT_TRUE
#else
#define CAN_TC_SELECTED_FD_BRS               RT_FALSE
#endif
#endif

#if defined(RT_CAN_TC_USING_DUAL_DEVICE)
#define CAN_TC_MAX_RECEIVE_WAITS             31
#elif defined(RT_CAN_TC_USING_SELF_LOOPBACK)
#define CAN_TC_MAX_RECEIVE_WAITS             20
#elif defined(RT_CAN_TC_EXTERNAL_USING_RECEIVE_TEST)
#define CAN_TC_MAX_RECEIVE_WAITS             3
#else
#define CAN_TC_MAX_RECEIVE_WAITS             1
#endif

#define CAN_TC_RX_TIMEOUT_SECONDS            ((RT_CAN_TC_TIMEOUT_MS + 999) / 1000)
#ifdef RT_CAN_TC_USING_EXTERNAL_DEVICE
#define CAN_TC_READY_DELAY_SECONDS           ((RT_CAN_TC_EXTERNAL_READY_DELAY_MS + 999) / 1000)
#else
#define CAN_TC_READY_DELAY_SECONDS           0
#endif
#define CAN_TC_SUITE_TIMEOUT                 (10 + CAN_TC_READY_DELAY_SECONDS + \
                                              CAN_TC_MAX_RECEIVE_WAITS * CAN_TC_RX_TIMEOUT_SECONDS)

struct can_tc_context
{
    rt_device_t dev;
    struct rt_can_device *can;
    struct can_configure original_config;
    rt_err_t (*original_rx_indicate)(rt_device_t dev, rt_size_t size);
    struct rt_semaphore rx_sem;
    rt_bool_t sem_inited;
    rt_bool_t opened;
    rt_bool_t configuration_touched;
};

static struct can_tc_context can_tx_context;
static struct can_tc_context can_rx_context;
static struct can_tc_context *can_tx_ctx;
static struct can_tc_context *can_rx_ctx;

static void can_log_status(struct can_tc_context *context)
{
    rt_err_t result;
    struct rt_can_status status;

    rt_memset(&status, 0, sizeof(status));
    result = rt_device_control(context->dev, RT_CAN_CMD_GET_STATUS, &status);
    if (result == RT_EOK)
    {
        LOG_E("CAN status: txerr=%u, rxerr=%u, errcode=0x%08x, rxpkg=%u, rxdrop=%u, txpkg=%u, txdrop=%u",
              status.snderrcnt, status.rcverrcnt, status.errcode,
              status.rcvpkg, status.dropedrcvpkg,
              status.sndpkg, status.dropedsndpkg);
    }
    else
    {
        LOG_E("Get CAN status failed on %s, result=%d",
              context->dev->parent.name, result);
    }
}

static const rt_uint32_t can_tc_baud_rates[] =
{
    CAN10kBaud,
    CAN20kBaud,
    CAN50kBaud,
    CAN100kBaud,
    CAN125kBaud,
    CAN250kBaud,
    CAN500kBaud,
    CAN800kBaud,
    CAN1MBaud,
};

static const rt_uint8_t can_tc_dlc_to_length[] =
{
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 12, 16, 20, 24, 32, 48, 64,
};

static rt_bool_t can_is_standard_baud_rate(rt_uint32_t baud_rate)
{
    rt_size_t i;

    for (i = 0; i < sizeof(can_tc_baud_rates) / sizeof(can_tc_baud_rates[0]); i++)
    {
        if (can_tc_baud_rates[i] == baud_rate)
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

#if defined(RT_CAN_TC_USING_SELF_LOOPBACK) || defined(RT_CAN_TC_USING_DUAL_DEVICE)
static rt_bool_t can_baud_rate_is_selected(rt_uint32_t baud_rate)
{
    if (baud_rate == RT_CAN_TC_BAUD_RATE)
    {
        return RT_TRUE;
    }

    switch (baud_rate)
    {
    case CAN10kBaud:
#ifdef RT_CAN_TC_TEST_BAUD_RATE_10K
        return RT_TRUE;
#endif
        break;
    case CAN20kBaud:
#ifdef RT_CAN_TC_TEST_BAUD_RATE_20K
        return RT_TRUE;
#endif
        break;
    case CAN50kBaud:
#ifdef RT_CAN_TC_TEST_BAUD_RATE_50K
        return RT_TRUE;
#endif
        break;
    case CAN100kBaud:
#ifdef RT_CAN_TC_TEST_BAUD_RATE_100K
        return RT_TRUE;
#endif
        break;
    case CAN125kBaud:
#ifdef RT_CAN_TC_TEST_BAUD_RATE_125K
        return RT_TRUE;
#endif
        break;
    case CAN250kBaud:
#ifdef RT_CAN_TC_TEST_BAUD_RATE_250K
        return RT_TRUE;
#endif
        break;
    case CAN500kBaud:
#ifdef RT_CAN_TC_TEST_BAUD_RATE_500K
        return RT_TRUE;
#endif
        break;
    case CAN800kBaud:
#ifdef RT_CAN_TC_TEST_BAUD_RATE_800K
        return RT_TRUE;
#endif
        break;
    case CAN1MBaud:
#ifdef RT_CAN_TC_TEST_BAUD_RATE_1M
        return RT_TRUE;
#endif
        break;
    default:
        break;
    }

    return RT_FALSE;
}
#endif

static rt_err_t can_dlc_to_payload_length(rt_uint8_t dlc, rt_size_t *payload_length)
{
    if (dlc >= sizeof(can_tc_dlc_to_length) / sizeof(can_tc_dlc_to_length[0]))
    {
        return -RT_EINVAL;
    }

    *payload_length = can_tc_dlc_to_length[dlc];
    return RT_EOK;
}

#ifdef RT_CAN_TC_USING_CANFD
static rt_err_t can_payload_length_to_dlc(rt_size_t payload_length, rt_uint8_t *dlc)
{
    rt_size_t i;

    for (i = 0; i < sizeof(can_tc_dlc_to_length) / sizeof(can_tc_dlc_to_length[0]); i++)
    {
        if (can_tc_dlc_to_length[i] == payload_length)
        {
            *dlc = (rt_uint8_t)i;
            return RT_EOK;
        }
    }

    return -RT_EINVAL;
}
#endif

static struct can_tc_context *can_find_context(rt_device_t dev)
{
    if (can_tx_ctx != RT_NULL && can_tx_ctx->dev == dev)
    {
        return can_tx_ctx;
    }
    if (can_rx_ctx != RT_NULL && can_rx_ctx->dev == dev)
    {
        return can_rx_ctx;
    }

    return RT_NULL;
}

static rt_err_t can_rx_indicate(rt_device_t dev, rt_size_t size)
{
    struct can_tc_context *context;

    context = can_find_context(dev);
    if (context != RT_NULL && context->sem_inited && size >= sizeof(struct rt_can_msg))
    {
        rt_sem_release(&context->rx_sem);
    }

    return RT_EOK;
}

static rt_err_t can_fill_message(struct rt_can_msg *msg,
                                 rt_uint32_t id,
                                 rt_uint8_t seed,
                                 rt_uint8_t dlc,
                                 rt_bool_t fd_frame,
                                 rt_bool_t brs)
{
    rt_size_t i;
    rt_size_t payload_length;

    if (can_dlc_to_payload_length(dlc, &payload_length) != RT_EOK ||
        payload_length > sizeof(msg->data))
    {
        return -RT_EINVAL;
    }

    rt_memset(msg, 0, sizeof(*msg));
    msg->id = id;
    msg->ide = RT_CAN_STDID;
    msg->rtr = RT_CAN_DTR;
    msg->len = dlc;
    msg->hdr_index = -1;
#ifdef RT_CAN_USING_CANFD
    msg->fd_frame = fd_frame;
    msg->brs = brs;
#else
    RT_UNUSED(fd_frame);
    RT_UNUSED(brs);
#endif

    for (i = 0; i < payload_length; i++)
    {
        msg->data[i] = (rt_uint8_t)(seed + i);
    }

    return RT_EOK;
}

#if defined(RT_CAN_TC_USING_SELF_LOOPBACK) || \
    defined(RT_CAN_TC_USING_DUAL_DEVICE) || \
    defined(RT_CAN_TC_EXTERNAL_USING_RECEIVE_TEST)
static rt_bool_t can_message_equal(const struct rt_can_msg *expected,
                                   const struct rt_can_msg *actual)
{
    rt_size_t payload_length;

    if (expected->id != actual->id ||
        expected->ide != actual->ide ||
        expected->rtr != actual->rtr ||
        expected->len != actual->len)
    {
        return RT_FALSE;
    }

#ifdef RT_CAN_USING_CANFD
    if (expected->fd_frame != actual->fd_frame || expected->brs != actual->brs)
    {
        return RT_FALSE;
    }
#endif

    if (can_dlc_to_payload_length((rt_uint8_t)expected->len, &payload_length) != RT_EOK)
    {
        return RT_FALSE;
    }

    return rt_memcmp(expected->data, actual->data, payload_length) == 0;
}

static void can_drain_receive(struct can_tc_context *context)
{
    rt_size_t i;
    rt_size_t limit;
    struct rt_can_msg msg;

    limit = context->can->config.msgboxsz;
    if (limit == 0)
    {
        limit = RT_CANMSG_BOX_SZ;
    }

    for (i = 0; i < limit; i++)
    {
        rt_ssize_t read_size;

        rt_memset(&msg, 0, sizeof(msg));
        msg.hdr_index = -1;
        read_size = rt_device_read(context->dev, 0, &msg, sizeof(msg));
        if (read_size != sizeof(msg))
        {
            break;
        }
    }

    for (i = 0; i < limit; i++)
    {
        if (rt_sem_take(&context->rx_sem, 0) != RT_EOK)
        {
            break;
        }
    }
}

#if defined(RT_CAN_TC_USING_SELF_LOOPBACK) || \
    defined(RT_CAN_TC_USING_DUAL_DEVICE) || \
    !defined(RT_CAN_TC_USING_CANFD)
static rt_err_t can_receive_expected(struct can_tc_context *context,
                                     const struct rt_can_msg *expected)
{
    rt_tick_t start;
    rt_tick_t timeout;

    timeout = rt_tick_from_millisecond(RT_CAN_TC_TIMEOUT_MS);
    if (timeout == 0)
    {
        timeout = 1;
    }
    start = rt_tick_get();

    while (1)
    {
        rt_ssize_t read_size;
        rt_tick_t elapsed;
        rt_tick_t remaining;
        struct rt_can_msg actual;

        rt_memset(&actual, 0, sizeof(actual));
        actual.hdr_index = -1;
        read_size = rt_device_read(context->dev, 0, &actual, sizeof(actual));
        if (read_size == sizeof(actual))
        {
            if (actual.id != expected->id || actual.ide != expected->ide)
            {
                elapsed = (rt_tick_t)(rt_tick_get() - start);
                if (elapsed >= timeout)
                {
                    LOG_E("CAN receive timeout on %s, expected id=0x%x",
                          context->dev->parent.name, expected->id);
                    can_log_status(context);
                    return -RT_ETIMEOUT;
                }
                continue;
            }
            if (!can_message_equal(expected, &actual))
            {
#ifdef RT_CAN_USING_CANFD
                LOG_E("CAN frame mismatch on %s: id=0x%x dlc=%u fd=%u brs=%u, got dlc=%u fd=%u brs=%u",
                      context->dev->parent.name,
                      expected->id,
                      expected->len,
                      expected->fd_frame,
                      expected->brs,
                      actual.len,
                      actual.fd_frame,
                      actual.brs);
#else
                LOG_E("CAN frame mismatch on %s: id=0x%x dlc=%u, got dlc=%u",
                      context->dev->parent.name,
                      expected->id,
                      expected->len,
                      actual.len);
#endif
                return -RT_ERROR;
            }

            return RT_EOK;
        }
        if (read_size < 0)
        {
            LOG_E("CAN read failed on %s, result=%d",
                  context->dev->parent.name, (int)read_size);
            return (rt_err_t)read_size;
        }

        elapsed = (rt_tick_t)(rt_tick_get() - start);
        if (elapsed >= timeout)
        {
            LOG_E("CAN receive timeout on %s, expected id=0x%x",
                  context->dev->parent.name, expected->id);
            can_log_status(context);
            return -RT_ETIMEOUT;
        }

        remaining = timeout - elapsed;
        rt_sem_take(&context->rx_sem, remaining);
    }
}
#endif
#endif

#if defined(RT_CAN_TC_USING_SELF_LOOPBACK) || \
    defined(RT_CAN_TC_USING_DUAL_DEVICE) || \
    defined(RT_CAN_TC_EXTERNAL_USING_SEND_TEST) || \
    defined(RT_CAN_TC_USING_NONBLOCKING_SEND_TEST)
static rt_bool_t can_support_nonblocking_send(struct can_tc_context *context)
{
    return context->can->ops != RT_NULL &&
           context->can->ops->sendmsg_nonblocking != RT_NULL;
}

static rt_err_t can_send_message(struct can_tc_context *context,
                                 const struct rt_can_msg *message,
                                 rt_bool_t nonblocking)
{
    rt_ssize_t write_size;
    struct rt_can_msg tx_message;

    if (nonblocking && !can_support_nonblocking_send(context))
    {
        LOG_E("CAN nonblocking send is not supported by %s", context->dev->parent.name);
        return -RT_ENOSYS;
    }

    tx_message = *message;
    tx_message.nonblocking = nonblocking;
    write_size = rt_device_write(context->dev, 0, &tx_message, sizeof(tx_message));
    if (write_size != sizeof(tx_message))
    {
#ifdef RT_CAN_USING_CANFD
        LOG_E("CAN %s write failed on %s, size=%d, id=0x%x, dlc=%u, fd=%u, brs=%u",
              nonblocking ? "nonblocking" : "blocking",
              context->dev->parent.name,
              (int)write_size,
              tx_message.id,
              tx_message.len,
              tx_message.fd_frame,
              tx_message.brs);
#else
        LOG_E("CAN %s write failed on %s, size=%d, id=0x%x, dlc=%u",
              nonblocking ? "nonblocking" : "blocking",
              context->dev->parent.name,
              (int)write_size,
              tx_message.id,
              tx_message.len);
#endif
        can_log_status(context);
        return -RT_ERROR;
    }

    return RT_EOK;
}
#endif

#if defined(RT_CAN_TC_USING_SELF_LOOPBACK) || defined(RT_CAN_TC_USING_DUAL_DEVICE)
static rt_err_t can_transfer_message(struct can_tc_context *tx_context,
                                     struct can_tc_context *rx_context,
                                     const struct rt_can_msg *message,
                                     rt_bool_t nonblocking)
{
    rt_err_t result;

    can_drain_receive(rx_context);
    result = can_send_message(tx_context, message, nonblocking);
    if (result != RT_EOK)
    {
        if (rx_context != tx_context)
        {
            LOG_E("CAN peer status on %s after transmit failure:",
                  rx_context->dev->parent.name);
            can_log_status(rx_context);
        }
        return result;
    }

    return can_receive_expected(rx_context, message);
}

static rt_err_t can_transfer_pattern(struct can_tc_context *tx_context,
                                     struct can_tc_context *rx_context,
                                     rt_uint32_t id,
                                     rt_uint8_t seed,
                                     rt_bool_t nonblocking)
{
    rt_err_t result;
    struct rt_can_msg message;

    result = can_fill_message(&message, id, seed, CAN_TC_CLASSIC_DLC, RT_FALSE, RT_FALSE);
    if (result != RT_EOK)
    {
        return result;
    }

    return can_transfer_message(tx_context, rx_context, &message, nonblocking);
}
#endif

#if defined(RT_CAN_TC_USING_EXTERNAL_DEVICE) && \
    (defined(RT_CAN_TC_EXTERNAL_USING_SEND_TEST) || \
     defined(RT_CAN_TC_USING_NONBLOCKING_SEND_TEST))
static rt_err_t can_send_pattern(struct can_tc_context *context,
                                 rt_uint32_t id,
                                 rt_uint8_t seed,
                                 rt_bool_t nonblocking)
{
    rt_err_t result;
    struct rt_can_msg message;

    result = can_fill_message(&message, id, seed, CAN_TC_CLASSIC_DLC, RT_FALSE, RT_FALSE);
    if (result != RT_EOK)
    {
        return result;
    }

    return can_send_message(context, &message, nonblocking);
}

#endif

#if defined(RT_CAN_TC_USING_EXTERNAL_DEVICE) && \
    defined(RT_CAN_TC_EXTERNAL_USING_RECEIVE_TEST) && \
    !defined(RT_CAN_TC_USING_CANFD)
static rt_err_t can_receive_pattern(struct can_tc_context *context,
                                    rt_uint32_t id,
                                    rt_uint8_t seed)
{
    rt_err_t result;
    struct rt_can_msg message;

    result = can_fill_message(&message, id, seed, CAN_TC_CLASSIC_DLC, RT_FALSE, RT_FALSE);
    if (result != RT_EOK)
    {
        return result;
    }

    return can_receive_expected(context, &message);
}
#endif

#ifdef RT_CAN_TC_USING_CANFD
static rt_err_t can_build_fd_messages(struct rt_can_msg messages[2],
                                      rt_uint32_t id,
                                      rt_uint8_t seed,
                                      rt_size_t *message_count)
{
    rt_err_t result;
    rt_uint8_t selected_dlc;

    result = can_fill_message(&messages[0], id, seed, CAN_MSG_12BYTES, RT_TRUE, RT_FALSE);
    if (result != RT_EOK)
    {
        return result;
    }
    *message_count = 1;

    result = can_payload_length_to_dlc(RT_CAN_TC_CANFD_DATA_LENGTH, &selected_dlc);
    if (result != RT_EOK)
    {
        return result;
    }
    if (selected_dlc == CAN_MSG_12BYTES && !CAN_TC_SELECTED_FD_BRS)
    {
        return RT_EOK;
    }

    result = can_fill_message(&messages[1],
                              id,
                              (rt_uint8_t)(seed + 0x40),
                              selected_dlc,
                              RT_TRUE,
                              CAN_TC_SELECTED_FD_BRS);
    if (result == RT_EOK)
    {
        *message_count = 2;
    }

    return result;
}

#if defined(RT_CAN_TC_USING_SELF_LOOPBACK) || defined(RT_CAN_TC_USING_DUAL_DEVICE)
static rt_err_t can_transfer_fd_patterns(struct can_tc_context *tx_context,
                                         struct can_tc_context *rx_context,
                                         rt_uint32_t id,
                                         rt_uint8_t seed)
{
    rt_err_t result;
    rt_size_t i;
    rt_size_t message_count;
    struct rt_can_msg messages[2];

    result = can_build_fd_messages(messages, id, seed, &message_count);
    if (result != RT_EOK)
    {
        return result;
    }

    for (i = 0; i < message_count; i++)
    {
        result = can_transfer_message(tx_context, rx_context, &messages[i], RT_FALSE);
        if (result != RT_EOK)
        {
            return result;
        }
    }

    return RT_EOK;
}
#endif

#ifdef RT_CAN_TC_EXTERNAL_USING_SEND_TEST
static rt_err_t can_send_fd_patterns(struct can_tc_context *context,
                                     rt_uint32_t id,
                                     rt_uint8_t seed)
{
    rt_err_t result;
    rt_size_t i;
    rt_size_t message_count;
    struct rt_can_msg messages[2];

    result = can_build_fd_messages(messages, id, seed, &message_count);
    if (result != RT_EOK)
    {
        return result;
    }

    for (i = 0; i < message_count; i++)
    {
        result = can_send_message(context, &messages[i], RT_FALSE);
        if (result != RT_EOK)
        {
            return result;
        }
    }

    return RT_EOK;
}
#endif

#ifdef RT_CAN_TC_EXTERNAL_USING_RECEIVE_TEST
static void can_log_missing_frame(const struct rt_can_msg *message)
{
#ifdef RT_CAN_USING_CANFD
    LOG_E("CAN expected frame missing: id=0x%x, dlc=%u, fd=%u, brs=%u",
          message->id, message->len, message->fd_frame, message->brs);
#else
    LOG_E("CAN expected frame missing: id=0x%x, dlc=%u",
          message->id, message->len);
#endif
}

static void can_log_unmatched_frame(const struct rt_can_msg *message)
{
    LOG_W("CAN RX unmatched: id=0x%x, ide=%u, rtr=%u, dlc=%u, fd=%u, brs=%u",
          message->id, message->ide, message->rtr,
          message->len, message->fd_frame, message->brs);
    LOG_W("CAN RX data[0..7]: %02x %02x %02x %02x %02x %02x %02x %02x",
          message->data[0], message->data[1], message->data[2], message->data[3],
          message->data[4], message->data[5], message->data[6], message->data[7]);
    if (message->len > CAN_MSG_8BYTES)
    {
        LOG_W("CAN RX data[8..15]: %02x %02x %02x %02x %02x %02x %02x %02x",
              message->data[8], message->data[9], message->data[10], message->data[11],
              message->data[12], message->data[13], message->data[14], message->data[15]);
    }
}

static rt_err_t can_receive_external_patterns(struct can_tc_context *context,
                                               rt_uint32_t id,
                                               rt_uint8_t seed)
{
    rt_bool_t received[3] = {RT_FALSE, RT_FALSE, RT_FALSE};
    rt_err_t result;
    rt_size_t i;
    rt_size_t received_count;
    rt_size_t fd_message_count;
    rt_size_t expected_count;
    rt_size_t unmatched_log_count;
    rt_tick_t progress_tick;
    rt_tick_t timeout;
    struct rt_can_msg messages[3];

    result = can_fill_message(&messages[0], id, seed,
                              CAN_TC_CLASSIC_DLC, RT_FALSE, RT_FALSE);
    if (result != RT_EOK)
    {
        return result;
    }

    result = can_build_fd_messages(&messages[1], id, seed, &fd_message_count);
    if (result != RT_EOK)
    {
        return result;
    }

    expected_count = fd_message_count + 1;
    received_count = 0;
    unmatched_log_count = 0;
    timeout = rt_tick_from_millisecond(RT_CAN_TC_TIMEOUT_MS);
    if (timeout == 0)
    {
        timeout = 1;
    }
    progress_tick = rt_tick_get();

    while (received_count < expected_count)
    {
        rt_ssize_t read_size;
        rt_tick_t elapsed;
        rt_tick_t remaining;
        struct rt_can_msg actual;

        rt_memset(&actual, 0, sizeof(actual));
        actual.hdr_index = -1;
        read_size = rt_device_read(context->dev, 0, &actual, sizeof(actual));
        if (read_size == sizeof(actual))
        {
            for (i = 0; i < expected_count; i++)
            {
                if (!received[i] && can_message_equal(&messages[i], &actual))
                {
                    received[i] = RT_TRUE;
                    received_count++;
                    progress_tick = rt_tick_get();
                    LOG_I("CAN RX matched: id=0x%x, dlc=%u, fd=%u, brs=%u",
                          actual.id, actual.len, actual.fd_frame, actual.brs);
                    break;
                }
            }
            if (i == expected_count && unmatched_log_count < 8)
            {
                can_log_unmatched_frame(&actual);
                unmatched_log_count++;
            }
            continue;
        }
        if (read_size < 0)
        {
            LOG_E("CAN read failed on %s, result=%d",
                  context->dev->parent.name, (int)read_size);
            return (rt_err_t)read_size;
        }

        elapsed = (rt_tick_t)(rt_tick_get() - progress_tick);
        if (elapsed >= timeout)
        {
            for (i = 0; i < expected_count; i++)
            {
                if (!received[i])
                {
                    can_log_missing_frame(&messages[i]);
                }
            }
            can_log_status(context);
            return -RT_ETIMEOUT;
        }

        remaining = timeout - elapsed;
        rt_sem_take(&context->rx_sem, remaining);
    }

    return RT_EOK;
}
#endif
#endif

static rt_err_t can_close_context(struct can_tc_context *context)
{
    rt_err_t result;

    if (context == RT_NULL || !context->opened)
    {
        return RT_EOK;
    }

    result = rt_device_close(context->dev);
    context->opened = RT_FALSE;
    return result;
}

static void can_try_start(struct can_tc_context *context, rt_bool_t enable)
{
    rt_err_t result;

    result = rt_device_control(context->dev,
                               RT_CAN_CMD_START,
                               (void *)(rt_ubase_t)enable);
    if (result != RT_EOK)
    {
        LOG_D("CAN start/stop command is not supported by %s, result=%d",
              context->dev->parent.name, result);
    }
}

static void can_build_configuration(struct can_tc_context *context,
                                    struct can_configure *configuration,
                                    rt_uint32_t baud_rate,
                                    rt_uint32_t mode,
                                    rt_bool_t enable_canfd)
{
    *configuration = context->original_config;
    configuration->baud_rate = baud_rate;
    if (configuration->msgboxsz == 0)
    {
        configuration->msgboxsz = RT_CANMSG_BOX_SZ;
    }
    if (configuration->sndboxnumber == 0)
    {
        configuration->sndboxnumber = RT_CANSND_BOX_NUM;
    }
    configuration->mode = mode;
    configuration->privmode = RT_CAN_MODE_NOPRIV;

#ifdef RT_CAN_USING_CANFD
    configuration->use_bit_timing = 0;
    configuration->enable_canfd = 0;
#ifdef RT_CAN_TC_USING_CANFD
    if (enable_canfd)
    {
        configuration->baud_rate_fd = RT_CAN_TC_CANFD_DATA_BAUD_RATE;
        configuration->enable_canfd = 1;
    }
#else
    RT_UNUSED(enable_canfd);
#endif
#else
    RT_UNUSED(enable_canfd);
#endif
}

static rt_err_t can_configure_context(struct can_tc_context *context,
                                      rt_uint32_t baud_rate,
                                      rt_uint32_t mode,
                                      rt_bool_t enable_canfd)
{
    rt_err_t result;
    struct can_configure configuration;
    struct can_configure previous_configuration;

    can_build_configuration(context, &configuration, baud_rate, mode, enable_canfd);
    previous_configuration = context->can->config;

    /* The first open lazily initializes CAN with can->config, so update the cache first. */
    context->can->config = configuration;
    context->configuration_touched = RT_TRUE;
    if (!(context->dev->flag & RT_DEVICE_FLAG_ACTIVATED))
    {
        result = rt_device_init(context->dev);
    }
    else
    {
        result = rt_device_control(context->dev, RT_DEVICE_CTRL_CONFIG, &configuration);
    }
    if (result != RT_EOK)
    {
        context->can->config = previous_configuration;
        LOG_E("Configure %s failed at %u bit/s, result=%d",
              context->dev->parent.name, baud_rate, result);
        return result;
    }

    result = rt_device_open(context->dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    if (result != RT_EOK)
    {
        LOG_E("Open CAN device %s failed, result=%d",
              context->dev->parent.name, result);
        return result;
    }
    context->opened = RT_TRUE;

    result = rt_device_set_rx_indicate(context->dev, can_rx_indicate);
    if (result != RT_EOK)
    {
        return result;
    }

    can_try_start(context, RT_TRUE);
    return RT_EOK;
}

static rt_err_t can_prepare_devices(rt_uint32_t baud_rate,
                                    rt_uint32_t mode,
                                    rt_bool_t enable_canfd)
{
    rt_err_t result;

    result = can_close_context(can_tx_ctx);
    if (result != RT_EOK)
    {
        return result;
    }
    if (can_rx_ctx != can_tx_ctx)
    {
        result = can_close_context(can_rx_ctx);
        if (result != RT_EOK)
        {
            return result;
        }
    }

    result = can_configure_context(can_tx_ctx, baud_rate, mode, enable_canfd);
    if (result != RT_EOK)
    {
        return result;
    }
    if (can_rx_ctx != can_tx_ctx)
    {
        result = can_configure_context(can_rx_ctx, baud_rate, mode, enable_canfd);
        if (result != RT_EOK)
        {
            return result;
        }
    }

    LOG_I("CAN phase: arbitration=%u bit/s, CAN FD=%s",
          baud_rate, enable_canfd ? "on" : "off");
    return RT_EOK;
}

static rt_bool_t can_phase_uses_canfd(rt_uint32_t baud_rate)
{
#ifdef RT_CAN_TC_USING_CANFD
    return baud_rate == RT_CAN_TC_BAUD_RATE;
#else
    RT_UNUSED(baud_rate);
    return RT_FALSE;
#endif
}

static rt_err_t can_find_device(const char *name, rt_device_t *device)
{
    rt_device_t found;

    found = rt_device_find(name);
    if (found == RT_NULL)
    {
        LOG_E("Find CAN device %s failed", name);
        return -RT_ERROR;
    }
    if (found->type != RT_Device_Class_CAN)
    {
        LOG_E("Device %s is not a CAN device", name);
        return -RT_ERROR;
    }
    if (found->ref_count != 0)
    {
        LOG_E("CAN device %s is busy", name);
        return -RT_EBUSY;
    }

    *device = found;
    return RT_EOK;
}

static rt_err_t can_init_context(struct can_tc_context *context,
                                 rt_device_t device,
                                 const char *semaphore_name)
{
    rt_err_t result;

    rt_memset(context, 0, sizeof(*context));
    context->dev = device;
    context->can = (struct rt_can_device *)device;
    context->original_config = context->can->config;
    context->original_rx_indicate = device->rx_indicate;

    result = rt_sem_init(&context->rx_sem, semaphore_name, 0, RT_IPC_FLAG_FIFO);
    if (result == RT_EOK)
    {
        context->sem_inited = RT_TRUE;
    }

    return result;
}

static void can_detach_context(struct can_tc_context *context)
{
    if (context->sem_inited)
    {
        rt_sem_detach(&context->rx_sem);
    }
    rt_memset(context, 0, sizeof(*context));
}

static rt_err_t can_validate_configuration(void)
{
    if (!can_is_standard_baud_rate(RT_CAN_TC_BAUD_RATE))
    {
        LOG_E("Unsupported CAN arbitration rate: %u", RT_CAN_TC_BAUD_RATE);
        return -RT_EINVAL;
    }

#ifdef RT_CAN_TC_USING_EXTERNAL_DEVICE
#if !defined(RT_CAN_TC_EXTERNAL_USING_SEND_TEST) && !defined(RT_CAN_TC_EXTERNAL_USING_RECEIVE_TEST)
    LOG_E("External CAN test requires at least one send or receive subtest");
    return -RT_EINVAL;
#endif
#endif

#ifdef RT_CAN_TC_USING_CANFD
    {
        rt_uint8_t dlc;

        if (can_payload_length_to_dlc(RT_CAN_TC_CANFD_DATA_LENGTH, &dlc) != RT_EOK ||
            RT_CAN_TC_CANFD_DATA_LENGTH <= 8)
        {
            LOG_E("Unsupported CAN FD payload length: %u", RT_CAN_TC_CANFD_DATA_LENGTH);
            return -RT_EINVAL;
        }
        if (CAN_TC_SELECTED_FD_BRS &&
            RT_CAN_TC_CANFD_DATA_BAUD_RATE < RT_CAN_TC_BAUD_RATE)
        {
            LOG_E("CAN FD BRS data rate must not be lower than the arbitration rate");
            return -RT_EINVAL;
        }
    }
#endif

    return RT_EOK;
}

#ifdef RT_CAN_TC_USING_EXTERNAL_DEVICE
static void can_print_external_agreement(void)
{
    LOG_I("CAN external ready: arbitration=%u bit/s, payload[i]=seed+i",
          RT_CAN_TC_BAUD_RATE);
#ifdef RT_CAN_TC_EXTERNAL_USING_SEND_TEST
    LOG_I("DUT TX[1]: classic std id=0x%x, raw DLC=8, seed=0x10",
          RT_CAN_TC_TX_FRAME_ID);
#ifdef RT_CAN_TC_USING_CANFD
    LOG_I("DUT TX[2]: CAN FD std id=0x%x, raw DLC=9, BRS=0, seed=0x10",
          RT_CAN_TC_TX_FRAME_ID);
#if RT_CAN_TC_CANFD_DATA_LENGTH != 12 || defined(RT_CAN_TC_CANFD_BRS)
    {
        rt_uint8_t selected_dlc;

        can_payload_length_to_dlc(RT_CAN_TC_CANFD_DATA_LENGTH, &selected_dlc);
        LOG_I("DUT TX[3]: CAN FD std id=0x%x, raw DLC=%u, BRS=%u, seed=0x50",
              RT_CAN_TC_TX_FRAME_ID, selected_dlc, CAN_TC_SELECTED_FD_BRS);
    }
#endif
#endif
#endif
#ifdef RT_CAN_TC_EXTERNAL_USING_RECEIVE_TEST
    LOG_I("Peer TX[1]: classic std id=0x%x, raw DLC=8, seed=0x20",
          RT_CAN_TC_RX_FRAME_ID);
#ifdef RT_CAN_TC_USING_CANFD
    LOG_I("Peer TX[2]: CAN FD std id=0x%x, raw DLC=9, BRS=0, seed=0x20",
          RT_CAN_TC_RX_FRAME_ID);
#if RT_CAN_TC_CANFD_DATA_LENGTH != 12 || defined(RT_CAN_TC_CANFD_BRS)
    {
        rt_uint8_t selected_dlc;

        can_payload_length_to_dlc(RT_CAN_TC_CANFD_DATA_LENGTH, &selected_dlc);
        LOG_I("Peer TX[3]: CAN FD std id=0x%x, raw DLC=%u, BRS=%u, seed=0x60",
              RT_CAN_TC_RX_FRAME_ID, selected_dlc, CAN_TC_SELECTED_FD_BRS);
    }
#endif
#endif
#endif
#ifdef RT_CAN_TC_USING_NONBLOCKING_SEND_TEST
    LOG_I("DUT nonblocking TX: classic std id=0x%x, raw DLC=8, seed=0x10",
          RT_CAN_TC_NONBLOCKING_TX_FRAME_ID);
#endif
#ifdef RT_CAN_TC_USING_CANFD
    LOG_I("CAN FD configured data rate=%u bit/s", RT_CAN_TC_CANFD_DATA_BAUD_RATE);
#endif
}
#endif

#ifdef RT_CAN_TC_USING_SELF_LOOPBACK
static rt_err_t can_run_self_loopback(void)
{
    rt_err_t result;
    rt_size_t i;

    for (i = 0; i < sizeof(can_tc_baud_rates) / sizeof(can_tc_baud_rates[0]); i++)
    {
        rt_bool_t enable_canfd;
        rt_uint32_t baud_rate;

        baud_rate = can_tc_baud_rates[i];
        if (!can_baud_rate_is_selected(baud_rate))
        {
            continue;
        }
        enable_canfd = can_phase_uses_canfd(baud_rate);

        result = can_prepare_devices(baud_rate, RT_CAN_MODE_LOOPBACK, enable_canfd);
        if (result != RT_EOK)
        {
            return result;
        }
        result = can_transfer_pattern(can_tx_ctx,
                                      can_rx_ctx,
                                      CAN_TC_FRAME_ID_BASE,
                                      CAN_TC_TX_SEED,
                                      RT_FALSE);
        if (result != RT_EOK)
        {
            return result;
        }

#ifdef RT_CAN_TC_USING_NONBLOCKING_SEND_TEST
        result = can_transfer_pattern(can_tx_ctx,
                                      can_rx_ctx,
                                      RT_CAN_TC_NONBLOCKING_TX_FRAME_ID,
                                      CAN_TC_TX_SEED,
                                      RT_TRUE);
        if (result != RT_EOK)
        {
            return result;
        }
#endif

#ifdef RT_CAN_TC_USING_CANFD
        if (enable_canfd)
        {
            result = can_transfer_fd_patterns(can_tx_ctx,
                                              can_rx_ctx,
                                              CAN_TC_FD_FRAME_ID_BASE,
                                              CAN_TC_TX_SEED);
            if (result != RT_EOK)
            {
                return result;
            }
        }
#endif
    }

    return RT_EOK;
}

static void can_self_loopback_test(void)
{
    uassert_int_equal(can_run_self_loopback(), RT_EOK);
}
#endif

#ifdef RT_CAN_TC_USING_DUAL_DEVICE
static rt_err_t can_run_dual_device(void)
{
    rt_err_t result;
    rt_size_t i;

    for (i = 0; i < sizeof(can_tc_baud_rates) / sizeof(can_tc_baud_rates[0]); i++)
    {
        rt_bool_t enable_canfd;
        rt_uint32_t baud_rate;

        baud_rate = can_tc_baud_rates[i];
        if (!can_baud_rate_is_selected(baud_rate))
        {
            continue;
        }
        enable_canfd = can_phase_uses_canfd(baud_rate);

        result = can_prepare_devices(baud_rate, RT_CAN_MODE_NORMAL, enable_canfd);
        if (result != RT_EOK)
        {
            return result;
        }
        result = can_transfer_pattern(can_tx_ctx,
                                      can_rx_ctx,
                                      CAN_TC_FRAME_ID_BASE,
                                      CAN_TC_TX_SEED,
                                      RT_FALSE);
        if (result != RT_EOK)
        {
            return result;
        }
        result = can_transfer_pattern(can_rx_ctx,
                                      can_tx_ctx,
                                      CAN_TC_FRAME_ID_BASE + 1,
                                      CAN_TC_RX_SEED,
                                      RT_FALSE);
        if (result != RT_EOK)
        {
            return result;
        }

#ifdef RT_CAN_TC_USING_NONBLOCKING_SEND_TEST
        result = can_transfer_pattern(can_tx_ctx,
                                      can_rx_ctx,
                                      RT_CAN_TC_NONBLOCKING_TX_FRAME_ID,
                                      CAN_TC_TX_SEED,
                                      RT_TRUE);
        if (result != RT_EOK)
        {
            return result;
        }
#endif

#ifdef RT_CAN_TC_USING_CANFD
        if (enable_canfd)
        {
            result = can_transfer_fd_patterns(can_tx_ctx,
                                              can_rx_ctx,
                                              CAN_TC_FD_FRAME_ID_BASE,
                                              CAN_TC_TX_SEED);
            if (result != RT_EOK)
            {
                return result;
            }
            result = can_transfer_fd_patterns(can_rx_ctx,
                                              can_tx_ctx,
                                              CAN_TC_REVERSE_FD_FRAME_ID_BASE,
                                              CAN_TC_RX_SEED);
            if (result != RT_EOK)
            {
                return result;
            }
        }
#endif
    }

    return RT_EOK;
}

static void can_dual_device_test(void)
{
    uassert_int_equal(can_run_dual_device(), RT_EOK);
}
#endif

#ifdef RT_CAN_TC_USING_EXTERNAL_DEVICE
static rt_err_t can_run_external_device(void)
{
    rt_err_t result;
    rt_bool_t enable_canfd;

    enable_canfd = can_phase_uses_canfd(RT_CAN_TC_BAUD_RATE);
    result = can_prepare_devices(RT_CAN_TC_BAUD_RATE, RT_CAN_MODE_NORMAL, enable_canfd);
    if (result != RT_EOK)
    {
        return result;
    }

#ifdef RT_CAN_TC_EXTERNAL_USING_RECEIVE_TEST
    can_drain_receive(can_rx_ctx);
#endif
    can_print_external_agreement();
    if (RT_CAN_TC_EXTERNAL_READY_DELAY_MS > 0)
    {
        rt_thread_mdelay(RT_CAN_TC_EXTERNAL_READY_DELAY_MS);
    }

#ifdef RT_CAN_TC_EXTERNAL_USING_SEND_TEST
    result = can_send_pattern(can_tx_ctx,
                              RT_CAN_TC_TX_FRAME_ID,
                              CAN_TC_TX_SEED,
                              RT_FALSE);
    if (result != RT_EOK)
    {
        return result;
    }
#ifdef RT_CAN_TC_USING_CANFD
    result = can_send_fd_patterns(can_tx_ctx, RT_CAN_TC_TX_FRAME_ID, CAN_TC_TX_SEED);
    if (result != RT_EOK)
    {
        return result;
    }
#endif
#endif

#ifdef RT_CAN_TC_EXTERNAL_USING_RECEIVE_TEST
#ifdef RT_CAN_TC_USING_CANFD
    result = can_receive_external_patterns(can_rx_ctx,
                                           RT_CAN_TC_RX_FRAME_ID,
                                           CAN_TC_RX_SEED);
#else
    result = can_receive_pattern(can_rx_ctx, RT_CAN_TC_RX_FRAME_ID, CAN_TC_RX_SEED);
#endif
    if (result != RT_EOK)
    {
        return result;
    }
#endif

#ifdef RT_CAN_TC_USING_NONBLOCKING_SEND_TEST
    result = can_send_pattern(can_tx_ctx,
                              RT_CAN_TC_NONBLOCKING_TX_FRAME_ID,
                              CAN_TC_TX_SEED,
                              RT_TRUE);
    if (result != RT_EOK)
    {
        return result;
    }
    LOG_I("External nonblocking frame was accepted or queued");
    rt_thread_mdelay(CAN_TC_EXTERNAL_TX_DRAIN_MS);
#endif

    return RT_EOK;
}

static void can_external_device_test(void)
{
    uassert_int_equal(can_run_external_device(), RT_EOK);
}
#endif

static rt_err_t utest_tc_init(void)
{
    rt_err_t result;
    rt_device_t tx_device;
    rt_device_t rx_device;

    can_tx_ctx = RT_NULL;
    can_rx_ctx = RT_NULL;
    rt_memset(&can_tx_context, 0, sizeof(can_tx_context));
    rt_memset(&can_rx_context, 0, sizeof(can_rx_context));

    result = can_validate_configuration();
    if (result != RT_EOK)
    {
        return result;
    }

#ifdef RT_CAN_TC_USING_DUAL_DEVICE
    result = can_find_device(RT_CAN_TC_TX_DEVICE_NAME, &tx_device);
#else
    result = can_find_device(RT_CAN_TC_DEVICE_NAME, &tx_device);
#endif
    if (result != RT_EOK)
    {
        return result;
    }

#ifdef RT_CAN_TC_USING_DUAL_DEVICE
    result = can_find_device(RT_CAN_TC_RX_DEVICE_NAME, &rx_device);
    if (result != RT_EOK)
    {
        return result;
    }
    if (rx_device == tx_device)
    {
        LOG_E("Dual CAN test requires different TX and RX devices");
        return -RT_EINVAL;
    }
#else
    rx_device = tx_device;
#endif

    result = can_init_context(&can_tx_context, tx_device, "cantx");
    if (result != RT_EOK)
    {
        return result;
    }
    can_tx_ctx = &can_tx_context;

    if (rx_device == tx_device)
    {
        can_rx_ctx = can_tx_ctx;
    }
    else
    {
        result = can_init_context(&can_rx_context, rx_device, "canrx");
        if (result != RT_EOK)
        {
            can_detach_context(&can_tx_context);
            can_tx_ctx = RT_NULL;
            return result;
        }
        can_rx_ctx = &can_rx_context;
    }

    return RT_EOK;
}

static void can_record_cleanup_error(rt_err_t *result, rt_err_t operation_result)
{
    if (*result == RT_EOK && operation_result != RT_EOK)
    {
        *result = operation_result;
    }
}

static rt_err_t can_restore_context(struct can_tc_context *context)
{
    rt_err_t result;
    rt_err_t operation_result;

    result = RT_EOK;
    operation_result = rt_device_set_rx_indicate(context->dev,
                                                  context->original_rx_indicate);
    can_record_cleanup_error(&result, operation_result);

    if (context->configuration_touched)
    {
        context->can->config = context->original_config;
        if (context->dev->flag & RT_DEVICE_FLAG_ACTIVATED)
        {
            operation_result = rt_device_control(context->dev,
                                                 RT_DEVICE_CTRL_CONFIG,
                                                 &context->original_config);
            can_record_cleanup_error(&result, operation_result);
            context->can->config = context->original_config;
            can_try_start(context, RT_FALSE);
        }
    }

    if (context->sem_inited)
    {
        operation_result = rt_sem_detach(&context->rx_sem);
        can_record_cleanup_error(&result, operation_result);
    }

    return result;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_err_t result;
    rt_err_t operation_result;

    result = RT_EOK;
    if (can_tx_ctx != RT_NULL)
    {
        operation_result = can_restore_context(can_tx_ctx);
        can_record_cleanup_error(&result, operation_result);
    }
    if (can_rx_ctx != RT_NULL && can_rx_ctx != can_tx_ctx)
    {
        operation_result = can_restore_context(can_rx_ctx);
        can_record_cleanup_error(&result, operation_result);
    }

    if (can_tx_ctx != RT_NULL)
    {
        operation_result = can_close_context(can_tx_ctx);
        can_record_cleanup_error(&result, operation_result);
    }
    if (can_rx_ctx != RT_NULL && can_rx_ctx != can_tx_ctx)
    {
        operation_result = can_close_context(can_rx_ctx);
        can_record_cleanup_error(&result, operation_result);
    }

    can_tx_ctx = RT_NULL;
    can_rx_ctx = RT_NULL;
    rt_memset(&can_tx_context, 0, sizeof(can_tx_context));
    rt_memset(&can_rx_context, 0, sizeof(can_rx_context));

    return result;
}

static void testcase(void)
{
#ifdef RT_CAN_TC_USING_SELF_LOOPBACK
    UTEST_UNIT_RUN(can_self_loopback_test);
#endif
#ifdef RT_CAN_TC_USING_EXTERNAL_DEVICE
    UTEST_UNIT_RUN(can_external_device_test);
#endif
#ifdef RT_CAN_TC_USING_DUAL_DEVICE
    UTEST_UNIT_RUN(can_dual_device_test);
#endif
}

UTEST_TC_EXPORT(testcase,
                "components.drivers.can.send_recv",
                utest_tc_init,
                utest_tc_cleanup,
                CAN_TC_SUITE_TIMEOUT);

#endif /* RT_UTEST_CAN */
