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
 * Title:        arm_relu_q15.c
 * Description:  Q15 version of ReLU
 *
 * $Date:        09. October 2020
 * $Revision:    V.1.0.2
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
 * @brief Q15 RELU function
 * @param[in,out]   data        pointer to input
 * @param[in]       size        number of elements
 *
 * @details
 *
 * Optimized relu with QSUB instructions.
 *
 */

void arm_relu_q15(q15_t *data, uint16_t size)
{

#if defined(ARM_MATH_DSP)
    /* Run the following code for M cores with DSP extension */

    uint16_t i = size >> 1;
    q15_t *input = data;
    q15_t *output = data;
    q31_t in;
    q31_t buf;
    q31_t mask;

    while (i)
    {
        in = read_q15x2_ia(&input);

        /* extract the first bit */
        buf = __ROR(in & 0x80008000, 15);

        /* if MSB=1, mask will be 0xFF, 0x0 otherwise */
        mask = __QSUB16(0x00000000, buf);

        arm_nn_write_q15x2_ia(&output, in & (~mask));
        i--;
    }

    if (size & 0x1)
    {
        if (*input < 0)
        {
            *input = 0;
        }
        input++;
    }
#else
    /* Run the following code as reference implementation for M cores without DSP extension */
    uint16_t i;

    for (i = 0; i < size; i++)
    {
        if (data[i] < 0)
            data[i] = 0;
    }

#endif /* ARM_MATH_DSP */
}

/**
 * @} end of Acti group
 */
