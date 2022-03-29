/**
  ******************************************************************************
  * @file    lib_adc.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   ADC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_adc.h"

#define ANA_INTEN_ADCMsk            (0x3FC003U)
#define ANA_INTSTS_ADCMsk           (0x3FC003U)
#define ANA_ADCCTRL0_RSTValue       (0x300000U)
#define ANA_ADCCTRL1_RSTValue       (0xC2U)
#define ANA_ADCCTRL2_RSTValue       (0x8014U)
#define ANA_ADCDATATHD1_0_RSTValue  (0U)
#define ANA_ADCDATATHD3_2_RSTValue  (0U)
#define ANA_ADCDATATHD_CH_RSTValue  (0U)
#define RTC_ADCUCALK_RSTValue       (0x599A599AU)
#define RTC_ADCMACTL_RSTValue       (0x78000000U)
#define RTC_ADCDTCTL_RSTValue       (0x80000000)

#define ADC_SYNC_WR(); {__NOP(); __NOP(); __NOP(); __NOP();}
/**
  * @brief  Initializes ADC peripheral registers to their default reset values.
  * @note   1. Disable ADC
            2. Disable resistor division.
            3. Disable ADC auto/manual done interrupt.
            4. The ADC correlation (register) is written to the default value.
  * @param  None
  * @retval None
  */
void ADC_DeInit(void)
{
  uint32_t tmp[3];
  
  if((ANA->ADCSTATE&0x07)!=0)
  {
    ADC_Cmd(DISABLE);
  }

  /* 6.5MHz clock. */
  ANA->REG0 &= ~ANA_REG0_ADCFRQSEL;
  /* ADC mode */
  ANA->REG1 &= ~ANA_REG1_ADCMODESEL;
  /* Power up VINBUF and REFBUF. */
  ANA->REG11 &= ~(ANA_REG11_REFBUFPD|ANA_REG11_VINBUFPD);
  /* Power down ADC */
  ANA->ADCCTRL2 &= ~ANA_ADCCTRL2_ADC_EN;
  /* Disable interrupt, Clear interrupt flag */
  ANA->INTEN &= ~ANA_INTEN_ADCMsk;
  ANA->INTSTS = ANA_INTSTS_ADCMsk;
  while (ANA->ADCCTRL0 & ANA_ADCCTRL0_MTRIG);
  ANA->ADCCTRL0 = ANA_ADCCTRL0_RSTValue;
  while (ANA->ADCCTRL0 & ANA_ADCCTRL0_MTRIG);
  ANA->ADCCTRL1 = ANA_ADCCTRL1_RSTValue;
  ANA->ADCCTRL2 = ANA_ADCCTRL2_RSTValue|ANA_ADCCTRL2_CONV_ERR_CLR|ANA_ADCCTRL2_CAL_ERR_CLR;
  
  ANA->ADCDATATHD1_0= ANA_ADCDATATHD1_0_RSTValue;
  ANA->ADCDATATHD3_2 = ANA_ADCDATATHD3_2_RSTValue;
  ANA->ADCDATATHD_CH = ANA_ADCDATATHD_CH_RSTValue;
  tmp[0] = RTC_ADCUCALK_RSTValue;
  tmp[1] = RTC_ADCMACTL_RSTValue;
  tmp[2] = RTC_ADCDTCTL_RSTValue;
  RTC_WriteRegisters((uint32_t)&RTC->ADCUCALK, tmp, 3);
  
  ANA->ADCCTRL2 = ANA_ADCCTRL2_RSTValue;
}

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @param  ADC_InitStruct: pointer to an ADC_InitType structure which will be initialized.
  * @retval None
  */
void ADC_StructInit(ADC_InitType* ADC_InitStruct)
{
  /*------ Reset ADC init structure parameters values ------*/
  ADC_InitStruct->Mode = ADC_MODE_DC;
  ADC_InitStruct->ClockSource = ADC_CLKSRC_RCH;
  ADC_InitStruct->ClockFrq = ADC_CLKFRQ_HIGH;
  ADC_InitStruct->SkipSample = ADC_SKIP_0;
  ADC_InitStruct->AverageSample = ADC_AVERAGE_2;
  ADC_InitStruct->TriggerSource = ADC_TRIGSOURCE_OFF;
  ADC_InitStruct->Channel = ADC_CHANNEL_GND0;
  ADC_InitStruct->ResDivEnable = 0;
  ADC_InitStruct->AverageEnable = 0;
}

/**
  * @brief  Initializes ADC.
  * @param  ADC_InitStruct: pointer to an ADC_InitType structure which will be initialized.
                Mode:
                     ADC_MODE_DC          (Not include ADC_CHANNEL_TEMP)
                     ADC_MODE_AC          (Only ADC_CHANNEL_CHx be valid)
                     ADC_MODE_TEMP        (Only ADC_CHANNEL_TEMP be valid)
                ClockSource: \n
                     ADC_CLKSRC_RCH \n
                     ADC_CLKSRC_PLLL \n
                ClockFrq: \n
                     ADC_CLKFRQ_HIGH \n
                     ADC_CLKFRQ_LOW \n
                SkipSample: \n
                     ADC_SKIP_0 \n
                     ADC_SKIP_4 \n
                     ADC_SKIP_8 \n
                     ADC_SKIP_12 \n
                AverageSample: \n
                     ADC_AVERAGE_2 \n
                     ADC_AVERAGE_4 \n
                     ADC_AVERAGE_8 \n
                     ADC_AVERAGE_16 \n
                     ADC_AVERAGE_32 \n
                     ADC_AVERAGE_64 \n
                TriggerSource: \n
                     ADC_TRIGSOURCE_OFF \n
                     ADC_TRIGSOURCE_ITVSITV \n
                     ADC_TRIGSOURCE_WKUSEC \n
                     ADC_TRIGSOURCE_ALARM \n
                     ADC_TRIGSOURCE_TMR0 \n
                     ADC_TRIGSOURCE_TMR1 \n
                     ADC_TRIGSOURCE_TMR2 \n
                     ADC_TRIGSOURCE_TMR3 \n
                Channel:
                ResDivEnable:   (also can be ADC_CHANNEL_NONE)
                AverageEnable:  (also can be ADC_CHANNEL_NONE)
                     ADC_CHANNEL_GND0
                     ADC_CHANNEL_BAT1
                     ADC_CHANNEL_BATRTC
                     ADC_CHANNEL_CH3
                     ADC_CHANNEL_CH4
                     ADC_CHANNEL_CH5
                     ADC_CHANNEL_CH6
                     ADC_CHANNEL_CH7
                     ADC_CHANNEL_CH8
                     ADC_CHANNEL_CH9
                     ADC_CHANNEL_TEMP
                     ADC_CHANNEL_CH11
                     ADC_CHANNEL_DVCC
                     ADC_CHANNEL_GND13
                     ADC_CHANNEL_GND14
                     ADC_CHANNEL_GND15
                     ADC_CHANNEL_DC_ALL
                     ADC_CHANNEL_AC_ALL
  * @retval None
  */
void ADC_Init(ADC_InitType *ADC_InitStruct)
{
  uint32_t tmp_anareg0, tmp_anareg1, tmp_anareg3, tmp_anareg11;
  uint32_t tmp_adcctrl0, tmp_adcctrl1, tmp_adcctrl2;
  uint32_t tmp_rtcadcmactl;

  /* Check parameters */
  assert_parameters(IS_ADC_MODE(ADC_InitStruct->Mode));
  assert_parameters(IS_ADC_CLKSRC(ADC_InitStruct->ClockSource));
  assert_parameters(IS_ADC_CLKFRQ(ADC_InitStruct->ClockFrq));
  assert_parameters(IS_ADC_SKIP(ADC_InitStruct->SkipSample));
  assert_parameters(IS_ADC_AVERAG(ADC_InitStruct->AverageSample));
  assert_parameters(IS_ADC_TRIGSOURCE(ADC_InitStruct->TriggerSource));

  while (ANA->ADCCTRL0 & ANA_ADCCTRL0_MTRIG); 
  ANA->ADCCTRL2 &= ~ANA_ADCCTRL2_ADC_EN;
  
  tmp_adcctrl0 = ANA->ADCCTRL0;
  tmp_adcctrl1 = ANA->ADCCTRL1;
  tmp_adcctrl2 = ANA->ADCCTRL2;
  tmp_anareg0 = ANA->REG0;
  tmp_anareg1 = ANA->REG1;
  tmp_anareg3 = ANA->REG3;
  tmp_anareg11 = 0;
  tmp_rtcadcmactl = RTC->ADCMACTL;
  
  /* Configure clock source and trigger source */
  tmp_adcctrl0 &= ~(ANA_ADCCTRL0_AEN | ANA_ADCCTRL0_CLKSRCSEL);
  tmp_adcctrl0 |= (ADC_InitStruct->TriggerSource | ADC_InitStruct->ClockSource);

  /* Configure ClockFrq */
  if (ADC_InitStruct->ClockFrq == ADC_CLKFRQ_HIGH)
  {
    tmp_anareg0 &= ~ANA_REG0_ADCFRQSEL;
    tmp_adcctrl2 &= ~ANA_ADCCTRL2_ADCCR;
  }
  else
  {
    tmp_anareg0 |= ANA_REG0_ADCFRQSEL;
    tmp_adcctrl2 |= ANA_ADCCTRL2_ADCCR;
  }

  /* Configure skip samples and  average samples */
  tmp_rtcadcmactl &= ~(RTC_ADCMACTL_SKIP_SAMPLE | RTC_ADCMACTL_AVERAGE_SAMPLE);
  tmp_rtcadcmactl |= (ADC_InitStruct->SkipSample | ADC_InitStruct->AverageSample);

  /* Mode: DC */
  if (ADC_InitStruct->Mode == ADC_MODE_DC)
  {
    /* Check parameters */
    assert_parameters(IS_ADC_CHANNEL_DC(ADC_InitStruct->Channel));
    assert_parameters(IS_ADC_CHANNEL_EN_DC(ADC_InitStruct->AverageEnable));
    assert_parameters(IS_ADC_CHANNEL_EN_DC(ADC_InitStruct->ResDivEnable));

    /* Enable or disable Channels */
    tmp_adcctrl2 &= ~ANA_ADCCTRL2_SCAN_CHx;
    tmp_adcctrl2 |= (ADC_InitStruct->Channel << ADC_CHANNEL_SHIFT);
    /* Enable or disable average  */
    tmp_rtcadcmactl &= ~RTC_ADCMACTL_AVERAGE_CHx;
    tmp_rtcadcmactl |= (ADC_InitStruct->AverageEnable << ADC_AVERAGECH_SHIFT);
    /* Enable or disable RESDIV */
    tmp_adcctrl1 &= ~ANA_ADCCTRL1_RESDIV_CHx;
    tmp_adcctrl1 |= (ADC_InitStruct->ResDivEnable << ADC_RESDIVCH_SHIFT);
    /* Others */
    tmp_anareg1 &= ~ANA_REG1_ADCMODESEL;
  }
  /* Mode: AC */  
  else if (ADC_InitStruct->Mode == ADC_MODE_AC)
  {
    /* Check parameters */
    assert_parameters(IS_ADC_CHANNEL_AC(ADC_InitStruct->Channel));
    assert_parameters(IS_ADC_CHANNEL_EN_AC(ADC_InitStruct->AverageEnable));
    
    /* Enable or disable Channels */
    tmp_adcctrl2 &= ~ANA_ADCCTRL2_SCAN_CHx;
    tmp_adcctrl2 |= (ADC_InitStruct->Channel << ADC_CHANNEL_SHIFT);
    /* Enable or disable average  */
    tmp_rtcadcmactl &= ~RTC_ADCMACTL_AVERAGE_CHx;
    tmp_rtcadcmactl |= (ADC_InitStruct->AverageEnable << ADC_AVERAGECH_SHIFT);
    /* Enable or disable RESDIV */
    tmp_adcctrl1 &= ~ANA_ADCCTRL1_RESDIV_CHx;
    tmp_adcctrl1 |= (ADC_InitStruct->Channel << ADC_RESDIVCH_SHIFT);
    /* Others */
    tmp_anareg1 |= ANA_REG1_ADCMODESEL;    
  }
  /* Mode: TEMP */
  else
  {
    /* Check parameters */
    assert_parameters(IS_ADC_CHANNEL_TEMP(ADC_InitStruct->Channel)); 

    /* Enable ADC_CHANNEL_TEMP */
    tmp_adcctrl2 &= ~ANA_ADCCTRL2_SCAN_CHx;
    tmp_adcctrl2 |= (ADC_CHANNEL_TEMP << ADC_CHANNEL_SHIFT);
    /* Enable  average  */
    tmp_rtcadcmactl &= ~RTC_ADCMACTL_AVERAGE_CHx;
    tmp_rtcadcmactl |= (ADC_CHANNEL_TEMP << ADC_AVERAGECH_SHIFT);
    /* Disable RESDIV */
    tmp_adcctrl1 &= ~ANA_ADCCTRL1_RESDIV_CHx;
    /* Others */
    tmp_anareg1 &= ~ANA_REG1_ADCMODESEL;
    if(ADC_InitStruct->ClockFrq == ADC_CLKFRQ_LOW)
    {
      /* It can improve the accuracy of temperature measurement */
      tmp_anareg11 |= (ANA_REG11_VINBUFPD | ANA_REG11_REFBUFPD); 
    }
  }

  ANA->ADCCTRL0 = tmp_adcctrl0&(~ANA_ADCCTRL0_MTRIG);
  ANA->ADCCTRL1 = tmp_adcctrl1;
  ANA->ADCCTRL2 = tmp_adcctrl2;
  ANA->REG0 = tmp_anareg0;
  ANA->REG1 = tmp_anareg1;
  ANA->REG3 = tmp_anareg3;
  ANA->REG11 = tmp_anareg11;  
  RTC_WriteRegisters((uint32_t)&RTC->ADCMACTL, &tmp_rtcadcmactl, 1);
}

/**
  * @brief  Fills each ADCTHD_InitType member with its default value.
  * @param  ADC_THDStruct: pointer to an ADC_THDStruct structure which will be initialized.
  * @retval None
  */
void ADC_THDStructInit(ADCTHD_InitType* ADC_THDStruct)
{
  ADC_THDStruct->THDChannel = ADC_THDCHANNEL0;
  ADC_THDStruct->UpperTHD = 0x0000;
  ADC_THDStruct->LowerTHD = 0x0000;
  ADC_THDStruct->TriggerSel = ADC_THDSEL_HIGH;
  ADC_THDStruct->THDSource = ADC_CHANNEL_GND0;
}

/**
  * @brief  Initializes ADC threshold.
  * @param  ADC_THDStruct:
  *             THDChannel:
  *                 ADC_THDCHANNEL0
  *                 ADC_THDCHANNEL1
  *                 ADC_THDCHANNEL2
  *                 ADC_THDCHANNEL3
  *             UpperTHD:
  *                 0~0xFF
  *             LowerTHD:
  *                 0~0xFF
  *             TriggerSel:
  *                 ADC_THDSEL_HIGH
  *                 ADC_THDSEL_RISING
  *                 ADC_THDSEL_FALLING
  *                 ADC_THDSEL_BOTH
  *             THDSource:
  *                ADC_CHANNEL_GND0
  *                ADC_CHANNEL_BAT1
  *                ADC_CHANNEL_BATRTC
  *                ADC_CHANNEL_CH3
  *                ADC_CHANNEL_CH4
  *                ADC_CHANNEL_CH5
  *                ADC_CHANNEL_CH6
  *                ADC_CHANNEL_CH7
  *                ADC_CHANNEL_CH8
  *                ADC_CHANNEL_CH9
  *                ADC_CHANNEL_TEMP
  *                ADC_CHANNEL_CH11
  *                ADC_CHANNEL_DVCC
  *                ADC_CHANNEL_GND13
  *                ADC_CHANNEL_GND14
  *                ADC_CHANNEL_GND15
  * @retval None
  */
void ADC_THDInit(ADCTHD_InitType* ADC_THDStruct)
{
  uint32_t tmp = 0;
  uint32_t position = 0x00U;
  uint32_t currentch = 0x00U;

  /* Check parameters */
  assert_parameters(IS_ADC_THDCHANNEL(ADC_THDStruct->THDChannel));
  assert_parameters(IS_ADC_THDSEL(ADC_THDStruct->TriggerSel));
  assert_parameters(IS_ADC_CHANNEL_GETDATA(ADC_THDStruct->THDSource));
  
  while ((ADC_THDStruct->THDSource >> position) != 0U)
  {
    /* Get current ch position */
    currentch = ADC_THDStruct->THDSource & (0x01U << position);
    
    if (currentch)
    {
      break;
    }
    position++;
  }

  if ((ADC_THDStruct->THDChannel == ADC_THDCHANNEL0) || (ADC_THDStruct->THDChannel == ADC_THDCHANNEL1))
  {
    ANA->ADCDATATHD1_0 &= ~((ANA_ADCDATATHD1_0_LOWER_THD0|ANA_ADCDATATHD1_0_UPPER_THD0) << (16*ADC_THDStruct->THDChannel));
    ANA->ADCDATATHD1_0 |= (((ADC_THDStruct->UpperTHD<<8)|ADC_THDStruct->LowerTHD) << (16*ADC_THDStruct->THDChannel));
  }
  else
  {
    ANA->ADCDATATHD3_2 &= ~((ANA_ADCDATATHD3_2_LOWER_THD2|ANA_ADCDATATHD3_2_UPPER_THD2) << (16*(ADC_THDStruct->THDChannel - 2)));
    ANA->ADCDATATHD3_2 |= (((ADC_THDStruct->UpperTHD<<8)|ADC_THDStruct->LowerTHD) << (16*(ADC_THDStruct->THDChannel - 2)));
  }

  tmp = ANA->ADCDATATHD_CH;
  tmp &= ~(ANA_ADCDATATHD_CH_THD0_SEL << (ADC_THDStruct->THDChannel*2));
  tmp |= (ADC_THDStruct->TriggerSel << (ADC_THDStruct->THDChannel*2 + ANA_ADCDATATHD_CH_THD0_SEL_Pos));

  tmp &= ~(ANA_ADCDATATHD_CH_THD0_CH << (ADC_THDStruct->THDChannel*4));
  tmp |= (position << (ADC_THDStruct->THDChannel*4+ANA_ADCDATATHD_CH_THD0_CH_Pos));

  ANA->ADCDATATHD_CH = tmp;
}

/**
  * @brief  Starts a ADC calibration (ADC calibration is implemented when DPORST or ADC RESET happened).
  * @param  None
  * @retval None
  */
void ADC_Calibration(void)
{
  volatile uint32_t i;
  
//  if ((ANA->ADCCTRL2 & ANA_ADCCTRL2_RTC_CAL_DONE) && (ANA->ADCDOS != 0))
//    return;
  //Disable ADC
ADCCALSTART:
  ANA->ADCCTRL2 &= ~ANA_ADCCTRL2_ADC_EN;
  ANA->ADCCTRL2 |= ANA_ADCCTRL2_CAL_ERR_CLR;
  ADC_SYNC_WR();
  //Set 6.5M ADC clock 
  ANA->REG0 &= ~ANA_REG0_ADCFRQSEL;
  ADC_SYNC_WR();
  while (ANA->ADCCTRL0 & ANA_ADCCTRL0_MTRIG);
  //ADC STOP
  ANA->ADCCTRL0 = ANA_ADCCTRL0_RSTValue|ANA_ADCCTRL0_STOP;
  ADC_SYNC_WR();
  ANA->ADCCTRL0 = ANA_ADCCTRL0_RSTValue;
  ADC_SYNC_WR();
  //Reset ADC
  ANA->ADCCTRL2 = ANA_ADCCTRL2_RSTValue | ANA_ADCCTRL2_RESET;
  ADC_SYNC_WR();
  ANA->ADCCTRL2 = ANA_ADCCTRL2_RSTValue;
  ADC_SYNC_WR();
  //Enable ADC TRG_CAL
  ANA->ADCCTRL2 |= ANA_ADCCTRL2_ADC_EN_TRG_CAL;
  ADC_SYNC_WR();
  ANA->ADCCTRL2 |= ANA_ADCCTRL2_ADC_EN;
  ADC_SYNC_WR();
  /* while loop until ADC calibration is done */
  ADC_SYNC_WR();
  while (!(ANA->ADCCTRL2 & ANA_ADCCTRL2_RTC_CAL_DONE))
  {
  }
  if(ANA->ADCCTRL2 & ANA_ADCCTRL2_CAL_ERR)
  {
    goto ADCCALSTART;
  }
  ANA->ADCCTRL2 &= ~ANA_ADCCTRL2_ADC_EN_TRG_CAL;
  ADC_SYNC_WR();
  ANA->ADCCTRL2 &= ~ANA_ADCCTRL2_ADC_EN;
  ADC_SYNC_WR();
  
}

/**
  * @brief  Calculates ADC value via ADC original data.
  * @param  [in]Mode:
                   ADC_3V_ADCCHx_NODIV
                   ADC_3V_ADCCHx_RESDIV
                   ADC_3V_BAT1_RESDIV
                   ADC_3V_BATRTC_RESDIV
                   ADC_5V_ADCCHx_NODIV
                   ADC_5V_ADCCHx_RESDIV
                   ADC_5V_BAT1_RESDIV
                   ADC_5V_BATRTC_RESDIV
                   ADC_TEMP
  * @param  [in]adc_data: The ADC original data
  * @param  [out]value: The pointer of value calculated by this function
  * @retval 1  NVR checksum error.
            0  Function successed.
  */
uint32_t ADC_CalculateValue(uint32_t Mode, int16_t adc_data, int16_t *value)
{
  NVR_ADCVOLPARA parameter;
  NVR_TempParams TempParams;

  /* Check parameters */
  assert_parameters(IS_ADCVOL_MODE(Mode));

  if (Mode == ADC_TEMP)
  {
    if (NVR_GetTempParameters(&TempParams))
    {
      return 1;
    }
    else
    {
        /* Calculate temperature */
      *value = ((TempParams.RTCTempP0 * ((adc_data*adc_data)>>16)) + TempParams.RTCTempP1*adc_data + TempParams.RTCTempP2) >> 8;
    }
  }
  else
  {
    if (NVR_GetVoltageParameters(Mode, &parameter))
    {
      return 1;
    }
    else
    {
      *value = (int16_t)((parameter.aParameter*(float)adc_data + parameter.bParameter) + parameter.OffsetParameter);
    }
  }

  return 0;
}

/**
  * @brief  Enables or disables ADC.
  * @note   None
  * @param  NewState
                ENABLE
                DISABLE
  * @retval None
  */
void ADC_Cmd(uint32_t NewState)
{
  __IO uint32_t dly = 400UL;

  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  while (ANA->ADCCTRL0 & ANA_ADCCTRL0_MTRIG);
  if (NewState == DISABLE)
  {
    if(ANA->ADCSTATE & ANA_ADCSTATE_ADCSTATE)
    {
      ANA->ADCCTRL0 |= ANA_ADCCTRL0_STOP;
      if ((MISC2->CLKSEL&MISC2_CLKSEL_CLKSEL) == MISC2_CLKSEL_CLKSEL_RTCCLK)
      {
        __NOP();
        __NOP();
      }
      else
      {
        while (dly--)
          __NOP();
      }
      ANA->ADCCTRL0 &= ~ANA_ADCCTRL0_STOP;
    }
    ANA->ADCCTRL2 &= ~ANA_ADCCTRL2_ADC_EN;
  }
  else
  {
    ANA->ADCCTRL0 &= ~ANA_ADCCTRL0_STOP;
    ANA->ADCCTRL2 |= ANA_ADCCTRL2_ADC_EN;

    if ((MISC2->CLKSEL&MISC2_CLKSEL_CLKSEL) == MISC2_CLKSEL_CLKSEL_RTCCLK)
    {
      __NOP();
      __NOP();
    }
    else
    {
      while (dly--)
        __NOP();
    }
    /* Start Manual ADC conversion */
    ADC_StartManual();
    /* Waiting Manual ADC conversion done */
    ADC_WaitForManual();   
  }
}

/**
  * @brief  Enables or disables ADC lower threshold detect function.
  * @note   None
  * @param  THDChannel:
                ADC_THDCHANNEL0~ADC_THDCHANNEL3
            NewState
                ENABLE
                DISABLE
  * @retval None
  */
void ADC_LowerTHDCmd(uint32_t THDChannel,uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_ADC_THDCHANNEL(THDChannel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState == DISABLE)
  {
    ANA->ADCCTRL1 &= ~(ANA_ADCCTRL1_LOWER_THD0_EN << (THDChannel*2));
  }
  else
  {
    ANA->ADCCTRL1 |= (ANA_ADCCTRL1_LOWER_THD0_EN << (THDChannel*2));
  }
}

/**
  * @brief  Enables or disables ADC upper threshold detect function.
  * @note   None
  * @param  THDChannel:
                IS_ADC_THDCHANNEL0~IS_ADC_THDCHANNEL3
            NewState
                ENABLE
                DISABLE
  * @retval None
  */
void ADC_UpperTHDCmd(uint32_t THDChannel,uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_ADC_THDCHANNEL(THDChannel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState == DISABLE)
  {
    ANA->ADCCTRL1 &= ~(ANA_ADCCTRL1_UPPER_THD0_EN << (THDChannel*2));
  }
  else
  {
    ANA->ADCCTRL1 |= (ANA_ADCCTRL1_UPPER_THD0_EN << (THDChannel*2));
  }
}

/**
  * @brief  Starts a ADC manual-trigger.
  * @param  None
  * @retval None
  */
void ADC_StartManual(void)
{
  while (ANA->ADCCTRL0 & ANA_ADCCTRL0_MTRIG);
  ANA->ADCCTRL0 |= ANA_ADCCTRL0_MTRIG;
}

/**
  * @brief  Waits until the last Manual ADC conversion done.
  * @param  None
  * @retval None
  */
void ADC_WaitForManual(void)
{
  while (ANA->ADCCTRL0 & ANA_ADCCTRL0_MTRIG)
  {
  }
}

/**
  * @brief  Gets ADC vonversion value.
  * @param  Channel:
  *              ADC_CHANNEL_GND0
  *              ADC_CHANNEL_BAT1
  *              ADC_CHANNEL_BATRTC
  *              ADC_CHANNEL_CH3
  *              ADC_CHANNEL_CH4
  *              ADC_CHANNEL_CH5
  *              ADC_CHANNEL_CH6
  *              ADC_CHANNEL_CH7
  *              ADC_CHANNEL_CH8
  *              ADC_CHANNEL_CH9
  *              ADC_CHANNEL_TEMP
  *              ADC_CHANNEL_CH11
  *              ADC_CHANNEL_DVCC
  *              ADC_CHANNEL_GND13
  *              ADC_CHANNEL_GND14
  *              ADC_CHANNEL_GND15
  * @retval ADC conversion value.
  */
int16_t ADC_GetADCConversionValue(uint32_t Channel)
{
  uint32_t position = 0x0000UL;
  uint32_t chcurrent = 0x0000UL;
  
  /* Check parameters */
  assert_parameters(IS_ADC_CHANNEL_GETDATA(Channel));

  while ((Channel >> position) != 0UL)
  {
    chcurrent = Channel & (0x01U << position);
    if (chcurrent)
      break;
    position++;
  }
  return (ANA->ADCDATA[position]);
}

/**
  * @brief  Enables or disables ADC interrupt.
  * @param  INTMask: can use the '|' operator
                ADC_INT_UPPER_TH3
                ADC_INT_LOWER_TH3
                ADC_INT_UPPER_TH2
                ADC_INT_LOWER_TH2
                ADC_INT_UPPER_TH1
                ADC_INT_LOWER_TH1
                ADC_INT_UPPER_TH0
                ADC_INT_LOWER_TH0
                ADC_INT_AUTODONE
                ADC_INT_MANUALDONE
            NewState
                ENABLE
                DISABLE
  * @retval None
  */
void ADC_INTConfig(uint32_t INTMask, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  assert_parameters(IS_ADC_INT(INTMask));

  if (NewState == ENABLE)
    ANA->INTEN |= INTMask;
  else
    ANA->INTEN &= ~INTMask;
}

/**
  * @brief  Clears ADC interrupt status.
  * @param  INTMask: can use the '|' operator
                ADC_INTSTS_UPPER_TH3
                ADC_INTSTS_LOWER_TH3
                ADC_INTSTS_UPPER_TH2
                ADC_INTSTS_LOWER_TH2
                ADC_INTSTS_UPPER_TH1
                ADC_INTSTS_LOWER_TH1
                ADC_INTSTS_UPPER_TH0
                ADC_INTSTS_LOWER_TH0
                ADC_INTSTS_AUTODONE
                ADC_INTSTS_MANUALDONE 
  * @retval  None
  */
void ADC_ClearINTStatus(uint32_t INTMask)
{
  /* Parameter check */
  assert_parameters(IS_ADC_INTFLAGC(INTMask));
  
  ANA->INTSTS = INTMask;
}

/**
  * @brief  Gets ADC interrupt status.
  * @param  INTMask: 
                ADC_INTSTS_UPPER_TH3
                ADC_INTSTS_LOWER_TH3
                ADC_INTSTS_UPPER_TH2
                ADC_INTSTS_LOWER_TH2
                ADC_INTSTS_UPPER_TH1
                ADC_INTSTS_LOWER_TH1
                ADC_INTSTS_UPPER_TH0
                ADC_INTSTS_LOWER_TH0
                ADC_INTSTS_AUTODONE
                ADC_INTSTS_MANUALDONE 
  * @retval  1: status set
             0: status reset.
  */
uint8_t ADC_GetINTStatus(uint32_t INTMask)
{
  /* Parameter check */
  assert_parameters(IS_ADC_INTFLAGR(INTMask));
  
  if (ANA->INTSTS & INTMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Gets ADC flag
  * @param  FlagMask
                ADC_FLAG_CONV_ERR
                ADC_FLAG_CAL_ERR
                ADC_FLAG_CAL_DONE
                ADC_FLAG_BUSY
  * @retval 1   flag set
  *         0   flag reset.
  */
uint8_t ADC_GetFlag(uint32_t FlagMask)
{
  /* Parameter check */
  assert_parameters(IS_ADC_ADCFLAG(FlagMask));
  
  if (ANA->ADCCTRL2 & FlagMask)
    return 1;
  else
    return 0;
}

/**
  * @brief  Clears ADC flag
  * @param  FlagMask: status to clear, can use the '|' operator.
                ADC_FLAG_CONV_ERR
                ADC_FLAG_CAL_ERR
  * @retval None
  */
void ADC_ClearFlag(uint32_t FlagMask)
{
  uint32_t tmp;

  /* Parameter check */
  assert_parameters(IS_ADC_ADCFLAGC(FlagMask));
  
  if (FlagMask == ADC_FLAG_CONV_ERR)
  {
    tmp = ANA->ADCCTRL2;
    tmp &= ~ANA_ADCCTRL2_CAL_ERR_CLR;
    tmp |= ANA_ADCCTRL2_CONV_ERR_CLR;
  }
  else if (FlagMask == ADC_FLAG_CAL_ERR)
  {
    tmp = ANA->ADCCTRL2;
    tmp &= ~ANA_ADCCTRL2_CONV_ERR_CLR;
    tmp |= ANA_ADCCTRL2_CAL_ERR_CLR;
  }
  else
  {
    tmp = ANA->ADCCTRL2;
    tmp |= (ANA_ADCCTRL2_CAL_ERR_CLR | ANA_ADCCTRL2_CONV_ERR_CLR);
  }
  ANA->ADCCTRL2 = tmp;
}

/**
  * @brief  Gets threshold flag
  * @param  THDFlagMask
                ADC_THDFLAG_UPPER3
                ADC_THDFLAG_LOWER3
                ADC_THDFLAG_UPPER2
                ADC_THDFLAG_LOWER2
                ADC_THDFLAG_UPPER1
                ADC_THDFLAG_LOWER1
                ADC_THDFLAG_UPPER0
                ADC_THDFLAG_LOWER0
  * @retval 1   flag set
  *         0   flag reset.
  */
uint8_t ADC_GetTHDFlag(uint32_t THDFlagMask)
{
  /* Parameter check */
  assert_parameters(IS_ADC_THDFLAG(THDFlagMask));

  if(ANA->ADCDATATHD_CH & THDFlagMask)
    return 1;
  else
    return 0;
}

/*********************************** END OF FILE ******************************/
