/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __HWSPINLOCK_H__
#define __HWSPINLOCK_H__

#include <rtdef.h>

struct rt_hwspinlock;
struct rt_hwspinlock_ops;
struct rt_hwspinlock_bank;

/**
 * @brief Register a hardware spinlock bank
 *
 * A bank represents a contiguous set of hardware spinlocks provided by
 * a hardware module. This API installs the bank into the system-wide list
 * so that each individual lock can be retrieved and used by clients.
 *
 * @param bank Pointer to the hardware spinlock bank
 * @return RT_EOK on success, otherwise an error code
 */
rt_err_t rt_hwspinlock_bank_register(struct rt_hwspinlock_bank *bank);

/**
 * @brief Unregister a hardware spinlock bank
 *
 * Removes the bank from the global registry. All locks under the bank
 * become unavailable. Caller must ensure no active users remain.
 *
 * @param bank Pointer to the hardware spinlock bank
 * @return RT_EOK on success, otherwise an error code
 */
rt_err_t rt_hwspinlock_bank_unregister(struct rt_hwspinlock_bank *bank);

/**
 * @brief Try to acquire a hardware spinlock (raw interface)
 *
 * The raw interface allows hardware drivers to retrieve the IRQ level
 * before acquiring the lock, enabling IRQ-safe usage scenarios.
 *
 * @param hwlock Pointer to the hardware spinlock
 * @param out_irq_level If non-NULL, returns saved IRQ level
 *
 * @return RT_EOK if lock is acquired, -RT_EBUSY if lock is held by others
 */
rt_err_t rt_hwspin_trylock_raw(struct rt_hwspinlock *hwlock,
        rt_ubase_t *out_irq_level);

/**
 * @brief Acquire a hardware spinlock with timeout (raw interface)
 *
 * Spins or relaxes according to the hardware implementation until the
 * lock becomes available or timeout expires. IRQ level handling is optional.
 *
 * @param hwlock Pointer to the hardware spinlock
 * @param timeout_ms Timeout in milliseconds
 * @param out_irq_level If non-NULL, returns saved IRQ level
 *
 * @return RT_EOK on success, -RT_ETIMEOUT if timed out
 */
rt_err_t rt_hwspin_lock_timeout_raw(struct rt_hwspinlock *hwlock,
        rt_uint32_t timeout_ms, rt_ubase_t *out_irq_level);

/**
 * @brief Release a hardware spinlock (raw interface)
 *
 * Restores IRQ state if @p out_irq_level is provided.
 *
 * @param hwlock Pointer to the hardware spinlock
 * @param out_irq_level IRQ level saved during lock operation
 */
void rt_hwspin_unlock_raw(struct rt_hwspinlock *hwlock,
        rt_ubase_t *out_irq_level);

/**
 * @brief Try to acquire a hardware spinlock (no IRQ management)
 */
rt_inline rt_err_t rt_hwspin_trylock(struct rt_hwspinlock *hwlock)
{
    return rt_hwspin_trylock_raw(hwlock, RT_NULL);
}

/**
 * @brief Try to acquire a hardware spinlock with IRQ saving
 */
rt_inline rt_err_t rt_hwspin_trylock_irqsave(struct rt_hwspinlock *hwlock,
        rt_ubase_t *out_irq_level)
{
    return rt_hwspin_trylock_raw(hwlock, out_irq_level);
}

/**
 * @brief Acquire a hardware spinlock with timeout (no IRQ management)
 */
rt_inline rt_err_t rt_hwspin_lock_timeout(struct rt_hwspinlock *hwlock,
        rt_uint32_t timeout_ms)
{
    return rt_hwspin_lock_timeout_raw(hwlock, timeout_ms, RT_NULL);
}

/**
 * @brief Acquire a hardware spinlock with timeout and IRQ saving
 */
rt_inline rt_err_t rt_hwspin_lock_timeout_irqsave(struct rt_hwspinlock *hwlock,
        rt_uint32_t timeout_ms, rt_ubase_t *out_level)
{
    return rt_hwspin_lock_timeout_raw(hwlock, timeout_ms, out_level);
}

/**
 * @brief Release a hardware spinlock (no IRQ management)
 */
rt_inline void rt_hwspin_unlock(struct rt_hwspinlock *hwlock)
{
    rt_hwspin_unlock_raw(hwlock, RT_NULL);
}

/**
 * @brief Release a hardware spinlock and restore IRQ level
 */
rt_inline void rt_hwspin_unlock_irqsave(struct rt_hwspinlock *hwlock,
        rt_ubase_t *out_level)
{
    rt_hwspin_unlock_raw(hwlock, out_level);
}

/**
 * @brief Acquire a free hardware spinlock from any registered bank
 *
 * The returned lock must later be released via rt_hwspinlock_put().
 *
 * @return Pointer to a hardware spinlock, or NULL if none available
 */
struct rt_hwspinlock *rt_hwspinlock_get(void);

/**
 * @brief Get hardware spinlock by index from a specific device
 *
 * @param dev Device providing hardware spinlocks
 * @param index Hardware spinlock index within device/bank
 *
 * @return Pointer to the hardware spinlock, or NULL if invalid index
 */
struct rt_hwspinlock *rt_hwspinlock_get_by_index(struct rt_device *dev, int index);

/**
 * @brief Get hardware spinlock by name from a specific device
 *
 * Names are assigned by device drivers and mapped to lock indices.
 *
 * @return Pointer to the hardware spinlock, or NULL if name not found
 */
struct rt_hwspinlock *rt_hwspinlock_get_by_name(struct rt_device *dev, const char *name);

/**
 * @brief Release hardware spinlock reference obtained from get()
 *
 * Does not unlock the spinlock; only decreases usage count.
 */
void rt_hwspinlock_put(struct rt_hwspinlock *hwlock);

/**
 * @brief Get hardware spinlock by index from device tree node
 */
struct rt_hwspinlock *rt_ofw_get_hwspinlock_by_index(struct rt_ofw_node *np, int index);

/**
 * @brief Get hardware spinlock by name from device tree node
 */
struct rt_hwspinlock *rt_ofw_get_hwspinlock_by_name(struct rt_ofw_node *np, const char *name);

#endif /* __HWSPINLOCK_H__ */
