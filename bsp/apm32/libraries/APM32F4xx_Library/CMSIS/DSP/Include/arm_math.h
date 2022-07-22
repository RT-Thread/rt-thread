/******************************************************************************
 * @file     arm_math.h
 * @brief    Public header file for CMSIS DSP Library
 * @version  V1.9.0
 * @date     23 April 2021
 * Target Processor: Cortex-M and Cortex-A cores
 ******************************************************************************/
/*
 * Copyright (c) 2010-2021 Arm Limited or its affiliates. All rights reserved.
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

/**
   \mainpage CMSIS DSP Software Library
   *
   * \section intro Introduction
   *
   * This user manual describes the CMSIS DSP software library,
   * a suite of common signal processing functions for use on Cortex-M and Cortex-A processor
   * based devices.
   *
   * The library is divided into a number of functions each covering a specific category:
   * - Basic math functions
   * - Fast math functions
   * - Complex math functions
   * - Filtering functions
   * - Matrix functions
   * - Transform functions
   * - Motor control functions
   * - Statistical functions
   * - Support functions
   * - Interpolation functions
   * - Support Vector Machine functions (SVM)
   * - Bayes classifier functions
   * - Distance functions
   * - Quaternion functions
   *
   * The library has generally separate functions for operating on 8-bit integers, 16-bit integers,
   * 32-bit integer and 32-bit floating-point values.
   *
   * The library is providing vectorized versions of most algorthms for Helium
   * and of most f32 algorithms for Neon.
   *
   * When using a vectorized version, provide a little bit of padding after the end of
   * a buffer (3 words) because the vectorized code may read a little bit after the end
   * of a buffer. You don't have to modify your buffers but just ensure that the
   * end of buffer + padding is not outside of a memory region.
   *
   * \section using Using the Library
   *
   * The library is released in source form. It is strongly advised to compile the library using -Ofast to
   * have the best performances.
   *
   * The library functions are declared in the public file <code>arm_math.h</code> which is placed in the <code>Include</code> folder.
   * Simply include this file. If you don't want to include everything, you can also rely
   * on headers in Include/dsp folder and use only what you need.
   *
   * \section example Examples
   *
   * The library ships with a number of examples which demonstrate how to use the library functions.
   *
   * \section toolchain Toolchain Support
   *
   * The library is now tested on Fast Models building with cmake.
   * Core M0, M4, M7, M33, M55, A32 are tested.
   *
   *
   * \section preprocessor Preprocessor Macros
   *
   * Each library project have different preprocessor macros.
   *
   * - ARM_MATH_BIG_ENDIAN:
   *
   * Define macro ARM_MATH_BIG_ENDIAN to build the library for big endian targets. By default library builds for little endian targets.
   *
   * - ARM_MATH_MATRIX_CHECK:
   *
   * Define macro ARM_MATH_MATRIX_CHECK for checking on the input and output sizes of matrices
   *
   * - ARM_MATH_ROUNDING:
   *
   * Define macro ARM_MATH_ROUNDING for rounding on support functions
   *
   * - ARM_MATH_LOOPUNROLL:
   *
   * Define macro ARM_MATH_LOOPUNROLL to enable manual loop unrolling in DSP functions
   *
   * - ARM_MATH_NEON:
   *
   * Define macro ARM_MATH_NEON to enable Neon versions of the DSP functions.
   * It is not enabled by default when Neon is available because performances are
   * dependent on the compiler and target architecture.
   *
   * - ARM_MATH_NEON_EXPERIMENTAL:
   *
   * Define macro ARM_MATH_NEON_EXPERIMENTAL to enable experimental Neon versions of
   * of some DSP functions. Experimental Neon versions currently do not have better
   * performances than the scalar versions.
   *
   * - ARM_MATH_HELIUM:
   *
   * It implies the flags ARM_MATH_MVEF and ARM_MATH_MVEI and ARM_MATH_MVE_FLOAT16.
   *
   * - ARM_MATH_HELIUM_EXPERIMENTAL:
   *
   * Only taken into account when ARM_MATH_MVEF, ARM_MATH_MVEI or ARM_MATH_MVE_FLOAT16 are defined.
   * Enable some vector versions which may have worse performance than scalar
   * depending on the core / compiler configuration.
   *
   * - ARM_MATH_MVEF:
   *
   * Select Helium versions of the f32 algorithms.
   * It implies ARM_MATH_FLOAT16 and ARM_MATH_MVEI.
   *
   * - ARM_MATH_MVEI:
   *
   * Select Helium versions of the int and fixed point algorithms.
   *
   * - ARM_MATH_MVE_FLOAT16:
   *
   * MVE Float16 implementations of some algorithms (Requires MVE extension).
   *
   * - DISABLEFLOAT16:
   *
   * Disable float16 algorithms when __fp16 is not supported for a
   * specific compiler / core configuration.
   * This is only valid for scalar. When vector architecture is
   * supporting f16 then it can't be disabled.
   *
   * - ARM_MATH_AUTOVECTORIZE:
   *
   * With Helium or Neon, disable the use of vectorized code with C intrinsics
   * and use pure C instead. The vectorization is then done by the compiler.
   *
   * <hr>
   * \section pack CMSIS-DSP in ARM::CMSIS Pack
   *
   * The following files relevant to CMSIS-DSP are present in the <b>ARM::CMSIS</b> Pack directories:
   * |File/Folder                      |Content                                                                 |
   * |---------------------------------|------------------------------------------------------------------------|
   * |\b CMSIS\\Documentation\\DSP     | This documentation                                                     |
   * |\b CMSIS\\DSP\\Examples          | Example projects demonstrating the usage of the library functions      |
   * |\b CMSIS\\DSP\\Include           | DSP_Lib include files for using and building the lib
   * |\b CMSIS\\DSP\\PrivateInclude    | DSP_Lib private include files for building the lib                                               |
   * |\b CMSIS\\DSP\\Lib               | DSP_Lib binaries                                                       |
   * |\b CMSIS\\DSP\\Source            | DSP_Lib source files                                                   |
   *
   * <hr>
   * \section rev Revision History of CMSIS-DSP
   * Please refer to \ref ChangeLog_pg.
   */











/**
 * @defgroup groupExamples Examples
 */





#ifndef _ARM_MATH_H
#define _ARM_MATH_H


#include "arm_math_types.h"
#include "arm_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#include "dsp/basic_math_functions.h"
#include "dsp/interpolation_functions.h"
#include "dsp/bayes_functions.h"
#include "dsp/matrix_functions.h"
#include "dsp/complex_math_functions.h"
#include "dsp/statistics_functions.h"
#include "dsp/controller_functions.h"
#include "dsp/support_functions.h"
#include "dsp/distance_functions.h"
#include "dsp/svm_functions.h"
#include "dsp/fast_math_functions.h"
#include "dsp/transform_functions.h"
#include "dsp/filtering_functions.h"
#include "dsp/quaternion_math_functions.h"



#ifdef   __cplusplus
extern "C"
{
#endif




//#define TABLE_SPACING_Q31     0x400000
//#define TABLE_SPACING_Q15     0x80





#ifdef   __cplusplus
}
#endif


#endif /* _ARM_MATH_H */

/**
 *
 * End of file.
 */
