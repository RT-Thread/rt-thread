/*
 * Copyright (C) 2010-2018 Arm Limited or its affiliates. All rights reserved.
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
 * Title:        arm_nn_add_q7.c
 * Description:  Non saturating addition of elements of a q7 vector.
 *
 * $Date:        20. July 2021
 * $Revision:    V.1.1.1
 *
 * Target Processor:  Cortex-M cores
 *
 * -------------------------------------------------------------------- */

#include "arm_nn_tables.h"
#include "arm_nnsupportfunctions.h"

/**
 * @ingroup groupSupport
 */

/**
 * @addtogroup NNBasicMath
 * @{
 */

void arm_nn_add_q7(const q7_t *input, q31_t *output, uint32_t block_size)
{
    uint32_t block_count;
    q31_t result = 0;
#if defined(ARM_MATH_DSP) && !defined(ARM_MATH_MVEI)
    /* Loop unrolling: Compute 4 outputs at a time */
    block_count = block_size >> 2U;

    while (block_count > 0U)
    {
        const int32_t mult_q15x2 = (1UL << 16) | 1UL;
        q31_t in_q7x4 = arm_nn_read_q7x4_ia(&input);
        q31_t temp_q15x2 = __SXTAB16(__SXTB16(in_q7x4), __ROR((uint32_t)in_q7x4, 8));

        result = __SMLAD(temp_q15x2, mult_q15x2, result);

        /* Decrement loop counter */
        block_count--;
    }

    /* Loop unrolling: Compute remaining outputs */
    block_count = block_size & 0x3;
#else
    block_count = block_size;
#endif
    while (block_count > 0U)
    {
        /* Add and store result in destination buffer. */
        result += *input++;

        /* Decrement loop counter */
        block_count--;
    }

    *output = result;
}

/**
 * @} end of NNBasicMath group
 */