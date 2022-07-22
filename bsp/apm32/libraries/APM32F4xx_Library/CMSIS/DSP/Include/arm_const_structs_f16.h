/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_const_structs_f16.h
 * Description:  Constant structs that are initialized for user convenience.
 *               For example, some can be given as arguments to the arm_cfft_f16() function.
 *
 * @version  V1.9.0
 * @date     23 April 2021
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

#ifndef _ARM_CONST_STRUCTS_F16_H
#define _ARM_CONST_STRUCTS_F16_H

#include "arm_math_types_f16.h"
#include "arm_common_tables.h"
#include "arm_common_tables_f16.h"
#include "dsp/transform_functions_f16.h"

#ifdef   __cplusplus
extern "C"
{
#endif

#if !defined(__CC_ARM) && defined(ARM_FLOAT16_SUPPORTED)
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_F16_16) && defined(ARM_TABLE_BITREVIDX_FLT_16))
   extern const arm_cfft_instance_f16 arm_cfft_sR_f16_len16;
   #endif
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_F16_32) && defined(ARM_TABLE_BITREVIDX_FLT_32))
   extern const arm_cfft_instance_f16 arm_cfft_sR_f16_len32;
    #endif
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_F16_64) && defined(ARM_TABLE_BITREVIDX_FLT_64))
   extern const arm_cfft_instance_f16 arm_cfft_sR_f16_len64;
    #endif
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_F16_128) && defined(ARM_TABLE_BITREVIDX_FLT_128))
   extern const arm_cfft_instance_f16 arm_cfft_sR_f16_len128;
    #endif
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_F16_256) && defined(ARM_TABLE_BITREVIDX_FLT_256))
   extern const arm_cfft_instance_f16 arm_cfft_sR_f16_len256;
    #endif
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_F16_512) && defined(ARM_TABLE_BITREVIDX_FLT_512))
   extern const arm_cfft_instance_f16 arm_cfft_sR_f16_len512;
    #endif
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_F16_1024) && defined(ARM_TABLE_BITREVIDX_FLT_1024))
   extern const arm_cfft_instance_f16 arm_cfft_sR_f16_len1024;
    #endif
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_F16_2048) && defined(ARM_TABLE_BITREVIDX_FLT_2048))
   extern const arm_cfft_instance_f16 arm_cfft_sR_f16_len2048;
    #endif
  #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_F16_4096) && defined(ARM_TABLE_BITREVIDX_FLT_4096))
   extern const arm_cfft_instance_f16 arm_cfft_sR_f16_len4096;
  #endif
#endif

#ifdef   __cplusplus
}
#endif

#endif
