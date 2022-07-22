
/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_correlation_distance_f16.c
 * Description:  Correlation distance between two vectors
 *
 * $Date:        23 April 2021
 * $Revision:    V1.9.0
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

#include "dsp/distance_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)

#include <limits.h>
#include <math.h>


/**
  @ingroup FloatDist
 */

/**
  @defgroup Correlation Correlation distance

  Correlation distance
 */

/**
  @addtogroup Correlation
  @{
 */


/**
 * @brief        Correlation distance between two vectors
 *
 * The input vectors are modified in place !
 *
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */

float16_t arm_correlation_distance_f16(float16_t *pA,float16_t *pB, uint32_t blockSize)
{
    float16_t ma,mb,pwra,pwrb,dot,tmp;

    arm_mean_f16(pA, blockSize, &ma);
    arm_mean_f16(pB, blockSize, &mb);

    arm_offset_f16(pA, -ma, pA, blockSize);
    arm_offset_f16(pB, -mb, pB, blockSize);

    arm_power_f16(pA, blockSize, &pwra);
    arm_power_f16(pB, blockSize, &pwrb);

    arm_dot_prod_f16(pA,pB,blockSize,&dot);

    dot = dot / blockSize;
    pwra = pwra / blockSize;
    pwrb = pwrb / blockSize;

    arm_sqrt_f16(pwra * pwrb,&tmp);

    return(1.0f - dot / tmp);


}



/**
 * @} end of Correlation group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

