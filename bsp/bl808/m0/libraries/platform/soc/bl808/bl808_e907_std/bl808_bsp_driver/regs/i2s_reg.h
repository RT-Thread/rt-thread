/**
  ******************************************************************************
  * @file    i2s_reg.h
  * @version V1.0
  * @date    2021-06-22
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
#ifndef __I2S_REG_H__
#define __I2S_REG_H__

#include "bl808.h"

/* 0x0 : i2s_config */
#define I2S_CONFIG_OFFSET      (0x0)
#define I2S_CR_I2S_M_EN        I2S_CR_I2S_M_EN
#define I2S_CR_I2S_M_EN_POS    (0U)
#define I2S_CR_I2S_M_EN_LEN    (1U)
#define I2S_CR_I2S_M_EN_MSK    (((1U << I2S_CR_I2S_M_EN_LEN) - 1) << I2S_CR_I2S_M_EN_POS)
#define I2S_CR_I2S_M_EN_UMSK   (~(((1U << I2S_CR_I2S_M_EN_LEN) - 1) << I2S_CR_I2S_M_EN_POS))
#define I2S_CR_I2S_S_EN        I2S_CR_I2S_S_EN
#define I2S_CR_I2S_S_EN_POS    (1U)
#define I2S_CR_I2S_S_EN_LEN    (1U)
#define I2S_CR_I2S_S_EN_MSK    (((1U << I2S_CR_I2S_S_EN_LEN) - 1) << I2S_CR_I2S_S_EN_POS)
#define I2S_CR_I2S_S_EN_UMSK   (~(((1U << I2S_CR_I2S_S_EN_LEN) - 1) << I2S_CR_I2S_S_EN_POS))
#define I2S_CR_I2S_TXD_EN      I2S_CR_I2S_TXD_EN
#define I2S_CR_I2S_TXD_EN_POS  (2U)
#define I2S_CR_I2S_TXD_EN_LEN  (1U)
#define I2S_CR_I2S_TXD_EN_MSK  (((1U << I2S_CR_I2S_TXD_EN_LEN) - 1) << I2S_CR_I2S_TXD_EN_POS)
#define I2S_CR_I2S_TXD_EN_UMSK (~(((1U << I2S_CR_I2S_TXD_EN_LEN) - 1) << I2S_CR_I2S_TXD_EN_POS))
#define I2S_CR_I2S_RXD_EN      I2S_CR_I2S_RXD_EN
#define I2S_CR_I2S_RXD_EN_POS  (3U)
#define I2S_CR_I2S_RXD_EN_LEN  (1U)
#define I2S_CR_I2S_RXD_EN_MSK  (((1U << I2S_CR_I2S_RXD_EN_LEN) - 1) << I2S_CR_I2S_RXD_EN_POS)
#define I2S_CR_I2S_RXD_EN_UMSK (~(((1U << I2S_CR_I2S_RXD_EN_LEN) - 1) << I2S_CR_I2S_RXD_EN_POS))
#define I2S_CR_MONO_MODE       I2S_CR_MONO_MODE
#define I2S_CR_MONO_MODE_POS   (4U)
#define I2S_CR_MONO_MODE_LEN   (1U)
#define I2S_CR_MONO_MODE_MSK   (((1U << I2S_CR_MONO_MODE_LEN) - 1) << I2S_CR_MONO_MODE_POS)
#define I2S_CR_MONO_MODE_UMSK  (~(((1U << I2S_CR_MONO_MODE_LEN) - 1) << I2S_CR_MONO_MODE_POS))
#define I2S_CR_MUTE_MODE       I2S_CR_MUTE_MODE
#define I2S_CR_MUTE_MODE_POS   (5U)
#define I2S_CR_MUTE_MODE_LEN   (1U)
#define I2S_CR_MUTE_MODE_MSK   (((1U << I2S_CR_MUTE_MODE_LEN) - 1) << I2S_CR_MUTE_MODE_POS)
#define I2S_CR_MUTE_MODE_UMSK  (~(((1U << I2S_CR_MUTE_MODE_LEN) - 1) << I2S_CR_MUTE_MODE_POS))
#define I2S_CR_FS_1T_MODE      I2S_CR_FS_1T_MODE
#define I2S_CR_FS_1T_MODE_POS  (6U)
#define I2S_CR_FS_1T_MODE_LEN  (1U)
#define I2S_CR_FS_1T_MODE_MSK  (((1U << I2S_CR_FS_1T_MODE_LEN) - 1) << I2S_CR_FS_1T_MODE_POS)
#define I2S_CR_FS_1T_MODE_UMSK (~(((1U << I2S_CR_FS_1T_MODE_LEN) - 1) << I2S_CR_FS_1T_MODE_POS))
#define I2S_CR_FS_CH_CNT       I2S_CR_FS_CH_CNT
#define I2S_CR_FS_CH_CNT_POS   (7U)
#define I2S_CR_FS_CH_CNT_LEN   (2U)
#define I2S_CR_FS_CH_CNT_MSK   (((1U << I2S_CR_FS_CH_CNT_LEN) - 1) << I2S_CR_FS_CH_CNT_POS)
#define I2S_CR_FS_CH_CNT_UMSK  (~(((1U << I2S_CR_FS_CH_CNT_LEN) - 1) << I2S_CR_FS_CH_CNT_POS))
#define I2S_CR_FRAME_SIZE      I2S_CR_FRAME_SIZE
#define I2S_CR_FRAME_SIZE_POS  (12U)
#define I2S_CR_FRAME_SIZE_LEN  (2U)
#define I2S_CR_FRAME_SIZE_MSK  (((1U << I2S_CR_FRAME_SIZE_LEN) - 1) << I2S_CR_FRAME_SIZE_POS)
#define I2S_CR_FRAME_SIZE_UMSK (~(((1U << I2S_CR_FRAME_SIZE_LEN) - 1) << I2S_CR_FRAME_SIZE_POS))
#define I2S_CR_DATA_SIZE       I2S_CR_DATA_SIZE
#define I2S_CR_DATA_SIZE_POS   (14U)
#define I2S_CR_DATA_SIZE_LEN   (2U)
#define I2S_CR_DATA_SIZE_MSK   (((1U << I2S_CR_DATA_SIZE_LEN) - 1) << I2S_CR_DATA_SIZE_POS)
#define I2S_CR_DATA_SIZE_UMSK  (~(((1U << I2S_CR_DATA_SIZE_LEN) - 1) << I2S_CR_DATA_SIZE_POS))
#define I2S_CR_I2S_MODE        I2S_CR_I2S_MODE
#define I2S_CR_I2S_MODE_POS    (16U)
#define I2S_CR_I2S_MODE_LEN    (2U)
#define I2S_CR_I2S_MODE_MSK    (((1U << I2S_CR_I2S_MODE_LEN) - 1) << I2S_CR_I2S_MODE_POS)
#define I2S_CR_I2S_MODE_UMSK   (~(((1U << I2S_CR_I2S_MODE_LEN) - 1) << I2S_CR_I2S_MODE_POS))
#define I2S_CR_ENDIAN          I2S_CR_ENDIAN
#define I2S_CR_ENDIAN_POS      (18U)
#define I2S_CR_ENDIAN_LEN      (1U)
#define I2S_CR_ENDIAN_MSK      (((1U << I2S_CR_ENDIAN_LEN) - 1) << I2S_CR_ENDIAN_POS)
#define I2S_CR_ENDIAN_UMSK     (~(((1U << I2S_CR_ENDIAN_LEN) - 1) << I2S_CR_ENDIAN_POS))
#define I2S_CR_MONO_RX_CH      I2S_CR_MONO_RX_CH
#define I2S_CR_MONO_RX_CH_POS  (19U)
#define I2S_CR_MONO_RX_CH_LEN  (1U)
#define I2S_CR_MONO_RX_CH_MSK  (((1U << I2S_CR_MONO_RX_CH_LEN) - 1) << I2S_CR_MONO_RX_CH_POS)
#define I2S_CR_MONO_RX_CH_UMSK (~(((1U << I2S_CR_MONO_RX_CH_LEN) - 1) << I2S_CR_MONO_RX_CH_POS))
#define I2S_CR_OFS_CNT         I2S_CR_OFS_CNT
#define I2S_CR_OFS_CNT_POS     (20U)
#define I2S_CR_OFS_CNT_LEN     (5U)
#define I2S_CR_OFS_CNT_MSK     (((1U << I2S_CR_OFS_CNT_LEN) - 1) << I2S_CR_OFS_CNT_POS)
#define I2S_CR_OFS_CNT_UMSK    (~(((1U << I2S_CR_OFS_CNT_LEN) - 1) << I2S_CR_OFS_CNT_POS))
#define I2S_CR_OFS_EN          I2S_CR_OFS_EN
#define I2S_CR_OFS_EN_POS      (25U)
#define I2S_CR_OFS_EN_LEN      (1U)
#define I2S_CR_OFS_EN_MSK      (((1U << I2S_CR_OFS_EN_LEN) - 1) << I2S_CR_OFS_EN_POS)
#define I2S_CR_OFS_EN_UMSK     (~(((1U << I2S_CR_OFS_EN_LEN) - 1) << I2S_CR_OFS_EN_POS))

/* 0x4 : i2s_int_sts */
#define I2S_INT_STS_OFFSET       (0x4)
#define I2S_TXF_INT              I2S_TXF_INT
#define I2S_TXF_INT_POS          (0U)
#define I2S_TXF_INT_LEN          (1U)
#define I2S_TXF_INT_MSK          (((1U << I2S_TXF_INT_LEN) - 1) << I2S_TXF_INT_POS)
#define I2S_TXF_INT_UMSK         (~(((1U << I2S_TXF_INT_LEN) - 1) << I2S_TXF_INT_POS))
#define I2S_RXF_INT              I2S_RXF_INT
#define I2S_RXF_INT_POS          (1U)
#define I2S_RXF_INT_LEN          (1U)
#define I2S_RXF_INT_MSK          (((1U << I2S_RXF_INT_LEN) - 1) << I2S_RXF_INT_POS)
#define I2S_RXF_INT_UMSK         (~(((1U << I2S_RXF_INT_LEN) - 1) << I2S_RXF_INT_POS))
#define I2S_FER_INT              I2S_FER_INT
#define I2S_FER_INT_POS          (2U)
#define I2S_FER_INT_LEN          (1U)
#define I2S_FER_INT_MSK          (((1U << I2S_FER_INT_LEN) - 1) << I2S_FER_INT_POS)
#define I2S_FER_INT_UMSK         (~(((1U << I2S_FER_INT_LEN) - 1) << I2S_FER_INT_POS))
#define I2S_CR_I2S_TXF_MASK      I2S_CR_I2S_TXF_MASK
#define I2S_CR_I2S_TXF_MASK_POS  (8U)
#define I2S_CR_I2S_TXF_MASK_LEN  (1U)
#define I2S_CR_I2S_TXF_MASK_MSK  (((1U << I2S_CR_I2S_TXF_MASK_LEN) - 1) << I2S_CR_I2S_TXF_MASK_POS)
#define I2S_CR_I2S_TXF_MASK_UMSK (~(((1U << I2S_CR_I2S_TXF_MASK_LEN) - 1) << I2S_CR_I2S_TXF_MASK_POS))
#define I2S_CR_I2S_RXF_MASK      I2S_CR_I2S_RXF_MASK
#define I2S_CR_I2S_RXF_MASK_POS  (9U)
#define I2S_CR_I2S_RXF_MASK_LEN  (1U)
#define I2S_CR_I2S_RXF_MASK_MSK  (((1U << I2S_CR_I2S_RXF_MASK_LEN) - 1) << I2S_CR_I2S_RXF_MASK_POS)
#define I2S_CR_I2S_RXF_MASK_UMSK (~(((1U << I2S_CR_I2S_RXF_MASK_LEN) - 1) << I2S_CR_I2S_RXF_MASK_POS))
#define I2S_CR_I2S_FER_MASK      I2S_CR_I2S_FER_MASK
#define I2S_CR_I2S_FER_MASK_POS  (10U)
#define I2S_CR_I2S_FER_MASK_LEN  (1U)
#define I2S_CR_I2S_FER_MASK_MSK  (((1U << I2S_CR_I2S_FER_MASK_LEN) - 1) << I2S_CR_I2S_FER_MASK_POS)
#define I2S_CR_I2S_FER_MASK_UMSK (~(((1U << I2S_CR_I2S_FER_MASK_LEN) - 1) << I2S_CR_I2S_FER_MASK_POS))
#define I2S_CR_I2S_TXF_EN        I2S_CR_I2S_TXF_EN
#define I2S_CR_I2S_TXF_EN_POS    (24U)
#define I2S_CR_I2S_TXF_EN_LEN    (1U)
#define I2S_CR_I2S_TXF_EN_MSK    (((1U << I2S_CR_I2S_TXF_EN_LEN) - 1) << I2S_CR_I2S_TXF_EN_POS)
#define I2S_CR_I2S_TXF_EN_UMSK   (~(((1U << I2S_CR_I2S_TXF_EN_LEN) - 1) << I2S_CR_I2S_TXF_EN_POS))
#define I2S_CR_I2S_RXF_EN        I2S_CR_I2S_RXF_EN
#define I2S_CR_I2S_RXF_EN_POS    (25U)
#define I2S_CR_I2S_RXF_EN_LEN    (1U)
#define I2S_CR_I2S_RXF_EN_MSK    (((1U << I2S_CR_I2S_RXF_EN_LEN) - 1) << I2S_CR_I2S_RXF_EN_POS)
#define I2S_CR_I2S_RXF_EN_UMSK   (~(((1U << I2S_CR_I2S_RXF_EN_LEN) - 1) << I2S_CR_I2S_RXF_EN_POS))
#define I2S_CR_I2S_FER_EN        I2S_CR_I2S_FER_EN
#define I2S_CR_I2S_FER_EN_POS    (26U)
#define I2S_CR_I2S_FER_EN_LEN    (1U)
#define I2S_CR_I2S_FER_EN_MSK    (((1U << I2S_CR_I2S_FER_EN_LEN) - 1) << I2S_CR_I2S_FER_EN_POS)
#define I2S_CR_I2S_FER_EN_UMSK   (~(((1U << I2S_CR_I2S_FER_EN_LEN) - 1) << I2S_CR_I2S_FER_EN_POS))

/* 0x10 : i2s_bclk_config */
#define I2S_BCLK_CONFIG_OFFSET (0x10)
#define I2S_CR_BCLK_DIV_L      I2S_CR_BCLK_DIV_L
#define I2S_CR_BCLK_DIV_L_POS  (0U)
#define I2S_CR_BCLK_DIV_L_LEN  (12U)
#define I2S_CR_BCLK_DIV_L_MSK  (((1U << I2S_CR_BCLK_DIV_L_LEN) - 1) << I2S_CR_BCLK_DIV_L_POS)
#define I2S_CR_BCLK_DIV_L_UMSK (~(((1U << I2S_CR_BCLK_DIV_L_LEN) - 1) << I2S_CR_BCLK_DIV_L_POS))
#define I2S_CR_BCLK_DIV_H      I2S_CR_BCLK_DIV_H
#define I2S_CR_BCLK_DIV_H_POS  (16U)
#define I2S_CR_BCLK_DIV_H_LEN  (12U)
#define I2S_CR_BCLK_DIV_H_MSK  (((1U << I2S_CR_BCLK_DIV_H_LEN) - 1) << I2S_CR_BCLK_DIV_H_POS)
#define I2S_CR_BCLK_DIV_H_UMSK (~(((1U << I2S_CR_BCLK_DIV_H_LEN) - 1) << I2S_CR_BCLK_DIV_H_POS))

/* 0x80 : i2s_fifo_config_0 */
#define I2S_FIFO_CONFIG_0_OFFSET   (0x80)
#define I2S_DMA_TX_EN              I2S_DMA_TX_EN
#define I2S_DMA_TX_EN_POS          (0U)
#define I2S_DMA_TX_EN_LEN          (1U)
#define I2S_DMA_TX_EN_MSK          (((1U << I2S_DMA_TX_EN_LEN) - 1) << I2S_DMA_TX_EN_POS)
#define I2S_DMA_TX_EN_UMSK         (~(((1U << I2S_DMA_TX_EN_LEN) - 1) << I2S_DMA_TX_EN_POS))
#define I2S_DMA_RX_EN              I2S_DMA_RX_EN
#define I2S_DMA_RX_EN_POS          (1U)
#define I2S_DMA_RX_EN_LEN          (1U)
#define I2S_DMA_RX_EN_MSK          (((1U << I2S_DMA_RX_EN_LEN) - 1) << I2S_DMA_RX_EN_POS)
#define I2S_DMA_RX_EN_UMSK         (~(((1U << I2S_DMA_RX_EN_LEN) - 1) << I2S_DMA_RX_EN_POS))
#define I2S_TX_FIFO_CLR            I2S_TX_FIFO_CLR
#define I2S_TX_FIFO_CLR_POS        (2U)
#define I2S_TX_FIFO_CLR_LEN        (1U)
#define I2S_TX_FIFO_CLR_MSK        (((1U << I2S_TX_FIFO_CLR_LEN) - 1) << I2S_TX_FIFO_CLR_POS)
#define I2S_TX_FIFO_CLR_UMSK       (~(((1U << I2S_TX_FIFO_CLR_LEN) - 1) << I2S_TX_FIFO_CLR_POS))
#define I2S_RX_FIFO_CLR            I2S_RX_FIFO_CLR
#define I2S_RX_FIFO_CLR_POS        (3U)
#define I2S_RX_FIFO_CLR_LEN        (1U)
#define I2S_RX_FIFO_CLR_MSK        (((1U << I2S_RX_FIFO_CLR_LEN) - 1) << I2S_RX_FIFO_CLR_POS)
#define I2S_RX_FIFO_CLR_UMSK       (~(((1U << I2S_RX_FIFO_CLR_LEN) - 1) << I2S_RX_FIFO_CLR_POS))
#define I2S_TX_FIFO_OVERFLOW       I2S_TX_FIFO_OVERFLOW
#define I2S_TX_FIFO_OVERFLOW_POS   (4U)
#define I2S_TX_FIFO_OVERFLOW_LEN   (1U)
#define I2S_TX_FIFO_OVERFLOW_MSK   (((1U << I2S_TX_FIFO_OVERFLOW_LEN) - 1) << I2S_TX_FIFO_OVERFLOW_POS)
#define I2S_TX_FIFO_OVERFLOW_UMSK  (~(((1U << I2S_TX_FIFO_OVERFLOW_LEN) - 1) << I2S_TX_FIFO_OVERFLOW_POS))
#define I2S_TX_FIFO_UNDERFLOW      I2S_TX_FIFO_UNDERFLOW
#define I2S_TX_FIFO_UNDERFLOW_POS  (5U)
#define I2S_TX_FIFO_UNDERFLOW_LEN  (1U)
#define I2S_TX_FIFO_UNDERFLOW_MSK  (((1U << I2S_TX_FIFO_UNDERFLOW_LEN) - 1) << I2S_TX_FIFO_UNDERFLOW_POS)
#define I2S_TX_FIFO_UNDERFLOW_UMSK (~(((1U << I2S_TX_FIFO_UNDERFLOW_LEN) - 1) << I2S_TX_FIFO_UNDERFLOW_POS))
#define I2S_RX_FIFO_OVERFLOW       I2S_RX_FIFO_OVERFLOW
#define I2S_RX_FIFO_OVERFLOW_POS   (6U)
#define I2S_RX_FIFO_OVERFLOW_LEN   (1U)
#define I2S_RX_FIFO_OVERFLOW_MSK   (((1U << I2S_RX_FIFO_OVERFLOW_LEN) - 1) << I2S_RX_FIFO_OVERFLOW_POS)
#define I2S_RX_FIFO_OVERFLOW_UMSK  (~(((1U << I2S_RX_FIFO_OVERFLOW_LEN) - 1) << I2S_RX_FIFO_OVERFLOW_POS))
#define I2S_RX_FIFO_UNDERFLOW      I2S_RX_FIFO_UNDERFLOW
#define I2S_RX_FIFO_UNDERFLOW_POS  (7U)
#define I2S_RX_FIFO_UNDERFLOW_LEN  (1U)
#define I2S_RX_FIFO_UNDERFLOW_MSK  (((1U << I2S_RX_FIFO_UNDERFLOW_LEN) - 1) << I2S_RX_FIFO_UNDERFLOW_POS)
#define I2S_RX_FIFO_UNDERFLOW_UMSK (~(((1U << I2S_RX_FIFO_UNDERFLOW_LEN) - 1) << I2S_RX_FIFO_UNDERFLOW_POS))
#define I2S_CR_FIFO_LR_MERGE       I2S_CR_FIFO_LR_MERGE
#define I2S_CR_FIFO_LR_MERGE_POS   (8U)
#define I2S_CR_FIFO_LR_MERGE_LEN   (1U)
#define I2S_CR_FIFO_LR_MERGE_MSK   (((1U << I2S_CR_FIFO_LR_MERGE_LEN) - 1) << I2S_CR_FIFO_LR_MERGE_POS)
#define I2S_CR_FIFO_LR_MERGE_UMSK  (~(((1U << I2S_CR_FIFO_LR_MERGE_LEN) - 1) << I2S_CR_FIFO_LR_MERGE_POS))
#define I2S_CR_FIFO_LR_EXCHG       I2S_CR_FIFO_LR_EXCHG
#define I2S_CR_FIFO_LR_EXCHG_POS   (9U)
#define I2S_CR_FIFO_LR_EXCHG_LEN   (1U)
#define I2S_CR_FIFO_LR_EXCHG_MSK   (((1U << I2S_CR_FIFO_LR_EXCHG_LEN) - 1) << I2S_CR_FIFO_LR_EXCHG_POS)
#define I2S_CR_FIFO_LR_EXCHG_UMSK  (~(((1U << I2S_CR_FIFO_LR_EXCHG_LEN) - 1) << I2S_CR_FIFO_LR_EXCHG_POS))
#define I2S_CR_FIFO_24B_LJ         I2S_CR_FIFO_24B_LJ
#define I2S_CR_FIFO_24B_LJ_POS     (10U)
#define I2S_CR_FIFO_24B_LJ_LEN     (1U)
#define I2S_CR_FIFO_24B_LJ_MSK     (((1U << I2S_CR_FIFO_24B_LJ_LEN) - 1) << I2S_CR_FIFO_24B_LJ_POS)
#define I2S_CR_FIFO_24B_LJ_UMSK    (~(((1U << I2S_CR_FIFO_24B_LJ_LEN) - 1) << I2S_CR_FIFO_24B_LJ_POS))

/* 0x84 : i2s_fifo_config_1 */
#define I2S_FIFO_CONFIG_1_OFFSET (0x84)
#define I2S_TX_FIFO_CNT          I2S_TX_FIFO_CNT
#define I2S_TX_FIFO_CNT_POS      (0U)
#define I2S_TX_FIFO_CNT_LEN      (5U)
#define I2S_TX_FIFO_CNT_MSK      (((1U << I2S_TX_FIFO_CNT_LEN) - 1) << I2S_TX_FIFO_CNT_POS)
#define I2S_TX_FIFO_CNT_UMSK     (~(((1U << I2S_TX_FIFO_CNT_LEN) - 1) << I2S_TX_FIFO_CNT_POS))
#define I2S_RX_FIFO_CNT          I2S_RX_FIFO_CNT
#define I2S_RX_FIFO_CNT_POS      (8U)
#define I2S_RX_FIFO_CNT_LEN      (5U)
#define I2S_RX_FIFO_CNT_MSK      (((1U << I2S_RX_FIFO_CNT_LEN) - 1) << I2S_RX_FIFO_CNT_POS)
#define I2S_RX_FIFO_CNT_UMSK     (~(((1U << I2S_RX_FIFO_CNT_LEN) - 1) << I2S_RX_FIFO_CNT_POS))
#define I2S_TX_FIFO_TH           I2S_TX_FIFO_TH
#define I2S_TX_FIFO_TH_POS       (16U)
#define I2S_TX_FIFO_TH_LEN       (4U)
#define I2S_TX_FIFO_TH_MSK       (((1U << I2S_TX_FIFO_TH_LEN) - 1) << I2S_TX_FIFO_TH_POS)
#define I2S_TX_FIFO_TH_UMSK      (~(((1U << I2S_TX_FIFO_TH_LEN) - 1) << I2S_TX_FIFO_TH_POS))
#define I2S_RX_FIFO_TH           I2S_RX_FIFO_TH
#define I2S_RX_FIFO_TH_POS       (24U)
#define I2S_RX_FIFO_TH_LEN       (4U)
#define I2S_RX_FIFO_TH_MSK       (((1U << I2S_RX_FIFO_TH_LEN) - 1) << I2S_RX_FIFO_TH_POS)
#define I2S_RX_FIFO_TH_UMSK      (~(((1U << I2S_RX_FIFO_TH_LEN) - 1) << I2S_RX_FIFO_TH_POS))

/* 0x88 : i2s_fifo_wdata */
#define I2S_FIFO_WDATA_OFFSET (0x88)
#define I2S_FIFO_WDATA        I2S_FIFO_WDATA
#define I2S_FIFO_WDATA_POS    (0U)
#define I2S_FIFO_WDATA_LEN    (32U)
#define I2S_FIFO_WDATA_MSK    (((1U << I2S_FIFO_WDATA_LEN) - 1) << I2S_FIFO_WDATA_POS)
#define I2S_FIFO_WDATA_UMSK   (~(((1U << I2S_FIFO_WDATA_LEN) - 1) << I2S_FIFO_WDATA_POS))

/* 0x8C : i2s_fifo_rdata */
#define I2S_FIFO_RDATA_OFFSET (0x8C)
#define I2S_FIFO_RDATA        I2S_FIFO_RDATA
#define I2S_FIFO_RDATA_POS    (0U)
#define I2S_FIFO_RDATA_LEN    (32U)
#define I2S_FIFO_RDATA_MSK    (((1U << I2S_FIFO_RDATA_LEN) - 1) << I2S_FIFO_RDATA_POS)
#define I2S_FIFO_RDATA_UMSK   (~(((1U << I2S_FIFO_RDATA_LEN) - 1) << I2S_FIFO_RDATA_POS))

/* 0xFC : i2s_io_config */
#define I2S_IO_CONFIG_OFFSET     (0xFC)
#define I2S_CR_I2S_TXD_INV       I2S_CR_I2S_TXD_INV
#define I2S_CR_I2S_TXD_INV_POS   (0U)
#define I2S_CR_I2S_TXD_INV_LEN   (1U)
#define I2S_CR_I2S_TXD_INV_MSK   (((1U << I2S_CR_I2S_TXD_INV_LEN) - 1) << I2S_CR_I2S_TXD_INV_POS)
#define I2S_CR_I2S_TXD_INV_UMSK  (~(((1U << I2S_CR_I2S_TXD_INV_LEN) - 1) << I2S_CR_I2S_TXD_INV_POS))
#define I2S_CR_I2S_RXD_INV       I2S_CR_I2S_RXD_INV
#define I2S_CR_I2S_RXD_INV_POS   (1U)
#define I2S_CR_I2S_RXD_INV_LEN   (1U)
#define I2S_CR_I2S_RXD_INV_MSK   (((1U << I2S_CR_I2S_RXD_INV_LEN) - 1) << I2S_CR_I2S_RXD_INV_POS)
#define I2S_CR_I2S_RXD_INV_UMSK  (~(((1U << I2S_CR_I2S_RXD_INV_LEN) - 1) << I2S_CR_I2S_RXD_INV_POS))
#define I2S_CR_I2S_FS_INV        I2S_CR_I2S_FS_INV
#define I2S_CR_I2S_FS_INV_POS    (2U)
#define I2S_CR_I2S_FS_INV_LEN    (1U)
#define I2S_CR_I2S_FS_INV_MSK    (((1U << I2S_CR_I2S_FS_INV_LEN) - 1) << I2S_CR_I2S_FS_INV_POS)
#define I2S_CR_I2S_FS_INV_UMSK   (~(((1U << I2S_CR_I2S_FS_INV_LEN) - 1) << I2S_CR_I2S_FS_INV_POS))
#define I2S_CR_I2S_BCLK_INV      I2S_CR_I2S_BCLK_INV
#define I2S_CR_I2S_BCLK_INV_POS  (3U)
#define I2S_CR_I2S_BCLK_INV_LEN  (1U)
#define I2S_CR_I2S_BCLK_INV_MSK  (((1U << I2S_CR_I2S_BCLK_INV_LEN) - 1) << I2S_CR_I2S_BCLK_INV_POS)
#define I2S_CR_I2S_BCLK_INV_UMSK (~(((1U << I2S_CR_I2S_BCLK_INV_LEN) - 1) << I2S_CR_I2S_BCLK_INV_POS))
#define I2S_CR_DEG_CNT           I2S_CR_DEG_CNT
#define I2S_CR_DEG_CNT_POS       (4U)
#define I2S_CR_DEG_CNT_LEN       (3U)
#define I2S_CR_DEG_CNT_MSK       (((1U << I2S_CR_DEG_CNT_LEN) - 1) << I2S_CR_DEG_CNT_POS)
#define I2S_CR_DEG_CNT_UMSK      (~(((1U << I2S_CR_DEG_CNT_LEN) - 1) << I2S_CR_DEG_CNT_POS))
#define I2S_CR_DEG_EN            I2S_CR_DEG_EN
#define I2S_CR_DEG_EN_POS        (7U)
#define I2S_CR_DEG_EN_LEN        (1U)
#define I2S_CR_DEG_EN_MSK        (((1U << I2S_CR_DEG_EN_LEN) - 1) << I2S_CR_DEG_EN_POS)
#define I2S_CR_DEG_EN_UMSK       (~(((1U << I2S_CR_DEG_EN_LEN) - 1) << I2S_CR_DEG_EN_POS))

struct i2s_reg {
    /* 0x0 : i2s_config */
    union {
        struct {
            uint32_t cr_i2s_m_en    : 1; /* [    0],        r/w,        0x0 */
            uint32_t cr_i2s_s_en    : 1; /* [    1],        r/w,        0x0 */
            uint32_t cr_i2s_txd_en  : 1; /* [    2],        r/w,        0x0 */
            uint32_t cr_i2s_rxd_en  : 1; /* [    3],        r/w,        0x0 */
            uint32_t cr_mono_mode   : 1; /* [    4],        r/w,        0x0 */
            uint32_t cr_mute_mode   : 1; /* [    5],        r/w,        0x0 */
            uint32_t cr_fs_1t_mode  : 1; /* [    6],        r/w,        0x0 */
            uint32_t cr_fs_ch_cnt   : 2; /* [ 8: 7],        r/w,        0x0 */
            uint32_t reserved_9_11  : 3; /* [11: 9],       rsvd,        0x0 */
            uint32_t cr_frame_size  : 2; /* [13:12],        r/w,        0x1 */
            uint32_t cr_data_size   : 2; /* [15:14],        r/w,        0x1 */
            uint32_t cr_i2s_mode    : 2; /* [17:16],        r/w,        0x0 */
            uint32_t cr_endian      : 1; /* [   18],        r/w,        0x0 */
            uint32_t cr_mono_rx_ch  : 1; /* [   19],        r/w,        0x0 */
            uint32_t cr_ofs_cnt     : 5; /* [24:20],        r/w,        0x0 */
            uint32_t cr_ofs_en      : 1; /* [   25],        r/w,        0x0 */
            uint32_t reserved_26_31 : 6; /* [31:26],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } i2s_config;

    /* 0x4 : i2s_int_sts */
    union {
        struct {
            uint32_t i2s_txf_int     : 1;  /* [    0],          r,        0x1 */
            uint32_t i2s_rxf_int     : 1;  /* [    1],          r,        0x0 */
            uint32_t i2s_fer_int     : 1;  /* [    2],          r,        0x0 */
            uint32_t reserved_3_7    : 5;  /* [ 7: 3],       rsvd,        0x0 */
            uint32_t cr_i2s_txf_mask : 1;  /* [    8],        r/w,        0x1 */
            uint32_t cr_i2s_rxf_mask : 1;  /* [    9],        r/w,        0x1 */
            uint32_t cr_i2s_fer_mask : 1;  /* [   10],        r/w,        0x1 */
            uint32_t reserved_11_23  : 13; /* [23:11],       rsvd,        0x0 */
            uint32_t cr_i2s_txf_en   : 1;  /* [   24],        r/w,        0x1 */
            uint32_t cr_i2s_rxf_en   : 1;  /* [   25],        r/w,        0x1 */
            uint32_t cr_i2s_fer_en   : 1;  /* [   26],        r/w,        0x1 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } i2s_int_sts;

    /* 0x8  reserved */
    uint8_t RESERVED0x8[8];

    /* 0x10 : i2s_bclk_config */
    union {
        struct {
            uint32_t cr_bclk_div_l  : 12; /* [11: 0],        r/w,        0x1 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t cr_bclk_div_h  : 12; /* [27:16],        r/w,        0x1 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } i2s_bclk_config;

    /* 0x14  reserved */
    uint8_t RESERVED0x14[108];

    /* 0x80 : i2s_fifo_config_0 */
    union {
        struct {
            uint32_t i2s_dma_tx_en     : 1;  /* [    0],        r/w,        0x0 */
            uint32_t i2s_dma_rx_en     : 1;  /* [    1],        r/w,        0x0 */
            uint32_t tx_fifo_clr       : 1;  /* [    2],        w1c,        0x0 */
            uint32_t rx_fifo_clr       : 1;  /* [    3],        w1c,        0x0 */
            uint32_t tx_fifo_overflow  : 1;  /* [    4],          r,        0x0 */
            uint32_t tx_fifo_underflow : 1;  /* [    5],          r,        0x0 */
            uint32_t rx_fifo_overflow  : 1;  /* [    6],          r,        0x0 */
            uint32_t rx_fifo_underflow : 1;  /* [    7],          r,        0x0 */
            uint32_t cr_fifo_lr_merge  : 1;  /* [    8],        r/w,        0x0 */
            uint32_t cr_fifo_lr_exchg  : 1;  /* [    9],        r/w,        0x0 */
            uint32_t cr_fifo_24b_lj    : 1;  /* [   10],        r/w,        0x0 */
            uint32_t reserved_11_31    : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } i2s_fifo_config_0;

    /* 0x84 : i2s_fifo_config_1 */
    union {
        struct {
            uint32_t tx_fifo_cnt    : 5; /* [ 4: 0],          r,       0x10 */
            uint32_t reserved_5_7   : 3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t rx_fifo_cnt    : 5; /* [12: 8],          r,        0x0 */
            uint32_t reserved_13_15 : 3; /* [15:13],       rsvd,        0x0 */
            uint32_t tx_fifo_th     : 4; /* [19:16],        r/w,        0x0 */
            uint32_t reserved_20_23 : 4; /* [23:20],       rsvd,        0x0 */
            uint32_t rx_fifo_th     : 4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4; /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } i2s_fifo_config_1;

    /* 0x88 : i2s_fifo_wdata */
    union {
        struct {
            uint32_t i2s_fifo_wdata : 32; /* [31: 0],          w,          x */
        } BF;
        uint32_t WORD;
    } i2s_fifo_wdata;

    /* 0x8C : i2s_fifo_rdata */
    union {
        struct {
            uint32_t i2s_fifo_rdata : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } i2s_fifo_rdata;

    /* 0x90  reserved */
    uint8_t RESERVED0x90[108];

    /* 0xFC : i2s_io_config */
    union {
        struct {
            uint32_t cr_i2s_txd_inv  : 1;  /* [    0],        r/w,        0x0 */
            uint32_t cr_i2s_rxd_inv  : 1;  /* [    1],        r/w,        0x0 */
            uint32_t cr_i2s_fs_inv   : 1;  /* [    2],        r/w,        0x0 */
            uint32_t cr_i2s_bclk_inv : 1;  /* [    3],        r/w,        0x0 */
            uint32_t cr_deg_cnt      : 3;  /* [ 6: 4],        r/w,        0x0 */
            uint32_t cr_deg_en       : 1;  /* [    7],        r/w,        0x0 */
            uint32_t reserved_8_31   : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } i2s_io_config;
};

typedef volatile struct i2s_reg i2s_reg_t;

#endif /* __I2S_REG_H__ */
