/**
  *********************************************************************************
  *
  * @file    ald_acmp.c
  * @brief   ACMP module driver.
  *
  * @version V1.0
  * @date    13 Dec 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#include "ald_acmp.h"

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

    if (hperh == NULL)
        return ERROR;

    if (hperh->init.vdd_level > 63)
        return ERROR;

    assert_param(IS_ACMP_TYPE(hperh->perh));
    assert_param(IS_ACMP_MODE_TYPE(hperh->init.mode));
    assert_param(IS_ACMP_WARM_UP_TIME_TYPE(hperh->init.warm_time));
    assert_param(IS_ACMP_HYSTSEL_TYPE(hperh->init.hystsel));
    assert_param(IS_ACMP_WARM_FUNC_TYPE(hperh->init.warm_func));
    assert_param(IS_ACMP_POS_INPUT_TYPE(hperh->init.pos_port));
    assert_param(IS_ACMP_NEG_INPUT_TYPE(hperh->init.neg_port));
    assert_param(IS_ACMP_INACTVAL_TYPE(hperh->init.inactval));
    assert_param(IS_ACMP_EDGE_TYPE(hperh->init.edge));

    __LOCK(hperh);

    tmp = hperh->perh->CON;

    tmp |= ((hperh->init.mode << ACMP_CON_MODSEL_POSS) | (hperh->init.warm_time << ACMP_CON_WARMUPT_POSS) |
            (hperh->init.inactval << ACMP_CON_INACTV_POS) | (hperh->init.hystsel << ACMP_CON_HYSTSEL_POSS));

    hperh->perh->CON = tmp;

    tmp = hperh->perh->INPUTSEL;

    tmp |= ((hperh->init.pos_port << ACMP_INPUTSEL_PSEL_POSS) | (hperh->init.neg_port << ACMP_INPUTSEL_NSEL_POSS) |
            (hperh->init.vdd_level << ACMP_INPUTSEL_VDDLVL_POSS));

    hperh->perh->INPUTSEL = tmp;

    if (hperh->init.warm_func == ACMP_WARM_DISABLE)
        CLEAR_BIT(hperh->perh->IES, ACMP_IES_WARMUP_MSK);
    else
        SET_BIT(hperh->perh->IES, ACMP_IES_WARMUP_MSK);

    switch (hperh->init.edge)
    {
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

    while (READ_BIT(hperh->perh->STAT, ACMP_STAT_ACT_MSK) == 0)
    {
        if (tmp++ >= 600000)
        {
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
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_acmp_interrupt_config(acmp_handle_t *hperh, acmp_it_t it, type_func_t state)
{
    assert_param(IS_ACMP_TYPE(hperh->perh));
    assert_param(IS_ACMP_IT_TYPE(it));
    assert_param(IS_FUNC_STATE(state));

    __LOCK(hperh);

    if (state)
        hperh->perh->IES |= it;
    else
        hperh->perh->IEC |= it;

    __UNLOCK(hperh);

    return OK;
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
    else
        return RESET;
}

/**
  * @brief  Checks whether the specified ACMP interrupt has occurred or not.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  flag: Specifies the ACMP interrupt source to check.
  *         This parameter can be one of the @ref acmp_it_t.
  * @retval it_status_t
  *           - SET
  *           - RESET
  */
it_status_t ald_acmp_get_flag_status(acmp_handle_t *hperh, acmp_flag_t flag)
{
    assert_param(IS_ACMP_TYPE(hperh->perh));
    assert_param(IS_ACMP_FLAG_TYPE(flag));

    if (hperh->perh->RIF & flag)
    {
        __UNLOCK(hperh);
        return SET;
    }

    return RESET;
}

/** @brief  Clear the specified ACMP it flags.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  flag: specifies the it flag.
  *         This parameter can be one of the @ref acmp_it_t.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_acmp_clear_flag_status(acmp_handle_t *hperh, acmp_flag_t flag)
{
    assert_param(IS_ACMP_TYPE(hperh->perh));
    assert_param(IS_ACMP_FLAG_TYPE(flag));

    __LOCK(hperh);
    hperh->perh->IFC |= flag;
    __UNLOCK(hperh);

    return OK;
}

/** @brief  Set the specified acmp it flags.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified acmp module.
  * @param  it: specifies the  it flag.
  *         This parameter can be one of the @ref acmp_it_t.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t acmp_set_it_mask(acmp_handle_t *hperh, acmp_it_t it)
{
    assert_param(IS_ACMP_TYPE(hperh->perh));
    assert_param(IS_ACMP_IT_TYPE(it));

    __LOCK(hperh);
    hperh->perh->IFM |= it;
    __UNLOCK(hperh);

    return OK;
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
    {
        __UNLOCK(hperh);
        return SET;
    }

    return RESET;
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
    if ((ald_acmp_get_flag_status(hperh, ACMP_FLAG_WARMUP) == SET) && (ald_acmp_get_it_status(hperh, ACMP_IT_WARMUP) == SET))
    {
        if (hperh->acmp_warmup_cplt_cbk)
            hperh->acmp_warmup_cplt_cbk(hperh);

        ald_acmp_clear_flag_status(hperh, ACMP_FLAG_WARMUP);
    }

    if ((ald_acmp_get_flag_status(hperh, ACMP_FLAG_EDGE) == SET) && (ald_acmp_get_it_status(hperh, ACMP_IT_EDGE) == SET))
    {
        if (hperh->acmp_edge_cplt_cbk)
            hperh->acmp_edge_cplt_cbk(hperh);

        ald_acmp_clear_flag_status(hperh, ACMP_FLAG_EDGE);
    }

    return;
}

/**
  * @brief  This function config acmp output.
  * @param  hperh: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  config: Pointer to a acmp_output_config_t structure that contains
  *         the configutation information for acmp output.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_acmp_out_config(acmp_handle_t *hperh, acmp_output_config_t *config)
{
    if (hperh == NULL)
        return ERROR;

    if (config == NULL)
        return ERROR;

    assert_param(IS_ACMP_TYPE(hperh->perh));
    assert_param(IS_ACMP_INVERT_TYPE(config->gpio_inv));
    assert_param(IS_ACMP_OUT_FUNC_TYPE(config->out_func));

    __LOCK(hperh);
    hperh->perh->CON |= (config->gpio_inv << ACMP_CON_OUTINV_POS);
    hperh->perh->PORT = config->out_func;
    __UNLOCK(hperh);

    return OK;
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
