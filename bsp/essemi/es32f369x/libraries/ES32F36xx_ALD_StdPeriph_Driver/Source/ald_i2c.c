/**
  *********************************************************************************
  *
  * @file    ald_i2c.c
  * @brief   I2C module driver.
  *
  * @version V1.0
  * @date    15 Nov 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          15 Nov 2019     AE Team         The first version
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
  *
  @verbatim
 ===============================================================================
                       ##### How to use this driver #####
 ===============================================================================
 [..]
   The I2C driver can be used as follows:

   (#) Declare a i2c_handle_t handle structure, for example:
       i2c_handle_t  hperh;

   (#) Configure the Communication Speed, Addressing mode, Own Address1,
       Dual Addressing mode, Own Address2, General call and Nostretch mode in the hperh init structure.

   (#) Initialize the I2C registers by calling the ald_i2c_init().

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

     (+) __I2C_ENABLE: Enable the I2C peripheral
     (+) __I2C_DISABLE: Disable the I2C peripheral
     (+) I2C_GET_FLAG: Check whether the specified I2C flag is set or not
     (+) I2C_ENABLE_IT: Enable the specified I2C interrupt
     (+) I2C_DISABLE_IT: Disable the specified I2C interrupt
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

#include "ald_conf.h"

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

#define I2C_TIMEOUT_FLAG          (10)
#define I2C_TIMEOUT_ADDR_SLAVE    (10)
#define I2C_TIMEOUT_BUSY_FLAG     (10)
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
static ald_status_t i2c_req_mem_read(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                                     uint16_t add_size, uint32_t timeout);
#endif
static ald_status_t i2c_master_req_write(i2c_handle_t *hperh, uint16_t dev_addr, uint32_t timeout);
static ald_status_t i2c_master_req_read(i2c_handle_t *hperh, uint16_t dev_addr, uint32_t timeout);
static ald_status_t i2c_req_mem_write(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                                      uint16_t add_size, uint32_t timeout);
static ald_status_t i2c_wait_flag_change_to_timeout(i2c_handle_t *hperh, uint32_t flag,
                                                flag_status_t status, uint32_t timeout);
static ald_status_t i2c_wait_master_addr_to_timeout(i2c_handle_t *hperh, uint32_t flag, uint32_t timeout);
static ald_status_t i2c_wait_txe_to_timeout(i2c_handle_t *hperh, uint32_t timeout);
static ald_status_t i2c_wait_rxne_to_timeout(i2c_handle_t *hperh, uint32_t timeout);
static ald_status_t i2c_master_send_tc(i2c_handle_t *hperh);
static ald_status_t i2c_master_send_txe(i2c_handle_t *hperh);
static ald_status_t i2c_master_recv_tc(i2c_handle_t *hperh);
static ald_status_t i2c_master_recv_rxne(i2c_handle_t *hperh);
static ald_status_t i2c_slave_send_txe(i2c_handle_t *hperh);
static ald_status_t i2c_slave_recv_rxne(i2c_handle_t *hperh);
static ald_status_t i2c_slave_stopf(i2c_handle_t *hperh);

/**
 * @}
 */

/** @defgroup I2C_Public_Functions I2C Public functions
 * @{
 */

/** @defgroup I2C_Public_Functions_Group1 Initialization and de-initialization functions
 * @brief     Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          de-initialiaze the I2Cx peripheral:

      (+) Call the function ald_i2c_init() to configure the selected device with
          the selected configuration:
        (++) Communication Speed
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
 * @brief  I2C Configuration Speed function.      
 * @param  hperh: Pointer to a i2c_handle_t structure that contains.
 *                the configuration information for the I2C speed.
 * @param  clk: I2C Peripheral bus clock
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t i2c_speed_init(i2c_handle_t *hperh, uint32_t clk)
{
	int32_t t_scl, t_pre, tmp;

	if (hperh->init.module == I2C_MODULE_SLAVE) {
		hperh->init.clk_speed = 450000UL;
	}

	if (hperh->init.clk_speed <= 100000UL) {
		tmp = clk / 4000000UL;
		clk = (tmp >= 16UL) ? (clk >> 4UL) : 4000000UL;
	}
	else {
		tmp = clk / 8000000UL;
		clk = (tmp >= 16UL) ? (clk >> 4UL) : 8000000UL;
	}

	tmp = tmp >= 16UL ? 15UL : tmp;
	MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_PRESC_MSK, tmp << I2C_TIMINGR_PRESC_POSS);

	t_scl = 1000000000 / hperh->init.clk_speed;
	t_pre = 1000000000 / clk;

	tmp = (t_scl * 10) / (t_pre << 1UL);
	tmp = (tmp % 10) >= 5 ? (tmp / 10 + 1) : tmp / 10;
	tmp = tmp >= 255UL ? 255UL : tmp;
	/* SCLDEL+1+SDADEL+0+SCLH+1 */
	if ((long)(t_scl - ((tmp + 3UL) * t_pre)) < 0)
		return ERROR;

	MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_SCLL_MSK, (tmp - 1UL) << I2C_TIMINGR_SCLL_POSS);	
	if (hperh->init.clk_speed > 100000UL) {		
		if ((tmp - 1UL) > 3UL) {
			MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_SCLDEL_MSK, ((tmp - 1UL) / 3UL) << I2C_TIMINGR_SCLDEL_POSS);
			MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_SDADEL_MSK, ((((tmp - 1UL) / 3UL) >= 3) ? 3 : (((tmp - 1UL) / 3UL) % 3)) << I2C_TIMINGR_SDADEL_POSS);		
		}
 		else {
			MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_SCLDEL_MSK, 1UL << I2C_TIMINGR_SCLDEL_POSS);
			MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_SDADEL_MSK, 1UL << I2C_TIMINGR_SDADEL_POSS);
		}                
	}
	else {
		MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_SDADEL_MSK, 2UL << I2C_TIMINGR_SDADEL_POSS);
		MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_SCLDEL_MSK, 4UL << I2C_TIMINGR_SCLDEL_POSS);
	}

	tmp = t_scl - (tmp + READ_BITS(hperh->perh->TIMINGR, I2C_TIMINGR_SCLDEL_MSK, I2C_TIMINGR_SCLDEL_POSS) + \
                             READ_BITS(hperh->perh->TIMINGR, I2C_TIMINGR_SDADEL_MSK, I2C_TIMINGR_SDADEL_POSS) + 1UL) * t_pre;
	if (tmp < 0)
		return ERROR;

	tmp = (tmp * 10) / t_pre;
	tmp = (tmp % 10) >= 5 ? (tmp / 10 + 1) : tmp / 10;
	tmp = tmp >= 255UL ? 255UL : tmp;
	/* tscll >= 3*tsclh */
	tmp = (tmp - 1) <= (READ_BITS(hperh->perh->TIMINGR, I2C_TIMINGR_SCLL_MSK, I2C_TIMINGR_SCLL_POSS) / 3) ? (READ_BITS(hperh->perh->TIMINGR, I2C_TIMINGR_SCLL_MSK, I2C_TIMINGR_SCLL_POSS) / 3) + 1: tmp;
	MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_SCLH_MSK, (tmp - 1UL) << I2C_TIMINGR_SCLH_POSS);

	return OK;
}
/**
 * @brief  Initializes the I2C according to the specified parameters
 *         in the i2c_init_t and initialize the associated handle.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_init(i2c_handle_t *hperh)
{
	uint32_t freqrange = ald_cmu_get_pclk1_clock();

	if (hperh == NULL)
		return ERROR;

	/* Check the parameters */
	assert_param(IS_I2C_CLOCK_SPEED(hperh->init.clk_speed));
	assert_param(IS_I2C_ADDRESSING_MODE(hperh->init.addr_mode));
	assert_param(IS_I2C_GENERAL_CALL(hperh->init.general_call));
	assert_param(IS_I2C_NO_STRETCH(hperh->init.no_stretch));
	assert_param(IS_I2C_MODULE(hperh->init.module));

	if (hperh->state == I2C_STATE_RESET)
		hperh->lock = UNLOCK;

	hperh->state = I2C_STATE_BUSY;

	I2C_DISABLE(hperh);

	if (OK != i2c_speed_init(hperh, freqrange))
		return ERROR;

	MODIFY_REG(hperh->perh->CON1, I2C_CON1_NOSTRETCH_MSK, (hperh->init.no_stretch) << I2C_CON1_NOSTRETCH_POS);
	MODIFY_REG(hperh->perh->CON1, I2C_CON1_GCEN_MSK, (hperh->init.general_call) << I2C_CON1_GCEN_POS);

	if (hperh->init.dual_addr == I2C_DUALADDR_ENABLE) {
		CLEAR_BIT(hperh->perh->ADDR1, I2C_ADDR1_OA1EN_MSK);
		MODIFY_REG(hperh->perh->ADDR1, I2C_ADDR1_OA1_MSK, (hperh->init.own_addr1 & 0x3FF) << I2C_ADDR1_OA1_POSS);
		SET_BIT(hperh->perh->ADDR1, I2C_ADDR1_OA1EN_MSK);

		CLEAR_BIT(hperh->perh->ADDR2, I2C_ADDR2_OA2EN_MSK);
		MODIFY_REG(hperh->perh->ADDR2, I2C_ADDR2_OA2_MSK, (hperh->init.own_addr2 & 0x7F) << I2C_ADDR2_OA2_POSS);
		SET_BIT(hperh->perh->ADDR2, I2C_ADDR2_OA2EN_MSK);
	} else {
		if (hperh->init.addr_mode == I2C_ADDR_10BIT) {
			CLEAR_BIT(hperh->perh->ADDR1, I2C_ADDR1_OA1EN_MSK);
			SET_BIT(hperh->perh->ADDR1, I2C_ADDR1_OA1MODE_MSK);
			MODIFY_REG(hperh->perh->ADDR1, I2C_ADDR1_OA1_MSK, (hperh->init.own_addr1 & 0x3FF) << I2C_ADDR1_OA1_POSS);
			SET_BIT(hperh->perh->ADDR1, I2C_ADDR1_OA1EN_MSK);
		}
		else {
			CLEAR_BIT(hperh->perh->ADDR2, I2C_ADDR2_OA2EN_MSK);
			MODIFY_REG(hperh->perh->ADDR2, I2C_ADDR2_OA2_MSK, (hperh->init.own_addr2 & 0x7F) << I2C_ADDR2_OA2_POSS);
			SET_BIT(hperh->perh->ADDR2, I2C_ADDR2_OA2EN_MSK);
		}
	}

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

	I2C_DISABLE(hperh);

	hperh->error_code = I2C_ERROR_NONE;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;

	__UNLOCK(hperh);

	WRITE_REG(hperh->perh->CON1, 0);
	WRITE_REG(hperh->perh->CON2, 0);
	WRITE_REG(hperh->perh->ADDR1, 0);
	WRITE_REG(hperh->perh->ADDR2, 0);
	WRITE_REG(hperh->perh->TIMINGR, 0);
	WRITE_REG(hperh->perh->TIMEOUTR, 0);
	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);
	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);
	WRITE_REG(hperh->perh->IDR, I2C_FLAG_MASK);
	WRITE_REG(hperh->perh->ICR, I2C_FLAG_MASK);

	I2C_ENABLE(hperh);

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
                                 uint32_t size, uint32_t timeout)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	i2c_master_req_write(hperh, dev_addr, timeout);

	if (size <= 0xFF) {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
	}
	else {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
		SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
	}

	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);
	SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

	while (size > 0) {
		hperh->perh->TXDATA  = (*buf++);
		size--;
		hperh->xfer_count++;

		if (i2c_wait_txe_to_timeout(hperh, timeout) != OK)
			goto ERROR;

		if (((hperh->xfer_count % 0xFF) == 0) && (READ_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK))) {
			if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_TCR, RESET, I2C_TIMEOUT_FLAG) == OK) {
				if (size > 0xFF) {
					MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
				}
				else {
					MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
					CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
				}
			}
			else {
				goto ERROR;
			}
		}
	}

	if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK) == SET)
		goto SUCCESS;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_TC, RESET, I2C_TIMEOUT_FLAG) == OK) {
		SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
		goto SUCCESS;
	}
	else {
		goto ERROR;
	}

ERROR:
	SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
	__UNLOCK(hperh);

	return ERROR;

SUCCESS:
	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
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
 * @retval Status, see @ref ald_status_t
 */
  ald_status_t ald_i2c_master_recv(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf,
                                uint32_t size, uint32_t timeout)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	i2c_master_req_read(hperh, dev_addr, timeout);

	if (size <= 0xFF) {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
	}
	else {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
		SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
	}

	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);
	SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

	while (size > 0) {
		if (i2c_wait_rxne_to_timeout(hperh, timeout) != OK)
			goto ERROR;

		(*buf++) = hperh->perh->RXDATA;
		size--;
		hperh->xfer_count++;

		if (((hperh->xfer_count % 0xFF) == 0) && (READ_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK))) {
			if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_TCR, RESET, I2C_TIMEOUT_FLAG) == OK) {
				if (size > 0xFF) {
					MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
				}
				else {
					MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
					CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
				}
			}
			else {
				goto ERROR;
			}
		}
	}

	if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK))
		goto SUCCESS;

	SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
		goto SUCCESS;

ERROR:
	SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
	__UNLOCK(hperh);

	return ERROR;

SUCCESS:
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
ald_status_t ald_i2c_slave_send(i2c_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout)
{
	uint8_t i = 0;

	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_SLAVE;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);
	MODIFY_REG(hperh->perh->FCON, I2C_FCON_TXFTH_MSK, 0x03 << I2C_FCON_TXFTH_POSS);

	for (i = 0; i < 16; i++) {
		if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_TXF, SET, timeout) != OK)
			goto ERROR;

		hperh->perh->TXDATA = (*buf++);
		--size;
		hperh->xfer_count++;

		if (size == 0)
			break;
	}

	if (i2c_wait_master_addr_to_timeout(hperh, I2C_IT_ADDR, timeout) == ERROR)
		goto ERROR;

	while (size > 0) {
		if (i2c_wait_txe_to_timeout(hperh, timeout) == ERROR)
			goto ERROR;

		for (i = 0; i < 8; i++) {
			if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_TXF, SET, timeout) != OK)
				goto ERROR;

			hperh->perh->TXDATA = (*buf++);
			--size;
			hperh->xfer_count++;

			if (size == 0)
				break;
		}
	}

	goto SUCCESS;

ERROR:
	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
	__UNLOCK(hperh);

	return ERROR;

SUCCESS:
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
ald_status_t ald_i2c_slave_recv(i2c_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_SLAVE;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_count = 0;
	hperh->xfer_size  = size;

	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);

	if (i2c_wait_master_addr_to_timeout(hperh, I2C_IT_ADDR, timeout) == ERROR)
		goto ERROR;

	while (size > 0) {
		if (i2c_wait_rxne_to_timeout(hperh, timeout) == ERROR)
			goto ERROR;

		SET_BIT(hperh->perh->CON2, I2C_CON2_ACK_UPD_MSK);
		(*buf++) = hperh->perh->RXDATA;
		--size;
		hperh->xfer_count++;
	}

	goto SUCCESS;

ERROR:
	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
	__UNLOCK(hperh);

	return ERROR;

SUCCESS:
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
ald_status_t ald_i2c_master_send_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint32_t size)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	i2c_master_req_write(hperh, dev_addr, I2C_TIMEOUT_FLAG);

	if (size <= 0xFF) {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
	}
	else {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
		SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
	}

	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);

	I2C_CLEAR_IT(hperh , I2C_IT_TXTH);
	I2C_CLEAR_IT(hperh , I2C_IT_NACK);
	I2C_CLEAR_IT(hperh , I2C_IT_TC);
	I2C_CLEAR_IT(hperh , I2C_IT_TCR);

	SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

	I2C_DISABLE_IT(hperh, I2C_FLAG_MASK);
	I2C_ENABLE_IT(hperh, I2C_IT_TXTH | I2C_IT_NACK | I2C_IT_TC | I2C_IT_TCR);

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
ald_status_t ald_i2c_master_recv_by_it(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint32_t size)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	i2c_master_req_read(hperh, dev_addr, I2C_TIMEOUT_FLAG) ;

	if (size <= 0xFF) {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
	}
	else {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
		SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
	}

	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);

	I2C_CLEAR_IT(hperh , I2C_IT_RXTH);
	I2C_CLEAR_IT(hperh , I2C_IT_TCR);
	I2C_CLEAR_IT(hperh , I2C_IT_TC);

	I2C_DISABLE_IT(hperh, I2C_FLAG_MASK);
	I2C_ENABLE_IT(hperh, I2C_IT_RXTH | I2C_IT_TCR | I2C_IT_TC);

	SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

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
ald_status_t ald_i2c_slave_send_by_it(i2c_handle_t *hperh, uint8_t *buf, uint32_t size)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_SLAVE;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);

	I2C_CLEAR_IT(hperh , I2C_IT_TXTH);
	I2C_CLEAR_IT(hperh , I2C_IT_ADDR);
	I2C_CLEAR_IT(hperh , I2C_IT_NACK);
	I2C_CLEAR_IT(hperh , I2C_IT_STOP);

	I2C_DISABLE_IT(hperh, I2C_FLAG_MASK);
	I2C_ENABLE_IT(hperh, I2C_IT_ADDR | I2C_IT_NACK | I2C_IT_STOP | I2C_IT_TXTH);

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
ald_status_t ald_i2c_slave_recv_by_it(i2c_handle_t *hperh, uint8_t *buf, uint32_t size)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_SLAVE;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);

	I2C_CLEAR_IT(hperh , I2C_IT_RXTH);
	I2C_CLEAR_IT(hperh , I2C_IT_ADDR);
	I2C_CLEAR_IT(hperh , I2C_IT_STOP);

	I2C_DISABLE_IT(hperh, I2C_FLAG_MASK);
	I2C_ENABLE_IT(hperh, I2C_IT_RXTH | I2C_IT_ADDR | I2C_IT_STOP);

	return OK;
}

#ifdef ALD_DMA
/**
 * @brief  Transmit in master mode an amount of data in non-blocking mode with DMA
 * @note   The maximum amount of data to be sent is 0xFF.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  dev_addr: Target device address
 * @param  buf: Pointer to data buffer
 * @param  size: Amount of data to be sent (maximum is 0xFF)
 * @param  channel: DMA channel as I2C transmit
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_master_send_by_dma(i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf,
                                    uint8_t size, uint8_t channel)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	if (size >= 0xFF)
		size = 0xFF;

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	if (hperh->hdmatx.perh == NULL)
		hperh->hdmatx.perh = DMA0;

	hperh->hdmatx.cplt_cbk = i2c_dma_master_send_cplt;
	hperh->hdmatx.cplt_arg = hperh;
	hperh->hdmatx.err_cbk  = i2c_dma_error;
	hperh->hdmatx.err_arg  = hperh;

	MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
	hperh->hdmatx.config.size = size;

	ald_dma_config_struct(&hperh->hdmatx.config);
	hperh->hdmatx.config.burst      = ENABLE;
	hperh->hdmatx.config.src     	 = (void *)hperh->p_buff;
	hperh->hdmatx.config.dst     	 = (void *)&hperh->perh->TXDATA;
	hperh->hdmatx.config.data_width = DMA_DATA_SIZE_BYTE;
	hperh->hdmatx.config.src_inc 	 = DMA_DATA_INC_BYTE;
	hperh->hdmatx.config.dst_inc 	 = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel    	 = hperh->perh == I2C0 ? DMA_MSEL_I2C0 : DMA_MSEL_I2C1;
	hperh->hdmatx.config.msigsel 	 = DMA_MSIGSEL_I2C_TXEMPTY;
	hperh->hdmatx.config.channel 	 = channel;
	ald_dma_config_basic(&hperh->hdmatx);

	i2c_master_req_write(hperh, dev_addr, I2C_TIMEOUT_FLAG);

	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);
	SET_BIT(hperh->perh->CON1, I2C_CON1_TXDMAEN_MSK);
	SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

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
                                    uint8_t size, uint8_t channel)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	if (size >= 0xFF)
		size = 0xFF;

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	if (hperh->hdmarx.perh == NULL)
		hperh->hdmarx.perh = DMA0;

	hperh->hdmarx.cplt_cbk = i2c_dma_master_recv_cplt;
	hperh->hdmarx.cplt_arg = (void *)hperh;
	hperh->hdmarx.err_cbk  = i2c_dma_error;
	hperh->hdmarx.err_arg  = (void *)hperh;

	MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
	hperh->hdmarx.config.size    	 = size;

	ald_dma_config_struct(&hperh->hdmarx.config);
	hperh->hdmarx.config.src     	 = (void *)&hperh->perh->RXDATA;
	hperh->hdmarx.config.dst     	 = (void *)buf;
	hperh->hdmatx.config.data_width = DMA_DATA_SIZE_BYTE;
	hperh->hdmarx.config.src_inc 	 = DMA_DATA_INC_NONE;
	hperh->hdmarx.config.dst_inc 	 = DMA_DATA_INC_BYTE;
	hperh->hdmarx.config.msel    	 = hperh->perh == I2C0 ? DMA_MSEL_I2C0 : DMA_MSEL_I2C1;
	hperh->hdmarx.config.msigsel 	 = DMA_MSIGSEL_I2C_RNR;
	hperh->hdmarx.config.channel 	 = channel;
	ald_dma_config_basic(&hperh->hdmarx);

	i2c_master_req_read(hperh, dev_addr, I2C_TIMEOUT_FLAG);

	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);
	SET_BIT(hperh->perh->CON1, I2C_CON1_RXDMAEN_MSK);
	SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

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
ald_status_t ald_i2c_slave_send_by_dma(i2c_handle_t *hperh, uint8_t *buf, uint8_t size, uint8_t channel)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_SLAVE;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	if (size >= 0xFF)
		size = 0xFF;

	if (hperh->hdmatx.perh == NULL)
		hperh->hdmatx.perh = DMA0;

	hperh->hdmatx.cplt_cbk = i2c_dma_slave_send_cplt;
	hperh->hdmatx.cplt_arg = hperh;
	hperh->hdmatx.err_cbk  = i2c_dma_error;
	hperh->hdmatx.err_arg  = hperh;

 	ald_dma_config_struct(&hperh->hdmatx.config);
	hperh->hdmatx.config.burst      = ENABLE;
	hperh->hdmatx.config.src     	= (void *)buf;
	hperh->hdmatx.config.dst     	= (void *)&hperh->perh->TXDATA;
	hperh->hdmatx.config.size    	= size;
	hperh->hdmatx.config.data_width = DMA_DATA_SIZE_BYTE;
	hperh->hdmatx.config.src_inc 	= DMA_DATA_INC_BYTE;
	hperh->hdmatx.config.dst_inc 	= DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel    	= hperh->perh == I2C0 ? DMA_MSEL_I2C0 : DMA_MSEL_I2C1;
	hperh->hdmatx.config.msigsel 	= DMA_MSIGSEL_I2C_TXEMPTY;
	hperh->hdmatx.config.channel 	= channel;
	ald_dma_config_basic(&hperh->hdmatx);

	if (i2c_wait_master_addr_to_timeout(hperh, I2C_IT_ADDR, I2C_TIMEOUT_ADDR_SLAVE) == ERROR) {
		hperh->state = I2C_STATE_READY;
		hperh->mode  = I2C_MODE_NONE;
		__UNLOCK(hperh);

		return ERROR;
	}

	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);
	SET_BIT(hperh->perh->CON1, I2C_CON1_TXDMAEN_MSK);

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
ald_status_t ald_i2c_slave_recv_by_dma(i2c_handle_t *hperh, uint8_t *buf, uint8_t size, uint8_t channel)
{
	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_SLAVE;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	if (size >= 0xFF)
		size = 0xFF;

	if (hperh->hdmarx.perh == NULL)
		hperh->hdmarx.perh = DMA0;

	hperh->hdmarx.cplt_cbk = i2c_dma_slave_recv_cplt;
	hperh->hdmarx.cplt_arg = (void *)hperh;
	hperh->hdmarx.err_cbk  = i2c_dma_error;
	hperh->hdmarx.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdmarx.config);
	hperh->hdmarx.config.src     	= (void *)&hperh->perh->RXDATA;
	hperh->hdmarx.config.dst     	= (void *)buf;
	hperh->hdmarx.config.size    	= size;
	hperh->hdmatx.config.data_width = DMA_DATA_SIZE_BYTE;
	hperh->hdmarx.config.src_inc 	= DMA_DATA_INC_NONE;
	hperh->hdmarx.config.dst_inc 	= DMA_DATA_INC_BYTE;
	hperh->hdmarx.config.msel    	= hperh->perh == I2C0 ? DMA_MSEL_I2C0 : DMA_MSEL_I2C1;
	hperh->hdmarx.config.msigsel 	= DMA_MSIGSEL_I2C_RNR;
	hperh->hdmarx.config.channel 	= channel;
	ald_dma_config_basic(&hperh->hdmarx);

	if (i2c_wait_master_addr_to_timeout(hperh, I2C_IT_ADDR, I2C_TIMEOUT_ADDR_SLAVE) == ERROR) {
		hperh->state = I2C_STATE_READY;
		hperh->mode  = I2C_MODE_NONE;
		__UNLOCK(hperh);

		return ERROR;
	}

	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);
	SET_BIT(hperh->perh->CON1, I2C_CON1_RXDMAEN_MSK);

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
                           i2c_addr_size_t add_size, uint8_t *buf, uint32_t size, uint32_t timeout)
{
	uint32_t nbyte = 0;

	assert_param(IS_I2C_MEMADD_size(add_size));

	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_MEM;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	nbyte = (add_size == I2C_MEMADD_SIZE_8BIT) ? 1 : 2;
	MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, nbyte << I2C_CON2_NBYTES_POSS);
	SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);
	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);

	if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, timeout) != OK)
		goto ERROR;

	if (size <= 0xFF) {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
	}
	else {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
		SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
	}

	while (size > 0) {
		hperh->perh->TXDATA = (*buf++);
		--size;
		hperh->xfer_count++;

		if (((hperh->xfer_count % 0xFF) == 0) && (READ_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK))) {
			if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_TCR, RESET, I2C_TIMEOUT_FLAG) == OK) {
				if (size > 0xFF) {
					MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
				}
				else {
					MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
					CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
				}
			}
			else {
				goto ERROR;
			}
		}

		if (i2c_wait_txe_to_timeout(hperh, timeout) != OK)
			goto ERROR;
	}

	if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK))
		goto SUCCESS;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_TC, RESET, timeout))
		goto ERROR;

	SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
		goto SUCCESS;

ERROR:
	SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
	__UNLOCK(hperh);

	return ERROR;

SUCCESS:
	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
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
                          uint8_t *buf, uint32_t size, uint32_t timeout)
{
	uint32_t nbyte = 0;

	assert_param(IS_I2C_MEMADD_size(add_size));

	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_MEM;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->xfer_count = 0;
	hperh->xfer_size  = size;

	nbyte = (add_size == I2C_MEMADD_SIZE_8BIT) ? 1 : 2;
	MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, nbyte << I2C_CON2_NBYTES_POSS);
	SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);
	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);

	if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, timeout) != OK)
		return ERROR;

	if (size <= 0xFF) {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
	}
	else {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
		SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
	}

	SET_BIT(hperh->perh->CON2, I2C_CON2_RD_WRN_MSK);
	SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

	while (size > 0) {
		if (i2c_wait_rxne_to_timeout(hperh, timeout) != OK)
			goto ERROR;

		(*buf++) = hperh->perh->RXDATA;
		size--;
		hperh->xfer_count++;

		if (((hperh->xfer_count % 0xFF) == 0) && (READ_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK))) {
			if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_TCR, RESET, timeout) == OK) {
				if (size > 0xFF) {
					MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
				}
				else {
					MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
					CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
				}
			}
			else {
				goto ERROR;
			}
		}
	}

	if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK))
		goto SUCCESS;

	SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
		goto SUCCESS;

ERROR:
	SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
	__UNLOCK(hperh);

	return ERROR;

SUCCESS:
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
                              i2c_addr_size_t add_size, uint8_t *buf, uint32_t size)
{
	uint32_t nbyte = 0;

	assert_param(IS_I2C_MEMADD_size(add_size));

	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_MEM;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	nbyte = (add_size == I2C_MEMADD_SIZE_8BIT) ? 1 : 2;
	MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, nbyte << I2C_CON2_NBYTES_POSS);
	SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);
	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);

	if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, I2C_TIMEOUT_FLAG) != OK) {
		SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
		hperh->state = I2C_STATE_READY;
		hperh->mode  = I2C_MODE_NONE;
		__UNLOCK(hperh);

		return ERROR;
	}
	
	if (size <= 0xFF) {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
	}
	else {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
		SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
	}
	
	I2C_CLEAR_IT(hperh , I2C_IT_TXTH);
	I2C_CLEAR_IT(hperh , I2C_IT_NACK);
	I2C_CLEAR_IT(hperh , I2C_IT_TC);
	I2C_CLEAR_IT(hperh , I2C_IT_TCR);

	hperh->perh->TXDATA = (*hperh->p_buff++);
	hperh->xfer_count++;

	I2C_DISABLE_IT(hperh, I2C_FLAG_MASK);
	I2C_ENABLE_IT(hperh, I2C_IT_TXTH | I2C_IT_NACK | I2C_IT_TC | I2C_IT_TCR);

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
                             i2c_addr_size_t add_size, uint8_t *buf, uint32_t size)
{
	uint32_t nbyte = 0;

	assert_param(IS_I2C_MEMADD_size(add_size));

	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_TYPE(hperh->perh));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_MEM;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	nbyte = (add_size == I2C_MEMADD_SIZE_8BIT) ? 1 : 2;
	MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, nbyte << I2C_CON2_NBYTES_POSS);
	SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);
	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);

	if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, I2C_TIMEOUT_FLAG) != OK) {
		SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
		hperh->state = I2C_STATE_READY;
		hperh->mode  = I2C_MODE_NONE;
		__UNLOCK(hperh);

		return ERROR;
	}

	if (size <= 0xFF) {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
	}
	else {
		MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
		SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
	}

	I2C_CLEAR_IT(hperh , I2C_IT_RXTH);
	I2C_CLEAR_IT(hperh , I2C_IT_TC);
	I2C_CLEAR_IT(hperh , I2C_IT_TCR);

	I2C_ENABLE_IT(hperh, I2C_IT_RXTH | I2C_IT_TC | I2C_IT_TCR);

	SET_BIT(hperh->perh->CON2, I2C_CON2_RD_WRN_MSK);
	SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

	return OK;
}

#ifdef ALD_DMA

/**
  * @brief  Write an amount of data in non-blocking mode with DMA to a specific memory address
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address(Maxsiz 0xFF)
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel
   * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_write_by_dma(i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, i2c_addr_size_t add_size,
                               uint8_t *buf, uint8_t size, uint8_t channel)
{
	uint32_t nbyte = 0;

	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_MEMADD_size(add_size));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_TX;
	hperh->mode       = I2C_MODE_MASTER;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = 0;

	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);
	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);

	nbyte = (add_size == I2C_MEMADD_SIZE_8BIT) ? 1 : 2;
	MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, nbyte << I2C_CON2_NBYTES_POSS);
	SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

	if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, I2C_TIMEOUT_FLAG) != OK) {
		SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
		hperh->state = I2C_STATE_READY;
		hperh->mode  = I2C_MODE_NONE;
		__UNLOCK(hperh);

		return ERROR;
	}

	if (hperh->hdmatx.perh == NULL)
		hperh->hdmatx.perh = DMA0;

	hperh->hdmatx.cplt_cbk = i2c_dma_mem_send_cplt;
	hperh->hdmatx.cplt_arg = hperh;
	hperh->hdmatx.err_cbk  = i2c_dma_error;
	hperh->hdmatx.err_arg  = hperh;

	ald_dma_config_struct(&hperh->hdmatx.config);
	hperh->hdmatx.config.burst      = ENABLE;
	hperh->hdmatx.config.src        = (void *)hperh->p_buff;
	hperh->hdmatx.config.dst     	= (void *)&hperh->perh->TXDATA;
	hperh->hdmatx.config.size       = size;
	hperh->hdmatx.config.data_width = DMA_DATA_SIZE_BYTE;
	hperh->hdmatx.config.src_inc 	= DMA_DATA_INC_BYTE;
	hperh->hdmatx.config.dst_inc 	= DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel    	= hperh->perh == I2C0 ? DMA_MSEL_I2C0 : DMA_MSEL_I2C1;
	hperh->hdmatx.config.msigsel 	= DMA_MSIGSEL_I2C_TXEMPTY;
	hperh->hdmatx.config.channel 	= channel;
	ald_dma_config_basic(&hperh->hdmatx);

	CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
	MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
	SET_BIT(hperh->perh->CON1, I2C_CON1_TXDMAEN_MSK);

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
                              uint8_t *buf, uint8_t size, uint8_t channel)
{
	uint32_t nbyte = 0;

	if (hperh->state != I2C_STATE_READY)
		return BUSY;

	if ((buf == NULL) || (size == 0))
		return  ERROR;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != OK)
		return BUSY;

	assert_param(IS_I2C_MEMADD_size(add_size));
	__LOCK(hperh);

	hperh->state      = I2C_STATE_BUSY_RX;
	hperh->mode       = I2C_MODE_MEM;
	hperh->error_code = I2C_ERROR_NONE;
	hperh->p_buff     = buf;
	hperh->xfer_size  = size;
	hperh->xfer_count = size;

	SET_BIT(hperh->perh->FCON, I2C_FCON_TXFRST_MSK);
	SET_BIT(hperh->perh->FCON, I2C_FCON_RXFRST_MSK);

	nbyte = (add_size == I2C_MEMADD_SIZE_8BIT) ? 1 : 2;
	MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, nbyte << I2C_CON2_NBYTES_POSS);
	SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

	if (i2c_req_mem_read(hperh, dev_addr, mem_addr, add_size, I2C_TIMEOUT_FLAG) != OK) {
		SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
		hperh->state = I2C_STATE_READY;
		hperh->mode  = I2C_MODE_NONE;
		__UNLOCK(hperh);
	}

	if (hperh->hdmarx.perh == NULL)
		hperh->hdmarx.perh = DMA0;

	hperh->hdmarx.cplt_cbk = i2c_dma_mem_recv_cplt;
	hperh->hdmarx.cplt_arg = (void *)hperh;
	hperh->hdmarx.err_cbk  = i2c_dma_error;
	hperh->hdmarx.err_arg  = (void *)hperh;
	
	ald_dma_config_struct(&hperh->hdmarx.config);
	hperh->hdmatx.config.burst       = ENABLE;
	hperh->hdmarx.config.src     	 = (void *)&hperh->perh->RXDATA;
	hperh->hdmarx.config.dst     	 = (void *)buf;
	hperh->hdmarx.config.data_width	 = DMA_DATA_SIZE_BYTE;
	hperh->hdmarx.config.size        = size;
	hperh->hdmarx.config.src_inc 	 = DMA_DATA_INC_NONE;
	hperh->hdmarx.config.dst_inc 	 = DMA_DATA_INC_BYTE;
	hperh->hdmarx.config.msel    	 = hperh->perh == I2C0 ? DMA_MSEL_I2C0 : DMA_MSEL_I2C1;
	hperh->hdmarx.config.msigsel 	 = DMA_MSIGSEL_I2C_RNR;
	hperh->hdmarx.config.channel 	 = channel;
	ald_dma_config_basic(&hperh->hdmarx);

	MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
	CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

	SET_BIT(hperh->perh->CON2, I2C_CON2_RD_WRN_MSK);
	SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);
	SET_BIT(hperh->perh->CON1, I2C_CON1_RXDMAEN_MSK);

	__UNLOCK(hperh);

	return OK;
}

#endif

/**
 * @}
 */

/** @defgroup I2C_Public_Functions_Group3 Peripheral state and Errors functions
 *  @brief   Peripheral state and Errors functions
 *
@verbatim
 ===============================================================================
            ##### Peripheral state and Errors functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
 * @{
 */

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
	uint32_t size = hperh->xfer_size - hperh->xfer_count;

	/**< Transmit FIFO threshold interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_TXTH) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_TXTH);
		if ((hperh->mode == I2C_MODE_MASTER) || (hperh->mode == I2C_MODE_MEM)) {
			i2c_master_send_txe(hperh);
		}
		else if (hperh->mode == I2C_MODE_SLAVE) {
			i2c_slave_send_txe(hperh);
		}
	}

	/**< Receive FIFO threshold interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_RXTH) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_RXTH);
		if ((hperh->mode == I2C_MODE_MASTER) || (hperh->mode == I2C_MODE_MEM)) {
			i2c_master_recv_rxne(hperh);
		}
		else if (hperh->mode == I2C_MODE_SLAVE) {
			i2c_slave_recv_rxne(hperh);
		}
	}

	/**< Transmit completed interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_TC) == SET) {
		if ((hperh->mode == I2C_MODE_MASTER) || (hperh->mode == I2C_MODE_MEM)) {
			if (I2C_MASTER_GET_DIR(hperh) == RESET) {
				i2c_master_send_tc(hperh);
			}
			else {
				i2c_master_recv_tc(hperh);
			}
		}

		ald_i2c_clear_flag_status(hperh, I2C_IT_TC);
	}

	/**< Transmit and reload completed interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_TCR) == SET) {
		if (size > 0xFF) {
			MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
		}
		else {
			MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, size << I2C_CON2_NBYTES_POSS);
			CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
		}

		ald_i2c_clear_flag_status(hperh, I2C_IT_TCR);
	}
	/**< Transmit FIFO empty interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_TXE) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_TXE);
	}

	/**< Receive FIFO full interrupt*/
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_RXF) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_RXF);
	}

	/**< Address matching interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_ADDR) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_ADDR);
	}

	/**< Stop detection interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_STOP) == SET) {
		i2c_slave_stopf(hperh);
		ald_i2c_clear_flag_status(hperh, I2C_IT_STOP);
	}
}

/**
  * @brief  This function handles I2C error interrupt request.
  * @param  hperh: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval  NONE
  */
void ald_i2c_er_irq_handler(i2c_handle_t *hperh)
{
	/**< Transmit FIFO overrun interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_TXOV) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_TXOV);
		hperh->error_code |= I2C_ERROR_TOV;
	}
	/**< Transmit FIFO underrun */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_TXUD) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_TXUD);
		hperh->error_code |= I2C_ERROR_TUD;
	}

	/**< Receive FIFO overrun interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_RXOV) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_RXOV);
		hperh->error_code |= I2C_ERROR_ROV;
	}

	/**< Receive FIFO underrun interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_RXUD) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_RXUD);
		hperh->error_code |= I2C_ERROR_RUD;
	}

	/**< NACK interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_NACK) == SET) {
		if (hperh->xfer_count != hperh->xfer_size) {
			hperh->state |= I2C_ERROR_AF;
		}
		else {
			I2C_DISABLE_IT(hperh, I2C_IT_TXTH | I2C_IT_NACK);
			ald_i2c_clear_flag_status(hperh, I2C_IT_NACK);
			return;
		}

		if ((hperh->mode == I2C_MODE_MASTER) || (hperh->mode == I2C_MODE_MEM))
			SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);

		I2C_DISABLE_IT(hperh, I2C_IT_TXTH | I2C_IT_NACK);
		ald_i2c_clear_flag_status(hperh, I2C_IT_NACK);
	}

	/**< Bus error interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_BERR) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_BERR);
		hperh->state |= I2C_ERROR_BERR;
	}

	/**< Arbitration loss interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_ARLO) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_ARLO);
		hperh->state |= I2C_ERROR_ARLO;
	}

	/**< PEC error interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_PECE) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_PECE);
	}

	/**< Timeout interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_TOUT) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_TOUT);
		hperh->state |= I2C_ERROR_TIMEOUT;
	}

	/**< SMBus Alert interrupt */
	if (ald_i2c_get_mask_flag_status(hperh, I2C_IT_ALERT) == SET) {
		ald_i2c_clear_flag_status(hperh, I2C_IT_ALERT);
	}

	hperh->state = I2C_STATE_READY;
	hperh->mode  = I2C_MODE_NONE;
	__UNLOCK(hperh);

	if (hperh->error_callback)
		hperh->error_callback(hperh);
}

/**
  * @brief  Enable/disable the specified I2C interrupts.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  it: Specifies the i2c interrupt sources to be enabled or disabled.
  * @param  state: New state of the specified I2C interrupts.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_i2c_interrupt_config(i2c_handle_t *hperh, i2c_interrupt_t it, type_func_t state)
{
	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_IT(it));
	assert_param(IS_FUNC_STATE(state));

	if (state == ENABLE)
		hperh->perh->IER = it;
	else
		hperh->perh->IDR = it;

	return;
}

/**
  * @brief  Get the status of I2C interrupt source.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  it: Specifies the I2C interrupt source.
  *         This parameter can be one of the @ref i2c_interrupt_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
it_status_t ald_i2c_get_it_status(i2c_handle_t *hperh, i2c_interrupt_t it)
{
	it_status_t status = RESET;

	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_IT(it));

	if (hperh->perh->IVS & it)
		status = SET;

	return status;
}

/**
  * @brief  Get the status of I2C interrupt flag.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  flag: Specifies the I2C interrupt flag.
  *         This parameter can be one of the @ref i2c_interrupt_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_i2c_get_flag_status(i2c_handle_t *hperh, i2c_interrupt_t flag)
{
	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_IT(flag));

	if (hperh->perh->RIF & flag)
		return SET;

	return RESET;
}


/**
  * @brief  Get the status of interrupt flag and interupt source.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  flag: Specifies the I2C interrupt flag.
  *         This parameter can be one of the @ref i2c_interrupt_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_i2c_get_mask_flag_status(i2c_handle_t *hperh, i2c_interrupt_t flag)
{
	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_IT(flag));

	if (hperh->perh->IFM & flag)
		return SET;

	return RESET;
}

/**
  * @brief  Clear the I2C interrupt flag.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  flag: Specifies the I2C interrupt flag.
  * @retval None
  */
void ald_i2c_clear_flag_status(i2c_handle_t *hperh, i2c_interrupt_t flag)
{
	assert_param(IS_I2C_TYPE(hperh->perh));
	assert_param(IS_I2C_IT(flag));

	hperh->perh->ICR = flag;
	return;
}

/**
 * @}
 */

/** @addtogroup I2C_Private_Functions
 * @{
 */

/**
 * @brief  Handle transmit complete flag for Master Transmit mode
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_master_send_tc(i2c_handle_t *hperh)
{
	I2C_DISABLE_IT(hperh, I2C_IT_TXTH | I2C_IT_NACK | I2C_IT_TC | I2C_IT_TCR);

	if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK) == RESET)
		SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);

	__UNLOCK(hperh);
	hperh->state = I2C_STATE_READY;

	if (hperh->mode == I2C_MODE_MEM) {
		if (hperh->mem_tx_cplt_cbk)
			hperh->mem_tx_cplt_cbk(hperh);
	}
	else {
		if (hperh->master_tx_cplt_cbk)
			hperh->master_tx_cplt_cbk(hperh);
	}

	return OK;
}


/**
 * @brief  Handle transmit empty flag for Master Transmit mode
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_master_send_txe(i2c_handle_t *hperh)
{
	if (hperh->xfer_count != hperh->xfer_size) {
		while(hperh->perh->STAT & (0x1 << 1));
		hperh->perh->TXDATA = (*hperh->p_buff++);
		hperh->xfer_count++;
	}

	return OK;
}

/**
 * @brief  Handle receive complete for Master Receive mode
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_master_recv_tc(i2c_handle_t *hperh)
{
	I2C_DISABLE_IT(hperh, I2C_IT_RXTH | I2C_IT_TCR | I2C_IT_TC);

	if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK) == RESET)
		SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);

	__UNLOCK(hperh);
	hperh->state = I2C_STATE_READY;

	if (hperh->mode == I2C_MODE_MEM) {
		if (hperh->mem_rx_cplt_cbk)
			hperh->mem_rx_cplt_cbk(hperh);
	}
	else {
		if (hperh->master_rx_cplt_cbk)
			hperh->master_rx_cplt_cbk(hperh);
	}

	return OK;
}
/**
 * @brief  Handle receive not empty for Master Receive mode
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_master_recv_rxne(i2c_handle_t *hperh)
{
	while (READ_BITS(hperh->perh->FCON, I2C_FCON_RXFLV_MSK, I2C_FCON_RXFLV_POSS) > 0) {
		if (hperh->xfer_size - hperh->xfer_count > 0) {
			(*hperh->p_buff++) = hperh->perh->RXDATA;
			hperh->xfer_count++;
		}
		else {
			return OK;
		}
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
	if (hperh->xfer_size > hperh->xfer_count) {
		while(hperh->perh->STAT & (0x1 << 1));
		hperh->perh->TXDATA = (*hperh->p_buff++);
		hperh->xfer_count++;
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
	while (READ_BITS(hperh->perh->FCON, I2C_FCON_RXFLV_MSK, I2C_FCON_RXFLV_POSS) > 0) {
		if (hperh->xfer_size > hperh->xfer_count) {
			(*hperh->p_buff++) = hperh->perh->RXDATA;
			hperh->xfer_count++;
		}
		else {
			return OK;
		}
	}

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
	I2C_DISABLE_IT(hperh, I2C_IT_ADDR | I2C_IT_NACK | I2C_IT_RXTH | I2C_IT_TXTH | I2C_IT_STOP);

	hperh->mode       = I2C_MODE_NONE;
	hperh->error_code = I2C_ERROR_NONE;
	__UNLOCK(hperh);

	if (hperh->state == I2C_STATE_BUSY_TX) {
		hperh->state = I2C_STATE_READY;
		if ((hperh->slave_tx_cplt_cbk) && (hperh->xfer_count != 0))
			hperh->slave_tx_cplt_cbk(hperh);
	}
	else if (hperh->state == I2C_STATE_BUSY_RX) {
		hperh->state = I2C_STATE_READY;
		if ((hperh->slave_rx_cplt_cbk) && (hperh->xfer_count != 0))
			hperh->slave_rx_cplt_cbk(hperh);
	}

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
	if (hperh->init.addr_mode == I2C_ADDR_7BIT) {
		CLEAR_BIT(hperh->perh->CON2, I2C_CON2_ADD10_MSK);
	}
	else {
		SET_BIT(hperh->perh->CON2, I2C_CON2_ADD10_MSK);
	}

	MODIFY_REG(hperh->perh->CON2, I2C_CON2_SADD_MSK, dev_addr << I2C_CON2_SADD_POSS);
	CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RD_WRN_MSK);

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
	if (hperh->init.addr_mode == I2C_ADDR_7BIT) {
		CLEAR_BIT(hperh->perh->CON2, I2C_CON2_ADD10_MSK);
	}
	else {
		SET_BIT(hperh->perh->CON2, I2C_CON2_ADD10_MSK);
	}

	MODIFY_REG(hperh->perh->CON2, I2C_CON2_SADD_MSK, dev_addr << I2C_CON2_SADD_POSS);
	SET_BIT(hperh->perh->CON2, I2C_CON2_RD_WRN_MSK);

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
	i2c_master_req_write(hperh, dev_addr, timeout);
	SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

	if (add_size == I2C_MEMADD_SIZE_8BIT) {
		while(hperh->perh->STAT & (0x1 << 1));
		hperh->perh->TXDATA = I2C_MEM_ADD_LSB(mem_addr);
	}
	else {
		while(hperh->perh->STAT & (0x1 << 1));
		hperh->perh->TXDATA = I2C_MEM_ADD_MSB(mem_addr);

		if (i2c_wait_txe_to_timeout(hperh, timeout) != OK)
			return ERROR;

		while(hperh->perh->STAT & (0x1 << 1));
		hperh->perh->TXDATA = I2C_MEM_ADD_LSB(mem_addr);
	}

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_TCR, RESET, timeout) != OK) {
		CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
		ald_i2c_clear_flag_status(hperh, I2C_IT_TCR);
		return ERROR;
	}

	CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
	ald_i2c_clear_flag_status(hperh, I2C_IT_TCR);
	
	return OK;
}
#ifdef ALD_DMA
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
	uint32_t tim_count = 0;

	if (i2c_master_req_write(hperh, dev_addr, timeout) != OK) {
		__UNLOCK(hperh);
		return ERROR;
	}

	SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

	if (add_size == I2C_MEMADD_SIZE_8BIT) {
		while(hperh->perh->STAT & (0x1 << 1));
		hperh->perh->TXDATA = I2C_MEM_ADD_LSB(mem_addr);
	}
	else {
		while(hperh->perh->STAT & (0x1 << 1));
		hperh->perh->TXDATA = I2C_MEM_ADD_MSB(mem_addr);

		if (i2c_wait_txe_to_timeout(hperh, timeout) != OK) {
			if (hperh->error_code == I2C_ERROR_AF) {
				SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);
				return ERROR;
			}
			else {
				return TIMEOUT;
			}
		}
		while(hperh->perh->STAT & (0x1 << 1));
		hperh->perh->TXDATA = I2C_MEM_ADD_LSB(mem_addr);
	}

	while (!I2C_GET_FLAG(hperh, I2C_STAT_TXE)) {
		tim_count++;

		if (tim_count > 0xFFFF)
			return TIMEOUT;
	}

	return OK;
}


/**
* @brief  DMA I2C master transmit process complete callback.
* @param  argv: I2C handle
* @retval None
*/
static void i2c_dma_master_send_cplt(void *argv)
{
	i2c_handle_t* hperh = (i2c_handle_t*)argv;

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_TC, RESET, I2C_TIMEOUT_FLAG) == ERROR)
		hperh->error_code |= I2C_ERROR_TIMEOUT;

	SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_TXDMAEN_MSK);

	hperh->xfer_count = 0;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;
	__UNLOCK(hperh);

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

	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_TXDMAEN_MSK);

	hperh->xfer_count = 0;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;
	__UNLOCK(hperh);

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

	if (i2c_wait_flag_change_to_timeout(hperh, I2C_STAT_TC, RESET, I2C_TIMEOUT_FLAG) == ERROR)
		hperh->error_code |= I2C_ERROR_TIMEOUT;

	SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_RXDMAEN_MSK);

	hperh->xfer_count = 0;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;
	__UNLOCK(hperh);

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

	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_RXDMAEN_MSK);

	hperh->xfer_count = 0;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;
	__UNLOCK(hperh);

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
 */uint32_t ccct = 0;
static void i2c_dma_mem_send_cplt(void *argv)
{
	uint32_t cnt = 0xFFFFFF;

	i2c_handle_t* hperh = (i2c_handle_t*)argv;
ccct++;ccct = ccct;
	while (cnt--) {
		if ((hperh->perh->STAT & I2C_STAT_TC) != 0)
			break;
	}

	if (cnt == 0)
		hperh->error_code |= I2C_ERROR_TIMEOUT;

	SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_TXDMAEN_MSK);

	hperh->xfer_count = 0;
	hperh->state      = I2C_STATE_READY;
	hperh->mode       = I2C_MODE_NONE;
	__UNLOCK(hperh);

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
	uint32_t cnt = 0xFFFFF;

	i2c_handle_t* hperh = (i2c_handle_t*)argv;

	while (cnt--) {
		if ((hperh->perh->STAT & I2C_STAT_TC) != 0)
			break;
	}

	if (cnt == 0)
		hperh->error_code |= I2C_ERROR_TIMEOUT;

	SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
	CLEAR_BIT(hperh->perh->CON1, I2C_CON1_RXDMAEN_MSK);

	hperh->xfer_count = 0;
	hperh->state = I2C_STATE_READY;
	hperh->mode = I2C_MODE_NONE;
	__UNLOCK(hperh);

	if (hperh->error_code != I2C_ERROR_NONE) {
		if (hperh->error_callback)
			hperh->error_callback(hperh);
	}
	else {
		if (hperh->mem_rx_cplt_cbk)
			hperh->mem_rx_cplt_cbk(hperh);
	}
}

/**
* @brief  DMA I2C communication error callback.
* @param  argv: I2C handle
* @retval None
*/
static void i2c_dma_error(void *argv)
{
 	i2c_handle_t* hperh = (i2c_handle_t*)argv;

 	hperh->xfer_count  = 0;
 	hperh->state       = I2C_STATE_READY;
 	hperh->mode        = I2C_MODE_NONE;
 	hperh->error_code |= I2C_ERROR_DMA;
	__UNLOCK(hperh);

 	if (hperh->error_callback)
 		hperh->error_callback(hperh);
}
#endif

/**
 * @brief  This function handles I2C Communication timeout.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  flag: specifies the I2C flag to check.
 * @param  status: The checked flag status (SET or RESET).
 * @param  timeout: Timeout duration
 * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_wait_flag_change_to_timeout(i2c_handle_t *hperh, uint32_t flag, flag_status_t status, uint32_t timeout)
{
	uint32_t tickstart = 0;

	tickstart = ald_get_tick();
	if (status == RESET) {
		while (I2C_GET_FLAG(hperh, flag) == RESET) {
			if ((timeout == 0) || ((ald_get_tick() - tickstart ) > timeout)) {
				hperh->error_code |= I2C_ERROR_TIMEOUT;
				return TIMEOUT;
			}
		}
	}
	else {
		while (I2C_GET_FLAG(hperh, flag) != RESET) {
			if ((timeout == 0) || ((ald_get_tick() - tickstart ) > timeout)) {
				hperh->error_code |= I2C_ERROR_TIMEOUT;
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
static ald_status_t i2c_wait_master_addr_to_timeout(i2c_handle_t *hperh, uint32_t flag, uint32_t timeout)
{
	uint32_t tickstart = ald_get_tick();

	while (I2C_GET_IT_FLAG(hperh, flag) == RESET) {
		if ((timeout == 0) || ((ald_get_tick() - tickstart ) > timeout)) {
			hperh->error_code = I2C_ERROR_TIMEOUT;

			return ERROR;
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

	while (I2C_GET_FLAG(hperh, I2C_STAT_THTH) == RESET) {
		if (I2C_GET_IT_FLAG(hperh, I2C_IT_ARLO)) {
			hperh->error_code |= I2C_ERROR_ARLO;
			return ERROR;
		}

		if (I2C_GET_IT_FLAG(hperh, I2C_IT_NACK) == SET) {
			hperh->error_code |= I2C_ERROR_AF;
			return ERROR;
		}

		if ((timeout == 0) || ((ald_get_tick() - tickstart) > timeout)) {
			hperh->error_code |= I2C_ERROR_TIMEOUT;
			return ERROR;
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
	uint32_t tickstart = ald_get_tick();

	while (I2C_GET_FLAG(hperh, I2C_STAT_RXTH) == RESET) {
		if ((timeout == 0) || ((ald_get_tick() - tickstart) > timeout)) {
			hperh->error_code |= I2C_ERROR_TIMEOUT;
			return ERROR;
		}
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

/**
 * @}
 */
