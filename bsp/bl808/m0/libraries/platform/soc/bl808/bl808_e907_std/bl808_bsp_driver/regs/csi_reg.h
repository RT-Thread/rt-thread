/**
  ******************************************************************************
  * @file    csi_reg.h
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
#ifndef __CSI_REG_H__
#define __CSI_REG_H__

#include "bl808.h"

/* 0x0 : mipi_config */
#define CSI_MIPI_CONFIG_OFFSET   (0x0)
#define CSI_CR_CSI_EN            CSI_CR_CSI_EN
#define CSI_CR_CSI_EN_POS        (0U)
#define CSI_CR_CSI_EN_LEN        (1U)
#define CSI_CR_CSI_EN_MSK        (((1U << CSI_CR_CSI_EN_LEN) - 1) << CSI_CR_CSI_EN_POS)
#define CSI_CR_CSI_EN_UMSK       (~(((1U << CSI_CR_CSI_EN_LEN) - 1) << CSI_CR_CSI_EN_POS))
#define CSI_CR_LANE_NUM          CSI_CR_LANE_NUM
#define CSI_CR_LANE_NUM_POS      (1U)
#define CSI_CR_LANE_NUM_LEN      (1U)
#define CSI_CR_LANE_NUM_MSK      (((1U << CSI_CR_LANE_NUM_LEN) - 1) << CSI_CR_LANE_NUM_POS)
#define CSI_CR_LANE_NUM_UMSK     (~(((1U << CSI_CR_LANE_NUM_LEN) - 1) << CSI_CR_LANE_NUM_POS))
#define CSI_CR_LANE_INV          CSI_CR_LANE_INV
#define CSI_CR_LANE_INV_POS      (3U)
#define CSI_CR_LANE_INV_LEN      (1U)
#define CSI_CR_LANE_INV_MSK      (((1U << CSI_CR_LANE_INV_LEN) - 1) << CSI_CR_LANE_INV_POS)
#define CSI_CR_LANE_INV_UMSK     (~(((1U << CSI_CR_LANE_INV_LEN) - 1) << CSI_CR_LANE_INV_POS))
#define CSI_CR_DATA_BIT_INV      CSI_CR_DATA_BIT_INV
#define CSI_CR_DATA_BIT_INV_POS  (4U)
#define CSI_CR_DATA_BIT_INV_LEN  (1U)
#define CSI_CR_DATA_BIT_INV_MSK  (((1U << CSI_CR_DATA_BIT_INV_LEN) - 1) << CSI_CR_DATA_BIT_INV_POS)
#define CSI_CR_DATA_BIT_INV_UMSK (~(((1U << CSI_CR_DATA_BIT_INV_LEN) - 1) << CSI_CR_DATA_BIT_INV_POS))
#define CSI_CR_SYNC_SP_EN        CSI_CR_SYNC_SP_EN
#define CSI_CR_SYNC_SP_EN_POS    (5U)
#define CSI_CR_SYNC_SP_EN_LEN    (1U)
#define CSI_CR_SYNC_SP_EN_MSK    (((1U << CSI_CR_SYNC_SP_EN_LEN) - 1) << CSI_CR_SYNC_SP_EN_POS)
#define CSI_CR_SYNC_SP_EN_UMSK   (~(((1U << CSI_CR_SYNC_SP_EN_LEN) - 1) << CSI_CR_SYNC_SP_EN_POS))
#define CSI_CR_UNPACK_EN         CSI_CR_UNPACK_EN
#define CSI_CR_UNPACK_EN_POS     (6U)
#define CSI_CR_UNPACK_EN_LEN     (1U)
#define CSI_CR_UNPACK_EN_MSK     (((1U << CSI_CR_UNPACK_EN_LEN) - 1) << CSI_CR_UNPACK_EN_POS)
#define CSI_CR_UNPACK_EN_UMSK    (~(((1U << CSI_CR_UNPACK_EN_LEN) - 1) << CSI_CR_UNPACK_EN_POS))
#define CSI_CR_VC_DVP0           CSI_CR_VC_DVP0
#define CSI_CR_VC_DVP0_POS       (12U)
#define CSI_CR_VC_DVP0_LEN       (2U)
#define CSI_CR_VC_DVP0_MSK       (((1U << CSI_CR_VC_DVP0_LEN) - 1) << CSI_CR_VC_DVP0_POS)
#define CSI_CR_VC_DVP0_UMSK      (~(((1U << CSI_CR_VC_DVP0_LEN) - 1) << CSI_CR_VC_DVP0_POS))
#define CSI_CR_VC_DVP1           CSI_CR_VC_DVP1
#define CSI_CR_VC_DVP1_POS       (14U)
#define CSI_CR_VC_DVP1_LEN       (2U)
#define CSI_CR_VC_DVP1_MSK       (((1U << CSI_CR_VC_DVP1_LEN) - 1) << CSI_CR_VC_DVP1_POS)
#define CSI_CR_VC_DVP1_UMSK      (~(((1U << CSI_CR_VC_DVP1_LEN) - 1) << CSI_CR_VC_DVP1_POS))

/* 0x10 : csi_int_status */
#define CSI_INT_STATUS_OFFSET (0x10)
#define CSI_INT_STATUS        CSI_INT_STATUS
#define CSI_INT_STATUS_POS    (0U)
#define CSI_INT_STATUS_LEN    (6U)
#define CSI_INT_STATUS_MSK    (((1U << CSI_INT_STATUS_LEN) - 1) << CSI_INT_STATUS_POS)
#define CSI_INT_STATUS_UMSK   (~(((1U << CSI_INT_STATUS_LEN) - 1) << CSI_INT_STATUS_POS))

/* 0x14 : csi_int_mask */
#define CSI_INT_MASK_OFFSET (0x14)
#define CSI_INT_MASK        CSI_INT_MASK
#define CSI_INT_MASK_POS    (0U)
#define CSI_INT_MASK_LEN    (6U)
#define CSI_INT_MASK_MSK    (((1U << CSI_INT_MASK_LEN) - 1) << CSI_INT_MASK_POS)
#define CSI_INT_MASK_UMSK   (~(((1U << CSI_INT_MASK_LEN) - 1) << CSI_INT_MASK_POS))

/* 0x18 : csi_int_clear */
#define CSI_INT_CLEAR_OFFSET (0x18)
#define CSI_INT_CLEAR        CSI_INT_CLEAR
#define CSI_INT_CLEAR_POS    (0U)
#define CSI_INT_CLEAR_LEN    (6U)
#define CSI_INT_CLEAR_MSK    (((1U << CSI_INT_CLEAR_LEN) - 1) << CSI_INT_CLEAR_POS)
#define CSI_INT_CLEAR_UMSK   (~(((1U << CSI_INT_CLEAR_LEN) - 1) << CSI_INT_CLEAR_POS))

/* 0x1C : csi_int_enable */
#define CSI_INT_ENABLE_OFFSET (0x1C)
#define CSI_INT_ENABLE        CSI_INT_ENABLE
#define CSI_INT_ENABLE_POS    (0U)
#define CSI_INT_ENABLE_LEN    (6U)
#define CSI_INT_ENABLE_MSK    (((1U << CSI_INT_ENABLE_LEN) - 1) << CSI_INT_ENABLE_POS)
#define CSI_INT_ENABLE_UMSK   (~(((1U << CSI_INT_ENABLE_LEN) - 1) << CSI_INT_ENABLE_POS))

/* 0x20 : gnr_buf_status */
#define CSI_GNR_BUF_STATUS_OFFSET (0x20)
#define CSI_ST_GNR_FIFO_CNT       CSI_ST_GNR_FIFO_CNT
#define CSI_ST_GNR_FIFO_CNT_POS   (0U)
#define CSI_ST_GNR_FIFO_CNT_LEN   (4U)
#define CSI_ST_GNR_FIFO_CNT_MSK   (((1U << CSI_ST_GNR_FIFO_CNT_LEN) - 1) << CSI_ST_GNR_FIFO_CNT_POS)
#define CSI_ST_GNR_FIFO_CNT_UMSK  (~(((1U << CSI_ST_GNR_FIFO_CNT_LEN) - 1) << CSI_ST_GNR_FIFO_CNT_POS))

/* 0x24 : gnr_buf_rdata */
#define CSI_GNR_BUF_RDATA_OFFSET (0x24)
#define CSI_GNR_BUF_RDATA        CSI_GNR_BUF_RDATA
#define CSI_GNR_BUF_RDATA_POS    (0U)
#define CSI_GNR_BUF_RDATA_LEN    (32U)
#define CSI_GNR_BUF_RDATA_MSK    (((1U << CSI_GNR_BUF_RDATA_LEN) - 1) << CSI_GNR_BUF_RDATA_POS)
#define CSI_GNR_BUF_RDATA_UMSK   (~(((1U << CSI_GNR_BUF_RDATA_LEN) - 1) << CSI_GNR_BUF_RDATA_POS))

/* 0x80 : dphy_config_0 */
#define CSI_DPHY_CONFIG_0_OFFSET   (0x80)
#define CSI_DL0_ENABLE             CSI_DL0_ENABLE
#define CSI_DL0_ENABLE_POS         (0U)
#define CSI_DL0_ENABLE_LEN         (1U)
#define CSI_DL0_ENABLE_MSK         (((1U << CSI_DL0_ENABLE_LEN) - 1) << CSI_DL0_ENABLE_POS)
#define CSI_DL0_ENABLE_UMSK        (~(((1U << CSI_DL0_ENABLE_LEN) - 1) << CSI_DL0_ENABLE_POS))
#define CSI_DL1_ENABLE             CSI_DL1_ENABLE
#define CSI_DL1_ENABLE_POS         (1U)
#define CSI_DL1_ENABLE_LEN         (1U)
#define CSI_DL1_ENABLE_MSK         (((1U << CSI_DL1_ENABLE_LEN) - 1) << CSI_DL1_ENABLE_POS)
#define CSI_DL1_ENABLE_UMSK        (~(((1U << CSI_DL1_ENABLE_LEN) - 1) << CSI_DL1_ENABLE_POS))
#define CSI_CL_ENABLE              CSI_CL_ENABLE
#define CSI_CL_ENABLE_POS          (2U)
#define CSI_CL_ENABLE_LEN          (1U)
#define CSI_CL_ENABLE_MSK          (((1U << CSI_CL_ENABLE_LEN) - 1) << CSI_CL_ENABLE_POS)
#define CSI_CL_ENABLE_UMSK         (~(((1U << CSI_CL_ENABLE_LEN) - 1) << CSI_CL_ENABLE_POS))
#define CSI_DL0_STOPSTATE          CSI_DL0_STOPSTATE
#define CSI_DL0_STOPSTATE_POS      (4U)
#define CSI_DL0_STOPSTATE_LEN      (1U)
#define CSI_DL0_STOPSTATE_MSK      (((1U << CSI_DL0_STOPSTATE_LEN) - 1) << CSI_DL0_STOPSTATE_POS)
#define CSI_DL0_STOPSTATE_UMSK     (~(((1U << CSI_DL0_STOPSTATE_LEN) - 1) << CSI_DL0_STOPSTATE_POS))
#define CSI_DL1_STOPSTATE          CSI_DL1_STOPSTATE
#define CSI_DL1_STOPSTATE_POS      (5U)
#define CSI_DL1_STOPSTATE_LEN      (1U)
#define CSI_DL1_STOPSTATE_MSK      (((1U << CSI_DL1_STOPSTATE_LEN) - 1) << CSI_DL1_STOPSTATE_POS)
#define CSI_DL1_STOPSTATE_UMSK     (~(((1U << CSI_DL1_STOPSTATE_LEN) - 1) << CSI_DL1_STOPSTATE_POS))
#define CSI_CL_STOPSTATE           CSI_CL_STOPSTATE
#define CSI_CL_STOPSTATE_POS       (6U)
#define CSI_CL_STOPSTATE_LEN       (1U)
#define CSI_CL_STOPSTATE_MSK       (((1U << CSI_CL_STOPSTATE_LEN) - 1) << CSI_CL_STOPSTATE_POS)
#define CSI_CL_STOPSTATE_UMSK      (~(((1U << CSI_CL_STOPSTATE_LEN) - 1) << CSI_CL_STOPSTATE_POS))
#define CSI_DL0_ULPSACTIVENOT      CSI_DL0_ULPSACTIVENOT
#define CSI_DL0_ULPSACTIVENOT_POS  (8U)
#define CSI_DL0_ULPSACTIVENOT_LEN  (1U)
#define CSI_DL0_ULPSACTIVENOT_MSK  (((1U << CSI_DL0_ULPSACTIVENOT_LEN) - 1) << CSI_DL0_ULPSACTIVENOT_POS)
#define CSI_DL0_ULPSACTIVENOT_UMSK (~(((1U << CSI_DL0_ULPSACTIVENOT_LEN) - 1) << CSI_DL0_ULPSACTIVENOT_POS))
#define CSI_DL1_ULPSACTIVENOT      CSI_DL1_ULPSACTIVENOT
#define CSI_DL1_ULPSACTIVENOT_POS  (9U)
#define CSI_DL1_ULPSACTIVENOT_LEN  (1U)
#define CSI_DL1_ULPSACTIVENOT_MSK  (((1U << CSI_DL1_ULPSACTIVENOT_LEN) - 1) << CSI_DL1_ULPSACTIVENOT_POS)
#define CSI_DL1_ULPSACTIVENOT_UMSK (~(((1U << CSI_DL1_ULPSACTIVENOT_LEN) - 1) << CSI_DL1_ULPSACTIVENOT_POS))
#define CSI_CL_ULPSACTIVENOT       CSI_CL_ULPSACTIVENOT
#define CSI_CL_ULPSACTIVENOT_POS   (10U)
#define CSI_CL_ULPSACTIVENOT_LEN   (1U)
#define CSI_CL_ULPSACTIVENOT_MSK   (((1U << CSI_CL_ULPSACTIVENOT_LEN) - 1) << CSI_CL_ULPSACTIVENOT_POS)
#define CSI_CL_ULPSACTIVENOT_UMSK  (~(((1U << CSI_CL_ULPSACTIVENOT_LEN) - 1) << CSI_CL_ULPSACTIVENOT_POS))
#define CSI_DL0_FORCERXMODE        CSI_DL0_FORCERXMODE
#define CSI_DL0_FORCERXMODE_POS    (12U)
#define CSI_DL0_FORCERXMODE_LEN    (1U)
#define CSI_DL0_FORCERXMODE_MSK    (((1U << CSI_DL0_FORCERXMODE_LEN) - 1) << CSI_DL0_FORCERXMODE_POS)
#define CSI_DL0_FORCERXMODE_UMSK   (~(((1U << CSI_DL0_FORCERXMODE_LEN) - 1) << CSI_DL0_FORCERXMODE_POS))
#define CSI_DL1_FORCERXMODE        CSI_DL1_FORCERXMODE
#define CSI_DL1_FORCERXMODE_POS    (13U)
#define CSI_DL1_FORCERXMODE_LEN    (1U)
#define CSI_DL1_FORCERXMODE_MSK    (((1U << CSI_DL1_FORCERXMODE_LEN) - 1) << CSI_DL1_FORCERXMODE_POS)
#define CSI_DL1_FORCERXMODE_UMSK   (~(((1U << CSI_DL1_FORCERXMODE_LEN) - 1) << CSI_DL1_FORCERXMODE_POS))
#define CSI_CL_RXCLKACTIVEHS       CSI_CL_RXCLKACTIVEHS
#define CSI_CL_RXCLKACTIVEHS_POS   (14U)
#define CSI_CL_RXCLKACTIVEHS_LEN   (1U)
#define CSI_CL_RXCLKACTIVEHS_MSK   (((1U << CSI_CL_RXCLKACTIVEHS_LEN) - 1) << CSI_CL_RXCLKACTIVEHS_POS)
#define CSI_CL_RXCLKACTIVEHS_UMSK  (~(((1U << CSI_CL_RXCLKACTIVEHS_LEN) - 1) << CSI_CL_RXCLKACTIVEHS_POS))
#define CSI_CL_RXULPSCLKNOT        CSI_CL_RXULPSCLKNOT
#define CSI_CL_RXULPSCLKNOT_POS    (15U)
#define CSI_CL_RXULPSCLKNOT_LEN    (1U)
#define CSI_CL_RXULPSCLKNOT_MSK    (((1U << CSI_CL_RXULPSCLKNOT_LEN) - 1) << CSI_CL_RXULPSCLKNOT_POS)
#define CSI_CL_RXULPSCLKNOT_UMSK   (~(((1U << CSI_CL_RXULPSCLKNOT_LEN) - 1) << CSI_CL_RXULPSCLKNOT_POS))
#define CSI_RESET_N                CSI_RESET_N
#define CSI_RESET_N_POS            (31U)
#define CSI_RESET_N_LEN            (1U)
#define CSI_RESET_N_MSK            (((1U << CSI_RESET_N_LEN) - 1) << CSI_RESET_N_POS)
#define CSI_RESET_N_UMSK           (~(((1U << CSI_RESET_N_LEN) - 1) << CSI_RESET_N_POS))

/* 0x84 : dphy_config_1 */
#define CSI_DPHY_CONFIG_1_OFFSET     (0x84)
#define CSI_REG_TIME_CK_SETTLE       CSI_REG_TIME_CK_SETTLE
#define CSI_REG_TIME_CK_SETTLE_POS   (0U)
#define CSI_REG_TIME_CK_SETTLE_LEN   (8U)
#define CSI_REG_TIME_CK_SETTLE_MSK   (((1U << CSI_REG_TIME_CK_SETTLE_LEN) - 1) << CSI_REG_TIME_CK_SETTLE_POS)
#define CSI_REG_TIME_CK_SETTLE_UMSK  (~(((1U << CSI_REG_TIME_CK_SETTLE_LEN) - 1) << CSI_REG_TIME_CK_SETTLE_POS))
#define CSI_REG_TIME_CK_TERM_EN      CSI_REG_TIME_CK_TERM_EN
#define CSI_REG_TIME_CK_TERM_EN_POS  (8U)
#define CSI_REG_TIME_CK_TERM_EN_LEN  (8U)
#define CSI_REG_TIME_CK_TERM_EN_MSK  (((1U << CSI_REG_TIME_CK_TERM_EN_LEN) - 1) << CSI_REG_TIME_CK_TERM_EN_POS)
#define CSI_REG_TIME_CK_TERM_EN_UMSK (~(((1U << CSI_REG_TIME_CK_TERM_EN_LEN) - 1) << CSI_REG_TIME_CK_TERM_EN_POS))
#define CSI_REG_TIME_HS_SETTLE       CSI_REG_TIME_HS_SETTLE
#define CSI_REG_TIME_HS_SETTLE_POS   (16U)
#define CSI_REG_TIME_HS_SETTLE_LEN   (8U)
#define CSI_REG_TIME_HS_SETTLE_MSK   (((1U << CSI_REG_TIME_HS_SETTLE_LEN) - 1) << CSI_REG_TIME_HS_SETTLE_POS)
#define CSI_REG_TIME_HS_SETTLE_UMSK  (~(((1U << CSI_REG_TIME_HS_SETTLE_LEN) - 1) << CSI_REG_TIME_HS_SETTLE_POS))
#define CSI_REG_TIME_HS_TERM_EN      CSI_REG_TIME_HS_TERM_EN
#define CSI_REG_TIME_HS_TERM_EN_POS  (24U)
#define CSI_REG_TIME_HS_TERM_EN_LEN  (8U)
#define CSI_REG_TIME_HS_TERM_EN_MSK  (((1U << CSI_REG_TIME_HS_TERM_EN_LEN) - 1) << CSI_REG_TIME_HS_TERM_EN_POS)
#define CSI_REG_TIME_HS_TERM_EN_UMSK (~(((1U << CSI_REG_TIME_HS_TERM_EN_LEN) - 1) << CSI_REG_TIME_HS_TERM_EN_POS))

/* 0x88 : dphy_config_2 */
#define CSI_DPHY_CONFIG_2_OFFSET         (0x88)
#define CSI_REG_ANA_LPRXEN_CLK           CSI_REG_ANA_LPRXEN_CLK
#define CSI_REG_ANA_LPRXEN_CLK_POS       (0U)
#define CSI_REG_ANA_LPRXEN_CLK_LEN       (1U)
#define CSI_REG_ANA_LPRXEN_CLK_MSK       (((1U << CSI_REG_ANA_LPRXEN_CLK_LEN) - 1) << CSI_REG_ANA_LPRXEN_CLK_POS)
#define CSI_REG_ANA_LPRXEN_CLK_UMSK      (~(((1U << CSI_REG_ANA_LPRXEN_CLK_LEN) - 1) << CSI_REG_ANA_LPRXEN_CLK_POS))
#define CSI_REG_ANA_HSRXEN_CLK           CSI_REG_ANA_HSRXEN_CLK
#define CSI_REG_ANA_HSRXEN_CLK_POS       (1U)
#define CSI_REG_ANA_HSRXEN_CLK_LEN       (1U)
#define CSI_REG_ANA_HSRXEN_CLK_MSK       (((1U << CSI_REG_ANA_HSRXEN_CLK_LEN) - 1) << CSI_REG_ANA_HSRXEN_CLK_POS)
#define CSI_REG_ANA_HSRXEN_CLK_UMSK      (~(((1U << CSI_REG_ANA_HSRXEN_CLK_LEN) - 1) << CSI_REG_ANA_HSRXEN_CLK_POS))
#define CSI_REG_ANA_HSRX_STOP_STATE      CSI_REG_ANA_HSRX_STOP_STATE
#define CSI_REG_ANA_HSRX_STOP_STATE_POS  (2U)
#define CSI_REG_ANA_HSRX_STOP_STATE_LEN  (2U)
#define CSI_REG_ANA_HSRX_STOP_STATE_MSK  (((1U << CSI_REG_ANA_HSRX_STOP_STATE_LEN) - 1) << CSI_REG_ANA_HSRX_STOP_STATE_POS)
#define CSI_REG_ANA_HSRX_STOP_STATE_UMSK (~(((1U << CSI_REG_ANA_HSRX_STOP_STATE_LEN) - 1) << CSI_REG_ANA_HSRX_STOP_STATE_POS))
#define CSI_REG_ANA_HSRX_SYNC_EN         CSI_REG_ANA_HSRX_SYNC_EN
#define CSI_REG_ANA_HSRX_SYNC_EN_POS     (4U)
#define CSI_REG_ANA_HSRX_SYNC_EN_LEN     (2U)
#define CSI_REG_ANA_HSRX_SYNC_EN_MSK     (((1U << CSI_REG_ANA_HSRX_SYNC_EN_LEN) - 1) << CSI_REG_ANA_HSRX_SYNC_EN_POS)
#define CSI_REG_ANA_HSRX_SYNC_EN_UMSK    (~(((1U << CSI_REG_ANA_HSRX_SYNC_EN_LEN) - 1) << CSI_REG_ANA_HSRX_SYNC_EN_POS))
#define CSI_REG_ANA_LPRXEN               CSI_REG_ANA_LPRXEN
#define CSI_REG_ANA_LPRXEN_POS           (6U)
#define CSI_REG_ANA_LPRXEN_LEN           (2U)
#define CSI_REG_ANA_LPRXEN_MSK           (((1U << CSI_REG_ANA_LPRXEN_LEN) - 1) << CSI_REG_ANA_LPRXEN_POS)
#define CSI_REG_ANA_LPRXEN_UMSK          (~(((1U << CSI_REG_ANA_LPRXEN_LEN) - 1) << CSI_REG_ANA_LPRXEN_POS))
#define CSI_REG_ANA_HSRXEN               CSI_REG_ANA_HSRXEN
#define CSI_REG_ANA_HSRXEN_POS           (8U)
#define CSI_REG_ANA_HSRXEN_LEN           (2U)
#define CSI_REG_ANA_HSRXEN_MSK           (((1U << CSI_REG_ANA_HSRXEN_LEN) - 1) << CSI_REG_ANA_HSRXEN_POS)
#define CSI_REG_ANA_HSRXEN_UMSK          (~(((1U << CSI_REG_ANA_HSRXEN_LEN) - 1) << CSI_REG_ANA_HSRXEN_POS))
#define CSI_REG_ANA_TERM_EN              CSI_REG_ANA_TERM_EN
#define CSI_REG_ANA_TERM_EN_POS          (10U)
#define CSI_REG_ANA_TERM_EN_LEN          (5U)
#define CSI_REG_ANA_TERM_EN_MSK          (((1U << CSI_REG_ANA_TERM_EN_LEN) - 1) << CSI_REG_ANA_TERM_EN_POS)
#define CSI_REG_ANA_TERM_EN_UMSK         (~(((1U << CSI_REG_ANA_TERM_EN_LEN) - 1) << CSI_REG_ANA_TERM_EN_POS))
#define CSI_REG_ANA_TEST_EN              CSI_REG_ANA_TEST_EN
#define CSI_REG_ANA_TEST_EN_POS          (15U)
#define CSI_REG_ANA_TEST_EN_LEN          (1U)
#define CSI_REG_ANA_TEST_EN_MSK          (((1U << CSI_REG_ANA_TEST_EN_LEN) - 1) << CSI_REG_ANA_TEST_EN_POS)
#define CSI_REG_ANA_TEST_EN_UMSK         (~(((1U << CSI_REG_ANA_TEST_EN_LEN) - 1) << CSI_REG_ANA_TEST_EN_POS))
#define CSI_REG_PT_LOCK_COUNTER          CSI_REG_PT_LOCK_COUNTER
#define CSI_REG_PT_LOCK_COUNTER_POS      (16U)
#define CSI_REG_PT_LOCK_COUNTER_LEN      (4U)
#define CSI_REG_PT_LOCK_COUNTER_MSK      (((1U << CSI_REG_PT_LOCK_COUNTER_LEN) - 1) << CSI_REG_PT_LOCK_COUNTER_POS)
#define CSI_REG_PT_LOCK_COUNTER_UMSK     (~(((1U << CSI_REG_PT_LOCK_COUNTER_LEN) - 1) << CSI_REG_PT_LOCK_COUNTER_POS))
#define CSI_REG_PT_PRBS_OR_JITT          CSI_REG_PT_PRBS_OR_JITT
#define CSI_REG_PT_PRBS_OR_JITT_POS      (20U)
#define CSI_REG_PT_PRBS_OR_JITT_LEN      (1U)
#define CSI_REG_PT_PRBS_OR_JITT_MSK      (((1U << CSI_REG_PT_PRBS_OR_JITT_LEN) - 1) << CSI_REG_PT_PRBS_OR_JITT_POS)
#define CSI_REG_PT_PRBS_OR_JITT_UMSK     (~(((1U << CSI_REG_PT_PRBS_OR_JITT_LEN) - 1) << CSI_REG_PT_PRBS_OR_JITT_POS))
#define CSI_REG_PT_LP_MODE               CSI_REG_PT_LP_MODE
#define CSI_REG_PT_LP_MODE_POS           (21U)
#define CSI_REG_PT_LP_MODE_LEN           (1U)
#define CSI_REG_PT_LP_MODE_MSK           (((1U << CSI_REG_PT_LP_MODE_LEN) - 1) << CSI_REG_PT_LP_MODE_POS)
#define CSI_REG_PT_LP_MODE_UMSK          (~(((1U << CSI_REG_PT_LP_MODE_LEN) - 1) << CSI_REG_PT_LP_MODE_POS))
#define CSI_REG_PT_EN                    CSI_REG_PT_EN
#define CSI_REG_PT_EN_POS                (22U)
#define CSI_REG_PT_EN_LEN                (1U)
#define CSI_REG_PT_EN_MSK                (((1U << CSI_REG_PT_EN_LEN) - 1) << CSI_REG_PT_EN_POS)
#define CSI_REG_PT_EN_UMSK               (~(((1U << CSI_REG_PT_EN_LEN) - 1) << CSI_REG_PT_EN_POS))
#define CSI_REG_PT_LOCK                  CSI_REG_PT_LOCK
#define CSI_REG_PT_LOCK_POS              (23U)
#define CSI_REG_PT_LOCK_LEN              (1U)
#define CSI_REG_PT_LOCK_MSK              (((1U << CSI_REG_PT_LOCK_LEN) - 1) << CSI_REG_PT_LOCK_POS)
#define CSI_REG_PT_LOCK_UMSK             (~(((1U << CSI_REG_PT_LOCK_LEN) - 1) << CSI_REG_PT_LOCK_POS))
#define CSI_REG_PT_PASS                  CSI_REG_PT_PASS
#define CSI_REG_PT_PASS_POS              (24U)
#define CSI_REG_PT_PASS_LEN              (1U)
#define CSI_REG_PT_PASS_MSK              (((1U << CSI_REG_PT_PASS_LEN) - 1) << CSI_REG_PT_PASS_POS)
#define CSI_REG_PT_PASS_UMSK             (~(((1U << CSI_REG_PT_PASS_LEN) - 1) << CSI_REG_PT_PASS_POS))

/* 0x8C : dphy_config_3 */
#define CSI_DPHY_CONFIG_3_OFFSET (0x8C)
#define CSI_REG_CSI_ANA_1        CSI_REG_CSI_ANA_1
#define CSI_REG_CSI_ANA_1_POS    (0U)
#define CSI_REG_CSI_ANA_1_LEN    (16U)
#define CSI_REG_CSI_ANA_1_MSK    (((1U << CSI_REG_CSI_ANA_1_LEN) - 1) << CSI_REG_CSI_ANA_1_POS)
#define CSI_REG_CSI_ANA_1_UMSK   (~(((1U << CSI_REG_CSI_ANA_1_LEN) - 1) << CSI_REG_CSI_ANA_1_POS))
#define CSI_REG_CSI_ANA_0        CSI_REG_CSI_ANA_0
#define CSI_REG_CSI_ANA_0_POS    (16U)
#define CSI_REG_CSI_ANA_0_LEN    (16U)
#define CSI_REG_CSI_ANA_0_MSK    (((1U << CSI_REG_CSI_ANA_0_LEN) - 1) << CSI_REG_CSI_ANA_0_POS)
#define CSI_REG_CSI_ANA_0_UMSK   (~(((1U << CSI_REG_CSI_ANA_0_LEN) - 1) << CSI_REG_CSI_ANA_0_POS))

/* 0x90 : dphy_config_4 */
#define CSI_DPHY_CONFIG_4_OFFSET      (0x90)
#define CSI_REG_CSI_DC_TP_OUT_EN      CSI_REG_CSI_DC_TP_OUT_EN
#define CSI_REG_CSI_DC_TP_OUT_EN_POS  (0U)
#define CSI_REG_CSI_DC_TP_OUT_EN_LEN  (1U)
#define CSI_REG_CSI_DC_TP_OUT_EN_MSK  (((1U << CSI_REG_CSI_DC_TP_OUT_EN_LEN) - 1) << CSI_REG_CSI_DC_TP_OUT_EN_POS)
#define CSI_REG_CSI_DC_TP_OUT_EN_UMSK (~(((1U << CSI_REG_CSI_DC_TP_OUT_EN_LEN) - 1) << CSI_REG_CSI_DC_TP_OUT_EN_POS))
#define CSI_REG_CSI_PW_AVDD1815       CSI_REG_CSI_PW_AVDD1815
#define CSI_REG_CSI_PW_AVDD1815_POS   (4U)
#define CSI_REG_CSI_PW_AVDD1815_LEN   (1U)
#define CSI_REG_CSI_PW_AVDD1815_MSK   (((1U << CSI_REG_CSI_PW_AVDD1815_LEN) - 1) << CSI_REG_CSI_PW_AVDD1815_POS)
#define CSI_REG_CSI_PW_AVDD1815_UMSK  (~(((1U << CSI_REG_CSI_PW_AVDD1815_LEN) - 1) << CSI_REG_CSI_PW_AVDD1815_POS))

/* 0x94 : dphy_config_5 */
#define CSI_DPHY_CONFIG_5_OFFSET      (0x94)
#define CSI_REG_CSI_BYTE_CLK_INV      CSI_REG_CSI_BYTE_CLK_INV
#define CSI_REG_CSI_BYTE_CLK_INV_POS  (0U)
#define CSI_REG_CSI_BYTE_CLK_INV_LEN  (1U)
#define CSI_REG_CSI_BYTE_CLK_INV_MSK  (((1U << CSI_REG_CSI_BYTE_CLK_INV_LEN) - 1) << CSI_REG_CSI_BYTE_CLK_INV_POS)
#define CSI_REG_CSI_BYTE_CLK_INV_UMSK (~(((1U << CSI_REG_CSI_BYTE_CLK_INV_LEN) - 1) << CSI_REG_CSI_BYTE_CLK_INV_POS))
#define CSI_REG_CSI_DDR_CLK_INV       CSI_REG_CSI_DDR_CLK_INV
#define CSI_REG_CSI_DDR_CLK_INV_POS   (1U)
#define CSI_REG_CSI_DDR_CLK_INV_LEN   (1U)
#define CSI_REG_CSI_DDR_CLK_INV_MSK   (((1U << CSI_REG_CSI_DDR_CLK_INV_LEN) - 1) << CSI_REG_CSI_DDR_CLK_INV_POS)
#define CSI_REG_CSI_DDR_CLK_INV_UMSK  (~(((1U << CSI_REG_CSI_DDR_CLK_INV_LEN) - 1) << CSI_REG_CSI_DDR_CLK_INV_POS))

/* 0xFC : dummy_reg */
#define CSI_DUMMY_REG_OFFSET (0xFC)
#define CSI_DUMMY_REG        CSI_DUMMY_REG
#define CSI_DUMMY_REG_POS    (0U)
#define CSI_DUMMY_REG_LEN    (32U)
#define CSI_DUMMY_REG_MSK    (((1U << CSI_DUMMY_REG_LEN) - 1) << CSI_DUMMY_REG_POS)
#define CSI_DUMMY_REG_UMSK   (~(((1U << CSI_DUMMY_REG_LEN) - 1) << CSI_DUMMY_REG_POS))

struct csi_reg {
    /* 0x0 : mipi_config */
    union {
        struct {
            uint32_t cr_csi_en       : 1;  /* [    0],        r/w,        0x0 */
            uint32_t cr_lane_num     : 1;  /* [    1],        r/w,        0x1 */
            uint32_t rsvd_2          : 1;  /* [    2],       rsvd,        0x0 */
            uint32_t cr_lane_inv     : 1;  /* [    3],        r/w,        0x0 */
            uint32_t cr_data_bit_inv : 1;  /* [    4],        r/w,        0x0 */
            uint32_t cr_sync_sp_en   : 1;  /* [    5],        r/w,        0x0 */
            uint32_t cr_unpack_en    : 1;  /* [    6],        r/w,        0x1 */
            uint32_t reserved_7_11   : 5;  /* [11: 7],       rsvd,        0x0 */
            uint32_t cr_vc_dvp0      : 2;  /* [13:12],        r/w,        0x0 */
            uint32_t cr_vc_dvp1      : 2;  /* [15:14],        r/w,        0x1 */
            uint32_t reserved_16_31  : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mipi_config;

    /* 0x4  reserved */
    uint8_t RESERVED0x4[12];

    /* 0x10 : csi_int_status */
    union {
        struct {
            uint32_t csi_int_status : 6;  /* [ 5: 0],          r,        0x0 */
            uint32_t reserved_6_31  : 26; /* [31: 6],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } csi_int_status;

    /* 0x14 : csi_int_mask */
    union {
        struct {
            uint32_t csi_int_mask  : 6;  /* [ 5: 0],        r/w,       0x3f */
            uint32_t reserved_6_31 : 26; /* [31: 6],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } csi_int_mask;

    /* 0x18 : csi_int_clear */
    union {
        struct {
            uint32_t csi_int_clear : 6;  /* [ 5: 0],        w1p,        0x0 */
            uint32_t reserved_6_31 : 26; /* [31: 6],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } csi_int_clear;

    /* 0x1C : csi_int_enable */
    union {
        struct {
            uint32_t csi_int_enable : 6;  /* [ 5: 0],        r/w,       0x3f */
            uint32_t reserved_6_31  : 26; /* [31: 6],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } csi_int_enable;

    /* 0x20 : gnr_buf_status */
    union {
        struct {
            uint32_t st_gnr_fifo_cnt : 4;  /* [ 3: 0],          r,        0x0 */
            uint32_t reserved_4_31   : 28; /* [31: 4],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } gnr_buf_status;

    /* 0x24 : gnr_buf_rdata */
    union {
        struct {
            uint32_t gnr_buf_rdata : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } gnr_buf_rdata;

    /* 0x28  reserved */
    uint8_t RESERVED0x28[88];

    /* 0x80 : dphy_config_0 */
    union {
        struct {
            uint32_t dl0_enable        : 1;  /* [    0],        r/w,        0x0 */
            uint32_t dl1_enable        : 1;  /* [    1],        r/w,        0x0 */
            uint32_t cl_enable         : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3        : 1;  /* [    3],       rsvd,        0x0 */
            uint32_t dl0_stopstate     : 1;  /* [    4],          r,        0x1 */
            uint32_t dl1_stopstate     : 1;  /* [    5],          r,        0x1 */
            uint32_t cl_stopstate      : 1;  /* [    6],          r,        0x1 */
            uint32_t reserved_7        : 1;  /* [    7],       rsvd,        0x0 */
            uint32_t dl0_ulpsactivenot : 1;  /* [    8],          r,        0x1 */
            uint32_t dl1_ulpsactivenot : 1;  /* [    9],          r,        0x1 */
            uint32_t cl_ulpsactivenot  : 1;  /* [   10],          r,        0x1 */
            uint32_t reserved_11       : 1;  /* [   11],       rsvd,        0x0 */
            uint32_t dl0_forcerxmode   : 1;  /* [   12],        r/w,        0x0 */
            uint32_t dl1_forcerxmode   : 1;  /* [   13],        r/w,        0x0 */
            uint32_t cl_rxclkactivehs  : 1;  /* [   14],          r,        0x0 */
            uint32_t cl_rxulpsclknot   : 1;  /* [   15],          r,        0x1 */
            uint32_t reserved_16_30    : 15; /* [30:16],       rsvd,        0x0 */
            uint32_t csi_reset_n       : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } dphy_config_0;

    /* 0x84 : dphy_config_1 */
    union {
        struct {
            uint32_t reg_time_ck_settle  : 8; /* [ 7: 0],        r/w,        0xa */
            uint32_t reg_time_ck_term_en : 8; /* [15: 8],        r/w,        0x1 */
            uint32_t reg_time_hs_settle  : 8; /* [23:16],        r/w,       0x2f */
            uint32_t reg_time_hs_term_en : 8; /* [31:24],        r/w,        0xf */
        } BF;
        uint32_t WORD;
    } dphy_config_1;

    /* 0x88 : dphy_config_2 */
    union {
        struct {
            uint32_t reg_ana_lprxen_clk      : 1; /* [    0],        r/w,        0x0 */
            uint32_t reg_ana_hsrxen_clk      : 1; /* [    1],        r/w,        0x0 */
            uint32_t reg_ana_hsrx_stop_state : 2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_ana_hsrx_sync_en    : 2; /* [ 5: 4],        r/w,        0x0 */
            uint32_t reg_ana_lprxen          : 2; /* [ 7: 6],        r/w,        0x0 */
            uint32_t reg_ana_hsrxen          : 2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reg_ana_term_en         : 5; /* [14:10],        r/w,        0x0 */
            uint32_t reg_ana_test_en         : 1; /* [   15],        r/w,        0x0 */
            uint32_t reg_pt_lock_counter     : 4; /* [19:16],        r/w,        0x0 */
            uint32_t reg_pt_prbs_or_jitt     : 1; /* [   20],        r/w,        0x0 */
            uint32_t reg_pt_lp_mode          : 1; /* [   21],        r/w,        0x0 */
            uint32_t reg_pt_en               : 1; /* [   22],        r/w,        0x0 */
            uint32_t reg_pt_lock             : 1; /* [   23],          r,        0x0 */
            uint32_t reg_pt_pass             : 1; /* [   24],          r,        0x0 */
            uint32_t reserved_25_31          : 7; /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } dphy_config_2;

    /* 0x8C : dphy_config_3 */
    union {
        struct {
            uint32_t reg_csi_ana_1 : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_csi_ana_0 : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } dphy_config_3;

    /* 0x90 : dphy_config_4 */
    union {
        struct {
            uint32_t reg_csi_dc_tp_out_en : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_3         : 3;  /* [ 3: 1],       rsvd,        0x0 */
            uint32_t reg_csi_pw_avdd1815  : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31        : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } dphy_config_4;

    /* 0x94 : dphy_config_5 */
    union {
        struct {
            uint32_t reg_csi_byte_clk_inv : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reg_csi_ddr_clk_inv  : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_31        : 30; /* [31: 2],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } dphy_config_5;

    /* 0x98  reserved */
    uint8_t RESERVED0x98[100];

    /* 0xFC : dummy_reg */
    union {
        struct {
            uint32_t dummy_reg : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } dummy_reg;
};

typedef volatile struct csi_reg csi_reg_t;

#endif /* __CSI_REG_H__ */
