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
 * Title:        arm_nn_activations_q15.c
 * Description:  Q15 neural network activation function using direct table look-up
 *
 * $Date:        09. October 2020
 * $Revision:    V.1.0.1
 *
 * Target Processor:  Cortex-M cores
 *
 * -------------------------------------------------------------------- */

#include "arm_nn_tables.h"
#include "arm_nnfunctions.h"

/**
 *  @ingroup groupNN
 */

/**
 * @addtogroup Acti
 * @{
 */

/**
 * @brief neural network activation function using direct table look-up
 *
 * @note  Refer header file for details.
 *
 */

void arm_nn_activations_direct_q15(q15_t *data, uint16_t size, uint16_t int_width, arm_nn_activation_type type)
{
    uint16_t i = size;
    q15_t *pIn = data;
    q15_t *pOut = data;
    uint16_t shift_size = 8 + 3 - int_width;
    uint32_t bit_mask = 0x7FF >> int_width;
    uint32_t full_frac = bit_mask + 1;
    const q15_t *lookup_table;

    switch (type)
    {
    case ARM_SIGMOID:
        lookup_table = sigmoidTable_q15;
        break;
    case ARM_TANH:
    default:
        lookup_table = tanhTable_q15;
        break;
    }

    while (i)
    {
        q15_t out;
        q15_t in = *pIn++;
        q15_t frac = (uint32_t)in & bit_mask;
        q15_t value = lookup_table[(uint8_t)(in >> shift_size)];
        if ((in >> shift_size) != 0x7f)
        {
            q15_t value2 = lookup_table[(uint8_t)(1 + ((uint8_t)(in >> shift_size)))];
            /* doing the interpolation here for better accuracy */
            out = ((q31_t)(full_frac - frac) * value + (q31_t)value2 * frac) >> shift_size;
        }
        else
        {
            /* the largest positive value does not have a right side for linear interpolation */
            out = value;
        }

        *pOut++ = out;
        i--;
    }
}

/**
 * @} end of Acti group
 */
