/**
  ******************************************************************************
  * @file    stm32u5xx_hal_dcache.c
  * @author  MCD Application Team
  * @brief   DCACHE HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the DCACHE.
  *           + Initialization and Configuration
  *           + Cache coherency command
  *           + Monitoring management
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
  [..]
   (#) Configure and enable the MPU to override default config if needed, please refers
       to ARM manual for default memory attribute. Then enable DCache.

    [..]
        (+) Use HAL_DCACHE_Invalidate() to invalidate the full cache content:
            (++) Cache content is lost, and reloaded when needed.
            (++) Used for complete invalidate of the dcache in case.
            (++) Blocking call until operation is done.
        (+) Use HAL_DCACHE_InvalidateByAddr() to invalidate cache content for specific range:
            (++) Cache content for specific range is lost, and reloaded when needed.
            (++) Used when excepting a buffer to be updated by a peripheral (typically DMA transfer)
            (++) Blocking call until operation is done.
        (+) Use HAL_DCACHE_CleanByAddr() to clean cache content for a specific range:
            (++) Cache content for specific range is written back to memory.
            (++) Used when buffer is updated by CPU before usage by a peripheral (typically DMA transfer)
            (++) Blocking call until operation is done.
        (+) Use HAL_DCACHE_CleanInvalidateByAddr() to clean and invalidate cache content for a specific range:
            (++) Cache content for specific range is written back to memory, and reloaded when needed.
            (++) Used when sharing buffer between CPU and other peripheral.
            (++) Recommended to use for MPU reprogramming.
            (++) Blocking call until operation is done.

     *** Interrupt mode IO operation ***
     ===================================
    [..]
        (+) Configure the DCACHE interrupt priority using HAL_NVIC_SetPriority()
        (+) Enable the DCACHE IRQ handler using HAL_NVIC_EnableIRQ()
        (+) Override weak definition for following callback (if needed):
            (++)HAL_DCACHE_CleanAndInvalidateByAddrCallback()
            (++)HAL_DCACHE_InvalidateCompleteCallback()
            (++)HAL_DCACHE_InvalidateByAddrCallback()
            (++)HAL_DCACHE_CleanByAddrCallback()
            (++)HAL_DCACHE_ErrorCallback()
        (+) Use HAL_DCACHE_<COMMAND>_IT() to start a DCache operation with IT enabled.
        (+) Use HAL_DCACHE_IRQHandler() called under DCACHE_IRQHandler() Interrupt subroutine

    [..]  Use HAL_DCACHE_GetState() function to return the DCACHE state and HAL_DCACHE_GetError()
          in case of error detection.

     *** DCACHE HAL driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in DCACHE HAL driver.

      (+) __HAL_DCACHE_ENABLE_IT    : Enable DCACHE interrupts.
      (+) __HAL_DCACHE_DISABLE_IT   : Disable DCACHE interrupts.
      (+) __HAL_DCACHE_GET_IT_SOURCE: Check whether the specified DCACHE interrupt source is enabled or not.
      (+) __HAL_DCACHE_GET_FLAG     : Check whether the selected DCACHE flag is set or not.
      (+) __HAL_DCACHE_CLEAR_FLAG   : Clear the selected DCACHE flags.

     [..]
      (@) You can refer to the header file of the DCACHE HAL driver for more useful macros.

    [..]

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup DCACHE DCACHE
  * @brief HAL DCACHE module driver
  * @{
  */
#ifdef HAL_DCACHE_MODULE_ENABLED

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/** @defgroup DCACHE_Private_Macros DCACHE Private Macros
  * @{
  */
#define IS_DCACHE_REGION_SIZE(__SIZE__)                ((__SIZE__) > 0U)

#define IS_DCACHE_MONITOR_TYPE(__TYPE__)               (((__TYPE__) & ~DCACHE_MONITOR_ALL) == 0U)

#define IS_DCACHE_SINGLE_MONITOR_TYPE(__TYPE__)        (((__TYPE__) == DCACHE_MONITOR_READ_HIT)  || \
                                                        ((__TYPE__) == DCACHE_MONITOR_READ_MISS) || \
                                                        ((__TYPE__) == DCACHE_MONITOR_WRITE_HIT) || \
                                                        ((__TYPE__) == DCACHE_MONITOR_WRITE_MISS))

#define IS_DCACHE_READ_BURST_TYPE(__OUTPUTBURSTTYPE__) (((__OUTPUTBURSTTYPE__) == DCACHE_READ_BURST_WRAP) || \
                                                        ((__OUTPUTBURSTTYPE__) == DCACHE_READ_BURST_INCR))

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup DCACHE_Private_Constants DCACHE Private Constants
  * @{
  */
#define DCACHE_COMMAND_TIMEOUT_VALUE           200U    /* 200ms*/
#define DCACHE_DISABLE_TIMEOUT_VALUE           1U      /* 1ms  */

#define DCACHE_COMMAND_INVALIDATE              DCACHE_CR_CACHECMD_1
#define DCACHE_COMMAND_CLEAN                   DCACHE_CR_CACHECMD_0
#define DCACHE_COMMAND_CLEAN_INVALIDATE        (DCACHE_CR_CACHECMD_0|DCACHE_CR_CACHECMD_1)

#define DCACHE_POLLING_MODE                    0U
#define DCACHE_IT_MODE                         1U

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static HAL_StatusTypeDef DCACHE_CommandByAddr(DCACHE_HandleTypeDef *hdcache, uint32_t Command,
                                              const uint32_t *const pAddr, uint32_t dSize, uint32_t mode);

/* Exported functions --------------------------------------------------------*/
/** @defgroup DCACHE_Exported_Functions DCACHE Exported Functions
  * @{
  */

/** @defgroup DCACHE_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          deinitialize the DCACHEx peripheral:

      (+) User must implement HAL_DCACHE_MspInit() function in which he configures
          all related peripherals resources (CLOCK, MPU, IT and NVIC ).

      (+) Call the function HAL_DCACHE_Init() to configure the selected device with
          the selected configuration:
        (++) ReadBurstType

      (+) Call the function HAL_DCACHE_DeInit() to restore the reset configuration
          of the selected DCACHEx peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the DCACHE according to the specified parameters
  *         in the DCACHE_InitTypeDef and initialize the associated handle.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHE.
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_DCACHE_Init(DCACHE_HandleTypeDef *hdcache)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the DCACHE handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));
  assert_param(IS_DCACHE_READ_BURST_TYPE(hdcache->Init.ReadBurstType));

  if (hdcache->State == HAL_DCACHE_STATE_RESET)
  {
    /* Init the DCACHE Callback settings with legacy weak */
    hdcache->ErrorCallback                      = HAL_DCACHE_ErrorCallback;
    hdcache->CleanByAddrCallback                = HAL_DCACHE_CleanByAddrCallback;
    hdcache->InvalidateByAddrCallback           = HAL_DCACHE_InvalidateByAddrCallback;
    hdcache->InvalidateCompleteCallback         = HAL_DCACHE_InvalidateCompleteCallback;
    hdcache->CleanAndInvalidateByAddrCallback   = HAL_DCACHE_CleanAndInvalidateByAddrCallback;

    if (hdcache->MspInitCallback == NULL)
    {
      hdcache->MspInitCallback = HAL_DCACHE_MspInit;
    }

    /* Init the low level hardware */
    hdcache->MspInitCallback(hdcache);
  }

  hdcache->State = HAL_DCACHE_STATE_BUSY;

  /* Disable the selected DCACHE peripheral */
  if (HAL_DCACHE_Disable(hdcache) != HAL_OK)
  {
    /* Return timeout status */
    status =  HAL_TIMEOUT;
  }
  else
  {
    /* Set requested read burst type */
    MODIFY_REG(hdcache->Instance->CR, DCACHE_CR_HBURST, hdcache->Init.ReadBurstType);

    /* Enable the selected DCACHE peripheral */
    if (HAL_DCACHE_Enable(hdcache) != HAL_OK)
    {
      /* Return error status */
      status =  HAL_ERROR;
    }
  }
  hdcache->State = HAL_DCACHE_STATE_READY;

  return status;
}

/**
  * @brief  DeInitialize the Data cache.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_DeInit(DCACHE_HandleTypeDef *hdcache)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));

  /* Before the lunch of the disable operation check first whether or not DCACHE clock is enabled */
  if (hdcache->State != HAL_DCACHE_STATE_RESET)
  {
    /* Disable cache with reset value */
    if (HAL_DCACHE_Disable(hdcache) != HAL_OK)
    {
      /* Update error code */
      hdcache->ErrorCode = HAL_DCACHE_ERROR_TIMEOUT;

      /* Change the DCACHE state */
      hdcache->State = HAL_DCACHE_STATE_ERROR;

      /* Return error status */
      status =  HAL_ERROR;
    }

    /* reset monitor values */
    (void)HAL_DCACHE_Monitor_Reset(hdcache, DCACHE_MONITOR_ALL);

    /* Reset all remaining bit */
    WRITE_REG(hdcache->Instance->CR, 0U);
    WRITE_REG(hdcache->Instance->CMDRSADDRR, 0U);
    WRITE_REG(hdcache->Instance->CMDREADDRR, 0U);
    WRITE_REG(hdcache->Instance->FCR, DCACHE_FCR_CCMDENDF | DCACHE_FCR_CERRF | DCACHE_FCR_CBSYENDF);

    if (hdcache->MspDeInitCallback == NULL)
    {
      hdcache->MspDeInitCallback = HAL_DCACHE_MspDeInit;
    }

    /* DeInit the low level hardware */
    hdcache->MspDeInitCallback(hdcache);

    /* Return to the reset state */
    hdcache->State = HAL_DCACHE_STATE_RESET;
  }

  return status;
}

/**
  * @brief Initialize the DCACHE MSP.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @retval None
  */
__weak void HAL_DCACHE_MspInit(DCACHE_HandleTypeDef *hdcache)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdcache);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_DCACHE_MspInit can be implemented in the user file
   */
}

/**
  * @brief DeInitialize the DCACHE MSP.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @retval None
  */
__weak void HAL_DCACHE_MspDeInit(DCACHE_HandleTypeDef *hdcache)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdcache);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_DCACHE_MspDeInit can be implemented in the user file
   */
}

/** @defgroup DCACHE_Exported_Functions_Group2 IO operation functions
  *  @brief    IO operation functions
  *
@verbatim
  ==============================================================================
             ##### IO operation functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Enable the Data cache.
      (+) Disable the Data cache.
      (+) Set Read Burst Type.
      (+) Invalidate the Data cache.
      (+) Invalidate the Data cache with interrupt.
      (+) Clean the Data cache by Addr.
      (+) Invalidate the Data cache by Addr.
      (+) Clean and Invalidate the Data cache by Addr.
      (+) Clean the Data cache by Addr with interrupt.
      (+) Invalidate the Data cache by Addr with interrupt.
      (+) Clean and Invalidate the Data cache by Addr with interrupt.
@endverbatim
  * @{
  */

/**
  * @brief  Enable the Data cache.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_Enable(DCACHE_HandleTypeDef *hdcache)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));

  /* Check no ongoing operation */
  if (READ_BIT(hdcache->Instance->SR, (DCACHE_SR_BUSYF | DCACHE_SR_BUSYCMDF)) != 0U)
  {
    /* Return error status */
    status =  HAL_ERROR;
  }
  else
  {
    SET_BIT(hdcache->Instance->CR, DCACHE_CR_EN);
  }

  hdcache->State = HAL_DCACHE_STATE_READY;

  return status;
}

/**
  * @brief  Disable the Data cache.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_Disable(DCACHE_HandleTypeDef *hdcache)
{
  HAL_StatusTypeDef status = HAL_OK;

  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));

  /* Change DCACHE state */
  hdcache->State = HAL_DCACHE_STATE_BUSY;

  /* Get timeout */
  tickstart = HAL_GetTick();

  /* Before disable check first whether or not DCACHE clock is enabled */
  if (hdcache->State != HAL_DCACHE_STATE_RESET)
  {
    CLEAR_BIT(hdcache->Instance->CR, DCACHE_CR_EN);

    /* Wait for end of data cache disabling */
    while (READ_BIT(hdcache->Instance->SR, (DCACHE_SR_BUSYF | DCACHE_SR_BUSYCMDF)) != 0U)
    {
      if ((HAL_GetTick() - tickstart) > DCACHE_DISABLE_TIMEOUT_VALUE)
      {
        /* Update error code */
        hdcache->ErrorCode = HAL_DCACHE_ERROR_TIMEOUT;

        /* Change the DCACHE state */
        hdcache->State = HAL_DCACHE_STATE_ERROR;

        /* Return error status */
        status =  HAL_ERROR;
      }
    }

    hdcache->State = HAL_DCACHE_STATE_RESET;
  }

  return status;
}

/**
  * @brief  Set Read Burst Type.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @param  ReadBurstType Burst type to be applied for Data Cache
  *                       DCACHE_READ_BURST_WRAP, DCACHE_READ_BURST_INC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_SetReadBurstType(DCACHE_HandleTypeDef *hdcache, uint32_t ReadBurstType)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));
  assert_param(IS_DCACHE_READ_BURST_TYPE(ReadBurstType));

  /* check DCACHE state */
  if (hdcache->State == HAL_DCACHE_STATE_RESET)
  {
    /* Set requested read burst type */
    if (ReadBurstType == DCACHE_READ_BURST_WRAP)
    {
      CLEAR_BIT(hdcache->Instance->CR, DCACHE_CR_HBURST);
    }
    else
    {
      SET_BIT(hdcache->Instance->CR, DCACHE_CR_HBURST);
    }
  }
  else
  {
    /* Return error status */
    status =  HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Invalidate the Data cache.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @note   This function waits for end of full cache invalidation
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_Invalidate(DCACHE_HandleTypeDef *hdcache)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tickstart;

  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));

  /* Check no ongoing operation */
  if (READ_BIT(hdcache->Instance->SR, (DCACHE_SR_BUSYF | DCACHE_SR_BUSYCMDF)) != 0U)
  {
    /* Return error status */
    status =  HAL_ERROR;
  }
  else
  {
    /* Make sure flags are reset */
    WRITE_REG(hdcache->Instance->FCR, (DCACHE_FCR_CBSYENDF | DCACHE_FCR_CCMDENDF));

    /* Set no operation on address range */
    MODIFY_REG(hdcache->Instance->CR, DCACHE_CR_CACHECMD, 0U);

    /* Get timeout */
    tickstart = HAL_GetTick();

    /* Launch cache invalidation */
    SET_BIT(hdcache->Instance->CR, DCACHE_CR_CACHEINV);

    /* Wait for end of cache invalidation */
    while (READ_BIT(hdcache->Instance->SR, DCACHE_FCR_CBSYENDF) != 0U)
    {
      if ((HAL_GetTick() - tickstart) > DCACHE_COMMAND_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  return status;
}

/**
  * @brief  Invalidate the Data cache for a specific region.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @param  pAddr Start address of the region to be Invalidated
  * @param  dSize Size of the region to be Invalidated(in bytes)
  * @note   This function waits for end of cache Invalidation
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_InvalidateByAddr(DCACHE_HandleTypeDef *hdcache, const uint32_t *const pAddr,
                                              uint32_t dSize)
{
  HAL_StatusTypeDef status;

  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));
  assert_param(IS_DCACHE_REGION_SIZE(dSize));

  status = DCACHE_CommandByAddr(hdcache, DCACHE_COMMAND_INVALIDATE, pAddr, dSize, DCACHE_POLLING_MODE);

  return status;
}

/**
  * @brief  Clean the Data cache by Addr.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @param  pAddr Start address of the region to be Cleaned
  * @param  dSize Size of the region to be Cleaned (in bytes)
  * @note   This function waits for end of cache Clean
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_CleanByAddr(DCACHE_HandleTypeDef *hdcache, const uint32_t *const pAddr, uint32_t dSize)
{
  HAL_StatusTypeDef status;

  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));
  assert_param(IS_DCACHE_REGION_SIZE(dSize));

  status = DCACHE_CommandByAddr(hdcache, DCACHE_COMMAND_CLEAN, pAddr, dSize, DCACHE_POLLING_MODE);

  return status;
}

/**
  * @brief  Clean and Invalidate the Data cache by Addr.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @param  pAddr Start address of the region to be Cleaned and Invalidated
  * @param  dSize Size of the region to be Cleaned and Invalidated (in bytes)
  * @note   This function waits for end of cache Clean and Invalidation
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_CleanInvalidByAddr(DCACHE_HandleTypeDef *hdcache, const uint32_t *const pAddr,
                                                uint32_t dSize)
{
  HAL_StatusTypeDef status;

  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));
  assert_param(IS_DCACHE_REGION_SIZE(dSize));

  status = DCACHE_CommandByAddr(hdcache, DCACHE_COMMAND_CLEAN_INVALIDATE, pAddr, dSize, DCACHE_POLLING_MODE);

  return status;
}

/**
  * @brief  Invalidate the Data cache with interrupt.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @note   This function launches maintenance operation and returns immediately.
  *         User application shall resort to interrupt generation to check
  *         the end of operation.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_Invalidate_IT(DCACHE_HandleTypeDef *hdcache)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));

  /* Check no ongoing operation */
  if (READ_BIT(hdcache->Instance->SR, (DCACHE_SR_BUSYF | DCACHE_SR_BUSYCMDF)) != 0U)
  {

    /* Return error status */
    status =  HAL_ERROR;
  }
  else
  {
    /* Make sure BSYENDF is reset */
    WRITE_REG(hdcache->Instance->FCR, (DCACHE_FCR_CBSYENDF | DCACHE_FCR_CCMDENDF));

    /* Set no operation on address range for callback under interrupt */
    MODIFY_REG(hdcache->Instance->CR, DCACHE_CR_CACHECMD, 0U);

    /* Enable end of cache invalidation interrupt */
    SET_BIT(hdcache->Instance->IER, DCACHE_IER_BSYENDIE);

    /* Launch cache invalidation */
    SET_BIT(hdcache->Instance->CR, DCACHE_CR_CACHEINV);
  }

  return status;
}

/**
  * @brief  Invalidate the Data cache by Addr with interrupt.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @param  pAddr Start address of the region to be Invalidated
  * @param  dSize Size of the region to be Invalidated
  * @note   This function launches maintenance operation and returns immediately.
  *         User application shall resort to interrupt generation to check
  *         the end of operation.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_InvalidateByAddr_IT(DCACHE_HandleTypeDef *hdcache, const uint32_t *const pAddr,
                                                 uint32_t dSize)
{
  HAL_StatusTypeDef status;

  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));
  assert_param(IS_DCACHE_REGION_SIZE(dSize));

  status = DCACHE_CommandByAddr(hdcache, DCACHE_COMMAND_INVALIDATE, pAddr, dSize, DCACHE_IT_MODE);

  return status;
}

/**
  * @brief  Clean the Data cache by Addr with interrupt.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @param  pAddr Start address of the region to be Cleaned
  * @param  dSize Size of the region to be Cleaned
  * @note   This function launches maintenance operation and returns immediately.
  *         User application shall resort to interrupt generation to check
  *         the end of operation.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_CleanByAddr_IT(DCACHE_HandleTypeDef *hdcache, const uint32_t *const pAddr,
                                            uint32_t dSize)
{
  HAL_StatusTypeDef status;

  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));
  assert_param(IS_DCACHE_REGION_SIZE(dSize));

  status = DCACHE_CommandByAddr(hdcache, DCACHE_COMMAND_CLEAN, pAddr, dSize, DCACHE_IT_MODE);

  return status;
}

/**
  * @brief  Clean and Invalidate the Data cache by Addr with interrupt.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @param  pAddr Start address of the region to be Cleaned and Invalidated
  * @param  dSize Size of the region to be Cleaned and Invalidated
  * @note   This function launches maintenance operation and returns immediately.
  *         User application shall resort to interrupt generation to check
  *         the end of operation.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_CleanInvalidByAddr_IT(DCACHE_HandleTypeDef *hdcache, const uint32_t *const pAddr,
                                                   uint32_t dSize)
{
  HAL_StatusTypeDef status;

  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));
  assert_param(IS_DCACHE_REGION_SIZE(dSize));

  status = DCACHE_CommandByAddr(hdcache, DCACHE_COMMAND_CLEAN_INVALIDATE, pAddr, dSize, DCACHE_IT_MODE);

  return status;
}

/**
  * @brief Handle the Data Cache interrupt request.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @note  This API should be called under the DCACHE_IRQHandler().
  * @retval None
  */
void HAL_DCACHE_IRQHandler(DCACHE_HandleTypeDef *hdcache)
{
  /* Get current interrupt flags and interrupt sources value */
  uint32_t itflags   = READ_REG(hdcache->Instance->SR);
  uint32_t itsources = READ_REG(hdcache->Instance->IER);

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));

  /* Check Data cache Error interrupt flag  */
  if (((itflags & itsources) & DCACHE_FLAG_ERROR) != 0U)
  {
    /* Clear DCACHE error pending flag */
    __HAL_DCACHE_CLEAR_FLAG(hdcache, DCACHE_FLAG_ERROR);

    /* Data cache error interrupt user callback */
    hdcache->ErrorCallback(hdcache);
  }

  if (READ_BIT(hdcache->Instance->CR, DCACHE_CR_CACHECMD) == 0U) /* no operation by range */
  {
    /* Clear DCACHE busyend pending flag */
    __HAL_DCACHE_CLEAR_FLAG(hdcache, DCACHE_FLAG_BUSYEND);

    /* Data cache invalidate complete interrupt user callback */
    hdcache->InvalidateCompleteCallback(hdcache);
  }
  else if (READ_BIT(hdcache->Instance->CR, DCACHE_CR_CACHECMD_1 | DCACHE_CR_CACHECMD_0) == \
           (DCACHE_CR_CACHECMD_1 | DCACHE_CR_CACHECMD_0))
  {
    /* Clear DCACHE cmdend pending flag */
    __HAL_DCACHE_CLEAR_FLAG(hdcache, DCACHE_FLAG_CMDEND);

    /* Data cache clean and invalidate range cmdend interrupt user callback */
    hdcache->CleanAndInvalidateByAddrCallback(hdcache);
  }
  else if (READ_BIT(hdcache->Instance->CR, DCACHE_CR_CACHECMD_0) == DCACHE_CR_CACHECMD_0)
  {
    /* Clear DCACHE cmdend pending flag */
    __HAL_DCACHE_CLEAR_FLAG(hdcache, DCACHE_FLAG_CMDEND);

    /* Data cache clean range cmdend interrupt user callback */
    hdcache->CleanByAddrCallback(hdcache);
  }
  else
  {
    /* Clear DCACHE cmdend pending flag */
    __HAL_DCACHE_CLEAR_FLAG(hdcache, DCACHE_FLAG_CMDEND);

    /* Data cache Invalidate range cmdend interrupt user callback */
    hdcache->InvalidateByAddrCallback(hdcache);
  }

}

/**
  * @brief  Cache clean  command  by address callback.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @retval None
  */
__weak void HAL_DCACHE_CleanByAddrCallback(DCACHE_HandleTypeDef *hdcache)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdcache);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_DCACHE_CleanByAddrCallback() should be implemented in the user file
   */
}

/**
  * @brief  Cache Invalidate  command  by address callback.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @retval None
  */
__weak void HAL_DCACHE_InvalidateByAddrCallback(DCACHE_HandleTypeDef *hdcache)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdcache);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_DCACHE_InvalidateByAddrCallback() should be implemented in the user file
   */
}

/**
  * @brief  Cache clean and Invalidate command  by address callback.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @retval None
  */
__weak void HAL_DCACHE_CleanAndInvalidateByAddrCallback(DCACHE_HandleTypeDef *hdcache)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdcache);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_DCACHE_CleanAndInvalidateByAddrCallback() should be implemented in the user file
   */
}

/**
  * @brief  Cache full invalidation complete callback.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @retval None
  */
__weak void HAL_DCACHE_InvalidateCompleteCallback(DCACHE_HandleTypeDef *hdcache)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdcache);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_DCACHE_InvalidateCompleteCallback() should be implemented in the user file
   */
}

/**
  * @brief  Error callback.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @retval None
  */
__weak void HAL_DCACHE_ErrorCallback(DCACHE_HandleTypeDef *hdcache)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdcache);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_DCACHE_ErrorCallback() should be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup DCACHE_Exported_Functions_Group3 Peripheral State,
 *  @brief   Peripheral State,
 *
@verbatim
 ===============================================================================
            #####          Peripheral State          #####
 ===============================================================================
    [..]
    This subsection permit to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Return the DCACHE handle state.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @retval HAL state
  */
HAL_DCACHE_StateTypeDef HAL_DCACHE_GetState(DCACHE_HandleTypeDef *hdcache)
{
  /* Return DCACHE handle state */
  return hdcache->State;
}

/**
  * @}
  */

/**
  * @brief  Return the DCACHE error code
  * @param  hdcache pointer to a DCACHE_HandleTypeDef structure that contains
  *         the configuration information for the specified DCACHE.
  * @retval DCACHE Error Code
  */
uint32_t HAL_DCACHE_GetError(DCACHE_HandleTypeDef *hdcache)
{
  return hdcache->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup DCACHE_Exported_Functions
  * @{
  */

/** @addtogroup DCACHE_Exported_Functions_Group1
  * @{
  */

/**
  * @brief  Register a User DCACHE Callback
  *         To be used instead of the weak predefined callback
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_DCACHE_CLEAN_BY_ADDRESS_CB_ID Clean By Addr callback ID
  *          @arg @ref HAL_DCACHE_INVALIDATE_BY_ADDRESS_CB_ID Invalidate By Addr callback ID
  *          @arg @ref HAL_DCACHE_CLEAN_AND_INVALIDATE_BY_ADDRESS_CB_ID Clean and Invalidate By Addr callback ID
  *          @arg @ref HAL_DCACHE_INVALIDATE_COMPLETE_CB_ID Invalidate Complete ID
  *          @arg @ref HAL_DCACHE_ERROR_CB_ID  Error callback ID
  *          @arg @ref HAL_DCACHE_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_DCACHE_MSPDEINIT_CB_ID MspDeInit callback ID
  * @param  pCallback pointer to the Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_RegisterCallback(DCACHE_HandleTypeDef *hdcache, HAL_DCACHE_CallbackIDTypeDef CallbackID,
                                              pDCACHE_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hdcache->ErrorCode |= HAL_DCACHE_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  if (HAL_DCACHE_STATE_READY == hdcache->State)
  {
    switch (CallbackID)
    {
      case HAL_DCACHE_CLEAN_BY_ADDRESS_CB_ID :
        hdcache->CleanByAddrCallback = pCallback;
        break;

      case HAL_DCACHE_INVALIDATE_BY_ADDRESS_CB_ID :
        hdcache->InvalidateByAddrCallback = pCallback;
        break;

      case HAL_DCACHE_CLEAN_AND_INVALIDATE_BY_ADDRESS_CB_ID :
        hdcache->CleanAndInvalidateByAddrCallback = pCallback;
        break;

      case HAL_DCACHE_INVALIDATE_COMPLETE_CB_ID :
        hdcache->InvalidateCompleteCallback = pCallback;
        break;

      case HAL_DCACHE_ERROR_CB_ID :
        hdcache->ErrorCallback = pCallback;
        break;

      case HAL_DCACHE_MSPINIT_CB_ID :
        hdcache->MspInitCallback = pCallback;
        break;

      case HAL_DCACHE_MSPDEINIT_CB_ID :
        hdcache->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hdcache->ErrorCode |= HAL_DCACHE_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_DCACHE_STATE_RESET == hdcache->State)
  {
    switch (CallbackID)
    {
      case HAL_DCACHE_MSPINIT_CB_ID :
        hdcache->MspInitCallback = pCallback;
        break;

      case HAL_DCACHE_MSPDEINIT_CB_ID :
        hdcache->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hdcache->ErrorCode |= HAL_DCACHE_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hdcache->ErrorCode |= HAL_DCACHE_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Unregister an DCACHE Callback
  *         DCACHE callback is redirected to the weak predefined callback
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @param  CallbackID ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_DCACHE_CLEAN_BY_ADDRESS_CB_ID Clean By Addr callback ID
  *          @arg @ref HAL_DCACHE_INVALIDATE_BY_ADDRESS_CB_ID Invalidate By Addr callback ID
  *          @arg @ref HAL_DCACHE_CLEAN_AND_INVALIDATE_BY_ADDRESS_CB_ID Clean and Invalidate By Addr callback ID
  *          @arg @ref HAL_DCACHE_INVALIDATE_COMPLETE_CB_ID Invalidate Complete callback ID
  *          @arg @ref HAL_DCACHE_ERROR_CB_ID  Error callback ID
  *          @arg @ref HAL_DCACHE_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_DCACHE_MSPDEINIT_CB_ID MspDeInit callback ID
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_UnRegisterCallback(DCACHE_HandleTypeDef *hdcache, HAL_DCACHE_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (HAL_DCACHE_STATE_READY == hdcache->State)
  {
    switch (CallbackID)
    {
      case HAL_DCACHE_CLEAN_BY_ADDRESS_CB_ID :
        /* Legacy weak Clean By Addr Callback */
        hdcache->CleanByAddrCallback = HAL_DCACHE_CleanByAddrCallback;
        break;

      case HAL_DCACHE_INVALIDATE_BY_ADDRESS_CB_ID :
        /* Legacy weak Invalidate By Addr Callback */
        hdcache->InvalidateByAddrCallback = HAL_DCACHE_InvalidateByAddrCallback;
        break;

      case HAL_DCACHE_CLEAN_AND_INVALIDATE_BY_ADDRESS_CB_ID :
        /* Legacy weak Clean and Invalidate By Addr Callback */
        hdcache->InvalidateByAddrCallback = HAL_DCACHE_CleanAndInvalidateByAddrCallback;
        break;

      case HAL_DCACHE_INVALIDATE_COMPLETE_CB_ID :
        /* Legacy weak Invalidate Complete Callback */
        hdcache->InvalidateCompleteCallback = HAL_DCACHE_InvalidateCompleteCallback;
        break;

      case HAL_DCACHE_ERROR_CB_ID :
        /* Legacy weak ErrorCallback */
        hdcache->ErrorCallback = HAL_DCACHE_ErrorCallback;
        break;

      case HAL_DCACHE_MSPINIT_CB_ID :
        /* Legacy weak MspInit */
        hdcache->MspInitCallback = HAL_DCACHE_MspInit;
        break;

      case HAL_DCACHE_MSPDEINIT_CB_ID :
        /* Legacy weak MspDeInit */
        hdcache->MspDeInitCallback = HAL_DCACHE_MspDeInit;
        break;

      default :
        /* Update the error code */
        hdcache->ErrorCode |= HAL_DCACHE_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_DCACHE_STATE_RESET == hdcache->State)
  {
    switch (CallbackID)
    {
      case HAL_DCACHE_MSPINIT_CB_ID :
        /* Legacy weak MspInit */
        hdcache->MspInitCallback = HAL_DCACHE_MspInit;
        break;

      case HAL_DCACHE_MSPDEINIT_CB_ID :
        /* Legacy weak MspDeInit */
        hdcache->MspDeInitCallback = HAL_DCACHE_MspDeInit;
        break;

      default :
        /* Update the error code */
        hdcache->ErrorCode |= HAL_DCACHE_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hdcache->ErrorCode |= HAL_DCACHE_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Start the Data Cache performance monitoring.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @param  MonitorType Monitoring type
  *         This parameter can be a combination of the following values:
  *            @arg DCACHE_MONITOR_READ_HIT
  *            @arg DCACHE_MONITOR_READ_MISS
  *            @arg DCACHE_MONITOR_WRITE_HIT
  *            @arg DCACHE_MONITOR_WRITE_MISS
  *            @arg DCACHE_MONITOR_ALL
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_Monitor_Start(DCACHE_HandleTypeDef *hdcache, uint32_t MonitorType)
{
  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));
  assert_param(IS_DCACHE_MONITOR_TYPE(MonitorType));

  SET_BIT(hdcache->Instance->CR, MonitorType);

  return HAL_OK;
}

/**
  * @brief  Stop the Data Cache performance monitoring.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @note   Stopping the monitoring does not reset the values.
  * @param  MonitorType Monitoring type
  *         This parameter can be a combination of the following values:
  *            @arg DCACHE_MONITOR_READ_HIT
  *            @arg DCACHE_MONITOR_READ_MISS
  *            @arg DCACHE_MONITOR_WRITE_HIT
  *            @arg DCACHE_MONITOR_WRITE_MISS
  *            @arg DCACHE_MONITOR_ALL
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_Monitor_Stop(DCACHE_HandleTypeDef *hdcache, uint32_t MonitorType)
{
  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));
  assert_param(IS_DCACHE_MONITOR_TYPE(MonitorType));

  CLEAR_BIT(hdcache->Instance->CR, MonitorType);

  return HAL_OK;
}

/**
  * @brief  Reset the Data Cache performance monitoring values.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @param  MonitorType Monitoring type
  *         This parameter can be a combination of the following values:
  *            @arg DCACHE_MONITOR_READ_HIT
  *            @arg DCACHE_MONITOR_READ_MISS
  *            @arg DCACHE_MONITOR_WRITE_HIT
  *            @arg DCACHE_MONITOR_WRITE_MISS
  *            @arg DCACHE_MONITOR_ALL
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCACHE_Monitor_Reset(DCACHE_HandleTypeDef *hdcache, uint32_t MonitorType)
{
  /* Check the dcache handle allocation */
  if (hdcache == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));
  assert_param(IS_DCACHE_MONITOR_TYPE(MonitorType));

  /* Force/Release reset */
  SET_BIT(hdcache->Instance->CR, (MonitorType << 2U));
  CLEAR_BIT(hdcache->Instance->CR, (MonitorType << 2U));

  return HAL_OK;
}

/**
  * @brief  Get the Data Cache performance Read Hit monitoring value.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @note   Upon reaching the maximum value, monitor does not wrap.
  * @retval Read Hit monitoring value
  */
uint32_t HAL_DCACHE_Monitor_GetReadHitValue(DCACHE_HandleTypeDef *hdcache)
{
  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));

  /*return the Read Hit monitor value*/
  return hdcache->Instance->RHMONR;
}

/**
  * @brief  Get the Data Cache performance Read Miss monitoring value.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @note   Upon reaching the maximum value, monitor does not wrap.
  * @retval Read Miss monitoring value
  */
uint32_t HAL_DCACHE_Monitor_GetReadMissValue(DCACHE_HandleTypeDef *hdcache)
{
  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));

  /*return the Read Miss monitor value*/
  return hdcache->Instance->RMMONR;
}

/**
  * @brief  Get the Data Cache performance Write Hit monitoring value.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @note   Upon reaching the maximum value, monitor does not wrap.
  * @retval Write Hit monitoring value
  */
uint32_t HAL_DCACHE_Monitor_GetWriteHitValue(DCACHE_HandleTypeDef *hdcache)
{
  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));

  /*return the Write Hit monitor value*/
  return hdcache->Instance->WHMONR;
}

/**
  * @brief  Get the Data Cache performance Write Miss monitoring value.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @note   Upon reaching the maximum value, monitor does not wrap.
  * @retval Write Miss monitoring value
  */
uint32_t HAL_DCACHE_Monitor_GetWriteMissValue(DCACHE_HandleTypeDef *hdcache)
{
  /* Check the parameters */
  assert_param(IS_DCACHE_ALL_INSTANCE(hdcache->Instance));

  /*return the Write Miss monitor value*/
  return hdcache->Instance->WMMONR;
}
/**
  * @}
  */

/**
  * @brief  launch dcache command Clean, Invalidate or clean and invalidate by Addr.
  * @param  hdcache Pointer to a DCACHE_HandleTypeDef structure that contains
  *                 the configuration information for the specified DCACHEx peripheral.
  * @param  Command command to be applied for the dcache
  *                       DCACHE_COMMAND_INVALIDATE, DCACHE_COMMAND_CLEAN, DCACHE_COMMAND_CLEAN_INVALIDATE
  * @param  pAddr Start address of region to be Cleaned, Invalidated or Cleaned and Invalidated.
  * @param  dSize Size of the region to be Cleaned, Invalidated or Cleaned and Invalidated (in bytes).
  * @param  mode mode to be applied for the dcache
  *                       DCACHE_IT_MODE, DCACHE_POLLING_MODE.
  * @retval HAL status
  */
static HAL_StatusTypeDef DCACHE_CommandByAddr(DCACHE_HandleTypeDef *hdcache, uint32_t Command,
                                              const uint32_t *const pAddr, uint32_t dSize, uint32_t mode)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t op_addr = (uint32_t)pAddr;
  uint32_t tickstart;

  /* Set HAL_DCACHE_STATE_BUSY */
  hdcache->State = HAL_DCACHE_STATE_BUSY;

  /* Check no ongoing operation */
  if (READ_BIT(hdcache->Instance->SR, (DCACHE_SR_BUSYF | DCACHE_SR_BUSYCMDF)) != 0U)
  {
    return HAL_ERROR;
  }
  else
  {
    /* Make sure flags are reset */
    WRITE_REG(hdcache->Instance->FCR, (DCACHE_FCR_CBSYENDF | DCACHE_FCR_CCMDENDF));

    /* Get timeout */
    tickstart = HAL_GetTick();

    /* Fill area start address */
    WRITE_REG(hdcache->Instance->CMDRSADDRR, op_addr);

    /* Fill area end address */
    WRITE_REG(hdcache->Instance->CMDREADDRR, (op_addr + dSize - 1U));

    /* Set command */
    MODIFY_REG(hdcache->Instance->CR, DCACHE_CR_CACHECMD, Command);

    /* Enable IT if required */
    if (mode == DCACHE_IT_MODE)
    {
      /* Enable end of cache command interrupt */
      SET_BIT(hdcache->Instance->IER, DCACHE_IER_CMDENDIE);

      /* Launch cache command */
      SET_BIT(hdcache->Instance->CR, DCACHE_CR_STARTCMD);
    }
    else
    {

      /* Make sure that end of cache command interrupt is disabled */
      CLEAR_BIT(hdcache->Instance->IER, DCACHE_IER_CMDENDIE);

      /* Launch cache command */
      SET_BIT(hdcache->Instance->CR, DCACHE_CR_STARTCMD);

      /* Wait for end of cache command */
      while (READ_BIT(hdcache->Instance->SR, DCACHE_SR_CMDENDF) == 0U)
      {
        if ((HAL_GetTick() - tickstart) > DCACHE_COMMAND_TIMEOUT_VALUE)
        {
          /* Update error code */
          hdcache->ErrorCode = HAL_DCACHE_ERROR_TIMEOUT;

          /* Change the DCACHE state */
          hdcache->State = HAL_DCACHE_STATE_ERROR;

          /* Return error status */
          status =  HAL_ERROR;
        }
      }
    }
  }

  /* Set HAL_DCACHE_STATE_READY */
  hdcache->State = HAL_DCACHE_STATE_READY;

  return status;
}


#endif /* HAL_DCACHE_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
