/**
  ******************************************************************************
  * @file               ft32f4xx_adc.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the Analog to Digital Convertor (ADC) peripheral:
  *                 + Initialization and Configuration
  *                 + Power saving
  *                 + Analog Watchdog configuration
  *                 + Temperature Sensor, Vrefint (Internal Reference Voltage) and
  *                   Vbat (Voltage battery) management
  *                 + ADC Channels Configuration
  *                 + ADC Channels DMA Configuration
  *                 + Interrupts and flags management.
  * @version            V1.0.0
  * @data                   2025-03-06
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_adc.h"
#include "ft32f4xx_rcc.h"


/* ADC CFGR mask */
#define CFGR1_CLEAR_MASK           ((uint32_t)0x80000000)

/* Calibration time out */
#define CALIBRATION_TIMEOUT        ((uint32_t)0x0000F000)

/* ADC register bits groups */
#define ADC_CR_BITS_PROPERTY_RS            (ADC_CR_ADCAL | ADC_CR_ADEN | ADC_CR_ADDIS \
                                            | ADC_CR_JADSTART | ADC_CR_JADSTP \
                                            | ADC_CR_ADSTART | ADC_CR_ADSTP)
/* ADC register CR bits with HW property "rs":
 * Software can read as well as set this bit.
 * Writing '0' has no effect on the bit value. */

/**
  * @brief  Deinitializes ADCx peripheral registers to their default reset values.
  * @param  ADCx: where x can be 1/2/3 to select the ADC peripheral.
  * @retval None
  */
void ADC_DeInit(void)
{
    /* Enable ADC1 reset state */
    //RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC, ENABLE);

    /* Release ADC1 from reset state */
    //RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC, DISABLE);
}

/**
  * @brief  Initializes the ADCx peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @note   This function is used to configure the global features of the ADC (
  *         Common clock prescaler ,Resolution, Data Alignment, continuous mode activation, External
  *         trigger source and edge, Data Gain, regular/injected channel, Discontinuous mode,
  *         Auto injected mode, injected queue contexts, DMA mode, Auto delayed mode,
  *         Overrun mode, Sampling mode and oversampling mode).
  * @param  ADCx: where x can be 1/2/3 to select the ADC peripheral.
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains
  *         the configuration information for the specified ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_RESOLUTION(ADC_InitStruct->Resolution));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ContinuousConvMode));
    assert_param(IS_ADC_EXT_TRIG_EDGE(ADC_InitStruct->ExternalTrigConvEdge));
    assert_param(IS_ADC_REGULAR_EXTTRIG_SOURCE(ADCx, ADC_InitStruct->ExternalTrigConv));
    assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->DataAlign));
    assert_param(IS_ADC_GAIN_COMPENSATION(ADC_InitStruct->GainCompensation));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->DiscontinuousConvMode));
    assert_param(IS_ADC_DMA_MODE(ADC_InitStruct->DMAMode));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->AutoDelayedConvMode));
    assert_param(IS_ADC_OVERRUN(ADC_InitStruct->Overrun));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->InjectedDiscontinuousConvMode));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->AutoInjectedConvMode));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->QueueInjectedContext));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->QueueMode));
    assert_param(IS_ADC_SAMPLINGMODE(ADC_InitStruct->SamplingMode));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->OversamplingMode));
    assert_param(IS_ADC_SAMPLE_PLUS_TIME(ADC_InitStruct->SamplingPlusTime));

    /* Get the ADCx CFGR value */
    tmpreg = ADCx->CFGR1;

    /* Clear RES[1:0], ALIGN, EXTSEL[2:0], EXTEN[1:0] and CONT bits */
    tmpreg &= CFGR1_CLEAR_MASK;

    /*---------------------------- ADCx CFGR Configuration ---------------------*/
    /* Set DMACFG bit according to ADC_ value */
    /* Set RES[1:0] bits according to ADC_Resolution value */
    /* Set EXTEN[1:0] bits according to ADC_ExternalTrigConvEdge value */
    /* Set EXTSEL[2:0] bits according to ADC_ExternalTrigConv value */
    /* Set OVRMOD bit according to ADC_ value */
    /* Set CONT bit according to ADC_ContinuousConvMode value */
    /* Set ALIGN bit according to ADC_DataAlign value */
    /* Set AUTDLY bit according to ADC_ value */
    /* Set DISCEN bit according to ADC_ value */
    /* Set DISCNUM[2:0] bits according to ADC_ value */
    /* Set JAUTO bit according to ADC_ value */
    /* Set JQM bit according to ADC_ value */
    /* Set JDISCEN bit according to ADC_ value */
    /* Set JQDIS bit according to ADC_ value */

    if (ADC_InitStruct->DiscontinuousConvMode == ENABLE)
    {
        assert_param(IS_ADC_REGULAR_DISCONT_NUMBER(ADC_InitStruct->NbrOfDiscConversion));
        tmpreg |= (uint32_t)(ADC_CFGR1_DISCEN | ((ADC_InitStruct->NbrOfDiscConversion - 1) << 17));
    }

    if (ADC_InitStruct->InjectedDiscontinuousConvMode == ENABLE)
    {
        tmpreg |= (uint32_t)ADC_CFGR1_JDISCEN;
    }

    if (ADC_InitStruct->AutoInjectedConvMode == ENABLE)
    {
        tmpreg |= (uint32_t)ADC_CFGR1_JAUTO;
        tmpreg &= (uint32_t)~(ADC_CFGR1_DISCEN | ADC_CFGR1_JDISCEN);
    }

    if (ADC_InitStruct->QueueInjectedContext == DISABLE)
    {
        tmpreg |= (uint32_t)ADC_CFGR1_JQDIS;
    }
    else
    {
        tmpreg &= (uint32_t)~ADC_CFGR1_JQDIS;
        /* Only when the QueueInjectedContext is enabled, QueueMode can be enabled */
        if (ADC_InitStruct->QueueMode == ENABLE)
        {
            tmpreg |= (uint32_t)ADC_CFGR1_JQM;
        }
    }

    /* ADC group regular and injected auto delay conversion mode enable */
    if (ADC_InitStruct->AutoDelayedConvMode == ENABLE)
    {
        tmpreg |= (uint32_t)ADC_CFGR1_AUTDLY;
    }

    /* ADC group regular continuous mode enable */
    if (ADC_InitStruct->ContinuousConvMode == ENABLE)
    {
        tmpreg |= (uint32_t)ADC_CFGR1_CONT;
    }

    /*Set the ADC minimum sampling clock period for all channels */
    if (ADC_InitStruct->SamplingPlusTime == ADC_SAMPLETIMEPLUS_1_5CYCLES)
    {
        ADCx->SMPR1 &= (uint32_t)(~ADC_SMPR1_SMPLUS);
    }
    else
    {
        ADCx->SMPR1 &= (uint32_t)(~ADC_SMPR1_SMPLUS);
        ADCx->SMPR1 |= (uint32_t)ADC_InitStruct->SamplingPlusTime;
    }


    if (ADC_InitStruct->ExternalTrigConvEdge == ADC_SOFTWARE_START)
    {
        tmpreg  |= (uint32_t)(ADC_InitStruct->DataAlign | ADC_InitStruct->Resolution | ADC_InitStruct->Overrun | ADC_InitStruct->DMAMode);
    }
    else
    {
        tmpreg  |= (uint32_t)(ADC_InitStruct->ExternalTrigConvEdge | ADC_InitStruct->ExternalTrigConv | ADC_InitStruct->DataAlign | ADC_InitStruct->Resolution | ADC_InitStruct->Overrun | ADC_InitStruct->DMAMode);
    }


    if (ADC_InitStruct->SamplingMode == ADC_SAMPLING_MODE_TRIGGER_CONTROLED)
    {
        /* Clear BULB enable bit */
        ADCx->CFGR2 &= (uint32_t)~ADC_CFGR2_BULB;

        /* Set Sampling time control trigger mode enable bit */
        ADCx->CFGR2 |= (uint32_t)ADC_CFGR2_SMPTRIG;

        if (ADC_InitStruct->ExternalTrigConvEdge == ADC_SOFTWARE_START)
        {
            tmpreg &= (uint32_t)~ADC_CFGR1_EXTEN;
        }
        else
        {
            /* If select hardware trigger when sampling time control trigger mode
             * external trigger enable and polarity selection for regular channel must set rising edge */
            tmpreg &= (uint32_t)~ADC_CFGR1_EXTEN;
            tmpreg |= (uint32_t)ADC_CFGR1_EXTEN_0;
        }
    }


    if (ADC_InitStruct->SamplingMode == ADC_SAMPLING_MODE_BULB)
    {
        ADCx->CFGR2 &= (uint32_t)~ADC_CFGR2_SMPTRIG;
        ADCx->CFGR2 |= (uint32_t)ADC_CFGR2_BULB;
    }

    /* If the GainCompensation is not 0, Gain mode can be enabled
     * Otherwise, disable Gain mode */
    if (ADC_InitStruct->GainCompensation != 0)
    {
        ADCx->CFGR2 |= (uint32_t)ADC_CFGR2_GCOMP;
        ADCx->GCOMP |= (uint32_t)ADC_InitStruct->GainCompensation;
    }
    else
    {
        ADCx->CFGR2 &= (uint32_t)~ADC_CFGR2_GCOMP;
        ADCx->GCOMP &= (uint32_t)~ADC_GCOMP_GCOMPCOEFF;
    }


    /* Configuration of Oversampler:                                      */
    /*  - Oversampling Ratio                                              */
    /*  - Right bit shift                                                 */
    /*  - Triggered mode                                                  */
    /*  - Oversampling mode (continued/resumed)                           */
    if (ADC_InitStruct->OversamplingMode == ENABLE)
    {

        assert_param(IS_ADC_OVERSAMPLING_RATIO(ADC_InitStruct->Oversampling.Ratio));
        assert_param(IS_ADC_RIGHT_BIT_SHIFT(ADC_InitStruct->Oversampling.RightBitShift));
        assert_param(IS_ADC_TRIGGERED_OVERSAMPLING_MODE(ADC_InitStruct->Oversampling.TriggeredMode));
        assert_param(IS_ADC_REGOVERSAMPLING_MODE(ADC_InitStruct->Oversampling.OversamplingStopReset));


        /* Reset the Oversampling config */
        ADCx->CFGR2 &= (uint32_t)~(ADC_CFGR2_ROVSE | ADC_CFGR2_OVSR | ADC_CFGR2_OVSS  | ADC_CFGR2_TROVS | ADC_CFGR2_ROVSM);

        /* Configuration of Oversampler:                                      */
        /*  - Oversampling Ratio                                              */
        /*  - Right bit shift                                                 */
        /*  - Triggered mode                                                  */
        /*  - Oversampling mode (continued/resumed)                           */
        ADCx->CFGR2 |= (uint32_t)(ADC_InitStruct->Oversampling.Ratio | ADC_InitStruct->Oversampling.RightBitShift | ADC_InitStruct->Oversampling.TriggeredMode | ADC_InitStruct->Oversampling.OversamplingStopReset | ADC_CFGR2_ROVSE);

    }
    else
    {
        /* Reset the Oversampling config */
        ADCx->CFGR2 &= (uint32_t)~(ADC_CFGR2_ROVSE | ADC_CFGR2_TROVS | ADC_CFGR2_ROVSM);
    }


    /* Write to ADCx CFGR */
    ADCx->CFGR1 = tmpreg;

    /* Write Regular channel length to ADCx SQR1 and clear all channels config */
    if (ADC_InitStruct->NbrOfConversion == RESET)
    {
        ADCx->SQR1 = (uint32_t)RESET;
    }
    else
    {
        assert_param(IS_ADC_REGULAR_NUMBER(ADC_InitStruct->NbrOfConversion));
        ADCx->SQR1 = (uint32_t)(ADC_InitStruct->NbrOfConversion - 1);
    }

}

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @note   This function is used to initialize the global features of the ADC (
  *         Resolution, Data Alignment, continuous mode activation, External
  *         trigger source and edge, Sequence Scan Direction).
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct)
{
    /* Reset ADC init structure parameters values */
    /* Initialize the ADC_Resolution member */
    ADC_InitStruct->Resolution = ADC_RESOLUTION_12B;

    /* Initialize the ADC_ContinuousConvMode member */
    ADC_InitStruct->ContinuousConvMode = DISABLE;

    /* Initialize the ADC_ExternalTrigConvEdge member */
    ADC_InitStruct->ExternalTrigConvEdge = ADC_SOFTWARE_START;

    /* Initialize the ADC_DataAlign member */
    ADC_InitStruct->DataAlign = ADC_DATAALIGN_RIGHT;

    /* Initialize the ADC_NbrOfConversion member */
    ADC_InitStruct->NbrOfConversion = 8;

}

/**
  * @brief  Enables or disables the specified ADC peripheral.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @param  NewState: new state of the ADCx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set the ADEN bit to Enable the ADC peripheral */
        ADCx->CR |= (uint32_t)ADC_CR_ADEN;
    }
    else
    {
        /* Set the ADDIS to Disable the ADC peripheral */
        ADCx->CR |= (uint32_t)ADC_CR_ADDIS;
    }
}
/**
  * @}
  */

/**
  * @brief  Set parameter common to several ADC: Clock source and prescaler.
  *         This parameter can be a value of @ref ADC_ClockMode.
  * @note   On this FT32F4xx series, if ADC group injected is used, some
  *         clock ratio constraints between ADC clock and AHB clock
  *         must be respected.
  *         Refer to reference manual.
  * @note   On this FT32F4xx series, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  * @param  ADC_Common ADC common instance
  * @param  CommonClock This parameter can be one of the following values:
  *         @arg @ref ADC_CLOCK_SYNC_HCLK_DIV1
  *         @arg @ref ADC_CLOCK_SYNC_HCLK_DIV2
  *         @arg @ref ADC_CLOCK_SYNC_HCLK_DIV4
  *         @arg @ref ADC_CLOCK_ASYNC_DIV1
  *         @arg @ref ADC_CLOCK_ASYNC_DIV2
  *         @arg @ref ADC_CLOCK_ASYNC_DIV4
  *         @arg @ref ADC_CLOCK_ASYNC_DIV6
  *         @arg @ref ADC_CLOCK_ASYNC_DIV8
  *         @arg @ref ADC_CLOCK_ASYNC_DIV10
  *         @arg @ref ADC_CLOCK_ASYNC_DIV12
  *         @arg @ref ADC_CLOCK_ASYNC_DIV16
  *         @arg @ref ADC_CLOCK_ASYNC_DIV32
  *         @arg @ref ADC_CLOCK_ASYNC_DIV64
  *         @arg @ref ADC_CLOCK_ASYNC_DIV128
  *         @arg @ref ADC_CLOCK_ASYNC_DIV256
  * @retval None
  */
void ADC_ClockModeConfig(uint32_t CommonClock)
{
    assert_param(IS_ADC_CLOCKPRESCALER(CommonClock));

    /* Clear Clock Mode previous config */
    ADC_Common->CCR &= (uint32_t)~ADC_CCR_CKMODE;

    /* Set ADC Common clock mode and prescaler factor */
    if ((CommonClock != ADC_CLOCK_SYNC_HCLK_DIV1) || (CommonClock != ADC_CLOCK_SYNC_HCLK_DIV2) || (CommonClock != ADC_CLOCK_SYNC_HCLK_DIV4))
    {
        /* Set Clock Mode on Async mode */
        ADC_Common->CCR &= (uint32_t)~ADC_CCR_PRESC;

        /* Set prescaler factor to Async mode */
        ADC_Common->CCR |= (uint32_t)CommonClock;
    }
    else
    {
        /* Set Clock Mode on Sync and select the HCLK prescaler factor */
        ADC_Common->CCR |= (uint32_t)CommonClock;
    }
}
/**
  * @}
  */

/**
  * @brief  Enable ADC multimode and configure multimode parameters
  * @note   Possibility to update parameters on the fly:
  *         This function initializes multimode parameters, following
  *         calls to this function can be used to reconfigure some parameters
  *         of structure "ADC_MultiModeTypeDef" on the fly, without resetting
  *         the ADCs.
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure
  *         "ADC_MultiModeTypeDef".
  * @note   To move back configuration from multimode to single mode, ADC must
  *         be reset (using function ADC_Init() ).
  * @param hadc Master ADC handle
  * @param Multimode Structure of ADC multimode configuration
  * @retval None
  */
void ADC_MultiModeConfig(ADC_MultiModeTypeDef* MultiMode)
{
    /* Check the parameters */
    assert_param(IS_ADC_MULTIMODE(MultiMode->Mode));
    assert_param(IS_ADC_DMA_ACCESS_MULTIMODE(MultiMode->DMAAccessMode));
    assert_param(IS_ADC_MULTI_DMA_MODE(MultiMode->DMAMode));
    assert_param(IS_ADC_TWOSAMPLING_DELAY(MultiMode->TwoSamplingDelay));

    /* Config ADCx multi mode */
    if (MultiMode->Mode != ADC_MODE_INDEPENDENT)
    {
        ADC_Common->CCR &= (uint32_t)(~(ADC_CCR_MDMA | ADC_CCR_DMACFG | ADC_CCR_DELAY | ADC_CCR_MULTI));
        ADC_Common->CCR |= (uint32_t)(MultiMode->Mode | MultiMode->DMAAccessMode | MultiMode->DMAMode | MultiMode->TwoSamplingDelay);

    }
    else
    {
        ADC_Common->CCR &= (uint32_t)(~(ADC_CCR_MDMA | ADC_CCR_DMACFG | ADC_CCR_DELAY | ADC_CCR_MULTI));
    }
}
/**
  * @}
  */

/**
  * @brief  Start ADC sampling phase for sampling time trigger mode
  * @note   This function is relevant only when
  *         - @ref ADC_InitTypeDef->SamplingMode has been set
  *           using @ref ADC_SAMPLING_MODE_TRIGGER_CONTROLED
  *         - @ref ADC_SOFTWARE_TRIGCONV is used as trigger source
  * @note   On this FT32F4xx series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion on going on group regular,
  *         without conversion stop command on going on group regular,
  *         without ADC disable command on going.
  * @rmtoll CFGR2    SWTRIG         ADC_StartSamplingPhase
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @retval None
  */
void ADC_StartSamplingPhase(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* Start sampling */
    ADCx->CFGR2 |= (uint32_t)ADC_CFGR2_SWTRIG;
    SET_BIT(ADCx->CFGR2, ADC_CFGR2_SWTRIG);

}
/**
  * @}
  */

/**
  * @brief  Stop ADC sampling phase for sampling time trigger mode
  *         and start conversion
  * @note   This function is relevant only when
  *         - @ref ADC_InitTypeDef->SamplingMode has been set
  *           using @ref ADC_SAMPLING_MODE_TRIGGER_CONTROLED
  *         - @ref ADC_SOFTWARE_TRIGCONV is used as trigger source
  *         - @ref ADC_StartSampling has been called to start
  *           the sampling phase
  * @note   On this FT32F4xx series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion on going on group regular,
  *         without conversion stop command on going on group regular,
  *         without ADC disable command on going.
  * @rmtoll CFGR2    SWTRIG         ADC_StopSamplingPhase
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @retval None
  */
void ADC_StoptSamplingPhase(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* Start sampling */
    ADCx->CFGR2 &= (uint32_t)~ADC_CFGR2_SWTRIG;
}
/**
  * @}
  */

/**
  * @brief  Enables or disables the Wait conversion mode.
  * @note   When the CPU clock is not fast enough to manage the data rate, a
  *         Hardware delay can be introduced between ADC conversions to reduce
  *         this data rate.
  * @note   The Hardware delay is inserted after each conversions and until the
  *         previous data is read from the ADC data register
  * @note   This is a way to automatically adapt the speed of the ADC to the speed
  *         of the system which will read the data.
  * @note   Any hardware triggers wich occur while a conversion is on going or
  *         while the automatic Delay is applied are ignored
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @param  NewState: new state of the ADCx Auto-Delay.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AutoDelayModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the ADC Automatic Delayed conversion */
        ADCx->CFGR1 |= (uint32_t)ADC_CFGR1_AUTDLY;
    }
    else
    {
        /* Disable the ADC Automatic Delayed conversion */
        ADCx->CFGR1 &= (uint32_t)~ADC_CFGR1_AUTDLY;
    }
}
/**
  * @}
  */

/**
  * @brief  Enable the Continuous mode for the selected ADCx channels.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @param  NewState: new state of the Continuous mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   It is not possible to have both discontinuous mode and continuous mode
  *         enabled. In this case (If DISCEN and CONT are Set), the ADC behaves
  *         as if continuous mode was disabled
  * @retval None
  */
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Continuous mode*/
        ADCx->CFGR1 |= (uint32_t)ADC_CFGR1_CONT;
    }
    else
    {
        /* Disable the Continuous mode */
        ADCx->CFGR1 &= (uint32_t)(~ADC_CFGR1_CONT);
    }
}
/**
  * @}
  */

/**
  * @brief  Enable the automatic injected mode for the selected ADCx injected channels.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @param  NewState: new state of the automatic injected mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   It is not possible to enable both ADC group injected
  *         auto-injected mode and sequencer discontinuous mode.
  * @retval None
  */
void ADC_AutoInjectedModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Continuous mode*/
        ADCx->CFGR1 |= (uint32_t)ADC_CFGR1_JAUTO;
    }
    else
    {
        /* Disable the Continuous mode */
        ADCx->CFGR1 &= (uint32_t)(~ADC_CFGR1_JAUTO);
    }
}
/**
  * @}
  */

/**
  * @brief  Enable the discontinuous mode for the selected ADC regular channels.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @param  DiscontNum: This parameter can be one of the following values:
  *          ADC_REG_SEQ_DISCONT_DISABLE
  *          ADC_REG_SEQ_DISCNUM_1_CHANNEL
  *          ADC_REG_SEQ_DISCNUM_2_CHANNELS
  *          ADC_REG_SEQ_DISCNUM_3_CHANNELS
  *          ADC_REG_SEQ_DISCNUM_4_CHANNELS
  *          ADC_REG_SEQ_DISCNUM_5_CHANNELS
  *          ADC_REG_SEQ_DISCNUM_6_CHANNELS
  *          ADC_REG_SEQ_DISCNUM_7_CHANNELS
  *          ADC_REG_SEQ_DISCNUM_8_CHANNELS
  * @note   It is not possible to have both discontinuous mode and continuous mode
  *         enabled. In this case (If DISCEN and CONT are Set), the ADC behaves
  *         as if continuous mode was disabled
  * @retval None
  */
void ADC_REG_DiscModeCmd(ADC_TypeDef* ADCx, uint32_t DiscontNum)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    if (DiscontNum != ADC_REG_SEQ_DISCONT_DISABLE)
    {
        /* Enable the Discontinuous mode and Config the Discontinuous number of channels */
        ADCx->CFGR1 |= (uint32_t)DiscontNum;
    }
    else
    {
        /* Disable the Discontinuous mode and clear the Discontinuous number of channels */
        ADCx->CFGR1 &= (uint32_t)~(ADC_CFGR1_DISCNUM | ADC_CFGR1_DISCEN);
    }
}
/**
  * @}
  */

/**
  * @brief  Enable the discontinuous mode for the selected ADC injected channels.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @param  NewState: new state of the discontinuous mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   It is not possible to have both discontinuous mode and continuous mode
  *         enabled. In this case (If DISCEN and CONT are Set), the ADC behaves
  *         as if continuous mode was disabled
  * @note   ADC group injected each conversion only one channel.
  * @retval None
  */
void ADC_INJ_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Discontinuous mode */
        ADCx->CFGR1 |= (uint32_t)ADC_CFGR1_JDISCEN;
    }
    else
    {
        /* Disable the Discontinuous mode */
        ADCx->CFGR1 &= (uint32_t)(~ADC_CFGR1_JDISCEN);
    }
}
/**
  * @}
  */

/**
  * @brief  Enable the Overrun mode for the selected ADC channels.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @param  NewState: new state of the Overrun mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_OverrunModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Overrun mode */
        ADCx->CFGR1 |= (uint32_t)ADC_CFGR1_OVRMOD;
    }
    else
    {
        /* Disable the Overrun mode */
        ADCx->CFGR1 &= (uint32_t)(~ADC_CFGR1_OVRMOD);
    }
}
/**
  * @}
  */

/**
  * @brief  Put ADC instance in deep power down state.
  * @note   In case of ADC calibration necessary: When ADC is in deep-power-down
  *         state, the internal analog calibration is lost. After exiting from
  *         deep power down, calibration must be relaunched or calibration factor
  *         (preliminarily saved) must be set back into calibration register.
  * @note   On this FT32F4xx series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @param  NewState: new state of the ADCx DeepPowerDown.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DeepPWDModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Note: Write register with some additional bits forced to state reset     */
    /*       instead of modifying only the selected bit for this function,      */
    /*       to not interfere with bits.                                        */
    ADCx->CR &= (uint32_t)~ADC_CR_BITS_PROPERTY_RS;

    if (NewState != DISABLE)
    {
        /* Enable the ADC enter Deep Power Down Mode */
        ADCx->CR |= (uint32_t)ADC_CR_DEEPPWD;
    }
    else
    {
        /* Disable the ADC exti Deep Power Down Mode */
        ADCx->CR &= (uint32_t)~ADC_CR_DEEPPWD;
    }
}
/**
  * @}
  */

/**
  * @brief  Enable ADC instance internal voltage regulator.
  * @note   On this FT32 series, after ADC internal voltage regulator enable,
  *         a delay for ADC internal voltage regulator stabilization
  *         is required before performing a ADC calibration or ADC enable.
  *         Refer to device datasheet, parameter tADCVREG_STUP.
  * @note   On this FT32F4xx series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @param  NewState: new state of the ADCx DeepPowerDown.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_InternalRegulatorCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Note: Write register with some additional bits forced to state reset     */
    /*       instead of modifying only the selected bit for this function,      */
    /*       to not interfere with bits with HW property "rs".                  */
    ADCx->CR &= (uint32_t)~ADC_CR_BITS_PROPERTY_RS;

    if (NewState != DISABLE)
    {
        /* Enable the ADC enable ADCx internal voltage regulator */
        ADCx->CR |= (uint32_t)ADC_CR_ADVREGEN;
    }
    else
    {
        /* Disable the ADC disable ADCx internal voltage regulator */
        ADCx->CR &= (uint32_t)~ADC_CR_ADVREGEN;
    }
}
/**
  * @}
  */

/**
  * @brief  Enables or disables the temperature sensor channel.
  * @param  NewState: new state of the temperature sensor input channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_TempSensorCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the temperature sensor channel*/
        ADC_Common->CCR |= (uint32_t)ADC_CCR_VSENSESEL;
    }
    else
    {
        /* Disable the temperature sensor channel*/
        ADC_Common->CCR &= (uint32_t)(~ADC_CCR_VSENSESEL);
    }
}
/**
  * @}
  */

/**
  * @brief  Enables or disables the Vrefint channel.
  * @param  NewState: new state of the Vref input channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_VrefintCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Vrefint channel*/
        ADC_Common->CCR |= (uint32_t)ADC_CCR_VREFEN;
    }
    else
    {
        /* Disable the Vrefint channel*/
        ADC_Common->CCR &= (uint32_t)(~ADC_CCR_VREFEN);
    }
}
/**
  * @}
  */

/**
  * @brief  Enables or disables the Vbat channel.
  * @param  NewState: new state of the Vbat input channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_VbatCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Vbat channel */
        ADC_Common->CCR |= (uint32_t)ADC_CCR_VBATSEL;
    }
    else
    {
        /* Disable the Vbat channel */
        ADC_Common->CCR &= (uint32_t)(~ADC_CCR_VBATSEL);
    }
}
/**
  * @}
  */

/**
  * @brief  Enables or disables the Analog Watchdog 2 monitor Vbat channel.
  * @param  NewState: new state of the monitor Vbat input channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AWD2MonitorVbatCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Sel the AWD2 monitor the Vbat channel */
        ADC_Common->CCR &= (uint32_t)(~ADC_CCR_AWDSEL);
    }
    else
    {
        /* Sel the AWD3 monitor the Vbat channel */
        ADC_Common->CCR |= (uint32_t)ADC_CCR_AWDSEL;
    }
}
/**
  * @}
  */

/**
  * @brief  Enables or disables the Analog Watchdog 3 monitor Vbat channel.
  * @param  NewState: new state of the monitor Vbat input channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AWD3MonitorVbatCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Sel the AWD3 monitor the Vbat channel */
        ADC_Common->CCR |= (uint32_t)ADC_CCR_AWDSEL;
    }
    else
    {
        /* Sel the AWD2 monitor the Vbat channel */
        ADC_Common->CCR &= (uint32_t)(~ADC_CCR_AWDSEL);
    }
}
/**
  * @}
  */

/**
  * @brief  Enables or disables the Battery charging when voltage is lower than threshold.
  * @param  NewState: This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_BatteryAutoChargingCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Vbat channel automatic charging for battery */
        ADC_Common->CCR |= (uint32_t)ADC_CCR_VBEAUTO;
    }
    else
    {
        /* Disable the Vbat channel automatic charging for battery */
        ADC_Common->CCR &= (uint32_t)(~ADC_CCR_VBEAUTO);
    }
}
/**
  * @}
  */

/**
  * @}
  */
/**
  * @brief  Configures for the selected ADC and its sampling time.
  * @param  ADCx: where x can be 1/2/3 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure.
  *          This parameter can be any combination of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: ADC Channel9 selected
  *            @arg ADC_Channel_10: ADC Channel10 selected
  *            @arg ADC_Channel_11: ADC Channel11 selected
  *            @arg ADC_Channel_12: ADC Channel12 selected
  *            @arg ADC_Channel_13: ADC Channel13 selected
  *            @arg ADC_Channel_14: ADC Channel14 selected
  *            @arg ADC_Channel_15: ADC Channel15 selected
  *            @arg ADC_Channel_16: ADC Channel16 selected
  *            @arg ADC_Channel_17: ADC Channel17 selected
  *            @arg ADC_Channel_18: ADC Channel18 selected
  *            @arg ADC_Channel_19: ADC Channel19 selected
  *            @arg ADC_Channel_20: ADC Channel20 selected
  *            @arg ADC_Channel_21: ADC Channel21 selected
  * @param  ADC_SampleTime: The sample time value to be set for the selected channel.
  *          This parameter can be one of the following values:
  *            @arg ADC_SAMPLETIME_1_5CYCLES: Sample time equal to 1.5 cycles
  *            @arg ADC_SAMPLETIME_6_5CYCLES: Sample time equal to 6.5 cycles
  *            @arg ADC_SAMPLETIME_12_5CYCLES: Sample time equal to 12.5 cycles
  *            @arg ADC_SAMPLETIME_24_5CYCLES: Sample time equal to 24.5 cycles
  *            @arg ADC_SAMPLETIME_47_5CYCLES: Sample time equal to 47.5 cycles
  *            @arg ADC_SAMPLETIME_92_5CYCLES: Sample time equal to 92.5 cycles
  *            @arg ADC_SAMPLETIME_247_5CYCLES: Sample time equal to 247.5 cycles
  *            @arg ADC_SAMPLETIME_640_5CYCLES: Sample time equal to 640.5 cycles
  * @retval None
  */
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, ADC_ChannelConfTypeDef* RegularConfig)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(RegularConfig->Channel));
    assert_param(IS_ADC_REGULAR_RANK(RegularConfig->Rank));
    assert_param(IS_ADC_SAMPLE_TIME(RegularConfig->SamplingTime));
    assert_param(IS_ADC_SINGLE_DIFFERENTIAL(RegularConfig->SingleDiff));
    assert_param(IS_ADC_OFFSET_NUMBER(RegularConfig->OffsetNumber));
    assert_param(IS_ADC_OFFSET_SIGN(RegularConfig->OffsetSign));
    assert_param(IS_FUNCTIONAL_STATE(RegularConfig->OffsetSaturation));


    /* Clear th Channel Selection bits, and Configure the ADC Channel */
    if (RegularConfig->Rank <= ADC_REGULAR_RANK_4)
    {
        ADCx->SQR1 &= (uint32_t)(~(0x1f << ((RegularConfig->Rank + 1) * 6)));
        ADCx->SQR1 |=  RegularConfig->Channel << ((RegularConfig->Rank + 1) * 6);
    }
    else if (RegularConfig->Rank <= ADC_REGULAR_RANK_9)
    {
        ADCx->SQR2 &= (uint32_t)(~(0x1f << ((RegularConfig->Rank - 4) * 6)));
        ADCx->SQR2 |=  RegularConfig->Channel << ((RegularConfig->Rank - 4) * 6);
    }
    else if (RegularConfig->Rank <= ADC_REGULAR_RANK_14)
    {
        ADCx->SQR3 &= (uint32_t)(~(0x1f << ((RegularConfig->Rank - 9) * 6)));
        ADCx->SQR3 |=  RegularConfig->Channel << ((RegularConfig->Rank - 9) * 6);
    }
    else if (RegularConfig->Rank <= ADC_REGULAR_RANK_16)
    {
        ADCx->SQR4 &= (uint32_t)(~(0x1f << ((RegularConfig->Rank - 14) * 6)));
        ADCx->SQR4 |=  RegularConfig->Channel << ((RegularConfig->Rank - 14) * 6);
    }


    /* Clear the Sampling time Selection bits, and Set the ADC Sampling Time register */
    /* Set sampling time of the selected ADC channel */
    /* Note: ADC channel number masked with value "0x1F" to ensure shift value within 32 bits range */
    if (RegularConfig->Channel <= ADC_CHANNEL_9)
    {
        ADCx->SMPR1 &= (uint32_t)(~(0x7 << (RegularConfig->Channel * 3)));
        ADCx->SMPR1 |= RegularConfig->SamplingTime << (RegularConfig->Channel * 3);
    }
    else if (RegularConfig->Channel <= ADC_CHANNEL_18)
    {
        ADCx->SMPR2 &= (uint32_t)(~(0x7 << (RegularConfig->Channel - 10)));
        ADCx->SMPR2 |= RegularConfig->SamplingTime << ((RegularConfig->Channel - 10) * 3);
    }
    else if (RegularConfig->Channel <= ADC_CHANNEL_21)
    {
        ADCx->SMPR3 &= (uint32_t)(~(0x7 << (RegularConfig->Channel - 19)));
        ADCx->SMPR3 |= RegularConfig->SamplingTime << ((RegularConfig->Channel - 19) * 3);
    }


    /* Parameters update conditioned to ADC state:                              */
    /* Parameters that can be updated only when ADC is disabled:                */
    /*  - Single or differential mode                                           */
    if (RegularConfig->SingleDiff == ADC_DIFFERENTIAL_ENDED)
    {
        /* Set mode differential input of the selected ADC channel */
        ADCx->DIFSEL |= (uint32_t)(ADC_DIFFERENTIAL_ENDED << RegularConfig->Channel);
    }
    else
    {
        /* Set mode single-ended input of the selected ADC channel */
        ADCx->DIFSEL &= (uint32_t)~(ADC_DIFFERENTIAL_ENDED << RegularConfig->Channel);
    }


    /* Scan each offset register to check if the selected channel is targeted.      */
    /* If this is the case, the corresponding offset number is enable or disabled.  */
    /* Parameters update conditioned to ADC state:                                  */
    /* Parameters that can be updated when ADC is disabled or enabled without       */
    /* conversion on going on regular group or injected group:                      */
    /*  - Channel offset                                                            */
    /* Shift the offset with respect to the selected ADC resolution.                */
    /* Offset has to be left-aligned on bit 11, the LSB (right bits) are set to 0   */
    /* Set ADC selected offset sign & saturation by @param OffsetSign and OffsetSaturation */
    if (RegularConfig->OffsetNumber != ADC_OFFSET_NONE)
    {
        /* Config register OFR1 */
        if (RegularConfig->OffsetNumber == ADC_OFFSET_1)
        {
            ADCx->OFR1 = ADC_OFR1_OFFSET_EN | RegularConfig->OffsetSign | (RegularConfig->Channel << 26) |
                         (RegularConfig->OffsetSaturation << 25) | RegularConfig->Offset ;
        }

        /* Config register OFR2 */
        if (RegularConfig->OffsetNumber == ADC_OFFSET_2)
        {
            ADCx->OFR2 = ADC_OFR2_OFFSET_EN | RegularConfig->OffsetSign | (RegularConfig->Channel << 26) |
                         (RegularConfig->OffsetSaturation << 25) | RegularConfig->Offset ;
        }

        /* Config register OFR3 */
        if (RegularConfig->OffsetNumber == ADC_OFFSET_3)
        {
            ADCx->OFR3 = ADC_OFR3_OFFSET_EN | RegularConfig->OffsetSign | (RegularConfig->Channel << 26) |
                         (RegularConfig->OffsetSaturation << 25) | RegularConfig->Offset ;
        }

        /* Config register OFR4 */
        if (RegularConfig->OffsetNumber == ADC_OFFSET_4)
        {
            ADCx->OFR4 = ADC_OFR4_OFFSET_EN | RegularConfig->OffsetSign | (RegularConfig->Channel << 26) |
                         (RegularConfig->OffsetSaturation << 25) | RegularConfig->Offset ;
        }
    }
    else
    {
        /* Reset register OFR1 */
        if (RegularConfig->Channel == ((ADCx->OFR1 >> 26) & 0x1f))
        {
            ADCx->OFR1 = (uint32_t)RESET;
        }

        /* Reset register OFR2 */
        if (RegularConfig->Channel == ((ADCx->OFR2 >> 26) & 0x1f))
        {
            ADCx->OFR2 = (uint32_t)RESET;
        }

        /* Reset register OFR3 */
        if (RegularConfig->Channel == ((ADCx->OFR3 >> 26) & 0x1f))
        {
            ADCx->OFR3 = (uint32_t)RESET;
        }

        /* Reset register OFR4 */
        if (RegularConfig->Channel == ((ADCx->OFR4 >> 26) & 0x1f))
        {
            ADCx->OFR4 = (uint32_t)RESET;
        }
    }
}



/**
  * @brief  Configures for the selected ADC and its sampling time.
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure.
  *          This parameter can be any combination of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: ADC Channel9 selected
  *            @arg ADC_Channel_10: ADC Channel10 selected
  *            @arg ADC_Channel_11: ADC Channel11 selected
  *            @arg ADC_Channel_12: ADC Channel12 selected
  *            @arg ADC_Channel_13: ADC Channel13 selected
  *            @arg ADC_Channel_14: ADC Channel14 selected
  *            @arg ADC_Channel_15: ADC Channel15 selected
  *            @arg ADC_Channel_16: ADC Channel16 selected
  *            @arg ADC_Channel_17: ADC Channel17 selected
  *            @arg ADC_Channel_18: ADC Channel18 selected
  *            @arg ADC_Channel_19: ADC Channel19 selected
  *            @arg ADC_Channel_20: ADC Channel20 selected
  *            @arg ADC_Channel_21: ADC Channel21 selected
  *          This parameter can be one of the following values:
  *            @arg ADC_SampleTime_1_5Cycles: Sample time equal to 1.5 cycles
  *            @arg ADC_SampleTime_7_5Cycles: Sample time equal to 7.5 cycles
  *            @arg ADC_SampleTime_13_5Cycles: Sample time equal to 13.5 cycles
  *            @arg ADC_SampleTime_28_5Cycles: Sample time equal to 28.5 cycles
  *            @arg ADC_SampleTime_41_5Cycles: Sample time equal to 41.5 cycles
  *            @arg ADC_SampleTime_55_5Cycles: Sample time equal to 55.5 cycles
  *            @arg ADC_SampleTime_71_5Cycles: Sample time equal to 71.5 cycles
  *            @arg ADC_SampleTime_239_5Cycles: Sample time equal to 239.5 cycles
  * @retval None
  */
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, ADC_InjectedConfTypeDef* InjectedConfig)
{
    static uint32_t tmp_jsqr = 0x0, channel_count = 0x0;


    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(InjectedConfig->InjectedChannel));
    assert_param(IS_ADC_REGULAR_RANK(InjectedConfig->InjectedRank));
    assert_param(IS_ADC_SAMPLE_TIME(InjectedConfig->InjectedSamplingTime));
    assert_param(IS_ADC_SINGLE_DIFFERENTIAL(InjectedConfig->InjectedSingleDiff));
    assert_param(IS_ADC_OFFSET_NUMBER(InjectedConfig->InjectedOffsetNumber));
    assert_param(IS_ADC_OFFSET_SIGN(InjectedConfig->InjectedOffsetSign));
    assert_param(IS_FUNCTIONAL_STATE(InjectedConfig->InjectedOffsetSaturation));
    assert_param(IS_FUNCTIONAL_STATE(InjectedConfig->InjectedOversamplingMode));
    assert_param(IS_ADC_INJECTED_NUMBER(InjectedConfig->InjectedNbrOfConversion));
    assert_param(IS_ADC_EXTTRIG_INJEC_EDGE(InjectedConfig->ExternalTrigInjecConvEdge));
    assert_param(IS_ADC_INJECTED_EXTTRIG_SOURCE(ADCx, InjectedConfig->ExternalTrigInjecConv));


    if (InjectedConfig->InjectedRank == ADC_INJECTED_RANK_1)
    {
        if (channel_count != (uint32_t)RESET)
        {
            channel_count = (uint32_t)RESET;
        }

        tmp_jsqr |= (uint32_t)(InjectedConfig->InjectedChannel << 9);
    }
    else if (InjectedConfig->InjectedRank == ADC_INJECTED_RANK_2)
    {
        tmp_jsqr |= (uint32_t)(InjectedConfig->InjectedChannel << 15);
    }
    else if (InjectedConfig->InjectedRank == ADC_INJECTED_RANK_3)
    {
        tmp_jsqr |= (uint32_t)(InjectedConfig->InjectedChannel << 21);
    }
    else if (InjectedConfig->InjectedRank == ADC_INJECTED_RANK_4)
    {
        tmp_jsqr |= (uint32_t)(InjectedConfig->InjectedChannel << 27);
    }

    channel_count ++;

    if (channel_count == InjectedConfig->InjectedNbrOfConversion)
    {
        ADCx->JSQR = tmp_jsqr + (uint32_t)(InjectedConfig->InjectedNbrOfConversion - 1) + (uint32_t)InjectedConfig->ExternalTrigInjecConv + (uint32_t)InjectedConfig->ExternalTrigInjecConvEdge;

        /* ADC group injected config reset when all injected channels set */
        tmp_jsqr = RESET;

        channel_count = RESET;

        /* Configuration of Oversampler:                                      */
        /*  - Oversampling Ratio                                              */
        /*  - Right bit shift                                                 */
        /*  - Triggered mode                                                  */
        /*  - Oversampling mode (continued/resumed)                           */
        if (InjectedConfig->InjectedOversamplingMode == ENABLE)
        {

            assert_param(IS_ADC_OVERSAMPLING_RATIO(InjectedConfig->InjectedOversampling.Ratio));
            assert_param(IS_ADC_RIGHT_BIT_SHIFT(InjectedConfig->InjectedOversampling.RightBitShift));

            /* Reset the Oversampling config */
            ADCx->CFGR2 &= (uint32_t)~(ADC_CFGR2_JOVSE | ADC_CFGR2_OVSR | ADC_CFGR2_OVSS);

            /* Configuration of Oversampler:                                      */
            /*  - Oversampling Ratio                                              */
            /*  - Right bit shift                                                 */
            ADCx->CFGR2 |= (uint32_t)(InjectedConfig->InjectedOversampling.Ratio | InjectedConfig->InjectedOversampling.RightBitShift | ADC_CFGR2_JOVSE);

        }
        else
        {
            /* Reset the Oversampling config */
            ADCx->CFGR2 &= (uint32_t)~ADC_CFGR2_JOVSE;
        }
    }


    /* Clear the Sampling time Selection bits, and Set the ADC Sampling Time register */
    /* Set sampling time of the selected ADC channel */
    /* Note: ADC channel number masked with value "0x1F" to ensure shift value within 32 bits range */
    if (InjectedConfig->InjectedChannel <= ADC_CHANNEL_9)
    {
        ADCx->SMPR1 &= (uint32_t)(~(0x7 << (InjectedConfig->InjectedChannel * 3)));
        ADCx->SMPR1 |= (uint32_t)(InjectedConfig->InjectedSamplingTime << (InjectedConfig->InjectedChannel * 3));
    }
    else if (InjectedConfig->InjectedChannel <= ADC_CHANNEL_18)
    {
        ADCx->SMPR2 &= (uint32_t)(~(0x7 << (InjectedConfig->InjectedChannel - 10)));
        ADCx->SMPR2 |= (uint32_t)(InjectedConfig->InjectedSamplingTime << ((InjectedConfig->InjectedChannel - 10) * 3));
    }
    else if (InjectedConfig->InjectedChannel <= ADC_CHANNEL_21)
    {
        ADCx->SMPR3 &= (uint32_t)(~(0x7 << (InjectedConfig->InjectedChannel - 19)));
        ADCx->SMPR3 |= (uint32_t)(InjectedConfig->InjectedSamplingTime << ((InjectedConfig->InjectedChannel - 19) * 3));
    }

    /* Parameters update conditioned to ADC state:                              */
    /* Parameters that can be updated only when ADC is disabled:                */
    /*  - Single or differential mode                                           */
    if (InjectedConfig->InjectedSingleDiff == ADC_DIFFERENTIAL_ENDED)
    {
        /* Set mode differential input of the selected ADC channel */
        ADCx->DIFSEL |= (uint32_t)(ADC_DIFFERENTIAL_ENDED << InjectedConfig->InjectedChannel);
    }
    else
    {
        /* Set mode single-ended input of the selected ADC channel */
        ADCx->DIFSEL &= (uint32_t)~(ADC_DIFFERENTIAL_ENDED << InjectedConfig->InjectedChannel);
    }


    /* Scan each offset register to check if the selected channel is targeted.      */
    /* If this is the case, the corresponding offset number is enable or disabled.  */
    /* Parameters update conditioned to ADC state:                                  */
    /* Parameters that can be updated when ADC is disabled or enabled without       */
    /* conversion on going on regular group or injected group:                      */
    /*  - Channel offset                                                            */
    /* Shift the offset with respect to the selected ADC resolution.                */
    /* Offset has to be left-aligned on bit 11, the LSB (right bits) are set to 0   */
    /* Set ADC selected offset sign & saturation by @param OffsetSign and OffsetSaturation */
    if (InjectedConfig->InjectedOffsetNumber != ADC_OFFSET_NONE)
    {
        /* Config register OFRx */
        if (InjectedConfig->InjectedOffsetNumber == ADC_OFFSET_1)
        {
            ADCx->OFR1 = ADC_OFR1_OFFSET_EN | (uint32_t)InjectedConfig->InjectedOffsetSign | (uint32_t)(InjectedConfig->InjectedChannel << 26) |
                         (uint32_t)(InjectedConfig->InjectedOffsetSaturation << 25) | (uint32_t)InjectedConfig->InjectedOffset ;
        }

        /* Config register OFRx */
        if (InjectedConfig->InjectedOffsetNumber == ADC_OFFSET_2)
        {
            ADCx->OFR2 = ADC_OFR2_OFFSET_EN | (uint32_t)InjectedConfig->InjectedOffsetSign | (uint32_t)(InjectedConfig->InjectedChannel << 26) |
                         (uint32_t)(InjectedConfig->InjectedOffsetSaturation << 25) | (uint32_t)InjectedConfig->InjectedOffset ;
        }

        /* Config register OFRx */
        if (InjectedConfig->InjectedOffsetNumber == ADC_OFFSET_3)
        {
            ADCx->OFR3 = ADC_OFR3_OFFSET_EN | (uint32_t)InjectedConfig->InjectedOffsetSign | (uint32_t)(InjectedConfig->InjectedChannel << 26) |
                         (uint32_t)(InjectedConfig->InjectedOffsetSaturation << 25) | (uint32_t)InjectedConfig->InjectedOffset ;
        }

        /* Config register OFRx */
        if (InjectedConfig->InjectedOffsetNumber == ADC_OFFSET_4)
        {
            ADCx->OFR4 = ADC_OFR4_OFFSET_EN | (uint32_t)InjectedConfig->InjectedOffsetSign | (uint32_t)(InjectedConfig->InjectedChannel << 26) |
                         (uint32_t)(InjectedConfig->InjectedOffsetSaturation << 25) | (uint32_t)InjectedConfig->InjectedOffset ;
        }
    }
    else
    {
        /* Reset register OFR1 */
        if (InjectedConfig->InjectedChannel == ((ADCx->OFR1 >> 26) & 0x1f))
        {
            ADCx->OFR1 = (uint32_t)RESET;
        }

        /* Reset register OFR2 */
        if (InjectedConfig->InjectedChannel == ((ADCx->OFR2 >> 26) & 0x1f))
        {
            ADCx->OFR2 = (uint32_t)RESET;
        }

        /* Reset register OFR3 */
        if (InjectedConfig->InjectedChannel == ((ADCx->OFR3 >> 26) & 0x1f))
        {
            ADCx->OFR3 = (uint32_t)RESET;
        }

        /* Reset register OFR4 */
        if (InjectedConfig->InjectedChannel == ((ADCx->OFR4 >> 26) & 0x1f))
        {
            ADCx->OFR4 = (uint32_t)RESET;
        }
    }
}


/**
  * @brief  Configure the analog watchdog.
  * @note   Possibility to update parameters on the fly:
  *         This function initializes the selected analog watchdog, successive
  *         calls to this function can be used to reconfigure some parameters
  *         of structure "ADC_AnalogWDGConfTypeDef" on the fly, without resetting
  *         the ADC.
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure
  *         "ADC_AnalogWDGConfTypeDef".
  * @note   On this FT32 series, analog watchdog thresholds can be modified
  *         while ADC conversion is on going.
  *         In this case, some constraints must be taken into account:
  *         the programmed threshold values are effective from the next
  *         ADC EOC (end of unitary conversion).
  *         Considering that registers write delay may happen due to
  *         bus activity, this might cause an uncertainty on the
  *         effective timing of the new programmed threshold values.
  * @param  AnalogWDGConfig Structure of ADC analog watchdog 1 configuration
  *         AnalogWDG 1 Mode can be any combination of the following values:
  *         ADC_ANALOGWATCHDOG_SINGLE_REG
  *         ADC_ANALOGWATCHDOG_SINGLE_INJEC
  *         ADC_ANALOGWATCHDOG_SINGLE_REGINJEC
  *         ADC_ANALOGWATCHDOG_ALL_REG
  *         ADC_ANALOGWATCHDOG_ALL_INJEC
  *         ADC_ANALOGWATCHDOG_ALL_REGINJEC
  * @param  ADC_AnalogWatchdog23_Channel: the ADC channel to configure for the analog watchdog.
  *          This parameter can be one of the following values:
  *            @arg ADC_AnalogWatchdog_Channel_0: ADC Channel0 selected
  *            @arg ADC_AnalogWatchdog_Channel_1: ADC Channel1 selected
  *            @arg ADC_AnalogWatchdog_Channel_2: ADC Channel2 selected
  *            @arg ADC_AnalogWatchdog_Channel_3: ADC Channel3 selected
  *            @arg ADC_AnalogWatchdog_Channel_4: ADC Channel4 selected
  *            @arg ADC_AnalogWatchdog_Channel_5: ADC Channel5 selected
  *            @arg ADC_AnalogWatchdog_Channel_6: ADC Channel6 selected
  *            @arg ADC_AnalogWatchdog_Channel_7: ADC Channel7 selected
  *            @arg ADC_AnalogWatchdog_Channel_8: ADC Channel8 selected
  *            @arg ADC_AnalogWatchdog_Channel_9: ADC Channel9 selected
  *            @arg ADC_AnalogWatchdog_Channel_10: ADC Channel10 selected
  *            @arg ADC_AnalogWatchdog_Channel_11: ADC Channel11 selected
  *            @arg ADC_AnalogWatchdog_Channel_12: ADC Channel12 selected
  *            @arg ADC_AnalogWatchdog_Channel_13: ADC Channel13 selected
  *            @arg ADC_AnalogWatchdog_Channel_14: ADC Channel14 selected
  *            @arg ADC_AnalogWatchdog_Channel_15: ADC Channel15 selected
  *            @arg ADC_AnalogWatchdog_Channel_16: ADC Channel16 selected
  *            @arg ADC_AnalogWatchdog_Channel_17: ADC Channel17 selected
  *            @arg ADC_AnalogWatchdog_Channel_18: ADC Channel18 selected
  * @note   The channel selected on the AWDCH must be also set into the AWDxCR
  *         register
  * @retval None
  */

void ADC_AnalogWDGConfig(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_ANALOG_WATCHDOG_1_MODE(AnalogWDGConfig->WatchdogMode));
    assert_param(IS_FUNCTIONAL_STATE(AnalogWDGConfig->ITMode));
    assert_param(IS_ADC_ANALOG_WATCHDOG_FILTERING_MODE(AnalogWDGConfig->FilteringConfig));

    if ((AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_REG)     ||
            (AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_INJEC)   ||
            (AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC))
    {
        assert_param(IS_ADC_CHANNEL(AnalogWDGConfig->Channel));
    }

    /* Set  AnologWatchdog  */
    if (((ADCx->CR & ADC_CR_ADSTART) != ADC_CR_ADSTART) || ((ADCx->CR & ADC_CR_JADSTART) != ADC_CR_JADSTART))
    {
        /* Analog watchdog configuration */
        if (AnalogWDGConfig->WatchdogNumber == ADC_ANALOGWATCHDOG_1)
        {
            /* Configuration of analog watchdog:                                    */
            /*  - Set the analog watchdog enable mode: one or overall group of      */
            /*    channels, on groups regular and-or injected.                      */
            if ((AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_REG) || (AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_INJEC) || (AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC))
            {
                ADCx->CFGR1 &= (uint32_t)~(ADC_CFGR1_AWD1EN | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1CH);
                ADCx->CFGR1 |= (uint32_t)(AnalogWDGConfig->WatchdogMode | (AnalogWDGConfig->Channel << 26));
            }
            else if ((AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_ALL_REG) || (AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_ALL_INJEC) || (AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_ALL_REGINJEC))
            {
                ADCx->CFGR1 &= (uint32_t)~(ADC_CFGR1_AWD1EN | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1CH | ADC_CFGR1_AWD1SGL);
                ADCx->CFGR1 |= (uint32_t)AnalogWDGConfig->WatchdogMode;
            }
            else
            {
                /* Disable Analog watchdog 1 configuration */
                ADCx->CFGR1 &= (uint32_t)~(ADC_CFGR1_AWD1EN | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1CH | ADC_CFGR1_AWD1SGL);
            }

            /* Set the filtering configuration */
            ADCx->TR1 &= (uint32_t)~ADC_TR1_AWDFILT;
            ADCx->TR1 |= (uint32_t)AnalogWDGConfig->FilteringConfig;

            /* Clear flag ADC analog watchdog */
            /* Note: Flag cleared Clear the ADC Analog watchdog flag to be ready  */
            /* to use for ADC_IRQHandler()                                        */
            /* (in case left enabled by previous ADC operations).                 */
            ADCx->ISR |= (uint32_t)ADC_ISR_AWD1;

            /* Configure ADC analog watchdog interrupt */
            if (AnalogWDGConfig->ITMode == ENABLE)
            {
                ADC_ITConfig(ADCx, ADC_IT_AWD1, ENABLE);
            }
            else
            {
                ADC_ITConfig(ADCx, ADC_IT_AWD1, DISABLE);
            }
        }
        else
        {
            if (AnalogWDGConfig->WatchdogNumber == ADC_ANALOGWATCHDOG_2)
            {
                if (AnalogWDGConfig->Channel == (uint32_t)RESET)
                {
                    ADCx->AWD2CR = (uint32_t)AnalogWDGConfig->Channel;
                }
                else
                {
                    ADCx->AWD2CR = (uint32_t)RESET;
                }

                /* Clear flag ADC analog watchdog */
                /* Note: Flag cleared Clear the ADC Analog watchdog flag to be ready  */
                /* to use for ADC_IRQHandler()                                        */
                /* (in case left enabled by previous ADC operations).                 */
                ADCx->ISR |=  ADC_ISR_AWD2;

                /* Configure ADC analog watchdog interrupt */
                if (AnalogWDGConfig->ITMode == ENABLE)
                {
                    ADC_ITConfig(ADCx, ADC_IT_AWD2, ENABLE);
                }
                else
                {
                    ADC_ITConfig(ADCx, ADC_IT_AWD2, DISABLE);
                }
            }
            else if (AnalogWDGConfig->WatchdogNumber == ADC_ANALOGWATCHDOG_3)
            {
                if (AnalogWDGConfig->Channel == (uint32_t)RESET)
                {
                    ADCx->AWD3CR = (uint32_t)AnalogWDGConfig->Channel;
                }
                else
                {
                    ADCx->AWD3CR = (uint32_t)RESET;
                }

                /* Clear flag ADC analog watchdog */
                /* Note: Flag cleared Clear the ADC Analog watchdog flag to be ready  */
                /* to use for ADC_IRQHandler()                                        */
                /* (in case left enabled by previous ADC operations).                 */
                ADCx->ISR |=  ADC_ISR_AWD3;

                /* Configure ADC analog watchdog interrupt */
                if (AnalogWDGConfig->ITMode == ENABLE)
                {
                    ADC_ITConfig(ADCx, ADC_IT_AWD3, ENABLE);
                }
                else
                {
                    ADC_ITConfig(ADCx, ADC_IT_AWD3, DISABLE);
                }
            }
        }
    }


    /* Analog watchdog thresholds configuration */
    if (AnalogWDGConfig->WatchdogNumber == ADC_ANALOGWATCHDOG_1)
    {
        /* These value configure the ADC threshold value depending of ADC resolution */
        if (ADC_InitStruct->Resolution == ADC_RESOLUTION_6B)
        {
            ADCx->TR1 &= (uint32_t)~(ADC_TR1_LT1 | ADC_TR1_HT1);
            ADCx->TR1 |= (uint32_t)(((AnalogWDGConfig->HighThreshold & 0xfc0) << 16) | (AnalogWDGConfig->LowThreshold & 0xfc0));
        }
        else if (ADC_InitStruct->Resolution == ADC_RESOLUTION_8B)
        {
            ADCx->TR1 &= (uint32_t)~(ADC_TR1_LT1 | ADC_TR1_HT1);
            ADCx->TR1 |= (uint32_t)(((AnalogWDGConfig->HighThreshold & 0xff0) << 16) | (AnalogWDGConfig->LowThreshold & 0xff0));
        }
        else if (ADC_InitStruct->Resolution == ADC_RESOLUTION_10B)
        {
            ADCx->TR1 &= (uint32_t)~(ADC_TR1_LT1 | ADC_TR1_HT1);
            ADCx->TR1 |= (uint32_t)(((AnalogWDGConfig->HighThreshold & 0xffc) << 16) | (AnalogWDGConfig->LowThreshold & 0xffc));
        }
        else
        {
            ADCx->TR1 &= (uint32_t)~(ADC_TR1_LT1 | ADC_TR1_HT1);
            ADCx->TR1 |= (uint32_t)(((AnalogWDGConfig->HighThreshold & 0xfff) << 16) | (AnalogWDGConfig->LowThreshold & 0xfff));
        }
    }

    if (AnalogWDGConfig->WatchdogNumber == ADC_ANALOGWATCHDOG_2)
    {
        if (ADC_InitStruct->Resolution == ADC_RESOLUTION_6B)
        {
            ADCx->TR2 &= (uint32_t)~(ADC_TR2_LT2 | ADC_TR2_HT2);
            ADCx->TR2 |= (uint32_t)(((AnalogWDGConfig->HighThreshold & 0xfc) << 16) | (AnalogWDGConfig->LowThreshold & 0xfc));
        }
        else if (ADC_InitStruct->Resolution == ADC_RESOLUTION_8B)
        {
            ADCx->TR2 &= (uint32_t)~(ADC_TR2_LT2 | ADC_TR2_HT2);
            ADCx->TR2 |= (uint32_t)(((AnalogWDGConfig->HighThreshold & 0xff) << 16) | (AnalogWDGConfig->LowThreshold & 0xff));
        }
        else if (ADC_InitStruct->Resolution == ADC_RESOLUTION_10B)
        {
            ADCx->TR2 &= (uint32_t)~(ADC_TR2_LT2 | ADC_TR2_HT2);
            ADCx->TR2 |= (uint32_t)(((AnalogWDGConfig->HighThreshold & 0xff) << 16) | (AnalogWDGConfig->LowThreshold & 0xff));
        }
        else
        {
            ADCx->TR2 &= (uint32_t)~(ADC_TR2_LT2 | ADC_TR2_HT2);
            ADCx->TR2 |= (uint32_t)(((AnalogWDGConfig->HighThreshold & 0xff)  << 16) | (AnalogWDGConfig->LowThreshold & 0xff));
        }
    }

    if (AnalogWDGConfig->WatchdogNumber == ADC_ANALOGWATCHDOG_3)
    {
        if (ADC_InitStruct->Resolution == ADC_RESOLUTION_6B)
        {
            ADCx->TR3 &= (uint32_t)~(ADC_TR3_LT3 | ADC_TR3_HT3);
            ADCx->TR3 |= (uint32_t)(((AnalogWDGConfig->HighThreshold & 0xfc) << 16) | (AnalogWDGConfig->LowThreshold & 0xfc));
        }
        else if (ADC_InitStruct->Resolution == ADC_RESOLUTION_8B)
        {
            ADCx->TR3 &= (uint32_t)~(ADC_TR3_LT3 | ADC_TR3_HT3);
            ADCx->TR3 |= (uint32_t)(((AnalogWDGConfig->HighThreshold & 0xff) << 16) | (AnalogWDGConfig->LowThreshold & 0xff));
        }
        else if (ADC_InitStruct->Resolution == ADC_RESOLUTION_10B)
        {
            ADCx->TR3 &= (uint32_t)~(ADC_TR3_LT3 | ADC_TR3_HT3);
            ADCx->TR3 |= (uint32_t)(((AnalogWDGConfig->HighThreshold & 0xff) << 16) | (AnalogWDGConfig->LowThreshold & 0xff));
        }
        else
        {
            ADCx->TR3 &= (uint32_t)~(ADC_TR3_LT3 | ADC_TR3_HT3);
            ADCx->TR3 |= (uint32_t)(((AnalogWDGConfig->HighThreshold & 0xff)  << 16) | (AnalogWDGConfig->LowThreshold & 0xff));
        }
    }
}


/**
  * @brief  Active the Calibration operation in the mode single-ended
  *         for the selected ADC.
  * @note   The Calibration can be initiated only when ADC is still in the
  *         reset configuration (ADEN must be equal to 0).
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @retval ADC Calibration factor
  */
uint32_t ADC_StartSingleCalibration(ADC_TypeDef* ADCx)
{
    uint32_t tmpreg = 0x0, calibrationcounter = 0x0, calibrationstatus = 0x0;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* Set the diff calibration mode */
    ADCx->CR &= (uint32_t)~ADC_CR_ADCALDIF;

    /* Set the ADC calibration */
    ADCx->CR |= (uint32_t)ADC_CR_ADCAL;

    /* Wait until no ADC calibration is completed */
    do
    {
        calibrationstatus = ADCx->CR & ADC_CR_ADCAL;
        calibrationcounter++;
    }
    while ((calibrationcounter != CALIBRATION_TIMEOUT) && (calibrationstatus != 0x00));

    if ((uint32_t)(ADCx->CR & ADC_CR_ADCAL) == RESET)
    {
        /*Get the calibration factor from the ADC data register */
        tmpreg = (uint32_t)(ADCx->CALFACT & ADC_CALFACT_S);
    }
    else
    {
        /* Error factor */
        tmpreg = (uint32_t)RESET;
    }
    return tmpreg;
}


/**
  * @brief  Get ADC calibration factor in the mode single-ended.
  * @note   Calibration factors are set by hardware after performing
  *         a calibration run using function @ref ADC_SingleCalibrationStart().
  * @param  ADCx ADC instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x7F
  */
uint32_t ADC_GetSingleCalibrationFactor(ADC_TypeDef* ADCx)
{
    uint32_t tmpreg = 0x0, calibrationcounter = 0x0, calibrationstatus = 0x0;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /*Get the calibration factor from the ADC data register */
    tmpreg = (uint32_t)(ADCx->CALFACT & ADC_CALFACT_S);

    return tmpreg;
}


/**
  * @brief  Active the Calibration operation in the mode differential
  *         for the selected ADC.
  * @note   The Calibration can be initiated only when ADC is still in the
  *         reset configuration (ADEN must be equal to 0).
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @retval ADC Calibration factor
  */
uint32_t ADC_StartDiffCalibration(ADC_TypeDef* ADCx)
{
    uint32_t tmpreg = 0x0, calibrationcounter = 0x0, calibrationstatus = 0x0;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* Set the diff calibration mode */
    ADCx->CR |= (uint32_t)ADC_CR_ADCALDIF;

    /* Set the ADC calibration */
    ADCx->CR |= (uint32_t)ADC_CR_ADCAL;

    /* Wait until no ADC calibration is completed */
    do
    {
        calibrationstatus = ADCx->CR & ADC_CR_ADCAL;
        calibrationcounter++;
    }
    while ((calibrationcounter != CALIBRATION_TIMEOUT) && (calibrationstatus != 0x00));

    if ((uint32_t)(ADCx->CR & ADC_CR_ADCAL) == RESET)
    {
        /*Get the calibration factor from the ADC data register */
        tmpreg = (uint32_t)((ADCx->CALFACT & ADC_CALFACT_D) >> 16);
    }
    else
    {
        /* Error factor */
        tmpreg = (uint32_t)RESET;
    }
    return tmpreg;
}


/**
  * @brief  Get ADC calibration factor in the mode differential.
  * @note   Calibration factors are set by hardware after performing
  *         a calibration run using function @ref ADC_DiffCalibrationStart().
  * @param  ADCx ADC instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x7F
  */
uint32_t ADC_GetDiffCalibrationFactor(ADC_TypeDef* ADCx)
{
    uint32_t tmpreg = 0x0, calibrationcounter = 0x0, calibrationstatus = 0x0;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /*Get the calibration factor from the ADC data register */
    tmpreg = (uint32_t)((ADCx->CALFACT & ADC_CALFACT_D) >> 16);

    return tmpreg;
}


/**
  * @brief  Set ADC calibration factor in the mode single-ended
  *         for the selected ADC.
  * @note   This function is intended to set calibration parameters
  *         without having to perform a new calibration using
  *         @ref ADC_GetSingleCalibrationFactor().
  * @note   Set calibration factor must ensure ADEN=1, ADSTART
  *         and JADSTART equal to 0.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @param  Calfact_S Value between Min_Data=0x00 and Max_Data=0x7F
  * @retval None
  */
void ADC_SetSingleCalibrationFactor(ADC_TypeDef* ADCx, uint32_t Calfact_S)
{

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* Reset the ADC Single mode calibration factor */
    ADCx->CALFACT &= (uint32_t)~ADC_CALFACT_S;

    /* Set the ADC Single mode calibration factor */
    ADCx->CALFACT |= (uint32_t)Calfact_S;
}


/**
  * @brief  Set ADC calibration factor in the mode differential
  *         for the selected ADC.
  * @note   This function is intended to set calibration parameters
  *         without having to perform a new calibration using
  *         @ref ADC_GetDiffCalibrationFactor().
  * @note   Set calibration factor must ensure ADEN=1, ADSTART
  *         and JADSTART equal to 0.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @param  Calfact_D Value between Min_Data=0x00 and Max_Data=0x7F
  * @retval None
  */
void ADC_SetDiffCalibrationFactor(ADC_TypeDef* ADCx, uint32_t Calfact_D)
{

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* Reset the ADC Single mode calibration factor */
    ADCx->CALFACT &= (uint32_t)~ADC_CALFACT_D;

    /* Set the ADC Single mode calibration factor */
    ADCx->CALFACT |= (uint32_t)(Calfact_D << 16);
}



/**
  * @brief  Start Conversion for the selected ADC regular channels.
  * @note   In continuous mode, ADSTART is not cleared by hardware with the
  *         assertion of EOSEQ because the sequence is automatic relaunched
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @retval None
  */
void ADC_REG_StartOfConversion(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    ADCx->CR |= (uint32_t)ADC_CR_ADSTART;
}


/**
  * @brief  Stop the on going ADCx group regular conversions for the selected ADC.
  * @note   When ADSTP is set, any on ADCx group regular going conversion is aborted,
  *         and the ADC data register is not updated with current conversion.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @retval None
  */
void ADC_REG_StopOfConversion(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    ADCx->CR |= (uint32_t)ADC_CR_ADSTP;
}


/**
  * @brief  Start Conversion for the selected ADC injected channels.
  * @note   In continuous mode, JADSTART is not cleared by hardware with the
  *         assertion of EOSEQ because the sequence is automatic relaunched
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @retval None
  */
void ADC_INJ_StartOfConversion(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    ADCx->CR |= (uint32_t)ADC_CR_JADSTART;
}


/**
  * @brief  Stop the on going ADCx group injected conversions for the selected ADC.
  * @note   When JADSTP is set, any on ADCx group injected going conversion is aborted,
  *         and the ADC data register is not updated with current conversion.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @retval None
  */
void ADC_INJ_StopOfConversion(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    ADCx->CR |= (uint32_t)ADC_CR_JADSTP;
}


/**
  * @brief  Returns the last ADCx conversion result data for ADC regular channel.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @retval The Data conversion value.
  */
uint16_t ADC_REG_GetConversionValue(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* Return the selected ADC conversion value */
    return (uint16_t)ADCx->DR;
}


/**
  * @brief  Returns the last ADCx conversion result data for ADC injected channel.
  * @param  ADCx: where x can be 1/2/3 to select the ADCx peripheral.
  * @param  INJ_RANK can be one of the following values:
  *         @ref  ADC_INJECTED_RANK_1 : return to JDR1 data
  *         @ref  ADC_INJECTED_RANK_2 : return to JDR2 data
  *         @ref  ADC_INJECTED_RANK_3 : return to JDR3 data
  *         @ref  ADC_INJECTED_RANK_4 : return to JDR4 data
  * @retval The Data conversion value.
  */
uint16_t ADC_INJ_GetConversionValue(ADC_TypeDef* ADCx, uint32_t INJ_RANK)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_INJECTED_RANK(INJ_RANK));

    /* Return the selected ADC conversion value */
    if (INJ_RANK == ADC_INJECTED_RANK_1)
    {
        return (uint16_t)ADCx->JDR1;
    }
    else if (INJ_RANK == ADC_INJECTED_RANK_2)
    {
        return (uint16_t)ADCx->JDR2;
    }
    else if (INJ_RANK == ADC_INJECTED_RANK_3)
    {
        return (uint16_t)ADCx->JDR3;
    }
    else if (INJ_RANK == ADC_INJECTED_RANK_4)
    {
        return (uint16_t)ADCx->JDR4;
    }
    else
    {
        return 0x00;
    }
}

/**
  * @}
  */


/**
  * @brief  Get ADC multimode conversion data of ADC master, ADC slave
  *         or raw data with ADC master and slave concatenated.
  * @retval Value between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF
  */
uint32_t ADC_ReadMultiConversionData32(void)
{
    return (uint32_t)ADC_Common->CDR;
}


/**
  * @brief  Enables or disables the specified ADC DMA request.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the selected ADC DMA transfer.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   This function must be configured before group injected
  *         otherwise, the configuration of the group injected may
  *         be reset when JQDIS=1.
  * @retval None
  */
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected ADC DMA request */
        ADCx->CFGR1 |= (uint32_t)ADC_CFGR1_DMAEN;
    }
    else
    {
        /* Disable the selected ADC DMA request */
        ADCx->CFGR1 &= (uint32_t)(~ADC_CFGR1_DMAEN);
    }
}

/**
  * @brief  Enables or disables the ADC DMA request after last transfer (Single-ADC mode)
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_DMARequestMode: the ADC channel to configure.
  *          This parameter can be one of the following values:
  *            @arg ADC_DMAMode_OneShot: DMA One Shot Mode
  *            @arg ADC_DMAMode_Circular: DMA Circular Mode
  * @note   This function must be configured before group injected
  *         otherwise, the configuration of the group injected may
  *         be reset when JQDIS=1.
  *  @retval None
  */
void ADC_DMARequestModeConfig(ADC_TypeDef* ADCx, uint32_t ADC_DMARequestMode)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    ADCx->CFGR1 &= (uint32_t)~ADC_CFGR1_DMACFG;
    ADCx->CFGR1 |= (uint32_t)ADC_DMARequestMode;
}

/**
  * @}
  */
/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  ADCx: where x can be 1/2/3 to select the ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_ADRDY: ADC Ready interrupt
  *            @arg ADC_IT_EOSMP: End of sampling interrupt
  *            @arg ADC_IT_EOC: ADC group regular end of conversion interrupt
  *            @arg ADC_IT_EOSEQ: ADC group regular end of Sequence interrupt
  *            @arg ADC_IT_OVR: ADC group regular overrun interrupt
  *            @arg ADC_IT_JEOC: ADC group injected end of conversion interrupt
  *            @arg ADC_IT_JEOSEQ: ADC group injected end of Sequence interrupt
  *            @arg ADC_IT_AWD1: ADC Analog watchdog 1 interrupt
  *            @arg ADC_IT_AWD2: ADC Analog watchdog 2 interrupt
  *            @arg ADC_IT_AWD3: ADC Analog watchdog 3 interrupt
  *            @arg ADC_IT_JQOVF: ADC group injected contexts queue overflow interrupt
  * @param  NewState: new state of the specified ADC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_CONFIG_IT(ADC_IT));

    if (NewState != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        ADCx->IER |= ADC_IT;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        ADCx->IER &= (~(uint32_t)ADC_IT);
    }
}

/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADCx: where x can be 1/2/3 to select the ADC1 peripheral.
  * @param  ADC_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg ADC_FLAG_ADRDY: ADC Ready flag
  *            @arg ADC_FLAG_EOSMP: End of sampling flag
  *            @arg ADC_FLAG_EOC: ADC group regular end of conversion flag
  *            @arg ADC_FLAG_EOSEQ: ADC group regular end of Sequence flag
  *            @arg ADC_FLAG_OVR: ADC group regular overrun flag
  *            @arg ADC_FLAG_JEOC: ADC group injected end of conversion flag
  *            @arg ADC_FLAG_JEOSEQ: ADC group injected end of Sequence flag
  *            @arg ADC_FLAG_AWD1: ADC Analog watchdog 1 flag
  *            @arg ADC_FLAG_AWD2: ADC Analog watchdog 2 flag
  *            @arg ADC_FLAG_AWD3: ADC Analog watchdog 3 flag
  *            @arg ADC_FLAG_JQOVF: ADC group injected contexts queue overflow flag
  *            @arg ADC_FLAG_ADEN: ADC enable flag
  *            @arg ADC_FLAG_ADDIS: ADC disable flag
  *            @arg ADC_FLAG_ADSTART: ADC start flag
  *            @arg ADC_FLAG_ADSTP: ADC stop flag
  *            @arg ADC_FLAG_ADCAL: ADC Calibration flag
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
    FlagStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_GET_FLAG(ADC_FLAG));

    if ((uint32_t)(ADC_FLAG & 0x01000000))
    {
        tmpreg = ADCx->CR & 0xFEFFFFFF;
    }
    else
    {
        tmpreg = ADCx->ISR;
    }

    /* Check the status of the specified ADC flag */
    if ((tmpreg & ADC_FLAG) != (uint32_t)RESET)
    {
        /* ADC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_FLAG status */
    return  bitstatus;
}


/**
  * @brief  Checks whether the specified ADC MultiMode flag is set or not.
  * @param  ADCx: where x can be 1/2/3 to select the ADC1 peripheral.
  * @param  ADC_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg ADC_FLAG_ADRDY: ADC Ready flag
  *            @arg ADC_FLAG_EOSMP: End of sampling flag
  *            @arg ADC_FLAG_EOC: ADC group regular end of conversion flag
  *            @arg ADC_FLAG_EOSEQ: ADC group regular end of Sequence flag
  *            @arg ADC_FLAG_OVR: ADC group regular overrun flag
  *            @arg ADC_FLAG_JEOC: ADC group injected end of conversion flag
  *            @arg ADC_FLAG_JEOSEQ: ADC group injected end of Sequence flag
  *            @arg ADC_FLAG_AWD1: ADC Analog watchdog 1 flag
  *            @arg ADC_FLAG_AWD2: ADC Analog watchdog 2 flag
  *            @arg ADC_FLAG_AWD3: ADC Analog watchdog 3 flag
  *            @arg ADC_FLAG_JQOVF: ADC group injected contexts queue overflow flag
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetMultiFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_GET_FLAG(ADC_FLAG));

    /* Check the status of the specified ADC flag */
    if (ADCx == ADC1)
    {
        if ((ADC_Common->CSR1 & ADC_FLAG) != (uint32_t)RESET)
        {
            /* ADC_FLAG is set */
            bitstatus = SET;
        }
        else
        {
            /* ADC_FLAG is reset */
            bitstatus = RESET;
        }
    }
    else if (ADCx == ADC2)
    {
        if ((ADC_Common->CSR1 & (ADC_FLAG << 16)) != (uint32_t)RESET)
        {
            /* ADC_FLAG is set */
            bitstatus = SET;
        }
        else
        {
            /* ADC_FLAG is reset */
            bitstatus = RESET;
        }
    }
    else if (ADCx == ADC3)
    {
        if ((ADC_Common->CSR2 & ADC_FLAG) != (uint32_t)RESET)
        {
            /* ADC_FLAG is set */
            bitstatus = SET;
        }
        else
        {
            /* ADC_FLAG is reset */
            bitstatus = RESET;
        }
    }

    /* Return the ADC_FLAG status */
    return  bitstatus;
}


/**
  * @brief  Clears the ADCx's pending flags.
  * @param  ADCx: where x can be 1/2/3 to select the ADC1 peripheral.
  * @param  ADC_FLAG: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg ADC_FLAG_ADRDY: ADC Ready flag
  *            @arg ADC_FLAG_EOSMP: End of sampling flag
  *            @arg ADC_FLAG_EOC: ADC group regular end of conversion flag
  *            @arg ADC_FLAG_EOSEQ: ADC group regular end of Sequence flag
  *            @arg ADC_FLAG_OVR: ADC group regular overrun flag
  *            @arg ADC_FLAG_JEOC: ADC group injected end of conversion flag
  *            @arg ADC_FLAG_JEOSEQ: ADC group injected end of Sequence flag
  *            @arg ADC_FLAG_AWD1: ADC Analog watchdog 1 flag
  *            @arg ADC_FLAG_AWD2: ADC Analog watchdog 2 flag
  *            @arg ADC_FLAG_AWD3: ADC Analog watchdog 3 flag
  *            @arg ADC_FLAG_JQOVF: ADC group injected contexts queue overflow flag
 * @retval None
  */
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));

    /* Clear the selected ADC flags */
    ADCx->ISR = (uint32_t)ADC_FLAG;
}

/**
  * @brief  Checks whether the specified ADC interrupt has occurred or not.
  * @param  ADCx: where x can be 1/2/3 to select the ADC peripheral
  * @param  ADC_IT: specifies the ADC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_ADRDY: ADC Ready interrupt
  *            @arg ADC_IT_EOSMP: End of sampling interrupt
  *            @arg ADC_IT_EOC: ADC group regular end of conversion interrupt
  *            @arg ADC_IT_EOSEQ: ADC group regular end of Sequence interrupt
  *            @arg ADC_IT_OVR: ADC group regular overrun interrupt
  *            @arg ADC_IT_JEOC: ADC group injected end of conversion interrupt
  *            @arg ADC_IT_JEOSEQ: ADC group injected end of Sequence interrupt
  *            @arg ADC_IT_AWD1: ADC Analog watchdog 1 interrupt
  *            @arg ADC_IT_AWD2: ADC Analog watchdog 2 interrupt
  *            @arg ADC_IT_AWD3: ADC Analog watchdog 3 interrupt
  *            @arg ADC_IT_JQOVF: ADC group injected contexts queue overflow interrupt
 * @retval The new state of ADC_IT (SET or RESET).
  */
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT)
{
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_GET_IT(ADC_IT));

    /* Get the ADC_IT enable bit status */
    enablestatus = (uint32_t)(ADCx->IER & ADC_IT);

    /* Check the status of the specified ADC interrupt */
    if (((uint32_t)(ADCx->ISR & ADC_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
    {
        /* ADC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_IT is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_IT status */
    return  bitstatus;
}


/**
  * @brief  Clears the ADCx's interrupt pending bits.
  * @param  ADCx: where x can be 1/2/3 to select the ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt pending bit to clear.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_ADRDY: ADC Ready interrupt
  *            @arg ADC_IT_EOSMP: End of sampling interrupt
  *            @arg ADC_IT_EOC: ADC group regular end of conversion interrupt
  *            @arg ADC_IT_EOSEQ: ADC group regular end of Sequence interrupt
  *            @arg ADC_IT_OVR: ADC group regular overrun interrupt
  *            @arg ADC_IT_JEOC: ADC group injected end of conversion interrupt
  *            @arg ADC_IT_JEOSEQ: ADC group injected end of Sequence interrupt
  *            @arg ADC_IT_AWD1: ADC Analog watchdog 1 interrupt
  *            @arg ADC_IT_AWD2: ADC Analog watchdog 2 interrupt
  *            @arg ADC_IT_AWD3: ADC Analog watchdog 3 interrupt
  *            @arg ADC_IT_JQOVF: ADC group injected contexts queue overflow interrupt
  * @retval None
  */
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_IT)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CLEAR_IT(ADC_IT));

    /* Clear the selected ADC interrupt pending bits */
    ADCx->ISR = (uint32_t)ADC_IT;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
