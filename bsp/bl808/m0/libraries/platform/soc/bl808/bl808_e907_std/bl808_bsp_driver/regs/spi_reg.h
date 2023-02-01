/**
  ******************************************************************************
  * @file    spi_reg.h
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
#ifndef __SPI_REG_H__
#define __SPI_REG_H__

#include "bl808.h"

/* 0x0 : spi_config */
#define SPI_CONFIG_OFFSET           (0x0)
#define SPI_CR_SPI_M_EN             SPI_CR_SPI_M_EN
#define SPI_CR_SPI_M_EN_POS         (0U)
#define SPI_CR_SPI_M_EN_LEN         (1U)
#define SPI_CR_SPI_M_EN_MSK         (((1U << SPI_CR_SPI_M_EN_LEN) - 1) << SPI_CR_SPI_M_EN_POS)
#define SPI_CR_SPI_M_EN_UMSK        (~(((1U << SPI_CR_SPI_M_EN_LEN) - 1) << SPI_CR_SPI_M_EN_POS))
#define SPI_CR_SPI_S_EN             SPI_CR_SPI_S_EN
#define SPI_CR_SPI_S_EN_POS         (1U)
#define SPI_CR_SPI_S_EN_LEN         (1U)
#define SPI_CR_SPI_S_EN_MSK         (((1U << SPI_CR_SPI_S_EN_LEN) - 1) << SPI_CR_SPI_S_EN_POS)
#define SPI_CR_SPI_S_EN_UMSK        (~(((1U << SPI_CR_SPI_S_EN_LEN) - 1) << SPI_CR_SPI_S_EN_POS))
#define SPI_CR_SPI_FRAME_SIZE       SPI_CR_SPI_FRAME_SIZE
#define SPI_CR_SPI_FRAME_SIZE_POS   (2U)
#define SPI_CR_SPI_FRAME_SIZE_LEN   (2U)
#define SPI_CR_SPI_FRAME_SIZE_MSK   (((1U << SPI_CR_SPI_FRAME_SIZE_LEN) - 1) << SPI_CR_SPI_FRAME_SIZE_POS)
#define SPI_CR_SPI_FRAME_SIZE_UMSK  (~(((1U << SPI_CR_SPI_FRAME_SIZE_LEN) - 1) << SPI_CR_SPI_FRAME_SIZE_POS))
#define SPI_CR_SPI_SCLK_POL         SPI_CR_SPI_SCLK_POL
#define SPI_CR_SPI_SCLK_POL_POS     (4U)
#define SPI_CR_SPI_SCLK_POL_LEN     (1U)
#define SPI_CR_SPI_SCLK_POL_MSK     (((1U << SPI_CR_SPI_SCLK_POL_LEN) - 1) << SPI_CR_SPI_SCLK_POL_POS)
#define SPI_CR_SPI_SCLK_POL_UMSK    (~(((1U << SPI_CR_SPI_SCLK_POL_LEN) - 1) << SPI_CR_SPI_SCLK_POL_POS))
#define SPI_CR_SPI_SCLK_PH          SPI_CR_SPI_SCLK_PH
#define SPI_CR_SPI_SCLK_PH_POS      (5U)
#define SPI_CR_SPI_SCLK_PH_LEN      (1U)
#define SPI_CR_SPI_SCLK_PH_MSK      (((1U << SPI_CR_SPI_SCLK_PH_LEN) - 1) << SPI_CR_SPI_SCLK_PH_POS)
#define SPI_CR_SPI_SCLK_PH_UMSK     (~(((1U << SPI_CR_SPI_SCLK_PH_LEN) - 1) << SPI_CR_SPI_SCLK_PH_POS))
#define SPI_CR_SPI_BIT_INV          SPI_CR_SPI_BIT_INV
#define SPI_CR_SPI_BIT_INV_POS      (6U)
#define SPI_CR_SPI_BIT_INV_LEN      (1U)
#define SPI_CR_SPI_BIT_INV_MSK      (((1U << SPI_CR_SPI_BIT_INV_LEN) - 1) << SPI_CR_SPI_BIT_INV_POS)
#define SPI_CR_SPI_BIT_INV_UMSK     (~(((1U << SPI_CR_SPI_BIT_INV_LEN) - 1) << SPI_CR_SPI_BIT_INV_POS))
#define SPI_CR_SPI_BYTE_INV         SPI_CR_SPI_BYTE_INV
#define SPI_CR_SPI_BYTE_INV_POS     (7U)
#define SPI_CR_SPI_BYTE_INV_LEN     (1U)
#define SPI_CR_SPI_BYTE_INV_MSK     (((1U << SPI_CR_SPI_BYTE_INV_LEN) - 1) << SPI_CR_SPI_BYTE_INV_POS)
#define SPI_CR_SPI_BYTE_INV_UMSK    (~(((1U << SPI_CR_SPI_BYTE_INV_LEN) - 1) << SPI_CR_SPI_BYTE_INV_POS))
#define SPI_CR_SPI_RXD_IGNR_EN      SPI_CR_SPI_RXD_IGNR_EN
#define SPI_CR_SPI_RXD_IGNR_EN_POS  (8U)
#define SPI_CR_SPI_RXD_IGNR_EN_LEN  (1U)
#define SPI_CR_SPI_RXD_IGNR_EN_MSK  (((1U << SPI_CR_SPI_RXD_IGNR_EN_LEN) - 1) << SPI_CR_SPI_RXD_IGNR_EN_POS)
#define SPI_CR_SPI_RXD_IGNR_EN_UMSK (~(((1U << SPI_CR_SPI_RXD_IGNR_EN_LEN) - 1) << SPI_CR_SPI_RXD_IGNR_EN_POS))
#define SPI_CR_SPI_M_CONT_EN        SPI_CR_SPI_M_CONT_EN
#define SPI_CR_SPI_M_CONT_EN_POS    (9U)
#define SPI_CR_SPI_M_CONT_EN_LEN    (1U)
#define SPI_CR_SPI_M_CONT_EN_MSK    (((1U << SPI_CR_SPI_M_CONT_EN_LEN) - 1) << SPI_CR_SPI_M_CONT_EN_POS)
#define SPI_CR_SPI_M_CONT_EN_UMSK   (~(((1U << SPI_CR_SPI_M_CONT_EN_LEN) - 1) << SPI_CR_SPI_M_CONT_EN_POS))
#define SPI_CR_SPI_S_3PIN_MODE      SPI_CR_SPI_S_3PIN_MODE
#define SPI_CR_SPI_S_3PIN_MODE_POS  (10U)
#define SPI_CR_SPI_S_3PIN_MODE_LEN  (1U)
#define SPI_CR_SPI_S_3PIN_MODE_MSK  (((1U << SPI_CR_SPI_S_3PIN_MODE_LEN) - 1) << SPI_CR_SPI_S_3PIN_MODE_POS)
#define SPI_CR_SPI_S_3PIN_MODE_UMSK (~(((1U << SPI_CR_SPI_S_3PIN_MODE_LEN) - 1) << SPI_CR_SPI_S_3PIN_MODE_POS))
#define SPI_CR_SPI_DEG_EN           SPI_CR_SPI_DEG_EN
#define SPI_CR_SPI_DEG_EN_POS       (11U)
#define SPI_CR_SPI_DEG_EN_LEN       (1U)
#define SPI_CR_SPI_DEG_EN_MSK       (((1U << SPI_CR_SPI_DEG_EN_LEN) - 1) << SPI_CR_SPI_DEG_EN_POS)
#define SPI_CR_SPI_DEG_EN_UMSK      (~(((1U << SPI_CR_SPI_DEG_EN_LEN) - 1) << SPI_CR_SPI_DEG_EN_POS))
#define SPI_CR_SPI_DEG_CNT          SPI_CR_SPI_DEG_CNT
#define SPI_CR_SPI_DEG_CNT_POS      (12U)
#define SPI_CR_SPI_DEG_CNT_LEN      (4U)
#define SPI_CR_SPI_DEG_CNT_MSK      (((1U << SPI_CR_SPI_DEG_CNT_LEN) - 1) << SPI_CR_SPI_DEG_CNT_POS)
#define SPI_CR_SPI_DEG_CNT_UMSK     (~(((1U << SPI_CR_SPI_DEG_CNT_LEN) - 1) << SPI_CR_SPI_DEG_CNT_POS))

/* 0x4 : spi_int_sts */
#define SPI_INT_STS_OFFSET       (0x4)
#define SPI_END_INT              SPI_END_INT
#define SPI_END_INT_POS          (0U)
#define SPI_END_INT_LEN          (1U)
#define SPI_END_INT_MSK          (((1U << SPI_END_INT_LEN) - 1) << SPI_END_INT_POS)
#define SPI_END_INT_UMSK         (~(((1U << SPI_END_INT_LEN) - 1) << SPI_END_INT_POS))
#define SPI_TXF_INT              SPI_TXF_INT
#define SPI_TXF_INT_POS          (1U)
#define SPI_TXF_INT_LEN          (1U)
#define SPI_TXF_INT_MSK          (((1U << SPI_TXF_INT_LEN) - 1) << SPI_TXF_INT_POS)
#define SPI_TXF_INT_UMSK         (~(((1U << SPI_TXF_INT_LEN) - 1) << SPI_TXF_INT_POS))
#define SPI_RXF_INT              SPI_RXF_INT
#define SPI_RXF_INT_POS          (2U)
#define SPI_RXF_INT_LEN          (1U)
#define SPI_RXF_INT_MSK          (((1U << SPI_RXF_INT_LEN) - 1) << SPI_RXF_INT_POS)
#define SPI_RXF_INT_UMSK         (~(((1U << SPI_RXF_INT_LEN) - 1) << SPI_RXF_INT_POS))
#define SPI_STO_INT              SPI_STO_INT
#define SPI_STO_INT_POS          (3U)
#define SPI_STO_INT_LEN          (1U)
#define SPI_STO_INT_MSK          (((1U << SPI_STO_INT_LEN) - 1) << SPI_STO_INT_POS)
#define SPI_STO_INT_UMSK         (~(((1U << SPI_STO_INT_LEN) - 1) << SPI_STO_INT_POS))
#define SPI_TXU_INT              SPI_TXU_INT
#define SPI_TXU_INT_POS          (4U)
#define SPI_TXU_INT_LEN          (1U)
#define SPI_TXU_INT_MSK          (((1U << SPI_TXU_INT_LEN) - 1) << SPI_TXU_INT_POS)
#define SPI_TXU_INT_UMSK         (~(((1U << SPI_TXU_INT_LEN) - 1) << SPI_TXU_INT_POS))
#define SPI_FER_INT              SPI_FER_INT
#define SPI_FER_INT_POS          (5U)
#define SPI_FER_INT_LEN          (1U)
#define SPI_FER_INT_MSK          (((1U << SPI_FER_INT_LEN) - 1) << SPI_FER_INT_POS)
#define SPI_FER_INT_UMSK         (~(((1U << SPI_FER_INT_LEN) - 1) << SPI_FER_INT_POS))
#define SPI_CR_SPI_END_MASK      SPI_CR_SPI_END_MASK
#define SPI_CR_SPI_END_MASK_POS  (8U)
#define SPI_CR_SPI_END_MASK_LEN  (1U)
#define SPI_CR_SPI_END_MASK_MSK  (((1U << SPI_CR_SPI_END_MASK_LEN) - 1) << SPI_CR_SPI_END_MASK_POS)
#define SPI_CR_SPI_END_MASK_UMSK (~(((1U << SPI_CR_SPI_END_MASK_LEN) - 1) << SPI_CR_SPI_END_MASK_POS))
#define SPI_CR_SPI_TXF_MASK      SPI_CR_SPI_TXF_MASK
#define SPI_CR_SPI_TXF_MASK_POS  (9U)
#define SPI_CR_SPI_TXF_MASK_LEN  (1U)
#define SPI_CR_SPI_TXF_MASK_MSK  (((1U << SPI_CR_SPI_TXF_MASK_LEN) - 1) << SPI_CR_SPI_TXF_MASK_POS)
#define SPI_CR_SPI_TXF_MASK_UMSK (~(((1U << SPI_CR_SPI_TXF_MASK_LEN) - 1) << SPI_CR_SPI_TXF_MASK_POS))
#define SPI_CR_SPI_RXF_MASK      SPI_CR_SPI_RXF_MASK
#define SPI_CR_SPI_RXF_MASK_POS  (10U)
#define SPI_CR_SPI_RXF_MASK_LEN  (1U)
#define SPI_CR_SPI_RXF_MASK_MSK  (((1U << SPI_CR_SPI_RXF_MASK_LEN) - 1) << SPI_CR_SPI_RXF_MASK_POS)
#define SPI_CR_SPI_RXF_MASK_UMSK (~(((1U << SPI_CR_SPI_RXF_MASK_LEN) - 1) << SPI_CR_SPI_RXF_MASK_POS))
#define SPI_CR_SPI_STO_MASK      SPI_CR_SPI_STO_MASK
#define SPI_CR_SPI_STO_MASK_POS  (11U)
#define SPI_CR_SPI_STO_MASK_LEN  (1U)
#define SPI_CR_SPI_STO_MASK_MSK  (((1U << SPI_CR_SPI_STO_MASK_LEN) - 1) << SPI_CR_SPI_STO_MASK_POS)
#define SPI_CR_SPI_STO_MASK_UMSK (~(((1U << SPI_CR_SPI_STO_MASK_LEN) - 1) << SPI_CR_SPI_STO_MASK_POS))
#define SPI_CR_SPI_TXU_MASK      SPI_CR_SPI_TXU_MASK
#define SPI_CR_SPI_TXU_MASK_POS  (12U)
#define SPI_CR_SPI_TXU_MASK_LEN  (1U)
#define SPI_CR_SPI_TXU_MASK_MSK  (((1U << SPI_CR_SPI_TXU_MASK_LEN) - 1) << SPI_CR_SPI_TXU_MASK_POS)
#define SPI_CR_SPI_TXU_MASK_UMSK (~(((1U << SPI_CR_SPI_TXU_MASK_LEN) - 1) << SPI_CR_SPI_TXU_MASK_POS))
#define SPI_CR_SPI_FER_MASK      SPI_CR_SPI_FER_MASK
#define SPI_CR_SPI_FER_MASK_POS  (13U)
#define SPI_CR_SPI_FER_MASK_LEN  (1U)
#define SPI_CR_SPI_FER_MASK_MSK  (((1U << SPI_CR_SPI_FER_MASK_LEN) - 1) << SPI_CR_SPI_FER_MASK_POS)
#define SPI_CR_SPI_FER_MASK_UMSK (~(((1U << SPI_CR_SPI_FER_MASK_LEN) - 1) << SPI_CR_SPI_FER_MASK_POS))
#define SPI_CR_SPI_END_CLR       SPI_CR_SPI_END_CLR
#define SPI_CR_SPI_END_CLR_POS   (16U)
#define SPI_CR_SPI_END_CLR_LEN   (1U)
#define SPI_CR_SPI_END_CLR_MSK   (((1U << SPI_CR_SPI_END_CLR_LEN) - 1) << SPI_CR_SPI_END_CLR_POS)
#define SPI_CR_SPI_END_CLR_UMSK  (~(((1U << SPI_CR_SPI_END_CLR_LEN) - 1) << SPI_CR_SPI_END_CLR_POS))
#define SPI_CR_SPI_STO_CLR       SPI_CR_SPI_STO_CLR
#define SPI_CR_SPI_STO_CLR_POS   (19U)
#define SPI_CR_SPI_STO_CLR_LEN   (1U)
#define SPI_CR_SPI_STO_CLR_MSK   (((1U << SPI_CR_SPI_STO_CLR_LEN) - 1) << SPI_CR_SPI_STO_CLR_POS)
#define SPI_CR_SPI_STO_CLR_UMSK  (~(((1U << SPI_CR_SPI_STO_CLR_LEN) - 1) << SPI_CR_SPI_STO_CLR_POS))
#define SPI_CR_SPI_TXU_CLR       SPI_CR_SPI_TXU_CLR
#define SPI_CR_SPI_TXU_CLR_POS   (20U)
#define SPI_CR_SPI_TXU_CLR_LEN   (1U)
#define SPI_CR_SPI_TXU_CLR_MSK   (((1U << SPI_CR_SPI_TXU_CLR_LEN) - 1) << SPI_CR_SPI_TXU_CLR_POS)
#define SPI_CR_SPI_TXU_CLR_UMSK  (~(((1U << SPI_CR_SPI_TXU_CLR_LEN) - 1) << SPI_CR_SPI_TXU_CLR_POS))
#define SPI_CR_SPI_END_EN        SPI_CR_SPI_END_EN
#define SPI_CR_SPI_END_EN_POS    (24U)
#define SPI_CR_SPI_END_EN_LEN    (1U)
#define SPI_CR_SPI_END_EN_MSK    (((1U << SPI_CR_SPI_END_EN_LEN) - 1) << SPI_CR_SPI_END_EN_POS)
#define SPI_CR_SPI_END_EN_UMSK   (~(((1U << SPI_CR_SPI_END_EN_LEN) - 1) << SPI_CR_SPI_END_EN_POS))
#define SPI_CR_SPI_TXF_EN        SPI_CR_SPI_TXF_EN
#define SPI_CR_SPI_TXF_EN_POS    (25U)
#define SPI_CR_SPI_TXF_EN_LEN    (1U)
#define SPI_CR_SPI_TXF_EN_MSK    (((1U << SPI_CR_SPI_TXF_EN_LEN) - 1) << SPI_CR_SPI_TXF_EN_POS)
#define SPI_CR_SPI_TXF_EN_UMSK   (~(((1U << SPI_CR_SPI_TXF_EN_LEN) - 1) << SPI_CR_SPI_TXF_EN_POS))
#define SPI_CR_SPI_RXF_EN        SPI_CR_SPI_RXF_EN
#define SPI_CR_SPI_RXF_EN_POS    (26U)
#define SPI_CR_SPI_RXF_EN_LEN    (1U)
#define SPI_CR_SPI_RXF_EN_MSK    (((1U << SPI_CR_SPI_RXF_EN_LEN) - 1) << SPI_CR_SPI_RXF_EN_POS)
#define SPI_CR_SPI_RXF_EN_UMSK   (~(((1U << SPI_CR_SPI_RXF_EN_LEN) - 1) << SPI_CR_SPI_RXF_EN_POS))
#define SPI_CR_SPI_STO_EN        SPI_CR_SPI_STO_EN
#define SPI_CR_SPI_STO_EN_POS    (27U)
#define SPI_CR_SPI_STO_EN_LEN    (1U)
#define SPI_CR_SPI_STO_EN_MSK    (((1U << SPI_CR_SPI_STO_EN_LEN) - 1) << SPI_CR_SPI_STO_EN_POS)
#define SPI_CR_SPI_STO_EN_UMSK   (~(((1U << SPI_CR_SPI_STO_EN_LEN) - 1) << SPI_CR_SPI_STO_EN_POS))
#define SPI_CR_SPI_TXU_EN        SPI_CR_SPI_TXU_EN
#define SPI_CR_SPI_TXU_EN_POS    (28U)
#define SPI_CR_SPI_TXU_EN_LEN    (1U)
#define SPI_CR_SPI_TXU_EN_MSK    (((1U << SPI_CR_SPI_TXU_EN_LEN) - 1) << SPI_CR_SPI_TXU_EN_POS)
#define SPI_CR_SPI_TXU_EN_UMSK   (~(((1U << SPI_CR_SPI_TXU_EN_LEN) - 1) << SPI_CR_SPI_TXU_EN_POS))
#define SPI_CR_SPI_FER_EN        SPI_CR_SPI_FER_EN
#define SPI_CR_SPI_FER_EN_POS    (29U)
#define SPI_CR_SPI_FER_EN_LEN    (1U)
#define SPI_CR_SPI_FER_EN_MSK    (((1U << SPI_CR_SPI_FER_EN_LEN) - 1) << SPI_CR_SPI_FER_EN_POS)
#define SPI_CR_SPI_FER_EN_UMSK   (~(((1U << SPI_CR_SPI_FER_EN_LEN) - 1) << SPI_CR_SPI_FER_EN_POS))

/* 0x8 : spi_bus_busy */
#define SPI_BUS_BUSY_OFFSET       (0x8)
#define SPI_STS_SPI_BUS_BUSY      SPI_STS_SPI_BUS_BUSY
#define SPI_STS_SPI_BUS_BUSY_POS  (0U)
#define SPI_STS_SPI_BUS_BUSY_LEN  (1U)
#define SPI_STS_SPI_BUS_BUSY_MSK  (((1U << SPI_STS_SPI_BUS_BUSY_LEN) - 1) << SPI_STS_SPI_BUS_BUSY_POS)
#define SPI_STS_SPI_BUS_BUSY_UMSK (~(((1U << SPI_STS_SPI_BUS_BUSY_LEN) - 1) << SPI_STS_SPI_BUS_BUSY_POS))

/* 0x10 : spi_prd_0 */
#define SPI_PRD_0_OFFSET           (0x10)
#define SPI_CR_SPI_PRD_S           SPI_CR_SPI_PRD_S
#define SPI_CR_SPI_PRD_S_POS       (0U)
#define SPI_CR_SPI_PRD_S_LEN       (8U)
#define SPI_CR_SPI_PRD_S_MSK       (((1U << SPI_CR_SPI_PRD_S_LEN) - 1) << SPI_CR_SPI_PRD_S_POS)
#define SPI_CR_SPI_PRD_S_UMSK      (~(((1U << SPI_CR_SPI_PRD_S_LEN) - 1) << SPI_CR_SPI_PRD_S_POS))
#define SPI_CR_SPI_PRD_P           SPI_CR_SPI_PRD_P
#define SPI_CR_SPI_PRD_P_POS       (8U)
#define SPI_CR_SPI_PRD_P_LEN       (8U)
#define SPI_CR_SPI_PRD_P_MSK       (((1U << SPI_CR_SPI_PRD_P_LEN) - 1) << SPI_CR_SPI_PRD_P_POS)
#define SPI_CR_SPI_PRD_P_UMSK      (~(((1U << SPI_CR_SPI_PRD_P_LEN) - 1) << SPI_CR_SPI_PRD_P_POS))
#define SPI_CR_SPI_PRD_D_PH_0      SPI_CR_SPI_PRD_D_PH_0
#define SPI_CR_SPI_PRD_D_PH_0_POS  (16U)
#define SPI_CR_SPI_PRD_D_PH_0_LEN  (8U)
#define SPI_CR_SPI_PRD_D_PH_0_MSK  (((1U << SPI_CR_SPI_PRD_D_PH_0_LEN) - 1) << SPI_CR_SPI_PRD_D_PH_0_POS)
#define SPI_CR_SPI_PRD_D_PH_0_UMSK (~(((1U << SPI_CR_SPI_PRD_D_PH_0_LEN) - 1) << SPI_CR_SPI_PRD_D_PH_0_POS))
#define SPI_CR_SPI_PRD_D_PH_1      SPI_CR_SPI_PRD_D_PH_1
#define SPI_CR_SPI_PRD_D_PH_1_POS  (24U)
#define SPI_CR_SPI_PRD_D_PH_1_LEN  (8U)
#define SPI_CR_SPI_PRD_D_PH_1_MSK  (((1U << SPI_CR_SPI_PRD_D_PH_1_LEN) - 1) << SPI_CR_SPI_PRD_D_PH_1_POS)
#define SPI_CR_SPI_PRD_D_PH_1_UMSK (~(((1U << SPI_CR_SPI_PRD_D_PH_1_LEN) - 1) << SPI_CR_SPI_PRD_D_PH_1_POS))

/* 0x14 : spi_prd_1 */
#define SPI_PRD_1_OFFSET      (0x14)
#define SPI_CR_SPI_PRD_I      SPI_CR_SPI_PRD_I
#define SPI_CR_SPI_PRD_I_POS  (0U)
#define SPI_CR_SPI_PRD_I_LEN  (8U)
#define SPI_CR_SPI_PRD_I_MSK  (((1U << SPI_CR_SPI_PRD_I_LEN) - 1) << SPI_CR_SPI_PRD_I_POS)
#define SPI_CR_SPI_PRD_I_UMSK (~(((1U << SPI_CR_SPI_PRD_I_LEN) - 1) << SPI_CR_SPI_PRD_I_POS))

/* 0x18 : spi_rxd_ignr */
#define SPI_RXD_IGNR_OFFSET        (0x18)
#define SPI_CR_SPI_RXD_IGNR_P      SPI_CR_SPI_RXD_IGNR_P
#define SPI_CR_SPI_RXD_IGNR_P_POS  (0U)
#define SPI_CR_SPI_RXD_IGNR_P_LEN  (5U)
#define SPI_CR_SPI_RXD_IGNR_P_MSK  (((1U << SPI_CR_SPI_RXD_IGNR_P_LEN) - 1) << SPI_CR_SPI_RXD_IGNR_P_POS)
#define SPI_CR_SPI_RXD_IGNR_P_UMSK (~(((1U << SPI_CR_SPI_RXD_IGNR_P_LEN) - 1) << SPI_CR_SPI_RXD_IGNR_P_POS))
#define SPI_CR_SPI_RXD_IGNR_S      SPI_CR_SPI_RXD_IGNR_S
#define SPI_CR_SPI_RXD_IGNR_S_POS  (16U)
#define SPI_CR_SPI_RXD_IGNR_S_LEN  (5U)
#define SPI_CR_SPI_RXD_IGNR_S_MSK  (((1U << SPI_CR_SPI_RXD_IGNR_S_LEN) - 1) << SPI_CR_SPI_RXD_IGNR_S_POS)
#define SPI_CR_SPI_RXD_IGNR_S_UMSK (~(((1U << SPI_CR_SPI_RXD_IGNR_S_LEN) - 1) << SPI_CR_SPI_RXD_IGNR_S_POS))

/* 0x1C : spi_sto_value */
#define SPI_STO_VALUE_OFFSET      (0x1C)
#define SPI_CR_SPI_STO_VALUE      SPI_CR_SPI_STO_VALUE
#define SPI_CR_SPI_STO_VALUE_POS  (0U)
#define SPI_CR_SPI_STO_VALUE_LEN  (12U)
#define SPI_CR_SPI_STO_VALUE_MSK  (((1U << SPI_CR_SPI_STO_VALUE_LEN) - 1) << SPI_CR_SPI_STO_VALUE_POS)
#define SPI_CR_SPI_STO_VALUE_UMSK (~(((1U << SPI_CR_SPI_STO_VALUE_LEN) - 1) << SPI_CR_SPI_STO_VALUE_POS))

/* 0x80 : spi_fifo_config_0 */
#define SPI_FIFO_CONFIG_0_OFFSET   (0x80)
#define SPI_DMA_TX_EN              SPI_DMA_TX_EN
#define SPI_DMA_TX_EN_POS          (0U)
#define SPI_DMA_TX_EN_LEN          (1U)
#define SPI_DMA_TX_EN_MSK          (((1U << SPI_DMA_TX_EN_LEN) - 1) << SPI_DMA_TX_EN_POS)
#define SPI_DMA_TX_EN_UMSK         (~(((1U << SPI_DMA_TX_EN_LEN) - 1) << SPI_DMA_TX_EN_POS))
#define SPI_DMA_RX_EN              SPI_DMA_RX_EN
#define SPI_DMA_RX_EN_POS          (1U)
#define SPI_DMA_RX_EN_LEN          (1U)
#define SPI_DMA_RX_EN_MSK          (((1U << SPI_DMA_RX_EN_LEN) - 1) << SPI_DMA_RX_EN_POS)
#define SPI_DMA_RX_EN_UMSK         (~(((1U << SPI_DMA_RX_EN_LEN) - 1) << SPI_DMA_RX_EN_POS))
#define SPI_TX_FIFO_CLR            SPI_TX_FIFO_CLR
#define SPI_TX_FIFO_CLR_POS        (2U)
#define SPI_TX_FIFO_CLR_LEN        (1U)
#define SPI_TX_FIFO_CLR_MSK        (((1U << SPI_TX_FIFO_CLR_LEN) - 1) << SPI_TX_FIFO_CLR_POS)
#define SPI_TX_FIFO_CLR_UMSK       (~(((1U << SPI_TX_FIFO_CLR_LEN) - 1) << SPI_TX_FIFO_CLR_POS))
#define SPI_RX_FIFO_CLR            SPI_RX_FIFO_CLR
#define SPI_RX_FIFO_CLR_POS        (3U)
#define SPI_RX_FIFO_CLR_LEN        (1U)
#define SPI_RX_FIFO_CLR_MSK        (((1U << SPI_RX_FIFO_CLR_LEN) - 1) << SPI_RX_FIFO_CLR_POS)
#define SPI_RX_FIFO_CLR_UMSK       (~(((1U << SPI_RX_FIFO_CLR_LEN) - 1) << SPI_RX_FIFO_CLR_POS))
#define SPI_TX_FIFO_OVERFLOW       SPI_TX_FIFO_OVERFLOW
#define SPI_TX_FIFO_OVERFLOW_POS   (4U)
#define SPI_TX_FIFO_OVERFLOW_LEN   (1U)
#define SPI_TX_FIFO_OVERFLOW_MSK   (((1U << SPI_TX_FIFO_OVERFLOW_LEN) - 1) << SPI_TX_FIFO_OVERFLOW_POS)
#define SPI_TX_FIFO_OVERFLOW_UMSK  (~(((1U << SPI_TX_FIFO_OVERFLOW_LEN) - 1) << SPI_TX_FIFO_OVERFLOW_POS))
#define SPI_TX_FIFO_UNDERFLOW      SPI_TX_FIFO_UNDERFLOW
#define SPI_TX_FIFO_UNDERFLOW_POS  (5U)
#define SPI_TX_FIFO_UNDERFLOW_LEN  (1U)
#define SPI_TX_FIFO_UNDERFLOW_MSK  (((1U << SPI_TX_FIFO_UNDERFLOW_LEN) - 1) << SPI_TX_FIFO_UNDERFLOW_POS)
#define SPI_TX_FIFO_UNDERFLOW_UMSK (~(((1U << SPI_TX_FIFO_UNDERFLOW_LEN) - 1) << SPI_TX_FIFO_UNDERFLOW_POS))
#define SPI_RX_FIFO_OVERFLOW       SPI_RX_FIFO_OVERFLOW
#define SPI_RX_FIFO_OVERFLOW_POS   (6U)
#define SPI_RX_FIFO_OVERFLOW_LEN   (1U)
#define SPI_RX_FIFO_OVERFLOW_MSK   (((1U << SPI_RX_FIFO_OVERFLOW_LEN) - 1) << SPI_RX_FIFO_OVERFLOW_POS)
#define SPI_RX_FIFO_OVERFLOW_UMSK  (~(((1U << SPI_RX_FIFO_OVERFLOW_LEN) - 1) << SPI_RX_FIFO_OVERFLOW_POS))
#define SPI_RX_FIFO_UNDERFLOW      SPI_RX_FIFO_UNDERFLOW
#define SPI_RX_FIFO_UNDERFLOW_POS  (7U)
#define SPI_RX_FIFO_UNDERFLOW_LEN  (1U)
#define SPI_RX_FIFO_UNDERFLOW_MSK  (((1U << SPI_RX_FIFO_UNDERFLOW_LEN) - 1) << SPI_RX_FIFO_UNDERFLOW_POS)
#define SPI_RX_FIFO_UNDERFLOW_UMSK (~(((1U << SPI_RX_FIFO_UNDERFLOW_LEN) - 1) << SPI_RX_FIFO_UNDERFLOW_POS))

/* 0x84 : spi_fifo_config_1 */
#define SPI_FIFO_CONFIG_1_OFFSET (0x84)
#define SPI_TX_FIFO_CNT          SPI_TX_FIFO_CNT
#define SPI_TX_FIFO_CNT_POS      (0U)
#define SPI_TX_FIFO_CNT_LEN      (6U)
#define SPI_TX_FIFO_CNT_MSK      (((1U << SPI_TX_FIFO_CNT_LEN) - 1) << SPI_TX_FIFO_CNT_POS)
#define SPI_TX_FIFO_CNT_UMSK     (~(((1U << SPI_TX_FIFO_CNT_LEN) - 1) << SPI_TX_FIFO_CNT_POS))
#define SPI_RX_FIFO_CNT          SPI_RX_FIFO_CNT
#define SPI_RX_FIFO_CNT_POS      (8U)
#define SPI_RX_FIFO_CNT_LEN      (6U)
#define SPI_RX_FIFO_CNT_MSK      (((1U << SPI_RX_FIFO_CNT_LEN) - 1) << SPI_RX_FIFO_CNT_POS)
#define SPI_RX_FIFO_CNT_UMSK     (~(((1U << SPI_RX_FIFO_CNT_LEN) - 1) << SPI_RX_FIFO_CNT_POS))
#define SPI_TX_FIFO_TH           SPI_TX_FIFO_TH
#define SPI_TX_FIFO_TH_POS       (16U)
#define SPI_TX_FIFO_TH_LEN       (5U)
#define SPI_TX_FIFO_TH_MSK       (((1U << SPI_TX_FIFO_TH_LEN) - 1) << SPI_TX_FIFO_TH_POS)
#define SPI_TX_FIFO_TH_UMSK      (~(((1U << SPI_TX_FIFO_TH_LEN) - 1) << SPI_TX_FIFO_TH_POS))
#define SPI_RX_FIFO_TH           SPI_RX_FIFO_TH
#define SPI_RX_FIFO_TH_POS       (24U)
#define SPI_RX_FIFO_TH_LEN       (5U)
#define SPI_RX_FIFO_TH_MSK       (((1U << SPI_RX_FIFO_TH_LEN) - 1) << SPI_RX_FIFO_TH_POS)
#define SPI_RX_FIFO_TH_UMSK      (~(((1U << SPI_RX_FIFO_TH_LEN) - 1) << SPI_RX_FIFO_TH_POS))

/* 0x88 : spi_fifo_wdata */
#define SPI_FIFO_WDATA_OFFSET (0x88)
#define SPI_FIFO_WDATA        SPI_FIFO_WDATA
#define SPI_FIFO_WDATA_POS    (0U)
#define SPI_FIFO_WDATA_LEN    (32U)
#define SPI_FIFO_WDATA_MSK    (((1U << SPI_FIFO_WDATA_LEN) - 1) << SPI_FIFO_WDATA_POS)
#define SPI_FIFO_WDATA_UMSK   (~(((1U << SPI_FIFO_WDATA_LEN) - 1) << SPI_FIFO_WDATA_POS))

/* 0x8C : spi_fifo_rdata */
#define SPI_FIFO_RDATA_OFFSET (0x8C)
#define SPI_FIFO_RDATA        SPI_FIFO_RDATA
#define SPI_FIFO_RDATA_POS    (0U)
#define SPI_FIFO_RDATA_LEN    (32U)
#define SPI_FIFO_RDATA_MSK    (((1U << SPI_FIFO_RDATA_LEN) - 1) << SPI_FIFO_RDATA_POS)
#define SPI_FIFO_RDATA_UMSK   (~(((1U << SPI_FIFO_RDATA_LEN) - 1) << SPI_FIFO_RDATA_POS))

/* 0xFC : backup_io_en */
#define SPI_BACKUP_IO_EN_OFFSET (0xFC)
#define SPI_BACKUP_IO_EN        SPI_BACKUP_IO_EN
#define SPI_BACKUP_IO_EN_POS    (0U)
#define SPI_BACKUP_IO_EN_LEN    (1U)
#define SPI_BACKUP_IO_EN_MSK    (((1U << SPI_BACKUP_IO_EN_LEN) - 1) << SPI_BACKUP_IO_EN_POS)
#define SPI_BACKUP_IO_EN_UMSK   (~(((1U << SPI_BACKUP_IO_EN_LEN) - 1) << SPI_BACKUP_IO_EN_POS))

struct spi_reg {
    /* 0x0 : spi_config */
    union {
        struct {
            uint32_t cr_spi_m_en        : 1;  /* [    0],        r/w,        0x0 */
            uint32_t cr_spi_s_en        : 1;  /* [    1],        r/w,        0x0 */
            uint32_t cr_spi_frame_size  : 2;  /* [ 3: 2],        r/w,        0x0 */
            uint32_t cr_spi_sclk_pol    : 1;  /* [    4],        r/w,        0x0 */
            uint32_t cr_spi_sclk_ph     : 1;  /* [    5],        r/w,        0x0 */
            uint32_t cr_spi_bit_inv     : 1;  /* [    6],        r/w,        0x0 */
            uint32_t cr_spi_byte_inv    : 1;  /* [    7],        r/w,        0x0 */
            uint32_t cr_spi_rxd_ignr_en : 1;  /* [    8],        r/w,        0x0 */
            uint32_t cr_spi_m_cont_en   : 1;  /* [    9],        r/w,        0x0 */
            uint32_t cr_spi_s_3pin_mode : 1;  /* [   10],        r/w,        0x0 */
            uint32_t cr_spi_deg_en      : 1;  /* [   11],        r/w,        0x0 */
            uint32_t cr_spi_deg_cnt     : 4;  /* [15:12],        r/w,        0x0 */
            uint32_t reserved_16_31     : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } spi_config;

    /* 0x4 : spi_int_sts */
    union {
        struct {
            uint32_t spi_end_int     : 1; /* [    0],          r,        0x0 */
            uint32_t spi_txf_int     : 1; /* [    1],          r,        0x1 */
            uint32_t spi_rxf_int     : 1; /* [    2],          r,        0x0 */
            uint32_t spi_sto_int     : 1; /* [    3],          r,        0x0 */
            uint32_t spi_txu_int     : 1; /* [    4],          r,        0x0 */
            uint32_t spi_fer_int     : 1; /* [    5],          r,        0x0 */
            uint32_t reserved_6_7    : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t cr_spi_end_mask : 1; /* [    8],        r/w,        0x1 */
            uint32_t cr_spi_txf_mask : 1; /* [    9],        r/w,        0x1 */
            uint32_t cr_spi_rxf_mask : 1; /* [   10],        r/w,        0x1 */
            uint32_t cr_spi_sto_mask : 1; /* [   11],        r/w,        0x1 */
            uint32_t cr_spi_txu_mask : 1; /* [   12],        r/w,        0x1 */
            uint32_t cr_spi_fer_mask : 1; /* [   13],        r/w,        0x1 */
            uint32_t reserved_14_15  : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t cr_spi_end_clr  : 1; /* [   16],        w1c,        0x0 */
            uint32_t rsvd_17         : 1; /* [   17],       rsvd,        0x0 */
            uint32_t rsvd_18         : 1; /* [   18],       rsvd,        0x0 */
            uint32_t cr_spi_sto_clr  : 1; /* [   19],        w1c,        0x0 */
            uint32_t cr_spi_txu_clr  : 1; /* [   20],        w1c,        0x0 */
            uint32_t rsvd_21         : 1; /* [   21],       rsvd,        0x0 */
            uint32_t reserved_22_23  : 2; /* [23:22],       rsvd,        0x0 */
            uint32_t cr_spi_end_en   : 1; /* [   24],        r/w,        0x1 */
            uint32_t cr_spi_txf_en   : 1; /* [   25],        r/w,        0x1 */
            uint32_t cr_spi_rxf_en   : 1; /* [   26],        r/w,        0x1 */
            uint32_t cr_spi_sto_en   : 1; /* [   27],        r/w,        0x1 */
            uint32_t cr_spi_txu_en   : 1; /* [   28],        r/w,        0x1 */
            uint32_t cr_spi_fer_en   : 1; /* [   29],        r/w,        0x1 */
            uint32_t reserved_30_31  : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } spi_int_sts;

    /* 0x8 : spi_bus_busy */
    union {
        struct {
            uint32_t sts_spi_bus_busy : 1;  /* [    0],          r,        0x0 */
            uint32_t reserved_1_31    : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } spi_bus_busy;

    /* 0xc  reserved */
    uint8_t RESERVED0xc[4];

    /* 0x10 : spi_prd_0 */
    union {
        struct {
            uint32_t cr_spi_prd_s      : 8; /* [ 7: 0],        r/w,        0xf */
            uint32_t cr_spi_prd_p      : 8; /* [15: 8],        r/w,        0xf */
            uint32_t cr_spi_prd_d_ph_0 : 8; /* [23:16],        r/w,        0xf */
            uint32_t cr_spi_prd_d_ph_1 : 8; /* [31:24],        r/w,        0xf */
        } BF;
        uint32_t WORD;
    } spi_prd_0;

    /* 0x14 : spi_prd_1 */
    union {
        struct {
            uint32_t cr_spi_prd_i  : 8;  /* [ 7: 0],        r/w,        0xf */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } spi_prd_1;

    /* 0x18 : spi_rxd_ignr */
    union {
        struct {
            uint32_t cr_spi_rxd_ignr_p : 5;  /* [ 4: 0],        r/w,        0x0 */
            uint32_t reserved_5_15     : 11; /* [15: 5],       rsvd,        0x0 */
            uint32_t cr_spi_rxd_ignr_s : 5;  /* [20:16],        r/w,        0x0 */
            uint32_t reserved_21_31    : 11; /* [31:21],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } spi_rxd_ignr;

    /* 0x1C : spi_sto_value */
    union {
        struct {
            uint32_t cr_spi_sto_value : 12; /* [11: 0],        r/w,      0xfff */
            uint32_t reserved_12_31   : 20; /* [31:12],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } spi_sto_value;

    /* 0x20  reserved */
    uint8_t RESERVED0x20[96];

    /* 0x80 : spi_fifo_config_0 */
    union {
        struct {
            uint32_t spi_dma_tx_en     : 1;  /* [    0],        r/w,        0x0 */
            uint32_t spi_dma_rx_en     : 1;  /* [    1],        r/w,        0x0 */
            uint32_t tx_fifo_clr       : 1;  /* [    2],        w1c,        0x0 */
            uint32_t rx_fifo_clr       : 1;  /* [    3],        w1c,        0x0 */
            uint32_t tx_fifo_overflow  : 1;  /* [    4],          r,        0x0 */
            uint32_t tx_fifo_underflow : 1;  /* [    5],          r,        0x0 */
            uint32_t rx_fifo_overflow  : 1;  /* [    6],          r,        0x0 */
            uint32_t rx_fifo_underflow : 1;  /* [    7],          r,        0x0 */
            uint32_t reserved_8_31     : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } spi_fifo_config_0;

    /* 0x84 : spi_fifo_config_1 */
    union {
        struct {
            uint32_t tx_fifo_cnt    : 6; /* [ 5: 0],          r,       0x20 */
            uint32_t reserved_6_7   : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t rx_fifo_cnt    : 6; /* [13: 8],          r,        0x0 */
            uint32_t reserved_14_15 : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t tx_fifo_th     : 5; /* [20:16],        r/w,        0x0 */
            uint32_t reserved_21_23 : 3; /* [23:21],       rsvd,        0x0 */
            uint32_t rx_fifo_th     : 5; /* [28:24],        r/w,        0x0 */
            uint32_t reserved_29_31 : 3; /* [31:29],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } spi_fifo_config_1;

    /* 0x88 : spi_fifo_wdata */
    union {
        struct {
            uint32_t spi_fifo_wdata : 32; /* [31: 0],          w,          x */
        } BF;
        uint32_t WORD;
    } spi_fifo_wdata;

    /* 0x8C : spi_fifo_rdata */
    union {
        struct {
            uint32_t spi_fifo_rdata : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } spi_fifo_rdata;

    /* 0x90  reserved */
    uint8_t RESERVED0x90[108];

    /* 0xFC : backup_io_en */
    union {
        struct {
            uint32_t backup_io_en  : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31 : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } backup_io_en;
};

typedef volatile struct spi_reg spi_reg_t;

#endif /* __SPI_REG_H__ */
