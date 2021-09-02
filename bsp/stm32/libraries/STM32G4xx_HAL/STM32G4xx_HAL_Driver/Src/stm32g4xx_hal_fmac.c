/**
  ******************************************************************************
  * @file    stm32g4xx_hal_fmac.c
  * @author  MCD Application Team
  * @brief   FMAC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the FMAC peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *           + Callback functions
  *           + IRQ handler management
  *           + Peripheral State and Error functions
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  *
  *  @verbatim
================================================================================
            ##### How to use this driver #####
================================================================================
    [..]
      The FMAC HAL driver can be used as follows:

      (#) Initialize the FMAC low level resources by implementing the @ref HAL_FMAC_MspInit():
          (++) Enable the FMAC interface clock using @ref __HAL_RCC_FMAC_CLK_ENABLE().
          (++) In case of using interrupts (e.g. access configured as FMAC_BUFFER_ACCESS_IT):
               (+++) Configure the FMAC interrupt priority using @ref HAL_NVIC_SetPriority().
               (+++) Enable the FMAC IRQ handler using @ref HAL_NVIC_EnableIRQ().
               (+++) In FMAC IRQ handler, call @ref HAL_FMAC_IRQHandler().
          (++) In case of using DMA to control data transfer (e.g. access configured
               as FMAC_BUFFER_ACCESS_DMA):
               (+++) Enable the DMA interface clock using @ref __HAL_RCC_DMA1_CLK_ENABLE()
                     or @ref __HAL_RCC_DMA2_CLK_ENABLE() depending on the used DMA instance.
               (+++) Enable the DMAMUX1 interface clock using @ref __HAL_RCC_DMAMUX1_CLK_ENABLE().
               (+++) If the initialization of the internal buffers (coefficients, input,
                     output) is done via DMA, configure and enable one DMA channel for
                     managing data transfer from memory to memory (preload channel).
               (+++) If the input buffer is accessed via DMA, configure and enable one
                     DMA channel for managing data transfer from memory to peripheral
                     (input channel).
               (+++) If the output buffer is accessed via DMA, configure and enable
                     one DMA channel for managing data transfer from peripheral to
                     memory (output channel).
               (+++) Associate the initialized DMA handle(s) to the FMAC DMA handle(s)
                     using @ref __HAL_LINKDMA().
               (+++) Configure the priority and enable the NVIC for the transfer complete
                     interrupt on the enabled DMA channel(s) using @ref HAL_NVIC_SetPriority()
                     and @ref HAL_NVIC_EnableIRQ().

      (#) Initialize the FMAC HAL using @ref HAL_FMAC_Init(). This function
          resorts to @ref HAL_FMAC_MspInit() for low-level initialization.

      (#) Configure the FMAC processing (filter) using @ref HAL_FMAC_FilterConfig()
          or @ref HAL_FMAC_FilterConfig_DMA().
          This function:
          (++) Defines the memory area within the FMAC internal memory
               (input, coefficients, output) and the associated threshold (input, output).
          (++) Configures the filter and its parameters:
               (+++) Finite Impulse Response (FIR) filter (also known as convolution).
               (+++) Infinite Impulse Response (IIR) filter (direct form 1).
          (++) Choose the way to access to the input and output buffers: none, polling,
               DMA, IT. "none" means the input and/or output data will be handled by
               another IP (ADC, DAC, etc.).
          (++) Enable the error interruptions in the input access and/or the output
               access is done through IT/DMA. If an error occurs, the interruption
               will be triggered in loop. In order to recover, the user will have
               to reset the IP with the sequence @ref HAL_FMAC_DeInit / @ref HAL_FMAC_Init.
               Optionally, he can also disable the interrupt using @ref __HAL_FMAC_DISABLE_IT;
               the error status will be kept, but no more interrupt will be triggered.
          (++) Write the provided coefficients into the internal memory using polling
               mode ( @ref HAL_FMAC_FilterConfig() ) or DMA ( @ref HAL_FMAC_FilterConfig_DMA() ).
               In the DMA case, @ref HAL_FMAC_FilterConfigCallback() is called when
               the handling is over.

       (#) Optionally, the user can enable the error interruption related to
           saturation by calling @ref __HAL_FMAC_ENABLE_IT. This helps in debugging the
           filter. If a saturation occurs, the interruption will be triggered in loop.
           In order to recover, the user will have to:
           (++) Disable the interruption by calling @ref __HAL_FMAC_DISABLE_IT if
                the user wishes to continue all the same.
           (++) Reset the IP with the sequence @ref HAL_FMAC_DeInit / @ref HAL_FMAC_Init.

       (#) Optionally, preload input (FIR, IIR) and output (IIR) data using
           @ref HAL_FMAC_FilterPreload() or @ref HAL_FMAC_FilterPreload_DMA().
           In the DMA case, @ref HAL_FMAC_FilterPreloadCallback() is called when
           the handling is over.
           This step is optional as the filter can be started without preloaded
           data.

       (#) Start the FMAC processing (filter) using @ref HAL_FMAC_FilterStart().
           This function also configures the output buffer that will be filled from
           the circular internal output buffer. The function returns immediately
           without updating the provided buffer. The IP processing will be active until
           @ref HAL_FMAC_FilterStop() is called.

       (#) If the input internal buffer is accessed via DMA, @ref HAL_FMAC_HalfGetDataCallback()
           will be called to indicate that half of the input buffer has been handled.

       (#) If the input internal buffer is accessed via DMA or interrupt, @ref HAL_FMAC_GetDataCallback()
           will be called to require new input data. It will be provided through
           @ref HAL_FMAC_AppendFilterData() if the DMA isn't in circular mode.

       (#) If the output internal buffer is accessed via DMA, @ref HAL_FMAC_HalfOutputDataReadyCallback()
           will be called to indicate that half of the output buffer has been handled.

       (#) If the output internal buffer is accessed via DMA or interrupt,
           @ref HAL_FMAC_OutputDataReadyCallback() will be called to require a new output
           buffer. It will be provided through @ref HAL_FMAC_ConfigFilterOutputBuffer()
           if the DMA isn't in circular mode.

       (#) In all modes except none, provide new input data to be processed via @ref HAL_FMAC_AppendFilterData().
           This function should only be called once the previous input data has been handled
           (the preloaded input data isn't concerned).

       (#) In all modes except none, provide a new output buffer to be filled via
           @ref HAL_FMAC_ConfigFilterOutputBuffer(). This function should only be called once the previous
           user's output buffer has been filled.

       (#) In polling mode, handle the input and output data using @ref HAL_FMAC_PollFilterData().
           This function:
           (++) Write the user's input data (provided via @ref HAL_FMAC_AppendFilterData())
                into the FMAC input memory area.
           (++) Read the FMAC output memory area and write it into the user's output buffer.
           It will return either when:
           (++) the user's output buffer is filled.
           (++) the user's input buffer has been handled.
           The unused data (unread input data or free output data) will not be saved.
           The user will have to use the updated input and output sizes to keep track
           of them.

       (#) Stop the FMAC processing (filter) using @ref HAL_FMAC_FilterStop().

       (#) Call @ref HAL_FMAC_DeInit() to de-initialize the FMAC peripheral. This function
           resorts to @ref HAL_FMAC_MspDeInit() for low-level de-initialization.

  ##### Callback registration #####
  ==================================

    [..]
      The compilation define USE_HAL_FMAC_REGISTER_CALLBACKS when set to 1
      allows the user to configure dynamically the driver callbacks.

    [..]
      Use Function @ref HAL_FMAC_RegisterCallback() to register a user callback.
      Function @ref HAL_FMAC_RegisterCallback() allows to register following callbacks:
      (+) ErrorCallback               : Error Callback.
      (+) HalfGetDataCallback         : Get Half Data Callback.
      (+) GetDataCallback             : Get Data Callback.
      (+) HalfOutputDataReadyCallback : Half Output Data Ready Callback.
      (+) OutputDataReadyCallback     : Output Data Ready Callback.
      (+) FilterConfigCallback        : Filter Configuration Callback.
      (+) FilterPreloadCallback       : Filter Preload Callback.
      (+) MspInitCallback             : FMAC MspInit.
      (+) MspDeInitCallback           : FMAC MspDeInit.
      This function takes as parameters the HAL peripheral handle, the Callback ID
      and a pointer to the user callback function.

    [..]
      Use function @ref HAL_FMAC_UnRegisterCallback() to reset a callback to the default
      weak (surcharged) function.
      @ref HAL_FMAC_UnRegisterCallback() takes as parameters the HAL peripheral handle
      and the Callback ID.
      This function allows to reset following callbacks:
      (+) ErrorCallback               : Error Callback.
      (+) HalfGetDataCallback         : Get Half Data Callback.
      (+) GetDataCallback             : Get Data Callback.
      (+) HalfOutputDataReadyCallback : Half Output Data Ready Callback.
      (+) OutputDataReadyCallback     : Output Data Ready Callback.
      (+) FilterConfigCallback        : Filter Configuration Callback.
      (+) FilterPreloadCallback       : Filter Preload Callback.
      (+) MspInitCallback             : FMAC MspInit.
      (+) MspDeInitCallback           : FMAC MspDeInit.

    [..]
      By default, after the @ref HAL_FMAC_Init() and when the state is HAL_FMAC_STATE_RESET
      all callbacks are set to the corresponding weak (surcharged) functions:
      examples @ref GetDataCallback(), @ref OutputDataReadyCallback().
      Exception done for MspInit and MspDeInit functions that are respectively
      reset to the legacy weak (surcharged) functions in the @ref HAL_FMAC_Init()
      and @ref HAL_FMAC_DeInit() only when these callbacks are null (not registered beforehand).
      If not, MspInit or MspDeInit are not null, the @ref HAL_FMAC_Init() and @ref HAL_FMAC_DeInit()
      keep and use the user MspInit/MspDeInit callbacks (registered beforehand).

    [..]
      Callbacks can be registered/unregistered in HAL_FMAC_STATE_READY state only.
      Exception done MspInit/MspDeInit that can be registered/unregistered
      in HAL_FMAC_STATE_READY or HAL_FMAC_STATE_RESET state, thus registered (user)
      MspInit/DeInit callbacks can be used during the Init/DeInit.
      In that case first register the MspInit/MspDeInit user callbacks
      using @ref HAL_FMAC_RegisterCallback() before calling @ref HAL_FMAC_DeInit()
      or @ref HAL_FMAC_Init() function.

    [..]
      When the compilation define USE_HAL_FMAC_REGISTER_CALLBACKS is set to 0 or
      not defined, the callback registration feature is not available
      and weak (surcharged) callbacks are used.


  @endverbatim
  *
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

#ifdef HAL_FMAC_MODULE_ENABLED

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

/** @defgroup FMAC FMAC
  * @brief    FMAC HAL driver module
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/** @defgroup  FMAC_Private_Constants   FMAC Private Constants
  * @{
  */

#define MAX_FILTER_DATA_SIZE_TO_HANDLE ((uint16_t) 0xFFU)
#define MAX_PRELOAD_INDEX      0xFFU
#define PRELOAD_ACCESS_DMA     0x00U
#define PRELOAD_ACCESS_POLLING 0x01U
#define POLLING_DISABLED       0U
#define POLLING_ENABLED        1U
#define POLLING_NOT_STOPPED    0U
#define POLLING_STOPPED        1U
/* FMAC polling-based communications time-out value */
#define HAL_FMAC_TIMEOUT_VALUE         1000U
/* FMAC reset time-out value */
#define HAL_FMAC_RESET_TIMEOUT_VALUE   500U
/* DMA Read Requests Enable */
#define FMAC_DMA_REN                   FMAC_CR_DMAREN
/* DMA Write Channel Enable */
#define FMAC_DMA_WEN                   FMAC_CR_DMAWEN
/* FMAC Execution Enable */
#define FMAC_START                     FMAC_PARAM_START

/**
  * @}
  */


/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup  FMAC_Private_Macros   FMAC Private Macros
  * @{
  */

/**
  * @brief  Get the X1 memory area size.
  * @param  __HANDLE__ FMAC handle.
  * @retval X1_BUF_SIZE
  */
#define FMAC_GET_X1_SIZE(__HANDLE__) \
  ((((__HANDLE__)->Instance->X1BUFCFG) & (FMAC_X1BUFCFG_X1_BUF_SIZE)) >> (FMAC_X1BUFCFG_X1_BUF_SIZE_Pos))

/**
  * @brief  Get the X1 watermark.
  * @param  __HANDLE__ FMAC handle.
  * @retval FULL_WM
  */
#define FMAC_GET_X1_FULL_WM(__HANDLE__) \
  (((__HANDLE__)->Instance->X1BUFCFG) & (FMAC_X1BUFCFG_FULL_WM))

/**
  * @brief  Get the X2 memory area size.
  * @param  __HANDLE__ FMAC handle.
  * @retval X2_BUF_SIZE
  */
#define FMAC_GET_X2_SIZE(__HANDLE__) \
  ((((__HANDLE__)->Instance->X2BUFCFG) & (FMAC_X2BUFCFG_X2_BUF_SIZE)) >> (FMAC_X2BUFCFG_X2_BUF_SIZE_Pos))

/**
  * @brief  Get the Y memory area size.
  * @param  __HANDLE__ FMAC handle.
  * @retval Y_BUF_SIZE
  */
#define FMAC_GET_Y_SIZE(__HANDLE__) \
  ((((__HANDLE__)->Instance->YBUFCFG) & (FMAC_YBUFCFG_Y_BUF_SIZE)) >> (FMAC_YBUFCFG_Y_BUF_SIZE_Pos))

/**
  * @brief  Get the Y watermark.
  * @param  __HANDLE__ FMAC handle.
  * @retval EMPTY_WM
  */
#define FMAC_GET_Y_EMPTY_WM(__HANDLE__) \
  (((__HANDLE__)->Instance->YBUFCFG) & (FMAC_YBUFCFG_EMPTY_WM))

/**
  * @brief  Get the start bit state.
  * @param  __HANDLE__ FMAC handle.
  * @retval START
  */
#define FMAC_GET_START_BIT(__HANDLE__) \
  ((((__HANDLE__)->Instance->PARAM) & (FMAC_PARAM_START)) >> (FMAC_PARAM_START_Pos))

/**
  * @brief  Get the threshold matching the watermark.
  * @param  __WM__ Watermark value.
  * @retval THRESHOLD
  */
#define FMAC_GET_THRESHOLD_FROM_WM(__WM__) (((__WM__) == FMAC_THRESHOLD_1)? 1U: \
                                            ((__WM__) == FMAC_THRESHOLD_2)? 2U: \
                                            ((__WM__) == FMAC_THRESHOLD_4)? 4U:8U)

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static HAL_StatusTypeDef FMAC_Reset(FMAC_HandleTypeDef *hfmac);
static void FMAC_ResetDataPointers(FMAC_HandleTypeDef *hfmac);
static void FMAC_ResetOutputStateAndDataPointers(FMAC_HandleTypeDef *hfmac);
static void FMAC_ResetInputStateAndDataPointers(FMAC_HandleTypeDef *hfmac);
static HAL_StatusTypeDef FMAC_FilterConfig(FMAC_HandleTypeDef *hfmac, FMAC_FilterConfigTypeDef *pConfig,
                                           uint8_t PreloadAccess);
static HAL_StatusTypeDef FMAC_FilterPreload(FMAC_HandleTypeDef *hfmac, int16_t *pInput, uint8_t InputSize,
                                            int16_t *pOutput, uint8_t OutputSize, uint8_t PreloadAccess);
static void FMAC_WritePreloadDataIncrementPtr(FMAC_HandleTypeDef *hfmac, int16_t **ppData, uint8_t Size);
static HAL_StatusTypeDef FMAC_WaitOnStartUntilTimeout(FMAC_HandleTypeDef *hfmac, uint32_t Tickstart, uint32_t Timeout);
static HAL_StatusTypeDef FMAC_AppendFilterDataUpdateState(FMAC_HandleTypeDef *hfmac, int16_t *pInput,
                                                          uint16_t *pInputSize);
static HAL_StatusTypeDef FMAC_ConfigFilterOutputBufferUpdateState(FMAC_HandleTypeDef *hfmac, int16_t *pOutput,
                                                                  uint16_t *pOutputSize);
static void FMAC_WriteDataIncrementPtr(FMAC_HandleTypeDef *hfmac, uint16_t MaxSizeToWrite);
static void FMAC_ReadDataIncrementPtr(FMAC_HandleTypeDef *hfmac, uint16_t MaxSizeToRead);
static void FMAC_DMAHalfGetData(DMA_HandleTypeDef *hdma);
static void FMAC_DMAGetData(DMA_HandleTypeDef *hdma);
static void FMAC_DMAHalfOutputDataReady(DMA_HandleTypeDef *hdma);
static void FMAC_DMAOutputDataReady(DMA_HandleTypeDef *hdma);
static void FMAC_DMAFilterConfig(DMA_HandleTypeDef *hdma);
static void FMAC_DMAFilterPreload(DMA_HandleTypeDef *hdma);
static void FMAC_DMAError(DMA_HandleTypeDef *hdma);

/* Functions Definition ------------------------------------------------------*/

/** @defgroup FMAC_Exported_Functions FMAC Exported Functions
  * @{
  */

/** @defgroup FMAC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
     #####       Initialization and de-initialization functions       #####
 ===============================================================================
    [..] This section provides functions allowing to:
      (+) Initialize the FMAC peripheral and the associated handle
      (+) DeInitialize the FMAC peripheral
      (+) Initialize the FMAC MSP (MCU Specific Package)
      (+) De-Initialize the FMAC MSP
      (+) Register a User FMAC Callback
      (+) Unregister a FMAC CallBack

    [..]

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the FMAC peripheral and the associated handle.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure.
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_Init(FMAC_HandleTypeDef *hfmac)
{
  HAL_StatusTypeDef status;

  /* Check the FMAC handle allocation */
  if (hfmac == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the instance */
  assert_param(IS_FMAC_ALL_INSTANCE(hfmac->Instance));

  if (hfmac->State == HAL_FMAC_STATE_RESET)
  {
    /* Initialize lock resource */
    hfmac->Lock = HAL_UNLOCKED;

#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
    /* Register the default callback functions */
    hfmac->ErrorCallback = HAL_FMAC_ErrorCallback;
    hfmac->HalfGetDataCallback = HAL_FMAC_HalfGetDataCallback;
    hfmac->GetDataCallback = HAL_FMAC_GetDataCallback;
    hfmac->HalfOutputDataReadyCallback = HAL_FMAC_HalfOutputDataReadyCallback;
    hfmac->OutputDataReadyCallback = HAL_FMAC_OutputDataReadyCallback;
    hfmac->FilterConfigCallback = HAL_FMAC_FilterConfigCallback;
    hfmac->FilterPreloadCallback = HAL_FMAC_FilterPreloadCallback;

    if (hfmac->MspInitCallback == NULL)
    {
      hfmac->MspInitCallback = HAL_FMAC_MspInit;
    }

    /* Init the low level hardware */
    hfmac->MspInitCallback(hfmac);
#else
    /* Init the low level hardware */
    HAL_FMAC_MspInit(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
  }

  /* Reset pInput and pOutput */
  hfmac->FilterParam = 0U;
  FMAC_ResetDataPointers(hfmac);

  /* Reset FMAC unit (internal pointers) */
  if (FMAC_Reset(hfmac) == HAL_TIMEOUT)
  {
    /* Update FMAC error code and FMAC peripheral state */
    hfmac->ErrorCode |= HAL_FMAC_ERROR_RESET;
    hfmac->State = HAL_FMAC_STATE_TIMEOUT;

    status = HAL_TIMEOUT;
  }
  else
  {
    /* Update FMAC error code and FMAC peripheral state */
    hfmac->ErrorCode = HAL_FMAC_ERROR_NONE;
    hfmac->State = HAL_FMAC_STATE_READY;

    status = HAL_OK;
  }

  __HAL_UNLOCK(hfmac);

  return status;
}

/**
  * @brief  De-initialize the FMAC peripheral.
  * @param  hfmac pointer to a FMAC structure.
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_DeInit(FMAC_HandleTypeDef *hfmac)
{
  /* Check the FMAC handle allocation */
  if (hfmac == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_FMAC_ALL_INSTANCE(hfmac->Instance));

  /* Change FMAC peripheral state */
  hfmac->State = HAL_FMAC_STATE_BUSY;

  /* Set FMAC error code to none */
  hfmac->ErrorCode = HAL_FMAC_ERROR_NONE;

  /* Reset pInput and pOutput */
  hfmac->FilterParam = 0U;
  FMAC_ResetDataPointers(hfmac);

#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  if (hfmac->MspDeInitCallback == NULL)
  {
    hfmac->MspDeInitCallback = HAL_FMAC_MspDeInit;
  }
  /* DeInit the low level hardware */
  hfmac->MspDeInitCallback(hfmac);
#else
  /* DeInit the low level hardware: CLOCK, NVIC, DMA */
  HAL_FMAC_MspDeInit(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */

  /* Change FMAC peripheral state */
  hfmac->State = HAL_FMAC_STATE_RESET;

  /* Always release Lock in case of de-initialization */
  __HAL_UNLOCK(hfmac);

  return HAL_OK;
}

/**
  * @brief  Initialize the FMAC MSP.
  * @param  hfmac FMAC handle.
  * @retval None
  */
__weak void HAL_FMAC_MspInit(FMAC_HandleTypeDef *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hfmac);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_FMAC_MspInit can be implemented in the user file
   */
}

/**
  * @brief  De-initialize the FMAC MSP.
  * @param  hfmac FMAC handle.
  * @retval None
  */
__weak void HAL_FMAC_MspDeInit(FMAC_HandleTypeDef *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hfmac);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_FMAC_MspDeInit can be implemented in the user file
   */
}

#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User FMAC Callback.
  * @note   The User FMAC Callback is to be used instead of the weak predefined callback.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  CallbackID ID of the callback to be registered.
  *         This parameter can be one of the following values:
  *           @arg @ref HAL_FMAC_ERROR_CB_ID Error Callback ID
  *           @arg @ref HAL_FMAC_HALF_GET_DATA_CB_ID Get Half Data Callback ID
  *           @arg @ref HAL_FMAC_GET_DATA_CB_ID Get Data Callback ID
  *           @arg @ref HAL_FMAC_HALF_OUTPUT_DATA_READY_CB_ID Half Output Data Ready Callback ID
  *           @arg @ref HAL_FMAC_OUTPUT_DATA_READY_CB_ID Output Data Ready Callback ID
  *           @arg @ref HAL_FMAC_FILTER_CONFIG_CB_ID Filter Configuration Callback ID
  *           @arg @ref HAL_FMAC_FILTER_PRELOAD_CB_ID Filter Preload Callback ID
  *           @arg @ref HAL_FMAC_MSPINIT_CB_ID FMAC MspInit ID
  *           @arg @ref HAL_FMAC_MSPDEINIT_CB_ID FMAC MspDeInit ID
  * @param  pCallback pointer to the Callback function.
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_RegisterCallback(FMAC_HandleTypeDef *hfmac, HAL_FMAC_CallbackIDTypeDef CallbackID,
                                            pFMAC_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the FMAC handle allocation */
  if (hfmac == NULL)
  {
    return HAL_ERROR;
  }

  if (pCallback == NULL)
  {
    /* Update the error code */
    hfmac->ErrorCode |= HAL_FMAC_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }
  __HAL_LOCK(hfmac);

  if (hfmac->State == HAL_FMAC_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_FMAC_ERROR_CB_ID :
        hfmac->ErrorCallback = pCallback;
        break;

      case HAL_FMAC_HALF_GET_DATA_CB_ID :
        hfmac->HalfGetDataCallback = pCallback;
        break;

      case HAL_FMAC_GET_DATA_CB_ID :
        hfmac->GetDataCallback = pCallback;
        break;

      case HAL_FMAC_HALF_OUTPUT_DATA_READY_CB_ID :
        hfmac->HalfOutputDataReadyCallback = pCallback;
        break;

      case HAL_FMAC_OUTPUT_DATA_READY_CB_ID :
        hfmac->OutputDataReadyCallback = pCallback;
        break;

      case HAL_FMAC_FILTER_CONFIG_CB_ID :
        hfmac->FilterConfigCallback = pCallback;
        break;

      case HAL_FMAC_FILTER_PRELOAD_CB_ID :
        hfmac->FilterPreloadCallback = pCallback;
        break;

      case HAL_FMAC_MSPINIT_CB_ID :
        hfmac->MspInitCallback = pCallback;
        break;

      case HAL_FMAC_MSPDEINIT_CB_ID :
        hfmac->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hfmac->ErrorCode |= HAL_FMAC_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hfmac->State == HAL_FMAC_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_FMAC_MSPINIT_CB_ID :
        hfmac->MspInitCallback = pCallback;
        break;

      case HAL_FMAC_MSPDEINIT_CB_ID :
        hfmac->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hfmac->ErrorCode |= HAL_FMAC_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hfmac->ErrorCode |= HAL_FMAC_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  __HAL_UNLOCK(hfmac);

  return status;
}

/**
  * @brief  Unregister a FMAC CallBack.
  * @note   The FMAC callback is redirected to the weak predefined callback.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module
  * @param  CallbackID ID of the callback to be unregistered.
  *         This parameter can be one of the following values:
  *           @arg @ref HAL_FMAC_ERROR_CB_ID Error Callback ID
  *           @arg @ref HAL_FMAC_HALF_GET_DATA_CB_ID Get Half Data Callback ID
  *           @arg @ref HAL_FMAC_GET_DATA_CB_ID Get Data Callback ID
  *           @arg @ref HAL_FMAC_HALF_OUTPUT_DATA_READY_CB_ID Half Output Data Ready Callback ID
  *           @arg @ref HAL_FMAC_OUTPUT_DATA_READY_CB_ID Output Data Ready Callback ID
  *           @arg @ref HAL_FMAC_FILTER_CONFIG_CB_ID Filter Configuration Callback ID
  *           @arg @ref HAL_FMAC_FILTER_PRELOAD_CB_ID Filter Preload Callback ID
  *           @arg @ref HAL_FMAC_MSPINIT_CB_ID FMAC MspInit ID
  *           @arg @ref HAL_FMAC_MSPDEINIT_CB_ID FMAC MspDeInit ID
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_UnRegisterCallback(FMAC_HandleTypeDef *hfmac, HAL_FMAC_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the FMAC handle allocation */
  if (hfmac == NULL)
  {
    return HAL_ERROR;
  }

  __HAL_LOCK(hfmac);

  if (hfmac->State == HAL_FMAC_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_FMAC_ERROR_CB_ID :
        hfmac->ErrorCallback = HAL_FMAC_ErrorCallback;                             /* Legacy weak ErrorCallback               */
        break;

      case HAL_FMAC_HALF_GET_DATA_CB_ID :
        hfmac->HalfGetDataCallback = HAL_FMAC_HalfGetDataCallback;                 /* Legacy weak HalfGetDataCallback         */
        break;

      case HAL_FMAC_GET_DATA_CB_ID :
        hfmac->GetDataCallback = HAL_FMAC_GetDataCallback;                         /* Legacy weak GetDataCallback             */
        break;

      case HAL_FMAC_HALF_OUTPUT_DATA_READY_CB_ID :
        hfmac->HalfOutputDataReadyCallback = HAL_FMAC_HalfOutputDataReadyCallback; /* Legacy weak HalfOutputDataReadyCallback */
        break;

      case HAL_FMAC_OUTPUT_DATA_READY_CB_ID :
        hfmac->OutputDataReadyCallback = HAL_FMAC_OutputDataReadyCallback;         /* Legacy weak OutputDataReadyCallback     */
        break;

      case HAL_FMAC_FILTER_CONFIG_CB_ID :
        hfmac->FilterConfigCallback = HAL_FMAC_FilterConfigCallback;               /* Legacy weak FilterConfigCallback        */
        break;

      case HAL_FMAC_FILTER_PRELOAD_CB_ID :
        hfmac->FilterPreloadCallback = HAL_FMAC_FilterPreloadCallback;             /* Legacy weak FilterPreloadCallback       */
        break;

      case HAL_FMAC_MSPINIT_CB_ID :
        hfmac->MspInitCallback = HAL_FMAC_MspInit;                                 /* Legacy weak MspInitCallback             */
        break;

      case HAL_FMAC_MSPDEINIT_CB_ID :
        hfmac->MspDeInitCallback = HAL_FMAC_MspDeInit;                             /* Legacy weak MspDeInitCallback           */
        break;

      default :
        /* Update the error code */
        hfmac->ErrorCode |= HAL_FMAC_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hfmac->State == HAL_FMAC_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_FMAC_MSPINIT_CB_ID :
        hfmac->MspInitCallback = HAL_FMAC_MspInit;
        break;

      case HAL_FMAC_MSPDEINIT_CB_ID :
        hfmac->MspDeInitCallback = HAL_FMAC_MspDeInit;
        break;

      default :
        /* Update the error code */
        hfmac->ErrorCode |= HAL_FMAC_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hfmac->ErrorCode |= HAL_FMAC_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status = HAL_ERROR;
  }

  __HAL_UNLOCK(hfmac);

  return status;
}
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup FMAC_Exported_Functions_Group2 Peripheral Control functions
  * @brief    Control functions.
  *
@verbatim
  ==============================================================================
                      ##### Peripheral Control functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the FMAC peripheral: memory area, filter type and parameters,
          way to access to the input and output memory area (none, polling, IT, DMA).
      (+) Start the FMAC processing (filter).
      (+) Handle the input data that will be provided into FMAC.
      (+) Handle the output data provided by FMAC.
      (+) Stop the FMAC processing (filter).

@endverbatim
  * @{
  */

/**
  * @brief  Configure the FMAC filter.
  * @note   The configuration is done according to the parameters
  *         specified in the FMAC_FilterConfigTypeDef structure.
  *         The provided data will be loaded using polling mode.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  pConfig pointer to a FMAC_FilterConfigTypeDef structure that
  *         contains the FMAC configuration information.
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_FilterConfig(FMAC_HandleTypeDef *hfmac, FMAC_FilterConfigTypeDef *pConfig)
{
  return (FMAC_FilterConfig(hfmac, pConfig, PRELOAD_ACCESS_POLLING));
}

/**
  * @brief  Configure the FMAC filter.
  * @note   The configuration is done according to the parameters
  *         specified in the FMAC_FilterConfigTypeDef structure.
  *         The provided data will be loaded using DMA.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  pConfig pointer to a FMAC_FilterConfigTypeDef structure that
  *         contains the FMAC configuration information.
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_FilterConfig_DMA(FMAC_HandleTypeDef *hfmac, FMAC_FilterConfigTypeDef *pConfig)
{
  return (FMAC_FilterConfig(hfmac, pConfig, PRELOAD_ACCESS_DMA));
}

/**
  * @brief  Preload the input (FIR, IIR) and output data (IIR) of the FMAC filter.
  * @note   The set(s) of data will be used by FMAC as soon as @ref HAL_FMAC_FilterStart is called.
  *         The provided data will be loaded using polling mode.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  pInput Preloading of the first elements of the input buffer (X1).
  *         If not needed (no data available when starting), it should be set to NULL.
  * @param  InputSize Size of the input vector.
  *         As pInput is used for preloading data, it cannot be bigger than the input memory area.
  * @param  pOutput [IIR] Preloading of the first elements of the output vector (Y).
  *         If not needed, it should be set to NULL.
  * @param  OutputSize Size of the output vector.
  *         As pOutput is used for preloading data, it cannot be bigger than the output memory area.
  * @note   The input and the output buffers can be filled by calling several times @ref HAL_FMAC_FilterPreload
  *         (each call filling partly the buffers). In case of overflow (too much data provided through
  *         all these calls), an error will be returned.
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_FilterPreload(FMAC_HandleTypeDef *hfmac, int16_t *pInput, uint8_t InputSize,
                                         int16_t *pOutput, uint8_t OutputSize)
{
  return (FMAC_FilterPreload(hfmac, pInput, InputSize, pOutput, OutputSize, PRELOAD_ACCESS_POLLING));
}

/**
  * @brief  Preload the input (FIR, IIR) and output data (IIR) of the FMAC filter.
  * @note   The set(s) of data will be used by FMAC as soon as @ref HAL_FMAC_FilterStart is called.
  *         The provided data will be loaded using DMA.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  pInput Preloading of the first elements of the input buffer (X1).
  *         If not needed (no data available when starting), it should be set to NULL.
  * @param  InputSize Size of the input vector.
  *         As pInput is used for preloading data, it cannot be bigger than the input memory area.
  * @param  pOutput [IIR] Preloading of the first elements of the output vector (Y).
  *         If not needed, it should be set to NULL.
  * @param  OutputSize Size of the output vector.
  *         As pOutput is used for preloading data, it cannot be bigger than the output memory area.
  * @note   The input and the output buffers can be filled by calling several times @ref HAL_FMAC_FilterPreload
  *         (each call filling partly the buffers). In case of overflow (too much data provided through
  *         all these calls), an error will be returned.
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_FilterPreload_DMA(FMAC_HandleTypeDef *hfmac, int16_t *pInput, uint8_t InputSize,
                                             int16_t *pOutput, uint8_t OutputSize)
{
  return (FMAC_FilterPreload(hfmac, pInput, InputSize, pOutput, OutputSize, PRELOAD_ACCESS_DMA));
}


/**
  * @brief  Start the FMAC processing according to the existing FMAC configuration.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  pOutput pointer to buffer where output data of FMAC processing will be stored
  *         in the next steps.
  *         If it is set to NULL, the output will not be read and it will be up to
  *         an external IP to empty the output buffer.
  * @param  pOutputSize pointer to the size of the output buffer. The number of read data will be written here.
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_FilterStart(FMAC_HandleTypeDef *hfmac, int16_t *pOutput, uint16_t *pOutputSize)
{
  uint32_t tmpcr = 0U;
  HAL_StatusTypeDef status;

  /* Check the START bit state */
  if (FMAC_GET_START_BIT(hfmac) != 0U)
  {
    return HAL_ERROR;
  }

  /* Check that a valid configuration was done previously */
  if (hfmac->FilterParam == 0U)
  {
    return HAL_ERROR;
  }

  /* Check handle state is ready */
  if (hfmac->State == HAL_FMAC_STATE_READY)
  {
    /* Change the FMAC state */
    hfmac->State = HAL_FMAC_STATE_BUSY;

    /* CR: Configure the input access (error interruptions enabled only for IT or DMA) */
    if (hfmac->InputAccess == FMAC_BUFFER_ACCESS_DMA)
    {
      tmpcr |= FMAC_DMA_WEN;
    }
    else if (hfmac->InputAccess == FMAC_BUFFER_ACCESS_IT)
    {
      tmpcr |= FMAC_IT_WIEN;
    }
    else
    {
      /* nothing to do */
    }

    /* CR: Configure the output access (error interruptions enabled only for IT or DMA) */
    if (hfmac->OutputAccess == FMAC_BUFFER_ACCESS_DMA)
    {
      tmpcr |= FMAC_DMA_REN;
    }
    else if (hfmac->OutputAccess == FMAC_BUFFER_ACCESS_IT)
    {
      tmpcr |= FMAC_IT_RIEN;
    }
    else
    {
      /* nothing to do */
    }

    /* CR: Write the configuration */
    MODIFY_REG(hfmac->Instance->CR, \
               FMAC_IT_RIEN | FMAC_IT_WIEN | FMAC_DMA_REN | FMAC_CR_DMAWEN, \
               tmpcr);

    /* Register the new output buffer */
    status = FMAC_ConfigFilterOutputBufferUpdateState(hfmac, pOutput, pOutputSize);

    if (status == HAL_OK)
    {
      /* PARAM: Start the filter ( this can generate interrupts before the end of the HAL_FMAC_FilterStart ) */
      WRITE_REG(hfmac->Instance->PARAM, (uint32_t)(hfmac->FilterParam));
    }

    /* Reset the busy flag (do not overwrite the possible write and read flag) */
    hfmac->State = HAL_FMAC_STATE_READY;
  }
  else
  {
    status = HAL_BUSY;
  }

  return status;
}

/**
  * @brief  Provide a new input buffer that will be loaded into the FMAC input memory area.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  pInput New input vector (additional input data).
  * @param  pInputSize Size of the input vector (if all the data can't be
  *         written, it will be updated with the number of data read from FMAC).
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_AppendFilterData(FMAC_HandleTypeDef *hfmac, int16_t *pInput, uint16_t *pInputSize)
{
  HAL_StatusTypeDef status;

  /* Check the function parameters */
  if ((pInput == NULL) || (pInputSize == NULL))
  {
    return HAL_ERROR;
  }
  if (*pInputSize == 0U)
  {
    return HAL_ERROR;
  }

  /* Check the START bit state */
  if (FMAC_GET_START_BIT(hfmac) == 0U)
  {
    return HAL_ERROR;
  }

  /* Check the FMAC configuration */
  if (hfmac->InputAccess == FMAC_BUFFER_ACCESS_NONE)
  {
    return HAL_ERROR;
  }

  /* Check whether the previous input vector has been handled */
  if ((hfmac->pInputSize != NULL) && (hfmac->InputCurrentSize < * (hfmac->pInputSize)))
  {
    return HAL_BUSY;
  }

  /* Check that FMAC was initialized and that no writing is already ongoing */
  if (hfmac->WrState == HAL_FMAC_STATE_READY)
  {
    /* Register the new input buffer */
    status = FMAC_AppendFilterDataUpdateState(hfmac, pInput, pInputSize);
  }
  else
  {
    status = HAL_BUSY;
  }

  return status;
}

/**
  * @brief  Provide a new output buffer to be filled with the data computed by FMAC unit.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  pOutput New output vector.
  * @param  pOutputSize Size of the output vector (if the vector can't
  *         be entirely filled, pOutputSize will be updated with the number
  *         of data read from FMAC).
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_ConfigFilterOutputBuffer(FMAC_HandleTypeDef *hfmac, int16_t *pOutput, uint16_t *pOutputSize)
{
  HAL_StatusTypeDef status;

  /* Check the function parameters */
  if ((pOutput == NULL) || (pOutputSize == NULL))
  {
    return HAL_ERROR;
  }
  if (*pOutputSize == 0U)
  {
    return HAL_ERROR;
  }

  /* Check the START bit state */
  if (FMAC_GET_START_BIT(hfmac) == 0U)
  {
    return HAL_ERROR;
  }

  /* Check the FMAC configuration */
  if (hfmac->OutputAccess == FMAC_BUFFER_ACCESS_NONE)
  {
    return HAL_ERROR;
  }

  /* Check whether the previous output vector has been handled */
  if ((hfmac->pOutputSize != NULL) && (hfmac->OutputCurrentSize < * (hfmac->pOutputSize)))
  {
    return HAL_BUSY;
  }

  /* Check that FMAC was initialized and that not reading is already ongoing */
  if (hfmac->RdState == HAL_FMAC_STATE_READY)
  {
    /* Register the new output buffer */
    status = FMAC_ConfigFilterOutputBufferUpdateState(hfmac, pOutput, pOutputSize);
  }
  else
  {
    status = HAL_BUSY;
  }

  return status;
}

/**
  * @brief  Handle the input and/or output data in polling mode
  * @note   This function writes the previously provided user's input data and
  *         fills the previously provided user's output buffer,
  *         according to the existing FMAC configuration (polling mode only).
  *         The function returns when the input data has been handled or
  *         when the output data is filled. The possible unused data isn't
  *         kept. It will be up to the user to handle it. The previously
  *         provided pInputSize and pOutputSize will be used to indicate to the
  *         size of the read/written data to the user.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  Timeout timeout value.
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_PollFilterData(FMAC_HandleTypeDef *hfmac, uint32_t Timeout)
{
  uint32_t tickstart;
  uint8_t inpolling;
  uint8_t inpollingover = POLLING_NOT_STOPPED;
  uint8_t outpolling;
  uint8_t outpollingover = POLLING_NOT_STOPPED;
  HAL_StatusTypeDef status;

  /* Check the START bit state */
  if (FMAC_GET_START_BIT(hfmac) == 0U)
  {
    return HAL_ERROR;
  }

  /* Check the configuration */

  /* Get the input and output mode (if no buffer was previously provided, nothing will be read/written) */
  if ((hfmac->InputAccess  == FMAC_BUFFER_ACCESS_POLLING) && (hfmac->pInput  != NULL))
  {
    inpolling = POLLING_ENABLED;
  }
  else
  {
    inpolling = POLLING_DISABLED;
  }
  if ((hfmac->OutputAccess == FMAC_BUFFER_ACCESS_POLLING) && (hfmac->pOutput != NULL))
  {
    outpolling = POLLING_ENABLED;
  }
  else
  {
    outpolling = POLLING_DISABLED;
  }

  /* Check the configuration */
  if ((inpolling == POLLING_DISABLED) && (outpolling == POLLING_DISABLED))
  {
    return HAL_ERROR;
  }

  /* Check handle state is ready */
  if (hfmac->State == HAL_FMAC_STATE_READY)
  {
    /* Change the FMAC state */
    hfmac->State = HAL_FMAC_STATE_BUSY;

    /* Get tick */
    tickstart = HAL_GetTick();

    /* Loop on reading and writing until timeout */
    while ((HAL_GetTick() - tickstart) < Timeout)
    {
      /* X1: Check the mode: polling or none */
      if (inpolling != POLLING_DISABLED)
      {
        FMAC_WriteDataIncrementPtr(hfmac, MAX_FILTER_DATA_SIZE_TO_HANDLE);
        if (hfmac->InputCurrentSize == *(hfmac->pInputSize))
        {
          inpollingover = POLLING_STOPPED;
        }
      }

      /* Y: Check the mode: polling or none */
      if (outpolling != POLLING_DISABLED)
      {
        FMAC_ReadDataIncrementPtr(hfmac, MAX_FILTER_DATA_SIZE_TO_HANDLE);
        if (hfmac->OutputCurrentSize == *(hfmac->pOutputSize))
        {
          outpollingover = POLLING_STOPPED;
        }
      }

      /* Exit if there isn't data to handle anymore on one side or another */
      if ((inpollingover != POLLING_NOT_STOPPED) || (outpollingover != POLLING_NOT_STOPPED))
      {
        break;
      }
    }

    /* Change the FMAC state; update the input and output sizes; reset the indexes */
    if (inpolling != POLLING_DISABLED)
    {
      (*(hfmac->pInputSize))  = hfmac->InputCurrentSize;
      FMAC_ResetInputStateAndDataPointers(hfmac);
    }
    if (outpolling != POLLING_DISABLED)
    {
      (*(hfmac->pOutputSize)) = hfmac->OutputCurrentSize;
      FMAC_ResetOutputStateAndDataPointers(hfmac);
    }

    /* Reset the busy flag (do not overwrite the possible write and read flag) */
    hfmac->State = HAL_FMAC_STATE_READY;

    if ((HAL_GetTick() - tickstart) >= Timeout)
    {
      hfmac->ErrorCode |= HAL_FMAC_ERROR_TIMEOUT;
      status = HAL_TIMEOUT;
    }
    else
    {
      status = HAL_OK;
    }
  }
  else
  {
    status = HAL_BUSY;
  }

  return status;
}

/**
  * @brief  Stop the FMAC processing.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @retval HAL_StatusTypeDef HAL status
  */
HAL_StatusTypeDef HAL_FMAC_FilterStop(FMAC_HandleTypeDef *hfmac)
{
  HAL_StatusTypeDef status;

  /* Check handle state is ready */
  if (hfmac->State == HAL_FMAC_STATE_READY)
  {
    /* Change the FMAC state */
    hfmac->State = HAL_FMAC_STATE_BUSY;

    /* Set the START bit to 0 (stop the previously configured filter) */
    CLEAR_BIT(hfmac->Instance->PARAM, FMAC_PARAM_START);

    /* Disable the interrupts in order to avoid crossing cases */
    CLEAR_BIT(hfmac->Instance->CR, FMAC_DMA_REN | FMAC_DMA_WEN | FMAC_IT_RIEN | FMAC_IT_WIEN);

    /* In case of IT, update the sizes */
    if ((hfmac->InputAccess == FMAC_BUFFER_ACCESS_IT) && (hfmac->pInput != NULL))
    {
      (*(hfmac->pInputSize))  = hfmac->InputCurrentSize;
    }
    if ((hfmac->OutputAccess == FMAC_BUFFER_ACCESS_IT) && (hfmac->pOutput != NULL))
    {
      (*(hfmac->pOutputSize)) = hfmac->OutputCurrentSize;
    }

    /* Reset FMAC unit (internal pointers) */
    if (FMAC_Reset(hfmac) == HAL_TIMEOUT)
    {
      /* Update FMAC error code and FMAC peripheral state */
      hfmac->ErrorCode = HAL_FMAC_ERROR_RESET;
      hfmac->State = HAL_FMAC_STATE_TIMEOUT;
      status = HAL_TIMEOUT;
    }
    else
    {
      /* Reset the data pointers */
      FMAC_ResetDataPointers(hfmac);

      status = HAL_OK;
    }

    /* Reset the busy flag */
    hfmac->State = HAL_FMAC_STATE_READY;
  }
  else
  {
    status = HAL_BUSY;
  }

  return status;
}

/**
  * @}
  */

/** @defgroup FMAC_Exported_Functions_Group3 Callback functions
  * @brief    Callback functions.
  *
@verbatim
  ==============================================================================
                      ##### Callback functions  #####
  ==============================================================================
    [..]  This section provides Interruption and DMA callback functions:
      (+) DMA or Interrupt: the user's input data is half written (DMA only)
          or completely written.
      (+) DMA or Interrupt: the user's output buffer is half filled (DMA only)
          or completely filled.
      (+) DMA or Interrupt: error handling.

@endverbatim
  * @{
  */

/**
  * @brief  FMAC error callback.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @retval None
  */
__weak void HAL_FMAC_ErrorCallback(FMAC_HandleTypeDef *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hfmac);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_FMAC_ErrorCallback can be implemented in the user file.
   */
}

/**
  * @brief  FMAC get half data callback.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @retval None
  */
__weak void HAL_FMAC_HalfGetDataCallback(FMAC_HandleTypeDef *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hfmac);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_FMAC_HalfGetDataCallback can be implemented in the user file.
   */
}

/**
  * @brief  FMAC get data callback.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @retval None
  */
__weak void HAL_FMAC_GetDataCallback(FMAC_HandleTypeDef *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hfmac);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_FMAC_GetDataCallback can be implemented in the user file.
   */
}

/**
  * @brief  FMAC half output data ready callback.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @retval None
  */
__weak void HAL_FMAC_HalfOutputDataReadyCallback(FMAC_HandleTypeDef *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hfmac);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_FMAC_HalfOutputDataReadyCallback can be implemented in the user file.
   */
}

/**
  * @brief  FMAC output data ready callback.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @retval None
  */
__weak void HAL_FMAC_OutputDataReadyCallback(FMAC_HandleTypeDef *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hfmac);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_FMAC_OutputDataReadyCallback can be implemented in the user file.
   */
}

/**
  * @brief  FMAC filter configuration callback.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @retval None
  */
__weak void HAL_FMAC_FilterConfigCallback(FMAC_HandleTypeDef *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hfmac);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_FMAC_FilterConfigCallback can be implemented in the user file.
   */
}

/**
  * @brief  FMAC filter preload callback.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @retval None
  */
__weak void HAL_FMAC_FilterPreloadCallback(FMAC_HandleTypeDef *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hfmac);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_FMAC_FilterPreloadCallback can be implemented in the user file.
   */
}

/**
  * @}
  */

/** @defgroup FMAC_Exported_Functions_Group4 IRQ handler management
  * @brief    IRQ handler.
  *
@verbatim
  ==============================================================================
                ##### IRQ handler management #####
  ==============================================================================
[..]  This section provides IRQ handler function.

@endverbatim
  * @{
  */

/**
  * @brief  Handle FMAC interrupt request.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @retval None
  */
void HAL_FMAC_IRQHandler(FMAC_HandleTypeDef *hfmac)
{
  uint32_t itsource;

  /* Check if the read interrupt is enabled and if Y buffer empty flag isn't set */
  itsource = __HAL_FMAC_GET_IT_SOURCE(hfmac, FMAC_IT_RIEN);
  if ((__HAL_FMAC_GET_FLAG(hfmac, FMAC_FLAG_YEMPTY) == 0U) && (itsource != 0U))
  {
    /* Read some data if possible (Y size is used as a pseudo timeout in order
       to not get stuck too long under IT if FMAC keeps on processing input
       data reloaded via DMA for instance). */
    if (hfmac->pOutput != NULL)
    {
      FMAC_ReadDataIncrementPtr(hfmac, (uint16_t)FMAC_GET_Y_SIZE(hfmac));
    }

    /* Indicate that data is ready to be read */
    if ((hfmac->pOutput == NULL) || (hfmac->OutputCurrentSize == *(hfmac->pOutputSize)))
    {
      /* Reset the pointers to indicate new data will be needed */
      FMAC_ResetOutputStateAndDataPointers(hfmac);

      /* Call the output data ready callback */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
      hfmac->OutputDataReadyCallback(hfmac);
#else
      HAL_FMAC_OutputDataReadyCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
    }
  }

  /* Check if the write interrupt is enabled and if X1 buffer full flag isn't set */
  itsource = __HAL_FMAC_GET_IT_SOURCE(hfmac, FMAC_IT_WIEN);
  if ((__HAL_FMAC_GET_FLAG(hfmac, FMAC_FLAG_X1FULL) == 0U) && (itsource != 0U))
  {
    /* Write some data if possible (X1 size is used as a pseudo timeout in order
       to not get stuck too long under IT if FMAC keep on processing input
       data whereas its output emptied via DMA for instance). */
    if (hfmac->pInput != NULL)
    {
      FMAC_WriteDataIncrementPtr(hfmac, (uint16_t)FMAC_GET_X1_SIZE(hfmac));
    }

    /* Indicate that new data will be needed */
    if ((hfmac->pInput == NULL) || (hfmac->InputCurrentSize == *(hfmac->pInputSize)))
    {
      /* Reset the pointers to indicate new data will be needed */
      FMAC_ResetInputStateAndDataPointers(hfmac);

      /* Call the get data callback */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
      hfmac->GetDataCallback(hfmac);
#else
      HAL_FMAC_GetDataCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
    }
  }

  /* Check if the overflow error interrupt is enabled and if overflow error flag is raised */
  itsource = __HAL_FMAC_GET_IT_SOURCE(hfmac, FMAC_IT_OVFLIEN);
  if ((__HAL_FMAC_GET_FLAG(hfmac, FMAC_FLAG_OVFL) != 0U) && (itsource != 0U))
  {
    hfmac->ErrorCode |= HAL_FMAC_ERROR_OVFL;
  }

  /* Check if the underflow error interrupt is enabled and if underflow error flag is raised */
  itsource = __HAL_FMAC_GET_IT_SOURCE(hfmac, FMAC_IT_UNFLIEN);
  if ((__HAL_FMAC_GET_FLAG(hfmac, FMAC_FLAG_UNFL) != 0U) && (itsource != 0U))
  {
    hfmac->ErrorCode |= HAL_FMAC_ERROR_UNFL;
  }

  /* Check if the saturation error interrupt is enabled and if saturation error flag is raised */
  itsource = __HAL_FMAC_GET_IT_SOURCE(hfmac, FMAC_IT_SATIEN);
  if ((__HAL_FMAC_GET_FLAG(hfmac, FMAC_FLAG_SAT) != 0U) && (itsource != 0U))
  {
    hfmac->ErrorCode |= HAL_FMAC_ERROR_SAT;
  }

  /* Call the error callback if an error occurred */
  if (hfmac->ErrorCode != HAL_FMAC_ERROR_NONE)
  {
    /* Call the error callback */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
    hfmac->ErrorCallback(hfmac);
#else
    HAL_FMAC_ErrorCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
  }
}

/**
  * @}
  */

/** @defgroup FMAC_Exported_Functions_Group5 Peripheral State and Error functions
  * @brief    Peripheral State and Error functions.
  *
@verbatim
  ==============================================================================
                 ##### Peripheral State and Error functions #####
  ==============================================================================
    [..]  This subsection provides functions allowing to
      (+) Check the FMAC state
      (+) Get error code

@endverbatim
  * @{
  */

/**
  * @brief  Return the FMAC state.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @retval HAL_FMAC_StateTypeDef FMAC state
  */
HAL_FMAC_StateTypeDef HAL_FMAC_GetState(FMAC_HandleTypeDef *hfmac)
{
  /* Return FMAC state */
  return hfmac->State;
}

/**
  * @brief  Return the FMAC peripheral error.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @note   The returned error is a bit-map combination of possible errors.
  * @retval uint32_t Error bit-map based on @ref FMAC_Error_Code
  */
uint32_t HAL_FMAC_GetError(FMAC_HandleTypeDef *hfmac)
{
  /* Return FMAC error code */
  return hfmac->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FMAC_Private_Functions FMAC Private Functions
  * @{
  */

/**
  ==============================================================================
                       ##### FMAC Private Functions #####
  ==============================================================================
  */
/**
  * @brief  Perform a reset of the FMAC unit.
  * @param  hfmac FMAC handle.
  * @retval HAL_StatusTypeDef HAL status
  */
static HAL_StatusTypeDef FMAC_Reset(FMAC_HandleTypeDef *hfmac)
{
  uint32_t tickstart;

  /* Init tickstart for timeout management*/
  tickstart = HAL_GetTick();

  /* Perform the reset */
  SET_BIT(hfmac->Instance->CR, FMAC_CR_RESET);

  /* Wait until flag is reset */
  while (READ_BIT(hfmac->Instance->CR, FMAC_CR_RESET) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > HAL_FMAC_RESET_TIMEOUT_VALUE)
    {
      hfmac->ErrorCode |= HAL_FMAC_ERROR_TIMEOUT;
      return HAL_TIMEOUT;
    }
  }

  hfmac->ErrorCode = HAL_FMAC_ERROR_NONE;
  return HAL_OK;
}

/**
  * @brief  Reset the data pointers of the FMAC unit.
  * @param  hfmac FMAC handle.
  * @retval None
  */
static void FMAC_ResetDataPointers(FMAC_HandleTypeDef *hfmac)
{
  FMAC_ResetInputStateAndDataPointers(hfmac);
  FMAC_ResetOutputStateAndDataPointers(hfmac);
}

/**
  * @brief  Reset the input data pointers of the FMAC unit.
  * @param  hfmac FMAC handle.
  * @retval None
  */
static void FMAC_ResetInputStateAndDataPointers(FMAC_HandleTypeDef *hfmac)
{
  hfmac->pInput = NULL;
  hfmac->pInputSize = NULL;
  hfmac->InputCurrentSize = 0U;
  hfmac->WrState = HAL_FMAC_STATE_READY;
}

/**
  * @brief  Reset the output data pointers of the FMAC unit.
  * @param  hfmac FMAC handle.
  * @retval None
  */
static void FMAC_ResetOutputStateAndDataPointers(FMAC_HandleTypeDef *hfmac)
{
  hfmac->pOutput = NULL;
  hfmac->pOutputSize = NULL;
  hfmac->OutputCurrentSize = 0U;
  hfmac->RdState = HAL_FMAC_STATE_READY;
}

/**
  * @brief  Configure the FMAC filter.
  * @note   The configuration is done according to the parameters
  *         specified in the FMAC_FilterConfigTypeDef structure.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  pConfig pointer to a FMAC_FilterConfigTypeDef structure that
  *         contains the FMAC configuration information.
  * @param  PreloadAccess access mode used for the preload (polling or DMA).
  * @retval HAL_StatusTypeDef HAL status
  */
static HAL_StatusTypeDef FMAC_FilterConfig(FMAC_HandleTypeDef *hfmac, FMAC_FilterConfigTypeDef *pConfig,
                                           uint8_t PreloadAccess)
{
  uint32_t tickstart;
  uint32_t tmpcr;
#if defined(USE_FULL_ASSERT)
  uint32_t x2size;
#endif /* USE_FULL_ASSERT */

  /* Check the parameters */
  assert_param(IS_FMAC_THRESHOLD(pConfig->InputThreshold));
  assert_param(IS_FMAC_THRESHOLD(pConfig->OutputThreshold));
  assert_param(IS_FMAC_BUFFER_ACCESS(pConfig->InputAccess));
  assert_param(IS_FMAC_BUFFER_ACCESS(pConfig->OutputAccess));
  assert_param(IS_FMAC_CLIP_STATE(pConfig->Clip));
  assert_param(IS_FMAC_FILTER_FUNCTION(pConfig->Filter));
  assert_param(IS_FMAC_PARAM_P(pConfig->Filter, pConfig->P));
  assert_param(IS_FMAC_PARAM_Q(pConfig->Filter, pConfig->Q));
  assert_param(IS_FMAC_PARAM_R(pConfig->Filter, pConfig->R));

  /* Check the START bit state */
  if (FMAC_GET_START_BIT(hfmac) != 0U)
  {
    return HAL_ERROR;
  }

  /* Check handle state is ready */
  if (hfmac->State != HAL_FMAC_STATE_READY)
  {
    return HAL_BUSY;
  }

  /* Change the FMAC state */
  hfmac->State = HAL_FMAC_STATE_BUSY;

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Indicate that there is no valid configuration done */
  hfmac->FilterParam = 0U;

  /* FMAC_X1BUFCFG: Configure the input buffer within the internal memory if required */
  if (pConfig->InputBufferSize != 0U)
  {
    MODIFY_REG(hfmac->Instance->X1BUFCFG,                                                                   \
               (FMAC_X1BUFCFG_X1_BASE | FMAC_X1BUFCFG_X1_BUF_SIZE),                                         \
               (((((uint32_t)(pConfig->InputBaseAddress)) << FMAC_X1BUFCFG_X1_BASE_Pos)     & FMAC_X1BUFCFG_X1_BASE) | \
                ((((uint32_t)(pConfig->InputBufferSize))  << FMAC_X1BUFCFG_X1_BUF_SIZE_Pos) & FMAC_X1BUFCFG_X1_BUF_SIZE)));
  }

  /* FMAC_X1BUFCFG: Configure the input threshold if valid when compared to the configured X1 size */
  if (pConfig->InputThreshold != FMAC_THRESHOLD_NO_VALUE)
  {
    /* Check the parameter */
    assert_param(IS_FMAC_THRESHOLD_APPLICABLE(FMAC_GET_X1_SIZE(hfmac), pConfig->InputThreshold, pConfig->InputAccess));

    MODIFY_REG(hfmac->Instance->X1BUFCFG, \
               FMAC_X1BUFCFG_FULL_WM,     \
               ((pConfig->InputThreshold) & FMAC_X1BUFCFG_FULL_WM));
  }

  /* FMAC_X2BUFCFG: Configure the coefficient buffer within the internal memory */
  if (pConfig->CoeffBufferSize != 0U)
  {
    MODIFY_REG(hfmac->Instance->X2BUFCFG,                                                                   \
               (FMAC_X2BUFCFG_X2_BASE | FMAC_X2BUFCFG_X2_BUF_SIZE),                                         \
               (((((uint32_t)(pConfig->CoeffBaseAddress)) << FMAC_X2BUFCFG_X2_BASE_Pos)     & FMAC_X2BUFCFG_X2_BASE) | \
                ((((uint32_t)(pConfig->CoeffBufferSize))  << FMAC_X2BUFCFG_X2_BUF_SIZE_Pos) & FMAC_X2BUFCFG_X2_BUF_SIZE)));
  }

  /* FMAC_YBUFCFG: Configure the output buffer within the internal memory if required */
  if (pConfig->OutputBufferSize != 0U)
  {
    MODIFY_REG(hfmac->Instance->YBUFCFG,                                                                    \
               (FMAC_YBUFCFG_Y_BASE | FMAC_YBUFCFG_Y_BUF_SIZE),                                             \
               (((((uint32_t)(pConfig->OutputBaseAddress)) << FMAC_YBUFCFG_Y_BASE_Pos)     & FMAC_YBUFCFG_Y_BASE) |    \
                ((((uint32_t)(pConfig->OutputBufferSize))  << FMAC_YBUFCFG_Y_BUF_SIZE_Pos) & FMAC_YBUFCFG_Y_BUF_SIZE)));
  }

  /* FMAC_YBUFCFG: Configure the output threshold if valid when compared to the configured Y size */
  if (pConfig->OutputThreshold != FMAC_THRESHOLD_NO_VALUE)
  {
    /* Check the parameter */
    assert_param(IS_FMAC_THRESHOLD_APPLICABLE(FMAC_GET_Y_SIZE(hfmac), pConfig->OutputThreshold, pConfig->OutputAccess));

    MODIFY_REG(hfmac->Instance->YBUFCFG, \
               FMAC_YBUFCFG_EMPTY_WM,    \
               ((pConfig->OutputThreshold) & FMAC_YBUFCFG_EMPTY_WM));
  }

  /* FMAC_CR: Configure the clip feature */
  tmpcr = pConfig->Clip & FMAC_CR_CLIPEN;

  /* FMAC_CR: If IT or DMA will be used, enable error interrupts.
    * Being more a debugging feature, FMAC_CR_SATIEN isn't enabled by default. */
  if ((pConfig->InputAccess  == FMAC_BUFFER_ACCESS_DMA) || (pConfig->InputAccess  == FMAC_BUFFER_ACCESS_IT) ||
      (pConfig->OutputAccess == FMAC_BUFFER_ACCESS_DMA) || (pConfig->OutputAccess == FMAC_BUFFER_ACCESS_IT))
  {
    tmpcr |= FMAC_IT_UNFLIEN | FMAC_IT_OVFLIEN;
  }

  /* FMAC_CR: write the value */
  WRITE_REG(hfmac->Instance->CR, tmpcr);

  /* Save the input/output accesses in order to configure RIEN, WIEN, DMAREN and DMAWEN during filter start */
  hfmac->InputAccess = pConfig->InputAccess;
  hfmac->OutputAccess = pConfig->OutputAccess;

  /* Check whether the configured X2 is big enough for the filter */
#if defined(USE_FULL_ASSERT)
  x2size = FMAC_GET_X2_SIZE(hfmac);
#endif /* USE_FULL_ASSERT */
  assert_param(((pConfig->Filter == FMAC_FUNC_CONVO_FIR) && (x2size >= pConfig->P)) || \
               ((pConfig->Filter == FMAC_FUNC_IIR_DIRECT_FORM_1) && (x2size >= ((uint32_t)pConfig->P + (uint32_t)pConfig->Q))));

  /* Build the PARAM value that will be used when starting the filter */
  hfmac->FilterParam = (FMAC_PARAM_START | pConfig->Filter |                   \
                        ((((uint32_t)(pConfig->P)) << FMAC_PARAM_P_Pos) & FMAC_PARAM_P) | \
                        ((((uint32_t)(pConfig->Q)) << FMAC_PARAM_Q_Pos) & FMAC_PARAM_Q) | \
                        ((((uint32_t)(pConfig->R)) << FMAC_PARAM_R_Pos) & FMAC_PARAM_R));

  /* Initialize the coefficient buffer if required (pCoeffA for FIR only) */
  if ((pConfig->pCoeffB != NULL) && (pConfig->CoeffBSize != 0U))
  {
    /* FIR/IIR: The provided coefficients should match X2 size */
    assert_param(((uint32_t)pConfig->CoeffASize + (uint32_t)pConfig->CoeffBSize) <= x2size);
    /* FIR/IIR: The size of pCoeffB should match the parameter P */
    assert_param(pConfig->CoeffBSize >= pConfig->P);
    /* pCoeffA should be provided for IIR but not for FIR */
    /* IIR : if pCoeffB is provided, pCoeffA should also be there */
    /* IIR: The size of pCoeffA should match the parameter Q */
    assert_param(((pConfig->Filter == FMAC_FUNC_CONVO_FIR) &&
                  (pConfig->pCoeffA == NULL) && (pConfig->CoeffASize == 0U)) ||
                 ((pConfig->Filter == FMAC_FUNC_IIR_DIRECT_FORM_1) &&
                  (pConfig->pCoeffA != NULL) && (pConfig->CoeffASize != 0U) &&
                  (pConfig->CoeffASize >= pConfig->Q)));

    /* Write number of values to be loaded, the data load function and start the operation */
    WRITE_REG(hfmac->Instance->PARAM,                      \
              (((uint32_t)(pConfig->CoeffBSize) << FMAC_PARAM_P_Pos) | \
               ((uint32_t)(pConfig->CoeffASize) << FMAC_PARAM_Q_Pos) | \
               FMAC_FUNC_LOAD_X2 | FMAC_PARAM_START));

    if (PreloadAccess == PRELOAD_ACCESS_POLLING)
    {
      /* Load the buffer into the internal memory */
      FMAC_WritePreloadDataIncrementPtr(hfmac, &(pConfig->pCoeffB), pConfig->CoeffBSize);

      /* Load pCoeffA if needed */
      if ((pConfig->pCoeffA != NULL) && (pConfig->CoeffASize != 0U))
      {
        /* Load the buffer into the internal memory */
        FMAC_WritePreloadDataIncrementPtr(hfmac, &(pConfig->pCoeffA), pConfig->CoeffASize);
      }

      /* Wait for the end of the writing */
      if (FMAC_WaitOnStartUntilTimeout(hfmac, tickstart, HAL_FMAC_TIMEOUT_VALUE) != HAL_OK)
      {
        hfmac->ErrorCode |= HAL_FMAC_ERROR_TIMEOUT;
        hfmac->State = HAL_FMAC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }

      /* Change the FMAC state */
      hfmac->State = HAL_FMAC_STATE_READY;
    }
    else
    {
      hfmac->pInput = pConfig->pCoeffA;
      hfmac->InputCurrentSize = pConfig->CoeffASize;

      /* Set the FMAC DMA transfer complete callback */
      hfmac->hdmaPreload->XferHalfCpltCallback = NULL;
      hfmac->hdmaPreload->XferCpltCallback = FMAC_DMAFilterConfig;
      /* Set the DMA error callback */
      hfmac->hdmaPreload->XferErrorCallback = FMAC_DMAError;

      /* Enable the DMA stream managing FMAC preload data write */
      return (HAL_DMA_Start_IT(hfmac->hdmaPreload, (uint32_t)pConfig->pCoeffB, (uint32_t)&hfmac->Instance->WDATA,
                               pConfig->CoeffBSize));
    }
  }
  else
  {
    /* Change the FMAC state */
    hfmac->State = HAL_FMAC_STATE_READY;
  }

  return HAL_OK;
}

/**
  * @brief  Preload the input (FIR, IIR) and output data (IIR) of the FMAC filter.
  * @note   The set(s) of data will be used by FMAC as soon as @ref HAL_FMAC_FilterStart is called.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  pInput Preloading of the first elements of the input buffer (X1).
  *         If not needed (no data available when starting), it should be set to NULL.
  * @param  InputSize Size of the input vector.
  *         As pInput is used for preloading data, it cannot be bigger than the input memory area.
  * @param  pOutput [IIR] Preloading of the first elements of the output vector (Y).
  *         If not needed, it should be set to NULL.
  * @param  OutputSize Size of the output vector.
  *         As pOutput is used for preloading data, it cannot be bigger than the output memory area.
  * @param  PreloadAccess access mode used for the preload (polling or DMA).
  * @note   The input and the output buffers can be filled by calling several times @ref HAL_FMAC_FilterPreload
  *         (each call filling partly the buffers). In case of overflow (too much data provided through
  *         all these calls), an error will be returned.
  * @retval HAL_StatusTypeDef HAL status
  */
static HAL_StatusTypeDef FMAC_FilterPreload(FMAC_HandleTypeDef *hfmac, int16_t *pInput, uint8_t InputSize,
                                            int16_t *pOutput, uint8_t OutputSize, uint8_t PreloadAccess)
{
  uint32_t tickstart;
  HAL_StatusTypeDef status;

  /* Check the START bit state */
  if (FMAC_GET_START_BIT(hfmac) != 0U)
  {
    return HAL_ERROR;
  }

  /* Check that a valid configuration was done previously */
  if (hfmac->FilterParam == 0U)
  {
    return HAL_ERROR;
  }

  /* Check the preload input buffers isn't too big */
  if ((InputSize > FMAC_GET_X1_SIZE(hfmac)) && (pInput != NULL))
  {
    return HAL_ERROR;
  }

  /* Check the preload output buffer isn't too big */
  if ((OutputSize > FMAC_GET_Y_SIZE(hfmac)) && (pOutput != NULL))
  {
    return HAL_ERROR;
  }

  /* Check handle state is ready */
  if (hfmac->State != HAL_FMAC_STATE_READY)
  {
    return HAL_BUSY;
  }

  /* Change the FMAC state */
  hfmac->State = HAL_FMAC_STATE_BUSY;

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Preload the input buffer if required */
  if ((pInput != NULL) && (InputSize != 0U))
  {
    /* Write number of values to be loaded, the data load function and start the operation */
    WRITE_REG(hfmac->Instance->PARAM, \
              (((uint32_t)InputSize << FMAC_PARAM_P_Pos) | FMAC_FUNC_LOAD_X1 | FMAC_PARAM_START));

    if (PreloadAccess == PRELOAD_ACCESS_POLLING)
    {
      /* Load the buffer into the internal memory */
      FMAC_WritePreloadDataIncrementPtr(hfmac, &pInput, InputSize);

      /* Wait for the end of the writing */
      if (FMAC_WaitOnStartUntilTimeout(hfmac, tickstart, HAL_FMAC_TIMEOUT_VALUE) != HAL_OK)
      {
        hfmac->ErrorCode |= HAL_FMAC_ERROR_TIMEOUT;
        hfmac->State = HAL_FMAC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }
    else
    {
      hfmac->pInput = pOutput;
      hfmac->InputCurrentSize = OutputSize;

      /* Set the FMAC DMA transfer complete callback */
      hfmac->hdmaPreload->XferHalfCpltCallback = NULL;
      hfmac->hdmaPreload->XferCpltCallback = FMAC_DMAFilterPreload;
      /* Set the DMA error callback */
      hfmac->hdmaPreload->XferErrorCallback = FMAC_DMAError;

      /* Enable the DMA stream managing FMAC preload data write */
      return (HAL_DMA_Start_IT(hfmac->hdmaPreload, (uint32_t)pInput, (uint32_t)&hfmac->Instance->WDATA, InputSize));
    }
  }

  /* Preload the output buffer if required */
  if ((pOutput != NULL) && (OutputSize != 0U))
  {
    /* Write number of values to be loaded, the data load function and start the operation */
    WRITE_REG(hfmac->Instance->PARAM, \
              (((uint32_t)OutputSize << FMAC_PARAM_P_Pos) | FMAC_FUNC_LOAD_Y | FMAC_PARAM_START));

    if (PreloadAccess == PRELOAD_ACCESS_POLLING)
    {
      /* Load the buffer into the internal memory */
      FMAC_WritePreloadDataIncrementPtr(hfmac, &pOutput, OutputSize);

      /* Wait for the end of the writing */
      if (FMAC_WaitOnStartUntilTimeout(hfmac, tickstart, HAL_FMAC_TIMEOUT_VALUE) != HAL_OK)
      {
        hfmac->ErrorCode |= HAL_FMAC_ERROR_TIMEOUT;
        hfmac->State = HAL_FMAC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }
    else
    {
      hfmac->pInput = NULL;
      hfmac->InputCurrentSize = 0U;

      /* Set the FMAC DMA transfer complete callback */
      hfmac->hdmaPreload->XferHalfCpltCallback = NULL;
      hfmac->hdmaPreload->XferCpltCallback = FMAC_DMAFilterPreload;
      /* Set the DMA error callback */
      hfmac->hdmaPreload->XferErrorCallback = FMAC_DMAError;

      /* Enable the DMA stream managing FMAC preload data write */
      return (HAL_DMA_Start_IT(hfmac->hdmaPreload, (uint32_t)pOutput, (uint32_t)&hfmac->Instance->WDATA, OutputSize));
    }
  }

  /* Update the error codes */
  if (__HAL_FMAC_GET_FLAG(hfmac, FMAC_FLAG_OVFL))
  {
    hfmac->ErrorCode |= HAL_FMAC_ERROR_OVFL;
  }
  if (__HAL_FMAC_GET_FLAG(hfmac, FMAC_FLAG_UNFL))
  {
    hfmac->ErrorCode |= HAL_FMAC_ERROR_UNFL;
  }
  if (__HAL_FMAC_GET_FLAG(hfmac, FMAC_FLAG_SAT))
  {
    hfmac->ErrorCode |= HAL_FMAC_ERROR_SAT;
  }

  /* Change the FMAC state */
  hfmac->State = HAL_FMAC_STATE_READY;

  /* Return function status */
  if (hfmac->ErrorCode == HAL_FMAC_ERROR_NONE)
  {
    status = HAL_OK;
  }
  else
  {
    status = HAL_ERROR;
  }
  return status;
}

/**
  * @brief  Write data into FMAC internal memory through WDATA and increment input buffer pointer.
  * @note   This function is only used with preload functions.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  ppData pointer to pointer to the data buffer.
  * @param  Size size of the data buffer.
  * @retval None
  */
static void FMAC_WritePreloadDataIncrementPtr(FMAC_HandleTypeDef *hfmac, int16_t **ppData, uint8_t Size)
{
  uint8_t index;

  /* Load the buffer into the internal memory */
  for (index = Size; index > 0U; index--)
  {
    WRITE_REG(hfmac->Instance->WDATA, (((uint32_t)(*(*ppData))) & FMAC_WDATA_WDATA));
    (*ppData)++;
  }
}

/**
  * @brief  Handle FMAC Function Timeout.
  * @param  hfmac FMAC handle.
  * @param  Tickstart Tick start value.
  * @param  Timeout Timeout duration.
  * @retval HAL_StatusTypeDef HAL status
  */
static HAL_StatusTypeDef FMAC_WaitOnStartUntilTimeout(FMAC_HandleTypeDef *hfmac, uint32_t Tickstart, uint32_t Timeout)
{
  /* Wait until flag changes */
  while (READ_BIT(hfmac->Instance->PARAM, FMAC_PARAM_START) != 0U)
  {
    if ((HAL_GetTick() - Tickstart) > Timeout)
    {
      hfmac->ErrorCode |= HAL_FMAC_ERROR_TIMEOUT;

      return HAL_TIMEOUT;
    }
  }
  return HAL_OK;
}

/**
  * @brief  Register the new input buffer, update DMA configuration if needed and change the FMAC state.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  pInput New input vector (additional input data).
  * @param  pInputSize Size of the input vector (if all the data can't be
  *         written, it will be updated with the number of data read from FMAC).
  * @retval HAL_StatusTypeDef HAL status
  */
static HAL_StatusTypeDef FMAC_AppendFilterDataUpdateState(FMAC_HandleTypeDef *hfmac, int16_t *pInput,
                                                          uint16_t *pInputSize)
{
  /* Change the FMAC state */
  hfmac->WrState = HAL_FMAC_STATE_BUSY_WR;

  /* Reset the current size */
  hfmac->InputCurrentSize = 0U;

  /* Handle the pointer depending on the input access */
  if (hfmac->InputAccess == FMAC_BUFFER_ACCESS_DMA)
  {
    hfmac->pInput = NULL;
    hfmac->pInputSize = NULL;

    /* Set the FMAC DMA transfer complete callback */
    hfmac->hdmaIn->XferHalfCpltCallback = FMAC_DMAHalfGetData;
    hfmac->hdmaIn->XferCpltCallback = FMAC_DMAGetData;
    /* Set the DMA error callback */
    hfmac->hdmaIn->XferErrorCallback = FMAC_DMAError;

    /* Enable the DMA stream managing FMAC input data write */
    return (HAL_DMA_Start_IT(hfmac->hdmaIn, (uint32_t)pInput, (uint32_t)&hfmac->Instance->WDATA, *pInputSize));
  }
  else
  {
    /* Update the input data information (polling, IT) */
    hfmac->pInput = pInput;
    hfmac->pInputSize = pInputSize;
  }

  return HAL_OK;
}

/**
  * @brief  Register the new output buffer, update DMA configuration if needed and change the FMAC state.
  * @param  hfmac pointer to a FMAC_HandleTypeDef structure that contains
  *         the configuration information for FMAC module.
  * @param  pOutput New output vector.
  * @param  pOutputSize Size of the output vector (if the vector can't
  *         be entirely filled, pOutputSize will be updated with the number
  *         of data read from FMAC).
  * @retval HAL_StatusTypeDef HAL status
  */
static HAL_StatusTypeDef FMAC_ConfigFilterOutputBufferUpdateState(FMAC_HandleTypeDef *hfmac, int16_t *pOutput,
                                                                  uint16_t *pOutputSize)
{
  /* Reset the current size */
  hfmac->OutputCurrentSize = 0U;

  /* Check whether a valid pointer was provided */
  if ((pOutput == NULL) || (pOutputSize == NULL) || (*pOutputSize == 0U))
  {
    /* The user will have to provide a valid configuration later */
    hfmac->pOutput = NULL;
    hfmac->pOutputSize = NULL;
    hfmac->RdState = HAL_FMAC_STATE_READY;
  }
  /* Handle the pointer depending on the input access */
  else if (hfmac->OutputAccess == FMAC_BUFFER_ACCESS_DMA)
  {
    hfmac->pOutput = NULL;
    hfmac->pOutputSize = NULL;
    hfmac->RdState = HAL_FMAC_STATE_BUSY_RD;

    /* Set the FMAC DMA transfer complete callback */
    hfmac->hdmaOut->XferHalfCpltCallback = FMAC_DMAHalfOutputDataReady;
    hfmac->hdmaOut->XferCpltCallback = FMAC_DMAOutputDataReady;
    /* Set the DMA error callback */
    hfmac->hdmaOut->XferErrorCallback = FMAC_DMAError;

    /* Enable the DMA stream managing FMAC output data read */
    return (HAL_DMA_Start_IT(hfmac->hdmaOut, (uint32_t)&hfmac->Instance->RDATA, (uint32_t)pOutput, *pOutputSize));
  }
  else if (hfmac->OutputAccess == FMAC_BUFFER_ACCESS_NONE)
  {
    hfmac->pOutput = NULL;
    hfmac->pOutputSize = NULL;
    hfmac->RdState = HAL_FMAC_STATE_READY;
  }
  else
  {
    /* Update the output data information (polling, IT) */
    hfmac->pOutput = pOutput;
    hfmac->pOutputSize = pOutputSize;
    hfmac->RdState = HAL_FMAC_STATE_BUSY_RD;
  }

  return HAL_OK;
}

/**
  * @brief  Read available output data until Y EMPTY is set.
  * @param  hfmac FMAC handle.
  * @param  MaxSizeToRead Maximum number of data to read (this serves as a timeout
  *         if FMAC continuously writes into the output buffer).
  * @retval None
  */
static void FMAC_ReadDataIncrementPtr(FMAC_HandleTypeDef *hfmac, uint16_t MaxSizeToRead)
{
  uint16_t maxsize;
  uint16_t threshold;
  uint32_t tmpvalue;

  /* Check if there is data to read */
  if (READ_BIT(hfmac->Instance->SR, FMAC_SR_YEMPTY) != 0U)
  {
    return;
  }

  /* Get the maximum index (no wait allowed, no overstepping of the output buffer) */
  if ((hfmac->OutputCurrentSize + MaxSizeToRead) > *(hfmac->pOutputSize))
  {
    maxsize = *(hfmac->pOutputSize);
  }
  else
  {
    maxsize = hfmac->OutputCurrentSize + MaxSizeToRead;
  }

  /* Read until there is no more room or no more data */
  do
  {
    /* If there is no more room, return */
    if (!(hfmac->OutputCurrentSize < maxsize))
    {
      return;
    }

    /* Read the available data */
    tmpvalue = ((READ_REG(hfmac->Instance->RDATA))& FMAC_RDATA_RDATA);
    *(hfmac->pOutput) = (int16_t)tmpvalue;
    hfmac->pOutput++;
    hfmac->OutputCurrentSize++;
  } while (READ_BIT(hfmac->Instance->SR, FMAC_SR_YEMPTY) == 0U);

  /* Y buffer empty flag has just be raised, read the threshold */
  threshold = (uint16_t)FMAC_GET_THRESHOLD_FROM_WM(FMAC_GET_Y_EMPTY_WM(hfmac)) - 1U;

  /* Update the maximum size if needed (limited data available) */
  if ((hfmac->OutputCurrentSize + threshold) < maxsize)
  {
    maxsize = hfmac->OutputCurrentSize + threshold;
  }

  /* Read the available data */
  while (hfmac->OutputCurrentSize < maxsize)
  {
    tmpvalue = ((READ_REG(hfmac->Instance->RDATA))& FMAC_RDATA_RDATA);
    *(hfmac->pOutput) = (int16_t)tmpvalue;
    hfmac->pOutput++;
    hfmac->OutputCurrentSize++;
  }
}

/**
  * @brief  Write available input data until X1 FULL is set.
  * @param  hfmac FMAC handle.
  * @param  MaxSizeToWrite Maximum number of data to write (this serves as a timeout
  *         if FMAC continuously empties the input buffer).
  * @retval None
  */
static void FMAC_WriteDataIncrementPtr(FMAC_HandleTypeDef *hfmac, uint16_t MaxSizeToWrite)
{
  uint16_t maxsize;
  uint16_t threshold;

  /* Check if there is room in FMAC */
  if (READ_BIT(hfmac->Instance->SR, FMAC_SR_X1FULL) != 0U)
  {
    return;
  }

  /* Get the maximum index (no wait allowed, no overstepping of the output buffer) */
  if ((hfmac->InputCurrentSize + MaxSizeToWrite) > *(hfmac->pInputSize))
  {
    maxsize = *(hfmac->pInputSize);
  }
  else
  {
    maxsize = hfmac->InputCurrentSize + MaxSizeToWrite;
  }

  /* Write until there is no more room or no more data */
  do
  {
    /* If there is no more room, return */
    if (!(hfmac->InputCurrentSize < maxsize))
    {
      return;
    }

    /* Write the available data */
    WRITE_REG(hfmac->Instance->WDATA, (((uint32_t)(*(hfmac->pInput))) & FMAC_WDATA_WDATA));
    hfmac->pInput++;
    hfmac->InputCurrentSize++;
  } while (READ_BIT(hfmac->Instance->SR, FMAC_SR_X1FULL) == 0U);

  /* X1 buffer full flag has just be raised, read the threshold */
  threshold = (uint16_t)FMAC_GET_THRESHOLD_FROM_WM(FMAC_GET_X1_FULL_WM(hfmac)) - 1U;

  /* Update the maximum size if needed (limited data available) */
  if ((hfmac->InputCurrentSize + threshold) < maxsize)
  {
    maxsize = hfmac->InputCurrentSize + threshold;
  }

  /* Write the available data */
  while (hfmac->InputCurrentSize < maxsize)
  {
    WRITE_REG(hfmac->Instance->WDATA, (((uint32_t)(*(hfmac->pInput))) & FMAC_WDATA_WDATA));
    hfmac->pInput++;
    hfmac->InputCurrentSize++;
  }
}

/**
  * @brief  DMA FMAC Input Data process half complete callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void FMAC_DMAHalfGetData(DMA_HandleTypeDef *hdma)
{
  FMAC_HandleTypeDef *hfmac = (FMAC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Call half get data callback */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hfmac->HalfGetDataCallback(hfmac);
#else
  HAL_FMAC_HalfGetDataCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA FMAC Input Data process complete callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void FMAC_DMAGetData(DMA_HandleTypeDef *hdma)
{
  FMAC_HandleTypeDef *hfmac = (FMAC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Reset the pointers to indicate new data will be needed */
  FMAC_ResetInputStateAndDataPointers(hfmac);

  /* Call get data callback */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hfmac->GetDataCallback(hfmac);
#else
  HAL_FMAC_GetDataCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA FMAC Output Data process half complete callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void FMAC_DMAHalfOutputDataReady(DMA_HandleTypeDef *hdma)
{
  FMAC_HandleTypeDef *hfmac = (FMAC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Call half output data ready callback */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hfmac->HalfOutputDataReadyCallback(hfmac);
#else
  HAL_FMAC_HalfOutputDataReadyCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA FMAC Output Data process complete callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void FMAC_DMAOutputDataReady(DMA_HandleTypeDef *hdma)
{
  FMAC_HandleTypeDef *hfmac = (FMAC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Reset the pointers to indicate new data will be needed */
  FMAC_ResetOutputStateAndDataPointers(hfmac);

  /* Call output data ready callback */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hfmac->OutputDataReadyCallback(hfmac);
#else
  HAL_FMAC_OutputDataReadyCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA FMAC Filter Configuration process complete callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void FMAC_DMAFilterConfig(DMA_HandleTypeDef *hdma)
{
  uint8_t index;

  FMAC_HandleTypeDef *hfmac = (FMAC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* If needed, write CoeffA and exit */
  if (hfmac->pInput != NULL)
  {
    /* Set the FMAC DMA transfer complete callback */
    hfmac->hdmaPreload->XferHalfCpltCallback = NULL;
    hfmac->hdmaPreload->XferCpltCallback = FMAC_DMAFilterConfig;
    /* Set the DMA error callback */
    hfmac->hdmaPreload->XferErrorCallback = FMAC_DMAError;

    /* Enable the DMA stream managing FMAC preload data write */
    if (HAL_DMA_Start_IT(hfmac->hdmaPreload, (uint32_t)hfmac->pInput, (uint32_t)&hfmac->Instance->WDATA,
                         hfmac->InputCurrentSize) == HAL_OK)
    {
      hfmac->pInput = NULL;
      hfmac->InputCurrentSize = 0U;
      return;
    }

    /* If not exited, there was an error: set FMAC handle state to error */
    hfmac->State = HAL_FMAC_STATE_ERROR;
  }
  else
  {
    /* Wait for the end of the writing */
    for (index = 0U; index < MAX_PRELOAD_INDEX; index++)
    {
      if (READ_BIT(hfmac->Instance->PARAM, FMAC_PARAM_START) == 0U)
      {
        break;
      }
    }

    /* If 'START' is still set, there was a timeout: set FMAC handle state to timeout */
    if (READ_BIT(hfmac->Instance->PARAM, FMAC_PARAM_START) != 0U)
    {
      hfmac->State = HAL_FMAC_STATE_TIMEOUT;
    }
    else
    {
      /* Change the FMAC state */
      hfmac->State = HAL_FMAC_STATE_READY;

      /* Call output data ready callback */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
      hfmac->FilterConfigCallback(hfmac);
#else
      HAL_FMAC_FilterConfigCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
      return;
    }
  }

  /* If not exited, there was an error: set FMAC handle error code to DMA error */
  hfmac->ErrorCode |= HAL_FMAC_ERROR_DMA;

  /* Call user callback */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hfmac->ErrorCallback(hfmac);
#else
  HAL_FMAC_ErrorCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */

}

/**
  * @brief  DMA FMAC Filter Configuration process complete callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void FMAC_DMAFilterPreload(DMA_HandleTypeDef *hdma)
{
  uint8_t index;

  FMAC_HandleTypeDef *hfmac = (FMAC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Wait for the end of the X1 writing */
  for (index = 0U; index < MAX_PRELOAD_INDEX; index++)
  {
    if (READ_BIT(hfmac->Instance->PARAM, FMAC_PARAM_START) == 0U)
    {
      break;
    }
  }

  /* If 'START' is still set, there was an error: set FMAC handle state to error */
  if (READ_BIT(hfmac->Instance->PARAM, FMAC_PARAM_START) != 0U)
  {
    hfmac->State = HAL_FMAC_STATE_TIMEOUT;
    hfmac->ErrorCode |= HAL_FMAC_ERROR_TIMEOUT;
  }
  /* If needed, preload Y buffer */
  else if ((hfmac->pInput != NULL) && (hfmac->InputCurrentSize != 0U))
  {
    /* Write number of values to be loaded, the data load function and start the operation */
    WRITE_REG(hfmac->Instance->PARAM, \
              (((uint32_t)(hfmac->InputCurrentSize) << FMAC_PARAM_P_Pos) | FMAC_FUNC_LOAD_Y | FMAC_PARAM_START));

    /* Set the FMAC DMA transfer complete callback */
    hfmac->hdmaPreload->XferHalfCpltCallback = NULL;
    hfmac->hdmaPreload->XferCpltCallback = FMAC_DMAFilterPreload;
    /* Set the DMA error callback */
    hfmac->hdmaPreload->XferErrorCallback = FMAC_DMAError;

    /* Enable the DMA stream managing FMAC preload data write */
    if (HAL_DMA_Start_IT(hfmac->hdmaPreload, (uint32_t)hfmac->pInput, (uint32_t)&hfmac->Instance->WDATA,
                         hfmac->InputCurrentSize) == HAL_OK)
    {
      hfmac->pInput = NULL;
      hfmac->InputCurrentSize = 0U;
      return;
    }

    /* If not exited, there was an error */
    hfmac->ErrorCode = HAL_FMAC_ERROR_DMA;
    hfmac->State = HAL_FMAC_STATE_ERROR;
  }
  else
  {
    /* nothing to do */
  }

  if (hfmac->ErrorCode == HAL_FMAC_ERROR_NONE)
  {
    /* Change the FMAC state */
    hfmac->State = HAL_FMAC_STATE_READY;

    /* Call output data ready callback */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
    hfmac->FilterPreloadCallback(hfmac);
#else
    HAL_FMAC_FilterPreloadCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
  }
  else
  {
    /* Call user callback */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
    hfmac->ErrorCallback(hfmac);
#else
    HAL_FMAC_ErrorCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
  }
}


/**
  * @brief  DMA FMAC communication error callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void FMAC_DMAError(DMA_HandleTypeDef *hdma)
{
  FMAC_HandleTypeDef *hfmac = (FMAC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Set FMAC handle state to error */
  hfmac->State = HAL_FMAC_STATE_ERROR;

  /* Set FMAC handle error code to DMA error */
  hfmac->ErrorCode |= HAL_FMAC_ERROR_DMA;

  /* Call user callback */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hfmac->ErrorCallback(hfmac);
#else
  HAL_FMAC_ErrorCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
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

#endif /* HAL_FMAC_MODULE_ENABLED */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
