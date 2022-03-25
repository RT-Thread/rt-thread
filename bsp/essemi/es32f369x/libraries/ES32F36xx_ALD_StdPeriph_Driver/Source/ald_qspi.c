/**
  *********************************************************************************
  *
  * @file    ald_qspi.c
  * @brief   QSPI module driver.
  *
  * @version V1.0
  * @date    09 Nov 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          09 Nov 2019     AE Team         The first version
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

/** @defgroup QSPI QSPI
  * @brief QSPI module driver
  * @{
  */

#ifdef ALD_QSPI

/** @defgroup QSPI_Private_Functions   QSPI Private Functions
  * @brief  QSPI Private functions
  * @{
  */

/**
  * @brief  Wait for a flag state until timeout.
  * @param  hperh: QSPI handle
  * @param  timeout: Duration of the time out
  * @param  tickstart: tick start value
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t qspi_wait_for_idle(qspi_handle_t *hperh, uint32_t tickstart, uint32_t timeout)
{
	/* Wait until flag is in expected state */
	while (READ_BIT(hperh->perh->CR, QSPI_CR_IDLES_MSK) != QSPI_CR_IDLES_MSK) {
		/* Check for the Timeout */
		if (timeout != ALD_MAX_DELAY) {
			if ((timeout == 0U) || ((ald_get_tick() - tickstart) > timeout)) {
				return ERROR;
			}
		}
	}
	return OK;
}

/**
  * @brief  Get indirect read status.
  * @param  hperh: Pointer to a qspi_handle_t structure.
  * @param  status: Indirect status.
  * @retval Status, see @ref ald_status_t.
  */
static flag_status_t qspi_indrd_get_status(qspi_handle_t *hperh, qspi_indrd_flag_t status)
{
	assert_param(IS_QSPI_ALL(hperh->perh));
	assert_param(IS_QSPI_INDIRECT_READ_STATUS(status));

	if (hperh->perh->IRTR & status)
		return SET;

	return RESET;
}

/**
  * @}
  */

/** @defgroup QSPI_Public_Functions QSPI Public Functions
  * @brief QSPI Public Functions
  * @{
  */ 
/** @defgroup QSPI_Public_Functions_Group1 Basic execution functions
  * @brief QSPI basic execution functions 
  * @{
  */
/**
  * @brief Initializes the QSPI basic parameters.
  * @param hperh: Pointer to the QSPI qspi_handle_t structure.
  * @retval None.
  */
void ald_qspi_init(qspi_handle_t *hperh)
{
	assert_param(IS_QSPI_CLOCK_PRESCALER(hperh->init.clkdiv));
	assert_param(IS_QSPI_CLOCK_PHASE(hperh->init.chpa));
	assert_param(IS_QSPI_CLOCK_POLARITY(hperh->init.cpol));
	
	MODIFY_REG(hperh->perh->CR, QSPI_CR_BAUD_MSK | QSPI_CR_CPOL_MSK | QSPI_CR_CPHA_MSK | \
	                            QSPI_CR_PSL_MSK  | QSPI_CR_SWPP_MSK , (hperh->init.clkdiv << QSPI_CR_BAUD_POSS) | \
	                            (hperh->init.cpol << QSPI_CR_CPOL_POS) | \
	                            (hperh->init.chpa << QSPI_CR_CPHA_POS) | \
	                            (hperh->init.chipsel << QSPI_CR_PSL_POSS) | \
	                            (hperh->init.wrppin << QSPI_CR_SWPP_POS));
}

/**
  * @brief  DAC read. 
  * @param  addr: address.
  * @retval value
  */
uint32_t ald_qspi_dac_rd(uint32_t addr)
{
	return ((*(volatile uint32_t *)(addr)));
}

/**
  * @brief  DAC write . 
  * @param  addr: address.
  * @param  dat: data.
  * @retval None
  */
void ald_qspi_dac_wr(uint32_t addr, uint32_t dat)
{
	(*(volatile uint32_t *)(addr)) = dat;
}

/**
 * @brief Configure Read Operations.
 * @param hperh: Pointer to the QSPI qspi_handle_t structure.
 * @param rdcfg: Pointer to configuration structure for QSPI read operations.
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_qspi_read_config(qspi_handle_t * hperh, const qspi_read_cfg_t * rdcfg)
{
	ald_status_t status = ERROR;
	uint32_t tickstart = ald_get_tick();

	assert_param(IS_QSPI_RD_OPCODE(rdcfg->rdcde));
	assert_param(IS_QSPI_DCYLES(rdcfg->dcyles));
	assert_param(IS_QSPI_XFER_TYPE(rdcfg->datxfer));
	assert_param(IS_QSPI_XFER_TYPE(rdcfg->addxfer));
	assert_param(IS_QSPI_XFER_TYPE(rdcfg->instxfer));

	status = qspi_wait_for_idle(hperh, tickstart, QSPI_TIMEOUT_DEFAULT_VALUE);

	if (status != OK)
		return status;

	MODIFY_REG(hperh->perh->DRIR, QSPI_DRIR_RINST_MSK | QSPI_DRIR_MBEN_MSK | \
				      QSPI_DRIR_DCYC_MSK | QSPI_DRIR_ADMODE_MSK | \
				      QSPI_DRIR_DMODE_MSK | QSPI_DRIR_IMODE_MSK | \
				      QSPI_DRIR_DDRM_MSK, \
				     (rdcfg->rdcde | (rdcfg->dcyles << 24) | \
				     (rdcfg->addxfer << 12) | (rdcfg->instxfer << 8) | \
				     (rdcfg->ddrbit << QSPI_DRIR_DDRM_POS) | (rdcfg->modebit << QSPI_DRIR_MBEN_POS)) | \
				     (rdcfg->datxfer << QSPI_DRIR_DMODE_POSS));

	if (rdcfg->modebit)
		MODIFY_REG(hperh->perh->MBR, QSPI_MBR_MODEB_MSK, rdcfg->mbitval);

	return status;
}

/**
 * @brief Configure Write Operations.
 * @param hperh: Pointer to the QSPI qspi_handle_t structure.
 * @param wrcfg: Pointer to configuration structure for QSPI write operations.
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_qspi_write_config(qspi_handle_t * hperh, const qspi_write_cfg_t * wrcfg)
{
	ald_status_t status = ERROR;
	uint32_t tickstart = ald_get_tick();

	assert_param(IS_QSPI_WR_OPCODE(wrcfg->wrcde));
	assert_param(IS_QSPI_DCYLES(wrcfg->dcyles));
	assert_param(IS_QSPI_XFER_TYPE(wrcfg->datxfer));
	assert_param(IS_QSPI_XFER_TYPE(wrcfg->addxfer));

	status = qspi_wait_for_idle(hperh, tickstart, QSPI_TIMEOUT_DEFAULT_VALUE);

	if (status != OK)
		return status;

	MODIFY_REG(hperh->perh->DWIR, QSPI_DWIR_WINST_MSK | QSPI_DWIR_DCYC_MSK | \
				      QSPI_DWIR_ADMODE_MSK | QSPI_DWIR_DMODE_MSK,
	                              wrcfg->wrcde | \
				      (wrcfg->addxfer << 12) | \
				      (wrcfg->datxfer << 16) | \
				      (wrcfg->dcyles << 24));
	if (wrcfg->autowel)
		CLEAR_BIT(hperh->perh->DWIR, QSPI_DWIR_WELD_MSK);
	else
		SET_BIT(hperh->perh->DWIR, QSPI_DWIR_WELD_MSK);

	return status;
}

/**
 * @brief QSPI Device Delay Configuration.
 * @param hperh: Pointer to the QSPI qspi_handle_t structure.
 * @param dlycfg: Device delay configuration structure.
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_qspi_device_delay_config(qspi_handle_t * hperh, qspi_dly_cfg_t *dlycfg)
{
	ald_status_t status = ERROR;
	uint32_t tickstart = ald_get_tick();

	assert_param(IS_QSPI_ALL(hperh->perh));
	assert_param(IS_QSPI_DEVICE_DELAY_CCSOT(dlycfg->ccsot));
	assert_param(IS_QSPI_DEVICE_DELAY_CSEOT(dlycfg->cseot));
	assert_param(IS_QSPI_DEVICE_DELAY_CSDADS(dlycfg->csdads));
	assert_param(IS_QSPI_DEVICE_DELAY_CSDA(dlycfg->csda));

	status = qspi_wait_for_idle(hperh, tickstart, QSPI_TIMEOUT_DEFAULT_VALUE);

	if (status != OK)
		return status;

	MODIFY_REG(hperh->perh->DDLR, QSPI_DDLR_CSSOT_MSK | QSPI_DDLR_CSEOT_MSK | QSPI_DDLR_CSDADS_MSK | QSPI_DDLR_CSDA_MSK, \
				      dlycfg->ccsot | (dlycfg->cseot << 8) | (dlycfg->csdads << 16) | (dlycfg->csda << 24));
	return status;
}

/**
 * @brief QSPI Read Data Capture Configuration.
 * @param hperh: Pointer to the QSPI qspi_handle_t structure.
 * @param dtcptcfg: Data capture configuration structure.  
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_qspi_read_data_capture_config(qspi_handle_t * hperh, qspi_data_capture_cfg_t *dtcptcfg)
{
	ald_status_t status = ERROR;
	uint32_t tickstart = ald_get_tick();

	assert_param(IS_QSPI_ALL(hperh->perh));
	assert_param(IS_QSPI_READ_DATA_CAPTURE_DELAY_READ(dtcptcfg->dlydcl));
	assert_param(IS_QSPI_READ_DATA_SAMPLE_EDGE(dtcptcfg->smpledge));
	assert_param(IS_QSPI_READ_DATA_DELAY_TRANSMIT(dtcptcfg->dlytd));

	status = qspi_wait_for_idle(hperh, tickstart, QSPI_TIMEOUT_DEFAULT_VALUE);

	if (status != OK)
		return status;

	MODIFY_REG(hperh->perh->RDCR, QSPI_RDCR_BYLPC_MSK | QSPI_RDCR_DLYR_MSK | QSPI_RDCR_SMES_MSK | QSPI_RDCR_DLYT_MSK, \
				      0x1U | (dtcptcfg->dlydcl << 1) | (dtcptcfg->smpledge << 5) | (dtcptcfg->dlytd << 16));
	return status;
}

/**
 * @brief QSPI Flash memory Configuration.
 * @param hperh: Pointer to the QSPI qspi_handle_t structure.
 * @param devcfg: flash parameter configuration structure.  
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_qspi_device_size_config(qspi_handle_t *hperh, qspi_device_size_t * devcfg)
{
	ald_status_t status = ERROR;
	uint32_t tickstart = ald_get_tick();

	assert_param(IS_QSPI_ADDR_SIZE(devcfg->addr));
	assert_param(IS_QSPI_PAGE_SIZE(devcfg->page));
	assert_param(IS_QSPI_BLOCK_SIZE(devcfg->blk));
	assert_param(IS_QSPI_NSS_SIZE(devcfg->cs0));
	assert_param(IS_QSPI_NSS_SIZE(devcfg->cs1));
	assert_param(IS_QSPI_NSS_SIZE(devcfg->cs2));
	assert_param(IS_QSPI_NSS_SIZE(devcfg->cs3));

	status = qspi_wait_for_idle(hperh, tickstart, QSPI_TIMEOUT_DEFAULT_VALUE);

	if (status != OK)
		return status;

	MODIFY_REG(hperh->perh->DSCR, QSPI_DSCR_ADSIZE_MSK | QSPI_DSCR_PASIZE_MSK | QSPI_DSCR_BKSIZE_MSK | QSPI_DSCR_CS0SIZE_MSK |  \
	                              QSPI_DSCR_CS1SIZE_MSK | QSPI_DSCR_CS2SIZE_MSK | QSPI_DSCR_CS3SIZE_MSK, \
                  	              (devcfg->addr << QSPI_DSCR_ADSIZE_POSS) | \
	                              (devcfg->page << QSPI_DSCR_PASIZE_POSS) | \
	                              (devcfg->blk  << QSPI_DSCR_BKSIZE_POSS) | \
	                              (devcfg->cs0  << QSPI_DSCR_CS0SIZE_POSS) | \
	                              (devcfg->cs1  << QSPI_DSCR_CS1SIZE_POSS) | \
	                              (devcfg->cs2  << QSPI_DSCR_CS2SIZE_POSS) | \
	                              (devcfg->cs3  << QSPI_DSCR_CS3SIZE_POSS));
	return OK;
}

/**
  * @brief Initializes the QSPI direct access according to the specified parameters
  *        in the associated handle.
  * @param hperh: Pointer to the QSPI qspi_handle_t structure.
  * @param dcfg : structure that contains the indirect read command configuration information.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t qspi_dac_config(qspi_handle_t * hperh, qspi_dac_cfg_t * dcfg)
{
	ald_status_t status = ERROR;
	uint32_t tickstart = ald_get_tick();

	assert_param(IS_QSPI_WR_OPCODE(dcfg->wrinit.wrcde));
	assert_param(IS_QSPI_DCYLES(dcfg->wrinit.dcyles));
	assert_param(IS_QSPI_XFER_TYPE(dcfg->wrinit.datxfer));
	assert_param(IS_QSPI_XFER_TYPE(dcfg->wrinit.addxfer));
	assert_param(IS_QSPI_XFER_TYPE(dcfg->wrinit.instxfer));

	status = qspi_wait_for_idle(hperh, tickstart, QSPI_TIMEOUT_DEFAULT_VALUE);

	if (status != OK)
		return status;

	QSPI_DISABLE(hperh);
	ald_qspi_init(hperh);

	if (ald_qspi_write_config(hperh, &dcfg->wrinit) != OK)
		return ERROR;
	if (ald_qspi_read_config(hperh, &dcfg->rdinit) != OK)
		return ERROR;
	
	if (dcfg->addrremap)
		MODIFY_REG(hperh->perh->RAR, QSPI_RAR_READDR_MSK, dcfg->remapaddr);

	MODIFY_REG(hperh->perh->CR, QSPI_CR_DTRM_MSK | QSPI_CR_ADEN_MSK | QSPI_CR_XIPIM_MSK | \
				    QSPI_CR_XIPNX_MSK | QSPI_CR_AREN_MSK | QSPI_CR_DMAEN_MSK, \
				    dcfg->dtrprtcol << 24 | dcfg->ahbdecoder << 23);
	QSPI_ENABLE(hperh);
	return OK;
}

/**
  * @}
  */

/** @defgroup QSPI_Public_Functions_Group2 Indirect and stig access execution functions
  * @brief QSPI indirect and stig access execution functions
  * @{
  */
/**
  * @brief Initializes the QSPI indirect access according to the specified parameters
  *        in the associated handle.
  * @param hperh: Pointer to the QSPI qspi_handle_t structure.
  * @param indcfg: Pointer to indirect access initialization structure qspi_indac_config_t.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_qspi_indac_config(qspi_handle_t * hperh, qspi_indac_cfg_t *indcfg)
{
	ald_status_t status = ERROR;
	uint32_t tickstart = ald_get_tick();

	assert_param(IS_QSPI_ALL(hperh->perh));
	assert_param(IS_QSPI_SRAM_PARTITION(indcfg->srampt));
	assert_param(IS_QSPI_INDIRECT_TRIGGER_RANGE(indcfg->trgrng));
	assert_param(IS_QSPI_INDIRECT_READ_WATERMARK(indcfg->rdwmark));

	status = qspi_wait_for_idle(hperh, tickstart, QSPI_TIMEOUT_DEFAULT_VALUE);

	if (status != OK)
		return status;

	QSPI_DISABLE(hperh);

	MODIFY_REG(hperh->perh->SPR, QSPI_SPR_SRAMPS_MSK, indcfg->srampt);
	MODIFY_REG(hperh->perh->IATR, QSPI_IATR_INDTAD_MSK, indcfg->trgaddr);
	MODIFY_REG(hperh->perh->ITARR, QSPI_ITARR_RNGW_MSK, indcfg->trgrng);
	MODIFY_REG(hperh->perh->IWTWR, QSPI_IWTWR_VAULE_MSK, indcfg->wrwmark);
	MODIFY_REG(hperh->perh->IRTWR, QSPI_IRTWR_VAULE_MSK, indcfg->rdwmark);

	QSPI_ENABLE(hperh);

	return OK;
}

/**
  * @brief QSPI write data by interrupt. 
  * @param hperh: Pointer to a qspi_handle_t structure.
  * @param saddr: Write start address.
  * @param psrc: Pointer to source data buffer.
  * @param size : Write bytes number.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_qspi_indac_transmit_by_it(qspi_handle_t *hperh, uint32_t saddr, uint8_t *psrc,  uint32_t size)
{
	uint32_t i = 0;
	uint32_t tmp = 0, pgsize = 0;
	assert_param(IS_QSPI_ALL(hperh->perh));

	if ((psrc == NULL) || (size == 0))
		return ERROR;

	hperh->state   = QSPI_STATE_BUSY_TX;
	hperh->rx_buf  = NULL;
	hperh->rx_cnt  = 0;
	hperh->rx_size = 0;
	hperh->tx_buf  = psrc;
	hperh->tx_cnt  = 0;
	hperh->tx_size = size;

	tmp =  READ_REG(hperh->perh->DSCR);
	pgsize = (tmp & 0xfff0) >> 4;

	if (size >= pgsize)
		tmp = pgsize;
	else
		tmp = size;

	hperh->tx_cnt += tmp;

	ald_qspi_clear_it_flag(hperh, QSPI_IF_INDCF);
	MODIFY_REG(hperh->perh->IWTSAR, QSPI_IWTSAR_ADDR_MSK, saddr);
	MODIFY_REG(hperh->perh->IWTNR, QSPI_IWTNR_NUM_MSK, size);
	ald_qspi_interrupt_config(hperh, QSPI_IT_INDTWF, ENABLE);
	ald_qspi_interrupt_config(hperh, QSPI_IT_INDCF, ENABLE);

	/* Trigger indirect write */
	SET_BIT(hperh->perh->IWTR, QSPI_IWTR_WRST_MSK);

	for (i = 0; i < (tmp / 4); ++i)
		*(__IO uint32_t *)QSPI_MEMORY_ADDRESS = (*(uint32_t *)(psrc + 4 * i));

	return OK;
}

/**
  * @brief Transmit data to flash by poll. 
  * @param hperh: Pointer to a qspi_handle_t structure.
  * @param saddr: Write start address.
  * @param psrc: Pointer to source data buffer.
  * @param size: Write bytes number.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_qspi_indac_transmit_by_poll(qspi_handle_t *hperh, uint32_t saddr, uint8_t *psrc,  uint32_t size)
{
	uint32_t i, j = 0, cnt = 0;
	uint32_t tmp = 0;
	uint32_t idx = 0, txsm = 0;
	assert_param(IS_QSPI_ALL(hperh->perh));

	if ((psrc == NULL) || (size == 0))
		return ERROR;

	MODIFY_REG(hperh->perh->IWTSAR, QSPI_IWTSAR_ADDR_MSK, saddr);
	MODIFY_REG(hperh->perh->IWTNR, QSPI_IWTNR_NUM_MSK, size);

	/* Counter write times totally */
	if (size % 4)
		cnt = (size / 4) + 1;
	else
		cnt = size / 4;
	/* Get transmit SRAM partition (unit:4bytes)*/
	tmp = READ_REG(hperh->perh->SPR);
	txsm = QSPI_SRAM_SIZE - tmp;
	if (txsm == 0) return ERROR;
	if (cnt <= txsm) {
		/* Trigger indirect write */
		SET_BIT(hperh->perh->IWTR, QSPI_IWTR_WRST_MSK);
		for (i = 0; i < cnt; ++i)
			*(__IO uint32_t *)QSPI_MEMORY_ADDRESS = (*(uint32_t *)(psrc + 4 *i));
	} else {
		SET_BIT(hperh->perh->IWTR, QSPI_IWTR_WRST_MSK);
		for (j = 0; j < (cnt / txsm); ++j) {
			for (i = 0; i < txsm; ++i) {
				*(__IO uint32_t *)QSPI_MEMORY_ADDRESS = (*(uint32_t *)(psrc + idx + 4 *i));
			}
			idx += txsm * 4;
			do {
				tmp = READ_REG(hperh->perh->SFLR);
				tmp = (tmp >> 16) & 0xffff;
			} while (tmp != 0);
		}

		for (j = 0; j < (cnt % txsm); ++j)
			*(__IO uint32_t *)QSPI_MEMORY_ADDRESS = (*(uint32_t *)(psrc + idx + 4 *j));
	}
	/* Wait for indirect read operation completely */
	do {
		tmp = READ_REG(hperh->perh->IWTR);
	} while ( tmp & 0x4);

	return OK;
}

/**
  * @brief Read data from flash by poll. 
  * @param hperh: Pointer to a qspi_handle_t structure.
  * @param saddr: Read start address.
  * @param desbuf: Pointer to data buffer.
  * @param size: Read bytes number.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_qspi_indac_read_by_poll(qspi_handle_t *hperh, uint32_t saddr, uint8_t *desbuf, uint16_t size)
{

	uint32_t i = 0, j = 0, cnt = 0;
	uint32_t tmp = 0;
	uint32_t idx = 0, rxsm = 1;

	assert_param(IS_QSPI_ALL(hperh->perh));

	if ((desbuf == NULL) || (size == 0))
		return ERROR;

	MODIFY_REG(hperh->perh->IRTSAR, QSPI_IRTSAR_ADDR_MSK, saddr);
	MODIFY_REG(hperh->perh->IRTNR, QSPI_IRTNR_NUM_MSK, size);
	/* Counter read times totally */
	if (size % 4)
		cnt = (size / 4) + 1;
	else
		cnt = size / 4;
	/* Get read SRAM partition (unit: 4bytes)*/
	rxsm = READ_REG(hperh->perh->SPR) + 1;
	if (cnt <= rxsm) {
		SET_BIT(hperh->perh->IRTR, QSPI_IRTR_RDST_MSK);
		do {
			tmp = READ_REG(hperh->perh->SFLR);
			tmp = tmp & 0x0000ffffU;
		} while (tmp != cnt);
		for (i = 0; i < cnt; ++i)
			*(uint32_t *)(desbuf + 4 * i) = *(__IO uint32_t *)QSPI_MEMORY_ADDRESS;
	} else {
		SET_BIT(hperh->perh->IRTR, QSPI_IRTR_RDST_MSK);
		for (j = 0; j < (cnt / rxsm); ++j) {
			do {
				tmp = READ_REG(hperh->perh->SFLR);
				tmp = tmp & 0x0000ffffU;
			} while (tmp != rxsm);
			for (i = 0; i < rxsm; ++i) {
				*(uint32_t *)(desbuf + idx + 4 * i) = *(__IO uint32_t *)QSPI_MEMORY_ADDRESS;
			}
			idx += rxsm * 4;
		}
		do {
			tmp = READ_REG(hperh->perh->SFLR);
			tmp = tmp & 0x0000ffffU;
		} while ( tmp != (cnt % rxsm));

		for (j = 0; j < (cnt % rxsm); ++j) {
			*(uint32_t *)(desbuf + idx + 4 * i) = *(__IO uint32_t *)QSPI_MEMORY_ADDRESS;
		}
	}
	/* Wait for indirect read operation completely */
	do {
		tmp = READ_REG(hperh->perh->IRTR);
	} while (tmp & 0x04);

	return OK;
}

/**
  * @brief QSPI read data by interrupt. 
  * @param hperh: Pointer to a qspi_handle_t structure.
  * @param saddr: Read start address.
  * @param desbuf: Pointer to destination data buffer.
  * @param size: Read bytes length.
  * @retval Status, see @ref ald_status_t.
  */

ald_status_t ald_qspi_indac_read_by_it(qspi_handle_t *hperh, uint32_t saddr, uint8_t *desbuf, uint16_t size)
{
	assert_param(IS_QSPI_ALL(hperh->perh));

	if ((desbuf == NULL) || (size == 0))
		return ERROR;

	hperh->state   = QSPI_STATE_BUSY_RX;
	hperh->rx_buf  = desbuf;
	hperh->rx_cnt  = 0;
	hperh->rx_size = size;
	hperh->tx_buf  = NULL;
	hperh->tx_cnt  = 0;
	hperh->tx_size = 0;

	ald_qspi_clear_it_flag(hperh, QSPI_IF_INDCF);
	MODIFY_REG(hperh->perh->IRTSAR, QSPI_IRTSAR_ADDR_MSK, saddr);
	MODIFY_REG(hperh->perh->IRTNR, QSPI_IRTNR_NUM_MSK, size);
	ald_qspi_interrupt_config(hperh, QSPI_IT_INDTWF, ENABLE);
	ald_qspi_interrupt_config(hperh, QSPI_IT_INDCF, ENABLE);
	SET_BIT(hperh->perh->IRTR, QSPI_IRTR_RDST_MSK);

	return OK;
}

/**
 * @brief Execute a STIG command.
 * @param hperh: Pointer to the QSPI qspi_handle_t structure.
 * @param stigcmd: Pointer to a structure that describes the STIG command.
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_qspi_execute_stig_cmd(qspi_handle_t * hperh, const qspi_stig_cmd_t * stigcmd)
{
	uint32_t i;
	ald_status_t status = ERROR;
	uint32_t tickstart = ald_get_tick();

	assert_param(IS_QSPI_ALL(hperh->perh));
	assert_param(stigcmd->addr_len <= 4);
	assert_param(stigcmd->wr_len <= 8);
	assert_param(stigcmd->rd_len <= 8);
	assert_param(stigcmd->d_sycle < 32);

	if (stigcmd->wr_len)
		assert_param(stigcmd->wr_buf);
	if (stigcmd->rd_len)
		assert_param(stigcmd->rd_buf);

	/* wait for Flash idle */
	status = qspi_wait_for_idle(hperh, tickstart, QSPI_TIMEOUT_DEFAULT_VALUE);

	if (status != OK)
		return ERROR;

	MODIFY_REG(hperh->perh->FCR, QSPI_FCR_OPCODE_MSK | QSPI_FCR_DUMNUM_MSK , ((stigcmd->code << 24) | (stigcmd->d_sycle << 7)));

	if (stigcmd->wr_len) {
		uint32_t buffer[2] = {0, 0};
		uint8_t * dst = (uint8_t *) buffer;
		uint8_t * src = stigcmd->wr_buf;

		MODIFY_REG(hperh->perh->FCR, QSPI_FCR_WDNUM_MSK, (stigcmd->wr_len - 1) << QSPI_FCR_WDNUM_POSS);
		SET_BIT(hperh->perh->FCR, QSPI_FCR_WREN_MSK);

		for (i = 0; i < stigcmd->wr_len; i++)
			dst[i] = src[i];

		hperh->perh->FCWLR = buffer[0];
		hperh->perh->FCWHR = buffer[1];
	} else {
		CLEAR_BIT(hperh->perh->FCR, QSPI_FCR_WDNUM_MSK);
		CLEAR_BIT(hperh->perh->FCR, QSPI_FCR_WREN_MSK);
	}

	if (stigcmd->addr_len) {
		SET_BIT(hperh->perh->FCR, QSPI_FCR_ADDREN_MSK);

		MODIFY_REG(hperh->perh->FCR, QSPI_FCR_ADNUM_MSK, (stigcmd->addr_len - 1) << QSPI_FCR_ADNUM_POSS);
		MODIFY_REG(hperh->perh->FCAR, QSPI_FCAR_CMDADR_MSK, stigcmd->addr);
	} else {
		CLEAR_BIT(hperh->perh->FCR, QSPI_FCR_ADDREN_MSK);
		CLEAR_BIT(hperh->perh->FCR, QSPI_FCR_ADNUM_MSK);
		CLEAR_BIT(hperh->perh->FCAR, QSPI_FCAR_CMDADR_MSK);
	}

	if (stigcmd->mode_bit) {
		SET_BIT(hperh->perh->FCR, QSPI_FCR_MODBEN_MSK);
		MODIFY_REG(hperh->perh->MBR, QSPI_MBR_MODEB_MSK, stigcmd->val);
	} else {
		CLEAR_BIT(hperh->perh->FCR, QSPI_FCR_MODBEN_MSK);
		CLEAR_BIT(hperh->perh->MBR, QSPI_MBR_MODEB_MSK);
	}

	if (stigcmd->rd_len) {
		SET_BIT(hperh->perh->FCR, QSPI_FCR_RDEN_MSK);
		MODIFY_REG(hperh->perh->FCR, QSPI_FCR_RDNUM_MSK, (stigcmd->rd_len - 1) << QSPI_FCR_RDNUM_POSS);
	} else {
		CLEAR_BIT(hperh->perh->FCR, QSPI_FCR_RDEN_MSK);
		CLEAR_BIT(hperh->perh->FCR, QSPI_FCR_RDNUM_MSK);
	}

	/* Start command execution */
	SET_BIT(hperh->perh->FCR, QSPI_FCR_CMDT_MSK);

	while (hperh->perh->FCR & QSPI_FCR_CMDS_MSK);

	/* Read data if any */
	if (stigcmd->rd_len) {
		uint32_t buffer[2] = { 0, 0 };
		const uint8_t * src = (const uint8_t *)buffer;
		uint8_t * dst = stigcmd->rd_buf;

		buffer[0] = hperh->perh->FCRLR;
		buffer[1] = hperh->perh->FCRHR;

		for (i = 0; i < stigcmd->rd_len; i++) {
			dst[i] = src[i];
		}
	}

	return OK;
}

#ifdef ALD_DMA
/**
  * @brief  Sends an amount of data with DMA. 
  * @param  hperh: Pointer to a qspi_handle_t structure.
  * @param  addr: Write start address.
  * @param  psrc: Pointer to data buffer.
  * @param size: Write data bytes.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_qspi_indac_transmit_by_dma(qspi_handle_t *hperh, uint32_t addr, uint8_t *psrc, uint16_t size)
{
	uint16_t cnt = 0;
	uint32_t *tmp = (uint32_t*)psrc;
	/* Get Indirect Read Trigger Address */
	__IO uint32_t *data_reg = (uint32_t *)hperh->perh->IATR;

	assert_param(IS_QSPI_ALL(hperh->perh));

	if ((psrc == NULL) || (size == 0))
		return ERROR;

	MODIFY_REG(hperh->perh->IWTSAR, QSPI_IWTSAR_ADDR_MSK, addr);
	MODIFY_REG(hperh->perh->IWTNR, QSPI_IWTNR_NUM_MSK, size);
	QSPI_DMA_ENABLE(hperh);
	if (size % 4)
		cnt = (size / 4) + 1;
	else
		cnt = size / 4;

	__LOCK(hperh);

	hperh->hdma.perh     = DMA0;
	hperh->hdma.cplt_cbk = NULL;
	ald_dma_config_struct(&hperh->hdma.config);

	hperh->hdma.config.data_width = DMA_DATA_SIZE_WORD;
	hperh->hdma.config.src        = (void *)tmp;
	hperh->hdma.config.dst        = (void *)data_reg;
	hperh->hdma.config.size	      = cnt;
	hperh->hdma.config.src_inc    = DMA_DATA_INC_WORD;
	hperh->hdma.config.dst_inc    = DMA_DATA_INC_NONE;
	hperh->hdma.config.msel	      = DMA_MSEL_QSPI;
	hperh->hdma.config.msigsel    = DMA_MSIGSEL_QSPI_WRITE;
	hperh->hdma.config.channel    = 0;
	hperh->hdma.config.R_power    = DMA_R_POWER_4;
	hperh->hdma.config.burst      = ENABLE;
	ald_dma_config_basic(&hperh->hdma);

	/* Trigger indirect write */
	SET_BIT(hperh->perh->IWTR, QSPI_IWTR_WRST_MSK);
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief Receive an amount of data with DMA.
  * @param hperh: Pointer to a qspi_handle_t structure.
  * @param addr: Read start address.
  * @param pdbuf: Pointer to data buffer.
  * @param size: Read data bytes.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_qspi_indac_read_by_dma(qspi_handle_t *hperh, uint32_t addr, uint8_t *pdbuf, uint16_t size)
{
	uint16_t cnt = 0;
	ald_status_t status = OK;
	uint32_t *tmp = (uint32_t *)pdbuf;
	/* Get Indirect Read Trigger Address */
	__IO uint32_t *data_reg = (uint32_t *)hperh->perh->IATR;

	assert_param(IS_QSPI_ALL(hperh->perh));

	if ((pdbuf == NULL) || (size == 0))
		return ERROR;

	MODIFY_REG(hperh->perh->IRTSAR, QSPI_IRTSAR_ADDR_MSK, addr);
	MODIFY_REG(hperh->perh->IRTNR, QSPI_IRTNR_NUM_MSK, size);

	QSPI_DMA_ENABLE(hperh);

	if (size % 4)
		cnt = (size / 4) + 1;
	else
		cnt = size / 4;

	__LOCK(hperh);

	hperh->hdma.perh = DMA0;
	hperh->hdma.cplt_cbk = NULL;
	ald_dma_config_struct(&hperh->hdma.config);

	hperh->hdma.config.data_width = DMA_DATA_SIZE_WORD;
	hperh->hdma.config.src        = (void *)data_reg;
	hperh->hdma.config.dst        = (void *)tmp;
	hperh->hdma.config.size       = cnt;
	hperh->hdma.config.src_inc    = DMA_DATA_INC_NONE;
	hperh->hdma.config.dst_inc    = DMA_DATA_INC_WORD;
	hperh->hdma.config.msel       = DMA_MSEL_QSPI;
	hperh->hdma.config.msigsel    = DMA_MSIGSEL_QSPI_READ;
	hperh->hdma.config.channel    = 0;
	hperh->hdma.config.R_power    = DMA_R_POWER_4;
	hperh->hdma.config.burst      = ENABLE;
	ald_dma_config_basic(&hperh->hdma);

	/* Trigger indirect write */
	SET_BIT(hperh->perh->IRTR, QSPI_IRTR_RDST_MSK);
	__UNLOCK(hperh);

	return status;
}
#endif

/**
 * @}
 */

/** @defgroup QSPI_Public_Functions_Group3 Status functions
  * @brief QSPI status functions
  * @{
  */
/**
  * @brief  Get the status of QSPI interrupt flag.
  * @param  hperh: Pointer to a qspi_handle_t structure.
  * @param  flag: Specifies the QSPI interrupt flag.
  *         This parameter can be one of the @ref qspi_flag_t.
  * @retval Status, see @ref flag_status_t.
  */
flag_status_t qspi_get_flag_status(qspi_handle_t *hperh, qspi_flag_t flag)
{
	assert_param(IS_QSPI_ALL(hperh->perh));
	assert_param(IS_QSPI_IF(flag));

	if (hperh->perh->IFR & flag)
		return SET;

	return RESET;
}

/**
  * @brief  Clear the QSPI interrupt flag.
  * @param  hperh: Pointer to a qspi_handle_t structure.
  * @param  flag: Specifies the QSPI interrupt flag.
  *         This parameter can be one of the @ref qspi_flag_t.
  * @retval None
  */
void ald_qspi_clear_it_flag(qspi_handle_t *hperh, qspi_flag_t flag)
{
	assert_param(IS_QSPI_ALL(hperh->perh));
	assert_param(IS_QSPI_IF(flag));

	hperh->perh->IFR = flag;

	return;
}

/**
 * @brief Read QSPI SRAM fill level.
 * @param hperh: Pointer to the QSPI qspi_handle_t structure.
 * @param srt: QSPI embeded SRAM type,the value can be one of @ref qspi_sram_t.
 * @retval sram fill level value.
 */
uint16_t qspi_read_sram_fill_level(qspi_handle_t * hperh, qspi_sram_t srt)
{
	assert_param(IS_QSPI_ALL(hperh->perh));
	assert_param(IS_QSPI_INDIRECT_SRAM_FILL_TYPE(srt));

	if (srt == QSPI_SRAM_RD)
		return READ_BITS(hperh->perh->SFLR, QSPI_SFLR_INDRSFL_MSK, QSPI_SFLR_INDRSFL_POSS);

	return READ_BITS(hperh->perh->SFLR, QSPI_SFLR_INDWSFL_MSK, QSPI_SFLR_INDWSFL_POSS);
}

/**
 * @brief QSPI Write Protect Configuration.
 * @param hperh: Pointer to the QSPI qspi_handle_t structure.
 * @param wpcfg: Pointer to the QSPI write protect configuration structer.
 * @retval None.
 */
void ald_qspi_write_proect_config(qspi_handle_t * hperh, qspi_wr_protect_t * wpcfg)
{
	assert_param(IS_QSPI_ALL(hperh->perh));

	MODIFY_REG(hperh->perh->WPLR, QSPI_WPLR_LBLKNUM_MSK, wpcfg->lowblk);
	MODIFY_REG(hperh->perh->WPHR, QSPI_WPHR_HBLKNUM_MSK, wpcfg->upblk);
	QSPI_WRITE_PROTECT_ENABLE(hperh);

	return;
}

/**
 * @brief QSPI Write Protect Inversion.
 * @param hperh: Pointer to the QSPI qspi_handle_t structure.
 * @param state: SRAM protect inversion state.
 * 	  This parameter can be:
 *		@arg ENABLE
 *		@arg DISABLE
 * @retval None.
 */
void ald_qspi_write_proect_inverse(qspi_handle_t * hperh, type_func_t state)
{
	assert_param(IS_FUNC_STATE(state));
	assert_param(IS_QSPI_ALL(hperh->perh));

	if (state) {
		QSPI_WRITE_PROTECT_DISABLE(hperh);
		SET_BIT(hperh->perh->WPCR, QSPI_WPCR_WPINV_MSK);
		QSPI_WRITE_PROTECT_ENABLE(hperh);
	}
	else {
		QSPI_WRITE_PROTECT_DISABLE(hperh);
		SET_BIT(hperh->perh->WPCR, QSPI_WPCR_WPINV_MSK);
		QSPI_WRITE_PROTECT_ENABLE(hperh);
	}

	return;
}

/**
  * @brief  QSPI interrupt handler
  * @retval None
  */
void ald_qspi_irq_handler(qspi_handle_t *hperh)
{
	uint32_t regs = 0;
	uint32_t tmp = 0, i = 0;

	regs = READ_REG(hperh->perh->DSCR);
	regs = (regs & 0x0000fff0) >> 4;

	// indirect transmit
	if (hperh->state == QSPI_STATE_BUSY_TX) {

		//QSPI indirect transmit(xfer length longer than watermark value)
		if (qspi_get_flag_status(hperh, QSPI_IF_INDTWF) == SET) {
			ald_qspi_clear_it_flag(hperh, QSPI_IF_INDTWF);
			tmp = hperh->tx_size - hperh->tx_cnt;
			if (tmp > regs) {
				for (i = 0; i < (regs / 4); ++i) {
					*(__IO uint32_t *)QSPI_MEMORY_ADDRESS = (*(uint32_t *)(hperh->tx_buf + hperh->tx_cnt + 4 * i));
				}
				hperh->tx_cnt += regs;
			} else {
				for (i = 0; i < (tmp / 4); ++i) {
					*(__IO uint32_t *)QSPI_MEMORY_ADDRESS = (*(uint32_t *)(hperh->tx_buf + hperh->tx_cnt + 4 * i));
				}
				hperh->tx_cnt += tmp;
			}
		}
		//QSPI indirect transmit completely
		if (qspi_get_flag_status(hperh, QSPI_IF_INDCF) == SET) {
			ald_qspi_clear_it_flag(hperh, QSPI_IF_INDCF);
			ald_qspi_interrupt_config(hperh, QSPI_IT_INDTWF, DISABLE);
			//transmit completely callback
		}

	}

	// indirect receive
	if (hperh->state == QSPI_STATE_BUSY_RX) {
		if (qspi_get_flag_status(hperh, QSPI_IF_INDTWF) == SET) {
			ald_qspi_clear_it_flag(hperh, QSPI_IF_INDTWF);
			tmp = READ_REG(hperh->perh->SFLR);
			tmp = tmp & 0xffff;

			for (i = 0; i < tmp; ++i) {
				*(uint32_t *)(hperh->rx_buf + hperh->rx_cnt + i*4) = *(__IO uint32_t *)QSPI_MEMORY_ADDRESS;
			}
			hperh->rx_cnt += tmp*4;
		}

		if (qspi_get_flag_status(hperh, QSPI_IF_INDCF) == SET) {
			ald_qspi_clear_it_flag(hperh, QSPI_IF_INDCF);
			ald_qspi_interrupt_config(hperh, QSPI_IT_INDTWF, DISABLE);

			tmp = READ_REG(hperh->perh->SFLR);
			tmp = tmp & 0xffff;

			for (i = 0; i < tmp; ++i) {
				*(uint32_t *)(hperh->rx_buf + hperh->rx_cnt + i*4) = *(__IO uint32_t *)QSPI_MEMORY_ADDRESS;
			}
		}
	}
}

/**
  * @brief  Enable/disable the specified QSPI interrupts.
  * @param  hperh: Pointer to a qspi_handle_t structure.
  * @param  it: Specifies the QSPI interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref qspi_it_t.
  * @param  state: New state of the specified QSPI interrupts.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_qspi_interrupt_config(qspi_handle_t *hperh, qspi_it_t it, type_func_t state)
{
	assert_param(IS_QSPI_ALL(hperh->perh));
	assert_param(IS_QSPI_IT(it));
	assert_param(IS_FUNC_STATE(state));

	if (state == ENABLE)
		hperh->perh->IMR |= (uint32_t)it;
	else
		hperh->perh->IMR &= (uint32_t)(~it);

	return;
}

/**
  * @brief  Configure the QSPI legacy . 
  * @param  hperh: Pointer to a qspi_handle_t structure.
  * @param  config: structure that contains the legacy configuration information.
  * @retval None
  */
void ald_qspi_legacy_config(qspi_handle_t* hperh, const qspi_legacy_cfg_t *config)
{
	assert_param(IS_QSPI_ALL(hperh->perh));

	MODIFY_REG(hperh->perh->TXHR, QSPI_TXHR_TXTH_MSK, config->tx_thrd);
	MODIFY_REG(hperh->perh->RXHR, QSPI_RXHR_RXTH_MSK, config->rx_thrd);
	QSPI_LEGACY_SPI_ENABLE(hperh);

	return;
}

/**
  * @brief Get QSPI indirect write access status.
  * @param hperh: Pointer to the QSPI qspi_handle_t structure.
  * @param status: qspi indirect write status.
  * @retval Status, see @ref ald_status_t.
  */
flag_status_t qspi_indwr_get_status(qspi_handle_t *hperh, qspi_indwr_status_t status)
{
	assert_param(IS_QSPI_ALL(hperh->perh));
	assert_param(IS_QSPI_INDIRECT_WRITE_STATUS(status));

	if (hperh->perh->IWTR & status)
		return SET;

	return RESET;
}

/**
  * @brief  Wait indirect wriet a flag state until time out.
  * @param  hperh: Pointer to the QSPI qspi_handle_t structure.
  * @param  flag: Flag checked,the parameter can be one of @ref qspi_indwr_status_t.
  * @param  status: Value of the flag expected,the parameter can be one of @ref flag_status_t.
  * @param  timeout: Duration of the time out.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t qspi_indwr_wait_flag(qspi_handle_t *hperh, qspi_indwr_status_t flag, flag_status_t status, uint32_t timeout)
{
	uint32_t tick;

	if (timeout == 0)
		return ERROR;

	tick = ald_get_tick();

	/* Waiting for flag */
	while ((qspi_indwr_get_status(hperh, flag)) != status) {
		if (((ald_get_tick()) - tick) > timeout)
			return TIMEOUT;
	}

	return OK;
}

/**
  * @brief  QSPI Indirect read operation wait for specified status.
  * @param  hperh: Pointer to a qspi_handle_t structure.
  * @param  flag: specifies the qspi flag to check.
  * @param  status: The new Flag status (SET or RESET).
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t qspi_indrd_wait_flag(qspi_handle_t *hperh, qspi_indrd_flag_t flag, flag_status_t status, uint32_t timeout)
{
	uint32_t tick;

	if (timeout == 0)
		return ERROR;

	tick = ald_get_tick();

	/* Waiting for flag */
	while ((qspi_indrd_get_status(hperh, flag)) != status) {
		if (((ald_get_tick()) - tick) > timeout)
			return TIMEOUT;
	}
	return OK;
}

/**
  * @brief  Clear the QSPI interrupt flag.
  * @param  hperh: Pointer to a qspi_handle_t structure.
  * @param  flag: Specifies the QSPI interrupt flag.
  *         This parameter can be one of the @ref qspi_flag_t.
  * @retval None
  */
void qspi_clear_flag_status(qspi_handle_t *hperh, qspi_flag_t flag)
{
	assert_param(IS_QSPI_ALL(hperh->perh));
	assert_param(IS_QSPI_IF(flag));

	hperh->perh->IFR = flag;
	return;
}

/**
 * @}
 */
/**
 * @}
 */
#endif /* ALD_QSPI */
/**
  * @}
  */
/**
  * @}
  */
