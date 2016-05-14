/*
 * File      : pthread_spin.c
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

#include <pthread.h>

int pthread_spin_init (pthread_spinlock_t *lock, int pshared)
{
    if (!lock)
        return EINVAL;

    lock->lock = 0;

    return 0;
}

int pthread_spin_destroy (pthread_spinlock_t *lock)
{
    if (!lock)
        return EINVAL;

    return 0;
}

int pthread_spin_lock (pthread_spinlock_t *lock)
{
    if (!lock)
        return EINVAL;

    while (!(lock->lock))
    {
        lock->lock = 1;
    }

    return 0;
}

int pthread_spin_trylock (pthread_spinlock_t *lock)
{
    if (!lock)
        return EINVAL;

    if (!(lock->lock))
    {
        lock->lock = 1;

        return 0;
    }

    return EBUSY;
}

int pthread_spin_unlock (pthread_spinlock_t *lock)
{
    if (!lock)
        return EINVAL;
    if (!(lock->lock))
        return EPERM;

    lock->lock = 0;

    return 0;
}
