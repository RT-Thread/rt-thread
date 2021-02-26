/**
  *********************************************************************************
  *
  * @file    ald_smartcard.c
  * @brief   SMARTCARD module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the SMARTCARD peripheral:
  *           + Initialization functions
  *           + IO operation functions
  *           + Peripheral State and Errors functions
  *
  * @version V1.0
  * @date    25 Apr 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  * @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
    The SMARTCARD driver can be used as follows:

    (#) Declare a smartcard_handle_t handle structure.
        (##) Enable the interface clock of the USARTx associated to the SMARTCARD.
        (##) SMARTCARD pins configuration:
             (+++) Enable the clock for the SMARTCARD GPIOs.
             (+++) Configure the USART pins (TX as alternate function pull-up, RX as alternate function Input).
        (##) NVIC configuration if you need to use interrupt process (ald_smartcard_send_by_it()
             and ald_smartcard_recv_by_it() APIs):
            (+++) Configure the USARTx interrupt priority.
            (+++) Enable the NVIC USART IRQ handle.
        (##) DMA Configuration if you need to use DMA process (ald_smartcard_send_by_dma()
             and ald_smartcard_recv_by_dma() APIs):
            (+++) Declare a DMA handle structure for the Tx/Rx channel.
            (+++) Enable the DMAx interface clock.
            (+++) Configure the declared DMA handle structure with the required Tx/Rx parameters.
            (+++) Configure the DMA Tx/Rx channel.
            (+++) Associate the initilalized DMA handle to the SMARTCARD DMA Tx/Rx handle.
            (+++) Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA Tx/Rx channel.
            (+++) Configure the USARTx interrupt priority and enable the NVIC USART IRQ handle
                  (used for last byte sending completion detection in DMA non circular mode)

    (#) Program the Baud Rate, Word Length , Stop Bit, Parity, Hardware
        flow control and Mode(Receiver/Transmitter) in the SMARTCARD Init structure.

    (#) Initialize the SMARTCARD registers by calling the ald_smartcard_init() API.

    (#) Three operation modes are available within this driver :

     *** Polling mode IO operation ***
     =================================
     [..]
       (+) Send an amount of data in blocking mode using ald_smartcard_send()
       (+) Receive an amount of data in blocking mode using ald_smartcard_recv()

     *** Interrupt mode IO operation ***
     ===================================
     [..]
       (+) Send an amount of data in non blocking mode using ald_smartcard_send_by_it()
       (+) At transmission end of transfer hperh->tx_cplt_cbk() is executed and user can
            add his own code by customization of function pointer hperh->tx_cplt_cbk()
       (+) Receive an amount of data in non blocking mode using ald_smartcard_recv_by_it()
       (+) At reception end of transfer hperh->rx_cplt_cbk() is executed and user can
            add his own code by customization of function pointer hperh->rx_cplt_cbk()
       (+) In case of transfer Error, hperh->error_cbk() function is executed and user can
            add his own code by customization of function pointer hperh->error_cbk()

     *** DMA mode IO operation ***
     ==============================
     [..]
       (+) Send an amount of data in non blocking mode (DMA) using ald_smartcard_send_by_dma()
       (+) At transmission end of transfer hperh->tx_cplt_cbk() is executed and user can
            add his own code by customization of function pointer hperh->tx_cplt_cbk()
       (+) Receive an amount of data in non blocking mode (DMA) using ald_smartcard_recv_by_dma()
       (+) At reception end of transfer hperh->rx_cplt_cbk() is executed and user can
            add his own code by customization of function pointer hperh->rx_cplt_cbk()
       (+) In case of transfer Error, hperh->error_cbk()() function is executed and user can
            add his own code by customization of function pointer hperh->error_cbk()

     *** SMARTCARD ALD driver macros list ***
     ========================================
     [..]
       Below the list of most used macros in SMARTCARD ALD driver.

       (+) SMARTCARD_ENABLE: Enable the SmartCard peripheral.
       (+) SMARTCARD_DISABLE: Disable the SmartCard peripheral.
       (+) smartcard_reset_HANDLE_STATE : Reset SmartCard handle.
       (+) SMARTCARD_FLUSH_DRREGISTER : Flush SmartCard data.

     [..]
       (@) You can refer to the SMARTCARD library header file for more useful macros

    @endverbatim
  ******************************************************************************
  */


#include "ald_smartcard.h"
#include "ald_cmu.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup SMARTCARD SMARTCARD
  * @brief SMARTCARD module driver
  * @{
  */

#ifdef ALD_SMARTCARD

/** @addtogroup SMARTCARD_Private_Functions   SMARTCARD Private Functions
  * @{
  */
static ald_status_t __smartcard_send_by_it(smartcard_handle_t *hperh);
static ald_status_t __smartcard_end_send_by_it(smartcard_handle_t *hsmartcard);
static ald_status_t __smartcard_recv_by_it(smartcard_handle_t *hperh);
static void smartcard_set_config(smartcard_handle_t *hperh);
#ifdef ALD_DMA
static void smartcard_dma_send_cplt(void *arg);
static void smartcard_dma_recv_cplt(void *arg);
static void smartcard_dma_error(void *arg);
#endif
static ald_status_t smartcard_wait_flag(smartcard_handle_t *hperh, usart_flag_t flag, flag_status_t status, uint32_t timeout);
/**
  * @}
  */

/** @defgroup SMARTCARD_Public_Functions SMARTCARD Public Functions
  * @{
  */

/** @defgroup SMARTCARD_Public_Functions_Group1 Initialization functions
  * @brief   Initialization and Configuration functions
  *
  * @verbatim

  ==============================================================================
              ##### Initialization and Configuration functions #####
  ==============================================================================
  [..]
  This subsection provides a set of functions allowing to initialize the USART
  in Smartcard mode.
  [..]
  The Smartcard interface is designed to support asynchronous protocol Smartcards as
  defined in the ISO 7816-3 standard.
  [..]
  The USART can provide a clock to the smartcard through the SCLK output.
  In smartcard mode, SCLK is not associated to the communication but is simply derived
  from the internal peripheral input clock through a 5-bit prescaler.
  [..]
  (+) For the Smartcard mode only these parameters can be configured:
      (++) Baud Rate
      (++) Word Length => Should be 9 bits (8 bits + parity)
      (++) Stop Bit
      (++) Parity: => Should be enabled
      (++) USART polarity
      (++) USART phase
      (++) USART LastBit
      (++) Receiver/transmitter modes
      (++) Prescaler
      (++) GuardTime
      (++) NACKState: The Smartcard NACK state

     (+) Recommended SmartCard interface configuration to get the Answer to Reset from the Card:
        (++) word Length = 9 Bits
        (++) 1.5 Stop Bit
        (++) Even parity
        (++) BaudRate = 12096 baud
        (++) Tx and Rx enabled
  [..]
  Please refer to the ISO 7816-3 specification for more details.

    (@) It is also possible to choose 0.5 stop bit for receiving but it is recommended
        to use 1.5 stop bits for both transmitting and receiving to avoid switching
        between the two configurations.
  [..]
  The ald_smartcard_init() function follows the USART SmartCard configuration procedure.

    @endverbatim
  * @{
  */

/*
  Additionnal remark on the smartcard frame:
   +-------------------------------------------------------------+
   |   M bit |  PCE bit  |        SMARTCARD frame                |
   |---------------------|---------------------------------------|
   |    1    |    1      |    | SB | 8 bit data | PB | STB |     |
   +-------------------------------------------------------------+
*/

/**
  * @brief  Initializes the SmartCard mode according to the specified
  *         parameters in the smartcard_handle_t and create the associated handle.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_smartcard_init(smartcard_handle_t *hperh)
{
	assert_param(IS_USART_WORD_LENGTH(hperh->init.word_length));
	assert_param(IS_USART_STOPBITS(hperh->init.stop_bits));
	assert_param(IS_USART_PARITY(hperh->init.parity));
	assert_param(IS_USART(hperh->perh));
	assert_param(IS_FUNC_STATE(hperh->init.nack));
	assert_param(IS_SMARTCARD_PRESCALER(hperh->init.prescaler));

	if (hperh->state == SMARTCARD_STATE_RESET)
		hperh->lock = UNLOCK;

	hperh->state = SMARTCARD_STATE_BUSY;
	SMARTCARD_DISABLE(hperh);

	MODIFY_REG(hperh->perh->GP, USART_GP_PSC_MSK, hperh->init.prescaler << USART_GP_PSC_POSS);
	MODIFY_REG(hperh->perh->GP, USART_GP_GTVAL_MSK, hperh->init.guard_time << USART_GP_GTVAL_POSS);
	smartcard_set_config(hperh);

	CLEAR_BIT(hperh->perh->CON2, USART_CON2_IREN_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_HDPSEL_MSK);

	SMARTCARD_ENABLE(hperh);
	MODIFY_REG(hperh->perh->CON2, USART_CON2_NACK_MSK, hperh->init.nack << USART_CON2_NACK_POS);
	SET_BIT(hperh->perh->CON2, USART_CON2_SMARTEN_MSK);

	hperh->err_code = SMARTCARD_ERROR_NONE;
	hperh->state    = SMARTCARD_STATE_READY;
	return OK;
}

/**
  * @brief  Reset SMARTCARD register.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_smartcard_reset(smartcard_handle_t *hperh)
{
	assert_param(IS_USART(hperh->perh));

	hperh->state = SMARTCARD_STATE_BUSY;
	SMARTCARD_DISABLE(hperh);

	WRITE_REG(hperh->perh->CON0, 0x0);
	WRITE_REG(hperh->perh->CON1, 0x0);
	WRITE_REG(hperh->perh->CON2, 0x0);
	WRITE_REG(hperh->perh->BAUDCON, 0x0);
	WRITE_REG(hperh->perh->GP, 0x0);

	hperh->err_code = SMARTCARD_ERROR_NONE;
	hperh->state    = SMARTCARD_STATE_RESET;
	__UNLOCK(hperh);

	return OK;
}
/**
  * @}
  */

/** @defgroup SMARTCARD_Public_Functions_Group2 IO operation functions
  * @brief   SMARTCARD Transmit and Receive functions
  *
  * @verbatim
  ==============================================================================
                         ##### IO operation functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the SMARTCARD data transfers.

  [..]
    (#) Smartcard is a single wire half duplex communication protocol.
    The Smartcard interface is designed to support asynchronous protocol Smartcards as
    defined in the ISO 7816-3 standard.
    (#) The USART should be configured as:
        (++) 8 bits plus parity: where M=1 and PCE=1 in the USART_CR1 register
        (++) 1.5 stop bits when transmitting and receiving: where STOP=11 in the USART_CR2 register.

    (#) There are two modes of transfer:
        (++) Blocking mode: The communication is performed in polling mode.
             The library status of all data processing is returned by the same function
             after finishing transfer.
        (++) No-Blocking mode: The communication is performed using Interrupts
             or DMA, the relevant API's return the library status.
             The end of the data processing will be indicated through the
             dedicated SMARTCARD IRQ when using Interrupt mode or the DMA IRQ when
             using DMA mode.
             The hperh->tx_cplt_cbk(), hperh->rx_cplt_cbk() user callbacks
             will be executed respectively at the end of the Transmit or Receive process
             The hperh->error_cbk() user callback will be executed when a communication
             error is detected.

    (#) Blocking mode APIs are :
        (++) ald_smartcard_send()
        (++) ald_smartcard_recv()

    (#) Non Blocking mode APIs with Interrupt are :
        (++) ald_smartcard_send_by_it()
        (++) ald_smartcard_recv_by_it()
        (++) ald_smartcard_irq_handler()

    (#) Non Blocking mode functions with DMA are :
        (++) ald_smartcard_send_by_dma()
        (++) ald_smartcard_recv_by_dma()

  * @endverbatim
  * @{
  */

/**
  * @brief  Sends an amount of data in blocking mode.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Specify timeout value
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_smartcard_send(smartcard_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
	if ((hperh->state != SMARTCARD_STATE_READY) && (hperh->state != SMARTCARD_STATE_BUSY_RX))
		return BUSY;
	if ((buf == NULL) || (size == 0))
		return  ERROR;

	__LOCK(hperh);
	hperh->err_code = SMARTCARD_ERROR_NONE;
	SET_BIT(hperh->state, USART_STATE_TX_MASK);

	hperh->tx_size  = size;
	hperh->tx_count = size;

	while (hperh->tx_count-- > 0) {
		if (smartcard_wait_flag(hperh, USART_FLAG_TXE, SET, timeout) != OK) {
			hperh->state = SMARTCARD_STATE_READY;
			__UNLOCK(hperh);
			return TIMEOUT;
		}

		WRITE_REG(hperh->perh->DATA, *buf++);
	}

	if (smartcard_wait_flag(hperh, USART_FLAG_TC, SET, timeout) != OK) {
		hperh->state = SMARTCARD_STATE_READY;
		__UNLOCK(hperh);
		return TIMEOUT;
	}

	CLEAR_BIT(hperh->state, USART_STATE_TX_MASK);
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Receive an amount of data in blocking mode.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  timeout: Specify timeout value
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_smartcard_recv(smartcard_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
	if ((hperh->state != SMARTCARD_STATE_READY) && (hperh->state != SMARTCARD_STATE_BUSY_TX))
		return BUSY;
	if ((buf == NULL) || (size == 0))
		return  ERROR;

	__LOCK(hperh);
	hperh->err_code = SMARTCARD_ERROR_NONE;
	SET_BIT(hperh->state, USART_STATE_RX_MASK);

	hperh->rx_size  = size;
	hperh->rx_count = size;

	while (hperh->rx_count-- > 0) {
		if (smartcard_wait_flag(hperh, USART_FLAG_RXNE, SET, timeout) != OK) {
			hperh->state = SMARTCARD_STATE_READY;
			__UNLOCK(hperh);
			return TIMEOUT;
		}

		*buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);
	}

	__UNLOCK(hperh);
	CLEAR_BIT(hperh->state, USART_STATE_RX_MASK);

	return OK;
}

/**
  * @brief  Sends an amount of data in non-blocking mode.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_smartcard_send_by_it(smartcard_handle_t *hperh, uint8_t *buf, uint16_t size)
{
	if ((hperh->state != SMARTCARD_STATE_READY) && (hperh->state != SMARTCARD_STATE_BUSY_RX))
		return BUSY;
	if ((buf == NULL) || (size == 0))
		return ERROR;

	__LOCK(hperh);
	SET_BIT(hperh->state, USART_STATE_TX_MASK);

	hperh->tx_buf   = buf;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->err_code = SMARTCARD_ERROR_NONE;

	__UNLOCK(hperh);
	ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_ERR, ENABLE);
	ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_TXE, ENABLE);

	return OK;
}

/**
  * @brief  Receives an amount of data in non-blocking mode.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_smartcard_recv_by_it(smartcard_handle_t *hperh, uint8_t *buf, uint16_t size)
{
	if ((hperh->state != SMARTCARD_STATE_READY) && (hperh->state != SMARTCARD_STATE_BUSY_TX))
		return BUSY;
	if ((buf == NULL) || (size == 0))
		return ERROR;

	__LOCK(hperh);
	SET_BIT(hperh->state, USART_STATE_RX_MASK);

	hperh->rx_buf   = buf;
	hperh->rx_size  = size;
	hperh->rx_count = size;
	hperh->err_code = SMARTCARD_ERROR_NONE;

	__UNLOCK(hperh);
	ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_RXNE, ENABLE);
	ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_PE, ENABLE);
	ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_ERR, ENABLE);

	return OK;
}

#ifdef ALD_DMA
/**
  * @brief  Sends an amount of data in non-blocking mode.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as USART transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_smartcard_send_by_dma(smartcard_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
	if ((hperh->state != SMARTCARD_STATE_READY) && (hperh->state != SMARTCARD_STATE_BUSY_RX))
		return BUSY;
	if ((buf == NULL) || (size == 0))
		return ERROR;

	__LOCK(hperh);
	SET_BIT(hperh->state, USART_STATE_TX_MASK);

	hperh->tx_buf   = buf;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->err_code = SMARTCARD_ERROR_NONE;

	if (hperh->hdmatx.perh == NULL)
		hperh->hdmatx.perh = DMA0;

	hperh->hdmatx.cplt_cbk = smartcard_dma_send_cplt;
	hperh->hdmatx.cplt_arg = (void *)hperh;
	hperh->hdmatx.err_cbk  = smartcard_dma_error;
	hperh->hdmatx.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdmatx.config);
	hperh->hdmatx.config.src     = (void *)buf;
	hperh->hdmatx.config.dst     = (void *)&hperh->perh->DATA;
	hperh->hdmatx.config.size    = size;
	hperh->hdmatx.config.src_inc = DMA_DATA_INC_BYTE;
	hperh->hdmatx.config.dst_inc = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel    = hperh->perh == USART0 ? DMA_MSEL_USART0 : DMA_MSEL_USART1;
	hperh->hdmatx.config.msigsel = DMA_MSIGSEL_USART_TXEMPTY;
	hperh->hdmatx.config.channel = channel;
	ald_dma_config_basic(&hperh->hdmatx);

	ald_usart_clear_flag_status((usart_handle_t *)hperh, USART_FLAG_TC);
	__UNLOCK(hperh);
	ald_usart_dma_req_config((usart_handle_t *)hperh, USART_DMA_REQ_TX, ENABLE);

	return OK;
}

/**
  * @brief  Receive an amount of data in non-blocking mode.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  channel: DMA channel as USART transmit
  * @note   When the SMARTCARD parity is enabled (PCE = 1) the data received contain the parity bit.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_smartcard_recv_by_dma(smartcard_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
	if ((hperh->state != SMARTCARD_STATE_READY) && (hperh->state != SMARTCARD_STATE_BUSY_TX))
		return BUSY;
	if ((buf == NULL) || (size == 0))
		return ERROR;

	__LOCK(hperh);
	SET_BIT(hperh->state, USART_STATE_RX_MASK);

	hperh->rx_buf   = buf;
	hperh->rx_size  = size;
	hperh->rx_count = size;
	hperh->err_code = SMARTCARD_ERROR_NONE;

	if (hperh->hdmarx.perh == NULL)
		hperh->hdmarx.perh = DMA0;

	hperh->hdmarx.cplt_cbk = smartcard_dma_recv_cplt;
	hperh->hdmarx.cplt_arg = (void *)hperh;
	hperh->hdmarx.err_cbk  = smartcard_dma_error;
	hperh->hdmarx.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdmarx.config);
	hperh->hdmarx.config.src     = (void *)&hperh->perh->DATA;
	hperh->hdmarx.config.dst     = (void *)buf;
	hperh->hdmarx.config.size    = size;
	hperh->hdmarx.config.src_inc = DMA_DATA_INC_NONE;
	hperh->hdmarx.config.dst_inc = DMA_DATA_INC_BYTE;
	hperh->hdmarx.config.msel    = hperh->perh == USART0 ? DMA_MSEL_USART0 : DMA_MSEL_USART1;
	hperh->hdmarx.config.msigsel = DMA_MSIGSEL_USART_RNR;
	hperh->hdmarx.config.channel = channel;
	ald_dma_config_basic(&hperh->hdmarx);

	__UNLOCK(hperh);
	ald_usart_dma_req_config((usart_handle_t *)hperh, USART_DMA_REQ_RX, ENABLE);

	return OK;
}
#endif

/**
  * @brief  This function handles SMARTCARD interrupt request.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @retval None
  */
void ald_smartcard_irq_handler(smartcard_handle_t *hperh)
{
	uint32_t flag;
	uint32_t source;

	/* Handle parity error */
	flag   = ald_usart_get_flag_status((usart_handle_t *)hperh, USART_FLAG_PE);
	source = ald_usart_get_it_status((usart_handle_t *)hperh, USART_IT_PE);
	if ((flag != RESET) && (source != RESET))
		hperh->err_code |= SMARTCARD_ERROR_PE;

	/* Handle frame error */
	flag   = ald_usart_get_flag_status((usart_handle_t *)hperh, USART_FLAG_FE);
	source = ald_usart_get_it_status((usart_handle_t *)hperh, USART_IT_ERR);
	if ((flag != RESET) && (source != RESET))
		hperh->err_code |= SMARTCARD_ERROR_FE;

	/* Handle noise error */
	flag = ald_usart_get_flag_status((usart_handle_t *)hperh, USART_FLAG_NE);
	if ((flag != RESET) && (source != RESET))
		hperh->err_code |= SMARTCARD_ERROR_NE;

	/* Handle overrun error */
	flag = ald_usart_get_flag_status((usart_handle_t *)hperh, USART_FLAG_ORE);
	if ((flag != RESET) && (source != RESET))
		hperh->err_code |= SMARTCARD_ERROR_ORE;

	/* Handle receive */
	flag   = ald_usart_get_flag_status((usart_handle_t *)hperh, USART_FLAG_RXNE);
	source = ald_usart_get_it_status((usart_handle_t *)hperh, USART_IT_RXNE);
	if ((flag != RESET) && (source != RESET))
		__smartcard_recv_by_it(hperh);

	/* Handle transmit */
	flag   = ald_usart_get_flag_status((usart_handle_t *)hperh, USART_FLAG_TXE);
	source = ald_usart_get_it_status((usart_handle_t *)hperh, USART_IT_TXE);
	if ((flag != RESET) && (source != RESET))
		__smartcard_send_by_it(hperh);

	/* Handle transmit complete */
	flag   = ald_usart_get_flag_status((usart_handle_t *)hperh, USART_FLAG_TC);
	source = ald_usart_get_it_status((usart_handle_t *)hperh, USART_IT_TC);
	if ((flag != RESET) && (source != RESET))
		__smartcard_end_send_by_it(hperh);

	/* Handle error */
	if (hperh->err_code != SMARTCARD_ERROR_NONE) {
		USART_CLEAR_PEFLAG(hperh);
		hperh->state = SMARTCARD_STATE_READY;

		if (hperh->error_cbk)
			hperh->error_cbk(hperh);
	}
}
/**
  * @}
  */

/** @defgroup SMARTCARD_Public_Functions_Group3 Peripheral State and Errors functions
  *  @brief   SMARTCARD State and Errors functions
  *
@verbatim
  ==============================================================================
                  ##### Peripheral State and Errors functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to return the State of SmartCard
    communication process and also return Peripheral Errors occurred during communication process
     (+) ald_smartcard_get_state() API can be helpful to check in run-time the state
         of the SMARTCARD peripheral.
     (+) ald_smartcard_get_error() check in run-time errors that could be occurred during
         communication.

@endverbatim
  * @{
  */

/**
  * @brief  Returns the SMARTCARD state.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @retval ALD state
  */
smartcard_state_t ald_smartcard_get_state(smartcard_handle_t *hperh)
{
	return hperh->state;
}

/**
  * @brief  Return the SMARTCARD error code
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @retval SMARTCARD Error Code
  */
uint32_t ald_smartcard_get_error(smartcard_handle_t *hperh)
{
	return hperh->err_code;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SMARTCARD_Private_Functions   SMARTCARD Private Functions
  * @brief    SMARTCARD Private functions
  * @{
  */

#ifdef ALD_DMA
/**
  * @brief  DMA SMARTCARD transmit process complete callback.
  * @param  arg: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified DMA module.
  * @retval None
  */
static void smartcard_dma_send_cplt(void *arg)
{
	smartcard_handle_t* hperh = ( smartcard_handle_t *)arg;

	hperh->tx_count = 0;
	ald_usart_dma_req_config((usart_handle_t *)hperh, USART_DMA_REQ_TX, DISABLE);
	ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_TC, ENABLE);

	return;
}

/**
  * @brief  DMA SMARTCARD receive process complete callback.
  * @param  arg: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified DMA module.
  * @retval None
  */
static void smartcard_dma_recv_cplt(void *arg)
{
	smartcard_handle_t* hperh = ( smartcard_handle_t* )arg;

	hperh->rx_count = 0;
	ald_usart_dma_req_config((usart_handle_t *)hperh, USART_DMA_REQ_RX, DISABLE);
	CLEAR_BIT(hperh->state, USART_STATE_RX_MASK);

	if (hperh->rx_cplt_cbk)
		hperh->rx_cplt_cbk(hperh);

	return;
}

/**
  * @brief  DMA SMARTCARD communication error callback.
  * @param  arg: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified DMA module.
  * @retval None
  */
static void smartcard_dma_error(void *arg)
{
	smartcard_handle_t* hperh = ( smartcard_handle_t* )arg;

	hperh->rx_count = 0;
	hperh->tx_count = 0;
	hperh->err_code = SMARTCARD_ERROR_DMA;
	hperh->state    = SMARTCARD_STATE_READY;

	ald_usart_dma_req_config((usart_handle_t *)hperh, USART_DMA_REQ_TX, DISABLE);
	ald_usart_dma_req_config((usart_handle_t *)hperh, USART_DMA_REQ_RX, DISABLE);

	if (hperh->error_cbk)
		hperh->error_cbk(hperh);

	return;
}
#endif

/**
  * @brief  This function handles USART Communication Timeout.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  flag: specifies the USART flag to check.
  * @param  status: The new Flag status (SET or RESET).
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t smartcard_wait_flag(smartcard_handle_t *hperh, usart_flag_t flag, flag_status_t status, uint32_t timeout)
{
	uint32_t tick;

	if (timeout == 0)
		return OK;

	tick = ald_get_tick();

	while ((ald_usart_get_flag_status((usart_handle_t *)hperh, flag)) != status) {
		if (((ald_get_tick()) - tick) > timeout) {
			ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_TXE, DISABLE);
			ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_RXNE, DISABLE);
			ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_PE, DISABLE);
			ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_ERR, DISABLE);

			return TIMEOUT;
		}
	}

	return OK;
}

/**
  * @brief  Send an amount of data in non-blocking mode.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  *         Function called under interruption only, once
  *         interruptions have been enabled by ald_smartcard_send_by_it()
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __smartcard_send_by_it(smartcard_handle_t *hperh)
{
	if ((hperh->state != SMARTCARD_STATE_BUSY_TX) && (hperh->state != SMARTCARD_STATE_BUSY_TX_RX))
		return BUSY;

	WRITE_REG(hperh->perh->DATA, *hperh->tx_buf++);

	if (--hperh->tx_count == 0) {
		ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_TXE, DISABLE);
		ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_TC, ENABLE);
	}

	return OK;
}


/**
  * @brief  Wraps up transmission in non blocking mode.
  * @param  hperh: pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __smartcard_end_send_by_it(smartcard_handle_t *hperh)
{
	ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_TC, DISABLE);
	CLEAR_BIT(hperh->state, USART_STATE_TX_MASK);

	if (hperh->state == SMARTCARD_STATE_READY)
		ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_ERR, DISABLE);

	if (hperh->tx_cplt_cbk)
		hperh->tx_cplt_cbk(hperh);

	return OK;
}


/**
  * @brief  Receive an amount of data in non-blocking mode.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __smartcard_recv_by_it(smartcard_handle_t *hperh)
{
	if ((hperh->state != SMARTCARD_STATE_BUSY_RX) && (hperh->state != SMARTCARD_STATE_BUSY_TX_RX))
		return BUSY;

	*hperh->rx_buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);

	if (--hperh->rx_count == 0) {
		ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_RXNE, DISABLE);
		ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_PE, DISABLE);
		ald_usart_interrupt_config((usart_handle_t *)hperh, USART_IT_ERR, DISABLE);
		CLEAR_BIT(hperh->state, USART_STATE_RX_MASK);

		if (hperh->rx_cplt_cbk)
			hperh->rx_cplt_cbk(hperh);
	}

	return OK;
}

/**
  * @brief  Configures the SMARTCARD peripheral.
  * @param  hperh: Pointer to a smartcard_handle_t structure that contains
  *         the configuration information for the specified SMARTCARD module.
  * @retval None
  */
static void smartcard_set_config(smartcard_handle_t *hperh)
{
	uint32_t tmp;
	uint32_t integer;
	uint32_t fractional;

	/* Check the parameters */
	assert_param(IS_USART(hperh->perh));
	assert_param(IS_USART_BAUDRATE(hperh->init.baud));
	assert_param(IS_USART_WORD_LENGTH(hperh->init.word_length));
	assert_param(IS_USART_STOPBITS(hperh->init.stop_bits));
	assert_param(IS_USART_PARITY(hperh->init.parity));
	assert_param(IS_USART_MODE(hperh->init.mode));

	MODIFY_REG(hperh->perh->CON1, USART_CON1_STPLEN_MSK, hperh->init.stop_bits << USART_CON1_STPLEN_POSS);
	tmp = READ_REG(hperh->perh->CON0);
	MODIFY_REG(tmp, USART_CON0_DLEN_MSK, hperh->init.word_length << USART_CON0_DLEN_POS);

	if (hperh->init.parity == USART_PARITY_NONE)
		CLEAR_BIT(tmp, USART_CON0_PEN_MSK);
	else
		SET_BIT(tmp, USART_CON0_PEN_MSK);

	if (hperh->init.parity == USART_PARITY_ODD)
		SET_BIT(tmp, USART_CON0_PSEL_MSK);
	else
		CLEAR_BIT(tmp, USART_CON0_PSEL_MSK);

	WRITE_REG(hperh->perh->CON0, tmp);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_RTSEN_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_CTSEN_MSK);
	MODIFY_REG(hperh->perh->CON0, USART_CON0_RXEN_MSK, (hperh->init.mode & 0x1) << USART_CON0_RXEN_POS);
	MODIFY_REG(hperh->perh->CON0, USART_CON0_TXEN_MSK, ((hperh->init.mode >> 1) & 0x1) << USART_CON0_TXEN_POS);
	tmp = READ_REG(hperh->perh->CON1);
	SET_BIT(tmp, USART_CON1_SCKEN_MSK);
	MODIFY_REG(tmp, USART_CON1_SCKPOL_MSK, hperh->init.polarity << USART_CON1_SCKPOL_POS);
	MODIFY_REG(tmp, USART_CON1_SCKPHA_MSK, hperh->init.phase << USART_CON1_SCKPHA_POS);
	MODIFY_REG(tmp, USART_CON1_LBCP_MSK, hperh->init.last_bit << USART_CON1_LBCP_POS);

	/* Determine the integer part */
	if (READ_BIT(hperh->perh->CON0, (1 << 15))) {
		/* Integer part computing in case Oversampling mode is 8 Samples */
		integer = ((25 * ald_cmu_get_pclk1_clock()) / (2 * (hperh->init.baud)));
	}
	else {
		/* Integer part computing in case Oversampling mode is 16 Samples */
		integer = ((25 * ald_cmu_get_pclk1_clock()) / (4 * (hperh->init.baud)));
	}
	tmp = (integer / 100) << 4;

	/* Determine the fractional part */
	fractional = integer - (100 * (tmp >> 4));

	/* Implement the fractional part in the register */
	if (READ_BIT(hperh->perh->CON0, (1 << 15)))
    		tmp |= ((((fractional * 8) + 50) / 100)) & ((uint8_t)0x07);
	else
		tmp |= ((((fractional * 16) + 50) / 100)) & ((uint8_t)0x0F);

	WRITE_REG(hperh->perh->BAUDCON, (uint16_t)tmp);
	return;
}

/**
  * @}
  */

#endif /* ALD_SMARTCARD */
/**
  * @}
  */

/**
  * @}
  */
