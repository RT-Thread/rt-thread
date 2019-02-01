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
  * @param  init: Pointer to a trng_init_t structure that contains
  *         the configuration information.
  * @retval None
  */
void trng_init(trng_init_t *init)
{
    assert_param(IS_TRNG_DATA_WIDTH(init->data_width));
    assert_param(IS_TRNG_SEED_TYPE(init->seed_type));
    assert_param(IS_TRNG_ADJC(init->adjc));

    SET_BIT(TRNG->CR, TRNG_CR_TRNGSEL_MSK);
    MODIFY_REG(TRNG->CR, TRNG_CR_DSEL_MSK, (init->data_width) << TRNG_CR_DSEL_POSS);
    MODIFY_REG(TRNG->CR, TRNG_CR_SDSEL_MSK, (init->seed_type) << TRNG_CR_SDSEL_POSS);
    MODIFY_REG(TRNG->CR, TRNG_CR_ADJC_MSK, (init->adjc) << TRNG_CR_ADJC_POSS);

    if (init->adjc == 0)
    {
        MODIFY_REG(TRNG->CR, TRNG_CR_ADJC_MSK, (0) << TRNG_CR_ADJC_POSS);
    }
    else
    {
        MODIFY_REG(TRNG->CR, TRNG_CR_ADJC_MSK, (1) << TRNG_CR_ADJC_POSS);
    }

    WRITE_REG(TRNG->SEED, init->seed);
    MODIFY_REG(TRNG->CFGR, TRNG_CFGR_TSTART_MSK, (init->t_start) << TRNG_CFGR_TSTART_POSS);
    MODIFY_REG(TRNG->CR, TRNG_CR_POSTEN_MSK, (init->posten) << TRNG_CR_POSTEN_MSK);

    return;
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
    (+) trng_get_result() API can Get the result.
    (+) trng_interrupt_config() API can be helpful to configure TRNG interrupt source.
    (+) trng_get_it_status() API can get the status of interrupt source.
    (+) trng_get_status() API can get the status of SR register.
    (+) trng_get_flag_status() API can get the status of interrupt flag.
    (+) trng_clear_flag_status() API can clear interrupt flag.

    @endverbatim
  * @{
  */

/**
  * @brief  Get the result.
  * @retval The resultl
  */
uint32_t trng_get_result(void)
{
    return (uint32_t)TRNG->DR;
}

/**
  * @brief  Enable/disable the specified interrupts.
  * @param  it: Specifies the interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref trng_it_t.
  * @param  state: New state of the specified interrupts.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void trng_interrupt_config(trng_it_t it, type_func_t state)
{
    assert_param(IS_TRNG_IT(it));
    assert_param(IS_FUNC_STATE(state));

    if (state)
        SET_BIT(TRNG->IER, it);
    else
        CLEAR_BIT(TRNG->IER, it);

    return;
}

/**
  * @brief  Get the status of SR register.
  * @param  status: Specifies the TRNG status type.
  *         This parameter can be one of the @ref trng_status_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t trng_get_status(trng_status_t status)
{
    assert_param(IS_TRNG_STATUS(status));

    if (READ_BIT(TRNG->SR, status))
        return SET;

    return RESET;
}

/**
  * @brief  Get the status of interrupt source.
  * @param  it: Specifies the interrupt source.
  *         This parameter can be one of the @ref trng_it_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
it_status_t trng_get_it_status(trng_it_t it)
{
    assert_param(IS_TRNG_IT(it));

    if (READ_BIT(TRNG->IER, it))
        return SET;

    return RESET;
}

/**
  * @brief  Get the status of interrupt flag.
  * @param  flag: Specifies the interrupt flag.
  *         This parameter can be one of the @ref trng_flag_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t trng_get_flag_status(trng_flag_t flag)
{
    assert_param(IS_TRNG_FLAG(flag));

    if (READ_BIT(TRNG->IFR, flag))
        return SET;

    return RESET;
}

/**
  * @brief  Clear the interrupt flag.
  * @param  flag: Specifies the interrupt flag.
  *         This parameter can be one of the @ref trng_flag_t.
  * @retval None
  */
void trng_clear_flag_status(trng_flag_t flag)
{
    assert_param(IS_TRNG_FLAG(flag));
    WRITE_REG(TRNG->IFCR, flag);

    return;
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
