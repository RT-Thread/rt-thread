/**
  ******************************************************************************
  * @file    tae32f53xx_ll_tmr.c
  * @author  MCD Application Team
  * @brief   TMR LL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Timer (TMR) peripheral:
  *           + TMR Time Initialization and De-Initialization function
  *           + TMR Input Capture and Output Compare configure functions
  *           + TMR Start and Stop functions
  *           + TMR event software generate function
  *           + TMR internal trigger signal configure function
  *           + TMR interrupt handler and callback functions
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


#define DBG_TAG             "TMR LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup TMR_LL TMR LL
  * @brief    TMR LL module driver.
  * @{
  */

#ifdef LL_TMR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup TMR_LL_Private_Functions TMR LL Private Functions
  * @brief    TMR LL Private Functions
  * @{
  */
static void TMR_TB_SetConfig(TMR_TypeDef *Instance, TMR_TB_InitTypeDef *Config);
static void TMR_IC_SetConfig(TMR_TypeDef *Instance, TMR_IC_InitTypeDef *Config);
static void TMR_OC_SetConfig(TMR_TypeDef *Instance, TMR_OC_InitTypeDef *Config);
static void TMR_EXT_SetConfig(TMR_TypeDef *Instance, TMR_EXT_InitTypeDef *Config);
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup TMR_LL_Exported_Functions TMR LL Exported Functions
  * @brief    TMR LL Exported Functions
  * @{
  */

/** @defgroup TMR_LL_Exported_Functions_Group1 Initialization and De-Initialization functions
  * @brief    Initialization and De-Initialization functions
@verbatim
  ==============================================================================
              ##### Initialization and De-Initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the TMR base unit.
    (+) De-initialize the TMR base unit.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the TMR peripheral
  * @param  Instance TMR peripheral instance
  * @param  Init pointer to a TMR_InitTypeDef structure that contains the configuration
  *         information for the specified TMR peripheral.
  * @note   InputCapture and OutputCompare feature must NOT be enabled at the same time
  *         in one single TMR peripheral.
  * @return status of the initialization
  */
LL_StatusETypeDef LL_TMR_Init(TMR_TypeDef *Instance, TMR_InitTypeDef *Init)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(Init != NULL);
    /* Input Capture and Output Compare can not be enabled in one TMR at the same time */
    assert_param(!((Init->ICInit.ICEnable == ENABLE) && (Init->OCInit.OCEnable == ENABLE)));

    /* Handle Something */
    LL_TMR_MspInit(Instance);

    /* Disable Capture/Compare before initialization */
    __LL_TMR_CC_DISABLE(Instance);

    /* Stop Counter before initialization */
    __LL_TMR_DISABLE(Instance);

    /* Set configuration to TimeBase unit */
    TMR_TB_SetConfig(Instance, &Init->TBInit);

    /* Set configuration for Input Capture feature */
    TMR_IC_SetConfig(Instance, &Init->ICInit);

    /* Set configuration for Output Compare feature */
    TMR_OC_SetConfig(Instance, &Init->OCInit);

    /* Set configuration for Export Trigger Event feature */
    TMR_EXT_SetConfig(Instance, &Init->ExtInit);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  DeInitializes the timer
  * @param  Instance TMR peripheral instance
  * @return status of the initialization
  */
LL_StatusETypeDef LL_TMR_DeInit(TMR_TypeDef *Instance)
{
    /* Check the TMR initiation struct allocation */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    /* Stop Counter */
    __LL_TMR_DISABLE(Instance);

    /* Disable Capture Compare feature */
    __LL_TMR_CC_DISABLE(Instance);

    /* Disable TMR export trigger event feature */
    WRITE_REG(Instance->ETER, 0);

    /* Handle Something */
    LL_TMR_MspDeInit(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Initializes the TMR MSP.
  * @param  Instance TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_MspInit(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the TMR MSP
  * @param  Instance TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_MspDeInit(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup TMR_LL_Exported_Functions_Group2 TMR Peripheral Control functions
  * @brief    TMR Peripheral Control functions
@verbatim
  ===============================================================================
                       ##### Peripheral Control functions #####
  ===============================================================================
  [..]
    This section provides functions allowing to:
    (+) TMR Input-Capture configure functions
    (+) TMR Output-Compare configure functions

@endverbatim
  * @{
  */

/**
  * @brief  User can use this function to reconfigure the TMR TimeBase unit
  *         according to the specified parameters in the TMR_TB_InitTypeDef on runtime.
  * @param  Instance TMR peripheral instance
  * @param  Config TMR TimeBase Unit configuration structure
  * @return status of the initialization
  */
LL_StatusETypeDef LL_TMR_TB_Config(TMR_TypeDef *Instance, TMR_TB_InitTypeDef *Config)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(Config != NULL);

    /* Set configuration to TimeBase unit */
    TMR_TB_SetConfig(Instance, Config);

    /* Return function status */
    return LL_OK;
}


/**
  * @brief  User can use this function to reconfigure the TMR Input Capture feature
  *         according to the specified parameters in the TMR_IC_InitTypeDef on runtime.
  * @note   Use LL_TMR_CC_ENABLE() or LL_TMR_CC_DISABLE() macros to enable or disable
  *         the Capture Compare feature.
  * @param  Instance TMR peripheral
  * @param  Config TMR Input Capture configuration structure
  * @return status of the configuration
  */
LL_StatusETypeDef LL_TMR_IC_Config(TMR_TypeDef *Instance, TMR_IC_InitTypeDef *Config)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(Config != NULL);

    /* Disable CCE before configuration */
    CLEAR_BIT(Instance->CCCR, TMR_CCCR_CCE);

    /* Set configuration for Input Capture feature */
    TMR_IC_SetConfig(Instance, Config);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  User can use this function to reconfigure the TMR Output Compare feature
  *         according to the specified parameters in the TMR_OC_InitTypeDef on runtime.
  * @note   Use LL_TMR_CC_ENABLE() or LL_TMR_CC_DISABLE() macros to enable or disable
  *         the Capture Compare feature.
  * @param  Instance  TMR peripheral
  * @param  Config TMR Output Compare configuration structure.
  * @return status of the configuration
  */
LL_StatusETypeDef LL_TMR_OC_Config(TMR_TypeDef *Instance, TMR_OC_InitTypeDef *Config)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(Config != NULL);

    /* Disable CCE before configuration */
    CLEAR_BIT(Instance->CCCR, TMR_CCCR_CCE);

    /* Set configuration for Output Compare feature */
    TMR_OC_SetConfig(Instance, Config);

    /* Return function status */
    return LL_OK;

}

/**
  * @brief  User can use this function to reconfigure the TMR Export Trigger Event feature
  *         according to the specified parameters in the TMR_EXT_InitTypeDef on runtime.
  * @param  Instance TMR peripheral
  * @param  Config TMR Export Trigger configuration structure.
  * @note   Please notice if user want to enable or disable the TMR events as the internal signal,
  *         this configuration function should be called to config the specified events.
  * @return status of the configuration
  */
LL_StatusETypeDef LL_TMR_EXT_Config(TMR_TypeDef *Instance, TMR_EXT_InitTypeDef *Config)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(Config != NULL);

    /* Set configuration for Export Trigger Event feature */
    TMR_EXT_SetConfig(Instance, Config);

    /* Return function status */
    return LL_OK;
}

/**
  * @}
  */


/** @defgroup TMR_LL_Exported_Functions_Group3 TMR Input and Output operation functions
  * @brief    TMR Input and Output operation functions
@verbatim
  ===============================================================================
                  ##### Input and Output operation functions #####
  ===============================================================================
  [..]
    This section provides functions allowing to:
    (+) TMR Start and Stop functions
    (+) TMR Synchro start function
    (+) TMR event software generate function

@endverbatim
  * @{
  */

/**
  * @brief  Start the Timer.
  * @param  Instance TMR peripheral
  * @return LL status
  */
LL_StatusETypeDef LL_TMR_Start(TMR_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    /* Start Counter*/
    __LL_TMR_ENABLE(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Stop the Timer.
  * @param  Instance TMR peripheral
  * @return LL status
  */
LL_StatusETypeDef LL_TMR_Stop(TMR_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    /* Stop Counter */
    __LL_TMR_DISABLE(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Start the timer with interrupt enabled
  * @param  Instance TMR peripheral
  * @return LL status
  */
LL_StatusETypeDef LL_TMR_Start_IT(TMR_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    if ((Instance->CR & TMR_CR_UDIS_Msk) != TMR_CR_UDIS) {
        /* TMR Update Interrupt Enable if Update event is enabled */
        __LL_TMR_IT_ENABLE(Instance, TMR_IT_UIE);
    }

    /* Check if Capture Compare mode is enabled */
    if ((Instance->CCCR & TMR_CCCR_CCE_Msk) == TMR_CCCR_CCE) {
        if ((Instance->CCCR & TMR_CCCR_CCS_Msk) == TMR_CCCR_CCS) {
            /* Enable Input Capture interrupt source */
            __LL_TMR_CC_IT_ENABLE(Instance, TMR_IT_ICIE | TMR_IT_ICOIE);
        } else {
            /* Enable Output Compare interrupt source */
            __LL_TMR_CC_IT_ENABLE(Instance, TMR_IT_OCIE);
        }
    }

    /* TMR Counter Overflow Interrupt Enable */
    __LL_TMR_IT_ENABLE(Instance, TMR_IT_OVIE);

    /* Start Counter */
    __LL_TMR_ENABLE(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Stop the timer with interrupt disabled
  * @param  Instance TMR peripheral
  * @return LL status
  */
LL_StatusETypeDef LL_TMR_Stop_IT(TMR_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    /* TMR Update and Counter Overflow Interrupt Disable */
    __LL_TMR_IT_DISABLE(Instance, TMR_IT_UIE | TMR_IT_OVIE);

    /* Capture Compare interrupt disable */
    __LL_TMR_CC_IT_DISABLE(Instance, (TMR_IT_ICIE     |
                                      TMR_IT_ICOIE |
                                      TMR_IT_OCIE));

    /* Stop Counter */
    __LL_TMR_DISABLE(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Synchro Start the specifies timers.
  * @param  TMRGRPx TMRGRP peripheral
  *           @arg TMRGRP0: Group of LSTMRs(TMR0/1/2/3)
  *           @arg TMRGRP1: Group of HSTMRs(TMR4/5/6/7)
  * @param  SynchroMask Specifies timer masks to start synchronously. This parameter can be
  *         any combination of @ref TMRGRP_Sync_definition :
  *           @arg TMRGRP_SYNC_TMR0 : Select TMR0(specific to TMRGRP0)
  *           @arg TMRGRP_SYNC_TMR1 : Select TMR1(specific to TMRGRP0)
  *           @arg TMRGRP_SYNC_TMR2 : Select TMR2(specific to TMRGRP0)
  *           @arg TMRGRP_SYNC_TMR3 : Select TMR3(specific to TMRGRP0)
  *           @arg TMRGRP_SYNC_TMR4 : Select TMR4(specific to TMRGRP1)
  *           @arg TMRGRP_SYNC_TMR5 : Select TMR5(specific to TMRGRP1)
  *           @arg TMRGRP_SYNC_TMR6 : Select TMR6(specific to TMRGRP1)
  *           @arg TMRGRP_SYNC_TMR7 : Select TMR7(specific to TMRGRP1)
  *           @arg TMRGRP_SYNC_ALL  : Select all TMRs in TMRGRPx(x = 0 or 1)
  * @note   Please notice that only timers in same group can be started synchronously.
  *         For example for TMRGRP0, SynchroMask of the TMR0/1/2/3 will be started synchronously.
  * @note   If user wants to use it with specifies timers' interrupt enabled, use __LL_TMR_IT_ENABLE()
  *         and __LL_TMR_CC_IT_ENABLE() to enable the necessary interrupt sources before starting them.
  * @return LL status
  */
LL_StatusETypeDef LL_TMR_Start_Synchro(TMRGRP_TypeDef *TMRGRPx, uint32_t SynchroMask)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_TMRGRP_INSTANCE(TMRGRPx));

    /* Start specifies timers synchronously */
    WRITE_REG(TMRGRPx->SYNCR, SynchroMask);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Synchro Stop the specifies timers.
  * @param  TMRGRPx TMRGRP peripheral
  *           @arg TMRGRP0: Group of LSTMRs(TMR0/1/2/3)
  *           @arg TMRGRP1: Group of HSTMRs(TMR4/5/6/7)
  * @param  SynchroMask Specifies timer masks to stop synchronously. This parameter can be
  *         any combination of @ref TMRGRP_Sync_definition :
  *           @arg TMRGRP_SYNC_TMR0 : Select TMR0(specific to TMRGRP0)
  *           @arg TMRGRP_SYNC_TMR1 : Select TMR1(specific to TMRGRP0)
  *           @arg TMRGRP_SYNC_TMR2 : Select TMR2(specific to TMRGRP0)
  *           @arg TMRGRP_SYNC_TMR3 : Select TMR3(specific to TMRGRP0)
  *           @arg TMRGRP_SYNC_TMR4 : Select TMR4(specific to TMRGRP1)
  *           @arg TMRGRP_SYNC_TMR5 : Select TMR5(specific to TMRGRP1)
  *           @arg TMRGRP_SYNC_TMR6 : Select TMR6(specific to TMRGRP1)
  *           @arg TMRGRP_SYNC_TMR7 : Select TMR7(specific to TMRGRP1)
  *           @arg TMRGRP_SYNC_ALL  : Select all TMRs in TMRGRPx(x = 0 or 1)
  * @note   Please notice that only timers in same group can be stopped synchronously.
  *         For example for TMRGRP0, SynchroMask of the TMR0/1/2/3 will be stopped synchronously.
  * @return LL status
  */
LL_StatusETypeDef LL_TMR_Stop_Synchro(TMRGRP_TypeDef *TMRGRPx, uint32_t SynchroMask)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_TMRGRP_INSTANCE(TMRGRPx));

    /* Stop specifies timers synchronously */
    WRITE_REG(TMRGRPx->SYNCR, SynchroMask << 4);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Generate a software event
  * @param  Instance TMR peripheral
  * @param  EventSource specifies the event source.
  *          This parameter can be one of the following values in @ref TMR_Event_Source:
  *            @arg TMR_EVENTSOURCE_UG: Reinitialize the counter and generates an update of the registers
  *            @arg TMR_EVENTSOURCE_CCG: Generate a capture/compare event
  * @return LL status
  */
LL_StatusETypeDef LL_TMR_EventGenerate(TMR_TypeDef *Instance, TMR_EventSRCETypeDef EventSource)
{
    /* Check the TMR initiation struct allocation */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    /* Generation Timer Counter Update Event */
    WRITE_REG(Instance->EGR, EventSource);

    /* Return function status */
    return LL_OK;
}

/**
  * @}
  */


/** @defgroup TMR_LL_Exported_Functions_Interrupt TMR Interrupt management
  * @brief    TMR Initerrupt management
@verbatim
  ===============================================================================
                          ##### Initerrupt management #####
  ===============================================================================
  [..]
      This section provides TMR interrupt handler and callback functions.

@endverbatim
  * @{
  */

/**
  * @brief   This function handles TMR interrupts requests.
  * @param   Instance TMR peripheral
  * @return  None
  */
void LL_TMR_IRQHandler(TMR_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    if ((__LL_TMR_IT_CHECK_SOURCE(Instance, TMR_IT_UIE) != RESET) &&
        (__LL_TMR_GET_FLAG(Instance, TMR_FLAG_UIF) != RESET)) {
        /* Clear the Update interrupt flag */
        __LL_TMR_CLEAR_FLAG(Instance, TMR_FLAG_UIF);

        /* TMR Update Interrupt Callback */
        LL_TMR_TB_UpdateCallback(Instance);
    }

    if ((__LL_TMR_IT_CHECK_SOURCE(Instance, TMR_IT_OVIE) != RESET) &&
        (__LL_TMR_GET_FLAG(Instance, TMR_FLAG_OVIF) != RESET)) {
        /* Claer the OverFlow interrupt flag */
        __LL_TMR_CLEAR_FLAG(Instance, TMR_FLAG_OVIF);

        /* TMR Counter Overflow Interrupt Callback */
        LL_TMR_TB_OverflowCallback(Instance);
    }

    if ((__LL_TMR_CC_IT_CHECK_SOURCE(Instance, TMR_IT_ICIE) != RESET) &&
        (__LL_TMR_GET_FLAG(Instance, TMR_FLAG_ICIF) != RESET)) {
        /* Claer the Capture interrupt flag */
        __LL_TMR_CLEAR_FLAG(Instance, TMR_FLAG_ICIF);

        /* TMR Input Capture Captured Interrupt Callback */
        LL_TMR_IC_CaptureCallback(Instance);
    }

    if ((__LL_TMR_CC_IT_CHECK_SOURCE(Instance, TMR_IT_ICOIE) != RESET) &&
        (__LL_TMR_GET_FLAG(Instance, TMR_FLAG_ICOIF) != RESET)) {
        /* Claer the OverCapture interrupt flag */
        __LL_TMR_CLEAR_FLAG(Instance, TMR_FLAG_ICOIF);

        /* Handle Something */
        LL_TMR_IC_OverCaptureCallback(Instance);
    }

    if ((__LL_TMR_CC_IT_CHECK_SOURCE(Instance, TMR_IT_OCIE) != RESET) &&
        (__LL_TMR_GET_FLAG(Instance, TMR_FLAG_OCIF) != RESET)) {

        /* Claer the Compare interrupt flag */
        __LL_TMR_CLEAR_FLAG(Instance, TMR_FLAG_OCIF);

        /* Handle Something*/
        LL_TMR_OC_CompareMatchedCallback(Instance);
    }
}

/**
  * @brief  TMR TimeBase unit (Counter) update interrupt callback function
  * @param  Instance TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_TB_UpdateCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_TB_UpdateCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR TimeBase unit (Counter) overflow interrupt callback function
  * @param  Instance TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_TB_OverflowCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_TB_OverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR input capture interrupt callback function
  * @param  Instance TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_IC_CaptureCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_IC_CaptureCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR input capture over-capture interrupt callback function
  * @param  Instance TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_IC_OverCaptureCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_IC_OverCaptureCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR output compare matched interrupt callback function
  * @param  Instance TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_OC_CompareMatchedCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_OC_CompareMatchedCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/
/** @addtogroup TMR_LL_Private_Functions
  * @{
  */

/**
  * @brief  Set Configuration to TimeBase Unit.
  * @param  Instance TMR peripheral instance
  * @param  Config TMR TimeBase Unit configuration structure
  * @return None
  */
static void TMR_TB_SetConfig(TMR_TypeDef *Instance, TMR_TB_InitTypeDef *Config)
{
    if (IS_TMR_LSTMR_INSTANCE(Instance)) {    /* Check if Low-Speed Timer instance */
        assert_param(IS_TMR_LSTMR_PRESCALER(Config->Prescaler));
        assert_param(IS_TMR_LSTMR_END_VAL(Config->EndValue));
        assert_param(IS_TMR_LSTMR_START_VAL(Config->StartValue));
    } else {    /* High-Speed Timer instance */
        assert_param(IS_TMR_HSTMR_PRSCALER(Config->Prescaler));
        assert_param(IS_TMR_HSTMR_END_VAL(Config->EndValue));
        assert_param(IS_TMR_HSTMR_START_VAL(Config->StartValue));
    }

    /* Set the Counter Start value*/
    WRITE_REG(Instance->CSVR, Config->StartValue);

    /* Set the Counter End value*/
    WRITE_REG(Instance->CEVR, Config->EndValue);

    /* Set the Prescaler value*/
    WRITE_REG(Instance->PSCR, Config->Prescaler);

    /* Configures: Clock source, Auto-Reload preload, Continuous mode, Update enable and
       Update request source */
    WRITE_REG(Instance->CR, (Config->ClockSource | Config->AutoReloadPreload | Config->ContinuousMode |
                             Config->UpdateSource | Config->UpdateEnable));
}

/**
  * @brief  Set Configuration for Input Capture feature.
  * @param  Instance TMR peripheral instance
  * @param  sConfig TMR Input Capture configuration structure
  * @return None
  */
static void TMR_IC_SetConfig(TMR_TypeDef *Instance, TMR_IC_InitTypeDef *sConfig)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    /* Check if enable the input capture feature.
       Note: To do that TMR clock source must be configured to internal source */
    if ((sConfig->ICEnable == ENABLE) && (READ_BIT(Instance->CR, TMR_CR_CKSRC_Msk) == TMR_CLKSOURCE_INTERNAL)) {
        assert_param(IS_TMR_ICFILTER(sConfig->ICFilter));

        /* Set Input Capture filter */
        WRITE_REG(Instance->ICFR, sConfig->ICFilter);

        /* Configurate the TMRx_CCCR register */
        MODIFY_REG(Instance->CCCR,
                   (TMR_CCCR_ICSRC_Msk
                    | TMR_CCCR_CCP_Msk),
                   (TMR_CCCR_CCS
                    | sConfig->ICSelection
                    | sConfig->ICPolarity));

        /* Set CCE to enable the input-capture feature */
        SET_BIT(Instance->CCCR, TMR_CCCR_CCE);
    }
}

/**
  * @brief  Set Configuration for Output Compare feature.
  * @param  Instance TMR peripheral instance
  * @param  sConfig TMR Output Compare configuration structure
  * @return None
  */
static void TMR_OC_SetConfig(TMR_TypeDef *Instance, TMR_OC_InitTypeDef *sConfig)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    /* Check if enable the output compare feature.
       Note: To do that TMR clock source must be configured to internal source */
    if ((sConfig->OCEnable == ENABLE) && (READ_BIT(Instance->CR, TMR_CR_CKSRC_Msk) == TMR_CLKSOURCE_INTERNAL)) {
        if (IS_TMR_LSTMR_INSTANCE(Instance)) {
            assert_param(IS_TMR_LSTMR_COMPARE_VAL(sConfig->OCValue));
        } else {
            assert_param(IS_TMR_HSTMR_COMPARE_VAL(sConfig->OCValue));
        }

        /* Disable Output Preload feature before configuration */
        CLEAR_BIT(Instance->CCCR, TMR_CCCR_OCPE);

        /* Set Compare Value */
        WRITE_REG(Instance->CCR, sConfig->OCValue);

        /* Configurate the TMRx_CCCR register */
        MODIFY_REG(Instance->CCCR,
                   (TMR_CCCR_OCPE_Msk
                    | TMR_CCCR_CCS_Msk
                    | TMR_CCCR_OCM_Msk
                    | TMR_CCCR_CCP_Msk),
                   (sConfig->OCMode
                    | sConfig->OCPolarity
                    | sConfig->OCPreload));

        /* Set CCE to enable the input-capture feature */
        SET_BIT(Instance->CCCR, TMR_CCCR_CCE);
    }
}

/**
  * @brief  Set Configuration for TMR Export Trigger Event feature.
  * @param  Instance TMR peripheral
  * @param  Config TMR Export Trigger configuration structure.
  * @return None
  */
static void TMR_EXT_SetConfig(TMR_TypeDef *Instance, TMR_EXT_InitTypeDef *sConfig)
{
    /* Check the parameters */
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    if (sConfig->ExtEnable == ENABLE) {
        /* Configure the events */
        MODIFY_REG(Instance->ETER,
                   (TMR_ETER_CCTPW_Msk
                    | TMR_ETER_UTPW_Msk
                    | TMR_ETER_PWMOE_Msk
                    | TMR_ETER_CCTE_Msk
                    | TMR_ETER_UTE_Msk),
                   ((0xFU << TMR_ETER_CCTPW_Pos) |
                    (0xFU << TMR_ETER_UTPW_Pos)
                    | sConfig->ExtPWMWave
                    | sConfig->ExtCCTrigger
                    | sConfig->ExtTRGOTrigger));
    } else {
        WRITE_REG(Instance->ETER, 0);
    }
}

/**
  * @}
  */


#endif /* LL_TMR_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

