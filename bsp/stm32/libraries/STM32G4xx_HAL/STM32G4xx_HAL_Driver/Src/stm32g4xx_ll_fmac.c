/**
  ******************************************************************************
  * @file    stm32g4xx_ll_fmac.c
  * @author  MCD Application Team
  * @brief   Header for stm32g4xx_ll_fmac.c module
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
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_ll_fmac.h"
#include "stm32g4xx_ll_bus.h"
#ifdef USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32G4xx_LL_Driver
  * @{
  */

#if defined(FMAC)

/** @addtogroup FMAC_LL
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/
/** @addtogroup FMAC_LL_Exported_Functions
  * @{
  */

/** @addtogroup FMAC_LL_EF_Init
  * @{
  */

/**
  * @brief  Initialize FMAC peripheral registers to their default reset values.
  * @param  FMACx FMAC Instance
  * @retval ErrorStatus enumeration value:
  *          - SUCCESS: FMAC registers are initialized
  *          - ERROR: FMAC registers are not initialized
  */
ErrorStatus LL_FMAC_Init(FMAC_TypeDef *FMACx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_FMAC_ALL_INSTANCE(FMACx));

  if (FMACx == FMAC)
  {
    /* Perform the reset */
    LL_FMAC_EnableReset(FMACx);

    /* Wait until flag is reset */
    while (LL_FMAC_IsEnabledReset(FMACx) != 0UL)
    {
    }
  }
  else
  {
    status = ERROR;
  }

  return (status);
}

/**
  * @brief  De-Initialize FMAC peripheral registers to their default reset values.
  * @param  FMACx FMAC Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: FMAC registers are de-initialized
  *          - ERROR: FMAC registers are not de-initialized
  */
ErrorStatus LL_FMAC_DeInit(FMAC_TypeDef *FMACx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_FMAC_ALL_INSTANCE(FMACx));

  if (FMACx == FMAC)
  {
    /* Force FMAC reset */
    LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_FMAC);

    /* Release FMAC reset */
    LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_FMAC);
  }
  else
  {
    status = ERROR;
  }

  return (status);
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

#endif /* defined(FMAC) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
