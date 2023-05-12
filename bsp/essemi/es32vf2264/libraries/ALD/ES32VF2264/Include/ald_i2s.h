/**
  *********************************************************************************
  *
  * @file    ald_i2s.c
  * @brief   Header file of I2S module driver.
  *
  * @version V1.0
  * @date    09 Mar. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          09 Mar. 2023    Lisq            The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  **********************************************************************************
  */

#ifndef __ALD_I2S_H__
#define __ALD_I2S_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "ald_utils.h"
#include "ald_dma.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @addtogroup I2S
  * @{
  */

/** @defgroup I2S_Public_Types I2S Public Types
  * @{
  */

/**
  * @brief Channel length
  */
typedef enum {
    ALD_I2S_WIDE_16 = 0x0U, /**< Channel length is 16 */
    ALD_I2S_WIDE_32 = 0x1U, /**< Channel length is 32 */
} ald_i2s_chlen_t;

/**
  * @brief Data length
  */
typedef enum {
    ALD_I2S_LEN_16 = 0x0U,  /**< Data length is 16 */
    ALD_I2S_LEN_24 = 0x1U,  /**< Data length is 24 */
    ALD_I2S_LEN_32 = 0x2U,  /**< Data length is 32 */
} ald_i2s_datalen_t;

/**
  * @brief Inactive state clock polarity
  */
typedef enum {
    ALD_I2S_INACTIVE_LOW  = 0x0U,   /**< Inactive state is low */
    ALD_I2S_INACTIVE_HIGH = 0x1U,   /**< Inactive state is high */
} ald_i2s_cpol_t;

/**
  * @brief I2s standard
  */
typedef enum {
    ALD_I2S_STD_PHI = 0x0U, /**< Philips standard */
    ALD_I2S_STD_MSB = 0x1U, /**< MSB standard */
    ALD_I2S_STD_LSB = 0x2U, /**< LSB standard */
    ALD_I2S_STD_PCM = 0x3U, /**< PCM standard */
} ald_i2s_standard_t;

/**
  * @brief I2s configuration mode
  */
typedef enum {
    ALD_I2S_SLAVE_DUPLEX    = 0x0U, /**< I2S slave full duplex mode */
    ALD_I2S_SLAVE_RECEIVE   = 0x1U, /**< I2S slave receive mode */
    ALD_I2S_SLAVE_TRANSMIT  = 0x2U, /**< I2S slave transmit mode */
    ALD_I2S_MASTER_DUPLEX   = 0x4U, /**< I2S master full duplex mode */
    ALD_I2S_MASTER_TRANSMIT = 0x5U, /**< I2S master transmit mode */
    ALD_I2S_MASTER_RECEIVE  = 0x6U, /**< I2S master receive mode */
} ald_i2s_cfg_t;

/**
  * @brief Pcm frame synchronization
  */
typedef enum {
    ALD_I2S_FRAME_SHORT = 0x0U, /**< I2S PCM short frame */
    ALD_I2S_FRAME_LONG  = 0x1U, /**< I2S PCM long frame */
} ald_i2s_pcms_t;

/**
  * @brief Channel side
  */
typedef enum {
    ALD_I2S_SIDE_LEFT  = 0U,    /**< Sound channel is left */
    ALD_I2S_SIDE_RIGHT = 1U,    /**< Sound channel is right */
} ald_i2s_ch_side_t;

/**
  * @brief I2S error status
  */
typedef enum {
    ALD_I2S_ERROR_NONE = 0x0U,  /**< none */
    ALD_I2S_ERROR_MODF = 0x1U,  /**< mode fault */
    ALD_I2S_ERROR_DMA  = 0x2U,  /**< crc error */
    ALD_I2S_ERROR_FRE  = 0x4U,  /**< frame error */
    ALD_I2S_ERROR_RXOV = 0x8U,  /**< receive over error */
    ALD_I2S_ERROR_TXOV = 0x10U, /**< dma error  */
    ALD_I2S_ERROR_FLAG = 0x20U, /**< interrupt flag error */
} ald_i2s_error_t;

/**
  * @brief interrupt control
  */
typedef enum {
    ALD_I2S_IT_TXE    = (1U << 0),  /**< Transmit fifo empty interrupt */
    ALD_I2S_IT_TXOV   = (1U << 2),  /**< Transmit fifo overflow interrupt */
    ALD_I2S_IT_TXUD   = (1U << 3),  /**< Transmit fifo underflow interrupt */
    ALD_I2S_IT_TXTH   = (1U << 4),  /**< Transmit fifo under threshold interrupt */
    ALD_I2S_IT_RXNE   = (1U << 8),  /**< Receive fifo not empty interrupt */
    ALD_I2S_IT_RXF    = (1U << 9),  /**< Receive fifo full interrupt */
    ALD_I2S_IT_RXOV   = (1U << 10), /**< Receive fifo overflow interrupt */
    ALD_I2S_IT_RXUD   = (1U << 11), /**< Receive fifo underflow interrupt */
    ALD_I2S_IT_RXTH   = (1U << 12), /**< Receive fifo over threshold interrupt */
    ALD_I2S_IT_CRCERR = (1U << 16), /**< Crc error interrupt */
    ALD_I2S_IT_MODF   = (1U << 17), /**< Mode error interrupt */
    ALD_I2S_IT_FRE    = (1U << 18), /**< Frame error interrupt */
} ald_i2s_it_t;

/**
  * @brief I2S dma request definition
  */
typedef enum {
    ALD_I2S_DMA_REQ_TX = 0U,    /**< TX dma request */
    ALD_I2S_DMA_REQ_RX = 1U,    /**< RX dma request */
} ald_i2s_dma_req_t;

/**
  * @brief interrupt flag
  */
typedef enum {
    ALD_I2S_IF_TXE  = (1U << 0),    /**< Transmit fifo empty interrupt flag */
    ALD_I2S_IF_TXOV = (1U << 2),    /**< Transmit fifo overflow interrupt flag */
    ALD_I2S_IF_TXUD = (1U << 3),    /**< Transmit fifo underflow interrupt flag */
    ALD_I2S_IF_TXTH = (1U << 4),    /**< Transmit fifo under threshold interrupt flag */
    ALD_I2S_IF_RXNE = (1U << 8),    /**< Receive fifo not empty interrupt flag */
    ALD_I2S_IF_RXF  = (1U << 9),    /**< Receive fifo full interrupt flag */
    ALD_I2S_IF_RXOV = (1U << 10),   /**< Receive fifo overflow interrupt flag */
    ALD_I2S_IF_RXUD = (1U << 11),   /**< Receive fifo underflow interrupt flag */
    ALD_I2S_IF_RXTH = (1U << 12),   /**< Receive fifo over threshold interrupt flag */
    ALD_I2S_IF_CRCERR = (1U << 16), /**< Crc error interrupt flag */
    ALD_I2S_IF_MODF   = (1U << 17), /**< Mode error interrupt flag */
    ALD_I2S_IF_FRE  = (1U << 18),   /**< Frame error interrupt flag */
} ald_i2s_flag_t;

/**
  * @brief I2S state structures definition
  */
typedef enum {
    ALD_I2S_STATE_RESET      = 0x00U,   /**< Peripheral is not initialized */
    ALD_I2S_STATE_READY      = 0x01U,   /**< Peripheral Initialized and ready for use */
    ALD_I2S_STATE_BUSY       = 0x02U,   /**< an internal process is ongoing */
    ALD_I2S_STATE_BUSY_TX    = 0x11U,   /**< transmit is ongoing */
    ALD_I2S_STATE_BUSY_RX    = 0x21U,   /**< receive is ongoing */
    ALD_I2S_STATE_BUSY_TX_RX = 0x31U,   /**< transmit and receive are ongoing */
    ALD_I2S_STATE_TIMEOUT    = 0x03U,   /**< Timeout state */
    ALD_I2S_STATE_ERROR      = 0x04U,   /**< Error */
} ald_i2s_state_t;

/**
  * @brief I2S status definition
  */
typedef enum {
    ALD_I2S_STATUS_TXE    = (1U << 0),  /**< Transmit fifo empty status */
    ALD_I2S_STATUS_TXF    = (1U << 1),  /**< Transmit fifo full status */
    ALD_I2S_STATUS_TXOV   = (1U << 2),  /**< Transmit fifo overflow status */
    ALD_I2S_STATUS_TXUD   = (1U << 3),  /**< Transmit fifo underflow status */
    ALD_I2S_STATUS_TXTH   = (1U << 4),  /**< Transmit fifo under threshold status */
    ALD_I2S_STATUS_RXNE   = (1U << 8),  /**< Receive fifo not empty status */
    ALD_I2S_STATUS_RXF    = (1U << 9),  /**< Receive fifo full status */
    ALD_I2S_STATUS_RXOV   = (1U << 10), /**< Receive fifo overflow status */
    ALD_I2S_STATUS_RXUD   = (1U << 11), /**< Receive fifo underflow status */
    ALD_I2S_STATUS_RXTH   = (1U << 12), /**< Receive fifo over threshold status */
    ALD_I2S_STATUS_CHSIDE = (1U << 14), /**< Sound channel status */
    ALD_I2S_STATUS_BUSY   = (1U << 15), /**< BUSY status */
} ald_i2s_status_t;

/**
  * @brief I2S TXE/RXNE status definition
  */
typedef enum {
    ALD_I2S_SR_TXE      = 0U,   /**< STAT TXE set */
    ALD_I2S_SR_RXNE     = 1U,   /**< STAT RXTH set */
    ALD_I2S_SR_TXE_RXNE = 2U,   /**< STAT TXE and RXTH set */
} ald_i2s_sr_status_t;

/**
  * @brief I2S init structure definition
  */
typedef struct {
    ald_i2s_chlen_t ch_len;     /**< Channel length choose */
    ald_i2s_datalen_t data_len;     /**< Data length choose */
    ald_i2s_cpol_t polarity;        /**< Inactive clock polarity */
    ald_i2s_standard_t standard;    /**< Standard choose */
    ald_i2s_pcms_t pcm_frame;       /**< PCM frame synchronization */
    type_func_t ext_clk_en;     /**< Choose external clock or APB1 clock */
    uint32_t ext_clk;       /**< External clock, unit is Hz */
    type_func_t mck_en;     /**< Main clock output function */
    uint32_t sampling;      /**< Sampling rate. eg. 192*1024-192KHz, 96*1024-96KHz */
} ald_i2s_init_t;

/**
  * @brief  I2S handle structure definition
  */
typedef struct ald_i2s_handle_s {
    SPI_I2S_TypeDef *perh;  /**< I2S registers base address */
    ald_i2s_init_t init;    /**< I2S communication parameters */
    uint16_t *tx_buf;   /**< Pointer to I2S Tx transfer buffer */
    uint32_t tx_size;   /**< I2S Tx transfer size */
    uint32_t tx_count;  /**< I2S Tx transfer counter */
    uint16_t *rx_buf;   /**< Pointer to I2S Rx transfer buffer */
    uint32_t rx_size;   /**< I2S Rx Transfer size */
    uint32_t rx_count;  /**< I2S Rx Transfer Counter */

    ald_dma_handle_t hdmatx;    /**< I2S DMA handle parameters */
    ald_dma_handle_t hdmarx;    /**< I2S DMA handle parameters */

    lock_state_t lock;  /**< Locking object */
    ald_i2s_state_t state;  /**< I2S communication state */
    uint8_t side;       /**< I2S channel side */
    uint32_t err_code;  /**< I2S error code */

    void (*tx_cplt_cbk)(struct ald_i2s_handle_s *arg);      /**< Tx completed callback */
    void (*rx_cplt_cbk)(struct ald_i2s_handle_s *arg);      /**< Rx completed callback */
    void (*err_cbk)(struct ald_i2s_handle_s *arg);      /**< error callback */
} ald_i2s_handle_t;
/**
  * @}
  */

/** @defgroup I2S_Public_Macros I2S Public Macros
  * @{
  */
#define ALD_I2S_RESET_HANDLE_STATE(x)   ((x)->state = ALD_I2S_STATE_RESET)
#define ALD_I2S_ENABLE(x)               (SET_BIT((x)->perh->I2SCFG, SPI_I2SCFG_I2SE_MSK))
#define ALD_I2S_DISABLE(x)              (CLEAR_BIT((x)->perh->I2SCFG, SPI_I2SCFG_I2SE_MSK))
/**
  * @}
  */

/** @defgroup I2S_Private_Macros   I2S Private Macros
  * @{
  */
#define IS_I2S(x)       ((x) == I2S0)
#define IS_I2S_CH_LEN(x)    (((x) == ALD_I2S_WIDE_16) || \
                 ((x) == ALD_I2S_WIDE_32))
#define IS_I2S_DATE_LEN(x)  (((x) == ALD_I2S_LEN_16) || \
                 ((x) == ALD_I2S_LEN_24) || \
                 ((x) == ALD_I2S_LEN_32))
#define IS_I2S_CPOL(x)      (((x) == ALD_I2S_INACTIVE_LOW) || \
                 ((x) == ALD_I2S_INACTIVE_HIGH))
#define IS_I2S_STANDARD(x)  (((x) == ALD_I2S_STD_PHI) || \
                 ((x) == ALD_I2S_STD_MSB) || \
                 ((x) == ALD_I2S_STD_LSB) || \
                 ((x) == ALD_I2S_STD_PCM))
#define IS_I2S_PCMS(x)      (((x) == ALD_I2S_FRAME_SHORT) || \
                 ((x) == ALD_I2S_FRAME_LONG))
#define IS_I2S_IT(x)        (((x) == ALD_I2S_IT_TXE)    || \
                 ((x) == ALD_I2S_IT_TXOV)   || \
                 ((x) == ALD_I2S_IT_TXUD)   || \
                 ((x) == ALD_I2S_IT_TXTH)   || \
                 ((x) == ALD_I2S_IT_RXNE)   || \
                 ((x) == ALD_I2S_IT_RXF)    || \
                 ((x) == ALD_I2S_IT_RXOV)   || \
                 ((x) == ALD_I2S_IT_RXUD)   || \
                 ((x) == ALD_I2S_IT_RXTH)   || \
                 ((x) == ALD_I2S_IT_CRCERR) || \
                 ((x) == ALD_I2S_IT_MODF)   || \
                 ((x) == ALD_I2S_IT_FRE))
#define IS_I2S_IF(x)        (((x) == ALD_I2S_IF_TXE)    || \
                 ((x) == ALD_I2S_IF_TXOV)   || \
                 ((x) == ALD_I2S_IF_TXUD)   || \
                 ((x) == ALD_I2S_IF_TXTH)   || \
                 ((x) == ALD_I2S_IF_RXNE)   || \
                 ((x) == ALD_I2S_IF_RXF)    || \
                 ((x) == ALD_I2S_IF_RXOV)   || \
                 ((x) == ALD_I2S_IF_RXUD)   || \
                 ((x) == ALD_I2S_IF_RXTH)   || \
                 ((x) == ALD_I2S_IF_CRCERR) || \
                 ((x) == ALD_I2S_IF_MODF)   || \
                 ((x) == ALD_I2S_IF_FRE))
#define IS_I2S_STATUS(x)    (((x) == ALD_I2S_STATUS_TXE)    || \
                 ((x) == ALD_I2S_STATUS_TXF)    || \
                 ((x) == ALD_I2S_STATUS_TXOV)   || \
                 ((x) == ALD_I2S_STATUS_TXUD)   || \
                 ((x) == ALD_I2S_STATUS_TXTH)   || \
                 ((x) == ALD_I2S_STATUS_RXNE)    || \
                 ((x) == ALD_I2S_STATUS_RXF)    || \
                 ((x) == ALD_I2S_STATUS_RXOV)   || \
                 ((x) == ALD_I2S_STATUS_RXUD)   || \
                 ((x) == ALD_I2S_STATUS_RXTH)   || \
                 ((x) == ALD_I2S_STATUS_CHSIDE) || \
                 ((x) == ALD_I2S_STATUS_BUSY))
#define IS_I2S_DMA_REQ(x)   (((x) == ALD_I2S_DMA_REQ_TX) || \
                 ((x) == ALD_I2S_DMA_REQ_RX))
/**
  * @}
  */

/** @addtogroup I2S_Public_Functions
  * @{
  */

/** @addtogroup I2S_Public_Functions_Group1
  * @{
  */

ald_status_t ald_i2s_init(ald_i2s_handle_t *hperh);
void ald_i2s_reset(ald_i2s_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup I2S_Public_Functions_Group2
  * @{
  */
ald_status_t ald_i2s_master_send(ald_i2s_handle_t *hperh, uint16_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_i2s_master_recv(ald_i2s_handle_t *hperh, uint16_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_i2s_master_send_by_it(ald_i2s_handle_t *hperh, uint16_t *buf, uint32_t size);
ald_status_t ald_i2s_master_recv_by_it(ald_i2s_handle_t *hperh, uint16_t *buf, uint32_t size);

ald_status_t ald_i2s_master_send_by_dma(ald_i2s_handle_t *hperh, uint16_t *buf, uint32_t size, uint8_t channel);
ald_status_t ald_i2s_master_recv_by_dma(ald_i2s_handle_t *hperh, uint16_t *buf, uint32_t size, uint8_t dma_ch, uint8_t _dma_ch);
ald_status_t ald_i2s_dma_pause(ald_i2s_handle_t *hperh);
ald_status_t ald_i2s_dma_resume(ald_i2s_handle_t *hperh);
ald_status_t ald_i2s_dma_stop(ald_i2s_handle_t *hperh);

/**
  * @}
  */

/** @addtogroup I2S_Public_Functions_Group3
  * @{
  */
void ald_i2s_irq_handler(ald_i2s_handle_t *hperh);
void ald_i2s_interrupt_config(ald_i2s_handle_t *hperh, ald_i2s_it_t it, type_func_t state);
void ald_i2s_dma_req_config(ald_i2s_handle_t *hperh, ald_i2s_dma_req_t req, type_func_t state);
flag_status_t ald_i2s_get_status(ald_i2s_handle_t *hperh, ald_i2s_status_t status);
it_status_t ald_i2s_get_it_status(ald_i2s_handle_t *hperh, ald_i2s_it_t it);
flag_status_t ald_i2s_get_flag_status(ald_i2s_handle_t *hperh, ald_i2s_flag_t flag);
flag_status_t ald_i2s_get_mask_flag_status(ald_i2s_handle_t *hperh, ald_i2s_flag_t flag);
void ald_i2s_clear_flag_status(ald_i2s_handle_t *hperh, ald_i2s_flag_t flag);
/**
  * @}
  */

/** @addtogroup I2S_Public_Functions_Group4
  * @{
  */
ald_i2s_state_t ald_i2s_get_state(ald_i2s_handle_t *hperh);
uint32_t ald_i2s_get_error(ald_i2s_handle_t *hperh);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __ALD_I2S_H__ */
