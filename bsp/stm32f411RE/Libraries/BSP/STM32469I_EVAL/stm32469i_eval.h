/**
  ******************************************************************************
  * @file    stm32469i_eval.h
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file contains definitions for STM32469I-EVAL's LEDs,
  *          push-buttons and COM ports hardware resources.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32469I_EVAL_H
#define __STM32469I_EVAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* USE_STM32469I_EVAL_REVA must USE USE_IOEXPANDER */
#if defined(USE_STM32469I_EVAL_REVA)
#ifndef USE_IOEXPANDER
#define USE_IOEXPANDER
#endif /* USE_IOEXPANDER */
#endif /* USE_STM32469I_EVAL_REVA */

 /* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup BSP
  * @{
  */


/** @addtogroup STM32469I_EVAL
  * @{
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL STM32469I-EVAL LOW LEVEL
  * @{
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL_Exported_Types STM32469I EVAL Low Level Exported Types
 * @{
 */

/** @brief Led_TypeDef
  *  STM32469I_EVAL board leds definitions.
  */
typedef enum
{
 LED1 = 0,
 LED_GREEN = LED1,
 LED2 = 1,
 LED_ORANGE = LED2,
 LED3 = 2,
 LED_RED = LED3,
 LED4 = 3,
 LED_BLUE = LED4

} Led_TypeDef;

/** @brief Button_TypeDef
  *  STM32469I_EVAL board Buttons definitions.
  */
typedef enum
{
  BUTTON_WAKEUP = 0,
  BUTTON_TAMPER = 1,
  BUTTON_KEY = 2

} Button_TypeDef;

/** @brief ButtonMode_TypeDef
  *  STM32469I_EVAL board Buttons Modes definitions.
  */
typedef enum
{
 BUTTON_MODE_GPIO = 0,
 BUTTON_MODE_EXTI = 1

} ButtonMode_TypeDef;

#if defined(USE_IOEXPANDER)
/** @brief JOYMode_TypeDef
  *  STM32469I_EVAL board Joystick Mode definitions.
  */
typedef enum
{
 JOY_MODE_GPIO = 0,
 JOY_MODE_EXTI = 1

} JOYMode_TypeDef;

/** @brief JOYState_TypeDef
  *  STM32469I_EVAL board Joystick State definitions.
  */
typedef enum
{
 JOY_NONE  = 0,
 JOY_SEL   = 1,
 JOY_DOWN  = 2,
 JOY_LEFT  = 3,
 JOY_RIGHT = 4,
 JOY_UP    = 5

} JOYState_TypeDef;
#endif /* USE_IOEXPANDER */

/** @brief COM_TypeDef
  *  STM32469I_EVAL board COM ports.
  */
typedef enum
{
 COM1 = 0,
 COM2 = 1

} COM_TypeDef;

/** @brief EVAL_Status_TypeDef
  *  STM32469I_EVAL board Eval Status return possible values.
  */
typedef enum
{
 EVAL_OK    = 0,
 EVAL_ERROR = 1

} EVAL_Status_TypeDef;

/**
  * @}
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL_Exported_Constants STM32469I EVAL Low Level Exported Constants
  * @{
  */

/**
  * @brief  Define for STM32469I_EVAL board
  */
#if !defined (USE_STM32469I_EVAL)
 #define USE_STM32469I_EVAL
#endif

/** @addtogroup STM32469I_EVAL_LOW_LEVEL_LED STM32469I EVAL Low Level Led
  * @{
  */
/* Always four leds for all revisions of Eval boards */
#define LEDn                             ((uint8_t)4)

#if !defined(USE_STM32469I_EVAL_REVA)
/* Rev B board and beyond : 4 Leds are connected to MCU directly and not via MFX */
/* PK3, PK4, PK5, PK6 are used */
#define LEDx_GPIO_PORT                   GPIOK
#define LEDx_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOK_CLK_ENABLE()
#define LEDx_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOK_CLK_DISABLE()
#define LED1_PIN                         GPIO_PIN_3
#define LED2_PIN                         GPIO_PIN_4
#define LED3_PIN                         GPIO_PIN_5
#define LED4_PIN                         GPIO_PIN_6
#else
/* Eval Rev A board */
#define LED1_PIN                         IO_PIN_16
#define LED2_PIN                         IO_PIN_17
#define LED3_PIN                         IO_PIN_18
#define LED4_PIN                         IO_PIN_19
#endif /* USE_STM32469I_EVAL_REVA */
/**
  * @}
  */

/**
  * @brief MFX_IRQOUt pin
  */
#define MFX_IRQOUT_PIN                    GPIO_PIN_8
#define MFX_IRQOUT_GPIO_PORT              GPIOI
#define MFX_IRQOUT_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOI_CLK_ENABLE()
#define MFX_IRQOUT_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOI_CLK_DISABLE()
#define MFX_IRQOUT_EXTI_IRQn              EXTI9_5_IRQn
#define MFX_IRQOUT_EXTI_IRQnHandler       EXTI9_5_IRQHandler

/** @addtogroup STM32469I_EVAL_LOW_LEVEL_BUTTON STM32469I EVAL Low Level Button
  * @{
  */
/* Joystick pins are connected to IO Expander (accessible through I2C1 interface) */
#define BUTTONn                             ((uint8_t)3)

/**
  * @brief Wakeup push-button
  */
#define WAKEUP_BUTTON_PIN                   GPIO_PIN_0
#define WAKEUP_BUTTON_GPIO_PORT             GPIOA
#define WAKEUP_BUTTON_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define WAKEUP_BUTTON_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#define WAKEUP_BUTTON_EXTI_IRQn             EXTI0_IRQn

/**
  * @brief Tamper push-button
  */
#define TAMPER_BUTTON_PIN                    GPIO_PIN_13
#define TAMPER_BUTTON_GPIO_PORT              GPIOC
#define TAMPER_BUTTON_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define TAMPER_BUTTON_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOC_CLK_DISABLE()
#define TAMPER_BUTTON_EXTI_IRQn              EXTI15_10_IRQn

/**
  * @brief Key push-button
  */
#define KEY_BUTTON_PIN                       GPIO_PIN_13
#define KEY_BUTTON_GPIO_PORT                 GPIOC
#define KEY_BUTTON_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOC_CLK_ENABLE()
#define KEY_BUTTON_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOC_CLK_DISABLE()
#define KEY_BUTTON_EXTI_IRQn                 EXTI15_10_IRQn

#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)    do { if((__INDEX__) == 0) {WAKEUP_BUTTON_GPIO_CLK_ENABLE();} else\
                                                   if((__INDEX__) == 1) {TAMPER_BUTTON_GPIO_CLK_ENABLE();} else\
                                                                        {KEY_BUTTON_GPIO_CLK_ENABLE();   }} while(0)

#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)    (((__INDEX__) == 0) ? WAKEUP_BUTTON_GPIO_CLK_DISABLE() :\
                                                ((__INDEX__) == 1) ? TAMPER_BUTTON_GPIO_CLK_DISABLE() : KEY_BUTTON_GPIO_CLK_DISABLE())
/**
  * @}
  */

/** @addtogroup STM32469I_EVAL_LOW_LEVEL_COM
  * @{
  */
#define COMn                             ((uint8_t)1)

/**
 * @brief Definition for COM port1, connected to USART1
 */
#define EVAL_COM1                          USART1
#define EVAL_COM1_CLK_ENABLE()             __HAL_RCC_USART1_CLK_ENABLE()
#define EVAL_COM1_CLK_DISABLE()            __HAL_RCC_USART1_CLK_DISABLE()

#define EVAL_COM1_TX_PIN                   GPIO_PIN_9
#define EVAL_COM1_RX_PIN                   GPIO_PIN_10
#define EVAL_COM1_TX_GPIO_PORT             GPIOA
#define EVAL_COM1_RX_GPIO_PORT             EVAL_COM1_TX_GPIO_PORT

#define EVAL_COM1_TX_AF                    GPIO_AF7_USART1
#define EVAL_COM1_RX_AF                    EVAL_COM1_TX_AF

#define EVAL_COM1_TX_RX_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define EVAL_COM1_TX_RX_GPIO_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()

#define EVAL_COM1_IRQn                     USART1_IRQn

#define EVAL_COMx_CLK_ENABLE(__INDEX__)            do { if((__INDEX__) == 0) {EVAL_COM1_CLK_ENABLE();} } while(0)
#define EVAL_COMx_CLK_DISABLE(__INDEX__)           (((__INDEX__) == 0) ? EVAL_COM1_CLK_DISABLE() : 0)

#define EVAL_COMx_TX_RX_GPIO_CLK_ENABLE(__INDEX__)    do { if((__INDEX__) == 0) {EVAL_COM1_TX_RX_GPIO_CLK_ENABLE();} } while(0)
#define EVAL_COMx_TX_RX_GPIO_CLK_DISABLE(__INDEX__)   (((__INDEX__) == 0) ? EVAL_COM1_TX_RX_GPIO_CLK_DISABLE() : 0)

/**
  * @brief Joystick Pins definition
  */
#if defined(USE_IOEXPANDER)
#define JOY_SEL_PIN                    IO_PIN_0
#define JOY_DOWN_PIN                   IO_PIN_1
#define JOY_LEFT_PIN                   IO_PIN_2
#define JOY_RIGHT_PIN                  IO_PIN_3
#define JOY_UP_PIN                     IO_PIN_4
#define JOY_NONE_PIN                   JOY_ALL_PINS
#define JOY_ALL_PINS                   (IO_PIN_0 | IO_PIN_1 | IO_PIN_2 | IO_PIN_3 | IO_PIN_4)
#endif /* USE_IOEXPANDER */

/**
  * @brief Eval Pins definition
  */
#if defined(USE_IOEXPANDER)
#define XSDN_PIN                       IO_PIN_10
#define MII_INT_PIN                    IO_PIN_13
#define RSTI_PIN                       IO_PIN_11
#define CAM_PLUG_PIN                   IO_PIN_12
#define TS_INT_PIN                     IO_PIN_14
#define AUDIO_INT_PIN                  IO_PIN_5
#define OTG_FS1_OVER_CURRENT_PIN       IO_PIN_6
#define OTG_FS1_POWER_SWITCH_PIN       IO_PIN_7
#define OTG_FS2_OVER_CURRENT_PIN       IO_PIN_8
#define OTG_FS2_POWER_SWITCH_PIN       IO_PIN_9
#define SD_DETECT_PIN                  IO_PIN_15
#endif /* USE_IOEXPANDER */

/* Exported constant IO ------------------------------------------------------*/

/**
  * @brief TouchScreen FT6206 Slave I2C address
  */
#define TS_I2C_ADDRESS                   ((uint16_t)0x54)

/**
  * @brief MFX_I2C_ADDR 0
  */
#define IO_I2C_ADDRESS                   ((uint16_t)0x84)

/**
  * @brief Camera I2C Slave address
  */
#define CAMERA_I2C_ADDRESS               ((uint16_t)0x5A)

/**
  * @brief Audio I2C Slave address
  */
#define AUDIO_I2C_ADDRESS                ((uint16_t)0x34)

/**
  * @brief EEPROM I2C Slave address 1
  */
#define EEPROM_I2C_ADDRESS_A01           ((uint16_t)0xA0)

/**
  * @brief EEPROM I2C Slave address 2
  */
#define EEPROM_I2C_ADDRESS_A02           ((uint16_t)0xA6)

/**
  * @brief I2C clock speed configuration (in Hz)
  * WARNING:
  * Make sure that this define is not already declared in other files
  * It can be used in parallel by other modules.
  */
#ifndef I2C_SCL_FREQ_KHZ
#define I2C_SCL_FREQ_KHZ                  400000 /*!< f(I2C_SCL) = 400 kHz */
#endif /* I2C_SCL_FREQ_KHZ */

/**
  * @brief User can use this section to tailor I2Cx/I2Cx instance used and associated
  * resources.
  * Definition for I2Cx clock resources
  */
#define EVAL_I2Cx                             I2C1
#define EVAL_I2Cx_CLK_ENABLE()                __HAL_RCC_I2C1_CLK_ENABLE()
#define EVAL_DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define EVAL_I2Cx_SCL_SDA_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()

#define EVAL_I2Cx_FORCE_RESET()               __HAL_RCC_I2C1_FORCE_RESET()
#define EVAL_I2Cx_RELEASE_RESET()             __HAL_RCC_I2C1_RELEASE_RESET()

/** @brief Definition for I2Cx Pins
  */
#define EVAL_I2Cx_SCL_PIN                     GPIO_PIN_8 /*!< PB8 */
#define EVAL_I2Cx_SCL_SDA_GPIO_PORT           GPIOB
#define EVAL_I2Cx_SCL_SDA_AF                  GPIO_AF4_I2C1
#define EVAL_I2Cx_SDA_PIN                     GPIO_PIN_9 /*!< PB9 */

/** @brief Definition of I2C interrupt requests
  */
#define EVAL_I2Cx_EV_IRQn                     I2C1_EV_IRQn
#define EVAL_I2Cx_ER_IRQn                     I2C1_ER_IRQn

/**
  * @}
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL_Exported_Macros STM32469I EVAL Low Level Exported Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL_Exported_Functions STM32469I EVAL Low Level Exported Functions
  * @{
  */
uint32_t         BSP_GetVersion(void);
void             BSP_LED_Init(Led_TypeDef Led);
void             BSP_LED_DeInit(Led_TypeDef Led);
void             BSP_LED_On(Led_TypeDef Led);
void             BSP_LED_Off(Led_TypeDef Led);
void             BSP_LED_Toggle(Led_TypeDef Led);
void             BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
void             BSP_PB_DeInit(Button_TypeDef Button);
uint32_t         BSP_PB_GetState(Button_TypeDef Button);
void             BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef *husart);
void             BSP_COM_DeInit(COM_TypeDef COM, UART_HandleTypeDef *huart);
#if defined(USE_IOEXPANDER)
uint8_t          BSP_JOY_Init(JOYMode_TypeDef Joy_Mode);
void             BSP_JOY_DeInit(void);
JOYState_TypeDef BSP_JOY_GetState(void);
#endif /* USE_IOEXPANDER */

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

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* __STM32469I_EVAL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
