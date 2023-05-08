/**
  ******************************************************************************
  * @file    dac_reg.h
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
#ifndef __HARDWARE_DAC_H__
#define __HARDWARE_DAC_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

/* gpip base */
#define GPIP_GPDAC_CONFIG_OFFSET         (0x40) /* gpdac_config */
#define GPIP_GPDAC_DMA_CONFIG_OFFSET     (0x44) /* gpdac_dma_config */
#define GPIP_GPDAC_DMA_WDATA_OFFSET      (0x48) /* gpdac_dma_wdata */
#define GPIP_GPDAC_TX_FIFO_STATUS_OFFSET (0x4C) /* gpdac_tx_fifo_status */
/* glb base */
#if defined(BL702)
#define GLB_GPDAC_CTRL_OFFSET  (0x308) /* gpdac_ctrl */
#define GLB_GPDAC_ACTRL_OFFSET (0x30C) /* gpdac_actrl */
#define GLB_GPDAC_BCTRL_OFFSET (0x310) /* gpdac_bctrl */
#define GLB_GPDAC_DATA_OFFSET  (0x314) /* gpdac_data */
#else
#define GLB_GPDAC_CTRL_OFFSET  (0x120) /* gpdac_ctrl */
#define GLB_GPDAC_ACTRL_OFFSET (0x124) /* gpdac_actrl */
#define GLB_GPDAC_BCTRL_OFFSET (0x128) /* gpdac_bctrl */
#define GLB_GPDAC_DATA_OFFSET  (0x12C) /* gpdac_data */
#endif
/* Register Bitfield definitions *****************************************************/

/* 0x40 : gpdac_config */
#define GPIP_GPDAC_EN (1 << 0U)
#if defined(BL702)
#define GPIP_GPDAC_EN2      (1 << 1U)
#define GPIP_DSM_MODE_SHIFT (4U)
#define GPIP_DSM_MODE_MASK  (0x3 << GPIP_DSM_MODE_SHIFT)
#endif
#define GPIP_GPDAC_MODE_SHIFT     (8U)
#define GPIP_GPDAC_MODE_MASK      (0x7 << GPIP_GPDAC_MODE_SHIFT)
#define GPIP_GPDAC_CH_A_SEL_SHIFT (16U)
#define GPIP_GPDAC_CH_A_SEL_MASK  (0xf << GPIP_GPDAC_CH_A_SEL_SHIFT)
#define GPIP_GPDAC_CH_B_SEL_SHIFT (20U)
#define GPIP_GPDAC_CH_B_SEL_MASK  (0xf << GPIP_GPDAC_CH_B_SEL_SHIFT)

/* 0x44 : gpdac_dma_config */
#define GPIP_GPDAC_DMA_TX_EN (1 << 0U)
#if defined(BL616) || defined(BL628) || defined(BL606P) || defined(BL808)
#define GPIP_GPDAC_DMA_INV_MSB (1 << 1U)
#endif
#define GPIP_GPDAC_DMA_FORMAT_SHIFT (4U)
#define GPIP_GPDAC_DMA_FORMAT_MASK  (0x3 << GPIP_GPDAC_DMA_FORMAT_SHIFT)

/* 0x48 : gpdac_dma_wdata */
#define GPIP_GPDAC_DMA_WDATA_SHIFT (0U)
#define GPIP_GPDAC_DMA_WDATA_MASK  (0xffffffff << GPIP_GPDAC_DMA_WDATA_SHIFT)

/* 0x4C : gpdac_tx_fifo_status */
#define GPIP_TX_FIFO_EMPTY     (1 << 0U)
#define GPIP_TX_FIFO_FULL      (1 << 1U)
#define GPIP_TX_CS_SHIFT       (2U)
#define GPIP_TX_CS_MASK        (0x3 << GPIP_TX_CS_SHIFT)
#define GPIP_TXFIFORDPTR_SHIFT (4U)
#define GPIP_TXFIFORDPTR_MASK  (0x7 << GPIP_TXFIFORDPTR_SHIFT)
#define GPIP_TXFIFOWRPTR_SHIFT (8U)
#define GPIP_TXFIFOWRPTR_MASK  (0x3 << GPIP_TXFIFOWRPTR_SHIFT)

/* 0x308 : gpdac_ctrl */
#define GLB_GPDACA_RSTN_ANA      (1 << 0U)
#define GLB_GPDACB_RSTN_ANA      (1 << 1U)
#define GLB_GPDAC_TEST_EN        (1 << 7U)
#define GLB_GPDAC_REF_SEL        (1 << 8U)
#define GLB_GPDAC_TEST_SEL_SHIFT (9U)
#define GLB_GPDAC_TEST_SEL_MASK  (0x7 << GLB_GPDAC_TEST_SEL_SHIFT)
#if defined(BL616) || defined(BL628) || defined(BL606P) || defined(BL808)
#define GLB_GPDAC_ANA_CLK_SEL (1 << 12U)
#define GLB_GPDAC_DAT_CHA_SEL (1 << 13U)
#define GLB_GPDAC_DAT_CHB_SEL (1 << 14U)
#endif
#define GLB_GPDAC_RESERVED_SHIFT (24U)
#define GLB_GPDAC_RESERVED_MASK  (0xff << GLB_GPDAC_RESERVED_SHIFT)

/* 0x30C : gpdac_actrl */
#define GLB_GPDAC_A_EN           (1 << 0U)
#define GLB_GPDAC_IOA_EN         (1 << 1U)
#define GLB_GPDAC_A_RNG_SHIFT    (18U)
#define GLB_GPDAC_A_RNG_MASK     (0x3 << GLB_GPDAC_A_RNG_SHIFT)
#define GLB_GPDAC_A_OUTMUX_SHIFT (20U)
#define GLB_GPDAC_A_OUTMUX_MASK  (0x7 << GLB_GPDAC_A_OUTMUX_SHIFT)

/* 0x310 : gpdac_bctrl */
#define GLB_GPDAC_B_EN           (1 << 0U)
#define GLB_GPDAC_IOB_EN         (1 << 1U)
#define GLB_GPDAC_B_RNG_SHIFT    (18U)
#define GLB_GPDAC_B_RNG_MASK     (0x3 << GLB_GPDAC_B_RNG_SHIFT)
#define GLB_GPDAC_B_OUTMUX_SHIFT (20U)
#define GLB_GPDAC_B_OUTMUX_MASK  (0x7 << GLB_GPDAC_B_OUTMUX_SHIFT)

/* 0x314 : gpdac_data */
#if defined(BL702) || defined(BL602) || defined(BL606P) || defined(BL808)
#define GLB_GPDAC_B_DATA_SHIFT (0U)
#define GLB_GPDAC_B_DATA_MASK  (0x3ff << GLB_GPDAC_B_DATA_SHIFT)
#define GLB_GPDAC_A_DATA_SHIFT (16U)
#define GLB_GPDAC_A_DATA_MASK  (0x3ff << GLB_GPDAC_A_DATA_SHIFT)
#elif defined(BL616) || defined(BL628)
#define GLB_GPDAC_B_DATA_SHIFT (0U)
#define GLB_GPDAC_B_DATA_MASK  (0x1fff << GLB_GPDAC_B_DATA_SHIFT)
#define GLB_GPDAC_A_DATA_SHIFT (16U)
#define GLB_GPDAC_A_DATA_MASK  (0x1fff << GLB_GPDAC_A_DATA_SHIFT)
#endif

#endif /* __HARDWARE_DAC_H__ */
