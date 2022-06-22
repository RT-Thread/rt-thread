/**
  *********************************************************************************
  *
  * @file    ald_I2S.c
  * @brief   I2S module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of I2S peripheral:
  *           + Initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
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
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
      The I2S driver can be used as follows:

      (#) Declare a i2s_handle_t structure, for example:
          i2s_handle_t hperh;

      (#) Initialize the I2S low level resources:
          (##) Enable the I2Sx interface clock
          (##) I2S pins configuration
              (+++) Enable the clock for the I2S GPIOs
              (+++) Configure these I2S pins as push-pull
          (##) NVIC configuration if you need to use interrupt process
               by implementing the ald_mcu_irq_config() API.
	       Invoked ald_i2s_irq_handler() function in I2S-IRQ function
          (##) DMA Configuration if you need to use DMA process
              (+++) Define ALD_DMA in ald_conf.h
 	      (+++) Enable the DMAx clock

      (#) Program the Channel length, Data length, Polarity, Standard, Pcm frame,
          external clock and Main clock output, Odd factor and Divide clock in the i2s_init_t structure.

      (#) Initialize the I2S module by invoking the ald_i2s_init() API.

     [..]
       Circular mode restriction:
      (#) When the I2S DMA Pause/Stop features are used, we must use the following APIs
          the ald_i2s_dma_pause()/ ald_i2s_dma_stop().

  * @endverbatim
  */

#include "ald_conf.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup I2S I2S
  * @brief I2S module driver
  * @{
  */
#ifdef ALD_I2S

/** @addtogroup I2S_Private_Functions   I2S Private Functions
  * @{
  */

static ald_status_t i2s_wait_status(i2s_handle_t *hperh, i2s_status_t state, flag_status_t status, uint32_t timeout);
static void __i2s_send_by_it(i2s_handle_t *hperh);
static void __i2s_recv_by_it(i2s_handle_t *hperh);
static void __i2s_tx_recv_by_it(i2s_handle_t *hperh);
#ifdef ALD_DMA
static void i2s_dma_send_cplt(void *arg);
static void i2s_dma_recv_cplt(void *arg);
static void i2s_dma_error(void *arg);
#endif
/**
  * @}
  */

/** @defgroup I2S_Public_Functions I2S Public Functions
  * @{
  */

/** @defgroup I2S_Public_Functions_Group1 Initialization functions
  * @brief Initialization and Configuration functions
  *
  * @verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          reset the I2Sx peripheral:

      (+) User must configure all related peripherals resources
          (CLOCK, GPIO, DMA, NVIC).

      (+) Call the function ald_i2s_init() to configure the selected device with
          the selected configuration:
        (++) Channel length
        (++) Data length
        (++) Polarity
        (++) Standard
        (++) Pcm frame
        (++) External clock
        (++) Main clock output function
        (++) Odd factor
        (++) Divide clock

      (+) Call the function ald_i2s_reset() to reset the selected I2Sx periperal.

    @endverbatim
  * @{
  */

/**
  * @brief  Reset the I2S peripheral.
  * @param  hperh: Pointer to a i2s_handle_t structure that contains
  *         the configuration information for the specified I2S module.
  * @retval None
  */
void ald_i2s_reset(i2s_handle_t *hperh)
{
	hperh->perh->I2SCFG = 0x0;
	hperh->perh->I2SPR  = 0x0;

	I2S_RESET_HANDLE_STATE(hperh);
	__UNLOCK(hperh);

	return;
}

/**
  * @brief  Initializes the I2S mode according to the specified parameters in
  *         the i2s_init_t and create the associated handle.
  * @param  hperh: Pointer to a i2s_handle_t structure that contains
  *         the configuration information for the specified SPI module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2s_init(i2s_handle_t *hperh)
{
	uint32_t tmp = 0, clk, _div;

	if (hperh == NULL)
		return ERROR;

	assert_param(IS_I2S(hperh->perh));
	assert_param(IS_I2S_CH_LEN(hperh->init.ch_len));
	assert_param(IS_I2S_DATE_LEN(hperh->init.data_len));
	assert_param(IS_I2S_CPOL(hperh->init.polarity));
	assert_param(IS_I2S_STANDARD(hperh->init.standard));
	assert_param(IS_FUNC_STATE(hperh->init.ext_clk_en));
	assert_param(IS_FUNC_STATE(hperh->init.mck_en));
	assert_param(IS_I2S_PCMS(hperh->init.pcm_frame));

	ald_i2s_reset(hperh);
	
	tmp |= (hperh->init.ext_clk_en << SPI_I2SPR_EXTCKEN_POS);
	
	/* Get I2S clock */
	if (hperh->init.ext_clk_en)
		clk = hperh->init.ext_clk;
	else
		clk = ald_cmu_get_pclk1_clock();

	if (hperh->init.mck_en) { 
		_div = ((clk / hperh->init.sampling) >> 8);
	}
	else {
		if (hperh->init.ch_len == I2S_WIDE_16)
			_div = ((clk / hperh->init.sampling) >> 5);
		else
			_div = ((clk / hperh->init.sampling) >> 6);
	}
	
	if (_div & 0x1) {
		SET_BIT(tmp, SPI_I2SPR_ODD_MSK);
		--_div;
	}
	else {
		CLEAR_BIT(tmp, SPI_I2SPR_ODD_MSK);
	}
	
	if (hperh->init.standard != I2S_STD_PCM)
		MODIFY_REG(tmp, SPI_I2SPR_I2SDIV_MSK, (_div >> 1) << SPI_I2SPR_I2SDIV_POSS);
	else
		MODIFY_REG(tmp, SPI_I2SPR_I2SDIV_MSK, _div << SPI_I2SPR_I2SDIV_POSS);

	hperh->perh->I2SPR = tmp;

	tmp  = hperh->perh->I2SCFG;
	tmp |= ((hperh->init.ch_len << SPI_I2SCFG_CHLEN_POS) | (hperh->init.data_len << SPI_I2SCFG_DATLEN_POSS) |
		(hperh->init.polarity << SPI_I2SCFG_CKPOL_POS) | (hperh->init.standard << SPI_I2SCFG_I2SSTD_POSS) |
		(1 << SPI_I2SCFG_I2SMOD_POS));
	hperh->perh->I2SCFG = tmp;

	if (hperh->init.standard == I2S_STD_PCM)
		hperh->perh->I2SCFG |= (hperh->init.pcm_frame << SPI_I2SCFG_PCMSYNC_POS);

	hperh->err_code = I2S_ERROR_NONE;
	hperh->state    = I2S_STATE_READY;

	return OK;
}
/**
  * @}
  */

/** @defgroup I2S_Public_Functions_Group2 IO operation functions
  * @brief I2S Transmit and Receive functions
  *
  * @verbatim
  ==============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    This subsection provides a set of functions allowing to manage the I2S
    data transfers.

    [..] The I2S supports master or slave mode:

    (#) There are two modes of transfer:
       (++) Blocking mode: The communication is performed in polling mode.
            The ALD status of all data processing is returned by the same function
            after finishing transfer.
       (++) No-Blocking mode: The communication is performed using Interrupts
            or DMA, These APIs return the ALD status.
            The end of the data processing will be indicated through the
            dedicated I2S IRQ when using Interrupt mode or the DMA IRQ when
            using DMA mode.
            The hperh->tx_cplt_cbk(), hperh->rx_cplt_cbk() user callbacks
            will be executed respectivelly at the end of the transmit or Receive process
            The hperh->err_cbk() user callback will be executed when a communication error is detected

    (#) APIs provided for these 2 transfer modes (Blocking mode or Non blocking mode using either Interrupt or DMA).

  * @endverbatim
  * @{
  */

/**
  * @brief  Master mode transmit an amount of data in blocking mode.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2s_master_send(i2s_handle_t *hperh, uint16_t *buf, uint32_t size, uint32_t timeout)
{
	assert_param(IS_I2S(hperh->perh));

	if (hperh->state != I2S_STATE_READY)
		return BUSY;
	if (buf == NULL || size == 0)
		return ERROR;

	hperh->state    = I2S_STATE_BUSY_TX;
	hperh->err_code = I2S_ERROR_NONE;

	MODIFY_REG(hperh->perh->I2SCFG, SPI_I2SCFG_I2SCFG_MSK, I2S_MASTER_TRANSMIT << SPI_I2SCFG_I2SCFG_POSS);

	if (hperh->init.mck_en)
		MODIFY_REG(hperh->perh->I2SPR, SPI_I2SPR_MCKOE_MSK, hperh->init.mck_en << SPI_I2SPR_MCKOE_POS);
	if (READ_BIT(hperh->perh->I2SCFG, SPI_I2SCFG_I2SE_MSK) == 0)
		I2S_ENABLE(hperh);

	while (size > 0) {
		if (i2s_wait_status(hperh, I2S_STATUS_TXE, SET, timeout) != OK) {
			I2S_DISABLE(hperh);

			hperh->state = I2S_STATE_READY;
			return TIMEOUT;
		}

		hperh->side = READ_BITS(hperh->perh->STAT, SPI_STAT_CHSIDE_MSK, SPI_STAT_CHSIDE_POS);
		hperh->perh->DATA = *buf++;
		--size;
	}

 	if ((i2s_wait_status(hperh, I2S_STATUS_TXE, SET, timeout) != OK)
			|| (i2s_wait_status(hperh, I2S_STATUS_BUSY, RESET, timeout) != OK)) {
 		I2S_DISABLE(hperh);
 		hperh->state = I2S_STATE_READY;
 		return TIMEOUT;
 	}

 	I2S_DISABLE(hperh);
	hperh->state = I2S_STATE_READY;

	return OK;
}

/**
  * @brief  Master mode receive an amount of data in blocking mode.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2s_master_recv(i2s_handle_t *hperh, uint16_t *buf, uint32_t size, uint32_t timeout)
{
	assert_param(IS_I2S(hperh->perh));

	if (hperh->state != I2S_STATE_READY)
		return BUSY;
	if (buf == NULL || size == 0)
		return ERROR;

	hperh->state    = I2S_STATE_BUSY_RX;
	hperh->err_code = I2S_ERROR_NONE;

	MODIFY_REG(hperh->perh->I2SCFG, SPI_I2SCFG_I2SCFG_MSK, I2S_MASTER_RECEIVE << SPI_I2SCFG_I2SCFG_POSS);

	if (hperh->init.mck_en)
		MODIFY_REG(hperh->perh->I2SPR, SPI_I2SPR_MCKOE_MSK, hperh->init.mck_en << SPI_I2SPR_MCKOE_POS);
	if (READ_BIT(hperh->perh->I2SCFG, SPI_I2SCFG_I2SE_MSK) == 0)
		I2S_ENABLE(hperh);

	while (size > 0) {
		hperh->perh->DATA = 0xffff;
		if (i2s_wait_status(hperh, I2S_STATUS_RXE, RESET, timeout) != OK) {
			I2S_DISABLE(hperh);
			hperh->state = I2S_STATE_READY;
			return TIMEOUT;
		}

		*buf++ = hperh->perh->DATA;
		--size;
	}

	hperh->state = I2S_STATE_READY;
	return OK;
}

/**
  * @brief  Wraps up master mode transmission in non blocking mode.
  * @param  hperh: pointer to a i2s_handle_t structure.
  * @param  buf: Pointer to data transmitted buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2s_master_send_by_it(i2s_handle_t *hperh, uint16_t *buf, uint32_t size)
{
	assert_param(IS_I2S(hperh->perh));

	if (hperh->state != I2S_STATE_READY)
		return BUSY;
	if (buf == NULL || size == 0)
		return ERROR;

	hperh->state    = I2S_STATE_BUSY_TX;
	hperh->err_code = I2S_ERROR_NONE;
	hperh->tx_buf   = buf;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->rx_buf   = NULL;
	hperh->rx_size  = 0;
	hperh->rx_count = 0;
	
	WRITE_REG(hperh->perh->ICR, 0xffffffff);
	
	I2S_DISABLE(hperh);
	MODIFY_REG(hperh->perh->I2SCFG, SPI_I2SCFG_I2SCFG_MSK, I2S_MASTER_TRANSMIT << SPI_I2SCFG_I2SCFG_POSS);

	if (hperh->init.mck_en)
		MODIFY_REG(hperh->perh->I2SPR, SPI_I2SPR_MCKOE_MSK, hperh->init.mck_en << SPI_I2SPR_MCKOE_POS);
	if (READ_BIT(hperh->perh->I2SCFG, SPI_I2SCFG_I2SE_MSK) == 0)
		I2S_ENABLE(hperh);

	ald_i2s_interrupt_config(hperh, I2S_IT_TXE, ENABLE);
	return OK;
}

/**
  * @brief  Master mode receives an amount of data in non blocking mode
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  buf: Pointer to data received buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2s_master_recv_by_it(i2s_handle_t *hperh, uint16_t *buf, uint32_t size)
{
	assert_param(IS_I2S(hperh->perh));

	if (hperh->state != I2S_STATE_READY)
		return BUSY;
	if (buf == NULL || size == 0)
		return ERROR;

	hperh->state    = I2S_STATE_BUSY_TX_RX;
	hperh->err_code = I2S_ERROR_NONE;
	hperh->rx_buf   = buf;
	hperh->rx_size  = size;
	hperh->rx_count = size;
	hperh->tx_buf   = 0;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	
	WRITE_REG(hperh->perh->ICR, 0xffffffff);

	I2S_DISABLE(hperh);
	MODIFY_REG(hperh->perh->I2SCFG, SPI_I2SCFG_I2SCFG_MSK, I2S_MASTER_RECEIVE << SPI_I2SCFG_I2SCFG_POSS);

	if (hperh->init.mck_en)
		MODIFY_REG(hperh->perh->I2SPR, SPI_I2SPR_MCKOE_MSK, hperh->init.mck_en << SPI_I2SPR_MCKOE_POS);

	if (READ_BIT(hperh->perh->I2SCFG, SPI_I2SCFG_I2SE_MSK) == 0)
		I2S_ENABLE(hperh);
	
	ald_i2s_interrupt_config(hperh, I2S_IT_RXTH, ENABLE);
	ald_i2s_interrupt_config(hperh, I2S_IT_TXE, ENABLE);

	return OK;
}

#ifdef ALD_DMA
/**
  * @brief  Master mode transmit an amount of data used dma channel
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as I2S transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2s_master_send_by_dma(i2s_handle_t *hperh, uint16_t *buf, uint32_t size, uint8_t channel)
{
	assert_param(IS_I2S(hperh->perh));

	if (hperh->state != I2S_STATE_READY)
		return BUSY;
	if (buf == NULL || size == 0)
		return ERROR;

	hperh->state    = I2S_STATE_BUSY_TX;
	hperh->err_code = I2S_ERROR_NONE;
	hperh->tx_buf   = buf;
	hperh->tx_size  = size;
	hperh->tx_count = size;
	hperh->rx_buf   = NULL;
	hperh->rx_size  = 0;
	hperh->rx_count = 0;
	
	WRITE_REG(hperh->perh->ICR, 0xffffffff);

	I2S_DISABLE(hperh);

	MODIFY_REG(hperh->perh->I2SCFG, SPI_I2SCFG_I2SCFG_MSK, I2S_MASTER_TRANSMIT << SPI_I2SCFG_I2SCFG_POSS);

	if (hperh->init.mck_en)
		MODIFY_REG(hperh->perh->I2SPR, SPI_I2SPR_MCKOE_MSK, hperh->init.mck_en << SPI_I2SPR_MCKOE_POS);

	hperh->hdmatx.cplt_arg = (void *)hperh;
	hperh->hdmatx.cplt_cbk = i2s_dma_send_cplt;
	hperh->hdmatx.err_arg  = (void *)hperh;
	hperh->hdmatx.err_cbk  = i2s_dma_error;

	/* Configure I2S DMA transmit */
	ald_dma_config_struct(&(hperh->hdmatx.config));
	hperh->hdmatx.perh              = DMA0;
	hperh->hdmatx.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdmatx.config.src        = (void *)buf;
	hperh->hdmatx.config.dst        = (void *)&hperh->perh->DATA;
	hperh->hdmatx.config.size       = size;
	hperh->hdmatx.config.src_inc    = DMA_DATA_INC_HALFWORD;
	hperh->hdmatx.config.dst_inc    = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel       = hperh->perh == I2S0 ? DMA_MSEL_SPI0 : (hperh->perh == I2S1 ? DMA_MSEL_SPI1 : DMA_MSEL_SPI2);
	hperh->hdmatx.config.msigsel    = DMA_MSIGSEL_SPI_TXEMPTY;
	hperh->hdmatx.config.channel    = channel;
	hperh->hdmatx.config.burst      = ENABLE;
	ald_dma_config_basic(&(hperh->hdmatx));
	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_TX, ENABLE);

	if (READ_BIT(hperh->perh->I2SCFG, SPI_I2SCFG_I2SE_MSK) == 0)
		I2S_ENABLE(hperh);

	return OK;
}

/**
  * @brief  Master mode receive an amount of data used dma channel
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  dma_ch: DMA channel for I2S receive
  * @param  _dma_ch: DMA channel for sending clock
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2s_master_recv_by_dma(i2s_handle_t *hperh, uint16_t *buf, uint32_t size, uint8_t dma_ch, uint8_t _dma_ch)
{
	assert_param(IS_I2S(hperh->perh));
		
	if (hperh->state != I2S_STATE_READY)
		return BUSY;
	if (buf == NULL || size == 0)
		return ERROR;

	hperh->state    = I2S_STATE_BUSY_RX;
	hperh->err_code = I2S_ERROR_NONE;
	hperh->rx_buf   = buf;
	hperh->rx_size  = size;
	hperh->rx_count = size;
	hperh->tx_buf   = NULL;
	hperh->tx_size  = 0;
	hperh->tx_count = 0;
	buf[size - 1]   = 0xFFFF;
	
	WRITE_REG(hperh->perh->ICR, 0xffffffff);

	I2S_DISABLE(hperh);

	MODIFY_REG(hperh->perh->I2SCFG, SPI_I2SCFG_I2SCFG_MSK, I2S_MASTER_RECEIVE << SPI_I2SCFG_I2SCFG_POSS);

	if (hperh->init.mck_en)
		MODIFY_REG(hperh->perh->I2SPR, SPI_I2SPR_MCKOE_MSK, hperh->init.mck_en << SPI_I2SPR_MCKOE_POS);

	hperh->hdmatx.cplt_arg = (void *)hperh;
	hperh->hdmatx.cplt_cbk = i2s_dma_send_cplt;
	hperh->hdmatx.err_arg  = (void *)hperh;
	hperh->hdmatx.err_cbk  = i2s_dma_error;
	
	ald_dma_config_struct(&(hperh->hdmatx.config));
	hperh->hdmatx.perh              = DMA0;
	hperh->hdmatx.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdmatx.config.src        = (void *)&buf[size - 1];
	hperh->hdmatx.config.dst        = (void *)&hperh->perh->DATA;
	hperh->hdmatx.config.size       = size;
	hperh->hdmatx.config.src_inc    = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.dst_inc    = DMA_DATA_INC_NONE;
	hperh->hdmatx.config.msel       = hperh->perh == I2S0 ? DMA_MSEL_SPI0 : (hperh->perh == I2S1 ? DMA_MSEL_SPI1 : DMA_MSEL_SPI2);
	hperh->hdmatx.config.msigsel    = DMA_MSIGSEL_SPI_TXEMPTY;
	hperh->hdmatx.config.burst      = ENABLE;
	hperh->hdmatx.config.channel    = _dma_ch;
	ald_dma_config_basic(&(hperh->hdmatx));
	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_TX, ENABLE);
	
	hperh->hdmarx.cplt_arg = (void *)hperh;
	hperh->hdmarx.cplt_cbk = i2s_dma_recv_cplt;
	hperh->hdmarx.err_arg  = (void *)hperh;
	hperh->hdmarx.err_cbk  = i2s_dma_error;

	/* Configure DMA Receive */
	ald_dma_config_struct(&(hperh->hdmarx.config));
	hperh->hdmarx.perh              = DMA0;
	hperh->hdmarx.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdmarx.config.src        = (void *)&hperh->perh->DATA;
	hperh->hdmarx.config.dst        = (void *)buf;
	hperh->hdmarx.config.size       = size;
	hperh->hdmarx.config.src_inc    = DMA_DATA_INC_NONE;
	hperh->hdmarx.config.dst_inc    = DMA_DATA_INC_HALFWORD;
	hperh->hdmarx.config.msel       = hperh->perh == I2S0 ? DMA_MSEL_SPI0 : (hperh->perh == I2S1 ? DMA_MSEL_SPI1 : DMA_MSEL_SPI2);
	hperh->hdmarx.config.msigsel    = DMA_MSIGSEL_SPI_RNR;
	hperh->hdmarx.config.channel    = dma_ch;
	hperh->hdmarx.config.burst      = ENABLE;
	ald_dma_config_basic(&(hperh->hdmarx));
	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_RX, ENABLE);

	if (READ_BIT(hperh->perh->I2SCFG, SPI_I2SCFG_I2SE_MSK) == 0)
		I2S_ENABLE(hperh);
	
	return OK;
}

/**
  * @brief  Pauses the DMA Transfer.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @retval Status
  */
ald_status_t ald_i2s_dma_pause(i2s_handle_t *hperh)
{
	assert_param(IS_I2S(hperh->perh));

	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_TX, DISABLE);
	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_RX, DISABLE);

	return OK;
}

/**
  * @brief  Resumes the DMA Transfer.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @retval Status
  */
ald_status_t ald_i2s_dma_resume(i2s_handle_t *hperh)
{
	assert_param(IS_I2S(hperh->perh));

	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_TX, ENABLE);
	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_RX, ENABLE);

	return OK;
}

/**
  * @brief  Stops the DMA Transfer.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @retval Status
  */
ald_status_t ald_i2s_dma_stop(i2s_handle_t *hperh)
{
	assert_param(IS_I2S(hperh->perh));

	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_TX, DISABLE);
	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_RX, DISABLE);

	hperh->state = I2S_STATE_READY;
	return OK;
}
#endif
/**
  * @}
  */

/** @defgroup I2S_Public_Functions_Group3 Control functions
  * @brief I2S Control functions
  *
  * @verbatim
   ===============================================================================
                      ##### Peripheral Control functions #####
   ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the I2S.
     (+) Handle interrupt about I2S module. The ald_i2s_irq_handler() function must
         be invoked by I2S-IRQ function.
     (+) Configure the interrupt DISABLE/ENABLE.
     (+) Configure the DMA request.
     (+) Get interrupt source status.
     (+) Get interrupt flag status.
     (+) Clear interrupt flag

    @endverbatim
  * @{
  */

/**
  * @brief  This function handles I2S interrupt request.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @retval None
  */
void ald_i2s_irq_handler(i2s_handle_t *hperh)
{
	if (ald_i2s_get_mask_flag_status(hperh, I2S_IF_RXTH) == SET) {
		ald_i2s_clear_flag_status(hperh, I2S_IF_RXTH);
		if ((hperh->state == I2S_STATE_BUSY_TX_RX) || (hperh->state == I2S_STATE_BUSY_RX))
			__i2s_recv_by_it(hperh);
	}

	if (ald_i2s_get_mask_flag_status(hperh, I2S_IF_TXE) == SET) {
		ald_i2s_clear_flag_status(hperh, I2S_IF_TXE);
		if (hperh->state == I2S_STATE_BUSY_TX)
			__i2s_send_by_it(hperh);
		else if (hperh->state == I2S_STATE_BUSY_TX_RX)
			__i2s_tx_recv_by_it(hperh);
			
	}

	if (hperh->err_code != I2S_ERROR_NONE) {
		ald_i2s_interrupt_config(hperh, I2S_IT_RXTH, DISABLE);
		ald_i2s_interrupt_config(hperh, I2S_IT_TXE, DISABLE);
		hperh->state = I2S_STATE_READY;

		if (hperh->err_cbk)
			hperh->err_cbk(hperh);
	}

	return;
}

/**
  * @brief  Enables or disables the specified I2S interrupts.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  it: Specifies the I2S interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref i2s_it_t.
  * @param  state: New status
  *           - ENABLE
  *           - DISABLE
  * @retval None
  */
void ald_i2s_interrupt_config(i2s_handle_t *hperh, i2s_it_t it, type_func_t state)
{
	assert_param(IS_I2S(hperh->perh));
	assert_param(IS_I2S_IT(it));
	assert_param(IS_FUNC_STATE(state));

	if (state == ENABLE)
		hperh->perh->IER = (uint32_t)it;
	else
		hperh->perh->IDR = (uint32_t)it;

	return;
}

/**
  * @brief  Enables or disables the dma request.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  req: Specifies the I2S dma request sources to be enabled or disabled.
  *         This parameter can be one of the @ref i2s_dma_req_t.
  * @param  state: New status
  *           - ENABLE
  *           - DISABLE
  * @retval None
  */
void ald_i2s_dma_req_config(i2s_handle_t *hperh, i2s_dma_req_t req, type_func_t state)
{
	assert_param(IS_I2S(hperh->perh));
	assert_param(IS_I2S_DMA_REQ(req));
	assert_param(IS_FUNC_STATE(state));

	if (state == ENABLE) {
		if (req == I2S_DMA_REQ_TX)
			SET_BIT(hperh->perh->CON2, SPI_CON2_TXDMA_MSK);
		else
			SET_BIT(hperh->perh->CON2, SPI_CON2_RXDMA_MSK);
	}
	else {
		if (req == I2S_DMA_REQ_TX)
			CLEAR_BIT(hperh->perh->CON2, SPI_CON2_TXDMA_MSK);
		else
			CLEAR_BIT(hperh->perh->CON2, SPI_CON2_RXDMA_MSK);
	}

	return;
}

/** @brief  Check whether the specified I2S flag is set or not.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  status: specifies the flag to check.
  *         This parameter can be one of the @ref i2s_status_t.
  * @retval Status
  *           - SET
  *           - RESET
  */
flag_status_t ald_i2s_get_status(i2s_handle_t *hperh, i2s_status_t status)
{
	assert_param(IS_I2S(hperh->perh));
	assert_param(IS_I2S_STATUS(status));

	if (hperh->perh->STAT & status)
		return SET;

	return RESET;
}

/**
  * @brief  Checks whether the specified I2S interrupt has occurred or not.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  it: Specifies the I2S interrupt source to check.
  *         This parameter can be one of the @ref i2s_it_t.
  * @retval Status
  *           - SET
  *           - RESET
  */
it_status_t ald_i2s_get_it_status(i2s_handle_t *hperh, i2s_it_t it)
{
	assert_param(IS_I2S(hperh->perh));
	assert_param(IS_I2S_IT(it));

	if (hperh->perh->IVS & it)
		return SET;

	return RESET;
}

/** @brief  Check whether the specified I2S interrupt flag is set or not.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  flag: specifies the flag to check.
  *         This parameter can be one of the @ref i2s_flag_t.
  * @retval Status
  *           - SET
  *           - RESET
  */
flag_status_t ald_i2s_get_flag_status(i2s_handle_t *hperh, i2s_flag_t flag)
{
	assert_param(IS_I2S(hperh->perh));
	assert_param(IS_I2S_IF(flag));

	if (hperh->perh->RIF & flag)
		return SET;

	return RESET;
}

/** @brief  Check whether the specified I2S interrupt flag is set or not.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  flag: specifies the flag to check.
  *         This parameter can be one of the @ref i2s_flag_t.
  * @retval Status
  *           - SET
  *           - RESET
  */
flag_status_t ald_i2s_get_mask_flag_status(i2s_handle_t *hperh, i2s_flag_t flag)
{
	assert_param(IS_I2S(hperh->perh));
	assert_param(IS_I2S_IF(flag));

	if (hperh->perh->IFM & flag)
		return SET;

	return RESET;
}

/** @brief  Clear the specified I2S interrupt flags.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  flag: specifies the flag to check.
  *         This parameter can be one of the @ref i2s_flag_t.
  * @retval None
  */
void ald_i2s_clear_flag_status(i2s_handle_t *hperh, i2s_flag_t flag)
{
	assert_param(IS_I2S(hperh->perh));
	assert_param(IS_I2S_IF(flag));

	hperh->perh->ICR = flag;
	return;
}
/**
  * @}
  */

/** @defgroup I2S_Public_Functions_Group4 Peripheral State and Errors functions
  *  @brief   I2S State and Errors functions
  *
  * @verbatim
 ===============================================================================
                      ##### Peripheral State and Errors functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the I2S.
     (+) ald_i2s_get_state() API can check in run-time the state of the I2S peripheral
     (+) ald_i2s_get_error() check in run-time Errors occurring during communication

    @endverbatim
  * @{
  */

/**
  * @brief  Returns the I2S state.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @retval Status, see @ref i2s_state_t.
  */
i2s_state_t ald_i2s_get_state(i2s_handle_t *hperh)
{
	assert_param(IS_I2S(hperh->perh));
	return hperh->state;
}

/**
  * @brief  Return the I2S error code
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @retval I2S Error Code
  */
uint32_t ald_i2s_get_error(i2s_handle_t *hperh)
{
	assert_param(IS_I2S(hperh->perh));
	return hperh->err_code;
}
/**
  * @}
  */
/**
  * @}
  */

/** @defgroup I2S_Private_Functions I2S Private Functions
  * @brief   I2S Private functions
  * @{
  */
/**
  * @brief  This function wait I2S status until timeout.
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @param  flag: specifies the I2S flag to check.
  * @param  status: The new Flag status (SET or RESET).
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t i2s_wait_status(i2s_handle_t *hperh, i2s_status_t flag, flag_status_t status, uint32_t timeout)
{
	uint32_t tick = ald_get_tick();

	assert_param(timeout > 0);

	while ((ald_i2s_get_status(hperh, flag)) != status) {
		if (((ald_get_tick()) - tick) > timeout) {
			ald_i2s_interrupt_config(hperh, I2S_IT_TXE, DISABLE);
			ald_i2s_interrupt_config(hperh, I2S_IT_RXTH, DISABLE);
			return TIMEOUT;
		}
	}

	return OK;
}

/**
  * @brief  handle program when an tx empty interrupt flag arrived in non block mode
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @retval None.
  */
static void __i2s_send_by_it(i2s_handle_t *hperh)
{
	int cnt = 8000;

	if (hperh->tx_count == 0) {
		ald_i2s_interrupt_config(hperh, I2S_IT_TXE, DISABLE);
		hperh->state = I2S_STATE_READY;

		while ((hperh->perh->STAT & SPI_STAT_BUSY_MSK) && (--cnt));
		if (cnt == 0) {
			if (hperh->err_cbk)
				hperh->err_cbk(hperh);

			ald_i2s_interrupt_config(hperh, I2S_IT_RXTH, DISABLE);
			return;
		}

		if (hperh->tx_cplt_cbk)
			hperh->tx_cplt_cbk(hperh);

		return;
	}

	hperh->side = READ_BITS(hperh->perh->STAT, SPI_STAT_CHSIDE_MSK, SPI_STAT_CHSIDE_POS);
	hperh->perh->DATA = *hperh->tx_buf++;
	--hperh->tx_count;

	return;
}

/**
  * @brief  handle program when an rx no empty interrupt flag arrived in non block mode
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @retval None.
  */
static void __i2s_recv_by_it(i2s_handle_t *hperh)
{
	while (READ_BITS(hperh->perh->STAT, SPI_STAT_RXFLV_MSK, SPI_STAT_RXFLV_POSS)) {
		*(hperh->rx_buf++) = hperh->perh->DATA;
		--hperh->rx_count;
	}

	if (hperh->rx_count == 0) {
		ald_i2s_interrupt_config(hperh, I2S_IT_RXTH, DISABLE);
		hperh->state = I2S_STATE_READY;

		if (hperh->rx_cplt_cbk)
			hperh->rx_cplt_cbk(hperh);
	}

	return;
}

/**
  * @brief  handle program when an rx no empty interrupt flag arrived in non block mode
  * @param  hperh: Pointer to a i2s_handle_t structure.
  * @retval None.
  */
static void __i2s_tx_recv_by_it(i2s_handle_t *hperh)
{
	if (hperh->tx_count != 0) {
		ald_i2s_clear_flag_status(hperh, I2S_IF_TXE);
		hperh->perh->DATA = 0xffff;
		--hperh->tx_count;
		if (hperh->tx_count == 0) 
			ald_i2s_interrupt_config(hperh, I2S_IT_TXE, DISABLE);
	} 
}

#ifdef ALD_DMA
/**
  * @brief  DMA I2S transmit process complete callback.
  * @param  arg: Pointer to a void structure.
  * @retval None
  */
static void i2s_dma_send_cplt(void *arg)
{
	int cnt = 8000;
	i2s_handle_t *hperh = (i2s_handle_t *)arg;

	hperh->tx_count = 0;
	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_TX, DISABLE);
	hperh->state = I2S_STATE_READY;

	while ((hperh->perh->STAT & SPI_STAT_BUSY_MSK) && (--cnt));
	if (cnt == 0)
		hperh->err_code |= I2S_ERROR_FLAG;

	if (hperh->err_code == I2S_ERROR_NONE) {
		if (hperh->tx_cplt_cbk)
			hperh->tx_cplt_cbk(hperh);
	}
	else {
		if (hperh->err_cbk)
			hperh->err_cbk(hperh);
	}

	return;
}

/**
  * @brief  DMA I2S receive process complete callback.
  * @param  arg: Pointer to a void structure.
  * @retval None
  */
static void i2s_dma_recv_cplt(void *arg)
{
	i2s_handle_t *hperh = (i2s_handle_t *)arg;

	hperh->rx_count = 0;
	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_RX, DISABLE);
	hperh->state = I2S_STATE_READY;

	if (hperh->err_code == I2S_ERROR_NONE) {
		if (hperh->rx_cplt_cbk)
			hperh->rx_cplt_cbk(hperh);
	}
	else {
		if (hperh->err_cbk)
			hperh->err_cbk(hperh);
	}

	return;
}

/**
  * @brief  DMA I2S communication error callback.
  * @param  arg: Pointer to a void structure.
  * @retval None
  */
static void i2s_dma_error(void *arg)
{
	i2s_handle_t *hperh = (i2s_handle_t *)arg;

	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_TX, DISABLE);
	ald_i2s_dma_req_config(hperh, I2S_DMA_REQ_RX, DISABLE);
	SET_BIT(hperh->err_code, I2S_ERROR_DMA);

 	hperh->tx_count = 0;
 	hperh->rx_count = 0;
	hperh->state    = I2S_STATE_READY;

	if (hperh->err_cbk)
		hperh->err_cbk(hperh);

	return;
}

#endif
/**
  * @}
  */
#endif
/**
  * @}
  */

/**
  * @}
  */
