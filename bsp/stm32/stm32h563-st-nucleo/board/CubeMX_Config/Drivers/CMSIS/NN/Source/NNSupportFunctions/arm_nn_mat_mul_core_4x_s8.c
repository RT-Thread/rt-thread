/*
 * Copyright (C) 2010-2022 Arm Limited or its affiliates.
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
 * Title:        arm_nn_mat_mul_core_4x_s8.c
 * Description:  General matrix multiplication function for MVE extension
 *
 * $Date:        19. April 2022
 * $Revision:    V.3.0.1
 *
 * Target Processor:  Cortex-M processors
 * -------------------------------------------------------------------- */
#include "arm_nn_types.h"
#include "arm_nnsupportfunctions.h"
/**
 * @ingroup groupSupport
 */

/**
 * @addtogroup NNBasicMath
 * @{
 */

/*
 * s8 matrix multiplication to process 4 rows and one column
 *
 * Refer header file for details.
 *
 */

int8_t *arm_nn_mat_mul_core_4x_s8(const int32_t row_elements,
                                  const int32_t offset,
                                  const int8_t *row_base,
                                  const int8_t *col_base_ref,
                                  const int32_t out_ch,
                                  const cmsis_nn_conv_params *conv_params,
                                  const cmsis_nn_per_channel_quant_params *quant_params,
                                  const int32_t *bias,
                                  int8_t *output)
{

#if defined(ARM_MATH_MVEI)
    for (int i = 0; i < out_ch; i++)
    {
        int32_t acc_n0 = 0;
        int32_t acc_n1 = 0;
        int32_t acc_n2 = 0;
        int32_t acc_n3 = 0;

        const int8_t *ip_row_0 = row_base;
        const int8_t *ip_row_1 = row_base + offset;
        const int8_t *ip_row_2 = row_base + (2 * offset);
        const int8_t *ip_row_3 = row_base + (3 * offset);
        const int8_t *col_base = col_base_ref + i * row_elements;
        int32_t sum_tmp = 0;

        __ASM volatile("   vldrb.8         q0, [%[col]], #16     \n"
                       "   wlstp.8         lr, %[cnt], 1f       \n"
                       "2:                                      \n"
                       "   vaddva.s8      %[sum], q0            \n"
                       "   vldrb.8         q1, [%[row0]], #16    \n"
                       "   vmladava.s8    %[out0], q0, q1       \n"
                       "   vldrb.8         q2, [%[row1]], #16    \n"
                       "   vmladava.s8     %[out1], q0, q2      \n"
                       "   vldrb.8         q3, [%[row2]], #16    \n"
                       "   vmladava.s8     %[out2], q0, q3      \n"
                       "   vldrb.8         q4, [%[row3]], #16    \n"
                       "   vmladava.s8     %[out3], q0, q4      \n"
                       "   vldrb.8         q0, [%[col]], #16     \n"
                       "   letp            lr, 2b               \n"
                       "1:                                      \n"
                       : [col] "+r"(col_base),
                         [sum] "+Te"(sum_tmp),
                         [row0] "+r"(ip_row_0),
                         [row1] "+r"(ip_row_1),
                         [row2] "+r"(ip_row_2),
                         [row3] "+r"(ip_row_3),
                         [out0] "+Te"(acc_n0),
                         [out1] "+Te"(acc_n1),
                         [out2] "+Te"(acc_n2),
                         [out3] "+Te"(acc_n3)
                       : [cnt] "r"(row_elements)
                       : "q0", "q1", "q2", "q3", "q4", "memory", "r14");

        int32x4_t res = {acc_n0, acc_n1, acc_n2, acc_n3};
        sum_tmp *= conv_params->input_offset;
        if (bias)
        {
            sum_tmp += bias[i];
        }
        res = vaddq_n_s32(res, sum_tmp);

        res = arm_requantize_mve(res, quant_params->multiplier[i], quant_params->shift[i]);
        res = vaddq_n_s32(res, conv_params->output_offset);

        res = vmaxq_s32(res, vdupq_n_s32(conv_params->activation.min));
        res = vminq_s32(res, vdupq_n_s32(conv_params->activation.max));

        const uint32x4_t scatter_offset = {0, (uint32_t)out_ch, (uint32_t)out_ch * 2, (uint32_t)out_ch * 3};
        vstrbq_scatter_offset_s32(output, scatter_offset, res);
        output++;
    }

    return output + (3 * out_ch);
#else
    (void)row_elements;
    (void)offset;
    (void)row_base;
    (void)col_base_ref;
    (void)out_ch;
    (void)conv_params;
    (void)quant_params;
    (void)bias;
    (void)output;
    return NULL;
#endif
}

/**
 * @} end of NNBasicMath group
 */
