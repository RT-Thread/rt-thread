/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __MQUEUE_H__
#define __MQUEUE_H__

#include <sys/signal.h>
#include <sys/time.h>
#include <rtdef.h>

struct mqdes
{
    /* reference count and unlinked */
    rt_uint16_t refcount;
    rt_uint16_t unlinked;

    /* RT-Thread message queue */
    rt_mq_t mq;
    /* next posix mqueue */
    struct mqdes* next;
};
typedef struct mqdes* mqd_t;

struct mq_attr
{
    long mq_flags;      /* Message queue flags. */
    long mq_maxmsg;     /* Maximum number of messages. */
    long mq_msgsize;    /* Maximum message size. */
    long mq_curmsgs;    /* Number of messages currently queued. */
};

int     mq_close(mqd_t mqdes);
int     mq_getattr(mqd_t mqdes, struct mq_attr *mqstat);
int     mq_notify(mqd_t mqdes, const struct sigevent *notification);
mqd_t   mq_open(const char *name, int oflag, ...);
ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio);
int     mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio);
int     mq_setattr(mqd_t                 mqdes,
                   const struct mq_attr *mqstat,
                   struct mq_attr       *omqstat);
ssize_t mq_timedreceive(mqd_t                  mqdes,
                        char                  *msg_ptr,
                        size_t                 msg_len,
                        unsigned              *msg_prio,
                        const struct timespec *abs_timeout);
int     mq_timedsend(mqd_t                  mqdes,
                     const char            *msg_ptr,
                     size_t                 msg_len,
                     unsigned               msg_prio,
                     const struct timespec *abs_timeout);

int     mq_unlink(const char *name);

#endif
