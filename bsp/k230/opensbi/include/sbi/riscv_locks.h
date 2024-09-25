/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 * Copyright (c) 2021 Christoph Müllner <cmuellner@linux.com>
 */

#ifndef __RISCV_LOCKS_H__
#define __RISCV_LOCKS_H__

#include <sbi/sbi_types.h>

#define TICKET_SHIFT	16

typedef struct {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
       u16 next;
       u16 owner;
#else
       u16 owner;
       u16 next;
#endif
} __aligned(4) spinlock_t;

#define __SPIN_LOCK_UNLOCKED	\
	(spinlock_t) { 0, 0 }

#define SPIN_LOCK_INIT(x)	\
	x = __SPIN_LOCK_UNLOCKED

#define SPIN_LOCK_INITIALIZER	\
	__SPIN_LOCK_UNLOCKED

#define DEFINE_SPIN_LOCK(x)	\
	spinlock_t SPIN_LOCK_INIT(x)

int spin_lock_check(spinlock_t *lock);

int spin_trylock(spinlock_t *lock);

void spin_lock(spinlock_t *lock);

void spin_unlock(spinlock_t *lock);

#endif
