/*
  ******************************************************************************
  * @file    HAL_GPIO.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of GPIO HAL module.
  ******************************************************************************
*/
#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__

#include "ACM32Fxx_HAL.h"

/** @defgroup GPIO_pins GPIO pins
  * @{
  */
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */

#define GPIO_PIN_MASK              (0x0000FFFFu) /* PIN mask for assert test */
/**
  * @}
  */


/** @defgroup GPIO_mode GPIO mode
  * @{
  */
#define  GPIO_MODE_INPUT                    (0x00010000u)   /*!< Input Floating Mode                   */
#define  GPIO_MODE_OUTPUT_PP                (0x00010001u)   /*!< Output Push Pull Mode                 */
#define  GPIO_MODE_OUTPUT_OD                (0x00011002u)   /*!< Output Open Drain Mode                */
#define  GPIO_MODE_AF_PP                    (0x00000003u)   /*!< Alternate Function Push Pull Mode     */
#define  GPIO_MODE_AF_OD                    (0x00001004u)   /*!< Alternate Function Open Drain Mode    */
#define  GPIO_MODE_ANALOG                   (0x00000005u)   /*!< Analog Mode                           */
#define  GPIO_MODE_IT_RISING                (0x10010000u)   /*!< External Interrupt Mode with Rising edge trigger detection          */
#define  GPIO_MODE_IT_FALLING               (0x10010001u)   /*!< External Interrupt Mode with Falling edge trigger detection         */
#define  GPIO_MODE_IT_RISING_FALLING        (0x10010002u)   /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
#define  GPIO_MODE_IT_HIGH_LEVEL            (0x10010003u)   /*!< External Interrupt Mode with high level trigger detection  */
#define  GPIO_MODE_IT_LOW_LEVEL             (0x10010004u)   /*!< External Interrupt Mode with low level trigger detection  */

#define  GPIO_MODE_OD_MASK                  (0x00001000u)   /*!< OD Mode Mask                          */
#define  GPIO_MODE_IO_MASK                  (0x00010000u)   /*!< Use GPIO Function Mask                */
#define  GPIO_MODE_IT_MASK                  (0x10000000u)   /*!< GPIO interrupt Mask                */
/**
  * @}
  */


/** @defgroup GPIO_pull GPIO pull
  * @{
  */
#define  GPIO_NOPULL        (0x00000000u)   /*!< No Pull-up or Pull-down activation  */
#define  GPIO_PULLUP        (0x00000001u)   /*!< Pull-up activation                  */
#define  GPIO_PULLDOWN      (0x00000002u)   /*!< Pull-down activation                */
/**
  * @}
  */


/** @defgroup GPIOEx_function_selection GPIO pull
  * @{
  */
#define  GPIO_FUNCTION_0        (0x00000000u)
#define  GPIO_FUNCTION_1        (0x00000001u)
#define  GPIO_FUNCTION_2        (0x00000002u)
#define  GPIO_FUNCTION_3        (0x00000003u)
#define  GPIO_FUNCTION_4        (0x00000004u)
#define  GPIO_FUNCTION_5        (0x00000005u)
#define  GPIO_FUNCTION_6        (0x00000006u)
#define  GPIO_FUNCTION_7        (0x00000007u)
#define  GPIO_FUNCTION_8        (0x00000008u)
#define  GPIO_FUNCTION_9        (0x00000009u)
/**
  * @}
  */



/** @defgroup GPIOx Index
  * @{
  */
typedef enum
{
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
}enum_GPIOx_t;
/**
  * @}
  */


/** @defgroup GPIO Bit SET and Bit RESET enumeration
  * @{
  */
typedef enum
{
  GPIO_PIN_CLEAR = 0u,
  GPIO_PIN_SET   = 1u,
}enum_PinState_t;
/**
  * @}
  */



/*
 * @brief   GPIO Init structure definition
 */
typedef struct
{
    uint32_t Pin;        /*!< Specifies the GPIO pins to be configured.
                              This parameter can be any value of @ref GPIO_pins */

    uint32_t Mode;       /*!< Specifies the operating mode for the selected pins.
                              This parameter can be a value of @ref GPIO_mode */

    uint32_t Pull;       /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                              This parameter can be a value of @ref GPIO_pull */

    uint32_t Alternate;  /*!< Peripheral to be connected to the selected pins
                               This parameter can be a value of @ref GPIOEx_function_selection */
} GPIO_InitTypeDef;


/** @defgroup  GPIO Private Macros
  * @{
  */
#define IS_GPIO_ALL_INSTANCE(INSTANCE) (((INSTANCE) == GPIOA) || \
                                        ((INSTANCE) == GPIOB) || \
                                        ((INSTANCE) == GPIOC) || \
                                        ((INSTANCE) == GPIOD) )

#define IS_GPIO_PIN(__PIN__)           ((((uint32_t)(__PIN__) &  GPIO_PIN_MASK) != 0x00u) &&\
                                        (((uint32_t)(__PIN__) & ~GPIO_PIN_MASK) == 0x00u))


#define IS_GPIO_MODE(__MODE__)         (((__MODE__) == GPIO_MODE_INPUT)              ||\
                                        ((__MODE__) == GPIO_MODE_OUTPUT_PP)          ||\
                                        ((__MODE__) == GPIO_MODE_OUTPUT_OD)          ||\
                                        ((__MODE__) == GPIO_MODE_AF_PP)              ||\
                                        ((__MODE__) == GPIO_MODE_AF_OD)              ||\
                                        ((__MODE__) == GPIO_MODE_IT_RISING)          ||\
                                        ((__MODE__) == GPIO_MODE_IT_FALLING)         ||\
                                        ((__MODE__) == GPIO_MODE_IT_RISING_FALLING)  ||\
                                        ((__MODE__) == GPIO_MODE_IT_HIGH_LEVEL)      ||\
                                        ((__MODE__) == GPIO_MODE_IT_LOW_LEVEL)       ||\
                                        ((__MODE__) == GPIO_MODE_ANALOG))




#define IS_GPIO_PULL(__PULL__)         (((__PULL__) == GPIO_NOPULL)   ||\
                                        ((__PULL__) == GPIO_PULLUP)   ||\
                                        ((__PULL__) == GPIO_PULLDOWN))

#define IS_GPIO_PIN_ACTION(ACTION)     (((ACTION) == GPIO_PIN_CLEAR) || ((ACTION) == GPIO_PIN_SET))

#define IS_GPIO_FUNCTION(__FUNCTION__)    (((__FUNCTION__) == GPIO_FUNCTION_0) ||\
                                           ((__FUNCTION__) == GPIO_FUNCTION_1) ||\
                                           ((__FUNCTION__) == GPIO_FUNCTION_2) ||\
                                           ((__FUNCTION__) == GPIO_FUNCTION_3) ||\
                                           ((__FUNCTION__) == GPIO_FUNCTION_4) ||\
                                           ((__FUNCTION__) == GPIO_FUNCTION_5) ||\
                                           ((__FUNCTION__) == GPIO_FUNCTION_6) ||\
                                           ((__FUNCTION__) == GPIO_FUNCTION_7) ||\
                                           ((__FUNCTION__) == GPIO_FUNCTION_8) ||\
                                           ((__FUNCTION__) == GPIO_FUNCTION_9))

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/* HAL_GPIO_IRQHandler */
void HAL_GPIO_IRQHandler(enum_GPIOx_t fe_GPIO, uint32_t fu32_GPIO_Pin);

/* HAL_GPIO_Init */
void HAL_GPIO_Init(enum_GPIOx_t fe_GPIO, GPIO_InitTypeDef *GPIO_Init);

/* HAL_GPIO_DeInit */
void HAL_GPIO_DeInit(enum_GPIOx_t fe_GPIO, uint32_t fu32_Pin);

/* HAL_GPIO_AnalogEnable */
void HAL_GPIO_AnalogEnable(enum_GPIOx_t fe_GPIO, uint32_t fu32_Pin);

/* HAL_GPIO_WritePin */
void HAL_GPIO_WritePin(enum_GPIOx_t fe_GPIO, uint32_t fu32_GPIO_Pin, enum_PinState_t fe_PinState);

/* HAL_GPIO_ReadPin */
enum_PinState_t HAL_GPIO_ReadPin(enum_GPIOx_t fe_GPIO, uint32_t fu32_GPIO_Pin);

#endif
