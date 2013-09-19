/*
 * File      : semaphore.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
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
 * 2010-10-26     Bernard      the first version
 */

#ifndef __POSIX_SEMAPHORE_H__
#define __POSIX_SEMAPHORE_H__

#include <rtthread.h>
#include <pthread.h>

struct posix_sem
{
    /* reference count and unlinked */
    rt_uint16_t refcount;
    rt_uint8_t unlinked;
    rt_uint8_t unamed;

    /* RT-Thread semaphore */
    rt_sem_t sem;

    /* next posix semaphore */
    struct posix_sem* next;
};
typedef struct posix_sem sem_t;

int sem_close(sem_t *sem);
int sem_destroy(sem_t *sem);
int sem_getvalue(sem_t *sem, int *sval);
int sem_init(sem_t *sem, int pshared, unsigned int value);
sem_t *sem_open(const char *name, int oflag, ...);
int sem_post(sem_t *sem);
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
int sem_trywait(sem_t *sem);
int sem_unlink(const char *name);
int sem_wait(sem_t *sem);

#endif
