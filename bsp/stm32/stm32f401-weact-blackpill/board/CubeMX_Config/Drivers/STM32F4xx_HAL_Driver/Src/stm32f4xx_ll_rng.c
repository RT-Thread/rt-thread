/**
  ******************************************************************************
  * @file    stm32f4xx_ll_rng.c
  * @author  MCD Application Team
  * @brief   RNG LL module driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_ll_rng.h"
#include "stm32f4xx_ll_bus.h"

#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32F4xx_LL_Driver
  * @{
  */

#if defined (RNG)

/** @addtogroup RNG_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RNG_LL_Exported_Functions
  * @{
  */

/** @addtogroup RNG_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize RNG registers (Registers restored to their default values).
  * @param  RNGx RNG Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RNG registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_RNG_DeInit(RNG_TypeDef *RNGx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_RNG_ALL_INSTANCE(RNGx));
  if (RNGx == RNG)
  {
#if !defined(RCC_AHB2_SUPPORT)
    /* Enable RNG reset state */
    LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_RNG);

    /* Release RNG from reset state */
    LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_RNG);
#else
    /* Enable RNG reset state */
    LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_RNG);

  /* Release RNG from reset state */
    LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_RNG);
#endif /* !RCC_AHB2_SUPPORT */
  }
  else
  {
    status = ERROR;
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

#endif /* RNG */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

