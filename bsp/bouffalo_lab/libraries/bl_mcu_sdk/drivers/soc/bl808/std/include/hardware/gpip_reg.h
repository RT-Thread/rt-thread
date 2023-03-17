/**
  ******************************************************************************
  * @file    gpip_reg.h
  * @version V1.2
  * @date    2022-03-7
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2022 Bouffalo Lab</center></h2>
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
#ifndef __GPIP_REG_H__
#define __GPIP_REG_H__

#include "bl808.h"

/* 0x0 : gpadc_config */
#define GPIP_GPADC_CONFIG_OFFSET           (0x0)
#define GPIP_GPADC_DMA_EN                  GPIP_GPADC_DMA_EN
#define GPIP_GPADC_DMA_EN_POS              (0U)
#define GPIP_GPADC_DMA_EN_LEN              (1U)
#define GPIP_GPADC_DMA_EN_MSK              (((1U << GPIP_GPADC_DMA_EN_LEN) - 1) << GPIP_GPADC_DMA_EN_POS)
#define GPIP_GPADC_DMA_EN_UMSK             (~(((1U << GPIP_GPADC_DMA_EN_LEN) - 1) << GPIP_GPADC_DMA_EN_POS))
#define GPIP_GPADC_FIFO_CLR                GPIP_GPADC_FIFO_CLR
#define GPIP_GPADC_FIFO_CLR_POS            (1U)
#define GPIP_GPADC_FIFO_CLR_LEN            (1U)
#define GPIP_GPADC_FIFO_CLR_MSK            (((1U << GPIP_GPADC_FIFO_CLR_LEN) - 1) << GPIP_GPADC_FIFO_CLR_POS)
#define GPIP_GPADC_FIFO_CLR_UMSK           (~(((1U << GPIP_GPADC_FIFO_CLR_LEN) - 1) << GPIP_GPADC_FIFO_CLR_POS))
#define GPIP_GPADC_FIFO_NE                 GPIP_GPADC_FIFO_NE
#define GPIP_GPADC_FIFO_NE_POS             (2U)
#define GPIP_GPADC_FIFO_NE_LEN             (1U)
#define GPIP_GPADC_FIFO_NE_MSK             (((1U << GPIP_GPADC_FIFO_NE_LEN) - 1) << GPIP_GPADC_FIFO_NE_POS)
#define GPIP_GPADC_FIFO_NE_UMSK            (~(((1U << GPIP_GPADC_FIFO_NE_LEN) - 1) << GPIP_GPADC_FIFO_NE_POS))
#define GPIP_GPADC_FIFO_FULL               GPIP_GPADC_FIFO_FULL
#define GPIP_GPADC_FIFO_FULL_POS           (3U)
#define GPIP_GPADC_FIFO_FULL_LEN           (1U)
#define GPIP_GPADC_FIFO_FULL_MSK           (((1U << GPIP_GPADC_FIFO_FULL_LEN) - 1) << GPIP_GPADC_FIFO_FULL_POS)
#define GPIP_GPADC_FIFO_FULL_UMSK          (~(((1U << GPIP_GPADC_FIFO_FULL_LEN) - 1) << GPIP_GPADC_FIFO_FULL_POS))
#define GPIP_GPADC_RDY                     GPIP_GPADC_RDY
#define GPIP_GPADC_RDY_POS                 (4U)
#define GPIP_GPADC_RDY_LEN                 (1U)
#define GPIP_GPADC_RDY_MSK                 (((1U << GPIP_GPADC_RDY_LEN) - 1) << GPIP_GPADC_RDY_POS)
#define GPIP_GPADC_RDY_UMSK                (~(((1U << GPIP_GPADC_RDY_LEN) - 1) << GPIP_GPADC_RDY_POS))
#define GPIP_GPADC_FIFO_OVERRUN            GPIP_GPADC_FIFO_OVERRUN
#define GPIP_GPADC_FIFO_OVERRUN_POS        (5U)
#define GPIP_GPADC_FIFO_OVERRUN_LEN        (1U)
#define GPIP_GPADC_FIFO_OVERRUN_MSK        (((1U << GPIP_GPADC_FIFO_OVERRUN_LEN) - 1) << GPIP_GPADC_FIFO_OVERRUN_POS)
#define GPIP_GPADC_FIFO_OVERRUN_UMSK       (~(((1U << GPIP_GPADC_FIFO_OVERRUN_LEN) - 1) << GPIP_GPADC_FIFO_OVERRUN_POS))
#define GPIP_GPADC_FIFO_UNDERRUN           GPIP_GPADC_FIFO_UNDERRUN
#define GPIP_GPADC_FIFO_UNDERRUN_POS       (6U)
#define GPIP_GPADC_FIFO_UNDERRUN_LEN       (1U)
#define GPIP_GPADC_FIFO_UNDERRUN_MSK       (((1U << GPIP_GPADC_FIFO_UNDERRUN_LEN) - 1) << GPIP_GPADC_FIFO_UNDERRUN_POS)
#define GPIP_GPADC_FIFO_UNDERRUN_UMSK      (~(((1U << GPIP_GPADC_FIFO_UNDERRUN_LEN) - 1) << GPIP_GPADC_FIFO_UNDERRUN_POS))
#define GPIP_GPADC_RDY_CLR                 GPIP_GPADC_RDY_CLR
#define GPIP_GPADC_RDY_CLR_POS             (8U)
#define GPIP_GPADC_RDY_CLR_LEN             (1U)
#define GPIP_GPADC_RDY_CLR_MSK             (((1U << GPIP_GPADC_RDY_CLR_LEN) - 1) << GPIP_GPADC_RDY_CLR_POS)
#define GPIP_GPADC_RDY_CLR_UMSK            (~(((1U << GPIP_GPADC_RDY_CLR_LEN) - 1) << GPIP_GPADC_RDY_CLR_POS))
#define GPIP_GPADC_FIFO_OVERRUN_CLR        GPIP_GPADC_FIFO_OVERRUN_CLR
#define GPIP_GPADC_FIFO_OVERRUN_CLR_POS    (9U)
#define GPIP_GPADC_FIFO_OVERRUN_CLR_LEN    (1U)
#define GPIP_GPADC_FIFO_OVERRUN_CLR_MSK    (((1U << GPIP_GPADC_FIFO_OVERRUN_CLR_LEN) - 1) << GPIP_GPADC_FIFO_OVERRUN_CLR_POS)
#define GPIP_GPADC_FIFO_OVERRUN_CLR_UMSK   (~(((1U << GPIP_GPADC_FIFO_OVERRUN_CLR_LEN) - 1) << GPIP_GPADC_FIFO_OVERRUN_CLR_POS))
#define GPIP_GPADC_FIFO_UNDERRUN_CLR       GPIP_GPADC_FIFO_UNDERRUN_CLR
#define GPIP_GPADC_FIFO_UNDERRUN_CLR_POS   (10U)
#define GPIP_GPADC_FIFO_UNDERRUN_CLR_LEN   (1U)
#define GPIP_GPADC_FIFO_UNDERRUN_CLR_MSK   (((1U << GPIP_GPADC_FIFO_UNDERRUN_CLR_LEN) - 1) << GPIP_GPADC_FIFO_UNDERRUN_CLR_POS)
#define GPIP_GPADC_FIFO_UNDERRUN_CLR_UMSK  (~(((1U << GPIP_GPADC_FIFO_UNDERRUN_CLR_LEN) - 1) << GPIP_GPADC_FIFO_UNDERRUN_CLR_POS))
#define GPIP_GPADC_RDY_MASK                GPIP_GPADC_RDY_MASK
#define GPIP_GPADC_RDY_MASK_POS            (12U)
#define GPIP_GPADC_RDY_MASK_LEN            (1U)
#define GPIP_GPADC_RDY_MASK_MSK            (((1U << GPIP_GPADC_RDY_MASK_LEN) - 1) << GPIP_GPADC_RDY_MASK_POS)
#define GPIP_GPADC_RDY_MASK_UMSK           (~(((1U << GPIP_GPADC_RDY_MASK_LEN) - 1) << GPIP_GPADC_RDY_MASK_POS))
#define GPIP_GPADC_FIFO_OVERRUN_MASK       GPIP_GPADC_FIFO_OVERRUN_MASK
#define GPIP_GPADC_FIFO_OVERRUN_MASK_POS   (13U)
#define GPIP_GPADC_FIFO_OVERRUN_MASK_LEN   (1U)
#define GPIP_GPADC_FIFO_OVERRUN_MASK_MSK   (((1U << GPIP_GPADC_FIFO_OVERRUN_MASK_LEN) - 1) << GPIP_GPADC_FIFO_OVERRUN_MASK_POS)
#define GPIP_GPADC_FIFO_OVERRUN_MASK_UMSK  (~(((1U << GPIP_GPADC_FIFO_OVERRUN_MASK_LEN) - 1) << GPIP_GPADC_FIFO_OVERRUN_MASK_POS))
#define GPIP_GPADC_FIFO_UNDERRUN_MASK      GPIP_GPADC_FIFO_UNDERRUN_MASK
#define GPIP_GPADC_FIFO_UNDERRUN_MASK_POS  (14U)
#define GPIP_GPADC_FIFO_UNDERRUN_MASK_LEN  (1U)
#define GPIP_GPADC_FIFO_UNDERRUN_MASK_MSK  (((1U << GPIP_GPADC_FIFO_UNDERRUN_MASK_LEN) - 1) << GPIP_GPADC_FIFO_UNDERRUN_MASK_POS)
#define GPIP_GPADC_FIFO_UNDERRUN_MASK_UMSK (~(((1U << GPIP_GPADC_FIFO_UNDERRUN_MASK_LEN) - 1) << GPIP_GPADC_FIFO_UNDERRUN_MASK_POS))
#define GPIP_GPADC_FIFO_DATA_COUNT         GPIP_GPADC_FIFO_DATA_COUNT
#define GPIP_GPADC_FIFO_DATA_COUNT_POS     (16U)
#define GPIP_GPADC_FIFO_DATA_COUNT_LEN     (6U)
#define GPIP_GPADC_FIFO_DATA_COUNT_MSK     (((1U << GPIP_GPADC_FIFO_DATA_COUNT_LEN) - 1) << GPIP_GPADC_FIFO_DATA_COUNT_POS)
#define GPIP_GPADC_FIFO_DATA_COUNT_UMSK    (~(((1U << GPIP_GPADC_FIFO_DATA_COUNT_LEN) - 1) << GPIP_GPADC_FIFO_DATA_COUNT_POS))
#define GPIP_GPADC_FIFO_THL                GPIP_GPADC_FIFO_THL
#define GPIP_GPADC_FIFO_THL_POS            (22U)
#define GPIP_GPADC_FIFO_THL_LEN            (2U)
#define GPIP_GPADC_FIFO_THL_MSK            (((1U << GPIP_GPADC_FIFO_THL_LEN) - 1) << GPIP_GPADC_FIFO_THL_POS)
#define GPIP_GPADC_FIFO_THL_UMSK           (~(((1U << GPIP_GPADC_FIFO_THL_LEN) - 1) << GPIP_GPADC_FIFO_THL_POS))

/* 0x4 : gpadc_dma_rdata */
#define GPIP_GPADC_DMA_RDATA_OFFSET (0x4)
#define GPIP_GPADC_DMA_RDATA        GPIP_GPADC_DMA_RDATA
#define GPIP_GPADC_DMA_RDATA_POS    (0U)
#define GPIP_GPADC_DMA_RDATA_LEN    (26U)
#define GPIP_GPADC_DMA_RDATA_MSK    (((1U << GPIP_GPADC_DMA_RDATA_LEN) - 1) << GPIP_GPADC_DMA_RDATA_POS)
#define GPIP_GPADC_DMA_RDATA_UMSK   (~(((1U << GPIP_GPADC_DMA_RDATA_LEN) - 1) << GPIP_GPADC_DMA_RDATA_POS))

/* 0x20 : gpadc_pir_train */
#define GPIP_GPADC_PIR_TRAIN_OFFSET (0x20)
#define GPIP_PIR_EXTEND             GPIP_PIR_EXTEND
#define GPIP_PIR_EXTEND_POS         (0U)
#define GPIP_PIR_EXTEND_LEN         (5U)
#define GPIP_PIR_EXTEND_MSK         (((1U<<GPIP_PIR_EXTEND_LEN)-1)<<GPIP_PIR_EXTEND_POS)
#define GPIP_PIR_EXTEND_UMSK        (~(((1U<<GPIP_PIR_EXTEND_LEN)-1)<<GPIP_PIR_EXTEND_POS))
#define GPIP_PIR_CNT_V              GPIP_PIR_CNT_V
#define GPIP_PIR_CNT_V_POS          (8U)
#define GPIP_PIR_CNT_V_LEN          (5U)
#define GPIP_PIR_CNT_V_MSK          (((1U<<GPIP_PIR_CNT_V_LEN)-1)<<GPIP_PIR_CNT_V_POS)
#define GPIP_PIR_CNT_V_UMSK         (~(((1U<<GPIP_PIR_CNT_V_LEN)-1)<<GPIP_PIR_CNT_V_POS))
#define GPIP_PIR_TRAIN              GPIP_PIR_TRAIN
#define GPIP_PIR_TRAIN_POS          (16U)
#define GPIP_PIR_TRAIN_LEN          (1U)
#define GPIP_PIR_TRAIN_MSK          (((1U<<GPIP_PIR_TRAIN_LEN)-1)<<GPIP_PIR_TRAIN_POS)
#define GPIP_PIR_TRAIN_UMSK         (~(((1U<<GPIP_PIR_TRAIN_LEN)-1)<<GPIP_PIR_TRAIN_POS))
#define GPIP_PIR_STOP               GPIP_PIR_STOP
#define GPIP_PIR_STOP_POS           (17U)
#define GPIP_PIR_STOP_LEN           (1U)
#define GPIP_PIR_STOP_MSK           (((1U<<GPIP_PIR_STOP_LEN)-1)<<GPIP_PIR_STOP_POS)
#define GPIP_PIR_STOP_UMSK          (~(((1U<<GPIP_PIR_STOP_LEN)-1)<<GPIP_PIR_STOP_POS))
/* 0x40 : gpdac_config */
#define GPIP_GPDAC_CONFIG_OFFSET (0x40)
#define GPIP_GPDAC_EN            GPIP_GPDAC_EN
#define GPIP_GPDAC_EN_POS        (0U)
#define GPIP_GPDAC_EN_LEN        (1U)
#define GPIP_GPDAC_EN_MSK        (((1U << GPIP_GPDAC_EN_LEN) - 1) << GPIP_GPDAC_EN_POS)
#define GPIP_GPDAC_EN_UMSK       (~(((1U << GPIP_GPDAC_EN_LEN) - 1) << GPIP_GPDAC_EN_POS))
#define GPIP_GPDAC_MODE          GPIP_GPDAC_MODE
#define GPIP_GPDAC_MODE_POS      (8U)
#define GPIP_GPDAC_MODE_LEN      (3U)
#define GPIP_GPDAC_MODE_MSK      (((1U << GPIP_GPDAC_MODE_LEN) - 1) << GPIP_GPDAC_MODE_POS)
#define GPIP_GPDAC_MODE_UMSK     (~(((1U << GPIP_GPDAC_MODE_LEN) - 1) << GPIP_GPDAC_MODE_POS))
#define GPIP_GPDAC_CH_A_SEL      GPIP_GPDAC_CH_A_SEL
#define GPIP_GPDAC_CH_A_SEL_POS  (16U)
#define GPIP_GPDAC_CH_A_SEL_LEN  (4U)
#define GPIP_GPDAC_CH_A_SEL_MSK  (((1U << GPIP_GPDAC_CH_A_SEL_LEN) - 1) << GPIP_GPDAC_CH_A_SEL_POS)
#define GPIP_GPDAC_CH_A_SEL_UMSK (~(((1U << GPIP_GPDAC_CH_A_SEL_LEN) - 1) << GPIP_GPDAC_CH_A_SEL_POS))
#define GPIP_GPDAC_CH_B_SEL      GPIP_GPDAC_CH_B_SEL
#define GPIP_GPDAC_CH_B_SEL_POS  (20U)
#define GPIP_GPDAC_CH_B_SEL_LEN  (4U)
#define GPIP_GPDAC_CH_B_SEL_MSK  (((1U << GPIP_GPDAC_CH_B_SEL_LEN) - 1) << GPIP_GPDAC_CH_B_SEL_POS)
#define GPIP_GPDAC_CH_B_SEL_UMSK (~(((1U << GPIP_GPDAC_CH_B_SEL_LEN) - 1) << GPIP_GPDAC_CH_B_SEL_POS))

/* 0x44 : gpdac_dma_config */
#define GPIP_GPDAC_DMA_CONFIG_OFFSET (0x44)
#define GPIP_GPDAC_DMA_TX_EN         GPIP_GPDAC_DMA_TX_EN
#define GPIP_GPDAC_DMA_TX_EN_POS     (0U)
#define GPIP_GPDAC_DMA_TX_EN_LEN     (1U)
#define GPIP_GPDAC_DMA_TX_EN_MSK     (((1U << GPIP_GPDAC_DMA_TX_EN_LEN) - 1) << GPIP_GPDAC_DMA_TX_EN_POS)
#define GPIP_GPDAC_DMA_TX_EN_UMSK    (~(((1U << GPIP_GPDAC_DMA_TX_EN_LEN) - 1) << GPIP_GPDAC_DMA_TX_EN_POS))
#define GPIP_GPDAC_DMA_INV_MSB       GPIP_GPDAC_DMA_INV_MSB
#define GPIP_GPDAC_DMA_INV_MSB_POS   (1U)
#define GPIP_GPDAC_DMA_INV_MSB_LEN   (1U)
#define GPIP_GPDAC_DMA_INV_MSB_MSK   (((1U<<GPIP_GPDAC_DMA_INV_MSB_LEN)-1)<<GPIP_GPDAC_DMA_INV_MSB_POS)
#define GPIP_GPDAC_DMA_INV_MSB_UMSK  (~(((1U<<GPIP_GPDAC_DMA_INV_MSB_LEN)-1)<<GPIP_GPDAC_DMA_INV_MSB_POS))
#define GPIP_GPDAC_DMA_FORMAT        GPIP_GPDAC_DMA_FORMAT
#define GPIP_GPDAC_DMA_FORMAT_POS    (4U)
#define GPIP_GPDAC_DMA_FORMAT_LEN    (4U)
#define GPIP_GPDAC_DMA_FORMAT_MSK    (((1U << GPIP_GPDAC_DMA_FORMAT_LEN) - 1) << GPIP_GPDAC_DMA_FORMAT_POS)
#define GPIP_GPDAC_DMA_FORMAT_UMSK   (~(((1U << GPIP_GPDAC_DMA_FORMAT_LEN) - 1) << GPIP_GPDAC_DMA_FORMAT_POS))

/* 0x48 : gpdac_dma_wdata */
#define GPIP_GPDAC_DMA_WDATA_OFFSET (0x48)
#define GPIP_GPDAC_DMA_WDATA        GPIP_GPDAC_DMA_WDATA
#define GPIP_GPDAC_DMA_WDATA_POS    (0U)
#define GPIP_GPDAC_DMA_WDATA_LEN    (32U)
#define GPIP_GPDAC_DMA_WDATA_MSK    (((1U << GPIP_GPDAC_DMA_WDATA_LEN) - 1) << GPIP_GPDAC_DMA_WDATA_POS)
#define GPIP_GPDAC_DMA_WDATA_UMSK   (~(((1U << GPIP_GPDAC_DMA_WDATA_LEN) - 1) << GPIP_GPDAC_DMA_WDATA_POS))

/* 0x4C : gpdac_tx_fifo_status */
#define GPIP_GPDAC_TX_FIFO_STATUS_OFFSET (0x4C)
#define GPIP_TX_FIFO_EMPTY               GPIP_TX_FIFO_EMPTY
#define GPIP_TX_FIFO_EMPTY_POS           (0U)
#define GPIP_TX_FIFO_EMPTY_LEN           (1U)
#define GPIP_TX_FIFO_EMPTY_MSK           (((1U << GPIP_TX_FIFO_EMPTY_LEN) - 1) << GPIP_TX_FIFO_EMPTY_POS)
#define GPIP_TX_FIFO_EMPTY_UMSK          (~(((1U << GPIP_TX_FIFO_EMPTY_LEN) - 1) << GPIP_TX_FIFO_EMPTY_POS))
#define GPIP_TX_FIFO_FULL                GPIP_TX_FIFO_FULL
#define GPIP_TX_FIFO_FULL_POS            (1U)
#define GPIP_TX_FIFO_FULL_LEN            (1U)
#define GPIP_TX_FIFO_FULL_MSK            (((1U << GPIP_TX_FIFO_FULL_LEN) - 1) << GPIP_TX_FIFO_FULL_POS)
#define GPIP_TX_FIFO_FULL_UMSK           (~(((1U << GPIP_TX_FIFO_FULL_LEN) - 1) << GPIP_TX_FIFO_FULL_POS))
#define GPIP_TX_CS                       GPIP_TX_CS
#define GPIP_TX_CS_POS                   (2U)
#define GPIP_TX_CS_LEN                   (2U)
#define GPIP_TX_CS_MSK                   (((1U << GPIP_TX_CS_LEN) - 1) << GPIP_TX_CS_POS)
#define GPIP_TX_CS_UMSK                  (~(((1U << GPIP_TX_CS_LEN) - 1) << GPIP_TX_CS_POS))
#define GPIP_TXFIFORDPTR                 GPIP_TXFIFORDPTR
#define GPIP_TXFIFORDPTR_POS             (4U)
#define GPIP_TXFIFORDPTR_LEN             (4U)
#define GPIP_TXFIFORDPTR_MSK             (((1U << GPIP_TXFIFORDPTR_LEN) - 1) << GPIP_TXFIFORDPTR_POS)
#define GPIP_TXFIFORDPTR_UMSK            (~(((1U << GPIP_TXFIFORDPTR_LEN) - 1) << GPIP_TXFIFORDPTR_POS))
#define GPIP_TXFIFOWRPTR                 GPIP_TXFIFOWRPTR
#define GPIP_TXFIFOWRPTR_POS             (8U)
#define GPIP_TXFIFOWRPTR_LEN             (2U)
#define GPIP_TXFIFOWRPTR_MSK             (((1U << GPIP_TXFIFOWRPTR_LEN) - 1) << GPIP_TXFIFOWRPTR_POS)
#define GPIP_TXFIFOWRPTR_UMSK            (~(((1U << GPIP_TXFIFOWRPTR_LEN) - 1) << GPIP_TXFIFOWRPTR_POS))

struct gpip_reg {
    /* 0x0 : gpadc_config */
    union {
        struct
        {
            uint32_t gpadc_dma_en             : 1; /* [    0],        r/w,        0x0 */
            uint32_t gpadc_fifo_clr           : 1; /* [    1],        w1c,        0x0 */
            uint32_t gpadc_fifo_ne            : 1; /* [    2],          r,        0x0 */
            uint32_t gpadc_fifo_full          : 1; /* [    3],          r,        0x0 */
            uint32_t gpadc_rdy                : 1; /* [    4],          r,        0x0 */
            uint32_t gpadc_fifo_overrun       : 1; /* [    5],          r,        0x0 */
            uint32_t gpadc_fifo_underrun      : 1; /* [    6],          r,        0x0 */
            uint32_t reserved_7               : 1; /* [    7],       rsvd,        0x0 */
            uint32_t gpadc_rdy_clr            : 1; /* [    8],        r/w,        0x0 */
            uint32_t gpadc_fifo_overrun_clr   : 1; /* [    9],        r/w,        0x0 */
            uint32_t gpadc_fifo_underrun_clr  : 1; /* [   10],        r/w,        0x0 */
            uint32_t reserved_11              : 1; /* [   11],       rsvd,        0x0 */
            uint32_t gpadc_rdy_mask           : 1; /* [   12],        r/w,        0x0 */
            uint32_t gpadc_fifo_overrun_mask  : 1; /* [   13],        r/w,        0x0 */
            uint32_t gpadc_fifo_underrun_mask : 1; /* [   14],        r/w,        0x0 */
            uint32_t reserved_15              : 1; /* [   15],       rsvd,        0x0 */
            uint32_t gpadc_fifo_data_count    : 6; /* [21:16],          r,        0x0 */
            uint32_t gpadc_fifo_thl           : 2; /* [23:22],        r/w,        0x0 */
            uint32_t rsvd_31_24               : 8; /* [31:24],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } gpadc_config;

    /* 0x4 : gpadc_dma_rdata */
    union {
        struct
        {
            uint32_t gpadc_dma_rdata : 26; /* [25: 0],          r,        0x0 */
            uint32_t rsvd_31_26      : 6;  /* [31:26],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } gpadc_dma_rdata;

    /* 0x8  reserved */
    uint8_t RESERVED0x8[24];

    /* 0x20 : gpadc_pir_train */
    union {
        struct {
            uint32_t pir_extend               :  5; /* [ 4: 0],        r/w,        0xf */
            uint32_t reserved_5_7             :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t pir_cnt_v                :  5; /* [12: 8],          r,        0x0 */
            uint32_t reserved_13_15           :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t pir_train                :  1; /* [   16],        r/w,        0x0 */
            uint32_t pir_stop                 :  1; /* [   17],          r,        0x0 */
            uint32_t reserved_18_31           : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_pir_train;

    /* 0x24  reserved */
    uint8_t RESERVED0x24[28];
    /* 0x40 : gpdac_config */
    union {
        struct
        {
            uint32_t gpdac_en       : 1; /* [    0],        r/w,        0x0 */

            uint32_t reserved_1_7   : 7; /* [ 7: 1],       rsvd,        0x0 */
            uint32_t gpdac_mode     : 3; /* [10: 8],        r/w,        0x0 */
            uint32_t reserved_11_15 : 5; /* [15:11],       rsvd,        0x0 */
            uint32_t gpdac_ch_a_sel : 4; /* [19:16],        r/w,        0x0 */
            uint32_t gpdac_ch_b_sel : 4; /* [23:20],        r/w,        0x0 */
            uint32_t rsvd_31_24     : 8; /* [31:24],       rsvd,        0xd */
        } BF;
        uint32_t WORD;
    } gpdac_config;

    /* 0x44 : gpdac_dma_config */
    union {
        struct
        {
            uint32_t gpdac_dma_tx_en  :  1; /* [    0],        r/w,        0x0 */
            uint32_t gpdac_dma_inv_msb:  1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_3     :  2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t gpdac_dma_format :  4; /* [ 7: 4],        r/w,        0x0 */
            uint32_t reserved_8_31    : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } gpdac_dma_config;

    /* 0x48 : gpdac_dma_wdata */
    union {
        struct
        {
            uint32_t gpdac_dma_wdata : 32; /* [31: 0],          w,          x */
        } BF;
        uint32_t WORD;
    } gpdac_dma_wdata;

    /* 0x4C : gpdac_tx_fifo_status */
    union {
        struct
        {
            uint32_t tx_fifo_empty  : 1;  /* [    0],          r,        0x0 */
            uint32_t tx_fifo_full   : 1;  /* [    1],          r,        0x0 */
            uint32_t tx_cs          : 2;  /* [ 3: 2],          r,        0x0 */
            uint32_t TxFifoRdPtr    : 4;  /* [ 7: 4],          r,        0x8 */
            uint32_t TxFifoWrPtr    : 2;  /* [ 9: 8],          r,        0x0 */
            uint32_t reserved_10_31 : 22; /* [31:10],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } gpdac_tx_fifo_status;
};

typedef volatile struct gpip_reg gpip_reg_t;

#endif /* __GPIP_REG_H__ */
