/**
  ******************************************************************************
  * @file    stm32h7xx_hal_sai_ex.c
  * @author  MCD Application Team
  * @brief   SAI Extended HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionality of the SAI Peripheral Controller:
  *           + Modify PDM microphone delays.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */
#ifdef HAL_SAI_MODULE_ENABLED

/** @defgroup SAIEx SAIEx
  * @brief SAI Extended HAL module driver
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
#define SAI_PDM_DELAY_MASK          0x77U
#define SAI_PDM_DELAY_OFFSET        8U
#define SAI_PDM_RIGHT_DELAY_OFFSET  4U

/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup SAIEx_Exported_Functions SAIEx Extended Exported Functions
  * @{
  */

/** @defgroup SAIEx_Exported_Functions_Group1 Peripheral Control functions
  * @brief    SAIEx control functions
  *
@verbatim
 ===============================================================================
                 ##### Extended features functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Modify PDM microphone delays

@endverbatim
  * @{
  */

/**
  * @brief  Configure PDM microphone delays.
  * @param  hsai SAI handle.
  * @param  pdmMicDelay Microphone delays configuration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SAIEx_ConfigPdmMicDelay(const SAI_HandleTypeDef *hsai,
                                              const SAIEx_PdmMicDelayParamTypeDef *pdmMicDelay)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t offset;
  SAI_TypeDef *SaiBaseAddress;

  /* Get the SAI base address according to the SAI handle */
#if defined(SAI4)
  SaiBaseAddress = ((hsai->Instance == SAI1_Block_A) ? SAI1 : \
                    (hsai->Instance == SAI4_Block_A) ? SAI4 : \
                     NULL);
#else
  SaiBaseAddress = ((hsai->Instance == SAI1_Block_A) ? SAI1 : NULL);
#endif /* SAI4 */

  /* Check that SAI sub-block is SAI sub-block A */
  if (SaiBaseAddress == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check microphone delay parameters */
    assert_param(IS_SAI_PDM_MIC_PAIRS_NUMBER(pdmMicDelay->MicPair));
    assert_param(IS_SAI_PDM_MIC_DELAY(pdmMicDelay->LeftDelay));
    assert_param(IS_SAI_PDM_MIC_DELAY(pdmMicDelay->RightDelay));

    /* Compute offset on PDMDLY register according mic pair number */
    offset = SAI_PDM_DELAY_OFFSET * (pdmMicDelay->MicPair - 1U);

    /* Check SAI state and offset */
    if ((hsai->State != HAL_SAI_STATE_RESET) && (offset <= 24U))
    {
      /* Reset current delays for specified microphone */
      SaiBaseAddress->PDMDLY &= ~(SAI_PDM_DELAY_MASK << offset);

      /* Apply new microphone delays */
      SaiBaseAddress->PDMDLY |= (((pdmMicDelay->RightDelay << SAI_PDM_RIGHT_DELAY_OFFSET) | pdmMicDelay->LeftDelay) << offset);
    }
    else
    {
      status = HAL_ERROR;
    }
  }
  return status;
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

#endif /* HAL_SAI_MODULE_ENABLED */
/**
  * @}
  */

