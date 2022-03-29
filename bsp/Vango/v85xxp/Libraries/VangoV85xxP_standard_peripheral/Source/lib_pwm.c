/**
  ******************************************************************************
  * @file    lib_pwm.c
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   PWM library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_pwm.h"

/**
  * @brief  Initializes PWM timebase.
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
void PWM_BaseInit(PWM_Type *PWMx, PWM_BaseInitType *InitStruct)
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
          |PWM_CTL_TSEL);
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
  /* Initialize the Channel member */ 
  OCInitType->Channel = PWM_CHANNEL_0;
  /* Initialize the OutMode member */  
  OCInitType->OutMode = PWM_OUTMOD_CONST;
  /* Initialize the Period member */  
  OCInitType->Period = 0; 
}

/**
  * @brief  Initializes PWM channel output compare function.
  * @param  PWMx: PWM0~PWM3
            OCInitType:PWM output compare configuration.
                Channel:
                    PWM_CHANNEL_0
                    PWM_CHANNEL_1
                    PWM_CHANNEL_2
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
void PWM_OCInit(PWM_Type *PWMx, PWM_OCInitType *OCInitType)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  assert_parameters(IS_PWM_CHANNEL(OCInitType->Channel));
  assert_parameters(IS_PWM_OUTMODE(OCInitType->OutMode));
  assert_parameters(IS_PWM_CCR(OCInitType->Period));

  tmp = PWMx->CCTL[OCInitType->Channel];
  tmp &= ~(PWM_CCTL_CAP | PWM_CCTL_OUTMOD | PWM_CCTL_CCIFG | PWM_CCTL_COV);
  tmp |= OCInitType->OutMode;
  PWMx->CCTL[OCInitType->Channel] = tmp;
  PWMx->CCR[OCInitType->Channel] = OCInitType->Period;
}

/**
  * @brief  Fills each PWM_ICInitType member with its default value.
  * @param  ICInitType: pointer to a PWM_OCInitType structure which will be initialized.
  * @retval None
  */
void PWM_ICStructInit(PWM_ICInitType *ICInitType)
{
  /*------- Reset PWM output channel init structure parameters values --------*/
  /* Initialize the Channel member */ 
  ICInitType->Channel = PWM_CHANNEL_0;
  /* Initialize the CaptureMode member */  
  ICInitType->CaptureMode = PWM_CM_DISABLE;
}


/**
  * @brief  Initializes PWM channel input capture function.
  * @param  PWMx: PWM0~PWM3
            ICInitType:PWM output compare configuration.
                Channel:
                    PWM_CHANNEL_0
                    PWM_CHANNEL_1
                    PWM_CHANNEL_2
                CaptureMode:
                    PWM_CM_DISABLE
                    PWM_CM_RISING
                    PWM_CM_FALLING
                    PWM_CM_BOTH
  * @retval None
  */
void PWM_ICInit(PWM_Type *PWMx, PWM_ICInitType *ICInitType)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  assert_parameters(IS_PWM_CHANNEL(ICInitType->Channel));
  assert_parameters(IS_PWM_CAPMODE(ICInitType->CaptureMode));

  tmp = PWMx->CCTL[ICInitType->Channel];
  tmp &= ~(PWM_CCTL_CM | PWM_CCTL_CAP | PWM_CCTL_CCIFG | PWM_CCTL_COV);
  tmp |= (ICInitType->CaptureMode | PWM_CCTL_CAP);
  PWMx->CCTL[ICInitType->Channel] = tmp;
}

/**
  * @brief  Enables or disables PWM base interrupt.
  * @param  PWMx: PWM0~PWM3
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void PWM_BaseINTConfig(PWM_Type *PWMx, uint32_t NewState)
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
  * @brief  Gets PWM base interrupt status.
  * @param  PWMx: PWM0~PWM3
  * @retval interrupt status.
  */
uint8_t PWM_GetBaseINTStatus(PWM_Type *PWMx)
{
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  
  if (PWMx->CTL&PWM_CTL_IFG)
    return 1;
  else
    return 0;
}

/**
  * @brief  Clears PWM base interrupt status.
  * @param  PWMx: PWM0~PWM3
  * @retval None.
  */
void PWM_ClearBaseINTStatus(PWM_Type *PWMx)
{
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));

  PWMx->CTL |= PWM_CTL_IFG;
}

/**
  * @brief  Enables or disables channel interrupt.
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
void PWM_ChannelINTConfig(PWM_Type *PWMx, uint32_t Channel, uint32_t NewState)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  assert_parameters(IS_PWM_CHANNEL(Channel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  tmp = PWMx->CCTL[Channel];
  tmp &= ~(PWM_CCTL_CCIE | PWM_CCTL_CCIFG | PWM_CCTL_COV);
  if (NewState == ENABLE)
  {
    tmp |= PWM_CCTL_CCIE;
  }
  PWMx->CCTL[Channel] = tmp;
}

/**
  * @brief  Gets channel interrupt status.
  * @param  PWMx: PWM0~PWM3
            Channel:
                PWM_CHANNEL_0
                PWM_CHANNEL_1 
                PWM_CHANNEL_2 
            IntMask:
                PWM_INT_CCIFG
                PWM_INT_COV  
  * @retval  interrupt status
  */
uint8_t PWM_GetChannelINTStatus(PWM_Type *PWMx, uint32_t Channel, uint32_t IntMask)
{
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  assert_parameters(IS_PWM_CHANNEL(Channel));
  assert_parameters(IS_PWM_INTFLAGR(IntMask));

  if (PWMx->CCTL[Channel] & IntMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clears channel interrupt status.
  * @param  PWMx: PWM0~PWM3
            Channel:
                PWM_CHANNEL_0
                PWM_CHANNEL_1
                PWM_CHANNEL_2
            Int_Mask:
                PWM_INT_CCIFG
                PWM_INT_COV
  * @retval  None
  */
void PWM_ClearChannelINTStatus(PWM_Type *PWMx, uint32_t Channel, uint32_t IntMask)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  assert_parameters(IS_PWM_CHANNEL(Channel));
  assert_parameters(IS_PWM_INTFLAGC(IntMask));

  tmp = PWMx->CCTL[Channel];
  tmp &= ~PWM_INT_Msk;
  tmp |= IntMask;
  PWMx->CCTL[Channel] = tmp;
}

/**
  * @brief  Clears PWM counter.
  * @param  PWMx: PWM0~PWM3
  * @retval None
  */
void PWM_ClearCounter(PWM_Type *PWMx)
{
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));

  PWMx->CTL |= PWM_CTL_CLR;
}

/**
  * @brief  Configures PWM channel CCR value.
  * @param  PWMx: PWM0~PWM3
            Channel:
                PWM_CHANNEL_0
                PWM_CHANNEL_1 
                PWM_CHANNEL_2 
            Period: 0 ~ 0xFFFF
  * @retval None
  */
void PWM_CCRConfig(PWM_Type *PWMx, uint32_t Channel, uint16_t Period)
{
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  assert_parameters(IS_PWM_CHANNEL(Channel));

  PWMx->CCR[Channel] = Period;
}

/**
  * @brief  Configures PWM output line.
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
            OLine: can use the '|' operator
                PWM_OLINE_0
                PWM_OLINE_1 
                PWM_OLINE_2 
                PWM_OLINE_3 
  * @note    PWM Single channel's output waveform can be output on multiple output lines.
  *          Multiple-line configuration can be performed by using the '|' operator.
  *            ex: PWM_OLineConfig(PWM0_OUT0, PWM_OLINE_0 | PWM_OLINE_2)
  *                PWM0 channel0 output by PWM0&PWM2's line.
  * @retval  None
  */
void PWM_OLineConfig(uint32_t OutSelection, uint32_t OLine)
{
  uint32_t tmp;
  uint32_t position = 0;

  /* Check parameters */
  assert_parameters(IS_PWM_OUTLINE(OLine));
  assert_parameters(IS_PWM_OUTSEL(OutSelection));

  tmp = PWM_SEL->O_SEL;
  while ((OLine >> position) != 0UL)
  {
    if ((OLine >> position) & 1UL)
    {
      tmp &= ~(PWM_SEL_O_SEL_SEL0 << (position * 4));
      tmp |= (OutSelection << (position * 4));
    }
    position++;
  }
  PWM_SEL->O_SEL = tmp;
}

/**
  * @brief  Enables disables PWM output function.
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
void PWM_OutputCmd(PWM_Type *PWMx, uint32_t Channel, uint32_t NewState)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));  
  assert_parameters(IS_PWM_CHANNEL(Channel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));  

  tmp = PWMx->CCTL[Channel];
  tmp &= ~(PWM_CCTL_CCIFG | PWM_CCTL_COV);
  if (NewState == ENABLE)
  {
    tmp |= PWM_CCTL_OUTEN;
  }
  else
  {
    tmp &= ~PWM_CCTL_OUTEN;
  }
  PWMx->CCTL[Channel] = tmp;
}

/**
  * @brief  Sets PWM channel output level.
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
void PWM_SetOutLevel(PWM_Type *PWMx, uint32_t Channel, uint32_t Level)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));  
  assert_parameters(IS_PWM_CHANNEL(Channel));
  assert_parameters(IS_PWM_OUTLVL(Level));

  tmp = PWMx->CCTL[Channel];
  tmp &= ~(PWM_CCTL_OUT | PWM_CCTL_CCIFG | PWM_CCTL_COV);
  tmp |= Level;
  PWMx->CCTL[Channel] = tmp;
}

/**
  * @brief  Configures PWM input line.
  * @param  InSelection:
                 PWM1_IN2
                 PWM1_IN1  
                 PWM1_IN0  
                 PWM0_IN2  
                 PWM0_IN1  
                 PWM0_IN0  
                 PWM3_IN2  
                 PWM3_IN1  
                 PWM3_IN0  
                 PWM2_IN2  
                 PWM2_IN1  
                 PWM2_IN0  
            ILine:
                PWM_ILINE_0
                PWM_ILINE_1 
                PWM_ILINE_2 
                PWM_ILINE_3 
  * @retval  None
  */
void PWM_ILineConfig(uint32_t InSelection, uint32_t ILine)
{
  __IO uint32_t *addr;
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_PWM_INLINE(ILine));
  assert_parameters(IS_PWM_INSEL(InSelection));

  addr = &PWM_SEL->I_SEL01 + ((InSelection&0xF00)>>8);
  tmp = *addr;
  tmp &= ~( 3 << (InSelection&0xFF));
  tmp |= (ILine << (InSelection&0xFF));
  *addr = tmp;
}

/**
  * @brief  Gets PWM channel SCCI value.
  * @param  PWMx: PWM0~PWM3
            Channel:
                PWM_CHANNEL_0
                PWM_CHANNEL_1
                PWM_CHANNEL_2
  * @retval  INx¡¯s input value when the TAR is equal to CCRx
  */
uint8_t PWM_GetSCCI(PWM_Type *PWMx, uint32_t Channel)
{
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));
  assert_parameters(IS_PWM_CHANNEL(Channel));
  
  if (PWMx->CCTL[Channel] & PWM_CCTL_SCCI)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Gets PWM channel capture value.
  * @param  PWMx: PWM0~PWM3
            Channel:
                PWM_CHANNEL_0
                PWM_CHANNEL_1 
                PWM_CHANNEL_2 
  * @retval  The value of CCRx.
  */
uint32_t PWM_GetCapture(PWM_Type *PWMx, uint32_t Channel)
{  
  /* Check parameters */
  assert_parameters(IS_PWM_ALL_INSTANCE(PWMx));  
  assert_parameters(IS_PWM_CHANNEL(Channel));
    
  return PWMx->CCR[Channel];
}

/******************* (C) COPYRIGHT Vango Technologies, Inc *****END OF FILE****/
