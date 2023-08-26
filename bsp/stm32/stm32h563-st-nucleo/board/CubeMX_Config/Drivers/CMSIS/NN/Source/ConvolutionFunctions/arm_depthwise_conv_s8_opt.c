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
 * Title:        arm_depthwise_conv_s8_opt.c
 * Description:  Optimized s8 depthwise separable convolution function for
 *               channel multiplier of 1.
 *
 * $Date:        January 26, 2021
 * $Revision:    V.2.0.3
 *
 * Target Processor:  Cortex-M CPUs
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
 * Optimized s8 depthwise convolution function with constraint that in_channel equals out_channel
 *
 *  Refer prototype header file for details.
 *
 */

arm_status arm_depthwise_conv_s8_opt(const cmsis_nn_context *ctx,
                                     const cmsis_nn_dw_conv_params *dw_conv_params,
                                     const cmsis_nn_per_channel_quant_params *quant_params,
                                     const cmsis_nn_dims *input_dims,
                                     const q7_t *input,
                                     const cmsis_nn_dims *filter_dims,
                                     const q7_t *kernel,
                                     const cmsis_nn_dims *bias_dims,
                                     const int32_t *bias,
                                     const cmsis_nn_dims *output_dims,
                                     q7_t *output)
{

    const int32_t input_ch = input_dims->c;
    const int32_t output_ch = output_dims->c;

    /* Check input constraints input_ch == output_ch */
    if (input_ch != output_ch)
    {
        return ARM_MATH_SIZE_MISMATCH;
    }

    if (ctx->buf == NULL && arm_depthwise_conv_s8_opt_get_buffer_size(input_dims, filter_dims) > 0)
    {
        return ARM_MATH_ARGUMENT_ERROR;
    }
#ifdef ARM_MATH_DSP
    const int32_t input_x = input_dims->w;
    const int32_t input_y = input_dims->h;
    const int32_t kernel_x = filter_dims->w;
    const int32_t kernel_y = filter_dims->h;
    const int32_t pad_x = dw_conv_params->padding.w;
    const int32_t pad_y = dw_conv_params->padding.h;
    const int32_t stride_x = dw_conv_params->stride.w;
    const int32_t stride_y = dw_conv_params->stride.h;
    const int32_t *output_shift = quant_params->shift;
    const int32_t *output_mult = quant_params->multiplier;
    const int32_t output_x = output_dims->w;
    const int32_t output_y = output_dims->h;
    const int32_t output_offset = dw_conv_params->output_offset;
    const int32_t input_offset = dw_conv_params->input_offset;
    const int32_t output_activation_min = dw_conv_params->activation.min;
    const int32_t output_activation_max = dw_conv_params->activation.max;
    q15_t *buffer_a = (q15_t *)ctx->buf;

#ifdef ARM_MATH_MVEI
    (void)bias_dims;
    /* Generate two columns from the input tensor */
    q7_t *lhs_buffer = (q7_t *)buffer_a;
    q7_t *out = output;
    int padded = 0;
    int buffer_count = 0;
    const int32_t kernel_size = kernel_x * kernel_y;

    /* This part implements the im2col function */
    for (int i_out_y = 0, base_idx_y = -pad_y; i_out_y < output_y; base_idx_y += stride_y, i_out_y++)
    {
        for (int i_out_x = 0, base_idx_x = -pad_x; i_out_x < output_x; base_idx_x += stride_x, i_out_x++)
        {
            for (int i_ker_y = base_idx_y; i_ker_y < base_idx_y + kernel_y; i_ker_y++)
            {
                for (int i_ker_x = base_idx_x; i_ker_x < base_idx_x + kernel_x; i_ker_x++)
                {
                    if (i_ker_y < 0 || i_ker_y >= input_y || i_ker_x < 0 || i_ker_x >= input_x)
                    {
                        arm_memset_q7(lhs_buffer, (int8_t)-input_offset, (uint32_t)input_ch);
                        padded = 1;
                    }
                    else
                    {
                        arm_memcpy_q7(lhs_buffer, input + (i_ker_y * input_x + i_ker_x) * input_ch, (uint32_t)input_ch);
                    }
                    lhs_buffer += input_ch;
                }
            }
            buffer_count++;

            if (buffer_count == 4)
            {
                lhs_buffer = (q7_t *)buffer_a;
                if (padded == 0)
                {
                    out = arm_nn_depthwise_conv_nt_t_s8(lhs_buffer,
                                                        kernel,
                                                        input_offset,
                                                        input_ch,
                                                        output_shift,
                                                        output_mult,
                                                        output_offset,
                                                        output_activation_min,
                                                        output_activation_max,
                                                        kernel_size,
                                                        bias,
                                                        out);
                }
                else
                {
                    out = arm_nn_depthwise_conv_nt_t_padded_s8(lhs_buffer,
                                                               kernel,
                                                               input_offset,
                                                               input_ch,
                                                               output_shift,
                                                               output_mult,
                                                               output_offset,
                                                               output_activation_min,
                                                               output_activation_max,
                                                               kernel_size,
                                                               bias,
                                                               out);
                    padded = 0;
                }
                buffer_count = 0;
            }
        }
    }

    /* Handle left over buffers */
    lhs_buffer = (q7_t *)buffer_a;

    for (int i_buf = 0; i_buf < buffer_count; i_buf++)
    {
        int32_t loop_count = (input_ch + 3) / 4;

        int32_t num_ch_to_process = input_ch;
        for (int i_loop_cnt = 0, offset = 0; i_loop_cnt < loop_count; num_ch_to_process -= 4, offset += 4, i_loop_cnt++)
        {
            const int8_t *col_0 = lhs_buffer + (kernel_size * input_ch * i_buf) + offset;
            const int8_t *row_0 = kernel + offset;
            int32x4_t out_0 = vldrwq_s32(&bias[offset]);

            for (int i_ker = 0; i_ker < kernel_size; i_ker++)
            {
                const int32x4_t ker_0 = vldrbq_s32(row_0);

                int32x4_t ip_0 = vldrbq_s32(col_0);
                ip_0 = vaddq_n_s32(ip_0, input_offset);
                out_0 += vmulq_s32(ip_0, ker_0);

                col_0 += input_ch;
                row_0 += input_ch;
            }

            const int32x4_t mult = vldrwq_s32(&output_mult[offset]);
            const int32x4_t shift = vldrwq_s32(&output_shift[offset]);

            out_0 = arm_requantize_mve_32x4(out_0, mult, shift);
            out_0 = vaddq_n_s32(out_0, output_offset);
            out_0 = vmaxq_s32(out_0, vdupq_n_s32(output_activation_min));
            out_0 = vminq_s32(out_0, vdupq_n_s32(output_activation_max));
            mve_pred16_t p = vctp32q((uint32_t)num_ch_to_process);
            vstrbq_p_s32(out, out_0, p);

            out += 4;
        }

        const int tail_ch = input_ch & 0x3;
        if (tail_ch != 0)
        {
            out -= (4 - tail_ch);
        }
    }

#else // ARM_MATH_DSP
    (void)bias_dims;
    /* Run the following code in cores using DSP extension */
    q15_t *const col_buffer_start = buffer_a;
    q15_t *col_buffer = col_buffer_start;
    const int32_t *const bias_start_pos = bias;
    const q31_t *const out_mult_start_pos = output_mult;
    const q31_t *const out_shift_start_pos = output_shift;
    uint16_t row_count;
    uint16_t row_shift;

    for (int i_out_y = 0; i_out_y < output_y; i_out_y++)
    {
        const int16_t base_idx_y = (i_out_y * stride_y) - pad_y;
        for (int i_out_x = 0; i_out_x < output_x; i_out_x++)
        {
            const int16_t base_idx_x = (i_out_x * stride_x) - pad_x;

            /* Out of bounds is only considered for the y axis as it provides a contiguous zero'ing opportunity than
               along the x axis */
            const int ker_y_start = MAX(0, -base_idx_y);
            /* Condition for kernel end dimension: (base_idx_y + ker_y_end) < input_y */
            const int ker_y_end = MIN(kernel_y, input_y - base_idx_y);

            int32_t index = 0;
            if (ker_y_start != 0)
            {
                memset(&col_buffer[index], 0, (kernel_x * input_ch) * ker_y_start * sizeof(q15_t));
                index += (kernel_x * input_ch) * ker_y_start;
            }

            for (int i_ker_y = ker_y_start; i_ker_y < ker_y_end; i_ker_y++)
            {
                const int32_t idx_y = base_idx_y + i_ker_y;

                for (int i_ker_x = 0; i_ker_x < kernel_x; i_ker_x++)
                {
                    const int32_t idx_x = base_idx_x + i_ker_x;
                    if (idx_x < 0 || idx_x >= input_x)
                    {
                        memset(&col_buffer[index], 0, input_ch * sizeof(q15_t));
                    }
                    else
                    {
                        arm_q7_to_q15_with_offset((q7_t *)input + (idx_y * input_x + idx_x) * input_ch,
                                                  &col_buffer[index],
                                                  input_ch,
                                                  input_offset);
                    }
                    index += input_ch;
                }
            }

            const int diff = kernel_y - ker_y_end;
            if (diff != 0)
            {
                memset(&col_buffer[index], 0, (kernel_x * input_ch) * diff * sizeof(q15_t));
            }

            row_count = output_ch / 4;
            row_shift = 0;
            bias = bias_start_pos;
            output_mult = out_mult_start_pos;
            output_shift = out_shift_start_pos;

            while (row_count)
            {
                q31_t sum = *bias++;
                q31_t sum_2 = *bias++;
                q31_t sum_3 = *bias++;
                q31_t sum_4 = *bias++;

                uint16_t col_count = (kernel_x * kernel_y) / 2;
                q15_t *col_pos = col_buffer_start + row_shift;
                const q7_t *row_pos = kernel + row_shift;
                row_shift += 4;

                while (col_count)
                {
                    /* General idea is to read 4 + 4 (input, kernel) pair and re-arrange them in the right order to
                    use in a SMLAD instruction . One run of this loop produces 4 partial outputs with 8 MACs. */
                    /* Note: variable names can be improved here to align with rows and columns. */
                    q31_t ip_a1, ip_a2, ip_b1, ip_b2, op_a, op_b, op_c;
                    /* Read 4 weights */
                    ip_b1 = arm_nn_read_q7x4(row_pos);
                    ip_a1 = arm_nn_read_q7x4(row_pos + input_ch);
                    op_a = arm_nn_read_q15x2(col_pos);
                    op_b = arm_nn_read_q15x2(col_pos + input_ch);

                    ip_a2 = __SXTB16(ip_b1);
                    ip_b1 = __SXTB16(__ROR(ip_b1, 8));

                    ip_b2 = __SXTB16(ip_a1);
                    ip_a1 = __SXTB16(__ROR(ip_a1, 8));

                    op_c = __PKHBT(op_b, op_a, 16);
                    op_a = __PKHTB(op_b, op_a, 16);
                    op_b = __PKHBT(ip_b2, ip_a2, 16);
                    sum = __SMLAD(op_c, op_b, sum);

                    op_b = __PKHBT(ip_b1, ip_a1, 16);
                    sum_2 = __SMLAD(op_a, op_b, sum_2);

                    op_a = arm_nn_read_q15x2(col_pos + 2);
                    op_b = arm_nn_read_q15x2(col_pos + input_ch + 2);

                    op_c = __PKHBT(op_b, op_a, 16);
                    op_a = __PKHTB(op_b, op_a, 16);
                    op_b = __PKHTB(ip_a2, ip_b2, 16);
                    sum_3 = __SMLAD(op_c, op_b, sum_3);

                    op_b = __PKHTB(ip_a1, ip_b1, 16);
                    sum_4 = __SMLAD(op_a, op_b, sum_4);

                    row_pos += input_ch << 1;
                    col_pos += input_ch << 1;
                    col_count--;
                }

                col_count = (kernel_x * kernel_y) & 0x1;
                while (col_count)
                {
                    sum += row_pos[0] * col_pos[0];
                    sum_2 += row_pos[1] * col_pos[1];
                    sum_3 += row_pos[2] * col_pos[2];
                    sum_4 += row_pos[3] * col_pos[3];

                    row_pos += input_ch;
                    col_pos += input_ch;

                    col_count--;
                }
                sum = arm_nn_requantize(sum, *output_mult++, *output_shift++);
                sum += output_offset;
                sum = MAX(sum, output_activation_min);
                sum = MIN(sum, output_activation_max);
                *output++ = (q7_t)sum;

                sum_2 = arm_nn_requantize(sum_2, *output_mult++, *output_shift++);
                sum_2 += output_offset;
                sum_2 = MAX(sum_2, output_activation_min);
                sum_2 = MIN(sum_2, output_activation_max);
                *output++ = (q7_t)sum_2;
                sum_3 = arm_nn_requantize(sum_3, *output_mult++, *output_shift++);
                sum_3 += output_offset;
                sum_3 = MAX(sum_3, output_activation_min);
                sum_3 = MIN(sum_3, output_activation_max);
                *output++ = (q7_t)sum_3;

                sum_4 = arm_nn_requantize(sum_4, *output_mult++, *output_shift++);
                sum_4 += output_offset;
                sum_4 = MAX(sum_4, output_activation_min);
                sum_4 = MIN(sum_4, output_activation_max);
                *output++ = (q7_t)sum_4;

                row_count--;
            }

            row_count = output_ch & 0x3;
            while (row_count)
            {
                q15_t *col_pos = col_buffer_start + row_shift;
                const q7_t *row_pos = kernel + row_shift;
                q31_t sum = *bias++;
                const uint16_t col_count = (kernel_x * kernel_y);
                row_shift += 1;

                for (int i = 0; i < col_count; i++)
                {
                    sum += row_pos[i * input_ch] * col_pos[i * input_ch];
                }
                sum = arm_nn_requantize(sum, *output_mult++, *output_shift++);
                sum += output_offset;
                sum = MAX(sum, output_activation_min);
                sum = MIN(sum, output_activation_max);
                *output++ = (q7_t)sum;

                row_count--;
            }

            // clear counter and pointers
            col_buffer = col_buffer_start;
        }
    }
#endif
#else
    /* Run the following code as reference implementation for Cortex-M0 and Cortex-M3 */
    return arm_depthwise_conv_s8(ctx,
                                 dw_conv_params,
                                 quant_params,
                                 input_dims,
                                 input,
                                 filter_dims,
                                 kernel,
                                 bias_dims,
                                 bias,
                                 output_dims,
                                 output);
#endif /* ARM_MATH_MVEI | ARM_MATH_DSP */

    /* Return to application */
    return ARM_MATH_SUCCESS;
}

int32_t arm_depthwise_conv_s8_opt_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims)
{
#if defined(ARM_MATH_MVEI)
    /* The + 4 accounts for out of bounds read of the lhs buffers in the *_nt_t_* functions.  */
    return (2 * input_dims->c * filter_dims->w * filter_dims->h) * (int32_t)sizeof(int16_t) + 4;
#elif defined(ARM_MATH_DSP)
    return (input_dims->c * filter_dims->w * filter_dims->h) * sizeof(int16_t);
#else
    (void)input_dims;
    (void)filter_dims;
    return 0;
#endif
}

/**
 * @} end of NNConv group
 */
