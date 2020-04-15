/**
  ******************************************************************************
  * @file    stm32f1xx_hal_cec.c
  * @author  MCD Application Team
  * @brief   CEC HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the High Definition Multimedia Interface 
  *          Consumer Electronics Control Peripheral (CEC).
  *           + Initialization and de-initialization function
  *           + IO operation function
  *           + Peripheral Control function
  *
  *           
  @verbatim       
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
    [..]
    The CEC HAL driver can be used as follow:
    
    (#) Declare a CEC_HandleTypeDef handle structure.
    (#) Initialize the CEC low level resources by implementing the HAL_CEC_MspInit ()API:
        (##) Enable the CEC interface clock.
        (##) CEC pins configuration:
            (+++) Enable the clock for the CEC GPIOs.
            (+++) Configure these CEC pins as alternate function pull-up.
        (##) NVIC configuration if you need to use interrupt process (HAL_CEC_Transmit_IT()
             and HAL_CEC_Receive_IT() APIs):
            (+++) Configure the CEC interrupt priority.
            (+++) Enable the NVIC CEC IRQ handle.
            (+++) The specific CEC interrupts (Transmission complete interrupt, 
                  RXNE interrupt and Error Interrupts) will be managed using the macros
                  __HAL_CEC_ENABLE_IT() and __HAL_CEC_DISABLE_IT() inside the transmit 
                  and receive process.

    (#) Program the Bit Timing Error Mode and the Bit Period Error Mode in the hcec Init structure.

    (#) Initialize the CEC registers by calling the HAL_CEC_Init() API.

  [..]        
    (@) This API (HAL_CEC_Init()) configures also the low level Hardware (GPIO, CLOCK, CORTEX...etc)
        by calling the customed HAL_CEC_MspInit() API.
  *** Callback registration ***
  =============================================
  The compilation define  USE_HAL_CEC_REGISTER_CALLBACKS when set to 1
  allows the user to configure dynamically the driver callbacks.
  Use Functions @ref HAL_CEC_RegisterCallback() or HAL_CEC_RegisterXXXCallback()
  to register an interrupt callback.

  Function @ref HAL_CEC_RegisterCallback() allows to register following callbacks:
    (+) TxCpltCallback     : Tx Transfer completed callback.
    (+) ErrorCallback      : callback for error detection.
    (+) MspInitCallback    : CEC MspInit.
    (+) MspDeInitCallback  : CEC MspDeInit.
  This function takes as parameters the HAL peripheral handle, the Callback ID
  and a pointer to the user callback function.

  For specific callback HAL_CEC_RxCpltCallback use dedicated register callbacks 
  @ref HAL_CEC_RegisterRxCpltCallback().

  Use function @ref HAL_CEC_UnRegisterCallback() to reset a callback to the default
  weak function.
  @ref HAL_CEC_UnRegisterCallback() takes as parameters the HAL peripheral handle,
  and the Callback ID.
  This function allows to reset following callbacks:
    (+) TxCpltCallback     : Tx Transfer completed callback.
    (+) ErrorCallback      : callback for error detection.
    (+) MspInitCallback    : CEC MspInit.
    (+) MspDeInitCallback  : CEC MspDeInit.

  For callback HAL_CEC_RxCpltCallback use dedicated unregister callback : 
  @ref HAL_CEC_UnRegisterRxCpltCallback().

  By default, after the @ref HAL_CEC_Init() and when the state is HAL_CEC_STATE_RESET
  all callbacks are set to the corresponding weak functions :
  examples @ref HAL_CEC_TxCpltCallback() , @ref HAL_CEC_RxCpltCallback().
  Exception done for MspInit and MspDeInit functions that are
  reset to the legacy weak function in the @ref HAL_CEC_Init()/ @ref HAL_CEC_DeInit() only when
  these callbacks are null (not registered beforehand).
  if not, MspInit or MspDeInit are not null, the @ref HAL_CEC_Init() / @ref HAL_CEC_DeInit()
  keep and use the user MspInit/MspDeInit functions (registered beforehand)

  Callbacks can be registered/unregistered in HAL_CEC_STATE_READY state only.
  Exception done MspInit/MspDeInit callbacks that can be registered/unregistered
  in HAL_CEC_STATE_READY or HAL_CEC_STATE_RESET state,
  thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
  In that case first register the MspInit/MspDeInit user callbacks
  using @ref HAL_CEC_RegisterCallback() before calling @ref HAL_CEC_DeInit()
  or @ref HAL_CEC_Init() function.

  When the compilation define USE_HAL_CEC_REGISTER_CALLBACKS is set to 0 or
  not defined, the callback registration feature is not available and all callbacks
  are set to the corresponding weak functions.
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
#include "stm32f1xx_hal.h"

#ifdef HAL_CEC_MODULE_ENABLED

#if defined (CEC)

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @defgroup CEC CEC
  * @brief HAL CEC module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup CEC_Private_Constants CEC Private Constants
  * @{
  */
#define CEC_CFGR_FIELDS (CEC_CFGR_BTEM | CEC_CFGR_BPEM )
#define CEC_FLAG_TRANSMIT_MASK (CEC_FLAG_TSOM|CEC_FLAG_TEOM|CEC_FLAG_TBTRF)
#define CEC_FLAG_RECEIVE_MASK (CEC_FLAG_RSOM|CEC_FLAG_REOM|CEC_FLAG_RBTF)
#define CEC_ESR_ALL_ERROR (CEC_ESR_BTE|CEC_ESR_BPE|CEC_ESR_RBTFE|CEC_ESR_SBE|CEC_ESR_ACKE|CEC_ESR_LINE|CEC_ESR_TBTFE)
#define CEC_RXXFERSIZE_INITIALIZE 0xFFFF /*!< Value used to initialise the RxXferSize of the handle */
/**
  * @}
  */
 
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup CEC_Private_Functions CEC Private Functions
  * @{
  */
static HAL_StatusTypeDef CEC_Transmit_IT(CEC_HandleTypeDef *hcec);
static HAL_StatusTypeDef CEC_Receive_IT(CEC_HandleTypeDef *hcec);
/**
  * @}
  */
  
/* Exported functions ---------------------------------------------------------*/

/** @defgroup CEC_Exported_Functions CEC Exported Functions
  * @{
  */

/** @defgroup CEC_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions 
  *
@verbatim                                                
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to initialize the CEC
      (+) The following parameters need to be configured: 
        (++) TimingErrorFree
        (++) PeriodErrorFree 
        (++) InitiatorAddress

@endverbatim
  * @{
  */

/**
  * @brief Initializes the CEC mode according to the specified
  *         parameters in the CEC_InitTypeDef and creates the associated handle .
  * @param hcec: CEC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_Init(CEC_HandleTypeDef *hcec)
{
  /* Check the CEC handle allocation */
  if((hcec == NULL) ||(hcec->Init.RxBuffer == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the parameters */ 
  assert_param(IS_CEC_ALL_INSTANCE(hcec->Instance));
  assert_param(IS_CEC_BIT_TIMING_ERROR_MODE(hcec->Init.TimingErrorFree));
  assert_param(IS_CEC_BIT_PERIOD_ERROR_MODE(hcec->Init.PeriodErrorFree));
  assert_param(IS_CEC_ADDRESS(hcec->Init.OwnAddress));
#if (USE_HAL_CEC_REGISTER_CALLBACKS == 1)
  if(hcec->gState == HAL_CEC_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hcec->Lock = HAL_UNLOCKED;

    hcec->TxCpltCallback  = HAL_CEC_TxCpltCallback;  /* Legacy weak TxCpltCallback  */
    hcec->RxCpltCallback = HAL_CEC_RxCpltCallback;   /* Legacy weak RxCpltCallback */
    hcec->ErrorCallback = HAL_CEC_ErrorCallback;     /* Legacy weak ErrorCallback */

    if(hcec->MspInitCallback == NULL)
    {
      hcec->MspInitCallback = HAL_CEC_MspInit; /* Legacy weak MspInit  */
    }

    /* Init the low level hardware */
    hcec->MspInitCallback(hcec);
  }
#else
  if(hcec->gState == HAL_CEC_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hcec->Lock = HAL_UNLOCKED;
    /* Init the low level hardware : GPIO, CLOCK */
    HAL_CEC_MspInit(hcec);
  }
#endif /* USE_HAL_CEC_REGISTER_CALLBACKS */

  hcec->gState = HAL_CEC_STATE_BUSY;
  
  /* Disable the Peripheral */
  __HAL_CEC_DISABLE(hcec);
  
  /* Write to CEC Control Register */
  MODIFY_REG(hcec->Instance->CFGR, CEC_CFGR_FIELDS, hcec->Init.TimingErrorFree | hcec->Init.PeriodErrorFree);
  
  /* Write to CEC Own Address Register */
  MODIFY_REG(hcec->Instance->OAR, CEC_OAR_OA, hcec->Init.OwnAddress);
  
  /* Configure the prescaler to generate the required 50 microseconds time base.*/
  MODIFY_REG(hcec->Instance->PRES, CEC_PRES_PRES, 50U * (HAL_RCC_GetPCLK1Freq()/1000000U) - 1U);
  
  /* Enable the following CEC Interrupt */
  __HAL_CEC_ENABLE_IT(hcec, CEC_IT_IE);

  /* Enable the CEC Peripheral */
  __HAL_CEC_ENABLE(hcec);
  
  hcec->ErrorCode = HAL_CEC_ERROR_NONE;
  hcec->gState = HAL_CEC_STATE_READY;
  hcec->RxState = HAL_CEC_STATE_READY;
  
  return HAL_OK;
}

/**
  * @brief DeInitializes the CEC peripheral 
  * @param hcec: CEC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_DeInit(CEC_HandleTypeDef *hcec)
{
  /* Check the CEC handle allocation */
  if(hcec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_CEC_ALL_INSTANCE(hcec->Instance));

  hcec->gState = HAL_CEC_STATE_BUSY;

#if (USE_HAL_CEC_REGISTER_CALLBACKS == 1)
  if(hcec->MspDeInitCallback == NULL)
  {
    hcec->MspDeInitCallback = HAL_CEC_MspDeInit; /* Legacy weak MspDeInit  */
  }

  /* DeInit the low level hardware */
  hcec->MspDeInitCallback(hcec);

#else
  /* DeInit the low level hardware */
  HAL_CEC_MspDeInit(hcec);
#endif /* USE_HAL_CEC_REGISTER_CALLBACKS */

  __HAL_RCC_CEC_FORCE_RESET();
  __HAL_RCC_CEC_RELEASE_RESET();
  
  hcec->ErrorCode = HAL_CEC_ERROR_NONE;
  hcec->gState = HAL_CEC_STATE_RESET;
  hcec->RxState = HAL_CEC_STATE_RESET;
  
  /* Process Unlock */
  __HAL_UNLOCK(hcec);
  
  return HAL_OK;
}

/**
  * @brief Initializes the Own Address of the CEC device
  * @param hcec: CEC handle
  * @param  CEC_OwnAddress: The CEC own address.  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_SetDeviceAddress(CEC_HandleTypeDef *hcec, uint16_t CEC_OwnAddress)
{
  /* Check the parameters */
  assert_param(IS_CEC_OWN_ADDRESS(CEC_OwnAddress));

  if ((hcec->gState == HAL_CEC_STATE_READY) && (hcec->RxState == HAL_CEC_STATE_READY))
  { 
    /* Process Locked */
    __HAL_LOCK(hcec); 
    
    hcec->gState = HAL_CEC_STATE_BUSY;
  
    /* Disable the Peripheral */
    __HAL_CEC_DISABLE(hcec);
    
    if(CEC_OwnAddress != CEC_OWN_ADDRESS_NONE)
    {
       MODIFY_REG(hcec->Instance->OAR, CEC_OAR_OA, hcec->Init.OwnAddress);
    }
    else
    {
       CLEAR_BIT(hcec->Instance->OAR, CEC_OAR_OA);  
    }
        
    hcec->gState = HAL_CEC_STATE_READY;
    hcec->ErrorCode = HAL_CEC_ERROR_NONE;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcec); 
    
    /* Enable the Peripheral */
    __HAL_CEC_ENABLE(hcec);
    
    return  HAL_OK; 
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief CEC MSP Init
  * @param hcec: CEC handle
  * @retval None
  */
 __weak void HAL_CEC_MspInit(CEC_HandleTypeDef *hcec)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcec);
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_CEC_MspInit can be implemented in the user file
   */ 
}

/**
  * @brief CEC MSP DeInit
  * @param hcec: CEC handle
  * @retval None
  */
 __weak void HAL_CEC_MspDeInit(CEC_HandleTypeDef *hcec)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcec);
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_CEC_MspDeInit can be implemented in the user file
   */ 
}

#if (USE_HAL_CEC_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User CEC Callback
  *         To be used instead of the weak predefined callback
  * @param  hcec CEC handle
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_CEC_TX_CPLT_CB_ID Tx Complete callback ID
  *          @arg @ref HAL_CEC_ERROR_CB_ID Error callback ID
  *          @arg @ref HAL_CEC_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_CEC_MSPDEINIT_CB_ID MspDeInit callback ID
  * @param  pCallback pointer to the Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_RegisterCallback(CEC_HandleTypeDef *hcec, HAL_CEC_CallbackIDTypeDef CallbackID, pCEC_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if(pCallback == NULL)
  {
    /* Update the error code */
    hcec->ErrorCode |= HAL_CEC_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }
    /* Process locked */
  __HAL_LOCK(hcec);

  if(hcec->gState == HAL_CEC_STATE_READY)
  {
    switch (CallbackID)
    {
    case HAL_CEC_TX_CPLT_CB_ID :
      hcec->TxCpltCallback = pCallback;
      break;

    case HAL_CEC_ERROR_CB_ID :
      hcec->ErrorCallback = pCallback;
      break;

    case HAL_CEC_MSPINIT_CB_ID :
      hcec->MspInitCallback = pCallback;
      break;

   case HAL_CEC_MSPDEINIT_CB_ID :
      hcec->MspDeInitCallback = pCallback;
      break;

    default :
      /* Update the error code */
      hcec->ErrorCode |= HAL_CEC_ERROR_INVALID_CALLBACK;
      /* Return error status */
      status =  HAL_ERROR;
      break;
    }
  }
  else if(hcec->gState == HAL_CEC_STATE_RESET)
  {
    switch (CallbackID)
    {
    case HAL_CEC_MSPINIT_CB_ID :
      hcec->MspInitCallback = pCallback;
      break;

   case HAL_CEC_MSPDEINIT_CB_ID :
      hcec->MspDeInitCallback = pCallback;
      break;

    default :
      /* Update the error code */
      hcec->ErrorCode |= HAL_CEC_ERROR_INVALID_CALLBACK;
     /* Return error status */
      status =  HAL_ERROR;
      break;
    }
  }
  else
  {
    /* Update the error code */
    hcec->ErrorCode |= HAL_CEC_ERROR_INVALID_CALLBACK;
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hcec);

  return status;
}

/**
  * @brief  Unregister an CEC Callback
  *         CEC callabck is redirected to the weak predefined callback
  * @param hcec uart handle
  * @param CallbackID ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_CEC_TX_CPLT_CB_ID Tx Complete callback IDD
  *          @arg @ref HAL_CEC_ERROR_CB_ID Error callback ID
  *          @arg @ref HAL_CEC_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_CEC_MSPDEINIT_CB_ID MspDeInit callback ID
  * @retval status
  */
HAL_StatusTypeDef HAL_CEC_UnRegisterCallback(CEC_HandleTypeDef *hcec, HAL_CEC_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hcec);

  if(hcec->gState == HAL_CEC_STATE_READY)
  {
    switch (CallbackID)
    {
    case HAL_CEC_TX_CPLT_CB_ID :
      hcec->TxCpltCallback = HAL_CEC_TxCpltCallback;  /* Legacy weak  TxCpltCallback */
      break;

    case HAL_CEC_ERROR_CB_ID :
      hcec->ErrorCallback = HAL_CEC_ErrorCallback;  /* Legacy weak ErrorCallback   */
      break;

    case HAL_CEC_MSPINIT_CB_ID :
      hcec->MspInitCallback = HAL_CEC_MspInit;
      break;

   case HAL_CEC_MSPDEINIT_CB_ID :
      hcec->MspDeInitCallback = HAL_CEC_MspDeInit;
      break;

    default :
      /* Update the error code */
      hcec->ErrorCode |= HAL_CEC_ERROR_INVALID_CALLBACK;
     /* Return error status */
      status =  HAL_ERROR;
      break;
    }
  }
  else if(hcec->gState == HAL_CEC_STATE_RESET)
  {
    switch (CallbackID)
    {
    case HAL_CEC_MSPINIT_CB_ID :
      hcec->MspInitCallback = HAL_CEC_MspInit;
      break;

   case HAL_CEC_MSPDEINIT_CB_ID :
      hcec->MspDeInitCallback = HAL_CEC_MspDeInit;
      break;

    default :
      /* Update the error code */
      hcec->ErrorCode |= HAL_CEC_ERROR_INVALID_CALLBACK;
     /* Return error status */
      status =  HAL_ERROR;
      break;
    }
  }
  else
  {
    /* Update the error code */
    hcec->ErrorCode |= HAL_CEC_ERROR_INVALID_CALLBACK;
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hcec);

  return status;
}

/**
  * @brief  Register CEC RX complete Callback
  *         To be used instead of the weak HAL_CEC_RxCpltCallback() predefined callback
  * @param  hcec CEC handle
  * @param  pCallback pointer to the Rx transfer compelete Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_RegisterRxCpltCallback(CEC_HandleTypeDef *hcec, pCEC_RxCallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if(pCallback == NULL)
  {
    /* Update the error code */
    hcec->ErrorCode |= HAL_CEC_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }
  /* Process locked */
  __HAL_LOCK(hcec);

  if(HAL_CEC_STATE_READY == hcec->RxState)
  {
    hcec->RxCpltCallback = pCallback;
  }
  else
  {
    /* Update the error code */
    hcec->ErrorCode |= HAL_CEC_ERROR_INVALID_CALLBACK;
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hcec);
  return status;
}

/**
  * @brief  UnRegister CEC RX complete Callback
  *         CEC RX complete Callback is redirected to the weak HAL_CEC_RxCpltCallback() predefined callback
  * @param  hcec CEC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_UnRegisterRxCpltCallback(CEC_HandleTypeDef *hcec)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hcec);

  if(HAL_CEC_STATE_READY == hcec->RxState)
  {
    hcec->RxCpltCallback = HAL_CEC_RxCpltCallback; /* Legacy weak  CEC RxCpltCallback  */
  }
  else
  {
    /* Update the error code */
    hcec->ErrorCode |= HAL_CEC_ERROR_INVALID_CALLBACK;
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hcec);
  return status;
}
#endif /* USE_HAL_CEC_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup CEC_Exported_Functions_Group2 Input and Output operation functions 
  *  @brief CEC Transmit/Receive functions 
  *
@verbatim   
 ===============================================================================
                      ##### IO operation functions ##### 
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to manage the CEC data transfers.
    
    (#) The CEC handle must contain the initiator (TX side) and the destination (RX side)
        logical addresses (4-bit long addresses, 0xF for broadcast messages destination)
    
    (#) The communication is performed using Interrupts. 
           These API's return the HAL status.
           The end of the data processing will be indicated through the 
           dedicated CEC IRQ when using Interrupt mode.
           The HAL_CEC_TxCpltCallback(), HAL_CEC_RxCpltCallback() user callbacks 
           will be executed respectively at the end of the transmit or Receive process
           The HAL_CEC_ErrorCallback() user callback will be executed when a communication 
           error is detected
        
    (#) API's with Interrupt are :
         (+) HAL_CEC_Transmit_IT()
         (+) HAL_CEC_IRQHandler()

    (#) A set of User Callbacks are provided:
         (+) HAL_CEC_TxCpltCallback()
         (+) HAL_CEC_RxCpltCallback()
         (+) HAL_CEC_ErrorCallback()
      
@endverbatim
  * @{
  */

/**
  * @brief Send data in interrupt mode 
  * @param hcec: CEC handle
  * @param InitiatorAddress: Initiator address
  * @param DestinationAddress: destination logical address      
  * @param pData: pointer to input byte data buffer
  * @param Size: amount of data to be sent in bytes (without counting the header).
  *              0 means only the header is sent (ping operation).
  *              Maximum TX size is 15 bytes (1 opcode and up to 14 operands).    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_Transmit_IT(CEC_HandleTypeDef *hcec, uint8_t InitiatorAddress,uint8_t DestinationAddress, uint8_t *pData, uint32_t Size)
{
  /* if the IP isn't already busy and if there is no previous transmission
     already pending due to arbitration lost */
  if(hcec->gState == HAL_CEC_STATE_READY) 
  {    
    if((pData == NULL ) && (Size > 0U)) 
    {
      return  HAL_ERROR;
    }

    assert_param(IS_CEC_ADDRESS(DestinationAddress));
    assert_param(IS_CEC_ADDRESS(InitiatorAddress)); 
    assert_param(IS_CEC_MSGSIZE(Size));
    
    /* Process Locked */
    __HAL_LOCK(hcec);
    hcec->pTxBuffPtr = pData;
    hcec->gState = HAL_CEC_STATE_BUSY_TX;
    hcec->ErrorCode = HAL_CEC_ERROR_NONE;

    /* initialize the number of bytes to send,
     * 0 means only one header is sent (ping operation) */
    hcec->TxXferCount = Size;

    /* send header block */
    hcec->Instance->TXD = (uint8_t)((uint32_t)InitiatorAddress << CEC_INITIATOR_LSB_POS) | DestinationAddress;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcec); 

    /* case no data to be sent, sender is only pinging the system */
    if (Size != 0)
    {    
      /* Set TX Start of Message (TXSOM) bit */
      MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, CEC_FLAG_TSOM);
    }
    else
    {
      /* Send a ping command */
      MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, CEC_FLAG_TEOM|CEC_FLAG_TSOM);
    }
    return HAL_OK;

  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief Get size of the received frame.
  * @param hcec: CEC handle
  * @retval Frame size
  */
uint32_t HAL_CEC_GetLastReceivedFrameSize(CEC_HandleTypeDef *hcec)
{
  return hcec->RxXferSize;
}

/**
  * @brief Change Rx Buffer.
  * @param hcec: CEC handle
  * @param Rxbuffer: Rx Buffer
  * @note  This function can be called only inside the HAL_CEC_RxCpltCallback() 
  * @retval Frame size
  */
void HAL_CEC_ChangeRxBuffer(CEC_HandleTypeDef *hcec, uint8_t* Rxbuffer)
{
  hcec->Init.RxBuffer = Rxbuffer; 
}
  
/**
  * @brief This function handles CEC interrupt requests.
  * @param hcec: CEC handle
  * @retval None
  */
void HAL_CEC_IRQHandler(CEC_HandleTypeDef *hcec)
{
  /* Save error status register for further error handling purposes */
  hcec->ErrorCode = READ_BIT(hcec->Instance->ESR, CEC_ESR_ALL_ERROR);

  /* Transmit error */
  if(__HAL_CEC_GET_FLAG(hcec, CEC_FLAG_TERR) != RESET)
  {
    /* Acknowledgement of the error */
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_FLAG_TERR);
    
    hcec->gState = HAL_CEC_STATE_READY;
  }
  
  /* Receive error */
  if(__HAL_CEC_GET_FLAG(hcec, CEC_FLAG_RERR) != RESET)
  {
    /* Acknowledgement of the error */
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_FLAG_RERR);
    hcec->Init.RxBuffer-=hcec->RxXferSize;
    hcec->RxXferSize = 0U; 
    hcec->RxState = HAL_CEC_STATE_READY;
  }
  
  if((hcec->ErrorCode & CEC_ESR_ALL_ERROR) != 0U)
  {
    /* Error  Call Back */
#if (USE_HAL_CEC_REGISTER_CALLBACKS == 1)
    hcec->ErrorCallback(hcec);
#else    
    HAL_CEC_ErrorCallback(hcec);
#endif /* USE_HAL_CEC_REGISTER_CALLBACKS */
  }
  
  /* Transmit byte request or block transfer finished */
  if(__HAL_CEC_GET_FLAG(hcec, CEC_FLAG_TBTRF) != RESET)
  {
    CEC_Transmit_IT(hcec);
  }

  /* Receive byte or block transfer finished */
  if(__HAL_CEC_GET_FLAG(hcec, CEC_FLAG_RBTF) != RESET)
  {
    if(hcec->RxXferSize == 0U)
    {
      /* reception is starting */ 
      hcec->RxState = HAL_CEC_STATE_BUSY_RX;
    }
    CEC_Receive_IT(hcec);
  }
}


/**
  * @brief Tx Transfer completed callback
  * @param hcec: CEC handle
  * @retval None
  */
 __weak void HAL_CEC_TxCpltCallback(CEC_HandleTypeDef *hcec)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcec);
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_CEC_TxCpltCallback can be implemented in the user file
   */ 
}

/**
  * @brief Rx Transfer completed callback
  * @param hcec: CEC handle
  * @param RxFrameSize: Size of frame
  * @retval None
  */
__weak void HAL_CEC_RxCpltCallback(CEC_HandleTypeDef *hcec, uint32_t RxFrameSize)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcec);
  UNUSED(RxFrameSize);
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_CEC_RxCpltCallback can be implemented in the user file
   */
}

/**
  * @brief CEC error callbacks
  * @param hcec: CEC handle
  * @retval None
  */
 __weak void HAL_CEC_ErrorCallback(CEC_HandleTypeDef *hcec)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcec);
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_CEC_ErrorCallback can be implemented in the user file
   */ 
}
/**
  * @}
  */

/** @defgroup CEC_Exported_Functions_Group3 Peripheral Control functions 
  *  @brief   CEC control functions 
  *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control function #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the CEC.
     (+) HAL_CEC_GetState() API can be helpful to check in run-time the state of the CEC peripheral. 
	 (+) HAL_CEC_GetError() API can be helpful to check in run-time the error of the CEC peripheral. 
@endverbatim
  * @{
  */
/**
  * @brief return the CEC state
  * @param hcec: pointer to a CEC_HandleTypeDef structure that contains
  *              the configuration information for the specified CEC module.
  * @retval HAL state
  */
HAL_CEC_StateTypeDef HAL_CEC_GetState(CEC_HandleTypeDef *hcec)
{
  uint32_t temp1= 0x00U, temp2 = 0x00U;
  temp1 = hcec->gState;
  temp2 = hcec->RxState;
  
  return (HAL_CEC_StateTypeDef)(temp1 | temp2);
}

/**
* @brief  Return the CEC error code
* @param  hcec : pointer to a CEC_HandleTypeDef structure that contains
  *              the configuration information for the specified CEC.
* @retval CEC Error Code
*/
uint32_t HAL_CEC_GetError(CEC_HandleTypeDef *hcec)
{
  return hcec->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup CEC_Private_Functions
  * @{
  */

 /**
  * @brief Send data in interrupt mode 
  * @param hcec: CEC handle. 
  *         Function called under interruption only, once
  *         interruptions have been enabled by HAL_CEC_Transmit_IT()   
  * @retval HAL status
  */  
static HAL_StatusTypeDef CEC_Transmit_IT(CEC_HandleTypeDef *hcec)
{
  /* if the IP is already busy or if there is a previous transmission
     already pending due to arbitration loss */
  if((hcec->gState == HAL_CEC_STATE_BUSY_TX) || (__HAL_CEC_GET_TRANSMISSION_START_FLAG(hcec) != RESET))
  {
    /* if all data have been sent */
    if(hcec->TxXferCount == 0U)
    {
      /* Acknowledge successful completion by writing 0x00 */
      MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, 0x00U);

      hcec->gState = HAL_CEC_STATE_READY;
#if (USE_HAL_CEC_REGISTER_CALLBACKS == 1)
     hcec->TxCpltCallback(hcec);
#else
     HAL_CEC_TxCpltCallback(hcec);
#endif /* USE_HAL_CEC_REGISTER_CALLBACKS */     
      
      return HAL_OK;
    }
    else
    {
      /* Reduce the number of bytes to transfer by one */
      hcec->TxXferCount--;
      
      /* Write data to TX buffer*/
      hcec->Instance->TXD = *hcec->pTxBuffPtr++;
      
      /* If this is the last byte of the ongoing transmission */
      if(hcec->TxXferCount == 0U)
      {
        /* Acknowledge byte request and signal end of message */
        MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, CEC_FLAG_TEOM);
      }
      else
      {
        /* Acknowledge byte request by writing 0x00 */
        MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, 0x00U);
      }  
      
      return HAL_OK;
    }
  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief Receive data in interrupt mode. 
  * @param hcec: CEC handle.
  *         Function called under interruption only, once
  *         interruptions have been enabled by HAL_CEC_Receive_IT()   
  * @retval HAL status
  */  
static HAL_StatusTypeDef CEC_Receive_IT(CEC_HandleTypeDef *hcec)
{
  static uint32_t temp;
  
  if(hcec->RxState == HAL_CEC_STATE_BUSY_RX)
  {
    temp = hcec->Instance->CSR;
    
    /* Store received data */
    hcec->RxXferSize++;
    *hcec->Init.RxBuffer++ = hcec->Instance->RXD;
    
    /* Acknowledge received byte by writing 0x00 */
    MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_RECEIVE_MASK, 0x00U);
    
    /* If the End Of Message is reached */
    if(HAL_IS_BIT_SET(temp, CEC_FLAG_REOM))
    {
      /* Interrupts are not disabled due to transmission still ongoing */
      hcec->RxState = HAL_CEC_STATE_READY;
#if (USE_HAL_CEC_REGISTER_CALLBACKS == 1)
    hcec->RxCpltCallback(hcec, hcec->RxXferSize);
#else
    HAL_CEC_RxCpltCallback(hcec, hcec->RxXferSize); 
#endif /* USE_HAL_CEC_REGISTER_CALLBACKS */      
      
      return HAL_OK;
    }
    else
    {
      return HAL_BUSY; 
    }
  }
  else
  {
    return HAL_BUSY; 
  }
}

/**
 * @}
 */ 
 
/**
  * @}
  */

#endif /* CEC */

#endif /* HAL_CEC_MODULE_ENABLED */
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
