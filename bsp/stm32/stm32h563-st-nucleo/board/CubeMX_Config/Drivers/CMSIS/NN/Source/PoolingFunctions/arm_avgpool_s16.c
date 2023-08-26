/*
 * Copyright (C) 2022 Arm Limited or its affiliates.
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
 * Title:        arm_avgpool_s16.c
 * Description:  Pooling function implementations
 *
 * $Date:        3. February 2022
 * $Revision:    V.1.0.1
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
 * @addtogroup Pooling
 * @{
 */

/*
 * s16 average pooling function
 *
 * Refer to header file for details.
 *
 */
arm_status arm_avgpool_s16(const cmsis_nn_context *ctx,
                           const cmsis_nn_pool_params *pool_params,
                           const cmsis_nn_dims *input_dims,
                           const q15_t *src,
                           const cmsis_nn_dims *filter_dims,
                           const cmsis_nn_dims *output_dims,
                           q15_t *dst)
{
    (void)ctx;
    const int32_t input_y = input_dims->h;
    const int32_t input_x = input_dims->w;
    const int32_t output_y = output_dims->h;
    const int32_t output_x = output_dims->w;
    const int32_t stride_y = pool_params->stride.h;
    const int32_t stride_x = pool_params->stride.w;
    const int32_t kernel_y = filter_dims->h;
    const int32_t kernel_x = filter_dims->w;
    const int32_t pad_y = pool_params->padding.h;
    const int32_t pad_x = pool_params->padding.w;
    const int32_t act_min = pool_params->activation.min;
    const int32_t act_max = pool_params->activation.max;
    const int32_t ch_src = input_dims->c;

    /* Reference C code adapted from CMSIS-NN arm_avgpool_s8.c.
     */

    for (int i_y = 0, base_idx_y = -pad_y; i_y < output_y; base_idx_y += stride_y, i_y++)
    {
        for (int i_x = 0, base_idx_x = -pad_x; i_x < output_x; base_idx_x += stride_x, i_x++)
        {
            /* Condition for kernel start dimension: (base_idx_<x,y> + kernel_<x,y>_start) >= 0 */
            const int32_t ker_y_start = MAX(0, -base_idx_y);
            const int32_t ker_x_start = MAX(0, -base_idx_x);

            /* Condition for kernel end dimension: (base_idx_<x,y> + kernel_<x,y>_end) < dim_src_<width,height> */
            const int32_t kernel_y_end = MIN(kernel_y, input_y - base_idx_y);
            const int32_t kernel_x_end = MIN(kernel_x, input_x - base_idx_x);

            for (int i_ch_in = 0; i_ch_in < ch_src; i_ch_in++)
            {
                int sum = 0;
                int count = 0;

                for (int k_y = ker_y_start; k_y < kernel_y_end; k_y++)
                {
                    for (int k_x = ker_x_start; k_x < kernel_x_end; k_x++)
                    {
                        sum += src[i_ch_in + ch_src * (k_x + base_idx_x + (k_y + base_idx_y) * input_x)];
                        count++;
                    }
                }

                // Prevent static code issue DIVIDE_BY_ZERO.
                if (count == 0)
                {
                    return ARM_MATH_ARGUMENT_ERROR;
                }

                sum = sum > 0 ? (sum + count / 2) / count : (sum - count / 2) / count;
                sum = MAX(sum, act_min);
                sum = MIN(sum, act_max);

                dst[i_ch_in + ch_src * (i_x + i_y * output_x)] = sum;
            }
        }
    }

    return ARM_MATH_SUCCESS;
}

int32_t arm_avgpool_s16_get_buffer_size(const int output_x, const int ch_src)
{
    (void)output_x;
    (void)ch_src;
    return 0;
}

/**
 * @} end of Pooling group
 */
