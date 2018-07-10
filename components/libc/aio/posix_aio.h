/*
 * File      : posix_aio.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/12/30     Bernard      The first version.
 */

#ifndef POSIX_AIO_H__
#define POSIX_AIO_H__

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
