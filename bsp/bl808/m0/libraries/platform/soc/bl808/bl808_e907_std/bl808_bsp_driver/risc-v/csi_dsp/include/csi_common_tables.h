/*
 * Copyright (C) 2016-2019 C-SKY Limited. All rights reserved.
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
 * @file     csi_common_tables.h
 * @brief    This file has extern declaration for common tables like
 *           Bitreverse, reciprocal etc which are used across different functions.
 * @version  V1.0
 * @date     20. Dec 2016
 ******************************************************************************/

#ifndef _CSI_COMMON_TABLES_H
#define _CSI_COMMON_TABLES_H

#include "csi_math.h"

extern const uint16_t csiBitRevTable[1024];
extern const q15_t csiRecipTableQ15[64];
extern const q31_t csiRecipTableQ31[64];
extern const uint32_t twiddleCoef_16[32];
extern const uint32_t twiddleCoef_32[64];
extern const uint32_t twiddleCoef_64[128];
extern const uint32_t twiddleCoef_128[256];
extern const uint32_t twiddleCoef_256[512];
extern const uint32_t twiddleCoef_512[1024];
extern const uint32_t twiddleCoef_1024[2048];
extern const uint32_t twiddleCoef_2048[4096];
extern const uint32_t twiddleCoef_4096[8192];
extern const q31_t twiddleCoef_16_q31[24];
extern const q31_t twiddleCoef_32_q31[48];
extern const q31_t twiddleCoef_64_q31[96];
extern const q31_t twiddleCoef_128_q31[192];
extern const q31_t twiddleCoef_256_q31[384];
extern const q31_t twiddleCoef_512_q31[768];
extern const q31_t twiddleCoef_1024_q31[1536];
extern const q31_t twiddleCoef_2048_q31[3072];
extern const q31_t twiddleCoef_4096_q31[6144];
extern const q15_t twiddleCoef_16_q15[24];
extern const q15_t twiddleCoef_32_q15[48];
extern const q15_t twiddleCoef_64_q15[96];
extern const q15_t twiddleCoef_128_q15[192];
extern const q15_t twiddleCoef_256_q15[384];
extern const q15_t twiddleCoef_512_q15[768];
extern const q15_t twiddleCoef_1024_q15[1536];
extern const q15_t twiddleCoef_2048_q15[3072];
extern const q15_t twiddleCoef_4096_q15[6144];
extern const float32_t twiddleCoef_rfft_32[32];
extern const float32_t twiddleCoef_rfft_64[64];
extern const float32_t twiddleCoef_rfft_128[128];
extern const float32_t twiddleCoef_rfft_256[256];
extern const float32_t twiddleCoef_rfft_512[512];
extern const float32_t twiddleCoef_rfft_1024[1024];
extern const float32_t twiddleCoef_rfft_2048[2048];
extern const float32_t twiddleCoef_rfft_4096[4096];
extern const float32_t twiddleCoef_rfft_8192[8192];

extern const q15_t twiddleCoef_fast_16_q15[24];
extern const q15_t twiddleCoef_fast_32_q15[56];
extern const q15_t twiddleCoef_fast_64_q15[120];
extern const q15_t twiddleCoef_fast_128_q15[248];
extern const q15_t twiddleCoef_fast_256_q15[504];
extern const q15_t twiddleCoef_fast_512_q15[1016];
extern const q15_t twiddleCoef_fast_1024_q15[2040];
extern const q15_t twiddleCoef_fast_2048_q15[4088];
extern const q15_t twiddleCoef_fast_4096_q15[8184];

extern const q31_t twiddleCoef_fast_16_q31[24];
extern const q31_t twiddleCoef_fast_32_q31[56];
extern const q31_t twiddleCoef_fast_64_q31[120];
extern const q31_t twiddleCoef_fast_128_q31[248];
extern const q31_t twiddleCoef_fast_256_q31[504];
extern const q31_t twiddleCoef_fast_512_q31[1016];
extern const q31_t twiddleCoef_fast_1024_q31[2040];
extern const q31_t twiddleCoef_fast_2048_q31[4088];
extern const q31_t twiddleCoef_fast_4096_q31[8184];

extern const uint32_t twiddleCoef_fast_16[24];
extern const uint32_t twiddleCoef_fast_32[56];
extern const uint32_t twiddleCoef_fast_64[120];
extern const uint32_t twiddleCoef_fast_128[248];
extern const uint32_t twiddleCoef_fast_256[504];
extern const uint32_t twiddleCoef_fast_512[1016];
extern const uint32_t twiddleCoef_fast_1024[2040];
extern const uint32_t twiddleCoef_fast_2048[4088];
extern const uint32_t twiddleCoef_fast_4096[8184];

extern const q15_t realCoefAQ15_8192[8192];
extern const q31_t realCoefAQ31_8192[8192];
extern const q15_t realCoefBQ15_8192[8192];
extern const q31_t realCoefBQ31_8192[8192];

/*Tables for RFFT.*/
extern const q15_t ALIGN4 realCoefAQ15_32[32];
extern const q15_t ALIGN4 realCoefAQ15_64[64];
extern const q15_t ALIGN4 realCoefAQ15_128[128];
extern const q15_t ALIGN4 realCoefAQ15_256[256];
extern const q15_t ALIGN4 realCoefAQ15_512[512];
extern const q15_t ALIGN4 realCoefAQ15_1024[1024];
extern const q15_t ALIGN4 realCoefAQ15_2048[2048];
extern const q15_t ALIGN4 realCoefAQ15_4096[4096];

extern const q15_t ALIGN4 realCoefBQ15_32[32];
extern const q15_t ALIGN4 realCoefBQ15_64[64];
extern const q15_t ALIGN4 realCoefBQ15_128[128];
extern const q15_t ALIGN4 realCoefBQ15_256[256];
extern const q15_t ALIGN4 realCoefBQ15_512[512];
extern const q15_t ALIGN4 realCoefBQ15_1024[1024];
extern const q15_t ALIGN4 realCoefBQ15_2048[2048];
extern const q15_t ALIGN4 realCoefBQ15_4096[4096];

extern const q31_t realCoefAQ31_32[32];
extern const q31_t realCoefAQ31_64[64];
extern const q31_t realCoefAQ31_128[128];
extern const q31_t realCoefAQ31_256[256];
extern const q31_t realCoefAQ31_512[512];
extern const q31_t realCoefAQ31_1024[1024];
extern const q31_t realCoefAQ31_2048[2048];
extern const q31_t realCoefAQ31_4096[4096];

extern const q31_t realCoefBQ31_32[32];
extern const q31_t realCoefBQ31_64[64];
extern const q31_t realCoefBQ31_128[128];
extern const q31_t realCoefBQ31_256[256];
extern const q31_t realCoefBQ31_512[512];
extern const q31_t realCoefBQ31_1024[1024];
extern const q31_t realCoefBQ31_2048[2048];
extern const q31_t realCoefBQ31_4096[4096];


extern const float32_t realCoefA[8192];
extern const float32_t realCoefB[8192];

extern const csi_cfft_instance_q15 csi_cfft_fast_sR_q15_len16;
extern const csi_cfft_instance_q15 csi_cfft_fast_sR_q15_len32;
extern const csi_cfft_instance_q15 csi_cfft_fast_sR_q15_len64;
extern const csi_cfft_instance_q15 csi_cfft_fast_sR_q15_len128;
extern const csi_cfft_instance_q15 csi_cfft_fast_sR_q15_len256;
extern const csi_cfft_instance_q15 csi_cfft_fast_sR_q15_len512;
extern const csi_cfft_instance_q15 csi_cfft_fast_sR_q15_len1024;
extern const csi_cfft_instance_q15 csi_cfft_fast_sR_q15_len2048;
extern const csi_cfft_instance_q15 csi_cfft_fast_sR_q15_len4096;

extern const csi_cfft_instance_q31 csi_cfft_fast_sR_q31_len16;
extern const csi_cfft_instance_q31 csi_cfft_fast_sR_q31_len32;
extern const csi_cfft_instance_q31 csi_cfft_fast_sR_q31_len64;
extern const csi_cfft_instance_q31 csi_cfft_fast_sR_q31_len128;
extern const csi_cfft_instance_q31 csi_cfft_fast_sR_q31_len256;
extern const csi_cfft_instance_q31 csi_cfft_fast_sR_q31_len512;
extern const csi_cfft_instance_q31 csi_cfft_fast_sR_q31_len1024;
extern const csi_cfft_instance_q31 csi_cfft_fast_sR_q31_len2048;
extern const csi_cfft_instance_q31 csi_cfft_fast_sR_q31_len4096;

extern csi_rfft_fast_instance_q15 csi_rfft_fast_sR_q15_len32;
extern csi_rfft_fast_instance_q15 csi_rfft_fast_sR_q15_len64;
extern csi_rfft_fast_instance_q15 csi_rfft_fast_sR_q15_len128;
extern csi_rfft_fast_instance_q15 csi_rfft_fast_sR_q15_len256;
extern csi_rfft_fast_instance_q15 csi_rfft_fast_sR_q15_len512;
extern csi_rfft_fast_instance_q15 csi_rfft_fast_sR_q15_len1024;
extern csi_rfft_fast_instance_q15 csi_rfft_fast_sR_q15_len2048;
extern csi_rfft_fast_instance_q15 csi_rfft_fast_sR_q15_len4096;
extern csi_rfft_fast_instance_q15 csi_rfft_fast_sR_q15_len8192;

extern csi_rfft_fast_instance_q15 csi_inv_rfft_fast_sR_q15_len32;
extern csi_rfft_fast_instance_q15 csi_inv_rfft_fast_sR_q15_len64;
extern csi_rfft_fast_instance_q15 csi_inv_rfft_fast_sR_q15_len128;
extern csi_rfft_fast_instance_q15 csi_inv_rfft_fast_sR_q15_len256;
extern csi_rfft_fast_instance_q15 csi_inv_rfft_fast_sR_q15_len512;
extern csi_rfft_fast_instance_q15 csi_inv_rfft_fast_sR_q15_len1024;
extern csi_rfft_fast_instance_q15 csi_inv_rfft_fast_sR_q15_len2048;
extern csi_rfft_fast_instance_q15 csi_inv_rfft_fast_sR_q15_len4096;
extern csi_rfft_fast_instance_q15 csi_inv_rfft_fast_sR_q15_len8192;

extern csi_rfft_fast_instance_q31 csi_rfft_fast_sR_q31_len32;
extern csi_rfft_fast_instance_q31 csi_rfft_fast_sR_q31_len64;
extern csi_rfft_fast_instance_q31 csi_rfft_fast_sR_q31_len128;
extern csi_rfft_fast_instance_q31 csi_rfft_fast_sR_q31_len256;
extern csi_rfft_fast_instance_q31 csi_rfft_fast_sR_q31_len512;
extern csi_rfft_fast_instance_q31 csi_rfft_fast_sR_q31_len1024;
extern csi_rfft_fast_instance_q31 csi_rfft_fast_sR_q31_len2048;
extern csi_rfft_fast_instance_q31 csi_rfft_fast_sR_q31_len4096;
extern csi_rfft_fast_instance_q31 csi_rfft_fast_sR_q31_len8192;

extern csi_rfft_fast_instance_q31 csi_inv_rfft_fast_sR_q31_len32;
extern csi_rfft_fast_instance_q31 csi_inv_rfft_fast_sR_q31_len64;
extern csi_rfft_fast_instance_q31 csi_inv_rfft_fast_sR_q31_len128;
extern csi_rfft_fast_instance_q31 csi_inv_rfft_fast_sR_q31_len256;
extern csi_rfft_fast_instance_q31 csi_inv_rfft_fast_sR_q31_len512;
extern csi_rfft_fast_instance_q31 csi_inv_rfft_fast_sR_q31_len1024;
extern csi_rfft_fast_instance_q31 csi_inv_rfft_fast_sR_q31_len2048;
extern csi_rfft_fast_instance_q31 csi_inv_rfft_fast_sR_q31_len4096;
extern csi_rfft_fast_instance_q31 csi_inv_rfft_fast_sR_q31_len8192;

extern csi_dct4_fast_instance_q15 csi_dct4_fast_sR_q15_len128;
extern csi_dct4_fast_instance_q15 csi_dct4_fast_sR_q15_len512;
extern csi_dct4_fast_instance_q15 csi_dct4_fast_sR_q15_len2048;
extern csi_dct4_fast_instance_q15 csi_dct4_fast_sR_q15_len8192;

extern csi_dct4_fast_instance_q31 csi_dct4_fast_sR_q31_len128;
extern csi_dct4_fast_instance_q31 csi_dct4_fast_sR_q31_len512;
extern csi_dct4_fast_instance_q31 csi_dct4_fast_sR_q31_len2048;
extern csi_dct4_fast_instance_q31 csi_dct4_fast_sR_q31_len8192;

/*Tables for DCT4*/
#ifndef CSI_OPT_WEIGHT
extern const q15_t ALIGN4 WeightsQ15_128[256];
extern const q15_t ALIGN4 WeightsQ15_512[1024];
extern const q15_t ALIGN4 WeightsQ15_2048[4096];
extern const q15_t ALIGN4 WeightsQ15_8192[16384];
#else
extern const q15_t ALIGN4 WeightsQ15_128[128+2];
extern const q15_t ALIGN4 WeightsQ15_512[512+2];
extern const q15_t ALIGN4 WeightsQ15_2048[2048+2];
extern const q15_t ALIGN4 WeightsQ15_8192[8192+2];
#endif
extern const q15_t ALIGN4 cos_factorsQ15_128[128];
extern const q15_t ALIGN4 cos_factorsQ15_512[512];
extern const q15_t ALIGN4 cos_factorsQ15_2048[2048];
extern const q15_t ALIGN4 cos_factorsQ15_8192[8192];

#ifndef CSI_OPT_WEIGHT
extern const q31_t WeightsQ31_128[256];
extern const q31_t WeightsQ31_512[1024];
extern const q31_t WeightsQ31_2048[4096];
extern const q31_t WeightsQ31_8192[16384];
#else
extern const q31_t WeightsQ31_128[128+2];
extern const q31_t WeightsQ31_512[512+2];
extern const q31_t WeightsQ31_2048[2048+2];
extern const q31_t WeightsQ31_8192[8192+2];
#endif

extern const q31_t cos_factorsQ31_128[128];
extern const q31_t cos_factorsQ31_512[512];
extern const q31_t cos_factorsQ31_2048[2048];
extern const q31_t cos_factorsQ31_8192[8192];

#ifndef CSI_OPT_WEIGHT
extern const float32_t Weights_128[256];
extern const float32_t Weights_512[1024];
extern const float32_t Weights_2048[4096];
extern const float32_t Weights_8192[16384];

#else
extern const float32_t Weights_128[128+2];
extern const float32_t Weights_512[512+2];
extern const float32_t Weights_2048[2048+2];
extern const float32_t Weights_8192[8192+2];
#endif
extern const float32_t cos_factors_128[128];
extern const float32_t cos_factors_512[512];
extern const float32_t cos_factors_2048[2048];
extern const float32_t cos_factors_8192[8192];

/* floating-point bit reversal tables */
#define CSIBITREVINDEXTABLE_16_TABLE_LENGTH ((uint16_t)20  )
#define CSIBITREVINDEXTABLE_32_TABLE_LENGTH ((uint16_t)48  )
#define CSIBITREVINDEXTABLE_64_TABLE_LENGTH ((uint16_t)56  )
#define CSIBITREVINDEXTABLE_128_TABLE_LENGTH ((uint16_t)208 )
#define CSIBITREVINDEXTABLE_256_TABLE_LENGTH ((uint16_t)440 )
#define CSIBITREVINDEXTABLE_512_TABLE_LENGTH ((uint16_t)448 )
#define CSIBITREVINDEXTABLE_1024_TABLE_LENGTH ((uint16_t)1800)
#define CSIBITREVINDEXTABLE_2048_TABLE_LENGTH ((uint16_t)3808)
#define CSIBITREVINDEXTABLE_4096_TABLE_LENGTH ((uint16_t)4032)

extern const uint16_t csiBitRevIndexTable16[CSIBITREVINDEXTABLE_16_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable32[CSIBITREVINDEXTABLE_32_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable64[CSIBITREVINDEXTABLE_64_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable128[CSIBITREVINDEXTABLE_128_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable256[CSIBITREVINDEXTABLE_256_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable512[CSIBITREVINDEXTABLE_512_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable1024[CSIBITREVINDEXTABLE_1024_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable2048[CSIBITREVINDEXTABLE_2048_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable4096[CSIBITREVINDEXTABLE_4096_TABLE_LENGTH];

/* fixed-point bit reversal tables */
#define CSIBITREVINDEXTABLE_FIXED_16_TABLE_LENGTH ((uint16_t)12  )
#define CSIBITREVINDEXTABLE_FIXED_32_TABLE_LENGTH ((uint16_t)24  )
#define CSIBITREVINDEXTABLE_FIXED_64_TABLE_LENGTH ((uint16_t)56  )
#define CSIBITREVINDEXTABLE_FIXED_128_TABLE_LENGTH ((uint16_t)112 )
#define CSIBITREVINDEXTABLE_FIXED_256_TABLE_LENGTH ((uint16_t)240 )
#define CSIBITREVINDEXTABLE_FIXED_512_TABLE_LENGTH ((uint16_t)480 )
#define CSIBITREVINDEXTABLE_FIXED_1024_TABLE_LENGTH ((uint16_t)992 )
#define CSIBITREVINDEXTABLE_FIXED_2048_TABLE_LENGTH ((uint16_t)1984)
#define CSIBITREVINDEXTABLE_FIXED_4096_TABLE_LENGTH ((uint16_t)4032)

extern const uint16_t csiBitRevIndexTable_fixed_16[CSIBITREVINDEXTABLE_FIXED_16_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable_fixed_32[CSIBITREVINDEXTABLE_FIXED_32_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable_fixed_64[CSIBITREVINDEXTABLE_FIXED_64_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable_fixed_128[CSIBITREVINDEXTABLE_FIXED_128_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable_fixed_256[CSIBITREVINDEXTABLE_FIXED_256_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable_fixed_512[CSIBITREVINDEXTABLE_FIXED_512_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable_fixed_1024[CSIBITREVINDEXTABLE_FIXED_1024_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable_fixed_2048[CSIBITREVINDEXTABLE_FIXED_2048_TABLE_LENGTH];
extern const uint16_t csiBitRevIndexTable_fixed_4096[CSIBITREVINDEXTABLE_FIXED_4096_TABLE_LENGTH];

/* Tables for Fast Math Sine and Cosine */
extern const float32_t sinTable_f32[FAST_MATH_TABLE_SIZE + 1];
extern const q31_t sinTable_q31[FAST_MATH_TABLE_SIZE + 1];
extern const q15_t sinTable_q15[FAST_MATH_TABLE_SIZE + 1];

#endif /*  CSI_COMMON_TABLES_H */
