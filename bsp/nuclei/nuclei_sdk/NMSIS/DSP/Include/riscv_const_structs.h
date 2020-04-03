/* ----------------------------------------------------------------------
 * Project:      NMSIS DSP Library
 * Title:        riscv_const_structs.h
 * Description:  Constant structs that are initialized for user convenience.
 *               For example, some can be given as arguments to the riscv_cfft_f32() function.
 *
 * $Date:        27. January 2017
 * $Revision:    V.1.5.1
 *
 * Target Processor: RISC-V Cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2017 ARM Limited or its affiliates. All rights reserved.
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
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

#ifndef _RISCV_CONST_STRUCTS_H
#define _RISCV_CONST_STRUCTS_H

#include "riscv_math.h"
#include "riscv_common_tables.h"

   extern const riscv_cfft_instance_f32 riscv_cfft_sR_f32_len16;
   extern const riscv_cfft_instance_f32 riscv_cfft_sR_f32_len32;
   extern const riscv_cfft_instance_f32 riscv_cfft_sR_f32_len64;
   extern const riscv_cfft_instance_f32 riscv_cfft_sR_f32_len128;
   extern const riscv_cfft_instance_f32 riscv_cfft_sR_f32_len256;
   extern const riscv_cfft_instance_f32 riscv_cfft_sR_f32_len512;
   extern const riscv_cfft_instance_f32 riscv_cfft_sR_f32_len1024;
   extern const riscv_cfft_instance_f32 riscv_cfft_sR_f32_len2048;
   extern const riscv_cfft_instance_f32 riscv_cfft_sR_f32_len4096;

   extern const riscv_cfft_instance_q31 riscv_cfft_sR_q31_len16;
   extern const riscv_cfft_instance_q31 riscv_cfft_sR_q31_len32;
   extern const riscv_cfft_instance_q31 riscv_cfft_sR_q31_len64;
   extern const riscv_cfft_instance_q31 riscv_cfft_sR_q31_len128;
   extern const riscv_cfft_instance_q31 riscv_cfft_sR_q31_len256;
   extern const riscv_cfft_instance_q31 riscv_cfft_sR_q31_len512;
   extern const riscv_cfft_instance_q31 riscv_cfft_sR_q31_len1024;
   extern const riscv_cfft_instance_q31 riscv_cfft_sR_q31_len2048;
   extern const riscv_cfft_instance_q31 riscv_cfft_sR_q31_len4096;

   extern const riscv_cfft_instance_q15 riscv_cfft_sR_q15_len16;
   extern const riscv_cfft_instance_q15 riscv_cfft_sR_q15_len32;
   extern const riscv_cfft_instance_q15 riscv_cfft_sR_q15_len64;
   extern const riscv_cfft_instance_q15 riscv_cfft_sR_q15_len128;
   extern const riscv_cfft_instance_q15 riscv_cfft_sR_q15_len256;
   extern const riscv_cfft_instance_q15 riscv_cfft_sR_q15_len512;
   extern const riscv_cfft_instance_q15 riscv_cfft_sR_q15_len1024;
   extern const riscv_cfft_instance_q15 riscv_cfft_sR_q15_len2048;
   extern const riscv_cfft_instance_q15 riscv_cfft_sR_q15_len4096;

#endif
