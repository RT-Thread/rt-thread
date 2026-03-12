/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g43x_gpio.h
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32G43X_GPIO_H__
#define __N32G43X_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g43x.h"

/** @addtogroup N32G43x_StdPeriph_Driver
 * @{
 */

/** @addtogroup GPIO
 * @{
 */

/** @addtogroup GPIO_Exported_Types
 * @{
 */

#define IS_GPIO_ALL_PERIPH(PERIPH)                                                                                     \
    (((PERIPH) == GPIOA) || ((PERIPH) == GPIOB) || ((PERIPH) == GPIOC) || ((PERIPH) == GPIOD))


#define GPIO_GET_INDEX(PERIPH)    (((PERIPH) == (GPIOA))? 0 :\
                                      ((PERIPH) == (GPIOB))? 1 :\
                                      ((PERIPH) == (GPIOC))? 2 :3)
#define GPIO_GET_PERIPH(INDEX) (((INDEX)==((uint8_t)0x00))? GPIOA :\
                                ((INDEX)==((uint8_t)0x01))? GPIOB :\
                                ((INDEX)==((uint8_t)0x02))? GPIOC : GPIOD )


/**
 * @brief  Output Maximum frequency selection
 */

typedef enum
{
    GPIO_Slew_Rate_High = 0,
    GPIO_Slew_Rate_Low
} GPIO_SpeedType;
#define IS_GPIO_SLEW_RATE(_RATE_)                           \
    (((_RATE_) == GPIO_Slew_Rate_High) || ((_RATE_) == GPIO_Slew_Rate_Low))

/**
 * @brief   driver strength config
 */

typedef enum
{
    GPIO_DC_2mA = 0x00,
    GPIO_DC_4mA = 0x10,
    GPIO_DC_8mA = 0x01,
    GPIO_DC_12mA= 0x11
}GPIO_CurrentType;

#define IS_GPIO_CURRENT(CURRENT)  \
        (((CURRENT) == GPIO_DC_2mA) ||((CURRENT) == GPIO_DC_4mA)   \
        || ((CURRENT) == GPIO_DC_8mA)||((CURRENT) == GPIO_DC_12mA))
/**
 * @brief  Configuration Mode enumeration
 */


/** @brief GPIO_mode_define Mode definition
  * @brief GPIO Configuration Mode
  *    Values convention: 0xW0yz00YZ
  *           - W  : GPIO mode or EXTI Mode
  *           - y  : External IT or Event trigger detection
  *           - z  : IO configuration on External IT or Event
  *           - Y  : Output type (Push Pull or Open Drain)
  *           - Z  : IO Direction mode (Input, Output, Alternate or Analog)
  * @{
  */

typedef enum
{
    GPIO_Mode_Input =  0x00000000,   /*!< Input Floating Mode                   */
    GPIO_Mode_Out_PP = 0x00000001,   /*!< Output Push Pull Mode                 */
    GPIO_Mode_Out_OD = 0x00000011,   /*!< Output Open Drain Mode                */
    GPIO_Mode_AF_PP =  0x00000002,   /*!< Alternate Function Push Pull Mode     */
    GPIO_Mode_AF_OD =  0x00000012,   /*!< Alternate Function Open Drain Mode    */

    GPIO_Mode_Analog = 0x00000003,   /*!< Analog Mode  */

    GPIO_Mode_IT_Rising = 0x10110000,   /*!< External Interrupt Mode with Rising edge trigger detection          */
    GPIO_Mode_IT_Falling = 0x10210000,   /*!< External Interrupt Mode with Falling edge trigger detection         */
    GPIO_Mode_IT_Rising_Falling = 0x10310000,   /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */

    GPIO_Mode_EVT_Rising = 0x10120000,   /*!< External Event Mode with Rising edge trigger detection               */
    GPIO_Mode_EVT_Falling = 0x10220000,   /*!< External Event Mode with Falling edge trigger detection              */
    GPIO_Mode_EVT_Rising_Falling = 0x10320000
}GPIO_ModeType;



/**
  * @}
  */
#define IS_GPIO_MODE(__MODE__) (((__MODE__) == GPIO_Mode_Input)              ||\
                                ((__MODE__) == GPIO_Mode_Out_PP)             ||\
                                ((__MODE__) == GPIO_Mode_Out_OD)             ||\
                                ((__MODE__) == GPIO_Mode_AF_PP)              ||\
                                ((__MODE__) == GPIO_Mode_AF_OD)              ||\
                                ((__MODE__) == GPIO_Mode_IT_Rising)          ||\
                                ((__MODE__) == GPIO_Mode_IT_Falling)         ||\
                                ((__MODE__) == GPIO_Mode_IT_Rising_Falling)  ||\
                                ((__MODE__) == GPIO_Mode_EVT_Rising)         ||\
                                ((__MODE__) == GPIO_Mode_EVT_Falling)        ||\
                                ((__MODE__) == GPIO_Mode_EVT_Rising_Falling) ||\
                                ((__MODE__) == GPIO_Mode_Analog))

/**
  * @}
  */

/**
  * @}
  */

/** @brief GPIO_pull_define Pull definition
   * @brief GPIO Pull-Up or Pull-Down Activation
   * @{
   */

typedef enum
{
    GPIO_No_Pull = 0x00000000,   /*!< No Pull-up or Pull-down activation  */
    GPIO_Pull_Up = 0x00000001,  /*!< Pull-up activation                  */
    GPIO_Pull_Down = 0x00000002   /*!< Pull-down activation                */
}GPIO_PuPdType;
/**
  * @}
  */

#define IS_GPIO_PULL(__PULL__) (((__PULL__) == GPIO_No_Pull) || ((__PULL__) == GPIO_Pull_Up) || \
                                ((__PULL__) == GPIO_Pull_Down))
/**
  * @}
  */

/**
 * @brief  GPIO Init structure definition
 */

typedef struct
{
    uint16_t Pin; /*!< Specifies the GPIO pins to be configured.
                            This parameter can be any value of @ref GPIO_pins_define */

    GPIO_CurrentType GPIO_Current; /*!<Driving current of the select pins>.
                                        This paramter can be a value of @ref GPIO_CurrentType*/

    GPIO_SpeedType GPIO_Slew_Rate; /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIO_SpeedType */

    GPIO_PuPdType GPIO_Pull;      /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                           This parameter can be a value of @ref GPIO_pull_define */

    GPIO_ModeType GPIO_Mode; /*!< Specifies the operating mode for the selected pins.
                                     This parameter can be a value of @ref GPIO_ModeType */

    uint32_t GPIO_Alternate;  /*!< Peripheral to be connected to the selected pins
                            This parameter can be a value of @ref GPIOEx_Alternate_function_selection */
} GPIO_InitType;

/**
 * @brief  Bit_SET and Bit_RESET enumeration
 */

typedef enum
{
    Bit_RESET = 0,
    Bit_SET
} Bit_OperateType;

#define IS_GPIO_BIT_OPERATE(OPERATE) (((OPERATE) == Bit_RESET) || ((OPERATE) == Bit_SET))

/**
 * @}
 */




/** @addtogroup GPIO_Exported_Constants
 * @{
 */

/** @addtogroup GPIO_pins_define
 * @{
 */

#define GPIO_PIN_0   ((uint16_t)0x0001) /*!< Pin 0 selected */
#define GPIO_PIN_1   ((uint16_t)0x0002) /*!< Pin 1 selected */
#define GPIO_PIN_2   ((uint16_t)0x0004) /*!< Pin 2 selected */
#define GPIO_PIN_3   ((uint16_t)0x0008) /*!< Pin 3 selected */
#define GPIO_PIN_4   ((uint16_t)0x0010) /*!< Pin 4 selected */
#define GPIO_PIN_5   ((uint16_t)0x0020) /*!< Pin 5 selected */
#define GPIO_PIN_6   ((uint16_t)0x0040) /*!< Pin 6 selected */
#define GPIO_PIN_7   ((uint16_t)0x0080) /*!< Pin 7 selected */
#define GPIO_PIN_8   ((uint16_t)0x0100) /*!< Pin 8 selected */
#define GPIO_PIN_9   ((uint16_t)0x0200) /*!< Pin 9 selected */
#define GPIO_PIN_10  ((uint16_t)0x0400) /*!< Pin 10 selected */
#define GPIO_PIN_11  ((uint16_t)0x0800) /*!< Pin 11 selected */
#define GPIO_PIN_12  ((uint16_t)0x1000) /*!< Pin 12 selected */
#define GPIO_PIN_13  ((uint16_t)0x2000) /*!< Pin 13 selected */
#define GPIO_PIN_14  ((uint16_t)0x4000) /*!< Pin 14 selected */
#define GPIO_PIN_15  ((uint16_t)0x8000) /*!< Pin 15 selected */
#define GPIO_PIN_ALL ((uint16_t)0xFFFF) /*!< All pins selected */

#define GPIOA_PIN_AVAILABLE  ((uint16_t)0xFFFF)
#define GPIOB_PIN_AVAILABLE  ((uint16_t)0xFFFF)
#define GPIOC_PIN_AVAILABLE  ((uint16_t)0xFFFF)
#define GPIOD_PIN_AVAILABLE  ((uint16_t)0xFFFF)

#define IS_GPIO_PIN(PIN) ((((PIN) & (uint16_t)0x00) == 0x00) && ((PIN) != (uint16_t)0x00))

#define IS_GET_GPIO_PIN(PIN)                                                                                           \
    (((PIN) == GPIO_PIN_0) || ((PIN) == GPIO_PIN_1) || ((PIN) == GPIO_PIN_2) || ((PIN) == GPIO_PIN_3)                  \
     || ((PIN) == GPIO_PIN_4) || ((PIN) == GPIO_PIN_5) || ((PIN) == GPIO_PIN_6) || ((PIN) == GPIO_PIN_7)               \
     || ((PIN) == GPIO_PIN_8) || ((PIN) == GPIO_PIN_9) || ((PIN) == GPIO_PIN_10) || ((PIN) == GPIO_PIN_11)             \
     || ((PIN) == GPIO_PIN_12) || ((PIN) == GPIO_PIN_13) || ((PIN) == GPIO_PIN_14) || ((PIN) == GPIO_PIN_15))


#define IS_GPIO_PIN_AVAILABLE(__INSTANCE__,__PIN__)  \
           ((((__INSTANCE__) == GPIOA) && (((__PIN__) & (GPIOA_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOA_PIN_AVAILABLE)) == (GPIOA_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOB) && (((__PIN__) & (GPIOB_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOB_PIN_AVAILABLE)) == (GPIOB_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOC) && (((__PIN__) & (GPIOC_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOC_PIN_AVAILABLE)) == (GPIOC_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOD) && (((__PIN__) & (GPIOD_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOD_PIN_AVAILABLE)) == (GPIOD_PIN_AVAILABLE))))





/**
 * @}
 */




/** @addtogroup GPIO_Port_Sources
 * @{
 */

#define GPIOA_PORT_SOURCE ((uint8_t)0x00)
#define GPIOB_PORT_SOURCE ((uint8_t)0x01)
#define GPIOC_PORT_SOURCE ((uint8_t)0x02)
#define GPIOD_PORT_SOURCE ((uint8_t)0x03)

#define IS_GPIO_REMAP_PORT_SOURCE(PORTSOURCE)                                                                       \
    (((PORTSOURCE) == GPIOA_PORT_SOURCE) || ((PORTSOURCE) == GPIOB_PORT_SOURCE) || ((PORTSOURCE) == GPIOC_PORT_SOURCE) \
     || ((PORTSOURCE) == GPIOD_PORT_SOURCE))


#define IS_GPIO_EVENTOUT_PORT_SOURCE(PORTSOURCE)                                                                       \
    (((PORTSOURCE) == GPIOA_PORT_SOURCE) || ((PORTSOURCE) == GPIOB_PORT_SOURCE) || ((PORTSOURCE) == GPIOC_PORT_SOURCE) \
     || ((PORTSOURCE) == GPIOD_PORT_SOURCE))

#define IS_GPIO_EXTI_PORT_SOURCE(PORTSOURCE)                                                                           \
    (((PORTSOURCE) == GPIOA_PORT_SOURCE) || ((PORTSOURCE) == GPIOB_PORT_SOURCE) || ((PORTSOURCE) == GPIOC_PORT_SOURCE) \
     || ((PORTSOURCE) == GPIOD_PORT_SOURCE))

/**
 * @}
 */

/** @addtogroup GPIO_Pin_sources
 * @{
 */

#define GPIO_PIN_SOURCE0  ((uint8_t)0x00)
#define GPIO_PIN_SOURCE1  ((uint8_t)0x01)
#define GPIO_PIN_SOURCE2  ((uint8_t)0x02)
#define GPIO_PIN_SOURCE3  ((uint8_t)0x03)
#define GPIO_PIN_SOURCE4  ((uint8_t)0x04)
#define GPIO_PIN_SOURCE5  ((uint8_t)0x05)
#define GPIO_PIN_SOURCE6  ((uint8_t)0x06)
#define GPIO_PIN_SOURCE7  ((uint8_t)0x07)
#define GPIO_PIN_SOURCE8  ((uint8_t)0x08)
#define GPIO_PIN_SOURCE9  ((uint8_t)0x09)
#define GPIO_PIN_SOURCE10 ((uint8_t)0x0A)
#define GPIO_PIN_SOURCE11 ((uint8_t)0x0B)
#define GPIO_PIN_SOURCE12 ((uint8_t)0x0C)
#define GPIO_PIN_SOURCE13 ((uint8_t)0x0D)
#define GPIO_PIN_SOURCE14 ((uint8_t)0x0E)
#define GPIO_PIN_SOURCE15 ((uint8_t)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE)                                                                                  \
    (((PINSOURCE) == GPIO_PIN_SOURCE0) || ((PINSOURCE) == GPIO_PIN_SOURCE1) || ((PINSOURCE) == GPIO_PIN_SOURCE2)       \
     || ((PINSOURCE) == GPIO_PIN_SOURCE3) || ((PINSOURCE) == GPIO_PIN_SOURCE4) || ((PINSOURCE) == GPIO_PIN_SOURCE5)    \
     || ((PINSOURCE) == GPIO_PIN_SOURCE6) || ((PINSOURCE) == GPIO_PIN_SOURCE7) || ((PINSOURCE) == GPIO_PIN_SOURCE8)    \
     || ((PINSOURCE) == GPIO_PIN_SOURCE9) || ((PINSOURCE) == GPIO_PIN_SOURCE10) || ((PINSOURCE) == GPIO_PIN_SOURCE11)  \
     || ((PINSOURCE) == GPIO_PIN_SOURCE12) || ((PINSOURCE) == GPIO_PIN_SOURCE13) || ((PINSOURCE) == GPIO_PIN_SOURCE14) \
     || ((PINSOURCE) == GPIO_PIN_SOURCE15))

/**
 * @}
 */



/** @defgroup GPIOx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 */
#define GPIO_AF0_SW_JTAG        ((uint8_t)0x00)  /* SPI1 Alternate Function mapping */
#define GPIO_AF0_SPI1           ((uint8_t)0x00)  /* SPI1 Alternate Function mapping */
#define GPIO_AF0_LPTIM          ((uint8_t)0x00)  /* LPTIM Alternate Function mapping    */
#define GPIO_AF0_SPI2           ((uint8_t)0x00)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_TIM8           ((uint8_t)0x00)  /* TIM8 Alternate Function mapping      */
#define GPIO_AF0_USART1         ((uint8_t)0x00)  /* USART1 Alternate Function mapping    */
#define GPIO_AF0_USART3         ((uint8_t)0x00)  /* USART3 Alternate Function mapping    */
#define GPIO_AF0_LPUART         ((uint8_t)0x00)  /* LPUART Alternate Function mapping   */
#define GPIO_AF0_USART2         ((uint8_t)0x00)  /* USART2 Alternate Function mapping     */

/**
 *
 */

/*
 * Alternate function AF1
 */
#define GPIO_AF1_TIM5          ((uint8_t)0x01)  /* TIM5 Alternate Function mapping     */
#define GPIO_AF1_USART1        ((uint8_t)0x01)  /* USART1 Alternate Function mapping     */
#define GPIO_AF1_I2C2          ((uint8_t)0x01)  /* I2C2 Alternate Function mapping    */
#define GPIO_AF1_CAN           ((uint8_t)0x01)  /* CAN Alternate Function mapping      */
#define GPIO_AF1_SPI2          ((uint8_t)0x01)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF1_TIM9          ((uint8_t)0x01)  /* TIM9 Alternate Function mapping     */
#define GPIO_AF1_SPI1          ((uint8_t)0x01)  /* SPI1 Alternate Function mapping    */
#define GPIO_AF1_I2C1          ((uint8_t)0x01)  /* I2C1 Alternate Function mapping      */
#define GPIO_AF1               ((uint8_t)0x01)  /* test Alternate Function mapping      */
/**
 *
 */

/*
 * Alternate function AF2
 */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF2_TIM3          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping     */
#define GPIO_AF2_TIM1          ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_LPTIM         ((uint8_t)0x02)  /* LPTIM Alternate Function mapping   */
#define GPIO_AF2_TIM4          ((uint8_t)0x02)  /* TIM4 Alternate Function mapping  */
#define GPIO_AF2_LPUART        ((uint8_t)0x02)  /* LPUART Alternate Function mapping      */
/**
 *
 */

/*
 * Alternate function AF3
 */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03)  /* EVENTOUT Alternate Function mapping */

/**
 *
 */

/*
 * Alternate function AF4
 */
#define GPIO_AF4_USART2          ((uint8_t)0x04)  /* USART2 Alternate Function mapping  */
#define GPIO_AF4_LPUART          ((uint8_t)0x04)  /* LPUART Alternate Function mapping */
#define GPIO_AF4_USART1          ((uint8_t)0x04)  /* USART1 Alternate Function mapping  */
#define GPIO_AF4_TIM3            ((uint8_t)0x04)  /* TIM3 Alternate Function mapping*/
#define GPIO_AF4_SPI1            ((uint8_t)0x04)  /* SPI1 Alternate Function mapping   */
#define GPIO_AF4_I2C1            ((uint8_t)0x04)  /* I2C1 Alternate Function mapping    */
#define GPIO_AF4_USART3          ((uint8_t)0x04)  /* USART3 Alternate Function mapping    */
/**
 *
 */

/*
 * Alternate function AF5
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM1          ((uint8_t)0x05)  /* TIM1 Alternate Function mapping    */
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping    */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2 Alternate Function mapping   */
#define GPIO_AF5_I2C2          ((uint8_t)0x05)  /* I2C2 Alternate Function mapping     */
#define GPIO_AF5_LPTIM         ((uint8_t)0x05)  /* LPTIM Alternate Function mapping     */
#define GPIO_AF5_CAN           ((uint8_t)0x05)  /* CAN Alternate Function mapping    */
#define GPIO_AF5_USART3        ((uint8_t)0x05)  /* USART3 Alternate Function mapping    */

/**
 *
 */

/*
 * Alternate function AF6
 */

#define GPIO_AF6_USART2        ((uint8_t)0x06)  /* USART2 Alternate Function mapping   */
#define GPIO_AF6_LPUART        ((uint8_t)0x06)  /* LPUART Alternate Function mapping  */
#define GPIO_AF6_TIM5          ((uint8_t)0x06)  /* TIM5 Alternate Function mapping */
#define GPIO_AF6_TIM8          ((uint8_t)0x06)  /* TIM8 Alternate Function mapping     */
#define GPIO_AF6_I2C2          ((uint8_t)0x06)  /* I2C2 Alternate Function mapping     */
#define GPIO_AF6_UART4         ((uint8_t)0x06)  /* UART4 Alternate Function mapping   */
#define GPIO_AF6_UART5         ((uint8_t)0x06)  /* UART5 Alternate Function mapping    */
#define GPIO_AF6_SPI1          ((uint8_t)0x06)  /* SPI1 Alternate Function mapping    */
/**
 *
 */

/*
 * Alternate function AF7
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07)  /* COMP2 Alternate Function mapping     */
#define GPIO_AF7_I2C1         ((uint8_t)0x07)  /* I2C1 Alternate Function mapping      */
#define GPIO_AF7_TIM8         ((uint8_t)0x07)  /* TIM8 Alternate Function mapping   */
#define GPIO_AF7_TIM5         ((uint8_t)0x07)  /* TIM5 Alternate Function mapping     */
#define GPIO_AF7_LPUART       ((uint8_t)0x07)  /* LPUART Alternate Function mapping     */
#define GPIO_AF7_UART5        ((uint8_t)0x07)  /* UART5 Alternate Function mapping      */
#define GPIO_AF7_TIM1         ((uint8_t)0x07)  /* TIM1 Alternate Function mapping   */
#define GPIO_AF7_USART3       ((uint8_t)0x07)  /* USART3 Alternate Function mapping     */

/**
  *
  */

 /*
 * Alternate function AF8
 */
#define GPIO_AF8_COMP1        ((uint8_t)0x08)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF8_COMP2        ((uint8_t)0x08)  /* COMP2 Alternate Function mapping     */
#define GPIO_AF8_LPTIM        ((uint8_t)0x08)  /* LPTIM Alternate Function mapping      */
#define GPIO_AF8_MCO          ((uint8_t)0x08)  /* MCO   Alternate Function mapping      */

/**
  *
  */

 /*
 * Alternate function AF9
 */
#define GPIO_AF9_RTC          ((uint8_t)0x09)  /* RTC Alternate Function mapping     */
#define GPIO_AF9_COMP1        ((uint8_t)0x09)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF9_TSC          ((uint8_t)0x09)  /* COMP1 Alternate Function mapping     */

/**
  *
  */

 /*
 * Alternate function AF15
 */
#define GPIO_AF15         ((uint8_t)0x0F)  /* NON Alternate Function mapping   */

#define GPIO_NO_AF        (GPIO_AF15)
/**
  * @}
  */


/**
 *  IS_GPIO_AF macro definition
 */

#define IS_GPIO_AF(__AF__) (((__AF__) == GPIO_AF0_SPI1) || ((__AF__) == GPIO_AF1_TIM5)      || \
                            ((__AF__) == GPIO_AF0_LPTIM)     || ((__AF__) == GPIO_AF1_USART1)     || \
                            ((__AF__) == GPIO_AF0_SPI2)    || ((__AF__) == GPIO_AF1_I2C2)     || \
                            ((__AF__) == GPIO_AF0_TIM8)      || ((__AF__) == GPIO_AF1_CAN)    || \
                            ((__AF__) == GPIO_AF0_USART1)    || ((__AF__) == GPIO_AF1_SPI2)     || \
                            ((__AF__) == GPIO_AF0_USART3)    || ((__AF__) == GPIO_AF1_TIM9)     || \
                            ((__AF__) == GPIO_AF0_LPUART)   || ((__AF__) == GPIO_AF1_SPI1)      || \
                            ((__AF__) == GPIO_AF0_USART2)     || ((__AF__) == GPIO_AF1_I2C1) || \
                            ((__AF__) == GPIO_AF3_EVENTOUT)   || ((__AF__) == GPIO_AF2_TIM2)   || \
                            ((__AF__) == GPIO_AF5_TIM2)     || ((__AF__) == GPIO_AF2_TIM3)  || \
                            ((__AF__) == GPIO_AF5_TIM1)  || ((__AF__) == GPIO_AF2_TIM1)      || \
                            ((__AF__) == GPIO_AF5_SPI1)   || ((__AF__) == GPIO_AF2_LPTIM)      || \
                            ((__AF__) == GPIO_AF5_SPI2)      || ((__AF__) == GPIO_AF2_TIM4)     || \
                            ((__AF__) == GPIO_AF5_I2C2)     || ((__AF__) == GPIO_AF2_LPUART)   || \
                            ((__AF__) == GPIO_AF5_LPTIM)      || ((__AF__) == GPIO_AF4_USART2)     || \
                            ((__AF__) == GPIO_AF5_CAN) || ((__AF__) == GPIO_AF4_LPUART)   || \
                            ((__AF__) == GPIO_AF5_USART3)     || ((__AF__) == GPIO_AF4_USART1)  || \
                            ((__AF__) == GPIO_AF6_USART2)    || ((__AF__) == GPIO_AF4_TIM3) || \
                            ((__AF__) == GPIO_AF6_LPUART)     || ((__AF__) == GPIO_AF4_SPI1)   || \
                            ((__AF__) == GPIO_AF6_TIM5)   || ((__AF__) == GPIO_AF4_I2C1)    || \
                            ((__AF__) == GPIO_AF6_TIM8)    || ((__AF__) == GPIO_AF4_USART3)     || \
                            ((__AF__) == GPIO_AF6_I2C2)     || ((__AF__) == GPIO_AF7_COMP1)     || \
                            ((__AF__) == GPIO_AF6_UART4)     || ((__AF__) == GPIO_AF7_COMP2)   || \
                            ((__AF__) == GPIO_AF6_UART5)    || ((__AF__) == GPIO_AF7_I2C1)  || \
                            ((__AF__) == GPIO_AF6_SPI1)    || ((__AF__) == GPIO_AF7_TIM8)     || \
                            ((__AF__) == GPIO_AF8_COMP1)     || ((__AF__) == GPIO_AF7_TIM5) || \
                            ((__AF__) == GPIO_AF8_COMP2)  || ((__AF__) == GPIO_AF7_LPUART)     || \
                            ((__AF__) == GPIO_AF8_LPTIM)   || ((__AF__) == GPIO_AF7_UART5)       || \
                            ((__AF__) == GPIO_AF9_RTC)   || ((__AF__) == GPIO_AF7_TIM1)   || \
                            ((__AF__) == GPIO_AF9_COMP1)     || ((__AF__) == GPIO_AF7_USART3)  || \
                            ((__AF__) == GPIO_AF15)  || ((__AF__) == GPIO_NO_AF))





/**
 * @}
 */
/** @defgroup GPIO Alternate function remaping
 * @{
 */
#define AFIO_SPI1_NSS   (11U)
#define AFIO_SPI2_NSS   (10U)

#define IS_AFIO_SPIX(_PARAMETER_) \
            (((_PARAMETER_) == AFIO_SPI1_NSS) ||((_PARAMETER_) == AFIO_SPI2_NSS))
typedef enum
{
    AFIO_SPI_NSS_High_IMPEDANCE = 0U,
    AFIO_SPI_NSS_High_LEVEL = 1U
}AFIO_SPI_NSSType;

#define IS_AFIO_SPI_NSS(_PARAMETER_) \
            (((_PARAMETER_) == AFIO_SPI_NSS_High_IMPEDANCE) ||((_PARAMETER_) == AFIO_SPI_NSS_High_LEVEL))


typedef enum
{
    AFIO_ADC_ETRI= 9U,
    AFIO_ADC_ETRR = 8U
}AFIO_ADC_ETRType;

typedef enum
{
    AFIO_ADC_TRIG_EXTI_0 = 0x0U,
    AFIO_ADC_TRIG_EXTI_1 = 0x01U,
    AFIO_ADC_TRIG_EXTI_2,
    AFIO_ADC_TRIG_EXTI_3,
    AFIO_ADC_TRIG_EXTI_4,
    AFIO_ADC_TRIG_EXTI_5,
    AFIO_ADC_TRIG_EXTI_6,
    AFIO_ADC_TRIG_EXTI_7,
    AFIO_ADC_TRIG_EXTI_8,
    AFIO_ADC_TRIG_EXTI_9,
    AFIO_ADC_TRIG_EXTI_10,
    AFIO_ADC_TRIG_EXTI_11,
    AFIO_ADC_TRIG_EXTI_12,
    AFIO_ADC_TRIG_EXTI_13,
    AFIO_ADC_TRIG_EXTI_14,
    AFIO_ADC_TRIG_EXTI_15,
    AFIO_ADC_TRIG_TIM8_CH3,
    AFIO_ADC_TRIG_TIM8_CH4
}AFIO_ADC_Trig_RemapType;

#define IS_AFIO_ADC_ETR(_PARAMETER_) \
            (((_PARAMETER_) == AFIO_ADC_ETRI) ||((_PARAMETER_) == AFIO_ADC_ETRR))
#define IS_AFIO_ADC_ETRI(_PARAMETER_) \
            (((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_0) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_1)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_2) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_3)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_4) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_5)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_6) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_7)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_8) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_9)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_10) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_11)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_12) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_13)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_14) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_15)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_TIM8_CH4))

#define IS_AFIO_ADC_ETRR(_PARAMETER_) \
            (((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_0) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_1)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_2) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_3)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_4) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_5)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_6) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_7)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_8) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_9)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_10) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_11)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_12) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_13) ||\
            ((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_14) ||((_PARAMETER_) == AFIO_ADC_TRIG_EXTI_15)|| \
            ((_PARAMETER_) == AFIO_ADC_TRIG_TIM8_CH3))

 /**
 * @}
 */

/** @addtogroup GPIO_Exported_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup GPIO_Exported_Functions
 * @{
 */

void GPIO_DeInit(GPIO_Module* GPIOx);
void GPIO_AFIOInitDefault(void);
void GPIO_InitPeripheral(GPIO_Module* GPIOx, GPIO_InitType* GPIO_InitStruct);
void GPIO_InitStruct(GPIO_InitType* GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit(GPIO_Module* GPIOx, uint16_t Pin);
uint16_t GPIO_ReadInputData(GPIO_Module* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_Module* GPIOx, uint16_t Pin);
uint16_t GPIO_ReadOutputData(GPIO_Module* GPIOx);
void GPIO_SetBits(GPIO_Module* GPIOx, uint16_t Pin);
void GPIO_ResetBits(GPIO_Module* GPIOx, uint16_t Pin);
void GPIO_WriteBit(GPIO_Module* GPIOx, uint16_t Pin, Bit_OperateType BitCmd);
void GPIO_Write(GPIO_Module* GPIOx, uint16_t PortVal);
void GPIO_ConfigPinLock(GPIO_Module* GPIOx, uint16_t Pin);
void GPIO_ConfigEventOutput(uint8_t PortSource, uint8_t PinSource);
void GPIO_CtrlEventOutput(FunctionalState Cmd);
void GPIO_ConfigPinRemap(uint8_t PortSource, uint8_t PinSource, uint32_t AlternateFunction);
void GPIO_ConfigEXTILine(uint8_t PortSource, uint8_t PinSource);

void AFIO_ConfigSPINSSMode(uint32_t AFIO_SPIx_NSS,AFIO_SPI_NSSType SpiNssType);
void AFIO_ConfigADCExternalTrigRemap(AFIO_ADC_ETRType ADCETRType,AFIO_ADC_Trig_RemapType ADCTrigRemap);

#ifdef __cplusplus
}
#endif

#endif /* __N32G43X_GPIO_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
