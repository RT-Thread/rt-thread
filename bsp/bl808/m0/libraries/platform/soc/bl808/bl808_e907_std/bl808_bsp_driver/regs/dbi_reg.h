/**
  ******************************************************************************
  * @file    dbi_reg.h
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
#ifndef __DBI_REG_H__
#define __DBI_REG_H__

#include "bl808.h"

/* 0x0 : dbi_config */
#define DBI_CONFIG_OFFSET          (0x0)
#define DBI_CR_DBI_EN              DBI_CR_DBI_EN
#define DBI_CR_DBI_EN_POS          (0U)
#define DBI_CR_DBI_EN_LEN          (1U)
#define DBI_CR_DBI_EN_MSK          (((1U << DBI_CR_DBI_EN_LEN) - 1) << DBI_CR_DBI_EN_POS)
#define DBI_CR_DBI_EN_UMSK         (~(((1U << DBI_CR_DBI_EN_LEN) - 1) << DBI_CR_DBI_EN_POS))
#define DBI_CR_DBI_SEL             DBI_CR_DBI_SEL
#define DBI_CR_DBI_SEL_POS         (1U)
#define DBI_CR_DBI_SEL_LEN         (1U)
#define DBI_CR_DBI_SEL_MSK         (((1U << DBI_CR_DBI_SEL_LEN) - 1) << DBI_CR_DBI_SEL_POS)
#define DBI_CR_DBI_SEL_UMSK        (~(((1U << DBI_CR_DBI_SEL_LEN) - 1) << DBI_CR_DBI_SEL_POS))
#define DBI_CR_DBI_CMD_EN          DBI_CR_DBI_CMD_EN
#define DBI_CR_DBI_CMD_EN_POS      (2U)
#define DBI_CR_DBI_CMD_EN_LEN      (1U)
#define DBI_CR_DBI_CMD_EN_MSK      (((1U << DBI_CR_DBI_CMD_EN_LEN) - 1) << DBI_CR_DBI_CMD_EN_POS)
#define DBI_CR_DBI_CMD_EN_UMSK     (~(((1U << DBI_CR_DBI_CMD_EN_LEN) - 1) << DBI_CR_DBI_CMD_EN_POS))
#define DBI_CR_DBI_DAT_EN          DBI_CR_DBI_DAT_EN
#define DBI_CR_DBI_DAT_EN_POS      (3U)
#define DBI_CR_DBI_DAT_EN_LEN      (1U)
#define DBI_CR_DBI_DAT_EN_MSK      (((1U << DBI_CR_DBI_DAT_EN_LEN) - 1) << DBI_CR_DBI_DAT_EN_POS)
#define DBI_CR_DBI_DAT_EN_UMSK     (~(((1U << DBI_CR_DBI_DAT_EN_LEN) - 1) << DBI_CR_DBI_DAT_EN_POS))
#define DBI_CR_DBI_DAT_WR          DBI_CR_DBI_DAT_WR
#define DBI_CR_DBI_DAT_WR_POS      (4U)
#define DBI_CR_DBI_DAT_WR_LEN      (1U)
#define DBI_CR_DBI_DAT_WR_MSK      (((1U << DBI_CR_DBI_DAT_WR_LEN) - 1) << DBI_CR_DBI_DAT_WR_POS)
#define DBI_CR_DBI_DAT_WR_UMSK     (~(((1U << DBI_CR_DBI_DAT_WR_LEN) - 1) << DBI_CR_DBI_DAT_WR_POS))
#define DBI_CR_DBI_DAT_TP          DBI_CR_DBI_DAT_TP
#define DBI_CR_DBI_DAT_TP_POS      (5U)
#define DBI_CR_DBI_DAT_TP_LEN      (1U)
#define DBI_CR_DBI_DAT_TP_MSK      (((1U << DBI_CR_DBI_DAT_TP_LEN) - 1) << DBI_CR_DBI_DAT_TP_POS)
#define DBI_CR_DBI_DAT_TP_UMSK     (~(((1U << DBI_CR_DBI_DAT_TP_LEN) - 1) << DBI_CR_DBI_DAT_TP_POS))
#define DBI_CR_DBI_DAT_BC          DBI_CR_DBI_DAT_BC
#define DBI_CR_DBI_DAT_BC_POS      (6U)
#define DBI_CR_DBI_DAT_BC_LEN      (2U)
#define DBI_CR_DBI_DAT_BC_MSK      (((1U << DBI_CR_DBI_DAT_BC_LEN) - 1) << DBI_CR_DBI_DAT_BC_POS)
#define DBI_CR_DBI_DAT_BC_UMSK     (~(((1U << DBI_CR_DBI_DAT_BC_LEN) - 1) << DBI_CR_DBI_DAT_BC_POS))
#define DBI_CR_DBI_CMD             DBI_CR_DBI_CMD
#define DBI_CR_DBI_CMD_POS         (8U)
#define DBI_CR_DBI_CMD_LEN         (8U)
#define DBI_CR_DBI_CMD_MSK         (((1U << DBI_CR_DBI_CMD_LEN) - 1) << DBI_CR_DBI_CMD_POS)
#define DBI_CR_DBI_CMD_UMSK        (~(((1U << DBI_CR_DBI_CMD_LEN) - 1) << DBI_CR_DBI_CMD_POS))
#define DBI_CR_DBI_SCL_POL         DBI_CR_DBI_SCL_POL
#define DBI_CR_DBI_SCL_POL_POS     (16U)
#define DBI_CR_DBI_SCL_POL_LEN     (1U)
#define DBI_CR_DBI_SCL_POL_MSK     (((1U << DBI_CR_DBI_SCL_POL_LEN) - 1) << DBI_CR_DBI_SCL_POL_POS)
#define DBI_CR_DBI_SCL_POL_UMSK    (~(((1U << DBI_CR_DBI_SCL_POL_LEN) - 1) << DBI_CR_DBI_SCL_POL_POS))
#define DBI_CR_DBI_SCL_PH          DBI_CR_DBI_SCL_PH
#define DBI_CR_DBI_SCL_PH_POS      (17U)
#define DBI_CR_DBI_SCL_PH_LEN      (1U)
#define DBI_CR_DBI_SCL_PH_MSK      (((1U << DBI_CR_DBI_SCL_PH_LEN) - 1) << DBI_CR_DBI_SCL_PH_POS)
#define DBI_CR_DBI_SCL_PH_UMSK     (~(((1U << DBI_CR_DBI_SCL_PH_LEN) - 1) << DBI_CR_DBI_SCL_PH_POS))
#define DBI_CR_DBI_CONT_EN         DBI_CR_DBI_CONT_EN
#define DBI_CR_DBI_CONT_EN_POS     (18U)
#define DBI_CR_DBI_CONT_EN_LEN     (1U)
#define DBI_CR_DBI_CONT_EN_MSK     (((1U << DBI_CR_DBI_CONT_EN_LEN) - 1) << DBI_CR_DBI_CONT_EN_POS)
#define DBI_CR_DBI_CONT_EN_UMSK    (~(((1U << DBI_CR_DBI_CONT_EN_LEN) - 1) << DBI_CR_DBI_CONT_EN_POS))
#define DBI_CR_DBI_DMY_EN          DBI_CR_DBI_DMY_EN
#define DBI_CR_DBI_DMY_EN_POS      (19U)
#define DBI_CR_DBI_DMY_EN_LEN      (1U)
#define DBI_CR_DBI_DMY_EN_MSK      (((1U << DBI_CR_DBI_DMY_EN_LEN) - 1) << DBI_CR_DBI_DMY_EN_POS)
#define DBI_CR_DBI_DMY_EN_UMSK     (~(((1U << DBI_CR_DBI_DMY_EN_LEN) - 1) << DBI_CR_DBI_DMY_EN_POS))
#define DBI_CR_DBI_DMY_CNT         DBI_CR_DBI_DMY_CNT
#define DBI_CR_DBI_DMY_CNT_POS     (20U)
#define DBI_CR_DBI_DMY_CNT_LEN     (4U)
#define DBI_CR_DBI_DMY_CNT_MSK     (((1U << DBI_CR_DBI_DMY_CNT_LEN) - 1) << DBI_CR_DBI_DMY_CNT_POS)
#define DBI_CR_DBI_DMY_CNT_UMSK    (~(((1U << DBI_CR_DBI_DMY_CNT_LEN) - 1) << DBI_CR_DBI_DMY_CNT_POS))
#define DBI_CR_DBI_TC_3W_MODE      DBI_CR_DBI_TC_3W_MODE
#define DBI_CR_DBI_TC_3W_MODE_POS  (27U)
#define DBI_CR_DBI_TC_3W_MODE_LEN  (1U)
#define DBI_CR_DBI_TC_3W_MODE_MSK  (((1U << DBI_CR_DBI_TC_3W_MODE_LEN) - 1) << DBI_CR_DBI_TC_3W_MODE_POS)
#define DBI_CR_DBI_TC_3W_MODE_UMSK (~(((1U << DBI_CR_DBI_TC_3W_MODE_LEN) - 1) << DBI_CR_DBI_TC_3W_MODE_POS))
#define DBI_CR_DBI_TC_DEG_EN       DBI_CR_DBI_TC_DEG_EN
#define DBI_CR_DBI_TC_DEG_EN_POS   (28U)
#define DBI_CR_DBI_TC_DEG_EN_LEN   (1U)
#define DBI_CR_DBI_TC_DEG_EN_MSK   (((1U << DBI_CR_DBI_TC_DEG_EN_LEN) - 1) << DBI_CR_DBI_TC_DEG_EN_POS)
#define DBI_CR_DBI_TC_DEG_EN_UMSK  (~(((1U << DBI_CR_DBI_TC_DEG_EN_LEN) - 1) << DBI_CR_DBI_TC_DEG_EN_POS))
#define DBI_CR_DBI_TC_DEG_CNT      DBI_CR_DBI_TC_DEG_CNT
#define DBI_CR_DBI_TC_DEG_CNT_POS  (29U)
#define DBI_CR_DBI_TC_DEG_CNT_LEN  (3U)
#define DBI_CR_DBI_TC_DEG_CNT_MSK  (((1U << DBI_CR_DBI_TC_DEG_CNT_LEN) - 1) << DBI_CR_DBI_TC_DEG_CNT_POS)
#define DBI_CR_DBI_TC_DEG_CNT_UMSK (~(((1U << DBI_CR_DBI_TC_DEG_CNT_LEN) - 1) << DBI_CR_DBI_TC_DEG_CNT_POS))

/* 0x4 : dbi_int_sts */
#define DBI_INT_STS_OFFSET       (0x4)
#define DBI_END_INT              DBI_END_INT
#define DBI_END_INT_POS          (0U)
#define DBI_END_INT_LEN          (1U)
#define DBI_END_INT_MSK          (((1U << DBI_END_INT_LEN) - 1) << DBI_END_INT_POS)
#define DBI_END_INT_UMSK         (~(((1U << DBI_END_INT_LEN) - 1) << DBI_END_INT_POS))
#define DBI_TXF_INT              DBI_TXF_INT
#define DBI_TXF_INT_POS          (1U)
#define DBI_TXF_INT_LEN          (1U)
#define DBI_TXF_INT_MSK          (((1U << DBI_TXF_INT_LEN) - 1) << DBI_TXF_INT_POS)
#define DBI_TXF_INT_UMSK         (~(((1U << DBI_TXF_INT_LEN) - 1) << DBI_TXF_INT_POS))
#define DBI_FER_INT              DBI_FER_INT
#define DBI_FER_INT_POS          (2U)
#define DBI_FER_INT_LEN          (1U)
#define DBI_FER_INT_MSK          (((1U << DBI_FER_INT_LEN) - 1) << DBI_FER_INT_POS)
#define DBI_FER_INT_UMSK         (~(((1U << DBI_FER_INT_LEN) - 1) << DBI_FER_INT_POS))
#define DBI_CR_DBI_END_MASK      DBI_CR_DBI_END_MASK
#define DBI_CR_DBI_END_MASK_POS  (8U)
#define DBI_CR_DBI_END_MASK_LEN  (1U)
#define DBI_CR_DBI_END_MASK_MSK  (((1U << DBI_CR_DBI_END_MASK_LEN) - 1) << DBI_CR_DBI_END_MASK_POS)
#define DBI_CR_DBI_END_MASK_UMSK (~(((1U << DBI_CR_DBI_END_MASK_LEN) - 1) << DBI_CR_DBI_END_MASK_POS))
#define DBI_CR_DBI_TXF_MASK      DBI_CR_DBI_TXF_MASK
#define DBI_CR_DBI_TXF_MASK_POS  (9U)
#define DBI_CR_DBI_TXF_MASK_LEN  (1U)
#define DBI_CR_DBI_TXF_MASK_MSK  (((1U << DBI_CR_DBI_TXF_MASK_LEN) - 1) << DBI_CR_DBI_TXF_MASK_POS)
#define DBI_CR_DBI_TXF_MASK_UMSK (~(((1U << DBI_CR_DBI_TXF_MASK_LEN) - 1) << DBI_CR_DBI_TXF_MASK_POS))
#define DBI_CR_DBI_FER_MASK      DBI_CR_DBI_FER_MASK
#define DBI_CR_DBI_FER_MASK_POS  (10U)
#define DBI_CR_DBI_FER_MASK_LEN  (1U)
#define DBI_CR_DBI_FER_MASK_MSK  (((1U << DBI_CR_DBI_FER_MASK_LEN) - 1) << DBI_CR_DBI_FER_MASK_POS)
#define DBI_CR_DBI_FER_MASK_UMSK (~(((1U << DBI_CR_DBI_FER_MASK_LEN) - 1) << DBI_CR_DBI_FER_MASK_POS))
#define DBI_CR_DBI_END_CLR       DBI_CR_DBI_END_CLR
#define DBI_CR_DBI_END_CLR_POS   (16U)
#define DBI_CR_DBI_END_CLR_LEN   (1U)
#define DBI_CR_DBI_END_CLR_MSK   (((1U << DBI_CR_DBI_END_CLR_LEN) - 1) << DBI_CR_DBI_END_CLR_POS)
#define DBI_CR_DBI_END_CLR_UMSK  (~(((1U << DBI_CR_DBI_END_CLR_LEN) - 1) << DBI_CR_DBI_END_CLR_POS))
#define DBI_CR_DBI_END_EN        DBI_CR_DBI_END_EN
#define DBI_CR_DBI_END_EN_POS    (24U)
#define DBI_CR_DBI_END_EN_LEN    (1U)
#define DBI_CR_DBI_END_EN_MSK    (((1U << DBI_CR_DBI_END_EN_LEN) - 1) << DBI_CR_DBI_END_EN_POS)
#define DBI_CR_DBI_END_EN_UMSK   (~(((1U << DBI_CR_DBI_END_EN_LEN) - 1) << DBI_CR_DBI_END_EN_POS))
#define DBI_CR_DBI_TXF_EN        DBI_CR_DBI_TXF_EN
#define DBI_CR_DBI_TXF_EN_POS    (25U)
#define DBI_CR_DBI_TXF_EN_LEN    (1U)
#define DBI_CR_DBI_TXF_EN_MSK    (((1U << DBI_CR_DBI_TXF_EN_LEN) - 1) << DBI_CR_DBI_TXF_EN_POS)
#define DBI_CR_DBI_TXF_EN_UMSK   (~(((1U << DBI_CR_DBI_TXF_EN_LEN) - 1) << DBI_CR_DBI_TXF_EN_POS))
#define DBI_CR_DBI_FER_EN        DBI_CR_DBI_FER_EN
#define DBI_CR_DBI_FER_EN_POS    (26U)
#define DBI_CR_DBI_FER_EN_LEN    (1U)
#define DBI_CR_DBI_FER_EN_MSK    (((1U << DBI_CR_DBI_FER_EN_LEN) - 1) << DBI_CR_DBI_FER_EN_POS)
#define DBI_CR_DBI_FER_EN_UMSK   (~(((1U << DBI_CR_DBI_FER_EN_LEN) - 1) << DBI_CR_DBI_FER_EN_POS))

/* 0x8 : dbi_bus_busy */
#define DBI_BUS_BUSY_OFFSET       (0x8)
#define DBI_STS_DBI_BUS_BUSY      DBI_STS_DBI_BUS_BUSY
#define DBI_STS_DBI_BUS_BUSY_POS  (0U)
#define DBI_STS_DBI_BUS_BUSY_LEN  (1U)
#define DBI_STS_DBI_BUS_BUSY_MSK  (((1U << DBI_STS_DBI_BUS_BUSY_LEN) - 1) << DBI_STS_DBI_BUS_BUSY_POS)
#define DBI_STS_DBI_BUS_BUSY_UMSK (~(((1U << DBI_STS_DBI_BUS_BUSY_LEN) - 1) << DBI_STS_DBI_BUS_BUSY_POS))

/* 0xC : dbi_pix_cnt */
#define DBI_PIX_CNT_OFFSET         (0xC)
#define DBI_CR_DBI_PIX_CNT         DBI_CR_DBI_PIX_CNT
#define DBI_CR_DBI_PIX_CNT_POS     (0U)
#define DBI_CR_DBI_PIX_CNT_LEN     (24U)
#define DBI_CR_DBI_PIX_CNT_MSK     (((1U << DBI_CR_DBI_PIX_CNT_LEN) - 1) << DBI_CR_DBI_PIX_CNT_POS)
#define DBI_CR_DBI_PIX_CNT_UMSK    (~(((1U << DBI_CR_DBI_PIX_CNT_LEN) - 1) << DBI_CR_DBI_PIX_CNT_POS))
#define DBI_CR_DBI_PIX_FORMAT      DBI_CR_DBI_PIX_FORMAT
#define DBI_CR_DBI_PIX_FORMAT_POS  (31U)
#define DBI_CR_DBI_PIX_FORMAT_LEN  (1U)
#define DBI_CR_DBI_PIX_FORMAT_MSK  (((1U << DBI_CR_DBI_PIX_FORMAT_LEN) - 1) << DBI_CR_DBI_PIX_FORMAT_POS)
#define DBI_CR_DBI_PIX_FORMAT_UMSK (~(((1U << DBI_CR_DBI_PIX_FORMAT_LEN) - 1) << DBI_CR_DBI_PIX_FORMAT_POS))

/* 0x10 : dbi_prd */
#define DBI_PRD_OFFSET             (0x10)
#define DBI_CR_DBI_PRD_S           DBI_CR_DBI_PRD_S
#define DBI_CR_DBI_PRD_S_POS       (0U)
#define DBI_CR_DBI_PRD_S_LEN       (8U)
#define DBI_CR_DBI_PRD_S_MSK       (((1U << DBI_CR_DBI_PRD_S_LEN) - 1) << DBI_CR_DBI_PRD_S_POS)
#define DBI_CR_DBI_PRD_S_UMSK      (~(((1U << DBI_CR_DBI_PRD_S_LEN) - 1) << DBI_CR_DBI_PRD_S_POS))
#define DBI_CR_DBI_PRD_I           DBI_CR_DBI_PRD_I
#define DBI_CR_DBI_PRD_I_POS       (8U)
#define DBI_CR_DBI_PRD_I_LEN       (8U)
#define DBI_CR_DBI_PRD_I_MSK       (((1U << DBI_CR_DBI_PRD_I_LEN) - 1) << DBI_CR_DBI_PRD_I_POS)
#define DBI_CR_DBI_PRD_I_UMSK      (~(((1U << DBI_CR_DBI_PRD_I_LEN) - 1) << DBI_CR_DBI_PRD_I_POS))
#define DBI_CR_DBI_PRD_D_PH_0      DBI_CR_DBI_PRD_D_PH_0
#define DBI_CR_DBI_PRD_D_PH_0_POS  (16U)
#define DBI_CR_DBI_PRD_D_PH_0_LEN  (8U)
#define DBI_CR_DBI_PRD_D_PH_0_MSK  (((1U << DBI_CR_DBI_PRD_D_PH_0_LEN) - 1) << DBI_CR_DBI_PRD_D_PH_0_POS)
#define DBI_CR_DBI_PRD_D_PH_0_UMSK (~(((1U << DBI_CR_DBI_PRD_D_PH_0_LEN) - 1) << DBI_CR_DBI_PRD_D_PH_0_POS))
#define DBI_CR_DBI_PRD_D_PH_1      DBI_CR_DBI_PRD_D_PH_1
#define DBI_CR_DBI_PRD_D_PH_1_POS  (24U)
#define DBI_CR_DBI_PRD_D_PH_1_LEN  (8U)
#define DBI_CR_DBI_PRD_D_PH_1_MSK  (((1U << DBI_CR_DBI_PRD_D_PH_1_LEN) - 1) << DBI_CR_DBI_PRD_D_PH_1_POS)
#define DBI_CR_DBI_PRD_D_PH_1_UMSK (~(((1U << DBI_CR_DBI_PRD_D_PH_1_LEN) - 1) << DBI_CR_DBI_PRD_D_PH_1_POS))

/* 0x18 : dbi_wdata */
#define DBI_WDATA_OFFSET      (0x18)
#define DBI_CR_DBI_WDATA      DBI_CR_DBI_WDATA
#define DBI_CR_DBI_WDATA_POS  (0U)
#define DBI_CR_DBI_WDATA_LEN  (32U)
#define DBI_CR_DBI_WDATA_MSK  (((1U << DBI_CR_DBI_WDATA_LEN) - 1) << DBI_CR_DBI_WDATA_POS)
#define DBI_CR_DBI_WDATA_UMSK (~(((1U << DBI_CR_DBI_WDATA_LEN) - 1) << DBI_CR_DBI_WDATA_POS))

/* 0x1C : dbi_rdata */
#define DBI_RDATA_OFFSET       (0x1C)
#define DBI_STS_DBI_RDATA      DBI_STS_DBI_RDATA
#define DBI_STS_DBI_RDATA_POS  (0U)
#define DBI_STS_DBI_RDATA_LEN  (32U)
#define DBI_STS_DBI_RDATA_MSK  (((1U << DBI_STS_DBI_RDATA_LEN) - 1) << DBI_STS_DBI_RDATA_POS)
#define DBI_STS_DBI_RDATA_UMSK (~(((1U << DBI_STS_DBI_RDATA_LEN) - 1) << DBI_STS_DBI_RDATA_POS))

/* 0x80 : dbi_fifo_config_0 */
#define DBI_FIFO_CONFIG_0_OFFSET   (0x80)
#define DBI_DMA_TX_EN              DBI_DMA_TX_EN
#define DBI_DMA_TX_EN_POS          (0U)
#define DBI_DMA_TX_EN_LEN          (1U)
#define DBI_DMA_TX_EN_MSK          (((1U << DBI_DMA_TX_EN_LEN) - 1) << DBI_DMA_TX_EN_POS)
#define DBI_DMA_TX_EN_UMSK         (~(((1U << DBI_DMA_TX_EN_LEN) - 1) << DBI_DMA_TX_EN_POS))
#define DBI_TX_FIFO_CLR            DBI_TX_FIFO_CLR
#define DBI_TX_FIFO_CLR_POS        (2U)
#define DBI_TX_FIFO_CLR_LEN        (1U)
#define DBI_TX_FIFO_CLR_MSK        (((1U << DBI_TX_FIFO_CLR_LEN) - 1) << DBI_TX_FIFO_CLR_POS)
#define DBI_TX_FIFO_CLR_UMSK       (~(((1U << DBI_TX_FIFO_CLR_LEN) - 1) << DBI_TX_FIFO_CLR_POS))
#define DBI_TX_FIFO_OVERFLOW       DBI_TX_FIFO_OVERFLOW
#define DBI_TX_FIFO_OVERFLOW_POS   (4U)
#define DBI_TX_FIFO_OVERFLOW_LEN   (1U)
#define DBI_TX_FIFO_OVERFLOW_MSK   (((1U << DBI_TX_FIFO_OVERFLOW_LEN) - 1) << DBI_TX_FIFO_OVERFLOW_POS)
#define DBI_TX_FIFO_OVERFLOW_UMSK  (~(((1U << DBI_TX_FIFO_OVERFLOW_LEN) - 1) << DBI_TX_FIFO_OVERFLOW_POS))
#define DBI_TX_FIFO_UNDERFLOW      DBI_TX_FIFO_UNDERFLOW
#define DBI_TX_FIFO_UNDERFLOW_POS  (5U)
#define DBI_TX_FIFO_UNDERFLOW_LEN  (1U)
#define DBI_TX_FIFO_UNDERFLOW_MSK  (((1U << DBI_TX_FIFO_UNDERFLOW_LEN) - 1) << DBI_TX_FIFO_UNDERFLOW_POS)
#define DBI_TX_FIFO_UNDERFLOW_UMSK (~(((1U << DBI_TX_FIFO_UNDERFLOW_LEN) - 1) << DBI_TX_FIFO_UNDERFLOW_POS))
#define DBI_FIFO_FORMAT            DBI_FIFO_FORMAT
#define DBI_FIFO_FORMAT_POS        (29U)
#define DBI_FIFO_FORMAT_LEN        (3U)
#define DBI_FIFO_FORMAT_MSK        (((1U << DBI_FIFO_FORMAT_LEN) - 1) << DBI_FIFO_FORMAT_POS)
#define DBI_FIFO_FORMAT_UMSK       (~(((1U << DBI_FIFO_FORMAT_LEN) - 1) << DBI_FIFO_FORMAT_POS))

/* 0x84 : dbi_fifo_config_1 */
#define DBI_FIFO_CONFIG_1_OFFSET (0x84)
#define DBI_TX_FIFO_CNT          DBI_TX_FIFO_CNT
#define DBI_TX_FIFO_CNT_POS      (0U)
#define DBI_TX_FIFO_CNT_LEN      (4U)
#define DBI_TX_FIFO_CNT_MSK      (((1U << DBI_TX_FIFO_CNT_LEN) - 1) << DBI_TX_FIFO_CNT_POS)
#define DBI_TX_FIFO_CNT_UMSK     (~(((1U << DBI_TX_FIFO_CNT_LEN) - 1) << DBI_TX_FIFO_CNT_POS))
#define DBI_TX_FIFO_TH           DBI_TX_FIFO_TH
#define DBI_TX_FIFO_TH_POS       (16U)
#define DBI_TX_FIFO_TH_LEN       (3U)
#define DBI_TX_FIFO_TH_MSK       (((1U << DBI_TX_FIFO_TH_LEN) - 1) << DBI_TX_FIFO_TH_POS)
#define DBI_TX_FIFO_TH_UMSK      (~(((1U << DBI_TX_FIFO_TH_LEN) - 1) << DBI_TX_FIFO_TH_POS))

/* 0x88 : dbi_fifo_wdata */
#define DBI_FIFO_WDATA_OFFSET (0x88)
#define DBI_FIFO_WDATA        DBI_FIFO_WDATA
#define DBI_FIFO_WDATA_POS    (0U)
#define DBI_FIFO_WDATA_LEN    (32U)
#define DBI_FIFO_WDATA_MSK    (((1U << DBI_FIFO_WDATA_LEN) - 1) << DBI_FIFO_WDATA_POS)
#define DBI_FIFO_WDATA_UMSK   (~(((1U << DBI_FIFO_WDATA_LEN) - 1) << DBI_FIFO_WDATA_POS))

struct dbi_reg {
    /* 0x0 : dbi_config */
    union {
        struct {
            uint32_t cr_dbi_en         : 1; /* [    0],        r/w,        0x0 */
            uint32_t cr_dbi_sel        : 1; /* [    1],        r/w,        0x0 */
            uint32_t cr_dbi_cmd_en     : 1; /* [    2],        r/w,        0x1 */
            uint32_t cr_dbi_dat_en     : 1; /* [    3],        r/w,        0x1 */
            uint32_t cr_dbi_dat_wr     : 1; /* [    4],        r/w,        0x1 */
            uint32_t cr_dbi_dat_tp     : 1; /* [    5],        r/w,        0x0 */
            uint32_t cr_dbi_dat_bc     : 2; /* [ 7: 6],        r/w,        0x0 */
            uint32_t cr_dbi_cmd        : 8; /* [15: 8],        r/w,       0x2c */
            uint32_t cr_dbi_scl_pol    : 1; /* [   16],        r/w,        0x1 */
            uint32_t cr_dbi_scl_ph     : 1; /* [   17],        r/w,        0x0 */
            uint32_t cr_dbi_cont_en    : 1; /* [   18],        r/w,        0x1 */
            uint32_t cr_dbi_dmy_en     : 1; /* [   19],        r/w,        0x0 */
            uint32_t cr_dbi_dmy_cnt    : 4; /* [23:20],        r/w,        0x0 */
            uint32_t rsvd_26_24        : 3; /* [26:24],       rsvd,        0x0 */
            uint32_t cr_dbi_tc_3w_mode : 1; /* [   27],        r/w,        0x0 */
            uint32_t cr_dbi_tc_deg_en  : 1; /* [   28],        r/w,        0x0 */
            uint32_t cr_dbi_tc_deg_cnt : 3; /* [31:29],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } dbi_config;

    /* 0x4 : dbi_int_sts */
    union {
        struct {
            uint32_t dbi_end_int     : 1; /* [    0],          r,        0x0 */
            uint32_t dbi_txf_int     : 1; /* [    1],          r,        0x1 */
            uint32_t dbi_fer_int     : 1; /* [    2],          r,        0x0 */
            uint32_t reserved_3_7    : 5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t cr_dbi_end_mask : 1; /* [    8],        r/w,        0x1 */
            uint32_t cr_dbi_txf_mask : 1; /* [    9],        r/w,        0x1 */
            uint32_t cr_dbi_fer_mask : 1; /* [   10],        r/w,        0x1 */
            uint32_t reserved_11_15  : 5; /* [15:11],       rsvd,        0x0 */
            uint32_t cr_dbi_end_clr  : 1; /* [   16],        w1c,        0x0 */
            uint32_t rsvd_17         : 1; /* [   17],       rsvd,        0x0 */
            uint32_t rsvd_18         : 1; /* [   18],       rsvd,        0x0 */
            uint32_t reserved_19_23  : 5; /* [23:19],       rsvd,        0x0 */
            uint32_t cr_dbi_end_en   : 1; /* [   24],        r/w,        0x1 */
            uint32_t cr_dbi_txf_en   : 1; /* [   25],        r/w,        0x1 */
            uint32_t cr_dbi_fer_en   : 1; /* [   26],        r/w,        0x1 */
            uint32_t reserved_27_31  : 5; /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } dbi_int_sts;

    /* 0x8 : dbi_bus_busy */
    union {
        struct {
            uint32_t sts_dbi_bus_busy : 1;  /* [    0],          r,        0x0 */
            uint32_t reserved_1_31    : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } dbi_bus_busy;

    /* 0xC : dbi_pix_cnt */
    union {
        struct {
            uint32_t cr_dbi_pix_cnt    : 24; /* [23: 0],        r/w,        0x0 */
            uint32_t reserved_24_30    : 7;  /* [30:24],       rsvd,        0x0 */
            uint32_t cr_dbi_pix_format : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } dbi_pix_cnt;

    /* 0x10 : dbi_prd */
    union {
        struct {
            uint32_t cr_dbi_prd_s      : 8; /* [ 7: 0],        r/w,        0xf */
            uint32_t cr_dbi_prd_i      : 8; /* [15: 8],        r/w,        0xf */
            uint32_t cr_dbi_prd_d_ph_0 : 8; /* [23:16],        r/w,        0xf */
            uint32_t cr_dbi_prd_d_ph_1 : 8; /* [31:24],        r/w,        0xf */
        } BF;
        uint32_t WORD;
    } dbi_prd;

    /* 0x14  reserved */
    uint8_t RESERVED0x14[4];

    /* 0x18 : dbi_wdata */
    union {
        struct {
            uint32_t cr_dbi_wdata : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } dbi_wdata;

    /* 0x1C : dbi_rdata */
    union {
        struct {
            uint32_t sts_dbi_rdata : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } dbi_rdata;

    /* 0x20  reserved */
    uint8_t RESERVED0x20[96];

    /* 0x80 : dbi_fifo_config_0 */
    union {
        struct {
            uint32_t dbi_dma_tx_en     : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1        : 1;  /* [    1],       rsvd,        0x0 */
            uint32_t tx_fifo_clr       : 1;  /* [    2],        w1c,        0x0 */
            uint32_t reserved_3        : 1;  /* [    3],       rsvd,        0x0 */
            uint32_t tx_fifo_overflow  : 1;  /* [    4],          r,        0x0 */
            uint32_t tx_fifo_underflow : 1;  /* [    5],          r,        0x0 */
            uint32_t reserved_6_28     : 23; /* [28: 6],       rsvd,        0x0 */
            uint32_t fifo_format       : 3;  /* [31:29],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } dbi_fifo_config_0;

    /* 0x84 : dbi_fifo_config_1 */
    union {
        struct {
            uint32_t tx_fifo_cnt    : 4;  /* [ 3: 0],          r,        0x8 */
            uint32_t reserved_4_15  : 12; /* [15: 4],       rsvd,        0x0 */
            uint32_t tx_fifo_th     : 3;  /* [18:16],        r/w,        0x0 */
            uint32_t reserved_19_31 : 13; /* [31:19],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } dbi_fifo_config_1;

    /* 0x88 : dbi_fifo_wdata */
    union {
        struct {
            uint32_t dbi_fifo_wdata : 32; /* [31: 0],          w,          x */
        } BF;
        uint32_t WORD;
    } dbi_fifo_wdata;
};

typedef volatile struct dbi_reg dbi_reg_t;

#endif /* __DBI_REG_H__ */
