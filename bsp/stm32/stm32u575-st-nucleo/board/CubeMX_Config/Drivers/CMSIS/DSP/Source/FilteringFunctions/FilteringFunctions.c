/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        FilteringFunctions.c
 * Description:  Combination of all filtering function source files.
 *
 * $Date:        18. March 2019
 * $Revision:    V1.0.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2019 ARM Limited or its affiliates. All rights reserved.
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

#include "arm_biquad_cascade_df1_32x64_init_q31.c"
#include "arm_biquad_cascade_df1_32x64_q31.c"
#include "arm_biquad_cascade_df1_f32.c"
#include "arm_biquad_cascade_df1_fast_q15.c"
#include "arm_biquad_cascade_df1_fast_q31.c"
#include "arm_biquad_cascade_df1_init_f32.c"
#include "arm_biquad_cascade_df1_init_q15.c"
#include "arm_biquad_cascade_df1_init_q31.c"
#include "arm_biquad_cascade_df1_q15.c"
#include "arm_biquad_cascade_df1_q31.c"
#include "arm_biquad_cascade_df2T_f32.c"
#include "arm_biquad_cascade_df2T_f64.c"
#include "arm_biquad_cascade_df2T_init_f32.c"
#include "arm_biquad_cascade_df2T_init_f64.c"
#include "arm_biquad_cascade_stereo_df2T_f32.c"
#include "arm_biquad_cascade_stereo_df2T_init_f32.c"
#include "arm_conv_f32.c"
#include "arm_conv_fast_opt_q15.c"
#include "arm_conv_fast_q15.c"
#include "arm_conv_fast_q31.c"
#include "arm_conv_opt_q15.c"
#include "arm_conv_opt_q7.c"
#include "arm_conv_partial_f32.c"
#include "arm_conv_partial_fast_opt_q15.c"
#include "arm_conv_partial_fast_q15.c"
#include "arm_conv_partial_fast_q31.c"
#include "arm_conv_partial_opt_q15.c"
#include "arm_conv_partial_opt_q7.c"
#include "arm_conv_partial_q15.c"
#include "arm_conv_partial_q31.c"
#include "arm_conv_partial_q7.c"
#include "arm_conv_q15.c"
#include "arm_conv_q31.c"
#include "arm_conv_q7.c"
#include "arm_correlate_f32.c"
#include "arm_correlate_fast_opt_q15.c"
#include "arm_correlate_fast_q15.c"
#include "arm_correlate_fast_q31.c"
#include "arm_correlate_opt_q15.c"
#include "arm_correlate_opt_q7.c"
#include "arm_correlate_q15.c"
#include "arm_correlate_q31.c"
#include "arm_correlate_q7.c"
#include "arm_fir_decimate_f32.c"
#include "arm_fir_decimate_fast_q15.c"
#include "arm_fir_decimate_fast_q31.c"
#include "arm_fir_decimate_init_f32.c"
#include "arm_fir_decimate_init_q15.c"
#include "arm_fir_decimate_init_q31.c"
#include "arm_fir_decimate_q15.c"
#include "arm_fir_decimate_q31.c"
#include "arm_fir_f32.c"
#include "arm_fir_fast_q15.c"
#include "arm_fir_fast_q31.c"
#include "arm_fir_init_f32.c"
#include "arm_fir_init_q15.c"
#include "arm_fir_init_q31.c"
#include "arm_fir_init_q7.c"
#include "arm_fir_interpolate_f32.c"
#include "arm_fir_interpolate_init_f32.c"
#include "arm_fir_interpolate_init_q15.c"
#include "arm_fir_interpolate_init_q31.c"
#include "arm_fir_interpolate_q15.c"
#include "arm_fir_interpolate_q31.c"
#include "arm_fir_lattice_f32.c"
#include "arm_fir_lattice_init_f32.c"
#include "arm_fir_lattice_init_q15.c"
#include "arm_fir_lattice_init_q31.c"
#include "arm_fir_lattice_q15.c"
#include "arm_fir_lattice_q31.c"
#include "arm_fir_q15.c"
#include "arm_fir_q31.c"
#include "arm_fir_q7.c"
#include "arm_fir_sparse_f32.c"
#include "arm_fir_sparse_init_f32.c"
#include "arm_fir_sparse_init_q15.c"
#include "arm_fir_sparse_init_q31.c"
#include "arm_fir_sparse_init_q7.c"
#include "arm_fir_sparse_q15.c"
#include "arm_fir_sparse_q31.c"
#include "arm_fir_sparse_q7.c"
#include "arm_iir_lattice_f32.c"
#include "arm_iir_lattice_init_f32.c"
#include "arm_iir_lattice_init_q15.c"
#include "arm_iir_lattice_init_q31.c"
#include "arm_iir_lattice_q15.c"
#include "arm_iir_lattice_q31.c"
#include "arm_lms_f32.c"
#include "arm_lms_init_f32.c"
#include "arm_lms_init_q15.c"
#include "arm_lms_init_q31.c"
#include "arm_lms_norm_f32.c"
#include "arm_lms_norm_init_f32.c"
#include "arm_lms_norm_init_q15.c"
#include "arm_lms_norm_init_q31.c"
#include "arm_lms_norm_q15.c"
#include "arm_lms_norm_q31.c"
#include "arm_lms_q15.c"
#include "arm_lms_q31.c"
