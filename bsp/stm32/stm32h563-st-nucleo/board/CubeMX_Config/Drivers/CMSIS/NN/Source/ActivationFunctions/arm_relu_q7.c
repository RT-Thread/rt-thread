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
 * Title:        arm_relu_q7.c
 * Description:  Q7 version of ReLU
 *
 * $Date:        20. July 2021
 * $Revision:    V.1.1.3
 *
 * Target Processor:  Cortex-M cores
 *
 * -------------------------------------------------------------------- */

#include "arm_nnfunctions.h"
#include "arm_nnsupportfunctions.h"

/**
 *  @ingroup groupNN
 */

/**
 * @addtogroup Acti
 * @{
 */

/**
 * @brief Q7 RELU function
 * @param[in,out]   data        pointer to input
 * @param[in]       size        number of elements
 *
 * @details
 *
 * Optimized relu with QSUB instructions.
 *
 */

void arm_relu_q7(q7_t *data, uint16_t size)
{

#if defined(ARM_MATH_DSP) && !defined(ARM_MATH_MVEI)
    /* Run the following code for M cores with DSP extension */

    uint16_t i = size >> 2;
    q7_t *input = data;
    q7_t *output = data;
    q31_t in;
    q31_t buf;
    q31_t mask;

    while (i)
    {
        in = arm_nn_read_q7x4_ia((const q7_t **)&input);

        /* extract the first bit */
        buf = (int32_t)__ROR((uint32_t)in & 0x80808080, 7);

        /* if MSB=1, mask will be 0xFF, 0x0 otherwise */
        mask = __QSUB8(0x00000000, buf);

        arm_nn_write_q7x4_ia(&output, in & (~mask));

        i--;
    }

    i = size & 0x3;
    while (i)
    {
        if (*input < 0)
        {
            *input = 0;
        }
        input++;
        i--;
    }

#else
    /* Run the following code as reference implementation for cores without DSP extension */

    uint16_t i;

    for (i = 0; i < size; i++)
    {
        if (data[i] < 0)
            data[i] = 0;
    }

#endif
}

/**
 * @} end of Acti group
 */
