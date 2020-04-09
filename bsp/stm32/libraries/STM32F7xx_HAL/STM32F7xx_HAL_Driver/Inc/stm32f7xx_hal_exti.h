/**
  ******************************************************************************
  * @file    stm32f7xx_hal_exti.h
  * @author  MCD Application Team
  * @brief   Header file of EXTI HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F7xx_HAL_EXTI_H
#define __STM32F7xx_HAL_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal_def.h"

/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */

/** @defgroup EXTI EXTI
  * @brief EXTI HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Types EXTI Exported Types
  * @{
  */
typedef enum
{
  HAL_EXTI_COMMON_CB_ID          = 0x00U,
  HAL_EXTI_RISING_CB_ID          = 0x01U,
  HAL_EXTI_FALLING_CB_ID         = 0x02U,
} EXTI_CallbackIDTypeDef;

/**
  * @brief  EXTI Handle structure definition
  */
typedef struct
{
  uint32_t Line;                    /*!<  Exti line number */
  void (* PendingCallback)(void);   /*!<  Exti pending callback */
} EXTI_HandleTypeDef;

/**
  * @brief  EXTI Configuration structure definition
  */
typedef struct
{
  uint32_t Line;      /*!< The Exti line to be configured. This parameter
                           can be a value of @ref EXTI_Line */
  uint32_t Mode;      /*!< The Exit Mode to be configured for a core.
                           This parameter can be a combination of @ref EXTI_Mode */
  uint32_t Trigger;   /*!< The Exti Trigger to be configured. This parameter
                           can be a value of @ref EXTI_Trigger */
} EXTI_ConfigTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup EXTI_Exported_Constants EXTI Exported Constants
  * @{
  */

/** @defgroup EXTI_Line  EXTI Line
  * @{
  */
#define EXTI_LINE_0                          EXTI_IMR_IM0     /*!< External interrupt line 0 */
#define EXTI_LINE_1                          EXTI_IMR_IM1     /*!< External interrupt line 1 */
#define EXTI_LINE_2                          EXTI_IMR_IM2     /*!< External interrupt line 2 */
#define EXTI_LINE_3                          EXTI_IMR_IM3     /*!< External interrupt line 3 */
#define EXTI_LINE_4                          EXTI_IMR_IM4     /*!< External interrupt line 4 */
#define EXTI_LINE_5                          EXTI_IMR_IM5     /*!< External interrupt line 5 */
#define EXTI_LINE_6                          EXTI_IMR_IM6     /*!< External interrupt line 6 */
#define EXTI_LINE_7                          EXTI_IMR_IM7     /*!< External interrupt line 7 */
#define EXTI_LINE_8                          EXTI_IMR_IM8     /*!< External interrupt line 8 */
#define EXTI_LINE_9                          EXTI_IMR_IM9     /*!< External interrupt line 9 */
#define EXTI_LINE_10                         EXTI_IMR_IM10    /*!< External interrupt line 10 */
#define EXTI_LINE_11                         EXTI_IMR_IM11    /*!< External interrupt line 11 */
#define EXTI_LINE_12                         EXTI_IMR_IM12    /*!< External interrupt line 12 */
#define EXTI_LINE_13                         EXTI_IMR_IM13    /*!< External interrupt line 13 */
#define EXTI_LINE_14                         EXTI_IMR_IM14    /*!< External interrupt line 14 */
#define EXTI_LINE_15                         EXTI_IMR_IM15    /*!< External interrupt line 15 */
#if defined(EXTI_IMR_IM16)
#define EXTI_LINE_16                         EXTI_IMR_IM16    /*!< External interrupt line 16 Connected to the PVD Output */
#endif /* EXTI_IMR_IM16 */
#if defined(EXTI_IMR_IM17)
#define EXTI_LINE_17                         EXTI_IMR_IM17    /*!< External interrupt line 17 Connected to the RTC Alarm event */
#endif /* EXTI_IMR_IM17 */
#if defined(EXTI_IMR_IM18)
#define EXTI_LINE_18                         EXTI_IMR_IM18    /*!< External interrupt line 18 Connected to the USB OTG FS Wakeup from suspend event */
#endif /* EXTI_IMR_IM18 */
#if defined(EXTI_IMR_IM19)
#define EXTI_LINE_19                         EXTI_IMR_IM19    /*!< External interrupt line 19 Connected to the Ethernet Wakeup event */
#endif /* EXTI_IMR_IM19 */
#if defined(EXTI_IMR_IM20)
#define EXTI_LINE_20                         EXTI_IMR_IM20    /*!< External interrupt line 20 Connected to the USB OTG HS (configured in FS) Wakeup event  */
#endif /* EXTI_IMR_IM20 */
#if defined(EXTI_IMR_IM21)
#define EXTI_LINE_21                         EXTI_IMR_IM21    /*!< External interrupt line 21 Connected to the RTC Tamper and Time Stamp events */ 
#endif /* EXTI_IMR_IM21 */
#if defined(EXTI_IMR_IM22)
#define EXTI_LINE_22                         EXTI_IMR_IM22    /*!< External interrupt line 22 Connected to the RTC Wakeup event */
#endif /* EXTI_IMR_IM22 */
#if defined(EXTI_IMR_IM23)
#define EXTI_LINE_23                         EXTI_IMR_IM23    /*!< External interrupt line 23 Connected to the LPTIM Wakeup event */
#endif /* EXTI_IMR_IM23 */
#if defined(EXTI_IMR_IM24)
#define EXTI_LINE_24                         EXTI_IMR_IM24    /*!< External interrupt line 24 Connected to the MDIO Slave global Interrupt Wakeup event */
#endif /* EXTI_IMR_IM24 */
/**
  * @}
  */

/** @defgroup EXTI_Mode  EXTI Mode
  * @{
  */
#define EXTI_MODE_NONE                      0x00000000u
#define EXTI_MODE_INTERRUPT                 0x00000001u
#define EXTI_MODE_EVENT                     0x00000002u
/**
  * @}
  */

/** @defgroup EXTI_Trigger  EXTI Trigger
  * @{
  */
#define EXTI_TRIGGER_NONE                   0x00000000u
#define EXTI_TRIGGER_RISING                 0x00000001u
#define EXTI_TRIGGER_FALLING                0x00000002u
#define EXTI_TRIGGER_RISING_FALLING         (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Macros EXTI Exported Macros
  * @{
  */

/**
  * @}
  */

/* Private constants --------------------------------------------------------*/
/** @defgroup EXTI_Private_Constants EXTI Private Constants
  * @{
  */
/**
  * @brief  EXTI Mask for interrupt & event mode
  */
#define EXTI_MODE_MASK                      (EXTI_MODE_EVENT | EXTI_MODE_INTERRUPT)

/**
  * @brief  EXTI Mask for trigger possibilities
  */
#define EXTI_TRIGGER_MASK                   (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING | EXTI_TRIGGER_RISING_FALLING)

/**
  * @brief  EXTI Line number
  */
#define EXTI_LINE_NB                        25u

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup EXTI_Private_Macros EXTI Private Macros
  * @{
  */
#define IS_EXTI_LINE(__LINE__)          ((((__LINE__) & ~EXTI_IMR_IM) == 0x00U) && (__LINE__))

#define IS_EXTI_MODE(__LINE__)          ((((__LINE__) & ~EXTI_MODE_MASK) == 0x00U))

#define IS_EXTI_TRIGGER(__LINE__)       (((__LINE__)  & ~EXTI_TRIGGER_MASK) == 0x00U)

#define IS_EXTI_PENDING_EDGE(__LINE__)  (((__LINE__) == EXTI_TRIGGER_FALLING) || \
                                         ((__LINE__) == EXTI_TRIGGER_RISING)  || \
                                         ((__LINE__) == EXTI_TRIGGER_RISING_FALLING))

#define IS_EXTI_GPIO_PIN(__PIN__)       ((__PIN__) < 16U)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup EXTI_Exported_Functions EXTI Exported Functions
  * @brief    EXTI Exported Functions
  * @{
  */

/** @defgroup EXTI_Exported_Functions_Group1 Configuration functions
  * @brief    Configuration functions
  * @{
  */
/* Configuration functions ****************************************************/
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(EXTI_HandleTypeDef *hexti);
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID, void (*pPendingCbfn)(void));
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine);
/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions_Group2 IO operation functions
  * @brief    IO operation functions
  * @{
  */
/* IO operation functions *****************************************************/
void HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti);
uint32_t HAL_EXTI_GetPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void HAL_EXTI_GenerateSWI(EXTI_HandleTypeDef *hexti);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7xx_HAL_EXTI_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
