/**
  *********************************************************************************
  *
  * @file    ald_uart.c
  * @brief   UART module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter (UART) peripheral:
  *           + Initialization and Configuration functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
  *
  * @version V1.0
  * @date    21 Nov 2017
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
    The UART driver can be used as follows:

    (#) Declare a uart_handle_t handle structure.

    (#) Initialize the UART low level resources:
        (##) Enable the UARTx interface clock.
        (##) UART pins configuration:
            (+++) Enable the clock for the UART GPIOs.
            (+++) Configure the UART pins (TX as alternate function pull-up, RX as alternate function Input).
        (##) NVIC configuration if you need to use interrupt process (ald_uart_send_by_it()
             and ald_uart_recv_by_it() APIs):
            (+++) Configure the uart interrupt priority.
            (+++) Enable the NVIC UART IRQ handle.
        (##) DMA Configuration if you need to use DMA process (ald_uart_send_by_dma()
             and ald_uart_recv_by_dma() APIs):
            (+++) Select the DMA Tx/Rx channel.
            (+++) Associate the initialized DMA handle to the UART DMA Tx/Rx handle.

    (#) Program the Baud Rate, Word Length, Stop Bit, Parity, Hardware
        flow control and Mode(Receiver/Transmitter) in the hperh Init structure.

    (#) Initialize the UART registers by calling the ald_uart_init() API.

     [..]
        Three operation modes are available within this driver:

     *** Polling mode IO operation ***
     =================================
     [..]
       (+) Send an amount of data in blocking mode using ald_uart_send()
       (+) Receive an amount of data in blocking mode using ald_uart_recv()

     *** Interrupt mode IO operation ***
     ===================================
     [..]
       (+) Send an amount of data in non blocking mode using ald_uart_send_by_it()
       (+) At transmission end of transfer hperh->tx_cplt_cbk() is executed and user can
           add his own code by customization of function pointer hperh->tx_cplt_cbk()
       (+) Receive an amount of data in non blocking mode using ald_uart_recv_by_it()
       (+) At reception end of transfer hperh->rx_cplt_cbk() is executed and user can
           add his own code by customization of function pointer hperh->rx_cplt_cbk()
       (+) In case of transfer Error, hperh->error_cbk() function is executed and user can
           add his own code by customization of function pointer hperh->error_cbk()

     *** DMA mode IO operation ***
     ==============================
     [..]
       (+) Send an amount of data in non blocking mode (DMA) using ald_uart_send_by_dma()
       (+) At transmission end of transfer hperh->tx_cplt_cbk() is executed and user can
           add his own code by customization of function pointer hperh->tx_cplt_cbk()
       (+) Receive an amount of data in non blocking mode (DMA) using ald_uart_recv_by_dma()
       (+) At reception end of transfer hperh->rx_cplt_cbk() is executed and user can
           add his own code by customization of function pointer hperh->rx_cplt_cbk()
       (+) In case of transfer Error, hperh->error_cbk() function is executed and user can
           add his own code by customization of function pointer hperh->error_cbk()
       (+) Pause the DMA Transfer using ald_uart_dma_pause()
       (+) Resume the DMA Transfer using ald_uart_dma_resume()
       (+) Stop the DMA Transfer using ald_uart_dma_stop()

    @endverbatim
  ******************************************************************************
  */

#include "ald_uart.h"
#include "ald_cmu.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup UART UART
  * @brief UART module driver
  * @{
  */
#ifdef ALD_UART

/** @defgroup UART_Private_Functions   UART Private Functions
  *  @brief   UART Private functions
  * @{
  */
#ifdef ALD_DMA
/**
  * @brief  DMA uart transmit process complete callback.
  * @param  arg: Pointer to a uart_handle_t structure.
  * @retval None
  */
static void uart_dma_send_cplt(void *arg)
{
	uart_handle_t *hperh = (uart_handle_t *)arg;

	if (hperh->state == UART_STATE_BUSY_TX)
		ald_uart_dma_req_config(hperh, DISABLE);

	hperh->tx_count = 0;
	ald_uart_interrupt_config(hperh, UART_IT_TC, ENABLE);
	return;
}

/**
  * @brief  DMA uart receive process complete callback.
  * @param  arg: Pointer to a uart_handle_t structure.
  * @retval None
  */
static void uart_dma_recv_cplt(void *arg)
{
	uart_handle_t *hperh = (uart_handle_t *)arg;

	if (hperh->state == UART_STATE_BUSY_RX)
		ald_uart_dma_req_config(hperh, DISABLE);

	hperh->rx_count = 0;
	CLEAR_BIT(hperh->state, UART_STATE_RX_MASK);

	if (hperh->rx_cplt_cbk)
		hperh->rx_cplt_cbk(hperh);

	return;
}

/**
  * @brief  DMA uart communication error callback.
  * @param  arg: Pointer to a uart_handle_t structure.
  * @retval None
  */
static void uart_dma_error(void *arg)
{
	uart_handle_t *hperh = (uart_handle_t *)arg;

	hperh->rx_count  = 0;
	hperh->tx_count  = 0;
	hperh->state     = UART_STATE_READY;
	hperh->err_code |= UART_ERROR_DMA;
	ald_uart_dma_req_config(hperh, DISABLE);

	if (hperh->error_cbk)
		hperh->error_cbk(hperh);

	return;
}
#endif

/**
  * @brief  This function handles uart Communication Timeout.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  flag: specifies the uart flag to check.
  * @param  status: The new Flag status (SET or RESET).
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t uart_wait_flag(uart_handle_t *hperh, uart_status_t flag, flag_status_t status, uint32_t timeout)
{
	uint32_t tick;

	if (timeout == 0)
		return ERROR;

	tick = ald_get_tick();

	/* Waiting for flag */
	while ((ald_uart_get_status(hperh, flag)) != status) {
		if (((ald_get_tick()) - tick) > timeout)
			return TIMEOUT;
	}

	return OK;
}

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __uart_send_by_it(uart_handle_t *hperh)
{
	if ((hperh->state & UART_STATE_TX_MASK) == 0x0)
		return BUSY;

	WRITE_REG(hperh->perh->TBR, (uint8_t)(*hperh->tx_buf++ & 0x00FF));

	if (--hperh->tx_count == 0) {
		ald_uart_clear_flag_status(hperh, UART_IF_TC);
		ald_uart_interrupt_config(hperh, UART_IT_TXS, DISABLE);
		ald_uart_interrupt_config(hperh, UART_IT_TC, ENABLE);
	}

	return OK;
}

/**
  * @brief  Wraps up transmission in non blocking mode.
  * @param  hperh: pointer to a uart_handle_t structure.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __uart_end_send_by_it(uart_handle_t *hperh)
{
	if (!(READ_BIT(hperh->perh->SR, UART_SR_TEM_MSK)))
		return OK;

	ald_uart_interrupt_config(hperh, UART_IT_TC, DISABLE);
	CLEAR_BIT(hperh->state, UART_STATE_TX_MASK);
	if (hperh->tx_cplt_cbk)
		hperh->tx_cplt_cbk(hperh);

	return OK;
}

/**
  * @brief  Receives an amount of data in non blocking mode
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __uart_recv_by_it(uart_handle_t *hperh)
{
	if ((hperh->state & UART_STATE_RX_MASK) == 0x0)
		return BUSY;

	*hperh->rx_buf++ = (uint8_t)(hperh->perh->RBR & 0xFF);

	if (--hperh->rx_count == 0) {
		ald_uart_interrupt_config(hperh, UART_IT_RXRD, DISABLE);
		CLEAR_BIT(hperh->state, UART_STATE_RX_MASK);

		if (hperh->rx_cplt_cbk)
			hperh->rx_cplt_cbk(hperh);
	}

	return OK;
}
/**
  * @}
  */

/** @defgroup UART_Public_Functions UART Public Functions
  * @{
  */

/** @defgroup UART_Public_Functions_Group1 Initialization and Configuration functions
  * @brief    Initialization and Configuration functions
  *
  * @verbatim
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the UARTx
    and configure UARTx param.
      (+) For the UARTx only these parameters can be configured:
        (++) Baud Rate
        (++) Word Length
        (++) Stop Bit
        (++) Parity
        (++) Hardware flow control
      (+) For RS485 mode, user also need configure some parameters by
          ald_uart_rs485_config():
        (++) Enable/disable normal point mode
	(++) Enable/disable auto-direction
	(++) Enable/disable address detection invert
	(++) Enable/disable address for compare

    @endverbatim
  * @{
  */

/**
  * @brief  Reset UART peripheral
  * @param  hperh: Pointer to a uart_handle_t structure that contains
  *         the configuration information for the specified uart module.
  * @retval None
  */
void ald_uart_reset(uart_handle_t *hperh)
{
	assert_param(IS_UART_ALL(hperh->perh));

	WRITE_REG(hperh->perh->BRR, 0x0);
	WRITE_REG(hperh->perh->LCR, 0x0);
	WRITE_REG(hperh->perh->MCR, 0x0);
	WRITE_REG(hperh->perh->CR, 0x0);
	WRITE_REG(hperh->perh->RTOR, 0x0);
	WRITE_REG(hperh->perh->FCR, 0x0);
	WRITE_REG(hperh->perh->IDR, 0xFFF);

	hperh->err_code = UART_ERROR_NONE;
	hperh->state    = UART_STATE_RESET;

	__UNLOCK(hperh);
	return;
}

/**
  * @brief  Initializes the UARTx according to the specified
  *         parameters in the uart_handle_t.
  * @param  hperh: Pointer to a uart_handle_t structure that contains
  *         the configuration information for the specified UART module.
  * @retval None
  */
void ald_uart_init(uart_handle_t *hperh)
{
	uint32_t tmp;

	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_UART_BAUDRATE(hperh->init.baud));
	assert_param(IS_UART_WORD_LENGTH(hperh->init.word_length));
	assert_param(IS_UART_STOPBITS(hperh->init.stop_bits));
	assert_param(IS_UART_PARITY(hperh->init.parity));
	assert_param(IS_UART_MODE(hperh->init.mode));
	assert_param(IS_UART_HARDWARE_FLOW_CONTROL(hperh->init.fctl));

	ald_uart_reset(hperh);

	tmp = READ_REG(hperh->perh->LCR);
	MODIFY_REG(tmp, UART_LCR_DLS_MSK, hperh->init.word_length << UART_LCR_DLS_POSS);
	MODIFY_REG(tmp, UART_LCR_STOP_MSK, hperh->init.stop_bits << UART_LCR_STOP_POS);
	MODIFY_REG(tmp, UART_LCR_PEN_MSK, (hperh->init.parity == UART_PARITY_NONE ? 0 : 1) << UART_LCR_PEN_POS);
	MODIFY_REG(tmp, UART_LCR_PS_MSK, (hperh->init.parity == UART_PARITY_EVEN ? 1 : 0) << UART_LCR_PS_POS);
	WRITE_REG(hperh->perh->LCR, tmp);
	MODIFY_REG(hperh->perh->MCR, UART_MCR_AFCEN_MSK, hperh->init.fctl << UART_MCR_AFCEN_POS);
	SET_BIT(hperh->perh->LCR, UART_LCR_BRWEN_MSK);
	WRITE_REG(hperh->perh->BRR, ald_cmu_get_pclk1_clock() / hperh->init.baud);
	CLEAR_BIT(hperh->perh->LCR, UART_LCR_BRWEN_MSK);
	SET_BIT(hperh->perh->FCR, UART_FCR_FIFOEN_MSK);
	SET_BIT(hperh->perh->FCR, UART_FCR_RFRST_MSK);
	SET_BIT(hperh->perh->FCR, UART_FCR_TFRST_MSK);
	MODIFY_REG(hperh->perh->FCR, UART_FCR_RXTL_MSK, 0 << UART_FCR_RXTL_POSS);
	MODIFY_REG(hperh->perh->FCR, UART_FCR_TXTL_MSK, 0 << UART_FCR_TXTL_POSS);
	SET_BIT(hperh->perh->LCR, UART_LCR_RXEN_MSK);

	if (hperh->init.mode == UART_MODE_LIN)
		SET_BIT(hperh->perh->MCR, UART_MCR_LINEN_MSK);
	else if (hperh->init.mode == UART_MODE_IrDA)
		SET_BIT(hperh->perh->MCR, UART_MCR_IREN_MSK);
	else if (hperh->init.mode == UART_MODE_RS485)
		SET_BIT(hperh->perh->MCR, UART_MCR_AADEN_MSK);
	else if (hperh->init.mode == UART_MODE_HDSEL)
		SET_BIT(hperh->perh->MCR, UART_MCR_HDSEL_MSK);
	else
		;/* do nothing */

	if (hperh->init.fctl)
		SET_BIT(hperh->perh->MCR, UART_MCR_RTSCTRL_MSK);
	if (hperh->init.mode == UART_MODE_IrDA)
		SET_BIT(hperh->perh->LCR, UART_LCR_RXINV_MSK);

	hperh->state    = UART_STATE_READY;
	hperh->err_code = UART_ERROR_NONE;
	return;
}

/**
  * @brief  Configure the RS485 mode according to the specified
  *         parameters in the uart_rs485_config_t.
  * @param  hperh: Pointer to a uart_handle_t structure that contains
  *         the configuration information for the specified UART module.
  * @param  config: Specifies the RS485 parameters.
  * @retval None
  */
void ald_uart_rs485_config(uart_handle_t *hperh, uart_rs485_config_t *config)
{
	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_FUNC_STATE(config->normal));
	assert_param(IS_FUNC_STATE(config->dir));
	assert_param(IS_FUNC_STATE(config->invert));

	MODIFY_REG(hperh->perh->MCR, UART_MCR_AADNOR_MSK, config->normal << UART_MCR_AADNOR_POS);
	MODIFY_REG(hperh->perh->MCR, UART_MCR_AADDIR_MSK, config->dir << UART_MCR_AADDIR_POS);
	MODIFY_REG(hperh->perh->MCR, UART_MCR_AADINV_MSK, config->invert << UART_MCR_AADINV_POS);
	MODIFY_REG(hperh->perh->CR, UART_CR_ADDR_MSK, config->addr << UART_CR_ADDR_POSS);

	return;
}
/**
  * @}
  */

/** @defgroup UART_Public_Functions_Group2 IO operation functions
  * @brief UART Transmit and Receive functions
  * @verbatim
  ==============================================================================
                      # IO operation functions #
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the UART data transfers.

    (#) There are two modes of transfer:
       (++) Blocking mode: The communication is performed in polling mode.
            The Status of all data processing is returned by the same function
            after finishing transfer.
       (++) Non blocking mode: The communication is performed using Interrupts
            or DMA, these APIs return the Status.
            The end of the data processing will be indicated through the
            dedicated UART IRQ when using Interrupt mode or the DMA IRQ when
            using DMA mode.
            The hperh->tx_cplt_cbk(), hperh->rx_cplt_cbk() user callbacks
            will be executed respectively at the end of the transmit or receive process.
            The hperh->error_cbk() user callback will be executed when
            a communication error is detected.

    (#) Blocking mode APIs are:
        (++) ald_uart_send()
        (++) ald_uart_recv()

    (#) Non Blocking mode APIs with Interrupt are:
        (++) ald_uart_send_by_it()
        (++) ald_uart_recv_by_it()
        (++) ald_uart_irq_handler()

    (#) Non Blocking mode functions with DMA are:
        (++) ald_uart_send_by_dma()
        (++) ald_uart_recv_by_dma()
        (++) ald_uart_dma_pause()
        (++) ald_uart_dma_resume()
        (++) ald_uart_dma_stop()

    (#) A set of transfer complete callbacks are provided in non blocking mode:
        (++) hperh->tx_cplt_cbk()
        (++) hperh->rx_cplt_cbk()
        (++) hperh->error_cbk()

    @endverbatim
  * @{
  */

/**
  * @brief  Sends an amount of data in blocking mode.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_send(uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
	assert_param(IS_UART_ALL(hperh->perh));

	if ((hperh->state != UART_STATE_READY) && (hperh->state != UART_STATE_BUSY_RX))
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	__LOCK(hperh);
	hperh->err_code = UART_ERROR_NONE;
	SET_BIT(hperh->state, UART_STATE_TX_MASK);

	hperh->tx_size  = size;
	hperh->tx_count = size;

	while (hperh->tx_count-- > 0) {
		if (uart_wait_flag(hperh, UART_STATUS_TBEM, SET, timeout) != OK) {
			__UNLOCK(hperh);
			hperh->state = UART_STATE_READY;
			return TIMEOUT;
		}

		WRITE_REG(hperh->perh->TBR, (*buf++ & 0xFF));
	}

	if (uart_wait_flag(hperh, UART_STATUS_TEM, SET, timeout) != OK) {
		__UNLOCK(hperh);
		hperh->state = UART_STATE_READY;
		return TIMEOUT;
	}

	CLEAR_BIT(hperh->state, UART_STATE_TX_MASK);
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Receives an amount of data in blocking mode.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_recv(uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
	assert_param(IS_UART_ALL(hperh->perh));

	if ((hperh->state != UART_STATE_READY) && (hperh->state != UART_STATE_BUSY_TX))
		return BUSY;

	if ((buf == NULL ) || (size == 0))
		return  ERROR;

	__LOCK(hperh);

	hperh->err_code = UART_ERROR_NONE;
	SET_BIT(hperh->state, UART_STATE_RX_MASK);

	hperh->rx_size  = size;
	hperh->rx_count = size;

	while (hperh->rx_count-- > 0) {
		if (uart_wait_flag(hperh, UART_STATUS_DR, SET, timeout) != OK) {
			__UNLOCK(hperh);
			hperh->state = UART_STATE_READY;
			return TIMEOUT;
		}

		*buf++ = (uint8_t)(hperh->perh->RBR & 0xFF);
	}

	CLEAR_BIT(hperh->state, UART_STATE_RX_MASK);
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_send_by_it(uart_handle_t *hperh, uint8_t *buf, uint16_t size)
{
	assert_param(IS_UART_ALL(hperh->perh));

	if ((hperh->state != UART_STATE_READY) && (hperh->state != UART_STATE_BUSY_RX))
		return BUSY;

	if ((buf == NULL ) || (size == 0))
		return ERROR;

	__LOCK(hperh);

	hperh->tx_buf   = buf;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->err_code = UART_ERROR_NONE;
	SET_BIT(hperh->state, UART_STATE_TX_MASK);
	__UNLOCK(hperh);

	if (((ald_uart_get_status(hperh, UART_STATUS_TBEM)) == SET)
			&& ((ald_uart_get_flag_status(hperh, UART_IF_TXS)) == RESET)) {
		WRITE_REG(hperh->perh->TBR, (*hperh->tx_buf++ & 0xFF));
		--hperh->tx_count;
	}

	if (hperh->tx_count == 0) {
		ald_uart_interrupt_config(hperh, UART_IT_TC, ENABLE);
		return OK;
	}

	ald_uart_interrupt_config(hperh, UART_IT_TXS, ENABLE);
	return OK;
}

/**
  * @brief  Receives an amount of data in non blocking mode
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_recv_by_it(uart_handle_t *hperh, uint8_t *buf, uint16_t size)
{
	assert_param(IS_UART_ALL(hperh->perh));

	if ((hperh->state != UART_STATE_READY) && (hperh->state != UART_STATE_BUSY_TX))
		return BUSY;

	if ((buf == NULL ) || (size == 0))
		return ERROR;

	__LOCK(hperh);
	hperh->rx_buf   = buf;
	hperh->rx_size  = size;
	hperh->rx_count = size;
	hperh->err_code = UART_ERROR_NONE;
	SET_BIT(hperh->state, UART_STATE_RX_MASK);
	__UNLOCK(hperh);

	ald_uart_interrupt_config(hperh, UART_IT_RXRD, ENABLE);
	return OK;
}
#ifdef ALD_DMA
/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as UART transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_send_by_dma(uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
	assert_param(IS_UART_ALL(hperh->perh));

	if ((hperh->state != UART_STATE_READY) && (hperh->state != UART_STATE_BUSY_RX))
		return BUSY;

	if ((buf == NULL ) || (size == 0))
		return ERROR;

	__LOCK(hperh);

	hperh->tx_buf   = buf;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->err_code = UART_ERROR_NONE;
	SET_BIT(hperh->state, UART_STATE_TX_MASK);

	if (hperh->hdmatx.perh == NULL)
		hperh->hdmatx.perh = DMA0;

	hperh->hdmatx.cplt_cbk = uart_dma_send_cplt;
	hperh->hdmatx.cplt_arg = (void *)hperh;
	hperh->hdmatx.err_cbk  = uart_dma_error;
	hperh->hdmatx.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdmatx.config);
	hperh->hdmatx.config.src     = (void *)buf;
	hperh->hdmatx.config.dst     = (void *)&hperh->perh->TBR;
	hperh->hdmatx.config.size    = size;
	hperh->hdmatx.config.src_inc = DMA_DATA_INC_BYTE;
	hperh->hdmatx.config.dst_inc = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msigsel = DMA_MSIGSEL_UART_TXEMPTY;
	hperh->hdmatx.config.burst   = ENABLE;
	hperh->hdmatx.config.channel = channel;

	if (hperh->init.mode == UART_MODE_RS485) {
		hperh->hdmatx.config.src_inc    = DMA_DATA_INC_HALFWORD;
		hperh->hdmatx.config.data_width = DMA_DATA_SIZE_HALFWORD;
	}

	if (hperh->perh == UART0)
		hperh->hdmatx.config.msel = DMA_MSEL_UART0;
	else if (hperh->perh == UART1)
		hperh->hdmatx.config.msel = DMA_MSEL_UART1;
	else if (hperh->perh == UART2)
		hperh->hdmatx.config.msel = DMA_MSEL_UART2;
	else if (hperh->perh == UART3)
		hperh->hdmatx.config.msel = DMA_MSEL_UART3;
	else
		;	/* do nothing */

	ald_dma_config_basic(&hperh->hdmatx);

	__UNLOCK(hperh);
	ald_uart_clear_flag_status(hperh, UART_IF_TC);
	ald_uart_dma_req_config(hperh, ENABLE);

	return OK;
}

/**
  * @brief  Receives an amount of data in non blocking mode.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  channel: DMA channel as UART receive
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_recv_by_dma(uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
	assert_param(IS_UART_ALL(hperh->perh));

	if ((hperh->state != UART_STATE_READY) && (hperh->state != UART_STATE_BUSY_TX))
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return ERROR;

	__LOCK(hperh);

	hperh->rx_buf   = buf;
	hperh->rx_size  = size;
	hperh->err_code = UART_ERROR_NONE;
	SET_BIT(hperh->state, UART_STATE_RX_MASK);

	if (hperh->hdmarx.perh == NULL)
		hperh->hdmarx.perh = DMA0;

	hperh->hdmarx.cplt_cbk = uart_dma_recv_cplt;
	hperh->hdmarx.cplt_arg = (void *)hperh;
	hperh->hdmarx.err_cbk  = uart_dma_error;
	hperh->hdmarx.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdmarx.config);
	hperh->hdmarx.config.src     = (void *)&hperh->perh->RBR;
	hperh->hdmarx.config.dst     = (void *)buf;
	hperh->hdmarx.config.size    = size;
	hperh->hdmarx.config.src_inc = DMA_DATA_INC_NONE;
	hperh->hdmarx.config.dst_inc = DMA_DATA_INC_BYTE;
	hperh->hdmarx.config.msigsel = DMA_MSIGSEL_UART_RNR;
	hperh->hdmarx.config.burst   = ENABLE;
	hperh->hdmarx.config.channel = channel;

	if (hperh->init.mode == UART_MODE_RS485) {
		hperh->hdmarx.config.dst_inc    = DMA_DATA_INC_HALFWORD;
		hperh->hdmarx.config.data_width = DMA_DATA_SIZE_HALFWORD;
	}

	if (hperh->perh == UART0)
		hperh->hdmarx.config.msel = DMA_MSEL_UART0;
	else if (hperh->perh == UART1)
		hperh->hdmarx.config.msel = DMA_MSEL_UART1;
	else if (hperh->perh == UART2)
		hperh->hdmarx.config.msel = DMA_MSEL_UART2;
	else if (hperh->perh == UART3)
		hperh->hdmarx.config.msel = DMA_MSEL_UART3;
	else
		;

	ald_dma_config_basic(&hperh->hdmarx);
	__UNLOCK(hperh);
	ald_uart_dma_req_config(hperh, ENABLE);

	return OK;
}

/**
  * @brief  Pauses the DMA Transfer.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_dma_pause(uart_handle_t *hperh)
{
	assert_param(IS_UART_ALL(hperh->perh));

	ald_uart_dma_req_config(hperh, DISABLE);
	return OK;
}

/**
  * @brief  Resumes the DMA Transfer.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_dma_resume(uart_handle_t *hperh)
{
	assert_param(IS_UART_ALL(hperh->perh));

	ald_uart_dma_req_config(hperh, ENABLE);
	return OK;
}

/**
  * @brief  Stops the DMA Transfer.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_dma_stop(uart_handle_t *hperh)
{
	assert_param(IS_UART_ALL(hperh->perh));

	ald_uart_dma_req_config(hperh, DISABLE);
	hperh->state = UART_STATE_READY;
	return OK;
}
#endif

/**
  * @brief  This function handles UART interrupt request.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval None
  */
void ald_uart_irq_handler(uart_handle_t *hperh)
{
	assert_param(IS_UART_ALL(hperh->perh));

	/* Handle parity error */
	if ((ald_uart_get_status(hperh, UART_STATUS_PE)) != RESET)
		hperh->err_code |= UART_ERROR_PE;

	/* Handle frame error */
	if ((ald_uart_get_status(hperh, UART_STATUS_FE)) != RESET)
		hperh->err_code |= UART_ERROR_FE;

	/* Handle overflow error */
	if ((ald_uart_get_status(hperh, UART_STATUS_OE)) != RESET)
		hperh->err_code |= UART_ERROR_ORE;

	/* Receive */
	if ((ald_uart_get_mask_flag_status(hperh, UART_IF_RXRD)) != RESET) {
		__uart_recv_by_it(hperh);
		ald_uart_clear_flag_status(hperh, UART_IF_RXRD);
	}

	/* Transmit */
	if ((ald_uart_get_mask_flag_status(hperh, UART_IF_TXS)) != RESET) {
		__uart_send_by_it(hperh);
		ald_uart_clear_flag_status(hperh, UART_IF_TXS);
	}

	/* End Transmit */
	if ((ald_uart_get_mask_flag_status(hperh, UART_IF_TC)) != RESET) {
		__uart_end_send_by_it(hperh);
		ald_uart_clear_flag_status(hperh, UART_IF_TC);
	}

	/* Handle error state */
	if (hperh->err_code != UART_ERROR_NONE) {
		hperh->state = UART_STATE_READY;

		if (hperh->error_cbk)
			hperh->error_cbk(hperh);
	}
}
/**
  * @}
  */

/** @defgroup UART_Public_Functions_Group3 Peripheral Control functions
  *  @brief   UART control functions
  *
  * @verbatim
  ==============================================================================
                      ##### Peripheral Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control the UART:
    (+) ald_uart_interrupt_config() API can be helpful to configure UART interrupt source.
    (+) ald_uart_dma_req_config() API can be helpful to configure UART DMA request.
    (+) ald_uart_tx_fifo_config() API can be helpful to configure UART TX FIFO paramters.
    (+) ald_uart_rx_fifo_config() API can be helpful to configure UART RX FIFO paramters.
    (+) ald_uart_lin_send_break() API can send a frame of break in LIN mode.
    (+) ald_uart_lin_detect_break_len_config() API can be helpful to configure the length of break frame.
    (+) ald_uart_auto_baud_config() API can be helpful to configure detection data mode.
    (+) ald_uart_get_it_status() API can get the status of interrupt source.
    (+) ald_uart_get_status() API can get the status of UART_SR register.
    (+) ald_uart_get_flag_status() API can get the status of UART flag.
    (+) ald_uart_get_mask_flag_status() API can get status os flag and interrupt source.
    (+) ald_uart_clear_flag_status() API can clear UART flag.

    @endverbatim
  * @{
  */

/**
  * @brief  Enable/disable the specified UART interrupts.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  it: Specifies the UART interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref uart_it_t.
  * @param  state: New state of the specified UART interrupts.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_uart_interrupt_config(uart_handle_t *hperh, uart_it_t it, type_func_t state)
{
	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_UART_IT(it));
	assert_param(IS_FUNC_STATE(state));

	if (state == ENABLE)
		WRITE_REG(hperh->perh->IER, it);
	else
		WRITE_REG(hperh->perh->IDR, it);

	return;
}

/**
  * @brief  Configure UART DMA request.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  state: New state of the specified DMA request.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_uart_dma_req_config(uart_handle_t *hperh, type_func_t state)
{
	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_FUNC_STATE(state));

	if (state == ENABLE)
		SET_BIT(hperh->perh->MCR, UART_MCR_DMAEN_MSK);
	else
		CLEAR_BIT(hperh->perh->MCR, UART_MCR_DMAEN_MSK);

	return;
}

/**
  * @brief  Configure transmit fifo parameters.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  config: Transmit fifo trigger level.
  * @retval None
  */
void ald_uart_tx_fifo_config(uart_handle_t *hperh, uart_txfifo_t config)
{
	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_UART_TXFIFO_TYPE(config));

	SET_BIT(hperh->perh->FCR, UART_FCR_TFRST_MSK);
	MODIFY_REG(hperh->perh->FCR, UART_FCR_TXTL_MSK, config << UART_FCR_TXTL_POSS);
	SET_BIT(hperh->perh->FCR, UART_FCR_FIFOEN_MSK);

	return;
}

/**
  * @brief  Configure receive fifo parameters.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  config: Receive fifo trigger level.
  * @retval None
  */
void ald_uart_rx_fifo_config(uart_handle_t *hperh, uart_rxfifo_t config)
{
	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_UART_RXFIFO_TYPE(config));

	SET_BIT(hperh->perh->FCR, UART_FCR_RFRST_MSK);
	MODIFY_REG(hperh->perh->FCR, UART_FCR_RXTL_MSK, config << UART_FCR_RXTL_POSS);
	SET_BIT(hperh->perh->FCR, UART_FCR_FIFOEN_MSK);

	return;
}

/**
  * @brief  request to send a frame of break.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval None
  */
void ald_uart_lin_send_break(uart_handle_t *hperh)
{
	assert_param(IS_UART_ALL(hperh->perh));

	SET_BIT(hperh->perh->MCR, UART_MCR_BKREQ_MSK);
	return;
}

/**
  * @brief  Configure the length of break frame to be detect.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  len: Length of break frame.
  *           @arg LIN_BREAK_LEN_10B
  *           @arg LIN_BREAK_LEN_11B
  * @retval None
  */
void ald_uart_lin_detect_break_len_config(uart_handle_t *hperh, uart_lin_break_len_t len)
{
	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_UART_LIN_BREAK_LEN(len));

	MODIFY_REG(hperh->perh->MCR, UART_MCR_LINBDL_MSK, len << UART_MCR_LINBDL_POS);
	return;
}

/**
  * @brief  Configure the mode of auto-baud-rate detect.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  mode: The mode of auto-baud-rate detect.
  *           @arg UART_ABRMOD_1_TO_0
  *           @arg UART_ABRMOD_1
  *           @arg UART_ABRMOD_0_TO_1
  * @retval None
  */
void ald_uart_auto_baud_config(uart_handle_t *hperh, uart_auto_baud_mode_t mode)
{
	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_UART_AUTO_BAUD_MODE(mode));

	MODIFY_REG(hperh->perh->MCR, UART_MCR_ABRMOD_MSK, mode << UART_MCR_ABRMOD_POSS);
	return;
}

/**
  * @brief  Send address in RS485 mode.
  * @param  hperh: Pointer to a uart_handle_t structure that contains
  *         the configuration information for the specified UART module.
  * @param  addr: the address of RS485 device.
  * @param  timeout: Timeout duration
  * @retval The ALD status.
  */
ald_status_t ald_uart_rs485_send_addr(uart_handle_t *hperh, uint16_t addr, uint32_t timeout)
{
	assert_param(IS_UART_ALL(hperh->perh));

	if ((hperh->state != UART_STATE_READY) && (hperh->state != UART_STATE_BUSY_RX))
		return BUSY;

	SET_BIT(hperh->state, UART_STATE_TX_MASK);

	if (uart_wait_flag(hperh, UART_STATUS_TBEM, SET, timeout) != OK) {
		hperh->state = UART_STATE_READY;
		return TIMEOUT;
	}

	WRITE_REG(hperh->perh->TBR, (addr | 0x100));

	if (uart_wait_flag(hperh, UART_STATUS_TEM, SET, timeout) != OK) {
		hperh->state = UART_STATE_READY;
		return TIMEOUT;
	}

	CLEAR_BIT(hperh->state, UART_STATE_TX_MASK);

	return OK;
}

/**
  * @brief  Get the status of UART interrupt source.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  it: Specifies the UART interrupt source.
  *         This parameter can be one of the @ref uart_it_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
it_status_t ald_uart_get_it_status(uart_handle_t *hperh, uart_it_t it)
{
	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_UART_IT(it));

	if (READ_BIT(hperh->perh->IVS, it))
		return SET;

	return RESET;
}

/**
  * @brief  Get the status of UART_SR register.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  status: Specifies the UART status type.
  *         This parameter can be one of the @ref uart_status_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_uart_get_status(uart_handle_t *hperh, uart_status_t status)
{
	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_UART_STATUS(status));

	if (READ_BIT(hperh->perh->SR, status))
		return SET;

	return RESET;
}


/**
  * @brief  Get the status of UART interrupt flag.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  flag: Specifies the UART interrupt flag.
  *         This parameter can be one of the @ref uart_flag_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_uart_get_flag_status(uart_handle_t *hperh, uart_flag_t flag)
{
	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_UART_IF(flag));

	if (READ_BIT(hperh->perh->RIF, flag))
		return SET;

	return RESET;
}

/**
  * @brief  Get the status of interrupt flag and interupt source.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  flag: Specifies the UART interrupt flag.
  *         This parameter can be one of the @ref uart_flag_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_uart_get_mask_flag_status(uart_handle_t *hperh, uart_flag_t flag)
{
	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_UART_IF(flag));

	if (READ_BIT(hperh->perh->IFM, flag))
		return SET;

	return RESET;
}

/**
  * @brief  Clear the UART interrupt flag.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  flag: Specifies the UART interrupt flag.
  *         This parameter can be one of the @ref uart_flag_t.
  * @retval None
  */
void ald_uart_clear_flag_status(uart_handle_t *hperh, uart_flag_t flag)
{
	assert_param(IS_UART_ALL(hperh->perh));
	assert_param(IS_UART_IF(flag));

	WRITE_REG(hperh->perh->ICR, flag);
	return;
}
/**
  * @}
  */

/** @defgroup UART_Public_Functions_Group4 Peripheral State and Errors functions
  *  @brief   UART State and Errors functions
  *
@verbatim
  ==============================================================================
                 ##### Peripheral State and Errors functions #####
  ==============================================================================
 [..]
   This subsection provides a set of functions allowing to return the State of
   UART communication process, return Peripheral Errors occurred during communication
   process
   (+) ald_uart_get_state() API can be helpful to check in run-time the state of the UART peripheral.
   (+) ald_uart_get_error() check in run-time errors that could be occurred during communication.

@endverbatim
  * @{
  */

/**
  * @brief  Returns the UART state.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval ALD state
  */
uart_state_t ald_uart_get_state(uart_handle_t *hperh)
{
	return hperh->state;
}

/**
  * @brief  Return the UART error code
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval UART Error Code
  */
uint32_t ald_uart_get_error(uart_handle_t *hperh)
{
	return hperh->err_code;
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* ALD_UART */

/**
  * @}
  */

/**
  * @}
  */
