/*********************************************************************************************************//**
 * @file    ht32f65xxx_66xxx_adc.c
 * @version $Rev:: 7367         $
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
#include "ht32f65xxx_66xxx_adc.h"

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
#define DUAL_MODE_MASK       (0x00000003)
#define ADC_SOFTWARE_RESET   (0x00000001)
#define LST_SEQ_SET          (0x0000001F)
#define TCR_SC_SET           (0x00000001)

#define HLST_SEQ_SET         (0x0000001F)
#define HTCR_SC_SET          (0x00000001)

#define OFR_ADOF_MASK        (0x00000FFF)
#define OFR_ADAL             (1 << 14)
#define OFR_ADOFE            (1 << 15)
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

  if (HT_ADCn == HT_ADC0)
  {
    RSTCUReset.Bit.ADC0 = 1;
  }
  #if (LIBCFG_ADC1)
  else if (HT_ADCn == HT_ADC1)
  {
    RSTCUReset.Bit.ADC1 = 1;
  }
  #endif
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

  HT_ADCn->RST |= ADC_SOFTWARE_RESET;
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
    HT_ADCn->CONV |= ADC_ENABLE_BIT;
  }
  else
  {
    HT_ADCn->CONV &= ~(ADC_ENABLE_BIT);
  }
}

#if (LIBCFG_ADC1)
/*********************************************************************************************************//**
 * @brief Configure the ADC dual mode.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals. (ADC1 only)
 * @param DUAL_X: ADC dual mode configuration.
 *   This parameter can be one of the following values:
 *     @arg DUAL_INDEPENDENT                : Independent mode (dual mode off).
 *     @arg DUAL_CASCADE_REGULAR            : Cascade mode in regular conversion.
 *     @arg DUAL_CASCADE_REGULAR_H_PRIORITY : Cascade mode in regular/high priority conversion.
 * @param HDelayTime: High priority ADC trigger delay.
 *   This parameter must be between 0x00 to 0xFF.
 * @param DelayTime: Regular ADC trigger delay.
 *   This parameter must be between 0x00 to 0xFF.
 * @retval None
 ************************************************************************************************************/
void ADC_DualModeConfig(HT_ADC_TypeDef* HT_ADCn, u32 DUAL_X, u8 HDelayTime, u8 DelayTime)
{
  u32 uTmpReg1, uTmpReg2;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_DUAL_MODE(DUAL_X));

  uTmpReg1 = HT_ADCn->CFGR;
  uTmpReg2 = (DUAL_MODE_MASK | 0x00FFFF00);
  uTmpReg1 &= ~uTmpReg2;
  uTmpReg2 = (DUAL_X | HDelayTime << 16 | DelayTime << 8);
  uTmpReg1 |= uTmpReg2;

  HT_ADCn->CFGR = uTmpReg1;
}
#endif

/*********************************************************************************************************//**
 * @brief Configure conversion mode and length of list queue for regular group.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_MODE: ADC Cyclic Conversion Mode.
 *   This parameter can be one of the following values:
 *     @arg ONE_SHOT_MODE      :
 *     @arg CONTINUOUS_MODE    :
 *     @arg DISCONTINUOUS_MODE :
 * @param Length: must between 1 ~ 16
 * @param SubLength: must between 1 ~ 16, only valid for DISCONTINUOUS_MODE.
 * @retval None
 ************************************************************************************************************/
void ADC_RegularGroupConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_MODE, u8 Length, u8 SubLength)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_CONVERSION_MODE(ADC_MODE));
  Assert_Param(IS_ADC_REGULAR_LENGTH(Length));
  if (ADC_MODE == DISCONTINUOUS_MODE)
  {
    Assert_Param(IS_ADC_REGULAR_SUB_LENGTH(SubLength));
  }

  /* Config cyclic conversion mode and length of list queue and sub length for regular group                */
  HT_ADCn->CONV = ((u32)(SubLength - 1) << 16) | ((u32)(Length - 1) << 8) | ADC_MODE | (HT_ADCn->CONV & ADC_ENABLE_BIT);
}

/*********************************************************************************************************//**
 * @brief Configure conversion mode and length of list queue for high priority group.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_MODE: ADC Cyclic Conversion Mode.
 *   This parameter can be one of the following values:
 *     @arg ONE_SHOT_MODE      :
 *     @arg CONTINUOUS_MODE    :
 *     @arg DISCONTINUOUS_MODE :
 * @param Length: must between 1 ~ 4
 * @param SubLength: must between 1 ~ 4
 * @retval None
 ************************************************************************************************************/
void ADC_HPGroupConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_MODE, u8 Length, u8 SubLength)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_CONVERSION_MODE(ADC_MODE));
  Assert_Param(IS_ADC_HP_LENGTH(Length));
  Assert_Param(IS_ADC_HP_SUB_LENGTH(SubLength));

  /* Config cyclic conversion mode and length of list queue and sub length for regular group                */
  HT_ADCn->HCONV = ((u32)(SubLength - 1) << 16) | ((u32)(Length - 1) << 8) | ADC_MODE;
}

/*********************************************************************************************************//**
 * @brief Configure the corresponding rank in the sequencer and the sampling time for the regular channel
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_CH_n: the ADC channel to configure
 *   This parameter can be one of the following values:
 *     @arg ADC_CH_n        : ADC Channel x selected, x must between 0 ~ 7
 *     @arg ADC_CH_GND_VREF : ADC GND VREF selected
 *     @arg ADC_CH_VDD_VREF : ADC VDD VREF selected
 * @param Rank: The rank in the regular group sequencer.
 *   This parameter must be between 0 to 7.
 * @param SampleClock: Number of sampling clocks.
 *   This parameter must be between 0x00 to 0xFF.
 * @retval None
 ************************************************************************************************************/
void ADC_RegularChannelConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n, u8 Rank, u8 SampleClock)
{
  u32 tmpreg1, tmpreg2;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_CHANNEL(ADC_CH_n));
  Assert_Param(IS_ADC_REGULAR_RANK(Rank));
  Assert_Param(IS_ADC_INPUT_SAMPLING_TIME(SampleClock));

  /* config sampling clock of correspond ADC input channel                                                  */
  HT_ADCn->STR[ADC_CH_n] = SampleClock;

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
 * @brief Configure the corresponding rank in the sequencer and the sample time for the High Priority channel
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_CH_n: the ADC channel to configure
 *   This parameter can be one of the following values:
 *     @arg ADC_CH_n        : ADC Channel x selected, x must between 0 ~ 7
 *     @arg ADC_CH_GND_VREF : ADC GND VREF selected
 *     @arg ADC_CH_VDD_VREF : ADC VDD VREF selected
 * @param Rank: The rank in the high priority group sequencer.
 *   This parameter must be between 0 to 3.
 * @param SampleClock: Number of sampling clocks.
 *   This parameter must be between 0x00 to 0xFF.
 * @retval None
 ************************************************************************************************************/
void ADC_HPChannelConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n, u8 Rank, u8 SampleClock)
{
  u32 tmpreg1, tmpreg2;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_CHANNEL(ADC_CH_n));
  Assert_Param(IS_ADC_HP_RANK(Rank));
  Assert_Param(IS_ADC_INPUT_SAMPLING_TIME(SampleClock));

  /* config sampling clock of correspond ADC input channel                                                  */
  HT_ADCn->STR[ADC_CH_n] = SampleClock;

  /* Get the old register value                                                                             */
  tmpreg1 = HT_ADCn->HLST;
  /* Calculate the mask to clear                                                                            */
  tmpreg2 = HLST_SEQ_SET << (8 * (Rank & 0x3));
  /* Clear the old SEQx bits for the selected rank                                                          */
  tmpreg1 &= ~tmpreg2;
  /* Calculate the mask to set                                                                              */
  tmpreg2 = (u32)ADC_CH_n << (8 * (Rank & 0x3));
  /* Set the SEQx bits for the selected rank                                                                */
  tmpreg1 |= tmpreg2;
  /* Store the new register value                                                                           */
  HT_ADCn->HLST = tmpreg1;
}

/*********************************************************************************************************//**
 * @brief Configure the ADC trigger source for regular channels conversion.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_TRIG_x:
 *   This parameter can be one of the following values:
 *     @arg ADC_TRIG_SOFTWARE        : S/W trigger
 *     @arg ADC_TRIG_EXTI_n          : where n can be 0 ~ 15
 *     @arg ADC_TRIG_MCTMn_MEVx      : where n can be 0
 *     @arg ADC_TRIG_MCTM0_DMEVx     : where n can be 0*
 *     @arg ADC_TRIG_MCTM0_MEVxDEVz  : where n can be 0
 *     @arg ADC_TRIG_MCTMn_MTO       : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CH0O      : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CH1O      : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CH2O      : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CH3O      : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CHmMEV    : where n can be 0, m can be 0 ~ 3
 *     @arg ADC_TRIG_MCTMn_CHmDEV    : where n can be 0, m can be 0 ~ 3
 *     @arg ADC_TRIG_MCTMn_CHmMDEV   : where n can be 0, m can be 0 ~ 3
 *     @arg ADC_TRIG_MCTMn_CHALLMEV  : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CHALLDEV  : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CHALLMDEV : where n can be 0
 *     @arg ADC_TRIG_BFTMn           : where n can be 0 ~ 1
 *     @arg ADC_TRIG_GPTMn_MTO       : where n can be 0
 *     @arg ADC_TRIG_GPTMn_CH0O      : where n can be 0
 *     @arg ADC_TRIG_GPTMn_CH1O      : where n can be 0
 *     @arg ADC_TRIG_GPTMn_CH2O      : where n can be 0
 *     @arg ADC_TRIG_GPTMn_CH3O      : where n can be 0
 *     @arg ADC_TRIG_CMPn            : where n can be 0 ~ 3
 * @retval None
 ************************************************************************************************************/
void ADC_RegularTrigConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_TRIG_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_TRIG(ADC_TRIG_x));

  /* Config external trigger conversion source of regular group                                             */
  HT_ADCn->TCR = ADC_TRIG_x & 0x0000001F;
  HT_ADCn->TSR = ADC_TRIG_x & (~0x0000001F);
}

/*********************************************************************************************************//**
 * @brief Configure the ADC trigger source for high priority channels conversion.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_TRIG_x:
 *   This parameter can be one of the following values:
 *     @arg ADC_TRIG_SOFTWARE        : S/W trigger
 *     @arg ADC_TRIG_EXTI_n          : where n can be 0 ~ 15
 *     @arg ADC_TRIG_MCTMn_MEVx      : where n can be 0
 *     @arg ADC_TRIG_MCTM0_DMEVx     : where n can be 0*
 *     @arg ADC_TRIG_MCTM0_MEVxDEVz  : where n can be 0
 *     @arg ADC_TRIG_MCTMn_MTO       : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CH0O      : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CH1O      : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CH2O      : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CH3O      : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CHmMEV    : where n can be 0, m can be 0 ~ 3
 *     @arg ADC_TRIG_MCTMn_CHmDEV    : where n can be 0, m can be 0 ~ 3
 *     @arg ADC_TRIG_MCTMn_CHmMDEV   : where n can be 0, m can be 0 ~ 3
 *     @arg ADC_TRIG_MCTMn_CHALLMEV  : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CHALLDEV  : where n can be 0
 *     @arg ADC_TRIG_MCTMn_CHALLMDEV : where n can be 0
 *     @arg ADC_TRIG_BFTMn           : where n can be 0 ~ 1
 *     @arg ADC_TRIG_GPTMn_MTO       : where n can be 0
 *     @arg ADC_TRIG_GPTMn_CH0O      : where n can be 0
 *     @arg ADC_TRIG_GPTMn_CH1O      : where n can be 0
 *     @arg ADC_TRIG_GPTMn_CH2O      : where n can be 0
 *     @arg ADC_TRIG_GPTMn_CH3O      : where n can be 0
 *     @arg ADC_TRIG_CMPn            : where n can be 0 ~ 3
 * @retval None
 ************************************************************************************************************/
void ADC_HPTrigConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_TRIG_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_TRIG(ADC_TRIG_x));

  HT_ADCn->HTCR = ADC_TRIG_x & 0x0000001F;
  HT_ADCn->HTSR = ADC_TRIG_x & (~0x0000001F);
}

#if (!LIBCFG_ADC_NO_OFFSET_REG)
/*********************************************************************************************************//**
 * @brief Configure the channel data alignment format.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_CH_n: the ADC channel to configure
 *   This parameter can be one of the following values:
 *     @arg ADC_CH_n        : ADC Channel x selected
 *     @arg ADC_CH_OPAn     : ADC channel for OPAn
 *     @arg ADC_CH_GND_VREF : ADC GND VREF selected
 *     @arg ADC_CH_VDD_VREF : ADC VDD VREF selected
 * @param ADC_ALIGN_x: ADC_ALIGN_RIGHT or ADC_ALIGN_LEFT
 * @retval None
 ************************************************************************************************************/
void ADC_ChannelDataAlign(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n, ADC_ALIGN_Enum ADC_ALIGN_x)
{
  u32 OFRValue;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_CHANNEL(ADC_CH_n));
  Assert_Param(IS_ADC_ALIGN(ADC_ALIGN_x));

  OFRValue = HT_ADCn->OFR[ADC_CH_n] & (~(OFR_ADAL));
  OFRValue |= ADC_ALIGN_x;

  HT_ADCn->OFR[ADC_CH_n] = OFRValue;
}

/*********************************************************************************************************//**
 * @brief Configure the offset value for channel offset cancellation.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_CH_n: the ADC channel to configure
 *   This parameter can be one of the following values:
 *     @arg ADC_CH_n        : ADC Channel x selected
 *     @arg ADC_CH_OPAn     : ADC channel for OPAn
 *     @arg ADC_CH_GND_VREF : ADC GND VREF selected
 *     @arg ADC_CH_VDD_VREF : ADC VDD VREF selected
 * @param OffsetValue: The offset value
 * @retval None
 ************************************************************************************************************/
void ADC_ChannelOffsetValue(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n, u16 OffsetValue)
{
  u32 OFRValue;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_CHANNEL(ADC_CH_n));
  Assert_Param(IS_ADC_OFFSET(OffsetValue));

  OFRValue = HT_ADCn->OFR[ADC_CH_n] & (~OFR_ADOF_MASK);
  OFRValue |= (OffsetValue & 0xFFF);
  HT_ADCn->OFR[ADC_CH_n] = OFRValue;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the channel offset cancellation function.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_CH_n: the ADC channel to configure
 *   This parameter can be one of the following values:
 *     @arg ADC_CH_n        : ADC Channel x selected
 *     @arg ADC_CH_OPAn     : ADC channel for OPAn
 *     @arg ADC_CH_GND_VREF : ADC GND VREF selected
 *     @arg ADC_CH_VDD_VREF : ADC VDD VREF selected
 * @param NewState: ENABLE DISABLE
 * @retval None
 ************************************************************************************************************/
void ADC_ChannelOffsetCmd(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n, ControlStatus NewState)
{
  u32 OFRValue;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_CHANNEL(ADC_CH_n));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  OFRValue = HT_ADCn->OFR[ADC_CH_n] & (~(OFR_ADOFE));

  if (NewState == ENABLE)
  {
    OFRValue |= OFR_ADOFE;
  }

  HT_ADCn->OFR[ADC_CH_n] = OFRValue;
}
#endif

#if (LIBCFG_ADC_TRIG_DELAY)
/*********************************************************************************************************//**
 * @brief Configure the ADC Trigger Delay.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals. (ADC1 only)
  * @param HDelayTime: High priority ADC trigger delay.
 *   This parameter must be between 0x00 to 0xFF.
 * @param DelayTime: Regular ADC trigger delay.
 *   This parameter must be between 0x00 to 0xFF.
 * @retval None
 ************************************************************************************************************/
void ADC_TrigDelayConfig(HT_ADC_TypeDef* HT_ADCn, u8 HDelayTime, u8 DelayTime)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));

  HT_ADCn->CFGR = (HDelayTime << 16 | DelayTime << 8);
}
#endif

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
 * @brief Enable or Disable software start of the high priority channel conversion of the selected ADC.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_HPSoftwareStartConvCmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Start Conversion                                                                                       */
  if (NewState != DISABLE)
  {
    HT_ADCn->HTSR |= HTCR_SC_SET;
  }
  else
  {
    HT_ADCn->HTSR &= ~HTCR_SC_SET;
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
 * @brief Return the result of ADC high priority channel conversion.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_HP_DATAn: where x can be 0 ~ 3
 * @retval The Value of data conversion.
 ************************************************************************************************************/
u16 ADC_GetHPConversionData(HT_ADC_TypeDef* HT_ADCn, u8 ADC_HP_DATAn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ADC(HT_ADCn));
  Assert_Param(IS_ADC_HP_DATA(ADC_HP_DATAn));

  return ((u16)HT_ADCn->HDR[ADC_HP_DATAn]);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified ADC interrupts.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_INT_x: Specify the ADC interrupt sources that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_INT_SINGLE_EOC        :
 *     @arg ADC_INT_SUB_GROUP_EOC     :
 *     @arg ADC_INT_CYCLE_EOC         :
 *     @arg ADC_INT_HP_SINGLE_EOC     :
 *     @arg ADC_INT_HP_SUB_GROUP_EOC  :
 *     @arg ADC_INT_HP_CYCLE_EOC      :
 *     @arg ADC_INT_DATA_OVERWRITE    :
 *     @arg ADC_INT_HP_DATA_OVERWRITE :
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
 *     @arg ADC_INT_HP_SINGLE_EOC     :
 *     @arg ADC_INT_HP_SUB_GROUP_EOC  :
 *     @arg ADC_INT_HP_CYCLE_EOC      :
 *     @arg ADC_INT_DATA_OVERWRITE    :
 *     @arg ADC_INT_HP_DATA_OVERWRITE :
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
 *     @arg ADC_INT_HP_SINGLE_EOC     :
 *     @arg ADC_INT_HP_SUB_GROUP_EOC  :
 *     @arg ADC_INT_HP_CYCLE_EOC      :
 *     @arg ADC_INT_DATA_OVERWRITE    :
 *     @arg ADC_INT_HP_DATA_OVERWRITE :
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
 *     @arg ADC_FLAG_HP_SINGLE_EOC     :
 *     @arg ADC_FLAG_HP_SUB_GROUP_EOC  :
 *     @arg ADC_FLAG_HP_CYCLE_EOC      :
 *     @arg ADC_FLAG_DATA_OVERWRITE    :
 *     @arg ADC_FLAG_HP_DATA_OVERWRITE :
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
 * @param ADC_CH_n: where n must between 0 ~ 7
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

  HT_ADCn->LTR = LOWER;
  HT_ADCn->UTR = UPPER;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified PDMA request.
 * @param HT_ADCn: where HT_ADCn is the selected ADC from the ADC peripherals.
 * @param ADC_PDMA_x: Specify the ADC PDMA request that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_PDMA_REGULAR_SINGLE   :
 *     @arg ADC_PDMA_REGULAR_SUBGROUP :
 *     @arg ADC_PDMA_REGULAR_CYCLE    :
 *     @arg ADC_PDMA_HP_SINGLE        :
 *     @arg ADC_PDMA_HP_SUBGROUP      :
 *     @arg ADC_PDMA_HP_CYCLE         :
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
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */
