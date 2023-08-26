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
 * Title:        arm_concatenation_s8_z.c
 * Description:  s8 version of concatenation along the Z axis
 *
 * $Date:        October 2019
 * $Revision:    V.1.0.0
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
 * @addtogroup Concatenation
 * @{
 */

/*
 *  s8 version of concatenation along the Z axis
 *
 * Refer to header file for details.
 *
 */
void arm_concatenation_s8_z(const int8_t *input,
                            const uint16_t input_x,
                            const uint16_t input_y,
                            const uint16_t input_z,
                            const uint16_t input_w,
                            int8_t *output,
                            const uint16_t output_z,
                            const uint32_t offset_z)
{
    const uint32_t input_copy_size = input_x * input_y * input_z;
    const uint32_t output_stride = input_x * input_y * output_z;

    output += offset_z * (input_x * input_y);

    uint32_t i;

    for (i = 0; i < input_w; ++i)
    {
        arm_memcpy_q7(output, input, input_copy_size);
        input += input_copy_size;
        output += output_stride;
    }
}

/**
 * @} end of Concatenation group
 */
