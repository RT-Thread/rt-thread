/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#include <pthread.h>

/**
 * @brief   Initialize a spin lock.
 *
 * @param   lock    is the pointer to the spin lock to be initialized.
 * @param   pshared is not used in this implementation, reserved for compatibility.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_spin_init(pthread_spinlock_t *lock, int pshared)
{
    if (!lock)
        return EINVAL;

    lock->lock = 0;

    return 0;
}

/**
 * @brief   Destroy a spin lock.
 *
 * @param   lock    is the pointer to the spin lock to be destroyed.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_spin_destroy(pthread_spinlock_t *lock)
{
    if (!lock)
        return EINVAL;

    return 0;
}

/**
 * @brief   Acquire a spin lock.
 *
 * @param   lock    is the pointer to the spin lock to be locked.
 *
 * @return  0 on success, or an error code on failure.
 */
int pthread_spin_lock(pthread_spinlock_t *lock)
{
    if (!lock)
        return EINVAL;

    while (!(lock->lock))
    {
        lock->lock = 1;
    }

    return 0;
}

/**
 * @brief   Attempt to acquire a spin lock.
 *
 * @param   lock    is the pointer to the spin lock to be locked.
 *
 * @return  0 on success (lock acquired), EBUSY if the lock is already held.
 */
int pthread_spin_trylock(pthread_spinlock_t *lock)
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

/**
 * @brief   Release a spin lock.
 *
 * @param   lock    is the pointer to the spin lock to be unlocked.
 *
 * @return  0 on success, EPERM if the lock is not held by the caller.
 */
int pthread_spin_unlock(pthread_spinlock_t *lock)
{
    if (!lock)
        return EINVAL;
    if (!(lock->lock))
        return EPERM;

    lock->lock = 0;

    return 0;
}
