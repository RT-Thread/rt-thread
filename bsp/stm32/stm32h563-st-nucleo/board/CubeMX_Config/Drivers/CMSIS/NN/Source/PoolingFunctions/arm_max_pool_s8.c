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
 * Title:        arm_max_pool_s8.c
 * Description:  Pooling function implementations
 *
 * $Date:        20. July 2021
 * $Revision:    V.2.0.3
 *
 * Target Processor:  Cortex-M CPUs
 *
 * -------------------------------------------------------------------- */

#include "arm_nnfunctions.h"
#include "arm_nnsupportfunctions.h"

static void compare_and_replace_if_larger_q7(q7_t *base, const q7_t *target, int32_t length)
{
#if defined(ARM_MATH_MVEI)
    int32_t loop_count = (length + 15) / 16;
    for (int i = 0; i < loop_count; i++)
    {
        mve_pred16_t p = vctp8q((uint32_t)length);
        const int8x16_t op_1 = vldrbq_z_s8(base, p);
        const int8x16_t op_2 = vldrbq_z_s8(target, p);
        const int8x16_t max = vmaxq_m_s8(vuninitializedq_s8(), op_1, op_2, p);
        vstrbq_p_s8(base, max, p);
        base += 16;
        target += 16;
        length -= 16;
    }
#else
    q7_t *dst = base;
    const q7_t *src = target;
    union arm_nnword ref_max;
    union arm_nnword comp_max;
    int32_t cnt = length >> 2;

    while (cnt > 0l)
    {
        ref_max.word = arm_nn_read_q7x4(dst);
        comp_max.word = arm_nn_read_q7x4_ia(&src);

        if (comp_max.bytes[0] > ref_max.bytes[0])
        {
            ref_max.bytes[0] = comp_max.bytes[0];
        }
        if (comp_max.bytes[1] > ref_max.bytes[1])
        {
            ref_max.bytes[1] = comp_max.bytes[1];
        }
        if (comp_max.bytes[2] > ref_max.bytes[2])
        {
            ref_max.bytes[2] = comp_max.bytes[2];
        }
        if (comp_max.bytes[3] > ref_max.bytes[3])
        {
            ref_max.bytes[3] = comp_max.bytes[3];
        }

        arm_nn_write_q7x4_ia(&dst, ref_max.word);

        cnt--;
    }

    cnt = length & 0x3;
    while (cnt > 0l)
    {
        if (*src > *dst)
        {
            *dst = *src;
        }
        dst++;
        src++;
        cnt--;
    }
#endif
}

static void clamp_output(q7_t *source, int32_t length, const int32_t act_min, const int32_t act_max)
{
#if defined(ARM_MATH_MVEI)
    int32_t loop_count = (length + 15) / 16;
    for (int i = 0; i < loop_count; i++)
    {
        mve_pred16_t p = vctp8q((uint32_t)length);
        length -= 16;
        const int8x16_t src = vldrbq_z_s8(source, p);
        const int8x16_t predicated_min = vdupq_m_n_s8(vuninitializedq_s8(), (int8_t)act_min, p);
        const int8x16_t predicated_max = vdupq_m_n_s8(vuninitializedq_s8(), (int8_t)act_max, p);
        int8x16_t res = vmaxq_m_s8(vuninitializedq_s8(), src, predicated_min, p);
        res = vminq_m_s8(vuninitializedq_s8(), res, predicated_max, p);
        vstrbq_p_s8(source, res, p);
        source += 16;
    }
#else
    union arm_nnword in;
    int32_t cnt = length >> 2;

    while (cnt > 0l)
    {
        in.word = arm_nn_read_q7x4(source);

        in.bytes[0] = MAX(in.bytes[0], act_min);
        in.bytes[0] = MIN(in.bytes[0], act_max);
        in.bytes[1] = MAX(in.bytes[1], act_min);
        in.bytes[1] = MIN(in.bytes[1], act_max);
        in.bytes[2] = MAX(in.bytes[2], act_min);
        in.bytes[2] = MIN(in.bytes[2], act_max);
        in.bytes[3] = MAX(in.bytes[3], act_min);
        in.bytes[3] = MIN(in.bytes[3], act_max);

        arm_nn_write_q7x4_ia(&source, in.word);
        cnt--;
    }

    cnt = length & 0x3;
    while (cnt > 0l)
    {
        int32_t comp = *source;
        comp = MAX(comp, act_min);
        comp = MIN(comp, act_max);
        *source++ = (int8_t)comp;
        cnt--;
    }
#endif
}

/**
 *  @ingroup groupNN
 */

/**
 * @addtogroup Pooling
 * @{
 */

/*
 * Optimized s8 max pooling function
 *
 * Refer to header file for details.
 *
 */

arm_status arm_max_pool_s8(const cmsis_nn_context *ctx,
                           const cmsis_nn_pool_params *pool_params,
                           const cmsis_nn_dims *input_dims,
                           const q7_t *src,
                           const cmsis_nn_dims *filter_dims,
                           const cmsis_nn_dims *output_dims,
                           q7_t *dst)
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
    const int32_t act_min = pool_params->activation.min;
    const int32_t act_max = pool_params->activation.max;
    const int32_t channel_in = input_dims->c;
    (void)ctx;
    q7_t *dst_base = dst;

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
                    const q7_t *start = src + channel_in * (k_x + base_idx_x + (k_y + base_idx_y) * input_x);

                    if (count == 0)
                    {
                        arm_memcpy_q7(dst, start, channel_in);
                        count++;
                    }
                    else
                    {
                        compare_and_replace_if_larger_q7(dst, start, channel_in);
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
