/**
  *********************************************************************************
  *
  * @file    ald_temp.c
  * @brief   TEMP module driver.
  *
  * @version V1.0
  * @date    15 Dec 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#include "ald_temp.h"
#include "ald_bkpc.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup TEMP TEMP
  * @brief TEMP module driver
  * @{
  */
#ifdef ALD_TEMP


/** @defgroup TEMP_Private_Variables TEMP Private Variables
  * @{
  */
temp_cbk __temp_cbk;
/**
  * @}
  */

/** @defgroup TEMP_Public_Functions TEMP Public Functions
  * @{
  */

/** @addtogroup TEMP_Public_Functions_Group1 Initialization functions
  * @brief Initialization functions
  *
  * @verbatim
  ==============================================================================
              ##### Initialization functions #####
  ==============================================================================
    [..]  This section provides functions allowing to initialize the TEMP:
      (+) This parameters can be configured:
        (++) Update Cycle
        (++) Output Mode
        (++) Perscaler
      (+) Select TEMP source clock(default LOSC)

    @endverbatim
  * @{
  */

/**
  * @brief  Initializes the TEMP according to the specified
  *         parameters in the temp_init_t.
  * @param  init: Pointer to a temp_init_t structure that contains
  *         the configuration information.
  * @retval None
  */
void temp_init(temp_init_t *init)
{
    assert_param(IS_TEMP_UPDATE_CYCLE(init->cycle));
    assert_param(IS_TEMP_OUTPUT_MODE(init->mode));

    TEMP_UNLOCK();
    MODIFY_REG(TEMP->CR, TEMP_CR_TSU_MSK, init->cycle << TEMP_CR_TSU_POSS);
    MODIFY_REG(TEMP->CR, TEMP_CR_TOM_MSK, init->mode << TEMP_CR_TOM_POSS);
    MODIFY_REG(TEMP->CR, TEMP_CR_CTN_MSK, init->ctn << TEMP_CR_CTN_POS);
    MODIFY_REG(TEMP->PSR, TEMP_PSR_PRS_MSK, init->psc << TEMP_PSR_PRS_POSS);
    TEMP_LOCK();

    return;
}

/**
  * @brief  Configure the TEMP source.
  * @param  sel: TEMP source type.
  * @retval None
  */
void temp_source_selcet(temp_source_sel_t sel)
{
    assert_param(IS_TEMP_SOURCE_SEL(sel));

    BKPC_UNLOCK();
    MODIFY_REG(BKPC->PCCR, BKPC_PCCR_TEMPCS_MSK, sel << BKPC_PCCR_TEMPCS_POSS);

    if (sel == TEMP_SOURCE_LOSC)
    {
        SET_BIT(BKPC->CR, BKPC_CR_LOSCEN_MSK);
    }
    else if (sel == TEMP_SOURCE_LRC)
    {
        SET_BIT(BKPC->CR, BKPC_CR_LRCEN_MSK);
    }
    else
    {
        ; /* do nothing */
    }

    BKPC_LOCK();
    return;
}
/**
  * @}
  */

/** @addtogroup TEMP_Public_Functions_Group2 Peripheral Control functions
  * @brief Peripheral Control functions
  *
  * @verbatim
  ==============================================================================
              ##### Peripheral Control functions #####
  ==============================================================================
  [..]  This section provides functions allowing to:
    (+) temp_get_value() API can get the current temperature.
    (+) temp_get_value_by_it() API can get the current temperature by interrupt.
    (+) temp_irq_handle() API can handle the interrupt request.

    @endverbatim
  * @{
  */

/**
  * @brief  Get the current temperature
  * @param  temp: The value of current temperature.
  * @retval ALD status:
  *         @arg @ref OK    The value is valid
  *         @arg @ref ERROR The value is invalid
  */
ald_status_t temp_get_value(uint16_t *temp)
{
    TEMP_UNLOCK();
    SET_BIT(TEMP->IFCR, TEMP_IFCR_TEMP_MSK);
    SET_BIT(TEMP->CR, TEMP_CR_EN_MSK);
    TEMP_LOCK();

    while (!(READ_BIT(TEMP->IF, TEMP_IF_TEMP_MSK)));

    TEMP_UNLOCK();
    SET_BIT(TEMP->IFCR, TEMP_IFCR_TEMP_MSK);
    TEMP_LOCK();

    if (READ_BIT(TEMP->DR, TEMP_DR_ERR_MSK))
        return ERROR;

    *temp = READ_BITS(TEMP->DR, TEMP_DR_DATA_MSK, TEMP_DR_DATA_POSS);
    return OK;
}

/**
  * @brief  Get the current temperature by interrupt
  * @param  cbk: The callback function
  * @retval None
  */
void temp_get_value_by_it(temp_cbk cbk)
{
    __temp_cbk = cbk;

    TEMP_UNLOCK();
    SET_BIT(TEMP->IFCR, TEMP_IFCR_TEMP_MSK);
    SET_BIT(TEMP->IE, TEMP_IE_TEMP_MSK);
    SET_BIT(TEMP->CR, TEMP_CR_EN_MSK);
    TEMP_LOCK();

    return;
}

/**
  * @brief  This function handles TEMP interrupt request.
  * @retval None
  */
void temp_irq_handle(void)
{
    TEMP_UNLOCK();
    SET_BIT(TEMP->IFCR, TEMP_IFCR_TEMP_MSK);
    TEMP_LOCK();

    if (__temp_cbk == NULL)
        return;

    if (READ_BIT(TEMP->DR, TEMP_DR_ERR_MSK))
    {
        __temp_cbk(0, ERROR);
        return;
    }

    __temp_cbk(READ_BITS(TEMP->DR, TEMP_DR_DATA_MSK, TEMP_DR_DATA_POSS), OK);

    return;
}
/**
  * @}
  */
/**
  * @}
  */
#endif /* ALD_TEMP */
/**
  * @}
  */

/**
  * @}
  */
