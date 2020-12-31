/**
  *********************************************************************************
  *
  * @file    ald_lpuart.h
  * @brief   Header file of Low Power UART module library.
  *
  * @version V1.0
  * @date    30 May 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __ALD_LPUART_H__
#define __ALD_LPUART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"
#include "ald_dma.h"
#include "ald_cmu.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup LPUART
  * @{
  */

/**
  * @defgroup LPUART_Public_Macros LPUART Public Macros
  * @{
  */

/**
  * @defgroup LPUART_Public_Macros1 LPUART FIFO Reset
  * @{
  */
#define LPUART_FIFO_TX_RESET(hperh)	(SET_BIT((hperh)->perh->FIFOCON, LPUART_FIFOCON_TXRESET_MSK))
#define LPUART_FIFO_RX_RESET(hperh)	(SET_BIT((hperh)->perh->FIFOCON, LPUART_FIFOCON_RXRESET_MSK))
/**
  * @}
  */
/**
  * @defgroup LPUART_Public_Macros2 LPUART RS485 RX Enable
  * @{
  */
#define LPUART_RS485_RX_DISABLE(hperh)	(SET_BIT((hperh)->perh->FIFOCON, LPUART_FIFOCON_NMPMRXDIS_MSK))
#define LPUART_RS485_RX_ENABLE(hperh)	(CLEAR_BIT((hperh)->perh->FIFOCON, LPUART_FIFOCON_NMPMRXDIS_MSK))
/**
  * @}
  */
/**
  * @defgroup LPUART_Public_Macros4 LPUART LoopMode Enable
  * @{
  */
#define LPUART_LPBMOD_ENABLE(hperh)	(SET_BIT((hperh)->perh->CON0, LPUART_CON0_LPBMOD_MSK))
#define LPUART_LPBMOD_DISABLE(hperh)	(CLEAR_BIT((hperh)->perh->CON0, LPUART_CON0_LPBMOD_MSK))
/**
  * @}
  */
/**
  * @defgroup LPUART_Public_Macros5 LPUART IrDA TX Enable
  * @{
  */
#define LPUART_IRTX_ENABLE(hperh)	(SET_BIT((hperh)->perh->CON1, LPUART_CON1_IRTXE_MSK))
#define LPUART_IRTX_DISABLE(hperh)	(CLEAR_BIT((hperh)->perh->CON1, LPUART_CON1_IRTXE_MSK))
/**
  * @}
  */
/**
  * @defgroup LPUART_Public_Macros6 LPUART IRWIDTH Enable
  * @{
  */
#define LPUART_IRWIDTH_DISABLE(hperh)	(SET_BIT((hperh)->perh->CON1, LPUART_CON1_IRWIDTH_MSK))
#define LPUART_IRWIDTH_ENABLE(hperh)	(CLEAR_BIT((hperh)->perh->CON1, LPUART_CON1_IRWIDTH_MSK))
/**
  * @}
  */
/**
  * @defgroup LPUART_Public_Macros7 LPUART CTS/RTS Enable
  * @{
  */
#define LPUART_CTS_ENABLE(hperh)	(SET_BIT((hperh)->perh->CON0, LPUART_CON0_ATCTSE_MSK))
#define LPUART_CTS_DISABLE(hperh)	(CLEAR_BIT((hperh)->perh->CON0, LPUART_CON0_ATCTSE_MSK))
#define LPUART_RTS_ENABLE(hperh)	(SET_BIT((hperh)->perh->CON0, LPUART_CON0_ATRTSE_MSK))
#define LPUART_RTS_DISABLE(hperh)	(CLEAR_BIT((hperh)->perh->CON0, LPUART_CON0_ATRTSE_MSK))
/**
  * @}
  */
/**
  * @defgroup LPUART_Public_Macros8 LPUART CTS/RTS Polarity
  * @{
  */
#define LPUART_CTS_POL_LOW(hperh)	(SET_BIT((hperh)->perh->CON0, LPUART_CON0_CTSPOL_MSK))
#define LPUART_CTS_POL_HIGH(hperh)	(CLEAR_BIT((hperh)->perh->CON0, LPUART_CON0_CTSPOL_MSK))
#define LPUART_RTS_POL_LOW(hperh)	(SET_BIT((hperh)->perh->CON0, LPUART_CON0_RTSPOL_MSK))
#define LPUART_RTS_POL_HIGH(hperh)	(CLEAR_BIT((hperh)->perh->CON0, LPUART_CON0_RTSPOL_MSK))
/**
  * @}
  */
/**
  * @defgroup LPUART_Public_Macros10 LPUART Update Enable
  * @{
  */
#define LPUART_UPDATE_ENABLE(hperh)	(CLEAR_BIT((hperh)->perh->UPDATE, LPUART_UPDATE_UDIS_MSK))
#define LPUART_UPDATE_DISABLE(hperh)	(SET_BIT((hperh)->perh->UPDATE, LPUART_UPDATE_UDIS_MSK))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup LPUART_Public_Types LPUART Public Types
  * @{
  */
/**
  * @brief LPUART Word Length
  */
typedef enum {
	LPUART_WORD_LENGTH_5B = 0x0U,	/**< 5-bits */
	LPUART_WORD_LENGTH_6B = 0x1U,	/**< 6-bits */
	LPUART_WORD_LENGTH_7B = 0x2U,	/**< 7-bits */
	LPUART_WORD_LENGTH_8B = 0x3U,	/**< 8-bits */
	LPUART_WORD_LENGTH_9B = 0x4U,	/**< 9-bits */
} lpuart_word_length_t;

/**
  * @brief LPUART Stop Bits
  */
typedef enum {
	LPUART_STOP_BITS_1 = 0x0U,	/**< 1-bits */
	LPUART_STOP_BITS_2 = 0x1U,	/**< 2-bits */
} lpuart_stop_bits_t;

/**
  * @brief LPUART Parity
  */
typedef enum {
	LPUART_PARITY_NONE = 0x0U,	/**< Not parity */
	LPUART_PARITY_ODD  = 0x1U,	/**< Odd parity */
	LPUART_PARITY_EVEN = 0x3U,	/**< Even parity */
} lpuart_parity_t;

/**
  * @brief LPUART Mode
  */
typedef enum {
	LPUART_MODE_UART  = 0x0U,	/**< UART */
	LPUART_MODE_IrDA  = 0x2U,	/**< IrDA */
	LPUART_MODE_RS485 = 0x3U,	/**< RS485 */
} lpuart_mode_t;

/**
  * @brief LPUART Hardware Flow Control
  */
typedef enum {
	LPUART_HW_FLOW_CTL_NONE    = 0x0U,	/**< None */
	LPUART_HW_FLOW_CTL_RTS     = 0x1U,	/**< RTS */
	LPUART_HW_FLOW_CTL_CTS     = 0x2U,	/**< CTS */
	LPUART_HW_FLOW_CTL_RTS_CTS = 0x3U,	/**< RTS & CTS */
} lpuart_hw_flow_ctl_t;

/**
  * @brief ALD LPUART State
  */
typedef enum {
	LPUART_STATE_RESET      = 0x00U,	/**< Peripheral is not initialized */
	LPUART_STATE_READY      = 0x01U,	/**< Peripheral Initialized and ready for use */
	LPUART_STATE_BUSY       = 0x02U,	/**< an internal process is ongoing */
	LPUART_STATE_BUSY_TX    = 0x11U,	/**< Data Transmission process is ongoing */
	LPUART_STATE_BUSY_RX    = 0x21U,	/**< Data Reception process is ongoing */
	LPUART_STATE_BUSY_TX_RX = 0x31U,	/**< Data Transmission Reception process is ongoing */
	LPUART_STATE_TIMEOUT    = 0x03U,	/**< Timeout state */
	LPUART_STATE_ERROR      = 0x04U,	/**< Error */
} lpuart_state_t;

/**
  * @brief LPUART Error Codes
  */
typedef enum {
	LPUART_ERROR_NONE = ((uint32_t)0x00U),	/**< No error */
	LPUART_ERROR_PE   = ((uint32_t)0x01U),	/**< Parity error */
	LPUART_ERROR_NE   = ((uint32_t)0x02U),	/**< Noise error */
	LPUART_ERROR_FE   = ((uint32_t)0x04U),	/**< frame error */
	LPUART_ERROR_ORE  = ((uint32_t)0x08U),	/**< Overrun error */
	LPUART_ERROR_DMA  = ((uint32_t)0x10U),	/**< DMA transfer error */
} lpuart_error_t;

/**
  * @brief LPUART Init structure definition
  */
typedef struct {
	uint32_t baud;				/**< Specifies the lpuart communication baud rate */
	lpuart_word_length_t word_length;	/**< Specifies the number of data bits transmitted or received in a frame */
	lpuart_stop_bits_t stop_bits;		/**< Specifies the number of stop bits transmitted */
	lpuart_parity_t parity;			/**< Specifies the parity mode */
	lpuart_mode_t mode;			/**< Specifies uart mode */
	lpuart_hw_flow_ctl_t fctl;		/**< Specifies wether the hardware flow control mode is enabled or disabled */
	cmu_lp_perh_clock_sel_t clock;		/**< Specifies clock, only support LOSC and LRC */
} lpuart_init_t;

/**
  * @brief  LPUART handle structure definition
  */
typedef struct lpuart_handle_s {
	LPUART_TypeDef *perh;		/**< LPUART registers base address */
	lpuart_init_t init;		/**< LPUART communication parameters */
	uint8_t *tx_buf;		/**< Pointer to LPUART Tx transfer Buffer */
	uint16_t tx_size;		/**< LPUART Tx Transfer size */
	uint16_t tx_count;		/**< LPUART Tx Transfer Counter */
	uint8_t *rx_buf;		/**< Pointer to LPUART Rx transfer Buffer */
	uint16_t rx_size;		/**< LPUART Rx Transfer size */
	uint16_t rx_count;		/**< LPUART Rx Transfer Counter */
#ifdef ALD_DMA
	dma_handle_t hdmatx;		/**< LPUART Tx DMA Handle parameters */
	dma_handle_t hdmarx;		/**< LPUART Rx DMA Handle parameters */
#endif
	lock_state_t lock;            	/**< Locking object */
	lpuart_state_t state;		/**< LPUART communication state */
	lpuart_error_t err_code;	/**< LPUART Error code */

	void (*tx_cplt_cbk)(struct lpuart_handle_s *arg);	/**< Tx completed callback */
	void (*rx_cplt_cbk)(struct lpuart_handle_s *arg);	/**< Rx completed callback */
	void (*error_cbk)(struct lpuart_handle_s *arg);		/**< error callback */
} lpuart_handle_t;

/**
  * @brief LPUART RS485 Configure Structure definition
  */
typedef struct {
	type_func_t RS485_NMM;		/**< Normal Point Mode */
	type_func_t RS485_AAD;		/**< Auto-Address Detect */
	type_func_t RS485_AUD;		/**< Auto-Direction Mode */
	type_func_t RS485_ADD_DET;	/**< Eable/Disable Address Detect */
	uint8_t RS485_ADDCMP;		/**< Address for compare */
} lpuart_rs485_config_t;

/**
  * @brief LPUART DMA Requests
  */
typedef enum {
	LPUART_DMA_REQ_TX = 0x0U,	/**< TX dma */
	LPUART_DMA_REQ_RX = 0x1U,	/**< RX dma */
} lpuart_dma_req_t;

/**
  * @brief LPUART RXFIFO size
  */
typedef enum {
	LPUART_RXFIFO_1BYTE  = 0x0U,	/**< 1-Byte */
	LPUART_RXFIFO_4BYTE  = 0x1U,	/**< 4-Bytes */
	LPUART_RXFIFO_8BYTE  = 0x2U,	/**< 8-Bytes */
	LPUART_RXFIFO_14BYTE = 0x3U,	/**< 14-Bytes */
} lpuart_rxfifo_t;

/**
  * @brief LPUART Interrupts Types
  */
typedef enum {
	LPUART_IT_RBR    = (1U << 0),	/**< RBR */
	LPUART_IT_TBEMP  = (1U << 1),	/**< TBEMP */
	LPUART_IT_CTSDET = (1U << 2),	/**< CTSDET */
	LPUART_IT_RXTO   = (1U << 3),	/**< RXTO */
	LPUART_IT_RXOV   = (1U << 4),	/**< RXOV */
	LPUART_IT_TXOV   = (1U << 5),	/**< TXOV */
	LPUART_IT_CTSWK  = (1U << 7),	/**< CTSWK */
	LPUART_IT_DATWK  = (1U << 8),	/**< DATWK */
	LPUART_IT_PERR   = (1U << 9),	/**< PERR */
	LPUART_IT_FERR   = (1U << 10),	/**< FERR */
	LPUART_IT_BRKERR = (1U << 11),	/**< BRKERR */
	LPUART_IT_ADET   = (1U << 12),	/**< ADET */
	LPUART_IT_TC     = (1U << 15),	/**< TC */
} lpuart_it_t;

/**
  * @brief LPUART Flags Types
  */
typedef enum {
	LPUART_IF_RBR    = (1U << 0),	/**< RBR */
	LPUART_IF_TBEMP  = (1U << 1),	/**< TBEMP */
	LPUART_IF_CTSDET = (1U << 2),	/**< CTSDET */
	LPUART_IF_RXTO   = (1U << 3),	/**< RXTO */
	LPUART_IF_RXOV   = (1U << 4),	/**< RXOV */
	LPUART_IF_TXOV   = (1U << 5),	/**< TXOV */
	LPUART_IF_CTSWK  = (1U << 7),	/**< CTSWK */
	LPUART_IF_DATWK  = (1U << 8),	/**< DATWK */
	LPUART_IF_PERR   = (1U << 9),	/**< PERR */
	LPUART_IF_FERR   = (1U << 10),	/**< FERR */
	LPUART_IF_BRKERR = (1U << 11),	/**< BRKERR */
	LPUART_IF_ADET   = (1U << 12),	/**< ADET */
	LPUART_IF_TC     = (1U << 15),	/**< TC */
} lpuart_flag_t;

/**
  * @brief LPUART Status Types
  */
typedef enum {
	LPUART_STAT_RXEMP   = (1U << 6),	/**< RX FIFO empty */
	LPUART_STAT_RXFULL  = (1U << 7),	/**< RX FIFO full */
	LPUART_STAT_TXEMP   = (1U << 14),	/**< TX FIFO empty */
	LPUART_STAT_TXFULL  = (1U << 15),	/**< TX FIFO full */
	LPUART_STAT_TXIDLE  = (1U << 16),	/**< TX idle */
	LPUART_STAT_CTSSTAT = (1U << 17),	/**< CTS status */
	LPUART_STAT_RTSSTAT = (1U << 18),	/**< RTS status */
} lpuart_status_t;
/**
  * @}
  */

/** @defgroup LPUART_Private_Macros   LPUART Private Macros
  * @{
  */
#define IS_LPUART(x)  ((x) == LPUART0)
#define IS_LPUART_DATA(x) ((x) <= 0x1FF)
#define IS_LPUART_BAUDRATE(x) (((x) > 0) && ((x) <= 115200))
#define IS_LPUART_WORD_LENGTH(x)  (((x) == LPUART_WORD_LENGTH_5B) || \
                                   ((x) == LPUART_WORD_LENGTH_6B) || \
                                   ((x) == LPUART_WORD_LENGTH_7B) || \
                                   ((x) == LPUART_WORD_LENGTH_8B) || \
                                   ((x) == LPUART_WORD_LENGTH_9B))
#define IS_LPUART_STOPBITS(x)  (((x) == LPUART_STOP_BITS_1) || \
                                ((x) == LPUART_STOP_BITS_2))
#define IS_LPUART_PARITY(x)  (((x) == LPUART_PARITY_NONE)  || \
                              ((x) == LPUART_PARITY_ODD) || \
                              ((x) == LPUART_PARITY_EVEN))
#define IS_LPUART_MODE(x)  (((x) == LPUART_MODE_UART) || \
                            ((x) == LPUART_MODE_IrDA) || \
                            ((x) == LPUART_MODE_RS485))
#define IS_LPUART_HARDWARE_FLOW_CONTROL(x)\
                              (((x) == LPUART_HW_FLOW_CTL_NONE) || \
                               ((x) == LPUART_HW_FLOW_CTL_RTS)  || \
                               ((x) == LPUART_HW_FLOW_CTL_CTS)  || \
                               ((x) == LPUART_HW_FLOW_CTL_RTS_CTS))
#define IS_LPUART_DMAREQ(x)  (((x) == LPUART_DMA_REQ_TX) || ((x) == LPUART_DMA_REQ_RX))
#define IS_LPUART_RXFIFO(x)  (((x) == LPUART_RXFIFO_1BYTE) || \
                              ((x) == LPUART_RXFIFO_4BYTE) || \
                              ((x) == LPUART_RXFIFO_8BYTE) || \
                              ((x) == LPUART_RXFIFO_14BYTE))
#define IS_LPUART_IT(x)	(((x) == LPUART_IT_RBR)    || \
                         ((x) == LPUART_IT_TBEMP)  || \
                         ((x) == LPUART_IT_CTSDET) || \
                         ((x) == LPUART_IT_RXTO)   || \
                         ((x) == LPUART_IT_RXOV)   || \
                         ((x) == LPUART_IT_TXOV)   || \
                         ((x) == LPUART_IT_CTSWK)  || \
                         ((x) == LPUART_IT_DATWK)  || \
                         ((x) == LPUART_IT_PERR)   || \
                         ((x) == LPUART_IT_FERR)   || \
                         ((x) == LPUART_IT_BRKERR) || \
                         ((x) == LPUART_IT_ADET)   || \
                         ((x) == LPUART_IT_TC))
#define IS_LPUART_IF(x)	(((x) == LPUART_IF_RBR)    || \
                         ((x) == LPUART_IF_TBEMP)  || \
                         ((x) == LPUART_IF_CTSDET) || \
                         ((x) == LPUART_IF_RXTO)   || \
                         ((x) == LPUART_IF_RXOV)   || \
                         ((x) == LPUART_IF_TXOV)   || \
                         ((x) == LPUART_IF_CTSWK)  || \
                         ((x) == LPUART_IF_DATWK)  || \
                         ((x) == LPUART_IF_PERR)   || \
                         ((x) == LPUART_IF_FERR)   || \
                         ((x) == LPUART_IF_BRKERR) || \
                         ((x) == LPUART_IF_ADET)   || \
                         ((x) == LPUART_IF_TC))
#define IS_LPUART_STAT(x)	(((x) == LPUART_STAT_RXEMP)   || \
                                 ((x) == LPUART_STAT_RXFULL)  || \
                                 ((x) == LPUART_STAT_TXEMP)   || \
                                 ((x) == LPUART_STAT_TXFULL)  || \
                                 ((x) == LPUART_STAT_TXIDLE)  || \
                                 ((x) == LPUART_STAT_CTSSTAT) || \
                                 ((x) == LPUART_STAT_RTSSTAT))

#define LPUART_STATE_TX_MASK	(1U << 4)
#define LPUART_STATE_RX_MASK	(1U << 5)
/**
  * @}
  */

/** @addtogroup LPUART_Public_Functions
  * @{
  */

/** @addtogroup LPUART_Public_Functions_Group1
  * @{
  */
/* Initialization functions */
void ald_lpuart_init(lpuart_handle_t *hperh);
void ald_lpuart_reset(lpuart_handle_t *hperh);
void ald_lpuart_rs485_config(lpuart_handle_t *hperh, lpuart_rs485_config_t *config);
/**
  * @}
  */

/** @addtogroup LPUART_Public_Functions_Group2
  * @{
  */
/* IO operation functions */
ald_status_t ald_lpuart_send(lpuart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_lpuart_recv(lpuart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_lpuart_send_by_it(lpuart_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_lpuart_recv_by_it(lpuart_handle_t *hperh, uint8_t *buf, uint16_t size);
#ifdef ALD_DMA
ald_status_t ald_lpuart_send_by_dma(lpuart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_lpuart_recv_by_dma(lpuart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_lpuart_dma_pause(lpuart_handle_t *hperh);
ald_status_t ald_lpuart_dma_resume(lpuart_handle_t *hperh);
ald_status_t ald_lpuart_dma_stop(lpuart_handle_t *hperh);
#endif
void ald_lpuart_irq_handler(lpuart_handle_t *hperh);

/**
  * @}
  */

/** @addtogroup LPUART_Public_Functions_Group3
  * @{
  */
/* Peripheral Control functions */
void ald_lpuart_interrupt_config(lpuart_handle_t *hperh, lpuart_it_t it, type_func_t status);
void ald_lpuart_tx_interval_config(lpuart_handle_t *hperh, uint8_t val);
void ald_lpuart_dma_req_config(lpuart_handle_t *hperh, lpuart_dma_req_t req, type_func_t status);
void ald_lpuart_rx_fifo_it_config(lpuart_handle_t *hperh, lpuart_rxfifo_t config);
void ald_lpuart_rx_fifo_rts_config(lpuart_handle_t *hperh, lpuart_rxfifo_t config);
ald_status_t ald_lpuart_rs485_send_addr(lpuart_handle_t *hperh, uint16_t addr, uint32_t timeout);
flag_status_t ald_lpuart_get_status(lpuart_handle_t *hperh, lpuart_status_t flag);
flag_status_t ald_lpuart_get_flag_status(lpuart_handle_t *hperh, lpuart_flag_t flag);
void ald_lpuart_clear_flag_status(lpuart_handle_t *hperh, lpuart_flag_t flag);
it_status_t ald_lpuart_get_it_status(lpuart_handle_t *hperh, lpuart_it_t it);
/**
  * @}
  */

/** @addtogroup LPUART_Public_Functions_Group4
  * @{
  */
/* Peripheral State and Errors functions */
lpuart_state_t ald_lpuart_get_state(lpuart_handle_t *hperh);
uint32_t ald_lpuart_get_error(lpuart_handle_t *hperh);
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

#endif /* __ALD_LPUART_H__ */
