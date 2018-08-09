/**
 * Copyright (c) 2012 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/** @file
 *
 * @defgroup app_util Utility Functions and Definitions
 * @{
 * @ingroup app_common
 *
 * @brief Various types and definitions available to all applications.
 */

#ifndef APP_UTIL_H__
#define APP_UTIL_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "compiler_abstraction.h"
#include "nordic_common.h"
#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @cond (NODOX)
 */
/*lint -save -e27 -e10 -e19 */
#if defined (__LINT__)
#define STACK_BASE 0x1F000 // Arbitrary value.
#define STACK_TOP  0x20000 // Arbitrary value.

#elif defined ( __CC_ARM )
extern char STACK$$Base;
extern char STACK$$Length;
#define STACK_BASE    &STACK$$Base
#define STACK_TOP    ((void*)((uint32_t)STACK_BASE + (uint32_t)&STACK$$Length))

#elif defined ( __ICCARM__ )
extern char CSTACK$$Base;
extern char CSTACK$$Length;
#define STACK_BASE    &CSTACK$$Base
#define STACK_TOP    ((void*)((uint32_t)STACK_BASE + (uint32_t)&CSTACK$$Length))

#elif defined   ( __GNUC__ )
extern uint32_t __StackTop;
extern uint32_t __StackLimit;
#define STACK_BASE    &__StackLimit
#define STACK_TOP     &__StackTop
#endif

/* These macros are valid only when absolute placement is used for the application
 * image. The macros are not compile time symbols. They cannot be used as a
 * constant expression, for example, inside a static assert or linker script
 * at-placement. */
#if defined (__LINT__)
#define CODE_START (0)      // Arbitrary value.
#define CODE_END   (0x1000) // Arbitrary value.
#define CODE_SIZE  (0x1000) // Arbitrary value.

#elif defined ( __CC_ARM )
extern char Load$$LR$$LR_IROM1$$Base;
extern char Load$$LR$$LR_IROM1$$Length;
extern char Load$$LR$$LR_IROM1$$Limit;
#define CODE_START ((uint32_t)&Load$$LR$$LR_IROM1$$Base)
#define CODE_END   ((uint32_t)&Load$$LR$$LR_IROM1$$Limit)
#define CODE_SIZE  ((uint32_t)&Load$$LR$$LR_IROM1$$Length)

#elif defined ( __ICCARM__ )
extern void * __vector_table;
extern char RO_END$$Base;
#define CODE_START ((uint32_t)&__vector_table)
#define CODE_END   ((uint32_t)&RO_END$$Base)
#define CODE_SIZE  (CODE_END - CODE_START)

#elif defined(__SES_ARM)
extern uint32_t * _vectors;
extern uint32_t __FLASH_segment_used_end__;
#define CODE_START ((uint32_t)&_vectors)
#define CODE_END   ((uint32_t)&__FLASH_segment_used_end__)
#define CODE_SIZE  (CODE_END - CODE_START)

#elif defined ( __GNUC__ )
extern uint32_t __isr_vector;
extern uint32_t __etext;
#define CODE_START ((uint32_t)&__isr_vector)
#define CODE_END   ((uint32_t)&__etext)
#define CODE_SIZE  (CODE_END - CODE_START)
#endif
/** @}
 * @endcond
 */
/* lint -restore */

enum
{
    UNIT_0_625_MS = 625,        /**< Number of microseconds in 0.625 milliseconds. */
    UNIT_1_25_MS  = 1250,       /**< Number of microseconds in 1.25 milliseconds. */
    UNIT_10_MS    = 10000       /**< Number of microseconds in 10 milliseconds. */
};

/**
 * @brief Counts number of bits required for the given value
 *
 * The macro technically searches for the highest bit set.
 * For value 0 it returns 0.
 *
 * @param val Value to be processed
 *
 * @return Number of bits required for the given value
 */
//lint -emacro(572,VBITS)
#define VBITS(val) VBITS_32(val)

/**
 * @def VBITS_1
 * @brief Internal macro used by @ref VBITS */
/**
 * @def VBITS_2
 * @brief Internal macro used by @ref VBITS */
/**
 * @def VBITS_4
 * @brief Internal macro used by @ref VBITS */
/**
 * @def VBITS_8
 * @brief Internal macro used by @ref VBITS */
/**
 * @def VBITS_16
 * @brief Internal macro used by @ref VBITS */
/**
 * @def VBITS_32
 * @brief Internal macro used by @ref VBITS */
#define VBITS_1( v) ((((v) & (0x0001U <<  0)) != 0) ? 1U : 0U)
#define VBITS_2( v) ((((v) & (0x0001U <<  1)) != 0) ? VBITS_1 ((v) >>  1) +  1 : VBITS_1 (v))
#define VBITS_4( v) ((((v) & (0x0003U <<  2)) != 0) ? VBITS_2 ((v) >>  2) +  2 : VBITS_2 (v))
#define VBITS_8( v) ((((v) & (0x000fU <<  4)) != 0) ? VBITS_4 ((v) >>  4) +  4 : VBITS_4 (v))
#define VBITS_16(v) ((((v) & (0x00ffU <<  8)) != 0) ? VBITS_8 ((v) >>  8) +  8 : VBITS_8 (v))
#define VBITS_32(v) ((((v) & (0xffffU << 16)) != 0) ? VBITS_16((v) >> 16) + 16 : VBITS_16(v))


/*Segger embedded studio originally has offsetof macro which cannot be used in macros (like STATIC_ASSERT).
  This redefinition is to allow using that. */
#if defined(__SES_ARM) && defined(__GNUC__)
#undef offsetof
#define offsetof(TYPE, MEMBER) __builtin_offsetof (TYPE, MEMBER)
#endif

/**@brief Implementation specific macro for delayed macro expansion used in string concatenation
*
* @param[in]   lhs   Left hand side in concatenation
* @param[in]   rhs   Right hand side in concatenation
*/
#define STRING_CONCATENATE_IMPL(lhs, rhs) lhs ## rhs


/**@brief Macro used to concatenate string using delayed macro expansion
*
* @note This macro will delay concatenation until the expressions have been resolved
*
* @param[in]   lhs   Left hand side in concatenation
* @param[in]   rhs   Right hand side in concatenation
*/
#define STRING_CONCATENATE(lhs, rhs) STRING_CONCATENATE_IMPL(lhs, rhs)


#ifndef __LINT__

#ifdef __GNUC__
#define STATIC_ASSERT_SIMPLE(EXPR)      _Static_assert(EXPR, "unspecified message")
#define STATIC_ASSERT_MSG(EXPR, MSG)    _Static_assert(EXPR, MSG)
#endif

#ifdef __CC_ARM
#define STATIC_ASSERT_SIMPLE(EXPR)      extern char (*_do_assert(void)) [sizeof(char[1 - 2*!(EXPR)])]
#define STATIC_ASSERT_MSG(EXPR, MSG)    extern char (*_do_assert(void)) [sizeof(char[1 - 2*!(EXPR)])]
#endif

#ifdef __ICCARM__
#define STATIC_ASSERT_SIMPLE(EXPR)      static_assert(EXPR, "unspecified message")
#define STATIC_ASSERT_MSG(EXPR, MSG)    static_assert(EXPR, MSG)
#endif

#else // __LINT__

#define STATIC_ASSERT_SIMPLE(EXPR)      extern char (*_ignore(void))
#define STATIC_ASSERT_MSG(EXPR, MSG)    extern char (*_ignore(void))

#endif


#define _SELECT_ASSERT_FUNC(x, EXPR, MSG, ASSERT_MACRO, ...) ASSERT_MACRO

/**
 * @brief   Static (i.e. compile time) assert macro.
 *
 * @note The output of STATIC_ASSERT can be different across compilers.
 *
 * Usage:
 * STATIC_ASSERT(expression);
 * STATIC_ASSERT(expression, message);
 *
 * @hideinitializer
 */
//lint -save -esym(???, STATIC_ASSERT)
#define STATIC_ASSERT(...)                                                                          \
    _SELECT_ASSERT_FUNC(x, ##__VA_ARGS__,                                                           \
                        STATIC_ASSERT_MSG(__VA_ARGS__),                                             \
                        STATIC_ASSERT_SIMPLE(__VA_ARGS__))
//lint -restore


/**@brief Implementation details for NUM_VAR_ARGS */
#define NUM_VA_ARGS_IMPL(                              \
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,       \
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,  \
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,  \
    _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,  \
    _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,  \
    _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,  \
    _61, _62, N, ...) N


/**@brief Macro to get the number of arguments in a call variadic macro call
 *
 * param[in]    ...     List of arguments
 *
 * @retval  Number of variadic arguments in the argument list
 */
#define NUM_VA_ARGS(...) NUM_VA_ARGS_IMPL(__VA_ARGS__, 63, 62, 61,  \
    60, 59, 58, 57, 56, 55, 54, 53, 52, 51,                         \
    50, 49, 48, 47, 46, 45, 44, 43, 42, 41,                         \
    40, 39, 38, 37, 36, 35, 34, 33, 32, 31,                         \
    30, 29, 28, 27, 26, 25, 24, 23, 22, 21,                         \
    20, 19, 18, 17, 16, 15, 14, 13, 12, 11,                         \
    10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

/**@brief Implementation details for NUM_VAR_ARGS */
#define NUM_VA_ARGS_LESS_1_IMPL(                       \
    _ignored,                                          \
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,       \
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,  \
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,  \
    _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,  \
    _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,  \
    _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,  \
    _61, _62, N, ...) N

/**@brief Macro to get the number of arguments in a call variadic macro call.
 * First argument is not counted.
 *
 * param[in]    ...     List of arguments
 *
 * @retval  Number of variadic arguments in the argument list
 */
#define NUM_VA_ARGS_LESS_1(...) NUM_VA_ARGS_LESS_1_IMPL(__VA_ARGS__, 63, 62, 61,  \
    60, 59, 58, 57, 56, 55, 54, 53, 52, 51,                         \
    50, 49, 48, 47, 46, 45, 44, 43, 42, 41,                         \
    40, 39, 38, 37, 36, 35, 34, 33, 32, 31,                         \
    30, 29, 28, 27, 26, 25, 24, 23, 22, 21,                         \
    20, 19, 18, 17, 16, 15, 14, 13, 12, 11,                         \
    10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, ~)


/**@brief type for holding an encoded (i.e. little endian) 16 bit unsigned integer. */
typedef uint8_t uint16_le_t[2];

/**@brief Type for holding an encoded (i.e. little endian) 32 bit unsigned integer. */
typedef uint8_t uint32_le_t[4];

/**@brief Byte array type. */
typedef struct
{
    uint16_t  size;                 /**< Number of array entries. */
    uint8_t * p_data;               /**< Pointer to array entries. */
} uint8_array_t;


/**@brief Macro for performing rounded integer division (as opposed to truncating the result).
 *
 * @param[in]   A   Numerator.
 * @param[in]   B   Denominator.
 *
 * @return      Rounded (integer) result of dividing A by B.
 */
#define ROUNDED_DIV(A, B) (((A) + ((B) / 2)) / (B))


/**@brief Macro for checking if an integer is a power of two.
 *
 * @param[in]   A   Number to be tested.
 *
 * @return      true if value is power of two.
 * @return      false if value not power of two.
 */
#define IS_POWER_OF_TWO(A) ( ((A) != 0) && ((((A) - 1) & (A)) == 0) )


/**@brief Macro for converting milliseconds to ticks.
 *
 * @param[in] TIME          Number of milliseconds to convert.
 * @param[in] RESOLUTION    Unit to be converted to in [us/ticks].
 */
#define MSEC_TO_UNITS(TIME, RESOLUTION) (((TIME) * 1000) / (RESOLUTION))


/**@brief Macro for performing integer division, making sure the result is rounded up.
 *
 * @details One typical use for this is to compute the number of objects with size B is needed to
 *          hold A number of bytes.
 *
 * @param[in]   A   Numerator.
 * @param[in]   B   Denominator.
 *
 * @return      Integer result of dividing A by B, rounded up.
 */
#define CEIL_DIV(A, B)      \
    (((A) + (B) - 1) / (B))


/**@brief Macro for creating a buffer aligned to 4 bytes.
 *
 * @param[in]   NAME        Name of the buffor.
 * @param[in]   MIN_SIZE    Size of this buffor (it will be rounded up to multiples of 4 bytes).
 */
#define WORD_ALIGNED_MEM_BUFF(NAME, MIN_SIZE) static uint32_t NAME[CEIL_DIV(MIN_SIZE, sizeof(uint32_t))]


/**@brief Macro for calculating the number of words that are needed to hold a number of bytes.
 *
 * @details Adds 3 and divides by 4.
 *
 * @param[in]  n_bytes  The number of bytes.
 *
 * @return The number of words that @p n_bytes take up (rounded up).
 */
#define BYTES_TO_WORDS(n_bytes) (((n_bytes) + 3) >> 2)


/**@brief The number of bytes in a word.
 */
#define BYTES_PER_WORD (4)


/**@brief Macro for increasing a number to the nearest (larger) multiple of another number.
 *
 * @param[in]  alignment  The number to align to.
 * @param[in]  number     The number to align (increase).
 *
 * @return The aligned (increased) @p number.
 */
#define ALIGN_NUM(alignment, number) (((number) - 1) + (alignment) - (((number) - 1) % (alignment)))

/**@brief Macro for getting first of 2 parameters.
 *
 * @param[in] a1    First parameter.
 * @param[in] a2    Second parameter.
 */
#define GET_ARG_1(a1, a2) a1

/**@brief Macro for getting second of 2 parameters.
 *
 * @param[in] a1    First parameter.
 * @param[in] a2    Second parameter.
 */
#define GET_ARG_2(a1, a2) a2


/**@brief Container of macro (borrowed from Linux kernel).
 *
 * This macro returns parent structure address basing on child member address.
 *
 * @param ptr       Address of child type.
 * @param type      Type of parent structure.
 * @param member    Name of child field in parent structure.
 *
 * @return Parent structure address.
 * */
#define CONTAINER_OF(ptr, type, member)                 \
        (type *)((char *)ptr - offsetof(type, member))


/**
 * @brief Define Bit-field mask
 *
 * Macro that defined the mask with selected number of bits set, starting from
 * provided bit number.
 *
 * @param[in] bcnt Number of bits in the bit-field
 * @param[in] boff Lowest bit number
 */
#define BF_MASK(bcnt, boff) ( ((1U << (bcnt)) - 1U) << (boff) )

/**
 * @brief Get bit-field
 *
 * Macro that extracts selected bit-field from provided value
 *
 * @param[in] val  Value from witch selected bit-field would be extracted
 * @param[in] bcnt Number of bits in the bit-field
 * @param[in] boff Lowest bit number
 *
 * @return Value of the selected bits
 */
#define BF_GET(val, bcnt, boff) ( ( (val) & BF_MASK((bcnt), (boff)) ) >> (boff) )

/**
 * @brief Create bit-field value
 *
 * Value is masked and shifted to match given bit-field
 *
 * @param[in] val  Value to set on bit-field
 * @param[in] bcnt Number of bits for bit-field
 * @param[in] boff Offset of bit-field
 *
 * @return Value positioned of given bit-field.
 */
#define BF_VAL(val, bcnt, boff) ( (((uint32_t)(val)) << (boff)) & BF_MASK(bcnt, boff) )

/**
 * @name Configuration of complex bit-field
 *
 * @sa BF_CX
 * @{
 */
/** @brief Position of bit count in complex bit-field value */
#define BF_CX_BCNT_POS  0U
/** @brief Mask of bit count in complex bit-field value */
#define BF_CX_BCNT_MASK (0xffU << BF_CX_BCNT_POS)
/** @brief Position of bit position in complex bit-field value */
#define BF_CX_BOFF_POS  8U
/** @brief Mask of bit position in complex bit-field value */
#define BF_CX_BOFF_MASK (0xffU << BF_CX_BOFF_POS)
/** @} */

/**
 * @brief Define complex bit-field
 *
 * Complex bit-field would contain its position and size in one number.
 * @sa BF_CX_MASK
 * @sa BF_CX_POS
 * @sa BF_CX_GET
 *
 * @param[in] bcnt Number of bits in the bit-field
 * @param[in] boff Lowest bit number
 *
 * @return The single number that describes the bit-field completely.
 */
#define BF_CX(bcnt, boff) ( ((((uint32_t)(bcnt)) << BF_CX_BCNT_POS) & BF_CX_BCNT_MASK) | ((((uint32_t)(boff)) << BF_CX_BOFF_POS) & BF_CX_BOFF_MASK) )

/**
 * @brief Get number of bits in bit-field
 *
 * @sa BF_CX
 *
 * @param bf_cx Complex bit-field
 *
 * @return Number of bits in given bit-field
 */
#define BF_CX_BCNT(bf_cx) ( ((bf_cx) & BF_CX_BCNT_MASK) >> BF_CX_BCNT_POS )

/**
 * @brief Get lowest bit number in the field
 *
 * @sa BF_CX
 *
 * @param[in] bf_cx Complex bit-field
 *
 * @return Lowest bit number in given bit-field
 */
#define BF_CX_BOFF(bf_cx) ( ((bf_cx) & BF_CX_BOFF_MASK) >> BF_CX_BOFF_POS )

/**
 * @brief Get bit mask of the selected field
 *
 * @sa BF_CX
 *
 * @param[in] bf_cx Complex bit-field
 *
 * @return Mask of given bit-field
 */
#define BF_CX_MASK(bf_cx) BF_MASK(BF_CX_BCNT(bf_cx), BF_CX_BOFF(bf_cx))

/**
 * @brief Get bit-field
 *
 * Macro that extracts selected bit-field from provided value.
 * Bit-field is given as a complex value.
 *
 * @sa BF_CX
 * @sa BF_GET
 *
 * @param[in] val   Value from witch selected bit-field would be extracted
 * @param[in] bf_cx Complex bit-field
 *
 * @return Value of the selected bits.
 */
#define BF_CX_GET(val, bf_cx) BF_GET(val, BF_CX_BCNT(bf_cx), BF_CX_BOFF(bf_cx))

/**
 * @brief Create bit-field value
 *
 * Value is masked and shifted to match given bit-field.
 *
 * @param[in] val  Value to set on bit-field
 * @param[in] bf_cx Complex bit-field
 *
 * @return Value positioned of given bit-field.
 */
#define BF_CX_VAL(val, bf_cx) BF_VAL(val, BF_CX_BCNT(bf_cx), BF_CX_BOFF(bf_cx))

/**
 * @brief Extracting data from the brackets
 *
 * This macro get rid of brackets around the argument.
 * It can be used to pass multiple arguments in logical one argument to a macro.
 * Call it with arguments inside brackets:
 * @code
 * #define ARGUMENTS (a, b, c)
 * BRACKET_EXTRACT(ARGUMENTS)
 * @endcode
 * It would produce:
 * @code
 * a, b, c
 * @endcode
 *
 * @param a Argument with anything inside brackets
 * @return Anything that appears inside the brackets of the argument
 *
 * @note
 * The argument of the macro have to be inside brackets.
 * In other case the compilation would fail.
 */
#define BRACKET_EXTRACT(a)  BRACKET_EXTRACT_(a)
#define BRACKET_EXTRACT_(a) BRACKET_EXTRACT__ a
#define BRACKET_EXTRACT__(...) __VA_ARGS__


/**
 * @brief Check if number of parameters is more than 1
 *
 * @param ... Arguments to count
 *
 * @return 0 If argument count is <= 1
 * @return 1 If argument count is > 1
 *
 * @sa NUM_VA_ARGS
 * @sa NUM_IS_MORE_THAN_1
 */
#define NUM_VA_ARGS_IS_MORE_THAN_1(...) NUM_IS_MORE_THAN_1(NUM_VA_ARGS(__VA_ARGS__))

/**
 * @brief Check if given numeric value is bigger than 1
 *
 * This macro accepts numeric value, that may be the result of argument expansion.
 * This numeric value is then converted to 0 if it is lover than 1 or to 1 if
 * its value is higher than 1.
 * The generated result can be used to glue it into other macro mnemonic name.
 *
 * @param N Numeric value to check
 *
 * @return 0 If argument is <= 1
 * @return 1 If argument is > 1
 *
 * @note Any existing definition of a form NUM_IS_MORE_THAN_1_PROBE_[N] can
 *       broke the result of this macro
 */
#define NUM_IS_MORE_THAN_1(N) NUM_IS_MORE_THAN_1_(N)
#define NUM_IS_MORE_THAN_1_(N)  NUM_IS_MORE_THAN_1_PROBE_(NUM_IS_MORE_THAN_1_PROBE_ ## N, 1)
#define NUM_IS_MORE_THAN_1_PROBE_(...) GET_VA_ARG_1(GET_ARGS_AFTER_1(__VA_ARGS__))
#define NUM_IS_MORE_THAN_1_PROBE_0 ~, 0
#define NUM_IS_MORE_THAN_1_PROBE_1 ~, 0

/**
 * @brief Get the first argument
 *
 * @param ... Arguments to select
 *
 * @return First argument or empty if no arguments are provided
 */
#define GET_VA_ARG_1(...) GET_VA_ARG_1_(__VA_ARGS__, ) // Make sure that also for 1 argument it works
#define GET_VA_ARG_1_(a1, ...) a1

/**
 * @brief Get all the arguments but the first one
 *
 * @param ... Arguments to select
 *
 * @return All arguments after the first one or empty if less than 2 arguments are provided
 */
#define GET_ARGS_AFTER_1(...) GET_ARGS_AFTER_1_(__VA_ARGS__, ) // Make sure that also for 1 argument it works
#define GET_ARGS_AFTER_1_(a1, ...) __VA_ARGS__

/**
 * @brief Size of a field in declared structure
 *
 * Macro that returns the size of the structure field.
 * @param struct_type Variable type to get the field size from
 * @param field Field name to analyze. It can be even field inside field (field.somethingelse.and_another).
 *
 * @return Size of the field
 */
#define FIELD_SIZE(struct_type, field) sizeof(((struct struct_type*)NULL)->field)

/**
 * @brief Number of elements in field array in declared structure
 *
 * Macro that returns number of elementy in structure field.
 * @param struct_type Variable type to get the field size from
 * @param field Field name to analyze.
 *
 * @return Number of elements in field array
 *
 * @sa FIELD_SIZE
 */
#define FIELD_ARRAY_SIZE(struct_type, field) (FIELD_SIZE(struct_type, field) / FIELD_SIZE(struct_type, field[0]))

/**
 * @brief Mapping macro
 *
 * Macro that process all arguments using given macro
 *
 * @param ... Macro name to be used for argument processing followed by arguments to process.
 *            Macro should have following form: MACRO(argument)
 *
 * @return All arguments processed by given macro
 */
#define MACRO_MAP(...) MACRO_MAP_(__VA_ARGS__)
#define MACRO_MAP_(...) MACRO_MAP_N(NUM_VA_ARGS_LESS_1(__VA_ARGS__), __VA_ARGS__) // To make sure it works also for 2 arguments in total

/**
 * @brief Mapping macro, recursive version
 *
 *  Can be used in @ref MACRO_MAP macro
 */
#define MACRO_MAP_REC(...) MACRO_MAP_REC_(__VA_ARGS__)
#define MACRO_MAP_REC_(...) MACRO_MAP_REC_N(NUM_VA_ARGS_LESS_1(__VA_ARGS__), __VA_ARGS__) // To make sure it works also for 2 arguments in total
/**
 * @brief Mapping N arguments macro
 *
 * Macro similar to @ref MACRO_MAP but maps exact number of arguments.
 * If there is more arguments given, the rest would be ignored.
 *
 * @param N   Number of arguments to map
 * @param ... Macro name to be used for argument processing followed by arguments to process.
 *            Macro should have following form: MACRO(argument)
 *
 * @return Selected number of arguments processed by given macro
 */
#define MACRO_MAP_N(N, ...) MACRO_MAP_N_(N, __VA_ARGS__)
#define MACRO_MAP_N_(N, ...) CONCAT_2(MACRO_MAP_, N)(__VA_ARGS__, )

/**
 * @brief Mapping N arguments macro, recursive version
 *
 *  Can be used in @ref MACRO_MAP_N macro
 */
#define MACRO_MAP_REC_N(N, ...) MACRO_MAP_REC_N_(N, __VA_ARGS__)
#define MACRO_MAP_REC_N_(N, ...) CONCAT_2(MACRO_MAP_REC_, N)(__VA_ARGS__, )

#define MACRO_MAP_0(           ...)
#define MACRO_MAP_1( macro, a, ...) macro(a)
#define MACRO_MAP_2( macro, a, ...) macro(a) MACRO_MAP_1 (macro, __VA_ARGS__, )
#define MACRO_MAP_3( macro, a, ...) macro(a) MACRO_MAP_2 (macro, __VA_ARGS__, )
#define MACRO_MAP_4( macro, a, ...) macro(a) MACRO_MAP_3 (macro, __VA_ARGS__, )
#define MACRO_MAP_5( macro, a, ...) macro(a) MACRO_MAP_4 (macro, __VA_ARGS__, )
#define MACRO_MAP_6( macro, a, ...) macro(a) MACRO_MAP_5 (macro, __VA_ARGS__, )
#define MACRO_MAP_7( macro, a, ...) macro(a) MACRO_MAP_6 (macro, __VA_ARGS__, )
#define MACRO_MAP_8( macro, a, ...) macro(a) MACRO_MAP_7 (macro, __VA_ARGS__, )
#define MACRO_MAP_9( macro, a, ...) macro(a) MACRO_MAP_8 (macro, __VA_ARGS__, )
#define MACRO_MAP_10(macro, a, ...) macro(a) MACRO_MAP_9 (macro, __VA_ARGS__, )
#define MACRO_MAP_11(macro, a, ...) macro(a) MACRO_MAP_10(macro, __VA_ARGS__, )
#define MACRO_MAP_12(macro, a, ...) macro(a) MACRO_MAP_11(macro, __VA_ARGS__, )
#define MACRO_MAP_13(macro, a, ...) macro(a) MACRO_MAP_12(macro, __VA_ARGS__, )
#define MACRO_MAP_14(macro, a, ...) macro(a) MACRO_MAP_13(macro, __VA_ARGS__, )
#define MACRO_MAP_15(macro, a, ...) macro(a) MACRO_MAP_14(macro, __VA_ARGS__, )

#define MACRO_MAP_REC_0(           ...)
#define MACRO_MAP_REC_1( macro, a, ...) macro(a)
#define MACRO_MAP_REC_2( macro, a, ...) macro(a) MACRO_MAP_REC_1 (macro, __VA_ARGS__, )
#define MACRO_MAP_REC_3( macro, a, ...) macro(a) MACRO_MAP_REC_2 (macro, __VA_ARGS__, )
#define MACRO_MAP_REC_4( macro, a, ...) macro(a) MACRO_MAP_REC_3 (macro, __VA_ARGS__, )
#define MACRO_MAP_REC_5( macro, a, ...) macro(a) MACRO_MAP_REC_4 (macro, __VA_ARGS__, )
#define MACRO_MAP_REC_6( macro, a, ...) macro(a) MACRO_MAP_REC_5 (macro, __VA_ARGS__, )
#define MACRO_MAP_REC_7( macro, a, ...) macro(a) MACRO_MAP_REC_6 (macro, __VA_ARGS__, )
#define MACRO_MAP_REC_8( macro, a, ...) macro(a) MACRO_MAP_REC_7 (macro, __VA_ARGS__, )
#define MACRO_MAP_REC_9( macro, a, ...) macro(a) MACRO_MAP_REC_8 (macro, __VA_ARGS__, )
#define MACRO_MAP_REC_10(macro, a, ...) macro(a) MACRO_MAP_REC_9 (macro, __VA_ARGS__, )
#define MACRO_MAP_REC_11(macro, a, ...) macro(a) MACRO_MAP_REC_10(macro, __VA_ARGS__, )
#define MACRO_MAP_REC_12(macro, a, ...) macro(a) MACRO_MAP_REC_11(macro, __VA_ARGS__, )
#define MACRO_MAP_REC_13(macro, a, ...) macro(a) MACRO_MAP_REC_12(macro, __VA_ARGS__, )
#define MACRO_MAP_REC_14(macro, a, ...) macro(a) MACRO_MAP_REC_13(macro, __VA_ARGS__, )
#define MACRO_MAP_REC_15(macro, a, ...) macro(a) MACRO_MAP_REC_14(macro, __VA_ARGS__, )

/**
 * @brief Mapping macro with current index
 *
 * Basically macro similar to @ref MACRO_MAP, but the processing function would get an argument
 * and current argument index (beginning from 0).
 *
 * @param ... Macro name to be used for argument processing followed by arguments to process.
 *            Macro should have following form: MACRO(argument, index)
 * @return All arguments processed by given macro
 */
#define MACRO_MAP_FOR(...) MACRO_MAP_FOR_(__VA_ARGS__)
#define MACRO_MAP_FOR_N_LIST 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
#define MACRO_MAP_FOR_(...) MACRO_MAP_FOR_N(NUM_VA_ARGS_LESS_1(__VA_ARGS__), __VA_ARGS__)

/**
 * @brief Mapping N arguments macro with current index
 *
 * Macro is similar to @ref MACRO_MAP_FOR but maps exact number of arguments.
 * If there is more arguments given, the rest would be ignored.
 *
 * @param N   Number of arguments to map
 * @param ... Macro name to be used for argument processing followed by arguments to process.
 *            Macro should have following form: MACRO(argument, index)
 *
 * @return Selected number of arguments processed by given macro
 */
#define MACRO_MAP_FOR_N(N, ...) MACRO_MAP_FOR_N_(N, __VA_ARGS__)
#define MACRO_MAP_FOR_N_(N, ...) CONCAT_2(MACRO_MAP_FOR_, N)((MACRO_MAP_FOR_N_LIST), __VA_ARGS__, )

#define MACRO_MAP_FOR_0( n_list,           ...)
#define MACRO_MAP_FOR_1( n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)))
#define MACRO_MAP_FOR_2( n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_1 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_3( n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_2 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_4( n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_3 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_5( n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_4 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_6( n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_5 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_7( n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_6 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_8( n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_7 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_9( n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_8 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_10(n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_9 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_11(n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_10((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_12(n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_11((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_13(n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_12((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_14(n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_13((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_15(n_list, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list))) MACRO_MAP_FOR_14((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__, )


/**
 * @brief Mapping macro with current index and parameter
 *
 * Version of @ref MACRO_MAP_FOR that passes also the same parameter to all macros.
 *
 * @param param Parameter that would be passed to each macro call during mapping.
 * @param ...   Macro name to be used for argument processing followed by arguments to process.
 *              Macro should have following form: MACRO(argument, index, param)
 *
 * @return All arguments processed by given macro
 */
#define MACRO_MAP_FOR_PARAM(param, ...) MACRO_MAP_FOR_PARAM_(param, __VA_ARGS__)
#define MACRO_MAP_FOR_PARAM_(param, ...) MACRO_MAP_FOR_PARAM_N(NUM_VA_ARGS_LESS_1(__VA_ARGS__), param, __VA_ARGS__)

/**
 * @brief Mapping N arguments macro with with current index and parameter
 *
 * @param N     Number of arguments to map
 * @param param Parameter that would be passed to each macro call during mapping.
 * @param ...   Macro name to be used for argument processing followed by arguments to process.
 *              Macro should have following form: MACRO(argument, index, param)
 *
 * @return All arguments processed by given macro
 */
#define MACRO_MAP_FOR_PARAM_N(N, param, ...) MACRO_MAP_FOR_PARAM_N_(N, param, __VA_ARGS__)
#define MACRO_MAP_FOR_PARAM_N_(N, param, ...) CONCAT_2(MACRO_MAP_FOR_PARAM_, N)((MACRO_MAP_FOR_N_LIST), param, __VA_ARGS__, )


#define MACRO_MAP_FOR_PARAM_0( n_list, param, ...)
#define MACRO_MAP_FOR_PARAM_1( n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param)
#define MACRO_MAP_FOR_PARAM_2( n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_1 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_3( n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_2 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_4( n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_3 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_5( n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_4 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_6( n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_5 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_7( n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_6 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_8( n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_7 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_9( n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_8 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_10(n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_9 ((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_11(n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_10((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_12(n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_11((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_13(n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_12((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_14(n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_13((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )
#define MACRO_MAP_FOR_PARAM_15(n_list, param, macro, a, ...) macro(a, GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), param) MACRO_MAP_FOR_PARAM_14((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), param, macro, __VA_ARGS__, )


/**
 * @brief Repeating macro.
 *
 * @param count Count of repeats.
 * @param macro Macro must have the following form: MACRO(arguments).
 * @param ...   Arguments passed to the macro.
 *
 * @return All arguments processed by the given macro.
 */
#define MACRO_REPEAT(count, macro, ...)     MACRO_REPEAT_(count, macro, __VA_ARGS__)
#define MACRO_REPEAT_(count, macro, ...)    CONCAT_2(MACRO_REPEAT_, count)(macro, __VA_ARGS__)

#define MACRO_REPEAT_0(macro, ...)
#define MACRO_REPEAT_1(macro, ...)  macro(__VA_ARGS__) MACRO_REPEAT_0(macro, __VA_ARGS__)
#define MACRO_REPEAT_2(macro, ...)  macro(__VA_ARGS__) MACRO_REPEAT_1(macro, __VA_ARGS__)
#define MACRO_REPEAT_3(macro, ...)  macro(__VA_ARGS__) MACRO_REPEAT_2(macro, __VA_ARGS__)
#define MACRO_REPEAT_4(macro, ...)  macro(__VA_ARGS__) MACRO_REPEAT_3(macro, __VA_ARGS__)
#define MACRO_REPEAT_5(macro, ...)  macro(__VA_ARGS__) MACRO_REPEAT_4(macro, __VA_ARGS__)
#define MACRO_REPEAT_6(macro, ...)  macro(__VA_ARGS__) MACRO_REPEAT_5(macro, __VA_ARGS__)
#define MACRO_REPEAT_7(macro, ...)  macro(__VA_ARGS__) MACRO_REPEAT_6(macro, __VA_ARGS__)
#define MACRO_REPEAT_8(macro, ...)  macro(__VA_ARGS__) MACRO_REPEAT_7(macro, __VA_ARGS__)
#define MACRO_REPEAT_9(macro, ...)  macro(__VA_ARGS__) MACRO_REPEAT_8(macro, __VA_ARGS__)
#define MACRO_REPEAT_10(macro, ...) macro(__VA_ARGS__) MACRO_REPEAT_9(macro, __VA_ARGS__)
#define MACRO_REPEAT_11(macro, ...) macro(__VA_ARGS__) MACRO_REPEAT_10(macro, __VA_ARGS__)
#define MACRO_REPEAT_12(macro, ...) macro(__VA_ARGS__) MACRO_REPEAT_11(macro, __VA_ARGS__)
#define MACRO_REPEAT_13(macro, ...) macro(__VA_ARGS__) MACRO_REPEAT_12(macro, __VA_ARGS__)
#define MACRO_REPEAT_14(macro, ...) macro(__VA_ARGS__) MACRO_REPEAT_13(macro, __VA_ARGS__)
#define MACRO_REPEAT_15(macro, ...) macro(__VA_ARGS__) MACRO_REPEAT_14(macro, __VA_ARGS__)


/**
 * @brief Repeating macro with current index.
 *
 * Macro similar to @ref MACRO_REPEAT but the processing function gets the arguments
 * and the current argument index (beginning from 0).

 * @param count Count of repeats.
 * @param macro Macro must have the following form: MACRO(index, arguments).
 * @param ...   Arguments passed to the macro.
 *
 * @return All arguments processed by the given macro.
 */
#define MACRO_REPEAT_FOR(count, macro, ...)     MACRO_REPEAT_FOR_(count, macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_(count, macro, ...)    CONCAT_2(MACRO_REPEAT_FOR_, count)((MACRO_MAP_FOR_N_LIST), macro, __VA_ARGS__)

#define MACRO_REPEAT_FOR_0(n_list, macro, ...)
#define MACRO_REPEAT_FOR_1(n_list, macro, ...)  macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_0((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_2(n_list, macro, ...)  macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_1((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_3(n_list, macro, ...)  macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_2((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_4(n_list, macro, ...)  macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_3((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_5(n_list, macro, ...)  macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_4((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_6(n_list, macro, ...)  macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_5((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_7(n_list, macro, ...)  macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_6((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_8(n_list, macro, ...)  macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_7((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_9(n_list, macro, ...)  macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_8((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_10(n_list, macro, ...) macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_9((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_11(n_list, macro, ...) macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_10((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_12(n_list, macro, ...) macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_11((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_13(n_list, macro, ...) macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_12((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_14(n_list, macro, ...) macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_13((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)
#define MACRO_REPEAT_FOR_15(n_list, macro, ...) macro(GET_VA_ARG_1(BRACKET_EXTRACT(n_list)), __VA_ARGS__) MACRO_REPEAT_FOR_14((GET_ARGS_AFTER_1(BRACKET_EXTRACT(n_list))), macro, __VA_ARGS__)

/**@brief Adding curly brace to the macro parameter.
 *
 * Useful in array of structures initialization.
 *
 * @param p Parameter to put into the curly brace. */
#define PARAM_CBRACE(p) { p },


/**@brief Function for changing the value unit.
 *
 * @param[in]   value               Value to be rescaled.
 * @param[in]   old_unit_reversal   Reversal of the incoming unit.
 * @param[in]   new_unit_reversal   Reversal of the desired unit.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint64_t value_rescale(uint32_t value, uint32_t old_unit_reversal, uint16_t new_unit_reversal)
{
    return (uint64_t)ROUNDED_DIV((uint64_t)value * new_unit_reversal, old_unit_reversal);
}

/**@brief Function for encoding a uint16 value.
 *
 * @param[in]   value            Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint8_t uint16_encode(uint16_t value, uint8_t * p_encoded_data)
{
    p_encoded_data[0] = (uint8_t) ((value & 0x00FF) >> 0);
    p_encoded_data[1] = (uint8_t) ((value & 0xFF00) >> 8);
    return sizeof(uint16_t);
}

/**@brief Function for encoding a three-byte value.
 *
 * @param[in]   value            Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint8_t uint24_encode(uint32_t value, uint8_t * p_encoded_data)
{
    p_encoded_data[0] = (uint8_t) ((value & 0x000000FF) >> 0);
    p_encoded_data[1] = (uint8_t) ((value & 0x0000FF00) >> 8);
    p_encoded_data[2] = (uint8_t) ((value & 0x00FF0000) >> 16);
    return 3;
}

/**@brief Function for encoding a uint32 value.
 *
 * @param[in]   value            Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint8_t uint32_encode(uint32_t value, uint8_t * p_encoded_data)
{
    p_encoded_data[0] = (uint8_t) ((value & 0x000000FF) >> 0);
    p_encoded_data[1] = (uint8_t) ((value & 0x0000FF00) >> 8);
    p_encoded_data[2] = (uint8_t) ((value & 0x00FF0000) >> 16);
    p_encoded_data[3] = (uint8_t) ((value & 0xFF000000) >> 24);
    return sizeof(uint32_t);
}

/**@brief Function for encoding a uint40 value.
 *
 * @param[in]   value            Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint8_t uint40_encode(uint64_t value, uint8_t * p_encoded_data)
{
    p_encoded_data[0] = (uint8_t) ((value & 0x00000000FF) >> 0);
    p_encoded_data[1] = (uint8_t) ((value & 0x000000FF00) >> 8);
    p_encoded_data[2] = (uint8_t) ((value & 0x0000FF0000) >> 16);
    p_encoded_data[3] = (uint8_t) ((value & 0x00FF000000) >> 24);
    p_encoded_data[4] = (uint8_t) ((value & 0xFF00000000) >> 32);
    return 5;
}

/**@brief Function for encoding a uint48 value.
 *
 * @param[in]   value            Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint8_t uint48_encode(uint64_t value, uint8_t * p_encoded_data)
{
    p_encoded_data[0] = (uint8_t) ((value & 0x0000000000FF) >> 0);
    p_encoded_data[1] = (uint8_t) ((value & 0x00000000FF00) >> 8);
    p_encoded_data[2] = (uint8_t) ((value & 0x000000FF0000) >> 16);
    p_encoded_data[3] = (uint8_t) ((value & 0x0000FF000000) >> 24);
    p_encoded_data[4] = (uint8_t) ((value & 0x00FF00000000) >> 32);
    p_encoded_data[5] = (uint8_t) ((value & 0xFF0000000000) >> 40);
    return 6;
}

/**@brief Function for decoding a uint16 value.
 *
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 *
 * @return      Decoded value.
 */
static __INLINE uint16_t uint16_decode(const uint8_t * p_encoded_data)
{
        return ( (((uint16_t)((uint8_t *)p_encoded_data)[0])) |
                 (((uint16_t)((uint8_t *)p_encoded_data)[1]) << 8 ));
}

/**@brief Function for decoding a uint16 value in big-endian format.
 *
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 *
 * @return      Decoded value.
 */
static __INLINE uint16_t uint16_big_decode(const uint8_t * p_encoded_data)
{
        return ( (((uint16_t)((uint8_t *)p_encoded_data)[0]) << 8 ) |
                 (((uint16_t)((uint8_t *)p_encoded_data)[1])) );
}

/**@brief Function for decoding a three-byte value.
 *
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 *
 * @return      Decoded value (uint32_t).
 */
static __INLINE uint32_t uint24_decode(const uint8_t * p_encoded_data)
{
    return ( (((uint32_t)((uint8_t *)p_encoded_data)[0]) << 0)  |
             (((uint32_t)((uint8_t *)p_encoded_data)[1]) << 8)  |
             (((uint32_t)((uint8_t *)p_encoded_data)[2]) << 16));
}

/**@brief Function for decoding a uint32 value.
 *
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 *
 * @return      Decoded value.
 */
static __INLINE uint32_t uint32_decode(const uint8_t * p_encoded_data)
{
    return ( (((uint32_t)((uint8_t *)p_encoded_data)[0]) << 0)  |
             (((uint32_t)((uint8_t *)p_encoded_data)[1]) << 8)  |
             (((uint32_t)((uint8_t *)p_encoded_data)[2]) << 16) |
             (((uint32_t)((uint8_t *)p_encoded_data)[3]) << 24 ));
}

/**@brief Function for decoding a uint32 value in big-endian format.
 *
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 *
 * @return      Decoded value.
 */
static __INLINE uint32_t uint32_big_decode(const uint8_t * p_encoded_data)
{
    return ( (((uint32_t)((uint8_t *)p_encoded_data)[0]) << 24) |
             (((uint32_t)((uint8_t *)p_encoded_data)[1]) << 16) |
             (((uint32_t)((uint8_t *)p_encoded_data)[2]) << 8)  |
             (((uint32_t)((uint8_t *)p_encoded_data)[3]) << 0) );
}

/**
 * @brief Function for encoding an uint16 value in big-endian format.
 *
 * @param[in]   value            Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data will be written.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint8_t uint16_big_encode(uint16_t value, uint8_t * p_encoded_data)
{
    p_encoded_data[0] = (uint8_t) (value >> 8);
    p_encoded_data[1] = (uint8_t) (value & 0xFF);

    return sizeof(uint16_t);
}

/*lint -esym(526, __rev) */
/*lint -esym(628, __rev) */
/**@brief Function for encoding a uint32 value in big-endian format.
 *
 * @param[in]   value            Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data will be written.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint8_t uint32_big_encode(uint32_t value, uint8_t * p_encoded_data)
{
    *(uint32_t *)p_encoded_data = __REV(value);
    return sizeof(uint32_t);
}

/**@brief Function for decoding a uint40 value.
 *
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 *
 * @return      Decoded value. (uint64_t)
 */
static __INLINE uint64_t uint40_decode(const uint8_t * p_encoded_data)
{
    return ( (((uint64_t)((uint8_t *)p_encoded_data)[0]) << 0)  |
             (((uint64_t)((uint8_t *)p_encoded_data)[1]) << 8)  |
             (((uint64_t)((uint8_t *)p_encoded_data)[2]) << 16) |
             (((uint64_t)((uint8_t *)p_encoded_data)[3]) << 24) |
             (((uint64_t)((uint8_t *)p_encoded_data)[4]) << 32 ));
}

/**@brief Function for decoding a uint48 value.
 *
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 *
 * @return      Decoded value. (uint64_t)
 */
static __INLINE uint64_t uint48_decode(const uint8_t * p_encoded_data)
{
    return ( (((uint64_t)((uint8_t *)p_encoded_data)[0]) << 0)  |
             (((uint64_t)((uint8_t *)p_encoded_data)[1]) << 8)  |
             (((uint64_t)((uint8_t *)p_encoded_data)[2]) << 16) |
             (((uint64_t)((uint8_t *)p_encoded_data)[3]) << 24) |
             (((uint64_t)((uint8_t *)p_encoded_data)[4]) << 32) |
             (((uint64_t)((uint8_t *)p_encoded_data)[5]) << 40 ));
}

/** @brief Function for converting the input voltage (in milli volts) into percentage of 3.0 Volts.
 *
 *  @details The calculation is based on a linearized version of the battery's discharge
 *           curve. 3.0V returns 100% battery level. The limit for power failure is 2.1V and
 *           is considered to be the lower boundary.
 *
 *           The discharge curve for CR2032 is non-linear. In this model it is split into
 *           4 linear sections:
 *           - Section 1: 3.0V - 2.9V = 100% - 42% (58% drop on 100 mV)
 *           - Section 2: 2.9V - 2.74V = 42% - 18% (24% drop on 160 mV)
 *           - Section 3: 2.74V - 2.44V = 18% - 6% (12% drop on 300 mV)
 *           - Section 4: 2.44V - 2.1V = 6% - 0% (6% drop on 340 mV)
 *
 *           These numbers are by no means accurate. Temperature and
 *           load in the actual application is not accounted for!
 *
 *  @param[in] mvolts The voltage in mV
 *
 *  @return    Battery level in percent.
*/
static __INLINE uint8_t battery_level_in_percent(const uint16_t mvolts)
{
    uint8_t battery_level;

    if (mvolts >= 3000)
    {
        battery_level = 100;
    }
    else if (mvolts > 2900)
    {
        battery_level = 100 - ((3000 - mvolts) * 58) / 100;
    }
    else if (mvolts > 2740)
    {
        battery_level = 42 - ((2900 - mvolts) * 24) / 160;
    }
    else if (mvolts > 2440)
    {
        battery_level = 18 - ((2740 - mvolts) * 12) / 300;
    }
    else if (mvolts > 2100)
    {
        battery_level = 6 - ((2440 - mvolts) * 6) / 340;
    }
    else
    {
        battery_level = 0;
    }

    return battery_level;
}

/**@brief Function for checking if a pointer value is aligned to a 4 byte boundary.
 *
 * @param[in]   p   Pointer value to be checked.
 *
 * @return      TRUE if pointer is aligned to a 4 byte boundary, FALSE otherwise.
 */
static __INLINE bool is_word_aligned(void const* p)
{
    return (((uintptr_t)p & 0x03) == 0);
}

/*lint -e{568, 685} */
/**
 * @brief Function for checking if provided address is located in stack space.
 *
 * @param[in]   ptr Pointer to be checked.
 *
 * @return      true if address is in stack space, false otherwise.
 */
static __INLINE bool is_address_from_stack(void * ptr)
{
    if (((uint32_t)ptr >= (uint32_t)STACK_BASE) &&
        ((uint32_t)ptr <  (uint32_t)STACK_TOP) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

#ifdef __cplusplus
}
#endif

#endif // APP_UTIL_H__

/** @} */
