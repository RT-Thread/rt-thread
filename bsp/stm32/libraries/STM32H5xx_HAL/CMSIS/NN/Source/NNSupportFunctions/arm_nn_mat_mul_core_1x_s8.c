/*
 * Copyright (C) 2010-2022 Arm Limited or its affiliates. All rights reserved.
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
 * Title:        arm_nn_mat_mul_core_1x_s8.c
 * Description:  General Matrix-multiplication function
 *
 * $Date:        19. April 2022
 * $Revision:    V.1.0.3
 *
 * Target Processor:  Cortex-M cores
 * -------------------------------------------------------------------- */

#include "arm_nnsupportfunctions.h"

/**
 * @ingroup groupSupport
 */

/**
 * @addtogroup NNBasicMath
 * @{
 */

/*
 * s8 matrix multiplication to process 1 row
 *
 * Refer header file for details.
 *
 */

arm_status arm_nn_mat_mul_core_1x_s8(int32_t row_elements,
                                     const int8_t *row_base,
                                     const int8_t *col_base,
                                     int32_t *const sum_col,
                                     int32_t *const output)
{
    int32_t acc_n0 = 0;
    int32_t sum_tmp = 0;

#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

    __ASM volatile("   vldrb.8         q0, [%[col]], #16     \n"
                   "   wlstp.8         lr, %[cnt], 1f       \n"
                   "2:                                      \n"
                   "   vaddva.s8      %[sum], q0            \n"
                   "   vldrb.8         q1, [%[row0]], #16    \n"
                   "   vmladava.s8    %[out0], q0, q1       \n"
                   "   vldrb.8         q0, [%[col]], #16     \n"
                   "   letp            lr, 2b               \n"
                   "1:                                      \n"
                   : [col] "+r"(col_base), [sum] "+Te"(sum_tmp), [row0] "+r"(row_base), [out0] "+Te"(acc_n0)
                   : [cnt] "r"(row_elements)
                   : "q0", "q1", "memory", "r14");
#else
    for (int i = 0; i < row_elements; i++)
    {
        sum_tmp += col_base[i];
        acc_n0 += row_base[i] * col_base[i];
    }
#endif

    *sum_col = sum_tmp;
    *output = acc_n0;
    return ARM_MATH_SUCCESS;
}

/**
 * @} end of NNBasicMath group
 */
