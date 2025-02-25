/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mve_tables.h
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

 #ifndef _ARM_MVE_TABLES_H
 #define _ARM_MVE_TABLES_H

#include "arm_math_types.h"

#ifdef   __cplusplus
extern "C"
{
#endif




#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_FFT_ALLOW_TABLES)

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_F32_16) || defined(ARM_TABLE_TWIDDLECOEF_F32_32)

extern uint32_t rearranged_twiddle_tab_stride1_arr_16_f32[2];
extern uint32_t rearranged_twiddle_tab_stride2_arr_16_f32[2];
extern uint32_t rearranged_twiddle_tab_stride3_arr_16_f32[2];
extern float32_t rearranged_twiddle_stride1_16_f32[8];
extern float32_t rearranged_twiddle_stride2_16_f32[8];
extern float32_t rearranged_twiddle_stride3_16_f32[8];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_F32_64) || defined(ARM_TABLE_TWIDDLECOEF_F32_128)

extern uint32_t rearranged_twiddle_tab_stride1_arr_64_f32[3];
extern uint32_t rearranged_twiddle_tab_stride2_arr_64_f32[3];
extern uint32_t rearranged_twiddle_tab_stride3_arr_64_f32[3];
extern float32_t rearranged_twiddle_stride1_64_f32[40];
extern float32_t rearranged_twiddle_stride2_64_f32[40];
extern float32_t rearranged_twiddle_stride3_64_f32[40];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_F32_256) || defined(ARM_TABLE_TWIDDLECOEF_F32_512)

extern uint32_t rearranged_twiddle_tab_stride1_arr_256_f32[4];
extern uint32_t rearranged_twiddle_tab_stride2_arr_256_f32[4];
extern uint32_t rearranged_twiddle_tab_stride3_arr_256_f32[4];
extern float32_t rearranged_twiddle_stride1_256_f32[168];
extern float32_t rearranged_twiddle_stride2_256_f32[168];
extern float32_t rearranged_twiddle_stride3_256_f32[168];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_F32_1024) || defined(ARM_TABLE_TWIDDLECOEF_F32_2048)

extern uint32_t rearranged_twiddle_tab_stride1_arr_1024_f32[5];
extern uint32_t rearranged_twiddle_tab_stride2_arr_1024_f32[5];
extern uint32_t rearranged_twiddle_tab_stride3_arr_1024_f32[5];
extern float32_t rearranged_twiddle_stride1_1024_f32[680];
extern float32_t rearranged_twiddle_stride2_1024_f32[680];
extern float32_t rearranged_twiddle_stride3_1024_f32[680];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_F32_4096) || defined(ARM_TABLE_TWIDDLECOEF_F32_8192)

extern uint32_t rearranged_twiddle_tab_stride1_arr_4096_f32[6];
extern uint32_t rearranged_twiddle_tab_stride2_arr_4096_f32[6];
extern uint32_t rearranged_twiddle_tab_stride3_arr_4096_f32[6];
extern float32_t rearranged_twiddle_stride1_4096_f32[2728];
extern float32_t rearranged_twiddle_stride2_4096_f32[2728];
extern float32_t rearranged_twiddle_stride3_4096_f32[2728];
#endif


#endif /* !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_FFT_ALLOW_TABLES) */

#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */



#if defined(ARM_MATH_MVEI)  && !defined(ARM_MATH_AUTOVECTORIZE)

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_FFT_ALLOW_TABLES)

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_Q31_16) || defined(ARM_TABLE_TWIDDLECOEF_Q31_32)

extern uint32_t rearranged_twiddle_tab_stride1_arr_16_q31[2];
extern uint32_t rearranged_twiddle_tab_stride2_arr_16_q31[2];
extern uint32_t rearranged_twiddle_tab_stride3_arr_16_q31[2];
extern q31_t rearranged_twiddle_stride1_16_q31[8];
extern q31_t rearranged_twiddle_stride2_16_q31[8];
extern q31_t rearranged_twiddle_stride3_16_q31[8];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_Q31_64) || defined(ARM_TABLE_TWIDDLECOEF_Q31_128)

extern uint32_t rearranged_twiddle_tab_stride1_arr_64_q31[3];
extern uint32_t rearranged_twiddle_tab_stride2_arr_64_q31[3];
extern uint32_t rearranged_twiddle_tab_stride3_arr_64_q31[3];
extern q31_t rearranged_twiddle_stride1_64_q31[40];
extern q31_t rearranged_twiddle_stride2_64_q31[40];
extern q31_t rearranged_twiddle_stride3_64_q31[40];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_Q31_256) || defined(ARM_TABLE_TWIDDLECOEF_Q31_512)

extern uint32_t rearranged_twiddle_tab_stride1_arr_256_q31[4];
extern uint32_t rearranged_twiddle_tab_stride2_arr_256_q31[4];
extern uint32_t rearranged_twiddle_tab_stride3_arr_256_q31[4];
extern q31_t rearranged_twiddle_stride1_256_q31[168];
extern q31_t rearranged_twiddle_stride2_256_q31[168];
extern q31_t rearranged_twiddle_stride3_256_q31[168];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_Q31_1024) || defined(ARM_TABLE_TWIDDLECOEF_Q31_2048)

extern uint32_t rearranged_twiddle_tab_stride1_arr_1024_q31[5];
extern uint32_t rearranged_twiddle_tab_stride2_arr_1024_q31[5];
extern uint32_t rearranged_twiddle_tab_stride3_arr_1024_q31[5];
extern q31_t rearranged_twiddle_stride1_1024_q31[680];
extern q31_t rearranged_twiddle_stride2_1024_q31[680];
extern q31_t rearranged_twiddle_stride3_1024_q31[680];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_Q31_4096) || defined(ARM_TABLE_TWIDDLECOEF_Q31_8192)

extern uint32_t rearranged_twiddle_tab_stride1_arr_4096_q31[6];
extern uint32_t rearranged_twiddle_tab_stride2_arr_4096_q31[6];
extern uint32_t rearranged_twiddle_tab_stride3_arr_4096_q31[6];
extern q31_t rearranged_twiddle_stride1_4096_q31[2728];
extern q31_t rearranged_twiddle_stride2_4096_q31[2728];
extern q31_t rearranged_twiddle_stride3_4096_q31[2728];
#endif


#endif /* !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_FFT_ALLOW_TABLES) */

#endif /* defined(ARM_MATH_MVEI) */



#if defined(ARM_MATH_MVEI)  && !defined(ARM_MATH_AUTOVECTORIZE)

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_FFT_ALLOW_TABLES)

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_Q15_16) || defined(ARM_TABLE_TWIDDLECOEF_Q15_32)

extern uint32_t rearranged_twiddle_tab_stride1_arr_16_q15[2];
extern uint32_t rearranged_twiddle_tab_stride2_arr_16_q15[2];
extern uint32_t rearranged_twiddle_tab_stride3_arr_16_q15[2];
extern q15_t rearranged_twiddle_stride1_16_q15[8];
extern q15_t rearranged_twiddle_stride2_16_q15[8];
extern q15_t rearranged_twiddle_stride3_16_q15[8];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_Q15_64) || defined(ARM_TABLE_TWIDDLECOEF_Q15_128)

extern uint32_t rearranged_twiddle_tab_stride1_arr_64_q15[3];
extern uint32_t rearranged_twiddle_tab_stride2_arr_64_q15[3];
extern uint32_t rearranged_twiddle_tab_stride3_arr_64_q15[3];
extern q15_t rearranged_twiddle_stride1_64_q15[40];
extern q15_t rearranged_twiddle_stride2_64_q15[40];
extern q15_t rearranged_twiddle_stride3_64_q15[40];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_Q15_256) || defined(ARM_TABLE_TWIDDLECOEF_Q15_512)

extern uint32_t rearranged_twiddle_tab_stride1_arr_256_q15[4];
extern uint32_t rearranged_twiddle_tab_stride2_arr_256_q15[4];
extern uint32_t rearranged_twiddle_tab_stride3_arr_256_q15[4];
extern q15_t rearranged_twiddle_stride1_256_q15[168];
extern q15_t rearranged_twiddle_stride2_256_q15[168];
extern q15_t rearranged_twiddle_stride3_256_q15[168];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_Q15_1024) || defined(ARM_TABLE_TWIDDLECOEF_Q15_2048)

extern uint32_t rearranged_twiddle_tab_stride1_arr_1024_q15[5];
extern uint32_t rearranged_twiddle_tab_stride2_arr_1024_q15[5];
extern uint32_t rearranged_twiddle_tab_stride3_arr_1024_q15[5];
extern q15_t rearranged_twiddle_stride1_1024_q15[680];
extern q15_t rearranged_twiddle_stride2_1024_q15[680];
extern q15_t rearranged_twiddle_stride3_1024_q15[680];
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_TWIDDLECOEF_Q15_4096) || defined(ARM_TABLE_TWIDDLECOEF_Q15_8192)

extern uint32_t rearranged_twiddle_tab_stride1_arr_4096_q15[6];
extern uint32_t rearranged_twiddle_tab_stride2_arr_4096_q15[6];
extern uint32_t rearranged_twiddle_tab_stride3_arr_4096_q15[6];
extern q15_t rearranged_twiddle_stride1_4096_q15[2728];
extern q15_t rearranged_twiddle_stride2_4096_q15[2728];
extern q15_t rearranged_twiddle_stride3_4096_q15[2728];
#endif


#endif /* !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_FFT_ALLOW_TABLES) */

#endif /* defined(ARM_MATH_MVEI) */



#ifdef   __cplusplus
}
#endif

#endif /*_ARM_MVE_TABLES_H*/

