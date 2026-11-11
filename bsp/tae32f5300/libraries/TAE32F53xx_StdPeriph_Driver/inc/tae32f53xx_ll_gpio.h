/**
  ******************************************************************************
  * @file    tae32f53xx_ll_gpio.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO LL module.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_LL_GPIO_H_
#define _TAE32F53XX_LL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup GPIO_LL
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup GPIO_LL_Exported_Types GPIO LL Exported Types
  * @brief    GPIO LL Exported Types
  * @{
  */

/**
  * @brief GPIO Configuration Mode
  *        Elements values convention: 0xX0Y0000Z
  *           - X  : GPIO mode or Interrupt Mode
  *           - Y  : External IT detection
  *           - Z  : IO Direction mode (Input, Output or Alternate)
  * @note  External Interrupt only vailed in input mode
  */
typedef enum {
    GPIO_MODE_INPUT             = 0x00000000u,      /*!< GPIO Input Mode                                                     */
    GPIO_MODE_OUTPUT            = 0x00000001u,      /*!< GPIO Output Mode                                                    */
    GPIO_MODE_AF                = 0x00000002u,      /*!< GPIO Alternate Mode                                                 */
    GPIO_MODE_ANALOG            = 0x00000003u,      /*!< Analog Mode                                                         */
    GPIO_MODE_IT_RISING         = 0x10100000u,      /*!< External Interrupt Mode with Rising edge trigger detection          */
    GPIO_MODE_IT_FALLING        = 0x10200000u,      /*!< External Interrupt Mode with Falling edge trigger detection         */
    GPIO_MODE_IT_RISING_FALLING = 0x10300000u,      /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
} GPIO_ModeETypeDef;

/**
  * @brief GPIO AF Mode enumeration
  */

typedef enum {
    GPIO_AF0_INPUT              = ((uint8_t)0x0),   /*!< GPIO alternate function 0 INPUT        */

    GPIO_AF1_OUTPUT             = ((uint8_t)0x1),   /*!< GPIO alternate function 1 OUTPUT       */

    GPIO_AF2_MCO                = ((uint8_t)0x2),   /*!< GPIO alternate function 2 MCO          */
    GPIO_AF2_SWDAT              = ((uint8_t)0x2),   /*!< GPIO alternate function 2 SWDAT        */
    GPIO_AF2_SWCLK              = ((uint8_t)0x2),   /*!< GPIO alternate function 2 SWCLK        */
    GPIO_AF2_SWO                = ((uint8_t)0x2),   /*!< GPIO alternate function 2 SWO          */
    GPIO_AF2_SYSDBOUT           = ((uint8_t)0x2),   /*!< GPIO alternate function 2 SYSDBOUT     */

    GPIO_AF3_TMR0               = ((uint8_t)0x3),   /*!< GPIO alternate function 3 TMR0         */
    GPIO_AF3_TMR1               = ((uint8_t)0x3),   /*!< GPIO alternate function 3 TMR1         */
    GPIO_AF3_TMR2               = ((uint8_t)0x3),   /*!< GPIO alternate function 3 TMR2         */
    GPIO_AF3_TMR3               = ((uint8_t)0x3),   /*!< GPIO alternate function 3 TMR3         */

    GPIO_AF4_TMR0               = ((uint8_t)0x4),   /*!< GPIO alternate function 4 TMR0         */
    GPIO_AF4_TMR1               = ((uint8_t)0x4),   /*!< GPIO alternate function 4 TMR1         */
    GPIO_AF4_TMR2               = ((uint8_t)0x4),   /*!< GPIO alternate function 4 TMR2         */
    GPIO_AF4_TMR3               = ((uint8_t)0x4),   /*!< GPIO alternate function 4 TMR3         */

    GPIO_AF5_TMR4               = ((uint8_t)0x5),   /*!< GPIO alternate function 5 TMR4         */
    GPIO_AF5_TMR5               = ((uint8_t)0x5),   /*!< GPIO alternate function 5 TMR5         */
    GPIO_AF5_TMR6               = ((uint8_t)0x5),   /*!< GPIO alternate function 5 TMR6         */
    GPIO_AF5_TMR7               = ((uint8_t)0x5),   /*!< GPIO alternate function 5 TMR7         */

    GPIO_AF6_TMR4               = ((uint8_t)0x6),   /*!< GPIO alternate function 6 TMR4         */
    GPIO_AF6_TMR5               = ((uint8_t)0x6),   /*!< GPIO alternate function 6 TMR5         */
    GPIO_AF6_TMR6               = ((uint8_t)0x6),   /*!< GPIO alternate function 6 TMR6         */
    GPIO_AF6_TMR7               = ((uint8_t)0x6),   /*!< GPIO alternate function 6 TMR7         */

    GPIO_AF7_CAN                = ((uint8_t)0x7),   /*!< GPIO alternate function 7 CAN          */
    GPIO_AF7_I2C0               = ((uint8_t)0x7),   /*!< GPIO alternate function 7 I2C0         */

    GPIO_AF8_I2C0               = ((uint8_t)0x8),   /*!< GPIO alternate function 8 I2C0         */
    GPIO_AF8_DALI               = ((uint8_t)0x8),   /*!< GPIO alternate function 8 DALI         */

    GPIO_AF9_I2C1               = ((uint8_t)0x9),   /*!< GPIO alternate function 9 I2C1         */
    GPIO_AF9_UART1              = ((uint8_t)0x9),   /*!< GPIO alternate function 9 UART1        */

    GPIO_AF10_UART0             = ((uint8_t)0xA),   /*!< GPIO alternate function 10 UART0       */
    GPIO_AF10_UART1             = ((uint8_t)0xA),   /*!< GPIO alternate function 10 UART1       */

    GPIO_AF11_HRPWM             = ((uint8_t)0xB),   /*!< GPIO alternate function 11 HRPWM       */
    GPIO_AF11_USB               = ((uint8_t)0xB),   /*!< GPIO alternate function 1 USB          */

    GPIO_AF12_HRPWM             = ((uint8_t)0xC),   /*!< GPIO alternate function 12 HRPWM       */

    GPIO_AF13_HRPWM             = ((uint8_t)0xD),   /*!< GPIO alternate function 13 HRPWM       */

    GPIO_AF14_CMP0              = ((uint8_t)0xE),   /*!< GPIO alternate function 14 CMP0        */
    GPIO_AF14_CMP1              = ((uint8_t)0xE),   /*!< GPIO alternate function 14 CMP1        */
    GPIO_AF14_CMP2              = ((uint8_t)0xE),   /*!< GPIO alternate function 14 CMP2        */
    GPIO_AF14_CMP3              = ((uint8_t)0xE),   /*!< GPIO alternate function 14 CMP3        */

    GPIO_AF15_ANALOG            = ((uint8_t)0xF),   /*!< GPIO alternate function 15 ANALOG      */
    GPIO_AF15_ADC0              = ((uint8_t)0xF),   /*!< GPIO alternate function 15 ADC0        */
    GPIO_AF15_ADC1              = ((uint8_t)0xF),   /*!< GPIO alternate function 15 ADC1        */
    GPIO_AF15_DAC0              = ((uint8_t)0xF),   /*!< GPIO alternate function 15 DAC0        */
    GPIO_AF15_DAC1              = ((uint8_t)0xF),   /*!< GPIO alternate function 15 DAC1        */
    GPIO_AF15_DAC2              = ((uint8_t)0xF),   /*!< GPIO alternate function 15 DAC2        */
    GPIO_AF15_DAC3              = ((uint8_t)0xF),   /*!< GPIO alternate function 15 DAC3        */
    GPIO_AF15_CMP0              = ((uint8_t)0xF),   /*!< GPIO alternate function 15 CMP0        */
    GPIO_AF15_CMP1              = ((uint8_t)0xF),   /*!< GPIO alternate function 15 CMP1        */
    GPIO_AF15_CMP2              = ((uint8_t)0xF),   /*!< GPIO alternate function 15 CMP2        */
    GPIO_AF15_CMP3              = ((uint8_t)0xF),   /*!< GPIO alternate function 15 CMP3        */
    GPIO_AF15_USB               = ((uint8_t)0xF),   /*!< GPIO alternate function 15 USB         */
} GPIO_AFETypeDef;

/**
  * @brief GPIO Pull-Up or Pull-Down Activation
  */
typedef enum {
    GPIO_NOPULL                 = 0x00000000U,      /*!< No Pull-up or Pull-down activation     */
    GPIO_PULLUP                 = 0x00000001U,      /*!< Pull-up activation                     */
    GPIO_PULLDOWN               = 0x00000002U,      /*!< Pull-down activation                   */
} GPIO_PullETypeDef;

/**
  * @brief GPIO output type: Push-Pull or Open-Drain
  */
typedef enum {
    GPIO_OTYPE_PP               = 0x00000000U,      /*!< Output Push Pull Type                  */
    GPIO_OTYPE_OD               = 0x00000001U,      /*!< Output Open Drain Type                 */
} GPIO_OutputETypeDef;

/**
  * @brief GPIO Output Maximum frequency
  */
typedef enum {
    GPIO_SPEED_FREQ_LOW         = 0x00000000U,     /*!< Low speed                               */
    GPIO_SPEED_FREQ_HIGH        = 0x00000001U,     /*!< High speed                              */
} GPIO_SpeedETypeDef;

/**
  * @brief  GPIO Bit SET and Bit RESET enumeration
  */
typedef enum {
    GPIO_PIN_RESET = 0, /*!< GPIO pin state RESET   */
    GPIO_PIN_SET,       /*!< GPIO pin state SET     */
} GPIO_PinStateETypeDef;


/**
  * @brief GPIO Init structure definition
  */
typedef struct __GPIO_InitTypeDef {
    uint32_t Pin;                   /*!< Specifies the GPIO pins to be configured.
                                        This parameter can be any value of @ref GPIO_pins_define                         */

    GPIO_ModeETypeDef   Mode;       /*!< Specifies the operating mode for the selected pins.                             */

    GPIO_OutputETypeDef OType;      /*!< Specifies the output type for the selected pins(output or AF output mode only). */

    GPIO_PullETypeDef   Pull;       /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.            */

    GPIO_SpeedETypeDef  Speed;      /*!< Specifies the speed for the selected pins.                                      */

    GPIO_AFETypeDef     Alternate;  /*!< Peripheral to be connected to the selected pins.                                */
} GPIO_InitTypeDef;

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIO_LL_Exported_Constants GPIO LL Exported Constants
  * @brief    GPIO LL Exported Constants
  * @{
  */

/** @addtogroup GPIO_pins_define GPIO pins define
  * @{
  */
#define GPIO_NUMBER                 16U

#define GPIO_PIN_0                  ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                  ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                  ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                  ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                  ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                  ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                  ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                  ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                  ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                  ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                 ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                 ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                 ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                 ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                 ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                 ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All                ((uint16_t)0xFFFF)  /* All pins selected */

#define GPIO_PIN_MASK               0x0000FFFFu /* PIN mask for assert test */

/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIO_LL_Exported_Macros GPIO LL Exported Macros
  * @brief    GPIO LL Exported Macros
  * @{
  */

/**
  * @brief  Enable the specified GPIO_Port interrupt.
  * @param  __GPIO__ specifies GPIO Port to enable.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @return None
  */
#define __LL_GPIO_PORT_IT_ENABLE(__GPIO__)                      WRITE_REG((__GPIO__)->IER, 0x01U)

/**
  * @brief  Disable the specified GPIO_Port interrupt.
  * @param  __GPIO__ specifies GPIO Port to disable.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @return None
  */
#define __LL_GPIO_PORT_IT_DISABLE(__GPIO__)                     WRITE_REG((__GPIO__)->IER, 0x00U)

/**
  * @brief  Enable the specified GPIO_Pin interrupt.
  * @note   GPIO_Port interrupt must also be enabled.
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return None
  */
#define __LL_GPIO_IT_ENABLE(__GPIO__, __PIN__)                  SET_BIT((__GPIO__)->ITER, (__PIN__))

/**
  * @brief  Disable the specified GPIO_Pin interrupt.
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return None
  */
#define __LL_GPIO_IT_DISABLE(__GPIO__, __PIN__)                 CLEAR_BIT((__GPIO__)->ITER, (__PIN__))

/**
  * @brief  Check whether the specified GPIO_Pin Interrupt is enabled or not.
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return The interrupt settings for specified GPIO_Pin(ENABLE or DISABLE)
  */
#define __LL_GPIO_IT_CHECK_SOURCE(__GPIO__, __PIN__)            ((((__GPIO__)->ITER & GPIO_ITER_ITE) == (__PIN__)) ? SET : RESET)

/**
  * @brief  Check whether the specified GPIO_Pin pending flag is set or not.
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return The pending state of __PIN__
  *     @retval SET At least one of __PIN__ is Pending
  *     @retval RESET None of __PIN__ is Pending
  */
#define __LL_GPIO_GET_FLAG(__GPIO__, __PIN__)                   ((((__GPIO__)->PR & (__PIN__)) != 0x00UL) ? SET : RESET)

/**
  * @brief  Clear the specified GPIO_Pin pending flags
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return None
  */
#define __LL_GPIO_CLEAR_FLAG(__GPIO__, __PIN__)                 ((__GPIO__)->PR = (__PIN__))

/**
  * @brief  Check whether the specified GPIO_Pin interrupt pending flag is asserted or not.
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return The interrupt pending state of __PIN__
  *     @retval SET At least one of __PIN__ is pending interrupt
  *     @retval RESET None of __PIN__ is pending interrupt
  */
#define __LL_GPIO_GET_IT(__GPIO__, __PIN__)                     ((((__GPIO__)->PR & (__PIN__)) != 0x00UL) ? SET : RESET)

/**
  * @brief  Clear the specified GPIO_Pin interrupt pending flags
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return None
  */
#define __LL_GPIO_CLEAR_IT(__GPIO__, __PIN__)                   ((__GPIO__)->PR = (__PIN__))

/**
  * @brief  Enable the specified GPIO_Pin input debounce feature.
  *         The external signal will debounce 4 HCLK time before enter GPIO module
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return None
  */
#define __LL_GPIO_INPUT_DEB_ENABLE(__GPIO__, __PIN__)           SET_BIT((__GPIO__)->SDER, (__PIN__))

/**
  * @brief  Disable the specified GPIO_Pin input debounce feature.
  *         The external signal will enter GPIO module without any debounce
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return None
  */
#define __LL_GPIO_INPUT_DEB_DISABLE(__GPIO__, __PIN__)          CLEAR_BIT((__GPIO__)->SDER, (__PIN__))

/**
  * @brief  Enable the specified GPIO_Pin input synchronize feature.
  *         The external signal will be aligned with HCLK before enter GPIO module
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return None
  */
#define __LL_GPIO_INPUT_SYNC_ENABLE(__GPIO__, __PIN__)          SET_BIT((__GPIO__)->SDER, ((__PIN__) << 16U))

/**
  * @brief  Disable the specified GPIO_Pin input synchronize feature.
  *         The external signal will enter GPIO module without synchronization
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return None
  */
#define __LL_GPIO_INPUT_SYNC_DISABLE(__GPIO__, __PIN__)         CLEAR_BIT((__GPIO__)->SDER, ((__PIN__) << 16U))

/**
  * @brief  Enable the specified GPIO_Pin input Hysteresis feature.
  *         When enable hysteresis, the rising edge?threshold?voltage is larger than the falling edge?threshold?voltage
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return None
  */
#define __LL_GPIO_INPUT_HY_ENABLE(__GPIO__, __PIN__)            SET_BIT((__GPIO__)->IHYR, (__PIN__))

/**
  * @brief  Disable the specified GPIO_Pin input Hysteresis feature.
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return None
  */
#define __LL_GPIO_INPUT_HY_DISABLE(__GPIO__, __PIN__)           CLEAR_BIT((__GPIO__)->IHYR, (__PIN__))

/**
  * @brief  Set low output driver strenght (8mA) for specified GPIO_Pin.
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return None
  */
#define __LL_GPIO_OUTPUT_DRV_STRENGHT_LOW(__GPIO__, __PIN__)    CLEAR_BIT((__GPIO__)->DSR, (__PIN__))

/**
  * @brief  Set high output driver strenght (24mA) for specified GPIO_Pin.
  * @param  __GPIO__ specifies GPIO Port.
  *         This parameter can be one of GPIOx where x can be (A, B, ...)
  * @param  __PIN__ specifies GPIO Pin.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return None
  */
#define __LL_GPIO_OUTPUT_DRV_STRENGHT_HIGH(__GPIO__, __PIN__)   SET_BIT((__GPIO__)->DSR, (__PIN__))

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup GPIO_LL_Exported_Functions
  * @{
  */

/** @addtogroup GPIO_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);
LL_StatusETypeDef LL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin);
/**
  * @}
  */


/** @addtogroup GPIO_LL_Exported_Functions_Group2
  * @{
  */
void LL_GPIO_AF_Config(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_AFETypeDef Alternate);
/**
  * @}
  */


/** @addtogroup GPIO_LL_Exported_Functions_Group3
  * @{
  */
GPIO_PinStateETypeDef LL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) ;
void          LL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinStateETypeDef PinState);
void          LL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint16_t      LL_GPIO_ReadData(GPIO_TypeDef *GPIOx);
void          LL_GPIO_WriteData(GPIO_TypeDef *GPIOx, uint16_t Data);
/**
  * @}
  */


/** @addtogroup GPIO_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_GPIO_IRQHandler(GPIO_TypeDef *GPIOx);
void LL_GPIO_ExtTrigCallback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
/**
  * @}
  */

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup GPIO_LL_Private_Macros GPIO LL Private Macros
  * @brief    GPIO LL Private Macros
  * @{
  */

/**
  * @brief  Judge is GPIO pin or not
  * @param  __PIN__ pin to judge
  * @retval 0 isn't GPIO pin
  * @retval 1 is GPIO pin
  */
#define IS_GPIO_PIN(__PIN__)            ((((__PIN__) & GPIO_PIN_MASK) != 0x00U) && \
                                         (((__PIN__) & ~GPIO_PIN_MASK) == 0x00U))

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_GPIO_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

