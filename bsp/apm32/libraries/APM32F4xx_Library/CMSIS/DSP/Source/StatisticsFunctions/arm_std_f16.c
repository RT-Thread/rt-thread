/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_std_f16.c
 * Description:  Standard deviation of the elements of a floating-point vector
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

#include "dsp/statistics_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)


/**
  @ingroup groupStats
 */



/**
  @addtogroup STD
  @{
 */

/**
  @brief         Standard deviation of the elements of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    standard deviation value returned here
  @return        none
 */
void arm_std_f16(
  const float16_t * pSrc,
        uint32_t blockSize,
        float16_t * pResult)
{
  float16_t var;
  arm_var_f16(pSrc,blockSize,&var);
  arm_sqrt_f16(var, pResult);
}

/**
  @} end of STD group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

