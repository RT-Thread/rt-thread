/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/12/30     Bernard      The first version.
 */

#ifndef __AIO_H__
#define __AIO_H__

#include <stdio.h>
#include <sys/signal.h>
#include <rtdevice.h>

struct aiocb
{
    int aio_fildes;         /* File descriptor. */
    off_t aio_offset;       /* File offset. */

    volatile void *aio_buf; /* Location of buffer. */
    size_t aio_nbytes;      /* Length of transfer. */
    int aio_reqprio;        /* Request priority offset. */
    struct sigevent aio_sigevent; /* Signal number and value. */
    int aio_lio_opcode;     /* Operation to be performed. */

    int aio_result;
    struct rt_work aio_work;
};

int aio_cancel(int fd, struct aiocb *cb);
int aio_error (const struct aiocb *cb);

int aio_fsync(int op, struct aiocb *cb);

int aio_read(struct aiocb *cb);
ssize_t  aio_return(struct aiocb *cb);
int aio_suspend(const struct aiocb *const list[], int nent,
             const struct timespec *timeout);
int aio_write(struct aiocb *cb);

int lio_listio(int mode, struct aiocb * const list[], int nent,
            struct sigevent *sig);

#endif
