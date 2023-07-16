/******************************************************************************
 * @file     arm_vec_fft.h
 * @brief    Private header file for CMSIS DSP Library
 * @version  V1.7.0
 * @date     07. January 2020
 ******************************************************************************/
/*
 * Copyright (c) 2010-2020 Arm Limited or its affiliates. All rights reserved.
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

#ifndef _ARM_VEC_FFT_H_
#define _ARM_VEC_FFT_H_

#include "arm_math.h"
#include "arm_helium_utils.h"

#ifdef   __cplusplus
extern "C"
{
#endif

#if (defined(ARM_MATH_MVEF) || defined(ARM_MATH_MVEI) || defined(ARM_MATH_HELIUM)) && !defined(ARM_MATH_AUTOVECTORIZE)

#define MVE_CMPLX_ADD_A_ixB(A, B)           vcaddq_rot90(A,B)
#define MVE_CMPLX_SUB_A_ixB(A,B)            vcaddq_rot270(A,B)
#define MVE_CMPLX_MULT_FLT_AxB(A,B)         vcmlaq_rot90(vcmulq(A, B), A, B)
#define MVE_CMPLX_MULT_FLT_Conj_AxB(A,B)    vcmlaq_rot270(vcmulq(A, B), A, B)

#define MVE_CMPLX_MULT_FX_AxB(A,B)          vqdmladhxq(vqdmlsdhq((__typeof(A))vuninitializedq_s32(), A, B), A, B);
#define MVE_CMPLX_MULT_FX_AxConjB(A,B)      vqdmladhq(vqdmlsdhxq((__typeof(A))vuninitializedq_s32(), A, B), A, B);

#define MVE_CMPLX_ADD_FX_A_ixB(A, B)        vhcaddq_rot90(A,B)
#define MVE_CMPLX_SUB_FX_A_ixB(A,B)         vhcaddq_rot270(A,B)


#endif /* (defined(ARM_MATH_MVEF) || defined(ARM_MATH_HELIUM)) && !defined(ARM_MATH_AUTOVECTORIZE)*/


#ifdef   __cplusplus
}
#endif


#endif /* _ARM_VEC_FFT_H_ */