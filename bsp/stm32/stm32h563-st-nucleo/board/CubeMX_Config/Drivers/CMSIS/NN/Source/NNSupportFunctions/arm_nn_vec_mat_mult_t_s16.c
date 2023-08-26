/*
 * Copyright (C) 2020-2022 Arm Limited or its affiliates.
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
 * Title:        arm_nn_vec_mat_mult_t_s16
 * Description:  s16 vector by matrix (transposed) multiplication
 *
 * $Date:        04. January 2022
 * $Revision:    V.1.2.0
 *
 * Target Processor:  Cortex-M
 *
 * -------------------------------------------------------------------- */

#include "arm_nnsupportfunctions.h"
/**
 * @ingroup groupSupport
 */

/**
 * @addtogroup NNBasicMath
 * @{
 */

/*
 * s16 vector(lhs) by matrix (transposed) multiplication
 *
 * Refer header file for details.
 *
 */
arm_status arm_nn_vec_mat_mult_t_s16(const q15_t *lhs,
                                     const q7_t *rhs,
                                     const q63_t *bias,
                                     q15_t *dst,
                                     const int32_t dst_multiplier,
                                     const int32_t dst_shift,
                                     const int32_t rhs_cols,
                                     const int32_t rhs_rows,
                                     const int32_t activation_min,
                                     const int32_t activation_max)
{
#if defined(ARM_MATH_DSP) && !defined(ARM_MATH_MVEI)
    const int32_t row_loop_cnt = rhs_rows / 2;

    int32_t rhs_cols_fast = rhs_cols;

    if (rhs_cols > 512)
    {
        rhs_cols_fast = 512;
    }

    for (int32_t i = 0; i < row_loop_cnt; i++)
    {
        q63_t acc_64_0 = 0;
        q63_t acc_64_1 = 0;
        int32_t acc_0 = 0;
        int32_t acc_1 = 0;

        const int32_t col_loop_cnt = rhs_cols_fast / 4;

        const int16_t *lhs_vec = lhs;
        const int8_t *rhs_0 = rhs;
        const int8_t *rhs_1 = rhs + rhs_cols;
        rhs += 2 * rhs_cols;

        for (int j = col_loop_cnt; j != 0; j--)
        {
            int32_t ker_0, ker_1, vec_part_0, vec_part_1;
            vec_part_0 = arm_nn_read_q15x2_ia(&lhs_vec);
            vec_part_1 = arm_nn_read_q15x2_ia(&lhs_vec);

            rhs_0 = read_and_pad(rhs_0, &ker_0, &ker_1);

            acc_0 = __SMLAD(ker_0, vec_part_0, acc_0);
            acc_0 = __SMLAD(ker_1, vec_part_1, acc_0);

            rhs_1 = read_and_pad(rhs_1, &ker_0, &ker_1);

            acc_1 = __SMLAD(ker_0, vec_part_0, acc_1);
            acc_1 = __SMLAD(ker_1, vec_part_1, acc_1);
        }

        acc_64_0 += acc_0;
        acc_64_1 += acc_1;

        for (int k = col_loop_cnt * 4; k < rhs_cols; k++)
        {
            const int32_t lhs_temp = (*lhs_vec);
            lhs_vec++;
            acc_64_0 += lhs_temp * (*rhs_0);
            rhs_0++;
            acc_64_1 += lhs_temp * (*rhs_1);
            rhs_1++;
        }

        if (bias)
        {
            acc_64_0 += *bias++;
            acc_64_1 += *bias++;
        }
        q31_t tmp;
        tmp = arm_nn_requantize_s64(acc_64_0, dst_multiplier, dst_shift);
        tmp = MAX(tmp, activation_min);
        tmp = MIN(tmp, activation_max);
        *dst++ = (q15_t)tmp;

        tmp = arm_nn_requantize_s64(acc_64_1, dst_multiplier, dst_shift);
        tmp = MAX(tmp, activation_min);
        tmp = MIN(tmp, activation_max);
        *dst++ = (q15_t)tmp;
    }

    if (rhs_rows & 0x1)
    {
        q63_t acc_64_0 = 0;
        int32_t acc_0 = 0;
        const int32_t col_loop_cnt = rhs_cols_fast / 4;

        const int16_t *lhs_vec = lhs;
        const int8_t *rhs_0 = rhs;

        for (int i = col_loop_cnt; i != 0; i--)
        {
            int32_t ker_0, ker_1, vec;
            rhs_0 = read_and_pad(rhs_0, &ker_0, &ker_1);

            vec = arm_nn_read_q15x2_ia(&lhs_vec);
            acc_0 = __SMLAD(ker_0, vec, acc_0);

            vec = arm_nn_read_q15x2_ia(&lhs_vec);
            acc_0 = __SMLAD(ker_1, vec, acc_0);
        }

        acc_64_0 += acc_0;

        for (int j = col_loop_cnt * 4; j < rhs_cols; j++)
        {
            const int32_t lhs_temp = (*lhs_vec);
            lhs_vec++;
            acc_64_0 += lhs_temp * (*rhs_0);
            rhs_0++;
        }

        if (bias)
        {
            acc_64_0 += *bias++;
        }
        q31_t tmp;
        tmp = arm_nn_requantize_s64(acc_64_0, dst_multiplier, dst_shift);
        tmp = MAX(tmp, activation_min);
        tmp = MIN(tmp, activation_max);
        *dst++ = (q15_t)tmp;
    }

#else
    for (int i_row_loop_cnt = 0; i_row_loop_cnt < rhs_rows; i_row_loop_cnt++)
    {
        const q15_t *lhs_ptr = lhs;
        const q7_t *rhs_ptr_0 = &rhs[0];

        q63_t result = 0;

        if (bias)
        {
            result = *bias++;
        }
        for (int32_t rhs_cols_idx = 0; rhs_cols_idx < rhs_cols; ++rhs_cols_idx)
        {
            const q63_t rhs_value0 = (int8_t)*rhs_ptr_0;
            const q63_t lhs_value = *lhs_ptr;

            result += lhs_value * rhs_value0;

            ++rhs_ptr_0;
            ++lhs_ptr;
        }

        // Quantize down
        result = arm_nn_requantize_s64(result, dst_multiplier, dst_shift);

        // Clamp the result
        result = ((result) > (activation_min) ? (result) : (activation_min));
        result = ((result) < (activation_max) ? (result) : (activation_max));

        *dst++ = (q15_t)result;
        rhs += rhs_cols;
    }
#endif

    return ARM_MATH_SUCCESS;
}

/**
 * @} end of NNBasicMath group
 */
