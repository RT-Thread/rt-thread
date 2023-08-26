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
 * Title:        arm_nn_depthwise_conv_s8_core.c
 * Description:  Depthwise convolution on im2col buffers.
 *
 * $Date:        09. October 2020
 * $Revision:    V.1.0.4
 *
 * Target Processor:  Cortex-M cores
 * -------------------------------------------------------------------- */

#include "arm_nnsupportfunctions.h"

/*
 * Depthwise conv on an im2col buffer where the input channel equals
 * output channel.
 *
 * Refer header file for details.
 *
 */

q7_t *arm_nn_depthwise_conv_s8_core(const q7_t *row,
                                    const q15_t *col,
                                    const uint16_t num_ch,
                                    const int32_t *out_shift,
                                    const int32_t *out_mult,
                                    const int32_t out_offset,
                                    const int32_t activation_min,
                                    const int32_t activation_max,
                                    const uint16_t kernel_size,
                                    const int32_t *const output_bias,
                                    q7_t *out)
{
#if defined(ARM_MATH_MVEI)
    int32_t ch_per_loop = num_ch / 4;

    const int32_t *bias = output_bias;
    int8_t *out_tmp = out;

    int32_t idx = 0;

    while (ch_per_loop > 0)
    {
        int32x4_t ip_0;
        int32x4_t ip_1;
        int32_t ker_loop = kernel_size / 3;
        int32x4_t out_0 = vldrwq_s32(bias);
        int32x4_t out_1 = out_0;
        bias += 4;

        const int32_t offset = idx * 4;
        const int8_t *row_0 = row + offset;
        const int16_t *col_0 = col + offset;
        const int16_t *col_1 = col + kernel_size * num_ch + offset;

        int32x4_t ker_0 = vldrbq_s32(row_0);

        while (ker_loop > 0)
        {
            const int8_t *row_1 = row_0 + num_ch;
            const int8_t *row_2 = row_0 + 2 * num_ch;
            const int32x4_t ker_1 = vldrbq_s32(row_1);
            const int32x4_t ker_2 = vldrbq_s32(row_2);

            ip_0 = vldrhq_s32(col_0);
            ip_1 = vldrhq_s32(col_1);
            col_0 += num_ch;
            col_1 += num_ch;

            out_0 += vmulq_s32(ip_0, ker_0);
            out_1 += vmulq_s32(ip_1, ker_0);

            ip_0 = vldrhq_s32(col_0);
            ip_1 = vldrhq_s32(col_1);
            col_0 += num_ch;
            col_1 += num_ch;

            out_0 += vmulq_s32(ip_0, ker_1);
            out_1 += vmulq_s32(ip_1, ker_1);

            ip_0 = vldrhq_s32(col_0);
            ip_1 = vldrhq_s32(col_1);
            col_0 += num_ch;
            col_1 += num_ch;

            out_0 += vmulq_s32(ip_0, ker_2);
            out_1 += vmulq_s32(ip_1, ker_2);
            row_0 += 3 * num_ch;

            ker_0 = vldrbq_s32(row_0);
            ker_loop--;
        }

        idx++;
        /* Handle tail kernel elements */
        ker_loop = kernel_size - ((kernel_size / 3) * 3);
        while (ker_loop > 0)
        {
            ip_0 = vldrhq_s32(col_0);
            ip_1 = vldrhq_s32(col_1);

            out_0 += vmulq_s32(ip_0, ker_0);
            out_1 += vmulq_s32(ip_1, ker_0);

            col_0 += num_ch;
            col_1 += num_ch;

            ip_0 = vldrhq_s32(col_0);
            ip_1 = vldrhq_s32(col_1);

            row_0 += num_ch;
            ker_0 = vldrbq_s32(row_0);
            ker_loop--;
        }
        const int32x4_t mult = vldrwq_s32(out_mult);
        const int32x4_t shift = vldrwq_s32(out_shift);
        out_mult += 4;
        out_shift += 4;

        out_0 = arm_requantize_mve_32x4(out_0, mult, shift);
        out_1 = arm_requantize_mve_32x4(out_1, mult, shift);

        out_0 = vaddq_n_s32(out_0, out_offset);
        out_0 = vmaxq_s32(out_0, vdupq_n_s32(activation_min));
        out_0 = vminq_s32(out_0, vdupq_n_s32(activation_max));
        vstrbq_s32(out_tmp, out_0);

        out_1 = vaddq_n_s32(out_1, out_offset);
        out_1 = vmaxq_s32(out_1, vdupq_n_s32(activation_min));
        out_1 = vminq_s32(out_1, vdupq_n_s32(activation_max));
        vstrbq_s32(out_tmp + num_ch, out_1);

        out_tmp += 4;
        ch_per_loop--;
    }

    int32_t tail_ch = num_ch & 3;
    if (tail_ch != 0)
    {
        int32_t ch_idx = (num_ch & ~3);
        int32x4_t col_0_sum;
        int32x4_t col_1_sum;

        const int32_t single_buffer_size = kernel_size * num_ch;
        for (int i = 0; i < tail_ch; i++)
        {
            const int16_t *col_pos_0 = col + ch_idx;
            const int16_t *col_pos_1 = col_pos_0 + single_buffer_size;

            const int8_t *row_pos = row + ch_idx;
            int32_t sum_0 = bias[i];
            int32_t sum_1 = bias[i];

            for (int j = 0; j < kernel_size; j++)
            {
                const int8_t row_val = row_pos[j * num_ch];
                sum_0 += row_val * col_pos_0[j * num_ch];
                sum_1 += row_val * col_pos_1[j * num_ch];
            }
            col_0_sum[i] = sum_0;
            col_1_sum[i] = sum_1;

            ch_idx++;
        }
        const mve_pred16_t p = vctp32q((uint32_t)tail_ch);
        const int32x4_t mult = vldrwq_z_s32(out_mult, p);
        const int32x4_t shift = vldrwq_z_s32(out_shift, p);

        col_0_sum = arm_requantize_mve_32x4(col_0_sum, mult, shift);
        col_1_sum = arm_requantize_mve_32x4(col_1_sum, mult, shift);

        col_0_sum = vaddq_n_s32(col_0_sum, out_offset);
        col_0_sum = vmaxq_s32(col_0_sum, vdupq_n_s32(activation_min));
        col_0_sum = vminq_s32(col_0_sum, vdupq_n_s32(activation_max));
        vstrbq_p_s32(out_tmp, col_0_sum, p);

        col_1_sum = vaddq_n_s32(col_1_sum, out_offset);
        col_1_sum = vmaxq_s32(col_1_sum, vdupq_n_s32(activation_min));
        col_1_sum = vminq_s32(col_1_sum, vdupq_n_s32(activation_max));
        vstrbq_p_s32(out_tmp + num_ch, col_1_sum, p);

        out_tmp += tail_ch;
    }

    return out_tmp + num_ch;
#else
    (void)row;
    (void)col;
    (void)num_ch;
    (void)out_shift;
    (void)out_mult;
    (void)out_offset;
    (void)activation_min;
    (void)activation_max;
    (void)kernel_size;
    (void)output_bias;
    (void)out;
    return NULL;
#endif
}
