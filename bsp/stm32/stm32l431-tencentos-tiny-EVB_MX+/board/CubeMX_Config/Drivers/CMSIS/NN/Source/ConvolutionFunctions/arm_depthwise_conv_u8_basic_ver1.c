/*
 * Copyright (C) 2010-2019 Arm Limited or its affiliates. All rights reserved.
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
 * Title:        arm_depthwise_conv_u8_basic_ver1.c
 * Description:  u8 depthwise convolution function
 *
 * $Date:        June, 2019
 * $Revision:    V.0.8.0
 *
 * Target :  Cortex-M cores with DSP extension
 *
 * -------------------------------------------------------------------- */

#include "arm_math.h"
#include "arm_nnfunctions.h"
#include <stdint.h>
#include <stdio.h>

#define DILATION_X (1)
#define DILATION_Y (1)

/**
 *  @ingroup groupNN
 */

/**
 * @addtogroup NNConv
 * @{
 */

/**
 * @brief uint8 depthwise convolution function with asymmetric quantization for even number of channel multiplier
 *        and input channels. Unless specified otherwise, arguments are mandatory. Both square and non-square inputs
 *        are accepted.
 *
 * @param[in]     input     Pointer to input tensor
 * @param[in]     input_x   Width of input tensor
 * @param[in]     input_y   Height of input tensor
 * @param[in]     input_ch  Channels in input tensor
 * @param[in]     kernel    Pointer to kernel weights
 * @param[in]     kernel_x  Width of kernel
 * @param[in]     kernel_y  Height of kernel
 * @param[in]     ch_mult   Number of channel multiplier
 * @param[in]     pad_x     Padding sizes x
 * @param[in]     pad_y     Padding sizes y
 * @param[in]     stride_x  Convolution stride along the width
 * @param[in]     stride_y  Convolution stride along the height
 * @param[in]     dilation_x Dilation along width. Not used and intended for future enhancement.
 * @param[in]     dilation_y Dilation along height. Not used and intended for future enhancement.
 * @param[in]     bias       Pointer to optional bias values. If no bias is
 *                           availble, NULL is expected
 * @param[in]     input_offset  Input tensor zero offset
 * @param[in]     filter_offset Kernel tensor zero offset
 * @param[in]     output_offset Output tensor zero offset
 * @param[in,out] output        Pointer to output tensor
 * @param[in]     output_x  Width of output tensor
 * @param[in]     output_y  Height of output tensor
 * @param[in]     output_activation_min   Minimum value to clamp the output to. Range : {0, 255}
 * @param[in]     output_activation_max   Minimum value to clamp the output to. Range : {0, 255}
 * @param[in]     out_shift  Amount of right-shift for output
 * @param[in]     out_mult   Output multiplier for requantization
 * @return        The function returns one of the following
 *                <code>ARM_MATH_SIZE_MISMATCH</code> - Not supported dimension of tensors
 *                <code>ARM_MATH_SUCCESS</code> - Successful operation
 *                <code>ARM_MATH_ARGUMENT_ERROR</code> - Implementation not available
 *
 * <b> Input constraints</b>
 * ch_mult  is multiple of 2
 * kernel_x is multiple of 2
 *
 */

arm_status arm_depthwise_conv_u8_basic_ver1(const uint8_t *input,
                                            const uint16_t input_x,
                                            const uint16_t input_y,
                                            const uint16_t input_ch,
                                            const uint8_t *kernel,
                                            const uint16_t kernel_x,
                                            const uint16_t kernel_y,
                                            const int16_t ch_mult,
                                            const int16_t pad_x,
                                            const int16_t pad_y,
                                            const int16_t stride_x,
                                            const int16_t stride_y,
                                            const int16_t dilation_x,
                                            const int16_t dilation_y,
                                            const int32_t *bias,
                                            const int32_t input_offset,
                                            const int32_t filter_offset,
                                            const int32_t output_offset,
                                            uint8_t *output,
                                            const uint16_t output_x,
                                            const uint16_t output_y,
                                            const int32_t output_activation_min,
                                            const int32_t output_activation_max,
                                            const int32_t out_shift,
                                            const int32_t out_mult)
{
    arm_status status = ARM_MATH_SUCCESS;
 #if defined (ARM_MATH_DSP)
    int i_out = 0;
    (void)dilation_x;
    (void)dilation_y;

    const int32_t input_offset_pkd = (input_offset & 0xFFFF) | (input_offset & 0xFFFF) << 16;
    const int32_t kernel_offset_pkd = (filter_offset & 0xFFFF) | (filter_offset & 0xFFFF) << 16;

    if (0 != ch_mult % 2 || 0 != kernel_x % 2)
    {
        return ARM_MATH_SIZE_MISMATCH;
    }

    for (int i_out_y = 0; i_out_y < output_y; i_out_y++)
    {
        const int16_t base_idx_y = (i_out_y * stride_y) - pad_y;
        for (int i_out_x = 0; i_out_x < output_x; i_out_x++)
        {
            const int16_t base_idx_x = (i_out_x * stride_x) - pad_x;
            for (int i_input_ch = 0; i_input_ch < input_ch; i_input_ch++)
            {
                for (int i_ch_mult = 0; i_ch_mult < ch_mult; i_ch_mult += 2)
                {
                    const int idx_out_ch = i_ch_mult + i_input_ch * ch_mult;

                    int32_t acc_0 = 0;
                    int32_t acc_1 = 0;
                    if (NULL != bias)
                    {
                        acc_0 = bias[idx_out_ch];
                        acc_1 = bias[idx_out_ch + 1];
                    }

                    for (int i_ker_y = 0; i_ker_y < kernel_y; i_ker_y++)
                    {
                        const int32_t idx_y = base_idx_y + DILATION_Y * i_ker_y;
                        const int32_t y_in_range = (idx_y >= 0) && (idx_y < input_y);

                        for (int i_ker_x = 0; i_ker_x < kernel_x; i_ker_x += 2)
                        {
                            if (1 == y_in_range)
                            {
                                const int32_t idx_x = base_idx_x + DILATION_X * i_ker_x;
                                const int32_t idx_x1 = base_idx_x + DILATION_X * (i_ker_x + 1);
                                /* Range check for first input */
                                if (idx_x >= 0 && idx_x < input_x)
                                {
                                    const int32_t idx_0 = (idx_y * input_x + idx_x) * input_ch + i_input_ch;

                                    const int32_t ker_idx_0 =
                                        (i_ker_y * kernel_x + i_ker_x) * (input_ch * ch_mult) + idx_out_ch;
                                    const int32_t ker_idx_1 = ker_idx_0 + input_ch * ch_mult;

                                    int32_t input_pkd = input[idx_0] | (input[idx_0 + input_ch] << 16);
                                    int32_t kernel_pkd = kernel[ker_idx_0] | (kernel[ker_idx_1] << 16);

                                    input_pkd = __SADD16(input_pkd, input_offset_pkd);
                                    kernel_pkd = __SADD16(kernel_pkd, kernel_offset_pkd);
                                    /* Range check for second input */
                                    if (idx_x1 >= input_x)
                                    {
                                        input_pkd &= 0xFFFF;
                                    }
                                    acc_0 = __SMLAD(input_pkd, kernel_pkd, acc_0);

                                    kernel_pkd = kernel[ker_idx_0 + 1] | (kernel[ker_idx_1 + 1] << 16);
                                    kernel_pkd = __SADD16(kernel_pkd, kernel_offset_pkd);
                                    acc_1 = __SMLAD(input_pkd, kernel_pkd, acc_1);
                                }
                            }
                        }
                    }

                    /* Requantize and clamp output to provided range */
                    acc_0 = arm_nn_divide_by_power_of_two(arm_nn_sat_doubling_high_mult(
                                                              acc_0 * (1 << LEFT_SHIFT(out_shift)), out_mult),
                                                          RIGHT_SHIFT(out_shift));

                    acc_0 += output_offset;

                    if (output_activation_min > acc_0)
                    {
                        acc_0 = output_activation_min;
                    }

                    if (acc_0 > output_activation_max)
                    {
                        acc_0 = output_activation_max;
                    }
                    output[i_out++] = acc_0;

                    /* Requantize and clamp output to provided range */
                    acc_1 = arm_nn_divide_by_power_of_two(arm_nn_sat_doubling_high_mult(
                                                              acc_1 * (1 << LEFT_SHIFT(out_shift)), out_mult),
                                                          RIGHT_SHIFT(out_shift));
                    acc_1 += output_offset;

                    if (output_activation_min > acc_1)
                    {
                        acc_1 = output_activation_min;
                    }

                    if (acc_1 > output_activation_max)
                    {
                        acc_1 = output_activation_max;
                    }
                    output[i_out++] = acc_1;
                }
            }
        }
    }
#else
    /* No available implementation. */
    status = ARM_MATH_ARGUMENT_ERROR;
#endif
    return status;
}

/**
 * @} end of NNConv group
 */


