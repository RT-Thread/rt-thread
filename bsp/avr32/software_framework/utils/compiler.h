/**
 * \file
 *
 * \brief Commonly used includes, types and macros.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _COMPILER_AVR32_H_
#define _COMPILER_AVR32_H_

/**
 * \defgroup group_avr32_utils Compiler abstraction layer and code utilities
 *
 * Compiler abstraction layer and code utilities for 32-bit AVR.
 * This module provides various abstraction layers and utilities to make code compatible between different compilers.
 *
 * \{
 */

#if (defined __ICCAVR32__)
#  include <intrinsics.h>
#endif
#include "preprocessor.h"

#include <parts.h>
#include <avr32/io.h>
#include "header_files/uc3d_defines_fix.h"
#include "header_files/uc3l3_l4_defines_fix.h"

//_____ D E C L A R A T I O N S ____________________________________________

#ifdef __AVR32_ABI_COMPILER__ // Automatically defined when compiling for AVR32, not when assembling.

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


#if (defined __ICCAVR32__)

/*! \name Compiler Keywords
 *
 * Port of some keywords from GNU GCC for AVR32 to IAR Embedded Workbench for Atmel AVR32.
 */
//! @{
#define __asm__             asm
#define __inline__          inline
#define __volatile__
//! @}
#endif

/**
 * \def UNUSED
 * \brief Marking \a v as a unused parameter or value.
 */
#define UNUSED(v)          (void)(v)

/**
 * \def unused
 * \brief Marking \a v as a unused parameter or value.
 */
#define unused(v)          do { (void)(v); } while(0)

/**
 * \def barrier
 * \brief Memory barrier
 */
#if defined(__GNUC__)
#  define barrier()        asm volatile("" ::: "memory")
#elif defined(__ICCAVR32__)
#  define barrier()        __asm__ __volatile__ ("")
#endif

/**
 * \brief Emit the compiler pragma \a arg.
 *
 * \param arg The pragma directive as it would appear after \e \#pragma
 * (i.e. not stringified).
 */
#define COMPILER_PRAGMA(arg)            _Pragma(#arg)

/**
 * \def COMPILER_PACK_SET(alignment)
 * \brief Set maximum alignment for subsequent struct and union
 * definitions to \a alignment.
 */
#define COMPILER_PACK_SET(alignment)   COMPILER_PRAGMA(pack(alignment))

/**
 * \def COMPILER_PACK_RESET()
 * \brief Set default alignment for subsequent struct and union
 * definitions.
 */
#define COMPILER_PACK_RESET()          COMPILER_PRAGMA(pack())


/**
 * \brief Set aligned boundary.
 */
#if (defined __GNUC__)
#define COMPILER_ALIGNED(a)    __attribute__((__aligned__(a)))
#elif (defined __ICCAVR32__)
#define COMPILER_ALIGNED(a)    COMPILER_PRAGMA(data_alignment = a)
#endif

/**
 * \brief Set word-aligned boundary.
 */
#if (defined __GNUC__)
#define COMPILER_WORD_ALIGNED    __attribute__((__aligned__(4)))
#elif (defined __ICCAVR32__)
#define COMPILER_WORD_ALIGNED    COMPILER_PRAGMA(data_alignment = 4)
#endif

/**
 * \name System Register Access
 * @{
 */
#if defined(__GNUC__) || defined(__DOXYGEN__)
/**
  * \brief Get value of system register
 *
 * \param reg Address of the system register of which to get the value.
 *
 * \return Value of system register \a reg.
 */
#  define sysreg_read(reg)               __builtin_mfsr(reg)

/**
 * \name Tag functions as deprecated
 *
 * Tagging a function as deprecated will produce a warning when and only
 * when the function is called.
 *
 * Usage is to add the __DEPRECATED__ symbol before the function definition.
 * E.g.:
 * __DEPRECATED__ uint8_t some_deprecated_function (void)
 * {
 *     ...
 * }
 *
 * \note Only supported by GCC 3.1 and above, no IAR support
 * @{
 */
#if ((defined __GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >=1)))
#define __DEPRECATED__  __attribute__((__deprecated__))
#else
#define __DEPRECATED__
#endif
//! @}

/**
 * \brief Set value of system register
 *
 * \param reg Address of the system register of which to set the value.
 * \param val Value to set the system register \a reg to.
 */
#  define sysreg_write(reg, val)         __builtin_mtsr(reg, val)

#elif defined(__ICCAVR32__)
#  define sysreg_read(reg)               __get_system_register(reg)
#  define sysreg_write(reg, val)         __set_system_register(reg, val)
#endif

// Deprecated definitions
#define Get_system_register(reg)         sysreg_read(reg)
#define Set_system_register(reg, val)    sysreg_write(reg, val)
//! @}

#include "interrupt.h"

/*! \name Usual Types
 */
//! @{
typedef unsigned char           Bool; //!< Boolean.
#ifndef __cplusplus
#if !defined(__bool_true_false_are_defined)
typedef unsigned char           bool; //!< Boolean.
#endif
#endif
typedef int8_t                  S8 ;  //!< 8-bit signed integer.
typedef uint8_t                 U8 ;  //!< 8-bit unsigned integer.
typedef int16_t                 S16;  //!< 16-bit signed integer.
typedef uint16_t                U16;  //!< 16-bit unsigned integer.
typedef uint16_t                le16_t;
typedef uint16_t                be16_t;
typedef int32_t                 S32;  //!< 32-bit signed integer.
typedef uint32_t                U32;  //!< 32-bit unsigned integer.
typedef uint32_t                le32_t;
typedef uint32_t                be32_t;
typedef signed long long int    S64;  //!< 64-bit signed integer.
typedef unsigned long long int  U64;  //!< 64-bit unsigned integer.
typedef float                   F32;  //!< 32-bit floating-point number.
typedef double                  F64;  //!< 64-bit floating-point number.
typedef uint32_t                iram_size_t;
//! @}


/*! \name Status Types
 */
//! @{
typedef bool                Status_bool_t;  //!< Boolean status.
typedef U8                  Status_t;       //!< 8-bit-coded status.
//! @}


/*! \name Aliasing Aggregate Types
 */
//! @{

//! 16-bit union.
typedef union
{
  S16 s16   ;
  U16 u16   ;
  S8  s8 [2];
  U8  u8 [2];
} Union16;

//! 32-bit union.
typedef union
{
  S32 s32   ;
  U32 u32   ;
  S16 s16[2];
  U16 u16[2];
  S8  s8 [4];
  U8  u8 [4];
} Union32;

//! 64-bit union.
typedef union
{
  S64 s64   ;
  U64 u64   ;
  S32 s32[2];
  U32 u32[2];
  S16 s16[4];
  U16 u16[4];
  S8  s8 [8];
  U8  u8 [8];
} Union64;

//! Union of pointers to 64-, 32-, 16- and 8-bit unsigned integers.
typedef union
{
  S64 *s64ptr;
  U64 *u64ptr;
  S32 *s32ptr;
  U32 *u32ptr;
  S16 *s16ptr;
  U16 *u16ptr;
  S8  *s8ptr ;
  U8  *u8ptr ;
} UnionPtr;

//! Union of pointers to volatile 64-, 32-, 16- and 8-bit unsigned integers.
typedef union
{
  volatile S64 *s64ptr;
  volatile U64 *u64ptr;
  volatile S32 *s32ptr;
  volatile U32 *u32ptr;
  volatile S16 *s16ptr;
  volatile U16 *u16ptr;
  volatile S8  *s8ptr ;
  volatile U8  *u8ptr ;
} UnionVPtr;

//! Union of pointers to constant 64-, 32-, 16- and 8-bit unsigned integers.
typedef union
{
  const S64 *s64ptr;
  const U64 *u64ptr;
  const S32 *s32ptr;
  const U32 *u32ptr;
  const S16 *s16ptr;
  const U16 *u16ptr;
  const S8  *s8ptr ;
  const U8  *u8ptr ;
} UnionCPtr;

//! Union of pointers to constant volatile 64-, 32-, 16- and 8-bit unsigned integers.
typedef union
{
  const volatile S64 *s64ptr;
  const volatile U64 *u64ptr;
  const volatile S32 *s32ptr;
  const volatile U32 *u32ptr;
  const volatile S16 *s16ptr;
  const volatile U16 *u16ptr;
  const volatile S8  *s8ptr ;
  const volatile U8  *u8ptr ;
} UnionCVPtr;

//! Structure of pointers to 64-, 32-, 16- and 8-bit unsigned integers.
typedef struct
{
  S64 *s64ptr;
  U64 *u64ptr;
  S32 *s32ptr;
  U32 *u32ptr;
  S16 *s16ptr;
  U16 *u16ptr;
  S8  *s8ptr ;
  U8  *u8ptr ;
} StructPtr;

//! Structure of pointers to volatile 64-, 32-, 16- and 8-bit unsigned integers.
typedef struct
{
  volatile S64 *s64ptr;
  volatile U64 *u64ptr;
  volatile S32 *s32ptr;
  volatile U32 *u32ptr;
  volatile S16 *s16ptr;
  volatile U16 *u16ptr;
  volatile S8  *s8ptr ;
  volatile U8  *u8ptr ;
} StructVPtr;

//! Structure of pointers to constant 64-, 32-, 16- and 8-bit unsigned integers.
typedef struct
{
  const S64 *s64ptr;
  const U64 *u64ptr;
  const S32 *s32ptr;
  const U32 *u32ptr;
  const S16 *s16ptr;
  const U16 *u16ptr;
  const S8  *s8ptr ;
  const U8  *u8ptr ;
} StructCPtr;

//! Structure of pointers to constant volatile 64-, 32-, 16- and 8-bit unsigned integers.
typedef struct
{
  const volatile S64 *s64ptr;
  const volatile U64 *u64ptr;
  const volatile S32 *s32ptr;
  const volatile U32 *u32ptr;
  const volatile S16 *s16ptr;
  const volatile U16 *u16ptr;
  const volatile S8  *s8ptr ;
  const volatile U8  *u8ptr ;
} StructCVPtr;

//! @}

#endif  // __AVR32_ABI_COMPILER__


//_____ M A C R O S ________________________________________________________

/*! \name Usual Constants
 */
//! @{
#define DISABLE   0
#define ENABLE    1
#ifndef __cplusplus
#if !defined(__bool_true_false_are_defined)
#define false     0
#define true      1
#endif
#endif
#define PASS      0
#define FAIL      1
#define LOW       0
#define HIGH      1
//! @}


#ifdef __AVR32_ABI_COMPILER__ // Automatically defined when compiling for AVR32, not when assembling.

//! \name Optimization Control
//@{

/**
 * \def likely(exp)
 * \brief The expression \a exp is likely to be true
 */
#ifndef likely
# define likely(exp)    (exp)
#endif

/**
 * \def unlikely(exp)
 * \brief The expression \a exp is unlikely to be true
 */
#ifndef unlikely
# define unlikely(exp)  (exp)
#endif

/**
 * \def is_constant(exp)
 * \brief Determine if an expression evaluates to a constant value.
 *
 * \param exp Any expression
 *
 * \return true if \a exp is constant, false otherwise.
 */
#ifdef __GNUC__
# define is_constant(exp)       __builtin_constant_p(exp)
#else
# define is_constant(exp)       (0)
#endif

//! @}

/*! \name Bit-Field Handling
 */
//! @{

/*! \brief Reads the bits of a value specified by a given bit-mask.
 *
 * \param value Value to read bits from.
 * \param mask  Bit-mask indicating bits to read.
 *
 * \return Read bits.
 */
#define Rd_bits( value, mask)        ((value) & (mask))

/*! \brief Writes the bits of a C lvalue specified by a given bit-mask.
 *
 * \param lvalue  C lvalue to write bits to.
 * \param mask    Bit-mask indicating bits to write.
 * \param bits    Bits to write.
 *
 * \return Resulting value with written bits.
 */
#define Wr_bits(lvalue, mask, bits)  ((lvalue) = ((lvalue) & ~(mask)) |\
                                                 ((bits  ) &  (mask)))

/*! \brief Tests the bits of a value specified by a given bit-mask.
 *
 * \param value Value of which to test bits.
 * \param mask  Bit-mask indicating bits to test.
 *
 * \return \c 1 if at least one of the tested bits is set, else \c 0.
 */
#define Tst_bits( value, mask)  (Rd_bits(value, mask) != 0)

/*! \brief Clears the bits of a C lvalue specified by a given bit-mask.
 *
 * \param lvalue  C lvalue of which to clear bits.
 * \param mask    Bit-mask indicating bits to clear.
 *
 * \return Resulting value with cleared bits.
 */
#define Clr_bits(lvalue, mask)  ((lvalue) &= ~(mask))

/*! \brief Sets the bits of a C lvalue specified by a given bit-mask.
 *
 * \param lvalue  C lvalue of which to set bits.
 * \param mask    Bit-mask indicating bits to set.
 *
 * \return Resulting value with set bits.
 */
#define Set_bits(lvalue, mask)  ((lvalue) |=  (mask))

/*! \brief Toggles the bits of a C lvalue specified by a given bit-mask.
 *
 * \param lvalue  C lvalue of which to toggle bits.
 * \param mask    Bit-mask indicating bits to toggle.
 *
 * \return Resulting value with toggled bits.
 */
#define Tgl_bits(lvalue, mask)  ((lvalue) ^=  (mask))

/*! \brief Reads the bit-field of a value specified by a given bit-mask.
 *
 * \param value Value to read a bit-field from.
 * \param mask  Bit-mask indicating the bit-field to read.
 *
 * \return Read bit-field.
 */
#define Rd_bitfield( value, mask)           (Rd_bits( value, mask) >> ctz(mask))

/*! \brief Writes the bit-field of a C lvalue specified by a given bit-mask.
 *
 * \param lvalue    C lvalue to write a bit-field to.
 * \param mask      Bit-mask indicating the bit-field to write.
 * \param bitfield  Bit-field to write.
 *
 * \return Resulting value with written bit-field.
 */
#define Wr_bitfield(lvalue, mask, bitfield) (Wr_bits(lvalue, mask, (U32)(bitfield) << ctz(mask)))

//! @}


/*! \brief This macro makes the CPU take a small break for a few cycles. This should
 *         be used when waiting for an event. It will reduce the internal bus load.
 *
 * "sub pc, pc, -4" (or "sub pc, -2") forces the IF stage to wait until the result
 * of the calculation before it can fetch the next instruction. This makes sure
 * there are nothing stuck in the LS pipe when you start a new iteration and guarantee
 * to flush the pipeline without having any other effect.
 * (A nop doesn't have any effect on the IF stage.)
 */
#if (defined __GNUC__)
# define cpu_relax()             __asm__ __volatile__("sub pc, pc, -4" ::: "memory", "cc")
#elif (defined __ICCAVR32__)
# define cpu_relax()             __asm__ __volatile__("sub pc, pc, -4")
#endif


/*! \brief This macro is used to test fatal errors.
 *
 * The macro tests if the expression is false. If it is, a fatal error is
 * detected and the application hangs up. If TEST_SUITE_DEFINE_ASSERT_MACRO
 * is defined, a unit test version of the macro is used, to allow execution
 * of further tests after a false expression.
 *
 * \param expr  Expression to evaluate and supposed to be nonzero.
 */
#if defined(_ASSERT_ENABLE_)
#  if defined(TEST_SUITE_DEFINE_ASSERT_MACRO)
	// Assert() is defined in unit_test/suite.h
#    include "unit_test/suite.h"
#  else
#    define Assert(expr) \
	{\
		if (!(expr)) while (true);\
	}
#  endif
#else
#  define Assert(expr) ((void) 0)
#endif


/*! \name Zero-Bit Counting
 *
 * Under AVR32-GCC, __builtin_clz and __builtin_ctz behave like macros when
 * applied to constant expressions (values known at compile time), so they are
 * more optimized than the use of the corresponding assembly instructions and
 * they can be used as constant expressions e.g. to initialize objects having
 * static storage duration, and like the corresponding assembly instructions
 * when applied to non-constant expressions (values unknown at compile time), so
 * they are more optimized than an assembly periphrasis. Hence, clz and ctz
 * ensure a possible and optimized behavior for both constant and non-constant
 * expressions.
 */
//! @{

/*! \brief Counts the leading zero bits of the given value considered as a 32-bit integer.
 *
 * \param u Value of which to count the leading zero bits.
 *
 * \return The count of leading zero bits in \a u.
 */
#if (defined __GNUC__)
  #define clz(u)              ((u) ? __builtin_clz(u) : 32)
#elif (defined __ICCAVR32__)
  #if (__VER__ == 330) && (__SUBVERSION__ <= 1)
    // __count_leading_zeros is broken and returns a value which is offset by
    // -32 when called with a constant parameter.
    #define clz(v) (0 == v ? 32 : (31 & __count_leading_zeros(v)))
  #else
    #define clz(v) __count_leading_zeros(v)
  #endif
#endif

/*! \brief Counts the trailing zero bits of the given value considered as a 32-bit integer.
 *
 * \param u Value of which to count the trailing zero bits.
 *
 * \return The count of trailing zero bits in \a u.
 */
#if (defined __GNUC__)
  #define ctz(u)              ((u) ? __builtin_ctz(u) : 32)
#elif (defined __ICCAVR32__)
  #define ctz(u)              __count_trailing_zeros(u)
#endif

//! @}

//! \name Logarithmic functions
//! @{

/**
 * \internal
 * Undefined function. Will cause a link failure if ilog2() is called
 * with an invalid constant value.
 */
int_fast8_t ilog2_undefined(void);

/**
 * \brief Calculate the base-2 logarithm of a number rounded down to
 * the nearest integer.
 *
 * \param x A 32-bit value
 * \return The base-2 logarithm of \a x, or -1 if \a x is 0.
 */
static inline int_fast8_t ilog2(uint32_t x)
{
	if (is_constant(x))
		return ((x) & (1ULL << 31) ? 31 :
			(x) & (1ULL << 30) ? 30 :
			(x) & (1ULL << 29) ? 29 :
			(x) & (1ULL << 28) ? 28 :
			(x) & (1ULL << 27) ? 27 :
			(x) & (1ULL << 26) ? 26 :
			(x) & (1ULL << 25) ? 25 :
			(x) & (1ULL << 24) ? 24 :
			(x) & (1ULL << 23) ? 23 :
			(x) & (1ULL << 22) ? 22 :
			(x) & (1ULL << 21) ? 21 :
			(x) & (1ULL << 20) ? 20 :
			(x) & (1ULL << 19) ? 19 :
			(x) & (1ULL << 18) ? 18 :
			(x) & (1ULL << 17) ? 17 :
			(x) & (1ULL << 16) ? 16 :
			(x) & (1ULL << 15) ? 15 :
			(x) & (1ULL << 14) ? 14 :
			(x) & (1ULL << 13) ? 13 :
			(x) & (1ULL << 12) ? 12 :
			(x) & (1ULL << 11) ? 11 :
			(x) & (1ULL << 10) ? 10 :
			(x) & (1ULL <<  9) ?  9 :
			(x) & (1ULL <<  8) ?  8 :
			(x) & (1ULL <<  7) ?  7 :
			(x) & (1ULL <<  6) ?  6 :
			(x) & (1ULL <<  5) ?  5 :
			(x) & (1ULL <<  4) ?  4 :
			(x) & (1ULL <<  3) ?  3 :
			(x) & (1ULL <<  2) ?  2 :
			(x) & (1ULL <<  1) ?  1 :
			(x) & (1ULL <<  0) ?  0 :
			ilog2_undefined());

	return 31 - clz(x);
}

//! @}

/*! \name Bit Reversing
 */
//! @{

/*! \brief Reverses the bits of \a u8.
 *
 * \param u8  U8 of which to reverse the bits.
 *
 * \return Value resulting from \a u8 with reversed bits.
 */
#define bit_reverse8(u8)    ((U8)(bit_reverse32((U8)(u8)) >> 24))

/*! \brief Reverses the bits of \a u16.
 *
 * \param u16 U16 of which to reverse the bits.
 *
 * \return Value resulting from \a u16 with reversed bits.
 */
#define bit_reverse16(u16)  ((U16)(bit_reverse32((U16)(u16)) >> 16))

/*! \brief Reverses the bits of \a u32.
 *
 * \param u32 U32 of which to reverse the bits.
 *
 * \return Value resulting from \a u32 with reversed bits.
 */
#if (defined __GNUC__)
  #define bit_reverse32(u32) \
  (\
    {\
      unsigned int __value = (U32)(u32);\
      __asm__ ("brev\t%0" : "+r" (__value) :  : "cc");\
      (U32)__value;\
    }\
  )
#elif (defined __ICCAVR32__)
  #define bit_reverse32(u32)  ((U32)__bit_reverse((U32)(u32)))
#endif

/*! \brief Reverses the bits of \a u64.
 *
 * \param u64 U64 of which to reverse the bits.
 *
 * \return Value resulting from \a u64 with reversed bits.
 */
#define bit_reverse64(u64)  ((U64)(((U64)bit_reverse32((U64)(u64) >> 32)) |\
                                   ((U64)bit_reverse32((U64)(u64)) << 32)))

//! @}


/*! \name Alignment
 */
//! @{

/*! \brief Tests alignment of the number \a val with the \a n boundary.
 *
 * \param val Input value.
 * \param n   Boundary.
 *
 * \return \c 1 if the number \a val is aligned with the \a n boundary, else \c 0.
 */
#define Test_align(val, n     ) (!Tst_bits( val, (n) - 1     )   )

/*! \brief Gets alignment of the number \a val with respect to the \a n boundary.
 *
 * \param val Input value.
 * \param n   Boundary.
 *
 * \return Alignment of the number \a val with respect to the \a n boundary.
 */
#define Get_align( val, n     ) (  Rd_bits( val, (n) - 1     )   )

/*! \brief Sets alignment of the lvalue number \a lval to \a alg with respect to the \a n boundary.
 *
 * \param lval  Input/output lvalue.
 * \param n     Boundary.
 * \param alg   Alignment.
 *
 * \return New value of \a lval resulting from its alignment set to \a alg with respect to the \a n boundary.
 */
#define Set_align(lval, n, alg) (  Wr_bits(lval, (n) - 1, alg)   )

/*! \brief Aligns the number \a val with the upper \a n boundary.
 *
 * \param val Input value.
 * \param n   Boundary.
 *
 * \return Value resulting from the number \a val aligned with the upper \a n boundary.
 */
#define Align_up(  val, n     ) (((val) + ((n) - 1)) & ~((n) - 1))

/*! \brief Aligns the number \a val with the lower \a n boundary.
 *
 * \param val Input value.
 * \param n   Boundary.
 *
 * \return Value resulting from the number \a val aligned with the lower \a n boundary.
 */
#define Align_down(val, n     ) ( (val)              & ~((n) - 1))

//! @}


/*! \name Mathematics
 *
 * The same considerations as for clz and ctz apply here but AVR32-GCC does not
 * provide built-in functions to access the assembly instructions abs, min and
 * max and it does not produce them by itself in most cases, so two sets of
 * macros are defined here:
 *   - Abs, Min and Max to apply to constant expressions (values known at
 *     compile time);
 *   - abs, min and max to apply to non-constant expressions (values unknown at
 *     compile time).
 */
//! @{

/*! \brief Takes the absolute value of \a a.
 *
 * \param a Input value.
 *
 * \return Absolute value of \a a.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Abs(a)              (((a) <  0 ) ? -(a) : (a))

/*! \brief Takes the minimal value of \a a and \a b.
 *
 * \param a Input value.
 * \param b Input value.
 *
 * \return Minimal value of \a a and \a b.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Min(a, b)           (((a) < (b)) ?  (a) : (b))

/*! \brief Takes the maximal value of \a a and \a b.
 *
 * \param a Input value.
 * \param b Input value.
 *
 * \return Maximal value of \a a and \a b.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Max(a, b)           (((a) > (b)) ?  (a) : (b))

/*! \brief Takes the absolute value of \a a.
 *
 * \param a Input value.
 *
 * \return Absolute value of \a a.
 *
 * \note More optimized if only used with values unknown at compile time.
 */
#if (defined __GNUC__)
  #define abs(a) \
  (\
    {\
      int __value = (a);\
      __asm__ ("abs\t%0" : "+r" (__value) :  : "cc");\
      __value;\
    }\
  )
#elif (defined __ICCAVR32__)
  #define abs(a)      Abs(a)
#endif

/*! \brief Takes the minimal value of \a a and \a b.
 *
 * \param a Input value.
 * \param b Input value.
 *
 * \return Minimal value of \a a and \a b.
 *
 * \note More optimized if only used with values unknown at compile time.
 */
#if (defined __GNUC__)
  #define min(a, b) \
  (\
    {\
      int __value, __arg_a = (a), __arg_b = (b);\
      __asm__ ("min\t%0, %1, %2" : "=r" (__value) : "r" (__arg_a), "r" (__arg_b));\
      __value;\
    }\
  )
#elif (defined __ICCAVR32__)
  #define min(a, b)   __min(a, b)
#endif

/*! \brief Takes the maximal value of \a a and \a b.
 *
 * \param a Input value.
 * \param b Input value.
 *
 * \return Maximal value of \a a and \a b.
 *
 * \note More optimized if only used with values unknown at compile time.
 */
#if (defined __GNUC__)
  #define max(a, b) \
  (\
    {\
      int __value, __arg_a = (a), __arg_b = (b);\
      __asm__ ("max\t%0, %1, %2" : "=r" (__value) : "r" (__arg_a), "r" (__arg_b));\
      __value;\
    }\
  )
#elif (defined __ICCAVR32__)
  #define max(a, b)   __max(a, b)
#endif

//! @}


/*! \brief Calls the routine at address \a addr.
 *
 * It generates a long call opcode.
 *
 * For example, `Long_call(0x80000000)' generates a software reset on a UC3 if
 * it is invoked from the CPU supervisor mode.
 *
 * \param addr  Address of the routine to call.
 *
 * \note It may be used as a long jump opcode in some special cases.
 */
#define Long_call(addr)                   ((*(void (*)(void))(addr))())

/*! \brief Resets the CPU by software.
 *
 * \warning It shall not be called from the CPU application mode.
 */
#if (defined __GNUC__)
  #define Reset_CPU() \
  (\
    {\
      __asm__ __volatile__ (\
        "lddpc   r9, 3f\n\t"\
        "mfsr    r8, %[SR]\n\t"\
        "bfextu  r8, r8, %[SR_M_OFFSET], %[SR_M_SIZE]\n\t"\
        "cp.w    r8, 0b001\n\t"\
        "breq    0f\n\t"\
        "sub     r8, pc, $ - 1f\n\t"\
        "pushm   r8-r9\n\t"\
        "rete\n"\
        "0:\n\t"\
        "mtsr    %[SR], r9\n"\
        "1:\n\t"\
        "mov     r0, 0\n\t"\
        "mov     r1, 0\n\t"\
        "mov     r2, 0\n\t"\
        "mov     r3, 0\n\t"\
        "mov     r4, 0\n\t"\
        "mov     r5, 0\n\t"\
        "mov     r6, 0\n\t"\
        "mov     r7, 0\n\t"\
        "mov     r8, 0\n\t"\
        "mov     r9, 0\n\t"\
        "mov     r10, 0\n\t"\
        "mov     r11, 0\n\t"\
        "mov     r12, 0\n\t"\
        "mov     sp, 0\n\t"\
        "stdsp   sp[0], sp\n\t"\
        "ldmts   sp, sp\n\t"\
        "mov     lr, 0\n\t"\
        "lddpc   pc, 2f\n\t"\
        ".balign 4\n"\
        "2:\n\t"\
        ".word   _start\n"\
        "3:\n\t"\
        ".word   %[RESET_SR]"\
        :\
        : [SR] "i" (AVR32_SR),\
          [SR_M_OFFSET] "i" (AVR32_SR_M_OFFSET),\
          [SR_M_SIZE] "i" (AVR32_SR_M_SIZE),\
          [RESET_SR] "i" (AVR32_SR_GM_MASK | AVR32_SR_EM_MASK | (AVR32_SR_M_SUP << AVR32_SR_M_OFFSET))\
      );\
    }\
  )
#elif (defined __ICCAVR32__)
  #define Reset_CPU() \
  {\
    extern void *volatile __program_start;\
    __asm__ __volatile__ (\
      "mov     r7, LWRD(__program_start)\n\t"\
      "orh     r7, HWRD(__program_start)\n\t"\
      "mov     r9, LWRD("ASTRINGZ(AVR32_SR_GM_MASK | AVR32_SR_EM_MASK | (AVR32_SR_M_SUP << AVR32_SR_M_OFFSET))")\n\t"\
      "orh     r9, HWRD("ASTRINGZ(AVR32_SR_GM_MASK | AVR32_SR_EM_MASK | (AVR32_SR_M_SUP << AVR32_SR_M_OFFSET))")\n\t"\
      "mfsr    r8, "ASTRINGZ(AVR32_SR)"\n\t"\
      "bfextu  r8, r8, "ASTRINGZ(AVR32_SR_M_OFFSET)", "ASTRINGZ(AVR32_SR_M_SIZE)"\n\t"\
      "cp.w    r8, 001b\n\t"\
      "breq    $ + 10\n\t"\
      "sub     r8, pc, -12\n\t"\
      "pushm   r8-r9\n\t"\
      "rete\n\t"\
      "mtsr    "ASTRINGZ(AVR32_SR)", r9\n\t"\
      "mov     r0, 0\n\t"\
      "mov     r1, 0\n\t"\
      "mov     r2, 0\n\t"\
      "mov     r3, 0\n\t"\
      "mov     r4, 0\n\t"\
      "mov     r5, 0\n\t"\
      "mov     r6, 0\n\t"\
      "st.w    r0[4], r7\n\t"\
      "mov     r7, 0\n\t"\
      "mov     r8, 0\n\t"\
      "mov     r9, 0\n\t"\
      "mov     r10, 0\n\t"\
      "mov     r11, 0\n\t"\
      "mov     r12, 0\n\t"\
      "mov     sp, 0\n\t"\
      "stdsp   sp[0], sp\n\t"\
      "ldmts   sp, sp\n\t"\
      "mov     lr, 0\n\t"\
      "ld.w    pc, lr[4]"\
    );\
    __program_start;\
  }
#endif



/*! \name CPU Status Register Access
 */
//! @{

/*! \brief Tells whether exceptions are globally enabled.
 *
 * \return \c 1 if exceptions are globally enabled, else \c 0.
 */
#define Is_global_exception_enabled()         (!Tst_bits(Get_system_register(AVR32_SR), AVR32_SR_EM_MASK))

/*! \brief Disables exceptions globally.
 */
#if (defined __GNUC__)
  #define Disable_global_exception()          ({__asm__ __volatile__ ("ssrf\t%0" :  : "i" (AVR32_SR_EM_OFFSET));})
#elif (defined __ICCAVR32__)
  #define Disable_global_exception()          (__set_status_flag(AVR32_SR_EM_OFFSET))
#endif

/*! \brief Enables exceptions globally.
 */
#if (defined __GNUC__)
  #define Enable_global_exception()           ({__asm__ __volatile__ ("csrf\t%0" :  : "i" (AVR32_SR_EM_OFFSET));})
#elif (defined __ICCAVR32__)
  #define Enable_global_exception()           (__clear_status_flag(AVR32_SR_EM_OFFSET))
#endif

//! @}


/*! \name Debug Register Access
 */
//! @{

/*! \brief Gets the value of the \a dbgreg debug register.
 *
 * \param dbgreg  Address of the debug register of which to get the value.
 *
 * \return Value of the \a dbgreg debug register.
 */
#if (defined __GNUC__)
  #define Get_debug_register(dbgreg)          __builtin_mfdr(dbgreg)
#elif (defined __ICCAVR32__)
  #define Get_debug_register(dbgreg)          __get_debug_register(dbgreg)
#endif

/*! \brief Sets the value of the \a dbgreg debug register to \a value.
 *
 * \param dbgreg  Address of the debug register of which to set the value.
 * \param value   Value to set the \a dbgreg debug register to.
 */
#if (defined __GNUC__)
  #define Set_debug_register(dbgreg, value)   __builtin_mtdr(dbgreg, value)
#elif (defined __ICCAVR32__)
  #define Set_debug_register(dbgreg, value)   __set_debug_register(dbgreg, value)
#endif

//! @}


/*! \name Force Assembly Inline Code Section
 */
//! @{
#if (defined __GNUC__)
#define __always_inline     inline __attribute__((__always_inline__))
#elif (defined __ICCAVR32__)
#define __always_inline     _Pragma("inline=forced")
#endif
//! @}

/*! \name MCU Endianism Handling
 * AVR32 is MCU big endianism.
 */
//! @{
#define  MSB(u16)       (((U8  *)&(u16))[0]) //!< Most significant byte of \a u16.
#define  LSB(u16)       (((U8  *)&(u16))[1]) //!< Least significant byte of \a u16.

#define  MSH(u32)       (((U16 *)&(u32))[0]) //!< Most significant half-word of \a u32.
#define  LSH(u32)       (((U16 *)&(u32))[1]) //!< Least significant half-word of \a u32.
#define  MSB0W(u32)     (((U8  *)&(u32))[0]) //!< Most significant byte of 1st rank of \a u32.
#define  MSB1W(u32)     (((U8  *)&(u32))[1]) //!< Most significant byte of 2nd rank of \a u32.
#define  MSB2W(u32)     (((U8  *)&(u32))[2]) //!< Most significant byte of 3rd rank of \a u32.
#define  MSB3W(u32)     (((U8  *)&(u32))[3]) //!< Most significant byte of 4th rank of \a u32.
#define  LSB3W(u32)     MSB0W(u32)           //!< Least significant byte of 4th rank of \a u32.
#define  LSB2W(u32)     MSB1W(u32)           //!< Least significant byte of 3rd rank of \a u32.
#define  LSB1W(u32)     MSB2W(u32)           //!< Least significant byte of 2nd rank of \a u32.
#define  LSB0W(u32)     MSB3W(u32)           //!< Least significant byte of 1st rank of \a u32.

#define  MSW(u64)       (((U32 *)&(u64))[0]) //!< Most significant word of \a u64.
#define  LSW(u64)       (((U32 *)&(u64))[1]) //!< Least significant word of \a u64.
#define  MSH0(u64)      (((U16 *)&(u64))[0]) //!< Most significant half-word of 1st rank of \a u64.
#define  MSH1(u64)      (((U16 *)&(u64))[1]) //!< Most significant half-word of 2nd rank of \a u64.
#define  MSH2(u64)      (((U16 *)&(u64))[2]) //!< Most significant half-word of 3rd rank of \a u64.
#define  MSH3(u64)      (((U16 *)&(u64))[3]) //!< Most significant half-word of 4th rank of \a u64.
#define  LSH3(u64)      MSH0(u64)            //!< Least significant half-word of 4th rank of \a u64.
#define  LSH2(u64)      MSH1(u64)            //!< Least significant half-word of 3rd rank of \a u64.
#define  LSH1(u64)      MSH2(u64)            //!< Least significant half-word of 2nd rank of \a u64.
#define  LSH0(u64)      MSH3(u64)            //!< Least significant half-word of 1st rank of \a u64.
#define  MSB0D(u64)     (((U8  *)&(u64))[0]) //!< Most significant byte of 1st rank of \a u64.
#define  MSB1D(u64)     (((U8  *)&(u64))[1]) //!< Most significant byte of 2nd rank of \a u64.
#define  MSB2D(u64)     (((U8  *)&(u64))[2]) //!< Most significant byte of 3rd rank of \a u64.
#define  MSB3D(u64)     (((U8  *)&(u64))[3]) //!< Most significant byte of 4th rank of \a u64.
#define  MSB4D(u64)     (((U8  *)&(u64))[4]) //!< Most significant byte of 5th rank of \a u64.
#define  MSB5D(u64)     (((U8  *)&(u64))[5]) //!< Most significant byte of 6th rank of \a u64.
#define  MSB6D(u64)     (((U8  *)&(u64))[6]) //!< Most significant byte of 7th rank of \a u64.
#define  MSB7D(u64)     (((U8  *)&(u64))[7]) //!< Most significant byte of 8th rank of \a u64.
#define  LSB7D(u64)     MSB0D(u64)           //!< Least significant byte of 8th rank of \a u64.
#define  LSB6D(u64)     MSB1D(u64)           //!< Least significant byte of 7th rank of \a u64.
#define  LSB5D(u64)     MSB2D(u64)           //!< Least significant byte of 6th rank of \a u64.
#define  LSB4D(u64)     MSB3D(u64)           //!< Least significant byte of 5th rank of \a u64.
#define  LSB3D(u64)     MSB4D(u64)           //!< Least significant byte of 4th rank of \a u64.
#define  LSB2D(u64)     MSB5D(u64)           //!< Least significant byte of 3rd rank of \a u64.
#define  LSB1D(u64)     MSB6D(u64)           //!< Least significant byte of 2nd rank of \a u64.
#define  LSB0D(u64)     MSB7D(u64)           //!< Least significant byte of 1st rank of \a u64.

#define  LE16(x)        Swap16(x)
#define  le16_to_cpu(x) swap16(x)
#define  cpu_to_le16(x) swap16(x)
#define  LE16_TO_CPU(x) Swap16(x)
#define  CPU_TO_LE16(x) Swap16(x)

#define  be16_to_cpu(x) (x)
#define  cpu_to_be16(x) (x)
#define  BE16_TO_CPU(x) (x)
#define  CPU_TO_BE16(x) (x)

#define  le32_to_cpu(x) swap32(x)
#define  cpu_to_le32(x) swap32(x)
#define  LE32_TO_CPU(x) Swap32(x)
#define  CPU_TO_LE32(x) Swap32(x)

#define  be32_to_cpu(x) (x)
#define  cpu_to_be32(x) (x)
#define  BE32_TO_CPU(x) (x)
#define  CPU_TO_BE32(x) (x)
//! @}


/*! \name Endianism Conversion
 *
 * The same considerations as for clz and ctz apply here but AVR32-GCC's
 * __builtin_bswap_16 and __builtin_bswap_32 do not behave like macros when
 * applied to constant expressions, so two sets of macros are defined here:
 *   - Swap16, Swap32 and Swap64 to apply to constant expressions (values known
 *     at compile time);
 *   - swap16, swap32 and swap64 to apply to non-constant expressions (values
 *     unknown at compile time).
 */
//! @{

/*! \brief Toggles the endianism of \a u16 (by swapping its bytes).
 *
 * \param u16 U16 of which to toggle the endianism.
 *
 * \return Value resulting from \a u16 with toggled endianism.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Swap16(u16) ((U16)(((U16)(u16) >> 8) |\
                           ((U16)(u16) << 8)))

/*! \brief Toggles the endianism of \a u32 (by swapping its bytes).
 *
 * \param u32 U32 of which to toggle the endianism.
 *
 * \return Value resulting from \a u32 with toggled endianism.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Swap32(u32) ((U32)(((U32)Swap16((U32)(u32) >> 16)) |\
                           ((U32)Swap16((U32)(u32)) << 16)))

/*! \brief Toggles the endianism of \a u64 (by swapping its bytes).
 *
 * \param u64 U64 of which to toggle the endianism.
 *
 * \return Value resulting from \a u64 with toggled endianism.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Swap64(u64) ((U64)(((U64)Swap32((U64)(u64) >> 32)) |\
                           ((U64)Swap32((U64)(u64)) << 32)))

/*! \brief Toggles the endianism of \a u16 (by swapping its bytes).
 *
 * \param u16 U16 of which to toggle the endianism.
 *
 * \return Value resulting from \a u16 with toggled endianism.
 *
 * \note More optimized if only used with values unknown at compile time.
 */
#if (defined __GNUC__)
#  if (!defined __OPTIMIZE_SIZE__) || !__OPTIMIZE_SIZE__
  #define swap16(u16) ((U16)__builtin_bswap_16((U16)(u16)))
#  else
  // swap_16 must be not used when GCC's -Os command option is used
  #define swap16(u16) Swap16(u16)
#  endif
#elif (defined __ICCAVR32__)
  #define swap16(u16) ((U16)__swap_bytes_in_halfwords((U16)(u16)))
#endif

/*! \brief Toggles the endianism of \a u32 (by swapping its bytes).
 *
 * \param u32 U32 of which to toggle the endianism.
 *
 * \return Value resulting from \a u32 with toggled endianism.
 *
 * \note More optimized if only used with values unknown at compile time.
 */
#if (defined __GNUC__)
  #define swap32(u32) ((U32)__builtin_bswap_32((U32)(u32)))
#elif (defined __ICCAVR32__)
  #define swap32(u32) ((U32)__swap_bytes((U32)(u32)))
#endif

/*! \brief Toggles the endianism of \a u64 (by swapping its bytes).
 *
 * \param u64 U64 of which to toggle the endianism.
 *
 * \return Value resulting from \a u64 with toggled endianism.
 *
 * \note More optimized if only used with values unknown at compile time.
 */
#define swap64(u64) ((U64)(((U64)swap32((U64)(u64) >> 32)) |\
                           ((U64)swap32((U64)(u64)) << 32)))

//! @}


/*! \name Target Abstraction
 */
//! @{

#define _GLOBEXT_           extern      //!< extern storage-class specifier.
#define _CONST_TYPE_        const       //!< const type qualifier.
#define _MEM_TYPE_SLOW_                 //!< Slow memory type.
#define _MEM_TYPE_MEDFAST_              //!< Fairly fast memory type.
#define _MEM_TYPE_FAST_                 //!< Fast memory type.

typedef U8                  Byte;       //!< 8-bit unsigned integer.

#define memcmp_ram2ram      memcmp      //!< Target-specific memcmp of RAM to RAM.
#define memcmp_code2ram     memcmp      //!< Target-specific memcmp of RAM to NVRAM.
#define memcpy_ram2ram      memcpy      //!< Target-specific memcpy from RAM to RAM.
#define memcpy_code2ram     memcpy      //!< Target-specific memcpy from NVRAM to RAM.

#define LSB0(u32)           LSB0W(u32)  //!< Least significant byte of 1st rank of \a u32.
#define LSB1(u32)           LSB1W(u32)  //!< Least significant byte of 2nd rank of \a u32.
#define LSB2(u32)           LSB2W(u32)  //!< Least significant byte of 3rd rank of \a u32.
#define LSB3(u32)           LSB3W(u32)  //!< Least significant byte of 4th rank of \a u32.
#define MSB3(u32)           MSB3W(u32)  //!< Most significant byte of 4th rank of \a u32.
#define MSB2(u32)           MSB2W(u32)  //!< Most significant byte of 3rd rank of \a u32.
#define MSB1(u32)           MSB1W(u32)  //!< Most significant byte of 2nd rank of \a u32.
#define MSB0(u32)           MSB0W(u32)  //!< Most significant byte of 1st rank of \a u32.

//! @}

/**
 * \brief Calculate \f$ \left\lceil \frac{a}{b} \right\rceil \f$ using
 * integer arithmetic.
 *
 * \param a An integer
 * \param b Another integer
 *
 * \return (\a a / \a b) rounded up to the nearest integer.
 */
#define div_ceil(a, b)	(((a) + (b) - 1) / (b))

#if (defined __GNUC__)
  #define SHORTENUM                           __attribute__ ((packed))
#elif (defined __ICCAVR32__)
  #define SHORTENUM                           /**/
#endif

#define FUNC_PTR                            void *


#if (defined __GNUC__)
  #define FLASH_DECLARE(x)  const x
#elif (defined __ICCAVR32__)
  #define FLASH_DECLARE(x) x
#endif

#if (defined __GNUC__)
  #define FLASH_EXTERN(x) extern const x
#elif (defined __ICCAVR32__)
  #define FLASH_EXTERN(x) extern x
#endif

/*Program Memory Space Storage abstraction definition*/
#if (defined __GNUC__)
  #define CMD_ID_OCTET    (0)
#elif (defined __ICCAVR32__)
  #define CMD_ID_OCTET    (3)
#endif


/* Converting of values from CPU endian to little endian. */
#define CPU_ENDIAN_TO_LE16(x) swap16(x)
#define CPU_ENDIAN_TO_LE32(x) swap32(x)
#define CPU_ENDIAN_TO_LE64(x) swap64(x)

/* Converting of values from little endian to CPU endian. */
#define LE16_TO_CPU_ENDIAN(x) swap16(x)
#define LE32_TO_CPU_ENDIAN(x) swap32(x)
#define LE64_TO_CPU_ENDIAN(x) swap64(x)

/* Converting of constants from CPU endian to little endian. */
#define CCPU_ENDIAN_TO_LE16(x) ((uint16_t)(\
  (((uint16_t)(x) & (uint16_t)0x00ffU) << 8) | \
  (((uint16_t)(x) & (uint16_t)0xff00U) >> 8)))

#define CCPU_ENDIAN_TO_LE32(x) ((uint32_t)(\
  (((uint32_t)(x) & (uint32_t)0x000000ffUL) << 24) | \
  (((uint32_t)(x) & (uint32_t)0x0000ff00UL) <<  8) | \
  (((uint32_t)(x) & (uint32_t)0x00ff0000UL) >>  8) | \
  (((uint32_t)(x) & (uint32_t)0xff000000UL) >> 24)))

#define CCPU_ENDIAN_TO_LE64(x) ((uint64_t)(\
  (((uint64_t)(x) & (uint64_t)0x00000000000000ffULL) << 56) | \
  (((uint64_t)(x) & (uint64_t)0x000000000000ff00ULL) << 40) | \
  (((uint64_t)(x) & (uint64_t)0x0000000000ff0000ULL) << 24) | \
  (((uint64_t)(x) & (uint64_t)0x00000000ff000000ULL) <<  8) | \
  (((uint64_t)(x) & (uint64_t)0x000000ff00000000ULL) >>  8) | \
  (((uint64_t)(x) & (uint64_t)0x0000ff0000000000ULL) >> 24) | \
  (((uint64_t)(x) & (uint64_t)0x00ff000000000000ULL) >> 40) | \
  (((uint64_t)(x) & (uint64_t)0xff00000000000000ULL) >> 56)))

/* Converting of constants from little endian to CPU endian. */
#define CLE16_TO_CPU_ENDIAN(x) CCPU_ENDIAN_TO_LE16(x)
#define CLE32_TO_CPU_ENDIAN(x) CCPU_ENDIAN_TO_LE32(x)
#define CLE64_TO_CPU_ENDIAN(x) CCPU_ENDIAN_TO_LE64(x)

/**
 * Address copy from the source to the Destination Memory
 */
#define ADDR_COPY_DST_SRC_16(dst, src)  memcpy((&(dst)), (&(src)), sizeof(uint16_t))
#define ADDR_COPY_DST_SRC_64(dst, src)  do {dst=src;}while(0)

#define MEMCPY_ENDIAN memcpy_be

#ifndef FREERTOS_USED
#if (EXT_BOARD != SPB104)
#ifndef BIG_ENDIAN
#define BIG_ENDIAN
#endif
#endif
#endif

/* Converts a 8 Byte array into a 64-Bit value */
static inline uint64_t convert_byte_array_to_64_bit(uint8_t *data)
{
    union
    {
        uint64_t u64;
        uint8_t u8[8];
    }long_addr;
    uint8_t index;
    for (index = 0; index <= 7; index++)
    {
        long_addr.u8[index] = *data++;
    }

    return long_addr.u64;
}

/* Converts a 64-Bit value into a 2 Byte array */
#define convert_64_bit_to_byte_array(value, data) \
    memcpy((data), (&(value)), sizeof(uint64_t))


/* Converts a 2 Byte array into a 16-Bit value */
static inline uint16_t convert_byte_array_to_16_bit(uint8_t *data)
{
    return (data[1] | ((uint16_t)data[0] << 8));
}

/* Converts a 16-Bit value into a 2 Byte array */
static inline void convert_16_bit_to_byte_array(uint16_t value, uint8_t *data)
{
    data[1] = value & 0xFF;
    data[0] = (value >> 8) & 0xFF;
}

/* Converts a 8 Byte array into a 32-Bit value */
static inline uint32_t convert_byte_array_to_32_bit(uint8_t *data)
{
    union
    {
        uint32_t u32;
        uint8_t u8[8];
    }long_addr;
    uint8_t index;
    for (index = 0; index < 4; index++)
    {
        long_addr.u8[index] = *data++;
    }
    return long_addr.u32;
}

/* Converts a 32-Bit value into a 2 Byte array */
#define convert_32_bit_to_byte_array(value, data) \
    memcpy((data), (&(value)), sizeof(uint32_t))

/* Converts a 16-Bit value into a 2 Byte array */
static inline void convert_spec_16_bit_to_byte_array(uint16_t value, uint8_t *data)
{
    data[0] = value & 0xFF;
    data[1] = (value >> 8) & 0xFF;
}

/* Converts a 16-Bit value into a 2 Byte array */
static inline void convert_16_bit_to_byte_address(uint64_t value, uint8_t *data)
{
    data[1] = (value >> 48) & 0xFF;
    data[0] = (value >> 56) & 0xFF;
}


#define PGM_READ_BYTE(x) *(x)
#define PGM_READ_WORD(x) *(x)
#define PGM_READ_BLOCK(dst, src, len) memcpy((dst), (src), (len))


#if (defined __GNUC__)
  #define nop() do { __asm__ __volatile__ ("nop"); } while (0)
#elif (defined __ICCAVR32__)
  #define nop() __no_operation()
#endif

/* Copy char s2[n] to s1[n] in any order */
static inline void *memcpy_be(void *s1, const void *s2, char n)
{
    char *su1 = (char *)s1;
    const char *su2 = (const char *)s2;
    signed char count = 0x00, count1 = 0x00;
    if ((n - 1) == 0)
    {
        *(su1 + count1) = *(su2 + count);
    }
    for (count = (n - 1), count1 = 0; count >= 0;)
    {
        *(su1 + count1++) = *(su2 + count--);
    }
    return (s1);
}


/**
 * \}
 */
#endif  // __AVR32_ABI_COMPILER__

#endif  // _COMPILER_AVR32_H_
