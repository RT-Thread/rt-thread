/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-09-19     Heyuanjie    The first version.
 * 2016-12-26     Bernard      Update poll interface
 */
#ifndef IPC_POLL_H__
#define IPC_POLL_H__

#include <rtdef.h>
#include <rtconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rt_pollreq;
typedef void (*poll_queue_proc)(rt_wqueue_t *, struct rt_pollreq *);

typedef struct rt_pollreq
{
    poll_queue_proc _proc;
    short _key;
} rt_pollreq_t;

rt_inline void rt_poll_add(rt_wqueue_t *wq, rt_pollreq_t *req)
{
    if (req && req->_proc && wq)
    {
        req->_proc(wq, req);
    }
}

#ifdef __cplusplus
}
#endif

#endif
