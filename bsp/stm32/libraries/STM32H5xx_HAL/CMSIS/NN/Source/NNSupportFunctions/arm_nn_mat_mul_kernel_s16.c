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
 * Title:        arm_nn_mat_mult_kernel_s16.c
 * Description:  Matrix-multiplication function for convolution
 *
 * $Date:        12 August 2021
 * $Revision:    V.1.1.0
 *
 * Target Processor:  Cortex-M cores
 * -------------------------------------------------------------------- */

#include "arm_nnfunctions.h"
#include "arm_nnsupportfunctions.h"

/*
 * Matrix-multiplication function for convolution with per-channel requantization.
 *
 * Refer header file for details.
 *
 */

q15_t *arm_nn_mat_mult_kernel_s16(const q7_t *input_a,
                                  const q15_t *input_b,
                                  const int32_t output_ch,
                                  const int32_t *out_shift,
                                  const int32_t *out_mult,
                                  const int16_t activation_min,
                                  const int16_t activation_max,
                                  const int32_t num_col_a,
                                  const int64_t *const output_bias,
                                  q15_t *out_0)
{

#if defined(ARM_MATH_DSP) && !defined(ARM_MATH_MVEI)
    /* set up the second output pointers */
    q15_t *out_1 = out_0 + output_ch;
    const int64_t *bias = output_bias;
    uint16_t row_count = output_ch / 2;
    const q7_t *ip_a0 = input_a;

    /* this loop over rows in A */
    while (row_count)
    {
        /* setup pointers for B */
        const q15_t *ip_b0 = input_b;
        const q15_t *ip_b1 = ip_b0 + num_col_a;

        /* align the second pointer for A */
        const q7_t *ip_a1 = ip_a0 + num_col_a;

        /* Init accumulator for channel N and N + 1 */
        q31_t ch_0_out_0 = 0;
        q31_t ch_0_out_1 = 0;
        q31_t ch_1_out_0 = 0;
        q31_t ch_1_out_1 = 0;

        uint16_t col_count = num_col_a / 4;
        /* accumulate over the vector */
        while (col_count)
        {
            q31_t a01, a02, a11, a12;
            q31_t b0 = arm_nn_read_q15x2_ia(&ip_b0);
            q31_t b1 = arm_nn_read_q15x2_ia(&ip_b1);

            ip_a0 = read_and_pad(ip_a0, &a01, &a02);
            ip_a1 = read_and_pad(ip_a1, &a11, &a12);

            ch_0_out_0 = __SMLAD(a01, b0, ch_0_out_0);
            ch_0_out_1 = __SMLAD(a01, b1, ch_0_out_1);
            ch_1_out_0 = __SMLAD(a11, b0, ch_1_out_0);
            ch_1_out_1 = __SMLAD(a11, b1, ch_1_out_1);

            b0 = arm_nn_read_q15x2_ia(&ip_b0);
            b1 = arm_nn_read_q15x2_ia(&ip_b1);

            ch_0_out_0 = __SMLAD(a02, b0, ch_0_out_0);
            ch_0_out_1 = __SMLAD(a02, b1, ch_0_out_1);
            ch_1_out_0 = __SMLAD(a12, b0, ch_1_out_0);
            ch_1_out_1 = __SMLAD(a12, b1, ch_1_out_1);

            col_count--;
        } /* while over col_count */
        col_count = num_col_a & 0x3;
        while (col_count)
        {
            q7_t a0 = *ip_a0++;
            q15_t b0 = *ip_b0++;
            q7_t a1 = *ip_a1++;
            q15_t b1 = *ip_b1++;

            ch_0_out_0 += a0 * b0;
            ch_0_out_1 += a0 * b1;
            ch_1_out_0 += a1 * b0;
            ch_1_out_1 += a1 * b1;
            col_count--;
        } /* while over col_count */
        if (bias)
        {
            q31_t reduced_multiplier = REDUCE_MULTIPLIER(*out_mult);
            q63_t acc_64 = ch_0_out_0 + *bias;
            ch_0_out_0 = arm_nn_requantize_s64(acc_64, reduced_multiplier, *out_shift);
            acc_64 = ch_0_out_1 + *bias++;
            ch_0_out_1 = arm_nn_requantize_s64(acc_64, reduced_multiplier, *out_shift);
            out_mult++;
        }
        else
        {
            ch_0_out_0 = arm_nn_requantize(ch_0_out_0, *out_mult, *out_shift);
            ch_0_out_1 = arm_nn_requantize(ch_0_out_1, *out_mult, *out_shift);
            out_mult++;
        }
        ch_0_out_0 = MAX(ch_0_out_0, activation_min);
        ch_0_out_0 = MIN(ch_0_out_0, activation_max);
        *out_0++ = (q15_t)ch_0_out_0;

        ch_0_out_1 = MAX(ch_0_out_1, activation_min);
        ch_0_out_1 = MIN(ch_0_out_1, activation_max);
        *out_1++ = (q15_t)ch_0_out_1;
        out_shift++;

        if (bias)
        {
            q31_t reduced_multiplier = REDUCE_MULTIPLIER(*out_mult);
            q63_t acc_64 = ch_1_out_0 + *bias;
            ch_1_out_0 = arm_nn_requantize_s64(acc_64, reduced_multiplier, *out_shift);
            acc_64 = ch_1_out_1 + *bias++;
            ch_1_out_1 = arm_nn_requantize_s64(acc_64, reduced_multiplier, *out_shift);
            out_mult++;
        }
        else
        {
            ch_1_out_0 = arm_nn_requantize(ch_1_out_0, *out_mult, *out_shift);
            ch_1_out_1 = arm_nn_requantize(ch_1_out_1, *out_mult, *out_shift);
            out_mult++;
        }
        ch_1_out_0 = MAX(ch_1_out_0, activation_min);
        ch_1_out_0 = MIN(ch_1_out_0, activation_max);
        *out_0++ = (q15_t)ch_1_out_0;

        ch_1_out_1 = MAX(ch_1_out_1, activation_min);
        ch_1_out_1 = MIN(ch_1_out_1, activation_max);
        *out_1++ = (q15_t)ch_1_out_1;
        out_shift++;

        /* skip row */
        ip_a0 += num_col_a;
        row_count--;
    }

    /* compute the last odd numbered row if any */
    if (output_ch & 0x1)
    {
        /* setup pointers for B */
        const q15_t *ip_b0 = input_b;
        const q15_t *ip_b1 = ip_b0 + num_col_a;

        q31_t ch_0_out_0 = 0;
        q31_t ch_0_out_1 = 0;

        uint16_t col_count = num_col_a >> 2;
        while (col_count)
        {
            q31_t a01, a02;
            q31_t b0 = arm_nn_read_q15x2_ia(&ip_b0);
            q31_t b1 = arm_nn_read_q15x2_ia(&ip_b1);

            ip_a0 = read_and_pad(ip_a0, &a01, &a02);

            ch_0_out_0 = __SMLAD(a01, b0, ch_0_out_0);
            ch_0_out_1 = __SMLAD(a01, b1, ch_0_out_1);

            b0 = arm_nn_read_q15x2_ia(&ip_b0);
            b1 = arm_nn_read_q15x2_ia(&ip_b1);
            ch_0_out_0 = __SMLAD(a02, b0, ch_0_out_0);
            ch_0_out_1 = __SMLAD(a02, b1, ch_0_out_1);

            col_count--;
        }
        col_count = num_col_a & 0x3;
        while (col_count)
        {
            q7_t a0 = *ip_a0++;
            q15_t b0 = *ip_b0++;
            q15_t b1 = *ip_b1++;

            ch_0_out_0 += a0 * b0;
            ch_0_out_1 += a0 * b1;
            col_count--;
        }
        if (bias)
        {
            q31_t reduced_multiplier = REDUCE_MULTIPLIER(*out_mult);
            q63_t acc_64 = ch_0_out_0 + *bias;
            ch_0_out_0 = arm_nn_requantize_s64(acc_64, reduced_multiplier, *out_shift);
            acc_64 = ch_0_out_1 + *bias++;
            ch_0_out_1 = arm_nn_requantize_s64(acc_64, reduced_multiplier, *out_shift);
        }
        else
        {
            ch_0_out_0 = arm_nn_requantize(ch_0_out_0, *out_mult, *out_shift);
            ch_0_out_1 = arm_nn_requantize(ch_0_out_1, *out_mult, *out_shift);
        }
        ch_0_out_0 = MAX(ch_0_out_0, activation_min);
        ch_0_out_0 = MIN(ch_0_out_0, activation_max);
        *out_0++ = (q15_t)ch_0_out_0;

        ch_0_out_1 = MAX(ch_0_out_1, activation_min);
        ch_0_out_1 = MIN(ch_0_out_1, activation_max);
        *out_1++ = (q15_t)ch_0_out_1;
        out_mult++;
        out_shift++;
    }

    out_0 += output_ch;

    /* return the new output pointer with offset */
    return out_0;
#else
    (void)input_a;
    (void)input_b;
    (void)output_ch;
    (void)out_shift;
    (void)out_mult;
    (void)activation_min;
    (void)activation_max;
    (void)num_col_a;
    (void)output_bias;
    (void)out_0;
    /* To be completed */
    return NULL;
#endif
}
