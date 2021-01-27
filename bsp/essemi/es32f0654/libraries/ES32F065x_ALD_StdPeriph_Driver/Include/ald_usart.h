/**
  *********************************************************************************
  *
  * @file    ald_usart.h
  * @brief   Header file of USART module library.
  *
  * @version V1.0
  * @date    16 Apr 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __ALD_USART_H__
#define __ALD_USART_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "utils.h"
#include "ald_dma.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup USART
  * @{
  */

/** @defgroup USART_Public_Types USART Public Types
  * @{
  */

/**
  * @brief usart_word_length
  */
typedef enum {
	USART_WORD_LENGTH_8B = 0x0U,	/**< Word length is 8-bits */
	USART_WORD_LENGTH_9B = 0x1U,	/**< Word length is 9-bits */
} usart_word_length_t;

/**
  * @brief usart_stop_bits
  */
typedef enum {
	USART_STOP_BITS_1   = 0x0U,	/**< Stop bits is 1-bits */
	USART_STOP_BITS_0_5 = 0x1U,	/**< Stop bits is 0.5-bits */
	USART_STOP_BITS_2   = 0x2U,	/**< Stop bits is 2-bits */
	USART_STOP_BITS_1_5 = 0x3U,	/**< Stop bits is 1.5-bits */
} usart_stop_bits_t;

/**
  * @brief usart_parity
  */
typedef enum {
	USART_PARITY_NONE = 0x0U,	/**< Not parity */
	USART_PARITY_EVEN = 0x2U,	/**< Even parity */
	USART_PARITY_ODD  = 0x3U,	/**< Odd parity */
} usart_parity_t;

/**
  * @brief usart_mode
  */
typedef enum {
	USART_MODE_RX    = 0x1U,	/**< TX mode */
	USART_MODE_TX    = 0x2U,	/**< RX mode */
	USART_MODE_TX_RX = 0x3U,	/**< TX & RX mode */
} usart_mode_t;

/**
  * @brief usart_hardware_flow_control
  */
typedef enum {
	USART_HW_FLOW_CTL_NONE    = 0x0U,	/**< Not flow control */
	USART_HW_FLOW_CTL_RTS     = 0x1U,	/**< RTS flow control */
	USART_HW_FLOW_CTL_CTS     = 0x2U,	/**< CTS flow control */
	USART_HW_FLOW_CTL_RTS_CTS = 0x3U,	/**< RTS & CTS flow control */
} usart_hw_flow_ctl_t;

/**
  * @brief usart_clock
  */
typedef enum {
	USART_CLOCK_DISABLE = 0x0U,	/**< Disable clock output */
	USART_CLOCK_ENABLE  = 0x1U,	/**< Enable clock output */
} usart_clock_t;

/**
  * @brief usart_clock_polarity
  */
typedef enum {
	USART_CPOL_LOW  = 0x0U,		/**< Clock polarity low */
	USART_CPOL_HIGH = 0x1U,		/**< Clock polarity high */
} usart_cpol_t;

/**
  * @brief usart_clock_phase
  */
typedef enum {
	USART_CPHA_1EDGE = 0x0U,	/**< Clock phase first edge */
	USART_CPHA_2EDGE = 0x1U,	/**< Clock phase second edge */
} usart_cpha_t;

/**
  * @brief usart_last_bit
  */
typedef enum {
	USART_LAST_BIT_DISABLE = 0x0U,	/**< Disable last bit clock output */
	USART_LAST_BIT_ENABLE  = 0x1U,	/**< Enable last bit clock output */
} usart_last_bit_t;

/**
  * @brief usart state structures definition
  */
typedef enum {
	USART_STATE_RESET      = 0x00U,	/**< Peripheral is not initialized */
	USART_STATE_READY      = 0x01U,	/**< Peripheral Initialized and ready for use */
	USART_STATE_BUSY       = 0x02U,	/**< an internal process is ongoing */
	USART_STATE_BUSY_TX    = 0x11U,	/**< Data Transmission process is ongoing */
	USART_STATE_BUSY_RX    = 0x21U,	/**< Data Reception process is ongoing */
	USART_STATE_BUSY_TX_RX = 0x31U,	/**< Data Transmission Reception process is ongoing */
	USART_STATE_TIMEOUT    = 0x03U,	/**< Timeout state */
	USART_STATE_ERROR      = 0x04U,	/**< Error */
} usart_state_t;

/**
  * @brief usart error codes
  */
typedef enum {
	USART_ERROR_NONE = ((uint32_t)0x00U),	/**< No error */
	USART_ERROR_PE   = ((uint32_t)0x01U),	/**< Parity error */
	USART_ERROR_NE   = ((uint32_t)0x02U),	/**< Noise error */
	USART_ERROR_FE   = ((uint32_t)0x04U),	/**< frame error */
	USART_ERROR_ORE  = ((uint32_t)0x08U),	/**< Overrun error */
	USART_ERROR_DMA  = ((uint32_t)0x10U),	/**< DMA transfer error */
} usart_error_t;


/**
  * @brief usart init structure definition
  */
typedef struct {
	uint32_t baud;			/**< This member configures the Usart communication baud rate. */
	usart_word_length_t word_length;/**< Specifies the number of data bits transmitted or received in a frame. */
	usart_stop_bits_t stop_bits;	/**< Specifies the number of stop bits transmitted. */
	usart_parity_t parity;		/**< Specifies the parity mode.
					     @note When parity is enabled, the computed parity is inserted
 						   at the MSB position of the transmitted data (9th bit when
 						   the word length is set to 9 data bits; 8th bit when the
						   word length is set to 8 data bits). */
	usart_mode_t mode;		/**< Specifies wether the Receive or Transmit mode is enabled or disabled. */
	usart_hw_flow_ctl_t fctl;	/**< Specifies wether the hardware flow control mode is enabled or disabled. */
} usart_init_t;

/**
  * @brief  USART handle structure definition
  */
typedef struct usart_handle_s {
	USART_TypeDef *perh;	/**< USART registers base address */
	usart_init_t init;	/**< USART communication parameters */
	uint8_t *tx_buf;	/**< Pointer to USART Tx transfer buffer */
	uint16_t tx_size;	/**< USART Tx transfer size */
	uint16_t tx_count;	/**< USART Tx transfer counter */
	uint8_t *rx_buf;	/**< Pointer to USART Rx transfer buffer */
	uint16_t rx_size;	/**< USART Rx Transfer size */
	uint16_t rx_count;	/**< USART Rx Transfer Counter */
#ifdef ALD_DMA
	dma_handle_t hdmatx;	/**< USART Tx DMA handle parameters */
	dma_handle_t hdmarx;	/**< USART Rx DMA handle parameters */
#endif
	lock_state_t lock;	/**< Locking object */
	usart_state_t state;	/**< USART communication state */
	uint32_t err_code;	/**< USART error code */

	void (*tx_cplt_cbk)(struct usart_handle_s *arg);	/**< Tx completed callback */
	void (*rx_cplt_cbk)(struct usart_handle_s *arg);	/**< Rx completed callback */
	void (*tx_rx_cplt_cbk)(struct usart_handle_s *arg);	/**< Tx & Rx completed callback */
	void (*error_cbk)(struct usart_handle_s *arg);		/**< error callback */
} usart_handle_t;


/**
  * @brief USART clock init structure definition
  */
typedef struct {
	usart_clock_t clk;		/**< Pecifies whether the USART clock is enable or disable. */
	usart_cpol_t polarity;		/**< Specifies the steady state of the serial clock. */
	usart_cpha_t phase;		/**< Specifies the clock transition on which the bit capture is made. */
	usart_last_bit_t last_bit;	/**< Specifies whether the clock pulse corresponding to the last transmitted
				             data bit (MSB) has to be output on the SCLK pin in synchronous mode. */
} usart_clock_init_t;


/**
  * @brief usart_dma_request
  */
typedef enum {
	USART_DMA_REQ_TX = (1U << 7),	/**< TX dma bit */
	USART_DMA_REQ_RX = (1U << 6),	/**< RX dma bit */
} usart_dma_req_t;

/**
  * @brief usart_wakeup_methods
  */
typedef enum {
	USART_WAKEUP_IDLE = 0x0U,	/**< Wake up the machine when bus-line is idle */
	USART_WAKEUP_ADDR = 0x1U,	/**< Wake up the machine when match the address */
} usart_wakeup_t;

/**
  * @brief usart_IrDA_low_power
  */
typedef enum {
	USART_IrDA_MODE_NORMAL    = 0x0U,		/**< Normal IrDA mode */
	USART_IrDA_MODE_LOW_POWER = 0x1U,		/**< Low-power IrDA mode */
} usart_IrDA_mode_t;

/**
  * @brief USART interrupts definition
  */
typedef enum {
	USART_IT_PE   = ((1U << 8) | (1U << 16)),	/**< Parity error */
	USART_IT_TXE  = ((1U << 7) | (1U << 16)),	/**< Tx empty */
	USART_IT_TC   = ((1U << 6) | (1U << 16)),	/**< Tx complete */
	USART_IT_RXNE = ((1U << 5) | (1U << 16)),	/**< Rx not empty */
	USART_IT_IDLE = ((1U << 4) | (1U << 16)),	/**< Idle */
	USART_IT_CTS  = ((1U << 10)| (1U << 18)),	/**< CTS */
	USART_IT_ERR  = ((1U << 0) | (1U << 18)),	/**< Error */
	USART_IT_ORE  = (1U << 3),			/**< Overrun error */
	USART_IT_NE   = (1U << 2),			/**< Noise error */
	USART_IT_FE   = (1U << 0),			/**< Frame error */
} usart_it_t;

/**
  * @brief USART flags
  */
typedef enum {
	USART_FLAG_CTS  = (1U << 9),	/**< CTS */
	USART_FLAG_TXE  = (1U << 7),	/**< Tx empty */
	USART_FLAG_TC   = (1U << 6),	/**< Tx complete */
	USART_FLAG_RXNE = (1U << 5),	/**< Rx not empty */
	USART_FLAG_IDLE = (1U << 4),	/**< Idle */
	USART_FLAG_ORE  = (1U << 3),	/**< Overrun error */
	USART_FLAG_NE   = (1U << 2),	/**< Noise error */
	USART_FLAG_FE   = (1U << 1),	/**< Frame error */
	USART_FLAG_PE   = (1U << 0),	/**< Parity error */
} usart_flag_t;

/**
  * @}
  */


/** @defgroup USART_Public_Macros USART Public Macros
  * @{
  */

/** @defgroup USART_Public_Macros_1 USART handle reset
  * @{
  */
#define USART_RESET_HANDLE_STATE(handle) ((handle)->state = USART_STATE_RESET)
/**
  * @}
  */

/** @defgroup USART_Public_Macros_2 USART clear PE flag
  * @{
  */
#define USART_CLEAR_PEFLAG(handle)	\
do {					\
	__IO uint32_t tmpreg;		\
	tmpreg = (handle)->perh->STAT;	\
	tmpreg = (handle)->perh->DATA;	\
	UNUSED(tmpreg);			\
} while (0)
/**
  * @}
  */

/** @defgroup USART_Public_Macros_3 USART clear FE flag
  * @{
  */
#define USART_CLEAR_FEFLAG(handle) USART_CLEAR_PEFLAG(handle)
/**
  * @}
  */

/** @defgroup USART_Public_Macros_4 USART clear NE flag
  * @{
  */
#define USART_CLEAR_NEFLAG(handle) USART_CLEAR_PEFLAG(handle)
/**
  * @}
  */

/** @defgroup USART_Public_Macros_5 USART clear ORE flag
  * @{
  */
#define USART_CLEAR_OREFLAG(handle) USART_CLEAR_PEFLAG(handle)
/**
  * @}
  */

/** @defgroup USART_Public_Macros_6 USART clear IDLE flag
  * @{
  */
#define USART_CLEAR_IDLEFLAG(handle) USART_CLEAR_PEFLAG(handle)
/**
  * @}
  */

/** @defgroup USART_Public_Macros_7 USART enable CTS flow control
  * @{
  */
#define USART_HWCONTROL_CTS_ENABLE(handle)	\
	(SET_BIT((handle)->perh->CON2, USART_CON2_CTSEN_MSK))
/**
  * @}
  */

/** @defgroup USART_Public_Macros_8 USART disable CTS flow control
  * @{
  */
#define USART_HWCONTROL_CTS_DISABLE(handle)	\
	(CLEAR_BIT((handle)->perh->CON2, USART_CON2_CTSEN_MSK))
/**
  * @}
  */

/** @defgroup USART_Public_Macros_9 USART enable RTS flow control
  * @{
  */
#define USART_HWCONTROL_RTS_ENABLE(handle)	\
	(SET_BIT((handle)->perh->CON2, USART_CON2_RTSEN_MSK))
/**
  * @}
  */

/** @defgroup USART_Public_Macros_10 USART disable RTS flow control
  * @{
  */
#define USART_HWCONTROL_RTS_DISABLE(handle)	\
	(CLEAR_BIT((handle)->perh->CON2, USART_CON2_RTSEN_MSK))
/**
  * @}
  */

/** @defgroup USART_Public_Macros_11 USART enable
  * @{
  */
#define USART_ENABLE(handle)	(SET_BIT((handle)->perh->CON0, USART_CON0_EN_MSK))
/**
  * @}
  */

/** @defgroup USART_Public_Macros_12 USART disable
  * @{
  */
#define USART_DISABLE(handle)	(CLEAR_BIT((handle)->perh->CON0, USART_CON0_EN_MSK))
 /**
  * @}
  */

/**
  * @}
  */

/** @defgroup USART_Private_Macros   USART Private Macros
  * @{
  */

#define IS_USART(x) (((x) == USART0) || ((x) == USART1))
#define IS_USART_WORD_LENGTH(x) (((x) == USART_WORD_LENGTH_8B) || \
                                 ((x) == USART_WORD_LENGTH_9B))
#define IS_USART_STOPBITS(x) (((x) == USART_STOP_BITS_1) ||   \
                              ((x) == USART_STOP_BITS_0_5) || \
                              ((x) == USART_STOP_BITS_2) ||   \
                              ((x) == USART_STOP_BITS_1_5))
#define IS_USART_PARITY(x) (((x) == USART_PARITY_NONE) ||   \
                            ((x) == USART_PARITY_EVEN) || \
                            ((x) == USART_PARITY_ODD))
#define IS_USART_MODE(x) (((x) == USART_MODE_RX) || \
			  ((x) == USART_MODE_TX) || \
			  ((x) == USART_MODE_TX_RX))
#define IS_USART_HARDWARE_FLOW_CONTROL(x)\
                              (((x) == USART_HW_FLOW_CTL_NONE) || \
                               ((x) == USART_HW_FLOW_CTL_RTS)  || \
                               ((x) == USART_HW_FLOW_CTL_CTS)  || \
                               ((x) == USART_HW_FLOW_CTL_RTS_CTS))
#define IS_USART_CLOCK(x) (((x) == USART_CLOCK_DISABLE) || \
                           ((x) == USART_CLOCK_ENABLE))
#define IS_USART_CPOL(x) (((x) == USART_CPOL_LOW) || ((x) == USART_CPOL_HIGH))
#define IS_USART_CPHA(x) (((x) == USART_CPHA_1EDGE) || ((x) == USART_CPHA_2EDGE))
#define IS_USART_LASTBIT(x) (((x) == USART_LAST_BIT_DISABLE) || \
                             ((x) == USART_LAST_BIT_ENABLE))
#define IS_USART_DMAREQ(x) (((x) == USART_DMA_REQ_TX) || \
                            ((x) == USART_DMA_REQ_RX))
#define IS_USART_WAKEUP(x) (((x) == USART_WAKEUP_IDLE) || \
                            ((x) == USART_WAKEUP_ADDR))
#define IS_USART_IRDA_MODE(x) (((x) == USART_IrDA_MODE_NORMAL) || \
                               ((x) == USART_IrDA_MODE_LOW_POWER))
#define IS_USART_CONFIG_IT(x) (((x) == USART_IT_PE) || ((x) == USART_IT_TXE)   || \
                               ((x) == USART_IT_TC) || ((x) == USART_IT_RXNE)  || \
                               ((x) == USART_IT_IDLE) || \
                               ((x) == USART_IT_CTS) || ((x) == USART_IT_ERR))
#define IS_USART_GET_IT(x) (((x) == USART_IT_PE) || ((x) == USART_IT_TXE)   || \
                            ((x) == USART_IT_TC) || ((x) == USART_IT_RXNE)  || \
                            ((x) == USART_IT_IDLE) || \
                            ((x) == USART_IT_CTS) || ((x) == USART_IT_ORE)  || \
                            ((x) == USART_IT_NE) || ((x) == USART_IT_FE)    || \
                            ((x) == USART_IT_ERR))
#define IS_USART_CLEAR_IT(x) (((x) == USART_IT_TC) || ((x) == USART_IT_RXNE) || \
                               ((x) == USART_IT_CTS))

#define IS_USART_FLAG(x) (((x) == USART_FLAG_PE) || ((x) == USART_FLAG_TXE)   || \
                          ((x) == USART_FLAG_TC) || ((x) == USART_FLAG_RXNE)  || \
                          ((x) == USART_FLAG_IDLE) || \
                          ((x) == USART_FLAG_CTS) || ((x) == USART_FLAG_ORE)  || \
                          ((x) == USART_FLAG_NE) || ((x) == USART_FLAG_FE))
#define IS_USART_CLEAR_FLAG(x) (((x) == USART_FLAG_CTS) || \
                                ((x) == USART_FLAG_TC)  || \
                                ((x) == USART_FLAG_RXNE))
#define IS_USART_BAUDRATE(x)	(((x) > 0) && ((x) < 0x0044AA21))
#define IS_USART_ADDRESS(x)	((x) <= 0xF)
#define IS_USART_DATA(x)	((x) <= 0x1FF)
#define DUMMY_DATA		0xFFFF
#define USART_STATE_TX_MASK	(1U << 4)
#define USART_STATE_RX_MASK	(1U << 5)

/**
  * @}
  */

/** @addtogroup USART_Public_Functions
  * @{
  */

/** @addtogroup USART_Public_Functions_Group1
  * @{
  */
/* Initialization functions */
void ald_usart_reset(usart_handle_t *hperh);
ald_status_t ald_usart_init(usart_handle_t *hperh);
ald_status_t ald_usart_half_duplex_init(usart_handle_t *hperh);
ald_status_t ald_usart_multi_processor_init(usart_handle_t *hperh, uint8_t addr, usart_wakeup_t wakeup);
ald_status_t ald_usart_clock_init(usart_handle_t *hperh, usart_clock_init_t *init);
/**
  * @}
  */

/** @addtogroup USART_Public_Functions_Group2
  * @{
  */

/** @addtogroup USART_Public_Functions_Group2_1
  * @{
  */
/* Asynchronization IO operation functions */
ald_status_t ald_usart_send(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_usart_recv(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_usart_send_by_it(usart_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_usart_recv_by_it(usart_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_usart_recv_frame_by_it(usart_handle_t *hperh, uint8_t *buf, uint16_t size);
#ifdef ALD_DMA
ald_status_t ald_usart_send_by_dma(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_usart_recv_by_dma(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
#endif
/**
  * @}
  */

/** @addtogroup USART_Public_Functions_Group2_2
  * @{
  */
/* Synchronization IO operation functions */
ald_status_t ald_usart_send_sync(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_usart_recv_sync(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_usart_send_recv_sync(usart_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size, uint32_t timeout);
ald_status_t ald_usart_send_by_it_sync(usart_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_usart_recv_by_it_sync(usart_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_usart_send_recv_by_it_sync(usart_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf,  uint16_t size);
#ifdef ALD_DMA
ald_status_t ald_usart_send_by_dma_sync(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_usart_recv_by_dma_sync(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t tx_channel, uint8_t rx_channel);
ald_status_t ald_usart_send_recv_by_dma_sync(usart_handle_t *hperh, uint8_t *tx_buf,
                    uint8_t *rx_buf, uint16_t size, uint8_t tx_channel, uint8_t rx_channel);
#endif
/**
  * @}
  */

/** @addtogroup USART_Public_Functions_Group2_3
  * @{
  */
/* Utilities functions */
#ifdef ALD_DMA
ald_status_t ald_usart_dma_pause(usart_handle_t *hperh);
ald_status_t ald_usart_dma_resume(usart_handle_t *hperh);
ald_status_t ald_usart_dma_stop(usart_handle_t *hperh);
#endif
void ald_usart_irq_handler(usart_handle_t *hperh);
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup USART_Public_Functions_Group3
  * @{
  */
/* Peripheral control functions */
ald_status_t ald_usart_multi_processor_enter_mute_mode(usart_handle_t *hperh);
ald_status_t ald_usart_multi_processor_exit_mute_mode(usart_handle_t *hperh);
ald_status_t ald_usart_half_duplex_enable_send(usart_handle_t *hperh);
ald_status_t ald_usart_half_duplex_enable_recv(usart_handle_t *hperh);
void ald_usart_dma_req_config(usart_handle_t *hperh, usart_dma_req_t req, type_func_t state);
void ald_usart_interrupt_config(usart_handle_t *hperh, usart_it_t it, type_func_t state);
flag_status_t ald_usart_get_flag_status(usart_handle_t *hperh, usart_flag_t flag);
void ald_usart_clear_flag_status(usart_handle_t *hperh, usart_flag_t flag);
it_status_t ald_usart_get_it_status(usart_handle_t *hperh, usart_it_t it);
/**
  * @}
  */

/** @addtogroup USART_Public_Functions_Group4
  * @{
  */

/* Peripheral state and error functions */
usart_state_t ald_usart_get_state(usart_handle_t *hperh);
uint32_t ald_usart_get_error(usart_handle_t *hperh);
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

#endif /* __ALD_USART_H__ */
