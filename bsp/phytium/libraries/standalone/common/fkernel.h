/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fkernel.h
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:35:07
 * Description:  This file is for kernel definition functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/10/20       first release
 * 1.1   zhugengyu  2022/2/17        add extra functionality
 */


#ifndef FKERNEL_H
#define FKERNEL_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __ASSEMBLY__
    #define _AC(X, Y) X
    #define _AT(T, X) X
#else
    #define __AC(X, Y) (X##Y)
    #define _AC(X, Y) __AC(X, Y)
    #define _AT(T, X) ((T)(X))
#endif

#define _UL(x) (_AC(x, UL))
#define _ULL(x) (_AC(x, ULL))

#define _BITUL(x) (_UL(1) << (x))
#define _BITULL(x) (_ULL(1) << (x))

#define UL(x) (_UL(x))
#define ULL(x) (_ULL(x))

#define min(x, y) (                    \
{                                  \
    typeof(x) _min1 = (x);         \
    typeof(y) _min2 = (y);         \
    (void)(&_min1 == &_min2);      \
    _min1 < _min2 ? _min1 : _min2; \
})

#define max(x, y) (                    \
{                                  \
    typeof(x) _max1 = (x);         \
    typeof(y) _max2 = (y);         \
    (void)(&_max1 == &_max2);      \
    _max1 > _max2 ? _max1 : _max2; \
})

#define min3(x, y, z) min((typeof(x))min(x, y), z)
#define max3(x, y, z) max((typeof(x))max(x, y), z)

#define min_t(type, a, b) min(((type) a), ((type) b))
#define max_t(type, a, b) max(((type) a), ((type) b))

/**
 * clamp - return a value clamped to a given range with strict typechecking
 * @val: current value
 * @lo: lowest allowable value
 * @hi: highest allowable value
 *
 * This macro does strict typechecking of @lo/@hi to make sure they are of the
 * same type as @val.  See the unnecessary pointer comparisons.
 */
#define clamp(val, lo, hi) min((typeof(val))max(val, lo), hi)

/**
 * do_div - returns 2 values: calculate remainder and update new dividend
 * @n: uint64_t dividend (will be updated)
 * @base: uint32_t divisor
 *
 * Summary:
 * ``uint32_t remainder = n % base;``
 * ``n = n / base;``
 *
 * Return: (uint32_t)remainder
 *
 * NOTE: macro parameter @n is evaluated multiple times,
 * beware of side effects!
 */
#define do_div(n, base) (                 \
{                                     \
    uint32_t __base = (base);         \
    uint32_t __rem;                   \
    __rem = ((uint64_t)(n)) % __base; \
    (n) = ((uint64_t)(n)) / __base;   \
    __rem;                            \
})

/* The `const' in roundup() prevents gcc-3.3 from calling __divdi3 */
#define roundup(x, y) (                  \
{                                    \
    const typeof(y) __y = y;         \
    ((x + (__y - 1)) / __y) * __y; \
})
#define rounddown(x, y) (    \
{                        \
    typeof(x) __x = (x); \
    __x - (__x % (y));   \
})

#define DIV_ROUND_UP(n, d) (((n) + (d)-1) / (d))

#if defined(__aarch64__)
    #define BITS_PER_LONG 64
#else
    #define BITS_PER_LONG 32
#endif

#ifndef BITS_PER_LONG_LONG
    #define BITS_PER_LONG_LONG 64
#endif

#define BIT(nr) (1ULL << (nr))
#define BIT_ULL(nr) (1ULL << (nr))
#define BIT_MASK(nr) (BIT(nr) - 1UL)
#define BIT_WORD(nr) ((nr) / BITS_PER_LONG)
#define BIT_ULL_MASK(nr) (1ULL << ((nr) % BITS_PER_LONG_LONG))
#define BIT_ULL_WORD(nr) ((nr) / BITS_PER_LONG_LONG)
#define BITS_PER_BYTE 8

#define DIV_ROUND_DOWN_ULL(ll, d) \
    ({ unsigned long long _tmp = (ll); do_div(_tmp, d); _tmp; })
#define DIV_ROUND_UP_ULL(ll, d)     DIV_ROUND_DOWN_ULL((ll) + (d) - 1, (d))

#if BITS_PER_LONG == 32
    #define DIV_ROUND_UP_SECTOR_T(ll,d) DIV_ROUND_UP_ULL(ll, d)
#else
    #define DIV_ROUND_UP_SECTOR_T(ll,d) DIV_ROUND_UP(ll,d)
#endif

/*
 * Create a contiguous bitmask starting at bit position @l and ending at
 * position @h. For example
 * GENMASK_ULL(39, 21) gives us the 64bit vector 0x000000ffffe00000.
 */
#define GENMASK(h, l) \
    (((~0UL) - (1UL << (l)) + 1) & (~0UL >> (BITS_PER_LONG - 1 - (h))))

#define GENMASK_ULL(h, l)            \
    (((~0ULL) - (1ULL << (l)) + 1) & \
     (~0ULL >> (BITS_PER_LONG_LONG - 1 - (h))))

#define SZ_1 0x00000001
#define SZ_2 0x00000002
#define SZ_4 0x00000004
#define SZ_8 0x00000008
#define SZ_16 0x00000010
#define SZ_32 0x00000020
#define SZ_64 0x00000040
#define SZ_128 0x00000080
#define SZ_256 0x00000100
#define SZ_512 0x00000200

#define SZ_1K 0x00000400
#define SZ_2K 0x00000800
#define SZ_4K 0x00001000
#define SZ_8K 0x00002000
#define SZ_16K 0x00004000
#define SZ_32K 0x00008000
#define SZ_64K 0x00010000
#define SZ_128K 0x00020000
#define SZ_256K 0x00040000
#define SZ_512K 0x00080000

#define SZ_1M 0x00100000
#define SZ_2M 0x00200000
#define SZ_4M 0x00400000
#define SZ_8M 0x00800000
#define SZ_16M 0x01000000
#define SZ_32M 0x02000000
#define SZ_64M 0x04000000
#define SZ_128M 0x08000000
#define SZ_256M 0x10000000
#define SZ_512M 0x20000000

#define SZ_1G 0x40000000
#define SZ_2G 0x80000000
#define SZ_3G 0xC0000000
#define SZ_4G 0x100000000ULL
#define SZ_8G 0x200000000ULL

#define NANO_TO_MICRO 1000
#define NANO_TO_KILO 1000000

/**
 * UPPER_32_BITS - return bits 32-63 of a number
 * @n: the number we're accessing
 *
 * A basic shift-right of a 64- or 32-bit quantity.  Use this to suppress
 * the "right shift count >= width of type" warning when that quantity is
 * 32-bits.
 * Note that do not input signed int 'n'
 */
#define UPPER_32_BITS(n) ((uint32_t)(((n) >> 16) >> 16))

/**
 * LOWER_32_BITS - return bits 0-31 of a number
 * @n: the number we're accessing
 * Note that do not input signed int 'n'
 */
#define LOWER_32_BITS(n) ((uint32_t)((n)&0xffffffff))
#define IS_ALIGNED(x, a) (((x) & ((typeof(x))(a)-1)) == 0)

#ifndef __aligned
    #define __aligned(x) __attribute__((__aligned__(x)))
#endif

/**
 * CONTAINER_OF - return the member address of ptr, if the type of ptr is the
 * struct type.
 */
#define CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

#ifndef ARRAY_SIZE
    #define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

/* set 32-bit register [a:b] as x, where a is high bit, b is low bit, x is setting/getting value */
#define GET_REG32_BITS(x, a, b)                  (u32)((((u32)(x)) & GENMASK(a, b)) >> b)
#define SET_REG32_BITS(x, a, b)                  (u32)((((u32)(x)) << b) & GENMASK(a, b))

/* Integer alignment down */
#define PALIGN_DOWN(x,align)    (x & ~(align-1))
/* Integer alignment up */
#define PALIGN_UP(x,align)      ((x + (align-1)) & ~(align-1))

#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

#define __BUILD_BUG_ON_NOT_POWER_OF_2(n)	\
	BUILD_BUG_ON(((n) & ((n) - 1)) != 0)
#define BUILD_BUG_ON_NOT_POWER_OF_2(n)			\
	BUILD_BUG_ON((n) == 0 || (((n) & ((n) - 1)) != 0))

/**
 * COMILETIME_ASSERT - break build and emit msg if condition is false
 * @condition: a compile-time constant condition to check
 * @msg:       a message to emit if condition is false
 *
 * In tradition of POSIX assert, this macro will break the build if the
 * supplied condition is *false*, emitting the supplied error message if the
 * compiler has support to do so.
 */
# define COMILETIME_ASSERT(condition, msg, prefix, suffix)		\
	do {								\
		extern void prefix ## suffix(void) __attribute__((error(msg))); \
		if (!(condition))					\
			prefix ## suffix();				\
	} while (0)
 
/**
 * BUILD_BUG_ON_MSG - break compile if a condition is true & emit supplied
 *		      error message.
 * @condition: the condition which the compiler should know is false.
 *
 * See BUILD_BUG_ON for description.
 */
#define BUILD_BUG_ON_MSG(cond, msg) COMILETIME_ASSERT(!(cond), msg, __compiletime_assert_, __COUNTER__)

/*
 * Bitfield access macros
 *
 * FIELD_{GET,PREP} macros take as first parameter shifted mask
 * from which they extract the base mask and shift amount.
 * Mask must be a compilation time constant.
 *
 * Example:
 *
 *  #define REG_FIELD_A  GENMASK(6, 0)
 *  #define REG_FIELD_B  BIT(7)
 *  #define REG_FIELD_C  GENMASK(15, 8)
 *  #define REG_FIELD_D  GENMASK(31, 16)
 *
 * Get:
 *  a = FIELD_GET(REG_FIELD_A, reg);
 *  b = FIELD_GET(REG_FIELD_B, reg);
 *
 * Set:
 *  reg = FIELD_PREP(REG_FIELD_A, 1) |
 *	  FIELD_PREP(REG_FIELD_B, 0) |
 *	  FIELD_PREP(REG_FIELD_C, c) |
 *	  FIELD_PREP(REG_FIELD_D, 0x40);
 *
 * Modify:
 *  reg &= ~REG_FIELD_C;
 *  reg |= FIELD_PREP(REG_FIELD_C, c);
 */

#define BF_SHF(x) (__builtin_ffsll(x) - 1)

#define BF_FIELD_CHECK(mask, reg, val, pfx)			\
	({								\
		BUILD_BUG_ON_MSG(!__builtin_constant_p(mask),		\
				 pfx "mask is not constant");		\
		BUILD_BUG_ON_MSG((mask) == 0, pfx "mask is zero");	\
		BUILD_BUG_ON_MSG(__builtin_constant_p(val) ?		\
				 ~((mask) >> BF_SHF(mask)) & (val) : 0, \
				 pfx "value too large for the field"); \
		BUILD_BUG_ON_MSG((mask) > (typeof(reg))~0ull,		\
				 pfx "type of reg too small for mask"); \
		__BUILD_BUG_ON_NOT_POWER_OF_2((mask) +			\
					      (1ULL << BF_SHF(mask))); \
	})


/**
 * FIELD_PREP() - prepare a bitfield element
 * @mask: shifted mask defining the field's length and position
 * @val:  value to put in the field
 *
 * FIELD_PREP() masks and shifts up the value.  The result should
 * be combined with other fields of the bitfield using logical OR.
 */
#define FIELD_PREP(mask, val)						\
	({								\
		BF_FIELD_CHECK(mask, 0ULL, val, "FIELD_PREP: ");	\
		((typeof(mask))(val) << BF_SHF(mask)) & (mask);	\
	})

#ifdef __cplusplus
}
#endif

#endif