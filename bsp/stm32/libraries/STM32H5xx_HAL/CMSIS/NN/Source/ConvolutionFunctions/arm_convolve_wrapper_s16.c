/*
 * Copyright (C) 2021-2022 Arm Limited or its affiliates. All rights reserved.
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
 * Title:        arm_convolve_wrapper_s16.c
 * Description:  s16 convolution layer wrapper function with the main purpose to call the optimal kernel available in
 * cmsis-nn to perform the convolution.
 *
 * $Date:        13 January 2022
 * $Revision:    V.1.2.0
 *
 * Target Processor:  Cortex-M cores
 *
 * -------------------------------------------------------------------- */

#include "arm_nnfunctions.h"

/**
 *  @ingroup groupNN
 */

/**
 * @addtogroup NNConv
 * @{
 */

/*
 * Convolution layer
 *
 * Refer header file for details.
 *
 */

arm_status arm_convolve_wrapper_s16(const cmsis_nn_context *ctx,
                                    const cmsis_nn_conv_params *conv_params,
                                    const cmsis_nn_per_channel_quant_params *quant_params,
                                    const cmsis_nn_dims *input_dims,
                                    const q15_t *input_data,
                                    const cmsis_nn_dims *filter_dims,
                                    const q7_t *filter_data,
                                    const cmsis_nn_dims *bias_dims,
                                    const int64_t *bias_data,
                                    const cmsis_nn_dims *output_dims,
                                    q15_t *output_data)
{
#if defined(ARM_MATH_DSP) && !defined(ARM_MATH_MVEI)
    if (filter_dims->w * filter_dims->h * input_dims->c < 512 &&
        (conv_params->dilation.w == 1 && conv_params->dilation.h == 1))
    {
        return arm_convolve_fast_s16(ctx,
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
    }
    else
    {
        return arm_convolve_s16(ctx,
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
    }
#else
    return arm_convolve_s16(ctx,
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
}

int32_t arm_convolve_wrapper_s16_get_buffer_size(const cmsis_nn_conv_params *conv_params,
                                                 const cmsis_nn_dims *input_dims,
                                                 const cmsis_nn_dims *filter_dims,
                                                 const cmsis_nn_dims *output_dims)
{
    (void)conv_params;
    (void)output_dims;

#if defined(ARM_MATH_DSP) && !defined(ARM_MATH_MVEI)
    if (filter_dims->w * filter_dims->h * input_dims->c < 512 &&
        (conv_params->dilation.w == 1 && conv_params->dilation.h == 1))
    {
        return arm_convolve_fast_s16_get_buffer_size(input_dims, filter_dims);
    }

    return arm_convolve_s16_get_buffer_size(input_dims, filter_dims);
#else
    return arm_convolve_s16_get_buffer_size(input_dims, filter_dims);
#endif
}

/**
 * @} end of NNConv group
 */
