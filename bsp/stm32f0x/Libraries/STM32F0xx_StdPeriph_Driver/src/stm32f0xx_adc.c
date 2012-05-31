/**
  ******************************************************************************
  * @file    stm32f0xx_adc.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC) peripheral:
  *           + Initialization and Configuration
  *           + Power saving
  *           + Analog Watchdog configuration
  *           + Temperature Sensor, Vrefint (Internal Reference Voltage) and 
  *             Vbat (Voltage battery) management 
  *           + ADC Channels Configuration
  *           + ADC Channels DMA Configuration
  *           + Interrupts and flags management
  *
  *  @verbatim
================================================================================
                      ##### How to use this driver #####
================================================================================
    [..]
    (#) Enable the ADC interface clock using 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 
    (#) ADC pins configuration
       (++) Enable the clock for the ADC GPIOs using the following function:
            RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOx, ENABLE);   
       (++) Configure these ADC pins in analog mode using GPIO_Init();  
    (#) Configure the ADC conversion resolution, data alignment, external
        trigger and edge, scan direction and Enable/Disable the continuous mode
        using the ADC_Init() function.
    (#) Activate the ADC peripheral using ADC_Cmd() function.

    *** ADC channels group configuration ***
    ============================================
    [..] 
    (+) To configure the ADC channels features, use ADC_Init() and 
        ADC_ChannelConfig() functions.
    (+) To activate the continuous mode, use the ADC_ContinuousModeCmd()
        function.
    (+) To activate the Discontinuous mode, use the ADC_DiscModeCmd() functions. 
    (+) To activate the overrun mode, use the ADC_OverrunModeCmd() functions.
    (+) To activate the calibration mode, use the ADC_GetCalibrationFactor() functions.
    (+) To read the ADC converted values, use the ADC_GetConversionValue()
        function.

    *** DMA for ADC channels features configuration ***
    =============================================================
    [..] 
    (+) To enable the DMA mode for ADC channels group, use the ADC_DMACmd() function.
    (+) To configure the DMA transfer request, use ADC_DMARequestModeConfig() function.

  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_adc.h"
#include "stm32f0xx_rcc.h"

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup ADC 
  * @brief ADC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ADC CFGR mask */
#define CFGR1_CLEAR_MASK           ((uint32_t)0xFFFFD203)

/* Calibration time out */
#define CALIBRATION_TIMEOUT       ((uint32_t)0x0000F000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ADC_Private_Functions
  * @{
  */

/** @defgroup ADC_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim
 ===============================================================================
          ##### Initialization and Configuration functions #####
 ===============================================================================
    [..] This section provides functions allowing to:
        (+) Initialize and configure the ADC Prescaler
        (+) ADC Conversion Resolution (12bit..6bit)
        (+) ADC Continuous Conversion Mode (Continuous or Single conversion)
        (+) External trigger Edge and source 
        (+) Converted data alignment (left or right)
        (+) The direction in which the channels will be scanned in the sequence
        (+) Enable or disable the ADC peripheral
   
@endverbatim
  * @{
  */

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
  *         This parameter can be: ENABLE or DISABLE.
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
  * @brief  Enables or disables the jitter when the ADC is clocked by PCLK div2
  *         or div4
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_JitterOff: This parameter can be :
  *     @arg ADC_JitterOff_PCLKDiv2: Remove jitter when ADC is clocked by PLCK divided by 2
  *     @arg ADC_JitterOff_PCLKDiv4: Remove jitter when ADC is clocked by PLCK divided by 4
  * @param  NewState: new state of the ADCx jitter. 
  *         This parameter can be: ENABLE or DISABLE.
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

/** @defgroup ADC_Group2 Power saving functions
 *  @brief   Power saving functions 
 *
@verbatim
 ===============================================================================
          ##### Power saving functions #####
 ===============================================================================
    [..] This section provides functions allowing to reduce power consumption.
    [..] The two function must be combined to get the maximal benefits:
         When the ADC frequency is higher than the CPU one, it is recommended to 
         (#) Enable the Auto Delayed Conversion mode : 
             ==> using ADC_WaitModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
         (#) Enable the power off in Delay phases :
             ==> using ADC_AutoPowerOffCmd(ADC_TypeDef* ADCx, FunctionalState NewState);

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the ADC Power Off.
  * @note   ADC power-on and power-off can be managed by hardware to cut the 
  *         consumption when the ADC is not converting. 
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @note   The ADC can be powered down: 
  *         - During the Auto delay phase 
  *           => The ADC is powered on again at the end of the delay (until the 
  *              previous data is read from the ADC data register). 
  *         - During the ADC is waiting for a trigger event 
  *           => The ADC is powered up at the next trigger event (when the 
  *              conversion is started).
  * @param  NewState: new state of the ADCx power Off. 
  *         This parameter can be: ENABLE or DISABLE.
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
  * @note   The Hardware delay is inserted after :
  *         - after each conversions and until the previous data is read from the 
  *           ADC data register
  * @note   This is a way to automatically adapt the speed of the ADC to the speed 
  *         of the system which will read the data.
  * @note   Any hardware triggers wich occur while a conversion is on going or 
  *         while the automatic Delay is applied are ignored 
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the ADCx Auto-Delay.
  *         This parameter can be: ENABLE or DISABLE.
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

/** @defgroup ADC_Group3 Analog Watchdog configuration functions
 *  @brief   Analog Watchdog configuration functions 
 *
@verbatim
 ===============================================================================
                   ##### Analog Watchdog configuration functions #####
 ===============================================================================  
    [..] This section provides functions allowing to configure the Analog Watchdog
         (AWD) feature in the ADC.
    [..] A typical configuration Analog Watchdog is done following these steps :
         (#) the ADC guarded channel(s) is (are) selected using the 
             ADC_AnalogWatchdogSingleChannelConfig() function.
         (#) The Analog watchdog lower and higher threshold are configured using the  
             ADC_AnalogWatchdogThresholdsConfig() function.
         (#) The Analog watchdog is enabled and configured to enable the check, on one
             or more channels, using the  ADC_AnalogWatchdogCmd() function.
         (#) Enable the analog watchdog on the selected channel using
             ADC_AnalogWatchdogSingleChannelCmd() function

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the analog watchdog 
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the ADCx Analog Watchdog.
  *         This parameter can be: ENABLE or DISABLE.
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
  *         This parameter must be a 12bit value.
  * @param  LowThreshold: the ADC analog watchdog Low threshold value.
  *         This parameter must be a 12bit value.
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
  *   This parameter can be one of the following values:
  *     @arg ADC_AnalogWatchdog_Channel_0: ADC Channel0 selected
  *     @arg ADC_AnalogWatchdog_Channel_1: ADC Channel1 selected
  *     @arg ADC_AnalogWatchdog_Channel_2: ADC Channel2 selected
  *     @arg ADC_AnalogWatchdog_Channel_3: ADC Channel3 selected
  *     @arg ADC_AnalogWatchdog_Channel_4: ADC Channel4 selected
  *     @arg ADC_AnalogWatchdog_Channel_5: ADC Channel5 selected
  *     @arg ADC_AnalogWatchdog_Channel_6: ADC Channel6 selected
  *     @arg ADC_AnalogWatchdog_Channel_7: ADC Channel7 selected
  *     @arg ADC_AnalogWatchdog_Channel_8: ADC Channel8 selected
  *     @arg ADC_AnalogWatchdog_Channel_9: ADC Channel9 selected
  *     @arg ADC_AnalogWatchdog_Channel_10: ADC Channel10 selected
  *     @arg ADC_AnalogWatchdog_Channel_11: ADC Channel11 selected
  *     @arg ADC_AnalogWatchdog_Channel_12: ADC Channel12 selected
  *     @arg ADC_AnalogWatchdog_Channel_13: ADC Channel13 selected
  *     @arg ADC_AnalogWatchdog_Channel_14: ADC Channel14 selected
  *     @arg ADC_AnalogWatchdog_Channel_15: ADC Channel15 selected
  *     @arg ADC_AnalogWatchdog_Channel_16: ADC Channel16 selected
  *     @arg ADC_AnalogWatchdog_Channel_17: ADC Channel17 selected
  *     @arg ADC_AnalogWatchdog_Channel_18: ADC Channel18 selected
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
  *         This parameter can be: ENABLE or DISABLE.
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

/** @defgroup ADC_Group4 Temperature Sensor, Vrefint  and Vbat management functions
 *  @brief   Temperature Sensor, Vrefint  and Vbat management functions
 *
@verbatim
 ===============================================================================
 ##### Temperature Sensor, Vrefint  and Vbat management function #####
 ===============================================================================
    [..] This section provides a function allowing to enable/disable the internal 
         connections between the ADC and the Temperature Sensor, the Vrefint and
         Vbat source.
     
    [..] A typical configuration to get the Temperature sensor, Vrefint and Vbat channels 
         voltages is done following these steps :
         (#) Enable the internal connection of Temperature sensor, Vrefint or Vbat sources 
             with the ADC channels using ADC_TempSensorCmd(), ADC_VrefintCmd() or ADC_VbatCmd()
             functions. 
         (#) select the ADC_Channel_16(Temperature sensor), ADC_Channel_17(Vrefint)
             or ADC_Channel_18(Voltage battery) using ADC_ChannelConfig() function 
         (#) Get the voltage values, using ADC_GetConversionValue() function

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the temperature sensor channel.
  * @param  NewState: new state of the temperature sensor input channel.
  *         This parameter can be: ENABLE or DISABLE.
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
  *         This parameter can be: ENABLE or DISABLE.
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
  * @param  NewState: new state of the Vbat input channel.
  *         This parameter can be: ENABLE or DISABLE.
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

/** @defgroup ADC_Group5 Channels Configuration functions
 *  @brief    Channels Configuration functions 
 *
@verbatim
 ===============================================================================
            ##### Channels Configuration functions #####
 ===============================================================================
    [..] This section provides functions allowing to manage the ADC channels,
         it is composed of 3 sub sections :
         (#) Configuration and management functions for ADC channels: This subsection 
             provides functions allowing to configure the ADC channels :    
             (++) Select the ADC channels
             (++) Activate ADC Calibration
             (++) Activate the Overrun Mode.
             (++) Activate the Discontinuous Mode 
             (++) Activate the Continuous Mode.
             (++) Configure the sampling time for each channel
             (++) Select the conversion Trigger and Edge for ADC channels
             (++) Select the scan direction.
             -@@- Please Note that the following features for ADC channels are configurated
                  using the ADC_Init() function : 
                  (+@@) Activate the Continuous Mode (can be also activated by ADC_OverrunModeCmd().
                  (+@@) Select the conversion Trigger and Edge for ADC channels
                  (+@@) Select the scan direction.
         (#) Control the ADC peripheral : This subsection permits to command the ADC:
             (++) Stop or discard an on-going conversion (ADSTP command)
             (++) Start the ADC conversion .
         (#) Get the conversion data: This subsection provides an important function in 
             the ADC peripheral since it returns the converted data of the current 
             ADC channel. When the Conversion value is read, the EOC Flag is 
             automatically cleared.

@endverbatim
  * @{
  */

/**
  * @brief  Configures for the selected ADC and its sampling time.
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure. 
  *   This parameter can be any combination of the following values:
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
  *     @arg ADC_Channel_18: ADC Channel18 selected    
  * @param  ADC_SampleTime: The sample time value to be set for the selected 
  *         channel. 
  *   This parameter can be one of the following values:
  *     @arg ADC_SampleTime_1_5Cycles: Sample time equal to 1.5 cycles  
  *     @arg ADC_SampleTime_7_5Cycles: Sample time equal to 7.5 cycles
  *     @arg ADC_SampleTime_13_5Cycles: Sample time equal to 13.5 cycles
  *     @arg ADC_SampleTime_28_5Cycles: Sample time equal to 28.5 cycles
  *     @arg ADC_SampleTime_41_5Cycles: Sample time equal to 41.5 cycles
  *     @arg ADC_SampleTime_55_5Cycles: Sample time equal to 55.5 cycles
  *     @arg ADC_SampleTime_71_5Cycles: Sample time equal to 71.5 cycles
  *     @arg ADC_SampleTime_239_5Cycles: Sample time equal to 239.5 cycles
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
  *         This parameter can be: ENABLE or DISABLE.
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
  *         This parameter can be: ENABLE or DISABLE.
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
  *         This parameter can be: ENABLE or DISABLE.
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

/** @defgroup ADC_Group6 DMA Configuration functions
 *  @brief   Regular Channels DMA Configuration functions 
 *
@verbatim
 ===============================================================================
          ##### DMA Configuration functions #####
 ===============================================================================
    [..] This section provides functions allowing to configure the DMA for ADC hannels.
         Since converted channel values are stored into a unique data register, 
         it is useful to use DMA for conversion of more than one channel. This 
         avoids the loss of the data already stored in the ADC Data register. 
         When the DMA mode is enabled (using the ADC_DMACmd() function), after each
         conversion of a channel, a DMA request is generated.
  
    [..] Depending on the "DMA disable selection" configuration (using the 
         ADC_DMARequestModeConfig() function), at the end of the last DMA 
         transfer, two possibilities are allowed:
         (+) No new DMA request is issued to the DMA controller (One Shot Mode) 
         (+) Requests can continue to be generated (Circular Mode).

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified ADC DMA request.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the selected ADC DMA transfer.
  *         This parameter can be: ENABLE or DISABLE.
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
  *   This parameter can be one of the following values:
  *     @arg ADC_DMAMode_OneShot  : DMA One Shot Mode 
  *     @arg ADC_DMAMode_Circular : DMA Circular Mode  
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

/** @defgroup ADC_Group7 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions.
 *
@verbatim   
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================
    [..] This section provides functions allowing to configure the ADC Interrupts 
         and get the status and clear flags and Interrupts pending bits.
  
    [..] The ADC provide 6 Interrupts sources and 11 Flags which can be divided into 
         3 groups:

  *** Flags for ADC status ***
  ======================================================
    [..]
        (+)Flags :
           (##) ADC_FLAG_ADRDY : This flag is set after the ADC has been enabled (bit ADEN=1)
               and when the ADC reaches a state where it is ready to accept conversion requests
           (##) ADC_FLAG_ADEN : This flag is set by software to enable the ADC.
                The ADC will be effectively ready to operate once the ADRDY flag has been set.
           (##) ADC_FLAG_ADDIS : This flag is cleared once the ADC is effectively
                disabled.
           (##) ADC_FLAG_ADSTART : This flag is cleared after the execution of
                ADC_StopOfConversion() function, at the same time as the ADSTP bit is
                cleared by hardware
           (##) ADC_FLAG_ADSTP : This flag is cleared by hardware when the conversion
                is effectively discarded and the ADC is ready to accept a new start conversion
           (##) ADC_FLAG_ADCAL : This flag is set once the calibration is complete.

        (+)Interrupts 
           (##) ADC_IT_ADRDY : specifies the interrupt source for ADC ready event.

  *** Flags and Interrupts for ADC channel conversion ***
  =====================================================
    [..]
        (+)Flags :
           (##) ADC_FLAG_EOC : This flag is set by hardware at the end of each conversion
                of a channel when a new data result is available in the data register
           (##) ADC_FLAG_EOSEQ : This bit is set by hardware at the end of the conversion
                of a sequence of channels selected by ADC_ChannelConfig() function.
           (##) ADC_FLAG_EOSMP : This bit is set by hardware at the end of the sampling phase.
           (##) ADC_FLAG_OVR : This flag is set by hardware when an overrun occurs,
                meaning that a new conversion has complete while the EOC flag was already set.

        (+)Interrupts :
           (##) ADC_IT_EOC : specifies the interrupt source for end of conversion event.
           (##) ADC_IT_EOSEQ : specifies the interrupt source for end of sequence event.
           (##) ADC_IT_EOSMP : specifies the interrupt source for end of sampling event.
           (##) ADC_IT_OVR : specifies the interrupt source for Overrun detection 
                event.

  *** Flags and Interrupts for the Analog Watchdog ***
  ================================================
    [..]
        (+)Flags :
           (##) ADC_FLAG_AWD: This flag is set by hardware when the converted
                voltage crosses the values programmed thrsholds

        (+)Interrupts :
           (##) ADC_IT_AWD : specifies the interrupt source for Analog watchdog 
                event.
  
    [..] The user should identify which mode will be used in his application to 
         manage the ADC controller events: Polling mode or Interrupt mode.
  
    [..] In the Polling Mode it is advised to use the following functions:
         (+) ADC_GetFlagStatus() : to check if flags events occur.
         (+) ADC_ClearFlag()     : to clear the flags events.
  
    [..] In the Interrupt Mode it is advised to use the following functions:
         (+) ADC_ITConfig()       : to enable or disable the interrupt source.
         (+) ADC_GetITStatus()    : to check if Interrupt occurs.
         (+) ADC_ClearITPendingBit() : to clear the Interrupt pending Bit 
             (corresponding Flag).

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg ADC_IT_ADRDY: ADC ready interrupt 
  *     @arg ADC_IT_EOSMP: End of sampling interrupt
  *     @arg ADC_IT_EOC: End of conversion interrupt 
  *     @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *     @arg ADC_IT_OVR: overrun interrupt
  *     @arg ADC_IT_AWD: Analog watchdog interrupt
  * @param  NewState: new state of the specified ADC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
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
  *   This parameter can be one of the following values:
  *     @arg ADC_FLAG_AWD: Analog watchdog flag
  *     @arg ADC_FLAG_OVR: Overrun flag 
  *     @arg ADC_FLAG_EOSEQ: End of Sequence flag
  *     @arg ADC_FLAG_EOC: End of conversion flag
  *     @arg ADC_FLAG_EOSMP: End of sampling flag
  *     @arg ADC_FLAG_ADRDY: ADC Ready flag
  *     @arg ADC_FLAG_ADEN: ADC enable flag 
  *     @arg ADC_FLAG_ADDIS: ADC disable flag 
  *     @arg ADC_FLAG_ADSTART: ADC start flag 
  *     @arg ADC_FLAG_ADSTP: ADC stop flag
  *     @arg ADC_FLAG_ADCAL: ADC Calibration flag
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
  *   This parameter can be any combination of the following values:
  *     @arg ADC_FLAG_AWD: Analog watchdog flag
  *     @arg ADC_FLAG_EOC: End of conversion flag
  *     @arg ADC_FLAG_ADRDY: ADC Ready flag
  *     @arg ADC_FLAG_EOSMP: End of sampling flag
  *     @arg ADC_FLAG_EOSEQ: End of Sequence flag
  *     @arg ADC_FLAG_OVR: Overrun flag 
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
  *   This parameter can be one of the following values:
  *     @arg ADC_IT_ADRDY: ADC ready interrupt 
  *     @arg ADC_IT_EOSMP: End of sampling interrupt
  *     @arg ADC_IT_EOC: End of conversion interrupt 
  *     @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *     @arg ADC_IT_OVR: overrun interrupt
  *     @arg ADC_IT_AWD: Analog watchdog interrupt
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
  *   This parameter can be one of the following values:
  *     @arg ADC_IT_ADRDY: ADC ready interrupt
  *     @arg ADC_IT_EOSMP: End of sampling interrupt
  *     @arg ADC_IT_EOC: End of conversion interrupt
  *     @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *     @arg ADC_IT_OVR: overrun interrupt
  *     @arg ADC_IT_AWD: Analog watchdog interrupt
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
