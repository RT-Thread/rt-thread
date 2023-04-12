/**
  ******************************************************************************
  * @file    audac_reg.h
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
#ifndef __AUDAC_REG_H__
#define __AUDAC_REG_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define AUDAC_0_OFFSET           (0x000) /* audac_0 */
#define AUDAC_STATUS_OFFSET      (0x4)   /* audac_status */
#define AUDAC_S0_OFFSET          (0x8)   /* audac_s0 */
#define AUDAC_S0_MISC_OFFSET     (0xC)   /* audac_s0_misc */
#define AUDAC_ZD_0_OFFSET        (0x10)  /* audac_zd_0 */
#define AUDAC_1_OFFSET           (0x14)  /* audac_1 */
#define AUDAC_RSVD_OFFSET        (0x18)  /* audac_rsvd */
#define AUDAC_TEST_0_OFFSET      (0x1C)  /* audac_test_0 */
#define AUDAC_TEST_1_OFFSET      (0x20)  /* audac_test_1 */
#define AUDAC_TEST_2_OFFSET      (0x24)  /* audac_test_2 */
#define AUDAC_TEST_3_OFFSET      (0x28)  /* audac_test_3 */
#define AUDAC_FIFO_CTRL_OFFSET   (0x8C)  /* audac_fifo_ctrl */
#define AUDAC_FIFO_STATUS_OFFSET (0x90)  /* audac_fifo_status */
#define AUDAC_FIFO_DATA_OFFSET   (0x94)  /* audac_fifo_data */

/* Register Bitfield definitions *****************************************************/

/* 0x000 : audac_0 */
#define AUDAC_DAC_0_EN          (1 << 0U)
#define AUDAC_DAC_ITF_EN        (1 << 1U)
#define AUDAC_CKG_ENA           (1 << 27U)
#define AUDAC_AU_PWM_MODE_SHIFT (28U)
#define AUDAC_AU_PWM_MODE_MASK  (0xf << AUDAC_AU_PWM_MODE_SHIFT)

/* 0x4 : audac_status */
#define AUDAC_DAC_H0_BUSY      (1 << 12U)
#define AUDAC_DAC_H0_MUTE_DONE (1 << 13U)
#define AUDAC_DAC_S0_INT       (1 << 16U)
#define AUDAC_DAC_S0_INT_CLR   (1 << 17U)
#define AUDAC_ZD_AMUTE         (1 << 23U)
#define AUDAC_AUDIO_INT_ALL    (1 << 24U)

/* 0x8 : audac_s0 */
#define AUDAC_DAC_S0_CTRL_RMP_RATE_SHIFT   (2U)
#define AUDAC_DAC_S0_CTRL_RMP_RATE_MASK    (0xf << AUDAC_DAC_S0_CTRL_RMP_RATE_SHIFT)
#define AUDAC_DAC_S0_CTRL_ZCD_RATE_SHIFT   (6U)
#define AUDAC_DAC_S0_CTRL_ZCD_RATE_MASK    (0xf << AUDAC_DAC_S0_CTRL_ZCD_RATE_SHIFT)
#define AUDAC_DAC_S0_CTRL_MODE_SHIFT       (10U)
#define AUDAC_DAC_S0_CTRL_MODE_MASK        (0x3 << AUDAC_DAC_S0_CTRL_MODE_SHIFT)
#define AUDAC_DAC_S0_VOLUME_UPDATE         (1 << 12U)
#define AUDAC_DAC_S0_VOLUME_SHIFT          (13U)
#define AUDAC_DAC_S0_VOLUME_MASK           (0x1ff << AUDAC_DAC_S0_VOLUME_SHIFT)
#define AUDAC_DAC_S0_MUTE_RMPUP_RATE_SHIFT (22U)
#define AUDAC_DAC_S0_MUTE_RMPUP_RATE_MASK  (0xf << AUDAC_DAC_S0_MUTE_RMPUP_RATE_SHIFT)
#define AUDAC_DAC_S0_MUTE_RMPDN_RATE_SHIFT (26U)
#define AUDAC_DAC_S0_MUTE_RMPDN_RATE_MASK  (0xf << AUDAC_DAC_S0_MUTE_RMPDN_RATE_SHIFT)
#define AUDAC_DAC_S0_MUTE_SOFTMODE         (1 << 30U)
#define AUDAC_DAC_S0_MUTE                  (1 << 31U)

/* 0xC : audac_s0_misc */
#define AUDAC_DAC_S0_CTRL_ZCD_TIMEOUT_SHIFT (28U)
#define AUDAC_DAC_S0_CTRL_ZCD_TIMEOUT_MASK  (0xf << AUDAC_DAC_S0_CTRL_ZCD_TIMEOUT_SHIFT)

/* 0x10 : audac_zd_0 */
#define AUDAC_ZD_TIME_SHIFT (0U)
#define AUDAC_ZD_TIME_MASK  (0x7fff << AUDAC_ZD_TIME_SHIFT)
#define AUDAC_ZD_EN         (1 << 16U)

/* 0x14 : audac_1 */
#define AUDAC_DAC_MIX_SEL_SHIFT              (0U)
#define AUDAC_DAC_MIX_SEL_MASK               (0x3 << AUDAC_DAC_MIX_SEL_SHIFT)
#define AUDAC_DAC_DSM_OUT_FMT                (1 << 4U)
#define AUDAC_DAC_DSM_ORDER_SHIFT            (5U)
#define AUDAC_DAC_DSM_ORDER_MASK             (0x3 << AUDAC_DAC_DSM_ORDER_SHIFT)
#define AUDAC_DAC_DSM_SCALING_MODE_SHIFT     (7U)
#define AUDAC_DAC_DSM_SCALING_MODE_MASK      (0x3 << AUDAC_DAC_DSM_SCALING_MODE_SHIFT)
#define AUDAC_DAC_DSM_SCALING_EN             (1 << 10U)
#define AUDAC_DAC_DSM_DITHER_AMP_SHIFT       (11U)
#define AUDAC_DAC_DSM_DITHER_AMP_MASK        (0x7 << AUDAC_DAC_DSM_DITHER_AMP_SHIFT)
#define AUDAC_DAC_DSM_DITHER_EN              (1 << 14U)
#define AUDAC_DAC_DSM_DITHER_PRBS_MODE_SHIFT (15U)
#define AUDAC_DAC_DSM_DITHER_PRBS_MODE_MASK  (0x3 << AUDAC_DAC_DSM_DITHER_PRBS_MODE_SHIFT)

/* 0x18 : audac_rsvd */
#define AUDAC_AU_PWM_RESERVED_SHIFT (0U)
#define AUDAC_AU_PWM_RESERVED_MASK  (0xffffffff << AUDAC_AU_PWM_RESERVED_SHIFT)

/* 0x1C : audac_test_0 */
#define AUDAC_DAC_IN_0_SHIFT   (0U)
#define AUDAC_DAC_IN_0_MASK    (0xffff << AUDAC_DAC_IN_0_SHIFT)
#define AUDAC_DAC_DPGA_0_SHIFT (16U)
#define AUDAC_DAC_DPGA_0_MASK  (0xffff << AUDAC_DAC_DPGA_0_SHIFT)

/* 0x20 : audac_test_1 */
#define AUDAC_DAC_FIR_0_SHIFT (0U)
#define AUDAC_DAC_FIR_0_MASK  (0x1ffff << AUDAC_DAC_FIR_0_SHIFT)

/* 0x24 : audac_test_2 */
#define AUDAC_DAC_SINC_0_SHIFT (0U)
#define AUDAC_DAC_SINC_0_MASK  (0xffff << AUDAC_DAC_SINC_0_SHIFT)

/* 0x28 : audac_test_3 */
#define AUDAC_AU_PWM_TEST_READ_SHIFT (0U)
#define AUDAC_AU_PWM_TEST_READ_MASK  (0xffffffff << AUDAC_AU_PWM_TEST_READ_SHIFT)

/* 0x8C : audac_fifo_ctrl */
#define AUDAC_TX_FIFO_FLUSH      (1 << 0U)
#define AUDAC_TXO_INT_EN         (1 << 1U)
#define AUDAC_TXU_INT_EN         (1 << 2U)
#define AUDAC_TXA_INT_EN         (1 << 3U)
#define AUDAC_TX_DRQ_EN          (1 << 4U)
#define AUDAC_TX_CH_EN_SHIFT     (8U)
#define AUDAC_TX_CH_EN_MASK      (0x3 << AUDAC_TX_CH_EN_SHIFT)
#define AUDAC_TX_DRQ_CNT_SHIFT   (14U)
#define AUDAC_TX_DRQ_CNT_MASK    (0x3 << AUDAC_TX_DRQ_CNT_SHIFT)
#define AUDAC_TX_TRG_LEVEL_SHIFT (16U)
#define AUDAC_TX_TRG_LEVEL_MASK  (0x1f << AUDAC_TX_TRG_LEVEL_SHIFT)
#define AUDAC_TX_DATA_MODE_SHIFT (24U)
#define AUDAC_TX_DATA_MODE_MASK  (0x3 << AUDAC_TX_DATA_MODE_SHIFT)

/* 0x90 : audac_fifo_status */
#define AUDAC_TXO_INT       (1 << 1U)
#define AUDAC_TXU_INT       (1 << 2U)
#define AUDAC_TXA_INT       (1 << 4U)
#define AUDAC_TXA_CNT_SHIFT (16U)
#define AUDAC_TXA_CNT_MASK  (0x1f << AUDAC_TXA_CNT_SHIFT)
#define AUDAC_TXA           (1 << 24U)

/* 0x94 : audac_fifo_data */
#define AUDAC_TX_DATA_SHIFT (0U)
#define AUDAC_TX_DATA_MASK  (0xffffffff << AUDAC_TX_DATA_SHIFT)

#endif /* __AUDAC_REG_H__ */
