/**
  ******************************************************************************
  * @file    dtsrc_reg.h
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
#ifndef __DTSRC_REG_H__
#define __DTSRC_REG_H__

#include "bl808.h"

/* 0x0 : config */
#define DTSRC_CONFIG_OFFSET             (0x0)
#define DTSRC_CR_ENABLE                 DTSRC_CR_ENABLE
#define DTSRC_CR_ENABLE_POS             (0U)
#define DTSRC_CR_ENABLE_LEN             (1U)
#define DTSRC_CR_ENABLE_MSK             (((1U << DTSRC_CR_ENABLE_LEN) - 1) << DTSRC_CR_ENABLE_POS)
#define DTSRC_CR_ENABLE_UMSK            (~(((1U << DTSRC_CR_ENABLE_LEN) - 1) << DTSRC_CR_ENABLE_POS))
#define DTSRC_CR_AXI_EN                 DTSRC_CR_AXI_EN
#define DTSRC_CR_AXI_EN_POS             (1U)
#define DTSRC_CR_AXI_EN_LEN             (1U)
#define DTSRC_CR_AXI_EN_MSK             (((1U << DTSRC_CR_AXI_EN_LEN) - 1) << DTSRC_CR_AXI_EN_POS)
#define DTSRC_CR_AXI_EN_UMSK            (~(((1U << DTSRC_CR_AXI_EN_LEN) - 1) << DTSRC_CR_AXI_EN_POS))
#define DTSRC_CR_MODE_CEA_861           DTSRC_CR_MODE_CEA_861
#define DTSRC_CR_MODE_CEA_861_POS       (2U)
#define DTSRC_CR_MODE_CEA_861_LEN       (1U)
#define DTSRC_CR_MODE_CEA_861_MSK       (((1U << DTSRC_CR_MODE_CEA_861_LEN) - 1) << DTSRC_CR_MODE_CEA_861_POS)
#define DTSRC_CR_MODE_CEA_861_UMSK      (~(((1U << DTSRC_CR_MODE_CEA_861_LEN) - 1) << DTSRC_CR_MODE_CEA_861_POS))
#define DTSRC_CR_SNSR_EN                DTSRC_CR_SNSR_EN
#define DTSRC_CR_SNSR_EN_POS            (3U)
#define DTSRC_CR_SNSR_EN_LEN            (1U)
#define DTSRC_CR_SNSR_EN_MSK            (((1U << DTSRC_CR_SNSR_EN_LEN) - 1) << DTSRC_CR_SNSR_EN_POS)
#define DTSRC_CR_SNSR_EN_UMSK           (~(((1U << DTSRC_CR_SNSR_EN_LEN) - 1) << DTSRC_CR_SNSR_EN_POS))
#define DTSRC_CR_SNSR_HSYNC_INV         DTSRC_CR_SNSR_HSYNC_INV
#define DTSRC_CR_SNSR_HSYNC_INV_POS     (4U)
#define DTSRC_CR_SNSR_HSYNC_INV_LEN     (1U)
#define DTSRC_CR_SNSR_HSYNC_INV_MSK     (((1U << DTSRC_CR_SNSR_HSYNC_INV_LEN) - 1) << DTSRC_CR_SNSR_HSYNC_INV_POS)
#define DTSRC_CR_SNSR_HSYNC_INV_UMSK    (~(((1U << DTSRC_CR_SNSR_HSYNC_INV_LEN) - 1) << DTSRC_CR_SNSR_HSYNC_INV_POS))
#define DTSRC_CR_SNSR_VSYNC_INV         DTSRC_CR_SNSR_VSYNC_INV
#define DTSRC_CR_SNSR_VSYNC_INV_POS     (5U)
#define DTSRC_CR_SNSR_VSYNC_INV_LEN     (1U)
#define DTSRC_CR_SNSR_VSYNC_INV_MSK     (((1U << DTSRC_CR_SNSR_VSYNC_INV_LEN) - 1) << DTSRC_CR_SNSR_VSYNC_INV_POS)
#define DTSRC_CR_SNSR_VSYNC_INV_UMSK    (~(((1U << DTSRC_CR_SNSR_VSYNC_INV_LEN) - 1) << DTSRC_CR_SNSR_VSYNC_INV_POS))
#define DTSRC_CR_AXI_SWAP_MODE          DTSRC_CR_AXI_SWAP_MODE
#define DTSRC_CR_AXI_SWAP_MODE_POS      (7U)
#define DTSRC_CR_AXI_SWAP_MODE_LEN      (1U)
#define DTSRC_CR_AXI_SWAP_MODE_MSK      (((1U << DTSRC_CR_AXI_SWAP_MODE_LEN) - 1) << DTSRC_CR_AXI_SWAP_MODE_POS)
#define DTSRC_CR_AXI_SWAP_MODE_UMSK     (~(((1U << DTSRC_CR_AXI_SWAP_MODE_LEN) - 1) << DTSRC_CR_AXI_SWAP_MODE_POS))
#define DTSRC_CR_AXI_SWAP_IDX_SEL       DTSRC_CR_AXI_SWAP_IDX_SEL
#define DTSRC_CR_AXI_SWAP_IDX_SEL_POS   (8U)
#define DTSRC_CR_AXI_SWAP_IDX_SEL_LEN   (4U)
#define DTSRC_CR_AXI_SWAP_IDX_SEL_MSK   (((1U << DTSRC_CR_AXI_SWAP_IDX_SEL_LEN) - 1) << DTSRC_CR_AXI_SWAP_IDX_SEL_POS)
#define DTSRC_CR_AXI_SWAP_IDX_SEL_UMSK  (~(((1U << DTSRC_CR_AXI_SWAP_IDX_SEL_LEN) - 1) << DTSRC_CR_AXI_SWAP_IDX_SEL_POS))
#define DTSRC_CR_AXI_SWAP_IDX_SWM       DTSRC_CR_AXI_SWAP_IDX_SWM
#define DTSRC_CR_AXI_SWAP_IDX_SWM_POS   (12U)
#define DTSRC_CR_AXI_SWAP_IDX_SWM_LEN   (1U)
#define DTSRC_CR_AXI_SWAP_IDX_SWM_MSK   (((1U << DTSRC_CR_AXI_SWAP_IDX_SWM_LEN) - 1) << DTSRC_CR_AXI_SWAP_IDX_SWM_POS)
#define DTSRC_CR_AXI_SWAP_IDX_SWM_UMSK  (~(((1U << DTSRC_CR_AXI_SWAP_IDX_SWM_LEN) - 1) << DTSRC_CR_AXI_SWAP_IDX_SWM_POS))
#define DTSRC_CR_AXI_SWAP_IDX_SWV       DTSRC_CR_AXI_SWAP_IDX_SWV
#define DTSRC_CR_AXI_SWAP_IDX_SWV_POS   (13U)
#define DTSRC_CR_AXI_SWAP_IDX_SWV_LEN   (1U)
#define DTSRC_CR_AXI_SWAP_IDX_SWV_MSK   (((1U << DTSRC_CR_AXI_SWAP_IDX_SWV_LEN) - 1) << DTSRC_CR_AXI_SWAP_IDX_SWV_POS)
#define DTSRC_CR_AXI_SWAP_IDX_SWV_UMSK  (~(((1U << DTSRC_CR_AXI_SWAP_IDX_SWV_LEN) - 1) << DTSRC_CR_AXI_SWAP_IDX_SWV_POS))
#define DTSRC_CR_AXI_DVP_DATA_MODE      DTSRC_CR_AXI_DVP_DATA_MODE
#define DTSRC_CR_AXI_DVP_DATA_MODE_POS  (16U)
#define DTSRC_CR_AXI_DVP_DATA_MODE_LEN  (3U)
#define DTSRC_CR_AXI_DVP_DATA_MODE_MSK  (((1U << DTSRC_CR_AXI_DVP_DATA_MODE_LEN) - 1) << DTSRC_CR_AXI_DVP_DATA_MODE_POS)
#define DTSRC_CR_AXI_DVP_DATA_MODE_UMSK (~(((1U << DTSRC_CR_AXI_DVP_DATA_MODE_LEN) - 1) << DTSRC_CR_AXI_DVP_DATA_MODE_POS))
#define DTSRC_CR_AXI_B0_SEL             DTSRC_CR_AXI_B0_SEL
#define DTSRC_CR_AXI_B0_SEL_POS         (20U)
#define DTSRC_CR_AXI_B0_SEL_LEN         (2U)
#define DTSRC_CR_AXI_B0_SEL_MSK         (((1U << DTSRC_CR_AXI_B0_SEL_LEN) - 1) << DTSRC_CR_AXI_B0_SEL_POS)
#define DTSRC_CR_AXI_B0_SEL_UMSK        (~(((1U << DTSRC_CR_AXI_B0_SEL_LEN) - 1) << DTSRC_CR_AXI_B0_SEL_POS))
#define DTSRC_CR_AXI_B1_SEL             DTSRC_CR_AXI_B1_SEL
#define DTSRC_CR_AXI_B1_SEL_POS         (22U)
#define DTSRC_CR_AXI_B1_SEL_LEN         (2U)
#define DTSRC_CR_AXI_B1_SEL_MSK         (((1U << DTSRC_CR_AXI_B1_SEL_LEN) - 1) << DTSRC_CR_AXI_B1_SEL_POS)
#define DTSRC_CR_AXI_B1_SEL_UMSK        (~(((1U << DTSRC_CR_AXI_B1_SEL_LEN) - 1) << DTSRC_CR_AXI_B1_SEL_POS))
#define DTSRC_CR_AXI_B2_SEL             DTSRC_CR_AXI_B2_SEL
#define DTSRC_CR_AXI_B2_SEL_POS         (24U)
#define DTSRC_CR_AXI_B2_SEL_LEN         (2U)
#define DTSRC_CR_AXI_B2_SEL_MSK         (((1U << DTSRC_CR_AXI_B2_SEL_LEN) - 1) << DTSRC_CR_AXI_B2_SEL_POS)
#define DTSRC_CR_AXI_B2_SEL_UMSK        (~(((1U << DTSRC_CR_AXI_B2_SEL_LEN) - 1) << DTSRC_CR_AXI_B2_SEL_POS))

/* 0x4 : frame_size_h */
#define DTSRC_FRAME_SIZE_H_OFFSET (0x4)
#define DTSRC_CR_TOTAL_H          DTSRC_CR_TOTAL_H
#define DTSRC_CR_TOTAL_H_POS      (0U)
#define DTSRC_CR_TOTAL_H_LEN      (12U)
#define DTSRC_CR_TOTAL_H_MSK      (((1U << DTSRC_CR_TOTAL_H_LEN) - 1) << DTSRC_CR_TOTAL_H_POS)
#define DTSRC_CR_TOTAL_H_UMSK     (~(((1U << DTSRC_CR_TOTAL_H_LEN) - 1) << DTSRC_CR_TOTAL_H_POS))
#define DTSRC_CR_BLANK_H          DTSRC_CR_BLANK_H
#define DTSRC_CR_BLANK_H_POS      (16U)
#define DTSRC_CR_BLANK_H_LEN      (12U)
#define DTSRC_CR_BLANK_H_MSK      (((1U << DTSRC_CR_BLANK_H_LEN) - 1) << DTSRC_CR_BLANK_H_POS)
#define DTSRC_CR_BLANK_H_UMSK     (~(((1U << DTSRC_CR_BLANK_H_LEN) - 1) << DTSRC_CR_BLANK_H_POS))

/* 0x8 : frame_size_v */
#define DTSRC_FRAME_SIZE_V_OFFSET (0x8)
#define DTSRC_CR_TOTAL_V          DTSRC_CR_TOTAL_V
#define DTSRC_CR_TOTAL_V_POS      (0U)
#define DTSRC_CR_TOTAL_V_LEN      (12U)
#define DTSRC_CR_TOTAL_V_MSK      (((1U << DTSRC_CR_TOTAL_V_LEN) - 1) << DTSRC_CR_TOTAL_V_POS)
#define DTSRC_CR_TOTAL_V_UMSK     (~(((1U << DTSRC_CR_TOTAL_V_LEN) - 1) << DTSRC_CR_TOTAL_V_POS))
#define DTSRC_CR_BLANK_V          DTSRC_CR_BLANK_V
#define DTSRC_CR_BLANK_V_POS      (16U)
#define DTSRC_CR_BLANK_V_LEN      (12U)
#define DTSRC_CR_BLANK_V_MSK      (((1U << DTSRC_CR_BLANK_V_LEN) - 1) << DTSRC_CR_BLANK_V_POS)
#define DTSRC_CR_BLANK_V_UMSK     (~(((1U << DTSRC_CR_BLANK_V_LEN) - 1) << DTSRC_CR_BLANK_V_POS))

/* 0xC : frame_size_cea_861 */
#define DTSRC_FRAME_SIZE_CEA_861_OFFSET (0xC)
#define DTSRC_CR_H_DURATION             DTSRC_CR_H_DURATION
#define DTSRC_CR_H_DURATION_POS         (0U)
#define DTSRC_CR_H_DURATION_LEN         (8U)
#define DTSRC_CR_H_DURATION_MSK         (((1U << DTSRC_CR_H_DURATION_LEN) - 1) << DTSRC_CR_H_DURATION_POS)
#define DTSRC_CR_H_DURATION_UMSK        (~(((1U << DTSRC_CR_H_DURATION_LEN) - 1) << DTSRC_CR_H_DURATION_POS))
#define DTSRC_CR_H_PLACEMENT            DTSRC_CR_H_PLACEMENT
#define DTSRC_CR_H_PLACEMENT_POS        (8U)
#define DTSRC_CR_H_PLACEMENT_LEN        (8U)
#define DTSRC_CR_H_PLACEMENT_MSK        (((1U << DTSRC_CR_H_PLACEMENT_LEN) - 1) << DTSRC_CR_H_PLACEMENT_POS)
#define DTSRC_CR_H_PLACEMENT_UMSK       (~(((1U << DTSRC_CR_H_PLACEMENT_LEN) - 1) << DTSRC_CR_H_PLACEMENT_POS))
#define DTSRC_CR_V_DURATION             DTSRC_CR_V_DURATION
#define DTSRC_CR_V_DURATION_POS         (16U)
#define DTSRC_CR_V_DURATION_LEN         (8U)
#define DTSRC_CR_V_DURATION_MSK         (((1U << DTSRC_CR_V_DURATION_LEN) - 1) << DTSRC_CR_V_DURATION_POS)
#define DTSRC_CR_V_DURATION_UMSK        (~(((1U << DTSRC_CR_V_DURATION_LEN) - 1) << DTSRC_CR_V_DURATION_POS))
#define DTSRC_CR_V_PLACEMENT            DTSRC_CR_V_PLACEMENT
#define DTSRC_CR_V_PLACEMENT_POS        (24U)
#define DTSRC_CR_V_PLACEMENT_LEN        (8U)
#define DTSRC_CR_V_PLACEMENT_MSK        (((1U << DTSRC_CR_V_PLACEMENT_LEN) - 1) << DTSRC_CR_V_PLACEMENT_POS)
#define DTSRC_CR_V_PLACEMENT_UMSK       (~(((1U << DTSRC_CR_V_PLACEMENT_LEN) - 1) << DTSRC_CR_V_PLACEMENT_POS))

/* 0x10 : pix_data_range */
#define DTSRC_PIX_DATA_RANGE_OFFSET (0x10)
#define DTSRC_CR_DATA_MIN           DTSRC_CR_DATA_MIN
#define DTSRC_CR_DATA_MIN_POS       (0U)
#define DTSRC_CR_DATA_MIN_LEN       (16U)
#define DTSRC_CR_DATA_MIN_MSK       (((1U << DTSRC_CR_DATA_MIN_LEN) - 1) << DTSRC_CR_DATA_MIN_POS)
#define DTSRC_CR_DATA_MIN_UMSK      (~(((1U << DTSRC_CR_DATA_MIN_LEN) - 1) << DTSRC_CR_DATA_MIN_POS))
#define DTSRC_CR_DATA_MAX           DTSRC_CR_DATA_MAX
#define DTSRC_CR_DATA_MAX_POS       (16U)
#define DTSRC_CR_DATA_MAX_LEN       (16U)
#define DTSRC_CR_DATA_MAX_MSK       (((1U << DTSRC_CR_DATA_MAX_LEN) - 1) << DTSRC_CR_DATA_MAX_POS)
#define DTSRC_CR_DATA_MAX_UMSK      (~(((1U << DTSRC_CR_DATA_MAX_LEN) - 1) << DTSRC_CR_DATA_MAX_POS))

/* 0x14 : pix_data_step */
#define DTSRC_PIX_DATA_STEP_OFFSET (0x14)
#define DTSRC_CR_DATA_STEP         DTSRC_CR_DATA_STEP
#define DTSRC_CR_DATA_STEP_POS     (0U)
#define DTSRC_CR_DATA_STEP_LEN     (8U)
#define DTSRC_CR_DATA_STEP_MSK     (((1U << DTSRC_CR_DATA_STEP_LEN) - 1) << DTSRC_CR_DATA_STEP_POS)
#define DTSRC_CR_DATA_STEP_UMSK    (~(((1U << DTSRC_CR_DATA_STEP_LEN) - 1) << DTSRC_CR_DATA_STEP_POS))

/* 0x20 : axi2dvp_setting */
#define DTSRC_AXI2DVP_SETTING_OFFSET    (0x20)
#define DTSRC_CR_AXI_XLEN               DTSRC_CR_AXI_XLEN
#define DTSRC_CR_AXI_XLEN_POS           (0U)
#define DTSRC_CR_AXI_XLEN_LEN           (3U)
#define DTSRC_CR_AXI_XLEN_MSK           (((1U << DTSRC_CR_AXI_XLEN_LEN) - 1) << DTSRC_CR_AXI_XLEN_POS)
#define DTSRC_CR_AXI_XLEN_UMSK          (~(((1U << DTSRC_CR_AXI_XLEN_LEN) - 1) << DTSRC_CR_AXI_XLEN_POS))
#define DTSRC_CR_AXI_DRAIN_ERR_CLR      DTSRC_CR_AXI_DRAIN_ERR_CLR
#define DTSRC_CR_AXI_DRAIN_ERR_CLR_POS  (4U)
#define DTSRC_CR_AXI_DRAIN_ERR_CLR_LEN  (1U)
#define DTSRC_CR_AXI_DRAIN_ERR_CLR_MSK  (((1U << DTSRC_CR_AXI_DRAIN_ERR_CLR_LEN) - 1) << DTSRC_CR_AXI_DRAIN_ERR_CLR_POS)
#define DTSRC_CR_AXI_DRAIN_ERR_CLR_UMSK (~(((1U << DTSRC_CR_AXI_DRAIN_ERR_CLR_LEN) - 1) << DTSRC_CR_AXI_DRAIN_ERR_CLR_POS))
#define DTSRC_CR_AXI_420_MODE           DTSRC_CR_AXI_420_MODE
#define DTSRC_CR_AXI_420_MODE_POS       (8U)
#define DTSRC_CR_AXI_420_MODE_LEN       (1U)
#define DTSRC_CR_AXI_420_MODE_MSK       (((1U << DTSRC_CR_AXI_420_MODE_LEN) - 1) << DTSRC_CR_AXI_420_MODE_POS)
#define DTSRC_CR_AXI_420_MODE_UMSK      (~(((1U << DTSRC_CR_AXI_420_MODE_LEN) - 1) << DTSRC_CR_AXI_420_MODE_POS))
#define DTSRC_CR_AXI_420_UD_SEL         DTSRC_CR_AXI_420_UD_SEL
#define DTSRC_CR_AXI_420_UD_SEL_POS     (9U)
#define DTSRC_CR_AXI_420_UD_SEL_LEN     (1U)
#define DTSRC_CR_AXI_420_UD_SEL_MSK     (((1U << DTSRC_CR_AXI_420_UD_SEL_LEN) - 1) << DTSRC_CR_AXI_420_UD_SEL_POS)
#define DTSRC_CR_AXI_420_UD_SEL_UMSK    (~(((1U << DTSRC_CR_AXI_420_UD_SEL_LEN) - 1) << DTSRC_CR_AXI_420_UD_SEL_POS))
#define DTSRC_CR_QOS_SW_MODE            DTSRC_CR_QOS_SW_MODE
#define DTSRC_CR_QOS_SW_MODE_POS        (10U)
#define DTSRC_CR_QOS_SW_MODE_LEN        (1U)
#define DTSRC_CR_QOS_SW_MODE_MSK        (((1U << DTSRC_CR_QOS_SW_MODE_LEN) - 1) << DTSRC_CR_QOS_SW_MODE_POS)
#define DTSRC_CR_QOS_SW_MODE_UMSK       (~(((1U << DTSRC_CR_QOS_SW_MODE_LEN) - 1) << DTSRC_CR_QOS_SW_MODE_POS))
#define DTSRC_CR_QOS_SW                 DTSRC_CR_QOS_SW
#define DTSRC_CR_QOS_SW_POS             (11U)
#define DTSRC_CR_QOS_SW_LEN             (1U)
#define DTSRC_CR_QOS_SW_MSK             (((1U << DTSRC_CR_QOS_SW_LEN) - 1) << DTSRC_CR_QOS_SW_POS)
#define DTSRC_CR_QOS_SW_UMSK            (~(((1U << DTSRC_CR_QOS_SW_LEN) - 1) << DTSRC_CR_QOS_SW_POS))

/* 0x24 : axi2dvp_start_addr_by */
#define DTSRC_AXI2DVP_START_ADDR_BY_OFFSET (0x24)
#define DTSRC_CR_AXI_ADDR_START_BY         DTSRC_CR_AXI_ADDR_START_BY
#define DTSRC_CR_AXI_ADDR_START_BY_POS     (0U)
#define DTSRC_CR_AXI_ADDR_START_BY_LEN     (32U)
#define DTSRC_CR_AXI_ADDR_START_BY_MSK     (((1U << DTSRC_CR_AXI_ADDR_START_BY_LEN) - 1) << DTSRC_CR_AXI_ADDR_START_BY_POS)
#define DTSRC_CR_AXI_ADDR_START_BY_UMSK    (~(((1U << DTSRC_CR_AXI_ADDR_START_BY_LEN) - 1) << DTSRC_CR_AXI_ADDR_START_BY_POS))

/* 0x28 : axi2dvp_burst_cnt */
#define DTSRC_AXI2DVP_BURST_CNT_OFFSET (0x28)
#define DTSRC_CR_AXI_FRAME_BC          DTSRC_CR_AXI_FRAME_BC
#define DTSRC_CR_AXI_FRAME_BC_POS      (0U)
#define DTSRC_CR_AXI_FRAME_BC_LEN      (32U)
#define DTSRC_CR_AXI_FRAME_BC_MSK      (((1U << DTSRC_CR_AXI_FRAME_BC_LEN) - 1) << DTSRC_CR_AXI_FRAME_BC_POS)
#define DTSRC_CR_AXI_FRAME_BC_UMSK     (~(((1U << DTSRC_CR_AXI_FRAME_BC_LEN) - 1) << DTSRC_CR_AXI_FRAME_BC_POS))

/* 0x2C : axi2dvp_status */
#define DTSRC_AXI2DVP_STATUS_OFFSET      (0x2C)
#define DTSRC_ST_AXI_FIFO_CNT_BY         DTSRC_ST_AXI_FIFO_CNT_BY
#define DTSRC_ST_AXI_FIFO_CNT_BY_POS     (0U)
#define DTSRC_ST_AXI_FIFO_CNT_BY_LEN     (7U)
#define DTSRC_ST_AXI_FIFO_CNT_BY_MSK     (((1U << DTSRC_ST_AXI_FIFO_CNT_BY_LEN) - 1) << DTSRC_ST_AXI_FIFO_CNT_BY_POS)
#define DTSRC_ST_AXI_FIFO_CNT_BY_UMSK    (~(((1U << DTSRC_ST_AXI_FIFO_CNT_BY_LEN) - 1) << DTSRC_ST_AXI_FIFO_CNT_BY_POS))
#define DTSRC_ST_AXI_DRAIN_ERROR_BY      DTSRC_ST_AXI_DRAIN_ERROR_BY
#define DTSRC_ST_AXI_DRAIN_ERROR_BY_POS  (7U)
#define DTSRC_ST_AXI_DRAIN_ERROR_BY_LEN  (1U)
#define DTSRC_ST_AXI_DRAIN_ERROR_BY_MSK  (((1U << DTSRC_ST_AXI_DRAIN_ERROR_BY_LEN) - 1) << DTSRC_ST_AXI_DRAIN_ERROR_BY_POS)
#define DTSRC_ST_AXI_DRAIN_ERROR_BY_UMSK (~(((1U << DTSRC_ST_AXI_DRAIN_ERROR_BY_LEN) - 1) << DTSRC_ST_AXI_DRAIN_ERROR_BY_POS))
#define DTSRC_ST_AXI_STATE_IDLE_BY       DTSRC_ST_AXI_STATE_IDLE_BY
#define DTSRC_ST_AXI_STATE_IDLE_BY_POS   (8U)
#define DTSRC_ST_AXI_STATE_IDLE_BY_LEN   (1U)
#define DTSRC_ST_AXI_STATE_IDLE_BY_MSK   (((1U << DTSRC_ST_AXI_STATE_IDLE_BY_LEN) - 1) << DTSRC_ST_AXI_STATE_IDLE_BY_POS)
#define DTSRC_ST_AXI_STATE_IDLE_BY_UMSK  (~(((1U << DTSRC_ST_AXI_STATE_IDLE_BY_LEN) - 1) << DTSRC_ST_AXI_STATE_IDLE_BY_POS))
#define DTSRC_ST_AXI_STATE_FUNC_BY       DTSRC_ST_AXI_STATE_FUNC_BY
#define DTSRC_ST_AXI_STATE_FUNC_BY_POS   (9U)
#define DTSRC_ST_AXI_STATE_FUNC_BY_LEN   (1U)
#define DTSRC_ST_AXI_STATE_FUNC_BY_MSK   (((1U << DTSRC_ST_AXI_STATE_FUNC_BY_LEN) - 1) << DTSRC_ST_AXI_STATE_FUNC_BY_POS)
#define DTSRC_ST_AXI_STATE_FUNC_BY_UMSK  (~(((1U << DTSRC_ST_AXI_STATE_FUNC_BY_LEN) - 1) << DTSRC_ST_AXI_STATE_FUNC_BY_POS))
#define DTSRC_ST_AXI_STATE_FLSH_BY       DTSRC_ST_AXI_STATE_FLSH_BY
#define DTSRC_ST_AXI_STATE_FLSH_BY_POS   (10U)
#define DTSRC_ST_AXI_STATE_FLSH_BY_LEN   (1U)
#define DTSRC_ST_AXI_STATE_FLSH_BY_MSK   (((1U << DTSRC_ST_AXI_STATE_FLSH_BY_LEN) - 1) << DTSRC_ST_AXI_STATE_FLSH_BY_POS)
#define DTSRC_ST_AXI_STATE_FLSH_BY_UMSK  (~(((1U << DTSRC_ST_AXI_STATE_FLSH_BY_LEN) - 1) << DTSRC_ST_AXI_STATE_FLSH_BY_POS))
#define DTSRC_ST_AXI_FIFO_CNT_UV         DTSRC_ST_AXI_FIFO_CNT_UV
#define DTSRC_ST_AXI_FIFO_CNT_UV_POS     (16U)
#define DTSRC_ST_AXI_FIFO_CNT_UV_LEN     (7U)
#define DTSRC_ST_AXI_FIFO_CNT_UV_MSK     (((1U << DTSRC_ST_AXI_FIFO_CNT_UV_LEN) - 1) << DTSRC_ST_AXI_FIFO_CNT_UV_POS)
#define DTSRC_ST_AXI_FIFO_CNT_UV_UMSK    (~(((1U << DTSRC_ST_AXI_FIFO_CNT_UV_LEN) - 1) << DTSRC_ST_AXI_FIFO_CNT_UV_POS))
#define DTSRC_ST_AXI_DRAIN_ERROR_UV      DTSRC_ST_AXI_DRAIN_ERROR_UV
#define DTSRC_ST_AXI_DRAIN_ERROR_UV_POS  (23U)
#define DTSRC_ST_AXI_DRAIN_ERROR_UV_LEN  (1U)
#define DTSRC_ST_AXI_DRAIN_ERROR_UV_MSK  (((1U << DTSRC_ST_AXI_DRAIN_ERROR_UV_LEN) - 1) << DTSRC_ST_AXI_DRAIN_ERROR_UV_POS)
#define DTSRC_ST_AXI_DRAIN_ERROR_UV_UMSK (~(((1U << DTSRC_ST_AXI_DRAIN_ERROR_UV_LEN) - 1) << DTSRC_ST_AXI_DRAIN_ERROR_UV_POS))
#define DTSRC_ST_AXI_STATE_IDLE_UV       DTSRC_ST_AXI_STATE_IDLE_UV
#define DTSRC_ST_AXI_STATE_IDLE_UV_POS   (24U)
#define DTSRC_ST_AXI_STATE_IDLE_UV_LEN   (1U)
#define DTSRC_ST_AXI_STATE_IDLE_UV_MSK   (((1U << DTSRC_ST_AXI_STATE_IDLE_UV_LEN) - 1) << DTSRC_ST_AXI_STATE_IDLE_UV_POS)
#define DTSRC_ST_AXI_STATE_IDLE_UV_UMSK  (~(((1U << DTSRC_ST_AXI_STATE_IDLE_UV_LEN) - 1) << DTSRC_ST_AXI_STATE_IDLE_UV_POS))
#define DTSRC_ST_AXI_STATE_FUNC_UV       DTSRC_ST_AXI_STATE_FUNC_UV
#define DTSRC_ST_AXI_STATE_FUNC_UV_POS   (25U)
#define DTSRC_ST_AXI_STATE_FUNC_UV_LEN   (1U)
#define DTSRC_ST_AXI_STATE_FUNC_UV_MSK   (((1U << DTSRC_ST_AXI_STATE_FUNC_UV_LEN) - 1) << DTSRC_ST_AXI_STATE_FUNC_UV_POS)
#define DTSRC_ST_AXI_STATE_FUNC_UV_UMSK  (~(((1U << DTSRC_ST_AXI_STATE_FUNC_UV_LEN) - 1) << DTSRC_ST_AXI_STATE_FUNC_UV_POS))
#define DTSRC_ST_AXI_STATE_FLSH_UV       DTSRC_ST_AXI_STATE_FLSH_UV
#define DTSRC_ST_AXI_STATE_FLSH_UV_POS   (26U)
#define DTSRC_ST_AXI_STATE_FLSH_UV_LEN   (1U)
#define DTSRC_ST_AXI_STATE_FLSH_UV_MSK   (((1U << DTSRC_ST_AXI_STATE_FLSH_UV_LEN) - 1) << DTSRC_ST_AXI_STATE_FLSH_UV_POS)
#define DTSRC_ST_AXI_STATE_FLSH_UV_UMSK  (~(((1U << DTSRC_ST_AXI_STATE_FLSH_UV_LEN) - 1) << DTSRC_ST_AXI_STATE_FLSH_UV_POS))

/* 0x30 : axi2dvp_swap_addr_by */
#define DTSRC_AXI2DVP_SWAP_ADDR_BY_OFFSET (0x30)
#define DTSRC_CR_AXI_ADDR_SWAP_BY         DTSRC_CR_AXI_ADDR_SWAP_BY
#define DTSRC_CR_AXI_ADDR_SWAP_BY_POS     (0U)
#define DTSRC_CR_AXI_ADDR_SWAP_BY_LEN     (32U)
#define DTSRC_CR_AXI_ADDR_SWAP_BY_MSK     (((1U << DTSRC_CR_AXI_ADDR_SWAP_BY_LEN) - 1) << DTSRC_CR_AXI_ADDR_SWAP_BY_POS)
#define DTSRC_CR_AXI_ADDR_SWAP_BY_UMSK    (~(((1U << DTSRC_CR_AXI_ADDR_SWAP_BY_LEN) - 1) << DTSRC_CR_AXI_ADDR_SWAP_BY_POS))

/* 0x34 : axi2dvp_prefetch */
#define DTSRC_AXI2DVP_PREFETCH_OFFSET (0x34)
#define DTSRC_CR_PREFETCH_V           DTSRC_CR_PREFETCH_V
#define DTSRC_CR_PREFETCH_V_POS       (0U)
#define DTSRC_CR_PREFETCH_V_LEN       (12U)
#define DTSRC_CR_PREFETCH_V_MSK       (((1U << DTSRC_CR_PREFETCH_V_LEN) - 1) << DTSRC_CR_PREFETCH_V_POS)
#define DTSRC_CR_PREFETCH_V_UMSK      (~(((1U << DTSRC_CR_PREFETCH_V_LEN) - 1) << DTSRC_CR_PREFETCH_V_POS))

/* 0x38 : snsr2dvp_wait_pos */
#define DTSRC_SNSR2DVP_WAIT_POS_OFFSET (0x38)
#define DTSRC_CR_SNSR_FIFO_TH          DTSRC_CR_SNSR_FIFO_TH
#define DTSRC_CR_SNSR_FIFO_TH_POS      (0U)
#define DTSRC_CR_SNSR_FIFO_TH_LEN      (11U)
#define DTSRC_CR_SNSR_FIFO_TH_MSK      (((1U << DTSRC_CR_SNSR_FIFO_TH_LEN) - 1) << DTSRC_CR_SNSR_FIFO_TH_POS)
#define DTSRC_CR_SNSR_FIFO_TH_UMSK     (~(((1U << DTSRC_CR_SNSR_FIFO_TH_LEN) - 1) << DTSRC_CR_SNSR_FIFO_TH_POS))

/* 0x40 : axi2dvp_start_addr_uv */
#define DTSRC_AXI2DVP_START_ADDR_UV_OFFSET (0x40)
#define DTSRC_CR_AXI_ADDR_START_UV         DTSRC_CR_AXI_ADDR_START_UV
#define DTSRC_CR_AXI_ADDR_START_UV_POS     (0U)
#define DTSRC_CR_AXI_ADDR_START_UV_LEN     (32U)
#define DTSRC_CR_AXI_ADDR_START_UV_MSK     (((1U << DTSRC_CR_AXI_ADDR_START_UV_LEN) - 1) << DTSRC_CR_AXI_ADDR_START_UV_POS)
#define DTSRC_CR_AXI_ADDR_START_UV_UMSK    (~(((1U << DTSRC_CR_AXI_ADDR_START_UV_LEN) - 1) << DTSRC_CR_AXI_ADDR_START_UV_POS))

/* 0x44 : axi2dvp_swap_addr_uv */
#define DTSRC_AXI2DVP_SWAP_ADDR_UV_OFFSET (0x44)
#define DTSRC_CR_AXI_ADDR_SWAP_UV         DTSRC_CR_AXI_ADDR_SWAP_UV
#define DTSRC_CR_AXI_ADDR_SWAP_UV_POS     (0U)
#define DTSRC_CR_AXI_ADDR_SWAP_UV_LEN     (32U)
#define DTSRC_CR_AXI_ADDR_SWAP_UV_MSK     (((1U << DTSRC_CR_AXI_ADDR_SWAP_UV_LEN) - 1) << DTSRC_CR_AXI_ADDR_SWAP_UV_POS)
#define DTSRC_CR_AXI_ADDR_SWAP_UV_UMSK    (~(((1U << DTSRC_CR_AXI_ADDR_SWAP_UV_LEN) - 1) << DTSRC_CR_AXI_ADDR_SWAP_UV_POS))

struct dtsrc_reg {
    /* 0x0 : config */
    union {
        struct {
            uint32_t cr_enable            : 1; /* [    0],        r/w,        0x0 */
            uint32_t cr_axi_en            : 1; /* [    1],        r/w,        0x0 */
            uint32_t cr_mode_cea_861      : 1; /* [    2],        r/w,        0x0 */
            uint32_t cr_snsr_en           : 1; /* [    3],        r/w,        0x0 */
            uint32_t cr_snsr_hsync_inv    : 1; /* [    4],        r/w,        0x0 */
            uint32_t cr_snsr_vsync_inv    : 1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6           : 1; /* [    6],       rsvd,        0x0 */
            uint32_t cr_axi_swap_mode     : 1; /* [    7],        r/w,        0x0 */
            uint32_t cr_axi_swap_idx_sel  : 4; /* [11: 8],        r/w,        0x0 */
            uint32_t cr_axi_swap_idx_swm  : 1; /* [   12],        r/w,        0x0 */
            uint32_t cr_axi_swap_idx_swv  : 1; /* [   13],        r/w,        0x0 */
            uint32_t reserved_14_15       : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t cr_axi_dvp_data_mode : 3; /* [18:16],        r/w,        0x0 */
            uint32_t reserved_19          : 1; /* [   19],       rsvd,        0x0 */
            uint32_t cr_axi_b0_sel        : 2; /* [21:20],        r/w,        0x0 */
            uint32_t cr_axi_b1_sel        : 2; /* [23:22],        r/w,        0x1 */
            uint32_t cr_axi_b2_sel        : 2; /* [25:24],        r/w,        0x2 */
            uint32_t reserved_26_31       : 6; /* [31:26],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } config;

    /* 0x4 : frame_size_h */
    union {
        struct {
            uint32_t cr_total_h     : 12; /* [11: 0],        r/w,      0x897 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t cr_blank_h     : 12; /* [27:16],        r/w,      0x117 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } frame_size_h;

    /* 0x8 : frame_size_v */
    union {
        struct {
            uint32_t cr_total_v     : 12; /* [11: 0],        r/w,      0x464 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t cr_blank_v     : 12; /* [27:16],        r/w,       0x2c */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } frame_size_v;

    /* 0xC : frame_size_cea_861 */
    union {
        struct {
            uint32_t cr_h_duration  : 8; /* [ 7: 0],        r/w,       0x83 */
            uint32_t cr_h_placement : 8; /* [15: 8],        r/w,       0x57 */
            uint32_t cr_v_duration  : 8; /* [23:16],        r/w,        0x8 */
            uint32_t cr_v_placement : 8; /* [31:24],        r/w,        0x3 */
        } BF;
        uint32_t WORD;
    } frame_size_cea_861;

    /* 0x10 : pix_data_range */
    union {
        struct {
            uint32_t cr_data_min : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t cr_data_max : 16; /* [31:16],        r/w,     0xffff */
        } BF;
        uint32_t WORD;
    } pix_data_range;

    /* 0x14 : pix_data_step */
    union {
        struct {
            uint32_t cr_data_step  : 8;  /* [ 7: 0],        r/w,        0x1 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pix_data_step;

    /* 0x18  reserved */
    uint8_t RESERVED0x18[8];

    /* 0x20 : axi2dvp_setting */
    union {
        struct {
            uint32_t cr_axi_xlen          : 3;  /* [ 2: 0],        r/w,        0x3 */
            uint32_t reserved_3           : 1;  /* [    3],       rsvd,        0x0 */
            uint32_t cr_axi_drain_err_clr : 1;  /* [    4],        w1p,        0x0 */
            uint32_t reserved_5_7         : 3;  /* [ 7: 5],       rsvd,        0x0 */
            uint32_t cr_axi_420_mode      : 1;  /* [    8],        r/w,        0x0 */
            uint32_t cr_axi_420_ud_sel    : 1;  /* [    9],        r/w,        0x0 */
            uint32_t cr_qos_sw_mode       : 1;  /* [   10],        r/w,        0x0 */
            uint32_t cr_qos_sw            : 1;  /* [   11],        r/w,        0x0 */
            uint32_t reserved_12_31       : 20; /* [31:12],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } axi2dvp_setting;

    /* 0x24 : axi2dvp_start_addr_by */
    union {
        struct {
            uint32_t cr_axi_addr_start_by : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } axi2dvp_start_addr_by;

    /* 0x28 : axi2dvp_burst_cnt */
    union {
        struct {
            uint32_t cr_axi_frame_bc : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } axi2dvp_burst_cnt;

    /* 0x2C : axi2dvp_status */
    union {
        struct {
            uint32_t st_axi_fifo_cnt_by    : 7; /* [ 6: 0],          r,        0x0 */
            uint32_t st_axi_drain_error_by : 1; /* [    7],          r,        0x0 */
            uint32_t st_axi_state_idle_by  : 1; /* [    8],          r,        0x0 */
            uint32_t st_axi_state_func_by  : 1; /* [    9],          r,        0x0 */
            uint32_t st_axi_state_flsh_by  : 1; /* [   10],          r,        0x0 */
            uint32_t reserved_11_15        : 5; /* [15:11],       rsvd,        0x0 */
            uint32_t st_axi_fifo_cnt_uv    : 7; /* [22:16],          r,        0x0 */
            uint32_t st_axi_drain_error_uv : 1; /* [   23],          r,        0x0 */
            uint32_t st_axi_state_idle_uv  : 1; /* [   24],          r,        0x0 */
            uint32_t st_axi_state_func_uv  : 1; /* [   25],          r,        0x0 */
            uint32_t st_axi_state_flsh_uv  : 1; /* [   26],          r,        0x0 */
            uint32_t reserved_27_31        : 5; /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } axi2dvp_status;

    /* 0x30 : axi2dvp_swap_addr_by */
    union {
        struct {
            uint32_t cr_axi_addr_swap_by : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } axi2dvp_swap_addr_by;

    /* 0x34 : axi2dvp_prefetch */
    union {
        struct {
            uint32_t cr_prefetch_v  : 12; /* [11: 0],        r/w,       0x28 */
            uint32_t reserved_12_31 : 20; /* [31:12],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } axi2dvp_prefetch;

    /* 0x38 : snsr2dvp_wait_pos */
    union {
        struct {
            uint32_t cr_snsr_fifo_th : 11; /* [10: 0],        r/w,       0x8b */
            uint32_t reserved_11_31  : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } snsr2dvp_wait_pos;

    /* 0x3c  reserved */
    uint8_t RESERVED0x3c[4];

    /* 0x40 : axi2dvp_start_addr_uv */
    union {
        struct {
            uint32_t cr_axi_addr_start_uv : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } axi2dvp_start_addr_uv;

    /* 0x44 : axi2dvp_swap_addr_uv */
    union {
        struct {
            uint32_t cr_axi_addr_swap_uv : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } axi2dvp_swap_addr_uv;
};

typedef volatile struct dtsrc_reg dtsrc_reg_t;

#endif /* __DTSRC_REG_H__ */
