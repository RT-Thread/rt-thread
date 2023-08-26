/*
 * Copyright (C) 2010-2020 Arm Limited or its affiliates. All rights reserved.
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
 * Project:      CMSIS NN Library
 * Title:        arm_elementwise_add_s8
 * Description:  Element wise add
 *
 * $Date:        01. March 2021
 * $Revision:    V.2.5.3
 *
 * Target Processor:  Cortex-M CPUs
 *
 * -------------------------------------------------------------------- */

#include "arm_nnfunctions.h"
#include "arm_nnsupportfunctions.h"
#if defined(ARM_MATH_MVEI)
#include "arm_helium_utils.h"
#endif

#if defined(ARM_MATH_MVEI)
#define SAT_INPUT_VECT(__INPUT_V, __MULT, __SHIFT)                                                                     \
    __INPUT_V = arm_doubling_high_mult_mve(__INPUT_V, __MULT);                                                         \
    __INPUT_V = arm_divide_by_power_of_two_mve(__INPUT_V, -__SHIFT);
#endif

/**
 * @note The *_no_sat API does not mean that the input not saturated, Since
 *       __MULT is a positive integer, it is saturated. The API definition
 *       has more info about it.
 */
#define SAT_INPUT(__INPUT, __MULT, __SHIFT)                                                                            \
    __INPUT = arm_nn_doubling_high_mult_no_sat(__INPUT, __MULT);                                                       \
    __INPUT = arm_nn_divide_by_power_of_two(__INPUT, -__SHIFT);

/**
 *  @ingroup groupNN
 */

/**
 * @addtogroup BasicMath
 * @{
 */

/*
 * s8 element wise add
 *
 * Refer header file for details.
 *
 */

/* Note: __SHIFT is expected to be <=0 */

arm_status arm_elementwise_add_s8(const int8_t *input_1_vect,
                                  const int8_t *input_2_vect,
                                  const int32_t input_1_offset,
                                  const int32_t input_1_mult,
                                  const int32_t input_1_shift,
                                  const int32_t input_2_offset,
                                  const int32_t input_2_mult,
                                  const int32_t input_2_shift,
                                  const int32_t left_shift,
                                  int8_t *output,
                                  const int32_t out_offset,
                                  const int32_t out_mult,
                                  const int32_t out_shift,
                                  const int32_t out_activation_min,
                                  const int32_t out_activation_max,
                                  const uint32_t block_size)
{
#if defined(ARM_MATH_MVEI)
    int32_t count = (int32_t)block_size;

    while (count > 0)
    {
        int32x4_t vect_1;
        int32x4_t vect_2;

        mve_pred16_t p = vctp32q((uint32_t)count);

        vect_1 = vldrbq_z_s32(input_1_vect, p);
        vect_2 = vldrbq_z_s32(input_2_vect, p);

        vect_1 = vaddq_s32(vect_1, vdupq_n_s32(input_1_offset));
        vect_2 = vaddq_s32(vect_2, vdupq_n_s32(input_2_offset));

        vect_1 = vshlq_r_s32(vect_1, left_shift);
        vect_2 = vshlq_r_s32(vect_2, left_shift);

        SAT_INPUT_VECT(vect_1, input_1_mult, input_1_shift);
        SAT_INPUT_VECT(vect_2, input_2_mult, input_2_shift);

        vect_1 = vaddq_s32(vect_1, vect_2);
        SAT_INPUT_VECT(vect_1, out_mult, out_shift);

        vect_1 = vaddq_n_s32(vect_1, out_offset);

        vect_1 = vmaxq_s32(vect_1, vdupq_n_s32(out_activation_min));
        vect_1 = vminq_s32(vect_1, vdupq_n_s32(out_activation_max));

        input_1_vect += 4;
        input_2_vect += 4;
        vstrbq_p_s32(output, vect_1, p);

        output += 4;
        count -= 4;
    }
#else
    uint32_t loop_count;
    int32_t input_1;
    int32_t input_2;
    int32_t sum;

#if defined(ARM_MATH_DSP)
    int32_t a_1, b_1, a_2, b_2;

    int32_t offset_1_packed, offset_2_packed;

    int8_t r1, r2, r3, r4;

    offset_1_packed = (input_1_offset << 16U) | (input_1_offset & 0x0FFFFL);
    offset_2_packed = (input_2_offset << 16U) | (input_2_offset & 0x0FFFFL);

    loop_count = block_size >> 2;

    while (loop_count > 0U)
    {
        /* 4 outputs are calculated in one loop. The order of calculation is follows the order of output sign extension
           intrinsic */
        input_1_vect = read_and_pad_reordered(input_1_vect, &b_1, &a_1);
        input_2_vect = read_and_pad_reordered(input_2_vect, &b_2, &a_2);

        a_1 = __SADD16(a_1, offset_1_packed);
        b_1 = __SADD16(b_1, offset_1_packed);

        a_2 = __SADD16(a_2, offset_2_packed);
        b_2 = __SADD16(b_2, offset_2_packed);

        /* Sum 1 */
        input_1 = (b_1 & 0x0FFFF) << left_shift;

        SAT_INPUT(input_1, input_1_mult, input_1_shift);

        input_2 = (b_2 & 0x0FFFF) << left_shift;
        SAT_INPUT(input_2, input_2_mult, input_2_shift);

        sum = input_1 + input_2;
        SAT_INPUT(sum, out_mult, out_shift);
        sum += out_offset;
        sum = MAX(sum, out_activation_min);
        sum = MIN(sum, out_activation_max);
        r1 = (q7_t)sum;

        /* Sum 3 */
        input_1 = ((b_1 >> 16) & 0x0FFFF) << left_shift;
        SAT_INPUT(input_1, input_1_mult, input_1_shift);

        input_2 = ((b_2 >> 16) & 0x0FFFF) << left_shift;
        SAT_INPUT(input_2, input_2_mult, input_2_shift);

        sum = input_1 + input_2;
        SAT_INPUT(sum, out_mult, out_shift);
        sum += out_offset;
        sum = MAX(sum, out_activation_min);
        sum = MIN(sum, out_activation_max);
        r3 = (q7_t)sum;

        /* Sum 2 */
        input_1 = (a_1 & 0x0FFFF) << left_shift;
        SAT_INPUT(input_1, input_1_mult, input_1_shift);

        input_2 = (a_2 & 0x0FFFF) << left_shift;
        SAT_INPUT(input_2, input_2_mult, input_2_shift);

        sum = input_1 + input_2;
        SAT_INPUT(sum, out_mult, out_shift);
        sum += out_offset;
        sum = MAX(sum, out_activation_min);
        sum = MIN(sum, out_activation_max);
        r2 = (q7_t)sum;

        /* Sum 4 */
        input_1 = ((a_1 >> 16) & 0x0FFFF) << left_shift;
        SAT_INPUT(input_1, input_1_mult, input_1_shift);

        input_2 = ((a_2 >> 16) & 0x0FFFF) << left_shift;
        SAT_INPUT(input_2, input_2_mult, input_2_shift);

        sum = input_1 + input_2;
        SAT_INPUT(sum, out_mult, out_shift);
        sum += out_offset;
        sum = MAX(sum, out_activation_min);
        sum = MIN(sum, out_activation_max);
        r4 = (q7_t)sum;

        write_q7x4_ia(&output, __PACKq7(r1, r2, r3, r4));

        loop_count--;
    }

    loop_count = block_size & 0x3;
#else
    loop_count = block_size;
#endif

    while (loop_count > 0U)
    {
        /* C = A + B */

        input_1 = (*input_1_vect++ + input_1_offset) << left_shift;
        input_2 = (*input_2_vect++ + input_2_offset) << left_shift;

        input_1 = arm_nn_doubling_high_mult(input_1, input_1_mult);
        input_1 = arm_nn_divide_by_power_of_two(input_1, -input_1_shift);

        input_2 = arm_nn_doubling_high_mult(input_2, input_2_mult);
        input_2 = arm_nn_divide_by_power_of_two(input_2, -input_2_shift);

        sum = input_1 + input_2;
        SAT_INPUT(sum, out_mult, out_shift);
        sum += out_offset;

        sum = MAX(sum, out_activation_min);
        sum = MIN(sum, out_activation_max);

        *output++ = (q7_t)sum;

        /* Decrement loop counter */
        loop_count--;
    }

#endif /* ARM_MATH_MVEI */

    return (ARM_MATH_SUCCESS);
}

/**
 * @} end of BasicMath group
 */
