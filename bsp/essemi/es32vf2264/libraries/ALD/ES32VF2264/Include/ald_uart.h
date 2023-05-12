/**
  *********************************************************************************
  *
  * @file    ald_uart.h
  * @brief   Header file of UART module library.
  *
  * @version V1.0
  * @date    22 Feb. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          22 Feb. 2023    Lisq            The first version
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

#ifndef __ALD_UART_H__
#define __ALD_UART_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "ald_cmu.h"
#include "ald_dma.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @addtogroup UART
  * @{
  */

/**
  * @defgroup UART_Public_Macros UART Public Macros
  * @{
  */
#define ALD_UART_RX_ENABLE(hperh)       (SET_BIT((hperh)->perh->LCON, UART_LCON_RXEN_MSK))
#define ALD_UART_RX_DISABLE(hperh)      (CLEAR_BIT((hperh)->perh->LCON, UART_LCON_RXEN_MSK))
#define ALD_UART_TX_ENABLE(hperh)       (SET_BIT((hperh)->perh->LCON, UART_LCON_TXEN_MSK))
#define ALD_UART_TX_DISABLE(hperh)      (CLEAR_BIT((hperh)->perh->LCON, UART_LCON_TXEN_MSK))
#define ALD_UART_RX_TIMEOUT_ENABLE(hperh)   (SET_BIT((hperh)->perh->RTOR, UART_RTOR_RTOEN_MSK))
#define ALD_UART_RX_TIMEOUT_DISABLE(hperh)  (CLEAR_BIT((hperh)->perh->RTOR, UART_RTOR_RTOEN_MSK))
#define ALD_UART_MSB_FIRST_ENABLE(hperh)    (SET_BIT((hperh)->perh->LCON, UART_LCON_MSB_MSK))
#define ALD_UART_MSB_FIRST_DISABLE(hperh)   (CLEAR_BIT((hperh)->perh->LCON, UART_LCON_MSB_MSK))
#define ALD_UART_DATA_INV_ENABLE(hperh) (SET_BIT((hperh)->perh->LCON, UART_LCON_DATAINV_MSK))
#define ALD_UART_DATA_INV_DISABLE(hperh)    (CLEAR_BIT((hperh)->perh->LCON, UART_LCON_DATAINV_MSK))
#define ALD_UART_RX_INV_ENABLE(hperh)   (SET_BIT((hperh)->perh->LCON, UART_LCON_RXINV_MSK))
#define ALD_UART_RX_INV_DISABLE(hperh)  (CLEAR_BIT((hperh)->perh->LCON, UART_LCON_RXINV_MSK))
#define ALD_UART_TX_INV_ENABLE(hperh)   (SET_BIT((hperh)->perh->LCON, UART_LCON_TXINV_MSK))
#define ALD_UART_TX_INV_DISABLE(hperh)  (CLEAR_BIT((hperh)->perh->LCON, UART_LCON_TXINV_MSK))
#define ALD_UART_TX_RX_SWAP_ENABLE(hperh)   (SET_BIT((hperh)->perh->LCON, UART_LCON_SWAP_MSK))
#define ALD_UART_TX_RX_SWAP_DISABLE(hperh)  (CLEAR_BIT((hperh)->perh->LCON, UART_LCON_SWAP_MSK))
#define ALD_UART_HDSEL_ENABLE(hperh)    (SET_BIT((hperh)->perh->MCON, UART_MCON_HDEN_MSK))
#define ALD_UART_HDSEL_DISABLE(hperh)   (CLEAR_BIT((hperh)->perh->MCON, UART_MCON_HDEN_MSK))
#define ALD_UART_LPBMOD_ENABLE(hperh)   (SET_BIT((hperh)->perh->MCON, UART_MCON_LPBKEN_MSK))
#define ALD_UART_LPBMOD_DISABLE(hperh)  (CLEAR_BIT((hperh)->perh->MCON, UART_MCON_LPBKEN_MSK))
#define ALD_UART_AUTOBR_ENABLE(hperh)   (SET_BIT((hperh)->perh->MCON, UART_MCON_ABREN_MSK))
#define ALD_UART_AUTOBR_DISABLE(hperh)  (CLEAR_BIT((hperh)->perh->MCON, UART_MCON_ABREN_MSK))
#define ALD_UART_AUTOBR_REPT(hperh)     (SET_BIT((hperh)->perh->MCON, UART_MCON_ABRREPT_MSK))
#define ALD_UART_GET_BRR_VALUE(hperh)   (READ_REG((hperh)->perh->BRR))
#define ALD_UART_SET_TIMEOUT_VALUE(x, y)    (MODIFY_REG((x)->perh->RTOR, UART_RTOR_RTO_MSK, (y) << UART_RTOR_RTO_POSS))
#define ALD_UART_ENABLE_SCARD_CLK(hperh)    (SET_BIT((hperh)->perh->SCARD, UART_SCARD_SCLKEN_MSK))
#define ALD_UART_DISABLE_SCARD_CLK(hperh)   (CLEAR_BIT((hperh)->perh->SCARD, UART_SCARD_SCLKEN_MSK))
#define ALD_UART_ENABLE_SCARD_NACK(hperh)   (SET_BIT((hperh)->perh->SCARD, UART_SCARD_SCNACK_MSK))
#define ALD_UART_DISABLE_SCARD_NACK(hperh)  (CLEAR_BIT((hperh)->perh->SCARD, UART_SCARD_SCNACK_MSK))
#define ALD_UART_SCARD_ENABLE(hperh)        (SET_BIT((hperh)->perh->SCARD, UART_SCARD_SCEN_MSK))
#define ALD_UART_SCARD_DISABLE(hperh)       (CLEAR_BIT((hperh)->perh->SCARD, UART_SCARD_SCEN_MSK))
/**
  * @}
  */

/** @defgroup UART_Public_Types UART Public Types
  * @{
  */
/**
  * @brief UART word length
  */
typedef enum {
    ALD_UART_WORD_LENGTH_8B = 0x0U, /**< 8-bits */
    ALD_UART_WORD_LENGTH_7B = 0x1U, /**< 7-bits */
    ALD_UART_WORD_LENGTH_6B = 0x2U, /**< 6-bits */
    ALD_UART_WORD_LENGTH_5B = 0x3U, /**< 5-bits */
} ald_uart_word_length_t;

/**
  * @brief UART stop bits
  */
typedef enum {
    ALD_UART_STOP_BITS_1   = 0x0U,  /**< 1-bits */
    ALD_UART_STOP_BITS_2   = 0x1U,  /**< 2-bits */
    ALD_UART_STOP_BITS_0_5 = 0x0U,  /**< 0.5-bits, using smartcard mode */
    ALD_UART_STOP_BITS_1_5 = 0x1U,  /**< 1.5-bits, using smartcard mode */
} ald_uart_stop_bits_t;

/**
  * @brief UART parity
  */
typedef enum {
    ALD_UART_PARITY_NONE = 0x0U,    /**< Not parity */
    ALD_UART_PARITY_ODD  = 0x1U,    /**< Odd parity */
    ALD_UART_PARITY_EVEN = 0x3U,    /**< Even parity */
} ald_uart_parity_t;

/**
  * @brief UART mode
  */
typedef enum {
    ALD_UART_MODE_UART  = 0x0U, /**< UART */
    ALD_UART_MODE_LIN   = 0x1U, /**< LIN */
    ALD_UART_MODE_IrDA  = 0x2U, /**< IrDA */
    ALD_UART_MODE_RS485 = 0x3U, /**< RS485 */
    ALD_UART_MODE_HDSEL = 0x4U, /**< Single-wire half-duplex */
    ALD_UART_MODE_SCARD = 0x5U, /**< Smart card */
} ald_uart_mode_t;

/**
  * @brief UART hardware flow control
  */
typedef enum {
    ALD_UART_HW_FLOW_CTL_DISABLE = 0x0U,    /**< Auto-flow-control disable */
    ALD_UART_HW_FLOW_CTL_ENABLE  = 0x1U,    /**< Auto-flow-control enable */
} ald_uart_hw_flow_ctl_t;

/**
  * @brief ALD UART state
  */
typedef enum {
    ALD_UART_STATE_RESET      = 0x00U,  /**< Peripheral is not initialized */
    ALD_UART_STATE_READY      = 0x01U,  /**< Peripheral Initialized and ready for use */
    ALD_UART_STATE_BUSY       = 0x02U,  /**< an internal process is ongoing */
    ALD_UART_STATE_BUSY_TX    = 0x11U,  /**< Data Transmission process is ongoing */
    ALD_UART_STATE_BUSY_RX    = 0x21U,  /**< Data Reception process is ongoing */
    ALD_UART_STATE_BUSY_TX_RX = 0x31U,  /**< Data Transmission Reception process is ongoing */
    ALD_UART_STATE_TIMEOUT    = 0x03U,  /**< Timeout state */
    ALD_UART_STATE_ERROR      = 0x04U,  /**< Error */
} ald_uart_state_t;

/**
  * @brief UART error codes
  */
typedef enum {
    ALD_UART_ERROR_NONE = ((uint32_t)0x00U),    /**< No error */
    ALD_UART_ERROR_PE   = ((uint32_t)0x01U),    /**< Parity error */
    ALD_UART_ERROR_NE   = ((uint32_t)0x02U),    /**< Noise error */
    ALD_UART_ERROR_FE   = ((uint32_t)0x04U),    /**< frame error */
    ALD_UART_ERROR_ORE  = ((uint32_t)0x08U),    /**< Overrun error */
    ALD_UART_ERROR_DMA  = ((uint32_t)0x10U),    /**< DMA transfer error */
} ald_uart_error_t;

/**
  * @brief UART init structure definition
  */
typedef struct {
    uint32_t baud;          /**< Specifies the uart communication baud rate */
    ald_uart_word_length_t word_length; /**< Specifies the number of data bits transmitted or received in a frame */
    ald_uart_stop_bits_t stop_bits; /**< Specifies the number of stop bits transmitted */
    ald_uart_parity_t parity;       /**< Specifies the parity mode */
    ald_uart_mode_t mode;       /**< Specifies uart mode */
    ald_uart_hw_flow_ctl_t fctl;    /**< Specifies wether the hardware flow control mode is enabled or disabled */
} ald_uart_init_t;

/**
  * @brief  UART handle structure definition
  */
typedef struct ald_uart_handle_s {
    UART_TypeDef *perh; /**< UART registers base address */
    ald_uart_init_t init;   /**< UART communication parameters */
    uint8_t *tx_buf;    /**< Pointer to UART Tx transfer Buffer */
    uint16_t tx_size;   /**< UART Tx Transfer size */
    uint16_t tx_count;  /**< UART Tx Transfer Counter */
    uint8_t *rx_buf;    /**< Pointer to UART Rx transfer Buffer */
    uint16_t rx_size;   /**< UART Rx Transfer size */
    uint16_t rx_count;  /**< UART Rx Transfer Counter */

    ald_dma_handle_t hdmatx;    /**< UART Tx DMA Handle parameters */
    ald_dma_handle_t hdmarx;    /**< UART Rx DMA Handle parameters */

    lock_state_t lock;  /**< Locking object */
    ald_uart_state_t state; /**< UART communication state */
    ald_uart_error_t err_code;  /**< UART Error code */

    void (*tx_cplt_cbk)(struct ald_uart_handle_s *arg); /**< Tx completed callback */
    void (*rx_cplt_cbk)(struct ald_uart_handle_s *arg); /**< Rx completed callback */
    void (*error_cbk)(struct ald_uart_handle_s *arg);   /**< error callback */
} ald_uart_handle_t;

/**
  * @brief UART RS485 configure structure definition
  */
typedef struct {
    type_func_t normal; /**< Normal mode */
    type_func_t dir;    /**< Auto-direction mode */
    type_func_t invert; /**< Address detection invert */
    uint8_t addr;       /**< Address for compare */
} ald_uart_rs485_config_t;

/**
  * @brief Smart_card Rx/Tx handle retry time
  */
typedef enum {
    ALD_SCARD_RETRY_CNT0 = 0x0U,    /**< retry time 0 */
    ALD_SCARD_RETRY_CNT1 = 0x1U,    /**< retry time 1 */
    ALD_SCARD_RETRY_CNT2 = 0x2U,    /**< retry time 2 */
    ALD_SCARD_RETRY_CNT3 = 0x3U,    /**< retry time 3 */
    ALD_SCARD_RETRY_CNT4 = 0x4U,    /**< retry time 4 */
    ALD_SCARD_RETRY_CNT5 = 0x5U,    /**< retry time 5 */
    ALD_SCARD_RETRY_CNT6 = 0x6U,    /**< retry time 6 */
    ALD_SCARD_RETRY_CNT7 = 0x7U,    /**< retry time 7 */
} ald_scard_retry_t;

/**
  * @brief UART Smart card configure structure definition
  */
typedef struct {
    uint8_t block_len;       /**< Specifies the data block length.*/
    uint8_t pt;          /**< Specifies the protect time*/
    ald_scard_retry_t retry;     /**< Specifies retry time.*/
    uint8_t clk_div;         /**< Specifies the clock division.*/
    type_func_t clk_out;     /**< Specifies the clock out */
} ald_uart_scard_config_t;

/**
  * @brief LIN detection break length
  */
typedef enum {
    ALD_LIN_BREAK_LEN_10B = 0x0U,   /**< 10-bit break */
    ALD_LIN_BREAK_LEN_11B = 0x1U,   /**< 11-bit break */
} ald_uart_lin_break_len_t;

/**
  * @brief UART auto-baud mode
  */
typedef enum {
    ALD_UART_ABRMOD_1_TO_0 = 0x0U,  /**< Detect bit0:1, bit1:0 */
    ALD_UART_ABRMOD_1      = 0x1U,  /**< Detect bit0:1 */
    ALD_UART_ABRMOD_0_TO_1 = 0x2U,  /**< Detect bit0:0, bit1:1 */
} ald_uart_auto_baud_mode_t;

/**
  * @brief UART DMA Requests
  */
typedef enum {
    ALD_UART_DMA_REQ_TX = 0x0U, /**< TX dma */
    ALD_UART_DMA_REQ_RX = 0x1U, /**< RX dma */
} ald_uart_dma_req_t;

/**
  * @brief UART status types
  */
typedef enum {
    ALD_UART_STATUS_PERR     = (1U << 0),   /**< Parity error */
    ALD_UART_STATUS_FERR     = (1U << 1),   /**< Framing error */
    ALD_UART_STATUS_BKERR    = (1U << 2),   /**< Break error */
    ALD_UART_STATUS_CTSSTA   = (1U << 3),   /**< Clear to send status */
    ALD_UART_STATUS_RSBUSY   = (1U << 8),   /**< Receive shif register busy */
    ALD_UART_STATUS_RFNEMPTY = (1U << 10),  /**< Receive FIFO not empty */
    ALD_UART_STATUS_RFOERR   = (1U << 12),  /**< Reveive FIFO overrun error */
    ALD_UART_STATUS_RFUERR   = (1U << 13),  /**< Receive FIFO underrun error */
    ALD_UART_STATUS_TSBUSY   = (1U << 14),  /**< Transmit shit register busy */
    ALD_UART_STATUS_TFEMPTY  = (1U << 16),  /**< Transmit FIFO empty */
    ALD_UART_STATUS_TFOERR   = (1U << 18),  /**< Transmit FIFO overrun error */
} ald_uart_status_t;

/**
  * @brief UART interrupt types
  */
typedef enum {
    ALD_UART_IT_RXBERR   = (1U << 0),   /**< Receiver byte error */
    ALD_UART_IT_ABEND    = (1U << 1),   /**< Auto-Baud rate detection end */
    ALD_UART_IT_ABTO     = (1U << 2),   /**< Auto-Baud rate detection timeout */
    ALD_UART_IT_DCTS     = (1U << 3),   /**< Delta CTS status */
    ALD_UART_IT_RXTO     = (1U << 4),   /**< Receiver timeout */
    ALD_UART_IT_ADDRM    = (1U << 5),   /**< Addredd match */
    ALD_UART_IT_LINBK    = (1U << 6),   /**< Lin break detection */
    ALD_UART_IT_EOB      = (1U << 7),   /**< End of block */
    ALD_UART_IT_NOISE    = (1U << 8),   /**< Start bit noise detection */
    ALD_UART_IT_RFNEMPTY = (1U << 10),  /**< Receive FIFO not empty */
    ALD_UART_IT_RFFULL   = (1U << 11),  /**< Receive FIFO full */
    ALD_UART_IT_RFOERR   = (1U << 12),  /**< Receive FIFO overrun */
    ALD_UART_IT_RFUERR   = (1U << 13),  /**< Reveive FIFO underrun */
    ALD_UART_IT_TBC      = (1U << 14),  /**< Transmit shift register empty */
    ALD_UART_IT_TFEMPTY  = (1U << 16),  /**< Transmit FIFO empty */
    ALD_UART_IT_TFOERR   = (1U << 18),  /**< Transmit FIFO overrun error */
} ald_uart_it_t;

/**
  * @brief UART flags types
  */
typedef enum {
    ALD_UART_IF_RXBERR   = (1U << 0),   /**< Receiver byte error */
    ALD_UART_IF_ABEND    = (1U << 1),   /**< Auto-Baud rate detection end */
    ALD_UART_IF_ABTO     = (1U << 2),   /**< Auto-Baud rate detection timeout */
    ALD_UART_IF_DCTS     = (1U << 3),   /**< Delta CTS status */
    ALD_UART_IF_RXTO     = (1U << 4),   /**< Receiver timeout */
    ALD_UART_IF_ADDRM    = (1U << 5),   /**< Addredd match */
    ALD_UART_IF_LINBK    = (1U << 6),   /**< Lin break detection */
    ALD_UART_IF_EOB      = (1U << 7),   /**< End of block */
    ALD_UART_IF_NOISE    = (1U << 8),   /**< Start bit noise detection */
    ALD_UART_IF_RFNEMPTY = (1U << 10),  /**< Receive FIFO not empty */
    ALD_UART_IF_RFFULL   = (1U << 11),  /**< Receive FIFO full */
    ALD_UART_IF_RFOERR   = (1U << 12),  /**< Receive FIFO overrun */
    ALD_UART_IF_RFUERR   = (1U << 13),  /**< Reveive FIFO underrun */
    ALD_UART_IF_TBC      = (1U << 14),  /**< Transmit shift register empty */
    ALD_UART_IF_TFEMPTY  = (1U << 16),  /**< Transmit FIFO empty */
    ALD_UART_IF_TFOVER   = (1U << 18),  /**< Transmit FIFO overrun */
} ald_uart_flag_t;
/**
  * @}
  */

/** @defgroup UART_Private_Macros   UART Private Macros
  * @{
  */
#define IS_UART_ENHANCE(x)(((x) == EUART0) || \
                         ((x) == EUART1))
#define IS_UART_ALL(x)  (((x) == EUART0) || \
                         ((x) == EUART1) || \
                         ((x) == CUART0) || \
                         ((x) == CUART1) || \
                         ((x) == CUART2))
#define IS_UART_WORD_LENGTH(x)  (((x) == ALD_UART_WORD_LENGTH_5B) || \
                                 ((x) == ALD_UART_WORD_LENGTH_6B) || \
                                 ((x) == ALD_UART_WORD_LENGTH_7B) || \
                                 ((x) == ALD_UART_WORD_LENGTH_8B))
#define IS_UART_STOPBITS(x) (((x) == ALD_UART_STOP_BITS_1)   || \
                                 ((x) == ALD_UART_STOP_BITS_2)   || \
                                 ((x) == ALD_UART_STOP_BITS_0_5) || \
                                 ((x) == ALD_UART_STOP_BITS_1_5))
#define IS_UART_PARITY(x)   (((x) == ALD_UART_PARITY_NONE)  || \
                                 ((x) == ALD_UART_PARITY_ODD) || \
                                 ((x) == ALD_UART_PARITY_EVEN))
#define IS_UART_MODE(x)     (((x) == ALD_UART_MODE_UART) || \
                                 ((x) == ALD_UART_MODE_LIN)  || \
                                 ((x) == ALD_UART_MODE_IrDA) || \
                                 ((x) == ALD_UART_MODE_HDSEL) || \
                                 ((x) == ALD_UART_MODE_SCARD) || \
                                 ((x) == ALD_UART_MODE_RS485))
#define IS_UART_HARDWARE_FLOW_CONTROL(x) \
                                (((x) == ALD_UART_HW_FLOW_CTL_DISABLE) || \
                                 ((x) == ALD_UART_HW_FLOW_CTL_ENABLE))
#define IS_UART_LIN_BREAK_LEN(x)    (((x) == ALD_LIN_BREAK_LEN_10B) || \
                                         ((x) == ALD_LIN_BREAK_LEN_11B))
#define IS_UART_AUTO_BAUD_MODE(x)   (((x) == ALD_UART_ABRMOD_1_TO_0) || \
                                         ((x) == ALD_UART_ABRMOD_1)      || \
                                         ((x) == ALD_UART_ABRMOD_0_TO_1))
#define IS_UART_DMA_REQ(x)  (((x) == ALD_UART_DMA_REQ_TX) || \
                                 ((x) == ALD_UART_DMA_REQ_RX))
#define IS_UART_STATUS(x)   (((x) == ALD_UART_STATUS_PERR)    || \
                                 ((x) == ALD_UART_STATUS_FERR)    || \
                                 ((x) == ALD_UART_STATUS_BKERR)   || \
                                 ((x) == ALD_UART_STATUS_CTSSTA)  || \
                                 ((x) == ALD_UART_STATUS_RSBUSY)  || \
                                 ((x) == ALD_UART_STATUS_RFNEMPTY) || \
                                 ((x) == ALD_UART_STATUS_RFOERR)  || \
                                 ((x) == ALD_UART_STATUS_RFUERR)  || \
                                 ((x) == ALD_UART_STATUS_TSBUSY)  || \
                                 ((x) == ALD_UART_STATUS_TFEMPTY) || \
                                 ((x) == ALD_UART_STATUS_TFOERR))
#define IS_UART_IT(x)       (((x) == ALD_UART_IT_RXBERR)  || \
                                 ((x) == ALD_UART_IT_ABEND)   || \
                                 ((x) == ALD_UART_IT_ABTO)    || \
                                 ((x) == ALD_UART_IT_DCTS)    || \
                                 ((x) == ALD_UART_IT_RXTO)    || \
                                 ((x) == ALD_UART_IT_ADDRM)   || \
                                 ((x) == ALD_UART_IT_LINBK)   || \
                                 ((x) == ALD_UART_IT_EOB)     || \
                                 ((x) == ALD_UART_IT_NOISE)   || \
                                 ((x) == ALD_UART_IT_RFNEMPTY)    || \
                                 ((x) == ALD_UART_IT_RFOERR)  || \
                                 ((x) == ALD_UART_IT_RFUERR)  || \
                                 ((x) == ALD_UART_IT_TBC) || \
                                 ((x) == ALD_UART_IT_TFEMPTY) || \
                                 ((x) == ALD_UART_IT_TFOERR))
#define IS_UART_IF(x)       (((x) == ALD_UART_IF_RXBERR)  || \
                                 ((x) == ALD_UART_IF_ABEND)   || \
                                 ((x) == ALD_UART_IF_ABTO)    || \
                                 ((x) == ALD_UART_IF_DCTS)    || \
                                 ((x) == ALD_UART_IF_RXTO)    || \
                                 ((x) == ALD_UART_IF_ADDRM)   || \
                                 ((x) == ALD_UART_IF_LINBK)   || \
                                 ((x) == ALD_UART_IF_EOB)     || \
                                 ((x) == ALD_UART_IF_NOISE)   || \
                                 ((x) == ALD_UART_IF_RFNEMPTY)    || \
                                 ((x) == ALD_UART_IF_RFOERR)  || \
                                 ((x) == ALD_UART_IF_RFUERR)  || \
                                 ((x) == ALD_UART_IF_TBC) || \
                                 ((x) == ALD_UART_IF_TFEMPTY) || \
                                 ((x) == ALD_UART_IF_TFOVER))
#define IS_UART_SCARD_CLK(x) (((x) <= 0x1F))
#define IS_UART_BAUDRATE(x) (((x) > 0) && ((x) < 0x44AA21))
#define IS_UART_DATA(x)     ((x) <= 0x1FF)

#define ALD_UART_STATE_TX_MASK  (1U << 4)
#define ALD_UART_STATE_RX_MASK  (1U << 5)
/**
  * @}
  */

/** @addtogroup UART_Public_Functions
  * @{
  */

/** @addtogroup UART_Public_Functions_Group1
  * @{
  */
/* Initialization functions */
void ald_uart_init(ald_uart_handle_t *hperh);
void ald_uart_reset(ald_uart_handle_t *hperh);
void ald_uart_rs485_config(ald_uart_handle_t *hperh, ald_uart_rs485_config_t *config);
void ald_uart_scard_config(ald_uart_handle_t *hperh, ald_uart_scard_config_t *config);
/**
  * @}
  */

/** @addtogroup UART_Public_Functions_Group2
  * @{
  */
/* IO operation functions */
ald_status_t ald_uart_send(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_uart_recv(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_uart_send_n_lock(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_uart_recv_n_lock(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_uart_send_by_it(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_uart_recv_by_it(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_uart_recv_frame_by_it(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t t_out);

ald_status_t ald_uart_send_by_dma(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_uart_recv_by_dma(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_uart_dma_pause(ald_uart_handle_t *hperh);
ald_status_t ald_uart_dma_resume(ald_uart_handle_t *hperh);
ald_status_t ald_uart_dma_stop(ald_uart_handle_t *hperh);

void ald_uart_irq_handler(ald_uart_handle_t *hperh);
void ald_uart_irq_handler_fast(ald_uart_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup UART_Public_Functions_Group3
  * @{
  */
/* Peripheral Control functions */
void ald_uart_interrupt_config(ald_uart_handle_t *hperh, ald_uart_it_t it, type_func_t state);
void ald_uart_dma_req_config(ald_uart_handle_t *hperh, ald_uart_dma_req_t req, type_func_t state);
void uart_lin_break_detect_irq(ald_uart_handle_t *hperh, type_func_t status);
void ald_uart_lin_send_break(ald_uart_handle_t *hperh);
void ald_uart_lin_detect_break_len_config(ald_uart_handle_t *hperh, ald_uart_lin_break_len_t len);
void ald_uart_auto_baud_config(ald_uart_handle_t *hperh, ald_uart_auto_baud_mode_t mode);
ald_status_t ald_uart_rs485_send_addr(ald_uart_handle_t *hperh, uint16_t addr, uint32_t timeout);
it_status_t ald_uart_get_it_status(ald_uart_handle_t *hperh, ald_uart_it_t it);
flag_status_t ald_uart_get_status(ald_uart_handle_t *hperh, ald_uart_status_t status);
flag_status_t ald_uart_get_flag_status(ald_uart_handle_t *hperh, ald_uart_flag_t flag);
flag_status_t ald_uart_get_mask_flag_status(ald_uart_handle_t *hperh, ald_uart_flag_t flag);
void ald_uart_clear_flag_status(ald_uart_handle_t *hperh, ald_uart_flag_t flag);
/**
  * @}
  */

/** @addtogroup UART_Public_Functions_Group4
  * @{
  */
/* Peripheral State and Errors functions */
ald_uart_state_t ald_uart_get_state(ald_uart_handle_t *hperh);
uint32_t ald_uart_get_error(ald_uart_handle_t *hperh);
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

#endif /* __ALD_UART_H__ */
