/**
  ******************************************************************************
  * @file    i2c_reg.h
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
#ifndef __I2C_REG_H__
#define __I2C_REG_H__

#include "bl808.h"

/* 0x0 : i2c_config */
#define I2C_CONFIG_OFFSET           (0x0)
#define I2C_CR_I2C_M_EN             I2C_CR_I2C_M_EN
#define I2C_CR_I2C_M_EN_POS         (0U)
#define I2C_CR_I2C_M_EN_LEN         (1U)
#define I2C_CR_I2C_M_EN_MSK         (((1U << I2C_CR_I2C_M_EN_LEN) - 1) << I2C_CR_I2C_M_EN_POS)
#define I2C_CR_I2C_M_EN_UMSK        (~(((1U << I2C_CR_I2C_M_EN_LEN) - 1) << I2C_CR_I2C_M_EN_POS))
#define I2C_CR_I2C_PKT_DIR          I2C_CR_I2C_PKT_DIR
#define I2C_CR_I2C_PKT_DIR_POS      (1U)
#define I2C_CR_I2C_PKT_DIR_LEN      (1U)
#define I2C_CR_I2C_PKT_DIR_MSK      (((1U << I2C_CR_I2C_PKT_DIR_LEN) - 1) << I2C_CR_I2C_PKT_DIR_POS)
#define I2C_CR_I2C_PKT_DIR_UMSK     (~(((1U << I2C_CR_I2C_PKT_DIR_LEN) - 1) << I2C_CR_I2C_PKT_DIR_POS))
#define I2C_CR_I2C_DEG_EN           I2C_CR_I2C_DEG_EN
#define I2C_CR_I2C_DEG_EN_POS       (2U)
#define I2C_CR_I2C_DEG_EN_LEN       (1U)
#define I2C_CR_I2C_DEG_EN_MSK       (((1U << I2C_CR_I2C_DEG_EN_LEN) - 1) << I2C_CR_I2C_DEG_EN_POS)
#define I2C_CR_I2C_DEG_EN_UMSK      (~(((1U << I2C_CR_I2C_DEG_EN_LEN) - 1) << I2C_CR_I2C_DEG_EN_POS))
#define I2C_CR_I2C_SCL_SYNC_EN      I2C_CR_I2C_SCL_SYNC_EN
#define I2C_CR_I2C_SCL_SYNC_EN_POS  (3U)
#define I2C_CR_I2C_SCL_SYNC_EN_LEN  (1U)
#define I2C_CR_I2C_SCL_SYNC_EN_MSK  (((1U << I2C_CR_I2C_SCL_SYNC_EN_LEN) - 1) << I2C_CR_I2C_SCL_SYNC_EN_POS)
#define I2C_CR_I2C_SCL_SYNC_EN_UMSK (~(((1U << I2C_CR_I2C_SCL_SYNC_EN_LEN) - 1) << I2C_CR_I2C_SCL_SYNC_EN_POS))
#define I2C_CR_I2C_SUB_ADDR_EN      I2C_CR_I2C_SUB_ADDR_EN
#define I2C_CR_I2C_SUB_ADDR_EN_POS  (4U)
#define I2C_CR_I2C_SUB_ADDR_EN_LEN  (1U)
#define I2C_CR_I2C_SUB_ADDR_EN_MSK  (((1U << I2C_CR_I2C_SUB_ADDR_EN_LEN) - 1) << I2C_CR_I2C_SUB_ADDR_EN_POS)
#define I2C_CR_I2C_SUB_ADDR_EN_UMSK (~(((1U << I2C_CR_I2C_SUB_ADDR_EN_LEN) - 1) << I2C_CR_I2C_SUB_ADDR_EN_POS))
#define I2C_CR_I2C_SUB_ADDR_BC      I2C_CR_I2C_SUB_ADDR_BC
#define I2C_CR_I2C_SUB_ADDR_BC_POS  (5U)
#define I2C_CR_I2C_SUB_ADDR_BC_LEN  (2U)
#define I2C_CR_I2C_SUB_ADDR_BC_MSK  (((1U << I2C_CR_I2C_SUB_ADDR_BC_LEN) - 1) << I2C_CR_I2C_SUB_ADDR_BC_POS)
#define I2C_CR_I2C_SUB_ADDR_BC_UMSK (~(((1U << I2C_CR_I2C_SUB_ADDR_BC_LEN) - 1) << I2C_CR_I2C_SUB_ADDR_BC_POS))
#define I2C_CR_I2C_10B_ADDR_EN      I2C_CR_I2C_10B_ADDR_EN
#define I2C_CR_I2C_10B_ADDR_EN_POS  (7U)
#define I2C_CR_I2C_10B_ADDR_EN_LEN  (1U)
#define I2C_CR_I2C_10B_ADDR_EN_MSK  (((1U << I2C_CR_I2C_10B_ADDR_EN_LEN) - 1) << I2C_CR_I2C_10B_ADDR_EN_POS)
#define I2C_CR_I2C_10B_ADDR_EN_UMSK (~(((1U << I2C_CR_I2C_10B_ADDR_EN_LEN) - 1) << I2C_CR_I2C_10B_ADDR_EN_POS))
#define I2C_CR_I2C_SLV_ADDR         I2C_CR_I2C_SLV_ADDR
#define I2C_CR_I2C_SLV_ADDR_POS     (8U)
#define I2C_CR_I2C_SLV_ADDR_LEN     (10U)
#define I2C_CR_I2C_SLV_ADDR_MSK     (((1U << I2C_CR_I2C_SLV_ADDR_LEN) - 1) << I2C_CR_I2C_SLV_ADDR_POS)
#define I2C_CR_I2C_SLV_ADDR_UMSK    (~(((1U << I2C_CR_I2C_SLV_ADDR_LEN) - 1) << I2C_CR_I2C_SLV_ADDR_POS))
#define I2C_CR_I2C_PKT_LEN          I2C_CR_I2C_PKT_LEN
#define I2C_CR_I2C_PKT_LEN_POS      (20U)
#define I2C_CR_I2C_PKT_LEN_LEN      (8U)
#define I2C_CR_I2C_PKT_LEN_MSK      (((1U << I2C_CR_I2C_PKT_LEN_LEN) - 1) << I2C_CR_I2C_PKT_LEN_POS)
#define I2C_CR_I2C_PKT_LEN_UMSK     (~(((1U << I2C_CR_I2C_PKT_LEN_LEN) - 1) << I2C_CR_I2C_PKT_LEN_POS))
#define I2C_CR_I2C_DEG_CNT          I2C_CR_I2C_DEG_CNT
#define I2C_CR_I2C_DEG_CNT_POS      (28U)
#define I2C_CR_I2C_DEG_CNT_LEN      (4U)
#define I2C_CR_I2C_DEG_CNT_MSK      (((1U << I2C_CR_I2C_DEG_CNT_LEN) - 1) << I2C_CR_I2C_DEG_CNT_POS)
#define I2C_CR_I2C_DEG_CNT_UMSK     (~(((1U << I2C_CR_I2C_DEG_CNT_LEN) - 1) << I2C_CR_I2C_DEG_CNT_POS))

/* 0x4 : i2c_int_sts */
#define I2C_INT_STS_OFFSET       (0x4)
#define I2C_END_INT              I2C_END_INT
#define I2C_END_INT_POS          (0U)
#define I2C_END_INT_LEN          (1U)
#define I2C_END_INT_MSK          (((1U << I2C_END_INT_LEN) - 1) << I2C_END_INT_POS)
#define I2C_END_INT_UMSK         (~(((1U << I2C_END_INT_LEN) - 1) << I2C_END_INT_POS))
#define I2C_TXF_INT              I2C_TXF_INT
#define I2C_TXF_INT_POS          (1U)
#define I2C_TXF_INT_LEN          (1U)
#define I2C_TXF_INT_MSK          (((1U << I2C_TXF_INT_LEN) - 1) << I2C_TXF_INT_POS)
#define I2C_TXF_INT_UMSK         (~(((1U << I2C_TXF_INT_LEN) - 1) << I2C_TXF_INT_POS))
#define I2C_RXF_INT              I2C_RXF_INT
#define I2C_RXF_INT_POS          (2U)
#define I2C_RXF_INT_LEN          (1U)
#define I2C_RXF_INT_MSK          (((1U << I2C_RXF_INT_LEN) - 1) << I2C_RXF_INT_POS)
#define I2C_RXF_INT_UMSK         (~(((1U << I2C_RXF_INT_LEN) - 1) << I2C_RXF_INT_POS))
#define I2C_NAK_INT              I2C_NAK_INT
#define I2C_NAK_INT_POS          (3U)
#define I2C_NAK_INT_LEN          (1U)
#define I2C_NAK_INT_MSK          (((1U << I2C_NAK_INT_LEN) - 1) << I2C_NAK_INT_POS)
#define I2C_NAK_INT_UMSK         (~(((1U << I2C_NAK_INT_LEN) - 1) << I2C_NAK_INT_POS))
#define I2C_ARB_INT              I2C_ARB_INT
#define I2C_ARB_INT_POS          (4U)
#define I2C_ARB_INT_LEN          (1U)
#define I2C_ARB_INT_MSK          (((1U << I2C_ARB_INT_LEN) - 1) << I2C_ARB_INT_POS)
#define I2C_ARB_INT_UMSK         (~(((1U << I2C_ARB_INT_LEN) - 1) << I2C_ARB_INT_POS))
#define I2C_FER_INT              I2C_FER_INT
#define I2C_FER_INT_POS          (5U)
#define I2C_FER_INT_LEN          (1U)
#define I2C_FER_INT_MSK          (((1U << I2C_FER_INT_LEN) - 1) << I2C_FER_INT_POS)
#define I2C_FER_INT_UMSK         (~(((1U << I2C_FER_INT_LEN) - 1) << I2C_FER_INT_POS))
#define I2C_CR_I2C_END_MASK      I2C_CR_I2C_END_MASK
#define I2C_CR_I2C_END_MASK_POS  (8U)
#define I2C_CR_I2C_END_MASK_LEN  (1U)
#define I2C_CR_I2C_END_MASK_MSK  (((1U << I2C_CR_I2C_END_MASK_LEN) - 1) << I2C_CR_I2C_END_MASK_POS)
#define I2C_CR_I2C_END_MASK_UMSK (~(((1U << I2C_CR_I2C_END_MASK_LEN) - 1) << I2C_CR_I2C_END_MASK_POS))
#define I2C_CR_I2C_TXF_MASK      I2C_CR_I2C_TXF_MASK
#define I2C_CR_I2C_TXF_MASK_POS  (9U)
#define I2C_CR_I2C_TXF_MASK_LEN  (1U)
#define I2C_CR_I2C_TXF_MASK_MSK  (((1U << I2C_CR_I2C_TXF_MASK_LEN) - 1) << I2C_CR_I2C_TXF_MASK_POS)
#define I2C_CR_I2C_TXF_MASK_UMSK (~(((1U << I2C_CR_I2C_TXF_MASK_LEN) - 1) << I2C_CR_I2C_TXF_MASK_POS))
#define I2C_CR_I2C_RXF_MASK      I2C_CR_I2C_RXF_MASK
#define I2C_CR_I2C_RXF_MASK_POS  (10U)
#define I2C_CR_I2C_RXF_MASK_LEN  (1U)
#define I2C_CR_I2C_RXF_MASK_MSK  (((1U << I2C_CR_I2C_RXF_MASK_LEN) - 1) << I2C_CR_I2C_RXF_MASK_POS)
#define I2C_CR_I2C_RXF_MASK_UMSK (~(((1U << I2C_CR_I2C_RXF_MASK_LEN) - 1) << I2C_CR_I2C_RXF_MASK_POS))
#define I2C_CR_I2C_NAK_MASK      I2C_CR_I2C_NAK_MASK
#define I2C_CR_I2C_NAK_MASK_POS  (11U)
#define I2C_CR_I2C_NAK_MASK_LEN  (1U)
#define I2C_CR_I2C_NAK_MASK_MSK  (((1U << I2C_CR_I2C_NAK_MASK_LEN) - 1) << I2C_CR_I2C_NAK_MASK_POS)
#define I2C_CR_I2C_NAK_MASK_UMSK (~(((1U << I2C_CR_I2C_NAK_MASK_LEN) - 1) << I2C_CR_I2C_NAK_MASK_POS))
#define I2C_CR_I2C_ARB_MASK      I2C_CR_I2C_ARB_MASK
#define I2C_CR_I2C_ARB_MASK_POS  (12U)
#define I2C_CR_I2C_ARB_MASK_LEN  (1U)
#define I2C_CR_I2C_ARB_MASK_MSK  (((1U << I2C_CR_I2C_ARB_MASK_LEN) - 1) << I2C_CR_I2C_ARB_MASK_POS)
#define I2C_CR_I2C_ARB_MASK_UMSK (~(((1U << I2C_CR_I2C_ARB_MASK_LEN) - 1) << I2C_CR_I2C_ARB_MASK_POS))
#define I2C_CR_I2C_FER_MASK      I2C_CR_I2C_FER_MASK
#define I2C_CR_I2C_FER_MASK_POS  (13U)
#define I2C_CR_I2C_FER_MASK_LEN  (1U)
#define I2C_CR_I2C_FER_MASK_MSK  (((1U << I2C_CR_I2C_FER_MASK_LEN) - 1) << I2C_CR_I2C_FER_MASK_POS)
#define I2C_CR_I2C_FER_MASK_UMSK (~(((1U << I2C_CR_I2C_FER_MASK_LEN) - 1) << I2C_CR_I2C_FER_MASK_POS))
#define I2C_CR_I2C_END_CLR       I2C_CR_I2C_END_CLR
#define I2C_CR_I2C_END_CLR_POS   (16U)
#define I2C_CR_I2C_END_CLR_LEN   (1U)
#define I2C_CR_I2C_END_CLR_MSK   (((1U << I2C_CR_I2C_END_CLR_LEN) - 1) << I2C_CR_I2C_END_CLR_POS)
#define I2C_CR_I2C_END_CLR_UMSK  (~(((1U << I2C_CR_I2C_END_CLR_LEN) - 1) << I2C_CR_I2C_END_CLR_POS))
#define I2C_CR_I2C_NAK_CLR       I2C_CR_I2C_NAK_CLR
#define I2C_CR_I2C_NAK_CLR_POS   (19U)
#define I2C_CR_I2C_NAK_CLR_LEN   (1U)
#define I2C_CR_I2C_NAK_CLR_MSK   (((1U << I2C_CR_I2C_NAK_CLR_LEN) - 1) << I2C_CR_I2C_NAK_CLR_POS)
#define I2C_CR_I2C_NAK_CLR_UMSK  (~(((1U << I2C_CR_I2C_NAK_CLR_LEN) - 1) << I2C_CR_I2C_NAK_CLR_POS))
#define I2C_CR_I2C_ARB_CLR       I2C_CR_I2C_ARB_CLR
#define I2C_CR_I2C_ARB_CLR_POS   (20U)
#define I2C_CR_I2C_ARB_CLR_LEN   (1U)
#define I2C_CR_I2C_ARB_CLR_MSK   (((1U << I2C_CR_I2C_ARB_CLR_LEN) - 1) << I2C_CR_I2C_ARB_CLR_POS)
#define I2C_CR_I2C_ARB_CLR_UMSK  (~(((1U << I2C_CR_I2C_ARB_CLR_LEN) - 1) << I2C_CR_I2C_ARB_CLR_POS))
#define I2C_CR_I2C_END_EN        I2C_CR_I2C_END_EN
#define I2C_CR_I2C_END_EN_POS    (24U)
#define I2C_CR_I2C_END_EN_LEN    (1U)
#define I2C_CR_I2C_END_EN_MSK    (((1U << I2C_CR_I2C_END_EN_LEN) - 1) << I2C_CR_I2C_END_EN_POS)
#define I2C_CR_I2C_END_EN_UMSK   (~(((1U << I2C_CR_I2C_END_EN_LEN) - 1) << I2C_CR_I2C_END_EN_POS))
#define I2C_CR_I2C_TXF_EN        I2C_CR_I2C_TXF_EN
#define I2C_CR_I2C_TXF_EN_POS    (25U)
#define I2C_CR_I2C_TXF_EN_LEN    (1U)
#define I2C_CR_I2C_TXF_EN_MSK    (((1U << I2C_CR_I2C_TXF_EN_LEN) - 1) << I2C_CR_I2C_TXF_EN_POS)
#define I2C_CR_I2C_TXF_EN_UMSK   (~(((1U << I2C_CR_I2C_TXF_EN_LEN) - 1) << I2C_CR_I2C_TXF_EN_POS))
#define I2C_CR_I2C_RXF_EN        I2C_CR_I2C_RXF_EN
#define I2C_CR_I2C_RXF_EN_POS    (26U)
#define I2C_CR_I2C_RXF_EN_LEN    (1U)
#define I2C_CR_I2C_RXF_EN_MSK    (((1U << I2C_CR_I2C_RXF_EN_LEN) - 1) << I2C_CR_I2C_RXF_EN_POS)
#define I2C_CR_I2C_RXF_EN_UMSK   (~(((1U << I2C_CR_I2C_RXF_EN_LEN) - 1) << I2C_CR_I2C_RXF_EN_POS))
#define I2C_CR_I2C_NAK_EN        I2C_CR_I2C_NAK_EN
#define I2C_CR_I2C_NAK_EN_POS    (27U)
#define I2C_CR_I2C_NAK_EN_LEN    (1U)
#define I2C_CR_I2C_NAK_EN_MSK    (((1U << I2C_CR_I2C_NAK_EN_LEN) - 1) << I2C_CR_I2C_NAK_EN_POS)
#define I2C_CR_I2C_NAK_EN_UMSK   (~(((1U << I2C_CR_I2C_NAK_EN_LEN) - 1) << I2C_CR_I2C_NAK_EN_POS))
#define I2C_CR_I2C_ARB_EN        I2C_CR_I2C_ARB_EN
#define I2C_CR_I2C_ARB_EN_POS    (28U)
#define I2C_CR_I2C_ARB_EN_LEN    (1U)
#define I2C_CR_I2C_ARB_EN_MSK    (((1U << I2C_CR_I2C_ARB_EN_LEN) - 1) << I2C_CR_I2C_ARB_EN_POS)
#define I2C_CR_I2C_ARB_EN_UMSK   (~(((1U << I2C_CR_I2C_ARB_EN_LEN) - 1) << I2C_CR_I2C_ARB_EN_POS))
#define I2C_CR_I2C_FER_EN        I2C_CR_I2C_FER_EN
#define I2C_CR_I2C_FER_EN_POS    (29U)
#define I2C_CR_I2C_FER_EN_LEN    (1U)
#define I2C_CR_I2C_FER_EN_MSK    (((1U << I2C_CR_I2C_FER_EN_LEN) - 1) << I2C_CR_I2C_FER_EN_POS)
#define I2C_CR_I2C_FER_EN_UMSK   (~(((1U << I2C_CR_I2C_FER_EN_LEN) - 1) << I2C_CR_I2C_FER_EN_POS))

/* 0x8 : i2c_sub_addr */
#define I2C_SUB_ADDR_OFFSET         (0x8)
#define I2C_CR_I2C_SUB_ADDR_B0      I2C_CR_I2C_SUB_ADDR_B0
#define I2C_CR_I2C_SUB_ADDR_B0_POS  (0U)
#define I2C_CR_I2C_SUB_ADDR_B0_LEN  (8U)
#define I2C_CR_I2C_SUB_ADDR_B0_MSK  (((1U << I2C_CR_I2C_SUB_ADDR_B0_LEN) - 1) << I2C_CR_I2C_SUB_ADDR_B0_POS)
#define I2C_CR_I2C_SUB_ADDR_B0_UMSK (~(((1U << I2C_CR_I2C_SUB_ADDR_B0_LEN) - 1) << I2C_CR_I2C_SUB_ADDR_B0_POS))
#define I2C_CR_I2C_SUB_ADDR_B1      I2C_CR_I2C_SUB_ADDR_B1
#define I2C_CR_I2C_SUB_ADDR_B1_POS  (8U)
#define I2C_CR_I2C_SUB_ADDR_B1_LEN  (8U)
#define I2C_CR_I2C_SUB_ADDR_B1_MSK  (((1U << I2C_CR_I2C_SUB_ADDR_B1_LEN) - 1) << I2C_CR_I2C_SUB_ADDR_B1_POS)
#define I2C_CR_I2C_SUB_ADDR_B1_UMSK (~(((1U << I2C_CR_I2C_SUB_ADDR_B1_LEN) - 1) << I2C_CR_I2C_SUB_ADDR_B1_POS))
#define I2C_CR_I2C_SUB_ADDR_B2      I2C_CR_I2C_SUB_ADDR_B2
#define I2C_CR_I2C_SUB_ADDR_B2_POS  (16U)
#define I2C_CR_I2C_SUB_ADDR_B2_LEN  (8U)
#define I2C_CR_I2C_SUB_ADDR_B2_MSK  (((1U << I2C_CR_I2C_SUB_ADDR_B2_LEN) - 1) << I2C_CR_I2C_SUB_ADDR_B2_POS)
#define I2C_CR_I2C_SUB_ADDR_B2_UMSK (~(((1U << I2C_CR_I2C_SUB_ADDR_B2_LEN) - 1) << I2C_CR_I2C_SUB_ADDR_B2_POS))
#define I2C_CR_I2C_SUB_ADDR_B3      I2C_CR_I2C_SUB_ADDR_B3
#define I2C_CR_I2C_SUB_ADDR_B3_POS  (24U)
#define I2C_CR_I2C_SUB_ADDR_B3_LEN  (8U)
#define I2C_CR_I2C_SUB_ADDR_B3_MSK  (((1U << I2C_CR_I2C_SUB_ADDR_B3_LEN) - 1) << I2C_CR_I2C_SUB_ADDR_B3_POS)
#define I2C_CR_I2C_SUB_ADDR_B3_UMSK (~(((1U << I2C_CR_I2C_SUB_ADDR_B3_LEN) - 1) << I2C_CR_I2C_SUB_ADDR_B3_POS))

/* 0xC : i2c_bus_busy */
#define I2C_BUS_BUSY_OFFSET          (0xC)
#define I2C_STS_I2C_BUS_BUSY         I2C_STS_I2C_BUS_BUSY
#define I2C_STS_I2C_BUS_BUSY_POS     (0U)
#define I2C_STS_I2C_BUS_BUSY_LEN     (1U)
#define I2C_STS_I2C_BUS_BUSY_MSK     (((1U << I2C_STS_I2C_BUS_BUSY_LEN) - 1) << I2C_STS_I2C_BUS_BUSY_POS)
#define I2C_STS_I2C_BUS_BUSY_UMSK    (~(((1U << I2C_STS_I2C_BUS_BUSY_LEN) - 1) << I2C_STS_I2C_BUS_BUSY_POS))
#define I2C_CR_I2C_BUS_BUSY_CLR      I2C_CR_I2C_BUS_BUSY_CLR
#define I2C_CR_I2C_BUS_BUSY_CLR_POS  (1U)
#define I2C_CR_I2C_BUS_BUSY_CLR_LEN  (1U)
#define I2C_CR_I2C_BUS_BUSY_CLR_MSK  (((1U << I2C_CR_I2C_BUS_BUSY_CLR_LEN) - 1) << I2C_CR_I2C_BUS_BUSY_CLR_POS)
#define I2C_CR_I2C_BUS_BUSY_CLR_UMSK (~(((1U << I2C_CR_I2C_BUS_BUSY_CLR_LEN) - 1) << I2C_CR_I2C_BUS_BUSY_CLR_POS))

/* 0x10 : i2c_prd_start */
#define I2C_PRD_START_OFFSET       (0x10)
#define I2C_CR_I2C_PRD_S_PH_0      I2C_CR_I2C_PRD_S_PH_0
#define I2C_CR_I2C_PRD_S_PH_0_POS  (0U)
#define I2C_CR_I2C_PRD_S_PH_0_LEN  (8U)
#define I2C_CR_I2C_PRD_S_PH_0_MSK  (((1U << I2C_CR_I2C_PRD_S_PH_0_LEN) - 1) << I2C_CR_I2C_PRD_S_PH_0_POS)
#define I2C_CR_I2C_PRD_S_PH_0_UMSK (~(((1U << I2C_CR_I2C_PRD_S_PH_0_LEN) - 1) << I2C_CR_I2C_PRD_S_PH_0_POS))
#define I2C_CR_I2C_PRD_S_PH_1      I2C_CR_I2C_PRD_S_PH_1
#define I2C_CR_I2C_PRD_S_PH_1_POS  (8U)
#define I2C_CR_I2C_PRD_S_PH_1_LEN  (8U)
#define I2C_CR_I2C_PRD_S_PH_1_MSK  (((1U << I2C_CR_I2C_PRD_S_PH_1_LEN) - 1) << I2C_CR_I2C_PRD_S_PH_1_POS)
#define I2C_CR_I2C_PRD_S_PH_1_UMSK (~(((1U << I2C_CR_I2C_PRD_S_PH_1_LEN) - 1) << I2C_CR_I2C_PRD_S_PH_1_POS))
#define I2C_CR_I2C_PRD_S_PH_2      I2C_CR_I2C_PRD_S_PH_2
#define I2C_CR_I2C_PRD_S_PH_2_POS  (16U)
#define I2C_CR_I2C_PRD_S_PH_2_LEN  (8U)
#define I2C_CR_I2C_PRD_S_PH_2_MSK  (((1U << I2C_CR_I2C_PRD_S_PH_2_LEN) - 1) << I2C_CR_I2C_PRD_S_PH_2_POS)
#define I2C_CR_I2C_PRD_S_PH_2_UMSK (~(((1U << I2C_CR_I2C_PRD_S_PH_2_LEN) - 1) << I2C_CR_I2C_PRD_S_PH_2_POS))
#define I2C_CR_I2C_PRD_S_PH_3      I2C_CR_I2C_PRD_S_PH_3
#define I2C_CR_I2C_PRD_S_PH_3_POS  (24U)
#define I2C_CR_I2C_PRD_S_PH_3_LEN  (8U)
#define I2C_CR_I2C_PRD_S_PH_3_MSK  (((1U << I2C_CR_I2C_PRD_S_PH_3_LEN) - 1) << I2C_CR_I2C_PRD_S_PH_3_POS)
#define I2C_CR_I2C_PRD_S_PH_3_UMSK (~(((1U << I2C_CR_I2C_PRD_S_PH_3_LEN) - 1) << I2C_CR_I2C_PRD_S_PH_3_POS))

/* 0x14 : i2c_prd_stop */
#define I2C_PRD_STOP_OFFSET        (0x14)
#define I2C_CR_I2C_PRD_P_PH_0      I2C_CR_I2C_PRD_P_PH_0
#define I2C_CR_I2C_PRD_P_PH_0_POS  (0U)
#define I2C_CR_I2C_PRD_P_PH_0_LEN  (8U)
#define I2C_CR_I2C_PRD_P_PH_0_MSK  (((1U << I2C_CR_I2C_PRD_P_PH_0_LEN) - 1) << I2C_CR_I2C_PRD_P_PH_0_POS)
#define I2C_CR_I2C_PRD_P_PH_0_UMSK (~(((1U << I2C_CR_I2C_PRD_P_PH_0_LEN) - 1) << I2C_CR_I2C_PRD_P_PH_0_POS))
#define I2C_CR_I2C_PRD_P_PH_1      I2C_CR_I2C_PRD_P_PH_1
#define I2C_CR_I2C_PRD_P_PH_1_POS  (8U)
#define I2C_CR_I2C_PRD_P_PH_1_LEN  (8U)
#define I2C_CR_I2C_PRD_P_PH_1_MSK  (((1U << I2C_CR_I2C_PRD_P_PH_1_LEN) - 1) << I2C_CR_I2C_PRD_P_PH_1_POS)
#define I2C_CR_I2C_PRD_P_PH_1_UMSK (~(((1U << I2C_CR_I2C_PRD_P_PH_1_LEN) - 1) << I2C_CR_I2C_PRD_P_PH_1_POS))
#define I2C_CR_I2C_PRD_P_PH_2      I2C_CR_I2C_PRD_P_PH_2
#define I2C_CR_I2C_PRD_P_PH_2_POS  (16U)
#define I2C_CR_I2C_PRD_P_PH_2_LEN  (8U)
#define I2C_CR_I2C_PRD_P_PH_2_MSK  (((1U << I2C_CR_I2C_PRD_P_PH_2_LEN) - 1) << I2C_CR_I2C_PRD_P_PH_2_POS)
#define I2C_CR_I2C_PRD_P_PH_2_UMSK (~(((1U << I2C_CR_I2C_PRD_P_PH_2_LEN) - 1) << I2C_CR_I2C_PRD_P_PH_2_POS))
#define I2C_CR_I2C_PRD_P_PH_3      I2C_CR_I2C_PRD_P_PH_3
#define I2C_CR_I2C_PRD_P_PH_3_POS  (24U)
#define I2C_CR_I2C_PRD_P_PH_3_LEN  (8U)
#define I2C_CR_I2C_PRD_P_PH_3_MSK  (((1U << I2C_CR_I2C_PRD_P_PH_3_LEN) - 1) << I2C_CR_I2C_PRD_P_PH_3_POS)
#define I2C_CR_I2C_PRD_P_PH_3_UMSK (~(((1U << I2C_CR_I2C_PRD_P_PH_3_LEN) - 1) << I2C_CR_I2C_PRD_P_PH_3_POS))

/* 0x18 : i2c_prd_data */
#define I2C_PRD_DATA_OFFSET        (0x18)
#define I2C_CR_I2C_PRD_D_PH_0      I2C_CR_I2C_PRD_D_PH_0
#define I2C_CR_I2C_PRD_D_PH_0_POS  (0U)
#define I2C_CR_I2C_PRD_D_PH_0_LEN  (8U)
#define I2C_CR_I2C_PRD_D_PH_0_MSK  (((1U << I2C_CR_I2C_PRD_D_PH_0_LEN) - 1) << I2C_CR_I2C_PRD_D_PH_0_POS)
#define I2C_CR_I2C_PRD_D_PH_0_UMSK (~(((1U << I2C_CR_I2C_PRD_D_PH_0_LEN) - 1) << I2C_CR_I2C_PRD_D_PH_0_POS))
#define I2C_CR_I2C_PRD_D_PH_1      I2C_CR_I2C_PRD_D_PH_1
#define I2C_CR_I2C_PRD_D_PH_1_POS  (8U)
#define I2C_CR_I2C_PRD_D_PH_1_LEN  (8U)
#define I2C_CR_I2C_PRD_D_PH_1_MSK  (((1U << I2C_CR_I2C_PRD_D_PH_1_LEN) - 1) << I2C_CR_I2C_PRD_D_PH_1_POS)
#define I2C_CR_I2C_PRD_D_PH_1_UMSK (~(((1U << I2C_CR_I2C_PRD_D_PH_1_LEN) - 1) << I2C_CR_I2C_PRD_D_PH_1_POS))
#define I2C_CR_I2C_PRD_D_PH_2      I2C_CR_I2C_PRD_D_PH_2
#define I2C_CR_I2C_PRD_D_PH_2_POS  (16U)
#define I2C_CR_I2C_PRD_D_PH_2_LEN  (8U)
#define I2C_CR_I2C_PRD_D_PH_2_MSK  (((1U << I2C_CR_I2C_PRD_D_PH_2_LEN) - 1) << I2C_CR_I2C_PRD_D_PH_2_POS)
#define I2C_CR_I2C_PRD_D_PH_2_UMSK (~(((1U << I2C_CR_I2C_PRD_D_PH_2_LEN) - 1) << I2C_CR_I2C_PRD_D_PH_2_POS))
#define I2C_CR_I2C_PRD_D_PH_3      I2C_CR_I2C_PRD_D_PH_3
#define I2C_CR_I2C_PRD_D_PH_3_POS  (24U)
#define I2C_CR_I2C_PRD_D_PH_3_LEN  (8U)
#define I2C_CR_I2C_PRD_D_PH_3_MSK  (((1U << I2C_CR_I2C_PRD_D_PH_3_LEN) - 1) << I2C_CR_I2C_PRD_D_PH_3_POS)
#define I2C_CR_I2C_PRD_D_PH_3_UMSK (~(((1U << I2C_CR_I2C_PRD_D_PH_3_LEN) - 1) << I2C_CR_I2C_PRD_D_PH_3_POS))

/* 0x80 : i2c_fifo_config_0 */
#define I2C_FIFO_CONFIG_0_OFFSET   (0x80)
#define I2C_DMA_TX_EN              I2C_DMA_TX_EN
#define I2C_DMA_TX_EN_POS          (0U)
#define I2C_DMA_TX_EN_LEN          (1U)
#define I2C_DMA_TX_EN_MSK          (((1U << I2C_DMA_TX_EN_LEN) - 1) << I2C_DMA_TX_EN_POS)
#define I2C_DMA_TX_EN_UMSK         (~(((1U << I2C_DMA_TX_EN_LEN) - 1) << I2C_DMA_TX_EN_POS))
#define I2C_DMA_RX_EN              I2C_DMA_RX_EN
#define I2C_DMA_RX_EN_POS          (1U)
#define I2C_DMA_RX_EN_LEN          (1U)
#define I2C_DMA_RX_EN_MSK          (((1U << I2C_DMA_RX_EN_LEN) - 1) << I2C_DMA_RX_EN_POS)
#define I2C_DMA_RX_EN_UMSK         (~(((1U << I2C_DMA_RX_EN_LEN) - 1) << I2C_DMA_RX_EN_POS))
#define I2C_TX_FIFO_CLR            I2C_TX_FIFO_CLR
#define I2C_TX_FIFO_CLR_POS        (2U)
#define I2C_TX_FIFO_CLR_LEN        (1U)
#define I2C_TX_FIFO_CLR_MSK        (((1U << I2C_TX_FIFO_CLR_LEN) - 1) << I2C_TX_FIFO_CLR_POS)
#define I2C_TX_FIFO_CLR_UMSK       (~(((1U << I2C_TX_FIFO_CLR_LEN) - 1) << I2C_TX_FIFO_CLR_POS))
#define I2C_RX_FIFO_CLR            I2C_RX_FIFO_CLR
#define I2C_RX_FIFO_CLR_POS        (3U)
#define I2C_RX_FIFO_CLR_LEN        (1U)
#define I2C_RX_FIFO_CLR_MSK        (((1U << I2C_RX_FIFO_CLR_LEN) - 1) << I2C_RX_FIFO_CLR_POS)
#define I2C_RX_FIFO_CLR_UMSK       (~(((1U << I2C_RX_FIFO_CLR_LEN) - 1) << I2C_RX_FIFO_CLR_POS))
#define I2C_TX_FIFO_OVERFLOW       I2C_TX_FIFO_OVERFLOW
#define I2C_TX_FIFO_OVERFLOW_POS   (4U)
#define I2C_TX_FIFO_OVERFLOW_LEN   (1U)
#define I2C_TX_FIFO_OVERFLOW_MSK   (((1U << I2C_TX_FIFO_OVERFLOW_LEN) - 1) << I2C_TX_FIFO_OVERFLOW_POS)
#define I2C_TX_FIFO_OVERFLOW_UMSK  (~(((1U << I2C_TX_FIFO_OVERFLOW_LEN) - 1) << I2C_TX_FIFO_OVERFLOW_POS))
#define I2C_TX_FIFO_UNDERFLOW      I2C_TX_FIFO_UNDERFLOW
#define I2C_TX_FIFO_UNDERFLOW_POS  (5U)
#define I2C_TX_FIFO_UNDERFLOW_LEN  (1U)
#define I2C_TX_FIFO_UNDERFLOW_MSK  (((1U << I2C_TX_FIFO_UNDERFLOW_LEN) - 1) << I2C_TX_FIFO_UNDERFLOW_POS)
#define I2C_TX_FIFO_UNDERFLOW_UMSK (~(((1U << I2C_TX_FIFO_UNDERFLOW_LEN) - 1) << I2C_TX_FIFO_UNDERFLOW_POS))
#define I2C_RX_FIFO_OVERFLOW       I2C_RX_FIFO_OVERFLOW
#define I2C_RX_FIFO_OVERFLOW_POS   (6U)
#define I2C_RX_FIFO_OVERFLOW_LEN   (1U)
#define I2C_RX_FIFO_OVERFLOW_MSK   (((1U << I2C_RX_FIFO_OVERFLOW_LEN) - 1) << I2C_RX_FIFO_OVERFLOW_POS)
#define I2C_RX_FIFO_OVERFLOW_UMSK  (~(((1U << I2C_RX_FIFO_OVERFLOW_LEN) - 1) << I2C_RX_FIFO_OVERFLOW_POS))
#define I2C_RX_FIFO_UNDERFLOW      I2C_RX_FIFO_UNDERFLOW
#define I2C_RX_FIFO_UNDERFLOW_POS  (7U)
#define I2C_RX_FIFO_UNDERFLOW_LEN  (1U)
#define I2C_RX_FIFO_UNDERFLOW_MSK  (((1U << I2C_RX_FIFO_UNDERFLOW_LEN) - 1) << I2C_RX_FIFO_UNDERFLOW_POS)
#define I2C_RX_FIFO_UNDERFLOW_UMSK (~(((1U << I2C_RX_FIFO_UNDERFLOW_LEN) - 1) << I2C_RX_FIFO_UNDERFLOW_POS))

/* 0x84 : i2c_fifo_config_1 */
#define I2C_FIFO_CONFIG_1_OFFSET (0x84)
#define I2C_TX_FIFO_CNT          I2C_TX_FIFO_CNT
#define I2C_TX_FIFO_CNT_POS      (0U)
#define I2C_TX_FIFO_CNT_LEN      (2U)
#define I2C_TX_FIFO_CNT_MSK      (((1U << I2C_TX_FIFO_CNT_LEN) - 1) << I2C_TX_FIFO_CNT_POS)
#define I2C_TX_FIFO_CNT_UMSK     (~(((1U << I2C_TX_FIFO_CNT_LEN) - 1) << I2C_TX_FIFO_CNT_POS))
#define I2C_RX_FIFO_CNT          I2C_RX_FIFO_CNT
#define I2C_RX_FIFO_CNT_POS      (8U)
#define I2C_RX_FIFO_CNT_LEN      (2U)
#define I2C_RX_FIFO_CNT_MSK      (((1U << I2C_RX_FIFO_CNT_LEN) - 1) << I2C_RX_FIFO_CNT_POS)
#define I2C_RX_FIFO_CNT_UMSK     (~(((1U << I2C_RX_FIFO_CNT_LEN) - 1) << I2C_RX_FIFO_CNT_POS))
#define I2C_TX_FIFO_TH           I2C_TX_FIFO_TH
#define I2C_TX_FIFO_TH_POS       (16U)
#define I2C_TX_FIFO_TH_LEN       (1U)
#define I2C_TX_FIFO_TH_MSK       (((1U << I2C_TX_FIFO_TH_LEN) - 1) << I2C_TX_FIFO_TH_POS)
#define I2C_TX_FIFO_TH_UMSK      (~(((1U << I2C_TX_FIFO_TH_LEN) - 1) << I2C_TX_FIFO_TH_POS))
#define I2C_RX_FIFO_TH           I2C_RX_FIFO_TH
#define I2C_RX_FIFO_TH_POS       (24U)
#define I2C_RX_FIFO_TH_LEN       (1U)
#define I2C_RX_FIFO_TH_MSK       (((1U << I2C_RX_FIFO_TH_LEN) - 1) << I2C_RX_FIFO_TH_POS)
#define I2C_RX_FIFO_TH_UMSK      (~(((1U << I2C_RX_FIFO_TH_LEN) - 1) << I2C_RX_FIFO_TH_POS))

/* 0x88 : i2c_fifo_wdata */
#define I2C_FIFO_WDATA_OFFSET (0x88)
#define I2C_FIFO_WDATA        I2C_FIFO_WDATA
#define I2C_FIFO_WDATA_POS    (0U)
#define I2C_FIFO_WDATA_LEN    (32U)
#define I2C_FIFO_WDATA_MSK    (((1U << I2C_FIFO_WDATA_LEN) - 1) << I2C_FIFO_WDATA_POS)
#define I2C_FIFO_WDATA_UMSK   (~(((1U << I2C_FIFO_WDATA_LEN) - 1) << I2C_FIFO_WDATA_POS))

/* 0x8C : i2c_fifo_rdata */
#define I2C_FIFO_RDATA_OFFSET (0x8C)
#define I2C_FIFO_RDATA        I2C_FIFO_RDATA
#define I2C_FIFO_RDATA_POS    (0U)
#define I2C_FIFO_RDATA_LEN    (32U)
#define I2C_FIFO_RDATA_MSK    (((1U << I2C_FIFO_RDATA_LEN) - 1) << I2C_FIFO_RDATA_POS)
#define I2C_FIFO_RDATA_UMSK   (~(((1U << I2C_FIFO_RDATA_LEN) - 1) << I2C_FIFO_RDATA_POS))

struct i2c_reg {
    /* 0x0 : i2c_config */
    union {
        struct {
            uint32_t cr_i2c_m_en        : 1;  /* [    0],        r/w,        0x0 */
            uint32_t cr_i2c_pkt_dir     : 1;  /* [    1],        r/w,        0x1 */
            uint32_t cr_i2c_deg_en      : 1;  /* [    2],        r/w,        0x0 */
            uint32_t cr_i2c_scl_sync_en : 1;  /* [    3],        r/w,        0x1 */
            uint32_t cr_i2c_sub_addr_en : 1;  /* [    4],        r/w,        0x0 */
            uint32_t cr_i2c_sub_addr_bc : 2;  /* [ 6: 5],        r/w,        0x0 */
            uint32_t cr_i2c_10b_addr_en : 1;  /* [    7],        r/w,        0x0 */
            uint32_t cr_i2c_slv_addr    : 10; /* [17: 8],        r/w,        0x0 */
            uint32_t reserved_18_19     : 2;  /* [19:18],       rsvd,        0x0 */
            uint32_t cr_i2c_pkt_len     : 8;  /* [27:20],        r/w,        0x0 */
            uint32_t cr_i2c_deg_cnt     : 4;  /* [31:28],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } i2c_config;

    /* 0x4 : i2c_int_sts */
    union {
        struct {
            uint32_t i2c_end_int     : 1; /* [    0],          r,        0x0 */
            uint32_t i2c_txf_int     : 1; /* [    1],          r,        0x1 */
            uint32_t i2c_rxf_int     : 1; /* [    2],          r,        0x0 */
            uint32_t i2c_nak_int     : 1; /* [    3],          r,        0x0 */
            uint32_t i2c_arb_int     : 1; /* [    4],          r,        0x0 */
            uint32_t i2c_fer_int     : 1; /* [    5],          r,        0x0 */
            uint32_t reserved_6_7    : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t cr_i2c_end_mask : 1; /* [    8],        r/w,        0x1 */
            uint32_t cr_i2c_txf_mask : 1; /* [    9],        r/w,        0x1 */
            uint32_t cr_i2c_rxf_mask : 1; /* [   10],        r/w,        0x1 */
            uint32_t cr_i2c_nak_mask : 1; /* [   11],        r/w,        0x1 */
            uint32_t cr_i2c_arb_mask : 1; /* [   12],        r/w,        0x1 */
            uint32_t cr_i2c_fer_mask : 1; /* [   13],        r/w,        0x1 */
            uint32_t reserved_14_15  : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t cr_i2c_end_clr  : 1; /* [   16],        w1c,        0x0 */
            uint32_t rsvd_17         : 1; /* [   17],       rsvd,        0x0 */
            uint32_t rsvd_18         : 1; /* [   18],       rsvd,        0x0 */
            uint32_t cr_i2c_nak_clr  : 1; /* [   19],        w1c,        0x0 */
            uint32_t cr_i2c_arb_clr  : 1; /* [   20],        w1c,        0x0 */
            uint32_t rsvd_21         : 1; /* [   21],       rsvd,        0x0 */
            uint32_t reserved_22_23  : 2; /* [23:22],       rsvd,        0x0 */
            uint32_t cr_i2c_end_en   : 1; /* [   24],        r/w,        0x1 */
            uint32_t cr_i2c_txf_en   : 1; /* [   25],        r/w,        0x1 */
            uint32_t cr_i2c_rxf_en   : 1; /* [   26],        r/w,        0x1 */
            uint32_t cr_i2c_nak_en   : 1; /* [   27],        r/w,        0x1 */
            uint32_t cr_i2c_arb_en   : 1; /* [   28],        r/w,        0x1 */
            uint32_t cr_i2c_fer_en   : 1; /* [   29],        r/w,        0x1 */
            uint32_t reserved_30_31  : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } i2c_int_sts;

    /* 0x8 : i2c_sub_addr */
    union {
        struct {
            uint32_t cr_i2c_sub_addr_b0 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t cr_i2c_sub_addr_b1 : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t cr_i2c_sub_addr_b2 : 8; /* [23:16],        r/w,        0x0 */
            uint32_t cr_i2c_sub_addr_b3 : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } i2c_sub_addr;

    /* 0xC : i2c_bus_busy */
    union {
        struct {
            uint32_t sts_i2c_bus_busy    : 1;  /* [    0],          r,        0x0 */
            uint32_t cr_i2c_bus_busy_clr : 1;  /* [    1],        w1c,        0x0 */
            uint32_t reserved_2_31       : 30; /* [31: 2],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } i2c_bus_busy;

    /* 0x10 : i2c_prd_start */
    union {
        struct {
            uint32_t cr_i2c_prd_s_ph_0 : 8; /* [ 7: 0],        r/w,        0xf */
            uint32_t cr_i2c_prd_s_ph_1 : 8; /* [15: 8],        r/w,        0xf */
            uint32_t cr_i2c_prd_s_ph_2 : 8; /* [23:16],        r/w,        0xf */
            uint32_t cr_i2c_prd_s_ph_3 : 8; /* [31:24],        r/w,        0xf */
        } BF;
        uint32_t WORD;
    } i2c_prd_start;

    /* 0x14 : i2c_prd_stop */
    union {
        struct {
            uint32_t cr_i2c_prd_p_ph_0 : 8; /* [ 7: 0],        r/w,        0xf */
            uint32_t cr_i2c_prd_p_ph_1 : 8; /* [15: 8],        r/w,        0xf */
            uint32_t cr_i2c_prd_p_ph_2 : 8; /* [23:16],        r/w,        0xf */
            uint32_t cr_i2c_prd_p_ph_3 : 8; /* [31:24],        r/w,        0xf */
        } BF;
        uint32_t WORD;
    } i2c_prd_stop;

    /* 0x18 : i2c_prd_data */
    union {
        struct {
            uint32_t cr_i2c_prd_d_ph_0 : 8; /* [ 7: 0],        r/w,        0xf */
            uint32_t cr_i2c_prd_d_ph_1 : 8; /* [15: 8],        r/w,        0xf */
            uint32_t cr_i2c_prd_d_ph_2 : 8; /* [23:16],        r/w,        0xf */
            uint32_t cr_i2c_prd_d_ph_3 : 8; /* [31:24],        r/w,        0xf */
        } BF;
        uint32_t WORD;
    } i2c_prd_data;

    /* 0x1c  reserved */
    uint8_t RESERVED0x1c[100];

    /* 0x80 : i2c_fifo_config_0 */
    union {
        struct {
            uint32_t i2c_dma_tx_en     : 1;  /* [    0],        r/w,        0x0 */
            uint32_t i2c_dma_rx_en     : 1;  /* [    1],        r/w,        0x0 */
            uint32_t tx_fifo_clr       : 1;  /* [    2],        w1c,        0x0 */
            uint32_t rx_fifo_clr       : 1;  /* [    3],        w1c,        0x0 */
            uint32_t tx_fifo_overflow  : 1;  /* [    4],          r,        0x0 */
            uint32_t tx_fifo_underflow : 1;  /* [    5],          r,        0x0 */
            uint32_t rx_fifo_overflow  : 1;  /* [    6],          r,        0x0 */
            uint32_t rx_fifo_underflow : 1;  /* [    7],          r,        0x0 */
            uint32_t reserved_8_31     : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } i2c_fifo_config_0;

    /* 0x84 : i2c_fifo_config_1 */
    union {
        struct {
            uint32_t tx_fifo_cnt    : 2; /* [ 1: 0],          r,        0x2 */
            uint32_t reserved_2_7   : 6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t rx_fifo_cnt    : 2; /* [ 9: 8],          r,        0x0 */
            uint32_t reserved_10_15 : 6; /* [15:10],       rsvd,        0x0 */
            uint32_t tx_fifo_th     : 1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_23 : 7; /* [23:17],       rsvd,        0x0 */
            uint32_t rx_fifo_th     : 1; /* [   24],        r/w,        0x0 */
            uint32_t reserved_25_31 : 7; /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } i2c_fifo_config_1;

    /* 0x88 : i2c_fifo_wdata */
    union {
        struct {
            uint32_t i2c_fifo_wdata : 32; /* [31: 0],          w,          x */
        } BF;
        uint32_t WORD;
    } i2c_fifo_wdata;

    /* 0x8C : i2c_fifo_rdata */
    union {
        struct {
            uint32_t i2c_fifo_rdata : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } i2c_fifo_rdata;
};

typedef volatile struct i2c_reg i2c_reg_t;

#endif /* __I2C_REG_H__ */
