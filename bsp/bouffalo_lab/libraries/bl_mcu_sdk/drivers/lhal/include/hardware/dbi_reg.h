/**
  ******************************************************************************
  * @file    dbi_reg.h
  * @version V1.0
  * @date    2023-02-08
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
#ifndef __DBI_REG_H__
#define __DBI_REG_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define DBI_CONFIG_OFFSET           (0x0)  /* dbi_config */
#define DBI_QSPI_CONFIG_OFFSET      (0x4)  /* qspi_config */
#define DBI_PIX_CNT_OFFSET          (0x8)  /* dbi_pix_cnt */
#define DBI_PRD_OFFSET              (0xC)  /* dbi_prd */
#define DBI_CMD_OFFSET              (0x10) /* dbi_cmd */
#define DBI_QSPI_ADR_OFFSET         (0x14) /* dbi_qspi_adr */
#define DBI_RDATA_0_OFFSET          (0x18) /* dbi_rdata_0 */
#define DBI_RDATA_1_OFFSET          (0x1C) /* dbi_rdata_1 */
#define DBI_INT_STS_OFFSET          (0x30) /* dbi_int_sts */
#define DBI_YUV_RGB_CONFIG_0_OFFSET (0x60) /* dbi_yuv_rgb_config_0 */
#define DBI_YUV_RGB_CONFIG_1_OFFSET (0x64) /* dbi_yuv_rgb_config_1 */
#define DBI_YUV_RGB_CONFIG_2_OFFSET (0x68) /* dbi_yuv_rgb_config_2 */
#define DBI_YUV_RGB_CONFIG_3_OFFSET (0x6C) /* dbi_yuv_rgb_config_3 */
#define DBI_YUV_RGB_CONFIG_4_OFFSET (0x70) /* dbi_yuv_rgb_config_4 */
#define DBI_YUV_RGB_CONFIG_5_OFFSET (0x74) /* dbi_yuv_rgb_config_5 */
#define DBI_FIFO_CONFIG_0_OFFSET    (0x80) /* dbi_fifo_config_0 */
#define DBI_FIFO_CONFIG_1_OFFSET    (0x84) /* dbi_fifo_config_1 */
#define DBI_FIFO_WDATA_OFFSET       (0x88) /* dbi_fifo_wdata */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : dbi_config */
#define DBI_CR_DBI_EN               (1 << 0U)
#define DBI_CR_DBI_SEL_SHIFT        (1U)
#define DBI_CR_DBI_SEL_MASK         (0x3 << DBI_CR_DBI_SEL_SHIFT)
#define DBI_CR_DBI_CMD_EN           (1 << 4U)
#define DBI_CR_DBI_DAT_EN           (1 << 5U)
#define DBI_CR_DBI_DAT_WR           (1 << 6U)
#define DBI_CR_DBI_DAT_TP           (1 << 7U)
#define DBI_CR_DBI_DAT_BC_SHIFT     (8U)
#define DBI_CR_DBI_DAT_BC_MASK      (0xff << DBI_CR_DBI_DAT_BC_SHIFT)
#define DBI_CR_DBI_SCL_POL          (1 << 16U)
#define DBI_CR_DBI_SCL_PH           (1 << 17U)
#define DBI_CR_DBI_CONT_EN          (1 << 18U)
#define DBI_CR_DBI_DMY_EN           (1 << 19U)
#define DBI_CR_DBI_DMY_CNT_SHIFT    (20U)
#define DBI_CR_DBI_DMY_CNT_MASK     (0xf << DBI_CR_DBI_DMY_CNT_SHIFT)
#define DBI_CR_DBI_CS_STRETCH       (1 << 24U)
#define DBI_STS_DBI_BUS_BUSY        (1 << 31U)

/* 0x4 : qspi_config */
#define DBI_CR_QSPI_CMD_4B          (1 << 0U)
#define DBI_CR_QSPI_ADR_4B          (1 << 1U)
#define DBI_CR_QSPI_DAT_4B          (1 << 2U)
#define DBI_CR_QSPI_ADR_BC_SHIFT    (4U)
#define DBI_CR_QSPI_ADR_BC_MASK     (0x3 << DBI_CR_QSPI_ADR_BC_SHIFT)

/* 0x8 : dbi_pix_cnt */
#define DBI_CR_DBI_PIX_CNT_SHIFT    (0U)
#define DBI_CR_DBI_PIX_CNT_MASK     (0xffffff << DBI_CR_DBI_PIX_CNT_SHIFT)
#define DBI_CR_DBI_PIX_FORMAT       (1 << 31U)

/* 0xC : dbi_prd */
#define DBI_CR_DBI_PRD_S_SHIFT      (0U)
#define DBI_CR_DBI_PRD_S_MASK       (0xff << DBI_CR_DBI_PRD_S_SHIFT)
#define DBI_CR_DBI_PRD_I_SHIFT      (8U)
#define DBI_CR_DBI_PRD_I_MASK       (0xff << DBI_CR_DBI_PRD_I_SHIFT)
#define DBI_CR_DBI_PRD_D_PH_0_SHIFT (16U)
#define DBI_CR_DBI_PRD_D_PH_0_MASK  (0xff << DBI_CR_DBI_PRD_D_PH_0_SHIFT)
#define DBI_CR_DBI_PRD_D_PH_1_SHIFT (24U)
#define DBI_CR_DBI_PRD_D_PH_1_MASK  (0xff << DBI_CR_DBI_PRD_D_PH_1_SHIFT)

/* 0x10 : dbi_cmd */
#define DBI_CR_DBI_CMD_SHIFT        (0U)
#define DBI_CR_DBI_CMD_MASK         (0xff << DBI_CR_DBI_CMD_SHIFT)

/* 0x14 : dbi_qspi_adr */
#define DBI_CR_QSPI_ADR_SHIFT       (0U)
#define DBI_CR_QSPI_ADR_MASK        (0xffffffff << DBI_CR_QSPI_ADR_SHIFT)

/* 0x18 : dbi_rdata_0 */
#define DBI_STS_DBI_RDATA_0_SHIFT   (0U)
#define DBI_STS_DBI_RDATA_0_MASK    (0xffffffff << DBI_STS_DBI_RDATA_0_SHIFT)

/* 0x1C : dbi_rdata_1 */
#define DBI_STS_DBI_RDATA_1_SHIFT   (0U)
#define DBI_STS_DBI_RDATA_1_MASK    (0xffffffff << DBI_STS_DBI_RDATA_1_SHIFT)

/* 0x30 : dbi_int_sts */
#define DBI_END_INT                 (1 << 0U)
#define DBI_TXF_INT                 (1 << 1U)
#define DBI_FER_INT                 (1 << 2U)
#define DBI_CR_DBI_END_MASK         (1 << 8U)
#define DBI_CR_DBI_TXF_MASK         (1 << 9U)
#define DBI_CR_DBI_FER_MASK         (1 << 10U)
#define DBI_CR_DBI_END_CLR          (1 << 16U)
#define DBI_CR_DBI_END_EN           (1 << 24U)
#define DBI_CR_DBI_TXF_EN           (1 << 25U)
#define DBI_CR_DBI_FER_EN           (1 << 26U)

/* 0x60 : dbi_yuv_rgb_config_0 */
#define DBI_CR_Y2R_PRE_0_SHIFT      (0U)
#define DBI_CR_Y2R_PRE_0_MASK       (0x1ff << DBI_CR_Y2R_PRE_0_SHIFT)
#define DBI_CR_Y2R_PRE_1_SHIFT      (10U)
#define DBI_CR_Y2R_PRE_1_MASK       (0x1ff << DBI_CR_Y2R_PRE_1_SHIFT)
#define DBI_CR_Y2R_PRE_2_SHIFT      (20U)
#define DBI_CR_Y2R_PRE_2_MASK       (0x1ff << DBI_CR_Y2R_PRE_2_SHIFT)
#define DBI_CR_Y2R_EN               (1 << 31U)

/* 0x64 : dbi_yuv_rgb_config_1 */
#define DBI_CR_Y2R_POS_0_SHIFT      (0U)
#define DBI_CR_Y2R_POS_0_MASK       (0x1ff << DBI_CR_Y2R_POS_0_SHIFT)
#define DBI_CR_Y2R_POS_1_SHIFT      (10U)
#define DBI_CR_Y2R_POS_1_MASK       (0x1ff << DBI_CR_Y2R_POS_1_SHIFT)
#define DBI_CR_Y2R_POS_2_SHIFT      (20U)
#define DBI_CR_Y2R_POS_2_MASK       (0x1ff << DBI_CR_Y2R_POS_2_SHIFT)

/* 0x68 : dbi_yuv_rgb_config_2 */
#define DBI_CR_Y2R_MTX_00_SHIFT     (0U)
#define DBI_CR_Y2R_MTX_00_MASK      (0xfff << DBI_CR_Y2R_MTX_00_SHIFT)
#define DBI_CR_Y2R_MTX_01_SHIFT     (12U)
#define DBI_CR_Y2R_MTX_01_MASK      (0xfff << DBI_CR_Y2R_MTX_01_SHIFT)
#define DBI_CR_Y2R_MTX_02_L_SHIFT   (24U)
#define DBI_CR_Y2R_MTX_02_L_MASK    (0xff << DBI_CR_Y2R_MTX_02_L_SHIFT)

/* 0x6C : dbi_yuv_rgb_config_3 */
#define DBI_CR_Y2R_MTX_02_U_SHIFT   (0U)
#define DBI_CR_Y2R_MTX_02_U_MASK    (0xf << DBI_CR_Y2R_MTX_02_U_SHIFT)
#define DBI_CR_Y2R_MTX_10_SHIFT     (4U)
#define DBI_CR_Y2R_MTX_10_MASK      (0xfff << DBI_CR_Y2R_MTX_10_SHIFT)
#define DBI_CR_Y2R_MTX_11_SHIFT     (16U)
#define DBI_CR_Y2R_MTX_11_MASK      (0xfff << DBI_CR_Y2R_MTX_11_SHIFT)
#define DBI_CR_Y2R_MTX_12_L_SHIFT   (28U)
#define DBI_CR_Y2R_MTX_12_L_MASK    (0xf << DBI_CR_Y2R_MTX_12_L_SHIFT)

/* 0x70 : dbi_yuv_rgb_config_4 */
#define DBI_CR_Y2R_MTX_12_U_SHIFT   (0U)
#define DBI_CR_Y2R_MTX_12_U_MASK    (0xff << DBI_CR_Y2R_MTX_12_U_SHIFT)
#define DBI_CR_Y2R_MTX_20_SHIFT     (8U)
#define DBI_CR_Y2R_MTX_20_MASK      (0xfff << DBI_CR_Y2R_MTX_20_SHIFT)
#define DBI_CR_Y2R_MTX_21_SHIFT     (20U)
#define DBI_CR_Y2R_MTX_21_MASK      (0xfff << DBI_CR_Y2R_MTX_21_SHIFT)

/* 0x74 : dbi_yuv_rgb_config_5 */
#define DBI_CR_Y2R_MTX_22_SHIFT     (0U)
#define DBI_CR_Y2R_MTX_22_MASK      (0xfff << DBI_CR_Y2R_MTX_22_SHIFT)

/* 0x80 : dbi_fifo_config_0 */
#define DBI_DMA_TX_EN               (1 << 0U)
#define DBI_TX_FIFO_CLR             (1 << 2U)
#define DBI_TX_FIFO_OVERFLOW        (1 << 4U)
#define DBI_TX_FIFO_UNDERFLOW       (1 << 5U)
#define DBI_FIFO_YUV_MODE           (1 << 28U)
#define DBI_FIFO_FORMAT_SHIFT       (29U)
#define DBI_FIFO_FORMAT_MASK        (0x7 << DBI_FIFO_FORMAT_SHIFT)

/* 0x84 : dbi_fifo_config_1 */
#define DBI_TX_FIFO_CNT_SHIFT       (0U)
#define DBI_TX_FIFO_CNT_MASK        (0xf << DBI_TX_FIFO_CNT_SHIFT)
#define DBI_TX_FIFO_TH_SHIFT        (16U)
#define DBI_TX_FIFO_TH_MASK         (0x7 << DBI_TX_FIFO_TH_SHIFT)

/* 0x88 : dbi_fifo_wdata */
#define DBI_FIFO_WDATA_SHIFT        (0U)
#define DBI_FIFO_WDATA_MASK         (0xffffffff << DBI_FIFO_WDATA_SHIFT)

#endif /* __DBI_REG_H__ */
