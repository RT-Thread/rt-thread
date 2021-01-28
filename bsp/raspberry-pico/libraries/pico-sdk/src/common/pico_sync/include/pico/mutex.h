/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PLATFORM_MUTEX_H
#define _PLATFORM_MUTEX_H

#include "pico/lock_core.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file mutex.h
 *  \defgroup mutex mutex
 *  \ingroup pico_sync
 * \brief Mutex API for non IRQ mutual exclusion between cores
 *
 * Mutexes are application level locks usually used protecting data structures that might be used by
 * multiple cores. Unlike critical sections, the mutex protected code is not necessarily
 * required/expected to complete quickly, as no other sytemwide locks are held on account of a locked mutex.
 *
 * Because they are not re-entrant on the same core, blocking on a mutex should never be done in an IRQ
 * handler. It is valid to call \ref mutex_try_enter from within an IRQ handler, if the operation
 * that would be conducted under lock can be skipped if the mutex is locked (at least by the same core).
 *
 * See \ref critical_section.h for protecting access between multiple cores AND IRQ handlers
 */

typedef struct __packed_aligned mutex {
    lock_core_t core;
    bool owned;
    int8_t owner;
} mutex_t;

/*! \brief  Initialise a mutex structure
 *  \ingroup mutex
 *
 * \param mtx Pointer to mutex structure
 */
void mutex_init(mutex_t *mtx);

/*! \brief  Take ownership of a mutex
 *  \ingroup mutex
 *
 * This function will block until the calling core can claim ownership of the mutex.
 * On return the caller core owns the mutex
 *
 * \param mtx Pointer to mutex structure
 */
void mutex_enter_blocking(mutex_t *mtx);

/*! \brief Check to see if a mutex is available
 *  \ingroup mutex
 *
 * Will return true if the mutex is unowned, false otherwise
 *
 * \param mtx Pointer to mutex structure
 * \param owner_out If mutex is owned, and this pointer is non-zero, it will be filled in with the core number of the current owner of the mutex
 */
bool mutex_try_enter(mutex_t *mtx, uint32_t *owner_out);

/*! \brief Wait for mutex with timeout
 *  \ingroup mutex
 *
 * Wait for up to the specific time to take ownership of the mutex. If the calling
 * core can take ownership of the mutex before the timeout expires, then true will be returned
 * and the calling core will own the mutex, otherwise false will be returned and the calling
 * core will *NOT* own the mutex.
 *
 * \param mtx Pointer to mutex structure
 * \param timeout_ms The timeout in milliseconds.
 * \return true if mutex now owned, false if timeout occurred before mutex became available
 */
bool mutex_enter_timeout_ms(mutex_t *mtx, uint32_t timeout_ms);

/*! \brief Wait for mutex until a specific time
 *  \ingroup mutex
 *
 * Wait until the specific time to take ownership of the mutex. If the calling
 * core can take ownership of the mutex before the timeout expires, then true will be returned
 * and the calling core will own the mutex, otherwise false will be returned and the calling
 * core will *NOT* own the mutex.
 *
 * \param mtx Pointer to mutex structure
 * \param until The time after which to return if the core cannot take owner ship of the mutex
 * \return true if mutex now owned, false if timeout occurred before mutex became available
 */
bool mutex_enter_block_until(mutex_t *mtx, absolute_time_t until);

/*! \brief  Release ownership of a mutex
 *  \ingroup mutex
 *
 * \param mtx Pointer to mutex structure
 */
void mutex_exit(mutex_t *mtx);

/*! \brief Test for mutex initialised state
 *  \ingroup mutex
 *
 * \param mtx Pointer to mutex structure
 * \return true if the mutex is initialised, false otherwise
 */
static inline bool mutex_is_initialzed(mutex_t *mtx) {
    return mtx->core.spin_lock != 0;
}

/*! \brief Helper macro for static definition of mutexes
 *  \ingroup mutex
 *
 * A mutex defined as follows:
 *
 * ```c
 * auto_init_mutex(my_mutex);
 * ```
 *
 * Is equivalent to doing
 *
 * ```c
 * static mutex_t my_mutex;
 *
 * void my_init_function() {
 *    mutex_init(&my_mutex);
 * }
 * ```
 *
 * But the initialization of the mutex is performed automatically during runtime initialization
 */
#define auto_init_mutex(name) static __attribute__((section(".mutex_array"))) mutex_t name

#ifdef __cplusplus
}
#endif
#endif
