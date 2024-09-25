/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __RISCV_ATOMIC_H__
#define __RISCV_ATOMIC_H__

typedef struct {
	volatile long counter;
} atomic_t;

#define ATOMIC_INIT(_lptr, val) (_lptr)->counter = (val)

#define ATOMIC_INITIALIZER(val)   \
	{                         \
		.counter = (val), \
	}

long atomic_read(atomic_t *atom);

void atomic_write(atomic_t *atom, long value);

long atomic_add_return(atomic_t *atom, long value);

long atomic_sub_return(atomic_t *atom, long value);

long atomic_cmpxchg(atomic_t *atom, long oldval, long newval);

long atomic_xchg(atomic_t *atom, long newval);

unsigned int atomic_raw_xchg_uint(volatile unsigned int *ptr,
				  unsigned int newval);

unsigned long atomic_raw_xchg_ulong(volatile unsigned long *ptr,
				    unsigned long newval);
/**
 * Set a bit in an atomic variable and return the new value.
 * @nr : Bit to set.
 * @atom: atomic variable to modify
 */
int atomic_set_bit(int nr, atomic_t *atom);

/**
 * Clear a bit in an atomic variable and return the new value.
 * @nr : Bit to set.
 * @atom: atomic variable to modify
 */

int atomic_clear_bit(int nr, atomic_t *atom);

/**
 * Set a bit in any address and return the new value .
 * @nr : Bit to set.
 * @addr: Address to modify
 */
int atomic_raw_set_bit(int nr, volatile unsigned long *addr);

/**
 * Clear a bit in any address and return the new value .
 * @nr : Bit to set.
 * @addr: Address to modify
 */
int atomic_raw_clear_bit(int nr, volatile unsigned long *addr);

#endif
