/*
 * Copyright (C) 2010-2021 Arm Limited or its affiliates. All rights reserved.
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
 * Title:        arm_nn_accumulate_q7_to_q15.c
 * Description:  Accumulate q7 vector into q15 one.
 *
 * $Date:        20 July 2021
 * $Revision:    V.1.1.2
 *
 * pSrc Processor:  Cortex-M CPUs
 *
 * -------------------------------------------------------------------- */

#include "arm_nnfunctions.h"
#include "arm_nnsupportfunctions.h"

/**
 * @ingroup groupSupport
 */

/**
 * @addtogroup NNBasicMath
 * @{
 */

void arm_nn_accumulate_q7_to_q15(q15_t *pDst, const q7_t *pSrc, uint32_t length)
{
    q15_t *pCnt = pDst;
    const q7_t *pV = pSrc;
    int32_t count = length;
#if defined(ARM_MATH_DSP) && !defined(ARM_MATH_MVEI)
    q31_t v1, v2, vo1, vo2;
    count = length >> 2;
    q31_t in;

    while (count > 0l)
    {
        q31_t value = arm_nn_read_q7x4_ia(&pV);
        v1 = __SXTB16(__ROR((uint32_t)value, 8));
        v2 = __SXTB16(value);
#ifndef ARM_MATH_BIG_ENDIAN
        vo2 = (q31_t)__PKHTB(v1, v2, 16);
        vo1 = (q31_t)__PKHBT(v2, v1, 16);
#else
        vo1 = (q31_t)__PKHTB(v1, v2, 16);
        vo2 = (q31_t)__PKHBT(v2, v1, 16);
#endif

        in = arm_nn_read_q15x2(pCnt);
        arm_nn_write_q15x2_ia(&pCnt, __QADD16(vo1, in));

        in = arm_nn_read_q15x2(pCnt);
        arm_nn_write_q15x2_ia(&pCnt, __QADD16(vo2, in));

        count--;
    }
    count = length & 0x3;
#endif
    while (count > 0l)
    {
        *pCnt++ += *pV++;
        count--;
    }
}

/**
 * @} end of NNBasicMath group
 */
