/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-12     Jesven       first version
 */

#ifndef LWP_IPC_H__
#define LWP_IPC_H__

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    RT_CHANNEL_RAW,
    RT_CHANNEL_BUFFER,
    RT_CHANNEL_FD
};

struct rt_channel_msg
{
    void *sender;
    int type;
    union
    {
        struct chbuf
        {
            void *buf;
            size_t length;
        } b;
        struct chfd
        {
            void *file;
            int fd;
        } fd;
        void* d;
    } u;
};
typedef struct rt_channel_msg *rt_channel_msg_t;

int rt_channel_open(const char *name, int flags);
rt_err_t rt_channel_close(int fd);
rt_err_t rt_channel_send(int fd, rt_channel_msg_t data);
rt_err_t rt_channel_send_recv(int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret);
rt_err_t rt_channel_send_recv_timeout(int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret, rt_int32_t time);
rt_err_t rt_channel_reply(int fd, rt_channel_msg_t data);
rt_err_t rt_channel_recv(int fd, rt_channel_msg_t data);
rt_err_t rt_channel_recv_timeout(int fd, rt_channel_msg_t data, rt_int32_t time);
rt_err_t rt_channel_peek(int fd, rt_channel_msg_t data);

rt_channel_t rt_raw_channel_open(const char *name, int flags);
rt_err_t rt_raw_channel_close(rt_channel_t ch);
rt_err_t rt_raw_channel_send(rt_channel_t ch, rt_channel_msg_t data);
rt_err_t rt_raw_channel_send_recv(rt_channel_t ch, rt_channel_msg_t data, rt_channel_msg_t data_ret);
rt_err_t rt_raw_channel_send_recv_timeout(rt_channel_t ch, rt_channel_msg_t data, rt_channel_msg_t data_ret, rt_int32_t time);
rt_err_t rt_raw_channel_reply(rt_channel_t ch, rt_channel_msg_t data);
rt_err_t rt_raw_channel_recv(rt_channel_t ch, rt_channel_msg_t data);
rt_err_t rt_raw_channel_recv_timeout(rt_channel_t ch, rt_channel_msg_t data, rt_int32_t time);
rt_err_t rt_raw_channel_peek(rt_channel_t ch, rt_channel_msg_t data);

rt_err_t rt_channel_component_init(void);

#ifdef __cplusplus
}
#endif

#endif
