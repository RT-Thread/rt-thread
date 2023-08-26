/*
 * Copyright (C) 2022 Arm Limited or its affiliates.
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
 * Title:        arm_softmax_s16.c
 * Description:  S16 softmax function
 *
 * $Date:        9 March 2022
 * $Revision:    V.1.0.0
 *
 * Target Processor:  Cortex-M cores
 *
 * -------------------------------------------------------------------- */

#include "arm_nnfunctions.h"
#include "arm_nnsupportfunctions.h"

/**
 * @addtogroup Softmax
 * @{
 */

arm_status arm_softmax_s16(const int16_t *input,
                           const int32_t num_rows,
                           const int32_t row_size,
                           const int32_t mult,
                           const int32_t shift,
                           const cmsis_nn_softmax_lut_s16 *softmax_params,
                           int16_t *output)
{
    int32_t col = 0;
    int32_t row_idx;

    if (softmax_params->exp_lut == NULL || softmax_params->one_by_one_lut == NULL)
    {
        return ARM_MATH_ARGUMENT_ERROR;
    }

    for (row_idx = 0; row_idx < num_rows; ++row_idx)
    {
        // Find the maximum value in order to ensure numerical stability
        int16_t max = *input;
        for (col = 1; col < row_size; ++col)
        {
            max = MAX(max, input[col]);
        }

        int32_t diff = 0;
        int32_t sum = 0;
        int16_t *cached_exp_results = output;

        for (col = 0; col < row_size; ++col)
        {
            diff = input[col] - max;
            const int32_t scaled_diff = arm_nn_requantize(diff, mult, shift);
            const int32_t symmetric_scaled_diff = scaled_diff + NN_Q15_MAX;
            const int16_t saturated_symmetric_scaled_diff = MIN(MAX(symmetric_scaled_diff, NN_Q15_MIN), NN_Q15_MAX);

            // Lookup from exp table and cache result for next step
            const int16_t index = (256 + (saturated_symmetric_scaled_diff >> 7));
            const int16_t offset = saturated_symmetric_scaled_diff & 0x7f;
            const int16_t base = softmax_params->exp_lut[index];
            const int16_t slope = softmax_params->exp_lut[index + 1] - softmax_params->exp_lut[index];
            const int16_t delta = (slope * offset + 64) >> 7;
            const int16_t result = (base + delta);
            cached_exp_results[col] = result;

            sum += cached_exp_results[col];
        }

        const int32_t headroom = __CLZ(sum);

        // Compute the reciprocal 1/sum
        const int32_t shifted_sum = (((sum) << (headroom - 1)) + (1 << 13)) >> 14;

        // Since LUT computes 1/(1 + x), compute x = (sum - 1) => -65536
        // Since LUT expects a symmetrical input, recenter from [UINT16_MIN, UINT16_MAX] to [INT16_MIN, INT16_MAX] =>
        // -32768 ==> So in total -65536 -32768 => -98304
        const int16_t symmetric_shifted_sum = shifted_sum - 98304;

        // Lookup from one by one table
        const int16_t index = (256 + (symmetric_shifted_sum >> 7));
        const int16_t offset = symmetric_shifted_sum & 0x7f;
        const int16_t base = softmax_params->one_by_one_lut[index];
        const int16_t slope = softmax_params->one_by_one_lut[index + 1] - softmax_params->one_by_one_lut[index];
        const int16_t delta = (slope * offset + 64) >> 7;
        const int16_t one_by_one_result = (base + delta);

        for (col = 0; col < row_size; ++col)
        {
            const int16_t right_shift = 30 - headroom;
            int32_t result = (cached_exp_results[col] * one_by_one_result) >> right_shift;
            result = (result + 1) >> 1; // Last shift position and insert round
            output[col] = (int16_t)result;
        }

        output += row_size;
        input += row_size;
    }

    return ARM_MATH_SUCCESS;
}

/**
 * @} end of Softmax group
 */
