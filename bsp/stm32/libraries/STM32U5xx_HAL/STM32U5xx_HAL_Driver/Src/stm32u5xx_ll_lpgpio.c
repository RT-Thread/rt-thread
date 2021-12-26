/**
  ******************************************************************************
  * @file    stm32u5xx_ll_lpgpio.c
  * @author  MCD Application Team
  * @brief   LPGPIO LL module driver.
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_ll_lpgpio.h"
#include "stm32u5xx_ll_bus.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (LPGPIO1)

/** @addtogroup LPGPIO_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup LPGPIO_LL_Private_Macros
  * @{
  */
#define IS_LL_LPGPIO_PIN(__VALUE__)          (((0x00000000U) < (__VALUE__)) && ((__VALUE__) <= (LL_LPGPIO_PIN_ALL)))

#define IS_LL_LPGPIO_MODE(__VALUE__)         (((__VALUE__) == LL_LPGPIO_MODE_INPUT)     ||\
                                              ((__VALUE__) == LL_LPGPIO_MODE_OUTPUT))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup LPGPIO_LL_Exported_Functions
  * @{
  */

/** @addtogroup LPGPIO_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize LPGPIO registers (Registers restored to their default values).
  * @param  LPGPIOx LPGPIO Port
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: LPGPIO registers are de-initialized
  *          - ERROR:   Wrong LPGPIO Port
  */
ErrorStatus LL_LPGPIO_DeInit(GPIO_TypeDef *LPGPIOx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_LPGPIO_ALL_INSTANCE(LPGPIOx));

  /* Force and Release reset on clock of LPGPIOx Port */
  if (LPGPIOx == LPGPIO1)
  {
    LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_LPGPIO1);
    LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_LPGPIO1);
  }
  else
  {
    status = ERROR;
  }

  return (status);
}

/**
  * @brief  Initialize LPGPIO registers according to the specified parameters in LPGPIO_InitStruct.
  * @param  LPGPIOx LPGPIO Port
  * @param  LPGPIO_InitStruct: pointer to a @ref LL_LPGPIO_InitTypeDef structure
  *         that contains the configuration information for the specified LPGPIO peripheral.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: LPGPIO registers are initialized according to LPGPIO_InitStruct content
  *          - ERROR:   Not applicable
  */
ErrorStatus LL_LPGPIO_Init(GPIO_TypeDef *LPGPIOx, const LL_LPGPIO_InitTypeDef *const LPGPIO_InitStruct)
{
  uint32_t pinpos;
  uint32_t currentpin;

  /* Check the parameters */
  assert_param(IS_LPGPIO_ALL_INSTANCE(LPGPIOx));
  assert_param(IS_LL_LPGPIO_PIN(LPGPIO_InitStruct->Pin));
  assert_param(IS_LL_LPGPIO_MODE(LPGPIO_InitStruct->Mode));

  /* ------------------------- Configure the port pins ---------------- */
  /* Initialize  pinpos on first pin set */
  pinpos = POSITION_VAL(LPGPIO_InitStruct->Pin);

  /* Configure the port pins */
  while (((LPGPIO_InitStruct->Pin) >> pinpos) != 0U)
  {
    /* Get current io position */
    currentpin = (LPGPIO_InitStruct->Pin) & (1UL << pinpos);

    if (currentpin != 0U)
    {
      /* Pin Mode configuration */
      LL_LPGPIO_SetPinMode(LPGPIOx, currentpin, LPGPIO_InitStruct->Mode);
    }
    pinpos++;
  }
  return (SUCCESS);
}

/**
  * @brief Set each @ref LL_LPGPIO_InitTypeDef field to default value.
  * @param LPGPIO_InitStruct: pointer to a @ref LL_LPGPIO_InitTypeDef structure
  *                           whose fields will be set to default values.
  * @retval None
  */

void LL_LPGPIO_StructInit(LL_LPGPIO_InitTypeDef *LPGPIO_InitStruct)
{
  /* Reset LPGPIO init structure parameters values */
  LPGPIO_InitStruct->Pin        = LL_LPGPIO_PIN_ALL;
  LPGPIO_InitStruct->Mode       = LL_LPGPIO_MODE_INPUT;
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

#endif /* defined (LPGPIO1) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
