/*
 * Copyright (C) 2010-2021 Arm Limited or its affiliates.
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
 * Title:        arm_nn_mat_mult_s8.c
 * Description:  General Matrix-multiplication function
 *
 * $Date:        27. October 2021
 * $Revision:    V.2.0.6
 *
 * Target Processor:  Cortex-M cores
 * -------------------------------------------------------------------- */

#include "arm_nnsupportfunctions.h"

/*
 * s8 General matrix multiplication function with per-channel requantization for upto 4 column batches.
 *
 * Refer header file for details.
 *
 */

q7_t *arm_nn_mat_mult_s8(const q7_t *input_row,
                         const q7_t *input_col,
                         const uint16_t output_ch,
                         const uint16_t col_batches,
                         const int32_t *output_shift,
                         const int32_t *output_mult,
                         const int32_t out_offset,
                         const int32_t col_offset,
                         const int32_t row_offset,
                         const int16_t activation_min,
                         const int16_t activation_max,
                         const uint16_t row_len,
                         const int32_t *const bias,
                         q7_t *out)
{
#if defined(ARM_MATH_MVEI)
    (void)row_offset;
    if (col_batches == 4)
    {
        for (int i_out_ch = 0; i_out_ch < output_ch; i_out_ch++)
        {
            int32_t row_len_tmp = row_len;
            const int8_t *ip_r0 = input_row + (i_out_ch * row_len);
            const int8_t *ip_c0 = input_col;
            const int8_t *ip_c1 = input_col + row_len;
            const int8_t *ip_c2 = input_col + (2 * row_len);
            const int8_t *ip_c3 = input_col + (3 * row_len);

            int32_t acc_0 = 0;
            int32_t acc_1 = 0;
            int32_t acc_2 = 0;
            int32_t acc_3 = 0;
            const int32_t row_loop_cnt = (row_len + 7) / 8;

            for (int i_row_loop = 0; i_row_loop < row_loop_cnt; i_row_loop++)
            {
                mve_pred16_t p = vctp16q((uint32_t)row_len_tmp);
                const int16x8_t offset = vdupq_m_n_s16(vuninitializedq_s16(), col_offset, p);
                row_len_tmp -= 8;

                int16x8_t c0 = vldrbq_s16(ip_c0);
                ip_c0 += 8;
                c0 = vaddq_s16(c0, offset);

                int16x8_t c1 = vldrbq_s16(ip_c1);
                ip_c1 += 8;
                c1 = vaddq_s16(c1, offset);

                int16x8_t c2 = vldrbq_s16(ip_c2);
                ip_c2 += 8;
                c2 = vaddq_s16(c2, offset);

                int16x8_t c3 = vldrbq_s16(ip_c3);
                ip_c3 += 8;
                c3 = vaddq_s16(c3, offset);

                int16x8_t r0 = vldrbq_z_s16(ip_r0, p);
                ip_r0 += 8;

                acc_0 = vmladavaq_p_s16(acc_0, r0, c0, p);
                acc_1 = vmladavaq_p_s16(acc_1, r0, c1, p);
                acc_2 = vmladavaq_p_s16(acc_2, r0, c2, p);
                acc_3 = vmladavaq_p_s16(acc_3, r0, c3, p);
            }

            int32x4_t res = {acc_0, acc_1, acc_2, acc_3};
            if (bias)
            {
                res = vaddq_n_s32(res, bias[i_out_ch]);
            }
            res = arm_requantize_mve(res, output_mult[i_out_ch], output_shift[i_out_ch]);
            res = vaddq_n_s32(res, out_offset);

            res = vmaxq_s32(res, vdupq_n_s32(activation_min));
            res = vminq_s32(res, vdupq_n_s32(activation_max));

            const uint32x4_t scatter_offset = {0, output_ch, output_ch * 2, output_ch * 3};
            vstrbq_scatter_offset_s32(&out[i_out_ch], scatter_offset, res);
        }
        out += 4 * output_ch;
    }
    else
    {
        for (int i_col_batch = (col_batches & ~0x3); i_col_batch < (col_batches & 0x3); i_col_batch++)
        {
            for (int i_out_ch = 0; i_out_ch < output_ch; i_out_ch++)
            {
                int32_t row_len_tmp = row_len;

                const int8_t *ip_r0 = input_row + (i_out_ch * row_len);
                const int8_t *ip_c0 = input_col + (i_col_batch * row_len);
                int32_t acc_0 = 0;
                const int32_t row_loop_cnt = (row_len + 7) / 8;

                for (int i_row_loop = 0; i_row_loop < row_loop_cnt; i_row_loop++)
                {
                    const mve_pred16_t p = vctp16q((uint32_t)row_len_tmp);
                    const int16x8_t offset = vdupq_m_n_s16(vuninitializedq_s16(), col_offset, p);
                    row_len_tmp -= 8;

                    int16x8_t c0 = vldrbq_s16(ip_c0);
                    ip_c0 += 8;
                    c0 = vaddq_s16(c0, offset);

                    int16x8_t r0 = vldrbq_z_s16(ip_r0, p);
                    ip_r0 += 8;
                    acc_0 = vmladavaq_p_s16(acc_0, r0, c0, p);
                }

                if (bias)
                {
                    acc_0 += bias[i_out_ch];
                }
                acc_0 = arm_nn_requantize(acc_0, output_mult[i_out_ch], output_shift[i_out_ch]);
                acc_0 += out_offset;
                acc_0 = MAX(acc_0, activation_min);
                acc_0 = MIN(acc_0, activation_max);
                out[i_out_ch] = (q7_t)acc_0;
            }
            out += output_ch;
        }
    }
    return out;

#else
    (void)input_row;
    (void)input_col;
    (void)output_ch;
    (void)col_batches;
    (void)output_shift;
    (void)output_mult;
    (void)out_offset;
    (void)col_offset;
    (void)row_offset;
    (void)activation_min;
    (void)activation_max;
    (void)row_len;
    (void)bias;
    (void)out;
    return NULL;
#endif
}
