/**
  ******************************************************************************
  * @file    tae32f53xx_ll_wwdg.c
  * @author  MCD Application Team
  * @brief   WWDG LL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Window Watchdog (WWDG) peripheral:
  *           + Initialization and de-initialization functions
  *           + Refresh function
  *           + Interrupt and Callback functions
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll.h"


#define DBG_TAG             "WWDG LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup WWDG_LL WWDG LL
  * @brief    WWDG LL module driver
  * @{
  */

#ifdef LL_WWDG_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup WWDG_LL_Exported_Functions WWDG LL Exported Functions
  * @brief    WWDG LL Exported Functions
  * @{
  */

/** @defgroup WWDG_LL_Exported_Functions_Group1 Initialization and De-Initialization functions
  * @brief    Initialization and Configuration functions.
  *
@verbatim
  ==============================================================================
          ##### Initialization and De-Initialization functions #####
  ==============================================================================
  [..]  This section provides a set of functions allowing to initialize and
        deinitialize the WWDG peripheral

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the WWDG according to the specified.
  *         parameters in the WWDG_InitTypeDef of associated handle.
  * @param  Instance WWDG peripheral
  * @param  Init pointer to a WWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified WWDG module.
  * @return LL status
  */
LL_StatusETypeDef LL_WWDG_Init(WWDG_TypeDef *Instance, WWDG_InitTypeDef *Init)
{
    /* Check the WWDG handle allocation */
    if (Init == NULL) {
        return LL_ERROR;
    }

    /* Check the parameters */
    assert_param(IS_WWDG_ALL_INSTANCE(Instance));
    assert_param(IS_WWDG_PRESCALER(Init->Prescaler));
    assert_param(IS_WWDG_WINDOW(Init->Window));
    assert_param(IS_WWDG_COUNTER(Init->Counter));

    /* Handle Something */
    LL_WWDG_MspInit(Instance);

    /* Set WWDG Counter */
    WRITE_REG(Instance->CVR, Init->Counter);

    /* Set WWDG Prescaler */
    WRITE_REG(Instance->PSCR, Init->Prescaler);

    /* Set WWDG Window Val */
    WRITE_REG(Instance->WVR, Init->Window);

    /* SET Early Interrupt */
    MODIFY_REG(Instance->CR, WWDG_CR_EWIE, Init->EWIMode);

    /* Start WWDG Counter */
    __LL_WWDG_ENABLE(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  De-initializes the WWDG peripheral.
  * @param  Instance WWDG peripheral
  * @return status of the de-initialization
  */
LL_StatusETypeDef LL_WWDG_DeInit(WWDG_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_WWDG_ALL_INSTANCE(Instance));

    /*Disable WWDG*/
    __LL_WWDG_DISABLE(Instance);

    /* Handle Something */
    LL_WWDG_MspDeInit(Instance);

    /* Return function status */
    return LL_OK;
}

__WEAK void LL_WWDG_MspInit(WWDG_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_WWDG_MspInit could be implemented in the user file
     */
}

__WEAK void LL_WWDG_MspDeInit(WWDG_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_WWDG_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup WWDG_LL_Exported_Functions_Group2 WWDG Input and Output operation functions
  * @brief    WWDG Input and Output operation functions
@verbatim
  ===============================================================================
                  ##### Input and Output operation functions #####
  ===============================================================================
  [..]
    This section provides functions allowing to:
    (+) Refresh the WWDG.

@endverbatim
  * @{
  */

/**
  * @brief  Refresh the WWDG.
  * @param  Instance WWDG peripheral
  * @param  Counter Counter value to refresh with
  * @return LL status
  */
LL_StatusETypeDef LL_WWDG_Refresh(WWDG_TypeDef *Instance, uint16_t Counter)
{
    /* Check the parameters */
    assert_param(IS_WWDG_ALL_INSTANCE(Instance));
    assert_param(IS_WWDG_COUNTER(Counter));

    /* Write to WWDG CR the WWDG Counter value to refresh with */
    __LL_WWDG_SET_COUNTER(Instance, Counter);

    /* Return function status */
    return LL_OK;
}

/**
  * @}
  */


/** @defgroup WWDG_LL_Exported_Functions_Interrupt WWDG Interrupt management
  * @brief    WWDG Initerrupt management
@verbatim
  ===============================================================================
                          ##### Initerrupt management #####
  ===============================================================================
  [..]
      This section provides WWDG interrupt handler and callback functions.

@endverbatim
  * @{
  */

/**
  * @brief Handle WWDG interrupt request.
  * @param Instance: WWDG peripheral
  * @return None
  */
void LL_WWDG_IRQHandler(WWDG_TypeDef *Instance)
{
    /* Check if Early Wakeup Interrupt is enable */
    if ((__LL_WWDG_CHECK_IT_SOURCE(Instance, WWDG_IT_EWIE) != RESET) && (__LL_WWDG_GET_FLAG(Instance, WWDG_FLAG_EWIF) != RESET)) {

        /* Clear Flag */
        __LL_WWDG_CLEAR_FLAG(Instance, WWDG_FLAG_EWIF);

        /* Early Wakeup callback */
        LL_WWDG_EarlyWakeUpCallback(Instance);
    }
}

/**
  * @brief  WWDG Early Wakeup callback.
  * @param  Instance WWDG peripheral
  * @return None
  */
__WEAK void LL_WWDG_EarlyWakeUpCallback(WWDG_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_WWDG_EarlyWakeupCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


#endif /* LL_WWDG_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

