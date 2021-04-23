/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PLATFORM_CRITICAL_SECTION_H
#define _PLATFORM_CRITICAL_SECTION_H

#include "pico/lock_core.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file critical_section.h
 *  \defgroup critical_section critical_section
 *  \ingroup pico_sync
 *  \brief Critical Section API for short-lived mutual exclusion safe for IRQ and multi-core
 *
 *  A critical section is non-reentrant, and provides mutual exclusion using a spin-lock to prevent access
 *  from the other core, and from (higher priority) interrupts on the same core. It does the former
 *  using a spin lock and the latter by disabling interrupts on the calling core.
 *
 *  Because interrupts are disabled by this function, uses of the critical_section should be as short as possible.
 */

typedef struct __packed_aligned critical_section {
    lock_core_t core;
    uint32_t save;
} critical_section_t;

/*! \brief  Initialise a critical_section structure allowing the system to assign a spin lock number
 *  \ingroup critical_section
 *
 * The critical section is initialized ready for use, and will use a (possibly shared) spin lock
 * number assigned by the system. Note that in general it is unlikely that you would be nesting
 * critical sections, however if you do so you *must* use \ref critical_section_init_with_lock_num
 * to ensure that the spin lock's used are different.
 *
 * \param critsec Pointer to critical_section structure
 */
void critical_section_init(critical_section_t *critsec);

/*! \brief  Initialise a critical_section structure assigning a specific spin lock number
 *  \ingroup critical_section
 * \param critsec Pointer to critical_section structure
 * \param lock_num the specific spin lock number to use
 */
void critical_section_init_with_lock_num(critical_section_t *critsec, uint lock_num);

/*! \brief  Enter a critical_section
 *  \ingroup critical_section
 *
 * If the spin lock associated with this critical section is in use, then this
 * method will block until it is released.
 *
 * \param critsec Pointer to critical_section structure
 */
static inline void critical_section_enter_blocking(critical_section_t *critsec) {
    critsec->save = spin_lock_blocking(critsec->core.spin_lock);
}

/*! \brief  Release a critical_section
 *  \ingroup critical_section
 *
 * \param critsec Pointer to critical_section structure
 */
static inline void critical_section_exit(critical_section_t *critsec) {
    spin_unlock(critsec->core.spin_lock, critsec->save);
}
#ifdef __cplusplus
}
#endif
#endif
