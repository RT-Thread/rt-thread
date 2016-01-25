/**
  ******************************************************************************
  * @file    stm32469i_discovery.h
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file contains definitions for STM32469I-Discovery LEDs,
  *          push-buttons hardware resources.
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
#ifndef __STM32469I_DISCOVERY_H
#define __STM32469I_DISCOVERY_H

#ifdef __cplusplus
 extern "C" {
#endif


 /* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I_Discovery
  * @{
  */

/** @defgroup STM32469I_Discovery_LOW_LEVEL STM32469I-Discovery LOW LEVEL
  * @{
  */

/** @defgroup STM32469I_Discovery_LOW_LEVEL_Exported_Types STM32469I Discovery Low Level Exported Types
 * @{
 */

/** @brief Led_TypeDef
  *  STM32469I_Discovery board leds definitions.
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
  *  STM32469I_Discovery board Buttons definitions.
  */
typedef enum
{
  BUTTON_WAKEUP = 0
} Button_TypeDef;

#define BUTTON_USER BUTTON_WAKEUP

/** @brief ButtonMode_TypeDef
  *  STM32469I_Discovery board Buttons Modes definitions.
  */
typedef enum
{
 BUTTON_MODE_GPIO = 0,
 BUTTON_MODE_EXTI = 1

} ButtonMode_TypeDef;

/** @addtogroup Exported_types
  * @{
  */ 
typedef enum 
{
  PB_SET = 0, 
  PB_RESET = !PB_SET
} ButtonValue_TypeDef;


/** @brief DISCO_Status_TypeDef
  *  STM32469I_DISCO board Status return possible values.
  */
typedef enum
{
 DISCO_OK    = 0,
 DISCO_ERROR = 1

} DISCO_Status_TypeDef;

/**
  * @}
  */

/** @defgroup STM32469I_Discovery_LOW_LEVEL_Exported_Constants STM32469I Discovery Low Level Exported Constants
  * @{
  */


/** @addtogroup STM32469I_Discovery_LOW_LEVEL_LED STM32469I Discovery Low Level Led
  * @{
  */
/* Always four leds for all revisions of Discovery boards */
#define LEDn                             ((uint8_t)4)


/* 4 Leds are connected to MCU directly on PG6, PD4, PD5, PK3 */
#define LED1_GPIO_PORT                   ((GPIO_TypeDef*)GPIOG)
#define LED2_GPIO_PORT                   ((GPIO_TypeDef*)GPIOD)
#define LED3_GPIO_PORT                   ((GPIO_TypeDef*)GPIOD)
#define LED4_GPIO_PORT                   ((GPIO_TypeDef*)GPIOK)

#define LED1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOG_CLK_ENABLE()
#define LED1_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOG_CLK_DISABLE()
#define LED2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOD_CLK_ENABLE()
#define LED2_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOD_CLK_DISABLE()
#define LED3_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOD_CLK_ENABLE()
#define LED3_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOD_CLK_DISABLE()
#define LED4_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOK_CLK_ENABLE()
#define LED4_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOK_CLK_DISABLE()

#define LED1_PIN                         ((uint32_t)GPIO_PIN_6)
#define LED2_PIN                         ((uint32_t)GPIO_PIN_4)
#define LED3_PIN                         ((uint32_t)GPIO_PIN_5)
#define LED4_PIN                         ((uint32_t)GPIO_PIN_3)
/**
  * @}
  */

/** @addtogroup STM32469I_Discovery_LOW_LEVEL_BUTTON STM32469I Discovery Low Level Button
  * @{
  */
/* Only one User/Wakeup button */
#define BUTTONn                             ((uint8_t)1)

/**
  * @brief Wakeup push-button
  */
#define WAKEUP_BUTTON_PIN                   GPIO_PIN_0
#define WAKEUP_BUTTON_GPIO_PORT             GPIOA
#define WAKEUP_BUTTON_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define WAKEUP_BUTTON_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#define WAKEUP_BUTTON_EXTI_IRQn             EXTI0_IRQn

/* Define the USER button as an alias of the Wakeup button */
#define USER_BUTTON_PIN                   WAKEUP_BUTTON_PIN
#define USER_BUTTON_GPIO_PORT             WAKEUP_BUTTON_GPIO_PORT
#define USER_BUTTON_GPIO_CLK_ENABLE()     WAKEUP_BUTTON_GPIO_CLK_ENABLE()
#define USER_BUTTON_GPIO_CLK_DISABLE()    WAKEUP_BUTTON_GPIO_CLK_DISABLE()
#define USER_BUTTON_EXTI_IRQn             WAKEUP_BUTTON_EXTI_IRQn

#define BUTTON_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOA_CLK_ENABLE()

/**
  * @}
  */

/**
  * @brief Discovery Pins definition
  * TODO : to be modified/reviewed
  */
#define AUDIO_INT_PIN                  GPIO_PIN_7
#define AUDIO_INT_PORT                 GPIOB
#define AUDIO_INT_PORT_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()

#define OTG_FS1_OVER_CURRENT_PIN                  GPIO_PIN_7
#define OTG_FS1_OVER_CURRENT_PORT                 GPIOB
#define OTG_FS1_OVER_CURRENT_PORT_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()

#define OTG_FS1_POWER_SWITCH_PIN                  GPIO_PIN_2
#define OTG_FS1_POWER_SWITCH_PORT                 GPIOB
#define OTG_FS1_POWER_SWITCH_PORT_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()

/**
  * @brief SD-detect signal
  */
#define SD_DETECT_PIN                        ((uint32_t)GPIO_PIN_2)
#define SD_DETECT_GPIO_PORT                  ((GPIO_TypeDef*)GPIOG)
#define SD_DETECT_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOG_CLK_ENABLE()
#define SD_DETECT_GPIO_CLK_DISABLE()         __HAL_RCC_GPIOG_CLK_DISABLE()
#define SD_DETECT_EXTI_IRQn                  EXTI2_IRQn

/**
  * @brief TS_INT signal from TouchScreen when it is configured in interrupt mode
  * GPIOJ5 is used for that purpose on Manta Dragon Discovery board
  */
#define TS_INT_PIN                        ((uint32_t)GPIO_PIN_5)
#define TS_INT_GPIO_PORT                  ((GPIO_TypeDef*)GPIOJ)
#define TS_INT_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOJ_CLK_ENABLE()
#define TS_INT_GPIO_CLK_DISABLE()         __HAL_RCC_GPIOJ_CLK_DISABLE()
#define TS_INT_EXTI_IRQn                  EXTI9_5_IRQn

/**
  * @brief TouchScreen FT6206 Slave I2C address
  */
#define TS_I2C_ADDRESS                   ((uint16_t)0x54)


/**
  * @brief Audio I2C Slave address
  */
#define AUDIO_I2C_ADDRESS                ((uint16_t)0x94)

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
#ifndef I2C1_SCL_FREQ_KHZ
#define I2C1_SCL_FREQ_KHZ                  400000 /*!< f(I2C_SCL) = 400 kHz */
#endif /* I2C1_SCL_FREQ_KHZ */

/**
  * @brief User can use this section to tailor I2C1/I2C1 instance used and associated
  * resources.
  * Definition for I2C1 clock resources
  */
#define DISCO_I2C1                             I2C1
#define DISCO_I2C1_CLK_ENABLE()                __HAL_RCC_I2C1_CLK_ENABLE()
#define DISCO_DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define DISCO_I2C1_SCL_SDA_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()

#define DISCO_I2C1_FORCE_RESET()               __HAL_RCC_I2C1_FORCE_RESET()
#define DISCO_I2C1_RELEASE_RESET()             __HAL_RCC_I2C1_RELEASE_RESET()

/** @brief Definition for I2C1 Pins
  */
#define DISCO_I2C1_SCL_PIN                     GPIO_PIN_8 /*!< PB8 */
#define DISCO_I2C1_SCL_SDA_GPIO_PORT           GPIOB
#define DISCO_I2C1_SCL_SDA_AF                  GPIO_AF4_I2C1
#define DISCO_I2C1_SDA_PIN                     GPIO_PIN_9 /*!< PB9 */

/** @brief Definition of I2C interrupt requests
  */
#define DISCO_I2C1_EV_IRQn                     I2C1_EV_IRQn
#define DISCO_I2C1_ER_IRQn                     I2C1_ER_IRQn



/**
  * @brief I2C2 clock speed configuration (in Hz)
  * WARNING:
  * Make sure that this define is not already declared in other files
  * It can be used in parallel by other modules.
  */
#ifndef I2C2_SCL_FREQ_KHZ
#define I2C2_SCL_FREQ_KHZ                  100000 /*!< f(I2C2_SCL) < 100 kHz */
#endif /* I2C2_SCL_FREQ_KHZ */

/**
  * @brief User can use this section to tailor I2C2/I2C2 instance used and associated
  * resources (audio codec).
  * Definition for I2C2 clock resources
  */
#define DISCO_I2C2                             I2C2
#define DISCO_I2C2_CLK_ENABLE()                __HAL_RCC_I2C2_CLK_ENABLE()
#define DISCO_I2C2_SCL_SDA_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOH_CLK_ENABLE()

#define DISCO_I2C2_FORCE_RESET()               __HAL_RCC_I2C2_FORCE_RESET()
#define DISCO_I2C2_RELEASE_RESET()             __HAL_RCC_I2C2_RELEASE_RESET()

/** @brief Definition for I2C2 Pins
  */
#define DISCO_I2C2_SCL_PIN                     GPIO_PIN_4 /*!< PH4 */
#define DISCO_I2C2_SCL_SDA_GPIO_PORT           GPIOH
#define DISCO_I2C2_SCL_SDA_AF                  GPIO_AF4_I2C2
#define DISCO_I2C2_SDA_PIN                     GPIO_PIN_5 /*!< PH5 */

/** @brief Definition of I2C2 interrupt requests
  */
#define DISCO_I2C2_EV_IRQn                     I2C2_EV_IRQn
#define DISCO_I2C2_ER_IRQn                     I2C2_ER_IRQn


/**
  * @}
  */

/** @defgroup STM32469I_Discovery_LOW_LEVEL_Exported_Macros STM32469I Discovery Low Level Exported Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I_Discovery_LOW_LEVEL_Exported_Functions STM32469I Discovery Low Level Exported Functions
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

#endif /* __STM32469I_DISCOVERY_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
