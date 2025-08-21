/**************************************************************************//**
 * @file     cache_armv8a.c
 * @brief    CMSIS AARCH64 Cache Source file
 * @version  V1.0.0
 * @date     21. January 2022
 ******************************************************************************/

/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "core_ca53.h"
#include "cache_armv8a.h"

#ifndef BIT_MASK
#define BIT_MASK(n)			((1UL << n) - 1UL)
#endif

/* CLIDR_EL1 */
#define CLIDR_EL1_LOC_SHIFT		24
#define CLIDR_EL1_LOC_MASK		BIT_MASK(3)
#define CLIDR_EL1_CTYPE_SHIFT(l)	((l) * 3)
#define CLIDR_EL1_CTYPE_MASK		BIT_MASK(3)

/* CCSIDR_EL1 */
#define CCSIDR_EL1_LN_SZ_SHIFT		0
#define CCSIDR_EL1_LN_SZ_MASK		BIT_MASK(3)
#define CCSIDR_EL1_WAYS_SHIFT		3
#define CCSIDR_EL1_WAYS_MASK		BIT_MASK(10)
#define CCSIDR_EL1_SETS_SHIFT		13
#define CCSIDR_EL1_SETS_MASK		BIT_MASK(15)

/* CSSELR_EL1 */
#define CSSELR_EL1_LEVEL_SHIFT		1
#define CSSELR_EL1_LEVEL_MASK		BIT_MASK(3)

enum cache_ops {
	CACHE_OP_C,	/* Clean */
	CACHE_OP_I,	/* Invalidate */
	CACHE_OP_CI	/* Clean and Invalidate */
};

/*
 * Operation for all data cache to PoC
 * op:	CACHE_OP_C: clean
 * 	CACHE_OP_I: invalidate
 *	CACHE_OP_CI: clean and invalidate
 */
int dcache_all(enum cache_ops op)
{
	uint32_t clidr_el1, csselr_el1, ccsidr_el1;
	uint32_t num_ways, num_sets, set, way, operand;
	uint8_t loc, cache_type, cache_level, set_shift, way_shift;

	__DSB();

	__MRS(CLIDR_EL1, &clidr_el1);

	loc = (clidr_el1 >> CLIDR_EL1_LOC_SHIFT) & CLIDR_EL1_LOC_MASK;
	if (!loc)
		return 0;

	for (cache_level = 0; cache_level < loc; cache_level++) {
		cache_type = (clidr_el1 >> CLIDR_EL1_CTYPE_SHIFT(cache_level)) &
			     CLIDR_EL1_CTYPE_MASK;
		/* No Data or Unified cache at this level */
		if (cache_type < 2)
			continue;

		/* Select cache level and Data/Unified cache */
		csselr_el1 = (cache_level & CSSELR_EL1_LEVEL_MASK) <<
			     CSSELR_EL1_LEVEL_SHIFT;
		__MSR(CSSELR_EL1, csselr_el1);
		__ISB();

		__MRS(CCSIDR_EL1, &ccsidr_el1);
		set_shift = ((ccsidr_el1 >> CCSIDR_EL1_LN_SZ_SHIFT) &
			    CCSIDR_EL1_LN_SZ_MASK) + 4;
		num_ways = ((ccsidr_el1 >> CCSIDR_EL1_WAYS_SHIFT) &
			   CCSIDR_EL1_WAYS_MASK) + 1;
		num_sets = ((ccsidr_el1 >> CCSIDR_EL1_SETS_SHIFT) &
			   CCSIDR_EL1_SETS_MASK) + 1;
		/* 32-log2(ways), bit position of way in DC operand */
		way_shift = __CLZ(num_ways - 1);

		for (set = 0; set < num_sets; set++) {
			for (way = 0; way < num_ways; way++) {
				/* cache level, aligned to pos in DC operand */
				operand = (cache_level << 1);
				/* set number, aligned to pos in DC operand */
				operand |= set << set_shift;
				/* way number, aligned to pos in DC operand */
				/* No way number field for direct-mapped cache */
				if (way_shift < 32)
					operand |= way << way_shift;

				switch (op) {
				case CACHE_OP_C:
					dcache_ops(csw, operand);
					break;
				case CACHE_OP_I:
					dcache_ops(isw, operand);
					break;
				case CACHE_OP_CI:
					dcache_ops(cisw, operand);
					break;
				default:
					return -1;
				}
			}
		}
	}

	__DSB();

	/* Restore csselr_el1 to level 0 */
	__MSR(CSSELR_EL1, 0);
	__ISB();

	return 0;
}

void dcache_clean_all(void)
{
	dcache_all(CACHE_OP_C);
}

void dcache_invalidate_all(void)
{
	dcache_all(CACHE_OP_I);
}
void dcache_clean_invalidate_all(void)
{
	dcache_all(CACHE_OP_CI);
}
