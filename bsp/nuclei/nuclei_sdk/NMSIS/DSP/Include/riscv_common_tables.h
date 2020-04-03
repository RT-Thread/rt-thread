/* ----------------------------------------------------------------------
 * Project:      NMSIS DSP Library
 * Title:        riscv_common_tables.h
 * Description:  Extern declaration for common tables
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

#ifndef _RISCV_COMMON_TABLES_H
#define _RISCV_COMMON_TABLES_H

#include "riscv_math.h"

#if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_FFT_ALLOW_TABLES) 

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREV_1024)
    extern const uint16_t riscvBitRevTable[1024];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_F32_16)
    extern const float32_t twiddleCoef_16[32];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_F32_32)
    extern const float32_t twiddleCoef_32[64];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_F32_64)
    extern const float32_t twiddleCoef_64[128];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_F32_128)
    extern const float32_t twiddleCoef_128[256];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_F32_256)
    extern const float32_t twiddleCoef_256[512];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_F32_512)
    extern const float32_t twiddleCoef_512[1024];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_F32_1024)
    extern const float32_t twiddleCoef_1024[2048];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_F32_2048)
    extern const float32_t twiddleCoef_2048[4096];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_F32_4096)
    extern const float32_t twiddleCoef_4096[8192];
    #define twiddleCoef twiddleCoef_4096
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q31_16)
    extern const q31_t twiddleCoef_16_q31[24];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q31_32)
    extern const q31_t twiddleCoef_32_q31[48];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q31_64)
    extern const q31_t twiddleCoef_64_q31[96];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q31_128)
    extern const q31_t twiddleCoef_128_q31[192];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q31_256)
    extern const q31_t twiddleCoef_256_q31[384];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q31_512)
    extern const q31_t twiddleCoef_512_q31[768];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q31_1024)
    extern const q31_t twiddleCoef_1024_q31[1536];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q31_2048)
    extern const q31_t twiddleCoef_2048_q31[3072];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q31_4096)
    extern const q31_t twiddleCoef_4096_q31[6144];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q15_16)
    extern const q15_t twiddleCoef_16_q15[24];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q15_32)
    extern const q15_t twiddleCoef_32_q15[48];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q15_64)
    extern const q15_t twiddleCoef_64_q15[96];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q15_128)
    extern const q15_t twiddleCoef_128_q15[192];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q15_256)
    extern const q15_t twiddleCoef_256_q15[384];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q15_512)
    extern const q15_t twiddleCoef_512_q15[768];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q15_1024)
    extern const q15_t twiddleCoef_1024_q15[1536];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q15_2048)
    extern const q15_t twiddleCoef_2048_q15[3072];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_Q15_4096)
    extern const q15_t twiddleCoef_4096_q15[6144];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_RFFT_F32_32)
    extern const float32_t twiddleCoef_rfft_32[32];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_RFFT_F32_64)
    extern const float32_t twiddleCoef_rfft_64[64];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_RFFT_F32_128)
    extern const float32_t twiddleCoef_rfft_128[128];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_RFFT_F32_256)
    extern const float32_t twiddleCoef_rfft_256[256];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_RFFT_F32_512)
    extern const float32_t twiddleCoef_rfft_512[512];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_RFFT_F32_1024)
    extern const float32_t twiddleCoef_rfft_1024[1024];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_RFFT_F32_2048)
    extern const float32_t twiddleCoef_rfft_2048[2048];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_TWIDDLECOEF_RFFT_F32_4096)
    extern const float32_t twiddleCoef_rfft_4096[4096];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  /* floating-point bit reversal tables */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FLT_16)
    #define RISCVBITREVINDEXTABLE_16_TABLE_LENGTH ((uint16_t)20)
    extern const uint16_t riscvBitRevIndexTable16[RISCVBITREVINDEXTABLE_16_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FLT_32)
    #define RISCVBITREVINDEXTABLE_32_TABLE_LENGTH ((uint16_t)48)
    extern const uint16_t riscvBitRevIndexTable32[RISCVBITREVINDEXTABLE_32_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FLT_64)
    #define RISCVBITREVINDEXTABLE_64_TABLE_LENGTH ((uint16_t)56)
    extern const uint16_t riscvBitRevIndexTable64[RISCVBITREVINDEXTABLE_64_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FLT_128)
    #define RISCVBITREVINDEXTABLE_128_TABLE_LENGTH ((uint16_t)208)
    extern const uint16_t riscvBitRevIndexTable128[RISCVBITREVINDEXTABLE_128_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FLT_256)
    #define RISCVBITREVINDEXTABLE_256_TABLE_LENGTH ((uint16_t)440)
    extern const uint16_t riscvBitRevIndexTable256[RISCVBITREVINDEXTABLE_256_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FLT_512)
    #define RISCVBITREVINDEXTABLE_512_TABLE_LENGTH ((uint16_t)448)
    extern const uint16_t riscvBitRevIndexTable512[RISCVBITREVINDEXTABLE_512_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FLT_1024)
    #define RISCVBITREVINDEXTABLE_1024_TABLE_LENGTH ((uint16_t)1800)
    extern const uint16_t riscvBitRevIndexTable1024[RISCVBITREVINDEXTABLE_1024_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FLT_2048)
    #define RISCVBITREVINDEXTABLE_2048_TABLE_LENGTH ((uint16_t)3808)
    extern const uint16_t riscvBitRevIndexTable2048[RISCVBITREVINDEXTABLE_2048_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FLT_4096)
    #define RISCVBITREVINDEXTABLE_4096_TABLE_LENGTH ((uint16_t)4032)
    extern const uint16_t riscvBitRevIndexTable4096[RISCVBITREVINDEXTABLE_4096_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  
  /* fixed-point bit reversal tables */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FXT_16)
    #define RISCVBITREVINDEXTABLE_FIXED_16_TABLE_LENGTH ((uint16_t)12)
    extern const uint16_t riscvBitRevIndexTable_fixed_16[RISCVBITREVINDEXTABLE_FIXED_16_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FXT_32)
    #define RISCVBITREVINDEXTABLE_FIXED_32_TABLE_LENGTH ((uint16_t)24)
    extern const uint16_t riscvBitRevIndexTable_fixed_32[RISCVBITREVINDEXTABLE_FIXED_32_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FXT_64)
    #define RISCVBITREVINDEXTABLE_FIXED_64_TABLE_LENGTH ((uint16_t)56)
    extern const uint16_t riscvBitRevIndexTable_fixed_64[RISCVBITREVINDEXTABLE_FIXED_64_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FXT_128)
    #define RISCVBITREVINDEXTABLE_FIXED_128_TABLE_LENGTH ((uint16_t)112)
    extern const uint16_t riscvBitRevIndexTable_fixed_128[RISCVBITREVINDEXTABLE_FIXED_128_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FXT_256)
    #define RISCVBITREVINDEXTABLE_FIXED_256_TABLE_LENGTH ((uint16_t)240)
    extern const uint16_t riscvBitRevIndexTable_fixed_256[RISCVBITREVINDEXTABLE_FIXED_256_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FXT_512)
    #define RISCVBITREVINDEXTABLE_FIXED_512_TABLE_LENGTH ((uint16_t)480)
    extern const uint16_t riscvBitRevIndexTable_fixed_512[RISCVBITREVINDEXTABLE_FIXED_512_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FXT_1024)
    #define RISCVBITREVINDEXTABLE_FIXED_1024_TABLE_LENGTH ((uint16_t)992)
    extern const uint16_t riscvBitRevIndexTable_fixed_1024[RISCVBITREVINDEXTABLE_FIXED_1024_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FXT_2048)
    #define RISCVBITREVINDEXTABLE_FIXED_2048_TABLE_LENGTH ((uint16_t)1984)
    extern const uint16_t riscvBitRevIndexTable_fixed_2048[RISCVBITREVINDEXTABLE_FIXED_2048_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_BITREVIDX_FXT_4096)
    #define RISCVBITREVINDEXTABLE_FIXED_4096_TABLE_LENGTH ((uint16_t)4032)
    extern const uint16_t riscvBitRevIndexTable_fixed_4096[RISCVBITREVINDEXTABLE_FIXED_4096_TABLE_LENGTH];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) */

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_REALCOEF_F32)
    extern const float32_t realCoefA[8192];
    extern const float32_t realCoefB[8192];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_REALCOEF_Q31)
    extern const q31_t realCoefAQ31[8192];
    extern const q31_t realCoefBQ31[8192];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_REALCOEF_Q15)
    extern const q15_t realCoefAQ15[8192];
    extern const q15_t realCoefBQ15[8192];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_DCT4_F32_128)
    extern const float32_t Weights_128[256];
    extern const float32_t cos_factors_128[128];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_DCT4_F32_512)
    extern const float32_t Weights_512[1024];
    extern const float32_t cos_factors_512[512];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_DCT4_F32_2048)
    extern const float32_t Weights_2048[4096];
    extern const float32_t cos_factors_2048[2048];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_DCT4_F32_8192)
    extern const float32_t Weights_8192[16384];
    extern const float32_t cos_factors_8192[8192];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_DCT4_Q15_128)
    extern const q15_t WeightsQ15_128[256];
    extern const q15_t cos_factorsQ15_128[128];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_DCT4_Q15_512)
    extern const q15_t WeightsQ15_512[1024];
    extern const q15_t cos_factorsQ15_512[512];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_DCT4_Q15_2048)
    extern const q15_t WeightsQ15_2048[4096];
    extern const q15_t cos_factorsQ15_2048[2048];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_DCT4_Q15_8192)
    extern const q15_t WeightsQ15_8192[16384];
    extern const q15_t cos_factorsQ15_8192[8192];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_DCT4_Q31_128)  
    extern const q31_t WeightsQ31_128[256];
    extern const q31_t cos_factorsQ31_128[128];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_DCT4_Q31_512) 
    extern const q31_t WeightsQ31_512[1024];
    extern const q31_t cos_factorsQ31_512[512];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_DCT4_Q31_2048) 
    extern const q31_t WeightsQ31_2048[4096];
    extern const q31_t cos_factorsQ31_2048[2048];
  #endif

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FFT_TABLES) || defined(RISCV_TABLE_DCT4_Q31_8192) 
    extern const q31_t WeightsQ31_8192[16384];
    extern const q31_t cos_factorsQ31_8192[8192];
  #endif
    
#endif /* if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_FFT_TABLES) */

#if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_FAST_ALLOW_TABLES)

  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FAST_TABLES) || defined(RISCV_TABLE_RECIP_Q15)
    extern const q15_t riscvRecipTableQ15[64];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) defined(RISCV_ALL_FAST_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FAST_TABLES) || defined(RISCV_TABLE_RECIP_Q31)
    extern const q31_t riscvRecipTableQ31[64];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) defined(RISCV_ALL_FAST_TABLES) */
  
  /* Tables for Fast Math Sine and Cosine */
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FAST_TABLES) || defined(RISCV_TABLE_SIN_F32)
    extern const float32_t sinTable_f32[FAST_MATH_TABLE_SIZE + 1];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) defined(RISCV_ALL_FAST_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FAST_TABLES) || defined(RISCV_TABLE_SIN_Q31)
    extern const q31_t sinTable_q31[FAST_MATH_TABLE_SIZE + 1];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) defined(RISCV_ALL_FAST_TABLES) */
  
  #if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_ALL_FAST_TABLES) || defined(RISCV_TABLE_SIN_Q15)
    extern const q15_t sinTable_q15[FAST_MATH_TABLE_SIZE + 1];
  #endif /* !defined(RISCV_DSP_CONFIG_TABLES) defined(RISCV_ALL_FAST_TABLES) */

#endif /* if !defined(RISCV_DSP_CONFIG_TABLES) || defined(RISCV_FAST_TABLES) */

#endif /*  RISCV_COMMON_TABLES_H */
