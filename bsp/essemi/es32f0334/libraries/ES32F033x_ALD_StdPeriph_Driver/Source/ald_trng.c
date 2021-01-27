/**
  *********************************************************************************
  *
  * @file    ald_trng.c
  * @brief   TRNG module driver.
  *
  * @version V1.0
  * @date    04 Dec 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#include "ald_trng.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup TRNG TRNG
  * @brief TRNG module driver
  * @{
  */
#ifdef ALD_TRNG

/** @addtogroup CRYPT_Private_Functions CRYPT Private Functions
  * @{
  */
void trng_reset(trng_handle_t *hperh);
/**
  * @}
  */ 

/** @defgroup TRNG_Public_Functions TRNG Public Functions
  * @{
  */

/** @addtogroup TRNG_Public_Functions_Group1 Initialization functions
  * @brief Initialization functions
  *
  * @verbatim
  ==============================================================================
              ##### Initialization functions #####
  ==============================================================================
    [..]  This section provides functions allowing to initialize the TRNG:
      (+) This parameters can be configured:
        (++) Word Width
        (++) Seed Type
        (++) Seed
        (++) Start Time
        (++) Adjust parameter

    @endverbatim
  * @{
  */


/**
  * @brief  Initializes the TRNG according to the specified
  *         parameters in the trng_init_t.
  * @param  hperh: Pointer to a trng_handle_t structure that contains
  *         the configuration information for the specified TRNG module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_trng_init(trng_handle_t *hperh)
{
	uint32_t tmp = 0;

	if (hperh == NULL)
		return ERROR;

	assert_param(IS_TRNG_DATA_WIDTH(hperh->init.data_width));
	assert_param(IS_TRNG_SEED_TYPE(hperh->init.seed_type));
	assert_param(IS_TRNG_ADJC(hperh->init.adjc));
	assert_param(IS_FUNC_STATE(hperh->init.posten));
	assert_param(IS_TRNG_T_START(hperh->init.t_start));

	__LOCK(hperh);
	trng_reset(hperh);

	if (hperh->state == TRNG_STATE_RESET)
		__UNLOCK(hperh);

	tmp = TRNG->CR;

	if (hperh->init.adjc == 0)
		tmp = (0 << TRNG_CR_ADJM_POS);
	else
		tmp = (1 << TRNG_CR_ADJM_POS);

	tmp |= ((1 << TRNG_CR_TRNGSEL_POS) | (hperh->init.data_width << TRNG_CR_DSEL_POSS) |
	       (hperh->init.seed_type << TRNG_CR_SDSEL_POSS) | (hperh->init.adjc << TRNG_CR_ADJC_POSS) |
	       (hperh->init.posten << TRNG_CR_POSTEN_MSK));

	TRNG->CR = tmp;

	WRITE_REG(TRNG->SEED, hperh->init.seed);
	MODIFY_REG(TRNG->CFGR, TRNG_CFGR_TSTART_MSK, (hperh->init.t_start) << TRNG_CFGR_TSTART_POSS);

	hperh->state = TRNG_STATE_READY;
	__UNLOCK(hperh);
	return OK;
}
/**
  * @}
  */

/** @addtogroup TRNG_Public_Functions_Group2 Peripheral Control functions
  * @brief Peripheral Control functions
  *
  * @verbatim
  ==============================================================================
              ##### Peripheral Control functions #####
  ==============================================================================
  [..]  This section provides functions allowing to:
    (+) ald_trng_get_result() API can Get the result.
    (+) ald_trng_interrupt_config() API can be helpful to configure TRNG interrupt source.
    (+) ald_trng_get_it_status() API can get the status of interrupt source.
    (+) ald_trng_get_status() API can get the status of SR register.
    (+) ald_trng_get_flag_status() API can get the status of interrupt flag.
    (+) ald_trng_clear_flag_status() API can clear interrupt flag.

    @endverbatim
  * @{
  */

/**
  * @brief  Get the result.
  * @param  hperh: Pointer to a trng_handle_t structure that contains
  *         the configuration information for the specified TRNG module.
  * @retval The resultl
  */
uint32_t ald_trng_get_result(trng_handle_t *hperh)
{
	hperh->state = TRNG_STATE_READY;
	hperh->data = hperh->perh->DR;
	return (uint32_t)hperh->perh->DR;
}

/**
  * @brief  Enable/disable the specified interrupts.
  * @param  hperh: Pointer to a trng_handle_t structure that contains
  *         the configuration information for the specified TRNG module.
  * @param  it: Specifies the interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref trng_it_t.
  * @param  state: New state of the specified interrupts.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_trng_interrupt_config(trng_handle_t *hperh, trng_it_t it, type_func_t state)
{
	assert_param(IS_TRNG_IT(it));
	assert_param(IS_FUNC_STATE(state));

	if (state)
		SET_BIT(hperh->perh->IER, it);
	else
		CLEAR_BIT(hperh->perh->IER, it);

	return;
}

/**
  * @brief  Get the status of SR register.
  * @param  hperh: Pointer to a trng_handle_t structure that contains
  *         the configuration information for the specified TRNG module.
  * @param  status: Specifies the TRNG status type.
  *         This parameter can be one of the @ref trng_status_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_trng_get_status(trng_handle_t *hperh, trng_status_t status)
{
	assert_param(IS_TRNG_STATUS(status));

	if (READ_BIT(hperh->perh->SR, status))
		return SET;

	return RESET;
}

/**
  * @brief  Get the status of interrupt source.
  * @param  hperh: Pointer to a trng_handle_t structure that contains
  *         the configuration information for the specified TRNG module.
  * @param  it: Specifies the interrupt source.
  *         This parameter can be one of the @ref trng_it_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
it_status_t ald_trng_get_it_status(trng_handle_t *hperh, trng_it_t it)
{
	assert_param(IS_TRNG_IT(it));

	if (READ_BIT(hperh->perh->IER, it))
		return SET;

	return RESET;
}

/**
  * @brief  Get the status of interrupt flag.
  * @param  hperh: Pointer to a trng_handle_t structure that contains
  *         the configuration information for the specified TRNG module.
  * @param  flag: Specifies the interrupt flag.
  *         This parameter can be one of the @ref trng_flag_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_trng_get_flag_status(trng_handle_t *hperh, trng_flag_t flag)
{
	assert_param(IS_TRNG_FLAG(flag));

	if (READ_BIT(hperh->perh->IFR, flag))
		return SET;

	return RESET;
}

/**
  * @brief  Clear the interrupt flag.
  * @param  hperh: Pointer to a trng_handle_t structure that contains
  *         the configuration information for the specified TRNG module.
  * @param  flag: Specifies the interrupt flag.
  *         This parameter can be one of the @ref trng_flag_t.
  * @retval None
  */
void ald_trng_clear_flag_status(trng_handle_t *hperh, trng_flag_t flag)
{
	assert_param(IS_TRNG_FLAG(flag));
	WRITE_REG(hperh->perh->IFCR, flag);

	return;
}

/**
  * @brief  Reset the TRNG peripheral.
  * @param  hperh: Pointer to a trng_handle_t structure that contains
  *         the configuration information for the specified TRNG module.
  * @retval None
  */
void trng_reset(trng_handle_t *hperh)
{
	TRNG->CR = 0;
	TRNG->SEED = 0;
	TRNG->CFGR = 0x1FF0707;
	TRNG->IER = 0;
	TRNG->IFCR = 0xFFFFFFFF;

	hperh->state = TRNG_STATE_READY;
	__UNLOCK(hperh);
	return;
}

/**
  * @brief  This function handles TRNG interrupt request.
  * @param  hperh: Pointer to a trng_handle_t structure that contains
  *         the configuration information for the specified TRNG module.
  * @retval None
  */
void ald_trng_irq_handler(trng_handle_t *hperh)
{
	if (ald_trng_get_flag_status(hperh, TRNG_IF_SERR) == SET) {
		hperh->state = TRNG_STATE_ERROR;
		ald_trng_clear_flag_status(hperh, TRNG_IF_SERR);
		if (hperh->err_cplt_cbk)
			hperh->err_cplt_cbk(hperh);
		return;
	}

	if (ald_trng_get_flag_status(hperh, TRNG_IF_DAVLD) == SET) {
		hperh->data = hperh->perh->DR;
		hperh->state = TRNG_STATE_READY;
		ald_trng_clear_flag_status(hperh, TRNG_IF_DAVLD);
		if (hperh->trng_cplt_cbk)
			hperh->trng_cplt_cbk(hperh);
	}

	if (ald_trng_get_flag_status(hperh, TRNG_IF_START) == SET) {
		hperh->state = TRNG_STATE_BUSY;
		ald_trng_clear_flag_status(hperh, TRNG_IF_START);
		if (hperh->init_cplt_cbk)
			hperh->init_cplt_cbk(hperh);
	}
}

/**
  * @}
  */
/**
  * @}
  */
#endif /* ALD_TRNG */
/**
  * @}
  */

/**
  * @}
  */
