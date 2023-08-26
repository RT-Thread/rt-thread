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
 * Title:        arm_convolve_wrapper_s8.c
 * Description:  s8 convolution layer wrapper function with the main purpose to call the optimal kernel available in
 * cmsis-nn to perform the convolution.
 *
 * $Date:        02. December 2021
 * $Revision:    V.1.1.0
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

arm_status arm_convolve_wrapper_s8(const cmsis_nn_context *ctx,
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
    if ((conv_params->padding.w == 0) && (conv_params->padding.h == 0) && (input_dims->c % 4 == 0) &&
        (conv_params->stride.w == 1) && (conv_params->stride.h == 1) && (filter_dims->w == 1) &&
        (filter_dims->h == 1) && (conv_params->dilation.w == 1 && conv_params->dilation.h == 1))
    {
        return arm_convolve_1x1_s8_fast(ctx,
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
    else if ((output_dims->h == 1) && (input_dims->h == 1) && (filter_dims->h == 1) && (output_dims->w % 4 == 0) &&
             (input_dims->n == 1) && (conv_params->dilation.w == 1 && conv_params->dilation.h == 1))
    {
        return arm_convolve_1_x_n_s8(ctx,
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
        return arm_convolve_s8(ctx,
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
}

int32_t arm_convolve_wrapper_s8_get_buffer_size(const cmsis_nn_conv_params *conv_params,
                                                const cmsis_nn_dims *input_dims,
                                                const cmsis_nn_dims *filter_dims,
                                                const cmsis_nn_dims *output_dims)
{
    if ((conv_params->padding.w == 0) && (conv_params->padding.h == 0) && (input_dims->c % 4 == 0) &&
        (conv_params->stride.w == 1) && (conv_params->stride.h == 1) && (filter_dims->w == 1) &&
        (filter_dims->h == 1) && (conv_params->dilation.w == 1 && conv_params->dilation.h == 1))
    {
        return arm_convolve_1x1_s8_fast_get_buffer_size(input_dims);
    }
    else if ((output_dims->h == 1) && (input_dims->h == 1) && (filter_dims->h == 1) && (output_dims->w % 4 == 0) &&
             (input_dims->n == 1) && (conv_params->dilation.w == 1 && conv_params->dilation.h == 1))
    {
        return arm_convolve_1_x_n_s8_get_buffer_size(input_dims, filter_dims);
    }
    else
    {
        return arm_convolve_s8_get_buffer_size(input_dims, filter_dims);
    }
}

/**
 * @} end of NNConv group
 */
