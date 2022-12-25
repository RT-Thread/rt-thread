/*
 * Copyright (C) 2016-2020 T-head Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     csi_instance.h
 * @brief    Some common define
 * @version  V1.0
 * @date     Feb. 2020
 ******************************************************************************/


#ifndef _CSI_INSTANCE_H
#define _CSI_INSTANCE_H

#ifdef   __cplusplus
extern "C"
{
#endif


#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <unistd.h>
#ifndef __CK860__
#include "csi_core.h"
#else
#include <stdint.h>
#endif

#define	LOW_OPTIMIZATION_ENTER
#define	LOW_OPTIMIZATION_EXIT

#define F64_MAX   ((float64_t)DBL_MAX)
#define F32_MAX   ((float32_t)FLT_MAX)

#define F64_MIN   (-DBL_MAX)
#define F32_MIN   (-FLT_MAX)

#define F64_ABSMAX   ((float64_t)DBL_MAX)
#define F32_ABSMAX   ((float32_t)FLT_MAX)

#define F64_ABSMIN   ((float64_t)0.0)
#define F32_ABSMIN   ((float32_t)0.0)

#define Q31_MAX   ((q31_t)(0x7FFFFFFFL))
#define Q15_MAX   ((q15_t)(0x7FFF))
#define Q7_MAX    ((q7_t)(0x7F))
#define Q31_MIN   ((q31_t)(0x80000000L))
#define Q15_MIN   ((q15_t)(0x8000))
#define Q7_MIN    ((q7_t)(0x80))

#define Q31_ABSMAX   ((q31_t)(0x7FFFFFFFL))
#define Q15_ABSMAX   ((q15_t)(0x7FFF))
#define Q7_ABSMAX    ((q7_t)(0x7F))
#define Q31_ABSMIN   ((q31_t)0)
#define Q15_ABSMIN   ((q15_t)0)
#define Q7_ABSMIN    ((q7_t)0)

/**
 * @brief Macros required for reciprocal calculation in Normalized LMS
 */

#define DELTA_Q31          ((q31_t)(0x100))
#define DELTA_Q15          ((q15_t)0x5)
#define INDEX_MASK         0x0000003F
#ifndef PI
#define PI               3.14159265358979f
#endif

#ifndef UNALIGNED_SUPPORT_DISABLE
    #define ALIGN4
#else
    #define ALIGN4 __attribute__((aligned(4)))
#endif   /* #ifndef UNALIGNED_SUPPORT_DISABLE */

/**
 * @brief Macros required for SINE and COSINE Fast math approximations
 */

#define FAST_MATH_TABLE_SIZE  512
#define FAST_MATH_Q31_SHIFT   (32 - 10)
#define FAST_MATH_Q15_SHIFT   (16 - 10)
#define CONTROLLER_Q31_SHIFT  (32 - 9)
#define TABLE_SPACING_Q31     0x400000
#define TABLE_SPACING_Q15     0x80

#define __STATIC_FORCEINLINE static inline __attribute__((unused))
#define CSI_NEWTON_SQRTF
#ifdef __CK860__
#define __STATIC_INLINE static inline __attribute__((unused))

#define __ALWAYS_STATIC_INLINE  __attribute__((always_inline)) static inline

#endif


/**
 * @brief Macros required for SINE and COSINE Controller functions
 */
/* 1.31(q31) Fixed value of 2/360 */
/* -1 to +1 is divided into 360 values so total spacing is (2/360) */
#define INPUT_SPACING         0xB60B61

/**
 * @brief Macros for complex numbers
 */

/* Dimension C vector space */
#define CMPLX_DIM 2

/**
 * @brief Error status returned by some functions in the library.
 */

typedef enum {
    CSI_MATH_SUCCESS        =  0,        /**< No error */
    CSI_MATH_ARGUMENT_ERROR = -1,        /**< One or more arguments are incorrect */
    CSI_MATH_LENGTH_ERROR   = -2,        /**< Length of data buffer is incorrect */
    CSI_MATH_SIZE_MISMATCH  = -3,        /**< Size of matrices is not compatible with the operation */
    CSI_MATH_NANINF         = -4,        /**< Not-a-number (NaN) or infinity is generated */
    CSI_MATH_SINGULAR       = -5,        /**< Input matrix is singular and cannot be inverted */
    CSI_MATH_TEST_FAILURE   = -6         /**< Test Failed */
} csi_status;

/**
 * @brief 8-bit fractional data type in 1.7 format.
 */
typedef int8_t q7_t;

/**
 * @brief 16-bit fractional data type in 1.15 format.
 */
typedef int16_t q15_t;

/**
 * @brief 32-bit fractional data type in 1.31 format.
 */
typedef int32_t q31_t;

/**
 * @brief 64-bit fractional data type in 1.63 format.
 */
typedef int64_t q63_t;

/**
 * @brief 32-bit floating-point type definition.
 */
typedef float float32_t;

/**
 * @brief 64-bit floating-point type definition.
 */
typedef double float64_t;

/**
  @brief definition to read/write two 16 bit values.
  @deprecated
 */
#define __SIMD32_TYPE int32_t
#define __SIMD32(addr)        (*(__SIMD32_TYPE **) & (addr))
#define __SIMD32_CONST(addr)  ( (__SIMD32_TYPE * )   (addr))
#define _SIMD32_OFFSET(addr)  (*(__SIMD32_TYPE * )   (addr))
#define __SIMD64(addr)        (*(      int64_t **) & (addr))

#define STEP(x) (x) <= 0 ? 0 : 1
#define SQ(x) ((x) * (x))

__ALWAYS_STATIC_INLINE int32_t __SSAT_31(int32_t x)
{
        int32_t res = x;
            if (x > 0x3fffffff) {
                       res = 0x3fffffff;
                           } else if (x < -1073741824) {
                                      res = -1073741824;
                                          }

                return res;
}

__ALWAYS_STATIC_INLINE int32_t __SSAT_16(int32_t x)
{
        int32_t res = x;
            if (x > 0x7fff) {
                       res = 0x7fff;
                           } else if (x < -32768) {
                                      res = -32768;
                                          }

                return res;
}

__ALWAYS_STATIC_INLINE int32_t __SSAT_8(int32_t x)
{
        int32_t res = x;
            if (x > 0x7f) {
                       res = 0x7f;
                           } else if (x < -128) {
                                      res = -128;
                                          }

                return res;
}

/**
  @brief         Read 2 Q15 from Q15 pointer.
  @param[in]     pQ15      points to input value
  @return        Q31 value
 */
__STATIC_FORCEINLINE q31_t read_q15x2 (
    q15_t * pQ15)
{
    q31_t val;
    memcpy (&val, pQ15, 4);
    return (val);
}

/**
  @brief         Read 2 Q15 from Q15 pointer and increment pointer afterwards.
  @param[in]     pQ15      points to input value
  @return        Q31 value
 */
__STATIC_FORCEINLINE q31_t read_q15x2_ia (
    q15_t ** pQ15)
{
    q31_t val;
    memcpy (&val, *pQ15, 4);
    *pQ15 += 2;
    return (val);
}

/**
  @brief         Read 2 Q15 from Q15 pointer and decrement pointer afterwards.
  @param[in]     pQ15      points to input value
  @return        Q31 value
 */
__STATIC_FORCEINLINE q31_t read_q15x2_da (
    q15_t ** pQ15)
{
    q31_t val;
    memcpy (&val, *pQ15, 4);
    *pQ15 -= 2;
    return (val);
}

/**
  @brief         Write 2 Q15 to Q15 pointer and increment pointer afterwards.
  @param[in]     pQ15      points to input value
  @param[in]     value     Q31 value
  @return        none
 */
__STATIC_FORCEINLINE void write_q15x2_ia (
    q15_t ** pQ15,
    q31_t    value)
{
    q31_t val = value;
    memcpy (*pQ15, &val, 4);
    *pQ15 += 2;
}

/**
  @brief         Write 2 Q15 to Q15 pointer.
  @param[in]     pQ15      points to input value
  @param[in]     value     Q31 value
  @return        none
 */
__STATIC_FORCEINLINE void write_q15x2 (
    q15_t * pQ15,
    q31_t   value)
{
    q31_t val = value;
    memcpy (pQ15, &val, 4);
}


/**
  @brief         Read 4 Q7 from Q7 pointer and increment pointer afterwards.
  @param[in]     pQ7       points to input value
  @return        Q31 value
 */
__STATIC_FORCEINLINE q31_t read_q7x4_ia (
    q7_t ** pQ7)
{
    q31_t val;
    memcpy (&val, *pQ7, 4);
    *pQ7 += 4;
    return (val);
}

/**
  @brief         Read 4 Q7 from Q7 pointer and decrement pointer afterwards.
  @param[in]     pQ7       points to input value
  @return        Q31 value
 */
__STATIC_FORCEINLINE q31_t read_q7x4_da (
    q7_t ** pQ7)
{
    q31_t val;
    memcpy (&val, *pQ7, 4);
    *pQ7 -= 4;
    return (val);
}

/**
  @brief         Write 4 Q7 to Q7 pointer and increment pointer afterwards.
  @param[in]     pQ7       points to input value
  @param[in]     value     Q31 value
  @return        none
 */
__STATIC_FORCEINLINE void write_q7x4_ia (
    q7_t ** pQ7,
    q31_t   value)
{
    q31_t val = value;
    memcpy (*pQ7, &val, 4);
    *pQ7 += 4;
}

#ifdef __CK860__
__STATIC_FORCEINLINE uint8_t __CLZ(uint32_t data)
{
    if (data == 0U) {
        return 32U;
    }

    uint32_t count = 0U;
    uint32_t mask = 0x80000000U;

    while ((data & mask) == 0U) {
        count += 1U;
        mask = mask >> 1U;
    }

    return count;
}

__STATIC_FORCEINLINE int32_t __SSAT(int32_t val, uint32_t sat)
{
    if ((sat >= 1U) && (sat <= 32U)) {
        const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
        const int32_t min = -1 - max ;

        if (val > max) {
            return max;

        } else if (val < min) {
            return min;
        }
    }

    return val;
}

__STATIC_FORCEINLINE uint32_t __USAT(int32_t val, uint32_t sat)
{
    if (sat <= 31U) {
        const uint32_t max = ((1U << sat) - 1U);

        if (val > (int32_t)max) {
            return max;

        } else if (val < 0) {
            return 0U;
        }
    }

    return (uint32_t)val;
}
#endif
/**
 * @brief definition to pack two 16 bit values.
 */
#define __PKHBT(ARG1, ARG2, ARG3) ( (((int32_t)(ARG1) <<    0) & (int32_t)0x0000FFFF) | \
                                      (((int32_t)(ARG2) << ARG3) & (int32_t)0xFFFF0000)  )
#define __PKHTB(ARG1, ARG2, ARG3) ( (((int32_t)(ARG1) <<    0) & (int32_t)0xFFFF0000) | \
                                      (((int32_t)(ARG2) >> ARG3) & (int32_t)0x0000FFFF)  )


/**
* @brief definition to pack four 8 bit values.
*/
#define __PACKq7(v0,v1,v2,v3) ( (((int32_t)(v0) <<  0) & (int32_t)0x000000FF) | \
									  (((int32_t)(v1) <<  8) & (int32_t)0x0000FF00) | \
									  (((int32_t)(v2) << 16) & (int32_t)0x00FF0000) | \
									  (((int32_t)(v3) << 24) & (int32_t)0xFF000000)  )

/**
 * @brief Clips Q63 to Q31 values.
 */
__STATIC_FORCEINLINE q31_t clip_q63_to_q31(
    q63_t x)
{
    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ?
           ((0x7FFFFFFF ^ ((q31_t) (x >> 63)))) : (q31_t) x;
}

/**
 * @brief Clips Q63 to Q15 values.
 */
__STATIC_FORCEINLINE q15_t clip_q63_to_q15(
    q63_t x)
{
    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ?
           ((0x7FFF ^ ((q15_t) (x >> 63)))) : (q15_t) (x >> 15);
}

/**
 * @brief Clips Q31 to Q7 values.
 */
__STATIC_FORCEINLINE q7_t clip_q31_to_q7(
    q31_t x)
{
    return ((q31_t) (x >> 24) != ((q31_t) x >> 23)) ?
           ((0x7F ^ ((q7_t) (x >> 31)))) : (q7_t) x;
}

/**
 * @brief Clips Q31 to Q15 values.
 */
__STATIC_FORCEINLINE q15_t clip_q31_to_q15(
    q31_t x)
{
    return ((q31_t) (x >> 16) != ((q31_t) x >> 15)) ?
           ((0x7FFF ^ ((q15_t) (x >> 31)))) : (q15_t) x;
}

/**
 * @brief Multiplies 32 X 64 and returns 32 bit result in 2.30 format.
 */
__STATIC_FORCEINLINE q63_t mult32x64(
    q63_t x,
    q31_t y)
{
    return ((((q63_t) (x & 0x00000000FFFFFFFF) * y) >> 32) +
            (((q63_t) (x >> 32)                * y)      )  );
}

/**
 * @brief Integer exponentiation
 * @param[in]    x           value
 * @param[in]    nb          integer exponent >= 1
 * @return x^nb
 *
 */
__STATIC_INLINE float32_t csi_exponent_f32(float32_t x, int32_t nb)
{
    float32_t r = x;
    nb --;

    while(nb > 0) {
        r = r * x;
        nb--;
    }

    return(r);
}

/**
 * @brief  64-bit to 32-bit unsigned normalization
 * @param[in]  in           is input unsigned long long value
 * @param[out] normalized   is the 32-bit normalized value
 * @param[out] norm         is norm scale
 */
__STATIC_INLINE  void csi_norm_64_to_32u(uint64_t in, int32_t * normalized, int32_t *norm)
{
    int32_t     n1;
    int32_t     hi = (int32_t) (in >> 32);
    int32_t     lo = (int32_t) ((in << 32) >> 32);
    n1 = __CLZ(hi) - 32;

    if (!n1) {
        /*
         * input fits in 32-bit
         */
        n1 = __CLZ(lo);

        if (!n1) {
            /*
             * MSB set, need to scale down by 1
             */
            *norm = -1;
            *normalized = (((uint32_t) lo) >> 1);

        } else {
            if (n1 == 32) {
                /*
                 * input is zero
                 */
                *norm = 0;
                *normalized = 0;

            } else {
                /*
                 * 32-bit normalization
                 */
                *norm = n1 - 1;
                *normalized = lo << *norm;
            }
        }

    } else {
        /*
         * input fits in 64-bit
         */
        n1 = 1 - n1;
        *norm = -n1;
        /*
         * 64 bit normalization
         */
        *normalized = (((uint32_t) lo) >> n1) | (hi << (32 - n1));
    }
}

__STATIC_INLINE q31_t csi_div_q63_to_q31(q63_t num, q31_t den)
{
    q31_t   result;
    uint64_t   absNum;
    int32_t   normalized;
    int32_t   norm;
    /*
     * if sum fits in 32bits
     * avoid costly 64-bit division
     */
    absNum = num > 0 ? num : -num;
    csi_norm_64_to_32u(absNum, &normalized, &norm);

    if (norm > 0)
        /*
         * 32-bit division
         */
        result = (q31_t) num / den;

    else
        /*
         * 64-bit division
         */
        result = (q31_t) (num / den);

    return result;
}

/*
 * @brief C custom defined intrinsic functions
 */
#ifdef __CK860__
/*
 * @brief C custom defined QADD8
 */
__STATIC_FORCEINLINE uint32_t __QADD8(
    uint32_t x,
    uint32_t y)
{
    q31_t r, s, t, u;
    r = __SSAT(((((q31_t)x << 24) >> 24) + (((q31_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((q31_t)x << 16) >> 24) + (((q31_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((q31_t)x <<  8) >> 24) + (((q31_t)y <<    8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((q31_t)x    ) >> 24) + (((q31_t)y      ) >> 24)), 8) & (int32_t)0x000000FF;
    return ((uint32_t)((u << 24) | (t << 16) | (s <<    8) | (r      )));
}


/*
 * @brief C custom defined QSUB8
 */
__STATIC_FORCEINLINE uint32_t __QSUB8(
    uint32_t x,
    uint32_t y)
{
    q31_t r, s, t, u;
    r = __SSAT(((((q31_t)x << 24) >> 24) - (((q31_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((q31_t)x << 16) >> 24) - (((q31_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((q31_t)x <<  8) >> 24) - (((q31_t)y <<    8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((q31_t)x    ) >> 24) - (((q31_t)y      ) >> 24)), 8) & (int32_t)0x000000FF;
    return ((uint32_t)((u << 24) | (t << 16) | (s <<    8) | (r      )));
}


/*
 * @brief C custom defined QADD16
 */
__STATIC_FORCEINLINE uint32_t __QADD16(
    uint32_t x,
    uint32_t y)
{
    /*  q31_t r,       s;  without initialisation 'csi_offset_q15 test' fails  but 'intrinsic' tests pass! for armCC */
    q31_t r = 0, s = 0;
    r = __SSAT(((((q31_t)x << 16) >> 16) + (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31_t)x    ) >> 16) + (((q31_t)y      ) >> 16)), 16) & (int32_t)0x0000FFFF;
    return ((uint32_t)((s << 16) | (r    )));
}


/*
 * @brief C custom defined SHADD16
 */
__STATIC_FORCEINLINE uint32_t __SHADD16(
    uint32_t x,
    uint32_t y)
{
    q31_t r, s;
    r = (((((q31_t)x << 16) >> 16) + (((q31_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31_t)x        ) >> 16) + (((q31_t)y      ) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    return ((uint32_t)((s << 16) | (r    )));
}


/*
 * @brief C custom defined QSUB16
 */
__STATIC_FORCEINLINE uint32_t __QSUB16(
    uint32_t x,
    uint32_t y)
{
    q31_t r, s;
    r = __SSAT(((((q31_t)x << 16) >> 16) - (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31_t)x    ) >> 16) - (((q31_t)y      ) >> 16)), 16) & (int32_t)0x0000FFFF;
    return ((uint32_t)((s << 16) | (r    )));
}


/*
 * @brief C custom defined SHSUB16
 */
__STATIC_FORCEINLINE uint32_t __SHSUB16(
    uint32_t x,
    uint32_t y)
{
    q31_t r, s;
    r = (((((q31_t)x << 16) >> 16) - (((q31_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31_t)x        ) >> 16) - (((q31_t)y      ) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    return ((uint32_t)((s << 16) | (r    )));
}


/*
 * @brief C custom defined QASX
 */
__STATIC_FORCEINLINE uint32_t __QASX(
    uint32_t x,
    uint32_t y)
{
    q31_t r, s;
    r = __SSAT(((((q31_t)x << 16) >> 16) - (((q31_t)y    ) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31_t)x    ) >> 16) + (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    return ((uint32_t)((s << 16) | (r    )));
}


/*
 * @brief C custom defined SHASX
 */
__STATIC_FORCEINLINE uint32_t __SHASX(
    uint32_t x,
    uint32_t y)
{
    q31_t r, s;
    r = (((((q31_t)x << 16) >> 16) - (((q31_t)y    ) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31_t)x        ) >> 16) + (((q31_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    return ((uint32_t)((s << 16) | (r    )));
}


/*
 * @brief C custom defined QSAX
 */
__STATIC_FORCEINLINE uint32_t __QSAX(
    uint32_t x,
    uint32_t y)
{
    q31_t r, s;
    r = __SSAT(((((q31_t)x << 16) >> 16) + (((q31_t)y    ) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31_t)x    ) >> 16) - (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    return ((uint32_t)((s << 16) | (r    )));
}


/*
 * @brief C custom defined SHSAX
 */
__STATIC_FORCEINLINE uint32_t __SHSAX(
    uint32_t x,
    uint32_t y)
{
    q31_t r, s;
    r = (((((q31_t)x << 16) >> 16) + (((q31_t)y    ) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31_t)x        ) >> 16) - (((q31_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    return ((uint32_t)((s << 16) | (r    )));
}


/*
 * @brief C custom defined SMUSDX
 */
__STATIC_FORCEINLINE uint32_t __SMUSDX(
    uint32_t x,
    uint32_t y)
{
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y    ) >> 16)) -
                       ((((q31_t)x    ) >> 16) * (((q31_t)y << 16) >> 16))   ));
}

/*
 * @brief C custom defined SMUADX
 */
__STATIC_FORCEINLINE uint32_t __SMUADX(
    uint32_t x,
    uint32_t y)
{
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y    ) >> 16)) +
                       ((((q31_t)x    ) >> 16) * (((q31_t)y << 16) >> 16))   ));
}


/*
 * @brief C custom defined QADD
 */
__STATIC_FORCEINLINE int32_t __QADD(
    int32_t x,
    int32_t y)
{
    return ((int32_t)(clip_q63_to_q31((q63_t)x + (q31_t)y)));
}


/*
 * @brief C custom defined QSUB
 */
__STATIC_FORCEINLINE int32_t __QSUB(
    int32_t x,
    int32_t y)
{
    return ((int32_t)(clip_q63_to_q31((q63_t)x - (q31_t)y)));
}


/*
 * @brief C custom defined SMLAD
 */
__STATIC_FORCEINLINE uint32_t __SMLAD(
    uint32_t x,
    uint32_t y,
    uint32_t sum)
{
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ((((q31_t)x    ) >> 16) * (((q31_t)y      ) >> 16)) +
                       ( ((q31_t)sum      )                                  )   ));
}


/*
 * @brief C custom defined SMLADX
 */
__STATIC_FORCEINLINE uint32_t __SMLADX(
    uint32_t x,
    uint32_t y,
    uint32_t sum)
{
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y    ) >> 16)) +
                       ((((q31_t)x    ) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ( ((q31_t)sum      )                                  )   ));
}


/*
 * @brief C custom defined SMLSDX
 */
__STATIC_FORCEINLINE uint32_t __SMLSDX(
    uint32_t x,
    uint32_t y,
    uint32_t sum)
{
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y    ) >> 16)) -
                       ((((q31_t)x    ) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ( ((q31_t)sum      )                                  )   ));
}


/*
 * @brief C custom defined SMLALD
 */
__STATIC_FORCEINLINE uint64_t __SMLALD(
    uint32_t x,
    uint32_t y,
    uint64_t sum)
{
    /*  return (sum + ((q15_t) (x >> 16) * (q15_t) (y >> 16)) + ((q15_t) x * (q15_t) y)); */
    return ((uint64_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ((((q31_t)x    ) >> 16) * (((q31_t)y      ) >> 16)) +
                       ( ((q63_t)sum      )                                  )   ));
}


/*
 * @brief C custom defined SMLALDX
 */
__STATIC_FORCEINLINE uint64_t __SMLALDX(
    uint32_t x,
    uint32_t y,
    uint64_t sum)
{
    /*  return (sum + ((q15_t) (x >> 16) * (q15_t) y)) + ((q15_t) x * (q15_t) (y >> 16)); */
    return ((uint64_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y    ) >> 16)) +
                       ((((q31_t)x    ) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ( ((q63_t)sum      )                                  )   ));
}


/*
 * @brief C custom defined SMUAD
 */
__STATIC_FORCEINLINE uint32_t __SMUAD(
    uint32_t x,
    uint32_t y)
{
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ((((q31_t)x    ) >> 16) * (((q31_t)y      ) >> 16))   ));
}


/*
 * @brief C custom defined SMUSD
 */
__STATIC_FORCEINLINE uint32_t __SMUSD(
    uint32_t x,
    uint32_t y)
{
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y << 16) >> 16)) -
                       ((((q31_t)x    ) >> 16) * (((q31_t)y      ) >> 16))   ));
}


/*
 * @brief C custom defined SXTB16
 */
__STATIC_FORCEINLINE uint32_t __SXTB16(
    uint32_t x)
{
    return ((uint32_t)(((((q31_t)x << 24) >> 24) & (q31_t)0x0000FFFF) |
                       ((((q31_t)x <<  8) >>    8) & (q31_t)0xFFFF0000)  ));
}
/*
 * @brief C custom defined SMMLA
 */
__STATIC_FORCEINLINE int32_t __SMMLA(
    int32_t x,
    int32_t y,
    int32_t sum)
{
    return (sum + (int32_t) (((int64_t) x * y) >> 32));
}
#endif
/**
 * @brief Instance structure for the Q7 FIR filter.
 */
typedef struct {
    uint16_t numTaps;        /**< number of filter coefficients in the filter. */
    q7_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const q7_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
} csi_fir_instance_q7;

/**
 * @brief Instance structure for the Q15 FIR filter.
 */
typedef struct {
    uint16_t numTaps;         /**< number of filter coefficients in the filter. */
    q15_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const q15_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
} csi_fir_instance_q15;

/**
 * @brief Instance structure for the Q31 FIR filter.
 */
typedef struct {
    uint16_t numTaps;         /**< number of filter coefficients in the filter. */
    q31_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const q31_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps. */
} csi_fir_instance_q31;

/**
 * @brief Instance structure for the floating-point FIR filter.
 */
typedef struct {
    uint16_t numTaps;     /**< number of filter coefficients in the filter. */
    float32_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const float32_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
} csi_fir_instance_f32;

/**
 * @brief Instance structure for the Q15 Biquad cascade filter.
 */
typedef struct {
    int8_t numStages;        /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    q15_t *pState;           /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    const q15_t *pCoeffs;          /**< Points to the array of coefficients.  The array is of length 5*numStages. */
    int8_t postShift;        /**< Additional shift, in bits, applied to each output sample. */
} csi_biquad_casd_df1_inst_q15;

/**
 * @brief Instance structure for the Q31 Biquad cascade filter.
 */
typedef struct {
    uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    q31_t *pState;           /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    const q31_t *pCoeffs;          /**< Points to the array of coefficients.  The array is of length 5*numStages. */
    uint8_t postShift;       /**< Additional shift, in bits, applied to each output sample. */
} csi_biquad_casd_df1_inst_q31;

/**
 * @brief Instance structure for the floating-point Biquad cascade filter.
 */
typedef struct {
    uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    float32_t *pState;       /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    const float32_t *pCoeffs;      /**< Points to the array of coefficients.  The array is of length 5*numStages. */
} csi_biquad_casd_df1_inst_f32;

/**
 * @brief Instance structure for the floating-point matrix structure.
 */
typedef struct {
    uint16_t numRows;     /**< number of rows of the matrix.     */
    uint16_t numCols;     /**< number of columns of the matrix.  */
    float32_t *pData;     /**< points to the data of the matrix. */
} csi_matrix_instance_f32;


/**
 * @brief Instance structure for the floating-point matrix structure.
 */
typedef struct {
    uint16_t numRows;     /**< number of rows of the matrix.     */
    uint16_t numCols;     /**< number of columns of the matrix.  */
    float64_t *pData;     /**< points to the data of the matrix. */
} csi_matrix_instance_f64;

/**
 * @brief Instance structure for the Q15 matrix structure.
 */
typedef struct {
    uint16_t numRows;     /**< number of rows of the matrix.     */
    uint16_t numCols;     /**< number of columns of the matrix.  */
    q15_t *pData;         /**< points to the data of the matrix. */
} csi_matrix_instance_q15;

/**
 * @brief Instance structure for the Q31 matrix structure.
 */
typedef struct {
    uint16_t numRows;     /**< number of rows of the matrix.     */
    uint16_t numCols;     /**< number of columns of the matrix.  */
    q31_t *pData;         /**< points to the data of the matrix. */
} csi_matrix_instance_q31;

/**
 * @brief Instance structure for the Q15 PID Control.
 */
typedef struct {
    q15_t A0;           /**< The derived gain, A0 = Kp + Ki + Kd . */
    q15_t A1;
    q15_t A2;
    q15_t state[3];     /**< The state array of length 3. */
    q15_t Kp;           /**< The proportional gain. */
    q15_t Ki;           /**< The integral gain. */
    q15_t Kd;           /**< The derivative gain. */
} csi_pid_instance_q15;

/**
 * @brief Instance structure for the Q31 PID Control.
 */
typedef struct {
    q31_t A0;            /**< The derived gain, A0 = Kp + Ki + Kd . */
    q31_t A1;            /**< The derived gain, A1 = -Kp - 2Kd. */
    q31_t A2;            /**< The derived gain, A2 = Kd . */
    q31_t state[3];      /**< The state array of length 3. */
    q31_t Kp;            /**< The proportional gain. */
    q31_t Ki;            /**< The integral gain. */
    q31_t Kd;            /**< The derivative gain. */
} csi_pid_instance_q31;

/**
 * @brief Instance structure for the floating-point PID Control.
 */
typedef struct {
    float32_t A0;          /**< The derived gain, A0 = Kp + Ki + Kd . */
    float32_t A1;          /**< The derived gain, A1 = -Kp - 2Kd. */
    float32_t A2;          /**< The derived gain, A2 = Kd . */
    float32_t state[3];    /**< The state array of length 3. */
    float32_t Kp;          /**< The proportional gain. */
    float32_t Ki;          /**< The integral gain. */
    float32_t Kd;          /**< The derivative gain. */
} csi_pid_instance_f32;

/**
 * @brief Instance structure for the floating-point Linear Interpolate function.
 */
typedef struct {
    uint32_t nValues;           /**< nValues */
    float32_t x1;               /**< x1 */
    float32_t xSpacing;         /**< xSpacing */
    float32_t *pYData;          /**< pointer to the table of Y values */
} csi_linear_interp_instance_f32;

/**
 * @brief Instance structure for the floating-point bilinear interpolation function.
 */
typedef struct {
    uint16_t numRows;   /**< number of rows in the data table. */
    uint16_t numCols;   /**< number of columns in the data table. */
    float32_t *pData;   /**< points to the data table. */
} csi_bilinear_interp_instance_f32;

/**
* @brief Instance structure for the Q31 bilinear interpolation function.
*/
typedef struct {
    uint16_t numRows;   /**< number of rows in the data table. */
    uint16_t numCols;   /**< number of columns in the data table. */
    q31_t *pData;       /**< points to the data table. */
} csi_bilinear_interp_instance_q31;

/**
* @brief Instance structure for the Q15 bilinear interpolation function.
*/
typedef struct {
    uint16_t numRows;   /**< number of rows in the data table. */
    uint16_t numCols;   /**< number of columns in the data table. */
    q15_t *pData;       /**< points to the data table. */
} csi_bilinear_interp_instance_q15;

/**
* @brief Instance structure for the Q15 bilinear interpolation function.
*/
typedef struct {
    uint16_t numRows;   /**< number of rows in the data table. */
    uint16_t numCols;   /**< number of columns in the data table. */
    q7_t *pData;        /**< points to the data table. */
} csi_bilinear_interp_instance_q7;

/**
 * @brief Instance structure for the Q15 CFFT/CIFFT function.
 */
typedef struct {
    uint16_t fftLen;                 /**< length of the FFT. */
    uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const q15_t *pTwiddle;                 /**< points to the Sin twiddle factor table. */
    const uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
} csi_cfft_radix2_instance_q15;

/**
 * @brief Instance structure for the Q15 CFFT/CIFFT function.
 */
typedef struct {
    uint16_t fftLen;                 /**< length of the FFT. */
    uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const q15_t *pTwiddle;                 /**< points to the twiddle factor table. */
    const uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
} csi_cfft_radix4_instance_q15;

/**
 * @brief Instance structure for the Radix-2 Q31 CFFT/CIFFT function.
 */
typedef struct {
    uint16_t fftLen;                 /**< length of the FFT. */
    uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const q31_t *pTwiddle;                 /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
} csi_cfft_radix2_instance_q31;


/**
 * @brief Instance structure for the Q31 CFFT/CIFFT function.
 */
typedef struct {
    uint16_t fftLen;                 /**< length of the FFT. */
    uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const q31_t *pTwiddle;                 /**< points to the twiddle factor table. */
    const uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
} csi_cfft_radix4_instance_q31;

/**
 * @brief Instance structure for the floating-point CFFT/CIFFT function.
 */
typedef struct {
    uint16_t fftLen;                   /**< length of the FFT. */
    uint8_t ifftFlag;                  /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;            /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const float32_t *pTwiddle;               /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;            /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;         /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;             /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
    float32_t onebyfftLen;             /**< value of 1/fftLen. */
} csi_cfft_radix2_instance_f32;

/**
 * @brief Instance structure for the floating-point CFFT/CIFFT function.
 */
typedef struct {
    uint16_t fftLen;                   /**< length of the FFT. */
    uint8_t ifftFlag;                  /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;            /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const float32_t *pTwiddle;               /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;            /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;         /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;             /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
    float32_t onebyfftLen;             /**< value of 1/fftLen. */
} csi_cfft_radix4_instance_f32;

/**
 * @brief Instance structure for the fixed-point CFFT/CIFFT function.
 */
typedef struct {
    uint16_t fftLen;                   /**< length of the FFT. */
    const q15_t *pTwiddle;             /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
    uint16_t bitRevLength;             /**< bit reversal table length. */
} csi_cfft_instance_q15;

/**
 * @brief Instance structure for the fixed-point CFFT/CIFFT function.
 */
typedef struct {
    uint16_t fftLen;                   /**< length of the FFT. */
    const q31_t *pTwiddle;             /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
    uint16_t bitRevLength;             /**< bit reversal table length. */
} csi_cfft_instance_q31;


/**
 * @brief Instance structure for the floating-point CFFT/CIFFT function.
 */
typedef struct {
    uint16_t fftLen;                   /**< length of the FFT. */
    const float32_t *pTwiddle;         /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
    uint16_t bitRevLength;             /**< bit reversal table length. */
} csi_cfft_instance_f32;

  typedef struct
  {
    uint32_t fftLenReal;                        /**< length of the real FFT. */
    uint8_t ifftFlagR;                          /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
    uint8_t bitReverseFlagR;                    /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
    q31_t *pTwiddleAReal;                       /**< points to the A real twiddle factor table. */
    q31_t *pTwiddleBReal;                       /**< points to the B real twiddle factor table. */
    const csi_cfft_instance_q31 *pCfft;        /**< points to the complex FFT instance. */
  } csi_rfft_fast_instance_q31;

  typedef struct
  {
    uint32_t fftLenReal;                      /**< length of the real FFT. */
    uint8_t ifftFlagR;                        /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
    uint8_t bitReverseFlagR;                  /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
    q15_t *pTwiddleAReal;                     /**< points to the A real twiddle factor table. */
    q15_t *pTwiddleBReal;                     /**< points to the B real twiddle factor table. */
    const csi_cfft_instance_q15 *pCfft;      /**< points to the complex FFT instance. */
  } csi_rfft_fast_instance_q15;

/**
 * @brief Instance structure for the Q15 RFFT/RIFFT function.
 */
typedef struct {
    uint32_t fftLenReal;                      /**< length of the real FFT. */
    uint8_t ifftFlagR;                        /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
    uint8_t bitReverseFlagR;                  /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
    uint32_t twidCoefRModifier;               /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    q15_t *pTwiddleAReal;                     /**< points to the real twiddle factor table. */
#if (!defined __riscv_xthead) && (defined __riscv)
    q15_t *pTwiddleBReal;                     /**< points to the imag twiddle factor table. */
#endif
    const csi_cfft_instance_q15 *pCfft;       /**< points to the complex FFT instance. */
} csi_rfft_instance_q15;


/**
 * @brief Instance structure for the Q31 RFFT/RIFFT function.
 */
typedef struct {
    uint32_t fftLenReal;                        /**< length of the real FFT. */
    uint8_t ifftFlagR;                          /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
    uint8_t bitReverseFlagR;                    /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
    uint32_t twidCoefRModifier;                 /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    q31_t *pTwiddleAReal;                       /**< points to the real twiddle factor table. */
#if (!defined __riscv_xthead) && (defined __riscv)
    q31_t *pTwiddleBReal;                       /**< points to the imag twiddle factor table. */
#endif
    const csi_cfft_instance_q31 *pCfft;         /**< points to the complex FFT instance. */
} csi_rfft_instance_q31;


/**
 * @brief Instance structure for the floating-point RFFT/RIFFT function.
 */
typedef struct {
    uint32_t fftLenReal;                        /**< length of the real FFT. */
    uint16_t fftLenBy2;                         /**< length of the complex FFT. */
    uint8_t ifftFlagR;                          /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
    uint8_t bitReverseFlagR;                    /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
    uint32_t twidCoefRModifier;                     /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    float32_t *pTwiddleAReal;                   /**< points to the real twiddle factor table. */
    float32_t *pTwiddleBReal;                   /**< points to the imag twiddle factor table. */
    csi_cfft_radix4_instance_f32 *pCfft;        /**< points to the complex FFT instance. */
} csi_rfft_instance_f32;

/**
 * @brief Instance structure for the floating-point RFFT/RIFFT function.
 */
typedef struct {
    csi_cfft_instance_f32 Sint;      /**< Internal CFFT structure. */
    uint16_t fftLenRFFT;             /**< length of the real sequence */
    const float32_t * pTwiddleRFFT;        /**< Twiddle factors real stage  */
} csi_rfft_fast_instance_f32 ;

/**
 * @brief Instance structure for the floating-point DCT4/IDCT4 function.
 */
typedef struct {
    uint16_t N;                          /**< length of the DCT4. */
    uint16_t Nby2;                       /**< half of the length of the DCT4. */
    float32_t normalize;                 /**< normalizing factor. */
    const float32_t *pTwiddle;                 /**< points to the twiddle factor table. */
    const float32_t *pCosFactor;               /**< points to the cosFactor table. */
    csi_rfft_fast_instance_f32 *pRfft;        /**< points to the real FFT instance. */
    csi_cfft_radix4_instance_f32 *pCfft; /**< points to the complex FFT instance. */
} csi_dct4_instance_f32;


/**
 * @brief Instance structure for the Q31 DCT4/IDCT4 function.
 */
typedef struct {
    uint16_t N;                          /**< length of the DCT4. */
    uint16_t Nby2;                       /**< half of the length of the DCT4. */
    q31_t normalize;                     /**< normalizing factor. */
    const q31_t *pTwiddle;                     /**< points to the twiddle factor table. */
    const q31_t *pCosFactor;                   /**< points to the cosFactor table. */
    csi_rfft_instance_q31 *pRfft;        /**< points to the real FFT instance. */
    csi_cfft_radix4_instance_q31 *pCfft; /**< points to the complex FFT instance. */
} csi_dct4_instance_q31;


/**
 * @brief Instance structure for the Q15 DCT4/IDCT4 function.
 */
typedef struct {
    uint16_t N;                          /**< length of the DCT4. */
    uint16_t Nby2;                       /**< half of the length of the DCT4. */
    q15_t normalize;                     /**< normalizing factor. */
    const q15_t *pTwiddle;                     /**< points to the twiddle factor table. */
    const q15_t *pCosFactor;                   /**< points to the cosFactor table. */
    csi_rfft_instance_q15 *pRfft;        /**< points to the real FFT instance. */
    csi_cfft_radix4_instance_q15 *pCfft; /**< points to the complex FFT instance. */
} csi_dct4_instance_q15;

  typedef struct
  {
    uint16_t N;                           /**< length of the DCT4. */
    uint16_t Nby2;                        /**< half of the length of the DCT4. */
    q15_t normalize;                      /**< normalizing factor. */
    q15_t *pTwiddle;                      /**< points to the twiddle factor table. */
    q15_t *pCosFactor;                    /**< points to the cosFactor table. */
    csi_rfft_fast_instance_q15 *pRfft;        /**< points to the real FFT instance. */
    csi_cfft_radix4_instance_q15 *pCfft; /**< points to the complex FFT instance. */
  } csi_dct4_fast_instance_q15;

  typedef struct
  {
    uint16_t N;                           /**< length of the DCT4. */
    uint16_t Nby2;                        /**< half of the length of the DCT4. */
    q31_t normalize;                      /**< normalizing factor. */
    q31_t *pTwiddle;                      /**< points to the twiddle factor table. */
    q31_t *pCosFactor;                    /**< points to the cosFactor table. */
    csi_rfft_fast_instance_q31 *pRfft;        /**< points to the real FFT instance. */
    csi_cfft_radix4_instance_q31 *pCfft; /**< points to the complex FFT instance. */
  } csi_dct4_fast_instance_q31;

  csi_status csi_dct4_init_q31(
  csi_dct4_instance_q31 * S,
  csi_rfft_instance_q31 * S_RFFT,
  csi_cfft_radix4_instance_q31 * S_CFFT,
  uint16_t N,
  uint16_t Nby2,
  q31_t normalize);

  void csi_dct4_q31(
  const csi_dct4_instance_q31 * S,
  q31_t * pState,
  q31_t * pInlineBuffer);

  void csi_dct4_fast_q31(
  const csi_dct4_fast_instance_q31 * S,
  q31_t * pState,
  q31_t * pInlineBuffer);


/**
 * @brief Instance structure for the Q15 FIR decimator.
 */
typedef struct {
    uint8_t M;                  /**< decimation factor. */
    uint16_t numTaps;           /**< number of coefficients in the filter. */
    const q15_t *pCoeffs;             /**< points to the coefficient array. The array is of length numTaps.*/
    q15_t *pState;              /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
} csi_fir_decimate_instance_q15;

/**
 * @brief Instance structure for the Q31 FIR decimator.
 */
typedef struct {
    uint8_t M;                  /**< decimation factor. */
    uint16_t numTaps;           /**< number of coefficients in the filter. */
    const q31_t *pCoeffs;             /**< points to the coefficient array. The array is of length numTaps.*/
    q31_t *pState;              /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
} csi_fir_decimate_instance_q31;

/**
  @brief Instance structure for floating-point FIR decimator.
 */
typedef struct {
    uint8_t M;                  /**< decimation factor. */
    uint16_t numTaps;           /**< number of coefficients in the filter. */
    const float32_t *pCoeffs;         /**< points to the coefficient array. The array is of length numTaps.*/
    float32_t *pState;          /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
} csi_fir_decimate_instance_f32;

/**
 * @brief Instance structure for the Q15 FIR interpolator.
 */
typedef struct {
    uint8_t L;                      /**< upsample factor. */
    uint16_t phaseLength;           /**< length of each polyphase filter component. */
    const q15_t *pCoeffs;                 /**< points to the coefficient array. The array is of length L*phaseLength. */
    q15_t *pState;                  /**< points to the state variable array. The array is of length blockSize+phaseLength-1. */
} csi_fir_interpolate_instance_q15;

/**
 * @brief Instance structure for the Q31 FIR interpolator.
 */
typedef struct {
    uint8_t L;                      /**< upsample factor. */
    uint16_t phaseLength;           /**< length of each polyphase filter component. */
    const q31_t *pCoeffs;                 /**< points to the coefficient array. The array is of length L*phaseLength. */
    q31_t *pState;                  /**< points to the state variable array. The array is of length blockSize+phaseLength-1. */
} csi_fir_interpolate_instance_q31;

/**
 * @brief Instance structure for the floating-point FIR interpolator.
 */
typedef struct {
    uint8_t L;                     /**< upsample factor. */
    uint16_t phaseLength;          /**< length of each polyphase filter component. */
    const float32_t *pCoeffs;            /**< points to the coefficient array. The array is of length L*phaseLength. */
    float32_t *pState;             /**< points to the state variable array. The array is of length phaseLength+numTaps-1. */
} csi_fir_interpolate_instance_f32;


/**
 * @brief Instance structure for the high precision Q31 Biquad cascade filter.
 */
typedef struct {
    uint8_t numStages;       /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    q63_t *pState;           /**< points to the array of state coefficients.  The array is of length 4*numStages. */
    const q31_t *pCoeffs;          /**< points to the array of coefficients.  The array is of length 5*numStages. */
    uint8_t postShift;       /**< additional shift, in bits, applied to each output sample. */
} csi_biquad_cas_df1_32x64_ins_q31;

/**
 * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
 */
typedef struct {
    uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    float32_t *pState;         /**< points to the array of state coefficients.  The array is of length 2*numStages. */
    const float32_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
} csi_biquad_cascade_df2T_instance_f32;

/**
 * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
 */
typedef struct {
    uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    float32_t *pState;         /**< points to the array of state coefficients.  The array is of length 4*numStages. */
    const float32_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
} csi_biquad_cascade_stereo_df2T_instance_f32;

/**
 * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
 */
typedef struct {
    uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    float64_t *pState;         /**< points to the array of state coefficients.  The array is of length 2*numStages. */
    float64_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
} csi_biquad_cascade_df2T_instance_f64;

/**
 * @brief Instance structure for the Q15 FIR lattice filter.
 */
typedef struct {
    uint16_t numStages;                  /**< number of filter stages. */
    q15_t *pState;                       /**< points to the state variable array. The array is of length numStages. */
    const q15_t *pCoeffs;                      /**< points to the coefficient array. The array is of length numStages. */
} csi_fir_lattice_instance_q15;

/**
 * @brief Instance structure for the Q31 FIR lattice filter.
 */
typedef struct {
    uint16_t numStages;                  /**< number of filter stages. */
    q31_t *pState;                       /**< points to the state variable array. The array is of length numStages. */
    const q31_t *pCoeffs;                      /**< points to the coefficient array. The array is of length numStages. */
} csi_fir_lattice_instance_q31;

/**
 * @brief Instance structure for the floating-point FIR lattice filter.
 */
typedef struct {
    uint16_t numStages;                  /**< number of filter stages. */
    float32_t *pState;                   /**< points to the state variable array. The array is of length numStages. */
    const float32_t *pCoeffs;                  /**< points to the coefficient array. The array is of length numStages. */
} csi_fir_lattice_instance_f32;


/**
 * @brief Instance structure for the Q15 IIR lattice filter.
 */
typedef struct {
    uint16_t numStages;                  /**< number of stages in the filter. */
    q15_t *pState;                       /**< points to the state variable array. The array is of length numStages+blockSize. */
    q15_t *pkCoeffs;                     /**< points to the reflection coefficient array. The array is of length numStages. */
    q15_t *pvCoeffs;                     /**< points to the ladder coefficient array. The array is of length numStages+1. */
} csi_iir_lattice_instance_q15;

/**
 * @brief Instance structure for the Q31 IIR lattice filter.
 */
typedef struct {
    uint16_t numStages;                  /**< number of stages in the filter. */
    q31_t *pState;                       /**< points to the state variable array. The array is of length numStages+blockSize. */
    q31_t *pkCoeffs;                     /**< points to the reflection coefficient array. The array is of length numStages. */
    q31_t *pvCoeffs;                     /**< points to the ladder coefficient array. The array is of length numStages+1. */
} csi_iir_lattice_instance_q31;

/**
 * @brief Instance structure for the floating-point IIR lattice filter.
 */
typedef struct {
    uint16_t numStages;                  /**< number of stages in the filter. */
    float32_t *pState;                   /**< points to the state variable array. The array is of length numStages+blockSize. */
    float32_t *pkCoeffs;                 /**< points to the reflection coefficient array. The array is of length numStages. */
    float32_t *pvCoeffs;                 /**< points to the ladder coefficient array. The array is of length numStages+1. */
} csi_iir_lattice_instance_f32;


/**
 * @brief Instance structure for the floating-point LMS filter.
 */
typedef struct {
    uint16_t numTaps;    /**< number of coefficients in the filter. */
    float32_t *pState;   /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    float32_t *pCoeffs;  /**< points to the coefficient array. The array is of length numTaps. */
    float32_t mu;        /**< step size that controls filter coefficient updates. */
} csi_lms_instance_f32;


/**
 * @brief Instance structure for the Q15 LMS filter.
 */
typedef struct {
    uint16_t numTaps;    /**< number of coefficients in the filter. */
    q15_t *pState;       /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q15_t *pCoeffs;      /**< points to the coefficient array. The array is of length numTaps. */
    q15_t mu;            /**< step size that controls filter coefficient updates. */
    uint32_t postShift;  /**< bit shift applied to coefficients. */
} csi_lms_instance_q15;


/**
 * @brief Instance structure for the Q31 LMS filter.
 */
typedef struct {
    uint16_t numTaps;    /**< number of coefficients in the filter. */
    q31_t *pState;       /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q31_t *pCoeffs;      /**< points to the coefficient array. The array is of length numTaps. */
    q31_t mu;            /**< step size that controls filter coefficient updates. */
    uint32_t postShift;  /**< bit shift applied to coefficients. */
} csi_lms_instance_q31;


/**
 * @brief Instance structure for the floating-point normalized LMS filter.
 */
typedef struct {
    uint16_t numTaps;     /**< number of coefficients in the filter. */
    float32_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    float32_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
    float32_t mu;         /**< step size that control filter coefficient updates. */
    float32_t energy;     /**< saves previous frame energy. */
    float32_t x0;         /**< saves previous input sample. */
} csi_lms_norm_instance_f32;

/**
 * @brief Instance structure for the Q31 normalized LMS filter.
 */
typedef struct {
    uint16_t numTaps;     /**< number of coefficients in the filter. */
    q31_t *pState;        /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q31_t *pCoeffs;       /**< points to the coefficient array. The array is of length numTaps. */
    q31_t mu;             /**< step size that controls filter coefficient updates. */
    uint8_t postShift;    /**< bit shift applied to coefficients. */
    const q31_t *recipTable;    /**< points to the reciprocal initial value table. */
    q31_t energy;         /**< saves previous frame energy. */
    q31_t x0;             /**< saves previous input sample. */
} csi_lms_norm_instance_q31;


/**
 * @brief Instance structure for the Q15 normalized LMS filter.
 */
typedef struct {
    uint16_t numTaps;     /**< Number of coefficients in the filter. */
    q15_t *pState;        /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q15_t *pCoeffs;       /**< points to the coefficient array. The array is of length numTaps. */
    q15_t mu;             /**< step size that controls filter coefficient updates. */
    uint8_t postShift;    /**< bit shift applied to coefficients. */
    const q15_t *recipTable;    /**< Points to the reciprocal initial value table. */
    q15_t energy;         /**< saves previous frame energy. */
    q15_t x0;             /**< saves previous input sample. */
} csi_lms_norm_instance_q15;

/**
 * @brief Instance structure for the floating-point sparse FIR filter.
 */
typedef struct {
    uint16_t numTaps;             /**< number of coefficients in the filter. */
    uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
    float32_t *pState;            /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const float32_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
    uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
    int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
} csi_fir_sparse_instance_f32;

/**
 * @brief Instance structure for the Q31 sparse FIR filter.
 */
typedef struct {
    uint16_t numTaps;             /**< number of coefficients in the filter. */
    uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
    q31_t *pState;                /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const q31_t *pCoeffs;               /**< points to the coefficient array. The array is of length numTaps.*/
    uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
    int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
} csi_fir_sparse_instance_q31;

/**
 * @brief Instance structure for the Q15 sparse FIR filter.
 */
typedef struct {
    uint16_t numTaps;             /**< number of coefficients in the filter. */
    uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
    q15_t *pState;                /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const q15_t *pCoeffs;               /**< points to the coefficient array. The array is of length numTaps.*/
    uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
    int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
} csi_fir_sparse_instance_q15;

/**
 * @brief Instance structure for the Q7 sparse FIR filter.
 */
typedef struct {
    uint16_t numTaps;             /**< number of coefficients in the filter. */
    uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
    q7_t *pState;                 /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const q7_t *pCoeffs;                /**< points to the coefficient array. The array is of length numTaps.*/
    uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
    int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
} csi_fir_sparse_instance_q7;


/**
* @brief Struct for specifying SVM Kernel
*
*/
typedef enum {
    CSI_ML_KERNEL_LINEAR = 0,
    /**< Linear kernel */
    CSI_ML_KERNEL_POLYNOMIAL = 1,
    /**< Polynomial kernel */
    CSI_ML_KERNEL_RBF = 2,
    /**< Radial Basis Function kernel */
    CSI_ML_KERNEL_SIGMOID = 3
                              /**< Sigmoid kernel */
} csi_ml_kernel_type;



/**
 * @brief Instance structure for linear SVM prediction function.
 */
typedef struct {
    uint32_t        nbOfSupportVectors;     /**< Number of support vectors */
    uint32_t        vectorDimension;        /**< Dimension of vector space */
    float32_t       intercept;              /**< Intercept */
    const float32_t *dualCoefficients;      /**< Dual coefficients */
    const float32_t *supportVectors;        /**< Support vectors */
    const int32_t   *classes;               /**< The two SVM classes */
} csi_svm_linear_instance_f32;


/**
 * @brief Instance structure for polynomial SVM prediction function.
 */
typedef struct {
    uint32_t        nbOfSupportVectors;     /**< Number of support vectors */
    uint32_t        vectorDimension;        /**< Dimension of vector space */
    float32_t       intercept;              /**< Intercept */
    const float32_t *dualCoefficients;      /**< Dual coefficients */
    const float32_t *supportVectors;        /**< Support vectors */
    const int32_t   *classes;               /**< The two SVM classes */
    int32_t         degree;                 /**< Polynomial degree */
    float32_t       coef0;                  /**< Polynomial constant */
    float32_t       gamma;                  /**< Gamma factor */
} csi_svm_polynomial_instance_f32;

/**
 * @brief Instance structure for rbf SVM prediction function.
 */
typedef struct {
    uint32_t        nbOfSupportVectors;     /**< Number of support vectors */
    uint32_t        vectorDimension;        /**< Dimension of vector space */
    float32_t       intercept;              /**< Intercept */
    const float32_t *dualCoefficients;      /**< Dual coefficients */
    const float32_t *supportVectors;        /**< Support vectors */
    const int32_t   *classes;               /**< The two SVM classes */
    float32_t       gamma;                  /**< Gamma factor */
} csi_svm_rbf_instance_f32;

/**
 * @brief Instance structure for sigmoid SVM prediction function.
 */
typedef struct {
    uint32_t        nbOfSupportVectors;     /**< Number of support vectors */
    uint32_t        vectorDimension;        /**< Dimension of vector space */
    float32_t       intercept;              /**< Intercept */
    const float32_t *dualCoefficients;      /**< Dual coefficients */
    const float32_t *supportVectors;        /**< Support vectors */
    const int32_t   *classes;               /**< The two SVM classes */
    float32_t       coef0;                  /**< Independant constant */
    float32_t       gamma;                  /**< Gamma factor */
} csi_svm_sigmoid_instance_f32;

/**
 * @brief Instance structure for Naive Gaussian Bayesian estimator.
 */
typedef struct {
    uint32_t vectorDimension;  /**< Dimension of vector space */
    uint32_t numberOfClasses;  /**< Number of different classes  */
    const float32_t *theta;          /**< Mean values for the Gaussians */
    const float32_t *sigma;          /**< Variances for the Gaussians */
    const float32_t *classPriors;    /**< Class prior probabilities */
    float32_t epsilon;         /**< Additive value to variances */
} csi_gaussian_naive_bayes_instance_f32;

#ifdef CSI_SIMD
/* SMMLAR */
__ALWAYS_STATIC_INLINE int32_t multAcc_32x32_keep32_R(int32_t a, int32_t x, int32_t y)
{
    __ASM volatile("mula.s32.rhs %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y) : "0" (a), "1" (x), "2" (y));
    return a;
}

/* SMMLSR */
__ALWAYS_STATIC_INLINE int32_t multSub_32x32_keep32_R(int32_t a, int32_t x, int32_t y)
{
    __ASM volatile("muls.s32.rhs %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y): "0" (a), "1" (x), "2" (y));
    return a;
}

/* SMMULR */
__ALWAYS_STATIC_INLINE int32_t mult_32x32_keep32_R(int32_t x, int32_t y)
{
    int32_t a;
    __ASM volatile("mul.s32.rh %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y): "1" (x), "2" (y));
    return a;
}

/* SMMLA */
__ALWAYS_STATIC_INLINE int32_t multAcc_32x32_keep32(int32_t a, int32_t x, int32_t y)
{
    __ASM volatile("mula.s32.hs %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y): "0" (a), "1" (x), "2" (y));
    return a;
}

/* SMMLS */
__ALWAYS_STATIC_INLINE int32_t multSub_32x32_keep32(int32_t a, int32_t x, int32_t y)
{
    __ASM volatile("muls.s32.hs %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y): "0" (a), "1" (x), "2" (y));
    return a;
}

/* SMMUL */
__ALWAYS_STATIC_INLINE int32_t mult_32x32_keep32(int32_t x, int32_t y)
{
    int32_t a;
    __ASM volatile("mul.s32.h %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y): "0" (a), "1" (x), "2" (y));
    return a;
}

__ALWAYS_STATIC_INLINE int32_t multAcc_16x16_keep32(int32_t a, int16_t x, int16_t y)
{
    __ASM volatile("mulall.s16 %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y): "0" (a), "1" (x), "2" (y));
    return a;
}

__ALWAYS_STATIC_INLINE int64_t multAcc_16x16_keep64(int64_t a, int16_t x, int16_t y)
{
    __ASM volatile("mulall.s16.e %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y): "0" (a), "1" (x), "2" (y));
    return a;
}

__ALWAYS_STATIC_INLINE int64_t mult_32x32_keep64(int32_t x, int32_t y)
{
    int64_t a;
    __ASM volatile("mul.s32 %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y): "1" (x), "2" (y));
    return a;
}

__ALWAYS_STATIC_INLINE int64_t multAcc_32x32_keep64(int64_t a, int32_t x, int32_t y)
{
    __ASM volatile("mula.s32 %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y): "0" (a), "1" (x), "2" (y));
    return a;
}

__ALWAYS_STATIC_INLINE int32_t mult_32x32_dext_31(int32_t x, int32_t y)
{
    int64_t tmp1;
    int32_t tmp2;
    __ASM volatile("mul.s32 %0, %1, %2\n\t"
                   "dexti %3, %0, %R0, 31"
                   :"=r" (tmp1), "=r" (x), "=r" (y), "=r" (tmp2): "1" (x), "2" (y));
    return tmp2;
}

__ALWAYS_STATIC_INLINE int32_t mult_32x32_dext_30(int32_t x, int32_t y)
{
    int64_t tmp1;
    int32_t tmp2;
    __ASM volatile("mul.s32 %0, %1, %2\n\t"
                   "dexti %3, %0, %R0, 30"
                   :"=r" (tmp1), "=r" (x), "=r" (y), "=r" (tmp2): "1" (x), "2" (y));
    return tmp2;
}

__ALWAYS_STATIC_INLINE int32_t mult_32x32_dext_4(int32_t x, int32_t y)
{
    int64_t tmp1;
    int32_t tmp2;
    __ASM volatile("mul.s32 %0, %1, %2\n\t"
                   "dexti %3, %0, %R0, 4"
                   :"=r" (tmp1), "=r" (x), "=r" (y), "=r" (tmp2): "1" (x), "2" (y));
    return tmp2;
}

__ALWAYS_STATIC_INLINE int32_t mult_32x32_dext_33(int32_t x, int32_t y)
{
    int64_t tmp1;
    int32_t tmp2;
    __ASM volatile("mul.s32 %0, %1, %2\n\t"
                   "asri %3, %R0, 1"
                   :"=r" (tmp1), "=r" (x), "=r" (y), "=r" (tmp2): "1" (x), "2" (y));
    return tmp2;
}

__ALWAYS_STATIC_INLINE int32_t dext_31(int64_t x)
{
    int32_t tmp1;
    __ASM volatile(
                   "dexti %0, %1, %R1, 31"
                   :"=r" (tmp1), "=r" (x) : "1" (x));
    return tmp1;
}

__ALWAYS_STATIC_INLINE int32_t mult_l16xl16_keep32(int32_t x, int32_t y)
{
    int32_t a;
    __ASM volatile("mulll.s16 %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y): "1" (x), "2" (y));
    return a;
}

__ALWAYS_STATIC_INLINE int32_t mult_h16xl16_keep32(int32_t x, int32_t y)
{
    int32_t a;
    __ASM volatile("mulhl.s16 %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y): "1" (x), "2" (y));
    return a;
}

__ALWAYS_STATIC_INLINE int32_t mult_h16xh16_keep32(int32_t x, int32_t y)
{
    int32_t a;
    __ASM volatile("mulhh.s16 %0, %1, %2\n\t"
                   :"=r" (a), "=r" (x), "=r" (y): "1" (x), "2" (y));
    return a;
}

#else

/* SMMLAR */
#define multAcc_32x32_keep32_R(a, x, y) \
    a = (q31_t) (((((q63_t) a) << 32) + ((q63_t) x * y) + 0x80000000LL ) >> 32)

/* SMMLSR */
#define multSub_32x32_keep32_R(a, x, y) \
    a = (q31_t) (((((q63_t) a) << 32) - ((q63_t) x * y) + 0x80000000LL ) >> 32)

/* SMMULR */
#define mult_32x32_keep32_R(a, x, y) \
    a = (q31_t) (((q63_t) x * y + 0x80000000LL ) >> 32)

/* SMMLA */
#define multAcc_32x32_keep32(a, x, y) \
    a += (q31_t) (((q63_t) x * y) >> 32)

/* SMMLS */
#define multSub_32x32_keep32(a, x, y) \
    a -= (q31_t) (((q63_t) x * y) >> 32)

/* SMMUL */
#define mult_32x32_keep32(a, x, y) \
    a = (q31_t) (((q63_t) x * y ) >> 32)
#endif
#ifdef   __cplusplus
}
#endif


#endif /* _CSI_MATH_H */

/**
 *
 * End of file.
 */
