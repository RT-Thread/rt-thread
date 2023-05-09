/**
  *********************************************************************************
  *
  * @file    ald_spi.c
  * @brief   Header file of SPI module driver.
  *
  * @version V1.0
  * @date    23 Feb. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          23 Feb. 2023    Lisq            The first version
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

#ifndef __ALD_SPI_H__
#define __ALD_SPI_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "ald_dma.h"
#include "ald_syscfg.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/** @defgroup SPI_Public_Types SPI Public Types
  * @{
  */

/**
  * @brief clock phase
  */
typedef enum {
    ALD_SPI_CPHA_FIRST  = 0U,   /**< Transiting data in the first edge */
    ALD_SPI_CPHA_SECOND = 1U,   /**< Transiting data in the seconde edge */
} ald_spi_cpha_t;

/**
  * @brief clock polarity
  */
typedef enum {
    ALD_SPI_CPOL_LOW  = 0U, /**< Polarity hold low when spi-bus is idle */
    ALD_SPI_CPOL_HIGH = 1U, /**< Polarity hold high when spi-bus is idle */
} ald_spi_cpol_t;

/**
  * @brief master selection
  */
typedef enum {
    ALD_SPI_MODE_SLAVER = 0U,   /**< Slave mode */
    ALD_SPI_MODE_MASTER = 1U,   /**< Master mode */
} ald_spi_mode_t;

/**
  * @brief baud rate control
  */
typedef enum {
    ALD_SPI_BAUD_2   = 0U,  /**< fpclk/2 */
    ALD_SPI_BAUD_4   = 1U,  /**< fpclk/4 */
    ALD_SPI_BAUD_8   = 2U,  /**< fpclk/8 */
    ALD_SPI_BAUD_16  = 3U,  /**< fpclk/16 */
    ALD_SPI_BAUD_32  = 4U,  /**< fpclk/32 */
    ALD_SPI_BAUD_64  = 5U,  /**< fpclk/64 */
    ALD_SPI_BAUD_128 = 6U,  /**< fpclk/128 */
    ALD_SPI_BAUD_256 = 7U,  /**< fpclk/256 */
} ald_spi_baud_t;

/**
  * @brief frame format
  */
typedef enum {
    ALD_SPI_FIRSTBIT_MSB = 0U,  /**< MSB transmitted first */
    ALD_SPI_FIRSTBIT_LSB = 1U,  /**< LSB transmitted first */
} ald_spi_firstbit_t;

/**
  * @brief data frame format
  */
typedef enum {
    ALD_SPI_DATA_SIZE_8  = 0U,  /**< 8-bit data frame format is selected for transmission/reception */
    ALD_SPI_DATA_SIZE_16 = 1U,  /**< 16-bit data frame format is selected for transmission/reception */
} ald_spi_datasize_t;

/**
  * @brief SPI error status
  */
typedef enum {
    ALD_SPI_ERROR_NONE = 0U,    /**< none */
    ALD_SPI_ERROR_MODF = 1U,    /**< mode fault */
    ALD_SPI_ERROR_CRC  = 2U,    /**< crc error */
    ALD_SPI_ERROR_FRE  = 4U,    /**< frame error */
    ALD_SPI_ERROR_RXOV = 8U,    /**< receive over error */
    ALD_SPI_ERROR_TXOV = 0x10U, /**< dma error  */
    ALD_SPI_ERROR_FLAG = 0x20U, /**< interrupt flag error */
} ald_spi_error_t;

/**
  * @brief interrupt control
  */
typedef enum {
    ALD_SPI_IT_TXE    = (1U << 0),  /**< Transmit fifo empty interrupt */
    ALD_SPI_IT_TXOV   = (1U << 2),  /**< Transmit fifo overflow interrupt */
    ALD_SPI_IT_TXUD   = (1U << 3),  /**< Transmit fifo underflow interrupt */
    ALD_SPI_IT_TXTH   = (1U << 4),  /**< Transmit fifo under threshold interrupt */
    ALD_SPI_IT_RXNE   = (1U << 8),  /**< Receive fifo not empty interrupt */
    ALD_SPI_IT_RXF    = (1U << 9),  /**< Receive fifo full interrupt */
    ALD_SPI_IT_RXOV   = (1U << 10), /**< Receive fifo overflow interrupt */
    ALD_SPI_IT_RXUD   = (1U << 11), /**< Receive fifo underflow interrupt */
    ALD_SPI_IT_RXTH   = (1U << 12), /**< Receive fifo over threshold interrupt */
    ALD_SPI_IT_CRCERR = (1U << 16), /**< Crc error interrupt */
    ALD_SPI_IT_MODF   = (1U << 17), /**< Mode error interrupt */
    ALD_SPI_IT_FRE    = (1U << 18), /**< Frame error interrupt */
} ald_spi_it_t;

/**
  * @brief interrupt flag
  */
typedef enum {
    ALD_SPI_IF_TXE    = (1U << 0),  /**< Transmit fifo empty interrupt flag */
    ALD_SPI_IF_TXOV   = (1U << 2),  /**< Transmit fifo overflow interrupt flag */
    ALD_SPI_IF_TXUD   = (1U << 3),  /**< Transmit fifo underflow interrupt flag */
    ALD_SPI_IF_TXTH   = (1U << 4),  /**< Transmit fifo under threshold interrupt flag */
    ALD_SPI_IF_RXNE   = (1U << 8),  /**< Receive fifo not empty interrupt flag */
    ALD_SPI_IF_RXF    = (1U << 9),  /**< Receive fifo full interrupt flag */
    ALD_SPI_IF_RXOV   = (1U << 10), /**< Receive fifo overflow interrupt flag */
    ALD_SPI_IF_RXUD   = (1U << 11), /**< Receive fifo underflow interrupt flag */
    ALD_SPI_IF_RXTH   = (1U << 12), /**< Receive fifo over threshold interrupt flag */
    ALD_SPI_IF_CRCERR = (1U << 16), /**< Crc error interrupt flag */
    ALD_SPI_IF_MODF   = (1U << 17), /**< Mode error interrupt flag */
    ALD_SPI_IF_FRE    = (1U << 18), /**< Frame error interrupt flag */
} ald_spi_flag_t;

/**
  * @brief SPI state structures definition
  */
typedef enum {
    ALD_SPI_STATE_RESET      = 0x00U,   /**< Peripheral is not initialized */
    ALD_SPI_STATE_READY      = 0x01U,   /**< Peripheral Initialized and ready for use */
    ALD_SPI_STATE_BUSY       = 0x02U,   /**< an internal process is ongoing */
    ALD_SPI_STATE_BUSY_TX    = 0x11U,   /**< transmit is ongoing */
    ALD_SPI_STATE_BUSY_RX    = 0x21U,   /**< receive is ongoing */
    ALD_SPI_STATE_BUSY_TX_RX = 0x31U,   /**< transmit and receive are ongoing */
    ALD_SPI_STATE_TIMEOUT    = 0x03U,   /**< Timeout state */
    ALD_SPI_STATE_ERROR      = 0x04U,   /**< Error */
} ald_spi_state_t;

/**
  * @brief SPI direction definition
  */
typedef enum {
    ALD_SPI_DIRECTION_2LINES        = 0U,   /**< 2 lines */
    ALD_SPI_DIRECTION_2LINES_RXONLY = 1U,   /**< 2 lines only rx */
    ALD_SPI_DIRECTION_1LINE         = 2U,   /**< 1 line */
    ALD_SPI_DIRECTION_1LINE_RX      = 3U,   /**< 1 line only rx */
} ald_spi_direction_t;

/**
  * @brief SPI dma request definition
  */
typedef enum {
    ALD_SPI_DMA_REQ_TX = 0U,    /**< TX dma request */
    ALD_SPI_DMA_REQ_RX = 1U,    /**< RX dma request */
} ald_spi_dma_req_t;

/**
  * @brief SPI crc length definition
  */
typedef enum {
    ALD_SPI_FRAME_MOTOROLA = 0U,    /**< SPI motorola mode */
    ALD_SPI_FRAME_TI       = 1U,    /**< SPI TI mode */
} ald_spi_frame_t;

/**
  * @brief SPI status definition
  */
typedef enum {
    ALD_SPI_STATUS_TXE  = (1U << 0),    /**< Transmit fifo empty status */
    ALD_SPI_STATUS_TXF  = (1U << 1),    /**< Transmit fifo full status */
    ALD_SPI_STATUS_TXOV = (1U << 2),    /**< Transmit fifo overflow status */
    ALD_SPI_STATUS_TXUD = (1U << 3),    /**< Transmit fifo underflow status */
    ALD_SPI_STATUS_TXTH = (1U << 4),    /**< Transmit fifo under threshold status */
    ALD_SPI_STATUS_RXNE = (1U << 8),    /**< Receive fifo not empty status */
    ALD_SPI_STATUS_RXF  = (1U << 9),    /**< Receive fifo full status */
    ALD_SPI_STATUS_RXOV = (1U << 10),   /**< Receive fifo overflow status */
    ALD_SPI_STATUS_RXUD = (1U << 11),   /**< Receive fifo underflow status */
    ALD_SPI_STATUS_RXTH = (1U << 12),   /**< Receive fifo under threshold status */
    ALD_SPI_STATUS_BUSY = (1U << 15),   /**< BUSY status */
} ald_spi_status_t;

/**
  * @brief SPI TXE/RXNE status definition
  */
typedef enum {
    ALD_SPI_SR_TXE      = 0U,   /**< SR.TXE set */
    ALD_SPI_SR_RXNE     = 1U,   /**< SR.RXTH set */
    ALD_SPI_SR_TXE_RXNE = 2U,   /**< SR.TXE and SR.RXNE set */
} ald_spi_sr_status_t;


/**
  * @brief SPI init structure definition
  */
typedef struct {
    ald_spi_mode_t mode;        /**< SPI mode */
    ald_spi_direction_t dir;        /**< SPI direction */
    ald_spi_datasize_t data_size;   /**< SPI data size */
    ald_spi_baud_t baud;        /**< SPI baudrate prescaler */
    ald_spi_cpha_t phase;       /**< SPI clock phase */
    ald_spi_cpol_t polarity;        /**< SPI clock polarity */
    ald_spi_firstbit_t first_bit;   /**< SPI first bit */
    type_func_t ss_en;      /**< SPI ssm enable or disable */
    type_func_t crc_calc;       /**< SPI crc calculation */
    ald_spi_frame_t frame;              /**< SPI frame format */
    uint16_t crc_poly;      /**< SPI crc polynomial */
} ald_spi_init_t;

/**
  * @brief  SPI handle structure definition
  */
typedef struct ald_spi_handle_s {
    SPI_I2S_TypeDef *perh;  /**< SPI registers base address */
    ald_spi_init_t init;    /**< SPI communication parameters */
    uint8_t *tx_buf;    /**< Pointer to SPI Tx transfer buffer */
    uint16_t tx_size;   /**< SPI Tx transfer size */
    uint16_t tx_count;  /**< SPI Tx transfer counter */
    uint8_t *rx_buf;    /**< Pointer to SPI Rx transfer buffer */
    uint16_t rx_size;   /**< SPI Rx Transfer size */
    uint16_t rx_count;  /**< SPI Rx Transfer Counter */

    ald_dma_handle_t hdmatx;    /**< SPI Tx DMA handle parameters */
    ald_dma_handle_t hdmarx;    /**< SPI Rx DMA handle parameters */

    lock_state_t lock;  /**< Locking object */
    ald_spi_state_t state;  /**< SPI communication state */
    uint32_t err_code;  /**< SPI error code */

    void (*tx_cplt_cbk)(struct ald_spi_handle_s *arg);      /**< Tx completed callback */
    void (*rx_cplt_cbk)(struct ald_spi_handle_s *arg);      /**< Rx completed callback */
    void (*tx_rx_cplt_cbk)(struct ald_spi_handle_s *arg);   /**< Tx & Rx completed callback */
    void (*err_cbk)(struct ald_spi_handle_s *arg);      /**< error callback */
} ald_spi_handle_t;
/**
  * @}
  */

/** @defgroup SPI_Public_Macros SPI Public Macros
  * @{
  */
#define ALD_SPI_RESET_HANDLE_STATE(x)   ((x)->state = ALD_SPI_STATE_RESET)
#define ALD_SPI_ENABLE(x)           ((x)->perh->CON1 |= (1 << SPI_CON1_SPIEN_POS))
#define ALD_SPI_DISABLE(x)          ((x)->perh->CON1 &= ~(1 << SPI_CON1_SPIEN_POS))
#define ALD_SPI_CRC_RESET(x)                    \
do {                                \
    CLEAR_BIT((x)->perh->CON1, SPI_CON1_CRCEN_MSK);     \
    SET_BIT((x)->perh->CON1, SPI_CON1_CRCEN_MSK);       \
} while (0)
#define ALD_SPI_CRCNEXT_ENABLE(x)   (SET_BIT((x)->perh->CON1, SPI_CON1_NXTCRC_MSK))
#define ALD_SPI_CRCNEXT_DISABLE(x)  (CLEAR_BIT((x)->perh->CON1, SPI_CON1_NXTCRC_MSK))
#define ALD_SPI_RXONLY_ENABLE(x)    (SET_BIT((x)->perh->CON1, SPI_CON1_RXO_MSK))
#define ALD_SPI_RXONLY_DISABLE(x)   (CLEAR_BIT((x)->perh->CON1, SPI_CON1_RXO_MSK))
#define ALD_SPI_1LINE_TX(x)     (SET_BIT((x)->perh->CON1, SPI_CON1_BIDOEN_MSK))
#define ALD_SPI_1LINE_RX(x)     (CLEAR_BIT((x)->perh->CON1, SPI_CON1_BIDOEN_MSK))
#define ALD_SPI_SSI_HIGH(x)     (SET_BIT((x)->perh->CON1, SPI_CON1_SSOUT_MSK))
#define ALD_SPI_SSI_LOW(x)      (CLEAR_BIT((x)->perh->CON1, SPI_CON1_SSOUT_MSK))
#define ALD_SPI_SSOE_ENABLE(x)  (SET_BIT((x)->perh->CON2, SPI_CON2_NSSOE_MSK))
#define ALD_SPI_SSOE_DISABLE(x) (CLEAR_BIT((x)->perh->CON2, SPI_CON2_NSSOE_MSK))
/**
  * @}
  */

/** @defgroup SPI_Private_Macros   SPI Private Macros
  * @{
  */
#define IS_SPI(x)   (((x) == SPI0) || \
                         ((x) == SPI1))
#define IS_SPI_CPHA(x)  (((x) == ALD_SPI_CPHA_FIRST) || \
                         ((x) == ALD_SPI_CPHA_SECOND))
#define IS_SPI_CPOL(x)  (((x) == ALD_SPI_CPOL_LOW) || \
                         ((x) == ALD_SPI_CPOL_HIGH))
#define IS_SPI_MODE(x)  (((x) == ALD_SPI_MODE_SLAVER) || \
                         ((x) == ALD_SPI_MODE_MASTER))
#define IS_SPI_FIRBIT(x) (((x) == ALD_SPI_FIRSTBIT_MSB) || \
                          ((x) == ALD_SPI_FIRSTBIT_LSB))
#define IS_SPI_BAUD(x)  (((x) == ALD_SPI_BAUD_2)   || \
                         ((x) == ALD_SPI_BAUD_4)   || \
                         ((x) == ALD_SPI_BAUD_8)   || \
                         ((x) == ALD_SPI_BAUD_16)  || \
                         ((x) == ALD_SPI_BAUD_32)  || \
                         ((x) == ALD_SPI_BAUD_64)  || \
                         ((x) == ALD_SPI_BAUD_128) || \
                         ((x) == ALD_SPI_BAUD_256))
#define IS_SPI_DATASIZE(x)  (((x) == ALD_SPI_DATA_SIZE_8) || \
                                 ((x) == ALD_SPI_DATA_SIZE_16))
#define IS_SPI_BIDOE(x)     (((x) == ALD_SPI_BID_RX) || \
                                 ((x) == ALD_SPI_BID_TX))
#define IS_SPI_BIDMODE(x)   (((x) == ALD_SPI_BIDMODE_DUAL) || \
                                 ((x) == ALD_SPI_BIDMODE_SOLE))
#define IS_SPI_DIRECTION(x) (((x) == ALD_SPI_DIRECTION_2LINES)         || \
                                 ((x) == ALD_SPI_DIRECTION_2LINES_RXONLY)  || \
                                 ((x) == ALD_SPI_DIRECTION_1LINE)          || \
                 ((x) == ALD_SPI_DIRECTION_1LINE_RX))
#define IS_SPI_DMA_REQ(x)   (((x) == ALD_SPI_DMA_REQ_TX) || \
                                 ((x) == ALD_SPI_DMA_REQ_RX))
#define IS_SPI_STATUS(x)    (((x) == ALD_SPI_STATUS_TXE)    || \
                 ((x) == ALD_SPI_STATUS_TXF)    || \
                 ((x) == ALD_SPI_STATUS_TXOV)   || \
                 ((x) == ALD_SPI_STATUS_TXUD)   || \
                 ((x) == ALD_SPI_STATUS_TXTH)   || \
                 ((x) == ALD_SPI_STATUS_RXNE)   || \
                 ((x) == ALD_SPI_STATUS_RXF)    || \
                 ((x) == ALD_SPI_STATUS_RXOV)   || \
                 ((x) == ALD_SPI_STATUS_RXUD)   || \
                 ((x) == ALD_SPI_STATUS_RXTH)   || \
                 ((x) == ALD_SPI_STATUS_BUSY))
#define IS_SPI_IT(x)        (((x) == ALD_SPI_IT_TXE)    || \
                 ((x) == ALD_SPI_IT_TXOV)   || \
                 ((x) == ALD_SPI_IT_TXUD)   || \
                 ((x) == ALD_SPI_IT_TXTH)   || \
                 ((x) == ALD_SPI_IT_RXNE)   || \
                 ((x) == ALD_SPI_IT_RXF)    || \
                 ((x) == ALD_SPI_IT_RXOV)   || \
                 ((x) == ALD_SPI_IT_RXUD)   || \
                 ((x) == ALD_SPI_IT_RXTH)   || \
                 ((x) == ALD_SPI_IT_CRCERR) || \
                 ((x) == ALD_SPI_IT_MODF)   || \
                 ((x) == ALD_SPI_IT_FRE))
#define IS_SPI_IF(x)        (((x) == ALD_SPI_IF_TXE)    || \
                 ((x) == ALD_SPI_IF_TXOV)   || \
                 ((x) == ALD_SPI_IF_TXUD)   || \
                 ((x) == ALD_SPI_IF_TXTH)   || \
                 ((x) == ALD_SPI_IF_RXNE)   || \
                 ((x) == ALD_SPI_IF_RXF)    || \
                 ((x) == ALD_SPI_IF_RXOV)   || \
                 ((x) == ALD_SPI_IF_RXUD)   || \
                 ((x) == ALD_SPI_IF_RXTH)   || \
                 ((x) == ALD_SPI_IF_CRCERR) || \
                 ((x) == ALD_SPI_IF_MODF)   || \
                 ((x) == ALD_SPI_IF_FRE))
#define IS_SPI_FRAME(x)     (((x) == ALD_SPI_FRAME_MOTOROLA) || \
                 ((x) == ALD_SPI_FRAME_TI) )
/**
  * @}
  */

/** @addtogroup SPI_Public_Functions
  * @{
  */

/** @addtogroup SPI_Public_Functions_Group1
  * @{
  */

ald_status_t ald_spi_init(ald_spi_handle_t *hperh);
void ald_spi_reset(ald_spi_handle_t *hperh);
/**
  * @}
  */
/** @addtogroup SPI_Public_Functions_Group2
  * @{
  */
int32_t ald_spi_send_byte_fast(ald_spi_handle_t *hperh, uint8_t data);
int32_t ald_spi_send_byte_fast_1line(ald_spi_handle_t *hperh, uint8_t data);
uint8_t ald_spi_recv_byte_fast(ald_spi_handle_t *hperh, int *status);
ald_status_t ald_spi_send_bytes_fast(ald_spi_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_spi_master_recv_bytes_fast(ald_spi_handle_t *hperh, uint8_t *buf, uint32_t size);
ald_status_t ald_spi_slave_recv_bytes_fast(ald_spi_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_spi_send_dbytes_fast(ald_spi_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_spi_master_recv_dbytes_fast(ald_spi_handle_t *hperh, uint8_t *buf, uint32_t size);
ald_status_t ald_spi_slave_recv_dbytes_fast(ald_spi_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout);
/**
  * @}
  */
/** @addtogroup SPI_Public_Functions_Group3
  * @{
  */
ald_status_t ald_spi_send(ald_spi_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_spi_recv(ald_spi_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_spi_send_recv(ald_spi_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size, uint32_t timeout);
ald_status_t ald_spi_send_by_it(ald_spi_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_spi_recv_by_it(ald_spi_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_spi_send_recv_by_it(ald_spi_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size);

ald_status_t ald_spi_send_by_dma(ald_spi_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_spi_recv_by_dma(ald_spi_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_spi_send_recv_by_dma(ald_spi_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size, uint8_t tx_channel, uint8_t rx_channel);
ald_status_t ald_spi_dma_pause(ald_spi_handle_t *hperh);
ald_status_t ald_spi_dma_resume(ald_spi_handle_t *hperh);
ald_status_t ald_spi_dma_stop(ald_spi_handle_t *hperh);

/**
  * @}
  */
/** @addtogroup SPI_Public_Functions_Group4
  * @{
  */
void ald_spi_irq_handler(ald_spi_handle_t *hperh);
void ald_spi_interrupt_config(ald_spi_handle_t *hperh, ald_spi_it_t it, type_func_t state);
void ald_spi_speed_config(ald_spi_handle_t *hperh, ald_spi_baud_t speed);
void ald_spi_dma_req_config(ald_spi_handle_t *hperh, ald_spi_dma_req_t req, type_func_t state);
it_status_t ald_spi_get_it_status(ald_spi_handle_t *hperh, ald_spi_it_t it);
flag_status_t spi_get_status(ald_spi_handle_t *hperh, ald_spi_status_t status);
flag_status_t ald_spi_get_flag_status(ald_spi_handle_t *hperh, ald_spi_flag_t flag);
void ald_spi_clear_flag_status(ald_spi_handle_t *hperh, ald_spi_flag_t flag);
/**
  * @}
  */
/** @addtogroup SPI_Public_Functions_Group5
  * @{
  */
ald_spi_state_t ald_spi_get_state(ald_spi_handle_t *hperh);
uint32_t ald_spi_get_error(ald_spi_handle_t *hperh);
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
#endif /* __ALD_SPI_H__ */
