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
 * Title:        arm_q7_to_q15_reordered_with_offset.c
 * Description:  Converts the elements of the Q7 vector to a reordered Q15 vector with an added offset. The re-ordering
 *               is a signature of sign extension intrinsic(DSP extension).
 *
 * $Date:        May 29, 2020
 * $Revision:    V.2.0.3
 *
 * Target Processor:  Cortex-M cores
 *
 * -------------------------------------------------------------------- */

#include "arm_nnsupportfunctions.h"

/**
 * @ingroup groupSupport
 */

/**
 * @addtogroup nndata_convert
 * @{
 */

/**
 * @brief Converts the elements of the Q7 vector to a reordered Q15 vector with an added offset.
 *
 * @note  Refer header file for details.
 *
 */

void arm_q7_to_q15_reordered_with_offset(const q7_t *src, q15_t *dst, uint32_t block_size, q15_t offset)
{

#if defined(ARM_MATH_DSP)
    uint32_t block_cnt;
    /* Run the below code for cores that support SIMD instructions  */
    q31_t in_q7x4;
    q31_t out_q15x2_1;
    q31_t out_q15x2_2;

    /*loop unrolling */
    block_cnt = block_size >> 2u;

    /* First part of the processing with loop unrolling. Compute 4 outputs at a time. */
    const q31_t offset_q15x2 = (q31_t)__PKHBT(offset, offset, 16);
    while (block_cnt > 0u)
    {
        /* convert from q7 to q15 and then store the results in the destination buffer */
        in_q7x4 = arm_nn_read_q7x4_ia(&src);

        /* Extract and sign extend each of the four q7 values to q15 */
        out_q15x2_1 = __SXTAB16(offset_q15x2, __ROR((uint32_t)in_q7x4, 8));
        out_q15x2_2 = __SXTAB16(offset_q15x2, in_q7x4);

        arm_nn_write_q15x2_ia(&dst, out_q15x2_2);
        arm_nn_write_q15x2_ia(&dst, out_q15x2_1);

        block_cnt--;
    }
    /* Handle left over samples */
    block_cnt = block_size % 0x4u;

    while (block_cnt > 0u)
    {
        *dst++ = (q15_t)*src++ + offset;

        /* Decrement the loop counter */
        block_cnt--;
    }
#else
    (void)src;
    (void)dst;
    (void)block_size;
    (void)offset;
    /* Not available */
#endif
}

/**
 * @} end of nndata_convert group
 */
