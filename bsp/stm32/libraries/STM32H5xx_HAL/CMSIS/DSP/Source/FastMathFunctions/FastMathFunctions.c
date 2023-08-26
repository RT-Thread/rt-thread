/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        FastMathFunctions.c
 * Description:  Combination of all fast math function source files.
 *
 * $Date:        16. March 2020
 * $Revision:    V1.1.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2019-2020 ARM Limited or its affiliates. All rights reserved.
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

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_FAST_ALLOW_TABLES)

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SIN_F32)
#include "arm_cos_f32.c"
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SIN_Q15)
#include "arm_cos_q15.c"
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SIN_Q31)
#include "arm_cos_q31.c"
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SIN_F32)
#include "arm_sin_f32.c"
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SIN_Q15)
#include "arm_sin_q15.c"
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SIN_Q31)
#include "arm_sin_q31.c"
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SQRT_Q31)
#include "arm_sqrt_q31.c"
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_SQRT_Q15)
#include "arm_sqrt_q15.c"
#endif 

#endif

#include "arm_vexp_f32.c"
#include "arm_vexp_f64.c"
#include "arm_vlog_f32.c"
#include "arm_vlog_f64.c"
#include "arm_divide_q15.c"
#include "arm_divide_q31.c"
#include "arm_vlog_q31.c"
#include "arm_vlog_q15.c"
#include "arm_atan2_f32.c"
#include "arm_atan2_q31.c"
#include "arm_atan2_q15.c"
