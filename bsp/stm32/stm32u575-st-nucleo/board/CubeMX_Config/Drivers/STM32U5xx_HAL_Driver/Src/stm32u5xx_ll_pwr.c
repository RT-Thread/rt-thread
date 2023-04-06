/**
  ******************************************************************************
  * @file    stm32u5xx_ll_pwr.c
  * @author  MCD Application Team
  * @brief   PWR LL module driver.
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
  */

#if defined (USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_ll_pwr.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup PWR_LL_Exported_Functions
  * @{
  */

/** @addtogroup PWR_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the PWR registers to their default reset values.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS : PWR registers are de-initialized.
  *          - ERROR   : not applicable.
  */
ErrorStatus LL_PWR_DeInit(void)
{
  /* Clear PWR low power flags */
  LL_PWR_ClearFlag_STOP();

  /* Clear PWR wake up flags */
  LL_PWR_ClearFlag_WU();

  /* Reset privilege attribute for nsecure attribute */
  LL_PWR_DisableNSecurePrivilege();

#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
  /* Reset privilege attribute for nsecure attribute */
  LL_PWR_DisableSecurePrivilege();

  /* Reset secure attribute */
  LL_PWR_ConfigSecure(0);
#endif /* defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U) */

  return SUCCESS;
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
#endif /* defined(PWR) */
/**
  * @}
  */

#endif /* defined (USE_FULL_LL_DRIVER) */
