/**
  ******************************************************************************
  * @file    adc_reg.h
  * @version V1.0
  * @date    2022-08-05
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
#ifndef __HARDWARE_ADC_H__
#define __HARDWARE_ADC_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

/* gpip base */
#define GPIP_GPADC_CONFIG_OFFSET    (0x0) /* gpadc_config */
#define GPIP_GPADC_DMA_RDATA_OFFSET (0x4) /* gpadc_dma_rdata */
#if defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
#define GPIP_GPADC_PIR_TRAIN_OFFSET (0x20) /* gpadc_pir_train */
#endif
/* aon base */
#define AON_GPADC_REG_CMD_OFFSET        (0x90C) /* gpadc_reg_cmd */
#define AON_GPADC_REG_CONFIG1_OFFSET    (0x910) /* gpadc_reg_config1 */
#define AON_GPADC_REG_CONFIG2_OFFSET    (0x914) /* gpadc_reg_config2 */
#define AON_GPADC_REG_SCN_POS1_OFFSET   (0x918) /* adc converation sequence 1 */
#define AON_GPADC_REG_SCN_POS2_OFFSET   (0x91C) /* adc converation sequence 2 */
#define AON_GPADC_REG_SCN_NEG1_OFFSET   (0x920) /* adc converation sequence 3 */
#define AON_GPADC_REG_SCN_NEG2_OFFSET   (0x924) /* adc converation sequence 4 */
#define AON_GPADC_REG_STATUS_OFFSET     (0x928) /* gpadc_reg_status */
#define AON_GPADC_REG_ISR_OFFSET        (0x92C) /* gpadc_reg_isr */
#define AON_GPADC_REG_RESULT_OFFSET     (0x930) /* gpadc_reg_result */
#define AON_GPADC_REG_RAW_RESULT_OFFSET (0x934) /* gpadc_reg_raw_result */
#define AON_GPADC_REG_DEFINE_OFFSET     (0x938) /* gpadc_reg_define */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : gpadc_config */
#define GPIP_GPADC_DMA_EN        (1 << 0U)
#define GPIP_GPADC_FIFO_CLR      (1 << 1U)
#define GPIP_GPADC_FIFO_NE       (1 << 2U)
#define GPIP_GPADC_FIFO_FULL     (1 << 3U)
#define GPIP_GPADC_RDY           (1 << 4U)
#define GPIP_GPADC_FIFO_OVERRUN  (1 << 5U)
#define GPIP_GPADC_FIFO_UNDERRUN (1 << 6U)
#if defined(BL702) || defined(BL702L)
#define GPIP_GPADC_FIFO_RDY (1 << 7U)
#endif
#define GPIP_GPADC_RDY_CLR            (1 << 8U)
#define GPIP_GPADC_FIFO_OVERRUN_CLR   (1 << 9U)
#define GPIP_GPADC_FIFO_UNDERRUN_CLR  (1 << 10U)
#define GPIP_GPADC_RDY_MASK           (1 << 12U)
#define GPIP_GPADC_FIFO_OVERRUN_MASK  (1 << 13U)
#define GPIP_GPADC_FIFO_UNDERRUN_MASK (1 << 14U)
#if defined(BL702) || defined(BL702L)
#define GPIP_GPADC_FIFO_RDY_MASK (1 << 15U)
#endif
#define GPIP_GPADC_FIFO_DATA_COUNT_SHIFT (16U)
#define GPIP_GPADC_FIFO_DATA_COUNT_MASK  (0x3f << GPIP_GPADC_FIFO_DATA_COUNT_SHIFT)
#define GPIP_GPADC_FIFO_THL_SHIFT        (22U)
#define GPIP_GPADC_FIFO_THL_MASK         (0x3 << GPIP_GPADC_FIFO_THL_SHIFT)

/* 0x4 : gpadc_dma_rdata */
#define GPIP_GPADC_DMA_RDATA_SHIFT (0U)
#define GPIP_GPADC_DMA_RDATA_MASK  (0x3ffffff << GPIP_GPADC_DMA_RDATA_SHIFT)

/* 0x20 : gpadc_pir_train */
#define GPIP_PIR_EXTEND_SHIFT (0U)
#define GPIP_PIR_EXTEND_MASK  (0x1f << GPIP_PIR_EXTEND_SHIFT)
#define GPIP_PIR_CNT_V_SHIFT  (8U)
#define GPIP_PIR_CNT_V_MASK   (0x1f << GPIP_PIR_CNT_V_SHIFT)
#define GPIP_PIR_TRAIN        (1 << 16U)
#define GPIP_PIR_STOP         (1 << 17U)

/* 0x90C : gpadc_reg_cmd */
#define AON_GPADC_GLOBAL_EN     (1 << 0U)
#define AON_GPADC_CONV_START    (1 << 1U)
#define AON_GPADC_SOFT_RST      (1 << 2U)
#define AON_GPADC_NEG_SEL_SHIFT (3U)
#define AON_GPADC_NEG_SEL_MASK  (0x1f << AON_GPADC_NEG_SEL_SHIFT)
#define AON_GPADC_POS_SEL_SHIFT (8U)
#define AON_GPADC_POS_SEL_MASK  (0x1f << AON_GPADC_POS_SEL_SHIFT)
#define AON_GPADC_NEG_GND       (1 << 13U)
#define AON_GPADC_MICBIAS_EN    (1 << 14U)
#define AON_GPADC_MICPGA_EN     (1 << 15U)
#define AON_GPADC_BYP_MICBOOST  (1 << 16U)
#if defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
#define AON_GPADC_RCAL_EN (1 << 17U)
#endif
#define AON_GPADC_DWA_EN              (1 << 18U)
#define AON_GPADC_MIC2_DIFF           (1 << 19U)
#define AON_GPADC_MIC1_DIFF           (1 << 20U)
#define AON_GPADC_MIC_PGA2_GAIN_SHIFT (21U)
#define AON_GPADC_MIC_PGA2_GAIN_MASK  (0x3 << AON_GPADC_MIC_PGA2_GAIN_SHIFT)
#define AON_GPADC_MICBOOST_32DB_EN    (1 << 23U)
#define AON_GPADC_CHIP_SEN_PU         (1 << 27U)
#define AON_GPADC_SEN_SEL_SHIFT       (28U)
#if defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
#define AON_GPADC_SEN_SEL_MASK (0x7 << AON_GPADC_SEN_SEL_SHIFT)
#define AON_GPADC_SEN_TEST_EN  (1 << 31U)
#elif defined(BL702) || defined(BL602) || defined(BL702L)
#define AON_GPADC_SEN_SEL_MASK (0x3 << AON_GPADC_SEN_SEL_SHIFT)
#define AON_GPADC_SEN_TEST_EN  (1 << 30U)
#endif

/* 0x910 : gpadc_reg_config1 */
#define AON_GPADC_CAL_OS_EN     (1 << 0U)
#define AON_GPADC_CONT_CONV_EN  (1 << 1U)
#define AON_GPADC_RES_SEL_SHIFT (2U)
#define AON_GPADC_RES_SEL_MASK  (0x7 << AON_GPADC_RES_SEL_SHIFT)
#define AON_GPADC_VCM_SEL_EN    (1 << 8U)
#define AON_GPADC_VCM_HYST_SEL  (1 << 9U)
#define AON_GPADC_LOWV_DET_EN   (1 << 10U)
#if defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
#define AON_GPADC_PWM_TRG_EN        (1 << 11U)
#define AON_GPADC_CLK_ANA_DLY_SHIFT (12U)
#define AON_GPADC_CLK_ANA_DLY_MASK  (0xf << AON_GPADC_CLK_ANA_DLY_SHIFT)
#define AON_GPADC_CLK_ANA_DLY_EN    (1 << 16U)
#endif
#define AON_GPADC_CLK_ANA_INV         (1 << 17U)
#define AON_GPADC_CLK_DIV_RATIO_SHIFT (18U)
#define AON_GPADC_CLK_DIV_RATIO_MASK  (0x7 << AON_GPADC_CLK_DIV_RATIO_SHIFT)
#define AON_GPADC_SCAN_LENGTH_SHIFT   (21U)
#define AON_GPADC_SCAN_LENGTH_MASK    (0xf << AON_GPADC_SCAN_LENGTH_SHIFT)
#define AON_GPADC_SCAN_EN             (1 << 25U)
#define AON_GPADC_DITHER_EN           (1 << 26U)
#define AON_GPADC_V11_SEL_SHIFT       (27U)
#define AON_GPADC_V11_SEL_MASK        (0x3 << AON_GPADC_V11_SEL_SHIFT)
#define AON_GPADC_V18_SEL_SHIFT       (29U)
#define AON_GPADC_V18_SEL_MASK        (0x3 << AON_GPADC_V18_SEL_SHIFT)

/* 0x914 : gpadc_reg_config2 */
#define AON_GPADC_DIFF_MODE        (1 << 2U)
#define AON_GPADC_VREF_SEL         (1 << 3U)
#define AON_GPADC_VBAT_EN          (1 << 4U)
#define AON_GPADC_TSEXT_SEL        (1 << 5U)
#define AON_GPADC_TS_EN            (1 << 6U)
#define AON_GPADC_PGA_VCM_SHIFT    (7U)
#define AON_GPADC_PGA_VCM_MASK     (0x3 << AON_GPADC_PGA_VCM_SHIFT)
#define AON_GPADC_PGA_OS_CAL_SHIFT (9U)
#define AON_GPADC_PGA_OS_CAL_MASK  (0xf << AON_GPADC_PGA_OS_CAL_SHIFT)
#define AON_GPADC_PGA_EN           (1 << 13U)
#define AON_GPADC_PGA_VCMI_EN      (1 << 14U)
#define AON_GPADC_CHOP_MODE_SHIFT  (15U)
#define AON_GPADC_CHOP_MODE_MASK   (0x3 << AON_GPADC_CHOP_MODE_SHIFT)
#define AON_GPADC_BIAS_SEL         (1 << 17U)
#define AON_GPADC_TEST_EN          (1 << 18U)
#define AON_GPADC_TEST_SEL_SHIFT   (19U)
#define AON_GPADC_TEST_SEL_MASK    (0x7 << AON_GPADC_TEST_SEL_SHIFT)
#define AON_GPADC_PGA2_GAIN_SHIFT  (22U)
#define AON_GPADC_PGA2_GAIN_MASK   (0x7 << AON_GPADC_PGA2_GAIN_SHIFT)
#define AON_GPADC_PGA1_GAIN_SHIFT  (25U)
#define AON_GPADC_PGA1_GAIN_MASK   (0x7 << AON_GPADC_PGA1_GAIN_SHIFT)
#define AON_GPADC_DLY_SEL_SHIFT    (28U)
#define AON_GPADC_DLY_SEL_MASK     (0x7 << AON_GPADC_DLY_SEL_SHIFT)
#define AON_GPADC_TSVBE_LOW        (1 << 31U)

/* 0x918 : adc converation sequence 1 */
#define AON_GPADC_SCAN_POS_0_SHIFT (0U)
#define AON_GPADC_SCAN_POS_0_MASK  (0x1f << AON_GPADC_SCAN_POS_0_SHIFT)
#define AON_GPADC_SCAN_POS_1_SHIFT (5U)
#define AON_GPADC_SCAN_POS_1_MASK  (0x1f << AON_GPADC_SCAN_POS_1_SHIFT)
#define AON_GPADC_SCAN_POS_2_SHIFT (10U)
#define AON_GPADC_SCAN_POS_2_MASK  (0x1f << AON_GPADC_SCAN_POS_2_SHIFT)
#define AON_GPADC_SCAN_POS_3_SHIFT (15U)
#define AON_GPADC_SCAN_POS_3_MASK  (0x1f << AON_GPADC_SCAN_POS_3_SHIFT)
#define AON_GPADC_SCAN_POS_4_SHIFT (20U)
#define AON_GPADC_SCAN_POS_4_MASK  (0x1f << AON_GPADC_SCAN_POS_4_SHIFT)
#define AON_GPADC_SCAN_POS_5_SHIFT (25U)
#define AON_GPADC_SCAN_POS_5_MASK  (0x1f << AON_GPADC_SCAN_POS_5_SHIFT)

/* 0x91C : adc converation sequence 2 */
#define AON_GPADC_SCAN_POS_6_SHIFT  (0U)
#define AON_GPADC_SCAN_POS_6_MASK   (0x1f << AON_GPADC_SCAN_POS_6_SHIFT)
#define AON_GPADC_SCAN_POS_7_SHIFT  (5U)
#define AON_GPADC_SCAN_POS_7_MASK   (0x1f << AON_GPADC_SCAN_POS_7_SHIFT)
#define AON_GPADC_SCAN_POS_8_SHIFT  (10U)
#define AON_GPADC_SCAN_POS_8_MASK   (0x1f << AON_GPADC_SCAN_POS_8_SHIFT)
#define AON_GPADC_SCAN_POS_9_SHIFT  (15U)
#define AON_GPADC_SCAN_POS_9_MASK   (0x1f << AON_GPADC_SCAN_POS_9_SHIFT)
#define AON_GPADC_SCAN_POS_10_SHIFT (20U)
#define AON_GPADC_SCAN_POS_10_MASK  (0x1f << AON_GPADC_SCAN_POS_10_SHIFT)
#define AON_GPADC_SCAN_POS_11_SHIFT (25U)
#define AON_GPADC_SCAN_POS_11_MASK  (0x1f << AON_GPADC_SCAN_POS_11_SHIFT)

/* 0x920 : adc converation sequence 3 */
#define AON_GPADC_SCAN_NEG_0_SHIFT (0U)
#define AON_GPADC_SCAN_NEG_0_MASK  (0x1f << AON_GPADC_SCAN_NEG_0_SHIFT)
#define AON_GPADC_SCAN_NEG_1_SHIFT (5U)
#define AON_GPADC_SCAN_NEG_1_MASK  (0x1f << AON_GPADC_SCAN_NEG_1_SHIFT)
#define AON_GPADC_SCAN_NEG_2_SHIFT (10U)
#define AON_GPADC_SCAN_NEG_2_MASK  (0x1f << AON_GPADC_SCAN_NEG_2_SHIFT)
#define AON_GPADC_SCAN_NEG_3_SHIFT (15U)
#define AON_GPADC_SCAN_NEG_3_MASK  (0x1f << AON_GPADC_SCAN_NEG_3_SHIFT)
#define AON_GPADC_SCAN_NEG_4_SHIFT (20U)
#define AON_GPADC_SCAN_NEG_4_MASK  (0x1f << AON_GPADC_SCAN_NEG_4_SHIFT)
#define AON_GPADC_SCAN_NEG_5_SHIFT (25U)
#define AON_GPADC_SCAN_NEG_5_MASK  (0x1f << AON_GPADC_SCAN_NEG_5_SHIFT)

/* 0x924 : adc converation sequence 4 */
#define AON_GPADC_SCAN_NEG_6_SHIFT  (0U)
#define AON_GPADC_SCAN_NEG_6_MASK   (0x1f << AON_GPADC_SCAN_NEG_6_SHIFT)
#define AON_GPADC_SCAN_NEG_7_SHIFT  (5U)
#define AON_GPADC_SCAN_NEG_7_MASK   (0x1f << AON_GPADC_SCAN_NEG_7_SHIFT)
#define AON_GPADC_SCAN_NEG_8_SHIFT  (10U)
#define AON_GPADC_SCAN_NEG_8_MASK   (0x1f << AON_GPADC_SCAN_NEG_8_SHIFT)
#define AON_GPADC_SCAN_NEG_9_SHIFT  (15U)
#define AON_GPADC_SCAN_NEG_9_MASK   (0x1f << AON_GPADC_SCAN_NEG_9_SHIFT)
#define AON_GPADC_SCAN_NEG_10_SHIFT (20U)
#define AON_GPADC_SCAN_NEG_10_MASK  (0x1f << AON_GPADC_SCAN_NEG_10_SHIFT)
#define AON_GPADC_SCAN_NEG_11_SHIFT (25U)
#define AON_GPADC_SCAN_NEG_11_MASK  (0x1f << AON_GPADC_SCAN_NEG_11_SHIFT)

/* 0x928 : gpadc_reg_status */
#define AON_GPADC_DATA_RDY       (1 << 0U)
#define AON_GPADC_RESERVED_SHIFT (16U)
#define AON_GPADC_RESERVED_MASK  (0xffff << AON_GPADC_RESERVED_SHIFT)

/* 0x92C : gpadc_reg_isr */
#define AON_GPADC_NEG_SATUR      (1 << 0U)
#define AON_GPADC_POS_SATUR      (1 << 1U)
#define AON_GPADC_NEG_SATUR_CLR  (1 << 4U)
#define AON_GPADC_POS_SATUR_CLR  (1 << 5U)
#define AON_GPADC_NEG_SATUR_MASK (1 << 8U)
#define AON_GPADC_POS_SATUR_MASK (1 << 9U)

/* 0x930 : gpadc_reg_result */
#define AON_GPADC_DATA_OUT_SHIFT (0U)
#define AON_GPADC_DATA_OUT_MASK  (0x3ffffff << AON_GPADC_DATA_OUT_SHIFT)

/* 0x934 : gpadc_reg_raw_result */
#define AON_GPADC_RAW_DATA_SHIFT (0U)
#define AON_GPADC_RAW_DATA_MASK  (0xfff << AON_GPADC_RAW_DATA_SHIFT)

/* 0x938 : gpadc_reg_define */
#define AON_GPADC_OS_CAL_DATA_SHIFT (0U)
#define AON_GPADC_OS_CAL_DATA_MASK  (0xffff << AON_GPADC_OS_CAL_DATA_SHIFT)

#endif /* __HARDWARE_ADC_H__ */
