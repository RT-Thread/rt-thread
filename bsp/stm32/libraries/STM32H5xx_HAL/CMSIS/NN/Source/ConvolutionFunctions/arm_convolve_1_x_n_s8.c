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
 * Title:        arm_convolve_1_x_n_s8.c
 * Description:  s8 version of 1xN convolution using symmetric quantization.
 *
 * $Date:        December 14, 2021
 * $Revision:    V.2.1.0
 *
 * Target Processor:  Cortex-M cores
 *
 * -------------------------------------------------------------------- */

#include "arm_nnfunctions.h"
#include "arm_nnsupportfunctions.h"

/**
 *  @ingroup groupNN
 */

/**
 * @addtogroup NNConv
 * @{
 */

/*
 * 1xN s8 convolution function.
 *
 * Refer header file for details.
 *
 */

arm_status arm_convolve_1_x_n_s8(const cmsis_nn_context *ctx,
                                 const cmsis_nn_conv_params *conv_params,
                                 const cmsis_nn_per_channel_quant_params *quant_params,
                                 const cmsis_nn_dims *input_dims,
                                 const q7_t *input_data,
                                 const cmsis_nn_dims *filter_dims,
                                 const q7_t *filter_data,
                                 const cmsis_nn_dims *bias_dims,
                                 const int32_t *bias_data,
                                 const cmsis_nn_dims *output_dims,
                                 q7_t *output_data)
{
    (void)bias_dims;
    arm_status status = ARM_MATH_SUCCESS;
    if (output_dims->w % 4 != 0)
    {
        status = ARM_MATH_SIZE_MISMATCH;
        goto out;
    }

#if defined(ARM_MATH_MVEI)
    (void)ctx;

    const uint16_t input_x = input_dims->w;
    const uint16_t kernel_x = filter_dims->w;
    const uint16_t output_x = output_dims->w;
    const uint16_t output_ch = output_dims->c;
    const uint16_t input_ch = input_dims->c;
    const uint16_t pad_x = conv_params->padding.w;
    const uint16_t stride_x = conv_params->stride.w;

    const int32_t input_offset = conv_params->input_offset;
    const int32_t out_offset = conv_params->output_offset;
    const int32_t out_activation_min = conv_params->activation.min;
    const int32_t out_activation_max = conv_params->activation.max;
    int32_t *output_mult = quant_params->multiplier;
    int32_t *output_shift = quant_params->shift;

    for (int i_out_x = 0; i_out_x <= (output_x - 4); i_out_x += 4)
    {
        int32_t input_begin_idx[4];
        int32_t ker_begin_idx[4];
        int32_t ker_end_idx[4];

        for (int i = 0; i < 4; i++)
        {
            const int32_t est_input_x_idx = stride_x * (i_out_x + i) - pad_x;
            input_begin_idx[i] = MAX(0, est_input_x_idx);
            ker_begin_idx[i] = MAX(0, -est_input_x_idx);
            ker_end_idx[i] = MIN(kernel_x, input_x - est_input_x_idx);
        }

        if ((ker_begin_idx[0] != 0) || (ker_end_idx[3] != kernel_x))
        {
            for (int i_out_ch = 0; i_out_ch < output_ch; i_out_ch++)
            {
                int32x4_t s_offset;
                int32_t acc[4];
                {
                    int32_t sum_row[4];

                    (void)arm_nn_mat_mul_core_1x_s8((ker_end_idx[0] - ker_begin_idx[0]) * input_ch,
                                                    input_data + input_begin_idx[0] * input_ch,
                                                    filter_data + (input_ch * kernel_x * i_out_ch) +
                                                        (ker_begin_idx[0] * input_ch),
                                                    &sum_row[0],
                                                    &acc[0]);
                    (void)arm_nn_mat_mul_core_1x_s8((ker_end_idx[1] - ker_begin_idx[1]) * input_ch,
                                                    input_data + input_begin_idx[1] * input_ch,
                                                    filter_data + (input_ch * kernel_x * i_out_ch) +
                                                        (ker_begin_idx[1] * input_ch),
                                                    &sum_row[1],
                                                    &acc[1]);

                    (void)arm_nn_mat_mul_core_1x_s8((ker_end_idx[2] - ker_begin_idx[2]) * input_ch,
                                                    input_data + input_begin_idx[2] * input_ch,
                                                    filter_data + (input_ch * kernel_x * i_out_ch) +
                                                        (ker_begin_idx[2] * input_ch),
                                                    &sum_row[2],
                                                    &acc[2]);

                    (void)arm_nn_mat_mul_core_1x_s8((ker_end_idx[3] - ker_begin_idx[3]) * input_ch,
                                                    input_data + input_begin_idx[3] * input_ch,
                                                    filter_data + (input_ch * kernel_x * i_out_ch) +
                                                        (ker_begin_idx[3] * input_ch),
                                                    &sum_row[3],
                                                    &acc[3]);

                    s_offset = vldrwq_s32(sum_row);
                }
                int32x4_t res = vldrwq_s32(acc);
                s_offset = vmulq_n_s32(s_offset, input_offset);
                res = vaddq_s32(res, s_offset);
                if (bias_data)
                {
                    res = vaddq_n_s32(res, bias_data[i_out_ch]);
                }
                res = arm_requantize_mve(res, output_mult[i_out_ch], output_shift[i_out_ch]);
                res = vaddq_n_s32(res, out_offset);

                res = vmaxq_s32(res, vdupq_n_s32(out_activation_min));
                res = vminq_s32(res, vdupq_n_s32(out_activation_max));

                const uint32x4_t scatter_offset = {0, output_ch, output_ch * 2, output_ch * 3};
                vstrbq_scatter_offset_s32(output_data, scatter_offset, res);
                output_data++;
            }
            output_data += (3 * output_ch);
        }
        else
        {
            output_data = arm_nn_mat_mul_core_4x_s8(kernel_x * input_ch,
                                                    stride_x * input_ch,
                                                    input_data + input_begin_idx[0] * input_ch,
                                                    filter_data,
                                                    output_ch,
                                                    conv_params,
                                                    quant_params,
                                                    bias_data,
                                                    output_data);
        }
    }

#else
    status = arm_convolve_s8(ctx,
                             conv_params,
                             quant_params,
                             input_dims,
                             input_data,
                             filter_dims,
                             filter_data,
                             bias_dims,
                             bias_data,
                             output_dims,
                             output_data);
#endif

out:
    /* Return to application */
    return status;
}

int32_t arm_convolve_1_x_n_s8_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims)
{
#if !defined(ARM_MATH_MVEI)
    return (2 * input_dims->c * filter_dims->w * filter_dims->h) * sizeof(int16_t);
#else
    (void)input_dims;
    (void)filter_dims;
    return 0;
#endif
}

/**
 * @} end of NNConv group
 */
