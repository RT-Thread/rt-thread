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
 * Title:        arm_max_pool_s16.c
 * Description:  Pooling function implementations
 *
 * $Date:        24. January 2022
 * $Revision:    V.1.0.0
 *
 * Target Processor:  Cortex-M CPUs
 *
 * -------------------------------------------------------------------- */

#include "arm_nnfunctions.h"
#include "arm_nnsupportfunctions.h"

static void compare_and_replace_if_larger(int16_t *base, const int16_t *target, int32_t length)
{
    q15_t *dst = base;
    const q15_t *src = target;
    union arm_nnword ref_max;
    union arm_nnword comp_max;
    int32_t cnt = length >> 1;

    while (cnt > 0l)
    {
        ref_max.word = arm_nn_read_q15x2(dst);
        comp_max.word = arm_nn_read_q15x2_ia(&src);

        if (comp_max.half_words[0] > ref_max.half_words[0])
        {
            ref_max.half_words[0] = comp_max.half_words[0];
        }
        if (comp_max.half_words[1] > ref_max.half_words[1])
        {
            ref_max.half_words[1] = comp_max.half_words[1];
        }

        arm_nn_write_q15x2_ia(&dst, ref_max.word);

        cnt--;
    }

    if (length & 0x1)
    {
        if (*src > *dst)
        {
            *dst = *src;
        }
    }
}

static void clamp_output(int16_t *source, int32_t length, const int16_t act_min, const int16_t act_max)
{
    union arm_nnword in;
    int32_t cnt = length >> 1;

    while (cnt > 0l)
    {
        in.word = arm_nn_read_q15x2(source);

        in.half_words[0] = MAX(in.half_words[0], act_min);
        in.half_words[0] = MIN(in.half_words[0], act_max);
        in.half_words[1] = MAX(in.half_words[1], act_min);
        in.half_words[1] = MIN(in.half_words[1], act_max);

        arm_nn_write_q15x2_ia(&source, in.word);
        cnt--;
    }

    if (length & 0x1)
    {
        int16_t comp = *source;
        comp = MAX(comp, act_min);
        comp = MIN(comp, act_max);
        *source = comp;
    }
}

/**
 *  @ingroup groupNN
 */

/**
 * @addtogroup Pooling
 * @{
 */

/*
 * Optimized s16 max pooling function
 *
 * Refer to header file for details.
 *
 */

arm_status arm_max_pool_s16(const cmsis_nn_context *ctx,
                            const cmsis_nn_pool_params *pool_params,
                            const cmsis_nn_dims *input_dims,
                            const int16_t *src,
                            const cmsis_nn_dims *filter_dims,
                            const cmsis_nn_dims *output_dims,
                            int16_t *dst)
{
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
    const int16_t act_min = pool_params->activation.min;
    const int16_t act_max = pool_params->activation.max;
    const int32_t channel_in = input_dims->c;
    (void)ctx;
    int16_t *dst_base = dst;

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

            int count = 0;

            for (int k_y = ker_y_start; k_y < kernel_y_end; k_y++)
            {
                for (int k_x = ker_x_start; k_x < kernel_x_end; k_x++)
                {
                    const int16_t *start = src + channel_in * (k_x + base_idx_x + (k_y + base_idx_y) * input_x);

                    if (count == 0)
                    {
                        memcpy(dst, start, channel_in * sizeof(int16_t));
                        count++;
                    }
                    else
                    {
                        compare_and_replace_if_larger(dst, start, channel_in);
                    }
                }
            }
            /* 'count' is expected to be non-zero here. */
            dst += channel_in;
        }
    }

    clamp_output(dst_base, output_x * output_y * channel_in, act_min, act_max);

    return ARM_MATH_SUCCESS;
}

/**
 * @} end of Pooling group
 */
