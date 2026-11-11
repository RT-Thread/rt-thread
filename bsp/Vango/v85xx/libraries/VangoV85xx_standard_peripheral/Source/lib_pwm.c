/**
  ******************************************************************************
  * @file    lib_pwm.c 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   PWM library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_pwm.h"

/**
  * @brief  PWM timebase initialization.
  * @param  PWMx: PWM0~PWM3
            InitStruct:PWM BASE configuration.
                ClockDivision:
                    PWM_CLKDIV_2
                    PWM_CLKDIV_4
                    PWM_CLKDIV_8
                    PWM_CLKDIV_16
                Mode:
                    PWM_MODE_STOP
                    PWM_MODE_UPCOUNT
                    PWM_MODE_CONTINUOUS
                    PWM_MODE_UPDOWN
                ClockSource:
                    PWM_CLKSRC_APB
                    PWM_CLKSRC_APBD128
  * @retval None
  */
void PWM_BaseInit(PWM_TypeDef *PWMx, PWM_BaseInitType *InitStruct)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  assert_parameters(IS_PWM_CLKDIV(InitStruct->ClockDivision));
  assert_parameters(IS_PWM_CNTMODE(InitStruct->Mode));
  assert_parameters(IS_PWM_CLKSRC(InitStruct->ClockSource));
    
  tmp = PWMx->CTL;
  tmp &= ~(PWM_CTL_ID\
          |PWM_CTL_MC\
          |PWM_CTL_TESL);
  tmp |= (InitStruct->ClockDivision\
         |InitStruct->Mode\
         |InitStruct->ClockSource);
  PWMx->CTL = tmp;
}

/**
  * @brief  Fills each PWM_BaseInitType member with its default value.
  * @param  InitStruct: pointer to an PWM_BaseInitType structure which will be initialized.
  * @retval None
  */
void PWM_BaseStructInit(PWM_BaseInitType *InitStruct)
{
  /*------------ Reset PWM base init structure parameters values ------------*/
  /* Initialize the ClockDivision member */
  InitStruct->ClockDivision = PWM_CLKDIV_2;
  /* Initialize the ClockSource member */
  InitStruct->ClockSource = PWM_CLKSRC_APBD128; 
  /* Initialize the Mode member */
  InitStruct->Mode = PWM_MODE_STOP; 
}

/**
  * @brief  Fills each PWM_OCInitType member with its default value.
  * @param  OCInitType: pointer to an PWM_OCInitType structure which will be initialized.
  * @retval None
  */
void PWM_OCStructInit(PWM_OCInitType *OCInitType)
{
  /*------- Reset PWM output channel init structure parameters values --------*/
  /* Initialize the OutMode member */  
  OCInitType->OutMode = PWM_OUTMOD_CONST;
  /* Initialize the Period member */  
  OCInitType->Period = 0; 
}

/**
  * @brief  PWM output compare channel 0.
  * @param  PWMx: PWM0~PWM3
            OCInitType:PWM output compare configuration.
                OutMode:
                    PWM_OUTMOD_CONST
                    PWM_OUTMOD_SET
                    PWM_OUTMOD_TOGGLE_RESET
                    PWM_OUTMOD_SET_RESET
                    PWM_OUTMOD_TOGGLE
                    PWM_OUTMOD_RESET
                    PWM_OUTMOD_TOGGLE_SET
                    PWM_OUTMOD_RESET_SET
                Period: 0 ~ 0xFFFF
  * @retval None
  */
void PWM_OC0Init(PWM_TypeDef *PWMx, PWM_OCInitType *OCInitType)
{
  uint32_t tmp;
                      
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  assert_parameters(IS_PWM_OUTMODE(OCInitType->OutMode));
  assert_parameters(IS_PWM_CCR(OCInitType->Period));
  
  tmp = PWMx->CCTL0;
  tmp &= ~(PWM_CCTL_OUTMOD | PWM_CCTL_CCIGG);
  tmp |= OCInitType->OutMode;
  PWMx->CCTL0 = tmp;
  PWMx->CCR0 = OCInitType->Period;
}

/**
  * @brief  PWM output compare channel 1.
  * @param  PWMx: PWM0~PWM3
            OCInitType:PWM output compare configuration.
                OutMode:
                    PWM_OUTMOD_CONST
                    PWM_OUTMOD_SET
                    PWM_OUTMOD_TOGGLE_RESET
                    PWM_OUTMOD_SET_RESET
                    PWM_OUTMOD_TOGGLE
                    PWM_OUTMOD_RESET
                    PWM_OUTMOD_TOGGLE_SET
                    PWM_OUTMOD_RESET_SET
                Period: 0 ~ 0xFFFF
  * @retval None
  */
void PWM_OC1Init(PWM_TypeDef *PWMx, PWM_OCInitType *OCInitType)
{
  uint32_t tmp;
                      
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  assert_parameters(IS_PWM_OUTMODE(OCInitType->OutMode));
  assert_parameters(IS_PWM_CCR(OCInitType->Period));
  
  tmp = PWMx->CCTL1;
  tmp &= ~(PWM_CCTL_OUTMOD | PWM_CCTL_CCIGG);
  tmp |= OCInitType->OutMode;
  PWMx->CCTL1 = tmp;
  PWMx->CCR1 = OCInitType->Period;
}

/**
  * @brief  PWM output compare channel 2.
  * @param  PWMx: PWM0~PWM3
            OCInitType:PWM output compare configuration.
                OutMode:
                    PWM_OUTMOD_CONST
                    PWM_OUTMOD_SET
                    PWM_OUTMOD_TOGGLE_RESET
                    PWM_OUTMOD_SET_RESET
                    PWM_OUTMOD_TOGGLE
                    PWM_OUTMOD_RESET
                    PWM_OUTMOD_TOGGLE_SET
                    PWM_OUTMOD_RESET_SET
                Period: 0 ~ 0xFFFF
  * @retval None
  */
void PWM_OC2Init(PWM_TypeDef *PWMx, PWM_OCInitType *OCInitType)
{
  uint32_t tmp;
                      
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  assert_parameters(IS_PWM_OUTMODE(OCInitType->OutMode));
  assert_parameters(IS_PWM_CCR(OCInitType->Period));
  
  tmp = PWMx->CCTL2;
  tmp &= ~(PWM_CCTL_OUTMOD | PWM_CCTL_CCIGG);
  tmp |= OCInitType->OutMode;
  PWMx->CCTL2 = tmp;
  PWMx->CCR2 = OCInitType->Period;
}

/**
  * @brief  PWM base interrupt configure.
  * @param  PWMx: PWM0~PWM3
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void PWM_BaseINTConfig(PWM_TypeDef *PWMx, uint32_t NewState)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  
  tmp = PWMx->CTL;
  tmp &= ~(PWM_CTL_IE | PWM_CTL_IFG);
  if (NewState == ENABLE)
  {
    tmp |= PWM_CTL_IE;
  }
  PWMx->CTL = tmp;
}

/**
  * @brief  Get PWM base interrupt status.
  * @param  PWMx: PWM0~PWM3
  * @retval interrupt status.
  */
uint8_t PWM_GetBaseINTStatus(PWM_TypeDef *PWMx)
{
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));  
  
  if (PWMx->CTL&PWM_CTL_IFG)
    return 1;
  else
    return 0;
}

/**
  * @brief  Clear PWM base interrupt status.
  * @param  PWMx: PWM0~PWM3
  * @retval None.
  */
void PWM_ClearBaseINTStatus(PWM_TypeDef *PWMx)
{
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  
  PWMx->CTL |= PWM_CTL_IFG;
}

/**
  * @brief  channel interrupt configure.
  * @param  PWMx: PWM0~PWM3
            Channel:
                PWM_CHANNEL_0
                PWM_CHANNEL_1 
                PWM_CHANNEL_2 
            NewState:
                ENABLE
                DISABLE
  * @retval  None
  */
void PWM_ChannelINTConfig(PWM_TypeDef *PWMx, uint32_t Channel, uint32_t NewState)
{
  __IO uint32_t *addr;
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));  
  assert_parameters(IS_PWM_CHANNEL(Channel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  addr = &PWMx->CCTL0 + Channel;
  tmp = *addr;
  tmp &= ~(PWM_CCTL_CCIE | PWM_CCTL_CCIGG);
  if (NewState == ENABLE)
  {
    tmp |= PWM_CCTL_CCIE;
  }
  *addr = tmp;
}

/**
  * @brief  Get channel interrupt status.
  * @param  PWMx: PWM0~PWM3
            Channel:
                PWM_CHANNEL_0
                PWM_CHANNEL_1 
                PWM_CHANNEL_2                  
  * @retval  interrupt status
  */
uint8_t PWM_GetChannelINTStatus(PWM_TypeDef *PWMx, uint32_t Channel)
{
  __IO uint32_t *addr;
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));  
  assert_parameters(IS_PWM_CHANNEL(Channel));
    
  addr = &PWMx->CCTL0 + Channel;
  tmp = *addr;
  if (tmp & PWM_CCTL_CCIGG)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clear channel interrupt status.
  * @param  PWMx: PWM0~PWM3
            Channel:
                PWM_CHANNEL_0
                PWM_CHANNEL_1 
                PWM_CHANNEL_2 
  * @retval  None
  */
void PWM_ClearChannelINTStatus(PWM_TypeDef *PWMx, uint32_t Channel)
{
  __IO uint32_t *addr;
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));  
  assert_parameters(IS_PWM_CHANNEL(Channel));
    
  addr = &PWMx->CCTL0 + Channel;
    
  tmp = *addr;
  tmp &= ~PWM_CCTL_CCIGG;
  tmp |= PWM_CCTL_CCIGG;
  *addr = tmp;
}

/**
  * @brief  PWM clear counter.
  * @param  PWMx: PWM0~PWM3
  * @retval None
  */
void PWM_ClearCounter(PWM_TypeDef *PWMx)
{
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx)); 
  
  PWMx->CTL |= PWM_CTL_CLR;
}

/**
  * @brief  Configure PWMx channelx's CCR value.
  * @param  PWMx: PWM0~PWM3
            Channel:
                PWM_CHANNEL_0
                PWM_CHANNEL_1 
                PWM_CHANNEL_2 
            Period: 0 ~ 0xFFFF
  * @retval None
  */
void PWM_CCRConfig(PWM_TypeDef *PWMx, uint32_t Channel, uint16_t Period)
{
  __IO uint32_t *addr;
  
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));  
  assert_parameters(IS_PWM_CHANNEL(Channel));
  
  addr = &PWMx->CCR0 + Channel;
  *addr = Period;
}

/**
  * @brief  pwm output line selection.
  * @param  OutSelection:
                PWM0_OUT0
                PWM0_OUT1 
                PWM0_OUT2 
                PWM1_OUT0 
                PWM1_OUT1 
                PWM1_OUT2 
                PWM2_OUT0 
                PWM2_OUT1 
                PWM2_OUT2 
                PWM3_OUT0 
                PWM3_OUT1 
                PWM3_OUT2 
            OLine: can use the ¡®|¡¯ operator
                PWM_OLINE_0
                PWM_OLINE_1 
                PWM_OLINE_2 
                PWM_OLINE_3 
  * @note    PWM Single channel's output waveform can be output on multiple output lines.
  *          Multiple-line configuration can be performed by using the ¡®|¡¯ operator.
  *            ex: PWM_OLineConfig(PWM0_OUT0, PWM_OLINE_0 | PWM_OLINE_2)
  *                PWM0 channel0 output by PWM0&PWM2's lien.
  * @retval  None
  */
void PWM_OLineConfig(uint32_t OutSelection, uint32_t OLine)
{
  uint32_t tmp;
  uint32_t position = 0;

  /* Check parameters */
  assert_parameters(IS_PWM_OUTLINE(OLine));
  assert_parameters(IS_PWM_OUTSEL(OutSelection));   
  
  tmp = PWMMUX->OSEL;
  while ((OLine >> position) != 0UL)
  {
    if ((OLine >> position) & 1UL)
    {
      tmp &= ~(PWM_O_SEL_O_SEL0 << (position * 4));
      tmp |= (OutSelection << (position * 4));
    }
    position++;
  }
  PWMMUX->OSEL = tmp;
}

/**
  * @brief  PWM output enable.
  * @param  PWMx: PWM0~PWM3
            Channel:
                PWM_CHANNEL_0
                PWM_CHANNEL_1
                PWM_CHANNEL_2
            NewState:
                ENABLE
                DISABLE
  * @retval  None
  */
void PWM_OutputCmd(PWM_TypeDef *PWMx, uint32_t Channel, uint32_t NewState)
{
  __IO uint32_t *addr;
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));  
  assert_parameters(IS_PWM_CHANNEL(Channel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));  
    
  addr = &PWMx->CCTL0 + Channel;
  tmp = *addr;
  tmp &= ~PWM_CCTL_CCIGG;
  if (NewState == ENABLE)
    tmp |= PWM_CCTL_OUTEN;
  else
    tmp &= ~PWM_CCTL_OUTEN;
  *addr = tmp;
}

/**
  * @brief  Set channel output level.
  * @param  PWMx: PWM0~PWM3
            Channel:
                PWM_CHANNEL_0
                PWM_CHANNEL_1
                PWM_CHANNEL_2
            Level:
                PWM_LEVEL_HIGH
                PWM_LEVEL_LOW
  * @retval  None
  */
void PWM_SetOutLevel(PWM_TypeDef *PWMx, uint32_t Channel, uint32_t Level)
{
  __IO uint32_t *addr;
  uint32_t tmp;
    
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));  
  assert_parameters(IS_PWM_CHANNEL(Channel));
  assert_parameters(IS_PWM_OUTLVL(Level));
  
  addr = &PWMx->CCTL0 + Channel;
  tmp = *addr;
  tmp &= ~(PWM_CCTL_OUT | PWM_CCTL_CCIGG);
  tmp |= Level;
  *addr = tmp;
}

/*********************************** END OF FILE ******************************/
