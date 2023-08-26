/*
 * Copyright (C) 2010-2020 Arm Limited or its affiliates. All rights reserved.
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
 * Title:        arm_softmax_s8.c
 * Description:  S8 softmax function
 *
 * $Date:        01. March 2021
 * $Revision:    V.2.0.2
 *
 * Target Processor:  Cortex-M cores
 *
 * -------------------------------------------------------------------- */

#include "arm_nnfunctions.h"
#include "arm_nnsupportfunctions.h"

#define ACCUM_BITS 12

#ifdef ARM_MATH_MVEI
static int32x4_t arm_exp_on_negative_values_mve_32x4(int32x4_t val)
{
#define SHIFT_START (24)
    int32_t shift = SHIFT_START;
    int32x4_t mask;

    const int32x4_t val_mod_minus_quarter =
        vandq_s32(val, vdupq_n_s32((1 << SHIFT_START) - 1)) - vdupq_n_s32(1 << SHIFT_START);
    const int32x4_t remainder = vsubq_s32(val_mod_minus_quarter, val);
    const int32x4_t x = vaddq_n_s32(val_mod_minus_quarter << 5, 1 << 28);
    const int32x4_t x2 = MUL_SAT_MVE(x, x);
    const int32x4_t op_1 = DIV_POW2_MVE(MUL_SAT_MVE(x2, x2), 2) + MUL_SAT_MVE(x2, x);
    const int32x4_t op_2 = x + DIV_POW2_MVE(MUL_SAT_MVE(op_1, vdupq_n_s32(715827883)) + x2, 1);
    int32x4_t result = vdupq_n_s32(1895147668) + MUL_SAT_MVE(vdupq_n_s32(1895147668), op_2);

#define SELECT_IF_NON_ZERO(x)                                                                                          \
    {                                                                                                                  \
        mve_pred16_t p = vcmpneq_n_s32(remainder & vdupq_n_s32(1 << shift++), 0);                                      \
        mask = vmvnq_m_s32(vdupq_n_s32(0), vdupq_n_s32(0), p);                                                         \
        result = SELECT_USING_MASK(mask, MUL_SAT_MVE(result, vdupq_n_s32(x)), result);                                 \
    }

    SELECT_IF_NON_ZERO(1672461947)
    SELECT_IF_NON_ZERO(1302514674)
    SELECT_IF_NON_ZERO(790015084)
    SELECT_IF_NON_ZERO(290630308)
    SELECT_IF_NON_ZERO(39332535)
    SELECT_IF_NON_ZERO(720401)
    SELECT_IF_NON_ZERO(242)

#undef SELECT_IF_NON_ZERO

    mve_pred16_t p = vcmpeqq_n_s32(val, 0);
    mask = vmvnq_m_s32(vdupq_n_s32(0), vdupq_n_s32(0), p);

    result = SELECT_USING_MASK(mask, vdupq_n_s32(Q31_MAX), result);
    return result;
}
#endif

/**
 *  @ingroup groupNN
 */

/**
 * @addtogroup Softmax
 * @{
 */

void arm_softmax_s8(const int8_t *input,
                    const int32_t num_rows,
                    const int32_t row_size,
                    const int32_t mult,
                    const int32_t shift,
                    const int32_t diff_min,
                    int8_t *output)
{
#ifdef ARM_MATH_MVEI

#define ACT_MIN ((int8_t)Q7_MIN)
#define ACT_MAX ((int8_t)Q7_MAX)

    const int32_t mask = (1 << shift);

    for (int i_num_rows = 0; i_num_rows < num_rows; ++i_num_rows)
    {
        int8_t max = ACT_MIN;

        int32_t vec_count = (row_size + 15) / 16;
        uint32_t r_count = (uint32_t)row_size;
        for (int i = 0; i < vec_count; i++)
        {
            mve_pred16_t p = vctp8q(r_count);
            const int8x16_t ip = vldrbq_z_s8(&input[i * 16], p);
            max = vmaxvq_p_s8(max, ip, p);
            r_count -= 16;
        }

        vec_count = row_size / 4;
        int32_t idx = 0;
        int32_t sum = 0;

        while (vec_count)
        {
            int32x4_t ip = vldrbq_s32(&input[idx * 4]);
            ip = vsubq_n_s32(ip, max);
            mve_pred16_t p = vcmpgeq_n_s32(ip, diff_min);
            if (p != 0)
            {
                ip = vmulq_n_s32(ip, mask);

                int32x4_t res = MUL_SAT_MVE(ip, vdupq_n_s32(mult));

                res = arm_exp_on_negative_values_mve_32x4(res);
                res = DIV_POW2_MVE(res, ACCUM_BITS);
                res = vpselq_s32(res, vdupq_n_s32(0), p);
                sum += vaddvq_s32(res);
            }

            vec_count--;
            idx++;
        }

        const int32_t tail_idx = row_size & ~3;
        for (int i = 0; i < (row_size & 3); i++)
        {
            const int32_t diff = input[tail_idx + i] - max;
            if (diff >= diff_min)
            {
                sum += DIV_POW2(EXP_ON_NEG(MUL_SAT(diff * mask, mult)), ACCUM_BITS);
            }
        }

        const int32_t headroom = __CLZ((uint32_t)sum);
        const int32_t bits_over_unit = ACCUM_BITS - headroom + 23;
        const int32_t shifted_scale = ONE_OVER1((sum > 0 ? sum << headroom : 0) - (1 << 31));

        vec_count = row_size / 4;
        idx = 0;

        while (vec_count)
        {
            int32x4_t ip = vldrbq_s32(&input[idx]);
            ip = vsubq_n_s32(ip, max);

            mve_pred16_t p = vcmpgeq_n_s32(ip, diff_min);

            int32x4_t tmp_res;

            if (p != 0)
            {
                ip = vmulq_n_s32(ip, mask);

                tmp_res = MUL_SAT_MVE(ip, vdupq_n_s32(mult));
                tmp_res = arm_exp_on_negative_values_mve_32x4(tmp_res);
                tmp_res = MUL_SAT_MVE(vdupq_n_s32(shifted_scale), tmp_res);
                tmp_res = DIV_POW2_MVE(tmp_res, bits_over_unit);
                tmp_res += vdupq_n_s32(ACT_MIN);

                tmp_res = vmaxq_s32(tmp_res, vdupq_n_s32(ACT_MIN));
                tmp_res = vminq_s32(tmp_res, vdupq_n_s32(ACT_MAX));
                tmp_res = vpselq_s32(tmp_res, vdupq_n_s32(ACT_MIN), p);
            }
            else
            {
                tmp_res = vdupq_n_s32(ACT_MIN);
            }
            vstrbq_s32(&output[idx], tmp_res);
            vec_count--;
            idx += 4;
        }

        for (int i = 0; i < (row_size & 3); i++)
        {
            int32_t diff = input[tail_idx + i] - max;
            if (diff >= diff_min)
            {
                const int32_t res =
                    DIV_POW2(MUL_SAT(shifted_scale, EXP_ON_NEG(MUL_SAT(diff * mask, mult))), bits_over_unit) - 128;
                output[tail_idx + i] = (int8_t)CLAMP(res, (int32_t)ACT_MAX, (int32_t)ACT_MIN);
            }
            else
            {
                output[tail_idx + i] = ACT_MIN;
            }
        }

        input += row_size;
        output += row_size;
    }
#else
    const int32_t mask = (1 << shift);

    int32_t col = 0;
    int32_t row_idx;

    for (row_idx = 0; row_idx < num_rows; ++row_idx)
    {
        // Find the maximum value in order to ensure numerical stability
        int8_t max = *input;

        for (col = 1; col < row_size; ++col)
        {
            max = MAX(max, input[col]);
        }

        int32_t diff = 0;
        int32_t sum = 0;

        for (col = 0; col < row_size; ++col)
        {
            diff = input[col] - max;
            if (diff >= diff_min)
            {
                sum += DIV_POW2(EXP_ON_NEG(MUL_SAT(diff * mask, mult)), ACCUM_BITS);
            }
        }

        const int32_t headroom = __CLZ(sum);
        const int32_t bits_over_unit = ACCUM_BITS - headroom + 23;
        const int32_t shifted_scale = ONE_OVER1((sum > 0 ? sum << headroom : 0) - (1 << 31));

        for (col = 0; col < row_size; ++col)
        {
            diff = input[col] - max;
            if (diff >= diff_min)
            {
                const int32_t res =
                    DIV_POW2(MUL_SAT(shifted_scale, EXP_ON_NEG(MUL_SAT(diff * mask, mult))), bits_over_unit) - 128;
                output[col] = (int8_t)CLAMP(res, (int32_t)127, (int32_t)-128);
            }
            else
            {
                output[col] = -128;
            }
        }
        input += row_size;
        output += row_size;
    }

#endif
}
/**
 * @} end of Softmax group
 */
