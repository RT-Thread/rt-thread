/**
  ******************************************************************************
  * @file    dsp2_auto_reg.h
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
#ifndef __DSP2_AUTO_REG_H__
#define __DSP2_AUTO_REG_H__

#include "bl808.h"

/* 0x444 : afwas */
#define DSP2_AUTO_AFWAS_OFFSET  (0x444)
#define DSP2_AUTO_AFWASX_W      DSP2_AUTO_AFWASX_W
#define DSP2_AUTO_AFWASX_W_POS  (16U)
#define DSP2_AUTO_AFWASX_W_LEN  (8U)
#define DSP2_AUTO_AFWASX_W_MSK  (((1U << DSP2_AUTO_AFWASX_W_LEN) - 1) << DSP2_AUTO_AFWASX_W_POS)
#define DSP2_AUTO_AFWASX_W_UMSK (~(((1U << DSP2_AUTO_AFWASX_W_LEN) - 1) << DSP2_AUTO_AFWASX_W_POS))
#define DSP2_AUTO_AFWASY_W      DSP2_AUTO_AFWASY_W
#define DSP2_AUTO_AFWASY_W_POS  (24U)
#define DSP2_AUTO_AFWASY_W_LEN  (8U)
#define DSP2_AUTO_AFWASY_W_MSK  (((1U << DSP2_AUTO_AFWASY_W_LEN) - 1) << DSP2_AUTO_AFWASY_W_POS)
#define DSP2_AUTO_AFWASY_W_UMSK (~(((1U << DSP2_AUTO_AFWASY_W_LEN) - 1) << DSP2_AUTO_AFWASY_W_POS))

/* 0x448 : afwae_afwbs */
#define DSP2_AUTO_AFWAE_AFWBS_OFFSET (0x448)
#define DSP2_AUTO_AFWAEX_W           DSP2_AUTO_AFWAEX_W
#define DSP2_AUTO_AFWAEX_W_POS       (0U)
#define DSP2_AUTO_AFWAEX_W_LEN       (8U)
#define DSP2_AUTO_AFWAEX_W_MSK       (((1U << DSP2_AUTO_AFWAEX_W_LEN) - 1) << DSP2_AUTO_AFWAEX_W_POS)
#define DSP2_AUTO_AFWAEX_W_UMSK      (~(((1U << DSP2_AUTO_AFWAEX_W_LEN) - 1) << DSP2_AUTO_AFWAEX_W_POS))
#define DSP2_AUTO_AFWAEY_W           DSP2_AUTO_AFWAEY_W
#define DSP2_AUTO_AFWAEY_W_POS       (8U)
#define DSP2_AUTO_AFWAEY_W_LEN       (8U)
#define DSP2_AUTO_AFWAEY_W_MSK       (((1U << DSP2_AUTO_AFWAEY_W_LEN) - 1) << DSP2_AUTO_AFWAEY_W_POS)
#define DSP2_AUTO_AFWAEY_W_UMSK      (~(((1U << DSP2_AUTO_AFWAEY_W_LEN) - 1) << DSP2_AUTO_AFWAEY_W_POS))
#define DSP2_AUTO_AFWBSX_W           DSP2_AUTO_AFWBSX_W
#define DSP2_AUTO_AFWBSX_W_POS       (16U)
#define DSP2_AUTO_AFWBSX_W_LEN       (8U)
#define DSP2_AUTO_AFWBSX_W_MSK       (((1U << DSP2_AUTO_AFWBSX_W_LEN) - 1) << DSP2_AUTO_AFWBSX_W_POS)
#define DSP2_AUTO_AFWBSX_W_UMSK      (~(((1U << DSP2_AUTO_AFWBSX_W_LEN) - 1) << DSP2_AUTO_AFWBSX_W_POS))
#define DSP2_AUTO_AFWBSY_W           DSP2_AUTO_AFWBSY_W
#define DSP2_AUTO_AFWBSY_W_POS       (24U)
#define DSP2_AUTO_AFWBSY_W_LEN       (8U)
#define DSP2_AUTO_AFWBSY_W_MSK       (((1U << DSP2_AUTO_AFWBSY_W_LEN) - 1) << DSP2_AUTO_AFWBSY_W_POS)
#define DSP2_AUTO_AFWBSY_W_UMSK      (~(((1U << DSP2_AUTO_AFWBSY_W_LEN) - 1) << DSP2_AUTO_AFWBSY_W_POS))

/* 0x44C : afbae_afmisc */
#define DSP2_AUTO_AFBAE_AFMISC_OFFSET (0x44C)
#define DSP2_AUTO_AFWBEX_W            DSP2_AUTO_AFWBEX_W
#define DSP2_AUTO_AFWBEX_W_POS        (0U)
#define DSP2_AUTO_AFWBEX_W_LEN        (8U)
#define DSP2_AUTO_AFWBEX_W_MSK        (((1U << DSP2_AUTO_AFWBEX_W_LEN) - 1) << DSP2_AUTO_AFWBEX_W_POS)
#define DSP2_AUTO_AFWBEX_W_UMSK       (~(((1U << DSP2_AUTO_AFWBEX_W_LEN) - 1) << DSP2_AUTO_AFWBEX_W_POS))
#define DSP2_AUTO_AFWBEY_W            DSP2_AUTO_AFWBEY_W
#define DSP2_AUTO_AFWBEY_W_POS        (8U)
#define DSP2_AUTO_AFWBEY_W_LEN        (8U)
#define DSP2_AUTO_AFWBEY_W_MSK        (((1U << DSP2_AUTO_AFWBEY_W_LEN) - 1) << DSP2_AUTO_AFWBEY_W_POS)
#define DSP2_AUTO_AFWBEY_W_UMSK       (~(((1U << DSP2_AUTO_AFWBEY_W_LEN) - 1) << DSP2_AUTO_AFWBEY_W_POS))
#define DSP2_AUTO_FCORE2_W            DSP2_AUTO_FCORE2_W
#define DSP2_AUTO_FCORE2_W_POS        (16U)
#define DSP2_AUTO_FCORE2_W_LEN        (4U)
#define DSP2_AUTO_FCORE2_W_MSK        (((1U << DSP2_AUTO_FCORE2_W_LEN) - 1) << DSP2_AUTO_FCORE2_W_POS)
#define DSP2_AUTO_FCORE2_W_UMSK       (~(((1U << DSP2_AUTO_FCORE2_W_LEN) - 1) << DSP2_AUTO_FCORE2_W_POS))
#define DSP2_AUTO_FCORE1_W            DSP2_AUTO_FCORE1_W
#define DSP2_AUTO_FCORE1_W_POS        (20U)
#define DSP2_AUTO_FCORE1_W_LEN        (4U)
#define DSP2_AUTO_FCORE1_W_MSK        (((1U << DSP2_AUTO_FCORE1_W_LEN) - 1) << DSP2_AUTO_FCORE1_W_POS)
#define DSP2_AUTO_FCORE1_W_UMSK       (~(((1U << DSP2_AUTO_FCORE1_W_LEN) - 1) << DSP2_AUTO_FCORE1_W_POS))
#define DSP2_AUTO_AFGAMMA_W           DSP2_AUTO_AFGAMMA_W
#define DSP2_AUTO_AFGAMMA_W_POS       (24U)
#define DSP2_AUTO_AFGAMMA_W_LEN       (3U)
#define DSP2_AUTO_AFGAMMA_W_MSK       (((1U << DSP2_AUTO_AFGAMMA_W_LEN) - 1) << DSP2_AUTO_AFGAMMA_W_POS)
#define DSP2_AUTO_AFGAMMA_W_UMSK      (~(((1U << DSP2_AUTO_AFGAMMA_W_LEN) - 1) << DSP2_AUTO_AFGAMMA_W_POS))
#define DSP2_AUTO_SUM_SHIFT_B_W       DSP2_AUTO_SUM_SHIFT_B_W
#define DSP2_AUTO_SUM_SHIFT_B_W_POS   (27U)
#define DSP2_AUTO_SUM_SHIFT_B_W_LEN   (3U)
#define DSP2_AUTO_SUM_SHIFT_B_W_MSK   (((1U << DSP2_AUTO_SUM_SHIFT_B_W_LEN) - 1) << DSP2_AUTO_SUM_SHIFT_B_W_POS)
#define DSP2_AUTO_SUM_SHIFT_B_W_UMSK  (~(((1U << DSP2_AUTO_SUM_SHIFT_B_W_LEN) - 1) << DSP2_AUTO_SUM_SHIFT_B_W_POS))
#define DSP2_AUTO_SUM_SHIFT_A_W       DSP2_AUTO_SUM_SHIFT_A_W
#define DSP2_AUTO_SUM_SHIFT_A_W_POS   (30U)
#define DSP2_AUTO_SUM_SHIFT_A_W_LEN   (2U)
#define DSP2_AUTO_SUM_SHIFT_A_W_MSK   (((1U << DSP2_AUTO_SUM_SHIFT_A_W_LEN) - 1) << DSP2_AUTO_SUM_SHIFT_A_W_POS)
#define DSP2_AUTO_SUM_SHIFT_A_W_UMSK  (~(((1U << DSP2_AUTO_SUM_SHIFT_A_W_LEN) - 1) << DSP2_AUTO_SUM_SHIFT_A_W_POS))

/* 0x450 : afwah */
#define DSP2_AUTO_AFWAH_OFFSET  (0x450)
#define DSP2_AUTO_AFWAH1_R      DSP2_AUTO_AFWAH1_R
#define DSP2_AUTO_AFWAH1_R_POS  (0U)
#define DSP2_AUTO_AFWAH1_R_LEN  (16U)
#define DSP2_AUTO_AFWAH1_R_MSK  (((1U << DSP2_AUTO_AFWAH1_R_LEN) - 1) << DSP2_AUTO_AFWAH1_R_POS)
#define DSP2_AUTO_AFWAH1_R_UMSK (~(((1U << DSP2_AUTO_AFWAH1_R_LEN) - 1) << DSP2_AUTO_AFWAH1_R_POS))
#define DSP2_AUTO_AFWAH2_R      DSP2_AUTO_AFWAH2_R
#define DSP2_AUTO_AFWAH2_R_POS  (16U)
#define DSP2_AUTO_AFWAH2_R_LEN  (16U)
#define DSP2_AUTO_AFWAH2_R_MSK  (((1U << DSP2_AUTO_AFWAH2_R_LEN) - 1) << DSP2_AUTO_AFWAH2_R_POS)
#define DSP2_AUTO_AFWAH2_R_UMSK (~(((1U << DSP2_AUTO_AFWAH2_R_LEN) - 1) << DSP2_AUTO_AFWAH2_R_POS))

/* 0x454 : afwbh */
#define DSP2_AUTO_AFWBH_OFFSET  (0x454)
#define DSP2_AUTO_AFWBH1_R      DSP2_AUTO_AFWBH1_R
#define DSP2_AUTO_AFWBH1_R_POS  (0U)
#define DSP2_AUTO_AFWBH1_R_LEN  (16U)
#define DSP2_AUTO_AFWBH1_R_MSK  (((1U << DSP2_AUTO_AFWBH1_R_LEN) - 1) << DSP2_AUTO_AFWBH1_R_POS)
#define DSP2_AUTO_AFWBH1_R_UMSK (~(((1U << DSP2_AUTO_AFWBH1_R_LEN) - 1) << DSP2_AUTO_AFWBH1_R_POS))
#define DSP2_AUTO_AFWBH2_R      DSP2_AUTO_AFWBH2_R
#define DSP2_AUTO_AFWBH2_R_POS  (16U)
#define DSP2_AUTO_AFWBH2_R_LEN  (16U)
#define DSP2_AUTO_AFWBH2_R_MSK  (((1U << DSP2_AUTO_AFWBH2_R_LEN) - 1) << DSP2_AUTO_AFWBH2_R_POS)
#define DSP2_AUTO_AFWBH2_R_UMSK (~(((1U << DSP2_AUTO_AFWBH2_R_LEN) - 1) << DSP2_AUTO_AFWBH2_R_POS))

struct dsp2_auto_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[1092];

    /* 0x444 : afwas */
    union {
        struct {
            uint32_t reserved_0_15 : 16; /* [15: 0],       rsvd,        0x0 */
            uint32_t afwasx_w      : 8;  /* [23:16],        r/w,        0x0 */
            uint32_t afwasy_w      : 8;  /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } afwas;

    /* 0x448 : afwae_afwbs */
    union {
        struct {
            uint32_t afwaex_w : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t afwaey_w : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t afwbsx_w : 8; /* [23:16],        r/w,        0x0 */
            uint32_t afwbsy_w : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } afwae_afwbs;

    /* 0x44C : afbae_afmisc */
    union {
        struct {
            uint32_t afwbex_w      : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t afwbey_w      : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t fcore2_w      : 4; /* [19:16],        r/w,        0x0 */
            uint32_t fcore1_w      : 4; /* [23:20],        r/w,        0x0 */
            uint32_t AFGamma_w     : 3; /* [26:24],        r/w,        0x0 */
            uint32_t sum_shift_b_w : 3; /* [29:27],        r/w,        0x0 */
            uint32_t sum_shift_a_w : 2; /* [31:30],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } afbae_afmisc;

    /* 0x450 : afwah */
    union {
        struct {
            uint32_t afwah1_r : 16; /* [15: 0],          r,        0x0 */
            uint32_t afwah2_r : 16; /* [31:16],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } afwah;

    /* 0x454 : afwbh */
    union {
        struct {
            uint32_t afwbh1_r : 16; /* [15: 0],          r,        0x0 */
            uint32_t afwbh2_r : 16; /* [31:16],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } afwbh;
};

typedef volatile struct dsp2_auto_reg dsp2_auto_reg_t;

#endif /* __DSP2_AUTO_REG_H__ */
