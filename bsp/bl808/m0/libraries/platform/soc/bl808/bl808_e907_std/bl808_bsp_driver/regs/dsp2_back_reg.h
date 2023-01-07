/**
  ******************************************************************************
  * @file    dsp2_back_reg.h
  * @version V1.0
  * @date    2021-02-05
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __DSP2_BACK_REG_H__
#define __DSP2_BACK_REG_H__

#include "bl808.h"

/* 0x314 : ccr_coef_A */
#define DSP2_BACK_CCR_COEF_A_OFFSET (0x314)
#define DSP2_BACK_A11_PRE           DSP2_BACK_A11_PRE
#define DSP2_BACK_A11_PRE_POS       (16U)
#define DSP2_BACK_A11_PRE_LEN       (12U)
#define DSP2_BACK_A11_PRE_MSK       (((1U << DSP2_BACK_A11_PRE_LEN) - 1) << DSP2_BACK_A11_PRE_POS)
#define DSP2_BACK_A11_PRE_UMSK      (~(((1U << DSP2_BACK_A11_PRE_LEN) - 1) << DSP2_BACK_A11_PRE_POS))

/* 0x318 : ccr_coef_B */
#define DSP2_BACK_CCR_COEF_B_OFFSET (0x318)
#define DSP2_BACK_A12_PRE           DSP2_BACK_A12_PRE
#define DSP2_BACK_A12_PRE_POS       (0U)
#define DSP2_BACK_A12_PRE_LEN       (12U)
#define DSP2_BACK_A12_PRE_MSK       (((1U << DSP2_BACK_A12_PRE_LEN) - 1) << DSP2_BACK_A12_PRE_POS)
#define DSP2_BACK_A12_PRE_UMSK      (~(((1U << DSP2_BACK_A12_PRE_LEN) - 1) << DSP2_BACK_A12_PRE_POS))
#define DSP2_BACK_A13_PRE           DSP2_BACK_A13_PRE
#define DSP2_BACK_A13_PRE_POS       (16U)
#define DSP2_BACK_A13_PRE_LEN       (12U)
#define DSP2_BACK_A13_PRE_MSK       (((1U << DSP2_BACK_A13_PRE_LEN) - 1) << DSP2_BACK_A13_PRE_POS)
#define DSP2_BACK_A13_PRE_UMSK      (~(((1U << DSP2_BACK_A13_PRE_LEN) - 1) << DSP2_BACK_A13_PRE_POS))

/* 0x31C : ccr_coef_C */
#define DSP2_BACK_CCR_COEF_C_OFFSET (0x31C)
#define DSP2_BACK_A21_PRE           DSP2_BACK_A21_PRE
#define DSP2_BACK_A21_PRE_POS       (0U)
#define DSP2_BACK_A21_PRE_LEN       (12U)
#define DSP2_BACK_A21_PRE_MSK       (((1U << DSP2_BACK_A21_PRE_LEN) - 1) << DSP2_BACK_A21_PRE_POS)
#define DSP2_BACK_A21_PRE_UMSK      (~(((1U << DSP2_BACK_A21_PRE_LEN) - 1) << DSP2_BACK_A21_PRE_POS))
#define DSP2_BACK_A22_PRE           DSP2_BACK_A22_PRE
#define DSP2_BACK_A22_PRE_POS       (16U)
#define DSP2_BACK_A22_PRE_LEN       (12U)
#define DSP2_BACK_A22_PRE_MSK       (((1U << DSP2_BACK_A22_PRE_LEN) - 1) << DSP2_BACK_A22_PRE_POS)
#define DSP2_BACK_A22_PRE_UMSK      (~(((1U << DSP2_BACK_A22_PRE_LEN) - 1) << DSP2_BACK_A22_PRE_POS))

/* 0x320 : ccr_coef_D */
#define DSP2_BACK_CCR_COEF_D_OFFSET (0x320)
#define DSP2_BACK_A23_PRE           DSP2_BACK_A23_PRE
#define DSP2_BACK_A23_PRE_POS       (0U)
#define DSP2_BACK_A23_PRE_LEN       (12U)
#define DSP2_BACK_A23_PRE_MSK       (((1U << DSP2_BACK_A23_PRE_LEN) - 1) << DSP2_BACK_A23_PRE_POS)
#define DSP2_BACK_A23_PRE_UMSK      (~(((1U << DSP2_BACK_A23_PRE_LEN) - 1) << DSP2_BACK_A23_PRE_POS))
#define DSP2_BACK_A31_PRE           DSP2_BACK_A31_PRE
#define DSP2_BACK_A31_PRE_POS       (16U)
#define DSP2_BACK_A31_PRE_LEN       (12U)
#define DSP2_BACK_A31_PRE_MSK       (((1U << DSP2_BACK_A31_PRE_LEN) - 1) << DSP2_BACK_A31_PRE_POS)
#define DSP2_BACK_A31_PRE_UMSK      (~(((1U << DSP2_BACK_A31_PRE_LEN) - 1) << DSP2_BACK_A31_PRE_POS))

/* 0x324 : ccr_coef_E */
#define DSP2_BACK_CCR_COEF_E_OFFSET (0x324)
#define DSP2_BACK_A32_PRE           DSP2_BACK_A32_PRE
#define DSP2_BACK_A32_PRE_POS       (0U)
#define DSP2_BACK_A32_PRE_LEN       (12U)
#define DSP2_BACK_A32_PRE_MSK       (((1U << DSP2_BACK_A32_PRE_LEN) - 1) << DSP2_BACK_A32_PRE_POS)
#define DSP2_BACK_A32_PRE_UMSK      (~(((1U << DSP2_BACK_A32_PRE_LEN) - 1) << DSP2_BACK_A32_PRE_POS))
#define DSP2_BACK_A33_PRE           DSP2_BACK_A33_PRE
#define DSP2_BACK_A33_PRE_POS       (16U)
#define DSP2_BACK_A33_PRE_LEN       (12U)
#define DSP2_BACK_A33_PRE_MSK       (((1U << DSP2_BACK_A33_PRE_LEN) - 1) << DSP2_BACK_A33_PRE_POS)
#define DSP2_BACK_A33_PRE_UMSK      (~(((1U << DSP2_BACK_A33_PRE_LEN) - 1) << DSP2_BACK_A33_PRE_POS))

/* 0x328 : gamma_A */
#define DSP2_BACK_GAMMA_A_OFFSET    (0x328)
#define DSP2_BACK_GAMMA_ON_PRE      DSP2_BACK_GAMMA_ON_PRE
#define DSP2_BACK_GAMMA_ON_PRE_POS  (0U)
#define DSP2_BACK_GAMMA_ON_PRE_LEN  (1U)
#define DSP2_BACK_GAMMA_ON_PRE_MSK  (((1U << DSP2_BACK_GAMMA_ON_PRE_LEN) - 1) << DSP2_BACK_GAMMA_ON_PRE_POS)
#define DSP2_BACK_GAMMA_ON_PRE_UMSK (~(((1U << DSP2_BACK_GAMMA_ON_PRE_LEN) - 1) << DSP2_BACK_GAMMA_ON_PRE_POS))
#define DSP2_BACK_GAMMA_EB_PRE      DSP2_BACK_GAMMA_EB_PRE
#define DSP2_BACK_GAMMA_EB_PRE_POS  (1U)
#define DSP2_BACK_GAMMA_EB_PRE_LEN  (1U)
#define DSP2_BACK_GAMMA_EB_PRE_MSK  (((1U << DSP2_BACK_GAMMA_EB_PRE_LEN) - 1) << DSP2_BACK_GAMMA_EB_PRE_POS)
#define DSP2_BACK_GAMMA_EB_PRE_UMSK (~(((1U << DSP2_BACK_GAMMA_EB_PRE_LEN) - 1) << DSP2_BACK_GAMMA_EB_PRE_POS))
#define DSP2_BACK_B0_PRE            DSP2_BACK_B0_PRE
#define DSP2_BACK_B0_PRE_POS        (8U)
#define DSP2_BACK_B0_PRE_LEN        (8U)
#define DSP2_BACK_B0_PRE_MSK        (((1U << DSP2_BACK_B0_PRE_LEN) - 1) << DSP2_BACK_B0_PRE_POS)
#define DSP2_BACK_B0_PRE_UMSK       (~(((1U << DSP2_BACK_B0_PRE_LEN) - 1) << DSP2_BACK_B0_PRE_POS))
#define DSP2_BACK_B1_PRE            DSP2_BACK_B1_PRE
#define DSP2_BACK_B1_PRE_POS        (16U)
#define DSP2_BACK_B1_PRE_LEN        (8U)
#define DSP2_BACK_B1_PRE_MSK        (((1U << DSP2_BACK_B1_PRE_LEN) - 1) << DSP2_BACK_B1_PRE_POS)
#define DSP2_BACK_B1_PRE_UMSK       (~(((1U << DSP2_BACK_B1_PRE_LEN) - 1) << DSP2_BACK_B1_PRE_POS))
#define DSP2_BACK_B2_PRE            DSP2_BACK_B2_PRE
#define DSP2_BACK_B2_PRE_POS        (24U)
#define DSP2_BACK_B2_PRE_LEN        (8U)
#define DSP2_BACK_B2_PRE_MSK        (((1U << DSP2_BACK_B2_PRE_LEN) - 1) << DSP2_BACK_B2_PRE_POS)
#define DSP2_BACK_B2_PRE_UMSK       (~(((1U << DSP2_BACK_B2_PRE_LEN) - 1) << DSP2_BACK_B2_PRE_POS))

/* 0x32C : gamma_B */
#define DSP2_BACK_GAMMA_B_OFFSET (0x32C)
#define DSP2_BACK_B3_PRE         DSP2_BACK_B3_PRE
#define DSP2_BACK_B3_PRE_POS     (0U)
#define DSP2_BACK_B3_PRE_LEN     (8U)
#define DSP2_BACK_B3_PRE_MSK     (((1U << DSP2_BACK_B3_PRE_LEN) - 1) << DSP2_BACK_B3_PRE_POS)
#define DSP2_BACK_B3_PRE_UMSK    (~(((1U << DSP2_BACK_B3_PRE_LEN) - 1) << DSP2_BACK_B3_PRE_POS))
#define DSP2_BACK_B4_PRE         DSP2_BACK_B4_PRE
#define DSP2_BACK_B4_PRE_POS     (8U)
#define DSP2_BACK_B4_PRE_LEN     (8U)
#define DSP2_BACK_B4_PRE_MSK     (((1U << DSP2_BACK_B4_PRE_LEN) - 1) << DSP2_BACK_B4_PRE_POS)
#define DSP2_BACK_B4_PRE_UMSK    (~(((1U << DSP2_BACK_B4_PRE_LEN) - 1) << DSP2_BACK_B4_PRE_POS))
#define DSP2_BACK_B5_PRE         DSP2_BACK_B5_PRE
#define DSP2_BACK_B5_PRE_POS     (16U)
#define DSP2_BACK_B5_PRE_LEN     (8U)
#define DSP2_BACK_B5_PRE_MSK     (((1U << DSP2_BACK_B5_PRE_LEN) - 1) << DSP2_BACK_B5_PRE_POS)
#define DSP2_BACK_B5_PRE_UMSK    (~(((1U << DSP2_BACK_B5_PRE_LEN) - 1) << DSP2_BACK_B5_PRE_POS))
#define DSP2_BACK_B6_PRE         DSP2_BACK_B6_PRE
#define DSP2_BACK_B6_PRE_POS     (24U)
#define DSP2_BACK_B6_PRE_LEN     (8U)
#define DSP2_BACK_B6_PRE_MSK     (((1U << DSP2_BACK_B6_PRE_LEN) - 1) << DSP2_BACK_B6_PRE_POS)
#define DSP2_BACK_B6_PRE_UMSK    (~(((1U << DSP2_BACK_B6_PRE_LEN) - 1) << DSP2_BACK_B6_PRE_POS))

/* 0x330 : gamma_C */
#define DSP2_BACK_GAMMA_C_OFFSET (0x330)
#define DSP2_BACK_B7_PRE         DSP2_BACK_B7_PRE
#define DSP2_BACK_B7_PRE_POS     (0U)
#define DSP2_BACK_B7_PRE_LEN     (8U)
#define DSP2_BACK_B7_PRE_MSK     (((1U << DSP2_BACK_B7_PRE_LEN) - 1) << DSP2_BACK_B7_PRE_POS)
#define DSP2_BACK_B7_PRE_UMSK    (~(((1U << DSP2_BACK_B7_PRE_LEN) - 1) << DSP2_BACK_B7_PRE_POS))
#define DSP2_BACK_B8_PRE         DSP2_BACK_B8_PRE
#define DSP2_BACK_B8_PRE_POS     (8U)
#define DSP2_BACK_B8_PRE_LEN     (8U)
#define DSP2_BACK_B8_PRE_MSK     (((1U << DSP2_BACK_B8_PRE_LEN) - 1) << DSP2_BACK_B8_PRE_POS)
#define DSP2_BACK_B8_PRE_UMSK    (~(((1U << DSP2_BACK_B8_PRE_LEN) - 1) << DSP2_BACK_B8_PRE_POS))
#define DSP2_BACK_B9_PRE         DSP2_BACK_B9_PRE
#define DSP2_BACK_B9_PRE_POS     (16U)
#define DSP2_BACK_B9_PRE_LEN     (8U)
#define DSP2_BACK_B9_PRE_MSK     (((1U << DSP2_BACK_B9_PRE_LEN) - 1) << DSP2_BACK_B9_PRE_POS)
#define DSP2_BACK_B9_PRE_UMSK    (~(((1U << DSP2_BACK_B9_PRE_LEN) - 1) << DSP2_BACK_B9_PRE_POS))
#define DSP2_BACK_B10_PRE        DSP2_BACK_B10_PRE
#define DSP2_BACK_B10_PRE_POS    (24U)
#define DSP2_BACK_B10_PRE_LEN    (8U)
#define DSP2_BACK_B10_PRE_MSK    (((1U << DSP2_BACK_B10_PRE_LEN) - 1) << DSP2_BACK_B10_PRE_POS)
#define DSP2_BACK_B10_PRE_UMSK   (~(((1U << DSP2_BACK_B10_PRE_LEN) - 1) << DSP2_BACK_B10_PRE_POS))

/* 0x334 : gamma_D */
#define DSP2_BACK_GAMMA_D_OFFSET (0x334)
#define DSP2_BACK_B11_PRE        DSP2_BACK_B11_PRE
#define DSP2_BACK_B11_PRE_POS    (0U)
#define DSP2_BACK_B11_PRE_LEN    (8U)
#define DSP2_BACK_B11_PRE_MSK    (((1U << DSP2_BACK_B11_PRE_LEN) - 1) << DSP2_BACK_B11_PRE_POS)
#define DSP2_BACK_B11_PRE_UMSK   (~(((1U << DSP2_BACK_B11_PRE_LEN) - 1) << DSP2_BACK_B11_PRE_POS))
#define DSP2_BACK_B12_PRE        DSP2_BACK_B12_PRE
#define DSP2_BACK_B12_PRE_POS    (8U)
#define DSP2_BACK_B12_PRE_LEN    (8U)
#define DSP2_BACK_B12_PRE_MSK    (((1U << DSP2_BACK_B12_PRE_LEN) - 1) << DSP2_BACK_B12_PRE_POS)
#define DSP2_BACK_B12_PRE_UMSK   (~(((1U << DSP2_BACK_B12_PRE_LEN) - 1) << DSP2_BACK_B12_PRE_POS))
#define DSP2_BACK_B13_PRE        DSP2_BACK_B13_PRE
#define DSP2_BACK_B13_PRE_POS    (16U)
#define DSP2_BACK_B13_PRE_LEN    (8U)
#define DSP2_BACK_B13_PRE_MSK    (((1U << DSP2_BACK_B13_PRE_LEN) - 1) << DSP2_BACK_B13_PRE_POS)
#define DSP2_BACK_B13_PRE_UMSK   (~(((1U << DSP2_BACK_B13_PRE_LEN) - 1) << DSP2_BACK_B13_PRE_POS))
#define DSP2_BACK_B14_PRE        DSP2_BACK_B14_PRE
#define DSP2_BACK_B14_PRE_POS    (24U)
#define DSP2_BACK_B14_PRE_LEN    (8U)
#define DSP2_BACK_B14_PRE_MSK    (((1U << DSP2_BACK_B14_PRE_LEN) - 1) << DSP2_BACK_B14_PRE_POS)
#define DSP2_BACK_B14_PRE_UMSK   (~(((1U << DSP2_BACK_B14_PRE_LEN) - 1) << DSP2_BACK_B14_PRE_POS))

/* 0x338 : gamma_E */
#define DSP2_BACK_GAMMA_E_OFFSET (0x338)
#define DSP2_BACK_B15_PRE        DSP2_BACK_B15_PRE
#define DSP2_BACK_B15_PRE_POS    (0U)
#define DSP2_BACK_B15_PRE_LEN    (8U)
#define DSP2_BACK_B15_PRE_MSK    (((1U << DSP2_BACK_B15_PRE_LEN) - 1) << DSP2_BACK_B15_PRE_POS)
#define DSP2_BACK_B15_PRE_UMSK   (~(((1U << DSP2_BACK_B15_PRE_LEN) - 1) << DSP2_BACK_B15_PRE_POS))
#define DSP2_BACK_B16_PRE        DSP2_BACK_B16_PRE
#define DSP2_BACK_B16_PRE_POS    (8U)
#define DSP2_BACK_B16_PRE_LEN    (8U)
#define DSP2_BACK_B16_PRE_MSK    (((1U << DSP2_BACK_B16_PRE_LEN) - 1) << DSP2_BACK_B16_PRE_POS)
#define DSP2_BACK_B16_PRE_UMSK   (~(((1U << DSP2_BACK_B16_PRE_LEN) - 1) << DSP2_BACK_B16_PRE_POS))
#define DSP2_BACK_B17_PRE        DSP2_BACK_B17_PRE
#define DSP2_BACK_B17_PRE_POS    (16U)
#define DSP2_BACK_B17_PRE_LEN    (8U)
#define DSP2_BACK_B17_PRE_MSK    (((1U << DSP2_BACK_B17_PRE_LEN) - 1) << DSP2_BACK_B17_PRE_POS)
#define DSP2_BACK_B17_PRE_UMSK   (~(((1U << DSP2_BACK_B17_PRE_LEN) - 1) << DSP2_BACK_B17_PRE_POS))
#define DSP2_BACK_B18_PRE        DSP2_BACK_B18_PRE
#define DSP2_BACK_B18_PRE_POS    (24U)
#define DSP2_BACK_B18_PRE_LEN    (8U)
#define DSP2_BACK_B18_PRE_MSK    (((1U << DSP2_BACK_B18_PRE_LEN) - 1) << DSP2_BACK_B18_PRE_POS)
#define DSP2_BACK_B18_PRE_UMSK   (~(((1U << DSP2_BACK_B18_PRE_LEN) - 1) << DSP2_BACK_B18_PRE_POS))

/* 0x33C : conv_mode */
#define DSP2_BACK_CONV_MODE_OFFSET (0x33C)
#define DSP2_BACK_CONV_MODE_W      DSP2_BACK_CONV_MODE_W
#define DSP2_BACK_CONV_MODE_W_POS  (0U)
#define DSP2_BACK_CONV_MODE_W_LEN  (1U)
#define DSP2_BACK_CONV_MODE_W_MSK  (((1U << DSP2_BACK_CONV_MODE_W_LEN) - 1) << DSP2_BACK_CONV_MODE_W_POS)
#define DSP2_BACK_CONV_MODE_W_UMSK (~(((1U << DSP2_BACK_CONV_MODE_W_LEN) - 1) << DSP2_BACK_CONV_MODE_W_POS))

/* 0x348 : edge_enhance */
#define DSP2_BACK_EDGE_ENHANCE_OFFSET      (0x348)
#define DSP2_BACK_ENHANCE_LEVEL_W          DSP2_BACK_ENHANCE_LEVEL_W
#define DSP2_BACK_ENHANCE_LEVEL_W_POS      (0U)
#define DSP2_BACK_ENHANCE_LEVEL_W_LEN      (7U)
#define DSP2_BACK_ENHANCE_LEVEL_W_MSK      (((1U << DSP2_BACK_ENHANCE_LEVEL_W_LEN) - 1) << DSP2_BACK_ENHANCE_LEVEL_W_POS)
#define DSP2_BACK_ENHANCE_LEVEL_W_UMSK     (~(((1U << DSP2_BACK_ENHANCE_LEVEL_W_LEN) - 1) << DSP2_BACK_ENHANCE_LEVEL_W_POS))
#define DSP2_BACK_EDGE_LIMIT_W             DSP2_BACK_EDGE_LIMIT_W
#define DSP2_BACK_EDGE_LIMIT_W_POS         (8U)
#define DSP2_BACK_EDGE_LIMIT_W_LEN         (8U)
#define DSP2_BACK_EDGE_LIMIT_W_MSK         (((1U << DSP2_BACK_EDGE_LIMIT_W_LEN) - 1) << DSP2_BACK_EDGE_LIMIT_W_POS)
#define DSP2_BACK_EDGE_LIMIT_W_UMSK        (~(((1U << DSP2_BACK_EDGE_LIMIT_W_LEN) - 1) << DSP2_BACK_EDGE_LIMIT_W_POS))
#define DSP2_BACK_HPF_RATE_W               DSP2_BACK_HPF_RATE_W
#define DSP2_BACK_HPF_RATE_W_POS           (16U)
#define DSP2_BACK_HPF_RATE_W_LEN           (4U)
#define DSP2_BACK_HPF_RATE_W_MSK           (((1U << DSP2_BACK_HPF_RATE_W_LEN) - 1) << DSP2_BACK_HPF_RATE_W_POS)
#define DSP2_BACK_HPF_RATE_W_UMSK          (~(((1U << DSP2_BACK_HPF_RATE_W_LEN) - 1) << DSP2_BACK_HPF_RATE_W_POS))
#define DSP2_BACK_NOISE_THRESHOLD_PRE      DSP2_BACK_NOISE_THRESHOLD_PRE
#define DSP2_BACK_NOISE_THRESHOLD_PRE_POS  (24U)
#define DSP2_BACK_NOISE_THRESHOLD_PRE_LEN  (7U)
#define DSP2_BACK_NOISE_THRESHOLD_PRE_MSK  (((1U << DSP2_BACK_NOISE_THRESHOLD_PRE_LEN) - 1) << DSP2_BACK_NOISE_THRESHOLD_PRE_POS)
#define DSP2_BACK_NOISE_THRESHOLD_PRE_UMSK (~(((1U << DSP2_BACK_NOISE_THRESHOLD_PRE_LEN) - 1) << DSP2_BACK_NOISE_THRESHOLD_PRE_POS))

/* 0x34C : YUVC_A */
#define DSP2_BACK_YUVC_A_OFFSET         (0x34C)
#define DSP2_BACK_YBRIGHTNESS_W         DSP2_BACK_YBRIGHTNESS_W
#define DSP2_BACK_YBRIGHTNESS_W_POS     (0U)
#define DSP2_BACK_YBRIGHTNESS_W_LEN     (8U)
#define DSP2_BACK_YBRIGHTNESS_W_MSK     (((1U << DSP2_BACK_YBRIGHTNESS_W_LEN) - 1) << DSP2_BACK_YBRIGHTNESS_W_POS)
#define DSP2_BACK_YBRIGHTNESS_W_UMSK    (~(((1U << DSP2_BACK_YBRIGHTNESS_W_LEN) - 1) << DSP2_BACK_YBRIGHTNESS_W_POS))
#define DSP2_BACK_YCONTRAST_W           DSP2_BACK_YCONTRAST_W
#define DSP2_BACK_YCONTRAST_W_POS       (8U)
#define DSP2_BACK_YCONTRAST_W_LEN       (8U)
#define DSP2_BACK_YCONTRAST_W_MSK       (((1U << DSP2_BACK_YCONTRAST_W_LEN) - 1) << DSP2_BACK_YCONTRAST_W_POS)
#define DSP2_BACK_YCONTRAST_W_UMSK      (~(((1U << DSP2_BACK_YCONTRAST_W_LEN) - 1) << DSP2_BACK_YCONTRAST_W_POS))
#define DSP2_BACK_CBSATURATION_PRE      DSP2_BACK_CBSATURATION_PRE
#define DSP2_BACK_CBSATURATION_PRE_POS  (16U)
#define DSP2_BACK_CBSATURATION_PRE_LEN  (8U)
#define DSP2_BACK_CBSATURATION_PRE_MSK  (((1U << DSP2_BACK_CBSATURATION_PRE_LEN) - 1) << DSP2_BACK_CBSATURATION_PRE_POS)
#define DSP2_BACK_CBSATURATION_PRE_UMSK (~(((1U << DSP2_BACK_CBSATURATION_PRE_LEN) - 1) << DSP2_BACK_CBSATURATION_PRE_POS))
#define DSP2_BACK_CRSATURATION_PRE      DSP2_BACK_CRSATURATION_PRE
#define DSP2_BACK_CRSATURATION_PRE_POS  (24U)
#define DSP2_BACK_CRSATURATION_PRE_LEN  (8U)
#define DSP2_BACK_CRSATURATION_PRE_MSK  (((1U << DSP2_BACK_CRSATURATION_PRE_LEN) - 1) << DSP2_BACK_CRSATURATION_PRE_POS)
#define DSP2_BACK_CRSATURATION_PRE_UMSK (~(((1U << DSP2_BACK_CRSATURATION_PRE_LEN) - 1) << DSP2_BACK_CRSATURATION_PRE_POS))

/* 0x350 : YUVC_B */
#define DSP2_BACK_YUVC_B_OFFSET                 (0x350)
#define DSP2_BACK_SPECIALMODE_W                 DSP2_BACK_SPECIALMODE_W
#define DSP2_BACK_SPECIALMODE_W_POS             (0U)
#define DSP2_BACK_SPECIALMODE_W_LEN             (3U)
#define DSP2_BACK_SPECIALMODE_W_MSK             (((1U << DSP2_BACK_SPECIALMODE_W_LEN) - 1) << DSP2_BACK_SPECIALMODE_W_POS)
#define DSP2_BACK_SPECIALMODE_W_UMSK            (~(((1U << DSP2_BACK_SPECIALMODE_W_LEN) - 1) << DSP2_BACK_SPECIALMODE_W_POS))
#define DSP2_BACK_C444TO422FILTERINGMODE_W      DSP2_BACK_C444TO422FILTERINGMODE_W
#define DSP2_BACK_C444TO422FILTERINGMODE_W_POS  (4U)
#define DSP2_BACK_C444TO422FILTERINGMODE_W_LEN  (1U)
#define DSP2_BACK_C444TO422FILTERINGMODE_W_MSK  (((1U << DSP2_BACK_C444TO422FILTERINGMODE_W_LEN) - 1) << DSP2_BACK_C444TO422FILTERINGMODE_W_POS)
#define DSP2_BACK_C444TO422FILTERINGMODE_W_UMSK (~(((1U << DSP2_BACK_C444TO422FILTERINGMODE_W_LEN) - 1) << DSP2_BACK_C444TO422FILTERINGMODE_W_POS))
#define DSP2_BACK_SEPIACB_W                     DSP2_BACK_SEPIACB_W
#define DSP2_BACK_SEPIACB_W_POS                 (8U)
#define DSP2_BACK_SEPIACB_W_LEN                 (8U)
#define DSP2_BACK_SEPIACB_W_MSK                 (((1U << DSP2_BACK_SEPIACB_W_LEN) - 1) << DSP2_BACK_SEPIACB_W_POS)
#define DSP2_BACK_SEPIACB_W_UMSK                (~(((1U << DSP2_BACK_SEPIACB_W_LEN) - 1) << DSP2_BACK_SEPIACB_W_POS))
#define DSP2_BACK_SEPIACR_W                     DSP2_BACK_SEPIACR_W
#define DSP2_BACK_SEPIACR_W_POS                 (16U)
#define DSP2_BACK_SEPIACR_W_LEN                 (8U)
#define DSP2_BACK_SEPIACR_W_MSK                 (((1U << DSP2_BACK_SEPIACR_W_LEN) - 1) << DSP2_BACK_SEPIACR_W_POS)
#define DSP2_BACK_SEPIACR_W_UMSK                (~(((1U << DSP2_BACK_SEPIACR_W_LEN) - 1) << DSP2_BACK_SEPIACR_W_POS))
#define DSP2_BACK_SOLARTHRED_W                  DSP2_BACK_SOLARTHRED_W
#define DSP2_BACK_SOLARTHRED_W_POS              (24U)
#define DSP2_BACK_SOLARTHRED_W_LEN              (8U)
#define DSP2_BACK_SOLARTHRED_W_MSK              (((1U << DSP2_BACK_SOLARTHRED_W_LEN) - 1) << DSP2_BACK_SOLARTHRED_W_POS)
#define DSP2_BACK_SOLARTHRED_W_UMSK             (~(((1U << DSP2_BACK_SOLARTHRED_W_LEN) - 1) << DSP2_BACK_SOLARTHRED_W_POS))

/* 0x354 : DNR_A */
#define DSP2_BACK_DNR_A_OFFSET              (0x354)
#define DSP2_BACK_NOISE_LEVEL_PRE           DSP2_BACK_NOISE_LEVEL_PRE
#define DSP2_BACK_NOISE_LEVEL_PRE_POS       (0U)
#define DSP2_BACK_NOISE_LEVEL_PRE_LEN       (6U)
#define DSP2_BACK_NOISE_LEVEL_PRE_MSK       (((1U << DSP2_BACK_NOISE_LEVEL_PRE_LEN) - 1) << DSP2_BACK_NOISE_LEVEL_PRE_POS)
#define DSP2_BACK_NOISE_LEVEL_PRE_UMSK      (~(((1U << DSP2_BACK_NOISE_LEVEL_PRE_LEN) - 1) << DSP2_BACK_NOISE_LEVEL_PRE_POS))
#define DSP2_BACK_NR_HSIZE_PRE              DSP2_BACK_NR_HSIZE_PRE
#define DSP2_BACK_NR_HSIZE_PRE_POS          (8U)
#define DSP2_BACK_NR_HSIZE_PRE_LEN          (16U)
#define DSP2_BACK_NR_HSIZE_PRE_MSK          (((1U << DSP2_BACK_NR_HSIZE_PRE_LEN) - 1) << DSP2_BACK_NR_HSIZE_PRE_POS)
#define DSP2_BACK_NR_HSIZE_PRE_UMSK         (~(((1U << DSP2_BACK_NR_HSIZE_PRE_LEN) - 1) << DSP2_BACK_NR_HSIZE_PRE_POS))
#define DSP2_BACK_FILT_STRENGTH_2D_PRE      DSP2_BACK_FILT_STRENGTH_2D_PRE
#define DSP2_BACK_FILT_STRENGTH_2D_PRE_POS  (24U)
#define DSP2_BACK_FILT_STRENGTH_2D_PRE_LEN  (4U)
#define DSP2_BACK_FILT_STRENGTH_2D_PRE_MSK  (((1U << DSP2_BACK_FILT_STRENGTH_2D_PRE_LEN) - 1) << DSP2_BACK_FILT_STRENGTH_2D_PRE_POS)
#define DSP2_BACK_FILT_STRENGTH_2D_PRE_UMSK (~(((1U << DSP2_BACK_FILT_STRENGTH_2D_PRE_LEN) - 1) << DSP2_BACK_FILT_STRENGTH_2D_PRE_POS))
#define DSP2_BACK_FILT_STRENGTH_3D_PRE      DSP2_BACK_FILT_STRENGTH_3D_PRE
#define DSP2_BACK_FILT_STRENGTH_3D_PRE_POS  (28U)
#define DSP2_BACK_FILT_STRENGTH_3D_PRE_LEN  (4U)
#define DSP2_BACK_FILT_STRENGTH_3D_PRE_MSK  (((1U << DSP2_BACK_FILT_STRENGTH_3D_PRE_LEN) - 1) << DSP2_BACK_FILT_STRENGTH_3D_PRE_POS)
#define DSP2_BACK_FILT_STRENGTH_3D_PRE_UMSK (~(((1U << DSP2_BACK_FILT_STRENGTH_3D_PRE_LEN) - 1) << DSP2_BACK_FILT_STRENGTH_3D_PRE_POS))

/* 0x358 : DNR_B */
#define DSP2_BACK_DNR_B_OFFSET        (0x358)
#define DSP2_BACK_DELAYNUM3DNR_W      DSP2_BACK_DELAYNUM3DNR_W
#define DSP2_BACK_DELAYNUM3DNR_W_POS  (0U)
#define DSP2_BACK_DELAYNUM3DNR_W_LEN  (3U)
#define DSP2_BACK_DELAYNUM3DNR_W_MSK  (((1U << DSP2_BACK_DELAYNUM3DNR_W_LEN) - 1) << DSP2_BACK_DELAYNUM3DNR_W_POS)
#define DSP2_BACK_DELAYNUM3DNR_W_UMSK (~(((1U << DSP2_BACK_DELAYNUM3DNR_W_LEN) - 1) << DSP2_BACK_DELAYNUM3DNR_W_POS))
#define DSP2_BACK_CBCR_SELECT_W       DSP2_BACK_CBCR_SELECT_W
#define DSP2_BACK_CBCR_SELECT_W_POS   (8U)
#define DSP2_BACK_CBCR_SELECT_W_LEN   (1U)
#define DSP2_BACK_CBCR_SELECT_W_MSK   (((1U << DSP2_BACK_CBCR_SELECT_W_LEN) - 1) << DSP2_BACK_CBCR_SELECT_W_POS)
#define DSP2_BACK_CBCR_SELECT_W_UMSK  (~(((1U << DSP2_BACK_CBCR_SELECT_W_LEN) - 1) << DSP2_BACK_CBCR_SELECT_W_POS))
#define DSP2_BACK_OUT_FORMAT_W        DSP2_BACK_OUT_FORMAT_W
#define DSP2_BACK_OUT_FORMAT_W_POS    (9U)
#define DSP2_BACK_OUT_FORMAT_W_LEN    (2U)
#define DSP2_BACK_OUT_FORMAT_W_MSK    (((1U << DSP2_BACK_OUT_FORMAT_W_LEN) - 1) << DSP2_BACK_OUT_FORMAT_W_POS)
#define DSP2_BACK_OUT_FORMAT_W_UMSK   (~(((1U << DSP2_BACK_OUT_FORMAT_W_LEN) - 1) << DSP2_BACK_OUT_FORMAT_W_POS))

/* 0x3FF : DVI_HDMI_MODE */
#define DSP2_BACK_DVI_HDMI_MODE_OFFSET (0x3FF)
#define DSP2_BACK_DVI_HDMI_MODE_W      DSP2_BACK_DVI_HDMI_MODE_W
#define DSP2_BACK_DVI_HDMI_MODE_W_POS  (0U)
#define DSP2_BACK_DVI_HDMI_MODE_W_LEN  (1U)
#define DSP2_BACK_DVI_HDMI_MODE_W_MSK  (((1U << DSP2_BACK_DVI_HDMI_MODE_W_LEN) - 1) << DSP2_BACK_DVI_HDMI_MODE_W_POS)
#define DSP2_BACK_DVI_HDMI_MODE_W_UMSK (~(((1U << DSP2_BACK_DVI_HDMI_MODE_W_LEN) - 1) << DSP2_BACK_DVI_HDMI_MODE_W_POS))

struct dsp2_back_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[788];

    /* 0x314 : ccr_coef_A */
    union {
        struct
        {
            uint32_t reserved_0_15  : 16; /* [15: 0],       rsvd,        0x0 */
            uint32_t a11_pre        : 12; /* [27:16],        r/w,      0x200 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } ccr_coef_A;

    /* 0x318 : ccr_coef_B */
    union {
        struct
        {
            uint32_t a12_pre        : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t a13_pre        : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } ccr_coef_B;

    /* 0x31C : ccr_coef_C */
    union {
        struct
        {
            uint32_t a21_pre        : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t a22_pre        : 12; /* [27:16],        r/w,      0x200 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } ccr_coef_C;

    /* 0x320 : ccr_coef_D */
    union {
        struct
        {
            uint32_t a23_pre        : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t a31_pre        : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } ccr_coef_D;

    /* 0x324 : ccr_coef_E */
    union {
        struct
        {
            uint32_t a32_pre        : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t a33_pre        : 12; /* [27:16],        r/w,      0x200 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } ccr_coef_E;

    /* 0x328 : gamma_A */
    union {
        struct
        {
            uint32_t gamma_on_pre : 1; /* [    0],        r/w,        0x0 */
            uint32_t gamma_eb_pre : 1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_7 : 6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t b0_pre       : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t b1_pre       : 8; /* [23:16],        r/w,        0x4 */
            uint32_t b2_pre       : 8; /* [31:24],        r/w,        0x8 */
        } BF;
        uint32_t WORD;
    } gamma_A;

    /* 0x32C : gamma_B */
    union {
        struct
        {
            uint32_t b3_pre : 8; /* [ 7: 0],        r/w,       0x10 */
            uint32_t b4_pre : 8; /* [15: 8],        r/w,       0x20 */
            uint32_t b5_pre : 8; /* [23:16],        r/w,       0x30 */
            uint32_t b6_pre : 8; /* [31:24],        r/w,       0x40 */
        } BF;
        uint32_t WORD;
    } gamma_B;

    /* 0x330 : gamma_C */
    union {
        struct
        {
            uint32_t b7_pre  : 8; /* [ 7: 0],        r/w,       0x50 */
            uint32_t b8_pre  : 8; /* [15: 8],        r/w,       0x60 */
            uint32_t b9_pre  : 8; /* [23:16],        r/w,       0x70 */
            uint32_t b10_pre : 8; /* [31:24],        r/w,       0x80 */
        } BF;
        uint32_t WORD;
    } gamma_C;

    /* 0x334 : gamma_D */
    union {
        struct
        {
            uint32_t b11_pre : 8; /* [ 7: 0],        r/w,       0x90 */
            uint32_t b12_pre : 8; /* [15: 8],        r/w,       0xa0 */
            uint32_t b13_pre : 8; /* [23:16],        r/w,       0xb0 */
            uint32_t b14_pre : 8; /* [31:24],        r/w,       0xc0 */
        } BF;
        uint32_t WORD;
    } gamma_D;

    /* 0x338 : gamma_E */
    union {
        struct
        {
            uint32_t b15_pre : 8; /* [ 7: 0],        r/w,       0xd0 */
            uint32_t b16_pre : 8; /* [15: 8],        r/w,       0xe0 */
            uint32_t b17_pre : 8; /* [23:16],        r/w,       0xf0 */
            uint32_t b18_pre : 8; /* [31:24],        r/w,       0xff */
        } BF;
        uint32_t WORD;
    } gamma_E;

    /* 0x33C : conv_mode */
    union {
        struct
        {
            uint32_t conv_mode_w   : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31 : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } conv_mode;

    /* 0x340  reserved */
    uint8_t RESERVED0x340[8];

    /* 0x348 : edge_enhance */
    union {
        struct
        {
            uint32_t enhance_level_w     : 7; /* [ 6: 0],        r/w,       0x69 */
            uint32_t reserved_7          : 1; /* [    7],       rsvd,        0x0 */
            uint32_t edge_limit_w        : 8; /* [15: 8],        r/w,       0x30 */
            uint32_t HPF_rate_w          : 4; /* [19:16],        r/w,        0x4 */
            uint32_t reserved_20_23      : 4; /* [23:20],       rsvd,        0x0 */
            uint32_t noise_threshold_pre : 7; /* [30:24],        r/w,        0x0 */
            uint32_t reserved_31         : 1; /* [   31],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } edge_enhance;

    /* 0x34C : YUVC_A */
    union {
        struct
        {
            uint32_t YBrightness_w    : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t YContrast_w      : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t CbSaturation_pre : 8; /* [23:16],        r/w,       0x80 */
            uint32_t CrSaturation_pre : 8; /* [31:24],        r/w,       0x80 */
        } BF;
        uint32_t WORD;
    } YUVC_A;

    /* 0x350 : YUVC_B */
    union {
        struct
        {
            uint32_t SpecialMode_w            : 3; /* [ 2: 0],        r/w,        0x0 */
            uint32_t reserved_3               : 1; /* [    3],       rsvd,        0x0 */
            uint32_t C444to422Filteringmode_w : 1; /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_7             : 3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t SepiaCb_w                : 8; /* [15: 8],        r/w,       0x73 */
            uint32_t SepiaCr_w                : 8; /* [23:16],        r/w,       0x89 */
            uint32_t SolarThred_w             : 8; /* [31:24],        r/w,       0x80 */
        } BF;
        uint32_t WORD;
    } YUVC_B;

    /* 0x354 : DNR_A */
    union {
        struct
        {
            uint32_t noise_level_pre      : 6;  /* [ 5: 0],        r/w,        0x0 */
            uint32_t reserved_6_7         : 2;  /* [ 7: 6],       rsvd,        0x0 */
            uint32_t nr_hsize_pre         : 16; /* [23: 8],        r/w,      0x788 */
            uint32_t Filt_Strength_2D_pre : 4;  /* [27:24],        r/w,        0x6 */
            uint32_t Filt_Strength_3D_pre : 4;  /* [31:28],        r/w,        0x5 */
        } BF;
        uint32_t WORD;
    } DNR_A;

    /* 0x358 : DNR_B */
    union {
        struct
        {
            uint32_t DelayNum3DNR_w : 3;  /* [ 2: 0],        r/w,        0x4 */
            uint32_t reserved_3_7   : 5;  /* [ 7: 3],       rsvd,        0x0 */
            uint32_t CbCr_select_w  : 1;  /* [    8],        r/w,        0x1 */
            uint32_t out_format_w   : 2;  /* [10: 9],        r/w,        0x1 */
            uint32_t reserved_11_31 : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DNR_B;

    /* 0x35c  reserved */
    uint8_t RESERVED0x35c[163];

    /* 0x3FF : DVI_HDMI_MODE */
    union {
        struct
        {
            uint32_t DVI_HDMI_MODE_w : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31   : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DVI_HDMI_MODE;
};

typedef volatile struct dsp2_back_reg dsp2_back_reg_t;

#endif /* __DSP2_BACK_REG_H__ */
