/**
  ******************************************************************************
  * @file    stm32u5xx_ll_lpgpio.h
  * @author  MCD Application Team
  * @brief   Header file of LPGPIO LL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_LL_LPGPIO_H
#define STM32U5xx_LL_LPGPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (LPGPIO1)

/** @defgroup LPGPIO_LL LPGPIO
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup LPGPIO_LL_Private_Macros LPGPIO Private Macros
  * @{
  */

/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup LPGPIO_LL_ES_INIT LPGPIO Exported Init structures
  * @{
  */

/**
  * @brief LL LPGPIO Init Structure definition
  */
typedef struct
{
  uint32_t Pin;          /*!< Specifies the LPGPIO pins to be configured.
                              This parameter can be any value of @ref LPGPIO_LL_EC_PIN */

  uint32_t Mode;         /*!< Specifies the operating mode for the selected pins.
                              This parameter can be a value of @ref LPGPIO_LL_EC_MODE.*/

} LL_LPGPIO_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup LPGPIO_LL_Exported_Constants LPGPIO Exported Constants
  * @{
  */

/** @defgroup LPGPIO_LL_EC_PIN PIN
  * @{
  */
#define LL_LPGPIO_PIN_0                   LPGPIO_BSRR_BS0 /*!< Select pin 0 */
#define LL_LPGPIO_PIN_1                   LPGPIO_BSRR_BS1 /*!< Select pin 1 */
#define LL_LPGPIO_PIN_2                   LPGPIO_BSRR_BS2 /*!< Select pin 2 */
#define LL_LPGPIO_PIN_3                   LPGPIO_BSRR_BS3 /*!< Select pin 3 */
#define LL_LPGPIO_PIN_4                   LPGPIO_BSRR_BS4 /*!< Select pin 4 */
#define LL_LPGPIO_PIN_5                   LPGPIO_BSRR_BS5 /*!< Select pin 5 */
#define LL_LPGPIO_PIN_6                   LPGPIO_BSRR_BS6 /*!< Select pin 6 */
#define LL_LPGPIO_PIN_7                   LPGPIO_BSRR_BS7 /*!< Select pin 7 */
#define LL_LPGPIO_PIN_8                   LPGPIO_BSRR_BS8 /*!< Select pin 8 */
#define LL_LPGPIO_PIN_9                   LPGPIO_BSRR_BS9 /*!< Select pin 9 */
#define LL_LPGPIO_PIN_10                  LPGPIO_BSRR_BS10 /*!< Select pin 10 */
#define LL_LPGPIO_PIN_11                  LPGPIO_BSRR_BS11 /*!< Select pin 11 */
#define LL_LPGPIO_PIN_12                  LPGPIO_BSRR_BS12 /*!< Select pin 12 */
#define LL_LPGPIO_PIN_13                  LPGPIO_BSRR_BS13 /*!< Select pin 13 */
#define LL_LPGPIO_PIN_14                  LPGPIO_BSRR_BS14 /*!< Select pin 14 */
#define LL_LPGPIO_PIN_15                  LPGPIO_BSRR_BS15 /*!< Select pin 15 */
#define LL_LPGPIO_PIN_ALL                 (LPGPIO_BSRR_BS0  | LPGPIO_BSRR_BS1  | LPGPIO_BSRR_BS2  | \
                                           LPGPIO_BSRR_BS3  | LPGPIO_BSRR_BS4  | LPGPIO_BSRR_BS5  | \
                                           LPGPIO_BSRR_BS6  | LPGPIO_BSRR_BS7  | LPGPIO_BSRR_BS8  | \
                                           LPGPIO_BSRR_BS9  | LPGPIO_BSRR_BS10 | LPGPIO_BSRR_BS11 | \
                                           LPGPIO_BSRR_BS12 | LPGPIO_BSRR_BS13 | LPGPIO_BSRR_BS14 | \
                                           LPGPIO_BSRR_BS15) /*!< Select all pins */
/**
  * @}
  */

/** @defgroup LPGPIO_LL_EC_MODE Mode
  * @{
  */
#define LL_LPGPIO_MODE_INPUT                 (0x00000000U) /*!< Select input mode */
#define LL_LPGPIO_MODE_OUTPUT                LPGPIO_MODER_MOD0  /*!< Select output mode */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup LPGPIO_LL_Exported_Macros LPGPIO Exported Macros
  * @{
  */

/** @defgroup LPGPIO_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in LPGPIO register
  * @param  __INSTANCE__ LPGPIO Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_LPGPIO_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in LPGPIO register
  * @param  __INSTANCE__ LPGPIO Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_LPGPIO_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup LPGPIO_LL_Exported_Functions LPGPIO Exported Functions
  * @{
  */

/** @defgroup LPGPIO_LL_EF_Port_Configuration Port Configuration
  * @{
  */

/**
  * @brief  Configure lpgpio mode for a dedicated pin on dedicated port.
  * @note   I/O mode can be Input mode, General purpose output, Alternate function mode or Analog.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll MODER        MODEy         LL_LPGPIO_SetPinMode
  * @param  LPGPIOx LPGPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_LPGPIO_MODE_INPUT
  *         @arg @ref LL_LPGPIO_MODE_OUTPUT
  * @retval None
  */
__STATIC_INLINE void LL_LPGPIO_SetPinMode(GPIO_TypeDef *LPGPIOx, uint32_t Pin, uint32_t Mode)
{
  MODIFY_REG(LPGPIOx->MODER, (LPGPIO_MODER_MOD0 << (POSITION_VAL(Pin))), (Mode << (POSITION_VAL(Pin))));
}

/**
  * @brief  Return lpgpio mode for a dedicated pin on dedicated port.
  * @note   I/O mode can be Input mode, General purpose output, Alternate function mode or Analog.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll MODER        MODEy         LL_LPGPIO_GetPinMode
  * @param  LPGPIOx LPGPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPGPIO_MODE_INPUT
  *         @arg @ref LL_LPGPIO_MODE_OUTPUT
  */
__STATIC_INLINE uint32_t LL_LPGPIO_GetPinMode(GPIO_TypeDef *LPGPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(LPGPIOx->MODER,
                             (LPGPIO_MODER_MOD0 << (POSITION_VAL(Pin)))) >> (POSITION_VAL(Pin)));
}

/**
  * @}
  */


/** @defgroup LPGPIO_LL_EF_Data_Access Data Access
  * @{
  */

/**
  * @brief  Return full input data register value for a dedicated port.
  * @rmtoll IDR          IDy           LL_LPGPIO_ReadInputPort
  * @param  LPGPIOx LPGPIO Port
  * @retval Input data register value of port
  */
__STATIC_INLINE uint32_t LL_LPGPIO_ReadInputPort(GPIO_TypeDef *LPGPIOx)
{
  return (uint32_t)(READ_REG(LPGPIOx->IDR));
}

/**
  * @brief  Return if input data level for several pins of dedicated port is high or low.
  * @rmtoll IDR          IDy           LL_LPGPIO_IsInputPinSet
  * @param  LPGPIOx LPGPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  *         @arg @ref LL_LPGPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPGPIO_IsInputPinSet(GPIO_TypeDef *LPGPIOx, uint32_t PinMask)
{
  return ((READ_BIT(LPGPIOx->IDR, PinMask) == (PinMask)) ? 1UL : 0UL);
}

/**
  * @brief  Write output data register for the port.
  * @rmtoll ODR          ODy           LL_LPGPIO_WriteOutputPort
  * @param  LPGPIOx LPGPIO Port
  * @param  PortValue Level value for each pin of the port
  * @retval None
  */
__STATIC_INLINE void LL_LPGPIO_WriteOutputPort(GPIO_TypeDef *LPGPIOx, uint32_t PortValue)
{
  WRITE_REG(LPGPIOx->ODR, PortValue);
}

/**
  * @brief  Return full output data register value for a dedicated port.
  * @rmtoll ODR          ODy           LL_LPGPIO_ReadOutputPort
  * @param  LPGPIOx LPGPIO Port
  * @retval Output data register value of port
  */
__STATIC_INLINE uint32_t LL_LPGPIO_ReadOutputPort(GPIO_TypeDef *LPGPIOx)
{
  return (uint32_t)(READ_REG(LPGPIOx->ODR));
}

/**
  * @brief  Return if input data level for several pins of dedicated port is high or low.
  * @rmtoll ODR          ODy           LL_LPGPIO_IsOutputPinSet
  * @param  LPGPIOx LPGPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  *         @arg @ref LL_LPGPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPGPIO_IsOutputPinSet(GPIO_TypeDef *LPGPIOx, uint32_t PinMask)
{
  return ((READ_BIT(LPGPIOx->ODR, PinMask) == (PinMask)) ? 1UL : 0UL);
}

/**
  * @brief  Set several pins to high level on dedicated gpio port.
  * @rmtoll BSRR         BSy           LL_LPGPIO_SetOutputPin
  * @param  LPGPIOx LPGPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  *         @arg @ref LL_LPGPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_LPGPIO_SetOutputPin(GPIO_TypeDef *LPGPIOx, uint32_t PinMask)
{
  WRITE_REG(LPGPIOx->BSRR, PinMask);
}

/**
  * @brief  Set several pins to low level on dedicated gpio port.
  * @rmtoll BRR          BRy           LL_LPGPIO_ResetOutputPin
  * @param  LPGPIOx LPGPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  *         @arg @ref LL_LPGPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_LPGPIO_ResetOutputPin(GPIO_TypeDef *LPGPIOx, uint32_t PinMask)
{
  WRITE_REG(LPGPIOx->BRR, PinMask);
}

/**
  * @brief  Toggle data value for several pin of dedicated port.
  * @rmtoll ODR          ODy           LL_LPGPIO_TogglePin
  * @param  LPGPIOx LPGPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  *         @arg @ref LL_LPGPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_LPGPIO_TogglePin(GPIO_TypeDef *LPGPIOx, uint32_t PinMask)
{
  WRITE_REG(LPGPIOx->ODR, READ_REG(LPGPIOx->ODR) ^ PinMask);
}

/**
  * @}
  */

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup GPIO_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_LPGPIO_DeInit(GPIO_TypeDef *LPGPIOx);
ErrorStatus LL_LPGPIO_Init(GPIO_TypeDef *LPGPIOx, const LL_LPGPIO_InitTypeDef *const LPGPIO_InitStruct);
void        LL_LPGPIO_StructInit(LL_LPGPIO_InitTypeDef *LPGPIO_InitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

#endif /* defined (LPGPIO1) */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_LL_LPGPIO_H */
