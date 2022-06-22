/**
  *********************************************************************************
  *
  * @file    ald_usart.c
  * @brief   USART module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Synchronous Asynchronous Receiver Transmitter (USART) peripheral:
  *           + Initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
  *
  * @version V1.0
  * @date    25 Apr 2017
  * @author  AE Team
  * @note
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
  *
  *********************************************************************************
  * @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
    The USART ALD driver can be used as follows:

    (#) Declare a usart_handle_t handle structure.

    (#) Initialize the USART handle:
        (##) Enable the USARTx interface clock.
        (##) USART pins configuration:
            (+++) Enable the clock for the USART GPIOs.
            (+++) Configure the USART pins (TX as alternate function pull-up, RX as alternate function Input).
        (##) NVIC configuration if you need to use interrupt process (ald_usart_send_by_it()
             and ald_usart_recv_by_it() APIs):
            (+++) Configure the USARTx interrupt priority.
            (+++) Enable the NVIC USART IRQ handle.
        (##) DMA Configuration if you need to use DMA process (ald_usart_send_by_dma()
             and ald_usart_recv_by_dma() APIs):
            (+++) Declare a DMA handle structure for the Tx/Rx channel.
            (+++) Enable the DMAx interface clock.
            (+++) Configure the declared DMA handle structure with the required
                  Tx/Rx parameters.
            (+++) Configure the DMA Tx/Rx channel.
            (+++) Associate the initialized DMA handle to the USART DMA Tx/Rx handle.

    (#) Program the baud rate, word length, stop bit, parity, hardware
        flow control and mode(Receiver/Transmitter) in the hperh Init structure.

    (#) For the USART asynchronous mode, initialize the USART registers by calling
        the ald_usart_init() API.

    (#) For the USART Half duplex mode, initialize the USART registers by calling
        the ald_usart_half_duplex_init() API.

    (#) For the LIN mode, initialize the USART registers by calling the usart_lin_init() API.

    (#) For the Multi-Processor mode, initialize the USART registers by calling
        the ald_usart_multi_processor_init() API.

     [..]
       (@) The specific USART interrupts (Transmission complete interrupt,
            RXNE interrupt and Error Interrupts) will be managed using the function
            ald_usart_interrupt_config inside the transmit and receive process.

     [..]
        Three operation modes are available within this driver :

     *** Polling mode IO operation ***
     =================================
     [..] Asynchronous:
       (+) Send an amount of data in blocking mode using ald_usart_send()
       (+) Receive an amount of data in blocking mode using ald_usart_recv()

     [..] Synchronous:
       (+) Send an amount of data in blocking mode using ald_usart_send_sync()
       (+) Receive an amount of data in blocking mode using ald_usart_recv_sync()

     *** Interrupt mode IO operation ***
     ===================================
     [..] Asynchronous:
       (+) Send an amount of data in non blocking mode using ald_usart_send_by_it()
       (+) At transmission end of transfer hperh->tx_cplt_cbk() is executed and user can
            add his own code by customization of function pointer hperh->tx_cplt_cbk()
       (+) Receive an amount of data in non blocking mode using USART_recv_by_it()
       (+) At reception end of transfer hperh->rx_cplt_cbk() is executed and user can
            add his own code by customization of function pointer hperh->rx_cplt_cbk()
       (+) In case of transfer Error, hperh->error_cbk() function is executed and user can
            add his own code by customization of function pointer hperh->error_cbk()
     [..] Synchronous:
       (+) Send an amount of data in non blocking mode using ald_usart_send_by_it_sync()
       (+) At transmission end of transfer hperh->tx_cplt_cbk() is executed and user can
            add his own code by customization of function pointer hperh->tx_cplt_cbk()
       (+) Receive an amount of data in non blocking mode using USART_recv_by_it_sync()
       (+) At reception end of transfer hperh->rx_cplt_cbk() is executed and user can
            add his own code by customization of function pointer hperh->rx_cplt_cbk()
       (+) In case of transfer Error, hperh->error_cbk() function is executed and user can
            add his own code by customization of function pointer hperh->error_cbk()

     *** DMA mode IO operation ***
     ==============================
     [..] Asynchronous:
       (+) Send an amount of data in non blocking mode (DMA) using ald_usart_send_by_dma()
       (+) At transmission end of transfer hperh->tx_cplt_cbk() is executed and user can
            add his own code by customization of function pointer hperh->tx_cplt_cbk()
       (+) Receive an amount of data in non blocking mode (DMA) using ald_usart_recv_by_dma()
       (+) At reception end of transfer hperh->rx_cplt_cbk() is executed and user can
            add his own code by customization of function pointer hperh->rx_cplt_cbk()
       (+) In case of transfer Error, hperh->error_cbk()() function is executed and user can
            add his own code by customization of function pointer hperh->error_cbk()
     [..] Synchronous:
       (+) Send an amount of data in non blocking mode (DMA) using ald_usart_send_by_dma_sync()
       (+) At transmission end of transfer hperh->tx_cplt_cbk() is executed and user can
            add his own code by customization of function pointer hperh->tx_cplt_cbk()
       (+) Receive an amount of data in non blocking mode (DMA) using ald_usart_recv_by_dma_sync()
       (+) At reception end of transfer hperh->rx_cplt_cbk() is executed and user can
            add his own code by customization of function pointer hperh->rx_cplt_cbk()
       (+) In case of transfer Error, hperh->error_cbk()() function is executed and user can
            add his own code by customization of function pointer hperh->error_cbk()
     [..] Utilities:
       (+) Pause the DMA Transfer using ald_usart_dma_pause()
       (+) Resume the DMA Transfer using ald_usart_dma_resume()
       (+) Stop the DMA Transfer using ald_usart_dma_stop()

     *** USART ALD driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in USART ALD driver.

      (+) USART_ENABLE: Enable the USART peripheral
      (+) USART_DISABLE: Disable the USART peripheral
      (+) USART_RESET_HANDLE_STATE : Reset USART handle
      (+) USART_CLEAR_PEFLAG : Clear PE flag
      (+) USART_CLEAR_FEFLAG: Clear FE flag
      (+) USART_CLEAR_NEFLAG: Clear NE flag
      (+) USART_CLEAR_OREFLAG: Clear voerrun flag
      (+) USART_CLEAR_IDLEFLAG : Clear IDLE flag
      (+) USART_HWCONTROL_CTS_ENABLE: Enable CTS flow control
      (+) USART_HWCONTROL_CTS_DISABLE: Disable CTS flow control
      (+) USART_HWCONTROL_RTS_ENABLE: Enable RTS flow control
      (+) USART_HWCONTROL_RTS_DISABLE: Disable RTS flow control

     [..]
       (@) You can refer to the USART Library header file for more useful macros

    @endverbatim
  ******************************************************************************
  */

#include "ald_usart.h"
#include "ald_cmu.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup USART USART
  * @brief USART module driver
  * @{
  */
#ifdef ALD_USART

/** @defgroup USART_Private_Variables USART Private Variables
  * @{
  */
uint8_t __frame_mode = 0;
/**
  * @}
  */

/** @addtogroup USART_Private_Functions   USART Private Functions
  * @{
  */
static void usart_set_config (usart_handle_t *hperh);
static ald_status_t __usart_send_by_it(usart_handle_t *hperh);
static ald_status_t __usart_end_send_by_it(usart_handle_t *hperh);
static ald_status_t __usart_recv_by_it(usart_handle_t *hperh);
static ald_status_t __usart_recv_frame_cplt(usart_handle_t *hperh);
static ald_status_t __usart_recv_by_it_sync(usart_handle_t *hperh);
static ald_status_t __usart_send_recv_by_it_sync(usart_handle_t *hperh);
#ifdef ALD_DMA
static void usart_dma_send_cplt(void *arg);
static void usart_dma_recv_cplt(void *arg);
static void usart_dma_error(void *arg);
#endif
static ald_status_t usart_wait_flag(usart_handle_t *hperh, usart_flag_t flag, flag_status_t status, uint32_t timeout);
/**
  * @}
  */

/** @defgroup USART_Public_Functions USART Public Functions
  * @{
  */

/** @defgroup USART_Public_Functions_Group1 Initialization functions
  * @brief    Initialization and Configuration functions
  *
  * @verbatim
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the USARTx or the USARTy
    in asynchronous or synchronous mode.
      (+) For the asynchronous mode only these parameters can be configured:
        (++) Baud rate
        (++) Word length
        (++) Stop bit
        (++) Parity
        (++) Hardware flow control
        (++) Receiver/transmitter modes
    [..]
    The ald_usart_init(), ald_usart_half_duplex_init(), usart_lin_init(), ald_usart_multi_processor_init()
    and ald_usart_clock_init() APIs follow respectively the USART asynchronous, USART Half duplex,
    LIN, Multi-Processor and synchronous configuration procedures.

    @endverbatim
  * @{
  */

/*
  Additionnal remark: If the parity is enabled, then the MSB bit of the data written
                      in the data register is transmitted but is changed by the parity bit.
                      Depending on the frame length defined by the M bit (8-bits or 9-bits),
                      the possible USART frame formats are as listed in the following table:
    +-------------------------------------------------------------+
    |   M bit |  PCE bit  |            USART frame                 |
    |---------------------|---------------------------------------|
    |    0    |    0      |    | SB | 8 bit data | STB |          |
    |---------|-----------|---------------------------------------|
    |    0    |    1      |    | SB | 7 bit data | PB | STB |     |
    |---------|-----------|---------------------------------------|
    |    1    |    0      |    | SB | 9 bit data | STB |          |
    |---------|-----------|---------------------------------------|
    |    1    |    1      |    | SB | 8 bit data | PB | STB |     |
    +-------------------------------------------------------------+
*/


/**
  * @brief  Reset the USART peripheral.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval None
  */
void ald_usart_reset(usart_handle_t *hperh)
{
	assert_param(IS_USART(hperh->perh));

	hperh->state = USART_STATE_BUSY;
	USART_DISABLE(hperh);

	WRITE_REG(hperh->perh->CON0, 0x0);
	WRITE_REG(hperh->perh->CON1, 0x0);
	WRITE_REG(hperh->perh->CON2, 0x0);

	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_RESET;

	__UNLOCK(hperh);
	return;
}

/**
  * @brief  Initializes the USART mode according to the specified parameters in
  *         the usart_init_t and create the associated handle.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_init(usart_handle_t *hperh)
{
	assert_param(IS_USART(hperh->perh));
	assert_param(IS_USART_HARDWARE_FLOW_CONTROL(hperh->init.fctl));
	assert_param(IS_USART_WORD_LENGTH(hperh->init.word_length));

	ald_usart_reset(hperh);
	hperh->state = USART_STATE_BUSY;
	USART_DISABLE(hperh);
	usart_set_config(hperh);

	/* In asynchronous mode, the following bits must be kept cleared:
	 *   - LINEN and CLKEN bits in the USART_CR2 register,
	 *   - SCEN, HDSEL and IREN  bits in the USART_CR3 register.
	 */
	CLEAR_BIT(hperh->perh->CON1, USART_CON1_SCKEN_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_SMARTEN_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_HDPSEL_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_IREN_MSK);

	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_READY;
	USART_ENABLE(hperh);

	return OK;
}

/**
  * @brief  Initializes the half-duplex mode according to the specified
  *         parameters in the usart_init_t and create the associated handle.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_half_duplex_init(usart_handle_t *hperh)
{
	assert_param(IS_USART(hperh->perh));
	assert_param(IS_USART_WORD_LENGTH(hperh->init.word_length));

	ald_usart_reset(hperh);
	hperh->state = USART_STATE_BUSY;
	USART_DISABLE(hperh);
	usart_set_config(hperh);

	/* In half-duplex mode, the following bits must be kept cleared:
	 *   - LINEN and CLKEN bits in the USART_CR2 register,
	 *   - SCEN and IREN bits in the USART_CR3 register.*/
	CLEAR_BIT(hperh->perh->CON1, USART_CON1_SCKEN_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_SMARTEN_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_IREN_MSK);
	SET_BIT(hperh->perh->CON2, USART_CON2_HDPSEL_MSK);

	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_READY;
	USART_ENABLE(hperh);

	return OK;
}

/**
  * @brief  Initializes the Multi-Processor mode according to the specified
  *         parameters in the usart_init_t and create the associated handle.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  addr: USART node address
  * @param  wakeup: specifies the USART wakeup method.
  *         This parameter can be one of the following values:
  *            @arg USART_WAKEUP_IDLE: Wakeup by an idle line detection
  *            @arg USART_WAKEUP_ADDR: Wakeup by an address mark
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_multi_processor_init(usart_handle_t *hperh, uint8_t addr, usart_wakeup_t wakeup)
{
	assert_param(IS_USART(hperh->perh));
	assert_param(IS_USART_WAKEUP(wakeup));
	assert_param(IS_USART_ADDRESS(addr));
	assert_param(IS_USART_WORD_LENGTH(hperh->init.word_length));

	ald_usart_reset(hperh);
	hperh->state = USART_STATE_BUSY;
	USART_DISABLE(hperh);
	usart_set_config(hperh);

	/* In Multi-Processor mode, the following bits must be kept cleared:
	 *   - LINEN and CLKEN bits in the USART_CR2 register,
	 *   - SCEN, HDSEL and IREN  bits in the USART_CR3 register */
	CLEAR_BIT(hperh->perh->CON1, USART_CON1_SCKEN_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_SMARTEN_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_HDPSEL_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_IREN_MSK);
	MODIFY_REG(hperh->perh->CON1, USART_CON1_ADDR_MSK, addr << USART_CON1_ADDR_POSS);
	MODIFY_REG(hperh->perh->CON0, USART_CON0_WKMOD_MSK, wakeup << USART_CON0_WKMOD_POS);

	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_READY;
	USART_ENABLE(hperh);

	return OK;
}

/**
  * @brief  Initializes the synchronization mode according to the specified
  *         parameters in the usart_init_t and usart_clock_init_t.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  init: USART Clock Init Structure.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_clock_init(usart_handle_t *hperh, usart_clock_init_t *init)
{
	assert_param(IS_USART(hperh->perh));
	assert_param(IS_USART_WORD_LENGTH(hperh->init.word_length));

	ald_usart_reset(hperh);
	hperh->state = USART_STATE_BUSY;
	USART_DISABLE(hperh);
	usart_set_config(hperh);

	/* In Multi-Processor mode, the following bits must be kept cleared:
	 *   - LINEN and CLKEN bits in the USART_CR2 register,
	 *   - SCEN, HDSEL and IREN  bits in the USART_CR3 register */
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_SMARTEN_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_HDPSEL_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_IREN_MSK);
	MODIFY_REG(hperh->perh->CON1, USART_CON1_SCKEN_MSK, init->clk << USART_CON1_SCKEN_POS);
	MODIFY_REG(hperh->perh->CON1, USART_CON1_SCKPOL_MSK, init->polarity << USART_CON1_SCKPOL_POS);
	MODIFY_REG(hperh->perh->CON1, USART_CON1_SCKPHA_MSK, init->phase << USART_CON1_SCKPHA_POS);
	MODIFY_REG(hperh->perh->CON1, USART_CON1_LBCP_MSK, init->last_bit << USART_CON1_LBCP_POS);

	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_READY;
	USART_ENABLE(hperh);

	return OK;
}

/**
  * @}
  */

/** @defgroup USART_Public_Functions_Group2 IO operation functions
  * @brief USART Transmit and Receive functions
  * @{
  */

/** @defgroup USART_Public_Functions_Group2_1 Asynchronization IO operation functions
  * @brief Asynchronization IO operation functions
  *
  * @verbatim
  ==============================================================================
                      ##### IO operation functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the USART asynchronous
    and Half duplex data transfers.

    (#) There are two modes of transfer:
       (++) Blocking mode: The communication is performed in polling mode.
            The Status of all data processing is returned by the same function
            after finishing transfer.
       (++) Non blocking mode: The communication is performed using Interrupts
            or DMA, these APIs return the Status.
            The end of the data processing will be indicated through the
            dedicated USART IRQ when using Interrupt mode or the DMA IRQ when
            using DMA mode.
            The hperh->tx_cplt_cbk(), hperh->rx_cplt_cbk() user callbacks
            will be executed respectively at the end of the transmit or receive process.
            The hperh->error_cbk() user callback will be executed when
            a communication error is detected.

    (#) Blocking mode APIs are:
        (++) ald_usart_send()
        (++) ald_usart_recv()

    (#) Non Blocking mode APIs with Interrupt are:
        (++) ald_usart_send_by_it()
        (++) ald_usart_recv_by_it()
        (++) urart_irq_handle()

    (#) Non Blocking mode functions with DMA are:
        (++) ald_usart_send_by_dma()
        (++) ald_usart_recv_by_dma()
        (++) ald_usart_dma_pause()
        (++) ald_usart_dma_resume()
        (++) ald_usart_dma_stop()

    (#) A set of Transfer Complete Callbacks are provided in non blocking mode:
        (++) hperh->tx_cplt_cbk()
        (++) hperh->rx_cplt_cbk()
        (++) hperh->error_cbk()

    [..]
      (@) In the Half duplex communication, it is forbidden to run the transmit
          and receive process in parallel, the USART state USART_STATE_BUSY_TX_RX
          can't be useful.

    @endverbatim
  * @{
  */

/**
  * @brief  Sends an amount of data in blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_send(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
	if ((hperh->state != USART_STATE_READY) && (hperh->state != USART_STATE_BUSY_RX))
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return ERROR;

	__LOCK(hperh);
	hperh->err_code = USART_ERROR_NONE;
	SET_BIT(hperh->state, USART_STATE_TX_MASK);

	hperh->tx_size  = size;
	hperh->tx_count = size;

	while (hperh->tx_count-- > 0) {
		if (usart_wait_flag(hperh, USART_FLAG_TXE, SET, timeout) != OK) {
			__UNLOCK(hperh);
			hperh->state = USART_STATE_READY;
			return TIMEOUT;
		}

		if (hperh->init.word_length == USART_WORD_LENGTH_9B) {
			if (hperh->init.parity == USART_PARITY_NONE) {
				WRITE_REG(hperh->perh->DATA, (*(uint16_t *)buf & (uint16_t)0x01FF));
				buf += 2;
			}
			else {
				WRITE_REG(hperh->perh->DATA, *buf++);
			}
		}
		else {
			WRITE_REG(hperh->perh->DATA, *buf++);
		}
	}

	if (usart_wait_flag(hperh, USART_FLAG_TC, SET, timeout) != OK) {
		__UNLOCK(hperh);
		hperh->state = USART_STATE_READY;
		return TIMEOUT;
	}

	CLEAR_BIT(hperh->state, USART_STATE_TX_MASK);
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Receives an amount of data in blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_recv(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
	if ((hperh->state != USART_STATE_READY) && (hperh->state != USART_STATE_BUSY_TX))
		return BUSY;

	if ((buf == NULL ) || (size == 0))
		return  ERROR;

	__LOCK(hperh);
	hperh->err_code = USART_ERROR_NONE;
	SET_BIT(hperh->state, USART_STATE_RX_MASK);

	hperh->rx_size  = size;
	hperh->rx_count = size;

	while (hperh->rx_count-- > 0) {
		if (usart_wait_flag(hperh, USART_FLAG_RXNE, SET, timeout) != OK) {
			__UNLOCK(hperh);
			hperh->state = USART_STATE_READY;
			return TIMEOUT;
		}

		if (hperh->init.word_length == USART_WORD_LENGTH_9B) {
			if (hperh->init.parity == USART_PARITY_NONE) {
				*(uint16_t *)buf = (uint16_t)(hperh->perh->DATA & 0x1FF);
				buf += 2;
			}
			else {
				*buf = (uint8_t)(hperh->perh->DATA & 0xFF);
				buf += 1;
			}
		}
		else {
			if (hperh->init.parity == USART_PARITY_NONE)
				*buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);
			else
				*buf++ = (uint8_t)(hperh->perh->DATA & 0x7F);
		}
	}

	CLEAR_BIT(hperh->state, USART_STATE_RX_MASK);
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_send_by_it(usart_handle_t *hperh, uint8_t *buf, uint16_t size)
{
	if ((hperh->state != USART_STATE_READY) && (hperh->state != USART_STATE_BUSY_RX))
		return BUSY;

	if ((buf == NULL ) || (size == 0))
		return ERROR;

	__LOCK(hperh);
	SET_BIT(hperh->state, USART_STATE_TX_MASK);

	hperh->tx_buf   = buf;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->err_code = USART_ERROR_NONE;

	__UNLOCK(hperh);
	ald_usart_interrupt_config(hperh, USART_IT_TXE, ENABLE);

	return OK;
}

/**
  * @brief  Receives an amount of data in non blocking mode
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_recv_by_it(usart_handle_t *hperh, uint8_t *buf, uint16_t size)
{
	if ((hperh->state != USART_STATE_READY) && (hperh->state != USART_STATE_BUSY_TX))
		return BUSY;

	if ((buf == NULL ) || (size == 0))
		return ERROR;

	__LOCK(hperh);
	SET_BIT(hperh->state, USART_STATE_RX_MASK);

	hperh->rx_buf   = buf;
	hperh->rx_size  = size;
	hperh->rx_count = size;
	hperh->err_code = USART_ERROR_NONE;

	__UNLOCK(hperh);
	ald_usart_interrupt_config(hperh, USART_IT_PE, ENABLE);
	ald_usart_interrupt_config(hperh, USART_IT_ERR, ENABLE);
	ald_usart_interrupt_config(hperh, USART_IT_RXNE, ENABLE);

	return OK;
}

/**
  * @brief  Receives an frame in interrupt mode
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Maximum amount of data to be received
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_recv_frame_by_it(usart_handle_t *hperh, uint8_t *buf, uint16_t size)
{
	if ((hperh->state != USART_STATE_READY) && (hperh->state != USART_STATE_BUSY_TX))
		return BUSY;

	if ((buf == NULL ) || (size == 0))
		return ERROR;

	__LOCK(hperh);
	SET_BIT(hperh->state, USART_STATE_RX_MASK);

	hperh->rx_buf   = buf;
	hperh->rx_size  = size;
	hperh->rx_count = size;
	hperh->err_code = USART_ERROR_NONE;

	__UNLOCK(hperh);
	ald_usart_interrupt_config(hperh, USART_IT_PE, ENABLE);
	ald_usart_interrupt_config(hperh, USART_IT_ERR, ENABLE);
	ald_usart_interrupt_config(hperh, USART_IT_RXNE, ENABLE);
	__frame_mode = 1;

	return OK;
}

#ifdef ALD_DMA
/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as USART transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_send_by_dma(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
	if ((hperh->state != USART_STATE_READY) && (hperh->state != USART_STATE_BUSY_RX))
		return BUSY;

	if ((buf == NULL ) || (size == 0))
		return ERROR;

	__LOCK(hperh);
	SET_BIT(hperh->state, USART_STATE_TX_MASK);

	hperh->tx_buf   = buf;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->err_code = USART_ERROR_NONE;

	if (hperh->hdmatx.perh == NULL)
		hperh->hdmatx.perh = DMA0;

	/* Configure callback function */
	hperh->hdmatx.cplt_cbk = usart_dma_send_cplt;
	hperh->hdmatx.cplt_arg = (void *)hperh;
	hperh->hdmatx.err_cbk  = usart_dma_error;
	hperh->hdmatx.err_arg  = (void *)hperh;

	/* Configure USART DMA transmit */
	ald_dma_config_struct(&hperh->hdmatx.config);
	hperh->hdmatx.config.src     = (void *)buf;
	hperh->hdmatx.config.dst     = (void *)&hperh->perh->DATA;
	hperh->hdmatx.config.size    = size;
	hperh->hdmatx.config.src_inc = DMA_DATA_INC_BYTE;
	hperh->hdmatx.config.dst_inc = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel    = hperh->perh == USART0 ? DMA_MSEL_USART0 : DMA_MSEL_USART1;
	hperh->hdmatx.config.msigsel = DMA_MSIGSEL_USART_TXEMPTY;
	hperh->hdmatx.config.channel = channel;

	if ((hperh->init.word_length == USART_WORD_LENGTH_9B)
			&& (hperh->init.parity == USART_PARITY_NONE)) {
		hperh->hdmatx.config.src_inc    = DMA_DATA_INC_HALFWORD;
		hperh->hdmatx.config.data_width = DMA_DATA_SIZE_HALFWORD;
	}

	ald_dma_config_basic(&hperh->hdmatx);

	__UNLOCK(hperh);
	ald_usart_clear_flag_status(hperh, USART_FLAG_TC);
	SET_BIT(hperh->perh->CON2, USART_CON2_TXDMAEN_MSK);

	return OK;
}

/**
  * @brief  Receives an amount of data in non blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  channel: DMA channel as USART receive
  * @note   When the USART parity is enabled (PCE = 1), the received data contain
  *         the parity bit (MSB position)
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_recv_by_dma(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
	if ((hperh->state != USART_STATE_READY) && (hperh->state != USART_STATE_BUSY_TX))
		return BUSY;

	if ((buf == NULL ) || (size == 0))
		return ERROR;

	__LOCK(hperh);
	SET_BIT(hperh->state, USART_STATE_RX_MASK);

	hperh->rx_buf   = buf;
	hperh->rx_size  = size;
	hperh->err_code = USART_ERROR_NONE;

	if (hperh->hdmarx.perh == NULL)
		hperh->hdmarx.perh = DMA0;

	/* Configure callback function */
	hperh->hdmarx.cplt_cbk = usart_dma_recv_cplt;
	hperh->hdmarx.cplt_arg = (void *)hperh;
	hperh->hdmarx.err_cbk  = usart_dma_error;
	hperh->hdmarx.err_arg  = (void *)hperh;

	/* Configure DMA Receive */
	ald_dma_config_struct(&hperh->hdmarx.config);
	hperh->hdmarx.config.src     = (void *)&hperh->perh->DATA;
	hperh->hdmarx.config.dst     = (void *)buf;
	hperh->hdmarx.config.size    = size;
	hperh->hdmarx.config.src_inc = DMA_DATA_INC_NONE;
	hperh->hdmarx.config.dst_inc = DMA_DATA_INC_BYTE;
	hperh->hdmarx.config.msel    = hperh->perh == USART0 ? DMA_MSEL_USART0 : DMA_MSEL_USART1;
	hperh->hdmarx.config.msigsel = DMA_MSIGSEL_USART_RNR;
	hperh->hdmarx.config.channel = channel;

	if ((hperh->init.word_length == USART_WORD_LENGTH_9B)
			&& (hperh->init.parity == USART_PARITY_NONE)) {
		hperh->hdmarx.config.dst_inc    = DMA_DATA_INC_HALFWORD;
		hperh->hdmarx.config.data_width = DMA_DATA_SIZE_HALFWORD;
	}

	ald_dma_config_basic(&hperh->hdmarx);

	__UNLOCK(hperh);
	SET_BIT(hperh->perh->CON2, USART_CON2_RXDMAEN_MSK);

	return OK;
}
#endif
/**
  * @}
  */

/** @defgroup USART_Public_Functions_Group2_2 Synchronization IO operation functions
  *  @brief   Synchronization IO operation functions
  *
  * @verbatim
  ==============================================================================
                         ##### IO operation functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the USART synchronous
    data transfers.

  [..]
    The USART supports master mode only: it cannot receive or send data related to an input
    clock (SCLK is always an output).

    (#) There are two modes of transfer:
        (++) Blocking mode: The communication is performed in polling mode.
             The Status of all data processing is returned by the same function
             after finishing transfer.
        (++) No-Blocking mode: The communication is performed using Interrupts
             or DMA, These API's return the Status.
             The end of the data processing will be indicated through the
             dedicated USART IRQ when using Interrupt mode or the DMA IRQ when
             using DMA mode.
             The hperh->tx_cplt_cbk(), hperh->rx_cplt_cbk() and hperh->tx_rx_cplt_cbk()
             user callbacks will be executed respectively at the end of the transmit
	     or Receive process. The hperh->error_cbk() user callback will be
	     executed when a communication error is detected

    (#) Blocking mode APIs are :
        (++) ald_usart_send_sync() in simplex mode
        (++) ald_usart_recv_sync() in full duplex receive only
        (++) ald_usart_send_recv_sync() in full duplex mode

    (#) Non Blocking mode APIs with Interrupt are :
        (++) ald_usart_send_by_it_sync()in simplex mode
        (++) ald_usart_recv_by_it_sync() in full duplex receive only
        (++) ald_usart_send_recv_by_it_sync() in full duplex mode
        (++) ald_usart_irq_handler()

    (#) Non Blocking mode functions with DMA are :
        (++) ald_usart_send_by_dma_sync()in simplex mode
        (++) ald_usart_recv_by_dma_sync() in full duplex receive only
        (++) usart_send_recv_by_dma_symc() in full duplex mode
        (++) ald_usart_dma_pause()
        (++) ald_usart_dma_resume()
        (++) ald_usart_dma_stop()

    (#) A set of Transfer Complete Callbacks are provided in non Blocking mode:
        (++) hperh->tx_cplt_cbk()
        (++) hperh->rx_cplt_cbk()
        (++) hperh->tx_rx_cplt_cbk()
        (++) hperh->error_cbk()

    @endverbatim
  * @{
  */

/**
  * @brief  Simplex Send an amount of data in blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_send_sync(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
	if (hperh->state != USART_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	__LOCK(hperh);

	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_BUSY_TX;

	while (hperh->tx_count-- > 0) {
		if (usart_wait_flag(hperh, USART_FLAG_TXE, SET, timeout) != OK) {
			__UNLOCK(hperh);
			hperh->state = USART_STATE_READY;
			return TIMEOUT;
		}

		if ((hperh->init.word_length == USART_WORD_LENGTH_9B) && (hperh->init.parity == USART_PARITY_NONE)) {
			WRITE_REG(hperh->perh->DATA, (*(uint16_t *)buf & 0x1FF));
			buf += 2;
		}
		else {
			WRITE_REG(hperh->perh->DATA, *buf++);
		}
    	}

	if (usart_wait_flag(hperh, USART_FLAG_TC, SET, timeout) != OK) {
		__UNLOCK(hperh);
		hperh->state = USART_STATE_READY;
		return TIMEOUT;
	}

	hperh->state = USART_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Full-Duplex Receive an amount of data in blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_recv_sync(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
	if (hperh->state != USART_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	__LOCK(hperh);

	hperh->rx_size  = size;
	hperh->rx_count = size;
	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_BUSY_RX;

	while (hperh->rx_count-- > 0) {
		if (usart_wait_flag(hperh, USART_FLAG_TXE, SET, timeout) != OK) {
			__UNLOCK(hperh);
			hperh->state = USART_STATE_READY;
			return TIMEOUT;
		}

		if (hperh->init.word_length == USART_WORD_LENGTH_9B) {
			WRITE_REG(hperh->perh->DATA, (DUMMY_DATA & 0x1FF));

			if (usart_wait_flag(hperh, USART_FLAG_RXNE, SET, timeout) != OK) {
				__UNLOCK(hperh);
				hperh->state = USART_STATE_READY;
				return TIMEOUT;
			}

			if (hperh->init.parity == USART_PARITY_NONE) {
				*(uint16_t *)buf = (uint16_t)(hperh->perh->DATA & 0x1FF);
				buf += 2;
			}
			else {
				*buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);
			}
		}
		else {
			WRITE_REG(hperh->perh->DATA, (DUMMY_DATA & 0xFF));

			if (usart_wait_flag(hperh, USART_FLAG_RXNE, SET, timeout) != OK) {
				__UNLOCK(hperh);
				hperh->state = USART_STATE_READY;
				return TIMEOUT;
			}

			if (hperh->init.parity == USART_PARITY_NONE)
				*buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);
			else
				*buf++ = (uint8_t)(hperh->perh->DATA & 0x7F);
		}
	}

	hperh->state = USART_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Full-Duplex Send receive an amount of data in full-duplex mode (blocking mode).
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  tx_buf: Pointer to data transmitted buffer
  * @param  rx_buf: Pointer to data received buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_send_recv_sync(usart_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size, uint32_t timeout)
{
	if (hperh->state != USART_STATE_READY)
		return BUSY;

	if ((tx_buf == NULL) || (rx_buf == NULL) || (size == 0))
		return  ERROR;

	__LOCK(hperh);

	hperh->rx_size  = size;
	hperh->rx_count = size;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_BUSY_RX;

	while (hperh->tx_count-- > 0) {
		--hperh->rx_count;

		if (usart_wait_flag(hperh, USART_FLAG_TXE, SET, timeout) != OK) {
			__UNLOCK(hperh);
			hperh->state = USART_STATE_READY;
			return TIMEOUT;
		}

		if (hperh->init.word_length == USART_WORD_LENGTH_9B) {
			if (hperh->init.parity == USART_PARITY_NONE) {
				WRITE_REG(hperh->perh->DATA, (*(uint16_t *)tx_buf & 0x1FF));
				tx_buf += 2;
			}
			else {
				WRITE_REG(hperh->perh->DATA, *tx_buf++);
			}

			if (usart_wait_flag(hperh, USART_FLAG_RXNE, SET, timeout) != OK) {
				__UNLOCK(hperh);
				hperh->state = USART_STATE_READY;
				return TIMEOUT;
			}

			if (hperh->init.parity == USART_PARITY_NONE) {
				*(uint16_t *)rx_buf = (uint16_t)(hperh->perh->DATA & 0x1FF);
				rx_buf += 2;
			}
			else {
				*rx_buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);
			}
		}
		else {
			WRITE_REG(hperh->perh->DATA, *tx_buf++);

			if (usart_wait_flag(hperh, USART_FLAG_RXNE, SET, timeout) != OK) {
				__UNLOCK(hperh);
				hperh->state = USART_STATE_READY;
				return TIMEOUT;
			}

			if (hperh->init.parity == USART_PARITY_NONE)
				*rx_buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);
			else
				*rx_buf++ = (uint8_t)(hperh->perh->DATA & 0x7F);
		}
	}

	hperh->state = USART_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Simplex Send an amount of data in non-blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  * @note   The USART errors are not managed to avoid the overrun error.
  */
ald_status_t ald_usart_send_by_it_sync(usart_handle_t *hperh, uint8_t *buf, uint16_t size)
{
	if (hperh->state != USART_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return ERROR;

	__LOCK(hperh);

	hperh->tx_buf   = buf;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_BUSY_TX;

	/* The USART Error Interrupts: (Frame error, Noise error, Overrun error)
	 * are not managed by the USART transmit process to avoid the overrun interrupt
	 * when the USART mode is configured for transmit and receive "USART_MODE_TX_RX"
	 * to benefit for the frame error and noise interrupts the USART mode should be
	 * configured only for transmit "USART_MODE_TX"
	 * The __ALD_USART_ENABLE_IT(hperh, USART_IT_ERR) can be used to enable the Frame error,
	 * Noise error interrupt
	 */

	__UNLOCK(hperh);
	ald_usart_interrupt_config(hperh, USART_IT_TXE, ENABLE);

	return OK;
}

/**
  * @brief  Simplex Receive an amount of data in non-blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_recv_by_it_sync(usart_handle_t *hperh, uint8_t *buf, uint16_t size)
{
	if (hperh->state != USART_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return ERROR;

	__LOCK(hperh);

	hperh->rx_buf   = buf;
	hperh->rx_size  = size;
	hperh->rx_count = size;
	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_BUSY_RX;

	__UNLOCK(hperh);
	ald_usart_interrupt_config(hperh, USART_IT_RXNE, ENABLE);
	ald_usart_interrupt_config(hperh, USART_IT_PE, ENABLE);
	ald_usart_interrupt_config(hperh, USART_IT_ERR, ENABLE);

	WRITE_REG(hperh->perh->DATA, (DUMMY_DATA & (uint16_t)0x01FF));
	return OK;
}

/**
  * @brief  Full-Duplex Send receive an amount of data in full-duplex mode (non-blocking).
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  tx_buf: Pointer to data transmitted buffer
  * @param  rx_buf: Pointer to data received buffer
  * @param  size: Amount of data to be received
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_send_recv_by_it_sync(usart_handle_t *hperh, uint8_t *tx_buf, uint8_t *rx_buf,  uint16_t size)
{
	if (hperh->state != USART_STATE_READY)
		return BUSY;

	if ((tx_buf == NULL) || (rx_buf == NULL) || (size == 0))
		return ERROR;

	__LOCK(hperh);

	hperh->rx_buf   = rx_buf;
	hperh->rx_size  = size;
	hperh->rx_count = size;
	hperh->tx_buf   = tx_buf;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_BUSY_TX_RX;

	__UNLOCK(hperh);
	ald_usart_interrupt_config(hperh, USART_IT_RXNE, ENABLE);
	ald_usart_interrupt_config(hperh, USART_IT_PE, ENABLE);
	ald_usart_interrupt_config(hperh, USART_IT_ERR, ENABLE);
	ald_usart_interrupt_config(hperh, USART_IT_TXE, ENABLE);

	return OK;
}

#ifdef ALD_DMA
/**
  * @brief  Simplex Send an amount of data in non-blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as USART transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_send_by_dma_sync(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
	if (hperh->state != USART_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return ERROR;

	__LOCK(hperh);

	hperh->tx_buf   = buf;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_BUSY_TX;

	if (hperh->hdmatx.perh == NULL)
		hperh->hdmatx.perh = DMA0;

	/* Configure callback function */
	hperh->hdmatx.cplt_cbk = usart_dma_send_cplt;
	hperh->hdmatx.cplt_arg = (void *)hperh;
	hperh->hdmatx.err_cbk  = usart_dma_error;
	hperh->hdmatx.err_arg  = (void *)hperh;

	/* Configure DMA transmit */
	ald_dma_config_struct(&hperh->hdmatx.config);
	hperh->hdmatx.config.src     = (void *)buf;
	hperh->hdmatx.config.dst     = (void *)&hperh->perh->DATA;
	hperh->hdmatx.config.size    = size;
	hperh->hdmatx.config.src_inc = DMA_DATA_INC_BYTE;
	hperh->hdmatx.config.dst_inc = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel    = hperh->perh == USART0 ? DMA_MSEL_USART0 : DMA_MSEL_USART1;
	hperh->hdmatx.config.msigsel = DMA_MSIGSEL_USART_TXEMPTY;
	hperh->hdmatx.config.channel = channel;

	if ((hperh->init.word_length == USART_WORD_LENGTH_9B)
			&& (hperh->init.parity == USART_PARITY_NONE)) {
		hperh->hdmatx.config.src_inc    = DMA_DATA_INC_HALFWORD;
		hperh->hdmatx.config.data_width = DMA_DATA_SIZE_HALFWORD;
	}

	ald_dma_config_basic(&hperh->hdmatx);

	__UNLOCK(hperh);
	ald_usart_clear_flag_status(hperh, USART_FLAG_TC);
	SET_BIT(hperh->perh->CON2, USART_CON2_TXDMAEN_MSK);

	return OK;
}

/**
  * @brief  Full-Duplex Receive an amount of data in non-blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  tx_channel: DMA channel as USART transmit
  * @param  rx_channel: DMA channel as USART receive
  * @retval Status, see @ref ald_status_t.
  * @note   The USART DMA transmit channel must be configured in order to generate the clock for the slave.
  * @note   When the USART parity is enabled (PCE = 1) the data received contain the parity bit.
  */
ald_status_t ald_usart_recv_by_dma_sync(usart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t tx_channel, uint8_t rx_channel)
{
	if (hperh->state != USART_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return ERROR;

	__LOCK(hperh);

	hperh->rx_buf   = buf;
	hperh->rx_size  = size;
	hperh->tx_buf   = buf;
	hperh->tx_size  = size;
	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_BUSY_RX;

	if (hperh->hdmatx.perh == NULL)
		hperh->hdmatx.perh = DMA0;
	if (hperh->hdmarx.perh == NULL)
		hperh->hdmarx.perh = DMA0;

	/* Configure DMA callback function */
	hperh->hdmarx.cplt_cbk = usart_dma_recv_cplt;
	hperh->hdmarx.cplt_arg = (void *)hperh;
	hperh->hdmarx.err_cbk  = usart_dma_error;
	hperh->hdmarx.err_arg  = (void *)hperh;

	/* Configure DMA receive*/
	ald_dma_config_struct(&hperh->hdmarx.config);
	hperh->hdmarx.config.src     = (void *)&hperh->perh->DATA;
	hperh->hdmarx.config.dst     = (void *)buf;
	hperh->hdmarx.config.size    = size;
	hperh->hdmarx.config.src_inc = DMA_DATA_INC_NONE;
	hperh->hdmarx.config.dst_inc = DMA_DATA_INC_BYTE;
	hperh->hdmarx.config.msel    = hperh->perh == USART0 ? DMA_MSEL_USART0 : DMA_MSEL_USART1;
	hperh->hdmarx.config.msigsel = DMA_MSIGSEL_USART_RNR;
	hperh->hdmarx.config.channel = rx_channel;

	if ((hperh->init.word_length == USART_WORD_LENGTH_9B)
			&& (hperh->init.parity == USART_PARITY_NONE)) {
		hperh->hdmarx.config.dst_inc    = DMA_DATA_INC_HALFWORD;
		hperh->hdmarx.config.data_width = DMA_DATA_SIZE_HALFWORD;
	}

	ald_dma_config_basic(&hperh->hdmarx);

	/* Enable the USART transmit DMA channel: the transmit channel is used in order
	 * to generate in the non-blocking mode the clock to the slave device,
	 * this mode isn't a simplex receive mode but a full-duplex receive one
	 */
	ald_dma_config_struct(&hperh->hdmatx.config);
	hperh->hdmatx.config.src     = (void *)buf;
	hperh->hdmatx.config.dst     = (void *)&hperh->perh->DATA;
	hperh->hdmatx.config.size    = size;
	hperh->hdmatx.config.src_inc = DMA_DATA_INC_BYTE;
	hperh->hdmatx.config.dst_inc = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel    = hperh->perh == USART0 ? DMA_MSEL_USART0 : DMA_MSEL_USART1;
	hperh->hdmatx.config.msigsel = DMA_MSIGSEL_USART_TXEMPTY;
	hperh->hdmatx.config.channel = tx_channel;

	if ((hperh->init.word_length == USART_WORD_LENGTH_9B)
			&& (hperh->init.parity == USART_PARITY_NONE)) {
		hperh->hdmatx.config.src_inc    = DMA_DATA_INC_HALFWORD;
		hperh->hdmatx.config.data_width = DMA_DATA_SIZE_HALFWORD;
	}

	ald_dma_config_basic(&hperh->hdmatx);

	USART_CLEAR_OREFLAG(hperh);
	__UNLOCK(hperh);
	SET_BIT(hperh->perh->CON2, USART_CON2_RXDMAEN_MSK);
	SET_BIT(hperh->perh->CON2, USART_CON2_TXDMAEN_MSK);

	return OK;
}

/**
  * @brief  Full-Duplex Transmit Receive an amount of data in non-blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  tx_buf: Pointer to data transmitted buffer
  * @param  rx_buf: Pointer to data received buffer
  * @param  size: Amount of data to be received
  * @param  tx_channel: DMA channel as USART transmit
  * @param  rx_channel: DMA channel as USART receive
  * @note   When the USART parity is enabled (PCE = 1) the data received contain the parity bit.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_send_recv_by_dma_sync(usart_handle_t *hperh, uint8_t *tx_buf,
                    uint8_t *rx_buf, uint16_t size, uint8_t tx_channel, uint8_t rx_channel)
{
	if (hperh->state != USART_STATE_READY)
		return BUSY;

	if ((tx_buf == NULL) || (rx_buf == NULL) || (size == 0))
		return ERROR;

	__LOCK(hperh);

	hperh->rx_buf   = rx_buf;
	hperh->rx_size  = size;
	hperh->tx_buf   = tx_buf;
	hperh->tx_size  = size;
	hperh->err_code = USART_ERROR_NONE;
	hperh->state    = USART_STATE_BUSY_TX_RX;

	if (hperh->hdmatx.perh == NULL)
		hperh->hdmatx.perh = DMA0;
	if (hperh->hdmarx.perh == NULL)
		hperh->hdmarx.perh = DMA0;

	/* Configure DMA callback function */
	hperh->hdmarx.cplt_cbk = usart_dma_recv_cplt;
	hperh->hdmarx.cplt_arg = (void *)hperh;
	hperh->hdmatx.cplt_cbk = usart_dma_send_cplt;
	hperh->hdmatx.cplt_arg = (void *)hperh;
	hperh->hdmatx.err_cbk  = usart_dma_error;
	hperh->hdmatx.err_arg  = (void *)hperh;
	hperh->hdmarx.err_cbk  = usart_dma_error;
	hperh->hdmarx.err_arg  = (void *)hperh;

	/* Configure DMA receive */
	ald_dma_config_struct(&hperh->hdmarx.config);
	hperh->hdmarx.config.src     = (void *)&hperh->perh->DATA;
	hperh->hdmarx.config.dst     = (void *)rx_buf;
	hperh->hdmarx.config.size    = size;
	hperh->hdmarx.config.src_inc = DMA_DATA_INC_NONE;
	hperh->hdmarx.config.dst_inc = DMA_DATA_INC_BYTE;
	hperh->hdmarx.config.msel    = hperh->perh == USART0 ? DMA_MSEL_USART0 : DMA_MSEL_USART1;
	hperh->hdmarx.config.msigsel = DMA_MSIGSEL_USART_RNR;
	hperh->hdmarx.config.channel = rx_channel;

	if ((hperh->init.word_length == USART_WORD_LENGTH_9B)
			&& (hperh->init.parity == USART_PARITY_NONE)) {
		hperh->hdmarx.config.dst_inc    = DMA_DATA_INC_HALFWORD;
		hperh->hdmarx.config.data_width = DMA_DATA_SIZE_HALFWORD;
	}

	ald_dma_config_basic(&hperh->hdmarx);

	/* Configure DMA transmit*/
	ald_dma_config_struct(&hperh->hdmatx.config);
	hperh->hdmatx.config.src     = (void *)tx_buf;
	hperh->hdmatx.config.dst     = (void *)&hperh->perh->DATA;
	hperh->hdmatx.config.size    = size;
	hperh->hdmatx.config.src_inc = DMA_DATA_INC_BYTE;
	hperh->hdmatx.config.dst_inc = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel    = hperh->perh == USART0 ? DMA_MSEL_USART0 : DMA_MSEL_USART1;
	hperh->hdmatx.config.msigsel = DMA_MSIGSEL_USART_TXEMPTY;
	hperh->hdmatx.config.channel = tx_channel;

	if ((hperh->init.word_length == USART_WORD_LENGTH_9B)
			&& (hperh->init.parity == USART_PARITY_NONE)) {
		hperh->hdmatx.config.src_inc    = DMA_DATA_INC_HALFWORD;
		hperh->hdmatx.config.data_width = DMA_DATA_SIZE_HALFWORD;
	}

	ald_dma_config_basic(&hperh->hdmatx);

	ald_usart_clear_flag_status(hperh, USART_FLAG_TC);
	USART_CLEAR_OREFLAG(hperh);
	__UNLOCK(hperh);
	SET_BIT(hperh->perh->CON2, USART_CON2_RXDMAEN_MSK);
	SET_BIT(hperh->perh->CON2, USART_CON2_TXDMAEN_MSK);

	return OK;
}
#endif
/**
  * @}
  */

/** @defgroup USART_Public_Functions_Group2_3 Utilities functions
  * @brief    Utilities functions
  * @{
  */
#ifdef ALD_DMA
/**
  * @brief  Pauses the DMA Transfer.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_dma_pause(usart_handle_t *hperh)
{
	__LOCK(hperh);

	if (hperh->state == USART_STATE_BUSY_TX) {
		CLEAR_BIT(hperh->perh->CON2, USART_CON2_TXDMAEN_MSK);
	}
	else if (hperh->state == USART_STATE_BUSY_RX) {
		CLEAR_BIT(hperh->perh->CON2, USART_CON2_RXDMAEN_MSK);
	}
	else if (hperh->state == USART_STATE_BUSY_TX_RX) {
		CLEAR_BIT(hperh->perh->CON2, USART_CON2_TXDMAEN_MSK);
		CLEAR_BIT(hperh->perh->CON2, USART_CON2_RXDMAEN_MSK);
	}
	else {
		__UNLOCK(hperh);
		return ERROR;
	}

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Resumes the DMA Transfer.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_dma_resume(usart_handle_t *hperh)
{
	__LOCK(hperh);

	if (hperh->state == USART_STATE_BUSY_TX) {
		SET_BIT(hperh->perh->CON2, USART_CON2_TXDMAEN_MSK);
	}
	else if (hperh->state == USART_STATE_BUSY_RX) {
		USART_CLEAR_OREFLAG(hperh);
		SET_BIT(hperh->perh->CON2, USART_CON2_RXDMAEN_MSK);
	}
	else if (hperh->state == USART_STATE_BUSY_TX_RX) {
		USART_CLEAR_OREFLAG(hperh);
		SET_BIT(hperh->perh->CON2, USART_CON2_TXDMAEN_MSK);
		SET_BIT(hperh->perh->CON2, USART_CON2_RXDMAEN_MSK);
	}
	else {
		__UNLOCK(hperh);
		return ERROR;
	}

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Stops the DMA Transfer.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_dma_stop(usart_handle_t *hperh)
{
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_TXDMAEN_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_RXDMAEN_MSK);

	hperh->state = USART_STATE_READY;
	return OK;
}
#endif
/**
  * @brief  This function handles USART interrupt request.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval None
  */
void ald_usart_irq_handler(usart_handle_t *hperh)
{
	uint32_t flag;
	uint32_t source;

	/* Handle parity error */
	flag   = ald_usart_get_flag_status(hperh, USART_FLAG_PE);
	source = ald_usart_get_it_status(hperh, USART_IT_PE);
	if ((flag != RESET) && (source != RESET))
		hperh->err_code |= USART_ERROR_PE;

	/* Handle frame error */
	flag   = ald_usart_get_flag_status(hperh, USART_FLAG_FE);
	source = ald_usart_get_it_status(hperh, USART_IT_ERR);
	if ((flag != RESET) && (source != RESET))
		hperh->err_code |= USART_ERROR_FE;

	/* Handle noise error */
	flag = ald_usart_get_flag_status(hperh, USART_FLAG_NE);
	if ((flag != RESET) && (source != RESET))
		hperh->err_code |= USART_ERROR_NE;

	/* Handle overrun error */
	flag = ald_usart_get_flag_status(hperh, USART_FLAG_ORE);
	if ((flag != RESET) && (source != RESET))
		hperh->err_code |= USART_ERROR_ORE;

	/* Handle idle error */
	flag   = ald_usart_get_flag_status(hperh, USART_FLAG_IDLE);
	source = ald_usart_get_it_status(hperh, USART_IT_IDLE);
	if ((flag != RESET) && (source != RESET))
		__usart_recv_frame_cplt(hperh);

	/* Handle asynchronous */
	if (READ_BIT(hperh->perh->CON1, USART_CON1_SCKEN_MSK) == 0) {
		/* Receiver */
		flag   = ald_usart_get_flag_status(hperh, USART_FLAG_RXNE);
		source = ald_usart_get_it_status(hperh, USART_IT_RXNE);
		if ((flag != RESET) && (source != RESET))
			__usart_recv_by_it(hperh);

		/* Transmitter */
		flag   = ald_usart_get_flag_status(hperh, USART_FLAG_TXE);
		source = ald_usart_get_it_status(hperh, USART_IT_TXE);
		if ((flag != RESET) && (source != RESET))
			__usart_send_by_it(hperh);
	}
	else {	/* Handle synchronous */
		/* Receiver */
		flag   = ald_usart_get_flag_status(hperh, USART_FLAG_RXNE);
		source = ald_usart_get_it_status(hperh, USART_IT_RXNE);
		if ((flag != RESET) && (source != RESET)) {
			if (hperh->state == USART_STATE_BUSY_RX)
				__usart_recv_by_it_sync(hperh);
			else
				__usart_send_recv_by_it_sync(hperh);
		}

		/* Transmitter */
		flag   = ald_usart_get_flag_status(hperh, USART_FLAG_TXE);
		source = ald_usart_get_it_status(hperh, USART_IT_TXE);
		if ((flag != RESET) && (source != RESET)) {
			if (hperh->state == USART_STATE_BUSY_TX)
				__usart_send_by_it(hperh);
			else
				__usart_send_recv_by_it_sync(hperh);
		}
	}

	/* Handle transmitter end */
	flag   = ald_usart_get_flag_status(hperh, USART_FLAG_TC);
	source = ald_usart_get_it_status(hperh, USART_IT_TC);
	if ((flag != RESET) && (source != RESET))
		__usart_end_send_by_it(hperh);

	/* Handle error */
	if (hperh->err_code != USART_ERROR_NONE) {
		USART_CLEAR_PEFLAG(hperh);
		hperh->state = USART_STATE_READY;

		if (hperh->error_cbk != NULL)
			hperh->error_cbk(hperh);
	}
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup USART_Public_Functions_Group3 Peripheral Control functions
  *  @brief   USART control functions
  *
  * @verbatim
  ==============================================================================
                      ##### Peripheral Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control the USART:
    (+) usart_lin_send_break() API can be helpful to transmit the break character.
    (+) ald_usart_multi_processor_enter_mute_mode() API can be helpful to enter the USART in mute mode.
    (+) ald_usart_multi_processor_exit_mute_mode() API can be helpful to exit the USART mute mode by software.
    (+) ald_usart_half_duplex_enable_send() API to enable the USART transmitter and disables the USART receiver in Half Duplex mode
    (+) ald_usart_half_duplex_enable_recv() API to enable the USART receiver and disables the USART transmitter in Half Duplex mode
    (+) ald_usart_interrupt_config() API to Enables/Disables the specified USART interrupts
    (+) ald_usart_get_flag_status() API to get USART flag status
    (+) ald_usart_clear_flag_status() API to clear USART flag status
    (+) ald_usart_get_it_status() API to Checks whether the specified USART interrupt has occurred or not

    @endverbatim
  * @{
  */

/**
  * @brief  Enters the USART in mute mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_multi_processor_enter_mute_mode(usart_handle_t *hperh)
{
	assert_param(IS_USART(hperh->perh));

	__LOCK(hperh);

	hperh->state = USART_STATE_BUSY;
	SET_BIT(hperh->perh->CON0, USART_CON0_RXWK_MSK);
	hperh->state = USART_STATE_READY;

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Exits the USART mute mode: wake up software.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_multi_processor_exit_mute_mode(usart_handle_t *hperh)
{
	assert_param(IS_USART(hperh->perh));

	__LOCK(hperh);

	hperh->state = USART_STATE_BUSY;
	CLEAR_BIT(hperh->perh->CON0, USART_CON0_RXWK_MSK);
	hperh->state = USART_STATE_READY;

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Enables the USART transmitter and disables the USART receiver.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_half_duplex_enable_send(usart_handle_t *hperh)
{
	__LOCK(hperh);

	hperh->state = USART_STATE_BUSY;
	SET_BIT(hperh->perh->CON0, USART_CON0_RXEN_MSK);
	SET_BIT(hperh->perh->CON0, USART_CON0_TXEN_MSK);
	hperh->state = USART_STATE_READY;

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Enables the USART receiver and disables the USART transmitter.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_usart_half_duplex_enable_recv(usart_handle_t *hperh)
{
	__LOCK(hperh);

	hperh->state = USART_STATE_BUSY;
	SET_BIT(hperh->perh->CON0, USART_CON0_RXEN_MSK);
	SET_BIT(hperh->perh->CON0, USART_CON0_TXEN_MSK);
	hperh->state = USART_STATE_READY;

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Enables or disables the USART's DMA request.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  req: specifies the DMA request.
  *	      @arg USART_dma_req_tx: USART DMA transmit request
  *	      @arg USART_dma_req_rx: USART DMA receive request
  * @param  state: New state of the DMA Request sources.
  *	      @arg ENABLE
  *           @arg DISABLE
  * @return: None
  */
void ald_usart_dma_req_config(usart_handle_t *hperh, usart_dma_req_t req, type_func_t state)
{
	assert_param(IS_USART(hperh->perh));
	assert_param(IS_USART_DMAREQ(req));
	assert_param(IS_FUNC_STATE(state));

	if (state != DISABLE)
		SET_BIT(hperh->perh->CON2, req);
	else
		CLEAR_BIT(hperh->perh->CON2, req);

	return;
}

/**
  * @brief  Enables or disables the specified USART interrupts.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  it: Specifies the USART interrupt sources to be enabled or disabled.
  *           This parameter can be one of the following values:
  *           @arg USART_IT_CTS:  CTS change interrupt
  *           @arg USART_IT_LBD:  LIN Break detection interrupt
  *           @arg USART_IT_TXE:  Transmit Data Register empty interrupt
  *           @arg USART_IT_TC:   Transmission complete interrupt
  *           @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *           @arg USART_IT_IDLE: Idle line detection interrupt
  *           @arg USART_IT_PE:   Parity Error interrupt
  *           @arg USART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @param  state: New status
  *           - ENABLE
  *           - DISABLE
  * @retval None
  */
void ald_usart_interrupt_config(usart_handle_t *hperh, usart_it_t it, type_func_t state)
{
	uint8_t idx;

	assert_param(IS_USART(hperh->perh));
	assert_param(IS_USART_CONFIG_IT(it));
	assert_param(IS_FUNC_STATE(state));

	idx = (it >> 16) & 0x7;
	it &= 0xFFFF;

	if (state) {
		if (idx == 1)
			SET_BIT(hperh->perh->CON0, it);
		else if (idx == 2)
			SET_BIT(hperh->perh->CON1, it);
		else if (idx == 4)
			SET_BIT(hperh->perh->CON2, it);
		else
			;
	}
	else {
		if (idx == 1)
			CLEAR_BIT(hperh->perh->CON0, it);
		else if (idx == 2)
			CLEAR_BIT(hperh->perh->CON1, it);
		else if (idx == 4)
			CLEAR_BIT(hperh->perh->CON2, it);
		else
			;
	}

	return;
}

/** @brief  Check whether the specified USART flag is set or not.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  flag: specifies the flag to check.
  *         This parameter can be one of the @ref usart_flag_t.
  * @retval Status
  *           - SET
  *           - RESET
  */
flag_status_t ald_usart_get_flag_status(usart_handle_t *hperh, usart_flag_t flag)
{
	flag_status_t status = RESET;

	assert_param(IS_USART(hperh->perh));
	assert_param(IS_USART_FLAG(flag));

	if (READ_BIT(hperh->perh->STAT, flag))
		status = SET;

	return status;
}

/** @brief  Clear the specified USART pending flags.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  flag: specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg USART_FLAG_TC:   Transmission Complete flag.
  *            @arg USART_FLAG_RXNE: Receive data register not empty flag.
  * @note   PE (Parity error), FE (Framing error), NE (Noise error), ORE (OverRun
  *          error) and IDLE (Idle line detected) flags are cleared by software
  *          sequence: a read operation to USART_SR register followed by a read
  *          operation to USART_DR register.
  * @note   RXNE flag can be also cleared by a read to the USART_DR register.
  * @note   TC flag can be also cleared by software sequence: a read operation to
  *         USART_SR register followed by a write operation to USART_DR register.
  * @note   TXE flag is cleared only by a write to the USART_DR register.
  * @retval None
  */
void ald_usart_clear_flag_status(usart_handle_t *hperh, usart_flag_t flag)
{
	assert_param(IS_USART(hperh->perh));
	assert_param(IS_USART_CLEAR_FLAG(flag));

	CLEAR_BIT(hperh->perh->STAT, flag);
}

/**
  * @brief  Checks whether the specified USART interrupt has occurred or not.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @param  it: Specifies the USART interrupt source to check.
  *	       This parameter can be one of the following values:
  *	       @arg USART_IT_CTS:  CTS change interrupt
  *	       @arg USART_IT_LBD:  LIN Break detection interrupt
  *	       @arg USART_IT_TXE:  Tansmit Data Register empty interrupt
  *	       @arg USART_IT_TC:   Transmission complete interrupt
  *	       @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *	       @arg USART_IT_IDLE: Idle line detection interrupt
  *	       @arg USART_IT_ORE:  OverRun Error interrupt
  *	       @arg USART_IT_NE:   Noise Error interrupt
  *	       @arg USART_IT_FE:   Framing Error interrupt
  *	       @arg USART_IT_PE:   Parity Error interrupt
  * @retval Status
  *           - SET
  *           - RESET
  */
it_status_t ald_usart_get_it_status(usart_handle_t *hperh, usart_it_t it)
{
	uint8_t idx;
	it_status_t status = RESET;

	/* Check the parameters */
	assert_param(IS_USART(hperh->perh));
	assert_param(IS_USART_GET_IT(it));

	idx = (it >> 16) & 0x7;
	it &= 0xFFFF;

	if (idx == 0) {
		if (READ_BIT(hperh->perh->STAT, it))
			status = SET;
	}
	else if (idx == 1) {
		if (READ_BIT(hperh->perh->CON0, it))
			status = SET;
	}
	else if (idx == 2) {
		if (READ_BIT(hperh->perh->CON1, it))
			status = SET;
	}
	else if (idx == 4) {
		if (READ_BIT(hperh->perh->CON2, it))
			status = SET;
	}
	else {
		/* do nothing */
	}

	return status;
}

/**
  * @}
  */

/** @defgroup USART_Public_Functions_Group4 Peripheral State and Errors functions
  *  @brief   USART State and Errors functions
  *
@verbatim
  ==============================================================================
                 ##### Peripheral State and Errors functions #####
  ==============================================================================
 [..]
   This subsection provides a set of functions allowing to return the State of
   USART communication process, return Peripheral Errors occurred during communication
   process
   (+) ald_usart_get_state() API can be helpful to check in run-time the state of the USART peripheral.
   (+) ald_usart_get_error() check in run-time errors that could be occurred during communication.

@endverbatim
  * @{
  */

/**
  * @brief  Returns the USART state.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval USART state
  */
usart_state_t ald_usart_get_state(usart_handle_t *hperh)
{
	return hperh->state;
}

/**
  * @brief  Return the USART error code
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART.
  * @retval USART Error Code
  */
uint32_t ald_usart_get_error(usart_handle_t *hperh)
{
	return hperh->err_code;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup USART_Private_Functions   USART Private Functions
  *  @brief   USART Private functions
  * @{
  */
#ifdef ALD_DMA
/**
  * @brief  DMA USART transmit process complete callback.
  * @param  arg: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval None
  */
static void usart_dma_send_cplt(void *arg)
{
	usart_handle_t *hperh = (usart_handle_t *)arg;

	hperh->tx_count = 0;
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_TXDMAEN_MSK);
	ald_usart_interrupt_config(hperh, USART_IT_TC, ENABLE);
}

/**
  * @brief  DMA USART receive process complete callback.
  * @param  arg: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval None
  */
static void usart_dma_recv_cplt(void *arg)
{
	usart_handle_t *hperh = (usart_handle_t *)arg;

	hperh->rx_count = 0;
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_RXDMAEN_MSK);
	CLEAR_BIT(hperh->state, USART_STATE_RX_MASK);

	if (hperh->rx_cplt_cbk != NULL)
		hperh->rx_cplt_cbk(hperh);
}

/**
  * @brief  DMA USART communication error callback.
  * @param  arg: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval None
  */
static void usart_dma_error(void *arg)
{
	usart_handle_t *hperh = (usart_handle_t *)arg;

	hperh->rx_count  = 0;
	hperh->tx_count  = 0;
	hperh->state     = USART_STATE_READY;
	hperh->err_code |= USART_ERROR_DMA;

	CLEAR_BIT(hperh->perh->CON2, USART_CON2_TXDMAEN_MSK);
	CLEAR_BIT(hperh->perh->CON2, USART_CON2_RXDMAEN_MSK);

	if (hperh->error_cbk != NULL)
		hperh->error_cbk(hperh);
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
static ald_status_t usart_wait_flag(usart_handle_t *hperh, usart_flag_t flag, flag_status_t status, uint32_t timeout)
{
	uint32_t tick;

	if (timeout == 0)
		return OK;

	tick = ald_get_tick();

	while ((ald_usart_get_flag_status(hperh, flag)) != status) {
		if (((ald_get_tick()) - tick) > timeout) {
			ald_usart_interrupt_config(hperh, USART_IT_TXE, DISABLE);
			ald_usart_interrupt_config(hperh, USART_IT_RXNE, DISABLE);
			ald_usart_interrupt_config(hperh, USART_IT_PE, DISABLE);
			ald_usart_interrupt_config(hperh, USART_IT_ERR, DISABLE);

			return TIMEOUT;
		}
	}

	return OK;
}

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __usart_send_by_it(usart_handle_t *hperh)
{
	if ((hperh->state != USART_STATE_BUSY_TX) && (hperh->state != USART_STATE_BUSY_TX_RX))
		return BUSY;

	if ((hperh->init.word_length == USART_WORD_LENGTH_9B) && (hperh->init.parity == USART_PARITY_NONE)) {
		WRITE_REG(hperh->perh->DATA, (uint16_t)(*(uint16_t *)hperh->tx_buf & (uint16_t)0x01FF));
		hperh->tx_buf += 2;
	}
	else {
		WRITE_REG(hperh->perh->DATA, *hperh->tx_buf++);
	}

	if (--hperh->tx_count == 0) {
		ald_usart_interrupt_config(hperh, USART_IT_TXE, DISABLE);
		ald_usart_interrupt_config(hperh, USART_IT_TC, ENABLE);
	}

	return OK;
}


/**
  * @brief  Wraps up transmission in non blocking mode.
  * @param  hperh: pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __usart_end_send_by_it(usart_handle_t *hperh)
{
	ald_usart_interrupt_config(hperh, USART_IT_TC, DISABLE);
	CLEAR_BIT(hperh->state, USART_STATE_TX_MASK);

	if (hperh->tx_cplt_cbk != NULL)
		hperh->tx_cplt_cbk(hperh);

	return OK;
}

/**
  * @brief  Receives an amount of data in non blocking mode
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __usart_recv_by_it(usart_handle_t *hperh)
{
	if ((hperh->state != USART_STATE_BUSY_RX) && (hperh->state != USART_STATE_BUSY_TX_RX))
		return BUSY;

	if (hperh->init.word_length == USART_WORD_LENGTH_9B) {
		if (hperh->init.parity == USART_PARITY_NONE) {
			*(uint16_t *)hperh->rx_buf = (uint16_t)(hperh->perh->DATA & (uint16_t)0x01FF);
			hperh->rx_buf += 2;
		}
		else {
			*hperh->rx_buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);
		}
    	}
	else {
		if (hperh->init.parity == USART_PARITY_NONE)
			*hperh->rx_buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);
		else
			*hperh->rx_buf++ = (uint8_t)(hperh->perh->DATA & 0x7F);
	}

	if (__frame_mode && ((ald_usart_get_it_status(hperh, USART_IT_IDLE)) == RESET))
		ald_usart_interrupt_config(hperh, USART_IT_IDLE, ENABLE);

	if (--hperh->rx_count == 0) {
		ald_usart_interrupt_config(hperh, USART_IT_RXNE, DISABLE);
		CLEAR_BIT(hperh->state, USART_STATE_RX_MASK);
		__frame_mode = 0;

		if (hperh->state == USART_STATE_READY) {
			ald_usart_interrupt_config(hperh, USART_IT_PE, DISABLE);
			ald_usart_interrupt_config(hperh, USART_IT_ERR, DISABLE);
		}

		if (hperh->rx_cplt_cbk != NULL)
			hperh->rx_cplt_cbk(hperh);
	}

	return OK;
}

/**
  * @brief  Receives an frame complete in non blocking mode
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __usart_recv_frame_cplt(usart_handle_t *hperh)
{
	if ((hperh->state != USART_STATE_BUSY_RX) && (hperh->state != USART_STATE_BUSY_TX_RX))
		return BUSY;

	ald_usart_interrupt_config(hperh, USART_IT_IDLE, DISABLE);
	ald_usart_interrupt_config(hperh, USART_IT_RXNE, DISABLE);
	CLEAR_BIT(hperh->state, USART_STATE_RX_MASK);

	__frame_mode    = 0;
	hperh->rx_size -= hperh->rx_count;

	if (hperh->state == USART_STATE_READY) {
		ald_usart_interrupt_config(hperh, USART_IT_PE, DISABLE);
		ald_usart_interrupt_config(hperh, USART_IT_ERR, DISABLE);
	}

	if (hperh->rx_cplt_cbk != NULL)
		hperh->rx_cplt_cbk(hperh);

	return OK;
}



/**
  * @brief  Simplex Receive an amount of data in non-blocking mode.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __usart_recv_by_it_sync(usart_handle_t *hperh)
{
	if (hperh->state != USART_STATE_BUSY_RX)
		return BUSY;

	if (hperh->init.word_length == USART_WORD_LENGTH_9B) {

		if (hperh->init.parity == USART_PARITY_NONE) {
			*(uint16_t *)hperh->rx_buf = (uint16_t)(hperh->perh->DATA & 0x1FF);
			hperh->rx_buf += 2;
		}
		else {
			*hperh->rx_buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);
		}

		if (--hperh->rx_count != 0x00)
			WRITE_REG(hperh->perh->DATA, (DUMMY_DATA & 0x1FF));
	}
	else {
		if (hperh->init.parity == USART_PARITY_NONE)
			*hperh->rx_buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);
		else
			*hperh->rx_buf++ = (uint8_t)(hperh->perh->DATA & 0x7F);

		if (--hperh->rx_count != 0x00)
			hperh->perh->DATA = (DUMMY_DATA & 0xFF);
	}

	if (hperh->rx_count == 0) {
		ald_usart_interrupt_config(hperh, USART_IT_RXNE, DISABLE);
		ald_usart_interrupt_config(hperh, USART_IT_PE, DISABLE);
		ald_usart_interrupt_config(hperh, USART_IT_ERR, DISABLE);
		hperh->state = USART_STATE_READY;

		if (hperh->rx_cplt_cbk != NULL)
			hperh->rx_cplt_cbk(hperh);
	}

	return OK;
}

/**
  * @brief  Full-Duplex Send receive an amount of data in full-duplex mode (non-blocking).
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __usart_send_recv_by_it_sync(usart_handle_t *hperh)
{
	if (hperh->state != USART_STATE_BUSY_TX_RX)
		return BUSY;

	if (hperh->tx_count != 0) {
		if (ald_usart_get_flag_status(hperh, USART_FLAG_TXE) != RESET) {
 			if (hperh->init.word_length == USART_WORD_LENGTH_9B) {
				if (hperh->init.parity == USART_PARITY_NONE) {
					WRITE_REG(hperh->perh->DATA, (uint16_t)(*(uint16_t *)hperh->tx_buf & 0x1FF));
					hperh->tx_buf += 2;
				}
				else {
					WRITE_REG(hperh->perh->DATA, *hperh->tx_buf++);
				}
			}
			else {
				WRITE_REG(hperh->perh->DATA, *hperh->tx_buf++);
			}

			if (--hperh->tx_count == 0)
				ald_usart_interrupt_config(hperh, USART_IT_TXE, DISABLE);
		}
	}

	if (hperh->rx_count != 0) {
		if (ald_usart_get_flag_status(hperh, USART_FLAG_RXNE) != RESET) {
			if (hperh->init.word_length == USART_WORD_LENGTH_9B) {
				if (hperh->init.parity == USART_PARITY_NONE) {
					*(uint16_t *)hperh->rx_buf = (uint16_t)(hperh->perh->DATA & 0x1FF);
					hperh->rx_buf += 2;
				}
				else {
					*hperh->rx_buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);
				}
			}
			else {
				if (hperh->init.parity == USART_PARITY_NONE)
					*hperh->rx_buf++ = (uint8_t)(hperh->perh->DATA & 0xFF);
				else
					*hperh->rx_buf++ = (uint8_t)(hperh->perh->DATA & 0x7F);
			}

			--hperh->rx_count;
		}
	}

	if (hperh->rx_count == 0) {
		ald_usart_interrupt_config(hperh, USART_IT_RXNE, DISABLE);
		ald_usart_interrupt_config(hperh, USART_IT_PE, DISABLE);
		ald_usart_interrupt_config(hperh, USART_IT_ERR, DISABLE);

		hperh->state = USART_STATE_READY;

		if (hperh->tx_rx_cplt_cbk != NULL)
			hperh->tx_rx_cplt_cbk(hperh);
	}

	return OK;
}

/**
  * @brief  Configures the USART peripheral.
  * @param  hperh: Pointer to a usart_handle_t structure that contains
  *         the configuration information for the specified USART module.
  * @retval None
  */
static void usart_set_config (usart_handle_t *hperh)
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
	assert_param(IS_USART_HARDWARE_FLOW_CONTROL(hperh->init.fctl));

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
	MODIFY_REG(hperh->perh->CON2, USART_CON2_RTSEN_MSK, (hperh->init.fctl & 0x1) << USART_CON2_RTSEN_POS);
	MODIFY_REG(hperh->perh->CON2, USART_CON2_CTSEN_MSK, ((hperh->init.fctl >> 1) & 0x1) << USART_CON2_CTSEN_POS);
	MODIFY_REG(hperh->perh->CON0, USART_CON0_RXEN_MSK, (hperh->init.mode & 0x1) << USART_CON0_RXEN_POS);
	MODIFY_REG(hperh->perh->CON0, USART_CON0_TXEN_MSK, ((hperh->init.mode >> 1) & 0x1) << USART_CON0_TXEN_POS);

	/* Determine the integer part */
	integer = ((25 * ald_cmu_get_pclk1_clock()) / (4 * (hperh->init.baud)));
	tmp     = (integer / 100) << 4;

	/* Determine the fractional part */
	fractional = integer - (100 * (tmp >> 4));
	tmp       |= ((((fractional * 16) + 50) / 100) & ((uint8_t)0x0F));
	WRITE_REG(hperh->perh->BAUDCON, (uint16_t)tmp);

	return;
}
/**
  * @}
  */
#endif /* ALD_USART */
/**
  * @}
  */
/**
  * @}
  */
