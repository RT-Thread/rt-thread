/*
 * Copyright (C) 2010-2019 Arm Limited or its affiliates. All rights reserved.
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
 * Title:        arm_softmax_with_batch_q7.c
 * Description:  Q7 softmax function
 *
 * $Date:        09. October 2020
 * $Revision:    V.1.0.1
 *
 * Target Processor:  Cortex-M and Cortex-A cores
 *
 * -------------------------------------------------------------------- */

#include "arm_nnfunctions.h"

/**
 *  @ingroup groupNN
 */

/**
 * @addtogroup Softmax
 * @{
 */

/**
 * @brief Q7 softmax function with batch parameter
 * @param[in]       vec_in      pointer to input vector
 * @param[in]       nb_batches  number of batches
 * @param[in]       dim_vec     input vector dimention
 * @param[out]      p_out       pointer to output vector
 *
 * @details
 *
 *  Here, instead of typical natural logarithm e based softmax, we use
 *  2-based softmax here, i.e.,:
 *
 *  y_i = 2^(x_i) / sum(2^x_j)
 *
 *  The relative output will be different here.
 *  But mathematically, the gradient will be the same
 *  with a log(2) scaling factor.
 *
 */

void arm_softmax_with_batch_q7(const q7_t *vec_in, const uint16_t nb_batches, const uint16_t dim_vec, q7_t *p_out)
{
    for (int i = 0; i < nb_batches; i++)
    {
        arm_softmax_q7(vec_in, dim_vec, p_out);
        vec_in += dim_vec;
        p_out += dim_vec;
    }
}

/**
 * @} end of Softmax group
 */
