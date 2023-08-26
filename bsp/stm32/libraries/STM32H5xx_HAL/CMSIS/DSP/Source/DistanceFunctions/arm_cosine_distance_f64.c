
/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_cosine_distance_f64.c
 * Description:  Cosine distance between two vectors
 *
 * $Date:        13 September 2021
 * $Revision:    V1.10.0
 *
 * Target Processor: Cortex-M and Cortex-A cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2021 ARM Limited or its affiliates. All rights reserved.
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

#include "dsp/distance_functions.h"
#include <limits.h>
#include <math.h>


/**
  @addtogroup CosineDist
  @{
 */



/**
 * @brief        Cosine distance between two vectors
 *
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */

float64_t arm_cosine_distance_f64(const float64_t *pA,const float64_t *pB, uint32_t blockSize)
{
    float64_t pwra,pwrb,dot,tmp;

    arm_power_f64(pA, blockSize, &pwra);
    arm_power_f64(pB, blockSize, &pwrb);

    arm_dot_prod_f64(pA,pB,blockSize,&dot);

    tmp = sqrt(pwra * pwrb);
    return(1. - dot / tmp);

}



/**
 * @} end of CosineDist group
 */
