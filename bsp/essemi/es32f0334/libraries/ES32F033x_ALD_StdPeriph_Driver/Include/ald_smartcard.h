/**
  *********************************************************************************
  *
  * @file    ald_usart.h
  * @brief   Header file of SMARTCARD driver module.
  *
  * @version V1.0
  * @date    25 Apr 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __ALD_SMARTCARD_H__
#define __ALD_SMARTCARD_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "utils.h"
#include "ald_dma.h"
#include "ald_usart.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup SMARTCARD
  * @{
  */

/** @defgroup SMARTCARD_Public_Constants  SMARTCARD Public constants
  * @{
  */

/**
  * @brief SMARTCARD error codes
  */
typedef enum {
	SMARTCARD_ERROR_NONE = ((uint32_t)0x00U),	/**< No error */
	SMARTCARD_ERROR_PE   = ((uint32_t)0x01U),	/**< Parity error */
	SMARTCARD_ERROR_NE   = ((uint32_t)0x02U),	/**< Noise error */
	SMARTCARD_ERROR_FE   = ((uint32_t)0x04U),	/**< frame error */
	SMARTCARD_ERROR_ORE  = ((uint32_t)0x08U),	/**< Overrun error */
	SMARTCARD_ERROR_DMA  = ((uint32_t)0x10U),	/**< DMA transfer error */
} smartcard_error_t;

/**
  * @brief SMARTCARD Prescaler
  */
typedef enum {
	SMARTCARD_PRESCALER_SYSCLK_DIV2  = ((uint32_t)0x1U),	/**< SYSCLK divided by 2 */
	SMARTCARD_PRESCALER_SYSCLK_DIV4  = ((uint32_t)0x2U),	/**< SYSCLK divided by 4 */
	SMARTCARD_PRESCALER_SYSCLK_DIV6  = ((uint32_t)0x3U),	/**< SYSCLK divided by 6 */
	SMARTCARD_PRESCALER_SYSCLK_DIV8  = ((uint32_t)0x4U),	/**< SYSCLK divided by 8 */
	SMARTCARD_PRESCALER_SYSCLK_DIV10 = ((uint32_t)0x5U),	/**< SYSCLK divided by 10 */
	SMARTCARD_PRESCALER_SYSCLK_DIV12 = ((uint32_t)0x6U),	/**< SYSCLK divided by 12 */
	SMARTCARD_PRESCALER_SYSCLK_DIV14 = ((uint32_t)0x7U),	/**< SYSCLK divided by 14 */
	SMARTCARD_PRESCALER_SYSCLK_DIV16 = ((uint32_t)0x8U),	/**< SYSCLK divided by 16 */
	SMARTCARD_PRESCALER_SYSCLK_DIV18 = ((uint32_t)0x9U),	/**< SYSCLK divided by 18 */
	SMARTCARD_PRESCALER_SYSCLK_DIV20 = ((uint32_t)0xAU),	/**< SYSCLK divided by 20 */
	SMARTCARD_PRESCALER_SYSCLK_DIV22 = ((uint32_t)0xBU),	/**< SYSCLK divided by 22 */
	SMARTCARD_PRESCALER_SYSCLK_DIV24 = ((uint32_t)0xCU),	/**< SYSCLK divided by 24 */
	SMARTCARD_PRESCALER_SYSCLK_DIV26 = ((uint32_t)0xDU),	/**< SYSCLK divided by 26 */
	SMARTCARD_PRESCALER_SYSCLK_DIV28 = ((uint32_t)0xEU),	/**< SYSCLK divided by 28 */
	SMARTCARD_PRESCALER_SYSCLK_DIV30 = ((uint32_t)0xFU),	/**< SYSCLK divided by 30 */
	SMARTCARD_PRESCALER_SYSCLK_DIV32 = ((uint32_t)0x10U),	/**< SYSCLK divided by 32 */
	SMARTCARD_PRESCALER_SYSCLK_DIV34 = ((uint32_t)0x11U),	/**< SYSCLK divided by 34 */
	SMARTCARD_PRESCALER_SYSCLK_DIV36 = ((uint32_t)0x12U),	/**< SYSCLK divided by 36 */
	SMARTCARD_PRESCALER_SYSCLK_DIV38 = ((uint32_t)0x13U),	/**< SYSCLK divided by 38 */
	SMARTCARD_PRESCALER_SYSCLK_DIV40 = ((uint32_t)0x14U),	/**< SYSCLK divided by 40 */
	SMARTCARD_PRESCALER_SYSCLK_DIV42 = ((uint32_t)0x15U),	/**< SYSCLK divided by 42 */
	SMARTCARD_PRESCALER_SYSCLK_DIV44 = ((uint32_t)0x16U),	/**< SYSCLK divided by 44 */
	SMARTCARD_PRESCALER_SYSCLK_DIV46 = ((uint32_t)0x17U),	/**< SYSCLK divided by 46 */
	SMARTCARD_PRESCALER_SYSCLK_DIV48 = ((uint32_t)0x18U),	/**< SYSCLK divided by 48 */
	SMARTCARD_PRESCALER_SYSCLK_DIV50 = ((uint32_t)0x19U),	/**< SYSCLK divided by 50 */
	SMARTCARD_PRESCALER_SYSCLK_DIV52 = ((uint32_t)0x1AU),	/**< SYSCLK divided by 52 */
	SMARTCARD_PRESCALER_SYSCLK_DIV54 = ((uint32_t)0x1BU),	/**< SYSCLK divided by 54 */
	SMARTCARD_PRESCALER_SYSCLK_DIV56 = ((uint32_t)0x1CU),	/**< SYSCLK divided by 56 */
	SMARTCARD_PRESCALER_SYSCLK_DIV58 = ((uint32_t)0x1DU),	/**< SYSCLK divided by 58 */
	SMARTCARD_PRESCALER_SYSCLK_DIV60 = ((uint32_t)0x1EU),	/**< SYSCLK divided by 60 */
	SMARTCARD_PRESCALER_SYSCLK_DIV62 = ((uint32_t)0x1FU),	/**< SYSCLK divided by 62 */
} smartcard_prescaler_t;

/**
  * @}
  */

/** @defgroup SMARTCARD_Public_Types SMARTCARD Public Types
  * @{
  */

/**
  * @brief SMARTCARD Init Structure definition
  */
typedef struct {
	uint32_t baud;			/**< This member configures the SmartCard communication baud rate. */
	usart_word_length_t word_length;/**< Specifies the number of data bits transmitted or received in a frame. */
	usart_stop_bits_t stop_bits;	/**< Specifies the number of stop bits transmitted. */
	usart_parity_t parity;		/**< Specifies the parity mode.
						@note When parity is enabled, the computed parity is inserted
                                                      at the MSB position of the transmitted data (9th bit when
                                                      the word length is set to 9 data bits; 8th bit when the
                                                      word length is set to 8 data bits).*/
	usart_mode_t mode;		/**< Specifies whether the Receive or Transmit mode is enabled or disabled. */
	usart_cpol_t polarity;		/**< Specifies the steady state of the serial clock. */
	usart_cpha_t phase;		/**< Specifies the clock transition on which the bit capture is made.*/
	usart_last_bit_t last_bit;	/**< Specifies whether the clock pulse corresponding to the last transmitted
					     data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                                             This parameter can be a value of @ref usart_last_bit_t */
	smartcard_prescaler_t prescaler;/**< Specifies the SmartCard Prescaler value used for dividing the system clock
					     to provide the smartcard clock. The value given in the register (5 significant bits)
					     is multiplied by 2 to give the division factor of the source clock frequency. */
	uint32_t guard_time;		/**< Specifies the SmartCard Guard Time value in terms of number of baud clocks */
	type_func_t nack;		/**< Specifies the SmartCard NACK Transmission state. */
} smartcard_init_t;

/**
  * @brief ALD state structures definition
  */
typedef enum {
	SMARTCARD_STATE_RESET      = 0x00U,	/**< Peripheral is not yet Initialized */
	SMARTCARD_STATE_READY      = 0x01U,	/**< Peripheral Initialized and ready for use */
	SMARTCARD_STATE_BUSY       = 0x02U,	/**< an internal process is ongoing */
	SMARTCARD_STATE_BUSY_TX    = 0x11U,	/**< Data Transmission process is ongoing */
	SMARTCARD_STATE_BUSY_RX    = 0x21U,	/**< Data Reception process is ongoing */
	SMARTCARD_STATE_BUSY_TX_RX = 0x31U,	/**< Data Transmission and Reception process is ongoing */
	SMARTCARD_STATE_TIMEOUT    = 0x03U,	/**< Timeout state */
	SMARTCARD_STATE_ERROR      = 0x04U,	/**< Error */
} smartcard_state_t;


/**
  * @brief  SMARTCARD handle structure definition
  */
typedef struct smartcard_handle_s {
	USART_TypeDef *perh;		/**< USART registers base address */
	smartcard_init_t init;		/**< SmartCard communication parameters */
	uint8_t *tx_buf;		/**< Pointer to SmartCard Tx transfer Buffer */
	uint16_t tx_size;		/**< SmartCard Tx Transfer size */
	uint16_t tx_count;		/**< SmartCard Tx Transfer Counter */
	uint8_t *rx_buf;		/**< Pointer to SmartCard Rx transfer Buffer */
	uint16_t rx_size;		/**< SmartCard Rx Transfer size */
	uint16_t rx_count;		/**< SmartCard Rx Transfer Counter */
#ifdef ALD_DMA
	dma_handle_t hdmatx;		/**< SmartCard Tx DMA Handle parameters */
	dma_handle_t hdmarx;		/**< SmartCard Rx DMA Handle parameters */
#endif
	lock_state_t lock;		/**< Locking object */
	smartcard_state_t state;	/**< SmartCard communication state */
	uint32_t  err_code;		/**< SmartCard Error code */

	void (*tx_cplt_cbk)(struct smartcard_handle_s *arg);	/**< Tx completed callback */
	void (*rx_cplt_cbk)(struct smartcard_handle_s *arg);	/**< Rx completed callback */
	void (*error_cbk)(struct smartcard_handle_s *arg);	/**< error callback */
} smartcard_handle_t;

/**
  * @}
  */

/** @defgroup SMARTCARD_Public_Macros SMARTCARD Public Macros
  * @{
  */

/** @defgroup SMARTCARD_Public_Macros_1 SMARTCARD handle reset
  * @{
  */
#define SMARTCARD_RESET_HANDLE_STATE(handle) ((handle)->state = SMARTCARD_STATE_RESET)
/**
  * @}
  */

/** @defgroup SMARTCARD_Public_Macros_2 SMARTCARD flush data
  * @{
  */
#define SMARTCARD_FLUSH_DRREGISTER(handle) ((handle)->perh->DATA)
/**
  * @}
  */

/** @defgroup SMARTCARD_Public_Macros_3 SMARTCARD enable
  * @{
  */
#define SMARTCARD_ENABLE(handle)	(SET_BIT((handle)->perh->CON0, USART_CON0_EN_MSK))
/**
  * @}
  */

/** @defgroup SMARTCARD_Public_Macros_4 SMARTCARD disable
  * @{
  */
#define SMARTCARD_DISABLE(handle)	(CLEAR_BIT((handle)->perh->CON0, USART_CON0_EN_MSK))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SMARTCARD_Private_Macros SMARTCARD Private Macros
  * @{
  */

#define IS_SMARTCARD_PRESCALER(x)   (((x) >= SMARTCARD_PRESCALER_SYSCLK_DIV2) && \
				     ((x) <= SMARTCARD_PRESCALER_SYSCLK_DIV62))
/**
  * @}
  */

/** @addtogroup SMARTCARD_Public_Functions
  * @{
  */

/** @addtogroup SMARTCARD_Public_Functions_Group1
  * @{
  */
/* Initialization functions */
ald_status_t ald_smartcard_init(smartcard_handle_t *hperh);
ald_status_t ald_smartcard_reset(smartcard_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup SMARTCARD_Public_Functions_Group2
  * @{
  */
/* IO operation functions */
ald_status_t ald_smartcard_send(smartcard_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_smartcard_recv(smartcard_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout);
ald_status_t ald_smartcard_send_by_it(smartcard_handle_t *hperh, uint8_t *buf, uint16_t size);
ald_status_t ald_smartcard_recv_by_it(smartcard_handle_t *hperh, uint8_t *buf, uint16_t size);
#ifdef ALD_DMA
ald_status_t ald_smartcard_send_by_dma(smartcard_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_smartcard_recv_by_dma(smartcard_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel);
#endif
void ald_smartcard_irq_handler(smartcard_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup SMARTCARD_Public_Functions_Group3
  * @{
  */
/* Peripheral State and Errors functions functions */
smartcard_state_t ald_smartcard_get_state(smartcard_handle_t *hperh);
uint32_t ald_smartcard_get_error(smartcard_handle_t *hperh);
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

#endif /* __ALD_SMARTCARD_H__ */
