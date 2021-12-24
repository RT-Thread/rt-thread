/**
  *********************************************************************************
  *
  * @file    ald_timer.c
  * @brief   TIMER module driver.
  *	     This is the common part of the TIMER initialization
  *
  * @version V1.0
  * @date    06 Nov 2017
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
  *********************************************************************************
  */

#include <string.h>
#include "ald_timer.h"
#include "ald_cmu.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup TIMER TIMER
  * @brief TIMER module driver
  * @{
  */
#ifdef ALD_TIMER

/** @defgroup TIMER_Private_Functions TIMER Private Functions
  * @{
  */
static void timer_base_set_config(TIMER_TypeDef *TIMERx, timer_base_init_t *init);
static void timer_oc1_set_config(TIMER_TypeDef *TIMERx, timer_oc_init_t *oc_config);
static void timer_oc2_set_config(TIMER_TypeDef *TIMERx, timer_oc_init_t *oc_config);
static void timer_oc3_set_config(TIMER_TypeDef *TIMERx, timer_oc_init_t *oc_config);
static void timer_oc4_set_config(TIMER_TypeDef *TIMERx, timer_oc_init_t *oc_config);
static void timer_ccx_channel_cmd(TIMER_TypeDef* TIMERx, timer_channel_t ch, type_func_t state);
static void timer_ccxn_channel_cmd(TIMER_TypeDef* TIMERx, timer_channel_t ch, type_func_t state);
static void timer_ti1_set_config(TIMER_TypeDef *TIMERx, timer_ic_polarity_t polarity,
                                   timer_ic_select_t sel, uint32_t filter);
static void timer_ti1_set_config_stage(TIMER_TypeDef *TIMERx, timer_ic_polarity_t polarity, uint32_t filter);
static void timer_ti2_set_config(TIMER_TypeDef *TIMERx, timer_ic_polarity_t polarity,
                                   timer_ic_select_t sel, uint32_t filter);
static void timer_ti2_set_config_stage(TIMER_TypeDef *TIMERx, timer_ic_polarity_t polarity, uint32_t filter);
static void timer_ti3_set_config(TIMER_TypeDef *TIMERx, timer_ic_polarity_t polarity,
                                   timer_ic_select_t sel, uint32_t filter);
static void timer_ti4_set_config(TIMER_TypeDef *TIMERx, timer_ic_polarity_t polarity,
                                   timer_ic_select_t sel, uint32_t filter);
static void timer_etr_set_config(TIMER_TypeDef* TIMERx, timer_etr_psc_t psc, timer_clock_polarity_t polarity, uint32_t filter);
static void timer_slave_set_config(timer_handle_t *hperh, timer_slave_config_t *config);
#ifdef ALD_DMA
static void timer_dma_oc_cplt(void *arg);
static void timer_dma_capture_cplt(void *arg);
static void timer_dma_period_elapse_cplt(void *arg);
static void timer_dma_error(void *arg);
static void timer_dma_msel(TIMER_TypeDef *hperh, dma_config_t *config);
#endif
/**
  * @}
  */

/** @defgroup  TIMER_Public_Functions TIMER Public Functions
  * @{
  */

/** @defgroup TIMER_Public_Functions_Group1 TIMER Base functions
  * @brief    Time Base functions
  *
  * @verbatim
  ==============================================================================
              ##### Timer Base functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the TIMER base.
    (+) Reset the TIMER base.
    (+) Start the Time Base.
    (+) Stop the Time Base.
    (+) Start the Time Base and enable interrupt.
    (+) Stop the Time Base and disable interrupt.
    (+) Start the Time Base and enable DMA transfer.
    (+) Stop the Time Base and disable DMA transfer.

    @endverbatim
  * @{
  */
/**
  * @brief  Initializes the TIMER Time base Unit according to the specified
  *         parameters in the timer_handle_t and create the associated handle.
  * @param  hperh: TIMER base handle
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_base_init(timer_handle_t *hperh)
{
	if (hperh == NULL)
		return ERROR;

	assert_param(IS_TIMER_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_COUNTER_MODE(hperh->init.mode));
	assert_param(IS_TIMER_CLOCK_DIVISION(hperh->init.clk_div));

	if (hperh->state == TIMER_STATE_RESET)
		hperh->lock = UNLOCK;

	hperh->state = TIMER_STATE_BUSY;
	timer_base_set_config(hperh->perh, &hperh->init);
	hperh->state = TIMER_STATE_READY;

	return OK;
}

/**
  * @brief  Reset the TIMER base peripheral
  * @param  hperh: TIMER base handle
  * @retval Status, see @ref ald_status_t.
  */
void ald_timer_base_reset(timer_handle_t *hperh)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));

	hperh->state = TIMER_STATE_BUSY;
	TIMER_DISABLE(hperh);
	hperh->state = TIMER_STATE_RESET;
	__UNLOCK(hperh);

	return;
}

/**
  * @brief  Starts the TIMER Base generation.
  * @param  hperh: TIMER handle
  * @retval None
  */
void ald_timer_base_start(timer_handle_t *hperh)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));

	hperh->state = TIMER_STATE_BUSY;
	SET_BIT(hperh->perh->SGE, TIMER_SGE_SGU_MSK);
	SET_BIT(hperh->perh->ICR, TIMER_ICR_UEIC_MSK);
	TIMER_ENABLE(hperh);
	hperh->state = TIMER_STATE_READY;

	return;
}

/**
  * @brief  Stops the TIMER Base generation.
  * @param  hperh: TIMER handle
  * @retval None
  */
void ald_timer_base_stop(timer_handle_t *hperh)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));

	hperh->state = TIMER_STATE_BUSY;
	TIMER_DISABLE(hperh);
	hperh->state = TIMER_STATE_READY;

	return;
}

/**
  * @brief  Starts the TIMER Base generation in interrupt mode.
  * @param  hperh: TIMER handle
  * @retval None
  */
void ald_timer_base_start_by_it(timer_handle_t *hperh)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));

	ald_timer_interrupt_config(hperh, TIMER_IT_UPDATE, ENABLE);
	TIMER_ENABLE(hperh);

	return;
}

/**
  * @brief  Stops the TIMER Base generation in interrupt mode.
  * @param  hperh: TIMER handle
  * @retval None
  */
void ald_timer_base_stop_by_it(timer_handle_t *hperh)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));

	ald_timer_interrupt_config(hperh, TIMER_IT_UPDATE, DISABLE);
	TIMER_DISABLE(hperh);

	return;
}

#ifdef ALD_DMA
/**
  * @brief  Starts the TIMER Base generation in DMA mode.
  * @param  hperh: TIMER handle
  * @param  buf: The source Buffer address.
  * @param  len: The length of buffer to be transferred from memory to TIMER peripheral
  * @param  dma_ch: Channel of DMA.
  * @retval Status, see @ref ald_status_t.
*/
ald_status_t ald_timer_base_start_by_dma(timer_handle_t *hperh, 
                                  uint16_t *buf, uint32_t len, uint8_t dma_ch)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));

	if ((hperh->state == TIMER_STATE_BUSY))
		 return BUSY;
	if ((hperh->state == TIMER_STATE_READY)) {
		if (((uint32_t)buf == 0 ) || (len == 0))
			return ERROR;
	}

	hperh->state   = TIMER_STATE_BUSY;

	if (hperh->hdma1.perh == NULL)
		hperh->hdma1.perh = DMA0;

	hperh->hdma1.cplt_cbk = timer_dma_period_elapse_cplt;
	hperh->hdma1.cplt_arg = (void *)hperh;
	hperh->hdma1.err_cbk  = timer_dma_error;
	hperh->hdma1.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdma1.config);
	hperh->hdma1.config.src        = (void *)buf;
	hperh->hdma1.config.dst        = (void *)&hperh->perh->AR;
	hperh->hdma1.config.size       = len;
	hperh->hdma1.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdma1.config.src_inc    = DMA_DATA_INC_HALFWORD;
	hperh->hdma1.config.dst_inc    = DMA_DATA_INC_NONE;
	hperh->hdma1.config.msigsel    = DMA_MSIGSEL_TIMER_UPDATE;
	hperh->hdma1.config.channel    = dma_ch;

	timer_dma_msel(hperh->perh, &hperh->hdma1.config);
	ald_dma_config_basic(&hperh->hdma1);
	ald_timer_dma_req_config(hperh, TIMER_DMA_UPDATE, ENABLE);
	TIMER_ENABLE(hperh);

	return OK;
}

/**
  * @brief  Stops the TIMER Base generation in DMA mode.
  * @param  hperh: TIMER handle
  * @retval None
*/
void ald_timer_base_stop_by_dma(timer_handle_t *hperh)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));

	ald_timer_dma_req_config(hperh, TIMER_DMA_UPDATE, DISABLE);
	TIMER_DISABLE(hperh);
	hperh->state = TIMER_STATE_READY;

	return;
}
#endif
/**
  * @}
  */

/** @defgroup TIMER_Public_Functions_Group2 TIMER Output Compare functions
  *  @brief   Time Output Compare functions
  *
  * @verbatim
  ==============================================================================
                  ##### Time Output Compare functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the TIMER Output Compare.
    (+) Start the Time Output Compare.
    (+) Stop the Time Output Compare.
    (+) Start the Time Output Compare and enable interrupt.
    (+) Stop the Time Output Compare and disable interrupt.
    (+) Start the Time Output Compare and enable DMA transfer.
    (+) Stop the Time Output Compare and disable DMA transfer.

    @endverbatim
  * @{
  */
/**
  * @brief  Initializes the TIMER Output Compare according to the specified
  *         parameters in the timer_handle_t and create the associated handle.
  * @param  hperh: TIMER handle
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_oc_init(timer_handle_t *hperh)
{
	return ald_timer_base_init(hperh);
}

/**
  * @brief  Starts the TIMER Output Compare signal generation.
  * @param  hperh: TIMER handle
  * @param  ch : TIMER Channel to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *            @arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_oc_start(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));

	timer_ccx_channel_cmd(hperh->perh, ch, ENABLE);

	if (IS_TIMER_BREAK_INSTANCE(hperh->perh) != RESET)
		TIMER_MOE_ENABLE(hperh);

	TIMER_ENABLE(hperh);
	return;
}

/**
  * @brief  Stops the TIMER Output Compare signal generation.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channel to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *            @arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_oc_stop(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));

	timer_ccx_channel_cmd(hperh->perh, ch, DISABLE);

	if (IS_TIMER_BREAK_INSTANCE(hperh->perh) != RESET)
		TIMER_MOE_DISABLE(hperh);

	TIMER_DISABLE(hperh);
	hperh->state = TIMER_STATE_READY;
	return;
}

/**
  * @brief  Starts the TIMER Output Compare signal generation in interrupt mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channel to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *            @arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_oc_start_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));

	switch (ch) {
	case TIMER_CHANNEL_1:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC1, ENABLE);
		break;

	case TIMER_CHANNEL_2:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC2, ENABLE);
		break;

	case TIMER_CHANNEL_3:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC3, ENABLE);
		break;

	case TIMER_CHANNEL_4:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC4, ENABLE);
		break;

	default:
		break;
	}

	timer_ccx_channel_cmd(hperh->perh, ch, ENABLE);

	if (IS_TIMER_BREAK_INSTANCE(hperh->perh) != RESET)
		TIMER_MOE_ENABLE(hperh);

	TIMER_ENABLE(hperh);
	return;
}

/**
  * @brief  Stops the TIMER Output Compare signal generation in interrupt mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channel to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *            @arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_oc_stop_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));

	switch (ch) {
	case TIMER_CHANNEL_1:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC1, DISABLE);
		break;

	case TIMER_CHANNEL_2:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC2, DISABLE);
		break;

	case TIMER_CHANNEL_3:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC3, DISABLE);
		break;

	case TIMER_CHANNEL_4:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC4, DISABLE);
		break;

	default:
		break;
	}

	timer_ccx_channel_cmd(hperh->perh, ch, DISABLE);

	if (IS_TIMER_BREAK_INSTANCE(hperh->perh) != RESET)
		TIMER_MOE_DISABLE(hperh);

	TIMER_DISABLE(hperh);
	hperh->state = TIMER_STATE_READY;
	return;
}





#ifdef ALD_DMA
/**
  * @brief  Starts the TIMER Output Compare signal generation in DMA mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @param  buf: The source Buffer address.
  * @param  len: The length of buffer to be transferred from memory to TIMER peripheral
  * @param  dma_ch: Channel of DMA.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_oc_start_by_dma(timer_handle_t *hperh, timer_channel_t ch,
                      uint16_t *buf, uint32_t len, uint8_t dma_ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));

	if ((hperh->state == TIMER_STATE_BUSY))
		 return BUSY;
	if ((hperh->state == TIMER_STATE_READY)) {
		if (((uint32_t)buf == 0 ) || (len == 0))
			return ERROR;
	}

	hperh->state   = TIMER_STATE_BUSY;

	if (hperh->hdma1.perh == NULL)
		hperh->hdma1.perh = DMA0;

	hperh->hdma1.cplt_cbk = timer_dma_oc_cplt;
	hperh->hdma1.cplt_arg = (void *)hperh;
	hperh->hdma1.err_cbk  = timer_dma_error;
	hperh->hdma1.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdma1.config);
	hperh->hdma1.config.src        = (void *)buf;
	hperh->hdma1.config.size       = len;
	hperh->hdma1.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdma1.config.src_inc    = DMA_DATA_INC_HALFWORD;
	hperh->hdma1.config.dst_inc    = DMA_DATA_INC_NONE;
	hperh->hdma1.config.channel    = dma_ch;


	timer_dma_msel(hperh->perh, &hperh->hdma1.config);

	switch (ch) {
	case TIMER_CHANNEL_1:
		hperh->hdma1.config.dst     = (void *)&hperh->perh->CCVAL1;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH1;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC1, ENABLE);
		hperh->ch = TIMER_ACTIVE_CHANNEL_1;
		break;

	case TIMER_CHANNEL_2:
		hperh->hdma1.config.dst     = (void *)&hperh->perh->CCVAL2;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH2;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC2, ENABLE);
		hperh->ch = TIMER_ACTIVE_CHANNEL_2;
		break;

	case TIMER_CHANNEL_3:
		hperh->hdma1.config.dst     = (void *)&hperh->perh->CCVAL3;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH3;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC3, ENABLE);
		hperh->ch = TIMER_ACTIVE_CHANNEL_3;
		break;

	case TIMER_CHANNEL_4:
		hperh->hdma1.config.dst     = (void *)&hperh->perh->CCVAL4;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH4;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC4, ENABLE);
		hperh->ch = TIMER_ACTIVE_CHANNEL_4;
		break;

	default:
		break;
	}

	timer_ccx_channel_cmd(hperh->perh, ch, ENABLE);

	if (IS_TIMER_BREAK_INSTANCE(hperh->perh) != RESET)
		TIMER_MOE_ENABLE(hperh);

	TIMER_ENABLE(hperh);
	return OK;
}

/**
  * @brief  Stops the TIMER Output Compare signal generation in DMA mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
*/
void ald_timer_oc_stop_by_dma(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));

	switch (ch) {
	case TIMER_CHANNEL_1:
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC1, DISABLE);
		break;

	case TIMER_CHANNEL_2:
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC2, DISABLE);
		break;

	case TIMER_CHANNEL_3:
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC3, DISABLE);
		break;

	case TIMER_CHANNEL_4:
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC4, DISABLE);
		break;

	default:
		break;
	}

	timer_ccx_channel_cmd(hperh->perh, ch, DISABLE);

	if (IS_TIMER_BREAK_INSTANCE(hperh->perh) != RESET)
		TIMER_MOE_DISABLE(hperh);

	TIMER_DISABLE(hperh);
	hperh->state = TIMER_STATE_READY;
	return;
}
#endif
/**
  * @}
  */

/** @defgroup  TIMER_Public_Functions_Group3 TIMER PWM functions
  * @brief     TIMER PWM functions
  *
  * @verbatim
	==============================================================================
	##### Time PWM functions #####
	==============================================================================
	[..]
		This section provides functions allowing to:
		(+) Initialize and configure the TIMER PWM.
		(+) Start the Time PWM.
		(+) Stop the Time PWM.
		(+) Start the Time PWM and enable interrupt.
		(+) Stop the Time PWM and disable interrupt.
		(+) Start the Time PWM and enable DMA transfer.
		(+) Stop the Time PWM and disable DMA transfer.

    @endverbatim
  * @{
  */
/**
  * @brief  Initializes the TIMER PWM Time Base according to the specified
  *         parameters in the timer_handle_t and create the associated handle.
  * @param  hperh: TIMER handle
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_pwm_init(timer_handle_t *hperh)
{
	return ald_timer_base_init(hperh);
}

/**
  * @brief  Starts the PWM signal generation.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_pwm_start(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_oc_start(hperh, ch);
	return;
}

/**
  * @brief  Stops the PWM signal generation.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_pwm_stop(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_oc_stop(hperh, ch);
	return;
}

/**
  * @brief  Starts the PWM signal generation in interrupt mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channel to be disabled
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_pwm_start_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_oc_start_by_it(hperh, ch);
	return;
}

/**
  * @brief  Stops the PWM signal generation in interrupt mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_pwm_stop_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_oc_stop_by_it(hperh, ch);
	return;
}

#ifdef ALD_DMA
/**
  * @brief  Starts the TIMER PWM signal generation in DMA mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @param  buf: The source Buffer address.
  * @param  len: The length of buffer to be transferred from memory to TIMER peripheral
  * @param  dma_ch: Channel of DMA.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_pwm_start_by_dma(timer_handle_t *hperh, timer_channel_t ch,
                      uint16_t *buf, uint32_t len, uint8_t dma_ch)
{
	return ald_timer_oc_start_by_dma(hperh, ch, buf, len, dma_ch);
}

/**
  * @brief  Stops the TIMER PWM signal generation in DMA mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_pwm_stop_by_dma(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_oc_stop_by_dma(hperh, ch);
	return;
}
#endif
/**
  * @brief  Set the PWM freq.
  * @param  hperh: TIMER handle
  * @param  freq: PWM freq to set
  * @retval None
  */
void ald_timer_pwm_set_freq(timer_handle_t *hperh, uint16_t freq)
{
	uint32_t _arr;

	if (freq == 0)
		return;

	_arr = ald_cmu_get_pclk1_clock() / (hperh->init.prescaler + 1) / freq - 1;
	WRITE_REG(hperh->perh->AR, _arr);
	hperh->init.period   = _arr;
}

/**
  * @brief  Set the PWM duty.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @param  duty: PWM duty to set
  * @retval None
  */
void ald_timer_pwm_set_duty(timer_handle_t *hperh, timer_channel_t ch, uint16_t duty)
{
	uint32_t tmp = (hperh->init.period + 1) * duty / 100 - 1;

	if (ch == TIMER_CHANNEL_1)
		WRITE_REG(hperh->perh->CCVAL1, tmp);
	else if (ch == TIMER_CHANNEL_2)
		WRITE_REG(hperh->perh->CCVAL2, tmp);
	else if (ch == TIMER_CHANNEL_3)
		WRITE_REG(hperh->perh->CCVAL3, tmp);
	else if (ch == TIMER_CHANNEL_4)
		WRITE_REG(hperh->perh->CCVAL4, tmp);
	else {
		;/* do nothing */
	}
}

/**
  * @brief  Set capture the PWM.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be captured the PWM
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  * @retval None
  */
void ald_timer_pwm_set_input(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_PWM_INPUT_INSTANCE(hperh->perh, ch));

	CLEAR_BIT(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK);
	switch (ch) {
	case TIMER_CHANNEL_1:
		MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_CC1SSEL_MSK, TIMER_IC_SEL_DIRECT << TIMER_CHMR1_CC1SSEL_POSS);
		MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_CC2SSEL_MSK, TIMER_IC_SEL_INDIRECT << TIMER_CHMR1_CC2SSEL_POSS);
		MODIFY_REG(hperh->perh->CCEP, TIMER_CCEP_CC1POL_MSK, TIMER_IC_POLARITY_RISE << TIMER_CCEP_CC1POL_POS);
		MODIFY_REG(hperh->perh->CCEP, TIMER_CCEP_CC1NPOL_MSK, TIMER_IC_POLARITY_RISE << TIMER_CCEP_CC1NPOL_POS);
		MODIFY_REG(hperh->perh->CCEP, TIMER_CCEP_CC2POL_MSK, TIMER_IC_POLARITY_FALL << TIMER_CCEP_CC2POL_POS);
		MODIFY_REG(hperh->perh->CCEP, TIMER_CCEP_CC2NPOL_MSK, TIMER_IC_POLARITY_FALL << TIMER_CCEP_CC2NPOL_POS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_TI1FP1 << TIMER_SMCON_TSSEL_POSS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_RESET << TIMER_SMCON_SMODS_POSS);
		break;
	case TIMER_CHANNEL_2:
		MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_CC1SSEL_MSK, TIMER_IC_SEL_INDIRECT << TIMER_CHMR1_CC1SSEL_POSS);
		MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_CC2SSEL_MSK, TIMER_IC_SEL_DIRECT << TIMER_CHMR1_CC2SSEL_POSS);
		MODIFY_REG(hperh->perh->CCEP, TIMER_CCEP_CC1POL_MSK, TIMER_IC_POLARITY_RISE << TIMER_CCEP_CC1POL_POS);
		MODIFY_REG(hperh->perh->CCEP, TIMER_CCEP_CC1NPOL_MSK, TIMER_IC_POLARITY_FALL << TIMER_CCEP_CC1NPOL_POS);
		MODIFY_REG(hperh->perh->CCEP, TIMER_CCEP_CC2POL_MSK, TIMER_IC_POLARITY_FALL << TIMER_CCEP_CC2POL_POS);
		MODIFY_REG(hperh->perh->CCEP, TIMER_CCEP_CC2NPOL_MSK, TIMER_IC_POLARITY_RISE << TIMER_CCEP_CC2NPOL_POS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_TI2FP2 << TIMER_SMCON_TSSEL_POSS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_RESET << TIMER_SMCON_SMODS_POSS);
		break;
	default:
		break;
	}

	SET_BIT(hperh->perh->CCEP, TIMER_CCEP_CC1EN_MSK);
	SET_BIT(hperh->perh->CCEP, TIMER_CCEP_CC2EN_MSK);

	return;
}
/**
  * @}
  */

/** @defgroup TIMER_Public_Functions_Group4 TIMER Input Capture functions
  * @brief    Time Input Capture functions
  *
  * @verbatim
  ==============================================================================
              ##### Time Input Capture functions #####
  ==============================================================================
 [..]
   This section provides functions allowing to:
   (+) Initialize and configure the TIMER Input Capture.
   (+) Start the Time Input Capture.
   (+) Stop the Time Input Capture.
   (+) Start the Time Input Capture and enable interrupt.
   (+) Stop the Time Input Capture and disable interrupt.
   (+) Start the Time Input Capture and enable DMA transfer.
   (+) Stop the Time Input Capture and disable DMA transfer.

  * @endverbatim
  * @{
  */
/**
  * @brief  Initializes the TIMER Input Capture Time base according to the specified
  *         parameters in the timer_handle_t and create the associated handle.
  * @param  hperh: TIMER handle
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_ic_init(timer_handle_t *hperh)
{
	return ald_timer_base_init(hperh);
}

/**
  * @brief  Starts the TIMER Input Capture measurement.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *            @arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_ic_start(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));

	timer_ccx_channel_cmd(hperh->perh, ch, ENABLE);
	TIMER_ENABLE(hperh);
	return;
}

/**
  * @brief  Stops the TIMER Input Capture measurement.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *            @arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_ic_stop(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));

	timer_ccx_channel_cmd(hperh->perh, ch, DISABLE);
	TIMER_DISABLE(hperh);
	return;
}

/**
  * @brief  Starts the TIMER Input Capture measurement in interrupt mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *            @arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_ic_start_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));

	switch (ch) {
	case TIMER_CHANNEL_1:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC1, ENABLE);
		break;
	case TIMER_CHANNEL_2:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC2, ENABLE);
		break;
	case TIMER_CHANNEL_3:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC3, ENABLE);
		break;
	case TIMER_CHANNEL_4:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC4, ENABLE);
		break;
	default:
		break;
	}

	timer_ccx_channel_cmd(hperh->perh, ch, ENABLE);
	TIMER_ENABLE(hperh);
	return;
}

/**
  * @brief  Stops the TIMER Input Capture measurement in interrupt mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *            @arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_ic_stop_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));

	switch (ch) {
	case TIMER_CHANNEL_1:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC1, DISABLE);
		break;
	case TIMER_CHANNEL_2:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC2, DISABLE);
		break;
	case TIMER_CHANNEL_3:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC3, DISABLE);
		break;
	case TIMER_CHANNEL_4:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC4, DISABLE);
		break;
	default:
		break;
	}

	timer_ccx_channel_cmd(hperh->perh, ch, DISABLE);
	TIMER_DISABLE(hperh);
	return;
}

#ifdef ALD_DMA
/**
  * @brief  Starts the TIMER Input Capture measurement in DMA mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @param  buf: The destination Buffer address.
  * @param  len: The length of buffer to be transferred TIMER peripheral to memory
  * @param  dma_ch: Channel of DMA.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_ic_start_by_dma(timer_handle_t *hperh, timer_channel_t ch,
                     uint16_t *buf, uint32_t len, uint8_t dma_ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));

	if ((hperh->state == TIMER_STATE_BUSY))
		 return BUSY;
	if ((hperh->state == TIMER_STATE_READY)) {
		if (((uint32_t)buf == 0 ) || (len == 0))
			return ERROR;
	}

	hperh->state   = TIMER_STATE_BUSY;

	if (hperh->hdma1.perh == NULL)
		hperh->hdma1.perh = DMA0;

	hperh->hdma1.cplt_cbk = timer_dma_capture_cplt;
	hperh->hdma1.cplt_arg = (void *)hperh;
	hperh->hdma1.err_cbk  = timer_dma_error;
	hperh->hdma1.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdma1.config);
	hperh->hdma1.config.dst        = (void *)buf;
	hperh->hdma1.config.size       = len;
	hperh->hdma1.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdma1.config.src_inc    = DMA_DATA_INC_NONE;
	hperh->hdma1.config.dst_inc    = DMA_DATA_INC_HALFWORD;
	hperh->hdma1.config.channel    = dma_ch;

	timer_dma_msel(hperh->perh, &hperh->hdma1.config);

	switch (ch) {
	case TIMER_CHANNEL_1:
		hperh->hdma1.config.src     = (void *)&hperh->perh->CCVAL1;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH1;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC1, ENABLE);
		hperh->ch = TIMER_ACTIVE_CHANNEL_1;
		break;

	case TIMER_CHANNEL_2:
		hperh->hdma1.config.src     = (void *)&hperh->perh->CCVAL2;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH2;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC2, ENABLE);
		hperh->ch = TIMER_ACTIVE_CHANNEL_2;
		break;

	case TIMER_CHANNEL_3:
		hperh->hdma1.config.src     = (void *)&hperh->perh->CCVAL3;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH3;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC3, ENABLE);
		hperh->ch = TIMER_ACTIVE_CHANNEL_3;
		break;

	case TIMER_CHANNEL_4:
		hperh->hdma1.config.src     = (void *)&hperh->perh->CCVAL4;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH4;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC4, ENABLE);
		hperh->ch = TIMER_ACTIVE_CHANNEL_4;
		break;

	default:
		break;
	}

	timer_ccx_channel_cmd(hperh->perh, ch, ENABLE);
	TIMER_ENABLE(hperh);
	return OK;
}

/**
  * @brief  Stops the TIMER Input Capture measurement in DMA mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_ic_stop_by_dma(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));

	switch (ch) {
	case TIMER_CHANNEL_1:
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC1, DISABLE);
		break;
	case TIMER_CHANNEL_2:
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC2, DISABLE);
		break;
	case TIMER_CHANNEL_3:
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC3, DISABLE);
		break;
	case TIMER_CHANNEL_4:
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC4, DISABLE);
		break;
	default:
		break;
	}

	timer_ccx_channel_cmd(hperh->perh, ch, DISABLE);
	TIMER_DISABLE(hperh);
	hperh->state = TIMER_STATE_READY;
	return;
}
#endif
/**
  * @}
  */

/** @defgroup TIMER_Public_Functions_Group5 TIMER One Pulse functions
  * @brief    Time One Pulse functions
  *
  * @verbatim
  ==============================================================================
                        ##### Time One Pulse functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the TIMER One Pulse.
    (+) Start the Time One Pulse.
    (+) Stop the Time One Pulse.
    (+) Start the Time One Pulse and enable interrupt.
    (+) Stop the Time One Pulse and disable interrupt.
    (+) Start the Time One Pulse and enable DMA transfer.
    (+) Stop the Time One Pulse and disable DMA transfer.

  * @endverbatim
  * @{
  */
/**
  * @brief  Initializes the TIMER One Pulse Time Base according to the specified
  *         parameters in the timer_handle_t and create the associated handle.
  * @param  hperh: TIMER handle
  * @param  mode: Select the One pulse mode.
  *         This parameter can be one of the following values:
  *            @arg TIMER_OP_MODE_SINGLE: Only one pulse will be generated.
  *            @arg TIMER_OP_MODE_REPEAT: Repetitive pulses wil be generated.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_one_pulse_init(timer_handle_t *hperh, timer_op_mode_t mode)
{
	if (hperh == NULL)
		return ERROR;

	assert_param(IS_TIMER_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_COUNTER_MODE(hperh->init.mode));
	assert_param(IS_TIMER_CLOCK_DIVISION(hperh->init.clk_div));
	assert_param(IS_TIMER_OP_MODE(mode));

	if (hperh->state == TIMER_STATE_RESET)
		hperh->lock = UNLOCK;

	hperh->state = TIMER_STATE_BUSY;
	timer_base_set_config(hperh->perh, &hperh->init);
	MODIFY_REG(hperh->perh->CON1, TIMER_CON1_SPMEN_MSK, mode << TIMER_CON1_SPMEN_POS);
	hperh->state = TIMER_STATE_READY;

	return OK;
}

/**
  * @brief  Starts the TIMER One Pulse signal generation.
  * @param  hperh: TIMER One Pulse handle
  * @param  ch: TIMER Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_OP_OUTPUT_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_OP_OUTPUT_CHANNEL_2: TIMER Channel 2 selected
  * @retval None
  */
void ald_timer_one_pulse_start(timer_handle_t *hperh, timer_op_output_channel_t ch)
{
	/* Enable the Capture compare and the Input Capture channels
	 * (in the OPM Mode the two possible channels that can be used are TIMER_CHANNEL_1 and TIMER_CHANNEL_2)
	 * if TIMER_CHANNEL_1 is used as output, the TIMER_CHANNEL_2 will be used as input and
	 * if TIMER_CHANNEL_1 is used as input, the TIMER_CHANNEL_2 will be used as output
	 * in all combinations, the TIMER_CHANNEL_1 and TIMER_CHANNEL_2 should be enabled together
	 */
	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, ENABLE);
	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, ENABLE);

	if (IS_TIMER_BREAK_INSTANCE(hperh->perh) != RESET)
		TIMER_MOE_ENABLE(hperh);

	return;
}

/**
  * @brief  Stops the TIMER One Pulse signal generation.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_OP_OUTPUT_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_OP_OUTPUT_CHANNEL_2: TIMER Channel 2 selected
  * @retval None
  */
void ald_timer_one_pulse_stop(timer_handle_t *hperh, timer_op_output_channel_t ch)
{
	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, DISABLE);
	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, DISABLE);

	if (IS_TIMER_BREAK_INSTANCE(hperh->perh) != RESET)
		TIMER_MOE_DISABLE(hperh);

	TIMER_DISABLE(hperh);
	return;
}

/**
  * @brief  Starts the TIMER One Pulse signal generation in interrupt mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_OP_OUTPUT_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_OP_OUTPUT_CHANNEL_2: TIMER Channel 2 selected
  * @retval None
  */
void ald_timer_one_pulse_start_by_it(timer_handle_t *hperh, timer_op_output_channel_t ch)
{
	/* Enable the Capture compare and the Input Capture channels
	 * (in the OPM Mode the two possible channels that can be used are TIMER_CHANNEL_1 and TIMER_CHANNEL_2)
	 * if TIMER_CHANNEL_1 is used as output, the TIMER_CHANNEL_2 will be used as input and
	 * if TIMER_CHANNEL_1 is used as input, the TIMER_CHANNEL_2 will be used as output
	 * in all combinations, the TIMER_CHANNEL_1 and TIMER_CHANNEL_2 should be enabled together
	 */
	ald_timer_interrupt_config(hperh, TIMER_IT_CC1, ENABLE);
	ald_timer_interrupt_config(hperh, TIMER_IT_CC2, ENABLE);
	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, ENABLE);
	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, ENABLE);

	if (IS_TIMER_BREAK_INSTANCE(hperh->perh) != RESET)
		TIMER_MOE_ENABLE(hperh);

	return;
}

/**
  * @brief  Stops the TIMER One Pulse signal generation in interrupt mode.
  * @param  hperh : TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_OP_OUTPUT_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_OP_OUTPUT_CHANNEL_2: TIMER Channel 2 selected
  * @retval None
  */
void ald_timer_one_pulse_stop_by_it(timer_handle_t *hperh, timer_op_output_channel_t ch)
{
	ald_timer_interrupt_config(hperh, TIMER_IT_CC1, DISABLE);
	ald_timer_interrupt_config(hperh, TIMER_IT_CC2, DISABLE);
	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, DISABLE);
	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, DISABLE);

	if (IS_TIMER_BREAK_INSTANCE(hperh->perh) != RESET)
		TIMER_MOE_DISABLE(hperh);

	TIMER_DISABLE(hperh);
	return;
}
/**
  * @}
  */

/** @defgroup TIMER_Public_Functions_Group6 TIMER Encoder functions
  * @brief    TIMER Encoder functions
  *
  * @verbatim
	==============================================================================
	##### Time Encoder functions #####
	==============================================================================
	[..]
		This section provides functions allowing to:
		(+) Initialize and configure the TIMER Encoder.
		(+) Start the Time Encoder.
		(+) Stop the Time Encoder.
		(+) Start the Time Encoder and enable interrupt.
		(+) Stop the Time Encoder and disable interrupt.
		(+) Start the Time Encoder and enable DMA transfer.
		(+) Stop the Time Encoder and disable DMA transfer.

  * @endverbatim
  * @{
  */
/**
  * @brief  Initializes the TIMER Encoder Interface and create the associated handle.
  * @param  hperh: TIMER handle
  * @param  config: TIMER Encoder Interface configuration structure
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_encoder_init(timer_handle_t *hperh,  timer_encoder_init_t *config)
{
	if (hperh == NULL)
		return ERROR;

	assert_param(IS_TIMER_CC2_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_ENCODER_MODE(config->mode));
	assert_param(IS_TIMER_IC_POLARITY(config->ic1_polarity));
	assert_param(IS_TIMER_IC_POLARITY(config->ic2_polarity));
	assert_param(IS_TIMER_IC_SELECT(config->ic1_sel));
	assert_param(IS_TIMER_IC_SELECT(config->ic2_sel));
	assert_param(IS_TIMER_IC_PSC(config->ic1_psc));
	assert_param(IS_TIMER_IC_PSC(config->ic2_psc));
	assert_param(IS_TIMER_IC_FILTER(config->ic1_filter));
	assert_param(IS_TIMER_IC_FILTER(config->ic2_filter));

	if (hperh->state == TIMER_STATE_RESET)
		hperh->lock = UNLOCK;

	hperh->state = TIMER_STATE_BUSY;
	CLEAR_BIT(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK);
	timer_base_set_config(hperh->perh, &hperh->init);

	MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, config->mode << TIMER_SMCON_SMODS_POSS);
	MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_CC1SSEL_MSK, config->ic1_sel << TIMER_CHMR1_CC1SSEL_POSS);
	MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_CC2SSEL_MSK, config->ic2_sel << TIMER_CHMR1_CC2SSEL_POSS);
	MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_IC1PRES_MSK, config->ic1_psc << TIMER_CHMR1_IC1PRES_POSS);
	MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_IC2PRES_MSK, config->ic2_psc << TIMER_CHMR1_IC2PRES_POSS);
	MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_I1FLT_MSK, config->ic1_filter << TIMER_CHMR1_I1FLT_POSS);
	MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_I2FLT_MSK, config->ic2_filter << TIMER_CHMR1_I2FLT_POSS);
	MODIFY_REG(hperh->perh->CCEP, TIMER_CCEP_CC1POL_MSK, (config->ic1_polarity & 0x1) << TIMER_CCEP_CC1POL_POS);
	MODIFY_REG(hperh->perh->CCEP, TIMER_CCEP_CC1NPOL_MSK, ((config->ic1_polarity >> 1) & 0x1) << TIMER_CCEP_CC1NPOL_POS);
	MODIFY_REG(hperh->perh->CCEP, TIMER_CCEP_CC2POL_MSK, (config->ic2_polarity & 0x1) << TIMER_CCEP_CC2POL_POS);
	MODIFY_REG(hperh->perh->CCEP, TIMER_CCEP_CC2NPOL_MSK, ((config->ic2_polarity >> 1) & 0x1) << TIMER_CCEP_CC2NPOL_POS);

	hperh->state = TIMER_STATE_READY;
	return OK;
}

/**
  * @brief  Starts the TIMER Encoder Interface.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_ALL: TIMER Channel 1 and TIMER Channel 2 are selected
  * @retval None
  */
void ald_timer_encoder_start(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CC2_INSTANCE(hperh->perh));

	switch (ch) {
	case TIMER_CHANNEL_1:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, ENABLE);
		break;
	case TIMER_CHANNEL_2:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, ENABLE);
		break;
	default:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, ENABLE);
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, ENABLE);
		break;
	}

	TIMER_ENABLE(hperh);
	return;
}

/**
  * @brief  Stops the TIMER Encoder Interface.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_ALL: TIMER Channel 1 and TIMER Channel 2 are selected
  * @retval None
  */
void ald_timer_encoder_stop(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CC2_INSTANCE(hperh->perh));

	switch (ch) {
	case TIMER_CHANNEL_1:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, DISABLE);
		break;
	case TIMER_CHANNEL_2:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, DISABLE);
		break;
	default:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, DISABLE);
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, DISABLE);
		break;
	}

	TIMER_DISABLE(hperh);
	return;
}

/**
  * @brief  Starts the TIMER Encoder Interface in interrupt mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_ALL: TIMER Channel 1 and TIMER Channel 2 are selected
  * @retval None
  */
void ald_timer_encoder_start_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CC2_INSTANCE(hperh->perh));

	switch (ch) {
	case TIMER_CHANNEL_1:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, ENABLE);
		ald_timer_interrupt_config(hperh, TIMER_IT_CC1, ENABLE);
		break;
	case TIMER_CHANNEL_2:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, ENABLE);
		ald_timer_interrupt_config(hperh, TIMER_IT_CC2, ENABLE);
		break;
	default:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, ENABLE);
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, ENABLE);
		ald_timer_interrupt_config(hperh, TIMER_IT_CC1, ENABLE);
		ald_timer_interrupt_config(hperh, TIMER_IT_CC2, ENABLE);
		break;
	}

	TIMER_ENABLE(hperh);
	return;
}

/**
  * @brief  Stops the TIMER Encoder Interface in interrupt mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_ALL: TIMER Channel 1 and TIMER Channel 2 are selected
  * @retval None
  */
void ald_timer_encoder_stop_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CC2_INSTANCE(hperh->perh));

	switch (ch) {
	case TIMER_CHANNEL_1:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, DISABLE);
		ald_timer_interrupt_config(hperh, TIMER_IT_CC1, DISABLE);
		break;
	case TIMER_CHANNEL_2:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, DISABLE);
		ald_timer_interrupt_config(hperh, TIMER_IT_CC2, DISABLE);
		break;
	default:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, DISABLE);
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, DISABLE);
		ald_timer_interrupt_config(hperh, TIMER_IT_CC1, DISABLE);
		ald_timer_interrupt_config(hperh, TIMER_IT_CC2, DISABLE);
		break;
	}

	TIMER_DISABLE(hperh);
	hperh->state = TIMER_STATE_READY;
	return;
}

#ifdef ALD_DMA
/**
  * @brief  Starts the TIMER Encoder Interface in DMA mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_ALL: TIMER Channel 1 and TIMER Channel 2 are selected
  * @param  buf1: The destination Buffer address. Reading data from CCR1.
  * @param  buf2: The destination Buffer address. Reading data from CCR2.
  * @param  len: The length of buffer to be transferred TIMER peripheral to memory
  * @param  dma_ch1: Channel of DMA.
  * @param  dma_ch2: Channel of DMA.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_encoder_start_by_dma(timer_handle_t *hperh, timer_channel_t ch,
                           uint16_t *buf1, uint16_t *buf2, uint32_t len, 
			   uint8_t dma_ch1, uint8_t dma_ch2)
{
	assert_param(IS_TIMER_CC2_INSTANCE(hperh->perh));

	if ((hperh->state == TIMER_STATE_BUSY))
		 return BUSY;
	if ((hperh->state == TIMER_STATE_READY)) {
		if (((uint32_t)buf1 == 0) || ((uint32_t)buf2 == 0) || (len == 0))
			return ERROR;
	}

	if (hperh->hdma1.perh == NULL)
		hperh->hdma1.perh = DMA0;
	if (hperh->hdma2.perh == NULL)
		hperh->hdma2.perh = DMA0;

	hperh->state    = TIMER_STATE_BUSY;
	hperh->hdma1.cplt_cbk = timer_dma_capture_cplt;
	hperh->hdma1.cplt_arg = (void *)hperh;
	hperh->hdma1.err_cbk  = timer_dma_error;
	hperh->hdma1.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdma1.config);
	hperh->hdma1.config.size       = len;
	hperh->hdma1.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdma1.config.src_inc    = DMA_DATA_INC_NONE;
	hperh->hdma1.config.dst_inc    = DMA_DATA_INC_HALFWORD;

	timer_dma_msel(hperh->perh, &hperh->hdma1.config);

	switch (ch) {
	case TIMER_CHANNEL_1:
		hperh->hdma1.config.src     = (void *)&hperh->perh->CCVAL1;
		hperh->hdma1.config.dst     = (void *)buf1;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH1;
		hperh->hdma1.config.channel = dma_ch1;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC1, ENABLE);
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, ENABLE);
		TIMER_ENABLE(hperh);
		break;

	case TIMER_CHANNEL_2:
		hperh->hdma1.config.src     = (void *)&hperh->perh->CCVAL2;
		hperh->hdma1.config.dst     = (void *)buf2;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH2;
		hperh->hdma1.config.channel = dma_ch2;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC2, ENABLE);
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, ENABLE);
		TIMER_ENABLE(hperh);
		break;

	default:
		hperh->hdma2.cplt_cbk = timer_dma_capture_cplt;
		hperh->hdma2.cplt_arg = (void *)hperh;
		hperh->hdma2.err_cbk  = timer_dma_error;
		hperh->hdma2.err_arg  = (void *)hperh;
		memcpy(&hperh->hdma2.config, &hperh->hdma1.config, sizeof(dma_config_t));

		hperh->hdma1.config.src     = (void *)&hperh->perh->CCVAL1;
		hperh->hdma1.config.dst     = (void *)buf1;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH1;
		hperh->hdma1.config.channel = dma_ch1;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC1, ENABLE);

		hperh->hdma2.config.src     = (void *)&hperh->perh->CCVAL2;
		hperh->hdma2.config.dst     = (void *)buf2;
		hperh->hdma2.config.msigsel = DMA_MSIGSEL_TIMER_CH2;
		hperh->hdma2.config.channel = dma_ch2;
		ald_dma_config_basic(&hperh->hdma2);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC2, ENABLE);

		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, ENABLE);
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, ENABLE);
		TIMER_ENABLE(hperh);
		break;
	}

	return OK;
}

/**
  * @brief  Stops the TIMER Encoder Interface in DMA mode.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_ALL: TIMER Channel 1 and TIMER Channel 2 are selected
  * @retval None
  */
void ald_timer_encoder_stop_by_dma(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CC2_INSTANCE(hperh->perh));

	switch (ch) {
	case TIMER_CHANNEL_1:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, DISABLE);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC1, DISABLE);
		break;
	case TIMER_CHANNEL_2:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, DISABLE);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC2, DISABLE);
		break;
	default:
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, DISABLE);
		timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_2, DISABLE);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC1, DISABLE);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC2, DISABLE);
		break;
	}

	TIMER_DISABLE(hperh);
	hperh->state = TIMER_STATE_READY;
	return;
}
#endif
/**
  * @}
  */

/** @defgroup TIMER_Public_Functions_Group7 TIMER Hall Sensor functions
  * @brief    TIMER Hall Sensor functions
  *
  * @verbatim
	==============================================================================
	##### Time Hall Sensor functions #####
	==============================================================================
	[..]
		This section provides functions allowing to:
		(+) Initialize and configure the TIMER hall sensor.
		(+) Start the hall sensor.
		(+) Stop the hall sensor.
		(+) Start the hall sensor and enable interrupt.
		(+) Stop the hall sensor and disable interrupt.
		(+) Start the hall sensor and enable DMA transfer.
		(+) Stop the hal sensor and disable DMA transfer.

  * @endverbatim
  * @{
  */
/**
  * @brief  Initializes the TIMER Encoder Interface and create the associated handle.
  * @param  hperh: TIMER handle
  * @param  config: TIMER Encoder Interface configuration structure
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_hall_sensor_init(timer_handle_t *hperh,  timer_hall_sensor_init_t *config)
{
	timer_oc_init_t oc;

	assert_param(IS_TIMER_XOR_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_COUNTER_MODE(hperh->init.mode));
	assert_param(IS_TIMER_CLOCK_DIVISION(hperh->init.clk_div));
	assert_param(IS_TIMER_IC_POLARITY(config->polarity));
	assert_param(IS_TIMER_IC_PSC(config->psc));
	assert_param(IS_TIMER_IC_FILTER(config->filter));

	if (hperh->state == TIMER_STATE_RESET)
		hperh->lock = UNLOCK;

	hperh->state = TIMER_STATE_READY;
	timer_base_set_config(hperh->perh, &hperh->init);
	timer_ti1_set_config(hperh->perh, config->polarity, TIMER_IC_SEL_TRC, config->filter);

	MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_IC1PRES_MSK, config->psc << TIMER_CHMR1_IC1PRES_POSS);
	SET_BIT(hperh->perh->CON2, TIMER_CON2_I1FSEL_MSK);
	MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_TI1F_ED << TIMER_SMCON_TSSEL_POSS);
	MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_RESET << TIMER_SMCON_SMODS_POSS);

	oc.oc_mode        = TIMER_OC_MODE_PWM2;
	oc.pulse          = config->delay;
	oc.oc_polarity    = TIMER_OC_POLARITY_HIGH;
	oc.ocn_polarity   = TIMER_OCN_POLARITY_HIGH;
	oc.oc_fast_en     = DISABLE;
	oc.oc_idle        = TIMER_OC_IDLE_RESET;
	oc.ocn_idle       = TIMER_OCN_IDLE_RESET;
	timer_oc2_set_config(hperh->perh, &oc);

	MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_TRGO_OC2REF << TIMER_SMCON_SMODS_POSS);
	return OK;
}
/**
  * @brief  Starts the TIMER hall sensor interface.
  * @param  hperh: TIMER handle
  * @retval None
  */
void ald_timer_hall_sensor_start(timer_handle_t *hperh)
{
	assert_param(IS_TIMER_XOR_INSTANCE(hperh->perh));

	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, ENABLE);
	TIMER_ENABLE(hperh);

	return;
}

/**
  * @brief  Stops the TIMER hall sensor interface.
  * @param  hperh: TIMER handle
  * @retval None
  */
void ald_timer_hall_sensor_stop(timer_handle_t *hperh)
{
	assert_param(IS_TIMER_XOR_INSTANCE(hperh->perh));

	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, DISABLE);
	TIMER_DISABLE(hperh);

	return;
}

/**
  * @brief  Starts the TIMER hall sensor interface in interrupt mode.
  * @param  hperh: TIMER handle
  * @retval None
  */
void ald_timer_hall_sensor_start_by_it(timer_handle_t *hperh)
{
	assert_param(IS_TIMER_XOR_INSTANCE(hperh->perh));

	ald_timer_interrupt_config(hperh, TIMER_IT_CC1, ENABLE);
	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, ENABLE);
	TIMER_ENABLE(hperh);

	return;
}

/**
  * @brief  Stops the TIMER hall sensor interface in interrupt mode.
  * @param  hperh: TIMER handle
  * @retval None
  */
void ald_timer_hall_sensor_stop_by_it(timer_handle_t *hperh)
{
	assert_param(IS_TIMER_XOR_INSTANCE(hperh->perh));

	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, DISABLE);
	ald_timer_interrupt_config(hperh, TIMER_IT_CC1, DISABLE);
	TIMER_DISABLE(hperh);

	return;
}

#ifdef ALD_DMA
/**
  * @brief  Starts the TIMER hall sensor interface in DMA mode.
  * @param  hperh: TIMER handle
  * @param  buf: The destination Buffer address. Reading data from CCR1.
  * @param  len: The length of buffer to be transferred TIMER peripheral to memory
  * @param  dma_ch: Channel of DMA.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_hall_sensor_start_by_dma(timer_handle_t *hperh, 
		                       uint16_t *buf, uint32_t len, uint8_t dma_ch)
{
	assert_param(IS_TIMER_XOR_INSTANCE(hperh->perh));

	if ((hperh->state == TIMER_STATE_BUSY))
		 return BUSY;
	if ((hperh->state == TIMER_STATE_READY)) {
		if (((uint32_t)buf == 0) ||  (len == 0))
			return ERROR;
	}

	if (hperh->hdma1.perh == NULL)
		hperh->hdma1.perh = DMA0;

	hperh->state   = TIMER_STATE_BUSY;
	hperh->hdma1.cplt_cbk = timer_dma_capture_cplt;
	hperh->hdma1.cplt_arg = (void *)hperh;
	hperh->hdma1.err_cbk  = timer_dma_error;
	hperh->hdma1.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdma1.config);
	hperh->hdma1.config.size       = len;
	hperh->hdma1.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdma1.config.src_inc    = DMA_DATA_INC_NONE;
	hperh->hdma1.config.dst_inc    = DMA_DATA_INC_HALFWORD;

	timer_dma_msel(hperh->perh, &hperh->hdma1.config);

	hperh->hdma1.config.src     = (void *)&hperh->perh->CCVAL1;
	hperh->hdma1.config.dst     = (void *)buf;
	hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH1;
	hperh->hdma1.config.channel = dma_ch;
	ald_dma_config_basic(&hperh->hdma1);
	ald_timer_dma_req_config(hperh, TIMER_DMA_CC1, ENABLE);
	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, ENABLE);
	TIMER_ENABLE(hperh);

	return OK;
}
/**
  * @brief  Stops the TIMER hall sensor interface in DMA mode.
  * @param  hperh: TIMER handle
  * @retval None
  */
void ald_timer_hall_sensor_stop_by_dma(timer_handle_t *hperh)
{
	assert_param(IS_TIMER_XOR_INSTANCE(hperh->perh));

	ald_timer_dma_req_config(hperh, TIMER_DMA_CC1, DISABLE);
	timer_ccx_channel_cmd(hperh->perh, TIMER_CHANNEL_1, DISABLE);
	TIMER_DISABLE(hperh);

	return;
}
#endif
/**
  * @}
  */

/** @defgroup TIMER_Public_Functions_Group8 TIMER complementary output compare functions
  * @brief    TIMER complementary output compare functions
  *
  * @verbatim
	==============================================================================
	##### Time complementary output compare functions #####
	==============================================================================
	[..]
		This section provides functions allowing to:
		(+) Start the Time complementary output compare.
		(+) Stop the Time complementary output compare.
		(+) Start the Time complementary output compare and enable interrupt.
		(+) Stop the Time complementary output compare and disable interrupt.
		(+) Start the Time complementary output compare and enable DMA transfer.
		(+) Stop the Time complementary output compare and disable DMA transfer.

  * @endverbatim
  * @{
  */

/**
  * @brief  Starts the TIMER output compare signal generation on the complementary output.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  * @retval None
  */
void ald_timer_ocn_start(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCXN_INSTANCE(hperh->perh, ch));

	timer_ccxn_channel_cmd(hperh->perh, ch, ENABLE);
	TIMER_MOE_ENABLE(hperh);
	TIMER_ENABLE(hperh);

	return;
}

/**
  * @brief  Stops the TIMER output compare signal generation on the complementary output.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  * @retval None
  */
void ald_timer_ocn_stop(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCXN_INSTANCE(hperh->perh, ch));

	timer_ccxn_channel_cmd(hperh->perh, ch, DISABLE);
	TIMER_MOE_DISABLE(hperh);
	TIMER_DISABLE(hperh);

	return;
}

/**
  * @brief  Starts the TIMER output compare signal generation on the complementary output.
  *         in interrupt mode
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  * @retval None
  */
void ald_timer_ocn_start_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCXN_INSTANCE(hperh->perh, ch));

	switch (ch) {
	case TIMER_CHANNEL_1:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC1, ENABLE);
		break;

	case TIMER_CHANNEL_2:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC2, ENABLE);
		break;

	case TIMER_CHANNEL_3:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC3, ENABLE);
		break;
	default:
		break;
	}

	ald_timer_interrupt_config(hperh, TIMER_IT_BREAK, ENABLE);
	timer_ccxn_channel_cmd(hperh->perh, ch, ENABLE);
	TIMER_MOE_ENABLE(hperh);
	TIMER_ENABLE(hperh);

	return;
}

/**
  * @brief  Stops the TIMER output compare signal generation on the complementary output.
  *         in interrupt mode
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  * @retval None
  */
void ald_timer_ocn_stop_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCXN_INSTANCE(hperh->perh, ch));

	switch (ch) {
	case TIMER_CHANNEL_1:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC1, DISABLE);
		break;

	case TIMER_CHANNEL_2:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC2, DISABLE);
		break;

	case TIMER_CHANNEL_3:
		ald_timer_interrupt_config(hperh, TIMER_IT_CC3, DISABLE);
		break;
	default:
		break;
	}

	if ((!(READ_BIT(hperh->perh->CCEP, TIMER_CCEP_CC1NEN_MSK)))
			&& (!(READ_BIT(hperh->perh->CCEP, TIMER_CCEP_CC2NEN_MSK)))
			&& (!(READ_BIT(hperh->perh->CCEP, TIMER_CCEP_CC3NEN_MSK)))) {
		ald_timer_interrupt_config(hperh, TIMER_IT_BREAK, DISABLE);
	}

	timer_ccxn_channel_cmd(hperh->perh, ch, DISABLE);
	TIMER_MOE_DISABLE(hperh);
	TIMER_DISABLE(hperh);

	return;
}

#ifdef ALD_DMA
/**
  * @brief  Starts the TIMER output compare signal generation on the complementary output.
  *         in DMA mode
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  * @param  buf: The destination Buffer address. Reading data from CCRx.
  * @param  len: The length of buffer to be transferred TIMER peripheral to memory
  * @param  dma_ch: Channel of DMA.
  * @retval None
  */
ald_status_t ald_timer_ocn_start_by_dma(timer_handle_t *hperh, 
		          timer_channel_t ch, uint16_t *buf, uint32_t len, uint8_t dma_ch)
{
	assert_param(IS_TIMER_CCXN_INSTANCE(hperh->perh, ch));

	if ((hperh->state == TIMER_STATE_BUSY))
		 return BUSY;
	if ((hperh->state == TIMER_STATE_READY)) {
		if (((uint32_t)buf == 0 ) || (len == 0))
			return ERROR;
	}

	hperh->state   = TIMER_STATE_BUSY;

	if (hperh->hdma1.perh == NULL)
		hperh->hdma1.perh = DMA0;

	hperh->hdma1.cplt_cbk = timer_dma_oc_cplt;
	hperh->hdma1.cplt_arg = (void *)hperh;
	hperh->hdma1.err_cbk  = timer_dma_error;
	hperh->hdma1.err_arg  = (void *)hperh;

	ald_dma_config_struct(&hperh->hdma1.config);
	hperh->hdma1.config.src        = (void *)buf;
	hperh->hdma1.config.size       = len;
	hperh->hdma1.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdma1.config.src_inc    = DMA_DATA_INC_HALFWORD;
	hperh->hdma1.config.dst_inc    = DMA_DATA_INC_NONE;
	hperh->hdma1.config.channel    = dma_ch;
	hperh->hdma1.config.msel       = DMA_MSEL_TIMER0;

	switch (ch) {
	case TIMER_CHANNEL_1:
		hperh->hdma1.config.dst     = (void *)&hperh->perh->CCVAL1;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH1;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC1, ENABLE);
		hperh->ch = TIMER_ACTIVE_CHANNEL_1;
		break;

	case TIMER_CHANNEL_2:
		hperh->hdma1.config.dst     = (void *)&hperh->perh->CCVAL2;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH2;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC2, ENABLE);
		hperh->ch = TIMER_ACTIVE_CHANNEL_2;
		break;

	case TIMER_CHANNEL_3:
		hperh->hdma1.config.dst     = (void *)&hperh->perh->CCVAL3;
		hperh->hdma1.config.msigsel = DMA_MSIGSEL_TIMER_CH3;
		ald_dma_config_basic(&hperh->hdma1);
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC3, ENABLE);
		hperh->ch = TIMER_ACTIVE_CHANNEL_3;
		break;

	default:
		break;
	}

	timer_ccx_channel_cmd(hperh->perh, ch, ENABLE);
	TIMER_MOE_ENABLE(hperh);
	TIMER_ENABLE(hperh);

	return OK;
}

/**
  * @brief  Starts the TIMER output compare signal generation on the complementary output.
  *         in DMA mode
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  * @retval None
  */
void ald_timer_ocn_stop_by_dma(timer_handle_t *hperh, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCXN_INSTANCE(hperh->perh, ch));

	switch (ch) {
	case TIMER_CHANNEL_1:
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC1, DISABLE);
		break;

	case TIMER_CHANNEL_2:
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC2, DISABLE);
		break;

	case TIMER_CHANNEL_3:
		ald_timer_dma_req_config(hperh, TIMER_DMA_CC3, DISABLE);
		break;
	default:
		break;
	}

	timer_ccxn_channel_cmd(hperh->perh, ch, DISABLE);
	TIMER_MOE_DISABLE(hperh);
	TIMER_DISABLE(hperh);

	return;
}
#endif
/**
  * @}
  */

/** @defgroup TIMER_Public_Functions_Group9 TIMER complementary PWM functions
  * @brief    TIMER complementary PWM functions
  *
  * @verbatim
	==============================================================================
	##### Time complementary PWM functions #####
	==============================================================================
	[..]
		This section provides functions allowing to:
		(+) Start the Time complementary PWM.
		(+) Stop the Time complementary PWM.
		(+) Start the Time complementary PWM and enable interrupt.
		(+) Stop the Time complementary PWM and disable interrupt.
		(+) Start the Time complementary PWM and enable DMA transfer.
		(+) Stop the Time complementary PWM and disable DMA transfer.

  * @endverbatim
  * @{
  */

/**
  * @brief  Starts the TIMER PWM signal generation on the complementary output.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  * @retval None
  */
void ald_timer_pwmn_start(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_ocn_start(hperh, ch);
}

/**
  * @brief  Stops the TIMER PWM signal generation on the complementary output.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  * @retval None
  */
void ald_timer_pwmn_stop(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_ocn_stop(hperh, ch);
}

/**
  * @brief  Starts the TIMER PWM signal generation on the complementary output.
  *         in interrupt mode
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  * @retval None
  */
void ald_timer_pwmn_start_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_ocn_start_by_it(hperh, ch);
}

/**
  * @brief  Stops the TIMER PWM signal generation on the complementary output.
  *         in interrupt mode
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  * @retval None
  */
void ald_timer_pwmn_stop_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_ocn_stop_by_it(hperh, ch);
}

#ifdef ALD_DMA
/**
  * @brief  Starts the TIMER PWM signal generation on the complementary output.
  *         in DMA mode
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  * @param  buf: The destination Buffer address. Reading data from CCRx.
  * @param  len: The length of buffer to be transferred TIMER peripheral to memory
  * @param  dma_ch: Channel of DMA.
  * @retval None
  */
ald_status_t ald_timer_pwmn_start_by_dma(timer_handle_t *hperh, 
		          timer_channel_t ch, uint16_t *buf, uint32_t len, uint8_t dma_ch)
{
	return ald_timer_ocn_start_by_dma(hperh, ch, buf, len, dma_ch);
}

/**
  * @brief  Starts the TIMER PWM signal generation on the complementary output.
  *         in DMA mode
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  * @retval None
  */
void ald_timer_pwmn_stop_by_dma(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_ocn_stop_by_dma(hperh, ch);
}
#endif
/**
  * @}
  */

/** @defgroup TIMER_Public_Functions_Group10 TIMER complementary one pulse functions
  * @brief    TIMER complementary one pulse functions
  *
  * @verbatim
	==============================================================================
	##### Time complementary one pulse functions #####
	==============================================================================
	[..]
		This section provides functions allowing to:
		(+) Start the Time complementary one pulse.
		(+) Stop the Time complementary one pulse.
		(+) Start the Time complementary one pulse and enable interrupt.
		(+) Stop the Time complementary one pulse and disable interrupt.

  * @endverbatim
  * @{
  */

/**
  * @brief  Starts the TIMER one pulse signal generation on the complementary output.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  * @retval None
  */
void ald_timer_one_pulse_n_start(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_ocn_start(hperh, ch);
}

/**
  * @brief  Stops the TIMER one pulse signal generation on the complementary output.
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  * @retval None
  */
void ald_timer_one_pulse_n_stop(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_ocn_stop(hperh, ch);
}

/**
  * @brief  Starts the TIMER one pulse signal generation on the complementary output.
  *         in interrupt mode
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  * @retval None
  */
void ald_timer_one_pulse_n_start_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_ocn_start_by_it(hperh, ch);
}

/**
  * @brief  Stops the TIMER one pulse signal generation on the complementary output.
  *         in interrupt mode
  * @param  hperh: TIMER handle
  * @param  ch: TIMER Channels to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  * @retval None
  */
void ald_timer_one_pulse_n_stop_by_it(timer_handle_t *hperh, timer_channel_t ch)
{
	ald_timer_ocn_stop_by_it(hperh, ch);
}
/**
  * @}
  */

/** @defgroup TIMER_Public_Functions_Group11 Peripheral Control functions
 *  @brief    Peripheral Control functions
 *
 * @verbatim
  ==============================================================================
                   ##### Peripheral Control functions #####
  ==============================================================================
 [..]
   This section provides functions allowing to:
      (+) Configure The Input Output channels for OC, PWM, IC or One Pulse mode.
      (+) Configure External Clock source.
      (+) Configure Complementary channels, break features and dead timere.
      (+) Configure Master and the Slave synchronization.
      (+) Handle TIMER interrupt.
      (+) Get TIMER compare register's vale.
      (+) Configure TIMER interrupt ENABLE/DISABLE.
      (+) Get TIMER interrupt source status.
      (+) Get TIMER interrupt flag status.
      (+) Clear TIMER interrupt flag.

    @endverbatim
  * @{
  */
/**
  * @brief  Initializes the TIMER Output Compare Channels according to the specified
  *         parameters in the timer_oc_init_t.
  * @param  hperh: TIMER handle
  * @param  config: TIMER Output Compare configuration structure
  * @param  ch: TIMER Channels to be enabled
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_oc_config_channel(timer_handle_t *hperh, timer_oc_init_t* config, timer_channel_t ch)
{
	assert_param(IS_TIMER_CCX_INSTANCE(hperh->perh, ch));
	assert_param(IS_TIMER_OC_MODE(config->oc_mode));
	assert_param(IS_TIMER_OC_POLARITY(config->oc_polarity));

	__LOCK(hperh);
	hperh->state = TIMER_STATE_BUSY;

	switch (ch) {
	case TIMER_CHANNEL_1:
		timer_oc1_set_config(hperh->perh, config);
		break;

	case TIMER_CHANNEL_2:
		timer_oc2_set_config(hperh->perh, config);
		break;

	case TIMER_CHANNEL_3:
		timer_oc3_set_config(hperh->perh, config);
		break;

	case TIMER_CHANNEL_4:
		timer_oc4_set_config(hperh->perh, config);
		break;

	default:
		break;
	}

	hperh->state = TIMER_STATE_READY;
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Initializes the TIMER Input Capture Channels according to the specified
  *         parameters in the timer_ic_init_t.
  * @param  hperh: TIMER handle
  * @param  config: TIMER Input Capture configuration structure
  * @param  ch: TIMER Channels to be enabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3 selected
  *            @arg TIMER_CHANNEL_4: TIMER Channel 4 selected
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_ic_config_channel(timer_handle_t *hperh, timer_ic_init_t* config, timer_channel_t ch)
{
	assert_param(IS_TIMER_CC2_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_IC_POLARITY(config->polarity));
	assert_param(IS_TIMER_IC_SELECT(config->sel));
	assert_param(IS_TIMER_IC_PSC(config->psc));
	assert_param(IS_TIMER_IC_FILTER(config->filter));

	__LOCK(hperh);
	hperh->state = TIMER_STATE_BUSY;

	switch (ch) {
	case TIMER_CHANNEL_1:
		timer_ti1_set_config(hperh->perh, config->polarity, config->sel, config->filter);
		MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_IC1PRES_MSK, config->psc << TIMER_CHMR1_IC1PRES_POSS);
		break;

	case TIMER_CHANNEL_2:
		timer_ti2_set_config(hperh->perh, config->polarity, config->sel, config->filter);
		MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_IC2PRES_MSK, config->psc << TIMER_CHMR1_IC2PRES_POSS);
		break;

	case TIMER_CHANNEL_3:
		timer_ti3_set_config(hperh->perh, config->polarity, config->sel, config->filter);
		MODIFY_REG(hperh->perh->CHMR2, TIMER_CHMR2_IC3PRES_MSK, config->psc << TIMER_CHMR2_IC3PRES_POSS);
		break;

	case TIMER_CHANNEL_4:
		timer_ti4_set_config(hperh->perh, config->polarity, config->sel, config->filter);
		MODIFY_REG(hperh->perh->CHMR2, TIMER_CHMR2_IC4PRES_MSK, config->psc << TIMER_CHMR2_IC4PRES_POSS);
		break;

	default:
		break;
	}

	hperh->state = TIMER_STATE_READY;
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Initializes the TIMER One Pulse Channels according to the specified
  *         parameters in the timer_one_pulse_init_t.
  * @param  hperh: TIMER handle
  * @param  config: TIMER One Pulse configuration structure
  * @param  ch_out: TIMER Channels to be enabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  * @param  ch_in: TIMER Channels to be enabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2 selected
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_one_pulse_config_channel(timer_handle_t *hperh, timer_one_pulse_init_t *config,
                                                   timer_channel_t ch_out,  timer_channel_t ch_in)
{
	timer_oc_init_t tmp;

	assert_param(IS_TIMER_CC2_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_OC_MODE(config->mode));
	assert_param(IS_TIMER_OC_POLARITY(config->oc_polarity));
	assert_param(IS_TIMER_OCN_POLARITY(config->ocn_polarity));
	assert_param(IS_TIMER_OCIDLE_STATE(config->oc_idle));
	assert_param(IS_TIMER_OCNIDLE_STATE(config->ocn_idle));
	assert_param(IS_TIMER_IC_POLARITY(config->polarity));
	assert_param(IS_TIMER_IC_SELECT(config->sel));
	assert_param(IS_TIMER_IC_FILTER(config->filter));

	if (ch_out == ch_in)
		return ERROR;

	__LOCK(hperh);
	hperh->state = TIMER_STATE_BUSY;

	tmp.oc_mode        = config->mode;
	tmp.pulse          = config->pulse;
	tmp.oc_polarity    = config->oc_polarity;
	tmp.ocn_polarity   = config->ocn_polarity;
	tmp.oc_idle  = config->oc_idle;
	tmp.ocn_idle = config->ocn_idle;

	switch (ch_out) {
	case TIMER_CHANNEL_1:
		timer_oc1_set_config(hperh->perh, &tmp);
		break;
	case TIMER_CHANNEL_2:
		timer_oc2_set_config(hperh->perh, &tmp);
		break;
	default:
		break;
	}

	switch (ch_in) {
	case TIMER_CHANNEL_1:
		timer_ti1_set_config(hperh->perh, config->polarity, config->sel, config->filter);
		CLEAR_BIT(hperh->perh->CHMR1, TIMER_CHMR1_IC1PRES_MSK);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_TI1FP1 << TIMER_SMCON_TSSEL_POSS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_TRIG << TIMER_SMCON_SMODS_POSS);
		break;

	case TIMER_CHANNEL_2:
		timer_ti2_set_config(hperh->perh, config->polarity, config->sel, config->filter);
		CLEAR_BIT(hperh->perh->CHMR1, TIMER_CHMR1_IC2PRES_MSK);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_TI2FP2 << TIMER_SMCON_TSSEL_POSS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_TRIG << TIMER_SMCON_SMODS_POSS);
		break;
	default:
		break;
	}

	hperh->state = TIMER_STATE_READY;
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Configures the OCRef clear feature
  * @param  hperh: TIMER handle
  * @param  config: pointer to a TIMER_ClearInputConfigTypeDef structure that
  *         contains the OCREF clear feature and parameters for the TIMER peripheral.
  * @param  ch: specifies the TIMER Channel
  *         This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1: TIMER Channel 1
  *            @arg TIMER_CHANNEL_2: TIMER Channel 2
  *            @arg TIMER_CHANNEL_3: TIMER Channel 3
  *            @arg TIMER_CHANNEL_4: TIMER Channel 4
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_config_oc_ref_clear(timer_handle_t *hperh, timer_clear_input_config_t *config, timer_channel_t ch)
{
	assert_param(IS_TIMER_CC2_INSTANCE(hperh->perh));
	assert_param(IS_FUNC_STATE(config->state));
	assert_param(IS_TIMER_CLEAR_INPUT_SOURCE(config->source));
	assert_param(IS_TIMER_CLEAR_INPUT_POLARITY(config->polarity));
	assert_param(IS_TIMER_ETR_PSC(config->psc));
	assert_param(IS_TIMER_IC_FILTER(config->filter));

	if (config->source == TIMER_INPUT_NONE) {
		timer_etr_set_config(hperh->perh, TIMER_ETR_PSC_DIV1, TIMER_CLK_POLARITY_NO_INV, 0);
	}
	else {
		timer_etr_set_config(hperh->perh, config->psc,
				(timer_clock_polarity_t)config->polarity, config->filter);
	}

	switch (ch) {
	case TIMER_CHANNEL_1:
		MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_CH1OCLREN_MSK, config->state << TIMER_CHMR1_CH1OCLREN_POS);
		break;

	case TIMER_CHANNEL_2:
		MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_CH2OCLREN_MSK, config->state << TIMER_CHMR1_CH2OCLREN_POS);
		break;

	case TIMER_CHANNEL_3:
		assert_param(IS_TIMER_CC4_INSTANCE(hperh->perh));
		MODIFY_REG(hperh->perh->CHMR2, TIMER_CHMR2_CH3OCLREN_MSK, config->state << TIMER_CHMR2_CH3OCLREN_POS);
		break;

	case TIMER_CHANNEL_4:
		assert_param(IS_TIMER_CC4_INSTANCE(hperh->perh));
		MODIFY_REG(hperh->perh->CHMR2, TIMER_CHMR2_CH4OCLREN_MSK, config->state << TIMER_CHMR2_CH4OCLREN_POS);
		break;

	default:
		break;
	}

	return OK;
}

/**
  * @brief  Configures the clock source to be used
  * @param  hperh: TIMER handle
  * @param  config: pointer to a timer_clock_config_t structure that
  *         contains the clock source information for the TIMER peripheral.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_config_clock_source(timer_handle_t *hperh, timer_clock_config_t *config)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_CLOCK_SOURCE(config->source));
	assert_param(IS_TIMER_CLOCK_POLARITY(config->polarity));
	assert_param(IS_TIMER_ETR_PSC(config->psc));
	assert_param(IS_TIMER_IC_FILTER(config->filter));

	__LOCK(hperh);
	hperh->state = TIMER_STATE_BUSY;
	WRITE_REG(hperh->perh->SMCON, 0x0);

	switch (config->source) {
	case TIMER_SRC_INTER:
		CLEAR_BIT(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK);
		break;

	case TIMER_SRC_ETRMODE1:
		timer_etr_set_config(hperh->perh, config->psc, config->polarity, config->filter);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_ETRF << TIMER_SMCON_TSSEL_POSS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_EXTERNAL1 << TIMER_SMCON_SMODS_POSS);
		break;

	case TIMER_SRC_ETRMODE2:
		timer_etr_set_config(hperh->perh, config->psc, config->polarity, config->filter);
		SET_BIT(hperh->perh->SMCON, TIMER_SMCON_ECM2EN_MSK);
		break;

	case TIMER_SRC_TI1:
		timer_ti1_set_config_stage(hperh->perh, (timer_ic_polarity_t)config->polarity, config->filter);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_TI1FP1 << TIMER_SMCON_TSSEL_POSS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_EXTERNAL1 << TIMER_SMCON_SMODS_POSS);
		break;

	case TIMER_SRC_TI2:
		timer_ti2_set_config_stage(hperh->perh, (timer_ic_polarity_t)config->polarity, config->filter);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_TI2FP2 << TIMER_SMCON_TSSEL_POSS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_EXTERNAL1 << TIMER_SMCON_SMODS_POSS);
		break;

	case TIMER_SRC_TI1ED:
		timer_ti1_set_config_stage(hperh->perh, (timer_ic_polarity_t)config->polarity, config->filter);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_TI1F_ED << TIMER_SMCON_TSSEL_POSS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_EXTERNAL1 << TIMER_SMCON_SMODS_POSS);
		break;

	case TIMER_SRC_ITR0:
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_ITR0 << TIMER_SMCON_TSSEL_POSS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_EXTERNAL1 << TIMER_SMCON_SMODS_POSS);
		break;

	case TIMER_SRC_ITR1:
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_ITR1 << TIMER_SMCON_TSSEL_POSS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_EXTERNAL1 << TIMER_SMCON_SMODS_POSS);
		break;

	case TIMER_SRC_ITR2:
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_ITR2 << TIMER_SMCON_TSSEL_POSS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_EXTERNAL1 << TIMER_SMCON_SMODS_POSS);
		break;

	case TIMER_SRC_ITR3:
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, TIMER_TS_ITR3 << TIMER_SMCON_TSSEL_POSS);
		MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, TIMER_MODE_EXTERNAL1 << TIMER_SMCON_SMODS_POSS);
		break;
	default:
		break;
	}

	hperh->state = TIMER_STATE_READY;
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Selects the signal connected to the TI1 input: direct from CH1_input
  *         or a XOR combination between CH1_input, CH2_input & CH3_input
  * @param  hperh: TIMER handle.
  * @param  ti1_select: Indicate whether or not channel 1 is connected to the
  *         output of a XOR gate.
  *         This parameter can be one of the following values:
  *            @arg 0: The TIMERx_CH1 pin is connected to TI1 input
  *            @arg 1: The TIMERx_CH1, CH2 and CH3
  *            pins are connected to the TI1 input (XOR combination)
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_config_ti1_input(timer_handle_t *hperh, uint32_t ti1_select)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));

	MODIFY_REG(hperh->perh->CON2, TIMER_CON2_I1FSEL_MSK, ti1_select << TIMER_CON2_I1FSEL_POS);
	return OK;
}

/**
  * @brief  Configures the TIMER in Slave mode
  * @param  hperh: TIMER handle.
  * @param  config: pointer to a timer_slave_config_t structure that
  *         contains the selected trigger (internal trigger input, filtered
  *         timerer input or external trigger input) and the Slave
  *         mode (Disable, Reset, Gated, Trigger, External clock mode 1).
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_slave_config_sync(timer_handle_t *hperh, timer_slave_config_t *config)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_SLAVE_MODE(config->mode));
	assert_param(IS_TIMER_TS(config->input));
	assert_param(IS_TIMER_CLOCK_POLARITY(config->polarity));
	assert_param(IS_TIMER_ETR_PSC(config->psc));
	assert_param(IS_TIMER_IC_FILTER(config->filter));

	__LOCK(hperh);
	hperh->state = TIMER_STATE_BUSY;

	timer_slave_set_config(hperh, config);
	ald_timer_interrupt_config(hperh, TIMER_IT_TRIGGER, DISABLE);
	ald_timer_dma_req_config(hperh, TIMER_DMA_TRIGGER, DISABLE);

	hperh->state = TIMER_STATE_READY;
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Configures the TIMER in Slave mode in interrupt mode
  * @param  hperh: TIMER handle.
  * @param  config: pointer to a timer_slave_config_t structure that
  *         contains the selected trigger (internal trigger input, filtered
  *         timerer input or external trigger input) and the ) and the Slave
  *         mode (Disable, Reset, Gated, Trigger, External clock mode 1).
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_slave_config_sync_by_it(timer_handle_t *hperh, timer_slave_config_t *config)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_SLAVE_MODE(config->mode));
	assert_param(IS_TIMER_TS(config->input));
	assert_param(IS_TIMER_CLOCK_POLARITY(config->polarity));
	assert_param(IS_TIMER_ETR_PSC(config->psc));
	assert_param(IS_TIMER_IC_FILTER(config->filter));

	__LOCK(hperh);
	hperh->state = TIMER_STATE_BUSY;

	timer_slave_set_config(hperh, config);
	ald_timer_interrupt_config(hperh, TIMER_IT_TRIGGER, ENABLE);
	ald_timer_dma_req_config(hperh, TIMER_DMA_TRIGGER, DISABLE);

	hperh->state = TIMER_STATE_READY;
	__UNLOCK(hperh);
	return OK;
}

/**
  * @brief  Generate a software event
  * @param  hperh: TIMER handle
  * @param  event: specifies the event source.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_timer_generate_event(timer_handle_t *hperh, timer_event_source_t event)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_EVENT_SOURCE(event));

	__LOCK(hperh);
	hperh->state          = TIMER_STATE_BUSY;
	WRITE_REG(hperh->perh->SGE, event);
	hperh->state          = TIMER_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Read the captured value from Capture Compare unit
  * @param  hperh: TIMER handle.
  * @param  ch: TIMER Channels to be enabled
  *         This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1 : TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2 : TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3 : TIMER Channel 3 selected
  *            @arg TIMER_CHANNEL_4 : TIMER Channel 4 selected
  * @retval Captured value
  */
uint32_t ald_timer_read_capture_value(timer_handle_t *hperh, timer_channel_t ch)
{
	uint32_t tmp;

	__LOCK(hperh);
	hperh->state = TIMER_STATE_BUSY;

	switch (ch) {
	case TIMER_CHANNEL_1:
		tmp = hperh->perh->CCVAL1;
		break;
	case TIMER_CHANNEL_2:
		tmp = hperh->perh->CCVAL2;
		break;
	case TIMER_CHANNEL_3:
		tmp = hperh->perh->CCVAL3;
		break;
	case TIMER_CHANNEL_4:
		tmp = hperh->perh->CCVAL4;
		break;
	default:
		tmp = hperh->perh->CCVAL1;
		break;
	}

	hperh->state = TIMER_STATE_READY;
	__UNLOCK(hperh);
	return tmp;
}

/**
  * @brief  Sets TIMER output mode.
  * @param  hperh: TIMER handle.
  * @param  mode: TIMER output mode.
  * @param  ch: TIMER Channels.
  *         This parameter can be one of the following values:
  *            @arg TIMER_CHANNEL_1 : TIMER Channel 1 selected
  *            @arg TIMER_CHANNEL_2 : TIMER Channel 2 selected
  *            @arg TIMER_CHANNEL_3 : TIMER Channel 3 selected
  *            @arg TIMER_CHANNEL_4 : TIMER Channel 4 selected
  * @retval None
  */
void ald_timer_set_output_mode(timer_handle_t *hperh, timer_oc_mode_t mode, timer_channel_t ch)
{
	assert_param(IS_TIMER_CC2_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_OC_MODE(mode));
	assert_param(IS_TIMER_CHANNELS(ch));

	switch (ch) {
	case TIMER_CHANNEL_1:
		MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_CH1OMOD_MSK, mode << TIMER_CHMR1_CH1OMOD_POSS);
		break;
	case TIMER_CHANNEL_2:
		MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_CH2OMOD_MSK, mode << TIMER_CHMR1_CH2OMOD_POSS);
		break;
	case TIMER_CHANNEL_3:
		MODIFY_REG(hperh->perh->CHMR2, TIMER_CHMR2_CH3OMOD_MSK, mode << TIMER_CHMR2_CH3OMOD_POSS);
		break;
	case TIMER_CHANNEL_4:
		MODIFY_REG(hperh->perh->CHMR2, TIMER_CHMR2_CH4OMOD_MSK, mode << TIMER_CHMR2_CH4OMOD_POSS);
		break;
	default:
		break;
	}

	return;
}

/**
  * @brief  Configure the channel in commutation event.
  * @param  hperh: TIMER handel
  * @param  config: Parameters of the channel.
  * @retval None
  */ 
void ald_timer_com_change_config(timer_handle_t *hperh, timer_com_channel_config_t *config)
{
	uint32_t cm1, cm2, cce;

	assert_param(IS_TIMER_COM_EVENT_INSTANCE(hperh->perh));
	assert_param(IS_FUNC_STATE(config->ch[0].en));
	assert_param(IS_FUNC_STATE(config->ch[0].n_en));
	assert_param(IS_TIMER_OC_MODE(config->ch[0].mode));
	assert_param(IS_FUNC_STATE(config->ch[1].en));
	assert_param(IS_FUNC_STATE(config->ch[1].n_en));
	assert_param(IS_TIMER_OC_MODE(config->ch[1].mode));
	assert_param(IS_FUNC_STATE(config->ch[2].en));
	assert_param(IS_FUNC_STATE(config->ch[2].n_en));
	assert_param(IS_TIMER_OC_MODE(config->ch[2].mode));

	TIMER_MOE_DISABLE(hperh);
	TIMER_DISABLE(hperh);

	cm1 = hperh->perh->CHMR1;
	cm2 = hperh->perh->CHMR2;
	cce = hperh->perh->CCEP;

	MODIFY_REG(cm1, (0x7 << 4), (config->ch[0].mode << 4));
	MODIFY_REG(cm1, (0x7 << 12), (config->ch[1].mode << 12));
	MODIFY_REG(cm2, (0x7 << 4), (config->ch[2].mode << 4));
	MODIFY_REG(cce, (0x1 << 0), (config->ch[0].en << 0));
	MODIFY_REG(cce, (0x1 << 2), (config->ch[0].n_en << 2));
	MODIFY_REG(cce, (0x1 << 4), (config->ch[1].en << 4));
	MODIFY_REG(cce, (0x1 << 6), (config->ch[1].n_en << 6));
	MODIFY_REG(cce, (0x1 << 8), (config->ch[2].en << 8));
	MODIFY_REG(cce, (0x1 << 10), (config->ch[2].n_en << 10));

	WRITE_REG(hperh->perh->CHMR1, cm1);
	WRITE_REG(hperh->perh->CHMR2, cm2);
	WRITE_REG(hperh->perh->CCEP, cce);

	TIMER_MOE_ENABLE(hperh);
	TIMER_ENABLE(hperh);
	return;
}

/**
  * @brief  Configure the TIMER commutation event sequence.
  * @param  hperh: TIMER handel
  * @param  ts: the internal trigger corresponding to the timerer interfacing
  *         with the hall sensor.
  *         This parameter can be one of the following values:
  *           @arg TIMER_TS_ITR0
  *           @arg TIMER_TS_ITR1
  *           @arg TIMER_TS_ITR2
  *           @arg TIMER_TS_ITR3
  * @param  trgi: the commutation event source.
  *         This parameter can be one of the following values:
  *           @arg ENABLE: Commutation event source is TRGI
  *           @arg DISABLE: Commutation event source is set by software using the COMG bit
  * @retval None
  */ 
void ald_timer_com_event_config(timer_handle_t *hperh, timer_ts_t ts, type_func_t trgi)
{
	assert_param(IS_TIMER_COM_EVENT_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_TS(ts));
	assert_param(IS_FUNC_STATE(trgi));

	MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, ts << TIMER_SMCON_TSSEL_POSS);
	SET_BIT(hperh->perh->CON2, TIMER_CON2_CCPCEN_MSK);
	MODIFY_REG(hperh->perh->CON2, TIMER_CON2_CCUSEL_MSK, trgi << TIMER_CON2_CCUSEL_POS);

	return;
}

/**
  * @brief  Configure the TIMER commutation event sequence with interrupt.
  * @param  hperh: TIMER handel
  * @param  ts: the internal trigger corresponding to the timerer interfacing
  *         with the hall sensor.
  *         This parameter can be one of the following values:
  *           @arg TIMER_TS_ITR0
  *           @arg TIMER_TS_ITR1
  *           @arg TIMER_TS_ITR2
  *           @arg TIMER_TS_ITR3
  * @param  trgi: the commutation event source.
  *         This parameter can be one of the following values:
  *           @arg ENABLE: Commutation event source is TRGI
  *           @arg DISABLE: Commutation event source is set by software using the COMG bit
  * @retval None
  */
void ald_timer_com_event_config_it(timer_handle_t *hperh, timer_ts_t ts, type_func_t trgi)
{
	ald_timer_com_event_config(hperh, ts, trgi);
	ald_timer_interrupt_config(hperh, TIMER_IT_COM, ENABLE);
}

/**
  * @brief  Configure the break, dead timere, lock level state.
  * @param  hperh: TIMER handle
  * @param  config: Pointer to the timer_break_dead_timere_t structure.
  * @retval None
  */ 
void ald_timer_break_dead_time_config(timer_handle_t *hperh, timer_break_dead_time_t *config)
{
	uint32_t tmp;

	assert_param(IS_TIMER_BREAK_INSTANCE(hperh->perh));
	assert_param(IS_FUNC_STATE(config->off_run));
	assert_param(IS_FUNC_STATE(config->off_idle));
	assert_param(IS_TIMER_CLOCK_LEVEL(config->lock_level));
	assert_param(IS_TIMER_DEAD_TIMERE(config->dead_time));
	assert_param(IS_FUNC_STATE(config->break_state));
	assert_param(IS_TIMER_BREAK_POLARITY(config->polarity));
	assert_param(IS_FUNC_STATE(config->auto_out));

	tmp = READ_REG(hperh->perh->BDCFG);
	MODIFY_REG(tmp, TIMER_BDCFG_OFFSSR_MSK, config->off_run << TIMER_BDCFG_OFFSSR_POS);
	MODIFY_REG(tmp, TIMER_BDCFG_OFFSSI_MSK, config->off_idle << TIMER_BDCFG_OFFSSI_POS);
	MODIFY_REG(tmp, TIMER_BDCFG_LOCKLVL_MSK, config->lock_level << TIMER_BDCFG_LOCKLVL_POSS);
	MODIFY_REG(tmp, TIMER_BDCFG_DT_MSK, config->dead_time << TIMER_BDCFG_DT_POSS);
	MODIFY_REG(tmp, TIMER_BDCFG_BRKEN_MSK, config->break_state << TIMER_BDCFG_BRKEN_POS);
	MODIFY_REG(tmp, TIMER_BDCFG_BRKP_MSK, config->polarity << TIMER_BDCFG_BRKP_POS);
	MODIFY_REG(tmp, TIMER_BDCFG_AOEN_MSK, config->auto_out << TIMER_BDCFG_AOEN_POS);
	WRITE_REG(hperh->perh->BDCFG, tmp);

	hperh->state = TIMER_STATE_READY;
	return;
}

/**
  * @brief  Configure the master mode
  * @param  hperh: TIMER handle
  * @param  config: Pointer to the timer_master_config_t structure.
  * @retval None
  */ 
void ald_timer_master_sync_config(timer_handle_t *hperh, timer_master_config_t *config)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_MASTER_MODE_SEL(config->sel));
	assert_param(IS_FUNC_STATE(config->master_en));

	hperh->state = TIMER_STATE_BUSY;
	MODIFY_REG(hperh->perh->CON2, TIMER_CON2_TRGOSEL_MSK, config->sel << TIMER_CON2_TRGOSEL_POSS);
	MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_MSCFG_MSK, config->master_en << TIMER_SMCON_MSCFG_POS);
	hperh->state = TIMER_STATE_READY;

	return;
}

/**
  * @brief  This function handles TIMER interrupts requests.
  * @param  hperh: TIMER handle
  * @retval None
  */
void ald_timer_irq_handler(timer_handle_t *hperh)
{
	uint32_t reg = hperh->perh->IFM;

	/* Capture or compare 1 event */
	if (READ_BIT(reg, TIMER_FLAG_CC1)) {
		ald_timer_clear_flag_status(hperh, TIMER_FLAG_CC1);
		hperh->ch = TIMER_ACTIVE_CHANNEL_1;

		/* Input capture event */
		if (READ_BIT(hperh->perh->CHMR1, TIMER_CHMR1_CC1SSEL_MSK)) {
			if (hperh->capture_cbk)
				hperh->capture_cbk(hperh);
		}
		else {	/* Output compare event */
			if (hperh->delay_elapse_cbk)
				hperh->delay_elapse_cbk(hperh);
			if (hperh->pwm_pulse_finish_cbk)
				hperh->pwm_pulse_finish_cbk(hperh);
		}

		hperh->ch = TIMER_ACTIVE_CHANNEL_CLEARED;
	}
	/* Capture or compare 2 event */
	if (READ_BIT(reg, TIMER_FLAG_CC2)) {
		ald_timer_clear_flag_status(hperh, TIMER_FLAG_CC2);
		hperh->ch = TIMER_ACTIVE_CHANNEL_2;

		/* Input capture event */
		if (READ_BIT(hperh->perh->CHMR1, TIMER_CHMR1_CC2SSEL_MSK)) {
			if (hperh->capture_cbk)
				hperh->capture_cbk(hperh);
		}
		else {	/* Output compare event */
			if (hperh->delay_elapse_cbk)
				hperh->delay_elapse_cbk(hperh);
			if (hperh->pwm_pulse_finish_cbk)
				hperh->pwm_pulse_finish_cbk(hperh);
		}

		hperh->ch = TIMER_ACTIVE_CHANNEL_CLEARED;
	}
	/* Capture or compare 3 event */
	if (READ_BIT(reg, TIMER_FLAG_CC3)) {
		ald_timer_clear_flag_status(hperh, TIMER_FLAG_CC3);
		hperh->ch = TIMER_ACTIVE_CHANNEL_3;

		/* Input capture event */
		if (READ_BIT(hperh->perh->CHMR2, TIMER_CHMR2_CC3SSEL_MSK)) {
			if (hperh->capture_cbk)
				hperh->capture_cbk(hperh);
		}
		else {	/* Output compare event */
			if (hperh->delay_elapse_cbk)
				hperh->delay_elapse_cbk(hperh);
			if (hperh->pwm_pulse_finish_cbk)
				hperh->pwm_pulse_finish_cbk(hperh);
		}

		hperh->ch = TIMER_ACTIVE_CHANNEL_CLEARED;
	}
	/* Capture or compare 4 event */
	if (READ_BIT(reg, TIMER_FLAG_CC4)) {
		ald_timer_clear_flag_status(hperh, TIMER_FLAG_CC4);
		hperh->ch = TIMER_ACTIVE_CHANNEL_4;

		/* Input capture event */
		if (READ_BIT(hperh->perh->CHMR2, TIMER_CHMR2_CC4SSEL_MSK)) {
			if (hperh->capture_cbk)
				hperh->capture_cbk(hperh);
		}
		else {	/* Output compare event */
			if (hperh->delay_elapse_cbk)
				hperh->delay_elapse_cbk(hperh);
			if (hperh->pwm_pulse_finish_cbk)
				hperh->pwm_pulse_finish_cbk(hperh);
		}

		hperh->ch = TIMER_ACTIVE_CHANNEL_CLEARED;
	}

	/* TIMER Update event */
	if (READ_BIT(reg, TIMER_FLAG_UPDATE)) {
		ald_timer_clear_flag_status(hperh, TIMER_FLAG_UPDATE);

		if (hperh->period_elapse_cbk)
			hperh->period_elapse_cbk(hperh);
	}

	/* TIMER Break input event */
	if (READ_BIT(reg, TIMER_FLAG_BREAK)) {
		ald_timer_clear_flag_status(hperh, TIMER_FLAG_BREAK);

		if (hperh->break_cbk)
			hperh->break_cbk(hperh);
	}

	/* TIMER Trigger detection event */
	if (READ_BIT(reg, TIMER_FLAG_TRIGGER)) {
		ald_timer_clear_flag_status(hperh, TIMER_FLAG_TRIGGER);

		if (hperh->trigger_cbk)
			hperh->trigger_cbk(hperh);
	}

	/* TIMER commutation event */
	if (READ_BIT(reg, TIMER_FLAG_COM)) {
		ald_timer_clear_flag_status(hperh, TIMER_FLAG_COM);

		if (hperh->com_cbk)
			hperh->com_cbk(hperh);
	}

	return;
}

/**
  * @brief  Configure DMA request source.
  * @param  hperh: TIMER handle
  * @param  req: DMA request source.
  * @param  state: New state of the specified DMA request.
  * @retval None
  */
void ald_timer_dma_req_config(timer_handle_t *hperh, timer_dma_req_t req, type_func_t state)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_DMA_REQ(req));
	assert_param(IS_FUNC_STATE(state));

	if (state == ENABLE)
		SET_BIT(hperh->perh->DIER, req);
	else
		SET_BIT(hperh->perh->DIDR, req);

	return;
}

/**
  * @brief  Enable/disable the specified TIMER interrupts.
  * @param  hperh: Pointer to a timer_handle_t structure.
  * @param  it: Specifies the timer interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref timer_it_t.
  * @param  state: New state of the specified TIMER interrupts.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_timer_interrupt_config(timer_handle_t *hperh, timer_it_t it, type_func_t state)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_IT(it));
	assert_param(IS_FUNC_STATE(state));

	if (state == ENABLE)
		SET_BIT(hperh->perh->DIER, it);
	else
		SET_BIT(hperh->perh->DIDR, it);

	return;
}

/**
  * @brief  Get the status of TIMER interrupt source.
  * @param  hperh: Pointer to a timer_handle_t structure.
  * @param  it: Specifies the TIMER interrupt source.
  *         This parameter can be one of the @ref timer_it_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
it_status_t ald_timer_get_it_status(timer_handle_t *hperh, timer_it_t it)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_IT(it));

	if (hperh->perh->DIVS & it)
		return SET;

	return RESET;
}

/**
  * @brief  Get the status of TIMER interrupt flag.
  * @param  hperh: Pointer to a timer_handle_t structure.
  * @param  flag: Specifies the TIMER interrupt flag.
  *         This parameter can be one of the @ref timer_flag_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_timer_get_flag_status(timer_handle_t *hperh, timer_flag_t flag)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_FLAG(flag));

	if (hperh->perh->RIF & flag)
		return SET;

	return RESET;
}

/**
  * @brief  Clear the TIMER interrupt flag.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  flag: Specifies the TIMER interrupt flag.
  *         This parameter can be one of the @ref timer_flag_t.
  * @retval None
  */
void ald_timer_clear_flag_status(timer_handle_t *hperh, timer_flag_t flag)
{
	assert_param(IS_TIMER_INSTANCE(hperh->perh));
	assert_param(IS_TIMER_FLAG(flag));

	hperh->perh->ICR = flag;
	return;
}
/**
  * @}
  */

/** @defgroup TIMER_Public_Functions_Group12 Peripheral State functions
  * @brief    Peripheral State functions
  *
  * @verbatim
  ==============================================================================
                        ##### Peripheral State functions #####
  ==============================================================================
    [..]
    This subsection permit to get in run-timere the status of the peripheral
    and the data flow.

    @endverbatim
  * @{
  */

/**
  * @brief  Return the TIMER Base state
  * @param  hperh: TIMER handle
  * @retval TIMER peripheral state
  */
timer_state_t ald_timer_get_state(timer_handle_t *hperh)
{
	return hperh->state;
}
/**
  * @}
  */
/**
  * @}
  */

/** @addtogroup TIMER_Private_Functions
  * @{
  */

#ifdef ALD_DMA
/**
  * @brief  TIMER DMA out compare complete callback.
  * @param  arg: pointer to TIMER handle.
  * @retval None
  */
void timer_dma_oc_cplt(void *arg)
{
	timer_handle_t *hperh = (timer_handle_t *)arg;

	if (hperh->delay_elapse_cbk)
		hperh->delay_elapse_cbk(hperh);

	if (hperh->pwm_pulse_finish_cbk)
		hperh->pwm_pulse_finish_cbk(hperh);

	hperh->ch = TIMER_ACTIVE_CHANNEL_CLEARED;
	return;
}

/**
  * @brief  TIMER DMA Capture complete callback.
  * @param  arg: pointer to TIMER handle.
  * @retval None
  */
void timer_dma_capture_cplt(void *arg)
{
	timer_handle_t *hperh = (timer_handle_t *)arg;

	if (hperh->capture_cbk)
		hperh->capture_cbk(hperh);

	hperh->ch = TIMER_ACTIVE_CHANNEL_CLEARED;
	return;
}

/**
  * @brief  TIMER DMA Period Elapse complete callback.
  * @param  arg: pointer to TIMER handle.
  * @retval None
  */
void timer_dma_period_elapse_cplt(void *arg)
{
	timer_handle_t *hperh = (timer_handle_t *)arg;

	if (hperh->period_elapse_cbk)
		hperh->period_elapse_cbk(hperh);

	hperh->state = TIMER_STATE_READY;
	return;
}

/**
  * @brief  TIMER DMA error callback
  * @param  arg: pointer to TIMER handle.
  * @retval None
  */
void timer_dma_error(void *arg)
{
	timer_handle_t *hperh = (timer_handle_t *)arg;

	hperh->state = TIMER_STATE_READY;
	if (hperh->error_cbk)
		hperh->error_cbk(hperh);

	return;
}
#endif

/**
  * @brief  Time Base configuration
  * @param  TIMERx: TIMER periheral
  * @param  init: TIMER Base configuration structure
  * @retval None
  */
static void timer_base_set_config(TIMER_TypeDef *TIMERx, timer_base_init_t *init)
{
	assert_param(IS_TIMER_COUNTER_MODE(init->mode));
	assert_param(IS_TIMER_CLOCK_DIVISION(init->clk_div));

	if (init->mode == TIMER_CNT_MODE_UP || init->mode == TIMER_CNT_MODE_DOWN) {
		CLEAR_BIT(TIMERx->CON1, TIMER_CON1_CMSEL_MSK);
		MODIFY_REG(TIMERx->CON1, TIMER_CON1_DIRSEL_MSK, init->mode << TIMER_CON1_DIRSEL_POS);
	}
	else {
		MODIFY_REG(TIMERx->CON1, TIMER_CON1_CMSEL_MSK, (init->mode - 1) << TIMER_CON1_CMSEL_POSS);
	}

	if (IS_TIMER_CLOCK_DIVISION_INSTANCE(TIMERx))
		MODIFY_REG(TIMERx->CON1, TIMER_CON1_DFCKSEL_MSK, init->clk_div << TIMER_CON1_DFCKSEL_POSS);

	WRITE_REG(TIMERx->AR, init->period);
	WRITE_REG(TIMERx->PRES, init->prescaler);

	if (IS_TIMER_REPETITION_COUNTER_INSTANCE(TIMERx))
		WRITE_REG(TIMERx->REPAR, init->re_cnt);

	return;
}

/**
  * @brief  Time Ouput Compare 1 configuration
  * @param  TIMERx: Select the TIMER peripheral
  * @param  oc_config: The ouput configuration structure
  * @retval None
  */
static void timer_oc1_set_config(TIMER_TypeDef *TIMERx, timer_oc_init_t *oc_config)
{
	CLEAR_BIT(TIMERx->CCEP, TIMER_CCEP_CC1EN_MSK);
	CLEAR_BIT(TIMERx->CHMR1, TIMER_CHMR1_CH1OMOD_MSK);
	CLEAR_BIT(TIMERx->CHMR1, TIMER_CHMR1_CC1SSEL_MSK);
	MODIFY_REG(TIMERx->CHMR1, TIMER_CHMR1_CH1OMOD_MSK, oc_config->oc_mode << TIMER_CHMR1_CH1OMOD_POSS);
	MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC1POL_MSK, oc_config->oc_polarity << TIMER_CCEP_CC1POL_POS);

	if (IS_TIMER_CCXN_INSTANCE(TIMERx, TIMER_CHANNEL_1)) {
		assert_param(IS_TIMER_OCN_POLARITY(oc_config->ocn_polarity));
		MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC1NPOL_MSK, oc_config->ocn_polarity << TIMER_CCEP_CC1NPOL_POS);
		CLEAR_BIT(TIMERx->CCEP, TIMER_CCEP_CC1NEN_MSK);
	}

	if (IS_TIMER_BREAK_INSTANCE(TIMERx)) {
		assert_param(IS_TIMER_OCNIDLE_STATE(oc_config->ocn_idle));
		assert_param(IS_TIMER_OCIDLE_STATE(oc_config->oc_idle));

		MODIFY_REG(TIMERx->CON2, TIMER_CON2_OISS1_MSK, oc_config->oc_idle << TIMER_CON2_OISS1_POS);
		MODIFY_REG(TIMERx->CON2, TIMER_CON2_OISS1N_MSK, oc_config->ocn_idle << TIMER_CON2_OISS1N_POS);
	}

	WRITE_REG(TIMERx->CCVAL1, oc_config->pulse);
}

/**
  * @brief  Time Ouput Compare 2 configuration
  * @param  TIMERx: Select the TIMER peripheral
  * @param  oc_config: The ouput configuration structure
  * @retval None
  */
static void timer_oc2_set_config(TIMER_TypeDef *TIMERx, timer_oc_init_t *oc_config)
{
	CLEAR_BIT(TIMERx->CCEP, TIMER_CCEP_CC2EN_MSK);
	CLEAR_BIT(TIMERx->CHMR1, TIMER_CHMR1_CH2OMOD_MSK);
	CLEAR_BIT(TIMERx->CHMR1, TIMER_CHMR1_CC2SSEL_MSK);
	MODIFY_REG(TIMERx->CHMR1, TIMER_CHMR1_CH2OMOD_MSK, oc_config->oc_mode << TIMER_CHMR1_CH2OMOD_POSS);
	MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC2POL_MSK, oc_config->oc_polarity << TIMER_CCEP_CC2POL_POS);

	if (IS_TIMER_CCXN_INSTANCE(TIMERx, TIMER_CHANNEL_2)) {
		assert_param(IS_TIMER_OCN_POLARITY(oc_config->ocn_polarity));
		MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC2NPOL_MSK, oc_config->ocn_polarity << TIMER_CCEP_CC2NPOL_POS);
		CLEAR_BIT(TIMERx->CCEP, TIMER_CCEP_CC2NEN_MSK);
	}

	if (IS_TIMER_BREAK_INSTANCE(TIMERx)) {
		assert_param(IS_TIMER_OCNIDLE_STATE(oc_config->ocn_idle));
		assert_param(IS_TIMER_OCIDLE_STATE(oc_config->oc_idle));

		MODIFY_REG(TIMERx->CON2, TIMER_CON2_OISS2_MSK, oc_config->oc_idle << TIMER_CON2_OISS2_POS);
		MODIFY_REG(TIMERx->CON2, TIMER_CON2_OISS2N_MSK, oc_config->ocn_idle << TIMER_CON2_OISS2N_POS);
	}

	WRITE_REG(TIMERx->CCVAL2, oc_config->pulse);
}

/**
  * @brief  Time Ouput Compare 3 configuration
  * @param  TIMERx: Select the TIMER peripheral
  * @param  oc_config: The ouput configuration structure
  * @retval None
  */
static void timer_oc3_set_config(TIMER_TypeDef *TIMERx, timer_oc_init_t *oc_config)
{
	CLEAR_BIT(TIMERx->CCEP, TIMER_CCEP_CC3EN_MSK);
	CLEAR_BIT(TIMERx->CHMR2, TIMER_CHMR2_CH3OMOD_MSK);
	CLEAR_BIT(TIMERx->CHMR2, TIMER_CHMR2_CC3SSEL_MSK);
	MODIFY_REG(TIMERx->CHMR2, TIMER_CHMR2_CH3OMOD_MSK, oc_config->oc_mode << TIMER_CHMR2_CH3OMOD_POSS);
	MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC3POL_MSK, oc_config->oc_polarity << TIMER_CCEP_CC3POL_POS);

	if (IS_TIMER_CCXN_INSTANCE(TIMERx, TIMER_CHANNEL_3)) {
		assert_param(IS_TIMER_OCN_POLARITY(oc_config->ocn_polarity));
		MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC3NPOL_MSK, oc_config->ocn_polarity << TIMER_CCEP_CC3NPOL_POS);
		CLEAR_BIT(TIMERx->CCEP, TIMER_CCEP_CC3NEN_MSK);
	}

	if (IS_TIMER_BREAK_INSTANCE(TIMERx)) {
		assert_param(IS_TIMER_OCNIDLE_STATE(oc_config->ocn_idle));
		assert_param(IS_TIMER_OCIDLE_STATE(oc_config->oc_idle));

		MODIFY_REG(TIMERx->CON2, TIMER_CON2_OISS3_MSK, oc_config->oc_idle << TIMER_CON2_OISS3_POS);
		MODIFY_REG(TIMERx->CON2, TIMER_CON2_OISS3N_MSK, oc_config->ocn_idle << TIMER_CON2_OISS3N_POS);
	}

	WRITE_REG(TIMERx->CCVAL3, oc_config->pulse);
}

/**
  * @brief  Time Ouput Compare 4 configuration
  * @param  TIMERx: Select the TIMER peripheral
  * @param  oc_config: The ouput configuration structure
  * @retval None
  */
static void timer_oc4_set_config(TIMER_TypeDef *TIMERx, timer_oc_init_t *oc_config)
{
	CLEAR_BIT(TIMERx->CCEP, TIMER_CCEP_CC4EN_MSK);
	CLEAR_BIT(TIMERx->CHMR2, TIMER_CHMR2_CH4OMOD_MSK);
	CLEAR_BIT(TIMERx->CHMR2, TIMER_CHMR2_CC4SSEL_MSK);
	MODIFY_REG(TIMERx->CHMR2, TIMER_CHMR2_CH4OMOD_MSK, oc_config->oc_mode << TIMER_CHMR2_CH4OMOD_POSS);
	MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC4POL_MSK, oc_config->oc_polarity << TIMER_CCEP_CC4POL_POS);

	if (IS_TIMER_BREAK_INSTANCE(TIMERx)) {
		assert_param(IS_TIMER_OCIDLE_STATE(oc_config->oc_idle));
		MODIFY_REG(TIMERx->CON2, TIMER_CON2_OISS4_MSK, oc_config->oc_idle << TIMER_CON2_OISS4_POS);
	}

	WRITE_REG(TIMERx->CCVAL4, oc_config->pulse);
}

/**
  * @brief  Enables or disables the TIMER Capture Compare Channel x.
  * @param  TIMERx: Select the TIMER peripheral
  * @param  ch: specifies the TIMER Channel
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3
  *		@arg TIMER_CHANNEL_4: TIMER Channel 4
  * @param  state: specifies the TIMER Channel CCxE bit new state.
  * @retval None
  */
static void timer_ccx_channel_cmd(TIMER_TypeDef* TIMERx, timer_channel_t ch, type_func_t state)
{
	assert_param(IS_TIMER_CC2_INSTANCE(TIMERx));
	assert_param(IS_TIMER_CHANNELS(ch));

	switch (ch) {
	case TIMER_CHANNEL_1:
		MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC1EN_MSK, state << TIMER_CCEP_CC1EN_POS);
		break;

	case TIMER_CHANNEL_2:
		MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC2EN_MSK, state << TIMER_CCEP_CC2EN_POS);
		break;

	case TIMER_CHANNEL_3:
		MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC3EN_MSK, state << TIMER_CCEP_CC3EN_POS);
		break;

	case TIMER_CHANNEL_4:
		MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC4EN_MSK, state << TIMER_CCEP_CC4EN_POS);
		break;

	default:
		break;
	}
}
/**
  * @brief  Enables or disables the TIMER Capture Compare Channel xN.
  * @param  TIMERx: Select the TIMER peripheral
  * @param  ch: specifies the TIMER Channel
  *		This parameter can be one of the following values:
  *		@arg TIMER_CHANNEL_1: TIMER Channel 1
  *		@arg TIMER_CHANNEL_2: TIMER Channel 2
  *		@arg TIMER_CHANNEL_3: TIMER Channel 3
  * @param  state: specifies the TIMER Channel CCxNE bit new state.
  * @retval None
  */
static void timer_ccxn_channel_cmd(TIMER_TypeDef* TIMERx, timer_channel_t ch, type_func_t state)
{
	switch (ch) {
	case TIMER_CHANNEL_1:
		MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC1NEN_MSK, state << TIMER_CCEP_CC1NEN_POS);
		break;

	case TIMER_CHANNEL_2:
		MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC2NEN_MSK, state << TIMER_CCEP_CC2NEN_POS);
		break;

	case TIMER_CHANNEL_3:
		MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC3NEN_MSK, state << TIMER_CCEP_CC3NEN_POS);
		break;

	default:
		break;
	}

}

/**
  * @brief  Configure the TI1 as Input.
  * @param  TIMERx: Select the TIMER peripheral.
  * @param  polarity: The Input Polarity.
  * @param  sel: specifies the input to be used.
  * @param  filter: Specifies the Input Capture Filter.
  *         This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void timer_ti1_set_config(TIMER_TypeDef *TIMERx, timer_ic_polarity_t polarity,
                                   timer_ic_select_t sel, uint32_t filter)
{
	CLEAR_BIT(TIMERx->CCEP, TIMER_CCEP_CC1EN_MSK);
	MODIFY_REG(TIMERx->CHMR1, TIMER_CHMR1_CC1SSEL_MSK, sel << TIMER_CHMR1_CC1SSEL_POSS);
	MODIFY_REG(TIMERx->CHMR1, TIMER_CHMR1_I1FLT_MSK, filter << TIMER_CHMR1_I1FLT_POSS);
	MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC1POL_MSK, polarity  << TIMER_CCEP_CC1POL_POS);

	return;
}

/**
  * @brief  Configure the Polarity and Filter for TI1.
  * @param  TIMERx: Select the TIMER peripheral.
  * @param  polarity: The Input Polarity.
  * @param  filter: Specifies the Input Capture Filter.
  *         This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void timer_ti1_set_config_stage(TIMER_TypeDef *TIMERx, timer_ic_polarity_t polarity, uint32_t filter)
{
	MODIFY_REG(TIMERx->CHMR1, TIMER_CHMR1_I1FLT_MSK, filter << TIMER_CHMR1_I1FLT_POSS);
	MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC1POL_MSK, polarity  << TIMER_CCEP_CC1POL_POS);


	return;
}

/**
  * @brief  Configure the TI2 as Input.
  * @param  TIMERx: Select the TIMER peripheral.
  * @param  polarity: The Input Polarity.
  * @param  sel: specifies the input to be used.
  * @param  filter: Specifies the Input Capture Filter.
  *         This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void timer_ti2_set_config(TIMER_TypeDef *TIMERx, timer_ic_polarity_t polarity,
                                   timer_ic_select_t sel, uint32_t filter)
{
	CLEAR_BIT(TIMERx->CCEP, TIMER_CCEP_CC2EN_MSK);
	MODIFY_REG(TIMERx->CHMR1, TIMER_CHMR1_CC2SSEL_MSK, sel << TIMER_CHMR1_CC2SSEL_POSS);
	MODIFY_REG(TIMERx->CHMR1, TIMER_CHMR1_I2FLT_MSK, filter << TIMER_CHMR1_I2FLT_POSS);
	MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC2POL_MSK, polarity << TIMER_CCEP_CC2POL_POS);


	return;
}

/**
  * @brief  Configure the Polarity and Filter for TI2.
  * @param  TIMERx: Select the TIMER peripheral.
  * @param  polarity: The Input Polarity.
  * @param  filter: Specifies the Input Capture Filter.
  *         This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void timer_ti2_set_config_stage(TIMER_TypeDef *TIMERx, timer_ic_polarity_t polarity, uint32_t filter)
{
	MODIFY_REG(TIMERx->CHMR1, TIMER_CHMR1_I2FLT_MSK, filter << TIMER_CHMR1_I2FLT_POSS);
	MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC2POL_MSK, polarity  << TIMER_CCEP_CC2POL_POS);
	return;
}

/**
  * @brief  Configure the TI3 as Input.
  * @param  TIMERx: Select the TIMER peripheral.
  * @param  polarity: The Input Polarity.
  * @param  sel: specifies the input to be used.
  * @param  filter: Specifies the Input Capture Filter.
  *         This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void timer_ti3_set_config(TIMER_TypeDef *TIMERx, timer_ic_polarity_t polarity,
                                   timer_ic_select_t sel, uint32_t filter)
{
	CLEAR_BIT(TIMERx->CCEP, TIMER_CCEP_CC3EN_MSK);
	MODIFY_REG(TIMERx->CHMR2, TIMER_CHMR2_CC3SSEL_MSK, sel << TIMER_CHMR2_CC3SSEL_POSS);
	MODIFY_REG(TIMERx->CHMR2, TIMER_CHMR2_I3FLT_MSK, filter << TIMER_CHMR2_I3FLT_POSS);
	MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC3POL_MSK, polarity << TIMER_CCEP_CC3POL_POS);

	return;
}

/**
  * @brief  Configure the TI4 as Input.
  * @param  TIMERx: Select the TIMER peripheral.
  * @param  polarity: The Input Polarity.
  * @param  sel: specifies the input to be used.
  * @param  filter: Specifies the Input Capture Filter.
  *         This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void timer_ti4_set_config(TIMER_TypeDef *TIMERx, timer_ic_polarity_t polarity,
                                   timer_ic_select_t sel, uint32_t filter)
{
	CLEAR_BIT(TIMERx->CCEP, TIMER_CCEP_CC4EN_MSK);
	MODIFY_REG(TIMERx->CHMR2, TIMER_CHMR2_CC4SSEL_MSK, sel << TIMER_CHMR2_CC4SSEL_POSS);
	MODIFY_REG(TIMERx->CHMR2, TIMER_CHMR2_I4FLT_MSK, filter << TIMER_CHMR2_I4FLT_POSS);
	MODIFY_REG(TIMERx->CCEP, TIMER_CCEP_CC4POL_MSK, polarity << TIMER_CCEP_CC4POL_POS);
	return;
}

/**
  * @brief  Configures the TIMERx External Trigger (ETR).
  * @param  TIMERx: Select the TIMER peripheral
  * @param  psc: The external Trigger Prescaler.
  * @param  polarity: The external Trigger Polarity.
  * @param  filter: External Trigger Filter.
  *         This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
static void timer_etr_set_config(TIMER_TypeDef* TIMERx, timer_etr_psc_t psc, timer_clock_polarity_t polarity, uint32_t filter)
{
	MODIFY_REG(TIMERx->SMCON, TIMER_SMCON_ETFLT_MSK, filter << TIMER_SMCON_ETFLT_POSS);
	MODIFY_REG(TIMERx->SMCON, TIMER_SMCON_ETPSEL_MSK, psc << TIMER_SMCON_ETPSEL_POSS);
	CLEAR_BIT(TIMERx->SMCON, TIMER_SMCON_ECM2EN_MSK);
	MODIFY_REG(TIMERx->SMCON, TIMER_SMCON_ETPOL_MSK, polarity << TIMER_SMCON_ETPOL_POS);
	return;
}

/**
  * @brief  Time Slave configuration
  * @param  hperh: pointer to a timer_handle_t structure that contains
  *         the configuration information for TIMER module.
  * @param  config: The slave configuration structure
  * @retval None
  */
static void timer_slave_set_config(timer_handle_t *hperh, timer_slave_config_t *config)
{
	MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_TSSEL_MSK, config->input << TIMER_SMCON_TSSEL_POSS);
	MODIFY_REG(hperh->perh->SMCON, TIMER_SMCON_SMODS_MSK, config->mode << TIMER_SMCON_SMODS_POSS);

	switch (config->input) {
	case TIMER_TS_ETRF:
		timer_etr_set_config(hperh->perh, config->psc, config->polarity, config->filter);
		break;

	case TIMER_TS_TI1F_ED:
		CLEAR_BIT(hperh->perh->CCEP, TIMER_CCEP_CC1EN_MSK);
		MODIFY_REG(hperh->perh->CHMR1, TIMER_CHMR1_I1FLT_MSK, config->filter << TIMER_CHMR1_I1FLT_POSS);
		break;

	case TIMER_TS_TI1FP1:
		timer_ti1_set_config_stage(hperh->perh, (timer_ic_polarity_t)config->polarity, config->filter);
		break;

	case TIMER_TS_TI2FP2:
		timer_ti2_set_config_stage(hperh->perh, (timer_ic_polarity_t)config->polarity, config->filter);
		break;

	default:
		break;
	}
}

#ifdef ALD_DMA

/**
  * @brief  Timer DMA msel signal configuration
  * @param  hperh: pointer to a timer_handle_t structure that contains
  *         the configuration information for TIMER module.
  * @param  config: DMA configuration structure
  * @retval None
  */
static void timer_dma_msel(TIMER_TypeDef *hperh, dma_config_t *config)
{
	#if defined (ES32F065x)
	if (hperh == AD16C4T0)
		config->msel = DMA_MSEL_TIMER0;
	if (hperh == GP16C4T0)
		config->msel = DMA_MSEL_TIMER6;
	#elif defined (ES32F033x) || defined (ES32F093x)
	if (hperh == GP16C4T0)
		config->msel = DMA_MSEL_TIMER0;
	if (hperh == GP16C4T1)
		config->msel = DMA_MSEL_TIMER6;
	#endif

	if (hperh == GP16C2T0)
		config->msel = DMA_MSEL_TIMER2;
	if (hperh == GP16C2T1)
		config->msel = DMA_MSEL_TIMER3;
	if (hperh == BS16T0)
		config->msel = DMA_MSEL_TIMER1;
	if (hperh == BS16T1)
		config->msel = DMA_MSEL_TIMER4;
	if (hperh == BS16T2)
		config->msel = DMA_MSEL_TIMER5;
	if (hperh == BS16T3)
		config->msel = DMA_MSEL_TIMER7;
}

#endif

/**
  * @}
  */
#endif /* ALD_TIMER */
/**
  * @}
  */
/**
  * @}
  */
