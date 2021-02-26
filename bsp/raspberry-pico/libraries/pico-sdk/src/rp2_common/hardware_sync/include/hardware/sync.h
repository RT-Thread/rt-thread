/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_SYNC_H
#define _HARDWARE_SYNC_H

#include "pico.h"
#include "hardware/address_mapped.h"
#include "hardware/regs/sio.h"

#ifdef __cplusplus
extern "C" {
#endif


/** \file hardware/sync.h
 *  \defgroup hardware_sync hardware_sync
 *
 * Low level hardware spin-lock, barrier and processor event API
 *
 * Functions for synchronisation between core's, HW, etc
 *
 * The RP2040 provides 32 hardware spin locks, which can be used to manage mutually-exclusive access to shared software
 * resources.
 *
 * \note spin locks 0-15 are currently reserved for fixed uses by the SDK - i.e. if you use them other
 * functionality may break or not function optimally
 */

/** \brief A spin lock identifier
 * \ingroup hardware_sync
 */
typedef volatile uint32_t spin_lock_t;

// PICO_CONFIG: PICO_SPINLOCK_ID_IRQ, Spinlock ID for IRQ protection, min=0, max=31, default=9, group=hardware_sync
#ifndef PICO_SPINLOCK_ID_IRQ
#define PICO_SPINLOCK_ID_IRQ 9
#endif

// PICO_CONFIG: PICO_SPINLOCK_ID_TIMER, Spinlock ID for Timer protection, min=0, max=31, default=10, group=hardware_sync
#ifndef PICO_SPINLOCK_ID_TIMER
#define PICO_SPINLOCK_ID_TIMER 10
#endif

// PICO_CONFIG: PICO_SPINLOCK_ID_HARDWARE_CLAIM, Spinlock ID for Hardware claim protection, min=0, max=31, default=11, group=hardware_sync
#ifndef PICO_SPINLOCK_ID_HARDWARE_CLAIM
#define PICO_SPINLOCK_ID_HARDWARE_CLAIM 11
#endif

// PICO_CONFIG: PICO_SPINLOCK_ID_STRIPED_FIRST, Spinlock ID for striped first, min=16, max=31, default=16, group=hardware_sync
#ifndef PICO_SPINLOCK_ID_STRIPED_FIRST
#define PICO_SPINLOCK_ID_STRIPED_FIRST 16
#endif

// PICO_CONFIG: PICO_SPINLOCK_ID_STRIPED_LAST, Spinlock ID for striped last, min=16, max=31, default=23, group=hardware_sync
#ifndef PICO_SPINLOCK_ID_STRIPED_LAST
#define PICO_SPINLOCK_ID_STRIPED_LAST 23
#endif

// PICO_CONFIG: PICO_SPINLOCK_ID_CLAIM_FREE_FIRST, Spinlock ID for claim free first, min=16, max=31, default=24, group=hardware_sync
#ifndef PICO_SPINLOCK_ID_CLAIM_FREE_FIRST
#define PICO_SPINLOCK_ID_CLAIM_FREE_FIRST 24
#endif

// PICO_CONFIG: PICO_SPINLOCK_ID_CLAIM_FREE_END, Spinlock ID for claim free end, min=16, max=31, default=31, group=hardware_sync
#ifndef PICO_SPINLOCK_ID_CLAIM_FREE_END
#define PICO_SPINLOCK_ID_CLAIM_FREE_END 31
#endif

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_SYNC, Enable/disable assertions in the HW sync module, type=bool, default=0, group=hardware_sync
#ifndef PARAM_ASSERTIONS_ENABLED_SYNC
#define PARAM_ASSERTIONS_ENABLED_SYNC 0
#endif


/*! \brief Insert a SEV instruction in to the code path.
 *  \ingroup hardware_sync

 * The SEV (send event) instruction sends an event to both cores.
 */
inline static void __sev() {
    __asm volatile ("sev");
}

/*! \brief Insert a WFE instruction in to the code path.
 *  \ingroup hardware_sync
 *
 * The WFE (wait for event) instruction waits until one of a number of
 * events occurs, including events signalled by the SEV instruction on either core.
 */
inline static void __wfe() {
    __asm volatile ("wfe");
}

/*! \brief Insert a WFI instruction in to the code path.
  *  \ingroup hardware_sync
*
 * The WFI (wait for interrupt) instruction waits for a interrupt to wake up the core.
 */
inline static void __wfi() {
    __asm volatile ("wfi");
}

/*! \brief Insert a DMB instruction in to the code path.
 *  \ingroup hardware_sync
 *
 * The DMB (data memory barrier) acts as a memory barrier, all memory accesses prior to this
 * instruction will be observed before any explicit access after the instruction.
 */
inline static void __dmb() {
    __asm volatile ("dmb");
}

/*! \brief Insert a ISB instruction in to the code path.
 *  \ingroup hardware_sync
 *
 * ISB acts as an instruction synchronization barrier. It flushes the pipeline of the processor,
 * so that all instructions following the ISB are fetched from cache or memory again, after
 * the ISB instruction has been completed.
 */
inline static void __isb() {
    __asm volatile ("isb");
}

/*! \brief Acquire a memory fence
 *  \ingroup hardware_sync
 */
inline static void __mem_fence_acquire() {
    // the original code below makes it hard for us to be included from C++ via a header
    // which itself is in an extern "C", so just use __dmb instead, which is what
    // is required on Cortex M0+
    __dmb();
//#ifndef __cplusplus
//    atomic_thread_fence(memory_order_acquire);
//#else
//    std::atomic_thread_fence(std::memory_order_acquire);
//#endif
}

/*! \brief Release a memory fence
 *  \ingroup hardware_sync
 *
 */
inline static void __mem_fence_release() {
    // the original code below makes it hard for us to be included from C++ via a header
    // which itself is in an extern "C", so just use __dmb instead, which is what
    // is required on Cortex M0+
    __dmb();
//#ifndef __cplusplus
//    atomic_thread_fence(memory_order_release);
//#else
//    std::atomic_thread_fence(std::memory_order_release);
//#endif
}

/*! \brief Save and disable interrupts
 *  \ingroup hardware_sync
 *
 * \return The prior interrupt enable status for restoration later via restore_interrupts()
 */
inline static uint32_t save_and_disable_interrupts() {
    uint32_t status;
    __asm volatile ("mrs %0, PRIMASK" : "=r" (status)::);
    __asm volatile ("cpsid i");
    return status;
}

/*! \brief Restore interrupts to a specified state
 *  \ingroup hardware_sync
 *
 * \param status Previous interrupt status from save_and_disable_interrupts()
  */
inline static void restore_interrupts(uint32_t status) {
    __asm volatile ("msr PRIMASK,%0"::"r" (status) : );
}

/*! \brief Get HW Spinlock instance from number
 *  \ingroup hardware_sync
 *
 * \param lock_num Spinlock ID
 * \return The spinlock instance
 */
inline static spin_lock_t *spin_lock_instance(uint lock_num) {
    return (spin_lock_t *) (SIO_BASE + SIO_SPINLOCK0_OFFSET + lock_num * 4);
}

/*! \brief Get HW Spinlock number from instance
 *  \ingroup hardware_sync
 *
 * \param lock The Spinlock instance
 * \return The Spinlock ID
 */
inline static uint spin_lock_get_num(spin_lock_t *lock) {
    return lock - (spin_lock_t *) (SIO_BASE + SIO_SPINLOCK0_OFFSET);
}

/*! \brief Acquire a spin lock without disabling interrupts (hence unsafe)
 *  \ingroup hardware_sync
 *
 * \param lock Spinlock instance
 */
inline static void spin_lock_unsafe_blocking(spin_lock_t *lock) {
    // Note we don't do a wfe or anything, because by convention these spin_locks are VERY SHORT LIVED and NEVER BLOCK and run
    // with INTERRUPTS disabled (to ensure that)... therefore nothing on our core could be blocking us, so we just need to wait on another core
    // anyway which should be finished soon
    while (__builtin_expect(!*lock, 0));
    __mem_fence_acquire();
}

/*! \brief Release a spin lock without re-enabling interrupts
 *  \ingroup hardware_sync
 *
 * \param lock Spinlock instance
 */
inline static void spin_unlock_unsafe(spin_lock_t *lock) {
    __mem_fence_release();
    *lock = 0;
}

/*! \brief Acquire a spin lock safely
 *  \ingroup hardware_sync
 *
 * This function will disable interrupts prior to acquiring the spinlock
 *
 * \param lock Spinlock instance
 * \return interrupt status to be used when unlocking, to restore to original state
 */
inline static uint32_t spin_lock_blocking(spin_lock_t *lock) {
    uint32_t save = save_and_disable_interrupts();
    spin_lock_unsafe_blocking(lock);
    return save;
}

/*! \brief Check to see if a spinlock is currently acquired elsewhere.
 *  \ingroup hardware_sync
 *
 * \param lock Spinlock instance
 */
inline static bool is_spin_locked(const spin_lock_t *lock) {
    check_hw_size(spin_lock_t, 4);
    uint32_t lock_num = lock - spin_lock_instance(0);
    return 0 != (*(io_ro_32 *) (SIO_BASE + SIO_SPINLOCK_ST_OFFSET) & (1u << lock_num));
}

/*! \brief Release a spin lock safely
 *  \ingroup hardware_sync
 *
 * This function will re-enable interrupts according to the parameters.
 *
 * \param lock Spinlock instance
 * \param saved_irq Return value from the \ref spin_lock_blocking() function.
 * \return interrupt status to be used when unlocking, to restore to original state
 *
 * \sa spin_lock_blocking()
 */
inline static void spin_unlock(spin_lock_t *lock, uint32_t saved_irq) {
    spin_unlock_unsafe(lock);
    restore_interrupts(saved_irq);
}

/*! \brief Get the current core number
 *  \ingroup hardware_sync
 *
 * \return The core number the call was made from
 */
static inline uint get_core_num() {
    return (*(uint32_t *) (SIO_BASE + SIO_CPUID_OFFSET));
}

/*! \brief Initialise a spin lock
 *  \ingroup hardware_sync
 *
 * The spin lock is initially unlocked
 *
 * \param lock_num The spin lock number
 * \return The spin lock instance
 */
spin_lock_t *spin_lock_init(uint lock_num);

/*! \brief Release all spin locks
 *  \ingroup hardware_sync
 */
void spin_locks_reset(void);

// this number is not claimed
uint next_striped_spin_lock_num();

/*! \brief Mark a spin lock as used
 *  \ingroup hardware_sync
 *
 * Method for cooperative claiming of hardware. Will cause a panic if the spin lock
 * is already claimed. Use of this method by libraries detects accidental
 * configurations that would fail in unpredictable ways.
 *
 * \param lock_num the spin lock number
 */
void spin_lock_claim(uint lock_num);

/*! \brief Mark multiple spin locks as used
 *  \ingroup hardware_sync
 *
 * Method for cooperative claiming of hardware. Will cause a panic if any of the spin locks
 * are already claimed. Use of this method by libraries detects accidental
 * configurations that would fail in unpredictable ways.
 *
 * \param lock_num_mask Bitfield of all required spin locks to claim (bit 0 == spin lock 0, bit 1 == spin lock 1 etc)
 */
void spin_lock_claim_mask(uint32_t lock_num_mask);

/*! \brief Mark a spin lock as no longer used
 *  \ingroup hardware_sync
 *
 * Method for cooperative claiming of hardware.
 *
 * \param lock_num the spin lock number to release
 */
void spin_lock_unclaim(uint lock_num);

/*! \brief Claim a free spin lock
 *  \ingroup hardware_sync
 *
 * \param required if true the function will panic if none are available
 * \return the spin lock number or -1 if required was false, and none were free
 */
int spin_lock_claim_unused(bool required);

#define remove_volatile_cast(t, x) ({__mem_fence_acquire(); (t)(x); })

#ifdef __cplusplus
}
#endif

#endif
