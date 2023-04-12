/**
  ******************************************************************************
  * @file    auadc_reg.h
  * @version V1.0
  * @date    2022-12-03
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
#ifndef __AUADC_REG_H__
#define __AUADC_REG_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define AUADC_AUDPDM_TOP_OFFSET            (0x00) /* audpdm_top */
#define AUADC_AUDPDM_ITF_OFFSET            (0x04) /* audpdm_itf */
#define AUADC_PDM_ADC_0_OFFSET             (0x08) /* pdm_adc_0 */
#define AUADC_PDM_ADC_1_OFFSET             (0x0C) /* pdm_adc_1 */
#define AUADC_PDM_DAC_0_OFFSET             (0x10) /* pdm_dac_0 */
#define AUADC_PDM_PDM_0_OFFSET             (0x1C) /* pdm_pdm_0 */
#define AUADC_PDM_ADC_S0_OFFSET            (0x38) /* pdm_adc_s0 */
#define AUADC_AUDADC_ANA_CFG1_OFFSET       (0x60) /* audadc_ana_cfg1 */
#define AUADC_AUDADC_ANA_CFG2_OFFSET       (0x64) /* audadc_ana_cfg2 */
#define AUADC_AUDADC_CMD_OFFSET            (0x68) /* audadc_cmd */
#define AUADC_AUDADC_DATA_OFFSET           (0x6C) /* audadc_data */
#define AUADC_AUDADC_RX_FIFO_CTRL_OFFSET   (0x80) /* audadc_rx_fifo_ctrl */
#define AUADC_AUDADC_RX_FIFO_STATUS_OFFSET (0x84) /* audadc_rx_fifo_status */
#define AUADC_AUDADC_RX_FIFO_DATA_OFFSET   (0x88) /* audadc_rx_fifo_data */

/* Register Bitfield definitions *****************************************************/

/* 0xC00 : audpdm_top */
#define AUADC_AUDIO_CKG_EN                 (1 << 0U)
#define AUADC_ADC_ITF_INV_SEL              (1 << 2U)
#define AUADC_PDM_ITF_INV_SEL              (1 << 3U)
#define AUADC_ADC_RATE_SHIFT               (28U)
#define AUADC_ADC_RATE_MASK                (0xf << AUADC_ADC_RATE_SHIFT)

/* 0xC04 : audpdm_itf */
#define AUADC_ADC_0_EN                     (1 << 0U)
#define AUADC_ADC_ITF_EN                   (1 << 30U)

/* 0xC08 : pdm_adc_0 */
#define AUADC_ADC_0_FIR_MODE               (1 << 0U)

/* 0xC0C : pdm_adc_1 */
#define AUADC_ADC_0_K1_SHIFT               (0U)
#define AUADC_ADC_0_K1_MASK                (0xf << AUADC_ADC_0_K1_SHIFT)
#define AUADC_ADC_0_K1_EN                  (1 << 4U)
#define AUADC_ADC_0_K2_SHIFT               (5U)
#define AUADC_ADC_0_K2_MASK                (0xf << AUADC_ADC_0_K2_SHIFT)
#define AUADC_ADC_0_K2_EN                  (1 << 9U)

/* 0xC10 : pdm_dac_0 */
#define AUADC_ADC_PDM_H_SHIFT              (0U)
#define AUADC_ADC_PDM_H_MASK               (0xf << AUADC_ADC_PDM_H_SHIFT)
#define AUADC_ADC_PDM_L_SHIFT              (6U)
#define AUADC_ADC_PDM_L_MASK               (0xf << AUADC_ADC_PDM_L_SHIFT)
#define AUADC_ADC_0_SRC                    (1 << 12U)

/* 0xC1C : pdm_pdm_0 */
#define AUADC_PDM_0_EN                     (1 << 0U)
#define AUADC_ADC_0_PDM_SEL_SHIFT          (3U)
#define AUADC_ADC_0_PDM_SEL_MASK           (0x7 << AUADC_ADC_0_PDM_SEL_SHIFT)

/* 0xC38 : pdm_adc_s0 */
#define AUADC_ADC_S0_VOLUME_SHIFT          (0U)
#define AUADC_ADC_S0_VOLUME_MASK           (0x1ff << AUADC_ADC_S0_VOLUME_SHIFT)

/* 0xC60 : audadc_ana_cfg1 */
#define AUADC_AUDADC_PGA_CHOP_CKSEL        (1 << 0U)
#define AUADC_AUDADC_PGA_CHOP_FREQ_SHIFT   (1U)
#define AUADC_AUDADC_PGA_CHOP_FREQ_MASK    (0x7 << AUADC_AUDADC_PGA_CHOP_FREQ_SHIFT)
#define AUADC_AUDADC_PGA_CHOP_EN           (1 << 4U)
#define AUADC_AUDADC_PGA_CHOP_CFG_SHIFT    (5U)
#define AUADC_AUDADC_PGA_CHOP_CFG_MASK     (0x3 << AUADC_AUDADC_PGA_CHOP_CFG_SHIFT)
#define AUADC_AUDADC_PGA_RHPAS_SEL_SHIFT   (8U)
#define AUADC_AUDADC_PGA_RHPAS_SEL_MASK    (0x3 << AUADC_AUDADC_PGA_RHPAS_SEL_SHIFT)
#define AUADC_AUDADC_PGA_NOIS_CTRL_SHIFT   (12U)
#define AUADC_AUDADC_PGA_NOIS_CTRL_MASK    (0x3 << AUADC_AUDADC_PGA_NOIS_CTRL_SHIFT)
#define AUADC_AUDADC_ICTRL_PGA_AAF_SHIFT   (16U)
#define AUADC_AUDADC_ICTRL_PGA_AAF_MASK    (0x3 << AUADC_AUDADC_ICTRL_PGA_AAF_SHIFT)
#define AUADC_AUDADC_ICTRL_PGA_MIC_SHIFT   (20U)
#define AUADC_AUDADC_ICTRL_PGA_MIC_MASK    (0x3 << AUADC_AUDADC_ICTRL_PGA_MIC_SHIFT)
#define AUADC_AUDADC_PGA_LP_EN             (1 << 24U)
#define AUADC_AUDADC_CKB_EN                (1 << 28U)
#define AUADC_AUDADC_SEL_EDGE              (1 << 29U)

/* 0xC64 : audadc_ana_cfg2 */
#define AUADC_AUDADC_DITHER_ORDER          (1 << 0U)
#define AUADC_AUDADC_DITHER_SEL_SHIFT      (1U)
#define AUADC_AUDADC_DITHER_SEL_MASK       (0x3 << AUADC_AUDADC_DITHER_SEL_SHIFT)
#define AUADC_AUDADC_DITHER_ENA            (1 << 3U)
#define AUADC_AUDADC_QUAN_GAIN_SHIFT       (4U)
#define AUADC_AUDADC_QUAN_GAIN_MASK        (0x3 << AUADC_AUDADC_QUAN_GAIN_SHIFT)
#define AUADC_AUDADC_DEM_EN                (1 << 8U)
#define AUADC_AUDADC_NCTRL_ADC2_SHIFT      (12U)
#define AUADC_AUDADC_NCTRL_ADC2_MASK       (0x3 << AUADC_AUDADC_NCTRL_ADC2_SHIFT)
#define AUADC_AUDADC_NCTRL_ADC1_SHIFT      (16U)
#define AUADC_AUDADC_NCTRL_ADC1_MASK       (0x7 << AUADC_AUDADC_NCTRL_ADC1_SHIFT)
#define AUADC_AUDADC_ICTRL_ADC_SHIFT       (20U)
#define AUADC_AUDADC_ICTRL_ADC_MASK        (0x3 << AUADC_AUDADC_ICTRL_ADC_SHIFT)
#define AUADC_AUDADC_SDM_LP_EN             (1 << 24U)
#define AUADC_AUDADC_RESERVED_SHIFT        (28U)
#define AUADC_AUDADC_RESERVED_MASK         (0x3 << AUADC_AUDADC_RESERVED_SHIFT)

/* 0xC68 : audadc_cmd */
#define AUADC_AUDADC_MEAS_ODR_SEL_SHIFT    (0U)
#define AUADC_AUDADC_MEAS_ODR_SEL_MASK     (0xf << AUADC_AUDADC_MEAS_ODR_SEL_SHIFT)
#define AUADC_AUDADC_MEAS_FILTER_TYPE      (1 << 4U)
#define AUADC_AUDADC_MEAS_FILTER_EN        (1 << 5U)
#define AUADC_AUDADC_AUDIO_OSR_SEL         (1 << 6U)
#define AUADC_AUDADC_PGA_GAIN_SHIFT        (8U)
#define AUADC_AUDADC_PGA_GAIN_MASK         (0xf << AUADC_AUDADC_PGA_GAIN_SHIFT)
#define AUADC_AUDADC_PGA_MODE_SHIFT        (12U)
#define AUADC_AUDADC_PGA_MODE_MASK         (0x3 << AUADC_AUDADC_PGA_MODE_SHIFT)
#define AUADC_AUDADC_CHANNEL_SELN_SHIFT    (16U)
#define AUADC_AUDADC_CHANNEL_SELN_MASK     (0x7 << AUADC_AUDADC_CHANNEL_SELN_SHIFT)
#define AUADC_AUDADC_CHANNEL_SELP_SHIFT    (20U)
#define AUADC_AUDADC_CHANNEL_SELP_MASK     (0x7 << AUADC_AUDADC_CHANNEL_SELP_SHIFT)
#define AUADC_AUDADC_CHANNEL_EN_SHIFT      (24U)
#define AUADC_AUDADC_CHANNEL_EN_MASK       (0x3 << AUADC_AUDADC_CHANNEL_EN_SHIFT)
#define AUADC_AUDADC_CONV                  (1 << 28U)
#define AUADC_AUDADC_SDM_PU                (1 << 29U)
#define AUADC_AUDADC_PGA_PU                (1 << 30U)

/* 0xC6C : audadc_data */
#define AUADC_AUDADC_RAW_DATA_SHIFT        (0U)
#define AUADC_AUDADC_RAW_DATA_MASK         (0xffffff << AUADC_AUDADC_RAW_DATA_SHIFT)
#define AUADC_AUDADC_DATA_RDY              (1 << 24U)
#define AUADC_AUDADC_SOFT_RST              (1 << 29U)
#define AUADC_AUDADC_VALID_4S_VAL          (1 << 30U)
#define AUADC_AUDADC_VALID_4S_EN           (1 << 31U)

/* 0xC80 : audadc_rx_fifo_ctrl */
#define AUADC_RX_FIFO_FLUSH                (1 << 0U)
#define AUADC_RXO_INT_EN                   (1 << 1U)
#define AUADC_RXU_INT_EN                   (1 << 2U)
#define AUADC_RXA_INT_EN                   (1 << 3U)
#define AUADC_RX_DRQ_EN                    (1 << 4U)
#define AUADC_RX_DATA_RES_SHIFT            (5U)
#define AUADC_RX_DATA_RES_MASK             (0x3 << AUADC_RX_DATA_RES_SHIFT)
#define AUADC_RX_CH_EN                     (1 << 8U)
#define AUADC_RX_DRQ_CNT_SHIFT             (14U)
#define AUADC_RX_DRQ_CNT_MASK              (0x3 << AUADC_RX_DRQ_CNT_SHIFT)
#define AUADC_RX_TRG_LEVEL_SHIFT           (16U)
#define AUADC_RX_TRG_LEVEL_MASK            (0xf << AUADC_RX_TRG_LEVEL_SHIFT)
#define AUADC_RX_DATA_MODE_SHIFT           (24U)
#define AUADC_RX_DATA_MODE_MASK            (0x3 << AUADC_RX_DATA_MODE_SHIFT)

/* 0xC84 : audadc_rx_fifo_status */
#define AUADC_RXO_INT                      (1 << 1U)
#define AUADC_RXU_INT                      (1 << 2U)
#define AUADC_RXA_INT                      (1 << 4U)
#define AUADC_RXA_CNT_SHIFT                (16U)
#define AUADC_RXA_CNT_MASK                 (0xf << AUADC_RXA_CNT_SHIFT)
#define AUADC_RXA                          (1 << 24U)

/* 0xC88 : audadc_rx_fifo_data */
#define AUADC_RX_DATA_SHIFT                (0U)
#define AUADC_RX_DATA_MASK                 (0xffffffff << AUADC_RX_DATA_SHIFT)

#endif /* __AUADC_REG_H__ */
