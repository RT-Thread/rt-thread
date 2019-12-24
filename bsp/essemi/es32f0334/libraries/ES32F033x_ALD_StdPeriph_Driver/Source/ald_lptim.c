/**
  *********************************************************************************
  *
  * @file    ald_lptim.c
  * @brief   LPTIM module driver.
  *	     This is the common part of the LPTIM initialization
  *
  * @version V1.0
  * @date    09 Nov 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#include "ald_lptim.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup LPTIM LPTIM
  * @brief LPTIM module driver
  * @{
  */
#ifdef ALD_LPTIM

/** @defgroup LPTIM_Public_Functions LPTIM Public Functions
  * @{
  */

/** @defgroup LPTIM_Public_Functions_Group1 Initialization functions
  * @brief    Initialization and Configuration functions
  *
  * @{
  */
/**
  * @brief  Reset the LPTIM peripheral.
  * @param  hperh: Pointer to a lptim_handle_t.
  * @retval None
  */
void ald_lptim_reset(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));

    hperh->state = LPTIM_STATE_BUSY;
    LPTIM_DISABLE(hperh);
    hperh->state = LPTIM_STATE_RESET;
    __UNLOCK(hperh);

    return;
}

/**
  * @brief  Configure the LPTIM trigger mode according to the specified parameters in
  *         the lptim_trigger_init_t.
  * @param  hperh: Pointer to a lptim_handle_t.
  * @param  config: Pointer to a lptim_trigger_init_t.
  * @retval None
  */
void ald_lptim_trigger_config(lptim_handle_t *hperh, lptim_trigger_init_t *config)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_TRIGEN(config->mode));
    assert_param(IS_LPTIM_TRIGSEL(config->sel));

    MODIFY_REG(hperh->perh->CON0, LP16T_CON0_TRIGEN_MSK, (config->mode) << LP16T_CON0_TRIGEN_POSS);
    MODIFY_REG(hperh->perh->CON0, LP16T_CON0_TRIGSEL_MSK, (config->sel) << LP16T_CON0_TRIGSEL_POSS);

    return;
}

/**
  * @brief  Configure the LPTIM clock source according to the specified parameters in
  *         the lptim_clock_source_init_t.
  * @param  hperh: Pointer to a lptim_handle_t.
  * @param  config: Pointer to a lptim_clock_source_init_t.
  * @retval None
  */
void ald_lptim_clock_source_config(lptim_handle_t *hperh, lptim_clock_source_init_t *config)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_CKSEL(config->sel));
    assert_param(IS_LPTIM_CKPOL(config->polarity));

    MODIFY_REG(hperh->perh->CON0, LP16T_CON0_CKSEL_MSK, (config->sel) << LP16T_CON0_CKSEL_POS);
    MODIFY_REG(hperh->perh->CON0, LP16T_CON0_CKPOL_MSK, (config->polarity) << LP16T_CON0_CKPOL_POS);

    return;
}

/**
  * @brief  Configure the LPTIM trigger filter parameter according to
  *         the specified parameters in the lptim_trgflt_t.
  * @param  hperh: Pointer to a lptim_handle_t.
  * @param  flt: Pointer to a lptim_trgflt_t.
  * @retval None
  */
void ald_lptim_trigger_filter_config(lptim_handle_t *hperh, lptim_trgflt_t flt)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_TRGFLT(flt));

    MODIFY_REG(hperh->perh->CON0, LP16T_CON0_TRGFLT_MSK, flt << LP16T_CON0_TRGFLT_POSS);

    return;
}

/**
  * @brief  Configure the LPTIM clock filter parameter according to
  *         the specified parameters in the lptim_ckflt_t.
  * @param  hperh: Pointer to a lptim_handle_t.
  * @param  flt: Pointer to a lptim_ckflt_t.
  * @retval None
  */
void ald_lptim_clock_filter_config(lptim_handle_t *hperh, lptim_ckflt_t flt)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_TRGFLT(flt));

    MODIFY_REG(hperh->perh->CON0, LP16T_CON0_CKFLT_MSK, flt << LP16T_CON0_CKFLT_POSS);

    return;
}
/**
  * @}
  */

/** @defgroup LPTIM_Public_Functions_Group2 LPTIM output toggle functions
  *  @brief    LPTime output toggle functions
  *
  * @verbatim
  ==============================================================================
                  ##### Time Output Compare functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize the LPTIM Output Toggle.
    (+) Start the LPTIM Output Toggle.
    (+) Stop the LPTIM Output Toggle.
    (+) Start the LPTIM Output Toggle and enable interrupt.
    (+) Stop the LPTIM Output Toggle and disable interrupt.

    @endverbatim
  * @{
  */
/**
  * @brief  Initializes the TIM Output toggle according to the specified
  *		parameters in the tim_handle_t.
  * @param  hperh: LPTIM handle
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lptim_toggle_init(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_PRESC(hperh->init.psc));

    __LOCK(hperh);
    hperh->state = LPTIM_STATE_BUSY;

    ald_cmu_lptim0_clock_select(hperh->init.clock);

    WRITE_REG(hperh->perh->UPDATE, 1);
    MODIFY_REG(hperh->perh->CON0, LP16T_CON0_WAVE_MSK, LPTIM_WAVE_TOGGLE << LP16T_CON0_WAVE_POSS);
    MODIFY_REG(hperh->perh->CON0, LP16T_CON0_PRESC_MSK, (hperh->init.psc) << LP16T_CON0_PRESC_POSS);
    WRITE_REG(hperh->perh->ARR, hperh->init.arr);
    WRITE_REG(hperh->perh->CMP, hperh->init.cmp);
    WRITE_REG(hperh->perh->UPDATE, 0);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_ARRWBSY_MSK));

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CMPWBSY_MSK));

    hperh->state = LPTIM_STATE_READY;
    __UNLOCK(hperh);
    return OK;
}

/**
  * @brief  Starts the LPTIM Output toggle.
  * @param  hperh: LPTIM handle
  * @retval None
  */
void ald_lptim_toggle_start(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_MODE(hperh->init.mode));

    LPTIM_ENABLE(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    if (hperh->init.mode == LPTIM_MODE_CONTINUOUS)
        LPTIM_CNTSTART(hperh);
    else
        LPTIM_SNGSTART(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    return;
}

/**
  * @brief  Stops the LPTIM Output toggle.
  * @param  hperh: LPTIM handle
  * @retval None
  */
void ald_lptim_toggle_stop(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));

    LPTIM_DISABLE(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    return;
}

/**
  * @brief  Starts the LPTIM Output toggle in interrupt mode.
  * @param  hperh: LPTIM handle
  * @retval None
  */
void ald_lptim_toggle_start_by_it(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_MODE(hperh->init.mode));

    ald_lptim_interrupt_config(hperh, LPTIM_IT_ARRMAT, ENABLE);
    LPTIM_ENABLE(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    if (hperh->init.mode == LPTIM_MODE_CONTINUOUS)
        LPTIM_CNTSTART(hperh);
    else
        LPTIM_SNGSTART(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    return;
}

/**
  * @brief  Stops the LPTIM Output toggle in interrupt mode.
  * @param  hperh: LPTIM handle
  * @retval None
  */
void ald_lptim_toggle_stop_by_it(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));

    ald_lptim_interrupt_config(hperh, LPTIM_IT_ARRMAT, DISABLE);
    LPTIM_DISABLE(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    return;
}
/**
  * @}
  */

/** @defgroup LPTIM_Public_Functions_Group3 LPTIM output pulse functions
  *  @brief    LPTime output pulse functions
  *
  * @verbatim
  ==============================================================================
                  ##### Time Output Compare functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize the LPTIM Output pulse.
    (+) Start the LPTIM Output pulse.
    (+) Stop the LPTIM Output pulse.
    (+) Start the LPTIM Output pulse and enable interrupt.
    (+) Stop the LPTIM Output pulse and disable interrupt.

    @endverbatim
  * @{
  */
/**
  * @brief  Initializes the TIM Output pulse according to the specified
  *		parameters in the tim_handle_t.
  * @param  hperh: LPTIM handle
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lptim_pulse_init(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_PRESC(hperh->init.psc));

    __LOCK(hperh);
    hperh->state = LPTIM_STATE_BUSY;
    ald_cmu_lptim0_clock_select(hperh->init.clock);

    WRITE_REG(hperh->perh->UPDATE, 1);
    MODIFY_REG(hperh->perh->CON0, LP16T_CON0_WAVE_MSK, LPTIM_WAVE_PULSE << LP16T_CON0_WAVE_POSS);
    MODIFY_REG(hperh->perh->CON0, LP16T_CON0_PRESC_MSK, (hperh->init.psc) << LP16T_CON0_PRESC_POSS);
    WRITE_REG(hperh->perh->ARR, hperh->init.arr);
    WRITE_REG(hperh->perh->CMP, hperh->init.cmp);
    WRITE_REG(hperh->perh->UPDATE, 0);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_ARRWBSY_MSK));

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CMPWBSY_MSK));

    hperh->state = LPTIM_STATE_READY;
    __UNLOCK(hperh);
    return OK;
}

/**
  * @brief  Starts the LPTIM Output pulse.
  * @param  hperh: LPTIM handle
  * @retval None
  */
void ald_lptim_pulse_start(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_MODE(hperh->init.mode));

    LPTIM_ENABLE(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    if (hperh->init.mode == LPTIM_MODE_CONTINUOUS)
        LPTIM_CNTSTART(hperh);
    else
        LPTIM_SNGSTART(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    return;
}

/**
  * @brief  Stops the LPTIM Output pulse.
  * @param  hperh: LPTIM handle
  * @retval None
  */
void ald_lptim_pulse_stop(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));

    LPTIM_DISABLE(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    return;
}

/**
  * @brief  Starts the LPTIM Output pulse in interrupt mode.
  * @param  hperh: LPTIM handle
  * @retval None
  */
void ald_lptim_pulse_start_by_it(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_MODE(hperh->init.mode));

    ald_lptim_interrupt_config(hperh, LPTIM_IT_ARRMAT, ENABLE);
    LPTIM_ENABLE(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    if (hperh->init.mode == LPTIM_MODE_CONTINUOUS)
        LPTIM_CNTSTART(hperh);
    else
        LPTIM_SNGSTART(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    return;
}

/**
  * @brief  Stops the LPTIM Output pulse in interrupt mode.
  * @param  hperh: LPTIM handle
  * @retval None
  */
void ald_lptim_pulse_stop_by_it(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));

    ald_lptim_interrupt_config(hperh, LPTIM_IT_ARRMAT, DISABLE);
    LPTIM_DISABLE(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    return;
}
/**
  * @}
  */

/** @defgroup LPTIM_Public_Functions_Group4 LPTIM output pwm functions
  *  @brief    LPTime output pwm functions
  *
  * @verbatim
  ==============================================================================
                  ##### Time Output Compare functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize the LPTIM Output pwm.
    (+) Start the LPTIM Output pwm.
    (+) Stop the LPTIM Output pwm.
    (+) Start the LPTIM Output pwm and enable interrupt.
    (+) Stop the LPTIM Output pwm and disable interrupt.

    @endverbatim
  * @{
  */
/**
  * @brief  Initializes the TIM Output pwm according to the specified
  *		parameters in the tim_handle_t.
  * @param  hperh: LPTIM handle
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lptim_pwm_init(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_PRESC(hperh->init.psc));

    __LOCK(hperh);
    hperh->state = LPTIM_STATE_BUSY;

    WRITE_REG(hperh->perh->UPDATE, 1);
    MODIFY_REG(hperh->perh->CON0, LP16T_CON0_WAVE_MSK, LPTIM_WAVE_PWM << LP16T_CON0_WAVE_POSS);
    MODIFY_REG(hperh->perh->CON0, LP16T_CON0_PRESC_MSK, (hperh->init.psc) << LP16T_CON0_PRESC_POSS);
    WRITE_REG(hperh->perh->ARR, hperh->init.arr);
    WRITE_REG(hperh->perh->CMP, hperh->init.cmp);
    WRITE_REG(hperh->perh->UPDATE, 0);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_ARRWBSY_MSK));

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CMPWBSY_MSK));

    hperh->state = LPTIM_STATE_READY;
    __UNLOCK(hperh);
    return OK;
}

/**
  * @brief  Starts the LPTIM Output pwm.
  * @param  hperh: LPTIM handle
  * @retval None
  */
void ald_lptim_pwm_start(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_MODE(hperh->init.mode));

    LPTIM_ENABLE(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    if (hperh->init.mode == LPTIM_MODE_CONTINUOUS)
        LPTIM_CNTSTART(hperh);
    else
        LPTIM_SNGSTART(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    return;
}

/**
  * @brief  Stops the LPTIM Output pwm.
  * @param  hperh: LPTIM handle
  * @retval None
  */
void ald_lptim_pwm_stop(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));

    LPTIM_DISABLE(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    return;
}

/**
  * @brief  Starts the LPTIM Output pwm in interrupt mode.
  * @param  hperh: LPTIM handle
  * @retval None
  */
void ald_lptim_pwm_start_by_it(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_MODE(hperh->init.mode));

    ald_lptim_interrupt_config(hperh, LPTIM_IT_CMPMAT, ENABLE);
    LPTIM_ENABLE(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    if (hperh->init.mode == LPTIM_MODE_CONTINUOUS)
        LPTIM_CNTSTART(hperh);
    else
        LPTIM_SNGSTART(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    return;
}

/**
  * @brief  Stops the LPTIM Output pwm in interrupt mode.
  * @param  hperh: LPTIM handle
  * @retval None
  */
void ald_lptim_pwm_stop_by_it(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));

    ald_lptim_interrupt_config(hperh, LPTIM_IT_CMPMAT, DISABLE);
    LPTIM_DISABLE(hperh);

    while (READ_BIT(hperh->perh->SYNCSTAT, LP16T_SYNCSTAT_CON1WBSY_MSK));

    return;
}
/**
  * @}
  */


/** @defgroup LPTIM_Public_Functions_Group5 Control functions
  * @brief LPTIM Control functions
  *
  * @{
  */
/**
  * @brief  This function handles LPTIM interrupts requests.
  * @param  hperh: LPTIM  handle
  * @retval None
  */
void ald_lptim_irq_handler(lptim_handle_t *hperh)
{
    assert_param(IS_LPTIM(hperh->perh));

    /* Output compare event */
    if (((ald_lptim_get_it_status(hperh, LPTIM_IT_CMPMAT)) != RESET) &&
            ((ald_lptim_get_flag_status(hperh, LPTIM_FLAG_CMPMAT)) != RESET))
    {
        ald_lptim_clear_flag_status(hperh, LPTIM_FLAG_CMPMAT);

        if (hperh->cmp_cbk)
            hperh->cmp_cbk(hperh);
    }

    /* Output update event */
    if (((ald_lptim_get_it_status(hperh, LPTIM_IT_ARRMAT)) != RESET) &&
            ((ald_lptim_get_flag_status(hperh, LPTIM_FLAG_ARRMAT)) != RESET))
    {
        ald_lptim_clear_flag_status(hperh, LPTIM_FLAG_ARRMAT);

        if (hperh->update_cbk)
            hperh->update_cbk(hperh);
    }

    /* Trigger event */
    if (((ald_lptim_get_it_status(hperh, LPTIM_IT_EXTTRIG)) != RESET) &&
            ((ald_lptim_get_flag_status(hperh, LPTIM_FLAG_EXTTRIG)) != RESET))
    {
        ald_lptim_clear_flag_status(hperh, LPTIM_FLAG_EXTTRIG);

        if (hperh->trig_cbk)
            hperh->trig_cbk(hperh);
    }

    return;
}

/**
  * @brief  Enables or disables the specified LPTIM interrupts.
  * @param  hperh: Pointer to a lptim_handle_t structure that contains
  *         the configuration information for the specified LPTIM module.
  * @param  it: Specifies the SPI interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref lptim_it_t.
  * @param  state: New status
  *           - ENABLE
  *           - DISABLE
  * @retval None
  */
void ald_lptim_interrupt_config(lptim_handle_t *hperh, lptim_it_t it, type_func_t state)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_IT(it));
    assert_param(IS_FUNC_STATE(state));

    if (state == ENABLE)
        SET_BIT(hperh->perh->IER, (uint32_t)it);
    else
        CLEAR_BIT(hperh->perh->IER, (uint32_t)it);

    return;
}

/**
  * @brief  Checks whether the specified LPTIM interrupt has occurred or not.
  * @param  hperh: Pointer to a lptim_handle_t structure that contains
  *         the configuration information for the specified LPTIM module.
  * @param  it: Specifies the LPTIM interrupt source to check.
  *         This parameter can be one of the @ref lptim_it_t.
  * @retval Status
  *           - SET
  *           - RESET
  */
it_status_t ald_lptim_get_it_status(lptim_handle_t *hperh, lptim_it_t it)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_IT(it));

    if (READ_BIT(hperh->perh->IER, it))
        return SET;

    return RESET;
}

/** @brief  Check whether the specified LPTIM flag is set or not.
  * @param  hperh: Pointer to a lptim_handle_t structure that contains
  *         the configuration information for the specified LPTIM module.
  * @param  flag: specifies the flag to check.
  *         This parameter can be one of the @ref lptim_flag_t.
  * @retval Status
  *           - SET
  *           - RESET
  */
flag_status_t ald_lptim_get_flag_status(lptim_handle_t *hperh, lptim_flag_t flag)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_FLAG(flag));

    if (READ_BIT(hperh->perh->ISR, flag))
        return SET;

    return RESET;
}

/** @brief  Clear the specified LPTIM pending flags.
  * @param  hperh: Pointer to a lptim_handle_t structure that contains
  *         the configuration information for the specified LPTIM module.
  * @param  flag: specifies the flag to check.
  *         This parameter can be one of the @ref lptim_flag_t.
  * @retval None
  */
void ald_lptim_clear_flag_status(lptim_handle_t *hperh, lptim_flag_t flag)
{
    assert_param(IS_LPTIM(hperh->perh));
    assert_param(IS_LPTIM_FLAG(flag));

    WRITE_REG(hperh->perh->IFC, (uint32_t)flag);
    return;
}
/**
  * @}
  */

/** @defgroup LPTIM_Public_Functions_Group6 Peripheral State functions
 *  @brief   Peripheral State functions
 *
 * @verbatim
  ==============================================================================
                        ##### Peripheral State functions #####
  ==============================================================================
    [..]
    This subsection permit to get in run-time the status of the peripheral.

    @endverbatim
  * @{
  */

/**
  * @brief  Return the LPTIM state
  * @param  hperh: LPTIM handle
  * @retval LPTIM peripheral state
  */
lptim_state_t ald_lptim_get_state(lptim_handle_t *hperh)
{
    return hperh->state;
}
/**
  * @}
  */
/**
  * @}
  */
#endif /* ALD_LPTIM */
/**
  * @}
  */
/**
  * @}
  */
