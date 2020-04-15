/**
  ******************************************************************************
  * @file    ald_dac.c
  * @brief   DAC module driver.
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

#include "ald_dac.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup DAC DAC
  * @brief DAC module driver
  * @{
  */
#ifdef ALD_DAC

/** @defgroup DAC_Public_Functions DAC Public Functions
  * @{
  */
/**
  * @brief  Reset the dac mode.
  * @param  hperh: Pointer to a dac_handle_t structure that contains
  *         the configuration information for the specified DAC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_dac_reset(dac_handle_t *hperh)
{
	assert_param(IS_DAC_TYPE(hperh->perh));

	hperh->perh->CON      = 0;
	hperh->perh->CH0CTRL  = 0;
	hperh->perh->CH1CTRL  = 0;
	hperh->perh->IES      = 0;
	hperh->perh->IEC      = 0xFF;
	hperh->perh->IFC      = 0xFF;
	hperh->perh->CAL      = 0;

	return OK;
}

/**
  * @brief  Initializes the DAC peripheral.
  * @param  hperh: Pointer to a dac_handle_t structure that contains
  *         the configuration information for the specified DAC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_dac_init(dac_handle_t *hperh)
{
	uint32_t tmp;

	assert_param(IS_DAC_TYPE(hperh->perh));
	assert_param(IS_DAC_CONVERT_TYPE(hperh->init.conv_mode));
	assert_param(IS_DAC_OUTPUT_TYPE(hperh->init.out_mode));
	assert_param(IS_DAC_NEG_REFRESH_TYPE(hperh->init.n_ref));
	assert_param(IS_DAC_POS_REFRESH_TYPE(hperh->init.p_ref));
	assert_param(IS_DAC_REFRESH_TYPE(hperh->init.refresh));
	assert_param(IS_DAC_PRESCALE_TYPE(hperh->init.div));
	assert_param(IS_FUNC_STATE(hperh->init.ch0_reset));
	assert_param(IS_FUNC_STATE(hperh->init.o_ctrl_pis));
	assert_param(IS_FUNC_STATE(hperh->init.sine));
	assert_param(IS_FUNC_STATE(hperh->init.diff));

	__LOCK(hperh);
	ald_dac_reset(hperh);
	DAC_CH0_DISABLE();
	DAC_CH1_DISABLE();

	MODIFY_REG(ADC0->CCR, ADC_CCR_VREFEN_MSK, 1 << ADC_CCR_VREFEN_POS);

	if (hperh->init.p_ref == DAC_POS_REF_VREEFP_BUF || hperh->init.p_ref == DAC_POS_REF_2V)
		SET_BIT(ADC0->CCR, (ADC_CCR_IREFEN_MSK | ADC_CCR_VRBUFEN_MSK | ADC_CCR_VCMBUFEN_MSK));

	MODIFY_REG(ADC0->CCR, ADC_CCR_VRNSEL_MSK, hperh->init.n_ref << ADC_CCR_VRNSEL_POS);
	MODIFY_REG(ADC0->CCR, ADC_CCR_VRPSEL_MSK, hperh->init.p_ref << ADC_CCR_VRPSEL_POSS);

	tmp = ((hperh->init.refresh << DAC_CON_RCYCLSEL_POSS) | (hperh->init.div << DAC_CON_PRES_POSS) |
	       (hperh->init.ch0_reset << DAC_CON_CH0PRESRST_POS) | ( hperh->init.o_ctrl_pis << DAC_CON_OUTENPIS_POS) |
	       (hperh->init.out_mode << DAC_CON_OUTMD_POSS) | (hperh->init.conv_mode << DAC_CON_CONVMD_POSS) |
	       (hperh->init.sine << DAC_CON_SINEMD_POS) | (hperh->init.diff << DAC_CON_DIFEN_POS));
	hperh->perh->CON = tmp;

	/* Automatic calibration */
	SET_BIT(hperh->perh->CAL, DAC_CAL_SELF_CALEN_MSK);
	for (tmp = 0; tmp < 1000; ++tmp);
	CLEAR_BIT(hperh->perh->CAL, DAC_CAL_SELF_CALEN_MSK);

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Configure dac channel.
  * @param  hperh: Pointer to a dac_handle_t structure that contains
  *         the configuration information for the specified DAC module.
  * @param  config: Pointer to a dac_channel_config_t structure that contains
  *         the configutation information for dac channel.
  * @param  ch: Specifies which dac channel to be config.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_dac_channel_config(dac_handle_t *hperh, dac_channel_config_t *config, dac_channel_t ch)
{
	uint32_t tmp;

	if ((hperh == NULL) || (config == NULL))
		return ERROR;

	assert_param(IS_DAC_TYPE(hperh->perh));
	assert_param(IS_FUNC_STATE(config->enable));
	assert_param(IS_DAC_TRIGGER_TYPE(config->trigger));
	assert_param(IS_FUNC_STATE(config->refresh_en));
	assert_param(IS_DAC_PISSEL_CH_TYPE(config->pis_ch));

	__LOCK(hperh);
	tmp = ((config->pis_ch << DAC_CH0CTRL_PISSEL_POSS) | (config->trigger << DAC_CH0CTRL_PISEN_POS) |
	       (config->refresh_en << DAC_CH0CTRL_RCYCLEN_POS) | (config->enable << DAC_CH0CTRL_EN_POS));

	switch (ch) {
	case DAC_CHANNEL_0:
		hperh->perh->CH0CTRL = tmp;
		break;

	case DAC_CHANNEL_1:
		hperh->perh->CH1CTRL = tmp;
		break;

	default:
		break;
	}

	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Set dac channel output value.
  * @param  hperh: Pointer to a dac_handle_t structure that contains
  *         the configuration information for the specified DAC module.
  * @param  ch: Specifies which dac channel to be set.
  * @param  value: The value be converted,and the valid value is low 12 bit.
  * @retval None
  */
void ald_dac_output_set(dac_handle_t *hperh, dac_channel_t ch, uint32_t value)
{
	assert_param(IS_DAC_TYPE(hperh->perh));
	assert_param(IS_DAC_CHANNEL_TYPE(ch));

	switch (ch) {
	case DAC_CHANNEL_0:
		hperh->perh->CH0DATA = value;
		break;

	case DAC_CHANNEL_1:
		hperh->perh->CH1DATA = value;
		break;

	case DAC_CHANNEL_COMB:
		hperh->perh->COMBDATA = value;
		break;

	default:
		break;
	}

	return;
}

/**
  * @brief  Checks whether the specified DAC flag is set or not.
  * @param  hperh: Pointer to a dac_handle_t structure that contains
  *               the configuration information for the specified dac.
  * @param  status: Specifies the flag to check.
  * @retval The new state.
  */
flag_status_t ald_dac_get_status(dac_handle_t *hperh, dac_status_t status)
{
	assert_param(IS_DAC_TYPE(hperh->perh));
	assert_param(IS_DAC_STATUS_TYPE(status));

	return hperh->perh->STAT & status ? SET : RESET;
}

/**
  * @brief Enable or disable the specified interrupt
  * @param hperh: Pointer to a dac_handle_t structure that contains
  *               the configuration information for the specified DAC.
  * @param it: Specifies the interrupt type to be enabled or disabled
  *        @arg @ref DAC_IT_CH0 Channel 0 conversion complete interrupt
  *        @arg @ref DAC_IT_CH1 Channel 1 conversion complete interrupt
  *        @arg @ref DAC_IT_CH0_UF Channel 0 data underflow interrupt
  *        @arg @ref DAC_IT_CH1_UF Channel 1 data underflow interrupt
  * @param state: New state of the specified interrupt.
  *        This parameter can be: ENABLE or DISABLE
  * @retval Status, see @ref ald_status_t.
  */
void ald_dac_interrupt_config(dac_handle_t *hperh, dac_it_t it, type_func_t state)
{
	assert_param(IS_DAC_TYPE(hperh->perh));
	assert_param(IS_DAC_INTERRUPT_TYPE(it));
	assert_param(IS_FUNC_STATE(state));

	if (state)
		hperh->perh->IES |= it;
	else
		hperh->perh->IEC = it;

	return;
}

/**
  * @brief  Get the status of DAC interrupt source.
  * @param  hperh: Pointer to a dac_handle_t structure that contains
  *               the configuration information for the specified DAC.
  * @param  it: Specifies the DAC interrupt source.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
it_status_t ald_dac_get_it_status(dac_handle_t *hperh, dac_it_t it)
{
	assert_param(IS_DAC_TYPE(hperh->perh));
	assert_param(IS_DAC_INTERRUPT_TYPE(it));

	return hperh->perh->IEV & it ? SET : RESET;
}

/**
  * @brief Checks whether the specified interrupt has occurred or not.
  * @param hperh: Pointer to a dac_handle_t structure that contains
  *               the configuration information for the specified DAC.
  * @param flag: Specifies the interrupt type to check.
  * @retval The new state.
  */
flag_status_t ald_dac_get_flag_status(dac_handle_t *hperh, dac_flag_t flag)
{
	assert_param(IS_DAC_TYPE(hperh->perh));
	assert_param(IS_DAC_FLAG_TYPE(flag));

	return hperh->perh->RIF & flag ? SET : RESET;
}

/**
  * @brief  Get the status of interrupt flag and interupt source.
  * @param  hperh: Pointer to a dac_handle_t structure that contains
  *               the configuration information for the specified DAC.
  * @param  flag: Specifies the DAC interrupt flag.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_dac_get_mask_flag_status(dac_handle_t *hperh, dac_flag_t flag)
{
	assert_param(IS_DAC_TYPE(hperh->perh));
	assert_param(IS_DAC_FLAG_TYPE(flag));

	return hperh->perh->IFM & flag ? SET : RESET;
}

/**
  * @brief  Clear interrupt state flag
  * @param  hperh: Pointer to a dac_handle_t structure that contains
  *               the configuration information for the specified DAC.
  * @param  flag: Specifies the interrupt type to clear
  * @retval None
  */
void ald_dac_clear_flag_status(dac_handle_t *hperh, dac_flag_t flag)
{
	assert_param(IS_DAC_TYPE(hperh->perh));
	assert_param(IS_DAC_FLAG_TYPE(flag));

	hperh->perh->IFC = flag;
	return;
}

/**
  * @brief  This function handles DAC event interrupt request.
  * @param hperh: Pointer to a dac_handle_t structure that contains
  *               the configuration information for the specified DAC.
  * @retval None
  */
void ald_dac_irq_handler(dac_handle_t *hperh)
{
	if (ald_dac_get_mask_flag_status(hperh, DAC_FLAG_CH0)) {
		ald_dac_clear_flag_status(hperh, DAC_FLAG_CH0);

		if (hperh->cbk)
			hperh->cbk(hperh, DAC_EVENT_CH0_CPLT);
	}

	if (ald_dac_get_mask_flag_status(hperh, DAC_FLAG_CH1)) {
		ald_dac_clear_flag_status(hperh, DAC_FLAG_CH1);

		if (hperh->cbk)
			hperh->cbk(hperh, DAC_EVENT_CH1_CPLT);
	}

	if (ald_dac_get_mask_flag_status(hperh, DAC_FLAG_CH0_UF)) {
		ald_dac_clear_flag_status(hperh, DAC_FLAG_CH0_UF);

		if (hperh->cbk)
			hperh->cbk(hperh, DAC_EVENT_CH0_UF);
	}

	if (ald_dac_get_mask_flag_status(hperh, DAC_FLAG_CH1_UF)) {
		ald_dac_clear_flag_status(hperh, DAC_FLAG_CH1_UF);

		if (hperh->cbk)
			hperh->cbk(hperh, DAC_EVENT_CH1_UF);
	}

	return;
}
/**
  *@}
  */
#endif /* ALD_DAC */
/**
  *@}
  */
/**
  *@}
  */
