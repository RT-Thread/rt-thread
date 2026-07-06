/**
  ******************************************************************************
  * @file    tae32f53xx_ll_dac.c
  * @author  MCD Application Team
  * @brief   Source file for DAC Module
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


#define DBG_TAG             "DAC LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup DAC_LL DAC LL
  * @brief    DAC LL module driver
  * @{
  */

#ifdef LL_DAC_MODULE_ENABLED

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Functions DAC LL Exported Functions
  * @brief    DAC LL Exported Functions
  * @{
  */

/** @defgroup DAC_LL_Exported_Functions_Group1 Initialization and De-Initialization functions
  * @brief    Initialization and De-Initialization functions

@verbatim
  ==============================================================================
              ##### Initialization and De-Initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize the DAC peripheral.
    (+) De-initialize the DAC peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the DAC peripheral
  * @param  Instance DAC peripheral instance
  * @return status of the initialization
  */
LL_StatusETypeDef LL_DAC_Init(DAC_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));

    /* Init the low level hardware */
    LL_DAC_MspInit(Instance);

    /* Clear interrupt pending flags */
    __LL_DAC_PENDING_FLAG_CLEAR(Instance, DAC_FLAG_ALLIF);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Deinitialize the DAC peripheral
  * @param  Instance DAC peripheral instance
  * @return status of the initialization
  */
LL_StatusETypeDef LL_DAC_DeInit(DAC_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));

    for (uint8_t chnnum = 0; chnnum < DAC_CHN_NB; ++chnnum) {
        /* Disable DAC Channel wave */
        CLEAR_BIT(Instance->CR[chnnum], DAC_CR_TGE_Msk | DAC_CR_STE_Msk);

        /* Disable DONE/DONEB interrupts */
        __LL_DAC_IT_DISABLE(Instance, chnnum, DAC_IT_DIE | DAC_IT_DBIE);

        /* Disable DAC Channel Output */
        __LL_DAC_OUTPUT_DISABLE(Instance, chnnum);

        /* Disable DAC Channel */
        __LL_DAC_DISABLE(Instance, chnnum);
    }

    /* DeInit the low level hardware */
    LL_DAC_MspDeInit(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Initializes the DAC MSP.
  * @param  Instance DAC peripheral
  * @return None
  */
__WEAK void LL_DAC_MspInit(DAC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_DAC_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the DAC MSP
  * @param  Instance DAC peripheral
  * @return None
  */
__WEAK void LL_DAC_MspDeInit(DAC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DAC_MspDeInit could be implemented in the user file
     */
}
/**
  * @}
  */


/** @defgroup DAC_LL_Exported_Functions_Group2 DAC Peripheral Control functions
  * @brief    DAC Peripheral Control functions
@verbatim
  ===============================================================================
                       ##### Peripheral Control functions #####
  ===============================================================================
  [..] This section provides functions allowing to:
    (+) Configure channels.
    (+) Sawtooth/Tranigle wave generate configure

@endverbatim
  * @{
  */

/**
  * @brief  Configures the selected DAC channel.
  * @param  Instance DAC peripheral
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_0: DAC Channel0 selected
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_3: DAC Channel3 selected
  * @param  sConfig DAC configuration structure.
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_ChannelConfig(DAC_TypeDef *Instance, uint32_t Channel, DAC_ChannelConfTypeDef *sConfig)
{
    /* Get the channel number */
    uint8_t chnnum = POSITION_VAL(Channel);

    /* Check the DAC parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(IS_DAC_CHANNEL(Channel));
    assert_param(IS_DAC_NUMBER(chnnum));
    assert_param(sConfig != NULL);
    assert_param(IS_DAC_CHANNEL_OUTPUT_SEL(sConfig->Output));
    assert_param(IS_DAC_CHANNEL_DONE_IT_PENDING_CFG(sConfig->DoneIntPending));
    assert_param(IS_DAC_CHANNEL_DONEB_IT_PENDING_CFG(sConfig->DoneBIntPending));

    /* Reset and Calculate CR register value depending on sConfig */
    MODIFY_REG(Instance->CR[chnnum],
               (DAC_CR_PEN_Msk   | DAC_CR_OEN_Msk
                | DAC_CR_TGE_Msk | DAC_CR_STE_Msk
                | DAC_CR_DIE_Msk | DAC_CR_DBIE_Msk),
               (sConfig->Output
                | sConfig->DoneIntPending
                | sConfig->DoneBIntPending));

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Enable the selected DAC channel sawtooth wave generation.
  * @param  Instance DAC peripheral
  * @param  Channel The selected DAC channel.
  * @param  sConfig DAC sawtooth configuration structure.
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_SawtoothWaveGenerate(DAC_TypeDef *Instance, uint32_t Channel, DAC_SawtoothConfTypeDef *sConfig)
{
    /* Get the channel number */
    uint8_t chnnum = POSITION_VAL(Channel);

    /* Check the DAC parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(IS_DAC_CHANNEL(Channel));
    assert_param(IS_DAC_NUMBER(chnnum));
    assert_param(sConfig != NULL);
    assert_param(IS_DAC_SAWTOOTH_RESET_DATA(sConfig->ResetData));
    assert_param(IS_DAC_SAWTOOTH_STEP_DATA(sConfig->StepData));
    assert_param(IS_DAC_SAWTOOTH_POLARITY(sConfig->Polarity));
    assert_param(IS_DAC_SAWTOOTH_RESET_TRIGGER(sConfig->ResetTrigger));
    assert_param(IS_DAC_SAWTOOTH_STEP_TRIGGER(sConfig->StepTrigger));
    assert_param(sConfig->StepTrigger != sConfig->ResetTrigger);

    /* Configure the sawtooth wave */
    MODIFY_REG(Instance->CR[chnnum],
               (DAC_CR_TGE_Msk
                | DAC_CR_STE_Msk
                | DAC_CR_STDIR_Msk
                | DAC_CR_STINCTRIG_Msk
                | DAC_CR_STRSTTRIG_Msk),
               (sConfig->Polarity
                | (sConfig->StepTrigger << DAC_CR_STINCTRIG_Pos)
                | (sConfig->ResetTrigger << DAC_CR_STRSTTRIG_Pos)));

    /* Configure the sawtooth wave generation data parameters */
    WRITE_REG(Instance->SIDR[chnnum], sConfig->StepData);
    WRITE_REG(Instance->SRDR[chnnum], sConfig->ResetData << 4);

    /* Enable sawtooth wave */
    SET_BIT(Instance->CR[chnnum], DAC_CR_STE);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Enable the selected DAC channel triangle wave generation.
  * @param  Instance DAC peripheral
  * @param  Channel The selected DAC channel.
  * @param  sConfig DAC triangle configuration structure.
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_TriangleWaveGenerate(DAC_TypeDef *Instance, uint32_t Channel, DAC_TriangleConfTypeDef *sConfig)
{
    /* Get the channel number */
    uint8_t chnnum = POSITION_VAL(Channel);

    /* Check the DAC parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(IS_DAC_CHANNEL(Channel));
    assert_param(IS_DAC_NUMBER(chnnum));
    assert_param(sConfig != NULL);
    assert_param(IS_DAC_TRIANGLE_INITIALDIRECTION(sConfig->InitialDirection));
    assert_param(IS_DAC_TRIANGLE_AMPLITUDE(sConfig->Amplitude));
    assert_param(IS_DAC_TRIANGLE_STEP_TRIGGER(sConfig->StepTrigger));

    /* Configure the triangle wave */
    MODIFY_REG(Instance->CR[chnnum],
               (DAC_CR_TGE_Msk
                | DAC_CR_STE_Msk
                | DAC_CR_TGDIR_Msk
                | DAC_CR_TGAMP_Msk
                | DAC_CR_TGTRIG_Msk),
               (sConfig->InitialDirection
                | sConfig->Amplitude
                | (sConfig->StepTrigger << DAC_CR_TGTRIG_Pos)));

    /* Enable triangle wave */
    SET_BIT(Instance->CR[chnnum], DAC_CR_TGE);

    /* Return function status */
    return LL_OK;
}
/**
  * @}
  */


/** @defgroup DAC_LL_Exported_Functions_Group3 DAC IO operation functions
  * @brief    DAC IO operation functions
  *
@verbatim
  ==============================================================================
             ##### IO operation functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Start/Stop DAC Output.
      (+) Simple value conversion.
      (+) Singles conversion.
      (+) Get result of conversion.

@endverbatim
  * @{
  */

/**
  * @brief  Enables DAC Channel conversion
  * @param  Instance DAC peripheral instance
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_0: DAC Channel0 selected
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_3: DAC Channel3 selected
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_Start(DAC_TypeDef *Instance, uint32_t Channel)
{
    /* Get the channel number */
    uint8_t chnnum = POSITION_VAL(Channel);

    /* Check the DAC parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(IS_DAC_CHANNEL(Channel));
    assert_param(IS_DAC_NUMBER(chnnum));

    /* Enable DAC Channel */
    __LL_DAC_ENABLE(Instance, chnnum);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Disable DAC Channel conversion
  * @param  Instance DAC peripheral instance
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_0: DAC Channel0 selected
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_3: DAC Channel3 selected
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_Stop(DAC_TypeDef *Instance, uint32_t Channel)
{
    /* Get the channel number */
    uint8_t chnnum = POSITION_VAL(Channel);

    /* Check the DAC parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(IS_DAC_CHANNEL(Channel));
    assert_param(IS_DAC_NUMBER(chnnum));

    /* Enable DAC Channel */
    __LL_DAC_DISABLE(Instance, chnnum);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Set the specified data value for DAC channel.
  * @param  Instance DAC peripheral instance
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_0: DAC Channel0 selected
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_3: DAC Channel3 selected
  * @param  Data Data to be loaded.
  *         This parameter can be a number in range from 0 to DAC full range 4095(0xFFF),
  *         witch will be converse to 0 - VCC
  * @return LL status
  */
LL_StatusETypeDef LL_DAC_SetValue(DAC_TypeDef *Instance, uint32_t Channel, uint16_t Data)
{
    /* Get the channel number */
    uint8_t chnnum = POSITION_VAL(Channel);

    /* Check the DAC parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(IS_DAC_CHANNEL(Channel));
    assert_param(IS_DAC_NUMBER(chnnum));

    /* Set the data for DAC channel conversion */
    __LL_DAC_SET_VALUE(Instance, chnnum, Data & 0xFFFUL);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Get the specified DAC channel conversion value on runtime.
  * @param  Instance DAC peripheral instance
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_0: DAC Channel0 selected
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_3: DAC Channel3 selected
  * @return Current conversion value
  */
uint16_t LL_DAC_GetValue(DAC_TypeDef *Instance, uint32_t Channel)
{
    /* Get the channel number */
    uint8_t chnnum = POSITION_VAL(Channel);

    /* Check the DAC parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(IS_DAC_CHANNEL(Channel));
    assert_param(IS_DAC_NUMBER(chnnum));

    return __LL_DAC_GET_VALUE(Instance, chnnum) & 0xFFFUL;
}

/**
  * @brief  Trig sawtooth wave step
  * @param  Instance DAC peripheral instance
  * @param  Channel The selected DAC channel[s].
  *         This parameter can be any combination of the following values:
  *            @arg DAC_CHANNEL_0: DAC Channel0 selected
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_3: DAC Channel3 selected
  * @return LL status
  */
LL_StatusETypeDef LL_DAC_SawtoothWaveDataStep(DAC_TypeDef *Instance, uint32_t Channel)
{
    /* Check the DAC parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(IS_DAC_CHANNELS_MASK(Channel));

    /* Trigger the selected DAC channel software conversion */
    SET_BIT(Instance->SWTR, (Channel << DAC_SWTR_SWTB0_Pos));

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Trig sawtooth wave reset
  * @param  Instance DAC peripheral instance
  * @param  Channel The selected DAC channel[s].
  *         This parameter can be any combination of the following values:
  *            @arg DAC_CHANNEL_0: DAC Channel0 selected
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_3: DAC Channel3 selected
  * @return LL status
  */
LL_StatusETypeDef LL_DAC_SawtoothWaveDataReset(DAC_TypeDef *Instance, uint32_t Channel)
{
    /* Check the DAC parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(IS_DAC_CHANNELS_MASK(Channel));

    /* Trigger the selected DAC channel software conversion */
    SET_BIT(Instance->SWTR, (Channel << DAC_SWTR_SWT0_Pos));

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Trig triangle wave step
  * @param  Instance DAC peripheral instance
  * @param  Channel The selected DAC channel[s].
  *         This parameter can be any combination of the following values:
  *            @arg DAC_CHANNEL_0: DAC Channel0 selected
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_3: DAC Channel3 selected
  * @return LL status
  */
LL_StatusETypeDef LL_DAC_TriangleWaveStep(DAC_TypeDef *Instance, uint32_t Channel)
{
    /* Check the DAC parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(IS_DAC_CHANNELS_MASK(Channel));

    /* Trigger the selected DAC channel software conversion */
    SET_BIT(Instance->SWTR, (Channel << DAC_SWTR_SWT0_Pos));

    /* Return function status */
    return LL_OK;
}
/**
  * @}
  */


/** @defgroup DAC_LL_Exported_Functions_Interrupt DAC Initerrupt management
  * @brief    DAC Initerrupt management
@verbatim
  ===============================================================================
                          ##### Initerrupt management #####
  ===============================================================================
  [..]
      This section provides DAC interrupt handler and callback functions.

@endverbatim
  * @{
  */

/**
  * @brief   This function handles DAC interrupts requests.
  * @param   Instance DAC peripheral
  * @return  None
  */
void LL_DAC_IRQHandler(DAC_TypeDef *Instance)
{
    uint32_t irqtemp = READ_REG(Instance->ISR);
    /* Check the DAC parameters */
    assert_param(IS_DAC_ALL_INSTANCE(Instance));

    for (uint8_t chnnum = 0; chnnum < DAC_CHN_NB; ++chnnum) {
        if ((__LL_DAC_IT_CHECK_SOURCE(Instance, chnnum, DAC_IT_DIE) != RESET) &&
            ((irqtemp & (DAC_ISR_D0IF << chnnum)) != RESET)) {
            /* Chear the DAC_CHx DONE pending flag */
            __LL_DAC_PENDING_FLAG_CLEAR(Instance, (DAC_ISR_D0IF << chnnum));

            /* DACx DONE interrupt callback function */
            LL_DAC_ConvDoneCallback(Instance, 0x1UL << chnnum);
        }

        if ((__LL_DAC_IT_CHECK_SOURCE(Instance, chnnum, DAC_IT_DBIE) != RESET) &&
            ((irqtemp & (DAC_ISR_DB0IF << chnnum)) != RESET)) {
            /* Chear the DAC_CHx DONEB pending flag */
            __LL_DAC_PENDING_FLAG_CLEAR(Instance, (DAC_ISR_DB0IF << chnnum));

            /* DACx DONEB interrupt callback function */
            LL_DAC_ConvDoneBCallback(Instance, 0x1UL << chnnum);

        }
    }
}

/**
  * @brief  DAC_CHx DONE interrupt callback function
  * @param  Instance DAC peripheral
  * @param  Channel The handling DAC channel
  * @return None
  */
__WEAK void LL_DAC_ConvDoneCallback(DAC_TypeDef *Instance, uint32_t Channel)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DAC_ConvDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  DAC_CHx DONE interrupt callback function
  * @param  Instance DAC peripheral
  * @param  Channel The handling DAC channel
  * @return None
  */
__WEAK void LL_DAC_ConvDoneBCallback(DAC_TypeDef *Instance, uint32_t Channel)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DAC_ConvDoneBCallback could be implemented in the user file
     */
}
/**
  * @}
  */


/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/


#endif /* LL_DAC_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

