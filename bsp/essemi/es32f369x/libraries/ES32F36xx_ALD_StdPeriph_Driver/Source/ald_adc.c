/**
  ******************************************************************************
  * @file    ald_adc.c
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Initialization functions
  *             ++ Initialization and Configuration of ADC
  *           + Operation functions
  *             ++ Start, stop, get result of conversions of normal
  *                group, using 3 possible modes: polling, interruption or DMA.
  *           + Control functions
  *             ++ Channels configuration on normal group
  *             ++ Channels configuration on insert group
  *             ++ Analog Watchdog configuration
  *           + State functions
  *             ++ ADC state machine management
  *             ++ Interrupts and flags management
  *
  * @version V1.0
  * @date    28 Jun 2019
  * @author  AE Team.
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */


#include "ald_cmu.h"
#include "ald_adc.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup ADC ADC
  * @brief ADC module driver
  * @{
  */

#ifdef ALD_ADC

/** @addtogroup ADC_Private_Functions
  * @{
  */
#ifdef ALD_DMA
static void adc_dma_normal_conv_cplt(void *arg);
static void adc_dma_error(void *arg);
#endif
/**
  * @}
  */


/** @defgroup ADC_Public_Functions ADC Public Functions
  * @{
  */

/** @defgroup ADC_Public_Functions_Group1 Initialization functions
  * @brief    Initialization and Configuration functions
  * @{
  */

/**
  * @brief  Initializes the ADC peripheral and normal group according to
  *         parameters specified in structure "adc_handle_t".
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_init(adc_handle_t *hperh)
{
	ald_status_t tmp_status = OK;

	if (hperh == NULL)
		return ERROR;

	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_DATA_ALIGN_TYPE(hperh->init.data_align));
	assert_param(IS_ADC_SCAN_MODE_TYPE(hperh->init.scan_mode));
	assert_param(IS_ADC_CLK_DIV_TYPE(hperh->init.clk_div));
	assert_param(IS_ADC_NEG_REF_VOLTAGE_TYPE(hperh->init.neg_ref));
	assert_param(IS_POS_REF_VOLTAGE_TYPE(hperh->init.pos_ref));
	assert_param(IS_ADC_CONV_RES_TYPE(hperh->init.conv_res));
	assert_param(IS_ADC_NCH_LEN_TYPE(hperh->init.nch_len));
	assert_param(IS_ADC_DISC_NBR_TYPE(hperh->init.disc_nbr));
	assert_param(IS_FUNC_STATE(hperh->init.cont_mode));
	assert_param(IS_ADC_NCHESEL_MODE_TYPE(hperh->init.nche_sel));

	if (hperh->state ==  ADC_STATE_RESET ) {
		hperh->error_code = ADC_ERROR_NONE;
		hperh->lock 	  = UNLOCK;
	}

	ADC_DISABLE(hperh);
	ald_adc_reset(hperh);
	hperh->state = ADC_STATE_BUSY_INTERNAL;
	MODIFY_REG(hperh->perh->CON1, ADC_CON1_ALIGN_MSK, hperh->init.data_align << ADC_CON1_ALIGN_POS);
	MODIFY_REG(hperh->perh->CON1, ADC_CON1_CM_MSK, hperh->init.cont_mode << ADC_CON1_CM_POS);
	MODIFY_REG(hperh->perh->CON0, ADC_CON0_RSEL_MSK, hperh->init.conv_res << ADC_CON0_RSEL_POSS);
	MODIFY_REG(hperh->perh->CON0, ADC_CON0_SCANEN_MSK, hperh->init.scan_mode << ADC_CON0_SCANEN_POS);

	/* Enable discontinuous mode only if continuous mode is enabled */
	if (hperh->init.disc_mode == ADC_NCH_DISC_EN) {
		hperh->init.scan_mode = ENABLE;
		SET_BIT(hperh->perh->CON0, ADC_CON0_NCHDCEN_MSK);
		MODIFY_REG(hperh->perh->CON0, ADC_CON0_ETRGN_MSK, hperh->init.disc_nbr << ADC_CON0_ETRGN_POSS);
	}
	else {
		CLEAR_BIT(hperh->perh->CON0, ADC_CON0_NCHDCEN_MSK);
	}

	if ((hperh->init.scan_mode == ENABLE) || (hperh->init.disc_mode == ADC_NCH_DISC_EN))
		MODIFY_REG(hperh->perh->CHSL, ADC_CHSL_NSL_MSK, hperh->init.nch_len << ADC_CHSL_NSL_POSS);

	MODIFY_REG(hperh->perh->CCR, ADC_CCR_GAINCALEN_MSK, DISABLE << ADC_CCR_GAINCALEN_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_OFFCALEN_MSK, DISABLE << ADC_CCR_OFFCALEN_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_DIFFEN_MSK, DISABLE << ADC_CCR_DIFFEN_POS);
	/* if the ADC CLK less than 1MHZ,PWRMOD should be Enable*/
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_PWRMODSEL_MSK, DISABLE << ADC_CCR_PWRMODSEL_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_VRBUFEN_MSK, ENABLE << ADC_CCR_VRBUFEN_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_VCMBUFEN_MSK, ENABLE << ADC_CCR_VCMBUFEN_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_VREFEN_MSK, ENABLE << ADC_CCR_VREFEN_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_IREFEN_MSK, ENABLE << ADC_CCR_IREFEN_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_CKDIV_MSK, hperh->init.clk_div << ADC_CCR_CKDIV_POSS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_VRNSEL_MSK, hperh->init.neg_ref << ADC_CCR_VRNSEL_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_VRPSEL_MSK, hperh->init.pos_ref << ADC_CCR_VRPSEL_POSS);
	MODIFY_REG(hperh->perh->CON1, ADC_CON1_NCHESEL_MSK, hperh->init.nche_sel << ADC_CON1_NCHESEL_POS);

	if (tmp_status == OK) {
		hperh->error_code = ADC_ERROR_NONE;
		hperh->state 	 |= ADC_STATE_READY;
		hperh->state 	 &= ~(ADC_STATE_ERROR | ADC_STATE_NM_BUSY
		                   | ADC_STATE_IST_BUSY | ADC_STATE_BUSY_INTERNAL);
	}

	ald_adc_interrupt_config(hperh, ADC_IT_OVR, ENABLE);
	return tmp_status;
}

/**
  * @brief  Deinitialize the ADC peripheral registers to their default reset
  *         values.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_reset(adc_handle_t *hperh)
{
	if (hperh == NULL)
		return ERROR;

	assert_param(IS_ADC_TYPE(hperh->perh));

	ADC_DISABLE(hperh);

	ald_adc_clear_flag_status(hperh, ADC_FLAG_AWD);
	ald_adc_clear_flag_status(hperh, ADC_FLAG_NCH);
	ald_adc_clear_flag_status(hperh, ADC_FLAG_ICH);
	ald_adc_clear_flag_status(hperh, ADC_FLAG_OVR);
	ald_adc_clear_flag_status(hperh, ADC_FLAG_NCHS);
	ald_adc_clear_flag_status(hperh, ADC_FLAG_ICHS);

	WRITE_REG(hperh->perh->CON0, 0x0);
	WRITE_REG(hperh->perh->CON1, 0x0);
	WRITE_REG(hperh->perh->CCR, 0x0);
	WRITE_REG(hperh->perh->WDTH, 0xFFF);
	WRITE_REG(hperh->perh->WDTL, 0x0);
	WRITE_REG(hperh->perh->ICHOFF1, 0x0);
	WRITE_REG(hperh->perh->ICHOFF2, 0x0);
	WRITE_REG(hperh->perh->ICHOFF3, 0x0);
	WRITE_REG(hperh->perh->ICHOFF4, 0x0);
	WRITE_REG(hperh->perh->ICHS, 0x0);
	WRITE_REG(hperh->perh->NCHS1, 0x0);
	WRITE_REG(hperh->perh->NCHS2, 0x0);
	WRITE_REG(hperh->perh->NCHS3, 0x0);
	WRITE_REG(hperh->perh->NCHS4, 0x0);
	WRITE_REG(hperh->perh->SMPT1, 0x0);
	WRITE_REG(hperh->perh->SMPT2, 0x0);
	WRITE_REG(hperh->perh->CHSL, 0x0);

	hperh->state      = ADC_STATE_RESET;
	hperh->error_code = ADC_ERROR_NONE;
	return OK;
}
/**
  * @}
  */

/** @defgroup ADC_Public_Functions_Group2 IO operation functions
 *  @brief    Input and Output operation functions
 *  @{
 */

/**
  * @brief  Enables ADC, starts conversion of normal group.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_normal_start(adc_handle_t *hperh)
{
	if (hperh == NULL)
		return ERROR;

	assert_param(IS_ADC_TYPE(hperh->perh));

	__LOCK(hperh);
	ADC_ENABLE(hperh);
	hperh->state &= ~(ADC_STATE_READY | ADC_STATE_NM_EOC);
	hperh->state |= ADC_STATE_NM_BUSY;
	__UNLOCK(hperh);
	ald_adc_clear_flag_status(hperh, ADC_FLAG_NCH);

	SET_BIT(hperh->perh->CON1, ADC_CON1_NCHTRG_MSK);

	return OK;
}

/**
  * @brief  Stop ADC conversion of normal group (and insert channels in
  *         case of auto_injection mode), disable ADC peripheral.
  * @note:  ADC peripheral disable is forcing stop of potential
  *         conversion on insert group. If insert group is under use, it
  *         should be preliminarily stopped using ald_adc_insert_stop function.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_normal_stop(adc_handle_t *hperh)
{
	assert_param(IS_ADC_TYPE(hperh->perh));

	__LOCK(hperh);

	ADC_DISABLE(hperh);
	hperh->state &= ~(ADC_STATE_NM_BUSY | ADC_STATE_NM_EOC);
	hperh->state |=  ADC_STATE_READY;

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Wait for normal group conversion to be completed.
  * @note   This function cannot be used in a particular setup: ADC configured  in DMA mode.
  *         In this case, DMA resets the flag EOC and polling cannot be performed on each conversion.
  * @note   When use this function,you should be pay attention to the hperh->init.reocs_mode,
  *         if it is ADC_REOCS_MODE_ALL, it means the function will wait all normal rank conversion  finished.
  *         if it is ADC_REOCS_MODE_ONE, it means the funcion will wait every normal rank conversion finished.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  timeout: Timeout value in millisecond.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_normal_poll_for_conversion(adc_handle_t *hperh, uint32_t timeout)
{
	uint32_t tickstart = 0;

	assert_param(IS_ADC_TYPE(hperh->perh));

	tickstart = ald_get_tick();
	while (!(READ_BIT(hperh->perh->STAT, ADC_STAT_NCHE_MSK))) {
		if (timeout != ALD_MAX_DELAY ) {
			if ((timeout == 0) || ((ald_get_tick() - tickstart) > timeout)) {
				hperh->state |= ADC_STATE_TIMEOUT;
				__UNLOCK(hperh);
				return TIMEOUT;
			}
		}
	}

	ald_adc_clear_flag_status(hperh, ADC_FLAG_NCHS);
	ald_adc_clear_flag_status(hperh, ADC_FLAG_NCH);

	hperh->state |= ADC_STATE_NM_EOC;

	if ((hperh->init.cont_mode == DISABLE) && (hperh->init.scan_mode == DISABLE)) {
		hperh->state &= ~ADC_STATE_NM_BUSY;

		if ((hperh->state & ADC_STATE_IST_BUSY) == 0)
			hperh->state |= ADC_STATE_READY;
	}
	return OK;
}

/**
  * @brief  Poll for conversion event.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  event_type: the ADC event type.
  *          This parameter can be one of the following values:
  *            ADC_awd_event: ADC Analog watchdog event.
  * @param  timeout: Timeout value in millisecond.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_poll_for_event(adc_handle_t *hperh, adc_event_type_t event_type, uint32_t timeout)
{
	uint32_t tickstart = 0;

	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_EVENT_TYPE(event_type));

	tickstart = ald_get_tick();

	while (ald_adc_get_flag_status(hperh, (adc_flag_t)event_type) == RESET) {
		if (timeout != ALD_MAX_DELAY ) {
			if ((timeout == 0) || ((ald_get_tick() - tickstart) > timeout)) {
				hperh->state |= ADC_STATE_TIMEOUT;
				__UNLOCK(hperh);
				return TIMEOUT;
			}
		}
	}

	hperh->state |= ADC_STATE_AWD;
	return OK;
}

/**
  * @brief  Enables ADC, starts conversion of normal group with interruption.
  *         Interruptions enabled in this function:
  *          - REOC (end of conversion of normal group)
  *         Each of these interruptions has its dedicated callback function.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_normal_start_by_it(adc_handle_t *hperh)
{
	assert_param(IS_ADC_TYPE(hperh->perh));

	__LOCK(hperh);
	ADC_ENABLE(hperh);
	hperh->state 	 &= ~(ADC_STATE_READY | ADC_STATE_NM_EOC);
	hperh->state 	 |= ADC_STATE_NM_BUSY;
	hperh->error_code = ADC_ERROR_NONE;

	if (READ_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK)) {
		hperh->state &= ~(ADC_STATE_IST_EOC);
		hperh->state |= ADC_STATE_IST_BUSY;
	}

	__UNLOCK(hperh);
	ald_adc_clear_flag_status(hperh, ADC_FLAG_NCH);
	ald_adc_interrupt_config(hperh, ADC_IT_NCH, ENABLE);

	SET_BIT(hperh->perh->CON1, ADC_CON1_NCHTRG_MSK);

	return OK;
}

/**
  * @brief  Stop ADC conversion of normal group (and insert group in
  *         case of auto_injection mode), disable interrution of
  *         end-of-conversion, disable ADC peripheral.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_normal_stop_by_it(adc_handle_t *hperh)
{
	assert_param(IS_ADC_TYPE(hperh->perh));

	__LOCK(hperh);
	ADC_DISABLE(hperh);
	ald_adc_interrupt_config(hperh, ADC_IT_NCH, DISABLE);
	hperh->state |= ADC_STATE_READY;
	hperh->state &= ~(ADC_STATE_NM_BUSY | ADC_STATE_IST_BUSY);

	__UNLOCK(hperh);
	return OK;
}

#ifdef ALD_DMA
/**
  * @brief  Enables ADC, starts conversion of normal group and transfers result
  *         through DMA.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  buf: The destination Buffer address.
  * @param  size: The length of data to be transferred from ADC peripheral to memory.
  * @param  channel: The DMA channel
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_start_by_dma(adc_handle_t *hperh, uint16_t *buf, uint16_t size, uint8_t channel)
{
	if ((hperh == NULL) || (buf == NULL) || (size == 0) || (channel > 5))
		return ERROR;

	assert_param(IS_ADC_TYPE(hperh->perh));

	__LOCK(hperh);
	ADC_ENABLE(hperh);
	hperh->state &= ~(ADC_STATE_READY | ADC_STATE_NM_EOC);
	hperh->state |= ADC_STATE_NM_BUSY;

	if (READ_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK)) {
		hperh->state &= ~(ADC_STATE_IST_EOC);
		hperh->state |= ADC_STATE_IST_BUSY;
	}

	if ((hperh->state & ADC_STATE_IST_BUSY) != 0) {
		hperh->state      &= ~(ADC_STATE_ERROR);
		hperh->error_code &= ~(ADC_ERROR_OVR | ADC_ERROR_DMA);
	}
	else {
		hperh->state     &= ~(ADC_STATE_ERROR);
		hperh->error_code = ADC_ERROR_NONE;
	}
	__UNLOCK(hperh);

	if (hperh->hdma.perh == NULL)
		hperh->hdma.perh = DMA0;

	hperh->hdma.cplt_cbk = adc_dma_normal_conv_cplt;
	hperh->hdma.cplt_arg = hperh;
	hperh->hdma.err_cbk  = adc_dma_error;
	hperh->hdma.err_arg  = hperh;

	ald_dma_config_struct(&hperh->hdma.config);
	hperh->hdma.config.src        = (void *)&hperh->perh->NCHDR;
	hperh->hdma.config.dst        = (void *)buf;
	hperh->hdma.config.size       = size;
	hperh->hdma.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdma.config.src_inc    = DMA_DATA_INC_NONE;
	hperh->hdma.config.dst_inc    = DMA_DATA_INC_HALFWORD;
	hperh->hdma.config.msel       = DMA_MSEL_ADC0;
	hperh->hdma.config.msigsel    = DMA_MSIGSEL_ADC;
	hperh->hdma.config.burst      = ENABLE;
	hperh->hdma.config.channel    = channel;
	ald_dma_config_basic(&hperh->hdma);

	MODIFY_REG(hperh->perh->CON1, ADC_CON1_DMA_MSK, 1 << ADC_CON1_DMA_POS);
	SET_BIT(hperh->perh->CON1, ADC_CON1_NCHTRG_MSK);

	return OK;
}

/**
  * @brief  Stop ADC conversion of normal group (and insert group in
  *         case of auto_insert mode), disable ADC DMA transfer, disable
  *         ADC peripheral.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t adc_stop_dma(adc_handle_t *hperh)
{
	assert_param(IS_ADC_TYPE(hperh->perh));
	__LOCK(hperh);

	ADC_DISABLE(hperh);
	ald_pis_destroy(&hperh->hpis);
	hperh->state &= ~(ADC_STATE_NM_BUSY | ADC_STATE_IST_BUSY);
	hperh->state |= ADC_STATE_READY;

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  DMA transfer complete callback.
  * @param  arg: argument of the call back.
  * @retval None
  */
static void adc_dma_timer_trigger_cplt(void *arg)
{
	adc_timer_config_t *hperh = (adc_timer_config_t *)arg;

	ADC_DISABLE(&hperh->lh_adc);
	ald_timer_base_stop(&hperh->lh_timer);

	__UNLOCK(hperh);
	if (hperh->lh_adc.adc_reg_cplt_cbk != NULL)
		hperh->lh_adc.adc_reg_cplt_cbk(&hperh->lh_adc);

}


/**
  * @brief  Config Timer trigger adc function
  * @param  config: Pointer to a adc_timer_config_t structure that
  *         contains the configuration information for the specified function.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_timer_trigger_adc_by_dma(adc_timer_config_t *config)
{
	__LOCK(config);

	config->lh_pis.perh               = PIS;
	config->lh_pis.init.producer_clk  = PIS_CLK_PCLK1;
	config->lh_pis.init.producer_edge = PIS_EDGE_NONE;
	config->lh_pis.init.consumer_clk  = PIS_CLK_PCLK2;

	#if defined(ES32F36xx)
	if (config->p_timer == AD16C4T0)
		config->lh_pis.init.producer_src  = PIS_TIMER0_UPDATA;
	else if (config->p_timer == AD16C4T1)
		config->lh_pis.init.producer_src  = PIS_TIMER1_UPDATA;
	else if (config->p_timer == GP32C4T0)
		config->lh_pis.init.producer_src  = PIS_TIMER2_UPDATA;
	else if (config->p_timer == GP32C4T1)
		config->lh_pis.init.producer_src  = PIS_TIMER3_UPDATA;
	else
		return ERROR;
	#elif defined(ES32F39xx) || defined(ES32F336x)
	if (config->p_timer == GP16C4T0)
		config->lh_pis.init.producer_src  = PIS_TIMER0_UPDATA;
	else if (config->p_timer == GP16C4T1)
		config->lh_pis.init.producer_src  = PIS_TIMER1_UPDATA;
	else if (config->p_timer == GP32C4T0)
		config->lh_pis.init.producer_src  = PIS_TIMER2_UPDATA;
	else if (config->p_timer == GP32C4T1)
		config->lh_pis.init.producer_src  = PIS_TIMER3_UPDATA;
	else
		return ERROR;
	#endif

	if (config->p_adc == ADC0)
		config->lh_pis.init.consumer_trig = PIS_CH6_ADC0_REGULAT;
	else
		return ERROR;

	ald_pis_create(&config->lh_pis);

	/* Initialize TIMER0 */
	config->lh_timer.perh           = config->p_timer;
	config->lh_timer.init.prescaler = 0;
	config->lh_timer.init.mode      = TIMER_CNT_MODE_UP;
	config->lh_timer.init.period    = ((ald_cmu_get_pclk1_clock() / 1000000) * config->time);
	config->lh_timer.init.clk_div   = TIMER_CLOCK_DIV1;
	config->lh_timer.init.re_cnt    = 0;
	ald_timer_base_init(&config->lh_timer);

	config->lh_adc.perh               = config->p_adc;
	config->lh_adc.init.data_align    = ADC_DATAALIGN_RIGHT;
	config->lh_adc.init.scan_mode     = DISABLE;
	config->lh_adc.init.cont_mode     = DISABLE;
	config->lh_adc.init.nch_len       = ADC_NCH_LEN_1;
	config->lh_adc.init.disc_mode     = ADC_ALL_DISABLE;
	config->lh_adc.init.disc_nbr      = ADC_DISC_NBR_1;
	config->lh_adc.init.conv_res      = ADC_CONV_RES_12;
	config->lh_adc.init.clk_div       = ADC_CKDIV_16;
	config->lh_adc.init.nche_sel      = ADC_NCHESEL_MODE_ONE;
	config->lh_adc.init.neg_ref       = config->n_ref;
	config->lh_adc.init.pos_ref       = config->p_ref;
	config->lh_adc.adc_reg_cplt_cbk   = config->adc_cplt_cbk;
	config->lh_adc.adc_inj_cplt_cbk   = NULL;
	config->lh_adc.adc_out_of_win_cbk = NULL;
	config->lh_adc.adc_error_cbk      = NULL;
	config->lh_adc.adc_ovr_cbk        = NULL;
	ald_adc_init(&config->lh_adc);

	MODIFY_REG(config->lh_adc.perh->CON1, ADC_CON1_DMA_MSK, 1 << ADC_CON1_DMA_POS);

	config->lh_adc.perh->CON1 |= 0x10000000;
	config->lnm_config.channel       = config->adc_ch;
	config->lnm_config.rank          = ADC_NCH_RANK_1;
	config->lnm_config.samp_time     = ADC_SAMPLETIME_1;
 	ald_adc_normal_channel_config(&config->lh_adc, &config->lnm_config);

	config->lh_dma.cplt_cbk = adc_dma_timer_trigger_cplt;
	config->lh_dma.cplt_arg = config;
	config->lh_dma.err_cbk  = adc_dma_error;
	config->lh_dma.err_arg  = &config->lh_adc;

	ald_dma_config_struct(&config->lh_dma.config);
	config->lh_dma.perh              = DMA0;
	config->lh_dma.config.src        = (void *)&config->lh_adc.perh->NCHDR;
	config->lh_dma.config.dst        = (void *)config->buf;
	config->lh_dma.config.size       = config->size;
	config->lh_dma.config.data_width = DMA_DATA_SIZE_HALFWORD;
	config->lh_dma.config.src_inc    = DMA_DATA_INC_NONE;
	config->lh_dma.config.dst_inc    = DMA_DATA_INC_HALFWORD;
	config->lh_dma.config.msel       = config->p_adc == ADC0 ? DMA_MSEL_ADC0 : DMA_MSEL_ADC1;
	config->lh_dma.config.msigsel    = DMA_MSIGSEL_ADC;
	config->lh_dma.config.burst      = ENABLE;
	config->lh_dma.config.channel    = config->dma_ch;
	ald_dma_config_basic(&config->lh_dma);

	ADC_ENABLE(&config->lh_adc);
	ald_timer_base_start(&config->lh_timer);

	return OK;
}
#endif

/**
  * @brief  Get ADC normal group conversion result.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval ADC group normal conversion data
  */
uint32_t ald_adc_normal_get_value(adc_handle_t *hperh)
{
	assert_param(IS_ADC_TYPE(hperh->perh));

	hperh->state &= ~ADC_STATE_NM_EOC;
	return hperh->perh->NCHDR;
}

/**
  * @brief  Enables ADC, starts conversion of insert group.
  *         Interruptions enabled in this function: None.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_insert_start(adc_handle_t *hperh)
{
	assert_param(IS_ADC_TYPE(hperh->perh));

	__LOCK(hperh);
	ADC_ENABLE(hperh);
	hperh->state &= ~(ADC_STATE_READY | ADC_STATE_IST_EOC);
	hperh->state |= ADC_STATE_IST_BUSY;

	if ((hperh->state & ADC_STATE_NM_BUSY) == 0)
		hperh->error_code = ADC_ERROR_NONE;

	__UNLOCK(hperh);
	ald_adc_clear_flag_status(hperh, ADC_FLAG_ICH);

	if (!(READ_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK)))
		SET_BIT(hperh->perh->CON1, ADC_CON1_ICHTRG_MSK);

	return OK;
}

/**
  * @brief  Stop conversion of insert channels. Disable ADC peripheral if
  *         no normal conversion is on going.
  * @note   If ADC must be disabled and if conversion is on going on
  *         normal group, function ald_adc_normal_stop must be used to stop both
  *         insert and normal groups, and disable the ADC.
  * @note   If insert group mode auto-injection is enabled,
  *         function ald_adc_normal_stop must be used.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_insert_stop(adc_handle_t *hperh)
{
	assert_param(IS_ADC_TYPE(hperh->perh));

	__LOCK(hperh);

	if (((hperh->state & ADC_STATE_NM_BUSY) == 0)
				&& (!(READ_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK)))) {
		ADC_DISABLE(hperh);
		hperh->state &= ~(ADC_STATE_NM_BUSY | ADC_STATE_IST_BUSY | ADC_STATE_IST_EOC);
		hperh->state |= ADC_STATE_READY;
	}
	else {
		hperh->state |= ADC_STATE_ERROR;
		__UNLOCK(hperh);
		return ERROR;
	}

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Wait for insert group conversion to be completed.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  timeout: Timeout value in millisecond.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_insert_poll_for_conversion(adc_handle_t *hperh, uint32_t timeout)
{
	uint32_t tickstart;

	assert_param(IS_ADC_TYPE(hperh->perh));

	tickstart = ald_get_tick();

	while (!(READ_BIT(hperh->perh->STAT, ADC_STAT_ICHE_MSK))) {
		if (timeout != ALD_MAX_DELAY) {
			if ((timeout == 0) || ((ald_get_tick() - tickstart) > timeout)) {
				hperh->state |= ADC_STATE_TIMEOUT;
				__UNLOCK(hperh);
				return TIMEOUT;
			}
		}
	}

	ald_adc_clear_flag_status(hperh, ADC_FLAG_ICHS);
	ald_adc_clear_flag_status(hperh, ADC_FLAG_ICH);
	ald_adc_clear_flag_status(hperh, ADC_FLAG_NCH);

	hperh->state |= ADC_STATE_IST_EOC;

	hperh->state &= ~(ADC_STATE_IST_BUSY);
	if ((hperh->state & ADC_STATE_NM_BUSY) == 0)
		hperh->state |= ADC_STATE_READY;

	hperh->state &= ~(ADC_STATE_TIMEOUT);
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Enables ADC, starts conversion of insert group with interruption.
  *          - JEOC (end of conversion of insert group)
  *         Each of these interruptions has its dedicated callback function.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t..
  */
ald_status_t ald_adc_insert_start_by_it(adc_handle_t *hperh)
{
	assert_param(IS_ADC_TYPE(hperh->perh));

	__LOCK(hperh);
	ADC_ENABLE(hperh);
	hperh->state &= ~(ADC_STATE_READY | ADC_STATE_IST_EOC);
	hperh->state |= ADC_STATE_IST_BUSY;

	if ((hperh->state & ADC_STATE_NM_BUSY) == 0)
		hperh->error_code = ADC_ERROR_NONE;

	__UNLOCK(hperh);
	ald_adc_clear_flag_status(hperh, ADC_FLAG_ICH);
	ald_adc_interrupt_config(hperh, ADC_IT_ICH, ENABLE);

	if (!(READ_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK)))
		SET_BIT(hperh->perh->CON1, ADC_CON1_ICHTRG_MSK);

	return OK;
}

/**
  * @brief  Stop conversion of insert channels, disable interruption of
  *         end-of-conversion. Disable ADC peripheral if no normal conversion
  *         is on going.
  * @note   If ADC must be disabled and if conversion is on going on
  *         normal group, function ald_adc_normal_stop must be used to stop both
  *         insert and normal groups, and disable the ADC.
  * @note   If insert group mode auto-injection is enabled,
  *         function ald_adc_normal_stop must be used.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval None
  */
ald_status_t ald_adc_insert_stop_by_it(adc_handle_t *hperh)
{
	assert_param(IS_ADC_TYPE(hperh->perh));

	__LOCK(hperh);

	if (((hperh->state & ADC_STATE_NM_BUSY) == 0)
		&& (!(READ_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK)))) {
		ADC_DISABLE(hperh);
		ald_adc_interrupt_config(hperh, ADC_IT_ICH, DISABLE);
		hperh->state &= ~(ADC_STATE_NM_BUSY | ADC_STATE_IST_BUSY);
		hperh->state |= ADC_STATE_READY;
	}
	else {
		ald_adc_interrupt_config(hperh, ADC_IT_ICH, DISABLE);
		hperh->state |= ADC_STATE_ERROR;
		__UNLOCK(hperh);
		return ERROR;
	}

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Get ADC insert group conversion result.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  ih_rank: the converted ADC insert rank.
  *          This parameter can be one of the following values:
  *            @arg ADC_INJ_RANK_1: insert Channel1 selected
  *            @arg ADC_INJ_RANK_2: insert Channel2 selected
  *            @arg ADC_INJ_RANK_3: insert Channel3 selected
  *            @arg ADC_INJ_RANK_4: insert Channel4 selected
  * @retval ADC group insert conversion data
  */
uint32_t ald_adc_insert_get_value(adc_handle_t *hperh, adc_ich_rank_t ih_rank)
{
	uint32_t tmp;

	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_ICH_RANK_TYPE(ih_rank));

	switch (ih_rank) {
	case ADC_ICH_RANK_1:
		tmp = hperh->perh->ICHDR1;
		break;
	case ADC_ICH_RANK_2:
		tmp = hperh->perh->ICHDR2;
		break;
	case ADC_ICH_RANK_3:
		tmp = hperh->perh->ICHDR3;
		break;
	case ADC_ICH_RANK_4:
		tmp = hperh->perh->ICHDR4;
		break;
	default:
		break;
	}

	return tmp;
}

/**
  * @brief  Handles ADC interrupt request
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval None
  */
void ald_adc_irq_handler(adc_handle_t *hperh)
{
	assert_param(IS_ADC_TYPE(hperh->perh));

	if (ald_adc_get_it_status(hperh, ADC_IT_NCH) && ald_adc_get_flag_status(hperh, ADC_FLAG_NCH)) {
		if ((hperh->state & ADC_STATE_ERROR) == 0)
			hperh->state |= ADC_STATE_NM_EOC;

		if (hperh->init.cont_mode == DISABLE) {
			ald_adc_interrupt_config(hperh, ADC_IT_NCH, DISABLE);
			hperh->state &= ~(ADC_STATE_NM_BUSY);

			if ((hperh->state & ADC_STATE_IST_BUSY) == 0)
				hperh->state |= ADC_STATE_READY;
		}

		if (hperh->adc_reg_cplt_cbk != NULL)
			hperh->adc_reg_cplt_cbk(hperh);

		ald_adc_clear_flag_status(hperh, ADC_FLAG_NCHS);
		ald_adc_clear_flag_status(hperh, ADC_FLAG_NCH);
	}

	if (ald_adc_get_it_status(hperh, ADC_IT_ICH) && ald_adc_get_flag_status(hperh, ADC_FLAG_ICH)) {
		if ((hperh->state & ADC_STATE_ERROR) == 0)
			hperh->state |= ADC_STATE_IST_EOC;

		if ((!(READ_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK))) && (hperh->init.cont_mode == DISABLE)) {
			ald_adc_interrupt_config(hperh, ADC_IT_ICH, DISABLE);
			hperh->state &= ~(ADC_STATE_IST_BUSY);

			if ((hperh->state & ADC_STATE_NM_BUSY) == 0)
				hperh->state |= ADC_STATE_READY;
		}
		if (hperh->adc_inj_cplt_cbk != NULL)
			hperh->adc_inj_cplt_cbk(hperh);

		ald_adc_clear_flag_status(hperh, ADC_FLAG_ICHS);
		ald_adc_clear_flag_status(hperh, ADC_FLAG_ICH);
	}

	if (ald_adc_get_it_status(hperh, ADC_IT_AWD) && ald_adc_get_flag_status(hperh, ADC_FLAG_AWD)) {
		hperh->state |= ADC_STATE_AWD;

		if (hperh->adc_out_of_win_cbk != NULL)
			hperh->adc_out_of_win_cbk(hperh);

		ald_adc_clear_flag_status(hperh, ADC_FLAG_AWD);
	}

	if (ald_adc_get_it_status(hperh, ADC_IT_OVR) && ald_adc_get_flag_status(hperh, ADC_FLAG_OVR)) {
		ald_adc_clear_flag_status(hperh, ADC_FLAG_OVR);
		hperh->error_code |= ADC_ERROR_OVR;
		hperh->state      |= ADC_STATE_ERROR;

		if (hperh->adc_ovr_cbk != NULL)
			hperh->adc_ovr_cbk(hperh);
	}
}

/**
  * @}
  */

/** @defgroup ADC_Public_Functions_Group3 Peripheral Control functions
 *  @brief    Peripheral Control functions
 *  @{
 */

/**
  * @brief  Configures the the selected channel to be linked to the normal
  *         group.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  config: Structure of ADC channel for normal group.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_normal_channel_config(adc_handle_t *hperh, adc_nch_conf_t *config)
{
	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_CHANNELS_TYPE(config->channel));
	assert_param(IS_ADC_NCH_RANK_TYPE(config->rank));
	assert_param(IS_ADC_SAMPLING_TIMES_TYPE(config->samp_time));

	__LOCK(hperh);

	if (config->rank <= ADC_NCH_RANK_4 ) {
		hperh->perh->NCHS1 &= ~(0x1f <<  ((config->rank - 1) << 3));
		hperh->perh->NCHS1 |= (config->channel << ((config->rank - 1) << 3));
	}
	else if (config->rank <= ADC_NCH_RANK_8) {
		hperh->perh->NCHS2 &= ~(0x1f <<  ((config->rank - 5) << 3));
		hperh->perh->NCHS2 |= (config->channel << ((config->rank - 5) << 3));
	}
	else if (config->rank <= ADC_NCH_RANK_12) {
		hperh->perh->NCHS3 &= ~(0x1f <<  ((config->rank - 9) << 3));
		hperh->perh->NCHS3 |= (config->channel << ((config->rank - 9) << 3));
	}
	else {
		hperh->perh->NCHS4 &= ~(0x1f <<  ((config->rank - 13) << 3));
		hperh->perh->NCHS4 |= (config->channel << ((config->rank - 13) << 3));
	}

	if (config->channel < 8) {
		hperh->perh->SMPT1 &=  ~(0x0f << (config->channel << 2));
		hperh->perh->SMPT1 |= config->samp_time << (config->channel << 2);
	}
	else if (config->channel < 16) {
		hperh->perh->SMPT2 &=  ~(0x0f << ((config->channel - 8) << 2));
		hperh->perh->SMPT2 |= config->samp_time << ((config->channel - 8) << 2);
	}
	else {
		hperh->perh->SMPT3 &=  ~(0x0f << ((config->channel - 16) << 2));
		hperh->perh->SMPT3 |= config->samp_time << ((config->channel - 16) << 2);
	}

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Configures the the selected channel to be linked to the insert
  *         group.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  config: Structure of ADC channel for insert group.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_insert_channel_config(adc_handle_t *hperh, adc_ich_conf_t *config)
{
	uint8_t tmp1, tmp2;
	ald_status_t tmp_status = OK;

	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_CHANNELS_TYPE(config->channel));
	assert_param(IS_ADC_ICH_RANK_TYPE(config->rank));
	assert_param(IS_ADC_SAMPLING_TIMES_TYPE(config->samp_time));
	assert_param(IS_ADC_IST_OFFSET_TYPE(config->offset));
	assert_param(IS_ADC_NBR_OF_IST_TYPE(config->ich_len));

	__LOCK(hperh);

	if (hperh->init.scan_mode == DISABLE) {
		switch (config->rank) {
		case ADC_ICH_RANK_1:
			MODIFY_REG(hperh->perh->ICHS, ADC_ICHS_IS1_MSK, config->channel << ADC_ICHS_IS1_POSS);
			break;
		case ADC_ICH_RANK_2:
			MODIFY_REG(hperh->perh->ICHS, ADC_ICHS_IS2_MSK, config->channel << ADC_ICHS_IS2_POSS);
			break;
		case ADC_ICH_RANK_3:
			MODIFY_REG(hperh->perh->ICHS, ADC_ICHS_IS3_MSK, config->channel << ADC_ICHS_IS3_POSS);
			break;
		case ADC_ICH_RANK_4:
			MODIFY_REG(hperh->perh->ICHS, ADC_ICHS_IS4_MSK, config->channel << ADC_ICHS_IS4_POSS);
			break;
		default:
			hperh->state      |= ADC_STATE_ERROR;
			hperh->error_code |= ADC_ERROR_INTERNAL;
			tmp_status         = ERROR;
			break;
		}
	}
	else {
		MODIFY_REG(hperh->perh->CHSL, ADC_CHSL_ISL_MSK, config->ich_len << ADC_CHSL_ISL_POSS);
		tmp1 = config->rank ;
		tmp2 = config->ich_len;

		if (tmp1 <= tmp2) {
			hperh->perh->ICHS &= ~(0x1f << ((tmp1 - 1) << 3));
			hperh->perh->ICHS |= config->channel
			                                  << ((tmp1 - 1) << 3);
		}
		else {
			hperh->perh->ICHS &= ~(0x1f << ((tmp1 - 1) << 3));
			hperh->perh->ICHS |= config->channel
			                                  << ((tmp1 - 1) << 3);
		}
	}

	if (config->auto_inj == ENABLE)
		SET_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK);

	if (hperh->init.disc_mode == ADC_ICH_DISC_EN) {
		if (config->auto_inj == DISABLE) {
			MODIFY_REG(hperh->perh->CHSL, ADC_CHSL_ISL_MSK, config->ich_len << ADC_CHSL_ISL_POSS);
			SET_BIT(hperh->perh->CON0, ADC_CON0_ICHDCEN_MSK);
		}
		else {
			hperh->state      |= ADC_STATE_ERROR;
			hperh->error_code |= ADC_ERROR_INTERNAL;
			tmp_status         = ERROR;
		}
	}

	if (config->channel < 8) {
		hperh->perh->SMPT1 &=  ~(0x03 << (config->channel << 2));
		hperh->perh->SMPT1 |= config->samp_time << (config->channel << 2);
	}
	else if (config->channel < 16) {
		hperh->perh->SMPT2 &=  ~(0x03 << ((config->channel - 8) << 2));
		hperh->perh->SMPT2 |= config->samp_time << ((config->channel - 8) << 2);
	}
	else {
		hperh->perh->SMPT3 &=  ~(0x03 << ((config->channel - 16) << 2));
		hperh->perh->SMPT3 |= config->samp_time << ((config->channel - 16) << 2);
	}

	switch (config->rank) {
	case ADC_ICH_RANK_1:
		hperh->perh->ICHOFF1 = config->offset;
		break;
	case ADC_ICH_RANK_2:
		hperh->perh->ICHOFF2 = config->offset;
		break;
	case ADC_ICH_RANK_3:
		hperh->perh->ICHOFF3 = config->offset;
		break;
	case ADC_ICH_RANK_4:
		hperh->perh->ICHOFF4 = config->offset;
		break;
	default:
		break;
	}

	__UNLOCK(hperh);
	return tmp_status;
}

/**
  * @brief  Configures the analog watchdog.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  config: Structure of ADC analog watchdog configuration
  * @retval ALD status
  */
ald_status_t ald_adc_analog_wdg_config(adc_handle_t *hperh, adc_analog_wdg_conf_t *config)
{

	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_ANALOG_WTD_MODE_TYPE(config->watchdog_mode));
	assert_param(IS_FUNC_STATE(config->it_mode));
	assert_param(IS_HTR_TYPE(config->high_threshold));
	assert_param(IS_LTR_TYPE(config->low_threshold));

	__LOCK(hperh);

	if ((config->watchdog_mode == ADC_ANAWTD_SING_NM)
		|| (config->watchdog_mode == ADC_ANAWTD_SING_IST)
	        || (config->watchdog_mode == ADC_ANAWTD_SING_NMIST))
		assert_param(IS_ADC_CHANNELS_TYPE(config->channel));

	if (config->it_mode == DISABLE)
		ald_adc_interrupt_config(hperh, ADC_IT_AWD, DISABLE);
	else
		ald_adc_interrupt_config(hperh, ADC_IT_AWD, ENABLE);

	CLEAR_BIT(hperh->perh->CON0, ADC_CON0_ICHWDTEN_MSK);
	CLEAR_BIT(hperh->perh->CON0, ADC_CON0_NCHWDEN_MSK);
	CLEAR_BIT(hperh->perh->CON0, ADC_CON0_AWDSGL_MSK);
	hperh->perh->CON0 |= config->watchdog_mode;

	if (READ_BIT(hperh->perh->CON0, ADC_CON0_AWDSGL_MSK))
		MODIFY_REG(hperh->perh->CON0, ADC_CON0_AWDCH_MSK, config->channel << ADC_CON0_AWDCH_POSS);

	WRITE_REG(hperh->perh->WDTL, config->low_threshold);
	WRITE_REG(hperh->perh->WDTH, config->high_threshold);

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  hperh: Pointer to a adc_handle_t structure.
  * @param  it: Specifies the ADC interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref adc_it_t.
  * @param  state: New status
  *           - ENABLE
  *           - DISABLE
  * @retval None
  */
void ald_adc_interrupt_config(adc_handle_t *hperh, adc_it_t it, type_func_t state)
{
	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_IT_TYPE(it));
	assert_param(IS_FUNC_STATE(state));

	if (state == ENABLE)
		SET_BIT(hperh->perh->CON0, it);
	else
		CLEAR_BIT(hperh->perh->CON0, it);

	return;
}

/**
  * @brief  Checks whether the specified ADC interrupt has occurred or not.
  * @param  hperh: Pointer to a adc_handle_t structure.
  * @param  it: Specifies the ADC interrupt source to check.
  *         This parameter can be one of the @ref adc_it_t.
  * @retval Status
  *           - SET
  *           - RESET
  */
it_status_t ald_adc_get_it_status(adc_handle_t *hperh, adc_it_t it)
{
	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_IT_TYPE(it));

	if (READ_BIT(hperh->perh->CON0, it))
		return SET;

	return RESET;
}

/** @brief  Check whether the specified ADC flag is set or not.
  * @param  hperh: Pointer to a adc_handle_t structure.
  * @param  flag: specifies the flag to check.
  *         This parameter can be one of the @ref adc_flag_t.
  * @retval Status
  *           - SET
  *           - RESET
  */
flag_status_t ald_adc_get_flag_status(adc_handle_t *hperh, adc_flag_t flag)
{
	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_FLAGS_TYPE(flag));

	if (READ_BIT(hperh->perh->STAT, flag))
		return SET;

	return RESET;
}

/** @brief  Clear the specified ADC pending flags.
  * @param  hperh: Pointer to a adc_handle_t structure.
  * @param  flag: specifies the flag to check.
  *         This parameter can be one of the @ref adc_flag_t.
  * @retval None
  */
void ald_adc_clear_flag_status(adc_handle_t *hperh, adc_flag_t flag)
{
	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_FLAGS_TYPE(flag));

	WRITE_REG(hperh->perh->CLR, flag);
	return;
}
/**
  * @}
  */

/** @defgroup ADC_Public_Functions_Group4 Peripheral State functions
 *  @brief    Peripheral State functions
 *  @{
 */

/**
  * @brief  return the ADC state
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval state
  */
uint32_t ald_adc_get_state(adc_handle_t *hperh)
{
	return hperh->state;
}

/**
  * @brief  Return the ADC error code
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval ADC Error Code
  */
uint32_t ald_adc_get_error(adc_handle_t *hperh)
{
	return hperh->error_code;
}

/**
  *@}
  */

/**
  *@}
  */

/** @defgroup ADC_Private_Functions ADC Private Functions
  * @{
  */

#ifdef ALD_DMA
/**
  * @brief  DMA transfer complete callback.
  * @param  arg: argument of the call back.
  * @retval None
  */
static void adc_dma_normal_conv_cplt(void *arg)
{
	adc_handle_t *hperh = (adc_handle_t *)arg;

	if (hperh->adc_reg_cplt_cbk != NULL)
		hperh->adc_reg_cplt_cbk(hperh);

}

/**
  * @brief  DMA error callback
  * @param  arg: argument of the call back.
  * @retval None
  */
static void adc_dma_error(void *arg)
{
	adc_handle_t *hperh = (adc_handle_t *)arg;
	hperh->state       |= ADC_STATE_ERROR;
	hperh->error_code  |= ADC_ERROR_DMA;

	if (hperh->adc_error_cbk != NULL)
		hperh->adc_error_cbk(hperh);
}
#endif
/**
  *@}
  */

#endif /* ALD_ADC */

/**
  *@}
  */

/**
  *@}
  */
