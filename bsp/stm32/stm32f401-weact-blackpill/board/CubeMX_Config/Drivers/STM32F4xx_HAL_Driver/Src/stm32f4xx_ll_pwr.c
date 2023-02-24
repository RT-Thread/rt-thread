/**
  ******************************************************************************
  * @file    stm32f4xx_ll_pwr.c
  * @author  MCD Application Team
  * @brief   PWR LL module driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_bus.h"

/** @addtogroup STM32F4xx_LL_Driver
  * @{
  */

#if defined(PWR)

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
  *          - SUCCESS: PWR registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_PWR_DeInit(void)
{
  /* Force reset of PWR clock */
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_PWR);

  /* Release reset of PWR clock */
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_PWR);

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

#endif /* USE_FULL_LL_DRIVER */
