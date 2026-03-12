/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __HWSPINLOCK_DM_H__
#define __HWSPINLOCK_DM_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/misc.h>
#include <ref.h>

/**
 * @brief Hardware spinlock instance
 *
 * Represents a single hardware spinlock managed by a bank. Each lock
 * maintains a local software spinlock to protect internal state and a
 * usage flag to indicate whether it has been allocated to clients.
 */
struct rt_hwspinlock
{
    struct rt_hwspinlock_bank *bank;
    struct rt_spinlock lock;           /**< Local software spinlock to guard structure access */

    rt_bool_t used;                    /**< Indicates whether this lock is currently in use */
    void *priv;                        /**< Driver-specific private data */
};

/**
 * @brief Hardware spinlock operations
 *
 * A hardware spinlock driver must provide these low-level operations.
 * trylock() performs a non-blocking acquire. relax() is called inside
 * busy-wait loops to reduce power usage or yield the bus.
 */
struct rt_hwspinlock_ops
{
    /**
     * @brief Attempt to acquire the hardware spinlock (non-blocking)
     *
     * Should immediately return RT_EOK on success or -RT_EBUSY if the lock
     * is already taken by another CPU or hardware requester.
     */
    rt_err_t (*trylock)(struct rt_hwspinlock *hwlock);

    /**
     * @brief Release the hardware spinlock
     */
    void (*unlock)(struct rt_hwspinlock *hwlock);

    /**
     * @brief Relax operation called during spinning
     *
     * Typically implemented using power-saving instructions (e.g., WFE),
     * yielding the CPU, or other hardware-supported wait mechanisms.
     */
    void (*relax)(struct rt_hwspinlock *hwlock);
};

/**
 * @brief Hardware spinlock bank
 *
 * Represents a group of hardware spinlocks exported by the same device
 * or hardware module. A bank is registered globally so that locks can be
 * retrieved by index, name, or device tree bindings.
 */
struct rt_hwspinlock_bank
{
    rt_list_t list;
    struct rt_ref ref;

    struct rt_device *dev;
    const struct rt_hwspinlock_ops *ops;

    int base_id;                           /**< Global base ID used to calculate lock identifiers */
    rt_size_t locks_nr;                    /**< Number of hardware spinlocks in this bank */

    /**
     * @brief Array of hardware spinlock instances
     *
     * Implemented as a flexible array member. Memory is allocated using
     * hwspinlock_bank_alloc(), ensuring space for all lock structures.
     */
    struct rt_hwspinlock locks[];
};

/**
 * @brief Allocate a hardware spinlock bank with a given number of locks
 *
 * The allocation includes both the bank structure and the flexible array
 * of hardware spinlock objects.
 *
 * @param obj        The object pointer used to store the bank
 * @param locks_nr   Number of hardware spinlocks to allocate
 *
 * @return Pointer to the allocated memory or NULL on failure
 */
#define hwspinlock_bank_alloc(obj, locks_nr) \
    rt_calloc(1, sizeof(typeof(*obj)) + sizeof(struct rt_hwspinlock) * (locks_nr))

/**
 * @brief Compute the global hardware spinlock ID
 *
 * The global ID is calculated as:
 *     bank->base_id + index
 * where the index is derived from the hardware spinlock's position inside
 * the bank->locks array.
 *
 * @param hwlock  Pointer to a hardware spinlock
 *
 * @return The global lock identifier
 */
rt_inline int hwspinlock_find_id(struct rt_hwspinlock *hwlock)
{
    return hwlock->bank->base_id + (hwlock - &hwlock->bank->locks[0]);
}

#endif /* __HWSPINLOCK_DM_H__ */
