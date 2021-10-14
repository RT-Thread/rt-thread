/**
  ******************************************************************************
  * @file    lib_adc.c 
  * @author  Application Team
  * @version V4.6.0
  * @date    2019-06-18
  * @brief   ADC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_adc.h"

extern __IO uint32_t ana_reg3_tmp;
#define ANA_REG1_RSTValue     (0U)
#define ANA_ADCCTRL_RSTValue  (0U)

/**
  * @brief  Initializes ADC peripheral registers to their default reset values.
  * @note   1. Disable ADC
            2. Disable ADC overall bias current trim
            3. Disable resistor/cap division.
            4. Disable ADC auto/manual done interrupt
            5. ANA_ADCCTRL(register) write default value.
  * @param  None
  * @retval None
  */
void ADC_DeInit(void)
{
  /* Power down ADC */
  ana_reg3_tmp &= ~ANA_REG3_ADCPDN;  
  ANA->REG3 = ana_reg3_tmp;
  /* Disable resistor/cap division. */
  ANA->REG1 = ANA_REG1_RSTValue;
  /* Disable interrupt, Clear interrupt flag */
  ANA->INTEN &= ~(ANA_INTEN_INTEN0 | ANA_INTEN_INTEN1);
  ANA->INTSTS = (ANA_INTSTS_INTSTS0 | ANA_INTSTS_INTSTS1);
  while (ANA->ADCCTRL & ANA_ADCCTRL_MTRIG);
  ANA->ADCCTRL = ANA_ADCCTRL_RSTValue;
}

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @param  ADC_InitStruct: pointer to an ADCInitType structure which will be initialized.
  * @retval None
  */
void ADC_StructInit(ADCInitType* ADC_InitStruct)
{
  /*--------------- Reset ADC init structure parameters values ---------------*/
  /* Initialize the ClockSource member */
  ADC_InitStruct->ClockSource = ADC_CLKSRC_RCH;
  /* Initialize the Channel member */
  ADC_InitStruct->Channel = ADC_CHANNEL0;
  /* Initialize the ClockDivider member */
  ADC_InitStruct->ClockDivider = ADC_CLKDIV_1;
  /* Initialize the ConvMode member */
  ADC_InitStruct->ConvMode = ADC_CONVMODE_SINGLECHANNEL;
  /* Initialize the TrigMode member */
  ADC_InitStruct->TrigMode = ADC_TRIGMODE_MANUAL;
}

/**
  * @brief  ADC initialization.
  * @param  ADC_InitStruct:
                TrigMode:
                    ADC_TRIGMODE_AUTO
                    ADC_TRIGMODE_MANUAL
                ConvMode:
                    ADC_CONVMODE_SINGLECHANNEL
                    ADC_CONVMODE_MULTICHANNEL
                ClockSource:
                    ADC_CLKSRC_RCH
                    ADC_CLKSRC_PLLL
                ClockDivider:
                    ADC_CLKDIV_1
                    ADC_CLKDIV_2
                    ADC_CLKDIV_3
                    ADC_CLKDIV_4
                    ADC_CLKDIV_5
                    ADC_CLKDIV_6
                    ADC_CLKDIV_7
                    ADC_CLKDIV_8
                    ADC_CLKDIV_9
                    ADC_CLKDIV_10
                    ADC_CLKDIV_11
                    ADC_CLKDIV_12
                    ADC_CLKDIV_13
                    ADC_CLKDIV_14
                    ADC_CLKDIV_15
                    ADC_CLKDIV_16
                Channel:(be valid when ConvMode is ADC_CONVMODE_SINGLECHANNEL)
                    ADC_CHANNEL0
                    ADC_CHANNEL1
                    ADC_CHANNEL2
                    ADC_CHANNEL3
                    ADC_CHANNEL4
                    ADC_CHANNEL5
                    ADC_CHANNEL6
                    ADC_CHANNEL7
                    ADC_CHANNEL8
                    ADC_CHANNEL9
                    ADC_CHANNEL10
                    ADC_CHANNEL11
                    
  * @retval None
  */
void ADC_Init(ADCInitType* ADC_InitStruct)
{
  uint32_t tmp = 0;
  
  /* Check parameters */
  assert_parameters(IS_ADC_TRIGMODE(ADC_InitStruct->TrigMode));
  assert_parameters(IS_ADC_CONVMODE(ADC_InitStruct->ConvMode));
  assert_parameters(IS_ADC_CLKDIV(ADC_InitStruct->ClockDivider));
  assert_parameters(IS_ADC_CLKSRC(ADC_InitStruct->ClockSource));
  
  tmp = ANA->ADCCTRL;
  tmp &= ~(ANA_ADCCTRL_AMODE \
          |ANA_ADCCTRL_MMODE \
          |ANA_ADCCTRL_CLKSEL \
          |ANA_ADCCTRL_CLKDIV \
          |ANA_ADCCTRL_AEN \
          |ANA_ADCCTRL_MCH \
          |ANA_ADCCTRL_ACH);
  tmp |= (ADC_InitStruct->ClockDivider | ADC_InitStruct->ClockSource);
  
  if(ADC_InitStruct->TrigMode == ADC_TRIGMODE_AUTO)  //Auto mode
  {
    if(ADC_InitStruct->ConvMode == ADC_CONVMODE_SINGLECHANNEL)  //signal channel
    {
      assert_parameters(IS_ADC_CHANNEL(ADC_InitStruct->Channel));
      tmp &= (~ANA_ADCCTRL_ACH);
      tmp |= (ADC_InitStruct->Channel << ANA_ADCCTRL_ACH_Pos);
    }
    else   //multi channels
    {
      tmp |= ANA_ADCCTRL_AMODE;
    }
  }
  else  // Manual mode
  {
    if(ADC_InitStruct->ConvMode == ADC_CONVMODE_SINGLECHANNEL)  //signal channel
    {
      assert_parameters(IS_ADC_CHANNEL(ADC_InitStruct->Channel));
      tmp &= (~ANA_ADCCTRL_MCH);
      tmp |= (ADC_InitStruct->Channel << ANA_ADCCTRL_MCH_Pos);
    }
    else   //multi channels
    {
      tmp |= ANA_ADCCTRL_MMODE;
    }     
  }
  
  while (ANA->ADCCTRL & ANA_ADCCTRL_MTRIG);
  ANA->ADCCTRL = tmp;
}

/**
  * @brief  Calculate ADC voltage value(uint:V) via ADC original data.
  * @param  [in]Mode:
  *                ADC_3V_EXTERNAL_NODIV
  *                ADC_3V_EXTERNAL_RESDIV
  *                ADC_3V_EXTERNAL_CAPDIV
  *                ADC_3V_VDD_RESDIV
  *                ADC_3V_VDD_CAPDIV
  *                ADC_3V_BATRTC_RESDIV
  *                ADC_3V_BATRTC_CAPDIV
  *                ADC_5V_EXTERNAL_NODIV
  *                ADC_5V_EXTERNAL_RESDIV
  *                ADC_5V_EXTERNAL_CAPDIV
  *                ADC_5V_VDD_RESDIV
  *                ADC_5V_VDD_CAPDIV
  *                ADC_5V_BATRTC_RESDIV
  *                ADC_5V_BATRTC_CAPDIV
  * @param  [in]adc_data: The ADC original data
  * @param  [out]Voltage: The pointer of voltage value calculated by this function
  * @retval 1  NVR checksum error.
            0  Function successed.
  */
uint32_t ADC_CalculateVoltage(uint32_t Mode, int16_t adc_data, float *Voltage)
{
  NVR_ADCVOLPARA parameter;
  NVR_BATMEARES BAT_OffsetInfo;

  /* Check parameters */
  assert_parameters(IS_ADCVOL_MODE(Mode));
  
  if (NVR_GetADCVoltageParameter(Mode, &parameter))
  {
    if ((Mode&0xFUL) > 2UL) /* VDD or BATRTC channel */
    {
      if (NVR_GetBATOffset(&BAT_OffsetInfo))
      {
        return 1;
      }
      else
      {
        if (((Mode&0xFUL) == 3UL) || ((Mode&0xFUL) == 5UL))      /* VDD/BATRTC, Resistive */
        {
          *Voltage = (float)(0.00015392*(float)adc_data + 0.06667986) + BAT_OffsetInfo.BATRESResult;
        }
        else                                                     /* VDD/BATRTC, Capacitive */
        {
          *Voltage = (float)(0.00014107*(float)adc_data  - 0.00699515) + BAT_OffsetInfo.BATCAPResult;
        }
      }
    }
    else /* External channel */
    {
      if (Mode & 0x100UL)  /* Power supply: 5V */
      {
        if ((Mode&0xFUL) == 0UL)      /* No divider */
        {
          *Voltage = (float)(0.00003678*(float)adc_data + 0.00235783);
        }
        else if ((Mode&0xFUL) == 1UL) /* Resistive */
        {
          *Voltage = (float)(0.00016129*(float)adc_data + 0.00673599);
        }
        else                          /* Capacitive */
        {
          *Voltage = (float)(0.00014076*(float)adc_data - 0.00753319);
        }
      }
      else                 /* Power supply: 3.3V */
      {
        if ((Mode&0xFUL) == 0UL)      /* No divider */
        {
          *Voltage = (float)(0.00003680*(float)adc_data + 0.00205011);
        }
        else if ((Mode&0xFUL) == 1UL) /* Resistive */
        {
          *Voltage = (float)(0.00016425*(float)adc_data + 0.03739179);
        }
        else                          /* Capacitive */
        {
          *Voltage = (float)(0.00014051*(float)adc_data - 0.00023322);
        }
      }
    }
  }
  else
  {
    *Voltage = (float)(parameter.aParameter*(float)adc_data + parameter.bParameter);
  }

  return 0;
}

/**
  * @brief  Get VDD Voltage(takes 244us).
  * @note   This function costs about 170us when SystemClock is 26M.
  *         ADC data refresh time is 117us.
  * @note   This function will release ADC resource(write ADC registers with their
  *         default reset values).
  * @note   ADC configurarion:
  *             - Trigger mode:       manual mode
  *             - Conversion mode:    single channel mode(VDD channel 1)
  *             - ADC clock:          3.2M
  *             - Skip samples:       Skip 2 samples
  *             - Down sampling rate: 1/64
  * @param  [in]Division
                ADC_BAT_CAPDIV  (Cap division 1/4)
                ADC_BAT_RESDIV  (Resistance division 1/4)
            [out]CalResults.VDDVoltage      The value of VDD Voltage
            [out]CalResults.BATRTCVoltage   is ignored
            [out]CalResults.Temperature     is ignored
  * @retval 1  NVR BAT-offset information checksum error.
            0  Function successed.
  */
uint32_t ADC_GetVDDVoltage_Fast(uint32_t Division, ADC_CalResType *CalResults)
{
  float Vbatcap;
  float Vbatres;
  NVR_BATMEARES BAT_OffsetInfo;
  int16_t data;

  assert_parameters(IS_ADC_BATDIV(Division));
  
  /* Get NVR BAT offset information */
  if (NVR_GetBATOffset(&BAT_OffsetInfo))
  {
    return (1);
  }
  else  
  {
    Vbatcap = BAT_OffsetInfo.BATCAPResult;
    Vbatres = BAT_OffsetInfo.BATRESResult;
  }
  
  /* ADC initialization */
  ADC_DeInit();
  while (ANA->ADCCTRL & ANA_ADCCTRL_MTRIG);
  ANA->ADCCTRL = 0x06C00101;
  
  /* Enable division */
  ANA->REG1 |= Division;
  /* Enable ADC */
  ana_reg3_tmp |= ANA_REG3_ADCPDN;  
  ANA->REG3 = ana_reg3_tmp;
  
  /* Start a manual ADC conversion */
  ADC_StartManual();
  /* Waiting last operation done */
  ADC_WaitForManual();
  
  data = ANA->ADCDATA1;
 
  /* Calculate the voltage of VDD */
  if (Division & ADC_BAT_CAPDIV)
  {
    CalResults->VDDVoltage = (0.00014107*(float)data - 0.00699515) + Vbatcap;
  }
  else
  {
    CalResults->VDDVoltage = (0.00015392*(float)data + 0.06667986) + Vbatres;
  }
  
  /* ADC resource release */
  ADC_DeInit();
  
  return (0);
}

/**
  * @brief  Get VDD Voltage(takes 3.3ms).
  * @note   This function costs about 3.3ms when SystemClock is 26M.
  *         ADC data refresh time is about 3.2ms.
  * @note   This function will release ADC resource(write ADC registers with their
  *         default reset values).
  * @note   ADC configurarion:
  *             - Trigger mode:       manual mode
  *             - Conversion mode:    single channel mode(VDD channel 1)
  *             - ADC clock:          1.6M
  *             - Skip samples:       Skip first 4 samples
  *             - Down sampling rate: 1/512
  * @param  [in]Division
                ADC_BAT_CAPDIV  (Cap division 1/4)
                ADC_BAT_RESDIV  (Resistance division 1/4)
            [out]CalResults.VDDVoltage      The value of VDD Voltage
            [out]CalResults.BATRTCVoltage   is ignored
            [out]CalResults.Temperature     is ignored
  * @retval 1  NVR BAT-offset information checksum error.
            0  Function successed.
  */
uint32_t ADC_GetVDDVoltage_Normal(uint32_t Division, ADC_CalResType *CalResults)
{
  float Vbatcap;
  float Vbatres;
  NVR_BATMEARES BAT_OffsetInfo;
  ADCInitType ADC_InitStruct;
  int16_t data;
  
  assert_parameters(IS_ADC_BATDIV(Division));
  
  /* Get NVR BAT offset information */
  if (NVR_GetBATOffset(&BAT_OffsetInfo))
  {
    return (1);
  }
  else  
  {
    Vbatcap = BAT_OffsetInfo.BATCAPResult;
    Vbatres = BAT_OffsetInfo.BATRESResult;
  }
  
  /* ADC initialization */
  ADC_DeInit();
  ADC_InitStruct.TrigMode = ADC_TRIGMODE_MANUAL;
  ADC_InitStruct.ConvMode = ADC_CONVMODE_SINGLECHANNEL;
  ADC_InitStruct.Channel = ADC_CHANNEL1;
  ADC_InitStruct.ClockDivider = ADC_CLKDIV_4;
  ADC_InitStruct.ClockSource = ADC_CLKSRC_RCH;
  ADC_Init(&ADC_InitStruct);

  /* Enable division */
  ANA->REG1 |= Division;
  /* Enable ADC */
  ana_reg3_tmp |= ANA_REG3_ADCPDN;  
  ANA->REG3 = ana_reg3_tmp;
  
  /* Start a manual ADC conversion */
  ADC_StartManual();
  /* Waiting last operation done */
  ADC_WaitForManual();
  

  data = ANA->ADCDATA1;
 
  /* Calculate the voltage of  VDD */
  if (Division & ADC_BAT_CAPDIV)
  {
    CalResults->VDDVoltage = (0.00014107*(float)data - 0.00699515) + Vbatcap;
  }
  else
  {
    CalResults->VDDVoltage = (0.00015392*(float)data + 0.06667986) + Vbatres;
  }
  
  /* ADC resource release */
  ADC_DeInit();
  
  return (0);  
}

/**
  * @brief  Get BATRTC Voltage(takes 244us).
  * @note   This function takes about 244us when SystemClock is 26M.
  *         ADC data refresh time is 117us.
  * @note   This function will release ADC resource(write ADC registers with their
  *         default reset values).
  * @note   ADC configurarion:
  *             - Trigger mode:       manual mode
  *             - Conversion mode:    single channel mode(BATRTC channel 2)
  *             - ADC clock:          3.2M
  *             - Skip samples:       Skip 2 samples
  *             - Down sampling rate: 1/64
  * @param  [in]Division
                ADC_BAT_CAPDIV  (Cap division 1/4)
                ADC_BAT_RESDIV  (Resistance division 1/4)
            [out]CalResults.VDDVoltage     is ignored
            [out]CalResults.BATRTCVoltage   The value of BATRTC Voltage
            [out]CalResults.Temperature     is ignored
  * @retval 1  NVR BAT-offset or BGP-gain information checksum error.
            0  Function successed.
  */
uint32_t ADC_GetBATRTCVoltage_Fast(uint32_t Division, ADC_CalResType *CalResults)
{
  float Vbatcap;
  float Vbatres;
  
  NVR_BATMEARES BAT_OffsetInfo;
  int16_t data;
  
  assert_parameters(IS_ADC_BATDIV(Division));
  
  /* Get NVR BAT offset information */
  if (NVR_GetBATOffset(&BAT_OffsetInfo))
  {
    return (1);
  }
  else  
  {
    Vbatcap = BAT_OffsetInfo.BATCAPResult;
    Vbatres = BAT_OffsetInfo.BATRESResult;
  }
  
  /* ADC initialization */
  ADC_DeInit();
  while (ANA->ADCCTRL & ANA_ADCCTRL_MTRIG);
  ANA->ADCCTRL = 0x06C00102;
  /* Enable division */
  ANA->REG1 |= Division;
  /* Enable ADC */
  ana_reg3_tmp |= ANA_REG3_ADCPDN;  
  ANA->REG3 = ana_reg3_tmp;
  
  /* Start a manual ADC conversion */
  ADC_StartManual();
  /* Waiting last operation done */
  ADC_WaitForManual();
  
  data = ANA->ADCDATA2;
 
  /* Calculate the voltage of BAT1 */
  if (Division & ADC_BAT_CAPDIV)
  {
    CalResults->BATRTCVoltage = (0.00014107*(float)data  - 0.00699515) + Vbatcap;
  }
  else
  {
    CalResults->BATRTCVoltage = (0.00015392*(float)data  + 0.06667986) + Vbatres;
  }
  /* ADC resource release */
  ADC_DeInit();
  
  return (0);  
}

/**
  * @brief  Get BATRTC Voltage(takes 3.3ms).
  * @note   This function takes about 3.3ms when SystemClock is 26M.
  *         ADC data refresh time is about 3.2ms.
  * @note   This function will release ADC resource(write ADC registers with their
  *         default reset values).
  * @note   ADC configurarion:
  *             - Trigger mode:       manual mode
  *             - Conversion mode:    single channel mode(BATRTC channel 2)
  *             - ADC clock:          1.6M
  *             - Skip samples:       Skip first 4 samples
  *             - Down sampling rate: 1/512
  * @param  [in]Division
                ADC_BAT_CAPDIV  (Capacitance division 1/4)
                ADC_BAT_RESDIV  (Resistance division 1/4)
            [out]CalResults.VDDVoltage     is ignored
            [out]CalResults.BATRTCVoltage   The value of BATRTC Voltage
            [out]CalResults.Temperature     is ignored
  * @retval 1  NVR BAT-offset information checksum error.
            0  Function successed.
  */
uint32_t ADC_GetBATRTCVoltage_Normal(uint32_t Division, ADC_CalResType *CalResults)
{
  float Vbatcap;
  float Vbatres;
  NVR_BATMEARES BAT_OffsetInfo;
  ADCInitType ADC_InitStruct;
  int16_t data;
  
  assert_parameters(IS_ADC_BATDIV(Division));
  
  /* Get NVR BAT offset information */
  if (NVR_GetBATOffset(&BAT_OffsetInfo))
  {
    return (1);
  }
  else  
  {
    Vbatcap = BAT_OffsetInfo.BATCAPResult; 
    Vbatres = BAT_OffsetInfo.BATRESResult;
  }
  
  /* ADC initialization */
  ADC_DeInit();
  ADC_InitStruct.TrigMode = ADC_TRIGMODE_MANUAL;
  ADC_InitStruct.ConvMode = ADC_CONVMODE_SINGLECHANNEL;
  ADC_InitStruct.Channel = ADC_CHANNEL2;
  ADC_InitStruct.ClockDivider = ADC_CLKDIV_4;
  ADC_InitStruct.ClockSource = ADC_CLKSRC_RCH;
  ADC_Init(&ADC_InitStruct);

  /* Enable division */
  ANA->REG1 |= Division;
  /* Enable ADC */
  ana_reg3_tmp |= ANA_REG3_ADCPDN;  
  ANA->REG3 = ana_reg3_tmp;
  
  /* Start a manual ADC conversion */
  ADC_StartManual();
  /* Waiting last operation done */
  ADC_WaitForManual();
 
  data = ANA->ADCDATA2;
 
  /* Calculate the voltage of BAT1 */
  if (Division & ADC_BAT_CAPDIV)
  {
    CalResults->BATRTCVoltage = (0.00014107*(float)data  - 0.00699515) + Vbatcap;
  }
  else
  {
    CalResults->BATRTCVoltage = (0.00015392*(float)data  + 0.06667986) + Vbatres;
  }
  
  /* ADC resource release */
  ADC_DeInit();
  
  return (0);   
}

/**
  * @brief  Get Temperature(takes 6.5ms).
  * @note   This function costs about 6.5ms when SystemClock is 26M.
  *         ADC data refresh time is about 3.2ms.
  * @note   This function will release ADC resource(write ADC registers with their
  *         default reset values).
  * @note   ADC configurarion:
  *             - Trigger mode:       manual mode
  *             - Conversion mode:    single channel mode(Temperature channel 10)
  *             - ADC clock:          1.6M
  *             - Skip samples:       Skip first 4 samples
  *             - Down sampling rate: 1/512
  * @param  [out]CalResults.VDDVoltage      is ignored
            [out]CalResults.BATRTCVoltage   is ignored
            [out]CalResults.Temperature     The value of Temperature
  * @retval 1  Temperature delta information checksum error.
            0  Function successed.
  */
uint32_t ADC_GetTemperature(ADC_CalResType *CalResults)
{
  int32_t P2;
  int16_t P1, P0;
  int16_t adc_data;
  uint32_t retval;
  NVR_RTCINFO RTC_DataStruct;
  ADCInitType ADC_InitStruct;
  
  /* Get RTC Px parameters */
  retval = NVR_GetInfo_LoadRTCData(&RTC_DataStruct);
  if (retval & 0x1U)
  {
    return (1);
  }
  else
  {
    P0 = RTC_DataStruct.RTCTempP0;
    P1 = RTC_DataStruct.RTCTempP1;
    P2 = RTC_DataStruct.RTCTempP2;
  }  
  
  /* ADC initialization */
  ADC_DeInit();
  ADC_InitStruct.TrigMode = ADC_TRIGMODE_MANUAL;
  ADC_InitStruct.ConvMode = ADC_CONVMODE_SINGLECHANNEL;
  ADC_InitStruct.Channel = ADC_CHANNEL10;
  ADC_InitStruct.ClockDivider = ADC_CLKDIV_4;
  ADC_InitStruct.ClockSource = ADC_CLKSRC_RCH;
  ADC_Init(&ADC_InitStruct);
  
  /* Configure 1/512 down-sampling rate */
  ADC_CICDownSamRateConfig(ADC_SDRSEL_DIV512);
  /* Enable ADC */
  ADC_Cmd(ENABLE);
  
  /*---------- Get ADC data1 ----------*/
  /* Starts a manual ADC conversion */
  ADC_StartManual();
  /* Waiting Manual ADC conversion done */
  ADC_WaitForManual();
  adc_data = (int16_t)ADC_GetADCConversionValue(ADC_CHANNEL10);

  /* ADC resource release */
  ADC_DeInit();
    
  /* Calculate temperature */
  CalResults->Temperature = (float)((((P0 * ((adc_data*adc_data)>>16)) + P1*adc_data + P2) >> 8) / 256.0);
  
  return (0);
}

/**
  * @brief  ADC power control.
  * @note   When DISABLE is selected, the automatic triggering of the ADC must be turned off by calling 
  *         ADC_TrigSourceConfig(ADC_TRIGSOURCE_OFF) before using this function.
  * @param  NewState
                ENABLE
                DISABLE
  * @retval 0: Function succeeded
  *         1: Function failded, the automatic triggering be enabled when DISABLE selected
  */
uint32_t ADC_Cmd(uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  
  if (NewState == DISABLE)
  {
    if (ANA->ADCCTRL & ANA_ADCCTRL_AEN)
    {
      return 1;
    }
    else
    {
      ana_reg3_tmp &= ~ANA_REG3_ADCPDN;
    }
  }
  else
  {
    ana_reg3_tmp |= ANA_REG3_ADCPDN;
  }
  
  ANA->REG3 = ana_reg3_tmp;
  
  return 0;
}

/**
  * @brief  Manual ADC trigger
  * @param  None
  * @retval None
  */
void ADC_StartManual(void)
{
  while (ANA->ADCCTRL & ANA_ADCCTRL_MTRIG);
  ANA->ADCCTRL |= ANA_ADCCTRL_MTRIG;
}

/**
  * @brief  Wait for the last Manual ADC conversion done.
  * @param  None
  * @retval None
  */
void ADC_WaitForManual(void)
{
  while (ANA->ADCCTRL & ANA_ADCCTRL_MTRIG)
  {
  }
}

/**
  * @brief  ADC auto mode trigger source configure.
  * @param  TrigSource:
                ADC_TRIGSOURCE_OFF  
                ADC_TRIGSOURCE_TIM0  
                ADC_TRIGSOURCE_TIM1  
                ADC_TRIGSOURCE_TIM2  
                ADC_TRIGSOURCE_TIM3  
  * @retval None
  */
void ADC_TrigSourceConfig(uint32_t TrigSource)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_ADC_TRIGSOURCE(TrigSource));
  
  tmp = ANA->ADCCTRL;
  tmp &= ~ANA_ADCCTRL_AEN;
  tmp |= TrigSource;
  while (ANA->ADCCTRL & ANA_ADCCTRL_MTRIG);
  ANA->ADCCTRL = tmp;  
}

/**
  * @brief  Resistance division enable control.
  * @param  NewState
                ENABLE   (x1/4)
                DISABLE  (x1)
  * @retval None
  */
void ADC_RESDivisionCmd(uint32_t NewState)
{
  uint32_t tmp;
	
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  tmp = ANA->REG1;
  if (NewState == ENABLE)
  {
    tmp &= ~ANA_REG1_GDE4;
    tmp |=ANA_REG1_RESDIV;
  }
  else
  {
    tmp &= ~ANA_REG1_RESDIV;
  }
  ANA->REG1 = tmp;
}

/**
  * @brief  Capacitance division enable control.
  * @param  NewState
                ENABLE   (x1/4)
                DISABLE  (x1)
  * @retval None
  */
void ADC_CAPDivisionCmd(uint32_t NewState)
{
  uint32_t tmp;
	
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  tmp = ANA->REG1;
  if (NewState == ENABLE)
  {
    tmp &= ~ANA_REG1_RESDIV;
    tmp |=ANA_REG1_GDE4;
  }
  else
  {
    tmp &= ~ANA_REG1_GDE4;
  }
  ANA->REG1 = tmp;
}

/**
  * @brief  CIC filter always on control.
  * @param  NewState
                ENABLE   (CIC filter always on)
                DISABLE  (CIC filter will be disabled when no ADC sample process is ongoing.)
  * @retval None
  */
void ADC_CICAlwaysOnCmd(uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  while (ANA->ADCCTRL & ANA_ADCCTRL_MTRIG);
  
  if (NewState == ENABLE)
    ANA->ADCCTRL |= ANA_ADCCTRL_CICAON;
  else
    ANA->ADCCTRL &= ~ANA_ADCCTRL_CICAON;
}

/**
  * @brief  CIC filter input inversion control.
  * @param  NewState
                ENABLE
                DISABLE
  * @retval None
  */
void ADC_CICINVCmd(uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  while (ANA->ADCCTRL & ANA_ADCCTRL_MTRIG);

  if (NewState == ENABLE)  
    ANA->ADCCTRL |= ANA_ADCCTRL_CICINV;
  else
    ANA->ADCCTRL &= ~ANA_ADCCTRL_CICINV;
}

/**
  * @brief  CIC output scale-down configure.
  * @param  ScaleDown:
                ADC_SCA_NONE
                ADC_SCA_DIV2
  * @retval None
  */
void ADC_CICScaleDownConfig(uint32_t ScaleDown)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_ADC_SCA(ScaleDown));  
  
  tmp = ANA->ADCCTRL;
  tmp &= ~ANA_ADCCTRL_CICSCA;
  tmp |= ScaleDown;
  while (ANA->ADCCTRL & ANA_ADCCTRL_MTRIG);
  ANA->ADCCTRL = tmp;
}

/**
  * @brief  CIC output skip control.
  * @param  Skip:
                ADC_SKIP_4
                ADC_SKIP_5
                ADC_SKIP_6
                ADC_SKIP_7
                ADC_SKIP_0
                ADC_SKIP_1
                ADC_SKIP_2
                ADC_SKIP_3
  * @retval None
  */
void ADC_CICSkipConfig(uint32_t Skip)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_ADC_SKIP(Skip));  
  
  tmp = ANA->ADCCTRL; 
  tmp &= ~ANA_ADCCTRL_CICSKIP;
  tmp |= Skip;
  while (ANA->ADCCTRL & ANA_ADCCTRL_MTRIG);
  ANA->ADCCTRL = tmp;
}

/**
  * @brief  CIC down sampling rate control.
  * @param  DSRSelection:
                ADC_SDRSEL_DIV512
                ADC_SDRSEL_DIV256
                ADC_SDRSEL_DIV128
                ADC_SDRSEL_DIV64
  * @retval None
  */
void ADC_CICDownSamRateConfig(uint32_t DSRSelection)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_ADC_SDR(DSRSelection));  
  tmp = ANA->ADCCTRL;
  tmp &= ~ANA_ADCCTRL_DSRSEL;
  tmp |= DSRSelection;
  while (ANA->ADCCTRL & ANA_ADCCTRL_MTRIG);
  ANA->ADCCTRL = tmp;
}

/**
  * @brief  Get ADC vonversion value.
  * @param  Channel:
                 ADC_CHANNEL0 
                 ADC_CHANNEL1  
                 ADC_CHANNEL2  
                 ADC_CHANNEL3  
                 ADC_CHANNEL4  
                 ADC_CHANNEL5  
                 ADC_CHANNEL6  
                 ADC_CHANNEL7  
                 ADC_CHANNEL8  
                 ADC_CHANNEL9  
                 ADC_CHANNEL10 
                 ADC_CHANNEL11 
  * @retval ADC conversion value.
  */
int16_t ADC_GetADCConversionValue(uint32_t Channel)
{
  __IO uint32_t *addr;
  
  /* Check parameters */
  assert_parameters(IS_ADC_CHANNEL(Channel));
 
  addr = &ANA->ADCDATA0 + Channel;

  return *addr;
}

/**
  * @brief  ADC interrupt control.
  * @param  INTMask:
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
  * @brief  Get auto done flag
  * @param  None
  * @retval 1   flag set
  *         0   flag reset.
  */
uint8_t ADC_GetAutoDoneFlag(void)
{
  if(ANA->INTSTS & ANA_INTSTS_INTSTS1)
    return 1;
  else
    return 0;
}

/**
  * @brief  Get manual done flag
  * @param  None
  * @retval 1   flag set
  *         0   flag reset.
  */
uint8_t ADC_GetManualDoneFlag(void)
{
  if(ANA->INTSTS & ANA_INTSTS_INTSTS0)
    return 1;
  else
    return 0;
}

/**
  * @brief  Clear auto done flag
  * @param  None
  * @retval None
  */
void ADC_ClearAutoDoneFlag(void)
{
  ANA->INTSTS = ANA_INTSTS_INTSTS1;
}

/**
  * @brief  Clear manual done flag
  * @param  None
  * @retval None
  */
void ADC_ClearManualDoneFlag(void)
{
  ANA->INTSTS = ANA_INTSTS_INTSTS0;
}

/*********************************** END OF FILE ******************************/
