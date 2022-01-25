/**
  ******************************************************************************
  * @file    stm32f3xx_hal_dac.c
  * @author  MCD Application Team
  * @brief   DAC HAL module driver.
  *         This file provides firmware functions to manage the following 
  *         functionalities of the Digital to Analog Converter (DAC) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions      
  *
  *
 @verbatim      
  ==============================================================================
                      ##### DAC Peripheral features #####
  ==============================================================================
    [..]        
      *** DAC Channels ***
      ====================  
    [..]  
    The device integrates up to 3 12-bit Digital Analog Converters that can 
    be used independently or simultaneously (dual mode):
      (#) DAC1 channel1 with DAC1_OUT1 (PA4) as output
      (#) DAC1 channel2 with DAC1_OUT2 (PA5) as output 
          (for STM32F3 devices having 2 channels on DAC1)
      (#) DAC2 channel1 with DAC2_OUT1 (PA6) as output 
          (for STM32F3 devices having 2 DAC)

      *** DAC Triggers ***
      ====================
    [..]
    Digital to Analog conversion can be non-triggered using DAC_TRIGGER_NONE
    and DAC1_OUT1/DAC1_OUT2/DAC2_OUT1 is available once writing to DHRx register. 
    [..] 
    Digital to Analog conversion can be triggered by:
      (#) External event: EXTI Line 9 (any GPIOx_PIN_9) using DAC_TRIGGER_EXT_IT9.
          The used pin (GPIOx_PIN_9) must be configured in input mode.
  
      (#) Timers TRGO: TIM2, TIM4, TIM5, TIM6, TIM7 and TIM8 
          (DAC_TRIGGER_T2_TRGO, DAC_TRIGGER_T4_TRGO...)
  
      (#) Software using DAC_TRIGGER_SOFTWARE
  
      *** DAC Buffer mode feature ***
      =============================== 
      [..] 
      Each DAC channel integrates an output buffer that can be used to 
      reduce the output impedance, and to drive external loads directly
      without having to add an external operational amplifier.
      To enable, the output buffer use  
      sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
      Or
      An output switch 
         (in STM32F303x4, STM32F303x6, STM32F303x8
             c, STM32F334x6, STM32F334x8
           & STM32F334xx).
      To enable, the output switch
      sConfig.DAC_OutputSwitch = DAC_OUTPUTSWITCH_ENABLE;
      [..]         
      (@) Refer to the device datasheet for more details about output 
          impedance value with and without output buffer.

      *** GPIO configurations guidelines ***
      =====================
      [..] 
      When a DAC channel is used (ex channel1 on PA4) and the other is not 
      (ex channel2 on PA5 is configured in Analog and disabled).
      Channel1 may disturb channel2 as coupling effect.
      Note that there is no coupling on channel2 as soon as channel2 is turned on.
      Coupling on adjacent channel could be avoided as follows:
      when unused PA5 is configured as INPUT PULL-UP or DOWN. 
      PA5 is configured in ANALOG just before it is turned on.     

            
       *** DAC wave generation feature ***
       =================================== 
       [..]     
       Both DAC channels of DAC1 can be used to generate
       note that wave generation is not available in DAC2.
         (#) Noise wave
         (#) Triangle wave
      
       Wave generation is NOT available in DAC2.

       *** DAC data format ***
       =======================
       [..]   
       The DAC data format can be:
         (#) 8-bit right alignment using DAC_ALIGN_8B_R
         (#) 12-bit left alignment using DAC_ALIGN_12B_L
         (#) 12-bit right alignment using DAC_ALIGN_12B_R
  
       *** DAC data value to voltage correspondance ***  
       ================================================ 
       [..] 
       The analog output voltage on each DAC channel pin is determined
       by the following equation: 
       [..] 
       DAC_OUTx = VREF+ * DOR / 4095     
       (+) with  DOR is the Data Output Register
       [..]  
          VEF+ is the input voltage reference (refer to the device datasheet)
       [..]        
        e.g. To set DAC_OUT1 to 0.7V, use
       (+)  Assuming that VREF+ = 3.3V, DAC_OUT1 = (3.3U * 868U) / 4095U = 0.7V
  
       *** DMA requests  ***
       =====================
       [..]    
       A DMA1 or DMA2 request can be generated when an external trigger 
       (but not a software trigger) occurs if DMA1 or DMA2 requests are 
       enabled using HAL_DAC_Start_DMA().
       [..]
       DMA1 requests are mapped as following:
         (#) DAC1 channel1: mapped either on
         (++) DMA1 channel3 
         (++) or DMA2 channel3 (for STM32F3 devices having 2 DMA)
             which must be already configured
         (#) DAC1 channel2: 
             (for STM32F3 devices having 2 channels on DAC1)
             mapped either on
         (++) DMA1 channel4 
         (++) or DMA2 channel4 (for STM32F3 devices having 2 DMA)
             which must be already configured
      
         (#) DAC2 channel1: mapped either on 
             (for STM32F3 devices having 2 DAC)
         (++) DMA1 channel4 
         (++) or DMA2 channel4 (for STM32F3 devices having 2 DMA)
             which must be already configured
    

       (@) For Dual mode and specific signal (Triangle and noise) generation please 
       refer to Extended Features Driver description        

                      ##### How to use this driver #####
  ==============================================================================
    [..]          
      (+) DAC APB clock must be enabled to get write access to DAC
          registers using HAL_DAC_Init()
      (+) Configure DAC_OUTx (DAC_OUT1: PA4, DAC_OUT2: PA5) in analog mode.
      (+) Configure the DAC channel using HAL_DAC_ConfigChannel() function.
      (+) Enable the DAC channel using HAL_DAC_Start() or HAL_DAC_Start_DMA() functions

     *** Polling mode IO operation ***
     =================================
     [..]    
       (+) Start the DAC peripheral using HAL_DAC_Start() 
       (+) To read the DAC last data output value, use the HAL_DAC_GetValue() function.
       (+) Stop the DAC peripheral using HAL_DAC_Stop()
       
     *** DMA mode IO operation ***    
     ==============================
     [..]    
       (+) Start the DAC peripheral using HAL_DAC_Start_DMA(), at this stage the user specify the length 
           of data to be transferred at each end of conversion
       (+) At the middle of data transfer HAL_DAC_ConvHalfCpltCallbackCh1() or HAL_DACEx_ConvHalfCpltCallbackCh2()  
           function is executed and user can add his own code by customization of function pointer 
           HAL_DAC_ConvHalfCpltCallbackCh1() or HAL_DACEx_ConvHalfCpltCallbackCh2()
       (+) At The end of data transfer HAL_DAC_ConvCpltCallbackCh1() or HAL_DACEx_ConvHalfCpltCallbackCh2()  
           function is executed and user can add his own code by customization of function pointer 
           HAL_DAC_ConvCpltCallbackCh1() or HAL_DACEx_ConvHalfCpltCallbackCh2()
       (+) In case of transfer Error, HAL_DAC_ErrorCallbackCh1() function is executed and user can 
            add his own code by customization of function pointer HAL_DAC_ErrorCallbackCh1
       (+) In case of DMA underrun, DAC interruption triggers and execute internal function HAL_DAC_IRQHandler.
           HAL_DAC_DMAUnderrunCallbackCh1() or HAL_DACEx_DMAUnderrunCallbackCh2()  
           function is executed and user can add his own code by customization of function pointer 
           HAL_DAC_DMAUnderrunCallbackCh1() or HAL_DACEx_DMAUnderrunCallbackCh2() and
           add his own code by customization of function pointer HAL_DAC_ErrorCallbackCh1()
       (+) Stop the DAC peripheral using HAL_DAC_Stop_DMA()

    *** Callback registration ***
    =============================================
    [..]
      The compilation define  USE_HAL_DAC_REGISTER_CALLBACKS when set to 1
      allows the user to configure dynamically the driver callbacks.

    Use Functions HAL_DAC_RegisterCallback() to register a user callback,
      it allows to register following callbacks:
      (+) ConvCpltCallbackCh1     : callback when a half transfer is completed on Ch1.                 
      (+) ConvHalfCpltCallbackCh1 : callback when a transfer is completed on Ch1.
      (+) ErrorCallbackCh1        : callback when an error occurs on Ch1.
      (+) DMAUnderrunCallbackCh1  : callback when an underrun error occurs on Ch1.
      (+) ConvCpltCallbackCh2     : callback when a half transfer is completed on Ch2.   
      (+) ConvHalfCpltCallbackCh2 : callback when a transfer is completed on Ch2.        
      (+) ErrorCallbackCh2        : callback when an error occurs on Ch2.                
      (+) DMAUnderrunCallbackCh2  : callback when an underrun error occurs on Ch2.
      (+) MspInitCallback         : DAC MspInit.  
      (+) MspDeInitCallback       : DAC MspdeInit.
      This function takes as parameters the HAL peripheral handle, the Callback ID
      and a pointer to the user callback function.

    Use function HAL_DAC_UnRegisterCallback() to reset a callback to the default
      weak (surcharged) function. It allows to reset following callbacks:
      (+) ConvCpltCallbackCh1     : callback when a half transfer is completed on Ch1.                 
      (+) ConvHalfCpltCallbackCh1 : callback when a transfer is completed on Ch1.
      (+) ErrorCallbackCh1        : callback when an error occurs on Ch1.
      (+) DMAUnderrunCallbackCh1  : callback when an underrun error occurs on Ch1.
      (+) ConvCpltCallbackCh2     : callback when a half transfer is completed on Ch2.   
      (+) ConvHalfCpltCallbackCh2 : callback when a transfer is completed on Ch2.        
      (+) ErrorCallbackCh2        : callback when an error occurs on Ch2.                
      (+) DMAUnderrunCallbackCh2  : callback when an underrun error occurs on Ch2.
      (+) MspInitCallback         : DAC MspInit.  
      (+) MspDeInitCallback       : DAC MspdeInit.
      (+) All Callbacks
      This function) takes as parameters the HAL peripheral handle and the Callback ID.

      By default, after the HAL_DAC_Init and if the state is HAL_DAC_STATE_RESET
      all callbacks are reset to the corresponding legacy weak (surcharged) functions.
      Exception done for MspInit and MspDeInit callbacks that are respectively
      reset to the legacy weak (surcharged) functions in the HAL_DAC_Init 
      and  HAL_DAC_DeInit only when these callbacks are null (not registered beforehand).
      If not, MspInit or MspDeInit are not null, the HAL_DAC_Init and HAL_DAC_DeInit
      keep and use the user MspInit/MspDeInit callbacks (registered beforehand)

      Callbacks can be registered/unregistered in READY state only.
      Exception done for MspInit/MspDeInit callbacks that can be registered/unregistered
      in READY or RESET state, thus registered (user) MspInit/DeInit callbacks can be used
      during the Init/DeInit.
      In that case first register the MspInit/MspDeInit user callbacks
      using HAL_DAC_RegisterCallback before calling HAL_DAC_DeInit 
      or HAL_DAC_Init function.

      When The compilation define USE_HAL_DAC_REGISTER_CALLBACKS is set to 0 or
      not defined, the callback registering feature is not available 
      and weak (surcharged) callbacks are used.


     *** DAC HAL driver macros list ***
     ============================================= 
     [..]
       Below the list of most used macros in DAC HAL driver.
       
      (+) __HAL_DAC_ENABLE : Enable the DAC peripheral
      (+) __HAL_DAC_DISABLE : Disable the DAC peripheral
      (+) __HAL_DAC_CLEAR_FLAG: Clear the DAC's pending flags
      (+) __HAL_DAC_GET_FLAG: Get the selected DAC's flag status 
      
     [..]
      (@) You can refer to the DAC HAL driver header file for more useful macros  
   
 @endverbatim    
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @defgroup DAC DAC
  * @brief DAC HAL module driver
  * @{
  */ 
 
#ifdef HAL_DAC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/** @defgroup DAC_Private_Macros DAC Private Macros
  * @{
  */
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup DAC_Private_Functions DAC Private Functions
  * @{
  */
/**
  * @}
  */

/* Exported functions -------------------------------------------------------*/
    
/** @defgroup DAC_Exported_Functions DAC Exported Functions
  * @{
  */

/** @defgroup DAC_Exported_Functions_Group1 Initialization and de-initialization functions 
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
  ==============================================================================
              ##### Initialization and de-initialization functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the DAC. 
      (+) De-initialize the DAC. 
         
@endverbatim
  * @{
  */

/**
  * @brief  Initialize the DAC peripheral according to the specified parameters
  *         in the DAC_InitStruct and initialize the associated handle.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_Init(DAC_HandleTypeDef* hdac)
{ 
  /* Check DAC handle */
  if(hdac == NULL)
  {
     return HAL_ERROR;
  }
  /* Check the parameters */
  assert_param(IS_DAC_ALL_INSTANCE(hdac->Instance));
  
  if(hdac->State == HAL_DAC_STATE_RESET)
  {  
#if (USE_HAL_DAC_REGISTER_CALLBACKS == 1)
  /* Init the DAC Callback settings */
  hdac->ConvCpltCallbackCh1           = HAL_DAC_ConvCpltCallbackCh1;    
  hdac->ConvHalfCpltCallbackCh1       = HAL_DAC_ConvHalfCpltCallbackCh1;
  hdac->ErrorCallbackCh1              = HAL_DAC_ErrorCallbackCh1;
  hdac->DMAUnderrunCallbackCh1        = HAL_DAC_DMAUnderrunCallbackCh1;
#if defined(DAC_CHANNEL2_SUPPORT)
  hdac->ConvCpltCallbackCh2           = HAL_DACEx_ConvCpltCallbackCh2;    
  hdac->ConvHalfCpltCallbackCh2       = HAL_DACEx_ConvHalfCpltCallbackCh2;
  hdac->ErrorCallbackCh2              = HAL_DACEx_ErrorCallbackCh2;       
  hdac->DMAUnderrunCallbackCh2        = HAL_DACEx_DMAUnderrunCallbackCh2; 
#endif /* DAC_CHANNEL2_SUPPORT */
  if(hdac->MspInitCallback == NULL)
  {
    hdac->MspInitCallback               = HAL_DAC_MspInit;
  }
  if(hdac->MspDeInitCallback == NULL)
  {
    hdac->MspDeInitCallback             = HAL_DAC_MspDeInit;
  }
#endif /* USE_HAL_DAC_REGISTER_CALLBACKS */
  
    /* Allocate lock resource and initialize it */
    hdac->Lock = HAL_UNLOCKED;

#if (USE_HAL_DAC_REGISTER_CALLBACKS == 1)
    /* Init the low level hardware */
    hdac->MspInitCallback(hdac);
#else
    /* Init the low level hardware */
    HAL_DAC_MspInit(hdac);
#endif /* USE_HAL_DAC_REGISTER_CALLBACKS */
  }
  
  /* Initialize the DAC state*/
  hdac->State = HAL_DAC_STATE_BUSY;
       
  /* Set DAC error code to none */
  hdac->ErrorCode = HAL_DAC_ERROR_NONE;
  
  /* Initialize the DAC state*/
  hdac->State = HAL_DAC_STATE_READY;
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Deinitialize the DAC peripheral registers to their default reset values.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_DeInit(DAC_HandleTypeDef* hdac)
{
  /* Check DAC handle */
  if(hdac == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DAC_ALL_INSTANCE(hdac->Instance));

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_BUSY;
  
#if (USE_HAL_DAC_REGISTER_CALLBACKS == 1)
  if(hdac->MspDeInitCallback == NULL)
  {
    hdac->MspDeInitCallback = HAL_DAC_MspDeInit;
  }
  /* DeInit the low level hardware */
  hdac->MspDeInitCallback(hdac);
  
#else 
  /* DeInit the low level hardware */
  HAL_DAC_MspDeInit(hdac);
#endif /* USE_HAL_DAC_REGISTER_CALLBACKS */
  
  /* Set DAC error code to none */
  hdac->ErrorCode = HAL_DAC_ERROR_NONE;
  
  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hdac);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initialize the DAC MSP.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdac);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_DAC_MspInit could be implemented in the user file
   */ 
}

/**
  * @brief  DeInitialize the DAC MSP.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.  
  * @retval None
  */
__weak void HAL_DAC_MspDeInit(DAC_HandleTypeDef* hdac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdac);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_DAC_MspDeInit could be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup DAC_Exported_Functions_Group2 Input and Output operation functions
 *  @brief    IO operation functions 
 *
@verbatim   
  ==============================================================================
             ##### IO operation functions #####
  ==============================================================================  
    [..]  This section provides functions allowing to:
      (+) Start conversion.
      (+) Stop conversion.
      (+) Start conversion and enable DMA transfer.
      (+) Stop conversion and disable DMA transfer.
      (+) Get result of conversion.
      (+) Get result of dual mode conversion.
                     
@endverbatim
  * @{
  */

/**
  * @brief  Enables DAC and starts conversion of channel.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC1 Channel2 selected  
  *            @arg DAC_CHANNEL_1: DAC2 Channel1 selected  
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdac);
  UNUSED(Channel);

  /* Note : This function is defined into this file for library reference */
  /*        Function content is located into file stm32f3xx_hal_dac_ex.c  */
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Disables DAC and stop conversion of channel.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC1 Channel2 selected  
  *            @arg DAC_CHANNEL_1: DAC2 Channel1 selected  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_Stop(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL_INSTANCE(hdac->Instance, Channel));
  
  /* Disable the Peripheral */
  __HAL_DAC_DISABLE(hdac, Channel);
  
  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_READY;
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Disables DAC and stop conversion of channel.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC1 Channel2 selected  
  *            @arg DAC_CHANNEL_1: DAC2 Channel1 selected    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_Stop_DMA(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;
    
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL_INSTANCE(hdac->Instance, Channel));
  
  /* Disable the selected DAC channel DMA request */
    hdac->Instance->CR &= ~(DAC_CR_DMAEN1 << Channel);
    
  /* Disable the Peripheral */
  __HAL_DAC_DISABLE(hdac, Channel);
  
  /* Disable the DMA channel */
  /* Channel1 is used */
  if (Channel == DAC_CHANNEL_1)
  {
    /* Disable the DMA channel */
    status = HAL_DMA_Abort(hdac->DMA_Handle1);   
    
    /* Disable the DAC DMA underrun interrupt */
    __HAL_DAC_DISABLE_IT(hdac, DAC_IT_DMAUDR1);
  }
#if defined(DAC_CHANNEL2_SUPPORT)
  /* For all products including channel 2U */
  /* DAC channel 2 is available on top of DAC channel 1U */
  else /* Channel2 is used */
  {
    /* Disable the DMA channel */
    status = HAL_DMA_Abort(hdac->DMA_Handle2);   
    
    /* Disable the DAC DMA underrun interrupt */
    __HAL_DAC_DISABLE_IT(hdac, DAC_IT_DMAUDR2);
  }
#endif /* DAC_CHANNEL2_SUPPORT */
    
  /* Check if DMA Channel effectively disabled */
  if (status != HAL_OK)
  {
    /* Update DAC state machine to error */
    hdac->State = HAL_DAC_STATE_ERROR;      
  }
  else
  {
    /* Change DAC state */
    hdac->State = HAL_DAC_STATE_READY;
  }
  
  /* Return function status */
  return status;
}

/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC1 Channel2 selected  
  *            @arg DAC_CHANNEL_1: DAC2 Channel1 selected 
  * @retval The selected DAC channel data output value.
  */
__weak uint32_t HAL_DAC_GetValue(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdac);
  UNUSED(Channel);

  /* Note : This function is defined into this file for library reference */
  /*        Function content is located into file stm32f3xx_hal_dac_ex.c  */

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval The selected DAC channel data output value.
  */
__weak uint32_t HAL_DACEx_DualGetValue(DAC_HandleTypeDef* hdac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdac);

  /* Note : This function is defined into this file for library reference */
  /*        Function content is located into file stm32f3xx_hal_dac_ex.c  */

  /* Return function status */
  return HAL_OK;
}

/**
  * @}
  */
  
/** @defgroup DAC_Exported_Functions_Group3 Peripheral Control functions
 *  @brief    Peripheral Control functions 
 *
@verbatim   
  ==============================================================================
             ##### Peripheral Control functions #####
  ==============================================================================  
    [..]  This section provides functions allowing to:
      (+) Configure channels. 
      (+) Configure Triangle wave generation.
      (+) Configure Noise wave generation.
      (+) Set the specified data holding register value for DAC channel.
      (+) Set the specified data holding register value for Dual DAC channels.
      
@endverbatim
  * @{
  */

/**
  * @brief  Configures the selected DAC channel.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  sConfig DAC configuration structure.
  * @param  Channel The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC1 Channel2 selected  
  *            @arg DAC_CHANNEL_1: DAC2 Channel1 selected 
  * @retval HAL status
  */

__weak HAL_StatusTypeDef HAL_DAC_ConfigChannel(DAC_HandleTypeDef* hdac, DAC_ChannelConfTypeDef* sConfig, uint32_t Channel)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdac);
  UNUSED(sConfig);
  UNUSED(Channel);

  /* Return function status */
  return HAL_OK;
}

__weak HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef* hdac, uint32_t Channel, uint32_t Alignment, uint32_t Data)
{ 
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdac);
  UNUSED(Channel);
  UNUSED(Alignment);
  UNUSED(Data);

  /* Note : This function is defined into this file for library reference */
  /*        Function content is located into file stm32f3xx_hal_dac_ex.c  */

  /* Return function status */
  return HAL_ERROR;
}

__weak HAL_StatusTypeDef HAL_DACEx_DualSetValue(DAC_HandleTypeDef* hdac, uint32_t Alignment, uint32_t Data1, uint32_t Data2)
{ 
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdac);
  UNUSED(Alignment);
  UNUSED(Data1);
  UNUSED(Data2);

  /* Note : This function is defined into this file for library reference */
  /*        Function content is located into file stm32f3xx_hal_dac_ex.c  */

  /* Return function status */
  return HAL_ERROR;
}

/**
  * @}
  */

/** @defgroup DAC_Exported_Functions_Group4 Peripheral State and Error functions
 *  @brief   DAC Peripheral State and Error functions 
 *
@verbatim   
  ==============================================================================
            ##### DAC Peripheral State and Error functions #####
  ==============================================================================  
    [..]
    This subsection provides functions allowing to
      (+) Check the DAC state.
      (+) Check the DAC Errors.

        
@endverbatim
  * @{
  */

/**
  * @brief  return the DAC handle state
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval HAL state
  */
HAL_DAC_StateTypeDef HAL_DAC_GetState(DAC_HandleTypeDef* hdac)
{
  /* Return DAC handle state */
  return hdac->State;
}

/**
  * @brief  Return the DAC error code
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval DAC Error Code
  */
uint32_t HAL_DAC_GetError(DAC_HandleTypeDef *hdac)
{
  return hdac->ErrorCode;
}

/**
  * @}
  */

/** @addtogroup DAC_Exported_Functions_Group2 Input and Output operation functions
  * @{
  */

/**
  * @brief  Conversion complete callback in non blocking mode for Channel1 
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdac);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DAC_ConvCpltCallback1 could be implemented in the user file
   */
}

/**
  * @brief  Conversion half DMA transfer callback in non blocking mode for Channel1 
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DAC_ConvHalfCpltCallbackCh1(DAC_HandleTypeDef* hdac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdac);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DAC_ConvHalfCpltCallbackCh1 could be implemented in the user file
   */
}

/**
  * @brief  Error DAC callback for Channel1.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DAC_ErrorCallbackCh1(DAC_HandleTypeDef *hdac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdac);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DAC_ErrorCallback could be implemented in the user file
   */
}


/**
  * @brief  DMA underrun DAC callback for Channel1.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DAC_DMAUnderrunCallbackCh1(DAC_HandleTypeDef *hdac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdac);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DAC_DMAUnderrunCallbackCh1 could be implemented in the user file
   */
}

/**
  * @}
  */

/**
  * @}
  */

#if (USE_HAL_DAC_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User DAC Callback
  *         To be used instead of the weak (surcharged) predefined callback 
  * @param hdac : DAC handle
  * @param CallbackId : ID of the callback to be registered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_DAC_ERROR_INVALID_CALLBACK   DAC Error Callback ID
  *          @arg @ref HAL_DAC_CH1_COMPLETE_CB_ID       DAC CH1 Complete Callback ID
  *          @arg @ref HAL_DAC_CH1_HALF_COMPLETE_CB_ID  DAC CH1 Half Complete Callback ID
  *          @arg @ref HAL_DAC_CH1_ERROR_ID             DAC CH1 Error Callback ID
  *          @arg @ref HAL_DAC_CH1_UNDERRUN_CB_ID       DAC CH1 UnderRun Callback ID
  *          @arg @ref HAL_DAC_CH2_COMPLETE_CB_ID       DAC CH2 Complete Callback ID      
  *          @arg @ref HAL_DAC_CH2_HALF_COMPLETE_CB_ID  DAC CH2 Half Complete Callback ID 
  *          @arg @ref HAL_DAC_CH2_ERROR_ID             DAC CH2 Error Callback ID         
  *          @arg @ref HAL_DAC_CH2_UNDERRUN_CB_ID       DAC CH2 UnderRun Callback ID         
  *          @arg @ref HAL_DAC_MSP_INIT_CB_ID           DAC MSP Init Callback ID        
  *          @arg @ref HAL_DAC_MSP_DEINIT_CB_ID         DAC MSP DeInit Callback ID   
  *
    * @param pCallback : pointer to the Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_DAC_RegisterCallback (DAC_HandleTypeDef *hdac, HAL_DAC_CallbackIDTypeDef CallbackId, pDAC_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if(pCallback == NULL)
  {
    /* Update the error code */
    hdac->ErrorCode |= HAL_DAC_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hdac);
  
  if(hdac->State == HAL_DAC_STATE_READY)
  {
    switch (CallbackId)
    {
    case HAL_DAC_CH1_COMPLETE_CB_ID :
      hdac->ConvCpltCallbackCh1 = pCallback;
      break;
    case HAL_DAC_CH1_HALF_COMPLETE_CB_ID :
      hdac->ConvHalfCpltCallbackCh1 = pCallback;
      break;
    case HAL_DAC_CH1_ERROR_ID :
      hdac->ErrorCallbackCh1 = pCallback;
      break;
    case HAL_DAC_CH1_UNDERRUN_CB_ID :
      hdac->DMAUnderrunCallbackCh1 = pCallback;
      break;
    case HAL_DAC_CH2_COMPLETE_CB_ID :
      hdac->ConvCpltCallbackCh2 = pCallback;
      break;
    case HAL_DAC_CH2_HALF_COMPLETE_CB_ID :
      hdac->ConvHalfCpltCallbackCh2 = pCallback;
      break;
    case HAL_DAC_CH2_ERROR_ID :
      hdac->ErrorCallbackCh2 = pCallback;
      break;
    case HAL_DAC_CH2_UNDERRUN_CB_ID :
      hdac->DMAUnderrunCallbackCh2 = pCallback;
      break;
    case HAL_DAC_MSP_INIT_CB_ID :
      hdac->MspInitCallback = pCallback;
      break;
    case HAL_DAC_MSP_DEINIT_CB_ID :
      hdac->MspDeInitCallback = pCallback;
      break;
    default :
      /* Update the error code */
      hdac->ErrorCode |= HAL_DAC_ERROR_INVALID_CALLBACK; 
      /* update return status */
      status =  HAL_ERROR;
      break;
    }
  }
  else if (hdac->State == HAL_DAC_STATE_RESET)
  {
    switch (CallbackId)
    {
    case HAL_DAC_MSP_INIT_CB_ID :
      hdac->MspInitCallback = pCallback;
      break;
    case HAL_DAC_MSP_DEINIT_CB_ID :
      hdac->MspDeInitCallback = pCallback;
      break;
    default :
      /* Update the error code */
      hdac->ErrorCode |= HAL_DAC_ERROR_INVALID_CALLBACK; 
      /* update return status */
      status =  HAL_ERROR;
      break;
    }
  }
  else
  {
    /* Update the error code */
    hdac->ErrorCode |= HAL_DAC_ERROR_INVALID_CALLBACK; 
    /* update return status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hdac);
  return status;
}

/**
  * @brief  Unregister a User DAC Callback
  *         DAC Callback is redirected to the weak (surcharged) predefined callback 
  * @param hdac : DAC handle
  * @param CallbackId : ID of the callback to be unregistered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_DAC_CH1_COMPLETE_CB_ID          DAC CH1 tranfer Complete Callback ID     
  *          @arg @ref HAL_DAC_CH1_HALF_COMPLETE_CB_ID     DAC CH1 Half Complete Callback ID        
  *          @arg @ref HAL_DAC_CH1_ERROR_ID                DAC CH1 Error Callback ID                
  *          @arg @ref HAL_DMA_CH1_UNDERRUN_CB_ID          DAC CH1 UnderRun Callback ID             
  *          @arg @ref HAL_DAC_CH2_COMPLETE_CB_ID          DAC CH2 Complete Callback ID             
  *          @arg @ref HAL_DAC_CH2_HALF_COMPLETE_CB_ID     DAC CH2 Half Complete Callback ID        
  *          @arg @ref HAL_DAC_CH2_ERROR_ID                DAC CH2 Error Callback ID                
  *          @arg @ref HAL_DMA_CH2_UNDERRUN_CB_ID          DAC CH2 UnderRun Callback ID             
  *          @arg @ref HAL_DAC_MSP_INIT_CB_ID              DAC MSP Init Callback ID                 
  *          @arg @ref HAL_DAC_MSP_DEINIT_CB_ID            DAC MSP DeInit Callback ID               
  *          @arg @ref HAL_DAC_ALL_CB_ID                   DAC All callbacks
  * @retval status
  */
HAL_StatusTypeDef HAL_DAC_UnRegisterCallback (DAC_HandleTypeDef *hdac, HAL_DAC_CallbackIDTypeDef CallbackId)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hdac);
  
  if(hdac->State == HAL_DAC_STATE_READY)
  {
    switch (CallbackId)
    {
    case HAL_DAC_CH1_COMPLETE_CB_ID :
      hdac->ConvCpltCallbackCh1 = HAL_DAC_ConvCpltCallbackCh1;
      break;
    case HAL_DAC_CH1_HALF_COMPLETE_CB_ID :
      hdac->ConvHalfCpltCallbackCh1 = HAL_DAC_ConvHalfCpltCallbackCh1;
      break;
    case HAL_DAC_CH1_ERROR_ID :
      hdac->ErrorCallbackCh1 = HAL_DAC_ErrorCallbackCh1;
      break;
    case HAL_DAC_CH1_UNDERRUN_CB_ID :
      hdac->DMAUnderrunCallbackCh1 = HAL_DAC_DMAUnderrunCallbackCh1;
      break;
#if defined(DAC_CHANNEL2_SUPPORT)
    case HAL_DAC_CH2_COMPLETE_CB_ID :
      hdac->ConvCpltCallbackCh2 = HAL_DACEx_ConvCpltCallbackCh2;
      break;
    case HAL_DAC_CH2_HALF_COMPLETE_CB_ID :
      hdac->ConvHalfCpltCallbackCh2 = HAL_DACEx_ConvHalfCpltCallbackCh2;
      break;
    case HAL_DAC_CH2_ERROR_ID :
      hdac->ErrorCallbackCh2 = HAL_DACEx_ErrorCallbackCh2;
      break;
    case HAL_DAC_CH2_UNDERRUN_CB_ID :
      hdac->DMAUnderrunCallbackCh2 = HAL_DACEx_DMAUnderrunCallbackCh2;
      break;
#endif /* DAC_CHANNEL2_SUPPORT */
    case HAL_DAC_MSP_INIT_CB_ID :
      hdac->MspInitCallback = HAL_DAC_MspInit;
      break;
    case HAL_DAC_MSP_DEINIT_CB_ID :
      hdac->MspDeInitCallback = HAL_DAC_MspDeInit;
      break;
    case HAL_DAC_ALL_CB_ID :
      hdac->ConvCpltCallbackCh1 = HAL_DAC_ConvCpltCallbackCh1;
      hdac->ConvHalfCpltCallbackCh1 = HAL_DAC_ConvHalfCpltCallbackCh1;
      hdac->ErrorCallbackCh1 = HAL_DAC_ErrorCallbackCh1;
      hdac->DMAUnderrunCallbackCh1 = HAL_DAC_DMAUnderrunCallbackCh1;
#if defined(DAC_CHANNEL2_SUPPORT)
      hdac->ConvCpltCallbackCh2 = HAL_DACEx_ConvCpltCallbackCh2;
      hdac->ConvHalfCpltCallbackCh2 = HAL_DACEx_ConvHalfCpltCallbackCh2;
      hdac->ErrorCallbackCh2 = HAL_DACEx_ErrorCallbackCh2;
      hdac->DMAUnderrunCallbackCh2 = HAL_DACEx_DMAUnderrunCallbackCh2;
#endif /* DAC_CHANNEL2_SUPPORT */
      hdac->MspInitCallback = HAL_DAC_MspInit;
      hdac->MspDeInitCallback = HAL_DAC_MspDeInit;
      break;
    default :
      /* Update the error code */
      hdac->ErrorCode |= HAL_DAC_ERROR_INVALID_CALLBACK; 
      /* update return status */
      status =  HAL_ERROR;
      break;
    }
  }
  else if (hdac->State == HAL_DAC_STATE_RESET)
  {
    switch (CallbackId)
    {
    case HAL_DAC_MSP_INIT_CB_ID :
      hdac->MspInitCallback = HAL_DAC_MspInit;
      break;
    case HAL_DAC_MSP_DEINIT_CB_ID :
      hdac->MspDeInitCallback = HAL_DAC_MspDeInit;
      break;
    default :
      /* Update the error code */
      hdac->ErrorCode |= HAL_DAC_ERROR_INVALID_CALLBACK; 
      /* update return status */
      status =  HAL_ERROR;
      break;
    }
  }
  else
  {
    /* Update the error code */
    hdac->ErrorCode |= HAL_DAC_ERROR_INVALID_CALLBACK; 
    /* update return status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hdac);
  return status;
}
#endif /* USE_HAL_DAC_REGISTER_CALLBACKS */

#endif /* HAL_DAC_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
