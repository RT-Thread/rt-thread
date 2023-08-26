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
 * Title:        arm_convolve_s8.c
 * Description:  s8 version of convolution using symmetric quantization.
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
 * Basic s8 convolution function.
 *
 * Refer header file for details. Optimal use case for the DSP/MVE implementation is when input and output channels
 * are multiples of 4 or atleast greater than 4.
 *
 */

arm_status arm_convolve_s8(const cmsis_nn_context *ctx,
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

    if (ctx->buf == NULL && arm_convolve_s8_get_buffer_size(input_dims, filter_dims) > 0)
    {
        return ARM_MATH_ARGUMENT_ERROR;
    }
    q15_t *buffer_a = (q15_t *)ctx->buf;

    const int32_t input_batches = input_dims->n;
    const uint16_t input_x = input_dims->w;
    const uint16_t input_y = input_dims->h;
    const uint16_t input_ch = input_dims->c;
    const uint16_t kernel_x = filter_dims->w;
    const uint16_t kernel_y = filter_dims->h;
    const uint16_t output_x = output_dims->w;
    const uint16_t output_y = output_dims->h;
    const uint16_t output_ch = output_dims->c;

    const uint16_t pad_x = conv_params->padding.w;
    const uint16_t pad_y = conv_params->padding.h;
    const uint16_t stride_x = conv_params->stride.w;
    const uint16_t stride_y = conv_params->stride.h;

    const int32_t input_offset = conv_params->input_offset;
    const int32_t out_offset = conv_params->output_offset;
    const int32_t out_activation_min = conv_params->activation.min;
    const int32_t out_activation_max = conv_params->activation.max;
    int32_t *output_mult = quant_params->multiplier;
    int32_t *output_shift = quant_params->shift;

    int i_batch;
    for (i_batch = 0; i_batch < input_batches; i_batch++)
    {
#if defined(ARM_MATH_MVEI)
        /* Generate upto four columns from the input tensor a GEMM computation */
        q7_t *im2col_buf = (q7_t *)buffer_a;
        q7_t *out = output_data;
        int32_t buffer_fill_cnt = 0;
        int32_t padded = 0;
        const int32_t num_elem = kernel_x * kernel_y * input_ch;
        const int32_t dilation_x = conv_params->dilation.w;
        const int32_t dilation_y = conv_params->dilation.h;

        /* This part implements the im2col function */
        for (int i_out_y = 0; i_out_y < output_y; i_out_y++)
        {
            for (int i_out_x = 0; i_out_x < output_x; i_out_x++)
            {
                const int32_t base_idx_x = stride_x * i_out_x - pad_x;
                const int32_t base_idx_y = stride_y * i_out_y - pad_y;

                for (int32_t i_ker_y = 0; i_ker_y < kernel_y; i_ker_y++)
                {
                    for (int32_t i_ker_x = 0; i_ker_x < kernel_x; i_ker_x++)
                    {
                        const int32_t k_y = base_idx_y + dilation_y * i_ker_y;
                        const int32_t k_x = base_idx_x + dilation_x * i_ker_x;

                        if (k_y < 0 || k_y >= input_y || k_x < 0 || k_x >= input_x)
                        {
                            memset(im2col_buf, (int8_t)-input_offset, sizeof(q7_t) * input_ch);
                            padded = 1;
                        }
                        else
                        {
                            arm_memcpy_q7(im2col_buf, input_data + (k_y * input_x + k_x) * input_ch, input_ch);
                        }
                        im2col_buf += input_ch;
                    }
                }

                buffer_fill_cnt++;

                /* Computation is filed for every 4 columns */
                if (buffer_fill_cnt == 4 && (padded == 0))
                {
                    buffer_fill_cnt = 0;
                    out = arm_nn_mat_mul_core_4x_s8(num_elem,
                                                    num_elem,
                                                    (q7_t *)buffer_a,
                                                    filter_data,
                                                    output_ch,
                                                    conv_params,
                                                    quant_params,
                                                    bias_data,
                                                    out);
                    im2col_buf = (q7_t *)buffer_a;
                }
                else if (buffer_fill_cnt == 4 && (padded != 0))
                {
                    buffer_fill_cnt = 0;
                    out = arm_nn_mat_mult_s8(filter_data,
                                             (q7_t *)buffer_a,
                                             output_ch,
                                             4,
                                             output_shift,
                                             output_mult,
                                             out_offset,
                                             input_offset,
                                             0,
                                             out_activation_min,
                                             out_activation_max,
                                             num_elem,
                                             bias_data,
                                             out);

                    im2col_buf = (q7_t *)buffer_a;
                    padded = 0;
                }
            }
        }
        /* Handle left over columns */
        if (buffer_fill_cnt != 0)
        {
            out = arm_nn_mat_mult_s8(filter_data,
                                     (q7_t *)buffer_a,
                                     output_ch,
                                     buffer_fill_cnt,
                                     output_shift,
                                     output_mult,
                                     out_offset,
                                     input_offset,
                                     0,
                                     out_activation_min,
                                     out_activation_max,
                                     num_elem,
                                     bias_data,
                                     out);
        }
#else // #if defined(ARM_MATH_MVEI)
        const uint16_t dilation_x = conv_params->dilation.w;
        const uint16_t dilation_y = conv_params->dilation.h;

        int32_t i_out_y, i_out_x, i_ker_y, i_ker_x;

        /* Generate two columns from the input tensor a GEMM computation */
        q15_t *two_column_buf = buffer_a;
        q7_t *out = output_data;

        /* This part implements the im2col function */
        for (i_out_y = 0; i_out_y < output_y; i_out_y++)
        {
            for (i_out_x = 0; i_out_x < output_x; i_out_x++)
            {
                const int32_t base_idx_y = stride_y * i_out_y - pad_y;
                const int32_t base_idx_x = stride_x * i_out_x - pad_x;

                for (i_ker_y = 0; i_ker_y < kernel_y; i_ker_y++)
                {
                    for (i_ker_x = 0; i_ker_x < kernel_x; i_ker_x++)
                    {
                        const int32_t k_y = base_idx_y + dilation_y * i_ker_y;
                        const int32_t k_x = base_idx_x + dilation_x * i_ker_x;

                        if (k_y < 0 || k_y >= input_y || k_x < 0 || k_x >= input_x)
                        {
                            /* Filling 0 for out-of-bound paddings */
                            memset(two_column_buf, 0, sizeof(q15_t) * input_ch);
                        }
                        else
                        {
                            /* Copying the pixel data to column */
                            arm_q7_to_q15_with_offset(
                                input_data + (k_y * input_x + k_x) * input_ch, two_column_buf, input_ch, input_offset);
                        }
                        two_column_buf += input_ch;
                    }
                }

                /* Computation is filed for every 2 columns */
                if (two_column_buf == buffer_a + 2 * input_ch * kernel_y * kernel_x)
                {
                    out = arm_nn_mat_mult_kernel_s8_s16(filter_data,
                                                        buffer_a,
                                                        output_ch,
                                                        output_shift,
                                                        output_mult,
                                                        out_offset,
                                                        out_activation_min,
                                                        out_activation_max,
                                                        input_ch * kernel_y * kernel_x,
                                                        bias_data,
                                                        out);

                    /* counter reset */
                    two_column_buf = buffer_a;
                }
            }
        }

        /* left-over because odd number of output pixels */
        if (two_column_buf != buffer_a)
        {
            const q7_t *ker_a = filter_data;
            int i;

            for (i = 0; i < output_ch; i++)
            {
                /* Load the accumulator with bias first */
                q31_t sum = 0;
                if (bias_data)
                {
                    sum = bias_data[i];
                }

                /* Point to the beginning of the im2col buffer where the input is available as a rearranged column */
                const q15_t *ip_as_col = buffer_a;

                /* 4 multiply and accumulates are done in one loop. */
#if defined(ARM_MATH_DSP)
                uint16_t col_count = (input_ch * kernel_y * kernel_x) >> 2;

                while (col_count)
                {
                    q31_t ker_a1, ker_a2;
                    q31_t ip_b1, ip_b2;

                    ker_a = read_and_pad(ker_a, &ker_a1, &ker_a2);

                    ip_b1 = arm_nn_read_q15x2_ia(&ip_as_col);
                    sum = __SMLAD(ker_a1, ip_b1, sum);
                    ip_b2 = arm_nn_read_q15x2_ia(&ip_as_col);
                    sum = __SMLAD(ker_a2, ip_b2, sum);

                    col_count--;
                }
                /* Handle left over mac */
                col_count = input_ch * kernel_y * kernel_x & 0x3;
#else
                uint16_t col_count = input_ch * kernel_y * kernel_x;
#endif
                while (col_count)
                {
                    q7_t ker_a1 = *ker_a++;
                    q15_t ip_b1 = *ip_as_col++;
                    sum += ker_a1 * ip_b1;
                    col_count--;
                }

                sum = arm_nn_requantize(sum, output_mult[i], output_shift[i]);
                sum += out_offset;
                sum = MAX(sum, out_activation_min);
                sum = MIN(sum, out_activation_max);
                *out++ = (q7_t)sum;
            }
        }
#endif // #if defined(ARM_MATH_MVEI)
        /* Advance to the next batch */
        input_data += (input_x * input_y * input_ch);
        output_data += (output_x * output_y * output_ch);
    }

    /* Return to application */
    return ARM_MATH_SUCCESS;
}

int32_t arm_convolve_s8_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims)
{
#if defined(ARM_MATH_MVEI)
    int32_t col_length = input_dims->c * filter_dims->w * filter_dims->h;
    // Get number of complete int16 lanes(multiple of 8) for given col_length. This is dependent on
    // implementation of  arm_nn_mat_mult_s8
    col_length = (col_length + 7) / 8;
    // 4 -> number of im2col buffers, 8 -> 8 elements per Q register
    return 4 * col_length * 8 * (int32_t)sizeof(int8_t);
#else
    return (2 * input_dims->c * filter_dims->w * filter_dims->h) * (int32_t)sizeof(int16_t);
#endif
}

/**
 * @} end of NNConv group
 */
