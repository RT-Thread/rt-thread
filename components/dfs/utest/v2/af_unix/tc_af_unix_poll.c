/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "tc_af_unix.h"

#define TC_AF_UNIX_POLL_STACK 4096
#define TC_AF_UNIX_POLL_PRIO  20

struct tc_af_unix_poll_ctx
{
    int fd;
    int result;
    short revents;
    struct rt_event done;
};

static void tc_af_unix_poll_entry(void *parameter)
{
    struct pollfd poll_fd;
    struct tc_af_unix_poll_ctx *ctx;

    ctx = (struct tc_af_unix_poll_ctx *)parameter;
    poll_fd.fd = ctx->fd;
    poll_fd.events = POLLIN;
    poll_fd.revents = 0;
    ctx->result = poll(&poll_fd, 1, 3000);
    ctx->revents = poll_fd.revents;
    rt_event_send(&ctx->done, 0x1);
}

static void tc_af_unix_stream_readiness(void)
{
    char buffer[8];
    char *fill;
    const char payload[] = "poll";
    int result;
    int sockets[2] = { -1, -1 };
    rt_size_t sent = 0;
    struct pollfd poll_fd;

    result = socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
    uassert_int_equal(result, 0);
    if (result < 0)
    {
        return;
    }

    poll_fd.fd = sockets[1];
    poll_fd.events = POLLIN | POLLOUT;
    poll_fd.revents = 0;
    uassert_int_equal(poll(&poll_fd, 1, 0), 1);
    uassert_true((poll_fd.revents & POLLOUT) != 0);
    uassert_true((poll_fd.revents & POLLIN) == 0);

    uassert_int_equal(send(sockets[0], payload, sizeof(payload), 0),
                      sizeof(payload));
    poll_fd.revents = 0;
    uassert_int_equal(poll(&poll_fd, 1, 0), 1);
    uassert_true((poll_fd.revents & POLLIN) != 0);
    uassert_int_equal(recv(sockets[1], buffer, sizeof(buffer), 0),
                      sizeof(payload));

    fill = (char *)rt_malloc(AF_UNIX_STREAM_BUFFER_SIZE);
    uassert_true(fill != RT_NULL);
    if (fill != RT_NULL)
    {
        rt_memset(fill, 'x', AF_UNIX_STREAM_BUFFER_SIZE);
        uassert_int_equal(fcntl(sockets[0], F_SETFL, O_NONBLOCK), 0);
        while (sent < AF_UNIX_STREAM_BUFFER_SIZE)
        {
            result = send(sockets[0], fill + sent,
                          AF_UNIX_STREAM_BUFFER_SIZE - sent, 0);
            if (result <= 0)
            {
                break;
            }
            sent += (rt_size_t)result;
        }
        uassert_int_equal(sent, AF_UNIX_STREAM_BUFFER_SIZE);

        poll_fd.fd = sockets[0];
        poll_fd.events = POLLOUT;
        poll_fd.revents = 0;
        uassert_int_equal(poll(&poll_fd, 1, 0), 0);

        uassert_int_equal(recv(sockets[1], fill, 64, 0), 64);
        poll_fd.revents = 0;
        uassert_int_equal(poll(&poll_fd, 1, 0), 1);
        uassert_true((poll_fd.revents & POLLOUT) != 0);
        rt_free(fill);
    }

    uassert_int_equal(shutdown(sockets[0], SHUT_WR), 0);
    poll_fd.fd = sockets[1];
    poll_fd.events = POLLIN;
    poll_fd.revents = 0;
    uassert_int_equal(poll(&poll_fd, 1, 0), 1);
    uassert_true((poll_fd.revents & POLLIN) != 0);

    tc_af_unix_closesocket(&sockets[0]);
    tc_af_unix_closesocket(&sockets[1]);
}

static void tc_af_unix_dgram_readiness(void)
{
    char buffer[2];
    const char payload[] = "x";
    int error;
    int index;
    int result;
    int sockets[2] = { -1, -1 };
    struct pollfd poll_fd;

    result = socketpair(AF_UNIX, SOCK_DGRAM | SOCK_NONBLOCK, 0, sockets);
    uassert_int_equal(result, 0);
    if (result < 0)
    {
        return;
    }

    poll_fd.fd = sockets[1];
    poll_fd.events = POLLIN;
    poll_fd.revents = 0;
    uassert_int_equal(poll(&poll_fd, 1, 0), 0);

    for (index = 0; index < AF_UNIX_DGRAM_QUEUE_LEN; index++)
    {
        uassert_int_equal(send(sockets[0], payload, sizeof(payload), 0),
                          sizeof(payload));
    }
    result = send(sockets[0], payload, sizeof(payload), 0);
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, EAGAIN);

    poll_fd.revents = 0;
    uassert_int_equal(poll(&poll_fd, 1, 0), 1);
    uassert_true((poll_fd.revents & POLLIN) != 0);
    uassert_int_equal(recv(sockets[1], buffer, sizeof(buffer), 0),
                      sizeof(payload));
    uassert_int_equal(send(sockets[0], payload, sizeof(payload), 0),
                      sizeof(payload));

    result = send(sockets[0], payload, AF_UNIX_DGRAM_MAX_SIZE + 1, 0);
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, EMSGSIZE);

    tc_af_unix_closesocket(&sockets[0]);
    tc_af_unix_closesocket(&sockets[1]);
}

static void tc_af_unix_poll_peer_close(void)
{
    int sockets[2] = { -1, -1 };
    rt_err_t wait;
    rt_thread_t thread;
    rt_uint32_t recved;
    struct tc_af_unix_poll_ctx ctx;

    uassert_int_equal(socketpair(AF_UNIX, SOCK_STREAM, 0, sockets), 0);
    if (sockets[0] < 0)
    {
        return;
    }

    rt_memset(&ctx, 0, sizeof(ctx));
    ctx.fd = sockets[0];
    ctx.result = -2;
    uassert_int_equal(rt_event_init(&ctx.done, "utafup", RT_IPC_FLAG_PRIO),
                      RT_EOK);

    thread = rt_thread_create("utafup", tc_af_unix_poll_entry, &ctx,
                              TC_AF_UNIX_POLL_STACK, TC_AF_UNIX_POLL_PRIO, 10);
    uassert_true(thread != RT_NULL);
    if (thread == RT_NULL)
    {
        rt_event_detach(&ctx.done);
        tc_af_unix_closesocket(&sockets[0]);
        tc_af_unix_closesocket(&sockets[1]);
        return;
    }

    rt_thread_startup(thread);
    rt_thread_mdelay(50);
    tc_af_unix_closesocket(&sockets[1]);

    wait = rt_event_recv(&ctx.done, 0x1,
                         RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                         rt_tick_from_millisecond(3000), &recved);
    uassert_int_equal(wait, RT_EOK);
    uassert_int_equal(ctx.result, 1);
    uassert_true((ctx.revents & (POLLIN | POLLHUP)) != 0);

    rt_event_detach(&ctx.done);
    tc_af_unix_closesocket(&sockets[0]);
    tc_af_unix_closesocket(&sockets[1]);
}

static void tc_af_unix_poll_testcase(void)
{
    UTEST_UNIT_RUN(tc_af_unix_stream_readiness);
    UTEST_UNIT_RUN(tc_af_unix_dgram_readiness);
    UTEST_UNIT_RUN(tc_af_unix_poll_peer_close);
}

UTEST_TC_EXPORT(tc_af_unix_poll_testcase, "components.dfs.v2.af_unix.poll",
                RT_NULL, RT_NULL, 20);
