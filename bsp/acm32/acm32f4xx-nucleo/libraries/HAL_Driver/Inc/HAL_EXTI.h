/*
  ******************************************************************************
  * @file    HAL_EXTI.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of EXTI HAL module.
  ******************************************************************************
*/
#ifndef __HAL_EXTI_H__
#define __HAL_EXTI_H__

#include "ACM32Fxx_HAL.h"

/** @defgroup EXTI_Line  EXTI Line
  * @{
  */
#define EXTI_LINE_0                (0x000001)
#define EXTI_LINE_1                (0x000002)
#define EXTI_LINE_2                (0x000004)
#define EXTI_LINE_3                (0x000008)
#define EXTI_LINE_4                (0x000010)
#define EXTI_LINE_5                (0x000020)
#define EXTI_LINE_6                (0x000040)
#define EXTI_LINE_7                (0x000080)
#define EXTI_LINE_8                (0x000100)
#define EXTI_LINE_9                (0x000200)
#define EXTI_LINE_10               (0x000300)
#define EXTI_LINE_11               (0x000400)
#define EXTI_LINE_12               (0x001000)
#define EXTI_LINE_13               (0x002000)
#define EXTI_LINE_14               (0x004000)
#define EXTI_LINE_15               (0x008000)
#define EXTI_LINE_16               (0x010000)
#define EXTI_LINE_17               (0x020000)
#define EXTI_LINE_18               (0x040000)
#define EXTI_LINE_19               (0x080000)
#define EXTI_LINE_20               (0x100000)
#define EXTI_LINE_21               (0x200000)
#define EXTI_LINE_22               (0x400000)
#define EXTI_LINE_23               (0x800000)
#define EXTI_LINE_MASK             (0xFFFFFFU)
/**
  * @}
  */


/** @defgroup EXTI_Mode  EXTI Mode
  * @{
  */
#define EXTI_MODE_INTERRUPT         (0x00000001)
#define EXTI_MODE_EVENT             (0x00000002)
/**
  * @}
  */


/** @defgroup EXTI_Trigger  EXTI Trigger
  * @{
  */
#define EXTI_TRIGGER_RISING                 (0x00000001)
#define EXTI_TRIGGER_FALLING                (0x00000002)
#define EXTI_TRIGGER_RISING_FALLING         (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING)
/**
  * @}
  */


/** @defgroup EXTI_GPIOSel  EXTI GPIOSel
  * @brief
  * @{
  */
#define EXTI_GPIOA                          0x00000000u
#define EXTI_GPIOB                          0x00000001u
#define EXTI_GPIOC                          0x00000002u
#define EXTI_GPIOD                          0x00000003u
#define EXTI_GPIOE                          0x00000004u
#define EXTI_GPIOF                          0x00000005u
/**
  * @}
  */


/**
  * @brief  EXTI Configuration structure definition
  */
typedef struct
{
    uint32_t u32_Line;        /*!< The Exti line to be configured. This parameter
                                   can be a value of @ref EXTI_Line */
    uint32_t u32_Mode;        /*!< The Exit Mode to be configured for a core.
                                   This parameter can be a combination of @ref EXTI_Mode */
    uint32_t u32_Trigger;     /*!< The Exti Trigger to be configured. This parameter
                                   can be a value of @ref EXTI_Trigger */
    uint32_t u32_GPIOSel;     /*!< The Exti GPIO multiplexer selection to be configured.
                                   This parameter is only possible for line 0 to 15. It
                                   can be a value of @ref EXTI_GPIOSel */
}EXTI_HandleTypeDef;


/** @defgroup  EXTI Private Macros
  * @{
  */
#define IS_EXTI_ALL_LINE(LINE)    ( (LINE) | (EXTI_LINE_MASK) )

#define IS_EXTI_MODE(__MODE__)     (((__MODE__) == EXTI_MODE_INTERRUPT) || \
                                    ((__MODE__) == EXTI_MODE_EVENT))

#define IS_EXTI_TRIGGER(__TRIGGER__)     (((__TRIGGER__) == EXTI_TRIGGER_RISING)  || \
                                          ((__TRIGGER__) == EXTI_TRIGGER_FALLING) || \
                                          ((__TRIGGER__) == EXTI_TRIGGER_RISING_FALLING))

#define IS_EXTI_GPIOSEL(__GPIOSEL__)     (((__GPIOSEL__) == EXTI_GPIOA) || \
                                          ((__GPIOSEL__) == EXTI_GPIOB) || \
                                          ((__GPIOSEL__) == EXTI_GPIOC) || \
                                          ((__GPIOSEL__) == EXTI_GPIOD) || \
                                          ((__GPIOSEL__) == EXTI_GPIOE) || \
                                          ((__GPIOSEL__) == EXTI_GPIOF))
/**
  * @}
  */

/** @brief  __HAL_EXTI_LINE_IT_ENABLE
  * @param  __LINE__: EXTI line.
  *         This parameter can be a value of @ref EXTI_Line
  */
#define __HAL_EXTI_LINE_IT_ENABLE(__LINE__)    (EXTI->IENR |= (__LINE__))

/** @brief  __HAL_EXTI_LINE_IT_DISABLE
  * @param  __LINE__: EXTI line.
  *         This parameter can be a value of @ref EXTI_Line
  */
#define __HAL_EXTI_LINE_IT_DISABLE(__LINE__)    (EXTI->IENR &= ~(__LINE__))

/** @brief  __HAL_EXTI_LINE_EVENT_ENABLE
  * @param  __LINE__: EXTI line.
  *         This parameter can be a value of @ref EXTI_Line
  */
#define __HAL_EXTI_LINE_EVENT_ENABLE(__LINE__)    (EXTI->EENR |= (__LINE__))

/** @brief  __HAL_EXTI_LINE_EVENT_DISABLE
  * @param  __LINE__: EXTI line.
  *         This parameter can be a value of @ref EXTI_Line
  */
#define __HAL_EXTI_LINE_EVENT_DISABLE(__LINE__)    (EXTI->EENR &= ~(__LINE__))


/* HAL_EXTI_IRQHandler */
void HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *huart);

/* HAL_EXTI_SetConfigLine */
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti);

/* HAL_EXTI_SoftTrigger */
void HAL_EXTI_SoftTrigger(EXTI_HandleTypeDef *hexti);

/* HAL_EXTI_GetPending */
bool HAL_EXTI_GetPending(EXTI_HandleTypeDef *hexti);

/* HAL_EXTI_ClearPending */
void HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti);

/* HAL_EXTI_ClearAllPending */
void HAL_EXTI_ClearAllPending(void);

#endif

