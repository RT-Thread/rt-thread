/**************************************************************************//**
 * @file     cache_armv8a.h
 * @brief    CMSIS AARCH64 Cache API header file
 * @version  V1.0.0
 * @date     21. January 2022
 ******************************************************************************/

/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#if   defined ( __ICCARM__ )
 #pragma system_include         /* treat file as system include file for MISRA check */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang system_header   /* treat file as system include file */
#endif

#ifndef __CACHE_ARMV8A_H
#define __CACHE_ARMV8A_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
 extern "C" {
#endif

#define dcache_ops(op, operand)				\
({							\
	__asm__ volatile ("dc " __STRINGIFY(op) ", %0"	\
			  ::"r" (operand): "memory");	\
})


/* Invalidate instruction cache by virtual address to PoU */
static inline void icache_invalidate_range(uintptr_t addr, size_t size)
{
	uintptr_t cur = addr;
	uintptr_t end_addr = cur + size;

	/* Align address to line size */
	cur &= ~(ICACHE_LINE_SIZE - 1);

	do {
		__asm__ volatile ("ic ivau, %0" ::"r" (cur): "memory");
		cur += ICACHE_LINE_SIZE;
	} while (cur < end_addr);

	__DSB();
	__ISB();
}

/* Invalidate all instruction cache to PoU */
static inline void icache_invalidate_all(void)
{
	__asm__ volatile ("ic iallu" ::: "memory");
	__DSB();
	__ISB();
}

/* Clean data cache by virtual address to PoC */
static inline void dcache_clean_range(uintptr_t addr, size_t size)
{
	uintptr_t cur = addr;
	uintptr_t end = addr + size;

	/* Align address to line size */
	cur &= ~(DCACHE_LINE_SIZE - 1);

	while (cur < end) {
		dcache_ops(cvac, cur);
		cur += DCACHE_LINE_SIZE;
	}

	__DSB();
}

/* Invalidate data cache by virtual address to PoC */
static inline void dcache_invalidate_range(uintptr_t addr, size_t size)
{
	uintptr_t cur = addr;
	uintptr_t end = addr + size;

	if (end & (DCACHE_LINE_SIZE - 1)) {
		end &= ~(DCACHE_LINE_SIZE - 1);
		dcache_ops(civac, end);
	}

	if (cur & (DCACHE_LINE_SIZE - 1)) {
		cur &= ~(DCACHE_LINE_SIZE - 1);
		if (cur != end)
			dcache_ops(civac, cur);
		cur += DCACHE_LINE_SIZE;
	}

	while (cur < end) {
		dcache_ops(ivac, cur);
		cur += DCACHE_LINE_SIZE;
	}

	__DSB();
}

/* Clean and invalidate data cache by virtual address to PoC */
static inline void dcache_clean_invalidate_range(uintptr_t addr, size_t size)
{
	uintptr_t cur = addr;
	uintptr_t end = addr + size;

	/* Align address to line size */
	cur &= ~(DCACHE_LINE_SIZE - 1);

	while (cur < end) {
		dcache_ops(civac, cur);
		cur += DCACHE_LINE_SIZE;
	}

	__DSB();
}

void dcache_clean_all(void);
void dcache_invalidate_all(void);
void dcache_clean_invalidate_all(void);

#ifdef __cplusplus
}
#endif

#endif /* __CACHE_ARMV8A_H */
