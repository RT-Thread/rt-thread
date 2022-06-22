/**
  *********************************************************************************
  *
  * @file    ald_i2c.c
  * @brief   I2C module driver.
  *
  * @version V1.0
  * @date    15 Nov 2017
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
 @verbatim
 ==============================================================================
                       ##### How to use this driver #####
 ==============================================================================
 [..]
   The I2C driver can be used as follows:

   (#) Declare a i2c_handle_t handle structure, for example:
       i2c_handle_t  hperh;

   (#) Configure the Communication Speed, Duty cycle, Addressing mode, Own Address1,
       Dual Addressing mode, Own Address2, General call and Nostretch mode in the hperh init structure.

   (#) Initialize the I2C registers by calling the ald_i2c_init().
   (#) To check if target device is ready for communication, use the function ald_i2c_is_device_ready()

   (#) For I2C IO and IO MEM operations, three operation modes are available within this driver :

   *** Polling mode IO operation ***
   =================================
   [..]
     (+) Transmit in master mode an amount of data in blocking mode using ald_i2c_master_send()
     (+) Receive in master mode an amount of data in blocking mode using ald_i2c_master_recv()
     (+) Transmit in slave mode an amount of data in blocking mode using ald_i2c_slave_send()
     (+) Receive in slave mode an amount of data in blocking mode using ald_i2c_slave_recv()

   *** Polling mode IO MEM operation ***
   =====================================
   [..]
     (+) Write an amount of data in blocking mode to a specific memory address using ald_i2c_mem_write()
     (+) Read an amount of data in blocking mode from a specific memory address using ald_i2c_mem_read()


   *** Interrupt mode IO operation ***
   ===================================
   [..]
     (+) The I2C interrupts should have the highest priority in the application in order
         to make them uninterruptible.
     (+) Transmit in master mode an amount of data in non-blocking mode using ald_i2c_master_send_by_it()
     (+) At transmission end of transfer, hperh->master_tx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->master_tx_cplt_cbk()
     (+) Receive in master mode an amount of data in non-blocking mode using ald_i2c_master_recv_by_it()
     (+) At reception end of transfer, hperh->master_rx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->master_rx_cplt_cbk()
     (+) Transmit in slave mode an amount of data in non-blocking mode using ald_i2c_slave_send_by_it()
     (+) At transmission end of transfer, hperh->slave_tx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->slave_tx_cplt_cbk()
     (+) Receive in slave mode an amount of data in non-blocking mode using ald_i2c_slave_recv_by_it()
     (+) At reception end of transfer, hperh->slave_rx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->slave_rx_cplt_cbk()
     (+) In case of transfer Error, hperh->error_callback() function is executed and user can
          add his own code by customization of function pointer hperh->error_callback()

   *** Interrupt mode IO MEM operation ***
   =======================================
   [..]
     (+) The I2C interrupts should have the highest priority in the application in order
         to make them uninterruptible.
     (+) Write an amount of data in non-blocking mode with Interrupt to a specific memory address using
         ald_i2c_mem_write_by_it()
     (+) At Memory end of write transfer, hperh->mem_tx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->mem_tx_cplt_cbk()
     (+) Read an amount of data in non-blocking mode with Interrupt from a specific memory address using
         ald_i2c_mem_read_by_it()
     (+) At Memory end of read transfer, hperh->mem_rx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->mem_rx_cplt_cbk()
     (+) In case of transfer Error, hperh->error_callback() function is executed and user can
          add his own code by customization of function pointer hperh->error_callback()

   *** DMA mode IO operation ***
   ==============================
   [..]
     (+) Transmit in master mode an amount of data in non-blocking mode (DMA) using
         ald_i2c_master_send_by_dma()
     (+) At transmission end of transfer, hperh->master_tx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->master_tx_cplt_cbk()
     (+) Receive in master mode an amount of data in non-blocking mode (DMA) using
         ald_i2c_master_recv_by_dma()
     (+) At reception end of transfer, hperh->master_rx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->master_rx_cplt_cbk()
     (+) Transmit in slave mode an amount of data in non-blocking mode (DMA) using
         ald_i2c_slave_send_by_dma()
     (+) At transmission end of transfer, hperh->slave_tx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->slave_tx_cplt_cbk()
     (+) Receive in slave mode an amount of data in non-blocking mode (DMA) using
         ald_i2c_slave_recv_by_dma()
     (+) At reception end of transfer, hperh->slave_rx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->slave_rx_cplt_cbk()
     (+) In case of transfer Error, hperh->error_callback() function is executed and user can
          add his own code by customization of function pointer hperh->error_callback()

   *** DMA mode IO MEM operation ***
   =================================
   [..]
     (+) Write an amount of data in non-blocking mode with DMA to a specific memory address using
         ald_i2c_mem_write_by_dma()
     (+) At Memory end of write transfer, hperh->mem_tx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->mem_tx_cplt_cbk()
     (+) Read an amount of data in non-blocking mode with DMA from a specific memory address using
         ald_i2c_mem_read_by_dma()
     (+) At Memory end of read transfer, hperh->mem_rx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->mem_rx_cplt_cbk()
     (+) In case of transfer Error, hperh->error_callback() function is executed and user can
          add his own code by customization of function pointer hperh->error_callback()


    *** I2C ald_status_t driver macros list ***
    ==================================
    [..]
      Below the list of most used macros in I2C ald_status_t driver.

     (+) I2C_ENABLE: Enable the I2C peripheral
     (+) I2C_DISABLE: Disable the I2C peripheral
      (@) You can refer to the I2C ald_status_t driver header file for more useful macros


    *** I2C Workarounds linked to Silicon Limitation ***
    ====================================================
    [..]
      Below the list of all silicon limitations implemented for library on our product.
      (@) See ErrataSheet to know full silicon limitation list of your product.

      (#) Workarounds Implemented inside I2C library
         (##) Wrong data read into data register (Polling and Interrupt mode)
         (##) Start cannot be generated after a misplaced Stop
         (##) Some software events must be managed before the current byte is being transferred:
              Workaround: Use DMA in general, except when the Master is receiving a single byte.
              For Interupt mode, I2C should have the highest priority in the application.
         (##) Mismatch on the "Setup time for a repeated Start condition" timing parameter:
              Workaround: Reduce the frequency down to 88 kHz or use the I2C Fast-mode if
              supported by the slave.
         (##) Data valid time (tVD;DAT) violated without the OVR flag being set:
              Workaround: If the slave device allows it, use the clock stretching mechanism
              by programming no_stretch = I2C_NOSTRETCH_DISABLE in ald_i2c_init.

 @endverbatim
 *********************************************************************************
 */

#include "ald_i2c.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup I2C I2C
  * @brief I2C module driver
  * @{
  */
#ifdef ALD_I2C

/** @addtogroup I2C_Private_Constants I2C Private Constants
  * @{
  */
#define I2C_TIMEOUT_FLAG          (__systick_interval / 20 + 1)
#define I2C_TIMEOUT_ADDR_SLAVE    (__systick_interval * 10)
#define I2C_TIMEOUT_BUSY_FLAG     (__systick_interval * 10)
#define I2C_MAX_DELAY             0xFFFFFFFF
/**
  * @}
  */

/** @addtogroup I2C_Private_Functions I2C Private Functions
  * @{
  */
#ifdef ALD_DMA
static void i2c_dma_master_send_cplt(void *argv);
static void i2c_dma_master_recv_cplt(void *argv);
static void i2c_dma_slave_send_cplt(void *argv);
static void i2c_dma_slave_recv_cplt(void *argv);
static void i2c_dma_mem_send_cplt(void *argv);
static void i2c_dma_mem_recv_cplt(void *argv);
static void i2c_dma_error(void *argv);
#endif
static ald_status_t i2c_master_req_write(i2c_handle_t *hperh, uint16_t dev_addr, uint32_t timeout);
static ald_status_t i2c_master_req_read(i2c_handle_t *hperh, uint16_t dev_addr, uint32_t timeout);
static ald_status_t i2c_req_mem_write(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                                      uint16_t add_size, uint32_t timeout);
static ald_status_t i2c_req_mem_read(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                                     uint16_t add_size, uint32_t timeout);
static ald_status_t i2c_wait_flag_to_timeout(i2c_handle_t *hperh, i2c_flag_t flag,
                                                flag_status_t status, uint32_t timeout);
static ald_status_t i2c_wait_master_addr_to_timeout(i2c_handle_t *hperh, i2c_flag_t flag, uint32_t timeout);
static ald_status_t i2c_wait_txe_to_timeout(i2c_handle_t *hperh, uint32_t timeout);
static ald_status_t i2c_wait_btf_to_timeout(i2c_handle_t *hperh, uint32_t timeout);
static ald_status_t i2c_wait_rxne_to_timeout(i2c_handle_t *hperh, uint32_t timeout);
static ald_status_t i2c_wait_stop_to_timeout(i2c_handle_t *hperh, uint32_t timeout);
static ald_status_t i2c_is_ack_failed(i2c_handle_t *hperh);
static ald_status_t i2c_master_send_txe(i2c_handle_t *hperh);
static ald_status_t i2c_master_send_btf(i2c_handle_t *hperh);
static ald_status_t i2c_master_recv_rxne(i2c_handle_t *hperh);
static ald_status_t i2c_master_recv_btf(i2c_handle_t *hperh);
static ald_status_t i2c_slave_send_txe(i2c_handle_t *hperh);
static ald_status_t i2c_slave_send_btf(i2c_handle_t *hperh);
static ald_status_t i2c_slave_recv_rxne(i2c_handle_t *hperh);
static ald_status_t i2c_slave_recv_btf(i2c_handle_t *hperh);
static ald_status_t i2c_slave_addr(i2c_handle_t *hperh);
static ald_status_t i2c_slave_stopf(i2c_handle_t *hperh);
static ald_status_t i2c_slave_af(i2c_handle_t *hperh);
static uint32_t i2c_configure_speed(i2c_handle_t *hperh, uint32_t i2c_clk);
/**
  * @}
  */

/** @defgroup I2C_Public_Functions I2C Public functions
  * @{
  */

/** @defgroup I2C_Public_Functions_Group1 Initialization functions
  * @brief     Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          de-initialiaze the I2Cx peripheral:

      (+) Call the function ald_i2c_init() to configure the selected device with
          the selected configuration:
        (++) Communication Speed
        (++) Duty cycle
        (++) Addressing mode
        (++) Own Address 1
        (++) Dual Addressing mode
        (++) Own Address 2
        (++) General call mode
        (++) Nostretch mode

      (+) Call the function ald_i2c_reset() to restore the default configuration
          of the selected I2Cx periperal.

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the I2C according to the specified parameters
  *         in the i2c_init_t and initialize the associated handle.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_init(i2c_handle_t *hperh)
{
	uint32_t freqrange = 0;
	uint32_t pclk1 = 0;

	if (hperh == NULL)
		return ERROR;

	/* Check the parameters */
	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_CLOCK_SPEED(hperh->init.clk_speed));
	assert_param(IS_I2C_DUTY_CYCLE(hperh->init.duty));
	assert_param(IS_I2C_OWN_ADDRESS1(hperh->init.own_addr1));
	assert_param(IS_I2C_ADDRESSING_MODE(hperh->init.addr_mode));
	assert_param(IS_I2C_GENERAL_CALL(hperh->init.general_call));
	assert_param(IS_I2C_NO_STRETCH(hperh->init.no_stretch));

	if (hperh->init.dual_addr == I2C_DUALADDR_ENABLE)
		assert_param(IS_I2C_OWN_ADDRESS2(hperh->init.own_addr2));

	if (hperh->state == I2C_STATE_RESET)
		hperh->lock = UNLOCK;

	hperh->state = I2C_STATE_BUSY;
	pclk1 = ald_cmu_get_pclk1_clock();
	I2C_DISABLE(hperh);

	freqrange = I2C_FREQ_RANGE(pclk1);
	WRITE_REG(hperh->perh->CON2, freqrange);
	WRITE_REG(hperh->perh->RT, I2C_RISE_TIME(freqrange, hperh->init.clk_speed));
	WRITE_REG(hperh->perh->CKCFG, i2c_configure_speed(hperh, pclk1));
	WRITE_REG(hperh->perh->CON1, hperh->init.general_call);
	SET_BIT(hperh->perh->CON1, hperh->init.no_stretch);

	if (hperh->init.addr_mode == I2C_ADDR_7BIT) {
		WRITE_REG(hperh->perh->ADDR1, (0x7FFF & hperh->init.own_addr1));
	}
	else {
		WRITE_REG(hperh->perh->ADDR1, (0x8000 | hperh->init.own_addr1));
	}

	WRITE_REG(hperh->perh->ADDR2, (hperh->init.dual_addr | hperh->init.own_addr2));

	I2C_ENABLE(hperh);

	hperh->error_code = I2C_ERROR_NONE;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;

	return OK;
}

/**
  * @brief  DeInitialize the I2C peripheral.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_reset(i2c_handle_t *hperh)
{
	if (hperh == NULL)
		return ERROR;

	assert_param(IS_I2C_TYPE(hperh->perh));

	hperh->state = I2C_STATE_BUSY;
	I2C_DISABLE(hperh);

	hperh->error_code = I2C_ERROR_NONE;
	hperh->state      = I2C_STATE_RESET;
	hperh->mode       = I2C_MODE_NONE;

	__UNLOCK(hperh);

	return OK;
}
/**
  * @}
  */

/** @defgroup I2C_Public_Functions_Group2 Input and Output operation functions
  *  @brief   Data transfers functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the I2C data
    transfers.

    (#) There are two modes of transfer:
       (++) Blocking mode : The communication is performed in the polling mode.
            The status of all data processing is returned by the same function
            after finishing transfer.
       (++) No-Blocking mode : The communication is performed using Interrupts
            or DMA. These functions return the status of the transfer startup.
            The end of the data processing will be indicated through the
            dedicated I2C IRQ when using Interrupt mode or the DMA IRQ when
            using DMA mode.

    (#) Blocking mode functions are :
        (++) ald_i2c_master_send()
        (++) ald_i2c_master_recv()
        (++) ald_i2c_slave_send()
        (++) ald_i2c_slave_recv()
        (++) ald_i2c_mem_write()
        (++) ald_i2c_mem_read()
        (++) ald_i2c_is_device_ready()

    (#) No-Blocking mode functions with Interrupt are :
        (++) ald_i2c_master_send_by_it()
        (++) ald_i2c_master_recv_by_it()
        (++) ald_i2c_slave_send_by_it()
        (++) ald_i2c_slave_recv_by_it()
        (++) ald_i2c_mem_write_by_it()
        (++) ald_i2c_mem_read_by_it()

    (#) No-Blocking mode functions with DMA are :
        (++) ald_i2c_master_send_by_dma()
        (++) ald_i2c_master_recv_by_dma()
        (++) ald_i2c_slave_send_by_dma()
        (++) ald_i2c_slave_recv_by_dma()
        (++) ald_i2c_mem_write_by_dma()
        (++) ald_i2c_mem_read_by_dma()

    (#) A set of Transfer Complete Callbacks are provided in non Blocking mode:
        (++) hperh->mem_tx_cplt_cbk()
        (++) hperh->mem_rx_cplt_cbk()
        (++) hperh->master_tx_cplt_cbk()
        (++) hperh->master_rx_cplt_cbk()
        (++) hperh->slave_tx_cplt_cbk()
        (++) hperh->slave_rx_cplt_cbk()
        (++) hperh->error_callback()

@endverbatim
 * @{
 */

/**
  * @brief  Transmits in master mode an amount of data in blocking mode.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_master_send(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf,
                                 uint16_t size, uint32_t timeout)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;

	if (i2c_master_req_write(hperh, dev_addr, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	I2C_CLEAR_ADDRFLAG(hperh);

	while (size > 0) {
		if (i2c_wait_txe_to_timeout(hperh, timeout) != OK) {
			if (hperh->error_code == I2C_ERROR_AF) {
				SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
				__UNLOCK(hperh);
				return ERROR;
			}
			else {
				__UNLOCK(hperh);
				return TIMEOUT;
			}
		}

		hperh->perh->DATA = (*buf++);
		--size;

		if ((ald_i2c_get_flag_status(hperh, I2C_FLAG_BTF) == SET) && (size != 0)) {
			hperh->perh->DATA = (*buf++);
			--size;
		}
	}

	if (i2c_wait_btf_to_timeout(hperh, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
	hperh->state = I2C_STATE_READY;
	__UNLOCK(hperh);
	return OK;

}

/**
  * @brief  Receives in master mode an amount of data in blocking mode.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_master_recv(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf,
                                uint16_t size, uint32_t timeout)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;

	if (i2c_master_req_read(hperh, dev_addr, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	if (size == 1) {
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		__disable_irq();
		I2C_CLEAR_ADDRFLAG(hperh);
		SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
		__enable_irq();
	}
	else if (size == 2) {
		SET_BIT(hperh->perh->CON1, I2C_CON1_POSAP);
		__disable_irq();
		I2C_CLEAR_ADDRFLAG(hperh);
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		__enable_irq();
	}
	else {
		SET_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		I2C_CLEAR_ADDRFLAG(hperh);
	}

	while (size > 3) {
		if (i2c_wait_rxne_to_timeout(hperh, timeout) != OK) {
			if (hperh->error_code == I2C_ERROR_TIMEOUT) {
				__UNLOCK(hperh);
				return TIMEOUT;
			}
			else {
				__UNLOCK(hperh);
				return ERROR;
			}
		}

		(*buf++) = hperh->perh->DATA;
		--size;

		if (ald_i2c_get_flag_status(hperh, I2C_FLAG_BTF) == SET) {
			(*buf++) = hperh->perh->DATA;
			--size;
		}
	}

	switch (size) {
	case 1:
		if (i2c_wait_rxne_to_timeout(hperh, timeout) != OK) {
			if (hperh->error_code == I2C_ERROR_TIMEOUT) {
				__UNLOCK(hperh);
				return TIMEOUT;
			}
			else {
				__UNLOCK(hperh);
				return ERROR;
			}
		}

		(*buf++) = hperh->perh->DATA;
		break;

	case 2:
		if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BTF, RESET, timeout) != OK) {
			__UNLOCK(hperh);
			return TIMEOUT;
		}

		__disable_irq();
		SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
		(*buf++) = hperh->perh->DATA;
		__enable_irq();
		(*buf++) = hperh->perh->DATA;
		break;

	case 3:
		if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BTF, RESET, timeout) != OK) {
			__UNLOCK(hperh);
			return TIMEOUT;
		}

		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		__disable_irq();
		(*buf++) = hperh->perh->DATA;

		if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BTF, RESET, timeout) != OK) {
			__UNLOCK(hperh);
			__enable_irq();
			return TIMEOUT;
		}

		SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
		(*buf++) = hperh->perh->DATA;
		__enable_irq();
		(*buf++) = hperh->perh->DATA;
		break;

	default :
		break;
	}

	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Transmits in slave mode an amount of data in blocking mode.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_slave_send(i2c_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_SLAVE;
	hperh->error_code = I2C_ERROR_NONE;
	SET_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_ADDR, RESET, timeout) != OK) {
		__UNLOCK(hperh);
		return TIMEOUT;
	}

	I2C_CLEAR_ADDRFLAG(hperh);

	if (hperh->init.addr_mode == I2C_ADDR_10BIT) {
		if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_ADDR, RESET, timeout) != OK) {
			__UNLOCK(hperh);
			return TIMEOUT;
		}

		I2C_CLEAR_ADDRFLAG(hperh);
	}

	while (size > 0) {
		if (i2c_wait_txe_to_timeout(hperh, timeout) != OK) {
			CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);

			if (hperh->error_code == I2C_ERROR_AF) {
				__UNLOCK(hperh);
				return ERROR;
			}
			else {
				__UNLOCK(hperh);
				return TIMEOUT;
			}
		}

		hperh->perh->DATA = (*buf++);
		--size;

		if ((ald_i2c_get_flag_status(hperh, I2C_FLAG_BTF) == SET) && (size != 0)) {
			hperh->perh->DATA = (*buf++);
			--size;
		}
	}

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_AF, RESET, timeout) != OK) {
		__UNLOCK(hperh);
		return TIMEOUT;
	}

	ald_i2c_clear_flag_status(hperh, I2C_FLAG_AF);

	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Receive in slave mode an amount of data in blocking mode
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_slave_recv(i2c_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_SLAVE;
	hperh->error_code = I2C_ERROR_NONE;
	SET_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_ADDR, RESET, timeout) != OK) {
		__UNLOCK(hperh);
		return TIMEOUT;
	}

	I2C_CLEAR_ADDRFLAG(hperh);

	while (size > 0) {
		if (i2c_wait_rxne_to_timeout(hperh, timeout) != OK) {
			hperh->perh->CON1 &= (uint32_t)(~I2C_CON1_ACKEN);

			if (hperh->error_code == I2C_ERROR_TIMEOUT) {
				__UNLOCK(hperh);
				return TIMEOUT;
			}
			else {
				__UNLOCK(hperh);
				return ERROR;
			}
		}

		(*buf++) = hperh->perh->DATA;
		--size;

		if ((ald_i2c_get_flag_status(hperh, I2C_FLAG_BTF) == SET) && (size != 0)) {
			(*buf++) = hperh->perh->DATA;
			--size;
		}
	}

	if (i2c_wait_stop_to_timeout(hperh, I2C_TIMEOUT_FLAG) != OK) {
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	__I2C_CLEAR_STOPFLAG(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Transmit in master mode an amount of data in non-blocking mode with Interrupt
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_master_send_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint16_t size)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;

	if (i2c_master_req_write(hperh, dev_addr, I2C_TIMEOUT_FLAG) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	I2C_CLEAR_ADDRFLAG(hperh);

	__UNLOCK(hperh);

	/* Note : The I2C interrupts must be enabled after unlocking current process
	 *        to avoid the risk of I2C interrupt handle execution before current
	 *        process unlock */
	ald_i2c_interrupt_config(hperh, I2C_IT_EVT, ENABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_BUF, ENABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_ERR, ENABLE);
	return OK;
}

/**
  * @brief  Receive in master mode an amount of data in non-blocking mode with Interrupt
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_master_recv_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint16_t size)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;

	if (i2c_master_req_read(hperh, dev_addr, I2C_TIMEOUT_FLAG) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	if (hperh->xfer_count == 1) {
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		I2C_CLEAR_ADDRFLAG(hperh);
		SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
	}
	else if (hperh->xfer_count == 2) {
		SET_BIT(hperh->perh->CON1, I2C_CON1_POSAP);
		I2C_CLEAR_ADDRFLAG(hperh);
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	}
	else {
		SET_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		I2C_CLEAR_ADDRFLAG(hperh);
	}

	__UNLOCK(hperh);

	/* Note : The I2C interrupts must be enabled after unlocking current process
	 *        to avoid the risk of I2C interrupt handle execution before current
	 *        process unlock */
	ald_i2c_interrupt_config(hperh, I2C_IT_EVT, ENABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_BUF, ENABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_ERR, ENABLE);
	return OK;
}

/**
  * @brief  Transmit in slave mode an amount of data in non-blocking mode with Interrupt
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_slave_send_by_it(i2c_handle_t *hperh, uint8_t *buf, uint16_t size)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_SLAVE;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;
	SET_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	__UNLOCK(hperh);

	/* Note : The I2C interrupts must be enabled after unlocking current process
	 *        to avoid the risk of I2C interrupt handle execution before current
	 *        process unlock */
	ald_i2c_interrupt_config(hperh, I2C_IT_EVT, ENABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_BUF, ENABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_ERR, ENABLE);

	return OK;
}

/**
  * @brief  Receive in slave mode an amount of data in non-blocking mode with Interrupt
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_slave_recv_by_it(i2c_handle_t *hperh, uint8_t *buf, uint16_t size)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_SLAVE;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;
	SET_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	__UNLOCK(hperh);

	/* Note : The I2C interrupts must be enabled after unlocking current process
	 *        to avoid the risk of I2C interrupt handle execution before current
	 *        process unlock */
	ald_i2c_interrupt_config(hperh, I2C_IT_EVT, ENABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_BUF, ENABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_ERR, ENABLE);

	return OK;
}

#ifdef ALD_DMA
/**
  * @brief  Transmit in master mode an amount of data in non-blocking mode with DMA
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as I2C transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_master_send_by_dma(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf,
                                     uint16_t size, uint8_t channel)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;

	if (hperh->hdmatx.perh == NULL)
		hperh->hdmatx.perh = DMA0;

	hperh->hdmatx.cplt_cbk = i2c_dma_master_send_cplt;
	hperh->hdmatx.cplt_arg = hperh;
	hperh->hdmatx.err_cbk  = i2c_dma_error;
	hperh->hdmatx.err_arg  = hperh;

	ald_dma_config_struct(&hperh->hdmatx.config);
	hperh->hdmatx.config.src        = (void *)buf;
	hperh->hdmatx.config.dst        = (void *)&hperh->perh->DATA;
	hperh->hdmatx.config.size       = size;
	hperh->hdmatx.config.data_width = DMA_DATA_SIZE_BYTE;
	hperh->hdmatx.config.src_inc    = DMA_DATA_INC_BYTE;
	hperh->hdmatx.config.dst_inc    = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel       = hperh->perh == I2C0 ? DMA_MSEL_I2C0 : DMA_MSEL_I2C1;
	hperh->hdmatx.config.msigsel    = DMA_MSIGSEL_I2C_TXEMPTY;
	hperh->hdmatx.config.channel    = channel;
	ald_dma_config_basic(&hperh->hdmatx);

	if (i2c_master_req_write(hperh, dev_addr, I2C_TIMEOUT_FLAG) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	SET_BIT(hperh->perh->CON2, I2C_CON2_DMAEN);
	I2C_CLEAR_ADDRFLAG(hperh);
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Receive in master mode an amount of data in non-blocking mode with DMA
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as I2C receive
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_master_recv_by_dma(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf,
                                    uint16_t size, uint8_t channel)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;

	if (hperh->hdmarx.perh == NULL)
		hperh->hdmarx.perh = DMA0;

	hperh->hdmarx.cplt_cbk = i2c_dma_master_recv_cplt;
	hperh->hdmarx.cplt_arg = (void *)hperh;
	hperh->hdmarx.err_cbk  = i2c_dma_error;
	hperh->hdmarx.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdmarx.config);
	hperh->hdmarx.config.src        = (void *)&hperh->perh->DATA;
	hperh->hdmarx.config.dst        = (void *)buf;
	hperh->hdmarx.config.size       = size;
	hperh->hdmarx.config.data_width = DMA_DATA_SIZE_BYTE;
	hperh->hdmarx.config.src_inc    = DMA_DATA_INC_NONE;
	hperh->hdmarx.config.dst_inc    = DMA_DATA_INC_BYTE;
	hperh->hdmarx.config.msel       = hperh->perh == I2C0 ? DMA_MSEL_I2C0 : DMA_MSEL_I2C1;
	hperh->hdmarx.config.msigsel    = DMA_MSIGSEL_I2C_RNR;
	hperh->hdmarx.config.channel    = channel;
	ald_dma_config_basic(&hperh->hdmarx);

	if (i2c_master_req_read(hperh, dev_addr, I2C_TIMEOUT_FLAG) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	if (size == 1)
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	else
		SET_BIT(hperh->perh->CON2, I2C_CON2_LDMA);

	SET_BIT(hperh->perh->CON2, I2C_CON2_DMAEN);
	I2C_CLEAR_ADDRFLAG(hperh);
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Transmit in slave mode an amount of data in non-blocking mode with DMA
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as I2C Transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_slave_send_by_dma(i2c_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_SLAVE;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;

	if (hperh->hdmatx.perh == NULL)
		hperh->hdmatx.perh = DMA0;

	hperh->hdmatx.cplt_cbk = i2c_dma_slave_send_cplt;
	hperh->hdmatx.cplt_arg = hperh;
	hperh->hdmatx.err_cbk  = i2c_dma_error;
	hperh->hdmatx.err_arg  = hperh;

	ald_dma_config_struct(&hperh->hdmatx.config);
	hperh->hdmatx.config.src        = (void *)buf;
	hperh->hdmatx.config.dst        = (void *)&hperh->perh->DATA;
	hperh->hdmatx.config.size       = size;
	hperh->hdmatx.config.data_width = DMA_DATA_SIZE_BYTE;
	hperh->hdmatx.config.src_inc    = DMA_DATA_INC_BYTE;
	hperh->hdmatx.config.dst_inc    = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel       = hperh->perh == I2C0 ? DMA_MSEL_I2C0 : DMA_MSEL_I2C1;
	hperh->hdmatx.config.msigsel    = DMA_MSIGSEL_I2C_TXEMPTY;
	hperh->hdmatx.config.channel    = channel;
	ald_dma_config_basic(&hperh->hdmatx);

	SET_BIT(hperh->perh->CON2, I2C_CON2_DMAEN);
	SET_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_ADDR, RESET, I2C_TIMEOUT_ADDR_SLAVE) != OK) {
		__UNLOCK(hperh);
		return TIMEOUT;
	}

	if (hperh->init.addr_mode == I2C_ADDR_7BIT) {
		I2C_CLEAR_ADDRFLAG(hperh);
	}
	else {
		I2C_CLEAR_ADDRFLAG(hperh);

		if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_ADDR, RESET, I2C_TIMEOUT_ADDR_SLAVE) != OK) {
			__UNLOCK(hperh);
			return TIMEOUT;
		}

		I2C_CLEAR_ADDRFLAG(hperh);
	}

	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Receive in slave mode an amount of data in non-blocking mode with DMA
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as I2C receive
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_slave_recv_by_dma(i2c_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_SLAVE;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;

	if (hperh->hdmarx.perh == NULL)
		hperh->hdmarx.perh = DMA0;

	hperh->hdmarx.cplt_cbk = i2c_dma_slave_recv_cplt;
	hperh->hdmarx.cplt_arg = (void *)hperh;
	hperh->hdmarx.err_cbk  = i2c_dma_error;
	hperh->hdmarx.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdmarx.config);
	hperh->hdmarx.config.src        = (void *)&hperh->perh->DATA;
	hperh->hdmarx.config.dst        = (void *)buf;
	hperh->hdmarx.config.size       = size;
	hperh->hdmarx.config.data_width = DMA_DATA_SIZE_BYTE;
	hperh->hdmarx.config.src_inc    = DMA_DATA_INC_NONE;
	hperh->hdmarx.config.dst_inc    = DMA_DATA_INC_BYTE;
	hperh->hdmarx.config.msel       = hperh->perh == I2C0 ? DMA_MSEL_I2C0 : DMA_MSEL_I2C1;
	hperh->hdmarx.config.msigsel    = DMA_MSIGSEL_I2C_RNR;
	hperh->hdmarx.config.channel    = channel;
	ald_dma_config_basic(&hperh->hdmarx);

	SET_BIT(hperh->perh->CON2, I2C_CON2_DMAEN);
	SET_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_ADDR, RESET, I2C_TIMEOUT_ADDR_SLAVE) != OK) {
		__UNLOCK(hperh);
		return TIMEOUT;
	}

	I2C_CLEAR_ADDRFLAG(hperh);
	__UNLOCK(hperh);
	return OK;
}
#endif

/**
  * @brief  Write an amount of data in blocking mode to a specific memory address
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_write(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                           i2c_addr_size_t add_size, uint8_t *buf, uint16_t size, uint32_t timeout)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_MEMADD_size(add_size));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_MEM;
	hperh->error_code = I2C_ERROR_NONE;

	if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	while (size > 0) {
		if (i2c_wait_txe_to_timeout(hperh, timeout) != OK) {
			if (hperh->error_code == I2C_ERROR_AF) {
				SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
				__UNLOCK(hperh);
				return ERROR;
			}
			else {
				__UNLOCK(hperh);
				return TIMEOUT;
			}
		}

		hperh->perh->DATA = (*buf++);
		--size;

		if ((ald_i2c_get_flag_status(hperh, I2C_FLAG_BTF) == SET) && (size != 0)) {
			hperh->perh->DATA = (*buf++);
			--size;
		}
	}

	if (i2c_wait_txe_to_timeout(hperh, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
	ald_delay_ms(10);
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Read an amount of data in blocking mode from a specific memory address
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_read(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, i2c_addr_size_t add_size,
                          uint8_t *buf, uint16_t size, uint32_t timeout)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_MEMADD_size(add_size));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_MEM;
	hperh->error_code = I2C_ERROR_NONE;

	if (i2c_req_mem_read(hperh, dev_addr, mem_addr, add_size, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	if (size == 1) {
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		__disable_irq();
		I2C_CLEAR_ADDRFLAG(hperh);
		SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
		__enable_irq();
	}
	else if (size == 2) {
		SET_BIT(hperh->perh->CON1, I2C_CON1_POSAP);
		__disable_irq();
		I2C_CLEAR_ADDRFLAG(hperh);
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		__enable_irq();
	}
	else {
		SET_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		I2C_CLEAR_ADDRFLAG(hperh);
	}

	while (size > 3) {
		if (i2c_wait_rxne_to_timeout(hperh, timeout) != OK) {
			if (hperh->error_code == I2C_ERROR_TIMEOUT) {
				__UNLOCK(hperh);
				return TIMEOUT;
			}
			else {
				__UNLOCK(hperh);
				return ERROR;
			}
		}

		(*buf++) = hperh->perh->DATA;
		--size;

		if (ald_i2c_get_flag_status(hperh, I2C_FLAG_BTF) == SET) {
			(*buf++) = hperh->perh->DATA;
			--size;
		}
	}

	switch (size) {
	case 1:
		if (i2c_wait_rxne_to_timeout(hperh, timeout) != OK) {
			if (hperh->error_code == I2C_ERROR_TIMEOUT) {
				__UNLOCK(hperh);
				return TIMEOUT;
			}
			else {
				__UNLOCK(hperh);
				return ERROR;
			}
		}

		(*buf++) = hperh->perh->DATA;
		break;

	case 2:
		if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BTF, RESET, timeout) != OK) {
			__UNLOCK(hperh);
			return TIMEOUT;
		}

		__disable_irq();
		SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
		(*buf++) = hperh->perh->DATA;
		__enable_irq();
		(*buf++) = hperh->perh->DATA;
		break;

	case 3:
		if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BTF, RESET, timeout) != OK) {
			__UNLOCK(hperh);
			return TIMEOUT;
		}

		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		__disable_irq();
		(*buf++) = hperh->perh->DATA;

		if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BTF, RESET, timeout) != OK) {
			__UNLOCK(hperh);
			__enable_irq();
			return TIMEOUT;
		}

		SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
		(*buf++) = hperh->perh->DATA;
		__enable_irq();
		(*buf++) = hperh->perh->DATA;
		break;

	default:
		break;
	}

	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Write an amount of data in non-blocking mode with Interrupt to a specific memory address
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_write_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                              i2c_addr_size_t add_size, uint8_t *buf, uint16_t size)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_MEMADD_size(add_size));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_MEM;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;

	if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, I2C_TIMEOUT_FLAG) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	__UNLOCK(hperh);

	/* Note : The I2C interrupts must be enabled after unlocking current process
	 *        to avoid the risk of I2C interrupt handle execution before current
	 *        process unlock */
	ald_i2c_interrupt_config(hperh, I2C_IT_EVT, ENABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_BUF, ENABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_ERR, ENABLE);

	return OK;
}

/**
  * @brief  Read an amount of data in non-blocking mode with Interrupt from a specific memory address
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_read_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                             i2c_addr_size_t add_size, uint8_t *buf, uint16_t size)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_MEMADD_size(add_size));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_MEM;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;

	if (i2c_req_mem_read(hperh, dev_addr, mem_addr, add_size, I2C_TIMEOUT_FLAG) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	if (hperh->xfer_count == 1) {
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		I2C_CLEAR_ADDRFLAG(hperh);
		SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
	}
	else if (hperh->xfer_count == 2) {
		SET_BIT(hperh->perh->CON1, I2C_CON1_POSAP);
		I2C_CLEAR_ADDRFLAG(hperh);
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	}
	else {
		SET_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		I2C_CLEAR_ADDRFLAG(hperh);
	}

	__UNLOCK(hperh);

	/* Note : The I2C interrupts must be enabled after unlocking current process
	 *        to avoid the risk of I2C interrupt handle execution before current
	 *        process unlock */
	ald_i2c_interrupt_config(hperh, I2C_IT_EVT, ENABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_BUF, ENABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_ERR, ENABLE);

	return OK;
}

#ifdef ALD_DMA
/**
  * @brief  Write an amount of data in non-blocking mode with DMA to a specific memory address
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_write_by_dma(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, i2c_addr_size_t add_size,
                               uint8_t *buf, uint16_t size, uint8_t channel)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_MEMADD_size(add_size));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_MEM;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;

	if (hperh->hdmatx.perh == NULL)
		hperh->hdmatx.perh = DMA0;

	hperh->hdmatx.cplt_cbk = i2c_dma_mem_send_cplt;
	hperh->hdmatx.cplt_arg = hperh;
	hperh->hdmatx.err_cbk  = i2c_dma_error;
	hperh->hdmatx.err_arg  = hperh;
	ald_dma_config_struct(&hperh->hdmatx.config);

	hperh->hdmatx.config.src        = (void *)buf;
	hperh->hdmatx.config.dst        = (void *)&hperh->perh->DATA;
	hperh->hdmatx.config.data_width = DMA_DATA_SIZE_BYTE;
	hperh->hdmatx.config.size       = size;
	hperh->hdmatx.config.src_inc    = DMA_DATA_INC_BYTE;
	hperh->hdmatx.config.dst_inc    = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel       = hperh->perh == I2C0 ? DMA_MSEL_I2C0 : DMA_MSEL_I2C1;
	hperh->hdmatx.config.msigsel    = DMA_MSIGSEL_I2C_TXEMPTY;
	hperh->hdmatx.config.channel    = channel;
	ald_dma_config_basic(&hperh->hdmatx);

	if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, I2C_TIMEOUT_FLAG) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	SET_BIT(hperh->perh->CON2, I2C_CON2_DMAEN);
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Reads an amount of data in non-blocking mode with DMA from a specific memory address.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be read
  * @param  channel: DMA channel
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_read_by_dma(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, i2c_addr_size_t add_size,
                              uint8_t *buf, uint16_t size, uint8_t channel)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_MEMADD_size(add_size));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_MEM;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;

	if (hperh->hdmarx.perh == NULL)
		hperh->hdmarx.perh = DMA0;

	hperh->hdmarx.cplt_cbk = i2c_dma_mem_recv_cplt;
	hperh->hdmarx.cplt_arg = (void *)hperh;
	hperh->hdmarx.err_cbk  = i2c_dma_error;
	hperh->hdmarx.err_arg  = (void *)hperh;
	ald_dma_config_struct(&hperh->hdmarx.config);

	hperh->hdmarx.config.src        = (void *)&hperh->perh->DATA;
	hperh->hdmarx.config.dst        = (void *)buf;
	hperh->hdmarx.config.data_width = DMA_DATA_SIZE_BYTE;
	hperh->hdmarx.config.size       = size;
	hperh->hdmarx.config.src_inc    = DMA_DATA_INC_NONE;
	hperh->hdmarx.config.dst_inc    = DMA_DATA_INC_BYTE;
	hperh->hdmarx.config.msel       = hperh->perh == I2C0 ? DMA_MSEL_I2C0 : DMA_MSEL_I2C1;
	hperh->hdmarx.config.msigsel    = DMA_MSIGSEL_I2C_RNR;
	hperh->hdmarx.config.channel    = channel;
	ald_dma_config_basic(&hperh->hdmarx);

	if (i2c_req_mem_read(hperh, dev_addr, mem_addr, add_size, I2C_TIMEOUT_FLAG) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			__UNLOCK(hperh);
			return ERROR;
		}
		else {
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}

	if (size == 1)
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	else
		SET_BIT(hperh->perh->CON2, I2C_CON2_LDMA);

	SET_BIT(hperh->perh->CON2, I2C_CON2_DMAEN);
	I2C_CLEAR_ADDRFLAG(hperh);
	__UNLOCK(hperh);
	return OK;
}
#endif

/**
  * @brief  Checks if target device is ready for communication.
  * @note   This function is used with Memory devices
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  trials: Number of trials
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_is_device_ready(i2c_handle_t *hperh, uint16_t dev_addr, uint32_t trials, uint32_t timeout)
{
	uint32_t tickstart = 0;
	uint32_t tmp1 = 0;
	uint32_t tmp2 = 0;
	uint32_t tmp3 = 0;
	uint32_t I2C_Trials = 1;

	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));

	__LOCK(hperh);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);

	hperh->state = I2C_STATE_BUSY;
	hperh->error_code = I2C_ERROR_NONE;

	do {
		SET_BIT(hperh->perh->CON1, I2C_CON1_START);

		if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_SB, RESET, timeout) != OK) {
			__UNLOCK(hperh);
			return TIMEOUT;
		}

		hperh->perh->DATA = I2C_7BIT_ADD_WRITE(dev_addr);
		tickstart            = ald_get_tick();
		tmp1                 = ald_i2c_get_flag_status(hperh, I2C_FLAG_ADDR);
		tmp2                 = ald_i2c_get_flag_status(hperh, I2C_FLAG_AF);
		tmp3                 = hperh->state;

		while ((tmp1 == RESET) && (tmp2 == RESET) && (tmp3 != I2C_STATE_TIMEOUT)) {
			if ((timeout == 0) || ((ald_get_tick() - tickstart ) > timeout))
				hperh->state = I2C_STATE_TIMEOUT;

			tmp1 = ald_i2c_get_flag_status(hperh, I2C_FLAG_ADDR);
			tmp2 = ald_i2c_get_flag_status(hperh, I2C_FLAG_AF);
			tmp3 = hperh->state;
		}
		hperh->state = I2C_STATE_READY;

		if (ald_i2c_get_flag_status(hperh, I2C_FLAG_ADDR) == SET) {
			SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
			I2C_CLEAR_ADDRFLAG(hperh);

			if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET,
							I2C_TIMEOUT_BUSY_FLAG) != OK) {
				__UNLOCK(hperh);
				return TIMEOUT;
			}

			hperh->state = I2C_STATE_READY;
			__UNLOCK(hperh);
			return OK;
		}
		else {
			SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
			ald_i2c_clear_flag_status(hperh, I2C_FLAG_AF);

			if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BUSY, SET,
							I2C_TIMEOUT_BUSY_FLAG) != OK) {
				__UNLOCK(hperh);
				return TIMEOUT;
			}
		}
	} while (I2C_Trials++ < trials);

	hperh->state = I2C_STATE_READY;
	__UNLOCK(hperh);
	return OK;
}
/**
  * @}
  */

/** @defgroup I2C_Public_Functions_Group3 Peripheral Control functions
  * @brief   Peripheral state and Errors functions
  *
@verbatim
 ===============================================================================
            ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
 * @{
 */

/**
  * @brief  Enable/disable the specified i2c interrupts.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  it: Specifies the i2c interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref i2c_interrupt_t.
  * @param  state: New state of the specified i2c interrupts.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_i2c_interrupt_config(i2c_handle_t *hperh, i2c_interrupt_t it, type_func_t state)
{
	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_IT_TYPE(it));
	assert_param(IS_FUNC_STATE(state));

	if (state == ENABLE)
		SET_BIT((hperh)->perh->CON2, (it));
	else
		CLEAR_BIT((hperh)->perh->CON2, (it));

	return;
}

/**
  * @brief  Get the status of I2C_SR register.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  flag: Specifies the I2C status type.
  *         This parameter can be one of the @ref i2c_flag_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_i2c_get_flag_status(i2c_handle_t *hperh, i2c_flag_t flag)
{
	flag_status_t state = RESET;

	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_FLAG(flag));

	if ((flag & 0xFF0000) == 0) {
		if ((hperh->perh->STAT1 & flag) == flag)
			state = SET;
	}
	else {
		if ((hperh->perh->STAT2 & (flag >> 16)) == (flag >> 16))
			state = SET;
	}

	return state;
}

/**
  * @brief  Get the status of interrupt.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  it: Specifies the i2c interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref i2c_interrupt_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_i2c_get_it_status(i2c_handle_t *hperh, i2c_interrupt_t it)
{
	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_IT_TYPE(it));

	if ((hperh->perh->CON2 & it) == it)
		return SET;
	else
		return RESET;
}

/**
  * @brief  Clear the UART interrupt flag.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  flag: Specifies the UART interrupt flag.
  *         This parameter can be one of the @ref uart_flag_t.
  * @retval None
  */
void ald_i2c_clear_flag_status(i2c_handle_t *hperh, i2c_flag_t flag)
{
	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_FLAG(flag));

	if (flag > 65535)
		return;

	hperh->perh->STAT1 = (hperh->perh->STAT1 & (uint32_t)(~flag));

	return;

}

/**
  * @brief  Return the I2C handle state.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval ald_status_t state
  */
i2c_state_t ald_i2c_get_state(i2c_handle_t *hperh)
{
	return hperh->state;
}

/**
  * @brief  Return the I2C error code.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval I2C Error Code
  */
uint32_t ald_i2c_get_error(i2c_handle_t *hperh)
{
	return hperh->error_code;
}
/**
  * @}
  */

/** @defgroup I2C_Public_Functions_Group4 IRQ Handler and Callbacks
  * @{
  */

/**
  * @brief  This function handles I2C event interrupt request.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void ald_i2c_ev_irq_handler(i2c_handle_t *hperh)
{
	if (ald_i2c_get_flag_status(hperh, I2C_FLAG_ADDR) == SET)
		i2c_slave_addr(hperh);

	if ((ald_i2c_get_it_status(hperh, I2C_IT_BUF) == SET) && (ald_i2c_get_flag_status(hperh, I2C_FLAG_TXE) == SET)) {
		if ((hperh->mode == I2C_MODE_MASTER) || (hperh->mode == I2C_MODE_MEM))
			i2c_master_send_txe(hperh);
		else
			i2c_slave_send_txe(hperh);
	}

	if ((ald_i2c_get_it_status(hperh, I2C_IT_BUF) == SET) && (ald_i2c_get_flag_status(hperh, I2C_FLAG_RXNE) == SET)) {
		if ((hperh->mode == I2C_MODE_MASTER) || (hperh->mode == I2C_MODE_MEM))
			i2c_master_recv_rxne(hperh);
		else
			i2c_slave_recv_rxne(hperh);
	}

	if (ald_i2c_get_flag_status(hperh, I2C_FLAG_BTF) == SET) {
		if (ald_i2c_get_flag_status(hperh, I2C_FLAG_TRA) == SET) {
			if ((hperh->mode == I2C_MODE_MASTER) || (hperh->mode == I2C_MODE_MEM))
				i2c_master_send_btf(hperh);
			else
				i2c_slave_send_btf(hperh);
		}
		else {
			if ((hperh->mode == I2C_MODE_MASTER) || (hperh->mode == I2C_MODE_MEM))
				i2c_master_recv_btf(hperh);
			else
				i2c_slave_recv_btf(hperh);
		}
	}

	if ((hperh->mode == I2C_MODE_SLAVE) && (ald_i2c_get_flag_status(hperh, I2C_FLAG_STOPF) == SET))
		i2c_slave_stopf(hperh);
}

/**
  * @brief  This function handles I2C error interrupt request.
  * @param  hperh: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval  NONE
  */
void ald_i2c_er_irq_handler(i2c_handle_t *hperh)
{
	uint32_t tmp1 = 0;
	uint32_t tmp2 = 0;
	uint32_t tmp3 = 0;

	tmp1 = ald_i2c_get_flag_status(hperh, I2C_FLAG_BERR);
	tmp2 = ald_i2c_get_it_status(hperh, I2C_IT_ERR);

	/* I2C Bus error interrupt occurred */
	if ((tmp1 == SET) && (tmp2 == SET)) {
		hperh->error_code |= I2C_ERROR_BERR;
		ald_i2c_clear_flag_status(hperh, I2C_FLAG_BERR);
		SET_BIT(hperh->perh->CON1, I2C_CON1_SRST);
	}

	tmp1 = ald_i2c_get_flag_status(hperh, I2C_FLAG_ARLO);
	tmp2 = ald_i2c_get_it_status(hperh, I2C_IT_ERR);

	/* I2C Arbitration Loss error interrupt occurred */
	if ((tmp1 == SET) && (tmp2 == SET)) {
		hperh->error_code |= I2C_ERROR_ARLO;
		ald_i2c_clear_flag_status(hperh, I2C_FLAG_ARLO);
	}

	tmp1 = ald_i2c_get_flag_status(hperh, I2C_FLAG_AF);
	tmp2 = ald_i2c_get_it_status(hperh, I2C_IT_ERR);

	/* I2C Acknowledge failure error interrupt occurred */
	if ((tmp1 == SET) && (tmp2 == SET)) {
		tmp1 = hperh->mode;
		tmp2 = hperh->xfer_count;
		tmp3 = hperh->state;
		if ((tmp1 == I2C_MODE_SLAVE) && (tmp2 == 0) && \
		   (tmp3 == I2C_STATE_BUSY_TX)) {
			i2c_slave_af(hperh);
		}
		else {
			hperh->error_code |= I2C_ERROR_AF;
			SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
			ald_i2c_clear_flag_status(hperh, I2C_FLAG_AF);
		}
	}

	tmp1 = ald_i2c_get_flag_status(hperh, I2C_FLAG_OVR);
	tmp2 = ald_i2c_get_it_status(hperh, I2C_IT_ERR);

	/* I2C Over-Run/Under-Run interrupt occurred */
	if ((tmp1 == SET) && (tmp2 == SET)) {
		hperh->error_code |= I2C_ERROR_OVR;
		ald_i2c_clear_flag_status(hperh, I2C_FLAG_OVR);
	}

	if (hperh->error_code != I2C_ERROR_NONE) {
		hperh->state = I2C_STATE_READY;
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_POSAP);
		if (hperh->error_callback)
			hperh->error_callback(hperh);
	}
}
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup I2C_Private_Functions
  * @{
  */

/**
  * @brief  Handle TXE flag for Master Transmit mode
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_master_send_txe(i2c_handle_t *hperh)
{
	if (hperh->xfer_count == 0) {
		ald_i2c_interrupt_config(hperh, I2C_IT_BUF, DISABLE);
	}
	else {
		hperh->perh->DATA = (*hperh->p_buff++);
		hperh->xfer_count--;
	}

	return OK;
}

/**
  * @brief  Handle BTF flag for Master Transmit mode
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_master_send_btf(i2c_handle_t *hperh)
{
	if (hperh->xfer_count != 0) {
		hperh->perh->DATA = (*hperh->p_buff++);
		hperh->xfer_count--;
	}
	else {
		ald_i2c_interrupt_config(hperh, I2C_IT_EVT, DISABLE);
		ald_i2c_interrupt_config(hperh, I2C_IT_BUF, DISABLE);
		ald_i2c_interrupt_config(hperh, I2C_IT_ERR, DISABLE);
		SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
		if (hperh->mode == I2C_MODE_MEM) {
			hperh->state = I2C_STATE_READY;
			if (hperh->mem_tx_cplt_cbk)
				hperh->mem_tx_cplt_cbk(hperh);
		}
		else {
			hperh->state = I2C_STATE_READY;
			if (hperh->master_tx_cplt_cbk)
				hperh->master_tx_cplt_cbk(hperh);
		}
	}
	return OK;
}

/**
  * @brief  Handle RXNE flag for Master Receive mode
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_master_recv_rxne(i2c_handle_t *hperh)
{
	uint32_t tmp = 0;

	tmp = hperh->xfer_count;
	if (tmp > 3) {
		(*hperh->p_buff++) = hperh->perh->DATA;
		hperh->xfer_count--;
	}
	else if ((tmp == 2) || (tmp == 3)) {
		ald_i2c_interrupt_config(hperh, I2C_IT_BUF, DISABLE);
	}
	else {
		ald_i2c_interrupt_config(hperh, I2C_IT_EVT, DISABLE);
		ald_i2c_interrupt_config(hperh, I2C_IT_BUF, DISABLE);
		ald_i2c_interrupt_config(hperh, I2C_IT_ERR, DISABLE);
		(*hperh->p_buff++) = hperh->perh->DATA;
		hperh->xfer_count--;

		if (hperh->mode == I2C_MODE_MEM) {
			hperh->state = I2C_STATE_READY;
			if (hperh->mem_rx_cplt_cbk)
				hperh->mem_rx_cplt_cbk(hperh);
		}
		else {
			hperh->state = I2C_STATE_READY;
			if (hperh->master_rx_cplt_cbk)
				hperh->master_rx_cplt_cbk(hperh);
		}
	}
	return OK;
}

/**
  * @brief  Handle BTF flag for Master Receive mode
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_master_recv_btf(i2c_handle_t *hperh)
{
	if (hperh->xfer_count == 3) {
		CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
		(*hperh->p_buff++) = hperh->perh->DATA;
		--hperh->xfer_count;
	}
	else if (hperh->xfer_count == 2) {
		ald_i2c_interrupt_config(hperh, I2C_IT_EVT, DISABLE);
		ald_i2c_interrupt_config(hperh, I2C_IT_ERR, DISABLE);
		SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
		(*hperh->p_buff++) = hperh->perh->DATA;
		--hperh->xfer_count;

		(*hperh->p_buff++) = hperh->perh->DATA;
		--hperh->xfer_count;

		if (hperh->mode == I2C_MODE_MEM) {
			hperh->state = I2C_STATE_READY;
			if (hperh->mem_rx_cplt_cbk)
				hperh->mem_rx_cplt_cbk(hperh);
		}
		else {
			hperh->state = I2C_STATE_READY;
			if (hperh->master_rx_cplt_cbk)
				hperh->master_rx_cplt_cbk(hperh);
		}
	}
	else {
		(*hperh->p_buff++) = hperh->perh->DATA;
		--hperh->xfer_count;
	}
	return OK;
}

/**
  * @brief  Handle TXE flag for Slave Transmit mode
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_slave_send_txe(i2c_handle_t *hperh)
{
	if (hperh->xfer_count != 0) {
		hperh->perh->DATA = (*hperh->p_buff++);
		--hperh->xfer_count;
	}
	return OK;
}

/**
  * @brief  Handle BTF flag for Slave Transmit mode
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_slave_send_btf(i2c_handle_t *hperh)
{
	if (hperh->xfer_count != 0) {
		hperh->perh->DATA = (*hperh->p_buff++);
		--hperh->xfer_count;
	}
	return OK;
}

/**
  * @brief  Handle RXNE flag for Slave Receive mode
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_slave_recv_rxne(i2c_handle_t *hperh)
{
	if (hperh->xfer_count != 0) {
		(*hperh->p_buff++) = hperh->perh->DATA;
		--hperh->xfer_count;
	}
	return OK;
}

/**
  * @brief  Handle BTF flag for Slave Receive mode
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_slave_recv_btf(i2c_handle_t *hperh)
{
	if (hperh->xfer_count != 0) {
		(*hperh->p_buff++) = hperh->perh->DATA;
		--hperh->xfer_count;
	}
	return OK;
}

/**
  * @brief  Handle ADD flag for Slave
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_slave_addr(i2c_handle_t *hperh)
{
	I2C_CLEAR_ADDRFLAG(hperh);

	return OK;
}

/**
  * @brief  Handle STOPF flag for Slave mode
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_slave_stopf(i2c_handle_t *hperh)
{
	if (hperh->xfer_count != 0) {
		(*hperh->p_buff++) = hperh->perh->DATA;
		--hperh->xfer_count;
	}

	ald_i2c_interrupt_config(hperh, I2C_IT_EVT, DISABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_BUF, DISABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_ERR, DISABLE);
	__I2C_CLEAR_STOPFLAG(hperh);

	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	hperh->state = I2C_STATE_READY;

	if (hperh->slave_rx_cplt_cbk)
		hperh->slave_rx_cplt_cbk(hperh);

	return OK;
}

/**
  * @brief  Handle Acknowledge Failed for Slave mode
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_slave_af(i2c_handle_t *hperh)
{
	ald_i2c_interrupt_config(hperh, I2C_IT_EVT, DISABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_BUF, DISABLE);
	ald_i2c_interrupt_config(hperh, I2C_IT_ERR, DISABLE);
	ald_i2c_clear_flag_status(hperh, I2C_FLAG_AF);

	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	hperh->state = I2C_STATE_READY;

	if (hperh->slave_tx_cplt_cbk)
		hperh->slave_tx_cplt_cbk(hperh);

	return OK;
}

/**
  * @brief  Master sends target device address followed by internal memory address for write request.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_master_req_write(i2c_handle_t *hperh, uint16_t dev_addr, uint32_t timeout)
{
	SET_BIT(hperh->perh->CON1, I2C_CON1_START);

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_SB, RESET, timeout) != OK)
		return TIMEOUT;

	if (hperh->init.addr_mode == I2C_ADDR_7BIT) {
		hperh->perh->DATA = I2C_7BIT_ADD_WRITE(dev_addr);
	}
	else {
		hperh->perh->DATA = I2C_10BIT_HEADER_WRITE(dev_addr);

		if (i2c_wait_master_addr_to_timeout(hperh, I2C_FLAG_ADD10, timeout) != OK) {
			if (hperh->error_code == I2C_ERROR_AF) {
				return ERROR;
			}
			else {
				return TIMEOUT;
			}
		}

		hperh->perh->DATA = I2C_10BIT_ADDRESS(dev_addr);
	}

	if (i2c_wait_master_addr_to_timeout(hperh, I2C_FLAG_ADDR, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF)
			return ERROR;
		else
			return TIMEOUT;
	}
	return OK;
}

/**
  * @brief  Master sends target device address followed by internal memory address for read request.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_master_req_read(i2c_handle_t *hperh, uint16_t dev_addr, uint32_t timeout)
{
	SET_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	SET_BIT(hperh->perh->CON1, I2C_CON1_START);

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_SB, RESET, timeout) != OK)
		return TIMEOUT;

	if (hperh->init.addr_mode == I2C_ADDR_7BIT) {
		hperh->perh->DATA = I2C_7BIT_ADD_READ(dev_addr);
	}
	else {
		hperh->perh->DATA = I2C_10BIT_HEADER_WRITE(dev_addr);
		if (i2c_wait_master_addr_to_timeout(hperh, I2C_FLAG_ADD10, timeout) != OK) {
			if (hperh->error_code == I2C_ERROR_AF)
				return ERROR;
			else
				return TIMEOUT;
		}

		hperh->perh->DATA = I2C_10BIT_ADDRESS(dev_addr);

		if (i2c_wait_master_addr_to_timeout(hperh, I2C_FLAG_ADDR, timeout) != OK) {
			if (hperh->error_code == I2C_ERROR_AF)
				return ERROR;
			else
				return TIMEOUT;
		}

		I2C_CLEAR_ADDRFLAG(hperh);
		SET_BIT(hperh->perh->CON1, I2C_CON1_START);

		if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_SB, RESET, timeout) != OK)
			return TIMEOUT;

		hperh->perh->DATA = I2C_10BIT_HEADER_READ(dev_addr);
	}

	if (i2c_wait_master_addr_to_timeout(hperh, I2C_FLAG_ADDR, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF)
			return ERROR;
		else
			return TIMEOUT;
	}

	I2C_CLEAR_ADDRFLAG(hperh);
	return OK;
}

/**
  * @brief  Master sends target device address followed by internal memory address for write request.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_req_mem_write(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, uint16_t add_size, uint32_t timeout)
{
	SET_BIT(hperh->perh->CON1, I2C_CON1_START);

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_SB, RESET, timeout) != OK) {
		return TIMEOUT;
	}

	hperh->perh->DATA = I2C_7BIT_ADD_WRITE(dev_addr);

	if (i2c_wait_master_addr_to_timeout(hperh, I2C_FLAG_ADDR, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF)
			return ERROR;
		else
			return TIMEOUT;
	}

	I2C_CLEAR_ADDRFLAG(hperh);

	if (i2c_wait_txe_to_timeout(hperh, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
			return ERROR;
		}
		else {
			return TIMEOUT;
		}
	}

	if (add_size == I2C_MEMADD_SIZE_8BIT) {
		hperh->perh->DATA = I2C_MEM_ADD_LSB(mem_addr);
	}
	else {
		hperh->perh->DATA = I2C_MEM_ADD_MSB(mem_addr);
		if (i2c_wait_txe_to_timeout(hperh, timeout) != OK) {
			if (hperh->error_code == I2C_ERROR_AF) {
				SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
				return ERROR;
			}
			else {
				return TIMEOUT;
			}
		}
		hperh->perh->DATA = I2C_MEM_ADD_LSB(mem_addr);
	}

	return OK;
}

/**
  * @brief  Master sends target device address followed by internal memory address for read request.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_req_mem_read(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, uint16_t add_size, uint32_t timeout)
{
	SET_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	SET_BIT(hperh->perh->CON1, I2C_CON1_START);

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_SB, RESET, timeout) != OK)
		return TIMEOUT;

	hperh->perh->DATA = I2C_7BIT_ADD_WRITE(dev_addr);

	if (i2c_wait_master_addr_to_timeout(hperh, I2C_FLAG_ADDR, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF)
			return ERROR;
		else
			return TIMEOUT;
	}

	I2C_CLEAR_ADDRFLAG(hperh);

	if (i2c_wait_txe_to_timeout(hperh, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
			return ERROR;
		}
		else {
			return TIMEOUT;
		}
	}

	if (add_size == I2C_MEMADD_SIZE_8BIT) {
		hperh->perh->DATA = I2C_MEM_ADD_LSB(mem_addr);
	}
	else {
		hperh->perh->DATA = I2C_MEM_ADD_MSB(mem_addr);

		if (i2c_wait_txe_to_timeout(hperh, timeout) != OK) {
			if (hperh->error_code == I2C_ERROR_AF) {
				SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
				return ERROR;
			}
			else {
				return TIMEOUT;
			}
		}
		hperh->perh->DATA = I2C_MEM_ADD_LSB(mem_addr);
	}

	if (i2c_wait_txe_to_timeout(hperh, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF) {
			SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
			return ERROR;
		}
		else {
			return TIMEOUT;
		}
	}

	SET_BIT(hperh->perh->CON1, I2C_CON1_START);

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_SB, RESET, timeout) != OK)
		return TIMEOUT;

	hperh->perh->DATA = I2C_7BIT_ADD_READ(dev_addr);

	if (i2c_wait_master_addr_to_timeout(hperh, I2C_FLAG_ADDR, timeout) != OK) {
		if (hperh->error_code == I2C_ERROR_AF)
			return ERROR;
		else
			return TIMEOUT;
	}

	return OK;
}

#ifdef ALD_DMA
/**
  * @brief  DMA I2C master transmit process complete callback.
  * @param  argv: I2C handle
  * @retval None
  */
static void i2c_dma_master_send_cplt(void *argv)
{
	i2c_handle_t* hperh = (i2c_handle_t*)argv;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BTF, RESET, I2C_TIMEOUT_FLAG) != OK)
		hperh->error_code |= I2C_ERROR_TIMEOUT;

	SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
	CLEAR_BIT(hperh->perh->CON2, I2C_CON2_DMAEN);

	hperh->xfer_count = 0;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;

	if (hperh->error_code != I2C_ERROR_NONE) {
		if (hperh->error_callback)
			hperh->error_callback(hperh);
	}
	else {
		if (hperh->master_tx_cplt_cbk)
			hperh->master_tx_cplt_cbk(hperh);
	}
}

/**
  * @brief  DMA I2C slave transmit process complete callback.
  * @param  argv: I2C handle
  * @retval None
  */
static void i2c_dma_slave_send_cplt(void *argv)
{
	i2c_handle_t* hperh = (i2c_handle_t*)argv;

	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_AF, RESET, I2C_TIMEOUT_FLAG) != OK)
		hperh->error_code |= I2C_ERROR_TIMEOUT;

	ald_i2c_clear_flag_status(hperh, I2C_FLAG_AF);

	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	CLEAR_BIT(hperh->perh->CON2, I2C_CON2_DMAEN);

	hperh->xfer_count = 0;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;

	if (hperh->error_code != I2C_ERROR_NONE) {
		if (hperh->error_callback)
			hperh->error_callback(hperh);
	}
	else {
		if (hperh->slave_tx_cplt_cbk)
			hperh->slave_tx_cplt_cbk(hperh);
	}
}

/**
  * @brief  DMA I2C master receive process complete callback
  * @param  argv: I2C handle
  * @retval None
  */
static void i2c_dma_master_recv_cplt(void *argv)
{
	i2c_handle_t* hperh = (i2c_handle_t*)argv;

	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
	CLEAR_BIT(hperh->perh->CON2, I2C_CON2_LDMA);
	CLEAR_BIT(hperh->perh->CON2, I2C_CON2_DMAEN);

	hperh->xfer_count = 0;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;

	if (hperh->error_code != I2C_ERROR_NONE) {
		if (hperh->error_callback)
			hperh->error_callback(hperh);
	}
	else {
		if (hperh->master_rx_cplt_cbk)
			hperh->master_rx_cplt_cbk(hperh);
	}
}

/**
  * @brief  DMA I2C slave receive process complete callback.
  * @param  argv: I2C handle
  * @retval None
  */
static void i2c_dma_slave_recv_cplt(void *argv)
{
	i2c_handle_t* hperh = (i2c_handle_t*)argv;

	if (i2c_wait_stop_to_timeout(hperh, I2C_TIMEOUT_FLAG) != OK) {
		if (hperh->error_code == I2C_ERROR_AF)
			hperh->error_code |= I2C_ERROR_AF;
		else
			hperh->error_code |= I2C_ERROR_TIMEOUT;
	}

	__I2C_CLEAR_STOPFLAG(hperh);

	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	CLEAR_BIT(hperh->perh->CON2, I2C_CON2_DMAEN);

	hperh->xfer_count = 0;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;

	if (hperh->error_code != I2C_ERROR_NONE) {
		if (hperh->error_callback)
			hperh->error_callback(hperh);
	}
	else {
		if (hperh->slave_rx_cplt_cbk)
			hperh->slave_rx_cplt_cbk(hperh);
	}
}

/**
  * @brief  DMA I2C Memory Write process complete callback
  * @param  argv: I2C handle
  * @retval None
  */
static void i2c_dma_mem_send_cplt(void *argv)
{
	i2c_handle_t* hperh = (i2c_handle_t*)argv;

 	if (i2c_wait_flag_to_timeout(hperh, I2C_FLAG_BTF, RESET, I2C_TIMEOUT_FLAG) != OK)
		hperh->error_code |= I2C_ERROR_TIMEOUT;

	SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
	CLEAR_BIT(hperh->perh->CON2, I2C_CON2_DMAEN);

	hperh->xfer_count = 0;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;

	if (hperh->error_code != I2C_ERROR_NONE) {
		if (hperh->error_callback)
			hperh->error_callback(hperh);
	}
	else {
		if (hperh->mem_tx_cplt_cbk)
			hperh->mem_tx_cplt_cbk(hperh);
	}
}

/**
  * @brief  DMA I2C Memory Read process complete callback
  * @param  argv: I2C handle
  * @retval None
  */
static void i2c_dma_mem_recv_cplt(void *argv)
{
	i2c_handle_t* hperh = (i2c_handle_t*)argv;

	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);
	SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
	CLEAR_BIT(hperh->perh->CON2, I2C_CON2_LDMA);
	CLEAR_BIT(hperh->perh->CON2, I2C_CON2_DMAEN);

	hperh->xfer_count = 0;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;

	if (hperh->error_code != I2C_ERROR_NONE) {
		if (hperh->error_callback)
			hperh->error_callback(hperh);
	}
	else {
		if (hperh->mem_rx_cplt_cbk)
			hperh->mem_rx_cplt_cbk(hperh);
	}
}
#endif

/**
  * @brief  I2C Configuration Speed function
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  i2c_clk: PCLK frequency from RCC.
  * @retval CCR Speed: Speed to set in I2C CCR Register
  */
static uint32_t i2c_configure_speed(i2c_handle_t *hperh, uint32_t i2c_clk)
{
	uint32_t tmp1 = 0;

	if (hperh->init.clk_speed <= I2C_STANDARD_MODE_MAX_CLK) {
		tmp1 = (i2c_clk / (hperh->init.clk_speed << 1));
		if ((tmp1 & I2C_CKCFG_CLKSET) < 4 )
			return 4;
		else
			return tmp1;
	}
	else {
		tmp1 = I2C_CKCFG_CLKMOD;

		if (hperh->init.duty == I2C_DUTYCYCLE_2) {
			tmp1 |= (i2c_clk / (hperh->init.clk_speed * 3)) | I2C_DUTYCYCLE_2;
			CLEAR_BIT(hperh->perh->CKCFG, I2C_CKCFG_CLKMOD_MSK);
		}
		else {
			tmp1 |= (i2c_clk / (hperh->init.clk_speed * 25)) | I2C_DUTYCYCLE_16_9;
			SET_BIT(hperh->perh->CKCFG, I2C_CKCFG_CLKMOD_MSK);
		}

		if ((tmp1 & I2C_CKCFG_CLKSET) < 1 )
			return 1;
		else
			return tmp1;
	}
}

#ifdef ALD_DMA
/**
  * @brief  DMA I2C communication error callback.
  * @param  argv: I2C handle
  * @retval None
  */
static void i2c_dma_error(void *argv)
{
	i2c_handle_t* hperh = (i2c_handle_t*)argv;

	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_ACKEN);

	hperh->xfer_count  = 0;
	hperh->state       = I2C_STATE_READY;
	hperh->mode        = I2C_MODE_NONE;
	hperh->error_code |= I2C_ERROR_DMA;

	if (hperh->error_callback)
		hperh->error_callback(hperh);
}
#endif

/**
  * @brief  This function handles I2C Communication timeout.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  flag: specifies the I2C flag to check.
  * @param  status: The new flag status (SET or RESET).
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_wait_flag_to_timeout(i2c_handle_t *hperh, i2c_flag_t flag, flag_status_t status, uint32_t timeout)
{
	uint32_t tickstart = 0;

	tickstart = ald_get_tick();

	if (status == RESET) {
		while (ald_i2c_get_flag_status(hperh, flag) == RESET) {
			if ((timeout == 0) || ((ald_get_tick() - tickstart ) > timeout)) {
				hperh->state = I2C_STATE_READY;
				__UNLOCK(hperh);
				return TIMEOUT;
			}
		}
	}
	else {
		while (ald_i2c_get_flag_status(hperh, flag) != RESET) {
			if ((timeout == 0) || ((ald_get_tick() - tickstart ) > timeout)) {
				hperh->state = I2C_STATE_READY;
				__UNLOCK(hperh);
				return TIMEOUT;
			}
		}
	}
	return OK;
}

/**
  * @brief  This function handles I2C Communication timeout for Master addressing phase.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  flag: specifies the I2C flag to check.
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_wait_master_addr_to_timeout(i2c_handle_t *hperh, i2c_flag_t flag, uint32_t timeout)
{
	uint32_t tickstart = 0;

	tickstart = ald_get_tick();
	while (ald_i2c_get_flag_status(hperh, flag) == RESET) {
		if (ald_i2c_get_flag_status(hperh, I2C_FLAG_AF) == SET) {
			SET_BIT(hperh->perh->CON1, I2C_CON1_STOP);
			ald_i2c_clear_flag_status(hperh, I2C_FLAG_AF);

			hperh->error_code = I2C_ERROR_AF;
			hperh->state = I2C_STATE_READY;
			__UNLOCK(hperh);
			return ERROR;
		}

		if (timeout != I2C_MAX_DELAY) {
			if ((timeout == 0) || ((ald_get_tick() - tickstart ) > timeout)) {
				hperh->state = I2C_STATE_READY;
				__UNLOCK(hperh);
				return TIMEOUT;
			}
		}
	}
	return OK;
}

/**
  * @brief  This function handles I2C Communication timeout for specific usage of TXE flag.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_wait_txe_to_timeout(i2c_handle_t *hperh, uint32_t timeout)
{
	uint32_t tickstart = ald_get_tick();

	while (ald_i2c_get_flag_status(hperh, I2C_FLAG_TXE) == RESET) {
		if (i2c_is_ack_failed(hperh) != OK)
			return ERROR;

		if (timeout != I2C_MAX_DELAY) {
			if ((timeout == 0) || ((ald_get_tick() - tickstart) > timeout)) {
				hperh->error_code |= I2C_ERROR_TIMEOUT;
				hperh->state = I2C_STATE_READY;
				__UNLOCK(hperh);
				return TIMEOUT;
			}
		}
	}
	return OK;
}

/**
  * @brief  This function handles I2C Communication timeout for specific usage of BTF flag.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_wait_btf_to_timeout(i2c_handle_t *hperh, uint32_t timeout)
{
	uint32_t tickstart = ald_get_tick();

	while (ald_i2c_get_flag_status(hperh, I2C_FLAG_BTF) == RESET) {
		if (i2c_is_ack_failed(hperh) != OK) {
			return ERROR;
		}

		if (timeout != I2C_MAX_DELAY) {
			if ((timeout == 0) || ((ald_get_tick() - tickstart) > timeout)) {
				hperh->error_code |= I2C_ERROR_TIMEOUT;
				hperh->state = I2C_STATE_READY;
				__UNLOCK(hperh);
				return TIMEOUT;
			}
		}
	}
	return OK;
}

/**
  * @brief  This function handles I2C Communication timeout for specific usage of STOP flag.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_wait_stop_to_timeout(i2c_handle_t *hperh, uint32_t timeout)
{
	uint32_t tickstart = 0x00;
	tickstart = ald_get_tick();

	while (ald_i2c_get_flag_status(hperh, I2C_FLAG_STOPF) == RESET) {
		if (i2c_is_ack_failed(hperh) != OK)
			return ERROR;

		if ((timeout == 0) || ((ald_get_tick() - tickstart) > timeout)) {
			hperh->error_code |= I2C_ERROR_TIMEOUT;
			hperh->state = I2C_STATE_READY;
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}
	return OK;
}

/**
  * @brief  This function handles I2C Communication timeout for specific usage of RXNE flag.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_wait_rxne_to_timeout(i2c_handle_t *hperh, uint32_t timeout)
{
	uint32_t tickstart = 0x00;
	tickstart = ald_get_tick();

	while (ald_i2c_get_flag_status(hperh, I2C_FLAG_RXNE) == RESET) {
		if (ald_i2c_get_flag_status(hperh, I2C_FLAG_STOPF) == SET) {
			ald_i2c_clear_flag_status(hperh, I2C_FLAG_STOPF);
			hperh->error_code = I2C_ERROR_NONE;
			hperh->state = I2C_STATE_READY;
			__UNLOCK(hperh);
			return ERROR;
		}

		if ((timeout == 0) || ((ald_get_tick() - tickstart) > timeout)) {
			hperh->error_code |= I2C_ERROR_TIMEOUT;
			hperh->state = I2C_STATE_READY;
			__UNLOCK(hperh);
			return TIMEOUT;
		}
	}
	return OK;
}

/**
  * @brief  This function handles Acknowledge failed detection during an I2C Communication.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2c_is_ack_failed(i2c_handle_t *hperh)
{
	if (ald_i2c_get_flag_status(hperh, I2C_FLAG_AF) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_FLAG_AF);
		hperh->error_code = I2C_ERROR_AF;
		hperh->state = I2C_STATE_READY;
		__UNLOCK(hperh);

		return ERROR;
	}

	return OK;
}
/**
  * @}
  */

#endif /* ALD_I2C */
/**
  * @}
  */

/**
  * @}
  */
