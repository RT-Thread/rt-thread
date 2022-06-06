/**
  ******************************************************************************
  * @file               ft32f0xx_adc.c
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
  * @data                   2021-07-01
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx_adc.h"
#include "ft32f0xx_rcc.h"



/* ADC CFGR mask */
#define CFGR1_CLEAR_MASK           ((uint32_t)0xFFFFD203)

/* Calibration time out */
#define CALIBRATION_TIMEOUT        ((uint32_t)0x0000F000)

/**
  * @brief  Deinitializes ADC1 peripheral registers to their default reset values.
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @retval None
  */
void ADC_DeInit(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  if(ADCx == ADC1)
  {
    /* Enable ADC1 reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);

    /* Release ADC1 from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);
  }
}

/**
  * @brief  Initializes the ADCx peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @note   This function is used to configure the global features of the ADC (
  *         Resolution, Data Alignment, continuous mode activation, External
  *         trigger source and edge, Sequence Scan Direction).
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains
  *         the configuration information for the specified ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_RESOLUTION(ADC_InitStruct->ADC_Resolution));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ContinuousConvMode));
  assert_param(IS_ADC_EXT_TRIG_EDGE(ADC_InitStruct->ADC_ExternalTrigConvEdge));
  assert_param(IS_ADC_EXTERNAL_TRIG_CONV(ADC_InitStruct->ADC_ExternalTrigConv));
  assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign));
  assert_param(IS_ADC_SCAN_DIRECTION(ADC_InitStruct->ADC_ScanDirection));

  /* Get the ADCx CFGR value */
  tmpreg = ADCx->CFGR1;

  /* Clear SCANDIR, RES[1:0], ALIGN, EXTSEL[2:0], EXTEN[1:0] and CONT bits */
  tmpreg &= CFGR1_CLEAR_MASK;

  /*---------------------------- ADCx CFGR Configuration ---------------------*/

  /* Set RES[1:0] bits according to ADC_Resolution value */
  /* Set CONT bit according to ADC_ContinuousConvMode value */
  /* Set EXTEN[1:0] bits according to ADC_ExternalTrigConvEdge value */
  /* Set EXTSEL[2:0] bits according to ADC_ExternalTrigConv value */
  /* Set ALIGN bit according to ADC_DataAlign value */
  /* Set SCANDIR bit according to ADC_ScanDirection value */

  tmpreg  |= (uint32_t)(ADC_InitStruct->ADC_Resolution | ((uint32_t)(ADC_InitStruct->ADC_ContinuousConvMode) << 13) |
             ADC_InitStruct->ADC_ExternalTrigConvEdge | ADC_InitStruct->ADC_ExternalTrigConv |
             ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ScanDirection);

  /* Write to ADCx CFGR */
  ADCx->CFGR1 = tmpreg;
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
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
  /* Reset ADC init structure parameters values */
  /* Initialize the ADC_Resolution member */
  ADC_InitStruct->ADC_Resolution = ADC_Resolution_12b;

   /* Initialize the ADC_ContinuousConvMode member */
  ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;

  /* Initialize the ADC_ExternalTrigConvEdge member */
  ADC_InitStruct->ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;

  /* Initialize the ADC_ExternalTrigConv member */
  ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;

  /* Initialize the ADC_DataAlign member */
  ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;

  /* Initialize the ADC_ScanDirection member */
  ADC_InitStruct->ADC_ScanDirection = ADC_ScanDirection_Upward;
}

/**
  * @brief  Enables or disables the specified ADC peripheral.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
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
  * @brief  Configure the ADC to either be clocked by the asynchronous clock(which is
  *         independent, the dedicated 14MHz clock) or the synchronous clock derived from
  *         the APB clock of the ADC bus interface divided by 2 or 4
  * @note   This function can be called only when ADC is disabled.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_ClockMode: This parameter can be :
  *            @arg ADC_ClockMode_AsynClk: ADC clocked by the dedicated 14MHz clock
  *            @arg ADC_ClockMode_SynClkDiv2: ADC clocked by PCLK/2
  *            @arg ADC_ClockMode_SynClkDiv4: ADC clocked by PCLK/4
  * @retval None
  */
void ADC_ClockModeConfig(ADC_TypeDef* ADCx, uint32_t ADC_ClockMode)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CLOCKMODE(ADC_ClockMode));

    /* Configure the ADC Clock mode according to ADC_ClockMode */
    ADCx->CFGR2 = (uint32_t)ADC_ClockMode;

}

/**
  * @brief  Enables or disables the jitter when the ADC is clocked by PCLK div2
  *         or div4
  * @note   This function is obsolete and maintained for legacy purpose only. ADC_ClockModeConfig()
  *         function should be used instead.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_JitterOff: This parameter can be :
  *            @arg ADC_JitterOff_PCLKDiv2: Remove jitter when ADC is clocked by PLCK divided by 2
  *            @arg ADC_JitterOff_PCLKDiv4: Remove jitter when ADC is clocked by PLCK divided by 4
  * @param  NewState: new state of the ADCx jitter.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_JitterCmd(ADC_TypeDef* ADCx, uint32_t ADC_JitterOff, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_JITTEROFF(ADC_JitterOff));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Disable Jitter */
    ADCx->CFGR2 |= (uint32_t)ADC_JitterOff;
  }
  else
  {
    /* Enable Jitter */
    ADCx->CFGR2 &= (uint32_t)(~ADC_JitterOff);
  }
}

/**
  * @}
  */

/**
  * @brief  Enables or disables the ADC Power Off.
  * @note   ADC power-on and power-off can be managed by hardware to cut the
  *         consumption when the ADC is not converting.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @note   The ADC can be powered down:
  *         - During the Auto delay phase:  The ADC is powered on again at the end
  *           of the delay (until the previous data is read from the ADC data register).
  *         - During the ADC is waiting for a trigger event: The ADC is powered up
  *           at the next trigger event (when the conversion is started).
  * @param  NewState: new state of the ADCx power Off.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AutoPowerOffCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the ADC Automatic Power-Off */
    ADCx->CFGR1 |= ADC_CFGR1_AUTOFF;
  }
  else
  {
    /* Disable the ADC Automatic Power-Off */
    ADCx->CFGR1 &= (uint32_t)~ADC_CFGR1_AUTOFF;
  }
}

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
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the ADCx Auto-Delay.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_WaitModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the ADC Automatic Delayed conversion */
    ADCx->CFGR1 |= ADC_CFGR1_WAIT;
  }
  else
  {
    /* Disable the ADC Automatic Delayed conversion */
    ADCx->CFGR1 &= (uint32_t)~ADC_CFGR1_WAIT;
  }
}

/**
  * @}
  */
/**
  * @brief  Enables or disables the analog watchdog
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the ADCx Analog Watchdog.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the ADC Analog Watchdog */
    ADCx->CFGR1 |= ADC_CFGR1_AWDEN;
  }
  else
  {
    /* Disable the ADC Analog Watchdog */
    ADCx->CFGR1 &= (uint32_t)~ADC_CFGR1_AWDEN;
  }
}

/**
  * @brief  Configures the high and low thresholds of the analog watchdog.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  HighThreshold: the ADC analog watchdog High threshold value.
  *          This parameter must be a 12bit value.
  * @param  LowThreshold: the ADC analog watchdog Low threshold value.
  *          This parameter must be a 12bit value.
  * @retval None
  */
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold,
                                        uint16_t LowThreshold)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_THRESHOLD(HighThreshold));
  assert_param(IS_ADC_THRESHOLD(LowThreshold));

  /* Set the ADCx high and low threshold */
  ADCx->TR = LowThreshold | ((uint32_t)HighThreshold << 16);

}

/**
  * @brief  Configures the analog watchdog guarded single channel
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_AnalogWatchdog_Channel: the ADC channel to configure for the analog watchdog.
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
  * @note   The channel selected on the AWDCH must be also set into the CHSELR
  *         register
  * @retval None
  */
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog_Channel)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_ANALOG_WATCHDOG_CHANNEL(ADC_AnalogWatchdog_Channel));

  /* Get the old register value */
  tmpreg = ADCx->CFGR1;

  /* Clear the Analog watchdog channel select bits */
  tmpreg &= ~ADC_CFGR1_AWDCH;

  /* Set the Analog watchdog channel */
  tmpreg |= ADC_AnalogWatchdog_Channel;

  /* Store the new register value */
  ADCx->CFGR1 = tmpreg;
}

/**
  * @brief  Enables or disables the ADC Analog Watchdog Single Channel.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the ADCx ADC Analog Watchdog Single Channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AnalogWatchdogSingleChannelCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the ADC Analog Watchdog Single Channel */
    ADCx->CFGR1 |= ADC_CFGR1_AWDSGL;
  }
  else
  {
    /* Disable the ADC Analog Watchdog Single Channel */
    ADCx->CFGR1 &= (uint32_t)~ADC_CFGR1_AWDSGL;
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
    ADC->CCR |= (uint32_t)ADC_CCR_TSEN;
  }
  else
  {
    /* Disable the temperature sensor channel*/
    ADC->CCR &= (uint32_t)(~ADC_CCR_TSEN);
  }
}

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
    ADC->CCR |= (uint32_t)ADC_CCR_VREFEN;
  }
  else
  {
    /* Disable the Vrefint channel*/
    ADC->CCR &= (uint32_t)(~ADC_CCR_VREFEN);
  }
}

/**
  * @brief  Enables or disables the Vbat channel.
  * @note   This feature is not applicable for FT32F030 devices.
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
    /* Enable the Vbat channel*/
    ADC->CCR |= (uint32_t)ADC_CCR_VBATEN;
  }
  else
  {
    /* Disable the Vbat channel*/
    ADC->CCR &= (uint32_t)(~ADC_CCR_VBATEN);
  }
}

/**
  * @}
  */
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
  *            @arg ADC_Channel_10: ADC Channel10 selected,
  *            @arg ADC_Channel_11: ADC Channel11 selected,
  *            @arg ADC_Channel_12: ADC Channel12 selected,
  *            @arg ADC_Channel_13: ADC Channel13 selected,
  *            @arg ADC_Channel_14: ADC Channel14 selected,
  *            @arg ADC_Channel_15: ADC Channel15 selected,
  *            @arg ADC_Channel_16: ADC Channel16 selected
  *            @arg ADC_Channel_17: ADC Channel17 selected
  *            @arg ADC_Channel_18: ADC Channel18 selected,
  *            @arg ADC_Channel_19: ADC Channel19 selected,
  *            @arg ADC_Channel_20: ADC Channel20 selected,
  *            @arg ADC_Channel_21: ADC Channel21 selected,
  * @param  ADC_SampleTime: The sample time value to be set for the selected channel.
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
void ADC_ChannelConfig(ADC_TypeDef* ADCx, uint32_t ADC_Channel, uint32_t ADC_SampleTime)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));

  /* Configure the ADC Channel */
  ADCx->CHSELR |= (uint32_t)ADC_Channel;

  /* Clear the Sampling time Selection bits */
  tmpreg &= ~ADC_SMPR1_SMPR;

  /* Set the ADC Sampling Time register */
  tmpreg |= (uint32_t)ADC_SampleTime;

  /* Configure the ADC Sample time register */
  ADCx->SMPR = tmpreg ;
}

/**
  * @brief  Enable the Continuous mode for the selected ADCx channels.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
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
  * @brief  Enable the discontinuous mode for the selected ADC channels.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the discontinuous mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   It is not possible to have both discontinuous mode and continuous mode
  *         enabled. In this case (If DISCEN and CONT are Set), the ADC behaves
  *         as if continuous mode was disabled
  * @retval None
  */
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
  {
    /* Enable the Discontinuous mode */
    ADCx->CFGR1 |= (uint32_t)ADC_CFGR1_DISCEN;
  }
  else
  {
    /* Disable the Discontinuous mode */
    ADCx->CFGR1 &= (uint32_t)(~ADC_CFGR1_DISCEN);
  }
}

/**
  * @brief  Enable the Overrun mode for the selected ADC channels.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
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
  * @brief  Active the Calibration operation for the selected ADC.
  * @note   The Calibration can be initiated only when ADC is still in the
  *         reset configuration (ADEN must be equal to 0).
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @retval ADC Calibration factor
  */
uint32_t ADC_GetCalibrationFactor(ADC_TypeDef* ADCx)
{
  uint32_t tmpreg = 0, calibrationcounter = 0, calibrationstatus = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Set the ADC calibartion */
  ADCx->CR |= (uint32_t)ADC_CR_ADCAL;

  /* Wait until no ADC calibration is completed */
  do
  {
    calibrationstatus = ADCx->CR & ADC_CR_ADCAL;
    calibrationcounter++;
  } while((calibrationcounter != CALIBRATION_TIMEOUT) && (calibrationstatus != 0x00));

  if((uint32_t)(ADCx->CR & ADC_CR_ADCAL) == RESET)
  {
    /*Get the calibration factor from the ADC data register */
    tmpreg = ADCx->DR;
  }
  else
  {
    /* Error factor */
    tmpreg = 0x00000000;
  }
  return tmpreg;
}

/**
  * @brief  Stop the on going conversions for the selected ADC.
  * @note   When ADSTP is set, any on going conversion is aborted, and the ADC
  *         data register is not updated with current conversion.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @retval None
  */
void ADC_StopOfConversion(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  ADCx->CR |= (uint32_t)ADC_CR_ADSTP;
}

/**
  * @brief  Start Conversion for the selected ADC channels.
  * @note   In continuous mode, ADSTART is not cleared by hardware with the
  *         assertion of EOSEQ because the sequence is automatic relaunched
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @retval None
  */
void ADC_StartOfConversion(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  ADCx->CR |= (uint32_t)ADC_CR_ADSTART;
}

/**
  * @brief  Returns the last ADCx conversion result data for ADC channel.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @retval The Data conversion value.
  */
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Return the selected ADC conversion value */
  return (uint16_t) ADCx->DR;
}

/**
  * @}
  */
/**
  * @brief  Enables or disables the specified ADC DMA request.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the selected ADC DMA transfer.
  *          This parameter can be: ENABLE or DISABLE.
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
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_ADRDY: ADC ready interrupt
  *            @arg ADC_IT_EOSMP: End of sampling interrupt
  *            @arg ADC_IT_EOC: End of conversion interrupt
  *            @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *            @arg ADC_IT_OVR: overrun interrupt
  *            @arg ADC_IT_AWD: Analog watchdog interrupt
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
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg ADC_FLAG_AWD: Analog watchdog flag
  *            @arg ADC_FLAG_OVR: Overrun flag
  *            @arg ADC_FLAG_EOSEQ: End of Sequence flag
  *            @arg ADC_FLAG_EOC: End of conversion flag
  *            @arg ADC_FLAG_EOSMP: End of sampling flag
  *            @arg ADC_FLAG_ADRDY: ADC Ready flag
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

  if((uint32_t)(ADC_FLAG & 0x01000000))
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
  * @brief  Clears the ADCx's pending flags.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_FLAG: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg ADC_FLAG_AWD: Analog watchdog flag
  *            @arg ADC_FLAG_EOC: End of conversion flag
  *            @arg ADC_FLAG_ADRDY: ADC Ready flag
  *            @arg ADC_FLAG_EOSMP: End of sampling flag
  *            @arg ADC_FLAG_EOSEQ: End of Sequence flag
  *            @arg ADC_FLAG_OVR: Overrun flag
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
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral
  * @param  ADC_IT: specifies the ADC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_ADRDY: ADC ready interrupt
  *            @arg ADC_IT_EOSMP: End of sampling interrupt
  *            @arg ADC_IT_EOC: End of conversion interrupt
  *            @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *            @arg ADC_IT_OVR: overrun interrupt
  *            @arg ADC_IT_AWD: Analog watchdog interrupt
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
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_IT: specifies the ADC interrupt pending bit to clear.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_ADRDY: ADC ready interrupt
  *            @arg ADC_IT_EOSMP: End of sampling interrupt
  *            @arg ADC_IT_EOC: End of conversion interrupt
  *            @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *            @arg ADC_IT_OVR: overrun interrupt
  *            @arg ADC_IT_AWD: Analog watchdog interrupt
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
  * @brief  select the ADC VREF.
  * @param  ADC_Vrefsel: The sVREF value to be set for the ADC.
             This parameter can be one of the following values:
  *            @arg ADC_Vrefsel_0_625V: VREF 0.625V selected
  *            @arg ADC_Vrefsel_1_5V:   VREF 1.5V selected
  *            @arg ADC_Vrefsel_2_5V:   VREF 2.5V selected
  *            @arg ADC_Vrefsel_VDDA:   VREF VDDA selected
  * @retval None
  */
void ADC_VrefselConfig(uint32_t ADC_Vrefsel)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_ADC_Vrefsel(ADC_Vrefsel));

    /* Read CR2 register */
    tmpreg = ADC->CR2;

    /* Clear the Vref Selection bits */
    tmpreg &= ~((uint32_t)0x0000000E) ;

    /* Set the ADC Vref register */
    tmpreg |= (uint32_t)ADC_Vrefsel;

    /* Configure the ADC Vref register */
    ADC->CR2 = tmpreg;
}

/**
  * @brief  Enable Reference voltage halved.
  * @param  NewState: new state of the reference voltage halved.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   None
  * @retval None
  */
void ADC_VrefDecibCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Discontinuous mode */
        ADC->CR2 |= (uint32_t)ADC_CR2_VREF_DECIB;
    }
    else
    {
        /* Disable the Discontinuous mode */
        ADC->CR2 &= (uint32_t)(~ADC_CR2_VREF_DECIB);
    }
}

/**
  * @brief  Sampling hold circuit sampling enable or disable.
  * @param  SmpEn:
  *         @arg    ADC_IOSH1_SMPEN
  *         @arg    ADC_IOSH2_SMPEN
  * @param  NewState: new state of SMP.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   None
  * @retval None
  */
void ADC_IoshSmpCmd(uint32_t SmpEn, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_SMPEN(SmpEn));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        ADC->CR2 |= SmpEn;
    }
    else
    {
        ADC->CR2 &= ~SmpEn;
    }
}

/**
  * @brief  The hold enable bit of the sample-hold circuit.
  * @param  SmpEn:
  *         @arg    ADC_IOSH1_AMPEN
  *         @arg    ADC_IOSH2_AMPEN
  * @param  NewState: new state of AMP.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   None
  * @retval None
  */
void ADC_IoshAmpCmd(uint32_t AmpEn, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_AMPEN(AmpEn));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        ADC->CR2 |= AmpEn;
    }
    else
    {
        ADC->CR2 &= ~AmpEn;
    }
}

/**
  * @brief  Input source selection.
  * @param  Ioshx:
  *         @arg    ADC_CR2_IOSH1_SEL
  *         @arg    ADC_CR2_IOSH2_SEL
  * @param  SmpSel:
  *         if Ioshx is ADC_CR2_IOSH1_SEL,the SmpSel can be
  *         @arg    ADC_IOSH1_SMPSEL_PB1
  *         @arg    ADC_IOSH1_SMPSEL_OP1OUT
  *         if Ioshx is ADC_CR2_IOSH2_SEL,the SmpSel can be
  *         @arg    ADC_IOSH2_SMPSEL_PB0
  *         @arg    ADC_IOSH2_SMPSEL_OP2OUT
  * @note   None
  * @retval None
  */
#if defined (FT32F072xB)
void ADC_IoshSmpSel(uint32_t Ioshx, uint32_t SmpSel)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_ADC_IOSH(Ioshx));
    assert_param(IS_ADC_SMPSEL(SmpSel));

    /* Read CR2 register */
    tmpreg = ADC->CR2;

    if (Ioshx != ADC_CR2_IOSH1_SEL)
    {
        /* IOSH2 */
        tmpreg &= ~ADC_CR2_IOSH2_SEL;
    }
    else
    {
        /* IOSH1 */
        tmpreg &= ~ADC_CR2_IOSH1_SEL;
    }

    tmpreg |= SmpSel;

    /* Config CR2 register */
    ADC->CR2 = tmpreg;
}
/**
  * @brief  The hold enable bit of the sample-hold circuit.
  * @param  SmpModBit:
  *         @arg    ADC_CR2_IOSH1_SMPMOD
  *         @arg    ADC_CR2_IOSH2_SMPMOD
  * @param  Mode:
  *         @arg    ADC_SMP_SOFTWARE_MODE
  *         @arg    ADC_SMP_HARDWARE_MODE
  * @note   None
  * @retval None
  */
void ADC_IoshSmpMod(uint32_t SmpModBit, uint32_t Mode)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_ADC_SMPMOD(SmpModBit));
    assert_param(IS_ADC_MODE(Mode));

    /* Read CR2 register */
    tmpreg = ADC->CR2;

    if (Mode != ADC_SMP_SOFTWARE_MODE)
    {
        /* Hardware mode */
        if (SmpModBit != ADC_CR2_IOSH1_SMPMOD)
        {
            /* IOSH2 */
            tmpreg |= ADC_CR2_IOSH2_SMPMOD | ADC_CR2_IOSH2_AMPEN;
        }
        else
        {
            /* IOSH1 */
            tmpreg |= ADC_CR2_IOSH1_SMPMOD | ADC_CR2_IOSH1_AMPEN;
        }
    }
    else
    {
        /* Software mode */
        if (SmpModBit != ADC_CR2_IOSH1_SMPMOD)
        {
            /* IOSH2 */
            tmpreg &= ~ADC_CR2_IOSH2_AMPEN;
            tmpreg |= ADC_CR2_IOSH2_SMPMOD | ADC_CR2_IOSH2_SMPEN;
        }
        else
        {
            /* IOSH1 */
            tmpreg &= ~ADC_CR2_IOSH1_AMPEN;
            tmpreg |= ADC_CR2_IOSH1_SMPMOD | ADC_CR2_IOSH1_SMPEN;
        }
    }

    /* Config CR2 register */
    ADC->CR2 = tmpreg;
}
/**
  * @brief  External hardware trigger mode config.
  * @param  NewState: new state of .
  *          This parameter can be: ENABLE or DISABLE.
  * @note   None
  * @retval None
  */
void ADC_ExtModeCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        ADC1->ETCR |= ADC_ETCR_EXTMOD;
    }
    else
    {
        ADC1->ETCR &= ~ADC_ETCR_EXTMOD;
    }
}

/**
  * @brief  Stop sampling configuration after triggering.
  * @param  NewState: new state of .
  *          This parameter can be: ENABLE or DISABLE.
  * @note   None
  * @retval None
  */
void ADC_TrgdDisSmpCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        ADC1->ETCR |= ADC_ETCR_TRGDISSMP;
    }
    else
    {
        ADC1->ETCR &= ~ADC_ETCR_TRGDISSMP;
    }
}
/**
  * @brief  The delay time of The external hardware triggers.
  * @param  ExtDly: 0~1023.
  * @note   None
  * @retval None
  */
void ADC_ExtDlyConfig(uint32_t ExtDly)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_ADC_EXTDLY(ExtDly));

    /* Read ETCR register */
    tmpreg = ADC1->ETCR;

    /* Clear EXTDLY */
    tmpreg &= ~ADC_ETCR_EXTDLY;

    /* Config EXTDLY */
    tmpreg |= ExtDly;

    /* Config ETCR */
    ADC1->ETCR = tmpreg;
}

/**
  * @brief  Rising edge triggering config.
  * @param  Rtenx:This parameter can be :
  *         ADC_RTENR_RTEN or ADC_RTENR_RTEN_0  ~ ADC_RTENR_RTEN_18
  * @param  NewState: new state of .
  *          This parameter can be: ENABLE or DISABLE.
  * @note   None
  * @retval None
  */
void ADC_RtenCmd(uint32_t Rtenx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_RTEN(Rtenx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        ADC1->RTENR |= Rtenx;
    }
    else
    {
        ADC1->RTENR &= ~Rtenx;
    }
}

/**
  * @brief  Falling edge triggering config.
  * @param  Ftenx:This parameter can be :
  *         ADC_FTENR_RTEN or ADC_FTENR_RTEN_0  ~ ADC_FTENR_RTEN_18
  * @param  NewState: new state of .
  *          This parameter can be: ENABLE or DISABLE.
  * @note   None
  * @retval None
  */
void ADC_FtenCmd(uint32_t Ftenx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_FTEN(Ftenx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        ADC1->FTENR |= Ftenx;
    }
    else
    {
        ADC1->FTENR &= ~Ftenx;
    }
}

#endif
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
