 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     drv_fft.h
 * @brief    header file for gpio driver
 * @version  V1.0
 * @date     11. Nov 2017
 * @model    fft
 ******************************************************************************/

#ifndef _CSI_FFT_H_
#define _CSI_FFT_H_


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
//#include <drv_common.h>

#ifdef __cplusplus
    extern "C" {
#endif

typedef enum {
    // 512-point FFT
    CSKY_MCA_FFT_LEN_512 = 0x1,
    // 256-point FFT
    CSKY_MCA_FFT_LEN_256 = 0x2,
    // 128-point FFT
    CSKY_MCA_FFT_LEN_128 = 0x4,
    // 64-point FFT
    CSKY_MCA_FFT_LEN_64 = 0x8,
    // 32-point FFT
    CSKY_MCA_FFT_LEN_32 = 0x10,
    // 16-point FFT
    CSKY_MCA_FFT_LEN_16 = 0x20,
} csky_mca_fft_len_t;

/* 8-bit fixed-point numeric type in user-defined format */
typedef int8_t fxp8_t;
/* 16-bit fixed-point numeric type in user-defined format */
typedef int16_t fxp16_t;
/* 24-bit fixed-point numeric type in user-defined format */
typedef int32_t fxp24_t;
/* 32-bit fixed-point numeric type in user-defined format */
typedef int32_t fxp32_t;
/* 64-bit fixed-point numeric type in user-defined format */
typedef int64_t fxp64_t;

/* 8-bit fixed-point numeric type in 1.0.7 format */
typedef fxp8_t q7_t;
/* 16-bit fixed-point numeric type in 1.0.15 format */
typedef fxp16_t q15_t;
/* 32-bit fixed-point numeric type in 1.15.16 format */
typedef fxp32_t q16_t;

void csky_mca_rfft_fxp32(csky_mca_fft_len_t fft_len, const fxp32_t *input, size_t input_size, fxp32_t *output);
void csky_mca_cfft_fxp32(csky_mca_fft_len_t fft_len, const fxp32_t *input, fxp32_t *output);
void csky_mca_rifft_fxp32(csky_mca_fft_len_t fft_len, const fxp32_t *input, fxp32_t *output);
void csky_mca_cifft_fxp32(csky_mca_fft_len_t fft_len, const fxp32_t *input, fxp32_t *output);
void csky_mca_power_spectrum_fxp32(csky_mca_fft_len_t fft_len, const fxp32_t *input, size_t input_size, fxp64_t *output);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_FFT_H_ */
