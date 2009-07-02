/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_adc.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the ADC firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ADC DISCNUM mask */
#define CR1_DISCNUM_Reset           ((u32)0xFFFF1FFF)

/* ADC DISCEN mask */
#define CR1_DISCEN_Set              ((u32)0x00000800)
#define CR1_DISCEN_Reset            ((u32)0xFFFFF7FF)

/* ADC JAUTO mask */
#define CR1_JAUTO_Set               ((u32)0x00000400)
#define CR1_JAUTO_Reset             ((u32)0xFFFFFBFF)

/* ADC JDISCEN mask */
#define CR1_JDISCEN_Set             ((u32)0x00001000)
#define CR1_JDISCEN_Reset           ((u32)0xFFFFEFFF)

/* ADC AWDCH mask */
#define CR1_AWDCH_Reset             ((u32)0xFFFFFFE0)

/* ADC Analog watchdog enable mode mask */
#define CR1_AWDMode_Reset           ((u32)0xFF3FFDFF)

/* CR1 register Mask */
#define CR1_CLEAR_Mask              ((u32)0xFFF0FEFF)

/* ADC ADON mask */
#define CR2_ADON_Set                ((u32)0x00000001)
#define CR2_ADON_Reset              ((u32)0xFFFFFFFE)

/* ADC DMA mask */
#define CR2_DMA_Set                 ((u32)0x00000100)
#define CR2_DMA_Reset               ((u32)0xFFFFFEFF)

/* ADC RSTCAL mask */
#define CR2_RSTCAL_Set              ((u32)0x00000008)

/* ADC CAL mask */
#define CR2_CAL_Set                 ((u32)0x00000004)

/* ADC SWSTART mask */
#define CR2_SWSTART_Set             ((u32)0x00400000)

/* ADC EXTTRIG mask */
#define CR2_EXTTRIG_Set             ((u32)0x00100000)
#define CR2_EXTTRIG_Reset           ((u32)0xFFEFFFFF)

/* ADC Software start mask */
#define CR2_EXTTRIG_SWSTART_Set     ((u32)0x00500000)
#define CR2_EXTTRIG_SWSTART_Reset   ((u32)0xFFAFFFFF)

/* ADC JEXTSEL mask */
#define CR2_JEXTSEL_Reset           ((u32)0xFFFF8FFF)

/* ADC JEXTTRIG mask */
#define CR2_JEXTTRIG_Set            ((u32)0x00008000)
#define CR2_JEXTTRIG_Reset          ((u32)0xFFFF7FFF)

/* ADC JSWSTART mask */
#define CR2_JSWSTART_Set            ((u32)0x00200000)

/* ADC injected software start mask */
#define CR2_JEXTTRIG_JSWSTART_Set   ((u32)0x00208000)
#define CR2_JEXTTRIG_JSWSTART_Reset ((u32)0xFFDF7FFF)

/* ADC TSPD mask */
#define CR2_TSVREFE_Set             ((u32)0x00800000)
#define CR2_TSVREFE_Reset           ((u32)0xFF7FFFFF)

/* CR2 register Mask */
#define CR2_CLEAR_Mask              ((u32)0xFFF1F7FD)

/* ADC SQx mask */
#define SQR3_SQ_Set                 ((u32)0x0000001F)
#define SQR2_SQ_Set                 ((u32)0x0000001F)
#define SQR1_SQ_Set                 ((u32)0x0000001F)

/* SQR1 register Mask */
#define SQR1_CLEAR_Mask             ((u32)0xFF0FFFFF)

/* ADC JSQx mask */
#define JSQR_JSQ_Set                ((u32)0x0000001F)

/* ADC JL mask */
#define JSQR_JL_Set                 ((u32)0x00300000)
#define JSQR_JL_Reset               ((u32)0xFFCFFFFF)

/* ADC SMPx mask */
#define SMPR1_SMP_Set               ((u32)0x00000007)
#define SMPR2_SMP_Set               ((u32)0x00000007)

/* ADC JDRx registers offset */
#define JDR_Offset                  ((u8)0x28)

/* ADC1 DR register base address */
#define DR_ADDRESS                  ((u32)0x4001244C)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : ADC_DeInit
* Description    : Deinitializes the ADCx peripheral registers to their default
*                  reset values.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_DeInit(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  switch (*(u32*)&ADCx)
  {
    case ADC1_BASE:
      /* Enable ADC1 reset state */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
      /* Release ADC1 from reset state */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);
      break;
    
    case ADC2_BASE:
      /* Enable ADC2 reset state */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, ENABLE);
      /* Release ADC2 from reset state */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, DISABLE);
      break;
      
    case ADC3_BASE:
      /* Enable ADC3 reset state */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, ENABLE);
      /* Release ADC3 from reset state */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, DISABLE);
      break; 

    default:
      break;
  }
}

/*******************************************************************************
* Function Name  : ADC_Init
* Description    : Initializes the ADCx peripheral according to the specified parameters
*                  in the ADC_InitStruct.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_InitStruct: pointer to an ADC_InitTypeDef structure that
*                    contains the configuration information for the specified
*                    ADC peripheral.
* Output         : None
* Return         : None
******************************************************************************/
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
  u32 tmpreg1 = 0;
  u8 tmpreg2 = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_MODE(ADC_InitStruct->ADC_Mode));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ScanConvMode));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ContinuousConvMode));  		    
  assert_param(IS_ADC_EXT_TRIG(ADC_InitStruct->ADC_ExternalTrigConv));   
  assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign)); 
  assert_param(IS_ADC_REGULAR_LENGTH(ADC_InitStruct->ADC_NbrOfChannel));

  /*---------------------------- ADCx CR1 Configuration -----------------*/
  /* Get the ADCx CR1 value */
  tmpreg1 = ADCx->CR1;
  /* Clear DUALMOD and SCAN bits */
  tmpreg1 &= CR1_CLEAR_Mask;
  /* Configure ADCx: Dual mode and scan conversion mode */
  /* Set DUALMOD bits according to ADC_Mode value */
  /* Set SCAN bit according to ADC_ScanConvMode value */
  tmpreg1 |= (u32)(ADC_InitStruct->ADC_Mode | ((u32)ADC_InitStruct->ADC_ScanConvMode << 8));
  /* Write to ADCx CR1 */
  ADCx->CR1 = tmpreg1;

  /*---------------------------- ADCx CR2 Configuration -----------------*/
  /* Get the ADCx CR2 value */
  tmpreg1 = ADCx->CR2;
  /* Clear CONT, ALIGN and EXTSEL bits */
  tmpreg1 &= CR2_CLEAR_Mask;
  /* Configure ADCx: external trigger event and continuous conversion mode */
  /* Set ALIGN bit according to ADC_DataAlign value */
  /* Set EXTSEL bits according to ADC_ExternalTrigConv value */
  /* Set CONT bit according to ADC_ContinuousConvMode value */
  tmpreg1 |= (u32)(ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ExternalTrigConv |
            ((u32)ADC_InitStruct->ADC_ContinuousConvMode << 1));
  /* Write to ADCx CR2 */
  ADCx->CR2 = tmpreg1;

  /*---------------------------- ADCx SQR1 Configuration -----------------*/
  /* Get the ADCx SQR1 value */
  tmpreg1 = ADCx->SQR1;
  /* Clear L bits */
  tmpreg1 &= SQR1_CLEAR_Mask;
  /* Configure ADCx: regular channel sequence length */
  /* Set L bits according to ADC_NbrOfChannel value */
  tmpreg2 |= (ADC_InitStruct->ADC_NbrOfChannel - 1);
  tmpreg1 |= ((u32)tmpreg2 << 20);
  /* Write to ADCx SQR1 */
  ADCx->SQR1 = tmpreg1;
}

/*******************************************************************************
* Function Name  : ADC_StructInit
* Description    : Fills each ADC_InitStruct member with its default value.
* Input          : ADC_InitStruct : pointer to an ADC_InitTypeDef structure
*                  which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
  /* Reset ADC init structure parameters values */
  /* Initialize the ADC_Mode member */
  ADC_InitStruct->ADC_Mode = ADC_Mode_Independent;

  /* initialize the ADC_ScanConvMode member */
  ADC_InitStruct->ADC_ScanConvMode = DISABLE;

  /* Initialize the ADC_ContinuousConvMode member */
  ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;

  /* Initialize the ADC_ExternalTrigConv member */
  ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;

  /* Initialize the ADC_DataAlign member */
  ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;

  /* Initialize the ADC_NbrOfChannel member */
  ADC_InitStruct->ADC_NbrOfChannel = 1;
}

/*******************************************************************************
* Function Name  : ADC_Cmd
* Description    : Enables or disables the specified ADC peripheral.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - NewState: new state of the ADCx peripheral. This parameter
*                    can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the ADON bit to wake up the ADC from power down mode */
    ADCx->CR2 |= CR2_ADON_Set;
  }
  else
  {
    /* Disable the selected ADC peripheral */
    ADCx->CR2 &= CR2_ADON_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_DMACmd
* Description    : Enables or disables the specified ADC DMA request.
* Input          : - ADCx: where x can be 1 or 3 to select the ADC peripheral.
*                    Note: ADC2 hasn't a DMA capability.
*                  - NewState: new state of the selected ADC DMA transfer.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_DMA_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC DMA request */
    ADCx->CR2 |= CR2_DMA_Set;
  }
  else
  {
    /* Disable the selected ADC DMA request */
    ADCx->CR2 &= CR2_DMA_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_ITConfig
* Description    : Enables or disables the specified ADC interrupts.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_IT: specifies the ADC interrupt sources to be enabled
*                    or disabled. 
*                    This parameter can be any combination of the following values:
*                       - ADC_IT_EOC: End of conversion interrupt mask
*                       - ADC_IT_AWD: Analog watchdog interrupt mask
*                       - ADC_IT_JEOC: End of injected conversion interrupt mask
*                  - NewState: new state of the specified ADC interrupts.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_ITConfig(ADC_TypeDef* ADCx, u16 ADC_IT, FunctionalState NewState)
{
  u8 itmask = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_ADC_IT(ADC_IT));

  /* Get the ADC IT index */
  itmask = (u8)ADC_IT;

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC interrupts */
    ADCx->CR1 |= itmask;
  }
  else
  {
    /* Disable the selected ADC interrupts */
    ADCx->CR1 &= (~(u32)itmask);
  }
}

/*******************************************************************************
* Function Name  : ADC_ResetCalibration
* Description    : Resets the selected ADC calibration registers.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_ResetCalibration(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Resets the selected ADC calibartion registers */  
  ADCx->CR2 |= CR2_RSTCAL_Set;
}

/*******************************************************************************
* Function Name  : ADC_GetResetCalibrationStatus
* Description    : Gets the selected ADC reset calibration registers status.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* Output         : None
* Return         : The new state of ADC reset calibration registers (SET or RESET).
*******************************************************************************/
FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Check the status of RSTCAL bit */
  if ((ADCx->CR2 & CR2_RSTCAL_Set) != (u32)RESET)
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

/*******************************************************************************
* Function Name  : ADC_StartCalibration
* Description    : Starts the selected ADC calibration process.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_StartCalibration(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Enable the selected ADC calibration process */  
  ADCx->CR2 |= CR2_CAL_Set;
}

/*******************************************************************************
* Function Name  : ADC_GetCalibrationStatus
* Description    : Gets the selected ADC calibration status.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* Output         : None
* Return         : The new state of ADC calibration (SET or RESET).
*******************************************************************************/
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Check the status of CAL bit */
  if ((ADCx->CR2 & CR2_CAL_Set) != (u32)RESET)
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

/*******************************************************************************
* Function Name  : ADC_SoftwareStartConvCmd
* Description    : Enables or disables the selected ADC software start conversion .
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - NewState: new state of the selected ADC software start conversion.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC conversion on external event and start the selected
       ADC conversion */
    ADCx->CR2 |= CR2_EXTTRIG_SWSTART_Set;
  }
  else
  {
    /* Disable the selected ADC conversion on external event and stop the selected
       ADC conversion */
    ADCx->CR2 &= CR2_EXTTRIG_SWSTART_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_GetSoftwareStartConvStatus
* Description    : Gets the selected ADC Software start conversion Status.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* Output         : None
* Return         : The new state of ADC software start conversion (SET or RESET).
*******************************************************************************/
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Check the status of SWSTART bit */
  if ((ADCx->CR2 & CR2_SWSTART_Set) != (u32)RESET)
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

/*******************************************************************************
* Function Name  : ADC_DiscModeChannelCountConfig
* Description    : Configures the discontinuous mode for the selected ADC regular
*                  group channel.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - Number: specifies the discontinuous mode regular channel
*                    count value. This number must be between 1 and 8.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, u8 Number)
{
  u32 tmpreg1 = 0;
  u32 tmpreg2 = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_REGULAR_DISC_NUMBER(Number));

  /* Get the old register value */
  tmpreg1 = ADCx->CR1;
  /* Clear the old discontinuous mode channel count */
  tmpreg1 &= CR1_DISCNUM_Reset;
  /* Set the discontinuous mode channel count */
  tmpreg2 = Number - 1;
  tmpreg1 |= tmpreg2 << 13;
  /* Store the new register value */
  ADCx->CR1 = tmpreg1;
}

/*******************************************************************************
* Function Name  : ADC_DiscModeCmd
* Description    : Enables or disables the discontinuous mode on regular group
*                  channel for the specified ADC
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - NewState: new state of the selected ADC discontinuous mode
*                    on regular group channel.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC regular discontinuous mode */
    ADCx->CR1 |= CR1_DISCEN_Set;
  }
  else
  {
    /* Disable the selected ADC regular discontinuous mode */
    ADCx->CR1 &= CR1_DISCEN_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_RegularChannelConfig
* Description    : Configures for the selected ADC regular channel its corresponding
*                  rank in the sequencer and its sample time.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_Channel: the ADC channel to configure. 
*                    This parameter can be one of the following values:
*                       - ADC_Channel_0: ADC Channel0 selected
*                       - ADC_Channel_1: ADC Channel1 selected
*                       - ADC_Channel_2: ADC Channel2 selected
*                       - ADC_Channel_3: ADC Channel3 selected
*                       - ADC_Channel_4: ADC Channel4 selected
*                       - ADC_Channel_5: ADC Channel5 selected
*                       - ADC_Channel_6: ADC Channel6 selected
*                       - ADC_Channel_7: ADC Channel7 selected
*                       - ADC_Channel_8: ADC Channel8 selected
*                       - ADC_Channel_9: ADC Channel9 selected
*                       - ADC_Channel_10: ADC Channel10 selected
*                       - ADC_Channel_11: ADC Channel11 selected
*                       - ADC_Channel_12: ADC Channel12 selected
*                       - ADC_Channel_13: ADC Channel13 selected
*                       - ADC_Channel_14: ADC Channel14 selected
*                       - ADC_Channel_15: ADC Channel15 selected
*                       - ADC_Channel_16: ADC Channel16 selected
*                       - ADC_Channel_17: ADC Channel17 selected
*                  - Rank: The rank in the regular group sequencer. This parameter
*                    must be between 1 to 16.
*                  - ADC_SampleTime: The sample time value to be set for the
*                    selected channel. 
*                    This parameter can be one of the following values:
*                       - ADC_SampleTime_1Cycles5: Sample time equal to 1.5 cycles
*                       - ADC_SampleTime_7Cycles5: Sample time equal to 7.5 cycles
*                       - ADC_SampleTime_13Cycles5: Sample time equal to 13.5 cycles
*                       - ADC_SampleTime_28Cycles5: Sample time equal to 28.5 cycles	
*                       - ADC_SampleTime_41Cycles5: Sample time equal to 41.5 cycles	
*                       - ADC_SampleTime_55Cycles5: Sample time equal to 55.5 cycles	
*                       - ADC_SampleTime_71Cycles5: Sample time equal to 71.5 cycles	
*                       - ADC_SampleTime_239Cycles5: Sample time equal to 239.5 cycles	
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel, u8 Rank, u8 ADC_SampleTime)
{
  u32 tmpreg1 = 0, tmpreg2 = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_REGULAR_RANK(Rank));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));

  /* if ADC_Channel_10 ... ADC_Channel_17 is selected */
  if (ADC_Channel > ADC_Channel_9)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR1;
    /* Calculate the mask to clear */
    tmpreg2 = SMPR1_SMP_Set << (3 * (ADC_Channel - 10));
    /* Clear the old discontinuous mode channel count */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (u32)ADC_SampleTime << (3 * (ADC_Channel - 10));
    /* Set the discontinuous mode channel count */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SMPR1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR2;
    /* Calculate the mask to clear */
    tmpreg2 = SMPR2_SMP_Set << (3 * ADC_Channel);
    /* Clear the old discontinuous mode channel count */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (u32)ADC_SampleTime << (3 * ADC_Channel);
    /* Set the discontinuous mode channel count */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SMPR2 = tmpreg1;
  }
  /* For Rank 1 to 6 */
  if (Rank < 7)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR3;
    /* Calculate the mask to clear */
    tmpreg2 = SQR3_SQ_Set << (5 * (Rank - 1));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (u32)ADC_Channel << (5 * (Rank - 1));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR3 = tmpreg1;
  }
  /* For Rank 7 to 12 */
  else if (Rank < 13)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR2;
    /* Calculate the mask to clear */
    tmpreg2 = SQR2_SQ_Set << (5 * (Rank - 7));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (u32)ADC_Channel << (5 * (Rank - 7));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR2 = tmpreg1;
  }
  /* For Rank 13 to 16 */
  else
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR1;
    /* Calculate the mask to clear */
    tmpreg2 = SQR1_SQ_Set << (5 * (Rank - 13));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (u32)ADC_Channel << (5 * (Rank - 13));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR1 = tmpreg1;
  }
}

/*******************************************************************************
* Function Name  : ADC_ExternalTrigConvCmd
* Description    : Enables or disables the ADCx conversion through external trigger.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - NewState: new state of the selected ADC external trigger
*                    start of conversion.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC conversion on external event */
    ADCx->CR2 |= CR2_EXTTRIG_Set;
  }
  else
  {
    /* Disable the selected ADC conversion on external event */
    ADCx->CR2 &= CR2_EXTTRIG_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_GetConversionValue
* Description    : Returns the last ADCx conversion result data for regular channel.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* Output         : None
* Return         : The Data conversion value.
*******************************************************************************/
u16 ADC_GetConversionValue(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Return the selected ADC conversion value */
  return (u16) ADCx->DR;
}

/*******************************************************************************
* Function Name  : ADC_GetDualModeConversionValue
* Description    : Returns the last ADC1 and ADC2 conversion result data in dual mode.
* Output         : None
* Return         : The Data conversion value.
*******************************************************************************/
u32 ADC_GetDualModeConversionValue(void)
{
  /* Return the dual mode conversion value */
  return (*(vu32 *) DR_ADDRESS);
}

/*******************************************************************************
* Function Name  : ADC_AutoInjectedConvCmd
* Description    : Enables or disables the selected ADC automatic injected group
*                  conversion after regular one.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - NewState: new state of the selected ADC auto injected
*                    conversion
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC automatic injected group conversion */
    ADCx->CR1 |= CR1_JAUTO_Set;
  }
  else
  {
    /* Disable the selected ADC automatic injected group conversion */
    ADCx->CR1 &= CR1_JAUTO_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_InjectedDiscModeCmd
* Description    : Enables or disables the discontinuous mode for injected group
*                  channel for the specified ADC
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - NewState: new state of the selected ADC discontinuous mode
*                    on injected group channel.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC injected discontinuous mode */
    ADCx->CR1 |= CR1_JDISCEN_Set;
  }
  else
  {
    /* Disable the selected ADC injected discontinuous mode */
    ADCx->CR1 &= CR1_JDISCEN_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_ExternalTrigInjectedConvConfig
* Description    : Configures the ADCx external trigger for injected channels conversion.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_ExternalTrigInjecConv: specifies the ADC trigger to
*                    start injected conversion. 
*                    This parameter can be one of the following values:
*                       - ADC_ExternalTrigInjecConv_T1_TRGO: Timer1 TRGO event 
*                         selected (for ADC1, ADC2 and ADC3)
*                       - ADC_ExternalTrigInjecConv_T1_CC4: Timer1 capture
*                         compare4 selected (for ADC1, ADC2 and ADC3)
*                       - ADC_ExternalTrigInjecConv_T2_TRGO: Timer2 TRGO event
*                         selected (for ADC1 and ADC2)
*                       - ADC_External TrigInjecConv_T2_CC1: Timer2 capture
*                         compare1 selected (for ADC1 and ADC2)
*                       - ADC_ExternalTrigInjecConv_T3_CC4: Timer3 capture
*                         compare4 selected (for ADC1 and ADC2)
*                       - ADC_ExternalTrigInjecConv_T4_TRGO: Timer4 TRGO event
*                         selected (for ADC1 and ADC2)
*                       - ADC_ExternalTrigInjecConv_Ext_IT15_TIM8_CC4: External
*                         interrupt line 15 or Timer8 capture compare4 event selected
*                         (for ADC1 and ADC2)                       
*                       - ADC_External TrigInjecConv_T4_CC3: Timer4 capture
*                         compare3 selected (for ADC3 only)
*                       - ADC_External TrigInjecConv_T8_CC2: Timer8 capture
*                         compare2 selected (for ADC3 only)                         
*                       - ADC_External TrigInjecConv_T8_CC4: Timer8 capture
*                         compare4 selected (for ADC3 only)
*                       - ADC_ExternalTrigInjecConv_T5_TRGO: Timer5 TRGO event
*                         selected (for ADC3 only)                         
*                       - ADC_External TrigInjecConv_T5_CC4: Timer5 capture
*                         compare4 selected (for ADC3 only)                        
*                       - ADC_ExternalTrigInjecConv_None: Injected conversion
*                         started by software and not by external trigger (for 
*                         ADC1, ADC2 and ADC3)
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, u32 ADC_ExternalTrigInjecConv)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_EXT_INJEC_TRIG(ADC_ExternalTrigInjecConv));

  /* Get the old register value */
  tmpreg = ADCx->CR2;
  /* Clear the old external event selection for injected group */
  tmpreg &= CR2_JEXTSEL_Reset;
  /* Set the external event selection for injected group */
  tmpreg |= ADC_ExternalTrigInjecConv;
  /* Store the new register value */
  ADCx->CR2 = tmpreg;
}

/*******************************************************************************
* Function Name  : ADC_ExternalTrigInjectedConvCmd
* Description    : Enables or disables the ADCx injected channels conversion
*                  through external trigger
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - NewState: new state of the selected ADC external trigger
*                    start of injected conversion.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC external event selection for injected group */
    ADCx->CR2 |= CR2_JEXTTRIG_Set;
  }
  else
  {
    /* Disable the selected ADC external event selection for injected group */
    ADCx->CR2 &= CR2_JEXTTRIG_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_SoftwareStartInjectedConvCmd
* Description    : Enables or disables the selected ADC start of the injected 
*                  channels conversion.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - NewState: new state of the selected ADC software start
*                    injected conversion.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_SoftwareStartInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC conversion for injected group on external event and start the selected
       ADC injected conversion */
    ADCx->CR2 |= CR2_JEXTTRIG_JSWSTART_Set;
  }
  else
  {
    /* Disable the selected ADC conversion on external event for injected group and stop the selected
       ADC injected conversion */
    ADCx->CR2 &= CR2_JEXTTRIG_JSWSTART_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_GetSoftwareStartInjectedConvCmdStatus
* Description    : Gets the selected ADC Software start injected conversion Status.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* Output         : None
* Return         : The new state of ADC software start injected conversion (SET or RESET).
*******************************************************************************/
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Check the status of JSWSTART bit */
  if ((ADCx->CR2 & CR2_JSWSTART_Set) != (u32)RESET)
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

/*******************************************************************************
* Function Name  : ADC_InjectedChannelConfig
* Description    : Configures for the selected ADC injected channel its corresponding
*                  rank in the sequencer and its sample time.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_Channel: the ADC channel to configure. 
*                    This parameter can be one of the following values:
*                       - ADC_Channel_0: ADC Channel0 selected
*                       - ADC_Channel_1: ADC Channel1 selected
*                       - ADC_Channel_2: ADC Channel2 selected
*                       - ADC_Channel_3: ADC Channel3 selected
*                       - ADC_Channel_4: ADC Channel4 selected
*                       - ADC_Channel_5: ADC Channel5 selected
*                       - ADC_Channel_6: ADC Channel6 selected
*                       - ADC_Channel_7: ADC Channel7 selected
*                       - ADC_Channel_8: ADC Channel8 selected
*                       - ADC_Channel_9: ADC Channel9 selected
*                       - ADC_Channel_10: ADC Channel10 selected
*                       - ADC_Channel_11: ADC Channel11 selected
*                       - ADC_Channel_12: ADC Channel12 selected
*                       - ADC_Channel_13: ADC Channel13 selected
*                       - ADC_Channel_14: ADC Channel14 selected
*                       - ADC_Channel_15: ADC Channel15 selected
*                       - ADC_Channel_16: ADC Channel16 selected
*                       - ADC_Channel_17: ADC Channel17 selected
*                  - Rank: The rank in the injected group sequencer. This parameter
*                    must be between 1 to 4.
*                  - ADC_SampleTime: The sample time value to be set for the
*                    selected channel. 
*                    This parameter can be one of the following values:
*                       - ADC_SampleTime_1Cycles5: Sample time equal to 1.5 cycles
*                       - ADC_SampleTime_7Cycles5: Sample time equal to 7.5 cycles
*                       - ADC_SampleTime_13Cycles5: Sample time equal to 13.5 cycles
*                       - ADC_SampleTime_28Cycles5: Sample time equal to 28.5 cycles	
*                       - ADC_SampleTime_41Cycles5: Sample time equal to 41.5 cycles	
*                       - ADC_SampleTime_55Cycles5: Sample time equal to 55.5 cycles	
*                       - ADC_SampleTime_71Cycles5: Sample time equal to 71.5 cycles	
*                       - ADC_SampleTime_239Cycles5: Sample time equal to 239.5 cycles	
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel, u8 Rank, u8 ADC_SampleTime)
{
  u32 tmpreg1 = 0, tmpreg2 = 0, tmpreg3 = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_INJECTED_RANK(Rank));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));

  /* if ADC_Channel_10 ... ADC_Channel_17 is selected */
  if (ADC_Channel > ADC_Channel_9)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR1;
    /* Calculate the mask to clear */
    tmpreg2 = SMPR1_SMP_Set << (3*(ADC_Channel - 10));
    /* Clear the old discontinuous mode channel count */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (u32)ADC_SampleTime << (3*(ADC_Channel - 10));
    /* Set the discontinuous mode channel count */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SMPR1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR2;
    /* Calculate the mask to clear */
    tmpreg2 = SMPR2_SMP_Set << (3 * ADC_Channel);
    /* Clear the old discontinuous mode channel count */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (u32)ADC_SampleTime << (3 * ADC_Channel);
    /* Set the discontinuous mode channel count */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SMPR2 = tmpreg1;
  }

  /* Rank configuration */
  /* Get the old register value */
  tmpreg1 = ADCx->JSQR;
  /* Get JL value: Number = JL+1 */
  tmpreg3 =  (tmpreg1 & JSQR_JL_Set)>> 20;
  /* Calculate the mask to clear: ((Rank-1)+(4-JL-1)) */
  tmpreg2 = JSQR_JSQ_Set << (5 * (u8)((Rank + 3) - (tmpreg3 + 1)));
  /* Clear the old JSQx bits for the selected rank */
  tmpreg1 &= ~tmpreg2;
  /* Calculate the mask to set: ((Rank-1)+(4-JL-1)) */
  tmpreg2 = (u32)ADC_Channel << (5 * (u8)((Rank + 3) - (tmpreg3 + 1)));
  /* Set the JSQx bits for the selected rank */
  tmpreg1 |= tmpreg2;
  /* Store the new register value */
  ADCx->JSQR = tmpreg1;
}

/*******************************************************************************
* Function Name  : ADC_InjectedSequencerLengthConfig
* Description    : Configures the sequencer length for injected channels
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - Length: The sequencer length. 
*                    This parameter must be a number between 1 to 4.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, u8 Length)
{
  u32 tmpreg1 = 0;
  u32 tmpreg2 = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_LENGTH(Length));
  
  /* Get the old register value */
  tmpreg1 = ADCx->JSQR;
  /* Clear the old injected sequnence lenght JL bits */
  tmpreg1 &= JSQR_JL_Reset;
  /* Set the injected sequnence lenght JL bits */
  tmpreg2 = Length - 1; 
  tmpreg1 |= tmpreg2 << 20;
  /* Store the new register value */
  ADCx->JSQR = tmpreg1;
}

/*******************************************************************************
* Function Name  : ADC_SetInjectedOffset
* Description    : Set the injected channels conversion value offset
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_InjectedChannel: the ADC injected channel to set its
*                    offset. 
*                    This parameter can be one of the following values:
*                       - ADC_InjectedChannel_1: Injected Channel1 selected
*                       - ADC_InjectedChannel_2: Injected Channel2 selected
*                       - ADC_InjectedChannel_3: Injected Channel3 selected
*                       - ADC_InjectedChannel_4: Injected Channel4 selected
*                  - Offset: the offset value for the selected ADC injected channel
*                    This parameter must be a 12bit value.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, u8 ADC_InjectedChannel, u16 Offset)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));
  assert_param(IS_ADC_OFFSET(Offset));  

  /* Set the selected injected channel data offset */
  *((vu32 *)((*(u32*)&ADCx) + ADC_InjectedChannel)) = (u32)Offset;
}

/*******************************************************************************
* Function Name  : ADC_GetInjectedConversionValue
* Description    : Returns the ADC injected channel conversion result
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_InjectedChannel: the converted ADC injected channel.
*                    This parameter can be one of the following values:
*                       - ADC_InjectedChannel_1: Injected Channel1 selected
*                       - ADC_InjectedChannel_2: Injected Channel2 selected
*                       - ADC_InjectedChannel_3: Injected Channel3 selected
*                       - ADC_InjectedChannel_4: Injected Channel4 selected
* Output         : None
* Return         : The Data conversion value.
*******************************************************************************/
u16 ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, u8 ADC_InjectedChannel)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));

  /* Returns the selected injected channel conversion data value */
  return (u16) (*(vu32*) (((*(u32*)&ADCx) + ADC_InjectedChannel + JDR_Offset)));
}

/*******************************************************************************
* Function Name  : ADC_AnalogWatchdogCmd
* Description    : Enables or disables the analog watchdog on single/all regular
*                  or injected channels
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_AnalogWatchdog: the ADC analog watchdog configuration.
*                    This parameter can be one of the following values:
*                       - ADC_AnalogWatchdog_SingleRegEnable: Analog watchdog on
*                         a single regular channel
*                       - ADC_AnalogWatchdog_SingleInjecEnable: Analog watchdog on
*                         a single injected channel
*                       - ADC_AnalogWatchdog_SingleRegOrInjecEnable: Analog 
*                         watchdog on a single regular or injected channel
*                       - ADC_AnalogWatchdog_AllRegEnable: Analog watchdog on
*                         all regular channel
*                       - ADC_AnalogWatchdog_AllInjecEnable: Analog watchdog on
*                         all injected channel
*                       - ADC_AnalogWatchdog_AllRegAllInjecEnable: Analog watchdog
*                         on all regular and injected channels
*                       - ADC_AnalogWatchdog_None: No channel guarded by the
*                         analog watchdog
* Output         : None
* Return         : None	  
*******************************************************************************/
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, u32 ADC_AnalogWatchdog)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_ANALOG_WATCHDOG(ADC_AnalogWatchdog));

  /* Get the old register value */
  tmpreg = ADCx->CR1;
  /* Clear AWDEN, AWDENJ and AWDSGL bits */
  tmpreg &= CR1_AWDMode_Reset;
  /* Set the analog watchdog enable mode */
  tmpreg |= ADC_AnalogWatchdog;
  /* Store the new register value */
  ADCx->CR1 = tmpreg;
}

/*******************************************************************************
* Function Name  : ADC_AnalogWatchdogThresholdsConfig
* Description    : Configures the high and low thresholds of the analog watchdog.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - HighThreshold: the ADC analog watchdog High threshold value.
*                    This parameter must be a 12bit value.
*                  - LowThreshold: the ADC analog watchdog Low threshold value.
*                    This parameter must be a 12bit value.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, u16 HighThreshold,
                                        u16 LowThreshold)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_THRESHOLD(HighThreshold));
  assert_param(IS_ADC_THRESHOLD(LowThreshold));

  /* Set the ADCx high threshold */
  ADCx->HTR = HighThreshold;
  /* Set the ADCx low threshold */
  ADCx->LTR = LowThreshold;
}

/*******************************************************************************
* Function Name  : ADC_AnalogWatchdogSingleChannelConfig
* Description    : Configures the analog watchdog guarded single channel
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_Channel: the ADC channel to configure for the analog
*                    watchdog. 
*                    This parameter can be one of the following values:
*                       - ADC_Channel_0: ADC Channel0 selected
*                       - ADC_Channel_1: ADC Channel1 selected
*                       - ADC_Channel_2: ADC Channel2 selected
*                       - ADC_Channel_3: ADC Channel3 selected
*                       - ADC_Channel_4: ADC Channel4 selected
*                       - ADC_Channel_5: ADC Channel5 selected
*                       - ADC_Channel_6: ADC Channel6 selected
*                       - ADC_Channel_7: ADC Channel7 selected
*                       - ADC_Channel_8: ADC Channel8 selected
*                       - ADC_Channel_9: ADC Channel9 selected
*                       - ADC_Channel_10: ADC Channel10 selected
*                       - ADC_Channel_11: ADC Channel11 selected
*                       - ADC_Channel_12: ADC Channel12 selected
*                       - ADC_Channel_13: ADC Channel13 selected
*                       - ADC_Channel_14: ADC Channel14 selected
*                       - ADC_Channel_15: ADC Channel15 selected
*                       - ADC_Channel_16: ADC Channel16 selected
*                       - ADC_Channel_17: ADC Channel17 selected
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));

  /* Get the old register value */
  tmpreg = ADCx->CR1;
  /* Clear the Analog watchdog channel select bits */
  tmpreg &= CR1_AWDCH_Reset;
  /* Set the Analog watchdog channel */
  tmpreg |= ADC_Channel;
  /* Store the new register value */
  ADCx->CR1 = tmpreg;
}

/*******************************************************************************
* Function Name  : ADC_TempSensorVrefintCmd
* Description    : Enables or disables the temperature sensor and Vrefint channel.
* Input          : - NewState: new state of the temperature sensor.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_TempSensorVrefintCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the temperature sensor and Vrefint channel*/
    ADC1->CR2 |= CR2_TSVREFE_Set;
  }
  else
  {
    /* Disable the temperature sensor and Vrefint channel*/
    ADC1->CR2 &= CR2_TSVREFE_Reset;
  }
}

/*******************************************************************************
* Function Name  : ADC_GetFlagStatus
* Description    : Checks whether the specified ADC flag is set or not.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_FLAG: specifies the flag to check. 
*                    This parameter can be one of the following values:
*                       - ADC_FLAG_AWD: Analog watchdog flag
*                       - ADC_FLAG_EOC: End of conversion flag
*                       - ADC_FLAG_JEOC: End of injected group conversion flag
*                       - ADC_FLAG_JSTRT: Start of injected group conversion flag
*                       - ADC_FLAG_STRT: Start of regular group conversion flag
* Output         : None
* Return         : The new state of ADC_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, u8 ADC_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_FLAG(ADC_FLAG));

  /* Check the status of the specified ADC flag */
  if ((ADCx->SR & ADC_FLAG) != (u8)RESET)
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

/*******************************************************************************
* Function Name  : ADC_ClearFlag
* Description    : Clears the ADCx's pending flags.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_FLAG: specifies the flag to clear. 
*                    This parameter can be any combination of the following values:
*                       - ADC_FLAG_AWD: Analog watchdog flag
*                       - ADC_FLAG_EOC: End of conversion flag
*                       - ADC_FLAG_JEOC: End of injected group conversion flag
*                       - ADC_FLAG_JSTRT: Start of injected group conversion flag
*                       - ADC_FLAG_STRT: Start of regular group conversion flag
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_ClearFlag(ADC_TypeDef* ADCx, u8 ADC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));

  /* Clear the selected ADC flags */
  ADCx->SR = ~(u32)ADC_FLAG;
}

/*******************************************************************************
* Function Name  : ADC_GetITStatus
* Description    : Checks whether the specified ADC interrupt has occurred or not.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_IT: specifies the ADC interrupt source to check. 
*                    This parameter can be one of the following values:
*                       - ADC_IT_EOC: End of conversion interrupt mask
*                       - ADC_IT_AWD: Analog watchdog interrupt mask
*                       - ADC_IT_JEOC: End of injected conversion interrupt mask
* Output         : None
* Return         : The new state of ADC_IT (SET or RESET).
*******************************************************************************/
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, u16 ADC_IT)
{
  ITStatus bitstatus = RESET;
  u32 itmask = 0, enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_IT(ADC_IT));

  /* Get the ADC IT index */
  itmask = ADC_IT >> 8;

  /* Get the ADC_IT enable bit status */
  enablestatus = (ADCx->CR1 & (u8)ADC_IT) ;

  /* Check the status of the specified ADC interrupt */
  if (((ADCx->SR & itmask) != (u32)RESET) && enablestatus)
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

/*******************************************************************************
* Function Name  : ADC_ClearITPendingBit
* Description    : Clears the ADCx’s interrupt pending bits.
* Input          : - ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
*                  - ADC_IT: specifies the ADC interrupt pending bit to clear.
*                    This parameter can be any combination of the following values:
*                       - ADC_IT_EOC: End of conversion interrupt mask
*                       - ADC_IT_AWD: Analog watchdog interrupt mask
*                       - ADC_IT_JEOC: End of injected conversion interrupt mask
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, u16 ADC_IT)
{
  u8 itmask = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_IT(ADC_IT));

  /* Get the ADC IT index */
  itmask = (u8)(ADC_IT >> 8);

  /* Clear the selected ADC interrupt pending bits */
  ADCx->SR = ~(u32)itmask;
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
