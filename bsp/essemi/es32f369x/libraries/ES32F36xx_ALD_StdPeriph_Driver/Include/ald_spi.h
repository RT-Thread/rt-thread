/**
  *********************************************************************************
  *
  * @file    ald_spi.c
  * @brief   Header file of SPI module driver.
  *
  * @version V1.0
  * @date    13 Nov 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          13 Nov 2019     AE Team         The first version
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
#endif

#include "utils.h"
#include "ald_dma.h"

/** @addtogroup ES32FXXX_ALD
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
	SPI_CPHA_FIRST  = 0U,	/**< Transiting data in the first edge */
	SPI_CPHA_SECOND = 1U,	/**< Transiting data in the seconde edge */
} spi_cpha_t;

/**
  * @brief clock polarity
  */
typedef enum {
	SPI_CPOL_LOW  = 0U,	/**< Polarity hold low when spi-bus is idle */
	SPI_CPOL_HIGH = 1U,	/**< Polarity hold high when spi-bus is idle */
} spi_cpol_t;

/**
  * @brief master selection
  */
typedef enum {
	SPI_MODE_SLAVER = 0U,	/**< Slave mode */
	SPI_MODE_MASTER = 1U,	/**< Master mode */
} spi_mode_t;

/**
  * @brief baud rate control
  */
typedef enum {
	SPI_BAUD_2   = 0U,	/**< fpclk/2 */
	SPI_BAUD_4   = 1U,	/**< fpclk/4 */
	SPI_BAUD_8   = 2U,	/**< fpclk/8 */
	SPI_BAUD_16  = 3U,	/**< fpclk/16 */
	SPI_BAUD_32  = 4U,	/**< fpclk/32 */
	SPI_BAUD_64  = 5U,	/**< fpclk/64 */
	SPI_BAUD_128 = 6U,	/**< fpclk/128 */
	SPI_BAUD_256 = 7U,	/**< fpclk/256 */
} spi_baud_t;

/**
  * @brief frame format
  */
typedef enum {
	SPI_FIRSTBIT_MSB = 0U,	/**< MSB transmitted first */
	SPI_FIRSTBIT_LSB = 1U,	/**< LSB transmitted first */
} spi_firstbit_t;

/**
  * @brief data frame format
  */
typedef enum {
	SPI_DATA_SIZE_8  = 0U,	/**< 8-bit data frame format is selected for transmission/reception */
	SPI_DATA_SIZE_16 = 1U,	/**< 16-bit data frame format is selected for transmission/reception */
} spi_datasize_t;

/**
  * @brief SPI error status
  */
typedef enum {
	SPI_ERROR_NONE = 0U,	/**< none */
	SPI_ERROR_MODF = 1U,	/**< mode fault */
	SPI_ERROR_CRC  = 2U,	/**< crc error */
	SPI_ERROR_FRE  = 4U,	/**< frame error */ 
	SPI_ERROR_RXOV = 8U,	/**< receive over error */
	SPI_ERROR_TXOV = 0x10U,	/**< dma error  */
	SPI_ERROR_FLAG = 0x20U,	/**< interrupt flag error */
} spi_error_t;

/**
  * @brief interrupt control
  */
typedef enum {
	SPI_IT_TXE    = (1U << 0),	/**< Transmit fifo empty interrupt */
	SPI_IT_TXOV   = (1U << 2),	/**< Transmit fifo overflow interrupt */
	SPI_IT_TXUD   = (1U << 3),	/**< Transmit fifo underflow interrupt */
	SPI_IT_TXTH   = (1U << 4),	/**< Transmit fifo under threshold interrupt */
	SPI_IT_RXF    = (1U << 9),	/**< Receive fifo full interrupt */
	SPI_IT_RXOV   = (1U << 10),	/**< Receive fifo overflow interrupt */
	SPI_IT_RXUD   = (1U << 11),	/**< Receive fifo underflow interrupt */
	SPI_IT_RXTH   = (1U << 12),	/**< Receive fifo over threshold interrupt */
	SPI_IT_CRCERR = (1U << 16),	/**< Crc error interrupt */
	SPI_IT_MODF   = (1U << 17),	/**< Mode error interrupt */
	SPI_IT_FRE    = (1U << 18),	/**< Frame error interrupt */
} spi_it_t;

/**
  * @brief interrupt flag
  */
typedef enum {
	SPI_IF_TXE    = (1U << 0),	/**< Transmit fifo empty interrupt flag */
	SPI_IF_TXOV   = (1U << 2),	/**< Transmit fifo overflow interrupt flag */
	SPI_IF_TXUD   = (1U << 3),	/**< Transmit fifo underflow interrupt flag */
	SPI_IF_TXTH   = (1U << 4),	/**< Transmit fifo under threshold interrupt flag */
	SPI_IF_RXF    = (1U << 9),	/**< Receive fifo full interrupt flag */
	SPI_IF_RXOV   = (1U << 10),	/**< Receive fifo overflow interrupt flag */
	SPI_IF_RXUD   = (1U << 11),	/**< Receive fifo underflow interrupt flag */
	SPI_IF_RXTH   = (1U << 12),	/**< Receive fifo over threshold interrupt flag */
	SPI_IF_CRCERR = (1U << 16),	/**< Crc error interrupt flag */
	SPI_IF_MODF   = (1U << 17),	/**< Mode error interrupt flag */
	SPI_IF_FRE    = (1U << 18),	/**< Frame error interrupt flag */
} spi_flag_t;

/**
  * @brief SPI state structures definition
  */
typedef enum {
	SPI_STATE_RESET      = 0x00U,	/**< Peripheral is not initialized */
	SPI_STATE_READY      = 0x01U,	/**< Peripheral Initialized and ready for use */
	SPI_STATE_BUSY       = 0x02U,	/**< an internal process is ongoing */
	SPI_STATE_BUSY_TX    = 0x11U,	/**< transmit is ongoing */
	SPI_STATE_BUSY_RX    = 0x21U,	/**< receive is ongoing */
	SPI_STATE_BUSY_TX_RX = 0x31U,	/**< transmit and receive are ongoing */
	SPI_STATE_TIMEOUT    = 0x03U,	/**< Timeout state */
	SPI_STATE_ERROR      = 0x04U,	/**< Error */
} spi_state_t;


/**
  * @brief SPI direction definition
  */
typedef enum {
	SPI_DIRECTION_2LINES        = 0U,	/**< 2 lines */
	SPI_DIRECTION_2LINES_RXONLY = 1U,	/**< 2 lines only rx */
	SPI_DIRECTION_1LINE         = 2U,	/**< 1 line */
	SPI_DIRECTION_1LINE_RX      = 3U,	/**< 1 line only rx */
} spi_direction_t;

/**
  * @brief SPI dma request definition
  */
typedef enum {
	SPI_DMA_REQ_TX = 0U,	/**< TX dma request */
	SPI_DMA_REQ_RX = 1U,	/**< RX dma request */
} spi_dma_req_t;

/**
  * @brief SPI crc length definition
  */
typedef enum {
	SPI_FRAME_MOTOROLA = 0U,	/**< SPI motorola mode */
	SPI_FRAME_TI       = 1U,	/**< SPI TI mode */
} spi_frame_t;

/**
  * @brief SPI status definition
  */
typedef enum {
	SPI_STATUS_TXE  = (1U << 0),	/**< Transmit fifo empty status */
	SPI_STATUS_TXF  = (1U << 1),	/**< Transmit fifo full status */
	SPI_STATUS_TXOV = (1U << 2),	/**< Transmit fifo overflow status */
	SPI_STATUS_TXUD = (1U << 3),    /**< Transmit fifo underflow status */
	SPI_STATUS_TXTH = (1U << 4),    /**< Transmit fifo under threshold status */
	SPI_STATUS_RXE  = (1U << 8),    /**< Receive fifo empty status */
	SPI_STATUS_RXF  = (1U << 9),    /**< Receive fifo full status */
	SPI_STATUS_RXOV = (1U << 10),   /**< Receive fifo overflow status */
	SPI_STATUS_RXUD = (1U << 11),   /**< Receive fifo underflow status */
	SPI_STATUS_RXTH = (1U << 12),   /**< Receive fifo under threshold status */
	SPI_STATUS_BUSY = (1U << 15),   /**< BUSY status */
} spi_status_t;

/**
  * @brief SPI TXE/RXNE status definition
  */
typedef enum {
	SPI_SR_TXE      = 0U,	/**< SR.TXE set */
	SPI_SR_RXNE     = 1U,	/**< SR.RXTH set */
	SPI_SR_TXE_RXNE = 2U,	/**< SR.TXE and SR.RXNE set */
} spi_sr_status_t;


/**
  * @brief SPI init structure definition
  */
typedef struct {
	spi_mode_t mode;		/**< SPI mode */
	spi_direction_t dir;		/**< SPI direction */
	spi_datasize_t data_size;	/**< SPI data size */
	spi_baud_t baud;		/**< SPI baudrate prescaler */
	spi_cpha_t phase;		/**< SPI clock phase */
	spi_cpol_t polarity;		/**< SPI clock polarity */
	spi_firstbit_t first_bit;	/**< SPI first bit */
	type_func_t ss_en;		/**< SPI ssm enable or disable */
	type_func_t crc_calc;		/**< SPI crc calculation */
	spi_frame_t frame;              /**< SPI frame format */
	uint16_t crc_poly;		/**< SPI crc polynomial */
} spi_init_t;

/**
  * @brief  SPI handle structure definition
  */
typedef struct spi_handle_s {
	SPI_I2S_TypeDef *perh;	/**< SPI registers base address */
	spi_init_t init;	/**< SPI communication parameters */
	uint8_t *tx_buf;	/**< Pointer to SPI Tx transfer buffer */
	uint16_t tx_size;	/**< SPI Tx transfer size */
	uint16_t tx_count;	/**< SPI Tx transfer counter */
	uint8_t *rx_buf;	/**< Pointer to SPI Rx transfer buffer */
	uint16_t rx_size;	/**< SPI Rx Transfer size */
	uint16_t rx_count;	/**< SPI Rx Transfer Counter */

	dma_handle_t hdmatx;	/**< SPI Tx DMA handle parameters */
	dma_handle_t hdmarx;	/**< SPI Rx DMA handle parameters */

	lock_state_t lock;	/**< Locking object */
	spi_state_t state;	/**< SPI communication state */
	uint32_t err_code;	/**< SPI error code */

	void (*tx_cplt_cbk)(struct spi_handle_s *arg);		/**< Tx completed callback */
	void (*rx_cplt_cbk)(struct spi_handle_s *arg);		/**< Rx completed callback */
	void (*tx_rx_cplt_cbk)(struct spi_handle_s *arg);	/**< Tx & Rx completed callback */
	void (*err_cbk)(struct spi_handle_s *arg);		/**< error callback */
} spi_handle_t;
/**
  * @}
  */

/** @defgroup SPI_Public_Macros SPI Public Macros
  * @{
  */
#define SPI_RESET_HANDLE_STATE(x)	((x)->state = SPI_STATE_RESET)
#define SPI_ENABLE(x)			((x)->perh->CON1 |= (1 << SPI_CON1_SPIEN_POS))
#define SPI_DISABLE(x)			((x)->perh->CON1 &= ~(1 << SPI_CON1_SPIEN_POS))
#define SPI_CRC_RESET(x)					\
do {								\
	CLEAR_BIT((x)->perh->CON1, SPI_CON1_CRCEN_MSK);		\
	SET_BIT((x)->perh->CON1, SPI_CON1_CRCEN_MSK);		\
} while (0)
#define SPI_CRCNEXT_ENABLE(x)	(SET_BIT((x)->perh->CON1, SPI_CON1_NXTCRC_MSK))
#define SPI_CRCNEXT_DISABLE(x)	(CLEAR_BIT((x)->perh->CON1, SPI_CON1_NXTCRC_MSK))
#define SPI_RXONLY_ENABLE(x)	(SET_BIT((x)->perh->CON1, SPI_CON1_RXO_MSK))
#define SPI_RXONLY_DISABLE(x)	(CLEAR_BIT((x)->perh->CON1, SPI_CON1_RXO_MSK))
#define SPI_1LINE_TX(x)		(SET_BIT((x)->perh->CON1, SPI_CON1_BIDOEN_MSK))
#define SPI_1LINE_RX(x)		(CLEAR_BIT((x)->perh->CON1, SPI_CON1_BIDOEN_MSK))
#define SPI_SSI_HIGH(x)		(SET_BIT((x)->perh->CON1, SPI_CON1_SSOUT_MSK))
#define SPI_SSI_LOW(x)		(CLEAR_BIT((x)->perh->CON1, SPI_CON1_SSOUT_MSK))
#define SPI_SSOE_ENABLE(x)	(SET_BIT((x)->perh->CON2, SPI_CON2_NSSOE_MSK))
#define SPI_SSOE_DISABLE(x)	(CLEAR_BIT((x)->perh->CON2, SPI_CON2_NSSOE_MSK))
/**
  * @}
  */

/** @defgroup SPI_Private_Macros   SPI Private Macros
  * @{
  */
#define IS_SPI(x)	(((x) == SPI0) || \
                         ((x) == SPI1) || \
                         ((x) == SPI2))
#define IS_SPI_CPHA(x)	(((x) == SPI_CPHA_FIRST) || \
                         ((x) == SPI_CPHA_SECOND))
#define IS_SPI_CPOL(x)	(((x) == SPI_CPOL_LOW) || \
                         ((x) == SPI_CPOL_HIGH))
#define IS_SPI_MODE(x)	(((x) == SPI_MODE_SLAVER) || \
                         ((x) == SPI_MODE_MASTER))
#define IS_SPI_FIRBIT(x) (((x) == SPI_FIRSTBIT_MSB) || \
                          ((x) == SPI_FIRSTBIT_LSB))
#define IS_SPI_BAUD(x)	(((x) == SPI_BAUD_2)   || \
                         ((x) == SPI_BAUD_4)   || \
                         ((x) == SPI_BAUD_8)   || \
                         ((x) == SPI_BAUD_16)  || \
                         ((x) == SPI_BAUD_32)  || \
                         ((x) == SPI_BAUD_64)  || \
                         ((x) == SPI_BAUD_128) || \
                         ((x) == SPI_BAUD_256))
#define IS_SPI_DATASIZE(x)	(((x) == SPI_DATA_SIZE_8) || \
                                 ((x) == SPI_DATA_SIZE_16))
#define IS_SPI_BIDOE(x)		(((x) == SPI_BID_RX) || \
                                 ((x) == SPI_BID_TX))
#define IS_SPI_BIDMODE(x)	(((x) == SPI_BIDMODE_DUAL) || \
                                 ((x) == SPI_BIDMODE_SOLE))
#define IS_SPI_DIRECTION(x)	(((x) == SPI_DIRECTION_2LINES)         || \
                                 ((x) == SPI_DIRECTION_2LINES_RXONLY)  || \
                                 ((x) == SPI_DIRECTION_1LINE)          || \
				 ((x) == SPI_DIRECTION_1LINE_RX))
#define IS_SPI_DMA_REQ(x)	(((x) == SPI_DMA_REQ_TX) || \
                                 ((x) == SPI_DMA_REQ_RX))
#define IS_SPI_STATUS(x)	(((x) == SPI_STATUS_TXE)    || \
				 ((x) == SPI_STATUS_TXF)    || \
				 ((x) == SPI_STATUS_TXOV)   || \
				 ((x) == SPI_STATUS_TXUD)   || \
				 ((x) == SPI_STATUS_TXTH)   || \
				 ((x) == SPI_STATUS_RXE)    || \
				 ((x) == SPI_STATUS_RXF)    || \
				 ((x) == SPI_STATUS_RXOV)   || \
				 ((x) == SPI_STATUS_RXUD)   || \
				 ((x) == SPI_STATUS_RXTH)   || \
				 ((x) == SPI_STATUS_BUSY))
#define IS_SPI_IT(x)		(((x) == SPI_IT_TXE)    || \
				 ((x) == SPI_IT_TXOV)   || \
				 ((x) == SPI_IT_TXUD)   || \
				 ((x) == SPI_IT_TXTH)   || \
				 ((x) == SPI_IT_RXF)    || \
				 ((x) == SPI_IT_RXOV)   || \
				 ((x) == SPI_IT_RXUD)   || \
				 ((x) == SPI_IT_RXTH)   || \
				 ((x) == SPI_IT_CRCERR) || \
				 ((x) == SPI_IT_MODF)   || \
				 ((x) == SPI_IT_FRE))
#define IS_SPI_IF(x)		(((x) == SPI_IF_TXE)    || \
				 ((x) == SPI_IF_TXOV)   || \
				 ((x) == SPI_IF_TXUD)   || \
				 ((x) == SPI_IF_TXTH)   || \
				 ((x) == SPI_IF_RXF)    || \
				 ((x) == SPI_IF_RXOV)   || \
				 ((x) == SPI_IF_RXUD)   || \
				 ((x) == SPI_IF_RXTH)   || \
				 ((x) == SPI_IF_CRCERR) || \
				 ((x) == SPI_IF_MODF)   || \
				 ((x) == SPI_IF_FRE))
#define IS_SPI_FRAME(x)		(((x) == SPI_FRAME_MOTOROLA) || \
				 ((x) == SPI_FRAME_TI) )
/**
  * @}
  */

/** @addtogroup SPI_Public_Functions
  * @{
  */

/** @addtogroup SPI_Public_Functions_Group1
  * @{
  */

ald_status_t ald_spi_init(spi_handle_t *hperh);
void ald_spi_reset(spi_handle_t *hperh);
/**
  * @}
  */
/** @addtogroup SPI_Public_Functions_Group2
  * @{
  */
int32_t ald_spi_send_byte_fast(spi_handle_t *hperh, uint8_t data);
int32_t ald_spi_send_byte_fast_1line(spi_handle_t *hperh, uint8_t data);
uint8_t ald_spi_recv_byte_fast(spi_handle_t *hperh, int *status);
ald_status_t ald_spi_send_bytes_fast(spi_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_spi_master_recv_bytes_fast(spi_handle_t *hperh, uint8_t *buf, uint32_t size);
ald_status_t ald_spi_slave_recv_bytes_fast(spi_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_spi_send_dbytes_fast(spi_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout);
ald_status_t ald_spi_master_recv_dbytes_fast(spi_handle_t *hperh, uint8_t *buf, uint32_t size);
ald_status_t ald_spi_slave_recv_dbytes_fast(spi_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout);
/**
  * @}
  */
/** @addtogroup SPI_Public_Functions_Group3
  * @{
  */
ald_status_t ald_spi_send(spi_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_spi_recv(spi_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_spi_send_recv(spi_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size, uint32_t timeout);
ald_status_t ald_spi_send_by_it(spi_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_spi_recv_by_it(spi_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_spi_send_recv_by_it(spi_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size);

ald_status_t ald_spi_send_by_dma(spi_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_spi_recv_by_dma(spi_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_spi_send_recv_by_dma(spi_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size, uint8_t tx_channel, uint8_t rx_channel);
ald_status_t ald_spi_dma_pause(spi_handle_t *hperh);
ald_status_t ald_spi_dma_resume(spi_handle_t *hperh);
ald_status_t ald_spi_dma_stop(spi_handle_t *hperh);

/**
  * @}
  */
/** @addtogroup SPI_Public_Functions_Group4
  * @{
  */
void ald_spi_irq_handler(spi_handle_t *hperh);
void ald_spi_interrupt_config(spi_handle_t *hperh, spi_it_t it, type_func_t state);
void ald_spi_speed_config(spi_handle_t *hperh, spi_baud_t speed);
void ald_spi_dma_req_config(spi_handle_t *hperh, spi_dma_req_t req, type_func_t state);
it_status_t ald_spi_get_it_status(spi_handle_t *hperh, spi_it_t it);
flag_status_t spi_get_status(spi_handle_t *hperh, spi_status_t status);
flag_status_t ald_spi_get_flag_status(spi_handle_t *hperh, spi_flag_t flag);
void ald_spi_clear_flag_status(spi_handle_t *hperh, spi_flag_t flag);
/**
  * @}
  */
/** @addtogroup SPI_Public_Functions_Group5
  * @{
  */
spi_state_t ald_spi_get_state(spi_handle_t *hperh);
uint32_t ald_spi_get_error(spi_handle_t *hperh);
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
#endif
#endif
