/**
 * Copyright (c) 2016 - 2018 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
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
#ifndef SYS_UTILS_H_INCLUDED
#define SYS_UTILS_H_INCLUDED

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#if (defined(__GNUC__) && !defined(__SES_ARM))
#include <strings.h>
#endif
#ifdef __MINGW32__
#define ffs __builtin_ffs
#endif

/** @file
 * This file contains definitions of useful macros and types.
 *
 * @defgroup sys_utils System Utilities API
 * @ingroup sys_15_4
 * @{
 * @brief Module to declare System Utilities API.
 * @details The System Utilities module implements multiple useful macros and inlines for the whole stack. Including
 * this header you will get access to GET_PARENT_BY_FIELD(), FIELD_SIZE() to work with complex structures,
 * ARRAY_SIZE() for arrays, mathematics macros like IMP(), LL_MIN(), LL_MAX(), CEIL(), ROUND(), Bitmap helpers
 * and many others. The variable arguments support macros are also defined here. Some SWAP routines are implemented
 * by this module as well.
 */

/**@brief Returns the pointer to the data structure
 *
 * @param[in] struct_type   name of the parent structure
 * @param[in] field_name    name of the structure field
 * @param[in] field_pointer pointer to the structure field
 *
 * @retval    Pointer to the parent structure which includes the field.
 */
#define GET_PARENT_BY_FIELD(struct_type, field_name, field_pointer)                            \
        ((struct_type*)(void*)(((uint8_t*)field_pointer) - offsetof(struct_type, field_name)))


/**@brief Returns the implication of two given expressions x and y.
 * @details The implication means:  if X==TRUE then Y==TRUE.
 *          The formula is: (X imp Y) = ((not X) or Y)
 */
#define IMP(x, y)       ( !(x) || (y) )


/**@brief Returns the minimum of two given expressions x and y.
 */
#define LL_MIN(x, y)       ( ((x) < (y)) ? (x) : (y) )


/**@brief Returns the maximum of two given expressions x and y.
 */
#define LL_MAX(x, y)       ( ((x) > (y)) ? (x) : (y) )


/**@brief Returns the quotient of a divided by b rounded upwards to the nearest
 *  integer.
 */
#define CEIL(a, b)      ((a) ? (((a) - 1U) / (b) + 1U) : 0U)


/**@brief Returns the quotient of a divided by b rounded to the nearest integer
 *  according to the standard arithmetic rules: if the fractional part of (a/b) is greater
 *  or equal to 0.5 then the result is rounded upwards; if the fractional part of (a/b) is
 *  less then 0.5 the result is rounded downwards.
 *
 * @note Use this formula only for unsigned arguments. The formula is not compatible with
 *  the signed arguments: when a and b have different signs it gives incorrect result.
 */
#define ROUND(a, b)      ( ((a) + ((b) >> 1)) / (b) )


/**@brief Declares a long bitmap named name of size bits. The size is rounded
 *  upwards to come a multiple of 8.
 */
#define BITMAP_DECLARE(name, size)          uint8_t name[CEIL(size, 8)]

/**@brief Clears all bits in given bitmap.
 */
#define BITMAP_RESET(name)                  memset((name), 0U, sizeof(name))

/**@brief Returns the value of a bit at position bit in the long bitmap named name.
 */
#define BITMAP_ISSET(name, bit)             ( 0 != ((name)[(bit) >> 3] & (1 << ((bit) & 0x7))) )

/**@brief Sets the bit at position bit in the long bitmap named name.
 */
#define BITMAP_SET(name, bit)               (name)[(bit) >> 3] |= (1 << ((bit) & 0x7))

/**@brief Clears the bit at position bit in the long bitmap named name.
 */
#define BITMAP_CLR(name, bit)               (name)[(bit) >> 3] &= ~(1 << ((bit) & 0x7))

/**@brief Assigns the given bitmap with the second bitmap.
 */
#define BITMAP_ASSIGN(nameDst, nameSrc)     memcpy((nameDst), (nameSrc), sizeof(nameDst))

/**@brief Compares two bitmaps and returns zero if they are equal.
 */
#define BITMAP_EQUAL(name1, name2)         ((sizeof(name1) == sizeof(name2)) && \
                                            (memcmp((name1), (name2), sizeof(name1)) == 0))

/**@brief Checks number. Return true if number is power of two.
 */
#define LL_IS_POWER_OF_TWO(name)       ((0 != (name)) && (0 == ((name)&(name - 1))))

/**@brief Return True if mask is fully included into a given set and False otherwise
 */
#define IS_SUBSET_OF(mask, set)     ((mask) == ((set) & (mask)))

/**@brief Creates a bit mask with single set bit on the specified position.
 */
#define BIT(pos)                    (1UL << (pos))

/**@brief Gets the given bit in the given value
 */
#define BIT_GET(val, pos)           ((((uint32_t)val) & BIT(pos)) != 0)

/**@brief Sets or clears the given bit in the given value
 */
#define BIT_SET(val, pos, bit)      { \
                                        if (bit) \
                                        { \
                                            val |= BIT(pos); \
                                        } \
                                        else \
                                        { \
                                            val &= ~BIT(pos); \
                                        } \
                                    }

/**@brief Returns two to the income power.*/
#define POWER2(n)                   (1ULL << (n))

/**@brief Creates a bit mask of specified length.
 */
#define BIT_MASK(len)               (BIT(len) - 1UL)

/**@brief Creates a bit field mask of specified length and start position.
 */
#define BIT_FIELD_MASK(start, len)  (BIT_MASK(len) << (start))

/**@brief Creates a bit field mask of specified length, start position and value.
 */
#define BIT_FIELD_VALUE(value, start, len)  (((value) & BIT_MASK(len)) << (start))

/**@brief Extracts a bit field value of specified start position and length.
 */
#define GET_BITFIELD_VALUE(bitmask, start, len)    (((bitmask) >> (start)) & BIT_MASK(len))

/**@brief Inserts a bit field value with specified start position and length.
 */
#define SET_BITFIELD_VALUE(bitmask, start, len, value) \
    (bitmask = (bitmask & ~BIT_FIELD_MASK(start, len)) | BIT_FIELD_VALUE(value, start, len))

/**@brief Extracts a mask from a BITMAP.
 * BITMAP MUST be aligned and mask length MUST be one of 2, 4, 8, 16, 32.
 */
#define BITMAP_MASK_GET(bitmap, bit, len)                                   \
    GET_BITFIELD_VALUE(((uint32_t*)(bitmap))[(bit) >> 5], (bit) & 0x1F, len)

/**@brief Sets up a mask to a BITMAP.
 * BITMAP MUST be aligned and mask length MUST be one of 2, 4, 8, 16, 32.
 */
#define BITMAP_MASK_SET(bitmap, bit, len, value)                            \
    SET_BITFIELD_VALUE(((uint32_t*)(bitmap))[(bit) >> 5], (bit) & 0x1F, len, value)

/**@brief Gets amount of the arguments.
 */
#define VA_NARGS(...) VA_NARGS_EVAL(__VA_ARGS__)
#define VA_NARGS_EVAL(...) VA_NARGS_IMPL(__VA_ARGS__, \
        /* 255, 254, */ 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, \
        239, 238, 237, 236, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224, \
        223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 208, \
        207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193, 192, \
        191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, \
        175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, \
        159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, \
        143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128, \
        127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, \
        111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100,  99,  98,  97,  96, \
        095,  94,  93,  92,  91,  90,  89,  88,  87,  86,  85,  84,  83,  82,  81,  80, \
        079,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66,  65,  64, \
        063,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53,  52,  51,  50,  49,  48, \
        047,  46,  45,  44,  43,  42,  41,  40,  39,  38,  37,  36,  35,  34,  33,  32, \
        031,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,  16, \
        015,  14,  13,  12,  11,  10,   9,   8,   7,   6,   5,   4,   3,   2,   1,   0)

/**@brief Helper macro. Gets amount of the arguments.
 */
#define VA_NARGS_IMPL(_________1,   _2,   _3,   _4,   _5,   _6,   _7, \
                        _8,   _9,  _10,  _11,  _12,  _13,  _14,  _15, \
                      __16,  _17,  _18,  _19,  _20,  _21,  _22,  _23, \
                       _24,  _25,  _26,  _27,  _28,  _29,  _30,  _31, \
                      __32,  _33,  _34,  _35,  _36,  _37,  _38,  _39, \
                       _40,  _41,  _42,  _43,  _44,  _45,  _46,  _47, \
                      __48,  _49,  _50,  _51,  _52,  _53,  _54,  _55, \
                       _56,  _57,  _58,  _59,  _60,  _61,  _62,  _63, \
                      __64,  _65,  _66,  _67,  _68,  _69,  _70,  _71, \
                       _72,  _73,  _74,  _75,  _76,  _77,  _78,  _79, \
                      __80,  _81,  _82,  _83,  _84,  _85,  _86,  _87, \
                       _88,  _89,  _90,  _91,  _92,  _93,  _94,  _95, \
                      __96,  _97,  _98,  _99, _100, _101, _102, _103, \
                      _104, _105, _106, _107, _108, _109, _110, _111, \
                      _112, _113, _114, _115, _116, _117, _118, _119, \
                      _120, _121, _122, _123, _124, _125, _126, _127, \
                      _128, _129, _130, _131, _132, _133, _134, _135, \
                      _136, _137, _138, _139, _140, _141, _142, _143, \
                      _144, _145, _146, _147, _148, _149, _150, _151, \
                      _152, _153, _154, _155, _156, _157, _158, _159, \
                      _160, _161, _162, _163, _164, _165, _166, _167, \
                      _168, _169, _170, _171, _172, _173, _174, _175, \
                      _176, _177, _178, _179, _180, _181, _182, _183, \
                      _184, _185, _186, _187, _188, _189, _190, _191, \
                      _192, _193, _194, _195, _196, _197, _198, _199, \
                      _200, _201, _202, _203, _204, _205, _206, _207, \
                      _208, _209, _210, _211, _212, _213, _214, _215, \
                      _216, _217, _218, _219, _220, _221, _222, _223, \
                      _224, _225, _226, _227, _228, _229, _230, _231, \
                      _232, _233, _234, _235, _236, _237, _238, _239, \
                      _240, _241, _242, _243, _244, _245, _246, _247, \
                      _248, _249, _250, _251, _252, _253, /* _254, _255, */\
                      N, ...) N

/**@brief Gets amount of the arguments. Execute by compiler.
 */
#define VA_NARGS_COMPILE_TIME(...) ((uint8_t)(sizeof((uint8_t[]){ __VA_ARGS__ })/sizeof(uint8_t)))

/**@brief Swaps values.
 */
#define SWAP_XOR(a, b)                                                 \
    do                                                                 \
    {                                                                  \
        (((b) ^= (a) ^= (b), (a) ^= (b)));                             \
    } while(0);

/**@brief Compare two number and take care of overflow threshold limit.
 */
#define COMPARE_WITH_THRESHOLD(a, b, threshold) \
    (((LL_MAX((a), (b)) - LL_MIN((a), (b))) < (threshold)) ? ((a) >= (b) ? 1 : 0) : ((a) > (b) ? 0 : 1))


#define ROUND_MASK(a)           ((a) - 1)
#define ROUND_UP(x, a)          (((x) + ROUND_MASK(a)) & ~ROUND_MASK(a))
#define ROUND_DOWN(x, a)        ((x) & ~ROUND_MASK(a))

/**@brief Dereferences input pointer \a y as a type \a x.
 *
 * @param[in] x type name.
 * @param[in] y pointer name.
 */
#define DEREF_VOID_PTR_AS(x, y)        (*(x *)y)

/**@brief Extends some bit value to the left extending 2's complement value
 * to 8-bit length.
 *
 * @param[out] result variable, where result is store to.
 * @param[in]  x input value.
 * @param[in]  sign_pos an integer in range 2..6 specifying bit position of sign bit.
 */
#define SIGN_EXTENSION(result, x, sign_pos)                                 \
    do                                                                      \
    {                                                                       \
        result = x & (1 << sign_pos) ?                                      \
                 x | (~((1 << (sign_pos + 1)) - 1)) :                       \
                 x & ((1 << (sign_pos + 1)) - 1);                           \
    } while (0)

/**@brief Clears some most significant bits of integer value reducing it precision.
 * Name and interface of the macro emphasizes complementary action to #SIGN_EXTENSION.
 *
 * @param[out] result variable, where result is store to.
 * @param[in]  x input value.
 * @param[in]  sign_pos an integer in range 2..6 specifying bit position of sign bit.
 */
#define SIGN_COMPRESSION(result, x, sign_pos)                               \
    do                                                                      \
    {                                                                       \
        result = x & ((1 << (sign_pos + 1)) - 1);                           \
    } while (0)

/************************* PROTOTYPES **************************************************/
/**@brief Swaps values of two bytes.
 *
 */
static inline void SWAP8(uint8_t * const x, uint8_t * const y)
{
    uint8_t _x = *x;
    *x = *y;
    *y = _x;
}

/**@brief Swaps values of two double words (DWORD).
 *
 */
static inline void SWAP32(uint32_t * const x, uint32_t * const y)
{
    uint32_t _x = *x;
    *x = *y;
    *y = _x;
}

/**@brief Swaps values of two arrays.
 *
 * @param[inout] x array pointer
 * @param[inout] y array pointer
 * @param[in] length amount of bytes to swap
 */
static inline void SWAP_ARRAYS(void * x, void * y, uint32_t length)
{
    uint8_t *_x = (uint8_t *)(void *)x;
    uint8_t *_y = (uint8_t *)(void *)y;
    if (0x0 == ((((size_t)_x) | ((size_t)_y)) & 0x3))
    {
        size_t len4 = length / sizeof(uint32_t);
        for (size_t i = 0; i < len4; i++)
        {
            SWAP32((uint32_t*)_x, (uint32_t*)_y);
            _x += sizeof(uint32_t);
            _y += sizeof(uint32_t);
        }
        length &= 0x3;
    }

    for (size_t i = 0; i < length; i++)
    {
        SWAP8(_x, _y);
        _x++;
        _y++;
    }
}


/**@brief   Find the first bit of the bitmap with the given value 
 *          (one or zero, as specified).
 *
 * @param[in]   p_bitmap        Pointer to bitmap.
 * @param[in]   bitmap_size     Number of bits in the bitmap.
 * @param[in]   bit_value       The bit value to find (one or zero).
 *
 * @retval  Bit position of the bit with specified value, or bitmap_size if no such bit 
 *          was found.
 */
static inline size_t bitmap_find_bit(uint8_t * p_bitmap, size_t bitmap_size, uint8_t bit_value)
{
#if (defined(__GNUC__) && !defined(__SES_ARM))
    if (bitmap_size <= 32)
    {
        uint32_t bitmap;
        memcpy(&bitmap, p_bitmap, sizeof(uint32_t));
        if (!bit_value)
        {
            bitmap ^= 0xFFFFFFFF;
        }
        size_t result = ffs(bitmap);
        if (result == 0 || result > bitmap_size)
        {
            return bitmap_size;
        }
        // built-in ffs implementation gives ffs(1) = 1, not 0
        return result - 1;
    }
    else
#endif
    {
        for (size_t i = 0; i < bitmap_size; i++)
        {
            if (BITMAP_ISSET(p_bitmap, i) == bit_value)
            {
                return i;
            }
        }
        return bitmap_size;
    }
}

/**@brief   Reverse the elements of array
 *
 * @param[in]   ptr        Pointer to array.
 * @param[in]   len        Length of array.
 */
static inline void array_reverse(uint8_t * ptr, size_t len)
{
    for (size_t i = 0; i < len/2; i++)
    {
        SWAP_XOR(ptr[i], ptr[len - 1 - i]);
    }
}

/**@brief Returns least significant byte of word.
 */
#define LSB_WORD(x)            ((uint8_t)(x & 0xFF))

/**@brief Returns least significant byte of halfword.
 */
#define LSB_HWORD(x)           LSB_WORD(x)

/**@brief Returns most significant byte of halfword.
 */
#define MSB_HWORD(x)           ((uint8_t)(x >> 8))

#define ALIGN_VALUE            (sizeof(size_t))

/**@brief Compiler-independent definitions.
 */
#if defined ( __CC_ARM )

    #ifndef __WEAK
        #define __WEAK              __weak
    #endif

    #ifndef PACK
        #define PACK                __attribute__ ((packed))
    #endif

    #ifndef BEGIN_PACK
        #define BEGIN_PACK
    #endif

    #ifndef END_PACK
        #define END_PACK
    #endif

#ifndef __ALIGN
    #define __ALIGN(n)          __align(n)
#endif

#elif defined ( __ICCARM__ )

    #ifndef __WEAK
        #define __WEAK              __weak
    #endif

    #ifndef PACK
        #define PACK
    #endif

    #ifndef BEGIN_PACK
        #define BEGIN_PACK          _Pragma("pack(push, 1)")
    #endif

    #ifndef END_PACK
        #define END_PACK            _Pragma("pack(pop)")
    #endif

#ifndef __ALIGN
    #define __ALIGN(n)
#endif

#elif defined   ( __GNUC__ )

    #ifndef __WEAK
        #define __WEAK              __attribute__((weak))
    #endif

    #ifndef PACK
        #define PACK                __attribute__ ((packed))
    #endif

    #ifndef BEGIN_PACK
        #define BEGIN_PACK          _Pragma("pack(push,1)")

    #endif

    #ifndef END_PACK
        #define END_PACK            _Pragma("pack(pop)")
    #endif

#ifndef __ALIGN
    #define __ALIGN(n)          __attribute__((aligned(n)))
#endif

#elif defined   ( __TASKING__ )

    #ifndef __WEAK
        #define __WEAK              __attribute__((weak))
    #endif

    #ifndef PACK
        #define PACK                __attribute__ ((packed))
    #endif

    #ifndef BEGIN_PACK
        #define BEGIN_PACK
    #endif

    #ifndef END_PACK
        #define END_PACK
    #endif

#ifndef __ALIGN
    #define __ALIGN(n)          __align(n)
#endif

#endif

/** @} */

#endif /* SYS_UTILS_H_INCLUDED */
