/**
  ******************************************************************************
  * @file    pdm_reg.h
  * @version V1.0
  * @date    2021-07-19
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
#ifndef __PDM_REG_H__
#define __PDM_REG_H__

#include "bl808.h"

/* 0xC00 : audpdm_top */
#define PDM_AUDPDM_TOP_OFFSET    (0xC00)
#define PDM_AUDIO_CKG_EN         PDM_AUDIO_CKG_EN
#define PDM_AUDIO_CKG_EN_POS     (0U)
#define PDM_AUDIO_CKG_EN_LEN     (1U)
#define PDM_AUDIO_CKG_EN_MSK     (((1U << PDM_AUDIO_CKG_EN_LEN) - 1) << PDM_AUDIO_CKG_EN_POS)
#define PDM_AUDIO_CKG_EN_UMSK    (~(((1U << PDM_AUDIO_CKG_EN_LEN) - 1) << PDM_AUDIO_CKG_EN_POS))
#define PDM_ADC_ITF_INV_SEL      PDM_ADC_ITF_INV_SEL
#define PDM_ADC_ITF_INV_SEL_POS  (2U)
#define PDM_ADC_ITF_INV_SEL_LEN  (1U)
#define PDM_ADC_ITF_INV_SEL_MSK  (((1U << PDM_ADC_ITF_INV_SEL_LEN) - 1) << PDM_ADC_ITF_INV_SEL_POS)
#define PDM_ADC_ITF_INV_SEL_UMSK (~(((1U << PDM_ADC_ITF_INV_SEL_LEN) - 1) << PDM_ADC_ITF_INV_SEL_POS))
#define PDM_ITF_INV_SEL          PDM_ITF_INV_SEL
#define PDM_ITF_INV_SEL_POS      (3U)
#define PDM_ITF_INV_SEL_LEN      (1U)
#define PDM_ITF_INV_SEL_MSK      (((1U << PDM_ITF_INV_SEL_LEN) - 1) << PDM_ITF_INV_SEL_POS)
#define PDM_ITF_INV_SEL_UMSK     (~(((1U << PDM_ITF_INV_SEL_LEN) - 1) << PDM_ITF_INV_SEL_POS))
#define PDM_ADC_RATE             PDM_ADC_RATE
#define PDM_ADC_RATE_POS         (28U)
#define PDM_ADC_RATE_LEN         (3U)
#define PDM_ADC_RATE_MSK         (((1U << PDM_ADC_RATE_LEN) - 1) << PDM_ADC_RATE_POS)
#define PDM_ADC_RATE_UMSK        (~(((1U << PDM_ADC_RATE_LEN) - 1) << PDM_ADC_RATE_POS))

/* 0xC04 : audpdm_itf */
#define PDM_AUDPDM_ITF_OFFSET (0xC04)
#define PDM_ADC_0_EN          PDM_ADC_0_EN
#define PDM_ADC_0_EN_POS      (0U)
#define PDM_ADC_0_EN_LEN      (1U)
#define PDM_ADC_0_EN_MSK      (((1U << PDM_ADC_0_EN_LEN) - 1) << PDM_ADC_0_EN_POS)
#define PDM_ADC_0_EN_UMSK     (~(((1U << PDM_ADC_0_EN_LEN) - 1) << PDM_ADC_0_EN_POS))
#define PDM_ADC_1_EN          PDM_ADC_1_EN
#define PDM_ADC_1_EN_POS      (1U)
#define PDM_ADC_1_EN_LEN      (1U)
#define PDM_ADC_1_EN_MSK      (((1U << PDM_ADC_1_EN_LEN) - 1) << PDM_ADC_1_EN_POS)
#define PDM_ADC_1_EN_UMSK     (~(((1U << PDM_ADC_1_EN_LEN) - 1) << PDM_ADC_1_EN_POS))
#define PDM_ADC_2_EN          PDM_ADC_2_EN
#define PDM_ADC_2_EN_POS      (2U)
#define PDM_ADC_2_EN_LEN      (1U)
#define PDM_ADC_2_EN_MSK      (((1U << PDM_ADC_2_EN_LEN) - 1) << PDM_ADC_2_EN_POS)
#define PDM_ADC_2_EN_UMSK     (~(((1U << PDM_ADC_2_EN_LEN) - 1) << PDM_ADC_2_EN_POS))
#define PDM_AUD_RX0_SEL       PDM_AUD_RX0_SEL
#define PDM_AUD_RX0_SEL_POS   (13U)
#define PDM_AUD_RX0_SEL_LEN   (3U)
#define PDM_AUD_RX0_SEL_MSK   (((1U << PDM_AUD_RX0_SEL_LEN) - 1) << PDM_AUD_RX0_SEL_POS)
#define PDM_AUD_RX0_SEL_UMSK  (~(((1U << PDM_AUD_RX0_SEL_LEN) - 1) << PDM_AUD_RX0_SEL_POS))
#define PDM_AUD_RX1_SEL       PDM_AUD_RX1_SEL
#define PDM_AUD_RX1_SEL_POS   (16U)
#define PDM_AUD_RX1_SEL_LEN   (3U)
#define PDM_AUD_RX1_SEL_MSK   (((1U << PDM_AUD_RX1_SEL_LEN) - 1) << PDM_AUD_RX1_SEL_POS)
#define PDM_AUD_RX1_SEL_UMSK  (~(((1U << PDM_AUD_RX1_SEL_LEN) - 1) << PDM_AUD_RX1_SEL_POS))
#define PDM_AUD_RX2_SEL       PDM_AUD_RX2_SEL
#define PDM_AUD_RX2_SEL_POS   (19U)
#define PDM_AUD_RX2_SEL_LEN   (3U)
#define PDM_AUD_RX2_SEL_MSK   (((1U << PDM_AUD_RX2_SEL_LEN) - 1) << PDM_AUD_RX2_SEL_POS)
#define PDM_AUD_RX2_SEL_UMSK  (~(((1U << PDM_AUD_RX2_SEL_LEN) - 1) << PDM_AUD_RX2_SEL_POS))
#define PDM_ADC_ITF_EN        PDM_ADC_ITF_EN
#define PDM_ADC_ITF_EN_POS    (30U)
#define PDM_ADC_ITF_EN_LEN    (1U)
#define PDM_ADC_ITF_EN_MSK    (((1U << PDM_ADC_ITF_EN_LEN) - 1) << PDM_ADC_ITF_EN_POS)
#define PDM_ADC_ITF_EN_UMSK   (~(((1U << PDM_ADC_ITF_EN_LEN) - 1) << PDM_ADC_ITF_EN_POS))

/* 0xC08 : pdm_adc_0 */
#define PDM_ADC_0_OFFSET        (0xC08)
#define PDM_ADC_0_FIR_MODE      PDM_ADC_0_FIR_MODE
#define PDM_ADC_0_FIR_MODE_POS  (0U)
#define PDM_ADC_0_FIR_MODE_LEN  (1U)
#define PDM_ADC_0_FIR_MODE_MSK  (((1U << PDM_ADC_0_FIR_MODE_LEN) - 1) << PDM_ADC_0_FIR_MODE_POS)
#define PDM_ADC_0_FIR_MODE_UMSK (~(((1U << PDM_ADC_0_FIR_MODE_LEN) - 1) << PDM_ADC_0_FIR_MODE_POS))
#define PDM_ADC_1_FIR_MODE      PDM_ADC_1_FIR_MODE
#define PDM_ADC_1_FIR_MODE_POS  (1U)
#define PDM_ADC_1_FIR_MODE_LEN  (1U)
#define PDM_ADC_1_FIR_MODE_MSK  (((1U << PDM_ADC_1_FIR_MODE_LEN) - 1) << PDM_ADC_1_FIR_MODE_POS)
#define PDM_ADC_1_FIR_MODE_UMSK (~(((1U << PDM_ADC_1_FIR_MODE_LEN) - 1) << PDM_ADC_1_FIR_MODE_POS))
#define PDM_ADC_2_FIR_MODE      PDM_ADC_2_FIR_MODE
#define PDM_ADC_2_FIR_MODE_POS  (2U)
#define PDM_ADC_2_FIR_MODE_LEN  (1U)
#define PDM_ADC_2_FIR_MODE_MSK  (((1U << PDM_ADC_2_FIR_MODE_LEN) - 1) << PDM_ADC_2_FIR_MODE_POS)
#define PDM_ADC_2_FIR_MODE_UMSK (~(((1U << PDM_ADC_2_FIR_MODE_LEN) - 1) << PDM_ADC_2_FIR_MODE_POS))
#define PDM_ADC_0_SCAL          PDM_ADC_0_SCAL
#define PDM_ADC_0_SCAL_POS      (3U)
#define PDM_ADC_0_SCAL_LEN      (6U)
#define PDM_ADC_0_SCAL_MSK      (((1U << PDM_ADC_0_SCAL_LEN) - 1) << PDM_ADC_0_SCAL_POS)
#define PDM_ADC_0_SCAL_UMSK     (~(((1U << PDM_ADC_0_SCAL_LEN) - 1) << PDM_ADC_0_SCAL_POS))
#define PDM_ADC_1_SCAL          PDM_ADC_1_SCAL
#define PDM_ADC_1_SCAL_POS      (9U)
#define PDM_ADC_1_SCAL_LEN      (6U)
#define PDM_ADC_1_SCAL_MSK      (((1U << PDM_ADC_1_SCAL_LEN) - 1) << PDM_ADC_1_SCAL_POS)
#define PDM_ADC_1_SCAL_UMSK     (~(((1U << PDM_ADC_1_SCAL_LEN) - 1) << PDM_ADC_1_SCAL_POS))
#define PDM_ADC_2_SCAL          PDM_ADC_2_SCAL
#define PDM_ADC_2_SCAL_POS      (15U)
#define PDM_ADC_2_SCAL_LEN      (6U)
#define PDM_ADC_2_SCAL_MSK      (((1U << PDM_ADC_2_SCAL_LEN) - 1) << PDM_ADC_2_SCAL_POS)
#define PDM_ADC_2_SCAL_UMSK     (~(((1U << PDM_ADC_2_SCAL_LEN) - 1) << PDM_ADC_2_SCAL_POS))

/* 0xC0C : pdm_adc_1 */
#define PDM_ADC_1_OFFSET     (0xC0C)
#define PDM_ADC_0_K1         PDM_ADC_0_K1
#define PDM_ADC_0_K1_POS     (0U)
#define PDM_ADC_0_K1_LEN     (4U)
#define PDM_ADC_0_K1_MSK     (((1U << PDM_ADC_0_K1_LEN) - 1) << PDM_ADC_0_K1_POS)
#define PDM_ADC_0_K1_UMSK    (~(((1U << PDM_ADC_0_K1_LEN) - 1) << PDM_ADC_0_K1_POS))
#define PDM_ADC_0_K1_EN      PDM_ADC_0_K1_EN
#define PDM_ADC_0_K1_EN_POS  (4U)
#define PDM_ADC_0_K1_EN_LEN  (1U)
#define PDM_ADC_0_K1_EN_MSK  (((1U << PDM_ADC_0_K1_EN_LEN) - 1) << PDM_ADC_0_K1_EN_POS)
#define PDM_ADC_0_K1_EN_UMSK (~(((1U << PDM_ADC_0_K1_EN_LEN) - 1) << PDM_ADC_0_K1_EN_POS))
#define PDM_ADC_0_K2         PDM_ADC_0_K2
#define PDM_ADC_0_K2_POS     (5U)
#define PDM_ADC_0_K2_LEN     (4U)
#define PDM_ADC_0_K2_MSK     (((1U << PDM_ADC_0_K2_LEN) - 1) << PDM_ADC_0_K2_POS)
#define PDM_ADC_0_K2_UMSK    (~(((1U << PDM_ADC_0_K2_LEN) - 1) << PDM_ADC_0_K2_POS))
#define PDM_ADC_0_K2_EN      PDM_ADC_0_K2_EN
#define PDM_ADC_0_K2_EN_POS  (9U)
#define PDM_ADC_0_K2_EN_LEN  (1U)
#define PDM_ADC_0_K2_EN_MSK  (((1U << PDM_ADC_0_K2_EN_LEN) - 1) << PDM_ADC_0_K2_EN_POS)
#define PDM_ADC_0_K2_EN_UMSK (~(((1U << PDM_ADC_0_K2_EN_LEN) - 1) << PDM_ADC_0_K2_EN_POS))
#define PDM_ADC_1_K1         PDM_ADC_1_K1
#define PDM_ADC_1_K1_POS     (10U)
#define PDM_ADC_1_K1_LEN     (4U)
#define PDM_ADC_1_K1_MSK     (((1U << PDM_ADC_1_K1_LEN) - 1) << PDM_ADC_1_K1_POS)
#define PDM_ADC_1_K1_UMSK    (~(((1U << PDM_ADC_1_K1_LEN) - 1) << PDM_ADC_1_K1_POS))
#define PDM_ADC_1_K1_EN      PDM_ADC_1_K1_EN
#define PDM_ADC_1_K1_EN_POS  (14U)
#define PDM_ADC_1_K1_EN_LEN  (1U)
#define PDM_ADC_1_K1_EN_MSK  (((1U << PDM_ADC_1_K1_EN_LEN) - 1) << PDM_ADC_1_K1_EN_POS)
#define PDM_ADC_1_K1_EN_UMSK (~(((1U << PDM_ADC_1_K1_EN_LEN) - 1) << PDM_ADC_1_K1_EN_POS))
#define PDM_ADC_1_K2         PDM_ADC_1_K2
#define PDM_ADC_1_K2_POS     (15U)
#define PDM_ADC_1_K2_LEN     (4U)
#define PDM_ADC_1_K2_MSK     (((1U << PDM_ADC_1_K2_LEN) - 1) << PDM_ADC_1_K2_POS)
#define PDM_ADC_1_K2_UMSK    (~(((1U << PDM_ADC_1_K2_LEN) - 1) << PDM_ADC_1_K2_POS))
#define PDM_ADC_1_K2_EN      PDM_ADC_1_K2_EN
#define PDM_ADC_1_K2_EN_POS  (19U)
#define PDM_ADC_1_K2_EN_LEN  (1U)
#define PDM_ADC_1_K2_EN_MSK  (((1U << PDM_ADC_1_K2_EN_LEN) - 1) << PDM_ADC_1_K2_EN_POS)
#define PDM_ADC_1_K2_EN_UMSK (~(((1U << PDM_ADC_1_K2_EN_LEN) - 1) << PDM_ADC_1_K2_EN_POS))
#define PDM_ADC_2_K1         PDM_ADC_2_K1
#define PDM_ADC_2_K1_POS     (20U)
#define PDM_ADC_2_K1_LEN     (4U)
#define PDM_ADC_2_K1_MSK     (((1U << PDM_ADC_2_K1_LEN) - 1) << PDM_ADC_2_K1_POS)
#define PDM_ADC_2_K1_UMSK    (~(((1U << PDM_ADC_2_K1_LEN) - 1) << PDM_ADC_2_K1_POS))
#define PDM_ADC_2_K1_EN      PDM_ADC_2_K1_EN
#define PDM_ADC_2_K1_EN_POS  (24U)
#define PDM_ADC_2_K1_EN_LEN  (1U)
#define PDM_ADC_2_K1_EN_MSK  (((1U << PDM_ADC_2_K1_EN_LEN) - 1) << PDM_ADC_2_K1_EN_POS)
#define PDM_ADC_2_K1_EN_UMSK (~(((1U << PDM_ADC_2_K1_EN_LEN) - 1) << PDM_ADC_2_K1_EN_POS))
#define PDM_ADC_2_K2         PDM_ADC_2_K2
#define PDM_ADC_2_K2_POS     (25U)
#define PDM_ADC_2_K2_LEN     (4U)
#define PDM_ADC_2_K2_MSK     (((1U << PDM_ADC_2_K2_LEN) - 1) << PDM_ADC_2_K2_POS)
#define PDM_ADC_2_K2_UMSK    (~(((1U << PDM_ADC_2_K2_LEN) - 1) << PDM_ADC_2_K2_POS))
#define PDM_ADC_2_K2_EN      PDM_ADC_2_K2_EN
#define PDM_ADC_2_K2_EN_POS  (29U)
#define PDM_ADC_2_K2_EN_LEN  (1U)
#define PDM_ADC_2_K2_EN_MSK  (((1U << PDM_ADC_2_K2_EN_LEN) - 1) << PDM_ADC_2_K2_EN_POS)
#define PDM_ADC_2_K2_EN_UMSK (~(((1U << PDM_ADC_2_K2_EN_LEN) - 1) << PDM_ADC_2_K2_EN_POS))

/* 0xC10 : pdm_dac_0 */
#define PDM_DAC_0_OFFSET            (0xC10)
#define PDM_ADC_PDM_H               PDM_ADC_PDM_H
#define PDM_ADC_PDM_H_POS           (0U)
#define PDM_ADC_PDM_H_LEN           (6U)
#define PDM_ADC_PDM_H_MSK           (((1U << PDM_ADC_PDM_H_LEN) - 1) << PDM_ADC_PDM_H_POS)
#define PDM_ADC_PDM_H_UMSK          (~(((1U << PDM_ADC_PDM_H_LEN) - 1) << PDM_ADC_PDM_H_POS))
#define PDM_ADC_PDM_L               PDM_ADC_PDM_L
#define PDM_ADC_PDM_L_POS           (6U)
#define PDM_ADC_PDM_L_LEN           (6U)
#define PDM_ADC_PDM_L_MSK           (((1U << PDM_ADC_PDM_L_LEN) - 1) << PDM_ADC_PDM_L_POS)
#define PDM_ADC_PDM_L_UMSK          (~(((1U << PDM_ADC_PDM_L_LEN) - 1) << PDM_ADC_PDM_L_POS))
#define PDM_ADC_0_PDM_LVL_SWAP      PDM_ADC_0_PDM_LVL_SWAP
#define PDM_ADC_0_PDM_LVL_SWAP_POS  (13U)
#define PDM_ADC_0_PDM_LVL_SWAP_LEN  (1U)
#define PDM_ADC_0_PDM_LVL_SWAP_MSK  (((1U << PDM_ADC_0_PDM_LVL_SWAP_LEN) - 1) << PDM_ADC_0_PDM_LVL_SWAP_POS)
#define PDM_ADC_0_PDM_LVL_SWAP_UMSK (~(((1U << PDM_ADC_0_PDM_LVL_SWAP_LEN) - 1) << PDM_ADC_0_PDM_LVL_SWAP_POS))
#define PDM_ADC_1_PDM_LVL_SWAP      PDM_ADC_1_PDM_LVL_SWAP
#define PDM_ADC_1_PDM_LVL_SWAP_POS  (16U)
#define PDM_ADC_1_PDM_LVL_SWAP_LEN  (1U)
#define PDM_ADC_1_PDM_LVL_SWAP_MSK  (((1U << PDM_ADC_1_PDM_LVL_SWAP_LEN) - 1) << PDM_ADC_1_PDM_LVL_SWAP_POS)
#define PDM_ADC_1_PDM_LVL_SWAP_UMSK (~(((1U << PDM_ADC_1_PDM_LVL_SWAP_LEN) - 1) << PDM_ADC_1_PDM_LVL_SWAP_POS))
#define PDM_ADC_2_PDM_LVL_SWAP      PDM_ADC_2_PDM_LVL_SWAP
#define PDM_ADC_2_PDM_LVL_SWAP_POS  (19U)
#define PDM_ADC_2_PDM_LVL_SWAP_LEN  (1U)
#define PDM_ADC_2_PDM_LVL_SWAP_MSK  (((1U << PDM_ADC_2_PDM_LVL_SWAP_LEN) - 1) << PDM_ADC_2_PDM_LVL_SWAP_POS)
#define PDM_ADC_2_PDM_LVL_SWAP_UMSK (~(((1U << PDM_ADC_2_PDM_LVL_SWAP_LEN) - 1) << PDM_ADC_2_PDM_LVL_SWAP_POS))

/* 0xC1C : pdm_pdm_0 */
#define PDM_PDM_0_OFFSET       (0xC1C)
#define PDM_0_EN               PDM_0_EN
#define PDM_0_EN_POS           (0U)
#define PDM_0_EN_LEN           (1U)
#define PDM_0_EN_MSK           (((1U << PDM_0_EN_LEN) - 1) << PDM_0_EN_POS)
#define PDM_0_EN_UMSK          (~(((1U << PDM_0_EN_LEN) - 1) << PDM_0_EN_POS))
#define PDM_1_EN               PDM_1_EN
#define PDM_1_EN_POS           (1U)
#define PDM_1_EN_LEN           (1U)
#define PDM_1_EN_MSK           (((1U << PDM_1_EN_LEN) - 1) << PDM_1_EN_POS)
#define PDM_1_EN_UMSK          (~(((1U << PDM_1_EN_LEN) - 1) << PDM_1_EN_POS))
#define PDM_2_EN               PDM_2_EN
#define PDM_2_EN_POS           (2U)
#define PDM_2_EN_LEN           (1U)
#define PDM_2_EN_MSK           (((1U << PDM_2_EN_LEN) - 1) << PDM_2_EN_POS)
#define PDM_2_EN_UMSK          (~(((1U << PDM_2_EN_LEN) - 1) << PDM_2_EN_POS))
#define PDM_ADC_0_PDM_SEL      PDM_ADC_0_PDM_SEL
#define PDM_ADC_0_PDM_SEL_POS  (3U)
#define PDM_ADC_0_PDM_SEL_LEN  (3U)
#define PDM_ADC_0_PDM_SEL_MSK  (((1U << PDM_ADC_0_PDM_SEL_LEN) - 1) << PDM_ADC_0_PDM_SEL_POS)
#define PDM_ADC_0_PDM_SEL_UMSK (~(((1U << PDM_ADC_0_PDM_SEL_LEN) - 1) << PDM_ADC_0_PDM_SEL_POS))
#define PDM_ADC_1_PDM_SEL      PDM_ADC_1_PDM_SEL
#define PDM_ADC_1_PDM_SEL_POS  (6U)
#define PDM_ADC_1_PDM_SEL_LEN  (3U)
#define PDM_ADC_1_PDM_SEL_MSK  (((1U << PDM_ADC_1_PDM_SEL_LEN) - 1) << PDM_ADC_1_PDM_SEL_POS)
#define PDM_ADC_1_PDM_SEL_UMSK (~(((1U << PDM_ADC_1_PDM_SEL_LEN) - 1) << PDM_ADC_1_PDM_SEL_POS))
#define PDM_ADC_2_PDM_SEL      PDM_ADC_2_PDM_SEL
#define PDM_ADC_2_PDM_SEL_POS  (9U)
#define PDM_ADC_2_PDM_SEL_LEN  (3U)
#define PDM_ADC_2_PDM_SEL_MSK  (((1U << PDM_ADC_2_PDM_SEL_LEN) - 1) << PDM_ADC_2_PDM_SEL_POS)
#define PDM_ADC_2_PDM_SEL_UMSK (~(((1U << PDM_ADC_2_PDM_SEL_LEN) - 1) << PDM_ADC_2_PDM_SEL_POS))

/* 0xC20 : pdm_rsvd0 */
#define PDM_RSVD0_OFFSET (0xC20)

/* 0xC24 : pdm_dbg_0 */
#define PDM_DBG_0_OFFSET           (0xC24)
#define PDM_ADC_TEST_CLKIN_EN      PDM_ADC_TEST_CLKIN_EN
#define PDM_ADC_TEST_CLKIN_EN_POS  (21U)
#define PDM_ADC_TEST_CLKIN_EN_LEN  (1U)
#define PDM_ADC_TEST_CLKIN_EN_MSK  (((1U << PDM_ADC_TEST_CLKIN_EN_LEN) - 1) << PDM_ADC_TEST_CLKIN_EN_POS)
#define PDM_ADC_TEST_CLKIN_EN_UMSK (~(((1U << PDM_ADC_TEST_CLKIN_EN_LEN) - 1) << PDM_ADC_TEST_CLKIN_EN_POS))
#define PDM_ADC_TEST_DIN_EN        PDM_ADC_TEST_DIN_EN
#define PDM_ADC_TEST_DIN_EN_POS    (23U)
#define PDM_ADC_TEST_DIN_EN_LEN    (1U)
#define PDM_ADC_TEST_DIN_EN_MSK    (((1U << PDM_ADC_TEST_DIN_EN_LEN) - 1) << PDM_ADC_TEST_DIN_EN_POS)
#define PDM_ADC_TEST_DIN_EN_UMSK   (~(((1U << PDM_ADC_TEST_DIN_EN_LEN) - 1) << PDM_ADC_TEST_DIN_EN_POS))
#define PDM_AUD_TEST_READ_SEL      PDM_AUD_TEST_READ_SEL
#define PDM_AUD_TEST_READ_SEL_POS  (24U)
#define PDM_AUD_TEST_READ_SEL_LEN  (6U)
#define PDM_AUD_TEST_READ_SEL_MSK  (((1U << PDM_AUD_TEST_READ_SEL_LEN) - 1) << PDM_AUD_TEST_READ_SEL_POS)
#define PDM_AUD_TEST_READ_SEL_UMSK (~(((1U << PDM_AUD_TEST_READ_SEL_LEN) - 1) << PDM_AUD_TEST_READ_SEL_POS))

/* 0xC28 : pdm_dbg_1 */
#define PDM_DBG_1_OFFSET       (0xC28)
#define PDM_AUD_TEST_READ      PDM_AUD_TEST_READ
#define PDM_AUD_TEST_READ_POS  (0U)
#define PDM_AUD_TEST_READ_LEN  (32U)
#define PDM_AUD_TEST_READ_MSK  (((1U << PDM_AUD_TEST_READ_LEN) - 1) << PDM_AUD_TEST_READ_POS)
#define PDM_AUD_TEST_READ_UMSK (~(((1U << PDM_AUD_TEST_READ_LEN) - 1) << PDM_AUD_TEST_READ_POS))

/* 0xC2C : pdm_dbg_2 */
#define PDM_DBG_2_OFFSET           (0xC2C)
#define PDM_ADC_FIR_4S_VAL         PDM_ADC_FIR_4S_VAL
#define PDM_ADC_FIR_4S_VAL_POS     (0U)
#define PDM_ADC_FIR_4S_VAL_LEN     (20U)
#define PDM_ADC_FIR_4S_VAL_MSK     (((1U << PDM_ADC_FIR_4S_VAL_LEN) - 1) << PDM_ADC_FIR_4S_VAL_POS)
#define PDM_ADC_FIR_4S_VAL_UMSK    (~(((1U << PDM_ADC_FIR_4S_VAL_LEN) - 1) << PDM_ADC_FIR_4S_VAL_POS))
#define PDM_ADC_0_FIR_4S_EN        PDM_ADC_0_FIR_4S_EN
#define PDM_ADC_0_FIR_4S_EN_POS    (20U)
#define PDM_ADC_0_FIR_4S_EN_LEN    (1U)
#define PDM_ADC_0_FIR_4S_EN_MSK    (((1U << PDM_ADC_0_FIR_4S_EN_LEN) - 1) << PDM_ADC_0_FIR_4S_EN_POS)
#define PDM_ADC_0_FIR_4S_EN_UMSK   (~(((1U << PDM_ADC_0_FIR_4S_EN_LEN) - 1) << PDM_ADC_0_FIR_4S_EN_POS))
#define PDM_ADC_1_FIR_4S_EN        PDM_ADC_1_FIR_4S_EN
#define PDM_ADC_1_FIR_4S_EN_POS    (21U)
#define PDM_ADC_1_FIR_4S_EN_LEN    (1U)
#define PDM_ADC_1_FIR_4S_EN_MSK    (((1U << PDM_ADC_1_FIR_4S_EN_LEN) - 1) << PDM_ADC_1_FIR_4S_EN_POS)
#define PDM_ADC_1_FIR_4S_EN_UMSK   (~(((1U << PDM_ADC_1_FIR_4S_EN_LEN) - 1) << PDM_ADC_1_FIR_4S_EN_POS))
#define PDM_ADC_2_FIR_4S_EN        PDM_ADC_2_FIR_4S_EN
#define PDM_ADC_2_FIR_4S_EN_POS    (22U)
#define PDM_ADC_2_FIR_4S_EN_LEN    (1U)
#define PDM_ADC_2_FIR_4S_EN_MSK    (((1U << PDM_ADC_2_FIR_4S_EN_LEN) - 1) << PDM_ADC_2_FIR_4S_EN_POS)
#define PDM_ADC_2_FIR_4S_EN_UMSK   (~(((1U << PDM_ADC_2_FIR_4S_EN_LEN) - 1) << PDM_ADC_2_FIR_4S_EN_POS))
#define PDM_ADC_IN_0_TEST_SEL      PDM_ADC_IN_0_TEST_SEL
#define PDM_ADC_IN_0_TEST_SEL_POS  (23U)
#define PDM_ADC_IN_0_TEST_SEL_LEN  (1U)
#define PDM_ADC_IN_0_TEST_SEL_MSK  (((1U << PDM_ADC_IN_0_TEST_SEL_LEN) - 1) << PDM_ADC_IN_0_TEST_SEL_POS)
#define PDM_ADC_IN_0_TEST_SEL_UMSK (~(((1U << PDM_ADC_IN_0_TEST_SEL_LEN) - 1) << PDM_ADC_IN_0_TEST_SEL_POS))
#define PDM_ADC_IN_1_TEST_SEL      PDM_ADC_IN_1_TEST_SEL
#define PDM_ADC_IN_1_TEST_SEL_POS  (24U)
#define PDM_ADC_IN_1_TEST_SEL_LEN  (1U)
#define PDM_ADC_IN_1_TEST_SEL_MSK  (((1U << PDM_ADC_IN_1_TEST_SEL_LEN) - 1) << PDM_ADC_IN_1_TEST_SEL_POS)
#define PDM_ADC_IN_1_TEST_SEL_UMSK (~(((1U << PDM_ADC_IN_1_TEST_SEL_LEN) - 1) << PDM_ADC_IN_1_TEST_SEL_POS))
#define PDM_ADC_IN_2_TEST_SEL      PDM_ADC_IN_2_TEST_SEL
#define PDM_ADC_IN_2_TEST_SEL_POS  (25U)
#define PDM_ADC_IN_2_TEST_SEL_LEN  (1U)
#define PDM_ADC_IN_2_TEST_SEL_MSK  (((1U << PDM_ADC_IN_2_TEST_SEL_LEN) - 1) << PDM_ADC_IN_2_TEST_SEL_POS)
#define PDM_ADC_IN_2_TEST_SEL_UMSK (~(((1U << PDM_ADC_IN_2_TEST_SEL_LEN) - 1) << PDM_ADC_IN_2_TEST_SEL_POS))

/* 0xC30 : pdm_dbg_3 */
#define PDM_DBG_3_OFFSET (0xC30)

/* 0xC34 : pdm_dbg_4 */
#define PDM_DBG_4_OFFSET                 (0xC34)
#define PDM_ADC_IN_RATIO_4S_VAL          PDM_ADC_IN_RATIO_4S_VAL
#define PDM_ADC_IN_RATIO_4S_VAL_POS      (0U)
#define PDM_ADC_IN_RATIO_4S_VAL_LEN      (1U)
#define PDM_ADC_IN_RATIO_4S_VAL_MSK      (((1U << PDM_ADC_IN_RATIO_4S_VAL_LEN) - 1) << PDM_ADC_IN_RATIO_4S_VAL_POS)
#define PDM_ADC_IN_RATIO_4S_VAL_UMSK     (~(((1U << PDM_ADC_IN_RATIO_4S_VAL_LEN) - 1) << PDM_ADC_IN_RATIO_4S_VAL_POS))
#define PDM_ADC_IN_CH0_RATIO_4S_VAL      PDM_ADC_IN_CH0_RATIO_4S_VAL
#define PDM_ADC_IN_CH0_RATIO_4S_VAL_POS  (1U)
#define PDM_ADC_IN_CH0_RATIO_4S_VAL_LEN  (1U)
#define PDM_ADC_IN_CH0_RATIO_4S_VAL_MSK  (((1U << PDM_ADC_IN_CH0_RATIO_4S_VAL_LEN) - 1) << PDM_ADC_IN_CH0_RATIO_4S_VAL_POS)
#define PDM_ADC_IN_CH0_RATIO_4S_VAL_UMSK (~(((1U << PDM_ADC_IN_CH0_RATIO_4S_VAL_LEN) - 1) << PDM_ADC_IN_CH0_RATIO_4S_VAL_POS))
#define PDM_ADC_IN_CH1_RATIO_4S_VAL      PDM_ADC_IN_CH1_RATIO_4S_VAL
#define PDM_ADC_IN_CH1_RATIO_4S_VAL_POS  (2U)
#define PDM_ADC_IN_CH1_RATIO_4S_VAL_LEN  (1U)
#define PDM_ADC_IN_CH1_RATIO_4S_VAL_MSK  (((1U << PDM_ADC_IN_CH1_RATIO_4S_VAL_LEN) - 1) << PDM_ADC_IN_CH1_RATIO_4S_VAL_POS)
#define PDM_ADC_IN_CH1_RATIO_4S_VAL_UMSK (~(((1U << PDM_ADC_IN_CH1_RATIO_4S_VAL_LEN) - 1) << PDM_ADC_IN_CH1_RATIO_4S_VAL_POS))
#define PDM_ADC_IN_CH2_RATIO_4S_VAL      PDM_ADC_IN_CH2_RATIO_4S_VAL
#define PDM_ADC_IN_CH2_RATIO_4S_VAL_POS  (3U)
#define PDM_ADC_IN_CH2_RATIO_4S_VAL_LEN  (1U)
#define PDM_ADC_IN_CH2_RATIO_4S_VAL_MSK  (((1U << PDM_ADC_IN_CH2_RATIO_4S_VAL_LEN) - 1) << PDM_ADC_IN_CH2_RATIO_4S_VAL_POS)
#define PDM_ADC_IN_CH2_RATIO_4S_VAL_UMSK (~(((1U << PDM_ADC_IN_CH2_RATIO_4S_VAL_LEN) - 1) << PDM_ADC_IN_CH2_RATIO_4S_VAL_POS))
#define PDM_IN_RATIO_4S_VAL              PDM_IN_RATIO_4S_VAL
#define PDM_IN_RATIO_4S_VAL_POS          (4U)
#define PDM_IN_RATIO_4S_VAL_LEN          (1U)
#define PDM_IN_RATIO_4S_VAL_MSK          (((1U << PDM_IN_RATIO_4S_VAL_LEN) - 1) << PDM_IN_RATIO_4S_VAL_POS)
#define PDM_IN_RATIO_4S_VAL_UMSK         (~(((1U << PDM_IN_RATIO_4S_VAL_LEN) - 1) << PDM_IN_RATIO_4S_VAL_POS))
#define PDM_IN_RATIO_4S                  PDM_IN_RATIO_4S
#define PDM_IN_RATIO_4S_POS              (5U)
#define PDM_IN_RATIO_4S_LEN              (1U)
#define PDM_IN_RATIO_4S_MSK              (((1U << PDM_IN_RATIO_4S_LEN) - 1) << PDM_IN_RATIO_4S_POS)
#define PDM_IN_RATIO_4S_UMSK             (~(((1U << PDM_IN_RATIO_4S_LEN) - 1) << PDM_IN_RATIO_4S_POS))

/* 0xC38 : pdm_adc_s0 */
#define PDM_ADC_S0_OFFSET      (0xC38)
#define PDM_ADC_S0_VOLUME      PDM_ADC_S0_VOLUME
#define PDM_ADC_S0_VOLUME_POS  (0U)
#define PDM_ADC_S0_VOLUME_LEN  (9U)
#define PDM_ADC_S0_VOLUME_MSK  (((1U << PDM_ADC_S0_VOLUME_LEN) - 1) << PDM_ADC_S0_VOLUME_POS)
#define PDM_ADC_S0_VOLUME_UMSK (~(((1U << PDM_ADC_S0_VOLUME_LEN) - 1) << PDM_ADC_S0_VOLUME_POS))

/* 0xC3C : pdm_adc_s1 */
#define PDM_ADC_S1_OFFSET      (0xC3C)
#define PDM_ADC_S1_VOLUME      PDM_ADC_S1_VOLUME
#define PDM_ADC_S1_VOLUME_POS  (0U)
#define PDM_ADC_S1_VOLUME_LEN  (9U)
#define PDM_ADC_S1_VOLUME_MSK  (((1U << PDM_ADC_S1_VOLUME_LEN) - 1) << PDM_ADC_S1_VOLUME_POS)
#define PDM_ADC_S1_VOLUME_UMSK (~(((1U << PDM_ADC_S1_VOLUME_LEN) - 1) << PDM_ADC_S1_VOLUME_POS))

/* 0xC40 : pdm_adc_s2 */
#define PDM_ADC_S2_OFFSET      (0xC40)
#define PDM_ADC_S2_VOLUME      PDM_ADC_S2_VOLUME
#define PDM_ADC_S2_VOLUME_POS  (0U)
#define PDM_ADC_S2_VOLUME_LEN  (9U)
#define PDM_ADC_S2_VOLUME_MSK  (((1U << PDM_ADC_S2_VOLUME_LEN) - 1) << PDM_ADC_S2_VOLUME_POS)
#define PDM_ADC_S2_VOLUME_UMSK (~(((1U << PDM_ADC_S2_VOLUME_LEN) - 1) << PDM_ADC_S2_VOLUME_POS))

/* 0xC80 : pdm_rx_fifo_ctrl */
#define PDM_RX_FIFO_CTRL_OFFSET (0xC80)
#define PDM_RX_FIFO_FLUSH       PDM_RX_FIFO_FLUSH
#define PDM_RX_FIFO_FLUSH_POS   (0U)
#define PDM_RX_FIFO_FLUSH_LEN   (1U)
#define PDM_RX_FIFO_FLUSH_MSK   (((1U << PDM_RX_FIFO_FLUSH_LEN) - 1) << PDM_RX_FIFO_FLUSH_POS)
#define PDM_RX_FIFO_FLUSH_UMSK  (~(((1U << PDM_RX_FIFO_FLUSH_LEN) - 1) << PDM_RX_FIFO_FLUSH_POS))
#define PDM_RXO_INT_EN          PDM_RXO_INT_EN
#define PDM_RXO_INT_EN_POS      (1U)
#define PDM_RXO_INT_EN_LEN      (1U)
#define PDM_RXO_INT_EN_MSK      (((1U << PDM_RXO_INT_EN_LEN) - 1) << PDM_RXO_INT_EN_POS)
#define PDM_RXO_INT_EN_UMSK     (~(((1U << PDM_RXO_INT_EN_LEN) - 1) << PDM_RXO_INT_EN_POS))
#define PDM_RXU_INT_EN          PDM_RXU_INT_EN
#define PDM_RXU_INT_EN_POS      (2U)
#define PDM_RXU_INT_EN_LEN      (1U)
#define PDM_RXU_INT_EN_MSK      (((1U << PDM_RXU_INT_EN_LEN) - 1) << PDM_RXU_INT_EN_POS)
#define PDM_RXU_INT_EN_UMSK     (~(((1U << PDM_RXU_INT_EN_LEN) - 1) << PDM_RXU_INT_EN_POS))
#define PDM_RXA_INT_EN          PDM_RXA_INT_EN
#define PDM_RXA_INT_EN_POS      (3U)
#define PDM_RXA_INT_EN_LEN      (1U)
#define PDM_RXA_INT_EN_MSK      (((1U << PDM_RXA_INT_EN_LEN) - 1) << PDM_RXA_INT_EN_POS)
#define PDM_RXA_INT_EN_UMSK     (~(((1U << PDM_RXA_INT_EN_LEN) - 1) << PDM_RXA_INT_EN_POS))
#define PDM_RX_DRQ_EN           PDM_RX_DRQ_EN
#define PDM_RX_DRQ_EN_POS       (4U)
#define PDM_RX_DRQ_EN_LEN       (1U)
#define PDM_RX_DRQ_EN_MSK       (((1U << PDM_RX_DRQ_EN_LEN) - 1) << PDM_RX_DRQ_EN_POS)
#define PDM_RX_DRQ_EN_UMSK      (~(((1U << PDM_RX_DRQ_EN_LEN) - 1) << PDM_RX_DRQ_EN_POS))
#define PDM_RX_DATA_RES         PDM_RX_DATA_RES
#define PDM_RX_DATA_RES_POS     (5U)
#define PDM_RX_DATA_RES_LEN     (1U)
#define PDM_RX_DATA_RES_MSK     (((1U << PDM_RX_DATA_RES_LEN) - 1) << PDM_RX_DATA_RES_POS)
#define PDM_RX_DATA_RES_UMSK    (~(((1U << PDM_RX_DATA_RES_LEN) - 1) << PDM_RX_DATA_RES_POS))
#define PDM_RX_CH_EN            PDM_RX_CH_EN
#define PDM_RX_CH_EN_POS        (8U)
#define PDM_RX_CH_EN_LEN        (3U)
#define PDM_RX_CH_EN_MSK        (((1U << PDM_RX_CH_EN_LEN) - 1) << PDM_RX_CH_EN_POS)
#define PDM_RX_CH_EN_UMSK       (~(((1U << PDM_RX_CH_EN_LEN) - 1) << PDM_RX_CH_EN_POS))
#define PDM_RX_DRQ_CNT          PDM_RX_DRQ_CNT
#define PDM_RX_DRQ_CNT_POS      (14U)
#define PDM_RX_DRQ_CNT_LEN      (2U)
#define PDM_RX_DRQ_CNT_MSK      (((1U << PDM_RX_DRQ_CNT_LEN) - 1) << PDM_RX_DRQ_CNT_POS)
#define PDM_RX_DRQ_CNT_UMSK     (~(((1U << PDM_RX_DRQ_CNT_LEN) - 1) << PDM_RX_DRQ_CNT_POS))
#define PDM_RX_TRG_LEVEL        PDM_RX_TRG_LEVEL
#define PDM_RX_TRG_LEVEL_POS    (16U)
#define PDM_RX_TRG_LEVEL_LEN    (6U)
#define PDM_RX_TRG_LEVEL_MSK    (((1U << PDM_RX_TRG_LEVEL_LEN) - 1) << PDM_RX_TRG_LEVEL_POS)
#define PDM_RX_TRG_LEVEL_UMSK   (~(((1U << PDM_RX_TRG_LEVEL_LEN) - 1) << PDM_RX_TRG_LEVEL_POS))
#define PDM_RX_DATA_MODE        PDM_RX_DATA_MODE
#define PDM_RX_DATA_MODE_POS    (24U)
#define PDM_RX_DATA_MODE_LEN    (2U)
#define PDM_RX_DATA_MODE_MSK    (((1U << PDM_RX_DATA_MODE_LEN) - 1) << PDM_RX_DATA_MODE_POS)
#define PDM_RX_DATA_MODE_UMSK   (~(((1U << PDM_RX_DATA_MODE_LEN) - 1) << PDM_RX_DATA_MODE_POS))

/* 0xC84 : pdm_rx_fifo_status */
#define PDM_RX_FIFO_STATUS_OFFSET (0xC84)
#define PDM_RXO_INT               PDM_RXO_INT
#define PDM_RXO_INT_POS           (1U)
#define PDM_RXO_INT_LEN           (1U)
#define PDM_RXO_INT_MSK           (((1U << PDM_RXO_INT_LEN) - 1) << PDM_RXO_INT_POS)
#define PDM_RXO_INT_UMSK          (~(((1U << PDM_RXO_INT_LEN) - 1) << PDM_RXO_INT_POS))
#define PDM_RXU_INT               PDM_RXU_INT
#define PDM_RXU_INT_POS           (2U)
#define PDM_RXU_INT_LEN           (1U)
#define PDM_RXU_INT_MSK           (((1U << PDM_RXU_INT_LEN) - 1) << PDM_RXU_INT_POS)
#define PDM_RXU_INT_UMSK          (~(((1U << PDM_RXU_INT_LEN) - 1) << PDM_RXU_INT_POS))
#define PDM_RXA_INT               PDM_RXA_INT
#define PDM_RXA_INT_POS           (4U)
#define PDM_RXA_INT_LEN           (1U)
#define PDM_RXA_INT_MSK           (((1U << PDM_RXA_INT_LEN) - 1) << PDM_RXA_INT_POS)
#define PDM_RXA_INT_UMSK          (~(((1U << PDM_RXA_INT_LEN) - 1) << PDM_RXA_INT_POS))
#define PDM_RXA_CNT               PDM_RXA_CNT
#define PDM_RXA_CNT_POS           (16U)
#define PDM_RXA_CNT_LEN           (6U)
#define PDM_RXA_CNT_MSK           (((1U << PDM_RXA_CNT_LEN) - 1) << PDM_RXA_CNT_POS)
#define PDM_RXA_CNT_UMSK          (~(((1U << PDM_RXA_CNT_LEN) - 1) << PDM_RXA_CNT_POS))
#define PDM_RXA                   PDM_RXA
#define PDM_RXA_POS               (24U)
#define PDM_RXA_LEN               (1U)
#define PDM_RXA_MSK               (((1U << PDM_RXA_LEN) - 1) << PDM_RXA_POS)
#define PDM_RXA_UMSK              (~(((1U << PDM_RXA_LEN) - 1) << PDM_RXA_POS))

/* 0xC88 : pdm_rx_fifo_data */
#define PDM_RX_FIFO_DATA_OFFSET (0xC88)
#define PDM_RX_DATA             PDM_RX_DATA
#define PDM_RX_DATA_POS         (0U)
#define PDM_RX_DATA_LEN         (32U)
#define PDM_RX_DATA_MSK         (((1U << PDM_RX_DATA_LEN) - 1) << PDM_RX_DATA_POS)
#define PDM_RX_DATA_UMSK        (~(((1U << PDM_RX_DATA_LEN) - 1) << PDM_RX_DATA_POS))

struct pdm_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[3072];

    /* 0xC00 : audpdm_top */
    union {
        struct {
            uint32_t audio_ckg_en    : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1      : 1;  /* [    1],       rsvd,        0x0 */
            uint32_t adc_itf_inv_sel : 1;  /* [    2],        r/w,        0x0 */
            uint32_t pdm_itf_inv_sel : 1;  /* [    3],        r/w,        0x0 */
            uint32_t reserved_4_27   : 24; /* [27: 4],       rsvd,        0x0 */
            uint32_t adc_rate        : 3;  /* [30:28],        r/w,        0x1 */
            uint32_t reserved_31     : 1;  /* [   31],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audpdm_top;

    /* 0xC04 : audpdm_itf */
    union {
        struct {
            uint32_t adc_0_en       : 1;  /* [    0],        r/w,        0x0 */
            uint32_t adc_1_en       : 1;  /* [    1],        r/w,        0x0 */
            uint32_t adc_2_en       : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_12  : 10; /* [12: 3],       rsvd,        0x0 */
            uint32_t aud_rx0_sel    : 3;  /* [15:13],        r/w,        0x0 */
            uint32_t aud_rx1_sel    : 3;  /* [18:16],        r/w,        0x1 */
            uint32_t aud_rx2_sel    : 3;  /* [21:19],        r/w,        0x2 */
            uint32_t reserved_22_29 : 8;  /* [29:22],       rsvd,        0x0 */
            uint32_t adc_itf_en     : 1;  /* [   30],        r/w,        0x0 */
            uint32_t reserved_31    : 1;  /* [   31],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audpdm_itf;

    /* 0xC08 : pdm_adc_0 */
    union {
        struct {
            uint32_t adc_0_fir_mode : 1;  /* [    0],        r/w,        0x0 */
            uint32_t adc_1_fir_mode : 1;  /* [    1],        r/w,        0x0 */
            uint32_t adc_2_fir_mode : 1;  /* [    2],        r/w,        0x0 */
            uint32_t adc_0_scal     : 6;  /* [ 8: 3],        r/w,       0x20 */
            uint32_t adc_1_scal     : 6;  /* [14: 9],        r/w,       0x20 */
            uint32_t adc_2_scal     : 6;  /* [20:15],        r/w,       0x20 */
            uint32_t reserved_21_31 : 11; /* [31:21],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_adc_0;

    /* 0xC0C : pdm_adc_1 */
    union {
        struct {
            uint32_t adc_0_k1       : 4; /* [ 3: 0],        r/w,        0x8 */
            uint32_t adc_0_k1_en    : 1; /* [    4],        r/w,        0x1 */
            uint32_t adc_0_k2       : 4; /* [ 8: 5],        r/w,        0xd */
            uint32_t adc_0_k2_en    : 1; /* [    9],        r/w,        0x0 */
            uint32_t adc_1_k1       : 4; /* [13:10],        r/w,        0x8 */
            uint32_t adc_1_k1_en    : 1; /* [   14],        r/w,        0x1 */
            uint32_t adc_1_k2       : 4; /* [18:15],        r/w,        0xd */
            uint32_t adc_1_k2_en    : 1; /* [   19],        r/w,        0x0 */
            uint32_t adc_2_k1       : 4; /* [23:20],        r/w,        0x8 */
            uint32_t adc_2_k1_en    : 1; /* [   24],        r/w,        0x1 */
            uint32_t adc_2_k2       : 4; /* [28:25],        r/w,        0xd */
            uint32_t adc_2_k2_en    : 1; /* [   29],        r/w,        0x0 */
            uint32_t reserved_30_31 : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_adc_1;

    /* 0xC10 : pdm_dac_0 */
    union {
        struct {
            uint32_t adc_pdm_h          : 6;  /* [ 5: 0],        r/w,        0x1 */
            uint32_t adc_pdm_l          : 6;  /* [11: 6],        r/w,       0x3f */
            uint32_t reserved_12        : 1;  /* [   12],       rsvd,        0x0 */
            uint32_t adc_0_pdm_lvl_swap : 1;  /* [   13],        r/w,        0x0 */
            uint32_t reserved_14_15     : 2;  /* [15:14],       rsvd,        0x0 */
            uint32_t adc_1_pdm_lvl_swap : 1;  /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_18     : 2;  /* [18:17],       rsvd,        0x0 */
            uint32_t adc_2_pdm_lvl_swap : 1;  /* [   19],        r/w,        0x0 */
            uint32_t reserved_20_31     : 12; /* [31:20],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_dac_0;

    /* 0xc14  reserved */
    uint8_t RESERVED0xc14[8];

    /* 0xC1C : pdm_pdm_0 */
    union {
        struct {
            uint32_t pdm_0_en       : 1;  /* [    0],        r/w,        0x0 */
            uint32_t pdm_1_en       : 1;  /* [    1],        r/w,        0x0 */
            uint32_t pdm_2_en       : 1;  /* [    2],        r/w,        0x0 */
            uint32_t adc_0_pdm_sel  : 3;  /* [ 5: 3],        r/w,        0x0 */
            uint32_t adc_1_pdm_sel  : 3;  /* [ 8: 6],        r/w,        0x1 */
            uint32_t adc_2_pdm_sel  : 3;  /* [11: 9],        r/w,        0x2 */
            uint32_t reserved_12_31 : 20; /* [31:12],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_pdm_0;

    /* 0xC20 : pdm_rsvd0 */
    union {
        struct {
            uint32_t rsvd0 : 32; /* [31: 0],        r/w,     0xffff */
        } BF;
        uint32_t WORD;
    } pdm_rsvd0;

    /* 0xC24 : pdm_dbg_0 */
    union {
        struct {
            uint32_t reserved_0_20     : 21; /* [20: 0],       rsvd,        0x0 */
            uint32_t adc_test_clkin_en : 1;  /* [   21],        r/w,        0x0 */
            uint32_t reserved_22       : 1;  /* [   22],       rsvd,        0x0 */
            uint32_t adc_test_din_en   : 1;  /* [   23],        r/w,        0x0 */
            uint32_t aud_test_read_sel : 6;  /* [29:24],        r/w,        0x0 */
            uint32_t reserved_30_31    : 2;  /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_dbg_0;

    /* 0xC28 : pdm_dbg_1 */
    union {
        struct {
            uint32_t aud_test_read : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_dbg_1;

    /* 0xC2C : pdm_dbg_2 */
    union {
        struct {
            uint32_t adc_fir_4s_val    : 20; /* [19: 0],        r/w,        0x0 */
            uint32_t adc_0_fir_4s_en   : 1;  /* [   20],        r/w,        0x0 */
            uint32_t adc_1_fir_4s_en   : 1;  /* [   21],        r/w,        0x0 */
            uint32_t adc_2_fir_4s_en   : 1;  /* [   22],        r/w,        0x0 */
            uint32_t adc_in_0_test_sel : 1;  /* [   23],        r/w,        0x0 */
            uint32_t adc_in_1_test_sel : 1;  /* [   24],        r/w,        0x0 */
            uint32_t adc_in_2_test_sel : 1;  /* [   25],        r/w,        0x0 */
            uint32_t reserved_26_31    : 6;  /* [31:26],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_dbg_2;

    /* 0xC30 : pdm_dbg_3 */
    union {
        struct {
            uint32_t reserved_0_31 : 32; /* [31: 0],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_dbg_3;

    /* 0xC34 : pdm_dbg_4 */
    union {
        struct {
            uint32_t adc_in_ratio_4s_val     : 1;  /* [    0],        r/w,        0x0 */
            uint32_t adc_in_ch0_ratio_4s_val : 1;  /* [    1],        r/w,        0x0 */
            uint32_t adc_in_ch1_ratio_4s_val : 1;  /* [    2],        r/w,        0x0 */
            uint32_t adc_in_ch2_ratio_4s_val : 1;  /* [    3],        r/w,        0x0 */
            uint32_t pdm_in_ratio_4s_val     : 1;  /* [    4],        r/w,        0x0 */
            uint32_t pdm_in_ratio_4s         : 1;  /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_31           : 26; /* [31: 6],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_dbg_4;

    /* 0xC38 : pdm_adc_s0 */
    union {
        struct {
            uint32_t adc_s0_volume : 9;  /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9_31 : 23; /* [31: 9],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_adc_s0;

    /* 0xC3C : pdm_adc_s1 */
    union {
        struct {
            uint32_t adc_s1_volume : 9;  /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9_31 : 23; /* [31: 9],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_adc_s1;

    /* 0xC40 : pdm_adc_s2 */
    union {
        struct {
            uint32_t adc_s2_volume : 9;  /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9_31 : 23; /* [31: 9],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_adc_s2;

    /* 0xc44  reserved */
    uint8_t RESERVED0xc44[60];

    /* 0xC80 : pdm_rx_fifo_ctrl */
    union {
        struct {
            uint32_t rx_fifo_flush  : 1; /* [    0],        w1c,        0x0 */
            uint32_t rxo_int_en     : 1; /* [    1],        r/w,        0x0 */
            uint32_t rxu_int_en     : 1; /* [    2],        r/w,        0x0 */
            uint32_t rxa_int_en     : 1; /* [    3],        r/w,        0x0 */
            uint32_t rx_drq_en      : 1; /* [    4],        r/w,        0x0 */
            uint32_t rx_data_res    : 1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7   : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t rx_ch_en       : 3; /* [10: 8],        r/w,        0x0 */
            uint32_t reserved_11_13 : 3; /* [13:11],       rsvd,        0x0 */
            uint32_t rx_drq_cnt     : 2; /* [15:14],        r/w,        0x0 */
            uint32_t rx_trg_level   : 6; /* [21:16],        r/w,       0x17 */
            uint32_t reserved_22_23 : 2; /* [23:22],       rsvd,        0x0 */
            uint32_t rx_data_mode   : 2; /* [25:24],        r/w,        0x0 */
            uint32_t reserved_26_31 : 6; /* [31:26],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_rx_fifo_ctrl;

    /* 0xC84 : pdm_rx_fifo_status */
    union {
        struct {
            uint32_t reserved_0     : 1;  /* [    0],       rsvd,        0x0 */
            uint32_t rxo_int        : 1;  /* [    1],          r,        0x0 */
            uint32_t rxu_int        : 1;  /* [    2],          r,        0x0 */
            uint32_t reserved_3     : 1;  /* [    3],       rsvd,        0x0 */
            uint32_t rxa_int        : 1;  /* [    4],          r,        0x0 */
            uint32_t reserved_5_15  : 11; /* [15: 5],       rsvd,        0x0 */
            uint32_t rxa_cnt        : 6;  /* [21:16],          r,        0x0 */
            uint32_t reserved_22_23 : 2;  /* [23:22],       rsvd,        0x0 */
            uint32_t rxa            : 1;  /* [   24],          r,        0x0 */
            uint32_t reserved_25_31 : 7;  /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_rx_fifo_status;

    /* 0xC88 : pdm_rx_fifo_data */
    union {
        struct {
            uint32_t rx_data : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } pdm_rx_fifo_data;
};

typedef volatile struct pdm_reg pdm_reg_t;

#endif /* __PDM_REG_H__ */
