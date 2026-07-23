/**
  ******************************************************************************
  * @file    tae32f53xx_ll_cmp.c
  * @author  MCD Application Team
  * @brief   Source file for CMP Moudle
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


#define DBG_TAG             "CMP LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup CMP_LL CMP LL
  * @brief    CMP LL module driver.
  * @{
  */

#ifdef LL_CMP_MODULE_ENABLED

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup CMP_LL_Exported_Functions CMP LL Exported Functions
  * @brief    CMP LL Exported Functions
  * @{
  */

/** @defgroup CMP_LL_Exported_Functions_Group1 Initialization and De-Initialization functions
  * @brief    Initialization and De-Initialization functions
@verbatim
  ==============================================================================
              ##### Initialization and De-Initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize the CMP peripheral.
    (+) De-initialize the CMP peripheral.
@endverbatim
  * @{
  */

/**
  * @brief  Initialize the CMP peripheral
  * @param  Instance CMP peripheral instance
  * @return status of the initialization
  */
LL_StatusETypeDef LL_CMP_Init(CMP_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_CMP_ALL_INSTANCE(Instance));

    /* Init the low level hardware */
    LL_CMP_MspInit(Instance);

    /* Clear interrupt pending flags */
    __LL_CMP_PENDING_FLAG_CLEAR(Instance, CMP_FLAG_ALLIF);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Deinitialize the CMP peripheral
  * @param  Instance CMP peripheral instance
  * @return status of the initialization
  */
LL_StatusETypeDef LL_CMP_DeInit(CMP_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_CMP_ALL_INSTANCE(Instance));

    for (uint8_t chnnum = 0; chnnum < CMP_CHN_NB; ++chnnum) {
        /* Disable CMP channel FALIE/RISIE interrupts */
        __LL_CMP_IT_DISABLE(Instance, chnnum, CMP_IT_FALIE | CMP_IT_RISIE);

        /* Disable CMP channel */
        __LL_CMP_DISABLE(Instance, chnnum);
    }

    /* DeInit the low level hardware */
    LL_CMP_MspDeInit(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Initializes the CMP MSP.
  * @param  Instance CMP peripheral
  * @return None
  */
__WEAK void LL_CMP_MspInit(CMP_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_CMP_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the CMP MSP
  * @param  Instance CMP peripheral
  * @return None
  */
__WEAK void LL_CMP_MspDeInit(CMP_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CMP_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup CMP_LL_Exported_Functions_Group2 CMP Peripheral Control functions
  * @brief    CMP Peripheral Control functions
@verbatim
  ===============================================================================
                       ##### Peripheral Control functions #####
  ===============================================================================
  [..] This section provides functions allowing to:
    (+) Configure CMP channels.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the selected CMP channel.
  * @param  Instance CMP peripheral
  * @param  Channel The selected CMP channel.
  *         This parameter can be one of the following values:
  *            @arg CMP_CHANNEL_0: CMP Channel0 selected
  *            @arg CMP_CHANNEL_1: CMP Channel1 selected
  *            @arg CMP_CHANNEL_2: CMP Channel2 selected
  *            @arg CMP_CHANNEL_3: CMP Channel3 selected
  * @param  sConfig CMP configuration structure.
  * @return LL Status
  */
LL_StatusETypeDef LL_CMP_ChannelConfig(CMP_TypeDef *Instance, uint32_t Channel, CMP_ChannelConfTypeDef *sConfig)
{
    /* Get the channel number */
    uint8_t chnnum = POSITION_VAL(Channel);

    /* Check the parameters */
    assert_param(IS_CMP_ALL_INSTANCE(Instance));
    assert_param(IS_CMP_CHANNEL(Channel));
    assert_param(IS_CMP_NUMBER(chnnum));
    assert_param(sConfig != NULL);
    assert_param(IS_CMP_INPUT_MINUS(sConfig->InputMinus));
    assert_param(IS_CMP_HYSTERESIS(sConfig->Hysteresis));
    assert_param(IS_CMP_BLANKING_SOURCE(Channel, sConfig->BlankingSource));
    assert_param(IS_CMP_OUTPUT_DEBOUNCE(sConfig->OutputDebounce));
    assert_param(IS_CMP_OUTPUT_DEBOUNCE_VAL(sConfig->OutputDebounceValue));
    assert_param(IS_CMP_OUTPUT_POLARITY(sConfig->OutputPolarity));
    assert_param(IS_CMP_TRIGGER_IT(sConfig->TriggerInterrupt));

    /* Set Debounce Vaule */
    if (sConfig->OutputDebounceValue == CMP_OUTPUT_DEBOUNCE_ENABLE) {
        __LL_CMP_DEBOUNCE_VALUE_SET(Instance, chnnum, sConfig->OutputDebounceValue);
    }

    /* Reset and Calculate CR register value depending on sConfig */
    MODIFY_REG(Instance->CR[chnnum],
               (CMP_CR_OPOL_Msk
                | CMP_CR_ODEB_Msk
                | CMP_CR_BLANKING_Msk
                | CMP_CR_INM_Msk
                | CMP_CR_HYST_Msk
                | CMP_CR_FALIE_Msk
                | CMP_CR_RISIE_Msk
               ),
               (sConfig->OutputPolarity
                | sConfig->OutputDebounce
                | sConfig->BlankingSource
                | sConfig->InputMinus
                | sConfig->Hysteresis
                | sConfig->TriggerInterrupt));

    /* Return function status */
    return LL_OK;
}

/**
  * @}
  */


/** @defgroup CMP_LL_Exported_Functions_Group3 CMP IO operation functions
  * @brief    CMP IO operation functions
  *
@verbatim
  ==============================================================================
             ##### IO operation functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Start/Stop CMP.

@endverbatim
  * @{
  */

/**
  * @brief  Enables CMP Channel conversion
  * @param  Instance CMP peripheral instance
  * @param  Channel The selected CMP channel.
  *         This parameter can be one of the following values:
  *            @arg CMP_CHANNEL_0: CMP Channel0 selected
  *            @arg CMP_CHANNEL_1: CMP Channel1 selected
  *            @arg CMP_CHANNEL_2: CMP Channel2 selected
  *            @arg CMP_CHANNEL_3: CMP Channel3 selected
  * @return LL Status
  */
LL_StatusETypeDef LL_CMP_Start(CMP_TypeDef *Instance, uint32_t Channel)
{
    /* Get the channel number */
    uint8_t chnnum = POSITION_VAL(Channel);

    /* Check the parameters */
    assert_param(IS_CMP_ALL_INSTANCE(Instance));
    assert_param(IS_CMP_CHANNEL(Channel));
    assert_param(IS_CMP_NUMBER(chnnum));

    /* Enable the CMP channel */
    __LL_CMP_ENABLE(Instance, chnnum);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Disable CMP Channel conversion
  * @param  Instance CMP peripheral instance
  * @param  Channel The selected CMP channel.
  *         This parameter can be one of the following values:
  *            @arg CMP_CHANNEL_0: CMP Channel0 selected
  *            @arg CMP_CHANNEL_1: CMP Channel1 selected
  *            @arg CMP_CHANNEL_2: CMP Channel2 selected
  *            @arg CMP_CHANNEL_3: CMP Channel3 selected
  * @return LL Status
  */
LL_StatusETypeDef LL_CMP_Stop(CMP_TypeDef *Instance, uint32_t Channel)
{
    /* Get the channel number */
    uint8_t chnnum = POSITION_VAL(Channel);

    /* Check the CMP parameters */
    assert_param(IS_CMP_ALL_INSTANCE(Instance));
    assert_param(IS_CMP_CHANNEL(Channel));
    assert_param(IS_CMP_NUMBER(chnnum));

    /* Enable CMP Channel */
    __LL_CMP_DISABLE(Instance, chnnum);

    /* Return function status */
    return LL_OK;
}

/**
  * @}
  */


/** @defgroup CMP_LL_Exported_Functions_Interrupt CMP Interrupt management
  * @brief    CMP Interrupt management
@verbatim
  ===============================================================================
                          ##### Initerrupt management #####
  ===============================================================================
  [..]
      This section provides CMP interrupt handler and callback functions.

@endverbatim
  * @{
  */

/**
  * @brief   This function handles CMP interrupts requests.
  * @param   Instance CMP peripheral
  * @return  None
  */
void LL_CMP_IRQHandler(CMP_TypeDef *Instance)
{
    uint32_t irqtemp = READ_REG(Instance->SR);

    /* Check the CMP parameters */
    assert_param(IS_CMP_ALL_INSTANCE(Instance));

    for (uint8_t chnnum = 0; chnnum < CMP_CHN_NB; ++chnnum) {
        if ((__LL_CMP_IT_CHECK_SOURCE(Instance, chnnum, CMP_IT_FALIE) != RESET) &&
            ((irqtemp & (CMP_SR_FALIF_0 << chnnum)) != RESET)) {
            /* Chear the CMP_CHx FALIF pending flag */
            __LL_CMP_PENDING_FLAG_CLEAR(Instance, (CMP_SR_FALIF_0 << chnnum));

            /* CMP falling edge trigger user callback */
            LL_CMP_FailingEdgeTrigCallback(Instance, (0x1UL << chnnum));
        }

        if ((__LL_CMP_IT_CHECK_SOURCE(Instance, chnnum, CMP_IT_RISIE) != RESET) &&
            ((irqtemp & (CMP_SR_RISIF_0 << chnnum)) != RESET)) {
            /* Chear the CMP_CHx RISIF pending flag */
            __LL_CMP_PENDING_FLAG_CLEAR(Instance, (CMP_SR_RISIF_0 << chnnum));

            /* CMP rising edge trigger user callback */
            LL_CMP_RisingEdgeTrigCallback(Instance, (0x1UL << chnnum));
        }
    }
}

/**
  * @brief  CMP_CHx failing edge interrupt callback function
  * @param  Instance CMP peripheral
  * @param  Channel The handling CMP channel
  * @return None
  */
__WEAK void LL_CMP_FailingEdgeTrigCallback(CMP_TypeDef *Instance, uint32_t Channel)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(Channel);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CMP_FailingEdgeTrigCallback could be implemented in the user file
     */
}

/**
  * @brief  CMP_CHx rising edge interrupt callback function
  * @param  Instance CMP peripheral
  * @param  Channel The handling CMP channel
  * @return None
  */
__WEAK void LL_CMP_RisingEdgeTrigCallback(CMP_TypeDef *Instance, uint32_t Channel)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(Channel);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CMP_RisingEdgeTrigCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

#endif /* LL_CMP_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

