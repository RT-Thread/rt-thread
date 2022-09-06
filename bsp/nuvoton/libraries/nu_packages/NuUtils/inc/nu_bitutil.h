/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-2-7        Wayne            First version
*
******************************************************************************/
#ifndef __NU_BITUTIL_H__
#define __NU_BITUTIL_H__

#if defined(__ICCARM__)
    #include <arm_math.h>
#elif defined (__ARMCC_VERSION)
    #ifdef __has_include
        #if __has_include("cmsis_compiler.h")
            #include "cmsis_compiler.h"
        #endif
    #endif

    #if !defined(__CLZ)
        #define __CLZ     __clz
    #endif
#endif

#include <stdint.h>

#if !defined(__STATIC_INLINE)
    #define __STATIC_INLINE static inline
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ----------------------------------------------
 * Count Leading Zeros       Count Trailing Zeros
 * (MSB)00000000000000001000000000001000(LSB)
 *      ################|           |!!!
 *       Find Highest Set           Find First Set
 * ----------------------------------------------
 *
 * ----------------------------------------------
 * Count Leading Ones         Count Trailing Ones
 * (MSB)11111111111111110111111111110111(LSB)
 *      ^^^^^^^^^^^^^^^^|           |@@@
 *      Find Highest Zero           Find First Zero
 * ----------------------------------------------
*/

/* Count Leading Zeros in word - Find Highest Set
   EX: x=(MSB)00000000000000001000000000001000(LSB)
              ################|
                              Find Highest Set
   nu_clz will start zero-counting from MSB and return the number.
*/

__STATIC_INLINE int nu_clz(uint32_t x)
{
    return x ? __CLZ(x) : 32;
}

/* Count Leading Ones in word - Find Highest Zero
   EX: x=(MSB)11111111111111110111111111110111(LSB)
              ^^^^^^^^^^^^^^^^|
                              Find Highest Zero
   nu_clo will start one-counting from MSB and return the number.
*/
__STATIC_INLINE int nu_clo(uint32_t x)
{
    return nu_clz(~x);
}

/* Count Trailing Zero in word - Find First Set
   EX: x=(MSB)00000000000000001000000000001000(LSB)
                                          |!!!
                                          Find First Set
   nu_ctz will start zero-counting from LSB and return the number.
*/
__STATIC_INLINE int nu_ctz(uint32_t x)
{
    int c = 32;
    if (x)
        c = __CLZ(x & -x);
    return x ? 31 - c : c;
}

/* Count Trailing Ones in word - Find First Zero
   EX: x=(MSB)11111111111111110111111111110111(LSB)
                                          |@@@
                                          Find First Zero
   nu_cto will start one-counting from LSB and return the number.
*/
__STATIC_INLINE int nu_cto(uint32_t x)
{
    return nu_ctz(~x);
}

/* Get 16-bit from a byte-array in little-endian */
__STATIC_INLINE uint16_t nu_get16_le(const uint8_t *pos)
{
    uint16_t val;

    val = *pos ++;
    val += (*pos << 8);

    return val;
}

/* Set 16-bit to a byte-array in little-endian */
__STATIC_INLINE void nu_set16_le(uint8_t *pos, uint16_t val)
{
    *pos ++ = val & 0xFF;
    *pos = val >> 8;
}

/* Get 32-bit from a byte-array in little-endian */
__STATIC_INLINE uint32_t nu_get32_le(const uint8_t *pos)
{
    uint32_t val;

    val = *pos ++;
    val += (*pos ++ << 8);
    val += (*pos ++ << 16);
    val += (*pos ++ << 24);

    return val;
}

/* Get 24-bit from a byte-array in little-endian */
__STATIC_INLINE uint32_t nu_get24_le(const uint8_t *pos)
{
    uint32_t val;

    val = *pos ++;
    val += (*pos ++ << 8);
    val += (*pos ++ << 16);

    return val;
}

/* Set 24-bit to a byte-array in little-endian */
__STATIC_INLINE void nu_set24_le(uint8_t *pos, uint32_t val)
{
    *pos ++ = val & 0xFF;
    *pos ++ = (val >> 8) & 0xFF;
    *pos ++ = (val >> 16) & 0xFF;
}

/* Set 32-bit to a byte-array in little-endian */
__STATIC_INLINE void nu_set32_le(uint8_t *pos, uint32_t val)
{
    *pos ++ = val & 0xFF;
    *pos ++ = (val >> 8) & 0xFF;
    *pos ++ = (val >> 16) & 0xFF;
    *pos = (val >> 24) & 0xFF;
}

/* Get 16-bit from a byte-array in big-endian */
__STATIC_INLINE uint16_t nu_get16_be(const uint8_t *pos)
{
    uint16_t val;

    val = *pos ++;
    val <<= 8;
    val += *pos;

    return val;
}

/* Set 16-bit to a byte-array in big-endian */
__STATIC_INLINE void nu_set16_be(uint8_t *pos, uint16_t val)
{
    *pos ++ = val >> 8;
    *pos = (val & 0xFF);
}

/* Get 24-bit from a byte-array in big-endian */
__STATIC_INLINE uint32_t nu_get24_be(const uint8_t *pos)
{
    uint32_t val;

    val = *pos ++;
    val <<= 8;
    val += *pos ++;
    val <<= 8;
    val += *pos ++;

    return val;
}

/* Set 24-bit to a byte-array in big-endian */
__STATIC_INLINE void nu_set24_be(uint8_t *pos, uint32_t val)
{
    *pos ++ = val >> 16;
    *pos ++ = val >> 8;
    *pos ++ = (val & 0xFF);
}

/* Get 32-bit from a byte-array in big-endian */
__STATIC_INLINE uint32_t nu_get32_be(const uint8_t *pos)
{
    uint32_t val;

    val = *pos ++;
    val <<= 8;
    val += *pos ++;
    val <<= 8;
    val += *pos ++;
    val <<= 8;
    val += *pos;

    return val;
}

/* Set 32-bit to a byte-array in big-endian */
__STATIC_INLINE void nu_set32_be(uint8_t *pos, uint32_t val)
{
    *pos ++ = val >> 24;
    *pos ++ = val >> 16;
    *pos ++ = val >> 8;
    *pos ++ = (val & 0xFF);
}

#ifdef __cplusplus
}
#endif

#endif //__NU_BITUTIL_H__
