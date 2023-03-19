/*
 * Copyright (C) 2016-2020 T-head Limited. All rights reserved.
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

/******************************************************************************
 * @file     csi_const_structs.h
 * @brief    Constant structs that are initialized for user convenience.
 * @version  V1.0
 * @date     Feb. 2020
 ******************************************************************************/


#ifndef _RISCV_CONST_STRUCTS_H
#define _RISCV_CONST_STRUCTS_H

#include "csi_math.h"
#include "csi_common_tables.h"

extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len16;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len32;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len64;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len128;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len256;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len512;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len1024;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len2048;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len4096;

extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len16;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len32;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len64;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len128;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len256;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len512;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len1024;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len2048;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len4096;

extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len16;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len32;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len64;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len128;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len256;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len512;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len1024;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len2048;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len4096;

extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len16 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len32 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len64 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len128 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len256 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len512 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len1024 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len2048 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len4096 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len16 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len32 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len64 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len128 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len256 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len512 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len1024 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len2048 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len4096 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len16 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len32 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len64 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len128 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len256 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len512 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len1024 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len2048 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len4096 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len32 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len64 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len128 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len256 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len512 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len1024 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len2048 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len4096 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len8192 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len32 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len64 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len128 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len256 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len512 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len1024 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len2048 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len4096 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len8192 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len32 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len64 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len128 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len256 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len512 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len1024 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len2048 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len4096 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len8192 ;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len32;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len64;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len128;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len256;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len512;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len1024;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len2048;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len4096;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len8192;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len32;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len64;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len128;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len256;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len512;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len1024;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len2048;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len4096;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len8192;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len32;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len64;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len128;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len256;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len512;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len1024;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len2048;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len4096;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len8192;
extern const csi_dct4_instance_q31 csi_dct4_sR_q31_len128;
extern const csi_dct4_instance_q31 csi_dct4_sR_q31_len512;
extern const csi_dct4_instance_q31 csi_dct4_sR_q31_len2048;
extern const csi_dct4_instance_q31 csi_dct4_sR_q31_len8192;
extern const csi_dct4_instance_q15 csi_dct4_sR_q15_len128;
extern const csi_dct4_instance_q15 csi_dct4_sR_q15_len512;
extern const csi_dct4_instance_q15 csi_dct4_sR_q15_len2048;
extern const csi_dct4_instance_q15 csi_dct4_sR_q15_len8192;
extern const csi_dct4_instance_f32 csi_dct4_sR_f32_len128;
extern const csi_dct4_instance_f32 csi_dct4_sR_f32_len512;
extern const csi_dct4_instance_f32 csi_dct4_sR_f32_len2048;
extern const csi_dct4_instance_f32 csi_dct4_sR_f32_len8192;

#endif
