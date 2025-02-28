/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mve_tables_f16.h
 * Description:  common tables like fft twiddle factors, Bitreverse, reciprocal etc
 *               used for MVE implementation only
 *
 * @version  V1.10.0
 * @date     04 October 2021
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

 #ifndef _ARM_MVE_TABLES_F16_H
 #define _ARM_MVE_TABLES_F16_H

#include "arm_math_types_f16.h"

#ifdef   __cplusplus
extern "C"
{
#endif




#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_FFT_ALLOW_TABLES)

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_F16_16) || defined(ARM_TABLE_TWIDDLECOEF_F16_32)

extern uint32_t rearranged_twiddle_tab_stride1_arr_16_f16[2];
extern uint32_t rearranged_twiddle_tab_stride2_arr_16_f16[2];
extern uint32_t rearranged_twiddle_tab_stride3_arr_16_f16[2];
extern float16_t rearranged_twiddle_stride1_16_f16[8];
extern float16_t rearranged_twiddle_stride2_16_f16[8];
extern float16_t rearranged_twiddle_stride3_16_f16[8];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_F16_64) || defined(ARM_TABLE_TWIDDLECOEF_F16_128)

extern uint32_t rearranged_twiddle_tab_stride1_arr_64_f16[3];
extern uint32_t rearranged_twiddle_tab_stride2_arr_64_f16[3];
extern uint32_t rearranged_twiddle_tab_stride3_arr_64_f16[3];
extern float16_t rearranged_twiddle_stride1_64_f16[40];
extern float16_t rearranged_twiddle_stride2_64_f16[40];
extern float16_t rearranged_twiddle_stride3_64_f16[40];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_F16_256) || defined(ARM_TABLE_TWIDDLECOEF_F16_512)

extern uint32_t rearranged_twiddle_tab_stride1_arr_256_f16[4];
extern uint32_t rearranged_twiddle_tab_stride2_arr_256_f16[4];
extern uint32_t rearranged_twiddle_tab_stride3_arr_256_f16[4];
extern float16_t rearranged_twiddle_stride1_256_f16[168];
extern float16_t rearranged_twiddle_stride2_256_f16[168];
extern float16_t rearranged_twiddle_stride3_256_f16[168];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_F16_1024) || defined(ARM_TABLE_TWIDDLECOEF_F16_2048)

extern uint32_t rearranged_twiddle_tab_stride1_arr_1024_f16[5];
extern uint32_t rearranged_twiddle_tab_stride2_arr_1024_f16[5];
extern uint32_t rearranged_twiddle_tab_stride3_arr_1024_f16[5];
extern float16_t rearranged_twiddle_stride1_1024_f16[680];
extern float16_t rearranged_twiddle_stride2_1024_f16[680];
extern float16_t rearranged_twiddle_stride3_1024_f16[680];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_F16_4096) || defined(ARM_TABLE_TWIDDLECOEF_F16_8192)

extern uint32_t rearranged_twiddle_tab_stride1_arr_4096_f16[6];
extern uint32_t rearranged_twiddle_tab_stride2_arr_4096_f16[6];
extern uint32_t rearranged_twiddle_tab_stride3_arr_4096_f16[6];
extern float16_t rearranged_twiddle_stride1_4096_f16[2728];
extern float16_t rearranged_twiddle_stride2_4096_f16[2728];
extern float16_t rearranged_twiddle_stride3_4096_f16[2728];
#endif


#endif /* !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_FFT_ALLOW_TABLES) */

#endif /* defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE) */



#ifdef   __cplusplus
}
#endif

#endif /*_ARM_MVE_TABLES_F16_H*/

