/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        CompexMathFunctions.c
 * Description:  Combination of all comlex math function source files.
 *
 * $Date:        18. March 2019
 * $Revision:    V1.0.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2019 ARM Limited or its affiliates. All rights reserved.
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

#include "arm_cmplx_conj_f32.c"
#include "arm_cmplx_conj_q15.c"
#include "arm_cmplx_conj_q31.c"
#include "arm_cmplx_dot_prod_f32.c"
#include "arm_cmplx_dot_prod_q15.c"
#include "arm_cmplx_dot_prod_q31.c"
#include "arm_cmplx_mag_f32.c"
#include "arm_cmplx_mag_f64.c"

#if (defined (ARM_MATH_HELIUM) || defined(ARM_MATH_MVEI))  && !defined(ARM_MATH_AUTOVECTORIZE)
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_FAST_SQRT_Q31_MVE)
  #include "arm_cmplx_mag_q15.c"
  #endif 

  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_FAST_SQRT_Q15_MVE)
  #include "arm_cmplx_mag_fast_q15.c"
  #endif 
  
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_FAST_SQRT_Q31_MVE)
  #include "arm_cmplx_mag_q31.c"
  #endif
#else
  #include "arm_cmplx_mag_q15.c"
  #include "arm_cmplx_mag_fast_q15.c"
  #include "arm_cmplx_mag_q31.c"
#endif

#include "arm_cmplx_mag_squared_f32.c"
#include "arm_cmplx_mag_squared_f64.c"
#include "arm_cmplx_mag_squared_q15.c"
#include "arm_cmplx_mag_squared_q31.c"
#include "arm_cmplx_mult_cmplx_f32.c"
#include "arm_cmplx_mult_cmplx_f64.c"
#include "arm_cmplx_mult_cmplx_q15.c"
#include "arm_cmplx_mult_cmplx_q31.c"
#include "arm_cmplx_mult_real_f32.c"
#include "arm_cmplx_mult_real_q15.c"
#include "arm_cmplx_mult_real_q31.c"
