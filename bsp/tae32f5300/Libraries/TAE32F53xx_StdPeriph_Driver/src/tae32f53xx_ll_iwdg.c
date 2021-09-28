/**
  ******************************************************************************
  * @file    tae32f53xx_ll_iwdg.c
  * @author  MCD Application Team
  * @brief   IWDG LL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Independent Watchdog (IWDG) peripheral:
  *           + Initialization and De-Initialization functions
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


#define DBG_TAG             "IWDG LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup IWDG_LL IWDG LL
  * @brief    IWDG LL module driver.
  * @{
  */

#ifdef LL_IWDG_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup IWDG_LL_Private_Defines IWDG LL Private Defines
  * @brief    IWDG LL Private Defines
  * @{
  */

/**
  * @brief Max delay time for IWDG status register update
  */
#define IWDG_TIMEOUT_VALUE                          100U
/**
  * @}
  */


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup IWDG_LL_Exported_Functions IWDG LL Exported Functions
  * @brief    IWDG LL Exported Functions
  * @{
  */

/** @defgroup IWDG_LL_Exported_Functions_Group1 Initialization and De-Initialization functions
  * @brief    Initialization and De-Initialization functions
@verbatim
  ===============================================================================
            ##### Initialization and de-initialization functions #####
  ===============================================================================
  [..]  This section provides a set of functions allowing to initialize and
        deinitialize the IWDG peripheral

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the IWDG peripheral according to the specified parameters in the Init.
  * @param  Instance IWDG peripheral instance
  * @param  Init pointer to a IWDG_InitTypeDef structure that contains the configuration information
  *         for the specified IWDG peripheral.
  * @return status of the initialization
  */
LL_StatusETypeDef LL_IWDG_Init(IWDG_TypeDef *Instance, IWDG_InitTypeDef *Init)
{
    uint32_t tickstart = 0;

    /* Check the IWDG initiation struct allocation */
    if (Init == NULL) {
        return LL_ERROR;
    }

    /* Check the parameters */
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));
    assert_param(IS_IWDG_RELOAD_Val(Init->Reload_val));

    /* Handle Something */
    LL_IWDG_MspInit(Instance);

    /* Start IWDG to work */
    __LL_IWDG_START(Instance);

    /* Enable write access to IWDG_PSCR, IWDG_RLR and IWDG_CR registers */
    __LL_IWDG_ENABLE_WRITE_ACCESS(Instance);

    /* PSCUPD must be 0 before writting prescaler settings to IWDG_PSCR register */
    tickstart = LL_GetTick();

    while (__LL_IWDG_GET_FLAG(Instance, IWDG_FLAG_PSCUPD) != RESET) {
        if ((LL_GetTick() - tickstart) > IWDG_TIMEOUT_VALUE) {
            return LL_TIMEOUT;
        }
    }

    /* Write to IWDG registers the Prescaler to work with */
    WRITE_REG(Instance->PSCR, Init->Prescaler);

    /* RLVUPD must be 0 before writting reload values to IWDG_RLR register */
    tickstart = LL_GetTick();

    while (__LL_IWDG_GET_FLAG(Instance, IWDG_FLAG_RLVUPD) != RESET) {
        if ((LL_GetTick() - tickstart) > IWDG_TIMEOUT_VALUE) {
            return LL_TIMEOUT;
        }
    }

    /* Write to IWDG registers the Reload values to work with */
    WRITE_REG(Instance->RLR, Init->Reload_val);

    /* Configure the IWDG bahavior after timeout */
    MODIFY_REG(Instance->CR, IWDG_CR_MODE, Init->Mode);

    /* Enable IWDG interrupt when using interrupt mode */
    if (Init->Mode == IWDG_MODE_INTERRUPT) {
        __LL_IWDG_ENABLE_IT(Instance, IWDG_IT_TOIE);
    }

    /* Disable write access to IWDG_PSCR, IWDG_RLR and IWDG_CR registers */
    __LL_IWDG_DISABLE_WRITE_ACCESS(Instance);

    /* Reload IWDG counter with value defined in the reload register */
    __LL_IWDG_RELOAD_COUNTER(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  De-initializes the IWDG peripheral.
  * @param  Instance IWDG peripheral
  * @return status of the de-initialization
  */
LL_StatusETypeDef LL_IWDG_DeInit(IWDG_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));

    /* Enable write access to IWDG_PSCR, IWDG_RLR and IWDG_CR registers */
    __LL_IWDG_ENABLE_WRITE_ACCESS(Instance);

    /* Disable the IWDG peripheral. */
    __LL_IWDG_STOP(Instance);

    /* Disable write access to IWDG_PSCR, IWDG_RLR and IWDG_CR registers */
    __LL_IWDG_DISABLE_WRITE_ACCESS(Instance);

    /* Handle Something */
    LL_IWDG_MspDeInit(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Initializes the IWDG MSP.
  * @param  Instance IWDG peripheral
  * @return None
  */
__WEAK void LL_IWDG_MspInit(IWDG_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_IWDG_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the IWDG MSP
  * @param  Instance IWDG peripheral
  * @return None
  */
__WEAK void LL_IWDG_MspDeInit(IWDG_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_IWDG_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup IWDG_LL_Exported_Functions_Group2 IWDG Input and Output operation functions
  * @brief    IWDG Input and Output operation functions
@verbatim
  ===============================================================================
                  ##### Input and Output operation functions #####
  ===============================================================================
  [..]
    This section provides functions allowing to:
    (+) Refresh the IWDG.

@endverbatim
  * @{
  */

/**
  * @brief  Refresh the IWDG.
  * @param  Instance: IWDG peripheral
  * @return LL_Status
  */
LL_StatusETypeDef LL_IWDG_Refresh(IWDG_TypeDef *Instance)
{
    uint32_t tickstart = 0;
    /* Check the parameters */
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));

    /* Notice that RLVUPD and PSCUPD must be 0 before refreshing IWDG counter */
    while ((__LL_IWDG_GET_FLAG(Instance, IWDG_FLAG_RLVUPD) != RESET) || (__LL_IWDG_GET_FLAG(Instance, IWDG_FLAG_PSCUPD) != RESET)) {
        if ((LL_GetTick() - tickstart) > IWDG_TIMEOUT_VALUE) {
            return LL_TIMEOUT;
        }
    }

    /* Reload IWDG counter with value defined in the IWDG_RLR register */
    __LL_IWDG_RELOAD_COUNTER(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @}
  */


/** @defgroup IWDG_LL_Exported_Functions_Interrupt IWDG Initerrupt management
  * @brief    IWDG Initerrupt management
@verbatim
  ===============================================================================
                          ##### Initerrupt management #####
  ===============================================================================
  [..]
      This section provides IWDG interrupt handler and callback functions.

@endverbatim
  * @{
  */

/**
  * @brief  This function handles IWDG interrupts requests.
  * @param  Instance: IWDG peripheral
  * @return None
  */
void LL_IWDG_IRQHandler(IWDG_TypeDef *Instance)
{
    if ((__LL_IWDG_IT_CHECK_SOURCE(Instance, IWDG_IT_TOIE) != RESET) && (__LL_IWDG_GET_FLAG(Instance, IWDG_FLAG_TOIF) != RESET)) {
        /* Clear the TOIF interrupt flag */
        __LL_IWDG_CLEAR_FLAG(Instance, IWDG_FLAG_TOIF);

        /* IWDG timeout callback */
        LL_IWDG_TimeOutCallBack(Instance);
    }
}

/**
  * @brief  Timeout callback
  * @param  Instance IWDG peripheral
  * @return None
  */
__WEAK void LL_IWDG_TimeOutCallBack(IWDG_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_IWDG_TimeOutCallBack could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


#endif /* LL_IWDG_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

