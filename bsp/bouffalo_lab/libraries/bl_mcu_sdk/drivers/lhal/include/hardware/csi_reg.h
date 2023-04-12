/**
  ******************************************************************************
  * @file    csi_reg.h
  * @version V1.0
  * @date    2022-12-13
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
#ifndef  __HARDWARE_CSI_H__
#define  __HARDWARE_CSI_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define CSI_MIPI_CONFIG_OFFSET    (0x0)/* mipi_config */
#define CSI_INT_STATUS_OFFSET     (0x10)/* csi_int_status */
#define CSI_INT_MASK_OFFSET       (0x14)/* csi_int_mask */
#define CSI_INT_CLEAR_OFFSET      (0x18)/* csi_int_clear */
#define CSI_INT_ENABLE_OFFSET     (0x1C)/* csi_int_enable */
#define CSI_GNR_BUF_STATUS_OFFSET (0x20)/* gnr_buf_status */
#define CSI_GNR_BUF_RDATA_OFFSET  (0x24)/* gnr_buf_rdata */
#define CSI_DPHY_CONFIG_0_OFFSET  (0x80)/* dphy_config_0 */
#define CSI_DPHY_CONFIG_1_OFFSET  (0x84)/* dphy_config_1 */
#define CSI_DPHY_CONFIG_2_OFFSET  (0x88)/* dphy_config_2 */
#define CSI_DPHY_CONFIG_3_OFFSET  (0x8C)/* dphy_config_3 */
#define CSI_DPHY_CONFIG_4_OFFSET  (0x90)/* dphy_config_4 */
#define CSI_DPHY_CONFIG_5_OFFSET  (0x94)/* dphy_config_5 */
#define CSI_DUMMY_REG_OFFSET      (0xFC)/* dummy_reg */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : mipi_config */
#define CSI_CR_CSI_EN        (1<<0U)
#define CSI_CR_LANE_NUM      (1<<1U)
#define CSI_CR_LANE_INV      (1<<3U)
#define CSI_CR_DATA_BIT_INV  (1<<4U)
#define CSI_CR_SYNC_SP_EN    (1<<5U)
#define CSI_CR_UNPACK_EN     (1<<6U)
#define CSI_CR_VC_DVP0_SHIFT (12U)
#define CSI_CR_VC_DVP0_MASK  (0x3<<CSI_CR_VC_DVP0_SHIFT)
#define CSI_CR_VC_DVP1_SHIFT (14U)
#define CSI_CR_VC_DVP1_MASK  (0x3<<CSI_CR_VC_DVP1_SHIFT)

/* 0x10 : csi_int_status */
#define CSI_INT_STATUS_SHIFT (0U)
#define CSI_INT_STATUS_MASK  (0x3f<<CSI_INT_STATUS_SHIFT)

/* 0x14 : csi_int_mask */
#define CSI_INT_MASK_SHIFT (0U)
#define CSI_INT_MASK_MASK  (0x3f<<CSI_INT_MASK_SHIFT)

/* 0x18 : csi_int_clear */
#define CSI_INT_CLEAR_SHIFT (0U)
#define CSI_INT_CLEAR_MASK  (0x3f<<CSI_INT_CLEAR_SHIFT)

/* 0x1C : csi_int_enable */
#define CSI_INT_ENABLE_SHIFT (0U)
#define CSI_INT_ENABLE_MASK  (0x3f<<CSI_INT_ENABLE_SHIFT)

/* 0x20 : gnr_buf_status */
#define CSI_ST_GNR_FIFO_CNT_SHIFT (0U)
#define CSI_ST_GNR_FIFO_CNT_MASK  (0xf<<CSI_ST_GNR_FIFO_CNT_SHIFT)

/* 0x24 : gnr_buf_rdata */
#define CSI_GNR_BUF_RDATA_SHIFT (0U)
#define CSI_GNR_BUF_RDATA_MASK  (0xffffffff<<CSI_GNR_BUF_RDATA_SHIFT)

/* 0x80 : dphy_config_0 */
#define CSI_DL0_ENABLE        (1<<0U)
#define CSI_DL1_ENABLE        (1<<1U)
#define CSI_CL_ENABLE         (1<<2U)
#define CSI_DL0_STOPSTATE     (1<<4U)
#define CSI_DL1_STOPSTATE     (1<<5U)
#define CSI_CL_STOPSTATE      (1<<6U)
#define CSI_DL0_ULPSACTIVENOT (1<<8U)
#define CSI_DL1_ULPSACTIVENOT (1<<9U)
#define CSI_CL_ULPSACTIVENOT  (1<<10U)
#define CSI_DL0_FORCERXMODE   (1<<12U)
#define CSI_DL1_FORCERXMODE   (1<<13U)
#define CSI_CL_RXCLKACTIVEHS  (1<<14U)
#define CSI_CL_RXULPSCLKNOT   (1<<15U)
#define CSI_RESET_N           (1<<31U)

/* 0x84 : dphy_config_1 */
#define CSI_REG_TIME_CK_SETTLE_SHIFT  (0U)
#define CSI_REG_TIME_CK_SETTLE_MASK   (0xff<<CSI_REG_TIME_CK_SETTLE_SHIFT)
#define CSI_REG_TIME_CK_TERM_EN_SHIFT (8U)
#define CSI_REG_TIME_CK_TERM_EN_MASK  (0xff<<CSI_REG_TIME_CK_TERM_EN_SHIFT)
#define CSI_REG_TIME_HS_SETTLE_SHIFT  (16U)
#define CSI_REG_TIME_HS_SETTLE_MASK   (0xff<<CSI_REG_TIME_HS_SETTLE_SHIFT)
#define CSI_REG_TIME_HS_TERM_EN_SHIFT (24U)
#define CSI_REG_TIME_HS_TERM_EN_MASK  (0xff<<CSI_REG_TIME_HS_TERM_EN_SHIFT)

/* 0x88 : dphy_config_2 */
#define CSI_REG_ANA_LPRXEN_CLK            (1<<0U)
#define CSI_REG_ANA_HSRXEN_CLK            (1<<1U)
#define CSI_REG_ANA_HSRX_STOP_STATE_SHIFT (2U)
#define CSI_REG_ANA_HSRX_STOP_STATE_MASK  (0x3<<CSI_REG_ANA_HSRX_STOP_STATE_SHIFT)
#define CSI_REG_ANA_HSRX_SYNC_EN_SHIFT    (4U)
#define CSI_REG_ANA_HSRX_SYNC_EN_MASK     (0x3<<CSI_REG_ANA_HSRX_SYNC_EN_SHIFT)
#define CSI_REG_ANA_LPRXEN_SHIFT          (6U)
#define CSI_REG_ANA_LPRXEN_MASK           (0x3<<CSI_REG_ANA_LPRXEN_SHIFT)
#define CSI_REG_ANA_HSRXEN_SHIFT          (8U)
#define CSI_REG_ANA_HSRXEN_MASK           (0x3<<CSI_REG_ANA_HSRXEN_SHIFT)
#define CSI_REG_ANA_TERM_EN_SHIFT         (10U)
#define CSI_REG_ANA_TERM_EN_MASK          (0x1f<<CSI_REG_ANA_TERM_EN_SHIFT)
#define CSI_REG_ANA_TEST_EN               (1<<15U)
#define CSI_REG_PT_LOCK_COUNTER_SHIFT     (16U)
#define CSI_REG_PT_LOCK_COUNTER_MASK      (0xf<<CSI_REG_PT_LOCK_COUNTER_SHIFT)
#define CSI_REG_PT_PRBS_OR_JITT           (1<<20U)
#define CSI_REG_PT_LP_MODE                (1<<21U)
#define CSI_REG_PT_EN                     (1<<22U)
#define CSI_REG_PT_LOCK                   (1<<23U)
#define CSI_REG_PT_PASS                   (1<<24U)

/* 0x8C : dphy_config_3 */
#define CSI_REG_CSI_ANA_1_SHIFT (0U)
#define CSI_REG_CSI_ANA_1_MASK  (0xffff<<CSI_REG_CSI_ANA_1_SHIFT)
#define CSI_REG_CSI_ANA_0_SHIFT (16U)
#define CSI_REG_CSI_ANA_0_MASK  (0xffff<<CSI_REG_CSI_ANA_0_SHIFT)

/* 0x90 : dphy_config_4 */
#define CSI_REG_CSI_DC_TP_OUT_EN (1<<0U)
#define CSI_REG_CSI_PW_AVDD1815  (1<<4U)

/* 0x94 : dphy_config_5 */
#define CSI_REG_CSI_BYTE_CLK_INV (1<<0U)
#define CSI_REG_CSI_DDR_CLK_INV  (1<<1U)

/* 0xFC : dummy_reg */
#define CSI_DUMMY_REG_SHIFT (0U)
#define CSI_DUMMY_REG_MASK  (0xffffffff<<CSI_DUMMY_REG_SHIFT)


#endif  /* __HARDWARE_CSI_H__ */
