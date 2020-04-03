/*
 * Copyright (C) 2010-2018 Arm Limited or its affiliates. All rights reserved.
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
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

/* ----------------------------------------------------------------------
 * Project:      NMSIS NN Library
 * Title:        riscv_nnsupportfunctions.h
 * Description:  Public header file of support functions for NMSIS NN Library
 *
 * $Date:        July 2019
 * $Revision:    V.1.0.0
 *
 * Target Processor: RISC-V Cores
 * -------------------------------------------------------------------- */

#ifndef _RISCV_NNSUPPORTFUNCTIONS_H_
#define _RISCV_NNSUPPORTFUNCTIONS_H_

#include "riscv_math.h"
#include "riscv_common_tables.h"

#ifdef __cplusplus
extern    "C"
{
#endif

#define LEFT_SHIFT(_shift)  (_shift > 0 ? _shift : 0)
#define RIGHT_SHIFT(_shift) (_shift > 0 ? 0 : -_shift)
#define Q31_MIN (0x80000000L)
#define Q31_MAX (0x7FFFFFFFL)

#define MAX(A,B) (A) > (B) ? (A) : (B)
#define MIN(A,B) (A) < (B) ? (A) : (B)

/**
 * @brief Union for SIMD access of q31/q15/q7 types
 */
union riscv_nnword
{
    q31_t     word;
               /**< q31 type */
    q15_t     half_words[2];
               /**< q15 type */
    q7_t      bytes[4];
               /**< q7 type */
};

/**
 * @brief Struct for specifying activation function types
 *
 */
typedef enum
{
    RISCV_SIGMOID = 0,
                /**< Sigmoid activation function */
    RISCV_TANH = 1,
             /**< Tanh activation function */
} riscv_nn_activation_type;

/**
 * @defgroup nndata_convert Neural Network Data Conversion Functions
 *
 * Perform data type conversion in-between neural network operations
 *
 */

/**
 * @brief Converts the elements of the q7 vector to q15 vector without left-shift
 * @param[in]       *pSrc points to the q7 input vector
 * @param[out]      *pDst points to the q15 output vector
 * @param[in]       blockSize length of the input vector
 * @return none.
 *
 */
void      riscv_q7_to_q15_no_shift(const q7_t * pSrc, q15_t * pDst, uint32_t blockSize);

void      riscv_q7_to_q7_no_shift(const q7_t * pSrc, q7_t * pDst, uint32_t blockSize);

/**
 * @brief Non-saturating addition of elements of a q7 vector
 * @param[in]       *input Pointer to the q7 input vector
 * @param[out]      *output Pointer to the q31 output variable.
 * @param[in]       block_size length of the input vector
 * @return none.
 * \par Description:
 *
 * 2^24 samples can be added without saturating the result.
 *
 * The equation used for the conversion process is:
 *
 * <pre>
 *  sum = input[0] + input[1] + .. + input[block_size -1]
 * </pre>
 *
 * */
void riscv_nn_add_q7(const q7_t *input, q31_t *output, uint32_t block_size);

/**
 * @brief  Converts the elements of the q7 vector to reordered q15 vector without left-shift
 * @param[in]       *pSrc points to the q7 input vector
 * @param[out]      *pDst points to the q15 output vector
 * @param[in]       blockSize length of the input vector
 * @return none.
 *
 */
void      riscv_q7_to_q15_reordered_no_shift(const q7_t * pSrc, q15_t * pDst, uint32_t blockSize);

void      riscv_q7_to_q7_reordered_no_shift(const q7_t * pSrc, q7_t * pDst, uint32_t blockSize);

/**
 * @brief Converts the elements from a q7 vector to a q15 vector with an added offset
 * @param[in]    *src       points to the q7 input vector
 * @param[out]   *dst       points to the q15 output vector
 * @param[in]    block_size length of the input vector
 * @param[in]    offset     q7 offset to be added to each input vector element.
 * @return none.
 *
 * \par Description:
 *
 * The equation used for the conversion process is:
 *
 * <pre>
 *  dst[n] = (q15_t) src[n] + offset;   0 <= n < block_size.
 * </pre>
 *
 */
void riscv_q7_to_q15_with_offset(const q7_t *src, q15_t *dst, uint32_t block_size, q7_t offset);

#if defined (RISCV_MATH_DSP)

/**
 * @brief read and expand one q7 word into two q15 words
 */

__STATIC_FORCEINLINE void *read_and_pad(void *source, q31_t * out1, q31_t * out2)
{
        q31_t     inA = *__SIMD32(source)++;
        q31_t     inAbuf1 = __SXTB16(__ROR(inA, 8));
        q31_t     inAbuf2 = __SXTB16(inA);

        *out2 = __PKHTB(inAbuf1, inAbuf2, 16);
        *out1 = __PKHBT(inAbuf2, inAbuf1, 16);

        return source;
}

/**
 * @brief read and expand one q7 word into two q15 words with reordering
 */

__STATIC_FORCEINLINE q7_t *read_and_pad_reordered(q7_t *source, q31_t * out1, q31_t * out2)
{
        q31_t     inA = read_q7x4_ia(&source);
        *out2 = __SXTB16(__ROR(inA, 8));
        *out1 = __SXTB16(inA);

        return source;
}

/**
 * @brief read and expand one q7 word into two q15 words with reordering and add an offset
 */
__STATIC_FORCEINLINE q7_t *read_and_pad_reordered_with_offset(q7_t *source, q31_t * out1, q31_t * out2,q31_t offset)
{
        q31_t     inA = read_q7x4_ia(&source);

        *out2 = __SXTB16(__ROR(inA, 8));
        *out1 = __SXTB16(inA);
        *out1 = __QADD16(*out1,offset);
        *out2 = __QADD16(*out2,offset);

        return source;
}


#endif



/**
 * @defgroup NNBasicMath Basic Math Functions for Neural Network Computation
 *
 * Basic Math Functions for Neural Network Computation
 *
 */

/**
 * @brief           q7 vector multiplication with variable output shifts
 * @param[in]       *pSrcA        pointer to the first input vector
 * @param[in]       *pSrcB        pointer to the second input vector
 * @param[out]      *pDst         pointer to the output vector
 * @param[in]       out_shift     amount of right-shift for output
 * @param[in]       blockSize     number of samples in each vector
 * @return none.
 *
 * <b>Scaling and Overflow Behavior:</b>
 * \par
 * The function uses saturating arithmetic.
 * Results outside of the allowable q15 range [0x8000 0x7FFF] will be saturated.
 */

void riscv_nn_mult_q15(
  q15_t * pSrcA,
  q15_t * pSrcB,
  q15_t * pDst,
  const uint16_t out_shift,
  uint32_t blockSize);

/**
 * @brief           q7 vector multiplication with variable output shifts
 * @param[in]       *pSrcA        pointer to the first input vector
 * @param[in]       *pSrcB        pointer to the second input vector
 * @param[out]      *pDst         pointer to the output vector
 * @param[in]       out_shift     amount of right-shift for output
 * @param[in]       blockSize     number of samples in each vector
 * @return none.
 *
 * <b>Scaling and Overflow Behavior:</b>
 * \par
 * The function uses saturating arithmetic.
 * Results outside of the allowable q7 range [0x80 0x7F] will be saturated.
 */

void riscv_nn_mult_q7(
  q7_t * pSrcA,
  q7_t * pSrcB,
  q7_t * pDst,
  const uint16_t out_shift,
  uint32_t blockSize);

/**
 * @brief macro for adding rounding offset
 */
#ifndef RISCV_NN_TRUNCATE
    #define NN_ROUND(out_shift) ( (0x1 << out_shift) >> 1 )
#else
    #define NN_ROUND(out_shift) 0
#endif

/**
 * @brief           Saturating doubling high multiply. Result matches
 *                  NEON instruction VQRDMULH.
 * @param[in]       m1        Multiplicand
 * @param[in]       m2        Multiplier
 * @return          Result of multiplication.
 *
 */
__STATIC_FORCEINLINE q31_t riscv_nn_sat_doubling_high_mult(const q31_t m1, const q31_t m2)
{
    q31_t result = 0;
    // Rounding offset to add for a right shift of 31
    q63_t mult = 1 << 30;

    if ((m1 < 0) ^ (m2 < 0))
    {
        mult = 1 - mult;
    }
    // Gets resolved as a SMLAL instruction
    mult = mult + (q63_t)m1 * m2;

    // Utilize all of the upper 32 bits. This is the doubling step
    // as well.
    result = mult / (1UL << 31);

    if ((m1 == m2) && (m1 == Q31_MIN))
    {
        result = Q31_MAX;
    }
    return result;
}

/**
 * @brief           Rounding divide by power of two.
 * @param[in]       dividend - Dividend
 * @param[in]       exponent - Divisor = power(2, exponent)
 *                             Range: [0, 31]
 * @return          Rounded result of division. Midpoint is rounded away from zero.
 *
 */
__STATIC_FORCEINLINE q31_t riscv_nn_divide_by_power_of_two(const q31_t dividend, const q31_t exponent)
{
    q31_t result = 0;
    const q31_t remainder_mask = (1l << exponent) - 1;
    int32_t remainder = remainder_mask & dividend;

    // Basic division
    result = dividend >> exponent;

    // Adjust 'result' for rounding (mid point away from zero)
    q31_t threshold = remainder_mask >> 1;
    if (result < 0)
    {
        threshold++;
    }
    if (remainder > threshold)
    {
        result++;
    }

    return result;
}

/**
 * @brief           Requantize a given value.
 * @param[in]       val         Value to be requantized
 * @param[in]       multiplier  multiplier
 * @param[in]       shift       left or right shift for 'val * multiplier'
 *
 * @return          Returns (val * multiplier)/(2 ^ shift)
 *
 */
__STATIC_FORCEINLINE q31_t riscv_nn_requantize(const q31_t val, const q31_t multiplier, const q31_t shift)
{
  return riscv_nn_divide_by_power_of_two(riscv_nn_sat_doubling_high_mult(val * (1 << LEFT_SHIFT(shift)), multiplier),
                                       RIGHT_SHIFT(shift));
}

/**
  @brief         Read 2 q15 elements and post increment pointer.
  @param[in]     in_q15   Pointer to pointer that holds address of input.
  @return        q31 value
 */
__STATIC_FORCEINLINE q31_t riscv_nn_read_q15x2_ia(const q15_t **in_q15)
{
  q31_t val;

  memcpy(&val, *in_q15, 4);
  *in_q15 += 2;

  return (val);
}

/**
  @brief         Read 4 q7 from q7 pointer and post increment pointer.
  @param[in]     in_q7       Pointer to pointer that holds address of input.
  @return        q31 value
 */
__STATIC_FORCEINLINE q31_t riscv_nn_read_q7x4_ia(const q7_t **in_q7)
{
  q31_t val;
  memcpy(&val, *in_q7, 4);
  *in_q7 += 4;

  return (val);
}

#ifdef __cplusplus
}
#endif

#endif
