/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-16     Jesven       first version
 */
#ifndef  LWP_IPC_INTERNAL_H__
#define  LWP_IPC_INTERNAL_H__

#include <rthw.h>
#include <rtthread.h>
#include <lwp.h>

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    FDT_TYPE_LWP,
    FDT_TYPE_KERNEL
};

int lwp_channel_open(int fdt_type, const char *name, int flags);
rt_err_t lwp_channel_close(int fdt_type, int fd);
rt_err_t lwp_channel_send(int fdt_type, int fd, rt_channel_msg_t data);
rt_err_t lwp_channel_send_recv_timeout(int fdt_type, int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret, rt_int32_t time);
rt_err_t lwp_channel_reply(int fdt_type, int fd, rt_channel_msg_t data);
rt_err_t lwp_channel_recv_timeout(int fdt_type, int fd, rt_channel_msg_t data, rt_int32_t time);

#ifdef __cplusplus
}
#endif

#endif  /* LWP_IPC_INTERNAL_H__*/
