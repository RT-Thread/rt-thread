/**
  ******************************************************************************
  * @file    tae32f53xx_ll_iir.c
  * @author  MCD Application Team
  * @brief   IIR LL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the IIR peripheral:
  *           + Initialization and De-Initialization functions
  *           + Start and Stop functions
  *           + Get output data function
  *           + Reset internal buffer function
  *           + Interrupt and Callback functions

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


#define DBG_TAG             "IIR LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup IIR_LL IIR LL
  * @brief    IIR LL module driver
  * @{
  */

#ifdef LL_IIR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup IIR_LL_Exported_functions IIR LL Exported functions
  * @brief    IIR LL Exported functions
  * @{
  */

/** @defgroup IIR_LL_Exported_Functions_Group1 Initialization and De-Initialization functions
  * @brief    Initialization and De-Initialization functions
@verbatim
  ===============================================================================
            ##### Initialization and De-Initialization functions #####
  ===============================================================================
  [..]  This section provides a set of functions allowing to initialize and
        deinitialize the IIR peripheral

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the IIR peripheral.
  * @param  Instance Specifies IIR peripheral.
  * @param  Init pointer to a IIR_InitTypeDef structure that contains the
  *         configuration information for the specified IIR peripheral.
  * @return status of the initialization
  */
LL_StatusETypeDef LL_IIR_Init(IIR_TypeDef *Instance, IIR_InitTypeDef *Init)
{
    /* Check the parameters */
    assert_param(IS_IIR_ALL_INSTANCE(Instance));

    /* Handle Something */
    LL_IIR_MspInit(Instance);

    /* IIRx_CR0 Configure : IIR Order select, Internal buffer reset and
       enable IIR peripheral */
    WRITE_REG(Instance->CR0, (Init->Order | Init->BufferReset));

    /* Enable the IIR peripheral */
    __LL_IIR_ENABLE(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  De-initializes the IIR peripheral registers to their default reset values.
  * @param  IIRx where x can be (0, 1, ...) to select the IIR peripheral.
  * @retval status of the de-initialization
  */
LL_StatusETypeDef LL_IIR_DeInit(IIR_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_IIR_ALL_INSTANCE(Instance));

    /* Disable IIR */
    __LL_IIR_DISABLE(Instance);

    /* Handle Something */
    LL_IIR_MspDeInit(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Initializes the IIR MSP.
  * @param  Instance IIR peripheral
  * @return None
  */
__WEAK void LL_IIR_MspInit(IIR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_IIR_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the IIR MSP
  * @param  Instance IIR peripheral
  * @return None
  */
__WEAK void LL_IIR_MspDeInit(IIR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_IIR_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup IIR_LL_Exported_Functions_Group2 IIR Peripheral Control functions
  * @brief    IIR Peripheral Control functions
@verbatim
  ===============================================================================
                  ##### Peripheral Control functions #####
  ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the IIR control registers
      (+) Configure the IIR preload control registers

@endverbatim
  * @{
  */

/**
  * @brief  Configures the IIR filter
  * @param  Instance IIR peripheral.
  * @param  Config   pointer to a IIR_ConfigTypeDef structure that contains
  *         the configuration information for the specified IIR peripheral.
  * @return status of the configuration
  */
LL_StatusETypeDef LL_IIR_FilterConfig(IIR_TypeDef *Instance, IIR_ConfigTypeDef *Config)
{
    /* Check the parameters */
    assert_param(IS_IIR_ALL_INSTANCE(Instance));
    assert_param(IS_IIR_INPUT_DATA_SCALE(Config->InDataScale));
    assert_param(IS_IIR_OUTPUT_DATA_SCALE(Config->OutDataScale));
    assert_param(IS_IIR_FEEDBACK_SCALE(Config->FeedBackScale));

    /* IIR Scale configure : Output data scale, Input data scale and Feedback scale */
    WRITE_REG(Instance->SCALR, (((uint32_t)(Config->InDataScale     << IIR_SCALR_DISCAL_Pos))  |
                                ((uint32_t)(Config->FeedBackScale   << IIR_SCALR_FBSCAL_Pos))  |
                                ((uint32_t)(Config->OutDataScale    << IIR_SCALR_DOSCAL_Pos))));

    /* IIR Data Input Address */
    WRITE_REG(Instance->DIAR, Config->InDataAddress);

    /* fill the coefficients */
    for (int idx = 0;  idx < ARRAY_SIZE(Config->AxCOEF); idx++) {
        WRITE_REG(Instance->AxCOEFR[idx], ((uint32_t)(Config->AxCOEF[idx]) & IIR_AxCOEFR_AxCOEF_Msk));
    }

    for (int idx = 0;  idx < ARRAY_SIZE(Config->BxCOEF); idx++) {
        WRITE_REG(Instance->BxCOEFR[idx], ((uint32_t)(Config->BxCOEF[idx]) & IIR_BxCOEFR_BxCOEF_Msk));
    }

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Configures the IIR filter preload registers
  * @note   This function is related to IIR Auto-Reload feature.
  *         Using __LL_IIR_AUTORELAOD_ENABLE() will auto-reload this configures.
  *         Using LL_IIR_FilterStart[_IT]() will auto-reload this configures(with AutoReload enabled) then start an IIR filter.
  * @param  Instance IIR peripheral.
  * @param  Config   pointer to a IIR_ConfigTypeDef structure that contains
  *         the configuration information for the specified IIR peripheral.
  * @return status of the configuration
  */
LL_StatusETypeDef LL_IIR_FilterConfig_Preload(IIR_TypeDef *Instance, IIR_ConfigTypeDef *Config)
{
    /* Check the parameters */
    assert_param(IS_IIR_ALL_INSTANCE(Instance));
    assert_param(IS_IIR_INPUT_DATA_SCALE(Config->InDataScale));
    assert_param(IS_IIR_OUTPUT_DATA_SCALE(Config->OutDataScale));
    assert_param(IS_IIR_FEEDBACK_SCALE(Config->FeedBackScale));

    /* IIR Scale configure : Output data scale, Input data scale and Feedback scale */
    WRITE_REG(Instance->SCALSR, (((uint32_t)(Config->InDataScale     << IIR_SCALSR_DISCALS_Pos))  |
                                 ((uint32_t)(Config->FeedBackScale   << IIR_SCALSR_FBSCALS_Pos))  |
                                 ((uint32_t)(Config->OutDataScale    << IIR_SCALSR_DOSCALS_Pos))));

    /* IIR Data Input Address */
    WRITE_REG(Instance->DIASR, Config->InDataAddress);

    /* fill the coefficients */
    for (int idx = 0;  idx < ARRAY_SIZE(Config->AxCOEF); idx++) {
        WRITE_REG(Instance->AxCOEFSR[idx], ((uint32_t)(Config->AxCOEF[idx]) & IIR_AxCOEFSR_AxCOEFS_Msk));
    }

    for (int idx = 0;  idx < ARRAY_SIZE(Config->BxCOEF); idx++) {
        WRITE_REG(Instance->BxCOEFSR[idx], ((uint32_t)(Config->BxCOEF[idx]) & IIR_BxCOEFSR_BxCOEFS_Msk));
    }

    /* Return function status */
    return LL_OK;
}

/**
  * @}
  */


/** @defgroup IIR_LL_Exported_Functions_Group3 IIR Input and Output operation functions
  * @brief    IIR Input and Output operation functions
@verbatim
  ===============================================================================
                  ##### Input and Output operation functions #####
  ===============================================================================
  [..]
    This section provides functions allowing to:
    (+) start and stop functions.
    (+) start and stop with interrupt functions.
    (+) get output data function.
    (+) reset internal buffer function.

@endverbatim
  * @{
  */

/**
  * @brief  Start an IIR Filter for current input data
  * @param  Instance IIR peripheral.
  * @param  AutoReload specifies IIR Auto-Reload the preloaded configures or not.
  *         This parameter can be one of the following values:
  *           @arg IIR_AUTORELOAD_DISABLE: Disable Auto-Reload feature.
  *           @arg IIR_AUTORELOAD_ENABLE: Auto-Reload the preload configures before starting IIR filter.
  * @note   The preloaded configures should be configured by calling LL_IIR_FilterConfig_Preload() function,
  *         before enable Auto-Reload feature.
  * @return LL status
  */
LL_StatusETypeDef LL_IIR_FilterStart(IIR_TypeDef *Instance, IIR_ATReloadETypeDef AutoReload)
{
    /* Check the parameters */
    assert_param(IS_IIR_ALL_INSTANCE(Instance));

    /* Configure the Auto-Reload feature before start the IIR filter */
    if (AutoReload != IIR_AUTORELOAD_DISABLE) {
        __LL_IIR_AUTORELOAD_ENABLE(Instance);
    }

    /* Start the IIR filter */
    __LL_IIR_FILTER_START(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Start an IIR Filter for current input data with interrupt
  * @param  Instance IIR peripheral.
  * @param  AutoReload specifies IIR Auto-Reload the preloaded configures or not.
  *         This parameter can be one of the following values:
  *           @arg IIR_AUTORELOAD_DISABLE: Disable Auto-Reload feature.
  *           @arg IIR_AUTORELOAD_ENABLE: Auto-Reload the preload configures before starting IIR filter.
  * @note   The preloaded configures should be configured by calling LL_IIR_FilterConfig_Preload() function,
  *         before enable Auto-Reload feature
  * @return LL status
  */
LL_StatusETypeDef LL_IIR_FilterStart_IT(IIR_TypeDef *Instance, IIR_ATReloadETypeDef AutoReload)
{
    /* Check the parameters */
    assert_param(IS_IIR_ALL_INSTANCE(Instance));

    /* Enable IIR interrupt */
    __LL_IIR_ENABLE_IT(Instance, IIR_IT_FDIE);

    /* Configure the Auto-Reload feature before start the IIR filter */
    if (AutoReload != IIR_AUTORELOAD_DISABLE) {
        __LL_IIR_AUTORELOAD_ENABLE(Instance);
    }

    /* Start the IIR filter */
    __LL_IIR_FILTER_START(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Get the latest IIR filter output data
  * @param  Instance IIR peripheral.
  * @return IIR filter output data
  */
int16_t LL_IIR_FilterDataGet(IIR_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_IIR_ALL_INSTANCE(Instance));

    /* Return the IIR filter output data */
    return (int16_t)(READ_REG(Instance->DOR) & 0xFFFFUL);
}

/**
  * @brief  Reset the IIR internal data buffer.
  * @param  Instance IIR peripheral.
  * @return LL status
  */
LL_StatusETypeDef LL_IIR_FilterBufferReset(IIR_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_IIR_ALL_INSTANCE(Instance));

    /* IIR Internal Buffer Reset control */
    __LL_IIR_FILTER_BUFFER_RESET(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @}
  */


/** @defgroup IIR_LL_Exported_Functions_Interrupt IIR Initerrupt management
  * @brief    IIR Initerrupt management
@verbatim
  ===============================================================================
                        ##### Initerrupt management #####
  ===============================================================================
  [..]
      This section provides IIR interrupt handler and callback functions.

@endverbatim
  * @{
  */

/**
  * @brief  This function handles IIR interrupts requests.
  * @param  Instance IIR peripheral
  * @return None
  */
void LL_IIR_IRQHandler(IIR_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_IIR_ALL_INSTANCE(Instance));

    if ((__LL_IIR_IT_CHECK_SOURCE(Instance, IIR_IT_FDIE) != RESET) && (__LL_IIR_GET_FLAG(Instance, IIR_FLAG_FDIF) != RESET)) {
        /* Clear the FDIF interrupt flag */
        __LL_IIR_CLEAR_FLAG(Instance, IIR_FLAG_FDIF);

        /* IIR Fliter done callback */
        LL_IIR_FilterDoneCallBack(Instance);
    }
}
/**
  * @brief  IIR Fliter done callback
  * @param  Instance IIR peripheral
  * @return None
  */
__WEAK void LL_IIR_FilterDoneCallBack(IIR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_IIR_FilterDoneCallBack could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


#endif /* LL_GPIO_MODULE_ENABLE */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

