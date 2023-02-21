/**
  ******************************************************************************
  * @file    dsp2_middle4_reg.h
  * @version V1.0
  * @date    2021-09-10
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
#ifndef __DSP2_MIDDLE4_REG_H__
#define __DSP2_MIDDLE4_REG_H__

#include "bl808.h"

/* 0x600 : bnr_config_0 */
#define DSP2_MIDDLE4_BNR_CONFIG_0_OFFSET (0x600)
#define DSP2_MIDDLE4_BNR_WEIGHT_PRE      DSP2_MIDDLE4_BNR_WEIGHT_PRE
#define DSP2_MIDDLE4_BNR_WEIGHT_PRE_POS  (0U)
#define DSP2_MIDDLE4_BNR_WEIGHT_PRE_LEN  (7U)
#define DSP2_MIDDLE4_BNR_WEIGHT_PRE_MSK  (((1U << DSP2_MIDDLE4_BNR_WEIGHT_PRE_LEN) - 1) << DSP2_MIDDLE4_BNR_WEIGHT_PRE_POS)
#define DSP2_MIDDLE4_BNR_WEIGHT_PRE_UMSK (~(((1U << DSP2_MIDDLE4_BNR_WEIGHT_PRE_LEN) - 1) << DSP2_MIDDLE4_BNR_WEIGHT_PRE_POS))
#define DSP2_MIDDLE4_BNR_EN_PRE          DSP2_MIDDLE4_BNR_EN_PRE
#define DSP2_MIDDLE4_BNR_EN_PRE_POS      (7U)
#define DSP2_MIDDLE4_BNR_EN_PRE_LEN      (1U)
#define DSP2_MIDDLE4_BNR_EN_PRE_MSK      (((1U << DSP2_MIDDLE4_BNR_EN_PRE_LEN) - 1) << DSP2_MIDDLE4_BNR_EN_PRE_POS)
#define DSP2_MIDDLE4_BNR_EN_PRE_UMSK     (~(((1U << DSP2_MIDDLE4_BNR_EN_PRE_LEN) - 1) << DSP2_MIDDLE4_BNR_EN_PRE_POS))
#define DSP2_MIDDLE4_LPF_WEIGHT_PRE      DSP2_MIDDLE4_LPF_WEIGHT_PRE
#define DSP2_MIDDLE4_LPF_WEIGHT_PRE_POS  (8U)
#define DSP2_MIDDLE4_LPF_WEIGHT_PRE_LEN  (5U)
#define DSP2_MIDDLE4_LPF_WEIGHT_PRE_MSK  (((1U << DSP2_MIDDLE4_LPF_WEIGHT_PRE_LEN) - 1) << DSP2_MIDDLE4_LPF_WEIGHT_PRE_POS)
#define DSP2_MIDDLE4_LPF_WEIGHT_PRE_UMSK (~(((1U << DSP2_MIDDLE4_LPF_WEIGHT_PRE_LEN) - 1) << DSP2_MIDDLE4_LPF_WEIGHT_PRE_POS))
#define DSP2_MIDDLE4_TH_BASE_B_PRE       DSP2_MIDDLE4_TH_BASE_B_PRE
#define DSP2_MIDDLE4_TH_BASE_B_PRE_POS   (16U)
#define DSP2_MIDDLE4_TH_BASE_B_PRE_LEN   (10U)
#define DSP2_MIDDLE4_TH_BASE_B_PRE_MSK   (((1U << DSP2_MIDDLE4_TH_BASE_B_PRE_LEN) - 1) << DSP2_MIDDLE4_TH_BASE_B_PRE_POS)
#define DSP2_MIDDLE4_TH_BASE_B_PRE_UMSK  (~(((1U << DSP2_MIDDLE4_TH_BASE_B_PRE_LEN) - 1) << DSP2_MIDDLE4_TH_BASE_B_PRE_POS))

/* 0x604 : bnr_config_1 */
#define DSP2_MIDDLE4_BNR_CONFIG_1_OFFSET (0x604)
#define DSP2_MIDDLE4_TH_BASE_R_PRE       DSP2_MIDDLE4_TH_BASE_R_PRE
#define DSP2_MIDDLE4_TH_BASE_R_PRE_POS   (0U)
#define DSP2_MIDDLE4_TH_BASE_R_PRE_LEN   (10U)
#define DSP2_MIDDLE4_TH_BASE_R_PRE_MSK   (((1U << DSP2_MIDDLE4_TH_BASE_R_PRE_LEN) - 1) << DSP2_MIDDLE4_TH_BASE_R_PRE_POS)
#define DSP2_MIDDLE4_TH_BASE_R_PRE_UMSK  (~(((1U << DSP2_MIDDLE4_TH_BASE_R_PRE_LEN) - 1) << DSP2_MIDDLE4_TH_BASE_R_PRE_POS))
#define DSP2_MIDDLE4_TH_BASE_G_PRE       DSP2_MIDDLE4_TH_BASE_G_PRE
#define DSP2_MIDDLE4_TH_BASE_G_PRE_POS   (16U)
#define DSP2_MIDDLE4_TH_BASE_G_PRE_LEN   (10U)
#define DSP2_MIDDLE4_TH_BASE_G_PRE_MSK   (((1U << DSP2_MIDDLE4_TH_BASE_G_PRE_LEN) - 1) << DSP2_MIDDLE4_TH_BASE_G_PRE_POS)
#define DSP2_MIDDLE4_TH_BASE_G_PRE_UMSK  (~(((1U << DSP2_MIDDLE4_TH_BASE_G_PRE_LEN) - 1) << DSP2_MIDDLE4_TH_BASE_G_PRE_POS))

/* 0x608 : bnr_config_2 */
#define DSP2_MIDDLE4_BNR_CONFIG_2_OFFSET (0x608)
#define DSP2_MIDDLE4_TH_SLOPE_R_PRE      DSP2_MIDDLE4_TH_SLOPE_R_PRE
#define DSP2_MIDDLE4_TH_SLOPE_R_PRE_POS  (0U)
#define DSP2_MIDDLE4_TH_SLOPE_R_PRE_LEN  (8U)
#define DSP2_MIDDLE4_TH_SLOPE_R_PRE_MSK  (((1U << DSP2_MIDDLE4_TH_SLOPE_R_PRE_LEN) - 1) << DSP2_MIDDLE4_TH_SLOPE_R_PRE_POS)
#define DSP2_MIDDLE4_TH_SLOPE_R_PRE_UMSK (~(((1U << DSP2_MIDDLE4_TH_SLOPE_R_PRE_LEN) - 1) << DSP2_MIDDLE4_TH_SLOPE_R_PRE_POS))
#define DSP2_MIDDLE4_TH_SLOPE_G_PRE      DSP2_MIDDLE4_TH_SLOPE_G_PRE
#define DSP2_MIDDLE4_TH_SLOPE_G_PRE_POS  (8U)
#define DSP2_MIDDLE4_TH_SLOPE_G_PRE_LEN  (8U)
#define DSP2_MIDDLE4_TH_SLOPE_G_PRE_MSK  (((1U << DSP2_MIDDLE4_TH_SLOPE_G_PRE_LEN) - 1) << DSP2_MIDDLE4_TH_SLOPE_G_PRE_POS)
#define DSP2_MIDDLE4_TH_SLOPE_G_PRE_UMSK (~(((1U << DSP2_MIDDLE4_TH_SLOPE_G_PRE_LEN) - 1) << DSP2_MIDDLE4_TH_SLOPE_G_PRE_POS))
#define DSP2_MIDDLE4_TH_SLOPE_B_PRE      DSP2_MIDDLE4_TH_SLOPE_B_PRE
#define DSP2_MIDDLE4_TH_SLOPE_B_PRE_POS  (16U)
#define DSP2_MIDDLE4_TH_SLOPE_B_PRE_LEN  (8U)
#define DSP2_MIDDLE4_TH_SLOPE_B_PRE_MSK  (((1U << DSP2_MIDDLE4_TH_SLOPE_B_PRE_LEN) - 1) << DSP2_MIDDLE4_TH_SLOPE_B_PRE_POS)
#define DSP2_MIDDLE4_TH_SLOPE_B_PRE_UMSK (~(((1U << DSP2_MIDDLE4_TH_SLOPE_B_PRE_LEN) - 1) << DSP2_MIDDLE4_TH_SLOPE_B_PRE_POS))
#define DSP2_MIDDLE4_SLOPE_GAIN_PRE      DSP2_MIDDLE4_SLOPE_GAIN_PRE
#define DSP2_MIDDLE4_SLOPE_GAIN_PRE_POS  (24U)
#define DSP2_MIDDLE4_SLOPE_GAIN_PRE_LEN  (6U)
#define DSP2_MIDDLE4_SLOPE_GAIN_PRE_MSK  (((1U << DSP2_MIDDLE4_SLOPE_GAIN_PRE_LEN) - 1) << DSP2_MIDDLE4_SLOPE_GAIN_PRE_POS)
#define DSP2_MIDDLE4_SLOPE_GAIN_PRE_UMSK (~(((1U << DSP2_MIDDLE4_SLOPE_GAIN_PRE_LEN) - 1) << DSP2_MIDDLE4_SLOPE_GAIN_PRE_POS))

/* 0x60C : bnr_config_3 */
#define DSP2_MIDDLE4_BNR_CONFIG_3_OFFSET    (0x60C)
#define DSP2_MIDDLE4_FB_LEVEL_PRE           DSP2_MIDDLE4_FB_LEVEL_PRE
#define DSP2_MIDDLE4_FB_LEVEL_PRE_POS       (0U)
#define DSP2_MIDDLE4_FB_LEVEL_PRE_LEN       (3U)
#define DSP2_MIDDLE4_FB_LEVEL_PRE_MSK       (((1U << DSP2_MIDDLE4_FB_LEVEL_PRE_LEN) - 1) << DSP2_MIDDLE4_FB_LEVEL_PRE_POS)
#define DSP2_MIDDLE4_FB_LEVEL_PRE_UMSK      (~(((1U << DSP2_MIDDLE4_FB_LEVEL_PRE_LEN) - 1) << DSP2_MIDDLE4_FB_LEVEL_PRE_POS))
#define DSP2_MIDDLE4_FB_LPF_WEIGHT_PRE      DSP2_MIDDLE4_FB_LPF_WEIGHT_PRE
#define DSP2_MIDDLE4_FB_LPF_WEIGHT_PRE_POS  (8U)
#define DSP2_MIDDLE4_FB_LPF_WEIGHT_PRE_LEN  (5U)
#define DSP2_MIDDLE4_FB_LPF_WEIGHT_PRE_MSK  (((1U << DSP2_MIDDLE4_FB_LPF_WEIGHT_PRE_LEN) - 1) << DSP2_MIDDLE4_FB_LPF_WEIGHT_PRE_POS)
#define DSP2_MIDDLE4_FB_LPF_WEIGHT_PRE_UMSK (~(((1U << DSP2_MIDDLE4_FB_LPF_WEIGHT_PRE_LEN) - 1) << DSP2_MIDDLE4_FB_LPF_WEIGHT_PRE_POS))

struct dsp2_middle4_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[1536];

    /* 0x600 : bnr_config_0 */
    union {
        struct {
            uint32_t bnr_weight_pre : 7;  /* [ 6: 0],        r/w,        0x0 */
            uint32_t bnr_en_pre     : 1;  /* [    7],        r/w,        0x0 */
            uint32_t lpf_weight_pre : 5;  /* [12: 8],        r/w,        0x0 */
            uint32_t reserved_13_15 : 3;  /* [15:13],       rsvd,        0x0 */
            uint32_t th_base_b_pre  : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31 : 6;  /* [31:26],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } bnr_config_0;

    /* 0x604 : bnr_config_1 */
    union {
        struct {
            uint32_t th_base_r_pre  : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t reserved_10_15 : 6;  /* [15:10],       rsvd,        0x0 */
            uint32_t th_base_g_pre  : 10; /* [25:16],        r/w,        0x0 */
            uint32_t reserved_26_31 : 6;  /* [31:26],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } bnr_config_1;

    /* 0x608 : bnr_config_2 */
    union {
        struct {
            uint32_t th_slope_r_pre : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t th_slope_g_pre : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t th_slope_b_pre : 8; /* [23:16],        r/w,        0x0 */
            uint32_t slope_gain_pre : 6; /* [29:24],        r/w,        0x0 */
            uint32_t reserved_30_31 : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } bnr_config_2;

    /* 0x60C : bnr_config_3 */
    union {
        struct {
            uint32_t fb_level_pre      : 3;  /* [ 2: 0],        r/w,        0x0 */
            uint32_t reserved_3_7      : 5;  /* [ 7: 3],       rsvd,        0x0 */
            uint32_t fb_lpf_weight_pre : 5;  /* [12: 8],        r/w,        0x0 */
            uint32_t reserved_13_31    : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } bnr_config_3;
};

typedef volatile struct dsp2_middle4_reg dsp2_middle4_reg_t;

#endif /* __DSP2_MIDDLE4_REG_H__ */
