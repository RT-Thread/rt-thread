/**
  ******************************************************************************
  * @file    stm32446e_eval.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    14-August-2015
  * @brief   This file contains definitions for STM32446E_EVAL's LEDs,
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

/* IMPORTANT: in order to compile with RevA following flag shall be defined  */
/* in the preprocessor options:  USE_STM32446E_EVAL_REVA !!!!!!!!!! */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32446E_EVAL_H
#define __STM32446E_EVAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* USE_STM32446E_EVAL_REVA must USE USE_IOEXPANDER */
#if defined(USE_STM32446E_EVAL_REVA)
#ifndef USE_IOEXPANDER
#define USE_IOEXPANDER
#endif // USE_IOEXPANDER
#endif // USE_STM32446E_EVAL_REVA

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
   
/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32446E_EVAL
  * @{
  */
      
/** @defgroup STM32446E_EVAL_LOW_LEVEL STM32446E-EVAL LOW LEVEL
  * @{
  */ 

/** @defgroup STM32446E_EVAL_LOW_LEVEL_Exported_Types STM32446E EVAL Low Level Exported Types
  * @{
  */
typedef enum 
{
#if defined(USE_IOEXPANDER)
LED1 = 0,
LED_GREEN = LED1,
LED2 = 1,
LED_ORANGE = LED2,
LED3 = 2,
LED_RED = LED3,
LED4 = 3,
LED_BLUE = LED4
#else
LED1 = 0,
LED_GREEN = LED1,
LED3 = 1,
LED_RED = LED3,
#endif /* USE_IOEXPANDER */
}Led_TypeDef;


typedef enum 
{  
  BUTTON_WAKEUP = 0,
  BUTTON_TAMPER = 1,
  BUTTON_KEY = 2
}Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
}ButtonMode_TypeDef;

#if defined(USE_IOEXPANDER)
typedef enum 
{  
  JOY_MODE_GPIO = 0,
  JOY_MODE_EXTI = 1
}JOYMode_TypeDef;

typedef enum 
{ 
  JOY_NONE  = 0,
  JOY_SEL   = 1,
  JOY_DOWN  = 2,
  JOY_LEFT  = 3,
  JOY_RIGHT = 4,
  JOY_UP    = 5
}JOYState_TypeDef;
#endif /* USE_IOEXPANDER */

typedef enum 
{
  COM1 = 0,
  COM2 = 1
}COM_TypeDef;
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_LOW_LEVEL_Exported_Constants STM32446E EVAL Low Level Exported Constants
  * @{
  */ 

/** 
  * @brief  Define for STM32446E_EVAL board
  */ 
#if !defined (USE_STM32446E_EVAL)
 #define USE_STM32446E_EVAL
#endif

/** @addtogroup STM32446E_EVAL_LOW_LEVEL_LED STM32446E EVAL Low Level Led
  * @{
  */

#if !defined(USE_STM32446E_EVAL_REVA)

#if defined(USE_IOEXPANDER)
#define LEDn                             ((uint8_t)4)
#define LED2_PIN                         IO_PIN_21
#define LED4_PIN                         IO_PIN_23
#else
#define LEDn                             ((uint8_t)2)
#endif /* USE_IOEXPANDER */

#define LEDx_GPIO_PORT                   GPIOB
#define LEDx_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define LEDx_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()
#define LED1_PIN                         GPIO_PIN_11
#define LED3_PIN                         GPIO_PIN_4

#else

#define LEDn                             ((uint8_t)4)
#define LED1_PIN                         IO_PIN_20
#define LED3_PIN                         IO_PIN_22
#define LED2_PIN                         IO_PIN_21
#define LED4_PIN                         IO_PIN_23

#endif // !USE_STM32446E_EVAL_REVA


/**
  * @}
  */ 
  
/** @addtogroup STM32446E_EVAL_LOW_LEVEL_BUTTON STM32446E EVAL Low Level Button
  * @{
  */ 
/* Joystick pins are connected to IO Expander (accessible through FMPI2C interface) */ 
#define BUTTONn                             ((uint8_t)3) 

/**
  * @brief Wakeup push-button
  */
#define WAKEUP_BUTTON_PIN                   GPIO_PIN_13
#define WAKEUP_BUTTON_GPIO_PORT             GPIOC
#define WAKEUP_BUTTON_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()  
#define WAKEUP_BUTTON_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOC_CLK_DISABLE()
#define WAKEUP_BUTTON_EXTI_IRQn             EXTI15_10_IRQn 

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

/**
  * @brief MFX Irq Out Pin
  */
#define MFX_IRQOUT_PIN                    GPIO_PIN_0
#define MFX_IRQOUT_GPIO_PORT              GPIOA
#define MFX_IRQOUT_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()  
#define MFX_IRQOUT_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOA_CLK_DISABLE()
#define MFX_IRQOUT_EXTI_IRQn              EXTI0_IRQn

#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)    do { if((__INDEX__) == 0) {WAKEUP_BUTTON_GPIO_CLK_ENABLE();} else\
                                                   if((__INDEX__) == 1) {TAMPER_BUTTON_GPIO_CLK_ENABLE();} else\
                                                                        {KEY_BUTTON_GPIO_CLK_ENABLE();   }} while(0)											   

#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)    (((__INDEX__) == 0) ? WAKEUP_BUTTON_GPIO_CLK_DISABLE() :\
                                                ((__INDEX__) == 1) ? TAMPER_BUTTON_GPIO_CLK_DISABLE() : KEY_BUTTON_GPIO_CLK_DISABLE())
/**
  * @}
  */ 

/** @addtogroup STM32446E_EVAL_LOW_LEVEL_COM STM32446E EVAL Low Level COM
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
#define EVAL_COM1_TX_GPIO_PORT             GPIOA
#define EVAL_COM1_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()   
#define EVAL_COM1_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()  
#define EVAL_COM1_TX_AF                    GPIO_AF7_USART1

#define EVAL_COM1_RX_PIN                   GPIO_PIN_10
#define EVAL_COM1_RX_GPIO_PORT             GPIOA
#define EVAL_COM1_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()   
#define EVAL_COM1_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()  
#define EVAL_COM1_RX_AF                    GPIO_AF7_USART1

#define EVAL_COM1_IRQn                     USART1_IRQn

#define EVAL_COMx_CLK_ENABLE(__INDEX__)            do { if((__INDEX__) == COM1) {EVAL_COM1_CLK_ENABLE();} } while(0)
#define EVAL_COMx_CLK_DISABLE(__INDEX__)           (((__INDEX__) == 0) ? EVAL_COM1_CLK_DISABLE() : 0)

#define EVAL_COMx_TX_GPIO_CLK_ENABLE(__INDEX__)    do { if((__INDEX__) == COM1) {EVAL_COM1_TX_GPIO_CLK_ENABLE();} } while(0)
#define EVAL_COMx_TX_GPIO_CLK_DISABLE(__INDEX__)   (((__INDEX__) == 0) ? EVAL_COM1_TX_GPIO_CLK_DISABLE() : 0)

#define EVAL_COMx_RX_GPIO_CLK_ENABLE(__INDEX__)    do { if((__INDEX__) == COM1) {EVAL_COM1_RX_GPIO_CLK_ENABLE();} } while(0)
#define EVAL_COMx_RX_GPIO_CLK_DISABLE(__INDEX__)   (((__INDEX__) == 0) ? EVAL_COM1_RX_GPIO_CLK_DISABLE() : 0)

/**
  * @brief Joystick Pins definition 
  */ 
#if defined(USE_IOEXPANDER)

#define JOY_SEL_PIN                    IO_PIN_5
#define JOY_UP_PIN                     IO_PIN_4
#define JOY_DOWN_PIN                   IO_PIN_3
#define JOY_LEFT_PIN                   IO_PIN_2
#define JOY_RIGHT_PIN                  IO_PIN_1
#define JOY_NONE_PIN                   JOY_ALL_PINS
#define JOY_ALL_PINS                   (IO_PIN_5 | IO_PIN_1 | IO_PIN_2 | IO_PIN_3 | IO_PIN_4)

#endif /* USE_IOEXPANDER */

/**
  * @brief Eval Pins definition connected to MFX
  */

#if defined(USE_IOEXPANDER)

#define XSDN_PIN                       IO_PIN_10    
#define RSTI_PIN                       IO_PIN_11    
#define CAM_PLUG_PIN                   IO_PIN_12    
#define AUDIO_INT_PIN                  IO_PIN_5     
#define OTG_FS1_OVER_CURRENT_PIN       IO_PIN_6      
#define OTG_FS1_POWER_SWITCH_PIN       IO_PIN_7     
#define OTG_FS2_OVER_CURRENT_PIN       IO_PIN_8     
#define SD_DETECT_PIN                  IO_PIN_15    

#endif /* USE_IOEXPANDER */


/* Exported constant IO ------------------------------------------------------*/

/*  The MFX_I2C_ADDR input pin selects the MFX I2C device address 
        MFX_I2C_ADDR input pin     MFX I2C device address
            0                           b: 1000 010x    (0x84)
            1                           b: 1000 011x    (0x86)
   This input is sampled during the MFX firmware startup.  */

#define IO_I2C_ADDRESS                   ((uint16_t)0x84)  /*mfx MFX_I2C_ADDR 0*/
#define IO_I2C_ADDRESS_2                 ((uint16_t)0x86)  /*mfx MFX_I2C_ADDR 1*/
#define TS_I2C_ADDRESS                   ((uint16_t)0x84)  /*mfx MFX_I2C_ADDR 0*/
#define TS_I2C_ADDRESS_2                 ((uint16_t)0x86)  /*mfx MFX_I2C_ADDR 1*/


#define CAMERA_I2C_ADDRESS               ((uint16_t)0x5A)
#define AUDIO_I2C_ADDRESS                ((uint16_t)0x34)
#define EEPROM_I2C_ADDRESS_A01           ((uint16_t)0xA0)
#define EEPROM_I2C_ADDRESS_A02           ((uint16_t)0xA6)  


/* User can use this section to tailor I2Cx/I2Cx instance used and associated 
   resources */
/* Definition for I2Cx clock resources */
#define EVAL_I2Cx                             FMPI2C1
#define EVAL_I2Cx_CLK_ENABLE()                __HAL_RCC_FMPI2C1_CLK_ENABLE()
#define EVAL_I2Cx_CLK_DISABLE()               __HAL_RCC_FMPI2C1_CLK_DISABLE()
#define EVAL_DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define EVAL_I2Cx_SCL_SDA_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOD_CLK_ENABLE()
#define EVAL_I2Cx_SCL_SDA_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOD_CLK_DISABLE()

#define EVAL_I2Cx_FORCE_RESET()               __HAL_RCC_FMPI2C1_FORCE_RESET()
#define EVAL_I2Cx_RELEASE_RESET()             __HAL_RCC_FMPI2C1_RELEASE_RESET()
   
/* Definition for I2Cx Pins */
#define EVAL_I2Cx_SCL_PIN                     GPIO_PIN_12
#define EVAL_I2Cx_SCL_SDA_GPIO_PORT           GPIOD
#define EVAL_I2Cx_SCL_SDA_AF                  GPIO_AF4_FMPI2C1
#define EVAL_I2Cx_SDA_PIN                     GPIO_PIN_13

/* I2C interrupt requests */
#define EVAL_I2Cx_EV_IRQn                     FMPI2C1_EV_IRQn
#define EVAL_I2Cx_ER_IRQn                     FMPI2C1_ER_IRQn

#ifndef EVAL_I2Cx_TIMING  
#define EVAL_I2Cx_TIMING                      ((uint32_t)0x00805252)   
#endif /* EVAL_I2Cx_TIMING */


/**
  * @}
  */ 

/**
  * @}
  */ 
  
/** @defgroup STM32446E_EVAL_LOW_LEVEL_Exported_Macros STM32446E EVAL Low Level Exported Macros
  * @{
  */  
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_LOW_LEVEL_Exported_Functions STM32446E EVAL Low Level Exported Functions
  * @{
  */
uint32_t         BSP_GetVersion(void);  
void             BSP_LED_Init(Led_TypeDef Led);
void             BSP_LED_DeInit(Led_TypeDef Led);
void             BSP_LED_On(Led_TypeDef Led);
void             BSP_LED_Off(Led_TypeDef Led);
void             BSP_LED_Toggle(Led_TypeDef Led);
void             BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
void             BSP_PB_DeInit(Button_TypeDef Button);
uint32_t         BSP_PB_GetState(Button_TypeDef Button);
void             BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef *husart);
void             BSP_COM_DeInit(COM_TypeDef COM, UART_HandleTypeDef *huart);
#if defined(USE_IOEXPANDER)
uint8_t          BSP_JOY_Init(JOYMode_TypeDef JoyMode);
void             BSP_JOY_DeInit(void);
JOYState_TypeDef BSP_JOY_GetState(void);
void             BSP_MFX_reg_access_for_debug(void);
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

#ifdef __cplusplus
}
#endif

#endif /* __STM32446E_EVAL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
