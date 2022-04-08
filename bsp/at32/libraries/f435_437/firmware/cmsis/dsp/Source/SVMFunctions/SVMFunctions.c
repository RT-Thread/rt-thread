/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        BayesFunctions.c
 * Description:  Combination of all SVM function source files.
 *
 * $Date:        16. March 2020
 * $Revision:    V1.0.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2020 ARM Limited or its affiliates. All rights reserved.
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

#include "arm_svm_linear_init_f32.c"
#include "arm_svm_linear_predict_f32.c"
#include "arm_svm_polynomial_init_f32.c"
#include "arm_svm_polynomial_predict_f32.c"
#include "arm_svm_rbf_init_f32.c"
#include "arm_svm_rbf_predict_f32.c"
#include "arm_svm_sigmoid_init_f32.c"
#include "arm_svm_sigmoid_predict_f32.c"
