/**
  *********************************************************************************
  *
  * @file    ald_crc.c
  * @brief   CRC module driver.
  *
  * @version V1.0
  * @date    18 Jun 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          18 Jun 2019     AE Team         The first version
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
  */

#include "ald_conf.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup CRC CRC
  * @brief CRC module driver
  * @{
  */
#ifdef ALD_CRC

/** @addtogroup CRC_Private_Functions   CRC Private Functions
  * @{
  */
void ald_crc_reset(crc_handle_t *hperh);
#ifdef ALD_DMA
static void crc_dma_calculate_cplt(void *arg);
static void crc_dma_error(void *arg);
#endif
/**
  * @}
  */


/** @defgroup CRC_Public_Functions CRC Public Functions
  * @{
  */

/** @defgroup CRC_Public_Functions_Group1 Initialization functions
  * @brief Initialization and Configuration functions
  * @{
  */

/**
  * @brief  Initializes the CRC mode according to the specified parameters in
  *         the crc_handle_t and create the associated handle.
  * @param  hperh: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_crc_init(crc_handle_t *hperh)
{
	uint32_t tmp = 0;

	if (hperh == NULL)
		return ERROR;

	assert_param(IS_CRC(hperh->perh));
	assert_param(IS_CRC_MODE(hperh->init.mode));
	assert_param(IS_FUNC_STATE(hperh->init.chs_rev));
	assert_param(IS_FUNC_STATE(hperh->init.data_inv));
	assert_param(IS_FUNC_STATE(hperh->init.data_rev));
	assert_param(IS_FUNC_STATE(hperh->init.chs_inv));

	ald_crc_reset(hperh);
	__LOCK(hperh);

	CRC_ENABLE(hperh);

	tmp = hperh->perh->CR;

	tmp |= ((hperh->init.chs_rev << CRC_CR_CHSREV_POS) | (hperh->init.data_inv << CRC_CR_DATINV_POS) |
		(hperh->init.chs_inv << CRC_CR_CHSINV_POS) | (hperh->init.mode << CRC_CR_MODE_POSS) |
		(CRC_DATASIZE_8 << CRC_CR_DATLEN_POSS) | (hperh->init.data_rev << CRC_CR_DATREV_POS) |
		(0 << CRC_CR_BYTORD_POS));

	hperh->perh->CR = tmp;
	hperh->perh->SEED = hperh->init.seed;
	CRC_RESET(hperh);

	hperh->state = CRC_STATE_READY;

	__UNLOCK(hperh);
	return OK;
}

/**
  * @}
  */

/** @defgroup CRC_Public_Functions_Group2 Calculate functions
  * @brief Calculate functions
  * @{
  */

/**
  * @brief  Calculate the crc value of data by byte.
  * @param  hperh: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @param  buf: Pointer to data buffer
  * @param  size: The size of data to be calculate
  * @retval result, the result of a amount data
  */
uint32_t ald_crc_calculate(crc_handle_t *hperh, uint8_t *buf, uint32_t size)
{
	uint32_t i;
	uint32_t ret;

	assert_param(IS_CRC(hperh->perh));

	if (buf == NULL || size == 0)
		return 0;

	__LOCK(hperh);
	MODIFY_REG(hperh->perh->CR, CRC_CR_DATLEN_MSK, CRC_DATASIZE_8 << CRC_CR_DATLEN_POSS);
	hperh->state = CRC_STATE_BUSY;

	for (i = 0; i < size; i++)
		*((volatile uint8_t *)&(hperh->perh->DATA)) = buf[i];

	ret          = CRC->CHECKSUM;
	hperh->state = CRC_STATE_READY;
	__UNLOCK(hperh);

	return ret;
}

/**
  * @brief  Calculate the crc value of data by halfword.
  * @param  hperh: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @param  buf: Pointer to data buffer
  * @param  size: The size of data to be calculate,width is 2 bytes.
  * @retval result, the result of a amount data
  */
uint32_t ald_crc_calculate_halfword(crc_handle_t *hperh, uint16_t *buf, uint32_t size)
{
	uint32_t i;
	uint32_t ret;

	assert_param(IS_CRC(hperh->perh));

	if (buf == NULL || size == 0)
		return 0;

	__LOCK(hperh);
	MODIFY_REG(hperh->perh->CR, CRC_CR_DATLEN_MSK, CRC_DATASIZE_16 << CRC_CR_DATLEN_POSS);
	hperh->state = CRC_STATE_BUSY;

	for (i = 0; i < size; i++)
		*((volatile uint16_t *)&(hperh->perh->DATA)) = buf[i];

	ret          = CRC->CHECKSUM;
	hperh->state = CRC_STATE_READY;
	__UNLOCK(hperh);

	return ret;
}

/**
  * @brief  Calculate the crc value of data by word.
  * @param  hperh: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @param  buf: Pointer to data buffer
  * @param  size: The size of data to be calculate,width is 4 bytes
  * @retval result, the result of a amount data
  */
uint32_t ald_crc_calculate_word(crc_handle_t *hperh, uint32_t *buf, uint32_t size)
{
	uint32_t i;
	uint32_t ret;

	assert_param(IS_CRC(hperh->perh));

	if (buf == NULL || size == 0)
		return 0;

	__LOCK(hperh);
	MODIFY_REG(hperh->perh->CR, CRC_CR_DATLEN_MSK, CRC_DATASIZE_32 << CRC_CR_DATLEN_POSS);
	hperh->state = CRC_STATE_BUSY;

	for (i = 0; i < size; i++)
 		CRC->DATA = buf[i];

	for (i = 0; i < 3; i++);

	ret          = CRC->CHECKSUM;
	hperh->state = CRC_STATE_READY;
	__UNLOCK(hperh);

	return ret;
}

/**
  * @}
  */

#ifdef ALD_DMA
/** @defgroup CRC_Public_Functions_Group3 DMA operation functions
  * @brief DMA operation functions
  * @{
  */

/**
  * @brief  Calculate an amount of data used dma channel
  * @param  hperh: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @param  buf: Pointer to data buffer
  * @param  res: Pointer to result
  * @param  size: Amount of data to be Calculate
  * @param  channel: DMA channel as CRC transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_crc_calculate_by_dma(crc_handle_t *hperh, uint8_t *buf, uint32_t *res, uint16_t size, uint8_t channel)
{
	if (hperh->state != CRC_STATE_READY)
		return BUSY;

	if (buf == NULL || size == 0)
		return ERROR;

	__LOCK(hperh);
	MODIFY_REG(hperh->perh->CR, CRC_CR_DATLEN_MSK, CRC_DATASIZE_8 << CRC_CR_DATLEN_POSS);

	hperh->state = CRC_STATE_BUSY;

	hperh->cal_buf = buf;
	hperh->cal_res = res;

	if (hperh->hdma.perh == NULL)
		hperh->hdma.perh = DMA0;

	hperh->hdma.cplt_arg = (void *)hperh;
	hperh->hdma.cplt_cbk = &crc_dma_calculate_cplt;
	hperh->hdma.err_arg  = (void *)hperh;
	hperh->hdma.err_cbk  = &crc_dma_error;

	ald_dma_config_struct(&(hperh->hdma.config));
	hperh->hdma.config.data_width = DMA_DATA_SIZE_BYTE;
	hperh->hdma.config.src        = (void *)buf;
	hperh->hdma.config.dst        = (void *)&hperh->perh->DATA;
	hperh->hdma.config.size       = size;
	hperh->hdma.config.src_inc    = DMA_DATA_INC_BYTE;
	hperh->hdma.config.dst_inc    = DMA_DATA_INC_NONE;
	hperh->hdma.config.msel       = DMA_MSEL_CRC;
	hperh->hdma.config.msigsel    = DMA_MSIGSEL_NONE;
	hperh->hdma.config.channel    = channel;
	hperh->hdma.config.burst      = ENABLE;
	ald_dma_config_basic(&(hperh->hdma));

	__UNLOCK(hperh);
	CRC_DMA_ENABLE(hperh);

	return OK;
}

/**
  * @brief  Calculate an amount of data used dma channel,data width is half-word.
  * @param  hperh: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @param  buf: Pointer to half_word data buffer
  * @param  res: Pointer to result
  * @param  size: Amount of half_word data to be Calculate
  * @param  channel: DMA channel as CRC transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_crc_calculate_halfword_by_dma(crc_handle_t *hperh, uint16_t *buf, uint32_t *res, uint16_t size, uint8_t channel)
{
	if (hperh->state != CRC_STATE_READY)
		return BUSY;

	if (buf == NULL || size == 0)
		return ERROR;

	__LOCK(hperh);
	MODIFY_REG(hperh->perh->CR, CRC_CR_DATLEN_MSK, CRC_DATASIZE_16 << CRC_CR_DATLEN_POSS);

	hperh->state = CRC_STATE_BUSY;

	hperh->cal_buf = (uint8_t *)buf;
	hperh->cal_res = res;

	if (hperh->hdma.perh == NULL)
		hperh->hdma.perh = DMA0;

	hperh->hdma.cplt_arg = (void *)hperh;
	hperh->hdma.cplt_cbk = &crc_dma_calculate_cplt;
	hperh->hdma.err_arg  = (void *)hperh;
	hperh->hdma.err_cbk  = &crc_dma_error;

	ald_dma_config_struct(&(hperh->hdma.config));
	hperh->hdma.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdma.config.src        = (void *)buf;
	hperh->hdma.config.dst        = (void *)&hperh->perh->DATA;
	hperh->hdma.config.size       = size;
	hperh->hdma.config.src_inc    = DMA_DATA_INC_HALFWORD;
	hperh->hdma.config.dst_inc    = DMA_DATA_INC_NONE;
	hperh->hdma.config.msel       = DMA_MSEL_CRC;
	hperh->hdma.config.msigsel    = DMA_MSIGSEL_NONE;
	hperh->hdma.config.channel    = channel;
	hperh->hdma.config.burst      = ENABLE;
	ald_dma_config_basic(&(hperh->hdma));

	__UNLOCK(hperh);
	CRC_DMA_ENABLE(hperh);

	return OK;
}

/**
  * @brief  Calculate an amount of data used dma channel,data width is word.
  * @param  hperh: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @param  buf: Pointer to word data buffer
  * @param  res: Pointer to result
  * @param  size: Amount of word data to be Calculate
  * @param  channel: DMA channel as CRC transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_crc_calculate_word_by_dma(crc_handle_t *hperh, uint32_t *buf, uint32_t *res, uint16_t size, uint8_t channel)
{
	if (hperh->state != CRC_STATE_READY)
		return BUSY;

	if (buf == NULL || size == 0)
		return ERROR;

	__LOCK(hperh);
	MODIFY_REG(hperh->perh->CR, CRC_CR_DATLEN_MSK, CRC_DATASIZE_32 << CRC_CR_DATLEN_POSS);

	hperh->state = CRC_STATE_BUSY;

	hperh->cal_buf = (uint8_t *)buf;
	hperh->cal_res = res;

	if (hperh->hdma.perh == NULL)
		hperh->hdma.perh = DMA0;

	hperh->hdma.cplt_arg = (void *)hperh;
	hperh->hdma.cplt_cbk = &crc_dma_calculate_cplt;
	hperh->hdma.err_arg  = (void *)hperh;
	hperh->hdma.err_cbk  = &crc_dma_error;

	ald_dma_config_struct(&(hperh->hdma.config));
	hperh->hdma.config.data_width = DMA_DATA_SIZE_WORD;
	hperh->hdma.config.src        = (void *)buf;
	hperh->hdma.config.dst        = (void *)&hperh->perh->DATA;
	hperh->hdma.config.size       = size;
	hperh->hdma.config.src_inc    = DMA_DATA_INC_WORD;
	hperh->hdma.config.dst_inc    = DMA_DATA_INC_NONE;
	hperh->hdma.config.msel       = DMA_MSEL_CRC;
	hperh->hdma.config.msigsel    = DMA_MSIGSEL_NONE;
	hperh->hdma.config.channel    = channel;
	hperh->hdma.config.burst      = ENABLE;
	ald_dma_config_basic(&(hperh->hdma));

	__UNLOCK(hperh);
	CRC_DMA_ENABLE(hperh);

	return OK;
}


/**
  * @brief  Pauses the DMA Transfer.
  * @param  hperh: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_crc_dma_pause(crc_handle_t *hperh)
{
	__LOCK(hperh);
	CRC_DMA_DISABLE(hperh);
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Resumes the DMA Transfer.
  * @param  hperh: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_crc_dma_resume(crc_handle_t *hperh)
{
	__LOCK(hperh);
	CRC_DMA_ENABLE(hperh);
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Stops the DMA Transfer.
  * @param  hperh: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_crc_dma_stop(crc_handle_t *hperh)
{
	__LOCK(hperh);
	CRC_DMA_DISABLE(hperh);
	__UNLOCK(hperh);

	hperh->state = CRC_STATE_READY;
	return OK;
}

/**
  * @}
  */
#endif

/** @defgroup CRC_Public_Functions_Group4 Peripheral State and Errors functions
  * @brief    CRC State and Errors functions
  * @{
  */

/**
  * @brief  Returns the CRC state.
  * @param  hperh: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @retval CRC state
  */
crc_state_t ald_crc_get_state(crc_handle_t *hperh)
{
	assert_param(IS_CRC(hperh->perh));

	return hperh->state;
}
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup CRC_Private_Functions   CRC Private Functions
  *  @brief   CRC Private functions
  * @{
  */

/**
  * @brief  Reset the CRC peripheral.
  * @param  hperh: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @retval None
  */
void ald_crc_reset(crc_handle_t *hperh)
{
	hperh->perh->DATA = 0x0;
	hperh->perh->CR   = 0x2;
	hperh->perh->SEED = 0xFFFFFFFF;

	hperh->state = CRC_STATE_READY;
	__UNLOCK(hperh);
	return;
}

#ifdef ALD_DMA
/**
  * @brief  DMA CRC calculate process complete callback.
  * @param  arg: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @retval None
  */
static void crc_dma_calculate_cplt(void *arg)
{
	crc_handle_t *hperh = (crc_handle_t *)arg;

	*(hperh->cal_res) = CRC->CHECKSUM;
	CRC_DMA_DISABLE(hperh);

	hperh->state = CRC_STATE_READY;

	if (hperh->cal_cplt_cbk)
		hperh->cal_cplt_cbk(hperh);
}

/**
  * @brief  DMA CRC communication error callback.
  * @param  arg: Pointer to a crc_handle_t structure that contains
  *         the configuration information for the specified CRC module.
  * @retval None
  */
static void crc_dma_error(void *arg)
{
	crc_handle_t *hperh = (crc_handle_t *)arg;

	CRC_CLEAR_ERROR_FLAG(hperh);
	CRC_DMA_DISABLE(hperh);

	hperh->state = CRC_STATE_READY;

	if (hperh->err_cplt_cbk)
		hperh->err_cplt_cbk(hperh);
}
#endif
/**
  * @}
  */
#endif /* ALD_CRC */

/**
  * @}
  */

/**
  * @}
  */
