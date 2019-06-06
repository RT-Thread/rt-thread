/**
  ******************************************************************************
  * @file    stm32f7xx_hal_ltdc.c
  * @author  MCD Application Team
  * @brief   LTDC HAL module driver.
<<<<<<< HEAD
  *          This file provides firmware functions to manage the following 
  *          functionalities of the LTDC peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions  
  *           + Peripheral State and Errors functions
  *           
  @verbatim      
=======
  *          This file provides firmware functions to manage the following
  *          functionalities of the LTDC peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
  *
  @verbatim
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
<<<<<<< HEAD
     (#) Program the required configuration through the following parameters:   
         the LTDC timing, the horizontal and vertical polarity, 
         the pixel clock polarity, Data Enable polarity and the LTDC background color value 
         using HAL_LTDC_Init() function

     (#) Program the required configuration through the following parameters:   
         the pixel format, the blending factors, input alpha value, the window size 
         and the image size using HAL_LTDC_ConfigLayer() function for foreground
         or/and background layer.     
  
     (#) Optionally, configure and enable the CLUT using HAL_LTDC_ConfigCLUT() and 
         HAL_LTDC_EnableCLUT functions.
       
     (#) Optionally, enable the Dither using HAL_LTDC_EnableDither().       
=======
     (#) Program the required configuration through the following parameters:
         the LTDC timing, the horizontal and vertical polarity,
         the pixel clock polarity, Data Enable polarity and the LTDC background color value
         using HAL_LTDC_Init() function

     (#) Program the required configuration through the following parameters:
         the pixel format, the blending factors, input alpha value, the window size
         and the image size using HAL_LTDC_ConfigLayer() function for foreground
         or/and background layer.

     (#) Optionally, configure and enable the CLUT using HAL_LTDC_ConfigCLUT() and
         HAL_LTDC_EnableCLUT functions.

     (#) Optionally, enable the Dither using HAL_LTDC_EnableDither().
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

     (#) Optionally, configure and enable the Color keying using HAL_LTDC_ConfigColorKeying()
         and HAL_LTDC_EnableColorKeying functions.

     (#) Optionally, configure LineInterrupt using HAL_LTDC_ProgramLineEvent()
         function

     (#) If needed, reconfigure and change the pixel format value, the alpha value
<<<<<<< HEAD
         value, the window size, the window position and the layer start address 
         for foreground or/and background layer using respectively the following 
         functions: HAL_LTDC_SetPixelFormat(), HAL_LTDC_SetAlpha(), HAL_LTDC_SetWindowSize(),
         HAL_LTDC_SetWindowPosition(), HAL_LTDC_SetAddress.

     (#) Variant functions with "_NoReload" post fix allows to set the LTDC configuration/settings without immediate reload.
         This is useful in case when the program requires to modify serval LTDC settings (on one or both layers) 
         then applying(reload) these settings in one shot by calling the function "HAL_LTDC_Reload"

         After calling the "_NoReload" functions to set different color/format/layer settings, 
         the program can call the function "HAL_LTDC_Reload" To apply(Reload) these settings. 
         Function "HAL_LTDC_Reload" can be called with the parameter "ReloadType" 
         set to LTDC_RELOAD_IMMEDIATE if an immediate reload is required.
         Function "HAL_LTDC_Reload" can be called with the parameter "ReloadType" 
         set to LTDC_RELOAD_VERTICAL_BLANKING if the reload should be done in the next vertical blanking period, 
         this option allows to avoid display flicker by applying the new settings during the vertical blanking period.
           
                     
     (#) To control LTDC state you can use the following function: HAL_LTDC_GetState()               

     *** LTDC HAL driver macros list ***
     ============================================= 
     [..]
       Below the list of most used macros in LTDC HAL driver.
       
      (+) __HAL_LTDC_ENABLE: Enable the LTDC.
      (+) __HAL_LTDC_DISABLE: Disable the LTDC.
      (+) __HAL_LTDC_LAYER_ENABLE: Enable the LTDC Layer.
      (+) __HAL_LTDC_LAYER_DISABLE: Disable the LTDC Layer.
      (+) __HAL_LTDC_RELOAD_CONFIG: Reload  Layer Configuration.
      (+) __HAL_LTDC_GET_FLAG: Get the LTDC pending flags.
      (+) __HAL_LTDC_CLEAR_FLAG: Clear the LTDC pending flags.
      (+) __HAL_LTDC_ENABLE_IT: Enable the specified LTDC interrupts. 
      (+) __HAL_LTDC_DISABLE_IT: Disable the specified LTDC interrupts.
      (+) __HAL_LTDC_GET_IT_SOURCE: Check whether the specified LTDC interrupt has occurred or not.
      
     [..] 
       (@) You can refer to the LTDC HAL driver header file for more useful macros
  
=======
         value, the window size, the window position and the layer start address
         for foreground or/and background layer using respectively the following
         functions: HAL_LTDC_SetPixelFormat(), HAL_LTDC_SetAlpha(), HAL_LTDC_SetWindowSize(),
         HAL_LTDC_SetWindowPosition() and HAL_LTDC_SetAddress().

     (#) Variant functions with _NoReload suffix allows to set the LTDC configuration/settings without immediate reload.
         This is useful in case when the program requires to modify serval LTDC settings (on one or both layers)
         then applying(reload) these settings in one shot by calling the function HAL_LTDC_Reload().

         After calling the _NoReload functions to set different color/format/layer settings,
         the program shall call the function HAL_LTDC_Reload() to apply(reload) these settings.
         Function HAL_LTDC_Reload() can be called with the parameter ReloadType set to LTDC_RELOAD_IMMEDIATE if
         an immediate reload is required.
         Function HAL_LTDC_Reload() can be called with the parameter ReloadType set to LTDC_RELOAD_VERTICAL_BLANKING if
         the reload should be done in the next vertical blanking period,
         this option allows to avoid display flicker by applying the new settings during the vertical blanking period.


     (#) To control LTDC state you can use the following function: HAL_LTDC_GetState()

     *** LTDC HAL driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in LTDC HAL driver.

      (+) __HAL_LTDC_ENABLE: Enable the LTDC.
      (+) __HAL_LTDC_DISABLE: Disable the LTDC.
      (+) __HAL_LTDC_LAYER_ENABLE: Enable an LTDC Layer.
      (+) __HAL_LTDC_LAYER_DISABLE: Disable an LTDC Layer.
      (+) __HAL_LTDC_RELOAD_IMMEDIATE_CONFIG: Reload  Layer Configuration.
      (+) __HAL_LTDC_GET_FLAG: Get the LTDC pending flags.
      (+) __HAL_LTDC_CLEAR_FLAG: Clear the LTDC pending flags.
      (+) __HAL_LTDC_ENABLE_IT: Enable the specified LTDC interrupts.
      (+) __HAL_LTDC_DISABLE_IT: Disable the specified LTDC interrupts.
      (+) __HAL_LTDC_GET_IT_SOURCE: Check whether the specified LTDC interrupt has occurred or not.


  *** Callback registration ***
  =============================================

  The compilation define  USE_HAL_LTDC_REGISTER_CALLBACKS when set to 1
  allows the user to configure dynamically the driver callbacks.
  Use Function @ref HAL_LTDC_RegisterCallback() to register a callback.

  Function @ref HAL_LTDC_RegisterCallback() allows to register following callbacks:
    (+) LineEventCallback   : LTDC Line Event Callback.
    (+) ReloadEventCallback : LTDC Reload Event Callback.
    (+) ErrorCallback       : LTDC Error Callback
    (+) MspInitCallback     : LTDC MspInit.
    (+) MspDeInitCallback   : LTDC MspDeInit.
  This function takes as parameters the HAL peripheral handle, the Callback ID
  and a pointer to the user callback function.

  Use function @ref HAL_LTDC_UnRegisterCallback() to reset a callback to the default
  weak function.
  @ref HAL_LTDC_UnRegisterCallback takes as parameters the HAL peripheral handle,
  and the Callback ID.
  This function allows to reset following callbacks:
    (+) LineEventCallback   : LTDC Line Event Callback.
    (+) ReloadEventCallback : LTDC Reload Event Callback.
    (+) ErrorCallback       : LTDC Error Callback
    (+) MspInitCallback     : LTDC MspInit.
    (+) MspDeInitCallback   : LTDC MspDeInit.

  By default, after the HAL_LTDC_Init and when the state is HAL_LTDC_STATE_RESET
  all callbacks are set to the corresponding weak functions:
  examples @ref HAL_LTDC_LineEventCallback(), @ref HAL_LTDC_ErrorCallback().
  Exception done for MspInit and MspDeInit functions that are
  reset to the legacy weak function in the HAL_LTDC_Init/ @ref HAL_LTDC_DeInit only when
  these callbacks are null (not registered beforehand).
  if not, MspInit or MspDeInit are not null, the @ref HAL_LTDC_Init/ @ref HAL_LTDC_DeInit
  keep and use the user MspInit/MspDeInit callbacks (registered beforehand)

  Callbacks can be registered/unregistered in HAL_LTDC_STATE_READY state only.
  Exception done MspInit/MspDeInit that can be registered/unregistered
  in HAL_LTDC_STATE_READY or HAL_LTDC_STATE_RESET state,
  thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
  In that case first register the MspInit/MspDeInit user callbacks
  using @ref HAL_LTDC_RegisterCallback() before calling @ref HAL_LTDC_DeInit
  or HAL_LTDC_Init function.

  When The compilation define USE_HAL_LTDC_REGISTER_CALLBACKS is set to 0 or
  not defined, the callback registration feature is not available and all callbacks
  are set to the corresponding weak functions.

     [..]
       (@) You can refer to the LTDC HAL driver header file for more useful macros

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  @endverbatim
  ******************************************************************************
  * @attention
  *
<<<<<<< HEAD
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 
=======
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

<<<<<<< HEAD
/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */
#if defined (STM32F746xx) || defined (STM32F756xx) || defined (STM32F767xx) || defined (STM32F769xx) || defined (STM32F777xx) || defined (STM32F779xx) || defined (STM32F750xx)
=======
#ifdef HAL_LTDC_MODULE_ENABLED
#if defined (LTDC)
/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

/** @defgroup LTDC LTDC
  * @brief LTDC HAL module driver
  * @{
  */

<<<<<<< HEAD
#ifdef HAL_LTDC_MODULE_ENABLED
=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
<<<<<<< HEAD
/* Private variables ---------------------------------------------------------*/    
=======
/* Private variables ---------------------------------------------------------*/
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/* Private function prototypes -----------------------------------------------*/
static void LTDC_SetConfig(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx);
/* Private functions ---------------------------------------------------------*/

/** @defgroup LTDC_Exported_Functions LTDC Exported Functions
  * @{
  */

/** @defgroup LTDC_Exported_Functions_Group1 Initialization and Configuration functions
<<<<<<< HEAD
 *  @brief   Initialization and Configuration functions
 *
@verbatim   
 ===============================================================================
                ##### Initialization and Configuration functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the LTDC
      (+) De-initialize the LTDC 
=======
  *  @brief   Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
                ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the LTDC
      (+) De-initialize the LTDC
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

@endverbatim
  * @{
  */
<<<<<<< HEAD
  
/**
  * @brief  Initializes the LTDC according to the specified
  *         parameters in the LTDC_InitTypeDef and create the associated handle.
  * @param  hltdc pointer to a LTDC_HandleTypeDef structure that contains
=======

/**
  * @brief  Initialize the LTDC according to the specified parameters in the LTDC_InitTypeDef.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *                the configuration information for the LTDC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_Init(LTDC_HandleTypeDef *hltdc)
{
<<<<<<< HEAD
  uint32_t tmp = 0, tmp1 = 0;

  /* Check the LTDC peripheral state */
  if(hltdc == NULL)
=======
  uint32_t tmp, tmp1;

  /* Check the LTDC peripheral state */
  if (hltdc == NULL)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  {
    return HAL_ERROR;
  }

  /* Check function parameters */
  assert_param(IS_LTDC_ALL_INSTANCE(hltdc->Instance));
  assert_param(IS_LTDC_HSYNC(hltdc->Init.HorizontalSync));
  assert_param(IS_LTDC_VSYNC(hltdc->Init.VerticalSync));
  assert_param(IS_LTDC_AHBP(hltdc->Init.AccumulatedHBP));
  assert_param(IS_LTDC_AVBP(hltdc->Init.AccumulatedVBP));
  assert_param(IS_LTDC_AAH(hltdc->Init.AccumulatedActiveH));
  assert_param(IS_LTDC_AAW(hltdc->Init.AccumulatedActiveW));
  assert_param(IS_LTDC_TOTALH(hltdc->Init.TotalHeigh));
  assert_param(IS_LTDC_TOTALW(hltdc->Init.TotalWidth));
  assert_param(IS_LTDC_HSPOL(hltdc->Init.HSPolarity));
  assert_param(IS_LTDC_VSPOL(hltdc->Init.VSPolarity));
  assert_param(IS_LTDC_DEPOL(hltdc->Init.DEPolarity));
  assert_param(IS_LTDC_PCPOL(hltdc->Init.PCPolarity));

<<<<<<< HEAD
  if(hltdc->State == HAL_LTDC_STATE_RESET)
=======
#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
  if (hltdc->State == HAL_LTDC_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hltdc->Lock = HAL_UNLOCKED;

    /* Reset the LTDC callback to the legacy weak callbacks */
    hltdc->LineEventCallback   = HAL_LTDC_LineEventCallback;    /* Legacy weak LineEventCallback    */
    hltdc->ReloadEventCallback = HAL_LTDC_ReloadEventCallback;  /* Legacy weak ReloadEventCallback  */
    hltdc->ErrorCallback       = HAL_LTDC_ErrorCallback;        /* Legacy weak ErrorCallback        */

    if (hltdc->MspInitCallback == NULL)
    {
      hltdc->MspInitCallback = HAL_LTDC_MspInit;
    }
    /* Init the low level hardware */
    hltdc->MspInitCallback(hltdc);
  }
#else
  if (hltdc->State == HAL_LTDC_STATE_RESET)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  {
    /* Allocate lock resource and initialize it */
    hltdc->Lock = HAL_UNLOCKED;
    /* Init the low level hardware */
    HAL_LTDC_MspInit(hltdc);
  }
<<<<<<< HEAD
  
  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Configures the HS, VS, DE and PC polarity */
  hltdc->Instance->GCR &= ~(LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_DEPOL | LTDC_GCR_PCPOL);
  hltdc->Instance->GCR |=  (uint32_t)(hltdc->Init.HSPolarity | hltdc->Init.VSPolarity | \
  hltdc->Init.DEPolarity | hltdc->Init.PCPolarity);

  /* Sets Synchronization size */
  hltdc->Instance->SSCR &= ~(LTDC_SSCR_VSH | LTDC_SSCR_HSW);
  tmp = (hltdc->Init.HorizontalSync << 16);
  hltdc->Instance->SSCR |= (tmp | hltdc->Init.VerticalSync);

  /* Sets Accumulated Back porch */
  hltdc->Instance->BPCR &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
  tmp = (hltdc->Init.AccumulatedHBP << 16);
  hltdc->Instance->BPCR |= (tmp | hltdc->Init.AccumulatedVBP);

  /* Sets Accumulated Active Width */
  hltdc->Instance->AWCR &= ~(LTDC_AWCR_AAH | LTDC_AWCR_AAW);
  tmp = (hltdc->Init.AccumulatedActiveW << 16);
  hltdc->Instance->AWCR |= (tmp | hltdc->Init.AccumulatedActiveH);

  /* Sets Total Width */
  hltdc->Instance->TWCR &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
  tmp = (hltdc->Init.TotalWidth << 16);
  hltdc->Instance->TWCR |= (tmp | hltdc->Init.TotalHeigh);

  /* Sets the background color value */
  tmp = ((uint32_t)(hltdc->Init.Backcolor.Green) << 8);
  tmp1 = ((uint32_t)(hltdc->Init.Backcolor.Red) << 16);
  hltdc->Instance->BCCR &= ~(LTDC_BCCR_BCBLUE | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCRED);
  hltdc->Instance->BCCR |= (tmp1 | tmp | hltdc->Init.Backcolor.Blue);

  /* Enable the transfer Error interrupt */
  __HAL_LTDC_ENABLE_IT(hltdc, LTDC_IT_TE);

  /* Enable the FIFO underrun interrupt */
  __HAL_LTDC_ENABLE_IT(hltdc, LTDC_IT_FU);
=======
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Configure the HS, VS, DE and PC polarity */
  hltdc->Instance->GCR &= ~(LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_DEPOL | LTDC_GCR_PCPOL);
  hltdc->Instance->GCR |= (uint32_t)(hltdc->Init.HSPolarity | hltdc->Init.VSPolarity | \
                                     hltdc->Init.DEPolarity | hltdc->Init.PCPolarity);

  /* Set Synchronization size */
  hltdc->Instance->SSCR &= ~(LTDC_SSCR_VSH | LTDC_SSCR_HSW);
  tmp = (hltdc->Init.HorizontalSync << 16U);
  hltdc->Instance->SSCR |= (tmp | hltdc->Init.VerticalSync);

  /* Set Accumulated Back porch */
  hltdc->Instance->BPCR &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
  tmp = (hltdc->Init.AccumulatedHBP << 16U);
  hltdc->Instance->BPCR |= (tmp | hltdc->Init.AccumulatedVBP);

  /* Set Accumulated Active Width */
  hltdc->Instance->AWCR &= ~(LTDC_AWCR_AAH | LTDC_AWCR_AAW);
  tmp = (hltdc->Init.AccumulatedActiveW << 16U);
  hltdc->Instance->AWCR |= (tmp | hltdc->Init.AccumulatedActiveH);

  /* Set Total Width */
  hltdc->Instance->TWCR &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
  tmp = (hltdc->Init.TotalWidth << 16U);
  hltdc->Instance->TWCR |= (tmp | hltdc->Init.TotalHeigh);

  /* Set the background color value */
  tmp = ((uint32_t)(hltdc->Init.Backcolor.Green) << 8U);
  tmp1 = ((uint32_t)(hltdc->Init.Backcolor.Red) << 16U);
  hltdc->Instance->BCCR &= ~(LTDC_BCCR_BCBLUE | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCRED);
  hltdc->Instance->BCCR |= (tmp1 | tmp | hltdc->Init.Backcolor.Blue);

  /* Enable the Transfer Error and FIFO underrun interrupts */
  __HAL_LTDC_ENABLE_IT(hltdc, LTDC_IT_TE | LTDC_IT_FU);
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Enable LTDC by setting LTDCEN bit */
  __HAL_LTDC_ENABLE(hltdc);

  /* Initialize the error code */
<<<<<<< HEAD
  hltdc->ErrorCode = HAL_LTDC_ERROR_NONE;  
=======
  hltdc->ErrorCode = HAL_LTDC_ERROR_NONE;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Initialize the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  return HAL_OK;
}

/**
<<<<<<< HEAD
  * @brief  Deinitializes the LTDC peripheral registers to their default reset
  *         values.
  * @param  hltdc pointer to a LTDC_HandleTypeDef structure that contains
=======
  * @brief  De-initialize the LTDC peripheral.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *                the configuration information for the LTDC.
  * @retval None
  */

HAL_StatusTypeDef HAL_LTDC_DeInit(LTDC_HandleTypeDef *hltdc)
{
<<<<<<< HEAD
  /* DeInit the low level hardware */
  HAL_LTDC_MspDeInit(hltdc); 
=======
#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
  if (hltdc->MspDeInitCallback == NULL)
  {
    hltdc->MspDeInitCallback = HAL_LTDC_MspDeInit;
  }
  /* DeInit the low level hardware */
  hltdc->MspDeInitCallback(hltdc);
#else
  /* DeInit the low level hardware */
  HAL_LTDC_MspDeInit(hltdc);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Initialize the error code */
  hltdc->ErrorCode = HAL_LTDC_ERROR_NONE;

  /* Initialize the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
<<<<<<< HEAD
  * @brief  Initializes the LTDC MSP.
=======
  * @brief  Initialize the LTDC MSP.
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval None
  */
<<<<<<< HEAD
__weak void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);
  
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_LTDC_MspInit could be implemented in the user file
   */ 
}

/**
  * @brief  DeInitializes the LTDC MSP.
=======
__weak void HAL_LTDC_MspInit(LTDC_HandleTypeDef *hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_LTDC_MspInit could be implemented in the user file
   */
}

/**
  * @brief  De-initialize the LTDC MSP.
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval None
  */
<<<<<<< HEAD
__weak void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);
  
  /* NOTE : This function Should not be modified, when the callback is needed,
=======
__weak void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef *hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);

  /* NOTE : This function should not be modified, when the callback is needed,
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
            the HAL_LTDC_MspDeInit could be implemented in the user file
   */
}

<<<<<<< HEAD
/**
  * @}
  */
  
/** @defgroup LTDC_Exported_Functions_Group2 IO operation functions 
 *  @brief   IO operation functions  
 *
@verbatim
 ===============================================================================
                      #####  IO operation functions  #####
 ===============================================================================  
=======
#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User LTDC Callback
  *         To be used instead of the weak predefined callback
  * @param hltdc ltdc handle
  * @param CallbackID ID of the callback to be registered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_LTDC_LINE_EVENT_CB_ID Line Event Callback ID
  *          @arg @ref HAL_LTDC_RELOAD_EVENT_CB_ID Reload Event Callback ID
  *          @arg @ref HAL_LTDC_ERROR_CB_ID Error Callback ID
  *          @arg @ref HAL_LTDC_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_LTDC_MSPDEINIT_CB_ID MspDeInit callback ID
  * @param pCallback pointer to the Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_LTDC_RegisterCallback(LTDC_HandleTypeDef *hltdc, HAL_LTDC_CallbackIDTypeDef CallbackID, pLTDC_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hltdc->ErrorCode |= HAL_LTDC_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }
  /* Process locked */
  __HAL_LOCK(hltdc);

  if (hltdc->State == HAL_LTDC_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_LTDC_LINE_EVENT_CB_ID :
        hltdc->LineEventCallback = pCallback;
        break;

      case HAL_LTDC_RELOAD_EVENT_CB_ID :
        hltdc->ReloadEventCallback = pCallback;
        break;

      case HAL_LTDC_ERROR_CB_ID :
        hltdc->ErrorCallback = pCallback;
        break;

      case HAL_LTDC_MSPINIT_CB_ID :
        hltdc->MspInitCallback = pCallback;
        break;

      case HAL_LTDC_MSPDEINIT_CB_ID :
        hltdc->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hltdc->ErrorCode |= HAL_LTDC_ERROR_INVALID_CALLBACK;
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hltdc->State == HAL_LTDC_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_LTDC_MSPINIT_CB_ID :
        hltdc->MspInitCallback = pCallback;
        break;

      case HAL_LTDC_MSPDEINIT_CB_ID :
        hltdc->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hltdc->ErrorCode |= HAL_LTDC_ERROR_INVALID_CALLBACK;
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hltdc->ErrorCode |= HAL_LTDC_ERROR_INVALID_CALLBACK;
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hltdc);

  return status;
}

/**
  * @brief  Unregister an LTDC Callback
  *         LTDC callabck is redirected to the weak predefined callback
  * @param hltdc ltdc handle
  * @param CallbackID ID of the callback to be unregistered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_LTDC_LINE_EVENT_CB_ID Line Event Callback ID
  *          @arg @ref HAL_LTDC_RELOAD_EVENT_CB_ID Reload Event Callback ID
  *          @arg @ref HAL_LTDC_ERROR_CB_ID Error Callback ID
  *          @arg @ref HAL_LTDC_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_LTDC_MSPDEINIT_CB_ID MspDeInit callback ID
  * @retval status
  */
HAL_StatusTypeDef HAL_LTDC_UnRegisterCallback(LTDC_HandleTypeDef *hltdc, HAL_LTDC_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hltdc);

  if (hltdc->State == HAL_LTDC_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_LTDC_LINE_EVENT_CB_ID :
        hltdc->LineEventCallback = HAL_LTDC_LineEventCallback;      /* Legacy weak LineEventCallback    */
        break;

      case HAL_LTDC_RELOAD_EVENT_CB_ID :
        hltdc->ReloadEventCallback = HAL_LTDC_ReloadEventCallback;  /* Legacy weak ReloadEventCallback  */
        break;

      case HAL_LTDC_ERROR_CB_ID :
        hltdc->ErrorCallback       = HAL_LTDC_ErrorCallback;        /* Legacy weak ErrorCallback        */
        break;

      case HAL_LTDC_MSPINIT_CB_ID :
        hltdc->MspInitCallback = HAL_LTDC_MspInit;                  /* Legcay weak MspInit Callback     */
        break;

      case HAL_LTDC_MSPDEINIT_CB_ID :
        hltdc->MspDeInitCallback = HAL_LTDC_MspDeInit;              /* Legcay weak MspDeInit Callback     */
        break;

      default :
        /* Update the error code */
        hltdc->ErrorCode |= HAL_LTDC_ERROR_INVALID_CALLBACK;
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hltdc->State == HAL_LTDC_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_LTDC_MSPINIT_CB_ID :
        hltdc->MspInitCallback = HAL_LTDC_MspInit;                  /* Legcay weak MspInit Callback     */
        break;

      case HAL_LTDC_MSPDEINIT_CB_ID :
        hltdc->MspDeInitCallback = HAL_LTDC_MspDeInit;              /* Legcay weak MspDeInit Callback     */
        break;

      default :
        /* Update the error code */
        hltdc->ErrorCode |= HAL_LTDC_ERROR_INVALID_CALLBACK;
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hltdc->ErrorCode |= HAL_LTDC_ERROR_INVALID_CALLBACK;
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hltdc);

  return status;
}
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup LTDC_Exported_Functions_Group2 IO operation functions
  *  @brief   IO operation functions
  *
@verbatim
 ===============================================================================
                      #####  IO operation functions  #####
 ===============================================================================
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
    [..]  This section provides function allowing to:
      (+) Handle LTDC interrupt request

@endverbatim
  * @{
  */
/**
<<<<<<< HEAD
  * @brief  Handles LTDC interrupt request.
  * @param  hltdc pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.  
=======
  * @brief  Handle LTDC interrupt request.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval HAL status
  */
void HAL_LTDC_IRQHandler(LTDC_HandleTypeDef *hltdc)
{
<<<<<<< HEAD
  /* Transfer Error Interrupt management ***************************************/
  if(__HAL_LTDC_GET_FLAG(hltdc, LTDC_FLAG_TE) != RESET)
  {
    if(__HAL_LTDC_GET_IT_SOURCE(hltdc, LTDC_IT_TE) != RESET)
    {
      /* Disable the transfer Error interrupt */
      __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_TE);

      /* Clear the transfer error flag */
      __HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_TE);

      /* Update error code */
      hltdc->ErrorCode |= HAL_LTDC_ERROR_TE;

      /* Change LTDC state */
      hltdc->State = HAL_LTDC_STATE_ERROR;

      /* Process unlocked */
      __HAL_UNLOCK(hltdc);

      /* Transfer error Callback */
      HAL_LTDC_ErrorCallback(hltdc);
    }
  }
  /* FIFO underrun Interrupt management ***************************************/
  if(__HAL_LTDC_GET_FLAG(hltdc, LTDC_FLAG_FU) != RESET)
  {
    if(__HAL_LTDC_GET_IT_SOURCE(hltdc, LTDC_IT_FU) != RESET)
    {
      /* Disable the FIFO underrun interrupt */
      __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_FU);

      /* Clear the FIFO underrun flag */
      __HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_FU);

      /* Update error code */
      hltdc->ErrorCode |= HAL_LTDC_ERROR_FU;

      /* Change LTDC state */
      hltdc->State = HAL_LTDC_STATE_ERROR;

      /* Process unlocked */
      __HAL_UNLOCK(hltdc);
      
      /* Transfer error Callback */
      HAL_LTDC_ErrorCallback(hltdc);
    }
  }
  /* Line Interrupt management ************************************************/
  if(__HAL_LTDC_GET_FLAG(hltdc, LTDC_FLAG_LI) != RESET)
  {
    if(__HAL_LTDC_GET_IT_SOURCE(hltdc, LTDC_IT_LI) != RESET)
    {
      /* Disable the Line interrupt */
      __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_LI);

      /* Clear the Line interrupt flag */  
      __HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_LI);

      /* Change LTDC state */
      hltdc->State = HAL_LTDC_STATE_READY;

      /* Process unlocked */
      __HAL_UNLOCK(hltdc);

      /* Line interrupt Callback */
      HAL_LTDC_LineEventCallback(hltdc);
    }
  }
  /* Register reload Interrupt management ***************************************/
  if(__HAL_LTDC_GET_FLAG(hltdc, LTDC_FLAG_RR) != RESET)
  {
    if(__HAL_LTDC_GET_IT_SOURCE(hltdc, LTDC_IT_RR) != RESET)
    {
      /* Disable the register reload interrupt */
      __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_RR);
      
      /* Clear the register reload flag */
      __HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_RR);
      
      /* Change LTDC state */
      hltdc->State = HAL_LTDC_STATE_READY;
      
      /* Process unlocked */
      __HAL_UNLOCK(hltdc);
      
      /* Register reload interrupt Callback */
      HAL_LTDC_ReloadEventCallback(hltdc);
    }
  }  
=======
  uint32_t isrflags  = READ_REG(hltdc->Instance->ISR);
  uint32_t itsources = READ_REG(hltdc->Instance->IER);

  /* Transfer Error Interrupt management ***************************************/
  if (((isrflags & LTDC_ISR_TERRIF) != 0U) && ((itsources & LTDC_IER_TERRIE) != 0U))
  {
    /* Disable the transfer Error interrupt */
    __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_TE);

    /* Clear the transfer error flag */
    __HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_TE);

    /* Update error code */
    hltdc->ErrorCode |= HAL_LTDC_ERROR_TE;

    /* Change LTDC state */
    hltdc->State = HAL_LTDC_STATE_ERROR;

    /* Process unlocked */
    __HAL_UNLOCK(hltdc);

    /* Transfer error Callback */
#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
    /*Call registered error callback*/
    hltdc->ErrorCallback(hltdc);
#else
    /* Call legacy error callback*/
    HAL_LTDC_ErrorCallback(hltdc);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
  }

  /* FIFO underrun Interrupt management ***************************************/
  if (((isrflags & LTDC_ISR_FUIF) != 0U) && ((itsources & LTDC_IER_FUIE) != 0U))
  {
    /* Disable the FIFO underrun interrupt */
    __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_FU);

    /* Clear the FIFO underrun flag */
    __HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_FU);

    /* Update error code */
    hltdc->ErrorCode |= HAL_LTDC_ERROR_FU;

    /* Change LTDC state */
    hltdc->State = HAL_LTDC_STATE_ERROR;

    /* Process unlocked */
    __HAL_UNLOCK(hltdc);

    /* Transfer error Callback */
#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
    /*Call registered error callback*/
    hltdc->ErrorCallback(hltdc);
#else
    /* Call legacy error callback*/
    HAL_LTDC_ErrorCallback(hltdc);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
  }

  /* Line Interrupt management ************************************************/
  if (((isrflags & LTDC_ISR_LIF) != 0U) && ((itsources & LTDC_IER_LIE) != 0U))
  {
    /* Disable the Line interrupt */
    __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_LI);

    /* Clear the Line interrupt flag */
    __HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_LI);

    /* Change LTDC state */
    hltdc->State = HAL_LTDC_STATE_READY;

    /* Process unlocked */
    __HAL_UNLOCK(hltdc);

    /* Line interrupt Callback */
#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
    /*Call registered Line Event callback */
    hltdc->LineEventCallback(hltdc);
#else
    /*Call Legacy Line Event callback */
    HAL_LTDC_LineEventCallback(hltdc);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
  }

  /* Register reload Interrupt management ***************************************/
  if (((isrflags & LTDC_ISR_RRIF) != 0U) && ((itsources & LTDC_IER_RRIE) != 0U))
  {
    /* Disable the register reload interrupt */
    __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_RR);

    /* Clear the register reload flag */
    __HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_RR);

    /* Change LTDC state */
    hltdc->State = HAL_LTDC_STATE_READY;

    /* Process unlocked */
    __HAL_UNLOCK(hltdc);

    /* Reload interrupt Callback */
#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
    /*Call registered reload Event callback */
    hltdc->ReloadEventCallback(hltdc);
#else
    /*Call Legacy Reload Event callback */
    HAL_LTDC_ReloadEventCallback(hltdc);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
  }
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
}

/**
  * @brief  Error LTDC callback.
<<<<<<< HEAD
  * @param  hltdc pointer to a LTDC_HandleTypeDef structure that contains
=======
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *                the configuration information for the LTDC.
  * @retval None
  */
__weak void HAL_LTDC_ErrorCallback(LTDC_HandleTypeDef *hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);
<<<<<<< HEAD
  
  /* NOTE : This function Should not be modified, when the callback is needed,
=======

  /* NOTE : This function should not be modified, when the callback is needed,
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
            the HAL_LTDC_ErrorCallback could be implemented in the user file
   */
}

/**
  * @brief  Line Event callback.
<<<<<<< HEAD
  * @param  hltdc pointer to a LTDC_HandleTypeDef structure that contains
=======
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *                the configuration information for the LTDC.
  * @retval None
  */
__weak void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef *hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);
<<<<<<< HEAD
  
  /* NOTE : This function Should not be modified, when the callback is needed,
=======

  /* NOTE : This function should not be modified, when the callback is needed,
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
            the HAL_LTDC_LineEventCallback could be implemented in the user file
   */
}

/**
  * @brief  Reload Event callback.
<<<<<<< HEAD
  * @param  hltdc pointer to a LTDC_HandleTypeDef structure that contains
=======
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *                the configuration information for the LTDC.
  * @retval None
  */
__weak void HAL_LTDC_ReloadEventCallback(LTDC_HandleTypeDef *hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);
<<<<<<< HEAD
  
  /* NOTE : This function Should not be modified, when the callback is needed,
=======

  /* NOTE : This function should not be modified, when the callback is needed,
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
            the HAL_LTDC_ReloadEvenCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup LTDC_Exported_Functions_Group3 Peripheral Control functions
<<<<<<< HEAD
 *  @brief    Peripheral Control functions 
 *
@verbatim   
 ===============================================================================
                    ##### Peripheral Control functions #####
 ===============================================================================  
=======
  *  @brief    Peripheral Control functions
  *
@verbatim
 ===============================================================================
                    ##### Peripheral Control functions #####
 ===============================================================================
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
    [..]  This section provides functions allowing to:
      (+) Configure the LTDC foreground or/and background parameters.
      (+) Set the active layer.
      (+) Configure the color keying.
      (+) Configure the C-LUT.
      (+) Enable / Disable the color keying.
      (+) Enable / Disable the C-LUT.
      (+) Update the layer position.
      (+) Update the layer size.
<<<<<<< HEAD
      (+) Update pixel format on the fly. 
=======
      (+) Update pixel format on the fly.
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
      (+) Update transparency on the fly.
      (+) Update address on the fly.

@endverbatim
  * @{
  */

/**
  * @brief  Configure the LTDC Layer according to the specified
  *         parameters in the LTDC_InitTypeDef and create the associated handle.
<<<<<<< HEAD
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                    the configuration information for the LTDC.
  * @param  pLayerCfg pointer to a LTDC_LayerCfgTypeDef structure that contains
  *                    the configuration information for the Layer.
  * @param  LayerIdx  LTDC Layer index.
  *                    This parameter can be one of the following values:
  *                    0 or 1
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ConfigLayer(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx)
{   
  /* Process locked */
  __HAL_LOCK(hltdc);
  
  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_PIXEL_FORMAT(pLayerCfg->PixelFormat));
  assert_param(IS_LTDC_BLENDING_FACTOR1(pLayerCfg->BlendingFactor1));
  assert_param(IS_LTDC_BLENDING_FACTOR2(pLayerCfg->BlendingFactor2));
=======
  * @param  hltdc      pointer to a LTDC_HandleTypeDef structure that contains
  *                    the configuration information for the LTDC.
  * @param  pLayerCfg  pointer to a LTDC_LayerCfgTypeDef structure that contains
  *                    the configuration information for the Layer.
  * @param  LayerIdx  LTDC Layer index.
  *                    This parameter can be one of the following values:
  *                    LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ConfigLayer(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  assert_param(IS_LTDC_HCONFIGST(pLayerCfg->WindowX0));
  assert_param(IS_LTDC_HCONFIGSP(pLayerCfg->WindowX1));
  assert_param(IS_LTDC_VCONFIGST(pLayerCfg->WindowY0));
  assert_param(IS_LTDC_VCONFIGSP(pLayerCfg->WindowY1));
<<<<<<< HEAD
  assert_param(IS_LTDC_ALPHA(pLayerCfg->Alpha0));
  assert_param(IS_LTDC_CFBLL(pLayerCfg->ImageWidth));
  assert_param(IS_LTDC_CFBLNBR(pLayerCfg->ImageHeight));

  /* Copy new layer configuration into handle structure */
  hltdc->LayerCfg[LayerIdx] = *pLayerCfg;  

  /* Configure the LTDC Layer */  
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Sets the Reload type */
=======
  assert_param(IS_LTDC_PIXEL_FORMAT(pLayerCfg->PixelFormat));
  assert_param(IS_LTDC_ALPHA(pLayerCfg->Alpha));
  assert_param(IS_LTDC_ALPHA(pLayerCfg->Alpha0));
  assert_param(IS_LTDC_BLENDING_FACTOR1(pLayerCfg->BlendingFactor1));
  assert_param(IS_LTDC_BLENDING_FACTOR2(pLayerCfg->BlendingFactor2));
  assert_param(IS_LTDC_CFBLL(pLayerCfg->ImageWidth));
  assert_param(IS_LTDC_CFBLNBR(pLayerCfg->ImageHeight));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Copy new layer configuration into handle structure */
  hltdc->LayerCfg[LayerIdx] = *pLayerCfg;

  /* Configure the LTDC Layer */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Set the Immediate Reload type */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Initialize the LTDC state*/
  hltdc->State  = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Configure the color keying.
<<<<<<< HEAD
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  RGBValue the color key value
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1
=======
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  RGBValue  the color key value
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ConfigColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t RGBValue, uint32_t LayerIdx)
{
<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Configures the default color values */
  LTDC_LAYER(hltdc, LayerIdx)->CKCR &=  ~(LTDC_LxCKCR_CKBLUE | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKRED);
  LTDC_LAYER(hltdc, LayerIdx)->CKCR  = RGBValue;

  /* Sets the Reload type */
=======
  /* Configure the default color values */
  LTDC_LAYER(hltdc, LayerIdx)->CKCR &=  ~(LTDC_LxCKCR_CKBLUE | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKRED);
  LTDC_LAYER(hltdc, LayerIdx)->CKCR  = RGBValue;

  /* Set the Immediate Reload type */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Load the color lookup table.
<<<<<<< HEAD
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  pCLUT    pointer to the color lookup table address.
  * @param  CLUTSize the color lookup table size.  
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1
=======
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  pCLUT     pointer to the color lookup table address.
  * @param  CLUTSize  the color lookup table size.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ConfigCLUT(LTDC_HandleTypeDef *hltdc, uint32_t *pCLUT, uint32_t CLUTSize, uint32_t LayerIdx)
{
<<<<<<< HEAD
  uint32_t tmp = 0;
  uint32_t counter = 0;
  uint32_t pcounter = 0;
=======
  uint32_t tmp;
  uint32_t counter;
  uint32_t *pcolorlut = pCLUT;
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
<<<<<<< HEAD
  hltdc->State = HAL_LTDC_STATE_BUSY;  

  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx)); 

  for(counter = 0; (counter < CLUTSize); counter++)
  {
    if(hltdc->LayerCfg[LayerIdx].PixelFormat == LTDC_PIXEL_FORMAT_AL44)
    {
      tmp  = (((counter + 16*counter) << 24) | ((uint32_t)(*pCLUT) & 0xFF) | ((uint32_t)(*pCLUT) & 0xFF00) | ((uint32_t)(*pCLUT) & 0xFF0000));
    }
    else
    { 
      tmp  = ((counter << 24) | ((uint32_t)(*pCLUT) & 0xFF) | ((uint32_t)(*pCLUT) & 0xFF00) | ((uint32_t)(*pCLUT) & 0xFF0000));
    }
    pcounter = (uint32_t)pCLUT + sizeof(*pCLUT);
    pCLUT = (uint32_t *)pcounter;
=======
  hltdc->State = HAL_LTDC_STATE_BUSY;

  for (counter = 0U; (counter < CLUTSize); counter++)
  {
    if (hltdc->LayerCfg[LayerIdx].PixelFormat == LTDC_PIXEL_FORMAT_AL44)
    {
      tmp  = (((counter + (16U*counter)) << 24U) | ((uint32_t)(*pcolorlut) & 0xFFU) | ((uint32_t)(*pcolorlut) & 0xFF00U) | ((uint32_t)(*pcolorlut) & 0xFF0000U));
    }
    else
    {
      tmp  = ((counter << 24U) | ((uint32_t)(*pcolorlut) & 0xFFU) | ((uint32_t)(*pcolorlut) & 0xFF00U) | ((uint32_t)(*pcolorlut) & 0xFF0000U));
    }

    pcolorlut++;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

    /* Specifies the C-LUT address and RGB value */
    LTDC_LAYER(hltdc, LayerIdx)->CLUTWR  = tmp;
  }
<<<<<<< HEAD
  
  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);  
=======

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  return HAL_OK;
}

/**
  * @brief  Enable the color keying.
<<<<<<< HEAD
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_EnableColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{  
=======
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_EnableColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Enable LTDC color keying by setting COLKEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_COLKEN;

  /* Sets the Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 
=======
  /* Enable LTDC color keying by setting COLKEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_COLKEN;

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

<<<<<<< HEAD
  return HAL_OK;  
}
  
/**
  * @brief  Disable the color keying.
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1
=======
  return HAL_OK;
}

/**
  * @brief  Disable the color keying.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_DisableColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Disable LTDC color keying by setting COLKEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR &= ~(uint32_t)LTDC_LxCR_COLKEN;

  /* Sets the Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 
=======
  /* Disable LTDC color keying by setting COLKEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR &= ~(uint32_t)LTDC_LxCR_COLKEN;

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Enable the color lookup table.
<<<<<<< HEAD
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1
=======
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_EnableCLUT(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Disable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_CLUTEN;

  /* Sets the Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 
=======
  /* Enable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_CLUTEN;

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Disable the color lookup table.
<<<<<<< HEAD
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1   
=======
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_DisableCLUT(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
<<<<<<< HEAD
 
=======
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Disable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR &= ~(uint32_t)LTDC_LxCR_CLUTEN;

  /* Sets the Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 
=======
  /* Disable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR &= ~(uint32_t)LTDC_LxCR_CLUTEN;

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
<<<<<<< HEAD
  * @brief  Enables Dither.
  * @param  hltdc pointer to a LTDC_HandleTypeDef structure that contains
=======
  * @brief  Enable Dither.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *                the configuration information for the LTDC.
  * @retval  HAL status
  */

HAL_StatusTypeDef HAL_LTDC_EnableDither(LTDC_HandleTypeDef *hltdc)
{
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Enable Dither by setting DTEN bit */
  LTDC->GCR |= (uint32_t)LTDC_GCR_DEN;

  /* Change the LTDC state*/
<<<<<<< HEAD
  hltdc->State = HAL_LTDC_STATE_READY; 
=======
  hltdc->State = HAL_LTDC_STATE_READY;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
<<<<<<< HEAD
  * @brief  Disables Dither.
  * @param  hltdc pointer to a LTDC_HandleTypeDef structure that contains
=======
  * @brief  Disable Dither.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *                the configuration information for the LTDC.
  * @retval  HAL status
  */

HAL_StatusTypeDef HAL_LTDC_DisableDither(LTDC_HandleTypeDef *hltdc)
{
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Disable Dither by setting DTEN bit */
  LTDC->GCR &= ~(uint32_t)LTDC_GCR_DEN;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Set the LTDC window size.
<<<<<<< HEAD
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  XSize    LTDC Pixel per line
  * @param  YSize    LTDC Line number
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetWindowSize(LTDC_HandleTypeDef *hltdc, uint32_t XSize, uint32_t YSize, uint32_t LayerIdx) 
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

=======
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  XSize     LTDC Pixel per line
  * @param  YSize     LTDC Line number
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetWindowSize(LTDC_HandleTypeDef *hltdc, uint32_t XSize, uint32_t YSize, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

  /* Check the parameters (Layers parameters)*/
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_CFBLL(XSize));
  assert_param(IS_LTDC_CFBLNBR(YSize));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
<<<<<<< HEAD
  hltdc->State = HAL_LTDC_STATE_BUSY; 
=======
  hltdc->State = HAL_LTDC_STATE_BUSY;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

<<<<<<< HEAD
  /* Check the parameters (Layers parameters)*/
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_HCONFIGST(pLayerCfg->WindowX0));
  assert_param(IS_LTDC_HCONFIGSP(pLayerCfg->WindowX1));
  assert_param(IS_LTDC_VCONFIGST(pLayerCfg->WindowY0));
  assert_param(IS_LTDC_VCONFIGSP(pLayerCfg->WindowY1));
  assert_param(IS_LTDC_CFBLL(XSize));
  assert_param(IS_LTDC_CFBLNBR(YSize));

  /* update horizontal start/stop */
  pLayerCfg->WindowX0 = 0;
  pLayerCfg->WindowX1 = XSize + pLayerCfg->WindowX0;

  /* update vertical start/stop */  
  pLayerCfg->WindowY0 = 0;
=======
  /* update horizontal stop */
  pLayerCfg->WindowX1 = XSize + pLayerCfg->WindowX0;

  /* update vertical stop */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  pLayerCfg->WindowY1 = YSize + pLayerCfg->WindowY0;

  /* Reconfigures the color frame buffer pitch in byte */
  pLayerCfg->ImageWidth = XSize;

  /* Reconfigures the frame buffer line number */
  pLayerCfg->ImageHeight = YSize;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

<<<<<<< HEAD
  /* Sets the Reload type */
=======
  /* Set the Immediate Reload type */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Set the LTDC window position.
<<<<<<< HEAD
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  X0       LTDC window X offset
  * @param  Y0       LTDC window Y offset
  * @param  LayerIdx  LTDC Layer index.
  *                         This parameter can be one of the following values:
  *                         0 or 1
=======
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  X0        LTDC window X offset
  * @param  Y0        LTDC window Y offset
  * @param  LayerIdx  LTDC Layer index.
  *                         This parameter can be one of the following values:
  *                         LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetWindowPosition(LTDC_HandleTypeDef *hltdc, uint32_t X0, uint32_t Y0, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;
<<<<<<< HEAD
  
=======

  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_CFBLL(X0));
  assert_param(IS_LTDC_CFBLNBR(Y0));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_HCONFIGST(pLayerCfg->WindowX0));
  assert_param(IS_LTDC_HCONFIGSP(pLayerCfg->WindowX1));
  assert_param(IS_LTDC_VCONFIGST(pLayerCfg->WindowY0));
  assert_param(IS_LTDC_VCONFIGSP(pLayerCfg->WindowY1));

=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* update horizontal start/stop */
  pLayerCfg->WindowX0 = X0;
  pLayerCfg->WindowX1 = X0 + pLayerCfg->ImageWidth;

  /* update vertical start/stop */
  pLayerCfg->WindowY0 = Y0;
  pLayerCfg->WindowY1 = Y0 + pLayerCfg->ImageHeight;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

<<<<<<< HEAD
  /* Sets the Reload type */
=======
  /* Set the Immediate Reload type */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Reconfigure the pixel format.
<<<<<<< HEAD
  * @param  hltdc       pointer to a LTDC_HandleTypeDef structure that contains
  *                      the configuration information for the LTDC.
  * @param  Pixelformat new pixel format value.
  * @param  LayerIdx    LTDC Layer index.
  *                      This parameter can be one of the following values:
  *                      0 or 1.
=======
  * @param  hltdc        pointer to a LTDC_HandleTypeDef structure that contains
  *                      the configuration information for the LTDC.
  * @param  Pixelformat  new pixel format value.
  * @param  LayerIdx     LTDC Layer index.
  *                      This parameter can be one of the following values:
  *                      LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1).
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetPixelFormat(LTDC_HandleTypeDef *hltdc, uint32_t Pixelformat, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_PIXEL_FORMAT(Pixelformat));
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_PIXEL_FORMAT(Pixelformat));

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];  
=======
  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Reconfigure the pixel format */
  pLayerCfg->PixelFormat = Pixelformat;

  /* Set LTDC parameters */
<<<<<<< HEAD
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);   

  /* Sets the Reload type */
=======
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Set the Immediate Reload type */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Reconfigure the layer alpha value.
<<<<<<< HEAD
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  Alpha    new alpha value.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1
=======
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  Alpha     new alpha value.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetAlpha(LTDC_HandleTypeDef *hltdc, uint32_t Alpha, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_ALPHA(Alpha));
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_ALPHA(Alpha));
  assert_param(IS_LTDC_LAYER(LayerIdx));

=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

  /* Reconfigure the Alpha value */
  pLayerCfg->Alpha = Alpha;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

<<<<<<< HEAD
  /* Sets the Reload type */
=======
  /* Set the Immediate Reload type */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}
/**
  * @brief  Reconfigure the frame buffer Address.
<<<<<<< HEAD
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  Address  new address value.
  * @param  LayerIdx LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1.
=======
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  Address   new address value.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1).
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetAddress(LTDC_HandleTypeDef *hltdc, uint32_t Address, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

  /* Reconfigure the Address */
  pLayerCfg->FBStartAdress = Address;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

<<<<<<< HEAD
  /* Sets the Reload type */
=======
  /* Set the Immediate Reload type */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Function used to reconfigure the pitch for specific cases where the attached LayerIdx buffer have a width that is
<<<<<<< HEAD
  *         larger than the one intended to be displayed on screen. Example of a buffer 800x480 attached to layer for which we 
  *         want to read and display on screen only a portion 320x240 taken in the center of the buffer. The pitch in pixels 
  *         will be in that case 800 pixels and not 320 pixels as initially configured by previous call to HAL_LTDC_ConfigLayer().
  *         Note : this function should be called only after a previous call to HAL_LTDC_ConfigLayer() to modify the default pitch
  *                configured by HAL_LTDC_ConfigLayer() when required (refer to example described just above).
  * @param  hltdc             pointer to a LTDC_HandleTypeDef structure that contains
  *                            the configuration information for the LTDC.
  * @param  LinePitchInPixels New line pitch in pixels to configure for LTDC layer 'LayerIdx'.
  * @param  LayerIdx          LTDC layer index concerned by the modification of line pitch.
=======
  *         larger than the one intended to be displayed on screen. Example of a buffer 800x480 attached to layer for which we
  *         want to read and display on screen only a portion 320x240 taken in the center of the buffer. The pitch in pixels
  *         will be in that case 800 pixels and not 320 pixels as initially configured by previous call to HAL_LTDC_ConfigLayer().
  * @note   This function should be called only after a previous call to HAL_LTDC_ConfigLayer() to modify the default pitch
  *         configured by HAL_LTDC_ConfigLayer() when required (refer to example described just above).
  * @param  hltdc              pointer to a LTDC_HandleTypeDef structure that contains
  *                            the configuration information for the LTDC.
  * @param  LinePitchInPixels  New line pitch in pixels to configure for LTDC layer 'LayerIdx'.
  * @param  LayerIdx           LTDC layer index concerned by the modification of line pitch.
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetPitch(LTDC_HandleTypeDef *hltdc, uint32_t LinePitchInPixels, uint32_t LayerIdx)
{
<<<<<<< HEAD
  uint32_t tmp = 0;
  uint32_t pitchUpdate = 0;
  uint32_t pixelFormat = 0;
  
  /* Process locked */
  __HAL_LOCK(hltdc);
  
  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;
  
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  
  /* get LayerIdx used pixel format */
  pixelFormat = hltdc->LayerCfg[LayerIdx].PixelFormat;
  
  if(pixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
  {
    tmp = 4;
  }
  else if (pixelFormat == LTDC_PIXEL_FORMAT_RGB888)
  {
    tmp = 3;
  }
  else if((pixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
          (pixelFormat == LTDC_PIXEL_FORMAT_RGB565)   || \
          (pixelFormat == LTDC_PIXEL_FORMAT_ARGB1555) || \
         (pixelFormat == LTDC_PIXEL_FORMAT_AL88))
  {
    tmp = 2;
  }
  else
  {
    tmp = 1;
  }
  
  pitchUpdate = ((LinePitchInPixels * tmp) << 16);
  
  /* Clear previously set standard pitch */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR &= ~LTDC_LxCFBLR_CFBP;
  
  /* Sets the Reload type as immediate update of LTDC pitch configured above */
  LTDC->SRCR |= LTDC_SRCR_IMR;
  
  /* Set new line pitch value */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR |= pitchUpdate;
  
  /* Sets the Reload type as immediate update of LTDC pitch configured above */
  LTDC->SRCR |= LTDC_SRCR_IMR;
  
  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hltdc);
  
  return HAL_OK;  
=======
  uint32_t tmp;
  uint32_t pitchUpdate;
  uint32_t pixelFormat;

  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* get LayerIdx used pixel format */
  pixelFormat = hltdc->LayerCfg[LayerIdx].PixelFormat;

  if (pixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
  {
    tmp = 4U;
  }
  else if (pixelFormat == LTDC_PIXEL_FORMAT_RGB888)
  {
    tmp = 3U;
  }
  else if ((pixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
           (pixelFormat == LTDC_PIXEL_FORMAT_RGB565)   || \
           (pixelFormat == LTDC_PIXEL_FORMAT_ARGB1555) || \
           (pixelFormat == LTDC_PIXEL_FORMAT_AL88))
  {
    tmp = 2U;
  }
  else
  {
    tmp = 1U;
  }

  pitchUpdate = ((LinePitchInPixels * tmp) << 16U);

  /* Clear previously set standard pitch */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR &= ~LTDC_LxCFBLR_CFBP;

  /* Set the Reload type as immediate update of LTDC pitch configured above */
  LTDC->SRCR |= LTDC_SRCR_IMR;

  /* Set new line pitch value */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR |= pitchUpdate;

  /* Set the Reload type as immediate update of LTDC pitch configured above */
  LTDC->SRCR |= LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
}

/**
  * @brief  Define the position of the line interrupt.
<<<<<<< HEAD
  * @param  hltdc             pointer to a LTDC_HandleTypeDef structure that contains
  *                            the configuration information for the LTDC.
  * @param  Line   Line Interrupt Position.
=======
  * @param  hltdc   pointer to a LTDC_HandleTypeDef structure that contains
  *                 the configuration information for the LTDC.
  * @param  Line    Line Interrupt Position.
  * @note   User application may resort to HAL_LTDC_LineEventCallback() at line interrupt generation.
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ProgramLineEvent(LTDC_HandleTypeDef *hltdc, uint32_t Line)
{
<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_LIPOS(Line));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LIPOS(Line));
=======
  /* Disable the Line interrupt */
  __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_LI);

  /* Set the Line Interrupt position */
  LTDC->LIPCR = (uint32_t)Line;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Enable the Line interrupt */
  __HAL_LTDC_ENABLE_IT(hltdc, LTDC_IT_LI);

<<<<<<< HEAD
  /* Sets the Line Interrupt position */
  LTDC->LIPCR = (uint32_t)Line;

=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
<<<<<<< HEAD
  * @brief  LTDC configuration reload.
  * @param  hltdc            pointer to a LTDC_HandleTypeDef structure that contains
  *                           the configuration information for the LTDC.
  * @param  ReloadType       This parameter can be one of the following values :
  *                           LTDC_RELOAD_IMMEDIATE : Immediate Reload
  *                           LTDC_RELOAD_VERTICAL_BLANKING  : Reload in the next Vertical Blanking
=======
  * @brief  Reload LTDC Layers configuration.
  * @param  hltdc      pointer to a LTDC_HandleTypeDef structure that contains
  *                    the configuration information for the LTDC.
  * @param  ReloadType This parameter can be one of the following values :
  *                      LTDC_RELOAD_IMMEDIATE : Immediate Reload
  *                      LTDC_RELOAD_VERTICAL_BLANKING  : Reload in the next Vertical Blanking
  * @note   User application may resort to HAL_LTDC_ReloadEventCallback() at reload interrupt generation.
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef  HAL_LTDC_Reload(LTDC_HandleTypeDef *hltdc, uint32_t ReloadType)
{
<<<<<<< HEAD
  assert_param(IS_LTDC_RELAOD(ReloadType));
=======
  /* Check the parameters */
  assert_param(IS_LTDC_RELOAD(ReloadType));
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
<<<<<<< HEAD
  hltdc->State = HAL_LTDC_STATE_BUSY;  
  
  /* Enable the Reload interrupt */  
  __HAL_LTDC_ENABLE_IT(hltdc, LTDC_IT_RR);
       
  /* Apply Reload type */
  hltdc->Instance->SRCR = ReloadType;        

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hltdc);
  
=======
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Enable the Reload interrupt */
  __HAL_LTDC_ENABLE_IT(hltdc, LTDC_IT_RR);

  /* Apply Reload type */
  hltdc->Instance->SRCR = ReloadType;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  return HAL_OK;
}

/**
  * @brief  Configure the LTDC Layer according to the specified without reloading
  *         parameters in the LTDC_InitTypeDef and create the associated handle.
<<<<<<< HEAD
  *         Variant of the function HAL_LTDC_ConfigLayer without immediate reload
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                    the configuration information for the LTDC.
  * @param  pLayerCfg pointer to a LTDC_LayerCfgTypeDef structure that contains
  *                    the configuration information for the Layer.
  * @param  LayerIdx  LTDC Layer index.
  *                    This parameter can be one of the following values:
  *                    0 or 1
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ConfigLayer_NoReload(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx)
{   
  /* Process locked */
  __HAL_LOCK(hltdc);
  
  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_PIXEL_FORMAT(pLayerCfg->PixelFormat));
  assert_param(IS_LTDC_BLENDING_FACTOR1(pLayerCfg->BlendingFactor1));
  assert_param(IS_LTDC_BLENDING_FACTOR2(pLayerCfg->BlendingFactor2));
=======
  *         Variant of the function HAL_LTDC_ConfigLayer without immediate reload.
  * @param  hltdc      pointer to a LTDC_HandleTypeDef structure that contains
  *                    the configuration information for the LTDC.
  * @param  pLayerCfg  pointer to a LTDC_LayerCfgTypeDef structure that contains
  *                    the configuration information for the Layer.
  * @param  LayerIdx   LTDC Layer index.
  *                    This parameter can be one of the following values:
  *                    LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ConfigLayer_NoReload(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  assert_param(IS_LTDC_HCONFIGST(pLayerCfg->WindowX0));
  assert_param(IS_LTDC_HCONFIGSP(pLayerCfg->WindowX1));
  assert_param(IS_LTDC_VCONFIGST(pLayerCfg->WindowY0));
  assert_param(IS_LTDC_VCONFIGSP(pLayerCfg->WindowY1));
<<<<<<< HEAD
  assert_param(IS_LTDC_ALPHA(pLayerCfg->Alpha0));
  assert_param(IS_LTDC_CFBLL(pLayerCfg->ImageWidth));
  assert_param(IS_LTDC_CFBLNBR(pLayerCfg->ImageHeight));

  /* Copy new layer configuration into handle structure */
  hltdc->LayerCfg[LayerIdx] = *pLayerCfg;  

  /* Configure the LTDC Layer */  
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Do not Sets the Reload  */

=======
  assert_param(IS_LTDC_PIXEL_FORMAT(pLayerCfg->PixelFormat));
  assert_param(IS_LTDC_ALPHA(pLayerCfg->Alpha));
  assert_param(IS_LTDC_ALPHA(pLayerCfg->Alpha0));
  assert_param(IS_LTDC_BLENDING_FACTOR1(pLayerCfg->BlendingFactor1));
  assert_param(IS_LTDC_BLENDING_FACTOR2(pLayerCfg->BlendingFactor2));
  assert_param(IS_LTDC_CFBLL(pLayerCfg->ImageWidth));
  assert_param(IS_LTDC_CFBLNBR(pLayerCfg->ImageHeight));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Copy new layer configuration into handle structure */
  hltdc->LayerCfg[LayerIdx] = *pLayerCfg;

  /* Configure the LTDC Layer */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Initialize the LTDC state*/
  hltdc->State  = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Set the LTDC window size without reloading.
<<<<<<< HEAD
  *         Variant of the function HAL_LTDC_SetWindowSize without immediate reload
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  XSize    LTDC Pixel per line
  * @param  YSize    LTDC Line number
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetWindowSize_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t XSize, uint32_t YSize, uint32_t LayerIdx) 
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

=======
  *         Variant of the function HAL_LTDC_SetWindowSize without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  XSize     LTDC Pixel per line
  * @param  YSize     LTDC Line number
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetWindowSize_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t XSize, uint32_t YSize, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

  /* Check the parameters (Layers parameters)*/
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_CFBLL(XSize));
  assert_param(IS_LTDC_CFBLNBR(YSize));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
<<<<<<< HEAD
  hltdc->State = HAL_LTDC_STATE_BUSY; 
=======
  hltdc->State = HAL_LTDC_STATE_BUSY;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

<<<<<<< HEAD
  /* Check the parameters (Layers parameters)*/
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_HCONFIGST(pLayerCfg->WindowX0));
  assert_param(IS_LTDC_HCONFIGSP(pLayerCfg->WindowX1));
  assert_param(IS_LTDC_VCONFIGST(pLayerCfg->WindowY0));
  assert_param(IS_LTDC_VCONFIGSP(pLayerCfg->WindowY1));
  assert_param(IS_LTDC_CFBLL(XSize));
  assert_param(IS_LTDC_CFBLNBR(YSize));

  /* update horizontal start/stop */
  pLayerCfg->WindowX0 = 0;
  pLayerCfg->WindowX1 = XSize + pLayerCfg->WindowX0;

  /* update vertical start/stop */  
  pLayerCfg->WindowY0 = 0;
=======
  /* update horizontal stop */
  pLayerCfg->WindowX1 = XSize + pLayerCfg->WindowX0;

  /* update vertical stop */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  pLayerCfg->WindowY1 = YSize + pLayerCfg->WindowY0;

  /* Reconfigures the color frame buffer pitch in byte */
  pLayerCfg->ImageWidth = XSize;

  /* Reconfigures the frame buffer line number */
  pLayerCfg->ImageHeight = YSize;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

<<<<<<< HEAD
  /* Do not Sets the Reload  */

=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Set the LTDC window position without reloading.
<<<<<<< HEAD
  *         Variant of the function HAL_LTDC_SetWindowPosition without immediate reload
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  X0       LTDC window X offset
  * @param  Y0       LTDC window Y offset
  * @param  LayerIdx  LTDC Layer index.
  *                         This parameter can be one of the following values:
  *                         0 or 1
=======
  *         Variant of the function HAL_LTDC_SetWindowPosition without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  X0        LTDC window X offset
  * @param  Y0        LTDC window Y offset
  * @param  LayerIdx  LTDC Layer index.
  *                         This parameter can be one of the following values:
  *                         LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetWindowPosition_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t X0, uint32_t Y0, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;
<<<<<<< HEAD
  
=======

  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_CFBLL(X0));
  assert_param(IS_LTDC_CFBLNBR(Y0));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_HCONFIGST(pLayerCfg->WindowX0));
  assert_param(IS_LTDC_HCONFIGSP(pLayerCfg->WindowX1));
  assert_param(IS_LTDC_VCONFIGST(pLayerCfg->WindowY0));
  assert_param(IS_LTDC_VCONFIGSP(pLayerCfg->WindowY1));

=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* update horizontal start/stop */
  pLayerCfg->WindowX0 = X0;
  pLayerCfg->WindowX1 = X0 + pLayerCfg->ImageWidth;

  /* update vertical start/stop */
  pLayerCfg->WindowY0 = Y0;
  pLayerCfg->WindowY1 = Y0 + pLayerCfg->ImageHeight;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

<<<<<<< HEAD
  /* Do not Sets the Reload  */

=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Reconfigure the pixel format without reloading.
<<<<<<< HEAD
  *         Variant of the function HAL_LTDC_SetPixelFormat without immediate reload
  * @param  hltdc       pointer to a LTDC_HandleTypeDfef structure that contains
  *                      the configuration information for the LTDC.
  * @param  Pixelformat new pixel format value.
  * @param  LayerIdx    LTDC Layer index.
  *                      This parameter can be one of the following values:
  *                      0 or 1.
=======
  *         Variant of the function HAL_LTDC_SetPixelFormat without immediate reload.
  * @param  hltdc        pointer to a LTDC_HandleTypeDfef structure that contains
  *                      the configuration information for the LTDC.
  * @param  Pixelformat  new pixel format value.
  * @param  LayerIdx     LTDC Layer index.
  *                      This parameter can be one of the following values:
  *                      LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1).
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetPixelFormat_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t Pixelformat, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_PIXEL_FORMAT(Pixelformat));
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_PIXEL_FORMAT(Pixelformat));

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];  
=======
  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Reconfigure the pixel format */
  pLayerCfg->PixelFormat = Pixelformat;

  /* Set LTDC parameters */
<<<<<<< HEAD
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);   

  /* Do not Sets the Reload  */
=======
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Reconfigure the layer alpha value without reloading.
<<<<<<< HEAD
  *         Variant of the function HAL_LTDC_SetAlpha without immediate reload
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  Alpha    new alpha value.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1
=======
  *         Variant of the function HAL_LTDC_SetAlpha without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  Alpha     new alpha value.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetAlpha_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t Alpha, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_ALPHA(Alpha));
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_ALPHA(Alpha));
  assert_param(IS_LTDC_LAYER(LayerIdx));

=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

  /* Reconfigure the Alpha value */
  pLayerCfg->Alpha = Alpha;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

<<<<<<< HEAD
  /* Do not Sets the Reload  */

=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Reconfigure the frame buffer Address without reloading.
<<<<<<< HEAD
  *         Variant of the function HAL_LTDC_SetAddress without immediate reload   
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  Address  new address value.
  * @param  LayerIdx LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1.
=======
  *         Variant of the function HAL_LTDC_SetAddress without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  Address   new address value.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1).
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetAddress_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t Address, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

  /* Reconfigure the Address */
  pLayerCfg->FBStartAdress = Address;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

<<<<<<< HEAD
  /* Do not Sets the Reload  */

=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Function used to reconfigure the pitch for specific cases where the attached LayerIdx buffer have a width that is
<<<<<<< HEAD
  *         larger than the one intended to be displayed on screen. Example of a buffer 800x480 attached to layer for which we 
  *         want to read and display on screen only a portion 320x240 taken in the center of the buffer. The pitch in pixels 
  *         will be in that case 800 pixels and not 320 pixels as initially configured by previous call to HAL_LTDC_ConfigLayer().
  *         Note : this function should be called only after a previous call to HAL_LTDC_ConfigLayer() to modify the default pitch
  *                configured by HAL_LTDC_ConfigLayer() when required (refer to example described just above).
  *         Variant of the function HAL_LTDC_SetPitch without immediate reload    
  * @param  hltdc             pointer to a LTDC_HandleTypeDef structure that contains
  *                            the configuration information for the LTDC.
  * @param  LinePitchInPixels New line pitch in pixels to configure for LTDC layer 'LayerIdx'.
  * @param  LayerIdx          LTDC layer index concerned by the modification of line pitch.
=======
  *         larger than the one intended to be displayed on screen. Example of a buffer 800x480 attached to layer for which we
  *         want to read and display on screen only a portion 320x240 taken in the center of the buffer. The pitch in pixels
  *         will be in that case 800 pixels and not 320 pixels as initially configured by previous call to HAL_LTDC_ConfigLayer().
  * @note   This function should be called only after a previous call to HAL_LTDC_ConfigLayer() to modify the default pitch
  *         configured by HAL_LTDC_ConfigLayer() when required (refer to example described just above).
  *         Variant of the function HAL_LTDC_SetPitch without immediate reload.
  * @param  hltdc              pointer to a LTDC_HandleTypeDef structure that contains
  *                            the configuration information for the LTDC.
  * @param  LinePitchInPixels  New line pitch in pixels to configure for LTDC layer 'LayerIdx'.
  * @param  LayerIdx           LTDC layer index concerned by the modification of line pitch.
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetPitch_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LinePitchInPixels, uint32_t LayerIdx)
{
<<<<<<< HEAD
  uint32_t tmp = 0;
  uint32_t pitchUpdate = 0;
  uint32_t pixelFormat = 0;
  
  /* Process locked */
  __HAL_LOCK(hltdc);
  
  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;
  
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  
  /* get LayerIdx used pixel format */
  pixelFormat = hltdc->LayerCfg[LayerIdx].PixelFormat;
  
  if(pixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
  {
    tmp = 4;
  }
  else if (pixelFormat == LTDC_PIXEL_FORMAT_RGB888)
  {
    tmp = 3;
  }
  else if((pixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
          (pixelFormat == LTDC_PIXEL_FORMAT_RGB565)   || \
          (pixelFormat == LTDC_PIXEL_FORMAT_ARGB1555) || \
         (pixelFormat == LTDC_PIXEL_FORMAT_AL88))
  {
    tmp = 2;
  }
  else
  {
    tmp = 1;
  }
  
  pitchUpdate = ((LinePitchInPixels * tmp) << 16);
  
  /* Clear previously set standard pitch */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR &= ~LTDC_LxCFBLR_CFBP;
  
  /* Set new line pitch value */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR |= pitchUpdate;
  
  /* Do not Sets the Reload  */
  
  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hltdc);
  
  return HAL_OK;  
=======
  uint32_t tmp;
  uint32_t pitchUpdate;
  uint32_t pixelFormat;

  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* get LayerIdx used pixel format */
  pixelFormat = hltdc->LayerCfg[LayerIdx].PixelFormat;

  if (pixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
  {
    tmp = 4U;
  }
  else if (pixelFormat == LTDC_PIXEL_FORMAT_RGB888)
  {
    tmp = 3U;
  }
  else if ((pixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
           (pixelFormat == LTDC_PIXEL_FORMAT_RGB565)   || \
           (pixelFormat == LTDC_PIXEL_FORMAT_ARGB1555) || \
           (pixelFormat == LTDC_PIXEL_FORMAT_AL88))
  {
    tmp = 2U;
  }
  else
  {
    tmp = 1U;
  }

  pitchUpdate = ((LinePitchInPixels * tmp) << 16U);

  /* Clear previously set standard pitch */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR &= ~LTDC_LxCFBLR_CFBP;

  /* Set new line pitch value */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR |= pitchUpdate;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
}


/**
  * @brief  Configure the color keying without reloading.
<<<<<<< HEAD
  *         Variant of the function HAL_LTDC_ConfigColorKeying without immediate reload
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
=======
  *         Variant of the function HAL_LTDC_ConfigColorKeying without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *                   the configuration information for the LTDC.
  * @param  RGBValue the color key value
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
<<<<<<< HEAD
  *                   0 or 1
=======
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ConfigColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t RGBValue, uint32_t LayerIdx)
{
<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Configures the default color values */
  LTDC_LAYER(hltdc, LayerIdx)->CKCR &=  ~(LTDC_LxCKCR_CKBLUE | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKRED);
  LTDC_LAYER(hltdc, LayerIdx)->CKCR  = RGBValue;

  /* Do not Sets the Reload  */

=======
  /* Configure the default color values */
  LTDC_LAYER(hltdc, LayerIdx)->CKCR &=  ~(LTDC_LxCKCR_CKBLUE | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKRED);
  LTDC_LAYER(hltdc, LayerIdx)->CKCR  = RGBValue;

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Enable the color keying without reloading.
<<<<<<< HEAD
  *         Variant of the function HAL_LTDC_EnableColorKeying without immediate reload
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_EnableColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{  
=======
  *         Variant of the function HAL_LTDC_EnableColorKeying without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_EnableColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Enable LTDC color keying by setting COLKEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_COLKEN;

  /* Do not Sets the Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 
=======
  /* Enable LTDC color keying by setting COLKEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_COLKEN;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

<<<<<<< HEAD
  return HAL_OK;  
=======
  return HAL_OK;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
}

/**
  * @brief  Disable the color keying without reloading.
<<<<<<< HEAD
  *         Variant of the function HAL_LTDC_DisableColorKeying without immediate reload
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1
=======
  *         Variant of the function HAL_LTDC_DisableColorKeying without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_DisableColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Disable LTDC color keying by setting COLKEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR &= ~(uint32_t)LTDC_LxCR_COLKEN;

  /* Do not Sets the Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 
=======
  /* Disable LTDC color keying by setting COLKEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR &= ~(uint32_t)LTDC_LxCR_COLKEN;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Enable the color lookup table without reloading.
<<<<<<< HEAD
  *         Variant of the function HAL_LTDC_EnableCLUT without immediate reload
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1
=======
  *         Variant of the function HAL_LTDC_EnableCLUT without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_EnableCLUT_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
<<<<<<< HEAD
=======
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Disable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_CLUTEN;

  /* Do not Sets the Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 
=======
  /* Disable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_CLUTEN;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Disable the color lookup table without reloading.
<<<<<<< HEAD
  *         Variant of the function HAL_LTDC_DisableCLUT without immediate reload
  * @param  hltdc    pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   0 or 1   
=======
  *         Variant of the function HAL_LTDC_DisableCLUT without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_DisableCLUT_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
<<<<<<< HEAD
 
=======
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

<<<<<<< HEAD
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Disable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR &= ~(uint32_t)LTDC_LxCR_CLUTEN;

  /* Do not Sets the Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 
=======
  /* Disable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR &= ~(uint32_t)LTDC_LxCR_CLUTEN;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup LTDC_Exported_Functions_Group4 Peripheral State and Errors functions
<<<<<<< HEAD
 *  @brief    Peripheral State and Errors functions 
 *
@verbatim   
 ===============================================================================
                  ##### Peripheral State and Errors functions #####
 ===============================================================================  
    [..]
    This subsection provides functions allowing to
      (+) Check the LTDC state.
      (+) Get error code.  

@endverbatim
  * @{
  */ 

/**
  * @brief  Return the LTDC state
  * @param  hltdc pointer to a LTDC_HandleTypeDef structure that contains
=======
  *  @brief    Peripheral State and Errors functions
  *
@verbatim
 ===============================================================================
                  ##### Peripheral State and Errors functions #####
 ===============================================================================
    [..]
    This subsection provides functions allowing to
      (+) Check the LTDC handle state.
      (+) Get the LTDC handle error code.

@endverbatim
  * @{
  */

/**
  * @brief  Return the LTDC handle state.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *                the configuration information for the LTDC.
  * @retval HAL state
  */
HAL_LTDC_StateTypeDef HAL_LTDC_GetState(LTDC_HandleTypeDef *hltdc)
{
  return hltdc->State;
}

/**
<<<<<<< HEAD
* @brief  Return the LTDC error code
* @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *               the configuration information for the LTDC.
* @retval LTDC Error Code
*/
=======
  * @brief  Return the LTDC handle error code.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *               the configuration information for the LTDC.
  * @retval LTDC Error Code
  */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
uint32_t HAL_LTDC_GetError(LTDC_HandleTypeDef *hltdc)
{
  return hltdc->ErrorCode;
}

/**
  * @}
  */

/**
<<<<<<< HEAD
  * @brief  Configures the LTDC peripheral 
=======
  * @}
  */

/** @defgroup LTDC_Private_Functions LTDC Private Functions
  * @{
  */

/**
  * @brief  Configure the LTDC peripheral
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @param  hltdc     Pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  pLayerCfg Pointer LTDC Layer Configuration structure
  * @param  LayerIdx  LTDC Layer index.
<<<<<<< HEAD
  *                    This parameter can be one of the following values: 0 or 1
=======
  *                   This parameter can be one of the following values: LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval None
  */
static void LTDC_SetConfig(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx)
{
<<<<<<< HEAD
  uint32_t tmp = 0;
  uint32_t tmp1 = 0;
  uint32_t tmp2 = 0;

  /* Configures the horizontal start and stop position */
  tmp = ((pLayerCfg->WindowX1 + ((hltdc->Instance->BPCR & LTDC_BPCR_AHBP) >> 16)) << 16);
  LTDC_LAYER(hltdc, LayerIdx)->WHPCR &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
  LTDC_LAYER(hltdc, LayerIdx)->WHPCR = ((pLayerCfg->WindowX0 + ((hltdc->Instance->BPCR & LTDC_BPCR_AHBP) >> 16) + 1) | tmp);

  /* Configures the vertical start and stop position */
  tmp = ((pLayerCfg->WindowY1 + (hltdc->Instance->BPCR & LTDC_BPCR_AVBP)) << 16);
  LTDC_LAYER(hltdc, LayerIdx)->WVPCR &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
  LTDC_LAYER(hltdc, LayerIdx)->WVPCR  = ((pLayerCfg->WindowY0 + (hltdc->Instance->BPCR & LTDC_BPCR_AVBP) + 1) | tmp);  
=======
  uint32_t tmp;
  uint32_t tmp1;
  uint32_t tmp2;

  /* Configure the horizontal start and stop position */
  tmp = ((pLayerCfg->WindowX1 + ((hltdc->Instance->BPCR & LTDC_BPCR_AHBP) >> 16U)) << 16U);
  LTDC_LAYER(hltdc, LayerIdx)->WHPCR &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
  LTDC_LAYER(hltdc, LayerIdx)->WHPCR = ((pLayerCfg->WindowX0 + ((hltdc->Instance->BPCR & LTDC_BPCR_AHBP) >> 16U) + 1U) | tmp);

  /* Configure the vertical start and stop position */
  tmp = ((pLayerCfg->WindowY1 + (hltdc->Instance->BPCR & LTDC_BPCR_AVBP)) << 16U);
  LTDC_LAYER(hltdc, LayerIdx)->WVPCR &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
  LTDC_LAYER(hltdc, LayerIdx)->WVPCR  = ((pLayerCfg->WindowY0 + (hltdc->Instance->BPCR & LTDC_BPCR_AVBP) + 1U) | tmp);
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Specifies the pixel format */
  LTDC_LAYER(hltdc, LayerIdx)->PFCR &= ~(LTDC_LxPFCR_PF);
  LTDC_LAYER(hltdc, LayerIdx)->PFCR = (pLayerCfg->PixelFormat);

<<<<<<< HEAD
  /* Configures the default color values */
  tmp = ((uint32_t)(pLayerCfg->Backcolor.Green) << 8);
  tmp1 = ((uint32_t)(pLayerCfg->Backcolor.Red) << 16);
  tmp2 = (pLayerCfg->Alpha0 << 24);  
  LTDC_LAYER(hltdc, LayerIdx)->DCCR &= ~(LTDC_LxDCCR_DCBLUE | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCALPHA);
  LTDC_LAYER(hltdc, LayerIdx)->DCCR = (pLayerCfg->Backcolor.Blue | tmp | tmp1 | tmp2); 
=======
  /* Configure the default color values */
  tmp = ((uint32_t)(pLayerCfg->Backcolor.Green) << 8U);
  tmp1 = ((uint32_t)(pLayerCfg->Backcolor.Red) << 16U);
  tmp2 = (pLayerCfg->Alpha0 << 24U);
  LTDC_LAYER(hltdc, LayerIdx)->DCCR &= ~(LTDC_LxDCCR_DCBLUE | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCALPHA);
  LTDC_LAYER(hltdc, LayerIdx)->DCCR = (pLayerCfg->Backcolor.Blue | tmp | tmp1 | tmp2);
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

  /* Specifies the constant alpha value */
  LTDC_LAYER(hltdc, LayerIdx)->CACR &= ~(LTDC_LxCACR_CONSTA);
  LTDC_LAYER(hltdc, LayerIdx)->CACR = (pLayerCfg->Alpha);

  /* Specifies the blending factors */
  LTDC_LAYER(hltdc, LayerIdx)->BFCR &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
  LTDC_LAYER(hltdc, LayerIdx)->BFCR = (pLayerCfg->BlendingFactor1 | pLayerCfg->BlendingFactor2);

<<<<<<< HEAD
  /* Configures the color frame buffer start address */
  LTDC_LAYER(hltdc, LayerIdx)->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
  LTDC_LAYER(hltdc, LayerIdx)->CFBAR = (pLayerCfg->FBStartAdress);

  if(pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
  {
    tmp = 4;
  }
  else if (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_RGB888)
  {
    tmp = 3;
  }
  else if((pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
    (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_RGB565)   || \
      (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_ARGB1555) || \
        (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_AL88))
  {
    tmp = 2;
  }
  else
  {
    tmp = 1;
  }

  /* Configures the color frame buffer pitch in byte */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR  &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR  = (((pLayerCfg->ImageWidth * tmp) << 16) | (((pLayerCfg->WindowX1 - pLayerCfg->WindowX0) * tmp)  + 3));

  /* Configures the frame buffer line number */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLNR  &= ~(LTDC_LxCFBLNR_CFBLNBR);
  LTDC_LAYER(hltdc, LayerIdx)->CFBLNR  = (pLayerCfg->ImageHeight);

  /* Enable LTDC_Layer by setting LEN bit */  
=======
  /* Configure the color frame buffer start address */
  LTDC_LAYER(hltdc, LayerIdx)->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
  LTDC_LAYER(hltdc, LayerIdx)->CFBAR = (pLayerCfg->FBStartAdress);

  if (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
  {
    tmp = 4U;
  }
  else if (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_RGB888)
  {
    tmp = 3U;
  }
  else if ((pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
           (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_RGB565)   || \
           (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_ARGB1555) || \
           (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_AL88))
  {
    tmp = 2U;
  }
  else
  {
    tmp = 1U;
  }

  /* Configure the color frame buffer pitch in byte */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR  &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR  = (((pLayerCfg->ImageWidth * tmp) << 16U) | (((pLayerCfg->WindowX1 - pLayerCfg->WindowX0) * tmp)  + 3U));
  /* Configure the frame buffer line number */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLNR  &= ~(LTDC_LxCFBLNR_CFBLNBR);
  LTDC_LAYER(hltdc, LayerIdx)->CFBLNR  = (pLayerCfg->ImageHeight);

  /* Enable LTDC_Layer by setting LEN bit */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_LEN;
}

/**
  * @}
  */

<<<<<<< HEAD
#endif /* HAL_LTDC_MODULE_ENABLED */
=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

/**
  * @}
  */
<<<<<<< HEAD
#endif /* STM32F746xx || STM32F756xx || STM32F767xx || STM32F769xx || STM32F777xx || STM32F779xx || STM32F750xx */
=======

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

/**
  * @}
  */

<<<<<<< HEAD
=======
#endif /* LTDC */
#endif /* HAL_LTDC_MODULE_ENABLED */

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
