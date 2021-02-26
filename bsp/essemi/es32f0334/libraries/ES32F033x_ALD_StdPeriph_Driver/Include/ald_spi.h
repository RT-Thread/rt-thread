/**
  *********************************************************************************
  *
  * @file    ald_spi.c
  * @brief   Header file of SPI module driver.
  *
  * @version V1.0
  * @date    13 Nov 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
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
  * @brief interrupt control
  */
typedef enum {
	SPI_IT_ERR   = (1U << 5),	/**< error interrupt */
	SPI_IT_RXBNE = (1U << 6),	/**< rx buffer not empty interrupt */
	SPI_IT_TXBE  = (1U << 7),	/**< tx buffer empty interrupt */
} spi_it_t;

/**
  * @brief interrupt flag
  */
typedef enum {
	SPI_IF_RXBNE  = (1U << 0),	/**< receive buffer not empty */
	SPI_IF_TXBE   = (1U << 1),	/**< transmit buffer empty */
	SPI_IF_CRCERR = (1U << 4),	/**< crc error flag */
	SPI_IF_MODF   = (1U << 5),	/**< mode fault */
	SPI_IF_OVE    = (1U << 6),	/**< overrun flag */
	SPI_IF_BUSY   = (1U << 7),	/**< busy flag */
} spi_flag_t;

/**
  * @brief SPI error status
  */
typedef enum {
	SPI_ERROR_NONE = 0U,	/**< none */
	SPI_ERROR_MODF = 1U,	/**< mode fault */
	SPI_ERROR_CRC  = 2U,	/**< crc error */
	SPI_ERROR_OVE  = 4U,	/**< overrun error */
	SPI_ERROR_DMA  = 8U,	/**< dma error  */
	SPI_ERROR_FLAG = 0x10U,	/**< interrupt flag error */
} spi_error_t;



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
  * @brief SPI status definition
  */
typedef enum {
	SPI_STATUS_RXBNE   = (1U << 0),		/**< Receive not empty status */
	SPI_STATUS_TXBE    = (1U << 1),		/**< Transmit empty status */
	SPI_STATUS_CRCERR  = (1U << 4),		/**< CRC error status */
	SPI_STATUS_MODEERR = (1U << 5),		/**< Mode error status */
	SPI_STATUS_OVERR   = (1U << 6),		/**< Overflow status */
	SPI_STATUS_BUSY    = (1U << 7),		/**< Busy status */

} spi_status_t;

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
  * @brief SPI TXE/RXNE status definition
  */
typedef enum {
	SPI_SR_TXBE       = 0U,	/**< SR.TXE set */
	SPI_SR_RXBNE      = 1U,	/**< SR.RXNE set */
	SPI_SR_TXBE_RXBNE = 2U,	/**< SR.TXE and SR.RXNE set */
} spi_sr_status_t;

/**
  * @brief SPI init structure definition
  */
typedef struct {
	spi_mode_t mode;		/**< SPI mode */
	spi_direction_t dir;		/**< SPI direction */
	spi_datasize_t data_size;	/**< SPI data size */
	spi_baud_t baud;			/**< SPI baudrate prescaler */
	spi_cpha_t phase;		/**< SPI clock phase */
	spi_cpol_t polarity;		/**< SPI clock polarity */
	spi_firstbit_t first_bit;	/**< SPI first bit */
	type_func_t ss_en;		/**< SPI ssm enable or disable */
	type_func_t crc_calc;		/**< SPI crc calculation */
	uint16_t crc_poly;		/**< SPI crc polynomial */
} spi_init_t;

/**
  * @brief  SPI handle structure definition
  */
typedef struct spi_handle_s {
	SPI_TypeDef *perh;	/**< SPI registers base address */
	spi_init_t init;	/**< SPI communication parameters */
	uint8_t *tx_buf;	/**< Pointer to SPI Tx transfer buffer */
	uint16_t tx_size;	/**< SPI Tx transfer size */
	uint16_t tx_count;	/**< SPI Tx transfer counter */
	uint8_t *rx_buf;	/**< Pointer to SPI Rx transfer buffer */
	uint16_t rx_size;	/**< SPI Rx Transfer size */
	uint16_t rx_count;	/**< SPI Rx Transfer Counter */
#ifdef ALD_DMA
	dma_handle_t hdmatx;	/**< SPI Tx DMA handle parameters */
	dma_handle_t hdmarx;	/**< SPI Rx DMA handle parameters */
#endif
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
#if defined(ES32F065x) || defined(ES32F033x)
#define IS_SPI(x)	(((x) == SPI0) || ((x) == SPI1))
#endif
#if defined(ES32F093x)
#define IS_SPI(x)	(((x) == SPI0) || ((x) == SPI1) || ((x) == SPI2))
#endif
#define IS_SPI_CPHA(x)	(((x) == SPI_CPHA_FIRST) || \
                         ((x) == SPI_CPHA_SECOND))
#define IS_SPI_CPOL(x)	(((x) == SPI_CPOL_LOW) || \
                         ((x) == SPI_CPOL_HIGH))
#define IS_SPI_MODE(x)	(((x) == SPI_MODE_SLAVER) || \
                         ((x) == SPI_MODE_MASTER))
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
#define IS_SPI_FIRSTBIT(x)	(((x) == SPI_FIRSTBIT_MSB) || \
                                 ((x) == SPI_FIRSTBIT_LSB))
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
#define IS_SPI_SR_STATUS(x)	(((x) == SPI_SR_TXBE)  || \
                                 ((x) == SPI_SR_RXBNE) || \
                                 ((x) == SPI_SR_TXBE_RXBNE))
#define IS_SPI_IT(x)	(((x) == SPI_IT_ERR)   || \
                         ((x) == SPI_IT_RXBNE) || \
                         ((x) == SPI_IT_TXBE))
#define IS_SPI_IF(x)	(((x) == SPI_IF_RXBNE)  || \
                         ((x) == SPI_IF_TXBE)   || \
                         ((x) == SPI_IF_CRCERR) || \
                         ((x) == SPI_IF_MODF)   || \
                         ((x) == SPI_IF_OVE)    || \
                         ((x) == SPI_IF_BUSY))
#define IS_SPI_STATUS(x)	(((x) == SPI_STATUS_RXBNE) || \
				 ((x) == SPI_STATUS_TXBE)  || \
				 ((x) == SPI_STATUS_CRCERR) || \
				 ((x) == SPI_STATUS_MODEERR) || \
				 ((x) == SPI_STATUS_OVERR)   || \
				 ((x) == SPI_STATUS_BUSY))
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
uint8_t ald_spi_recv_byte_fast(spi_handle_t *hperh);
ald_status_t ald_spi_send(spi_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_spi_recv(spi_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_spi_send_recv(spi_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size, uint32_t timeout);
ald_status_t ald_spi_send_by_it(spi_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_spi_recv_by_it(spi_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_spi_send_recv_by_it(spi_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size);
#ifdef ALD_DMA
ald_status_t ald_spi_send_by_dma(spi_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_spi_recv_by_dma(spi_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_spi_send_recv_by_dma(spi_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size, uint8_t tx_channel, uint8_t rx_channel);
ald_status_t ald_spi_dma_pause(spi_handle_t *hperh);
ald_status_t ald_spi_dma_resume(spi_handle_t *hperh);
ald_status_t ald_spi_dma_stop(spi_handle_t *hperh);
#endif
/**
  * @}
  */

/** @addtogroup SPI_Public_Functions_Group3
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

/** @addtogroup SPI_Public_Functions_Group4
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
