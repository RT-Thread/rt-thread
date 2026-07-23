/********************************** (C) COPYRIGHT  *******************************
* File Name          : ch32f20x_adc.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : This file provides all the ADC firmware functions. 
*******************************************************************************/ 
#include "ch32f20x_adc.h"
#include "ch32f20x_rcc.h"

/* ADC DISCNUM mask */
#define CTLR1_DISCNUM_Reset           ((uint32_t)0xFFFF1FFF)

/* ADC DISCEN mask */
#define CTLR1_DISCEN_Set              ((uint32_t)0x00000800)
#define CTLR1_DISCEN_Reset            ((uint32_t)0xFFFFF7FF)

/* ADC JAUTO mask */
#define CTLR1_JAUTO_Set               ((uint32_t)0x00000400)
#define CTLR1_JAUTO_Reset             ((uint32_t)0xFFFFFBFF)

/* ADC JDISCEN mask */
#define CTLR1_JDISCEN_Set             ((uint32_t)0x00001000)
#define CTLR1_JDISCEN_Reset           ((uint32_t)0xFFFFEFFF)

/* ADC AWDCH mask */
#define CTLR1_AWDCH_Reset             ((uint32_t)0xFFFFFFE0)

/* ADC Analog watchdog enable mode mask */
#define CTLR1_AWDMode_Reset           ((uint32_t)0xFF3FFDFF)

/* CTLR1 register Mask */
#define CTLR1_CLEAR_Mask              ((uint32_t)0xE0F0FEFF)

/* ADC ADON mask */
#define CTLR2_ADON_Set                ((uint32_t)0x00000001)
#define CTLR2_ADON_Reset              ((uint32_t)0xFFFFFFFE)

/* ADC DMA mask */
#define CTLR2_DMA_Set                 ((uint32_t)0x00000100)
#define CTLR2_DMA_Reset               ((uint32_t)0xFFFFFEFF)

/* ADC RSTCAL mask */
#define CTLR2_RSTCAL_Set              ((uint32_t)0x00000008)

/* ADC CAL mask */
#define CTLR2_CAL_Set                 ((uint32_t)0x00000004)

/* ADC SWSTART mask */
#define CTLR2_SWSTART_Set             ((uint32_t)0x00400000)

/* ADC EXTTRIG mask */
#define CTLR2_EXTTRIG_Set             ((uint32_t)0x00100000)
#define CTLR2_EXTTRIG_Reset           ((uint32_t)0xFFEFFFFF)

/* ADC Software start mask */
#define CTLR2_EXTTRIG_SWSTART_Set     ((uint32_t)0x00500000)
#define CTLR2_EXTTRIG_SWSTART_Reset   ((uint32_t)0xFFAFFFFF)

/* ADC JEXTSEL mask */
#define CTLR2_JEXTSEL_Reset           ((uint32_t)0xFFFF8FFF)

/* ADC JEXTTRIG mask */
#define CTLR2_JEXTTRIG_Set            ((uint32_t)0x00008000)
#define CTLR2_JEXTTRIG_Reset          ((uint32_t)0xFFFF7FFF)

/* ADC JSWSTART mask */
#define CTLR2_JSWSTART_Set            ((uint32_t)0x00200000)

/* ADC injected software start mask */
#define CTLR2_JEXTTRIG_JSWSTART_Set   ((uint32_t)0x00208000)
#define CTLR2_JEXTTRIG_JSWSTART_Reset ((uint32_t)0xFFDF7FFF)

/* ADC TSPD mask */
#define CTLR2_TSVREFE_Set             ((uint32_t)0x00800000)
#define CTLR2_TSVREFE_Reset           ((uint32_t)0xFF7FFFFF)

/* CTLR2 register Mask */
#define CTLR2_CLEAR_Mask              ((uint32_t)0xFFF1F7FD)

/* ADC SQx mask */
#define RSQR3_SQ_Set                  ((uint32_t)0x0000001F)
#define RSQR2_SQ_Set                  ((uint32_t)0x0000001F)
#define RSQR1_SQ_Set                  ((uint32_t)0x0000001F)

/* RSQR1 register Mask */
#define RSQR1_CLEAR_Mask              ((uint32_t)0xFF0FFFFF)

/* ADC JSQx mask */
#define ISQR_JSQ_Set                  ((uint32_t)0x0000001F)

/* ADC JL mask */
#define ISQR_JL_Set                   ((uint32_t)0x00300000)
#define ISQR_JL_Reset                 ((uint32_t)0xFFCFFFFF)

/* ADC SMPx mask */
#define SAMPTR1_SMP_Set               ((uint32_t)0x00000007)
#define SAMPTR2_SMP_Set               ((uint32_t)0x00000007)

/* ADC IDATARx registers offset */
#define IDATAR_Offset                 ((uint8_t)0x28)

/* ADC1 RDATAR register base address */
#define RDATAR_ADDRESS                ((uint32_t)0x4001244C)

/*******************************************************************************
* Function Name  : ADC_DeInit
* Description    : Deinitializes the ADCx peripheral registers to their default 
*      reset values.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
* Return         : None
*******************************************************************************/
void ADC_DeInit(ADC_TypeDef* ADCx)
{
  if (ADCx == ADC1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);
  }
  else if(ADCx == ADC2)
  {
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, DISABLE);
  }
}

/*******************************************************************************
* Function Name  : ADC_Init
* Description    : Initializes the ADCx peripheral according to the specified 
*      parameters in the ADC_InitStruct.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that 
*      contains the configuration information for the specified ADC peripheral.
* Return         : None
*******************************************************************************/
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
  uint32_t tmpreg1 = 0;
  uint8_t tmpreg2 = 0;

  tmpreg1 = ADCx->CTLR1;
  tmpreg1 &= CTLR1_CLEAR_Mask;
  tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_Mode | (uint32_t) ADC_InitStruct->ADC_OutputBuffer |
          (uint32_t) ADC_InitStruct->ADC_Pga | ((uint32_t)ADC_InitStruct->ADC_ScanConvMode << 8));
  ADCx->CTLR1 = tmpreg1;

  tmpreg1 = ADCx->CTLR2;
  tmpreg1 &= CTLR2_CLEAR_Mask;
  tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ExternalTrigConv |
            ((uint32_t)ADC_InitStruct->ADC_ContinuousConvMode << 1));
  ADCx->CTLR2 = tmpreg1;

  tmpreg1 = ADCx->RSQR1;
  tmpreg1 &= RSQR1_CLEAR_Mask;
  tmpreg2 |= (uint8_t) (ADC_InitStruct->ADC_NbrOfChannel - (uint8_t)1);
  tmpreg1 |= (uint32_t)tmpreg2 << 20;
  ADCx->RSQR1 = tmpreg1;
}

/*******************************************************************************
* Function Name  : ADC_StructInit
* Description    : Fills each ADC_InitStruct member with its default value.
* Input          : ADC_InitStruct : pointer to an ADC_InitTypeDef structure that
*      contains the configuration information for the specified ADC peripheral.
* Return         : None
*******************************************************************************/
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
  ADC_InitStruct->ADC_Mode = ADC_Mode_Independent;
  ADC_InitStruct->ADC_ScanConvMode = DISABLE;
  ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;
  ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStruct->ADC_NbrOfChannel = 1;
}

/*******************************************************************************
* Function Name  : ADC_Cmd
* Description    : Enables or disables the specified ADC peripheral.
* Input          : ADCx: 
*                    where x can be 1 to select the ADC peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ADCx->CTLR2 |= CTLR2_ADON_Set;
  }
  else
  {
    ADCx->CTLR2 &= CTLR2_ADON_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_DMACmd
* Description    : Enables or disables the specified ADC DMA request.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ADCx->CTLR2 |= CTLR2_DMA_Set;
  }
  else
  {
    ADCx->CTLR2 &= CTLR2_DMA_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_ITConfig
* Description    : Enables or disables the specified ADC interrupts.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_IT: specifies the ADC interrupt sources to be enabled or disabled. 
*                    ADC_IT_EOC: End of conversion interrupt mask.
*                    ADC_IT_AWD: Analog watchdog interrupt mask.
*                    ADC_IT_JEOC: End of injected conversion interrupt mask.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState)
{
  uint8_t itmask = 0;

  itmask = (uint8_t)ADC_IT;
	
  if (NewState != DISABLE)
  {
    ADCx->CTLR1 |= itmask;
  }
  else
  {
    ADCx->CTLR1 &= (~(uint32_t)itmask);
  }
}

/*******************************************************************************
* Function Name  : ADC_ResetCalibration
* Description    : Resets the selected ADC calibration registers.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
* Return         : None
*******************************************************************************/
void ADC_ResetCalibration(ADC_TypeDef* ADCx)
{
  ADCx->CTLR2 |= CTLR2_RSTCAL_Set;
}

/*******************************************************************************
* Function Name  : ADC_GetResetCalibrationStatus
* Description    : Gets the selected ADC reset calibration registers status.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
* Return         : FlagStatus: SET or RESET.
*******************************************************************************/
FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;

  if ((ADCx->CTLR2 & CTLR2_RSTCAL_Set) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
	
  return  bitstatus;
}

/*******************************************************************************
* Function Name  : ADC_StartCalibration
* Description    : Starts the selected ADC calibration process.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
* Return         : None
*******************************************************************************/
void ADC_StartCalibration(ADC_TypeDef* ADCx)
{ 
  ADCx->CTLR2 |= CTLR2_CAL_Set;
}

/*******************************************************************************
* Function Name  : ADC_GetCalibrationStatus
* Description    : Gets the selected ADC calibration status.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
* Return         : FlagStatus: SET or RESET.
*******************************************************************************/
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;

  if ((ADCx->CTLR2 & CTLR2_CAL_Set) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return  bitstatus;
}

/*******************************************************************************
* Function Name  : ADC_SoftwareStartConvCmd
* Description    : Enables or disables the selected ADC software start conversion.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ADCx->CTLR2 |= CTLR2_EXTTRIG_SWSTART_Set;
  }
  else
  {
    ADCx->CTLR2 &= CTLR2_EXTTRIG_SWSTART_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_GetSoftwareStartConvStatus
* Description    : Gets the selected ADC Software start conversion Status.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
* Return         : FlagStatus: SET or RESET.
*******************************************************************************/
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;

  if ((ADCx->CTLR2 & CTLR2_SWSTART_Set) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return  bitstatus;
}

/*******************************************************************************
* Function Name  : ADC_DiscModeChannelCountConfig
* Description    : Configures the discontinuous mode for the selected ADC regular
*      group channel.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  Number: specifies the discontinuous mode regular channel
*       count value.
*                    This number must be between 1 and 8.
* Return         : None
*******************************************************************************/
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number)
{
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;

  tmpreg1 = ADCx->CTLR1;
  tmpreg1 &= CTLR1_DISCNUM_Reset;
  tmpreg2 = Number - 1;
  tmpreg1 |= tmpreg2 << 13;
  ADCx->CTLR1 = tmpreg1;
}

/*******************************************************************************
* Function Name  : ADC_DiscModeCmd
* Description    : Enables or disables the discontinuous mode on regular group
*      channel for the specified ADC.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ADCx->CTLR1 |= CTLR1_DISCEN_Set;
  }
  else
  {
    ADCx->CTLR1 &= CTLR1_DISCEN_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_RegularChannelConfig
* Description    : Configures for the selected ADC regular channel its corresponding
*      rank in the sequencer and its sample time.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_Channel: the ADC channel to configure.
*                    ADC_Channel_0: ADC Channel0 selected.
*                    ADC_Channel_1: ADC Channel1 selected.
*                    ADC_Channel_2: ADC Channel2 selected.
*                    ADC_Channel_3: ADC Channel3 selected.
*                    ADC_Channel_4: ADC Channel4 selected.
*                    ADC_Channel_5: ADC Channel5 selected.
*                    ADC_Channel_6: ADC Channel6 selected.
*                    ADC_Channel_7: ADC Channel7 selected.
*                    ADC_Channel_8: ADC Channel8 selected.
*                    ADC_Channel_9: ADC Channel9 selected.
*                    ADC_Channel_10: ADC Channel10 selected.
*                    ADC_Channel_11: ADC Channel11 selected.
*                    ADC_Channel_12: ADC Channel12 selected.
*                    ADC_Channel_13: ADC Channel13 selected.
*                    ADC_Channel_14: ADC Channel14 selected.
*                    ADC_Channel_15: ADC Channel15 selected.
*                    ADC_Channel_16: ADC Channel16 selected.
*                    ADC_Channel_17: ADC Channel17 selected.
*                  Rank: The rank in the regular group sequencer.
*                    This parameter must be between 1 to 16.
*                  ADC_SampleTime: The sample time value to be set for the selected channel.
*                    ADC_SampleTime_1Cycles5: Sample time equal to 1.5 cycles.
*                    ADC_SampleTime_7Cycles5: Sample time equal to 7.5 cycles.
*                    ADC_SampleTime_13Cycles5: Sample time equal to 13.5 cycles.
*                    ADC_SampleTime_28Cycles5: Sample time equal to 28.5 cycles.	
*                    ADC_SampleTime_41Cycles5: Sample time equal to 41.5 cycles.	
*                    ADC_SampleTime_55Cycles5: Sample time equal to 55.5 cycles.	
*                    ADC_SampleTime_71Cycles5: Sample time equal to 71.5 cycles.	
*                    ADC_SampleTime_239Cycles5: Sample time equal to 239.5 cycles.	                   
* Return         : None
*******************************************************************************/
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;

  if (ADC_Channel > ADC_Channel_9)
  {
    tmpreg1 = ADCx->SAMPTR1;
    tmpreg2 = SAMPTR1_SMP_Set << (3 * (ADC_Channel - 10));
    tmpreg1 &= ~tmpreg2;
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
    tmpreg1 |= tmpreg2;
    ADCx->SAMPTR1 = tmpreg1;
  }
  else 
  {
    tmpreg1 = ADCx->SAMPTR2;
    tmpreg2 = SAMPTR2_SMP_Set << (3 * ADC_Channel);
    tmpreg1 &= ~tmpreg2;
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
    tmpreg1 |= tmpreg2;
    ADCx->SAMPTR2 = tmpreg1;
  }

  if (Rank < 7)
  {
    tmpreg1 = ADCx->RSQR3;
    tmpreg2 = RSQR3_SQ_Set << (5 * (Rank - 1));
    tmpreg1 &= ~tmpreg2;
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 1));
    tmpreg1 |= tmpreg2;
    ADCx->RSQR3 = tmpreg1;
  }
  else if (Rank < 13)
  {
    tmpreg1 = ADCx->RSQR2;
    tmpreg2 = RSQR2_SQ_Set << (5 * (Rank - 7));
    tmpreg1 &= ~tmpreg2;
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 7));
    tmpreg1 |= tmpreg2;
    ADCx->RSQR2 = tmpreg1;
  }
  else
  {
    tmpreg1 = ADCx->RSQR1;
    tmpreg2 = RSQR1_SQ_Set << (5 * (Rank - 13));
    tmpreg1 &= ~tmpreg2;
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 13));
    tmpreg1 |= tmpreg2;
    ADCx->RSQR1 = tmpreg1;
  }
}

/*******************************************************************************
* Function Name  : ADC_ExternalTrigConvCmd
* Description    : Enables or disables the ADCx conversion through external trigger.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ADCx->CTLR2 |= CTLR2_EXTTRIG_Set;
  }
  else
  {
    ADCx->CTLR2 &= CTLR2_EXTTRIG_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_GetConversionValue
* Description    : Returns the last ADCx conversion result data for regular channel.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
* Return         : ADCx->RDATAR:
*                    The Data conversion value.
*******************************************************************************/
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx)
{
  return (uint16_t) ADCx->RDATAR;
}

/*******************************************************************************
* Function Name  : ADC_GetDualModeConversionValue
* Description    : Returns the last ADC1 and ADC2 conversion result data in dual mode.
* Input          : None
* Return         : RDATAR_ADDRESS:
*                    The Data conversion value.
*******************************************************************************/
uint32_t ADC_GetDualModeConversionValue(void)
{
  return (*(__IO uint32_t *) RDATAR_ADDRESS);
}

/*******************************************************************************
* Function Name  : ADC_AutoInjectedConvCmd
* Description    : Enables or disables the selected ADC automatic injected group
*      conversion after regular one.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ADCx->CTLR1 |= CTLR1_JAUTO_Set;
  }
  else
  {
    ADCx->CTLR1 &= CTLR1_JAUTO_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_InjectedDiscModeCmd
* Description    : Enables or disables the discontinuous mode for injected group
*      channel for the specified ADC.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ADCx->CTLR1 |= CTLR1_JDISCEN_Set;
  }
  else
  {
    ADCx->CTLR1 &= CTLR1_JDISCEN_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_ExternalTrigInjectedConvConfig
* Description    : Configures the ADCx external trigger for injected channels conversion.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_ExternalTrigInjecConv: specifies the ADC trigger to start 
*      injected conversion.
*                    ADC_ExternalTrigInjecConv_T1_TRGO: Timer1 TRGO event selected.
*                    ADC_ExternalTrigInjecConv_T1_CC4: Timer1 capture compare4 selected. 
*                    ADC_ExternalTrigInjecConv_T2_TRGO: Timer2 TRGO event selected. 
*                    ADC_ExternalTrigInjecConv_T2_CC1: Timer2 capture compare1 selected. 
*                    ADC_ExternalTrigInjecConv_T3_CC4: Timer3 capture compare4 selected. 
*                    ADC_ExternalTrigInjecConv_T4_TRGO: Timer4 TRGO event selected.
*                    ADC_ExternalTrigInjecConv_Ext_IT15_TIM8_CC4: External interrupt 
*      line 15 event selected.
*                    ADC_ExternalTrigInjecConv_None: Injected conversion started
*      by software and not by external trigger.                   
* Return         : None
*******************************************************************************/
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv)
{
  uint32_t tmpreg = 0;

  tmpreg = ADCx->CTLR2;
  tmpreg &= CTLR2_JEXTSEL_Reset;
  tmpreg |= ADC_ExternalTrigInjecConv;
  ADCx->CTLR2 = tmpreg;
}

/*******************************************************************************
* Function Name  : ADC_ExternalTrigInjectedConvCmd
* Description    : Enables or disables the ADCx injected channels conversion through
*      external trigger.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ADCx->CTLR2 |= CTLR2_JEXTTRIG_Set;
  }
  else
  {
    ADCx->CTLR2 &= CTLR2_JEXTTRIG_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_SoftwareStartInjectedConvCmd
* Description    : Enables or disables the selected ADC start of the injected 
*      channels conversion.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ADC_SoftwareStartInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ADCx->CTLR2 |= CTLR2_JEXTTRIG_JSWSTART_Set;
  }
  else
  {
    ADCx->CTLR2 &= CTLR2_JEXTTRIG_JSWSTART_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_GetSoftwareStartInjectedConvCmdStatus
* Description    : Gets the selected ADC Software start injected conversion Status.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
* Return         : FlagStatus: SET or RESET.
*******************************************************************************/
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
	
  if ((ADCx->CTLR2 & CTLR2_JSWSTART_Set) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return  bitstatus;
}

/*******************************************************************************
* Function Name  : ADC_InjectedChannelConfig
* Description    : Configures for the selected ADC injected channel its corresponding
*      rank in the sequencer and its sample time.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_Channel: the ADC channel to configure.
*                    ADC_Channel_0: ADC Channel0 selected.
*                    ADC_Channel_1: ADC Channel1 selected.
*                    ADC_Channel_2: ADC Channel2 selected.
*                    ADC_Channel_3: ADC Channel3 selected.
*                    ADC_Channel_4: ADC Channel4 selected.
*                    ADC_Channel_5: ADC Channel5 selected.
*                    ADC_Channel_6: ADC Channel6 selected.
*                    ADC_Channel_7: ADC Channel7 selected.
*                    ADC_Channel_8: ADC Channel8 selected.
*                    ADC_Channel_9: ADC Channel9 selected.
*                    ADC_Channel_10: ADC Channel10 selected.
*                    ADC_Channel_11: ADC Channel11 selected.
*                    ADC_Channel_12: ADC Channel12 selected.
*                    ADC_Channel_13: ADC Channel13 selected.
*                    ADC_Channel_14: ADC Channel14 selected.
*                    ADC_Channel_15: ADC Channel15 selected.
*                    ADC_Channel_16: ADC Channel16 selected.
*                    ADC_Channel_17: ADC Channel17 selected.
*                  Rank: The rank in the injected group sequencer.
*                    This parameter must be between 1 to 4.
*                  ADC_SampleTime: The sample time value to be set for the selected channel.
*                    ADC_SampleTime_1Cycles5: Sample time equal to 1.5 cycles.
*                    ADC_SampleTime_7Cycles5: Sample time equal to 7.5 cycles.
*                    ADC_SampleTime_13Cycles5: Sample time equal to 13.5 cycles.
*                    ADC_SampleTime_28Cycles5: Sample time equal to 28.5 cycles.	
*                    ADC_SampleTime_41Cycles5: Sample time equal to 41.5 cycles.	
*                    ADC_SampleTime_55Cycles5: Sample time equal to 55.5 cycles.	
*                    ADC_SampleTime_71Cycles5: Sample time equal to 71.5 cycles.	
*                    ADC_SampleTime_239Cycles5: Sample time equal to 239.5 cycles.                   
* Return         : None
*******************************************************************************/
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0, tmpreg3 = 0;

  if (ADC_Channel > ADC_Channel_9)
  {
    tmpreg1 = ADCx->SAMPTR1;
    tmpreg2 = SAMPTR1_SMP_Set << (3*(ADC_Channel - 10));
    tmpreg1 &= ~tmpreg2;
    tmpreg2 = (uint32_t)ADC_SampleTime << (3*(ADC_Channel - 10));
    tmpreg1 |= tmpreg2;
    ADCx->SAMPTR1 = tmpreg1;
  }
  else 
  {
    tmpreg1 = ADCx->SAMPTR2;
    tmpreg2 = SAMPTR2_SMP_Set << (3 * ADC_Channel);
    tmpreg1 &= ~tmpreg2;
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
    tmpreg1 |= tmpreg2;
    ADCx->SAMPTR2 = tmpreg1;
  }

  tmpreg1 = ADCx->ISQR;
  tmpreg3 =  (tmpreg1 & ISQR_JL_Set)>> 20;
  tmpreg2 = ISQR_JSQ_Set << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
  tmpreg1 &= ~tmpreg2;
  tmpreg2 = (uint32_t)ADC_Channel << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
  tmpreg1 |= tmpreg2;
  ADCx->ISQR = tmpreg1;
}

/*******************************************************************************
* Function Name  : ADC_InjectedSequencerLengthConfig
* Description    : Configures the sequencer length for injected channels.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  Length: The sequencer length.
*                    This parameter must be a number between 1 to 4.
* Return         : None
*******************************************************************************/
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t Length)
{
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;

  tmpreg1 = ADCx->ISQR;
  tmpreg1 &= ISQR_JL_Reset;
  tmpreg2 = Length - 1; 
  tmpreg1 |= tmpreg2 << 20;
  ADCx->ISQR = tmpreg1;
}

/*******************************************************************************
* Function Name  : ADC_SetInjectedOffset
* Description    : Set the injected channels conversion value offset.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_InjectedChannel: the ADC injected channel to set its offset. 
*                    ADC_InjectedChannel_1: Injected Channel1 selected.
*                    ADC_InjectedChannel_2: Injected Channel2 selected.
*                    ADC_InjectedChannel_3: Injected Channel3 selected.
*                    ADC_InjectedChannel_4: Injected Channel4 selected.
*                  Offset: the offset value for the selected ADC injected channel.
*                    This parameter must be a 12bit value.
* Return         : None
*******************************************************************************/
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset)
{
  __IO uint32_t tmp = 0;
  
  tmp = (uint32_t)ADCx;
  tmp += ADC_InjectedChannel;
  
  *(__IO uint32_t *) tmp = (uint32_t)Offset;
}

/*******************************************************************************
* Function Name  : ADC_GetInjectedConversionValue
* Description    : Returns the ADC injected channel conversion result.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_InjectedChannel: the converted ADC injected channel.
*                    ADC_InjectedChannel_1: Injected Channel1 selected.
*                    ADC_InjectedChannel_2: Injected Channel2 selected.
*                    ADC_InjectedChannel_3: Injected Channel3 selected.
*                    ADC_InjectedChannel_4: Injected Channel4 selected.
* Return         : tmp: The Data conversion value.
*******************************************************************************/
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel)
{
  __IO uint32_t tmp = 0;
  
  tmp = (uint32_t)ADCx;
  tmp += ADC_InjectedChannel + IDATAR_Offset;
  
  return (uint16_t) (*(__IO uint32_t*)  tmp);   
}

/*******************************************************************************
* Function Name  : ADC_AnalogWatchdogCmd
* Description    : Enables or disables the analog watchdog on single/all regular
*      or injected channels.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_AnalogWatchdog: the ADC analog watchdog configuration.
*                    ADC_AnalogWatchdog_SingleRegEnable: Analog watchdog on a 
*      single regular channel.
*                    ADC_AnalogWatchdog_SingleInjecEnable: Analog watchdog on a 
*      single injected channel.
*                    ADC_AnalogWatchdog_SingleRegOrInjecEnable: Analog watchdog 
*      on a single regular or injected channel.
*                    ADC_AnalogWatchdog_AllRegEnable: Analog watchdog on  all 
*      regular channel.
*                    ADC_AnalogWatchdog_AllInjecEnable: Analog watchdog on  all 
*      injected channel.
*                    ADC_AnalogWatchdog_AllRegAllInjecEnable: Analog watchdog on 
*      all regular and injected channels.
*                    ADC_AnalogWatchdog_None: No channel guarded by the analog 
*      watchdog.
* Return         : None
*******************************************************************************/
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog)
{
  uint32_t tmpreg = 0;

  tmpreg = ADCx->CTLR1;
  tmpreg &= CTLR1_AWDMode_Reset;
  tmpreg |= ADC_AnalogWatchdog;
  ADCx->CTLR1 = tmpreg;
}

/*******************************************************************************
* Function Name  : ADC_AnalogWatchdogThresholdsConfig
* Description    : Configures the high and low thresholds of the analog watchdog.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  HighThreshold: the ADC analog watchdog High threshold value.
*                    This parameter must be a 12bit value.
*                  LowThreshold: the ADC analog watchdog Low threshold value.
*                    This parameter must be a 12bit value.
* Return         : None
*******************************************************************************/
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold,
                                        uint16_t LowThreshold)
{
  ADCx->WDHTR = HighThreshold;
  ADCx->WDLTR = LowThreshold;
}

/*******************************************************************************
* Function Name  : ADC_AnalogWatchdogSingleChannelConfig
* Description    : Configures the analog watchdog guarded single channel.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_Channel: the ADC channel to configure for the analog watchdog.
*                    ADC_Channel_0: ADC Channel0 selected.
*                    ADC_Channel_1: ADC Channel1 selected.
*                    ADC_Channel_2: ADC Channel2 selected.
*                    ADC_Channel_3: ADC Channel3 selected.
*                    ADC_Channel_4: ADC Channel4 selected.
*                    ADC_Channel_5: ADC Channel5 selected.
*                    ADC_Channel_6: ADC Channel6 selected.
*                    ADC_Channel_7: ADC Channel7 selected.
*                    ADC_Channel_8: ADC Channel8 selected.
*                    ADC_Channel_9: ADC Channel9 selected.
*                    ADC_Channel_10: ADC Channel10 selected.
*                    ADC_Channel_11: ADC Channel11 selected.
*                    ADC_Channel_12: ADC Channel12 selected.
*                    ADC_Channel_13: ADC Channel13 selected.
*                    ADC_Channel_14: ADC Channel14 selected.
*                    ADC_Channel_15: ADC Channel15 selected.
*                    ADC_Channel_16: ADC Channel16 selected.
*                    ADC_Channel_17: ADC Channel17 selected.                   
* Return         : None
*******************************************************************************/
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel)
{
  uint32_t tmpreg = 0;

  tmpreg = ADCx->CTLR1;
  tmpreg &= CTLR1_AWDCH_Reset;
  tmpreg |= ADC_Channel;
  ADCx->CTLR1 = tmpreg;
}

/*******************************************************************************
* Function Name  : ADC_TempSensorVrefintCmd
* Description    : Enables or disables the temperature sensor and Vrefint channel.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ADC_TempSensorVrefintCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ADC1->CTLR2 |= CTLR2_TSVREFE_Set;
  }
  else
  {
    ADC1->CTLR2 &= CTLR2_TSVREFE_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_GetFlagStatus
* Description    : Checks whether the specified ADC flag is set or not.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_FLAG: specifies the flag to check.
*                    ADC_FLAG_AWD: Analog watchdog flag.
*                    ADC_FLAG_EOC: End of conversion flag.
*                    ADC_FLAG_JEOC: End of injected group conversion flag.
*                    ADC_FLAG_JSTRT: Start of injected group conversion flag.
*                    ADC_FLAG_STRT: Start of regular group conversion flag.
* Return         : FlagStatus: SET or RESET.
*******************************************************************************/
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;

  if ((ADCx->STATR & ADC_FLAG) != (uint8_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return  bitstatus;
}

/*******************************************************************************
* Function Name  : ADC_ClearFlag
* Description    : Clears the ADCx's pending flags.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_FLAG: specifies the flag to clear.
*                    ADC_FLAG_AWD: Analog watchdog flag.
*                    ADC_FLAG_EOC: End of conversion flag.
*                    ADC_FLAG_JEOC: End of injected group conversion flag.
*                    ADC_FLAG_JSTRT: Start of injected group conversion flag.
*                    ADC_FLAG_STRT: Start of regular group conversion flag.
* Return         : None
*******************************************************************************/
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG)
{
  ADCx->STATR = ~(uint32_t)ADC_FLAG;
}

/*******************************************************************************
* Function Name  : ADC_GetITStatus
* Description    : Checks whether the specified ADC interrupt has occurred or not.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_IT: specifies the ADC interrupt source to check.
*                    ADC_IT_EOC: End of conversion interrupt mask.
*                    ADC_IT_AWD: Analog watchdog interrupt mask.
*                    ADC_IT_JEOC: End of injected conversion interrupt mask.
* Return         : ITStatus: SET or RESET.
*******************************************************************************/
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t itmask = 0, enablestatus = 0;

  itmask = ADC_IT >> 8;
  enablestatus = (ADCx->CTLR1 & (uint8_t)ADC_IT) ;
	
  if (((ADCx->STATR & itmask) != (uint32_t)RESET) && enablestatus)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return  bitstatus;
}

/*******************************************************************************
* Function Name  : ADC_ClearITPendingBit
* Description    : Clears the ADCx's interrupt pending bits.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  ADC_IT: specifies the ADC interrupt pending bit to clear.
*                    ADC_IT_EOC: End of conversion interrupt mask.
*                    ADC_IT_AWD: Analog watchdog interrupt mask.
*                    ADC_IT_JEOC: End of injected conversion interrupt mask.
* Return         : None
*******************************************************************************/
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT)
{
  uint8_t itmask = 0;

  itmask = (uint8_t)(ADC_IT >> 8);
  ADCx->STATR = ~(uint32_t)itmask;
}

/*******************************************************************************
* Function Name  : TempSensor_Volt_To_Temper
* Description    : Internal Temperature Sensor Voltage to temperature.
* Input          : Value: Voltage Value(mv).
* Return         : Temper: Temperature Value.
*******************************************************************************/
s32 TempSensor_Volt_To_Temper(s32 Value)
{
	s32 Temper, Refer_Volt, Refer_Temper;
	s32 k=43;
	
	Refer_Volt = (s32)((*(u32*)0x1FFFF898)&0x0000FFFF);
	Refer_Temper = (s32)(((*(u32*)0x1FFFF898)>>16) & 0x0000FFFF);
	
	Temper = Refer_Temper + ((Value-Refer_Volt)*10+(k>>1))/k;
	
	return Temper;
}

/*******************************************************************************
* Function Name  : ADC_BufferCmd
* Description    : Enables or disables the ADCx buffer.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ADC_BufferCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ADCx->CTLR1 |= (1<<26);
  }
  else
  {
    ADCx->CTLR1 &= ~(1<<26);
  }
}

/*******************************************************************************
* Function Name  : Get_CalibrationValue
* Description    : Get ADCx Calibration Value.
* Input          : ADCx:
*                    where x can be 1 to select the ADC peripheral.
* Return         : CalibrationValue
*******************************************************************************/
int16_t Get_CalibrationValue(ADC_TypeDef* ADCx)
{
    __IO uint8_t i,j;
    uint16_t buf[10];
    __IO uint16_t t;

    for(i=0; i<10; i++){
        ADC_ResetCalibration(ADC1);
        while(ADC_GetResetCalibrationStatus(ADC1));
        ADC_StartCalibration(ADC1);
        while(ADC_GetCalibrationStatus(ADC1));
        buf[i] = ADCx->RDATAR;
    }

    for(i=0; i<9; i++){
        for(j=0; j<9-i; j++){
            if(buf[j]>buf[j+1]){
              t=buf[j];
              buf[j]=buf[j+1];
              buf[j+1]= t;
            }
        }
    }

    t=0;
    for(i=0; i<6; i++){
        t += buf[i+2];
    }

    t = (t/6)+((t%6)/3);

    return (int16_t)((int16_t)t-2048);
}


