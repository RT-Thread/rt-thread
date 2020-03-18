/**
 **************************************************************************
 * File Name    : at32f4xx_adc.c
 * Description  : at32f4xx ADC source file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_adc.h"
#include "at32f4xx_rcc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup ADC
  * @brief ADC driver modules
  * @{
  */

/** @defgroup ADC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ADC_Private_Defines
  * @{
  */

/* ADC DISCNUM mask */
#define CTRL1_DISCNUM_Reset         ((uint32_t)0xFFFF1FFF)

/* ADC DISCEN mask */
#define CTRL1_RDISCEN_Set           ((uint32_t)0x00000800)
#define CTRL1_RDISCEN_Rst           ((uint32_t)0xFFFFF7FF)

/* ADC JAUTO mask */
#define CTRL1_JAUT_Set              ((uint32_t)0x00000400)
#define CTRL1_JAUT_Rst              ((uint32_t)0xFFFFFBFF)

/* ADC JDISCEN mask */
#define CTRL1_JDISCEN_Set           ((uint32_t)0x00001000)
#define CTRL1_JDISCEN_Rst           ((uint32_t)0xFFFFEFFF)

/* ADC AWDCH mask */
#define CTRL1_AWDCH_Rst             ((uint32_t)0xFFFFFFE0)

/* ADC Analog watchdog enable mode mask */
#define CTRL1_AWDMode_Rst           ((uint32_t)0xFF3FFDFF)

/* CTRL1 register Mask */
#define CTRL1_CLEAR_MASK            ((uint32_t)0xFFF0FEFF)

/* ADC ADON mask */
#define CTRL2_ADON_Set              ((uint32_t)0x00000001)
#define CTRL2_ADON_Rst              ((uint32_t)0xFFFFFFFE)

/* ADC DMA mask */
#define CTRL2_DMA_Set               ((uint32_t)0x00000100)
#define CTRL2_DMA_Rst               ((uint32_t)0xFFFFFEFF)

/* ADC RSTCAL mask */
#define CTRL2_RSTCAL_Set            ((uint32_t)0x00000008)

/* ADC CAL mask */
#define CTRL2_CAL_Set               ((uint32_t)0x00000004)

/* ADC SWSTART mask */
#define CTRL2_SWSTR_Set             ((uint32_t)0x00400000)

/* ADC EXTTRIG mask */
#define CTRL2_EXTTRIG_Set           ((uint32_t)0x00100000)
#define CTRL2_EXTTRIG_Rst           ((uint32_t)0xFFEFFFFF)

/* ADC Software start mask */
#define CTRL2_EXTTRIG_SWSTR_Set     ((uint32_t)0x00500000)
#define CTRL2_EXTTRIG_SWSTR_Rst     ((uint32_t)0xFFAFFFFF)

/* ADC JEXTSEL mask */
#define CTRL2_JEXTSEL_Rst           ((uint32_t)0xFEFF8FFF)

/* ADC JEXTTRIG mask */
#define CTRL2_JEXTTRIG_Set          ((uint32_t)0x00008000)
#define CTRL2_JEXTTRIG_Rst          ((uint32_t)0xFFFF7FFF)

/* ADC JSWSTART mask */
#define CTRL2_JSWSTR_Set            ((uint32_t)0x00200000)

/* ADC injected software start mask */
#define CTRL2_JEXTTRIG_JSWSTR_Set   ((uint32_t)0x00208000)
#define CTRL2_JEXTTRIG_JSWSTR_Rst   ((uint32_t)0xFFDF7FFF)

/* ADC TSPD mask */
#define CTRL2_TSVREFE_Set           ((uint32_t)0x00800000)
#define CTRL2_TSVREFE_Rst           ((uint32_t)0xFF7FFFFF)

/* CTRL2 register Mask */
#define CTRL2_CLEAR_Msk             ((uint32_t)0xFDF1F7FD)

/* ADC SQx mask */
#define RSQ3_SQ_Set                 ((uint32_t)0x0000001F)
#define RSQ2_SQ_Set                 ((uint32_t)0x0000001F)
#define RSQ1_SQ_Set                 ((uint32_t)0x0000001F)

/* SQR1 register Mask */
#define RSQ1_CLEAR_Msk              ((uint32_t)0xFF0FFFFF)

/* ADC JSQx mask */
#define JSQR_JSQ_Set                ((uint32_t)0x0000001F)

/* ADC JL mask */
#define JSQR_JLEN_Set               ((uint32_t)0x00300000)
#define JSQR_JLEN_Rst               ((uint32_t)0xFFCFFFFF)

/* ADC SMPx mask */
#define SMPT1_SMP_Set               ((uint32_t)0x00000007)
#define SMPT2_SMP_Set               ((uint32_t)0x00000007)

/* ADC JDRx registers offset */
#define JDOR_Offset                 ((uint8_t)0x28)

/* ADC1 DR register base address */
#define DOR_ADDRESS                 ((uint32_t)0x4001244C)

/**
  * @}
  */

/** @defgroup ADC_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ADC_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup ADC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ADC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the ADCx peripheral registers to their default reset values.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @retval None
  */
void ADC_Reset(ADC_Type* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  if (ADCx == ADC1)
  {
    /* Enable ADC1 reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_ADC1, ENABLE);
    /* Release ADC1 from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_ADC1, DISABLE);
  }
  else if (ADCx == ADC2)
  {
    /* Enable ADC2 reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_ADC2, ENABLE);
    /* Release ADC2 from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_ADC2, DISABLE);
  }
#ifdef AT32F403xx
  else if (ADCx == ADC3)
  {
    /* Enable ADC3 reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_ADC3, ENABLE);
    /* Release ADC3 from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_ADC3, DISABLE);
  }
#endif
}

/**
  * @brief  Initializes the ADCx peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_InitStruct: pointer to an ADC_InitType structure that contains
  *         the configuration information for the specified ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_Type* ADCx, ADC_InitType* ADC_InitStruct)
{
  uint32_t tmpreg1 = 0;
  uint8_t tmpreg2 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_MODE(ADC_InitStruct->ADC_Mode));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ScanMode));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ContinuousMode));
  assert_param(IS_ADC_EXT_TRIG(ADC_InitStruct->ADC_ExternalTrig));
  assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign));
  assert_param(IS_ADC_REGULAR_LENGTH(ADC_InitStruct->ADC_NumOfChannel));

  /*---------------------------- ADCx CTRL1 Configuration -----------------*/
  /* Get the ADCx CTRL1 value */
  tmpreg1 = ADCx->CTRL1;
  /* Clear DUALMOD and SCAN bits */
  tmpreg1 &= CTRL1_CLEAR_MASK;
  /* Configure ADCx: Dual mode and scan conversion mode */
  /* Set DUALMOD bits according to ADC_Mode value */
  /* Set SCAN bit according to ADC_ScanConvMode value */
  tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_Mode | ((uint32_t)ADC_InitStruct->ADC_ScanMode << 8));
  /* Write to ADCx CTRL1 */
  ADCx->CTRL1 = tmpreg1;

  /*---------------------------- ADCx CTRL2 Configuration -----------------*/
  /* Get the ADCx CTRL2 value */
  tmpreg1 = ADCx->CTRL2;
  /* Clear CONT, ALIGN and EXTSEL bits */
  tmpreg1 &= CTRL2_CLEAR_Msk;
  /* Configure ADCx: external trigger event and continuous conversion mode */
  /* Set ALIGN bit according to ADC_DataAlign value */
  /* Set EXTSEL bits according to ADC_ExternalTrigConv value */
  /* Set CONT bit according to ADC_ContinuousConvMode value */
  tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ExternalTrig |
                        ((uint32_t)ADC_InitStruct->ADC_ContinuousMode << 1));
  /* Write to ADCx CTRL2 */
  ADCx->CTRL2 = tmpreg1;

  /*---------------------------- ADCx SQR1 Configuration -----------------*/
  /* Get the ADCx SQR1 value */
  tmpreg1 = ADCx->RSQ1;
  /* Clear L bits */
  tmpreg1 &= RSQ1_CLEAR_Msk;
  /* Configure ADCx: regular channel sequence length */
  /* Set L bits according to ADC_NbrOfChannel value */
  tmpreg2 |= (uint8_t) (ADC_InitStruct->ADC_NumOfChannel - (uint8_t)1);
  tmpreg1 |= (uint32_t)tmpreg2 << 20;
  /* Write to ADCx SQR1 */
  ADCx->RSQ1 = tmpreg1;
}

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @param  ADC_InitStruct : pointer to an ADC_InitType structure which will be initialized.
  * @retval None
  */
void ADC_StructInit(ADC_InitType* ADC_InitStruct)
{
  /* Reset ADC init structure parameters values */
  /* Initialize the ADC_Mode member */
  ADC_InitStruct->ADC_Mode = ADC_Mode_Independent;
  /* initialize the ADC_ScanConvMode member */
  ADC_InitStruct->ADC_ScanMode = DISABLE;
  /* Initialize the ADC_ContinuousConvMode member */
  ADC_InitStruct->ADC_ContinuousMode = DISABLE;
  /* Initialize the ADC_ExternalTrigConv member */
  ADC_InitStruct->ADC_ExternalTrig = ADC_ExternalTrig_TMR1_CC1_ADC12;
  /* Initialize the ADC_DataAlign member */
  ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;
  /* Initialize the ADC_NbrOfChannel member */
  ADC_InitStruct->ADC_NumOfChannel = 1;
}

/**
  * @brief  Enables or disables the specified ADC peripheral.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  NewState: new state of the ADCx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Ctrl(ADC_Type* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the ADON bit to wake up the ADC from power down mode */
    ADCx->CTRL2 |= CTRL2_ADON_Set;
  }
  else
  {
    /* Disable the selected ADC peripheral */
    ADCx->CTRL2 &= CTRL2_ADON_Rst;
  }
}

/**
  * @brief  Enables or disables the specified ADC DMA request.
  * @param  ADCx: where x can be 1 or 3 to select the ADC peripheral.
  *   Note: ADC2 hasn't a DMA capability.
  * @param  NewState: new state of the selected ADC DMA transfer.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DMACtrl(ADC_Type* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_DMA_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC DMA request */
    ADCx->CTRL2 |= CTRL2_DMA_Set;
  }
  else
  {
    /* Disable the selected ADC DMA request */
    ADCx->CTRL2 &= CTRL2_DMA_Rst;
  }
}

/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_INT: specifies the ADC interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg ADC_INT_EC: End of conversion interrupt mask
  *     @arg ADC_INT_AWD: Analog watchdog interrupt mask
  *     @arg ADC_INT_JEC: End of injected conversion interrupt mask
  * @param  NewState: new state of the specified ADC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_INTConfig(ADC_Type* ADCx, uint16_t ADC_INT, FunctionalState NewState)
{
  uint8_t itmask = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_ADC_INT(ADC_INT));
  /* Get the ADC INT index */
  itmask = (uint8_t)ADC_INT;

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC interrupts */
    ADCx->CTRL1 |= itmask;
  }
  else
  {
    /* Disable the selected ADC interrupts */
    ADCx->CTRL1 &= (~(uint32_t)itmask);
  }
}

/**
  * @brief  Resets the selected ADC calibration registers.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @retval None
  */
void ADC_RstCalibration(ADC_Type* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Resets the selected ADC calibration registers */
  ADCx->CTRL2 |= CTRL2_RSTCAL_Set;
}

/**
  * @brief  Gets the selected ADC reset calibration registers status.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @retval The new state of ADC reset calibration registers (SET or RESET).
  */
FlagStatus ADC_GetResetCalibrationStatus(ADC_Type* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Check the status of RSTCAL bit */
  if ((ADCx->CTRL2 & CTRL2_RSTCAL_Set) != (uint32_t)RESET)
  {
    /* RSTCAL bit is set */
    bitstatus = SET;
  }
  else
  {
    /* RSTCAL bit is reset */
    bitstatus = RESET;
  }

  /* Return the RSTCAL bit status */
  return  bitstatus;
}

/**
  * @brief  Starts the selected ADC calibration process.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @retval None
  */
void ADC_StartCalibration(ADC_Type* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Enable the selected ADC calibration process */
  ADCx->CTRL2 |= CTRL2_CAL_Set;
}

/**
  * @brief  Gets the selected ADC calibration status.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @retval The new state of ADC calibration (SET or RESET).
  */
FlagStatus ADC_GetCalibrationStatus(ADC_Type* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Check the status of CAL bit */
  if ((ADCx->CTRL2 & CTRL2_CAL_Set) != (uint32_t)RESET)
  {
    /* CAL bit is set: calibration on going */
    bitstatus = SET;
  }
  else
  {
    /* CAL bit is reset: end of calibration */
    bitstatus = RESET;
  }

  /* Return the CAL bit status */
  return  bitstatus;
}

/**
  * @brief  Enables or disables the selected ADC software start conversion .
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  NewState: new state of the selected ADC software start conversion.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_SoftwareStartConvCtrl(ADC_Type* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC conversion on external event and start the selected
       ADC conversion */
    ADCx->CTRL2 |= CTRL2_EXTTRIG_SWSTR_Set;
  }
  else
  {
    /* Disable the selected ADC conversion on external event and stop the selected
       ADC conversion */
    ADCx->CTRL2 &= CTRL2_EXTTRIG_SWSTR_Rst;
  }
}

/**
  * @brief  Gets the selected ADC Software start conversion Status.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @retval The new state of ADC software start conversion (SET or RESET).
  */
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_Type* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Check the status of SWSTART bit */
  if ((ADCx->CTRL2 & CTRL2_SWSTR_Set) != (uint32_t)RESET)
  {
    /* SWSTART bit is set */
    bitstatus = SET;
  }
  else
  {
    /* SWSTART bit is reset */
    bitstatus = RESET;
  }

  /* Return the SWSTART bit status */
  return  bitstatus;
}

/**
  * @brief  Configures the discontinuous mode for the selected ADC regular
  *         group channel.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  Number: specifies the discontinuous mode regular channel
  *         count value. This number must be between 1 and 8.
  * @retval None
  */
void ADC_DiscModeChannelCountConfig(ADC_Type* ADCx, uint8_t Number)
{
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_REGULAR_DISC_NUMBER(Number));
  /* Get the old register value */
  tmpreg1 = ADCx->CTRL1;
  /* Clear the old discontinuous mode channel count */
  tmpreg1 &= CTRL1_DISCNUM_Reset;
  /* Set the discontinuous mode channel count */
  tmpreg2 = Number - 1;
  tmpreg1 |= tmpreg2 << 13;
  /* Store the new register value */
  ADCx->CTRL1 = tmpreg1;
}

/**
  * @brief  Enables or disables the discontinuous mode on regular group
  *         channel for the specified ADC
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  NewState: new state of the selected ADC discontinuous mode
  *         on regular group channel.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DiscModeCtrl(ADC_Type* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC regular discontinuous mode */
    ADCx->CTRL1 |= CTRL1_RDISCEN_Set;
  }
  else
  {
    /* Disable the selected ADC regular discontinuous mode */
    ADCx->CTRL1 &= CTRL1_RDISCEN_Rst;
  }
}

/**
  * @brief  Configures for the selected ADC regular channel its corresponding
  *         rank in the sequencer and its sample time.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure.
  *   This parameter can be one of the following values:
  *     @arg ADC_Channel_0: ADC Channel0 selected
  *     @arg ADC_Channel_1: ADC Channel1 selected
  *     @arg ADC_Channel_2: ADC Channel2 selected
  *     @arg ADC_Channel_3: ADC Channel3 selected
  *     @arg ADC_Channel_4: ADC Channel4 selected
  *     @arg ADC_Channel_5: ADC Channel5 selected
  *     @arg ADC_Channel_6: ADC Channel6 selected
  *     @arg ADC_Channel_7: ADC Channel7 selected
  *     @arg ADC_Channel_8: ADC Channel8 selected
  *     @arg ADC_Channel_9: ADC Channel9 selected
  *     @arg ADC_Channel_10: ADC Channel10 selected
  *     @arg ADC_Channel_11: ADC Channel11 selected
  *     @arg ADC_Channel_12: ADC Channel12 selected
  *     @arg ADC_Channel_13: ADC Channel13 selected
  *     @arg ADC_Channel_14: ADC Channel14 selected
  *     @arg ADC_Channel_15: ADC Channel15 selected
  *     @arg ADC_Channel_16: ADC Channel16 selected
  *     @arg ADC_Channel_17: ADC Channel17 selected
  * @param  Rank: The rank in the regular group sequencer. This parameter must be between 1 to 16.
  * @param  ADC_SampleTime: The sample time value to be set for the selected channel.
  *   This parameter can be one of the following values:
  *     @arg ADC_SampleTime_1_5: Sample time equal to 1.5 cycles
  *     @arg ADC_SampleTime_7_5: Sample time equal to 7.5 cycles
  *     @arg ADC_SampleTime_13_5: Sample time equal to 13.5 cycles
  *     @arg ADC_SampleTime_28_5: Sample time equal to 28.5 cycles
  *     @arg ADC_SampleTime_41_5: Sample time equal to 41.5 cycles
  *     @arg ADC_SampleTime_55_5: Sample time equal to 55.5 cycles
  *     @arg ADC_SampleTime_71_5: Sample time equal to 71.5 cycles
  *     @arg ADC_SampleTime_239_5: Sample time equal to 239.5 cycles
  * @retval None
  */
void ADC_RegularChannelConfig(ADC_Type* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_REGULAR_RANK(Rank));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));

  /* if ADC_Channel_10 ... ADC_Channel_17 is selected */
  if (ADC_Channel > ADC_Channel_9)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPT1;
    /* Calculate the mask to clear */
    tmpreg2 = SMPT1_SMP_Set << (3 * (ADC_Channel - 10));
    /* Clear the old channel sample time */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
    /* Set the new channel sample time */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SMPT1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPT2;
    /* Calculate the mask to clear */
    tmpreg2 = SMPT2_SMP_Set << (3 * ADC_Channel);
    /* Clear the old channel sample time */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
    /* Set the new channel sample time */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SMPT2 = tmpreg1;
  }

  /* For Rank 1 to 6 */
  if (Rank < 7)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->RSQ3;
    /* Calculate the mask to clear */
    tmpreg2 = RSQ3_SQ_Set << (5 * (Rank - 1));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 1));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->RSQ3 = tmpreg1;
  }
  /* For Rank 7 to 12 */
  else if (Rank < 13)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->RSQ2;
    /* Calculate the mask to clear */
    tmpreg2 = RSQ2_SQ_Set << (5 * (Rank - 7));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 7));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->RSQ2 = tmpreg1;
  }
  /* For Rank 13 to 16 */
  else
  {
    /* Get the old register value */
    tmpreg1 = ADCx->RSQ1;
    /* Calculate the mask to clear */
    tmpreg2 = RSQ1_SQ_Set << (5 * (Rank - 13));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 13));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->RSQ1 = tmpreg1;
  }
}

/**
  * @brief  Enables or disables the ADCx conversion through external trigger.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  NewState: new state of the selected ADC external trigger start of conversion.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ExternalTrigConvCtrl(ADC_Type* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC conversion on external event */
    ADCx->CTRL2 |= CTRL2_EXTTRIG_Set;
  }
  else
  {
    /* Disable the selected ADC conversion on external event */
    ADCx->CTRL2 &= CTRL2_EXTTRIG_Rst;
  }
}

/**
  * @brief  Returns the last ADCx conversion result data for regular channel.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @retval The Data conversion value.
  */
uint16_t ADC_GetConversionValue(ADC_Type* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Return the selected ADC conversion value */
  return (uint16_t) ADCx->RDOR;
}

/**
  * @brief  Returns the last ADC1 and ADC2 conversion result data in dual mode.
  * @retval The Data conversion value.
  */
uint32_t ADC_GetDualModeConversionValue(void)
{
  /* Return the dual mode conversion value */
  return (*(__IO uint32_t *) DOR_ADDRESS);
}

/**
  * @brief  Enables or disables the selected ADC automatic injected group
  *         conversion after regular one.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  NewState: new state of the selected ADC auto injected conversion
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AutoInjectedConvCtrl(ADC_Type* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC automatic injected group conversion */
    ADCx->CTRL1 |= CTRL1_JAUT_Set;
  }
  else
  {
    /* Disable the selected ADC automatic injected group conversion */
    ADCx->CTRL1 &= CTRL1_JAUT_Rst;
  }
}

/**
  * @brief  Enables or disables the discontinuous mode for injected group
  *         channel for the specified ADC
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  NewState: new state of the selected ADC discontinuous mode
  *         on injected group channel.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_InjectedDiscModeCtrl(ADC_Type* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC injected discontinuous mode */
    ADCx->CTRL1 |= CTRL1_JDISCEN_Set;
  }
  else
  {
    /* Disable the selected ADC injected discontinuous mode */
    ADCx->CTRL1 &= CTRL1_JDISCEN_Rst;
  }
}

/**
  * @brief  Configures the ADCx external trigger for injected channels conversion.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_ExternalTrigInjecConv: specifies the ADC trigger to start injected conversion.
  *   This parameter can be one of the following values:
  *     @arg ADC_ExternalTrigInjec_TMR2_TRGO_ADC12: Timer2 TRGO event selected (for ADC1, ADC2)
  *     @arg ADC_ExternalTrigInjec_TMR2_CC1_ADC12: Timer2 capture compare1 selected (for ADC1, ADC2)
  *     @arg ADC_ExternalTrigInjec_TMR3_CC4_ADC12: Timer3 capture compare4 selected (for ADC1, ADC2)
  *     @arg ADC_ExternalTrigInjec_TMR4_TRGO_ADC12: Timer4 TRGO event selected (for ADC1, ADC2)
  *     @arg ADC_ExternalTrigInjec_Ext_INT15_TMR8_CC4_ADC12: External interrupt line 15 or Timer8 capture compare4 event selected (for ADC1 and ADC2)
  *     @arg ADC_ExternalTrigInjec_TMR8_CC1_ADC12: Timer8 capture compare1 selected (for ADC1, ADC2)

  *     @arg ADC_ExternalTrigInjec_TMR1_TRGO: Timer1 TRGO event selected (for ADC1, ADC2 and ADC3)
  *     @arg ADC_ExternalTrigInjec_TMR1_CC4: Timer1 capture compare4 selected (for ADC1, ADC2 and ADC3)
  *     @arg ADC_ExternalTrigInjec_TMR15_CC1: Timer15 capture compare1 selected (for ADC1, ADC2 and ADC3)
  *     @arg ADC_ExternalTrigInjec_TMR15_CC2: Timer15 capture compare2 selected (for ADC1, ADC2 and ADC3)
  *     @arg ADC_ExternalTrigInjec_TMR15_CC3: Timer15 capture compare3 selected (for ADC1, ADC2 and ADC3)
  *     @arg ADC_ExternalTrigInjec_TMR15_CC4: Timer15 capture compare4 selected (for ADC1, ADC2 and ADC3)
  *     @arg ADC_ExternalTrigInjec_TMR15_TRGO: Timer15 TRGO event selected (for ADC1, ADC2 and ADC3)
  *     @arg ADC_ExternalTrigInjec_TMR1_CC1: Timer1 capture compare1 selected (for ADC1, ADC2 and ADC3)
  *     @arg ADC_ExternalTrigInjec_TMR8_TRGO: Timer8 TRGO event selected (for ADC1, ADC2 and ADC3)
  *     @arg ADC_ExternalTrigInjec_None: Injected conversion started by software and not by external trigger (for ADC1, ADC2 and ADC3)
  
  *     @arg ADC_ExternalTrigInjec_TMR4_CC3_ADC3: Timer4 capture compare3 selected (for ADC3 only)
  *     @arg ADC_ExternalTrigInjec_TMR8_CC2_ADC3: Timer8 capture compare2 selected (for ADC3 only)
  *     @arg ADC_ExternalTrigInjec_TMR8_CC4_ADC3: Timer8 capture compare4 selected (for ADC3 only)
  *     @arg ADC_ExternalTrigInjec_TMR5_TRGO_ADC3: Timer5 TRGO event selected (for ADC3 only)
  *     @arg ADC_ExternalTrigInjec_TMR5_CC4_ADC3: Timer5 capture compare4 selected (for ADC3 only)
  *     @arg ADC_ExternalTrigInjec_TMR1_CC2_ADC3: Timer1 capture compare2 selected (for ADC3 only)  
  * @retval None
  */
void ADC_ExternalTrigInjectedConvConfig(ADC_Type* ADCx, uint32_t ADC_ExternalTrigInjecConv)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_EXT_INJEC_TRIG(ADC_ExternalTrigInjecConv));
  /* Get the old register value */
  tmpreg = ADCx->CTRL2;
  /* Clear the old external event selection for injected group */
  tmpreg &= CTRL2_JEXTSEL_Rst;
  /* Set the external event selection for injected group */
  tmpreg |= ADC_ExternalTrigInjecConv;
  /* Store the new register value */
  ADCx->CTRL2 = tmpreg;
}

/**
  * @brief  Enables or disables the ADCx injected channels conversion through
  *         external trigger
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  NewState: new state of the selected ADC external trigger start of
  *         injected conversion.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ExternalTrigInjectedConvCtrl(ADC_Type* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC external event selection for injected group */
    ADCx->CTRL2 |= CTRL2_JEXTTRIG_Set;
  }
  else
  {
    /* Disable the selected ADC external event selection for injected group */
    ADCx->CTRL2 &= CTRL2_JEXTTRIG_Rst;
  }
}

/**
  * @brief  Enables or disables the selected ADC start of the injected
  *         channels conversion.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  NewState: new state of the selected ADC software start injected conversion.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_SoftwareStartInjectedConvCtrl(ADC_Type* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC conversion for injected group on external event and start the selected
       ADC injected conversion */
    ADCx->CTRL2 |= CTRL2_JEXTTRIG_JSWSTR_Set;
  }
  else
  {
    /* Disable the selected ADC conversion on external event for injected group and stop the selected
       ADC injected conversion */
    ADCx->CTRL2 &= CTRL2_JEXTTRIG_JSWSTR_Rst;
  }
}

/**
  * @brief  Gets the selected ADC Software start injected conversion Status.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @retval The new state of ADC software start injected conversion (SET or RESET).
  */
FlagStatus ADC_GetSoftwareStartInjectedConvCtrlStatus(ADC_Type* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Check the status of JSWSTART bit */
  if ((ADCx->CTRL2 & CTRL2_JSWSTR_Set) != (uint32_t)RESET)
  {
    /* JSWSTART bit is set */
    bitstatus = SET;
  }
  else
  {
    /* JSWSTART bit is reset */
    bitstatus = RESET;
  }

  /* Return the JSWSTART bit status */
  return  bitstatus;
}

/**
  * @brief  Configures for the selected ADC injected channel its corresponding
  *         rank in the sequencer and its sample time.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure.
  *   This parameter can be one of the following values:
  *     @arg ADC_Channel_0: ADC Channel0 selected
  *     @arg ADC_Channel_1: ADC Channel1 selected
  *     @arg ADC_Channel_2: ADC Channel2 selected
  *     @arg ADC_Channel_3: ADC Channel3 selected
  *     @arg ADC_Channel_4: ADC Channel4 selected
  *     @arg ADC_Channel_5: ADC Channel5 selected
  *     @arg ADC_Channel_6: ADC Channel6 selected
  *     @arg ADC_Channel_7: ADC Channel7 selected
  *     @arg ADC_Channel_8: ADC Channel8 selected
  *     @arg ADC_Channel_9: ADC Channel9 selected
  *     @arg ADC_Channel_10: ADC Channel10 selected
  *     @arg ADC_Channel_11: ADC Channel11 selected
  *     @arg ADC_Channel_12: ADC Channel12 selected
  *     @arg ADC_Channel_13: ADC Channel13 selected
  *     @arg ADC_Channel_14: ADC Channel14 selected
  *     @arg ADC_Channel_15: ADC Channel15 selected
  *     @arg ADC_Channel_16: ADC Channel16 selected
  *     @arg ADC_Channel_17: ADC Channel17 selected
  * @param  Rank: The rank in the injected group sequencer. This parameter must be between 1 and 4.
  * @param  ADC_SampleTime: The sample time value to be set for the selected channel.
  *   This parameter can be one of the following values:
  *     @arg ADC_SampleTime_1_5: Sample time equal to 1.5 cycles
  *     @arg ADC_SampleTime_7_5: Sample time equal to 7.5 cycles
  *     @arg ADC_SampleTime_13_5: Sample time equal to 13.5 cycles
  *     @arg ADC_SampleTime_28_5: Sample time equal to 28.5 cycles
  *     @arg ADC_SampleTime_41_5: Sample time equal to 41.5 cycles
  *     @arg ADC_SampleTime_55_5: Sample time equal to 55.5 cycles
  *     @arg ADC_SampleTime_71_5: Sample time equal to 71.5 cycles
  *     @arg ADC_SampleTime_239_5: Sample time equal to 239.5 cycles
  * @retval None
  */
void ADC_InjectedChannelConfig(ADC_Type* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0, tmpreg3 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_INJECTED_RANK(Rank));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));

  /* if ADC_Channel_10 ... ADC_Channel_17 is selected */
  if (ADC_Channel > ADC_Channel_9)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPT1;
    /* Calculate the mask to clear */
    tmpreg2 = SMPT1_SMP_Set << (3 * (ADC_Channel - 10));
    /* Clear the old channel sample time */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
    /* Set the new channel sample time */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SMPT1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPT2;
    /* Calculate the mask to clear */
    tmpreg2 = SMPT2_SMP_Set << (3 * ADC_Channel);
    /* Clear the old channel sample time */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
    /* Set the new channel sample time */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SMPT2 = tmpreg1;
  }

  /* Rank configuration */
  /* Get the old register value */
  tmpreg1 = ADCx->JSQ;
  /* Get JL value: Number = JL+1 */
  tmpreg3 =  (tmpreg1 & JSQR_JLEN_Set) >> 20;
  /* Calculate the mask to clear: ((Rank-1)+(4-JL-1)) */
  tmpreg2 = JSQR_JSQ_Set << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
  /* Clear the old JSQx bits for the selected rank */
  tmpreg1 &= ~tmpreg2;
  /* Calculate the mask to set: ((Rank-1)+(4-JL-1)) */
  tmpreg2 = (uint32_t)ADC_Channel << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
  /* Set the JSQx bits for the selected rank */
  tmpreg1 |= tmpreg2;
  /* Store the new register value */
  ADCx->JSQ = tmpreg1;
}

/**
  * @brief  Configures the sequencer length for injected channels
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  Length: The sequencer length.
  *   This parameter must be a number between 1 to 4.
  * @retval None
  */
void ADC_InjectedSequencerLengthConfig(ADC_Type* ADCx, uint8_t Length)
{
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_LENGTH(Length));

  /* Get the old register value */
  tmpreg1 = ADCx->JSQ;
  /* Clear the old injected sequnence lenght JL bits */
  tmpreg1 &= JSQR_JLEN_Rst;
  /* Set the injected sequnence lenght JL bits */
  tmpreg2 = Length - 1;
  tmpreg1 |= tmpreg2 << 20;
  /* Store the new register value */
  ADCx->JSQ = tmpreg1;
}

/**
  * @brief  Set the injected channels conversion value offset
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_InjectedChannel: the ADC injected channel to set its offset.
  *   This parameter can be one of the following values:
  *     @arg ADC_InjectedChannel_1: Injected Channel1 selected
  *     @arg ADC_InjectedChannel_2: Injected Channel2 selected
  *     @arg ADC_InjectedChannel_3: Injected Channel3 selected
  *     @arg ADC_InjectedChannel_4: Injected Channel4 selected
  * @param  Offset: the offset value for the selected ADC injected channel
  *   This parameter must be a 12bit value.
  * @retval None
  */
void ADC_SetInjectedOffset(ADC_Type* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));
  assert_param(IS_ADC_OFFSET(Offset));

  tmp = (uint32_t)ADCx;
  tmp += ADC_InjectedChannel;

  /* Set the selected injected channel data offset */
  *(__IO uint32_t *) tmp = (uint32_t)Offset;
}

/**
  * @brief  Returns the ADC injected channel conversion result
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_InjectedChannel: the converted ADC injected channel.
  *   This parameter can be one of the following values:
  *     @arg ADC_InjectedChannel_1: Injected Channel1 selected
  *     @arg ADC_InjectedChannel_2: Injected Channel2 selected
  *     @arg ADC_InjectedChannel_3: Injected Channel3 selected
  *     @arg ADC_InjectedChannel_4: Injected Channel4 selected
  * @retval The Data conversion value.
  */
uint16_t ADC_GetInjectedConversionValue(ADC_Type* ADCx, uint8_t ADC_InjectedChannel)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));

  tmp = (uint32_t)ADCx;
  tmp += ADC_InjectedChannel + JDOR_Offset;

  /* Returns the selected injected channel conversion data value */
  return (uint16_t) (*(__IO uint32_t*)  tmp);
}

/**
  * @brief  Enables or disables the analog watchdog on single/all regular
  *         or injected channels
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_AnalogWatchdog: the ADC analog watchdog configuration.
  *   This parameter can be one of the following values:
  *     @arg ADC_AnalogWDG_SingleRegEnable: Analog watchdog on a single regular channel
  *     @arg ADC_AnalogWDG_SingleInjecEnable: Analog watchdog on a single injected channel
  *     @arg ADC_AnalogWDG_SingleRegOrInjecEnable: Analog watchdog on a single regular or injected channel
  *     @arg ADC_AnalogWDG_AllRegEnable: Analog watchdog on  all regular channel
  *     @arg ADC_AnalogWDG_AllInjecEnable: Analog watchdog on  all injected channel
  *     @arg ADC_AnalogWDG_AllRegAllInjecEnable: Analog watchdog on all regular and injected channels
  *     @arg ADC_AnalogWDG_None: No channel guarded by the analog watchdog
  * @retval None
  */
void ADC_AnalogWDGCtrl(ADC_Type* ADCx, uint32_t ADC_AnalogWatchdog)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_ANALOG_WDG(ADC_AnalogWatchdog));
  /* Get the old register value */
  tmpreg = ADCx->CTRL1;
  /* Clear AWDEN, AWDENJ and AWDSGL bits */
  tmpreg &= CTRL1_AWDMode_Rst;
  /* Set the analog watchdog enable mode */
  tmpreg |= ADC_AnalogWatchdog;
  /* Store the new register value */
  ADCx->CTRL1 = tmpreg;
}

/**
  * @brief  Configures the high and low thresholds of the analog watchdog.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  HighThreshold: the ADC analog watchdog High threshold value.
  *   This parameter must be a 12bit value.
  * @param  LowThreshold: the ADC analog watchdog Low threshold value.
  *   This parameter must be a 12bit value.
  * @retval None
  */
void ADC_AnalogWDGThresholdsConfig(ADC_Type* ADCx, uint16_t HighThreshold,
                                   uint16_t LowThreshold)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_THRESHOLD(HighThreshold));
  assert_param(IS_ADC_THRESHOLD(LowThreshold));
  /* Set the ADCx high threshold */
  ADCx->WHTR = HighThreshold;
  /* Set the ADCx low threshold */
  ADCx->WLTR = LowThreshold;
}

/**
  * @brief  Configures the analog watchdog guarded single channel
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure for the analog watchdog.
  *   This parameter can be one of the following values:
  *     @arg ADC_Channel_0: ADC Channel0 selected
  *     @arg ADC_Channel_1: ADC Channel1 selected
  *     @arg ADC_Channel_2: ADC Channel2 selected
  *     @arg ADC_Channel_3: ADC Channel3 selected
  *     @arg ADC_Channel_4: ADC Channel4 selected
  *     @arg ADC_Channel_5: ADC Channel5 selected
  *     @arg ADC_Channel_6: ADC Channel6 selected
  *     @arg ADC_Channel_7: ADC Channel7 selected
  *     @arg ADC_Channel_8: ADC Channel8 selected
  *     @arg ADC_Channel_9: ADC Channel9 selected
  *     @arg ADC_Channel_10: ADC Channel10 selected
  *     @arg ADC_Channel_11: ADC Channel11 selected
  *     @arg ADC_Channel_12: ADC Channel12 selected
  *     @arg ADC_Channel_13: ADC Channel13 selected
  *     @arg ADC_Channel_14: ADC Channel14 selected
  *     @arg ADC_Channel_15: ADC Channel15 selected
  *     @arg ADC_Channel_16: ADC Channel16 selected
  *     @arg ADC_Channel_17: ADC Channel17 selected
  * @retval None
  */
void ADC_AnalogWDGSingleChannelConfig(ADC_Type* ADCx, uint8_t ADC_Channel)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  /* Get the old register value */
  tmpreg = ADCx->CTRL1;
  /* Clear the Analog watchdog channel select bits */
  tmpreg &= CTRL1_AWDCH_Rst;
  /* Set the Analog watchdog channel */
  tmpreg |= ADC_Channel;
  /* Store the new register value */
  ADCx->CTRL1 = tmpreg;
}

/**
  * @brief  Enables or disables the temperature sensor and Vrefint channel.
  * @param  NewState: new state of the temperature sensor.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_TempSensorVrefintCtrl(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the temperature sensor and Vrefint channel*/
    ADC1->CTRL2 |= CTRL2_TSVREFE_Set;
  }
  else
  {
    /* Disable the temperature sensor and Vrefint channel*/
    ADC1->CTRL2 &= CTRL2_TSVREFE_Rst;
  }
}

/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg ADC_FLAG_AWD: Analog watchdog flag
  *     @arg ADC_FLAG_EC: End of conversion flag
  *     @arg ADC_FLAG_JEC: End of injected group conversion flag
  *     @arg ADC_FLAG_JSTR: Start of injected group conversion flag
  *     @arg ADC_FLAG_RSTR: Start of regular group conversion flag
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetFlagStatus(ADC_Type* ADCx, uint8_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_FLAG(ADC_FLAG));

  /* Check the status of the specified ADC flag */
  if ((ADCx->STS & ADC_FLAG) != (uint8_t)RESET)
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
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg ADC_FLAG_AWD: Analog watchdog flag
  *     @arg ADC_FLAG_EC: End of conversion flag
  *     @arg ADC_FLAG_JEC: End of injected group conversion flag
  *     @arg ADC_FLAG_JSTR: Start of injected group conversion flag
  *     @arg ADC_FLAG_RSTR: Start of regular group conversion flag
  * @retval None
  */
void ADC_ClearFlag(ADC_Type* ADCx, uint8_t ADC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));
  /* Clear the selected ADC flags */
  ADCx->STS = ~(uint32_t)ADC_FLAG;
}

/**
  * @brief  Checks whether the specified ADC interrupt has occurred or not.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_INT: specifies the ADC interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg ADC_INT_EC: End of conversion interrupt mask
  *     @arg ADC_INT_AWD: Analog watchdog interrupt mask
  *     @arg ADC_INT_JEC: End of injected conversion interrupt mask
  * @retval The new state of ADC_INT (SET or RESET).
  */
ITStatus ADC_GetINTStatus(ADC_Type* ADCx, uint16_t ADC_INT)
{
  ITStatus bitstatus = RESET;
  uint32_t itmask = 0, enablestatus = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_INT(ADC_INT));
  /* Get the ADC INT index */
  itmask = ADC_INT >> 8;
  /* Get the ADC_INT enable bit status */
  enablestatus = (ADCx->CTRL1 & (uint8_t)ADC_INT) ;

  /* Check the status of the specified ADC interrupt */
  if (((ADCx->STS & itmask) != (uint32_t)RESET) && enablestatus)
  {
    /* ADC_INT is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_INT is reset */
    bitstatus = RESET;
  }

  /* Return the ADC_INT status */
  return  bitstatus;
}

/**
  * @brief  Clears the ADCx's interrupt pending bits.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_INT: specifies the ADC interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg ADC_INT_EC: End of conversion interrupt mask
  *     @arg ADC_INT_AWD: Analog watchdog interrupt mask
  *     @arg ADC_INT_JEC: End of injected conversion interrupt mask
  * @retval None
  */
void ADC_ClearINTPendingBit(ADC_Type* ADCx, uint16_t ADC_INT)
{
  uint8_t itmask = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INT(ADC_INT));
  /* Get the ADC INT index */
  itmask = (uint8_t)(ADC_INT >> 8);
  /* Clear the selected ADC interrupt pending bits */
  ADCx->STS = ~(uint32_t)itmask;
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


