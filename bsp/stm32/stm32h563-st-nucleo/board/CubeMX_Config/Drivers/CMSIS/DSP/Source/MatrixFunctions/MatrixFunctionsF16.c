/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        MatrixFunctions.c
 * Description:  Combination of all matrix function f16 source files.
 *
 * $Date:        18. March 2020
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

#include "arm_mat_add_f16.c"
#include "arm_mat_sub_f16.c"
#include "arm_mat_trans_f16.c"
#include "arm_mat_scale_f16.c"
#include "arm_mat_mult_f16.c"
#include "arm_mat_vec_mult_f16.c"
#include "arm_mat_cmplx_trans_f16.c"
#include "arm_mat_cmplx_mult_f16.c"
#include "arm_mat_inverse_f16.c"
#include "arm_mat_init_f16.c"
#include "arm_mat_cholesky_f16.c"
#include "arm_mat_solve_upper_triangular_f16.c"
#include "arm_mat_solve_lower_triangular_f16.c"
