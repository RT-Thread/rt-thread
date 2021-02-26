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
  * @date    15 Dec 2017
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
	if (hperh == NULL)
		return ERROR;

	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_DATA_ALIGN_TYPE(hperh->init.align));
	assert_param(IS_FUNC_STATE(hperh->init.scan));
	assert_param(IS_ADC_NCH_NR_TYPE(hperh->init.nch_nr));
	assert_param(IS_ADC_DISC_MODE_TYPE(hperh->init.disc));
	assert_param(IS_ADC_DISC_NR_TYPE(hperh->init.disc_nr));
	assert_param(IS_ADC_CONV_BIT_TYPE(hperh->init.data_bit));
	assert_param(IS_ADC_CLK_DIV_TYPE(hperh->init.div));
	assert_param(IS_ADC_NCHESEL_MODE_TYPE(hperh->init.nche_sel));
	assert_param(IS_ADC_NEG_REF_VOLTAGE_TYPE(hperh->init.n_ref));
	assert_param(IS_POS_REF_VOLTAGE_TYPE(hperh->init.p_ref));

	if (hperh->state ==  ADC_STATE_RESET ) {
		hperh->error_code = ADC_ERROR_NONE;
		hperh->lock 	  = UNLOCK;
	}

	if ((hperh->init.p_ref == ADC_POS_REF_VDD) && (hperh->init.n_ref == ADC_NEG_REF_VSS)) {
		ADC_ENABLE(hperh);

		MODIFY_REG(hperh->perh->CCR, ADC_CCR_VRNSEL_MSK, hperh->init.n_ref << ADC_CCR_VRNSEL_POS);
		MODIFY_REG(hperh->perh->CCR, ADC_CCR_VRPSEL_MSK, hperh->init.p_ref << ADC_CCR_VRPSEL_POSS);
		MODIFY_REG(hperh->perh->CCR, ADC_CCR_VCMBUFEN_MSK, 1 << ADC_CCR_VCMBUFEN_POS);
		MODIFY_REG(hperh->perh->CCR, ADC_CCR_IREFEN_MSK, 1 << ADC_CCR_IREFEN_POS);
		MODIFY_REG(hperh->perh->CCR, ADC_CCR_VREFEN_MSK, 1 << ADC_CCR_VREFEN_POS);
		MODIFY_REG(hperh->perh->CCR, ADC_CCR_CKDIV_MSK, 6 << ADC_CCR_CKDIV_POSS);
		MODIFY_REG(hperh->perh->CON1, ADC_CON1_ALIGN_MSK, ADC_DATAALIGN_RIGHT << ADC_CON1_ALIGN_POS);
		MODIFY_REG(hperh->perh->CON0, ADC_CON0_RSEL_MSK, ADC_CONV_BIT_12 << ADC_CON0_RSEL_POSS);
		MODIFY_REG(hperh->perh->CON1, ADC_CON1_CM_MSK, DISABLE << ADC_CON1_CM_POS);
		MODIFY_REG(hperh->perh->NCHS1, ADC_NCHS1_NS1_MSK, ADC_CHANNEL_18 << ADC_NCHS1_NS1_POSS);
		hperh->perh->SMPT2 = 0x30;

		/* Start adc normal convert */
		SET_BIT(hperh->perh->CON1, ADC_CON1_NCHTRG_MSK);
		/* Wait convert finish */
		while (!READ_BIT(hperh->perh->STAT, ADC_STAT_NCHE_MSK));
		hperh->vdd_value = (hperh->perh->NCHDR & 0xfff);
		/* Get calibration VDD value */
		hperh->vdd_value = 2000 * 4096 / hperh->vdd_value;
	}

	ADC_DISABLE(hperh);
	ald_adc_reset(hperh);
	hperh->state = ADC_STATE_BUSY;
	MODIFY_REG(hperh->perh->CON1, ADC_CON1_ALIGN_MSK, hperh->init.align << ADC_CON1_ALIGN_POS);
	MODIFY_REG(hperh->perh->CON0, ADC_CON0_RSEL_MSK, hperh->init.data_bit << ADC_CON0_RSEL_POSS);

	/* Enable discontinuous mode only if continuous mode is disable */
	if (hperh->init.disc == ADC_NCH_DISC_EN) {
		hperh->init.scan = ENABLE;
		SET_BIT(hperh->perh->CON0, ADC_CON0_NCHDCEN_MSK);
		MODIFY_REG(hperh->perh->CON0, ADC_CON0_ETRGN_MSK, hperh->init.disc_nr << ADC_CON0_ETRGN_POSS);
	}
	else if (hperh->init.disc == ADC_ICH_DISC_EN) {
		hperh->init.scan = ENABLE;
		SET_BIT(hperh->perh->CON0, ADC_CON0_ICHDCEN_MSK);
		MODIFY_REG(hperh->perh->CON0, ADC_CON0_ETRGN_MSK, hperh->init.disc_nr << ADC_CON0_ETRGN_POSS);
	}
	else {
		CLEAR_BIT(hperh->perh->CON0, ADC_CON0_NCHDCEN_MSK);
		CLEAR_BIT(hperh->perh->CON0, ADC_CON0_ICHDCEN_MSK);
	}

	if ((hperh->init.scan == ENABLE) || (hperh->init.disc == ADC_NCH_DISC_EN))
		MODIFY_REG(hperh->perh->CHSL, ADC_CHSL_NSL_MSK, hperh->init.nch_nr << ADC_CHSL_NSL_POSS);

	MODIFY_REG(hperh->perh->CON1, ADC_CON1_CM_MSK, hperh->init.scan << ADC_CON1_CM_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_GAINCALEN_MSK, DISABLE << ADC_CCR_GAINCALEN_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_OFFCALEN_MSK, DISABLE << ADC_CCR_OFFCALEN_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_DIFFEN_MSK, DISABLE << ADC_CCR_DIFFEN_POS);
	/* if the ADC clock less than 1MHz,PWRMOD should be disable*/
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_PWRMODSEL_MSK, DISABLE << ADC_CCR_PWRMODSEL_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_VRBUFEN_MSK, ENABLE << ADC_CCR_VRBUFEN_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_VCMBUFEN_MSK, ENABLE << ADC_CCR_VCMBUFEN_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_VREFEN_MSK, ENABLE << ADC_CCR_VREFEN_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_IREFEN_MSK, ENABLE << ADC_CCR_IREFEN_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_CKDIV_MSK, hperh->init.div << ADC_CCR_CKDIV_POSS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_VRNSEL_MSK, hperh->init.n_ref << ADC_CCR_VRNSEL_POS);
	MODIFY_REG(hperh->perh->CCR, ADC_CCR_VRPSEL_MSK, hperh->init.p_ref << ADC_CCR_VRPSEL_POSS);
	MODIFY_REG(hperh->perh->CON1, ADC_CON1_NCHESEL_MSK, hperh->init.nche_sel << ADC_CON1_NCHESEL_POS);
	ald_adc_interrupt_config(hperh, ADC_IT_OVR, ENABLE);
	ADC_ENABLE(hperh);

	hperh->init.cont  = DISABLE;
	hperh->error_code = ADC_ERROR_NONE;
	hperh->state 	  = ADC_STATE_READY;
	return OK;
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
	assert_param(IS_ADC_TYPE(hperh->perh));

	ADC_DISABLE(hperh);
	WRITE_REG(hperh->perh->CLR, 0x30F);
	WRITE_REG(hperh->perh->CON0, 0x0);
	WRITE_REG(hperh->perh->CON1, 0x0);
	WRITE_REG(hperh->perh->CCR, 0x0);
	WRITE_REG(hperh->perh->WDTH, 0xFFF);
	WRITE_REG(hperh->perh->WDTL, 0x0);
	WRITE_REG(hperh->perh->ICHOFF[0], 0x0);
	WRITE_REG(hperh->perh->ICHOFF[1], 0x0);
	WRITE_REG(hperh->perh->ICHOFF[2], 0x0);
	WRITE_REG(hperh->perh->ICHOFF[3], 0x0);
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
	assert_param(IS_ADC_TYPE(hperh->perh));

	ADC_ENABLE(hperh);
	WRITE_REG(hperh->perh->CLR, ADC_FLAG_NCH | ADC_FLAG_NCHS);
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

	ADC_DISABLE(hperh);
	hperh->state = ADC_STATE_READY;
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
	uint32_t _tick;

	assert_param(IS_ADC_TYPE(hperh->perh));

	_tick = ald_get_tick();
	while (!(READ_BIT(hperh->perh->STAT, ADC_STAT_NCHE_MSK))) {
		if (timeout != ALD_MAX_DELAY ) {
			if ((timeout == 0) || ((ald_get_tick() - _tick) > timeout)) {
				hperh->state = ADC_STATE_TIMEOUT;
				return TIMEOUT;
			}
		}
	}

	WRITE_REG(hperh->perh->CLR, ADC_FLAG_NCHS | ADC_FLAG_NCH);
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
	uint32_t _tick;

	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_EVENT_TYPE(event_type));

	_tick = ald_get_tick();
	while (ald_adc_get_flag_status(hperh, (adc_flag_t)event_type) == RESET) {
		if (timeout != ALD_MAX_DELAY ) {
			if ((timeout == 0) || ((ald_get_tick() - _tick) > timeout)) {
				hperh->state = ADC_STATE_TIMEOUT;
				return TIMEOUT;
			}
		}
	}

	
	CLEAR_BIT(hperh->state, ADC_STATE_BUSY_WDG);
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

	SET_BIT(hperh->state, ADC_STATE_BUSY_N);
	ADC_ENABLE(hperh);
	WRITE_REG(hperh->perh->CLR, ADC_FLAG_NCH);
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

	ADC_DISABLE(hperh);
	ald_adc_interrupt_config(hperh, ADC_IT_NCH, DISABLE);
	CLEAR_BIT(hperh->state, ADC_STATE_BUSY_N);

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
	if ((buf == NULL) || (size == 0))
		return ERROR;

	assert_param(IS_ADC_TYPE(hperh->perh));

	SET_BIT(hperh->state, ADC_STATE_BUSY_N);

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
	hperh->hdma.config.channel    = channel;
	ald_dma_config_basic(&hperh->hdma);

	ADC_ENABLE(hperh);
	SET_BIT(hperh->perh->CON1, ADC_CON1_NCHTRG_MSK);
	return OK;
}

/**
  * @brief  Stop ADC conversion of normal group (and insert group in
  *         case of auto_insert mode), disable ADC DMA transfer, disable
  *         ADC peripheral.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  channel: The DMA channel.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_stop_by_dma(adc_handle_t *hperh, uint8_t channel)
{
	assert_param(IS_ADC_TYPE(hperh->perh));

	ADC_DISABLE(hperh);
	ald_dma_channel_config(hperh->hdma.perh, channel, DISABLE);
	CLEAR_BIT(hperh->state, ADC_STATE_BUSY_N);
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

	ald_timer_base_stop(&hperh->h_timer);
	ADC_DISABLE(&hperh->h_adc);
	ald_dma_channel_config(hperh->h_dma.perh, hperh->dma_ch, DISABLE);
	CLEAR_BIT(hperh->h_adc.state, ADC_STATE_BUSY_N);

	if (hperh->h_adc.normal_cplt_cbk)
		hperh->h_adc.normal_cplt_cbk(&hperh->h_adc);

	return;
}

/**
  * @brief  Config Timer trigger adc function
  * @param  config: Pointer to a adc_timer_config_t structure that
  *         contains the configuration information for the specified function.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_timer_trigger_adc_by_dma(adc_timer_config_t *config)
{
	SET_BIT(config->h_adc.state, ADC_STATE_BUSY_N);

	config->h_pis.perh               = PIS;
	config->h_pis.init.producer_clk  = PIS_CLK_PCLK1;
	config->h_pis.init.producer_edge = PIS_EDGE_NONE;
	config->h_pis.init.consumer_clk  = PIS_CLK_PCLK2;

	#if defined (ES32F065x)
	if (config->p_timer == AD16C4T0)
		config->h_pis.init.producer_src  = PIS_TIMER0_UPDATA;
	#elif defined(ES32F033x) || defined (ES32F093x)
	if (config->p_timer == GP16C4T0)
		config->h_pis.init.producer_src  = PIS_TIMER0_UPDATA;
	#endif
	else if (config->p_timer == BS16T0)
		config->h_pis.init.producer_src  = PIS_TIMER1_UPDATA;
	else if (config->p_timer == GP16C2T0)
		config->h_pis.init.producer_src  = PIS_TIMER2_UPDATA;
	else if (config->p_timer == GP16C2T1)
		config->h_pis.init.producer_src  = PIS_TIMER3_UPDATA;
	else
		return ERROR;

	if (config->p_adc == ADC0)
		config->h_pis.init.consumer_trig = PIS_CH6_ADC0_NORMAL;
	else
		return ERROR;

	ald_pis_create(&config->h_pis);

	/* Initialize TIMER0 */
	config->h_timer.perh           = config->p_timer;
	config->h_timer.init.prescaler = 0;
	config->h_timer.init.mode      = TIMER_CNT_MODE_UP;
	config->h_timer.init.period    = ((ald_cmu_get_pclk1_clock() / 1000000) * config->time);
	config->h_timer.init.clk_div   = TIMER_CLOCK_DIV1;
	config->h_timer.init.re_cnt    = 0;
	ald_timer_base_init(&config->h_timer);

	config->h_adc.perh            = config->p_adc;
	config->h_adc.init.align      = ADC_DATAALIGN_RIGHT;
	config->h_adc.init.scan       = DISABLE;
	config->h_adc.init.cont       = DISABLE;
	config->h_adc.init.nch_nr     = ADC_NCH_NR_1;
	config->h_adc.init.disc       = ADC_ALL_DISABLE;
	config->h_adc.init.disc_nr    = ADC_DISC_NR_1;
	config->h_adc.init.data_bit   = ADC_CONV_BIT_12;
	config->h_adc.init.div        = ADC_CKDIV_128;
	config->h_adc.init.nche_sel   = ADC_NCHESEL_MODE_ONE;
	config->h_adc.init.n_ref      = config->n_ref;
	config->h_adc.init.p_ref      = config->p_ref;
	config->h_adc.normal_cplt_cbk = config->cplt_cbk;
	config->h_adc.insert_cplt_cbk = NULL;
	config->h_adc.wdg_cbk         = NULL;
	config->h_adc.error_cbk       = NULL;
	config->h_adc.ovr_cbk         = NULL;
	ald_adc_init(&config->h_adc);
	ADC_ENABLE(&config->h_adc);

	config->config.ch   = config->adc_ch;
	config->config.idx  = ADC_NCH_IDX_1;
	config->config.samp = ADC_SAMPLETIME_4;
 	ald_adc_normal_channel_config(&config->h_adc, &config->config);

	config->h_dma.cplt_cbk = adc_dma_timer_trigger_cplt;
	config->h_dma.cplt_arg = config;
	config->h_dma.err_cbk  = adc_dma_error;
	config->h_dma.err_arg  = &config->h_adc;

	ald_dma_config_struct(&config->h_dma.config);
	config->h_dma.perh              = DMA0;
	config->h_dma.config.src        = (void *)&config->h_adc.perh->NCHDR;
	config->h_dma.config.dst        = (void *)config->buf;
	config->h_dma.config.size       = config->size;
	config->h_dma.config.data_width = DMA_DATA_SIZE_HALFWORD;
	config->h_dma.config.src_inc    = DMA_DATA_INC_NONE;
	config->h_dma.config.dst_inc    = DMA_DATA_INC_HALFWORD;
	config->h_dma.config.msel       = DMA_MSEL_ADC0;
	config->h_dma.config.msigsel    = DMA_MSIGSEL_ADC;
	config->h_dma.config.channel    = config->dma_ch;
	ald_dma_config_basic(&config->h_dma);
	ald_timer_base_start(&config->h_timer);

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

	return hperh->perh->NCHDR;
}

/**
  * @brief  The pos reference is VDD and neg reference is VSS,
  *         get adc normal group result and convert voltage value.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval ADC group normal voltage value,the unit is mV.
  */
uint32_t ald_adc_get_vdd_value(adc_handle_t *hperh)
{
	uint32_t value, _tmp[5];

	if ((hperh->init.p_ref != ADC_POS_REF_VDD) || (hperh->init.n_ref != ADC_NEG_REF_VSS))
		return 0;

	_tmp[0] = hperh->perh->CCR;
	_tmp[1] = hperh->perh->CON0;
	_tmp[2] = hperh->perh->CON1;
	_tmp[3] = hperh->perh->NCHS1;
	_tmp[4] = hperh->perh->SMPT2;

	hperh->perh->CON0  = 0x0;
	hperh->perh->CON1  = 0x0;
	hperh->perh->NCHS1 = 0x0;

	ADC_ENABLE(hperh);
	hperh->perh->CCR = 0x8B06;
	MODIFY_REG(hperh->perh->CON0, ADC_CON1_ALIGN_MSK, ADC_DATAALIGN_RIGHT << ADC_CON1_ALIGN_POS);
	MODIFY_REG(hperh->perh->CON0, ADC_CON0_RSEL_MSK, ADC_CONV_BIT_12 << ADC_CON0_RSEL_POSS);
	MODIFY_REG(hperh->perh->CON1, ADC_CON1_CM_MSK, DISABLE << ADC_CON1_CM_POS);
	MODIFY_REG(hperh->perh->NCHS1, ADC_NCHS1_NS1_MSK, ADC_CHANNEL_18 << ADC_NCHS1_NS1_POSS);
	hperh->perh->SMPT2 = 0x30;
	SET_BIT(hperh->perh->CON1, ADC_CON1_NCHTRG_MSK);

	while (!READ_BIT(hperh->perh->STAT, ADC_STAT_NCHE_MSK));
	WRITE_REG(hperh->perh->CLR, ADC_FLAG_NCH | ADC_FLAG_NCHS);
	value = (hperh->perh->NCHDR & 0xfff);
	value = value == 0 ? 1 : value;
	value = (2000 << 12) / value;
	hperh->vdd_value = value;

	hperh->perh->CCR   = _tmp[0];
	hperh->perh->CON0  = _tmp[1];
	hperh->perh->CON1  = _tmp[2];
	hperh->perh->NCHS1 = _tmp[3];
        hperh->perh->SMPT2 = _tmp[4];
	ADC_DISABLE(hperh);

	return value;
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

	ADC_ENABLE(hperh);
	WRITE_REG(hperh->perh->CLR, ADC_FLAG_ICH);

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

	ADC_DISABLE(hperh);
	hperh->state = ADC_STATE_READY;
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
	uint32_t _tick;

	assert_param(IS_ADC_TYPE(hperh->perh));

	_tick = ald_get_tick();

	while (!(READ_BIT(hperh->perh->STAT, ADC_STAT_ICHE_MSK))) {
		if (timeout != ALD_MAX_DELAY) {
			if ((timeout == 0) || ((ald_get_tick() - _tick) > timeout)) {
				hperh->state = ADC_STATE_TIMEOUT;
				return TIMEOUT;
			}
		}
	}

	WRITE_REG(hperh->perh->CLR, ADC_FLAG_ICHS | ADC_FLAG_ICH);
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

	SET_BIT(hperh->state, ADC_STATE_BUSY_I);
	ADC_ENABLE(hperh);
	WRITE_REG(hperh->perh->CLR, ADC_FLAG_ICHS | ADC_FLAG_ICH);
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

	CLEAR_BIT(hperh->state, ADC_STATE_BUSY_I);
	ADC_DISABLE(hperh);
	ald_adc_interrupt_config(hperh, ADC_IT_ICH, DISABLE);
	return OK;
}

/**
  * @brief  Get ADC insert group conversion result.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  idx: Index of the insert channel.
  * @retval ADC group insert conversion data
  */
uint32_t ald_adc_insert_get_value(adc_handle_t *hperh, adc_ich_idx_t idx)
{
	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_ICH_IDX_TYPE(idx));

	return hperh->perh->ICHDR[idx - 1];
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
		WRITE_REG(hperh->perh->CLR, ADC_FLAG_NCH | ADC_FLAG_NCHS);
		CLEAR_BIT(hperh->state, ADC_STATE_BUSY_N);

		if (hperh->normal_cplt_cbk)
			hperh->normal_cplt_cbk(hperh);
	}

	if (ald_adc_get_it_status(hperh, ADC_IT_ICH) && ald_adc_get_flag_status(hperh, ADC_FLAG_ICH)) {
		WRITE_REG(hperh->perh->CLR, ADC_FLAG_ICH | ADC_FLAG_ICHS);
		CLEAR_BIT(hperh->state, ADC_STATE_BUSY_I);

		if (hperh->insert_cplt_cbk)
			hperh->insert_cplt_cbk(hperh);
	}

	if (ald_adc_get_it_status(hperh, ADC_IT_AWD) && ald_adc_get_flag_status(hperh, ADC_FLAG_AWD)) {
		CLEAR_BIT(hperh->state, ADC_STATE_BUSY_WDG);
		WRITE_REG(hperh->perh->CLR, ADC_FLAG_AWD);

		if (hperh->wdg_cbk)
			hperh->wdg_cbk(hperh);
	}

	if (ald_adc_get_it_status(hperh, ADC_IT_OVR) && ald_adc_get_flag_status(hperh, ADC_FLAG_OVR)) {
		WRITE_REG(hperh->perh->CLR, ADC_FLAG_OVR);
		hperh->error_code |= ADC_ERROR_OVR;
		hperh->state      |= ADC_STATE_ERROR;

		if (hperh->ovr_cbk)
			hperh->ovr_cbk(hperh);
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
	assert_param(IS_ADC_CHANNELS_TYPE(config->ch));
	assert_param(IS_ADC_NCH_IDX_TYPE(config->idx));
	assert_param(IS_ADC_SAMPLING_TIMES_TYPE(config->samp));

	if (config->idx <= ADC_NCH_IDX_4 ) {
		hperh->perh->NCHS1 &= ~(0x1f << (uint32_t)((config->idx - 1) << 3));
		hperh->perh->NCHS1 |= (config->ch << (uint32_t)((config->idx - 1) << 3));
	}
	else if (config->idx <= ADC_NCH_IDX_8) {
		hperh->perh->NCHS2 &= ~(0x1f << (uint32_t)((config->idx - 5) << 3));
		hperh->perh->NCHS2 |= (config->ch << (uint32_t)((config->idx - 5) << 3));
	}
	else if (config->idx <= ADC_NCH_IDX_12) {
		hperh->perh->NCHS3 &= ~(0x1f << (uint32_t)((config->idx - 9) << 3));
		hperh->perh->NCHS3 |= (config->ch << (uint32_t)((config->idx - 9) << 3));
	}
	else {
		hperh->perh->NCHS4 &= ~(0x1f << (uint32_t)((config->idx - 13) << 3));
		hperh->perh->NCHS4 |= (config->ch << (uint32_t)((config->idx - 13) << 3));
	}

	if (config->ch <= 15) {
		hperh->perh->SMPT1 &=  ~(0x03 << (uint32_t)(config->ch << 1));
		hperh->perh->SMPT1 |= config->samp << (uint32_t)(config->ch << 1);
	}
	else {
		hperh->perh->SMPT2 &=  ~(0x03 << (uint32_t)((config->ch - 16) << 1));
		hperh->perh->SMPT2 |= config->samp << (uint32_t)((config->ch - 16) << 1);
	}

	CLEAR_BIT(hperh->perh->CON0, ADC_CON0_SCANEN_MSK);
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
	ald_status_t status = OK;

	assert_param(IS_ADC_TYPE(hperh->perh));
	assert_param(IS_ADC_CHANNELS_TYPE(config->ch));
	assert_param(IS_ADC_ICH_IDX_TYPE(config->idx));
	assert_param(IS_ADC_SAMPLING_TIMES_TYPE(config->samp));
	assert_param(IS_ADC_IST_OFFSET_TYPE(config->offset));
	assert_param(IS_ADC_ICH_NR_TYPE(config->nr));
	assert_param(IS_FUNC_STATE(config->auto_m));

	MODIFY_REG(hperh->perh->CHSL, ADC_CHSL_ISL_MSK, config->nr << ADC_CHSL_ISL_POSS);
	hperh->perh->ICHS &= ~(0x1f << (uint32_t)((config->idx - 1) << 3));
	hperh->perh->ICHS |= config->ch << (uint32_t)((config->idx - 1) << 3);

	if (config->nr > 0)
		SET_BIT(hperh->perh->CON0, ADC_CON0_SCANEN_MSK);
	else
		CLEAR_BIT(hperh->perh->CON0, ADC_CON0_SCANEN_MSK);

	if (config->auto_m == ENABLE)
		SET_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK);
	else
		CLEAR_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK);

	if (hperh->init.disc == ADC_ICH_DISC_EN) {
		if (config->auto_m == DISABLE) {
			SET_BIT(hperh->perh->CON0, ADC_CON0_ICHDCEN_MSK);
		}
		else {
			hperh->state      |= ADC_STATE_ERROR;
			hperh->error_code |= ADC_ERROR_INTERNAL;
			status             = ERROR;
		}
	}

	if (config->ch <= 15) {
		hperh->perh->SMPT1 &=  ~(0x03U << ((uint32_t)config->ch << 1));
		hperh->perh->SMPT1 |= config->samp << ((uint32_t)config->ch << 1);
	}
	else {
		hperh->perh->SMPT2 &=  ~(0x03U << (((uint32_t)config->ch - 16) << 1));
		hperh->perh->SMPT2 |= config->samp << (((uint32_t)config->ch - 16) << 1);
	}

	hperh->perh->ICHOFF[config->idx] = config->offset;
	return status;
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
	assert_param(IS_ADC_ANALOG_WTD_MODE_TYPE(config->mode));
	assert_param(IS_FUNC_STATE(config->interrupt));
	assert_param(IS_HTR_TYPE(config->high_thrd));
	assert_param(IS_LTR_TYPE(config->low_thrd));

	if ((config->mode == ADC_ANAWTD_SING_NM)
		|| (config->mode == ADC_ANAWTD_SING_IST)
	        || (config->mode == ADC_ANAWTD_SING_NMIST))
		assert_param(IS_ADC_CHANNELS_TYPE(config->ch));

	if (config->interrupt == DISABLE)
		ald_adc_interrupt_config(hperh, ADC_IT_AWD, DISABLE);
	else
		ald_adc_interrupt_config(hperh, ADC_IT_AWD, ENABLE);

	CLEAR_BIT(hperh->perh->CON0, ADC_CON0_ICHWDTEN_MSK);
	CLEAR_BIT(hperh->perh->CON0, ADC_CON0_NCHWDEN_MSK);
	CLEAR_BIT(hperh->perh->CON0, ADC_CON0_AWDSGL_MSK);
	hperh->perh->CON0 |= config->mode;

	if (READ_BIT(hperh->perh->CON0, ADC_CON0_AWDSGL_MSK))
		MODIFY_REG(hperh->perh->CON0, ADC_CON0_AWDCH_MSK, config->ch << ADC_CON0_AWDCH_POSS);

	WRITE_REG(hperh->perh->WDTL, config->low_thrd);
	WRITE_REG(hperh->perh->WDTH, config->high_thrd);
	SET_BIT(hperh->state, ADC_STATE_BUSY_WDG);

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

	if (hperh->normal_cplt_cbk)
		hperh->normal_cplt_cbk(hperh);

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

	if (hperh->error_cbk)
		hperh->error_cbk(hperh);
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
