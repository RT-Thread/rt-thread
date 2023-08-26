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
 * Title:        arm_nn_depthwise_conv_nt_t_padded_s8.c
 * Description:  Depthwise convolution with padded matrices.
 *
 * $Date:        09. October 2020
 * $Revision:    V.1.0.2
 *
 * Target Processor:  Cortex-M processors with MVE extension
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
 * Depthwise convolution of transposed rhs matrix with 4 lhs matrices. One or more of the rhs matrices are padded.
 * Dimensions are the same for lhs and rhs.
 *
 * Refer header file for details.
 *
 */

q7_t *arm_nn_depthwise_conv_nt_t_padded_s8(const q7_t *lhs,
                                           const q7_t *rhs,
                                           const int32_t input_offset,
                                           const uint16_t num_ch,
                                           const int32_t *out_shift,
                                           const int32_t *out_mult,
                                           const int32_t out_offset,
                                           const int32_t activation_min,
                                           const int32_t activation_max,
                                           const uint16_t row_x_col,
                                           const int32_t *const output_bias,
                                           q7_t *out)
{
#if defined(ARM_MATH_MVEI)
    int32_t loop_count = (num_ch + 3) / 4;
    const int32_t *bias = output_bias;
    uint32_t num_ch_to_process = num_ch;

    for (int i_loop_cnt = 0, offset = 0; i_loop_cnt < loop_count;
         num_ch_to_process -= 4, out += 4, offset += 4, i_loop_cnt++)
    {
        int32x4_t out_0 = vldrwq_s32(bias);
        int32x4_t out_1 = out_0;
        int32x4_t out_2 = out_0;
        int32x4_t out_3 = out_0;
        bias += 4;

        const int8_t *rhs_0 = rhs + offset;
        const int8_t *lhs_0 = lhs + offset;
        const int8_t *lhs_1 = lhs + row_x_col * num_ch + offset;
        const int8_t *lhs_2 = lhs + (row_x_col * num_ch * 2) + offset;
        const int8_t *lhs_3 = lhs + (row_x_col * num_ch * 3) + offset;

        for (int i_row_x_col = 0; i_row_x_col < row_x_col; i_row_x_col++)
        {
            const int32x4_t ker_0 = vldrbq_s32(rhs_0);

            int32x4_t ip_0 = vldrbq_s32(lhs_0);
            ip_0 = vaddq_n_s32(ip_0, input_offset);
            out_0 += vmulq_s32(ip_0, ker_0);

            int32x4_t ip_1 = vldrbq_s32(lhs_1);
            ip_1 = vaddq_n_s32(ip_1, input_offset);
            out_1 += vmulq_s32(ip_1, ker_0);

            int32x4_t ip_2 = vldrbq_s32(lhs_2);
            ip_2 = vaddq_n_s32(ip_2, input_offset);
            out_2 += vmulq_s32(ip_2, ker_0);

            int32x4_t ip_3 = vldrbq_s32(lhs_3);
            ip_3 = vaddq_n_s32(ip_3, input_offset);

            out_3 += vmulq_s32(ip_3, ker_0);

            lhs_0 += num_ch;
            lhs_1 += num_ch;
            lhs_2 += num_ch;
            lhs_3 += num_ch;

            rhs_0 += num_ch;
        }

        const int32x4_t mult = vldrwq_s32(out_mult);
        const int32x4_t shift = vldrwq_s32(out_shift);
        out_mult += 4;
        out_shift += 4;

        out_0 = arm_requantize_mve_32x4(out_0, mult, shift);
        out_0 = vaddq_n_s32(out_0, out_offset);
        out_0 = vmaxq_s32(out_0, vdupq_n_s32(activation_min));
        out_0 = vminq_s32(out_0, vdupq_n_s32(activation_max));
        mve_pred16_t p = vctp32q(num_ch_to_process);
        vstrbq_p_s32(out, out_0, p);

        out_1 = arm_requantize_mve_32x4(out_1, mult, shift);
        out_1 = vaddq_n_s32(out_1, out_offset);
        out_1 = vmaxq_s32(out_1, vdupq_n_s32(activation_min));
        out_1 = vminq_s32(out_1, vdupq_n_s32(activation_max));
        vstrbq_p_s32(out + num_ch, out_1, p);

        out_2 = arm_requantize_mve_32x4(out_2, mult, shift);
        out_2 = vaddq_n_s32(out_2, out_offset);
        out_2 = vmaxq_s32(out_2, vdupq_n_s32(activation_min));
        out_2 = vminq_s32(out_2, vdupq_n_s32(activation_max));
        vstrbq_p_s32(out + 2 * num_ch, out_2, p);

        out_3 = arm_requantize_mve_32x4(out_3, mult, shift);
        out_3 = vaddq_n_s32(out_3, out_offset);
        out_3 = vmaxq_s32(out_3, vdupq_n_s32(activation_min));
        out_3 = vminq_s32(out_3, vdupq_n_s32(activation_max));
        vstrbq_p_s32(out + 3 * num_ch, out_3, p);
    }

    const int tail_ch = num_ch & 0x3;
    if (tail_ch != 0)
    {
        out -= (4 - tail_ch);
    }
    return out + (3 * num_ch);

#else
    (void)lhs;
    (void)rhs;
    (void)input_offset;
    (void)num_ch;
    (void)out_shift;
    (void)out_mult;
    (void)out_offset;
    (void)activation_min;
    (void)activation_max;
    (void)row_x_col;
    (void)output_bias;
    (void)out;
    return NULL;
#endif
}

/**
 * @} end of NNBasicMath group
 */
