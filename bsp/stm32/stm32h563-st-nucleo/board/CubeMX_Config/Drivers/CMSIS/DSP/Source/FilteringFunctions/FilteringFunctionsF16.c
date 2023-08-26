/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        FilteringFunctions.c
 * Description:  Combination of all filtering function f16 source files.
 *
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

#include "arm_fir_f16.c"
#include "arm_fir_init_f16.c"
#include "arm_biquad_cascade_df1_f16.c"
#include "arm_biquad_cascade_df1_init_f16.c"
#include "arm_biquad_cascade_df2T_f16.c"
#include "arm_biquad_cascade_df2T_init_f16.c"
#include "arm_biquad_cascade_stereo_df2T_f16.c"
#include "arm_biquad_cascade_stereo_df2T_init_f16.c"
#include "arm_correlate_f16.c"
#include "arm_levinson_durbin_f16.c"
