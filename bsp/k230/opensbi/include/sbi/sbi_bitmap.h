/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_BITMAP_H__
#define __SBI_BITMAP_H__

#include <sbi/sbi_bitops.h>

#define BITMAP_FIRST_WORD_MASK(start) (~0UL << ((start) % BITS_PER_LONG))
#define BITMAP_LAST_WORD_MASK(nbits)					\
(									\
	((nbits) % BITS_PER_LONG) ?					\
		((1UL << ((nbits) % BITS_PER_LONG)) - 1) : ~0UL		\
)

#define small_const_nbits(nbits) \
	(__builtin_constant_p(nbits) && (nbits) <= BITS_PER_LONG)

#define DECLARE_BITMAP(name, nbits)	unsigned long name[BITS_TO_LONGS(nbits)]
#define DEFINE_BITMAP(name)		extern unsigned long name[]

static inline unsigned long bitmap_estimate_size(int nbits)
{
	return (BITS_TO_LONGS(nbits) * sizeof(unsigned long));
}

void __bitmap_and(unsigned long *dst, const unsigned long *bitmap1,
		  const unsigned long *bitmap2, int bits);
void __bitmap_or(unsigned long *dst, const unsigned long *bitmap1,
		 const unsigned long *bitmap2, int bits);
void __bitmap_xor(unsigned long *dst, const unsigned long *bitmap1,
		  const unsigned long *bitmap2, int bits);

static inline void bitmap_set(unsigned long *bmap, int start, int len)
{
	int bit;
	for (bit = start; bit < (start + len); bit++)
		bmap[BIT_WORD(bit)] |= (0x1UL << BIT_WORD_OFFSET(bit));
}

static inline void bitmap_clear(unsigned long *bmap, int start, int len)
{
	int bit;
	for (bit = start; bit < (start + len); bit++)
		bmap[BIT_WORD(bit)] &= ~(0x1UL << BIT_WORD_OFFSET(bit));
}

static inline void bitmap_zero(unsigned long *dst, int nbits)
{
	if (small_const_nbits(nbits))
		*dst = 0UL;
	else {
		size_t i, len = BITS_TO_LONGS(nbits);
		for (i = 0; i < len; i++)
			dst[i] = 0;
	}
}

static inline void bitmap_zero_except(unsigned long *dst,
				      int exception, int nbits)
{
	if (small_const_nbits(nbits))
		*dst = 0UL;
	else {
		size_t i, len = BITS_TO_LONGS(nbits);
		for (i = 0; i < len; i++)
			dst[i] = 0;
	}
	if (exception < nbits)
		__set_bit(exception, dst);
}

static inline void bitmap_fill(unsigned long *dst, int nbits)
{
	size_t i, nlongs = BITS_TO_LONGS(nbits);
	if (!small_const_nbits(nbits)) {
		for (i = 0; i < (nlongs - 1); i++)
			dst[i] = -1UL;
	}
	dst[nlongs - 1] = BITMAP_LAST_WORD_MASK(nbits);
}

static inline void bitmap_copy(unsigned long *dst,
			       const unsigned long *src, int nbits)
{
	if (small_const_nbits(nbits))
		*dst = *src;
	else {
		size_t i, len = BITS_TO_LONGS(nbits);
		for (i = 0; i < len; i++)
			dst[i] = src[i];
	}
}

static inline void bitmap_and(unsigned long *dst, const unsigned long *src1,
			      const unsigned long *src2, int nbits)
{
	if (small_const_nbits(nbits))
		*dst = *src1 & *src2;
	else
		__bitmap_and(dst, src1, src2, nbits);
}

static inline void bitmap_or(unsigned long *dst, const unsigned long *src1,
			     const unsigned long *src2, int nbits)
{
	if (small_const_nbits(nbits))
		*dst = *src1 | *src2;
	else
		__bitmap_or(dst, src1, src2, nbits);
}

static inline void bitmap_xor(unsigned long *dst, const unsigned long *src1,
			      const unsigned long *src2, int nbits)
{
	if (small_const_nbits(nbits))
		*dst = *src1 ^ *src2;
	else
		__bitmap_xor(dst, src1, src2, nbits);
}

#endif
