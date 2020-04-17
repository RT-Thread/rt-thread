/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of Nuvoton Technology Corp. nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/

#ifndef __NU_BITUTIL_H__
#define __NU_BITUTIL_H__

#if defined(__ICCARM__) && defined(TARGET_M0)
    #include <arm_math.h>
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
    return __CLZ(x);
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
    int c = __CLZ(x & -x);
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
