/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-06     zmq810150896      The first version.
 */
#ifndef __SAL_MSG_H__
#define __SAL_MSG_H__
#include <rtthread.h>

/* message frame */
struct msg_buf
{
    void *parm;             /* Parameters for message detection */
    void *buf;              /* Data to be sent */
    rt_size_t length;       /* Data length */
    void *control_data;     /* Additional data to send the message */
    rt_size_t data_len;     /* Additional data length */
    int msg_type;           /* message type */
    int data_type;          /* Addittional data length */
    int msg_level;
    int *fd;                /* Pass the array used by fd */
    rt_slist_t msg_next;    /* Next message */
    rt_slist_t msg_node;    /* sendmsg is used to send multiple messages at the same time */
};

/* Remaining message */
struct last_buf
{
    void *buf;              /* Data to be sent */
    rt_size_t length;       /* Data length */
    rt_size_t offset;       /* Data Offset */
    struct msg_buf *msg;
};

/* sock */
struct unix_sock
{
    rt_uint8_t len;
    int flags;
    uint8_t family;             /* protocol */
    char path[108];             /* file name */
    struct unix_conn *conn;     /* connecting processing */
    rt_wqueue_t wq_head;        /* Waiting queue head */
    rt_atomic_t listen_num;     /* Maximum listening quantity */
    rt_atomic_t conn_counter;   /*  connected num */
    struct rt_mutex sock_lock;
    rt_slist_t wait_conn_head;
    struct last_buf pbuf;
};

struct unix_conn
{
    int state;                                          /*  connect state */
    int type;
    int proto;

#ifdef SAL_USING_AF_UNIX
    rt_atomic_t msg_count;
#endif
    rt_uint32_t send_timeout;
    rt_uint32_t recv_timeout;
    rt_wqueue_t wq_read_head;
    rt_wqueue_t wq_confirm;
    struct rt_mutex conn_lock;
    rt_slist_t msg_head;                                /* message head */
    rt_slist_t conn_node;
    struct unix_sock *sock;
    struct unix_sock *ser_sock;
    struct unix_conn *correl_conn;                      /* Information about the other party */
    int (* conn_callback)(struct unix_conn *conn);      /* The callback function that establishes the connection */
};

#endif
