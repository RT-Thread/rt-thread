/**
  *********************************************************************************
  *
  * @file    ald_acmp.c
  * @brief   ACMP module driver.
  *
  * @version V1.0
  * @date    26 Jun 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          26 Jun 2019     AE Team         The first version
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

/** @defgroup ACMP ACMP
  * @brief ACMP module driver
  * @{
  */
#ifdef ALD_ACMP

/** @defgroup ACMP_Public_Functions ACMP Public Functions
  * @{
  */

/** @defgroup ACMP_Public_Functions_Group1 Initialization functions
  * @brief Initialization and Configuration functions
  * @{
  */

/**
  * @brief  Initializes the ACMP mode according to the specified parameters in
  *         the acmp_init_t and create the associated handle.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_acmp_init(acmp_handle_t *hperh)
{
	uint32_t tmp = 0;

	assert_param(IS_ACMP_TYPE(hperh->perh));
	assert_param(IS_ACMP_MODE_TYPE(hperh->init.mode));
	assert_param(IS_ACMP_WARM_UP_TIME_TYPE(hperh->init.warm_time));
	assert_param(IS_ACMP_HYSTSEL_TYPE(hperh->init.hystsel));
	assert_param(IS_ACMP_POS_INPUT_TYPE(hperh->init.p_port));
	assert_param(IS_ACMP_NEG_INPUT_TYPE(hperh->init.n_port));
	assert_param(IS_ACMP_INACTVAL_TYPE(hperh->init.inactval));
	assert_param(IS_FUNC_STATE(hperh->init.out_inv));
	assert_param(IS_ACMP_EDGE_TYPE(hperh->init.edge));
	assert_param(hperh->init.vdd_level < 64);

	__LOCK(hperh);
	tmp = ((hperh->init.mode << ACMP_CON_MODSEL_POSS) | (hperh->init.warm_time << ACMP_CON_WARMUPT_POSS) |
		(hperh->init.inactval << ACMP_CON_INACTV_POS) | (hperh->init.hystsel << ACMP_CON_HYSTSEL_POSS));

	hperh->perh->CON = tmp;
	
	tmp = 0;

	tmp |= ((hperh->init.p_port << ACMP_INPUTSEL_PSEL_POSS) | (hperh->init.n_port << ACMP_INPUTSEL_NSEL_POSS) |
		(hperh->init.vdd_level << ACMP_INPUTSEL_VDDLVL_POSS));
	hperh->perh->INPUTSEL = tmp;

	if (hperh->init.out_inv)
		SET_BIT(hperh->perh->CON, ACMP_CON_OUTINV_MSK);
	else
		CLEAR_BIT(hperh->perh->CON, ACMP_CON_OUTINV_MSK);

	switch (hperh->init.edge) {
	case ACMP_EDGE_NONE:
		CLEAR_BIT(hperh->perh->CON, ACMP_CON_FALLEN_MSK);
		CLEAR_BIT(hperh->perh->CON, ACMP_CON_RISEEN_MSK);
		break;

	case ACMP_EDGE_FALL:
		SET_BIT(hperh->perh->CON, ACMP_CON_FALLEN_MSK);
		CLEAR_BIT(hperh->perh->CON, ACMP_CON_RISEEN_MSK);
		break;

	case ACMP_EDGE_RISE:
		CLEAR_BIT(hperh->perh->CON, ACMP_CON_FALLEN_MSK);
		SET_BIT(hperh->perh->CON, ACMP_CON_RISEEN_MSK);
		break;

	case ACMP_EDGE_ALL:
		SET_BIT(hperh->perh->CON, ACMP_CON_FALLEN_MSK);
		SET_BIT(hperh->perh->CON, ACMP_CON_RISEEN_MSK);
		break;

	default:
		break;
	}

	SET_BIT(hperh->perh->CON, ACMP_CON_EN_MSK);

	tmp = 0;
	while (READ_BIT(hperh->perh->STAT, ACMP_STAT_ACT_MSK) == 0) {
		if (tmp++ >= 600000) {
			__UNLOCK(hperh);
			return ERROR;
		}
	}

	__UNLOCK(hperh);
	return OK;
}
/**
  * @}
  */

/** @defgroup ACMP_Public_Functions_Group2 Interrupt operation functions
  * @brief ACMP Interrupt operation functions
  * @{
  */

/**
  * @brief  Enables or disables the specified ACMP interrupts.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  it: Specifies the ACMP interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref acmp_it_t.
  * @param  state: New status
  *           - ENABLE
  *           - DISABLE
  * @retval None
  */
void ald_acmp_interrupt_config(acmp_handle_t *hperh, acmp_it_t it, type_func_t state)
{
	assert_param(IS_ACMP_TYPE(hperh->perh));
	assert_param(IS_ACMP_IT_TYPE(it));
	assert_param(IS_FUNC_STATE(state));

	if (state)
		hperh->perh->IES = it;
	else
		hperh->perh->IEC = it;

	return;
}

/**
  * @brief  Checks whether the specified ACMP interrupt has set or not.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  it: Specifies the ACMP interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref acmp_it_t.
  * @retval it_status_t
  *           - SET
  *           - RESET
  */
it_status_t ald_acmp_get_it_status(acmp_handle_t *hperh, acmp_it_t it)
{
	assert_param(IS_ACMP_TYPE(hperh->perh));
	assert_param(IS_ACMP_IT_TYPE(it));

	if (hperh->perh->IEV & it)
		return SET;

	return RESET;
}

/**
  * @brief  Checks whether the specified ACMP interrupt has occurred or not.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  flag: Specifies the ACMP interrupt source to check.
  *         This parameter can be one of the @ref acmp_flag_t.
  * @retval flag_status_t
  *           - SET
  *           - RESET
  */
flag_status_t ald_acmp_get_flag_status(acmp_handle_t *hperh, acmp_flag_t flag)
{
	assert_param(IS_ACMP_TYPE(hperh->perh));
	assert_param(IS_ACMP_FLAG_TYPE(flag));

	if (hperh->perh->RIF & flag)
		return SET;

	return RESET;
}

/**
  * @brief  Get the status of interrupt flag and interupt source.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *               the configuration information for the specified ACMP.
  * @param  flag: Specifies the ACMP interrupt flag.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_acmp_get_mask_flag_status(acmp_handle_t *hperh, acmp_flag_t flag)
{
	assert_param(IS_ACMP_TYPE(hperh->perh));
	assert_param(IS_ACMP_FLAG_TYPE(flag));

	if (hperh->perh->IFM & flag)
		return SET;

	return RESET;
}

/** @brief  Clear the specified ACMP it flags.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  flag: specifies the it flag.
  *         This parameter can be one of the @ref acmp_flag_t.
  * @retval None
  */
void ald_acmp_clear_flag_status(acmp_handle_t *hperh, acmp_flag_t flag)
{
	assert_param(IS_ACMP_TYPE(hperh->perh));
	assert_param(IS_ACMP_FLAG_TYPE(flag));

	hperh->perh->IFC = flag;
	return;
}
/**
  * @}
  */
/** @defgroup ACMP_Public_Functions_Group3 Output value functions
  * @brief ACMP Output value functions
  * @{
  */
/**
  * @brief  This function handles ACMP interrupt request.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @retval None
  */
void ald_acmp_irq_handler(acmp_handle_t *hperh)
{
	if ((ald_acmp_get_mask_flag_status(hperh, ACMP_FLAG_WARMUP)) == SET) {
		ald_acmp_clear_flag_status(hperh, ACMP_FLAG_WARMUP);

		if (hperh->acmp_warmup_cplt_cbk)
			hperh->acmp_warmup_cplt_cbk(hperh);
	}

	if ((ald_acmp_get_mask_flag_status(hperh, ACMP_FLAG_EDGE)) == SET) {
		ald_acmp_clear_flag_status(hperh, ACMP_FLAG_EDGE);

		if (hperh->acmp_edge_cplt_cbk)
			hperh->acmp_edge_cplt_cbk(hperh);
	}

	return;
}

/**
  * @brief  This function config acmp output.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  state: ENABLE/DISABLE.
  * @retval None
  */
void ald_acmp_out_config(acmp_handle_t *hperh, type_func_t state)
{
	assert_param(IS_ACMP_TYPE(hperh->perh));
	assert_param(IS_FUNC_STATE(state));

	if (state)
		SET_BIT(hperh->perh->PORT, ACMP_PORT_PEN_MSK);
	else
		CLEAR_BIT(hperh->perh->PORT, ACMP_PORT_PEN_MSK);

	return;
}

/**
  * @brief  This function output acmp result.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @retval output value.
  */
uint8_t ald_acmp_out_result(acmp_handle_t *hperh)
{
	assert_param(IS_ACMP_TYPE(hperh->perh));

	return (READ_BIT(hperh->perh->STAT, ACMP_STAT_OUT_MSK) >> ACMP_STAT_OUT_POS);
}

/** @brief  Check whether the specified ACMP flag is set or not.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  status: specifies the status to check.
  *         This parameter can be one of the @ref acmp_status_t.
  * @retval flag_status_t
  *           - SET
  *           - RESET
  */
flag_status_t ald_acmp_get_status(acmp_handle_t *hperh, acmp_status_t status)
{
	assert_param(IS_ACMP_TYPE(hperh->perh));
	assert_param(IS_ACMP_STATUS_TYPE(status));

	if (hperh->perh->STAT & status)
		return SET;

	return RESET;
}
/**
  * @}
  */
/**
  * @}
  */
#endif /* ALD_ACMP */
/**
  * @}
  */
/**
  * @}
  */
