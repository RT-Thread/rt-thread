/*********************************************************************************************************//**
 * @file    ht32f5xxxx_adc.c
 * @version $Rev:: 7366         $
 * @date    $Date:: 2023-12-06 #$
 * @brief   This file provides all the ADC firmware functions.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f5xxxx_adc.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup ADC ADC
  * @brief ADC driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup ADC_Private_Define ADC private definitions
  * @{
  */
#define ADC_ENABLE_BIT       (0x00000080)
#define ADC_SOFTWARE_RESET   (0x00000040)
#define LST_SEQ_SET          (0x0000001F)
#define TCR_SC_SET           (0x00000001)

#define HLST_SEQ_SET         (0x0000001F)
#define HTCR_SC_SET          (0x00000001)

#define ADC_VREF_MVDDAEN     (0x00000100)
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @addtogroup ADC_Exported_Functions ADC exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the HT_ADCn peripheral registers to their default reset values.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @retval None
 ************************************************************************************************************/
void ADC_DeInit(HT_ADC_TypeDef* HT_ADCn)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));

  if (HT_ADCn == NULL) // Remove the compiler warning
  {
  }

  RSTCUReset.Bit.ADC0 = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Reset ADC.
 * @param HT_ADCn: is the selected ADC from the ADC peripherals.
 * @retval None
 ************************************************************************************************************/
void ADC_Reset(HT_ADC_TypeDef* HT_ADCn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));

  HT_ADCn->CR |= ADC_SOFTWARE_RESET;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified ADC.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_Cmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_ADCn->CR |= ADC_ENABLE_BIT;
  }
  else
  {
    HT_ADCn->CR &= ~(ADC_ENABLE_BIT);
  }
}

/*********************************************************************************************************//**
 * @brief Configure conversion mode and length of list queue for regular group.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_MODE: ADC Cyclic Conversion Mode.
 *   This parameter can be one of the following values:
 *     @arg ONE_SHOT_MODE      :
 *     @arg CONTINUOUS_MODE    :
 *     @arg DISCONTINUOUS_MODE :
 * @param Length: must between 1 ~ 8
 * @param SubLength: must between 1 ~ 8, only valid for DISCONTINUOUS_MODE.
 * @retval None
 ************************************************************************************************************/
void ADC_RegularGroupConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_MODE, u8 Length, u8 SubLength)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_CONVERSION_MODE(ADC_MODE));
  Assert_Param(IS_ADC_REGULAR_LENGTH(Length));
  #if (LIBCFG_ADC_NO_DISCON_MODE == 0)
  if (ADC_MODE == DISCONTINUOUS_MODE)
  {
    Assert_Param(IS_ADC_REGULAR_SUB_LENGTH(SubLength));
  }
  #endif

  #if (LIBCFG_ADC_NO_DISCON_MODE)
  /* Config cyclic conversion mode and length of list queue for regular group                               */
  HT_ADCn->CR = ((u32)(Length - 1) << 8) | ADC_MODE | (HT_ADCn->CR & ADC_ENABLE_BIT);
  #else
  /* Config cyclic conversion mode and length of list queue and sub length for regular group                */
  HT_ADCn->CR = ((u32)(SubLength - 1) << 16) | ((u32)(Length - 1) << 8) | ADC_MODE | (HT_ADCn->CR & ADC_ENABLE_BIT);
  #endif
}

/*********************************************************************************************************//**
 * @brief Configure the corresponding rank in the sequencer for the regular channel
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_CH_n: the ADC channel to configure
 *   This parameter can be one of the following values:
 *     @arg ADC_CH_n        : ADC Channel n selected, n must between 0 ~ m (m represent the maximum external ADC input channel).
 *     @arg ADC_CH_DAC0_CH0 : ADC DAC0_CH0 selected
 *     @arg ADC_CH_DAC0_CH1 : ADC DAC0_CH1 selected
 *     @arg ADC_CH_DAC1_CH0 : ADC DAC1_CH0 selected
 *     @arg ADC_CH_DAC1_CH1 : ADC DAC1_CH1 selected
 *     @arg ADC_CH_IVREF    : ADC Internal VREF selected
 *     @arg ADC_CH_GND_VREF : ADC GND VREF selected
 *     @arg ADC_CH_VDD_VREF : ADC VDD VREF selected
 *     @arg ADC_CH_MVDDA    : ADC MVDDA selected
 * @param Rank: The rank in the regular group sequencer.
 *   This parameter must be between 0 to 7.
 * @param ...: Null parameter for API compatibility.
 * @retval None
 ************************************************************************************************************/
void ADC_RegularChannelConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n, u8 Rank, ...)
{
  u32 tmpreg1, tmpreg2;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_CHANNEL(ADC_CH_n));
  Assert_Param(IS_ADC_REGULAR_RANK(Rank));

  /* Get the old register value                                                                             */
  tmpreg1 = HT_ADCn->LST[Rank >> 2];
  /* Calculate the mask to clear                                                                            */
  tmpreg2 = LST_SEQ_SET << (8 * (Rank & 0x3));
  /* Clear the old SEQx bits for the selected rank                                                          */
  tmpreg1 &= ~tmpreg2;
  /* Calculate the mask to set                                                                              */
  tmpreg2 = (u32)ADC_CH_n << (8 * (Rank & 0x3));
  /* Set the SEQx bits for the selected rank                                                                */
  tmpreg1 |= tmpreg2;
  /* Store the new register value                                                                           */
  HT_ADCn->LST[Rank >> 2] = tmpreg1;
}

/*********************************************************************************************************//**
 * @brief Configure the ADC trigger source for regular channels conversion.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_TRIG_x:
 *   This parameter can be one of the following values:
 *     @arg ADC_TRIG_SOFTWARE   : S/W trigger
 *     @arg ADC_TRIG_EXTI_n     : where n can be 0 ~ 15
 *     @arg ADC_TRIG_MCTMn_MTO  : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CH0O : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CH1O : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CH2O : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CH3O : where n can be 0
 *     @arg ADC_TRIG_GPTMn_MTO  : where n can be 0 ~ 1
 *     @arg ADC_TRIG_GPTMn_CH0O : where n can be 0 ~ 1
 *     @arg ADC_TRIG_GPTMn_CH1O : where n can be 0 ~ 1
 *     @arg ADC_TRIG_GPTMn_CH2O : where n can be 0 ~ 1
 *     @arg ADC_TRIG_GPTMn_CH3O : where n can be 0 ~ 1
 *     @arg ADC_TRIG_BFTMn      : where n can be 0 ~ 1
 *     @arg ADC_TRIG_PWMn_MTO   : where n can be 0 ~ 1
 *     @arg ADC_TRIG_PWMn_CH0O  : where n can be 0 ~ 1
 *     @arg ADC_TRIG_PWMn_CH1O  : where n can be 0 ~ 1
 *     @arg ADC_TRIG_PWMn_CH2O  : where n can be 0 ~ 1
 *     @arg ADC_TRIG_PWMn_CH3O  : where n can be 0 ~ 1
 *     @arg ADC_TRIG_CMPn       : where n can be 0 ~ 1
 * @retval None
 ************************************************************************************************************/
void ADC_RegularTrigConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_TRIG_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_TRIG(ADC_TRIG_x));

  /* Config external trigger conversion source of regular group                                             */
  #if (LIBCFG_ADC_SW_TRIGGER_ONLY == 0)
  HT_ADCn->TCR = ADC_TRIG_x & 0x0000001F;
  #endif
  HT_ADCn->TSR = ADC_TRIG_x & (~0x0000001F);
}

/*********************************************************************************************************//**
 * @brief Configure the sampling time for the ADC input channel.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param SampleClock: must between 0 ~ 255.
 * @retval None
 ************************************************************************************************************/
void ADC_SamplingTimeConfig(HT_ADC_TypeDef* HT_ADCn, u8 SampleClock)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));

  /* config sampling clock of ADC input channel                                                             */
  HT_ADCn->STR = SampleClock;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable software start of the regular channel conversion of the selected ADC.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_SoftwareStartConvCmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Start Conversion                                                                                       */
  if (NewState != DISABLE)
  {
    HT_ADCn->TSR |= TCR_SC_SET;
  }
  else
  {
    HT_ADCn->TSR &= ~TCR_SC_SET;
  }
}

/*********************************************************************************************************//**
 * @brief Return the result of ADC regular channel conversion.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_REGULAR_DATAn: where n can be 0 ~ 7
 * @retval The Value of data conversion.
 ************************************************************************************************************/
u16 ADC_GetConversionData(HT_ADC_TypeDef* HT_ADCn, u8 ADC_REGULAR_DATAn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_REGULAR_DATA(ADC_REGULAR_DATAn));

  return ((u16)HT_ADCn->DR[ADC_REGULAR_DATAn]);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified ADC interrupts.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_INT_x: Specify the ADC interrupt sources that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_INT_SINGLE_EOC        :
 *     @arg ADC_INT_SUB_GROUP_EOC     :
 *     @arg ADC_INT_CYCLE_EOC         :
 *     @arg ADC_INT_DATA_OVERWRITE    :
 *     @arg ADC_INT_AWD_LOWER         :
 *     @arg ADC_INT_AWD_UPPER         :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_IntConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_INT_x, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_INT(ADC_INT_x));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_ADCn->IER |= ADC_INT_x;
  }
  else
  {
    HT_ADCn->IER &= ~ADC_INT_x;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified ADC interrupt has occurred.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_INT_x: Specify the interrupt status to check.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_INT_SINGLE_EOC        :
 *     @arg ADC_INT_SUB_GROUP_EOC     :
 *     @arg ADC_INT_CYCLE_EOC         :
 *     @arg ADC_INT_DATA_OVERWRITE    :
 *     @arg ADC_INT_AWD_LOWER         :
 *     @arg ADC_INT_AWD_UPPER         :
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus ADC_GetIntStatus(HT_ADC_TypeDef* HT_ADCn, u32 ADC_INT_x)
{
  FlagStatus Status;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_INT(ADC_INT_x));

  if ((HT_ADCn->ISR & ADC_INT_x) != RESET)
  {
    Status = SET;
  }
  else
  {
    Status = RESET;
  }

  return Status;
}

/*********************************************************************************************************//**
 * @brief Clear the ADC interrupt pending bits.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_INT_x: Specify the interrupt pending bits to be cleared.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_INT_SINGLE_EOC        :
 *     @arg ADC_INT_SUB_GROUP_EOC     :
 *     @arg ADC_INT_CYCLE_EOC         :
 *     @arg ADC_INT_DATA_OVERWRITE    :
 *     @arg ADC_INT_AWD_LOWER         :
 *     @arg ADC_INT_AWD_UPPER         :
 * @retval None
 ************************************************************************************************************/
void ADC_ClearIntPendingBit(HT_ADC_TypeDef* HT_ADCn, u32 ADC_INT_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_INT(ADC_INT_x));

  HT_ADCn->ICLR = ADC_INT_x;
}

/*********************************************************************************************************//**
 * @brief Check whether the specified ADC flag has been set.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_FLAG_x: Specify the flag to check.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_FLAG_SINGLE_EOC        :
 *     @arg ADC_FLAG_SUB_GROUP_EOC     :
 *     @arg ADC_FLAG_CYCLE_EOC         :
 *     @arg ADC_FLAG_DATA_OVERWRITE    :
 *     @arg ADC_FLAG_AWD_LOWER         :
 *     @arg ADC_FLAG_AWD_UPPER         :
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus ADC_GetFlagStatus(HT_ADC_TypeDef* HT_ADCn, u32 ADC_FLAG_x)
{
  FlagStatus Status;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_FLAG(ADC_FLAG_x));

  if ((HT_ADCn->IRAW & ADC_FLAG_x) != RESET)
  {
    Status = SET;
  }
  else
  {
    Status = RESET;
  }

  return Status;
}

#if (LIBCFG_ADC_NO_WDT == 0)
/*********************************************************************************************************//**
 * @brief Enable or Disable Lower/Upper threshold warning of the analog watchdog on single/all channels.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_AWD_x:
 *   This parameter can be any combination of the following values:
 *     @arg ADC_AWD_DISABLE            :
 *     @arg ADC_AWD_ALL_LOWER          :
 *     @arg ADC_AWD_ALL_UPPER          :
 *     @arg ADC_AWD_ALL_LOWER_UPPER    :
 *     @arg ADC_AWD_SINGLE_LOWER       :
 *     @arg ADC_AWD_SINGLE_UPPER       :
 *     @arg ADC_AWD_SINGLE_LOWER_UPPER :
 * @retval None
 ************************************************************************************************************/
void ADC_AWDConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_AWD_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_AWD(ADC_AWD_x));

  HT_ADCn->WCR = (HT_ADCn->WCR & 0xFFFFFFF8) | ADC_AWD_x;
}

/*********************************************************************************************************//**
 * @brief Configure the analog watchdog that guards single channel.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_CH_n: where n must between 0 ~ m (m represent the maximum external ADC input channel).
 * @retval None
 ************************************************************************************************************/
void ADC_AWDSingleChannelConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_INPUT_CHANNEL(ADC_CH_n));

  HT_ADCn->WCR = (HT_ADCn->WCR & 0xFFFFF0FF) | ((u32)ADC_CH_n << 8);
}

/*********************************************************************************************************//**
 * @brief Configure the high and low thresholds of the analog watchdog.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param UPPER: must between 0x0000 ~ 0x0FFF
 * @param LOWER: must between 0x0000 ~ 0x0FFF
 * @retval None
 ************************************************************************************************************/
void ADC_AWDThresholdsConfig(HT_ADC_TypeDef* HT_ADCn, u16 UPPER, u16 LOWER)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_THRESHOLD(UPPER));
  Assert_Param(IS_ADC_THRESHOLD(LOWER));

  HT_ADCn->WTR = (UPPER << 16) | LOWER;
}
#endif

#if (LIBCFG_PDMA)
/*********************************************************************************************************//**
 * @brief Enable or Disable the specified PDMA request.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_PDMA_x: Specify the ADC PDMA request that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_PDMA_REGULAR_SINGLE   :
 *     @arg ADC_PDMA_REGULAR_SUBGROUP :
 *     @arg ADC_PDMA_REGULAR_CYCLE    :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_PDMAConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_PDMA_x, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_PDMA(ADC_PDMA_x));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_ADCn->PDMAR |= ADC_PDMA_x;
  }
  else
  {
    HT_ADCn->PDMAR &= ~ADC_PDMA_x;
  }
}
#endif

#if (LIBCFG_ADC_IVREF)
/*********************************************************************************************************//**
 * @brief Enable or Disable the VREF.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_VREFCmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_ADCn->VREFCR |= 0x00000001;
  }
  else
  {
    HT_ADCn->VREFCR &= ~(0x00000001);
  }
}

/*********************************************************************************************************//**
 * @brief Configure the VREF output voltage.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_VREF_x:
 *   This parameter can be one of the following value:
 *     @arg ADC_VREF_1V215 :
 *     @arg ADC_VREF_2V0   :
 *     @arg ADC_VREF_2V5   :
 *     @arg ADC_VREF_2V7   :
 *   For the 5 V version (LIBCFG_ADC_IVREF_LEVEL_TYPE2):
 *     @arg ADC_VREF_2V5   :
 *     @arg ADC_VREF_3V0   :
 *     @arg ADC_VREF_4V0   :
 *     @arg ADC_VREF_4V5   :
 * @retval None
 ************************************************************************************************************/
void ADC_VREFConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_VREF_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_VREF_SEL(ADC_VREF_x));

  HT_ADCn->VREFCR = (HT_ADCn->VREFCR & ~(3ul << 4)) | (ADC_VREF_x);
}
#endif

#if (LIBCFG_ADC_VREFBUF)
/*********************************************************************************************************//**
 * @brief Enable or Disable the VREF output. When enable, the VREF provides a stable voltage output to the ADVREFP pin (ADC reference positive voltage).
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_VREFOutputCmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState)
{
  /* !!! NOTICE !!!
     The ADCREFP pin should not be connected to an external voltage when the VREF output is enabled.
  */

  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_ADCn->VREFCR |= 0x00000002;
  }
  else
  {
    HT_ADCn->VREFCR &= ~(0x00000002);
  }
}
#endif

#if (LIBCFG_ADC_MVDDA)
/*********************************************************************************************************//**
 * @brief Enable or Disable the power of MVDDA (VDDA/2)
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_MVDDACmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_ADCn->VREFCR |= ADC_VREF_MVDDAEN;
  }
  else
  {
    HT_ADCn->VREFCR &= ~(ADC_VREF_MVDDAEN);
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
