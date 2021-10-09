/**
  ******************************************************************************
  * @file    stm32h7xx_ll_fmac.c
  * @author  MCD Application Team
  * @brief   FMAC LL module driver.
  ******************************************************************************
  * @attention
  *
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_ll_fmac.h"
#include "stm32h7xx_ll_bus.h"
#ifdef USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32H7xx_LL_Driver
  * @{
  */

#if defined(FMAC)

/** @addtogroup FMAC_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup FMAC_LL_Private_Macros
  * @{
  */

/** @brief  Check if the watermark value is a valid one.
  * @param  __VALUE__ Watermak value.
  * @retval SET (__VALUE__ is a valid value) or RESET (__VALUE__ is invalid)
  */
#define IS_LL_FMAC_WM(__VALUE__) (((__VALUE__) == LL_FMAC_WM_0_THRESHOLD_1) \
                                  || ((__VALUE__) == LL_FMAC_WM_1_THRESHOLD_2) \
                                  || ((__VALUE__) == LL_FMAC_WM_2_THRESHOLD_4) \
                                  || ((__VALUE__) == LL_FMAC_WM_3_THRESHOLD_8))

/** @brief  Check if the function ID is a valid one.
  * @param  __VALUE__ Function ID.
  * @retval SET (__VALUE__ is a valid value) or RESET (__VALUE__ is invalid)
  */
#define IS_LL_FMAC_FUNC(__VALUE__) (((__VALUE__) == LL_FMAC_FUNC_LOAD_X1) \
                                    || ((__VALUE__) == LL_FMAC_FUNC_LOAD_X2) \
                                    || ((__VALUE__) == LL_FMAC_FUNC_LOAD_Y) \
                                    || ((__VALUE__) == LL_FMAC_FUNC_CONVO_FIR) \
                                    || ((__VALUE__) == LL_FMAC_FUNC_IIR_DIRECT_FORM_1))


/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FMAC_LL_Exported_Functions
  * @{
  */

/** @addtogroup FMAC_LL_EF_Init
  * @{
  */

/**
  * @brief  Initialize FMAC peripheral registers to their default reset values.
  * @param  FMACx FMAC Instance
  * @retval An ErrorStatus enumeration value:
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
    LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_FMAC);

    /* Release FMAC reset */
    LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_FMAC);
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
